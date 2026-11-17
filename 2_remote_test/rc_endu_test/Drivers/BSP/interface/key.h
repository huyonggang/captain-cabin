#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "limits.h"
#include "portmacro.h"
#include "semphr.h"

enum
{
	power_off,
	power_on,
	power_ready,
};

#define Power_Lock_Port GPIOA
#define Power_Lock_Pin GPIO_PIN_12
#define Power_Lock() PAout(12) = 1
#define Power_Unlock() PAout(12) = 0

#define KEY_DEBUG 1
#define KEY_INT_EN 1 // 按键是否使用中断
#define DoubleLong 1 // 两个按键同时长按

#define KEY_DOUBLE_DIS 0 // 关闭双击模式
#define KEY_DOUBLE 1	 // 双击模式
#define KEY_MORE_DOWN 2	 // 多击模式

#define KEY_DELAY 20
#define KEY_LONG_DELAY 1500
#define KEY_Double_DELAY 200

#define getKeyState() globe_key
#define KeyTimeGet() GetSysTick()

#define Key_Pin_Read_Input(GPIOx, Pinx) GPIO_ReadInputBit(GPIOx, Pinx)

enum
{
	Key_TaskA,
	Key_Cab,
	Key_TaskB,
	Key_Cruise,
	Key_OK,
	Key_Opt,
	Key_Power,
	Key_Sign,
	Key_TaskAB,
	key_name_num
};

enum
{
	short_pass,		  // 短按
	double_pass,	  // 双击
	long_pass,		  // 双击后长按
	double_long_pass, // 双击后长按
	more_long_pass,	  // 多击后长按
	short_release,	  // 短按释放
	long_release,	  // 长按释放
	more_release,	  // 多击完成
	double_release,	  // 双击释放
	more_cnt,		  // 处于多击计数中
	key_invalid,	  // 按键无效
};

typedef struct
{
	uint8_t Key_Type;	  // Specific keys
	uint8_t Key_Value;	  // Key behavior
	uint8_t key_Down_Cnt; // Key 记录短时间多次按下次数
} S_Key;

typedef struct
{
	GPIO_T *GPIOx;
	uint16_t GPIO_Pinx;
	uint8_t KeyUpLevel;	   // 按键弹起电平状态
	uint8_t NeedDoubShort; // 是否需要双击
	uint8_t NeedMorePress; // 是否需要两个按键同时按
	uint8_t Key_name;
} S_KeyIOPin;

typedef struct
{
	uint32_t TickCntShort;
	uint32_t TickCntDoubShort; // 用于双击或多击计时
	uint32_t TickCntLong;
	S_KeyIOPin IO_Pin;
	uint8_t key_valid;	  // 用于多个按键一起按标志
	uint8_t key_stat;	  // 按键是否按下状态
	uint8_t key_Down_Cnt; // Key 记录短时间多次按下次数
	uint16_t key_long_delay;
} S_KeyState;

extern S_Key globe_key;
extern TaskHandle_t KEYTask_Handler;
extern uint8_t power_state;

void KeyInit(void);
void KeyIntInit(void);
#if KEY_INT_EN
void key_update(uint8_t *key_all_sta);
#else
void key_update(void);
#endif
void keyFun(void);

#if KEY_DEBUG
void key_print(S_Key *Key);
#else
#define key_print(x)
#endif

void LongKeyPowerON(void);
void Power_Lock_Init(void);

void PowerON_Hint(void);
void PowerOFF_Hint(void);

uint8_t getkey_stat(uint8_t key_name);
uint8_t keyIsValue(uint8_t Key_Type, uint8_t Key_Value);
void KeyInvalid(void);
uint32_t Get_GPIO_RCC(GPIO_T *GPIOx);
void key_task(void *pvParameters);

#endif
