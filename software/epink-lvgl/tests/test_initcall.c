#include <stdio.h>

#include "../common/module.h"
#include "../common/bitops.h"

static int ft6x36_init(void)
{
    printf("%s, %d\n", __func__, __LINE__);
    return 0;
}

static void ft6x36_exit(void)
{
    printf("%s, %d\n", __func__, __LINE__);
}

module_init(ft6x36_init);
module_exit(ft6x36_exit);

// #define GENMASK(h, l) \
	// (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))
#define BITS_PER_LONG 64
int main(int argc, char **argv)
{
    printf("YEEEEEEEEEEEEEEE!\n");
    printf("%lx\n", (((~0UL) - (1UL << (0)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (2)))));
    printf("%lx\n", (((~0UL) - (1UL << (0)) + 1)));
    printf("%lx\n", ((~0UL >> (BITS_PER_LONG - 1 - (2)))));
    printf("%lx\n", (0x80 & GENMASK(7,6)) >> 6);
    return 0;
}