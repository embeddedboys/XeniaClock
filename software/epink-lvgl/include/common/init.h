/**
 * @file init.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief this file is based on kernel init.h
 * @version 0.1
 * @date 2023-01-11
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

#ifndef __INIT_H
#define __INIT_H

/*
 * Used for initialization calls..
 *
 * WARN:
 * These APIs can only be used when you know what you do,
 * otherwise may cause system crash!
 */
typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

#define __define_initcall(fn, id) static int __attribute__((constructor(id))) fn(void);
#define __define_exitcall(fn, id) static void __attribute__((destructor(id))) fn(void);

/* constructor priorities from 0 to 100 are reserved for the implementation */
#define pure_initcall(fn)		__define_initcall(fn, 101)

#define core_initcall(fn)		__define_initcall(fn, 102)
// #define core_initcall_sync(fn)		__define_initcall(fn, 1s)
#define postcore_initcall(fn)		__define_initcall(fn, 103)
// #define postcore_initcall_sync(fn)	__define_initcall(fn, 2s)
#define arch_initcall(fn)		__define_initcall(fn, 104)
// #define arch_initcall_sync(fn)		__define_initcall(fn, 3s)
#define subsys_initcall(fn)		__define_initcall(fn, 105)
// #define subsys_initcall_sync(fn)	__define_initcall(fn, 4s)
#define fs_initcall(fn)			__define_initcall(fn, 106)
// #define fs_initcall_sync(fn)		__define_initcall(fn, 5s)
#define rootfs_initcall(fn)		__define_initcall(fn, 107)
#define device_initcall(fn)		__define_initcall(fn, 108)
// #define device_initcall_sync(fn)	__define_initcall(fn, 6s)
#define late_initcall(fn)		__define_initcall(fn, 109)
// #define late_initcall_sync(fn)		__define_initcall(fn, 7s)

#define __initcall(fn)  device_initcall(fn);
#define __exitcall(fn)  __define_exitcall(fn, 107);


#define __DEFINE_INITCALL(fn,id) int __attribute__((constructor(id))) fn(void)

#define PURE_INITCALL(fn) __DEFINE_INITCALL(fn,101)

#define CORE_INITCALL(fn) __DEFINE_INITCALL(fn,102)

#define POSTCORE_INITCALL(fn) __DEFINE_INITCALL(fn,103)

#define ARCH_INITCALL(fn) __DEFINE_INITCALL(fn,104)

#define SUBSYS_INITCALL(fn) __DEFINE_INITCALL(fn,105)

#define FS_INITCALL(fn) __DEFINE_INITCALL(fn,106)

#define ROOTFS_INITCALL(fn) __DEFINE_INITCALL(fn,107)

#define DEVICE_INITCALL(fn) __DEFINE_INITCALL(fn,108)

#define LATE_INITCALL(fn) __DEFINE_INITCALL(fn,109)

#endif