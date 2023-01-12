/**
 * @file vals.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
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

#ifndef __VALS_H
#define __VALS_H

#define DEFAULT_SYS_CLOCK   ()
// #define DEFAULT_SPI_SPEED (50000000)    // 50MHz
#define DEFAULT_SPI_SPEED (125000000)    // 12-125MHz
#define DEFAULT_I2C_SPEED (400000)      // 400KHz
#define DEFAULT_UART_SPEED (115200)

#define BATTERY_PRECENT_DEAD    (0)
#define BATTERY_PERCENT_LOW     (25)
#define BATTERY_PERCENT_HALT    (50)
#define BATTERY_PERCENT_GOOD    (75)
#define BATTERY_PERCENT_FULL    (100)

#define SECOND(x)               (x)
#define MILLISECOND(x)          (x)
#define MICROSECOND(x)          (x)

#define SECOND_UPDATE_STEP    (5)
#define SECONDS_IN_MINUTE     (60)
#define MINUTES_IN_HOUR       (60)
#define HOURS_IN_DAY          (24)

#define REFRESH_SPEED_FAST      (2000)
#define REFRESH_SPEED_NORMAL    (5000)
#define REFRESH_SPEED_SLOW      (9000)
#define REFRESH_SPEED_USER      (0x4)

/* time in millisecond to call a sync clock, make it default to 10 minutes */
#define TIME_SYNC_PERIOD        (10 * 60 * 1000) /* in ms */
#define GLOBAL_REFRESH_PERIOD   (60) /* in frame count */
#define FULL_REFRESH_FACTOR     (5)

#endif