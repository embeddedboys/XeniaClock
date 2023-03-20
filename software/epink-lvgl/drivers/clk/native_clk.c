/**
 * @file native_clk.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief clk subsystem of xenia clock
 * @version 0.1
 * @date 2022-12-26
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

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

#include <linux/init.h>
#include "common/tools.h"
#include "common/list.h"
#include "clk/native_clk.h"

void measure_freqs(void) 
{
    uint32_t f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint32_t f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint32_t f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint32_t f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    uint32_t f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    uint32_t f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    uint32_t f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    uint32_t f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);

    pr_debug("pll_sys = %dkHz\n", f_pll_sys);
    pr_debug("pll_usb = %dkHz\n", f_pll_usb);
    pr_debug("rosc = %dkHz\n", f_rosc);
    pr_debug("clk_sys = %dkHz\n", f_clk_sys);
    pr_debug("clk_peri = %dkHz\n", f_clk_peri);
    pr_debug("clk_usb = %dkHz\n", f_clk_usb);
    pr_debug("clk_adc = %dkHz\n", f_clk_adc);
    pr_debug("clk_rtc = %dkHz\n", f_clk_rtc);

    // Can't measure clk_ref / xosc as it is the ref
}

void set_sys_clk(uint16_t mhz)
{
    set_sys_clock_khz(mhz*KHZ, false);
    stdio_init_all();   /* reinit uart when clk is changed */
}

static int __init native_clk_init(void)
{
    measure_freqs();
    pr_debug("%s, initialzing clk ...", __func__);
}
core_initcall(native_clk_init);