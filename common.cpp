//
// Created by David Loh on 27.05.23.
//

#include "common.h"

void error_and_die(const char *fmt, ...) {
    int errno_save;
    va_list ap;

    errno_save = errno;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if(errno_save != 0) {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }

    va_end(ap);
    exit(1);
}

char *bin2hex(const unsigned char *input, size_t len) {
    char* result;
    char* hexits = "01234567890ABCDEF";

    if (input == nullptr || len <= 0)
        return nullptr;

    int resultLength = (len * 3) + 1;

    result = static_cast<char *>(malloc(resultLength));
    bzero(result, resultLength);

    for (int i = 0; i < len; i++) {
        result[i*3] = hexits[input[i] >> 4];
        result[(i * 3) + 1] = hexits[input[i] & 0x0F];
        result[(i * 3) + 2] = ' ';
    }

    return result;
}