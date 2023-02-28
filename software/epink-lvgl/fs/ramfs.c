/**
 * @file ramfs.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
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

#include <stdlib.h>
#include <generated/autoconf.h>

#include "pico/stdlib.h"

#include "common/tools.h"
#include "common/init.h"

#include "fs/lfs/lfs.h"
#include "fs/lfs/hal/lfs_rambd.h"

#include "lib/printk.h"

#define LFS_READ_SIZE       16
#define LFS_PROG_SIZE       16

#ifdef CONFIG_LFS_RAMFS_BLOCK_SIZE
    #define LFS_BLOCK_SIZE      CONFIG_LFS_RAMFS_BLOCK_SIZE
#else
    #define LFS_BLOCK_SIZE      64
#endif

#define LFS_BLOCK_COUNT     1

#define LFS_CACHE_SIZE      16
#define LFS_LOOKAHEAD_SIZE  16
#define LFS_BLOCK_CYCLES    200

#define LFS_READ_BUFFER_SIZE        LFS_CACHE_SIZE
#define LFS_PROG_BUFFER_SIZE        LFS_CACHE_SIZE
#define LFS_LOOKAHEAD_BUFFER_SIZE   LFS_CACHE_SIZE

lfs_t ramfs_lfs;
lfs_file_t ramfs_file;

static uint8_t read_buffer[LFS_READ_BUFFER_SIZE];
static uint8_t prog_buffer[LFS_PROG_BUFFER_SIZE];
static uint8_t lookahead_buffer[LFS_LOOKAHEAD_BUFFER_SIZE];

static uint8_t *ramfs_mem;

static struct lfs_config ramfs_cfg;
static struct lfs_file_config ramfs_f_cfg;
static uint32_t boot_count = 0;

void ramfs_test(void)
{
    int err = lfs_mount(&ramfs_lfs, &ramfs_cfg);

    if (err) {
        // printf("require a format ops\n");
        lfs_format(&ramfs_lfs, &ramfs_cfg);
        lfs_mount(&ramfs_lfs, &ramfs_cfg);
    }

    lfs_file_opencfg(&ramfs_lfs, &ramfs_file, "boot_count", LFS_O_RDWR | LFS_O_CREAT, &ramfs_f_cfg);
    lfs_file_read(&ramfs_lfs, &ramfs_file, &boot_count, sizeof(boot_count));
    printf("boot_count : %d\n", boot_count);

    boot_count += 1;
    lfs_file_rewind(&ramfs_lfs, &ramfs_file);
    lfs_file_write(&ramfs_lfs, &ramfs_file, &boot_count, sizeof(boot_count));

    lfs_file_close(&ramfs_lfs, &ramfs_file);

    lfs_unmount(&ramfs_lfs);
}

fs_initcall(ramfs_init);

static int ramfs_init(void)
{
    printk("%s, initializing RAM file system ...\n", __func__);

    ramfs_mem = (uint8_t *)malloc(LFS_BLOCK_SIZE * LFS_BLOCK_COUNT);

    struct lfs_rambd_config rambd_cfg = {
        .buffer = ramfs_mem,
    };

    lfs_rambd_t rambd = {
        .buffer = ramfs_mem,
        .cfg = &rambd_cfg,
    };

    struct lfs_config cfg = {
        .context = &rambd,

        .read = lfs_rambd_read,
        .prog = lfs_rambd_prog,
        .erase = lfs_rambd_erase,
        .sync = lfs_rambd_sync,

        .read_size = LFS_READ_SIZE,
        .prog_size = LFS_PROG_SIZE,
        .block_size = LFS_BLOCK_SIZE,
        .block_count = LFS_BLOCK_COUNT,
        .cache_size = LFS_CACHE_SIZE,
        .lookahead_size = LFS_LOOKAHEAD_SIZE,
        .block_cycles = LFS_BLOCK_CYCLES,

        .read_buffer = read_buffer,
        .prog_buffer = prog_buffer,
        .lookahead_buffer = lookahead_buffer,
    };
    lfs_rambd_createcfg(&ramfs_cfg, &rambd_cfg);


    int err = lfs_mount(&ramfs_lfs, &ramfs_cfg);
    if (err) {
        lfs_format(&ramfs_lfs, &ramfs_cfg);
        lfs_mount(&ramfs_lfs, &ramfs_cfg);
    }

    lfs_unmount(&ramfs_lfs);

    return 0;
}