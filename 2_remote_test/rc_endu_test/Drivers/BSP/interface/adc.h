#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define ADC_BAT 0
#define ADC_PITCH 1
#define ADC_ROLL 2
#define ADC_REF 3

/* 多通道ADC采集（DMA读取）定义 */
#define ADC_ADCX ADC1
#define ADC_ADCX_CHY_CLK_ENABLE()                        \
    do                                                   \
    {                                                    \
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC1); \
    } while (0)

#define ADC_ADCX_DMASx DMA2_Stream0
#define ADC_ADCX_DMASx_Chanel DMA_CHANNEL_0
#define ADC_ADCX_DMASx_IRQn DMA2_STR0_IRQn
#define ADC_ADCX_DMASx_IRQHandler DMA2_STR0_IRQHandler
#define ADC_ADCX_DMASx_IS_TC() DMA_ReadIntFlag(ADC_ADCX_DMASx, DMA_INT_TCIFLG0)
#define ADC_ADCX_DMASx_CLR_TC()                            \
    do                                                     \
    {                                                      \
        DMA_ClearIntFlag(ADC_ADCX_DMASx, DMA_INT_TCIFLG0); \
    } while (0)

/* 函数声明 */

#define LOWPOWER_LOW_LIMIT 3.30f                 // 3.3V
#define LOWPOWER_HIGH_LIMIT 3.60f                // 3.6V
#define LowPower_OFF 3.00f                       // 3.0V
#define SamplingRes (200.0f / (100.0f + 200.0f)) //

// 初始化ADC，使用DMA传输
void Adc_Init(void);
void ADC_Filter(uint16_t *adc_val); // ADC均值滤波
uint16_t getAdcValue(uint8_t axis);

#endif
