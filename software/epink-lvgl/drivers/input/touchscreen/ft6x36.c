/**
 * @file FT6X36.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief FocalTech FT6X36U Self-Capacitive Touch Panel Controller
 * @version 0.1
 * @date 2023-01-10
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

#include <common/module.h>

#include <hardware/gpio.h>
#include <i2c/native_i2c.h>
#include <input/input.h>

#include <input/touchscreen/ft6x36.h>

__u8 ft6x36_read_reg(__u8 addr, __u8 reg)
{
    return i2c_read_reg(addr, reg);
}

void ft6x36_write_reg(__u8 addr, __u8 reg, __u8 val)
{
    i2c_write_reg(addr, reg, val);
}

static void ft6x36_hw_init(void)
{
    /* interrupt gpio initialize */
    gpio_init(FT6X36_INT_PIN);
    gpio_set_dir(FT6X36_INT_PIN, GPIO_IN);

    /* reset gpio initialize */
    gpio_init(FT6X36_RST_PIN);
    gpio_set_dir(FT6X36_RST_PIN, GPIO_OUT);
    gpio_put(FT6X36_RST_PIN, 1);

    /* make a device reset */
    gpio_put(FT6X36_RST_PIN, 0);
    busy_wait_ms(2);
    gpio_put(FT6X36_RST_PIN, 1);

    /* set to working mode */
    ft6x36_set_device_mode(0x00);

    /* threshold setting */
    ft6x36_set_threshold_group(0x16);

    /* set control mode to Keeping Active Mode */
    ft6x36_set_ctrl_mode(0x00);

    /* set to polling mode */
    ft6x36_set_g_mode(0x00);

    /* set report rate in active mode */
    ft6x36_set_period_active(0x01);
}

bool ft6x36_is_pressed()
{
    /* only used in polling mode, this int pin will going to low
     * if there a touch data comes and keep high when it's finished */
    return !gpio_get(FT6X36_INT_PIN);
}

static int ft6x36_init(void)
{
    /* hardware initialize */
    ft6x36_hw_init();

    return 0;
}

static void ft6x36_exit(void)
{

}

void ft6x36_test(void)
{
    __u8 id = ft6x36_read_focaltech_id();
    pr_debug("focaltech id : %02x\n", id);
    
    ft6x36_set_g_mode(0x00);
}

module_init(ft6x36_init);
module_exit(ft6x36_exit);