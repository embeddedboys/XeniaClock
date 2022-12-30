/**
 * @file display_manager.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-29
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

#ifndef __DISPLAY_MANAGER_H
#define __DISPLAY_MANAGER_H

#include <stdint.h>
#include "common/list.h"

#define DISPLAY_PANEL_EP_LUAT    1
#define DISPLAY_PANEL_SSD1681    1
#define DISPLAY_PANEL_ST7789V    1

#define DISPLAY_MAIN_PANEL_EP_LUAT   0x00
#define DISPLAY_MAIN_PANEL_SSD1681   0x01
#define DISPLAY_MAIN_PANEL_ST7789V   0x02

#ifndef DEFAULT_DISPLAY_MAIN_PANEL
    #define DEFAULT_DISPLAY_MAIN_PANEL DISPLAY_MAIN_PANEL_EP_LUAT
#endif

struct display_config {
    uint32_t width;
    uint32_t height;
    uint32_t bpp;

    uint32_t update_mode;
};

struct display_ops {

    int (*module_init)(uint8_t mode);

    void (*module_flush)();

    void (*module_clear)(uint8_t color);

    void (*module_blank)();

    void (*module_set_update_mode)(uint8_t mode);

    void (*module_put_pixel)(uint16_t x, uint16_t y, uint16_t color);

};

struct display_module {
    uint32_t id;
    char *name;
    uint8_t *fb;
    struct display_config cfg;
    struct display_ops ops;

    struct display_module *p_next;
    struct list_head head;
} default_module;

extern int register_module( struct display_module *module );
struct display_module *request_disp_module(char *name);
void disp_modules_init( void );
void default_display_module_init(void);

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

#define DISP_MODULE_DRIVER(module) \
    static void __attribute__((constructor)) module##_register(void) \
    { \
        register_module(&module##_module); \
    }

#endif  /* __DISPLAY_MANAGER_H */
