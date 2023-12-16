#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9999);  // daytime server

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    int connfd;
    char buff[MAXLINE];
    time_t ticks;
    for (;;) {
        connfd = Accept(listenfd, (SA *)NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "0109_daytimetcpsrv: %.24s\r\n", ctime(&ticks));
        // Write(connfd, buff, strlen(buff));
        for (int i = 0; i < strlen(buff); ++i) {
            Write(connfd, &buff[i], 1);
            // sleep(1);
        }

        Close(connfd);
    }
}
