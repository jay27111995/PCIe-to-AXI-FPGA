#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
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

static void recv_fds(int sock, uint64_t* bar_offset, int* dev_fd, int* container_fd) {
    char buf[CMSG_SPACE(2 * sizeof(int))];
    read(sock, bar_offset, sizeof(*bar_offset));

    char dummy;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    recvmsg(sock, &msg, 0);
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    int* fds = (int*)CMSG_DATA(cmsg);
    *dev_fd = fds[0];
    *container_fd = fds[1];
}

static void* create_dma(int container_fd, uint64_t size, uint64_t iova) {
    void* p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    struct vfio_iommu_type1_dma_map dma_map = {
        .argsz = sizeof(dma_map),
        .flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE,
        .vaddr = (uint64_t)p,
        .iova = iova,
        .size = size
    };
    if (ioctl(container_fd, VFIO_IOMMU_MAP_DMA, &dma_map) < 0) {
        perror("VFIO_IOMMU_MAP_DMA");
        return NULL;
    }
    return p;
}

int main(int argc, char* argv[]) {
    uint64_t src_iova = 0x300000;  // Default IOVAs
    uint64_t dst_iova = 0x400000;
    uint64_t sram_page = 0x1000;   // Default SRAM page offset
    if (argc > 1) src_iova = strtoull(argv[1], NULL, 0);
    if (argc > 2) dst_iova = strtoull(argv[2], NULL, 0);
    if (argc > 3) sram_page = strtoull(argv[3], NULL, 0);

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); return 1;
    }

    uint64_t bar_offset;
    int dev_fd, container_fd;
    recv_fds(sock, &bar_offset, &dev_fd, &container_fd);
    close(sock);

    printf("[Client] dev_fd=%d container_fd=%d bar_offset=0x%lx\n", dev_fd, container_fd, bar_offset);
    printf("[Client] Using src_iova=0x%lx dst_iova=0x%lx\n", src_iova, dst_iova);

    // Map BAR - only map 4KB page
    volatile uint64_t* bar = (volatile uint64_t*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                                                       MAP_SHARED, dev_fd, bar_offset + sram_page);
    assert(bar != MAP_FAILED && "mmap BAR failed");
    printf("[Client] BAR mapped: va=%p (page at BAR+0x%lx)\n", bar, sram_page);

    // Also map register page separately
    volatile uint64_t* regs = (volatile uint64_t*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                                                        MAP_SHARED, dev_fd, bar_offset);
    assert(regs != MAP_FAILED && "mmap regs failed");
    printf("[Client] Regs mapped: va=%p (page at BAR+0x0)\n", regs);

    // Create DMA areas using container FD
    uint64_t* src = (uint64_t*)create_dma(container_fd, 4096, src_iova);
    uint64_t* dst = (uint64_t*)create_dma(container_fd, 4096, dst_iova);
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

    src[0] = 0xCAFEF00D00000000ULL | (src_iova & 0xFFFF);
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
    assert(dst[0] == src[0] && "DMA transfer failed");
    
    printf("[Client] PASS\n");

    printf("[Client] Press Enter to exit...\n");
    getchar();

    return 0;
}
