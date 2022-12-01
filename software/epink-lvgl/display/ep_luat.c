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

/**
 * @brief Directly clear the GDDRAM in controller
 * 
 * @param color 0xFF means white, 0x00 means black
 */
void ep_luat_clear( uint8_t color )
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

// void ep_luat_blank()
// {
//     ep_luat_init(EPINK_UPDATE_MODE_FULL);

//     /*  a global clear before drawing operations  */
//     ep_luat_clear(0x00);
//     sleep_ms(200);
//     ep_luat_clear(0xFF);
//     sleep_ms(200);

//     ep_luat_init(EPINK_UPDATE_MODE_PART);

//     ep_luat_clear(0x00);
//     sleep_ms(200);
//     ep_luat_clear(0xFF);
//     sleep_ms(200);
// }

DISP_MODULE_REGISTER(ep_luat);