/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd
 ******************************************************************************
 *  @File Name        : EmulatedEE.h
 *  @Author           : ChipON AE/FAE Group
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

#ifndef EMULATED_EE_H
#define EMULATED_EE_H

#include <stdint.h>

/* Flash sector number */
/* KF32A156 
#if defined(KF32A156MQW) || defined(KF32A156MQV) || defined(KF32A156MQT) || defined(KF32A156MQS) || defined(KF32A156MBV)
#define EE_FLASH_SECTOR_NUM (512U)
#elif defined(KF32A156KQV) || defined(KF32A156KQT) || defined(KF32A156KQS)
#define EE_FLASH_SECTOR_NUM (256U)
#elif defined(KF32A156IQS) || defined(KF32A156INP)
#define EE_FLASH_SECTOR_NUM (128U)
#else
#error "Please define the chip model"
#endif*/

/* User-modifiable parameters */
#define EE_SECTOR_NUM ((uint32_t)1U) /*!< sector number, support multiple sectors to from 1 page */
#define EE_PAGE_NUM                                                                                                    \
    ((uint32_t)2U) /*!< page number, Increase total read and write lifespan by increasing the number of flash pages */

/* Non-user-modifiable parameters */
#define EE_USE_FLS_API (false)

#define EE_SECTOR_SIZE ((uint32_t)(1024U)) /*!< sector size */

#define EE_PAGE_SIZE ((uint32_t)(EE_SECTOR_NUM * EE_SECTOR_SIZE)) /*!< page size */

//#define EE_BASE_ADDRESS                                                                                                \
//    ((uint32_t)((EE_FLASH_SECTOR_NUM * EE_SECTOR_SIZE) - (EE_PAGE_SIZE * EE_PAGE_NUM))) /*!< eeprom base address */

#define EE_PARA_MAX_NUMBER                                                                                             \
    ((uint32_t)((EE_PAGE_SIZE / 8U) - 1U)) /*!< maximum number of variables that can be stored                         \
                                            */

#define EE_CACHE_DATA    (32U) //»º´æÊý¾Ý

typedef enum
{
    EN_EERPROM_SECTOR_NUM_0,
    EN_EERPROM_SECTOR_NUM_1,
    EN_EERPROM_SECTOR_NUM_2,
    EN_EERPROM_SECTOR_NUM_3,
    EN_EERPROM_SECTOR_NUM_4,
    EN_EERPROM_SECTOR_NUM_5,
    EN_EERPROM_SECTOR_NUM_MAX,
}enEepromSectorNumType;


uint8_t EmulatedEE_SetSector(uint32_t FlashSectorNum,uint8_t Num);
uint32_t EmulatedEE_ErasePage(uint32_t PageAddress);
uint32_t EmulatedEE_GetValidPage(void);
uint32_t EmulatedEE_GetWriteablePage(void);
uint32_t EmulatedEE_DirectHwWrite(uint32_t Address, uint32_t Data);
uint32_t EmulatedEE_CopyDataToNewPage(uint32_t ValidPage);
uint32_t EmulatedEE_FormatSpace(void);
uint32_t EmulatedEE_CheckPageDateFull(void);
uint32_t EmulatedEE_InitStateOnlyTransfer(uint32_t TransferPage);
uint32_t EmulatedEE_InitStateValidTransfer(uint32_t ValidPage, uint32_t TransferPage);
uint32_t EmulatedEE_ReadData(uint32_t Address, uint32_t *Data);
uint32_t EmulatedEE_WriteData(uint32_t Address, uint32_t Data);
uint32_t EmulatedEE_Init(void);

#endif
