#include "spi.h"

/**
 * @brief       初始化SPI1
 * @param       无
 * @retval      无
 */
void spi1_init(void)
{
    GPIO_Config_T gpio_init_struct;
    SPI_Config_T spi_init_struct;

    /* 使能时钟 */
    SPI1_SPI_CLK_ENABLE();       /* 使能SPI1时钟 */
    SPI1_SCK_GPIO_CLK_ENABLE();  /* 使能SPI1 SCK引脚端口时钟 */
    SPI1_MISO_GPIO_CLK_ENABLE(); /* 使能SPI1 MISO引脚端口时钟 */
    SPI1_MOSI_GPIO_CLK_ENABLE(); /* 使能SPI1 MOSI引脚端口时钟 */

    /* 配置SPI1 SCK引脚 */
    GPIO_ConfigPinAF(SPI1_SCK_GPIO_PORT, SPI1_SCK_GPIO_PIN_SOURCE, SPI1_SCK_GPIO_AF); /* 配置SPI1 SCK引脚复用功能 */
    gpio_init_struct.pin = SPI1_SCK_GPIO_PIN;                                         /* SPI1 SCK引脚 */
    gpio_init_struct.mode = GPIO_MODE_AF;                                             /* 复用功能模式 */
    gpio_init_struct.speed = GPIO_SPEED_100MHz;                                       /* 高速 */
    gpio_init_struct.otype = GPIO_OTYPE_PP;                                           /* 推挽输出 */
    gpio_init_struct.pupd = GPIO_PUPD_NOPULL;                                         /* 禁止上拉/下拉 */
    GPIO_Config(SPI1_SCK_GPIO_PORT, &gpio_init_struct);                               /* 配置SPI1 SCK引脚 */

    // /* 配置SPI1 MISO引脚 */
    // GPIO_ConfigPinAF(SPI1_MISO_GPIO_PORT, SPI1_MISO_GPIO_PIN_SOURCE, SPI1_MISO_GPIO_AF);    /* 配置SPI1 MISO引脚复用功能 */
    // gpio_init_struct.pin = SPI1_MISO_GPIO_PIN;                                              /* SPI1 MISO引脚 */
    // gpio_init_struct.mode = GPIO_MODE_AF;                                                   /* 复用功能模式 */
    // gpio_init_struct.speed = GPIO_SPEED_100MHz;                                             /* 高速 */
    // gpio_init_struct.otype = GPIO_OTYPE_PP;                                                 /* 推挽输出 */
    // gpio_init_struct.pupd = GPIO_PUPD_NOPULL;                                               /* 禁止上拉/下拉 */
    // GPIO_Config(SPI1_MISO_GPIO_PORT, &gpio_init_struct);                                    /* 配置SPI1 MISO引脚 */

    /* 配置SPI1 MOSI引脚 */
    GPIO_ConfigPinAF(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_GPIO_PIN_SOURCE, SPI1_MOSI_GPIO_AF); /* 配置SPI1 MOSI引脚复用功能 */
    gpio_init_struct.pin = SPI1_MOSI_GPIO_PIN;                                           /* SPI1 MOSI引脚 */
    gpio_init_struct.mode = GPIO_MODE_AF;                                                /* 复用功能模式 */
    gpio_init_struct.speed = GPIO_SPEED_100MHz;                                          /* 高速 */
    gpio_init_struct.otype = GPIO_OTYPE_PP;                                              /* 推挽输出 */
    gpio_init_struct.pupd = GPIO_PUPD_NOPULL;                                            /* 禁止上拉/下拉 */
    GPIO_Config(SPI1_MOSI_GPIO_PORT, &gpio_init_struct);                                 /* 配置SPI1 MOSI引脚 */

    /* 配置SPI1 */
    spi_init_struct.mode = SPI_MODE_MASTER;             /* 主模式 */
    spi_init_struct.length = SPI_DATA_LENGTH_8B;        /* 8位数据帧格式 */
    spi_init_struct.phase = SPI_CLKPHA_2EDGE;           /* 在第2个时钟边沿采样 */
    spi_init_struct.polarity = SPI_CLKPOL_HIGH;         /* SPI处于空闲状态时，SCK保持高电平状态 */
    spi_init_struct.nss = SPI_NSS_SOFT;                 /* 启用软件NSS模式 */
    spi_init_struct.firstBit = SPI_FIRSTBIT_MSB;        /* 先发送最高有效位（MSB） */
    spi_init_struct.direction = SPI_DIRECTION_1LINE_TX; /* 双线单向、同时发送和接收 */
    spi_init_struct.baudrateDiv = SPI_BAUDRATE_DIV_2;   /* 波特率分频系数 */
    spi_init_struct.crcPolynomial = 7;                  /* CRC多项式数值 */
    SPI_Config(SPI1_SPI, &spi_init_struct);             /* 配置SPI1 */
    SPI_Enable(SPI1_SPI);                               /* 使能SPI1 */

    DMA_Config_T dma_init_struct;
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_DMA2); /* 使能DMA2时钟 */
    /* 复位DMA */
    DMA_Reset(DMA2_Stream3); /* 复位DMA */
    while (DMA_ReadCmdStatus(DMA2_Stream3) != DISABLE)
    {
        /* 等待DMA可配置 */
    }
    /* 配置DMA */
    dma_init_struct.channel = (DMA_CHANNEL_T)DMA_CHANNEL_3;             /* 通道 */
    dma_init_struct.peripheralBaseAddr = (uint32_t)(&SPI1->DATA);       /* 外设地址 */
    dma_init_struct.memoryBaseAddr = NULL;                              /* 存储器0地址 */
    dma_init_struct.dir = DMA_DIR_MEMORYTOPERIPHERAL;                   /* 数据传输方向 */
    dma_init_struct.bufferSize = 0;                                     /* 传输的数据项数目 */
    dma_init_struct.peripheralInc = DMA_PERIPHERAL_INC_DISABLE;         /* 外设增量模式 */
    dma_init_struct.memoryInc = DMA_MEMORY_INC_ENABLE;                  /* 存储器递增模式 */
    dma_init_struct.peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_BYTE; /* 外设数据大小 */
    dma_init_struct.memoryDataSize = DMA_MEMORY_DATA_SIZE_BYTE;         /* 存储器数据大小 */
    dma_init_struct.loopMode = DMA_MODE_NORMAL;                         /* 循环模式 */
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;                     /* 优先级 */
    dma_init_struct.fifoMode = DMA_FIFOMODE_DISABLE;                    /* 直接模式 */
    dma_init_struct.fifoThreshold = DMA_FIFOTHRESHOLD_FULL;             /* FIFO阈值 */
    dma_init_struct.memoryBurst = DMA_MEMORYBURST_SINGLE;               /* 存储器突发传输 */
    dma_init_struct.peripheralBurst = DMA_PERIPHERALBURST_SINGLE;       /* 外设突发传输 */
    DMA_Config(DMA2_Stream3, &dma_init_struct);                         /* 配置DMA */
}

/**
 * @brief       设置SPI1速度
 * @note        SPI1的时钟来自PCLK2，即84MHz
 *              SPI1速度 = PCLK2 / (2^(speed + 1))
 * @param       speed: 波特率分频系数，范围：0~7
 * @retval      无
 */
void spi1_set_speed(uint8_t speed)
{
    if (speed > 7) /* 检查参数合法性 */
    {
        return;
    }

    SPI_Disable(SPI1_SPI);           /* 禁用SPI后，才能修改波特率分频系数 */
    SPI1_SPI->CTRL1_B.BRSEL = speed; /* 设置SPI1波特率分频系数 */
    SPI_Enable(SPI1_SPI);            /* 重新使能SPI */
}

/**
 * @brief       SPI1读写一个字节数据
 * @param       txdata: 待发送的一字节数据
 * @retval      接收到的一字节数据
 */
uint8_t spi1_read_write_byte(uint8_t txdata)
{
    uint8_t rxdata;

    while (SPI_I2S_ReadStatusFlag(SPI1_SPI, SPI_FLAG_TXBE) != SET)
        ;                             /* 等待发送缓冲器为空 */
    SPI_I2S_TxData(SPI1_SPI, txdata); /* 发送一字节数据 */

    while (SPI_I2S_ReadStatusFlag(SPI1_SPI, SPI_FLAG_RXBNE) != SET)
        ;                              /* 等待接收缓冲非空 */
    rxdata = SPI_I2S_RxData(SPI1_SPI); /* 接收一字节数据 */

    return rxdata;
}
