/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_pm.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file provides the power management (PM) related
 *                      functions, including:                                  
 *                      + Power management(PM) control function               
 *                      + Power management(PM) status flag management function
 *                      + Power management(PM) calibration control function      
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


#include "kf32a156_pm.h"
#include "kf32a156_osc.h"


/**
  *   ##### 电源管理(PM)控制功能函数 #####
  */
/**
  * 描述  设置IO口状态锁存使能。
  * 输入  NewState: IO口状态锁存使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_IO_Latch_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器IOLATCH位 ----------------*/
    if (NewState != FALSE)
    {
        /*  IO口状态被锁存 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_IOLATCH_POS);
    }
    else
    {
        /* IO口状态未被锁存 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_IOLATCH_POS);
    }
}

/**
  * 描述  获取IO口状态锁存。
  * 输入  无。
  * 返回  1:IO口状态被锁存；0:IO口状态未被锁存。
  */
FlagStatus PM_Get_IO_Latch_Status (void)
{
    /*---------------- 读取PM_CTL0寄存器IOLATCH位 ----------------*/
    if (PM_CTL0 & PM_CTL0_IOLATCH)
    {
        /* IO口状态被锁存 */
        return SET;
    }
    else
    {
        /* IO口状态未被锁存 */
        return RESET;
    }
}

/**
  * 描述  设置内部低频振荡器软件使能。
  * 输入  NewState: 内部低频振荡器软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Internal_Low_Frequency_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器LSIEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 软件使能内部低频振荡器 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LSIEN_POS);
    }
    else
    {
        /* 软件未使能内部低频振荡器 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LSIEN_POS);
    }
}

/**
  * 描述  设置外部低频振荡器软件使能。
  * 输入  NewState: 外部低频振荡器软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_External_Low_Frequency_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器LSEEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 软件使能外部低频振荡器 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LSEEN_POS);
    }
    else
    {
        /* 软件未使能外部低频振荡器 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LSEEN_POS);
    }
}

/**
  * 描述  设置主BG软件使能。
  * 输入  NewState: 主BG软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Main_Bandgap_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器MRBGEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 软件使能主BG模块 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_MRBGEN_POS);
    }
    else
    {
        /* 未软件使能主BG模块 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_MRBGEN_POS);
    }
}

/**
  * 描述  设置LDO18软件使能。
  * 输入  NewState: LDO18软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_LDO18_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器LDO18EN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能LDO18模块 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LDO18EN_POS);
    }
    else
    {
        /* 禁止LDO18模块，Power18（flash）掉电 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LDO18EN_POS);
    }
}

/**
  * 描述  设置备份区寄存器模块软件复位。
  * 输入  BkpReset: 备份区寄存器模块软件复位状态，取值为:
  *                   PERIPHERAL_RST_STATUS: 备份区寄存器模块处于复位状态
  *                   PERIPHERAL_OUTRST_STATUS: 备份区寄存器模块退出复位
  * 返回  无。
  */
void PM_Backup_Registers_Reset_Config (uint32_t BkpReset)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PERIPHERAL_RST(BkpReset));

    /*---------------- 设置PM_CTL0寄存器BKPREGCLR位 ----------------*/
    if (BkpReset != PERIPHERAL_RST_STATUS)
    {
        /* 备份区寄存器模块退出复位 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPREGCLR_POS);
    }
    else
    {
        /* 备份区寄存器模块处于复位状态 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_BKPREGCLR_POS);
    }
}

/**
  * 描述  设置IWDT模块软件复位。
  * 输入  IWDTReset: IWDT模块软件复位状态，取值为:
  *                   PERIPHERAL_RST_STATUS: IWDT处于复位状态
  *                   PERIPHERAL_OUTRST_STATUS: IWDT退出复位
  * 返回  无。
  */
void PM_Independent_Watchdog_Reset_Config (uint32_t IWDTReset)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PERIPHERAL_RST(IWDTReset));

    /*---------------- 设置PM_CTL0寄存器IWDTCLR位 ----------------*/
    if (IWDTReset != PERIPHERAL_RST_STATUS)
    {
        /* IWDT退出复位 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_IWDTCLR_POS);
    }
    else
    {
        /* IWDT处于复位状态 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_IWDTCLR_POS);
    }
}

/**
  * 描述  设置DPRAM在standby模式下工作配置。
  * 输入  WorkMode: DPRAM_A区在standby模式下工作配置，取值为:
  *                   PM_DPRAM_IN_STANDBY_POWER_DOWN: SRAM的A区在standby模式下掉电
  *                   PM_DPRAM_IN_STANDBY_KEEP_DATA: SRAM的A区在standby模式下保持数据
  * 返回  无。
  */
void PM_DPRAM_In_Standby_Work_Mode_Config (uint32_t WorkMode)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_DPRAM_IN_STANDBY(WorkMode));

    /*---------------- 设置PM_CTL0寄存器DPRAMASEL位 ----------------*/
    if (WorkMode != PM_DPRAM_IN_STANDBY_POWER_DOWN)
    {
        /* DPRAM_A区在standby模式下保持数据 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_DPRAMASEL_POS);
    }
    else
    {
        /* SRAM的A区在standby模式下掉电 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_DPRAMASEL_POS);
    }
}

/**
  * 描述  设置LPRAM/DPRAMA在 stop1 和 standby 模式下工作配置。
  * 输入  WorkMode: LPRAM/DPRAMA 在 stop1 和 standby 模式下工作配置，取值为:
  *                   PM_LPRAM_IN_STANDBY_POWER_DOWN: LPRAM/DPRAMA在standby模式下掉电
  *                   PM_LPRAM_IN_STANDBY_KEEP_DATA:  LPRAM/DPRAMA在standby模式下保持数据
  * 返回  无。
  */
void PM_LPRAM_DPRAMA_In_Standby_Stop1_Work_Mode_Config (uint32_t WorkMode)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_LPSRAM_IN_STANDBY(WorkMode));

    /*---------------- 设置PM_CTL0寄存器SRAMASEL位 ----------------*/
    if (WorkMode != PM_LPRAM_IN_STANDBY_POWER_DOWN)
    {
        /* LPRAM在stop1 和 standby模式下保持数据 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LPRAMSEL_POS);
    }
    else
    {
        /* LPRAM在stop1 和 standby模式下掉电 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LPRAMSEL_POS);
    }
}

/**
  * 描述  设置BKP_POR延时时间。
  * 输入  DelayTime: BKP_POR延时时间，取值为:
  *                    DELAY_TIME_2ms: 2ms
  *                    DELAY_TIME_32us: 32us
  * 返回  无。
  */
void PM_Backup_POR_Delay_Time_Config (uint32_t DelayTime)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_DELAY_TIME(DelayTime));

    /*---------------- 设置PM_CTL0寄存器BKPPORDELAYSEL位 ----------------*/
    if (DelayTime != DELAY_TIME_2ms)
    {
        /* 延时1ms */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPPORDELAYSEL_POS);
    }
    else
    {
        /* 延时32us */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_BKPPORDELAYSEL_POS);
    }
}

/**
  * 描述  设置主POR、POR12和POR18延时时间。
  * 输入  DelayTime: 主POR、POR12和POR18延时时间，取值为:
  *                    DELAY_TIME_2ms: 2ms
  *                    DELAY_TIME_32us: 32us
  * 返回  无。
  */
void PM_Main_POR_Delay_Time_Config (uint32_t DelayTime)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_DELAY_TIME(DelayTime));

    /*---------------- 设置PM_CTL0寄存器PORDELAYSEL位 ----------------*/
    if (DelayTime != DELAY_TIME_2ms)
    {
        /* 延时2ms */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_PORDELAYSEL_POS);
    }
    else
    {
        /* 延时32us */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_PORDELAYSEL_POS);
    }
}

/**
  * 描述  设置低功耗外设IO口。
  * 输入  PeripheralPort: 低功耗外设IO口，取值为:
  *                         PM_GENERAL_PURPOSE_IO_PORT: 通用IO口
  *                         PM_LOW_POWER_IO_PORT: 低功耗专用IO口
  * 返回  无。
  */
void PM_Peripheral_IO_Port_Config (uint32_t PeripheralPort)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_LOW_POWER_IO(PeripheralPort));

    /*---------------- 设置PM_CTL0寄存器PHERIIOSEL位 ----------------*/
    if (PeripheralPort != PM_GENERAL_PURPOSE_IO_PORT)
    {
        /* 低功耗专用IO口 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_PHERIIOSEL_POS);
    }
    else
    {
        /* 通用IO口 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_PHERIIOSEL_POS);
    }
}

/**
  * 描述  低功耗模式下锁存内部高频晶振校准值
  * 输入  NewState: HSI内部高频晶振校准值锁存位,取值为TRUE 或 FALSE
  * 返回  无
  */
void PM_OCAL0LOCK_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器OCALLOCK位 ----------------*/
    if (NewState != FALSE)
    {
        /* 锁存晶振校准值 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_OCALLOCK_POS);
    }
    else
    {
        /* 不锁存晶振校准值 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_OCALLOCK_POS);
    }
}

/**
  * 描述  低功耗模式下MEMM数据保持使能
  * 输入  NewState: MEMM数据保持使能位,取值为TRUE 或 FALSE
  * 返回  无
  */
void PM_MEMSEL_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器OCALLOCK位 ----------------*/
    if (NewState != FALSE)
    {
        /* 锁存晶振校准值 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_MEMSEL_POS);
    }
    else
    {
        /* 不锁存晶振校准值 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_MEMSEL_POS);
    }
}

/**
  * 描述  设置FLASH供电电源软件关断使能。
  * 输入  NewState: FLASH供电电源软件关断使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Flash_Power_Off_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL2寄存器VF12EN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 关断FLASH供电电源开关，FLASH模块掉电 */
        SFR_CLR_BIT_ASM(PM_CTL2, PM_CTL2_VF12EN_POS);
    }
    else
    {
        /* 软件未关断FLASH供电电源开关 */
        SFR_SET_BIT_ASM(PM_CTL2, PM_CTL2_VF12EN_POS);
    }
}

/**
 *  @brief : Config the CCP0 CLk is INTLF
 *  @param in :NewState TRUE OR FALSE
 *  @param out :None
 *  @retval :None
 */
void PM_CCP0LPEN_ENABLE(FunctionalState NewState)
{
	/* param check */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));
	if (NewState != FALSE)
    {
		/* Set the INTLF as the CCP0 clk */
        SFR_SET_BIT_ASM(PM_CTL2, PM_CTL2_CCP0LPEN_POS);
    }
    else
    {
        /* Clear the INTLF as the CCP0 clk */
        SFR_CLR_BIT_ASM(PM_CTL2, PM_CTL2_CCP0LPEN_POS);
    }
}

/**
  * 描述  设置CCP0内部低频时钟使能。
  * 输入  NewState: CCP0内部低频时钟使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_CCP0CLKLPEN_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL2寄存器CCP0CLKLPEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 允许内部低频时钟作为 CCP0 工作时钟 */
        SFR_SET_BIT_ASM(PM_CTL2, PM_CTL2_CCP0CLKLPEN_POS);
    }
    else
    {
        /* 禁止内部低频时钟作为 CCP0 工作时钟 */
        SFR_CLR_BIT_ASM(PM_CTL2, PM_CTL2_CCP0CLKLPEN_POS);
    }
}

/**
  * 描述  设置备份区读写操作允许使能。
  * 输入  NewState: 备份区读写操作允许使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Backup_Write_And_Read_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器BKPWR位 ----------------*/
    if (NewState != FALSE)
    {
        /* 允许CPU对备份区内寄存器进行读写操作 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
    }
    else
    {
        /* 禁止CPU对备份区内寄存器进行读写操作 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
    }
}

/**
  * 描述  设置参考电压使能。
  * 输入  NewState: 参考电压使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_VREF_Software_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器VREFEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 软件使能参考电压 */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
    else
    {
        /* 软件未使能参考电压*/
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
}

/**
  * 描述  设置参考电压档位选择。
  * 输入  NewState: 参考电压档位选择
  * 			PM_VREF_VOLTAGE_4P0V
  * 			PM_VREF_VOLTAGE_1P5V
  * 			PM_VREF_VOLTAGE_2P0V
  * 			PM_VREF_VOLTAGE_3P0V
  * 返回  无。
  */
void PM_VREF_SELECT (uint32_t Voltage)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_VREF_VOLTAGE(Voltage));

    /*---------------- 配置PM_CTL0寄存器VREFSEL位 ----------------*/
    PM_CTL1 = SFR_Config (PM_CTL1, ~PM_CTL1_VREFSEL, Voltage);
}

/**
  * 描述  设置低功耗电压调制器LPR软件使能。
  * 输入  NewState: 低功耗电压调制器LPR软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_LPR_Software_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器LPREN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 软件使能LPR */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LPREN_POS);
    }
    else
    {
        /* 软件未使能LPR */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LPREN_POS);
    }
}

/**
  * 描述  设置低功耗模式。
  * 输入  LowPowerMode: 低功耗模式，取值为:
  *                       PM_LOW_POWER_MODE_STOP_0: 停止模式0
  *                       PM_LOW_POWER_MODE_STOP_1: 停止模式1
  *                       PM_LOW_POWER_MODE_STANDBY: 待机模式
  *                       PM_LOW_POWER_MODE_SHUTDOWN: 关断模式
  * 返回  无。
  */
void PM_Low_Power_Mode_Config (uint32_t LowPowerMode)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_LOW_POWER_MODE(LowPowerMode));

    /*---------------- 配置PM_CTL0寄存器LPMS位 ----------------*/
    PM_CTL0 = SFR_Config (PM_CTL0, ~PM_CTL0_LPMS, LowPowerMode);
}

/**
  * 描述  设置BOR使能。
  * 输入  NewState: BOR使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_BOR_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器BOREN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能BOR */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_BOREN_POS);
    }
    else
    {
        /* 禁止BOR */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_BOREN_POS);
    }
}

/**
  * 描述  设置LPBOR使能。
  * 输入  NewState: LPBOR使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Low_Power_BOR_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器LPBOREN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能LPBOR */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_LPBOREN_POS);
    }
    else
    {
        /* 禁止LPBOR */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_LPBOREN_POS);
    }
}

/**
  * 描述  设置TEMPSENSOR使能。
  * 输入  NewState: TEMPSENSOR使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Temperature_Sensor_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器TSEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能TEMPSENSOR */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_TSEN_POS);
    }
    else
    {
        /* 禁止TEMPSENSOR */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_TSEN_POS);
    }
}

/**
  * 描述  设置TEMPSENSOR输出到BUFFER使能。
  * 输入  NewState: TEMPSENSOR输出到BUFFER使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Temperature_Sensor_Buffer_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器TSOE位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能TEMPSENSOR输出到BUFFER */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_TSOE_POS);
    }
    else
    {
        /* 禁止TEMPSENSOR输出到BUFFER */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_TSOE_POS);
    }
}

/**
  * 描述  设置参考电压2V模块使能。
  * 输入  NewState: 参考电压2V模块使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Reference_Voltage_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器VREFEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能参考电压2V模块 */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
    else
    {
        /* 禁止参考电压2V模块 */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
}




/**
  * 描述  设置PVM1使能。
  * 输入  NewState: PVM1使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Peripheral_Voltage_Monitoring_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器VREFEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能参考电压模块 */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
    else
    {
        /* 禁止参考电压模块 */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_VREFEN_POS);
    }
}

/**
  * 描述  设置电压检测点选择。
  * 
  *       注意：具体PVD电压值请参考数据手册。
  * 
  * 输入  Voltage: 电压检测点选择，取值为:
  *                  PM_VOLTAGE_DETECTION_POINT_3
  *                  PM_VOLTAGE_DETECTION_POINT_4
  *                  PM_VOLTAGE_DETECTION_POINT_5
  *                  PM_VOLTAGE_DETECTION_POINT_6
  * 返回  无。
  */
void PM_Voltage_Detection_Config (uint32_t Voltage)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_VOLTAGE_DETECTION(Voltage));

    /*---------------- 配置PM_CTL1寄存器PVDS位 ----------------*/
    PM_CTL1 = SFR_Config (PM_CTL1, ~PM_CTL1_PVDS, Voltage);
}


/**
  * 描述 配置低功耗模式下 DEBUG 调试使能。
  * 输入  NewState: 取值为:
  *                TRUE: 使能低功耗模式下 DEBUG 调试
  *                FALSE: 禁止低功耗模式下 DEBUG 调试
  * 返回  无。
  */
void PM_LP_DEBUG_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_LPDEBUG, NewState << PM_CTL1_LPDEBUG_POS);
}

/**
  * 描述 配置LVL_LDO18 强制使能。
  * 输入  NewState: 取值为:
  *                TRUE: LVL_LDO18 强制使能
  *                FALSE: 无作用
  * 返回  无。
  */
void PM_LVL_LDO18_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_P18LVLSENB, (!NewState) << PM_CTL1_P18LVLSENB_POS);
}

/**
  * 描述 配置RAM 的 ECC 功能使能使能。
  * 输入  NewState: 取值为:
  *                TRUE: 使能 RAM 的 ECC 功能
  *                FALSE: 禁止 RAM 的 ECC 功能
  * 返回  无。
  */
void PM_RAM_ECC_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_RAMECCEN, NewState << PM_CTL1_RAMECCEN_POS);
}

/**
  * 描述 低功耗 CAN 工作时钟选择。
  * 输入  CLK: 取值为:
  *                PM_LPCAN_SCK_INTLF: 选择内部低频 INTLF 作为工作时钟
  *                PM_LPCAN_SCK_LP4M: 选择 LP4M 作为工作时钟
  * 返回  无。
  */
void PM_LPCAN_Work_CLK_Select(uint32_t CLK)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_PM_LPCAN_SCK(CLK));

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_LPCANCLKS, CLK << PM_CTL1_LPCANCLKS_POS);
}

/**
  * 描述  设置电压检测功能使能。
  * 输入  NewState: 电压检测功能使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Voltage_Detection_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器PVDEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能电压检测功能 */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_PVDEN_POS);
    }
    else
    {
        /* 禁止电压检测功能 */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_PVDEN_POS);
    }
}

/**
  * 描述  设置外部唤醒引脚WKPx使能。
  * 输入  PinSel: 唤醒引脚，取值为：
  *                 PM_PIN_WKP1: 引脚WKP1
  *                 PM_PIN_WKP2: 引脚WKP2
  *                 PM_PIN_WKP3: 引脚WKP3
  *                 PM_PIN_WKP4: 引脚WKP4
  *                 PM_PIN_WKP5: 引脚WKP5
  *       NewState: 外部唤醒引脚WKPx使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_External_Wakeup_Pin_Enable (uint32_t PinSel, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_PIN_WKP(PinSel));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL2寄存器WKPxEN位 ----------------*/
    tmpreg = PM_CTL2_WKP1EN << PinSel;
    if (NewState != FALSE)
    {
        /* 使能WKPx电平变化唤醒 */
        PM_CTL2 |= tmpreg;
    }
    else
    {
        /* 禁止WKPx电平变化唤醒 */
        PM_CTL2 &= ~tmpreg;
    }
}

/**
  * 描述  设置外部唤醒引脚WKPx唤醒触发沿。
  * 输入  PinSel: 唤醒引脚，取值为：
  *                 PM_PIN_WKP1: 引脚WKP1
  *                 PM_PIN_WKP2: 引脚WKP2
  *                 PM_PIN_WKP3: 引脚WKP3
  *                 PM_PIN_WKP4: 引脚WKP4
  *                 PM_PIN_WKP5: 引脚WKP5
  *       TriggerEdge: 外部唤醒引脚WKPx唤醒触发沿，取值为:
  *                      PM_TRIGGER_RISE_EDGE: WKPx上升沿触发
  *                      PM_TRIGGER_FALL_EDGE: WKPx下降沿触发
  * 返回  无。
  */
void PM_External_Wakeup_Edge_Config (uint32_t PinSel, uint32_t TriggerEdge)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_PIN_WKP(PinSel));
    CHECK_RESTRICTION(CHECK_PM_TRIGGER_EDGE(TriggerEdge));

    /*---------------- 设置PM_CTL2寄存器WKP5P位 ----------------*/
    tmpreg = PM_CTL2_WKP1P << PinSel;
    if (TriggerEdge != PM_TRIGGER_RISE_EDGE)
    {
        /* WKPx下降沿触发 */
        PM_CTL2 |= tmpreg;
    }
    else
    {
        /* WKPx上升沿触发 */
        PM_CTL2 &= ~tmpreg;
    }
}

/**
  * 描述  设置不同外设工作在Stop模式下内部低频时钟使能。
  * 输入  Peripheral: 外设选择，取值为：
  *                     PM_PERIPHERAL_CAN6: CAN6
  *                     PM_PERIPHERAL_CCP: CCP
  *                     PM_PERIPHERAL_EWDT: EWDT
  *                     PM_PERIPHERAL_USART0: USART0
  *       NewState: 内部低频时钟使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Stop_Mode_Peripheral_INLF_Enable (uint32_t Peripheral,FunctionalState NewState)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_PERIPHERAL(Peripheral));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL2寄存器xxxxCLKLPEN位 ----------------*/
    tmpreg = PM_CTL2_CAN6CLKLPEN << Peripheral;
    if (NewState != FALSE)
    {
        /* 允许内部低频时钟作为外设工作时钟 */
        PM_CTL2 |= tmpreg;
    }
    else
    {
        /* 禁止时钟 */
        PM_CTL2 &= ~tmpreg;
    }
}

/**
  * 描述  设置不同外设复位。
  * 输入  Peripheral: 外设选择，取值为：
  *                     PM_PERIPHERAL_CAN6: CAN6
  *                     PM_PERIPHERAL_CCP: CCP
  *                     PM_PERIPHERAL_EWDT: EWDT
  *                     PM_PERIPHERAL_USART0: USART0
  *       ResetStatus: 外设复位状态，取值为:
  *                      PERIPHERAL_RST_STATUS: 外设处于复位状态
  *                      PERIPHERAL_OUTRST_STATUS: 外设退出复位
  * 返回  无。
  */
void PM_Peripheral_Reset_Config (uint32_t Peripheral, uint32_t ResetStatus)
{
    uint32_t tmpreg;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_PERIPHERAL(Peripheral));
    CHECK_RESTRICTION(CHECK_PERIPHERAL_RST(ResetStatus));

    /*---------------- 设置PM_CTL2寄存器xxxxLPEN位 ----------------*/
    tmpreg = PM_CTL2_CAN6LPEN << Peripheral;
    if (ResetStatus != PERIPHERAL_RST_STATUS)
    {
        /* 模块退出复位 */
        PM_CTL2 |= tmpreg;
    }
    else
    {
        /* 模块处于复位状态 */
        PM_CTL2 &= ~tmpreg;
    }
}

/**
  * 描述  设置PMC 错误状态中断使能。
  * 输入  NewState: 取值为：
  *                TRUE：  使能 PMC 错误状态中断
  *                FALSE： 禁止 PMC 错误状态中断
  * 返回  无。
  */
void PM_PMC_Error_Status_INT_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_PMCIE, NewState << PM_CTL2_PMCIE_POS);
}

/**
  * 描述  设置QEI0 复位控制位。
  * 输入  NewState: 取值为：
  *                TRUE：   QEI0 模块退出复位
  *                FALSE： QEI0 模块处于复位状态
  * 返回  无。
  */
void PM_QEI0_Reset_Control(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_QEI0LPEN, NewState << PM_CTL2_QEI0LPEN_POS);
}

/**
  * 描述  设置GPIOA 复位控制位。
  * 输入  NewState: 取值为：
  *                TRUE：  GPIOA 模块退出复位
  *                FALSE： GPIOA 模块处于复位状态
  * 返回  无。
  */
void PM_GPIOA_Reset_Control(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_GPIOALPEN, NewState << PM_CTL2_GPIOALPEN_POS);
}

/**
  * 描述  设置RTC 复位控制位。
  * 输入  NewState: 取值为：
  *                TRUE：  RTC 模块退出复位
  *                FALSE： RTC 模块处于复位状态
  * 返回  无。
  */
void PM_RTC_Reset_Control(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_RTCLPEN, NewState << PM_CTL2_RTCLPEN_POS);
}

/**
  * 描述  设置QEI0 工作在 Stop 模式下内部低频时钟使能。
  * 输入  NewState: 取值为：
  *                TRUE：  允许内部低频时钟作为 QEI0 工作时钟
  *                FALSE： 禁止时钟
  * 返回  无。
  */
void PM_QEI0_Work_Stop_INTLF_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_QEI0CLKLPEN, NewState << PM_CTL2_QEI0CLKLPEN_POS);
}

/**
  * 描述  设置RTC 工作在 Stop 模式下内部低频时钟使能。
  * 输入  NewState: 取值为：
  *                TRUE：  允许内部低频/外部低频时钟作为 RTC 工作时钟
  *                FALSE： 禁止时钟
  * 返回  无。
  */
void PM_RTC_Work_Stop_INTLF_Enable(FunctionalState NewState)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	PM_CTL2 = SFR_Config(PM_CTL2, ~PM_CTL2_RTCCLKLPEN, NewState << PM_CTL2_RTCCLKLPEN_POS);
}


#if _CLOSE_SERVICE_

/**
  * 描述  设置LP_BG软件使能。
  * 输入  NewState: LP_BG软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Low_Power_Bandgap_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器LPBGON位 ----------------*/
    if (NewState != FALSE)
    {
        /*  软件使能LP_BG */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LPBGON_POS);
    }
    else
    {
        /* 软件不使能LP_BG，BOR、LPR、PVD、LCDpump使能时LP_BG将自动使能 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LPBGON_POS);
    }
}


#endif /* _CLOSE_SERVICE_ */
/**
  *   ##### 电源管理(PM)控制功能函数定义结束 #####
  */


/**
  *   ##### 电源管理(PM)状态标志管理函数 #####
  */
/**
  * 描述  清零复位/唤醒状态标志位。
  * 输入  EventSel: 复位/唤醒事件，取值为：
  *                   PM_RESET_IWDT: 独立看门狗复位事件
  *                   PM_WAKEUP_EXTERNAL_PIN: 外部唤醒引脚唤醒事件
  *                   PM_RESET_POR: POR复位事件
  *                   PM_RESET_BOR: BOR复位事件
  *                   PM_RESET_SOFTWARE: 软件复位事件
  * 返回  :  清除复位/唤醒状态标志位是否成功状态。
  */
RetStatus PM_Clear_Reset_And_Wakeup_Flag (uint32_t EventSel)
{
    uint32_t tmpmask;
	volatile uint32_t wait_flag=0x0000;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_CLEAR_STA0_RESET_WAKEUP(EventSel));
    tmpmask = (uint32_t)1 << EventSel;
    /*---------------- 设置PM_STA0寄存器RSTFC位 ----------------*/
    SFR_SET_BIT_ASM(PM_STA0, PM_STA0_RSTFC_POS);
    while((PM_STA0 & tmpmask)&& (wait_flag != FLAG_TIMEOUT))
	{
		wait_flag++;
	}
    SFR_CLR_BIT_ASM(PM_STA0, PM_STA0_RSTFC_POS);
	if(wait_flag==FLAG_TIMEOUT)
	{
		return FAILURE;
	}
	return SUCCESS;
}

/**
  * 描述  获取对应复位/唤醒事件的状态标志。
  * 输入  EventSel: 复位/唤醒事件，取值为：
  *                   PM_RESET_IWDT: 独立看门狗复位事件
  *                   PM_WAKEUP_EXTERNAL_PIN: 外部唤醒引脚唤醒事件
  *                   PM_RESET_POR: POR复位事件
  *                   PM_RESET_BOR: BOR复位事件
  *                   PM_RESET_SOFTWARE: 软件复位事件
  *                   PM_RESET_BKPBOR: BKPPOR复位事件
  *                   PM_RESET_NRST: NRST引脚复位事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP5: WKP5引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP4: WKP4引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP3: WKP3引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP2: WKP2引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP1: WKP1引脚唤醒事件
  * 返回  1: 发生了复位/唤醒事件；
  *       0: 未发生复位/唤醒事件。
  */
FlagStatus PM_Get_Reset_Flag (uint32_t EventSel)
{
    uint32_t tmpreg;
    uint32_t tmpmask;

    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_RESET_WAKEUP(EventSel));

    if (EventSel < 32)
    {
        tmpreg = PM_STA0;
        tmpmask = (uint32_t)1 << EventSel;
    }
    else
    {
        tmpreg = PM_STA1;
        tmpmask = (uint32_t)1 << (EventSel - 32);
    }

    /*---------------- 读取PM_STAx寄存器对应位 ----------------*/
    if (tmpreg & tmpmask)
    {
        /* 发生了复位/唤醒事件 */
        return SET;
    }
    else
    {
        /* 未发生复位/唤醒事件 */
        return RESET;
    }
}

/**
  * 描述  清零外部唤醒引脚WKPx状态标志。
  * 输入  EventSel: 复位/唤醒事件，取值为：
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP5: WKP5引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP4: WKP4引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP3: WKP3引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP2: WKP2引脚唤醒事件
  *                   PM_WAKEUP_EXTERNAL_PIN_WKP1: WKP1引脚唤醒事件
  * 返回  :清除外部唤醒引脚WKPx状态标志是否成功状态。
  */
RetStatus PM_Clear_External_Wakeup_Pin_Flag (uint32_t EventSel)
{
    uint32_t tmpreg;
    uint32_t tmpmask;
	volatile uint32_t wait_flag=0x0000;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_CLEAR_STA1_WAKEUP(EventSel));
    tmpmask = (uint32_t)1 << (EventSel - 32);
    /*---------------- 设置PM_STAC寄存器WKPxSC位 ----------------*/
    PM_STAC |= tmpmask;
    while((PM_STA1 & tmpmask)&& (wait_flag != FLAG_TIMEOUT))
	{
		wait_flag++;
	}
    PM_STAC &= ~tmpmask;
	if(wait_flag==FLAG_TIMEOUT)
	{
		return FAILURE;
	}
	return SUCCESS;
}


/**
  * 描述  清零全部外部唤醒引脚WKPx状态标志。
  * 输入  无
  * 返回  无
  */
void PM_Clear_All_External_Wakeup_Pin_Flag ()
{
    PM_STAC |= 0xF8000000u;
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    PM_STAC &= ~0xF8000000u;
}
/**
  * 描述  清零PMCIF 标志。
  * 输入  无
  * 返回  无。
  */
void PM_Clear_PMCIF_Flag(void)
{
	PM_STAC = SFR_Config(PM_STAC, ~PM_STAC_PMCIC, PM_STAC_PMCIC);
}

/**
  * 描述  获取低功耗运行模式状态标志。
  * 输入  无。
  * 返回  1: 电压调制器切换至LPR；0: 主电压调制器MR已使能完成。
  */
FlagStatus PM_Get_Low_Power_Running_State (void)
{
    /*---------------- 读取PM_STA0寄存器LPRUNF位 ----------------*/
    if (PM_STA0 & PM_STA0_LPRUNF)
    {
        /* 电压调制器切换至LPR */
        return SET;
    }
    else
    {
        /* 主电压调制器MR已使能完成 */
        return RESET;
    }
}

/**
  * 描述  获取低功耗电压调制器LPR状态。
  * 输入  无。
  * 返回  1: 低功耗电压调制器LPR已使能完成；
  *       0: 低功耗电压调制器LPR未使能完成。
  */
FlagStatus PM_Get_LPR_Status (void)
{
    /*---------------- 读取PM_STA0寄存器LPRSTA位 ----------------*/
    if (PM_STA0 & PM_STA0_LPRSTA)
    {
        /* 低功耗电压调制器LPR已使能完成 */
        return SET;
    }
    else
    {
        /* 低功耗电压调制器LPR未使能完成 */
        return RESET;
    }
}

/**
  * 描述  获取电压检测状态。
  * 输入  无。
  * 返回  1: VDD电压高于PVD电压点；
  *       0: VDD电压低于PVD电压点。
  */
FlagStatus PM_Get_Peripheral_Voltage_Detection_Status (void)
{
    /*---------------- 读取PM_STA1寄存器PVDSTA位 ----------------*/
    if (PM_STA1 & PM_STA1_PVDSTA)
    {
        /* VDD电压高于PVD电压点 */
        return SET;
    }
    else
    {
        /* VDD电压低于PVD电压点 */
        return RESET;
    }
}

/**
  * 描述  获取PMC 错误中断标志。
  * 输入  无。
  * 返回  1: 发生了 PMC 错误中断（STOPERROR 或 PMCERROR 置 1）
  *       0: 无作用。
  */
FlagStatus PM_Get_PMC_Error_INT_Falg(void)
{
    /*---------------- 读取PM_STA1寄存器PMCIF位 ----------------*/
    if (PM_STA1 & PM_STA1_PMCIF)
    {
        /* 发生了 PMC 错误中断 */
        return SET;
    }
    else
    {
        /* 无作用 */
        return RESET;
    }
}

/**
  * 描述  获取POR18 完成状态。
  * 输入  无。
  * 返回  1: 已完成 POR18
  *       0: 未完成 POR18
  */
FlagStatus PM_POR18_Finish_Falg(void)
{
    /*---------------- 读取PM_STA1寄存器POR18FINISH位 ----------------*/
    if (PM_STA1 & PM_STA1_POR18STA)
    {
        /* 已完成 POR18 */
        return SET;
    }
    else
    {
        /* 未完成 POR18 */
        return RESET;
    }
}

/**
  * 描述  获取掉电模式进入错误中断标志
  * 输入  无。
  * 返回  1: 在掉电动作完成前发生了唤醒条件
  *       0: 正常进入了掉电模式
  */
FlagStatus PM_PD_PMC_Error_Falg(void)
{
    /*---------------- 读取PM_STA1寄存器PMCERROR位 ----------------*/
    if (PM_STA1 & PM_STA1_PMCERROR)
    {
        /* 已完成 POR18 */
        return SET;
    }
    else
    {
        /* 未完成 POR18 */
        return RESET;
    }
}

/**
  * 描述  获取STOP 模式进入错误中断标志
  * 输入  无。
  * 返回  1: 进入 STOP 模式时存在唤醒条件
  *       0: 正常进入了 STOP 模式
  */
FlagStatus PM_Stop_Mode_Error_Falg(void)
{
    /*---------------- 读取PM_STA1寄存器STOPERROR位 ----------------*/
    if (PM_STA1 & PM_STA1_STOPERROR)
    {
        /* 进入 STOP 模式时存在唤醒条件 */
        return SET;
    }
    else
    {
        /* 正常进入了 STOP 模式 */
        return RESET;
    }
}


/**
  *   ##### 电源管理(PM)状态标志管理函数定义结束 #####
  */


/**
  *   ##### 电源管理(PM)校准控制函数 #####
  */

/**
  * 描述  设置BOR电压点选择。
  * 
  *       注意：具体BOR电压值请参考数据手册。
  * 
  * 输入  Voltage: BOR电压点选择，取值为:
  *                  PM_BOR_VOLTAGE_POINT_2
  *                  PM_BOR_VOLTAGE_POINT_3

  * 返回  无。
  */
void PM_BOR_Voltage_Config (uint32_t Voltage)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_BOR_VOLTAGE(Voltage));

    /*---------------- 配置PM_CAL0寄存器BORSEL位 ----------------*/
    PM_CAL0 = SFR_Config (PM_CAL0, ~PM_CAL0_BORSEL, Voltage);
}






/**
  * 描述  设置外部低频振荡器引脚选择位。
  * 输入  PeripheralPort: 设置外部低频振荡器引脚IO口，取值为:
  *                         PM_EXTLF_PIN1_IO_PORT: 选择外部低频晶振1
  *                         PM_EXTLF_PIN2_IO_PORT: 选择外部低频晶振2
  * 返回  无。
  */
void PM_EXTLF_PIN_Selection_Config (uint32_t PeripheralPort)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_EXTLF_PIN_IO(PeripheralPort));

    /*---------------- 设置PM_CTL1寄存器LSESEL位 ----------------*/
    if (PeripheralPort != PM_EXTLF_PIN1_IO_PORT)
    {
        /* 选择外部低频晶振2*/
        SFR_SET_BIT_ASM(PM_CAL1, PM_CAL1_LSE_SEL_POS);
    }
    else
    {
        /* 选择外部低频晶振1 */
        SFR_CLR_BIT_ASM(PM_CAL1, PM_CAL1_LSE_SEL_POS);
    }
}

/**
  * 描述  设置外部高频振荡器引脚选择位。
  * 输入  PeripheralPort: 设置外部高频振荡器引脚IO口，取值为:
  *                         PM_EXTHF_PIN1_IO_PORT: 选择外部高频晶振1
  *                         PM_EXTHF_PIN2_IO_PORT: 选择外部高频晶振2
  * 返回  无。
  */
void PM_EXTHF_PIN_Selection_Config (uint32_t PeripheralPort)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_EXTHF_PIN_IO(PeripheralPort));

    /*---------------- 设置PM_CTL1寄存器HSESEL位 ----------------*/
    if (PeripheralPort != PM_EXTHF_PIN1_IO_PORT)
    {
        /* 选择外部低频晶振2*/
        SFR_SET_BIT_ASM(PM_CAL1, PM_CAL1_HSE_SEL_POS);
    }
    else
    {
        /* 选择外部低频晶振1 */
        SFR_CLR_BIT_ASM(PM_CAL1, PM_CAL1_HSE_SEL_POS);
    }
}




/**
  *   ##### 电源管理(PM)校准控制函数定义结束 #####
  */

