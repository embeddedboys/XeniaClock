/**
 * @file lv_port_disp_linux.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#include "video/epd.h"
#include "common/tools.h"
#include "video/ssd1306.h"
#include "src/hal/lv_hal_disp.h"
#if 1

/*********************
 *      INCLUDES
 *********************/

#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "video/epd.h"
#include "video/ssd1306.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
#if 0
union rgb888 {
    uint8_t data[0];
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } channel;
};
#endif

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);
static void disp_exit(void);
static void main_screen_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                                   lv_color_t *color_p);
static void main_screen_set_pix_cb(lv_disp_drv_t *disp_drv, uint8_t *buf,
                                   lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

static void sub_screen_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                                  lv_color_t *color_p);
static void sub_screen_set_pix_cb(lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w,
                                  lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
/**********************
 *  STATIC VARIABLES
 **********************/
extern uint8_t epink_disp_buffer[EPINK_DISP_BUFFER_SIZE];
uint8_t *pen = epink_disp_buffer;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
extern void epink_buffer_clear();
extern void epink_flush();

lv_disp_t *g_default_disp = NULL;
static struct display_module *g_sub_disp_m = NULL;

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();
    
    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/
    
    /**
     * LVGL requires a buffer where it internally draws the widgets.
     * Later this buffer will passed to your display driver's `flush_cb` to copy its content to your display.
     * The buffer has to be greater than 1 display row
     *
     * There are 3 buffering configurations:
     * 1. Create ONE buffer:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Double buffering
     *      Set 2 screens sized buffers and set disp_drv.full_refresh = 1.
     *      This way LVGL will always provide the whole rendered screen in `flush_cb`
     *      and you only need to change the frame buffer's address.
     */
    
    /* Example for 1) */
    // static lv_disp_draw_buf_t draw_buf_dsc_1;
    // static lv_color_t buf_1[MY_DISP_HOR_RES * MY_DISP_VER_RES / 8];                          /*A buffer for 10 rows*/
    // lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * MY_DISP_VER_RES / 8);   /*Initialize the display buffer*/
    
    /* Example for 2) */
    // static lv_disp_draw_buf_t draw_buf_dsc_2;
    // static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];                        /*A buffer for 10 rows*/
    // static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];                        /*An other buffer for 10 rows*/
    // lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/
    
    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
    static lv_disp_draw_buf_t draw_buf_dsc_3;
    static lv_color_t buf_3_1[MY_DISP_HOR_RES *
                                              MY_DISP_VER_RES];            /*A screen sized buffer*/
    static lv_color_t buf_3_2[MY_DISP_HOR_RES *
                                              MY_DISP_VER_RES];            /*Another screen sized buffer*/
    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2,
                          MY_DISP_HOR_RES * MY_DISP_VER_RES);   /*Initialize the display buffer*/
                          
    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/
    
    static lv_disp_drv_t disp_drv;                  /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/
    
    /*Set up the functions to access to your display*/
    
    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
    
    /*Used to copy the buffer's content to the display*/
    disp_drv.set_px_cb = main_screen_set_pix_cb;
    disp_drv.flush_cb = main_screen_disp_flush;
    
    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_3;
    
    /*Required for Example 3)*/
    disp_drv.full_refresh = 1;
    
    // disp_drv.sw_rotate = 1;
    
    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;
    
    /*Finally register the driver*/
    g_default_disp = lv_disp_drv_register(&disp_drv);
    
    // lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    /* set a mono theme */
    // lv_theme_t *th = lv_theme_mono_init(disp, 1, &lv_font_montserrat_10);
    // lv_disp_set_theme(disp, th);
}

void post_lv_port_disp_init()
{
    static lv_disp_draw_buf_t draw_buf_dsc_sub_screen;
    static lv_color_t buf_sub_screen_1[SSD1306_HOR_RES_MAX *
                                                           SSD1306_VER_RES_MAX];            /*A screen sized buffer*/
    static lv_color_t buf_sub_screen_2[SSD1306_HOR_RES_MAX *
                                                           SSD1306_VER_RES_MAX];            /*Another screen sized buffer*/
    lv_disp_draw_buf_init(&draw_buf_dsc_sub_screen, buf_sub_screen_1, buf_sub_screen_2,
                          SSD1306_HOR_RES_MAX * SSD1306_VER_RES_MAX);   /*Initialize the display buffer*/
                          
    /* register sub screen driver */
    static lv_disp_drv_t sub_disp_drv;
    lv_disp_drv_init(&sub_disp_drv);
    
    sub_disp_drv.hor_res = SSD1306_HOR_RES_MAX;
    sub_disp_drv.ver_res = SSD1306_VER_RES_MAX;
    
    sub_disp_drv.set_px_cb = sub_screen_set_pix_cb;
    sub_disp_drv.flush_cb = sub_screen_disp_flush;
    
    sub_disp_drv.draw_buf = &draw_buf_dsc_sub_screen;
    // sub_disp_drv.full_refresh = 1;
    
    lv_disp_t *sub_disp = lv_disp_drv_register(&sub_disp_drv);
    
    /* set default disp */
    lv_disp_set_default(g_default_disp);
    
    g_sub_disp_m->ops.module_init(EPINK_UPDATE_MODE_PART);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    pr_debug("initializing display ...\n");
    default_display_module_init();
    
    /* initlize sub screen */
    g_sub_disp_m = request_disp_module("ssd1306");
    if (!g_sub_disp_m) {
        pr_debug("failed to request sub display module!\n");
        return;
    }
    
    //g_sub_disp_m->ops.module_init(EPINK_UPDATE_MODE_FULL);
}

static void disp_exit(void)
{
    /*You code here*/
}

static void main_screen_set_pix_cb(lv_disp_drv_t *disp_drv, uint8_t *buf,
                                   lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    // int page,page_left;
    // uint8_t *pen = epink_disp_buffer;
    // page = x / 8;
    /* The page_left is the bit we need to set to page, will use later */
    // page_left = ( x % 8 == 0 ) ? 0 : x % 8;
    
    // if(lv_color_brightness(color) < 128) {
    //     pen[y * 25 + page] &= ~( 1 << ( 7 - page_left ) );
    // }
    // else {
    //     pen[y * 25 + page] |= ( 1 << ( 7 - page_left ) );
    // }
    
    if (lv_color_brightness(color) < 128) {
        epink_draw_pixel(x, y, 0xffff);
    } else {
        epink_draw_pixel(x, y, 0x00);
    }
}

static void sub_screen_set_pix_cb(lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w,
                                  lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    if (lv_color_brightness(color) < 128) {
        g_sub_disp_m->ops.module_put_pixel(x, y, 1);
    } else {
        g_sub_disp_m->ops.module_put_pixel(x, y, 0);
    }
}

static void main_screen_disp_flush_part(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                                        lv_color_t *color_p)
{
    /* 1. save pixel to disp buffer */
    
    /* 2. flush the given area to panel
     * note: the ssd1681 like IC write in byte,
     * you need to convert pixels into byte */
    
    /* 3. before write to RAM, checkout if the area->x1,x2
     * align in byte? if not, we need to read the left bits
     * from disp buffer and fill the broken byte */
    
    /* 4. write to RAM and call part refresh */
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void main_screen_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                                   lv_color_t *color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    // int ret;
    // int x, y;
    
    // for( y = area->y1; y < area->y2; y++ ) {
    //     for( x = area->x1; x < area->x2; x++ ) {
    //         epink_draw_pixel(x, y, color_p++->full);
    //         pixel_count++;
    //         // LV_LOG_WARN("pixel colorp val :%d", color_p->full);
    //         // if(color_p->full)
    //         //     printf("1");
    //         // else
    //         //     printf("0");
    //     }
    //     // printf("\n");
    // }
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("pixel count:%d\n", pixel_count);
    // pixel_count=0;
    
    epink_flush();
    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

static void sub_screen_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                                  lv_color_t *color_p)
{
    g_sub_disp_m->ops.module_flush();
    
    lv_disp_flush_ready(disp_drv);
}

/*OPTIONAL: GPU INTERFACE*/

/*If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color*/
// static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                    const lv_area_t * fill_area, lv_color_t color)
// {
//    /*It's an example code which should be done by your GPU*/
//    int32_t x, y;
//    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/

//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        for(x = fill_area->x1; x <= fill_area->x2; x++) {
//            dest_buf[x] = color;
//        }
//        dest_buf+=dest_width;    /*Go to the next line*/
//    }
// }

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
