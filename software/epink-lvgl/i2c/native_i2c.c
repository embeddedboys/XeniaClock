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

#include "native_i2c.h"
#include "common/tools.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "common/vals.h"
#include "pico/binary_info.h"

void i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}

uint8_t i2c_read_reg(uint8_t addr, uint8_t reg)
{
    uint8_t wbuf[1] = {reg}, rbuf[1];
    i2c_write_blocking(i2c_default, addr, wbuf, 1, true);
    i2c_read_blocking(i2c_default, addr, rbuf, 1, false);
    return rbuf[0];
}

void native_i2c_init(void)
{
    i2c_init(i2c_default, DEFAULT_I2C_SPEED);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN,
                            PICO_DEFAULT_I2C_SCL_PIN,
                            GPIO_FUNC_I2C));
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    pr_debug("registering native i2c function pointer\n");
    p_i2c_write_reg = i2c_write_reg;
    p_i2c_read_reg = i2c_read_reg;
}