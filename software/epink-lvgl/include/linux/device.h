// SPDX-License-Identifier: GPL-2.0
/*
 * device.h - generic, centralized driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Hartman <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 *
 * See Documentation/driver-api/driver-model/ for more information.
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <common/types.h>
#include <linux/device/driver.h>

struct device;
struct device_driver;

struct device {
    struct device *parent;

    const char      *init_name;

    struct bus_type         *type;
    struct device_driver    *driver;

    void        *platform_data;
    void        *driver_data;
    u32         id;
};

#endif