/**
 * @file ssd1306.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-08-01
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

#include <string.h>

#include "common/tools.h"
#include "common/version.h"

#include "i2c/native_i2c.h"
#include "video/epd.h"
#include "video/ssd1306.h"
#include "pico/time.h"

#include "font/font.h"

/* ssd1306 functions switch */
#define SSD1306_USE_INIT              1
#define SSD1306_USE_FLUSH             1
#define SSD1306_USE_CLEAR             1
#define SSD1306_USE_BLANK             1
#define SSD1306_USE_SET_UPDATE_MODE   0
#define SSD1306_USE_PUT_PIXEL         1

#define DRV_NAME    "ssd1306"

#define SSD1306_ADDR    (0x3c)

#define SSD1306_CMD     (0x00)
#define SSD1306_DATA    (0x40)

#define SSD1306_COLOR_BLACK     (0xff)
#define SSD1306_COLOR_WHITE     (0x00)

/* The old buffer is used in flush function */
static uint8_t ssd1306_buffer[SSD1306_BUFFER_SIZE] = {0};
static uint8_t old_ssd1306_buffer[SSD1306_BUFFER_SIZE] = {0};

static struct font *g_default_font = NULL;

static void ssd1306_write_cmd(uint8_t val)
{
    // uint8_t wbuf[2] = {SSD1306_CMD, val};
    // i2c_write_blocking(i2c_default, SSD1306_ADDR, wbuf, 2, false);

    // uint16_t content = val << 8 | SSD1306_CMD;
    // i2c_write_blocking(i2c_default, SSD1306_ADDR, (uint8_t *)&content, sizeof(content), false);

    i2c_write_reg(SSD1306_ADDR, SSD1306_CMD, val);
}

static void ssd1306_write_data(uint8_t val)
{
    // uint8_t wbuf[2] = {SSD1306_DATA, val};
    // i2c_write_blocking(i2c_default, SSD1306_ADDR, wbuf, 2, false);

    // uint16_t content = val << 8 | SSD1306_DATA;
    // i2c_write_blocking(i2c_default, SSD1306_ADDR, (uint8_t *)&content, sizeof(content), false);

    i2c_write_reg(SSD1306_ADDR, SSD1306_DATA, val);
}

static void ssd1306_set_pos(uint8_t page, uint8_t col)
{
    ssd1306_write_cmd(0xb0 + page);

    ssd1306_write_cmd(0x00 | (col & 0x0f));
    ssd1306_write_cmd(0x10 | (col >> 4));
}

#if SSD1306_USE_FLUSH
static int ssd1306_flush()
{
    uint8_t page, col;

    for (page = 0; page < SSD1306_PAGE_SIZE; page++)
        for (col = 0; col < SSD1306_HOR_RES_MAX; col++)
            // if (oled_buffer[OFFSET(page, col)] != 0x00)
        {
            if (ssd1306_buffer[OFFSET(page, col)] == old_ssd1306_buffer[OFFSET(page, col)]) {
                continue;
            }

            ssd1306_set_pos(page, col);
            ssd1306_write_data(ssd1306_buffer[OFFSET(page, col)]);
        }

    memcpy(old_ssd1306_buffer, ssd1306_buffer, SSD1306_BUFFER_SIZE);
    return 0;
}
#else
static int ssd1306_flush()
{
    return 0;
}
#endif

#if SSD1306_USE_CLEAR
static void ssd1306_clear(uint16_t color)
{
    uint8_t page, col;

    for (page = 0; page < SSD1306_PAGE_SIZE; page++)
        for (col = 0; col < SSD1306_HOR_RES_MAX; col++) {
            ssd1306_set_pos(page, col);
            ssd1306_write_data(color);
        }
}
static void ssd1306_clear_buf(uint16_t color)
{
    memset(ssd1306_buffer, color, SSD1306_BUFFER_SIZE);
}
#else
static void ssd1306_clear(uint8_t color)
{

}
#endif

#if SSD1306_USE_SET_UPDATE_MODE
static void ssd1306_set_update_mode(uint8_t mode)
{

}
#else
static void ssd1306_set_update_mode(uint8_t mode)
{

}
#endif

static void ssd1306_device_init()
{
    /* TODO: add a reset ops here */

#ifdef SSD1306_128_32
    ssd1306_write_cmd(0xAE);//--display off
    // ssd1306_write_cmd(0x00);
    // ssd1306_write_cmd(0x10);
    ssd1306_write_cmd(0x40);//---set low column address
    ssd1306_write_cmd(0xB0);//---set high column address
    ssd1306_write_cmd(0xC8);//-not offset
    ssd1306_write_cmd(0x81);// contract control
    ssd1306_write_cmd(0xFF);//--128
    ssd1306_write_cmd(0xA1);//set segment remap
    ssd1306_write_cmd(0xA6);//--normal / reverse
    ssd1306_write_cmd(0xA8);//--set multiplex ratio(1 to 64)
    ssd1306_write_cmd(0x1F);
    ssd1306_write_cmd(0xD3);//-set display offset
    ssd1306_write_cmd(0x00);
    ssd1306_write_cmd(0xD5);//set osc division
    ssd1306_write_cmd(0xF0);
    ssd1306_write_cmd(0xD9);//Set Pre-Charge Period
    ssd1306_write_cmd(0x22);
    ssd1306_write_cmd(0xDA);//set com pin configuartion
    ssd1306_write_cmd(0x02);
    ssd1306_write_cmd(0xDB);//set Vcomh
    ssd1306_write_cmd(0x49);
    ssd1306_write_cmd(0x8D);//set charge pump enable
    ssd1306_write_cmd(0x14);
    sleep_ms(20);
    ssd1306_write_cmd(0xAF);//--turn on oled pan
#else
    ssd1306_write_cmd(0xAE); /*display off*/
    ssd1306_write_cmd(0x00); /*set lower column address*/
    ssd1306_write_cmd(0x10); /*set higher column address*/
    ssd1306_write_cmd(0x40); /*set display start line*/
    ssd1306_write_cmd(0xB0); /*set page address*/
    ssd1306_write_cmd(0x81); /*contract control*/
    ssd1306_write_cmd(0x66); /*128*/
    ssd1306_write_cmd(0xA1); /*set segment remap*/
    ssd1306_write_cmd(0xA6); /*normal / reverse*/
    ssd1306_write_cmd(0xA8); /*multiplex ratio*/
    ssd1306_write_cmd(0x3F); /*duty = 1/64*/
    ssd1306_write_cmd(0xC8); /*Com scan direction*/
    ssd1306_write_cmd(0xD3); /*set display offset*/
    ssd1306_write_cmd(0x00);
    ssd1306_write_cmd(0xD5); /*set osc division*/
    ssd1306_write_cmd(0x80);
    ssd1306_write_cmd(0xD9); /*set pre-charge period*/
    ssd1306_write_cmd(0x1f);
    ssd1306_write_cmd(0xDA); /*set COM pins*/
    ssd1306_write_cmd(0x12);
    ssd1306_write_cmd(0xdb); /*set vcomh*/
    ssd1306_write_cmd(0x30);
    ssd1306_write_cmd(0x8d); /*set charge pump enable*/
    ssd1306_write_cmd(0x14);
    ssd1306_write_cmd(0xAF); /*display ON*/
#endif
}

#if SSD1306_USE_INIT
static int ssd1306_init(uint8_t mode)
{
    pr_debug("initializing driver ic ssd1306 ...\n");
    ssd1306_device_init();

    pr_debug("clearing screen ...\n");
    ssd1306_clear(SSD1306_COLOR_WHITE);

    g_default_font = find_font_by_name("font_8x16");
    // g_default_font = find_font_by_name("font_mini_4x6");
    if (!g_default_font) {
        pr_debug("failed to find this font!\n");
        return -1;
    }

    return 0;
}
#else
static int ssd1306_init(uint8_t mode)
{
    return 0;
}
#endif

#if SSD1306_USE_BLANK
static void ssd1306_blank()
{
    ssd1306_clear(SSD1306_COLOR_BLACK);

    sleep_ms(200);

    ssd1306_clear(SSD1306_COLOR_WHITE);

    sleep_ms(200);
}
#else
static void ssd1306_blank()
{

}
#endif

#if SSD1306_USE_PUT_PIXEL
static void ssd1306_put_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t *pen = ssd1306_buffer;

    if (!((x >= 0 && x < SSD1306_HOR_RES_MAX) && (y >= 0 && y < SSD1306_VER_RES_MAX)))
        return;

    if (color)
        pen[OFFSET(y / 8, x)] |= (1 << (y % 8));
    else
        pen[OFFSET(y / 8, x)] &= ~(1 << (y % 8));
}
#else
static void ssd1306_put_pixel(uint16_t x, uint16_t y, uint8_t color)
{

}
#endif

/**
 * @brief Put a single ascii char to panel
 *
 * @param x start position of X
 * @param y start position of Y
 * @param c char that will outputting to panel
 */
static void ssd1306_putascii(struct font *font, uint8_t x, uint8_t y, char c, bool direct)
{
    /* Get the char in ascii array, each char use 16 byte to store */
    // const unsigned char *dots = (uint8_t *)&fontdata_8x16[c * 16];
    const unsigned char *dots = &font->data[c * font->height];
    uint8_t row, col, byte;

    /* In this case, we use a 8x16 size font, so
     * we need to draw 16 byte totally, for each
     * byte, draw it's each bit from higher to low
     */
    for (row = 0; row < font->height; row++) {
        byte = dots[row];

        for (col = 0; col < font->width; col++) {
            ssd1306_put_pixel(x + col, y + row, (byte << col) & 0x80);
        }
    }

    if (direct)
        ssd1306_flush();
}

/**
 * @brief Put ascii string to panel
 *
 * @param x start position of X
 * @param y start position of Y
 * @param str string that will outputting to the panel
 * @param delay a delay between each char display in ms
 */
static void ssd1306_putascii_string(struct font *font, uint8_t x, uint8_t y, char *str,
                                    int delay, bool direct)
{
    while (*str != '\0') {
        ssd1306_putascii(font, x, y, '_', direct);

        ssd1306_putascii(font, x, y, *str++, direct);
        x += font->width; /* move x to the next pos */
        if (delay > 0)
            sleep_ms(delay);
        /* start a new line if reach the end of line */
        if (x >= SSD1306_HOR_RES_MAX) {
            x = 0;
            y += font->height; /* line hight min:16 */
        }
    }
}

void ssd1306_test()
{
    ssd1306_init(1);

    ssd1306_blank();

    for (int x = 0; x < 128; x++)
        for (int y = 0; y < 16; y++)
            ssd1306_put_pixel(x, y, 1);
    ssd1306_flush();
}

static void __pre_ssd1306_banner(void)
{
#define PRE_BANNER "A fully open-sourced desktop clock gadget,\
including software, hardware, and more. Using an e-paper display,\
support network, and more functions! the platform is based on RP2040."

    struct font *mini_font = find_font_by_name("font_mini_4x6");

    ssd1306_putascii_string(mini_font, 0, 0, PRE_BANNER, 0, true);

    ssd1306_clear_buf(SSD1306_COLOR_WHITE);
}

void ssd1306_banner()
{
    ssd1306_init(1);

    __pre_ssd1306_banner();

    ssd1306_putascii_string(g_default_font, 20, 0, "Xenia Clock", 21, true);
    char buf[64];
    sprintf(buf, "version: %d.%d.%d", VER_MAJOR, VER_MINOR, VER_REVISION);
    ssd1306_putascii_string(g_default_font, 8, 16, buf, 21, true);

    sleep_ms(100);
    ssd1306_clear(SSD1306_COLOR_WHITE);

    ssd1306_putascii_string(g_default_font, 20, 8, "Booting...", 51, true);
    sleep_ms(100);
}

static struct display_module ssd1306_module = {
    .name = DRV_NAME,
    .cfg = {
        .width       = SSD1306_HOR_RES_MAX,
        .height      = SSD1306_VER_RES_MAX,
        .bpp         = OLED_COLOR_DEPTH,
        .update_mode = EPINK_UPDATE_MODE_FULL,
    },
    .ops = {
        .module_init            = ssd1306_init,
        .module_blank           = ssd1306_blank,
        .module_clear           = ssd1306_clear,
        // .module_flush_part      = ssd1306_flush_part,
        .module_flush           = ssd1306_flush,
        .module_put_pixel       = ssd1306_put_pixel,
        .module_set_update_mode = ssd1306_set_update_mode,
    },
};

DISP_MODULE_DRIVER(ssd1306);