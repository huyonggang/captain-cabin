#include "joystickCalib_ui.h"
#include "main.h"

extern const lv_img_dsc_t rocker_1;

#define FONT_0 font_blod_16 // 开始校准 + 完成校准  // lv_font_montserrat_14
#define FONT_1 font_blod_34 // 摇动摇杆一圈 + 保持摇杆回中
#define FONT_2 font_16		// 完成后点击Enter
#define FONT_3 font_14		// 显示摇杆值

const unsigned char *stepLanguage1[LanguageMAX] = {
	{"摇动摇杆一圈"},
	{"Rock joystick a circle"},
	{"Джойстик в центре"},
};

const unsigned char *stepLanguage2[LanguageMAX] = {
	{"开始校准"},
	{"Start calibration"},
	{"Начать калибровку"},
};

const unsigned char *stepLanguage3[LanguageMAX] = {
	{"保持摇杆回中"},
	{"Keep joystick on center"},
	{"Нажмите ENTER продолжить"},
};

const unsigned char *stepLanguage4[LanguageMAX] = {
	{"完成后点击Enter"},
	{"Press Enter when finished"},
	{"Нажмите Enter когда закончите"},
};

const unsigned char *stepLanguage5[LanguageMAX] = {
	{"完成校准"},
	{"Calibration complete"},
	{"Калибровка завершена"},
};

void joystickCalib_ui_setp(uint8_t setp)
{
	lv_obj_clean(globeGUI.screen);

	/* 图片 + 开始校准 + 完成校准 的obj*/
	lv_obj_t *obj = lv_obj_create(globeGUI.screen);
	lv_obj_set_style_border_opa(obj, LV_OPA_0, LV_STATE_DEFAULT);			  // 设置边框透明度
	lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT); // 无边框
	lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_STATE_DEFAULT); // 设置背景颜色为黑色
	lv_obj_set_style_radius(obj, 0, LV_STATE_DEFAULT);						  // 设置样式对象的圆角半径为0
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);							  // 关闭滚动
	if (setp)
	{
		lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 20); // 显示位置
	}
	else
	{
		lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 30); // 显示位置
	}
	lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);											  // 容器宽度为屏幕宽度，高度根据内容确定
	lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);												  // 设置为水平布局
	lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 在所有方向上居中对齐

	/* 图片 */
	globeGUI.joy_img = lv_img_create(obj);

	/* 开始校准 */
	globeGUI.joy_label_1 = lv_label_create(obj);
	lv_obj_set_style_text_font(globeGUI.joy_label_1, &FONT_0, LV_STATE_DEFAULT);
	if (setp)
	{
		lv_img_set_src(globeGUI.joy_img, &rocker_2);
		lv_label_set_text(globeGUI.joy_label_1, (const char *)stepLanguage5[configParam.language]); // 完成校准
	}
	else
	{
		lv_img_set_src(globeGUI.joy_img, &rocker_1);
		lv_label_set_text(globeGUI.joy_label_1, (const char *)stepLanguage2[configParam.language]); // 显示开始校准
	}
	lv_obj_set_style_text_color(globeGUI.joy_label_1, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
	const lv_font_t *font = lv_obj_get_style_text_font(globeGUI.joy_label_1, LV_PART_MAIN);		 // 获取标签使用的字体
	const char *text = lv_label_get_text(globeGUI.joy_label_1);									 // 获取标签的文本
	lv_coord_t text_width = lv_txt_get_width(text, strlen(text), font, 0, LV_TEXT_FLAG_NONE);	 // 计算文本的宽度
	if (text_width > 200)
	{
		lv_obj_set_width(globeGUI.joy_label_1, 200);								 // 设置最大显示宽度
		lv_label_set_long_mode(globeGUI.joy_label_1, LV_LABEL_LONG_SCROLL_CIRCULAR); // 字符串超过了最大宽度滚动显示
	}
	lv_obj_set_style_text_align(globeGUI.joy_label_1, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示

	/* 摇动摇杆一圈 */
	globeGUI.joy_label_2 = lv_label_create(globeGUI.screen);
	if (setp)
	{
		lv_obj_align(globeGUI.joy_label_2, LV_ALIGN_BOTTOM_MID, 0, -77); // 显示位置
	}
	else
	{
		lv_obj_align(globeGUI.joy_label_2, LV_ALIGN_BOTTOM_MID, 0, -60); // 显示位置
	}
	lv_obj_set_style_text_color(globeGUI.joy_label_2, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
	if (configParam.language)
	{
		lv_obj_set_style_text_font(globeGUI.joy_label_2, &font_blod_24, LV_STATE_DEFAULT); // 字体文件
	}
	else
	{
		lv_obj_set_style_text_font(globeGUI.joy_label_2, &FONT_1, LV_STATE_DEFAULT); // 字体文件
	}
	if (setp)
	{
		lv_label_set_text(globeGUI.joy_label_2, (const char *)stepLanguage3[configParam.language]); // 显示文字 保持摇杆回中
	}
	else
	{
		lv_label_set_text(globeGUI.joy_label_2, (const char *)stepLanguage1[configParam.language]); // 显示文字 摇动摇杆一圈
	}
	lv_obj_set_width(globeGUI.joy_label_2, 320);											   // 设置最大显示宽度
	lv_obj_set_style_text_align(globeGUI.joy_label_2, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 字符串居中显示
	lv_label_set_long_mode(globeGUI.joy_label_2, LV_LABEL_LONG_SCROLL_CIRCULAR);			   // 字符串超过了最大宽度滚动显示

	if (setp)
	{
		/* 完成后点击Enter */
		globeGUI.joy_label_3 = lv_label_create(globeGUI.screen);
		lv_obj_align(globeGUI.joy_label_3, LV_ALIGN_BOTTOM_MID, 0, -44);							 // 显示位置
		lv_obj_set_style_text_color(globeGUI.joy_label_3, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
		lv_obj_set_style_text_font(globeGUI.joy_label_3, &FONT_2, LV_STATE_DEFAULT);				 // 字体文件
		lv_label_set_text(globeGUI.joy_label_3, (const char *)stepLanguage4[configParam.language]);	 // 显示文字 完成后点击Enter
		lv_obj_set_width(globeGUI.joy_label_3, 320);												 // 设置最大显示宽度
		lv_obj_set_style_text_align(globeGUI.joy_label_3, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);	 // 字符串居中显示
		lv_label_set_long_mode(globeGUI.joy_label_3, LV_LABEL_LONG_SCROLL_CIRCULAR);				 // 字符串超过了最大宽度滚动显示
																									 // lv_obj_add_flag(globeGUI.joy_label_3, LV_OBJ_FLAG_HIDDEN);									 // 隐藏 完成后点击Enter
	}
	/* 显示摇杆值 */
	globeGUI.joy_label_4 = lv_label_create(globeGUI.screen);
	lv_obj_align(globeGUI.joy_label_4, LV_ALIGN_BOTTOM_LEFT, 10, -10);							 // 显示位置
	lv_obj_set_style_text_color(globeGUI.joy_label_4, lv_color_hex(0x707070), LV_STATE_DEFAULT); // 字体颜色
	lv_obj_set_style_text_font(globeGUI.joy_label_4, &FONT_3, LV_STATE_DEFAULT);				 // 字体文件
	lv_label_set_text_fmt(globeGUI.joy_label_4, "THR: %4d", getAdcValue(ADC_ROLL));				 // 显示ADC_ROLL

	/* 显示摇杆值 */
	globeGUI.joy_label_5 = lv_label_create(globeGUI.screen);
	lv_obj_align(globeGUI.joy_label_5, LV_ALIGN_BOTTOM_RIGHT, -10, -10);						 // 显示位置
	lv_obj_set_style_text_color(globeGUI.joy_label_5, lv_color_hex(0x707070), LV_STATE_DEFAULT); // 字体颜色
	lv_obj_set_style_text_font(globeGUI.joy_label_5, &FONT_3, LV_STATE_DEFAULT);				 // 字体文件
	lv_label_set_text_fmt(globeGUI.joy_label_5, "ROL: %4d", getAdcValue(ADC_PITCH));			 // 显示ADC_PITCH
}

void joystickCalib_ui_init(void)
{
	joystickCalib_ui_setp(0);
}

void joystickCalib_img_ui_init(lv_obj_t **arc)
{
	lv_obj_clean(globeGUI.screen);

	// lv_obj_t *arc = lv_arc_create(lv_scr_act());
	// lv_arc_set_rotation(arc, 180 + 45);			   // 旋转角度
	// lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
	// lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
	// lv_obj_center(arc);
	// lv_obj_set_size(arc, 140, 140);												   /* 宽度和高度都设置为150像素 */
	// lv_obj_set_style_arc_width(arc, 37, LV_STATE_DEFAULT);						   /* 设置线条厚度为20像素 */
	// lv_obj_set_style_arc_width(arc, 37, LV_PART_INDICATOR);						   /* 设置线条厚度为20像素 */
	// lv_obj_set_style_arc_rounded(arc, 0, LV_PART_INDICATOR);					   /* 设置圆弧边缘为直角 */
	// lv_obj_set_style_arc_color(arc, lv_color_make(4, 210, 82), LV_PART_INDICATOR); /* 设置圆弧的前景颜色 */
	// lv_obj_set_style_arc_color(arc, lv_color_make(0, 22, 0), LV_PART_MAIN);		   /* 设置为灰色 */
	// lv_arc_set_bg_angles(arc, 0, 360);											   /* 设置开始角度为0度，结束角度为360度 */
	// lv_arc_set_value(arc, 25);

	for (uint8_t i = 0; i < 4; i++)
	{
		arc[i] = lv_arc_create(lv_scr_act());
		lv_arc_set_rotation(arc[i], 180 + 45);			  // 旋转角度
		lv_obj_remove_style(arc[i], NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
		lv_obj_clear_flag(arc[i], LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
		lv_obj_center(arc[i]);
		lv_obj_set_size(arc[i], 140, 140);							/* 宽度和高度都设置为150像素 */
		lv_obj_set_style_arc_width(arc[i], 37, LV_STATE_DEFAULT);	/* 设置线条厚度为20像素 */
		lv_obj_set_style_arc_width(arc[i], 37, LV_PART_INDICATOR);	/* 设置线条厚度为20像素 */
		lv_obj_set_style_arc_rounded(arc[i], 0, LV_PART_INDICATOR); /* 设置圆弧边缘为直角 */
		lv_obj_set_style_arc_rounded(arc[i], 0, LV_PART_MAIN);		/* 设置圆弧边缘为直角 */

		lv_obj_set_style_arc_color(arc[i], lv_color_make(4, 210, 82), LV_PART_INDICATOR); /* 设置圆弧的前景颜色 */
		lv_obj_set_style_arc_color(arc[i], lv_color_make(0, 22, 0), LV_PART_MAIN);		  /* 设置为灰色 */
		lv_arc_set_bg_angles(arc[i], 90 * i, 90 + 90 * i);								  /* 设置开始角度为0度，结束角度为360度 */
		lv_arc_set_value(arc[i], 0);
	}

	lv_obj_t *img = lv_img_create(lv_scr_act());
	lv_img_set_src(img, &Rocker_img);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, -4);
	// lv_img_set_zoom(img, 2 * LV_IMG_ZOOM_NONE); // 放大两倍

	/* 显示摇杆值 */
	globeGUI.joy_label_4 = lv_label_create(globeGUI.screen);
	lv_obj_align(globeGUI.joy_label_4, LV_ALIGN_BOTTOM_LEFT, 10, -10);							 // 显示位置
	lv_obj_set_style_text_color(globeGUI.joy_label_4, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
	lv_obj_set_style_text_font(globeGUI.joy_label_4, &FONT_3, LV_STATE_DEFAULT);				 // 字体文件
	lv_label_set_text_fmt(globeGUI.joy_label_4, "THR: %4d", getAdcValue(ADC_ROLL));				 // 显示ADC_ROLL

	/* 显示摇杆值 */
	globeGUI.joy_label_5 = lv_label_create(globeGUI.screen);
	lv_obj_align(globeGUI.joy_label_5, LV_ALIGN_BOTTOM_RIGHT, -10, -10);						 // 显示位置
	lv_obj_set_style_text_color(globeGUI.joy_label_5, lv_color_hex(0xffffff), LV_STATE_DEFAULT); // 字体颜色
	lv_obj_set_style_text_font(globeGUI.joy_label_5, &FONT_3, LV_STATE_DEFAULT);				 // 字体文件
	lv_label_set_text_fmt(globeGUI.joy_label_5, "ROL: %4d", getAdcValue(ADC_PITCH));			 // 显示ADC_PITCH
}

void joystickCalib_ui(void)
{
#define CNT_MAX 3
	static uint8_t isCENTER = 0;
	static uint8_t steps = 0;
	static uint8_t img_step = 0;
	static s16 max[4] = {0, 0, 0, 0}, min[4] = {4095, 4095, 4095, 4095};
	static uint8_t pitch_max_flag = 0, pitch_min_flag = 0, roll_max_flag = 0, roll_min_flag = 0;
	static uint8_t pitch_max_cnt = 0, pitch_min_cnt = 0, roll_max_cnt = 0, roll_min_cnt = 0;

	static lv_obj_t *arc[4];

	joystickParam_t jsParam;
	joystickFlyui16_t adcValue;

	getFlyDataADCValue(&adcValue);

	lv_label_set_text_fmt(globeGUI.joy_label_4, "THR: %4d", adcValue.pitch); // 显示ADC_ROLL
	lv_label_set_text_fmt(globeGUI.joy_label_5, "ROL: %4d", adcValue.roll);	 // 显示ADC_PITCH

	if (adcValue.pitch >= (configParam.jsParam.pitch.mid - DIR_MID_PITCH) &&
		adcValue.pitch <= (configParam.jsParam.pitch.mid + DIR_MID_PITCH) &&
		adcValue.roll >= (configParam.jsParam.roll.mid - DIR_MID_ROLL) &&
		adcValue.roll <= (configParam.jsParam.roll.mid + DIR_MID_ROLL))
	{
		isCENTER = 1;
	}

	if (isCENTER)
	{
		if (steps == 0)
		{
			// roll
			max[0] = MAX(max[0], adcValue.roll);
			min[0] = MIN(min[0], adcValue.roll);
			// pitch
			max[1] = MAX(max[1], adcValue.pitch);
			min[1] = MIN(min[1], adcValue.pitch);
			// yaw
			max[2] = MAX(max[2], adcValue.yaw);
			min[2] = MIN(min[2], adcValue.yaw);
			// thrust
			max[3] = MAX(max[3], adcValue.thrust);
			min[3] = MIN(min[3], adcValue.thrust);

			if (!pitch_max_flag && adcValue.pitch > 4096.0f * 0.8f) // 下
			{
				if (pitch_max_cnt++ > CNT_MAX)
				{
					if (!img_step)
					{
						joystickCalib_img_ui_init(arc);
					}
					pitch_max_cnt = 0;
					pitch_max_flag = 1;
					img_step++;
					if (arc[2])
					{
						lv_arc_set_value(arc[2], 100);
					}
					Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
				}
			}
			if (!pitch_min_flag && adcValue.pitch < 4096.0f * 0.2f) // 上
			{
				if (pitch_min_cnt++ > CNT_MAX)
				{
					if (!img_step)
					{
						joystickCalib_img_ui_init(arc);
					}
					pitch_min_cnt = 0;
					pitch_min_flag = 1;
					img_step++;
					if (arc[0])
					{
						lv_arc_set_value(arc[0], 100);
					}
					Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
				}
			}
			if (!roll_max_flag && adcValue.roll > 4096.0f * 0.8f) // 右
			{
				if (roll_max_cnt++ > CNT_MAX)
				{
					if (!img_step)
					{
						joystickCalib_img_ui_init(arc);
					}
					roll_max_cnt = 0;
					roll_max_flag = 1;
					img_step++;
					if (arc[1])
					{
						lv_arc_set_value(arc[1], 100);
					}
					Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
				}
			}
			if (!roll_min_flag && adcValue.roll < 4096.0f * 0.2f) // 左
			{
				if (roll_min_cnt++ > CNT_MAX)
				{
					if (!img_step)
					{
						joystickCalib_img_ui_init(arc);
					}
					roll_max_cnt = 0;
					roll_min_flag = 1;
					img_step++;
					if (arc[3])
					{
						lv_arc_set_value(arc[3], 100);
					}
					Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, ShortMotorT, 0, 0, 0, 1);
				}
			}

			// if (pitch_min_flag && roll_max_flag) // 上和右
			// {
			// }
			// else if (pitch_min_flag && roll_min_flag) // 上和左
			// {
			// }
			// else if (pitch_max_flag && roll_max_flag) // 下和右
			// {
			// }
			// else if (pitch_max_flag && roll_min_flag) // 下和左
			// {
			// }
			// else if (pitch_min_flag && roll_min_flag && roll_max_flag) // 上左右
			// {
			// }
			// else if (pitch_max_flag && roll_min_flag && roll_max_flag) // 下左右
			// {
			// }
			// else if (pitch_min_flag && pitch_max_flag && roll_min_flag) // 上下左
			// {
			// }
			// else if (pitch_min_flag && pitch_max_flag && roll_max_flag) // 上下右
			// {
			// }

			if (img_step == 4)
			{
				steps = 1;
				lvgl_force_refresh();
				delay_ms(500);
				Time_Control_Set_Value(Vibr_Motor_ID, 100, 0, LongMotorT, 0, 0, 0, 1);
				lv_obj_clean(globeGUI.screen);
				lv_obj_t *img = lv_img_create(globeGUI.screen);
				lv_img_set_src(img, &Check_img);
				lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
				lvgl_force_refresh();
				delay_ms(500);
				joystickCalib_ui_setp(steps);
			}
		}

		if (steps == 1)
		{
			jsParam.roll.mid = adcValue.roll;
			jsParam.pitch.mid = adcValue.pitch;
			if (jsParam.roll.mid > 2048 + 4095 * 0.1f || jsParam.roll.mid < 2048 - 4095 * 0.1f)
			{
				jsParam.roll.mid = 2048;
			}

			if (jsParam.pitch.mid > 2048 + 4095 * 0.1f || jsParam.pitch.mid < 2048 - 4095 * 0.1f)
			{
				jsParam.pitch.mid = 2048;
			}
			jsParam.roll.range_pos = max[0] - jsParam.roll.mid;
			jsParam.roll.range_neg = jsParam.roll.mid - min[0];
			jsParam.pitch.range_pos = max[1] - jsParam.pitch.mid;
			jsParam.pitch.range_neg = jsParam.pitch.mid - min[1];
#if 0
			jsParam.yaw.mid = adcValue.yaw;
			jsParam.thrust.mid = adcValue.thrust;
			if (jsParam.yaw.mid > 2048 + 4095 * 0.1f || jsParam.yaw.mid < 2048 - 4095 * 0.1f)
			{
				jsParam.yaw.mid = 2048;
			}

			if (jsParam.thrust.mid > 2048 + 4095 * 0.1f || jsParam.thrust.mid < 2048 - 4095 * 0.1f)
			{
				jsParam.thrust.mid = 2048;
			}
			jsParam.yaw.range_pos = max[2] - jsParam.yaw.mid;
			jsParam.yaw.range_neg = jsParam.yaw.mid - min[2];
			jsParam.thrust.range_pos = max[3] - jsParam.thrust.mid;
			jsParam.thrust.range_neg = jsParam.thrust.mid - min[3];
#endif
		}
	}

	if (keyIsValue(Key_OK, short_release) && steps == 1)
	{
		isCENTER = 0;
		steps = 0;
		img_step = 0;
		pitch_max_flag = 0;
		pitch_min_flag = 0;
		roll_max_flag = 0;
		roll_min_flag = 0;
		configParam.jsParam = jsParam;
		Debug("pitch.mid: %d", configParam.jsParam.pitch.mid);
		Debug("pitch.range_neg: %d", configParam.jsParam.pitch.range_neg);
		Debug("pitch.range_pos: %d", configParam.jsParam.pitch.range_pos);
		Debug("roll.mid: %d", configParam.jsParam.roll.mid);
		Debug("roll.range_neg: %d", configParam.jsParam.roll.range_neg);
		Debug("roll.range_pos: %d", configParam.jsParam.roll.range_pos);

		WriteUserConfigParamEeprom();
		arc[0] = NULL;
		arc[1] = NULL;
		arc[2] = NULL;
		arc[3] = NULL;

		for (uint8_t i = 0; i < 4; i++)
		{
			min[i] = 4095;
			max[i] = 0;
		}
		set_show_ui(MENU_UI);
	}

	if (keyIsValue(Key_OK, long_pass))
	{
		isCENTER = 0;
		steps = 0;
		img_step = 0;
		pitch_max_flag = 0;
		pitch_min_flag = 0;
		roll_max_flag = 0;
		roll_min_flag = 0;
		arc[0] = NULL;
		arc[1] = NULL;
		arc[2] = NULL;
		arc[3] = NULL;
		set_show_ui(MENU_UI);
	}
}
