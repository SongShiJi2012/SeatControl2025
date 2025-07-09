/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_osc.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file contains the headers of the OSC
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/
#ifndef KF32A156_OSC_H_
#define KF32A156_OSC_H_

#include "KF32A156.h"

/*** 振荡器(OSC)相关定义  */

/**
  * 描述  振荡器(OSC) SCLK主时钟配置信息结构体
  */
typedef struct
{
    uint32_t m_InputSource;     /* 振荡源选择，根据不同的时钟，取值不同，
                                   	   取值满足“SCLK振荡源选择”、“HFCK振荡源选择”、“LFCK振荡源选择”、
                                   	   “CK48M振荡源选择”定义的一个。 */
    uint32_t m_CLKDivision;     /* 时钟分频系数，
                                   	   取值满足“SCLK分频系数”、“HFCK分频系数”、“LFCK分频系数”、
                                   “CK48M分频系数”定义的一个。 */
    uint32_t m_PLLInputSource;  /* PLL输入时钟源选择，当振荡源为PLL时有效，
                                   	   取值为宏“PLL输入时钟源选择”中的一个。 */

    uint32_t m_StartDelay;      /* PLL 或 外部启动延时时间配置，当振荡源为PLL或外部时有效，
                                   	   取值为宏“PLL启动延时时间配置”或“外部启动延时时间配置”中的一个。 */
} OSC_InitTypeDef;

/**
  * LFCK分频系数
  */
#define LFCK_DIVISION_1                 ((uint32_t)0x0)
#define LFCK_DIVISION_2                 ((uint32_t)0x1)
#define LFCK_DIVISION_4                 ((uint32_t)0x2)
#define LFCK_DIVISION_8                 ((uint32_t)0x3)
#define LFCK_DIVISION_16                ((uint32_t)0x4)
#define LFCK_DIVISION_32                ((uint32_t)0x5)
#define LFCK_DIVISION_64                ((uint32_t)0x6)
#define LFCK_DIVISION_128               ((uint32_t)0x7)
#define CHECK_LFCK_DIVISION(LFCK)       ((uint32_t)(LFCK) <= LFCK_DIVISION_128)

/**
  * HFCK分频系数
  */
#define HFCK_DIVISION_1                 ((uint32_t)0x0)
#define HFCK_DIVISION_2                 ((uint32_t)0x1)
#define HFCK_DIVISION_4                 ((uint32_t)0x2)
#define HFCK_DIVISION_8                 ((uint32_t)0x3)
#define HFCK_DIVISION_16                ((uint32_t)0x4)
#define HFCK_DIVISION_32                ((uint32_t)0x5)
#define HFCK_DIVISION_64                ((uint32_t)0x6)
#define HFCK_DIVISION_128               ((uint32_t)0x7)
#define HFCK_DIVISION_256               ((uint32_t)0x8)
#define HFCK_DIVISION_512               ((uint32_t)0x9)
#define CHECK_HFCK_DIVISION(HFCK)       ((uint32_t)(HFCK) <= HFCK_DIVISION_512)

/**
  * SCLK分频系数
  */
#define SCLK_DIVISION_1                 ((uint32_t)0x0)
#define SCLK_DIVISION_2                 ((uint32_t)0x1)
#define SCLK_DIVISION_4                 ((uint32_t)0x2)
#define SCLK_DIVISION_8                 ((uint32_t)0x3)
#define SCLK_DIVISION_16                ((uint32_t)0x4)
#define SCLK_DIVISION_32                ((uint32_t)0x5)
#define SCLK_DIVISION_64                ((uint32_t)0x6)
#define SCLK_DIVISION_128               ((uint32_t)0x7)
#define CHECK_SCLK_DIVISION(SCLK)       ((uint32_t)(SCLK) <= SCLK_DIVISION_128)

/**
 * PLL时钟源分频选择
 * */
#define PLL_SOURCE_DIV_1                ((uint32_t)0x0)
#define PLL_SOURCE_DIV_2                ((uint32_t)0x1)
#define CHECK_PLL_DIVISION(SEL)         ((uint32_t)(SEL) <= PLL_SOURCE_DIV_2)

/**
  * PLL输入时钟源选择
  */
#define PLL_INPUT_INTHF                 ((uint32_t)0x0)
#define PLL_INPUT_EXTHF                 ((uint32_t)0x1)
#define CHECK_PLL_INPUT(CFG)            (((CFG) >> 0x01) == 0x00)

/**
  * HFCK振荡源选择
  */
#define HFCK_SOURCE_INTHF               ((uint32_t)0x0)
#define HFCK_SOURCE_EXTHF               ((uint32_t)0x2)
#define HFCK_SOURCE_PLL                 ((uint32_t)0x4)
#define HFCK_SOURCE_LP4M				((uint32_t)0x6)
#define CHECK_HFCK_SOURCE(HFCK)         (((HFCK) >> 0x03) == 0x00)

/**
  * LFCK振荡源选择
  */
#define LFCK_INPUT_INTLF                ((uint32_t)0x0)
#define LFCK_INPUT_EXTLF                ((uint32_t)0x1)
#define CHECK_LFCK_INPUT(LFCK)          ((LFCK) <= LFCK_INPUT_EXTLF)

/**
  * SCLK振荡源选择
  */
#define SCLK_SOURCE_INTHF               ((uint32_t)0x0)
#define SCLK_SOURCE_INTLF               ((uint32_t)0x1)
#define SCLK_SOURCE_EXTHF               ((uint32_t)0x2)
#define SCLK_SOURCE_EXTLF               ((uint32_t)0x3)
#define SCLK_SOURCE_PLL                 ((uint32_t)0x4)
#define SCLK_SOURCE_LP4M                ((uint32_t)0x6)
#define CHECK_SCLK_SOURCE(SCLK)         (((SCLK) >> 0x03) == 0x00)
/**
  * CLKOUT输出时钟分频
  */
#define CLKOUT_DIVISION_1				((uint32_t)0x0)
#define CLKOUT_DIVISION_2				((uint32_t)0x1)
#define CLKOUT_DIVISION_4				((uint32_t)0x2)
#define CLKOUT_DIVISION_8				((uint32_t)0x3)
#define CLKOUT_DIVISION_16				((uint32_t)0x4)
#define CLKOUT_DIVISION_32				((uint32_t)0x5)
#define CLKOUT_DIVISION_64				((uint32_t)0x6)
#define CLKOUT_DIVISION_128				((uint32_t)0x7)
#define CHECK_CLOOUT_DIVISION(DIV)		(((DIV) >> 0x03) == 0x00)

/**
  * CLKOUT输出时钟选择
  */
#define CLKOUT_SCLK                      ((uint32_t)0x0)
#define CLKOUT_EXTLF                     ((uint32_t)0x1)
#define CLKOUT_EXTHF                     ((uint32_t)0x2)
#define CLKOUT_INTLF                     ((uint32_t)0x3)
#define CLKOUT_INTHF                     ((uint32_t)0x4)
#define CLKOUT_PLL                       ((uint32_t)0x5)
#define CLKOUT_LP4M				         ((uint32_t)0x6)
#define CHECK_CLKOUT_SEL(CLKOUT)         (((CLKOUT) >> 0x03) == 0x00)

/**
 * FSCM_DIVISION时钟故障检测分频
 */
#define FSCM_DIVISION_1				 	 ((uint32_t)0x0)
#define FSCM_DIVISION_2				 	 ((uint32_t)0x1)
#define FSCM_DIVISION_4				 	 ((uint32_t)0x2)
#define FSCM_DIVISION_8				 	 ((uint32_t)0x3)
#define FSCM_DIVISION_16				 ((uint32_t)0x4)
#define FSCM_DIVISION_32				 ((uint32_t)0x5)
#define FSCM_DIVISION_64				 ((uint32_t)0x6)
#define FSCM_DIVISION_128				 ((uint32_t)0x7)
#define CHECK_FSMC_DIVISION(DIV)		 (((DIV) >> 0x03) == 0x00)

/**
 * FSCM_SOURCE时钟故障检测源
 */
#define FSCM_SOURCE_EXTHF				 ((uint32_t)0x0)
#define FSCM_SOURCE_INTHF				 ((uint32_t)0x4)
#define CHECK_FSCM_SOURCE(SOURCE)		 (((SOURCE) >> 0x03) == 0x00)

/**
  * PLL启动延时时间配置
  */
#define PLL_START_DELAY_64              ((uint32_t)0x00)
#define PLL_START_DELAY_128             ((uint32_t)0x01)
#define PLL_START_DELAY_256             ((uint32_t)0x02)
#define PLL_START_DELAY_512             ((uint32_t)0x03)
#define PLL_START_DELAY_1024            ((uint32_t)0x04)
#define PLL_START_DELAY_2048            ((uint32_t)0x05)
#define PLL_START_DELAY_4096            ((uint32_t)0x06)
#define PLL_START_DELAY_8192            ((uint32_t)0x07)
#define PLL_START_DELAY_16384           ((uint32_t)0x08)
#define PLL_START_DELAY_32768           ((uint32_t)0x09)
#define CHECK_PLL_START_DELAY(PLL)      (((PLL) >> 0x04) == 0x00)

/**
  * 外部启动延时时间配置
  */
#define EXT_START_DELAY_256              ((uint32_t)0x00)
#define EXT_START_DELAY_512              ((uint32_t)0x01)
#define EXT_START_DELAY_1024             ((uint32_t)0x02)
#define EXT_START_DELAY_2048             ((uint32_t)0x03)
#define EXT_START_DELAY_4096             ((uint32_t)0x04)
#define EXT_START_DELAY_8192             ((uint32_t)0x05)
#define EXT_START_DELAY_16384            ((uint32_t)0x06)
#define EXT_START_DELAY_32768            ((uint32_t)0x07)
#define EXT_START_DELAY_65536            ((uint32_t)0x08)
#define EXT_START_DELAY_131072           ((uint32_t)0x09)
#define CHECK_EXT_START_DELAY(EXT)       (((EXT) >> 0x04) == 0x00)

/**
  * PLL分频系数
  */
#define CHECK_PLL_MULTIPLE_NValue(MUL)         ((uint32_t)(MUL) <= 0xF)
#define CHECK_PLL_MULTIPLE_MValue(MUL)         ((uint32_t)(MUL) <= 0x3FFF)

#define PLL_MULTIPLE_NOValue_8	(8)
#define PLL_MULTIPLE_NOValue_4	(4)
#define PLL_MULTIPLE_NOValue_2	(2)
#define PLL_MULTIPLE_NOValue_1	(1)
#define CHECK_PLL_MULTIPLE_NOValue(MUL)         (((MUL) == PLL_MULTIPLE_NOValue_1) \
											  || ((MUL) == PLL_MULTIPLE_NOValue_2) \
											  || ((MUL) == PLL_MULTIPLE_NOValue_4) \
											  || ((MUL) == PLL_MULTIPLE_NOValue_8))



/**
 * 时钟中断标志位/使能
 * */
#define OSC_INT_INTLF					((uint32_t)0)
#define OSC_INT_INTHF					((uint32_t)1)
#define OSC_INT_EXTLF					((uint32_t)2)
#define OSC_INT_EXTHF					((uint32_t)3)
#define OSC_INT_PLL						((uint32_t)4)
#define OSC_INT_LP4M					((uint32_t)6)
#define OSC_INT_CKF						((uint32_t)7)
#define CHECK_OSC_INT_FLAG(SEL)			(((SEL) == OSC_INT_INTLF) \
									  || ((SEL) == OSC_INT_INTHF) \
									  || ((SEL) == OSC_INT_EXTLF) \
									  || ((SEL) == OSC_INT_EXTHF) \
									  || ((SEL) == OSC_INT_PLL) \
									  || ((SEL) == OSC_INT_LP4M) \
									  || ((SEL) == OSC_INT_CKF))

#define CHECK_OSC_INT_ENABLE(SEL)		(((SEL) == OSC_INT_INTLF) \
									  || ((SEL) == OSC_INT_INTHF) \
									  || ((SEL) == OSC_INT_EXTLF) \
									  || ((SEL) == OSC_INT_EXTHF) \
									  || ((SEL) == OSC_INT_PLL) \
									  || ((SEL) == OSC_INT_LP4M))

/* 振荡器(OSC)外设初始化函数****************************************/
void OSC_SCLK_Configuration (OSC_InitTypeDef* oscInitStruct);
void OSC_HFCK_Configuration (OSC_InitTypeDef* oscInitStruct);
void OSC_LFCK_Configuration (OSC_InitTypeDef* oscInitStruct);
void OSC_Struct_Init (OSC_InitTypeDef* oscInitStruct);
/* 振荡器(OSC)功能配置函数******************************************/
void OSC_LFCK_Division_Config (uint32_t LFDivision);
void OSC_HFCK_Division_Config (uint32_t HFDivision);
void OSC_PLL_Division_Config(uint32_t PLLDivision);
void OSC_SCK_Division_Config (uint32_t SclkDivision);
void OSC_PLL_Input_Source_Config (uint32_t NewState);
void OSC_HFCK_Source_Config (uint32_t HFSource);
void OSC_HFCK_Enable (FunctionalState NewState);
void OSC_LFCK_Source_Config (uint32_t NewState);
void OSC_LFCK_Enable (FunctionalState NewState);
void OSC_SCK_Source_Config (uint32_t SclkSource);
void OSC_Backup_Write_Read_Enable (FunctionalState NewState);
void OSC_SCLK_Output_Enable (FunctionalState NewState);
void OSC_SCLK_Output_Select (uint32_t ClkSource);
void OSC_SCLK_Output_Division_Config (uint32_t OutputDivision);
void OSC_Clock_Failure_Check_Enable (FunctionalState NewState);
void OSC_Clock_Failure_Check_Division_Config (uint32_t FSCM_DIV);
void OSC_Clock_Failure_Check_Source_Config (uint32_t FSCM_Source);
void OSC_PLL_Multiple_Value_Select (uint32_t PLLmultiple_M,uint32_t PLLmultiple_N,uint32_t PLLmultiple_NO);
void OSC_PLL_RST(void);
void OSC_PLL_Start_Delay_Config (uint32_t PLLDelay);
void OSC_EXTHF_Start_Delay_Config (uint32_t ExternalDelay);
void OSC_EXTLF_Start_Delay_Config (uint32_t ExternalDelay);
void OSC_LP4M_Software_Enable (FunctionalState NewState);
void OSC_PLL_Software_Enable (FunctionalState NewState);
void OSC_EXTHF_Software_Enable (FunctionalState NewState);
void OSC_EXTLF_Software_Enable (FunctionalState NewState);
void OSC_INTHF_Software_Enable (FunctionalState NewState);
void OSC_INTLF_Software_Enable (FunctionalState NewState);
/* 振荡器(OSC)中断控制函数******************************************/
void OSC_LP4M_INT_Enable (FunctionalState NewState);
void OSC_PLL_INT_Enable (FunctionalState NewState);
void OSC_EXTHF_INT_Enable (FunctionalState NewState);
void OSC_EXTLF_INT_Enable (FunctionalState NewState);
void OSC_INTHF_INT_Enable (FunctionalState NewState);
void OSC_INTLF_INT_Enable (FunctionalState NewState);
FlagStatus OSC_Get_Clock_Failure_INT_Flag (void);
FlagStatus OSC_Get_LP4MIF_INT_Flag (void);
FlagStatus OSC_Get_PLL_INT_Flag (void);
FlagStatus OSC_Get_EXTHF_INT_Flag (void);
FlagStatus OSC_Get_EXTLF_INT_Flag (void);
FlagStatus OSC_Get_INTHF_INT_Flag (void);
FlagStatus OSC_Get_INTLF_INT_Flag (void);

void OSC_INT_Enable(uint32_t InterruptType, FunctionalState NewState);
FlagStatus OSC_Get_INT_Flag(uint32_t InterruptType);
void OSC_Clear_INT_Flag(uint32_t InterruptType);

#endif /* KF32A156_OSC_H_ */
