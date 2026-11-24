// Simple sniffer register debug - new memory map
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

    printf("=== Sniffer Debug (New Memory Map) ===\n\n");

    // Test RAM first (known working)
    printf("RAM test:\n");
    bar.write64(0x1000, 0xDEADBEEF12345678ULL);
    uint64_t ram_val = bar.read64(0x1000);
    printf("  0x1000: wrote 0xDEADBEEF12345678, read 0x%016lx %s\n", 
           ram_val, ram_val == 0xDEADBEEF12345678ULL ? "OK" : "FAIL");

    // PCIe Sniffer - new memory map
    printf("\nPCIe Sniffer (0x2000):\n");
    printf("  New map: 0x000=ctrl/status, 0x008=wr_ptr, 0x010=count, etc.\n\n");
    
    uint64_t v;
    
    v = bar.read64(0x2000);
    printf("  0x2000 (status):     0x%016lx (running=%lu, full=%lu)\n", v, v&1, (v>>1)&1);
    
    v = bar.read64(0x2008);
    printf("  0x2008 (write_ptr):  %lu\n", v);
    
    v = bar.read64(0x2010);
    printf("  0x2010 (entry_cnt):  %lu\n", v);
    
    v = bar.read64(0x2018);
    printf("  0x2018 (rx_count):   %lu\n", v);
    
    v = bar.read64(0x2020);
    printf("  0x2020 (tx_count):   %lu\n", v);
    
    v = bar.read64(0x2028);
    printf("  0x2028 (timestamp):  %lu\n", v);

    // Test start/stop/clear
    printf("\n--- Testing control ---\n");
    
    printf("Writing clear (0x4) to 0x2000...\n");
    bar.write64(0x2000, 0x4);
    v = bar.read64(0x2008);
    printf("  write_ptr after clear: %lu (expect 0)\n", v);
    
    printf("Writing start (0x1) to 0x2000...\n");
    bar.write64(0x2000, 0x1);
    v = bar.read64(0x2000);
    printf("  status after start: running=%lu (expect 1)\n", v & 1);
    
    // Trigger some activity by reading RAM
    bar.read64(0x1000);
    bar.read64(0x1008);
    
    printf("Writing stop (0x2) to 0x2000...\n");
    bar.write64(0x2000, 0x2);
    v = bar.read64(0x2000);
    printf("  status after stop: running=%lu (expect 0)\n", v & 1);
    
    // Check counters
    v = bar.read64(0x2010);
    printf("  entry_count: %lu\n", v);
    v = bar.read64(0x2018);
    printf("  rx_count: %lu\n", v);
    v = bar.read64(0x2020);
    printf("  tx_count: %lu\n", v);

    // Read last RX
    printf("\nLast RX TLP:\n");
    uint64_t hdr0 = bar.read64(0x2040);
    uint64_t hdr1 = bar.read64(0x2048);
    printf("  hdr: 0x%016lx 0x%016lx\n", hdr0, hdr1);

    // Read last TX
    printf("\nLast TX TLP:\n");
    hdr0 = bar.read64(0x2080);
    hdr1 = bar.read64(0x2088);
    printf("  hdr: 0x%016lx 0x%016lx\n", hdr0, hdr1);

    // AXI Slave Sniffer
    printf("\nAXI Slave Sniffer (0x3000):\n");
    v = bar.read64(0x3000);
    printf("  0x3000 (status):     0x%016lx (running=%lu, full=%lu)\n", v, v&1, (v>>1)&1);
    v = bar.read64(0x3008);
    printf("  0x3008 (write_ptr):  %lu\n", v);
    v = bar.read64(0x3010);
    printf("  0x3010 (entry_cnt):  %lu\n", v);

    // AXI Master Sniffer
    printf("\nAXI Master Sniffer (0x3800):\n");
    v = bar.read64(0x3800);
    printf("  0x3800 (status):     0x%016lx (running=%lu, full=%lu)\n", v, v&1, (v>>1)&1);
    v = bar.read64(0x3808);
    printf("  0x3808 (write_ptr):  %lu\n", v);
    v = bar.read64(0x3810);
    printf("  0x3810 (entry_cnt):  %lu\n", v);

    printf("\nDone.\n");
    return 0;
}
