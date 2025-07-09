/**
 *  @file TLE9210x_HAL.c
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

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "TLE9210x_HAL.h"
//#include "PAL_Traveo.h"

/*******************************************************************************
**                        Global Variable Definitions                         **
*******************************************************************************/

/******************************************************************************/
/**                        Local Function Definitions                        **/
/******************************************************************************/

/** \brief Wait function
 *
 *  \note Within this function the microcontroller specific wait routine must be called
 * 
 *  \param u32_waitTime wait time in microseconds
 * 
 *  \return void
 */
void TLE9210x_WaitFor_us_HAL(uint32_t u32_waitTime)
{
  /* Place here the code for waiting */
  systick_delay_us(u32_waitTime);
}

/** \brief Initialize the SPI peripheral
 *
 *  \note Within this function the microcontroller specific SPI initialization routine must be called
 * 
 *  \return void
 */
void TLE9210x_InitSpiInterface_HAL(void)
{
  /* Call here microcontroller dependent SPI initialization function */
  Srvl_Tle9210x_SpiMasterInit();
}

/** \brief Perform an SPI transfer
 *
 *  \note Within this function the microcontroller specific SPI initialization routine must be called
 * 
 *  \param u32_sendBuffer data to be transmitted
 * 
 *  \return void
 */
void TLE9210x_SendSpiData_HAL(uint32_t u32_sendBuffer)
{
  /* Place here the code to transfer the u32_sendBuffer */
  Srvl_Tle9210x_SpiMasterSendData(u32_sendBuffer);
}

/** \brief Read out the SPI RX buffer of the microconroller
 *  
 *  \return void
 */
uint32_t TLE9210x_ReadSpiRxBuffer_HAL(void)
{
  /* Call SPI Read function here and write into rxBuffer */
  return Srvl_Tle9210x_SpiMasterReadData();
}

/** \brief Get the Status of the SPI interface
 * 
 *  Within this function the microcontroller specific SPI status function has to be implemented or called.
 *  The result has to be returned by this function.
 *  
 *  \return uint8_t status of SPI transfer
 */
uint8_t TLE9210x_SpiInterfaceStatus_HAL(void)
{
  /* Call SPI status function here */
  return TRUE;
}


/** @}*/ /* End of group TLE9210x_HAL_C */