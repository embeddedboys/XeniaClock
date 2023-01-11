#include <stdio.h>

#include "../common/module.h"

module_init(ft6x36_init);
module_exit(ft6x36_exit);

static int ft6x36_init(void)
{
    printf("%s, %d\n", __func__, __LINE__);
    return 0;
}

static void ft6x36_exit(void)
{
    printf("%s, %d\n", __func__, __LINE__);
}


int main(int argc, char **argv)
{
    printf("YEEEEEEEEEEEEEEE!\n");
    return 0;
}