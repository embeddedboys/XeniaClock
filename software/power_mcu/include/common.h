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

#include "stc8g.h"

#define NULL ((void *)0)
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// #define typeof_member(T, m)	typeof(((T*)0)->m)
// #ifndef typeof
// #warning "typeof is not defined!"
// #define typeof(x) __typeof__(x)
// #endif

#ifndef offsetof
#define offsetof(type,member) ((unsigned long)((type *)0) - (unsigned long)&(((type *)0)->member))
#endif
/*
#define container_of(ptr, type, member)   ({                \
        const typeof(((type *)0)->member) * __mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member));})
*/

#define FOSC    11059200UL
#define nop() __asm NOP __endasm

#define xfr_on()  {P_SW2 |= 0x80;}
#define xfr_off()  {P_SW2 &= ~0x80;}

/* for sdcc compiler */
// #define sfr __sfr
// #define sbit __sbit

// #define writel(v,r) { xfr_on(); r=v; xfr_off(); }
// #define readl(r) { xfr_on(); v; xfr_off(); }

/* `fn` -> function name, `v` -> the vector */
#define interrupt_declear(fn, v) void fn(void) __interrupt(v)

// inline void write_xfr(u16 xfr, u8 val)
// {
//     volatile u8 *p = (u8 *)xfr;
//     xfr_on();
//     *p = val;
//     xfr_off();
// }

// inline u8 read_xfr(volatile u32 xfr)
// {
//     xfr_on();
//     u8 tmp = *xfr;
//     xfr_off();

//     return tmp;
// }


#endif