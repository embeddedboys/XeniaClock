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
#include "hardware/pwm.h"

/* x.X colorful black X.x */
#define RGB24_COLOR_ZHU_MO  0x3a3a3f
#define RGB24_COLOR_YA      0x121115
#define RGB24_COLOR_AN      0x293d44
#define RGB24_COLOR_LI      0x51452a

#define RGB24_COLOR_GREEN   0x95c194
#define RGB24_COLOR_RED     0xf57c69

#define WS2812B_DIN 25
#define WS2812B_NUM 4

/* TODO: Replace data output signal with PWM or others */

static __noinline void _delay_us(double __us)
{
    // uint32_t __count=(uint32_t)(__us/0.008)-3; // 8ns per cycle for 125MHz, from experimentation remove 3cycles for overhead
    uint32_t __count = (uint32_t)(__us / 0.008) - 15; // 8ns per cycle for 125MHz, from experimentation remove 3cycles for overhead
    busy_wait_at_least_cycles(__count);
}

static __noinline void _delay_ns(uint32_t ns)
{
    // cycles = ns * clk_sys_hz / 1,000,000,000
    uint32_t cycles = ns * (clock_get_hz(clk_sys) >> 16u) / (1000000000u >> 16u);
    busy_wait_at_least_cycles(cycles);
}

static  void ws2812b_write_0(void)
{
    // gpio_put(WS2812B_DIN, 0);
    gpio_put(WS2812B_DIN, 1);
    _delay_us(0.35);
    gpio_put(WS2812B_DIN, 0);
    _delay_us(0.7);
}

static  void ws2812b_write_1(void)
{
    // gpio_put(WS2812B_DIN, 0);
    gpio_put(WS2812B_DIN, 1);
    _delay_us(0.8);
    gpio_put(WS2812B_DIN, 0);
    _delay_us(0.6);
}

static  void ws2812b_reset(void)
{
    gpio_put(WS2812B_DIN, 1);
    gpio_put(WS2812B_DIN, 0);
    busy_wait_us_32(40);
    gpio_put(WS2812B_DIN, 1);
}

static uint32_t rgb2grb(uint32_t rgb)
{
    // uint8_t r,g,b;

    // r = rgb >> 16;
    // g = (rgb & 0xff00) >> 8;
    // b = rgb & 0xff;

    return ((rgb & 0xff00) << 8) | ((rgb & 0xff0000) >> 8) | (rgb & 0xff);
}

/* TODO: users doesn't want to know how the color bits arrayed,
 * just leave this work for us */
static void ws2812b_write_rgb(uint32_t rgb, int leds)
{
    /* mask to 24bit */
    rgb &= 0xFFFFFF;

    uint32_t grb = ((rgb & 0xff00) << 8) | ((rgb & 0xff0000) >> 8) | (rgb & 0xff);

    while (leds--) {
        for (int i = 23; i >= 0; i--) {
            if (grb & (1 << i))
                ws2812b_write_1();
            else
                ws2812b_write_0();
        }
    }
}

static void ws2812b_init(void)
{
    gpio_init(WS2812B_DIN);
    gpio_set_dir(WS2812B_DIN, GPIO_OUT);

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(WS2812B_DIN, GPIO_FUNC_PWM);


    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(WS2812B_DIN);
    pwm_set_enabled(slice_num, true);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 500);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 250);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);

}

void ws2812b_test(void)
{
    ws2812b_init();
    uint32_t rgb = 0xff7802;
    int count = WS2812B_NUM;

    while (1) {
        // ws2812b_write_0();
        // ws2812b_write_1();
    }

    for (;;) {
        ws2812b_write_rgb(rgb, WS2812B_NUM);
        ws2812b_reset();
    }
}