/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd
 ******************************************************************************
 *  @File Name        : fee.c
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

/******************************************************************************
 **                      Include Files
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "__driver_Flash_API.h"
#include "EmulatedEE.h"
#include "fee.h"
#include "kflog.h"
#include "CpuPeripheralInit.h"
#include "pins_driver.h"

/******************************************************************************
 *                      Macro Definitions
 ******************************************************************************/

/**
 * @brief Fee access to the maximum space
 */
#define FEE_EEPROM_ADDR_MAX ((EE_PAGE_SIZE / 2U) - ((EE_CACHE_DATA *2)))
/******************************************************************************
 *                      Constants
 ******************************************************************************/

/******************************************************************************
 *                      Type definitions
 ******************************************************************************/

/******************************************************************************
 *                      Variables
 ******************************************************************************/

/**
 * @brief Fee state
 */
static FEE_StateEnumType FeeState = FEE_UNINIT;
/******************************************************************************
 *                      Function definitions
 ******************************************************************************/
/**
 * @brief The function initializes Fee module.
 *
 */
void FEE_Init(void)
{
    FeeState = FEE_INIT;
    EmulatedEE_Init();
    FeeState = FEE_IDLE;
}

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
FEE_StatusType FEE_Write(uint32_t WriteAddr, uint32_t DataLength, const uint32_t *Buffers)
{
    uint32_t           kvRetVal;
    FEE_StatusType kvStatus = FEE_STATUS_OK;

    if ((WriteAddr + DataLength) > FEE_EEPROM_ADDR_MAX)
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

    if (((DataLength & 0x3U) > 0U) || (0U == DataLength))
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

    if (Buffers == NULL)
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

#if FEE_WRITE_ISR_LOCK_ENABLE
    kvIntState = (INT_CTL0 & INT_CTL0_AIE);
    asm("DSI");
    asm("NOP");
#endif
    /** EE_Write Lock*/
    if (FeeState == FEE_IDLE)
    {
        FeeState = FEE_WRITE;
    }
    else
    {
        return false;
    }
#if FEE_WRITE_ISR_LOCK_ENABLE
    if (kvIntState != 0)
    {
        asm("ENI");
        asm("NOP");
    }
#endif

    for (uint32_t i = 0U; i < DataLength; i += 4U)
    {

        kvRetVal = EmulatedEE_WriteData(WriteAddr + i, Buffers[i / 4U]);

        if (kvRetVal != CMD_SUCCESS)
        {
            kvStatus = FEE_STATUS_ERROR;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    FeeState = FEE_IDLE;

    return kvStatus;
}

/**
 * @brief Reads from Emulated Eeprom memory.
 *
 * @param ReadAddr Read address in Emulated Eeprom memory.
 * @param DataLength  Number of bytes to read.
 * @param Buffers Pointer to target data buffer.
 * @retval true
 * @retval false
 */
FEE_StatusType FEE_Read(uint32_t ReadAddr, uint32_t DataLength, uint32_t *Buffers)
{
    uint32_t           kvRetVal;
    FEE_StatusType kvStatus = FEE_STATUS_OK;

    if ((ReadAddr + DataLength) > FEE_EEPROM_ADDR_MAX)
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

    if (((ReadAddr & 0x3U) > 0U) || (0U == DataLength))
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

    if (Buffers == NULL)
    {
        return FEE_STATUS_PARAM_ERR;
    }
    else
    {
        /* Do Nothing */
    }

    for (uint32_t i = 0U; i < DataLength; i += 4U)
    {
        kvRetVal = EmulatedEE_ReadData(ReadAddr + i, &Buffers[i / 4U]);

        if (kvRetVal != CMD_SUCCESS)
        {
            kvStatus = FEE_STATUS_ERROR;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    return kvStatus;
}

/**
 * @brief Get Fee Current Status
 *
 * @return FEE_StateEnumType
 * @retval FEE_UNINIT
 * @retval FEE_INIT
 * @retval FEE_WRITE
 * @retval FEE_IDLE
 */
FEE_StateEnumType FEE_GetStatus(void)
{
    return FeeState;
}

#if 1

uint32_t WriteAddrrr = 0;
uint32_t WriteLengthggg = 504;
uint32_t WriteData[127] = {0};
uint32_t ReadData[127] = {0};
FEE_StatusType WriteResult = 0;
FEE_StatusType ReadResult = 0;
uint8_t writetestflg = 0;

void fee_Test(void)
{
    uint32_t i = 0;
    uint8_t j = 0;
    
    for(i = 0; i < WriteLengthggg; i+=4)
    {
        WriteData[i/4] = (j<< 24) | ((j+1)<<16) | ((j+2)<<8) | ((j+3)<<0);
        j+=4;
    }   

    if(writetestflg == 1)
    {
        writetestflg = 0;
        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        WriteResult = FEE_Write(WriteAddrrr,WriteLengthggg,WriteData);//9.4ms //17.2ms  //»»Ò³Ê±ºò 53.3ms
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);
        
        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        ReadResult = FEE_Read(WriteAddrrr,WriteLengthggg,ReadData);//13.8ms //5.1ms   //5.7ms
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);
        kf_printf("W:%d %d %d  ",WriteData[0],WriteData[1],WriteData[2]);
        kf_printf("D:%d %d %d  ",ReadData[0],ReadData[1],ReadData[2]);
    }
    if(writetestflg == 2)
    {
        uint32_t dddd = 0x48364735;
        writetestflg = 0;
        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        WriteResult = FEE_Write(0,4,&dddd);
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);

        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        ReadResult = FEE_Read(0,4,ReadData);
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);
        kf_printf("DD:%d %d %d  ",ReadData[0],ReadData[1],ReadData[2]);
    }
}

#endif
/* EOF */
