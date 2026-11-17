#include "setIDui.h"
#include "main.h"

extern const lv_img_dsc_t SetID_Colse_icon;
extern const lv_img_dsc_t SetID_OK_icon;
extern void mavlink_set_sys_msg_send_to_dtu(uint8_t SysID, uint8_t CompID, uint8_t msgid, const char *packet, uint8_t length);

#define FONT_BLOD font_blod_16 //
#define FONT font_16           //

char set_id_buff[8];
char set_id_str[8 + 1] = {0};

const unsigned char *SetIDLanguage1[LanguageMAX] = {
    {"设置的设备ID"},
    {"Set device ID"},
    {"ID устройства"},
};

const unsigned char *SetIDLanguage2[LanguageMAX] = {
    {"设置的设备ID"},
    {"Set device ID"},
    {"ID устройства"},
};

const unsigned char *SetIDLanguage3[LanguageMAX] = {
    {"短按Enter设置"},
    {"Press Enter"},
    {"Нажмите ENTER"},
};

const unsigned char *SetIDLanguage4[LanguageMAX] = {
    {"长按Enter退出"},
    {"Longpress Enter"},
    {"Удерживайте ENTER"},
};

// 设置ID的样式
void set_id_label_style_set(lv_style_t *style)
{
    lv_style_reset(style); // 重置样式释放内存
    lv_style_init(style);
    lv_style_set_border_side(style, LV_BORDER_SIDE_NONE); // 无边框
    // lv_style_set_border_width(style, 0); // 设置边框宽度为2像素
    // lv_style_set_border_color(style, lv_color_make(33,33,33)); // 设置边框颜色为红色
    lv_style_set_bg_opa(style, LV_OPA_COVER); // 设置背景不透明
    lv_style_set_max_width(style, 28);
    lv_style_set_min_width(style, 28);
    lv_style_set_max_height(style, 38);
    lv_style_set_min_height(style, 38);
    lv_style_set_radius(style, 7);
    lv_style_set_bg_color(style, lv_color_make(33, 33, 33));
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    // lv_style_set_text_letter_space(style, 20); // 字符之间的间隔
    lv_style_set_pad_top(style, 10); // 设置上内边距为10像素
                                     // lv_style_set_pad_bottom(style, 10); // 设置下内边距为10像素
    lv_style_set_pad_left(style, 0); // 设置左内边距为5像素
    // lv_style_set_pad_right(style, 5);   // 设置右内边距为5像素
    lv_style_set_outline_width(style, 0); // 轮廓宽度
}

void SetRF_ID_UI_Init(void)
{
    lv_obj_clean(globeGUI.screen);

    lv_obj_t *GetRfID_OBJ_2 = lv_obj_create(globeGUI.screen);
    lv_obj_align(GetRfID_OBJ_2, LV_ALIGN_TOP_RIGHT, -16, 16);                                               // 显示位置
    lv_obj_set_style_border_opa(GetRfID_OBJ_2, LV_OPA_0, LV_STATE_DEFAULT);                                 // 设置边框透明度
    lv_obj_set_style_border_side(GetRfID_OBJ_2, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);                     // 无边框
    lv_obj_set_style_bg_color(GetRfID_OBJ_2, lv_color_hex(0x000000), LV_STATE_DEFAULT);                     // 设置背景颜色为黑色
    lv_obj_set_style_radius(GetRfID_OBJ_2, 0, LV_STATE_DEFAULT);                                            // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(GetRfID_OBJ_2, LV_OBJ_FLAG_SCROLLABLE);                                               // 关闭滚动
    lv_obj_set_size(GetRfID_OBJ_2, 156, 38);                                                                // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_set_flex_flow(GetRfID_OBJ_2, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
    lv_obj_set_flex_align(GetRfID_OBJ_2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐
    lv_obj_set_style_pad_column(GetRfID_OBJ_2, 4, LV_STATE_DEFAULT);                                        // 设置子对象之间的水平间隔为10像素

    sprintf(set_id_str, "%05X", (configParam.RF_ID >> 12) & 0xFFFFF);

    for (uint8_t i = 0; i < 5; i++)
    {
        globeGUI.GetRfID_Label[i] = lv_label_create(GetRfID_OBJ_2);
        lv_obj_set_style_text_font(globeGUI.GetRfID_Label[i], &FONT_BLOD, LV_STATE_DEFAULT);

        lv_label_set_text_fmt(globeGUI.GetRfID_Label[i], "%c", set_id_str[i]);
        if (set_id_str[i] >= '0' && set_id_str[i] <= '9')
        {
            set_id_buff[i] = set_id_str[i] - '0';
        }
        else if (set_id_str[i] >= 'A' && set_id_str[i] <= 'F')
        {
            set_id_buff[i] = set_id_str[i] - 'A' + 10;
        }

        set_id_label_style_set(&globeGUI.my_style);
        lv_obj_add_style(globeGUI.GetRfID_Label[i], &globeGUI.my_style, 0);
    }

    /* 当前设备ID */
    lv_obj_t *GetRfID_Label_1 = lv_label_create(globeGUI.screen);
    lv_obj_align_to(GetRfID_Label_1, GetRfID_OBJ_2, LV_ALIGN_LEFT_MID, -150, 0); // 显示位置
    lv_obj_set_style_text_font(GetRfID_Label_1, &FONT_BLOD, LV_STATE_DEFAULT);
    lv_label_set_text(GetRfID_Label_1, (const char *)SetIDLanguage1[configParam.language]);   // 显示
    lv_obj_set_style_text_color(GetRfID_Label_1, lv_color_hex(0xffffff), LV_STATE_DEFAULT);   // 字体颜色
    const lv_font_t *font = lv_obj_get_style_text_font(GetRfID_Label_1, LV_PART_MAIN);        // 获取标签使用的字体
    const char *text = lv_label_get_text(GetRfID_Label_1);                                    // 获取标签的文本
    lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > 130)
    {
        lv_obj_set_width(GetRfID_Label_1, 130);                                 // 设置最大显示宽度
        lv_label_set_long_mode(GetRfID_Label_1, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(GetRfID_Label_1, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

    /* 设置设备ID */
    lv_obj_t *SetRfID_OBJ_2 = lv_obj_create(globeGUI.screen);
    lv_obj_align(SetRfID_OBJ_2, LV_ALIGN_TOP_RIGHT, -16, 70);                                               // 显示位置
    lv_obj_set_style_border_opa(SetRfID_OBJ_2, LV_OPA_0, LV_STATE_DEFAULT);                                 // 设置边框透明度
    lv_obj_set_style_border_side(SetRfID_OBJ_2, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);                     // 无边框
    lv_obj_set_style_bg_color(SetRfID_OBJ_2, lv_color_hex(0x000000), LV_STATE_DEFAULT);                     // 设置背景颜色为黑色
    lv_obj_set_style_radius(SetRfID_OBJ_2, 0, LV_STATE_DEFAULT);                                            // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(SetRfID_OBJ_2, LV_OBJ_FLAG_SCROLLABLE);                                               // 关闭滚动
    lv_obj_set_size(SetRfID_OBJ_2, 156, 38);                                                                // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_set_flex_flow(SetRfID_OBJ_2, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
    lv_obj_set_flex_align(SetRfID_OBJ_2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐
    lv_obj_set_style_pad_column(SetRfID_OBJ_2, 4, LV_STATE_DEFAULT);                                        // 设置子对象之间的水平间隔为10像素

    for (uint8_t i = 0; i < 5; i++)
    {
        globeGUI.SetRfID_Label[i] = lv_label_create(SetRfID_OBJ_2);
        lv_obj_set_style_text_font(globeGUI.SetRfID_Label[i], &FONT_BLOD, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(globeGUI.SetRfID_Label[i], "%c", set_id_str[i]);
        set_id_label_style_set(&globeGUI.my_style);
        lv_obj_add_style(globeGUI.SetRfID_Label[i], &globeGUI.my_style, 0);
    }
    lv_obj_set_style_bg_color(globeGUI.SetRfID_Label[0], lv_color_make(102, 102, 102), LV_STATE_DEFAULT); // 设置背景颜色

    lv_obj_t *SetRfID_Label_1 = lv_label_create(globeGUI.screen);
    lv_obj_align_to(SetRfID_Label_1, SetRfID_OBJ_2, LV_ALIGN_LEFT_MID, -150, 0); // 显示位置
    lv_obj_set_style_text_font(SetRfID_Label_1, &FONT_BLOD, LV_STATE_DEFAULT);
    lv_label_set_text(SetRfID_Label_1, (const char *)SetIDLanguage2[configParam.language]); // 显示
    lv_obj_set_style_text_color(SetRfID_Label_1, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    font = lv_obj_get_style_text_font(SetRfID_Label_1, LV_PART_MAIN);                       // 获取标签使用的字体
    text = lv_label_get_text(SetRfID_Label_1);                                              // 获取标签的文本
    text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE);          // 计算文本的宽度
    if (text_width > 120)
    {
        lv_obj_set_width(SetRfID_Label_1, 120);                                 // 设置最大显示宽度
        lv_label_set_long_mode(SetRfID_Label_1, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(SetRfID_Label_1, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

    /* 底部提示栏 */
    lv_obj_t *img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &SetID_Colse_icon);
    lv_obj_align(img, LV_ALIGN_BOTTOM_LEFT, 8, -8); // 显示位置

    lv_obj_t *label = lv_label_create(globeGUI.screen);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // 显示位置
    lv_obj_set_style_text_font(label, &FONT, LV_STATE_DEFAULT);
    lv_label_set_text(label, (const char *)SetIDLanguage4[configParam.language]);  // 显示
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);  // 字体颜色
    font = lv_obj_get_style_text_font(label, LV_PART_MAIN);                        // 获取标签使用的字体
    text = lv_label_get_text(label);                                               // 获取标签的文本
    text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > 130)
    {
        lv_obj_set_width(label, 130);                                 // 设置最大显示宽度
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

    img = lv_img_create(globeGUI.screen);
    lv_img_set_src(img, &SetID_OK_icon);
    lv_obj_align(img, LV_ALIGN_BOTTOM_RIGHT, -115, -8); // 显示位置

    label = lv_label_create(globeGUI.screen);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, 5, 0); // 显示位置
    lv_obj_set_style_text_font(label, &FONT, LV_STATE_DEFAULT);
    lv_label_set_text(label, (const char *)SetIDLanguage3[configParam.language]);  // 显示
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);  // 字体颜色
    font = lv_obj_get_style_text_font(label, LV_PART_MAIN);                        // 获取标签使用的字体
    text = lv_label_get_text(label);                                               // 获取标签的文本
    text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE); // 计算文本的宽度
    if (text_width > 130)
    {
        lv_obj_set_width(label, 130);                                 // 设置最大显示宽度
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
    }
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

    globeState.set_id = configParam.RF_ID;
    Debug("set_id_str: %s", set_id_str);
}

void set_id_str_to_id(uint32_t *id, char *id_str)
{
    uint32_t value = 0;
    *id = 0;

    for (int i = 0; i < 5; i++)
    {
        if (id_str[i] >= '0' && id_str[i] <= '9')
        {
            value = id_str[i] - '0';
            value = value << (4 * (7 - i));
            *id |= value;
        }
        else if (id_str[i] >= 'A' && id_str[i] <= 'F')
        {
            value = id_str[i] - 'A' + 10;
            value = value << (4 * (7 - i));
            *id |= value;
        }
    }
    Debug("id: %08X\r\n", *id);
}

void SetRF_ID_Run(void)
{
    static uint8_t E34SetID_Flag = 0;
    static uint8_t E34TimeOutCnt = 0;

    static uint8_t bit_num = 0; // 选择个十百千万的位置
    static uint32_t RF_DelayTick = 0;

    static uint8_t change_rate_flag = 0;

    const char hex_string[] = "0123456789ABCDEF";

    enum dir_e joystick2;
    joystick2 = getJoystick2Dir(0);

    switch (joystick2)
    {
    case BACK: // PITCH向后
        if (set_id_buff[bit_num] == 0)
        {
            set_id_buff[bit_num] = 15;
        }
        else
        {
            set_id_buff[bit_num]--;
        }
        set_id_str[bit_num] = hex_string[set_id_buff[bit_num]];
        lv_label_set_text_fmt(globeGUI.SetRfID_Label[bit_num], "%c", set_id_str[bit_num]);
        set_id_str_to_id((uint32_t *)&globeState.set_id, set_id_str);
        break;

    case FORWARD: // PITCH向前
        set_id_buff[bit_num]++;
        if (set_id_buff[bit_num] > 15)
        {
            set_id_buff[bit_num] = 0;
        }
        set_id_str[bit_num] = hex_string[set_id_buff[bit_num]];
        lv_label_set_text_fmt(globeGUI.SetRfID_Label[bit_num], "%c", set_id_str[bit_num]);
        set_id_str_to_id((uint32_t *)&globeState.set_id, set_id_str);
        break;

    case RIGHT: // ROLL向右
        lv_obj_set_style_bg_color(globeGUI.SetRfID_Label[bit_num], lv_color_make(33, 33, 33), LV_STATE_DEFAULT);
        bit_num++;
        if (bit_num > 4)
        {
            bit_num = 0;
        }
        lv_obj_set_style_bg_color(globeGUI.SetRfID_Label[bit_num], lv_color_make(102, 102, 102), LV_STATE_DEFAULT);
        break;

    case LEFT:                                                                                                   // ROLL向左
        lv_obj_set_style_bg_color(globeGUI.SetRfID_Label[bit_num], lv_color_make(33, 33, 33), LV_STATE_DEFAULT); // 设置背景颜色
        if (bit_num == 0)
        {
            bit_num = 4;
        }
        else
        {
            bit_num--;
        }
        lv_obj_set_style_bg_color(globeGUI.SetRfID_Label[bit_num], lv_color_make(102, 102, 102), LV_STATE_DEFAULT); // 设置背景颜色
        break;

    default:
        break;
    }

    if (keyIsValue(Key_OK, short_release))
    {
        E34SetID_Flag = 1;
        E34TimeOutCnt = 0;
    }

    if (E34SetID_Flag && GetTimeInterval(RF_DelayTick, GetSysTick()) >= 100)
    {
        RF_DelayTick = GetSysTick();

        if (globeState.SetNameOK)
        {
            E34SetID_Flag = 0;
            E34TimeOutCnt = 0;
            bit_num = 0;

            globeState.SetNameOK = 0;
            Debug("Set_Connect_WiFi_Name OK");
            Debug("configParam.RF_ID: %08X", configParam.RF_ID);
            Debug("globeState.set_id: %08X", globeState.set_id);

            if (configParam.RF_ID != globeState.set_id)
            {
                configParam.RF_ID = globeState.set_id;
                RF_Power_DIS;
                NeedSave_User_Data();
            }
            if (change_rate_flag)
            {
                rf_uart3_init(1500000);
                change_rate_flag = 0;
            }

            lv_obj_clean(globeGUI.screen);
            lv_obj_t *img = lv_img_create(globeGUI.screen);
            lv_img_set_src(img, &Check_img);
            lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
            // lv_img_set_zoom(img, 256 * 4);
            lvgl_force_refresh();
            delay_ms(1000);

            RF_Power_EN;
            set_show_ui(MENU_UI);

            return;
        }

        globeState.SetNameOK = 0;
        S_SetWirelessName_Msg SetWirelessName_Msg;
        SetWirelessName_Msg.type = 2;
        strcpy(SetWirelessName_Msg.name, set_id_str);
        mavlink_set_sys_msg_send_to_dtu(DTU_SONAR_SYS_ID, REMOTE_DTU_COMP_ID, SetWirelessName_Msg_ID, (char *)&SetWirelessName_Msg, sizeof(S_SetWirelessName_Msg));
        Debug("set_id_str: %s", set_id_str);

        E34TimeOutCnt++;
        if (E34TimeOutCnt == 10)
        {
            rf_uart3_init(57600);
            change_rate_flag = 1;
        }
        if (E34TimeOutCnt > 20)
        {
            E34SetID_Flag = 0;
            E34TimeOutCnt = 0;
            bit_num = 0;
            if (change_rate_flag)
            {
                rf_uart3_init(1500000);
                change_rate_flag = 0;
            }

            Debug("Set ID ERROR");
            lv_obj_clean(globeGUI.screen);
            lv_obj_t *img = lv_img_create(globeGUI.screen);
            lv_img_set_src(img, &Colse_img);
            lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
            // lv_img_set_zoom(img, 256 * 4);
            lvgl_force_refresh();
            delay_ms(1000);

            set_show_ui(MENU_UI);
        }
    }

    if (keyIsValue(Key_OK, long_pass))
    {
        E34SetID_Flag = 0;
        E34TimeOutCnt = 0;
        bit_num = 0;
        if (change_rate_flag)
        {
            rf_uart3_init(1500000);
            change_rate_flag = 0;
        }

        set_show_ui(MENU_UI);
    }
}
