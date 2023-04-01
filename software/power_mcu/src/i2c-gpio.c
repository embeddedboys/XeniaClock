/**
 * @file i2c-gpio.c
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

#include "stc8g.h"
#include "common.h"

#include "i2c-gpio.h"

#define delay() nop(); nop(); nop(); nop(); nop();

static volatile  inline  void __gpio_i2c_set_scl(u8 val)
{
    GPIO_I2C_SCL = val;
}

static volatile inline void __gpio_i2c_set_sda(u8 val)
{
    GPIO_I2C_SDA = val;
}

volatile  static u8 __gpio_i2c_get_sda()
{
    return GPIO_I2C_SDA;
}

volatile  void gpio_i2c_init()
{
    /* set config */
    __gpio_i2c_set_scl( 0 );
    __gpio_i2c_set_sda( 1 );
}

volatile  void gpio_i2c_start()
{
    __gpio_i2c_set_scl( 1 );

    delay();
    __gpio_i2c_set_sda( 1 );
    __gpio_i2c_set_sda( 0 );
    delay();

    __gpio_i2c_set_scl( 0 );
}

volatile void gpio_i2c_stop()
{
    __gpio_i2c_set_scl( 1 );

    __gpio_i2c_set_sda( 0 );
    __gpio_i2c_set_sda( 1 );
    delay();

    __gpio_i2c_set_scl( 0 );
}

volatile uint8_t gpio_i2c_revack()
{
    __gpio_i2c_set_scl( 1 );
    delay();
    __gpio_i2c_set_scl( 0 );
    return __gpio_i2c_get_sda();
}

volatile void gpio_i2c_sndack()
{
    __gpio_i2c_set_sda( 0 );
    __gpio_i2c_set_scl( 1 );
    __gpio_i2c_set_scl( 0 );
    __gpio_i2c_set_sda( 1 );
}

volatile  void gpio_i2c_sndnack()
{

}

volatile  uint8_t gpio_i2c_readbyte()
{
    int i;
    uint8_t byte_read = 0x00;

    for( i = 0; i < 8; i++ ) {
        byte_read |= __gpio_i2c_get_sda() ? 1:0;
        delay();
        __gpio_i2c_set_scl( 1 );
        delay();
        __gpio_i2c_set_scl( 0 );
        byte_read <<= 1;
    }

    return byte_read;
}

volatile  void gpio_i2c_sendbyte( uint8_t byte_in )
{
    int i;

    for( i = 0; i < 8; i++ ) {
        __gpio_i2c_set_sda( ( byte_in & 0x80 ) ? 1 : 0 );
        delay();
        __gpio_i2c_set_scl( 1 );
        delay();
        __gpio_i2c_set_scl( 0 );
        byte_in <<= 1;
    }
    __gpio_i2c_set_sda( 0 );
}