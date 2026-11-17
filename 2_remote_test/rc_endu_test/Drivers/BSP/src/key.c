#include "key.h"
#include "main.h"

S_Key globe_key;
TaskHandle_t KEYTask_Handler;

uint8_t power_state = power_off;

#if KEY_DEBUG
const char Key_Name[key_name_num][20] = {
	"Key_TaskA",
	"Key_Cab",
	"Key_TaskB",
	"Key_Cruise",
	"Key_OK",
	"Key_Opt",
	"Key_Power",
	"Key_Sign",
	"Key_TaskAB",
};
#endif

const S_KeyIOPin Key_IOPin[] = {
	{
		.GPIOx = GPIOC,
		.GPIO_Pinx = GPIO_PIN_12,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE_DIS,
		.NeedMorePress = 1,
		.Key_name = Key_TaskA,
	},
	{
		.GPIOx = GPIOB,
		.GPIO_Pinx = GPIO_PIN_3,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE,
		.NeedMorePress = 0,
		.Key_name = Key_Cab,
	},
	{
		.GPIOx = GPIOB,
		.GPIO_Pinx = GPIO_PIN_5,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE_DIS,
		.NeedMorePress = 1,
		.Key_name = Key_TaskB,
	},
	{
		.GPIOx = GPIOC,
		.GPIO_Pinx = GPIO_PIN_13,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE,
		.NeedMorePress = 0,
		.Key_name = Key_Cruise,
	},
	{
		.GPIOx = GPIOB,
		.GPIO_Pinx = GPIO_PIN_9,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE_DIS,
		.NeedMorePress = 0,
		.Key_name = Key_OK,
	},
	{
		.GPIOx = GPIOA,
		.GPIO_Pinx = GPIO_PIN_0,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE_DIS,
		.NeedMorePress = 0,
		.Key_name = Key_Opt,
	},
	{
		.GPIOx = GPIOC,
		.GPIO_Pinx = GPIO_PIN_14,
		.KeyUpLevel = 0,
		.NeedDoubShort = KEY_DOUBLE,
		.NeedMorePress = 0,
		.Key_name = Key_Power,
	},
	{
		.GPIOx = GPIOC,
		.GPIO_Pinx = GPIO_PIN_1,
		.KeyUpLevel = 1,
		.NeedDoubShort = KEY_DOUBLE,
		.NeedMorePress = 0,
		.Key_name = Key_Sign,
	},
};

#define KEY_NUM (sizeof(Key_IOPin) / sizeof(Key_IOPin[0]))

S_KeyState Key_State[KEY_NUM];

uint8_t get_key_more_perss(uint8_t i, uint8_t j)
{
	if ((i == Key_TaskA && j == Key_TaskB) || (i == Key_TaskB && j == Key_TaskA))
	{
		return Key_TaskAB;
	}
	return key_name_num;
}

uint32_t Get_GPIO_RCC(GPIO_T *GPIOx)
{
	/* Enable the GPIO Clock */
	if (GPIOx == GPIOA)
	{
		return RCM_AHB1_PERIPH_GPIOA;
	}
	else if (GPIOx == GPIOB)
	{
		return RCM_AHB1_PERIPH_GPIOB;
	}
	else if (GPIOx == GPIOC)
	{
		return RCM_AHB1_PERIPH_GPIOC;
	}
	else if (GPIOx == GPIOD)
	{
		return RCM_AHB1_PERIPH_GPIOD;
	}
	else if (GPIOx == GPIOE)
	{
		return RCM_AHB1_PERIPH_GPIOE;
	}
	else if (GPIOx == GPIOF)
	{
		return RCM_AHB1_PERIPH_GPIOF;
	}
	else if (GPIOx == GPIOG)
	{
		return RCM_AHB1_PERIPH_GPIOG;
	}
	Debug("Get_GPIO_RCC Err: file name:%s line: %d\r\n", __FILE__, __LINE__);
	return RCM_AHB1_PERIPH_GPIOA;
}

void KeyInit(void)
{
	uint8_t i;

#if 1
	GPIO_Config_T GPIO_InitStructure;
	GPIO_ConfigStructInit(&GPIO_InitStructure);

	// GPIO_InitStructure.pin = LEDx_Pin;
	GPIO_InitStructure.mode = GPIO_MODE_IN;
	GPIO_InitStructure.speed = GPIO_SPEED_100MHz;
	GPIO_InitStructure.otype = GPIO_OTYPE_PP;
#endif

	globe_key.Key_Type = key_name_num;
	globe_key.Key_Value = key_invalid;
	globe_key.key_Down_Cnt = 0;
	memset(Key_State, 0, sizeof(Key_State));

	for (i = 0; i < sizeof(Key_IOPin) / sizeof(Key_IOPin[0]); ++i)
	{
		Key_State[i].IO_Pin = Key_IOPin[i];
		Key_State[i].key_long_delay = KEY_LONG_DELAY;
		Key_State[i].key_valid = key_invalid;
#if 1
		RCM_EnableAHB1PeriphClock(Get_GPIO_RCC(Key_State[i].IO_Pin.GPIOx));
		GPIO_InitStructure.pin = Key_State[i].IO_Pin.GPIO_Pinx;

		if (Key_State[i].IO_Pin.KeyUpLevel == 1)
		{
			GPIO_InitStructure.pupd = GPIO_PUPD_UP;
		}
		else
		{
			GPIO_InitStructure.pupd = GPIO_PUPD_DOWN;
		}
		GPIO_Config(Key_State[i].IO_Pin.GPIOx, &GPIO_InitStructure);
#endif
	}
}

void KeyIntInit(void)
{
	uint8_t i;

	memset(Key_State, 0, sizeof(Key_State));

	for (i = 0; i < sizeof(Key_IOPin) / sizeof(Key_IOPin[0]); ++i)
	{
		Key_State[i].IO_Pin = Key_IOPin[i];
		Key_State[i].key_long_delay = KEY_LONG_DELAY;
		Key_State[i].key_valid = key_invalid;

		if (Key_State[i].IO_Pin.KeyUpLevel == 1)
		{
			GPIO_INT_Enable(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx, EINT_TRIGGER_FALLING, ENABLE);
		}
		else
		{
			GPIO_INT_Enable(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx, EINT_TRIGGER_RISING, ENABLE);
		}
	}

	NVIC_EnableIRQRequest(EINT0_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT1_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT2_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT3_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT4_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT9_5_IRQn, 15, 0x00);
	NVIC_EnableIRQRequest(EINT15_10_IRQn, 15, 0x00);
}

#if KEY_DEBUG
void key_print(S_Key *Key)
{
	if (Key->Key_Type == key_name_num)
	{
		return;
	}
	if (Key->Key_Type < key_name_num)
	{
		Debug("%s ", Key_Name[Key->Key_Type]);
	}
	else
	{
		return;
	}
	switch (Key->Key_Value)
	{
	case short_pass:
		Debug("short_press\r\n");
		break;
	case short_release:
		Debug("short_release\r\n");
		break;
	case long_pass:
		Debug("long_pass\r\n");
		break;
	case long_release:
		Debug("long_release\r\n");
		break;
	case double_pass:
		Debug("double_pass\r\n");
		break;
	case double_release:
		Debug("double_release\r\n");
		break;
	case more_release:
		Debug("more_release cnt: %d\r\n", Key->key_Down_Cnt);
		break;
	case more_long_pass:
		Debug("more_long_pass cnt: %d\r\n", Key->key_Down_Cnt);
		break;
	default:
		break;
	}
}
#endif

uint8_t getkey_stat(uint8_t key_name)
{
	uint8_t i;

	for (i = 0; i < KEY_NUM; ++i)
	{
		if (Key_State[i].IO_Pin.Key_name == key_name)
		{
			return (Key_Pin_Read_Input(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx) ^ Key_State[i].IO_Pin.KeyUpLevel) & 1;
		}
	}
	return 0;
}

#if KEY_INT_EN
void key_update(uint8_t *key_all_sta)
#else
void key_update(void)
#endif
{
#if KEY_INT_EN
	static uint8_t key_all_is_up = 0;
#endif
	uint8_t i, j;

	for (i = 0; i < KEY_NUM; ++i)
	{
		if ((Key_Pin_Read_Input(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx) ^ Key_State[i].IO_Pin.KeyUpLevel) & 1)
		{
			if (0 == Key_State[i].key_stat)
			{
				if (KeyTimeGet())
				{
					Key_State[i].TickCntShort = KeyTimeGet();
				}
				else
				{
					Key_State[i].TickCntShort = 1;
				}
				Key_State[i].key_stat = 1; // key down
			}
		}
		else if (Key_State[i].key_stat)
		{
			// 这里TickCntLong不为0表示按键成功消抖, 按键有效 -- 这里只要按下时间小于key_long_delay都认为是短按
			if (Key_State[i].TickCntLong && GetTimeInterval(Key_State[i].TickCntLong, KeyTimeGet()) < Key_State[i].key_long_delay)
			{
				if (!Key_State[i].IO_Pin.NeedDoubShort)
				{
					Key_State[i].TickCntLong = 0;
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					globe_key.Key_Value = short_release; // 短按释放
					key_print(&globe_key);
				}
				else if (Key_State[i].TickCntDoubShort == 0)
				{
					Key_State[i].TickCntDoubShort = KeyTimeGet();
				}
			}
			else if (Key_State[i].key_valid == long_pass)
			{
				globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
				globe_key.Key_Value = long_release; // 长按释放
				key_print(&globe_key);
			}
			Key_State[i].key_stat = 0;			  // key up
			Key_State[i].key_valid = key_invalid; // key_invalid
		}
		else if (Key_State[i].TickCntDoubShort) // 等待双击
		{
			if (Key_State[i].IO_Pin.NeedDoubShort == 1)
			{
				if (Key_State[i].key_Down_Cnt)
				{
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					globe_key.Key_Value = double_release;
					Key_State[i].key_Down_Cnt = 0;
					Key_State[i].TickCntDoubShort = 0;
					Key_State[i].TickCntLong = 0;
					key_print(&globe_key);
				}
				else if (GetTimeInterval(Key_State[i].TickCntDoubShort, KeyTimeGet()) >= KEY_Double_DELAY)
				{
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					globe_key.Key_Value = short_release;
					Key_State[i].TickCntDoubShort = 0;
					Key_State[i].TickCntLong = 0;
					key_print(&globe_key);
				}
			}
			else
			{
				if (GetTimeInterval(Key_State[i].TickCntDoubShort, KeyTimeGet()) >= KEY_Double_DELAY)
				{
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					if (globe_key.Key_Value == more_cnt)
					{
						globe_key.Key_Value = more_release;
						globe_key.key_Down_Cnt = Key_State[i].key_Down_Cnt + 1;
						Key_State[i].key_Down_Cnt = 0;
					}
					else
					{
						globe_key.Key_Value = short_release;
					}
					Key_State[i].TickCntDoubShort = 0;
					Key_State[i].TickCntLong = 0;
					key_print(&globe_key);
				}
			}
		}
#if KEY_INT_EN
		else
		{
			key_all_is_up++;
		}
#endif
	}

	for (i = 0; i < KEY_NUM; ++i)
	{
		if (Key_State[i].TickCntShort && GetTimeInterval(Key_State[i].TickCntShort, KeyTimeGet()) > KEY_DELAY) // 按键消抖
		{
			Key_State[i].TickCntShort = 0;

			if ((Key_Pin_Read_Input(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx) ^ Key_State[i].IO_Pin.KeyUpLevel) & 1)
			{
				globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
				globe_key.Key_Value = short_pass; // 短按按下

				// if (globe_key.Key_Type == Key_OK && power_state == power_on)
				// {
				// 	LED_OK_Pin = LED_ON;
				// }

				Key_State[i].key_valid = short_pass;
				Key_State[i].TickCntLong = KeyTimeGet();

				if (Key_State[i].IO_Pin.NeedDoubShort) // 如果需要双击
				{
					if (Key_State[i].TickCntDoubShort && GetTimeInterval(Key_State[i].TickCntDoubShort, KeyTimeGet()) < KEY_Double_DELAY) // 判断是否是双击
					{
						// Key_State[i].TickCntDoubShort = KeyTimeGet(); // 立即更新双击判别时基
						Key_State[i].TickCntDoubShort = 0; // 弹起后重新更新双击判别时基
						globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
						globe_key.Key_Value = more_cnt;
						Key_State[i].key_Down_Cnt++;
					}
				}
			}
		}
		else if (Key_State[i].TickCntLong && GetTimeInterval(Key_State[i].TickCntLong, KeyTimeGet()) >= Key_State[i].key_long_delay)
		{
			Key_State[i].TickCntLong = 0;

			if ((Key_Pin_Read_Input(Key_State[i].IO_Pin.GPIOx, Key_State[i].IO_Pin.GPIO_Pinx) ^ Key_State[i].IO_Pin.KeyUpLevel) & 1)
			{
				if (Key_State[i].key_valid == short_pass)
				{
					Key_State[i].key_valid = long_pass; // 改按键已经长按
				}

				if (Key_State[i].key_Down_Cnt)
				{
					Key_State[i].TickCntDoubShort = 0;
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					globe_key.Key_Value = more_long_pass;
					globe_key.key_Down_Cnt = Key_State[i].key_Down_Cnt + 1;
					Key_State[i].key_Down_Cnt = 0;
				}
				else if (Key_State[i].IO_Pin.NeedMorePress)
				{
					for (j = 0; j < KEY_NUM; j++)
					{
						if (Key_State[j].IO_Pin.NeedMorePress && Key_State[j].key_valid == short_pass && j != i) // 说明这里已经有另外一个按键成功按下了,	j != i 排除自己
						{
							globe_key.Key_Type = get_key_more_perss(i, j);
							globe_key.Key_Value = long_pass;

							if (globe_key.Key_Type != key_name_num)
							{
								Key_State[i].key_valid = key_invalid;
								Key_State[j].key_valid = key_invalid;
								key_print(&globe_key);
								break;
							}
						}
					}

					// 这里判断key_valid == long_pass是为了两个按键一起按下触发后，剩下一个按键又触发长按了
					if (j == KEY_NUM && Key_State[i].key_valid == long_pass)
					{
						globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
						globe_key.Key_Value = long_pass;
						key_print(&globe_key);
					}
				}
				else if (Key_State[i].key_valid == long_pass)
				{
					globe_key.Key_Type = Key_State[i].IO_Pin.Key_name;
					globe_key.Key_Value = long_pass;
					key_print(&globe_key);
				}
			}
		}
	}
#if KEY_INT_EN
	if (key_all_is_up == KEY_NUM)
	{
		*key_all_sta = 1;
		// Debug("key all up\r\n");
	}
	else
	{
		*key_all_sta = 0;
	}
	key_all_is_up = 0;
#endif
	keyFun();
}

uint8_t keyIsValue(uint8_t Key_Type, uint8_t Key_Value)
{
	uint8_t more_down_cnt = 1;

	if (getKeyState().Key_Type == Key_Type && getKeyState().Key_Value == Key_Value)
	{
		if (getKeyState().Key_Value == more_release)
		{
			more_down_cnt = getKeyState().key_Down_Cnt;
		}
		getKeyState().Key_Type = key_name_num;
		getKeyState().Key_Value = key_invalid;
		getKeyState().key_Down_Cnt = 0;
		return more_down_cnt;
	}
	else
	{
		return 0;
	}
}

void KeyInvalid(void)
{
	getKeyState().Key_Type = key_name_num;
	getKeyState().Key_Value = key_invalid;
	getKeyState().key_Down_Cnt = 0;
}

void keyFun(void)
{
	if (keyIsValue(Key_Power, long_pass))
	{
		if (power_state == power_on)
		{
			Debug("PowerOFF_Hint\n");
			PowerOFF_Hint();
		}
		else
		{
			// PowerON_Hint();
			NVIC_SystemReset();
		}
	}
}

void LongKeyPowerON(void)
{
	uint8_t i = 0;
	uint8_t j = 0;

	IWDG_Feed();

	if (RCM_ReadStatusFlag(RCM_FLAG_SWRST) || RCM_ReadStatusFlag(RCM_FLAG_IWDTRST)) // WDT Reset || NVIC_SystemReset || RCM_FLAG_PINRST
	{
		power_state = power_ready;
		Power_Lock(); // 开机
	}
	else if (!S_CHG)
	{
		power_state = power_off;
		Power_Unlock(); // 关机
		show_ui = CHARGE_UI;
		globeState.chargeStat = is_charging;
		ChargeFullSpeed_EN;
	}
	else if (getkey_stat(Key_Power)) // 这里是长按开机键开机
	{
		Debug("Key_Power\n");

		delay_ms(20); // 消抖

		if (getkey_stat(Key_Power))
		{
			for (i = 0; i < 75; ++i)
			{
				if (!getkey_stat(Key_Power))
				{
					break;
				}

				if (getkey_stat(Key_OK))
				{
					j++;
				}

				IWDG_Feed();
				delay_ms(20);
				IWDG_Feed();
			}
			if (i == 75)
			{
				power_state = power_ready;
				Power_Lock(); // 开机

				if (j == 75) // 进入工厂设置模式
				{
				}
			}
			else
			{
				Debug("Power OFF\r\n");
				Power_Unlock(); // 关机
				for (;;)
				{
				}
			}
		}
	}
	else if (power_state != power_ready)
	{
		Debug("Power OFF\r\n");
		Power_Unlock(); // 关机
		for (;;)
		{
		}
	}

	RCM_ClearStatusFlag();
}

void PowerON_Hint(void)
{
	LED_Power_Pin = LED_ON;
	Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 100, 100, 0, 0, 2);

	vTaskResume(ParseBoatMavTaskHandle);
	vTaskResume(JoystickSendHandle);
	vTaskResume(ParseAppMavTaskHandle);

	power_state = power_on;
	Power_Lock();
	RF_Power_EN;
	Debug("Power ON\n");
}

void PowerOFF_Hint(void)
{
	Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, 500, 0, 0, 0, 1);
	if (flash_need_update)
	{
		flash_need_update = 0;
		WriteUserConfigParamEeprom();
	}
	LED_Power_Pin = LED_OFF;
	if (globeState.chargeStat == not_charging)
	{
		while (TimeControl[Vibr_Motor_ID].CNT)
		{
			delay_ms(30);
		}
		LCD_Backlight = 0;
		for (;;)
		{
			delay_ms(30);
			if (!getkey_stat(Key_Power))
			{
				Debug("Power OFF\n");
				Power_Unlock();
			}
		}
	}
	Debug("-------------\n");
	power_state = power_off;
	RF_Power_DIS;
	ChargeFullSpeed_EN;

	vTaskSuspend(ParseBoatMavTaskHandle);
	vTaskSuspend(JoystickSendHandle);
	vTaskSuspend(ParseAppMavTaskHandle);

	LED_Cruise_Pin = LED_OFF;
	LED_TaskA_Pin = LED_OFF;
	LED_TaskB_Pin = LED_OFF;
	memset((void *)&globeState, 0, sizeof(GLOBE_STATE));

	globeState.Cut_Show_UI = CHARGE_UI;
}

// key任务函数
void key_task(void *pvParameters)
{
	delay_ms(100); // 先自锁稳定，在开WiFi供电

	if (power_state == power_ready)
	{
		PowerON_Hint();
	}

	while (getkey_stat(Key_Power))
	{
		delay_ms(10);
		IWDG_Feed();
	}

	rf_uart3_init(1500000);
	wifi_uart4_init(115200);

#if KEY_INT_EN
	uint8_t key_all_state; // 按键全部弹起标志
	for (;;)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		for (;;)
		{
			key_update(&key_all_state);
			if (key_all_state)
			{
				break;
			}
			delay_ms(10);
		}
	}
#else
	for (;;)
	{
		key_update();
		delay_ms(10);
	}
#endif
}
