/**
 * @file i2c.h
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

#ifndef __POWER_MCU_I2C_H
#define __POWER_MCU_I2C_H

#include "stc8g.h"

/**********************
* GLOBAL PROTOTYPES
**********************/

/**
 * @brief i2c_init 初始化I2C控制器
 *
 * 允许I2C功能
 * 设置为主机模式
 * 总线速度设置为400K（FOSC=24MHz）
 *
 */
void i2c_init();

/**
 * @brief i2c_start I2C总线起始命令
 *
 * MSCMD=0001
 * 发送START信号。如果当前I2C控制器处于空闲状态，
 * 即 MSBUSY (I2CMSST7）为0时，写此命令会使控制器进入忙状态，
 * 硬件自动将MSBUSY状态位置1，并开始发送START信号;
 * 若当前IC控制器处于忙状态，写此命令可触发发送START信号。
 *
 */
void i2c_start();

/**
 * @brief i2c_revack I2C总线接收ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将从SDA端口上读取的数据保存到MSACKI (I12CMSST.1)。
 * 
 */
void i2c_revack();

/**
 * @brief i2c_sndack I2C总线发送ACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndack();

/**
 * @brief i2c_sndnackI2C总线发送NACK命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生1个时钟，
 * 并将MSACKO (I2CMSST.0)中的数据发送到SDA端口。
 * 
 */
void i2c_sndnack();

/**
 * @brief I2C总线停止命令
 * 
 * 发送STOP信号。写此命令后，TPC总线控制器开始发送STOP信号。
 * 信号发送完成后，硬件自动将MSBUSY状态位清零。
 * 
 */
void i2c_stop();

/**
 * @brief i2c_readbyte I2C总线接受数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将从SDA端口上读取的数据依次左移到I2CRXD寄存器（先接收高位数据)。接
 * 
 * @return uint8_t 返回I2CRXD寄存器中的内容
 */
uint8_t i2c_readbyte();

/**
 * @brief i2c_sendbyte I2C总线发送数据命令
 * 
 * 写此命令后，I2C总线控制器会在SCL管脚上产生8个时钟，
 * 并将I2CTXD寄存器里面数据按位送到SDA管脚上（先发送高位数据)。
 *
 * @param byte 要发送的数据
 */
void i2c_sendbyte( uint8_t byte );

void i2c_test(void);

#endif