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

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "common/list.h"
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

static void esp01s_server_process_cb();
static inline void esp01s_rx_buf_reset();
static inline void esp01s_rx_buf_clear();
static void __esp01s_send_command(char *cmd);

static lv_timer_t *timer_server_process;

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

#define local_irq_disable() do { \
        uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, false, false); \
    } while(0);

#define GLOBAL_RX_BUF_LEN   (1024)
static volatile uint32_t g_rx_buf_index = 0;
static char g_rx_buf[GLOBAL_RX_BUF_LEN];
static bool g_dev_requesting = false;
static void esp01s_rx_isr()
{
    while (uart_is_readable(DEFAULT_ESP8266_UART_IFACE)) {
        char ch = uart_getc(DEFAULT_ESP8266_UART_IFACE);
        g_rx_buf[g_rx_buf_index] = ch;
        // printf("%c", g_rx_buf[g_rx_buf_index]);
        g_rx_buf_index+=1;

        if (!g_dev_requesting                  &&
            strstr(g_rx_buf, "+IPD")           &&
            // g_rx_buf[g_rx_buf_index-3] == 0x54 &&
            g_rx_buf[g_rx_buf_index-2] == 0x0d &&
            g_rx_buf[g_rx_buf_index-1] == 0x0a
        ) {
            g_dev_requesting = true;
            pr_debug("device requesting!\n");
            // pr_debug("%s\n", g_rx_buf);
            lv_timer_resume(timer_server_process);
            // esp01s_server_process_cb();
        }

        /* reset buf index when the end is reached */
        if (g_rx_buf_index == ARRAY_SIZE(g_rx_buf)) {
            esp01s_rx_buf_clear();
        }
    }

    // uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, true, false);
}

static inline void esp01s_rx_buf_clear()
{
    g_rx_buf_index = 0;
    memset(g_rx_buf, 0x0, GLOBAL_RX_BUF_LEN);
}

static inline void esp01s_rx_buf_reset()
{
    g_rx_buf[g_rx_buf_index] = '\0';
    g_rx_buf_index = 0;
}

static void __esp01s_send(char *buf, uint32_t delay_ms)
{
    uart_puts(DEFAULT_ESP8266_UART_IFACE, buf);
    /* a delay is needed for waiting esp8266 internal process */
    sleep_ms(delay_ms);

    /* append terminate ch '\0' to the end of buf and reset buf index */
    esp01s_rx_buf_reset();
}

static void __esp01s_send_command(char *cmd)
{
    __esp01s_send(cmd, 100);
}

static void __esp01s_send_data(char *data)
{
    __esp01s_send(data, 200);
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

/* ========== STA mode ========== */
void esp01s_connect_wifi(struct esp01s_handle *handle, char *ssid, char *psk)
{
    pr_debug("\n");
    // ESP8266_SEND_CMD(
    //     ESP8266_CMD_AT_CWJAP \
    //     "\"%s\",\"%s\"",
    //     ssid, psk
    //     // "oneplus", "12345678"
    // );
}

void esp01s_disconnect_wifi()
{

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
    pr_debug("AP name : %s\n", handle->cfg.ap_name);
}

void esp01s_start_ap(struct esp01s_handle *handle)
{
    handle->cfg.ap_name = DEFAULT_ESP8266_AP_NAME;
    handle->cfg.ap_psk = DEFAULT_ESP8266_AP_PSK;
    handle->cfg.ap_chn = DEFAULT_ESP8266_AP_CHANNEL;
    handle->cfg.ap_ecn = DEFAULT_ESP8266_AP_ECN;
    
    // ESP8266_SEND_CMD_NO_PARAM(ESP8266_CMD_AT_RST);
    // handle->cfg.mode = ESP8266_SOFT_AP_MODE;
    handle->cfg.mode = ESP8266_SOFT_AP_STATION_MODE;
    esp01s_change_mode(handle, handle->cfg.mode);

    esp01s_set_ap_config(handle, &handle->cfg);
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

static void esp01s_server_fsm(struct esp01s_response_args *p_args)
{
    struct kv_node *np;

    list_for_each_entry(np, &p_args->kv.head, head) {
        if (0 == strcmp(np->k, "ssid")) {
            /* the client is configuring network */
            pr_debug("network\n");
            p_correct_handle->cfg.ssid = np->k;
            p_correct_handle->cfg.psk = np->v;

            /* try to connect to the WiFi */
            esp01s_connect_wifi(p_correct_handle,
                            p_correct_handle->cfg.ssid,
                            p_correct_handle->cfg.psk);
        } else if (0 == strcmp(np->k, "light")) {
            /* the client is wanting to control the light */
            pr_debug("light\n");
        } else {

        }
    }
}

static void esp01s_server_args_reset(struct esp01s_response_args *p_args)
{
    struct kv_node *np;
    struct list_head *pos, *next;

    list_for_each_safe(pos, next, &p_args->kv.head) {
        np = list_entry(pos, struct kv_node, head);
        list_del(pos);
        free(np);
    }
}

static void esp01s_server_process_args(char *kv_buf)
{
    /* reset args list */
    esp01s_server_args_reset(&p_correct_handle->args);

    // pr_debug("=== \n");
    /* IPD,0,530:GET /?ssid=KYKJ&psk=keyifamily HTTP/1.1 */
    // /* parsing response key,value from IPD */
    int argc;
    printf("%s\n", kv_buf);

    char *token, *str;
    for (argc=0,str = kv_buf;; str = NULL,argc++) {
        token = strtok(str, "&");
        if (token == NULL)
            break;
        // printf("%s\n", token);

        struct kv_node *np = (struct kv_node *)malloc(sizeof(struct kv_node));
        memset(np->k, 0x0, ARRAY_SIZE(np->k));
        memset(np->v, 0x0, ARRAY_SIZE(np->v));

        // char *p_str = strchr(token, '=');
        // char *tmp = strcpy(np->v, (p_str+1));
        // while(*tmp++);
        // *tmp = '\0';
        // printf("%p %p \n", token, p_str);
        // tmp = strncpy(np->k, token, (p_str - token));
        // while(*tmp++);
        // *tmp = '\0';
        // printf("k : %s, v : %s\n", np->k, np->v);
        char *p_str = strchr(token, '=');
        strcpy(np->v, (p_str+1));
        strncpy(np->k, token, (p_str - token));
        list_add_tail(&np->head, &p_correct_handle->args.kv.head);
    }

    p_correct_handle->args.argc = argc;
}

static void esp01s_server_process_cb()
{
    /* sleep should never called in this function */
    if (!g_dev_requesting)
        return;

    uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, false, false);
    pr_debug("processing rx buffer!\n");

    /* parsing IPD */
    char * p_tmp = strchr(g_rx_buf, '+');
    if (!p_tmp)
        goto handled;

    // pr_debug("%s\n", p_tmp+1);
    char ipd[48];
    char *tmp = (p_tmp + 1);
    int i = 0;
    while (*tmp != '\n') {
        ipd[i++] = *tmp++;
    }
    ipd[i] = '\0';
    pr_debug("parsing : -> %s\n", ipd);

    /* parse kv buf and send it to args process */
    char kv_buf[64];
    int kv_len = 0;

    char *p_str = strchr(ipd, '?');
    if (!p_str) {
        pr_debug("got nothing about kv, bye\n");
        goto handled;
    }

    char *p_str_cursor = (p_str + 1);
    while(*p_str_cursor++ != ' ')
        kv_len++;
    // printf("kv_len :%d\n", kv_len);
    strncpy(kv_buf, (p_str+1), kv_len);
    kv_buf[kv_len] = '\0';
    // printf("kv_buf : %s, %d\n", kv_buf, sizeof(kv_buf));
    esp01s_server_process_args(kv_buf);

    /* process done, call fsm */
    esp01s_server_fsm(&p_correct_handle->args);

handled:
    /* request handled */
    printf("request handled!\n");
    lv_timer_pause(timer_server_process);
    g_dev_requesting = false;
    esp01s_rx_buf_clear();
    uart_set_irq_enables(DEFAULT_ESP8266_UART_IFACE, true, false);
    return;
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
                    ESP8266_CMD_OFF, port
        );
    }
    esp01s_rx_buf_clear();

    timer_server_process = lv_timer_create(esp01s_server_process_cb, 200, NULL);
    lv_timer_pause(timer_server_process);
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
    struct list_head *pos, *q;
    struct esp01s_connection *tmp;
    
    list_for_each_safe(pos, q, &conns->head) {
        tmp = list_entry(pos, struct esp01s_connection, head);
        list_del(pos);
        pr_debug("freeing connection : %d\n", tmp->id);
        free(tmp);
    }
    pr_debug("connections linked list has been all freed!\n");
}

struct esp01s_connection esp01s_server_status(struct esp01s_handle *handle)
{
    struct esp01s_connection *p_tmp_conn;
    
    /* reset connection linked list */
    // if (handle->conns != NULL) {
    //     esp01s_conns_list_reset(handle->conns);
    // }
    
    if (!list_empty(&handle->conns.head)) {
        pr_debug("list is not empty, resetting it!\n");
        esp01s_conns_list_reset(&handle->conns);
    }
    
    /* send AT command CIPSTATUS */
    ESP8266_SEND_CMD_NO_PARAM(
                ESP8266_CMD_AT_CIPSTATUS
    );
    
    /* process rx buf */
    uint8_t len = 0;
    uint8_t pass_echo_count = 2;
    
    if (handle->cfg.echo_enabled)
        pass_echo_count = 2;
    else
        pass_echo_count = 1;
    
    char *token, *line;
    for (line = g_rx_buf;; line = NULL) {
        token = strtok(line, "+");
        if (token == NULL)
            break;

        /* skip the echo lines */
        if (pass_echo_count) {
            pass_echo_count -= 1;
            pr_debug("passing this line because it's a echo\n");
            continue;
        }

        pr_debug("------ %s\n", token);
        /* parse each line */
        len++;
        pr_debug("== %d : %s", len, token);
        pr_debug("parsing connection : %d ...\n", len);
        
        struct esp01s_connection *conn = (struct esp01s_connection *) \
                                         malloc(sizeof(struct esp01s_connection));
        memset(conn, 0x00, sizeof(struct esp01s_connection));
        pr_debug("node address : %p\n", conn);
        conn->id = len;
        /* TODO: fix this parse process */
        // sscanf(token, "CIPSTATUS:%d,\"%s\",\"%s\",%d,%d,%d",
        //        &conn->id,
        //        conn->type,
        //        conn->addr,
        //        &conn->remote_port,
        //        &conn->local_port,
        //        &conn->tetype);
        
        /* parse connection id */
        char *p = strchr(token, ':');
        conn->id = atoi(p + 1);
        pr_debug("parsing : %s -> %d\n", p + 1, conn->id);
        
        /* parse connection type */
        p = strchr(p + 1, ',');
        strncpy(conn->type, p + 2, 3);
        pr_debug("parsing : %s -> %s\n", p + 1, conn->type);
        
        /* parse connection address */
        p = strchr(p + 1, ',');
        char *tmp = (p + 2);
        int i = 0;
        while (*tmp != '"') {
            conn->addr[i++] = *tmp++;
        }
        pr_debug("parsing : %s -> %s\n", p + 1, conn->addr);
        
        /* parse conn remote port */
        p = strchr(p + 1, ',');
        conn->remote_port = atoi(p + 1);
        pr_debug("parsing : %s -> %d\n", p + 1, conn->remote_port);
        
        /* parse conn local port */
        p = strchr(p + 1, ',');
        conn->local_port = atoi(p + 1);
        pr_debug("parsing : %s -> %d\n", p + 1, conn->local_port);
        
        /* parse connection type */
        p = strchr(p + 1, ',');
        conn->tetype = atoi(p + 1);
        pr_debug("parsing : %s -> %d\n", p + 1, conn->tetype);
        
        pr_debug("parsed connection : %d\n", len);
        /* store nodes into list */
        // esp01s_conns_list_append(handle, conn);
        list_add(&conn->head, &handle->conns.head);
    }
    
#ifdef DEBUG
    if (!list_empty(&handle->conns.head)) {
        pr_debug("dump nodes...\n");
        struct esp01s_connection *cursor;
        list_for_each_entry(cursor, &handle->conns.head, head) {
            pr_debug("node address : %p\n", cursor);
            pr_debug("conn id : %d\n", cursor->id);
        }
    }
#endif
    
    if (len >= 1) { /* we got some connections from client */
        pr_debug("we got some connections from client\n");
    } else {
        pr_debug("there haven't any client connected to the server! nothing to be done\n");
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
    
    if (!list_empty(&handle->conns.head)) {
        pr_debug("there are some connections to send data\n");
        struct esp01s_connection *p_tmp_conn;
        list_for_each_entry(p_tmp_conn, &handle->conns.head, head) {
            pr_debug("%p, sending content to conn->id : %d\n", p_tmp_conn, p_tmp_conn->id);
            if (0 == strcmp(ip, p_tmp_conn->addr)) {
                ESP8266_SEND_CMD(
                            ESP8266_CMD_AT_CIPSEND \
                            "%d,%d",
                            p_tmp_conn->id, length
                );
                __esp01s_send_data(INDEX_HTML_CONTENT);
            }
        }
    }
}

void esp01s_server_broadcast(struct esp01s_handle *handle,
                            uint16_t length,
                            char *content)
{
    pr_debug("---length : %d\n", length);
    /* send content to all connected clients,
     * need call `esp01s_server_status` first
     * to query connections
     */
    esp01s_server_status(handle);

    if (!list_empty(&handle->conns.head)) {
        pr_debug("there are some connections to send data\n");
        struct esp01s_connection *p_tmp_conn;
        list_for_each_entry(p_tmp_conn, &handle->conns.head, head) {
            pr_debug("%p, sending content to conn->id : %d\n", p_tmp_conn, p_tmp_conn->id);
            ESP8266_SEND_CMD(
                        ESP8266_CMD_AT_CIPSEND \
                        "%d,%d",
                        p_tmp_conn->id, length
            );
            __esp01s_send_data(INDEX_HTML_CONTENT);
        }
    }
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
    esp01s_set_echo_enabled(handle, false);
    esp01s_server_start(handle);
    esp01s_server_listen_on(handle, DEFAULT_ESP8266_SERVER_PORT, true);

    /* send content */
    esp01s_server_broadcast(handle,
                           strlen(INDEX_HTML_CONTENT),
                           INDEX_HTML_CONTENT);
    // esp01s_server_status(handle);
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
    
    INIT_LIST_HEAD(&p_correct_handle->conns.head);
    INIT_LIST_HEAD(&p_correct_handle->args.kv.head);
    
    p_correct_handle->initialized = ESP8266_STATUS_INITIALIZED;
    esp01s_run_config(p_correct_handle);
    
    pr_debug("esp01s is initialized\n");
}