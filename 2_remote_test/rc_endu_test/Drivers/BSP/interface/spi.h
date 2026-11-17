#ifndef __SPI_H
#define __SPI_H

#include "sys.h"

/* SPI1相关定义 */
#define SPI1_SPI SPI1
#define SPI1_SPI_CLK_ENABLE()                            \
    do                                                   \
    {                                                    \
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1); \
    } while (0)

/* SPI1引脚定义 */
#define SPI1_SCK_GPIO_PORT GPIOA
#define SPI1_SCK_GPIO_PIN GPIO_PIN_5
#define SPI1_SCK_GPIO_PIN_SOURCE GPIO_PIN_SOURCE_5
#define SPI1_SCK_GPIO_AF GPIO_AF_SPI1
#define SPI1_SCK_GPIO_CLK_ENABLE()                        \
    do                                                    \
    {                                                     \
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA); \
    } while (0)

#define SPI1_MISO_GPIO_PORT GPIOA
#define SPI1_MISO_GPIO_PIN GPIO_PIN_6
#define SPI1_MISO_GPIO_PIN_SOURCE GPIO_PIN_SOURCE_6
#define SPI1_MISO_GPIO_AF GPIO_AF_SPI1
#define SPI1_MISO_GPIO_CLK_ENABLE()                       \
    do                                                    \
    {                                                     \
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA); \
    } while (0)

#define SPI1_MOSI_GPIO_PORT GPIOA
#define SPI1_MOSI_GPIO_PIN GPIO_PIN_7
#define SPI1_MOSI_GPIO_PIN_SOURCE GPIO_PIN_SOURCE_7
#define SPI1_MOSI_GPIO_AF GPIO_AF_SPI1
#define SPI1_MOSI_GPIO_CLK_ENABLE()                       \
    do                                                    \
    {                                                     \
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA); \
    } while (0)

/* SPI总线速度定义 */
#define SPI_SPEED_2 0
#define SPI_SPEED_4 1
#define SPI_SPEED_8 2
#define SPI_SPEED_16 3
#define SPI_SPEED_32 4
#define SPI_SPEED_64 5
#define SPI_SPEED_128 6
#define SPI_SPEED_256 7

/* 函数声明 */
void spi1_init(void);                         /* 初始化SPI1 */
void spi1_set_speed(uint8_t speed);           /* 设置SPI1速度 */
uint8_t spi1_read_write_byte(uint8_t txdata); /* SPI1读写一个字节数据 */

#endif
