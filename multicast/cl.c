#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in addr;
  struct sockaddr_in src_addr;
  in_addr_t ipaddr;

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(11111);
  addr.sin_addr.s_addr = inet_addr("239.0.0.100");

  src_addr.sin_addr.s_addr = inet_addr("192.168.3.30");
  if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&src_addr.sin_addr.s_addr, sizeof(ipaddr)) != 0) {
    perror("setsockopt");
    return 1;
  }

  if(sendto(sock, "HELLO", 5, 0, (struct sockaddr *)&addr, sizeof(addr)) == -1){
    perror("sendto");
    return 1;
  }
  close(sock);
  return 0;
}
