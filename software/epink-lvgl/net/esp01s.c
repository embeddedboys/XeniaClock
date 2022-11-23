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
#include "pico/time.h"

#define ESP8266_CMD_SUFFIX          "\r\n"
#define ESP8266_CMD(cmd)            cmd ESP8266_CMD_SUFFIX
#define ESP8266_CMD_AT              ESP8266_CMD("AT")
#define ESP8266_CMD_AT_GMR          ESP8266_CMD("AT+GMR")

#define ESP8266_CMD_AT_CWMODE       "AT+CWMODE=%d"
#define ESP8266_CMD_AT_CWJAP        "AT+CWJAP="
#define ESP8266_CMD_AT_CWSAP        "AT+CWSAP="

// #define ESP8266_CMD_AT_CWMODE(m)    ESP8266_CMD("AT+CWMODE="#m)
// #define ESP8266_CMD_AT_CWJAP(ssid,psk)     ESP8266_CMD("AT+CWJAP=" #ssid "," #psk)
// #define ESP8266_CMD_AT_CWSAP(ssid,psk,chn,ecn)  ESP8266_CMD("AT+CWSAP=" #ssid "," #psk "," #chn "," #ecn)
// AT+CWJAP="redmiax3000","h2231841."
// AT+PING="192.168.31.57"

static void __esp01s_send_command(char *cmd);

#define ESP8266_SEND_CMD(cmd, ...) do { \
    char at_cmd[48];    \
    sprintf(at_cmd, ESP8266_CMD(cmd), __VA_ARGS__);   \
    __esp01s_send_command(at_cmd);  \
}while(0);

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
        break;
    default:
        mode = DEFAULT_ESP8266_WORK_MODE;
        break;
    }

    ESP8266_SEND_CMD(
        ESP8266_CMD_AT_CWMODE,
        mode
    );
}

void esp01s_set_ap_config(struct esp01s_config *cfg)
{
    // char at_cmd[64];
    // sprintf(at_cmd,
    //     ESP8266_CMD(
    //         ESP8266_CMD_AT_CWSAP "\"%s\",\"%s\",%d,%d"
    //     ),
    //     cfg->ap_name,
    //     cfg->ap_psk,
    //     cfg->ap_chn,
    //     cfg->ap_ecn
    // );
    // __esp01s_send_command(at_cmd);
    ESP8266_SEND_CMD(
        ESP8266_CMD_AT_CWSAP \
        "\"%s\",\"%s\",%d,%d",
        cfg->ap_name,
        cfg->ap_psk,
        cfg->ap_chn,
        cfg->ap_ecn
    );
}

void esp01s_start_ap()
{
    struct esp01s_config in_cfg;

    in_cfg.ap_name = DEFAULT_ESP8266_AP_NAME;
    in_cfg.ap_psk = DEFAULT_ESP8266_AP_PSK;
    in_cfg.ap_chn = DEFAULT_ESP8266_AP_CHANNEL;
    in_cfg.ap_ecn = DEFAULT_ESP8266_AP_ECN;

    esp01s_change_mode(ESP8266_SOFT_AP_MODE);
    sleep_ms(100);

    esp01s_set_ap_config(&in_cfg);
}

void esp01s_stop_ap()
{
    esp01s_change_mode(ESP8266_STATION_MODE);
}

void esp01s_start_server()
{
    __esp01s_send_command("AT+CIPMUX=1\r\n");
    __esp01s_send_command("AT+CIPSERVER=1,80\r\n");
}

void esp01s_stop_server()
{
    __esp01s_send_command("AT+CIPSERVER=0,1\r\n");
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