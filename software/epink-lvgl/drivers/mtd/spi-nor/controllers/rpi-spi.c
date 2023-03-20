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

// #include <FreeRTOS.h>
// #include "task.h"

#include <linux/init.h>
#include <common/init.h>
#include <lib/printk.h>

#include "mtd/spi-nor.h"

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

#include <spi/native_spi.h>

#define FLASH_SPI_IFCE  spi1

#define FLASH_SCK_PIN   10
#define FLASH_TX_PIN    11
#define FLASH_RX_PIN    8
#define FLASH_CS_PIN    9

#define FLASH_PAGE_SIZE        256
#define FLASH_SECTOR_SIZE      4096

#define FLASH_CMD_PAGE_PROGRAM 0x02
#define FLASH_CMD_READ         0x03
#define FLASH_CMD_STATUS       0x05
#define FLASH_CMD_WRITE_EN     0x06
#define FLASH_CMD_SECTOR_ERASE 0x20

#define FLASH_STATUS_BUSY_MASK 0x01

// static void flash_cs_select(uint16_t pin)
// {
//     asm volatile("nop \n nop \n nop");
//     gpio_put(pin, 0);
//     asm volatile("nop \n nop \n nop");
// }

// static void flash_cs_deselect(uint16_t pin)
// {
//     asm volatile("nop \n nop \n nop");
//     gpio_put(pin, 1);
//     asm volatile("nop \n nop \n nop");
// }

// static void flash_write8(uint8_t val, uint8_t cs_pin)
// {
//     uint8_t buf[1] = {val};

//     cs_select(cs_pin);
//     spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
//     cs_deselect(cs_pin);
// }

// static void flash_write_reg(u8 reg, u8 *vals, size_t len, u8 cs_pin)
// {
//     u8 buf[1] = {reg};

//     cs_select(cs_pin);
//     spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
//     spi_write_blocking(FLASH_SPI_IFCE, vals, len);
//     cs_deselect(cs_pin);
// }

// static u8 flash_read_reg(uint8_t reg, uint8_t cs_pin)
// {
//     uint8_t buf[1] = {reg};
//     u8 read[1] = {0};

//     cs_select(cs_pin);
//     spi_write_blocking(FLASH_SPI_IFCE, buf, 1);
//     spi_read_blocking(FLASH_SPI_IFCE, 0x0, read, 1);
//     cs_deselect(cs_pin);

//     return read[0];
// }

void __not_in_flash_func(flash_write_enable)()
{
    cs_select(FLASH_CS_PIN);
    uint8_t cmd = FLASH_CMD_WRITE_EN;
    spi_write_blocking(FLASH_SPI_IFCE, &cmd, 1);
    cs_deselect(FLASH_CS_PIN);
}

void __not_in_flash_func(flash_wait_done)()
{
    uint8_t status;
    uint32_t timeout = 200; /* 200ms */
    do {
        cs_select(FLASH_CS_PIN);
        uint8_t buf[2] = {FLASH_CMD_STATUS, 0};
        spi_write_read_blocking(FLASH_SPI_IFCE, buf, buf, 2);
        cs_deselect(FLASH_CS_PIN);
        status = buf[1];
        if (timeout-- > 0)
            sleep_ms(1);
    } while (timeout && (status & FLASH_STATUS_BUSY_MASK));
}

// static void flash_transfer(uint8_t *src, uint8_t *dst, int size, uint8_t cs_pin)
// {
//     cs_select(cs_pin);
//     spi_write_read_blocking(FLASH_SPI_IFCE, src, dst, size);
//     cs_deselect(cs_pin);
// }

// size_t winbond_flash_sector_erase(u32 to)
// {
//     int rc;
//     u8 to_buf[4] = { 0x20, to >> 16, to >> 8, to};

//     flash_write8(0x06, FLASH_CS_PIN);
//     flash_cs_select(FLASH_CS_PIN);
//     spi_write_blocking(FLASH_SPI_IFCE, to_buf, ARRAY_SIZE(to_buf));
//     flash_cs_deselect(FLASH_CS_PIN);
//     /* according to the manual, a sector erase will cost 120ms,
//      * max for 200ms, so give a 150ms delay for good */
//     return rc;
// }

static int __not_in_flash_func(rpi_spi_read_reg)(struct spi_nor *nor, u8 opcode, u8 *buf,
                                                 size_t len)
{
    int ret;
    // pr_dbg("opcode : 0x%02x\n");
    uint8_t w_buf[1] = {opcode};

    cs_select(FLASH_CS_PIN);
    spi_write_blocking(FLASH_SPI_IFCE, w_buf, 1);
    spi_read_blocking(FLASH_SPI_IFCE, 0x0, buf, len);
    cs_deselect(FLASH_CS_PIN);

    return 0;
}

static int __not_in_flash_func(rpi_spi_write_reg)(struct spi_nor *nor, u8 opcode,
                                                  const u8 *buf,
                                                  size_t len)
{
    int ret;
    uint8_t w_buf[1] = {opcode};

    flash_write_enable();
    cs_select(FLASH_CS_PIN);
    spi_write_blocking(FLASH_SPI_IFCE, w_buf, 1);
    if (buf && len > 0)
        spi_write_blocking(FLASH_SPI_IFCE, buf, len);
    cs_deselect(FLASH_CS_PIN);

    return 0;
}

static ssize_t __not_in_flash_func(rpi_spi_read)(struct spi_nor *nor, loff_t from,
                                                 size_t len,
                                                 u_char *read_buf)
{
    int rc;
    // printf("%s, reading from ... 0x%x\n", __func__, from);

    u8 w_buf[4] = {SPINOR_OP_READ, from >> 16, from >> 8, from};

    cs_select(FLASH_CS_PIN);
    rc = spi_write_blocking(FLASH_SPI_IFCE, w_buf, ARRAY_SIZE(w_buf));
    rc = spi_read_blocking(FLASH_SPI_IFCE, 0x0, read_buf, len);
    cs_deselect(FLASH_CS_PIN);

    return rc;
}

static ssize_t __not_in_flash_func(rpi_spi_write)(struct spi_nor *nor, loff_t to,
                                                  size_t len,
                                                  const u_char *write_buf)
{
    int rc;
    // printf("%s, writing to 0x%x ... \n", __func__, to);

    u8 w_buf[4] = {SPINOR_OP_PP, to >> 16, to >> 8, to};

    flash_write_enable();
    cs_select(FLASH_CS_PIN);
    rc = spi_write_blocking(FLASH_SPI_IFCE, w_buf, ARRAY_SIZE(w_buf));
    rc = spi_write_blocking(FLASH_SPI_IFCE, write_buf, len);
    cs_deselect(FLASH_CS_PIN);
    flash_wait_done();
    // vTaskDelay(3);
    return rc;
}

static int __not_in_flash_func(rpi_spi_erase)(struct spi_nor *nor, loff_t offs)
{
    // printf("%s, erasing block 0x%x ... \n", __func__, offs);

    u8 w_buf[4] = {SPINOR_OP_BE_4K, offs >> 16, offs >> 8, offs};
    flash_write_enable();
    cs_select(FLASH_CS_PIN);
    spi_write_blocking(FLASH_SPI_IFCE, w_buf, ARRAY_SIZE(w_buf));
    cs_deselect(FLASH_CS_PIN);
    // vTaskDelay(200);
    flash_wait_done();

    return 0;
}

const struct spi_nor_controller_ops rpi_spi_controller_ops = {
    .read_reg  = rpi_spi_read_reg,
    .write_reg = rpi_spi_write_reg,
    .read      = rpi_spi_read,
    .write     = rpi_spi_write,
    .erase     = rpi_spi_erase,
};

static int __init rpi_spi_init(void)
{
    printk("%s, initializing rpi spi nor interface ...\n", __func__);
    /* HAL init */
    spi_init(FLASH_SPI_IFCE, 12000000);
    gpio_set_function(FLASH_SCK_PIN, GPIO_FUNC_SPI);
    // gpio_set_function(FLASH_CS_PIN, GPIO_FUNC_SPI);
    gpio_set_function(FLASH_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(FLASH_RX_PIN, GPIO_FUNC_SPI);
    bi_decl(bi_3pins_with_func(FLASH_SCK_PIN, FLASH_TX_PIN, FLASH_RX_PIN, GPIO_FUNC_SPI));

    gpio_init(FLASH_CS_PIN);
    gpio_put(FLASH_CS_PIN, 1);
    gpio_set_dir(FLASH_CS_PIN, GPIO_OUT);
    bi_decl(bi_1pin_with_func(FLASH_CS_PIN, GPIO_FUNC_SPI));

    // const uint dma_tx = dma_claim_unused_channel(true);
    // const uint dma_rx = dma_claim_unused_channel(true);

    // static uint8_t txbuf[256];

    // printk("configure TX DMA\n");

    // dma_channel_config c = dma_channel_get_default_config(dma_tx);
    // channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    // channel_config_set_dreq(&c, spi_get_dreq(FLASH_SPI_IFCE, true));
    // dma_channel_configure(dma_tx, &c,
    //                     &spi_get_hw(FLASH_SPI_IFCE)->dr),
    //                     tx_buf,
    //                     ARRAY_SIZE(txbuf),
    //                     false);

    // printk("Staring DMAs\n");

    // dma_channel_unclaim(dma_tx);
    // dma_channel_unclaim(dma_rx);

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
subsys_initcall(rpi_spi_init);

// static SUBSYS_INITCALL(rpi_spi_controller_init)
// {
//  extern void register_nor_controller_ops(const struct spi_nor_controller_ops *ops);

//  pr_err("registering rpi spi controller ...\n");
//  register_nor_controller_ops(&rpi_spi_controller_ops);
// }

// void winbond_flash_test()
// {
//     /* match device */
//     // winbond_flash_read_id();
//     rpi_spi_erase(NULL, 0);
//     vTaskDelay(150);

//     u8 test_data[1] = {0x59};
//     u8 read_buf[1];
//     /* write a byte to address */
//     rpi_spi_write(NULL, 0x10, 1, test_data);

//     vTaskDelay(20);

//     // /* read a byte from address */
//     rpi_spi_read(NULL, 0x10, 1, read_buf);
//     printf("read : 0x%02x\n", read_buf[0]);
// }