/**
 * @file main.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief file of the epink-1.54.
 * @version 0.2
 * @date 2022-08-14
 *
 * Hi, guys!
 *
 * This is a simple ALL-IN-ONE driver for the LuatOS epink-1.54 screen module.
 *
 * the device init function in this file was based on :
 * https://gitee.com/openLuat/LuatOS/blob/master/components/epaper/EPD_1in54.c
 *
 * More info about the epaper module can be found in :
 * https://wiki.luatos.com/peripherals/eink_1.54/index.html
 *
 * Special thanks to :
 *   LuatOS (https://gitee.com/openLuat/LuatOS)
 *
 * MIT License
 *
 * Copyright (c) 2022 LuatOS
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

#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "display/epd.h"
#include "rtc/native_rtc.h"

#include "port/lv_port_disp.h"
#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "ui/ui.h"

/**
 * @brief hardware layer initialize
 * for each platform, do it's iomux and pinctl here
 */
static void hal_init(void)
{
    stdio_init_all();

#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(EPINK_CS_PIN)
#warning spi/bme280_spi example requires a board with SPI pins
    puts( "Default SPI pins were not defined" );
#else
    /* Useing default SPI0 at 50MHz */
    spi_init( spi_default, 50 * 1000 * 1000 );
    gpio_set_function( PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI );
    gpio_set_function( PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI );
    bi_decl( bi_2pins_with_func( PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN,
                                 GPIO_FUNC_SPI ) );

    gpio_init( EPINK_CS_PIN );
    gpio_set_dir( EPINK_CS_PIN, GPIO_OUT );
    gpio_put( EPINK_CS_PIN, 1 );
    bi_decl( bi_1pin_with_name( EPINK_CS_PIN, "SPI CS" ) );

    gpio_init( EPINK_RES_PIN );
    gpio_set_dir( EPINK_RES_PIN, GPIO_OUT );

    gpio_init( EPINK_DC_PIN );
    gpio_set_dir( EPINK_DC_PIN, GPIO_OUT );

    gpio_init( EPINK_BUSY_PIN );
    gpio_set_dir( EPINK_BUSY_PIN, GPIO_IN );
#endif
}

extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_RollerMinute;
extern lv_obj_t *ui_RollerHour;
extern lv_obj_t *ui_LabelTips;

static uint8_t hour = 23;
static uint8_t minute = 59;
static uint8_t second = 0;

static void native_rtc_init()
{
    datetime_t t;
    /* TODO: init rtc device */

    /* TODO: init rtc host in mcu */
    rtc_host_init();

    /* TODO: read RTC time from mcu */
    t = rtc_host_get_datetime();

    hour = t.hour;
    minute = t.min;
    second = t.sec;

    /* write back to lvgl */
    lv_roller_set_selected(ui_RollerHour, hour, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerMinute, minute, LV_ANIM_OFF);
    lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);
}

static void lv_timer_roller_time_cb()
{
    lv_roller_set_selected(ui_RollerSecond, ++second, LV_ANIM_OFF);

    if (second == 60) {
        second = 0;
        lv_roller_set_selected(ui_RollerSecond, second, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerMinute, ++minute, LV_ANIM_OFF);
    }

    if (minute == 60) {
        minute = 0;
        lv_roller_set_selected(ui_RollerMinute, minute, LV_ANIM_OFF);
        lv_roller_set_selected(ui_RollerHour, ++hour, LV_ANIM_OFF);
    }

    if (hour == 24) {
        hour=0;
        lv_roller_set_selected(ui_RollerHour, hour, LV_ANIM_OFF);
    }
}

static const char *g_tips[] = {
    "Learn to pause.",
    "Don't Worry, Be Happy.",
    "Gah! YEEEEEEEE!",
    "Never laugh at live dragons.",
    "You are not dead yet.",
    "Cheers!",
};
static uint8_t tips_index = 0;

static void lv_timer_label_tips_cb()
{
    lv_label_set_text(ui_LabelTips, g_tips[tips_index++]);
    if (tips_index > (sizeof(g_tips)/sizeof(g_tips[0]) - 1))
        tips_index = 0;
}

int main( void )
{
    printf("%s\n", __func__);

    /* system up hardware init */
    stdio_init_all();
    hal_init();

    /* lvgl init */
    lv_init();
    lv_port_disp_init();

    epink_blank();

    /* Load APP UI */
    ui_init();

    /* post hardware init */
    native_rtc_init();

    lv_timer_t *timer_roller = lv_timer_create_basic();
    timer_roller->timer_cb = lv_timer_roller_time_cb;
    timer_roller->period = 1000;

    lv_label_set_long_mode(ui_LabelTips, LV_LABEL_LONG_WRAP);

    lv_timer_t *timer_tips = lv_timer_create_basic();
    timer_tips->timer_cb = lv_timer_label_tips_cb;
    timer_tips->period = 5000;

    while( 1 ) {
        sleep_us(5*1000);
        lv_timer_handler();
        lv_tick_inc(5);
    }

    return 0;

}
