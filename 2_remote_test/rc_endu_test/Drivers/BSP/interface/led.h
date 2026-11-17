#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED_ON 0
#define LED_OFF 1

#define S_CHG PAin(11) // 低电平充电插入
#define U_CHG PCin(5)  // 高电平充满

#define LED_TaskA_Pin PAout(15)
#define LED_Cab_Pin PDout(2)
#define LED_TaskB_Pin PBout(4)
#define LED_Cruise_Pin PBout(7)
#define LED_OK_Pin PBout(6)
#define LED_Power_Pin PCout(6)

#define RF_Pair_PORT GPIOB
#define RF_Pair_PIN GPIO_PIN_15
#define RF_Pair_Pin_Read PBin(15)

#define RF_Pair_EN_PORT GPIOB
#define RF_Pair_EN_PIN GPIO_PIN_14
#define RF_Pair_EN_Pin_Set PBout(14)
#define RF_Pair_EN PBout(14) = 0 // 进入对频低电平
#define RF_Pair_DIS PBout(14) = 1

#define RF_Power_EN_PORT GPIOC // 数传供电使能
#define RF_Power_EN_PIN GPIO_PIN_9
#define RF_Power_EN_Pin_Set PCout(9)
#define RF_Power_EN PCout(9) = 1
#define RF_Power_DIS PCout(9) = 0

#define FP6296XR_EN_PORT GPIOB // 数传升压芯片使能(先使能数传供电, 1: 输出5V 0: 输出电池电压)
#define FP6296XR_EN_PIN GPIO_PIN_12
#define FP6296XR_EN_Pin_Set PBout(12)
#define FP6296XR_EN PBout(12) = 1
#define FP6296XR_DIS PBout(12) = 0

#define Motor_Port_EN_PORT GPIOC // 马达芯片使能
#define Motor_Port_EN_PIN GPIO_PIN_8
#define Motor_Port_EN_Pin_Set PCout(8)
#define Motor_Port_EN PCout(8) = 1
#define Motor_Port_DIS PCout(8) = 0

#define ChargeFullSpeed_PORT GPIOB // 关机全速充电
#define ChargeFullSpeed_PIN GPIO_PIN_12
#define ChargeFullSpeed_Pin_Set PBout(12)
#define ChargeFullSpeed_EN PBout(12) = 1
#define ChargeFullSpeed_DIS PBout(12) = 0

#define LCD_Backlight TMR1->CC1

enum
{
    LED_Task1_ID,
    LED_Cab_ID,
    LED_Task2_ID,
    LED_Cruise_ID,
    LED_OK_ID,
    LED_Power_ID,
};

enum
{
    LED_ID_NUM = LED_Power_ID,
    Vibr_Motor_ID,
    RF_Pair_ID,
    RF_Power_EN_ID,
    ALL_ID_NUM,
};

typedef enum
{
    not_charging,
    is_charging,
    charge_ok,
    delay_not_charging,
} ChargeState;

typedef struct
{
    GPIO_T *GPIOx;
    GPIO_Config_T GPIO_InitStructure;
    uint8_t OutPutLevel;
} S_MY_GPIO_Init;

void My_Gpio_Init(void);
void TFT_Backlight_PWM_Init(void);
void Motor_PWM_Init(void);
void Motor_PWM_Set(uint8_t percent);
void Time_Control_Call_Back(uint16_t Call_ID, uint32_t Call_Value);

#endif
