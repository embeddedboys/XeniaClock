#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../common/list.h"

struct kv_node {
    char k[24];
    char v[24];

    struct list_head head;
};

struct esp01s_response_args {
    int argc;
    struct kv_node kv;
};

static struct esp01s_response_args g_args;

static void free_args(struct kv_node *p_kv)
{
    struct list_head *pos, *q;
    struct kv_node *tmp;
    
    list_for_each_safe(pos, q, &p_kv->head){
        tmp = list_entry(pos, struct kv_node, head);
        list_del(pos);
        printf("freeing node : %p\n", tmp);
        free(tmp);
    }
}

int main(int argc, char **argv)
{
    char ipd[] = "IPD,0,530:GET /?ssid=KYKJ&psk=keyifamily HTTP/1.1";
    char kv_buf[128];
    int kv_len;
    
    INIT_LIST_HEAD(&g_args.kv.head);
    
    char *p_str = strchr(ipd, '?');
    char *p_str_cursor = (p_str + 1);
    while(*p_str_cursor++ != ' ')
        kv_len++;
    
    strncpy(kv_buf, (p_str + 1), kv_len);
    printf("%s\n", kv_buf);
    
    char *token, *str;
    for (str = kv_buf;; str = NULL) {
        token = strtok(str, "&");
        if (token == NULL)
            break;
        printf("------ %s\n", token);
        
        struct kv_node *kv = (struct kv_node *)malloc(sizeof(struct kv_node));
        
        char *p_str = strchr(token, '=');
        strcpy(kv->v, (p_str+1));
        printf("%p %p \n", token, p_str);
        strncpy(kv->k, token, (p_str - token));
        
        list_add_tail(&kv->head, &g_args.kv.head);
    }
    
    struct kv_node *cursor;
    list_for_each_entry(cursor, &g_args.kv.head, head) {
        printf("%p, k : %s v : %s\n", cursor, cursor->k, cursor->v);
    }
    
    free_args(&g_args.kv);
}