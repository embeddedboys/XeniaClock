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
#include "net/esp01s.h"
#include "clk/native_clk.h"
#include "spi/native_spi.h"
#include "i2c/native_i2c.h"
#include "misc/extras.h"

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

    xc_update_roller_time(t.hour, t.min, t.sec);

    /* write back to lvgl */
    pr_debug("setting lvgl time roller ...\n");
    lv_roller_set_selected(ui_RollerHour, t.hour, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerMinute, t.min, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerSecond, t.sec, LV_ANIM_OFF);
}

static inline bool lvgl_clock_cb(struct repeating_timer *t)
{
    lv_timer_handler();
    lv_tick_inc(5);
    return true;
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
    lv_scr_load(ui_ScreenEpinkConfig);

    /* wait here because we are testing esp01s */
    // while (1) {
    //     tight_loop_contents();
    // }

    /* lol, pretending we are configuring device */
    sleep_ms(1000);
    pr_debug("network has been sucessfully configured!\n");

    /* if network configuration is okay, switch to home */
    pr_debug("loading ui home screen ...\n");
    lv_scr_load(ui_ScreenEpinkHome);
}

lv_obj_t *sub_display_label_time;
static bool sub_display_label_flash = true;
static inline void sub_screen_display_update_cb()
{
    uint8_t hour, minute;

    hour = xc_get_roller_time_hour();
    minute = xc_get_roller_time_minute();

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
    lv_label_set_text_fmt(sub_display_label_time, "%02d:%02d", 0, 0);
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

    xc_event_setup();
    xc_theme_setup();

    /* initialize network */
    network_config();

    /* some post hardware init */
    native_rtc_init();

    /* widget timers init */
    xc_post_timers_init();

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
