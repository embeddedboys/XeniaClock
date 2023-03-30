/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __LINUX_GPIO_DRIVER_H
#define __LINUX_GPIO_DRIVER_H

#include <common/types.h>

struct gpio_chip {
    const char      *label;

    int         (*request)(struct gpio_chip *gc,
                        unsigned int offset);
    void           (*free)(struct gpio_chip *gc,
                        unsigned int offset);
    int         (*get_direction)(struct gpio_chip *gc,
                        unsigned int offset);
    int         (*direction_input)(struct gpio_chip *gc,
                        unsigned int offset);
    int         (*direction_output)(struct gpio_chip *gc,
                        unsigned int offset);
    int         (*get)(struct gpio_chip *gc,
                        unsigned int offset);
    int         (*get_multiple)(struct gpio_chip *gc,
                        unsigned long *mask,
                        unsigned long *bits);
    void         (*set)(struct gpio_chip *gc,
                        unsigned int offset);
    void         (*set_multiple)(struct gpio_chip *gc,
                        unsigned long *mask,
                        unsigned long *bits);
    int         (*set_config)(struct gpio_chip *gc,
                        unsigned int offset,
                        unsigned long config);
    int         (*to_irq)(struct gpio_chip *gc,
                        unsigned int offset);

    int         base;
    u16         ngpio;
    u16         offset;
    const char    *const *names;
    bool        can_sleep;

    unsigned long   *vaild_mask;
};

#endif