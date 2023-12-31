#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];

    if (argc != 2) {
        err_quit("usage: 0105_daytimetcpcli <ip_address>");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);  // daytime server
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
        err_sys("connect error");
    }

    int counter = 0;
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        counter++;
        recvline[n] = '\n';   // line feed
        recvline[n + 1] = 0;  // null terminate
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
        fflush(stdout);
    }

    if (n < 0) {
        err_sys("read error");
    }

    printf("counter = %d\n", counter);

    exit(0);
}
