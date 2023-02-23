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
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "lvgl/lvgl.h"
#include "common/tools.h"
#include "common/list.h"

typedef enum {
    ESP8266_DISABLE_MODE = 0,
    ESP8266_STATION_MODE = 1,
    ESP8266_SOFT_AP_MODE = 2,
    ESP8266_SOFT_AP_STATION_MODE = 3,
} esp8266_mode_t;

typedef enum {
    ESP8266_STATUS_RESET        = 0,
    ESP8266_STATUS_BUSY         = 1,
    ESP8266_STATUS_IDLE         = 2,
    ESP8266_STATUS_INITIALIZED  = 3,
} esp8266_status_t;

#define DEFAULT_ESP8266_RX_PIN      5
#define DEFAULT_ESP8266_TX_PIN      4
#define DEFAULT_ESP8266_EN_PIN      0

#define DEFAULT_ESP8266_UART_IFACE  uart1
#define DEFAULT_ESP8266_UART_IRQ    UART1_IRQ
#define DEFAULT_ESP8266_WORK_MODE   ESP8266_STATION_MODE

/* SoftAP */
#define DEFAULT_ESP8266_AP_NAME     "Ghosts" // max for 13 chars
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

    /* if in station mode */
    char *ssid;
    char *psk;

    /* if in SoftAP mode */
    char *ap_name;
    uint8_t ap_chn; /* AP channel */
    uint8_t ap_ecn; /* encypt mode */
    char *ap_psk;   /* password for WPA2 ecn mode */

    /* common */
    char *ip;   /* ip of esp */
    bool echo_enabled;
};

struct esp01s_server {
    void (*init)(void);
    void (*start_server)(void);
    void (*stop_server)(void);
    void (*restart_server)(void);

    void (*listen_on)(uint16_t port, char *root);
};

struct esp01s_connection {
    uint32_t id;
    char type[4];
    char addr[16];
    uint32_t remote_port;
    uint32_t local_port;
    uint32_t tetype;

    struct list_head head;
};

struct kv_node {
    char k[24];
    char v[24];

    struct list_head head;
};

struct esp01s_response_args {
    int argc;
    struct kv_node kv;
};

struct esp01s_handle {
    uint8_t initialized;
    esp8266_status_t stat;

    struct esp01s_config cfg;
    struct esp01s_connection conns;
    struct esp01s_response_args args;
};

void esp01s_init(struct esp01s_handle *handle);
void esp01s_test();
void esp01s_set_ap_config(struct esp01s_handle *handle, struct esp01s_config *cfg);
void esp01s_start_ap(struct esp01s_handle *handle);

void esp01s_server_broadcast(struct esp01s_handle *handle,
                            uint16_t length,
                            char *content);

#endif