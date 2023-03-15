/**
 * @file font.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-14
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

#ifndef __VIDEO_FONT_H
#define __VIDEO_FONT_H

#include <stddef.h>

#include <common/init.h>
#include <common/tools.h>
#include <common/list.h>

struct font {
    int id;             /* Used to find this font */
    const char *name;   /* Used to find this font */
    
    int width;          /* Width of the font */
    int height;         /* Height of the font */
    
    const unsigned char *data;  /* Font dot matrix data */
    int len;                    /* The length of data */
    
    struct list_head head;
};

extern struct font font_8x16;
extern struct font font_mini_4x6;

extern struct font *fonts[];

struct font *find_font_by_id(const int id);
struct font *find_font_by_name(const char *name);

int register_font(struct font *font);

#define DYNAMIC_FONT_REGISTER(font) \
    static void __attribute__((constructor)) font##_register(void) \
    {   \
        register_font(&font); \
    }

#endif