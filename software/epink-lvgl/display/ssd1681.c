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

static void ssd1681_device_init(uint8_t mode)
{
    epink_res_clr();
    sleep_ms(20);
    epink_res_set();
    sleep_ms(20);
    epink_wait_busy();

    epink_write_command(0x12);
    epink_wait_busy();

    epink_write_command(0x01);
    epink_write_data(0xC7);
    epink_write_data(0x00);
    epink_write_data(0x01);

    epink_write_command(0x11);
    epink_write_data(0x01);

    epink_write_command(0x44);
    epink_write_data(0x00);
    epink_write_data(0x18);

    epink_write_command(0x45);
    epink_write_data(0xC7);
    epink_write_data(0x00);
    epink_write_data(0x00);
    epink_write_data(0x00);

    epink_write_command(0x3C);
    epink_write_data(0x05);

    epink_write_command(0x18);
    epink_write_data(0x80);

    epink_write_command(0x4E);
    epink_write_data(0x00);
    epink_write_data(0x4F);
    epink_write_data(0xC7);
    epink_write_data(0x00);
    epink_wait_busy();
}

static void ssd1681_update(uint8_t mode)
{
    epink_write_command(0x22);
    // if (mode == EPINK_UPDATE_MODE_FULL)
        // epink_write_data(0xff);
    // else
    epink_write_data(0xf7);

    epink_write_command(0x20);
    epink_wait_busy();
}

static int ssd1681_init(uint8_t mode)
{
    ssd1681_device_init(mode);
}

void ssd1681_clear(uint8_t color)
{
    uint8_t *pen = epink_disp_buffer;
    uint8_t width, height;
    width = ( EPINK_WIDTH % 8 == 0 ) ? ( EPINK_WIDTH / 8 ) :
            ( EPINK_WIDTH / 8 + 1 );
    height = EPINK_HEIGHT;

    for( uint16_t i = 0; i < width * height; i++ ) {
        epink_write_command( 0x24 );

        /* flush each line in buffer */
        epink_write_data( color );
    }

    // sleep_ms(100);
    ssd1681_update(EPINK_UPDATE_MODE_FULL);
}

/**
 * @brief Flush each byte in display buffer to screen
 * 
 */
void ssd1681_flush()
{
    uint8_t *pen = epink_disp_buffer;
    uint8_t width, height;
    width = ( EPINK_WIDTH % 8 == 0 ) ? ( EPINK_WIDTH / 8 ) :
            ( EPINK_WIDTH / 8 + 1 );
    height = EPINK_HEIGHT;

    for( uint16_t i = 0; i < height * width; i++ ) {
        epink_write_command( 0x24 );

        /* flush each line in buffer */
        epink_write_data( pen[i] );
    }

    // sleep_ms(100);
    ssd1681_update(EPINK_UPDATE_MODE_PART);
}

void ssd1681_blank()
{
    ssd1681_clear(0x00);
    sleep_ms(200);
    ssd1681_clear(0xFF);
    sleep_ms(200);
}

DISP_MODULE_REGISTER(ssd1681);