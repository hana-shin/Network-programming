#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_USER 17
#define MAX_PAYLOAD 1024

struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;

int main(int argc, char *argv[])
{
    sock_fd=socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), argv[1]);

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    printf("My PID is %d\n", getpid());
    printf("Sending message to kernel: %s\n", argv[1]);

    /* Send message to kernel */
    sendmsg(sock_fd,&msg,0);
    printf("Waiting for message from kernel\n");

    /* Read message from kernel */
    recvmsg(sock_fd, &msg, 0);
    printf("Received message from kernel: %s\n", (char *)NLMSG_DATA(nlh));
    close(sock_fd);
    return 0;
}
