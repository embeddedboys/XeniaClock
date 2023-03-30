/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Hartman <gregkh@suse.de>
 * Copyright (c) 2008-2012 Novell Inc.
 * Copyright (c) 2012-2019 Greg Kroah-Hartman <gregkh@linuxfoundation.org>
 * Copyright (c) 2012-2019 Linux Foundation
 *
 * Core driver model functions and structures that should not be
 * shared outside of the drivers/base/ directory.
 *
 */

#include <linux/kobject.h>
#include <common/list.h>

struct driver_private {
    struct kobject      kobj;
    struct list         list_devices;
    struct list_node    node_bus;

    struct device_driver *driver;
};
#define to_driver(obj) container_of(obj, struct driver_private, kobj)