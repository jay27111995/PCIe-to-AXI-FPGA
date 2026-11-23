#include "pcie-util.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

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
#define PCIE_TRACE_META  0x2064

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
// AXI Sniffer Register offsets (0x3xxx)
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

// Control bits (same for both sniffers)
#define CTRL_START  (1 << 0)
#define CTRL_STOP   (1 << 1)
#define CTRL_CLEAR  (1 << 2)

const char* tx_state_name(int state) {
    switch (state) {
        case 0: return "IDLE";
        case 1: return "BAR_WR_ADDR";
        case 2: return "BAR_WR_RESP";
        case 3: return "BAR_RD_ADDR";
        case 4: return "BAR_RD_DATA";
        case 5: return "BAR_CPL";
        case 6: return "DMA_MRD";
        case 7: return "DMA_MWR";
        case 8: return "MSIX";
        case 9: return "SEND";
        default: return "???";
    }
}

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
    printf("  tx_state:      %d (%s)\n", (status >> 4) & 0xF, tx_state_name((status >> 4) & 0xF));
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
    printf("  # | Cycle      | Dir | State      | Type  | Len | Header (DW0-DW3)\n");
    printf("----+------------+-----+------------+-------+-----+------------------------------------------\n");
    
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
        uint32_t meta = dbg_read32(bar, PCIE_TRACE_META);
        
        // Parse meta: [31:5] timestamp, [4:1] tx_state, [0] direction
        int dir = meta & 1;
        int state = (meta >> 1) & 0xF;
        uint32_t timestamp = (meta >> 5) & 0x7FFFFFF;  // 27-bit timestamp
        
        // Parse TLP from header DW0: [31:29]=fmt, [28:24]=type, [9:0]=length
        int fmt = (hdr0 >> 29) & 0x7;
        int type = (hdr0 >> 24) & 0x1F;
        int len = hdr0 & 0x3FF;  // Length in DW
        
        printf("%3d | %10u | %s  | %-10s | %-5s | %3d | %08x %08x %08x %08x\n",
               i, timestamp, dir ? "TX" : "RX", tx_state_name(state), 
               tlp_type_name(fmt, type), len, hdr0, hdr1, hdr2, hdr3);
        
        // Print data if TLP has data (CplD, MWr)
        bool has_data = (fmt & 0x2);  // bit 1 of fmt indicates data present
        if (has_data && len > 0) {
            int dw_to_show = (len > 8) ? 8 : len;
            printf("    Data (%d DW): ", len);
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
    
    printf("\n=== AXI Sniffer Status ===\n");
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
// Combined Functions
//=============================================================================
void start_all(PCIe::BaseAddressRegister& bar) {
    pcie_start(bar, 1);  // stop-on-full mode
    axi_start(bar);
    printf("Both sniffers started.\n");
}

void stop_all(PCIe::BaseAddressRegister& bar) {
    pcie_stop(bar);
    axi_stop(bar);
    printf("Both sniffers stopped.\n");
}

void dump_all_status(PCIe::BaseAddressRegister& bar) {
    pcie_dump_status(bar);
    axi_dump_status(bar);
}

void dump_all_trace(PCIe::BaseAddressRegister& bar, int pcie_count, int axi_count) {
    pcie_dump_trace(bar, pcie_count);
    axi_dump_trace(bar, axi_count);
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

void usage(const char* prog) {
    printf("Usage: %s <pcie_device> [command]\n", prog);
    printf("\nCommands:\n");
    printf("  status          Show status of both sniffers (default)\n");
    printf("  pcie [N]        Dump PCIe TLP trace (up to N entries)\n");
    printf("  axi [N]         Dump AXI transaction trace (up to N entries)\n");
    printf("  trace [N]       Dump both traces (up to N entries each)\n");
    printf("  start           Start both sniffers\n");
    printf("  stop            Stop both sniffers\n");
    printf("  clear           Clear both trace buffers\n");
    printf("  test            Self-test: capture BAR writes/reads, dump traces\n");
    printf("\nExamples:\n");
    printf("  %s 0000:b1:00.0              # Show status\n", prog);
    printf("  %s 0000:b1:00.0 trace 10     # Dump both traces (10 entries)\n", prog);
    printf("  %s 0000:b1:00.0 test         # Run self-test\n", prog);
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
        
    } else if (strcmp(cmd, "trace") == 0) {
        dump_all_trace(bar, count, count);
        
    } else if (strcmp(cmd, "start") == 0) {
        start_all(bar);
        
    } else if (strcmp(cmd, "stop") == 0) {
        stop_all(bar);
        
    } else if (strcmp(cmd, "clear") == 0) {
        bar.write64(PCIE_CONTROL, CTRL_CLEAR);
        bar.write64(AXI_CONTROL, CTRL_CLEAR);
        printf("Both trace buffers cleared.\n");
        
    } else if (strcmp(cmd, "test") == 0) {
        self_test(bar);
        
    } else {
        printf("Unknown command: %s\n", cmd);
        usage(argv[0]);
        return 1;
    }

    return 0;
}
