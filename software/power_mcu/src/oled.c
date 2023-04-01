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

#include "common.h"
#include "list.h"
#include "ctype.h"
#include "types.h"

#include "i2c.h"
#include "i2c-gpio.h"

#include "oled.h"
#include "font.h"

#define SSD1306_CMD     (0x00)
#define SSD1306_DATA    (0x40)

#define SSD1306_ADDR    (0x78)
#define SSD1306_COLOR_BLACK     (0xff)
#define SSD1306_COLOR_WHITE     (0x00)

#define OFFSET(p, c) ((p)*128 + (c)-1)

static u8 __xdata oled_buffer[512] = {0}; /* oled display buffer */

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

void oled_flush()
{
	uint8_t page, col;

	for (page = 0; page < 8; page++)
		for (col = 0; col < 128; col++) {
            if (oled_buffer[OFFSET(page, col)] == 0x00)
                continue;
            
            oled_set_pos(page, col);
            oled_write_dat(oled_buffer[OFFSET(page, col)]);
        }
}

void oled_clear()
{
	uint8_t page, col;

	for (page = 0; page < 4; page++)
		for (col = 0; col < 128; col++)
			// if (oled_buffer[OFFSET(page, col)] > 0x00)
			{
				oled_set_pos(page, col);
				oled_write_dat(0);
			}
	// memset(oled_buffer, 0x0, 1024);
	// oled_flush();
}

void oled_device_init(void)
{
    // gpio_i2c_init();

    oled_write_cmd(0xae);//--display off
    // oled_write_cmd(0x00);
    // oled_write_cmd(0x10);
    oled_write_cmd(0x40);//---set low column address
    oled_write_cmd(0xb0);//---set high column address
    oled_write_cmd(0xc8);//-not offset
    oled_write_cmd(0x81);// contract control
    oled_write_cmd(0xff);//--128
    oled_write_cmd(0xa1);//set segment remap
    oled_write_cmd(0xa6);//--normal / reverse
    oled_write_cmd(0xa8);//--set multiplex ratio(1 to 64)
    oled_write_cmd(0x1f);
    oled_write_cmd(0xd3);//-set display offset
    oled_write_cmd(0x00);
    oled_write_cmd(0xd5);//set osc division
    oled_write_cmd(0xf0);
    oled_write_cmd(0xd9);//set pre-charge period
    oled_write_cmd(0x22);
    oled_write_cmd(0xda);//set com pin configuartion
    oled_write_cmd(0x02);
    oled_write_cmd(0xdb);//set vcomh
    oled_write_cmd(0x49);
    oled_write_cmd(0x8d);//set charge pump enable
    oled_write_cmd(0x14);
    delay();
    delay();
    oled_write_cmd(0xaf);//--turn on oled pan
}

static LIST_HEAD(g_str_head);

struct test_str {
    const char *str;
    struct list_head head;
};

struct test_str __xdata str1[] = {
    { .str = "08:00" },
    { .str = "08:01" },
    { .str = "08:02" },
    { .str = "08:03" },
    { .str = "08:04" },
    { .str = "08:05" },
    { .str = "08:06" },
};

void oled_init(void)
{
	int count = 0;
	oled_device_init();

	for (; count < 512; count++)
	{
		oled_buffer[count] = 0x00;
	}

    for(int i =0; i< ARRAY_SIZE(str1); i++) {
        list_add(&str1[i].head, &g_str_head);
    }
}

void oled_set_pixel(u8 x, u8 y, u8 color)
{
	u8 page;
	u8 *pen = oled_buffer;

    page = y / 8;

    if (color)
    {
        pen[OFFSET(page, x)] |= (1 << (y % 8));
    }
    else
    {
        pen[OFFSET(page, x)] &= ~(1 << (y % 8));
    }

	/*oled_set_pos(page, x);
	oled_write_dat(oled_buffer[offset]);*/
}

void oled_putchar(u8 page, u8 col, const char cha)
{
	int i;
	/* get the cha in oledfont */
	const u8 *dots = oled_asc2_8x16[cha - 48];
	u8 *pen = oled_buffer;

    if (!isdigit(cha)) {
        return;
    }

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page, col + i)] = 0x00;
		pen[OFFSET(page + 1, col + i)] = 0x00;
	}

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page, col + i)] = dots[i];
	}

	for (i = 0; i < 8; i++)
	{
		pen[OFFSET(page + 1, col + i)] = dots[i + 8];
	}
}

void oled_putstring(u8 page, u8 col, const char *str)
{
	while (*str != '\0')
	{
		oled_putchar(page, col, *str++);
		col += 8;
	}
}

void oled_test(void)
{
    oled_clear();
    // oled_putstring(0, 0, "Hello, world!");
    // oled_putstring(2, 0, "Bye, friend!");
    oled_putstring(1, 40, "18:30");
    // struct list_head *pos;
    // struct test_str *current;
    // list_for_each(pos, &g_str_head) {
        // current = list_entry(pos, struct test_str, head);
        // oled_putstring(1, 40, current->str);
    // }

    oled_flush();
}