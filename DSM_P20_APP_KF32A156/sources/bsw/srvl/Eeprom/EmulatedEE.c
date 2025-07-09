/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd
 ******************************************************************************
 *  @File Name        : EmulatedEE.c
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Example Version  : V2.4.0.250417_release
 *  @Description      : This file provides Driver for flash emulation of EEPROM
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd
 *  All rights reserved.
 *
 *  This software is copyright protected and proprietary to
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.
 ******************************************************************************/

/******************************************************************************
 *                      QAC Warnings
 ******************************************************************************/
/**
 * @page QAC Warnings
 *
 */
/* PRQA S 0310 EOF #Casting to different object pointer type. */
/* PRQA S 0306 EOF #Cast between a pointer to object and an integral type. */
/******************************************************************************
 *                      Include Files
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "EmulatedEE.h"
#include "__driver_Flash_API.h"
#if EE_USE_FLS_API
#include "kf32a1x6_hli_fls.h"
#endif
#include "CpuPeripheralInit.h"

#define EE_PAGE_NONE     ((uint32_t)0x0FFFFU)    /*!< no valid page found */
#define EE_PAGE_ERASED   ((uint32_t)0xFFFFFFFFU) /*!< page is in erased state */
#define EE_PAGE_TRANSFER ((uint32_t)0xCCCCCCCCU) /*!< page is in transfer state */
#define EE_PAGE_VALID    ((uint32_t)0x00000000U) /*!< page is in valid state */

void     EmulatedEE_UpdatePageStatus(void);
uint32_t EmulatedEE_CheckEEFormat(void);

static uint32_t CurValidPage[EN_EERPROM_SECTOR_NUM_MAX]      = {EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE};
static uint32_t CurValidPageInv[EN_EERPROM_SECTOR_NUM_MAX]   = {EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE};
static uint32_t CurTansferPage[EN_EERPROM_SECTOR_NUM_MAX]    = {EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE};
static uint32_t CurTansferPageInv[EN_EERPROM_SECTOR_NUM_MAX] = {EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE,EE_PAGE_NONE};

static uint32_t EE_FLASH_SECTOR_NUM = 512U;
static uint32_t EE_BASE_ADDRESS = 0;
    
static uint8_t s_EmulateEE_CurSectorNum = 0;

uint8_t EmulatedEE_SetSector(uint32_t FlashSectorNum,uint8_t Num)
{
    if(FlashSectorNum > 512 || Num >= EN_EERPROM_SECTOR_NUM_MAX)
    {
        return FALSE;
    }
    
    s_EmulateEE_CurSectorNum = Num;
    EE_FLASH_SECTOR_NUM = FlashSectorNum;
    EE_BASE_ADDRESS = ((uint32_t)((EE_FLASH_SECTOR_NUM * EE_SECTOR_SIZE) - (EE_PAGE_SIZE * EE_PAGE_NUM))); /*!< eeprom base address */
    return TRUE;
}

/**
 * @brief:模拟EE擦除页
 * @param[in] PageAddress
 * @retval uint32_t
 */
uint32_t EmulatedEE_ErasePage(uint32_t PageAddress)
{
    uint32_t i              = 0U;
    uint32_t kvEraseAddress = 0U;
    uint32_t kvFlashStatus  = CMD_SUCCESS;

    /* PRQA S 2877 ++ #This loop will never be executed more than once. */
    /* erase one or more sectors */
    for (i = 0; i < EE_SECTOR_NUM; i++)
    {
        /* calculate the erase address */
        kvEraseAddress = PageAddress + (i * EE_SECTOR_SIZE);
#if EE_USE_FLS_API
        kvFlashStatus = (uint32_t)HLI_Fls_EraseSector(kvEraseAddress, EE_SECTOR_SIZE);
        (kvFlashStatus == HLI_FLS_STATUS_OK) ? (kvFlashStatus = CMD_SUCCESS) : (kvFlashStatus = CMD_ERROR);

#else

        /* erase sector */
        kvFlashStatus = __FLASH_Erase__(Function_Parameter_Validate, kvEraseAddress, EE_SECTOR_SIZE);
#endif

        if (kvFlashStatus != CMD_SUCCESS)
        {
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    return kvFlashStatus;
    /* PRQA S 2877 -- #This loop will never be executed more than once. */
}

static inline uint32_t EmulatedEE_WriteFlashData(uint32_t WriteAddress, uint32_t Len, uint32_t *data)
{
    uint32_t kvFlashStatus = CMD_SUCCESS;

#if EE_USE_FLS_API
    kvFlashStatus = (uint32_t)HLI_Fls_WriteMinimumWriteableBytes(WriteAddress, Len, (uint8_t *)data);
    (kvFlashStatus == HLI_FLS_STATUS_OK) ? (kvFlashStatus = CMD_SUCCESS) : (kvFlashStatus = CMD_ERROR);
#else
    /*  write */
//    INT_All_Enable(FALSE);
    kvFlashStatus = __FLASH_Program_NBytes__(Function_Parameter_Validate, WriteAddress, Len, data);
//    INT_All_Enable(TRUE);
#endif
    return kvFlashStatus;
}
/**
 * @brief: 模拟EE获取有效页
 * @retval uint32_t
 */
uint32_t EmulatedEE_GetValidPage(void)
{
    if ((CurValidPage[s_EmulateEE_CurSectorNum] + CurValidPageInv[s_EmulateEE_CurSectorNum]) == 0xFFFFFFFFU)
    {
        return CurValidPage[s_EmulateEE_CurSectorNum];
    }
    else
    {
        if (EmulatedEE_CheckEEFormat() == 0U)
        {
            EmulatedEE_UpdatePageStatus();
            return CurValidPage[s_EmulateEE_CurSectorNum];
        }
        else
        {
            return EE_PAGE_NONE;
        }
    }
}

/**
 * @brief: 模拟EE获取可写Page
 * @retval uint32_t
 */
uint32_t EmulatedEE_GetWriteablePage(void)
{
    if (((CurValidPage[s_EmulateEE_CurSectorNum] + CurValidPageInv[s_EmulateEE_CurSectorNum]) == 0xFFFFFFFFU) 
     && ((CurTansferPage[s_EmulateEE_CurSectorNum] + CurTansferPageInv[s_EmulateEE_CurSectorNum]) == 0xFFFFFFFFU))
    {
        if (CurTansferPage[s_EmulateEE_CurSectorNum] != EE_PAGE_NONE)
        {
            return CurTansferPage[s_EmulateEE_CurSectorNum];
        }
        else if (CurValidPage[s_EmulateEE_CurSectorNum] != EE_PAGE_NONE)
        {
            return CurValidPage[s_EmulateEE_CurSectorNum];
        }
        else
        {
            return EE_PAGE_NONE;
        }
    }
    else
    {
        if (EmulatedEE_CheckEEFormat() == 0U)
        {
            EmulatedEE_UpdatePageStatus();
            return CurValidPage[s_EmulateEE_CurSectorNum];
        }
        else
        {
            return EE_PAGE_NONE;
        }
    }
}

/**
 * @brief: 模拟EE写Flash数据
 * @param[in] Address
 * @param[in] Data
 * @retval uint32_t
 */
uint32_t EmulatedEE_DirectHwWrite(uint32_t Address, uint32_t Data)
{
    uint32_t kvValidPage   = EE_PAGE_NONE;
    uint32_t kvFindAddress = 0U;
    uint32_t kvEndAddress  = 0U;
    uint32_t kvFlashStatus = 0U;

    /* get the valid page */
    kvValidPage = EmulatedEE_GetWriteablePage();

    if (kvValidPage == EE_PAGE_NONE)
    {
        return 0xFFU;
    }
    else
    {
        /* Do Nothing */
    }

    /* find address calculation */
    kvFindAddress = EE_BASE_ADDRESS + (kvValidPage * EE_PAGE_SIZE) + 8U;

    /* end address calculation */
    kvEndAddress = EE_BASE_ADDRESS + (kvValidPage * EE_PAGE_SIZE) + EE_PAGE_SIZE;

    while (kvFindAddress < kvEndAddress)
    {
        /* find addresses without Data */
        if (((*(uint32_t *)kvFindAddress) == 0xFFFFFFFFU) && ((*(uint32_t *)(kvFindAddress + 4U)) == 0xFFFFFFFFU))
        {
            uint32_t kvTempData[2U] = {0U, 0U};
            kvTempData[0U]          = Data;
            kvTempData[1U]          = Address;

            /* write Data to flash */
            kvFlashStatus = EmulatedEE_WriteFlashData(kvFindAddress, 8U, (uint32_t *)&kvTempData);

            return kvFlashStatus;
        }
        else
        {
            kvFindAddress += 8U;
        }
    }

    return kvFlashStatus;
}

/**
 * @brief: 模拟EE复制有效数据到下一页
 * @param[in] ValidPage
 * @retval uint32_t
 */
uint32_t EmulatedEE_CopyDataToNewPage(uint32_t ValidPage)
{
    uint32_t kvData             = 0U;
    uint32_t kvIdx              = 0U;
    uint32_t kvFullPageAddress  = 0U;
    uint32_t kvEmptyPageAddress = 0U;
    uint32_t kvFlashStatus      = CMD_SUCCESS;

    if (ValidPage != EE_PAGE_NONE)
    {
        kvEmptyPageAddress = (EE_BASE_ADDRESS + (EE_PAGE_SIZE * ((ValidPage + 1) % EE_PAGE_NUM)));

        kvFullPageAddress = (EE_BASE_ADDRESS + (EE_PAGE_SIZE * ValidPage));
    }
    else
    {
        return 0xFFU;
    }

    uint32_t kvTempData[2U] = {0U, 0U};
    kvTempData[0U]          = EE_PAGE_TRANSFER;

    /* change the status of the empty page to TRANSFER */

    if ((kvFlashStatus = EmulatedEE_WriteFlashData(kvEmptyPageAddress, 8U, (uint32_t *)&kvTempData)) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    EmulatedEE_UpdatePageStatus();

    for (kvIdx = 0U; kvIdx < EE_PARA_MAX_NUMBER; kvIdx++)
    {
        /* find valid variables */
        if (EmulatedEE_ReadData(kvIdx * 4U, &kvData) == 0U)
        {

            /* store variable to new page  */
            if ((kvFlashStatus = EmulatedEE_DirectHwWrite(kvIdx * 4U, kvData)) != CMD_SUCCESS)
            {
                return kvFlashStatus;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    /* erase old page */
    if ((kvFlashStatus = EmulatedEE_ErasePage(kvFullPageAddress)) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    kvTempData[0U] = EE_PAGE_VALID;

    /* change the status of the empty page to VALID */

    if ((kvFlashStatus = EmulatedEE_WriteFlashData(kvEmptyPageAddress, 8U, (uint32_t *)&kvTempData)) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    EmulatedEE_UpdatePageStatus();

    return kvFlashStatus;
}

/**
 * @brief 模拟EE空间格式化
 * @retval uint32_t
 */
uint32_t EmulatedEE_FormatSpace(void)
{
    uint32_t kvFlashStatus = CMD_SUCCESS;

    for (uint32_t i = 0U; i < EE_PAGE_NUM; i++)
    {
        uint32_t kvEraseAddress = (EE_BASE_ADDRESS + (EE_PAGE_SIZE * i));
        /* erase page */
        if ((kvFlashStatus = EmulatedEE_ErasePage(kvEraseAddress)) != CMD_SUCCESS)
        {
            return kvFlashStatus;
        }
        else
        {
            /* Do Nothing */
        }
    }

    {
        uint32_t kvTempData[2U] = {0U, 0U};
        kvTempData[0U]          = EE_PAGE_VALID;
        /* mark the status of page 0 as VALID */
        kvFlashStatus = EmulatedEE_WriteFlashData(EE_BASE_ADDRESS, 8U, (uint32_t *)&kvTempData);
    }

    return kvFlashStatus;
}

/**
 * @brief: 确认是否为模拟EE格式
 * @retval uint32_t
 */
uint32_t EmulatedEE_CheckEEFormat(void)
{
    uint32_t kvPageStatus   = EE_PAGE_ERASED;
    uint32_t kvValidPage    = EE_PAGE_NONE;
    uint32_t kvTransferPage = EE_PAGE_NONE;

    for (uint32_t i = 0U; i < EE_PAGE_NUM; i++)
    {
        kvPageStatus = (*(uint32_t *)(EE_BASE_ADDRESS + (EE_PAGE_SIZE * i)));

        if ((kvPageStatus != EE_PAGE_ERASED) && (kvPageStatus != EE_PAGE_TRANSFER) && (kvPageStatus != EE_PAGE_VALID))
        {
            return 1U;
        }
        else if (kvPageStatus == EE_PAGE_VALID)
        {
            if (kvValidPage == EE_PAGE_NONE)
            {
                kvValidPage = i;
            }
            else
            {
                return 1U;
            }
        }
        else if (kvPageStatus == EE_PAGE_TRANSFER)
        {
            if (kvTransferPage == EE_PAGE_NONE)
            {
                kvTransferPage = i;
            }
            else
            {
                return 1U;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    if ((kvValidPage == EE_PAGE_NONE) && (kvTransferPage == EE_PAGE_NONE))
    {
        return 1U;
    }
    else
    {
        /* Do Nothing */
    }

    /* the format is correct */
    return 0U;
}

/**
 * @brief: 模拟EE确认是否写满
 * @retval uint32_t
 */
uint32_t EmulatedEE_CheckPageDateFull(void)
{
    uint32_t kvValidPage   = 0U;
    uint32_t kvEndAddress  = 0U;
    uint32_t kvFlashStatus = CMD_SUCCESS;

    /* get the valid page */
    kvValidPage = EmulatedEE_GetValidPage();

    if (kvValidPage == EE_PAGE_NONE)
    {
        return 0xFFU;
    }
    else
    {
        /* Do Nothing */
    }

    /* end address calculation */
    kvEndAddress = EE_BASE_ADDRESS + (kvValidPage * EE_PAGE_SIZE) + EE_PAGE_SIZE;

    /* check if the page is full */
    if ((*(uint32_t *)(kvEndAddress - 4U)) != 0xFFFFFFFFU)
    {
        /* when the page is full, transfer the kvData to erase page */
        if ((kvFlashStatus = EmulatedEE_CopyDataToNewPage(kvValidPage)) != CMD_SUCCESS)
        {
            return kvFlashStatus;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    /* page full check ok */
    return 0U;
}

/**
 * @brief: 模拟EE初始化状态-只有Transfer页
 * @param[in] TransferPage
 * @retval uint32_t
 */
uint32_t EmulatedEE_InitStateOnlyTransfer(uint32_t TransferPage)
{
    uint32_t kvFlashStatus         = CMD_SUCCESS;
    uint32_t kvTransferPageAddress = (EE_BASE_ADDRESS + (EE_PAGE_SIZE * TransferPage));

    uint32_t kvTempData[2U] = {0U, 0U};
    kvTempData[0U]          = EE_PAGE_VALID;

    kvFlashStatus = EmulatedEE_WriteFlashData(kvTransferPageAddress, 8, (uint32_t *)&kvTempData);

    EmulatedEE_UpdatePageStatus();
    return kvFlashStatus;
}

/**
 * @brief: 模拟EE初始化状态- 同时存在Valid,Transfer页
 * @param[in] ValidPage
 * @param[in] TransferPage
 * @retval uint32_t
 */
uint32_t EmulatedEE_InitStateValidTransfer(uint32_t ValidPage, uint32_t TransferPage)
{
    uint32_t kvErasePageAddress = EE_BASE_ADDRESS + (EE_PAGE_SIZE * TransferPage);

    uint32_t kvFlashStatus = CMD_SUCCESS;

    /* erase the transfer state page */
    if ((kvFlashStatus = EmulatedEE_ErasePage(kvErasePageAddress)) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    EmulatedEE_UpdatePageStatus();

    /* retransmit kvData */
    return EmulatedEE_CopyDataToNewPage(ValidPage);
}

/**
 * @brief: 模拟EE初始化ram
 * @retval uint32_t
 */
void EmulatedEE_UpdatePageStatus(void)
{
    uint32_t kvPageStatus = EE_PAGE_ERASED;

    for (uint32_t i = 0U; i < EE_PAGE_NUM; i++)
    {
        kvPageStatus = (*(uint32_t *)(EE_BASE_ADDRESS + (EE_PAGE_SIZE * i)));
        if (kvPageStatus == EE_PAGE_VALID)
        {
            CurValidPage[s_EmulateEE_CurSectorNum] = i;
        }
        else if (kvPageStatus == EE_PAGE_TRANSFER)
        {
            CurTansferPage[s_EmulateEE_CurSectorNum] = i;
        }
        else
        {
            /* Do Nothing */
        }
    }

    CurValidPageInv[s_EmulateEE_CurSectorNum]   = ~CurValidPage[s_EmulateEE_CurSectorNum];
    CurTansferPageInv[s_EmulateEE_CurSectorNum] = ~CurTansferPage[s_EmulateEE_CurSectorNum];
}

/**
 * @brief: 模拟EE初始化
 * @retval uint32_t
 */
uint32_t EmulatedEE_Init(void)
{
    uint32_t kvFlashStatus  = CMD_SUCCESS;
    uint32_t kvPageStatus   = EE_PAGE_ERASED;
    uint32_t kvValidPage    = EE_PAGE_NONE;
    uint32_t kvTransferPage = EE_PAGE_NONE;

    /* format validity check */
    if (EmulatedEE_CheckEEFormat() != 0U)
    {
        /* if the format is invalid, reformat */
        if ((kvFlashStatus = EmulatedEE_FormatSpace()) != CMD_SUCCESS)
        {
            return kvFlashStatus;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    EmulatedEE_UpdatePageStatus();

    for (uint32_t i = 0U; i < EE_PAGE_NUM; i++)
    {
        kvPageStatus = (*(uint32_t *)(EE_BASE_ADDRESS + (EE_PAGE_SIZE * i)));
        if (kvPageStatus == EE_PAGE_VALID)
        {
            kvValidPage = i;
        }
        else if (kvPageStatus == EE_PAGE_TRANSFER)
        {
            kvTransferPage = i;
        }
        else
        {
            uint32_t kvEraseAddress = (EE_BASE_ADDRESS + (EE_PAGE_SIZE * i));
            if ((kvFlashStatus = EmulatedEE_ErasePage(kvEraseAddress)) != CMD_SUCCESS)
            {
                return kvFlashStatus;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }

    if ((kvValidPage == EE_PAGE_NONE) && (kvTransferPage != EE_PAGE_NONE))
    {
        if ((kvFlashStatus = EmulatedEE_InitStateOnlyTransfer(kvTransferPage)) != CMD_SUCCESS)
        {
            return kvFlashStatus;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else if ((kvValidPage != EE_PAGE_NONE) && (kvTransferPage != EE_PAGE_NONE))
    {
        if ((kvFlashStatus = EmulatedEE_InitStateValidTransfer(kvValidPage, kvTransferPage)) != CMD_SUCCESS)
        {
            return kvFlashStatus;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    /* check if the page is full, when the page is full, transfer the kvData to erase page */
    if ((kvFlashStatus = EmulatedEE_CheckPageDateFull()) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    return kvFlashStatus;
}

/**
 * @brief: 模拟EE写数据
 * @param[in] Address EE的虚拟地址
 * @param[in] Data  4字节数据
 * @retval uint32_t
 */
uint32_t EmulatedEE_WriteData(uint32_t Address, uint32_t Data)
{
    uint32_t kvFlashStatus = CMD_SUCCESS;

    if (((Address & 0x3U) > 0U) || (Address > ((EE_PAGE_SIZE / 2U) - 5U)))
    {
        return PARAM_ERROR;
    }
    else
    {
        /* Do Nothing */
    }

    /* check if the page is full, when the page is full, transfer the kvData to erase page */
    if ((kvFlashStatus = EmulatedEE_CheckPageDateFull()) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    /* write kvData to flash */
    if ((kvFlashStatus = EmulatedEE_DirectHwWrite(Address, Data)) != CMD_SUCCESS)
    {
        return kvFlashStatus;
    }
    else
    {
        /* Do Nothing */
    }

    return kvFlashStatus;
}

/**
 * @brief 模拟EE读取数据
 * @param[in] Address EE的虚拟地址
 * @param[in] Data 4字节数据
 * @retval uint32_t
 */
uint32_t EmulatedEE_ReadData(uint32_t Address, uint32_t *Data)
{
    uint32_t kvValidPage    = EE_PAGE_NONE;
    uint32_t kvDataAddress  = 0U;
    uint32_t kvFindAddress  = 0U;
    uint32_t kvStartAddress = 0U;

    if (((Address & 0x3U) > 0U) && (Address > ((EE_PAGE_SIZE / 2U) - 5U)))
    {
        return PARAM_ERROR;
    }
    else
    {
        /* Do Nothing */
    }

    /* get the valid page */
    kvValidPage = EmulatedEE_GetValidPage();

    if (kvValidPage == EE_PAGE_NONE)
    {
        return EE_PAGE_NONE;
    }
    else
    {
        /* Do Nothing */
    }
    /* start address calculation */
    kvStartAddress = EE_BASE_ADDRESS + (kvValidPage * EE_PAGE_SIZE) + 8U;

    /* find address calculation */
    kvFindAddress = ((EE_BASE_ADDRESS + (kvValidPage * EE_PAGE_SIZE)) + EE_PAGE_SIZE) - 4U;

    while (kvFindAddress > kvStartAddress)
    {
        /* read variable address */
        kvDataAddress = (*(uint16_t *)kvFindAddress);

        /* variable address matching */
        if (Address == kvDataAddress)
        {

            /* read Data */
            *Data = (*(uint32_t *)(kvFindAddress - 4U));

            /* kvData successfully read */
            return 0U;
        }
        else
        {
            /* Do Nothing */
        }

        /* find address - 8 */
        kvFindAddress -= 8U;
    }
    
    /* failed to read kvData */
    return 1U;
}
