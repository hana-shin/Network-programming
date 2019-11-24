#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int sock,val;
    char buf[10]="0123456789";

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = inet_addr("192.168.3.10");

    val = atoi(argv[1]);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    write(sock, buf, sizeof(buf));
    write(sock, buf, sizeof(buf));
    write(sock, buf, sizeof(buf));
    write(sock, buf, sizeof(buf));
    write(sock, buf, sizeof(buf));

    close(sock);
    return 0;
}
