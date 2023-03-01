/**
 * @file lfs_flashbd.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief lfs hal implementation of flash like w25qxx
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
#include <lib/printk.h>
#include "mtd/spi-nor.h"

#include "fs/lfs/hal/implementation.h"
#include "fs/lfs/hal/lfs_flashbd.h"

int lfs_flashbd_createcfg(const struct lfs_config *cfg,
                          const struct lfs_flashbd_config *bdcfg)
{
    // pr_warn("lfs_flashbd_createcfg(%p {.context=%p, "
    //             ".read=%p, .prog=%p, .erase=%p, .sync=%p, "
    //             ".read_size=%"PRIu32", .prog_size=%"PRIu32", "
    //             ".block_size=%"PRIu32", .block_count=%"PRIu32"}, "
    //             "%p {.erase_value=%"PRId32", .buffer=%p})",
    //         (void*)cfg, cfg->context,
    //         (void*)(uintptr_t)cfg->read, (void*)(uintptr_t)cfg->prog,
    //         (void*)(uintptr_t)cfg->erase, (void*)(uintptr_t)cfg->sync,
    //         cfg->read_size, cfg->prog_size, cfg->block_size, cfg->block_count,
    //         (void*)bdcfg, bdcfg->erase_value, bdcfg->buffer);
    lfs_flashbd_t *bd = cfg->context;
    bd->cfg = bdcfg;

    // allocate buffer?
    // if (bd->cfg->buffer) {
    //     bd->buffer = bd->cfg->buffer;
    // } else {
    //     bd->buffer = lfs_malloc(cfg->block_size * cfg->block_count);
    //     if (!bd->buffer) {
    //         pr_warn("lfs_flashbd_createcfg -> %d", LFS_ERR_NOMEM);
    //         return LFS_ERR_NOMEM;
    //     }
    // }

    // zero for reproducibility?
    // if (bd->cfg->erase_value != -1) {
    //     memset(bd->buffer, bd->cfg->erase_value,
    //             cfg->block_size * cfg->block_count);
    // } else {
    //     memset(bd->buffer, 0, cfg->block_size * cfg->block_count);
    // }

    pr_warn("lfs_flashbd_createcfg -> %d\n", 0);
    return LFS_ERR_OK;
}

int lfs_flashbd_create(const struct lfs_config *cfg)
{
    // LFS_RAMBD_TRACE("lfs_flashbd_create(%p {.context=%p, "
    //             ".read=%p, .prog=%p, .erase=%p, .sync=%p, "
    //             ".read_size=%"PRIu32", .prog_size=%"PRIu32", "
    //             ".block_size=%"PRIu32", .block_count=%"PRIu32"})",
    //         (void*)cfg, cfg->context,
    //         (void*)(uintptr_t)cfg->read, (void*)(uintptr_t)cfg->prog,
    //         (void*)(uintptr_t)cfg->erase, (void*)(uintptr_t)cfg->sync,
    //         cfg->read_size, cfg->prog_size, cfg->block_size, cfg->block_count);
    static const struct lfs_flashbd_config defaults = {.erase_value = -1};
    int err = lfs_flashbd_createcfg(cfg, &defaults);
    pr_warn("lfs_flashbd_create -> %d", err);
    return err;
}

int lfs_flashbd_destroy(const struct lfs_config *cfg)
{
    // pr_warn("lfs_flashbd_destroy(%p)", (void*)cfg);
    // // clean up memory
    // lfs_flashbd_t *bd = cfg->context;
    // if (!bd->cfg->buffer) {
    //     lfs_free(bd->buffer);
    // }
    // pr_warn("lfs_flashbd_destroy -> %d", 0);
    return 0;
}

int lfs_flashbd_read(const struct lfs_config *cfg, lfs_block_t block,
                     lfs_off_t off, void *buffer, lfs_size_t size)
{
    // LFS_RAMBD_TRACE("lfs_flashbd_read(%p, "
    //             "0x%"PRIx32", %"PRIu32", %p, %"PRIu32")",
    //         (void*)cfg, block, off, buffer, size);
    // lfs_flashbd_t *bd = cfg->context;

    // check if read is valid
    LFS_ASSERT(off  % cfg->read_size == 0);
    LFS_ASSERT(size % cfg->read_size == 0);
    LFS_ASSERT(block < cfg->block_count);

    // read data
    // printf("%s, reading from 0x%x\n", __func__, block*cfg->block_size + off);
    spi_nor_read((block * cfg->block_size + off), size, buffer);

    return LFS_ERR_OK;
}

int lfs_flashbd_prog(const struct lfs_config *cfg, lfs_block_t block,
                     lfs_off_t off, const void *buffer, lfs_size_t size)
{
    // LFS_RAMBD_TRACE("lfs_flashbd_prog(%p, "
    //             "0x%"PRIx32", %"PRIu32", %p, %"PRIu32")",
    //         (void*)cfg, block, off, buffer, size);
    // lfs_flashbd_t *bd = cfg->context;

    // check if write is valid
    LFS_ASSERT(off  % cfg->prog_size == 0);
    LFS_ASSERT(size % cfg->prog_size == 0);
    LFS_ASSERT(block < cfg->block_count);

    // check that data was erased? only needed for testing
    // if (bd->cfg->erase_value != -1) {
    //     for (lfs_off_t i = 0; i < size; i++) {
    //         LFS_ASSERT(bd->buffer[block*cfg->block_size + off + i] ==
    //                 bd->cfg->erase_value);
    //     }
    // }

    // progflash data
    // memcpy(&bd->buffer[block*cfg->block_size + off], buffer, size);
    spi_nor_write(block * cfg->block_size + off, size, buffer);

    return LFS_ERR_OK;
}

int lfs_flashbd_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    // LFS_RAMBD_TRACE("lfs_flashbd_erase(%p, 0x%"PRIx32")", (void*)cfg, block);
    // lfs_flashbd_t *bd = cfg->context;

    // check if erase is valid
    LFS_ASSERT(block < cfg->block_count);

    // erase, only needed for testing
    // if (bd->cfg->erase_value != -1) {
    // memset(&bd->buffer[block*cfg->block_size],
    //         bd->cfg->erase_value, cfg->block_size);
    spi_nor_ops_erase(block * cfg->block_size);
    // }

    return LFS_ERR_OK;
}

int lfs_flashbd_sync(const struct lfs_config *cfg)
{
     return LFS_ERR_OK;
}
