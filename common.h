//
// Created by David Loh on 21.06.23.
//

#ifndef SIMPLE_WEBSERVER_COMMON_H
#define SIMPLE_WEBSERVER_COMMON_H

#include <sys/socket.h>
#include <sys/types.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdarg>
#include <cerrno>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 3000
#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char* fmt, ...);
char* bin2hex(const unsigned char* input, size_t len);


#endif //SIMPLE_WEBSERVER_COMMON_H
