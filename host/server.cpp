#include "pcie-util.h"
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cinttypes>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/vfio.h>
#include <linux/memfd.h>
#include <sys/ioctl.h>

#define SOCK_PATH "/tmp/pcie_server.sock"
#define SHARED_DMA_SIZE 0x200000  // 2MB hugepage
#define SHARED_DMA_IOVA 0x80000000ULL  // Fixed IOVA at 2GB

static void send_fds(int sock, int* fds, int nfds) {
    char buf[CMSG_SPACE(4 * sizeof(int))];
    char dummy = 0;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(nfds * sizeof(int));
    memcpy(CMSG_DATA(cmsg), fds, nfds * sizeof(int));
    msg.msg_controllen = cmsg->cmsg_len;
    sendmsg(sock, &msg, 0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) { fprintf(stderr, "Usage: %s <pcie_dev>\n", argv[0]); return 1; }

    const char* device_bdf = argv[1];
    PCIe::Function dev(device_bdf);

    struct vfio_region_info reg = {.argsz = sizeof(reg), .index = 2};  // BAR2
    if (ioctl(dev.mDeviceFd, VFIO_DEVICE_GET_REGION_INFO, &reg) < 0) {
        perror("VFIO_DEVICE_GET_REGION_INFO");
        return 1;
    }

    // Create shared DMA region using 2MB hugepage memfd
    int dma_fd = memfd_create("shared_dma", MFD_HUGETLB | MFD_HUGE_2MB);
    if (dma_fd < 0) {
        perror("memfd_create hugepage");
        return 1;
    }
    ftruncate(dma_fd, SHARED_DMA_SIZE);

    void* dma_va = mmap((void*)SHARED_DMA_IOVA, SHARED_DMA_SIZE, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_FIXED_NOREPLACE, dma_fd, 0);
    if (dma_va == MAP_FAILED) {
        perror("mmap shared DMA");
        return 1;
    }

    struct vfio_iommu_type1_dma_map dma_map = {
        .argsz = sizeof(dma_map),
        .flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE,
        .vaddr = (uint64_t)dma_va,
        .iova = SHARED_DMA_IOVA,
        .size = SHARED_DMA_SIZE
    };
    if (ioctl(dev.mContainerFd, VFIO_IOMMU_MAP_DMA, &dma_map) < 0) {
        perror("VFIO_IOMMU_MAP_DMA shared");
        return 1;
    }

    printf("[Server] Shared DMA: va=%p iova=0x%" PRIx64 " size=0x%x fd=%d\n",
           dma_va, (uint64_t)SHARED_DMA_IOVA, SHARED_DMA_SIZE, dma_fd);

    unlink(SOCK_PATH);
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 4);

    printf("[Server] Listening. group_fd=%d container_fd=%d device=%s BAR2: offset=0x%llx size=0x%llx\n",
           dev.mGroupFd, dev.mContainerFd, device_bdf, reg.offset, reg.size);

    while (true) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) break;

        // Send device BDF, BAR offset, shared DMA info
        struct {
            char device_bdf[16];
            uint64_t bar_offset;
            uint64_t dma_iova;
            uint64_t dma_size;
        } info = {};
        strncpy(info.device_bdf, device_bdf, sizeof(info.device_bdf) - 1);
        info.bar_offset = reg.offset;
        info.dma_iova = SHARED_DMA_IOVA;
        info.dma_size = SHARED_DMA_SIZE;
        write(client, &info, sizeof(info));

        // Send group FD, container FD, and shared DMA memfd
        int fds[3] = {dev.mGroupFd, dev.mContainerFd, dma_fd};
        send_fds(client, fds, 3);
        printf("[Server] Client connected\n");
        close(client);
    }

    return 0;
}
