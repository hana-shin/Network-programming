#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct linger lin;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = inet_addr("192.168.3.10");

    lin.l_onoff = 1;
    lin.l_linger = 3;
    setsockopt(sock, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin));

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    write(sock, "123", sizeof("123"));
    sleep(10);

    close(sock);
    return 0;
}
