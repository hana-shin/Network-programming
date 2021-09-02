#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

int main(int argc, char *argv[])
{
  int sock_fd;
  fd_set readfds;
  ssize_t n;
  char buf[4096];
  struct sockaddr_in server;
  struct pollfd *pollFD;

  if(argc != 3) {
    fprintf(stderr, "Usage:./nc IP PORT\n");
    return 1;
  }

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(argv[1]);

  pollFD = calloc(2, sizeof(struct pollfd));
  pollFD[0].fd = 0;
  pollFD[0].events = POLLIN;


  connect(sock_fd, (struct sockaddr *)&server, sizeof(server));



  for(;;) {
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(sock_fd, &readfds);

    select(sock_fd+1, &readfds, NULL, NULL, NULL);
    if(FD_ISSET(0, &readfds)) {
      if((n=read(0, buf, sizeof(buf))) < 0) {
        perror("read");
        return 1;
      }
      else if (n==0) { //EOF
        break;
      }
      write(sock_fd, buf, n);
    }

    if(FD_ISSET(sock_fd, &readfds)) {
      if((n=read(sock_fd, buf, sizeof(buf))) < 0) {
        perror("read");
        return 1;
      }
      else if (n==0) { //EOF
        break;
      }
      write(1, buf, n);
    }
  }
  shutdown(sock_fd, SHUT_RDWR);
  return 0;
}
