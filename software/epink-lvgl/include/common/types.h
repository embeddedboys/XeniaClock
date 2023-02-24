/**
 * @file types.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
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

#ifndef __TYPES_H
#define __TYPES_H

#include <stdbool.h>

#ifndef u8
    typedef unsigned char u8;
#endif

#ifndef u16
    typedef unsigned short u16;
#endif

#ifndef u32
    typedef unsigned int u32;
#endif

#ifndef u64
    typedef unsigned long u64;
#endif

typedef unsigned char   __u8;
typedef unsigned short  __u16;
typedef unsigned int    __u32;
typedef  unsigned long long __u64;

typedef signed char  __s8;
typedef signed short __s16;
typedef signed int   __s32;
typedef signed long long __s64;

/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

typedef int __kernel_ssize_t;
typedef long long   __kernel_loff_t;

typedef __kernel_ssize_t ssize_t;
typedef __kernel_loff_t loff_t;

// typedef _Bool			bool;

#endif  /* __TYPES_H */