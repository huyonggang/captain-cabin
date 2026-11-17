#ifndef __CONFIG_PARAM_H
#define __CONFIG_PARAM_H
#include <stdbool.h>
#include "sys.h"
#include "joystick.h"
#include "main_ui.h"

#define HardFaultMsg_PARAM_ADDR ADDR_FLASH_SECTOR_3 /*异常堆栈保存*/
enum
{
	BOOT_FIRST_ADDR,		 /*Boot第一次运行标记地址*/
	APP_FIRST_ADDR,			 /*App第一次运行标记地址*/
	LOG_ADDR,				 /*LOG标记地址*/
	AT_HOME_AND_ABROAD_ADDR, /*国内外标记地址*/
	OTA_DATA_ADD,			 /*OTA升级标记地址*/
	CONFIG_PARAM_ADDR = 100, /*配置参数保存地址*/
};

#define BOOT_FIRST_FLAG 0x23
#define APP_FIRST_FLAG 0x56

/* 默认配置参数 */
#define SoftwareVERSION 10142 /*软件版本 表示版本为 V1.01.42*/
/* ===== ENDU TEST BUILD (Rogue Max motor endurance test, NOT for mass production) =====
 * Based on V1.01.42 source (controlled release is 1.01.43). SoftwareVERSION is left at 10142 so the
 * official App / OTA logic sees the same number; the screen shows "-ENDU-TEST".
 * The phone ENDU test App talks to the boat with MAVLink sysid ENDU_APP_SYSID through this remote. */
#define ENDU_TEST_BUILD 1
#define ENDU_APP_SYSID  200   /* must equal boat param ET_APP_SYSID */
#define HardwareVERSION 10101 /*硬件版本 表示版本为 V1.01.01*/
#define DISPLAY_LANGUAGE SIMPLE_CHINESE

enum
{
	WiFi_Mode, // 蓝牙模式
	BLE_Mode,  // 蓝牙模式
};

enum
{
	CatchX_BS_LOG,	  // 主界面显示"CatchXBlackxxxx"
	CatchX_BS_CH_LOG, // 主界面显示"黑武士"
};

enum language
{
	SIMPLE_CHINESE,
	ENGLISH,
	RUSSIAN,
	LanguageMAX,
};

enum
{
	Speed_min,	  // 低速
	Speed_normal, // 正常速度
	Speed_max,	  // 高速
};

enum
{
	KEY_NOT,		  // 无功能
	KEY_SIGN,		  // 标记功能
	Cut_Boat_Speed,	  // 切换速度模式
	ElectronicAnchor, // 电子锚
	CruiseControl,	  // 定速巡航
	FixTheDeviation,  // 一键纠偏
	GhostModeEnable,  // 幽灵模式
};

enum
{
	FirmwareBad,	 // 固件摔坏
	FirmwareUnknown, // OTA升级后固件状态为未知
	FirmwareOK,		 // 成功启动固件后设置成OK
	FirmwareInit,	 // 烧录初始化为Init
};

enum
{
	AB_MODE,   // AB两个任务点
	ABCD_MODE, // ABCD四个任务点
};

/*保存参数结构*/
#pragma pack(1)
typedef struct
{
	uint8_t FirmwareStatus; /*固件是否有效*/
	uint32_t OTA_FileSize;	/*OTA升级文件大小*/
	uint32_t OTA_FileCRC;	/*OTA升级文件的CRC*/
} ota_data_t;

typedef struct
{
	enum language language;	 /*显示语言*/
	uint16_t ParameterSize;	 /*参数大小*/
	uint8_t PopUpFlag;		 /*是否全屏弹框*/
	uint8_t ShortKeyCustom;	 /*短按自定义按键功能选择*/
	uint8_t DoubleKeyCustom; /*双击自定义按键功能选择*/
	uint8_t LongKeyCustom;	 /*长按自定义按键功能选择*/
	uint8_t SavePointAB;	 /*是否保存AB点*/
	uint8_t BoatAnchorEn;	 /*到点是否锚定*/
	uint8_t BoatSpeed;		 /*船控的速度设定*/
	joystickParam_t jsParam; /*摇杆校准参数*/
	S_Position PositionA;	 /*A点经纬度*/
	S_Position PositionB;	 /*B点经纬度*/
	S_Position PositionC;	 /*C点经纬度*/
	S_Position PositionD;	 /*D点经纬度*/
	S_Position PositionH;	 /*Home点经纬度*/
	uint8_t AB_Mode;		 /*AB/ABCD选择*/
	uint32_t RF_ID;			 /*配对ID*/
	uint8_t AutoCruiseEn;	 /*自动定速巡航*/
	uint8_t BoatVersion;	 /*船的型号*/
	uint8_t JoystickChoose;	 /*摇杆控制选择*/
} configParam_t;
#pragma pack()

extern configParam_t configParam;
extern ota_data_t ota_data;

void configParamInit(void);
void configParamTask(void *param);
void NeedSave_User_Data(void);
void WriteUserConfigParamEeprom(void);
void WriteOTAConfigParamEeprom(void);
void UserConfigParamReset(void);

#endif
