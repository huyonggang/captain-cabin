#include "led.h"
#include "main.h"

void My_Gpio_Init(void)
{
	S_MY_GPIO_Init MY_GPIO_Init[] = {
		{
			GPIOA,
			GPIO_PIN_11,
			GPIO_MODE_IN,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			NULL,
		}, // charge_in(1: 充电器插入)
		{
			GPIOC,
			GPIO_PIN_5,
			GPIO_MODE_IN,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			NULL,
		}, // charge_full(1: 电池充满)
		{
			GPIOA,
			GPIO_PIN_12,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // 电源自锁(1: ON 0: OFF)
		{
			GPIOA,
			GPIO_PIN_15,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_Task1
		{
			GPIOD,
			GPIO_PIN_2,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_Cab
		{
			GPIOB,
			GPIO_PIN_4,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_Task2
		{
			GPIOB,
			GPIO_PIN_7,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_Cruise
		{
			GPIOB,
			GPIO_PIN_6,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_OK
		{
			GPIOC,
			GPIO_PIN_6,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // LED_Power
		{
			RF_Pair_PORT,
			RF_Pair_PIN,
			GPIO_MODE_IN,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			NULL,
		}, // RF_Pair_Pin_Read
		{
			RF_Pair_EN_PORT,
			RF_Pair_EN_PIN,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // RF_Pair_EN_Pin_Set
		{
			RF_Power_EN_PORT,
			RF_Power_EN_PIN,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			0,
		}, // RF_Power_EN_Pin_Set
		{
			FP6296XR_EN_PORT,
			FP6296XR_EN_PIN,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		},
		{
			Motor_Port_EN_PORT,
			Motor_Port_EN_PIN,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			1,
		}, // 马达芯片使能
		{
			ChargeFullSpeed_PORT,
			ChargeFullSpeed_PIN,
			GPIO_MODE_OUT,
			GPIO_SPEED_100MHz,
			GPIO_OTYPE_PP,
			GPIO_PUPD_NOPULL,
			0,
		}, // 关机全速充电
	};

	/* 禁止JTA使能SWD口 */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	for (uint8_t i = 0; i < sizeof(MY_GPIO_Init) / sizeof(S_MY_GPIO_Init); i++)
	{
		RCM_EnableAHB1PeriphClock(Get_GPIO_RCC(MY_GPIO_Init[i].GPIOx));
		GPIO_Config(MY_GPIO_Init[i].GPIOx, &MY_GPIO_Init[i].GPIO_InitStructure);

		if (MY_GPIO_Init[i].GPIOx == RF_Power_EN_PORT && MY_GPIO_Init[i].GPIO_InitStructure.pin == RF_Power_EN_PIN)
		{
			if (!getkey_stat(Key_Power) && S_CHG) // 没有按下开机键，没有充电，直接给图传供电(系统重启或者OTA升级完成才会出现这个情况)
			{
				GPIO_SetBit(MY_GPIO_Init[i].GPIOx, MY_GPIO_Init[i].GPIO_InitStructure.pin);
			}
		}
		else
		{
			if (MY_GPIO_Init[i].GPIO_InitStructure.mode == GPIO_MODE_OUT)
			{
				if (MY_GPIO_Init[i].OutPutLevel)
				{
					GPIO_SetBit(MY_GPIO_Init[i].GPIOx, MY_GPIO_Init[i].GPIO_InitStructure.pin);
				}
				else
				{
					GPIO_ResetBit(MY_GPIO_Init[i].GPIOx, MY_GPIO_Init[i].GPIO_InitStructure.pin);
				}
			}
		}
	}

	// GPIO_INT_Enable(RF_Pair_PORT, RF_Pair_PIN, EINT_TRIGGER_RISING_FALLING, ENABLE);
}

void TFT_Backlight_PWM_Init(void)
{
	GPIO_Config_T GPIO_ConfigStruct;
	TMR_BaseConfig_T TMR_TimeBaseStruct;
	TMR_OCConfig_T OCcongigStruct;

	RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
	RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);

	/* TMR1_CH1 */
	GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_8, GPIO_AF_TMR1);

	/* Config TMR1 GPIO for complementary output PWM */
	GPIO_ConfigStruct.pin = GPIO_PIN_8;
	GPIO_ConfigStruct.mode = GPIO_MODE_AF;
	GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
	GPIO_ConfigStruct.speed = GPIO_SPEED_100MHz;
	GPIO_ConfigStruct.pupd = GPIO_PUPD_NOPULL;
	GPIO_Config(GPIOA, &GPIO_ConfigStruct);

	/* config TMR1 */
	TMR_TimeBaseStruct.clockDivision = TMR_CLOCK_DIV_1;
	TMR_TimeBaseStruct.countMode = TMR_COUNTER_MODE_UP;
	TMR_TimeBaseStruct.division = 174;
	TMR_TimeBaseStruct.period = 999;
	TMR_TimeBaseStruct.repetitionCounter = 0;
	TMR_ConfigTimeBase(TMR1, &TMR_TimeBaseStruct);

	/* Configure channel */
	OCcongigStruct.mode = TMR_OC_MODE_PWM1;
	OCcongigStruct.pulse = 0;
	OCcongigStruct.idleState = TMR_OC_IDLE_STATE_RESET;
	OCcongigStruct.outputState = TMR_OC_STATE_ENABLE;
	OCcongigStruct.polarity = TMR_OC_POLARITY_HIGH;
	OCcongigStruct.nIdleState = TMR_OC_NIDLE_STATE_RESET;
	OCcongigStruct.outputNState = TMR_OC_NSTATE_ENABLE;
	OCcongigStruct.nPolarity = TMR_OC_NPOLARITY_HIGH;

	TMR_ConfigOC1(TMR1, &OCcongigStruct);
	TMR_ConfigOC1Preload(TMR1, TMR_OC_PRELOAD_ENABLE);

	TMR_EnableAutoReload(TMR1);
	TMR_Enable(TMR1);
	/* Enable TMR1 PWM output */
	TMR_EnablePWMOutputs(TMR1);
}

void Motor_PWM_Set(uint8_t percent)
{
	if (percent)
	{
		TMR3->CC2 = percent * 2 + 500;
	}
	else
	{
		TMR3->CC2 = 0;
	}
}

void Motor_PWM_Init(void)
{
	GPIO_Config_T GPIO_ConfigStruct;
	TMR_BaseConfig_T TMR_TimeBaseStruct;
	TMR_OCConfig_T OCcongigStruct;

	RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
	RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC);

	GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_7, GPIO_AF_TMR3);

	/* Config PA7 and PA8 for complementary output PWM */
	GPIO_ConfigStruct.pin = GPIO_PIN_7;
	GPIO_ConfigStruct.mode = GPIO_MODE_AF;
	GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
	GPIO_ConfigStruct.speed = GPIO_SPEED_100MHz;
	GPIO_Config(GPIOC, &GPIO_ConfigStruct);

	/* config TMR3 */
	TMR_TimeBaseStruct.clockDivision = TMR_CLOCK_DIV_1;
	TMR_TimeBaseStruct.countMode = TMR_COUNTER_MODE_UP;
	TMR_TimeBaseStruct.division = 3;
	TMR_TimeBaseStruct.period = 999;
	TMR_ConfigTimeBase(TMR3, &TMR_TimeBaseStruct);

	OCcongigStruct.idleState = TMR_OC_IDLE_STATE_RESET;
	OCcongigStruct.mode = TMR_OC_MODE_PWM1;
	OCcongigStruct.nIdleState = TMR_OC_NIDLE_STATE_RESET;
	OCcongigStruct.nPolarity = TMR_OC_NPOLARITY_HIGH;
	OCcongigStruct.outputNState = TMR_OC_NSTATE_ENABLE;
	OCcongigStruct.outputState = TMR_OC_STATE_ENABLE;
	OCcongigStruct.polarity = TMR_OC_POLARITY_HIGH;
	OCcongigStruct.pulse = 0;
	TMR_ConfigOC2(TMR3, &OCcongigStruct);

	TMR_ConfigOC2Preload(TMR3, TMR_OC_PRELOAD_ENABLE);
	TMR_EnableAutoReload(TMR3);
	TMR_Enable(TMR3);
	TMR_EnablePWMOutputs(TMR3);
}

void Time_Control_Call_Back(uint16_t Call_ID, uint32_t Call_Value)
{
	if (Call_ID >= ALL_ID_NUM)
	{
		return;
	}

	switch (Call_ID)
	{
	case LED_Task1_ID:
	{
		LED_TaskA_Pin = Call_Value ? 0 : 1;
	}
	break;
	case LED_Cab_ID:
	{
		LED_Cab_Pin = Call_Value ? 0 : 1;
	}
	break;
	case LED_Task2_ID:
	{
		LED_TaskB_Pin = Call_Value ? 0 : 1;
	}
	break;
	case LED_Cruise_ID:
	{
		LED_Cruise_Pin = Call_Value ? 0 : 1;
	}
	break;
	case LED_OK_ID:
	{
		LED_OK_Pin = Call_Value ? 0 : 1;
	}
	break;
	case LED_Power_ID:
	{
		LED_Power_Pin = Call_Value ? 0 : 1;
	}
	break;
	case Vibr_Motor_ID:
	{
		Motor_PWM_Set(Call_Value);
	}
	break;
	default:
		break;
	}
}
