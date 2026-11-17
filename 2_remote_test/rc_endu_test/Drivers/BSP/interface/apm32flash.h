#ifndef __APM32FLASH_H
#define __APM32FLASH_H

#include "sys.h"

/* Flash相关定义 */
#define APM32_FLASH_BASE 0x8000000 /* APM32 Flash起始地址 */
#define APM32_FLASH_SIZE 0x100000  /* APM32 Flash大小 */
#define FLASH_WAITETIME 50000      /* Flash等待超时时间 */

/* Flash扇区起始地址定义 */
#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000)  /* 扇区0起始地址，16 KB */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000)  /* 扇区1起始地址，16 KB */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000)  /* 扇区2起始地址，16 KB */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000)  /* 扇区3起始地址，16 KB */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000)  /* 扇区4起始地址，64 KB */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000)  /* 扇区5起始地址，128 KB */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000)  /* 扇区6起始地址，128 KB */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000)  /* 扇区7起始地址，128 KB */
#define ADDR_FLASH_SECTOR_8 ((uint32_t)0x08080000)  /* 扇区8起始地址，128 KB */
#define ADDR_FLASH_SECTOR_9 ((uint32_t)0x080A0000)  /* 扇区9起始地址，128 KB */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* 扇区10起始地址，128 KB */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* 扇区11起始地址，128 KB */

extern uint8_t flash_need_update;

void apmflash_read_buff(uint32_t raddr, uint8_t *pbuf, uint32_t length);
uint8_t apmflash_write_buff(uint32_t waddr, uint8_t *pbuf, uint32_t length);
uint8_t Save_User_Data(void);
uint8_t BootLoader_Flash_Erasure(void);

#endif
