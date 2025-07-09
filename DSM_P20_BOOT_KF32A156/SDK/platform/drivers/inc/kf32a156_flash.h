/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_flash.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
 *  @Description      : This file contains the headers of the FLASH
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/
#ifndef KF32A156_FLASH_H_
#define KF32A156_FLASH_H_


#include "KF32A156.h"

/**
  * 描述  FLASH CheckSum结果数据结构体
  */
typedef union CheckSumStruct
{
    uint32_t m_ResultWord[4];     /* CheckSum的128位结果，字访问。 */
    uint32_t m_ResultShort[8];    /* CheckSum的128位结果，半字访问。 */
    uint32_t m_ResultByte[16];    /* CheckSum的128位结果，字节访问。 */
}FLASH_CheckSumResult;

/**
  * 描述  FLASH编程信息结构体
  */
#define CHECK_FLASH_PERIOD(NUM)         (((uint32_t)(NUM) >> 4) == 0)

/**
  * FLASH编程和行擦期间的地址
  */
#define CHECK_FLASH_ADDR_20BITS(ADDR)   (((uint32_t)(ADDR) >> 20) == 0)
#define CHECK_FLASH_ADDR_13BITS(ADDR)   (((uint32_t)(ADDR) >> 13) == 0)

/* FLASH程序存储器(FLASH)功能配置函数定义**************************/
void FLASH_NonVolatile_Memory_ECC_Enable_RAM (FunctionalState NewState);
void FLASH_Linear_Prefetch_Enable_RAM (FunctionalState NewState);
void FLASH_Period_Number_Config_RAM (uint32_t PeriodNum);
FlagStatus FLASH_Get_Program_Status_RAM (void);
FlagStatus FLASH_Get_Wipe_Status_RAM (void);
FlagStatus FLASH_Get_Compute_Complete_Status_RAM (void);
void FLASH_Clear_Compute_Complete_Status_RAM (void);

#if _CLOSE_SERVICE_
FlagStatus FLASH_Get_CFG_Error_Flag_RAM (void);
void FLASH_Clear_CFG_Error_Flag_RAM (void);
#endif /* _CLOSE_SERVICE_ */

void FLASH_CheckSum_Addr_Config_RAM(uint32_t StartAddr, uint32_t StopAddr);
void FLASH_Start_SIG_Compute_Enable_RAM (FunctionalState NewState);
void FLASH_Get_CheckSum_Result_RAM (FLASH_CheckSumResult* CheckSumStruct);
/* FLASH程序存储器(FLASH)编程功能函数定义**************************/

FlagStatus FLASH_Get_Program_Status (void);
FlagStatus FLASH_Get_Wipe_Status (void);


/* 指令缓存寄存器(CACHE)编程功能函数定义**************************/
FlagStatus CACHE_Get_CACHE_ECC_Error_Flag(void);
FlagStatus CACHE_Get_FLASH_ECC_Error_Flag(void);
void CACHE_RAM_Check_ECC_Error_INT_Enable(FunctionalState NewState);
void CACHE_CACHE_Check_ECC_Error_INT_Enable(FunctionalState NewState);
void CACHE_FLASH_Check_ECC_Error_INT_Enable(FunctionalState NewState);
void CACHE_CACHE_Check_ECC_Enable(FunctionalState NewState);
void CACHE_Instruction_CACHE_Read_2Row_Enable(FunctionalState NewState);
void CACHE_Instruction_CACHE_Write_2Row_Enable(FunctionalState NewState);
void CACHE_CACHE_Reset_Enable(FunctionalState NewState);
void CACHE_CACHE_Enable(FunctionalState NewState);



#endif /* KF32A156_FLASH_H_ */
