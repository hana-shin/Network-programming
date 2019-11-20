#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int sock;
    ssize_t n;
    char buf[32]="0123456789";

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(11111);
    server.sin_addr.s_addr = inet_addr("192.168.3.10");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while(1) {
        n = write(sock, buf, sizeof(buf));
        if( n == -1) {
            perror("write");
            return 1;
        }
        fprintf(stderr,"%zd, %s\n", n, buf);
        sleep(1);
    }
    close(sock);
    return 0;
}
