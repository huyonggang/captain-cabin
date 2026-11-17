#include "config_param.h"
#include "apm32flash.h"
#include "joystick.h"
#include "key.h"
// #include "display.h"
#include "led.h"
#include "main.h"
#include "my_mavlink.h"
#include "main_ui.h"
#include "bsp_i2c_eeprom_24xx.h"

/* FreeRtos includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

configParam_t configParam; /*配置参数全局变量*/
ota_data_t ota_data;

configParam_t configParamDefault = {
	.language = DISPLAY_LANGUAGE,
	.ParameterSize = sizeof(configParam_t),
	.BoatSpeed = Speed_max,
	.ShortKeyCustom = FixTheDeviation,
	.DoubleKeyCustom = Cut_Boat_Speed,
	.LongKeyCustom = ElectronicAnchor,
	.SavePointAB = ENABLE,
	.PopUpFlag = 1,
	.BoatAnchorEn = ENABLE,
	.AutoCruiseEn = 6,
	.BoatVersion = Init,
	.AB_Mode = ABCD_MODE,

	.PositionA.degE7_lat = 0,
	.PositionA.degE7_long = 0,
	.PositionA.alt_mm = 0,
	.PositionB.degE7_lat = 0,
	.PositionB.degE7_long = 0,
	.PositionB.alt_mm = 0,
	.PositionC.degE7_lat = 0,
	.PositionC.degE7_long = 0,
	.PositionC.alt_mm = 0,
	.PositionD.degE7_lat = 0,
	.PositionD.degE7_long = 0,
	.PositionD.alt_mm = 0,

	.jsParam.pitch.mid = 2000,
	.jsParam.pitch.range_neg = 2000,
	.jsParam.pitch.range_pos = 2000,
	.jsParam.roll.mid = 2000,
	.jsParam.roll.range_neg = 2000,
	.jsParam.roll.range_pos = 2000,
#if 0
	.jsParam.yaw.mid = 2000,
	.jsParam.yaw.range_neg = 2000,
	.jsParam.yaw.range_pos = 2000,
	.jsParam.thrust.mid = 2000,
	.jsParam.thrust.range_neg = 2000,
	.jsParam.thrust.range_pos = 2000,
#endif
};

static const ota_data_t ota_data_default = {
	.FirmwareStatus = FirmwareOK,
	.OTA_FileSize = 0,
	.OTA_FileCRC = 0xFFFFFFFF,
};

/*配置参数初始化*/
void configParamInit(void)
{
	uint8_t app_first_flag = 0;
	uint8_t value = 0;

	bsp_InitI2C();
	if (i2c_CheckDevice(EE_DEV_ADDR) != 0)
	{
		log_error("EEPROM error");
	}

	/* 读取配置参数 */
	ee_ReadBytes((uint8_t *)&configParam, CONFIG_PARAM_ADDR, sizeof(configParam));
	ee_ReadBytes((uint8_t *)&ota_data, OTA_DATA_ADD, sizeof(ota_data));
	ee_ReadBytes((uint8_t *)&app_first_flag, APP_FIRST_ADDR, sizeof(app_first_flag));
	if (app_first_flag != APP_FIRST_FLAG) // 说明是第一次运行
	{
		app_first_flag = APP_FIRST_FLAG;
		ee_WriteBytes((uint8_t *)&app_first_flag, APP_FIRST_ADDR, sizeof(app_first_flag));
		value = CatchX_BS_CH_LOG;
		ee_WriteBytes((uint8_t *)&value, LOG_ADDR, sizeof(value));
		value = 2; // (1：国内   2：国外)
		ee_WriteBytes((uint8_t *)&value, AT_HOME_AND_ABROAD_ADDR, sizeof(value));
		configParam = configParamDefault;
		WriteUserConfigParamEeprom();
		log_info("---> The first run of the app");
	}
	if (ota_data.FirmwareStatus != FirmwareOK)
	{
		ota_data.FirmwareStatus = FirmwareOK;
		ota_data.OTA_FileSize = 0;
		WriteOTAConfigParamEeprom();
		power_state = power_ready;
		Power_Lock(); // 开机
		log_info("OTA upgrade success, Firmware CRC: %08X", ota_data.OTA_FileCRC);
	}

	if (sizeof(configParam_t) > configParam.ParameterSize) // 这里新增了参数，拷贝默认值
	{
		memcpy(&((uint8_t *)&configParam)[configParam.ParameterSize],
			   &((uint8_t *)&configParamDefault)[configParam.ParameterSize],
			   sizeof(configParam_t) - configParam.ParameterSize);
		WriteUserConfigParamEeprom();
		log_info("---> Save new parameters");
	}

	if (configParam.language > 1)
	{
		configParam.language = SIMPLE_CHINESE;
	}

	memset((void *)&globeState, 0, sizeof(GLOBE_STATE));
	globeState.TaskAppSta = TaskClear;
	globeState.show_main = ShowMainLogo;
	globeState.NowTask.TaskType = TaskClear;
	globeState.Recover_Task.TaskType = TaskClear;
	globeState.TaskPresetFlag = 0;
	globeState.Cut_Show_UI = MAX_SHOW_UI;
	ee_ReadBytes((uint8_t *)&globeState.Log, LOG_ADDR, sizeof(globeState.Log));
	ee_ReadBytes((uint8_t *)&globeState.AtHomeAndAbroad, AT_HOME_AND_ABROAD_ADDR, sizeof(globeState.AtHomeAndAbroad));
	if (globeState.Log > 1)
	{
		globeState.Log = CatchX_BS_CH_LOG;
		ee_WriteBytes((uint8_t *)&globeState.Log, LOG_ADDR, sizeof(globeState.Log));
	}
	if (globeState.AtHomeAndAbroad > 2)
	{
		globeState.AtHomeAndAbroad = 2;
		ee_WriteBytes((uint8_t *)&globeState.AtHomeAndAbroad, AT_HOME_AND_ABROAD_ADDR, sizeof(globeState.AtHomeAndAbroad));
	}
	if (configParam.SavePointAB)
	{
		globeState.Task_Sta.PositionA = configParam.PositionA;
		if (globeState.Task_Sta.PositionA.degE7_lat && globeState.Task_Sta.PositionA.degE7_long)
		{
			Debug("degE7_lat A: %d", globeState.Task_Sta.PositionA.degE7_lat);
			Debug("degE7_long A: %d", globeState.Task_Sta.PositionA.degE7_long);
			Debug("alt_mm A: %d", globeState.Task_Sta.PositionA.alt_mm);
		}

		globeState.Task_Sta.PositionB = configParam.PositionB;
		if (globeState.Task_Sta.PositionB.degE7_lat && globeState.Task_Sta.PositionB.degE7_long)
		{
			Debug("degE7_lat B: %d", globeState.Task_Sta.PositionB.degE7_lat);
			Debug("degE7_long B: %d", globeState.Task_Sta.PositionB.degE7_long);
			Debug("alt_mm B: %d", globeState.Task_Sta.PositionB.alt_mm);
		}

		globeState.Task_Sta.PositionC = configParam.PositionC;
		if (globeState.Task_Sta.PositionC.degE7_lat && globeState.Task_Sta.PositionC.degE7_long)
		{
			Debug("degE7_lat C: %d", globeState.Task_Sta.PositionC.degE7_lat);
			Debug("degE7_long C: %d", globeState.Task_Sta.PositionC.degE7_long);
			Debug("alt_mm C: %d", globeState.Task_Sta.PositionC.alt_mm);
		}

		globeState.Task_Sta.PositionD = configParam.PositionD;
		if (globeState.Task_Sta.PositionD.degE7_lat && globeState.Task_Sta.PositionD.degE7_long)
		{
			Debug("degE7_lat D: %d", globeState.Task_Sta.PositionD.degE7_lat);
			Debug("degE7_long D: %d", globeState.Task_Sta.PositionD.degE7_long);
			Debug("alt_mm D: %d", globeState.Task_Sta.PositionD.alt_mm);
		}
	}
	globeState.home_position = configParam.PositionH;
	globeState.BoatVersion = configParam.BoatVersion;
}

void NeedSave_User_Data(void)
{
	flash_need_update = 1;
}

/*保存配置参数*/
void WriteUserConfigParamEeprom(void)
{
	flash_need_update = 0;
	// Save_User_Data();
	ee_WriteBytes((uint8_t *)&configParam, CONFIG_PARAM_ADDR, sizeof(configParam));
}

/*配置参数复位为默认(摇杆校准参数不恢复)*/
void UserConfigParamReset(void)
{
	joystickParam_t jsParam;
	uint32_t RF_ID;
	enum language language;

	jsParam = configParam.jsParam;
	RF_ID = configParam.RF_ID;
	language = configParam.language;

	configParam = configParamDefault;

	configParam.jsParam = jsParam;
	configParam.RF_ID = RF_ID;
	configParam.language = language;

	WriteUserConfigParamEeprom();
}

/*保存OTA配置参数*/
void WriteOTAConfigParamEeprom(void)
{
	ee_WriteBytes((uint8_t *)&ota_data, OTA_DATA_ADD, sizeof(ota_data));
}

/*OTA配置参数复位为默认*/
void OTAConfigParamReset(void)
{
	ota_data = ota_data_default;
	WriteOTAConfigParamEeprom();
}
