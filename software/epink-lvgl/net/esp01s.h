/**
 * @file esp01s.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-20
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

#ifndef __ESP01S_H
#define __ESP01S_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

typedef enum {
    ESP8266_DISABLE_MODE = 0,
    ESP8266_STATION_MODE = 1,
    ESP8266_SOFT_AP_MODE = 2,
    ESP8266_SOFT_AP_STATION_MODE = 3,
}esp8266_mode_t;

#define DEFAULT_ESP8266_UART_IFACE  uart1
#define DEFAULT_ESP8266_WORK_MODE   ESP8266_STATION_MODE

/* SoftAP */
#define DEFAULT_ESP8266_AP_NAME     "Ghost" // max for 13 chars
#define DEFAULT_ESP8266_AP_PSK      "12345678"
#define DEFAULT_ESP8266_AP_CHANNEL  5
#define DEFAULT_ESP8266_AP_ECN      0

/* Web server */
#define DEFAULT_ESP8266_SERVER_PORT 80

#define DEFAULT_ESP8266_WIFI_SSID   "redmiax3000"
#define DEFAULT_ESP8266_WIFI_PSK    "h2231841."

struct esp01s_config {
    uart_inst_t *ifce;

    esp8266_mode_t mode;

    /* If in station mode */
    char *ssid;
    char *psk;

    /* If in SoftAP mode */
    char *ap_name;
    uint8_t ap_chn; /* AP channel */
    uint8_t ap_ecn; /* encypt mode */
    char *ap_psk;   /* password for WPA2 ecn mode */

    /* ip of esp */
    char *ip;
};

void esp01s_test();
void esp01s_set_ap_config(struct esp01s_config *cfg);
void esp01s_start_ap();

#endif