// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0 Beta1
// LVGL VERSION: 8.2
// PROJECT: epink_desktop

#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_ScreenEpinkHome;
lv_obj_t * ui_PanelWidgets;
lv_obj_t * ui_RollerHour;
lv_obj_t * ui_RollerMinute;
lv_obj_t * ui_RollerSecond;
lv_obj_t * ui_LabelSplit1;
lv_obj_t * ui_LabelSplit2;
lv_obj_t * ui_ImageLine;
lv_obj_t * ui_ImageLine2;
lv_obj_t * ui_LabelHumidity;
lv_obj_t * ui_LabelTemperture;
lv_obj_t * ui_Image4;
lv_obj_t * ui_Image5;
lv_obj_t * ui_LabelTips;
lv_obj_t * ui_LabelTest;
lv_obj_t * ui_PanelStatusBar;
lv_obj_t * ui_LabelGreeting;
lv_obj_t * ui_ScreenEpinkConfig;
lv_obj_t * ui_PanelStatusBarConfig;
lv_obj_t * ui_PanelWidgetsConfig;
lv_obj_t * ui_LabelWifiName;
lv_obj_t * ui_ScreenSleep;
lv_obj_t * ui_ImageSleep;
lv_obj_t * ui_ScreenEpinkApps;
lv_obj_t * ui_PanelStatusBar1;
lv_obj_t * ui_ButtonApp1;
lv_obj_t * ui_ButtonApp2;
lv_obj_t * ui_ButtonApp3;
lv_obj_t * ui_ButtonApp4;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 8
    #error "LV_COLOR_DEPTH should be 8bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_ScreenEpinkHome_screen_init(void)
{
    ui_ScreenEpinkHome = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenEpinkHome, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PanelWidgets = lv_obj_create(ui_ScreenEpinkHome);
    lv_obj_set_width(ui_PanelWidgets, 200);
    lv_obj_set_height(ui_PanelWidgets, 160);
    lv_obj_set_x(ui_PanelWidgets, 0);
    lv_obj_set_y(ui_PanelWidgets, 15);
    lv_obj_set_align(ui_PanelWidgets, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelWidgets, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_RollerHour = lv_roller_create(ui_PanelWidgets);
    lv_roller_set_options(ui_RollerHour,
                          "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerHour, 46);
    lv_obj_set_width(ui_RollerHour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerHour, 5);
    lv_obj_set_y(ui_RollerHour, 0);
    lv_obj_set_align(ui_RollerHour, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_color(ui_RollerHour, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerHour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerHour, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerHour, &ui_font_FiraCodeSemiBold40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerHour, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerHour, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerHour, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerHour, &ui_font_FiraCodeSemiBold40, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerHour, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerHour, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_RollerMinute = lv_roller_create(ui_PanelWidgets);
    lv_roller_set_options(ui_RollerMinute,
                          "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerMinute, 46);
    lv_obj_set_width(ui_RollerMinute, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_RollerMinute, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerMinute, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerMinute, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerMinute, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerMinute, &ui_font_FiraCodeSemiBold40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerMinute, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerMinute, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerMinute, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerMinute, &ui_font_FiraCodeSemiBold40, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerMinute, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerMinute, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_RollerSecond = lv_roller_create(ui_PanelWidgets);
    lv_roller_set_options(ui_RollerSecond,
                          "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerSecond, 46);
    lv_obj_set_width(ui_RollerSecond, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerSecond, -5);
    lv_obj_set_y(ui_RollerSecond, 0);
    lv_obj_set_align(ui_RollerSecond, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_color(ui_RollerSecond, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSecond, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerSecond, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerSecond, &ui_font_FiraCodeSemiBold40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerSecond, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSecond, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_RollerSecond, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerSecond, &ui_font_FiraCodeSemiBold40, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerSecond, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerSecond, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_LabelSplit1 = lv_label_create(ui_PanelWidgets);
    lv_obj_set_width(ui_LabelSplit1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSplit1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelSplit1, -33);
    lv_obj_set_y(ui_LabelSplit1, -3);
    lv_obj_set_align(ui_LabelSplit1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSplit1, ":");
    lv_obj_set_style_text_color(ui_LabelSplit1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSplit1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelSplit1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSplit1, &ui_font_FiraCodeSemiBold40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSplit2 = lv_label_create(ui_PanelWidgets);
    lv_obj_set_width(ui_LabelSplit2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSplit2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelSplit2, 32);
    lv_obj_set_y(ui_LabelSplit2, -3);
    lv_obj_set_align(ui_LabelSplit2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSplit2, ":");
    lv_obj_set_style_text_color(ui_LabelSplit2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSplit2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelSplit2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSplit2, &ui_font_FiraCodeSemiBold40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageLine = lv_img_create(ui_PanelWidgets);
    lv_img_set_src(ui_ImageLine, &ui_img_line_180_1_png);
    lv_obj_set_width(ui_ImageLine, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImageLine, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImageLine, 0);
    lv_obj_set_y(ui_ImageLine, -30);
    lv_obj_set_align(ui_ImageLine, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageLine, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImageLine, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ImageLine2 = lv_img_create(ui_PanelWidgets);
    lv_img_set_src(ui_ImageLine2, &ui_img_line_180_1_png);
    lv_obj_set_width(ui_ImageLine2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImageLine2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImageLine2, 0);
    lv_obj_set_y(ui_ImageLine2, 25);
    lv_obj_set_align(ui_ImageLine2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageLine2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImageLine2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelHumidity = lv_label_create(ui_PanelWidgets);
    lv_obj_set_width(ui_LabelHumidity, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelHumidity, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelHumidity, -45);
    lv_obj_set_y(ui_LabelHumidity, -50);
    lv_obj_set_align(ui_LabelHumidity, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelHumidity, "40%");
    lv_obj_set_style_text_color(ui_LabelHumidity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelHumidity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHumidity, &ui_font_NeverMindSemiSerifBold20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelTemperture = lv_label_create(ui_PanelWidgets);
    lv_obj_set_width(ui_LabelTemperture, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTemperture, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTemperture, 60);
    lv_obj_set_y(ui_LabelTemperture, -50);
    lv_obj_set_align(ui_LabelTemperture, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTemperture, "25*C");
    lv_obj_set_style_text_color(ui_LabelTemperture, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTemperture, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTemperture, &ui_font_NeverMindSemiSerifBold20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image4 = lv_img_create(ui_ScreenEpinkHome);
    lv_img_set_src(ui_Image4, &ui_img_humidity_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image4, -80);
    lv_obj_set_y(ui_Image4, -37);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image5 = lv_img_create(ui_ScreenEpinkHome);
    lv_img_set_src(ui_Image5, &ui_img_tempture_png);
    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image5, 24);
    lv_obj_set_y(ui_Image5, -36);
    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelTips = lv_label_create(ui_ScreenEpinkHome);
    lv_obj_set_width(ui_LabelTips, 200);
    lv_obj_set_height(ui_LabelTips, 30);
    lv_obj_set_x(ui_LabelTips, 0);
    lv_obj_set_y(ui_LabelTips, 80);
    lv_obj_set_align(ui_LabelTips, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_LabelTips, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_LabelTips, "Have a great day!");
    lv_obj_set_style_text_color(ui_LabelTips, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTips, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelTips, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelTips, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelTips, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_LabelTips, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTips, &ui_font_NeverMindHandBold14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelTest = lv_label_create(ui_ScreenEpinkHome);
    lv_obj_set_width(ui_LabelTest, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTest, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTest, -3);
    lv_obj_set_y(ui_LabelTest, 53);
    lv_obj_set_align(ui_LabelTest, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_LabelTest, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_set_style_text_color(ui_LabelTest, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTest, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTest, &ui_font_NeverMindHandBold14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelStatusBar = ui_PanelStatusBar_create(ui_ScreenEpinkHome);
    lv_obj_set_x(ui_PanelStatusBar, 0);
    lv_obj_set_y(ui_PanelStatusBar, 5);
    lv_obj_clear_flag(ui_PanelStatusBar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelStatusBar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelStatusBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELDATE),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELDATE), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELDATE),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELBATTERY), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBar, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelGreeting = lv_label_create(ui_ScreenEpinkHome);
    lv_obj_set_width(ui_LabelGreeting, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_LabelGreeting, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_LabelGreeting, 0);
    lv_obj_set_y(ui_LabelGreeting, -60);
    lv_obj_set_align(ui_LabelGreeting, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelGreeting, "Good night, iotahydrae");
    lv_obj_set_style_text_color(ui_LabelGreeting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelGreeting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelGreeting, &ui_font_FiraCodeSemiBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_ScreenEpinkConfig_screen_init(void)
{
    ui_ScreenEpinkConfig = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenEpinkConfig, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PanelStatusBarConfig = ui_PanelStatusBar_create(ui_ScreenEpinkConfig);
    lv_obj_set_x(ui_PanelStatusBarConfig, 0);
    lv_obj_set_y(ui_PanelStatusBarConfig, 5);
    lv_obj_clear_flag(ui_PanelStatusBarConfig, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelStatusBarConfig, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelStatusBarConfig, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELDATE),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELDATE), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELDATE),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELBATTERY), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBarConfig, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelWidgetsConfig = lv_obj_create(ui_ScreenEpinkConfig);
    lv_obj_set_width(ui_PanelWidgetsConfig, 200);
    lv_obj_set_height(ui_PanelWidgetsConfig, 160);
    lv_obj_set_x(ui_PanelWidgetsConfig, 0);
    lv_obj_set_y(ui_PanelWidgetsConfig, 15);
    lv_obj_set_align(ui_PanelWidgetsConfig, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelWidgetsConfig, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelWifiName = lv_label_create(ui_ScreenEpinkConfig);
    lv_obj_set_width(ui_LabelWifiName, 200);
    lv_obj_set_height(ui_LabelWifiName, 30);
    lv_obj_set_x(ui_LabelWifiName, 1);
    lv_obj_set_y(ui_LabelWifiName, 80);
    lv_obj_set_align(ui_LabelWifiName, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_LabelWifiName, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_LabelWifiName, "connect to \"Xenia-Clock\" then scan this QR code");
    lv_obj_set_style_text_color(ui_LabelWifiName, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWifiName, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelWifiName, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelWifiName, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelWifiName, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_LabelWifiName, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWifiName, &ui_font_NeverMindHandBold14, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_ScreenSleep_screen_init(void)
{
    ui_ScreenSleep = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSleep, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ImageSleep = lv_img_create(ui_ScreenSleep);
    lv_img_set_src(ui_ImageSleep, &ui_img_884727455);
    lv_obj_set_width(ui_ImageSleep, LV_SIZE_CONTENT);   /// 160
    lv_obj_set_height(ui_ImageSleep, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_align(ui_ImageSleep, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageSleep, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImageSleep, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
void ui_ScreenEpinkApps_screen_init(void)
{
    ui_ScreenEpinkApps = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenEpinkApps, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PanelStatusBar1 = ui_PanelStatusBar_create(ui_ScreenEpinkApps);
    lv_obj_set_x(ui_PanelStatusBar1, 0);
    lv_obj_set_y(ui_PanelStatusBar1, 5);
    lv_obj_clear_flag(ui_PanelStatusBar1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelStatusBar1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelStatusBar1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELDATE),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELDATE), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELDATE),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                                lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELBATTERY), 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_comp_get_child(ui_PanelStatusBar1, UI_COMP_PANELSTATUSBAR_LABELBATTERY),
                               &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonApp1 = lv_btn_create(ui_ScreenEpinkApps);
    lv_obj_set_width(ui_ButtonApp1, 70);
    lv_obj_set_height(ui_ButtonApp1, 70);
    lv_obj_set_x(ui_ButtonApp1, -45);
    lv_obj_set_y(ui_ButtonApp1, -25);
    lv_obj_set_align(ui_ButtonApp1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonApp1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonApp1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonApp1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonApp1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonApp2 = lv_btn_create(ui_ScreenEpinkApps);
    lv_obj_set_width(ui_ButtonApp2, 70);
    lv_obj_set_height(ui_ButtonApp2, 70);
    lv_obj_set_x(ui_ButtonApp2, 45);
    lv_obj_set_y(ui_ButtonApp2, 55);
    lv_obj_set_align(ui_ButtonApp2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonApp2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonApp2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonApp2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonApp2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonApp3 = lv_btn_create(ui_ScreenEpinkApps);
    lv_obj_set_width(ui_ButtonApp3, 70);
    lv_obj_set_height(ui_ButtonApp3, 70);
    lv_obj_set_x(ui_ButtonApp3, -45);
    lv_obj_set_y(ui_ButtonApp3, 55);
    lv_obj_set_align(ui_ButtonApp3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonApp3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonApp3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonApp3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonApp3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonApp4 = lv_btn_create(ui_ScreenEpinkApps);
    lv_obj_set_width(ui_ButtonApp4, 70);
    lv_obj_set_height(ui_ButtonApp4, 70);
    lv_obj_set_x(ui_ButtonApp4, 45);
    lv_obj_set_y(ui_ButtonApp4, -25);
    lv_obj_set_align(ui_ButtonApp4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonApp4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonApp4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonApp4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonApp4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenEpinkHome_screen_init();
    ui_ScreenEpinkConfig_screen_init();
    ui_ScreenSleep_screen_init();
    ui_ScreenEpinkApps_screen_init();
    lv_disp_load_scr(ui_ScreenEpinkHome);
}
