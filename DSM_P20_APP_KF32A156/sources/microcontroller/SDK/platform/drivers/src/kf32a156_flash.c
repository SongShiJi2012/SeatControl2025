/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_flash.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file provides the Flash function
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

/******************************************************************************
**                      		Include Files                                **
******************************************************************************/
#include "kf32a156_flash.h"

/**
  *   ##### FLASH程序存储器(FLASH)功能配置函数 #####
  */

void __attribute__((section(".indata"))) CHECK_RESTRICTION_RAM(int expr)
{
	while(!expr)
		;
}

/* 写特殊功能寄存器RAM */
static inline uint32_t   __attribute__((section(".indata"))) SFR_Config_RAM (uint32_t SfrMem, uint32_t SfrMask, uint32_t WriteVal)
{
    return ((SfrMem & SfrMask) | (WriteVal));
}

/**
  * 描述  配置FLASH非易失性存储器ECC使能。
  * 输入  NewState: FLASH非易失性存储器ECC使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void __attribute__((section(".indata"))) FLASH_NonVolatile_Memory_ECC_Enable_RAM (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 配置FLASH_CFG寄存器ECCREADEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能ECC校验 */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_ECCREADEN_POS));
    }
    else
    {
        /* 不使能ECC校验 */
        __asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_ECCREADEN_POS));
    }
}

/**
  * 描述  配置FLASH线性预取使能。
  * 输入  NewState: FLASH线性预取使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void __attribute__((section(".indata"))) FLASH_Linear_Prefetch_Enable_RAM (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 配置FLASH_CFG寄存器PREFETCHEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能线性预取 */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_PREFETCHEN_POS));
    }
    else
    {
        /* 不使能线性预取 */
    	__asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_PREFETCHEN_POS));
    }
}

/**
  * 描述  配置FLASH访问周期。
  * 输入  PeriodNum: FLASH访问系统周期个数，取值为1~16。
  * 返回  无。
  */
void __attribute__((section(".indata"))) FLASH_Period_Number_Config_RAM (uint32_t PeriodNum)
{
	uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION_RAM(CHECK_FLASH_PERIOD(PeriodNum));

    /*---------------- 配置FLASH_CFG寄存器TCFG位 ----------------*/
    tmpreg = (PeriodNum - 1) << FLASH_CFG_TCFG0_POS;
    FLASH_CFG = SFR_Config_RAM (FLASH_CFG,
                        ~FLASH_CFG_TCFG,
                        tmpreg);
}

/**
  * 描述  读FLASH计算完成状态。
  * 输入  无。
  * 返回  编程状态，1：计算完成，0：未计算或者计算中。
  */
FlagStatus __attribute__((section(".indata"))) FLASH_Get_Compute_Complete_Status_RAM (void)
{
    if (FLASH_STATE & FLASH_STATE_SIGDONE)
    {
        /* 计算完成 */
        return SET;
    }
    else
    {
        /* 未计算或者计算中 */
        return RESET;
    }
}

/**
  * 描述  清零FLASH计算完成状态。
  * 输入  无。
  * 返回  无。
  */
void __attribute__((section(".indata"))) FLASH_Clear_Compute_Complete_Status_RAM (void)
{
    /* 写 1 清零 */
    while((FLASH_STATE & FLASH_STATE_SIGDONE)>>FLASH_STATE_SIGDONE_POS)
    {
    	__asm volatile("SET [%0], #%1"::"r"(&(FLASH_STATE)),"i"(FLASH_STATE_SIGDONE_POS));
    }
}


/**
  * 描述  配置FLASH CheckSum首尾地址。
  * 输入  StartAddr: FLASH CheckSum的首地址，地址区间为0x0~0xFFFFF，硬件忽略低4位。
  *       StopAddr: FLASH CheckSum的尾地址，地址区间为0x0~0xFFFFF，硬件忽略低4位。
  * 返回  无。
  */
void  __attribute__((section(".indata"))) FLASH_CheckSum_Addr_Config_RAM(uint32_t StartAddr, uint32_t StopAddr)
{
    /* 参数校验 */
    CHECK_RESTRICTION_RAM(CHECK_FLASH_ADDR_20BITS(StartAddr));
    CHECK_RESTRICTION_RAM(CHECK_FLASH_ADDR_20BITS(StopAddr));

    FLASH_CSSTART = StartAddr;
    FLASH_CSSTOP = StopAddr;
}

/**
  * 描述  配置FLASH启动SIG计算使能。
  * 输入  NewState: FLASH启动SIG计算使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void  __attribute__((section(".indata"))) FLASH_Start_SIG_Compute_Enable_RAM (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 配置FLASH_CSSTOP寄存器SIGGO位 ----------------*/
    if (NewState != FALSE)
    {
        /* 启动SIG计算 */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CSSTOP)),"i"(FLASH_CSSTOP_SIGGO_POS));
    }
    else
    {
        /* 不启动SIG计算 */
        __asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CSSTOP)),"i"(FLASH_CSSTOP_SIGGO_POS));
    }
}

/**
  * 描述  获取FLASH CheckSum的结果。
  * 输入  CheckSumStruct: FLASH CheckSum信息结构体指针，
  *                       指针必须指向可写的地址空间。
  * 返回  无。
  */
void __attribute__((section(".indata"))) FLASH_Get_CheckSum_Result_RAM (FLASH_CheckSumResult* CheckSumStruct)
{
	uint32_t tmpreg;

    /*---------------- 配置FLASH_CSRESx寄存器CKSPRES位 ----------------*/
    tmpreg = FLASH_CSRES0;
    CheckSumStruct->m_ResultWord[0] = tmpreg;

    tmpreg = FLASH_CSRES1;
    CheckSumStruct->m_ResultWord[1] = tmpreg;

    tmpreg = FLASH_CSRES2;
    CheckSumStruct->m_ResultWord[2] = tmpreg;

    tmpreg = FLASH_CSRES3;
    CheckSumStruct->m_ResultWord[3] = tmpreg;
}

/**
  * 描述: 获取FLASH的ECC错误标志
  * 输入： 无。
  * 返回： 	0：FLASH的ECC结果正确
  * 	  	1：FLASH的ECC结果错误。
  **/
FlagStatus CACHE_Get_FLASH_ECC_Error_Flag(void)
{
	return ((CACHE_CTLR & PCLK_CTL3_FECCERRFLAG) >> PCLK_CTL3_FECCERRFLAG_POS);
}
/**
  * 描述: RAM的ECC校验错误中断使能
  * 输入： 	NewState : 	TRUE : RAM的ECC校验错误中断使能
  * 					FALSE : RAM的ECC校验错误中断禁止。
  * 返回： 无。
  **/
void CACHE_RAM_Check_ECC_Error_INT_Enable(FunctionalState NewState)
{
	uint32_t tmpreg;

	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	tmpreg = NewState << PCLK_CTL3_RECCERRIE_POS;
	CACHE_CTLR = SFR_Config(CACHE_CTLR, ~PCLK_CTL3_RECCERRIE, tmpreg);
}

/**
  * 描述: FLASH的ECC校验错误中断使能
  * 输入： 	NewState : 	TRUE : FLASH的ECC校验错误中断使能
  * 					FALSE : FLASH的ECC校验错误中断禁止。
  * 返回： 无。
  **/
void CACHE_FLASH_Check_ECC_Error_INT_Enable(FunctionalState NewState)
{
	uint32_t tmpreg;

	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	tmpreg = NewState << PCLK_CTL3_FECCERRIE_POS;
	CACHE_CTLR = SFR_Config(CACHE_CTLR, ~PCLK_CTL3_FECCERRIE, tmpreg);
}

