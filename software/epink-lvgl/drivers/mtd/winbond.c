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

#include <FreeRTOS.h>
#include "task.h"

#include <common/init.h>
#include <common/tools.h>

#include <stdio.h>
#include <string.h>
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "common/vals.h"
#include "pico/binary_info.h"

#define FLASH_SPI_IFCE  spi1

#define FLASH_SCK_PIN   10
#define FLASH_TX_PIN    11
#define FLASH_RX_PIN    8
#define FLASH_CS_PIN    9

#define WINBOND_FLASH_CMD_PAGE_PROGRAM              0x02
#define WINBOND_FLASH_CMD_READ_DATA                 0x03
#define WINBOND_FLASH_CMD_SECTOR_ERASE              0x20

#define WINBOND_FLASH_CMD_POWER_DOWN                0xb9
#define WINBOND_FLASH_CMD_HIGH_PERFORMANCE_MODE
#define WINBOND_FLASH_CMD_MANUFACTURER_DEVICE_ID    0x90
#define WINBOND_FLASH_CMD_READ_UNIQUE_ID            0x4b
#define WINBOND_FLASH_CMD_JEDEC_ID                  0x9f

#define SPI_NOR_MAX_ID_LEN  6

struct flash_info {
    char *name;
    u8 id[SPI_NOR_MAX_ID_LEN];
    u8 id_len;
    unsigned sector_size;
    u16 n_sectors;
    u16 page_size;
    u16 addr_width;

    bool parse_sfdp;
    u16 flags;
#define SPI_NOR_HAS_LOCK        BIT(0)
#define SPI_NOR_HAS_TB          BIT(1)
#define SPI_NOR_TB_SR_BIT6      BIT(2)
#define SPI_NOR_4BIT_BP         BIT(3)
#define SPI_NOR_BP3_SR_BIT6     BIT(4)
#define SPI_NOR_SWP_IS_VOLATILE     BIT(5)
#define SPI_NOR_NO_ERASE        BIT(6)
#define NO_CHIP_ERASE           BIT(7)
#define SPI_NOR_NO_FR           BIT(8)
#define USE_CLSR            BIT(9)
#define USE_FSR             BIT(10)
#define SPI_NOR_XSR_RDY         BIT(11)

    u8 no_sfdp_flags;
#define SPI_NOR_SKIP_SFDP       BIT(0)
#define SECT_4K             BIT(1)
#define SECT_4K_PMC         BIT(2)
#define SPI_NOR_DUAL_READ       BIT(3)
#define SPI_NOR_QUAD_READ       BIT(4)
#define SPI_NOR_OCTAL_READ      BIT(5)
#define SPI_NOR_OCTAL_DTR_READ      BIT(6)
#define SPI_NOR_OCTAL_DTR_PP        BIT(7)

    u8 fixup_flags;
#define SPI_NOR_4B_OPCODES      BIT(0)
#define SPI_NOR_IO_MODE_EN_VOLATILE BIT(1)

    u8 mfr_flags;

    // const struct spi_nor_otp_organization otp_org;
    // const struct spi_nor_fixups *fixups;
};

/* Used when the "_ext_id" is two bytes at most */
#define INFO(_jedec_id, _ext_id, _sector_size, _n_sectors)      \
    .id = {                         \
                                    ((_jedec_id) >> 16) & 0xff,         \
                                    ((_jedec_id) >> 8) & 0xff,          \
                                    (_jedec_id) & 0xff,             \
                                    ((_ext_id) >> 8) & 0xff,            \
                                    (_ext_id) & 0xff,               \
          },                      \
          .id_len = (!(_jedec_id) ? 0 : (3 + ((_ext_id) ? 2 : 0))),   \
          .sector_size = (_sector_size),              \
          .n_sectors = (_n_sectors),              \
          .page_size = 256,                   \

#define INFO6(_jedec_id, _ext_id, _sector_size, _n_sectors)     \
    .id = {                         \
                                    ((_jedec_id) >> 16) & 0xff,         \
                                    ((_jedec_id) >> 8) & 0xff,          \
                                    (_jedec_id) & 0xff,             \
                                    ((_ext_id) >> 16) & 0xff,           \
                                    ((_ext_id) >> 8) & 0xff,            \
                                    (_ext_id) & 0xff,               \
          },                      \
          .id_len = 6,                        \
          .sector_size = (_sector_size),              \
          .n_sectors = (_n_sectors),              \
          .page_size = 256,                   \

#define CAT25_INFO(_sector_size, _n_sectors, _page_size, _addr_width)   \
    .sector_size = (_sector_size),              \
    .n_sectors = (_n_sectors),              \
    .page_size = (_page_size),              \
    .addr_width = (_addr_width),                \
    .flags = SPI_NOR_NO_ERASE | SPI_NOR_NO_FR,      \

#define S3AN_INFO(_jedec_id, _n_sectors, _page_size)            \
    .id = {                         \
                ((_jedec_id) >> 16) & 0xff,         \
                ((_jedec_id) >> 8) & 0xff,          \
                (_jedec_id) & 0xff              \
          },                      \
          .id_len = 3,                        \
          .sector_size = (8*_page_size),              \
          .n_sectors = (_n_sectors),              \
          .page_size = _page_size,                \
          .addr_width = 3,                    \
          .flags = SPI_NOR_NO_FR | SPI_NOR_XSR_RDY,

#define OTP_INFO(_len, _n_regions, _base, _offset)          \
    .otp_org = {                        \
                    .len = (_len),                  \
                    .base = (_base),                \
                    .offset = (_offset),                \
                    .n_regions = (_n_regions),          \
               },

#define PARSE_SFDP                          \
    .parse_sfdp = true,                     \

#define FLAGS(_flags)                           \
    .flags = (_flags),                  \

#define NO_SFDP_FLAGS(_no_sfdp_flags)                   \
    .no_sfdp_flags = (_no_sfdp_flags),          \

#define FIXUP_FLAGS(_fixup_flags)                   \
    .fixup_flags = (_fixup_flags),              \

#define MFR_FLAGS(_mfr_flags)                       \
    .mfr_flags = (_mfr_flags),              \

struct spi_nor_manufacturer {
    const char *name;
    const struct flash_info *parts;
    unsigned int nparts;
    const struct spi_nor_fixups *fixups;
};

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

static const struct flash_info *
spi_nor_search_part_by_id(const struct flash_info *parts, unsigned int nparts,
                          const u8 *id)
{
    unsigned int i;

    for (i = 0; i < nparts; i++) {
        if (parts[i].id_len &&
            !memcmp(parts[i].id, id, parts[i].id_len))
            return &parts[i];
    }

    return NULL;
}

static const struct flash_info *winbond_flash_read_id(void)
{
    const struct flash_info *info;
    uint8_t cmd[4] = {WINBOND_FLASH_CMD_JEDEC_ID, 0x00, 0x00, 0x00};
    uint8_t res[12];

    uint8_t *id = res + 1;

    flash_transfer(cmd, res, ARRAY_SIZE(cmd), FLASH_CS_PIN);

    info = spi_nor_search_part_by_id(winbond_parts,
                                     ARRAY_SIZE(winbond_parts),
                                     id);
    if (info) {
        pr_debug("matched -> %s, JEDEC id bytes: %02x%02x%02xh\n", info->name, *id, *(id + 1),
               *(id + 2));
        return info;
    } else {
        pr_debug("unrecognized JEDEC id bytes: %02x%02x%02xh\n", *id, *(id + 1), *(id + 2));
    }

    return NULL;
}

size_t winbond_flash_sector_erase(u32 to)
{
    int rc;
    u8 to_buf[4] = { 0x20, to >> 16, to >> 8, to};

    flash_write8(0x06, FLASH_CS_PIN);

    flash_cs_select(FLASH_CS_PIN);

    spi_write_blocking(FLASH_SPI_IFCE, to_buf, ARRAY_SIZE(to_buf));

    flash_cs_deselect(FLASH_CS_PIN);

    return rc;
}

size_t winbond_flash_write_data(u32 to, size_t len, const u8 *buf)
{
    int rc;
    u8 to_buf[4] = { WINBOND_FLASH_CMD_PAGE_PROGRAM, to >> 16, to >> 8, to};

    flash_write8(0x06, FLASH_CS_PIN);

    flash_cs_select(FLASH_CS_PIN);

    spi_write_blocking(FLASH_SPI_IFCE, to_buf, ARRAY_SIZE(to_buf));
    spi_write_blocking(FLASH_SPI_IFCE, buf, len);

    flash_cs_deselect(FLASH_CS_PIN);

    return rc;
}

size_t winbond_flash_read_data(u32 from, size_t len, u8 *buf)
{
    int rc;
    u8 from_buf[4] = { WINBOND_FLASH_CMD_READ_DATA, from >> 16, from >> 8, from};
    u8 read_buf[8] = {0};

    flash_cs_select(FLASH_CS_PIN);

    // spi_write_blocking(FLASH_SPI_IFCE, from_buf, ARRAY_SIZE(from_buf));
    // spi_read_blocking(FLASH_SPI_IFCE, 0x0, buf, len);
    
    spi_write_read_blocking(FLASH_SPI_IFCE, from_buf, read_buf, ARRAY_SIZE(from_buf) + len);
    flash_cs_deselect(FLASH_CS_PIN);

    u8 *p = read_buf + ARRAY_SIZE(from_buf);
    memcpy(buf, p, len);

    return 0;
}

void winbond_flash_init()
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

    /* disable memory protection */
    /* save status regs */
    u8 status_reg1, status_reg2;
    status_reg1 = flash_read_reg(0x05, FLASH_CS_PIN);
    status_reg2 = flash_read_reg(0x35, FLASH_CS_PIN);
    printf("stat1 : 0x%02x, stat2 : 0x%02x\n", status_reg1, status_reg2);

    /* write enable */
    flash_write8(0x06, FLASH_CS_PIN);
    vTaskDelay(5);

    u8 buf[2] = {status_reg1 |= (1 << 1), status_reg2 &= ~(0x03)};
    flash_write_reg(0x01, buf, ARRAY_SIZE(buf), FLASH_CS_PIN);
    vTaskDelay(20);

    status_reg1 = flash_read_reg(0x05, FLASH_CS_PIN);
    status_reg2 = flash_read_reg(0x35, FLASH_CS_PIN);
    printf("stat1 : 0x%02x, stat2 : 0x%02x\n", status_reg1, status_reg2);
}

void winbond_flash_test()
{
    /* match device */
    // winbond_flash_read_id();
    winbond_flash_sector_erase(0);
    vTaskDelay(150);

    u8 test_data[1] = {0x59};
    u8 read_buf[1];
    /* write a byte to address */
    winbond_flash_write_data(0, 1, test_data);
    
    vTaskDelay(20);

    // /* read a byte from address */
    winbond_flash_read_data(0, 1, read_buf);
    printf("read : 0x%02x\n", read_buf[0]);
}

const struct spi_nor_manufacturer spi_nor_winbond = {
    .name = "winbond",
    .parts = winbond_parts,
    .nparts = ARRAY_SIZE(winbond_parts),
};
