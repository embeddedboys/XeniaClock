/**
 * @file timers.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-13
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

#include "hardware/rtc.h"
#include "hardware/timer.h"

#include "common/tools.h"
#include "common/vals.h"
#include "i2c/sensors/aht10.h"
#include "rtc/native_rtc.h"

#include "../lvgl/lvgl.h"
#include "../ui/ui.h"
#include "../ui/ui_comp.h"

extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_RollerMinute;
extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_LabelDate;
extern lv_obj_t *ui_LabelTips;

static uint16_t g_label_year   = 2023;
static uint8_t g_label_mon     = 1;
static uint8_t g_label_day     = 19;

/* Whew, we are getting off work! */
static uint8_t g_roller_hour   = 18;
static uint8_t g_roller_minute = 30;
static uint8_t g_roller_second = 0;

static struct repeating_timer g_roller_timer;

uint8_t xc_get_roller_time_hour()
{
    return g_roller_hour;
}

uint8_t xc_get_roller_time_minute()
{
    return g_roller_minute;
}

uint8_t xc_get_roller_time_second()
{
    return g_roller_second;
}

void xc_set_roller_time_hour(uint8_t hour)
{
    g_roller_hour = hour;
}

void xc_set_roller_time_minute(uint8_t minute)
{
    g_roller_minute = minute;
}

void xc_set_roller_time_second(uint8_t second)
{
    g_roller_second = second;
}

void xc_update_roller_time(uint8_t hour, uint8_t min, uint8_t sec)
{
    if (hour >= 0)
        xc_set_roller_time_hour(hour);

    if (min >= 0)
        xc_set_roller_time_minute(min);

    if (sec >= 0)
        xc_set_roller_time_second(sec);
}

/* This logic should never modified unless have a better idea
 * This callback must be use a  high-res timer to handle
 * Be sure to use a monospaced font */
static bool xc_timer_roller_time_cb(struct repeating_timer *t)
{
    if ((++g_roller_second % SECOND_UPDATE_STEP) == 0)
        lv_roller_set_selected(ui_RollerSecond, g_roller_second, LV_ANIM_OFF);

    if (SECONDS_IN_MINUTE == g_roller_second) {
        g_roller_second = 0;     /* update first, then write back */
        lv_roller_set_selected(ui_RollerSecond, g_roller_second, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerMinute, ++g_roller_minute, LV_ANIM_OFF);
    }

    if (MINUTES_IN_HOUR == g_roller_minute) {
        g_roller_minute = 0;
        lv_roller_set_selected(ui_RollerMinute, g_roller_minute, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerHour, ++g_roller_hour, LV_ANIM_OFF);
    }

    if (HOURS_IN_DAY == g_roller_hour) {
        g_roller_hour = 0;
        lv_roller_set_selected(ui_RollerHour, g_roller_hour, LV_ANIM_OFF);
    }

    /* we deleted refresh timer of lvgl, and repalce it with timer of mcu,
     * bacause there some blocked function in display flush method, this
     * cause lvgl timer blocked too, so we call display refesh maunally
     * in every 1 second */
    _lv_disp_refr_timer(NULL);

    return true;
}

static inline void xc_timer_time_sync_cb(struct _lv_timer_t *t)
{
    /* 1. trying to get time from network though NTP */

    /* ON SYNC OKAY */
    /* 2. if ntp sync is OKAY, save it to rtc device, and set this synced time */

    /* ON SYNC FAILED */
    /* 3. if ntp sync is FAILED, just read from rtc device */
    datetime_t t_rtc = p_rtc_device_get_time();

    /* write back to host rtc */
    rtc_host_set_datetime(&t_rtc);

    /* 4. set synced time */
    g_roller_hour = t_rtc.hour;
    g_roller_minute = t_rtc.min;
    g_roller_second = t_rtc.sec;

    pr_debug("syncing time to %02d:%02d:%02d ...\n", g_roller_hour, g_roller_minute, g_roller_second);
    lv_roller_set_selected(ui_RollerHour, g_roller_hour, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerMinute, g_roller_minute, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerSecond, g_roller_second, LV_ANIM_OFF);
}

/* TODO: These tips should get from network */
static const char *g_tips[] = {
    "Be nice.",
    "Stay Hungry, Stay Foolish.",
    "Learn to pause.",
    "Don't Worry, Be Happy.",
    "Do Androids Dream of Electric Sheep?",
    "Gah! YEEEEEEEE!",
    "Never laugh at live dragons.",
    "Have a great day!",
    "What are the characteristics of a person?",
    "You are not dead yet.",
    "be happy!",
    "Cheers!",
    "Sleep seven to eight hours per night.",
    "Keep company with good people.",
    "Get regular exercise.",
    "Do something meaningful each day.",
    "Think good thoughts for others.",
    "Be humble and curious.",
    "I don't want to surive, I want to live!",
};
static uint8_t tips_index = 0;

static inline void xc_timer_label_tips_cb(struct _lv_timer_t *t)
{
    lv_label_set_text(ui_LabelTips, g_tips[tips_index++]);
    if (tips_index > (ARRAY_SIZE(g_tips) - 1))
        tips_index = 0;
}

// extern lv_obj_t *ui_LabelBattery;
extern lv_obj_t *ui_PanelStatusBar;

/* TODO: Real battery percent detect */
static inline void xc_timer_battery_cb(struct _lv_timer_t *t)
{
    lv_obj_t *ui_LabelBattery = ui_comp_get_child(ui_PanelStatusBar,
                                                  UI_COMP_PANELSTATUSBAR_LABELBATTERY);

    static uint8_t battery_percent = BATTERY_PERCENT_FULL;
    lv_label_set_text_fmt(ui_LabelBattery, "%d%%", --battery_percent);

    if (battery_percent == BATTERY_PRECENT_DEAD)
        battery_percent = BATTERY_PERCENT_FULL;
}

extern lv_obj_t *ui_LabelTemperture;
extern lv_obj_t *ui_LabelHumidity;

static inline void xc_timer_temp_humid_cb(struct _lv_timer_t *t)
{
    struct aht10_data data = aht10_read_humidity_temperture();

    lv_label_set_text_fmt(ui_LabelHumidity, "%d%%", (int)data.real_humidity);
    lv_label_set_text_fmt(ui_LabelTemperture, "%d*C", (int)data.real_temperture);
}


void xc_post_timers_init(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;

    pr_debug("registering time roller timer ...\n");

    add_repeating_timer_ms(MILLISECOND(1000), xc_timer_roller_time_cb, NULL, &g_roller_timer);

    lv_timer_t *timer_time_sync = lv_timer_create_basic();
    timer_time_sync->timer_cb = xc_timer_time_sync_cb;
    timer_time_sync->period = TIME_SYNC_PERIOD;

    /* timer for updating daily tips, should requst tips from internet */
    pr_debug("registering tips timer ...\n");
    lv_timer_t *timer_tips = lv_timer_create_basic();
    timer_tips->timer_cb = xc_timer_label_tips_cb;
    timer_tips->period = REFRESH_SPEED_NORMAL;

    /* timer for updating battery percent, just a demo for now */
    pr_debug("registering battery percent timer ...\n");
    lv_timer_t *timer_battery = lv_timer_create_basic();
    timer_battery->timer_cb = xc_timer_battery_cb;
    timer_battery->period = REFRESH_SPEED_SLOW;

    /* timer for updating temperture and humidity */
    pr_debug("registering temperture and humidity timer ...\n");
    lv_timer_t *timer_temp_humid = lv_timer_create_basic();
    timer_temp_humid->timer_cb = xc_timer_temp_humid_cb;
    timer_temp_humid->period = REFRESH_SPEED_FAST;
    // lv_timer_pause(timer_temp_humid);
}