//=============================================================================
// dump_debug.cpp - Debug tool for PCIe-AXI Bridge with 3 Sniffers
//
// New Memory Map (refactored 2024-11-25):
//   PCIe Sniffer (0x2000-0x2FFF): 32 entries x 64 bytes
//   AXI Slave Sniffer (0x3000-0x37FF): 64 entries x 32 bytes
//   AXI Master Sniffer (0x3800-0x3FFF): 64 entries x 32 bytes
//=============================================================================
#include "pcie-util.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <algorithm>

//=============================================================================
// PCIe Sniffer Memory Map (0x2000 base)
//   0x000: control/status - write [0]=start, [1]=stop, [2]=clear
//                         - read  [0]=running, [1]=full
//   0x008: write_ptr
//   0x010: entry_count
//   0x018: rx_count
//   0x020: tx_count
//   0x028: timestamp
//   0x040-0x07F: last RX TLP (hdr + data)
//   0x080-0x0BF: last TX TLP (hdr + data)
//   0x100+: trace entries (32 entries x 64 bytes = 8 QWs each)
//=============================================================================
#define PCIE_BASE        0x2000
#define PCIE_STATUS      (PCIE_BASE + 0x000)
#define PCIE_WRITE_PTR   (PCIE_BASE + 0x008)
#define PCIE_ENTRY_COUNT (PCIE_BASE + 0x010)
#define PCIE_RX_COUNT    (PCIE_BASE + 0x018)
#define PCIE_TX_COUNT    (PCIE_BASE + 0x020)
#define PCIE_TIMESTAMP   (PCIE_BASE + 0x028)
#define PCIE_LAST_RX     (PCIE_BASE + 0x040)
#define PCIE_LAST_TX     (PCIE_BASE + 0x080)
#define PCIE_TRACE       (PCIE_BASE + 0x100)
#define PCIE_DEPTH       32
#define PCIE_ENTRY_SIZE  64  // bytes per entry (8 QWs)

//=============================================================================
// AXI Slave Sniffer Memory Map (0x3000 base)
//   0x000: control/status
//   0x008: write_ptr
//   0x010: entry_count
//   0x018: aw_count
//   0x020: ar_count
//   0x028: timestamp
//   0x040+: trace entries (64 entries x 32 bytes = 4 QWs each)
//=============================================================================
#define AXI_SLV_BASE        0x3000
#define AXI_SLV_STATUS      (AXI_SLV_BASE + 0x000)
#define AXI_SLV_WRITE_PTR   (AXI_SLV_BASE + 0x008)
#define AXI_SLV_ENTRY_COUNT (AXI_SLV_BASE + 0x010)
#define AXI_SLV_AW_COUNT    (AXI_SLV_BASE + 0x018)
#define AXI_SLV_AR_COUNT    (AXI_SLV_BASE + 0x020)
#define AXI_SLV_TIMESTAMP   (AXI_SLV_BASE + 0x028)
#define AXI_SLV_TRACE       (AXI_SLV_BASE + 0x040)
#define AXI_SLV_DEPTH       64
#define AXI_SLV_ENTRY_SIZE  32  // bytes per entry (4 QWs)

//=============================================================================
// AXI Master Sniffer Memory Map (0x3800 base)
//=============================================================================
#define AXI_MST_BASE        0x3800
#define AXI_MST_STATUS      (AXI_MST_BASE + 0x000)
#define AXI_MST_WRITE_PTR   (AXI_MST_BASE + 0x008)
#define AXI_MST_ENTRY_COUNT (AXI_MST_BASE + 0x010)
#define AXI_MST_AW_COUNT    (AXI_MST_BASE + 0x018)
#define AXI_MST_AR_COUNT    (AXI_MST_BASE + 0x020)
#define AXI_MST_TIMESTAMP   (AXI_MST_BASE + 0x028)
#define AXI_MST_TRACE       (AXI_MST_BASE + 0x040)
#define AXI_MST_DEPTH       64
#define AXI_MST_ENTRY_SIZE  32

// Control bits (same for all sniffers)
#define CTRL_START  1
#define CTRL_STOP   2
#define CTRL_CLEAR  4

//=============================================================================
// TLP Type Names
//=============================================================================
const char* tlp_type_name(int fmt, int type) {
    if (type == 0x00) {
        if (fmt == 0 || fmt == 1) return "MRd";
        if (fmt == 2 || fmt == 3) return "MWr";
    }
    if (type == 0x0A) return "CplD";
    if (type == 0x00 && fmt == 0x0A) return "Cpl";
    return "???";
}

//=============================================================================
// PCIe Sniffer Functions
//=============================================================================
void pcie_clear(PCIe::BaseAddressRegister& bar) {
    bar.write64(PCIE_STATUS, CTRL_CLEAR);
}

void pcie_start(PCIe::BaseAddressRegister& bar) {
    bar.write64(PCIE_STATUS, CTRL_START);
}

void pcie_stop(PCIe::BaseAddressRegister& bar) {
    bar.write64(PCIE_STATUS, CTRL_STOP);
}

void pcie_dump_status(PCIe::BaseAddressRegister& bar) {
    uint64_t status = bar.read64(PCIE_STATUS);
    uint64_t write_ptr = bar.read64(PCIE_WRITE_PTR);
    uint64_t entry_count = bar.read64(PCIE_ENTRY_COUNT);
    uint64_t rx_count = bar.read64(PCIE_RX_COUNT);
    uint64_t tx_count = bar.read64(PCIE_TX_COUNT);
    uint64_t timestamp = bar.read64(PCIE_TIMESTAMP);

    printf("=== PCIe Sniffer Status ===\n");
    printf("  running:       %lu\n", status & 1);
    printf("  full:          %lu\n", (status >> 1) & 1);
    printf("  write_ptr:     %lu\n", write_ptr);
    printf("  entry_count:   %lu\n", entry_count);
    printf("  rx_count:      %lu\n", rx_count);
    printf("  tx_count:      %lu\n", tx_count);
    printf("  timestamp:     %lu\n", timestamp);
}

void pcie_dump_last(PCIe::BaseAddressRegister& bar) {
    printf("\nLast RX TLP:\n");
    uint64_t h0 = bar.read64(PCIE_LAST_RX);
    uint64_t h1 = bar.read64(PCIE_LAST_RX + 8);
    uint64_t d0 = bar.read64(PCIE_LAST_RX + 16);
    printf("  hdr:  %016lx %016lx\n", h0, h1);
    printf("  data: %016lx\n", d0);
    
    int fmt = (h0 >> 29) & 7;
    int type = (h0 >> 24) & 0x1F;
    printf("  type: %s (fmt=%d, type=0x%02x)\n", tlp_type_name(fmt, type), fmt, type);

    printf("\nLast TX TLP:\n");
    h0 = bar.read64(PCIE_LAST_TX);
    h1 = bar.read64(PCIE_LAST_TX + 8);
    d0 = bar.read64(PCIE_LAST_TX + 16);
    printf("  hdr:  %016lx %016lx\n", h0, h1);
    printf("  data: %016lx\n", d0);
    
    fmt = (h0 >> 29) & 7;
    type = (h0 >> 24) & 0x1F;
    printf("  type: %s (fmt=%d, type=0x%02x)\n", tlp_type_name(fmt, type), fmt, type);
}

void pcie_dump_trace(PCIe::BaseAddressRegister& bar, int count) {
    uint64_t entry_count = bar.read64(PCIE_ENTRY_COUNT);
    int to_dump = (count > 0 && (uint64_t)count < entry_count) ? count : entry_count;
    
    printf("\n=== PCIe Trace (%d entries) ===\n", to_dump);
    printf("  # | Dir | Timestamp  | Type | Header\n");
    printf("----+-----+------------+------+------------------------------------------\n");
    
    for (int i = 0; i < to_dump && i < PCIE_DEPTH; i++) {
        uint64_t base = PCIE_TRACE + i * PCIE_ENTRY_SIZE;
        uint64_t qw0 = bar.read64(base);       // hdr[63:0]
        uint64_t qw1 = bar.read64(base + 8);   // hdr[127:64]
        uint64_t qw6 = bar.read64(base + 48);  // timestamp + dir
        
        int dir = qw6 & 1;
        uint32_t ts = (qw6 >> 1) & 0xFFFFFFFF;
        
        int fmt = (qw0 >> 29) & 7;
        int type = (qw0 >> 24) & 0x1F;
        
        printf("%3d |  %s  | %10u | %s | %016lx %016lx\n",
               i, dir ? "TX" : "RX", ts, tlp_type_name(fmt, type), qw0, qw1);
    }
}

//=============================================================================
// AXI Sniffer Functions (shared for slave and master)
//=============================================================================
void axi_dump_status(PCIe::BaseAddressRegister& bar, uint32_t base, const char* name) {
    uint64_t status = bar.read64(base);
    uint64_t write_ptr = bar.read64(base + 0x008);
    uint64_t entry_count = bar.read64(base + 0x010);
    uint64_t aw_count = bar.read64(base + 0x018);
    uint64_t ar_count = bar.read64(base + 0x020);

    printf("=== %s Sniffer Status ===\n", name);
    printf("  running:       %lu\n", status & 1);
    printf("  full:          %lu\n", (status >> 1) & 1);
    printf("  write_ptr:     %lu\n", write_ptr);
    printf("  entry_count:   %lu\n", entry_count);
    printf("  aw_count:      %lu\n", aw_count);
    printf("  ar_count:      %lu\n", ar_count);
}

void axi_clear(PCIe::BaseAddressRegister& bar, uint32_t base) {
    bar.write64(base, CTRL_CLEAR);
}

void axi_start(PCIe::BaseAddressRegister& bar, uint32_t base) {
    bar.write64(base, CTRL_START);
}

void axi_stop(PCIe::BaseAddressRegister& bar, uint32_t base) {
    bar.write64(base, CTRL_STOP);
}

void axi_dump_trace(PCIe::BaseAddressRegister& bar, uint32_t base, int depth, int entry_size, const char* name, int count) {
    uint64_t entry_count = bar.read64(base + 0x010);
    int to_dump = (count > 0 && (uint64_t)count < entry_count) ? count : entry_count;
    
    printf("\n=== %s Trace (%d entries) ===\n", name, to_dump);
    printf("  # | Ch | Phase | Timestamp  | Address    | Data\n");
    printf("----+----+-------+------------+------------+------------------\n");
    
    uint32_t trace_base = base + 0x040;
    
    for (int i = 0; i < to_dump && i < depth; i++) {
        uint64_t addr_base = trace_base + i * entry_size;
        uint64_t qw0 = bar.read64(addr_base);        // addr
        uint64_t qw1 = bar.read64(addr_base + 8);    // data
        uint64_t qw2 = bar.read64(addr_base + 16);   // timestamp
        uint64_t qw3 = bar.read64(addr_base + 24);   // meta
        
        uint32_t addr = qw0 & 0xFFFFFFFF;
        uint32_t ts = qw2 & 0xFFFFFFFF;
        int ch = (qw3 >> 9) & 1;      // channel: 0=write, 1=read
        int phase = (qw3 >> 10) & 1;  // phase: 0=req, 1=resp
        
        printf("%3d |  %c |  %s   | %10u | 0x%08x | %016lx\n",
               i, ch ? 'R' : 'W', phase ? "Rsp" : "Req", ts, addr, qw1);
    }
}

//=============================================================================
// Combined Functions
//=============================================================================
void start_all(PCIe::BaseAddressRegister& bar) {
    pcie_start(bar);
    axi_start(bar, AXI_SLV_BASE);
    axi_start(bar, AXI_MST_BASE);
    printf("All 3 sniffers started.\n");
}

void stop_all(PCIe::BaseAddressRegister& bar) {
    pcie_stop(bar);
    axi_stop(bar, AXI_SLV_BASE);
    axi_stop(bar, AXI_MST_BASE);
    printf("All 3 sniffers stopped.\n");
}

void clear_all(PCIe::BaseAddressRegister& bar) {
    pcie_clear(bar);
    axi_clear(bar, AXI_SLV_BASE);
    axi_clear(bar, AXI_MST_BASE);
    printf("All 3 sniffers cleared (timestamp reset).\n");
}

void dump_all_status(PCIe::BaseAddressRegister& bar) {
    pcie_dump_status(bar);
    printf("\n");
    axi_dump_status(bar, AXI_SLV_BASE, "AXI Slave");
    printf("\n");
    axi_dump_status(bar, AXI_MST_BASE, "AXI Master");
}

//=============================================================================
// Test Functions
//=============================================================================
void test_rw(PCIe::BaseAddressRegister& bar) {
    printf("=== Test: BAR Write + Read ===\n\n");
    
    clear_all(bar);
    start_all(bar);
    
    printf("Writing 0xCAFEBABE to RAM[0x1000]...\n");
    bar.write64(0x1000, 0xCAFEBABE);
    
    printf("Reading RAM[0x1000]...\n");
    uint64_t val = bar.read64(0x1000);
    printf("  Got: 0x%lx\n\n", val);
    
    stop_all(bar);
    
    pcie_dump_status(bar);
    pcie_dump_last(bar);
    pcie_dump_trace(bar, 10);
}

void self_test(PCIe::BaseAddressRegister& bar) {
    printf("=== Self-Test ===\n\n");
    
    // Test RAM
    printf("1. RAM test:\n");
    bar.write64(0x1000, 0xDEADBEEF12345678ULL);
    uint64_t v = bar.read64(0x1000);
    printf("   Write 0xDEADBEEF12345678, read 0x%016lx %s\n\n", 
           v, v == 0xDEADBEEF12345678ULL ? "OK" : "FAIL");
    
    // Test sniffer control
    printf("2. Sniffer control test:\n");
    pcie_clear(bar);
    pcie_start(bar);
    uint64_t status = bar.read64(PCIE_STATUS);
    printf("   After start: running=%lu %s\n", status & 1, (status & 1) ? "OK" : "FAIL");
    
    pcie_stop(bar);
    status = bar.read64(PCIE_STATUS);
    printf("   After stop: running=%lu %s\n\n", status & 1, (status & 1) == 0 ? "OK" : "FAIL");
    
    // Test capture
    printf("3. Capture test:\n");
    pcie_clear(bar);
    pcie_start(bar);
    bar.read64(0x1000);  // Generate traffic
    bar.write64(0x1008, 0x1234);
    pcie_stop(bar);
    
    uint64_t rx_count = bar.read64(PCIE_RX_COUNT);
    uint64_t tx_count = bar.read64(PCIE_TX_COUNT);
    uint64_t entry_count = bar.read64(PCIE_ENTRY_COUNT);
    printf("   rx_count=%lu, tx_count=%lu, entry_count=%lu\n", rx_count, tx_count, entry_count);
    
    if (rx_count > 0 || tx_count > 0) {
        printf("   TLP counting: OK\n");
    } else {
        printf("   TLP counting: FAIL (no TLPs seen)\n");
    }
    
    if (entry_count > 0) {
        printf("   Trace capture: OK\n");
    } else {
        printf("   Trace capture: FAIL (buffer empty)\n");
    }
    
    printf("\n");
    pcie_dump_last(bar);
}

//=============================================================================
// Usage
//=============================================================================
void usage(const char* prog) {
    printf("Usage: %s <pcie_device> [command]\n\n", prog);
    printf("Commands:\n");
    printf("  status       Show all sniffer status (default)\n");
    printf("  start        Start all sniffers\n");
    printf("  stop         Stop all sniffers\n");
    printf("  clear        Clear all sniffers (resets timestamp)\n");
    printf("  pcie [n]     Dump PCIe trace (n entries)\n");
    printf("  axi [n]      Dump AXI slave trace\n");
    printf("  dma [n]      Dump AXI master (DMA) trace\n");
    printf("  last         Show last RX/TX TLPs\n");
    printf("  test         Run self-test\n");
    printf("  test_rw      Trace a BAR write+read\n");
    printf("\nExample: %s 0000:b1:00.0 test\n", prog);
}

//=============================================================================
// Main
//=============================================================================
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
    } else if (strcmp(cmd, "start") == 0) {
        start_all(bar);
    } else if (strcmp(cmd, "stop") == 0) {
        stop_all(bar);
    } else if (strcmp(cmd, "clear") == 0) {
        clear_all(bar);
    } else if (strcmp(cmd, "pcie") == 0) {
        pcie_dump_trace(bar, count);
    } else if (strcmp(cmd, "axi") == 0) {
        axi_dump_trace(bar, AXI_SLV_BASE, AXI_SLV_DEPTH, AXI_SLV_ENTRY_SIZE, "AXI Slave", count);
    } else if (strcmp(cmd, "dma") == 0) {
        axi_dump_trace(bar, AXI_MST_BASE, AXI_MST_DEPTH, AXI_MST_ENTRY_SIZE, "AXI Master", count);
    } else if (strcmp(cmd, "last") == 0) {
        pcie_dump_last(bar);
    } else if (strcmp(cmd, "test") == 0) {
        self_test(bar);
    } else if (strcmp(cmd, "test_rw") == 0) {
        test_rw(bar);
    } else {
        printf("Unknown command: %s\n", cmd);
        usage(argv[0]);
        return 1;
    }

    return 0;
}
