/**
 *  @file TLE9210x_HAL.h
 *  @author Infineon Technologies AG
 *	@date 11.09.2023
 *	@brief TLE9210x specific device driver implementation from Infineon Technologies AG.
 *
 ***********************************************************************************************************************
 *
 * Copyright (c) 2023, Infineon Technologies AG
 * All rights reserved.
 *
 **********************************************************************************************************************
 */

/** \addtogroup TLE9210x_HAL
 *  @{
 */

#ifndef TLE9210x_HAL_H
#define TLE9210x_HAL_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "system_init.h"
#include "Srvl_Tle9210x.h"

/*******************************************************************************
**                          Global Macro Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
void TLE9210x_WaitFor_us_HAL(uint32_t u32_waitTime);
void TLE9210x_InitSpiInterface_HAL(void);
uint8_t TLE9210x_SpiInterfaceStatus_HAL(void);
void TLE9210x_SendSpiData_HAL(uint32_t u32_sendBuffer);
uint32_t TLE9210x_ReadSpiRxBuffer_HAL(void);

/** @}*/ /* End of group TLE9210x_HAL */

#endif /* TLE9210x_HAL_H */
