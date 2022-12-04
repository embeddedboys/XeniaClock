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
#include "common/tools.h"
#include "hardware/irq.h"
#include "hardware/regs/intctrl.h"
#include "hardware/uart.h"
#include "pico/time.h"
#include "src/misc/lv_mem.h"

#define ESP8266_CMD_SUFFIX          "\r\n"
#define ESP8266_CMD(cmd)            cmd ESP8266_CMD_SUFFIX
#define ESP8266_CMD_AT              ESP8266_CMD("AT")
#define ESP8266_CMD_AT_GMR          ESP8266_CMD("AT+GMR")

#define ESP8266_CMD_ON              1
#define ESP8266_CMD_OFF             0

#define ESP8266_CMD_AT_RST          "AT+RST"
#define ESP8266_CMD_AT_CWMODE       "AT+CWMODE="    /* switch working mode */
#define ESP8266_CMD_AT_CWJAP        "AT+CWJAP="     /* join AP in station mode */
#define ESP8266_CMD_AT_CWSAP        "AT+CWSAP="     /* set AP infomation in AP mode */
#define ESP8266_CMD_AT_CIPMUX       "AT+CIPMUX="    /* on/off multiple device mode */
#define ESP8266_CMD_AT_CIPSERVER    "AT+CIPSERVER=" /* on/off server */
#define ESP8266_CMD_AT_CIPSTO       "AT+CIPSTO="    /* set length of server timeout */
#define ESP8266_CMD_AT_CIPSTATUS    "AT+CIPSTATUS"  /* query current connections */
#define ESP8266_CMD_DEBUG
// #define ESP8266_CMD_AT_CWMODE(m)    ESP8266_CMD("AT+CWMODE="#m)
// #define ESP8266_CMD_AT_CWJAP(ssid,psk)     ESP8266_CMD("AT+CWJAP=" #ssid "," #psk)
// #define ESP8266_CMD_AT_CWSAP(ssid,psk,chn,ecn)  ESP8266_CMD("AT+CWSAP=" #ssid "," #psk "," #chn "," #ecn)

static uint32_t g_rx_buf_index = 0;
static uint8_t g_rx_buf[128];

static void __esp01s_send_command(char *cmd);

#define ESP8266_SEND_CMD_NO_PARAM(cmd) do { \
        __esp01s_send_command(ESP8266_CMD(cmd));         \
    } while(0);

#define ESP8266_SEND_CMD(cmd, ...) do { \
        char at_cmd[48];    \
        sprintf(at_cmd, ESP8266_CMD(cmd), __VA_ARGS__);   \
        __esp01s_send_command(at_cmd);  \
    } while(0);

static struct esp01s_config cfg = {
    .ifce = DEFAULT_ESP8266_UART_IFACE,
    .mode = DEFAULT_ESP8266_WORK_MODE,
};

void esp01s_rx_isr() {
    while(uart_is_readable(DEFAULT_ESP8266_UART_IFACE)) {
        uint8_t ch = uart_getc(DEFAULT_ESP8266_UART_IFACE);
        // printf("%c", ch);
        g_rx_buf[g_rx_buf_index++] = ch;
    }
}

static void __esp01s_send_command(char *cmd)
{
    uint8_t buf[64];
    // printf("=========== %s, %d\n", __func__, __LINE__);
    uart_puts(DEFAULT_ESP8266_UART_IFACE, cmd);
    sleep_ms(100);
    g_rx_buf[g_rx_buf_index] = '\0';
    g_rx_buf_index = 0;
    printf("========%s========\n", g_rx_buf);
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
                ESP8266_CMD_AT_CWMODE \
                "%d",
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
    
    // ESP8266_SEND_CMD_NO_PARAM(ESP8266_CMD_AT_RST);
    esp01s_change_mode(ESP8266_SOFT_AP_MODE);
    
    esp01s_set_ap_config(&in_cfg);
}

void esp01s_stop_ap()
{
    esp01s_change_mode(ESP8266_STATION_MODE);
}

void esp01s_server_start()
{
    esp01s_start_ap();
    // __esp01s_send_command("AT+CIPMUX=1\r\n");
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPMUX \
                "%d",
                ESP8266_CMD_ON
    );
    // __esp01s_send_command("AT+CIPSERVER=1,80\r\n");
}

void esp01s_server_stop()
{
    // __esp01s_send_command("AT+CIPSERVER=0,1\r\n");
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPMUX \
                "%d",
                ESP8266_CMD_OFF
    );
    esp01s_stop_ap();
}

void esp01s_server_listen_on(uint16_t port)
{
    // __esp01s_send_command("AT+CIPSERVER=1,80\r\n");
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPSERVER \
                "%d,%d",
                ESP8266_CMD_ON, port
    );
}

void esp01s_server_set_timeout(uint16_t timeout)
{
    ESP8266_SEND_CMD(
        ESP8266_CMD_AT_CIPSTO \
        "%d",
        timeout
    );
}

void esp01s_server_status()
{
    ESP8266_SEND_CMD_NO_PARAM(
        ESP8266_CMD_AT_CIPSTATUS
    );
}

void esp01s_server_tcp_send(char *ip, uint16_t length, char *content)
{
    /* TODO: send to all connected clients,
     * need call `esp01s_server_status` first
     * to query connections
     */
}


/* ========== STA mode ========== */
void esp01s_connect_wifi()
{

}

void esp01s_disconnect_wifi()
{

}

/* ========== Common ========== */
void esp01s_get_ip()
{

}

void esp01s_ping(char *ip)
{

}

/* TODO: NTP handle */

/* entrance of this module */
void esp01s_init()
{
    irq_set_exclusive_handler(UART1_IRQ, esp01s_rx_isr);
    irq_set_enabled(UART1_IRQ, true);

    uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, true, false);
    __esp01s_send_command("ATE1\r\n");
    esp01s_start_ap();
    esp01s_server_status();
}