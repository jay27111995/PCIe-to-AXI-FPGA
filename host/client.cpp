#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cerrno>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/vfio.h>
#include <unistd.h>
#include <x86intrin.h>

#define SOCK_PATH "/tmp/pcie_server.sock"

#define REG_RESET    0x00
#define REG_SRC_ADDR 0x08
#define REG_DST_ADDR 0x10
#define REG_LEN      0x18
#define REG_CTRL     0x20

static void recv_fds(int sock, char* device_bdf, uint64_t* bar_offset, uint64_t* dma_iova, uint64_t* dma_size,
                     int* group_fd, int* container_fd, int* dma_fd) {
    struct {
        char device_bdf[16];
        uint64_t bar_offset;
        uint64_t dma_iova;
        uint64_t dma_size;
    } info;
    read(sock, &info, sizeof(info));
    strncpy(device_bdf, info.device_bdf, 16);
    *bar_offset = info.bar_offset;
    *dma_iova = info.dma_iova;
    *dma_size = info.dma_size;

    char buf[CMSG_SPACE(3 * sizeof(int))];
    char dummy;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    recvmsg(sock, &msg, 0);
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    int* fds = (int*)CMSG_DATA(cmsg);
    *group_fd = fds[0];
    *container_fd = fds[1];
    *dma_fd = fds[2];
}

static uint64_t find_free_addr(uint64_t size) {
    FILE* f = fopen("/proc/self/maps", "r");
    if (!f) {
        perror("fopen /proc/self/maps");
        return 0;
    }

    uint64_t prev_end = 0x100000000ULL;  // start searching from 4GB
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        unsigned long start, end;
        if (sscanf(line, "%lx-%lx", &start, &end) == 2) {
            if ((uint64_t)start >= prev_end + size) {
                fclose(f);
                return prev_end;  // found gap
            }
            if ((uint64_t)end > prev_end) prev_end = end;
        }
    }
    fclose(f);
    return prev_end;  // use after last mapping
}

static void* create_dma(int container_fd, uint64_t size, uint64_t* out_iova) {
    uint64_t addr = find_free_addr(size);
    if (addr == 0) return NULL;

    for (int i = 0; i < 256; i++) {
        void* p = mmap((void*)addr, size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
        if (p == MAP_FAILED) {
            addr += 0x1000;
            continue;
        }

        struct vfio_iommu_type1_dma_map dma_map = {
            .argsz = sizeof(dma_map),
            .flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE,
            .vaddr = (uint64_t)p,
            .iova = (uint64_t)p,
            .size = size
        };

        if (ioctl(container_fd, VFIO_IOMMU_MAP_DMA, &dma_map) == 0) {
            *out_iova = (uint64_t)p;
            return p;
        }

        munmap(p, size);
        if (errno != EEXIST) {
            perror("VFIO_IOMMU_MAP_DMA");
            return NULL;
        }
        addr += 0x1000;
    }

    fprintf(stderr, "Failed to find free VA/IOVA\n");
    return NULL;
}

int main(int argc, char* argv[]) {
    uint64_t sram_page = 0x1000;   // Default SRAM page offset
    if (argc > 1) sram_page = strtoull(argv[1], NULL, 0);

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); return 1;
    }

    char device_bdf[16];
    uint64_t bar_offset, shared_dma_iova, shared_dma_size;
    int group_fd, container_fd, dma_fd;
    recv_fds(sock, device_bdf, &bar_offset, &shared_dma_iova, &shared_dma_size, &group_fd, &container_fd, &dma_fd);
    close(sock);

    // Get device FD from group FD
    int dev_fd = ioctl(group_fd, VFIO_GROUP_GET_DEVICE_FD, device_bdf);
    if (dev_fd < 0) {
        perror("VFIO_GROUP_GET_DEVICE_FD");
        return 1;
    }

    printf("[Client] group_fd=%d dev_fd=%d container_fd=%d dma_fd=%d device=%s\n",
           group_fd, dev_fd, container_fd, dma_fd, device_bdf);
    printf("[Client] BAR offset=0x%lx, Shared DMA: iova=0x%lx size=0x%lx\n",
           bar_offset, shared_dma_iova, shared_dma_size);

    // Map shared DMA at fixed address (VA == IOVA)
    void* shared_dma = mmap((void*)shared_dma_iova, shared_dma_size, PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_FIXED_NOREPLACE, dma_fd, 0);
    if (shared_dma == MAP_FAILED) {
        perror("mmap shared DMA");
        return 1;
    }
    printf("[Client] Shared DMA mapped: va=%p\n", shared_dma);

    // Map BAR - only map 4KB page
    volatile uint64_t* bar = (volatile uint64_t*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                                                       MAP_SHARED, dev_fd, bar_offset + sram_page);
    if (bar == MAP_FAILED) {
        perror("mmap BAR");
        return 1;
    }
    printf("[Client] BAR mapped: va=%p (page at BAR+0x%lx)\n", bar, sram_page);

    // Also map register page separately
    volatile uint64_t* regs = (volatile uint64_t*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                                                        MAP_SHARED, dev_fd, bar_offset);
    if (regs == MAP_FAILED) {
        perror("mmap regs");
        return 1;
    }
    printf("[Client] Regs mapped: va=%p (page at BAR+0x0)\n", regs);

    // Create DMA areas using container FD
    uint64_t src_iova, dst_iova;
    uint64_t* src = (uint64_t*)create_dma(container_fd, 4096, &src_iova);
    uint64_t* dst = (uint64_t*)create_dma(container_fd, 4096, &dst_iova);
    assert(src && "create_dma src failed");
    assert(dst && "create_dma dst failed");
    printf("[Client] DMA src: va=%p iova=0x%lx\n", src, src_iova);
    printf("[Client] DMA dst: va=%p iova=0x%lx\n", dst, dst_iova);

    // Test: write to SRAM via BAR
    uint64_t sram_pattern = 0xBBBB000000000000ULL | (sram_page & 0xFFFF);
    bar[0] = sram_pattern;
    uint64_t readback = bar[0];
    printf("[Client] Wrote SRAM[0]=%016lx, read back=%016lx\n", sram_pattern, readback);
    assert(readback == sram_pattern && "SRAM write/read mismatch");

    // Reset and test DMA
    regs[REG_RESET/8] = 1;
    usleep(1000);

    src[0] = 0xCAFEF00D00000000ULL | (sram_page & 0xFFFF);
    dst[0] = 0;
    _mm_clflush(src); _mm_clflush(dst); _mm_mfence();

    printf("[Client] src[0]=%016lx\n", src[0]);

    regs[REG_SRC_ADDR/8] = src_iova;
    regs[REG_DST_ADDR/8] = dst_iova;
    regs[REG_LEN/8] = 1;
    regs[REG_CTRL/8] = 1;
    usleep(10000);

    _mm_clflush(dst); _mm_mfence();

    printf("[Client] dst[0]=%016lx\n", dst[0]);
    assert(dst[0] == src[0] && "Private DMA transfer failed");

    printf("[Client] Private DMA PASS\n");

    // Test 2: Shared DMA - use offset based on sram_page to avoid conflicts
    uint64_t offset = (sram_page / 0x1000) * 0x2000;  // 0x1000->0x2000, 0x2000->0x4000, etc.
    uint64_t* shared_src = (uint64_t*)((char*)shared_dma + offset);
    uint64_t* shared_dst = (uint64_t*)((char*)shared_dma + offset + 0x1000);
    uint64_t shared_src_iova = shared_dma_iova + offset;
    uint64_t shared_dst_iova = shared_dma_iova + offset + 0x1000;

    printf("[Client] Shared DMA test: src_iova=0x%lx dst_iova=0x%lx\n", shared_src_iova, shared_dst_iova);

    regs[REG_RESET/8] = 1;
    usleep(1000);

    memset(shared_src, 0, 0x1000);
    memset(shared_dst, 0, 0x1000);
    shared_src[0] = 0xDEADBEEF00000000ULL | (sram_page & 0xFFFF);
    _mm_clflush(shared_src); _mm_clflush(shared_dst); _mm_mfence();

    printf("[Client] shared_src[0]=%016lx\n", shared_src[0]);

    regs[REG_SRC_ADDR/8] = shared_src_iova;
    regs[REG_DST_ADDR/8] = shared_dst_iova;
    regs[REG_LEN/8] = 1;
    regs[REG_CTRL/8] = 1;
    usleep(10000);

    _mm_clflush(shared_dst); _mm_mfence();

    printf("[Client] shared_dst[0]=%016lx\n", shared_dst[0]);
    assert(shared_dst[0] == shared_src[0] && "Shared DMA transfer failed");

    printf("[Client] Shared DMA PASS\n");

    printf("[Client] Press Enter to exit...\n");
    getchar();

    return 0;
}
