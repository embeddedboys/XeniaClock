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

static int ft6x36_init(void)
{
    
    return 0;
}

static void ft6x36_exit(void)
{

}

module_init(ft6x36_init);
module_exit(ft6x36_exit);