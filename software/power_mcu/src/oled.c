/**
 * @file oled.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-31
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

#include "i2c.h"
#include "i2c-gpio.h"

#include "oled.h"

#define SSD1306_CMD     (0x00)
#define SSD1306_DATA    (0x40)

#define SSD1306_ADDR    (0x78)
#define SSD1306_COLOR_BLACK     (0xff)
#define SSD1306_COLOR_WHITE     (0x00)

#if 1
void oled_write_cmd(u8 val)
{
    i2c_start();
    i2c_sendbyte(SSD1306_ADDR);
    i2c_revack();
    i2c_sendbyte(SSD1306_CMD);
    i2c_revack();
    i2c_sendbyte(val);
    i2c_revack();
    i2c_stop();
}

void oled_write_dat(u8 val)
{
    i2c_start();
    i2c_sendbyte(SSD1306_ADDR);
    i2c_revack();
    i2c_sendbyte(SSD1306_DATA);
    i2c_revack();
    i2c_sendbyte(val);
    i2c_revack();
    i2c_stop();
}
#else
void oled_write_cmd(u8 val)
{
    gpio_i2c_start();
    gpio_i2c_sendbyte(SSD1306_ADDR);
    gpio_i2c_sndack();
    gpio_i2c_sendbyte(SSD1306_CMD);
    gpio_i2c_sndack();
    gpio_i2c_sendbyte(val);
    gpio_i2c_sndack();
    gpio_i2c_stop();
}

void oled_write_dat(u8 val)
{
    gpio_i2c_start();
    gpio_i2c_sendbyte(SSD1306_ADDR);
    gpio_i2c_sndack();
    gpio_i2c_sendbyte(SSD1306_DATA);
    gpio_i2c_sndack();
    gpio_i2c_sendbyte(val);
    gpio_i2c_sndack();
    gpio_i2c_stop();
}
#endif

static void oled_set_pos(uint8_t page, uint8_t col)
{
    oled_write_cmd(0xb0 + page);

    oled_write_cmd(0x00 | (col & 0x0f));
    oled_write_cmd(0x10 | (col >> 4));
}

void delay()       //@11.0592MHz
{
    unsigned char i, j;

    i = 144;
    j = 157;
    do {
        while (--j);
    } while (--i);
}

void oled_init(void)
{
    // gpio_i2c_init();

    oled_write_cmd(0xAE);//--display off
    // oled_write_cmd(0x00);
    // oled_write_cmd(0x10);
    oled_write_cmd(0x40);//---set low column address
    oled_write_cmd(0xB0);//---set high column address
    oled_write_cmd(0xC8);//-not offset
    oled_write_cmd(0x81);// contract control
    oled_write_cmd(0xFF);//--128
    oled_write_cmd(0xA1);//set segment remap
    oled_write_cmd(0xA6);//--normal / reverse
    oled_write_cmd(0xA8);//--set multiplex ratio(1 to 64)
    oled_write_cmd(0x1F);
    oled_write_cmd(0xD3);//-set display offset
    oled_write_cmd(0x00);
    oled_write_cmd(0xD5);//set osc division
    oled_write_cmd(0xF0);
    oled_write_cmd(0xD9);//Set Pre-Charge Period
    oled_write_cmd(0x22);
    oled_write_cmd(0xDA);//set com pin configuartion
    oled_write_cmd(0x02);
    oled_write_cmd(0xDB);//set Vcomh
    oled_write_cmd(0x49);
    oled_write_cmd(0x8D);//set charge pump enable
    oled_write_cmd(0x14);
    delay();
    delay();
    oled_write_cmd(0xAF);//--turn on oled pan
}

void oled_test(void)
{
    u8 page, col;

    for (page = 0; page < 8; page ++)
        for( col =0; col < 128; col++) {
            oled_set_pos(page,col);
            oled_write_dat(0x00);
        }

    for (page = 0; page < 8; page ++)
        for( col =0; col < 128; col++) {
            oled_set_pos(page,col);
            oled_write_dat(0xff);
        }
}