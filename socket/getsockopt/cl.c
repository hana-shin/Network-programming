#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void print_sock_option(int sock)
{
    int sndbuf, rcvbuf;
    socklen_t optlen;

    optlen = sizeof(sndbuf);
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen);

    optlen = sizeof(rcvbuf);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &optlen);

    printf("SO_RCVBUF:%d,SO_SNDBUF:%d\n", rcvbuf,sndbuf);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int sock;
    char buf[10]="0123456789";

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = inet_addr("192.168.122.20");

    print_sock_option(sock);
    connect(sock, (struct sockaddr *)&server, sizeof(server));
    print_sock_option(sock);

    write(sock, buf, sizeof(buf));

    sleep(30);
    close(sock);
    return 0;
}
