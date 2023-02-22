/**
 * @file implementation.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
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

#ifndef __LFS_HAL_IMPLEMENTATION_H
#define __LFS_HAL_IMPLEMENTATION_H

/* lfs supported devices */
#define LFS_PORT_DEVICE_RAM     0x00
#define LFS_PORT_DEVICE_FLASH   0x01
#define LFS_PORT_DEVICE_SDCARD  0x02

#define LFS_NO_ASSERT
#define LFS_NO_DEBUG
#define LFS_NO_WARN
#define LFS_NO_ERROR

/* default port device choosing */
#ifndef DEFAULT_LFS_PORT_DEVICE
    #define DEFAULT_LFS_PORT_DEVICE LFS_PORT_DEVICE_RAM
#endif

/* Different device need different marco */
#if DEFAULT_LFS_PORT_DEVICE == LFS_PORT_DEVICE_RAM
#elif DEFAULT_LFS_PORT_DEVICE == LFS_PORT_DEVICE_FLASH
#elif DEFAULT_LFS_PORT_DEVICE == LFS_PORT_DEVICE_SDCARD
#endif

#endif  /* __LFS_HAL_IMPLEMENTATION_H */