/**
 * @file st7789v.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-29
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

#include "display/epd.h"
#include "display/display_manager.h"
#include "pico/time.h"

enum st7789v_command {
    NOP       = 0x00,   // No operation
    SWRESET   = 0x01,   // Software reset
    RDDID     = 0x04,   // Read display identification information
    RDDST     = 0x09,   // Read display status
    RDDPM     = 0x0A,   // Read display power mode
    RDDMADCTL = 0x0B,   // Read display MADCTL
    RDDCOLMOD = 0x0C,   // Read display pixel format
    RDDIM     = 0x0D,   // Read display image mode
    RDDSM     = 0x0E,   // Read display signal mode
    RDDSDR    = 0x0F,   // Read display self-diagnostic result
    SLPIN     = 0x10,   // Enter sleep mode
    SLPOUT    = 0x11,   // Sleep out
    PTLON     = 0x12,   // Partial mode on
    NORON     = 0x13,   // Normal display mode on
    INVOFF    = 0x20,   // Display inversion off
    INVON     = 0x21,   // Display inversion on
    GAMSET    = 0x26,   // Gamma set
    DISPOFF   = 0x28,   // Display off
    DISPON    = 0x29,   // Display on
    CASET     = 0x2A,   // Column address set
    RASET     = 0x2B,   // Row address set
    RAMWR     = 0x2C,   // Memory write
    RAMRD     = 0x2E,   // Memory read
    PTLAR     = 0x30,   // Partial start/end address set
    VSCRDEF   = 0x33,   // Vertical scrolling definition
    TEOFF     = 0x34,   // Tearing effect line off
    TEON      = 0x35,   // Tearing effect line on
    MADCTL    = 0x36,   // Memory data access control
    VSCRSADD  = 0x37,   // Vertical scrolling start address
    IDMOFF    = 0x38,   // Idle mode off
    IDMON     = 0x39,   // Idle mode on
    COLMOD    = 0x3A,   // Interface pixel format
    RAMWRC    = 0x3C,   // Memory write continue
    RAMRDC    = 0x3E,   // Memory read continue
    TESCAN    = 0x44,   // Set tear scanline
    RDTESCAN  = 0x45,   // Read tear scanline
    WRDISBV   = 0x51,   // Write display brightness
    RDDISBV   = 0x52,   // Read display brightness
    WRCTRLD   = 0x53,   // Write control display
    RDCTRLD   = 0x54,   // Read control display
    WRCACE    = 0x55,   // Write content adaptive brightness control
    RDCACB    = 0x56,   // Read content adaptive brightness control
    WRCABCMB  = 0x5E,   // Write CABC minimum brightness
    RDCABCMB  = 0x5F,   // Read CABC minimum brightness
    RDABCSDR  = 0x68,   // Read auto brightness control self-diagnostic result
    RDID1     = 0xDA,   // Read ID1
    RDID2     = 0xDB,   // Read ID2
    RDID3     = 0xDC,   // Read ID3
};

#define DRV_NAME "st7789v"

#define ST7789V_HOR_RES     240
#define ST7789V_VER_RES     240
#define ST7789V_BPP         16

#define ST7789V_OFFSET_X    20
#define ST7789V_OFFSET_Y    0

#ifndef ST7789V_INVERT_MODE
    #define ST7789V_INVERT_MODE 0
#endif

#if ST7789V_INVERT_MODE
    #define ST7789V_COLOR_BLACK 0xffff
    #define ST7789V_COLOR_WHITE 0x0000
#else
    #define ST7789V_COLOR_BLACK 0x0000
    #define ST7789V_COLOR_WHITE 0xffff
#endif

#ifndef ST7789V_BUFFER_FLUSH
    #define ST7789V_BUFFER_FLUSH 1
#endif


/* TODO: port st7789v 240x240 display here */

static void st7789v_set_cursor(uint32_t x, uint32_t y)
{
    epink_write_command(0x2A);     //Column Address Set
    epink_write_data(0x00);
    epink_write_data((x & 0xFF));     //0
    epink_write_data(0x00);
    epink_write_data(0xEF);   //239
    
    epink_write_command(0x2B);     //Row Address Set
    epink_write_data(0x00);
    epink_write_data((y & 0xFF));     //0
    epink_write_data(0x00);
    epink_write_data(0xEF);
}

static void st7789v_draw_pixel_immediately(uint32_t x, uint32_t y,
                                           uint16_t color)
{
    st7789v_set_cursor(x, y);
    
    epink_write_command(0x2c);
    epink_write_data(color >> 8);
    epink_write_data(color & 0xFF);
}

static void st7789v_device_init(uint8_t mode)
{
    epink_reset();
    sleep_ms(50);
    
    // st7789v_write_command(SWRESET);
    epink_write_command(0x11);
    
    sleep_ms(120);
    
    epink_write_command(MADCTL);
    epink_write_data(0x00);
    
    epink_write_command(COLMOD);
    epink_write_data(0x05); /* RGB565 */
    
    epink_write_command(0xB2);
    epink_write_data(0x0C);
    epink_write_data(0x0C);
    epink_write_data(0x00);
    epink_write_data(0x33);
    epink_write_data(0x33);
    
    epink_write_command(0xB7);
    epink_write_data(0x35);
    
    epink_write_command(0xBB);
    epink_write_data(0x32);
    
    // epink_write_command(0xC0);
    // epink_write_data(0x2C);
    
    epink_write_command(0xC2);
    epink_write_data(0x01);
    
    epink_write_command(0xC3);
    epink_write_data(0x15);
    
    epink_write_command(0xC4);
    epink_write_data(0x20);   //VDV, 0x20:0v
    
    epink_write_command(0xC6);
    epink_write_data(0x0F);   //0x0F:60Hz
    
    epink_write_command(0xD0);
    epink_write_data(0xA4);
    epink_write_data(0xA1);
    
    // epink_write_command(0xD6);
    // epink_write_data(0xA1);   // after sleeping in，gate输出为GND
    
    epink_write_command(0xE0);
    epink_write_data(0xD0);
    epink_write_data(0x08);
    epink_write_data(0x0E);
    epink_write_data(0x09);
    epink_write_data(0x09);
    epink_write_data(0x05);
    epink_write_data(0x31);
    epink_write_data(0x33);
    epink_write_data(0x48);
    epink_write_data(0x17);
    epink_write_data(0x14);
    epink_write_data(0x15);
    epink_write_data(0x31);
    epink_write_data(0x34);
    
    epink_write_command(0xE1);
    epink_write_data(0xD0);
    epink_write_data(0x08);
    epink_write_data(0x0E);
    epink_write_data(0x09);
    epink_write_data(0x09);
    epink_write_data(0x15);
    epink_write_data(0x31);
    epink_write_data(0x33);
    epink_write_data(0x48);
    epink_write_data(0x17);
    epink_write_data(0x14);
    epink_write_data(0x15);
    epink_write_data(0x31);
    epink_write_data(0x34);
    
    // epink_write_command(0xE4);
    // epink_write_data(0x25);   // use 240 gates (N+1)*8
    // epink_write_data(0x00);   //set gate start position
    // epink_write_data(0x00);   // whne gate isn't run out，set bit4(TMG) to 0
    
    epink_write_command(0x21);
    
    epink_write_command(0x29);
    
    // epink_write_command(0x2A);     //column address Set
    // epink_write_data(0x00);
    // epink_write_data(0x00);   //0
    // epink_write_data(0x00);
    // epink_write_data(0xEF);   //239
    
    // epink_write_command(0x2B);     //row address Set
    // epink_write_data(0x00);
    // epink_write_data(0x00);   //0
    // epink_write_data(0x00);
    // epink_write_data(0xEF);   //239
}

static inline int st7789v_init(uint8_t mode)
{
    st7789v_device_init(mode);
}

static void st7789v_clear(uint16_t color)
{
    for(int x = 0; x < ST7789V_HOR_RES; x++)
        for(int y = 0; y < ST7789V_VER_RES; y++) {
            st7789v_set_cursor(x, y);
            epink_write_command(0x2c);
            epink_write_data(color >> 8);
            epink_write_data(color & 0xff);
        }
}

static void st7789v_flush()
{
#if ST7789V_BUFFER_FLUSH
    uint8_t *cursor = epink_disp_buffer;
    uint8_t *cursor_old = epink_disp_buffer_old;
    uint8_t byte;
    
    for(int y = 0; y < EPINK_HEIGHT; y++) {
        for(int page = 0; page < EPINK_LINE_WIDTH_IN_PAGE; page++) {
            byte = cursor[y * EPINK_LINE_WIDTH_IN_PAGE + page];
            
            /* if this byte same with the last frame, wo don't need go futher */
            if(byte == cursor_old[y * EPINK_LINE_WIDTH_IN_PAGE + page])
                continue;
                
            /* for bits in this byte, flush to screen */
            for(int bit = 0; bit < EPINK_PAGE_SIZE; bit++) {
                st7789v_draw_pixel_immediately(page * EPINK_PAGE_SIZE + bit + ST7789V_OFFSET_X, y,
                                            ((byte << bit) & 0x80) ? ST7789V_COLOR_BLACK : ST7789V_COLOR_WHITE);
            }
        }
    }

    /* save this frame to old buffer */
    memcpy(epink_disp_buffer_old, epink_disp_buffer, EPINK_DISP_BUFFER_SIZE);
#else
#endif
}

static void st7789v_blank()
{
    st7789v_init(0);
    st7789v_clear(0xffff);
}

static void st7789v_set_update_mode(uint8_t mode)
{

}

static void st7789v_put_pixel(uint16_t x, uint16_t y, uint16_t color)
{
#if ST7789V_BUFFER_FLUSH
    uint8_t *pen = epink_disp_buffer;

    if(color)
        pen[y * EPINK_LINE_WIDTH_IN_PAGE + (x / EPINK_PAGE_SIZE)] |= (0x80 >>
                                                                       (x % EPINK_PAGE_SIZE));
    else
        pen[y * EPINK_LINE_WIDTH_IN_PAGE + (x / EPINK_PAGE_SIZE)] &= ~(0x80 >>
                                                                      (x % EPINK_PAGE_SIZE));
#else
    st7789v_draw_pixel_immediately(x + ST7789V_OFFSET_X, y + ST7789V_OFFSET_X, ~color);
#endif
}

void st7789v_test(void)
{
    // st7789v_init(1);
    
    // for (int x = 0; x < ST7789V_HOR_RES; x++)
    //     for (int y = 0; y < ST7789V_VER_RES; y++)
    //         st7789v_draw_pixel_immediately(x, y, 0xffff);
    struct display_module *p_disp = request_disp_module(DRV_NAME);
    p_disp->ops.module_init(0);
    
    for(int x = 0; x < ST7789V_HOR_RES; x++)
        for(int y = 0; y < ST7789V_VER_RES; y++) {
            // p_disp->ops.module_put_pixel(x, y, 0x0);
            st7789v_draw_pixel_immediately(x, y, 0xffff);
            sleep_ms(1);
        }
}

static struct display_module st7789v_module = {
    .name = DRV_NAME,
    .cfg = {
        .width = ST7789V_HOR_RES,
        .height = ST7789V_VER_RES,
        .bpp = ST7789V_BPP,
        .update_mode = 0,
    },
    .ops = {
        .module_init      = st7789v_init,
        .module_blank     = st7789v_blank,
        .module_clear     = st7789v_clear,
        .module_flush     = st7789v_flush,
        .module_put_pixel = st7789v_put_pixel,
        .module_set_update_mode = st7789v_set_update_mode,
    },
};

DISP_MODULE_DRIVER(st7789v);