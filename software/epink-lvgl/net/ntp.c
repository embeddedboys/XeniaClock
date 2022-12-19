/**
 * @file ntp.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-05
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

#include "net/esp01s.h"

// Difference between Jan 1, 1900 and Jan 1, 1970
#define UNIX_OFFSET 2208988800L

#define NTP_DEFAULT_SERVER "pool.ntp.org"
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

