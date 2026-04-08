#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/pcie_server.sock"

static int recv_fd(int sock, uint64_t* bar_offset) {
    char buf[CMSG_SPACE(sizeof(int))];
    read(sock, bar_offset, sizeof(*bar_offset));

    char dummy;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    recvmsg(sock, &msg, 0);
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    return *(int*)CMSG_DATA(cmsg);
}

int main(int argc, char* argv[]) {
    uint64_t page_offset = 0x1000;  // Default: page 1
    if (argc > 1) page_offset = strtoull(argv[1], NULL, 0);

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); return 1;
    }

    uint64_t bar_offset;
    int dev_fd = recv_fd(sock, &bar_offset);
    close(sock);

    printf("[Client] Got device_fd=%d, BAR offset=0x%lx\n", dev_fd, bar_offset);

    // Map only 4KB at specified page
    const uint64_t PAGE_SIZE = 0x1000;
    uint8_t* page = (uint8_t*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, dev_fd, bar_offset + page_offset);
    if (page == MAP_FAILED) { perror("mmap"); return 1; }

    volatile uint64_t* mem = (volatile uint64_t*)page;
    uint64_t pattern = 0xAAAA000000000000ULL | page_offset;

    printf("[Client] PID=%d mapped 4KB at BAR+0x%lx\n", getpid(), page_offset);

    mem[0] = pattern;
    mem[1] = pattern + 1;
    printf("[Client] Wrote: 0x%lx, 0x%lx\n", pattern, pattern + 1);

    printf("[Client] Press Enter to read back...\n");
    getchar();

    uint64_t v0 = mem[0], v1 = mem[1];
    printf("[Client] Read:  0x%lx, 0x%lx\n", v0, v1);
    printf("[Client] %s\n", (v0 == pattern && v1 == pattern + 1) ? "MATCH" : "MISMATCH");

    munmap(page, PAGE_SIZE);
    return 0;
}
