#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>

#define EPINK_WIDTH 200
#define EPINK_HEIGHT 200

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static uint8_t epink_disp_buffer[EPINK_WIDTH * EPINK_HEIGHT / 8] = {0};

static const char *g_tips[] = {
    "Learn to pause.",
    "Don't Worry, Be Happy.",
    "Gah!",
};
static uint8_t tips_index = 0;

#define ESP8266_CMD_SUFFIX          "\r\n"
#define ESP8266_CMD(cmd)            cmd ESP8266_CMD_SUFFIX
#define ESP8266_CMD_AT              ESP8266_CMD("AT")
#define ESP8266_CMD_AT_GMR          ESP8266_CMD("AT+GMR")
#define ESP8266_CMD_AT_CWMODE(m)    ESP8266_CMD("AT+CWMODE="#m)
#define ESP8266_CMD_AT_CWJAP(ssid, psk)     ESP8266_CMD("AT+CWJAP=" #ssid "," #psk)
#define ESP8266_CMD_AT_CWSAP(ssid, psk, chn, ecn)  ESP8266_CMD("AT+CWSAP=" #ssid "," #psk "," #chn "," #ecn)

struct esp01s_connection {
    uint32_t id;
    char *type;
    char *addr;
    uint32_t remote_port;
    uint32_t local_port;
    uint32_t tetype;

    struct esp01s_connection *p_next;
};

int main(int argc, char **argv)
{
    int fd;
    int mode = 1;

    if (1) {
        printf("1 is okay\n");
    }

    if (-1) {
        printf("-1 is okay\n");
    }
    
    if (0) {
        printf("0 is okay\n");
    }
    // fd = open("/dev/urandom", O_RDONLY);

    // read(fd, epink_disp_buffer, ARRAY_SIZE(epink_disp_buffer));

    // for(int i=0;i<ARRAY_SIZE(epink_disp_buffer);i++){
    //     printf("%x ", epink_disp_buffer[i]);
    // }
    // printf("\n");
    // printf("%d\n", getpriority(PRIO_PROCESS, 0));
    // setpriority(PRIO_PROCESS, 0, -20);
    // printf("%d\n", getpriority(PRIO_PROCESS, 0));
    // while(1);
    printf("%s", ESP8266_CMD_AT_CWMODE(mode));
    printf("%s", ESP8266_CMD_AT_CWJAP("mywifi", "12345678"));
    printf("%s", ESP8266_CMD_AT_CWSAP("mywifi", "12345678", 5, 3));

    char* buffer = "Hello";
    char store_value[10];
    int total_read;

    total_read = sscanf(buffer, "%s" , store_value);

    printf("Value in buffer: %s",store_value);
    printf("\nTotal items read: %d\n",total_read);

    char sample[] = "STATUS:3\r\n+CIPSTATUS:5,\"TCP\",\"192.168.4.2\",3195,80,1\r\n+CTPSTATUS:1,\"TCP\",\"192.168.4.3\",3792,80,1\r\n";
    char *token, *str1, *saveptr1;
    int len;

    uint8_t passed = 1;
    for(str1=sample, len=0;;str1=NULL) {
        token = strtok(str1, "+");
        if (token == NULL)
            break;
        if (passed) {
            passed-=1;
            continue;
        }
        printf("%s", token);
        len++;
        char *id = strtok(NULL, ",");
        printf("%s\n", id);
        // int id,remote_port,local_port,tetype;
        // char type[20], addr[20];
        // sscanf(token, "CIPSTATUS:%d,%s,%s,%d,%d,%d\r\n", &id, type, addr,&remote_port,&local_port,&tetype);
        // printf("id : %d\n", id);
        // printf("type : %s\n", type);
        // printf("addr : %s\n", addr);
        // printf("remote_port : %d\n", remote_port);
        // printf("local_port : %d\n", local_port);
        // printf("tetype : %d\n", tetype);
        // struct esp01s_connection *conn = (struct esp01s_connection *) \
        //                                 malloc(sizeof(struct esp01s_connection));
        // sscanf(token, "CIPSTATUS:%d,\"%s\",\"%s\",%d,%d,%d\r\n",
        //                 &conn->id,
        //                 conn->type,
        //                 conn->addr,
        //                 &conn->remote_port,
        //                 &conn->local_port,
        //                 &conn->tetype);
        // printf("id : %d\n", conn->id);
        // printf("type : %s\n", conn->type);
        // printf("addr : %s\n", conn->addr);
        // printf("remote_port : %d\n", conn->remote_port);
        // printf("local_port : %d\n", conn->local_port);
        // printf("tetype : %d\n", conn->tetype);
    }
    printf("length : %d\n", len);

    // printf("%s", sample);
    int status, id, port, tetype;
    char *type;
    char *ip;

    // sscanf(token, "CIPSTATUS:%d,\"%s\",\"%s\",%d,%d,%d",
    //                 &conn->id,
    //                 conn->type,
    //                 conn->addr,
    //                 &conn->remote_port,
    //                 &conn->local_port,
    //                 &conn->tetype);
    // sscanf(sample, "STATUS:%d\r\n+CIPSTATUS:%d", &status,&id);
    // printf("status : %d\n", status);
    printf("long : %d\n", sizeof(long));
    return 0;
}
