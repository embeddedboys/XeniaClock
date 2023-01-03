#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "common/list.h"
#include "common/tools.h"
#include "display/epd.h"
#include "display/display_manager.h"

static struct display_module *g_pt_disp_module = NULL;
static uint32_t g_module_id = 0;

/* TODO: replace these lists with kernel list_head */

#if 1
int register_module(struct display_module *module)
{
    struct display_module *p_tmp;
    
    if (!module) {
        return -1;
    }
    
    pr_debug("register module: %s\n", module->name);
    
    if (!g_pt_disp_module) {
        pr_debug("first handler\n");
        g_pt_disp_module = module;  /* first node */
    } else {
        p_tmp = g_pt_disp_module;
        while (p_tmp->p_next) {
            p_tmp = p_tmp->p_next;
        }
        p_tmp->p_next = module;
    }
    module->id = g_module_id++;
    module->p_next = NULL;
    
    return 0;
}

struct display_module *request_disp_module(char *name)
{
    struct display_module *p_tmp = g_pt_disp_module;
    
    while (p_tmp) {
        if (0 == strcmp(p_tmp->name, name)) {
            pr_debug("%s display module matched!\n", p_tmp->name);
            return p_tmp;
        }
        p_tmp = p_tmp->p_next;
    }
    
    return NULL;
}
#else
int register_module(struct display_module *module)
{
    if (!module)
        return -1;

    if (!g_pt_disp_module) {
        g_pt_disp_module = (struct display_module *)malloc(sizeof(struct display_module));
    }

    list_add_tail(&module->head, &g_pt_disp_module->head);

    return 0;
}

struct display_module *request_disp_module(char *name)
{
    struct display_module *pos;

    list_for_each_entry(pos, &g_pt_disp_module->head, head) {
        pr_debug("%s\n", pos->name);
        if (0 == strcmp(pos->name, name)) {
            return pos;
        }
    }

    return NULL;
}
#endif
// void disp_modules_init(void)
// {
//     struct display_module *p_tmp = g_pt_disp_module;
    
//     if (!p_tmp) {
//         pr_debug("no handler\n");
//         return;
//     }
    
//     if (!p_tmp->p_next && p_tmp->ops.module_init) {
//         pr_debug("only one handler, calling it's init func\n");
//         p_tmp->ops.module_init(DEFAULT_EPINK_UPDATE_MODE);
//         return;
//     }
    
//     pr_debug("more than one handler, calling all init func\n");
//     while (p_tmp) {
//         pr_debug("init handler %s, id: %d\n", p_tmp->name, p_tmp->id);
//         if (p_tmp->ops.module_init && p_tmp->ops.module_init(DEFAULT_EPINK_UPDATE_MODE)) {
//             pr_debug("init handler %s failed\n", p_tmp->name);
//             return;
//         }
//         p_tmp = p_tmp->p_next;
//     }
// }

void default_display_module_init(void)
{
    char module_name[] = DEFAULT_DISPLAY_MAIN_PANEL_NAME;
    
    pr_debug("requesting display module : %s\n", module_name);
    struct display_module *p_disp_m = request_disp_module(module_name);
    
    if (!p_disp_m) {
        pr_debug("request default module failed!\n");
        return;
    } else {
        pr_debug("default module %s successfully requested!\n", module_name);
        default_module = *p_disp_m;
    }
    
    /* a global reflush for E-paper is required */
    default_module.ops.module_blank();
}