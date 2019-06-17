#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "def.h"

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[MAXLINE];
    char* message = "Hello Server";
    struct sockaddr_in servaddr;
    ssize_t n;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SV);
    sendto(sockfd, (const char*)message, strlen(message),0, (const struct sockaddr*)&servaddr,sizeof(servaddr));

    printf("Message from server: ");
    n = recvfrom(sockfd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&servaddr, &len);
    printf("%zd byes received\n", n);
    puts(buffer);
    close(sockfd);
    exit(0);
}
