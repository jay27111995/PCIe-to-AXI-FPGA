// PCIe-to-AXI Bridge Test Program
// Tests BAR access and DMA operations on the FPGA bridge.
//
// Usage: sudo ./test_bridge <pci_addr> <iommu_group>
// Example: sudo ./test_bridge 0000:b1:00.0 12

#include "pcie_vfio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/vfio.h>
#include <sys/ioctl.h>

// Memory map (BAR0)
#define REG_BASE    0x0000  // Control registers
#define DMA_BASE    0x1000  // DMA engine
#define RAM_BASE    0x2000  // Local RAM (4KB)

// Control registers
#define REG_SCRATCH     (REG_BASE + 0x00)
#define REG_WRITE_CNT   (REG_BASE + 0x08)

// DMA registers
#define DMA_CTRL        (DMA_BASE + 0x00)
#define DMA_STATUS      (DMA_BASE + 0x08)
#define DMA_HOST_LO     (DMA_BASE + 0x10)
#define DMA_HOST_HI     (DMA_BASE + 0x18)
#define DMA_LOCAL       (DMA_BASE + 0x20)
#define DMA_LENGTH      (DMA_BASE + 0x28)

// DMA control bits
#define DMA_START       (1 << 0)
#define DMA_DIR_C2H     (1 << 1)  // 0=H2C (host→card), 1=C2H (card→host)
#define DMA_IRQ_EN      (1 << 2)

// DMA status bits
#define DMA_BUSY        (1 << 0)
#define DMA_DONE        (1 << 1)
#define DMA_ERROR       (1 << 2)

// Global for DMA buffer
static void *dma_buf = NULL;
static uint64_t dma_iova = 0;
static int container_fd_global = -1;

// Forward declarations
static int dma_alloc(size_t size);
static void dma_free(void);

// ----------------------------------------------------------------------------
// Test Functions
// ----------------------------------------------------------------------------

static int test_scratch_reg(void) {
    printf("\n=== Test 1: Scratch Register ===\n");
    
    uint64_t test_val = 0xCAFEBABE12345678ULL;
    write64(REG_SCRATCH, test_val);
    uint64_t read_val = read64(REG_SCRATCH);
    
    printf("  Write: 0x%016lx\n", test_val);
    printf("  Read:  0x%016lx\n", read_val);
    
    if (read_val == test_val) {
        printf("  ✓ PASS\n");
        return 0;
    } else {
        printf("  ✗ FAIL\n");
        return 1;
    }
}

static int test_ram(void) {
    printf("\n=== Test 2: RAM Write/Read ===\n");
    
    // Write pattern
    uint64_t pattern = 0x1111222233334444ULL;
    write64(RAM_BASE, pattern);
    
    // Read back
    uint64_t read_val = read64(RAM_BASE);
    
    printf("  Write: 0x%016lx @ 0x%04x\n", pattern, RAM_BASE);
    printf("  Read:  0x%016lx\n", read_val);
    
    if (read_val == pattern) {
        printf("  ✓ PASS\n");
        return 0;
    } else {
        printf("  ✗ FAIL\n");
        return 1;
    }
}

static int test_ram_pattern(void) {
    printf("\n=== Test 3: RAM Pattern Test ===\n");
    
    int errors = 0;
    
    // Write incrementing pattern
    for (int i = 0; i < 64; i++) {
        uint64_t val = 0xDEAD000000000000ULL | (i << 8) | i;
        write64(RAM_BASE + i * 8, val);
    }
    
    // Read back and verify
    for (int i = 0; i < 64; i++) {
        uint64_t expected = 0xDEAD000000000000ULL | (i << 8) | i;
        uint64_t actual = read64(RAM_BASE + i * 8);
        if (actual != expected) {
            if (errors < 5) {
                printf("  Error @ 0x%04x: expected 0x%016lx, got 0x%016lx\n",
                       RAM_BASE + i * 8, expected, actual);
            }
            errors++;
        }
    }
    
    printf("  %d/64 words verified\n", 64 - errors);
    if (errors == 0) {
        printf("  ✓ PASS\n");
        return 0;
    } else {
        printf("  ✗ FAIL (%d errors)\n", errors);
        return 1;
    }
}

// Note: DMA requires IOMMU mapping which needs the container fd
// For now, we just test the register interface
static int test_dma_regs(void) {
    printf("\n=== Test 4: DMA Register Access ===\n");
    
    // Read status (should not be busy initially)
    uint64_t status = read64(DMA_STATUS);
    printf("  DMA status: 0x%016lx\n", status);
    
    // Write and read back DMA registers
    write64(DMA_HOST_LO, 0x80000000);
    write64(DMA_HOST_HI, 0x00000000);
    write64(DMA_LOCAL, 0x2000);
    write64(DMA_LENGTH, 64);
    
    uint64_t host_lo = read64(DMA_HOST_LO);
    uint64_t local = read64(DMA_LOCAL);
    uint64_t length = read64(DMA_LENGTH);
    
    printf("  host_lo: 0x%016lx (expect 0x80000000)\n", host_lo);
    printf("  local:   0x%016lx (expect 0x2000)\n", local);
    printf("  length:  0x%016lx (expect 0x40)\n", length);
    
    if (host_lo == 0x80000000 && local == 0x2000 && length == 64) {
        printf("  ✓ PASS\n");
        return 0;
    } else {
        printf("  ✗ FAIL\n");
        return 1;
    }
}

// ----------------------------------------------------------------------------
// DMA Buffer Allocation (requires IOMMU mapping)
// ----------------------------------------------------------------------------

// Get container fd - need to expose this from pcie_vfio.c or pass it
extern int vfio_get_container_fd(void);

static int dma_alloc(size_t size) {
    // Allocate page-aligned buffer
    dma_buf = mmap(NULL, size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    
    // Fall back to regular pages if huge pages not available
    if (dma_buf == MAP_FAILED) {
        dma_buf = mmap(NULL, size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }
    
    if (dma_buf == MAP_FAILED) {
        perror("Failed to allocate DMA buffer");
        return -1;
    }
    
    // For real DMA, we'd need to:
    // 1. Get the physical address (or use VFIO DMA mapping)
    // 2. Map it into the IOMMU
    // This requires VFIO_IOMMU_MAP_DMA ioctl
    
    printf("DMA buffer allocated at %p (size %zu)\n", dma_buf, size);
    return 0;
}

static void dma_free(void) {
    if (dma_buf && dma_buf != MAP_FAILED) {
        // Would need to unmap from IOMMU first
        munmap(dma_buf, 4096);  // Assuming 4K
        dma_buf = NULL;
    }
}

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s <pci_addr> <iommu_group>\n", prog);
    fprintf(stderr, "Example: %s 0000:b1:00.0 12\n", prog);
    fprintf(stderr, "\nSetup:\n");
    fprintf(stderr, "  1. Find device: lspci | grep -i fpga\n");
    fprintf(stderr, "  2. Bind to VFIO:\n");
    fprintf(stderr, "     PCI=0000:b1:00.0\n");
    fprintf(stderr, "     echo $PCI > /sys/bus/pci/devices/$PCI/driver/unbind\n");
    fprintf(stderr, "     echo vfio-pci > /sys/bus/pci/devices/$PCI/driver_override\n");
    fprintf(stderr, "     echo $PCI > /sys/bus/pci/drivers/vfio-pci/bind\n");
    fprintf(stderr, "  3. Find IOMMU group:\n");
    fprintf(stderr, "     GRP=$(basename $(readlink /sys/bus/pci/devices/$PCI/iommu_group))\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    const char *pci_addr = argv[1];
    int iommu_group = atoi(argv[2]);

    printf("=== PCIe-to-AXI Bridge Test ===\n");
    printf("PCI: %s, IOMMU Group: %d\n", pci_addr, iommu_group);

    // Initialize VFIO
    if (vfio_init(pci_addr, iommu_group) < 0) {
        fprintf(stderr, "Failed to initialize VFIO\n");
        return 1;
    }

    printf("BAR0 size: %zu bytes\n", vfio_get_bar_size());

    // Run tests
    int failures = 0;
    failures += test_scratch_reg();
    failures += test_ram();
    failures += test_ram_pattern();
    failures += test_dma_regs();

    printf("\n=== Results: %d tests failed ===\n", failures);

    vfio_cleanup();
    return failures > 0 ? 1 : 0;
}
