#ifndef __MY_MAVLINK_H
#define __MY_MAVLINK_H
#include "mavlink_types.h"
#include "mavlink.h"
#include "common.h"
#include "mavlink_msg_rc_channels.h"
#include "config_param.h"
#include "main_ui.h"
#include "app_mavlink.h"

#pragma pack()
#include <stdbool.h>

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define CONNECT_CNT 10

#define CALIBR_START 0      // 开始采集
#define CALIBR_H_ROTATION 1 // 水平旋转采集
#define CALIBR_COLLATION 2  // 数据采集中
#define CALIBR_V_ROTATION 4 // 垂直旋转采集
#define CALIBR_SUCCESS 5    // 校准成功
#define CALIBR_FAIL 6       // 校准失败

#define BoatSpeed_LOW 0.5
#define BoatSpeed_NORMA 0.9
#define BoatSpeed_HIGH 1.1

typedef enum ROVER_MODE
{
    ROVER_MODE_MANUAL = 0,        /*  | */
    ROVER_MODE_ACRO = 1,          /*  | */
    ROVER_MODE_STEERING = 3,      /*  | */
    ROVER_MODE_HOLD = 4,          /*  | */
    ROVER_MODE_LOITER = 5,        /*  | */
    ROVER_MODE_AUTO = 10,         /*  | */
    ROVER_MODE_RTL = 11,          /*  | */
    ROVER_MODE_SMART_RTL = 12,    /*  | */
    ROVER_MODE_GUIDED = 15,       /*  | */
    ROVER_MODE_INITIALIZING = 16, /*  | */
    ROVER_MODE_ENUM_END = 17,     /*  | */
} ROVER_MODE;

enum MAV_BASE_MODE
{
    ///< summary> 0b00000001 Reserved for future use.
    CUSTOM_MODE_ENABLED = 1,
    ///< summary> 0b00000010 system has a test mode enabled. This flag is intended for temporary system tests and should not be used for stable implementations.
    TEST_ENABLED = 2,
    ///< summary> 0b00000100 autonomous mode enabled, system finds its own goal positions. Guided flag can be set or not, depends on the actual implementation.
    AUTO_ENABLED = 4,
    ///< summary> 0b00001000 guided mode enabled, system flies waypoints / mission items.
    GUIDED_ENABLED = 8,
    ///< summary> 0b00010000 system stabilizes electronically its attitude (and optionally position). It needs however further control inputs to move around.
    STABILIZE_ENABLED = 16,
    ///< summary> 0b00100000 hardware in the loop simulation. All motors / actuators are blocked, but internal software is full operational.
    HIL_ENABLED = 32,
    ///< summary> 0b01000000 remote control input is enabled. | </summary>
    MANUAL_INPUT_ENABLED = 64,
    ///< summary> 0b10000000 MAV safety set to armed. Motors are enabled / running / can start. Ready to fly. Additional note: this flag is to be ignore when sent in the command MAV_CMD_DO_SET_MODE and MAV_CMD_COMPONENT_ARM_DISARM shall be used instead. The flag can still be used to report the armed state. | </summary>
    SAFETY_ARMED = 128
};

enum MAV_CUSTOM_MODE
{
    CUSTOM_MANUAL = 0,
    CUSTOM_ACRO = 1,
    CUSTOM_STEERING = 3,
    CUSTOM_HOLD = 4,
    CUSTOM_LOITER = 5,
    CUSTOM_FOLLOW = 6,
    CUSTOM_SIMPLE = 7,
    CUSTOM_AUTO = 10,
    CUSTOM_RTL = 11,
    CUSTOM_SMART_RTL = 12,
    CUSTOM_GUIDED = 15,
    CUSTOM_INITIALISING = 16
};

enum
{
    MISSION_IDEL,
    MISSION_EXEC,
    MISSION_LOITER,
};

enum
{
    Init,         // 初始值
    Unknown_Boat, // 连上船了，获取版本中
    CatchX_MAX,
    Rogue_MAX,
    CatchX_Ultra,
};

enum
{
    DETECT_STALL_NO_ERROR = 0,      // 无异常
    DETECT_STALL_WARN_HIGH_CUR = 1, // 发现异常高电流但未到达最大的判定时间
    DETECT_STALL_FLAG_HIGH_CUR = 2, // 异常高电流超过最大电流的判定时间
    DETECT_STALL_STARTUP_FAIL = 3,  // 启动失败标志。对应外力完全阻挡电机(直接插只笔或完全缠绕)后，再次自动的连续十次启动失败

};

typedef struct
{
    uint8_t activeFlag;
    uint16_t msgid;
    uint16_t seq;
    uint8_t ACKtype;
} MISSIONSTATE;

typedef struct
{
    uint8_t ShowPitch;                       /* 显示摇杆值 */
    uint8_t BoatVersion;                     /* 判断是什么版本的船 */
    uint8_t Log;                             /* 开机log */
    uint8_t AtHomeAndAbroad;                 /* 国内外标记 */
    uint8_t DebugGrade;                      /* 日志打印等级 */
    uint8_t TaskPresetFlag;                  /* 预设任务标志 */
    uint8_t IsUpTask;                        /* 上传任务中 */
    uint8_t Reposition_CNT;                  /* 给App发送纠偏值App没有应答最大重发次数 */
    uint8_t PairSta;                         /* 数传对频 */
    uint8_t Task_Set_X;                      /* 这个是为了做ABCD切换动画 */
    E_MAIN_UI show_main;                     /* 屏幕中间位置显示log还是其他 */
    E_MAIN_UI show_mainRefresh;              /* 刷新ui */
    uint8_t Cut_Show_UI;                     /* 别的线程切换UI */
    uint8_t KeyInvalid;                      /* 按键无效 */
    uint8_t PointABSetItem;                  /* AB条目的位置位置 */
    uint8_t ShowTask_IMG_ID;                 /* 刷新ui */
    uint8_t PositionARefresh;                /* 刷新ui */
    uint8_t PositionBRefresh;                /* 刷新ui */
    uint8_t PositionCRefresh;                /* 刷新ui */
    uint8_t PositionDRefresh;                /* 刷新ui */
    uint8_t boatLEDStat;                     /* 船指示灯状态 */
    uint8_t Arrow1_AC;                       /* 执行A还是C任务标志(0: A 1: C) */
    uint8_t Arrow2_BD;                       /* 执行B还是D任务标志(0: B 1: D) */
    uint8_t boatLEDStatRefresh;              /* 刷新ui */
    uint8_t CruiseSta;                       /* 船的定速巡航状态 */
    uint8_t TaskCount;                       /* 做任务时发送指令数量 */
    uint8_t TaskAppCount;                    /* App做任务时发送指令数量 */
    uint8_t TaskAppSta;                      /* App做任务时发送指令数量 */
    uint8_t xgyro;                           /* 船磁罗盘校准回调 */
    uint8_t cal_compass_stat;                /* 遥控器触发磁罗盘校准标志 */
    uint8_t chargeStat;                      /* 遥控器充电状态 */
    uint8_t batPercent;                      /* 电池电量百分比 */
    uint8_t batPercentRefresh;               /* 刷新ui */
    uint8_t FCbatPercent;                    /* 船电池电量百分比 */
    uint8_t isConnect;                       /* 是否和船建立链接 */
    uint8_t ConnectRefresh;                  /* 刷新ui */
    uint8_t WiFiConnect;                     /* 是否和App建立链接 */
    uint8_t connectCnt;                      /* 有点像看门狗的计数 */
    uint8_t rf_rssiRefresh;                  /* 刷新ui */
    uint8_t wifi_rssi;                       /* WiFi信号强度 */
    uint8_t SetNameOK;                       /* 设置蓝牙或WiFi名称成功 */
    uint8_t SetCommModeOK;                   /* 切换蓝牙或WiFi模式成功 */
    uint8_t RemoteLowPowerFlag;              /* 0正常状态 1低电量报警状态 2低电量报警后按OK键，状态变成2 */
    uint8_t BoatLowPowerFlag;                /* 0正常状态 1低电量报警状态 2低电量报警后按OK键，状态变成2 */
    uint8_t currentPosRefresh;               /* 船的当前经纬度是否刷新 */
    uint8_t FCmode;                          /* 船的模式，手动，自动 */
    uint8_t FCmodeRefresh;                   /* 刷新ui */
    uint8_t missionStat;                     /* 遥控器任务标志 */
    uint8_t home_sta;                        /* 船是否设置成功Home点 */
    uint8_t App_Task_Flag;                   /* App是否发来任务 */
    uint8_t App_ASK;                         /* 遥控器请求数据App是否应答 */
    uint8_t GhostModeEn;                     /* 幽灵模式 */
    uint8_t read_pair_id_flag;               /* 读取图传配对的id标志 */
    uint8_t motor_error_code;                /* 错误代码 */
    uint16_t RemoteBat;                      /* 遥控器电池电压 */
    uint16_t currentItem;                    /* 任务到点序号 */
    uint16_t HopperCurrentItem;              /* 任务抛仓序号 */
    uint16_t HomeCurrentItem;                /* 任务返航序号 */
    uint16_t HookCurrentItem;                /* 任务抛钩序号 */
    uint16_t TaskPointCurrentItem;           /* 任务返航序号 */
    uint16_t boat_voltage_battery;           /* 船的电压*/
    uint16_t boat_voltage_batteryRefresh;    /* 刷新ui */
    uint16_t satelliteNum;                   /* gps卫星的数目 */
    uint16_t satelliteNumRefresh;            /* 刷新ui */
    uint16_t Angle;                          /* 船的航向角度 */
    uint16_t AngleRefresh;                   /* 刷新ui */
    uint16_t ScanTaskRemainTime;             /* 扫描任务剩余时间 */
    int rf_rssi;                             /* 无线信号强度 */
    uint32_t motor_error_tick;               /* 错误时间戳 */
    uint32_t currentItemUpdataTime;          /* 遥控器执行任务超时 */
    uint32_t custom_mode;                    /* 船的当前模式 */
    uint32_t PopUpValue;                     /* 弹框标志 */
    uint32_t cal_timeout;                    /* 磁罗盘校准超时 */
    uint32_t menu_timeout;                   /* 设置菜单未操作多久超时退出 */
    uint32_t set_id;                         /* 设置连接的wifi后缀 */
    uint32_t Reposition_Time;                /* 重发纠偏值时间基准 */
    uint32_t JoystickDelayTick;              /* 延迟检测放大离home点距离和长按enter提示 */
    uint32_t SuspendMavRecTaskTime;          /* 挂起接收船控数据的任务，多久超时 */
    float distance;                          /* 船到Home的距离 */
    float task_distance;                     /* 做任务的时候到Home点的距离 */
    float speed;                             /* 船的速度 */
    float speedRefresh;                      /* 船的速度 */
    S_Position current_position;             /* 船的当前位置(没有减纠偏) */
    S_Position home_position;                /* 船的Home点 */
    S_Position TaskPosition;                 /* 记录当前任务的经纬度 */
    S_Position ReferencePoint;               /* 参照点 */
    S_Task_Sta Task_Sta;                     /* 任务点数据 */
    S_App_Task_Msg App_Task_Msg;             /* App发来的任务 */
    S_Reposition_Value_Msg Reposition_Value; /* 纠偏值 */
    S_PopUp_Inform PopUp_Inform;             /* 通知显示任务显示 */
    Task_Inform_Msg NowTask;                 /* 记录当前执行的任务 */
    Task_Inform_Msg Recover_Task;            /* 恢复任务 */
    S_TaskPresetUi TaskPresetUi;             /* 预设任务UI结构体*/
} GLOBE_STATE;

extern TaskHandle_t ParseBoatMavTaskHandle;
extern SemaphoreHandle_t MavRecBinary;
extern TaskHandle_t JoystickSendHandle;
extern TaskHandle_t ParseAppMavTaskHandle;
extern SemaphoreHandle_t WiFiRecBinary;
volatile extern GLOBE_STATE globeState;
extern mavlink_rc_channels_t rc_channels;

double get_distance(double lat1, double lng1, double lat2, double lng2);
uint8_t my_mavlink_msg_command(MAV_CMD mav_cmd, float p1, float p2, float p3, float p4, float p5, float p6, float p7, uint8_t requireack);
uint8_t my_mavlink_msg_int_command(MAV_CMD mav_cmd, float p1, float p2, float p3, float p4, float x, float y, float z, uint8_t requireack);
void mavlink_rc_channels_t_send(void);
void parse_boat_mavlink_msg_task(void *param);
void joystick_value_send_to_boat(void *param);
void Show_Precision_Bar(uint8_t barCurr, uint8_t barTotal);
uint8_t Task_Uploading(S_Position TaskPosition, uint8_t take_num, uint8_t Hopper, uint8_t Home, uint8_t Hook, uint8_t need_bar);
void parse_app_mavlink_msg_task(void *param);
void mavlink_msg_send_to_app(uint8_t msgid, const char *packet, uint8_t length);
void parse_app_mavlink_messages(mavlink_message_t *msg);
void boat_dtu_return_mavlink_msg(mavlink_message_t *msg);
void TaskUpProgSendApp(uint8_t progress);

#endif
