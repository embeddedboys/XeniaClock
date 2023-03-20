/**
 * @file bmp280.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-14
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

#include <stdlib.h>

#include <linux/init.h>
#include <linux/module.h>

#include <linux/err.h>
#include <linux/errno.h>

#include "common/tools.h"
#include "common/bitops.h"

#include "i2c/native_i2c.h"

#define BMP280_ADDR 0x76

#define BMP280_ID   0x58

#define BMP280_REG_ID      0xD0
#define BMP280_REG_RESET        0xE0

#define BMP280_CMD_STATUS       0xF3
#define BMP280_STATUS_MEASURING BIT(3)
#define BMP280_STATUS_IM_UPDATE BIT(0)

#define BMP280_REG_CTRL_MEAS    0xF4

#define BMP280_REG_CONFIG       0xF5

#define BMP280_CMD_PRESS_MSB    0xF7
#define BMP280_CMD_PRESS_LSB    0xF8
#define BMP280_CMD_PRESS_XLSB   0xF9

#define BMP280_CMD_TEMP_MSB    0xFA
#define BMP280_CMD_TEMP_LSB    0xFB
#define BMP280_CMD_TEMP_XLSB   0xFC

#define DRV_NAME    "bmp280"

enum bmp280_power_mode {
    BMP280_PWR_MODE_SLEEP  = 0x00,
    BMP280_PWR_MODE_FORCED = 0x01,
    BMP280_PWR_MODE_NORMAL = 0x03,
};

struct bmp280_data {
    /* usually fixed value, read once */
    u16 dig_T1;
    s16 dig_T2, dig_T3;
    
    s32 var1, var2, t_fine;
    
    s32 adc_T;
    u8 msb, lsb, xlsb;
};

struct bmp280_config {
    /* in register 0xf4 `ctrl_meas` */
    u8      osrs_t;
    u8      osrs_p;
    u8      pwr_mode;           /* working mode */
    
    /* in register 0xf5 `config` */
    u8      t_sb;
    u8      filter;
    u8      spi3w_en;
};

struct bmp280 {
    int     id;             /* used to specifiy which kind of variant */
    
    s32     pressure;       /* the result of pressure */
    s32     temperature;    /* the result of temperature */
    
    struct bmp280_config    cfg;
    struct bmp280_data      raw; /* the raw data reading from sensor */
};

static struct bmp280 *g_bmp280;

int bmp280_read_id(void)
{
    int id = i2c_read_reg(BMP280_ADDR, BMP280_REG_ID);
    pr_debug("id : 0x%02x\n", id);

    return id;
}

int bmp280_read_press(void)
{
    u8 msb, lsb, xlsb;
    u16 press;
    
    msb = i2c_read_reg(BMP280_ADDR, BMP280_CMD_PRESS_MSB);
    lsb = i2c_read_reg(BMP280_ADDR, BMP280_CMD_PRESS_LSB);
    
    press = msb << 8 | lsb;
    
    pr_debug("raw press : %d\n", press);
    return press;
}

s32 bmp280_read_temp(void)
{
    // s32 var1, var2, adc_T, t_fine, T;
    // u16 dig_T1;
    // s16 dig_T2, dig_T3;
    // u8 msb, lsb, xlsb;
    
    g_bmp280->raw.dig_T1 = i2c_read_reg(BMP280_ADDR, 0x89) << 8 | i2c_read_reg(BMP280_ADDR,
                                                                              0x88);
    g_bmp280->raw.dig_T2 = i2c_read_reg(BMP280_ADDR, 0x8B) << 8 | i2c_read_reg(BMP280_ADDR, 0x8A);
    g_bmp280->raw.dig_T3 = i2c_read_reg(BMP280_ADDR, 0x8F) << 8 | i2c_read_reg(BMP280_ADDR, 0x8E);
    
    g_bmp280->raw.msb = i2c_read_reg(BMP280_ADDR, BMP280_CMD_TEMP_MSB);
    g_bmp280->raw.lsb = i2c_read_reg(BMP280_ADDR, BMP280_CMD_TEMP_LSB);
    g_bmp280->raw.xlsb = i2c_read_reg(BMP280_ADDR, BMP280_CMD_TEMP_XLSB) >> 4;
    
    g_bmp280->raw.adc_T = g_bmp280->raw.msb << 12 | g_bmp280->raw.lsb << 4 | g_bmp280->raw.xlsb;
    
    /* calcualting */
    // var1 = ((double)adc_T)/16384.0 - ((double)dig_T1/1024.0) * ((double)dig_T2);
    // var2 = ((double)adc_T)/31072.0 - (((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0) - (((double)dig_T1)/8192.0) * ((double)dig_T3);
    g_bmp280->raw.var1 = ((((g_bmp280->raw.adc_T >> 3) - ((s32)g_bmp280->raw.dig_T1 << 1))) * ((s32)g_bmp280->raw.dig_T2)) >> 11;
    g_bmp280->raw.var2 = (((((g_bmp280->raw.adc_T >> 4) - ((s32)g_bmp280->raw.dig_T1)) * ((g_bmp280->raw.adc_T >> 4) - ((s32)g_bmp280->raw.dig_T1))) >> 12) *
            ((s32)g_bmp280->raw.dig_T3)) >> 14;
    g_bmp280->raw.t_fine = g_bmp280->raw.var1 + g_bmp280->raw.var2;
    
    /* format etc. 2516 -> 25.16 °C  */
    g_bmp280->temperature = (g_bmp280->raw.t_fine * 5 + 128) >> 8;
    
    pr_debug(" Temp : %02d.%02d *C\n", g_bmp280->temperature / 100, g_bmp280->temperature % 100);
    
    return g_bmp280->temperature;
}

static void bmp280_hw_init(void)
{
    if (!g_bmp280) {
        pr_debug("bmp280 has no memory!\n");
        return;
    }
    g_bmp280->id = bmp280_read_id();
    if (g_bmp280->id == BMP280_ID) {
        pr_debug("device : bmp280 detected!\n");
    }

    /* power-on reset */
    i2c_write_reg(BMP280_ADDR, BMP280_REG_RESET, 0xB6);
    
    /* eanble measurements, set work mode to normal */
    u8 ctrl_meas = BIT(5) | BIT(2) | 3;
    i2c_write_reg(BMP280_ADDR, BMP280_REG_CTRL_MEAS, ctrl_meas);
}

static int __init bmp280_drv_init(void)
{
    pr_debug("initializing bmp280 ...\n");

    g_bmp280 = calloc(sizeof(struct bmp280), 1);
    if (!g_bmp280)
        return -ENOMEM;

    bmp280_hw_init();
}
module_init(bmp280_drv_init);

static void __exit bmp280_drv_exit(void)
{
    pr_debug("bmp280 exiting ...\n");
}
module_exit(bmp280_drv_exit);