// Simple sniffer register debug
#include "pcie-util.h"
#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pcie_device>\n", argv[0]);
        return 1;
    }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== Raw Register Reads ===\n\n");

    // Test RAM first (known working)
    printf("RAM test:\n");
    bar.write64(0x1000, 0xDEADBEEF12345678ULL);
    uint64_t ram_val = bar.read64(0x1000);
    printf("  0x1000: wrote 0xDEADBEEF12345678, read 0x%016lx %s\n", 
           ram_val, ram_val == 0xDEADBEEF12345678ULL ? "OK" : "FAIL");

    // Now test sniffer registers with 64-bit reads
    printf("\nPCIe Sniffer (0x2000) - 64-bit reads:\n");
    for (uint32_t off = 0x2000; off <= 0x2020; off += 8) {
        uint64_t val = bar.read64(off);
        printf("  0x%04x: 0x%016lx (lo=0x%08x hi=0x%08x)\n", 
               off, val, (uint32_t)val, (uint32_t)(val >> 32));
    }

    // Try individual 32-bit aligned 64-bit reads
    printf("\nPCIe Sniffer - offset 0x2000:\n");
    uint64_t v = bar.read64(0x2000);
    printf("  status (0x2000): lo=0x%08x\n", (uint32_t)v);
    printf("  control(0x2004): hi=0x%08x (write-only, expect 0)\n", (uint32_t)(v >> 32));

    v = bar.read64(0x2008);
    printf("  mode   (0x2008): lo=0x%08x\n", (uint32_t)v);
    printf("  trigger(0x200C): hi=0x%08x\n", (uint32_t)(v >> 32));

    v = bar.read64(0x2010);
    printf("  wr_ptr (0x2010): lo=0x%08x (expect <256)\n", (uint32_t)v);
    printf("  entries(0x2014): hi=0x%08x (expect <256)\n", (uint32_t)(v >> 32));

    v = bar.read64(0x2018);
    printf("  rx_cnt (0x2018): lo=0x%08x\n", (uint32_t)v);
    printf("  tx_cnt (0x201C): hi=0x%08x\n", (uint32_t)(v >> 32));

    // Start sniffer and do one write, then check again
    printf("\n--- Starting sniffer, doing one RAM write ---\n");
    bar.write64(0x2004, 0x4);  // clear
    bar.write64(0x2004, 0x1);  // start
    bar.write64(0x1008, 0xABCD);  // trigger some activity
    bar.write64(0x2004, 0x2);  // stop

    printf("\nAfter activity:\n");
    v = bar.read64(0x2000);
    printf("  status (0x2000): 0x%08x\n", (uint32_t)v);
    
    v = bar.read64(0x2010);
    printf("  wr_ptr (0x2010): %u\n", (uint32_t)v);
    printf("  entries(0x2014): %u\n", (uint32_t)(v >> 32));

    v = bar.read64(0x2018);
    printf("  rx_cnt (0x2018): %u\n", (uint32_t)v);
    printf("  tx_cnt (0x201C): %u\n", (uint32_t)(v >> 32));

    // AXI sniffer
    printf("\nAXI Slave Sniffer (0x3000):\n");
    v = bar.read64(0x3000);
    printf("  status (0x3000): 0x%08x\n", (uint32_t)v);
    
    v = bar.read64(0x3008);
    printf("  wr_ptr (0x3008): %u\n", (uint32_t)v);
    printf("  entries(0x300C): %u\n", (uint32_t)(v >> 32));

    printf("\nDone.\n");
    return 0;
}
