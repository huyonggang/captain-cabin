#include "delay.h"
#include "main.h"

// 如果使用OS,则包括下面的头文件即可

#if SYS_SUPPORT_OS
#include "FreeRTOS.h" //FreeRTOS使用
#include "task.h"
#endif

/* 微秒级延时倍乘数 */
static uint32_t g_fac_us = 0;

#if (SYS_SUPPORT_OS != 0)

/* 毫秒级延时倍乘数 */
static uint16_t g_fac_ms = 0;

uint32_t SystemTick = 0;

extern void xPortSysTickHandler(void);

// systick中断服务函数,使用OS时用到
void SysTick_Handler(void)
{
	SystemTick++;

	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
	{
		xPortSysTickHandler();
	}
}

#endif

/**
 * @brief       初始化延时功
 * @param       无
 * @retval      无
 */
void delay_init(void)
{
	SystemCoreClock = RCM_ReadSYSCLKFreq();
	SysTick->CTRL = 0;
	SysTick_ConfigCLKSource(SYSTICK_CLK_SOURCE_HCLK); /* 配置SysTick时钟源 */
	g_fac_us = SystemCoreClock / 1000000;			  /* 延时单位微秒需要的时钟节拍数 */

#if (SYS_SUPPORT_OS != 0)
	g_fac_ms = 1000 / configTICK_RATE_HZ; /* 一个系统时钟节拍耗时毫秒数 */

	if (SysTick_Config(SystemCoreClock / configTICK_RATE_HZ))
	{
		/* Capture error */
		while (1)
		{
		}
	}
#endif
}

#if (SYS_SUPPORT_OS != 0)

// 延时nus
// nus:要延时的us数.
// nus:0~204522252(最大值即2^32/fac_us@fac_us=168)

void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t reload;
	uint32_t told;
	uint32_t tnow;
	uint32_t tcnt = 0;

	ticks = nus * g_fac_us; /* 计算需要延时的SysTick节拍数 */
	reload = SysTick->LOAD; /* 获取SysTick的重装载值 */
	told = SysTick->VAL;	/* 获取开始延时时的SysTick计数值 */

	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
			{
				tcnt += told - tnow; /* 需注意SysTick是一个递减计数器 */
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				break;
			}
		}
	}
}

// 延时nms
// nms:要延时的ms数
// nms:0~65535
void delay_ms(uint32_t nms)
{
	if (!nms)
	{
		return;
	}

	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
	{
		if (nms >= g_fac_ms) // 延时的时间大于OS的最少时间周期
		{
			vTaskDelay(nms / g_fac_ms); // FreeRTOS延时
		}
		nms %= g_fac_ms; // OS已经无法提供这么小的延时了,采用普通方式延时
	}
	delay_us((uint32_t)(nms * 1000)); // 普通方式延时
}

// 延时nms,不会引起任务调度
// nms:要延时的ms数
void delay_xms(uint32_t nms)
{
	uint32_t i;
	for (i = 0; i < nms; i++)
		delay_us(1000);
}

#else

/**
 * @brief       微秒级延时
 * @param       nus: 延时的微秒数，范围：0~((2^24)/g_fac_us)
 * @retval      无
 */
void delay_us(uint32_t nus)
{
	uint32_t temp;

	if (nus == 0) /* 延时时间为0，则不进行延时 */
	{
		return;
	}

	SysTick->LOAD = (nus * g_fac_us) - 1;	  /* 根据需要的延时时间设置SysTick装载值 */
	SysTick->VAL = 0;						  /* 清空SysTick计数值 */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; /* 开启SysTick */
	do
	{ /* 等待时间到达 */
		temp = SysTick->CTRL;
	} while (((temp & SysTick_CTRL_ENABLE_Msk) != 0) && ((temp & SysTick_CTRL_COUNTFLAG_Msk) == 0));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; /* 关闭SysTick */
	SysTick->VAL = 0;						   /* 清空SysTick计数值 */
}

/**
 * @brief       毫秒级延时
 * @param       nms: 延时的毫秒数，范围：0~(2^16 - 1)
 * @retval      无
 */
void delay_ms(uint32_t nms)
{
	uint32_t repeat;
	uint32_t remain;

	repeat = nms / 30; /* delay_us单次最大延时时间有限，因此分多次进行延时
						* 这里用30，是考虑到可能有超频应用
						*/
	remain = nms % 30;

	while (repeat != 0) /* 分repeat次进行30000us的延时 */
	{
		delay_us(30 * 1000);
		repeat--;
	}

	if (remain != 0) /* 用delay_us进行剩余时间的延时时间 */
	{
		delay_us(remain * 1000);
	}
}

#endif
