/**
 *	@file TLE9210x_ServLayer.h
 *	@author Infineon Technologies AG
 *	@date 11.09.2023
 *	@brief TLE9210x specific device driver implementation from Infineon Technologies AG.
 *
 ************************************************************************
 *
 * Copyright (c) 2023, Infineon Technologies AG
 * All rights reserved.
 *
 ************************************************************************
 */

/** \addtogroup TLE9210x_SERVICE_LAYER
 *  @{
 */

#ifndef TLE9210x_SERVLAYER_H
#define TLE9210x_SERVLAYER_H

/************************************************************************
**                             Includes                                **
************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TLE9210x_RegLayer.h"

/************************************************************************
**                      Local Macro Definitions                        **
************************************************************************/

/** \brief Indicate that the SPI message is a register-write operation.
*/
#define TLE9210x_SPI_ACTION_WRITE               (0x01u)

/** \brief Indicate that the SPI message is a register-read operation.
*/
#define TLE9210x_SPI_ACTION_READ                (0x00u)

/************************************************************************
**                      Local Type Definitions                         **
************************************************************************/

/************************************************************************
**                    Local Variable Definitions                       **
************************************************************************/

/************************************************************************
**                    Local Function Definitions                       **
************************************************************************/

/************************************************************************
**                    Global Variable Definitions                      **
************************************************************************/

/************************************************************************
**                    Global Function Definitions                      **
************************************************************************/
void TLE9210x_ServLayer_setReg(uint8_t u8_address, uint16_t u16_data);
void TLE9210x_ServLayer_getReg(uint8_t u8_address);
void TLE9210x_ServLayer_SpiInterfaceStatus(void);
void TLE9210x_ServLayer_InitSpiInterface(void);
void TLE9210x_ServLayer_getSpiData(void);

void TLE9210x_ServLayer_getRegClr(uint8_t u8_address);


/** @}*/ /* End of group TLE9210x_SERVICE_LAYER */

#endif /* TLE9210x_SERVLAYER_H */
