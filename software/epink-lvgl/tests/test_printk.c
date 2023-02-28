#include <stdio.h>
#include <lib/printk.h>
#include <common/init.h>

static SUBSYS_INITCALL(native_i2c_init)
{
    printk("%s, initializing\n", __func__);
}

static SUBSYS_INITCALL(native_spi_init)
{
    printk("%s, initializing\n", __func__);
}


int main()
{
    // printk_late_init();

    printk("hhhhhhh\n");

    printk("hello %s\n", "peter");

    dump_kmsg(true);

    return 0;
}
