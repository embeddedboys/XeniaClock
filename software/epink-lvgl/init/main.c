/**
 * @file main.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief file of the epink-1.54.
 * @version 0.2
 * @date 2022-08-14
 *
 * Hi, guys!
 *
 * Special thanks to :
 *   Raspberry Pi () -- MCU
 *   LuatOS (https://gitee.com/openLuat/LuatOS) -- Display module
 *   Espressif (https://github.com/espressif) -- Net module
 *
 * MIT License
 *
 * Copyright (c) 2022 IotaHydrae(writeforever@foxmail.com)
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


#include <stdio.h>
#include <string.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/types.h"
#include "pico/platform.h"
#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

/* Header files we defined */
#include "common/tools.h"
#include "common/vals.h"
#include "video/epd.h"
#include "video/ssd1306.h"
#include "rtc/native_rtc.h"
#include "i2c/sensors/aht10.h"
#include "net/esp01s.h"
#include "clk/native_clk.h"
#include "spi/native_spi.h"
#include "i2c/native_i2c.h"

/* Header files lvgl defined */
#include "lvgl/lvgl.h"
#include "lvgl/src/extra/libs/qrcode/lv_qrcode.h"
#include "port/lv_port_disp.h"
#include "port/lv_port_indev.h"
#include "src/extra/themes/basic/lv_theme_basic.h"
#include "ui/ui.h"
#include "ui/ui_comp.h"

static void clk_init()
{
    pr_debug("initlizing clocks ...\n");
    measure_freqs();
}

/**
 * @brief hardware layer initialize
 * for each platform, do it's iomux and pinctl here
 */
static void hal_init(void)
{
#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(EPINK_CS_PIN)
#warning spi/bme280_spi example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else
    /* changed to called by subsys_initcall */
    // native_spi_init();

    gpio_init(EPINK_CS_PIN);
    gpio_set_dir(EPINK_CS_PIN, GPIO_OUT);
    gpio_put(EPINK_CS_PIN, 1);
    bi_decl(bi_1pin_with_name(EPINK_CS_PIN, "EPINK CS"));

    gpio_init(EPINK_RES_PIN);
    gpio_set_dir(EPINK_RES_PIN, GPIO_OUT);
    bi_decl(bi_1pin_with_name(EPINK_CS_PIN, "EPINK RES"));

    gpio_init(EPINK_DC_PIN);
    gpio_set_dir(EPINK_DC_PIN, GPIO_OUT);
    bi_decl(bi_1pin_with_name(EPINK_CS_PIN, "EPINK DC"));

    gpio_init(EPINK_BUSY_PIN);
    gpio_set_dir(EPINK_BUSY_PIN, GPIO_IN);
    bi_decl(bi_1pin_with_name(EPINK_CS_PIN, "EPINK BUSY"));
#endif

    /* changed to called by subsys_initcall */
    // native_i2c_init();

    /* initialize uart */
    uart_init(uart1, DEFAULT_UART_SPEED);
    gpio_set_function(DEFAULT_ESP8266_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(DEFAULT_ESP8266_TX_PIN, GPIO_FUNC_UART);
    bi_decl(bi_2pins_with_func(DEFAULT_ESP8266_RX_PIN,
                               DEFAULT_ESP8266_TX_PIN, GPIO_FUNC_UART));
    uart_set_fifo_enabled(uart1, false);
}

void system_init(void)
{
    /* initialize clocks */
    clk_init();

    /* system up hardware init */
    stdio_init_all();
    hal_init();
}

static void lv_main_disp_scr_home_gesture_event_cb(lv_event_t *event)
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
        break;
    case LV_DIR_RIGHT:
        pr_debug("moving right gesture detected!\n");
        break;
    default:
        break;
    }
}

static void lv_main_disp_scr_sleep_gesture_event_cb(lv_event_t *event)
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

static void lv_main_disp_scr_home_roller_time_set_event_cb(lv_event_t *e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
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
    lv_obj_add_event_cb(msgbox_time_set, lv_main_disp_scr_home_roller_time_set_event_cb,
                        LV_EVENT_VALUE_CHANGED, NULL);
}

static void lv_event_setup(void)
{
    lv_obj_add_event_cb(ui_ScreenEpinkHome, lv_main_disp_scr_home_gesture_event_cb,
                        LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(ui_ScreenSleep, lv_main_disp_scr_sleep_gesture_event_cb,
                        LV_EVENT_GESTURE, NULL);

    lv_obj_add_event_cb(ui_RollerHour, roller_time_set_msgbox_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(ui_RollerMinute, roller_time_set_msgbox_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(ui_RollerSecond, roller_time_set_msgbox_event_cb, LV_EVENT_LONG_PRESSED, NULL);
}

static void lv_theme_setup(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    lv_theme_t *th = lv_theme_mono_init(disp, 0, &lv_font_montserrat_14);
    lv_disp_set_theme(disp, th);
}

extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_RollerMinute;
extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_LabelDate;
extern lv_obj_t *ui_LabelTips;

/* Whew, we are getting off work! */
static uint8_t hour = 18;
static uint8_t minute = 30;
static uint8_t second = 0;

/* initialize all stuff with RTC releated */
static void native_rtc_init()
{
    datetime_t t;
    /* TODO: init rtc device */
    pr_debug("initializing rtc device ...\n");
    rtc_device_init();

    /* set a test time to device */
    // t.hour = hour;    /* if i could get home earlier */
    // t.min = minute;
    // t.sec = second;
    // p_rtc_device_set_time(t);
    // pr_debug("time of rtc device has been set to %02d:%02d:%02d\n",
    //  hour, minute, second);

    /* init rtc host in mcu */
    pr_debug("initializing rtc host ...\n");
    rtc_host_init();

    /* read RTC time from mcu */
    t = rtc_host_get_datetime();
    pr_debug("got time from rtc host : %02d:%02d:%02d\n",
             t.hour, t.min, t.sec);

    hour = t.hour;
    minute = t.min;
    second = t.sec;

    /* write back to lvgl */
    pr_debug("setting lvgl time roller ...\n");
    lv_roller_set_selected(ui_RollerHour, hour, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerMinute, minute, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);
}

/* This logic should never modified unless have a better idea
/* This callback must be use a  high-res timer to handle
/* Be sure to use a monospaced font
 */
static bool lv_timer_roller_time_cb(struct repeating_timer *t)
{
    if ((++second % SECOND_UPDATE_STEP) == 0)
        lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);

    if (SECONDS_IN_MINUTE == second) {
        second = 0;     /* update first, then write back */
        lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerMinute, ++minute, LV_ANIM_OFF);
    }

    if (MINUTES_IN_HOUR == minute) {
        minute = 0;
        lv_roller_set_selected(ui_RollerMinute, minute, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerHour, ++hour, LV_ANIM_OFF);
    }

    if (HOURS_IN_DAY == hour) {
        hour = 0;
        lv_roller_set_selected(ui_RollerHour, hour, LV_ANIM_OFF);
    }

    /* we deleted refresh timer of lvgl, and repalce it with timer of mcu,
     * bacause there some blocked function in display flush method, this
     * cause lvgl timer blocked too, so we call display refesh maunally
     * in every 1 second */
    _lv_disp_refr_timer(NULL);

    return true;
}

static inline void lv_timer_time_sync_cb(struct _lv_timer_t *t)
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
    hour = t_rtc.hour;
    minute = t_rtc.min;
    second = t_rtc.sec;

    pr_debug("syncing time to %02d:%02d:%02d ...\n", hour, minute, second);
    lv_roller_set_selected(ui_RollerHour, hour, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerMinute, minute, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);
}

/* TODO: These tips should get from network */
static const char *g_tips[] = {
    "be nice.",
    "Stay Hungry, Stay Foolish.",
    "Learn to pause.",
    "Don't Worry, Be Happy.",
    "Do Androids Dream of Electric Sheep?",
    "Gah! YEEEEEEEE!",
    "Never laugh at live dragons.",
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

static inline void lv_timer_label_tips_cb(struct _lv_timer_t *t)
{
    lv_label_set_text(ui_LabelTips, g_tips[tips_index++]);
    if (tips_index > (ARRAY_SIZE(g_tips) - 1))
        tips_index = 0;
}

// extern lv_obj_t *ui_LabelBattery;
extern lv_obj_t *ui_PanelStatusBar;

/* TODO: Real battery percent detect */
static inline void lv_timer_battery_cb(struct _lv_timer_t *t)
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

static inline void lv_timer_temp_humid_cb(struct _lv_timer_t *t)
{
    struct aht10_data data = aht10_read_humidity_temperture();

    lv_label_set_text_fmt(ui_LabelHumidity, "%d%%", (int)data.real_humidity);
    lv_label_set_text_fmt(ui_LabelTemperture, "%d*C", (int)data.real_temperture);
}

static inline bool lvgl_clock_cb(struct repeating_timer *t)
{
    lv_timer_handler();
    lv_tick_inc(5);
    return true;
}

static void post_timers_init()
{
    lv_disp_t *disp = lv_disp_get_default();
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;

    pr_debug("registering time roller timer ...\n");
    struct repeating_timer roller_timer;
    add_repeating_timer_ms(MILLISECOND(1000), lv_timer_roller_time_cb, NULL, &roller_timer);

    lv_timer_t *timer_time_sync = lv_timer_create_basic();
    timer_time_sync->timer_cb = lv_timer_time_sync_cb;
    timer_time_sync->period = TIME_SYNC_PERIOD;

    /* timer for updating daily tips, should requst tips from internet */
    pr_debug("registering tips timer ...\n");
    lv_timer_t *timer_tips = lv_timer_create_basic();
    timer_tips->timer_cb = lv_timer_label_tips_cb;
    timer_tips->period = REFRESH_SPEED_NORMAL;

    /* timer for updating battery percent, just a demo for now */
    pr_debug("registering battery percent timer ...\n");
    lv_timer_t *timer_battery = lv_timer_create_basic();
    timer_battery->timer_cb = lv_timer_battery_cb;
    timer_battery->period = REFRESH_SPEED_SLOW;

    /* timer for updating temperture and humidity */
    pr_debug("registering temperture and humidity timer ...\n");
    lv_timer_t *timer_temp_humid = lv_timer_create_basic();
    timer_temp_humid->timer_cb = lv_timer_temp_humid_cb;
    timer_temp_humid->period = REFRESH_SPEED_FAST;
    // lv_timer_pause(timer_temp_humid);
}

extern lv_obj_t *ui_LabelWifiName;

static void network_config()
{
    pr_debug("configurating network ...\n");
    esp01s_init(NULL);
    const char *data = "http://192.168.4.1";

    /* show a default AP name */
    lv_label_set_text_fmt(ui_LabelWifiName, "connect to \"%s\" then scan this QR code",
                          DEFAULT_ESP8266_AP_NAME);

    /* make a QR code on it, (0, -5), 120x120 */
    lv_obj_t *qr_code = lv_qrcode_create(ui_ScreenEpinkConfig, 120, lv_color_hex(0x0),
                                         lv_color_hex(0xffffffff));
    lv_obj_align(qr_code, LV_ALIGN_CENTER, 0, -5);
    lv_qrcode_update(qr_code, data, strlen(data));
    lv_disp_load_scr(ui_ScreenEpinkConfig);

    /* wait here because we are testing esp01s */
    // while (1) {
    //     tight_loop_contents();
    // }

    /* lol, pretending we are configuring device */
    sleep_ms(1000);
    pr_debug("network has been sucessfully configured!\n");

    /* if network configuration is okay, switch to home */
    pr_debug("loading ui home screen ...\n");
    lv_disp_load_scr(ui_ScreenEpinkHome);
}

lv_obj_t *sub_display_label_time;
static bool sub_display_label_flash = true;

static void anim_x_cb(void *var, int32_t x)
{
    lv_obj_set_x(var, x);
}

static inline void sub_screen_display_update_cb()
{
    lv_label_set_text_fmt(sub_display_label_time,
                          sub_display_label_flash ? "%02d:%02d" : "%02d %02d",
                          hour, minute);

    sub_display_label_flash = !sub_display_label_flash;
}

static void sub_screen_display_init()
{
    /* this one is called here so late because a banner should
     * be displayed for a few seconds when deviced powered on
     * check ssd1306_banner();
     */
    post_lv_port_disp_init();

    /* get lvgl displays */
    lv_disp_t *disp = lv_disp_get_default();
    pr_debug("default disp hor ver : %d %d\n", disp->driver->hor_res,
             disp->driver->ver_res);

    lv_disp_t *sub_disp = lv_disp_get_next(NULL);
    pr_debug("sub disp hor ver : %d %d\n", sub_disp->driver->hor_res,
             sub_disp->driver->ver_res);

    /* set default disp to sub screen */
    lv_disp_set_default(sub_disp);
    lv_theme_t *th = lv_theme_mono_init(sub_disp, 0, &ui_font_FiraCodeSemiBold12);
    lv_disp_set_theme(sub_disp, th);

    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_style_radius(btn, 5, 0);
    lv_obj_set_style_pad_all(btn, 5, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Xenia Clock");
    lv_obj_center(btn);

    sleep_ms(1000);

    lv_obj_del(btn);
    th  = lv_theme_basic_init(sub_disp);
    lv_disp_set_theme(sub_disp, th);

    sub_display_label_time = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(sub_display_label_time, "%02d:%02d", hour, minute);
    lv_obj_set_style_text_font(sub_display_label_time, &ui_font_FiraCodeSemiBold40, 0);
    // lv_obj_align(sub_display_label_time, LV_ALIGN_CENTER, 0, 0);
    lv_obj_center(sub_display_label_time);

    /* add a time refresh timer */
    pr_debug("adding sub screen refresh timer ...\n");
    lv_timer_t *sub_screen_display_timer = lv_timer_create_basic();
    sub_screen_display_timer->timer_cb = sub_screen_display_update_cb;
    sub_screen_display_timer->period = MICROSECOND(500);

    lv_disp_set_default(disp);
}

static void launch_banner()
{
    /* display a string on sub screen when starting */
    ssd1306_banner();

    printf("\n\n\n\n");
    printf(R"EOF(
__  __          _              ____ _            _
\ \/ /___ _ __ (_) __ _       / ___| | ___   ___| | __
 \  // _ \ '_ \| |/ _` |     | |   | |/ _ \ / __| |/ /
 /  \  __/ | | | | (_| |     | |___| | (_) | (__|   <
/_/\_\___|_| |_|_|\__,_|      \____|_|\___/ \___|_|\_\
    )EOF");
    printf("\n\nPlease wait. Booting ...\n\n");
}

int main(void)
{
    /* some system layer initialize ops */
    system_init();
    // while(1);

    /* some ops used to display banner to anywhere */
    launch_banner();

    /* lvgl init */
    struct repeating_timer lvgl_clock_timer;
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    /* start a native timer for lvgl clock */
    add_repeating_timer_us(MICROSECOND(5000), lvgl_clock_cb, NULL, &lvgl_clock_timer);

    /* call squareline project initialization process */
    ui_init();

    lv_event_setup();
    lv_theme_setup();

    /* initialize network */
    network_config();

    /* some post hardware init */
    native_rtc_init();

    /* widget timers init */
    post_timers_init();

    /* initialize sub screen lvgl display */
    sub_screen_display_init();

    pr_debug("going to loop\n");
    while (1) {
        tight_loop_contents();
    }

    sleep_ms(3000);
    lv_disp_load_scr(ui_ScreenSleep);

    sleep_ms(3000);
    lv_disp_load_scr(ui_ScreenEpinkHome);

    while (1) {
        tight_loop_contents();
    }

    return 0;
}
