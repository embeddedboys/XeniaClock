/**
 * @file leds-ws2812b.c
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

#include <FreeRTOS.h>
#include "task.h"

#include "pico/stdlib.h"
#include "hardware/clocks.h"

#define WS2812B_DIN 25
#define WS2812B_NUM 4

/* TODO: Replace data output signal with PWM or others */

static __noinline void _delay_us(double __us)
{
    // uint32_t __count=(uint32_t)(__us/0.008)-3; // 8ns per cycle for 125MHz, from experimentation remove 3cycles for overhead
    uint32_t __count=(uint32_t)(__us/0.008)-20; // 8ns per cycle for 125MHz, from experimentation remove 3cycles for overhead
    busy_wait_at_least_cycles(__count);
}

static __noinline void _delay_ns(uint32_t ns) {
    // cycles = ns * clk_sys_hz / 1,000,000,000
    uint32_t cycles = ns * (clock_get_hz(clk_sys) >> 16u) / (1000000000u >> 16u);
    busy_wait_at_least_cycles(cycles);
}

static inline void ws2812b_write_0(void)
{
    gpio_put(WS2812B_DIN, 0);
    gpio_put(WS2812B_DIN, 1);
    _delay_us(0.4);
    gpio_put(WS2812B_DIN, 0);
    _delay_us(0.85);
}

static inline void ws2812b_write_1(void)
{
    gpio_put(WS2812B_DIN, 0);
    gpio_put(WS2812B_DIN, 1);
    _delay_us(0.85);
    gpio_put(WS2812B_DIN, 0);
    _delay_us(0.4);
}

static inline void ws2812b_reset(void)
{
    gpio_put(WS2812B_DIN, 1);
    gpio_put(WS2812B_DIN, 0);
    busy_wait_us_32(50);
    gpio_put(WS2812B_DIN, 1);
}

static inline uint32_t rgb2grb(uint32_t rgb)
{
    // uint8_t r,g,b;
    
    // r = rgb >> 16;
    // g = (rgb & 0xff00) >> 8;
    // b = rgb & 0xff;
    
    return ((rgb & 0xff00) << 8) | ((rgb & 0xff0000) >> 8) | (rgb & 0xff);;
}

/* TODO: users doesn't want to know how the color bits arrayed,
 * just leave this work for us */
static void ws2812b_write_rgb(uint32_t rgb)
{
    /* mask to 24bit */
    rgb &= 0xFFFFFF;

    // uint32_t grb = rgb2grb(rgb);

    // for(int i=23;i>=0;i--) {
    //     if ((grb >> i)  & 0x01)
    //         ws2812b_write_1();
    //     else
    //         ws2812b_write_0();
    // }
    uint8_t byte;
    for (int i=7, byte=((rgb & 0x00ff00) >> 8);i>=0;i--)
    {
        if (byte >> i)
            ws2812b_write_1();
        else
            ws2812b_write_0();
    }

    for (int i=7, byte=((rgb & 0xff0000) >> 16);i>=0;i--)
    {
        if (byte >> i)
            ws2812b_write_1();
        else
            ws2812b_write_0();
    }

    for (int i=7, byte=((rgb & 0xff));i>=0;i--)
    {
        if (byte >> i)
            ws2812b_write_1();
        else
            ws2812b_write_0();
    }
}

static void ws2812b_init(void)
{
    gpio_init(WS2812B_DIN);
    gpio_set_dir(WS2812B_DIN, GPIO_OUT);
}

void ws2812b_test(void)
{
    ws2812b_init();
    for (;;) {
        int count = WS2812B_NUM;
        uint32_t rgb = 0xffff33;
        while (count--) {
            // ws2812b_write_rgb(0xff0000);
            // ws2812b_write_rgb(0x00ff00);
            // ws2812b_write_rgb(0x0000ff);
            ws2812b_write_rgb(rgb);
        }
        ws2812b_reset();
    }
}