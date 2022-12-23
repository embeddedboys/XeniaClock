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

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "common/tools.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define TEST_DOC "This document describes how to write an ALSA \
(Advanced Linux Sound Architecture) driver. The document focuses \
mainly on PCI soundcards. In the case of other device types, the \
API might be different, too. However, at least the ALSA kernel \
API is consistent, and therefore it would be still a bit help \
for writing them."

#define TEST_DOC2 "This variable provides a means of enabling or \
disabling features of a recipe on a per-recipe basis. PACKAGECONFIG \
blocks are defined in recipes when you specify features and then \
arguments that define feature behaviors."

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
#define EPINK_COLOR_WHITE (0xff)
#define EPINK_COLOR_BLACK (0x00)
#define EPINK_DISP_BUFFER_SIZE (EPINK_WIDTH*EPINK_HEIGHT/8)
#define EPINK_DISP_BUFFER_OFFSET(p,x)(p*EPINK_WIDTH + x)

/* ========== epink panel settings ========== */
#define EPINK_UPDATE_MODE_FULL 1
#define EPINK_UPDATE_MODE_PART 2

#ifndef DEFAULT_EPINK_UPDATE_MODE
    #define DEFAULT_EPINK_UPDATE_MODE EPINK_UPDATE_MODE_PART
#endif

// #define EPINK_DEBUG_MODE
#define EPINK_COORD_CHECK
#ifdef EPINK_DEBUG_MODE
    #define EPINK_DEBUG(...) printf(__VA_ARGS__)
#else
    #define EPINK_DEBUG
#endif

#define EPINK_ERROR(...) printf("[ERROR]" __VA_ARGS__)

/* Base  */
void cs_select();
void cs_deselect();
void epink_dc_set();
void epink_dc_clr();
void epink_res_set();
void epink_res_clr();
void epink_reset();

void epink_write_byte(uint8_t val);
void epink_write_command(uint8_t command);
void epink_write_data(uint8_t data);
void epink_wait_busy();

void epink_init(uint8_t mode);
// void epink_clear(uint8_t color);
void epink_blank();
void epink_flush();
void epink_draw_pixel(uint8_t x, uint8_t y, uint8_t color);

struct display_config {
    uint32_t width;
    uint32_t height;
    uint32_t bpp;

    uint32_t update_mode;
} default_cfg;

struct display_ops {
#define EPINK_USE_INIT              1
    int (*module_init)(uint8_t mode);

#define EPINK_USE_FLUSH             1
    void (*module_flush)();

#define EPINK_USE_CLEAR             1
    void (*module_clear)(uint8_t color);

#define EPINK_USE_BLANK             1
    void (*module_blank)();

#define EPINK_USE_SET_UPDATE_MODE   1
    void (*module_set_update_mode)(uint8_t mode);

#define EPINK_USE_PUT_PIXEL         1
    void (*module_put_pixel)(uint16_t x, uint16_t y, uint8_t color);
};

struct display_module {
    uint32_t id;
    char *name;
    uint8_t *fb;
    struct display_ops ops;

    struct display_module *p_next;
} default_module;

extern int register_module( struct display_module *module );
struct display_module *request_disp_module(char *name);
void disp_modules_init( void );
#define DISP_MODULE_REGISTER(module) \
    static struct display_module module##_module = { \
        .name = #module, \
        .ops = { \
                .module_init = module##_init, \
                .module_flush = module##_flush, \
                .module_clear = module##_clear, \
                .module_blank = module##_blank, \
                .module_set_update_mode = module##_set_update_mode, \
                .module_put_pixel = module##_put_pixel \
        }, \
    }; \
    static void __attribute__((constructor)) module##_register(void) \
    { \
        register_module(&module##_module); \
    }
void display_init(void);

extern uint8_t epink_disp_buffer[EPINK_DISP_BUFFER_SIZE];
extern unsigned char fontdata_mini_4x6[1536];
extern unsigned char fontdata_8x16[4096];

#endif // !__EPD_H