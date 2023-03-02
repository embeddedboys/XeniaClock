/**
 * Copyright (c) 2023 IotaHydrae(writeforever@foxmail.com)
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
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

#define LFS_FLASH_FILE_BUFFER_SIZE  16

static uint8_t file_buffer[LFS_FLASH_FILE_BUFFER_SIZE];
static uint8_t read_buffer[LFS_FLASH_READ_SIZE];
static uint8_t prog_buffer[LFS_FLASH_PROG_SIZE];
static uint8_t lookahead_buffer[LFS_FLASH_LOOKAHEAD_SIZE];

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

    .read_buffer      = read_buffer,
    .prog_buffer      = prog_buffer,
    .lookahead_buffer = lookahead_buffer,
};
static struct lfs_file_config flashfs_f_cfg = {
    .buffer = file_buffer,
    .attr_count = 0,
    .attrs = 0,
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

}

void flashfs_read(const char *file_name, void *buffer, u32 size)
{
    lfs_file_t file;

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

    lfs_file_opencfg(&flashfs_lfs, &file, file_name, LFS_O_RDWR | LFS_O_CREAT,
                     &flashfs_f_cfg);
    lfs_file_read(&flashfs_lfs, &file, buffer, size);

    lfs_file_close(&flashfs_lfs, &file);

    lfs_unmount(&flashfs_lfs);
}


void flashfs_test(void)
{
    lfs_file_t file;

    int err = lfs_mount(&flashfs_lfs, &flashfs_cfg);
    if (err) {
        lfs_format(&flashfs_lfs, &flashfs_cfg);
        lfs_mount(&flashfs_lfs, &flashfs_cfg);
    }

    uint32_t boot_count = 0;
    lfs_file_opencfg(&flashfs_lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT,
                     &flashfs_f_cfg);
    lfs_file_read(&flashfs_lfs, &file, &boot_count, sizeof(boot_count));
    boot_count += 1;
    lfs_file_rewind(&flashfs_lfs, &file);
    lfs_file_write(&flashfs_lfs, &file, &boot_count, sizeof(boot_count));
    lfs_file_close(&flashfs_lfs, &file);

    lfs_unmount(&flashfs_lfs);

    printf("boot_count : %d\n", boot_count);
    return;
}

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
