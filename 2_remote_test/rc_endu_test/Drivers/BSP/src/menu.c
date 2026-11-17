#include "menu.h"
#include "my_mavlink.h"
#include "config_param.h"

extern const char *PopUpLanguage[Language_ID_MAX][LanguageMAX];

#define Option_MAX 7
#define MAIN_MENU_ITEMNUM 13 // 主菜单项数
#define joystickChoose_MENU_NUM 2
#define SpeedSet_MENU_NUM 3
#define CommType_MENU_NUM 2
#define KeyCustom_MENU_NUM 3
#define KeyCustomSet_MENU_NUM 7
#define PointAB_MENU_NUM 3
#define PointABSet_MENU_NUM 9
#define BoatAnchorEn_MENU_NUM 2
#define AutoCruiseEn_MENU_NUM 4
#define GhostModeEnMenu_MENU_NUM 2
#define FONT_MENU_NUM 2
#define LANGUAGE_MENU_NUM 3
#define LOG_MENU_NUM 2

#define TOP_BAR_H 40
#define MENU_FONE font_18 // lv_font_montserrat_14
#define TITLE_FONE font_blod_18

static uint32_t get_img_addr[Option_MAX];          // 这里数组装的是条目里面最左边的img的obj指针(这里为了适应UI界面复选框的效果，复选框样式采用图片)
static uint8_t last_item = 0;                      // 记录上一次的主菜单条目(这里是为了回到主菜单时可以回到之前聚焦的条目)
static lv_coord_t saved_scroll_y = 0;              // 保存主菜单的滚动条位置
static lv_obj_t *list_menu_img[MAIN_MENU_ITEMNUM]; // 主菜单条目最左边的图片
const MenuFun MenuFunArray[MENU_UI] = {
    joystickCalib_ui_init,
    // joystickChooseMenuInit,
    SpeedSetMenuInit,
    SetRF_ID_UI_Init,
    KeyCustomMenuInit,
    PointABMenuInit,
    BoatAnchorEnMenuInit,
    AutoCruiseEnMenuInit,
    GhostModeEnMenuInit,
    FontChoiceMenuInit,
    Show_Versions_UI,
    languageChoiceMenuInit,
    reset_ui_init,
    NULL,
    SavePointABMenuInit,
    TaskModeSelectMenuInit,
    KeyCustomSetMenuInit1,
    KeyCustomSetMenuInit2,
    KeyCustomSetMenuInit3,
    GhostModeEnHintMenuInit,
};
static const lv_img_dsc_t *mainMenuIcon[MAIN_MENU_ITEMNUM] = {
    &rocker,
    // &rocker,
    &speed_icon,
    &link,
    &custom,
    &ABPoint,
    &anchor_icon,
    &speed_auto,
    &ghost_icon,
    &screen_icon,
    &version_icon,
    &Earth_icon,
    &reset_icon,
    &exit_icon,
};
static const uint8_t *mainMenuTitle[LanguageMAX][1] = {
    {
        "设置菜单",
    },
    {
        "Setup menu",
    },
    {
        "меню",
    },
};
static const uint8_t *mainMenuLanguage[LanguageMAX][MAIN_MENU_ITEMNUM] = {
    {
        "摇杆校准",
        // "摇杆选择",
        "速度设置",
        "配对模式",
        "自定义键功能",
        "任务点设置",
        "电子锚",
        "自动定速巡航",
        "幽灵模式",
        "提示框大小",
        "版本信息",
        "语言选择",
        "重置",
        "退出",
    },
    {
        "Joystick calibrat",
        // "Joystick choose",
        "Speed Mode",
        "Pairing mode",
        "Custom key function",
        "Task point settings",
        "Electronic anchor",
        "Auto Cruise",
        "Ghost Mode",
        "Dialog size",
        "Versions",
        "Language",
        "Reset",
        "Exit",
    },
    {
        "RC калибровка", // 摇杆校准
        // "Speed Mode",               // 速度设置
        "пара",                     // 配对模式
        "Пользовательская функция", // 自定义键功能
        "Триггер",                  // 扳机键功能
        "якор",                     // 船锚设置
        "Auto Cruise",              // 自动定速巡航
        "Ghost Mode",               // 幽灵模式
        "Размер рамки",             // 提示弹框大小
        "издание",                  // 版本信息
        "язык",                     // 语言选择
        "сброс",                    // 重置
        "выход",                    // 退出
    },
};
static const uint8_t *joystickChooseLanguage[LanguageMAX][joystickChoose_MENU_NUM] = {
    {
        "遥控器控制",
        "App控制",
    },
    {
        "Remote Control",
        "App Control",
    },
    {
        "探索模式",
        "省电模式",
    },
};
static const uint8_t *SpeedSetLanguage[LanguageMAX][SpeedSet_MENU_NUM] = {
    {
        "探索模式",
        "省电模式",
        "运动模式",
    },
    {
        "Explore mode",
        "Lowpower mode",
        "Movement mode",
    },
    {
        "探索模式",
        "省电模式",
        "运动模式",
    },
};
static const uint8_t *KeyCustomLanguage[LanguageMAX][KeyCustom_MENU_NUM] = {
    {
        "单击选项",
        "双击选项",
        "长按选项",
    },
    {
        "Single click option",
        "Double click option",
        "Long press option",
    },
    {
        "Single click option",
        "Double click option",
        "Long press option",
    },
};
static const uint8_t *KeyCustomSetLanguage[LanguageMAX][KeyCustomSet_MENU_NUM] = {
    {
        "无功能",
        "标记点",
        "速度设置",
        "电子锚",
        "定速巡航",
        "纠正船位置",
        "幽灵模式",
    },
    {
        "Not function",
        "Mark point",
        "Speed mode",
        "Electronic Anchor",
        "Cruise Control",
        "Fix the Deviation",
        "Ghost Mode",
    },
    {
        "Not function",
        "Mark point",
        "Speed mode",
        "Электронный якорь",
        "Круиз-контроль",
        "Коррекция в один клик",
        "Ghost Mode",
    },
};
static const uint8_t *PointABLanguage[LanguageMAX][PointAB_MENU_NUM] = {
    {
        "保存选项",
        "数量选项",
        "删除",
    },
    {
        "Save option",
        "Quantity option",
        "Delete option",
    },
    {
        "Сохранить",
        "Делеция",
    },
};
static const uint8_t *PointABSetLanguage[LanguageMAX][PointABSet_MENU_NUM] = {
    {
        "保存任务点",
        "不保存任务点",
        "删除A点",
        "删除B点",
        "删除C点",
        "删除D点",
        "删除所有点",
        "显示A、B点",
        "显示A、B、C、D点",
    },
    {
        "Save task point",
        "Not save task point",
        "Del A point",
        "Del B point",
        "Del C point",
        "Del D point",
        "Del all point",
        "Show points A and B",
        "Show points A, B, C, D",
    },
    {
        "Сохранить точку",
        "Нет.",
        "Удалить A",
        "Удалить B",
        "Удалить C",
        "Удалить D",
        "Удалить все",
        "Show AB point",
        "Show ABCD point",
    },
};
static const uint8_t *BoatAnchorEnLanguage[LanguageMAX][BoatAnchorEn_MENU_NUM] = {
    {
        "开启船锚",
        "关闭船锚",
    },
    {
        "Open anchor",
        "Close anchor",
    },
    {
        "откр",
        "закрытие",
    },
};
static const uint8_t *AutoCruiseEnLanguage[LanguageMAX][AutoCruiseEn_MENU_NUM] = {
    {
        "摇杆前推持续10s",
        "摇杆前推持续6s",
        "摇杆前推持续3s",
        "关闭",
    },
    {
        "Push joystick forward 10s",
        "Push joystick forward 6s",
        "Push joystick forward 3s",
        "Turn OFF",
    },
    {
        "Push joystick forward 10s",
        "Push joystick forward 6s",
        "Push joystick forward 3s",
        "Turn OFF",
    },
};
static const uint8_t *GhostModeEnMenuLanguage[LanguageMAX][GhostModeEnMenu_MENU_NUM] = {
    {
        "开启",
        "关闭",
    },
    {
        "Turn On",
        "Turn OFF",
    },
    {
        "Turn On",
        "Turn OFF",
    },
};
static const uint8_t *FontChoiceLanguage[LanguageMAX][FONT_MENU_NUM] = {
    {
        "大",
        "小",
    },
    {
        "Big",
        "Small",
    },
    {
        "массив",
        "малый",
    },
};
static const uint8_t *languageChoiceLanguage[LanguageMAX][LANGUAGE_MENU_NUM] = {
    {
        "简体中文",
        "English",
        "русский язык",
    },
    {
        "简体中文",
        "English",
        "русский язык",
    },
    {
        "简体中文",
        "English",
        "русский язык",
    },
};

static void menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int item = lv_obj_get_index(obj);
    // Debug("code:  item: %d", code, item);

    if (show_ui == MENU_UI)
    {
        if (code == LV_EVENT_CLICKED)
        {
            // Debug("Clicked: %s", lv_list_get_btn_text(globeGUI.menu_list, obj));
            set_show_ui(item);
            if (item == Exit)
            {
                set_show_ui(MAIN_UI);
            }
        }
        else if (code == LV_EVENT_FOCUSED)
        {
            // Debug("LV_EVENT_FOCUSED");
            last_item = item;
            Debug("last_item: %d", last_item);
            saved_scroll_y = lv_obj_get_scroll_y(globeGUI.menu_list);
            lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 显示图片
        }
        else if (code == LV_EVENT_DEFOCUSED)
        {
            lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 隐藏图片
        }
    }
}

static lv_obj_t *my_lv_list_add_btn(lv_obj_t *list, uint32_t *img, const char *icon, const char *txt, lv_opa_t value)
{
    lv_obj_t *obj = lv_obj_class_create_obj(&lv_list_btn_class, list);
    lv_obj_class_init_obj(obj);
    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);

#if LV_USE_IMG == 1
    if (icon)
    {
        if (img)
        {
            *img = (uint32_t)lv_img_create(obj);
            // Debug("img: %08X", *img);
            lv_img_set_src((lv_obj_t *)*img, icon);
        }
        else
        {
            lv_obj_t *img1 = lv_img_create(obj);
            lv_img_set_src(img1, icon);
        }
        // lv_obj_set_style_pad_top(img, 4, LV_STATE_DEFAULT);
    }
#endif

    if (txt)
    {
        lv_obj_t *label = lv_label_create(obj);
        lv_obj_set_style_text_font(label, &MENU_FONE, LV_STATE_DEFAULT);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
        lv_obj_set_style_text_opa(label, value, 0); // LV_OPA_COVER 表示完全不透明
    }

    // lv_obj_t *p_img = lv_img_create(obj);
    // lv_img_set_src(p_img, &ArrowLeft_icon);
    // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);

    lv_obj_set_style_border_color(obj, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_min_height(obj, 37, LV_STATE_DEFAULT);
    lv_obj_set_style_min_height(obj, 37, LV_STATE_DEFAULT);
    lv_obj_set_style_max_width(obj, 288, LV_STATE_DEFAULT);
    lv_obj_set_style_transform_width(obj, 0, LV_STATE_FOCUS_KEY); // 禁止按键变宽
    lv_obj_set_style_radius(obj, 12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_make(102, 102, 102), LV_STATE_FOCUS_KEY); // 选中
    lv_obj_set_style_bg_color(obj, lv_color_make(31, 31, 31), LV_STATE_DEFAULT);      // 未选中
    lv_obj_set_style_bg_opa(obj, value, 0);

    return obj;
}

void main_menu_init(void)
{
    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Close_icon);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)mainMenuTitle[configParam.language][0]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;

    for (int i = 0; i < MAIN_MENU_ITEMNUM; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, (const char *)mainMenuIcon[i], (const char *)mainMenuLanguage[configParam.language][i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

        lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, menu_event_handler, LV_EVENT_DEFOCUSED, NULL);
    }
    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT);   // 设置10像素的间隔(条目之间的距离)
    lv_obj_scroll_to_y(globeGUI.menu_list, saved_scroll_y, LV_ANIM_OFF); // 恢复到之前的位置
    if (last_show_ui == BOAT_TASK_PRESET_UI)
    {
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到之前的位置
    }
    else
    {
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, last_item)); // 聚焦到之前的位置
    }
}

void GetSavePointItem(uint8_t direction)
{
    S_Position Position[7] = {
        [0].degE7_lat = 0,
        [0].degE7_long = 0,
        [0].alt_mm = 0,
        [1].degE7_lat = 0,
        [1].degE7_long = 0,
        [1].alt_mm = 0,
        [2] = globeState.Task_Sta.PositionA,
        [3] = globeState.Task_Sta.PositionB,
        [4] = globeState.Task_Sta.PositionC,
        [5] = globeState.Task_Sta.PositionD,
    };

    for (uint8_t i = 0; i < 6; i++)
    {
        if (Position[i].degE7_lat && Position[i].degE7_long)
        {
            Position[6].degE7_lat = 1;
            Position[6].degE7_long = 1;
            Position[6].alt_mm = 1;
            break;
        }
    }

    if (direction)
    {
        globeState.PointABSetItem++;
        if (globeState.PointABSetItem > 6)
        {
            globeState.PointABSetItem = 0;
        }
        if (globeState.PointABSetItem > 1)
        {
            for (uint8_t i = globeState.PointABSetItem; i < 7; i++) // 向后找
            {
                if (Position[i].degE7_lat && Position[i].degE7_long)
                {
                    lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, i + 1)); // 聚焦到哪个条目上
                    globeState.PointABSetItem = i;
                    return;
                }
            }
        }
    }
    else
    {
        if (globeState.PointABSetItem)
        {
            globeState.PointABSetItem--;
        }
        else
        {
            globeState.PointABSetItem = 6;
        }

        if (globeState.PointABSetItem > 1)
        {
            for (uint8_t i = globeState.PointABSetItem; i > 0 && i < 7; i--) // 向前找
            {
                if (Position[i].degE7_lat && Position[i].degE7_long)
                {
                    lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, i + 1)); // 聚焦到哪个条目上
                    globeState.PointABSetItem = i;
                    return;
                }
            }
        }
    }

    if (globeState.PointABSetItem < 2)
    {
        lv_obj_scroll_to_y(globeGUI.menu_list, 0, LV_ANIM_ON);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, globeState.PointABSetItem)); // 聚焦到哪个条目上
    }
    else if (globeState.PointABSetItem > 1)
    {
        globeState.PointABSetItem = 1;
    }
}

static void option_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int item = lv_obj_get_index(obj);
    // Debug("code:  item: %d", code, item);

    if (show_ui <= Exit)
    {
        if (show_ui == Point_AB_setup)
        {
            if (item >= 2) // 这里会去减二是因为list里面的label也会算一个item
            {
                item -= 1;
            }
        }

        if (code == LV_EVENT_CLICKED)
        {
            if (show_ui == Point_AB_setup && item < 2)
            {
                if (item)
                {
                    set_show_ui(TaskModeSelect);
                }
                else
                {
                    set_show_ui(SavePoint_AB);
                }
            }
            else if (show_ui == Custom_function && item < 3)
            {
                set_show_ui(CustomSet_function1 + item);
            }
            else if (show_ui == Ghost_Mode && item == 0 && !globeState.GhostModeEn)
            {
                set_show_ui(Ghost_Mode_Enable_Hint);
            }
            else
            {
                if (show_ui == Point_AB_setup)
                {
                    GUI_Set_System_Parameter(show_ui, item - 1);
                }
                else
                {
                    GUI_Set_System_Parameter(show_ui, item);
                }
                set_show_ui(MENU_UI);
            }
        }
        if (code == LV_EVENT_FOCUSED)
        {
            // Debug("FOCUSED");
            if (show_ui == Point_AB_setup)
            {
                if (item == 0)
                {
                    lv_obj_scroll_to_y(globeGUI.menu_list, 0, LV_ANIM_ON);
                }
                lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 显示图片
            }
            else if (show_ui == Custom_function)
            {
                lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 显示图片
            }
            else
            {
                lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_on_icon); // 设置为聚焦时选中的图片
                lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);     // 显示图片
            }
        }
        if (code == LV_EVENT_DEFOCUSED)
        {
            // Debug("DEFOCUSED");
            if (show_ui == Point_AB_setup)
            {
                lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 隐藏图片
            }
            else if (show_ui == Custom_function)
            {
                lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN); // 隐藏图片
            }
            else
            {
                lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_off_icon); // 设置为未选中图片
                lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);        // 隐藏图片
            }
        }
    }
}

static void option____event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int item = lv_obj_get_index(obj);
    // Debug("code:  item: %d", code, item);

    if (show_ui == SavePoint_AB || show_ui == TaskModeSelect)
    {
        if (code == LV_EVENT_CLICKED)
        {
            GUI_Set_System_Parameter(show_ui, item);
            set_show_ui(Point_AB_setup);
        }
        if (code == LV_EVENT_FOCUSED)
        {
            lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_on_icon); // 设置为聚焦时选中的图片
            lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);     // 显示图片
        }
        if (code == LV_EVENT_DEFOCUSED)
        {

            lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_off_icon); // 设置为未选中图片
            lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);        // 隐藏图片
        }
    }
    else if (show_ui == CustomSet_function1 || show_ui == CustomSet_function2 || show_ui == CustomSet_function3)
    {
        if (code == LV_EVENT_CLICKED)
        {
            GUI_Set_System_Parameter(show_ui, item);
            set_show_ui(Custom_function);
        }
        if (code == LV_EVENT_FOCUSED)
        {
            lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_on_icon); // 设置为聚焦时选中的图片
            lv_obj_clear_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);     // 显示图片
        }
        if (code == LV_EVENT_DEFOCUSED)
        {
            lv_img_set_src((lv_obj_t *)get_img_addr[item], &Radio_off_icon); // 设置为未选中图片
            lv_obj_add_flag(list_menu_img[item], LV_OBJ_FLAG_HIDDEN);        // 隐藏图片
        }
    }
}

static void OptionInit(const uint8_t *title_name, uint32_t *get_img_addr, const uint8_t **item_name, const uint8_t item_num, lv_event_cb_t event_cb)
{
    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)title_name);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;
    for (int i = 0; i < item_num; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, get_img_addr++, (const char *)&Radio_off_icon, (const char *)item_name[i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_DEFOCUSED, NULL);
    }
    lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0));       // 聚焦到哪个条目上(默认: 0)
    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT); // 设置10像素的间隔(条目之间的距离)
}

static void btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        if (show_ui == Reset)
        {
            if (btn == globeGUI.btn1)
            {
                set_show_ui(MENU_UI);
            }
            else if (btn == globeGUI.btn2)
            {
                UserConfigParamReset();
                delay_ms(2);
                NVIC_SystemReset(); // 复位系统
                set_show_ui(MENU_UI);
            }
        }
        else if (show_ui == Ghost_Mode_Enable_Hint)
        {
            if (btn == globeGUI.btn1) // 取消
            {
            }
            else if (btn == globeGUI.btn2) // 确认
            {
                if (globeState.GhostModeEn != 1)
                {
                    if (my_mavlink_msg_int_command(MAV_CMD_DO_GHOST_MODE, 1, 0, 0, 0, 0, 0, 0, 1))
                    {
                        globeState.GhostModeEn = 1;
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                        globeState.show_mainRefresh = Refresh;
                        globeState.boatLEDStatRefresh = Refresh;
                    }
                    else
                    {
                        popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                        lvgl_force_refresh();
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                        delay_ms(1000);
                        lv_show_popup_del();
                    }
                }
            }
            set_show_ui(last_show_ui);
        }
    }
    else if (code == LV_EVENT_VALUE_CHANGED)
    {
        Debug("Toggled");
    }
}

static void HintMenuInit(const lv_img_dsc_t *icon, const char *language1, const char *language2)
{
#define HINT_FONT_0 font_blod_16
#define HINT_FONT_1 font_blod_20
#define HINT_FONT_2 font_16

    static const uint8_t *Language[2][LanguageMAX] = {
        {
            "确定",
            "Confirm",
            "OK",
        },
        {
            "取消",
            "Cancel",
            "esc",
        },
    };

    lv_obj_clean(globeGUI.screen);

    lv_obj_t *label;

    /* 图片 + 开始校准 + 完成校准 的obj*/
    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    lv_obj_set_style_border_opa(obj, LV_OPA_0, LV_STATE_DEFAULT);                                 // 设置边框透明度
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);                     // 无边框
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_STATE_DEFAULT);                     // 设置背景颜色为黑色
    lv_obj_set_style_radius(obj, 0, LV_STATE_DEFAULT);                                            // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);                                               // 关闭滚动
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, -50);                                                   // 显示位置
    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);                                           // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    /* 重置img */
    lv_obj_t *reset_img = lv_img_create(obj);
    lv_img_set_src(reset_img, icon);

    /* 重置 */
    label = lv_label_create(obj);
    lv_obj_set_style_text_font(label, &HINT_FONT_0, LV_STATE_DEFAULT);
    lv_label_set_text(label, (const char *)language1);                                        //
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);             // 字体颜色
    const lv_font_t *font = lv_obj_get_style_text_font(label, LV_PART_MAIN);                  // 获取标签使用的字体
    const char *text = lv_label_get_text(label);                                              // 获取标签的文本
    lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > LCD_H)
    {
        lv_obj_set_width(label, LCD_H);                               // 设置最大显示宽度
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

    /* 确定恢复为默认设置？ */
    label = lv_label_create(lv_scr_act());
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);                                 // 显示位置
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_set_style_text_font(label, &HINT_FONT_1, LV_STATE_DEFAULT);            // 字体文件
    lv_label_set_text(label, (const char *)language2);                            // 显示文字 保持摇杆回中
    lv_obj_set_width(label, 320);                                                 // 设置最大显示宽度
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);   // 字符串居中显示
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);                 // 字符串超过了最大宽度滚动显示

    globeGUI.btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(globeGUI.btn1, btn_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(globeGUI.btn1, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    /* 取消 */
    label = lv_label_create(globeGUI.btn1);
    lv_obj_set_style_text_font(label, &HINT_FONT_2, LV_STATE_DEFAULT); // 字体文件
    lv_label_set_text(label, (const char *)Language[1][configParam.language]);
    lv_obj_center(label);
    lv_obj_set_style_border_color(globeGUI.btn1, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.btn1, 0, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_transform_width(globeGUI.btn1, 0, LV_STATE_FOCUS_KEY); // 禁止按键变宽
    lv_obj_set_style_radius(globeGUI.btn1, 12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(globeGUI.btn1, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(globeGUI.btn1, lv_color_hex(0x666666), LV_STATE_FOCUS_KEY); // 选中
    lv_obj_set_style_bg_color(globeGUI.btn1, lv_color_hex(0x212121), LV_STATE_DEFAULT);   // 未选中
    lv_obj_set_style_shadow_width(globeGUI.btn1, 0, LV_STATE_DEFAULT);                    // 禁用阴影效果
    lv_obj_set_style_outline_width(globeGUI.btn1, 0, LV_STATE_FOCUS_KEY);                 // 关闭轮廓
    lv_obj_set_size(globeGUI.btn1, 142, 48);

    /* 确认 */
    globeGUI.btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(globeGUI.btn2, btn_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(globeGUI.btn2, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    label = lv_label_create(globeGUI.btn2);
    lv_obj_set_style_text_font(label, &HINT_FONT_2, LV_STATE_DEFAULT); // 字体文件
    lv_label_set_text(label, (const char *)Language[0][configParam.language]);
    lv_obj_center(label);
    lv_obj_set_style_border_color(globeGUI.btn2, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.btn2, 0, LV_STATE_FOCUS_KEY);    // 外框
    lv_obj_set_style_transform_width(globeGUI.btn2, 0, LV_STATE_FOCUS_KEY); // 禁止按键变宽
    lv_obj_set_style_radius(globeGUI.btn2, 12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(globeGUI.btn2, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(globeGUI.btn2, lv_color_hex(0x666666), LV_STATE_FOCUS_KEY); // 选中
    lv_obj_set_style_bg_color(globeGUI.btn2, lv_color_hex(0x212121), LV_STATE_DEFAULT);   // 未选中
    lv_obj_set_style_shadow_width(globeGUI.btn2, 0, LV_STATE_DEFAULT);                    // 禁用阴影效果
    lv_obj_set_style_outline_width(globeGUI.btn2, 0, LV_STATE_FOCUS_KEY);                 // 关闭轮廓
    lv_obj_set_size(globeGUI.btn2, 142, 48);

    // 设置焦点到第一个按钮
    lv_group_focus_obj(globeGUI.btn1);
}

static void SpeedSetMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            SpeedSetLanguage[configParam.language][0],
        },
        {
            SpeedSetLanguage[configParam.language][1],
        },
        {
            SpeedSetLanguage[configParam.language][2],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][SpeedSet], get_img_addr, str, SpeedSet_MENU_NUM, option_event_handler);

    if (configParam.BoatSpeed == 0)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else if (configParam.BoatSpeed == 1)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[2], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 2)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[2], LV_OBJ_FLAG_HIDDEN);
    }
}

static void joystickChooseMenuInit(void)
{
    // lv_obj_clean(globeGUI.screen);

    // const uint8_t *str[] = {
    //     {
    //         joystickChooseLanguage[configParam.language][0],
    //     },
    //     {
    //         joystickChooseLanguage[configParam.language][1],
    //     },
    // };

    // OptionInit(mainMenuLanguage[configParam.language][JoystickChooseUI], get_img_addr, str, joystickChoose_MENU_NUM, option_event_handler);
    // if (configParam.JoystickChoose == 0)
    // {
    //     lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
    //     lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上
    //     lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    // }
    // else if (configParam.JoystickChoose == 1)
    // {
    //     lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
    //     lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
    //     lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    // }
    // else
    // {
    //     configParam.JoystickChoose = 0; // 默认值
    //     lv_img_set_src((lv_obj_t *)get_img_addr[2], &Radio_on_icon);
    //     lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上
    //     lv_obj_clear_flag(list_menu_img[2], LV_OBJ_FLAG_HIDDEN);
    // }
}

static void KeyCustomMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)mainMenuLanguage[configParam.language][Custom_function]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;
    for (int i = 0; i < KeyCustom_MENU_NUM; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)KeyCustomLanguage[configParam.language][i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_DEFOCUSED, NULL);
    }
    lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);           // 显示
    lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0));       // 聚焦到哪个条目上(默认: 0)
    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT); // 设置10像素的间隔(条目之间的距离)
}

static void KeyCustomSetMenuInit(int item)
{
    int KeyCustom = 0;

    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[KeyCustomSet_MENU_NUM];
    for (uint8_t i = 0; i < KeyCustomSet_MENU_NUM; i++)
    {
        str[i] = KeyCustomSetLanguage[configParam.language][i];
    }

    OptionInit(KeyCustomLanguage[configParam.language][item], get_img_addr, str, KeyCustomSet_MENU_NUM, option____event_handler);

    switch (item)
    {
    case 0:
    {
        KeyCustom = configParam.ShortKeyCustom;
    }
    break;
    case 1:
    {
        KeyCustom = configParam.DoubleKeyCustom;
    }
    break;
    case 2:
    {
        KeyCustom = configParam.LongKeyCustom;
    }
    break;
    }

    switch (KeyCustom)
    {
    case KEY_NOT:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case KEY_SIGN:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case Cut_Boat_Speed:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[2], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 2)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[2], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case ElectronicAnchor:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[3], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 3)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[3], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case CruiseControl:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[4], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 4)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[4], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case FixTheDeviation:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[5], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 5)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[5], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    case GhostModeEnable:
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[6], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 6)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[6], LV_OBJ_FLAG_HIDDEN);
    }
    break;
    }
}

static void KeyCustomSetMenuInit1(void)
{
    KeyCustomSetMenuInit(0);
}

static void KeyCustomSetMenuInit2(void)
{
    KeyCustomSetMenuInit(1);
}

static void KeyCustomSetMenuInit3(void)
{
    KeyCustomSetMenuInit(2);
}

static void PointABMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)mainMenuLanguage[configParam.language][Point_AB_setup]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;
    for (int i = 0; i < 2; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)PointABLanguage[configParam.language][i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_DEFOCUSED, NULL);
    }
    lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

    lv_obj_t *obj = lv_list_add_text(globeGUI.menu_list, (const char *)PointABLanguage[configParam.language][2]);
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0); // 设置屏幕背景为黑色
    lv_obj_set_style_text_font(obj, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色

    S_Position Position[4] = {
        globeState.Task_Sta.PositionA,
        globeState.Task_Sta.PositionB,
        globeState.Task_Sta.PositionC,
        globeState.Task_Sta.PositionD,
    };

    for (int i = 0, sum = 0; i < 5; i++)
    {
        if (i < 4)
        {
            if (Position[i].degE7_lat && Position[i].degE7_long)
            {
                sum++;
                btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)PointABSetLanguage[configParam.language][2 + i], LV_OPA_COVER);
            }
            else
            {
                btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)PointABSetLanguage[configParam.language][2 + i], LV_OPA_70);
            }
        }
        else // 删除全部点
        {
            if (sum)
            {
                btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)PointABSetLanguage[configParam.language][2 + i], LV_OPA_COVER);
            }
            else
            {
                btn = my_lv_list_add_btn(globeGUI.menu_list, NULL, NULL, (const char *)PointABSetLanguage[configParam.language][2 + i], LV_OPA_70);
            }
        }

        list_menu_img[2 + i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[2 + i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[2 + i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, option_event_handler, LV_EVENT_DEFOCUSED, NULL);
    }

    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT); // 设置10像素的间隔(条目之间的距离)
    lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0));       // 聚焦到哪个条目上

    globeState.PointABSetItem = 0;
}

static void SavePointABMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)PointABLanguage[configParam.language][0]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;
    for (int i = 0; i < 2; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, &get_img_addr[i], (const char *)&Radio_off_icon, (const char *)PointABSetLanguage[configParam.language][i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_DEFOCUSED, NULL);
    }

    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT); // 设置10像素的间隔(条目之间的距离)

    if (configParam.SavePointAB)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0));  // 聚焦到哪个条目上
    }
    else
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
}

static void TaskModeSelectMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)PointABLanguage[configParam.language][1]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    /*CONTENT DETAIL*/
    globeGUI.menu_list = lv_list_create(lv_scr_act());
    lv_obj_set_size(globeGUI.menu_list, LCD_W, (LCD_H - TOP_BAR_H));
    lv_obj_align(globeGUI.menu_list, LV_ALIGN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_bg_color(globeGUI.menu_list, lv_color_black(), 0);                      // 设置屏幕背景为黑色
    lv_obj_set_style_border_side(globeGUI.menu_list, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框

    lv_obj_t *btn;
    for (int i = 0; i < 2; i++)
    {
        btn = my_lv_list_add_btn(globeGUI.menu_list, &get_img_addr[i], (const char *)&Radio_off_icon, (const char *)PointABSetLanguage[configParam.language][7 + i], LV_OPA_COVER);
        list_menu_img[i] = lv_img_create(btn);
        lv_img_set_src(list_menu_img[i], &ArrowLeft_icon);
        // lv_obj_set_style_pad_top(p_img, 4, LV_STATE_DEFAULT);
        lv_obj_add_flag(list_menu_img[i], LV_OBJ_FLAG_HIDDEN); // 隐藏图片

        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_FOCUSED, NULL);
        lv_obj_add_event_cb(btn, option____event_handler, LV_EVENT_DEFOCUSED, NULL);
    }

    lv_obj_set_style_pad_row(globeGUI.menu_list, 8, LV_STATE_DEFAULT); // 设置10像素的间隔(条目之间的距离)

    if (configParam.AB_Mode == AB_MODE)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0));  // 聚焦到哪个条目上
    }
    else
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
}

static void BoatAnchorEnMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            BoatAnchorEnLanguage[configParam.language][0],
        },
        {
            BoatAnchorEnLanguage[configParam.language][1],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][Anchor_setup], get_img_addr, str, BoatAnchorEn_MENU_NUM, option_event_handler);

    if (configParam.BoatAnchorEn)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        // lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
}

static void AutoCruiseEnMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            AutoCruiseEnLanguage[configParam.language][0],
        },
        {
            AutoCruiseEnLanguage[configParam.language][1],
        },
        {
            AutoCruiseEnLanguage[configParam.language][2],
        },
        {
            AutoCruiseEnLanguage[configParam.language][3],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][AutoCruise_setup], get_img_addr, str, AutoCruiseEn_MENU_NUM, option_event_handler);

    if (configParam.AutoCruiseEn == 10)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else if (configParam.AutoCruiseEn == 6)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
    else if (configParam.AutoCruiseEn == 3)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[2], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 2)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[2], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[3], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 3)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[3], LV_OBJ_FLAG_HIDDEN);
    }
}

static void GhostModeEnMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            GhostModeEnMenuLanguage[configParam.language][0],
        },
        {
            GhostModeEnMenuLanguage[configParam.language][1],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][Ghost_Mode], get_img_addr, str, GhostModeEnMenu_MENU_NUM, option_event_handler);

    if (globeState.GhostModeEn)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        // lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
}

static void GhostModeEnHintMenuInit(void)
{
    static const char *ConfirmSetLanguage[2][LanguageMAX] = {
        {
            "开启幽灵模式",
            "Enable Ghost Mode",
            "Enable Ghost Mode",
        },
        {
            "示廓灯将始终关闭",
            "Indicator lights will always be off",
            "Indicator lights will always be off",
        },
    };

    if (last_show_ui == MAIN_UI || last_show_ui == BOAT_TASK_PRESET_UI)
    {
        lv_show_popup_del();
        task_animation_del();
        anchor_animation_del();
        globeGUI.main_label = NULL;
        globeGUI.log_img = NULL;
        globeGUI.light_img = NULL;
        globeGUI.main_label2 = NULL;
    }
    HintMenuInit(&ghost_icon, ConfirmSetLanguage[0][configParam.language], ConfirmSetLanguage[1][configParam.language]);
}

static void FontChoiceMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            FontChoiceLanguage[configParam.language][0],
        },
        {
            FontChoiceLanguage[configParam.language][1],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][Dialog_size], get_img_addr, str, FONT_MENU_NUM, option_event_handler);

    if (configParam.PopUpFlag)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        // lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
}

static void languageChoiceMenuInit(void)
{
    lv_obj_clean(globeGUI.screen);

    const uint8_t *str[] = {
        {
            languageChoiceLanguage[configParam.language][0],
        },
        {
            languageChoiceLanguage[configParam.language][1],
        },
        {
            languageChoiceLanguage[configParam.language][2],
        },
    };

    OptionInit(mainMenuLanguage[configParam.language][Language], get_img_addr, str, LANGUAGE_MENU_NUM - 1, option_event_handler); //

    if (configParam.language == SIMPLE_CHINESE)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
    }
    else if (configParam.language == ENGLISH)
    {
        // lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_off_icon); // 默认初始化为Radio_off_icon
        lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_on_icon);
        lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 1)); // 聚焦到哪个条目上
        lv_obj_clear_flag(list_menu_img[1], LV_OBJ_FLAG_HIDDEN);
    }
    else if (configParam.language == RUSSIAN)
    {
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        configParam.language = SIMPLE_CHINESE;
        lv_img_set_src((lv_obj_t *)get_img_addr[0], &Radio_on_icon);
        // lv_img_set_src((lv_obj_t *)get_img_addr[1], &Radio_off_icon); // 默认初始化为Radio_off_icon
        // lv_group_focus_obj(lv_obj_get_child(globeGUI.menu_list, 0)); // 聚焦到哪个条目上(默认为0)
        lv_obj_clear_flag(list_menu_img[0], LV_OBJ_FLAG_HIDDEN);
    }
}

/*重置界面*/
static void reset_ui_init(void)
{
    static const char *resetSystemLanguage[2][LanguageMAX] = {
        {
            "重置",
            "Reset",
            "сброс",
        },
        {
            "确定恢复为默认设置？",
            "Restore the default Setting?",
            "Восстановление по    умолчанию?",
        },
    };

    HintMenuInit(&reset_icon, resetSystemLanguage[0][configParam.language], resetSystemLanguage[1][configParam.language]);
}

static const char *VersionLanguage[2][LanguageMAX] = {
    {
        "软件版本：",
        "Software version: ",
        "программное: ",
    },
    {
        "硬件版本：",
        "Hardware version: ",
        "аппаратное: ",
    },
};

/*显示版本号*/
static void Show_Versions_UI(void)
{
    lv_obj_clean(globeGUI.screen);

    char string[20];
    char show_string[100];

    lv_obj_t *label;

    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &Arrow_left_L);
    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 20, 10);
    // lv_obj_set_size(img, 12, 12);

    lv_obj_t *title = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(title, &TITLE_FONE, LV_STATE_DEFAULT);
    lv_label_set_text(title, (const char *)mainMenuLanguage[configParam.language][Versions]);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(title, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    globeGUI.log_img = lv_img_create(globeGUI.screen); // LOG
    lv_obj_align(globeGUI.log_img, LV_ALIGN_CENTER, 0, -20);
    if (globeState.BoatVersion == CatchX_MAX)
    {
        lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + MAIN_LOG_IMG_ID_OFFSET]);
    }
    else if (globeState.BoatVersion == Rogue_MAX)
    {
        lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + ROGUE_MAX_IMG_ID]);
    }
    else if (globeState.BoatVersion == CatchX_Ultra)
    {
        lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + CATCHX_ULTRA_IMG_ID]);
    }

    /* 软件版本 */
    label = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(label, &font_blod_16, LV_STATE_DEFAULT);
#ifdef ENDU_TEST_BUILD
    sprintf(string, "V%d.%02d.%02d-ENDU-TEST", SoftwareVERSION / 10000, SoftwareVERSION % 10000 / 100, SoftwareVERSION % 100);
#else
    sprintf(string, "V%d.%02d.%02d", SoftwareVERSION / 10000, SoftwareVERSION % 10000 / 100, SoftwareVERSION % 100);
#endif
    strcpy(show_string, VersionLanguage[0][configParam.language]);
    strcat(show_string, string);
    lv_label_set_text(label, (const char *)show_string);                                      // 显示文字
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);             // 字体颜色
    const lv_font_t *font = lv_obj_get_style_text_font(label, LV_PART_MAIN);                  // 获取标签使用的字体
    const char *text = lv_label_get_text(label);                                              // 获取标签的文本
    lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > LCD_W)
    {
        lv_obj_set_width(label, LCD_W);                               // 设置最大显示宽度
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 25);

    /* 硬件版本 */
    label = lv_label_create(globeGUI.screen);
    lv_obj_set_style_text_font(label, &font_blod_16, LV_STATE_DEFAULT);
    sprintf(string, "V%d.%02d.%02d", HardwareVERSION / 10000, HardwareVERSION % 10000 / 100, HardwareVERSION % 100);
    strcpy(show_string, VersionLanguage[1][configParam.language]);
    strcat(show_string, string);
    lv_label_set_text(label, (const char *)show_string);                           // 显示文字
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);  // 字体颜色
    font = lv_obj_get_style_text_font(label, LV_PART_MAIN);                        // 获取标签使用的字体
    text = lv_label_get_text(label);                                               // 获取标签的文本
    text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > LCD_W)
    {
        lv_obj_set_width(label, LCD_W);                               // 设置最大显示宽度
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 50);
}

void change_ui_init(void)
{
#define SHOW_X 15
#define SHOW_Y 28
    globeGUI.remote_boat_img = lv_img_create(globeGUI.screen);       /* 充电图标 */
    lv_img_set_src(globeGUI.remote_boat_img, &Rippton_log);          // 加载的图片
    lv_obj_align(globeGUI.remote_boat_img, LV_ALIGN_CENTER, 0, -40); // 显示位置
    lv_img_set_angle(globeGUI.remote_boat_img, 0);                   // 图片旋转角度0-3600

    globeGUI.charge_semicircle = lv_obj_create(globeGUI.screen);                                     /* 实心圆 */
    lv_obj_set_size(globeGUI.charge_semicircle, 18, 18);                                             // 显示大小
    lv_obj_set_style_border_opa(globeGUI.charge_semicircle, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_bg_color(globeGUI.charge_semicircle, lv_color_hex(0xff0000), LV_STATE_DEFAULT); // 开始渐变颜色
    lv_obj_set_style_radius(globeGUI.charge_semicircle, 8, LV_PART_MAIN);
    lv_obj_align(globeGUI.charge_semicircle, LV_ALIGN_CENTER, 45 + SHOW_X, SHOW_Y); // 显示位置

    lv_obj_t *obj = lv_obj_create(globeGUI.screen);                           /* 遮住半圆 */
    lv_obj_set_size(obj, 18, 18);                                             // 显示大小
    lv_obj_set_style_border_opa(obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 开始渐变颜色
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
    lv_obj_align(obj, LV_ALIGN_CENTER, 45 - 9 + SHOW_X, SHOW_Y); // 显示位置

    globeGUI.charge_out_border = lv_obj_create(globeGUI.screen);                           /* 遥控器电量图标 */
    lv_obj_set_size(globeGUI.charge_out_border, 96 - 12, 48);                              // 显示大小
    lv_obj_set_style_border_opa(globeGUI.charge_out_border, LV_OPA_100, LV_STATE_DEFAULT); // 设置边框透明度
    lv_obj_set_style_border_width(globeGUI.charge_out_border, 6, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(globeGUI.charge_out_border, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(globeGUI.charge_out_border, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 开始渐变颜色
    lv_obj_set_style_radius(globeGUI.charge_out_border, 12, LV_PART_MAIN);
    lv_obj_align(globeGUI.charge_out_border, LV_ALIGN_CENTER, SHOW_X, SHOW_Y);                            // 显示位置
    globeGUI.remote_boat_img = lv_img_create(globeGUI.screen);                                            /* 充电图标 */
    lv_img_set_src(globeGUI.remote_boat_img, &change_1_img);                                              // 加载的图片
    lv_obj_align_to(globeGUI.remote_boat_img, globeGUI.charge_out_border, LV_ALIGN_OUT_LEFT_MID, -15, 0); // 图片显示位置
    lv_img_set_angle(globeGUI.remote_boat_img, 0);                                                        // 图片旋转角度0-3600

    // 创建一个进度条对象
    globeGUI.charge_bar = lv_bar_create(globeGUI.screen);
    lv_obj_set_size(globeGUI.charge_bar, 64, 28);
    lv_obj_align(globeGUI.charge_bar, LV_ALIGN_CENTER, SHOW_X, SHOW_Y); // 显示位置
    lv_bar_set_range(globeGUI.charge_bar, 0, 100);                      /* 设置进度条部件范围 */
    lv_bar_set_value(globeGUI.charge_bar, 50, LV_ANIM_ON);              /* 设置进度条当前值 */
    lv_obj_set_style_radius(globeGUI.charge_bar, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(globeGUI.charge_bar, 3, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(globeGUI.charge_bar, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_color(globeGUI.charge_bar, lv_color_hex(0xFF0000), LV_PART_INDICATOR);
}

void change_run(void)
{
    static uint8_t bar_value = 0;
    static uint32_t delay = 0;

    if (GetTimeInterval(delay, GetSysTick()) >= 1000)
    {
        delay = GetSysTick();

        if (globeState.chargeStat == charge_ok)
        {
            bar_value = 100;
        }
        else
        {
            bar_value += 20;
            if (bar_value > 100)
            {
                bar_value = 20;
            }
        }
        lv_obj_set_style_bg_color(globeGUI.charge_semicircle, lv_color_make(0, 255, 0), LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(globeGUI.charge_out_border, lv_color_make(0, 255, 0), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(globeGUI.charge_bar, lv_color_make(0, 255, 0), LV_PART_INDICATOR);
        lv_bar_set_value(globeGUI.charge_bar, bar_value, LV_ANIM_ON);
    }
}

void SetKeyCustom(uint8_t *KeyCustom, uint8_t SetValue)
{
    switch (SetValue)
    {
    case KEY_NOT:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case KEY_SIGN:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case Cut_Boat_Speed:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case ElectronicAnchor:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case CruiseControl:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case FixTheDeviation:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    case GhostModeEnable:
    {
        if (*KeyCustom != SetValue)
        {
            *KeyCustom = SetValue;
            NeedSave_User_Data();
        }
    }
    break;
    }
    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
}

void GUI_Set_System_Parameter(uint8_t main_item, uint8_t item)
{
    switch (main_item)
    {
    case JoystickChooseUI:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.JoystickChoose != 0)
            {
                configParam.JoystickChoose = 0;
                WriteUserConfigParamEeprom();
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
            }
        }
        break;
        case 1:
        {
            if (configParam.JoystickChoose != 1)
            {
                configParam.JoystickChoose = 1;
                WriteUserConfigParamEeprom();
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
            }
        }
        }
    }
    break;
    case SpeedSet:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.BoatSpeed != Speed_min)
            {
                if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_LOW)) // 设置RTL速度
                {
                    configParam.BoatSpeed = Speed_min;
                    WriteUserConfigParamEeprom();
                    popup_init((lv_img_dsc_t *)&Check_img, NULL, NULL, (char *)PopUpLanguage[SetOK_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
                else
                {
                    popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
            }
            else
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
            }
        }
        break;
        case 1:
        {
            if (configParam.BoatSpeed != Speed_normal)
            {
                if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_NORMA)) // 设置RTL速度
                {
                    configParam.BoatSpeed = Speed_normal;
                    WriteUserConfigParamEeprom();
                    popup_init((lv_img_dsc_t *)&Check_img, NULL, NULL, (char *)PopUpLanguage[SetOK_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
                else
                {
                    popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
            }
            else
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
            }
        }
        break;
        case 2:
        {
            if (configParam.BoatSpeed != Speed_max)
            {
                if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_HIGH)) // 设置RTL速度
                {
                    configParam.BoatSpeed = Speed_max;
                    WriteUserConfigParamEeprom();
                    popup_init((lv_img_dsc_t *)&Check_img, NULL, NULL, (char *)PopUpLanguage[SetOK_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
                else
                {
                    popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
            }
            else
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
            }
        }
        break;
        }

        if (globeState.CruiseSta)
        {
            float speed_value = 1.0f;
            if (configParam.BoatSpeed == Speed_min)
            {
                speed_value = BoatSpeed_LOW;
            }
            else if (configParam.BoatSpeed == Speed_normal)
            {
                speed_value = BoatSpeed_NORMA;
            }
            else if (configParam.BoatSpeed == Speed_max)
            {
                speed_value = BoatSpeed_HIGH;
            }
            if (!my_mavlink_msg_command((MAV_CMD)59999, speed_value, 0, 0, 0, 0, 0, 0, 1))
            {
                popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[CruiseFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                lvgl_force_refresh();
                delay_ms(1000);
                lv_show_popup_del();
            }
        }
    }
    break;
    case CustomSet_function1:
    {
        SetKeyCustom(&configParam.ShortKeyCustom, item);
        if (configParam.ShortKeyCustom == configParam.DoubleKeyCustom)
        {
            configParam.DoubleKeyCustom = KEY_NOT;
        }
        else if (configParam.ShortKeyCustom == configParam.LongKeyCustom)
        {
            configParam.LongKeyCustom = KEY_NOT;
        }
    }
    break;
    case CustomSet_function2:
    {
        SetKeyCustom(&configParam.DoubleKeyCustom, item);
        if (configParam.DoubleKeyCustom == configParam.ShortKeyCustom)
        {
            configParam.ShortKeyCustom = KEY_NOT;
        }
        else if (configParam.DoubleKeyCustom == configParam.LongKeyCustom)
        {
            configParam.LongKeyCustom = KEY_NOT;
        }
    }
    break;
    case CustomSet_function3:
    {
        SetKeyCustom(&configParam.LongKeyCustom, item);
        if (configParam.LongKeyCustom == configParam.DoubleKeyCustom)
        {
            configParam.DoubleKeyCustom = KEY_NOT;
        }
        else if (configParam.LongKeyCustom == configParam.ShortKeyCustom)
        {
            configParam.ShortKeyCustom = KEY_NOT;
        }
    }
    break;
    case SavePoint_AB:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.SavePointAB != 1)
            {
                configParam.SavePointAB = 1;
                NeedSave_User_Data();
                Debug("SavePointAB: %d", configParam.SavePointAB);
            }
        }
        break;
        case 1:
        {
            if (configParam.SavePointAB != 0)
            {
                configParam.SavePointAB = 0;
                memset(&configParam.PositionA, 0, sizeof(configParam.PositionA));
                memset(&configParam.PositionB, 0, sizeof(configParam.PositionB));
                memset(&configParam.PositionC, 0, sizeof(configParam.PositionA));
                memset(&configParam.PositionD, 0, sizeof(configParam.PositionB));
                NeedSave_User_Data();
                Debug("SavePointAB: %d", configParam.SavePointAB);
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case TaskModeSelect:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.AB_Mode != 0)
            {
                configParam.AB_Mode = 0;

                globeState.PositionARefresh = 1;
                globeState.PositionBRefresh = 1;
                globeState.PositionCRefresh = 1;
                globeState.PositionDRefresh = 1;

                memset((void *)&globeState.Task_Sta.PositionC, 0, sizeof(globeState.Task_Sta.PositionC));
                configParam.PositionC = globeState.Task_Sta.PositionC;
                memset((void *)&globeState.Task_Sta.PositionD, 0, sizeof(globeState.Task_Sta.PositionD));
                configParam.PositionD = globeState.Task_Sta.PositionD;

                NeedSave_User_Data();
                Debug("AB_Mode: %d", configParam.AB_Mode);
                remote_system_data_send_to_app();
            }
        }
        break;
        case 1:
        {
            if (configParam.AB_Mode != 1)
            {
                configParam.AB_Mode = 1;

                globeState.PositionARefresh = 1;
                globeState.PositionBRefresh = 1;
                globeState.PositionCRefresh = 1;
                globeState.PositionDRefresh = 1;

                NeedSave_User_Data();
                Debug("AB_Mode: %d", configParam.AB_Mode);
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case Point_AB_setup:
    {
        switch (item)
        {
        case 1:
        {
            memset((void *)&globeState.Task_Sta.PositionA, 0, sizeof(globeState.Task_Sta.PositionA));
            configParam.PositionA = globeState.Task_Sta.PositionA;
            globeState.PositionARefresh = 1;
            NeedSave_User_Data();
            remote_system_data_send_to_app();
            Debug("Del A");
        }
        break;
        case 2:
        {
            memset((void *)&globeState.Task_Sta.PositionB, 0, sizeof(globeState.Task_Sta.PositionB));
            configParam.PositionB = globeState.Task_Sta.PositionB;
            globeState.PositionBRefresh = 1;
            NeedSave_User_Data();
            remote_system_data_send_to_app();
            Debug("Del B");
        }
        break;
        case 3:
        {
            memset((void *)&globeState.Task_Sta.PositionC, 0, sizeof(globeState.Task_Sta.PositionC));
            configParam.PositionC = globeState.Task_Sta.PositionC;
            globeState.PositionCRefresh = 1;
            NeedSave_User_Data();
            remote_system_data_send_to_app();
            Debug("Del C");
        }
        break;
        case 4:
        {
            memset((void *)&globeState.Task_Sta.PositionD, 0, sizeof(globeState.Task_Sta.PositionD));
            configParam.PositionD = globeState.Task_Sta.PositionD;
            globeState.PositionDRefresh = 1;
            NeedSave_User_Data();
            remote_system_data_send_to_app();
            Debug("Del D");
        }
        break;
        case 5:
        {
            memset((void *)&globeState.Task_Sta.PositionA, 0, sizeof(globeState.Task_Sta.PositionA));
            configParam.PositionA = globeState.Task_Sta.PositionA;
            LED_TaskA_Pin = LED_OFF;

            memset((void *)&globeState.Task_Sta.PositionB, 0, sizeof(globeState.Task_Sta.PositionB));
            configParam.PositionB = globeState.Task_Sta.PositionB;
            LED_TaskB_Pin = LED_OFF;

            memset((void *)&globeState.Task_Sta.PositionC, 0, sizeof(globeState.Task_Sta.PositionC));
            configParam.PositionC = globeState.Task_Sta.PositionC;
            LED_TaskA_Pin = LED_OFF;

            memset((void *)&globeState.Task_Sta.PositionD, 0, sizeof(globeState.Task_Sta.PositionD));
            configParam.PositionD = globeState.Task_Sta.PositionD;
            LED_TaskB_Pin = LED_OFF;

            globeState.PositionARefresh = 1;
            globeState.PositionBRefresh = 1;
            globeState.PositionCRefresh = 1;
            globeState.PositionDRefresh = 1;

            NeedSave_User_Data();
            remote_system_data_send_to_app();
            Debug("Del ALL");
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case Anchor_setup:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.BoatAnchorEn != 1)
            {
                configParam.BoatAnchorEn = 1;
                NeedSave_User_Data();
                remote_system_data_send_to_app();
            }
        }
        break;
        case 1:
        {
            if (configParam.BoatAnchorEn != 0)
            {
                configParam.BoatAnchorEn = 0;
                NeedSave_User_Data();
                remote_system_data_send_to_app();
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case AutoCruise_setup:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.AutoCruiseEn != 10)
            {
                configParam.AutoCruiseEn = 10;
                NeedSave_User_Data();
            }
        }
        break;
        case 1:
        {
            if (configParam.AutoCruiseEn != 6)
            {
                configParam.AutoCruiseEn = 6;
                NeedSave_User_Data();
            }
        }
        break;
        case 2:
        {
            if (configParam.AutoCruiseEn != 3)
            {
                configParam.AutoCruiseEn = 3;
                NeedSave_User_Data();
            }
        }
        break;
        case 3:
        {
            if (configParam.AutoCruiseEn != 0)
            {
                configParam.AutoCruiseEn = 0;
                NeedSave_User_Data();
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case Ghost_Mode:
    {
        switch (item)
        {
        case 0:
        {
#if 0 
            if (globeState.GhostModeEn != 1)
            {
                globeState.GhostModeEn = 1;
            }
#endif
        }
        break;
        case 1:
        {
            if (globeState.GhostModeEn != 0)
            {
                if (my_mavlink_msg_int_command(MAV_CMD_DO_GHOST_MODE, 0, 0, 0, 0, 0, 0, 0, 1))
                {
                    globeState.GhostModeEn = 0;
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    globeState.show_mainRefresh = Refresh;
                    globeState.boatLEDStatRefresh = Refresh;
                }
                else
                {
                    popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                    lvgl_force_refresh();
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    delay_ms(1000);
                    lv_show_popup_del();
                }
            }
        }
        break;
        }
    }
    break;
    case Dialog_size:
    {
        switch (item)
        {
        case 1:
        {
            if (configParam.PopUpFlag != 0)
            {
                configParam.PopUpFlag = 0;
                NeedSave_User_Data();
            }
        }
        break;
        case 0:
        {
            if (configParam.PopUpFlag != 1)
            {
                configParam.PopUpFlag = 1;
                NeedSave_User_Data();
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    case Language:
    {
        switch (item)
        {
        case 0:
        {
            if (configParam.language != 0)
            {
                configParam.language = 0;
                NeedSave_User_Data();
            }
        }
        break;
        case 1:
        {
            if (configParam.language != 1)
            {
                configParam.language = 1;
                NeedSave_User_Data();
            }
        }
        break;
        }
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
    }
    break;
    }
}
