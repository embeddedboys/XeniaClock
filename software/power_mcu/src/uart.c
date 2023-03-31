/**
 * @file uart.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-08
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

#include "stc8g.h"

// #define BRT     (65536 - FOSC / 115200 / 4)

unsigned char busy;
// char wptr;
// char rptr;
// char buffer[16];

interrupt_declear(uart_isr, 4)
{
    if (TI) {
        TI = 0;
        busy = 0;
    }

    /* we don't do uart recv by now. */
    if (RI) {
        RI = 0;
        // buffer[wptr++] = SBUF;
        // wptr &= 0x0f;
    }
}

void uart_init()
{
    SCON = 0x50;
    AUXR |= 0x40;
    AUXR |= 0xfe;
    TMOD &= 0x0f;
    TL1 = 0xe8;
    TH1 = 0xff;
    ET1 = 0;
    TR1 = 1;
}

void uart_send(char c)
{
    while(busy);
    busy = 1;
    SBUF = c;
}

void uart_send_str(const char *str)
{
    const char *tmp = str;

    while(*tmp) {
        uart_send(*tmp++);
    }
}
