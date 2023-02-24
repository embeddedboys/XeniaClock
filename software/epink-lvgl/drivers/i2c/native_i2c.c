/**
 * @file native_i2c.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
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

#include <common/init.h>
#include <common/conf.h>

#include "i2c/native_i2c.h"
#include "common/tools.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "common/vals.h"
#include "pico/binary_info.h"

#define DEFAULT_I2C_IFCE        i2c0

void i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    i2c_write_blocking(DEFAULT_I2C_IFCE, addr, buf, 2, false);
}

uint8_t i2c_read_reg(uint8_t addr, uint8_t reg)
{
    uint8_t wbuf[1] = {reg}, rbuf[1];
    i2c_write_blocking(DEFAULT_I2C_IFCE, addr, wbuf, 1, true);
    i2c_read_blocking(DEFAULT_I2C_IFCE, addr, rbuf, 1, false);
    return rbuf[0];
}

static int native_i2c_init(void)
{
    i2c_init(DEFAULT_I2C_IFCE, DEFAULT_I2C_SPEED);
    gpio_set_function(DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    bi_decl(bi_2pins_with_func(DEFAULT_I2C_SDA_PIN,
                            DEFAULT_I2C_SCL_PIN,
                            GPIO_FUNC_I2C));
    gpio_pull_up(DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(DEFAULT_I2C_SCL_PIN);

    return 0;
}

subsys_initcall(native_i2c_init);