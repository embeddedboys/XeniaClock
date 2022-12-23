/**
 * @file ep_luat.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-30
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

static const unsigned char EPD_1IN54_lut_full_update[] = {
    0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
    0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
    0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

static const unsigned char EPD_1IN54_lut_partial_update[] = {
    0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* ========== epink operations ========== */
/**
 * @brief Set a limited drawing area of controller
 * 
 * @param x1 X start of area
 * @param y1 Y start of area
 * @param x2 X end of area
 * @param y2 Y end of area
 */
static void ep_luat_set_window( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 )
{
    /* set start/end position address of x in ram */
    epink_write_command( 0x44 );
    epink_write_data( ( x1 >> 3 ) & 0xFF );
    epink_write_data( ( x2 >> 3 ) & 0xFF );
    
    /* set start/end position address of y in ram */
    epink_write_command( 0x45 );
    epink_write_data( y1 & 0xFF );
    epink_write_data( ( y1 >> 8 ) & 0xFF );
    epink_write_data( y2 & 0xFF );
    epink_write_data( ( y2 >> 8 ) & 0xFF );
}

/**
 * @brief Set the drawing position of controller
 * 
 * @param x 
 * @param y 
 */
static void ep_luat_set_cursor( uint8_t x, uint8_t y )
{
    /* set address counter of x in ram */
    epink_write_command( 0x4E );
    epink_write_data( ( x >> 3 ) & 0xFF );
    
    /* set address counter of y in ram */
    epink_write_command( 0x4F );
    epink_write_data( y & 0xFF );
    epink_write_data( ( y >> 8 ) & 0xFF );
}

/**
 * @brief Turn on display, and sync the data in GDDRAM to screen
 * 
 */
static void ep_luat_turn_on_display()
{
    epink_write_command( 0x22 ); // display update control 2
    epink_write_data( 0xC4 );
    epink_write_command( 0x20 ); // master activation
    epink_write_command( 0xFF ); // terminate frame read write
    
    epink_wait_busy();
}

#if EPINK_USE_INIT
void ep_luat_device_init( uint8_t mode )
{
    epink_reset();
    
    epink_write_command( 0x01 ); // driver output control
    epink_write_data( ( EPINK_HEIGHT - 1 ) & 0xFF );
    epink_write_data( ( ( EPINK_HEIGHT - 1 ) >> 8 ) & 0xFF );
    epink_write_data( 0x00 ); // GD = 0; SM = 0; TB = 0;
    
    epink_write_command( 0x0C ); // booster soft start
    epink_write_data( 0xD7 );
    epink_write_data( 0xD6 );
    epink_write_data( 0x9D );
    
    epink_write_command( 0x2C ); // write vcom register
    epink_write_data( 0xA8 );  // VCOM 7C
    
    epink_write_command( 0x3A ); // set dummy line period
    epink_write_data( 0x1A );  // 4 dummy lines per gate
    
    epink_write_command( 0x3B ); // set gate line width
    epink_write_data( 0x08 );  // 2us per line
    
    epink_write_command( 0x11 );
    epink_write_data( 0x03 );
    
    /* set the look-up table register */
    epink_write_command( 0x32 );
    
    if( mode == EPINK_UPDATE_MODE_FULL )
        for( uint8_t i = 0; i < ARRAY_SIZE( EPD_1IN54_lut_full_update ); i++ ) {
            epink_write_data( EPD_1IN54_lut_full_update[i] );
        }
    else if( mode == EPINK_UPDATE_MODE_PART )
        for( uint8_t i = 0; i < ARRAY_SIZE( EPD_1IN54_lut_partial_update ); i++ ) {
            epink_write_data( EPD_1IN54_lut_partial_update[i] );
        }
    else {
        EPINK_DEBUG( "epink_init: unknown update mode\n" );
    }
}

static int ep_luat_init(uint8_t mode)
{
    ep_luat_device_init(mode);
}
#else
static int (*ep_luat_init)(uint8_t mode) = NULL;
#endif

/**
 * @brief Directly clear the GDDRAM in controller
 * 
 * @param color 0xFF means white, 0x00 means black
 */
#if EPINK_USE_CLEAR
static void ep_luat_clear( uint8_t color )
{
    uint8_t width, height;
    width = ( EPINK_WIDTH % 8 == 0 ) ? ( EPINK_WIDTH / 8 ) :
            ( EPINK_WIDTH / 8 + 1 );
    height = EPINK_HEIGHT;
    
    ep_luat_set_window( 0, 0, EPINK_WIDTH, EPINK_HEIGHT );
    
    for( uint16_t i = 0; i < height; i++ ) {
        ep_luat_set_cursor( 0, i );
        epink_write_command( 0x24 );
        
        for( uint16_t j = 0; j < width; j++ ) {
            epink_write_data( color );
        }
    }
    
    ep_luat_turn_on_display();
}
#else
static void (*ep_luat_clear)(uint8_t color) = NULL;
#endif

#if EPINK_USE_FLUSH
void ep_luat_flush()
{
    uint8_t *pen = epink_disp_buffer;
    uint8_t width, height;
    width = (EPINK_WIDTH % 8 == 0) ? (EPINK_WIDTH / 8) :
            (EPINK_WIDTH / 8 + 1);
    height = EPINK_HEIGHT;

    ep_luat_set_window(0, 0, EPINK_WIDTH, EPINK_HEIGHT);

    for (uint8_t i = 0; i < height; i++) {
        ep_luat_set_cursor(0, i);
        epink_write_command(0x24);

        /* flush each line in buffer */
        for (uint8_t j = 0; j < width; j++) {
            epink_write_data(pen[j + i * 25]);
        }
    }

    // sleep_ms(100);
    ep_luat_turn_on_display();
}
#else
static void (*ep_luat_flush)() = NULL;
#endif

#if EPINK_USE_SET_UPDATE_MODE
static void ep_luat_set_update_mode(uint8_t mode)
{
    epink_write_command( 0x32 );
    
    if( mode == EPINK_UPDATE_MODE_FULL )
        for( uint8_t i = 0; i < ARRAY_SIZE( EPD_1IN54_lut_full_update ); i++ ) {
            epink_write_data( EPD_1IN54_lut_full_update[i] );
        }
    else if( mode == EPINK_UPDATE_MODE_PART )
        for( uint8_t i = 0; i < ARRAY_SIZE( EPD_1IN54_lut_partial_update ); i++ ) {
            epink_write_data( EPD_1IN54_lut_partial_update[i] );
        }
    else {
        EPINK_DEBUG( "epink_init: unknown update mode\n" );
    }
}
#else
static void (*ep_luat_set_update_mode)(uint8_t mode) = NULL;
#endif

#if EPINK_USE_BLANK
static void ep_luat_blank()
{
    ep_luat_init(EPINK_UPDATE_MODE_FULL);

    /*  a global clear before drawing operations  */
    ep_luat_clear(EPINK_COLOR_BLACK);
    sleep_ms(200);
    ep_luat_clear(EPINK_COLOR_WHITE);
    sleep_ms(200);

    ep_luat_init(EPINK_UPDATE_MODE_PART);

    ep_luat_clear(EPINK_COLOR_BLACK);
    sleep_ms(200);
    ep_luat_clear(EPINK_COLOR_WHITE);
    sleep_ms(200);
}
#else
static void (*ep_luat_blank)() = NULL;
#endif

#if EPINK_USE_PUT_PIXEL
static void ep_luat_put_pixel(uint16_t x, uint16_t y, uint8_t color)
{
    /* If we want to do a given pixel draw, the best
     * way might be draw it in a display buffer, because
     * most display controller like this "epink", usually
     * could enter a page write mode(check maunal of ssd1306),
     * It's really makes a speed up and reduces the
     * display buffer size we need to alloced.
     *
     * But the problems also goes on, In this mode, the eight pixel
     * bit data was conbined to a byte and write to controller directly
     * so we need to clac the given (x,y) in which page at display buffer
     * and use "|=", "&=" to operate the page then flush it to screen.
     *
     * Actually, the flush operation can be executed when you already
     * drawed all the pixel data to buffer
     *
     * These pages in display buffer looks like this :
     *      Y
     *    X ******** ******** ... ******** 25 page
     *      ******** ******** ... ********
     *         ...
     *      ******** ******** ... ********
     *      200 line
     *                                  5000 bytes
     * So we did it like blow
     */
    // uint8_t page, page_left;
    uint8_t *pen = epink_disp_buffer;
#ifdef EPINK_COORD_CHECK
    if ((x >= 0 && x < EPINK_WIDTH) && (y >= 0 && y < EPINK_HEIGHT)) {
#endif
        /* How to get the page in ram? */
        /* 1. Calc the "X" in which page of line */
        // page = x / 8;
        /* The page_left is the bit we need to set to page, will use later */
        // page_left = (x % 8 == 0) ? 0 : x % 8;
        // EPINK_DEBUG("page:%d, page_left:%d\n", page, page_left);
        
        /* 2. Get which line using "Y" */
        /* The number 25 means a line contains 25 page,
         * I should use a MARCO better, but in order to be
         * more intuitive and if we use "Y * 25 + page",
         * we can got the target page in display buffer,
         * then we just set the offset bit to 0 means draw
         * it into black.
         *
         * A little bit explanation of "1 << (7 - page_left)",
         * when we draw a page to screen, the lowest bit of
         * page corresponded the highest bit of byte in buffer.
         */
        if (color)
            // pen[y * 25 + (x / 8)] &= ~(1 << (7 - (x % 8)));
            pen[y * 25 + (x / 8)] &= ~(0x80 >> (x % 8));
        else
            // pen[y * 25 + (x / 8)] |= (1 << (7 - (x % 8)));
            pen[y * 25 + (x / 8)] |= (0x80 >> (x % 8));
            
        // EPINK_DEBUG("set:%d, clear:%d\n", (uint8_t)~(1 << page_left),
        //             (1 << page_left));
        // EPINK_DEBUG("which:%d, dump:%d\n", y * 25 + page, pen[y * 25 + page]);
        
#ifdef EPINK_COORD_CHECK
    }
    
#endif
}
#else
static void ep_luat_put_pixel(uint16_t x, uint16_t y, uint8_t color)
{

}
#endif

DISP_MODULE_REGISTER(ep_luat);