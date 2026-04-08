#include "pcie-util.h"
#include <cstdio>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <linux/vfio.h>
#include <sys/ioctl.h>

// Server: opens VFIO device, sends device FD to clients
#define SOCK_PATH "/tmp/pcie_server.sock"

static void send_fd(int sock, int fd) {
    char buf[CMSG_SPACE(sizeof(int))];
    char dummy = 0;
    struct iovec io = {.iov_base = &dummy, .iov_len = 1};
    struct msghdr msg = {.msg_iov = &io, .msg_iovlen = 1, .msg_control = buf, .msg_controllen = sizeof(buf)};
    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    *(int*)CMSG_DATA(cmsg) = fd;
    sendmsg(sock, &msg, 0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) { fprintf(stderr, "Usage: %s <pcie_dev>\n", argv[0]); return 1; }

    PCIe::Function dev(argv[1]);

    // Get BAR0 info to send to clients
    struct vfio_region_info reg = {.argsz = sizeof(reg), .index = 0};
    ioctl(dev.mDeviceFd, VFIO_DEVICE_GET_REGION_INFO, &reg);

    unlink(SOCK_PATH);
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {.sun_family = AF_UNIX};
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 2);

    printf("[Server] Listening, device_fd=%d, BAR0 offset=0x%llx size=0x%llx\n",
           dev.mDeviceFd, reg.offset, reg.size);

    while (true) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) break;

        // Send BAR0 offset first
        write(client, &reg.offset, sizeof(reg.offset));

        // Send device FD
        send_fd(client, dev.mDeviceFd);
        printf("[Server] Sent device FD to client\n");
        close(client);
    }

    return 0;
}
