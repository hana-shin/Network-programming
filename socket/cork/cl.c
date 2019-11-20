#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int sock, i, val;
    ssize_t n;
    char buf[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = inet_addr("192.168.3.10");

    val = atoi(argv[1]);
    setsockopt(sock, IPPROTO_TCP, TCP_CORK, &val, sizeof(val));
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    for(i=0; i<1000; i++) {
        n = write(sock, buf, sizeof(buf));
        if(n == -1) {
            perror("write");
            return 1;
        }
    }
    close(sock);
    return 0;
}
