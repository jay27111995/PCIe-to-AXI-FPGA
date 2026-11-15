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
        printf("  ✓ PASS: 0x%016lx\n", read_val);
    } else {
        printf("  ✗ FAIL: wrote 0x%016lx, read 0x%016lx\n", test_val, read_val);
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
        printf("  [0x%04x] = 0x%016lx %s\n", RAM_BASE + i*8, val, ok ? "✓" : "✗");
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
        printf("  ✓ PASS: host=0x%lx, local=0x%lx, len=%lu\n", 
               host_addr, local_addr, length);
    } else {
        printf("  ✗ FAIL: register readback mismatch\n");
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
