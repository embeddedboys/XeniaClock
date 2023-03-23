/*
 * Copyright (c) 2023 IotaHydrae (writeforever@foxmail.com)
 *  
 * SPDX-License-Identifier: MIT
 */

.syntax unified
.cpu cortex-m0plus
.thumb

.global main

.weak main
.type main,%function
.thumb_func
main:
    ldr r1, =start_kernel
    blx r1
    bx lr
