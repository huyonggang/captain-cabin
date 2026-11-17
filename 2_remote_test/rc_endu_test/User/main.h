#ifndef __MAIN_H__
#define __MAIN_H__

#include <string.h>
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "adc.h"
#include "my_mavlink.h"
#include "app_mavlink.h"
#include "display.h"
#include "time.h"
#include "lcd.h"
#include "lcd_init.h"
#include "spi.h"
#include "lvgl.h"
#include "menu.h"
#include "main_ui.h"
#include "setIDui.h"
#include "joystickCalib_ui.h"
#include "apm32flash.h"

// #define RESTORE_PROGRESS_UI // 使用恢复任务进度条UI
// #define OLD_SET_POINT_UI // 使用以前的设置任务点UI
// #define SHOW_RSSI_DB // 显示遥控器和船的WiFi信号dB值

typedef struct
{
    unsigned long stacked_r0;
    unsigned long stacked_r1;
    unsigned long stacked_r2;
    unsigned long stacked_r3;
    unsigned long stacked_r12;
    unsigned long stacked_lr;
    unsigned long stacked_pc;
    unsigned long stacked_psr;
    unsigned long cfsr;
    unsigned long bus_fault_address;
    unsigned long memmanage_fault_address;
} S_HardFaultMsgSave;

extern S_HardFaultMsgSave HardFaultMsgSave;

void startTask(void *param);

#endif
