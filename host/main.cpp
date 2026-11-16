#include "pcie-util.h"
#include <cstdio>
#include <unistd.h>

// Memory map (BAR0)
#define RAM_BASE  0x1000  // 4KB RAM

// DMA registers
#define DMA_CTRL        0x00  // [0]=start, [1]=dir, [2]=irq_en
#define DMA_STATUS      0x08  // [0]=busy, [1]=done
#define DMA_HOST_ADDR   0x10  // 64-bit host address
#define DMA_LOCAL_ADDR  0x18  // 32-bit local (RAM) address  
#define DMA_LENGTH      0x20  // Transfer length

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pcie_device>\n", argv[0]);
        printf("Example: %s 0000:b4:00.0\n", argv[0]);
        return 1;
    }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe-to-AXI Bridge Test ===\n");
    printf("Device: %s\n\n", argv[1]);

    //=========================================================================
    // Test 1: RAM write/read
    //=========================================================================
    printf("Test 1: RAM write/read\n");
    uint64_t test_val = 0xCAFEBABE12345678ULL;
    bar.write64(RAM_BASE, test_val);
    uint64_t read_val = bar.read64(RAM_BASE);
    
    if (read_val == test_val) {
        printf("  [OK] PASS: 0x%016lx\n", read_val);
    } else {
        printf("  [X] FAIL: wrote 0x%016lx, read 0x%016lx\n", test_val, read_val);
        return 1;
    }

    //=========================================================================
    // Test 2: Multiple RAM locations
    //=========================================================================
    printf("\nTest 2: Multiple RAM addresses\n");
    bool pass = true;
    for (int i = 0; i < 8; i++) {
        bar.write64(RAM_BASE + i*8, 0xA000 + i);
    }
    for (int i = 0; i < 8; i++) {
        uint64_t val = bar.read64(RAM_BASE + i*8);
        bool ok = (val == 0xA000ULL + i);
        printf("  [0x%04x] = 0x%016lx %s\n", RAM_BASE + i*8, val, ok ? "[OK]" : "[X]");
        if (!ok) pass = false;
    }
    if (!pass) return 1;

    //=========================================================================
    // Test 3: DMA registers accessible
    //=========================================================================
    printf("\nTest 3: DMA register access\n");
    bar.write64(DMA_HOST_ADDR, 0x123456789ABCDEF0ULL);
    bar.write64(DMA_LOCAL_ADDR, 0x1234);
    bar.write64(DMA_LENGTH, 64);
    
    uint64_t host_addr = bar.read64(DMA_HOST_ADDR);
    uint64_t local_addr = bar.read64(DMA_LOCAL_ADDR);
    uint64_t length = bar.read64(DMA_LENGTH);
    
    if (host_addr == 0x123456789ABCDEF0ULL && 
        local_addr == 0x1234 && 
        length == 64) {
        printf("  [OK] PASS: host=0x%lx, local=0x%lx, len=%lu\n", 
               host_addr, local_addr, length);
    } else {
        printf("  [X] FAIL: register readback mismatch\n");
        return 1;
    }

    //=========================================================================
    // Test 4: DMA status
    //=========================================================================
    printf("\nTest 4: DMA status register\n");
    uint64_t status = bar.read64(DMA_STATUS);
    printf("  Status: 0x%016lx (busy=%lu, done=%lu)\n", 
           status, status & 1, (status >> 1) & 1);

    printf("\n=== ALL TESTS PASSED ===\n");
    printf("\nNote: Full DMA testing requires VFIO/IOMMU setup for host memory.\n");
    printf("See README.md for DMA test instructions.\n");
    return 0;
}

// Debug register dump (call with --debug flag)
void dump_debug_regs(PCIe::BaseAddressRegister& bar) {
    printf("\n=== Debug Register Dump (0x2000) ===\n");
    
    uint32_t status = bar.read32(0x2000);
    printf("  Status:      0x%08x\n", status);
    printf("    rx_seen:   %d\n", status & 1);
    printf("    tx_seen:   %d\n", (status >> 1) & 1);
    printf("    tx_state:  %d\n", (status >> 4) & 0xF);
    printf("    rx_type:   0x%02x\n", (status >> 8) & 0xFF);
    
    printf("  RX count:    %u\n", bar.read32(0x2004));
    printf("  TX count:    %u\n", bar.read32(0x2008));
    
    printf("\n  Last RX TLP header:\n");
    printf("    DW0: 0x%08x\n", bar.read32(0x2010));
    printf("    DW1: 0x%08x\n", bar.read32(0x2014));
    printf("    DW2: 0x%08x\n", bar.read32(0x2018));
    printf("    DW3: 0x%08x\n", bar.read32(0x201C));
    printf("  Last RX data: 0x%08x_%08x\n", bar.read32(0x2024), bar.read32(0x2020));
    
    printf("\n  Last TX TLP header:\n");
    printf("    DW0: 0x%08x\n", bar.read32(0x2028));
    printf("    DW1: 0x%08x\n", bar.read32(0x202C));
    printf("    DW2: 0x%08x\n", bar.read32(0x2030));
    printf("    DW3: 0x%08x\n", bar.read32(0x2034));
    printf("  Last TX data: 0x%08x_%08x\n", bar.read32(0x203C), bar.read32(0x2038));
    
    printf("\n  Cycle count: %u_%u\n", bar.read32(0x2044), bar.read32(0x2040));
    printf("  RX ready cycles: %u\n", bar.read32(0x2048));
    printf("  TX ready cycles: %u\n", bar.read32(0x204C));
}
