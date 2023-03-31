/**
 * @file main.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-18
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
#include "uart.h"
#include "i2c.h"

void interface_init(void)
{
    P_SW2 = 0;

    /* P32 P33 as i2c */
    P_SW2 = 0x80 | 0x30;
}

void system_init(void)
{
    MCLKOCR |= 0x80;

    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;

    interface_init();

    uart_init();
    i2c_init();
    ES = 1;
    EA = 1;
}

void delay_50ms()       //@11.0592MHz
{
    unsigned char i, j, k;

    i = 3;
    j = 207;
    k = 28;
    do {
        do {
            while (--k);
        } while (--j);
    } while (--i);
}

void delay_10ms()       //@11.0592MHz
{
    unsigned char i, j;

    i = 144;
    j = 157;
    do {
        while (--j);
    } while (--i);
}

static void power_on_once(void)
{
    /* I/O */
    P5M0 = 0x00;
    P5M1 = 0x00;

    P55 = 1;
    // delay_50ms();
    P55 = 0;
    delay_50ms();
    P55 = 1;
    // delay_50ms();

    /* OD */
    P5M0 |= (1 << 5);
    P5M1 |= (1 << 5);
}

static void power_off(void)
{
    /* I/O */
    P5M0 = 0x00;
    P5M1 = 0x00;

    P55 = 0;
    delay_50ms();
    P55 = 1;
    delay_10ms();

    P55 = 0;
    delay_50ms();
    P55 = 1;
    delay_10ms();

    /* OD */
    P5M0 |= (1 << 5);
    P5M1 |= (1 << 5);
}

static void blink(void)
{
    P32 = 1;
    delay_50ms();
    P32 = 0;
    delay_50ms();
}

static void power_on_off_test()
{
    P5M0 |= (1 << 5);
    P5M1 |= (1 << 5);

    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();

    power_on_once();

    int blink_time = 10;
    while (blink_time--) {
        blink();
    };

    power_off();

    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();

    power_on_once();

    blink_time = 10;
    while (blink_time--) {
        blink();
    };

    power_off();
}

/* TODO: finish this usb hot-plug detection */
static void usb_state_test(void)
{
    P5M0 |= (1 << 5);
    P5M1 |= (1 << 5);

    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();
    delay_50ms();

    power_on_once();

    int usb_state = 0;
    while (1) {
        // usb_state = P54;
        if (P54) {
            /* usb plugged in */
            P32 = 0;
            // delay_10ms();
        } else {
            /* usb plugged out */
            P32 = 1;
            // delay_10ms();
        }
    };
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    system_init();
    P5PU &= ~(0x1 << 4);
    // power_on_off_test();
    power_on_once();
    // usb_state_test();

    while (1) {
        // uart_send('a');
        // uart_send_str("Hello, world!\n");
        // i2c_start();
        // i2c_test();
        // delay_50ms();
        // delay_50ms();
        // delay_50ms();
        // delay_50ms();
        if (P54) {
            uart_send('1');
        } else {
            uart_send('0');
        }
    };

    return 0;
}