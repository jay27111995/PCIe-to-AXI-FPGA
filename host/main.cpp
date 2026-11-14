#include "pcie-util.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <x86intrin.h>

// DMA registers (0x0000 - 0x0FFF)
#define DMA_CTRL       0x00   // [0]=start, [1]=dir (0=H2C, 1=C2H), [2]=irq
#define DMA_STATUS     0x08   // [0]=busy, [1]=done
#define DMA_HOST_ADDR  0x10   // 64-bit host address
#define DMA_LOCAL_ADDR 0x18   // 32-bit local RAM address
#define DMA_LENGTH     0x20   // transfer length in bytes

// RAM (0x1000 - 0x1FFF)
#define RAM_BASE       0x1000

int main(int argc, char* argv[])
{
    if (argc < 2) { printf("Usage: %s <pcie_device> [iommu_group]\n", argv[0]); return 1; }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe-to-AXI Bridge Test ===\n\n");

    // Debug: Read various offsets to see what works
    printf("Debug reads:\n");
    printf("  [0x0000] = 0x%016lx (DMA ctrl)\n", bar.read64(0x0000));
    printf("  [0x0008] = 0x%016lx (DMA status)\n", bar.read64(0x0008));
    printf("  [0x1000] = 0x%016lx (RAM[0])\n", bar.read64(0x1000));
    printf("  [0x1008] = 0x%016lx (RAM[1])\n", bar.read64(0x1008));
    printf("\n");

    // Test 1: RAM write/read
    printf("Test 1: RAM write/read\n");
    bar.write64(RAM_BASE, 0xCAFEBABE12345678ULL);
    uint64_t val = bar.read64(RAM_BASE);
    if (val == 0xCAFEBABE12345678ULL) {
        printf("  PASS: wrote 0xCAFEBABE12345678, read 0x%016lx\n", val);
    } else {
        printf("  FAIL: wrote 0xCAFEBABE12345678, read 0x%016lx\n", val);
        return 1;
    }

    // Test 2: Multiple RAM addresses
    printf("\nTest 2: Multiple RAM addresses\n");
    for (int i = 0; i < 8; i++) {
        bar.write64(RAM_BASE + i*8, 0x1000 + i);
    }
    bool pass = true;
    for (int i = 0; i < 8; i++) {
        val = bar.read64(RAM_BASE + i*8);
        printf("  RAM[%d] = 0x%016lx %s\n", i, val, (val == 0x1000ULL + i) ? "OK" : "FAIL");
        if (val != 0x1000ULL + i) pass = false;
    }
    if (!pass) return 1;

    // Test 3: DMA C2H (FPGA -> Host)
    printf("\nTest 3: DMA C2H (RAM -> Host)\n");
    uint64_t* host_buf = (uint64_t*)pf.createDmaArea(4096, 0x100000);
    if (!host_buf) { printf("  FAIL: couldn't allocate DMA buffer\n"); return 1; }

    // Write test data to RAM
    bar.write64(RAM_BASE + 0x100, 0xAAAABBBBCCCCDDDDULL);
    
    // Clear host buffer
    host_buf[0] = 0;
    _mm_clflush(host_buf);
    _mm_mfence();

    // Setup DMA: RAM 0x1100 -> Host 0x100000, 8 bytes, C2H (dir=1)
    bar.write64(DMA_HOST_ADDR, 0x100000);
    bar.write64(DMA_LOCAL_ADDR, RAM_BASE + 0x100);
    bar.write64(DMA_LENGTH, 8);
    bar.write64(DMA_CTRL, 0x3);  // start=1, dir=1 (C2H)

    usleep(10000);  // Wait for DMA

    _mm_clflush(host_buf);
    _mm_mfence();

    if (host_buf[0] == 0xAAAABBBBCCCCDDDDULL) {
        printf("  PASS: DMA transferred 0x%016lx\n", host_buf[0]);
    } else {
        printf("  FAIL: expected 0xAAAABBBBCCCCDDDD, got 0x%016lx\n", host_buf[0]);
        printf("  DMA status: 0x%016lx\n", bar.read64(DMA_STATUS));
        return 1;
    }

    // Test 4: DMA H2C (Host -> FPGA)
    printf("\nTest 4: DMA H2C (Host -> RAM)\n");
    uint64_t* host_src = (uint64_t*)pf.createDmaArea(4096, 0x200000);
    if (!host_src) { printf("  FAIL: couldn't allocate DMA buffer\n"); return 1; }

    host_src[0] = 0xDEADBEEF12345678ULL;
    _mm_clflush(host_src);
    _mm_mfence();

    // Clear RAM destination
    bar.write64(RAM_BASE + 0x200, 0);

    // Setup DMA: Host 0x200000 -> RAM 0x1200, 8 bytes, H2C (dir=0)
    bar.write64(DMA_HOST_ADDR, 0x200000);
    bar.write64(DMA_LOCAL_ADDR, RAM_BASE + 0x200);
    bar.write64(DMA_LENGTH, 8);
    bar.write64(DMA_CTRL, 0x1);  // start=1, dir=0 (H2C)

    usleep(10000);  // Wait for DMA

    val = bar.read64(RAM_BASE + 0x200);
    if (val == 0xDEADBEEF12345678ULL) {
        printf("  PASS: DMA transferred 0x%016lx\n", val);
    } else {
        printf("  FAIL: expected 0xDEADBEEF12345678, got 0x%016lx\n", val);
        printf("  DMA status: 0x%016lx\n", bar.read64(DMA_STATUS));
        return 1;
    }

    printf("\n=== ALL TESTS PASSED ===\n");
    return 0;
}
