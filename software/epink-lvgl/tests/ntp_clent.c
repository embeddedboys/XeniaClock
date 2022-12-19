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

// Difference between Jan 1, 1900 and Jan 1, 1970
#define UNIX_OFFSET 2208988800L

#define NTP_DEFAULT_PORT "123"

// Flags 00|100|011 for li=0, vn=4, mode=3
#define NTP_FLAGS 0x23

typedef struct {

    uint8_t flags;

    uint8_t stratum;
    uint8_t poll;

    uint8_t precision;

    uint32_t root_delay;
    uint32_t root_dispersion;

    uint8_t referenceID[4];

    uint32_t ref_ts_secs;
    uint32_t ref_ts_frac;

    uint32_t origin_ts_secs;
    uint32_t origin_ts_frac;

    uint32_t recv_ts_secs; // This is what we need mostly to get current time.
    uint32_t recv_ts_fracs;

    uint32_t transmit_ts_secs;
    uint32_t transmit_ts_frac;

} ntp_packet;


int main(int argc, char *argv[]) {

    char *server;
    char *port = NTP_DEFAULT_PORT;

    int server_sock, status;

    struct addrinfo hints, *servinfo, *ap;

    socklen_t addrlen = sizeof(struct sockaddr_storage);

    if(argc < 2) {
        printf("Usage: %s <server> [port]\n", argv[0]);
        exit(1);
    }

    server = argv[1]; // if it is supplied as argument

    if(argc == 3) {

        // Port is also passed in as argument
        port = argv[2];
    }

    ntp_packet packet = { .flags = NTP_FLAGS }; // populate the struct

    hints = (struct addrinfo) { .ai_family = AF_UNSPEC, .ai_socktype = SOCK_DGRAM };

    // Get the info of the NTP server

    if((status = getaddrinfo(server, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo() error: %s\n", gai_strerror(status));
        exit(2);
    }

    // Initalize the socket

    for(ap = servinfo; ap != NULL; ap = ap->ai_next) {
        server_sock = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if(server_sock == -1)
            continue;
        break;
    }

    if (ap == NULL) {
        fprintf(stderr, "socket() error\n");
        exit(2);
    }

    // Send the structure to the server

    if((status = sendto(server_sock, &packet, sizeof(packet), 0, ap->ai_addr, addrlen)) == -1) {
        perror("sendto() error");
        exit(2);
    }

    // Send the structure to the server

    if((status = recvfrom(server_sock, &packet, sizeof(packet), 0, ap->ai_addr, &addrlen)) == -1) {
        perror("recvfrom() error");
        exit(2);
    }

    freeaddrinfo(servinfo);
    close(server_sock);

    // Convert from network's to host's endian order

    packet.recv_ts_secs = ntohl(packet.recv_ts_secs);

    // The number of seconds we get back from the server is equal to the no. of
    // seconds since Jan 1, 1900. Since Unix time starts from Jan 1, 1970, we
    // subtract 70 years worth of seconds from Jan 1, 1990.

    time_t time_struct = (time_t) packet.recv_ts_secs - UNIX_OFFSET;

    printf("Time: %s", ctime(&time_struct));
}