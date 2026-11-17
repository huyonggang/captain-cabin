#include "main_ui.h"
#include "main.h"

GLOBE_GUI globeGUI = {0};
S_PopUp globePopUp = {0};
S_PopUp LastglobePopUp = {0};
S_Task_Set_Animation Task_Set_Animation;

const lv_img_dsc_t *const PopUp_Img_Buff[IMG_ID_MAX][2] = {
    // {
    //     &spot_1,
    //     &spot_1,
    // },
    // {
    //     &spot_2,
    //     &spot_2,
    // },
    // {
    //     &spot_3,
    //     &spot_3,
    // },
    // {
    //     &spot_4,
    //     &spot_4,
    // },
    // {
    //     &spot_5,
    //     &spot_5,
    // },
    // {
    //     &spot_6,
    //     &spot_6,
    // },
    // {
    //     &spot_7,
    //     &spot_7,
    // },
    // {
    //     &spot_8,
    //     &spot_8,
    // },
    // {
    //     &spot_9,
    //     &spot_9,
    // },
    // {
    //     &spot_10,
    //     &spot_10,
    // },
    // {
    //     &spot_11,
    //     &spot_11,
    // },
    // {
    //     &spot_12,
    //     &spot_12,
    // },
    // {
    //     &spot_13,
    //     &spot_13,
    // },
    // {
    //     &spot_14,
    //     &spot_14,
    // },
    // {
    //     &spot_15,
    //     &spot_15,
    // },
    // {
    //     &spot_16,
    //     &spot_16,
    // },
    // {
    //     &spot_17,
    //     &spot_17,
    // },
    // {
    //     &spot_18,
    //     &spot_18,
    // },
    // {
    //     &spot_19,
    //     &spot_19,
    // },
    // {
    //     &spot_20,
    //     &spot_20,
    // },

    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &spot_task,
        &spot_task,
    },
    {
        &pointA_48_48,
        &PointA_80_80,
    },
    {
        &pointB_48_48,
        &PointB_80_80,
    },
    {
        &PointC_48_48,
        &PointC_80_80,
    },
    {
        &PointD_48_48,
        &PointD_80_80,
    },
    {
        &Homepoint48_48,
        &Homepoint,
    },
    {
        &SetID_OK_icon,
        &Check_img,
    },
    {
        &SetID_Colse_icon,
        &Colse_img,
    },
    {
        &SaveA_icon,
        &PointA_80_80,
    },
    {
        &SaveB_icon,
        &PointB_80_80,
    },
    {
        &SaveC_icon,
        &PointC_80_80,
    },
    {
        &SaveD_icon,
        &PointD_80_80,
    },
    {
        &home,
        &home,
    },
    {
        &NoSaveA_icon,
        &spot_a_green_l,
    },
    {
        &NoSaveB_icon,
        &spot_b_green_l,
    },
    {
        &NoSaveC_icon,
        &spot_c_green_l,
    },
    {
        &NoSaveD_icon,
        &spot_d_green_l,
    },
    {
        &Attention,
        &Attention,
    },
    {
        &rocker_1,
        &rocker_1,
    },
    {
        &lowpower_img,
        &lowpower_img,
    },
    {
        &SaveA_icon,
        &SaveA_icon,
    },
    {
        &SaveB_icon,
        &SaveB_icon,
    },
    {
        &SaveC_icon,
        &SaveC_icon,
    },
    {
        &SaveD_icon,
        &SaveD_icon,
    },
    {
        &home,
        &home,
    },
    {
        &continue_img,
        &continue_img,
    },
    {
        &reposition,
        &reposition,
    },
    {
        &Circle,
        &Circle,
    },
    {
        &Trash,
        &Trash,
    },
    {
        &speed_low,
        &speed_low,
    },
    {
        &speed_medium,
        &speed_medium,
    },
    {
        &speed_high,
        &speed_high,
    },
    {
        &icon_alert_s,
        &icon_alert_xl,
    },
};

const lv_img_dsc_t *const LVGL_Img_Buff[MAIN_UI_ID_MAX] = {
    &CatchX_BS_ch,
    &CatchX_BS,
    &Rogue_SparkMax_cn,
    &Rogue_SparkMax,
    &CATCHX_ULTRA_CH_ICON,
    &CATCHX_ULTRA_ICON,
    &SaveA_icon,
    &NoSaveA_icon,
    &SaveB_icon,
    &NoSaveB_icon,
    &SaveC_icon,
    &NoSaveC_icon,
    &SaveD_icon,
    &NoSaveD_icon,
    &light_icon,
    &icon_charging,
    &signal05,
    &signal00,
    &satellite,
    &Compass,
    &navigation,
    &arrow1_icon,
    &arrow2_icon,
    &ghost_icon,
    &ghost_max_icon1,
    &ghost_max_icon2,
};

const char *PopUpLanguage[Language_ID_MAX][LanguageMAX] = {
    {
        "A点",
        "Point A",
        "для установки точки A",
    },
    {
        "B点",
        "Point B",
        "для установки точки B",
    },
    {
        "C点",
        "Point C",
        "для установки точки C",
    },
    {
        "D点",
        "Point D",
        "для установки точки D",
    },
    {
        "设置A点",
        "to Set A",
        "для установки точки A",
    },
    {
        "设置B点",
        "to Set B",
        "для установки точки B",
    },
    {
        "设置C点",
        "to Set C",
        "для установки точки C",
    },
    {
        "设置D点",
        "to Set D",
        "для установки точки D",
    },
    {
        "设置返航点",
        "to Set Homepoint",
        "для установки точки Home",
    },
    {
        "A点设置成功",
        "Point A Set success",
        "для установки точки Home",
    },
    {
        "B点设置成功",
        "Point B Set success",
        "для установки точки Home",
    },
    {
        "C点设置成功",
        "Point C Set success",
        "для установки точки Home",
    },
    {
        "D点设置成功",
        "Point D Set success",
        "для установки точки Home",
    },
    {
        "返航点设置成功",
        "Homepoint Set success",
        "для установки точки Home",
    },
    {
        "A点设置失败",
        "Point A Set fail",
        "для установки точки Home",
    },
    {
        "B点设置失败",
        "Point B Set fail",
        "для установки точки Home",
    },
    {
        "C点设置失败",
        "Point C Set fail",
        "для установки точки Home",
    },
    {
        "D点设置失败",
        "Point D Set fail",
        "для установки точки Home",
    },
    {
        "返航点设置失败",
        "Homepoint Set fail",
        "для установки точки Home",
    },
    {
        "设置成功",
        "Set success",
        "Установка выполнена успешно",
    },
    {
        "设置失败",
        "Set fail",
        "Установка не удалась",
    },
    {
        "到达任务点A",
        "Arrived at A",
        "Достигнута точка A",
    },
    {
        "到达任务点B",
        "Arrived at B",
        "Достигнута точка B",
    },
    {
        "到达任务点C",
        "Arrived at C",
        "Достигнута точка C",
    },
    {
        "到达任务点D",
        "Arrived at D",
        "Достигнута точка D",
    },
    {
        "到达返航点",
        "Homepoint reached",
        "Достигнута точка Home",
    },
    {
        "到达任务点",
        "Arrived at the task point",
        "Достигнута точка App",
    },
    {
        "开始定速巡航",
        "Cruise control engaged",
        "Круиз-контроль установлен",
    },
    {
        "定速巡航失败",
        "Cruise control failed",
        "Круиз-контроль не установлен",
    },
    {
        "抛仓成功",
        "Successful drop",
        "Успешное выбрасывание",
    },
    {
        "抛仓失败",
        "Failed drop",
        "Неудачное выбрасывание",
    },
    {
        "正在发送RTH指令",
        "RTH command...",
        "Команда RTL выполнена...",
    },
    {
        "指令成功",
        "command success",
        "выполнена успешно",
    },
    {
        "退出自动驾驶",
        "Exit autopilot",
        "выполнена успешно",
    },
    {
        "退出电子锚？",
        "Exit anchor?",
        "выполнена успешно",
    },
    {
        "中止任务？",
        "Abort the task?",
        "Прекратить задачу?",
    },
    {
        "任务已中止",
        "Aborted",
        "Задача отменена",
    },
    {
        "中止任务失败",
        "Abort failed",
        "Отмена не удалась",
    },
    {
        "退出失败",
        "exit fail?",
        "выполнена успешно",
    },
    {
        "退出成功",
        "exit success",
        "выполнена успешно",
    },
    {
        "正在发送任务指令",
        "Sending task instructions",
        "выполнена успешно",
    },
    {
        "手动",
        "Manual",
        "выполнена успешно",
    },
    {
        "自动驾驶",
        "Autopilot",
        "выполнена успешно",
    },
    {
        "设备未连接",
        "Disconnected",
        "выполнена успешно",
    },
    {
        "水平校准中...",
        "Calibration...",
        "выполнена успешно",
    },
    {
        "校准成功",
        "Calibration completed",
        "выполнена успешно",
    },
    {
        "校准失败",
        "Calibration failed",
        "выполнена успешно",
    },
    {
        "任务已执行",
        "The task is executed",
        "выполнена успешно",
    },
    {
        "命令执行失败",
        "Command execution failed",
        "выполнена успешно",
    },
    {
        "遥控器电量低！",
        "The remote control is low on power!",
        "выполнена успешно",
    },
    {
        "短按Enter键",
        "Press ENTER",
        "Нажмите ENTER",
    },
    {
        "长按Enter键",
        "Longpass ENTER",
        "Нажмите ENTER",
    },
    {
        "松开Enter取消",
        "Release Enter to cancel",
        "Нажмите ENTER",
    },
    {
        "松开按键取消",
        "Release button to cancel",
        "Отпускай и отпускай",
    },
    {
        "继续出发",
        "Continue to depart",
        "Продолжайте миссию",
    },
    {
        "请连接App使用",
        "Please connect to the app for use",
        "Продолжайте миссию",
    },
    {
        "纠偏成功",
        "Correction successful",
        "Коррекция успешна",
    },
    {
        "纠偏失败",
        "Correction failed",
        "Коррекция успешна",
    },
    {
        "任务执行中,不可设置",
        "Unable to set during the mission",
        "Нельзя установить",
    },
    {
        "正在执行扫描任务...",
        "Executing scanning task...",
        "Нельзя установить...",
    },
    {
        "任务中不可执行",
        "Not execute during the task",
        "Нельзя установить...",
    },
    {
        "正在发送 RTH 指令",
        "RTH command...",
        "Нельзя установить...",
    },
    {
        "未设置任务点",
        "No mission point was set",
        "Нельзя установить...",
    },
    {
        "请先选择任务点",
        "Select a task point",
        "Нельзя установить...",
    },
    {
        "执行任务",
        "Perform the task",
        "Нельзя установить...",
    },
    {
        "抛钩成功",
        "Successful hook release",
        "Нельзя установить...",
    },
    {
        "抛钩失败",
        "Failed hook release",
        "Нельзя установить...",
    },
    {
        "抛仓、抛钩成功",
        "Successful drop and hook release",
        "Нельзя установить...",
    },
    {
        "抛仓、抛钩失败",
        "Failed drop and hook release",
        "Нельзя установить...",
    },
    {
        "距离参照点过远, 纠偏失败",
        "Too far from the reference point",
        "Нельзя установить...",
    },
    {
        "请连接App获取参照点",
        "Get the reference point from app",
        "Нельзя установить...",
    },
    {
        "已获取参照点",
        "Reference point acquired",
        "Нельзя установить...",
    },
    {
        "参照点已清除",
        "Reference point cleared",
        "Нельзя установить...",
    },
    {
        "剩余: ",
        "Remaining: ",
        "Remaining: ",
    },
    {
        "分钟",
        "min",
        "min",
    },
    {
        "小于",
        "less than ",
        "less than ",
    },
    {
        "探索模式",
        "Explore mode",
        "Explore mode",
    },
    {
        "省电模式",
        "Lowpower mode",
        "Lowpower mode",
    },
    {
        "运动模式",
        "Movement mode",
        "Movement mode",
    },
    {
        "卫星数需 >13",
        "Number of satellites needs to be >13",
        "Number of satellites needs to be >13",
    },
    {
        "船电量低！",
        "Boat power is low!",
        "выполнена успешно",
    },
    {
        "退出任务光束",
        "Stop Transmission",
        "Stop Transmission",
    },
    {
        "退出后可执行任务光束",
        "Transmission can be executed after exit",
        "Transmission can be executed after exit",
    },
    {
        "已开启幽灵模式",
        "Ghost mode has been activated",
        "Ghost mode has been activated",
    },
    {
        "电驱保护中, 请稍后尝试操作",
        "Protection active. Try later",
        "Электрическая защита привода, повторите попытку позже",
    },
    {
        "电机异常提示\n可能存在水草或异物缠绕风险",
        "Motor Abnormal Alert\nPossible debris entanglement",
        "Motor Abnormal Alert\nPossible debris entanglement",
    },
    {
        "电机堵转提示\n检测到电机严重堵转, 动力输出已停止",
        "Motor Stall Alert\nStall detected. Power stopped",
        "Motor Stall Alert\nStall detected. Power stopped",
    },
    {
        "电驱保护中",
        "Drive protection active",
        "Drive protection active",
    },
    {
        "动力输出已停止, 请1分钟后尝试",
        "Power output stopped. Retry in 1 min",
        "Power output stopped. Retry in 1 min",
    },
    {
        "电驱保护中\n动力输出已停止, 请1分钟后尝试",
        "Drive protection active\nPower stopped. Retry in 1 min",
        "Drive protection active\nPower stopped. Retry in 1 min",
    },
    {
        "“已退出电驱保护，请再次尝试操作",
        "Electric drive protection off.Retry",
        "Electric drive protection off.Retry",
    },
};

void my_img_set_zoom(const lv_img_dsc_t *img, float *scale, float img_size, int16_t *x_pos, int16_t *y_pos)
{
    float scale_width = img_size / img->header.h;
    float scale_height = img_size / img->header.w;
    *scale = (scale_width < scale_height) ? scale_width : scale_height;
    // 获取缩放后的图像宽高
    uint16_t scaled_width = (uint16_t)(img->header.w * *scale);
    uint16_t scaled_height = (uint16_t)(img->header.h * *scale);
    *x_pos = (img->header.w - scaled_width) / 2;
    *y_pos = (img->header.h - scaled_height) / 2;
}

static void popup_time_call_back(lv_timer_t *timer)
{
    S_PopUp *PopUpValue = (S_PopUp *)timer->user_data;

    if (PopUpValue->bar)
    {
        lv_bar_set_value(PopUpValue->bar, PopUpValue->BarValue += 5, LV_ANIM_ON); /* 设置进度条当前值 */
    }
    else
    {
        if (!(--PopUpValue->CallBackCount))
        {
            lv_show_popup_del();
            // Debug("lv_show_popup_del");
            return;
        }

        if (PopUpValue->label_3 && PopUpValue->Count_Down)
        {
            lv_label_set_text_fmt(PopUpValue->label_3, "%ds", PopUpValue->CallBackCount);
        }
    }
}

void lv_show_popup_del(void)
{
    if (globePopUp.PopUp_obj)
    {
        lv_obj_del(globePopUp.PopUp_obj);
        globePopUp.PopUp_obj = NULL;
        Task_Set_Animation.panel = NULL;
        // Task_Set_Animation.item_cut = 0;
        Task_Set_Animation.zoom_value = 0;
    }
    if (globePopUp.PopUpTime)
    {
        lv_timer_del(globePopUp.PopUpTime); // 删除倒计时任务
        globePopUp.PopUpTime = NULL;
    }
    if (Task_Set_Animation.animation_time)
    {
        lv_timer_del(Task_Set_Animation.animation_time);
        Task_Set_Animation.animation_time = NULL;
    }

    memset(&globePopUp, 0, sizeof(S_PopUp));
    memset(&LastglobePopUp, 0, sizeof(S_PopUp));
    memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);

    if (globeGUI.task_num_img)
    {
        lv_obj_clear_flag(globeGUI.task_num_img, LV_OBJ_FLAG_HIDDEN);
    }

    if (globeGUI.Anchor_obj)
    {
        lv_obj_clear_flag(globeGUI.Anchor_obj, LV_OBJ_FLAG_HIDDEN);
    }

    LED_TaskA_Pin = LED_OFF;
}

/*
    img + str1
       str2
       str3
*/
void popup_init(lv_img_dsc_t *img, char *str1, char *str2, char *str3, uint16_t Show_Time, uint8_t PopUpSize)
{
    S_PopUp PopUpValue;

    memset(&PopUpValue, 0, sizeof(PopUpValue));

    PopUpValue.img = img;
    PopUpValue.PopUpStr1 = str1;
    PopUpValue.PopUpStr2 = str2;
    PopUpValue.PopUpStr3 = str3;
    PopUpValue.TimePeriod = POPUP_TIMEPERIOD;
    PopUpValue.CallBackCount = Show_Time / POPUP_TIMEPERIOD;
    PopUpValue.PopUpSize = PopUpSize;

    PopUpValue.Str1_Font[0] = &font_blod_16;
    PopUpValue.Str1_Font[1] = &font_blod_16;
    // PopUpValue.Str2_Font[0] = &font_blod_22;
    PopUpValue.Str2_Font[0] = &font_blod_16;
    PopUpValue.Str2_Font[1] = &font_blod_34;
    PopUpValue.Str3_Font[0] = &font_blod_16;
    PopUpValue.Str3_Font[1] = &font_blod_16;

    lv_show_popup_init1(&PopUpValue);
}

static void task_animation_time_callback(lv_timer_t *timer)
{
    static uint8_t left_or_right = 1;
    if (Task_Set_Animation.item_cut == (configParam.AB_Mode ? 3 : 1) && Task_Set_Animation.last_item_cut == 0)
    {
        left_or_right = 0;
    }
    else if (Task_Set_Animation.item_cut == 0 && Task_Set_Animation.last_item_cut == (configParam.AB_Mode ? 3 : 1))
    {
        left_or_right = 1;
    }
    else if (Task_Set_Animation.item_cut > Task_Set_Animation.last_item_cut)
    {
        left_or_right = 1;
    }
    else if (Task_Set_Animation.item_cut < Task_Set_Animation.last_item_cut)
    {
        left_or_right = 0;
    }

    int last_item = Task_Set_Animation.last_item_cut;
    Task_Set_Animation.zoom_value += 15;
    if (Task_Set_Animation.zoom_value > 100)
    {
        Task_Set_Animation.zoom_value = 0;
        lv_timer_del(Task_Set_Animation.animation_time); // 删除倒计时任务
        Task_Set_Animation.animation_time = NULL;
        // lv_group_focus_obj(Task_Set_Animation.buttons[Task_Set_Animation.item_cut]);
        // lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, 0, -40);
        Debug("lv_timer_del\r\n");
        return;
    }
    // lv_obj_scroll_to_x(Task_Set_Animation.panel, 117.0f - 32.0f * Task_Set_Animation.zoom_value / 100.0f, LV_ANIM_ON); // 没效果
    lv_obj_set_size(Task_Set_Animation.buttons[last_item], 80.0f - ((80.0f - 32.0f) * Task_Set_Animation.zoom_value / 100.0f), 80.0f - (80.0f - 32.0f) * Task_Set_Animation.zoom_value / 100.0f);                   // 缩小
    lv_obj_set_size(Task_Set_Animation.buttons[Task_Set_Animation.item_cut], 32.0f + ((80.0f - 32.0f) * Task_Set_Animation.zoom_value / 100.0f), 32.0f + (80.0f - 32.0f) * Task_Set_Animation.zoom_value / 100.0f); // 放大
    lv_img_set_zoom(Task_Set_Animation.img[last_item], (1.0f - (1.0f - 0.43f) * Task_Set_Animation.zoom_value / 100.0f) * 256.0f);                                                                                  // 缩小
    lv_img_set_zoom(Task_Set_Animation.img[Task_Set_Animation.item_cut], (0.43f + (1.0f - 0.43f) * Task_Set_Animation.zoom_value / 100.0f) * 256.0f);                                                               // 放大
    lv_obj_set_style_opa(Task_Set_Animation.img[last_item], 255.0f - ((255.0f - 128.0f) * Task_Set_Animation.zoom_value / 100.0f), LV_STATE_DEFAULT);
    lv_obj_set_style_opa(Task_Set_Animation.img[Task_Set_Animation.item_cut], 127.0f + ((255.0f - 128.0f) * Task_Set_Animation.zoom_value / 100.0f), LV_STATE_DEFAULT);

    if (left_or_right || !configParam.AB_Mode)
    {
        if (globeState.Task_Set_X)
        {
            if (last_item == (configParam.AB_Mode ? 3 : 1))
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, -25 + 16 + (-32.0f * (configParam.AB_Mode ? 3 : 1)) + 32.0f * (configParam.AB_Mode ? 3 : 1) * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
            else
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, -25 + (-32.0f * last_item) - 32.0f * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
        }
        else
        {
            if (last_item == (configParam.AB_Mode ? 3 : 1))
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, 16 + (-32.0f * (configParam.AB_Mode ? 3 : 1)) + 32.0f * (configParam.AB_Mode ? 3 : 1) * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
            else
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, (-32.0f * last_item) - 32.0f * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
        }
    }
    else
    {
        if (globeState.Task_Set_X)
        {
            if (last_item == 0)
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, -25 - 16 - 32.0f * (configParam.AB_Mode ? 3 : 1) * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
            else
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, -25 + 10 + (-32.0f * last_item) + 32.0f * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
        }
        else
        {
            if (last_item == 0)
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, -16 - 32.0f * (configParam.AB_Mode ? 3 : 1) * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
            else
            {
                lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, 10 + (-32.0f * last_item) + 32.0f * Task_Set_Animation.zoom_value / 100.0f, -40);
            }
        }
    }
    // lv_group_focus_obj(Task_Set_Animation.buttons[1]); // 将焦点设置到第二个按钮
}

void task_set_animation_init(lv_obj_t *obj)
{
    float scale = 0;
    if (Task_Set_Animation.panel)
    {
        if (Task_Set_Animation.animation_time == NULL)
        {
            memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);
            ((uint8_t *)&globeState.Task_Sta.GetPosA_En)[Task_Set_Animation.item_cut] = 1;
            Task_Set_Animation.animation_time = lv_timer_create(task_animation_time_callback, 1, NULL);
        }
        // lv_group_focus_obj(Task_Set_Animation.buttons[item]); // 将焦点设置到第二个按钮
        // printf("%d\r\n", lv_obj_get_scroll_x(Task_Set_Animation.panel));
        return;
    }
    Task_Set_Animation.panel = lv_obj_create(obj);
    lv_obj_set_style_bg_color(Task_Set_Animation.panel, lv_color_make(0, 0, 0x00), 0); // 设置屏幕背景为黑色
    lv_obj_set_style_border_width(Task_Set_Animation.panel, 0, 0);                     // 第三个参数为状态，0表示所有状态
    lv_obj_set_size(Task_Set_Animation.panel, LCD_W, 80);
    lv_obj_set_scroll_snap_x(Task_Set_Animation.panel, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(Task_Set_Animation.panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(Task_Set_Animation.panel, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END); // 在所有方向上居中对齐
    if (Task_Set_Animation.item_cut)
    {
        globeState.Task_Set_X = 1;
        lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, Task_Set_Animation.item_cut * -32 - 22, -40);
    }
    else
    {
        globeState.Task_Set_X = 0;
        lv_obj_align(Task_Set_Animation.panel, LV_ALIGN_CENTER, 0, -40);
    }
    // lv_obj_set_scrollbar_mode(Task_Set_Animation.panel, LV_SCROLLBAR_MODE_OFF);          // 隐藏滚动条
    lv_obj_clear_flag(Task_Set_Animation.panel, LV_OBJ_FLAG_SCROLLABLE); // 关闭滚动
    lv_obj_set_style_pad_column(Task_Set_Animation.panel, 0, 0);
    lv_obj_set_style_pad_top(Task_Set_Animation.panel, 30, 0);
    lv_obj_set_style_pad_bottom(Task_Set_Animation.panel, 0, 0);

    // Task_Set_Animation.group = lv_group_create(); // 创建一个组 lv_group_del
    for (uint32_t i = 0; i < (configParam.AB_Mode ? 4 : 2); i++)
    {
        Task_Set_Animation.buttons[i] = lv_btn_create(Task_Set_Animation.panel);
        lv_obj_set_style_outline_width(Task_Set_Animation.buttons[i], 0, LV_STATE_FOCUS_KEY); // 第三个参数为状态，0表示所有状态
        lv_obj_set_style_border_width(Task_Set_Animation.buttons[i], 0, LV_STATE_FOCUS_KEY);  // 第三个参数为状态，0表示所有状态
        lv_obj_set_style_bg_color(Task_Set_Animation.buttons[i], lv_color_black(), 0);        // 设置屏幕背景为黑色
        lv_obj_set_style_shadow_width(Task_Set_Animation.buttons[i], 0, 0);
        Task_Set_Animation.img[i] = lv_img_create(Task_Set_Animation.buttons[i]); // 将图像添加到按钮中
        lv_obj_set_style_pad_bottom(Task_Set_Animation.buttons[i], 10, 0);

        if (((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_lat &&
            ((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_long)
        {
            lv_img_set_src(Task_Set_Animation.img[i], PopUp_Img_Buff[SetPointA_IMG_ID + i][1]); // 设置图像源
        }
        else
        {
            lv_img_set_src(Task_Set_Animation.img[i], PopUp_Img_Buff[_SetPointA_IMG_ID + i][1]); // 设置图像源
        }

        if (i == Task_Set_Animation.item_cut)
        {
            lv_obj_set_size(Task_Set_Animation.buttons[Task_Set_Animation.item_cut], 80, 80); // 每个按钮宽度为150
            lv_img_set_zoom(Task_Set_Animation.img[i], 256);
            lv_obj_set_style_opa(Task_Set_Animation.img[i], LV_OPA_100, 0);
        }
        else
        {
            lv_obj_set_size(Task_Set_Animation.buttons[i], 32, 32);                                                 // 每个按钮宽度为150
            my_img_set_zoom(PopUp_Img_Buff[SetPointA_IMG_ID + i][1], &scale, 32, &globeGUI.x_pos, &globeGUI.y_pos); /* 限制图片大小 */
            lv_img_set_zoom(Task_Set_Animation.img[i], scale * 256);
            lv_obj_set_style_opa(Task_Set_Animation.img[i], LV_OPA_50, 0);
            // Debug("scale: %1.2f", scale);
        }
        lv_obj_align(Task_Set_Animation.img[i], LV_ALIGN_CENTER, 0, 0); // 将图像居中对齐
        // lv_group_add_obj(Task_Set_Animation.group, Task_Set_Animation.buttons[i]); // 将按钮添加到组中
    }
    // lv_obj_scroll_to_x(Task_Set_Animation.panel, 107, LV_ANIM_ON);
    lv_obj_update_snap(Task_Set_Animation.panel, LV_ANIM_ON);
    // lv_group_focus_obj(Task_Set_Animation.buttons[Task_Set_Animation.item_cut]); // 设置焦点

    memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);
    ((uint8_t *)&globeState.Task_Sta.GetPosA_En)[Task_Set_Animation.item_cut] = 1;
}

void lv_show_popup_init(S_PopUp *PopUp_)
{
#ifndef OLD_SET_POINT_UI
    const char *BelowLanguage[3][LanguageMAX] = {
        {
            "设点",
            "Set",
            "Set",
        },
        {
            "切换点",
            "Switch",
            "Switch",
        },
        {
            "开始",
            "Go",
            "Go",
        },
    };
#endif

    S_PopUp *PopUpValue = &globePopUp;

    if (PopUpValue->PopUp_obj && Task_Set_Animation.panel)
    {
        PopUpValue->PopUpStr1 = PopUp_->PopUpStr1;
        PopUpValue->PopUpStr2 = PopUp_->PopUpStr2;
        PopUpValue->PopUpStr3 = PopUp_->PopUpStr3;
        task_set_animation_init(PopUpValue->PopUp_obj);
        lv_label_set_text(PopUpValue->label_1, (const char *)PopUpValue->PopUpStr1);
#ifdef OLD_SET_POINT_UI
        lv_label_set_text(PopUpValue->label_2, (const char *)PopUpValue->PopUpStr2);
#endif
        lv_label_set_text(PopUpValue->label_3, (const char *)PopUpValue->PopUpStr3);
        if (PopUpValue->PopUpTime)
        {
            lv_timer_del(PopUpValue->PopUpTime); // 删除倒计时任务
        }

        if (PopUpValue->TimePeriod)
        {
            PopUpValue->CallBackCount = 6;
            PopUpValue->PopUpTime = lv_timer_create(popup_time_call_back, PopUpValue->TimePeriod, PopUpValue);
        }

        // Debug("task_set_animation_init");
        return;
    }

    if (PopUpValue->PopUp_obj)
    {
        lv_show_popup_del();
    }

    memcpy(PopUpValue, PopUp_, sizeof(S_PopUp));

    /* 所有对象的obj*/
    PopUpValue->PopUp_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(PopUpValue->PopUp_obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(PopUpValue->PopUp_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(PopUpValue->PopUp_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(PopUpValue->PopUp_obj, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(PopUpValue->PopUp_obj, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
#ifndef OLD_SET_POINT_UI
    lv_obj_set_size(PopUpValue->PopUp_obj, LCD_W, LCD_H); // 容器宽度为屏幕宽度，高度根据内容确定
#else
    lv_obj_set_size(PopUpValue->PopUp_obj, LV_PCT(100), LV_SIZE_CONTENT); // 容器宽度为屏幕宽度，高度根据内容确定
#endif
                                                          // lv_obj_set_flex_flow(PopUpValue->PopUp_obj, LV_FLEX_FLOW_COLUMN);                                               // 设置为水平布局
    // lv_obj_set_flex_align(PopUpValue->PopUp_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    task_set_animation_init(PopUpValue->PopUp_obj);

    if (PopUpValue->PopUpStr1)
    {
        PopUpValue->label_1 = lv_label_create(PopUpValue->PopUp_obj);
        lv_obj_set_style_text_font(PopUpValue->label_1, PopUpValue->Str1_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_1, (const char *)PopUpValue->PopUpStr1);                //
        lv_obj_set_style_text_color(PopUpValue->label_1, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        const lv_font_t *font = lv_obj_get_style_text_font(PopUpValue->label_1, LV_PART_MAIN);      // 获取标签使用的字体
        const char *text = lv_label_get_text(PopUpValue->label_1);                                  // 获取标签的文本
        lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE);   // 计算文本的宽度
        if (text_width > LCD_W - 60)
        {
            lv_obj_set_size(PopUpValue->obj_Str1_label_1, LCD_W, 76);
            lv_obj_set_size(PopUpValue->label_1, LCD_W / 2, 66);             // 设置最大显示宽度
            lv_label_set_long_mode(PopUpValue->label_1, LV_LABEL_LONG_WRAP); // 字符串超过了最大宽度换行显示
        }
        lv_obj_set_style_text_align(PopUpValue->label_1, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

#ifndef OLD_SET_POINT_UI
        lv_obj_align(PopUpValue->label_1, LV_ALIGN_CENTER, 0, 20);
#else
        lv_obj_align(PopUpValue->label_1, LV_ALIGN_CENTER, 0, 70);
#endif
    }

    if (PopUpValue->PopUpStr2)
    {
#ifdef OLD_SET_POINT_UI
        PopUpValue->label_2 = lv_label_create(PopUpValue->PopUp_obj);
        lv_label_set_text(PopUpValue->label_2, (const char *)PopUpValue->PopUpStr2);                // 完成校准
        lv_obj_set_style_text_color(PopUpValue->label_2, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_set_width(PopUpValue->label_2, LCD_W);                                               // 设置最大显示宽度
        lv_label_set_long_mode(PopUpValue->label_2, LV_LABEL_LONG_SCROLL_CIRCULAR);                 // 字符串超过了最大宽度滚动显示
        lv_obj_set_style_text_align(PopUpValue->label_2, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);   // 字符串居中显示
        lv_obj_set_style_text_font(PopUpValue->label_2, PopUpValue->Str2_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
        lv_obj_align_to(PopUpValue->label_2, PopUpValue->label_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10); // 显示位置
        lv_obj_align(PopUpValue->label_1, LV_ALIGN_CENTER, 0, 17);
#else
        PopUpValue->obj_below = lv_obj_create(PopUpValue->PopUp_obj);
        lv_obj_set_style_border_opa(PopUpValue->obj_below, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
        lv_obj_set_style_border_side(PopUpValue->obj_below, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
        lv_obj_set_style_bg_color(PopUpValue->obj_below, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
        lv_obj_set_style_radius(PopUpValue->obj_below, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
        lv_obj_clear_flag(PopUpValue->obj_below, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
        lv_obj_set_size(PopUpValue->obj_below, LCD_W, 30);                                          // 容器宽度为屏幕宽度，高度根据内容确定
        // lv_obj_set_flex_flow(PopUpValue->obj_below, LV_FLEX_FLOW_ROW);                              // 设置为水平布局
        // lv_obj_set_flex_align(PopUpValue->obj_below, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐
        lv_obj_align_to(PopUpValue->obj_below, PopUpValue->label_1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10); // 显示位置

        PopUpValue->img_enter = lv_img_create(PopUpValue->obj_below);
        lv_img_set_src(PopUpValue->img_enter, &enter_img);
        lv_obj_align(PopUpValue->img_enter, LV_ALIGN_LEFT_MID, -10, 0);
        PopUpValue->label_enter = lv_label_create(PopUpValue->obj_below);
        lv_obj_set_style_text_font(PopUpValue->label_enter, &font_18, LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_enter, (const char *)BelowLanguage[0][configParam.language]);
        lv_obj_set_style_text_color(PopUpValue->label_enter, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_align_to(PopUpValue->label_enter, PopUpValue->img_enter, LV_ALIGN_OUT_RIGHT_MID, 4, 0);

        PopUpValue->img_cut_point = lv_img_create(PopUpValue->obj_below);
        lv_img_set_src(PopUpValue->img_cut_point, &switch_img);
        lv_obj_align(PopUpValue->img_cut_point, LV_ALIGN_CENTER, -20, 0);
        PopUpValue->label_cut_point = lv_label_create(PopUpValue->obj_below);
        lv_obj_set_style_text_font(PopUpValue->label_cut_point, &font_18, LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_cut_point, (const char *)BelowLanguage[1][configParam.language]);
        lv_obj_set_style_text_color(PopUpValue->label_cut_point, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_align_to(PopUpValue->label_cut_point, PopUpValue->img_cut_point, LV_ALIGN_OUT_RIGHT_MID, 4, 0);

        PopUpValue->img_task_start = lv_img_create(PopUpValue->obj_below);
        lv_img_set_src(PopUpValue->img_task_start, &start_img);
        lv_obj_align(PopUpValue->img_task_start, LV_ALIGN_RIGHT_MID, -35, 0);
        PopUpValue->label_task_start = lv_label_create(PopUpValue->obj_below);
        lv_obj_set_style_text_font(PopUpValue->label_task_start, &font_18, LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_task_start, (const char *)BelowLanguage[2][configParam.language]);
        lv_obj_set_style_text_color(PopUpValue->label_task_start, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_align_to(PopUpValue->label_task_start, PopUpValue->img_task_start, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
#endif
    }

    lv_obj_t *obj_3 = lv_obj_create(PopUpValue->PopUp_obj);
    lv_obj_set_style_border_opa(obj_3, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(obj_3, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(obj_3, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(obj_3, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(obj_3, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(obj_3, 21, 19);                                             // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_align(obj_3, LV_ALIGN_TOP_LEFT, 0, 0);                               // 显示位置

    /* 倒计时 */
    PopUpValue->label_3 = lv_label_create(obj_3);
    lv_obj_set_style_text_font(PopUpValue->label_3, PopUpValue->Str3_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
    lv_label_set_text(PopUpValue->label_3, (const char *)PopUpValue->PopUpStr3);                // 完成校准
    lv_obj_set_style_text_color(PopUpValue->label_3, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align(PopUpValue->label_3, LV_ALIGN_CENTER, 0, 0);                                   // 显示位置

    if (PopUpValue->TimePeriod)
    {
        PopUpValue->PopUpTime = lv_timer_create(popup_time_call_back, PopUpValue->TimePeriod, PopUpValue);
    }
}

/*
    img + str1
       str2
       str3
*/
void lv_show_popup_init1(S_PopUp *PopUp_)
{
    S_PopUp *PopUpValue = &globePopUp;

    if (globePopUp.PopUp_obj)
    {
        lv_obj_del(globePopUp.PopUp_obj);
        globePopUp.PopUp_obj = NULL;
        Task_Set_Animation.panel = NULL;
        Task_Set_Animation.zoom_value = 0;
        LED_TaskA_Pin = LED_OFF;
    }
    if (globePopUp.PopUpTime)
    {
        lv_timer_del(globePopUp.PopUpTime); // 删除倒计时任务
        globePopUp.PopUpTime = NULL;
    }
    if (Task_Set_Animation.animation_time)
    {
        lv_timer_del(Task_Set_Animation.animation_time);
        Task_Set_Animation.animation_time = NULL;
    }

    memcpy(PopUpValue, PopUp_, sizeof(S_PopUp));

    /* 所有对象的obj*/
    PopUpValue->PopUp_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(PopUpValue->PopUp_obj, LV_OPA_0, LV_STATE_DEFAULT);                                 // 设置边框透明度
    lv_obj_set_style_border_side(PopUpValue->PopUp_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);                     // 无边框
    lv_obj_set_style_bg_color(PopUpValue->PopUp_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT);                     // 设置背景颜色为黑色
    lv_obj_set_style_radius(PopUpValue->PopUp_obj, 0, LV_STATE_DEFAULT);                                            // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(PopUpValue->PopUp_obj, LV_OBJ_FLAG_SCROLLABLE);                                               // 关闭滚动
    lv_obj_set_size(PopUpValue->PopUp_obj, LV_PCT(100), LV_SIZE_CONTENT);                                           // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_set_flex_flow(PopUpValue->PopUp_obj, LV_FLEX_FLOW_COLUMN);                                               // 设置为水平布局
    lv_obj_set_flex_align(PopUpValue->PopUp_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    if (PopUpValue->PopUpSize)
    {
        lv_obj_set_size(PopUpValue->PopUp_obj, LCD_W, LCD_H);       // 容器宽度为屏幕宽度，高度根据内容确定
        lv_obj_align(PopUpValue->PopUp_obj, LV_ALIGN_CENTER, 0, 0); // 显示位置
        lv_obj_set_style_pad_row(PopUpValue->PopUp_obj, 16, 0);     // 设置行间距为 0
    }
    else
    {
        lv_obj_set_style_pad_row(PopUpValue->PopUp_obj, 2, 0); // 设置行间距为 0
        // lv_obj_set_style_pad_top(PopUpValue->PopUp_obj, -8, 0);  // 设置顶部间距为 0
        // lv_obj_set_style_pad_bottom(PopUpValue->PopUp_obj, -10, 0);   // 设置底部间距为 0
        lv_obj_set_size(PopUpValue->PopUp_obj, LCD_W, 76);            // 容器宽度为屏幕宽度，高度根据内容确定
        lv_obj_align(PopUpValue->PopUp_obj, LV_ALIGN_TOP_MID, 0, 39); // 显示位置
    }

    if (PopUpValue->img)
    {
        PopUpValue->obj_Str1_label_1 = lv_obj_create(PopUpValue->PopUp_obj);
        lv_obj_set_style_border_opa(PopUpValue->obj_Str1_label_1, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
        lv_obj_set_style_border_side(PopUpValue->obj_Str1_label_1, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
        lv_obj_set_style_bg_color(PopUpValue->obj_Str1_label_1, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
        lv_obj_set_style_radius(PopUpValue->obj_Str1_label_1, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
        lv_obj_clear_flag(PopUpValue->obj_Str1_label_1, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
        // lv_obj_align(PopUpValue->obj_Str1_label_1, LV_ALIGN_TOP_MID, 0, 0);                                                    // 显示位置
        lv_obj_set_size(PopUpValue->obj_Str1_label_1, LCD_W, PopUpValue->img->header.h);                                       // 容器宽度为屏幕宽度，高度根据内容确定
        lv_obj_set_flex_flow(PopUpValue->obj_Str1_label_1, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
        lv_obj_set_flex_align(PopUpValue->obj_Str1_label_1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐
        lv_obj_set_style_pad_column(PopUpValue->obj_Str1_label_1, 8, LV_STATE_DEFAULT);                                        // 设置子对象之间的水平间隔为10像素

        /* 图片 */
        PopUpValue->obj_img = lv_img_create(PopUpValue->obj_Str1_label_1);
        lv_img_set_src(PopUpValue->obj_img, PopUpValue->img);
        lv_obj_set_style_pad_top(PopUpValue->obj_img, 0, 0); // 设置顶部间距为 0

        /* 限制图片大小 */
        float img_size_max = 48;
        if (PopUpValue->Bar_EN)
        {
            img_size_max = 32;
        }
        if ((!PopUpValue->PopUpSize || PopUpValue->Bar_EN) && PopUpValue->img->header.h > img_size_max)
        {
            float scale;
            int16_t x_pos, y_pos;
            my_img_set_zoom(PopUpValue->img, &scale, img_size_max, &x_pos, &y_pos); /* 限制图片大小 */
            lv_img_set_zoom(PopUpValue->obj_img, scale * 256);
            lv_obj_set_style_pad_column(PopUpValue->obj_Str1_label_1, 8 - x_pos, LV_STATE_DEFAULT);
            lv_obj_set_size(PopUpValue->obj_Str1_label_1, LCD_W, PopUpValue->img->header.h * scale + 2);
        }
    }

    if (PopUpValue->PopUpStr1)
    {
        /* 文字 */
        PopUpValue->label_1 = lv_label_create(PopUpValue->obj_Str1_label_1);
        lv_obj_set_style_text_font(PopUpValue->label_1, PopUpValue->Str1_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_1, (const char *)PopUpValue->PopUpStr1);                // 完成校准
        lv_obj_set_style_text_color(PopUpValue->label_1, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        const lv_font_t *font = lv_obj_get_style_text_font(PopUpValue->label_1, LV_PART_MAIN);      // 获取标签使用的字体
        const char *text = lv_label_get_text(PopUpValue->label_1);                                  // 获取标签的文本
        lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE);   // 计算文本的宽度
        if (text_width > LCD_W - 60)
        {
            lv_obj_set_size(PopUpValue->obj_Str1_label_1, LCD_W, 76);
            lv_obj_set_size(PopUpValue->label_1, LCD_W / 2, 66);             // 设置最大显示宽度
            lv_label_set_long_mode(PopUpValue->label_1, LV_LABEL_LONG_WRAP); // 字符串超过了最大宽度换行显示
        }
        lv_obj_set_style_text_align(PopUpValue->label_1, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示
        lv_obj_set_style_pad_top(PopUpValue->label_1, 1, 0);                                      // 设置顶部间距为 0
    }

    if (PopUpValue->Bar_EN) // 进度条优先
    {
        PopUpValue->bar = lv_bar_create(PopUpValue->PopUp_obj);
        if (PopUpValue->PopUpSize)
        {
            lv_obj_set_size(PopUpValue->bar, 240, 24);
            lv_obj_set_style_radius(PopUpValue->bar, 12, LV_PART_MAIN);
            lv_obj_set_style_radius(PopUpValue->bar, 0, LV_PART_INDICATOR);
        }
        else
        {
            lv_obj_set_size(PopUpValue->bar, 200, 18);
            lv_obj_set_style_radius(PopUpValue->bar, 6, LV_PART_MAIN);
            lv_obj_set_style_radius(PopUpValue->bar, 0, LV_PART_INDICATOR);
        }
        lv_bar_set_range(PopUpValue->bar, 0, 100);                           /* 设置进度条部件范围 */
        lv_bar_set_value(PopUpValue->bar, PopUpValue->BarValue, LV_ANIM_ON); /* 设置进度条当前值 */
        lv_obj_set_style_bg_opa(PopUpValue->bar, 255, LV_PART_MAIN);
        lv_obj_set_style_bg_color(PopUpValue->bar, lv_color_hex(0x212121), LV_PART_MAIN);
        lv_obj_set_style_bg_color(PopUpValue->bar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR);
    }
    else if (PopUpValue->PopUpStr2)
    {
        /* 文字 */
        PopUpValue->label_2 = lv_label_create(PopUpValue->PopUp_obj);
        lv_label_set_text(PopUpValue->label_2, (const char *)PopUpValue->PopUpStr2);                // 完成校准
        lv_obj_set_style_text_color(PopUpValue->label_2, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_set_width(PopUpValue->label_2, LCD_W);                                               // 设置最大显示宽度
        lv_label_set_long_mode(PopUpValue->label_2, LV_LABEL_LONG_CLIP);                            // 字符串超过了最大宽度滚动显示
        lv_obj_set_style_text_align(PopUpValue->label_2, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);   // 字符串居中显示
        lv_obj_set_style_text_font(PopUpValue->label_2, PopUpValue->Str2_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(PopUpValue->label_2, 0, 0); // 设置顶部间距为 0
    }

    if ((PopUpValue->PopUpSize && PopUpValue->PopUpStr3) || PopUpValue->Bar_EN)
    {
        /* 文字 */
        PopUpValue->label_3 = lv_label_create(PopUpValue->PopUp_obj);
        lv_obj_set_style_text_font(PopUpValue->label_3, PopUpValue->Str3_Font[PopUpValue->PopUpSize], LV_STATE_DEFAULT);
        lv_label_set_text(PopUpValue->label_3, (const char *)PopUpValue->PopUpStr3);                // 完成校准
        lv_obj_set_style_text_color(PopUpValue->label_3, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        lv_obj_set_width(PopUpValue->label_3, LCD_W);                                               // 设置最大显示宽度
        lv_label_set_long_mode(PopUpValue->label_3, LV_LABEL_LONG_SCROLL_CIRCULAR);                 // 字符串超过了最大宽度滚动显示
        lv_obj_set_style_text_align(PopUpValue->label_3, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);   // 字符串居中显示
        lv_obj_set_style_pad_top(PopUpValue->label_3, PopUpValue->Pad_Top, 0);                      // 设置顶部间距为 0
    }

    if (PopUpValue->TimePeriod)
    {
        PopUpValue->PopUpTime = lv_timer_create(popup_time_call_back, PopUpValue->TimePeriod, PopUpValue);
    }
}

void show_popup(uint8_t img_id, uint8_t str1_id, uint8_t str2_id, uint8_t bar_en)
{
    S_PopUp PopUpValue;

    memset(&PopUpValue, 0, sizeof(PopUpValue));

    PopUpValue.Bar_EN = bar_en;
    PopUpValue.PopUpSize = configParam.PopUpFlag;
    PopUpValue.TimePeriod = POPUP_TIMEPERIOD;
    PopUpValue.CallBackCount = 1500 / POPUP_TIMEPERIOD;

    PopUpValue.Str1_Font[0] = &font_blod_16;
    PopUpValue.Str1_Font[1] = &font_blod_16;
    // PopUpValue.Str2_Font[0] = &font_blod_22;
    PopUpValue.Str2_Font[0] = &font_blod_16;
    PopUpValue.Str2_Font[1] = &font_blod_34;
    PopUpValue.Str3_Font[0] = &font_blod_16;
    PopUpValue.Str3_Font[1] = &font_blod_16;

    if (img_id == warn_IMG_ID && PopUpValue.PopUpSize == 0 && configParam.language == ENGLISH)
    {
        PopUpValue.Str1_Font[0] = &font_blod_14;
        PopUpValue.Str2_Font[0] = &font_blod_14;
        PopUpValue.Str3_Font[0] = &font_blod_14;
    }

    if (str1_id > SetHome_Lang_ID)
    {
        memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);
    }

    if (str1_id == ExitAuto_Lang_ID || str1_id == Calibration_Lang_ID) // 长按enter退出和校准弹框和电量弹框不清除
    {
        PopUpValue.TimePeriod = 0;
    }

    if (str1_id != Invalid_Lang_ID && str2_id != Invalid_Lang_ID)
    {
        if (img_id >= SetPointA_IMG_ID && img_id <= SetPointD_IMG_ID)
        {
            if (((S_Position *)&globeState.Task_Sta.PositionA)[img_id - SetPointA_IMG_ID].degE7_lat &&
                ((S_Position *)&globeState.Task_Sta.PositionA)[img_id - SetPointA_IMG_ID].degE7_long)
            {
                PopUpValue.img = PopUp_Img_Buff[img_id][configParam.PopUpFlag];
            }
            else
            {
                PopUpValue.img = PopUp_Img_Buff[img_id - SetPointA_IMG_ID + _SetPointA_IMG_ID][configParam.PopUpFlag]; // 灰色图标
            }
        }
        else
        {
            PopUpValue.img = PopUp_Img_Buff[img_id][0];
        }

        if (bar_en)
        {
            if (str1_id == UpTask_Lang_ID || str1_id == RTHTask_Lang_ID) // 这里说明是上传任务的进度条
            {
                PopUpValue.PopUpStr1 = (char *)PopUpLanguage[str1_id][configParam.language];
                PopUpValue.PopUpStr2 = NULL; // 显示进度条的时候占用Str2的位置，Str2所以不显示
                PopUpValue.PopUpStr3 = "0%";
                PopUpValue.TimePeriod = 0;
            }
            else
            {
                PopUpValue.PopUpStr1 = (char *)PopUpLanguage[str1_id][configParam.language];
                PopUpValue.PopUpStr2 = NULL; // 显示进度条的时候占用Str2的位置，Str2所以不显示
                PopUpValue.PopUpStr3 = (char *)PopUpLanguage[str2_id][configParam.language];
                PopUpValue.TimePeriod = 50;
            }
        }
        else
        {
            PopUpValue.PopUpStr1 = (char *)PopUpLanguage[str1_id][configParam.language];
            PopUpValue.PopUpStr2 = (char *)PopUpLanguage[str2_id][configParam.language];

            if (str1_id <= SetHome_Lang_ID)
            {
                PopUpValue.PopUpStr3 = "6s";
                PopUpValue.Count_Down = 1; // 需要倒计时
                PopUpValue.TimePeriod = 1000;
                PopUpValue.CallBackCount = 6;
            }
        }
    }
    else if (str1_id != Invalid_Lang_ID)
    {
        if (configParam.PopUpFlag)
        // if (PopUp_Img_Buff[img_id][configParam.PopUpFlag]->header.h > 56)
        {
            PopUpValue.img = PopUp_Img_Buff[img_id][configParam.PopUpFlag];
            PopUpValue.PopUpStr1 = NULL;
            PopUpValue.PopUpStr2 = NULL;
            PopUpValue.PopUpStr3 = (char *)PopUpLanguage[str1_id][configParam.language];
            PopUpValue.Pad_Top = 16;

            if (str1_id == Calibration_Lang_ID)
            {
                PopUpValue.Str3_Font[1] = &font_blod_34;
            }
        }
        else
        {
            PopUpValue.img = PopUp_Img_Buff[img_id][configParam.PopUpFlag];
            PopUpValue.PopUpStr1 = (char *)PopUpLanguage[str1_id][configParam.language];
            PopUpValue.PopUpStr2 = NULL;
            PopUpValue.PopUpStr3 = NULL;
        }
    }

    if (LastglobePopUp.img == PopUpValue.img && LastglobePopUp.PopUpStr1 == PopUpValue.PopUpStr1 &&
        LastglobePopUp.PopUpStr2 == PopUpValue.PopUpStr2 &&
        LastglobePopUp.PopUpStr3 == PopUpValue.PopUpStr3)
    {
        if (str1_id <= SetHome_Lang_ID) // 刷新倒计时
        {
            globePopUp.CallBackCount = 6;
            if (globePopUp.PopUpTime)
            {
                lv_timer_reset(globePopUp.PopUpTime);
            }
            if (globePopUp.label_3)
            {
                lv_label_set_text(globePopUp.label_3, PopUpValue.PopUpStr3);
            }
        }
        else if (str1_id == ExecuteTheTask_Lang_ID && str2_id == Preselect_Point_Lang_ID)
        {
            if (globePopUp.PopUpTime)
            {
                lv_timer_reset(globePopUp.PopUpTime);
            }
        }
        return;
    }

    LastglobePopUp = PopUpValue;

    if (globeGUI.Anchor_obj) // 隐藏船锚
    {
        lv_obj_add_flag(globeGUI.Anchor_obj, LV_OBJ_FLAG_HIDDEN);
    }

    if (img_id >= SetPointA_IMG_ID && img_id <= SetPointD_IMG_ID && PopUpValue.PopUpSize)
    {
        if (str1_id >= SetPointA_Lang_ID)
        {
            PopUpValue.PopUpStr1 = (char *)PopUpLanguage[str1_id - SetPointA_Lang_ID][configParam.language];
        }
        lv_show_popup_init(&PopUpValue);
    }
    else
    {
        if (img_id >= SetPointA_IMG_ID && img_id <= SetPointD_IMG_ID)
        {
            memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);
            ((uint8_t *)&globeState.Task_Sta.GetPosA_En)[Task_Set_Animation.item_cut] = 1;
        }
        lv_show_popup_init1(&PopUpValue);
    }

    if (globeGUI.task_num_img)
    {
        lv_obj_add_flag(globeGUI.task_num_img, LV_OBJ_FLAG_HIDDEN);
    }

    globeState.JoystickDelayTick = GetSysTick();
}

void show_home_popup(void)
{
    char string[20];
    S_PopUp PopUpValue;

    if (!globeState.ShowPitch)
    {
        if (globeState.satelliteNum)
        {
            if (globeState.distance > 99000)
            {
                sprintf(string, ">99Km");
            }
            else if (globeState.distance > 1000)
            {
                sprintf(string, "%6.2fKm", globeState.distance / 1000.0f);
            }
            else
            {
                sprintf(string, "%6.2fm", globeState.distance);
            }
        }
        else
        {
            sprintf(string, " --m");
        }
    }
    else
    {
        sprintf(string, "%04d  %04d", rc_channels.chan3_raw, rc_channels.chan4_raw);
    }

    memset(&PopUpValue, 0, sizeof(S_PopUp));
    PopUpValue.img = (lv_img_dsc_t *)&HomeBig_img;
    PopUpValue.PopUpStr1 = string;
    PopUpValue.TimePeriod = 0;
    PopUpValue.Str1_Font[0] = &font_blod_43;
    PopUpValue.Str1_Font[1] = &font_blod_43;

    if (LastglobePopUp.img == PopUpValue.img && LastglobePopUp.PopUpStr1 == PopUpValue.PopUpStr1 &&
        LastglobePopUp.PopUpStr2 == PopUpValue.PopUpStr2 &&
        LastglobePopUp.PopUpStr3 == PopUpValue.PopUpStr3)
    {
        lv_label_set_text(globePopUp.label_1, string);
        return;
    }
    LastglobePopUp = PopUpValue;
    lv_show_popup_init1(&PopUpValue);
    lv_obj_add_flag(globeGUI.home_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(globeGUI.home_img, LV_OBJ_FLAG_HIDDEN);
    if (globeGUI.task_num_img)
    {
        lv_obj_add_flag(globeGUI.task_num_img, LV_OBJ_FLAG_HIDDEN);
    }
}

static void task_time_callback(lv_timer_t *timer)
{
    static uint8_t time_cnt = 0;
    static uint8_t flag = 0;
    static int y = 0;
    float now_distance;

    if (++time_cnt > 10)
    {
        time_cnt = 0;

        if (globeState.custom_mode == ROVER_MODE_RTL)
        {
            now_distance = globeState.distance;
        }
        else
        {
            now_distance = get_distance(globeState.TaskPosition.degE7_lat / 10000000.0, globeState.TaskPosition.degE7_long / 10000000.0,
                                        globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0);
        }
        if (now_distance > globeState.task_distance) // 这里说明做任务的时候人为操作了船
        {
            globeState.task_distance = now_distance;
        }
        globeGUI.task_run_cnt = (1.0f - (now_distance / globeState.task_distance)) * 230.0f;
        // Debug("now_distance: %3.2f   task_distance: %3.2f", now_distance, globeState.task_distance);
        // if (globeGUI.task_run_cnt++ > 230)
        // {
        //     globeGUI.task_run_cnt = 0;
        // }
        lv_obj_align(globeGUI.Task_boat, LV_ALIGN_LEFT_MID, globeGUI.task_run_cnt, 7); // MAX 230 MIN 0
        lv_obj_set_size(globeGUI.Task_line_obj, 60 + globeGUI.task_run_cnt, 17);
    }

    if (globePopUp.PopUpSize || globePopUp.PopUp_obj == NULL)
    {
        if (!flag && ++y > 4)
        {
            flag = 1;
        }
        else if (flag && --y < 0)
        {
            flag = 0;
        }

        lv_obj_align(globeGUI.task_num_img, LV_ALIGN_RIGHT_MID, -20 + globeGUI.x_pos, -24 - y); // 显示位置
    }
}

void task_animation_del(void)
{
    if (globeGUI.Task_obj)
    {
        lv_obj_del(globeGUI.Task_obj);
    }
    if (globeGUI.task_num_img)
    {
        lv_obj_del(globeGUI.task_num_img);
    }
    if (globeGUI.task_time)
    {
        lv_timer_del(globeGUI.task_time);
    }
    globeGUI.Task_obj = NULL;
    globeGUI.task_time = NULL;
    globeGUI.task_num_img = NULL;
}

void task_animation_init(uint8_t TaskType)
{
    const void *TaskImg;
    float now_distance;

    switch (TaskType)
    {
    case TaskA:
        TaskImg = PopUp_Img_Buff[TaskA_IMG_ID][0];
        break;
    case TaskB:
        TaskImg = PopUp_Img_Buff[TaskB_IMG_ID][0];
        break;
    case TaskC:
        TaskImg = PopUp_Img_Buff[TaskC_IMG_ID][0];
        break;
    case TaskD:
        TaskImg = PopUp_Img_Buff[TaskD_IMG_ID][0];
        break;
    case TaskH:
        TaskImg = PopUp_Img_Buff[TaskHome_IMG_ID][0];
        break;
    case TaskApp:
        TaskImg = PopUp_Img_Buff[globeState.ShowTask_IMG_ID][0];
        break;
    }

    if (globeGUI.Task_obj)
    {
        // lv_img_set_src(globeGUI.task_num_img, TaskImg);
        // if (TaskType == TaskH)
        // {
        //     lv_img_set_src(globeGUI.task_line_img, &Line_return);
        // }
        // else
        // {
        //     lv_img_set_src(globeGUI.task_line_img, &task_img);
        // }
        task_animation_del();
    }

    // globeGUI.task_run_cnt = 0;
    if (globeState.custom_mode == ROVER_MODE_RTL)
    {
        now_distance = globeState.distance;
    }
    else
    {
        now_distance = get_distance(globeState.TaskPosition.degE7_lat / 10000000.0, globeState.TaskPosition.degE7_long / 10000000.0,
                                    globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0);
    }
    globeGUI.task_run_cnt = (1.0f - (now_distance / globeState.task_distance)) * 230.0f;

    /* 所有对象的obj*/
    globeGUI.Task_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(globeGUI.Task_obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.Task_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(globeGUI.Task_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(globeGUI.Task_obj, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(globeGUI.Task_obj, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(globeGUI.Task_obj, LCD_W, 72);                                          // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_align(globeGUI.Task_obj, LV_ALIGN_TOP_MID, 0, 39);                               // 显示位置
    // lv_obj_set_flex_flow(globeGUI.Task_obj, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
    // lv_obj_set_flex_align(globeGUI.Task_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    globeGUI.task_line_img = lv_img_create(globeGUI.Task_obj);
    if (TaskType == TaskH)
    {
        lv_img_set_src(globeGUI.task_line_img, &Line_return);
    }
    else
    {
        lv_img_set_src(globeGUI.task_line_img, &task_img);
    }
    lv_obj_align(globeGUI.task_line_img, LV_ALIGN_RIGHT_MID, -18, 7); // 显示位置

    globeGUI.Task_line_obj = lv_obj_create(globeGUI.Task_obj);                                   // 这个用来遮住Task_boat_light
    lv_obj_set_style_border_opa(globeGUI.Task_line_obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.Task_line_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(globeGUI.Task_line_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(globeGUI.Task_line_obj, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(globeGUI.Task_line_obj, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(globeGUI.Task_line_obj, 60 + globeGUI.task_run_cnt, 20);                     // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_align(globeGUI.Task_line_obj, LV_ALIGN_LEFT_MID, 5, 7);                               // MAX 230 MIN 0

    globeGUI.Task_boat = lv_img_create(globeGUI.Task_obj);

    if (globeState.BoatVersion == Rogue_MAX)
    {
        if (globeState.Reposition_Value.lat_Diff && globeState.Reposition_Value.long_Diff)
        {
            lv_img_set_src(globeGUI.Task_boat, &boat_rogue_fixed);
        }
        else
        {
            lv_img_set_src(globeGUI.Task_boat, &boat_rogue_nor);
        }
    }
    else
    {
        if (globeState.Reposition_Value.lat_Diff && globeState.Reposition_Value.long_Diff)
        {
            lv_img_set_src(globeGUI.Task_boat, &Boat_fix);
        }
        else
        {
            lv_img_set_src(globeGUI.Task_boat, &boat_mini_img);
        }
    }

    lv_obj_align(globeGUI.Task_boat, LV_ALIGN_LEFT_MID, globeGUI.task_run_cnt, 7); // MAX 230 MIN 0

    globeGUI.task_num_img = lv_img_create(globeGUI.screen);
    lv_img_set_src(globeGUI.task_num_img, TaskImg);
    float scale;
    my_img_set_zoom(TaskImg, &scale, 44, &globeGUI.x_pos, &globeGUI.y_pos); /* 限制图片大小 */
    lv_img_set_zoom(globeGUI.task_num_img, scale * 256);
    lv_obj_align(globeGUI.task_num_img, LV_ALIGN_RIGHT_MID, -20 + globeGUI.x_pos, -24); // 显示位置

    globeGUI.task_time = lv_timer_create(task_time_callback, 100, 0);
}

static void anchor_time_callback(lv_timer_t *timer)
{
    if (globePopUp.PopUp_obj) // 在弹框
    {
        return;
    }

    globeGUI.Anchor_run_cnt++;

    if (globeGUI.Anchor_run_cnt % 4 == 0)
    {
        globeGUI.img1_size += 0.05f;
        globeGUI.img1_opa -= 0.1f;
        if (globeGUI.img1_size >= 1.5f)
        {
            globeGUI.img1_size = 1;
            globeGUI.img1_opa = 1;
        }
        lv_img_set_zoom(globeGUI.Anchor_img1, 255.0f * globeGUI.img1_size);
        lv_obj_set_style_img_opa(globeGUI.Anchor_img1, 0.2f * 255 * globeGUI.img1_opa, 0); // 透明度设置
    }

    if (globeGUI.Anchor_run_cnt % 3 == 0)
    {
        globeGUI.img2_size += 0.05f;
        globeGUI.img2_opa -= 0.05f;
        if (globeGUI.img2_size >= 1.5f)
        {
            globeGUI.img2_size = 1;
            globeGUI.img2_opa = 1;
        }
        lv_img_set_zoom(globeGUI.Anchor_img2, 255.0f / 128.0f * 88.0f * globeGUI.img2_size);
        lv_obj_set_style_img_opa(globeGUI.Anchor_img2, 0.35f * 255 * globeGUI.img2_opa, 0); // 透明度设置
    }

    if (globeGUI.Anchor_run_cnt % 3 == 0)
    {
        globeGUI.img3_size += 0.05f;
        globeGUI.img3_opa -= 0.05f;
        if (globeGUI.img3_size >= 1.5f)
        {
            globeGUI.img3_size = 1;
            globeGUI.img3_opa = 1;
        }
        lv_img_set_zoom(globeGUI.Anchor_img3, 255.0f / 128.0f * 52.0f * globeGUI.img3_size);
        lv_obj_set_style_img_opa(globeGUI.Anchor_img3, 0.5f * 255 * globeGUI.img3_opa, 0); // 透明度设置
    }

    if (globeGUI.Anchor_run_cnt % 3 == 0)
    {
        if (globeGUI.img3_size >= 0.99f && globeGUI.img3_size < 1.01f)
        {
            if (!TimeControl[Vibr_Motor_ID].CNT)
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 20, 0, 50, 0, 0, 0, 1);
            }
        }
        else if (globeGUI.img3_size >= 1.09f && globeGUI.img3_size < 1.11f)
        {
            if (!TimeControl[Vibr_Motor_ID].CNT)
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 40, 0, 50, 0, 0, 0, 1);
            }
        }
        else if (globeGUI.img3_size >= 1.19f && globeGUI.img3_size < 1.21f)
        {
            if (!TimeControl[Vibr_Motor_ID].CNT)
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 50, 0, 0, 0, 1);
            }
        }
    }
}

void anchor_animation_init(void)
{
    if (globeGUI.Anchor_obj)
    {
        return;
    }

    globeGUI.img1_size = 1;
    globeGUI.img2_size = 1;
    globeGUI.img3_size = 1;
    globeGUI.img1_opa = 1;
    globeGUI.img2_opa = 1;
    globeGUI.img3_opa = 1;

    /* 所有对象的obj*/
    globeGUI.Anchor_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(globeGUI.Anchor_obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.Anchor_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(globeGUI.Anchor_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(globeGUI.Anchor_obj, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(globeGUI.Anchor_obj, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(globeGUI.Anchor_obj, 150, 80);                                            // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_align(globeGUI.Anchor_obj, LV_ALIGN_TOP_MID, 0, 50);                               // 显示位置
    // lv_obj_set_flex_flow(globeGUI.Anchor_obj, LV_FLEX_FLOW_ROW);                                                  // 设置为水平布局
    // lv_obj_set_flex_align(globeGUI.Anchor_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    globeGUI.Anchor_img1 = lv_img_create(globeGUI.Anchor_obj);
    lv_img_set_src(globeGUI.Anchor_img1, &anchor1_img);
    lv_obj_align(globeGUI.Anchor_img1, LV_ALIGN_CENTER, 0, 18);    // 显示位置
    lv_obj_set_style_img_opa(globeGUI.Anchor_img1, 0.2f * 255, 0); // 透明度设置为 50%
    lv_img_set_zoom(globeGUI.Anchor_img1, 255.0f * globeGUI.img1_size);

    globeGUI.Anchor_img2 = lv_img_create(globeGUI.Anchor_img1);
    lv_img_set_src(globeGUI.Anchor_img2, &anchor1_img);
    lv_obj_align(globeGUI.Anchor_img2, LV_ALIGN_CENTER, 0, 0);      // 显示位置
    lv_obj_set_style_img_opa(globeGUI.Anchor_img2, 0.35f * 255, 0); // 透明度设置为 50%
    lv_img_set_zoom(globeGUI.Anchor_img2, 255.0f / 128.0f * 88.0f * globeGUI.img2_size);

    globeGUI.Anchor_img3 = lv_img_create(globeGUI.Anchor_img1);
    lv_img_set_src(globeGUI.Anchor_img3, &anchor1_img);
    lv_obj_align(globeGUI.Anchor_img3, LV_ALIGN_CENTER, 0, 0);     // 显示位置
    lv_obj_set_style_img_opa(globeGUI.Anchor_img3, 0.5f * 255, 0); // 透明度设置为 50%
    lv_img_set_zoom(globeGUI.Anchor_img3, 255.0f / 128.0f * 52.0f * globeGUI.img3_size);

    globeGUI.Anchor_img = lv_img_create(globeGUI.Anchor_obj);
    lv_img_set_src(globeGUI.Anchor_img, &anchor_img);
    lv_obj_align(globeGUI.Anchor_img, LV_ALIGN_CENTER, 0, -10); // 显示位置

    globeGUI.Anchor_time = lv_timer_create(anchor_time_callback, 50, 0);
}

void anchor_animation_del(void)
{
    if (globeGUI.Anchor_obj)
    {
        lv_obj_del(globeGUI.Anchor_obj);
    }
    if (globeGUI.Anchor_time)
    {
        lv_timer_del(globeGUI.Anchor_time);
    }
    globeGUI.Anchor_obj = NULL;
    globeGUI.Anchor_time = NULL;
}

void main_ui_init(void)
{
    uint8_t value;
    char string[32];

    /*------------------------------------ 连接状态显示 --------------------------------------*/
#if 1
    globeGUI.Connect = lv_obj_create(globeGUI.screen);                                     // 渐变颜色效果
    lv_obj_set_style_border_opa(globeGUI.Connect, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.Connect, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_radius(globeGUI.Connect, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(globeGUI.Connect, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_pos(globeGUI.Connect, 0, 0);
    lv_obj_set_size(globeGUI.Connect, 160, 40);
    lv_obj_set_style_bg_grad_dir(globeGUI.Connect, LV_GRAD_DIR_HOR, LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_src(globeGUI.Connect, &rssi, LV_STATE_DEFAULT);
    globeGUI.Connect_label = lv_label_create(globeGUI.Connect); // 模式显示
    lv_obj_set_style_text_font(globeGUI.Connect_label, &font_blod_18, LV_STATE_DEFAULT);
    lv_obj_align(globeGUI.Connect_label, LV_ALIGN_LEFT_MID, -8, 0);
#ifndef SHOW_RSSI_DB
    globeGUI.RssiImg = lv_img_create(globeGUI.Connect); // 信号格数
#else
    globeGUI.RssiImg = lv_label_create(globeGUI.Connect); // 信号格数
    lv_obj_set_style_text_font(globeGUI.RssiImg, &font_blod_18, LV_STATE_DEFAULT);
    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -18, 0);
    lv_obj_set_style_text_color(globeGUI.RssiImg, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    sprintf(string, "%d", globeState.rf_rssi);
    lv_label_set_text(globeGUI.RssiImg, string);
#endif

    if (globeState.isConnect)
    {
        lv_obj_set_style_text_font(globeGUI.Connect_label, &font_blod_18, LV_STATE_DEFAULT);
        lv_obj_align(globeGUI.Connect_label, LV_ALIGN_LEFT_MID, -8, 0);

        if (globeState.FCmode == 'M')
        {
            lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 背景颜色渐变
            lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[ManualMode_Lang_ID][configParam.language]);
            lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0x0000ff), LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 背景颜色渐变
            lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[AutoMode_Lang_ID][configParam.language]);
            lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
        }
        globeState.FCmodeRefresh = globeState.FCmode;

#ifndef SHOW_RSSI_DB
        switch (globeState.rf_rssi)
        {
        case 5:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
            lv_obj_set_size(globeGUI.RssiImg, 24, 24);
        }
        break;
        case 4:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 18, 0);
            lv_obj_set_size(globeGUI.RssiImg, 18, 24);
        }
        break;
        case 3:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 14, 0);
            lv_obj_set_size(globeGUI.RssiImg, 14, 24);
        }
        break;
        case 2:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 10, 0);
            lv_obj_set_size(globeGUI.RssiImg, 10, 24);
        }
        break;
        case 1:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_set_size(globeGUI.RssiImg, 6, 24);
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 6, 0);
        }
        break;
        default:
        {
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
            lv_obj_set_size(globeGUI.RssiImg, 24, 24);
        }
        break;
        }
#else
        sprintf(string, "%d", globeState.rf_rssi);
        lv_label_set_text(globeGUI.RssiImg, string);
#endif
        globeState.rf_rssiRefresh = globeState.rf_rssi;
    }
    else
    {
        if (configParam.language == ENGLISH)
        {
            lv_obj_align(globeGUI.Connect_label, LV_ALIGN_LEFT_MID, -14, 0);
            lv_obj_set_style_text_font(globeGUI.Connect_label, &font_blod_14, LV_STATE_DEFAULT);
        }

        lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 背景颜色渐变
        lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[Disconnected_Lang_ID][configParam.language]);
        lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
#ifndef SHOW_RSSI_DB
        lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[DisSignal_IMG_ID]); // 断联图标
        lv_obj_set_size(globeGUI.RssiImg, 24, 24);
        lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
#else
        lv_label_set_text(globeGUI.RssiImg, 0);
#endif
    }
    globeState.ConnectRefresh = globeState.isConnect;
#endif

    /*------------------------------------ 卫星显示 -----------------------------------------*/
#if 1
    globeGUI.satellite_img = lv_img_create(globeGUI.screen);                                         // 卫星图标
    lv_img_set_src(globeGUI.satellite_img, LVGL_Img_Buff[Satellite_IMG_ID]);                         // 加载的图片
    lv_obj_align_to(globeGUI.satellite_img, globeGUI.Connect, LV_ALIGN_OUT_RIGHT_MID, -28, 0);       // 显示位置
    lv_img_set_angle(globeGUI.satellite_img, 0);                                                     // 图片旋转角度0-3600
    globeGUI.satellite_label = lv_label_create(globeGUI.screen);                                     // 卫星数量
    lv_obj_align_to(globeGUI.satellite_label, globeGUI.satellite_img, LV_ALIGN_OUT_RIGHT_MID, 0, 0); // 显示位置
    lv_obj_set_style_text_color(globeGUI.satellite_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_set_style_text_font(globeGUI.satellite_label, &font_blod_16, LV_STATE_DEFAULT);           // 字体文件
    // lv_obj_set_size(globeGUI.satellite_label, 28, 14);                                               // 显示大小

    if (globeState.isConnect)
    {
        sprintf(string, "%2d", globeState.satelliteNum);
        lv_label_set_text(globeGUI.satellite_label, string);
    }
    else
    {
        lv_label_set_text(globeGUI.satellite_label, " --");
    }
#endif

    /*------------------------------------ 电量显示 -----------------------------------------*/
#if 1
    globeGUI.remote_bat = lv_obj_create(globeGUI.screen);                                        /* 遥控器电量图标 */
    lv_obj_set_size(globeGUI.remote_bat, 64, 24);                                                // 显示大小
    lv_obj_set_style_border_opa(globeGUI.remote_bat, LV_OPA_0, LV_STATE_DEFAULT);                // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.remote_bat, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);    // 无边框
    lv_obj_set_style_bg_grad_dir(globeGUI.remote_bat, LV_GRAD_DIR_HOR, LV_STATE_DEFAULT);        // 颜色水平渐变
    lv_obj_set_style_radius(globeGUI.remote_bat, 5, LV_STATE_DEFAULT);                           // 圆角半径为5
    lv_obj_clear_flag(globeGUI.remote_bat, LV_OBJ_FLAG_SCROLLABLE);                              // 关闭滚动
    lv_obj_align_to(globeGUI.remote_bat, globeGUI.satellite_img, LV_ALIGN_OUT_RIGHT_MID, 25, 0); // 显示位置
    globeGUI.remote_boat_img = lv_img_create(globeGUI.remote_bat);                               /* 遥控器电量里面的图标 */
    if (globeState.chargeStat)
    {
        lv_img_set_src(globeGUI.remote_boat_img, LVGL_Img_Buff[Charging_IMG_ID]); // 加载的图片
    }
    lv_obj_align(globeGUI.remote_boat_img, LV_ALIGN_LEFT_MID, -12, 0);                                // 图片显示位置
    lv_img_set_angle(globeGUI.remote_boat_img, 0);                                                    // 图片旋转角度0-3600
    lv_obj_set_style_bg_grad_dir(globeGUI.remote_bat, LV_GRAD_DIR_HOR, LV_STATE_DEFAULT);             // 水平渐变
    globeGUI.remote_bat_lable = lv_label_create(globeGUI.remote_bat);                                 /* 遥控器电量百分比 */
    lv_obj_align(globeGUI.remote_bat_lable, LV_ALIGN_LEFT_MID, -12, 0);                               // 显示位置
    lv_obj_set_style_text_color(globeGUI.remote_bat_lable, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_set_style_text_font(globeGUI.remote_bat_lable, &font_blod_16, LV_STATE_DEFAULT);           // 字体文件
    /*--- 以下是根据遥控器电压刷新UI显示 ---*/
    if (globeState.chargeStat)
    {
        lv_img_set_src(globeGUI.remote_boat_img, &icon_charging);                                                                      // 加载的图片
        lv_obj_set_style_bg_main_stop(globeGUI.remote_bat, (uint8_t)(globeGUI.Charge_batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 开始渐变位置
        lv_obj_set_style_bg_grad_stop(globeGUI.remote_bat, (uint8_t)(globeGUI.Charge_batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 结束渐变位置
        if (globeGUI.Charge_batPercent)
        {
            lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT); // 开始渐变颜色
        }
        else
        {
            lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 开始渐变颜色
        }
        lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 渐变成什么颜色

        if (globeState.chargeStat == charge_ok)
        {
            lv_label_set_text(globeGUI.remote_bat_lable, "   CHG");
            globeGUI.Charge_batPercent = 100;
        }
        else
        {
            lv_label_set_text(globeGUI.remote_bat_lable, "   CHG");
            globeGUI.Charge_batPercent += 20;
            if (globeGUI.Charge_batPercent > 100)
            {
                globeGUI.Charge_batPercent = 0;
            }
        }
        lv_obj_clear_flag(globeGUI.remote_boat_img, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_set_style_bg_main_stop(globeGUI.remote_bat, (uint8_t)(globeState.batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 开始渐变位置(电量百分柱)
        lv_obj_set_style_bg_grad_stop(globeGUI.remote_bat, (uint8_t)(globeState.batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 结束渐变位置
        if (globeState.batPercent > 40)
        {
            lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT);     // 开始渐变颜色
            lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 渐变成什么颜色
        }
        else if (globeState.batPercent > 10)
        {
            lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(255, 130, 0), LV_STATE_DEFAULT);     // 开始渐变颜色
            lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(102, 53, 0), LV_STATE_DEFAULT); // 渐变成什么颜色
        }
        else
        {
            lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(242, 53, 48), LV_STATE_DEFAULT);     // 开始渐变颜色
            lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 渐变成什么颜色
        }
        sprintf(string, "R%3d%%", globeState.batPercent);
        lv_label_set_text(globeGUI.remote_bat_lable, string);
        lv_obj_add_flag(globeGUI.remote_boat_img, LV_OBJ_FLAG_HIDDEN);
    }

    globeState.batPercentRefresh = globeState.batPercent;
    /*--------------------- end ---------------------*/
    globeGUI.boat_bat = lv_obj_create(globeGUI.screen);                                     /* 船电量图标 */
    lv_obj_set_size(globeGUI.boat_bat, 64, 24);                                             // 显示大小
    lv_obj_set_style_border_opa(globeGUI.boat_bat, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.boat_bat, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_grad_dir(globeGUI.boat_bat, LV_GRAD_DIR_HOR, LV_STATE_DEFAULT);     // 颜色水平渐变
    lv_obj_set_style_radius(globeGUI.boat_bat, 5, LV_STATE_DEFAULT);                        // 圆角半径为5
    lv_obj_clear_flag(globeGUI.boat_bat, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_align_to(globeGUI.boat_bat, globeGUI.remote_bat, LV_ALIGN_OUT_RIGHT_MID, 5, 0);  // 显示位置
    // globeGUI.boat_bat_img = lv_img_create(globeGUI.boat_bat);                                       /* 船电量里面的图标 */
    // lv_img_set_src(globeGUI.boat_bat_img, &boat_mini);                                              // 加载的图片
    // lv_obj_align(globeGUI.boat_bat_img, LV_ALIGN_LEFT_MID, -12, 0);                                 // 图片显示位置
    // lv_img_set_angle(globeGUI.boat_bat_img, 0);                                                     // 图片旋转角度0-3600
    globeGUI.boat_bat_label = lv_label_create(globeGUI.boat_bat);                                   /* 船电压 */
    lv_obj_align(globeGUI.boat_bat_label, LV_ALIGN_LEFT_MID, -12, 0);                               // 显示位置
    lv_obj_set_style_text_color(globeGUI.boat_bat_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_set_style_text_font(globeGUI.boat_bat_label, &font_blod_16, LV_STATE_DEFAULT);           // 字体文件
    /*--- 以下是根据船电压刷新UI显示 ---*/
    value = getBatPercent(globeState.boat_voltage_battery / 1000.0f) * 2.55f;
    lv_obj_set_style_bg_main_stop(globeGUI.boat_bat, value, LV_STATE_DEFAULT); // 电量百分柱
    lv_obj_set_style_bg_grad_stop(globeGUI.boat_bat, value, LV_STATE_DEFAULT);
    if (!globeState.isConnect && globeState.boat_voltage_battery == 0)
    {
        lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 背景颜色渐变
    }
    else if (globeState.boat_voltage_battery > 10785)
    {
        lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 背景颜色渐变
    }
    else if (globeState.boat_voltage_battery > 10200)
    {
        lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(255, 130, 0), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(102, 53, 0), LV_STATE_DEFAULT); // 背景颜色渐变
    }
    else
    {
        lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(242, 53, 48), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 背景颜色渐变
    }
    if (globeState.isConnect)
    {
        sprintf(string, "B%2.1fV", globeState.boat_voltage_battery / 1000.0f);
    }
    else if (globeState.boat_voltage_battery == 0)
    {
        sprintf(string, "B     --");
    }
    lv_label_set_text(globeGUI.boat_bat_label, string);
    globeState.boat_voltage_batteryRefresh = globeState.boat_voltage_battery;
    /*--------------------- end ---------------------*/
#endif

/*------------------------------------ 指南针显示 ---------------------------------------*/
#if 1
    globeGUI.Compass_img = lv_img_create(globeGUI.screen); /* 指南针图标 */
    lv_img_set_src(globeGUI.Compass_img, LVGL_Img_Buff[Compass_IMG_ID]);
    lv_obj_align(globeGUI.Compass_img, LV_ALIGN_BOTTOM_LEFT, 4, -8);
    globeGUI.navigation_img = lv_img_create(globeGUI.Compass_img); /* 指南针箭头 */
    lv_img_set_src(globeGUI.navigation_img, LVGL_Img_Buff[Navigation_IMG_ID]);
    lv_obj_align(globeGUI.navigation_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(globeGUI.navigation_img, globeState.Angle * 10); // 船的角度UI
    globeState.AngleRefresh = globeState.Angle;
#endif

    /*------------------------------------ 保存的AB点显示 -----------------------------------*/
#if 1
    globeGUI.point_a_img = lv_img_create(globeGUI.screen); // A点未保存灰色图标
    if (globeState.Task_Sta.PositionA.degE7_lat && globeState.Task_Sta.PositionA.degE7_long)
    {
        lv_img_set_src(globeGUI.point_a_img, LVGL_Img_Buff[SaveA_IMG_ID]);
        // lv_img_set_zoom(globeGUI.point_a_img, 21);
    }
    else
    {
        lv_img_set_src(globeGUI.point_a_img, LVGL_Img_Buff[NoSaveA_IMG_ID]);
    }
    lv_obj_align_to(globeGUI.point_a_img, globeGUI.Compass_img, LV_ALIGN_OUT_RIGHT_BOTTOM, 18, 0);
    globeState.PositionARefresh = 0;

    globeGUI.point_b_img = lv_img_create(globeGUI.screen); // B点未保存灰色图标
    if (globeState.Task_Sta.PositionB.degE7_lat && globeState.Task_Sta.PositionB.degE7_long)
    {
        lv_img_set_src(globeGUI.point_b_img, LVGL_Img_Buff[SaveB_IMG_ID]);
    }
    else
    {
        lv_img_set_src(globeGUI.point_b_img, LVGL_Img_Buff[NoSaveB_IMG_ID]);
    }
    lv_obj_align_to(globeGUI.point_b_img, globeGUI.point_a_img, LV_ALIGN_OUT_RIGHT_BOTTOM, 8, 0);
    globeState.PositionBRefresh = 0;

    globeGUI.point_c_img = lv_img_create(globeGUI.screen); // C点未保存灰色图标
    if (globeState.Task_Sta.PositionC.degE7_lat && globeState.Task_Sta.PositionC.degE7_long)
    {
        lv_img_set_src(globeGUI.point_c_img, LVGL_Img_Buff[SaveC_IMG_ID]);
        // lv_img_set_zoom(globeGUI.point_a_img, 21);
    }
    else
    {
        lv_img_set_src(globeGUI.point_c_img, LVGL_Img_Buff[NoSaveC_IMG_ID]);
    }

    lv_obj_align_to(globeGUI.point_c_img, globeGUI.point_b_img, LV_ALIGN_OUT_RIGHT_BOTTOM, 8, 0);
    globeState.PositionCRefresh = 0;
    globeGUI.point_d_img = lv_img_create(globeGUI.screen); // D点未保存灰色图标
    if (globeState.Task_Sta.PositionD.degE7_lat && globeState.Task_Sta.PositionD.degE7_long)
    {
        lv_img_set_src(globeGUI.point_d_img, LVGL_Img_Buff[SaveD_IMG_ID]);
    }
    else
    {
        lv_img_set_src(globeGUI.point_d_img, LVGL_Img_Buff[NoSaveD_IMG_ID]);
    }

    lv_obj_align_to(globeGUI.point_d_img, globeGUI.point_c_img, LV_ALIGN_OUT_RIGHT_BOTTOM, 8, 0);
    globeState.PositionDRefresh = 0;

    if (configParam.AB_Mode == AB_MODE)
    {
        lv_obj_add_flag(globeGUI.point_c_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
        lv_obj_add_flag(globeGUI.point_d_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
    }
    else
    {
        lv_obj_clear_flag(globeGUI.point_c_img, LV_OBJ_FLAG_HIDDEN); // 显示
        lv_obj_clear_flag(globeGUI.point_d_img, LV_OBJ_FLAG_HIDDEN); // 显示
    }
#endif

    /*------------------------------------ 船灯light显示 ------------------------------------*/
#if 1
    globeGUI.light_img = lv_img_create(globeGUI.screen); // 船灯状态
    if (globeState.GhostModeEn)
    {
        if (globeState.show_main != ShowMainLogo)
        {
            lv_img_set_src(globeGUI.light_img, LVGL_Img_Buff[GhostMode_IMG_ID]);
            lv_obj_clear_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 显示
        }
        else
        {
            lv_obj_add_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
        }
    }
    else
    {
        lv_img_set_src(globeGUI.light_img, LVGL_Img_Buff[Light_IMG_ID]);
        if (globeState.boatLEDStat)
        {
            lv_obj_clear_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 显示
        }
        else
        {
            lv_obj_add_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
        }
    }
    lv_obj_align_to(globeGUI.light_img, globeGUI.Compass_img, LV_ALIGN_OUT_RIGHT_TOP, 0, -8);
    globeState.boatLEDStatRefresh = globeState.boatLEDStat;
#endif

    /*------------------------------------ home点显示 ---------------------------------------*/
#if 1
    globeGUI.home_img = lv_img_create(globeGUI.screen); /* home点图标 */
    lv_img_set_src(globeGUI.home_img, &home);
    lv_obj_align_to(globeGUI.home_img, globeGUI.point_d_img, LV_ALIGN_OUT_RIGHT_MID, 18, -20);
    globeGUI.home_label = lv_label_create(globeGUI.screen); /* 船离home点距离 */
    lv_obj_align_to(globeGUI.home_label, globeGUI.home_img, LV_ALIGN_OUT_RIGHT_MID, 5, -3);
    lv_obj_set_style_text_color(globeGUI.home_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(globeGUI.home_label, &font_blod_18, LV_STATE_DEFAULT);
    if (globeState.satelliteNum)
    {
        if (globeState.distance > 99000)
        {
            sprintf(string, ">99Km");
        }
        else if (globeState.distance > 1000)
        {
            sprintf(string, "%1.2fKm", globeState.distance / 1000.0f);
        }
        else
        {
            sprintf(string, "%1.2fm", globeState.distance);
        }
    }
    else
    {
        sprintf(string, " --m");
    }
    lv_label_set_text(globeGUI.home_label, string);
#endif

    /*------------------------------------ 船速度显示 ---------------------------------------*/
#if 1
    globeGUI.speed_img = lv_img_create(globeGUI.screen); /* 速度图标 */
    if (configParam.BoatSpeed == Speed_min)
    {
        lv_img_set_src(globeGUI.speed_img, &speed_low_s);
    }
    else if (configParam.BoatSpeed == Speed_normal)
    {
        lv_img_set_src(globeGUI.speed_img, &speed_medium_s);
    }
    else
    {
        lv_img_set_src(globeGUI.speed_img, &speed_high_s);
    }
    lv_obj_align_to(globeGUI.speed_img, globeGUI.point_d_img, LV_ALIGN_OUT_RIGHT_MID, 18, 5);

    globeGUI.speed_label = lv_label_create(globeGUI.screen); /* 速度值 */
    lv_obj_align_to(globeGUI.speed_label, globeGUI.speed_img, LV_ALIGN_OUT_RIGHT_MID, 5, -1);
    lv_obj_set_style_text_color(globeGUI.speed_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(globeGUI.speed_label, &font_blod_18, LV_STATE_DEFAULT);
    sprintf(string, "%1.1fm/s", globeState.speed);
    lv_label_set_text(globeGUI.speed_label, string);
    globeState.speedRefresh = globeState.speed;
#endif

    /*------------------------------------ LOG显示 ------------------------------------------*/
#if 1
    globeGUI.main_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(globeGUI.main_obj, LV_OPA_0, LV_STATE_DEFAULT);                                 // 设置边框透明度
    lv_obj_set_style_border_side(globeGUI.main_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);                     // 无边框
    lv_obj_set_style_bg_color(globeGUI.main_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT);                     // 设置背景颜色为黑色
    lv_obj_set_style_radius(globeGUI.main_obj, 0, LV_STATE_DEFAULT);                                            // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(globeGUI.main_obj, LV_OBJ_FLAG_SCROLLABLE);                                               // 关闭滚动
    lv_obj_set_size(globeGUI.main_obj, LV_PCT(100), LV_SIZE_CONTENT);                                           // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_set_flex_flow(globeGUI.main_obj, LV_FLEX_FLOW_COLUMN);                                               // 设置为水平布局
    lv_obj_set_flex_align(globeGUI.main_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    lv_obj_set_style_pad_row(globeGUI.main_obj, 5, 0); // 设置行间距为 0
    // lv_obj_set_style_pad_top(globeGUI.main_obj, -8, 0);  // 设置顶部间距为 0
    // lv_obj_set_style_pad_bottom(globeGUI.main_obj, -10, 0);   // 设置底部间距为 0
    lv_obj_set_size(globeGUI.main_obj, LCD_W, 76);            // 容器宽度为屏幕宽度，高度根据内容确定
    lv_obj_align(globeGUI.main_obj, LV_ALIGN_TOP_MID, 0, 39); // 显示位置

    globeGUI.log_img = lv_img_create(globeGUI.main_obj); // LOG
                                                         // lv_obj_align(globeGUI.log_img, LV_ALIGN_CENTER, 0, 0);

    /*----- 以下是根据运行状态刷新LOG部分的UI显示 ------*/
    switch (globeState.show_main)
    {
    case ShowTaskARun:
    case ShowTaskBRun:
    case ShowTaskCRun:
    case ShowTaskDRun:
    case ShowReturnHome:
    case ShowTaskAppRun:
    {
        anchor_animation_del();
        if (globeGUI.log_img)
        {
            lv_obj_del(globeGUI.log_img);
            globeGUI.log_img = NULL;
        }
        if (globeGUI.main_label)
        {
            lv_obj_del(globeGUI.main_label);
            globeGUI.main_label = NULL;
        }
        if (globeGUI.main_label2)
        {
            lv_obj_del(globeGUI.main_label2);
            globeGUI.main_label2 = NULL;
        }
        task_animation_init(globeState.show_main);
    }
    break;
    case ShowMainLogo:
    {
        task_animation_del();
        anchor_animation_del();
        if (globeState.GhostModeEn == 0)
        {
            if (globeGUI.log_img == NULL)
            {
                globeGUI.log_img = lv_img_create(globeGUI.main_obj); // LOG
            }
            if (globeState.BoatVersion == CatchX_MAX)
            {
                lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + MAIN_LOG_IMG_ID_OFFSET]);
                lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                log_info("显示CatchX_MAX LOG");
            }
            else if (globeState.BoatVersion == Rogue_MAX)
            {
                lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + ROGUE_MAX_IMG_ID]);
                lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                log_info("显示Rogue_MAX LOG");
            }
            else if (globeState.BoatVersion == CatchX_Ultra)
            {
                lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + CATCHX_ULTRA_IMG_ID]);
                lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                log_info("显示CatchX_Ultra LOG");
            }
            if (globeGUI.main_label)
            {
                lv_obj_del(globeGUI.main_label);
                globeGUI.main_label = NULL;
            }
            if (globeGUI.main_label2)
            {
                lv_obj_del(globeGUI.main_label2);
                globeGUI.main_label2 = NULL;
            }
        }
        else
        {
            if (globeGUI.log_img == NULL)
            {
                globeGUI.log_img = lv_img_create(globeGUI.main_obj); // LOG
            }
            lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[GhostMain_IMG1_ID]);
            lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
            if (globeGUI.main_label == NULL)
            {
                globeGUI.main_label = lv_label_create(globeGUI.main_obj);
                lv_obj_set_style_text_color(globeGUI.main_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
            }
            lv_obj_set_style_text_font(globeGUI.main_label, &font_blod_18, LV_STATE_DEFAULT);
            lv_label_set_text(globeGUI.main_label, PopUpLanguage[GhostModeON_Lang_ID][configParam.language]);
        }
    }
    break;
    case ShowCruise:
    {
        task_animation_del();
        anchor_animation_del();
        lv_img_set_src(globeGUI.log_img, &cruise_img);
        lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
    }
    break;
    case ShowAnchor:
    {
        task_animation_del();
        anchor_animation_init();
        if (globeState.TaskPresetUi.ui_obj && globeState.TaskPresetFlag != 0)
        {
            lv_obj_set_parent(globeState.TaskPresetUi.ui_obj, lv_scr_act());
        }
        else if (globeGUI.home_img)
        {
            lv_obj_move_foreground(globeGUI.home_img);
        }
        if (globeGUI.log_img)
        {
            lv_obj_del(globeGUI.log_img);
            globeGUI.log_img = NULL;
        }
        if (globeGUI.main_label)
        {
            lv_obj_del(globeGUI.main_label);
            globeGUI.main_label = NULL;
        }
        if (globeGUI.main_label2)
        {
            lv_obj_del(globeGUI.main_label2);
            globeGUI.main_label2 = NULL;
        }
        if (globePopUp.PopUp_obj && !globePopUp.PopUpSize)
        {
            lv_obj_add_flag(globeGUI.Anchor_obj, LV_OBJ_FLAG_HIDDEN); // 隐藏图片
        }
    }
    break;
    case ShowTaskScan:
    {
        task_animation_del();
        anchor_animation_del();
        if (globeGUI.log_img)
        {
            lv_obj_del(globeGUI.log_img);
            globeGUI.log_img = NULL;
        }
        lv_obj_set_flex_flow(globeGUI.main_obj, LV_FLEX_FLOW_COLUMN); // 设置为多行布局
        if (globeGUI.main_label == NULL)
        {
            globeGUI.main_label = lv_label_create(globeGUI.main_obj);
            lv_obj_set_style_text_color(globeGUI.main_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        }
        lv_obj_set_style_text_font(globeGUI.main_label, &font_blod_18, LV_STATE_DEFAULT); // 字体文件
        lv_obj_set_align(globeGUI.main_label, LV_ALIGN_TOP_MID);
        if (globeGUI.main_label2 == NULL)
        {
            globeGUI.main_label2 = lv_label_create(globeGUI.main_obj);
            lv_obj_set_style_text_color(globeGUI.main_label2, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
        }
        lv_obj_set_style_text_font(globeGUI.main_label2, &font_18, LV_STATE_DEFAULT); // 字体文件
        lv_obj_set_align(globeGUI.main_label2, LV_ALIGN_BOTTOM_MID);
        lv_label_set_text(globeGUI.main_label2, PopUpLanguage[ScanningTask_Lang_ID][configParam.language]);
        if (globeState.ScanTaskRemainTime >= 60)
        {
            lv_label_set_text_fmt(globeGUI.main_label, "%s%d%s",
                                  PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                  (uint16_t)(globeState.ScanTaskRemainTime / 60.0f + 0.5f),
                                  PopUpLanguage[Minute_Lang_ID][configParam.language]);
        }
        else if (globeState.ScanTaskRemainTime == 0)
        {
            lv_label_set_text_fmt(globeGUI.main_label, "%s -- %s",
                                  PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                  PopUpLanguage[Minute_Lang_ID][configParam.language]);
        }
        else
        {
            lv_label_set_text_fmt(globeGUI.main_label, "%s%s%d%s",
                                  PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                  PopUpLanguage[LessThanLang_ID][configParam.language],
                                  1,
                                  PopUpLanguage[Minute_Lang_ID][configParam.language]);
        }
    }
    break;
    default:
    {
        break;
    }
    }
    globeState.show_mainRefresh = globeState.show_main;
/*--------------------- end ---------------------*/
#endif

    /*------------------------------------ 上下左右阴影显示 --------------------------------------*/
#if 1
    // Write codes screen_cont_up
    globeGUI.screen_cont_up = lv_obj_create(globeGUI.screen);
    lv_obj_set_pos(globeGUI.screen_cont_up, 10, -1);
    lv_obj_set_size(globeGUI.screen_cont_up, 300, 1);
    lv_obj_set_scrollbar_mode(globeGUI.screen_cont_up, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_cont_up, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(globeGUI.screen_cont_up, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(globeGUI.screen_cont_up, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_down
    globeGUI.screen_cont_down = lv_obj_create(globeGUI.screen);
    lv_obj_set_pos(globeGUI.screen_cont_down, 10, 173);
    lv_obj_set_size(globeGUI.screen_cont_down, 300, 1);
    lv_obj_set_scrollbar_mode(globeGUI.screen_cont_down, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_cont_down, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(globeGUI.screen_cont_down, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(globeGUI.screen_cont_down, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_left
    globeGUI.screen_cont_left = lv_obj_create(globeGUI.screen);
    lv_obj_set_pos(globeGUI.screen_cont_left, -1, 10);
    lv_obj_set_size(globeGUI.screen_cont_left, 1, 152);
    lv_obj_set_scrollbar_mode(globeGUI.screen_cont_left, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_cont_left, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(globeGUI.screen_cont_left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(globeGUI.screen_cont_left, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_right
    globeGUI.screen_cont_right = lv_obj_create(globeGUI.screen);
    lv_obj_set_pos(globeGUI.screen_cont_right, 321, 10);
    lv_obj_set_size(globeGUI.screen_cont_right, 1, 152);
    lv_obj_set_scrollbar_mode(globeGUI.screen_cont_right, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_cont_right, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(globeGUI.screen_cont_right, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(globeGUI.screen_cont_right, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (globeState.motor_error_code == DETECT_STALL_STARTUP_FAIL)
    {
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else if (globeState.motor_error_code == DETECT_STALL_WARN_HIGH_CUR)
    {
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else if (globeState.motor_error_code == DETECT_STALL_FLAG_HIGH_CUR)
    {
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_style_shadow_opa(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // Write codes screen_cont_hint
    globeGUI.screen_cont_hint = lv_obj_create(globeGUI.screen);
    lv_obj_set_pos(globeGUI.screen_cont_hint, 26, 51);
    lv_obj_set_size(globeGUI.screen_cont_hint, 268, 45);
    lv_obj_set_scrollbar_mode(globeGUI.screen_cont_hint, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_hint, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(globeGUI.screen_cont_hint, 212, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x584328), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(globeGUI.screen_cont_hint, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_cont_hint, 22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_cont_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_img_hint
    globeGUI.screen_img_hint = lv_img_create(globeGUI.screen_cont_hint);
    lv_obj_add_flag(globeGUI.screen_img_hint, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(globeGUI.screen_img_hint, &icon_shield);
    lv_img_set_pivot(globeGUI.screen_img_hint, 50, 50);
    lv_img_set_angle(globeGUI.screen_img_hint, 0);
    lv_obj_set_pos(globeGUI.screen_img_hint, 19, 12);
    lv_obj_set_size(globeGUI.screen_img_hint, 18, 21);

    // Write style for screen_img_hint, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(globeGUI.screen_img_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(globeGUI.screen_img_hint, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_img_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(globeGUI.screen_img_hint, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_arc_hint
    globeGUI.screen_arc_hint = lv_arc_create(globeGUI.screen_cont_hint);
    lv_arc_set_mode(globeGUI.screen_arc_hint, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(globeGUI.screen_arc_hint, 0, 360);
    lv_arc_set_bg_angles(globeGUI.screen_arc_hint, 0, 360);
    lv_arc_set_value(globeGUI.screen_arc_hint, 0);
    lv_arc_set_rotation(globeGUI.screen_arc_hint, 0);
    lv_obj_set_style_arc_rounded(globeGUI.screen_arc_hint, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(globeGUI.screen_arc_hint, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(globeGUI.screen_arc_hint, 11, 6);
    lv_obj_set_size(globeGUI.screen_arc_hint, 34, 34);

    // Write style for screen_arc_hint, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(globeGUI.screen_arc_hint, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(globeGUI.screen_arc_hint, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(globeGUI.screen_arc_hint, lv_color_hex(0x796b59), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_arc_hint, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_arc_hint, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(globeGUI.screen_arc_hint, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(globeGUI.screen_arc_hint, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(globeGUI.screen_arc_hint, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for screen_arc_hint, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(globeGUI.screen_arc_hint, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(globeGUI.screen_arc_hint, 5, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_label_1
    globeGUI.screen_label_1 = lv_label_create(globeGUI.screen_cont_hint);
    lv_label_set_text(globeGUI.screen_label_1, PopUpLanguage[ElectricDriveProtection_Lang_ID][configParam.language]);
    lv_label_set_long_mode(globeGUI.screen_label_1, LV_LABEL_LONG_WRAP);
    if (configParam.language == SIMPLE_CHINESE)
    {
        lv_obj_set_pos(globeGUI.screen_label_1, 44, 14);
        lv_obj_set_style_text_font(globeGUI.screen_label_1, &font_blod_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_pos(globeGUI.screen_label_1, 44, 15);
        lv_obj_set_style_text_font(globeGUI.screen_label_1, &font_blod_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    lv_obj_set_size(globeGUI.screen_label_1, 220, 37);

    // Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(globeGUI.screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(globeGUI.screen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(globeGUI.screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(globeGUI.screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (globeState.motor_error_code == DETECT_STALL_STARTUP_FAIL)
    {
        lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x371215), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
        lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
    }
    else if (globeState.motor_error_code == DETECT_STALL_WARN_HIGH_CUR)
    {
        lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x584328), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
        lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
    }
    else if (globeState.motor_error_code == DETECT_STALL_FLAG_HIGH_CUR)
    {
        lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x584328), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
        lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
    }
    else
    {
        lv_obj_add_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 隐藏
        lv_obj_clear_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);       // 显示
    }
#endif
}

void boat_task_preset_ui_del(S_TaskPresetUi *BoatTaskPresetUi)
{
    if (BoatTaskPresetUi->ui_obj)
    {
        lv_obj_del(BoatTaskPresetUi->ui_obj);
        BoatTaskPresetUi->ui_obj = 0;
    }
    if (BoatTaskPresetUi->count_down_timer)
    {
        lv_timer_del(BoatTaskPresetUi->count_down_timer);
        BoatTaskPresetUi->count_down_timer = 0;
    }
}

static void boat_task_preset_ui_callback(lv_timer_t *timer)
{
    S_TaskPresetUi *BoatTaskPresetUi = timer->user_data;
    if (--(BoatTaskPresetUi->count_down_cnt))
    {
        lv_label_set_text_fmt(BoatTaskPresetUi->label_count_down, "%ds", BoatTaskPresetUi->count_down_cnt);
    }
    else
    {
        set_show_ui(MAIN_UI); // 这个函数调用会清零globeState.TaskPresetFlag
        mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
    }
}

void boat_task_preset_ui_init(S_TaskPresetUi *BoatTaskPresetUi)
{
    if (last_show_ui != MENU_UI)
    {
        BoatTaskPresetUi->count_down_cnt = 300;
    }

    if (BoatTaskPresetUi->ui_obj)
    {
        lv_label_set_text_fmt(BoatTaskPresetUi->label_count_down, "%ds", BoatTaskPresetUi->count_down_cnt);
        if (BoatTaskPresetUi->count_down_timer)
        {
            lv_timer_reset(BoatTaskPresetUi->count_down_timer);
        }
        return;
    }

    const char *BelowLanguage[3][LanguageMAX] = {
        {
            "任务光束中",
            "Task is being transferred",
            "TASK BEAM",
        },
        {
            "退出",
            "Exit",
            "Exit",
        },
        {
            "开始",
            "Go",
            "Go",
        },
    };

    BoatTaskPresetUi->count_down_timer = lv_timer_create(boat_task_preset_ui_callback, 1000, BoatTaskPresetUi);

    BoatTaskPresetUi->ui_obj = lv_obj_create(globeGUI.screen);
    lv_obj_set_style_border_opa(BoatTaskPresetUi->ui_obj, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(BoatTaskPresetUi->ui_obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(BoatTaskPresetUi->ui_obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(BoatTaskPresetUi->ui_obj, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(BoatTaskPresetUi->ui_obj, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(BoatTaskPresetUi->ui_obj, 320, 172);                                           // 容器宽度为屏幕宽度，高度根据内容确定
    // lv_obj_set_flex_flow(BoatTaskPresetUi->ui_obj , LV_FLEX_FLOW_COLUMN);                                               // 设置为水平布局
    // lv_obj_set_flex_align(BoatTaskPresetUi->ui_obj , LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

    BoatTaskPresetUi->label_title = lv_label_create(BoatTaskPresetUi->ui_obj);
    lv_obj_set_style_text_font(BoatTaskPresetUi->label_title, &font_blod_18, LV_STATE_DEFAULT);
    lv_label_set_text(BoatTaskPresetUi->label_title, (const char *)BelowLanguage[0][configParam.language]);
    lv_obj_set_style_text_color(BoatTaskPresetUi->label_title, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align(BoatTaskPresetUi->label_title, LV_ALIGN_TOP_MID, 0, 0);

    LV_IMG_DECLARE(icon_phone);
    BoatTaskPresetUi->img_phone = lv_img_create(BoatTaskPresetUi->ui_obj);
    lv_img_set_src(BoatTaskPresetUi->img_phone, &icon_phone);
    lv_obj_align(BoatTaskPresetUi->img_phone, LV_ALIGN_CENTER, -90, -5);

    LV_IMG_DECLARE(taskbeam);
    BoatTaskPresetUi->img_gif = lv_gif_create(BoatTaskPresetUi->ui_obj);
    lv_gif_set_src(BoatTaskPresetUi->img_gif, &taskbeam);
    lv_obj_align(BoatTaskPresetUi->img_gif, LV_ALIGN_CENTER, 0, -5);

    LV_IMG_DECLARE(icon_remote);
    BoatTaskPresetUi->img_remote = lv_img_create(BoatTaskPresetUi->ui_obj);
    lv_img_set_src(BoatTaskPresetUi->img_remote, &icon_remote);
    lv_obj_align(BoatTaskPresetUi->img_remote, LV_ALIGN_CENTER, 85, -5);

    BoatTaskPresetUi->obj_below = lv_obj_create(BoatTaskPresetUi->ui_obj);
    lv_obj_set_style_border_opa(BoatTaskPresetUi->obj_below, LV_OPA_0, LV_STATE_DEFAULT);             // 设置边框透明度
    lv_obj_set_style_border_side(BoatTaskPresetUi->obj_below, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
    lv_obj_set_style_bg_color(BoatTaskPresetUi->obj_below, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
    lv_obj_set_style_radius(BoatTaskPresetUi->obj_below, 0, LV_STATE_DEFAULT);                        // 设置样式对象的圆角半径为0
    lv_obj_clear_flag(BoatTaskPresetUi->obj_below, LV_OBJ_FLAG_SCROLLABLE);                           // 关闭滚动
    lv_obj_set_size(BoatTaskPresetUi->obj_below, 320, 30);                                            // 容器宽度为屏幕宽度，高度根据内容确定
    // lv_obj_set_flex_flow(BoatTaskPresetUi->obj_below, LV_FLEX_FLOW_ROW);                              // 设置为水平布局
    // lv_obj_set_flex_align(BoatTaskPresetUi->obj_below, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐
    lv_obj_align(BoatTaskPresetUi->obj_below, LV_ALIGN_BOTTOM_MID, 5, 10); // 显示位置

    BoatTaskPresetUi->img_enter = lv_img_create(BoatTaskPresetUi->obj_below);
    lv_img_set_src(BoatTaskPresetUi->img_enter, &enter_img);
    lv_obj_align(BoatTaskPresetUi->img_enter, LV_ALIGN_LEFT_MID, -10, 0);
    BoatTaskPresetUi->label_exit = lv_label_create(BoatTaskPresetUi->obj_below);
    lv_obj_set_style_text_font(BoatTaskPresetUi->label_exit, &font_18, LV_STATE_DEFAULT);
    lv_label_set_text(BoatTaskPresetUi->label_exit, (const char *)BelowLanguage[1][configParam.language]);
    lv_obj_set_style_text_color(BoatTaskPresetUi->label_exit, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(BoatTaskPresetUi->label_exit, BoatTaskPresetUi->img_enter, LV_ALIGN_OUT_RIGHT_MID, 4, 0);

    BoatTaskPresetUi->label_count_down = lv_label_create(BoatTaskPresetUi->obj_below);
    lv_obj_set_style_text_font(BoatTaskPresetUi->label_count_down, &font_18, LV_STATE_DEFAULT);
    // lv_label_set_text(BoatTaskPresetUi->label_count_down, (const char *)"180s");
    lv_label_set_text_fmt(BoatTaskPresetUi->label_count_down, "%ds", BoatTaskPresetUi->count_down_cnt);
    lv_obj_set_style_text_color(BoatTaskPresetUi->label_count_down, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align(BoatTaskPresetUi->label_count_down, LV_ALIGN_CENTER, 0, 0);

    BoatTaskPresetUi->img_start = lv_img_create(BoatTaskPresetUi->obj_below);
    lv_img_set_src(BoatTaskPresetUi->img_start, &start_img);
    lv_obj_align(BoatTaskPresetUi->img_start, LV_ALIGN_RIGHT_MID, -35, 0);
    BoatTaskPresetUi->label_start = lv_label_create(BoatTaskPresetUi->obj_below);
    lv_obj_set_style_text_font(BoatTaskPresetUi->label_start, &font_18, LV_STATE_DEFAULT);
    lv_label_set_text(BoatTaskPresetUi->label_start, (const char *)BelowLanguage[2][configParam.language]);
    lv_obj_set_style_text_color(BoatTaskPresetUi->label_start, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
    lv_obj_align_to(BoatTaskPresetUi->label_start, BoatTaskPresetUi->img_start, LV_ALIGN_OUT_RIGHT_MID, 4, 0);
}

static inline void boat_task_ui_task(void)
{
    static uint32_t delay_tick = 0;
    static bool flag = false;

    if (globeState.show_mainRefresh != globeState.show_main)
    {
        globeState.boatLEDStatRefresh = Refresh;
        globeState.show_mainRefresh = globeState.show_main;
        switch (globeState.show_main)
        {
        case ShowTaskARun:
        case ShowTaskBRun:
        case ShowTaskCRun:
        case ShowTaskDRun:
        case ShowReturnHome:
        case ShowTaskAppRun:
        {
            anchor_animation_del();
            if (globeGUI.log_img)
            {
                lv_obj_del(globeGUI.log_img);
                globeGUI.log_img = NULL;
            }
            if (globeGUI.main_label)
            {
                lv_obj_del(globeGUI.main_label);
                globeGUI.main_label = NULL;
            }
            if (globeGUI.main_label2)
            {
                lv_obj_del(globeGUI.main_label2);
                globeGUI.main_label2 = NULL;
            }
            task_animation_init(globeState.show_main);
        }
        break;
        case ShowMainLogo:
        {
            task_animation_del();
            anchor_animation_del();
            if (globeState.GhostModeEn == 0)
            {
                if (globeGUI.log_img == NULL)
                {
                    globeGUI.log_img = lv_img_create(globeGUI.main_obj); // LOG
                }
                if (globeState.BoatVersion == CatchX_MAX)
                {
                    lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + MAIN_LOG_IMG_ID_OFFSET]);
                    lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                    log_info("显示CatchX_MAX LOG");
                }
                else if (globeState.BoatVersion == Rogue_MAX)
                {
                    lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + ROGUE_MAX_IMG_ID]);
                    lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                    log_info("显示Rogue_MAX LOG");
                }
                else if (globeState.BoatVersion == CatchX_Ultra)
                {
                    lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[(globeState.AtHomeAndAbroad ? globeState.AtHomeAndAbroad - 1 : 0) + CATCHX_ULTRA_IMG_ID]);
                    lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                    log_info("显示CatchX_Ultra LOG");
                }
                else
                {
                    lv_obj_add_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 隐藏图片
                    log_info("隐藏LOG");
                }
                if (globeGUI.main_label)
                {
                    lv_obj_del(globeGUI.main_label);
                    globeGUI.main_label = NULL;
                }
                if (globeGUI.main_label2)
                {
                    lv_obj_del(globeGUI.main_label2);
                    globeGUI.main_label2 = NULL;
                }
            }
            else
            {
                if (globeGUI.main_label2)
                {
                    lv_obj_del(globeGUI.main_label2);
                    globeGUI.main_label2 = NULL;
                }
                if (globeGUI.main_label)
                {
                    lv_obj_del(globeGUI.main_label);
                    globeGUI.main_label = NULL;
                }
                if (globeGUI.log_img == NULL)
                {
                    globeGUI.log_img = lv_img_create(globeGUI.main_obj); // LOG
                }
                lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[GhostMain_IMG1_ID]);
                lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
                if (globeGUI.main_label == NULL)
                {
                    globeGUI.main_label = lv_label_create(globeGUI.main_obj);
                    lv_obj_set_style_text_color(globeGUI.main_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
                }
                lv_obj_set_style_text_font(globeGUI.main_label, &font_blod_18, LV_STATE_DEFAULT);
                lv_label_set_text(globeGUI.main_label, PopUpLanguage[GhostModeON_Lang_ID][configParam.language]);
                delay_tick = GetSysTick();
                flag = false;
            }
        }
        break;
        case ShowCruise:
        {
            task_animation_del();
            anchor_animation_del();
            lv_img_set_src(globeGUI.log_img, &cruise_img);
            lv_obj_clear_flag(globeGUI.log_img, LV_OBJ_FLAG_HIDDEN); // 显示图片
            if (globeGUI.main_label)
            {
                lv_obj_del(globeGUI.main_label);
                globeGUI.main_label = NULL;
            }
            if (globeGUI.main_label2)
            {
                lv_obj_del(globeGUI.main_label2);
                globeGUI.main_label2 = NULL;
            }
        }
        break;
        case ShowAnchor:
        {
            task_animation_del();
            anchor_animation_init();
            if (globeState.TaskPresetUi.ui_obj && globeState.TaskPresetFlag != 0)
            {
                lv_obj_set_parent(globeState.TaskPresetUi.ui_obj, lv_scr_act());
            }
            else if (globeGUI.home_img)
            {
                lv_obj_move_foreground(globeGUI.home_img);
            }

            if (globeGUI.log_img)
            {
                lv_obj_del(globeGUI.log_img);
                globeGUI.log_img = NULL;
            }
            if (globeGUI.main_label)
            {
                lv_obj_del(globeGUI.main_label);
                globeGUI.main_label = NULL;
            }
            if (globeGUI.main_label2)
            {
                lv_obj_del(globeGUI.main_label2);
                globeGUI.main_label2 = NULL;
            }
            if (globePopUp.PopUp_obj && !globePopUp.PopUpSize)
            {
                lv_obj_add_flag(globeGUI.Anchor_obj, LV_OBJ_FLAG_HIDDEN); // 隐藏图片
            }
        }
        break;
        case ShowTaskScan:
        {
            task_animation_del();
            anchor_animation_del();
            if (globeGUI.log_img)
            {
                lv_obj_del(globeGUI.log_img);
                globeGUI.log_img = NULL;
            }
            lv_obj_set_flex_flow(globeGUI.main_obj, LV_FLEX_FLOW_COLUMN); // 设置为多行布局
            if (globeGUI.main_label == NULL)
            {
                globeGUI.main_label = lv_label_create(globeGUI.main_obj);
                lv_obj_set_style_text_color(globeGUI.main_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
            }
            lv_obj_set_style_text_font(globeGUI.main_label, &font_blod_18, LV_STATE_DEFAULT); // 字体文件
            if (globeGUI.main_label2 == NULL)
            {
                globeGUI.main_label2 = lv_label_create(globeGUI.main_obj);
                lv_obj_set_style_text_color(globeGUI.main_label2, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
            }
            lv_obj_set_style_text_font(globeGUI.main_label2, &font_18, LV_STATE_DEFAULT); // 字体文件
            lv_label_set_text(globeGUI.main_label2, PopUpLanguage[ScanningTask_Lang_ID][configParam.language]);

            if (globeState.ScanTaskRemainTime >= 60)
            {
                lv_label_set_text_fmt(globeGUI.main_label, "%s%d%s",
                                      PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                      (uint16_t)(globeState.ScanTaskRemainTime / 60.0f + 0.5f),
                                      PopUpLanguage[Minute_Lang_ID][configParam.language]);
            }
            else if (globeState.ScanTaskRemainTime == 0)
            {
                lv_label_set_text_fmt(globeGUI.main_label, "%s -- %s",
                                      PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                      PopUpLanguage[Minute_Lang_ID][configParam.language]);
            }
            else
            {
                lv_label_set_text_fmt(globeGUI.main_label, "%s%s%d%s",
                                      PopUpLanguage[RemainTime_Lang_ID][configParam.language],
                                      PopUpLanguage[LessThanLang_ID][configParam.language],
                                      1,
                                      PopUpLanguage[Minute_Lang_ID][configParam.language]);
            }
        }
        break;
        default:
        {
            break;
        }
        }

        if (globePopUp.PopUp_obj)
        {
            lv_obj_move_foreground(globePopUp.PopUp_obj);
        }
    }

    if (globeState.GhostModeEn && globeState.show_main == ShowMainLogo && GetTimeInterval(delay_tick, GetSysTick()) >= 1000)
    {
        delay_tick = GetSysTick();
        if (flag)
        {
            flag = false;
            lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[GhostMain_IMG1_ID]);
        }
        else
        {
            flag = true;
            lv_img_set_src(globeGUI.log_img, LVGL_Img_Buff[GhostMain_IMG2_ID]);
        }
    }
}

void main_ui_refresh_task(void)
{
    if (key_main_ui()) // 这里切换到菜单了，下面的UI不能执行了
    {
        return;
    }
    long_pass_enter_cancel();
    boat_task();

    if (globeState.TaskPresetFlag == 0 || globeState.motor_error_code != DETECT_STALL_NO_ERROR)
    {
        char string[64];
        uint8_t value;
        /*- 以下是根据船是否连接遥控器和船的模式刷新UI显示 --*/
        if (globeState.isConnect)
        {
            if ((globeState.FCmodeRefresh != globeState.FCmode) || (globeState.ConnectRefresh != globeState.isConnect))
            {
                globeState.rf_rssiRefresh = Refresh;
                lv_obj_align(globeGUI.Connect_label, LV_ALIGN_LEFT_MID, -8, 0);
                lv_obj_set_style_text_font(globeGUI.Connect_label, &font_blod_18, LV_STATE_DEFAULT);
                globeState.FCmodeRefresh = globeState.FCmode;
                if (globeState.FCmode == 'M')
                {
                    lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT);
                    lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[ManualMode_Lang_ID][configParam.language]);
                    lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
                }
                else
                {
                    lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0x0000ff), LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 背景颜色渐变
                    lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[AutoMode_Lang_ID][configParam.language]);
                    lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
                }
            }
            globeState.ConnectRefresh = globeState.isConnect;

            if (globeState.rf_rssiRefresh != globeState.rf_rssi)
            {
                globeState.rf_rssiRefresh = globeState.rf_rssi;

#ifndef SHOW_RSSI_DB
                switch (globeState.rf_rssi)
                {
                case 5:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
                    lv_obj_set_size(globeGUI.RssiImg, 24, 24);
                }
                break;
                case 4:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 18, 0);
                    lv_obj_set_size(globeGUI.RssiImg, 18, 24);
                }
                break;
                case 3:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 14, 0);
                    lv_obj_set_size(globeGUI.RssiImg, 14, 24);
                }
                break;
                case 2:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 10, 0);
                    lv_obj_set_size(globeGUI.RssiImg, 10, 24);
                }
                break;
                case 1:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_set_size(globeGUI.RssiImg, 6, 24);
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20 - 24 + 6, 0);
                }
                break;
                default:
                {
                    lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[Signal_IMG_ID]); // 信号图标
                    lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
                    lv_obj_set_size(globeGUI.RssiImg, 24, 24);
                }
                break;
                }
#else
                sprintf(string, "%d", globeState.rf_rssi);
                lv_label_set_text(globeGUI.RssiImg, string);
#endif
            }
        }
        else if (globeState.ConnectRefresh != globeState.isConnect)
        {
            if (configParam.language == ENGLISH)
            {
                lv_obj_align(globeGUI.Connect_label, LV_ALIGN_LEFT_MID, -14, 0);
                lv_obj_set_style_text_font(globeGUI.Connect_label, &font_blod_14, LV_STATE_DEFAULT);
            }
            lv_obj_set_style_bg_color(globeGUI.Connect, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(globeGUI.Connect, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 背景颜色渐变
            lv_label_set_text(globeGUI.Connect_label, PopUpLanguage[Disconnected_Lang_ID][configParam.language]);
            lv_obj_set_style_text_color(globeGUI.Connect_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
#ifndef SHOW_RSSI_DB
            lv_img_set_src(globeGUI.RssiImg, LVGL_Img_Buff[DisSignal_IMG_ID]); // 断联图标
            lv_obj_set_size(globeGUI.RssiImg, 24, 24);
            lv_obj_align(globeGUI.RssiImg, LV_ALIGN_RIGHT_MID, -20, 0);
#else
            lv_label_set_text(globeGUI.RssiImg, 0);
#endif
            globeState.ConnectRefresh = globeState.isConnect;
        }
        /*--------------------- end ---------------------*/

        /*---------- 以下是根据卫星数量刷新UI显示 ---------*/
        if (globeState.isConnect)
        {
            if (globeState.satelliteNumRefresh != globeState.satelliteNum)
            {
                sprintf(string, "%2d", globeState.satelliteNum);
                lv_label_set_text(globeGUI.satellite_label, string);
                globeState.satelliteNumRefresh = globeState.satelliteNum;
            }
        }
        else
        {
            if (globeState.satelliteNumRefresh != 0xFFFF)
            {
                globeState.satelliteNumRefresh = 0xFFFF;
                lv_label_set_text(globeGUI.satellite_label, " --");
            }
        }
        /*--------------------- end ---------------------*/

        /*--------- 以下是根据遥控器电压刷新UI显示 --------*/
        if (globeState.batPercentRefresh != globeState.batPercent && !globeState.chargeStat)
        {
            globeState.batPercentRefresh = globeState.batPercent;
            lv_obj_set_style_bg_main_stop(globeGUI.remote_bat, (uint8_t)(globeState.batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 开始渐变位置
            lv_obj_set_style_bg_grad_stop(globeGUI.remote_bat, (uint8_t)(globeState.batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 结束渐变位置
            if (globeState.batPercent >= 40)
            {
                lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT);     // 开始渐变颜色
                lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 渐变成什么颜色
            }
            else if (globeState.batPercent >= 10)
            {
                lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(255, 130, 0), LV_STATE_DEFAULT);     // 开始渐变颜色
                lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(102, 53, 0), LV_STATE_DEFAULT); // 渐变成什么颜色
            }
            else
            {
                lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(242, 53, 48), LV_STATE_DEFAULT);     // 开始渐变颜色
                lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 渐变成什么颜色
            }
            sprintf(string, "R%3d%%", globeState.batPercent);
            lv_label_set_text(globeGUI.remote_bat_lable, string);
            lv_obj_add_flag(globeGUI.remote_boat_img, LV_OBJ_FLAG_HIDDEN);
        }
        else if (globeState.chargeStat && GetTimeInterval(globeGUI.charge_delay, GetSysTick()) >= 1000)
        {
            globeGUI.charge_delay = GetSysTick();

            lv_img_set_src(globeGUI.remote_boat_img, &icon_charging);                                                                      // 加载的图片
            lv_obj_set_style_bg_main_stop(globeGUI.remote_bat, (uint8_t)(globeGUI.Charge_batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 开始渐变位置
            lv_obj_set_style_bg_grad_stop(globeGUI.remote_bat, (uint8_t)(globeGUI.Charge_batPercent / 100.0f * 255.0f), LV_STATE_DEFAULT); // 结束渐变位置
            if (globeGUI.Charge_batPercent)
            {
                lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT); // 开始渐变颜色
            }
            else
            {
                lv_obj_set_style_bg_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 开始渐变颜色
            }
            lv_obj_set_style_bg_grad_color(globeGUI.remote_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 渐变成什么颜色

            if (globeState.chargeStat == charge_ok)
            {
                lv_label_set_text(globeGUI.remote_bat_lable, "   CHG");
                globeGUI.Charge_batPercent = 100;
            }
            else
            {
                lv_label_set_text(globeGUI.remote_bat_lable, "   CHG");
                globeGUI.Charge_batPercent += 20;
                if (globeGUI.Charge_batPercent > 100)
                {
                    globeGUI.Charge_batPercent = 0;
                }
            }
            lv_obj_clear_flag(globeGUI.remote_boat_img, LV_OBJ_FLAG_HIDDEN);
        }
        /*--------------------- end ---------------------*/

        /*----------- 以下是根据船电压刷新UI显示 ----------*/
        if (globeState.boat_voltage_batteryRefresh != globeState.boat_voltage_battery)
        {
            globeState.boat_voltage_batteryRefresh = globeState.boat_voltage_battery;
            value = getBatPercent((float)globeState.boat_voltage_battery / 1000.0f) * 2.55f;
            lv_obj_set_style_bg_main_stop(globeGUI.boat_bat, value, LV_STATE_DEFAULT); // 电量百分柱
            lv_obj_set_style_bg_grad_stop(globeGUI.boat_bat, value, LV_STATE_DEFAULT);
            if (!globeState.isConnect && globeState.boat_voltage_battery == 0)
            {
                lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT);
                lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 背景颜色渐变
            }
            else if (globeState.boat_voltage_battery >= 10785)
            {
                lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(4, 210, 82), LV_STATE_DEFAULT);
                lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(2, 84, 33), LV_STATE_DEFAULT); // 背景颜色渐变
            }
            else if (globeState.boat_voltage_battery >= 10200)
            {
                lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(255, 130, 0), LV_STATE_DEFAULT);
                lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(102, 53, 0), LV_STATE_DEFAULT); // 背景颜色渐变
            }
            else
            {
                lv_obj_set_style_bg_color(globeGUI.boat_bat, lv_color_make(242, 53, 48), LV_STATE_DEFAULT);
                lv_obj_set_style_bg_grad_color(globeGUI.boat_bat, lv_color_make(97, 21, 19), LV_STATE_DEFAULT); // 背景颜色渐变
            }
            if (globeState.isConnect)
            {
                sprintf(string, "B%2.1fV", globeState.boat_voltage_battery / 1000.0f);
            }
            else if (globeState.boat_voltage_battery == 0)
            {
                sprintf(string, "B     --");
            }
            lv_label_set_text(globeGUI.boat_bat_label, string);
        }
        /*--------------------- end ---------------------*/

        /*----- 以下是根据运行状态刷新LOG部分的UI显示 ------*/
        boat_task_ui_task();
        /*--------------------- end ---------------------*/

        /*--------- 以下是根据船的角度刷新的UI显示 ---------*/
        if (globeState.AngleRefresh != globeState.Angle)
        {
            globeState.AngleRefresh = globeState.Angle;

            lv_img_set_angle(globeGUI.navigation_img, globeState.Angle * 10);
        }
        /*--------------------- end ---------------------*/

        /*------------ 以下是根据AB点的UI显示 -------------*/
        if (globeState.PositionARefresh)
        {
            globeState.PositionARefresh = 0;

            if (globeState.Task_Sta.PositionA.degE7_lat && globeState.Task_Sta.PositionA.degE7_long)
            {
                lv_img_set_src(globeGUI.point_a_img, LVGL_Img_Buff[SaveA_IMG_ID]);
            }
            else
            {
                lv_img_set_src(globeGUI.point_a_img, LVGL_Img_Buff[NoSaveA_IMG_ID]);
            }
        }
        if (globeState.PositionBRefresh)
        {
            globeState.PositionBRefresh = 0;

            if (globeState.Task_Sta.PositionB.degE7_lat && globeState.Task_Sta.PositionB.degE7_long)
            {
                lv_img_set_src(globeGUI.point_b_img, LVGL_Img_Buff[SaveB_IMG_ID]);
            }
            else
            {
                lv_img_set_src(globeGUI.point_b_img, LVGL_Img_Buff[NoSaveB_IMG_ID]);
            }
        }
        if (globeState.PositionCRefresh)
        {
            globeState.PositionCRefresh = 0;

            if (globeState.Task_Sta.PositionC.degE7_lat && globeState.Task_Sta.PositionC.degE7_long)
            {
                lv_img_set_src(globeGUI.point_c_img, LVGL_Img_Buff[SaveC_IMG_ID]);
            }
            else
            {
                lv_img_set_src(globeGUI.point_c_img, LVGL_Img_Buff[NoSaveC_IMG_ID]);
            }
            if (configParam.AB_Mode == AB_MODE)
            {
                lv_obj_add_flag(globeGUI.point_c_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
            }
            else
            {
                lv_obj_clear_flag(globeGUI.point_c_img, LV_OBJ_FLAG_HIDDEN); // 显示
            }
        }
        if (globeState.PositionDRefresh)
        {
            globeState.PositionDRefresh = 0;

            if (globeState.Task_Sta.PositionD.degE7_lat && globeState.Task_Sta.PositionD.degE7_long)
            {
                lv_img_set_src(globeGUI.point_d_img, LVGL_Img_Buff[SaveD_IMG_ID]);
            }
            else
            {
                lv_img_set_src(globeGUI.point_d_img, LVGL_Img_Buff[NoSaveD_IMG_ID]);
            }
            if (configParam.AB_Mode == AB_MODE)
            {
                lv_obj_add_flag(globeGUI.point_d_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
            }
            else
            {
                lv_obj_clear_flag(globeGUI.point_d_img, LV_OBJ_FLAG_HIDDEN); // 显示
            }
        }

        /*--------------------- end ---------------------*/

        /*-------- 以下是根据船灯的状态刷新UI显示 ---------*/
        if (globeState.boatLEDStatRefresh != globeState.boatLEDStat)
        {
            globeState.boatLEDStatRefresh = globeState.boatLEDStat;
            if (globeState.GhostModeEn)
            {
                if (globeState.show_main != ShowMainLogo)
                {
                    lv_img_set_src(globeGUI.light_img, LVGL_Img_Buff[GhostMode_IMG_ID]);
                    lv_obj_clear_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 显示
                }
                else
                {
                    lv_obj_add_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
                }
            }
            else
            {
                lv_img_set_src(globeGUI.light_img, LVGL_Img_Buff[Light_IMG_ID]);
                if (globeState.boatLEDStat)
                {
                    lv_obj_clear_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 显示
                }
                else
                {
                    lv_obj_add_flag(globeGUI.light_img, LV_OBJ_FLAG_HIDDEN); // 隐藏
                }
            }
        }
        if (!globePopUp.PopUpSize && show_ui == MAIN_UI && globeGUI.light_img)
        {
            lv_obj_set_parent(globeGUI.light_img, lv_scr_act());
            // lv_obj_move_foreground(globeGUI.light_img);
        }

        /*------------ 以下是根据AB点的UI显示 ------------*/

        /*------ 以下是根据船距离Home点的距离UI显示 --- ----*/
        if (globeState.currentPosRefresh)
        {
            globeState.currentPosRefresh = 0;
            globeState.distance = get_distance((double)(globeState.current_position.degE7_lat - globeState.Reposition_Value.lat_Diff) / 10000000.0,
                                               (double)(globeState.current_position.degE7_long - globeState.Reposition_Value.long_Diff) / 10000000.0,
                                               globeState.home_position.degE7_lat / 10000000.0,
                                               globeState.home_position.degE7_long / 10000000.0);

            if (globeState.satelliteNum)
            {
                if (globeState.distance > 99000)
                {
                    sprintf(string, ">99Km");
                }
                else if (globeState.distance > 1000)
                {
                    sprintf(string, "%1.2fKm", globeState.distance / 1000.0f);
                }
                else
                {
                    sprintf(string, "%1.2fm", globeState.distance);
                }
            }
            else
            {
                sprintf(string, " --m");
            }
            lv_label_set_text(globeGUI.home_label, string);
        }
        /*--------------------- end ---------------------*/

        /*------------- 以下是船速度UI显示 ---------------*/
        if (globeState.speedRefresh != globeState.speed)
        {
            globeState.speedRefresh = globeState.speed;

            if (configParam.BoatSpeed == Speed_min)
            {
                lv_img_set_src(globeGUI.speed_img, &speed_low_s);
            }
            else if (configParam.BoatSpeed == Speed_normal)
            {
                lv_img_set_src(globeGUI.speed_img, &speed_medium_s);
            }
            else
            {
                lv_img_set_src(globeGUI.speed_img, &speed_high_s);
            }
            sprintf(string, "%1.1fm/s", globeState.speed);
            lv_label_set_text(globeGUI.speed_label, string);
        }
        /*--------------------- end ---------------------*/

        if (globeState.chargeStat == not_charging || globeState.chargeStat == delay_not_charging)
        {
            if (globeState.batPercent < 20 && globeGUI.RemoteLowPowerTime->paused)
            {
                lv_timer_resume(globeGUI.RemoteLowPowerTime);
            }
            else if (globeState.batPercent > 30 && !globeGUI.RemoteLowPowerTime->paused)
            {
                lv_timer_pause(globeGUI.RemoteLowPowerTime);
                lv_obj_set_style_bg_opa(globeGUI.remote_bat, 255, LV_STATE_DEFAULT);
            }
        }
        else if (!globeGUI.RemoteLowPowerTime->paused)
        {
            lv_timer_pause(globeGUI.RemoteLowPowerTime);
            lv_obj_set_style_bg_opa(globeGUI.remote_bat, 255, LV_STATE_DEFAULT);
        }

        if (globeState.isConnect)
        {
            uint8_t boat_bat_percent = getBatPercent(globeState.boat_voltage_battery / 1000.f);
            if (boat_bat_percent < 20 && globeGUI.BoatLowPowerTime->paused)
            {
                lv_timer_resume(globeGUI.BoatLowPowerTime);
            }
            else if (boat_bat_percent > 30 && !globeGUI.BoatLowPowerTime->paused)
            {
                lv_timer_pause(globeGUI.BoatLowPowerTime);
                lv_obj_set_style_bg_opa(globeGUI.boat_bat, 255, LV_STATE_DEFAULT);
            }
        }
        else if (!globeGUI.BoatLowPowerTime->paused)
        {
            lv_timer_pause(globeGUI.BoatLowPowerTime);
            lv_obj_set_style_bg_opa(globeGUI.boat_bat, 255, LV_STATE_DEFAULT);
        }

        /*------------------------------------ 上下左右阴影显示 --------------------------------------*/
        if (globeState.motor_error_code)
        {

            if (globeState.motor_error_tick == 0)
            {
                globeState.motor_error_tick = GetSysTick();

                if (globeState.CruiseSta)
                {
                    globeState.CruiseSta = 0;
                    LED_Cruise_Pin = LED_OFF;
                    globeState.show_main = ShowMainLogo;
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }

                if (globeState.motor_error_code > DETECT_STALL_WARN_HIGH_CUR)
                {
                    popup_init((lv_img_dsc_t *)&icon_alert_xl, NULL, NULL, (char *)PopUpLanguage[MotorStall_Lang_ID][configParam.language], POPUP_DELAY + POPUP_DELAY, 1);
                }
                else
                {
                    popup_init((lv_img_dsc_t *)&icon_alert_xl, NULL, NULL, (char *)PopUpLanguage[MotorAnomaly_Lang_ID][configParam.language], POPUP_DELAY + POPUP_DELAY, 1);
                }
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT * 3, 0, 0, 0, 1);
            }

            if (globeState.motor_error_code == DETECT_STALL_STARTUP_FAIL)
            {
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xb12723), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            else if (globeState.motor_error_code == DETECT_STALL_WARN_HIGH_CUR)
            {
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            else if (globeState.motor_error_code == DETECT_STALL_FLAG_HIGH_CUR)
            {
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_up, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_down, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_left, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_color(globeGUI.screen_cont_right, lv_color_hex(0xbb6100), LV_PART_MAIN | LV_STATE_DEFAULT);
            }

            if (globeState.motor_error_code == DETECT_STALL_STARTUP_FAIL)
            {
                lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x371215), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
                lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
            }
            else if (globeState.motor_error_code == DETECT_STALL_WARN_HIGH_CUR)
            {
                lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x584328), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
                lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
            }
            else if (globeState.motor_error_code == DETECT_STALL_FLAG_HIGH_CUR)
            {
                lv_obj_set_style_bg_color(globeGUI.screen_cont_hint, lv_color_hex(0x584328), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_add_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);           // 隐藏
                lv_obj_clear_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 显示
            }
            else
            {
                lv_obj_add_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 隐藏
                lv_obj_clear_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);       // 显示
            }

            static uint32_t last_time = 0;
            if (GetTimeInterval(last_time, GetSysTick()) >= 100)
            {
                last_time = GetSysTick();

                static uint8_t opa_value = 60;
                static uint8_t opa_flag = 0;
                if (opa_flag)
                {
                    opa_value -= 5;
                    if (opa_value <= 50)
                    {
                        opa_value = 50;
                        opa_flag = !opa_flag;
                    }
                }
                else
                {
                    opa_value += 5;
                    if (opa_value >= 100)
                    {
                        opa_value = 100;
                        opa_flag = !opa_flag;
                    }
                }
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_up, opa_value * 2.55f, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_down, opa_value * 2.55f, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_left, opa_value * 2.55f, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_right, opa_value * 2.55f, LV_PART_MAIN | LV_STATE_DEFAULT);
            }

            static uint32_t last_time_vibr = 0;
            if (GetTimeInterval(last_time_vibr, GetSysTick()) >= 2000)
            {
                last_time_vibr = GetSysTick();
                if (!TimeControl[Vibr_Motor_ID].CNT)
                {
                    Time_Control_Set_Value(Vibr_Motor_ID, 50, 0, 50, 0, 0, 0, 1);
                }
            }

            uint32_t current_tick = GetTimeInterval(globeState.motor_error_tick, GetSysTick());
            if (current_tick >= 60 * 1000)
            {
                globeState.motor_error_code = DETECT_STALL_NO_ERROR;
                globeState.motor_error_tick = 0;

                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_shadow_opa(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                lv_obj_add_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 隐藏
                lv_obj_clear_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);       // 显示

                show_popup(Success_IMG_ID, PowerRestored_Lang_ID, Invalid_Lang_ID, 0);
            }
            lv_arc_set_value(globeGUI.screen_arc_hint, current_tick * 360 / (60 * 1000));
        }
        else if (globeState.motor_error_tick)
        {
            globeState.motor_error_code = DETECT_STALL_NO_ERROR;
            globeState.motor_error_tick = 0;

            lv_obj_set_style_shadow_opa(globeGUI.screen_cont_up, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(globeGUI.screen_cont_down, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(globeGUI.screen_cont_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(globeGUI.screen_cont_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_obj_add_flag(globeGUI.screen_cont_hint, LV_OBJ_FLAG_HIDDEN); // 隐藏
            lv_obj_clear_flag(globeGUI.main_obj, LV_OBJ_FLAG_HIDDEN);       // 显示

            show_popup(Success_IMG_ID, PowerRestored_Lang_ID, Invalid_Lang_ID, 0);
        }
    }
    else
    {
        boat_task_ui_task();
    }

    if (globeState.BoatLowPowerFlag == 1)
    {
        globeState.BoatLowPowerFlag = 2;
        show_popup(LowPower_IMG_ID, Boat_LowerPower_Lang_ID, Invalid_Lang_ID, 0);
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 5000, 0, 0, 0, 1);
    }
    else if (globeState.RemoteLowPowerFlag == 1)
    {
        globeState.RemoteLowPowerFlag = 2;
        show_popup(LowPower_IMG_ID, Remote_LowerPower_Lang_ID, Invalid_Lang_ID, 0);
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
    }
}

int boat_task_init(S_Position *Position, uint8_t IsAppTask, E_TaskRunInit TaskRunInit, uint8_t Hopper, uint8_t Home, uint8_t led_on_off, uint8_t Hook, uint8_t need_popup)
{
    int ret = 0;
    S_Position Task_Position;

    switch (TaskRunInit)
    {
    case TaskA:
    case TaskB:
    case TaskC:
    case TaskD:
    case TaskH:
    case TaskApp:
    {
        globeState.HopperCurrentItem = 0;
        globeState.HomeCurrentItem = 0;
        globeState.HookCurrentItem = 0;
        globeState.TaskPointCurrentItem = 0;
        globeState.currentItem = 0;
        globeState.missionStat = MISSION_IDEL;

        if (Position == NULL)
        {
            ret = 1;
        }
        else
        {
            if (IsAppTask == 0)
            {
                Task_Position.degE7_lat = Position->degE7_lat + globeState.Reposition_Value.lat_Diff;
                Task_Position.degE7_long = Position->degE7_long + globeState.Reposition_Value.long_Diff;
            }
            else
            {
                Task_Position = *Position;
            }
            Debug("degE7_lat: %d", Task_Position.degE7_lat);
            Debug("degE7_long: %d", Task_Position.degE7_long);
            globeState.IsUpTask = 1;
            if (Task_Uploading(Task_Position, TaskRunInit, Hopper, Home, Hook, need_popup))
            {
                globeState.TaskPosition = Task_Position;
                globeState.task_distance = get_distance(globeState.TaskPosition.degE7_lat / 10000000.0, globeState.TaskPosition.degE7_long / 10000000.0,
                                                        globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0);
                Debug("globeState.task_distance: %3.2f", globeState.task_distance);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                ret = 1;
            }
            else
            {
                globeState.IsUpTask = 0;
                if (globeState.CruiseSta)
                {
                    globeState.CruiseSta = 0;
                    globeState.show_main = ShowMainLogo;
                    globeState.NowTask.TaskType = TaskClear;
                    globeState.NowTask.LED_Sta = globeState.boatLEDStat;
                    globeState.NowTask.Hopper = 0;
                    globeState.NowTask.ReturnHome = 0;
                    globeState.NowTask.Hook = 0;
                }
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
    }
    break;
    case TaskCruise:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (!globeState.CruiseSta)
            {
                float speed_value = 1;

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

                if (globeState.custom_mode != ROVER_MODE_MANUAL)
                {
                    if (need_popup)
                    {
                        show_popup(Fail_IMG_ID, NotExecuteDuringTask_Lang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    }
                }
                else
                {
                    if (my_mavlink_msg_command((MAV_CMD)59999, speed_value, 0, 0, 0, 0, 0, 0, 1))
                    {
                        ret = 1;
                        if (need_popup)
                        {
                            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                        }
                    }
                    else
                    {
                        LED_Cruise_Pin = LED_OFF;
                        if (need_popup)
                        {
                            show_popup(Fail_IMG_ID, CruiseFail_Lang_ID, Invalid_Lang_ID, 0);
                            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                        }
                    }
                }
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    case TaskLED:
    {
        if (!globeState.GhostModeEn)
        {
            if (led_on_off)
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_SERVO, 5, 2500, 0, 0, 0, 0, 0, 1))
                {
                    ret = 1;
                    globeState.boatLEDStat = 1;
                }
            }
            else
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_SERVO, 5, 0, 0, 0, 0, 0, 0, 1))
                {
                    ret = 1;
                    globeState.boatLEDStat = 0;
                }
            }
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
        }
    }
    break;
    case TaskHopper:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            LED_Cab_Pin = LED_ON;
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_SERVO, 6, 1100, 0, 0, 0, 0, 0, 1))
            {
                ret = 1;
                if (need_popup)
                {
                    show_popup(Success_IMG_ID, CabOK_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                }
            }
            else if (need_popup)
            {
                show_popup(Fail_IMG_ID, CabFail_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
            LED_Cab_Pin = LED_OFF;
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    case TaskScan:
    {
        ret = 1;
    }
    break;
    case TaskHook:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_SERVO, 7, 2000, 0, 0, 0, 0, 0, 1))
            {
                ret = 1;
                if (need_popup)
                {
                    show_popup(Success_IMG_ID, HookOK_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                }
            }
            else if (need_popup)
            {
                show_popup(Fail_IMG_ID, HookFail_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    case TaskClear:
    {
        ret = 1;
    }
    break;
    }

    if (ret)
    {
        Task_Inform_Msg Task_Msg;
        switch (TaskRunInit)
        {
        case TaskA:
        case TaskB:
        case TaskC:
        case TaskD:
        case TaskH:
        case TaskApp:
        {
            Task_Msg.TaskType = TaskRunInit;
            Task_Msg.LED_Sta = globeState.boatLEDStat;
            Task_Msg.Hopper = Hopper;
            Task_Msg.ReturnHome = Home;
            Task_Msg.Hook = Hook;
            if (globeState.TaskPresetFlag != 0) // 预设任务不加纠偏值给App
            {
                Task_Msg.TaskPosition = *Position;
            }
            else
            {
                Task_Msg.TaskPosition = globeState.TaskPosition;
            }
            globeState.NowTask = Task_Msg;
            mavlink_msg_send_to_app(Task_Inform_Msg_ID, (const char *)&Task_Msg, sizeof(Task_Inform_Msg));

            globeState.CruiseSta = 0;
            LED_Cruise_Pin = LED_OFF;
            globeState.show_main = TaskRunInit;
            if (TaskRunInit < TaskH)
            {
                LED_TaskB_Pin = LED_ON;
            }
            else
            {
                LED_TaskB_Pin = LED_OFF;
            }
        }
        break;
        case TaskCruise:
        {
            globeState.NowTask.TaskType = TaskCruise;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
            memset((void *)&globeState.NowTask.TaskPosition, 0, sizeof(globeState.NowTask.TaskPosition));
            mavlink_msg_send_to_app(Task_Inform_Msg_ID, (const char *)&globeState.NowTask, sizeof(Task_Inform_Msg));

            globeState.missionStat = MISSION_IDEL;
            Debug("MISSION_IDEL----->1");
            globeState.CruiseSta = 1;
            globeState.show_main = ShowCruise;
            LED_Cruise_Pin = LED_ON;
            LED_TaskB_Pin = LED_OFF;
        }
        break;
        case TaskLED:
        case TaskHook:
        case TaskHopper:
        {
            Task_Msg.TaskType = TaskRunInit;
            Task_Msg.LED_Sta = globeState.boatLEDStat;
            Task_Msg.Hopper = 0;
            Task_Msg.ReturnHome = 0;
            Task_Msg.Hook = 0;
            memset((void *)&Task_Msg.TaskPosition, 0, sizeof(Task_Msg.TaskPosition));
            mavlink_msg_send_to_app(Task_Inform_Msg_ID, (const char *)&Task_Msg, sizeof(Task_Inform_Msg));
        }
        break;
        case TaskScan:
        {
            globeState.NowTask.TaskType = TaskScan;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
            memset((void *)&globeState.NowTask.TaskPosition, 0, sizeof(globeState.NowTask.TaskPosition));

            globeState.missionStat = MISSION_IDEL;
            Debug("MISSION_IDEL----->2");
            globeState.CruiseSta = 0;
            LED_Cruise_Pin = LED_OFF;
            globeState.show_main = ShowTaskScan;
            LED_TaskB_Pin = LED_OFF;
        }
        break;
        case TaskClear:
        default:
        {
            globeState.NowTask.TaskType = TaskClear;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
            memset((void *)&globeState.NowTask.TaskPosition, 0, sizeof(globeState.NowTask.TaskPosition));
            globeState.Recover_Task = globeState.NowTask;
            globeState.show_main = ShowMainLogo;
            LED_TaskB_Pin = LED_OFF;
            globeState.missionStat = MISSION_IDEL;
        }
        break;
        }

        globeState.show_mainRefresh = Refresh;
        return 1;
    }
    return 0;
}

void custom_key_function(uint8_t value)
{
    switch (value)
    {
    case KEY_NOT:
    {
    }
    break;
    case KEY_SIGN:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
            S_Marker_Point_Msg Marker_Point_Msg;
            Marker_Point_Msg.Position = globeState.current_position;
            mavlink_msg_send_to_app(Marker_Point_Msg_ID, (const char *)&Marker_Point_Msg, sizeof(S_Marker_Point_Msg));
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    case Cut_Boat_Speed:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (globeState.custom_mode != CUSTOM_AUTO)
            {
                int item = configParam.BoatSpeed + 1;
                if (item > 2)
                {
                    item = 0;
                }
                switch (item)
                {
                case 0:
                {
                    if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_LOW)) // 设置RTL速度
                    {
                        configParam.BoatSpeed = Speed_min;
                        NeedSave_User_Data();
                        show_popup(speed_low_IMG_ID, ExploreModeLang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    }
                    else
                    {
                        popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    }
                }
                break;
                case 1:
                {
                    if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_NORMA)) // 设置RTL速度
                    {
                        configParam.BoatSpeed = Speed_normal;
                        NeedSave_User_Data();
                        show_popup(speed_medium_IMG_ID, LowpowerModeLang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    }
                    else
                    {
                        popup_init((lv_img_dsc_t *)&Colse_img, NULL, NULL, (char *)PopUpLanguage[SetFail_Lang_ID][configParam.language], POPUP_DELAY, 1);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    }
                }
                break;
                case 2:
                {
                    if (globeState.isConnect && setParamAsync("RTL_SPEED", BoatSpeed_HIGH)) // 设置RTL速度
                    {
                        configParam.BoatSpeed = Speed_max;
                        NeedSave_User_Data();
                        show_popup(speed_high_IMG_ID, MovementModeLang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
                    }
                    else
                    {
                        show_popup(Fail_IMG_ID, SetFail_Lang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    }
                }
                break;
                }
                globeState.speedRefresh = Refresh;
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
                    if (my_mavlink_msg_command((MAV_CMD)59999, speed_value, 0, 0, 0, 0, 0, 0, 1))
                    {
                    }
                    else
                    {
                        show_popup(Fail_IMG_ID, CruiseFail_Lang_ID, Invalid_Lang_ID, 0);
                    }
                }
            }
            else
            {
                show_popup(Fail_IMG_ID, CanNotBeSet_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    case ElectronicAnchor:
    {
        if (globeState.custom_mode != ROVER_MODE_LOITER && !globeState.KeyInvalid)
        {
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, 1, ROVER_MODE_LOITER, 0, 0, 0, 0, 0, 1)) // 切悬停模式
            {
                globeState.custom_mode = ROVER_MODE_LOITER;
#ifdef RESTORE_PROGRESS_UI
                if (configParam.LongKeyCustom == ElectronicAnchor)
                {
                    globeState.KeyInvalid = 1; // 这里防止按键继续长按会显示取消的画面
                }
#endif
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);

                if (globeState.CruiseSta)
                {
                    globeState.NowTask.TaskType = TaskClear;
                    globeState.NowTask.LED_Sta = globeState.boatLEDStat;
                    globeState.NowTask.Hopper = 0;
                    globeState.NowTask.ReturnHome = 0;
                    globeState.NowTask.Hook = 0;

                    globeState.CruiseSta = 0;
                    globeState.show_main = ShowMainLogo;
                    LED_Cruise_Pin = LED_OFF;
                }
            }
            else
            {
                show_popup(Fail_IMG_ID, CommandFail_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
        else
        {
            if (globeState.Recover_Task.TaskType != TaskClear)
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_AUTO, 0, 0, 0, 0, 0, 1)) // 设置为auto模式
                {
                    globeState.custom_mode = CUSTOM_AUTO;
                    globeState.CruiseSta = 0;
                    LED_Cruise_Pin = LED_OFF;
                    globeState.NowTask = globeState.Recover_Task;
                    globeState.NowTask.LED_Sta = globeState.boatLEDStat;
                    if (globeState.NowTask.TaskType == TaskScan)
                    {
                        globeState.show_main = ShowTaskScan;
                    }
                    else if (globeState.TaskPointCurrentItem)
                    {
                        globeState.show_main = globeState.Recover_Task.TaskType;
                        globeState.missionStat = MISSION_EXEC;
                    }
                    else if (globeState.HopperCurrentItem)
                    {
                        globeState.show_main = ShowMainLogo;
                        globeState.missionStat = MISSION_EXEC;
                    }
                    else if (globeState.HomeCurrentItem)
                    {
                        globeState.show_main = ShowReturnHome;
                        globeState.missionStat = MISSION_EXEC;
                    }
                    globeState.Recover_Task.TaskType = TaskClear;
                    if (globeState.NowTask.TaskType < TaskH)
                    {
                        LED_TaskB_Pin = LED_ON;
                    }
                    else
                    {
                        LED_TaskB_Pin = LED_OFF;
                    }
                }
            }
            else
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_MANUAL, 0, 0, 0, 0, 0, 1)) // 设置为mannul模式
                {
                    globeState.custom_mode = CUSTOM_MANUAL;
                }
                lv_show_popup_del();
            }
        }
    }
    break;
    case CruiseControl:
    {
        boat_task_init(NULL, NULL, TaskCruise, NULL, NULL, NULL, 0, 1);
    }
    break;
    case FixTheDeviation:
    {
        if (globeState.satelliteNum > 0)
        {
            if (ROVER_MODE_AUTO != globeState.custom_mode && globeState.Recover_Task.TaskType == TaskClear)
            {
                if (globeState.ReferencePoint.degE7_lat && globeState.ReferencePoint.degE7_long)
                {
                    double distance = get_distance(globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0,
                                                   globeState.ReferencePoint.degE7_lat / 10000000.0, globeState.ReferencePoint.degE7_long / 10000000.0);
                    if (distance > 50)
                    {
                        show_popup(Reposition_IMG_ID, BeyondDistance_Lang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                        globeState.Reposition_Value.RepositionState = BeyondDistance;
                        log_warn("distance > 50");
                    }
                    else
                    {
                        globeState.Reposition_Value.lat_Diff = globeState.current_position.degE7_lat - globeState.ReferencePoint.degE7_lat;
                        globeState.Reposition_Value.long_Diff = globeState.current_position.degE7_long - globeState.ReferencePoint.degE7_long;
                        globeState.Reposition_Value.RepositionState = Success;
                        Debug("lat_Diff : %d", globeState.Reposition_Value.lat_Diff);
                        Debug("long_Diff : %d", globeState.Reposition_Value.long_Diff);
                        show_popup(Reposition_IMG_ID, RepositionOK_Lang_ID, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                    }
                }
                else
                {
                    show_popup(Fail_IMG_ID, NoReferencePoint_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    globeState.Reposition_Value.RepositionState = NoReferencePoint;
                    log_warn("NoReferencePoint");
                }
            }
            else
            {
                show_popup(Fail_IMG_ID, NotExecuteDuringTask_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                globeState.Reposition_Value.RepositionState = InTheTask;
                log_warn("InTheTask");
            }
        }
        else
        {
            show_popup(Fail_IMG_ID, RepositionFail_Lang_ID, Invalid_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            globeState.Reposition_Value.RepositionState = NoSatellite;
            log_warn("globeState.satelliteNum <= 13");
        }
        globeState.Reposition_CNT = 4;
        globeState.Reposition_Time = GetSysTick();
        Debug("mavlink_msg_send_to_app -> Reposition_Value_Msg_ID");
        mavlink_msg_send_to_app(Reposition_Value_Msg_ID, (const char *)&globeState.Reposition_Value, sizeof(S_Reposition_Value_Msg));
    }
    break;
    case GhostModeEnable:
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (globeState.GhostModeEn)
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
                    show_popup(Fail_IMG_ID, SetFail_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
            }
            else
            {
                set_show_ui(Ghost_Mode_Enable_Hint);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    break;
    }
}

uint8_t key_main_ui(void)
{
    static uint8_t task_en = 0xFF;

    /*---------------------------------- Key_TaskA ------------------------------------*/
    if (keyIsValue(Key_TaskA, short_release))
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (!(*((uint32_t *)&globeState.Task_Sta.GetPosA_En)))
            {
                Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut - 1) & (configParam.AB_Mode ? 3 : 1);
            }
            if (task_en == 0xFF)
            {
                Task_Set_Animation.last_item_cut = configParam.AB_Mode ? 3 : 1;
                Task_Set_Animation.item_cut = 0;
                task_en = Task_Set_Animation.item_cut;
                show_popup(SetPointA_IMG_ID + Task_Set_Animation.item_cut, SetPointA_Lang_ID + Task_Set_Animation.item_cut, Press_ENTER_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 50, 0, 0, 0, 1);
                LED_TaskA_Pin = LED_ON;
            }
            else if (Task_Set_Animation.animation_time == NULL)
            {
                Task_Set_Animation.last_item_cut = Task_Set_Animation.item_cut;
                Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut + 1) & (configParam.AB_Mode ? 3 : 1);
                task_en = Task_Set_Animation.item_cut;
                show_popup(SetPointA_IMG_ID + Task_Set_Animation.item_cut, SetPointA_Lang_ID + Task_Set_Animation.item_cut, Press_ENTER_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 50, 0, 0, 0, 1);
                LED_TaskA_Pin = LED_ON;
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    if (keyIsValue(Key_TaskA, long_pass))
    {
        // globeState.ShowPitch = !globeState.ShowPitch;
    }

    enum dir_e joystick2;
    if (*((uint32_t *)&globeState.Task_Sta.GetPosA_En))
    {
        joystick2 = getJoystick2Dir(0);
        switch (joystick2)
        {
        case BACK: // PITCH向后
            lv_show_popup_del();
            break;
        case FORWARD: // PITCH向前
            break;
        case RIGHT: // ROLL向右
            if (Task_Set_Animation.animation_time == NULL)
            {
                Task_Set_Animation.last_item_cut = Task_Set_Animation.item_cut;
                Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut + 1) & (configParam.AB_Mode ? 3 : 1);
                show_popup(SetPointA_IMG_ID + Task_Set_Animation.item_cut, SetPointA_Lang_ID + Task_Set_Animation.item_cut, Press_ENTER_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 50, 0, 0, 0, 1);
                LED_TaskA_Pin = LED_ON;
                task_en = Task_Set_Animation.item_cut;
            }
            break;
        case LEFT: // ROLL向左
            if (Task_Set_Animation.animation_time == NULL)
            {
                Task_Set_Animation.last_item_cut = Task_Set_Animation.item_cut;
                Task_Set_Animation.item_cut = (Task_Set_Animation.item_cut - 1) & (configParam.AB_Mode ? 3 : 1);
                show_popup(SetPointA_IMG_ID + Task_Set_Animation.item_cut, SetPointA_Lang_ID + Task_Set_Animation.item_cut, Press_ENTER_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 50, 0, 0, 0, 1);
                LED_TaskA_Pin = LED_ON;
                task_en = Task_Set_Animation.item_cut;
            }
            break;
        default:
            break;
        }
    }
    else if (globeState.Task_Sta.SetHome_En && BACK == getJoystick2Dir(0))
    {
        lv_show_popup_del();
    }

    /*---------------------------------- Key_TaskB ------------------------------------*/
    if (keyIsValue(Key_TaskB, short_release))
    {
        if (((uint8_t *)&globeState.Task_Sta.GetPosA_En)[task_en])
        {
            if (((S_Position *)&globeState.Task_Sta.PositionA)[task_en].degE7_lat &&
                ((S_Position *)&globeState.Task_Sta.PositionA)[task_en].degE7_long)
            {
                boat_task_init(&(((S_Position *)&globeState.Task_Sta.PositionA)[task_en]), 0, task_en, 0, 0, 0, NULL, 1);
            }
            else
            {
                show_popup(Fail_IMG_ID, No_point_was_set_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
        else if (globeState.TaskPresetFlag != 0)
        {
            if (globeState.App_Task_Msg.Position.degE7_lat && globeState.App_Task_Msg.Position.degE7_long)
            {
                if (boat_task_init((S_Position *)&globeState.App_Task_Msg.Position, 0, globeState.App_Task_Msg.TaskType,
                                   globeState.App_Task_Msg.Hopper, globeState.App_Task_Msg.Home, globeState.App_Task_Msg.LED_Sta, globeState.App_Task_Msg.Hook, 1))
                {
                    set_show_ui(MAIN_UI); // 这个函数调用会清零globeState.TaskPresetFlag
                    mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
                }
            }
            else
            {
                show_popup(Fail_IMG_ID, No_point_was_set_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExecuteTheTask_Lang_ID, Preselect_Point_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
        }
    }
    if (keyIsValue(Key_TaskB, long_pass))
    {
    }

    /*---------------------------------- Key_Cab ------------------------------------*/
    if (keyIsValue(Key_Cab, short_release))
    {
        if (globeState.BoatVersion == CatchX_MAX || globeState.BoatVersion == CatchX_Ultra)
        {
            Debug("globeState.custom_mode: %d\r", globeState.custom_mode);
            boat_task_init(NULL, NULL, TaskHopper, NULL, NULL, NULL, NULL, 1);
        }
    }
    if (keyIsValue(Key_Cab, long_pass))
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (globeState.BoatVersion == CatchX_MAX || globeState.BoatVersion == CatchX_Ultra)
            {
                uint8_t flag0 = 0, flag1 = 0;

                if (boat_task_init(NULL, NULL, TaskHopper, NULL, NULL, NULL, NULL, 0))
                {
                    flag0 = 1;
                }

                if (boat_task_init(NULL, NULL, TaskHook, NULL, NULL, NULL, NULL, 0))
                {
                    flag1 = 1;
                }

                if (flag0 && flag1)
                {
                    show_popup(Success_IMG_ID, DropHookOK_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                }
                else if (flag0 == 0 && flag1)
                {
                    show_popup(Fail_IMG_ID, CabFail_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
                else if (flag0 && flag1 == 0)
                {
                    show_popup(Fail_IMG_ID, HookFail_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
                else
                {
                    show_popup(Fail_IMG_ID, DropHookFail_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
            }
            else if (globeState.BoatVersion == Rogue_MAX)
            {
                boat_task_init(NULL, NULL, TaskHopper, NULL, NULL, NULL, NULL, 1);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    if (keyIsValue(Key_Cab, double_release))
    {
        if (globeState.BoatVersion == CatchX_MAX || globeState.BoatVersion == CatchX_Ultra)
        {
            boat_task_init(NULL, NULL, TaskHook, NULL, NULL, NULL, NULL, 1);
        }
    }

    /*---------------------------------- Key_Cruise ------------------------------------*/
    if (keyIsValue(Key_Cruise, short_release))
    {
        custom_key_function(configParam.ShortKeyCustom);
    }
    if (keyIsValue(Key_Cruise, long_pass))
    {
#ifdef RESTORE_PROGRESS_UI
        if (configParam.LongKeyCustom == ElectronicAnchor && globeState.KeyInvalid) // 这里是为了防止长按此按键显示恢复任务UI，触发按键长按检测
        {
            globeState.KeyInvalid = 0;
        }
        else
        {
            custom_key_function(configParam.LongKeyCustom);
        }
#else
        custom_key_function(configParam.LongKeyCustom);
#endif
    }
    if (globeState.KeyInvalid && !getkey_stat(Key_Cruise)) // 按键释放
    {
        globeState.KeyInvalid = 0; // 长按释放后才能检测
    }
    if (keyIsValue(Key_Cruise, double_release))
    {
        custom_key_function(configParam.DoubleKeyCustom);
    }

    if (globeState.CruiseSta)
    {
        if (rc_channels.chan3_raw < 1500 - 60)
        {
            globeState.CruiseSta = 0;
            LED_Cruise_Pin = LED_OFF;
            globeState.show_main = ShowMainLogo;
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
        }
    }
    else if (configParam.AutoCruiseEn && globeState.custom_mode == ROVER_MODE_MANUAL)
    {
        static uint32_t long_delay = 0;
        int16_t adcValue = getAdcValue(ADC_PITCH);
        if (adcValue < (configParam.jsParam.pitch.mid - configParam.jsParam.pitch.range_neg + 100) && (rc_channels.chan4_raw > 1470 && rc_channels.chan4_raw < 1530))
        {
            if (GetTimeInterval(long_delay, GetSysTick()) >= (configParam.AutoCruiseEn * 1000))
            {
                long_delay = GetSysTick();
                boat_task_init(NULL, NULL, TaskCruise, NULL, NULL, NULL, NULL, 1);
            }
        }
        else
        {
            long_delay = GetSysTick();
        }
    }

    /*---------------------------------- Key_OK ------------------------------------*/
    if (keyIsValue(Key_OK, short_release))
    {
        // globeState.motor_error_code = DETECT_STALL_WARN_HIGH_CUR;

        for (uint8_t i = 0; i < (configParam.AB_Mode ? 4 : 2); i++)
        {
            if (((uint8_t *)&globeState.Task_Sta.GetPosA_En)[i])
            {
                if (globeState.custom_mode != CUSTOM_AUTO)
                {
                    if (globeState.satelliteNum && my_mavlink_msg_command(MAV_CMD_WAYPOINT_USER_1, 0, 0, 0, 0, 0, 0, 0, 1))
                    {
                        // lv_img_set_src(Task_Set_Animation.img[i], PopUp_Img_Buff[SetPointA_IMG_ID + i][1]); // 设置图像源
                        show_popup(Success_IMG_ID, SetPointA_OK_Lang_ID + i, Invalid_Lang_ID, 0);
                        // Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                        ((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_lat = globeState.current_position.degE7_lat - globeState.Reposition_Value.lat_Diff;
                        ((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_long = globeState.current_position.degE7_long - globeState.Reposition_Value.long_Diff;
                        ((S_Position *)&globeState.Task_Sta.PositionA)[i].alt_mm = globeState.current_position.alt_mm - globeState.Reposition_Value.long_Diff;
                        if (configParam.SavePointAB)
                        {
                            // ((S_Position *)&configParam.PositionA)[i] = ((S_Position *)&globeState.Task_Sta.PositionA)[i]; // 这里configParam使用了单字节对齐，这里会有问题
                            switch (i)
                            {
                            case 0:
                                configParam.PositionA = globeState.Task_Sta.PositionA;
                                break;
                            case 1:
                                configParam.PositionB = globeState.Task_Sta.PositionB;
                                break;
                            case 2:
                                configParam.PositionC = globeState.Task_Sta.PositionC;
                                break;
                            case 3:
                                configParam.PositionD = globeState.Task_Sta.PositionD;
                                break;
                            }
                            NeedSave_User_Data();
                            Debug("degE7_lat %d: %d", i, ((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_lat);
                            Debug("degE7_long %d: %d", i, ((S_Position *)&globeState.Task_Sta.PositionA)[i].degE7_long);
                            Debug("alt_mm %d: %d", i, ((S_Position *)&globeState.Task_Sta.PositionA)[i].alt_mm);
                        }
                        ((uint8_t *)&globeState.PositionARefresh)[i] = 1;
                        remote_system_data_send_to_app();
                    }
                    else
                    {
                        show_popup(Fail_IMG_ID, SetPointA_Fail_Lang_ID + i, Invalid_Lang_ID, 0);
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                    }
                }
                else
                {
                    show_popup(Fail_IMG_ID, CanNotBeSet_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
            }
        }
        if (globeState.Task_Sta.SetHome_En)
        {
            if (globeState.satelliteNum > 13)
            {
                double degE7_lat = (double)(globeState.current_position.degE7_lat - globeState.Reposition_Value.lat_Diff) / 10000000.0;
                double degE7_long = (double)(globeState.current_position.degE7_long - globeState.Reposition_Value.long_Diff) / 10000000.0;
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_HOME, 0, 0, 0, 0, degE7_lat, degE7_long, 0, 1))
                {
                    globeState.home_sta = 1;
                    show_popup(Success_IMG_ID, SetHome_OK_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                }
                else
                {
                    show_popup(Fail_IMG_ID, SetHome_Fail_Lang_ID, Invalid_Lang_ID, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                }
            }
            else
            {
                show_popup(Fail_IMG_ID, Satellites_13_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            }
        }
    }
    if (keyIsValue(Key_OK, long_pass))
    {
    }

    /*---------------------------------- Key_Opt ------------------------------------*/
    if (keyIsValue(Key_Opt, short_release))
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (globeState.custom_mode != CUSTOM_AUTO)
            {
                memset((void *)&globeState.Task_Sta.GetPosA_En, 0, 5);
                globeState.Task_Sta.SetHome_En = 1;
                show_popup(SetHomePoint_IMG_ID, SetHome_Lang_ID, Press_ENTER_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
            }
            else
            {
                show_popup(Fail_IMG_ID, CanNotBeSet_Lang_ID, Invalid_Lang_ID, 0);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    if (keyIsValue(Key_Opt, long_pass))
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (boat_task_init((S_Position *)&globeState.home_position, 0, TaskH, 0, 0, NULL, NULL, 1))
            {
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }

    /*---------------------------------- Key_Power ------------------------------------*/
    if (keyIsValue(Key_Power, short_release)) // 示廓灯
    {
        if (!globeState.boatLEDStat)
        {
            if (boat_task_init(NULL, NULL, TaskLED, NULL, NULL, 1, NULL, 1)) // 开灯
            {
            }
        }
        else
        {
            if (boat_task_init(NULL, NULL, TaskLED, NULL, NULL, 0, NULL, 1)) // 关灯
            {
            }
        }
    }
    if (keyIsValue(Key_Power, double_release))
    {
        if (globeState.TaskPresetFlag != 0)
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
        else if (!globeState.cal_compass_stat)
        {
            lv_show_popup_del();
            set_show_ui(MENU_UI);
            return 1;
        }
    }

    /*---------------------------------- Key_Sign ------------------------------------*/
    if (keyIsValue(Key_Sign, short_release))
    {
    }
    if (keyIsValue(Key_Sign, long_pass))
    {
    }
    if (keyIsValue(Key_Sign, double_release))
    {
    }

    /*---------------------------------- Key_TaskAB ------------------------------------*/
    if (keyIsValue(Key_TaskAB, long_pass))
    {
        if (globeState.TaskPresetFlag == 0)
        {
            if (globeState.FCmode != 'M') // 切换手动模式
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_MANUAL, 0, 0, 0, 0, 0, 1))
                {
                    globeState.custom_mode = CUSTOM_MANUAL;
                }
            }

            if (my_mavlink_msg_command((MAV_CMD)42422, 0, 0, 0, 0, 0, 0, 0, 1))
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, LongMotorT, 0, 0, 2);
                boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);

                globeState.cal_compass_stat = 1;
                globeState.xgyro = 0;
                globeState.cal_timeout = GetSysTick();
                show_popup(Calibration_IMG_ID, Calibration_Lang_ID, Invalid_Lang_ID, 0);
            }
            else
            {
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                show_popup(Fail_IMG_ID, CalibrationFail_Lang_ID, Invalid_Lang_ID, 0);
            }
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitTaskPreset_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }

    if (globeState.cal_compass_stat)
    {
        if (globeState.xgyro == 5) // 成功
        {
            show_popup(Success_IMG_ID, CalibrationOK_Lang_ID, Invalid_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
            globeState.cal_compass_stat = 0;
            globeState.xgyro = 0;
        }
        else if (globeState.xgyro == 6) // 失败
        {
            show_popup(Fail_IMG_ID, CalibrationFail_Lang_ID, Invalid_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            globeState.cal_compass_stat = 0;
            globeState.xgyro = 0;
        }
        else
        {
            show_popup(Calibration_IMG_ID, Calibration_Lang_ID, Invalid_Lang_ID, 0);

            if (GetTimeInterval(globeState.cal_timeout, GetSysTick()) >= 60000) // 一分钟未完成就算超时
            {
                show_popup(Fail_IMG_ID, CalibrationFail_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
                globeState.cal_compass_stat = 0;
                globeState.xgyro = 0;
            }
        }
    }

    return 0;
}

void boat_task_arrive_cut_mode(void)
{
    globeState.Recover_Task.TaskType = TaskClear;

    if (configParam.BoatAnchorEn) // 任务完成后，这里有可能App抢先设置了模式
    {
        if (globeState.custom_mode != ROVER_MODE_LOITER)
        {
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, ROVER_MODE_LOITER, 0, 0, 0, 0, 0, 1)) // 到了任务点后切悬停模式
            {
                globeState.custom_mode = ROVER_MODE_LOITER;
            }
        }
    }
    else
    {
        if (globeState.custom_mode != ROVER_MODE_MANUAL)
        {
            if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, ROVER_MODE_MANUAL, 0, 0, 0, 0, 0, 1)) // 切换手动模式
            {
                globeState.custom_mode = ROVER_MODE_MANUAL;
            }
        }
    }
}

/* [rc-0001] RTL arrival latch: set once per RTL episode, cleared in heartbeat
 * handler (mavlink.c) when the boat reports a mode other than RTL. */
volatile uint8_t g_rth_arrival_done = 0;

/* [rc-0001] Arrival action, called at most once per RTL episode.
 * Anchor: boat already loiters inside RTL (reports mode 11), so send LOITER
 * once without waiting for ACK (no 3 s UI block, no retry flood). Mode shown
 * on screen follows the next HEARTBEAT, not a local guess.
 * No anchor: switch to MANUAL with the normal ACK wait (happens once). */
static void rth_arrival_cut_mode(void)
{
    if (configParam.BoatAnchorEn)
    {
        my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, ROVER_MODE_LOITER, 0, 0, 0, 0, 0, 0);
    }
    else
    {
        if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_MANUAL, 0, 0, 0, 0, 0, 1))
        {
            globeState.custom_mode = CUSTOM_MANUAL;
        }
    }
}

void boat_task(void)
{
    if (globeState.custom_mode == ROVER_MODE_RTL)
    {
        if (globeState.TaskPresetFlag != 0)
        {
            globeState.TaskPresetFlag = 0;
            set_show_ui(MAIN_UI);
            mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
        }

        static float last_distance;
        static uint32_t delay_tisk = 0;
        if (globeState.NowTask.TaskType != TaskH) // 船失联返航或者低电量返航了
        {
            globeState.NowTask.TaskType = TaskH;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;

            globeState.show_main = ShowReturnHome;
            globeState.CruiseSta = 0;
            LED_Cruise_Pin = LED_OFF;
            globeState.distance = get_distance((double)(globeState.current_position.degE7_lat - globeState.Reposition_Value.lat_Diff) / 10000000.0,
                                               (double)(globeState.current_position.degE7_long - globeState.Reposition_Value.long_Diff) / 10000000.0,
                                               globeState.home_position.degE7_lat / 10000000.0,
                                               globeState.home_position.degE7_long / 10000000.0);
            globeState.task_distance = globeState.distance;
            last_distance = globeState.distance;
            delay_tisk = GetSysTick();
        }
        if (globeState.distance > 20)
        {
            last_distance = globeState.distance;
            delay_tisk = GetSysTick();
        }
        if (GetTimeInterval(delay_tisk, GetSysTick()) >= 20000)
        {
            delay_tisk = GetSysTick();
            if (!g_rth_arrival_done && last_distance < (globeState.distance + 2) && last_distance > (globeState.distance - 2)) /* [rc-0001] once per RTL episode */
            {
                g_rth_arrival_done = 1;
                show_popup(TaskHome_IMG_ID, ArriveHome_Lang_ID, Invalid_Lang_ID, 0);
                Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                rth_arrival_cut_mode();
            }
        }

        if (!g_rth_arrival_done && globeState.distance < 1 && globeState.isConnect) /* [rc-0001] once per RTL episode */
        {
            g_rth_arrival_done = 1;
            show_popup(TaskHome_IMG_ID, ArriveHome_Lang_ID, Invalid_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            rth_arrival_cut_mode();
            globeState.NowTask.TaskType = TaskClear;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
            mavlink_msg_send_to_app(Task_Inform_Msg_ID, (const char *)&globeState.NowTask, sizeof(Task_Inform_Msg));
        }
    }
    else if (globeState.custom_mode == ROVER_MODE_LOITER) // 悬停模式显示锚定的图标
    {
        if (globeState.CruiseSta)
        {
            globeState.CruiseSta = 0;
            LED_Cruise_Pin = LED_OFF;

            globeState.NowTask.TaskType = TaskClear;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
        }
        if (globeState.show_main != ShowAnchor)
        {
            globeState.show_main = ShowAnchor;
        }
    }
    else if (globeState.custom_mode == ROVER_MODE_MANUAL)
    {
        if (globeState.show_main != ShowCruise)
        {
            globeState.NowTask.TaskType = TaskClear;
            globeState.NowTask.LED_Sta = globeState.boatLEDStat;
            globeState.NowTask.Hopper = 0;
            globeState.NowTask.ReturnHome = 0;
            globeState.NowTask.Hook = 0;
            globeState.show_main = ShowMainLogo;
        }
    }
    else if (globeState.custom_mode == ROVER_MODE_AUTO)
    {
        if (globeState.show_main == ShowAnchor)
        {
            globeState.show_main = ShowMainLogo;
        }
    }
    else if (globeState.show_main != ShowMainLogo)
    {
        globeState.show_main = ShowMainLogo;
    }

    if (globeState.TaskPresetFlag == 0 && (globeState.JoystickDelayTick == 0 || GetTimeInterval(globeState.JoystickDelayTick, GetSysTick()) >= 1500))
    {
        globeState.JoystickDelayTick = 0;

        if (globeState.motor_error_code)
        {
            static uint8_t flag = 0;
            if (globeState.Task_Sta.SetHome_En || *((uint32_t *)&globeState.Task_Sta.GetPosA_En))
            {
                flag = 0;
            }
            else
            {
                if ((rc_channels.chan3_raw != 1500 || rc_channels.chan4_raw != 1500))
                {
                    flag = 1;
                    if (configParam.PopUpFlag)
                    {
                        show_popup(warn_IMG_ID, ElectricDriveProtection4_Lang_ID, Invalid_Lang_ID, 0);
                    }
                    else
                    {
                        show_popup(warn_IMG_ID, ElectricDriveProtection2_Lang_ID, ElectricDriveProtection3_Lang_ID, 0);
                        lv_obj_move_foreground(globeGUI.screen_cont_up);
                        lv_obj_move_foreground(globeGUI.screen_cont_down);
                        lv_obj_move_foreground(globeGUI.screen_cont_left);
                        lv_obj_move_foreground(globeGUI.screen_cont_right);
                    }
                    uint8_t error = 1;
                    mavlink_msg_send_to_app(DriveProtectionActive_Msg_ID, (const char *)&error, sizeof(error));
                }
                else if (flag)
                {
                    flag = 0;
                    lv_show_popup_del();
                    lv_obj_clear_flag(globeGUI.home_label, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(globeGUI.home_img, LV_OBJ_FLAG_HIDDEN);
                    uint8_t error = 0;
                    mavlink_msg_send_to_app(DriveProtectionActive_Msg_ID, (const char *)&error, sizeof(error));
                }
            }
        }
        else if (globeState.custom_mode == ROVER_MODE_MANUAL || globeState.custom_mode == ROVER_MODE_AUTO) // 手动和自动的时候推动摇杆放大Home距离显示
        {
            exit_or_big_home_popup_prompt(1);
        }
        else // 长按enter退出自动驾驶
        {
            exit_or_big_home_popup_prompt(0);
        }
    }

    static uint32_t delay_tick = 0;
    static uint32_t delay_return_home_tick = 0;
    if (globeState.missionStat != MISSION_IDEL && globeState.custom_mode == CUSTOM_AUTO)
    {
        if (globeState.TaskPointCurrentItem && globeState.currentItem > globeState.TaskPointCurrentItem) // 任务点
        {
            globeState.TaskPointCurrentItem = 0;
            if (globeState.NowTask.TaskType != TaskApp)
            {
                show_popup(TaskA_IMG_ID + globeState.NowTask.TaskType, ArriveA_Lang_ID + globeState.NowTask.TaskType, Invalid_Lang_ID, 0);
            }
            else
            {
                show_popup(globeState.ShowTask_IMG_ID, ArriveApp_Lang_ID, Invalid_Lang_ID, 0);
            }
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
            globeState.show_main = ShowMainLogo;

            if (globeState.HomeCurrentItem)
            {
                if (globeState.HookCurrentItem == 0 && globeState.HopperCurrentItem == 0)
                {
                    delay_return_home_tick = 0;
                    Debug("delay_return_home_tick = 0");
                    globeState.task_distance = get_distance(globeState.home_position.degE7_lat / 10000000.0, globeState.home_position.degE7_long / 10000000.0,
                                                            globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0);
                    globeState.TaskPosition = globeState.home_position;
                    globeState.show_main = ShowReturnHome;
                }
                else
                {
                    delay_return_home_tick = GetSysTick();
                }
            }
            else if (globeState.HookCurrentItem == 0 && globeState.HopperCurrentItem == 0)
            {
                globeState.missionStat = MISSION_IDEL;
                Debug("MISSION_IDEL----->3");
                boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);
                boat_task_arrive_cut_mode();
            }
        }
        else if (globeState.HopperCurrentItem && globeState.currentItem > globeState.HopperCurrentItem) // 抛投
        {
            globeState.HopperCurrentItem = 0;

            delay_tick = GetSysTick();
            if (globeState.HookCurrentItem)
            {
                globeState.HookCurrentItem = 0;

                globeState.PopUp_Inform.img_id = Success_IMG_ID;
                globeState.PopUp_Inform.str1_id = DropHookOK_Lang_ID;
                globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
                globeState.PopUp_Inform.bar_en = 0;
                // show_popup(Success_IMG_ID, DropHookOK_Lang_ID, Invalid_Lang_ID, 0);
            }
            else
            {
                globeState.PopUp_Inform.img_id = Success_IMG_ID;
                globeState.PopUp_Inform.str1_id = CabOK_Lang_ID;
                globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
                globeState.PopUp_Inform.bar_en = 0;
                // show_popup(Success_IMG_ID, CabOK_Lang_ID, Invalid_Lang_ID, 0);
            }
            // Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);

            if (globeState.HomeCurrentItem)
            {
                delay_return_home_tick = GetSysTick();
            }
            else
            {
                globeState.missionStat = MISSION_IDEL;
                Debug("MISSION_IDEL----->4");
                boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);
                boat_task_arrive_cut_mode();
            }
        }
        else if (globeState.HookCurrentItem && globeState.currentItem > globeState.HookCurrentItem) // 抛钩
        {
            globeState.HookCurrentItem = 0;

            delay_tick = GetSysTick();
            globeState.PopUp_Inform.img_id = Success_IMG_ID;
            globeState.PopUp_Inform.str1_id = HookOK_Lang_ID;
            globeState.PopUp_Inform.str2_id = Invalid_Lang_ID;
            globeState.PopUp_Inform.bar_en = 0;
            // show_popup(Success_IMG_ID, HookOK_Lang_ID, Invalid_Lang_ID, 0);
            // Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);

            if (globeState.HomeCurrentItem)
            {
                delay_return_home_tick = GetSysTick();
            }
            else
            {
                globeState.missionStat = MISSION_IDEL;
                Debug("MISSION_IDEL----->5");
                boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);
                boat_task_arrive_cut_mode();
            }
        }
        else if (globeState.HomeCurrentItem && globeState.currentItem > globeState.HomeCurrentItem) // 返回home点
        {
            globeState.HomeCurrentItem = 0;
            show_popup(TaskHome_IMG_ID, ArriveHome_Lang_ID, Invalid_Lang_ID, 0);
            Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
            globeState.missionStat = MISSION_IDEL;
            Debug("MISSION_IDEL----->6");
            boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);
            boat_task_arrive_cut_mode();
        }
    }

    if (delay_tick && GetTimeInterval(delay_tick, GetSysTick()) >= (1500 + 1000))
    {
        delay_tick = 0;
        Debug("delay_tick = 0");
        globeState.PopUp_Inform.PopUp_EN = 1;
        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
    }
    if (delay_return_home_tick && GetTimeInterval(delay_return_home_tick, GetSysTick()) >= (1500 + 1500 + 1000))
    {
        delay_return_home_tick = 0;
        Debug("delay_return_home_tick = 0");
        globeState.task_distance = get_distance(globeState.home_position.degE7_lat / 10000000.0, globeState.home_position.degE7_long / 10000000.0,
                                                globeState.current_position.degE7_lat / 10000000.0, globeState.current_position.degE7_long / 10000000.0);
        globeState.TaskPosition = globeState.home_position;
        globeState.show_main = ShowReturnHome;
    }
}

void long_pass_enter_cancel(void)
{
    static uint8_t flag = 0;
    static uint8_t wait_key_release = 0;
    uint8_t sta = 0;

    if (wait_key_release == 0 && getkey_stat(Key_OK) && globeState.isConnect && (globeState.custom_mode != ROVER_MODE_MANUAL || globeState.TaskPresetFlag != 0))
    {
        if ((*((uint32_t *)&globeState.Task_Sta.GetPosA_En)) == 0 && globeState.Task_Sta.SetHome_En == 0)
        {
            if (globeState.TaskPresetFlag != 0)
            {
                show_popup(Fail_IMG_ID, ExitTaskPreset_Lang_ID, Release_ENTER_Lang_ID, 1);
                sta = 2;
            }
            else if (globeState.custom_mode == ROVER_MODE_LOITER)
            {
                show_popup(Fail_IMG_ID, ExitAnchor_Lang_ID, Release_ENTER_Lang_ID, 1);
                sta = 1;
            }
            else
            {
                show_popup(Fail_IMG_ID, AbortTask_Lang_ID, Release_ENTER_Lang_ID, 1);
            }
            if (!flag)
            {
                flag = 1;
            }
            if (globePopUp.BarValue > 100)
            {
                if (sta == 2)
                {
                    set_show_ui(MAIN_UI); // 这个函数调用会清零globeState.TaskPresetFlag
                    mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
                    Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                    show_popup(Success_IMG_ID, ExitOK_Lang_ID, Invalid_Lang_ID, 0);
                    flag = 0;
                    wait_key_release = 1;
                }
                else
                {
                    if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_MANUAL, 0, 0, 0, 0, 0, 1)) // 设置为mannul模式
                    {
                        Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, ShortMotorT, 0, 0, 2);
                        globeState.missionStat = MISSION_IDEL;
                        globeState.Recover_Task.TaskType = TaskClear;
                        Debug("MISSION_IDEL----->7");
                        if (sta == 1)
                        {
                            show_popup(Success_IMG_ID, ExitOK_Lang_ID, Invalid_Lang_ID, 0);
                        }
                        else
                        {
                            show_popup(Success_IMG_ID, AbortTaskOK_Lang_ID, Invalid_Lang_ID, 0);
                        }
                        boat_task_init(NULL, NULL, TaskClear, NULL, NULL, NULL, NULL, 1);
                        globeState.custom_mode = ROVER_MODE_MANUAL;
                        flag = 0;
                        wait_key_release = 1;
                    }
                    else
                    {
                        if (sta)
                        {
                            show_popup(Fail_IMG_ID, ExitFail_Lang_ID, Invalid_Lang_ID, 0);
                        }
                        else
                        {
                            show_popup(Fail_IMG_ID, AbortTaskFail_Lang_ID, Invalid_Lang_ID, 0);
                        }
                        flag = 0;
                        wait_key_release = 1;
                    }
                }
            }
        }
    }
    else if (flag)
    {
        flag = 0;
        lv_show_popup_del();
    }
    else if (!getkey_stat(Key_OK))
    {
        wait_key_release = 0;
    }

#ifdef RESTORE_PROGRESS_UI
    static uint8_t flag1 = 0;
    if (configParam.LongKeyCustom == ElectronicAnchor &&
        configParam.ShortKeyCustom != ElectronicAnchor &&
        configParam.DoubleKeyCustom != ElectronicAnchor &&
        getkey_stat(Key_Cruise) &&
        globeState.custom_mode == ROVER_MODE_LOITER &&
        globeState.KeyInvalid != 1)
    {
        globeState.KeyInvalid = 2; // 这里是为了恢复任务之后不能触发长按逻辑

        if (!flag1 && !globePopUp.BarValue)
        {
            flag1 = 1;
            show_popup(Continue_IMG_ID, Continue_Lang_ID, Release_Key_Lang_ID, 1);
        }

        if (globePopUp.BarValue > 100)
        {
            flag1 = 0;
            lv_show_popup_del();

            if (globeState.Recover_Task.TaskType != TaskClear)
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_AUTO, 0, 0, 0, 0, 0, 1)) // 设置为auto模式
                {
                    globeState.custom_mode = ROVER_MODE_AUTO;
                }
            }
            else
            {
                if (my_mavlink_msg_command(MAV_CMD_DO_SET_MODE, CUSTOM_MODE_ENABLED, CUSTOM_MANUAL, 0, 0, 0, 0, 0, 1)) // 设置为mannul模式
                {
                    globeState.custom_mode = ROVER_MODE_MANUAL;
                }
                lv_show_popup_del();
            }
        }
    }
    else if (flag1)
    {
        flag1 = 0;
        lv_show_popup_del();
    }
#endif
}

void exit_or_big_home_popup_prompt(uint8_t choose)
{
    static uint8_t flag = 0;

    if (globeState.Task_Sta.SetHome_En || *((uint32_t *)&globeState.Task_Sta.GetPosA_En))
    {
        flag = 0;
        return;
    }

    if ((rc_channels.chan3_raw != 1500 || rc_channels.chan4_raw != 1500))
    {
        flag = 1;
        if (choose)
        {
            show_home_popup();
        }
        else
        {
            show_popup(ExitAuto_IMG_ID, ExitAuto_Lang_ID, Long_ENTER_Lang_ID, 0);
        }
    }
    else if (flag)
    {
        flag = 0;
        lv_show_popup_del();
        lv_obj_clear_flag(globeGUI.home_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(globeGUI.home_img, LV_OBJ_FLAG_HIDDEN);
    }
}
