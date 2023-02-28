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

#include <common/init.h>
#include <lib/printk.h>

#include "mtd/spi-nor.h"


#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include <spi/native_spi.h>

#define FLASH_SPI_IFCE  spi1

#define FLASH_SCK_PIN   10
#define FLASH_TX_PIN    11
#define FLASH_RX_PIN    8
#define FLASH_CS_PIN    9

static void flash_cs_select(uint16_t pin)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(pin, 0);
    asm volatile("nop \n nop \n nop");
}

static void flash_cs_deselect(uint16_t pin)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(pin, 1);
    asm volatile("nop \n nop \n nop");
}

static void flash_write8(uint8_t val, uint8_t cs_pin)
{
    uint8_t buf[1] = {val};

    flash_cs_select(cs_pin);
    spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
    flash_cs_deselect(cs_pin);
}

static void flash_write_reg(u8 reg, u8 *vals, size_t len, u8 cs_pin)
{
    u8 buf[1] = {reg};

    flash_cs_select(cs_pin);
    spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
    spi_write_blocking(FLASH_SPI_IFCE, vals, len);
    flash_cs_deselect(cs_pin);
}

static u8 flash_read_reg(uint8_t reg, uint8_t cs_pin)
{
    uint8_t buf[1] = {reg};
    u8 read[1] = {0};

    flash_cs_select(cs_pin);
    spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
    spi_read_blocking(FLASH_SPI_IFCE, 0x0, read, 1);
    flash_cs_deselect(cs_pin);

    return read[0];
}

static void flash_transfer(uint8_t *src, uint8_t *dst, int size, uint8_t cs_pin)
{
    flash_cs_select(cs_pin);
    spi_write_read_blocking(FLASH_SPI_IFCE, src, dst, size);
    flash_cs_deselect(cs_pin);
}

size_t winbond_flash_sector_erase(u32 to)
{
    int rc;
    u8 to_buf[4] = { 0x20, to >> 16, to >> 8, to};

    flash_write8(0x06, FLASH_CS_PIN);

    flash_cs_select(FLASH_CS_PIN);

    spi_write_blocking(FLASH_SPI_IFCE, to_buf, ARRAY_SIZE(to_buf));

    flash_cs_deselect(FLASH_CS_PIN);

    /* according to the manual, a sector erase will cost 120ms,
     * max for 200ms, so give a 150ms delay for good */
    return rc;
}

size_t winbond_flash_write_data(u32 to, size_t len, const u8 *buf)
{
    // int rc;
    // u8 to_buf[4] = { WINBOND_FLASH_CMD_PAGE_PROGRAM, to >> 16, to >> 8, to};

    // flash_write8(0x06, FLASH_CS_PIN);

    // flash_cs_select(FLASH_CS_PIN);

    // spi_write_blocking(FLASH_SPI_IFCE, to_buf, ARRAY_SIZE(to_buf));
    // spi_write_blocking(FLASH_SPI_IFCE, buf, len);

    // flash_cs_deselect(FLASH_CS_PIN);

    // return rc;
}

size_t winbond_flash_read_data(u32 from, size_t len, u8 *buf)
{
    // int rc;
    // u8 from_buf[4] = { WINBOND_FLASH_CMD_READ_DATA, from >> 16, from >> 8, from};
    // u8 read_buf[8] = {0};

    // flash_cs_select(FLASH_CS_PIN);

    // // spi_write_blocking(FLASH_SPI_IFCE, from_buf, ARRAY_SIZE(from_buf));
    // // spi_read_blocking(FLASH_SPI_IFCE, 0x0, buf, len);
    
    // spi_write_read_blocking(FLASH_SPI_IFCE, from_buf, read_buf, ARRAY_SIZE(from_buf) + len);
    // flash_cs_deselect(FLASH_CS_PIN);

    // u8 *p = read_buf + ARRAY_SIZE(from_buf);
    // memcpy(buf, p, len);

    // return 0;
}

static int rpi_spi_read_reg(struct spi_nor *nor, u8 opcode, u8 *buf,
                size_t len)
{
    int ret;

	pr_dbg("opcode : 0x%02x\n");

    uint8_t w_buf[1] = {opcode};

    flash_cs_select(FLASH_CS_PIN);
    spi_write_blocking(FLASH_SPI_IFCE, w_buf, 1);
    spi_read_blocking(FLASH_SPI_IFCE, 0x0, buf, len);
    flash_cs_deselect(FLASH_CS_PIN);

    return 0;
}

static int rpi_spi_write_reg(struct spi_nor *nor, u8 opcode, const u8 *buf,
                size_t len)
{
    int ret;

	pr_dbg("opcode : 0x%02x\n");

    uint8_t w_buf[1] = {opcode};

    flash_cs_select(FLASH_CS_PIN);
    spi_write_blocking(FLASH_SPI_IFCE, w_buf, 1);

	if (buf && len > 0)
    	spi_write_blocking(FLASH_SPI_IFCE, buf, len);

    flash_cs_deselect(FLASH_CS_PIN);

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

const struct spi_nor_controller_ops rpi_spi_controller_ops = {
	.read_reg  = rpi_spi_read_reg,
	.write_reg = rpi_spi_write_reg,
	.read      = rpi_spi_read,
	.write     = rpi_spi_write,
	.erase     = rpi_spi_erase,
};

static SUBSYS_INITCALL(rpi_spi_init)
{
    /* HAL init */
    spi_init(FLASH_SPI_IFCE, 10000000);
    gpio_set_function(FLASH_SCK_PIN, GPIO_FUNC_SPI);
    // gpio_set_function(FLASH_CS_PIN, GPIO_FUNC_SPI);
    gpio_set_function(FLASH_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(FLASH_RX_PIN, GPIO_FUNC_SPI);
    bi_decl(bi_3pins_with_func(FLASH_SCK_PIN, FLASH_TX_PIN, FLASH_RX_PIN, GPIO_FUNC_SPI));

    gpio_init(FLASH_CS_PIN);
    gpio_set_dir(FLASH_CS_PIN, GPIO_OUT);
    gpio_put(FLASH_CS_PIN, 1);
    bi_decl(bi_1pin_with_func(FLASH_CS_PIN, GPIO_FUNC_SPI));

    // /* disable memory protection */
    // /* save status regs */
    // u8 status_reg1, status_reg2;
    // status_reg1 = flash_read_reg(0x05, FLASH_CS_PIN);
    // status_reg2 = flash_read_reg(0x35, FLASH_CS_PIN);
    // printf("stat1 : 0x%02x, stat2 : 0x%02x\n", status_reg1, status_reg2);

    // /* write enable */
    // flash_write8(0x06, FLASH_CS_PIN);
    // vTaskDelay(5);

    // u8 buf[2] = {status_reg1 |= (1 << 1), status_reg2 &= ~(0x03)};
    // flash_write_reg(0x01, buf, ARRAY_SIZE(buf), FLASH_CS_PIN);
    // vTaskDelay(20);

    // status_reg1 = flash_read_reg(0x05, FLASH_CS_PIN);
    // status_reg2 = flash_read_reg(0x35, FLASH_CS_PIN);
    // printf("stat1 : 0x%02x, stat2 : 0x%02x\n", status_reg1, status_reg2);
}

// static SUBSYS_INITCALL(rpi_spi_controller_init)
// {
// 	extern void register_nor_controller_ops(const struct spi_nor_controller_ops *ops);

// 	pr_err("registering rpi spi controller ...\n");
// 	register_nor_controller_ops(&rpi_spi_controller_ops);
// }

// void winbond_flash_test()
// {
//     /* match device */
//     // winbond_flash_read_id();
//     winbond_flash_sector_erase(0);
//     vTaskDelay(150);

//     u8 test_data[1] = {0x59};
//     u8 read_buf[1];
//     /* write a byte to address */
//     winbond_flash_write_data(0, 1, test_data);
    
//     vTaskDelay(20);

//     // /* read a byte from address */
//     winbond_flash_read_data(0, 1, read_buf);
//     printf("read : 0x%02x\n", read_buf[0]);
// }