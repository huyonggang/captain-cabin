#include "main.h"

static TaskHandle_t startTaskHandle;
S_HardFaultMsgSave HardFaultMsgSave;
int DebugGrade = LOG_LEVEL_DEBUG; /* 日志打印等级 */

void led_task(void *param)
{
    for (;;)
    {
        Time_Control_Update();
        if (globeState.SuspendMavRecTaskTime && GetTimeInterval(globeState.SuspendMavRecTaskTime, GetSysTick()) >= 10000)
        {
            vTaskResume(ParseBoatMavTaskHandle);
            globeState.SuspendMavRecTaskTime = 0;
        }
        delay_ms(10);
    }
}

int main(void)
{
    SCB->VTOR = 0x08010000;
    NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_4);
    // iwdt_init(IWDT_DIVIDER_32, 875);
    sys_apm32_clock_init(336, 8, 2, 7);
    delay_init();
    uart_init(2000000);
    configParamInit();
    KeyIntInit();
    My_Gpio_Init();
    Motor_PWM_Init();
    Alarm_Data_Init();
    LongKeyPowerON();
    joystickInit();
    LCD_Init();
    LCD_Fill(0, 0, LCD_W, LCD_H, 0);
    TFT_Backlight_PWM_Init();
    Debug("System Init OK !");
    xTaskCreate(startTask, "startTask", 100, NULL, 2, &startTaskHandle);
    vTaskStartScheduler();

    for (;;)
    {
    }
}

// 任务堆栈溢出检测
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    for (;;)
    {
        log_error("-------- task %s is stack overflow. --------\r\n", pcTaskName);
        delay_ms(100);
    }
}

/*创建任务*/
void startTask(void *param)
{
    taskENTER_CRITICAL(); /*进入临界区*/

    xTaskCreate(parse_boat_mavlink_msg_task, "ParseBoatMavTask", 1024 + 512, NULL, 8, &ParseBoatMavTaskHandle); /*创建解析船控数据任务*/
    xTaskCreate(joystick_value_send_to_boat, "JoystickValueSend", 512, NULL, 7, &JoystickSendHandle);           /*创建摇杆值发送任务*/
    xTaskCreate(parse_app_mavlink_msg_task, "ParseAppMavTask", 512 + 512, NULL, 6, &ParseAppMavTaskHandle);     /*创建WiFi接收任务*/
    xTaskCreate(display_task, "display_task", 2048 + 2048, NULL, 5, NULL);                                      /*创建显示任务*/
    xTaskCreate(key_task, "key_task", 512, NULL, 4, &KEYTask_Handler);                                          /*创建按键扫描任务*/
    xTaskCreate(led_task, "led_task", 512, NULL, 3, NULL);                                                      /*创建LED控制任务*/
    xTaskCreate(low_priority_task, "low_priority_task", 512, NULL, 2, &LowPriorityTaskHandle);                  /*创建普通任务任务*/
    vTaskDelete(startTaskHandle);                                                                               /*删除开始任务*/

    taskEXIT_CRITICAL(); /*退出临界区*/
}

void vApplicationIdleHook(void)
{
    IWDG_Feed();
    // __WFI(); /*进入低功耗模式*/
}
