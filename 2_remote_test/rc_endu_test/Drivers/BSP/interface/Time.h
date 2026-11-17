#ifndef __ALARM_H__
#define __ALARM_H__

#include "sys.h"

#define Alarm_FIFO_EN // 使能 RGB FIFO 缓冲区

#define Time_Control_Set_Value(a, b, c, d, e, f, g, h) LED_Set_Control_Value(a, b, c, d, e, f, g, h, CanNotBreak, AddFifo)
#define Time_Control_Update Alarm_Control_Update
#define RGB_LED_Set_Color Time_Control_Call_Back

typedef enum
{
    Unlock,
    Lock
} DataLock;

typedef void (*FunType)(uint16_t, uint32_t);

typedef struct
{
    uint8_t state;
    uint8_t busy;
    uint16_t LED_ID;
    uint16_t ON_Time;
    uint16_t OFF_Time;
    uint16_t Hold_Time;
    uint16_t CNT;
    uint32_t Hold_Color;
    uint32_t LastTime;
    uint32_t ON_Color;
    uint32_t OFF_Color;
    FunType Fun;
} S_AlarmControl;

enum
{
    is_stop,         // 没有在工作
    CanNotBreak,     // 不能被打断
    without_recover, // 可以被打断，打断后也不需要恢复上一次执行的状态
    need_recover,    // 可以被打断，打断后需要恢复上一次执行的状态
};

typedef enum
{
    Other_Null,          // 如果当前在工作，且当前的状态可以被打断，那直接打断，若不能打断，直接添加到缓冲区
    BreakWithoutRecover, // 如果当前在工作，强行打断当前工作，并且不需要恢复被打断的状态
    BreakNeedRecover,    // 如果当前在工作，强行打断当前工作，需要恢复被打断的状态
    AddFifo,             // 如果当前在工作，直接添加到缓冲区(这个是为了不打断能被打断的状态)
} E_Other_Flag;

extern S_AlarmControl TimeControl[];

void Alarm_Data_Init(void);
void Alarm_Control_Update(void);
void LED_Set_Control_Value(uint8_t led_id, uint32_t ON_Color,
                           uint32_t OFF_Color, uint16_t ON_Time,
                           uint16_t OFF_Time, uint32_t Hold_Color,
                           uint16_t Hold_Time, uint16_t CNT,
                           uint8_t busy, uint8_t Other_Flag);
void Tone_Set_Control_Value(uint16_t Audio_Vol, uint32_t frequency, uint16_t ON_Time, uint16_t OFF_Time, uint16_t CNT);
void LED_Stop_Control_Value(uint8_t RGB_ID);
uint8_t RGB_Is_Extinguish(void);
uint8_t RGB_CanNotBreak_Is_Stop_Flicker(void);
uint8_t RGB_Is_Stop_Flicker(void);
uint8_t Audio_Is_Stop(void);

#ifdef Alarm_FIFO_EN

#define Alarm_FIFO_BUFF_SIZE 10 // RGB缓冲区大小

typedef struct
{
    uint8_t full;
    uint16_t length;
    uint16_t head;
    uint16_t tail;
    S_AlarmControl *buf;
} S_Alarm_FIFO; // 12Byte

extern S_AlarmControl AlarmControl[];

uint8_t RGB_Value_Compare(const S_AlarmControl *const AlarmControl, const S_AlarmControl *const Set_AlarmControl);
void Alarm_FIFO_Init(void);

#endif

#endif
