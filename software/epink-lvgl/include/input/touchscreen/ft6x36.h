/**
 * @file ft6x36.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-11
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

#ifndef __FT6X36_H
#define __FT6X36_H

#include <i2c/native_i2c.h>

#include <common/types.h>
#include <common/bitops.h>

#define FT6X36_ADDRESS                  0x38

#define FT6X36_REG_DEV_MODE             0x00
#define FT6X36_REG_GEST_ID              0x01
#define FT6X36_REG_TD_STATUS            0x02

#define FT6X36_REG_P1_XH                0x03
#define FT6X36_REG_P1_XL                0x04
#define FT6X36_REG_P1_YH                0x05
#define FT6X36_REG_P1_YL                0x06
#define FT6X36_REG_P1_WEIGHT            0x07
#define FT6X36_REG_P1_MISC              0x08

#define FT6X36_REG_P2_XH                0x09
#define FT6X36_REG_P2_XL                0x0a
#define FT6X36_REG_P2_YH                0x0b
#define FT6X36_REG_P2_YL                0x0c
#define FT6X36_REG_P2_WEIGHT            0x0d
#define FT6X36_REG_P2_MISC              0x0e

#define FT6X36_REG_TH_GROUP             0x80
#define FT6X36_REG_TH_DIFF              0x85
#define FT6X36_REG_CTRL                 0x86
#define FT6X36_REG_TIMEENTERMONITOR     0x87
#define FT6X36_REG_PERIODACTIVE         0x88
#define FT6X36_REG_PERIODMONITOR        0x89
#define FT6X36_REG_RADIAN_VALUE         0x91
#define FT6X36_REG_OFFSET_LEFT_RIGHT    0x92
#define FT6X36_REG_OFFSET_UP_DOWN       0x93
#define FT6X36_REG_DISTANCE_LEFT_RIGHT  0x94
#define FT6X36_REG_DISTANCE_UP_DOWN     0x95
#define FT6X36_REG_DISTANCE_ZOOM        0x96

#define FT6X36_REG_LIB_VER_H            0xa1
#define FT6X36_REG_LIB_VER_L            0xa2
#define FT6X36_REG_CIPHER               0xa3
#define FT6X36_REG_G_MODE               0xa4
#define FT6X36_REG_PWR_MODE             0xa5
#define FT6X36_REG_FIRMWARE_ID          0xa6
#define FT6X36_REG_FOCALTECH_ID         0xa8
#define FT6X36_REG_RELEASE_CODE_ID      0xaf
#define FT6X36_REG_STATE                0xbc

#define FT6X36_PWR_MODE_ACTIVE          0x00
#define FT6X36_PWR_MODE_MONITOR         0x01
#define FT6X36_PWR_MODE_STANDBY         0x02
#define FT6X36_PWR_MODE_HIBERNATE       0x03

#define FT6X36_VENDID                   0x11
#define FT6206_CHIPID                   0x06
#define FT6236_CHIPID                   0x36
#define FT6336_CHIPID                   0x64

#define FT6X36_DEFAULT_THRESHOLD        0x16

#define FT6X36_INT_PIN  3
#define FT6X36_RST_PIN  2

__u8 ft6x36_read_reg(__u8 addr, __u8 reg);
void ft6x36_write_reg(__u8 addr, __u8 reg, __u8 val);

static inline __u8 ft6x36_read_device_mode(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_DEV_MODE);
}

static inline void ft6x36_set_device_mode(__u8 mode)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_DEV_MODE, mode);
}

static inline __u8 ft6x36_read_gest_id(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_GEST_ID);
}

static inline __u8 ft6x36_read_td_status(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_TD_STATUS);
}

static inline __u8 ft6x36_read_p1_xh(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_XH);
}

static inline __u8 ft6x36_read_p1_xl(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_XL);
}

static inline __u8 ft6x36_read_1st_event_flag(void)
{
    return (ft6x36_read_p1_xh() & GENMASK(7, 6)) >> 6;
}

static inline __s16 ft6x36_read_p1_x(void)
{
    return ((ft6x36_read_p1_xh() & 0x7) << 8) | ft6x36_read_p1_xl();
}

static inline __u8 ft6x36_read_p1_yh(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_YH);
}

static inline __u8 ft6x36_read_p1_yl(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_YL);
}

static inline __u8 ft6x36_read_1st_touch_id(void)
{
    return (ft6x36_read_p1_yh() & GENMASK(7, 4)) >> 4;
}

static inline __s16 ft6x36_read_p1_y(void)
{
    return ((ft6x36_read_p1_yh() & 0x7) << 8) | ft6x36_read_p1_yl();
}

static inline __u8 ft6x36_read_p1_weight(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_WEIGHT);
}

static inline __u8 ft6x36_read_p1_misc(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P1_MISC);
}

static inline __u8 ft6x36_read_p2_xh(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_XH);
}

static inline __u8 ft6x36_read_p2_xl(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_XL);
}

static inline __u8 ft6x36_read_2st_event_flag(void)
{
    return (ft6x36_read_p2_xh() & GENMASK(7, 6)) >> 6;
}

static inline __s16 ft6x36_read_p2_x(void)
{
    return ((ft6x36_read_p2_xh() & 0x7) << 8) | ft6x36_read_p2_xl();
}

static inline __u8 ft6x36_read_p2_yh(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_YH);
}

static inline __u8 ft6x36_read_p2_yl(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_YL);
}

static inline __s16 ft6x36_read_p2_y(void)
{
    return ((ft6x36_read_p2_yh() & 0x7) << 8) | ft6x36_read_p2_yl();
}

static inline __u8 ft6x36_read_p2_weight(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_WEIGHT);
}

static inline __u8 ft6x36_read_p2_misc(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_P2_MISC);
}

static inline void ft6x36_set_threshold_group(__u8 threshold)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_TH_GROUP, threshold);
}

static inline void ft6x36_set_threshold_diff(__u8 filter)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_TH_DIFF, filter);
}

static inline void ft6x36_set_ctrl_mode(__u8 mode)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_CTRL, mode);
}

static inline void ft6x36_set_time_enter_monitor(__u8 time)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_TIMEENTERMONITOR, time);
}

static inline void ft6x36_set_period_active(__u8 period)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_PERIODACTIVE, period);
}

static inline void ft6x36_set_period_monitor(__u8 period)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_PERIODMONITOR, period);
}

static inline void ft6x36_set_radian_value(__u8 val)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_RADIAN_VALUE, val);
}

/**
 * @brief set offset of moving left and right gesture
 *
 * @param offset maximum offset while moving left and moving right gesture
 */
static inline void ft6x36_set_offset_left_right(__u8 offset)
{

}

/**
 * @brief set offset of moving up and down gesture
 *
 * @param offset maximum offset while moving up and moving down gesture
 */
static inline void ft6x36_set_offset_up_down(__u8 offset)
{

}

static inline void ft6x36_set_distance_left_right(__u8 distance)
{

}

static inline void ft6x36_set_distance_up_down(__u8 distance)
{

}

static inline __u8 ft6x36_read_distance_zoom(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_DISTANCE_ZOOM);
}

static inline void ft6x36_set_distance_zoom(__u8 distance)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_DISTANCE_ZOOM, distance);
}

static inline __u8 ft6x36_read_lib_ver_h(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_LIB_VER_H);
}

static inline __u8 ft6x36_read_lib_ver_l(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_LIB_VER_L);
}

static inline __u8 ft6x36_read_cipher(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_CIPHER);
}

static inline __u8 ft6x36_read_g_mode(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_G_MODE);
}

static inline void ft6x36_set_g_mode(__u8 mode)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_G_MODE, mode);
}

static inline __u8 ft6x36_read_pwr_mode(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_PWR_MODE);
}

static inline void ft6x36_set_pwr_mode(__u8 mode)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_PWR_MODE, mode);
}

static inline __u8 ft6x36_read_firmware_id(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_FIRMWARE_ID);
}

static inline __u8 ft6x36_read_focaltech_id(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_FOCALTECH_ID);
}


static inline __u8 ft6x36_read_release_code(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_RELEASE_CODE_ID);
}

static inline __u8 ft6x36_read_state(void)
{
    return ft6x36_read_reg(FT6X36_ADDRESS, FT6X36_REG_STATE);
}

static inline void ft6x36_set_state(__u8 state)
{
    ft6x36_write_reg(FT6X36_ADDRESS, FT6X36_REG_STATE, state);
}

#endif /* __FT6X36_H */