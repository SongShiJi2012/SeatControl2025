/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd
 ******************************************************************************
 *  @File Name        : fee.h
 *  @Author           : ChipON AE/FAE Group
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Example Version  : V2.4.0.250417_release
 *  @Description      : This file provides Driver for flash emulation of EEPROM
 ******************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd
 *  All rights reserved.
 *
 *  This software is copyright protected and proprietary to
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.
 *****************************************************************************/
#ifndef FEE_H
#define FEE_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 **                      Include Files
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
 *                      Macro or Inline
 ******************************************************************************/

/******************************************************************************
 **                     Typedef Definitions
 ******************************************************************************/
/**
 * @brief fee status
 */
typedef enum
{
    /** @brief fee status ok */
    FEE_STATUS_OK,
    /** @brief  */
    FEE_STATUS_PARAM_ERR = 0x0CU,
    /** @brief  */
    FEE_STATUS_ERROR = 0xAAU,
    /*¶ÔÆä */
    FEE_STATUS_ALIGNMENT = 0xABU,
    /*³¬·¶Î§ */
    FEE_STATUS_ADDR_ERR = 0xACU,
} FEE_StatusType;
typedef enum
{
    FEE_UNINIT,
    FEE_INIT,
    FEE_WRITE,
    FEE_IDLE,
} FEE_StateEnumType;

/******************************************************************************
 *                      Export Variables
 ******************************************************************************/

/******************************************************************************
 *                      Export Functions
 ******************************************************************************/
/**
 * @brief The function initializes Fee module.
 *
 */
void FEE_Init(void);

/**
 * @brief Write one or more 4 Bytes Block to Emulated Eeprom.
 *
 * @details The address range for writing is 0 to 511 bytes
 *
 * @param WriteAddr Target address in Emulated Eeprom memory.
 * @param DataLength Number of bytes to write.
 * @param Buffers Pointer to source data buffer.
 *
 * @return bool
 * @retval true write success
 * @retval false write failed
 */
FEE_StatusType FEE_Write(uint32_t WriteAddr, uint32_t DataLength, const uint32_t *Buffers);

/**
 * @brief Reads from Emulated Eeprom memory.
 *
 * @param ReadAddr Read address in Emulated Eeprom memory.
 * @param DataLength  Number of bytes to read.
 * @param Buffers Pointer to target data buffer.
 *
 * @return bool
 * @retval true read success
 * @retval false read failed
 */
FEE_StatusType FEE_Read(uint32_t ReadAddr, uint32_t DataLength, uint32_t *Buffers);

/**
 * @brief Get Fee Current Status
 *
 * @return FEE_StateEnumType
 * @retval FEE_UNINIT
 * @retval FEE_INIT
 * @retval FEE_WRITE
 * @retval FEE_IDLE
 */
FEE_StateEnumType FEE_GetStatus(void);
    void fee_Test(void);

#ifdef __cplusplus
}
#endif
#endif
/* EOF */
