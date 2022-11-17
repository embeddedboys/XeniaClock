/**
 * @file epd.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
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

#ifndef __EPD_H
#define __EPD_H

#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

/* Pins Define of rpi-pico
 *
 * The SPI interface using default spi0
 *
 * RES  <->  GP14
 * DC   <->  GP15
 * BUSY <->  GP20
 */
#define EPINK_RES_PIN   15
#define EPINK_DC_PIN    14
#define EPINK_CS_PIN    13
#define EPINK_BUSY_PIN  12

/* ========== epink panel info ========== */
#define EPINK_WIDTH         200
#define EPINK_HEIGHT        200
#define EPINK_PAGE_SIZE     8
#define EPINK_LINE_WIDTH_IN_PAGE (EPINK_WIDTH/EPINK_PAGE_SIZE)
#define EPINK_BPP 1
#define EPINK_COLOR_WHITE (0xFF)
#define EPINK_COLOR_BLACK (0x00)

#define EPINK_UPDATE_MODE_FULL 1
#define EPINK_UPDATE_MODE_PART 2

#define EPINK_DISP_BUFFER_SIZE (EPINK_WIDTH*EPINK_HEIGHT/8)
#define EPINK_DISP_BUFFER_OFFSET(p,x)(p*EPINK_WIDTH + x)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

// #define EPINK_DEBUG_MODE
#define EPINK_COORD_CHECK
#ifdef EPINK_DEBUG_MODE
    #define EPINK_DEBUG(...) printf(__VA_ARGS__)
#else
    #define EPINK_DEBUG
#endif

void epink_init( uint8_t mode );
void epink_clear( uint8_t color );
void epink_blank();

#endif // !__EPD_H