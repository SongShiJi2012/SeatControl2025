/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_pm.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
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
  * 描述  设置外部低频振荡器时钟输入使能。
  * 输入  NewState: 外部低频振荡器时钟输入使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_External_Low_Frequency_Clock_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器LSEEXEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 可直接从外部低频晶振输入口外接时钟信号作为晶振输入 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_LSEEXEN_POS);
    }
    else
    {
        /* 禁止外部时钟输入功能 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_LSEEXEN_POS);
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
  * 描述  设置LPRAM在在 stop1 和 standby 模式下工作配置。
  * 输入  WorkMode: LPRAM在 stop1 和 standby 模式下工作配置，取值为:
  *                   PM_LPRAM_IN_STANDBY_POWER_DOWN: LPRAM在standby模式下掉电
  *                   PM_LPRAM_IN_STANDBY_KEEP_DATA: LPRAM在standby模式下保持数据
  * 返回  无。
  */
void PM_LPRAM_In_Standby_Stop1_Work_Mode_Config (uint32_t WorkMode)
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
  * 描述  设置内部测试输出BUFFER时钟使能。
  * 输入  NewState: 内部测试输出BUFFER时钟使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Internal_Test_Buffer_Clock_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器BUFCLKEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能内部测试输出BUFFER工作时钟 */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_BUFCLKEN_POS);
    }
    else
    {
        /* 禁止内部测试输出BUFFER工作时钟 */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_BUFCLKEN_POS);
    }
}

/**
  * 描述  设置内部测试输出BUFFER工作时钟分频。
  * 输入  SclkScaler: 内部测试输出BUFFER工作时钟分频，取值为:
  *                     PM_BUFFER_SCLK_DIV_1: SCLK
  *                     PM_BUFFER_SCLK_DIV_2: SCLK/2
  *                     PM_BUFFER_SCLK_DIV_4: SCLK/4
  *                     PM_BUFFER_SCLK_DIV_8: SCLK/8
  *                     PM_BUFFER_SCLK_DIV_16: SCLK/16
  *                     PM_BUFFER_SCLK_DIV_32: SCLK/32
  *                     PM_BUFFER_SCLK_DIV_64: SCLK/64
  *                     PM_BUFFER_SCLK_DIV_128: SCLK/128
  * 返回  无。
  */
void PM_Internal_Test_Buffer_Clock_Scaler_Config (uint32_t SclkScaler)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_BUFFER_SCLK_SCALER(SclkScaler));

    /*---------------- 配置PM_CTL1寄存器BUFCLKDIV位 ----------------*/
    PM_CTL1 = SFR_Config (PM_CTL1, ~PM_CTL1_BUFCLKDIV, SclkScaler);
}

/**
  * 描述  设置BAT_BOR电压点选择。
  * 输入  Voltage: BAT_BOR电压点选择，取值为:
  *                  PM_BATTERY_VOLTAGE_1P6V: 1.6V
  *                  PM_BATTERY_VOLTAGE_1P8V: 1.8V
  *                  PM_BATTERY_VOLTAGE_2P06V: 2.06V
  *                  PM_BATTERY_VOLTAGE_2P4V: 2.4V
  *                  PM_BATTERY_VOLTAGE_2P88V: 2.88V
  *                  PM_BATTERY_VOLTAGE_3P6V: 3.6V
  * 返回  无。
  */
void PM_Battery_BOR_Config (uint32_t Voltage)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_BATTERY_VOLTAGE(Voltage));

    /*---------------- 配置PM_CTL1寄存器BATBORSEL位 ----------------*/
    PM_CTL1 = SFR_Config (PM_CTL1, ~PM_CTL1_BATBORSEL, Voltage);
}

/**
  * 描述  设置BAT_BOR使能。
  * 输入  NewState: BAT_BOR使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Battery_BOR_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器BATBOREN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能BAT_BOR */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_BATBOREN_POS);
    }
    else
    {
        /* 禁止BAT_BOR */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_BATBOREN_POS);
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
  * 输入  Voltage: 电压检测点选择，取值为:
  *                  PM_VOLTAGE_DETECTION_2P1V: 2.1V
  *                  PM_VOLTAGE_DETECTION_2P25V: 2.25V
  *                  PM_VOLTAGE_DETECTION_2P4V: 2.4V
  *                  PM_VOLTAGE_DETECTION_2P55V: 2.55V
  *                  PM_VOLTAGE_DETECTION_2P7V: 2.7V
  *                  PM_VOLTAGE_DETECTION_2P85V: 2.85V
  *                  PM_VOLTAGE_DETECTION_2P95V: 2.95V
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
  * 描述  LPR类型选择。
  * 输入  LPRMODE: LPR类型选择，取值为:
  *                  PM_LPR_MODE_CAPLESS
  *                  PM_LPR_MODE_CAP
  * 返回  无。
  */
void PM_BKP_LPR_Type_Select(uint32_t LPRMODE)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_PM_BKPLPR_MODE(LPRMODE));

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_BKPLPRTYPE, LPRMODE << PM_CTL1_BKPLPRTYPE_POS);
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

	PM_CTL1 = SFR_Config(PM_CTL1, ~PM_CTL1_DPRAMECCEN, NewState << PM_CTL1_DPRAMECCEN_POS);
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
  *                     PM_PERIPHERAL_EWM: EWM
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
  *                     PM_PERIPHERAL_EWM: EWM
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
  * 描述  设置主电源POR强制使能。
  * 输入  NewState: 主电源POR强制使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Vdd_Por_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL0寄存器VDDPORON位 ----------------*/
    if (NewState != FALSE)
    {
        /*  shutdown模式下强制使能VDD_POR */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_VDDPORON_POS);
    }
    else
    {
        /* shutdown模式下硬件将自动关闭VDD_POR */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_VDDPORON_POS);
    }
}

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

/**
  * 描述  设置功耗模式时序选择。
  * 输入  Mode: 功耗模式时序选择，取值为:
  *               PM_POWER_DISSIPATION_SCHEME1: Scheme1，新增简易时序
  *               PM_POWER_DISSIPATION_SCHEME2: Scheme2，时序参考4003，较复杂
  * 返回  无。
  */
void PM_Power_Dissipation_Mode_Config (uint32_t Mode)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_POWER_DISSIPATION(Mode));

    /*---------------- 设置PM_CTL0寄存器PDMSEL位 ----------------*/
    if (Mode != PM_POWER_DISSIPATION_SCHEME1)
    {
        /* Scheme2，时序参考4003，较复杂 */
        SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_PDMSEL_POS);
    }
    else
    {
        /* Scheme1，新增简易时序 */
        SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_PDMSEL_POS);
    }
}

/**
  * 描述  设置POR12关闭到LDO关闭的延时时间。
  * 输入  DelayTime: POR12关闭到LDO关闭的延时时间配置，取值为:
  *                    PM_POWER_DISSIPATION_500ns: 500ns
  *                    PM_POWER_DISSIPATION_500ns_1T: 500ns+1* T(INTLFOSC)
  *                    PM_POWER_DISSIPATION_500ns_2P5T: 500ns+2.5* T(INTLFOSC)
  * 返回  无。
  */
void PM_Power_Dissipation_Mode_Delay_Config (uint32_t DelayTime)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_POWER_DISSIPATION_DELAY(DelayTime));

    /*---------------- 配置PM_CTL0寄存器PDMDELAY位 ----------------*/
    PM_CTL0 = SFR_Config (PM_CTL0, ~PM_CTL0_PDMDELAY, DelayTime);
}

/**
  * 描述  设置内部测试输出BUFFER使能。
  * 输入  NewState: 内部测试输出BUFFER使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
void PM_Internal_Test_Buffer_Enable (FunctionalState NewState)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- 设置PM_CTL1寄存器INTBUFEN位 ----------------*/
    if (NewState != FALSE)
    {
        /* 使能内部测试输出BUFFER */
        SFR_SET_BIT_ASM(PM_CTL1, PM_CTL1_INTBUFEN_POS);
    }
    else
    {
        /* 禁止内部测试输出BUFFER */
        SFR_CLR_BIT_ASM(PM_CTL1, PM_CTL1_INTBUFEN_POS);
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
  * 描述  设置零温漂电流档校准。
  * 输入  Calibration: 零温漂电流档校准，取值为:
  *                      PM_CURRENT_OUTPUT_2uA: 输出电流2uA
  *                      PM_CURRENT_REDUCE_10_PERCENT: 电流减小加10%
  *                      PM_CURRENT_INCREASE_10_PERCENT: 电流增加10%
  *                      PM_CURRENT_INCREASE_20_PERCENT: 电流增加20%
  * 返回  无。
  */
// void PM_Zero_Drift_Current_Config (uint32_t Calibration)
// {
//     /* 参数校验 */
//     CHECK_RESTRICTION(CHECK_PM_CURRENT_CONFIG(Calibration));

//     /*---------------- 配置PM_CAL0寄存器ZEROTISTRIM位 ----------------*/
//     PM_CAL0 = SFR_Config (PM_CAL0, ~PM_CAL0_ZEROTISTRIM, Calibration);
// }

/**
  * 描述  设置BOR电压点选择。
  * 输入  Voltage: BOR电压点选择，取值为:
  *                  PM_BOR_VOLTAGE_2P45V: BOR电压点为2.45V
  *                  PM_BOR_VOLTAGE_2P65V: BOR电压点为2.65V

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
  * 描述  设置MR或MR_HV模块校准。
  * 输入  MRSel: MR或MR_HV模块选择，取值为：
  *                PM_MR_MODULE: MR模块
  *                PM_MR_HV_MODULE: MR_HV模块
  *       Voltage: 校准电压选择，取值为:
  *                  PM_MR_VOLTAGE_1P2V: BOR电压点为1.2V
  *                  PM_MR_VOLTAGE_0P9V: BOR电压点为0.9V
  *                  PM_MR_VOLTAGE_1V: BOR电压点为1V
  *                  PM_MR_VOLTAGE_1P32V: BOR电压点为1.32V
  * 返回  无。
  */
// void PM_Main_Regulator_Voltage_Config (uint32_t MRSel, uint32_t Voltage)
// {
//     uint32_t tmpreg;
//     uint32_t tmpmask;

//     /* 参数校验 */
//     CHECK_RESTRICTION(CHECK_PM_MR_MODULE(MRSel));
//     CHECK_RESTRICTION(CHECK_PM_MR_VOLTAGE(Voltage));

//     /*------------- 配置PM_CAL0寄存器MRTRIM或MRHVTRIM位 -------------*/
//     tmpreg = Voltage << MRSel;
//     tmpmask = (uint32_t)0xF << MRSel;
//     PM_CAL0 = SFR_Config (PM_CAL0, ~tmpmask, tmpreg);
// }

/**
  * 描述  设置MR_HV模块软件使能。
  * 输入  NewState: MR_HV模块软件使能状态，取值为TRUE 或 FALSE。
  * 返回  无。
  */
// void PM_Main_Regulator_HV_Enable (FunctionalState NewState)
// {
//     /* 参数校验 */
//     CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

//     /*---------------- 设置PM_CAL0寄存器MRHVEN位 ----------------*/
//     if (NewState != FALSE)
//     {
//         /* 使能MR_HV模块 */
//         SFR_SET_BIT_ASM(PM_CAL0, PM_CAL0_MRHVEN_POS);
//     }
//     else
//     {
//         /* 禁止MR_HV模块 */
//         SFR_CLR_BIT_ASM(PM_CAL0, PM_CAL0_MRHVEN_POS);
//     }
// }

/**
  * 描述  设置不同的基准校准。
  * 输入  Reference: 不同的基准选择，取值为：
  *                    PM_REFERENCE_LDO12: LDO12基准校准
  *                    PM_REFERENCE_LDO18: LDO18基准校准
  *       Calibration: 校准电压选择，
  *                    PM_REFERENCE_LDO12取值范围为0~0x1F,
  *                    PM_REFERENCE_LDO18取值范围为0~0x1F。
  * 返回  无。
  */
// void PM_Reference_Calibration_Config (uint32_t Reference, uint32_t Calibration)
// {
//     uint32_t tmpreg;
//     uint32_t tmpmask;

//     /* 参数校验 */
//     switch (Reference)
//     {
//         case PM_REFERENCE_LDO12:
//             CHECK_RESTRICTION(CHECK_PM_LDO12_CALIBRATION(Calibration));
//             tmpreg = Calibration << PM_REFERENCE_LDO12;
//             tmpmask = PM_CAL0_BGTRIMMRLDO;
//             break;
//         case PM_REFERENCE_LDO18:
//             CHECK_RESTRICTION(CHECK_PM_LDO18_CALIBRATION(Calibration));
//             tmpreg = Calibration << PM_REFERENCE_LDO18;
//             tmpmask = PM_CAL0_BGTRIMFLLDO;
//             break;
//         default:
//             CHECK_RESTRICTION(0);
//             break;
//     }

//     /*------------- 配置PM_CAL0寄存器对应的校准位域 -------------*/
//     PM_CAL0 = SFR_Config (PM_CAL0, ~tmpmask, tmpreg);
// }

/**
  * 描述  设置内部低频振荡器电流校准。
  * 输入  Calibration: 偏置电流选择，取值为：
  *                      PM_INTLF_BIAS_CURRENT_10nA: 10nA
  *                      PM_INTLF_BIAS_CURRENT_12P5nA: 12.5nA
  *                      PM_INTLF_BIAS_CURRENT_15nA: 15nA
  *                      PM_INTLF_BIAS_CURRENT_17P5nA: 17.5nA
  *                      PM_INTLF_BIAS_CURRENT_0nA: 0nA
  *                      PM_INTLF_BIAS_CURRENT_2P5nA: 2.5nA
  *                      PM_INTLF_BIAS_CURRENT_5nA: 5nA
  *                      PM_INTLF_BIAS_CURRENT_7P5nA: 7.5nA
  * 返回  无。
  */
void PM_INTLF_Bias_Current_Config (uint32_t Calibration)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_INTLF_BIAS_CURRENT(Calibration));

    /*------------- 配置PM_CAL1寄存器LSITRIMBIAS域 -------------*/
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LSI_TRIM_BIAS, Calibration);
}

/**
  * 描述  设置外部低频振荡器电流校准。
  * 输入  Calibration: 偏置电流选择，取值为：
  *                      PM_EXTLF_BIAS_CURRENT_20nA: 20nA
  *                      PM_EXTLF_BIAS_CURRENT_25nA: 25nA
  *                      PM_EXTLF_BIAS_CURRENT_30nA: 30nA
  *                      PM_EXTLF_BIAS_CURRENT_35nA: 35nA
  *                      PM_EXTLF_BIAS_CURRENT_0nA: 0nA
  *                      PM_EXTLF_BIAS_CURRENT_5nA: 5nA
  *                      PM_EXTLF_BIAS_CURRENT_10nA: 10nA
  *                      PM_EXTLF_BIAS_CURRENT_15nA: 15nA
  * 返回  无。
  */
void PM_EXTLF_Bias_Current_Config (uint32_t Calibration)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_EXTLF_BIAS_CURRENT(Calibration));

    /*------------- 配置PM_CAL1寄存器LSETRIMBIAS域 -------------*/
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LSE_TRIMBIAS, Calibration);
}

/**
  * 描述  设置内部低频振荡器电容校准。
  * 输入  Calibration: 校准值，取值范围为0~0x1F。
  * 返回  无。
  */
void PM_INTLF_Capacitance_Calibration_Config (uint32_t Calibration)
{
	uint32_t tmpreg;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_CAPACITANCE_CALIBRATION(Calibration));

    /*------------- 配置PM_CAL1寄存器LSITRIMCAP域 -------------*/
    tmpreg = Calibration << PM_CAL1_LSI_TRIM_CAP0_POS;
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LSI_TRIM_CAP, tmpreg);
}

/**
  * 描述  设置低功耗偏置电流校准。
  * 输入  Calibration: 校准值，取值范围为0~0x7。
  * 返回  无。
  */
void PM_LP_Bias_Calibration_Config (uint32_t Calibration)
{
	uint32_t tmpreg;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_LP_BIAS_CALIBRATION(Calibration));

    /*------------- 配置PM_CAL1寄存器LPTRIMBIAS域 -------------*/
    tmpreg = Calibration << PM_CAL1_LP_TRIM_BIAS0_POS;
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LP_TRIM_BIAS, tmpreg);
}

/**
  * 描述  设置内部低频振荡器电容校准。
  * 输入  Calibration: 校准值，取值范围为0~0x7。
  * 返回  无。
  */
void PM_LPBG_Pump_Calibration_Config (uint32_t Calibration)
{
	uint32_t tmpreg;
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_PUMP_CALIBRATION(Calibration));

    /*------------- 配置PM_CAL1寄存器LPBGTRIMPUMP域 -------------*/
    tmpreg = Calibration << PM_CAL1_LPBG_TRIM_PUMP0_POS;
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LPBG_TRIM_PUMP, tmpreg);

}

/**
  * 描述  设置外部低频振荡器N管偏置校准。
  * 输入  Calibration: 电流选择，取值为：
  *                      PM_BRANCH_CURRENT_NONE: 没有增加支路电流
  *                      PM_BRANCH_CURRENT_50_PERCENT: 增加50%支路电流
  *                      PM_BRANCH_CURRENT_150_PERCENT: 增加150%支路电流
  *                      PM_BRANCH_CURRENT_200_PERCENT: 增加200%支路电流
  * 返回  无。
  */
void PM_EXTLF_N_Bias_Current_Config (uint32_t Calibration)
{
    /* 参数校验 */
    CHECK_RESTRICTION(CHECK_PM_BRANCH_CURRENT(Calibration));

    /*------------- 配置PM_CAL1寄存器LSETRIMNBIAS域 -------------*/
    PM_CAL1 = SFR_Config (PM_CAL1, ~PM_CAL1_LSE_TRIM_NBIAS, Calibration);
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

///**
//  * 描述  设置LPR内置模块选择。
//  * 输入  ModeSel: LPR内置模块选择，取值为:
//  *                  PM_LPR_DEFAULT: 低功耗模式
//  *                  PM_LPR_BACKUP: 高功耗模式
//  * 返回  无。
//  */
//void PM_LPR_Module_Config (uint32_t ModeSel)
//{
//    /* 参数校验 */
//    CHECK_RESTRICTION(CHECK_PM_LPR_MODE(ModeSel));
//
//    /*---------------- 设置PM_CAL0寄存器MRBGSEL位 ----------------*/
//    if (ModeSel != PM_LPR_DEFAULT)
//    {
//        /* 高功耗模式 */
//        SFR_SET_BIT_ASM(PM_CAL0, PM_CAL0_MRBGSEL_POS);
//    }
//    else
//    {
//        /* 低功耗模式 */
//        SFR_CLR_BIT_ASM(PM_CAL0, PM_CAL0_MRBGSEL_POS);
//    }
//}

/**
  * 描述  设置外部复位引脚 NRST1（PH7）、NRST0（PD0） 软件使能。
  * 输入  NRSTPIN: 复位引脚选择，取值为:PM_NRST0、PM_NRST1
  * 	 NewState: TURE 使能\FALSE 禁止
  * 返回  无。
  */
// void PM_Reset_Pin_Config(uint32_t NRSTPIN, FunctionalState NewState)
// {
// 	uint32_t tmpreg;
// 	uint32_t tmask;

// 	/* 参数校验 */
// 	CHECK_RESTRICTION(CHECK_PM_NRST_PIN(NRSTPIN));
// 	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

// 	tmpreg = NewState << (PM_CAL0_NRST0EN_POS + NRSTPIN);
// 	tmask = 1 << (PM_CAL0_NRST0EN_POS + NRSTPIN);

// 	PM_CAL0 = SFR_Config(PM_CAL0, ~tmask, tmpreg);
// }

/**
  * 描述  设置IWDT 使能。
  * 输入  NewState:
  * 			TURE 使能 IWDT
  *				FALSE 无作用
  * 返回  无
  * 备注：使能后也会自动使能内部低频 INTLF， 且产生 IWDT 复位时不复位 IWDT 自身
  */
// void PM_IWDT_Enable(FunctionalState NewState)
// {
// 	/* 参数校验 */
// 	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

// 	PM_CAL0 = SFR_Config(PM_CAL0, ~PM_CAL0_PM_IWDTEN, NewState << PM_CAL0_PM_IWDTEN_POS);
// }

/**
  * 描述  设置LPR12 capless 电流调整位。
  * 输入  Calibration: Calibration <= 0x1F
  * 返回  无
  */
void PM_LPR12_CAPLESS_I_Config(uint32_t Calibration)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_PM_LPR12_CAPLESS_I(Calibration));

	PM_CAL2 = SFR_Config(PM_CAL2, ~PM_CAL2_LPR12_CAPLESS_I, Calibration << PM_CAL2_LPR12_CAPLESS_I0_POS);
}

/**
  * 描述  设置LPR12 capless 功耗控制位。
  * 输入  Calibration:
  * 			PM_LPR12_PC_MAX_90uA: MR12capless 使用最大功耗 90uA
  *				PM_LPR12_PC_MIN_20uA: MR12capless 使用最小功耗 20uA
  *				PM_LPR12_PC_MEDIUM_40uA: MR12capless 使用中等功耗 40uA
  * 返回  无
  */
void PM_MR12_Capless_PC_Config(uint32_t Calibration)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_PM_LPR12_PC(Calibration));

	PM_CAL2 = SFR_Config(PM_CAL2, ~PM_CAL2_CAP_FREE_LDO_IS, Calibration << PM_CAL2_CAP_FREE_LDO_IS0_POS);
}

/**
  * 描述  设置参考 BUFFER 基准校准。
  * 输入  Calibration: Calibration <= 0x3F
  * 返回  无
  */
void PM_BGTRIMREBUF_Config(uint32_t Calibration)
{
	/* 参数校验 */
	CHECK_RESTRICTION(CHECK_PM_BGTRIMREBUF_VALUE(Calibration));

	PM_CAL2 = SFR_Config(PM_CAL2, ~PM_CAL2_BGTRIMREFBUF, Calibration << PM_CAL2_BGTRIMREFBUF0_POS);
}


/**
  *   ##### 电源管理(PM)校准控制函数定义结束 #####
  */

