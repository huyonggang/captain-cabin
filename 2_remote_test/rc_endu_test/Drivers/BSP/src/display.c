#include "display.h"
#include "main.h"

enum ui_e show_ui = MAIN_UI;
enum ui_e last_show_ui = MAIN_UI;

TaskHandle_t LowPriorityTaskHandle;

float limit(float value, float min, float max)
{
	if (value > max)
	{
		value = max;
	}
	else if (value < min)
	{
		value = min;
	}
	return value;
}

uint8_t getRatio(uint8_t baseValue, uint8_t unit, float realVolt, float min, float max)
{
	float temp = (realVolt - min) / (max - min);
	return (uint8_t)(baseValue + unit * temp + 0.5f);
}

uint8_t getBatPercent(float volt)
{
	// char str[100];
	// sprintf(str, "volt: %2.3f", volt);
	// log_info("%s", str);
	if (volt >= 12.6f)
		return 100;
	else if (volt >= 12.435f)
		return 95;
	else if (volt >= 12.27f)
		return 90;
	else if (volt >= 12.105f)
		return 85;
	else if (volt >= 11.94f)
		return 80;
	else if (volt >= 11.775f)
		return 75;
	else if (volt >= 11.61f)
		return 70;
	else if (volt >= 11.445f)
		return 65;
	else if (volt >= 11.28f)
		return 60;
	else if (volt >= 11.115f)
		return 55;
	else if (volt >= 10.95f)
		return 50;
	else if (volt >= 10.785f)
		return 45;
	else if (volt >= 10.62f)
		return 40;
	else if (volt >= 10.455f)
		return 35;
	else if (volt >= 10.29f)
		return 30;
	else if (volt >= 10.2f)
		return 25;
	else if (volt >= 9.96f)
		return 20;
	else if (volt >= 9.795f)
		return 15;
	else if (volt >= 9.63f)
		return 10;
	else if (volt >= 9.465f)
		return 5;
	return 0;
}

uint8_t getBatPercent2(float volt)
{
	if (volt >= 4.044f) // 4.044V ---> 100%的分界线
		return 100;
	else if (volt >= 4.019f)
		return getRatio(96, 4, volt, 4.019f, 4.044f); // 4.019V - 4.044V ---> 96 - 100%
	else if (volt >= 3.941f)
		return getRatio(68, 28, volt, 3.941f, 4.019f); // 3.941V - 4.019V ---> 68 - 96%
	else if (volt >= 3.500f)
		return getRatio(0, 68, volt, 3.500f, 3.941f); // 3.500V - 3.941V ---> 0 - 68%
	return 0;
}

void get_charge_state(void)
{
	static uint8_t finished_shake = 0;
	static uint8_t change_shake = 0;
	static uint8_t no_change_shake = 0;
	static uint32_t delay_tick = 0;

	if (GetTimeInterval(delay_tick, GetSysTick()) >= 100)
	{
		delay_tick = GetSysTick();

		if (!S_CHG) // 充电插入0 充满1
		{
			if (U_CHG)
			{
				change_shake = 0;
				if (globeState.chargeStat != charge_ok)
				{
					finished_shake++;
					if (finished_shake >= 50)
					{
						finished_shake = 0;
						globeState.chargeStat = charge_ok;
						globeState.batPercentRefresh = 255;
						Debug("chargeStat: finished_shake");
						remote_system_data_send_to_app();
						if (power_state == power_off)
						{
							vTaskSuspend(ParseBoatMavTaskHandle);
							vTaskSuspend(JoystickSendHandle);
							vTaskSuspend(ParseAppMavTaskHandle);
						}
					}
				}
			}
			else
			{
				finished_shake = 0;
				if (globeState.chargeStat != is_charging)
				{
					change_shake++;
					if (change_shake >= 3)
					{
						change_shake = 0;
						globeState.chargeStat = is_charging;
						remote_system_data_send_to_app();
						Debug("chargeStat: is_charging");
						globeState.batPercentRefresh = 255;
						if (power_state == power_off)
						{
							vTaskSuspend(ParseBoatMavTaskHandle);
							vTaskSuspend(JoystickSendHandle);
							vTaskSuspend(ParseAppMavTaskHandle);
						}
					}
				}
			}
			no_change_shake = 0;
		}
		else
		{
			finished_shake = 0;
			change_shake = 0;
			no_change_shake++;
			if (no_change_shake >= 5)
			{
				if (globeState.chargeStat != not_charging)
				{
					globeState.chargeStat = not_charging;
					globeState.batPercentRefresh = 255;
					Debug("chargeStat: not_charging");
					remote_system_data_send_to_app();
				}
				if (power_state == power_off)
				{
					Debug("power_off");
					Power_Unlock();
					for (;;)
					{
						delay_ms(30);
					}
				}
			}
			else if (no_change_shake >= 1 && (globeState.chargeStat == is_charging || globeState.chargeStat == charge_ok))
			{
				globeState.chargeStat = delay_not_charging;
				Debug("chargeStat: delay_not_charging");
			}
		}
	}
}

void battery_charging(void)
{
}

/*设置显示界面*/
void set_show_ui(enum ui_e ui)
{
	extern MenuFun MenuFunArray[];

	last_show_ui = show_ui;
	show_ui = ui; // 必须写在这里

	switch (ui)
	{
	case MAIN_UI:
		globe_key.Key_Type = key_name_num;
		globe_key.Key_Value = key_invalid;
		globe_key.key_Down_Cnt = 0;
		if (globeState.TaskPresetFlag == 0)
		{
			lv_show_popup_del();
			anchor_animation_del();
			boat_task_preset_ui_del((S_TaskPresetUi *)&globeState.TaskPresetUi);
			lv_obj_clean(globeGUI.screen);
			globeGUI.main_label = NULL;
			globeGUI.log_img = NULL;
			globeGUI.light_img = NULL;
			globeGUI.main_label2 = NULL;
			main_ui_init();
		}
		else
		{
			boat_task_preset_ui_del((S_TaskPresetUi *)&globeState.TaskPresetUi);
			globeState.TaskPresetFlag = 0;
		}
		break;
	case MENU_UI:
		lv_show_popup_del();
		task_animation_del();
		anchor_animation_del();
		boat_task_preset_ui_del((S_TaskPresetUi *)&globeState.TaskPresetUi);
		lv_obj_clean(globeGUI.screen);
		globeGUI.main_label = NULL;
		globeGUI.log_img = NULL;
		globeGUI.light_img = NULL;
		globeGUI.main_label2 = NULL;
		main_menu_init();
		globeState.menu_timeout = GetSysTick();
		break;
	case CHARGE_UI:
		lv_show_popup_del();
		task_animation_del();
		anchor_animation_del();
		boat_task_preset_ui_del((S_TaskPresetUi *)&globeState.TaskPresetUi);
		lv_obj_clean(globeGUI.screen);
		globeGUI.main_label = NULL;
		globeGUI.log_img = NULL;
		globeGUI.light_img = NULL;
		globeGUI.main_label2 = NULL;
		change_ui_init();
		break;
	case BOAT_TASK_PRESET_UI:
		lv_show_popup_del();
		boat_task_preset_ui_init((S_TaskPresetUi *)&globeState.TaskPresetUi);
		break;
	default:
		if (show_ui <= MENU_UI && MenuFunArray[show_ui])
		{
			MenuFunArray[show_ui]();
		}
		break;
	}
}

/*界面显示初始化*/
void display_init(void)
{
}

/*显示开机LOG*/
void show_poweron_log(void)
{
	const char str2[] = "HOME TO FISHERMAN  ";
	const char str3[] = "让钓鱼跃入科技时代  ";
	const lv_img_dsc_t *const log_buf[] = {
		&logo,
		&yutantan,
	};
	char str[40] = {0};
	uint8_t i;

	lv_obj_t *img = lv_img_create(globeGUI.screen);
	lv_img_set_src(img, log_buf[globeState.Log]);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, -30);

	lv_obj_t *lable = lv_label_create(globeGUI.screen);
	lv_obj_set_style_text_color(lable, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
	lv_obj_set_style_text_font(lable, &font_blod_16, LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(lable, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示
	lv_obj_align(lable, LV_ALIGN_CENTER, 0, 30);
	lv_obj_set_style_size(lable, LCD_W, 40);
	lv_label_set_text(lable, "  ");

	for (i = 0; i < 20; i++)
	{
		lv_img_set_zoom(img, 0.05f * i * 256.0f);
		delay_ms(25);
		lvgl_force_refresh();
		LCD_Backlight = 999;
	}

	if (globeState.AtHomeAndAbroad == 0 || globeState.AtHomeAndAbroad == 1)
	{
		lv_obj_set_style_text_font(lable, &font_blod_16, LV_STATE_DEFAULT);
		for (i = 0; i < sizeof(str2) - 1; i++)
		{
			strncpy(str, str2, i);
			lv_label_set_text(lable, str);
			delay_ms(10);
			lvgl_force_refresh();
		}
	}
	else if (globeState.AtHomeAndAbroad == 1)
	{
		lv_obj_set_style_text_font(lable, &font_18, LV_STATE_DEFAULT);
		for (i = 0; i < sizeof(str3) - 1; i++)
		{
			strncpy(str, str3, i);
			lv_label_set_text(lable, str);
			delay_ms(10);
			lvgl_force_refresh();
		}
	}

	delay_ms(1000);
}

void lvgl_force_refresh(void)
{
	lv_disp_t *disp = lv_disp_get_default();
	if (disp == NULL)
		return;

	lv_obj_invalidate(lv_scr_act()); // 标记当前屏幕为无效，需要重绘
	lv_refr_now(disp);				 // 立即刷新显示
}

static void remote_lowpower_time_callback(lv_timer_t *timer)
{
	static uint8_t value = 100;
	static uint8_t flag = 0;

	if (show_ui == MAIN_UI && globeGUI.remote_bat)
	{
		lv_obj_set_style_bg_opa(globeGUI.remote_bat, 2.55 * value, LV_STATE_DEFAULT);

		if (flag)
		{
			value += 1;
			if (value > 100)
			{
				value = 100;
				flag = !flag;
			}
		}
		else
		{
			value -= 1;
			if (value < 50)
			{
				value = 50;
				flag = !flag;
			}
		}
	}
}

static void boat_lowpower_time_callback(lv_timer_t *timer)
{
	static uint8_t value = 100;
	static uint8_t flag = 0;

	if (show_ui == MAIN_UI && globeGUI.boat_bat)
	{
		lv_obj_set_style_bg_opa(globeGUI.boat_bat, 2.55 * value, LV_STATE_DEFAULT);
		if (flag)
		{
			value += 1;
			if (value > 100)
			{
				value = 100;
				flag = !flag;
			}
		}
		else
		{
			value -= 1;
			if (value < 50)
			{
				value = 50;
				flag = !flag;
			}
		}
	}
}

static inline void carry_out_the_tasks_of_the_app(void)
{
	if (globeState.App_Task_Flag)
	{
		if (globeState.TaskPresetFlag != 0)
		{
			set_show_ui(BOAT_TASK_PRESET_UI);
		}
		else
		{
			S_MsgAsk_Msg MsgAsk_Msg;
			if (boat_task_init((S_Position *)&globeState.App_Task_Msg.Position, 1, globeState.App_Task_Msg.TaskType,
							   globeState.App_Task_Msg.Hopper, globeState.App_Task_Msg.Home, globeState.App_Task_Msg.LED_Sta, globeState.App_Task_Msg.Hook, 1)) // show_ui == MAIN_UI ? 1 : 0
			{
				MsgAsk_Msg.Ask_Data = AppTaskSuccess;
			}
			else
			{
				MsgAsk_Msg.Ask_Data = AppTaskFail;
			}
			MsgAsk_Msg.Msg_ID = App_Task_Msg_ID;
			mavlink_msg_send_to_app(MsgASK_Msg_ID, (const char *)&MsgAsk_Msg, sizeof(S_MsgAsk_Msg));
		}
		globeState.App_Task_Flag = 0;
	}
}

static inline void other_tasks_call_the_ui(void)
{
	if (globeState.PopUp_Inform.PopUp_EN)
	{
		globeState.PopUp_Inform.PopUp_EN = 0;
		if (*((uint32_t *)&globeState.Task_Sta.GetPosA_En))
		{
			lv_show_popup_del();
		}
		show_popup(globeState.PopUp_Inform.img_id, globeState.PopUp_Inform.str1_id, globeState.PopUp_Inform.str2_id, globeState.PopUp_Inform.bar_en);
	}

	if (globeState.Cut_Show_UI != MAX_SHOW_UI)
	{
		set_show_ui(globeState.Cut_Show_UI);
		globeState.Cut_Show_UI = MAX_SHOW_UI;
	}
}

/*显示任务*/
void display_task(void *param)
{
	lv_init();			  // lvgl系统初始化
	lv_port_disp_init();  // lvgl显示接口初始化,放在lv_init()的后面
	lv_port_indev_init(); // lvgl输入接口初始化,放在lv_init()的后面
	globeGUI.screen = lv_scr_act();
	lv_obj_set_style_bg_color(globeGUI.screen, lv_color_black(), 0); // 设置屏幕背景为黑色
	lv_obj_clear_flag(globeGUI.screen, LV_OBJ_FLAG_SCROLLABLE);		 // 关闭滚动

	globeGUI.RemoteLowPowerTime = lv_timer_create(remote_lowpower_time_callback, 20, 0);
	globeGUI.BoatLowPowerTime = lv_timer_create(boat_lowpower_time_callback, 20, 0);
	lv_timer_pause(globeGUI.RemoteLowPowerTime);
	lv_timer_pause(globeGUI.BoatLowPowerTime);

	// globeState.BoatVersion = Rogue_MAX;
	// globeState.AtHomeAndAbroad = 2;

	show_poweron_log();
	set_show_ui(show_ui);

	for (;;)
	{
		other_tasks_call_the_ui();
		carry_out_the_tasks_of_the_app();

		switch (show_ui)
		{
		case MAIN_UI:
		case BOAT_TASK_PRESET_UI:
			main_ui_refresh_task();
			break;
		case MENU_UI:
			if (GetTimeInterval(globeState.menu_timeout, GetSysTick()) >= 20000)
			{
				set_show_ui(MAIN_UI);
			}
			break;
		case Joystick_Calib:
			joystickCalib_ui();
			break;
		case CHARGE_UI:
			change_run();
			break;
		case Pairing_mode:
			SetRF_ID_Run();
			break;
		default:
			break;
		}
		lv_task_handler();
		IWDG_Feed();
		delay_ms(10);
	}
}

static inline void detect_voltage_carry_out_once_upon_power_up(void)
{
	if (S_CHG) // 充电插入0 充满1
	{
		float RemoteBat = 0;
		RemoteBat = 1.2f * getAdcValue(ADC_BAT) / getAdcValue(ADC_REF);
		globeState.RemoteBat = 3.0f * RemoteBat / 2.0f * 1000.0f;
		globeState.batPercent = getBatPercent2(globeState.RemoteBat / 1000.0f);
		Debug("remoter bat: %d %d%%", globeState.RemoteBat, globeState.batPercent);
	}
}

static inline void detect_remote_voltage(void)
{
	float remoterBat = 0;
	static uint8_t carry_out_once_5 = 0;
	static uint8_t carry_out_once_10 = 0;
	static uint8_t carry_out_once_20 = 0;
	static uint8_t cnt = 0;
	static float sum = 0;
	static uint32_t delay_tick = 0;

	if (GetTimeInterval(delay_tick, GetSysTick()) >= 100)
	{
		delay_tick = GetSysTick();

		if (globeState.chargeStat == not_charging || globeState.chargeStat == delay_not_charging)
		{
			remoterBat = 1.2f * getAdcValue(ADC_BAT) / getAdcValue(ADC_REF);
			remoterBat = 3 * remoterBat / 2;
			sum += remoterBat;

			if (++cnt >= (globeState.chargeStat == delay_not_charging ? 3 : 100))
			{
				remoterBat = sum / cnt;
				globeState.RemoteBat = remoterBat * 1000;
				globeState.batPercent = getBatPercent2(globeState.RemoteBat / 1000.0f);
				mavlink_msg_send_to_app(RemoteVoltagePercent_Msg_ID, (void *)&globeState.batPercent, sizeof(globeState.batPercent));
				Debug("remoter bat: %03d %03d%%", globeState.RemoteBat, globeState.batPercent);

				static uint8_t lowpower_off = 0;
				if (globeState.batPercent == 0 && globeState.chargeStat == not_charging)
				{
					if (lowpower_off++ >= 2)
					{
						PowerOFF_Hint();
					}
				}
				else
				{
					lowpower_off = 0;
				}

				if (globeState.batPercent <= 5 && !carry_out_once_5)
				{
					globeState.RemoteLowPowerFlag = 1;
					carry_out_once_5 = 1;
				}
				else if (globeState.batPercent > 5 && globeState.batPercent <= 10 && !carry_out_once_10)
				{
					globeState.RemoteLowPowerFlag = 1;
					carry_out_once_10 = 1;
				}
				else if (globeState.batPercent > 10 && globeState.batPercent <= 20 && !carry_out_once_20)
				{
					globeState.RemoteLowPowerFlag = 1;
					carry_out_once_20 = 1;
				}

				sum = 0;
				cnt = 0;
			}
		}
		else
		{
			sum = 0;
			cnt = 0;
			carry_out_once_5 = 0;
			carry_out_once_10 = 0;
			carry_out_once_20 = 0;
		}
	}
}

static inline void auto_set_home_point(void)
{
	static uint8_t delay = 0;

	// if (!globeState.home_sta && ROVER_MODE_RTL != globeState.custom_mode && globeState.satelliteNum > 10)
	if (!globeState.home_sta && globeState.satelliteNum > 10)
	{
		if (my_mavlink_msg_command(MAV_CMD_GET_HOME_POSITION, 1.0, 0, 0, 0, 0, 0, 0, 0))
		{
			globeState.home_sta = 1;
			Debug("---------- Get Home OK----------");
		}
		if (delay >= 40)
		{
			if (!globeState.home_sta)
			{
				double degE7_lat = (double)(globeState.current_position.degE7_lat - globeState.Reposition_Value.lat_Diff) / 10000000.0;
				double degE7_long = (double)(globeState.current_position.degE7_long - globeState.Reposition_Value.long_Diff) / 10000000.0;
				if (my_mavlink_msg_command(MAV_CMD_DO_SET_HOME, 0, 0, 0, 0, degE7_lat, degE7_long, 0, 0))
				{
					globeState.home_sta = 1;
					Debug("---------- Set Home OK----------");
				}
			}
		}
		else
		{
			delay++;
		}
	}
}

static inline void boat_disconnection_detection(void)
{
	if (globeState.isConnect)
	{
		Debug("NowTask.TaskType: %d", globeState.NowTask.TaskType);
		if (globeState.connectCnt)
		{
			globeState.connectCnt--;
		}
		else
		{
			globeState.isConnect = 0;
			globeState.boat_voltage_battery = 0;
			globeState.rf_rssi = 0;
			if (globeState.TaskPresetFlag != 0)
			{
				globeState.TaskPresetFlag = 0;
				globeState.Cut_Show_UI = MAIN_UI;
				mavlink_msg_send_to_app(ClearTaskPreset_Msg_ID, (void *)0, 0);
			}
		}
	}
}

static inline void synchronize_correction_value_to_app(void)
{
	if (globeState.Reposition_CNT && GetTimeInterval(globeState.Reposition_Time, GetSysTick()) >= 1000)
	{
		Debug("mavlink_msg_send_to_app -> Reposition_Value_Msg_ID");
		mavlink_msg_send_to_app(Reposition_Value_Msg_ID, (const char *)&globeState.Reposition_Value, sizeof(S_Reposition_Value_Msg));
		globeState.Reposition_CNT--;
		globeState.Reposition_Time = GetSysTick();
	}
}

void low_priority_task(void *param)
{
	uint32_t delay_tick = 0;
	int cat_boat_version_cnt = 10;

	delay_ms(1000); // 等待ADC稳定
	detect_voltage_carry_out_once_upon_power_up();

	for (;;)
	{
		detect_remote_voltage();

		if (GetTimeInterval(delay_tick, GetSysTick()) >= 1000)
		{
			delay_tick = GetSysTick();
			boat_disconnection_detection();
			auto_set_home_point();
			if (globeState.isConnect && cat_boat_version_cnt-- > 0)
			{
				my_mavlink_msg_command(42428, 0, 0, 0, 0, 0, 0, 0, 0);
			}
			if (globeState.read_pair_id_flag == 0)
			{
				mavlink_set_sys_msg_send_to_dtu(DTU_SONAR_SYS_ID, BOAT_DTU_COMP_ID, LinuxCommand_Msg_ID, (char *)"cat wpa_supplicant.conf", strlen("cat wpa_supplicant.conf") + 1);
			}
		}
		synchronize_correction_value_to_app();
		get_charge_state();
		delay_ms(100);
	}
}
