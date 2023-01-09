/**
 * @file rtc_ds3231.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
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

#include "i2c/native_i2c.h"
#include "rtc/native_rtc.h"
#include <stdint.h>

#define DS3231_I2C_ADDR             0x68

#define DS3231_REG_CTL              0x0e
#define DS3231_REG_STAT             0x0f
#define DS3231_REG_AGING_OFFSET     0x10
#define DS3231_REG_TEMP_UB          0x11
#define DS3231_REG_TEMP_LB          0x12

enum {
    DS1307_REG_SECONDS = 0x00,
    DS1307_REG_MINUTES = 0x01,
    DS1307_REG_HOURS   = 0x02,
    DS1307_REG_DAY     = 0x03,
    DS1307_REG_DATE    = 0x04,
    DS1307_REG_MONTH   = 0x05,
    DS1307_REG_YEAR    = 0x06,
    DS1307_REG_CONTROL = 0x07,
    //RAM 56 Bytes
    DS1307_REG_RAM_00  = 0x08,
    DS1307_REG_RAM_55  = 0x3F,
};

extern lv_obj_t *ui_LabelTest;

static void ds3231_init()
{
    int rc;
    uint8_t val;

    /* enable clock, write zero into CH bit */
#if DEFAULT_RTC_DEVICE == RTC_DEVICE_DS1307
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val & 0x7f);
#elif DEFAULT_RTC_DEVICE == RTC_DEVICE_DS3231
    val = i2c_read_reg(DS3231_I2C_ADDR, DS3231_REG_CTL);
    i2c_write_reg(DS3231_I2C_ADDR, DS3231_REG_CTL, val & 0x7f);
#else
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val & 0x7f);
#endif

    /* set hour mode, 24-hour mode, when this bit changed,
     * a new value re-enterd is required
     */
    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS);
    i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val & 0x7f);
    
    /* 12-hour mode */
    // i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val | 0x40);
}

void __rtc_ds3231_set_time_hour(uint8_t hour)
{
    uint8_t val = 0, bit_ten = 0, bit_single = 0;
    if (hour != 0 && hour < 24) {
        bit_ten = hour / 10;
        bit_single = hour % 10;
        val |= (bit_ten << 4) & 0x3f | (bit_single & 0x0f);
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val);
    }
    else {
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS, val);
    }
}

void __rtc_ds3231_set_time_min(uint8_t min)
{
    uint8_t val = 0, bit_ten = 0, bit_single = 0;
    if (min != 0 && min < 60) {
        bit_ten = min / 10;
        bit_single = min % 10;
        val |= ((bit_ten << 4) & 0x7f | (bit_single & 0x0f));
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_MINUTES, val);
    }
    else {
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_MINUTES, val);
    }
}

void __rtc_ds3231_set_time_sec(uint8_t sec)
{
    uint8_t val = 0, bit_ten = 0, bit_single = 0;
    if (sec != 0 && sec < 60) {
        bit_ten = sec / 10;
        bit_single = sec % 10;
        val |= (bit_ten << 4) & 0x7f | (bit_single & 0x0f);
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val);
    }
    else {
        i2c_write_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS, val);
    }
}

void rtc_ds3231_set_time(datetime_t t)
{
    __rtc_ds3231_set_time_hour(t.hour);
    __rtc_ds3231_set_time_min(t.min);
    __rtc_ds3231_set_time_sec(t.sec);
}

/* TODO: The read ops from DS3231 should be brust
 * and fast (in 1 seconds), read all bytes in one time
 */
datetime_t rtc_ds3231_get_time()
{
    uint8_t val = 0;
    int rc;
    uint8_t hour = 0, minute = 0, second = 0;
    datetime_t ds3231_time;

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_HOURS);
    ds3231_time.hour = ((val & 0x3f) >> 4) * 10 + (val & 0x0f);

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_MINUTES);
    ds3231_time.min = ((val & 0x7f) >> 4) * 10 + (val & 0x0f);

    val = i2c_read_reg(DS3231_I2C_ADDR, DS1307_REG_SECONDS);
    ds3231_time.sec = ((val & 0x7f) >> 4) * 10 + (val & 0x0f);

    return ds3231_time;
}

void rtc_device_init()
{
    ds3231_init();

    p_rtc_device_set_time = rtc_ds3231_set_time;
    p_rtc_device_get_time = rtc_ds3231_get_time;
}
