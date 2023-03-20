/**
 * @file core.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-23
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

#include <linux/err.h>
#include <linux/errno.h>
#include <common/param.h>
#include <common/list.h>
#include <lib/printk.h>

#include <mtd/spi-nor.h>

#include <string.h>
#include <stdlib.h>

#include "core.h"

/* Define max times to check status register before we give up. */

/*
 * For everything but full-chip erase; probably could be much smaller, but kept
 * around for safety for now
 */
#define DEFAULT_READY_WAIT_JIFFIES		(40UL * HZ)

/*
 * For full-chip erase, calibrated to a 2MB flash (M25P16); should be scaled up
 * for larger flash
 */
#define CHIP_ERASE_2MB_READY_WAIT_JIFFIES	(40UL * HZ)

#define SPI_NOR_MAX_ADDR_WIDTH	4

#define SPI_NOR_SRST_SLEEP_MIN 200
#define SPI_NOR_SRST_SLEEP_MAX 400

static struct spi_nor *nor;

static int spi_nor_controller_ops_read_reg(struct spi_nor *nor, u8 opcode,
					   u8 *buf, size_t len)
{
	if (spi_nor_protocol_is_dtr(nor->reg_proto))
		return -EOPNOTSUPP;

	return nor->controller_ops->read_reg(nor, opcode, buf, len);
}

int spi_nor_read_reg(u8 opcode, u8 *buf, size_t len)
{
	if (!nor)
		return -ENODEV;

	return spi_nor_controller_ops_read_reg(nor, opcode, buf, len);
}

static int spi_nor_controller_ops_write_reg(struct spi_nor *nor, u8 opcode,
					    const u8 *buf, size_t len)
{
	if (spi_nor_protocol_is_dtr(nor->reg_proto))
		return -EOPNOTSUPP;

	return nor->controller_ops->write_reg(nor, opcode, buf, len);
}

int spi_nor_write_reg(u8 opcode, const u8 *buf, size_t len)
{
	if (!nor)
		return -ENODEV;

	return spi_nor_controller_ops_write_reg(nor, opcode, buf, len);
}

static int spi_nor_controller_ops_erase(struct spi_nor *nor, loff_t offs)
{
	if (spi_nor_protocol_is_dtr(nor->write_proto))
		return -EOPNOTSUPP;

	return nor->controller_ops->erase(nor, offs);
}

int spi_nor_ops_erase(loff_t offs)
{
	if (!nor)
		return -ENODEV;

	return spi_nor_controller_ops_erase(nor, offs);
}

/**
 * spi_nor_read_data() - read data from flash memory
 * @nor:        pointer to 'struct spi_nor'
 * @from:       offset to read from
 * @len:        number of bytes to read
 * @buf:        pointer to dst buffer
 *
 * Return: number of bytes read successfully, -errno otherwise
 */
ssize_t spi_nor_read_data(struct spi_nor *nor, loff_t from, size_t len, u8 *buf)
{
	// if (nor->spimem)
	// 	return spi_nor_spimem_read_data(nor, from, len, buf);

	return nor->controller_ops->read(nor, from, len, buf);
}

ssize_t spi_nor_read(loff_t from, size_t len, u8 *buf)
{
	if (!nor)
		return -ENODEV;

	spi_nor_read_data(nor, from, len, buf);
}

/**
 * spi_nor_write_data() - write data to flash memory
 * @nor:        pointer to 'struct spi_nor'
 * @to:         offset to write to
 * @len:        number of bytes to write
 * @buf:        pointer to src buffer
 *
 * Return: number of bytes written successfully, -errno otherwise
 */
ssize_t spi_nor_write_data(struct spi_nor *nor, loff_t to, size_t len,
			   const u8 *buf)
{
	// if (nor->spimem)
	// 	return spi_nor_spimem_write_data(nor, to, len, buf);

	return nor->controller_ops->write(nor, to, len, buf);
}

ssize_t spi_nor_write(loff_t to, size_t len, const u8 *buf)
{
	if (!nor)
		return -ENODEV;

	return spi_nor_write_data(nor, to, len, buf);
}

/**
 * spi_nor_write_enable() - Set write enable latch with Write Enable command.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_enable(struct spi_nor *nor)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WREN, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_WREN,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d on Write Enable\n", ret);

	return ret;
}


/**
 * spi_nor_write_disable() - Send Write Disable instruction to the chip.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_disable(struct spi_nor *nor)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRDI, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_WRDI,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d on Write Disable\n", ret);

	return ret;
}

/**
 * spi_nor_read_sr() - Read the Status Register.
 * @nor:	pointer to 'struct spi_nor'.
 * @sr:		pointer to a DMA-able buffer where the value of the
 *              Status Register will be written. Should be at least 2 bytes.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_read_sr(struct spi_nor *nor, u8 *sr)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(1, sr, 0));

	// 	if (nor->reg_proto == SNOR_PROTO_8_8_8_DTR) {
	// 		op.addr.nbytes = nor->params->rdsr_addr_nbytes;
	// 		op.dummy.nbytes = nor->params->rdsr_dummy;
	// 		/*
	// 		 * We don't want to read only one byte in DTR mode. So,
	// 		 * read 2 and then discard the second byte.
	// 		 */
	// 		op.data.nbytes = 2;
	// 	}

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_read_reg(nor, SPINOR_OP_RDSR, sr,
						      1);
	// }

	if (ret)
		pr_dbg("error %d reading SR\n", ret);

	return ret;
}

/**
 * spi_nor_read_fsr() - Read the Flag Status Register.
 * @nor:	pointer to 'struct spi_nor'
 * @fsr:	pointer to a DMA-able buffer where the value of the
 *              Flag Status Register will be written. Should be at least 2
 *              bytes.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_read_fsr(struct spi_nor *nor, u8 *fsr)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDFSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(1, fsr, 0));

	// 	if (nor->reg_proto == SNOR_PROTO_8_8_8_DTR) {
	// 		op.addr.nbytes = nor->params->rdsr_addr_nbytes;
	// 		op.dummy.nbytes = nor->params->rdsr_dummy;
	// 		/*
	// 		 * We don't want to read only one byte in DTR mode. So,
	// 		 * read 2 and then discard the second byte.
	// 		 */
	// 		op.data.nbytes = 2;
	// 	}

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_read_reg(nor, SPINOR_OP_RDFSR, fsr,
						      1);
	// }

	if (ret)
		pr_dbg("error %d reading FSR\n", ret);

	return ret;
}

/**
 * spi_nor_read_cr() - Read the Configuration Register using the
 * SPINOR_OP_RDCR (35h) command.
 * @nor:	pointer to 'struct spi_nor'
 * @cr:		pointer to a DMA-able buffer where the value of the
 *              Configuration Register will be written.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_read_cr(struct spi_nor *nor, u8 *cr)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDCR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(1, cr, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_read_reg(nor, SPINOR_OP_RDCR, cr,
						      1);
	// }

	if (ret)
		pr_dbg("error %d reading CR\n", ret);

	return ret;
}

/**
 * spi_nor_set_4byte_addr_mode() - Enter/Exit 4-byte address mode.
 * @nor:	pointer to 'struct spi_nor'.
 * @enable:	true to enter the 4-byte address mode, false to exit the 4-byte
 *		address mode.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_set_4byte_addr_mode(struct spi_nor *nor, bool enable)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(enable ?
	// 					  SPINOR_OP_EN4B :
	// 					  SPINOR_OP_EX4B,
	// 					  0),
	// 			  SPI_MEM_OP_NO_ADDR,
	// 			  SPI_MEM_OP_NO_DUMMY,
	// 			  SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor,
						       enable ? SPINOR_OP_EN4B :
								SPINOR_OP_EX4B,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d setting 4-byte mode\n", ret);

	return ret;
}

/**
 * spi_nor_write_ear() - Write Extended Address Register.
 * @nor:	pointer to 'struct spi_nor'.
 * @ear:	value to write to the Extended Address Register.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_ear(struct spi_nor *nor, u8 ear)
{
	int ret;

	nor->bouncebuf[0] = ear;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WREAR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_OUT(1, nor->bouncebuf, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_WREAR,
						       nor->bouncebuf, 1);
	// }

	if (ret)
		pr_dbg("error %d writing EAR\n", ret);

	return ret;
}

/**
 * spi_nor_xread_sr() - Read the Status Register on S3AN flashes.
 * @nor:	pointer to 'struct spi_nor'.
 * @sr:		pointer to a DMA-able buffer where the value of the
 *              Status Register will be written.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_xread_sr(struct spi_nor *nor, u8 *sr)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_XRDSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(1, sr, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_read_reg(nor, SPINOR_OP_XRDSR, sr,
						      1);
	// }

	if (ret)
		pr_dbg("error %d reading XRDSR\n", ret);

	return ret;
}

/**
 * spi_nor_xsr_ready() - Query the Status Register of the S3AN flash to see if
 * the flash is ready for new commands.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 1 if ready, 0 if not ready, -errno on errors.
 */
static int spi_nor_xsr_ready(struct spi_nor *nor)
{
	int ret;

	ret = spi_nor_xread_sr(nor, nor->bouncebuf);
	if (ret)
		return ret;

	return !!(nor->bouncebuf[0] & XSR_RDY);
}

/**
 * spi_nor_clear_sr() - Clear the Status Register.
 * @nor:	pointer to 'struct spi_nor'.
 */
static void spi_nor_clear_sr(struct spi_nor *nor)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CLSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_CLSR,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d clearing SR\n", ret);
}

/**
 * spi_nor_sr_ready() - Query the Status Register to see if the flash is ready
 * for new commands.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 1 if ready, 0 if not ready, -errno on errors.
 */
static int spi_nor_sr_ready(struct spi_nor *nor)
{
	int ret = spi_nor_read_sr(nor, nor->bouncebuf);

	if (ret)
		return ret;

	if (nor->flags & SNOR_F_USE_CLSR &&
	    nor->bouncebuf[0] & (SR_E_ERR | SR_P_ERR)) {
		if (nor->bouncebuf[0] & SR_E_ERR){
			pr_err("Erase Error occurred\n");
		} else
			pr_err("Programming Error occurred\n");

		spi_nor_clear_sr(nor);

		/*
		 * WEL bit remains set to one when an erase or page program
		 * error occurs. Issue a Write Disable command to protect
		 * against inadvertent writes that can possibly corrupt the
		 * contents of the memory.
		 */
		ret = spi_nor_write_disable(nor);
		if (ret)
			return ret;

		return -EIO;
	}

	return !(nor->bouncebuf[0] & SR_WIP);
}

/**
 * spi_nor_clear_fsr() - Clear the Flag Status Register.
 * @nor:	pointer to 'struct spi_nor'.
 */
static void spi_nor_clear_fsr(struct spi_nor *nor)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CLFSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_CLFSR,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d clearing FSR\n", ret);
}

/**
 * spi_nor_fsr_ready() - Query the Flag Status Register to see if the flash is
 * ready for new commands.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 1 if ready, 0 if not ready, -errno on errors.
 */
static int spi_nor_fsr_ready(struct spi_nor *nor)
{
	int ret = spi_nor_read_fsr(nor, nor->bouncebuf);

	if (ret)
		return ret;

	if (nor->bouncebuf[0] & (FSR_E_ERR | FSR_P_ERR)) {
		if (nor->bouncebuf[0] & FSR_E_ERR) {
			pr_err("Erase operation failed.\n");
		} else
			pr_err("Program operation failed.\n");

		if (nor->bouncebuf[0] & FSR_PT_ERR)
			pr_err("Attempted to modify a protected sector.\n");

		spi_nor_clear_fsr(nor);

		/*
		 * WEL bit remains set to one when an erase or page program
		 * error occurs. Issue a Write Disable command to protect
		 * against inadvertent writes that can possibly corrupt the
		 * contents of the memory.
		 */
		ret = spi_nor_write_disable(nor);
		if (ret)
			return ret;

		return -EIO;
	}

	return !!(nor->bouncebuf[0] & FSR_READY);
}

/**
 * spi_nor_ready() - Query the flash to see if it is ready for new commands.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 1 if ready, 0 if not ready, -errno on errors.
 */
static int spi_nor_ready(struct spi_nor *nor)
{
	int sr, fsr;

	if (nor->flags & SNOR_F_READY_XSR_RDY)
		sr = spi_nor_xsr_ready(nor);
	else
		sr = spi_nor_sr_ready(nor);
	if (sr < 0)
		return sr;
	fsr = nor->flags & SNOR_F_USE_FSR ? spi_nor_fsr_ready(nor) : 1;
	if (fsr < 0)
		return fsr;
	return sr && fsr;
}

/**
 * spi_nor_wait_till_ready_with_timeout() - Service routine to read the
 * Status Register until ready, or timeout occurs.
 * @nor:		pointer to "struct spi_nor".
 * @timeout_jiffies:	jiffies to wait until timeout.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_wait_till_ready_with_timeout(struct spi_nor *nor,
						unsigned long timeout_jiffies)
{
	unsigned long deadline;
	int timeout = 0, ret;

	// deadline = jiffies + timeout_jiffies;

	while (!timeout) {
		// if (time_after_eq(jiffies, deadline))
			// timeout = 1;

		ret = spi_nor_ready(nor);
		if (ret < 0)
			return ret;
		if (ret)
			return 0;

		// cond_resched();
	}

	pr_dbg("flash operation timed out\n");

	return -ETIMEDOUT;
}

/**
 * spi_nor_wait_till_ready() - Wait for a predefined amount of time for the
 * flash to be ready, or timeout occurs.
 * @nor:	pointer to "struct spi_nor".
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_wait_till_ready(struct spi_nor *nor)
{
	return spi_nor_wait_till_ready_with_timeout(nor,
						    DEFAULT_READY_WAIT_JIFFIES);
}

/**
 * spi_nor_global_block_unlock() - Unlock Global Block Protection.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_global_block_unlock(struct spi_nor *nor)
{
	int ret;

	ret = spi_nor_write_enable(nor);
	if (ret)
		return ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_GBULK, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_GBULK,
						       NULL, 0);
	// }

	if (ret) {
		pr_dbg("error %d on Global Block Unlock\n", ret);
		return ret;
	}

	return spi_nor_wait_till_ready(nor);
}

/**
 * spi_nor_write_sr() - Write the Status Register.
 * @nor:	pointer to 'struct spi_nor'.
 * @sr:		pointer to DMA-able buffer to write to the Status Register.
 * @len:	number of bytes to write to the Status Register.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_sr(struct spi_nor *nor, const u8 *sr, size_t len)
{
	int ret;

	ret = spi_nor_write_enable(nor);
	if (ret)
		return ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRSR, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_OUT(len, sr, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_WRSR, sr,
						       len);
	// }

	if (ret) {
		pr_dbg("error %d writing SR\n", ret);
		return ret;
	}

	return spi_nor_wait_till_ready(nor);
}

/**
 * spi_nor_write_sr1_and_check() - Write one byte to the Status Register 1 and
 * ensure that the byte written match the received value.
 * @nor:	pointer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_write_sr1_and_check(struct spi_nor *nor, u8 sr1)
{
	int ret;

	nor->bouncebuf[0] = sr1;

	ret = spi_nor_write_sr(nor, nor->bouncebuf, 1);
	if (ret)
		return ret;

	ret = spi_nor_read_sr(nor, nor->bouncebuf);
	if (ret)
		return ret;

	if (nor->bouncebuf[0] != sr1) {
		pr_dbg("SR1: read back test failed\n");
		return -EIO;
	}

	return 0;
}

/**
 * spi_nor_write_16bit_sr_and_check() - Write the Status Register 1 and the
 * Status Register 2 in one shot. Ensure that the byte written in the Status
 * Register 1 match the received value, and that the 16-bit Write did not
 * affect what was already in the Status Register 2.
 * @nor:	pointer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register 1.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_write_16bit_sr_and_check(struct spi_nor *nor, u8 sr1)
{
	int ret;
	u8 *sr_cr = nor->bouncebuf;
	u8 cr_written;

	/* Make sure we don't overwrite the contents of Status Register 2. */
	if (!(nor->flags & SNOR_F_NO_READ_CR)) {
		ret = spi_nor_read_cr(nor, &sr_cr[1]);
		if (ret)
			return ret;
	} else if (nor->params->quad_enable) {
		/*
		 * If the Status Register 2 Read command (35h) is not
		 * supported, we should at least be sure we don't
		 * change the value of the SR2 Quad Enable bit.
		 *
		 * We can safely assume that when the Quad Enable method is
		 * set, the value of the QE bit is one, as a consequence of the
		 * nor->params->quad_enable() call.
		 *
		 * We can safely assume that the Quad Enable bit is present in
		 * the Status Register 2 at BIT(1). According to the JESD216
		 * revB standard, BFPT DWORDS[15], bits 22:20, the 16-bit
		 * Write Status (01h) command is available just for the cases
		 * in which the QE bit is described in SR2 at BIT(1).
		 */
		sr_cr[1] = SR2_QUAD_EN_BIT1;
	} else {
		sr_cr[1] = 0;
	}

	sr_cr[0] = sr1;

	ret = spi_nor_write_sr(nor, sr_cr, 2);
	if (ret)
		return ret;

	if (nor->flags & SNOR_F_NO_READ_CR)
		return 0;

	cr_written = sr_cr[1];

	ret = spi_nor_read_cr(nor, &sr_cr[1]);
	if (ret)
		return ret;

	if (cr_written != sr_cr[1]) {
		pr_dbg("CR: read back test failed\n");
		return -EIO;
	}

	return 0;
}

/**
 * spi_nor_write_16bit_cr_and_check() - Write the Status Register 1 and the
 * Configuration Register in one shot. Ensure that the byte written in the
 * Configuration Register match the received value, and that the 16-bit Write
 * did not affect what was already in the Status Register 1.
 * @nor:	pointer to a 'struct spi_nor'.
 * @cr:		byte value to be written to the Configuration Register.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_16bit_cr_and_check(struct spi_nor *nor, u8 cr)
{
	int ret;
	u8 *sr_cr = nor->bouncebuf;
	u8 sr_written;

	/* Keep the current value of the Status Register 1. */
	ret = spi_nor_read_sr(nor, sr_cr);
	if (ret)
		return ret;

	sr_cr[1] = cr;

	ret = spi_nor_write_sr(nor, sr_cr, 2);
	if (ret)
		return ret;

	sr_written = sr_cr[0];

	ret = spi_nor_read_sr(nor, sr_cr);
	if (ret)
		return ret;

	if (sr_written != sr_cr[0]) {
		pr_dbg("SR: Read back test failed\n");
		return -EIO;
	}

	if (nor->flags & SNOR_F_NO_READ_CR)
		return 0;

	ret = spi_nor_read_cr(nor, &sr_cr[1]);
	if (ret)
		return ret;

	if (cr != sr_cr[1]) {
		pr_dbg("CR: read back test failed\n");
		return -EIO;
	}

	return 0;
}

/**
 * spi_nor_write_sr_and_check() - Write the Status Register 1 and ensure that
 * the byte written match the received value without affecting other bits in the
 * Status Register 1 and 2.
 * @nor:	pointer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register.
 *
 * Return: 0 on success, -errno otherwise.
 */
int spi_nor_write_sr_and_check(struct spi_nor *nor, u8 sr1)
{
	if (nor->flags & SNOR_F_HAS_16BIT_SR)
		return spi_nor_write_16bit_sr_and_check(nor, sr1);

	return spi_nor_write_sr1_and_check(nor, sr1);
}

/**
 * spi_nor_write_sr2() - Write the Status Register 2 using the
 * SPINOR_OP_WRSR2 (3eh) command.
 * @nor:	pointer to 'struct spi_nor'.
 * @sr2:	pointer to DMA-able buffer to write to the Status Register 2.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_write_sr2(struct spi_nor *nor, const u8 *sr2)
{
	int ret;

	ret = spi_nor_write_enable(nor);
	if (ret)
		return ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRSR2, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_OUT(1, sr2, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor, SPINOR_OP_WRSR2,
						       sr2, 1);
	// }

	if (ret) {
		pr_dbg("error %d writing SR2\n", ret);
		return ret;
	}

	return spi_nor_wait_till_ready(nor);
}

/**
 * spi_nor_read_sr2() - Read the Status Register 2 using the
 * SPINOR_OP_RDSR2 (3fh) command.
 * @nor:	pointer to 'struct spi_nor'.
 * @sr2:	pointer to DMA-able buffer where the value of the
 *		Status Register 2 will be written.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_read_sr2(struct spi_nor *nor, u8 *sr2)
{
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDSR2, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(1, sr2, 0));

	// 	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_read_reg(nor, SPINOR_OP_RDSR2, sr2,
						      1);
	// }

	if (ret)
		pr_dbg("error %d reading SR2\n", ret);

	return ret;
}

/**
 * spi_nor_erase_chip() - Erase the entire flash memory.
 * @nor:	pointer to 'struct spi_nor'.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_erase_chip(struct spi_nor *nor)
{
	int ret;

	// dev_dbg(nor->dev, " %lldKiB\n", (long long)(nor->mtd.size >> 10));

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CHIP_ERASE, 0),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->write_proto);

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = spi_nor_controller_ops_write_reg(nor,
						       SPINOR_OP_CHIP_ERASE,
						       NULL, 0);
	// }

	if (ret)
		pr_dbg("error %d erasing chip\n", ret);

	return ret;
}

static u8 spi_nor_convert_opcode(u8 opcode, const u8 table[][2], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (table[i][0] == opcode)
			return table[i][1];

	/* No conversion found, keep input op code. */
	return opcode;
}

u8 spi_nor_convert_3to4_read(u8 opcode)
{
	static const u8 spi_nor_3to4_read[][2] = {
		{ SPINOR_OP_READ,	SPINOR_OP_READ_4B },
		{ SPINOR_OP_READ_FAST,	SPINOR_OP_READ_FAST_4B },
		{ SPINOR_OP_READ_1_1_2,	SPINOR_OP_READ_1_1_2_4B },
		{ SPINOR_OP_READ_1_2_2,	SPINOR_OP_READ_1_2_2_4B },
		{ SPINOR_OP_READ_1_1_4,	SPINOR_OP_READ_1_1_4_4B },
		{ SPINOR_OP_READ_1_4_4,	SPINOR_OP_READ_1_4_4_4B },
		{ SPINOR_OP_READ_1_1_8,	SPINOR_OP_READ_1_1_8_4B },
		{ SPINOR_OP_READ_1_8_8,	SPINOR_OP_READ_1_8_8_4B },

		{ SPINOR_OP_READ_1_1_1_DTR,	SPINOR_OP_READ_1_1_1_DTR_4B },
		{ SPINOR_OP_READ_1_2_2_DTR,	SPINOR_OP_READ_1_2_2_DTR_4B },
		{ SPINOR_OP_READ_1_4_4_DTR,	SPINOR_OP_READ_1_4_4_DTR_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_read,
				      ARRAY_SIZE(spi_nor_3to4_read));
}

static u8 spi_nor_convert_3to4_program(u8 opcode)
{
	static const u8 spi_nor_3to4_program[][2] = {
		{ SPINOR_OP_PP,		SPINOR_OP_PP_4B },
		{ SPINOR_OP_PP_1_1_4,	SPINOR_OP_PP_1_1_4_4B },
		{ SPINOR_OP_PP_1_4_4,	SPINOR_OP_PP_1_4_4_4B },
		{ SPINOR_OP_PP_1_1_8,	SPINOR_OP_PP_1_1_8_4B },
		{ SPINOR_OP_PP_1_8_8,	SPINOR_OP_PP_1_8_8_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_program,
				      ARRAY_SIZE(spi_nor_3to4_program));
}

static u8 spi_nor_convert_3to4_erase(u8 opcode)
{
	static const u8 spi_nor_3to4_erase[][2] = {
		{ SPINOR_OP_BE_4K,	SPINOR_OP_BE_4K_4B },
		{ SPINOR_OP_BE_32K,	SPINOR_OP_BE_32K_4B },
		{ SPINOR_OP_SE,		SPINOR_OP_SE_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_erase,
				      ARRAY_SIZE(spi_nor_3to4_erase));
}

static bool spi_nor_has_uniform_erase(const struct spi_nor *nor)
{
	return !!nor->params->erase_map.uniform_erase_type;
}

static void spi_nor_set_4byte_opcodes(struct spi_nor *nor)
{
	nor->read_opcode = spi_nor_convert_3to4_read(nor->read_opcode);
	nor->program_opcode = spi_nor_convert_3to4_program(nor->program_opcode);
	nor->erase_opcode = spi_nor_convert_3to4_erase(nor->erase_opcode);

	if (!spi_nor_has_uniform_erase(nor)) {
		struct spi_nor_erase_map *map = &nor->params->erase_map;
		struct spi_nor_erase_type *erase;
		int i;

		for (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) {
			erase = &map->erase_type[i];
			erase->opcode =
				spi_nor_convert_3to4_erase(erase->opcode);
		}
	}
}

// int spi_nor_lock_and_prep(struct spi_nor *nor)
// {
// 	int ret = 0;

// 	mutex_lock(&nor->lock);

// 	if (nor->controller_ops &&  nor->controller_ops->prepare) {
// 		ret = nor->controller_ops->prepare(nor);
// 		if (ret) {
// 			mutex_unlock(&nor->lock);
// 			return ret;
// 		}
// 	}
// 	return ret;
// }

// void spi_nor_unlock_and_unprep(struct spi_nor *nor)
// {
// 	if (nor->controller_ops && nor->controller_ops->unprepare)
// 		nor->controller_ops->unprepare(nor);
// 	mutex_unlock(&nor->lock);
// }


static u32 spi_nor_convert_addr(struct spi_nor *nor, loff_t addr)
{
	if (!nor->params->convert_addr)
		return addr;

	return nor->params->convert_addr(nor, addr);
}

/*
 * Initiate the erasure of a single sector
 */
int spi_nor_erase_sector(struct spi_nor *nor, u32 addr)
{
	int i;

	addr = spi_nor_convert_addr(nor, addr);

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(nor->erase_opcode, 0),
	// 			   SPI_MEM_OP_ADDR(nor->addr_width, addr, 0),
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_NO_DATA);

	// 	spi_nor_spimem_setup_op(nor, &op, nor->write_proto);

	// 	return spi_mem_exec_op(nor->spimem, &op);
	// } else if (nor->controller_ops->erase) {
	// 	return spi_nor_controller_ops_erase(nor, addr);
	// }
    if (nor->controller_ops->erase) {
		return spi_nor_controller_ops_erase(nor, addr);
	}

	/*
	 * Default implementation, if driver doesn't have a specialized HW
	 * control
	 */
	for (i = nor->addr_width - 1; i >= 0; i--) {
		nor->bouncebuf[i] = addr & 0xff;
		addr >>= 8;
	}

	return spi_nor_controller_ops_write_reg(nor, nor->erase_opcode,
						nor->bouncebuf, nor->addr_width);
}

/**
 * spi_nor_div_by_erase_size() - calculate remainder and update new dividend
 * @erase:	pointer to a structure that describes a SPI NOR erase type
 * @dividend:	dividend value
 * @remainder:	pointer to u32 remainder (will be updated)
 *
 * Return: the result of the division
 */
static u64 spi_nor_div_by_erase_size(const struct spi_nor_erase_type *erase,
				     u64 dividend, u32 *remainder)
{
	/* JEDEC JESD216B Standard imposes erase sizes to be power of 2. */
	*remainder = (u32)dividend & erase->size_mask;
	return dividend >> erase->size_shift;
}

/**
 * spi_nor_find_best_erase_type() - find the best erase type for the given
 *				    offset in the serial flash memory and the
 *				    number of bytes to erase. The region in
 *				    which the address fits is expected to be
 *				    provided.
 * @map:	the erase map of the SPI NOR
 * @region:	pointer to a structure that describes a SPI NOR erase region
 * @addr:	offset in the serial flash memory
 * @len:	number of bytes to erase
 *
 * Return: a pointer to the best fitted erase type, NULL otherwise.
 */
static const struct spi_nor_erase_type *
spi_nor_find_best_erase_type(const struct spi_nor_erase_map *map,
			     const struct spi_nor_erase_region *region,
			     u64 addr, u32 len)
{
	const struct spi_nor_erase_type *erase;
	u32 rem;
	int i;
	u8 erase_mask = region->offset & SNOR_ERASE_TYPE_MASK;

	/*
	 * Erase types are ordered by size, with the smallest erase type at
	 * index 0.
	 */
	for (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) {
		/* Does the erase region support the tested erase type? */
		if (!(erase_mask & BIT(i)))
			continue;

		erase = &map->erase_type[i];

		/* Alignment is not mandatory for overlaid regions */
		if (region->offset & SNOR_OVERLAID_REGION &&
		    region->size <= len)
			return erase;

		/* Don't erase more than what the user has asked for. */
		if (erase->size > len)
			continue;

		spi_nor_div_by_erase_size(erase, addr, &rem);
		if (!rem)
			return erase;
	}

	return NULL;
}

static u64 spi_nor_region_is_last(const struct spi_nor_erase_region *region)
{
	return region->offset & SNOR_LAST_REGION;
}

static u64 spi_nor_region_end(const struct spi_nor_erase_region *region)
{
	return (region->offset & ~SNOR_ERASE_FLAGS_MASK) + region->size;
}

/**
 * spi_nor_region_next() - get the next spi nor region
 * @region:	pointer to a structure that describes a SPI NOR erase region
 *
 * Return: the next spi nor region or NULL if last region.
 */
struct spi_nor_erase_region *
spi_nor_region_next(struct spi_nor_erase_region *region)
{
	if (spi_nor_region_is_last(region))
		return NULL;
	region++;
	return region;
}

/**
 * spi_nor_find_erase_region() - find the region of the serial flash memory in
 *				 which the offset fits
 * @map:	the erase map of the SPI NOR
 * @addr:	offset in the serial flash memory
 *
 * Return: a pointer to the spi_nor_erase_region struct, ERR_PTR(-errno)
 *	   otherwise.
 */
static struct spi_nor_erase_region *
spi_nor_find_erase_region(const struct spi_nor_erase_map *map, u64 addr)
{
	struct spi_nor_erase_region *region = map->regions;
	u64 region_start = region->offset & ~SNOR_ERASE_FLAGS_MASK;
	u64 region_end = region_start + region->size;

	while (addr < region_start || addr >= region_end) {
		region = spi_nor_region_next(region);
		if (!region)
			return ERR_PTR(-EINVAL);

		region_start = region->offset & ~SNOR_ERASE_FLAGS_MASK;
		region_end = region_start + region->size;
	}

	return region;
}

static int spi_nor_set_addr_width(struct spi_nor *nor)
{
	if (nor->addr_width) {
		/* already configured from SFDP */
	} else if (nor->read_proto == SNOR_PROTO_8_8_8_DTR) {
		/*
		 * In 8D-8D-8D mode, one byte takes half a cycle to transfer. So
		 * in this protocol an odd address width cannot be used because
		 * then the address phase would only span a cycle and a half.
		 * Half a cycle would be left over. We would then have to start
		 * the dummy phase in the middle of a cycle and so too the data
		 * phase, and we will end the transaction with half a cycle left
		 * over.
		 *
		 * Force all 8D-8D-8D flashes to use an address width of 4 to
		 * avoid this situation.
		 */
		nor->addr_width = 4;
	} else if (nor->info->addr_width) {
		nor->addr_width = nor->info->addr_width;
	} else {
		nor->addr_width = 3;
	}

	if (nor->addr_width == 3 && nor->params->size > 0x1000000) {
		/* enable 4-byte addressing if the device exceeds 16MiB */
		nor->addr_width = 4;
	}

	if (nor->addr_width > SPI_NOR_MAX_ADDR_WIDTH) {
		pr_dbg("address width is too large: %u\n",
			nor->addr_width);
		return -EINVAL;
	}

	/* Set 4byte opcodes when possible. */
	if (nor->addr_width == 4 && nor->flags & SNOR_F_4B_OPCODES &&
	    !(nor->flags & SNOR_F_HAS_4BAIT))
		spi_nor_set_4byte_opcodes(nor);

	return 0;
}

static int spi_nor_setup(struct spi_nor *nor,
			 const struct spi_nor_hwcaps *hwcaps)
{
	int ret;

	if (nor->params->setup) {
		ret = nor->params->setup(nor, hwcaps);
		if (ret)
			return ret;
	}

	return spi_nor_set_addr_width(nor);
}

static int spi_nor_init(struct spi_nor *nor)
{
	int err;

	// err = spi_nor_octal_dtr_enable(nor, true);
	// if (err) {
	// 	dev_dbg(nor->dev, "octal mode not supported\n");
	// 	return err;
	// }

	// err = spi_nor_quad_enable(nor);
	// if (err) {
	// 	dev_dbg(nor->dev, "quad mode not supported\n");
	// 	return err;
	// }

	/*
	 * Some SPI NOR flashes are write protected by default after a power-on
	 * reset cycle, in order to avoid inadvertent writes during power-up.
	 * Backward compatibility imposes to unlock the entire flash memory
	 * array at power-up by default. Depending on the kernel configuration
	 * (1) do nothing, (2) always unlock the entire flash array or (3)
	 * unlock the entire flash array only when the software write
	 * protection bits are volatile. The latter is indicated by
	 * SNOR_F_SWP_IS_VOLATILE.
	 */
	// if (IS_ENABLED(CONFIG_MTD_SPI_NOR_SWP_DISABLE) ||
	    // (IS_ENABLED(CONFIG_MTD_SPI_NOR_SWP_DISABLE_ON_VOLATILE) &&
	    //  nor->flags & SNOR_F_SWP_IS_VOLATILE))
		// spi_nor_try_unlock_all(nor);
    u8 status_reg1, status_reg2, status_reg;

	// nor->controller_ops->read_reg(nor, SPINOR_OP_RDSR, nor->bouncebuf, 1);
	// status_reg1 = nor->bouncebuf[0];
	pr_warn("before : sr : 0x%02x, cr : 0x%02x\n", status_reg1, status_reg2);

	// nor->controller_ops->read_reg(nor, SPINOR_OP_RDCR, nor->bouncebuf, 1);
	// status_reg2 = nor->bouncebuf[0];
	spi_nor_read_sr(nor, &status_reg1);
	spi_nor_read_cr(nor, &status_reg2);

	spi_nor_write_enable(nor);

	status_reg1 |= (1 << 1);
	status_reg2 &= ~(0x03);
	status_reg = (status_reg1 << 8) | status_reg2;

	spi_nor_write_sr(nor, &status_reg, 1);

	spi_nor_read_sr(nor, &status_reg1);
	spi_nor_read_cr(nor, &status_reg2);
	pr_warn("after : sr : 0x%02x, cr : 0x%02x\n", status_reg1, status_reg2);

	return 0;
}

/**
 * spi_nor_soft_reset() - Perform a software reset
 * @nor:	pointer to 'struct spi_nor'
 *
 * Performs a "Soft Reset and Enter Default Protocol Mode" sequence which resets
 * the device to its power-on-reset state. This is useful when the software has
 * made some changes to device (volatile) registers and needs to reset it before
 * shutting down, for example.
 *
 * Not every flash supports this sequence. The same set of opcodes might be used
 * for some other operation on a flash that does not support this. Support for
 * this sequence can be discovered via SFDP in the BFPT table.
 *
 * Return: 0 on success, -errno otherwise.
 */
static void spi_nor_soft_reset(struct spi_nor *nor)
{
	// struct spi_mem_op op;
	int ret;

	// op = (struct spi_mem_op)SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_SRSTEN, 0),
	// 		SPI_MEM_OP_NO_DUMMY,
	// 		SPI_MEM_OP_NO_ADDR,
	// 		SPI_MEM_OP_NO_DATA);

	// spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// ret = spi_mem_exec_op(nor->spimem, &op);
	// if (ret) {
	// 	dev_warn(nor->dev, "Software reset failed: %d\n", ret);
	// 	return;
	// }

	// op = (struct spi_mem_op)SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_SRST, 0),
	// 		SPI_MEM_OP_NO_DUMMY,
	// 		SPI_MEM_OP_NO_ADDR,
	// 		SPI_MEM_OP_NO_DATA);

	// spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	// ret = spi_mem_exec_op(nor->spimem, &op);
	// if (ret) {
	// 	pr_warn("Software reset failed: %d\n", ret);
	// 	return;
	// }

	ret = nor->controller_ops->write_reg(nor, SPINOR_OP_SRSTEN, NULL, 0);
	if (ret) {
		pr_warn("Software reset failed: %d\n", ret);
		return;
	}

	ret = nor->controller_ops->write_reg(nor, SPINOR_OP_SRST, NULL, 0);
	if (ret) {
		pr_warn("Software reset failed: %d\n", ret);
		return;
	}

	/*
	 * Software Reset is not instant, and the delay varies from flash to
	 * flash. Looking at a few flashes, most range somewhere below 100
	 * microseconds. So, sleep for a range of 200-400 us.
	 */
	vTaskDelay(150);
}

/**
 * spi_nor_manufacturer_init_params() - Initialize the flash's parameters and
 * settings based on MFR register and ->default_init() hook.
 * @nor:	pointer to a 'struct spi_nor'.
 */
// static void spi_nor_manufacturer_init_params(struct spi_nor *nor)
// {
// 	if (nor->manufacturer && nor->manufacturer->fixups &&
// 	    nor->manufacturer->fixups->default_init)
// 		nor->manufacturer->fixups->default_init(nor);

// 	if (nor->info->fixups && nor->info->fixups->default_init)
// 		nor->info->fixups->default_init(nor);
// }

/**
 * spi_nor_init_default_params() - Default initialization of flash parameters
 * and settings. Done for all flashes, regardless is they define SFDP tables
 * or not.
 * @nor:	pointer to a 'struct spi_nor'.
 */
// static void spi_nor_init_default_params(struct spi_nor *nor)
// {
// 	struct spi_nor_flash_parameter *params = nor->params;
// 	const struct flash_info *info = nor->info;
// 	struct device_node *np = spi_nor_get_flash_node(nor);

// 	params->quad_enable = spi_nor_sr2_bit1_quad_enable;
// 	params->set_4byte_addr_mode = spansion_set_4byte_addr_mode;
// 	params->setup = spi_nor_default_setup;
// 	params->otp.org = &info->otp_org;

// 	/* Default to 16-bit Write Status (01h) Command */
// 	nor->flags |= SNOR_F_HAS_16BIT_SR;

// 	/* Set SPI NOR sizes. */
// 	params->writesize = 1;
// 	params->size = (u64)info->sector_size * info->n_sectors;
// 	params->page_size = info->page_size;

// 	if (!(info->flags & SPI_NOR_NO_FR)) {
// 		/* Default to Fast Read for DT and non-DT platform devices. */
// 		params->hwcaps.mask |= SNOR_HWCAPS_READ_FAST;

// 		/* Mask out Fast Read if not requested at DT instantiation. */
// 		if (np && !of_property_read_bool(np, "m25p,fast-read"))
// 			params->hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;
// 	}

// 	/* (Fast) Read settings. */
// 	params->hwcaps.mask |= SNOR_HWCAPS_READ;
// 	spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ],
// 				  0, 0, SPINOR_OP_READ,
// 				  SNOR_PROTO_1_1_1);

// 	if (params->hwcaps.mask & SNOR_HWCAPS_READ_FAST)
// 		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_FAST],
// 					  0, 8, SPINOR_OP_READ_FAST,
// 					  SNOR_PROTO_1_1_1);
// 	/* Page Program settings. */
// 	params->hwcaps.mask |= SNOR_HWCAPS_PP;
// 	spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP],
// 				SPINOR_OP_PP, SNOR_PROTO_1_1_1);
// }

/**
 * spi_nor_init_params() - Initialize the flash's parameters and settings.
 * @nor:	pointer to a 'struct spi_nor'.
 *
 * The flash parameters and settings are initialized based on a sequence of
 * calls that are ordered by priority:
 *
 * 1/ Default flash parameters initialization. The initializations are done
 *    based on nor->info data:
 *		spi_nor_info_init_params()
 *
 * which can be overwritten by:
 * 2/ Manufacturer flash parameters initialization. The initializations are
 *    done based on MFR register, or when the decisions can not be done solely
 *    based on MFR, by using specific flash_info tweeks, ->default_init():
 *		spi_nor_manufacturer_init_params()
 *
 * which can be overwritten by:
 * 3/ SFDP flash parameters initialization. JESD216 SFDP is a standard and
 *    should be more accurate that the above.
 *		spi_nor_parse_sfdp() or spi_nor_no_sfdp_init_params()
 *
 *    Please note that there is a ->post_bfpt() fixup hook that can overwrite
 *    the flash parameters and settings immediately after parsing the Basic
 *    Flash Parameter Table.
 *    spi_nor_post_sfdp_fixups() is called after the SFDP tables are parsed.
 *    It is used to tweak various flash parameters when information provided
 *    by the SFDP tables are wrong.
 *
 * which can be overwritten by:
 * 4/ Late flash parameters initialization, used to initialize flash
 * parameters that are not declared in the JESD216 SFDP standard, or where SFDP
 * tables are not defined at all.
 *		spi_nor_late_init_params()
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_init_params(struct spi_nor *nor)
{
	int ret;

	nor->params = malloc(sizeof(*nor->params));
	if (!nor->params)
		return -ENOMEM;

	// spi_nor_init_default_params(nor);

	// if (nor->info->parse_sfdp) {
	// 	ret = spi_nor_parse_sfdp(nor);
	// 	if (ret) {
	// 		pr_err("BFPT parsing failed. Please consider using SPI_NOR_SKIP_SFDP when declaring the flash\n");
	// 		return ret;
	// 	}
	// } else if (nor->info->no_sfdp_flags & SPI_NOR_SKIP_SFDP) {
	// 	spi_nor_no_sfdp_init_params(nor);
	// } else {
	// 	spi_nor_init_params_deprecated(nor);
	// }

	// spi_nor_late_init_params(nor);

	return 0;
}

static const struct spi_nor_manufacturer *manufacturers[] = {
	&spi_nor_winbond,
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

static const struct flash_info *spi_nor_read_id(struct spi_nor *nor)
{
	const struct flash_info *info;
	u8 *id = nor->bouncebuf;
	unsigned int i;
	int ret;

	// if (nor->spimem) {
	// 	struct spi_mem_op op =
	// 		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDID, 1),
	// 			   SPI_MEM_OP_NO_ADDR,
	// 			   SPI_MEM_OP_NO_DUMMY,
	// 			   SPI_MEM_OP_DATA_IN(SPI_NOR_MAX_ID_LEN, id, 1));

	// 	ret = spi_mem_exec_op(nor->spimem, &op);
	// } else {
		ret = nor->controller_ops->read_reg(nor, SPINOR_OP_RDID, id,
						    SPI_NOR_MAX_ID_LEN);
	// }
	if (ret) {
		pr_dbg("error %d reading JEDEC ID\n", ret);
		return ERR_PTR(ret);
	}

	for (i = 0; i < ARRAY_SIZE(manufacturers); i++) {
		info = spi_nor_search_part_by_id(manufacturers[i]->parts,
						 manufacturers[i]->nparts,
						 id);
		if (info) {
			pr_err("matched -> %s <- JEDEC id bytes: %02x%02x%02xh\n",
				info->name, *id, *(id + 1), *(id + 2));
			nor->manufacturer = manufacturers[i];
			return info;
		}
	}

	pr_err("%d unrecognized JEDEC id bytes: %02x%02x%02xh\n",
		SPI_NOR_MAX_ID_LEN, *id, *(id + 1), *(id + 2));
	return ERR_PTR(-ENODEV);
}

static const struct flash_info *spi_nor_match_id(struct spi_nor *nor,
						 const char *name)
{
	unsigned int i, j;

	for (i = 0; i < ARRAY_SIZE(manufacturers); i++) {
		for (j = 0; j < manufacturers[i]->nparts; j++) {
			if (!strcmp(name, manufacturers[i]->parts[j].name)) {
				nor->manufacturer = manufacturers[i];
				return &manufacturers[i]->parts[j];
			}
		}
	}

	return NULL;
}

static const struct flash_info *spi_nor_get_flash_info(struct spi_nor *nor,
						       const char *name)
{
	const struct flash_info *info = NULL;

	if (name)
		info = spi_nor_match_id(nor, name);
	/* Try to auto-detect if chip name wasn't specified or not found */
	if (!info)
		info = spi_nor_read_id(nor);
	if (IS_ERR_OR_NULL(info))
		return ERR_PTR(-ENOENT);

	/*
	 * If caller has specified name of flash model that can normally be
	 * detected using JEDEC, let's verify it.
	 */
	if (name && info->id_len) {
		const struct flash_info *jinfo;

		jinfo = spi_nor_read_id(nor);
		if (IS_ERR(jinfo)) {
			return jinfo;
		} else if (jinfo != info) {
			/*
			 * JEDEC knows better, so overwrite platform ID. We
			 * can't trust partitions any longer, but we'll let
			 * mtd apply them anyway, since some partitions may be
			 * marked read-only, and we don't want to lose that
			 * information, even if it's not 100% accurate.
			 */
			pr_warn("found %s, expected %s\n",
				 jinfo->name, info->name);
			info = jinfo;
		}
	}

	return info;
}

static int spi_nor_check(struct spi_nor *nor)
{
	if ((!nor->controller_ops->read ||
	     !nor->controller_ops->write ||
	     !nor->controller_ops->read_reg ||
	     !nor->controller_ops->write_reg)) {
		pr_err("spi-nor: please fill all the necessary fields!\n");
		return -EINVAL;
	}

	return 0;
}

int spi_nor_scan(struct spi_nor *nor, const char *name,
		 const struct spi_nor_hwcaps *hwcaps)
{
    const struct flash_info *info;
    int ret;
    int i;

    ret = spi_nor_check(nor);
    if (ret)
        return ret;

	/*
	 * We need the bounce buffer early to read/write registers when going
	 * through the spi-mem layer (buffers have to be DMA-able).
	 * For spi-mem drivers, we'll reallocate a new buffer if
	 * nor->params->page_size turns out to be greater than PAGE_SIZE (which
	 * shouldn't happen before long since NOR pages are usually less
	 * than 1KB) after spi_nor_scan() returns.
	 */
	nor->bouncebuf_size = (_AC(1,UL) << 8);
	nor->bouncebuf = malloc(nor->bouncebuf_size);
	if (!nor->bouncebuf)
        return -ENOMEM;

    info = spi_nor_get_flash_info(nor, name);
    if (IS_ERR(info))
        return PTR_ERR(info);

    nor->info = info;

    // mutex_init(&nor->lock);

    /* Init flash parameters based on flash_info struct and SFDP */
    // ret = spi_nor_init_params(nor);
    // if (ret)
    //     return ret;

	// ret = spi_nor_setup(nor, hwcaps);
	// if (ret)
	// 	return ret;

	/* Send all the required SPI flash commands to initialize device */
	ret = spi_nor_init(nor);
	if (ret)
		return ret;
}

extern const struct spi_nor_controller_ops rpi_spi_controller_ops;

static DEVICE_INITCALL(spi_nor_probe)
{
	/*
	 * Enable all caps by default. The core will mask them after
	 * checking what's really supported using spi_mem_supports_op().
	 */
	const struct spi_nor_hwcaps hwcaps = { .mask = SNOR_HWCAPS_ALL };
    char *flash_name;
    int ret;

    nor = (struct spi_nor *)malloc(sizeof(*nor));
    if (!nor)
        return -ENOMEM;

	nor->controller_ops = &rpi_spi_controller_ops;

    ret = spi_nor_scan(nor, flash_name, &hwcaps);
    if (ret)
        return ret;

}
