// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0 Beta1
// LVGL VERSION: 8.2
// PROJECT: epink_desktop


#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

uint32_t LV_EVENT_GET_COMP_CHILD;

typedef struct {
    uint32_t child_idx;
    lv_obj_t * child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t * comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_event_send(comp, LV_EVENT_GET_COMP_CHILD, &info);
    return info.child;
}

void get_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    ui_comp_get_child_t * info = lv_event_get_param(e);
    info->child = c[info->child_idx];
}

void del_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    lv_mem_free(c);
}


// COMPONENT Image1

lv_obj_t * ui_Image1_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Image1;
    cui_Image1 = lv_img_create(comp_parent);
    lv_obj_set_width(cui_Image1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Image1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_Image1, 0);
    lv_obj_set_y(cui_Image1, -15);
    lv_obj_set_align(cui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(cui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_IMAGE1_NUM);
    children[UI_COMP_IMAGE1_IMAGE1] = cui_Image1;
    lv_obj_add_event_cb(cui_Image1, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Image1, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_Image1;
}



// COMPONENT PanelStatusBar

lv_obj_t * ui_PanelStatusBar_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_PanelStatusBar;
    cui_PanelStatusBar = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_PanelStatusBar, 190);
    lv_obj_set_height(cui_PanelStatusBar, 20);
    lv_obj_set_x(cui_PanelStatusBar, 0);
    lv_obj_set_y(cui_PanelStatusBar, 5);
    lv_obj_set_align(cui_PanelStatusBar, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(cui_PanelStatusBar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_PanelStatusBar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_PanelStatusBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelDate;
    cui_LabelDate = lv_label_create(cui_PanelStatusBar);
    lv_obj_set_width(cui_LabelDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_LabelDate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_LabelDate, 5);
    lv_obj_set_y(cui_LabelDate, 0);
    lv_obj_set_align(cui_LabelDate, LV_ALIGN_LEFT_MID);
    lv_label_set_text(cui_LabelDate, "2022/11/8");
    lv_obj_set_style_text_color(cui_LabelDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_LabelDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_LabelDate, &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelBattery;
    cui_LabelBattery = lv_label_create(cui_PanelStatusBar);
    lv_obj_set_width(cui_LabelBattery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_LabelBattery, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_LabelBattery, -5);
    lv_obj_set_y(cui_LabelBattery, 0);
    lv_obj_set_align(cui_LabelBattery, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(cui_LabelBattery, "100%");
    lv_obj_set_style_text_color(cui_LabelBattery, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_LabelBattery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_LabelBattery, &ui_font_NeverMindSemiSerifBold12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_PANELSTATUSBAR_NUM);
    children[UI_COMP_PANELSTATUSBAR_PANELSTATUSBAR] = cui_PanelStatusBar;
    children[UI_COMP_PANELSTATUSBAR_LABELDATE] = cui_LabelDate;
    children[UI_COMP_PANELSTATUSBAR_LABELBATTERY] = cui_LabelBattery;
    lv_obj_add_event_cb(cui_PanelStatusBar, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_PanelStatusBar, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_PanelStatusBar;
}

