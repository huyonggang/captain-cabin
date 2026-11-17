/*!
 * @file        apm32f4xx_int.c
 *
 * @brief       Main Interrupt Service Routines
 *
 * @version     V1.0.3
 *
 * @date        2023-07-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "main.h"

extern TaskHandle_t KEYTask_Handler;

void Hard_Fault_Handler(uint32_t stack[]);

/** @addtogroup Examples
  @{
  */

/** @addtogroup EINT_Config
  @{
  */

/** @defgroup EINT_Config_INT_Functions INT_Functions
  @{
*/

/*!
 * @brief   This function handles NMI exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
void NMI_Handler(void)
{
}

void HardFault_Handler_C(unsigned int *hardfault_args)
{
    IWDG_Feed();

    HardFaultMsgSave.bus_fault_address = SCB->BFAR;
    HardFaultMsgSave.memmanage_fault_address = SCB->MMFAR;
    HardFaultMsgSave.stacked_r0 = ((unsigned long)hardfault_args[0]);
    HardFaultMsgSave.stacked_r1 = ((unsigned long)hardfault_args[1]);
    HardFaultMsgSave.stacked_r2 = ((unsigned long)hardfault_args[2]);
    HardFaultMsgSave.stacked_r3 = ((unsigned long)hardfault_args[3]);
    HardFaultMsgSave.stacked_r12 = ((unsigned long)hardfault_args[4]);
    HardFaultMsgSave.stacked_lr = ((unsigned long)hardfault_args[5]);
    HardFaultMsgSave.stacked_pc = ((unsigned long)hardfault_args[6]);
    HardFaultMsgSave.stacked_psr = ((unsigned long)hardfault_args[7]);
    Save_User_Data();
    mavlink_msg_send_to_app(HardFaultMsg_Msg_ID, (void *)&HardFaultMsgSave, sizeof(HardFaultMsgSave));

    Debug("bus_fault_address: 0x%08x", HardFaultMsgSave.bus_fault_address);
    Debug("memmanage_fault_address: 0x%08x", HardFaultMsgSave.memmanage_fault_address);
    Debug("cfsr: 0x%08x", HardFaultMsgSave.cfsr);
    Debug("R0 = 0x%08x", HardFaultMsgSave.stacked_r0);
    Debug("R1 = 0x%08x", HardFaultMsgSave.stacked_r1);
    Debug("R2 = 0x%08x", HardFaultMsgSave.stacked_r2);
    Debug("R3 = 0x%08x", HardFaultMsgSave.stacked_r2);
    Debug("R12 = 0x%08x", HardFaultMsgSave.stacked_r12);
    Debug("LR = 0x%08x", HardFaultMsgSave.stacked_lr);
    Debug("PC = 0x%08x", HardFaultMsgSave.stacked_pc);
    Debug("PSR = 0x%08x", HardFaultMsgSave.stacked_psr);

    Debug("BFAR = %x\r\n", (*((volatile unsigned long *)(0xE000ED38))));
    Debug("CFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED28))));
    Debug("HFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED2C))));
    Debug("DFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED30))));
    Debug("AFSR = %x\r\n", (*((volatile unsigned long *)(0xE000ED3C))));
    Debug("SCB_SHCSR = %x\r\n", SCB->SHCSR);

    while (1)
    {
    }
}

__ASM void HardFault_Handler(void)
{
    TST lr, #4;
    ITE EQ;
    MRSEQ r0, MSP;
    MRSNE r0, PSP;
    IMPORT HardFault_Handler_C;
    B HardFault_Handler_C;
}

/*!
 * @brief   This function handles Memory Manage exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles Bus Fault exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles Usage Fault exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/*!
 * @brief   This function handles SVCall exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
// void SVC_Handler(void)
// {
// }

/*!
 * @brief   This function handles Debug Monitor exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
void DebugMon_Handler(void)
{
}

/*!
 * @brief   This function handles PendSV_Handler exception
 *
 * @param   None
 *
 * @retval  None
 *
 */
// void PendSV_Handler(void)
// {
// }

/*!
 * @brief   This function handles SysTick Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
// void SysTick_Handler(void)
// {
// }

/*!
 * @brief   This function handles External line 0 Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
void EINT0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (EINT_ReadIntFlag(EINT_LINE_0))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_0);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PA0 int irq\r\n");
        }
    }
}

/*!
 * @brief   This function handles External lines 1 Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
void EINT1_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (EINT_ReadIntFlag(EINT_LINE_1))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_1);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PC1 int irq\r\n");
        }
    }
}

/*!
 * @brief   This function handles External lines 2 Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
void EINT2_IRQHandler(void)
{
}

void EINT3_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (EINT_ReadIntFlag(EINT_LINE_3))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_3);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PB3 int irq\r\n");
        }
    }
}

void EINT4_IRQHandler(void)
{
}

void EINT9_5_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (EINT_ReadIntFlag(EINT_LINE_9))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_9);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PB9 int irq\r\n");
        }
    }

    if (EINT_ReadIntFlag(EINT_LINE_5))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_5);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PC5 int irq\r\n");
        }
    }
    EINT_ClearIntFlag(EINT_LINE_5);
}

void EINT15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (EINT_ReadIntFlag(EINT_LINE_7))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_4);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PC7 int irq\r\n");
        }
    }

    if (EINT_ReadIntFlag(EINT_LINE_12))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_12);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PB12 int irq\r\n");
        }
    }

    if (EINT_ReadIntFlag(EINT_LINE_13))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_13);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PC13 int irq\r\n");
        }
    }

    if (EINT_ReadIntFlag(EINT_LINE_14))
    {
        /*Clear EINT_LINE2 interrupt flag*/
        EINT_ClearIntFlag(EINT_LINE_14);
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
        {
            vTaskNotifyGiveFromISR(KEYTask_Handler, &xHigherPriorityTaskWoken);
            /* 如果为 pdTRUE，则进行一次上下文切换 */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            Debug("PC14 int irq\r\n");
        }
    }

    if (EINT_ReadIntFlag(EINT_LINE_15))
    {
        EINT_ClearIntFlag(EINT_LINE_15);

        static uint32_t startTime;
        static uint16_t pairFailCnt = 0;
        uint32_t delta;

        if (RF_Pair_Pin_Read)
        {
            delta = xTaskGetTickCount() - startTime;
            Debug("delta: %d\n", delta);
            if (delta > 210 && delta < 280)
            {
                pairFailCnt = 0;
                if (globeState.PairSta != pairing)
                {
                    globeState.PairSta = pairing;
                }
                Debug("pairing\r\n");
            }
            else if (delta > 40 && delta < 60)
            {
                if (globeState.PairSta)
                {
                    pairFailCnt++;
                    if (pairFailCnt > 100)
                    {
                        globeState.PairSta = pairFail;
                        Debug("pairFail\r\n");
                    }
                }
            }
        }
        else
        {
            startTime = xTaskGetTickCount();
        }
    }
}

void DMA1_STR5_IRQHandler(void)
{
}

/**@} end of group EINT_Config_INT_Functions */
/**@} end of group EINT_Config */
/**@} end of group Examples */
