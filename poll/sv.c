#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  int sock1, sock2;
  struct sockaddr_in addr1, addr2;
  struct pollfd fds[2];
  char buf[2048];

  sock1 = socket(AF_INET, SOCK_DGRAM, 0);
  sock2 = socket(AF_INET, SOCK_DGRAM, 0);
  addr1.sin_family = AF_INET;
  addr2.sin_family = AF_INET;

  inet_pton(AF_INET, "192.168.3.20", &addr1.sin_addr.s_addr);
  inet_pton(AF_INET, "192.168.3.20", &addr2.sin_addr.s_addr);

  addr1.sin_port = htons(11111);
  addr2.sin_port = htons(22222);

  bind(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
  bind(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

  memset(&fds, 0, sizeof(fds));

  fds[0].fd = sock1;
  fds[0].events = POLLIN | POLLERR;

  fds[1].fd = sock2;
  fds[1].events = POLLIN | POLLERR;
  
  while (1) {
    poll(fds, 2, -1);

    if (fds[0].revents & POLLIN) {
      memset(buf, 0, sizeof(buf));
      recv(sock1, buf, sizeof(buf), 0);
      printf("%s\n", buf);
    }

    if (fds[1].revents & POLLIN) {
      memset(buf, 0, sizeof(buf));
      recv(sock2, buf, sizeof(buf), 0);
      printf("%s\n", buf);
    }
  }
  close(sock1);
  close(sock2);

  return 0;
}
