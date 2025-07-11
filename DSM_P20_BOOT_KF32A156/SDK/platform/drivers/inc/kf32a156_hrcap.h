/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_hrcap.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
 *  @Description      : This file contains the headers of the HRCAP
 *                        peripherals.                                          
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/
#ifndef KF32A156_HRCAP_H_
#define KF32A156_HRCAP_H_

#include "KF32A156.h"


/**
  * HRCAP内存指针
  */
#define CHECK_HRCAP_ALL_PERIPH(PERIPH)    (((PERIPH) == HRCAP0_SFR) \
                                        || ((PERIPH) == HRCAP1_SFR) \
                                        || ((PERIPH) == HRCAP2_SFR))

/**
 * 	HRCAPx模块工作时钟选择
 * */
#define HRCAP_CLK_SCLK						((uint32_t)0)
#define HRCAP_CLK_HFCLK						((uint32_t)1)
#define HRCAP_CLK_LFCLK						((uint32_t)3)
#define CHECK_HRCAP_CLK(CLK)				((CLK) <= HRCAP_CLK_LFCLK)


/**
 * 	HRCAPx捕捉输入选择
 * */
#define HRCAP_EXTERNAL_INPUT				((uint32_t)0)
#define HRCAP_HRPWMX_OUTPUT					((uint32_t)1)
#define CHECK_HRCAP_CAP_INPUT(SELECT)		((SELECT) <= HRCAP_HRPWMX_OUTPUT)

/**
 * 	16值校验
 * */
#define CHECK_HRCAP_16BIT_VALUE(VALUE)		((VALUE) <= 0xFFFF)

/**
 * 	寄存器0/1校验
 * */
#define HRCAP_REGISTER0					((uint32_t)0)
#define HRCAP_REGISTER1					((uint32_t)1)
#define CHECK_HRCAP_CAP_REGISTER(REG)	((REG) <= HRCAP_REGISTER1)

/**
 * 	中断标志位
 * */
#define HRCAP_RISEOVER_INT					((uint32_t)3)
#define HRCAP_COUNTOVER_INT					((uint32_t)2)
#define HRCAP_FALL_INT						((uint32_t)1)
#define HRCAP_RISE_INT						((uint32_t)0)
#define CHECK_HRCAP_INT(SELECT)				((SELECT) <= HRCAP_COUNTOVER_INT)
#define CHECK_HRCAP_INT_FLAG(SELECT)		((SELECT) <= HRCAP_RISEOVER_INT)

/**
 * 	中断标志位强制置位
 * */
#define CHECK_HRCAP_MANDATORY_INT(SELECT)	((SELECT) <= HRCAP_COUNTOVER_INT)


void HRCAP_Reset (HRCAP_SFRmap* HRCAPx);
void HRCAP_CLK_Select(HRCAP_SFRmap* HRCAPx, uint32_t CLK);
void HRCAP_Software_Reset_Enable(HRCAP_SFRmap* HRCAPx, FunctionalState NewState);
void HRCAP_INT_Enable(HRCAP_SFRmap* HRCAPx, uint32_t Select, FunctionalState NewState);
void HRCAP_Cap_Input_Select(HRCAP_SFRmap* HRCAPx, uint32_t Select);
uint16_t HRCAP_Read_Latch_Count_Value(HRCAP_SFRmap* HRCAPx);
uint16_t HRCAP_Read_Count_Value(HRCAP_SFRmap* HRCAPx);
uint16_t HRCAP_Read_Rise_Integer_Value(HRCAP_SFRmap* HRCAPx, uint32_t HRCAP_REG);
uint16_t HRCAP_Read_Fall_Integer_Value(HRCAP_SFRmap* HRCAPx, uint32_t HRCAP_REG);
uint16_t HRCAP_Read_Rise_Decimal_Value(HRCAP_SFRmap* HRCAPx, uint32_t HRCAP_REG);
uint16_t HRCAP_Read_Fall_Decimal_Value(HRCAP_SFRmap* HRCAPx, uint32_t HRCAP_REG);
FlagStatus HRCAP_Get_INT_Flag(HRCAP_SFRmap* HRCAPx, uint32_t Select);
RetStatus HRCAP_Clear_INT_Flag(HRCAP_SFRmap* HRCAPx, uint32_t Select);
void HRCAP_INT_Mandatory_Enable(HRCAP_SFRmap* HRCAPx, uint32_t Select, FunctionalState NewState);




#endif /* KF32A156_HRCAP_H_ */
