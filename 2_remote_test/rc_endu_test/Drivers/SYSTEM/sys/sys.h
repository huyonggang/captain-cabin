#ifndef __SYS_H
#define __SYS_H

#include "apm32f4xx.h"
#include "apm32f4xx_gpio.h"
#include "apm32f4xx_rcm.h"
#include "apm32f4xx_eint.h"
#include "apm32f4xx_usart.h"
#include "apm32f4xx_misc.h"
#include "apm32f4xx_syscfg.h"
#include "apm32f4xx_dma.h"
#include "apm32f4Xx_sdio.h"
#include "apm32f4xx_dci.h"
#include "apm32f4xx_misc.h"
#include "apm32f4xx_tmr.h"
#include "apm32f4xx_dac.h"
#include "apm32f4xx_adc.h"
#include "apm32f4xx_spi.h"
#include "apm32f4xx_pmu.h"
#include "apm32f4xx_fmc.h"
#include "apm32f4xx_rtc.h"
#include "apm32f4xx_iwdt.h"

#include "my_debug.h"

/**
 * SYS_SUPPORT_OS用于定义是否支持OS
 * 0，不支持OS
 * 1，支持OS
 */
#define SYS_SUPPORT_OS 1

#define BYTE0(dwTemp) (*((uint8_t *)(&(dwTemp))))
#define BYTE1(dwTemp) (*((uint8_t *)(&(dwTemp)) + 1))
#define BYTE2(dwTemp) (*((uint8_t *)(&(dwTemp)) + 2))
#define BYTE3(dwTemp) (*((uint8_t *)(&(dwTemp)) + 3))

#define HALFWORD0(dwTemp) (*((uint16_t *)(&(dwTemp))))
#define HALFWORD1(dwTemp) (*((uint16_t *)(&(dwTemp)) + 1))

#define WORD(dwTemp) (*((uint32_t *)(&(dwTemp))))

// 位带操作,实现51类似的GPIO控制功能
// 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
// IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 20) // 0x40020014
#define GPIOB_ODR_Addr (GPIOB_BASE + 20) // 0x40020414
#define GPIOC_ODR_Addr (GPIOC_BASE + 20) // 0x40020814
#define GPIOD_ODR_Addr (GPIOD_BASE + 20) // 0x40020C14
#define GPIOE_ODR_Addr (GPIOE_BASE + 20) // 0x40021014
#define GPIOF_ODR_Addr (GPIOF_BASE + 20) // 0x40021414
#define GPIOG_ODR_Addr (GPIOG_BASE + 20) // 0x40021814
#define GPIOH_ODR_Addr (GPIOH_BASE + 20) // 0x40021C14
#define GPIOI_ODR_Addr (GPIOI_BASE + 20) // 0x40022014

#define GPIOA_IDR_Addr (GPIOA_BASE + 16) // 0x40020010
#define GPIOB_IDR_Addr (GPIOB_BASE + 16) // 0x40020410
#define GPIOC_IDR_Addr (GPIOC_BASE + 16) // 0x40020810
#define GPIOD_IDR_Addr (GPIOD_BASE + 16) // 0x40020C10
#define GPIOE_IDR_Addr (GPIOE_BASE + 16) // 0x40021010
#define GPIOF_IDR_Addr (GPIOF_BASE + 16) // 0x40021410
#define GPIOG_IDR_Addr (GPIOG_BASE + 16) // 0x40021810
#define GPIOH_IDR_Addr (GPIOH_BASE + 16) // 0x40021C10
#define GPIOI_IDR_Addr (GPIOI_BASE + 16) // 0x40022010

// IO口操作,只对单一的IO口!
// 确保n的值小于16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) // 输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  // 输入

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) // 输出
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  // 输入

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) // 输出
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  // 输入

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) // 输出
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  // 输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) // 输出
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  // 输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) // 输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // 输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) // 输出
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  // 输入

#define PHout(n) BIT_ADDR(GPIOH_ODR_Addr, n) // 输出
#define PHin(n) BIT_ADDR(GPIOH_IDR_Addr, n)  // 输入

#define PIout(n) BIT_ADDR(GPIOI_ODR_Addr, n) // 输出
#define PIin(n) BIT_ADDR(GPIOI_IDR_Addr, n)  // 输入

/* 函数声明 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);                       /* 设置中断向量表偏移地址 */
void sys_wfi_set(void);                                                                   /* 执行WFI指令(执行完该指令进入睡眠模式, 等待中断唤醒) */
void sys_intx_disable(void);                                                              /* 禁用除了NMI和Hard Fault之外的所有异常 */
void sys_intx_enable(void);                                                               /* 启用所有异常 */
void sys_msr_msp(uint32_t addr);                                                          /* 设置栈顶地址 */
void sys_standby(void);                                                                   /* 进入待机模式 */
void sys_soft_reset(void);                                                                /* 系统软复位 */
uint8_t sys_apm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq); /* 配置系统时钟 */

uint32_t xTaskGetTickCount(void);
uint32_t GetTimeInterval(uint32_t lastTime, uint32_t curTime);
void iwdt_init(uint8_t prer, uint32_t rlr);
void IWDG_Feed(void);

#endif
