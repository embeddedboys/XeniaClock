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

// #include <common/init.h>

#include <linux/init.h>

#include <common/conf.h>
#include <common/tools.h>
#include <common/vals.h>

#include "lib/printk.h"

#include "i2c/native_i2c.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#define DEFAULT_I2C_IFCE        i2c0

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int i2c_bus_scan(i2c_inst_t *i2c)
{
    if (!i2c)
        i2c = DEFAULT_I2C_IFCE;

    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(i2c, addr, &rxdata, 1, false);

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
    return 0;
}

void i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t val)
{
    // printk("i2c_write_reg\n");
    uint16_t buf = val << 8 | reg;
    i2c_write_blocking(DEFAULT_I2C_IFCE, addr, (uint8_t *)&buf, sizeof(buf), false);
}

uint8_t i2c_read_reg(uint8_t addr, uint8_t reg)
{
    // printk("i2c_read_reg\n");
    uint8_t val = 0;
    i2c_write_blocking(DEFAULT_I2C_IFCE, addr, &reg, sizeof(reg), true);
    i2c_read_blocking(DEFAULT_I2C_IFCE, addr, &val, sizeof(val), false);
    return val;
}

// __deprecated_subsys_initcall(native_i2c_init);
static int __init native_i2c_init(void)
{
    // printk("native_i2c_init, initializing i2c bus ...\n");
    pr_debug("native_i2c_init, initializing i2c bus ...\n");

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