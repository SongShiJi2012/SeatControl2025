/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  *
 ******************************************************************************
 *  $File Name$       : main.c                                         	      *
 *  $Author$          : ChipON AE/FAE Group                                   *
 *  $Data$            : 2021-07-8                                             *
 *  $Hard Version     : KF32A156-MINI-EVB_V1.2                                *
 *  $Description$     : This file provides a routine for SPI slave DMA mode   *
 ******************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 *
 *  All rights reserved.                                                      *
 *                                                                            *
 *  This software is copyright protected and proprietary to                    *
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 *
 ******************************************************************************
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  *
 *                     		REVISON HISTORY                               	  *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  *
 *  Data       Version  Author        Description                             *
 *  ~~~~~~~~~~ ~~~~~~~~ ~~~~~~~~~~~~  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  *
 *  2021-07-08 00.02.00 FAE Group     Version 2.0 update                      *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/

/******************************************************************************
**                             Include Files                                **
******************************************************************************/
#include "SPI.h"

/*****************************************************************************
**                         Private Macro Definitions                        **
*****************************************************************************/

/*****************************************************************************
**                         Private Variables Definitions                    **
*****************************************************************************/
uint8_t Tx_Master[SPI_TRANSMISSION_DATA_SIZE] = "KF32A156-KungFu32 SPI Example master";
uint8_t Spi_ReadData[SPI_TRANSMISSION_DATA_SIZE];
/*****************************************************************************
**                             Private Functions                            **
*****************************************************************************/

/*****************************************************************************
**                             Global Functions                            **
*****************************************************************************/
/**
 *  @brief: Initialize the spi module
 *  @param in: SPIx
 *  @param out : None
 *  @retval : None
 */
void Spi_Init(SPI_SFRmap *SPIx)
{
    SPI_InitTypeDef Spi_ConfigPtr;

    /* SPI mode */
    Spi_ConfigPtr.m_Mode = SPI_MODE_MASTER_CLKDIV4;
    /* SPI clock */
    Spi_ConfigPtr.m_Clock = SPI_CLK_SCLK;
    /* Data transfer start control */
    Spi_ConfigPtr.m_FirstBit = SPI_FIRSTBIT_MSB;
    /* Spi idle state */
    Spi_ConfigPtr.m_CKP = SPI_CKP_LOW;
    /* Spi clock phase(Data shift edge) */
    Spi_ConfigPtr.m_CKE = SPI_CKE_2EDGE;
    /* Data width */
    Spi_ConfigPtr.m_DataSize = SPI_DATASIZE_8BITS;
    /* Baud rate :Fck_spi=Fck/2(m_BaudRate+1)*/
    //Spi_ConfigPtr.m_BaudRate = 0x0E;//1M
    Spi_ConfigPtr.m_BaudRate = 0x02;//5M

    /* Spi reset */
    SPI_Reset(SPIx);
    /* Configure SPI module */
    SPI_Configuration(SPIx, &Spi_ConfigPtr);
    /* Enable SPI module */
    SPI_Cmd(SPIx, TRUE);
}

/**
 *  @brief: Initialize the SPI IO
 *  @param in: None
 *  @param out : None
 *  @retval : None
 */
void Spi_IO_Init()
{
    /* Configure SPI2 IO */
    /* 
     * SPI0_SCK = PD14
     * SPI0_SDI = PH1
     * SPI0_SDO = PA2
     * SPI0_SS0 = PA1
     */
    GPIO_Write_Mode_Bits(GPIOA_SFR, GPIO_PIN_MASK_2, GPIO_MODE_RMP);
    GPIO_Write_Mode_Bits(GPIOH_SFR, GPIO_PIN_MASK_1, GPIO_MODE_RMP);
    GPIO_Write_Mode_Bits(GPIOD_SFR, GPIO_PIN_MASK_14, GPIO_MODE_RMP);

    //GPIO_Pin_RMP_Config(GPIOA_SFR, GPIO_Pin_Num_1, GPIO_RMP_AF4);
    GPIO_Pin_RMP_Config(GPIOA_SFR, GPIO_Pin_Num_2, GPIO_RMP_AF4);
    GPIO_Pin_RMP_Config(GPIOH_SFR, GPIO_Pin_Num_1, GPIO_RMP_AF9);
    GPIO_Pin_RMP_Config(GPIOD_SFR, GPIO_Pin_Num_14, GPIO_RMP_AF9);
}
