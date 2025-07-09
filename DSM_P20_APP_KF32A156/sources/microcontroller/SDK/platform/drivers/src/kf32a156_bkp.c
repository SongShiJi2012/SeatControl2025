/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_bkp.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file provides the backup domain (BKP)
 *                      peripherals function, including:                      
 *                      + Backup filed (BKP) reset and read-write allow       
 *                        functions                                              
 *                      + Backup domain (BKP) functional configuration           
 *                        function                                            
 *                          + Backup domain (BKP) interrupt management function      
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
#include "kf32a156_bkp.h"
static volatile uint32_t BkpEnterCounter = 0u;

static uint32_t Intr_Enter_Critical(void);
static void Intr_Exit_Critical(uint32_t v);

/**
  *   ##### 备份域(BKP)复位及读写允许函数 #####
  */
/**
  * 描述  复位备份域(BKP)外设，该函数仅复位备份域寄存器组，而不复位RTC模块。
  * 输入  无。
  * 返回  无。
  */
void BKP_Reset (void)
{
    /* 备份域寄存器组软件复位 */
    SFR_SET_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    SFR_CLR_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
}

/**
  * 描述  备份域(BKP)寄存器组读写时，需要对如下寄存器位进行配置：
  *         1.  OSCCTL0寄存器的PMWREN位置1，允许整个备份域的读写操作；
  *         2.  PM_CTL0寄存器的BKPREGCLR位置1，寄存器组退出复位；
  *         3.  PM_CTL0寄存器的BKPWR位置1，允许备份域数据寄存器组和RTC模块内的寄存器读写操作。
  *       读写寄存器组前调用该函数，结束读写后必须再次调用该函数，若缺少或多次调用则会无法恢复原始配置。
  * 输入  NewState: 备份域寄存器组读写配置使能，取值范围为：
  *                   TRUE: 备份域寄存器组读写前的配置
  *                   FALSE: 备份域寄存器组读写后的配置恢复
  * 返回  无。
  */
void BKP_Write_And_Read_Enable (FunctionalState NewState)
{
    uint32_t r = 0u;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));
    if (NewState != FALSE)
    {
        r = Intr_Enter_Critical();
        if (0u == BkpEnterCounter)
        {
            /* 允许整个备份域的读写操作 */
            SFR_SET_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
            /* 寄存器组退出复位 */
            SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPREGCLR_POS);
            /* 允许备份域数据寄存器组和RTC模块内的寄存器读写操作 */
            SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
        }
        else
        { /*Empty*/
        }
        BkpEnterCounter++;
        Intr_Exit_Critical(r);
    }
    else
    {
        r = Intr_Enter_Critical();
        if (BkpEnterCounter != 0)
        {
          BkpEnterCounter--;
        }
        else
        {
          /* code */
        }
        
        if (0u == BkpEnterCounter)
        {
            /* 恢复BKPWR位 */
            SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
            /* 结束读写备份域数据 */
            SFR_CLR_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
        }
        else
        { /*Empty*/
        }
        Intr_Exit_Critical(r);
    }
}
/**
 * @brief 进入临界区并返回当前中断状态
 *
 * @param 无
 * @retval uint32_t 中断状态
 */
static uint32_t Intr_Enter_Critical(void)
{
    uint32_t r = INT_CTL0 & INT_CTL0_AIE;
    __asm volatile("DSI");
    __asm volatile("NOP");
    return r;
}

/**
 * @brief 根据中断状态是否使能中断
 *
 * @param[in] v 中断状态值
 * @retval none
 */
static void Intr_Exit_Critical(uint32_t v)
{
    if (v > 0U)
    {
        __asm volatile("ENI");
        __asm volatile("NOP");
    }
    else
    {/*Empty*/
    }
}
/**
  *   ##### 备份域(BKP)复位及读写允许函数定义结束 #####
  */


/**
  *   ##### 备份域(BKP)功能配置函数 #####
  */
/**
  * 描述  配置备份域寄存器组软件复位使能。
  * 输入  NewState: 备份域寄存器组软件复位，取值范围为：TRUE 或 FALSE。
  * 返回  无
  */
void BKP_Reset_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置BKP_CTL寄存器BKDRST位 ----------------*/
    if (NewState != FALSE)
    {
        /* 备份域寄存器组复位 */
        SFR_SET_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    }
    else
    {
        /* 无作用 */
        SFR_CLR_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    }
}

/**
  * 描述  设置侵入检测引脚的有效电平。
  * 输入  PinSel: 侵入检测引脚选择，取值为：
  *                 BKP_PIN_RTC_TAMP1: 侵入检测引脚RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: 侵入检测引脚RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: 侵入检测引脚RTC_TAMP3
  *       Effective: 有效电平，取值为:
  *                    BKP_HIGH_LEVEL_EFFECTIVE: 高电平会清除所有的数据备份寄存器
  *                    BKP_LOW_LEVEL_EFFECTIVE: 低电平会清除所有的数据备份寄存器
  * 返回  无。
  */
void BKP_Pin_Effective_Level_Config (uint32_t PinSel, uint32_t Effective)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_BKP_EFFECTIVE_LEVEL(Effective));

    /*------------- 配置BKP_CTL寄存器TAMPxLVL位 -------------*/
    tmpreg = BKP_CTL_TAMP1LVL << PinSel;
    if (BKP_HIGH_LEVEL_EFFECTIVE != Effective)
    {
        /* 侵入检测引脚上的低电平会清除所有的数据备份寄存器 */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* 侵入检测引脚上的高电平会清除所有的数据备份寄存器 */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * 描述  设置侵入检测引脚RTC_TAMP1使能。
  * 输入  PinSel: 侵入检测引脚选择，取值为：
  *                 BKP_PIN_RTC_TAMP1: 侵入检测引脚RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: 侵入检测引脚RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: 侵入检测引脚RTC_TAMP3
  *       NewState: 侵入检测引脚RTC_TAMP1使能状态，取值范围为：TRUE 或 FALSE。
  * 返回  无。
  */
void BKP_Pin_Enable (uint32_t PinSel, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*------------- 配置BKP_CTL寄存器TAMPxLVL位 -------------*/
    tmpreg = BKP_CTL_TAMP1EN << PinSel;
    if (NewState != FALSE)
    {
        /* 使能侵入引脚1功能 */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* 禁止侵入引脚1功能 */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * 描述  设置侵入检测同步功能。
  * 输入  Mode: 取值为：
  *                 BKP_TAMP_ASYNC: 侵入检测异步
  *                 BKP_TAMP_SYNC: 侵入检测同步
  * 返回  无。
  */
void BKP_TAMP_SYNC_Mode_Select(uint32_t Mode)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_BKP_TAMP_MODE(Mode));

	BKP_CTL	= SFR_Config(BKP_CTL, ~BKP_CTL_SYNC, Mode << BKP_CTL_SYNC_POS);
}

/**
  * 描述  设置侵入检测采样时钟。
  * 输入  CLK: 取值为：
  *                 BKP_TAMP_SCK_SCLK: 选择 SCLK 作为采样时钟
  *                 BKP_TAMP_SCK_INTLF: 选择 INTLF 作为采样时钟
  * 返回  无。
  */
void BKP_TAMP_SCK_Select(uint32_t CLK)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_BKP_TAMP_SCK(CLK));

	BKP_CTL	= SFR_Config(BKP_CTL, ~BKP_CTL_SAMCLKS, CLK << BKP_CTL_SAMCLKS_POS);
}

/**
  * 描述  设置外部时钟旁路控制使能。
  * 输入  Source: 时钟选择，取值为：
  *                 BKP_EXTHF: 外部高频时钟
  *                 BKP_EXTLF: 外部低频时钟
  *       NewState: 外部时钟旁路控制使能状态，取值范围为：TRUE 或 FALSE。
  * 返回  无。
  */
void BKP_External_Clock_Bypass_Enable (uint32_t Source, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_CLOCK_SOURCE(Source));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*------------- 配置BKP_CTL寄存器TAMPxLVL位 -------------*/
    tmpreg = BKP_CTL_EXTHFBYP << Source;
    if (FALSE != NewState)
    {
        /* 外部时钟被旁路 */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* 外部时钟未旁路 */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * 描述  写备份域备份数据寄存器。
  * 输入  OrderNumber: 备份数据寄存器编号，取值范围为0~7。
  *       WriteData: 写入的数据，取值范围为32位数据。
  * 返回  无。
  */
void BKP_Data_Config (uint32_t OrderNumber, uint32_t WriteData)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_DATA_NUMBER(OrderNumber));

    /*------------- 配置BKP_DATA寄存器BKPDATA位 -------------*/
    BKP_SFR->DATA[OrderNumber] = WriteData;
}

/**
  * 描述  读备份域备份数据寄存器。
  * 输入  OrderNumber: 备份数据寄存器编号，取值范围为0~7。
  * 返回  备份数据寄存器的值，取值范围为32位数据。
  */
uint32_t BKP_Get_Data (uint32_t OrderNumber)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_DATA_NUMBER(OrderNumber));

    /*------------- 读取BKP_DATA寄存器BKPDATA位 -------------*/
    tmpreg = BKP_SFR->DATA[OrderNumber];

    return tmpreg;
}
/**
  *   ##### 备份域(BKP)功能配置函数定义结束 #####
  */


/**
  *   ##### 备份域(BKP)中断管理函数 #####
  */
/**
  * 描述  配置侵入引脚中断使能。
  * 输入  PinSel: 侵入检测引脚选择，取值为：
  *                 BKP_PIN_RTC_TAMP1: 侵入检测引脚RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: 侵入检测引脚RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: 侵入检测引脚RTC_TAMP3
  *       NewState: 侵入引脚中断使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void BKP_Pin_TAMP_INT_Enable (uint32_t PinSel, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 配置BKP_INT寄存器TAMPxIE位 ----------------*/
    tmpreg = BKP_INT_TAMP1IE << PinSel;
    if (NewState != FALSE)
    {
        /* 使能侵入检测中断 */
        BKP_INT |= tmpreg;
    }
    else
    {
        /* 禁止侵入检测中断 */
        BKP_INT &= ~tmpreg;
    }
}

/**
  * 描述  获取侵入中断标志。
  * 输入  PinSel: 侵入检测引脚选择，取值为：
  *                 BKP_PIN_RTC_TAMP1: 侵入检测引脚RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: 侵入检测引脚RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: 侵入检测引脚RTC_TAMP3
  * 返回  1:发生侵入事件，0:无侵入事件发生。
  */
FlagStatus BKP_Get_Pin_TAMP_INT_Flag (uint32_t PinSel)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));

    /*---------------- 读取BKP_INT寄存器TAMPxIF位 ----------------*/
    tmpreg = BKP_INT_TAMP1IF << PinSel;
    if (BKP_INT & tmpreg)
    {
        /* 发生侵入事件 */
        return SET;
    }
    else
    {
        /* 无侵入事件发生 */
        return RESET;
    }
}

/**
  * 描述  清除侵入检测中断标志。
  * 输入  PinSel: 侵入检测引脚选择，取值为：
  *                 BKP_PIN_RTC_TAMP1: 侵入检测引脚RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: 侵入检测引脚RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: 侵入检测引脚RTC_TAMP3
  * 返回  ：清除侵入检测中断标志状态。
  */
RetStatus BKP_Clear_Pin_TAMP_INT_Flag (uint32_t PinSel)
{
    uint32_t tmpreg;
    uint32_t tmpreg1;
	volatile uint32_t wait_flag=0x0000;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));

    /*---------------- 配置BKP_INT寄存器TAMPxIC位 ----------------*/
    tmpreg = BKP_INT_TAMP1IC << PinSel;
    tmpreg1 = BKP_INT_TAMP1IF << PinSel;
    BKP_INT |= tmpreg;
    while(((BKP_INT & tmpreg1)>>(BKP_INT_TAMP1IF_POS+PinSel))&& (wait_flag != FLAG_TIMEOUT))
	{
		wait_flag++;
	}
    BKP_INT &= ~tmpreg;
	if(wait_flag==FLAG_TIMEOUT)
	{
		return FAILURE;
	}
	return SUCCESS;
}
/**
  *   ##### 备份域(BKP)中断管理函数 #####
  */

