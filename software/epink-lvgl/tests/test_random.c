#include <stdint.h>
#include <stdio.h>
#include <string.h>
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

int main(int argc, char **argv)
{
    int fd;
    int mode = 1;
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
    return 0;
}