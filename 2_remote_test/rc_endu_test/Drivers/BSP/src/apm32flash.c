#include "apm32flash.h"
#include "main.h"

uint8_t flash_need_update = 0;

/**
 * @brief       从指定地址读出一个字数据
 * @param       faddr: 读取地址，必须按4字节对齐
 * @retval      读取到的一个字数据
 */
void apmflash_read_buff(uint32_t raddr, uint8_t *pbuf, uint32_t length)
{
    memcpy((void *)pbuf, (void *)raddr, length);
}

/**
 * @brief       获取某个地址所在的Flash扇区
 * @param       addr: Flash地址
 * @retval      指定地址所在的Flash扇区
 */
FMC_SECTOR_T apmflash_get_flash_sector(uint32_t addr)
{
    if (addr < ADDR_FLASH_SECTOR_1)
    {
        return FMC_SECTOR_0;
    }
    else if (addr < ADDR_FLASH_SECTOR_2)
    {
        return FMC_SECTOR_1;
    }
    else if (addr < ADDR_FLASH_SECTOR_3)
    {
        return FMC_SECTOR_2;
    }
    else if (addr < ADDR_FLASH_SECTOR_4)
    {
        return FMC_SECTOR_3;
    }
    else if (addr < ADDR_FLASH_SECTOR_5)
    {
        return FMC_SECTOR_4;
    }
    else if (addr < ADDR_FLASH_SECTOR_6)
    {
        return FMC_SECTOR_5;
    }
    else if (addr < ADDR_FLASH_SECTOR_7)
    {
        return FMC_SECTOR_6;
    }
    else if (addr < ADDR_FLASH_SECTOR_8)
    {
        return FMC_SECTOR_7;
    }
    else if (addr < ADDR_FLASH_SECTOR_9)
    {
        return FMC_SECTOR_8;
    }
    else if (addr < ADDR_FLASH_SECTOR_10)
    {
        return FMC_SECTOR_9;
    }
    else if (addr < ADDR_FLASH_SECTOR_11)
    {
        return FMC_SECTOR_10;
    }
    else
    {
        return FMC_SECTOR_11;
    }
}

/**
 * @brief       获取某个地址所在的Flash扇区的起始地址
 * @param       addr: Flash地址
 * @retval      指定地址所在的Flash扇区
 */
uint32_t apmflash_get_flash_satrt_addr(uint32_t addr)
{
    if (addr < ADDR_FLASH_SECTOR_1)
    {
        return ADDR_FLASH_SECTOR_0;
    }
    else if (addr < ADDR_FLASH_SECTOR_2)
    {
        return ADDR_FLASH_SECTOR_1;
    }
    else if (addr < ADDR_FLASH_SECTOR_3)
    {
        return ADDR_FLASH_SECTOR_2;
    }
    else if (addr < ADDR_FLASH_SECTOR_4)
    {
        return ADDR_FLASH_SECTOR_3;
    }
    else if (addr < ADDR_FLASH_SECTOR_5)
    {
        return ADDR_FLASH_SECTOR_4;
    }
    else if (addr < ADDR_FLASH_SECTOR_6)
    {
        return ADDR_FLASH_SECTOR_5;
    }
    else if (addr < ADDR_FLASH_SECTOR_7)
    {
        return ADDR_FLASH_SECTOR_6;
    }
    else if (addr < ADDR_FLASH_SECTOR_8)
    {
        return ADDR_FLASH_SECTOR_7;
    }
    else if (addr < ADDR_FLASH_SECTOR_9)
    {
        return ADDR_FLASH_SECTOR_8;
    }
    else if (addr < ADDR_FLASH_SECTOR_10)
    {
        return ADDR_FLASH_SECTOR_9;
    }
    else if (addr < ADDR_FLASH_SECTOR_11)
    {
        return ADDR_FLASH_SECTOR_10;
    }
    else
    {
        return ADDR_FLASH_SECTOR_11;
    }
}

/**
 * @brief       向指定地址写入指定长度的数据
 * @param       waddr : 指定写入数据的起始地址
 * @param       pbuf  : 保存写入数据的起始地址
 * @param       length: 指定写入数据的长度，单位：半字
 * @retval      无
 */
uint8_t apmflash_write_buff(uint32_t waddr, uint8_t *pbuf, uint32_t length)
{
    FMC_Unlock();           /* 解锁访问FMC控制寄存器 */
    FMC_DisableDataCache(); /* Flash擦除期间，必须禁止数据缓存 */

    if ((waddr < APM32_FLASH_BASE) ||                    /* 指定地址小于Flash的起始地址 */
        (waddr > (APM32_FLASH_BASE + APM32_FLASH_SIZE))) /* 指定地址大于Flash的末地址 */
    {
        return 0;
    }

    for (uint32_t i = 0; i < length; i += 4)
    {
        if (FMC_ProgramWord(waddr, *(uint32_t *)(&pbuf[i])) != FMC_COMPLETE) /* 写入数据 */
        {
            return 0;
        }
        waddr += 4;
    }

    FMC_EnableDataCache(); /* 重新打开数据缓存 */
    FMC_Lock();            /* 重新上锁访问FMC控制寄存器 */

    return 1;
}

uint8_t BootLoader_Flash_Erasure(void)
{
    Debug("FMC_EraseSector start\n");

    FMC_Unlock();           /* 解锁访问FMC控制寄存器 */
    FMC_DisableDataCache(); /* Flash擦除期间，必须禁止数据缓存 */

    IWDT_Refresh();
    if (FMC_EraseSector(apmflash_get_flash_sector(ADDR_FLASH_SECTOR_0), FMC_VOLTAGE_3) == FMC_COMPLETE) /* 擦除成功 */
    {
        IWDT_Refresh();
        Debug("FMC_EraseSector 16K ADDR_FLASH_SECTOR_0 OK!\n");
    }
    else
    {
        goto ERROR;
    }

    IWDT_Refresh();
    if (FMC_EraseSector(apmflash_get_flash_sector(ADDR_FLASH_SECTOR_1), FMC_VOLTAGE_3) == FMC_COMPLETE) /* 擦除成功 */
    {
        IWDT_Refresh();
        Debug("FMC_EraseSector 16K ADDR_FLASH_SECTOR_1 OK!\n");
    }
    else
    {
        goto ERROR;
    }

    IWDT_Refresh();
    if (FMC_EraseSector(apmflash_get_flash_sector(ADDR_FLASH_SECTOR_2), FMC_VOLTAGE_3) == FMC_COMPLETE) /* 擦除成功 */
    {
        IWDT_Refresh();
        Debug("FMC_EraseSector 16K ADDR_FLASH_SECTOR_2 OK!\n");
    }
    else
    {
        goto ERROR;
    }

    FMC_EnableDataCache(); /* 重新打开数据缓存 */
    FMC_Lock();            /* 重新上锁访问FMC控制寄存器 */
    return 1;

ERROR:
    IWDT_Refresh();
    FMC_EnableDataCache(); /* 重新打开数据缓存 */
    FMC_Lock();            /* 重新上锁访问FMC控制寄存器 */
    Debug("FMC_EraseSector ERROR!!!\n");
    return 0;
}

uint8_t Save_User_Data(void)
{
    IWDT_Refresh();
    FMC_Unlock();           /* 解锁访问FMC控制寄存器 */
    FMC_DisableDataCache(); /* Flash擦除期间，必须禁止数据缓存 */
    IWDT_Refresh();
    if (FMC_EraseSector(apmflash_get_flash_sector(ADDR_FLASH_SECTOR_3), FMC_VOLTAGE_3) == FMC_COMPLETE) /* 擦除成功 */
    {
        Debug("FMC_EraseSector 16K OK!");
        apmflash_write_buff(HardFaultMsg_PARAM_ADDR, (uint8_t *)&HardFaultMsgSave, sizeof(S_HardFaultMsgSave));
    }
    else
    {
        goto ERROR;
    }
    IWDT_Refresh();
    FMC_EnableDataCache(); /* 重新打开数据缓存 */
    FMC_Lock();            /* 重新上锁访问FMC控制寄存器 */

    return 1;

ERROR:
    IWDT_Refresh();
    FMC_EnableDataCache(); /* 重新打开数据缓存 */
    FMC_Lock();            /* 重新上锁访问FMC控制寄存器 */
    Debug("FMC_EraseSector ERROR!!!");
    return 0;
}
