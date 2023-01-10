/**
 * @file input.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief The Input event manager
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