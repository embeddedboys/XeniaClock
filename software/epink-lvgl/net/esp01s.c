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

#define ESP01S_CMD(cmd)     cmd "\r\n"
#define ESP01S_CMD_AT       ESP01S_CMD("AT")
#define ESP01S_CMD_INFO     ESP01S_CMD("AT+GMR")
// AT+CWJAP="redmiax3000","h2231841."
// AT+PING="192.168.31.57"
void esp01s_test()
{
    uint8_t rbuf[128];
    char command[64];

    sprintf(command, "AT+CWJAP=\"%s\",\"%s\"\r\n", DEFAULT_WIFI_SSID, DEFAULT_WIFI_PSK);

    uart_puts(uart1, "AT+CWMODE=1\r\n");
    // uart_read_blocking(uart1, rbuf, 128);
    uart_puts(uart1, "AT+CWJAP=\"redmiax3000\",\"h2231841.\"\r\n");
    // uart_read_blocking(uart1, rbuf, 128);
}
