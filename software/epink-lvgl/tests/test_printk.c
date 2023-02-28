#include <stdio.h>
#include <lib/printk.h>
#include <common/init.h>

static SUBSYS_INITCALL(native_i2c_init)
{
    pr_warn("%s, initializing\n", __func__);
}

static SUBSYS_INITCALL(native_spi_init)
{
    pr_debug("%s, initializing\n", __func__);
}


int main()
{
    // printk_late_init();

    pr_err("hhhhhhh\n");

    pr_info("hello %s\n", "peter");

    dump_kmsg(true);

    return 0;
}
