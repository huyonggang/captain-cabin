#include "time.h"
#include "main.h"
#include "My_Queue.h"

volatile DataLock AlarmDataLock = Unlock;

S_AlarmControl TimeControl[ALL_ID_NUM];

#ifdef Alarm_FIFO_EN
Queue_Type Alarm_FIFO[ALL_ID_NUM];
S_AlarmControl Alarm_FIFO_BUFF[ALL_ID_NUM][Alarm_FIFO_BUFF_SIZE];
#endif

void Alarm_Data_Init(void)
{
    memset(&TimeControl, 0, sizeof(TimeControl));
#ifdef Alarm_FIFO_EN
    Alarm_FIFO_Init();
#endif
}

void LED_Set_Control_Value(uint8_t Alarm_ID, uint32_t ON_Color, uint32_t OFF_Color, uint16_t ON_Time, uint16_t OFF_Time,
                           uint32_t Hold_Color, uint16_t Hold_Time, uint16_t CNT, uint8_t busy, uint8_t Other_Flag)
{
    S_AlarmControl Set_AlarmControl;

    if (Alarm_ID >= ALL_ID_NUM || busy == is_stop || !CNT)
    {
        return;
    }

    if (busy > need_recover)
    {
        busy = CanNotBreak;
    }

    if (Other_Flag > AddFifo)
    {
        Other_Flag = Other_Null;
    }

    Set_AlarmControl.LED_ID = Alarm_ID;
    Set_AlarmControl.LastTime = GetSysTick();
    Set_AlarmControl.ON_Color = ON_Color;
    Set_AlarmControl.OFF_Color = OFF_Color;
    Set_AlarmControl.ON_Time = ON_Time;
    Set_AlarmControl.OFF_Time = OFF_Time;
    Set_AlarmControl.Hold_Color = Hold_Color;
    Set_AlarmControl.Hold_Time = Hold_Time;
    Set_AlarmControl.CNT = CNT;
    Set_AlarmControl.state = 1;
    Set_AlarmControl.busy = busy;
    Set_AlarmControl.Fun = RGB_LED_Set_Color;

    if (AlarmDataLock == Unlock)
    {
        AlarmDataLock = Lock;
#ifdef Alarm_FIFO_EN
        if (Other_Flag == BreakNeedRecover) // 强行打断需要保存
        {
            if (TimeControl[Alarm_ID].busy)
            {
                TimeControl[Alarm_ID].LastTime = GetTimeInterval(TimeControl[Alarm_ID].LastTime, GetSysTick()); // 工作了多久
                Queue_AddOne(&Alarm_FIFO[Alarm_ID], &TimeControl[Alarm_ID]);
                TimeControl[Alarm_ID] = Set_AlarmControl;
                RGB_LED_Set_Color(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
            }
            else
            {
                TimeControl[Alarm_ID] = Set_AlarmControl;
                RGB_LED_Set_Color(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
            }
            AlarmDataLock = Unlock;
            return;
        }
        else if (Other_Flag == BreakWithoutRecover) // 强行打断不需要保存
        {
            TimeControl[Alarm_ID] = Set_AlarmControl;
            RGB_LED_Set_Color(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
            AlarmDataLock = Unlock;
            return;
        }
        else if (Other_Flag == AddFifo) // 直接添加在fifo
        {
            if (TimeControl[Alarm_ID].busy)
            {
                Set_AlarmControl.LastTime = 0;
                Queue_AddOne(&Alarm_FIFO[Alarm_ID], &Set_AlarmControl);
            }
            else
            {
                TimeControl[Alarm_ID] = Set_AlarmControl;
                RGB_LED_Set_Color(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
            }
            AlarmDataLock = Unlock;
            return;
        }
        else if (TimeControl[Alarm_ID].busy == CanNotBreak) // 当前正在运行的状态是不能打断的
        {
            if (RGB_Value_Compare(&TimeControl[Alarm_ID], &Set_AlarmControl))
            {
                TimeControl[Alarm_ID].CNT = CNT;
                // Debug("Alarm_ID: %d Sum CNT\r\n", Alarm_ID);
            }
            else
            {
                Set_AlarmControl.LastTime = 0;
                Queue_AddOne(&Alarm_FIFO[Alarm_ID], &Set_AlarmControl);
                // Debug("Alarm_ID: %d and fifo\r\n", Alarm_ID);
            }
            AlarmDataLock = Unlock;
            return;
        }

        // 到这里有两种情况：1 当前没有正在运行的状态 2 当前正在运行的状态是能打断的
        if (TimeControl[Alarm_ID].busy == need_recover) // 当前正在运行的状态是能打断的，但是需要保存，执行完优先级高的后再继续执行
        {
            TimeControl[Alarm_ID].LastTime = GetTimeInterval(TimeControl[Alarm_ID].LastTime, GetSysTick()); // 工作了多久
            Queue_AddOne(&Alarm_FIFO[Alarm_ID], &TimeControl[Alarm_ID]);
        }
#endif
        TimeControl[Alarm_ID] = Set_AlarmControl;

        RGB_LED_Set_Color(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);

        // RGB_Auto_Refresh_Color();
        AlarmDataLock = Unlock;
    }
}

#if 0
void Tone_Set_Control_Value(uint16_t Audio_Vol, uint32_t frequency, uint16_t ON_Time, uint16_t OFF_Time, uint16_t CNT)
{
#ifdef Alarm_FIFO_EN
    S_AlarmControl Set_AlarmControl;
#endif

    if (!Audio_Vol || !CNT)
    {
        return;
    }

    if (AlarmDataLock == Unlock)
    {
        AlarmDataLock = Lock;
        if (TimeControl[Audio_ID].busy)
        {
#ifdef Alarm_FIFO_EN
            Set_AlarmControl.LED_ID = Audio_Vol;
            Set_AlarmControl.LastTime = 0;
            Set_AlarmControl.ON_Color = frequency;
            Set_AlarmControl.OFF_Color = 0;
            Set_AlarmControl.ON_Time = ON_Time;
            Set_AlarmControl.OFF_Time = OFF_Time;
            Set_AlarmControl.Hold_Color = NULL;
            Set_AlarmControl.Hold_Time = NULL;
            Set_AlarmControl.CNT = CNT;
            Set_AlarmControl.state = 1;
            Set_AlarmControl.busy = 1;
            Set_AlarmControl.Fun = AudioToneControl;

            if (RGB_Value_Compare(&TimeControl[Audio_ID], &Set_AlarmControl))
            {
                // TimeControl[Audio_ID].CNT += CNT;
                TimeControl[Audio_ID].CNT = CNT;
                TimeControl[Audio_ID].ON_Time = ON_Time;
                TimeControl[Audio_ID].OFF_Time = ON_Time;
                // Debug("Audio_ID: %d Sum CNT\r\n", Audio_ID);
            }
            else
            {
                Queue_AddOne(&Alarm_FIFO[Audio_ID], &Set_AlarmControl);
                // Debug("Audio_ID: %d and fifo\r\n", Audio_ID);
            }
#endif
            AlarmDataLock = Unlock;
            return;
        }

        TimeControl[Audio_ID].LED_ID = Audio_Vol;
        TimeControl[Audio_ID].LastTime = GetSysTick();
        TimeControl[Audio_ID].ON_Color = frequency;
        TimeControl[Audio_ID].OFF_Color = NULL;Audio_ID
        TimeControl[Audio_ID].ON_Time = ON_Time;
        TimeControl[Audio_ID].OFF_Time = OFF_Time;
        TimeControl[Audio_ID].Hold_Color = NULL;
        TimeControl[Audio_ID].Hold_Time = NULL;
        TimeControl[Audio_ID].CNT = CNT;
        TimeControl[Audio_ID].state = 1;
        TimeControl[Audio_ID].busy = 1;
        TimeControl[Audio_ID].Fun = AudioToneControl;
        TimeControl[Audio_ID].Fun(TimeControl[Audio_ID].LED_ID, TimeControl[Audio_ID].ON_Color);
        AlarmDataLock = Unlock;
    }
}

uint8_t Audio_Is_Stop(void)
{
    if (TimeControl[Audio_ID].busy)
    {
        return 0;
    }
    return 1;
}

#endif

void LED_Stop_Control_Value(uint8_t Alarm_ID)
{
    if (Alarm_ID >= ALL_ID_NUM)
    {
        return;
    }

    if (!TimeControl[Alarm_ID].CNT)
    {
        return;
    }

    RGB_LED_Set_Color(Alarm_ID, 0);
    memset(&TimeControl[Alarm_ID], 0, sizeof(S_AlarmControl));

    __disable_irq();
#ifdef Alarm_FIFO_EN
    Queue_Init(&Alarm_FIFO[Alarm_ID], &Alarm_FIFO_BUFF[Alarm_ID][0], sizeof(S_AlarmControl), Alarm_FIFO_BUFF_SIZE);
#endif
    __enable_irq();

    // RGB_Manual_Refresh_Color();
}

void Alarm_Control_Update(void)
{
    uint8_t Alarm_ID;

    if (AlarmDataLock == Unlock)
    {
        AlarmDataLock = Lock;

        for (Alarm_ID = 0; Alarm_ID < ALL_ID_NUM; Alarm_ID++)
        {
            // __disable_irq();
            if (TimeControl[Alarm_ID].CNT)
            {
                if (TimeControl[Alarm_ID].state)
                {
                    if (GetTimeInterval(TimeControl[Alarm_ID].LastTime, GetSysTick()) >= TimeControl[Alarm_ID].ON_Time)
                    {
                        if (TimeControl[Alarm_ID].Fun != NULL)
                        {
                            TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].OFF_Color);
                        }

                        TimeControl[Alarm_ID].state = 0;
                        TimeControl[Alarm_ID].LastTime = GetSysTick();
                    }
                }
                else
                {
                    if (GetTimeInterval(TimeControl[Alarm_ID].LastTime, GetSysTick()) >= TimeControl[Alarm_ID].OFF_Time)
                    {
                        TimeControl[Alarm_ID].CNT--;
                        if (TimeControl[Alarm_ID].CNT)
                        {
                            if (TimeControl[Alarm_ID].Fun != NULL)
                            {
                                TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
                            }
                            TimeControl[Alarm_ID].LastTime = GetSysTick();
                            TimeControl[Alarm_ID].state = 1;
                        }
#ifdef Alarm_FIFO_EN
                        else if (!Queue_IsEmpty(&Alarm_FIFO[Alarm_ID]))
                        {
                            Queue_GetOne(&Alarm_FIFO[Alarm_ID], &TimeControl[Alarm_ID]);
                            if (GetSysTick() > TimeControl[Alarm_ID].LastTime)
                            {
                                TimeControl[Alarm_ID].LastTime = GetSysTick() - TimeControl[Alarm_ID].LastTime;
                            }
                            else
                            {
                                TimeControl[Alarm_ID].LastTime = 0xFFFFFFFF - TimeControl[Alarm_ID].LastTime + 1;
                            }

                            if (TimeControl[Alarm_ID].Fun != NULL)
                            {
                                if (TimeControl[Alarm_ID].state)
                                {
                                    TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].ON_Color);
                                }
                                else
                                {
                                    TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].OFF_Color);
                                }
                            }
                        }
#endif
                        else if (TimeControl[Alarm_ID].Hold_Time)
                        {
                            if (TimeControl[Alarm_ID].Fun != NULL)
                            {
                                TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].Hold_Color);
                            }
                            TimeControl[Alarm_ID].LastTime = GetSysTick();
                            TimeControl[Alarm_ID].OFF_Color = TimeControl[Alarm_ID].Hold_Color;
                            TimeControl[Alarm_ID].OFF_Time = TimeControl[Alarm_ID].Hold_Time;
                            TimeControl[Alarm_ID].busy = without_recover;
                            TimeControl[Alarm_ID].Hold_Color = 0;
                            TimeControl[Alarm_ID].Hold_Time = 0;
                            // TimeControl[Alarm_ID].state = 0;
                            TimeControl[Alarm_ID].CNT = 1;
                        }
                        else
                        {
                            // if (Audio_ID == Alarm_ID)
                            // {
                            //     TimeControl[Alarm_ID].Fun(0, 0);
                            // }
                            // else
                            // {
                            //     TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].Hold_Color);
                            // }
                            TimeControl[Alarm_ID].Fun(TimeControl[Alarm_ID].LED_ID, TimeControl[Alarm_ID].Hold_Color);
                            memset(&TimeControl[Alarm_ID], 0, sizeof(S_AlarmControl));
                        }
                    }
                }
            }
            // __enable_irq();
        }

        AlarmDataLock = Unlock;
    }
}

#ifdef Alarm_FIFO_EN

uint8_t RGB_Value_Compare(const S_AlarmControl *const TimeControl, const S_AlarmControl *const Set_AlarmControl)
{
    if (TimeControl->LED_ID != Set_AlarmControl->LED_ID)
        return 0;
    else if (TimeControl->ON_Color != Set_AlarmControl->ON_Color)
        return 0;
    else if (TimeControl->OFF_Color != Set_AlarmControl->OFF_Color)
        return 0;
    else if (TimeControl->ON_Time != Set_AlarmControl->ON_Time)
        return 0;
    else if (TimeControl->OFF_Time != Set_AlarmControl->OFF_Time)
        return 0;
    else if (TimeControl->Hold_Color != Set_AlarmControl->Hold_Color)
        return 0;
    else if (TimeControl->Hold_Time != Set_AlarmControl->Hold_Time)
        return 0;
    return 1;
}

void Alarm_FIFO_Init(void)
{
    uint8_t i;
    for (i = 0; i < ALL_ID_NUM; i++)
    {
        Queue_Init(&Alarm_FIFO[i], &Alarm_FIFO_BUFF[i][0], sizeof(S_AlarmControl), Alarm_FIFO_BUFF_SIZE);
    }
}

#endif

uint8_t RGB_Is_Extinguish(void)
{
    uint8_t i;

    for (i = 0; i < LED_ID_NUM; i++)
    {
        if (TimeControl[i].CNT)
        {
            return 0;
        }
    }

    if (i == LED_ID_NUM)
    {
        return 1;
    }
    return 0;
}

uint8_t RGB_CanNotBreak_Is_Stop_Flicker(void)
{
    uint8_t i;

    for (i = 0; i < LED_ID_NUM; i++)
    {
        if (TimeControl[i].busy == CanNotBreak)
        {
            return 0;
        }
    }

    if (i == LED_ID_NUM)
    {
        return 1;
    }
    return 0;
}

uint8_t RGB_Is_Stop_Flicker(void)
{
    uint8_t i;

    for (i = 0; i < LED_ID_NUM; i++)
    {
        if (TimeControl[i].busy)
        {
            return 0;
        }
    }

    if (i == LED_ID_NUM)
    {
        return 1;
    }
    return 0;
}
