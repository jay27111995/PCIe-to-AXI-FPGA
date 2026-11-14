#include "pcie-util.h"
#include <cstdio>

// Memory map
#define DMA_BASE  0x0000  // DMA registers
#define RAM_BASE  0x1000  // 4KB RAM

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pcie_device>\n", argv[0]);
        printf("Example: %s 0000:b4:00.0\n", argv[0]);
        return 1;
    }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe-to-AXI Bridge Test ===\n\n");

    // Test 1: RAM write/read
    printf("Test 1: RAM write/read at 0x%04x\n", RAM_BASE);
    uint64_t test_val = 0xCAFEBABE12345678ULL;
    bar.write64(RAM_BASE, test_val);
    uint64_t read_val = bar.read64(RAM_BASE);
    
    if (read_val == test_val) {
        printf("  PASS: 0x%016lx\n", read_val);
    } else {
        printf("  FAIL: wrote 0x%016lx, read 0x%016lx\n", test_val, read_val);
        return 1;
    }

    // Test 2: Multiple RAM locations
    printf("\nTest 2: Multiple RAM locations\n");
    bool pass = true;
    for (int i = 0; i < 8; i++) {
        bar.write64(RAM_BASE + i*8, 0xA000 + i);
    }
    for (int i = 0; i < 8; i++) {
        uint64_t val = bar.read64(RAM_BASE + i*8);
        bool ok = (val == 0xA000ULL + i);
        printf("  [0x%04x] = 0x%016lx %s\n", RAM_BASE + i*8, val, ok ? "OK" : "FAIL");
        if (!ok) pass = false;
    }
    if (!pass) return 1;

    // Test 3: DMA status register (should be readable)
    printf("\nTest 3: DMA registers\n");
    printf("  ctrl   [0x%02x] = 0x%016lx\n", 0x00, bar.read64(0x00));
    printf("  status [0x%02x] = 0x%016lx\n", 0x08, bar.read64(0x08));

    printf("\n=== PASSED ===\n");
    return 0;
}
