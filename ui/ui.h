// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0 Beta1
// LVGL VERSION: 8.2
// PROJECT: epink_desktop

#ifndef _EPINK_DESKTOP_UI_H
#define _EPINK_DESKTOP_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_ScreenEpinkHome;
extern lv_obj_t * ui_PanelWidgets;
extern lv_obj_t * ui_RollerHour;
extern lv_obj_t * ui_RollerMinute;
extern lv_obj_t * ui_RollerSecond;
extern lv_obj_t * ui_LabelSplit1;
extern lv_obj_t * ui_LabelSplit2;
extern lv_obj_t * ui_ImageLine;
extern lv_obj_t * ui_ImageLine2;
extern lv_obj_t * ui_LabelHumidity;
extern lv_obj_t * ui_LabelTemperture;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_Image5;
extern lv_obj_t * ui_LabelTips;
extern lv_obj_t * ui_LabelTest;
extern lv_obj_t * ui_PanelStatusBar;
extern lv_obj_t * ui_LabelGreeting;
extern lv_obj_t * ui_ScreenEpinkConfig;
extern lv_obj_t * ui_PanelStatusBarConfig;
extern lv_obj_t * ui_PanelWidgetsConfig;
extern lv_obj_t * ui_LabelWifiName;
extern lv_obj_t * ui_ScreenSleep;
extern lv_obj_t * ui_ImageSleep;
extern lv_obj_t * ui_ScreenEpinkApps;
extern lv_obj_t * ui_PanelStatusBar1;
extern lv_obj_t * ui_ButtonApp1;
extern lv_obj_t * ui_LabelApp1;
extern lv_obj_t * ui_ButtonApp2;
extern lv_obj_t * ui_LabelApp2;
extern lv_obj_t * ui_ButtonApp3;
extern lv_obj_t * ui_LabelApp3;
extern lv_obj_t * ui_ButtonApp4;
extern lv_obj_t * ui_LabelApp4;


LV_IMG_DECLARE(ui_img_line_180_1_png);    // assets/line_180_1.png
LV_IMG_DECLARE(ui_img_humidity_png);    // assets/humidity.png
LV_IMG_DECLARE(ui_img_tempture_png);    // assets/tempture.png
LV_IMG_DECLARE(ui_img_884727455);    // assets/Clock-Tower-160x200.png


LV_FONT_DECLARE(ui_font_FiraCodeBold12);
LV_FONT_DECLARE(ui_font_FiraCodeSemiBold12);
LV_FONT_DECLARE(ui_font_FiraCodeSemiBold40);
LV_FONT_DECLARE(ui_font_NeverMindHandBold14);
LV_FONT_DECLARE(ui_font_NeverMindSemiSerifBold12);
LV_FONT_DECLARE(ui_font_NeverMindSemiSerifBold20);
LV_FONT_DECLARE(ui_font_NeverMindSemiSerifBold40);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
