#include "pcie-util.h"
#include <cstdio>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <linux/vfio.h>
#include <sys/ioctl.h>

#define SOCK_PATH "/tmp/pcie_server.sock"

static void send_fds(int sock, int dev_fd, int container_fd) {
    char buf[CMSG_SPACE(2 * sizeof(int))];
    int fds[2] = {dev_fd, container_fd};
    char dummy = 0;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(2 * sizeof(int));
    memcpy(CMSG_DATA(cmsg), fds, 2 * sizeof(int));
    sendmsg(sock, &msg, 0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) { fprintf(stderr, "Usage: %s <pcie_dev>\n", argv[0]); return 1; }

    PCIe::Function dev(argv[1]);

    struct vfio_region_info reg = {.argsz = sizeof(reg), .index = 0};
    ioctl(dev.mDeviceFd, VFIO_DEVICE_GET_REGION_INFO, &reg);

    unlink(SOCK_PATH);
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 4);

    printf("[Server] Listening. dev_fd=%d container_fd=%d BAR0 offset=0x%llx\n",
           dev.mDeviceFd, dev.mContainerFd, reg.offset);

    while (true) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) break;

        // Send BAR0 offset
        write(client, &reg.offset, sizeof(reg.offset));
        
        // Send device FD and container FD
        send_fds(client, dev.mDeviceFd, dev.mContainerFd);
        printf("[Server] Sent FDs to client\n");
        close(client);
    }

    return 0;
}
