#ifndef __USART_H
#define __USART_H

#include <stdio.h>
#include "sys.h"

#define DEBUG_USARTX USART1
#define DEBUG_USART_PORT GPIOA
#define DEBUG_USART_TX_PIN GPIO_PIN_9
#define DEBUG_USART_RX_PIN GPIO_PIN_10
#define DEBUG_TXPinSource GPIO_PIN_SOURCE_9
#define DEBUG_RXPinSource GPIO_PIN_SOURCE_10
#define DEBUG_PORT_AF GPIO_AF_USART1
#define DEBUG_PORT_CLK RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA)
#define DEBUG_USART_CLK RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1)
#define DEBUG_USARTX_IRQn USART1_IRQn
#define DEBUG_USARTX_IRQHandler USART1_IRQHandler

#define WiFi_USARTX UART4
#define WiFi_USART_PORT GPIOC
#define WiFi_USART_TX_PIN GPIO_PIN_10
#define WiFi_USART_RX_PIN GPIO_PIN_11
#define WiFi_TXPinSource GPIO_PIN_SOURCE_10
#define WiFi_RXPinSource GPIO_PIN_SOURCE_11
#define WiFi_PORT_AF GPIO_AF_UART4
#define WiFi_PORT_CLK RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC)
#define WiFi_USART_CLK RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_UART4)
#define WiFi_USARTX_IRQn UART4_IRQn
#define WiFi_USARTX_IRQHandler UART4_IRQHandler

#define RF_USARTX USART3
#define RF_USART_PORT GPIOB
#define RF_USART_TX_PIN GPIO_PIN_10
#define RF_USART_RX_PIN GPIO_PIN_11
#define RF_TXPinSource GPIO_PIN_SOURCE_10
#define RF_RXPinSource GPIO_PIN_SOURCE_11
#define RF_PORT_AF GPIO_AF_USART3
#define RF_PORT_CLK RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB)
#define RF_USART_CLK RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART3)
#define RF_USARTX_IRQn USART3_IRQn
#define RF_USARTX_IRQHandler USART3_IRQHandler

#define min(x, y) ((x) <= (y) ? (x) : (y))
#define getSub(x, y) ((x) & ((y)->size - 1))
#define getFifoLen(x) ((x)->lenth)
#define getFifoFree(x) (((x)->size) - ((x)->lenth))

#define USART_REC_LEN 10 // 定义最大接收字节数 200
#define EN_USART1_RX 1   // 使能（1）/禁止（0）串口1接收

#define RfUart3_Tx_DMA_Buf_SIZE 2048
#define RfUart3_Rx_DMA_Buf_SIZE 2048

#define Rf_Tx_Fifo_Buf_SIZE 4096
#define Rf_Rx_Fifo_Buf_SIZE 4096

#define WiFiUart4_Tx_DMA_Buf_SIZE 2048
#define WiFiUart4_Rx_DMA_Buf_SIZE 2048

#define WiFi_Tx_Fifo_Buf_SIZE 2048
#define WiFi_Rx_Fifo_Buf_SIZE 2048

#define USART_REC_LEN 10 // 定义最大接收字节数 200

typedef struct
{
    uint8_t *buf;
    uint32_t size;
    uint32_t in;
    uint32_t out;
    uint32_t lenth;
    uint8_t uartSendBusy;
} s_cycle_buffer;

void uart_init(uint32_t bound);

int32_t initFifo(s_cycle_buffer *fifo, uint8_t *circBuf, uint16_t size);
uint32_t fifoGet(s_cycle_buffer *fifo, uint8_t *buf, uint32_t len);
uint32_t fifoPut(s_cycle_buffer *fifo, uint8_t *buf, uint32_t len);

extern uint8_t RfUart3_Tx_DMA_Buf[RfUart3_Tx_DMA_Buf_SIZE];
extern uint8_t RfUart3_Rx_DMA_Buf[RfUart3_Rx_DMA_Buf_SIZE];

extern s_cycle_buffer Rf_Tx_Fifo;
extern uint8_t Rf_Tx_Fifo_Buf[Rf_Tx_Fifo_Buf_SIZE];

extern s_cycle_buffer Rf_Rx_Fifo;
extern uint8_t Rf_Rx_Fifo_Buf[Rf_Rx_Fifo_Buf_SIZE];

void rf_uart3_init(uint32_t bound);
void Rf_Uart_Send(uint8_t *pData, uint32_t Length);
void Rf_Tx_Fifo_Uart_Send(void);

extern uint8_t WiFiUart4_Tx_DMA_Buf[WiFiUart4_Tx_DMA_Buf_SIZE];
extern uint8_t WiFiUart4_Rx_DMA_Buf[WiFiUart4_Rx_DMA_Buf_SIZE];

extern s_cycle_buffer WiFi_Tx_Fifo;
extern uint8_t WiFi_Tx_Fifo_Buf[WiFi_Tx_Fifo_Buf_SIZE];

extern s_cycle_buffer WiFi_Rx_Fifo;
extern uint8_t WiFi_Rx_Fifo_Buf[WiFi_Rx_Fifo_Buf_SIZE];

void wifi_uart4_init(uint32_t bound);
void WiFi_Uart_Send(uint8_t *pData, uint32_t Length);

#endif
