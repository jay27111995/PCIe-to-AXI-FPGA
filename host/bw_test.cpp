//=============================================================================
// PCIe Bandwidth Test Tool
// Measures DMA throughput between host memory and FPGA
//=============================================================================
#include "pcie-util.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// DMA registers
#define DMA_CTRL        0x00  // [0]=start, [1]=dir (0=H2C, 1=C2H), [2]=irq_en
#define DMA_STATUS      0x08  // [0]=busy, [1]=done
#define DMA_HOST_ADDR   0x10  // 64-bit host address
#define DMA_LOCAL_ADDR  0x18  // 32-bit local (RAM) address
#define DMA_LENGTH      0x20  // Transfer length in bytes

// Memory map
#define RAM_BASE        0x1000
#define RAM_SIZE        4096

//=============================================================================
// Wait for DMA to complete, return cycles waited
//=============================================================================
int wait_dma_done(PCIe::BaseAddressRegister& bar, int timeout_us = 1000000) {
    int cycles = 0;
    while (cycles < timeout_us) {
        uint64_t status = bar.read64(DMA_STATUS);
        if (status & 2) return cycles;  // done bit
        cycles++;
    }
    return -1;  // timeout
}

//=============================================================================
// Run DMA transfer and measure time
//=============================================================================
double run_dma_transfer(PCIe::BaseAddressRegister& bar, uint64_t host_addr,
                        uint32_t local_addr, uint32_t length, bool h2c) {
    // Setup DMA
    bar.write64(DMA_HOST_ADDR, host_addr);
    bar.write64(DMA_LOCAL_ADDR, local_addr);
    bar.write64(DMA_LENGTH, length);

    auto start = std::chrono::high_resolution_clock::now();

    // Start DMA: bit 0 = start, bit 1 = direction (0=H2C, 1=C2H)
    uint64_t ctrl = 1 | (h2c ? 0 : 2);
    bar.write64(DMA_CTRL, ctrl);

    // Wait for completion
    int result = wait_dma_done(bar);

    auto end = std::chrono::high_resolution_clock::now();

    if (result < 0) {
        printf("  DMA timeout!\n");
        return -1.0;
    }

    // Clear done by writing 0 to ctrl
    bar.write64(DMA_CTRL, 0);

    std::chrono::duration<double, std::micro> elapsed = end - start;
    return elapsed.count();
}

//=============================================================================
// Bandwidth test: multiple iterations, report statistics
//=============================================================================
void bandwidth_test(PCIe::BaseAddressRegister& bar, void* host_buf,
                    uint64_t host_iova, uint32_t size, int iterations,
                    bool h2c) {
    const char* dir_str = h2c ? "H2C (Host -> FPGA)" : "C2H (FPGA -> Host)";
    printf("\n=== %s Bandwidth Test ===\n", dir_str);
    printf("Transfer size: %u bytes, Iterations: %d\n\n", size, iterations);

    // Initialize host buffer for H2C
    if (h2c) {
        memset(host_buf, 0xAB, size);
    } else {
        // For C2H, initialize RAM with test pattern
        for (uint32_t i = 0; i < size && i < RAM_SIZE; i += 8) {
            bar.write64(RAM_BASE + i, 0xDEADBEEF00000000ULL | i);
        }
    }

    double total_time = 0;
    double min_time = 1e9;
    double max_time = 0;

    for (int i = 0; i < iterations; i++) {
        double time_us = run_dma_transfer(bar, host_iova, RAM_BASE, size, h2c);
        if (time_us < 0) {
            printf("Transfer %d failed!\n", i);
            return;
        }

        total_time += time_us;
        if (time_us < min_time) min_time = time_us;
        if (time_us > max_time) max_time = time_us;

        if (iterations <= 10) {
            double bw = (size / time_us);  // MB/s (bytes/us = MB/s)
            printf("  [%d] Time: %.2f us, BW: %.2f MB/s\n", i, time_us, bw);
        }
    }

    double avg_time = total_time / iterations;
    double avg_bw = (size / avg_time);  // MB/s
    double max_bw = (size / min_time);
    double min_bw = (size / max_time);

    printf("\nResults:\n");
    printf("  Avg time:  %.2f us\n", avg_time);
    printf("  Min time:  %.2f us (best)\n", min_time);
    printf("  Max time:  %.2f us (worst)\n", max_time);
    printf("  Avg BW:    %.2f MB/s\n", avg_bw);
    printf("  Peak BW:   %.2f MB/s\n", max_bw);
    printf("  Min BW:    %.2f MB/s\n", min_bw);

    // Compare to theoretical max
    // PCIe Gen5 x16 = ~64 GB/s = 64000 MB/s (but we have small transfers)
    printf("\n  (For reference: PCIe Gen5 x16 theoretical max ~64 GB/s)\n");
}

//=============================================================================
// Latency test: small transfers to measure round-trip time
//=============================================================================
void latency_test(PCIe::BaseAddressRegister& bar, void* host_buf,
                  uint64_t host_iova, int iterations) {
    printf("\n=== Latency Test (8-byte transfers) ===\n");
    printf("Iterations: %d\n\n", iterations);

    double total_time = 0;
    double min_time = 1e9;
    double max_time = 0;

    for (int i = 0; i < iterations; i++) {
        // H2C: write 8 bytes
        double time_us = run_dma_transfer(bar, host_iova, RAM_BASE, 8, true);
        if (time_us < 0) return;

        total_time += time_us;
        if (time_us < min_time) min_time = time_us;
        if (time_us > max_time) max_time = time_us;
    }

    double avg_time = total_time / iterations;

    printf("Results:\n");
    printf("  Avg latency:  %.2f us\n", avg_time);
    printf("  Min latency:  %.2f us\n", min_time);
    printf("  Max latency:  %.2f us\n", max_time);
}

//=============================================================================
// BAR access bandwidth test (MMIO, not DMA)
//=============================================================================
void bar_bandwidth_test(PCIe::BaseAddressRegister& bar, int iterations) {
    printf("\n=== BAR Access Bandwidth Test (MMIO) ===\n");
    printf("Iterations: %d\n\n", iterations);

    // Write test
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        bar.write64(RAM_BASE, 0xCAFEBABE12345678ULL);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> write_time = end - start;

    // Read test
    start = std::chrono::high_resolution_clock::now();
    volatile uint64_t val;
    for (int i = 0; i < iterations; i++) {
        val = bar.read64(RAM_BASE);
    }
    (void)val;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> read_time = end - start;

    printf("Write (posted):\n");
    printf("  Total time: %.2f us for %d writes\n", write_time.count(), iterations);
    printf("  Per write:  %.3f us\n", write_time.count() / iterations);
    printf("  Throughput: %.2f M writes/s\n", iterations / write_time.count());

    printf("\nRead (non-posted):\n");
    printf("  Total time: %.2f us for %d reads\n", read_time.count(), iterations);
    printf("  Per read:   %.3f us\n", read_time.count() / iterations);
    printf("  Throughput: %.2f M reads/s\n", iterations / read_time.count());
}

//=============================================================================
// Verify data integrity
//=============================================================================
bool verify_transfer(PCIe::BaseAddressRegister& bar, void* host_buf,
                     uint64_t host_iova, uint32_t size, bool h2c) {
    uint8_t* buf = (uint8_t*)host_buf;

    if (h2c) {
        // Fill host buffer with pattern
        for (uint32_t i = 0; i < size; i++) {
            buf[i] = (uint8_t)(i & 0xFF);
        }

        // DMA to FPGA
        double time = run_dma_transfer(bar, host_iova, RAM_BASE, size, true);
        if (time < 0) return false;

        // Read back from RAM and verify
        bool ok = true;
        for (uint32_t i = 0; i < size && i < RAM_SIZE; i += 8) {
            uint64_t expected = 0;
            for (int j = 0; j < 8 && (i+j) < size; j++) {
                expected |= ((uint64_t)((i+j) & 0xFF)) << (j*8);
            }
            uint64_t actual = bar.read64(RAM_BASE + i);
            if (actual != expected) {
                printf("  Mismatch at 0x%04x: expected 0x%016lx, got 0x%016lx\n",
                       i, expected, actual);
                ok = false;
            }
        }
        return ok;
    } else {
        // Fill RAM with pattern
        for (uint32_t i = 0; i < size && i < RAM_SIZE; i += 8) {
            uint64_t val = 0;
            for (int j = 0; j < 8 && (i+j) < size; j++) {
                val |= ((uint64_t)((i+j) & 0xFF)) << (j*8);
            }
            bar.write64(RAM_BASE + i, val);
        }

        // Clear host buffer
        memset(buf, 0, size);

        // DMA to host
        double time = run_dma_transfer(bar, host_iova, RAM_BASE, size, false);
        if (time < 0) return false;

        // Verify host buffer
        bool ok = true;
        for (uint32_t i = 0; i < size; i++) {
            uint8_t expected = (uint8_t)(i & 0xFF);
            if (buf[i] != expected) {
                printf("  Mismatch at byte %u: expected 0x%02x, got 0x%02x\n",
                       i, expected, buf[i]);
                ok = false;
            }
        }
        return ok;
    }
}

//=============================================================================
// Usage
//=============================================================================
void usage(const char* prog) {
    printf("Usage: %s <pcie_device> [command] [options]\n\n", prog);
    printf("Commands:\n");
    printf("  all          Run all tests (default)\n");
    printf("  h2c [size] [iter]   Host-to-Card bandwidth test\n");
    printf("  c2h [size] [iter]   Card-to-Host bandwidth test\n");
    printf("  latency [iter]      Latency test (small transfers)\n");
    printf("  bar [iter]          BAR MMIO bandwidth test\n");
    printf("  verify [size]       Data integrity test\n");
    printf("\nDefaults: size=256, iterations=100\n");
    printf("Max size: %d bytes (RAM size)\n", RAM_SIZE);
    printf("\nExample: %s 0000:b1:00.0 h2c 1024 1000\n", prog);
}

//=============================================================================
// Main
//=============================================================================
int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    const char* device = argv[1];
    const char* cmd = (argc > 2) ? argv[2] : "all";
    int size = (argc > 3) ? atoi(argv[3]) : 256;
    int iterations = (argc > 4) ? atoi(argv[4]) : 100;

    if (size > RAM_SIZE) {
        printf("Size %d exceeds RAM size %d, clamping.\n", size, RAM_SIZE);
        size = RAM_SIZE;
    }

    PCIe::Function pf(device);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe Bandwidth Test ===\n");
    printf("Device: %s\n", device);

    // Allocate DMA-able host memory
    // Use a fixed IOVA that won't conflict with anything
    uint64_t iova = 0x100000000ULL;  // 4GB mark
    void* host_buf = pf.createDmaArea(RAM_SIZE, iova);
    printf("DMA buffer: vaddr=%p, iova=0x%lx, size=%d\n", host_buf, iova, RAM_SIZE);

    if (strcmp(cmd, "h2c") == 0) {
        bandwidth_test(bar, host_buf, iova, size, iterations, true);
    } else if (strcmp(cmd, "c2h") == 0) {
        bandwidth_test(bar, host_buf, iova, size, iterations, false);
    } else if (strcmp(cmd, "latency") == 0) {
        latency_test(bar, host_buf, iova, iterations);
    } else if (strcmp(cmd, "bar") == 0) {
        bar_bandwidth_test(bar, iterations);
    } else if (strcmp(cmd, "verify") == 0) {
        printf("\n=== Data Integrity Test ===\n");
        printf("H2C verify (%d bytes): %s\n", size,
               verify_transfer(bar, host_buf, iova, size, true) ? "PASS" : "FAIL");
        printf("C2H verify (%d bytes): %s\n", size,
               verify_transfer(bar, host_buf, iova, size, false) ? "PASS" : "FAIL");
    } else if (strcmp(cmd, "all") == 0) {
        // Quick verification first
        printf("\n--- Verifying data integrity ---\n");
        bool h2c_ok = verify_transfer(bar, host_buf, iova, 64, true);
        bool c2h_ok = verify_transfer(bar, host_buf, iova, 64, false);
        printf("H2C: %s, C2H: %s\n", h2c_ok ? "OK" : "FAIL", c2h_ok ? "OK" : "FAIL");

        if (!h2c_ok || !c2h_ok) {
            printf("\nData integrity check failed, skipping bandwidth tests.\n");
            return 1;
        }

        // BAR bandwidth
        bar_bandwidth_test(bar, 10000);

        // DMA bandwidth
        bandwidth_test(bar, host_buf, iova, 256, 100, true);
        bandwidth_test(bar, host_buf, iova, 256, 100, false);

        // Larger transfers
        bandwidth_test(bar, host_buf, iova, RAM_SIZE, 100, true);
        bandwidth_test(bar, host_buf, iova, RAM_SIZE, 100, false);

        // Latency
        latency_test(bar, host_buf, iova, 100);
    } else {
        printf("Unknown command: %s\n", cmd);
        usage(argv[0]);
        return 1;
    }

    printf("\nDone.\n");
    return 0;
}
