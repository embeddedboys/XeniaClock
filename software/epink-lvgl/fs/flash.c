/**
 * @file flash.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-06
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
#include "fs/lfs/hal/lfs_flashbd.h"

#include "lib/printk.h"

lfs_t flashfs_lfs;
lfs_file_t flashfs_file;

#define LFS_FLASH_READ_SIZE         16
#define LFS_FLASH_PROG_SIZE         16
#define LFS_FLASH_BLOCK_SIZE        4096
#define LFS_FLASH_BLOCK_COUNT       1024    /* for w25q32 */
#define LFS_FLASH_CACHE_SIZE        16
#define LFS_FLASH_BLOCK_CYCLES      500
#define LFS_FLASH_LOOKAHEAD_SIZE    16


#ifdef LFS_NO_MALLOC
#define LFS_FLASH_FILE_BUFFER_SIZE  16
static uint8_t file_buffer[LFS_FLASH_FILE_BUFFER_SIZE];
static uint8_t read_buffer[LFS_FLASH_READ_SIZE];
static uint8_t prog_buffer[LFS_FLASH_PROG_SIZE];
static uint8_t lookahead_buffer[LFS_FLASH_LOOKAHEAD_SIZE];
static struct lfs_file_config flashfs_f_cfg = {
    .buffer = file_buffer,
    .attr_count = 0,
    .attrs = 0,
};
#endif

static struct lfs_config flashfs_cfg = {
    .context = NULL,

    .read  = lfs_flashbd_read,
    .prog  = lfs_flashbd_prog,
    .erase = lfs_flashbd_erase,
    .sync  = lfs_flashbd_sync,

    .read_size      = LFS_FLASH_READ_SIZE,
    .prog_size      = LFS_FLASH_PROG_SIZE,
    .block_size     = LFS_FLASH_BLOCK_SIZE,
    .block_count    = LFS_FLASH_BLOCK_COUNT,
    .cache_size     = LFS_FLASH_CACHE_SIZE,
    .lookahead_size = LFS_FLASH_LOOKAHEAD_SIZE,
    .block_cycles   = LFS_FLASH_BLOCK_CYCLES,

#ifdef LFS_NO_MALLOC
    .read_buffer      = read_buffer,
    .prog_buffer      = prog_buffer,
    .lookahead_buffer = lookahead_buffer,
#endif
};

int flashfs_mkdir(const char *dir)
{
    int rc = lfs_mkdir(&flashfs_lfs, dir);
    if (rc) {
        printf("failed to create dir !\n");
        return rc;
    }

    return 0;
}

int flashfs_find_file(const char *path, const char *parent, const char *filename, char *abs_path)
{
    lfs_dir_t dir;
    struct lfs_info info;

    char fullpath[64];

    if (parent)
        sprintf(fullpath, "%s/%s", parent, path);
    else
        sprintf(fullpath, "%s", path);

    int err = lfs_dir_open(&flashfs_lfs, &dir, fullpath);
    if (err) {
        printf("Failed to open directory: %s\n", fullpath);
        return -1;
    }

    while (lfs_dir_read(&flashfs_lfs, &dir, &info) != 0) {
        // skip . and ..
        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0) {
            continue;
        }

        if (info.type == LFS_TYPE_REG) {
            if (strcmp(filename, info.name) == 0) {
                printf("File: %s/%s (%u bytes)\n", fullpath, info.name, info.size);
                sprintf(abs_path, "%s/%s", fullpath, info.name);
            }
        } else if (info.type == LFS_TYPE_DIR) {
            printf("Directory: %s/%s\n", fullpath, info.name);
            flashfs_find_file(info.name, fullpath, filename, abs_path);
        } else {
            printf("Unknown type: %s/%s\n", fullpath, info.name);
        }
    }

    return -1;
}

void flashfs_traverse_directory(const char *path, const char *parent)
{
    lfs_dir_t dir;
    struct lfs_info info;

    char fullpath[64];

    if (parent)
        sprintf(fullpath, "%s/%s", parent, path);
    else
        sprintf(fullpath, "%s", path);

    int err = lfs_dir_open(&flashfs_lfs, &dir, fullpath);
    if (err) {
        printf("Failed to open directory: %s\n", fullpath);
        return;
    }

    while (lfs_dir_read(&flashfs_lfs, &dir, &info) != 0) {
        // skip . and ..
        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0) {
            continue;
        }

        if (info.type == LFS_TYPE_REG) {
            printf("File: %s/%s (%u bytes)\n", fullpath, info.name, info.size);
        } else if (info.type == LFS_TYPE_DIR) {
            printf("Directory: %s/%s\n", fullpath, info.name);
            flashfs_traverse_directory(info.name, fullpath);
        } else {
            printf("Unknown type: %s/%s\n", fullpath, info.name);
        }
    }

    lfs_dir_close(&flashfs_lfs, &dir);
}

void flashfs_write(const char *file_name, const void *buffer, u32 size)
{

    lfs_file_t file;

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

#ifdef LFS_NO_MALLOC
    lfs_file_opencfg(&flashfs_lfs, &file, file_name, LFS_O_RDWR | LFS_O_CREAT,
                     &flashfs_f_cfg);
#else
    lfs_file_open(&flashfs_lfs, &file, file_name, LFS_O_RDWR | LFS_O_CREAT);
#endif

    // lfs_file_rewind(&flashfs_lfs, &file);
    lfs_file_write(&flashfs_lfs, &file, buffer, size);
    lfs_file_close(&flashfs_lfs, &file);

    lfs_unmount(&flashfs_lfs);
}

void flashfs_read(const char *file_name, void *buffer, u32 size)
{
    lfs_file_t file;

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

#ifdef LFS_NO_MALLOC
    lfs_file_opencfg(&flashfs_lfs, &file, file_name, LFS_O_RDWR | LFS_O_CREAT,
                     &flashfs_f_cfg);
#else
    lfs_file_open(&flashfs_lfs, &file, file_name, LFS_O_RDWR | LFS_O_CREAT);
#endif

    lfs_file_read(&flashfs_lfs, &file, buffer, size);

    lfs_file_close(&flashfs_lfs, &file);

    lfs_unmount(&flashfs_lfs);
}

#if 0
void flashfs_test(void)
{
    lfs_file_t file;

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

    uint32_t boot_count = 0;

#ifdef LFS_NO_MALLOC
    lfs_file_opencfg(&flashfs_lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT,
                     &flashfs_f_cfg);
#else
    lfs_file_open(&flashfs_lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
#endif

    lfs_file_read(&flashfs_lfs, &file, &boot_count, sizeof(boot_count));
    boot_count += 1;
    lfs_file_rewind(&flashfs_lfs, &file);
    lfs_file_write(&flashfs_lfs, &file, &boot_count, sizeof(boot_count));
    lfs_file_close(&flashfs_lfs, &file);

    lfs_unmount(&flashfs_lfs);

    printf("boot_count : %d\n", boot_count);
    return;
}
#else
void flashfs_test(void)
{
    uint32_t boot_count = 0;

    flashfs_read("boot_count", &boot_count, sizeof(boot_count));
    boot_count += 1;
    flashfs_write("boot_count", &boot_count, sizeof(boot_count));

    printf("boot_count : %d\n", boot_count);
    if (boot_count % 10 == 0) {
        boot_count = 0;
        flashfs_write("boot_count", &boot_count, sizeof(boot_count));
    }

    return;
}
#endif

int flashfs_init(void)
{
    printf("%s, initializing FLASH file system ...\n", __func__);

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

    lfs_mkdir(&flashfs_lfs, "/usr");
    lfs_mkdir(&flashfs_lfs, "/home");
    lfs_mkdir(&flashfs_lfs, "/lib");

    lfs_unmount(&flashfs_lfs);
    // struct lfs_flashbd_config flashbd_cfg = {
    //     .erase_value = 0,
    //     .buffer = NULL,
    // };

    // lfs_flashbd_t flashbd = {
    //     .cfg = &flashbd_cfg,
    //     .buffer = NULL,
    // };

    // printf("%s, creating flashbd cfg ...\n", __func__);
    // lfs_flashbd_createcfg(&flashfs_cfg, &flashbd_cfg);

    // int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    // if (err) {
    //     printf("require a format ops\n");
    //     lfs_format(&flashfs_lfs, &flashfs_cfg);
    //     lfs_mount(&flashfs_lfs, &flashfs_cfg);
    // }

    // lfs_unmount(&flashfs_lfs);

    return 0;
}
