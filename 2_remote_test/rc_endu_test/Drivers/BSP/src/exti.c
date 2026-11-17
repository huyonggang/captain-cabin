#include "exti.h"
#include "led.h"

void eint_init(void)
{
    GPIO_Config_T GPIO_configStruct;
    EINT_Config_T EINT_configStruct;

    /* Enable the BUTTON Clock */
    RCM_EnableAHB1PeriphClock(MY_GPIO_CLK);

    /* Configure Button pin as input floating */
    GPIO_ConfigStructInit(&GPIO_configStruct);
    GPIO_configStruct.mode = GPIO_MODE_IN;
    GPIO_configStruct.pin = MY_PIN;
    GPIO_configStruct.pupd = GPIO_PUPD_UP;
    GPIO_Config(MY_GPIO_PORT, &GPIO_configStruct);

    /* Enable the SYSCFG Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Connect Button EINT Line to Button GPIO Pin */
    SYSCFG_ConfigEINTLine(MY_EINT_PORT_SOURCE, MY_EINT_PIN_SOURCE);

    /* Configure Button EINT line */
    EINT_configStruct.line = MY_EINT_LINE;
    EINT_configStruct.mode = EINT_MODE_INTERRUPT;
    EINT_configStruct.trigger = EINT_TRIGGER_RISING;
    EINT_configStruct.lineCmd = ENABLE;
    EINT_Config(&EINT_configStruct);

    /* Enable and set Button EINT Interrupt to the lowest priority */
    NVIC_EnableIRQRequest(MY_EINT_IRQn, 15, 0x00);
}

void GPIO_INT_Enable(GPIO_T *GPIOx, uint16_t GPIO_Pinx, EINT_TRIGGER_T trigger, uint8_t Enable)
{
    GPIO_Config_T GPIO_configStruct;
    EINT_Config_T EINT_configStruct;
    uint8_t syscfg_port;
    uint8_t i;

    /* Enable the BUTTON Clock */
    RCM_EnableAHB1PeriphClock(Get_GPIO_RCC(GPIOx));

    /* Configure Button pin as input floating */
    GPIO_ConfigStructInit(&GPIO_configStruct);
    GPIO_configStruct.mode = GPIO_MODE_IN;
    GPIO_configStruct.pin = GPIO_Pinx;

    // if (trigger == EINT_TRIGGER_RISING)
    // {
    //     GPIO_configStruct.pupd = GPIO_PUPD_DOWN;
    // }
    // else if (trigger == EINT_TRIGGER_FALLING)
    // {
    //     GPIO_configStruct.pupd = GPIO_PUPD_UP;
    // }
    // else
    // {
    //     GPIO_configStruct.pupd = GPIO_PUPD_UP;
    // }
    GPIO_Config(GPIOx, &GPIO_configStruct);

    /* Enable the SYSCFG Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    syscfg_port = ((uint32_t)GPIOx - AHB1PERIPH_BASE) / 0x400;
    // Debug("SYSCFG_PORT_T: %d\r\n", syscfg_port);

    for (i = 0; i < 16; i++)
    {
        if (!(GPIO_Pinx >> i))
        {
            break;
        }
    }
    // Debug("SYSCFG_PIN_T: %d\r\n", i - 1);
    SYSCFG_ConfigEINTLine((SYSCFG_PORT_T)syscfg_port, (SYSCFG_PIN_T)(i - 1));

    EINT_configStruct.line = (EINT_LINE_T)GPIO_Pinx;
    EINT_configStruct.mode = EINT_MODE_INTERRUPT;
    EINT_configStruct.trigger = trigger;
    EINT_configStruct.lineCmd = Enable;
    EINT_Config(&EINT_configStruct);
}

void INT_Enable(EINT_LINE_T Set_EINT_LINE, uint8_t Enable)
{
    if (Enable != DISABLE)
    {
        *(__IOM uint32_t *)EINT_BASE |= Set_EINT_LINE;
    }
    else
    {
        *(__IOM uint32_t *)EINT_BASE &= ~Set_EINT_LINE;
    }
}
