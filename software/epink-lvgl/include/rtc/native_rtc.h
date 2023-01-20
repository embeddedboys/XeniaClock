/**
 * @file rtc.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
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

#pragma once

#ifndef __NATIVE_RTC_H
#define __NATIVE_RTC_H

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "pico/types.h"
#include "lvgl/lvgl.h"

struct native_rtc_data {
    uint32_t year;
    uint32_t mon;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
};

struct native_rtc_config {
    uint8_t hour_mode;
};

struct native_rtc_handle {
    struct native_rtc_config cfg;
    struct native_rtc_data data;
};

#define RTC_DEVICE_DS3231 0x00
#define RTC_DEVICE_DS1307 0x01

#ifndef DEFAULT_RTC_DEVICE
    #define DEFAULT_RTC_DEVICE RTC_DEVICE_DS1307
#endif

extern void (*p_rtc_device_set_time)(datetime_t t);
extern datetime_t (*p_rtc_device_get_time)();
void rtc_device_init();

void rtc_host_init();
void rtc_host_set_datetime(datetime_t *time);
datetime_t rtc_host_get_datetime();

#endif /* __NATIVE_RTC_H */
