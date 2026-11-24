#include "pcie-util.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <algorithm>

//=============================================================================
// Helper: Read 32-bit debug register using 64-bit access
// The bridge only supports 64-bit transactions; 32-bit reads return 0xFFFFFFFF
//=============================================================================
inline uint32_t dbg_read32(PCIe::BaseAddressRegister& bar, uint64_t offset) {
    // Align to 8-byte boundary and read 64 bits
    uint64_t aligned = offset & ~7ULL;
    uint64_t val64 = bar.read64(aligned);
    // Return upper or lower 32 bits based on offset
    return (offset & 4) ? (uint32_t)(val64 >> 32) : (uint32_t)val64;
}

//=============================================================================
// PCIe Sniffer Register offsets (0x2xxx)
//=============================================================================
#define PCIE_STATUS      0x2000
#define PCIE_CONTROL     0x2004
#define PCIE_MODE        0x2008
#define PCIE_TRIGGER     0x200C
#define PCIE_WRITE_PTR   0x2010
#define PCIE_ENTRY_COUNT 0x2014
#define PCIE_RX_COUNT    0x2018
#define PCIE_TX_COUNT    0x201C
#define PCIE_CYCLE_LO    0x2020
#define PCIE_CYCLE_HI    0x2024

#define PCIE_READ_PTR    0x2030
#define PCIE_TRACE_HDR0  0x2034
#define PCIE_TRACE_HDR1  0x2038
#define PCIE_TRACE_HDR2  0x203C
#define PCIE_TRACE_HDR3  0x2040
#define PCIE_TRACE_DATA0 0x2044
#define PCIE_TRACE_DATA1 0x2048
#define PCIE_TRACE_DATA2 0x204C
#define PCIE_TRACE_DATA3 0x2050
#define PCIE_TRACE_DATA4 0x2054
#define PCIE_TRACE_DATA5 0x2058
#define PCIE_TRACE_DATA6 0x205C
#define PCIE_TRACE_DATA7 0x2060
#define PCIE_TRACE_META0 0x2064  // timestamp[31:0]
#define PCIE_TRACE_META1 0x2068  // control signals + direction + tx_state

// Last-seen RX TLP (header + 256-bit data)
#define PCIE_LAST_RX_HDR0  0x2070
#define PCIE_LAST_RX_HDR1  0x2074
#define PCIE_LAST_RX_HDR2  0x2078
#define PCIE_LAST_RX_HDR3  0x207C
#define PCIE_LAST_RX_DATA0 0x2080
#define PCIE_LAST_RX_DATA1 0x2084
#define PCIE_LAST_RX_DATA2 0x2088
#define PCIE_LAST_RX_DATA3 0x208C
#define PCIE_LAST_RX_DATA4 0x2090
#define PCIE_LAST_RX_DATA5 0x2094
#define PCIE_LAST_RX_DATA6 0x2098
#define PCIE_LAST_RX_DATA7 0x209C

// Last-seen TX TLP (header + 256-bit data)
#define PCIE_LAST_TX_HDR0  0x20A0
#define PCIE_LAST_TX_HDR1  0x20A4
#define PCIE_LAST_TX_HDR2  0x20A8
#define PCIE_LAST_TX_HDR3  0x20AC
#define PCIE_LAST_TX_DATA0 0x20B0
#define PCIE_LAST_TX_DATA1 0x20B4
#define PCIE_LAST_TX_DATA2 0x20B8
#define PCIE_LAST_TX_DATA3 0x20BC
#define PCIE_LAST_TX_DATA4 0x20C0
#define PCIE_LAST_TX_DATA5 0x20C4
#define PCIE_LAST_TX_DATA6 0x20C8
#define PCIE_LAST_TX_DATA7 0x20CC

//=============================================================================
// AXI Slave Sniffer Register offsets (0x3000-0x37FF) - BAR access
//=============================================================================
#define AXI_STATUS       0x3000
#define AXI_CONTROL      0x3004
#define AXI_WRITE_PTR    0x3008
#define AXI_ENTRY_COUNT  0x300C
#define AXI_AW_COUNT     0x3010
#define AXI_AR_COUNT     0x3014

#define AXI_READ_PTR     0x3020
#define AXI_TRACE_ADDR   0x3024
#define AXI_TRACE_DATA0  0x3028
#define AXI_TRACE_DATA1  0x302C
#define AXI_TRACE_META   0x3030

//=============================================================================
// DMA AXI Sniffer Register offsets (0x3800-0x3FFF) - DMA to host
//=============================================================================
#define DMA_AXI_STATUS       0x3800
#define DMA_AXI_CONTROL      0x3804
#define DMA_AXI_WRITE_PTR    0x3808
#define DMA_AXI_ENTRY_COUNT  0x380C
#define DMA_AXI_AW_COUNT     0x3810
#define DMA_AXI_AR_COUNT     0x3814

#define DMA_AXI_READ_PTR     0x3820
#define DMA_AXI_TRACE_ADDR   0x3824
#define DMA_AXI_TRACE_DATA0  0x3828
#define DMA_AXI_TRACE_DATA1  0x382C
#define DMA_AXI_TRACE_META   0x3830

// Control bits (same for all sniffers)
#define CTRL_START  (1 << 0)
#define CTRL_STOP   (1 << 1)
#define CTRL_CLEAR  (1 << 2)

const char* tlp_type_name(int fmt, int type) {
    if (type == 0x00) {
        if (fmt == 0 || fmt == 1) return "MRd";
        if (fmt == 2 || fmt == 3) return "MWr";
    }
    if (type == 0x0A) return "CplD";
    if (type == 0x04) return "CfgRd";
    if (type == 0x44) return "CfgWr";
    return "???";
}

//=============================================================================
// PCIe Sniffer Functions
//=============================================================================
void pcie_start(PCIe::BaseAddressRegister& bar, int mode) {
    bar.write64(PCIE_CONTROL, CTRL_STOP);
    bar.write64(PCIE_CONTROL, CTRL_CLEAR);
    bar.write64(PCIE_MODE, mode);
    bar.write64(PCIE_CONTROL, CTRL_START);
}

void pcie_stop(PCIe::BaseAddressRegister& bar) {
    bar.write64(PCIE_CONTROL, CTRL_STOP);
}

void pcie_dump_status(PCIe::BaseAddressRegister& bar) {
    uint32_t status = dbg_read32(bar, PCIE_STATUS);
    
    printf("=== PCIe Sniffer Status ===\n");
    printf("  rx_seen:       %d\n", status & 1);
    printf("  tx_seen:       %d\n", (status >> 1) & 1);
    printf("  running:       %d\n", (status >> 16) & 1);
    printf("  triggered:     %d\n", (status >> 17) & 1);
    printf("  full:          %d\n", (status >> 18) & 1);
    printf("  write_ptr:     %u\n", dbg_read32(bar, PCIE_WRITE_PTR));
    printf("  entry_count:   %u\n", dbg_read32(bar, PCIE_ENTRY_COUNT));
    printf("  rx_count:      %u\n", dbg_read32(bar, PCIE_RX_COUNT));
    printf("  tx_count:      %u\n", dbg_read32(bar, PCIE_TX_COUNT));
}

void pcie_dump_trace(PCIe::BaseAddressRegister& bar, int count) {
    uint32_t entry_count = dbg_read32(bar, PCIE_ENTRY_COUNT);
    if (entry_count == 0) {
        printf("\nPCIe trace buffer empty.\n");
        return;
    }
    
    int to_dump = (count > 0 && (uint32_t)count < entry_count) ? count : entry_count;
    printf("\n=== PCIe TLP Trace (%u entries, showing %d) ===\n", entry_count, to_dump);
    printf("  # | Time (us)  | Dir | State      | Type  | Details\n");
    printf("----+------------+-----+------------+-------+--------------------------------------------------\n");
    
    for (int i = 0; i < to_dump; i++) {
        // Set read pointer (use 64-bit write for bridge compatibility)
        bar.write64(PCIE_READ_PTR & ~7ULL, i);
        
        uint32_t hdr0 = dbg_read32(bar, PCIE_TRACE_HDR0);
        uint32_t hdr1 = dbg_read32(bar, PCIE_TRACE_HDR1);
        uint32_t hdr2 = dbg_read32(bar, PCIE_TRACE_HDR2);
        uint32_t hdr3 = dbg_read32(bar, PCIE_TRACE_HDR3);
        uint32_t data[8];
        data[0] = dbg_read32(bar, PCIE_TRACE_DATA0);
        data[1] = dbg_read32(bar, PCIE_TRACE_DATA1);
        data[2] = dbg_read32(bar, PCIE_TRACE_DATA2);
        data[3] = dbg_read32(bar, PCIE_TRACE_DATA3);
        data[4] = dbg_read32(bar, PCIE_TRACE_DATA4);
        data[5] = dbg_read32(bar, PCIE_TRACE_DATA5);
        data[6] = dbg_read32(bar, PCIE_TRACE_DATA6);
        data[7] = dbg_read32(bar, PCIE_TRACE_DATA7);
        uint32_t meta0 = dbg_read32(bar, PCIE_TRACE_META0);  // timestamp
        uint32_t meta1 = dbg_read32(bar, PCIE_TRACE_META1);  // control signals
        
        // Parse meta1: 
        // [0] direction, [1] rx_sop, [2] rx_eop, [3] rx_hvalid,
        // [4] rx_dvalid, [7:5] rx_bar, [8] rx_ready, [9] tx_sop, [10] tx_eop,
        // [11] tx_hvalid, [12] tx_dvalid, [13] tx_ready
        int dir = meta1 & 1;
        int rx_sop = (meta1 >> 1) & 1;
        int rx_eop = (meta1 >> 2) & 1;
        int rx_hvalid = (meta1 >> 3) & 1;
        int rx_dvalid = (meta1 >> 4) & 1;
        int rx_bar = (meta1 >> 5) & 0x7;
        int rx_ready = (meta1 >> 8) & 1;
        int tx_sop = (meta1 >> 9) & 1;
        int tx_eop = (meta1 >> 10) & 1;
        int tx_hvalid = (meta1 >> 11) & 1;
        int tx_dvalid = (meta1 >> 12) & 1;
        int tx_ready = (meta1 >> 13) & 1;
        
        // Convert cycles to microseconds (assume 250MHz = 4ns/cycle)
        double time_us = meta0 * 0.004;  // cycles * 4ns / 1000
        
        // Parse TLP from header DW0: [31:29]=fmt, [28:24]=type, [9:0]=length
        int fmt = (hdr0 >> 29) & 0x7;
        int type = (hdr0 >> 24) & 0x1F;
        int len = hdr0 & 0x3FF;  // Length in DW
        
        printf("%3d | %10.3f | %s  | %-5s | ", 
               i, time_us, dir ? "TX" : "RX", 
               tlp_type_name(fmt, type));
        
        // Type-specific details
        if (type == 0b00000 && !(fmt & 0x2)) {
            // MRd: show address and length
            uint32_t addr = (fmt & 0x1) ? hdr3 : hdr2;  // 4DW vs 3DW header
            printf("addr=0x%08x len=%d DW", addr, len);
        } else if (type == 0b00000 && (fmt & 0x2)) {
            // MWr: show address and length
            uint32_t addr = (fmt & 0x1) ? hdr3 : hdr2;
            printf("addr=0x%08x len=%d DW", addr, len);
        } else if (type == 0b01010) {
            // CplD: show tag, byte count, lower addr
            int cpl_status = (hdr1 >> 13) & 0x7;
            int byte_count = hdr1 & 0xFFF;
            int tag = (hdr2 >> 8) & 0xFF;
            int lower_addr = hdr2 & 0x7F;
            printf("tag=0x%02x BC=%d LA=0x%02x %s", 
                   tag, byte_count, lower_addr,
                   cpl_status ? "ERR" : "OK");
        } else {
            // Generic: show header
            printf("hdr: %08x %08x %08x %08x", hdr0, hdr1, hdr2, hdr3);
        }
        
        // Print control signals for debugging
        printf(" | bar=%d", rx_bar);
        if (dir == 0) {  // RX
            printf(" rx[sop=%d eop=%d hv=%d dv=%d rdy=%d]", 
                   rx_sop, rx_eop, rx_hvalid, rx_dvalid, rx_ready);
        } else {  // TX
            printf(" tx[sop=%d eop=%d hv=%d dv=%d rdy=%d]",
                   tx_sop, tx_eop, tx_hvalid, tx_dvalid, tx_ready);
        }
        printf("\n");
        
        // Print data if TLP has data (CplD, MWr)
        bool has_data = (fmt & 0x2);  // bit 1 of fmt indicates data present
        if (has_data && len > 0) {
            int dw_to_show = (len > 8) ? 8 : len;
            printf("      Data: ");
            for (int d = 0; d < dw_to_show; d++) {
                printf("%08x ", data[d]);
            }
            if (len > 8) printf("...");
            printf("\n");
        }
    }
}

//=============================================================================
// AXI Sniffer Functions
//=============================================================================
void axi_start(PCIe::BaseAddressRegister& bar) {
    bar.write64(AXI_CONTROL, CTRL_STOP);
    bar.write64(AXI_CONTROL, CTRL_CLEAR);
    bar.write64(AXI_CONTROL, CTRL_START);
}

void axi_stop(PCIe::BaseAddressRegister& bar) {
    bar.write64(AXI_CONTROL, CTRL_STOP);
}

void axi_dump_status(PCIe::BaseAddressRegister& bar) {
    uint32_t status = dbg_read32(bar, AXI_STATUS);
    
    printf("\n=== AXI Slave Sniffer Status (BAR Access) ===\n");
    printf("  running:       %d\n", status & 1);
    printf("  full:          %d\n", (status >> 1) & 1);
    printf("  aw_seen:       %d\n", (status >> 8) & 1);
    printf("  w_seen:        %d\n", (status >> 9) & 1);
    printf("  b_seen:        %d\n", (status >> 10) & 1);
    printf("  ar_seen:       %d\n", (status >> 11) & 1);
    printf("  r_seen:        %d\n", (status >> 12) & 1);
    printf("  write_ptr:     %u\n", dbg_read32(bar, AXI_WRITE_PTR));
    printf("  entry_count:   %u\n", dbg_read32(bar, AXI_ENTRY_COUNT));
    printf("  aw_count:      %u\n", dbg_read32(bar, AXI_AW_COUNT));
    printf("  ar_count:      %u\n", dbg_read32(bar, AXI_AR_COUNT));
}

void axi_dump_trace(PCIe::BaseAddressRegister& bar, int count) {
    uint32_t entry_count = dbg_read32(bar, AXI_ENTRY_COUNT);
    if (entry_count == 0) {
        printf("\nAXI trace buffer empty.\n");
        return;
    }
    
    int to_dump = (count > 0 && (uint32_t)count < entry_count) ? count : entry_count;
    printf("\n=== AXI Transaction Trace (%u entries, showing %d) ===\n", entry_count, to_dump);
    printf("  # | Cycle      | Ch  | Phase | Addr/Resp  | Data\n");
    printf("----+------------+-----+-------+------------+------------------\n");
    
    for (int i = 0; i < to_dump; i++) {
        // Set read pointer (use 64-bit write for bridge compatibility)
        bar.write64(AXI_READ_PTR & ~7ULL, i);
        
        uint32_t addr = dbg_read32(bar, AXI_TRACE_ADDR);
        uint32_t data0 = dbg_read32(bar, AXI_TRACE_DATA0);
        uint32_t data1 = dbg_read32(bar, AXI_TRACE_DATA1);
        uint32_t meta = dbg_read32(bar, AXI_TRACE_META);
        
        // Parse meta: [31:10] timestamp, [9] phase, [8] channel, [7:0] strb/resp
        int strb_resp = meta & 0xFF;
        int channel = (meta >> 8) & 1;
        int phase = (meta >> 9) & 1;
        uint32_t timestamp = (meta >> 10) & 0x3FFFFF;  // 22-bit timestamp
        
        const char* ch_str = channel ? "RD" : "WR";
        const char* ph_str = phase ? "Resp" : "Req ";
        
        if (phase == 0) {
            // Request - show address
            printf("%3d | %10u | %s | %s  | 0x%08x | %08x_%08x\n",
                   i, timestamp, ch_str, ph_str, addr, data1, data0);
        } else {
            // Response - show response code
            printf("%3d | %10u | %s | %s  | resp=%-5d | %08x_%08x\n",
                   i, timestamp, ch_str, ph_str, strb_resp & 0x3, data1, data0);
        }
    }
}

//=============================================================================
// DMA AXI Sniffer Functions (DMA -> Host memory)
//=============================================================================
void dma_axi_start(PCIe::BaseAddressRegister& bar) {
    bar.write64(DMA_AXI_CONTROL, CTRL_STOP);
    bar.write64(DMA_AXI_CONTROL, CTRL_CLEAR);
    bar.write64(DMA_AXI_CONTROL, CTRL_START);
}

void dma_axi_stop(PCIe::BaseAddressRegister& bar) {
    bar.write64(DMA_AXI_CONTROL, CTRL_STOP);
}

void dma_axi_dump_status(PCIe::BaseAddressRegister& bar) {
    uint32_t status = dbg_read32(bar, DMA_AXI_STATUS);
    
    printf("\n=== DMA AXI Sniffer Status (DMA -> Host) ===\n");
    printf("  running:       %d\n", status & 1);
    printf("  full:          %d\n", (status >> 1) & 1);
    printf("  aw_seen:       %d\n", (status >> 8) & 1);
    printf("  w_seen:        %d\n", (status >> 9) & 1);
    printf("  b_seen:        %d\n", (status >> 10) & 1);
    printf("  ar_seen:       %d\n", (status >> 11) & 1);
    printf("  r_seen:        %d\n", (status >> 12) & 1);
    printf("  write_ptr:     %u\n", dbg_read32(bar, DMA_AXI_WRITE_PTR));
    printf("  entry_count:   %u\n", dbg_read32(bar, DMA_AXI_ENTRY_COUNT));
    printf("  aw_count:      %u\n", dbg_read32(bar, DMA_AXI_AW_COUNT));
    printf("  ar_count:      %u\n", dbg_read32(bar, DMA_AXI_AR_COUNT));
}

void dma_axi_dump_trace(PCIe::BaseAddressRegister& bar, int count) {
    uint32_t entry_count = dbg_read32(bar, DMA_AXI_ENTRY_COUNT);
    if (entry_count == 0) {
        printf("\nDMA AXI trace buffer empty.\n");
        return;
    }
    
    int to_dump = (count > 0 && (uint32_t)count < entry_count) ? count : entry_count;
    printf("\n=== DMA AXI Transaction Trace (%u entries, showing %d) ===\n", entry_count, to_dump);
    printf("  # | Cycle      | Ch  | Phase | Addr/Resp  | Data\n");
    printf("----+------------+-----+-------+------------+------------------\n");
    
    for (int i = 0; i < to_dump; i++) {
        // Set read pointer
        bar.write64(DMA_AXI_READ_PTR & ~7ULL, i);
        
        uint32_t addr = dbg_read32(bar, DMA_AXI_TRACE_ADDR);
        uint32_t data0 = dbg_read32(bar, DMA_AXI_TRACE_DATA0);
        uint32_t data1 = dbg_read32(bar, DMA_AXI_TRACE_DATA1);
        uint32_t meta = dbg_read32(bar, DMA_AXI_TRACE_META);
        
        int strb_resp = meta & 0xFF;
        int channel = (meta >> 8) & 1;
        int phase = (meta >> 9) & 1;
        uint32_t timestamp = (meta >> 10) & 0x3FFFFF;
        
        const char* ch_str = channel ? "RD" : "WR";
        const char* ph_str = phase ? "Resp" : "Req ";
        
        if (phase == 0) {
            printf("%3d | %10u | %s | %s  | 0x%08x | %08x_%08x\n",
                   i, timestamp, ch_str, ph_str, addr, data1, data0);
        } else {
            printf("%3d | %10u | %s | %s  | resp=%-5d | %08x_%08x\n",
                   i, timestamp, ch_str, ph_str, strb_resp & 0x3, data1, data0);
        }
    }
}

//=============================================================================
// Combined Functions
//=============================================================================
void start_all(PCIe::BaseAddressRegister& bar) {
    pcie_start(bar, 1);  // stop-on-full mode
    axi_start(bar);
    dma_axi_start(bar);
    printf("All 3 sniffers started.\n");
}

void stop_all(PCIe::BaseAddressRegister& bar) {
    pcie_stop(bar);
    axi_stop(bar);
    dma_axi_stop(bar);
    printf("All 3 sniffers stopped.\n");
}

void clear_all(PCIe::BaseAddressRegister& bar) {
    bar.write64(PCIE_CONTROL, CTRL_CLEAR);
    bar.write64(AXI_CONTROL, CTRL_CLEAR);
    bar.write64(DMA_AXI_CONTROL, CTRL_CLEAR);
    printf("All 3 sniffers cleared.\n");
}

void dump_all_status(PCIe::BaseAddressRegister& bar) {
    pcie_dump_status(bar);
    axi_dump_status(bar);
    dma_axi_dump_status(bar);
}

void dump_all_trace(PCIe::BaseAddressRegister& bar, int pcie_count, int axi_count) {
    // Collect all events from all 3 sniffers into one merged view
    struct Event {
        uint32_t timestamp;
        char source;      // 'P'=PCIe, 'S'=AXI Slave, 'M'=AXI Master
        char dir;         // 'R'=RX/Read, 'T'=TX/Write
        char type[8];     // TLP type or AXI phase
        uint32_t addr;
        uint64_t data;
        char extra[32];
    };
    
    std::vector<Event> events;
    
    // Read PCIe sniffer entries
    uint32_t pcie_entries = dbg_read32(bar, PCIE_ENTRY_COUNT);
    int pcie_to_read = (pcie_count > 0 && (uint32_t)pcie_count < pcie_entries) ? pcie_count : pcie_entries;
    
    for (int i = 0; i < pcie_to_read; i++) {
        bar.write64(PCIE_READ_PTR & ~7ULL, i);
        uint32_t hdr0 = dbg_read32(bar, PCIE_TRACE_HDR0);
        uint32_t hdr2 = dbg_read32(bar, PCIE_TRACE_HDR2);
        uint32_t hdr3 = dbg_read32(bar, PCIE_TRACE_HDR3);
        uint32_t data0 = dbg_read32(bar, PCIE_TRACE_DATA0);
        uint32_t data1 = dbg_read32(bar, PCIE_TRACE_DATA1);
        uint32_t meta0 = dbg_read32(bar, PCIE_TRACE_META0);
        uint32_t meta1 = dbg_read32(bar, PCIE_TRACE_META1);
        
        Event e;
        e.timestamp = meta0;
        e.source = 'P';
        e.dir = (meta1 & 1) ? 'T' : 'R';
        int fmt = (hdr0 >> 29) & 0x7;
        int type = (hdr0 >> 24) & 0x1F;
        snprintf(e.type, sizeof(e.type), "%s", tlp_type_name(fmt, type));
        e.addr = (fmt & 0x1) ? hdr3 : hdr2;
        e.data = ((uint64_t)data1 << 32) | data0;
        e.extra[0] = '\0';
        events.push_back(e);
    }
    
    // Read AXI Slave sniffer entries
    uint32_t axi_entries = dbg_read32(bar, AXI_ENTRY_COUNT);
    int axi_to_read = (axi_count > 0 && (uint32_t)axi_count < axi_entries) ? axi_count : axi_entries;
    
    for (int i = 0; i < axi_to_read; i++) {
        bar.write64(AXI_READ_PTR & ~7ULL, i);
        uint32_t addr = dbg_read32(bar, AXI_TRACE_ADDR);
        uint32_t data0 = dbg_read32(bar, AXI_TRACE_DATA0);
        uint32_t data1 = dbg_read32(bar, AXI_TRACE_DATA1);
        uint32_t meta = dbg_read32(bar, AXI_TRACE_META);
        
        Event e;
        e.timestamp = (meta >> 10) & 0x3FFFFF;
        e.source = 'S';
        int channel = (meta >> 8) & 1;
        int phase = (meta >> 9) & 1;
        e.dir = channel ? 'R' : 'W';
        snprintf(e.type, sizeof(e.type), "%s", phase ? "Resp" : "Req");
        e.addr = addr;
        e.data = ((uint64_t)data1 << 32) | data0;
        e.extra[0] = '\0';
        events.push_back(e);
    }
    
    // Read DMA AXI sniffer entries
    uint32_t dma_entries = dbg_read32(bar, DMA_AXI_ENTRY_COUNT);
    int dma_to_read = (axi_count > 0 && (uint32_t)axi_count < dma_entries) ? axi_count : dma_entries;
    
    for (int i = 0; i < dma_to_read; i++) {
        bar.write64(DMA_AXI_READ_PTR & ~7ULL, i);
        uint32_t addr = dbg_read32(bar, DMA_AXI_TRACE_ADDR);
        uint32_t data0 = dbg_read32(bar, DMA_AXI_TRACE_DATA0);
        uint32_t data1 = dbg_read32(bar, DMA_AXI_TRACE_DATA1);
        uint32_t meta = dbg_read32(bar, DMA_AXI_TRACE_META);
        
        Event e;
        e.timestamp = (meta >> 10) & 0x3FFFFF;
        e.source = 'M';
        int channel = (meta >> 8) & 1;
        int phase = (meta >> 9) & 1;
        e.dir = channel ? 'R' : 'W';
        snprintf(e.type, sizeof(e.type), "%s", phase ? "Resp" : "Req");
        e.addr = addr;
        e.data = ((uint64_t)data1 << 32) | data0;
        e.extra[0] = '\0';
        events.push_back(e);
    }
    
    if (events.empty()) {
        printf("\nAll trace buffers empty.\n");
        return;
    }
    
    // Sort by timestamp
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.timestamp < b.timestamp;
    });
    
    // Print merged table
    printf("\n=== Merged Event Trace (sorted by timestamp) ===\n");
    printf("Src: P=PCIe, S=AXI-Slave(BAR), M=AXI-Master(DMA)\n\n");
    printf("  # | Cycle      | Src | Dir | Type  | Address    | Data\n");
    printf("----+------------+-----+-----+-------+------------+------------------\n");
    
    for (size_t i = 0; i < events.size(); i++) {
        const Event& e = events[i];
        printf("%3zu | %10u |  %c  |  %c  | %-5s | 0x%08x | %016lx\n",
               i, e.timestamp, e.source, e.dir, e.type, e.addr, e.data);
    }
}

void self_test(PCIe::BaseAddressRegister& bar) {
    printf("=== Self-Test: Capture BAR Activity ===\n\n");
    
    // 1. Start both sniffers
    printf("1. Starting trace capture...\n");
    start_all(bar);
    
    // 2. Write to DMA registers (0x0xxx) - use 64-bit access
    printf("2. Writing to DMA registers...\n");
    bar.write64(0x0010, 0x0000000012345678ULL);  // host_addr
    bar.write64(0x0018, 0x00001000);              // local_addr
    bar.write64(0x0020, 0x00000008);              // length
    
    // 3. Write to RAM (0x1xxx) - use 64-bit access
    printf("3. Writing to RAM...\n");
    bar.write64(0x1000, 0xDEADBEEFCAFEBABEULL);
    bar.write64(0x1008, 0xABCDEF0012345678ULL);
    
    // 4. Read back from RAM - use 64-bit access
    printf("4. Reading from RAM...\n");
    uint64_t v1 = bar.read64(0x1000);
    uint64_t v2 = bar.read64(0x1008);
    printf("   Read back: 0x%016lx 0x%016lx\n", v1, v2);
    
    // 5. Read DMA status - use 64-bit access
    printf("5. Reading DMA status...\n");
    uint64_t dma_status = bar.read64(0x0008);
    printf("   DMA status: 0x%016lx\n", dma_status);
    
    // 6. Stop and dump
    printf("6. Stopping capture...\n\n");
    stop_all(bar);
    
    // 7. Show results
    dump_all_status(bar);
    dump_all_trace(bar, 20, 20);
    
    // 8. Verify RAM values
    printf("\n=== Verification ===\n");
    bool ok = (v1 == 0xDEADBEEFCAFEBABEULL) && (v2 == 0xABCDEF0012345678ULL);
    if (ok) {
        printf("[OK] RAM read/write working!\n");
    } else {
        printf("[FAIL] RAM values don't match!\n");
    }
}

//=============================================================================
// Step-by-step debug commands
//=============================================================================
void test_bar_write(PCIe::BaseAddressRegister& bar) {
    printf("=== Test: BAR Write ===\n");
    clear_all(bar);
    start_all(bar);
    
    printf("Writing 0xDEADBEEF to RAM[0x1000]...\n");
    bar.write64(0x1000, 0xDEADBEEFCAFEBABEULL);
    
    stop_all(bar);
    dump_all_trace(bar, 10, 10);
}

void test_bar_read(PCIe::BaseAddressRegister& bar) {
    printf("=== Test: BAR Read ===\n");
    clear_all(bar);
    start_all(bar);
    
    printf("Reading from RAM[0x1000]...\n");
    uint64_t val = bar.read64(0x1000);
    printf("Got: 0x%016lx\n", val);
    
    stop_all(bar);
    dump_all_trace(bar, 10, 10);
}

void test_bar_rw(PCIe::BaseAddressRegister& bar) {
    printf("=== Test: BAR Write + Read ===\n");
    clear_all(bar);
    start_all(bar);
    
    printf("Writing 0x1234567890ABCDEF to RAM[0x1000]...\n");
    bar.write64(0x1000, 0x1234567890ABCDEFULL);
    
    printf("Reading back from RAM[0x1000]...\n");
    uint64_t val = bar.read64(0x1000);
    printf("Got: 0x%016lx %s\n", val, val == 0x1234567890ABCDEFULL ? "[OK]" : "[FAIL]");
    
    stop_all(bar);
    dump_all_trace(bar, 20, 20);
}

void test_dma_h2c(PCIe::BaseAddressRegister& bar, PCIe::Function& pf) {
    printf("=== Test: DMA Host-to-Card ===\n");
    
    // Allocate host DMA buffer
    uint64_t host_iova = 0x100000;
    void* host_buf = pf.createDmaArea(4096, host_iova);
    if (!host_buf) {
        printf("Failed to allocate DMA buffer\n");
        return;
    }
    
    // Fill host buffer with test pattern
    uint64_t* buf = (uint64_t*)host_buf;
    for (int i = 0; i < 8; i++) buf[i] = 0xAAAABBBBCCCC0000ULL | i;
    
    clear_all(bar);
    start_all(bar);
    
    printf("Setting up DMA: host 0x%lx -> local 0x1000, 64 bytes\n", host_iova);
    bar.write64(0x0010, host_iova);   // host_addr
    bar.write64(0x0018, 0x1000);      // local_addr
    bar.write64(0x0020, 64);          // length
    bar.write64(0x0000, 0x1);         // ctrl: start, dir=H2C
    
    // Wait for completion
    usleep(1000);
    uint64_t status = bar.read64(0x0008);
    printf("DMA status: 0x%lx (done=%lu)\n", status, (status >> 1) & 1);
    
    stop_all(bar);
    dump_all_trace(bar, 30, 30);
}

void test_dma_c2h(PCIe::BaseAddressRegister& bar, PCIe::Function& pf) {
    printf("=== Test: DMA Card-to-Host ===\n");
    
    // First write test data to local RAM
    printf("Writing test data to local RAM[0x1000]...\n");
    bar.write64(0x1000, 0x1111111111111111ULL);
    bar.write64(0x1008, 0x2222222222222222ULL);
    
    // Allocate host DMA buffer
    uint64_t host_iova = 0x100000;
    void* host_buf = pf.createDmaArea(4096, host_iova);
    if (!host_buf) {
        printf("Failed to allocate DMA buffer\n");
        return;
    }
    memset(host_buf, 0, 4096);
    
    clear_all(bar);
    start_all(bar);
    
    printf("Setting up DMA: local 0x1000 -> host 0x%lx, 16 bytes\n", host_iova);
    bar.write64(0x0010, host_iova);   // host_addr
    bar.write64(0x0018, 0x1000);      // local_addr
    bar.write64(0x0020, 16);          // length
    bar.write64(0x0000, 0x3);         // ctrl: start, dir=C2H
    
    // Wait for completion
    usleep(1000);
    uint64_t status = bar.read64(0x0008);
    printf("DMA status: 0x%lx (done=%lu)\n", status, (status >> 1) & 1);
    
    // Check host buffer
    uint64_t* buf = (uint64_t*)host_buf;
    printf("Host buffer: 0x%016lx 0x%016lx\n", buf[0], buf[1]);
    
    stop_all(bar);
    dump_all_trace(bar, 30, 30);
}

void usage(const char* prog) {
    printf("Usage: %s <pcie_device> [command]\n", prog);
    printf("\nBasic Commands:\n");
    printf("  status          Show status of all 3 sniffers (default)\n");
    printf("  start           Start all sniffers\n");
    printf("  stop            Stop all sniffers\n");
    printf("  clear           Clear all trace buffers & reset timestamp\n");
    printf("  trace [N]       Dump merged trace (up to N entries)\n");
    printf("\nIndividual Traces:\n");
    printf("  pcie [N]        Dump PCIe TLP trace only\n");
    printf("  axi [N]         Dump AXI slave trace only\n");
    printf("  dma [N]         Dump DMA AXI trace only\n");
    printf("\nStep-by-Step Tests:\n");
    printf("  test_wr         Trace a single BAR write\n");
    printf("  test_rd         Trace a single BAR read\n");
    printf("  test_rw         Trace BAR write + read\n");
    printf("  test_h2c        Trace DMA host-to-card\n");
    printf("  test_c2h        Trace DMA card-to-host\n");
    printf("  test            Full self-test (legacy)\n");
    printf("\nExamples:\n");
    printf("  %s 0000:b1:00.0              # Show status\n", prog);
    printf("  %s 0000:b1:00.0 test_wr      # Trace a BAR write\n", prog);
    printf("  %s 0000:b1:00.0 trace 20     # Dump merged trace\n", prog);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe-AXI Bridge Debug ===\n");
    printf("Device: %s\n\n", argv[1]);

    const char* cmd = (argc > 2) ? argv[2] : "status";
    int count = (argc > 3) ? atoi(argv[3]) : 20;
    
    if (strcmp(cmd, "status") == 0) {
        dump_all_status(bar);
        
    } else if (strcmp(cmd, "pcie") == 0) {
        pcie_dump_trace(bar, count);
        
    } else if (strcmp(cmd, "axi") == 0) {
        axi_dump_trace(bar, count);
        
    } else if (strcmp(cmd, "dma") == 0) {
        dma_axi_dump_trace(bar, count);
        
    } else if (strcmp(cmd, "trace") == 0) {
        dump_all_trace(bar, count, count);
        
    } else if (strcmp(cmd, "start") == 0) {
        start_all(bar);
        
    } else if (strcmp(cmd, "stop") == 0) {
        stop_all(bar);
        
    } else if (strcmp(cmd, "clear") == 0) {
        clear_all(bar);
        
    } else if (strcmp(cmd, "test") == 0) {
        self_test(bar);
        
    } else if (strcmp(cmd, "test_wr") == 0) {
        test_bar_write(bar);
        
    } else if (strcmp(cmd, "test_rd") == 0) {
        test_bar_read(bar);
        
    } else if (strcmp(cmd, "test_rw") == 0) {
        test_bar_rw(bar);
        
    } else if (strcmp(cmd, "test_h2c") == 0) {
        test_dma_h2c(bar, pf);
        
    } else if (strcmp(cmd, "test_c2h") == 0) {
        test_dma_c2h(bar, pf);
        
    } else {
        printf("Unknown command: %s\n", cmd);
        usage(argv[0]);
        return 1;
    }

    return 0;
}
