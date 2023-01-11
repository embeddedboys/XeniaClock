/**
 * @file input.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-10
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

#ifndef __INPUT_H
#define __INPUT_H

#include <stdbool.h>

#include "uapi/input-event-codes.h"
#include "common/list.h"
#include "common/bitops.h"

#define INPUT_DEFAULT_MAX_VALS    5

/**
 * struct input_value - input value representation
 * @type: type of value (EV_KEY, EV_ABS, etc)
 * @code: the value code
 * @value: the value
 */
struct input_value {
    __u16 type;
    __u16 code;
    __s32 value;
};

struct input_dev {
    const char *name;
    
    unsigned long evbit[BITS_TO_LONGS(EV_CNT)];
    
    struct list_head h_list;
    struct list_head node;
    
    unsigned int num_vals;
    unsigned int max_vals;
    struct input_value *vals;
};

struct input_handle;

struct input_handler {
    void *private;

    void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
    void (*events)(struct input_handle *handle, struct input_value *vals, unsigned int count);
    bool (*match)(struct input_handler *handler, struct input_dev *dev);
    int (*connect)(struct input_handler *handler, struct input_dev *dev);
    void (*disconnect)(struct input_handle *handle);
    void (*start)(struct input_handle *handle);

    const char *name;

    struct list_head    h_list;
    struct list_head    node;
};

struct input_handle {

    void *private;
    
    int open;
    const char *name;
    
    struct input_dev *dev;
    struct input_handler *handler;
    
    struct list_head    d_node;
    struct list_head    n_node;
};

struct input_dev *input_alloc_device(void);

int input_register_device(struct input_dev *);
void input_unregister_device(struct input_dev *);


int input_register_handler(struct input_handler *);
void input_unregister_handler(struct input_handler *);

int input_register_handle(struct input_handle *);
void input_unregister_handle(struct input_handle *);

void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value);

static inline void input_report_key(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_KEY, code, !!value);
}

static inline void input_report_rel(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_REL, code, value);
}

static inline void input_report_abs(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_ABS, code, value);
}

static inline void input_report_switch(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_SW, code, !!value);
}

static inline void input_sync(struct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_REPORT, 0);
}

static inline void input_mt_sync(struct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_MT_REPORT, 0);
}

void input_set_capability(struct input_dev *dev, unsigned int type, unsigned int code);


#endif  /* __INPUT_H */