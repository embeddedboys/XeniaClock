/**
 * @file i2c.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-08
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
#include "i2c.h"

interrupt_declear(i2c_isr, 24)
{

}

/**
 * @brief 初始化I2C控制器
 *
 * 允许I2C功能
 * 设置为主机模式
 * 总线速度设置为100K（FOSC=11.0592MHz）
 *
 */
void i2c_init()
{
    P_SW2 = 0x80;
    // I2CCFG = 0xe0; /* FOSC 11.0592MHz  I2C 100KHz */
    // I2CCFG = 0xd0; /* FOSC 11.0592MHz  I2C 200KHz */
    // I2CCFG = 0xc8; /* FOSC 11.0592MHz  I2C 400KHz */
    // I2CCFG = 0xc4; /* FOSC 11.0592MHz  I2C 400KHz */
    // I2CCFG = 0xc2; /* FOSC 11.0592MHz  I2C 400KHz */
    I2CCFG = 0xc0; /* FOSC 11.0592MHz  I2C 400KHz */
    I2CMSST = 0x00; /* 清空主机状态寄存器 */

    I2CMSAUX &= ~(1 << 0); /* 禁用自动发送功能 */
}

/**
 * @brief I2C控制器等待查询方式
 *
 * 当处于主机模式的I2C控制器执行完成寄存器I2CMSCR中MSCMD命令后产生中断信号，
 * 硬件自动将I2CMSST的MSIF位置1，向CPU发送中断请求，响应中断后MSIF必须用软件清零。
 * 
 */
static void __i2c_wait()
{
    while( !( I2CMSST & 0x40 ) );

    I2CMSST &= ~0x40;
}

/**
 * @brief I2C总线起始命令
 *
 * MSCMD=0001
 * 发送START信号。如果当前I2C控制器处于空闲状态，
 * 即 MSBUSY (I2CMSST7）为0时，写此命令会使控制器进入忙状态，
 * 硬件自动将MSBUSY状态位置1，并开始发送START信号;
 * 若当前IC控制器处于忙状态，写此命令可触发发送START信号。
 *
 */
void i2c_start()
{
    I2CMSCR = 0x01;
    __i2c_wait();
}

/**
 * @brief I2C总线发送数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将I2CTXD寄存器里面数据按位送到SDA管脚上（先发送高位数据)。
 *
 * @param byte 要发送的数据
 */
void i2c_sendbyte( u8 byte )
{
    I2CTXD = byte;
    I2CMSCR = 0x02;
    __i2c_wait();
}

/**
 * @brief I2C总线接收ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将从SDA端口上读取的数据保存到MSACKI (I12CMSST.1)。
 * 
 */
void i2c_revack()
{
    I2CMSCR = 0x03;
    __i2c_wait();
}

/**
 * @brief I2C总线接受数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将从SDA端口上读取的数据依次左移到I2CRXD寄存器（先接收高位数据)。接
 * 
 * @return uint8_t 返回I2CRXD寄存器中的内容
 */
uint8_t i2c_readbyte()
{
    I2CMSCR = 0x04;
    __i2c_wait();
    return I2CRXD;
}

/**
 * @brief I2C总线发送ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndack()
{
    I2CMSST = 0x00;
    I2CMSCR = 0x05;
    __i2c_wait();
}

/**
 * @brief I2C总线发送NACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndnack()
{
    I2CMSST = 0x01;
    I2CMSCR = 0x05;
    __i2c_wait();
}

/**
 * @brief I2C总线停止命令
 * 
 * 发送STOP信号。写此命令后，TPC总线控制器开始发送STOP信号。
 * 信号发送完成后，硬件自动将MSBUSY状态位清零。
 * 
 */
void i2c_stop()
{
    I2CMSCR = 0x06;
    __i2c_wait();
}

/*------------- complex operations -------------*/
/**
 * @brief I2C组合命令，起始、发送数据、接收ACK。
 * 
 * 此命令为命令0001、命令0010、命令0011三个命令的组合，
 * 下此命令后控制器会依次执行这三个命令。
 * 
 * @param byte 要发送的数据
 */
void i2c_start_sendbyte_revack(u8 byte)
{
    I2CTXD = byte;
    I2CMSCR = 0x09;
    __i2c_wait();
}

/**
 * @brief I2C组合命令，发送数据、接收ACK。
 * 
 * 此命令为命令0010、命令0011两个命令的组合，
 * 下此命令后控制器会依次执行这两个命令。
 * 
 * @param byte 要发送的数据
 */
void i2c_sendbyte_revack(u8 byte)
{
    I2CTXD = byte;
    I2CMSCR = 0x0A;
}

/**
 * @brief I2C组合命令，接收数据，发送ACK命令。
 * 
 * 此命令为命令0100、命令0101两个命令的组合，下此命令后控制器会依次执行这两个命令。
 * 注意:此命令所返回的应答信号固定为ACK(0)，不受MSACKO位的影响。
 * 
 * @return uint8_t 返回I2CRXD中的内容
 */
u8 i2c_readbyte_sendack()
{
    I2CMSCR = 0x0B;
    __i2c_wait();
    return I2CRXD;
}

/**
 * @brief I2C组合命令，接收数据，发送NACK命令。
 * 
 * 此命令为命令0100、命令0101两个命令的组合，下此命令后控制器会依次执行这两个命令。
 * 注意:此命令所返回的应答信号固定为NAK (1)，不受MSACKO位的影响。
 * 
 * @return uint8_t 
 */
u8 i2c_readbyte_sendnack()
{
    I2CMSCR = 0x0C;
    __i2c_wait();
    return I2CRXD;
}


void i2c_test(void)
{
    i2c_start();
    i2c_sendbyte(0x78);
    i2c_sndack();
    i2c_sendbyte(0x88);
    i2c_sndack();
    i2c_stop();
}