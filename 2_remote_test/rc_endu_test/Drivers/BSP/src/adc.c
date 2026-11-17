#include "adc.h"

#define ADC_SAMPLE_NUM 20
#define ADC_Channel_NUM 4

static uint16_t g_adc_dma_buf[ADC_Channel_NUM * ADC_SAMPLE_NUM]; /* ADC DMA缓冲区 */

/* DMA传输完成标志 */
// uint8_t g_adc_dma_sta = 0;

/**
 * @brief       使能一次DMA传输ADC数据
 * @param       ndtr: DMA传输的数据量
 * @retval      无
 */
void adc_dma_enable(uint16_t ndtr)
{
	ADC_Disable(ADC_ADCX);		 /* 禁用ADC */
	DMA_Disable(ADC_ADCX_DMASx); /* 禁止DMA数据流 */
	while (DMA_ReadCmdStatus(ADC_ADCX_DMASx) != DISABLE)
	{
		/* 等待DMA可配置 */
	}
	DMA_ConfigDataNumber(ADC_ADCX_DMASx, ndtr); /* 配置DMA数据流传输的数据项数目 */
	DMA_Enable(ADC_ADCX_DMASx);					/* 使能DMA数据流 */
	ADC_Enable(ADC_ADCX);						/* 使能ADC */
	ADC_SoftwareStartConv(ADC_ADCX);			/* 启动ADC转换规则通道 */
}

/**
 * @brief       初始化ADC多通道和DMA
 *  @note       本函数配置ADC为12位分辨率，时钟频率ADCCLK为21MHz，
 *              ADC转换时间TCONV=采样周期+12个周期
 *              例如使用最大采样周期480个周期，则ADC的转换时间为492个ADC时钟周期，即约为23.43微秒
 * @param       mar: 存储器0地址
 * @retval      无
 */
void adc_dma_init(uint32_t mar)
{
	GPIO_Config_T gpio_init_struct;
	ADC_Config_T adc_init_struct;
	ADC_CommonConfig_T adc_comm_init_struct;
	DMA_Config_T dma_init_struct;

	/* 使能时钟 */
	ADC_ADCX_CHY_CLK_ENABLE();						  /* 使能ADC时钟 */
	RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA); /* 使能ADC1通道1/2/3/4/5/6/7输入引脚端口时钟 */
	RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC); /* 使能ADC1通道1/2/3/4/5/6/7输入引脚端口时钟 */

	if ((uint32_t)ADC_ADCX_DMASx > (uint32_t)DMA2)
	{
		RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_DMA2); /* 使能DMA2时钟 */
	}
	else
	{
		RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_DMA1); /* 使能DMA1时钟 */
	}

	/* 配置ADC1通道1/2/3/4/5/6/7输入引脚 */
	gpio_init_struct.pin = GPIO_PIN_0;		  /* ADC1通道输入引脚 */
	gpio_init_struct.mode = GPIO_MODE_AN;	  /* 模拟模式 */
	gpio_init_struct.pupd = GPIO_PUPD_NOPULL; /* 禁止上拉/下拉 */
	GPIO_Config(GPIOC, &gpio_init_struct);	  /* 配置ADC1通道1/2/3/4/5/6/7输入引脚 */
	gpio_init_struct.pin = GPIO_PIN_1;		  /* ADC1通道输入引脚 */
	GPIO_Config(GPIOA, &gpio_init_struct);	  /* 配置ADC1通道1/2/3/4/5/6/7输入引脚 */
	gpio_init_struct.pin = GPIO_PIN_2;		  /* ADC1通道输入引脚 */
	GPIO_Config(GPIOA, &gpio_init_struct);	  /* 配置ADC1通道1/2/3/4/5/6/7输入引脚 */

	/* 配置ADC通用控制寄存器 */
	adc_comm_init_struct.mode = ADC_MODE_INDEPENDENT;			 /* 独立模式 */
	adc_comm_init_struct.prescaler = ADC_PRESCALER_DIV4;		 /* ADC预分频器 */
	adc_comm_init_struct.accessMode = ADC_ACCESS_MODE_DISABLED;	 /* 禁止DMA模式 */
	adc_comm_init_struct.twoSampling = ADC_TWO_SAMPLING_5CYCLES; /* 2个采样阶段之间的延迟 */
	ADC_CommonConfig(&adc_comm_init_struct);					 /* 配置ADC通用控制寄存器 */

	/* 配置ADC */
	adc_init_struct.resolution = ADC_RESOLUTION_12BIT;	  /* 分辨率 */
	adc_init_struct.scanConvMode = ENABLE;				  /* 使能扫描模式 */
	adc_init_struct.continuousConvMode = ENABLE;		  /* 使能连续转换模式 */
	adc_init_struct.extTrigEdge = ADC_EXT_TRIG_EDGE_NONE; /* 禁止触发检测 */
	adc_init_struct.dataAlign = ADC_DATA_ALIGN_RIGHT;	  /* 配置数据对齐方式 */
	adc_init_struct.nbrOfChannel = ADC_Channel_NUM;		  /* 规则通道序列长度 */
	ADC_Config(ADC_ADCX, &adc_init_struct);				  /* 配置ADC */
	ADC_EnableDMA(ADC_ADCX);							  /* 使能DMA模式 */
	ADC_EnableDMARequest(ADC_ADCX);						  /* 使能ADC发出DMA请求 */
	ADC_EnableTempSensorVrefint();

	/* 配置ADC通道 */
	ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_10, 1, ADC_SAMPLETIME_56CYCLES); /* 配置ADC1规则通道1 */
	ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_1, 2, ADC_SAMPLETIME_56CYCLES);	/* 配置ADC1规则通道2 */
	ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_2, 3, ADC_SAMPLETIME_56CYCLES);	/* 配置ADC1规则通道3 */
	ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_17, 4, ADC_SAMPLETIME_56CYCLES); /* 配置ADC1规则通道3 */

	// ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_4, 4, ADC_SAMPLETIME_480CYCLES); /* 配置ADC1规则通道4 */
	// ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_5, 5, ADC_SAMPLETIME_480CYCLES); /* 配置ADC1规则通道5 */
	// ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_6, 6, ADC_SAMPLETIME_480CYCLES); /* 配置ADC1规则通道6 */
	// ADC_ConfigRegularChannel(ADC_ADCX, ADC_CHANNEL_7, 7, ADC_SAMPLETIME_480CYCLES); /* 配置ADC1规则通道7 */

	/* 复位DMA */
	DMA_Reset(ADC_ADCX_DMASx); /* 复位DMA */
	while (DMA_ReadCmdStatus(ADC_ADCX_DMASx) != DISABLE)
	{
		/* 等待DMA可配置 */
	}

	/* 配置DMA */
	dma_init_struct.channel = ADC_ADCX_DMASx_Chanel;						/* 通道 */
	dma_init_struct.peripheralBaseAddr = (uint32_t)&ADC_ADCX->REGDATA;		/* 外设地址 */
	dma_init_struct.memoryBaseAddr = mar;									/* 存储器0地址 */
	dma_init_struct.dir = DMA_DIR_PERIPHERALTOMEMORY;						/* 数据传输方向 */
	dma_init_struct.bufferSize = 0;											/* 传输的数据项数目 */
	dma_init_struct.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;				/* 外设增量模式 */
	dma_init_struct.memoryInc = DMA_MEMORY_INC_ENABLE;						/* 存储器递增模式 */
	dma_init_struct.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_HALFWORD; /* 外设数据大小 */
	dma_init_struct.memoryDataSize = DMA_MEMORY_DATA_SIZE_HALFWORD;			/* 存储器数据大小 */
	dma_init_struct.loopMode = DMA_MODE_CIRCULAR;							/* 循环模式 */
	dma_init_struct.priority = DMA_PRIORITY_LOW;							/* 优先级 */
	dma_init_struct.fifoMode = DMA_FIFOMODE_DISABLE;						/* 直接模式 */
	dma_init_struct.fifoThreshold = DMA_FIFOTHRESHOLD_FULL;					/* FIFO阈值 */
	dma_init_struct.memoryBurst = DMA_MEMORYBURST_SINGLE;					/* 存储器突发传输 */
	dma_init_struct.peripheralBurst = DMA_PERIPHERALBURST_SINGLE;			/* 外设突发传输 */
	DMA_Config(ADC_ADCX_DMASx, &dma_init_struct);							/* 配置DMA */

	/* 配置DMA中断 */
	// ADC_ADCX_DMASx_CLR_TC(); /* 清除DMA数据流传输完成中断标志 */
	// NVIC_EnableIRQRequest(ADC_ADCX_DMASx_IRQn, 14, 0);	 /* 配置DMA中断 */
	// DMA_EnableInterrupt(ADC_ADCX_DMASx, DMA_INT_TCIFLG); /* 使能DMA数据流传输完成中断 */
}

void Adc_Init(void)
{
	adc_dma_init((uint32_t)g_adc_dma_buf);			  /* 初始化ADC多通道和DMA */
	adc_dma_enable(ADC_Channel_NUM * ADC_SAMPLE_NUM); /* 使能一次DMA传输ADC数据 */
}

// ADC均值滤波
void ADC_Filter(uint16_t *adc_val)
{
	uint16_t i = 0;
	uint32_t sum[ADC_Channel_NUM] = {0, 0, 0};

	for (; i < ADC_SAMPLE_NUM; i++)
	{
		sum[0] += g_adc_dma_buf[ADC_Channel_NUM * i + 0];
		sum[1] += g_adc_dma_buf[ADC_Channel_NUM * i + 1];
		sum[2] += g_adc_dma_buf[ADC_Channel_NUM * i + 2];
		sum[3] += g_adc_dma_buf[ADC_Channel_NUM * i + 3];
		// sum[4] += adc_value[ADC_Channel_NUM * i + 4];
	}
	adc_val[0] = sum[0] / ADC_SAMPLE_NUM;
	adc_val[1] = sum[1] / ADC_SAMPLE_NUM;
	adc_val[2] = sum[2] / ADC_SAMPLE_NUM;
	adc_val[3] = sum[3] / ADC_SAMPLE_NUM;
	// adc_val[4]=sum[4]/ADC_SAMPLE_NUM;
}

uint16_t getAdcValue(uint8_t axis)
{
	uint32_t sum = 0;

	for (uint8_t i = 0; i < ADC_SAMPLE_NUM; i++)
	{
		sum += g_adc_dma_buf[ADC_Channel_NUM * i + axis];
	}
	return sum / ADC_SAMPLE_NUM;
}
