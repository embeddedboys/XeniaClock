/**
 * @file rpi-spi.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-24
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

#include "mtd/spi-nor.h"

#include <spi/native_spi.h>

static int rpi_spi_read_reg(struct spi_nor *nor, u8 opcode, u8 *buf,
                size_t len)
{
    int     ret;

    return 0;
}

static int rpi_spi_write_reg(struct spi_nor *nor, u8 opcode, const u8 *buf,
                size_t len)
{
    int ret;

    return 0;
}

static ssize_t rpi_spi_read(struct spi_nor *nor, loff_t from, size_t len,
			      u_char *read_buf)
{

}

static ssize_t rpi_spi_write(struct spi_nor *nor, loff_t to, size_t len,
			       const u_char *write_buf)
{

}

static int rpi_spi_erase(struct spi_nor *nor, loff_t offs)
{

}

static const struct spi_nor_controller_ops rpi_spi_controller_ops = {
	.read_reg = rpi_spi_read_reg,
	.write_reg = rpi_spi_write_reg,
	.read = rpi_spi_read,
	.write = rpi_spi_write,
	.erase = rpi_spi_erase,
};