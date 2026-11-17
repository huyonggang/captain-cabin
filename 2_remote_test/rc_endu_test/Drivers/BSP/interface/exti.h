#ifndef _exti_h
#define _exti_h

#include "sys.h"

#define MY_PIN GPIO_PIN_2
#define MY_GPIO_PORT GPIOC
#define MY_GPIO_CLK RCM_AHB1_PERIPH_GPIOC
#define MY_EINT_LINE EINT_LINE_2
#define MY_EINT_PORT_SOURCE SYSCFG_PORT_GPIOC
#define MY_EINT_PIN_SOURCE SYSCFG_PIN_2
#define MY_EINT_IRQn EINT2_IRQn

void eint_init(void);
void GPIO_INT_Enable(GPIO_T *GPIOx, uint16_t GPIO_Pinx, EINT_TRIGGER_T trigger, uint8_t Enable);
void INT_Enable(EINT_LINE_T Set_EINT_LINE, uint8_t Enable);

#endif
