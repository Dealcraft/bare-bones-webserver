#include "common.h"
#include <strings.h>
#include <iostream>

int main(int argc, char* argv[]) {
    char opt;
    char* staticPath = nullptr;

    while((opt = getopt(argc, argv, "p:")) != EOF) {
        switch (opt) {
            case 'p':
                staticPath = optarg;
                break;
            default:
                fprintf(stdout, "\nUnknown option -%c\n", opt);
                exit(1);
        }
    }

    if(staticPath == nullptr) {
        fprintf(stdout, "\nNo path defined!\nUse -p <path> to define a path\n");
        exit(1);
    }

    struct sockaddr_in servaddr;
    int listenfd, connfd, n;
    uint8_t buff[MAXLINE + 1];
    uint8_t recvline[MAXLINE + 1];

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_and_die("Socket error");


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
        error_and_die("Bind error");


    if ((listen(listenfd, 10)) < 0)
        error_and_die("Listen error");


    while (true) {
        struct sockaddr_in addr;
        socklen_t addr_len;

        printf("Waiting for connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        connfd = accept(listenfd, (SA *) NULL, NULL);

        memset(recvline, 0, MAXLINE);

        while ((n = read(connfd, recvline, MAXLINE - 1)) > 0) {
            fprintf(stdout, "\n%s\n", recvline);

            if (recvline[n - 1] == '\n')
                break;

            memset(recvline, 0, MAXLINE);
        }

        if (n < 0)
            error_and_die("read error");

        snprintf((char *) buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");

        write(connfd, (char *) buff, strlen((char *) buff));
        shutdown(connfd, SHUT_WR);
        close(connfd);
    }



    return 0;
}
