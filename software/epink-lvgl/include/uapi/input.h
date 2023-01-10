/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 1999-2002 Vojtech Pavlik
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#ifndef _UAPI_INPUT_H
#define _UAPI_INPUT_H

#include "common/tools.h"
#include "input-event-codes.h"

/*
 * The event structure itself
 */

struct input_event {
	// struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};

/*
 * Protocol version.
 */

#define EV_VERSION		0x010001

/*
 * IOCTLs (0x00 - 0x7f)
 */

struct input_id {
	__u16 bustype;
	__u16 vendor;
	__u16 product;
	__u16 version;
};

/**
 * struct input_absinfo - used by EVIOCGABS/EVIOCSABS ioctls
 * @value: latest reported value for the axis.
 * @minimum: specifies minimum value for the axis.
 * @maximum: specifies maximum value for the axis.
 * @fuzz: specifies fuzz value that is used to filter noise from
 *	the event stream.
 * @flat: values that are within this value will be discarded by
 *	joydev interface and reported as 0 instead.
 * @resolution: specifies resolution for the values reported for
 *	the axis.
 *
 * Note that input core does not clamp reported values to the
 * [minimum, maximum] limits, such task is left to userspace.
 *
 * The default resolution for main axes (ABS_X, ABS_Y, ABS_Z)
 * is reported in units per millimeter (units/mm), resolution
 * for rotational axes (ABS_RX, ABS_RY, ABS_RZ) is reported
 * in units per radian.
 * When INPUT_PROP_ACCELEROMETER is set the resolution changes.
 * The main axes (ABS_X, ABS_Y, ABS_Z) are then reported in
 * in units per g (units/g) and in units per degree per second
 * (units/deg/s) for rotational axes (ABS_RX, ABS_RY, ABS_RZ).
 */
struct input_absinfo {
	__s32 value;
	__s32 minimum;
	__s32 maximum;
	__s32 fuzz;
	__s32 flat;
	__s32 resolution;
};

/**
 * struct input_keymap_entry - used by EVIOCGKEYCODE/EVIOCSKEYCODE ioctls
 * @scancode: scancode represented in machine-endian form.
 * @len: length of the scancode that resides in @scancode buffer.
 * @index: index in the keymap, may be used instead of scancode
 * @flags: allows to specify how kernel should handle the request. For
 *	example, setting INPUT_KEYMAP_BY_INDEX flag indicates that kernel
 *	should perform lookup in keymap by @index instead of @scancode
 * @keycode: key code assigned to this scancode
 *
 * The structure is used to retrieve and modify keymap data. Users have
 * option of performing lookup either by @scancode itself or by @index
 * in keymap entry. EVIOCGKEYCODE will also return scancode or index
 * (depending on which element was used to perform lookup).
 */
struct input_keymap_entry {
#define INPUT_KEYMAP_BY_INDEX	(1 << 0)
	__u8  flags;
	__u8  len;
	__u16 index;
	__u32 keycode;
	__u8  scancode[32];
};

struct input_mask {
	__u32 type;
	__u32 codes_size;
	__u64 codes_ptr;
};

#endif /* _UAPI_INPUT_H */
