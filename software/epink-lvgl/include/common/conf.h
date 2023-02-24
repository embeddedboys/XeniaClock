/**
 * @file conf.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-24
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

#pragma once

#ifndef __COMMON_CONF_H
#define __COMMON_CONF_H

#include <generated/autoconf.h>

#ifdef CONFIG_I2C0_DEFAULT_SCL_PIN
    #define DEFAULT_I2C_SCL_PIN     CONFIG_I2C0_DEFAULT_SCL_PIN
#else
    #define DEFAULT_I2C_SCL_PIN     21
#endif

#ifdef CONFIG_I2C0_DEFAULT_SDA_PIN
    #define DEFAULT_I2C_SDA_PIN     CONFIG_I2C0_DEFAULT_SDA_PIN
#else
    #define DEFAULT_I2C_SDA_PIN     20
#endif

#endif