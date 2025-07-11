/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : KF32A156Config.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
 *  @Description      : This file contains the Peripheral resources file
 *                      configuration for KF32A156 device.In order to         
 *                      distinguish the resources of each model,Users are     
 *                      forbidden to modify this file, otherwise MCU may      
 *                      not work or breakdown                                                  
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

#ifndef KF32A156CONFIG_H_
#define KF32A156CONFIG_H_

/******************************************************************************
**                       	Include Files                                    **
******************************************************************************/
#include "__Kungfu32_chipmodel_define.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*!< ADC Peripheral configuration >*/
#define KF32A_PERIPH_ADC0
#define KF32A_PERIPH_ADC1
#define KF32A_PERIPH_ADC2

/*!< AES  Peripheral configuration >*/
#define KF32A_PERIPH_AES

/*!< ATIM Peripheral configuration >*/
#define KF32A_PERIPH_ATIME5
#define KF32A_PERIPH_ATIME6

/*!< BTIM Peripheral configuration >*/
#define KF32A_PERIPH_BTIME14

/*!< CAN  Peripheral configuration >*/
#define KF32A_PERIPH_CAN
#define KF32A_PERIPH_CANFD0
#define KF32A_PERIPH_CANFD1

/*!< CFGL Peripheral configuration >*/
#define KF32A_PERIPH_CFGL

/*!< CMP  Peripheral configuration >*/
#define KF32A_PERIPH_CMP

/*!< DAC  Peripheral configuration >*/
#define KF32A_PERIPH_DAC

/*!< DMA  Peripheral configuration >*/
#define KF32A_PERIPH_DMA

/*!< ECFGL Peripheral configuration >*/
#define KF32A_PERIPH_ECFGL

/*!< EXIC Peripheral configuration >*/
#define KF32A_PERIPH_EXIC

/*!< FDC  Peripheral configuration >*/
#define KF32A_PERIPH_FDC

/*!< FLEXMUX Peripheral configuration >*/
#define KF32A_PERIPH_FLEMUX

/*!< GTIM Peripheral configuration >*/
#define KF32A_PERIPH_GTIME0
#define KF32A_PERIPH_GTIME1
#define KF32A_PERIPH_GTIME2
#define KF32A_PERIPH_GTIME3
#define KF32A_PERIPH_GTIME4
#define KF32A_PERIPH_GTIME18
#define KF32A_PERIPH_GTIME19
#define KF32A_PERIPH_GTIME21

/*!< HRCAP Peripheral configuration >*/
#define KF32A_PERIPH_HRCAP

/*!< I2C  Peripheral configuration >*/
#define KF32A_PERIPH_IIC0
#define KF32A_PERIPH_IIC1
#define KF32A_PERIPH_IIC2
#define KF32A_PERIPH_IIC3

/*!< OP   Peripheral configuration >*/
#define KF32A_PERIPH_OP

/*!< QEI   Peripheral configuration >*/
#define KF32A_PERIPH_QEI0
#define KF32A_PERIPH_QEI1

/*!< SPI   Peripheral configuration >*/
#define KF32A_PERIPH_SPI0
#define KF32A_PERIPH_SPI1
#define KF32A_PERIPH_SPI2
#define KF32A_PERIPH_SPI3

/*!< USART Peripheral configuration >*/
#define KF32A_PERIPH_USART0
#define KF32A_PERIPH_USART1
#define KF32A_PERIPH_USART2
#define KF32A_PERIPH_USART3

#endif /* KF32A156CONFIG_H_ */
