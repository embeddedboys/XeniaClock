/**
 * @file native_spi.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-06
 *
 * MIT License
 *
 * Copyright 2023 embeddedboys(writeforever@foxmail.com)
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

#include <string.h>
#include <linux/init.h>
#include <linux/module.h>

#include "FreeRTOS.h"
#include "spi/nrf24l01.h"

#define DRV_NAME "nrf24l01: "
#define NRF24L01_CLK_FREQ       20000000 // 20MHz

struct nrf24l01_priv {
    spi_inst_t *spi;
    
    struct {
        u8 cs;
        u8 ce;
        u8 intr;
    } gpio;
    
    u8 tx_address[TX_ADR_WIDTH];
    u8 rx_address[RX_ADR_WIDTH];
    
    u8 tx_buf[TX_PLOAD_WIDTH];
    u8 rx_buf[RX_PLOAD_WIDTH];
    u8 rx_ack_num;
};

struct nrf24l01_priv g_nrf_priv;

static u8 nrf24l01_write_reg(struct nrf24l01_priv *priv, u8 reg, u8 val)
{
    spi_write16(reg << 8 | val, priv->gpio.cs);
}
#define write_reg(priv, reg, val) nrf24l01_write_reg(priv, reg, val)

static u8 nrf24l01_read_reg(struct nrf24l01_priv *priv, u8 reg)
{
    return spi_r8w8(reg, priv->gpio.cs);
}
#define read_reg(priv, reg) nrf24l01_read_reg(priv, reg)

static void nrf24l01_spi_write_addr(struct nrf24l01_priv *priv, u8 addr, u8 *data,
                                    size_t len)
{
    cs_select(priv->gpio.cs);
    spi_write_blocking(priv->spi, &addr, 1);
    spi_write_blocking(priv->spi, data, len);
    cs_deselect(priv->gpio.cs);
}

static void nrf24l01_spi_read_addr(struct nrf24l01_priv *priv, u8 addr, u8 *data,
                                   size_t len)
{
    cs_select(priv->gpio.cs);
    spi_write_blocking(priv->spi, &addr, 1);
    spi_read_blocking(priv->spi, 0xff, data, len);
    cs_deselect(priv->gpio.cs);
}

static void nrf24l01_hw_init(struct nrf24l01_priv *priv)
{
    u8 default_tx_address[TX_ADR_WIDTH] = {0x13, 0x14, 0x52, 0x05, 0x20};
    u8 default_rx_address[RX_ADR_WIDTH] = {0x13, 0x14, 0x52, 0x05, 0x21};
    
    memcpy(priv->rx_address, default_rx_address, RX_ADR_WIDTH);
    memcpy(priv->tx_address, default_tx_address, TX_ADR_WIDTH);
    
    printk(DRV_NAME "setting default address\n");
    
    gpio_put(priv->gpio.ce, 0);
    
    write_reg(priv, NRF_WRITE_REG + EN_AA, 0x01);
    write_reg(priv, NRF_WRITE_REG + EN_RXADDR, 0x01);
    write_reg(priv, NRF_WRITE_REG + SETUP_RETR, 0x1a);
    write_reg(priv, NRF_WRITE_REG + RF_CH, 0x05);
    write_reg(priv, NRF_WRITE_REG + RF_SETUP, 0x0f);
    
    gpio_put(priv->gpio.ce, 1);
    printk(DRV_NAME "hardware initialized :p\n");
}

#define ID_VAL 0xa5
#define ID_LEN 5
static int do_check(struct nrf24l01_priv *priv)
{
    u8 txdata[] = {ID_VAL, ID_VAL, ID_VAL, ID_VAL, ID_VAL};
    u8 rxbuf[ID_LEN] = {0};
    int i;

    nrf24l01_spi_write_addr(priv, NRF_WRITE_REG + TX_ADDR, txdata, sizeof(txdata));
    nrf24l01_spi_read_addr(priv, TX_ADDR, rxbuf, sizeof(rxbuf));
    
    for (i = 0; i < ID_LEN; i++) {
        printk(DRV_NAME "rxbuf[%d] = 0x%x\n", i, rxbuf[i]);
        if (rxbuf[i] != ID_VAL)
            break;
    }
    if (i != ID_LEN) {
        return -1;
    }

    return 0;
}
static int nrf24l01_check(struct nrf24l01_priv *priv, u8 retry)
{

    while (retry--) {
        if (do_check(priv))
            printk("%s failed, retry : %d\n", __func__, retry);
        else
            break;
    }

    printk(DRV_NAME "check passed!\n");
}

static int __init nrf24l01_drv_init(void)
{
    int ret;
    printk("%s\n", __func__);
    
    g_nrf_priv.gpio.ce = 23;
    g_nrf_priv.gpio.cs = 17;
    g_nrf_priv.gpio.intr = 24;
    
    g_nrf_priv.spi = spi_default;
    
    // nrf24l01_hw_init(&g_nrf_priv);
    ret = nrf24l01_check(&g_nrf_priv, 1);
    if (ret) {
        printk(DRV_NAME "All check failed!, will do the clean job.\n");
        goto exit;
    }
    
    return 0;
    
exit:
    return -1;
}

static void __exit nrf24l01_drv_exit(void)
{
    printk("%s\n", __func__);
}

module_init(nrf24l01_drv_init);
module_exit(nrf24l01_drv_exit);
