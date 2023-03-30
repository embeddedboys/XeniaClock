/**
 * @file built-in.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-30
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

#include <linux/stringify.h>

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

#define __embed_file_name(prefix, __name, suffix) \
    __PASTE(__,             \
    __PASTE(prefix,         \
    __PASTE(__,             \
    __PASTE(__name,         \
    __PASTE(__,suffix)))))

#define __embed_file_name_str(prefix, __name, suffix) \
    __stringify(            \
    __PASTE(__,             \
    __PASTE(prefix,         \
    __PASTE(__,             \
    __PASTE(__name,         \
    __PASTE(__,suffix))))))

#define EMBED_FILE_WITH_SEC(__path, __name, __sec) \
    extern const char __embed_file_name(emb_file, __name, data)[];   \
    extern const int __embed_file_name(emb_file, __name, len)[];   \
    asm(".section    \"" __sec "\", \"a\"            \n"  \
    __embed_file_name_str(emb_file, __name, data) ": \n" \
    ".incbin   \"" __path "\" \n"  \
    __embed_file_name_str(emb_file, __name, len) ": \n"  \
    ".long " __embed_file_name_str(emb_file, __name, data) " - . \n"   \
    ".previous\n");

// #define EMBED_FILE_WITH_SEC(__path, __name, __sec) \
//     extern const char __embed_file_name(emb_file, __name, data)[];   \
//     extern const char __embed_file_name(emb_file, __name, end)[];   \
//     extern const char __embed_file_name(emb_file, __name, len)[];   \
//     asm(".section    \"" __sec "\", \"a\"            \n"  \
//     __embed_file_name_str(emb_file, __name, data) ": \n" \
//     ".incbin   \"" __path "\" \n"  \
//     __embed_file_name_str(emb_file, __name, end) ": \n"  \
//     ".equ " __embed_file_name_str(emb_file, __name, len) ", " \
//     "(" __embed_file_name_str(emb_file, __name, end) " - "   \
//     __embed_file_name_str(emb_file, __name, data) ")\n" \
//     ".previous\n");

#define EMBED_FILE(__path, __name) \
    EMBED_FILE_WITH_SEC(__path, __name, __stringify(.rodata))
