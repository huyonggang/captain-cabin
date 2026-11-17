#ifndef __APP_MAVLINK_H
#define __APP_MAVLINK_H

#include "stdint.h"
#include "main_ui.h"

typedef enum
{
    Success,           // 成功
    Fail,              // 错误
    Need_Rq,           // 请求重传
    Nonsupport,        // 不支持的命令
    ErrParameter,      // 错误参数
    FirmwareCRC_ERROR, // 文件CRC校验错误
    SEQ_ERROR,         // 序号错误
} E_Ask_Data;          // 应答参数

typedef enum
{
    success,          // 成功
    fail,             // 错误
    InTheTask,        // 任务中
    NoReferencePoint, // 无参照点
    BeyondDistance,   // 距离过远
    NoSatellite,      // 没有卫星
    App_Request,      // app请求纠偏值
} E_RepositionState;  // 应答参数

typedef struct
{
    uint8_t Msg_ID;   // 应答相应的MSG ID
    uint8_t Ask_Data; // 应答参数
} S_MsgAsk_Msg;       // 应答

typedef struct
{
    uint8_t Command_ID; // 设置什么参数
    uint8_t Ask_Data;   // 应答参数
} S_ComAsk_Msg;         // 应答

typedef struct
{
    uint8_t size;             // 用于指向File_Buffer的大小(打包传输的时候去掉这个字节)
    uint8_t File_Buffer[255]; // 文件数据流
} S_File_Transmit;            // 文件传输

typedef enum
{
    OTA_File,           // OTA升级文件
    BootLoaderOTA_File, // OTA升级文件
} E_FileType;           // 传输文件类型

typedef struct
{
    uint8_t FileType;      // 传输文件类型
    uint32_t FileSize;     // 文件大小
    uint32_t FileCRC;      // 文件CRC校验
    uint8_t File_Name[64]; // 文件名称
} S_FileInfo;              // 文件信息

#pragma pack(1)
typedef struct
{
    uint8_t TaskType;        // 任务类型
    uint8_t LED_Sta;         // 船灯状态
    uint8_t Hopper;          // 当前任务是否抛仓
    uint8_t ReturnHome;      // 当前任务是否返航
    uint8_t Hook;            // 当前任务是否抛钩
    S_Position TaskPosition; // 记录当前任务的经纬度
} Task_Inform_Msg;

typedef struct
{
    uint8_t CommType;         // 当前无线模式
    uint8_t BoatAnchorEn;     // 到点是否锚定
    uint16_t SoftwareVersion; // 遥控器软件版本号
    uint16_t HardwareVersion; // 遥控器硬件版本号
    uint16_t Bat;             // 遥控器电池电压
    S_Position PositionA;     // 遥控器A点经纬度
    S_Position PositionB;     // 遥控器B点经纬度
    S_Position PositionC;     // 遥控器C点经纬度
    S_Position PositionD;     // 遥控器D点经纬度
    uint8_t AtHomeAndAbroad;  // 国内外
    uint8_t LOG;              // LOG
    Task_Inform_Msg NowTask;  // 记录当前执行的任务
    uint8_t chargeStat;       // 遥控器充电标志
} S_RemoteSysData_Msg;        // 遥控器系统数据
#pragma pack()

typedef struct
{
    uint8_t Request_Msg_ID; // 请求的Msg_ID
} S_SysDataRequest_Msg;     // 请求系统数据

typedef enum
{
    AppTaskSuccess,           // 成功
    AppTaskFail,              // 任务执行失败
    AppTaskInTheTask,         // 任务中不可执行任务光束
    AppTaskExitTheExecutable, // 退出后可执行任务光束
} E_App_Task_ASK_State;       // 应答参数

typedef struct
{
    uint8_t TaskType;    // 任务类型
    uint8_t Hopper;      // 是否抛仓(1：抛仓)
    uint8_t TaskIcom;    // 任务图标
    uint8_t LED_Sta;     // 开关灯
    uint8_t Home;        // 是否返回Home点
    uint8_t Hook;        // 是否抛钩
    S_Position Position; // 任务点经纬度
} S_App_Task_Msg;

typedef struct
{
    int32_t lat_Diff;
    int32_t long_Diff;
    int32_t alt_mm_Diff;
    uint32_t RepositionState;
} S_Reposition_Value_Msg;

typedef struct
{
    S_Position Position;
} S_Marker_Point_Msg;

typedef enum
{
    add,                  // 增加
    modification,         // 修改
    delete,               // 删除
    ErrorParameter,       // 参数错误
} E_SetPointAskParameter; // 应答参数

typedef struct
{
    uint8_t PointType;
    S_Position Position;
} S_SetPoint_Msg;

typedef enum
{
    BoatAnchorEn,    // 使能锚定
    AtHomeAndAbroad, // 设置国内外版本(1：国内   2：国外)
    LogSet,          // Log设置(0: INTREPID   1：CatchX mini   2：无畏)
    Reposition_REQ,  // 遥控器触发一键纠偏
} e_command_id;      // 设置什么参数

typedef struct
{
    uint8_t Command_ID;  // 设置什么参数
    uint32_t Parameter0; // 设置参数0
    uint32_t Parameter1; // 设置参数1
    uint32_t Parameter2; // 设置参数2
    uint32_t Parameter3; // 设置参数3
} S_Command_Data;        // 命令参数

typedef enum
{
    MsgASK_Msg_ID,                // 需要应答的Msg_ID的应答Msg_ID
    FileInfo_Msg_ID,              // 传输文件信息描述
    FileTransmit_Msg_ID,          // 传输文件的数据流
    RemoteSysData_Msg_ID,         // 遥控器系统数据
    SysDataRequest_Msg_ID,        // 请求遥控器系统数据
    Command_Msg_ID,               // 设置系统参数命令
    ComASK_Msg_ID,                // 设置系统参数命令应答
    Reposition_Value_Msg_ID,      // App和遥控器使用这个消息ID来同步纠偏值
    Task_Inform_Msg_ID,           // 遥控器做任务通知App
    Marker_Point_Msg_ID,          // 标记点
    App_Task_Msg_ID,              // App通知遥控器做相应任务
    ReferencePoint_Msg_ID,        // App给的参照点
    ScanTaskRemainTime_Msg_ID,    // 扫描任务剩余时间
    TaskUpProg_Msg_ID,            // 任务上传进度
    BoatVoltage_Msg_ID,           // 船的电压平均值
    BoatSpeed_Msg_ID,             // 船速
    SetPoint_Msg_ID,              // 设置遥控器ABCD点
    SetPointASK_Msg_ID,           // 设置遥控器ABCD参数应答
    ClearTaskPreset_Msg_ID,       // 清除船的预设点位通知
    RemoteVoltagePercent_Msg_ID,  // 遥控器的电压百分比
    DriveProtectionActive_Msg_ID, // 电驱保护激活
    HardFaultMsg_Msg_ID = 255,    // 程序异常堆栈信息获取
} E_Msg_ID;                       // 消息ID, 用于判断有效载荷数据的类型

/*------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint8_t mode;        // 无线模式
} S_SetWirelessMode_Msg; // 设置无线模式

typedef struct
{
    uint8_t type;        // 0：设置WiFi名称 1：连接AP的WiFi名称 2：连接AP的WiFi名称后缀
    char name[64];       // 无线名字
} S_SetWirelessName_Msg; // 设置无线名字

typedef enum
{
    SetWirelessMode_Msg_ID = 7, // 设置linux数传声纳连接方式(0: 网线连接(内置声纳), 1: WiFi连接(外置声纳))
    SetWirelessName_Msg_ID,     // 设置无线名字和连接AP的WiFi名称Msg_ID
    BoatWiFiSignal_Msg_ID,      // 与船连接的WiFi信号强度
    WiFiCodeVersion_Msg_ID,     // 获取芯片厂商WiFi驱动ko固件mdk5sum校验
    CatFileMd5sum_Msg_ID,       // 查询文件mdk5sum校验
    AskFileMd5sum_Msg_ID,       // 回复文件mdk5sum校验
    LinuxCommand_Msg_ID,        // 执行终端命令
    AskLinuxCommand_Msg_ID,     // 执行的结果
    Firmware_Updata_OK_Msg_ID,  // 全部固件升级是否成功
    Sonar_Connect_Sta_Msg_ID,   // 声纳是否连接(未使用)
    ConnectSonarWiFi_Msg_ID,    // 要连接的声纳WiFi(未使用)
    MsgDebug_Msg_ID,            // 调试信息
} E_WiFiMsg_ID;                 // 消息ID, 用于判断有效载荷数据的类型(用于设置WiFi模块的一些参数)

uint8_t Cut_WiFi_BT_Mode(uint8_t mode);
uint8_t Set_WiFi_BT_Device_Name(char *deviceName);
void TaskUpProgSendApp(uint8_t progress);
void remote_system_data_send_to_app(void);

#endif
