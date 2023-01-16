/**
 * @file events.c
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

#include "common/tools.h"

#include "../lvgl/lvgl.h"
#include "../ui/ui.h"
#include "../ui/ui_comp.h"

static void xc_main_disp_scr_home_gesture_event_cb(lv_event_t *event)
{
    lv_obj_t *scr = lv_event_get_current_target(event);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    switch (dir) {
    case LV_DIR_TOP:
        pr_debug("moving top gesture detected!\n");
        break;
    case LV_DIR_BOTTOM:
        pr_debug("moving bottom gesture detected!\n");
        break;
    case LV_DIR_LEFT:
        pr_debug("moving left gesture detected!\n");
        lv_scr_load(ui_ScreenEpinkApps);
        break;
    case LV_DIR_RIGHT:
        pr_debug("moving right gesture detected!\n");
        lv_scr_load(ui_ScreenEpinkApps);
        break;
    default:
        break;
    }
}

static void xc_main_disp_scr_apps_gesture_event_cb(lv_event_t *event)
{
    lv_obj_t *scr = lv_event_get_current_target(event);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    switch (dir) {
    case LV_DIR_TOP:
        pr_debug("moving top gesture detected!\n");
        break;
    case LV_DIR_BOTTOM:
        pr_debug("moving bottom gesture detected!\n");
        break;
    case LV_DIR_LEFT:
        pr_debug("moving left gesture detected!\n");
        lv_scr_load(ui_ScreenEpinkHome);
        break;
    case LV_DIR_RIGHT:
        pr_debug("moving right gesture detected!\n");
        lv_scr_load(ui_ScreenEpinkHome);
        break;
    default:
        break;
    }
}

static void xc_main_disp_scr_sleep_gesture_event_cb(lv_event_t *event)
{
    lv_obj_t *scr = lv_event_get_current_target(event);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

    switch (dir) {
    case LV_DIR_TOP:
    case LV_DIR_BOTTOM:
    case LV_DIR_LEFT:
    case LV_DIR_RIGHT:
        pr_debug("exiting sleep mode!\n");
        break;
    default:
        break;
    }
}

static void xc_main_disp_scr_home_roller_time_set_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    pr_debug("Button %s clicked\n", lv_msgbox_get_active_btn_text(obj));
}

static void roller_time_set_msgbox_event_cb(lv_event_t *event)
{
    printf("obj has been Long Pressed!\n");
    static const char *msgbox_time_set_btns[] = {"Yes", "No", ""};
    lv_obj_t *msgbox_time_set = lv_msgbox_create(ui_ScreenEpinkHome, "Attention",
                                                 "Are you want to configure time?",
                                                 msgbox_time_set_btns, true);
    lv_obj_set_size(msgbox_time_set, 160, 100);
    lv_obj_center(msgbox_time_set);
    lv_obj_add_event_cb(msgbox_time_set, xc_main_disp_scr_home_roller_time_set_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void xc_event_buttonapps_cb(lv_event_t *e)
{
    static bool key_state = 0;

    switch (e->code) {
    case LV_EVENT_CLICKED:
        key_state = !key_state;
        pr_debug("clicked, val : %d\n", key_state);
        if (key_state) {
            lv_obj_set_style_bg_color(e->target, lv_color_hex(0x0), 0);
            lv_obj_set_style_text_color(lv_obj_get_child(e->target, 0), lv_color_hex(0xffffffff), 0);
        } else {
            lv_obj_set_style_bg_color(e->target, lv_color_hex(0xffffffff), 0);
            lv_obj_set_style_text_color(lv_obj_get_child(e->target, 0), lv_color_hex(0), 0);
        }
    }
}

static void xc_event_gesture_init(void)
{
    lv_obj_add_event_cb(ui_ScreenEpinkHome, xc_main_disp_scr_home_gesture_event_cb,
                        LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_ScreenSleep, xc_main_disp_scr_sleep_gesture_event_cb,
                        LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_ScreenEpinkApps, xc_main_disp_scr_apps_gesture_event_cb,
                        LV_EVENT_GESTURE, NULL);
}

static void xc_event_roller_init(void)
{
    lv_obj_add_event_cb(ui_RollerHour, roller_time_set_msgbox_event_cb, LV_EVENT_LONG_PRESSED,
                        NULL);
    lv_obj_add_event_cb(ui_RollerMinute, roller_time_set_msgbox_event_cb,
                        LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(ui_RollerSecond, roller_time_set_msgbox_event_cb,
                        LV_EVENT_LONG_PRESSED, NULL);
}

static void xc_event_buttonapps_init(void)
{
    // lv_obj_add_event_cb(ui_ButtonApp1, xc_event_buttonapps_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonApp2, xc_event_buttonapps_cb, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(ui_ButtonApp3, xc_event_buttonapps_cb, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(ui_ButtonApp4, xc_event_buttonapps_cb, LV_EVENT_ALL, NULL);

    // lv_obj_add_flag(ui_ButtonApp1, LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_flag(ui_ButtonApp2, LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_flag(ui_ButtonApp2, LV_OBJ_FLAG_CHECKABLE);
    // lv_obj_add_flag(ui_ButtonApp2, LV_OBJ_FLAG_CHECKABLE);
}

void xc_event_setup(void)
{
    xc_event_gesture_init();

    xc_event_roller_init();
    
    xc_event_buttonapps_init();
}
