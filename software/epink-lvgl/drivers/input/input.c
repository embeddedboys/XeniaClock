/**
 * @file input.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief The Input event manager, based on kernel input subsystem
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
#include <stdlib.h>

#include "hardware/platform_defs.h"
#include "input/input.h"
#include "common/list.h"
#include "src/misc/lv_area.h"
#include "uapi/input.h"

static LIST_HEAD(input_dev_list);
static LIST_HEAD(input_handler_list);

static const struct input_value input_value_sync = { EV_SYN, SYN_REPORT, 1 };

#define INPUT_IGNORE_EVENT	0
#define INPUT_PASS_TO_HANDLERS	1
#define INPUT_PASS_TO_DEVICE	2
#define INPUT_SLOT		4
#define INPUT_FLUSH		8
#define INPUT_PASS_TO_ALL	(INPUT_PASS_TO_HANDLERS | INPUT_PASS_TO_DEVICE)

static int input_get_disposition(struct input_dev *dev,
                unsigned int type, unsigned int code, int *pval)
{
    int disposition = INPUT_IGNORE_EVENT;
}

static void input_handle_event(struct input_dev *dev,
                    unsigned int type, unsigned int code, int value)
{
    if (!dev->vals)
        return;
    
}

void input_event(struct input_dev *dev,
        unsigned int type, unsigned int code, int value)
{
    input_handle_event(dev, type, code, value);
}

struct input_dev *input_alloc_device(void)
{
    struct input_dev *dev;
    
    dev = calloc(1, sizeof(*dev));
    
    /* initialize input dev */
    if (dev) {
        INIT_LIST_HEAD(&dev->h_list);
        INIT_LIST_HEAD(&dev->node);
    }
    
    return dev;
}

static void input_match_device(struct input_handler *handler, struct input_dev *dev)
{
    /* we do simple name match */
    
}

static int input_attach_handler(struct input_dev *dev, struct input_handler *handler)
{

}

void input_free_device(struct input_dev *dev)
{
    if (dev) {
        free(dev);
    }
}

int input_register_device(struct input_dev *dev)
{
    __set_bit(EV_SYN, dev->evbit);
    
    dev->max_vals = INPUT_DEFAULT_MAX_VALS;
    dev->vals = calloc(dev->max_vals, sizeof(*dev->vals));
    if (!dev->vals) {
        return -1;
    }

    list_add_tail(&dev->node, &input_dev_list);

    return 0;
}

void input_unregister_device(struct input_dev *dev)
{

}

int input_register_handler(struct input_handler *handler)
{

}

void input_unregister_handler(struct input_handler *handler)
{

}

int input_register_handle(struct input_handle *handle)
{

}

void input_unregister_handle(struct input_handle *handle)
{

}

