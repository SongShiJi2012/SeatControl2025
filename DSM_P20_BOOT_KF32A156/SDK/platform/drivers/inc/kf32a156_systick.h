/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_systick.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
 *  @Description      : This file contains the headers of the SYSTICK
 *                        peripherals.                                          
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/
#ifndef KF32A156_SYSTICK_H_
#define KF32A156_SYSTICK_H_

#include "KF32A156.h"

/* 节拍定时器指针定义 */
#define CHECK_SYSTICK_PERIPH(PERIPH)    ((PERIPH) == SYSTICK_SFR)

/**
  * 描述  节拍定时器(SYSTICK)配置信息结构体
  */
typedef struct
{
    uint32_t m_Period;          /* 节拍定时器重加载寄存器的值，取值24位数据。 */
    uint32_t m_Clock;           /* 节拍定时器的时钟源选择，
                                   取值为宏“SYSTICK定时器时钟源”中的一个。 */
    uint32_t m_SysTickINT;      /* 定时器SysTick中断使能配置，
                                   取值为TRUE或FALSE。 */
} SYSTICK_InitTypeDef;


/**
  * SYSTICK定时器时钟源
  */
#define SYSTICK_SYS_CLOCK_DIV_2         ((uint32_t)0x0 << ST_CTL_STCLKS_POS)
#define SYSTICK_SYS_CLOCK_DIV_1         ((uint32_t)0x1 << ST_CTL_STCLKS_POS)
#define CHECK_SYSTICK_CLOCK(SCLK)       (((SCLK) == SYSTICK_SYS_CLOCK_DIV_2) \
                                      || ((SCLK) == SYSTICK_SYS_CLOCK_DIV_1))

/**
  * SYSTICK定时器重加载寄存器的值
  */
#define CHECK_SYSTICK_RELOAD(SYS)       (((SYS) >> 24) == 0)

/* 节拍定时器(SYSTICK)外设初始化函数定义************************************/
void SYSTICK_Configuration (uint32_t Clock, uint32_t SysTickINT,uint32_t Reload);

/* 节拍定时器(SYSTICK)功能配置函数定义**************************************/
void SYSTICK_Cmd (FunctionalState NewState);
void SYSTICK_Clock_Config (uint32_t SysClock);
void SYSTICK_Systick_INT_Enable (uint32_t SysClock);
FlagStatus SYSTICK_Get_Count_Zero_Flag (void);
void SYSTICK_Reload_Config (uint32_t Reload);
void SYSTICK_Counter_Updata (void);
uint32_t SYSTICK_Get_Reload (void);
uint32_t SYSTICK_Get_Counter (void);

#endif /* KF32A156_SYSTICK_H_ */
