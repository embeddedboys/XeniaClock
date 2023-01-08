/**
 * @file ssd1681.c
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
#include "pico/time.h"

#if DISPLAY_MAIN_PANEL_USE_SSD1681

static void ssd1681_set_window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    epink_reset();
    
    epink_write_command(0x3c); //BorderWavefrom,
    epink_write_data(0x80);
    
    /* set start/end position address of x in ram */
    epink_write_command(0x44);
    epink_write_data(x1 & 0x3f);
    epink_write_data(x2 & 0x3f);
    
    /* set start/end position address of y in ram */
    epink_write_command(0x45);
    epink_write_data(y1 & 0xff);
    epink_write_data((y1 >> 8) & 0x01);
    epink_write_data(y2 & 0xff);
    epink_write_data((y2 >> 8) & 0x01);
}

static void ssd1681_set_cursor(uint8_t x, uint8_t y)
{
    /* set address counter of x in ram */
    epink_write_command(0x4e);
    epink_write_data(x & 0x3f);
    
    /* set address counter of y in ram */
    epink_write_command(0x4f);
    epink_write_data(y & 0xff);
    epink_write_data((y >> 8) & 0x01);
}

#if EPINK_USE_INIT
static void ssd1681_device_init(uint8_t mode)
{
    epink_reset();
    
    epink_write_command(0x12);
    epink_wait_busy();
    
    epink_write_command(0x01);
    epink_write_data(0xc7);
    epink_write_data(0x00);
    epink_write_data(0x00);
    
    epink_write_command(0x11);
    epink_write_data(0x01);
    
    epink_write_command(0x44);
    epink_write_data(0x00);
    epink_write_data(0x18);
    
    epink_write_command(0x45);
    epink_write_data(0xc7);
    epink_write_data(0x00);
    epink_write_data(0x00);
    epink_write_data(0x00);

    // epink_write_command(0x37);
    // epink_write_data(0x00);
    // epink_write_data(0xff);
    // epink_write_data(0xff);
    // epink_write_data(0xff);
    // epink_write_data(0xff);
    // epink_write_data(0x4f); /* Enable RAM ping-pong mode */
    // epink_write_data(0x00);
    // epink_write_data(0x00);
    // epink_write_data(0x00);
    // epink_write_data(0x00);

    epink_write_command(0x3c);
    epink_write_data(0x05);
    
    epink_write_command(0x18);
    epink_write_data(0x80);
    
    epink_write_command(0x4e);
    epink_write_data(0x00);
    epink_write_data(0x4f);
    epink_write_data(0xc7);
    epink_write_data(0x00);
    epink_wait_busy();
    
    // epink_write_command(0x22);
    // if (mode == EPINK_UPDATE_MODE_FULL)
    //     epink_write_data(0xf7);
    // else
    //     epink_write_data(0xff);
}

static int ssd1681_init(uint8_t mode)
{
    ssd1681_device_init(mode);

    return 0;
}
#else
static int ssd1681_init(uint8_t mode)
{
    return 0;
}
#endif

static void ssd1681_update()
{
    epink_write_command(0x22);
    epink_write_data(0xff);
    epink_write_command(0x20);
    epink_wait_busy();
}

#if EPINK_USE_FLUSH
static void ssd1681_clear(uint16_t color)
{
    // uint8_t width, height;
    // width = ( EPINK_WIDTH % 8 == 0 ) ? ( EPINK_WIDTH / 8 ) :
    //         ( EPINK_WIDTH / 8 + 1 );
    // height = EPINK_HEIGHT;
    
    // ssd1681_set_window( 0, 0, EPINK_WIDTH, EPINK_HEIGHT );
    // epink_write_command( 0x24 );
    
    // for( uint16_t i = 0; i < height; i++ ) {
    //     ssd1681_set_cursor( 0, i );
    
    //     for( uint16_t j = 0; j < width; j++ ) {
    //         epink_write_data( color );
    //     }
    // }
    
    /* Clear RED pixel RAM ? */
    // epink_write_command(0x26);
    // for (uint16_t i = 0; i < EPINK_DISP_BUFFER_SIZE; i++) {
    //     /* flush each line in buffer */
    //     epink_write_data(0xff);
    // }
    epink_write_command(0x24);
    for (uint16_t i = 0; i < EPINK_DISP_BUFFER_SIZE; i++) {
        epink_write_data(color);
    }
    
    ssd1681_update();
}
#else
static void ssd1681_clear(uint8_t color)
{

}
#endif

static void ssd1681_part_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

}

/**
 * @brief Flush each byte in display buffer to screen
 */
#if EPINK_USE_FLUSH
static void ssd1681_flush()
{
    uint8_t *pen = epink_disp_buffer;
    // uint8_t *pen_old = epink_disp_buffer_old;

    // epink_reset();

    epink_write_command(0x3c);
    epink_write_data(0x80);

    epink_write_command(0x24);
    for (uint16_t i = 0; i < EPINK_DISP_BUFFER_SIZE; i++) {
        // if (pen[i] == pen_old[i])
        //     continue;
        epink_write_data(pen[i]);
    }
    
    ssd1681_update();
    // memcpy(epink_disp_buffer_old, epink_disp_buffer, EPINK_DISP_BUFFER_SIZE);
}
#else
static void ssd1681_flush()
{

}
#endif

#if EPINK_USE_BLANK
static void ssd1681_blank()
{
    ssd1681_init(EPINK_UPDATE_MODE_FULL);
    ssd1681_clear(EPINK_COLOR_BLACK);
    ssd1681_clear(EPINK_COLOR_WHITE);
    ssd1681_init(EPINK_UPDATE_MODE_PART);
    // sleep_ms(200);
}
#else
static void ssd1681_blank()
{

}
#endif

#if EPINK_USE_SET_UPDATE_MODE
static void ssd1681_set_update_mode(uint8_t mode)
{

}
#else
static void ssd1681_set_update_mode(uint8_t mode)
{

}
#endif

#if EPINK_USE_PUT_PIXEL
static void ssd1681_put_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t *pen = epink_disp_buffer;
    
    if (color)
        pen[y * 25 + (x / 8)] &= ~(0x80 >> (x % 8));
    else
        pen[y * 25 + (x / 8)] |= (0x80 >> (x % 8));
}
#else
static void ssd1681_put_pixel(uint16_t x, uint16_t y, uint8_t color)
{

}
#endif

void ssd1681_test()
{
    ssd1681_init(EPINK_UPDATE_MODE_FULL);
    // memset(epink_disp_buffer, EPINK_COLOR_WHITE, ARRAY_SIZE(epink_disp_buffer));
    
    // ssd1681_clear(EPINK_COLOR_WHITE);
    // ssd1681_clear(EPINK_COLOR_BLACK);
    // sleep_ms(200);
    // sleep_ms(200);
    
    for (int x = 0, y = 0; x < 200; x++, y++) {
        ssd1681_put_pixel(x, y, EPINK_COLOR_WHITE);
        ssd1681_put_pixel(x + 1, y, EPINK_COLOR_BLACK);
        ssd1681_put_pixel(x + 2, y, EPINK_COLOR_BLACK);
        ssd1681_put_pixel(x + 3, y, EPINK_COLOR_BLACK);
    }
    ssd1681_flush();
}

DISP_MODULE_REGISTER(ssd1681);
#endif
