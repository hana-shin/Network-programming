#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  int sock_fd, epfd, i, nfds;
  ssize_t n;
  char buf[4096];
  struct sockaddr_in server;
  struct epoll_event ev, ev_ret[2];

  if(argc != 3) {
    fprintf(stderr, "Usage:./nc-epoll IP PORT\n");
    return 1;
  }

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(argv[1]);

  epfd = epoll_create(2);

  memset(&ev, 0, sizeof(ev));
  ev.events = EPOLLIN;
  ev.data.fd = 0;
  epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);

  memset(&ev, 0, sizeof(ev));
  ev.events = EPOLLIN;
  ev.data.fd = sock_fd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &ev);

  connect(sock_fd, (struct sockaddr *)&server, sizeof(server));

  for(;;) {
    nfds = epoll_wait(epfd, ev_ret, 2, -1);

    for(i=0; i<nfds; i++) {
      if (ev_ret[i].data.fd == 0) {
        if((n=read(0, buf, sizeof(buf))) < 0) {
          perror("read");
          return 1;
        }
        else if (n==0) { //EOF
          break;
        }
        write(sock_fd, buf, n);
      }
      else if (ev_ret[i].data.fd == sock_fd) {
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
  }
  shutdown(sock_fd, SHUT_RDWR);
  return 0;
}
