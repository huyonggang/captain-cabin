#ifndef __JOYSTICK_H
#define __JOYSTICK_H
#include "sys.h"
#include <stdbool.h>

#define MAX(a, b) a >= b ? a : b
#define MIN(a, b) a <= b ? a : b

// 获取摇杆方向时定义在中间的范围值（ADC值）
#define DIR_MID_THRUST 1000
#define DIR_MID_YAW 1000
#define DIR_MID_PITCH 1000
#define DIR_MID_ROLL 1000

enum dir_e
{
	CENTER,
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
	BACK_LEFT,
	BACK_RIGHT,
};

// 摇杆单方向量程参数
struct range_s
{
	s16 range_pos; // 摇杆正量程
	u16 mid;
	s16 range_neg; // 摇杆负量程
};

// 摇杆量程参数
typedef struct
{
	struct range_s roll;
	struct range_s pitch;
#if 0
	struct range_s thrust;
	struct range_s yaw;
#endif
} joystickParam_t;

// 飞控数据结构
typedef struct
{
	float roll;
	float pitch;
	float yaw;
	float thrust;
} joystickFlyf_t;

// 飞控数据结构
typedef struct
{
	u16 roll;
	u16 pitch;
	u16 yaw;
	u16 thrust;
} joystickFlyui16_t;

void joystickInit(void);

void getFlyDataADCValue(joystickFlyui16_t *adcValue);

void ADCtoFlyDataPercent(joystickFlyf_t *flyDataPercent);

void joystcikParamSet(joystickParam_t set);

enum dir_e getJoystick1Dir(u8 mode);

enum dir_e getJoystick2Dir(u8 mode);

#endif /*__JOYSTICK_H*/
