/**
 *	@file TLE9210x_ServLayer.c
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

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x_ServLayer.h"
#include "TLE9210x_FuncLayer.h"
#include "Srvl_Tle9210x.h"
#include "TLE9210x_HAL.h"

/************************************************************************
**                      Local Macro Definitions                        **
************************************************************************/

/************************************************************************
**                      Local Type Definitions                         **
************************************************************************/

/************************************************************************
**                    Local Variable Definitions                       **
************************************************************************/

/************************************************************************
**                    Local Function Definitions                       **
************************************************************************/

static void TLE9210x_ServLayer_SendSpiData(void);
static void TLE9210x_ServLayer_ReadSpiRxBuffer(void);

/************************************************************************
**                    Global Variable Definitions                      **
************************************************************************/

/** \brief Global u32 buffer for the receive function
*/
static uint32_t u32_rxBuffer;

/** \brief Global u8 buffer for the transmit function
*/
static uint8_t u8_txBuffer[3];

/** \brief Global u32 buffer for the transmit function
*/
static uint32_t u32_txBuffer;

/************************************************************************
**                    Global Function Definitions                      **
************************************************************************/

/** \brief Initialize the SPI interface of the microcontroller
 *  
 *  Within this function the microcontroller specific initialization for the SPI interface can either be implemented or called.
 *  
 *  \return void
 */
void TLE9210x_ServLayer_InitSpiInterface(void)
{
    /* Call SPI Init function here */
    TLE9210x_InitSpiInterface_HAL();
}

/** \brief Read out the SPI RX buffer of the microcontroller
 * 
 *  Within this function the microcontroller specific SPI buffer read out function can be either implemented or called.
 *  The buffer value has to be written into the \ref u32_rxBuffer.
 *  
 *  \return void
 */
static void TLE9210x_ServLayer_ReadSpiRxBuffer(void)
{
    /* Call SPI Read function here and write into rxBuffer */
    u32_rxBuffer = TLE9210x_ReadSpiRxBuffer_HAL();
}

/** \brief Get the Status of the SPI interface
 * 
 *  Within this function the microcontroller specific SPI status function has to be implemented or called.
 *  The result has to be written to TLE9210x_s_deviceDriver.u8_statusSPI.
 *  
 *  \return void
 */
void TLE9210x_ServLayer_SpiInterfaceStatus(void)
{
    /* Call SPI status function here */
    TLE9210x_s_deviceDriver.u8_statusSPI = TLE9210x_SpiInterfaceStatus_HAL();
}

/** \brief Sends data via the microcontroller's SPI interface
 * 
 *  Within this function the microcontroller specific SPI TX function has to be called or implemented.
 *  The transmit function has to transmit the variable u32_txBuffer that contains the SPI message. 
 * 
 *  \return void
 */
static void TLE9210x_ServLayer_SendSpiData(void)
{
    /* Call SPI send function here */
    TLE9210x_SendSpiData_HAL(u32_txBuffer); 
}

/** \brief Read out the SPI RX buffer of the microconroller
 *  
 *  \return void
 */
void TLE9210x_ServLayer_getSpiData(void)
{
    TLE9210x_ServLayer_ReadSpiRxBuffer();
    TLE9210x_s_deviceDriver.u8_SpiRx[2] = (uint8_t)(u32_rxBuffer & 0xFFu);
    TLE9210x_s_deviceDriver.u8_SpiRx[1] = (uint8_t)((u32_rxBuffer >> 8) & 0xFFu);
    TLE9210x_s_deviceDriver.u8_SpiRx[0] = (uint8_t)((u32_rxBuffer >> 16) & 0xFFu);
}

/** \brief Prepare a set-Register message and calls the corresponding microcontroller SPI send function
 *  
 *  \param u8_address address of the register to be written
 *  \param u16_data data to be written
 *  
 *  \return void
 */
void TLE9210x_ServLayer_setReg(uint8_t u8_address, uint16_t u16_data)
{
    u8_txBuffer[0] = (uint8_t)((u8_address << 1) | (uint8_t)TLE9210x_SPI_ACTION_WRITE);
    u8_txBuffer[0] = u8_txBuffer[0] | 0xC0u;
    u8_txBuffer[2] = (uint8_t)(u16_data & 0xFFu);
    u8_txBuffer[1] = (uint8_t)(u16_data >> 8);
   // u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[2] << 16)) | ((uint32_t)((uint32_t)u8_txBuffer[1] << 8)) | ((uint32_t)u8_txBuffer[0]);
     u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[0] << 24)) 
                  | ((uint32_t)((uint32_t)u8_txBuffer[1] << 16)) 
                  | ((uint32_t)((uint32_t)u8_txBuffer[2] << 8));
    TLE9210x_ServLayer_SendSpiData();
}

/** \brief Prepare a get-Register message and calls the corresponding microcontroller SPI send function
 *
 *  \param u8_address address of the register to be read out
 * 
 *  \return void
 *
 */
void TLE9210x_ServLayer_getReg(uint8_t u8_address)
{
    u8_txBuffer[0] = (uint8_t)((u8_address << 1) | (uint8_t)TLE9210x_SPI_ACTION_READ);
    u8_txBuffer[0] = u8_txBuffer[0] | 0xC0u;
    u8_txBuffer[1] = (uint8_t)0x00;
    u8_txBuffer[2] = (uint8_t)0x00;
   // u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[2] << 16)) | ((uint32_t)((uint32_t)u8_txBuffer[1] << 8)) | ((uint32_t)u8_txBuffer[0]);
     u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[0] << 24)) 
                  | ((uint32_t)((uint32_t)u8_txBuffer[1] << 16)) 
                  | ((uint32_t)((uint32_t)u8_txBuffer[2] << 8));
    TLE9210x_ServLayer_SendSpiData();
}

void TLE9210x_ServLayer_getRegClr(uint8_t u8_address)
{
    u8_txBuffer[0] = (uint8_t)((u8_address << 1) | (uint8_t)TLE9210x_SPI_ACTION_WRITE);
    u8_txBuffer[0] = u8_txBuffer[0] | 0xC0u;
    u8_txBuffer[1] = (uint8_t)0x00;
    u8_txBuffer[2] = (uint8_t)0x00;
    // u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[2] << 16)) | ((uint32_t)((uint32_t)u8_txBuffer[1] << 8)) | ((uint32_t)u8_txBuffer[0]);
      u32_txBuffer = ((uint32_t)((uint32_t)u8_txBuffer[0] << 24)) 
                   | ((uint32_t)((uint32_t)u8_txBuffer[1] << 16)) 
                   | ((uint32_t)((uint32_t)u8_txBuffer[2] << 8));
    TLE9210x_ServLayer_SendSpiData();
}

