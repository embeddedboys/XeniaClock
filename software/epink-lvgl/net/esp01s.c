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

#include <string.h>

#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/regs/intctrl.h"
#include "hardware/uart.h"

#include "common/tools.h"
#include "common/vals.h"
#include "net/esp01s.h"
#include "net/index.h"
#include "src/misc/lv_timer.h"

#define ESP8266_CMD_SUFFIX          "\r\n"
#define ESP8266_CMD(cmd)            cmd ESP8266_CMD_SUFFIX
#define ESP8266_CMD_AT              ESP8266_CMD("AT")
#define ESP8266_CMD_AT_GMR          ESP8266_CMD("AT+GMR")

#define ESP8266_CMD_ON              1
#define ESP8266_CMD_OFF             0

#define ESP8266_CMD_AT_RST          "AT+RST"
#define ESP8266_CMD_ATE             "ATE"           /* enable or disable uart echo */
#define ESP8266_CMD_AT_CWMODE       "AT+CWMODE="    /* switch working mode */
#define ESP8266_CMD_AT_CWJAP        "AT+CWJAP="     /* join AP in station mode */
#define ESP8266_CMD_AT_CWSAP        "AT+CWSAP="     /* set AP infomation in AP mode */
#define ESP8266_CMD_AT_CWLIF        "AT+CWLIF"      /* query ip of clients */
#define ESP8266_CMD_AT_CIPMUX       "AT+CIPMUX="    /* on/off multiple device mode */
#define ESP8266_CMD_AT_CIPSERVER    "AT+CIPSERVER=" /* on/off server */
#define ESP8266_CMD_AT_CIPSTO       "AT+CIPSTO="    /* set length of server timeout */
#define ESP8266_CMD_AT_CIPSTATUS    "AT+CIPSTATUS"  /* query current connections */
#define ESP8266_CMD_AT_CIPSEND      "AT+CIPSEND="   /* send data to given connection */
#define ESP8266_CMD_DEBUG
// #define ESP8266_CMD_AT_CWMODE(m)    ESP8266_CMD("AT+CWMODE="#m)
// #define ESP8266_CMD_AT_CWJAP(ssid,psk)     ESP8266_CMD("AT+CWJAP=" #ssid "," #psk)
// #define ESP8266_CMD_AT_CWSAP(ssid,psk,chn,ecn)  ESP8266_CMD("AT+CWSAP=" #ssid "," #psk "," #chn "," #ecn)

static void __esp01s_send_command(char *cmd);

static struct esp01s_handle g_esp01s_handle = {0};
static struct esp01s_handle *p_correct_handle = &g_esp01s_handle;

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

static uint32_t g_rx_buf_index = 0;
static char g_rx_buf[128];
void esp01s_rx_isr()
{
    while (uart_is_readable(DEFAULT_ESP8266_UART_IFACE)) {
        char ch = uart_getc(DEFAULT_ESP8266_UART_IFACE);
        printf("%c", ch);
        g_rx_buf[g_rx_buf_index++] = ch;
    }
}

static inline void esp01s_rx_buf_reset()
{
    g_rx_buf[g_rx_buf_index] = '\0';
    g_rx_buf_index = 0;
}

static void __esp01s_send_command(char *cmd)
{
    uint8_t buf[64];
    // printf("=========== %s, %d\n", __func__, __LINE__);
    uart_puts(DEFAULT_ESP8266_UART_IFACE, cmd);
    
    /* a delay is needed to wait esp8266 internal process */
    sleep_ms(100);
    
    /* append terminate ch '\0' to the end of buf and reset buf index */
    esp01s_rx_buf_reset();
    // pr_debug("========%s========\n", g_rx_buf);
}

static inline void esp01s_reset(struct esp01s_handle *handle)
{
    ESP8266_SEND_CMD_NO_PARAM(ESP8266_CMD_AT_RST);
    handle->stat = ESP8266_STATUS_RESET;
}

static inline void esp01s_set_echo_enabled(struct esp01s_handle *handle, bool enabled)
{
    if (handle->initialized != ESP8266_STATUS_INITIALIZED) {
        pr_debug("module is not initialized! do nothing.\n");
        return;
    }
    
    if (enabled) {
        ESP8266_SEND_CMD(ESP8266_CMD_ATE \
                         "%d",
                         ESP8266_CMD_ON);
        handle->cfg.echo_enabled = ESP8266_CMD_ON;
    } else {
        ESP8266_SEND_CMD(ESP8266_CMD_ATE \
                         "%d",
                         ESP8266_CMD_OFF);
        handle->cfg.echo_enabled = ESP8266_CMD_OFF;
    }
}

void esp01s_change_mode(struct esp01s_handle *handle, esp8266_mode_t mode)
{
    if (handle->initialized != ESP8266_STATUS_INITIALIZED) {
        pr_debug("module is not initialized! do nothing.\n");
        return;
    }
    
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
    
    handle->cfg.mode = mode;
}

void esp01s_set_ap_config(struct esp01s_handle *handle, struct esp01s_config *cfg)
{
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CWSAP \
                "\"%s\",\"%s\",%d,%d",
                cfg->ap_name,
                cfg->ap_psk,
                cfg->ap_chn,
                cfg->ap_ecn
    );
    memcpy(&handle->cfg, cfg, sizeof(struct esp01s_config));
}

void esp01s_start_ap(struct esp01s_handle *handle)
{
    struct esp01s_config in_cfg;
    
    in_cfg.ap_name = DEFAULT_ESP8266_AP_NAME;
    in_cfg.ap_psk = DEFAULT_ESP8266_AP_PSK;
    in_cfg.ap_chn = DEFAULT_ESP8266_AP_CHANNEL;
    in_cfg.ap_ecn = DEFAULT_ESP8266_AP_ECN;
    
    // ESP8266_SEND_CMD_NO_PARAM(ESP8266_CMD_AT_RST);
    esp01s_change_mode(handle, ESP8266_SOFT_AP_MODE);
    handle->cfg.mode = ESP8266_SOFT_AP_MODE;
    
    esp01s_set_ap_config(handle, &in_cfg);
}

void esp01s_stop_ap(struct esp01s_handle *handle)
{
    esp01s_change_mode(handle, ESP8266_STATION_MODE);
    handle->cfg.mode = ESP8266_STATION_MODE;
}

void esp01s_server_start(struct esp01s_handle *handle)
{
    esp01s_start_ap(handle);
    
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPMUX \
                "%d",
                ESP8266_CMD_ON
    );
}

void esp01s_server_stop(struct esp01s_handle *handle)
{
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPMUX \
                "%d",
                ESP8266_CMD_OFF
    );
    
    esp01s_stop_ap(handle);
    esp01s_reset(handle);
}

void esp01s_server_listen_on(struct esp01s_handle *handle,
                             uint16_t port,
                             bool enabled)
{
    // __esp01s_send_command("AT+CIPSERVER=1,80\r\n");
    if (enabled) {
        ESP8266_SEND_CMD(
                    ESP8266_CMD_AT_CIPSERVER \
                    "%d,%d",
                    ESP8266_CMD_ON, port
        );
    } else {
        ESP8266_SEND_CMD(
                    ESP8266_CMD_AT_CIPSERVER \
                    "%d,%d",
                    ESP8266_CMD_ON, port
        );
    }
}

void esp01s_server_set_timeout(uint16_t timeout)
{
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPSTO \
                "%d",
                timeout
    );
}

static void esp01s_conns_list_reset(struct esp01s_connection *conns)
{
    struct esp01s_connection *p_tmp_conn = conns;
    while(p_tmp_conn->p_next) {
        struct esp01s_connection *tmp = p_tmp_conn;
        p_tmp_conn = p_tmp_conn->p_next;
        free(tmp);
    }
    conns = NULL;
    pr_debug("connections linked list has been free!\n");
}

struct esp01s_connection esp01s_server_status(struct esp01s_handle *handle)
{
    struct esp01s_connection *p_tmp_conn;

    /* reset connection linked list */
    if (handle->conns != NULL) {
        esp01s_conns_list_reset(handle->conns);
    }

    ESP8266_SEND_CMD_NO_PARAM(
                ESP8266_CMD_AT_CIPSTATUS
    );

    /* process rx buf */
    uint8_t len = 0;
    uint8_t pass_echo_count = 2;
    char *token, *line;
    for (line = g_rx_buf;; line = NULL) {
        token = strtok(line, "+");
        if (token == NULL)
            break;
        if (handle->cfg.echo_enabled && pass_echo_count--) {
            pr_debug("passing this line because it's a echo\n");
            continue;
        }
        /* parse first line */
        len++;
        pr_debug("== %d : %s", len, token);
        struct esp01s_connection *conn = (struct esp01s_connection *) \
                                         malloc(sizeof(struct esp01s_connection));
        pr_debug("parsing connection : %d ...\n", len);
        /* TODO: fix this parse process */
        // sscanf(token, "CIPSTATUS:%d,\"%s\",\"%s\",%d,%d,%d",
        //        &conn->id,
        //        conn->type,
        //        conn->addr,
        //        &conn->remote_port,
        //        &conn->local_port,
        //        &conn->tetype);

        pr_debug("parsed connection : %d\n", len);
        /* store nodes into list */
        if (handle->conns == NULL) { /* first connection */
            pr_debug("it's first connection\n");
            handle->conns = conn;
        } else {    /* more than one connection */
            pr_debug("it's appending connection\n");
            p_tmp_conn = handle->conns;
            while (p_tmp_conn->p_next) {
                p_tmp_conn = p_tmp_conn->p_next;
            }
            p_tmp_conn->p_next = conn;
        }
    }
    if (len >= 1) { /* we got some connections from client */
        pr_debug("we got some connections from client\n");
    } else {
        pr_debug("there haven't any client connected to the server! nothing to be doing\n");
    }
}

void esp01s_server_tcp_send(struct esp01s_handle *handle,
                            char *ip,
                            uint16_t length,
                            char *content)
{
    pr_debug("---length : %d\n", length);
    /* TODO: send to all connected clients,
     * need call `esp01s_server_status` first
     * to query connections
     */
    esp01s_server_status(handle);
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPSEND \
                "%d,%d",
                0, length
    );
    uart_puts(DEFAULT_ESP8266_UART_IFACE, INDEX_HTML_CONTENT);
    ESP8266_SEND_CMD(
                ESP8266_CMD_AT_CIPSEND \
                "%d,%d",
                1, length
    );
    uart_puts(DEFAULT_ESP8266_UART_IFACE, INDEX_HTML_CONTENT);
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

void esp01s_run_config(struct esp01s_handle *handle)
{
    esp01s_set_echo_enabled(handle, true);
    esp01s_server_start(handle);
    esp01s_server_listen_on(handle, 80, true);
    esp01s_server_tcp_send(p_correct_handle, NULL,
                           strlen(INDEX_HTML_CONTENT),
                           INDEX_HTML_CONTENT);
}

/* entrance of this module */
void esp01s_test()
{
    __esp01s_send_command(ESP8266_CMD_AT);
}

void esp01s_init(struct esp01s_handle *handle)
{
    /* set rx isr of using uart, enable uart irq,
     * set uart rx irq enabled, tx irq disabled
     */
    irq_set_exclusive_handler(DEFAULT_ESP8266_UART_IRQ, esp01s_rx_isr);
    irq_set_enabled(DEFAULT_ESP8266_UART_IRQ, true);
    uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, true, false);
    
    /* if user given a handle, then we replaced with it */
    if (handle != NULL) {
        pr_debug("using user given esp01s handle\n");
        p_correct_handle = handle;
    }
    handle->conns = NULL;
    p_correct_handle->initialized = ESP8266_STATUS_INITIALIZED;
    esp01s_run_config(p_correct_handle);
    
    pr_debug("esp01s is initialized\n");
}