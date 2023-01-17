/**
 * @file settings.c
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

#include "common/init.h"
#include "common/module.h"

#include "common/tools.h"
#include "common/settings.h"

#include "../lvgl/lvgl.h"

static lv_obj_t *ui_EpinkScreenSettings;

xc_time_format_t g_xc_time_format;
xc_time_format_t xc_get_time_format(void)
{
    return g_xc_time_format;
}
void xc_set_time_format(xc_time_format_t format)
{

    g_xc_time_format = format;
    switch (format) {
    case TIME_FORMAT_12_HOUR:
        break;
    case TIME_FORMAT_24_HOUR:
        break;
    case TIME_FORMAT_HOUR_MIN:
        break;
    case TIME_FORMAT_HOUR_MIN_SEC:
        break;
    default:
        break;
    }
}

xc_disp_flush_mode_t g_xc_disp_flush_mode;
xc_disp_flush_mode_t xc_get_disp_flush_mode(void)
{
    return g_xc_disp_flush_mode;
}
void xc_set_disp_flush_mode(xc_disp_flush_mode_t mode)
{
    g_xc_disp_flush_mode = mode;
    switch (mode) {
    case DISP_FLUSH_MODE_FULL:
        pr_debug("setting disp flush mode to full flush\n");
        break;
    case DISP_FLUSH_MODE_PART:
        pr_debug("setting disp flush mode to part flush\n");
        break;
    default:
        break;
    }
}

/* give default settings */
static int xc_settings_init(void)
{
    xc_set_disp_flush_mode(DISP_FLUSH_MODE_FULL);
}

rootfs_initcall(xc_settings_init);