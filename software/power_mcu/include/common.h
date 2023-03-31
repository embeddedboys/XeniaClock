/**
 * @file common.h
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

#ifndef __POWER_MCU_COMMON_H
#define __POWER_MCU_COMMON_H

#define FOSC    11059200UL

/* for sdcc compiler */
#define sfr __sfr
#define sbit __sbit

/* `fn` -> function name, `v` -> the vector */
#define interrupt_declear(fn, v) void fn(void) __interrupt(v)

typedef unsigned char uint8_t;
typedef unsigned char uchar;
typedef unsigned char u8;

typedef unsigned short uint16_t;
typedef unsigned short ushort;
typedef unsigned short u16;

typedef unsigned int uint32_t;
typedef unsigned int uint;
typedef unsigned int u32;

typedef unsigned long long uint64_t;
// typedef unsigned long long ull;
typedef unsigned long long u64;

#endif