/**
 * @file winbond.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-22
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

// #include "mtd/spi-nor.h"

#include "core.h"

static const struct flash_info winbond_parts[] = {
    /* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
    {
        "w25x05", INFO(0xef3010, 0, 64 * 1024,  1)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25x10", INFO(0xef3011, 0, 64 * 1024,  2)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25x20", INFO(0xef3012, 0, 64 * 1024,  4)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25x40", INFO(0xef3013, 0, 64 * 1024,  8)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25x80", INFO(0xef3014, 0, 64 * 1024,  16)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25x16", INFO(0xef3015, 0, 64 * 1024,  32)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q16dw", INFO(0xef6015, 0, 64 * 1024,  32)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25x32", INFO(0xef3016, 0, 64 * 1024,  64)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q16jv-im/jm", INFO(0xef7015, 0, 64 * 1024,  32)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q20cl", INFO(0xef4012, 0, 64 * 1024,  4)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q20bw", INFO(0xef5012, 0, 64 * 1024,  4)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q20ew", INFO(0xef6012, 0, 64 * 1024,  4)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q32", INFO(0xef4016, 0, 64 * 1024,  64)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q32dw", INFO(0xef6016, 0, 64 * 1024,  64)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)
        // OTP_INFO(256, 3, 0x1000, 0x1000)
    },
    {
        "w25q32jv", INFO(0xef7016, 0, 64 * 1024,  64)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q32jwm", INFO(0xef8016, 0, 64 * 1024,  64)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)
        // OTP_INFO(256, 3, 0x1000, 0x1000)
    },
    {
        "w25q64jwm", INFO(0xef8017, 0, 64 * 1024, 128)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q128jwm", INFO(0xef8018, 0, 64 * 1024, 256)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q256jwm", INFO(0xef8019, 0, 64 * 1024, 512)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25x64", INFO(0xef3017, 0, 64 * 1024, 128)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q64", INFO(0xef4017, 0, 64 * 1024, 128)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q64dw", INFO(0xef6017, 0, 64 * 1024, 128)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q64jvm", INFO(0xef7017, 0, 64 * 1024, 128)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q128fw", INFO(0xef6018, 0, 64 * 1024, 256)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q128jv", INFO(0xef7018, 0, 64 * 1024, 256)
        FLAGS(SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25q80", INFO(0xef5014, 0, 64 * 1024,  16)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q80bl", INFO(0xef4014, 0, 64 * 1024,  16)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q128", INFO(0xef4018, 0, 64 * 1024, 256)
        NO_SFDP_FLAGS(SECT_4K)
    },
    {
        "w25q256", INFO(0xef4019, 0, 64 * 1024, 512)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)
        // .fixups = &w25q256_fixups
    },
    {
        "w25q256jvm", INFO(0xef7019, 0, 64 * 1024, 512)
        PARSE_SFDP
    },
    {
        "w25q256jw", INFO(0xef6019, 0, 64 * 1024, 512)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
    {
        "w25m512jv", INFO(0xef7119, 0, 64 * 1024, 1024)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_QUAD_READ |
                      SPI_NOR_DUAL_READ)
    },
    {
        "w25q512jvq", INFO(0xef4020, 0, 64 * 1024, 1024)
        NO_SFDP_FLAGS(SECT_4K | SPI_NOR_DUAL_READ |
                      SPI_NOR_QUAD_READ)
    },
};

const struct spi_nor_manufacturer spi_nor_winbond = {
    .name = "winbond",
    .parts = winbond_parts,
    .nparts = ARRAY_SIZE(winbond_parts),
};
