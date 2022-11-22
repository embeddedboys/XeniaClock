/**
 * @file esp01s.c
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

#include "esp01s.h"
#include "hardware/uart.h"

#define ESP8266_CMD_SUFFIX          "\r\n"
#define ESP8266_CMD(cmd)            cmd ESP8266_CMD_SUFFIX
#define ESP8266_CMD_AT              ESP8266_CMD("AT")
#define ESP8266_CMD_AT_GMR          ESP8266_CMD("AT+GMR")
#define ESP8266_CMD_AT_CWMODE(m)    ESP8266_CMD("AT+CWMODE="#m)
#define ESP8266_CMD_AT_CWJAP(ssid, psk)     ESP8266_CMD("AT+CWJAP=" #ssid "," #psk)
// AT+CWJAP="redmiax3000","h2231841."
// AT+PING="192.168.31.57"

static struct esp01s_config cfg = {
    .ifce = DEFAULT_ESP8266_UART_IFACE,
    .mode = DEFAULT_ESP8266_WORK_MODE,
};

static void __esp01s_send_command(char *cmd)
{
    uart_puts(DEFAULT_ESP8266_UART_IFACE, cmd);
}

void esp01s_test()
{
    __esp01s_send_command(ESP8266_CMD_AT);
}

void esp01s_change_mode(esp8266_mode_t mode)
{
    switch (mode) {
    case ESP8266_STATION_MODE:
    case ESP8266_SOFT_AP_MODE:
    case ESP8266_SOFT_AP_STATION_MODE:
        __esp01s_send_command(ESP8266_CMD_AT_CWMODE(mode));
        break;
    default:
        __esp01s_send_command(ESP8266_CMD_AT_CWMODE(DEFAULT_ESP8266_WORK_MODE));
        break;
    }
}

void esp01s_start_ap()
{
    
    esp01s_change_mode(ESP8266_SOFT_AP_MODE);
}

void esp01s_connect_wifi()
{

}

void esp01s_disconnect_wifi()
{

}

void esp01s_get_ip()
{

}

void esp01s_ping(char *ip)
{

}

/* TODO: NTP handle */