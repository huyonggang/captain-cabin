#ifndef __MAIN_UI_H
#define __MAIN_UI_H
#include <stdint.h>
#include <stdbool.h>
#include "lvgl.h"

#define LongMotorT 400
#define ShortMotorT 100
#define SetValidTime 3000

#define BOAT_BAT_MAX 12600.0f
#define BOAT_BAT_MIN 9000.0f

typedef struct
{
    uint8_t PopUp_EN;
    uint8_t img_id;
    uint8_t str1_id;
    uint8_t str2_id;
    uint8_t bar_en;
    uint8_t bar;
} S_PopUp_Inform; // 别的线程要显示，通知显示任务显示

typedef struct
{
    lv_obj_t *panel;
    lv_obj_t *buttons[4];
    lv_obj_t *img[4];
    lv_timer_t *animation_time;
    uint8_t zoom_value;
    uint8_t item_cut;
    uint8_t last_item_cut;
} S_Task_Set_Animation; // 设置任务点动画

enum
{
    TaskIcom0,
    TaskIcom1,
    TaskIcom2,
    TaskIcom3,
    TaskIcom4,
    TaskIcom5,
    TaskIcom6,
    TaskIcom7,
    TaskIcom8,
    TaskIcom9,
    TaskIcom10,
    TaskIcom11,
    TaskIcom12,
    TaskIcom13,
    TaskIcom14,
    TaskIcom15,
    TaskIcom16,
    TaskIcom17,
    TaskIcom18,
    TaskIcom19,
    TaskA_IMG_ID,
    TaskB_IMG_ID,
    TaskC_IMG_ID,
    TaskD_IMG_ID,
    TaskHome_IMG_ID, // 任务点图标

    Success_IMG_ID,
    Fail_IMG_ID,
    SetPointA_IMG_ID,
    SetPointB_IMG_ID,
    SetPointC_IMG_ID,
    SetPointD_IMG_ID,
    SetHomePoint_IMG_ID,
    _SetPointA_IMG_ID,
    _SetPointB_IMG_ID,
    _SetPointC_IMG_ID,
    _SetPointD_IMG_ID,
    ExitAuto_IMG_ID,
    Calibration_IMG_ID,
    LowPower_IMG_ID,

    UploadA_IMG_ID,
    UploadB_IMG_ID,
    UploadC_IMG_ID,
    UploadD_IMG_ID,
    UploadHome_IMG_ID,

    Continue_IMG_ID,
    Reposition_IMG_ID,
    Circle_IMG_ID,
    Trash_IMG_ID,
    speed_low_IMG_ID,
    speed_medium_IMG_ID,
    speed_high_IMG_ID,

    warn_IMG_ID,

    IMG_ID_MAX,
};

#define Task_IMG_ID_MAX (TaskHome_IMG_ID)

enum
{
    CatchX_BS_IMG_ID,       // 主界面显示"CatchXBlackxxxx"
    CatchX_BS_CH_IMG_ID,    // 主界面显示"黑武士"
    ROGUE_MAX_IMG_ID,       // 主界面显示"Rogue Max"
    ROGUE_MAX_CH_IMG_ID,    // 主界面显示"Rogue Max"
    CATCHX_ULTRA_IMG_ID,    // 主界面显示"CatchX Ultra"
    CATCHX_ULTRA_CH_IMG_ID, // 主界面显示"CatchX Ultra"
    SaveA_IMG_ID,           // 彩色A点图标
    NoSaveA_IMG_ID,         // 灰色A点图标
    SaveB_IMG_ID,           // 彩色B点图标
    NoSaveB_IMG_ID,         // 灰色B点图标
    SaveC_IMG_ID,           // 彩色C点图标
    NoSaveC_IMG_ID,         // 灰色C点图标
    SaveD_IMG_ID,           // 彩色D点图标
    NoSaveD_IMG_ID,         // 灰色D点图标
    Light_IMG_ID,           // 船灯图标
    Charging_IMG_ID,        // 充电图标
    Signal_IMG_ID,          // 信号图标
    DisSignal_IMG_ID,       // 断联图标
    Satellite_IMG_ID,       // 卫星图标
    Compass_IMG_ID,         // 指南针图标
    Navigation_IMG_ID,      // 指南针箭头
    Arrow1_IMG_ID,          // AC点选择箭头
    Arrow2_IMG_ID,          // BD点选择箭头
    GhostMode_IMG_ID,       // 幽灵模式图标
    GhostMain_IMG1_ID,      // 幽灵模式图标
    GhostMain_IMG2_ID,      // 幽灵模式图标
    MAIN_UI_ID_MAX,
};
#define MAIN_LOG_IMG_ID_OFFSET 0
enum
{
    PointA_Lang_ID,                   // A点
    PointB_Lang_ID,                   // B点
    PointC_Lang_ID,                   // C点
    PointD_Lang_ID,                   // D点
    SetPointA_Lang_ID,                // 设置A点
    SetPointB_Lang_ID,                // 设置B点
    SetPointC_Lang_ID,                // 设置C点
    SetPointD_Lang_ID,                // 设置D点
    SetHome_Lang_ID,                  // 设置返航点(这里五个枚举必须放在前五)
    SetPointA_OK_Lang_ID,             // 设置A点成功
    SetPointB_OK_Lang_ID,             // 设置B点成功
    SetPointC_OK_Lang_ID,             // 设置C点成功
    SetPointD_OK_Lang_ID,             // 设置D点成功
    SetHome_OK_Lang_ID,               // 设置返航点成功
    SetPointA_Fail_Lang_ID,           // 设置A点失败
    SetPointB_Fail_Lang_ID,           // 设置B点失败
    SetPointC_Fail_Lang_ID,           // 设置C点失败
    SetPointD_Fail_Lang_ID,           // 设置D点失败
    SetHome_Fail_Lang_ID,             // 设置返航点失败
    SetOK_Lang_ID,                    // 设置成功
    SetFail_Lang_ID,                  // 设置失败
    ArriveA_Lang_ID,                  // 到达任务点A
    ArriveB_Lang_ID,                  // 到达任务点B
    ArriveC_Lang_ID,                  // 到达任务点C
    ArriveD_Lang_ID,                  // 到达任务点D
    ArriveHome_Lang_ID,               // 到达返航点
    ArriveApp_Lang_ID,                // 到达任务点
    CruiseOK_Lang_ID,                 // 开始定速巡航
    CruiseFail_Lang_ID,               // 定速巡航失败
    CabOK_Lang_ID,                    // 抛投成功
    CabFail_Lang_ID,                  // 抛投失败
    RTHTask_Lang_ID,                  // 正在发送RTH指令
    RTH_OK_Lang_ID,                   // 指令成功
    ExitAuto_Lang_ID,                 // 退出自动驾驶
    ExitAnchor_Lang_ID,               // 退出电子锚？
    AbortTask_Lang_ID,                // 中止任务？
    AbortTaskOK_Lang_ID,              // 任务已中止
    AbortTaskFail_Lang_ID,            // 中止任务失败
    ExitFail_Lang_ID,                 // 退出失败
    ExitOK_Lang_ID,                   // 退出成功
    UpTask_Lang_ID,                   // 正在发送任务指令
    ManualMode_Lang_ID,               // 手动
    AutoMode_Lang_ID,                 // 自动驾驶
    Disconnected_Lang_ID,             // 设备未连接
    Calibration_Lang_ID,              // 水平校准中...
    CalibrationOK_Lang_ID,            // 校准成功
    CalibrationFail_Lang_ID,          // 校准失败
    AutoTaskOK_Lang_ID,               // 任务已执行
    CommandFail_Lang_ID,              // 命令执行失败
    Remote_LowerPower_Lang_ID,        // 遥控器电量低！
    Press_ENTER_Lang_ID,              // 短按Enter键
    Long_ENTER_Lang_ID,               // 长按Enter键
    Release_ENTER_Lang_ID,            // 松开Enter取消
    Release_Key_Lang_ID,              // 松开按键取消
    Continue_Lang_ID,                 // 继续出发
    PleaseConnectApp_Lang_ID,         // 请连接App使用
    RepositionOK_Lang_ID,             // 纠偏成功
    RepositionFail_Lang_ID,           // 纠偏失败
    CanNotBeSet_Lang_ID,              // 任务执行中，不可设置
    ScanningTask_Lang_ID,             // 正在执行扫描任务
    NotExecuteDuringTask_Lang_ID,     // 任务中不可执行
    RTH_Command_Lang_ID,              // 正在发送 RTH 指令
    No_point_was_set_Lang_ID,         // 未设置任务点
    Preselect_Point_Lang_ID,          // 请先选择任务点
    ExecuteTheTask_Lang_ID,           // 执行任务
    HookOK_Lang_ID,                   // 抛钩成功
    HookFail_Lang_ID,                 // 抛钩失败
    DropHookOK_Lang_ID,               // 抛仓、抛钩成功
    DropHookFail_Lang_ID,             // 抛仓、抛钩失败
    BeyondDistance_Lang_ID,           // 距离参照点过远, 纠偏失败
    NoReferencePoint_Lang_ID,         // 请连接App获取参照点
    ReferencePointAcquired_Lang_ID,   // 已获取参照点
    ReferencePointCleared_Lang_ID,    // 参照点已清除
    RemainTime_Lang_ID,               // 剩余
    Minute_Lang_ID,                   // 分钟
    LessThanLang_ID,                  // 小于
    ExploreModeLang_ID,               // 探索模式
    LowpowerModeLang_ID,              // 省电模式
    MovementModeLang_ID,              // 运动模式
    Satellites_13_Lang_ID,            // 卫星数需>13
    Boat_LowerPower_Lang_ID,          // 船电量低！
    ExitTaskPreset_Lang_ID,           // 退出任务光束
    ExitAfterTaskPreset_Lang_ID,      // 退出后可执行任务光束
    GhostModeON_Lang_ID,              // 已开启幽灵模式
    ElectricDriveProtection_Lang_ID,  // 电驱保护中，请稍后尝试操作
    MotorAnomaly_Lang_ID,             // 电机异常提示\n可能存在水草或异物缠绕风险
    MotorStall_Lang_ID,               // 电机堵转提示\n检测到电机严重堵转，动力输出已停止
    ElectricDriveProtection2_Lang_ID, // 电驱保护中
    ElectricDriveProtection3_Lang_ID, // 动力输出已停止, 请1分钟后尝试
    ElectricDriveProtection4_Lang_ID, // 电驱保护中\n动力输出已停止, 请1分钟后尝试
    PowerRestored_Lang_ID,            // 已恢复动力输出
    Language_ID_MAX,
    Invalid_Lang_ID = 0xFF,
};

typedef struct
{
    uint8_t PopUp_Top; // 弹框显示到最顶层
    uint8_t PopUpSize;
    uint8_t Pad_Top;
    uint8_t Bar_EN;
    uint8_t BarValue;
    uint8_t Count_Down;
    uint32_t Show_Time;
    uint32_t TimePeriod;
    uint32_t CallBackCount;
    char *PopUpStr1;
    char *PopUpStr2;
    char *PopUpStr3;
    lv_font_t *Str1_Font[2];
    lv_font_t *Str2_Font[2];
    lv_font_t *Str3_Font[2];
    lv_obj_t *label_1;
    lv_obj_t *label_2;
    lv_obj_t *label_3;
    lv_obj_t *obj_all;
    lv_obj_t *obj_Str1_label_1;
    const lv_img_dsc_t *img;
    const lv_img_dsc_t *img2;
    lv_obj_t *obj_img;
    lv_obj_t *PopUp_obj;
    lv_obj_t *bar;
    lv_timer_t *PopUpTime;
#ifndef OLD_SET_POINT_UI
    lv_obj_t *obj_below;
    lv_obj_t *label_enter;
    lv_obj_t *label_cut_point;
    lv_obj_t *label_task_start;
    lv_obj_t *img_enter;
    lv_obj_t *img_cut_point;
    lv_obj_t *img_task_start;
#endif
} S_PopUp;

typedef struct
{
    lv_obj_t *ui_obj;
    lv_obj_t *label_title;
    lv_obj_t *img_phone;
    lv_obj_t *img_gif;
    lv_obj_t *img_remote;
    lv_obj_t *obj_below;
    lv_obj_t *img_enter;
    lv_obj_t *label_exit;
    lv_obj_t *label_count_down;
    lv_obj_t *img_start;
    lv_obj_t *label_start;
    lv_timer_t *count_down_timer;
    uint16_t count_down_cnt;
} S_TaskPresetUi;

typedef enum
{
    ShowTaskARun,   // 显示执行A点动画
    ShowTaskBRun,   // 显示执行B点动画
    ShowTaskCRun,   // 显示执行C点动画
    ShowTaskDRun,   // 显示执行D点动画
    ShowReturnHome, // 显示返回Home点动画
    ShowTaskAppRun, // 显示执行App点动画
    ShowTaskScan,   // 显示扫描
    ShowCruise,     // 显示定速巡航动画
    ShowAnchor,     // 显示船锚
    ShowMainLogo,   // 显示LOG
    Refresh = 0xFF,
} E_MAIN_UI;

typedef enum
{
    TaskA,            // 执行A点
    TaskB,            // 执行B点
    TaskC,            // 执行C点
    TaskD,            // 执行D点
    TaskH,            // 返回Home点
    TaskApp,          // 执行手机任务点
    TaskScan,         // 扫描
    TaskCruise,       // 定速巡航
    TaskLED,          // 开灯
    TaskHopper,       // 抛仓
    TaskHook,         // 抛钩
    TaskA_Preset,     // 执行A点
    TaskB_Preset,     // 执行B点
    TaskC_Preset,     // 执行C点
    TaskD_Preset,     // 执行D点
    TaskH_Preset,     // 返回Home点
    TaskApp_Preset,   // 执行手机任务点
    TaskClear = 0xFF, // 清除任务
} E_TaskRunInit;

typedef struct
{
    int32_t degE7_lat;
    int32_t degE7_long;
    int32_t alt_mm;
} S_Position;

typedef struct
{
    uint8_t GetPosA_En;      // 是否使能获取航点A
    uint8_t GetPosB_En;      // 是否使能获取航点B
    uint8_t GetPosC_En;      // 是否使能获取航点A
    uint8_t GetPosD_En;      // 是否使能获取航点B
    uint8_t SetHome_En;      // 设置Home点标志
    S_Position PositionA;    // 任务点A的经纬度
    S_Position PositionB;    // 任务点B的经纬度
    S_Position PositionC;    // 任务点C的经纬度
    S_Position PositionD;    // 任务点D的经纬度
    S_Position TaskPosition; // 当前App任务点的经纬度
} S_Task_Sta;

extern S_PopUp globePopUp;
extern S_PopUp LastglobePopUp;
extern const lv_img_dsc_t *const LVGL_Img_Buff[MAIN_UI_ID_MAX];

void main_ui_test(void);
void main_ui_init(void);
void main_ui_refresh_task(void);
void lv_show_popup_del(void);
void long_pass_enter_cancel(void);
void popup_init(lv_img_dsc_t *img, char *str1, char *str2, char *str3, uint16_t Show_Time, uint8_t PopUpSize);
void lv_show_popup_init(S_PopUp *PopUp_);
void lv_show_popup_init1(S_PopUp *PopUp_);
void boat_task_preset_ui_del(S_TaskPresetUi *BoatTaskPresetUi);
void boat_task_preset_ui_init(S_TaskPresetUi *BoatTaskPresetUi);

int boat_task_init(S_Position *Position, uint8_t IsAppTask, E_TaskRunInit TaskRunInit, uint8_t Hopper, uint8_t Home, uint8_t led_on_off, uint8_t, uint8_t need_popup);
uint8_t key_main_ui(void);
void exit_or_big_home_popup_prompt(uint8_t choose);
void boat_task(void);

#endif /*__MAIN_UI_H*/
