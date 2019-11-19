#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int lfd, cfd;
    socklen_t len;
    struct sockaddr_in sv, cl;
    char buf[32];
    ssize_t n;

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    sv.sin_family = AF_INET;
    sv.sin_port = htons(11111);
    sv.sin_addr.s_addr = INADDR_ANY;

    if(bind(lfd, (struct sockaddr *)&sv, sizeof(sv)) == -1){
        perror("bind");
        _exit(1);
    }
    listen(lfd, 5);
    memset(buf, 0, sizeof(buf));
    len = sizeof(cl);
    cfd = accept(lfd, (struct sockaddr *)&cl, &len);

    while (1) {
        n = read(cfd, buf, sizeof(buf));
        if(n > 0)
            fprintf(stderr,"%zd, %s\n", n, buf);
        else if(n == 0)  //EOF
            close(cfd);
        else {
            perror("read");
            _exit(1);
        }
    }
    close(lfd);
    _exit(0);
}
