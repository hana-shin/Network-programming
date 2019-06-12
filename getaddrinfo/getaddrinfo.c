#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    struct in_addr addr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    getaddrinfo(argv[1], NULL, &hints, &result);

    for(rp = result; rp != NULL; rp = rp->ai_next) {
        addr.s_addr = ((struct sockaddr_in *)(rp->ai_addr))->sin_addr.s_addr;
        printf("ip addres: %s\n", inet_ntoa(addr));
    }

    freeaddrinfo(result);
    return 0;
}
