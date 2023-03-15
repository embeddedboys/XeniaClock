/**
 * @file font.c
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

#include <string.h>

#include "font.h"

static LIST_HEAD(g_font_head);

struct font *fonts[] = {
    &font_8x16,
    &font_mini_4x6,
    NULL,
};

struct font *find_font_by_name(const char *name)
{
    for (int i = 0; fonts[i] != NULL; i++) {
    
        if (0 == strcmp(name, fonts[i]->name)) {
            pr_debug("font `%s` matched!\n", fonts[i]->name);
            return fonts[i];
        }
    }
    
    return NULL;
}

struct font *find_font_by_id(const int id)
{
    for (int i = 0; fonts[i] != NULL; i++) {
    
        if (fonts[i]->id == id) {
            pr_debug("font `%s` matched!\n", fonts[i]->name);
            return fonts[i];
        }
    }
    
    return NULL;
}

int register_font(struct font *font)
{   
    if (!font) {
        return -1;
    }
    
    if (!font->name) {
        pr_debug("the name of font must be set!\n");
        return -1;
    }
    
    if (find_font_by_id(font->id) || find_font_by_name(font->name)) {
        pr_debug("Conflict ID or name!\n");
        return -1;
    }

    if (font->width <= 0 || font->height <= 0) {
        pr_debug("Invaild font width or height!\n");
        return -1;
    }

    if (!font->data) {
        pr_debug("No font data\n");
        return -1;
    }

    if (font->len <= 0) {
        pr_debug("Warning, no font data length is not provided\n");
        return -1;
    }

    /* the real register operation */
    list_add_tail(&font->head, &g_font_head);

    return 0;
}

// late_initcall(font_init);

// static int font_init(void)
// {
//     INIT_LIST_HEAD(&g_font_head);
// }