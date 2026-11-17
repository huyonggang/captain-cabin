#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"

extern uint32_t SystemTick;

#define GetSysTick() SystemTick

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
void delay_xms(uint32_t nms);

#endif
