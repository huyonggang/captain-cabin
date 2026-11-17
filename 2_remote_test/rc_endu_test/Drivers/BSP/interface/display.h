#ifndef __DISPLAY_H
#define __DISPLAY_H

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "main_ui.h"
#include "lvgl.h"

#define POPUP_TIMEPERIOD 100
#define POPUP_DELAY 1500

// 界面类型
enum ui_e
{
	Joystick_Calib,
	// JoystickChooseUI,
	SpeedSet,
	Pairing_mode,
	Custom_function,
	Point_AB_setup,
	Anchor_setup,
	AutoCruise_setup,
	Ghost_Mode,
	Dialog_size,
	Versions,
	Language,
	Reset,
	Exit,
	SavePoint_AB,
	TaskModeSelect,
	CustomSet_function1,
	CustomSet_function2,
	CustomSet_function3,
	Ghost_Mode_Enable_Hint,
	MENU_UI,
	MAIN_UI,
	CHARGE_UI,
	BOAT_TASK_PRESET_UI,
	JoystickChooseUI,
	MAX_SHOW_UI,
};

typedef struct
{
	/* 主界面 */
	lv_obj_t *screen;
	lv_obj_t *Connect;
	lv_obj_t *Connect_label;
	lv_obj_t *RssiImg;
	lv_obj_t *satellite_label;
	lv_obj_t *satellite_img;
	lv_obj_t *remote_bat;
	lv_obj_t *remote_bat_lable;
	lv_obj_t *remote_boat_img;
	lv_obj_t *boat_bat;
	lv_obj_t *boat_bat_label;
	lv_obj_t *boat_bat_img;
	lv_obj_t *main_obj;
	lv_obj_t *log_img;
	lv_obj_t *main_label;  // 扫描剩余时间
	lv_obj_t *main_label2; // 正在执行扫描任务
	lv_obj_t *Compass_img;
	lv_obj_t *navigation_img;
	lv_obj_t *point_a_img;
	lv_obj_t *point_b_img;
	lv_obj_t *point_c_img;
	lv_obj_t *point_d_img;
	lv_obj_t *light_img;
	lv_obj_t *home_img;
	lv_obj_t *speed_img;
	lv_obj_t *home_label;
	lv_obj_t *speed_label;
	lv_timer_t *RemoteLowPowerTime;
	lv_timer_t *BoatLowPowerTime;
	uint8_t Charge_batPercent;
	uint32_t charge_delay;

	/* 菜单 */
	lv_obj_t *menu_list;
	/* 摇杆校准 */
	lv_obj_t *joy_img;
	lv_obj_t *joy_img_1;
	lv_obj_t *joy_label_1;
	lv_obj_t *joy_label_2;
	lv_obj_t *joy_label_3;
	lv_obj_t *joy_label_4;
	lv_obj_t *joy_label_5;
	/* RF ID设置 */
	lv_style_t my_style;
	lv_obj_t *GetRfID_Label[5];
	lv_obj_t *SetRfID_Label[5];
	/* 复位 */
	lv_obj_t *btn1;
	lv_obj_t *btn2;
	/* 充电 */
	lv_obj_t *charge_semicircle;
	lv_obj_t *charge_bar;
	lv_obj_t *charge_out_border;
	/* 执行任务动画 */
	lv_obj_t *Task_obj;
	lv_obj_t *Task_line_obj;
	lv_obj_t *Task_boat;
	lv_obj_t *task_line_img;
	lv_obj_t *task_num_img;
	lv_timer_t *task_time;
	uint8_t task_run_cnt;
	int16_t x_pos;
	int16_t y_pos;
	/* 锚定的动画 */
	lv_obj_t *Anchor_obj;
	lv_obj_t *Anchor_img;
	lv_obj_t *Anchor_img1;
	lv_obj_t *Anchor_img2;
	lv_obj_t *Anchor_img3;
	float img1_size;
	float img2_size;
	float img3_size;
	float img1_opa;
	float img2_opa;
	float img3_opa;
	int Anchor_run_cnt;
	lv_timer_t *Anchor_time;

	// 上下左右的阴影
	lv_obj_t *screen_cont_up;
	lv_obj_t *screen_cont_down;
	lv_obj_t *screen_cont_left;
	lv_obj_t *screen_cont_right;

	lv_obj_t *screen_cont_hint;
	lv_obj_t *screen_img_hint;
	lv_obj_t *screen_arc_hint;
	lv_obj_t *screen_label_1;
} GLOBE_GUI;

extern GLOBE_GUI globeGUI;
extern enum ui_e show_ui;
extern enum ui_e last_show_ui;

extern TaskHandle_t LowPriorityTaskHandle;

extern lv_font_t font_blod_12;
extern lv_font_t font_blod_14;
extern lv_font_t font_blod_16;
extern lv_font_t font_blod_18;
extern lv_font_t font_blod_20;
extern lv_font_t font_blod_22;
extern lv_font_t font_blod_24;
extern lv_font_t font_blod_26;
extern lv_font_t font_blod_28;
extern lv_font_t font_blod_34; // !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ 摇动摇杆一圈保持摇杆回中短按长键
extern lv_font_t font_blod_43;

extern lv_font_t font_12;
extern lv_font_t font_14;
extern lv_font_t font_16;
extern lv_font_t font_17;
extern lv_font_t font_18;
extern lv_font_t font_20;
extern lv_font_t font_22;
extern lv_font_t font_24;
extern lv_font_t font_26;
// extern lv_font_t font_34;

extern const lv_img_dsc_t Rocker_img;
extern const lv_img_dsc_t change_1_img;
extern const lv_img_dsc_t Rippton_log;
extern const lv_img_dsc_t Check_img;
extern const lv_img_dsc_t SetID_OK_icon;
extern const lv_img_dsc_t Colse_img;
extern const lv_img_dsc_t SetID_Colse_icon;
extern const lv_img_dsc_t Homepoint;
extern const lv_img_dsc_t signal00;
extern const lv_img_dsc_t signal05;
extern const lv_img_dsc_t satellite;
extern const lv_img_dsc_t remote_boat;
extern const lv_img_dsc_t boat_mini;
extern const lv_img_dsc_t CatchX_BS;
extern const lv_img_dsc_t CatchX_BS_ch;
extern const lv_img_dsc_t wuwei;
extern const lv_img_dsc_t CatchX_mini;
extern const lv_img_dsc_t boat_mini_img;
extern const lv_img_dsc_t yutantan;
extern const lv_img_dsc_t Compass;
extern const lv_img_dsc_t navigation;
extern const lv_img_dsc_t pointA_24_24;
extern const lv_img_dsc_t pointB_24_24;
extern const lv_img_dsc_t light;
extern const lv_img_dsc_t home;
extern const lv_img_dsc_t speed;
extern const lv_img_dsc_t rocker;
extern const lv_img_dsc_t link;
extern const lv_img_dsc_t WiFi_BT_Switch;
extern const lv_img_dsc_t custom;
extern const lv_img_dsc_t remote_icon;
extern const lv_img_dsc_t ABPoint;
extern const lv_img_dsc_t anchor_icon;
extern const lv_img_dsc_t screen_icon;
extern const lv_img_dsc_t version_icon;
extern const lv_img_dsc_t Earth_icon;
extern const lv_img_dsc_t reset_icon;
extern const lv_img_dsc_t exit_icon;
extern const lv_img_dsc_t ArrowLeft_icon;
extern const lv_img_dsc_t Close_icon;
extern const lv_img_dsc_t Arrow_left_L;
extern const lv_img_dsc_t Radio_off_icon;
extern const lv_img_dsc_t Radio_on_icon;
extern const lv_img_dsc_t HomeBig_img;
extern const lv_img_dsc_t Attention;
extern const lv_img_dsc_t icon_charging;
extern const lv_img_dsc_t rocker_1;
extern const lv_img_dsc_t rocker_2;
extern const lv_img_dsc_t anchor_img;
extern const lv_img_dsc_t anchor1_img;
extern const lv_img_dsc_t task_img;
extern const lv_img_dsc_t Homepoint48_48;
extern const lv_img_dsc_t pointA_48_48;
extern const lv_img_dsc_t pointB_48_48;
extern const lv_img_dsc_t PointC_48_48;
extern const lv_img_dsc_t PointD_48_48;
extern const lv_img_dsc_t PointA_80_80;
extern const lv_img_dsc_t PointB_80_80;
extern const lv_img_dsc_t PointC_80_80;
extern const lv_img_dsc_t PointD_80_80;

extern const lv_img_dsc_t fish_point_img;
extern const lv_img_dsc_t Fram_img;
extern const lv_img_dsc_t logo;
extern const lv_img_dsc_t lowpower_img;
extern const lv_img_dsc_t cruise_img;
extern const lv_img_dsc_t speed_icon;

extern const lv_img_dsc_t spot_1;
extern const lv_img_dsc_t spot_2;
extern const lv_img_dsc_t spot_3;
extern const lv_img_dsc_t spot_4;
extern const lv_img_dsc_t spot_5;
extern const lv_img_dsc_t spot_6;
extern const lv_img_dsc_t spot_7;
extern const lv_img_dsc_t spot_8;
extern const lv_img_dsc_t spot_9;
extern const lv_img_dsc_t spot_10;
extern const lv_img_dsc_t spot_11;
extern const lv_img_dsc_t spot_12;
extern const lv_img_dsc_t spot_13;
extern const lv_img_dsc_t spot_14;
extern const lv_img_dsc_t spot_15;
extern const lv_img_dsc_t spot_16;
extern const lv_img_dsc_t spot_17;
extern const lv_img_dsc_t spot_18;
extern const lv_img_dsc_t spot_19;
extern const lv_img_dsc_t spot_20;
extern const lv_img_dsc_t spot_task;

extern const lv_img_dsc_t light_icon;
extern const lv_img_dsc_t NoSaveA_icon;
extern const lv_img_dsc_t NoSaveB_icon;
extern const lv_img_dsc_t NoSaveC_icon;
extern const lv_img_dsc_t NoSaveD_icon;
extern const lv_img_dsc_t SaveA_icon;
extern const lv_img_dsc_t SaveB_icon;
extern const lv_img_dsc_t SaveC_icon;
extern const lv_img_dsc_t SaveD_icon;
extern const lv_img_dsc_t R_icon;
extern const lv_img_dsc_t intrepid_log;
extern const lv_img_dsc_t arrow1_icon;
extern const lv_img_dsc_t arrow2_icon;
extern const lv_img_dsc_t reposition;
extern const lv_img_dsc_t continue_img;
extern const lv_img_dsc_t Boat_fix;
extern const lv_img_dsc_t Line_return;
extern const lv_img_dsc_t pair_img;
extern const lv_img_dsc_t spot_a_green_l;
extern const lv_img_dsc_t spot_b_green_l;
extern const lv_img_dsc_t spot_c_green_l;
extern const lv_img_dsc_t spot_d_green_l;
extern const lv_img_dsc_t Circle;
extern const lv_img_dsc_t Trash;
extern const lv_img_dsc_t speed_medium;
extern const lv_img_dsc_t speed_medium_s;
extern const lv_img_dsc_t speed_high;
extern const lv_img_dsc_t speed_high_s;
extern const lv_img_dsc_t speed_low;
extern const lv_img_dsc_t speed_low_s;
extern const lv_img_dsc_t speed_auto;
extern const lv_img_dsc_t enter_img;
extern const lv_img_dsc_t switch_img;
extern const lv_img_dsc_t start_img;
extern const lv_img_dsc_t ghost_icon;
extern const lv_img_dsc_t ghost_max_icon1;
extern const lv_img_dsc_t ghost_max_icon2;
extern const lv_img_dsc_t logo_gif;

extern const lv_img_dsc_t icon_alert_s;
extern const lv_img_dsc_t icon_alert_xl;
extern const lv_img_dsc_t icon_shield;
extern const lv_img_dsc_t CATCHX_ULTRA_ICON;
extern const lv_img_dsc_t CATCHX_ULTRA_CH_ICON;
extern const lv_img_dsc_t Rogue_SparkMax_cn;
extern const lv_img_dsc_t Rogue_SparkMax;
extern const lv_img_dsc_t boat_rogue_fixed;
extern const lv_img_dsc_t boat_rogue_nor;

void battery_charging(void);
void set_show_ui(enum ui_e ui);
void low_priority_task(void *param);
void display_task(void *param);
void display_init(void);
void lvgl_force_refresh(void);
uint8_t getBatPercent(float volt);

#endif /*__DISPLAY_H*/
