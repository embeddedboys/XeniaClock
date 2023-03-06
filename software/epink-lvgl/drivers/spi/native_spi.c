/**
 * @file native_spi.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
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

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "spi/native_spi.h"
#include "common/vals.h"
#include "pico/binary_info.h"
#include "lib/printk.h"

subsys_initcall(native_spi_init);

void cs_select(uint16_t pin)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(pin, 0);
    asm volatile("nop \n nop \n nop");
}

void cs_deselect(uint16_t pin)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(pin, 1);
    asm volatile("nop \n nop \n nop");
}

void spi_write8(uint8_t val, uint8_t cs_pin)
{
    uint8_t buf[1] = {val};

    cs_select(cs_pin);
    spi_write_blocking(spi_default, buf, 1);
    cs_deselect(cs_pin);
}

void spi_write16(uint16_t val, uint8_t cs_pin)
{
    uint16_t buf[1] = {val};
    cs_select(cs_pin);
    spi_write16_blocking(spi_default, buf, 1);
    cs_deselect(cs_pin);
}

void spi_transfer(uint8_t *buf, int size, uint8_t cs_pin)
{
    cs_select(cs_pin);
    spi_write_blocking(spi_default, buf, size);
    cs_deselect(cs_pin);
}

static int native_spi_init(void)
{
    printk("%s, initializing spi bus ...\n", __func__);
    spi_init(spi_default, DEFAULT_SPI_SPEED);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    /* could check this using `picotools` */
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN,
                               GPIO_FUNC_SPI));
    return 0;
}
