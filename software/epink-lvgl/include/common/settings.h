/**
 * @file settings.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
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

#ifndef __SETTINGS_H
#define __SETTINGS_H

typedef enum {
    TIME_FORMAT_12_HOUR = 0x00,
    TIME_FORMAT_24_HOUR = 0x01,
    
    TIME_FORMAT_HOUR_MIN     = 0x02,
    TIME_FORMAT_HOUR_MIN_SEC = 0x03,
} xc_time_format_t;
extern xc_time_format_t g_xc_time_format;
xc_time_format_t xc_get_time_format(void);
void xc_set_time_format(xc_time_format_t format);

typedef enum {
    DISP_FLUSH_MODE_PART = 0x00,
    DISP_FLUSH_MODE_FULL = 0x01,
} xc_disp_flush_mode_t;
extern xc_disp_flush_mode_t g_xc_disp_flush_mode;
xc_disp_flush_mode_t xc_get_disp_flush_mode(void);
void xc_set_disp_flush_mode(xc_disp_flush_mode_t mode);

#endif  /* __SETTINGS_H */
