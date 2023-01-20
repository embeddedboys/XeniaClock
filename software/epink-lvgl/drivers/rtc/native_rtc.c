/**
 * @file rtc_host.c
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

#include "rtc/native_rtc.h"
#include "pico/types.h"

void (*p_rtc_device_set_time)(datetime_t t);
datetime_t (*p_rtc_device_get_time)();

void rtc_host_set_datetime(datetime_t *time)
{
    rtc_set_datetime(time);
    /* clk_sys is >2000x faster than clk_rtc, so datetime is not updated immediately when
     * rtc_get_datetime() is called.
     *
     * tbe delay is up to 3 RTC clock cycles (which is 64us with the default clock settings)
     */
    busy_wait_us(64);
}

datetime_t rtc_host_get_datetime()
{
    datetime_t t;
    rtc_get_datetime(&t);
    // /* clk_sys is >2000x faster than clk_rtc, so datetime is not updated immediately when
    //  * rtc_get_datetime() is called.
    //  *
    //  * tbe delay is up to 3 RTC clock cycles (which is 64us with the default clock settings)
    //  */
    // sleep_us(64);
    return t;
}

void rtc_host_init()
{
    datetime_t *p_time;
    rtc_init();

    datetime_t default_t = {
        .year = 2022,
        .month = 11,
        .day = 17,
        .dotw = 4,
        .hour = 17,
        .min = 38,
        .sec = 29,
    };

    p_time = &default_t;

    if (p_rtc_device_get_time != NULL) {
        *p_time = p_rtc_device_get_time();   /* trying to require rtc device */
        rtc_host_set_datetime(p_time);
    } else {
        rtc_host_set_datetime(p_time);
    }
}
