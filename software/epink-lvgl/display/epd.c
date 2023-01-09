/**
 * @file epd.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-17
 *
 * This is a simple driver for the LuatOS epink-1.54 screen module.
 *
 * the device init function in this file was based on :
 * https://gitee.com/openLuat/LuatOS/blob/master/components/epaper/EPD_1in54.c
 *
 * More info about the epaper module can be found in :
 * https://wiki.luatos.com/peripherals/eink_1.54/index.html
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

#include "epd.h"
#include <stddef.h>

uint8_t epink_disp_buffer[EPINK_DISP_BUFFER_SIZE];
uint8_t epink_disp_buffer_old[EPINK_DISP_BUFFER_SIZE];
// static uint8_t *pen = epink_disp_buffer;

/* ========== epink pin controls ========== */
#ifdef EPINK_CS_PIN
inline void cs_select()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_CS_PIN, 0);   // Active low
    asm volatile("nop \n nop \n nop");
}

inline void cs_deselect()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_CS_PIN, 1);
    asm volatile("nop \n nop \n nop");
}
#endif

inline void epink_dc_set()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_DC_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

inline void epink_dc_clr()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_DC_PIN, 0);
    asm volatile("nop \n nop \n nop");
}

inline void epink_res_set()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_RES_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

inline void epink_res_clr()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(EPINK_RES_PIN, 0);
    asm volatile("nop \n nop \n nop");
}

void epink_reset()
{
    epink_res_set();
    busy_wait_ms(20);
    
    epink_res_clr();
    busy_wait_ms(2);
    
    epink_res_set();
    busy_wait_ms(20);
}

/* ========== epink I/O ========== */

inline void epink_write_byte(uint8_t val)
{
    spi_write8(val, EPINK_CS_PIN);
}

void epink_write_command(uint8_t command)
{
    epink_dc_clr();
    epink_write_byte(command);
}

void epink_write_data(uint8_t data)
{
    epink_dc_set();
    epink_write_byte(data);
}

/**
 * @brief Read the "busy" state pin to know if controller was busy,
 * but gives a timeout
 *
 * @param timeout
 */
static void epink_wait_busy_timeout(uint32_t timeout)
{
    while (gpio_get(EPINK_BUSY_PIN)) {
        if (timeout-- == 0) {
            EPINK_DEBUG("epink_wait_busy timeout\n");
            break;
        } else {
            busy_wait_ms(100);
        }
    }
    
    EPINK_DEBUG("epink_wait_busy_timeout ok\n");
}

/**
 * @brief Read the "busy" state pin to know if controller was busy
 *
 */
void epink_wait_busy()
{
    while (gpio_get(EPINK_BUSY_PIN));
}

/**
 * @brief Real initialize function of epink, it
 * initialize the controller and display buffer
 *
 * @param mode update mode of epink panel
 */
void epink_init(uint8_t mode)
{
    // epink_device_init(mode);
    // default_module = *request_disp_module("ssd1681");
    if (!default_module.ops.module_init) {
        EPINK_ERROR("This module [%s] doesn't exposed a {init} function!\n", default_module.name);
        return;
    }

    default_module.ops.module_init(mode);
    memset(epink_disp_buffer, EPINK_COLOR_WHITE, ARRAY_SIZE(epink_disp_buffer));
}

/**
 * @brief Flush each byte in display buffer to screen
 *
 */
void epink_flush()
{
    if (!default_module.ops.module_flush) {
        EPINK_ERROR("This module [%s] doesn't exposed a {flush} function!\n", default_module.name);
        return;
    }

    default_module.ops.module_flush();
}

/**
 * @brief Directly clear the GDDRAM in controller
 *
 * @param color 0xFF means white, 0x00 means black
 */
void epink_clear(uint8_t color)
{
    if (default_module.ops.module_clear) {
        EPINK_ERROR("This module [%s] doesn't exposed a {clear} function!\n", default_module.name);
        return;
    }

    default_module.ops.module_clear(color);
}

void epink_blank()
{
    if (!default_module.ops.module_blank) {
        EPINK_ERROR("This module [%s] doesn't exposed a {blank} function!\n \
                    Using a default blank ops\n", default_module.name);
        
        epink_init(EPINK_UPDATE_MODE_FULL);
        
        /*  a global clear before drawing operations  */
        epink_clear(0x00);
        sleep_ms(200);
        epink_clear(0xFF);
        sleep_ms(200);
        
        epink_init(EPINK_UPDATE_MODE_PART);
        
        epink_clear(0x00);
        sleep_ms(200);
        epink_clear(0xFF);
        sleep_ms(200);

        return;
    }

    default_module.ops.module_blank();
}

/**
 * @brief Makes controller into sleep mode
 *
 */
static void epink_sleep()
{
    epink_write_command(0x10);
    epink_write_data(0x01);
}

/* ========== epink drawing functions ========== */
static void __make_random_dram_data()
{
    for (int i = 0; i < ARRAY_SIZE(epink_disp_buffer); i++) {
        epink_disp_buffer[i] = 0x49;
    }
}

/**
 * @brief Simply clear the display buffer to 0xFF
 */
void epink_buffer_clear()
{
    for (int i = 0; i < ARRAY_SIZE(epink_disp_buffer); i++) {
        epink_disp_buffer[i] = 0xFF;
    }
}

void epink_set_backlight_level(uint8_t level)
{
    
}

/**
 * @brief draw a given position pixel to display buffer
 *
 * @param x draw position of X
 * @param y draw position os Y
 * @param color 1 means black, 0 means white
 */
void epink_draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
    default_module.ops.module_put_pixel(x, y, color);
}

/**
 * @brief Put a single ascii char to panel
 *
 * @param x start position of X
 * @param y start position of Y
 * @param c char that will outputting to panel
 */
static void epink_putascii(uint8_t x, uint8_t y, char c)
{
    /* Get the char in ascii array, each char use 16 byte to store */
    const unsigned char *dots = (uint8_t *)&fontdata_8x16[c * 16];
    uint8_t *pen = epink_disp_buffer;
    uint8_t row, col, byte;
    
    /* In this case, we use a 8x16 size font, so
     * we need to draw 16 byte totally, for each
     * byte, draw it's each bit from higher to low
     */
    for (row = 0; row < 16; row++) {
        byte = dots[row];
        
        for (col = 0; col < 8; col++) {
            epink_draw_pixel(x + col, y + row, (byte << col) & 0x80);
        }
    }
}

/**
 * @brief Put ascii string to panel
 *
 * @param x start position of X
 * @param y start position of Y
 * @param str string that will outputting to the panel
 */
static void epink_putascii_string(uint8_t x, uint8_t y, char *str)
{
    while (*str != '\0') {
        epink_putascii(x, y, *str++);
        x += 8; /* move x to the next pos */
        
        /* start a new line if reach the end of line */
        if (x >= EPINK_WIDTH) {
            x = 0;
            y += 16; /* line hight min:16 */
        }
    }
}
