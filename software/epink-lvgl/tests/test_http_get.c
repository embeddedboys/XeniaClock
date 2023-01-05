/**
 * @file ntp_clent.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief a copy from https://github.com/SanketDG/c-projects/blob/master/ntp-client.c
 * @version 0.1
 * @date 2022-12-19
 * 
 * MIT License
 * 
 * Copyright 2022 IotaHydrae(writeforever@foxmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char *server = "www.baidu.com";;
    char *port = "80";
    struct hostent *hostent;
    struct sockaddr_in addr_in;

    int fd_sock, status;
    char buf[] = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";

    fd_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_sock == -1) {
        exit(EXIT_FAILURE);
    }

    hostent = gethostbyname(server);
    if (hostent == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(&addr_in.sin_addr, hostent->h_addr, hostent->h_length);
    addr_in.sin_port = htons(80);
    addr_in.sin_family = AF_INET;

    if (connect(fd_sock, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in)) == -1) {
        printf("connect failed\n");
        exit(EXIT_FAILURE);
    }

    close(fd_sock);
}
