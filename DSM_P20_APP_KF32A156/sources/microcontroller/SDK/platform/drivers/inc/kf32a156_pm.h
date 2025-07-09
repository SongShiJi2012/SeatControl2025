/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_pm.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file contains the headers of the PM
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

#ifndef KF32A156_PM_H_
#define KF32A156_PM_H_

#include "KF32A156.h"


/**
  * 备份区寄存器模块软件复位
  */
#define PERIPHERAL_RST_STATUS           ((uint32_t)0)
#define PERIPHERAL_OUTRST_STATUS        ((uint32_t)1)
#define CHECK_PERIPHERAL_RST(RST)       (((RST) == PERIPHERAL_RST_STATUS) \
                                      || ((RST) == PERIPHERAL_OUTRST_STATUS))

/**
  * DPRAM的B区在standby模式下工作配置
  */
#define PM_DPRAM_IN_STANDBY_POWER_DOWN   ((uint32_t)0)
#define PM_DPRAM_IN_STANDBY_KEEP_DATA    ((uint32_t)1)
#define CHECK_PM_DPRAM_IN_STANDBY(MODE)  (((MODE) == PM_DPRAM_IN_STANDBY_POWER_DOWN) \
                                      || ((MODE) == PM_DPRAM_IN_STANDBY_KEEP_DATA))

/**
  * LPRAM在standby模式下工作配置
  */
#define PM_LPRAM_IN_STANDBY_POWER_DOWN   ((uint32_t)0)
#define PM_LPRAM_IN_STANDBY_KEEP_DATA    ((uint32_t)1)
#define CHECK_PM_LPSRAM_IN_STANDBY(MODE)  (((MODE) == PM_LPRAM_IN_STANDBY_POWER_DOWN) \
                                      || ((MODE) == PM_LPRAM_IN_STANDBY_KEEP_DATA))


/**
  * 延时时间
  */
#define DELAY_TIME_1ms                  ((uint32_t)0)
#define DELAY_TIME_2ms                  ((uint32_t)0)
#define DELAY_TIME_32us                 ((uint32_t)1)
#define DELAY_TIME_500us                ((uint32_t)1)
#define CHECK_DELAY_TIME(TIME)          (((TIME) == DELAY_TIME_1ms) \
                                      || ((TIME) == DELAY_TIME_2ms) \
                                      || ((TIME) == DELAY_TIME_32us) \
                                      || ((TIME) == DELAY_TIME_500us))

/**
  * 低功耗外设IO口
  */
#define PM_GENERAL_PURPOSE_IO_PORT      ((uint32_t)0<<PM_CTL0_PHERIIOSEL_POS)
#define PM_LOW_POWER_IO_PORT            ((uint32_t)1<<PM_CTL0_PHERIIOSEL_POS)
#define CHECK_PM_LOW_POWER_IO(CFG)      (((CFG) == PM_GENERAL_PURPOSE_IO_PORT) \
                                      || ((CFG) == PM_LOW_POWER_IO_PORT))

/**
  * 低频晶振IO口
  */
#define PM_EXTLF_PIN1_IO_PORT      ((uint32_t)0<<PM_CAL1_LSE_SEL_POS)
#define PM_EXTLF_PIN2_IO_PORT      ((uint32_t)1<<PM_CAL1_LSE_SEL_POS)
#define CHECK_PM_EXTLF_PIN_IO(CFG)      (((CFG) == PM_EXTLF_PIN1_IO_PORT) \
                                      || ((CFG) == PM_EXTLF_PIN2_IO_PORT))
/**
  * 高频频晶振IO口
  */
#define PM_EXTHF_PIN1_IO_PORT      ((uint32_t)0<<PM_CAL1_HSE_SEL_POS)
#define PM_EXTHF_PIN2_IO_PORT      ((uint32_t)1<<PM_CAL1_HSE_SEL_POS)
#define CHECK_PM_EXTHF_PIN_IO(CFG)      (((CFG) == PM_EXTHF_PIN1_IO_PORT) \
                                      || ((CFG) == PM_EXTHF_PIN2_IO_PORT))

/**
  * 低功耗模式
  */
#define PM_LOW_POWER_MODE_STOP_0        ((uint32_t)1<<PM_CTL0_LPMS0_POS)
#define PM_LOW_POWER_MODE_STOP_1        ((uint32_t)2<<PM_CTL0_LPMS0_POS)
#define PM_LOW_POWER_MODE_STANDBY       ((uint32_t)3<<PM_CTL0_LPMS0_POS)
#define PM_LOW_POWER_MODE_SHUTDOWN      ((uint32_t)4<<PM_CTL0_LPMS0_POS)
#define CHECK_PM_LOW_POWER_MODE(MODE)   (((MODE) == PM_LOW_POWER_MODE_STOP_0) \
                                      || ((MODE) == PM_LOW_POWER_MODE_STOP_1) \
                                      || ((MODE) == PM_LOW_POWER_MODE_STANDBY) \
                                      || ((MODE) == PM_LOW_POWER_MODE_SHUTDOWN))


/**
  * 电压检测点
  */
#define PM_VOLTAGE_DETECTION_POINT_3      ((uint32_t)3<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_POINT_4      ((uint32_t)4<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_POINT_5      ((uint32_t)5<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_POINT_6      ((uint32_t)6<<PM_CTL1_PVDS0_POS)
#define CHECK_PM_VOLTAGE_DETECTION(VOL) (((VOL) == PM_VOLTAGE_DETECTION_POINT_3) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_POINT_4) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_POINT_5) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_POINT_6))

/**
  * 触发沿选择
  */
#define PM_TRIGGER_RISE_EDGE            ((uint32_t)0)
#define PM_TRIGGER_FALL_EDGE            ((uint32_t)1)
#define CHECK_PM_TRIGGER_EDGE(EDGE)     (((EDGE) == PM_TRIGGER_RISE_EDGE) \
                                      || ((EDGE) == PM_TRIGGER_FALL_EDGE))

/**
  * WKP引脚
  */
#define PM_PIN_WKP1                     ((uint32_t)0)
#define PM_PIN_WKP2                     ((uint32_t)1)
#define PM_PIN_WKP3                     ((uint32_t)2)
#define PM_PIN_WKP4                     ((uint32_t)3)
#define PM_PIN_WKP5                     ((uint32_t)4)
#define CHECK_PM_PIN_WKP(PIN)           (((PIN) == PM_PIN_WKP1) \
                                      || ((PIN) == PM_PIN_WKP2) \
                                      || ((PIN) == PM_PIN_WKP3) \
                                      || ((PIN) == PM_PIN_WKP4) \
                                      || ((PIN) == PM_PIN_WKP5))

/**
  * Stop模式下的外设
  */
#define PM_PERIPHERAL_CAN6              ((uint32_t)0)
#define PM_PERIPHERAL_CCP               ((uint32_t)1)
#define PM_PERIPHERAL_EWDT              ((uint32_t)2)
#define PM_PERIPHERAL_USART0            ((uint32_t)3)
#define CHECK_PM_PERIPHERAL(PERIPH)     (((PERIPH) == PM_PERIPHERAL_CAN6) \
                                      || ((PERIPH) == PM_PERIPHERAL_CCP) \
                                      || ((PERIPH) == PM_PERIPHERAL_EWDT) \
                                      || ((PERIPH) == PM_PERIPHERAL_USART0))

/**
  * 复位/唤醒事件
  */
#define PM_RESET_IWDT                   (PM_STA0_IWDTF_POS)
#define PM_WAKEUP_EXTERNAL_PIN          (PM_STA0_WKPPINF_POS)
#define PM_RESET_POR                    (PM_STA0_PORF_POS)
#define PM_RESET_BOR                    (PM_STA0_BORF_POS)
#define PM_RESET_SOFTWARE               (PM_STA0_WSRSTF_POS)
#define PM_RESET_BKPBOR                 (PM_STA0_BKPPORIF_POS)
#define PM_RESET_NRST               	(PM_STA0_NRSTIF_POS)
#define PM_WAKEUP_EXTERNAL_PIN_WKP5     (PM_STA1_WKP5STA_POS + (uint32_t)32)
#define PM_WAKEUP_EXTERNAL_PIN_WKP4     (PM_STA1_WKP4STA_POS + (uint32_t)32)
#define PM_WAKEUP_EXTERNAL_PIN_WKP3     (PM_STA1_WKP3STA_POS + (uint32_t)32)
#define PM_WAKEUP_EXTERNAL_PIN_WKP2     (PM_STA1_WKP2STA_POS + (uint32_t)32)
#define PM_WAKEUP_EXTERNAL_PIN_WKP1     (PM_STA1_WKP1STA_POS + (uint32_t)32)
#define CHECK_PM_RESET_WAKEUP(SEL)      (((SEL) == PM_RESET_IWDT) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN) \
                                      || ((SEL) == PM_RESET_POR) \
                                      || ((SEL) == PM_RESET_BOR) \
                                      || ((SEL) == PM_RESET_SOFTWARE) \
                                      || ((SEL) == PM_RESET_BKPBOR) \
                                      || ((SEL) == PM_RESET_NRST) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP5) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP4) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP3) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP2) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP1))
#define CHECK_CLEAR_STA0_RESET_WAKEUP(SEL)	 (((SEL) == PM_RESET_IWDT) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN) \
                                      || ((SEL) == PM_RESET_POR) \
                                      || ((SEL) == PM_RESET_BOR) \
                                      || ((SEL) == PM_RESET_SOFTWARE)\
                                      || ((SEL) == PM_RESET_BKPBOR) \
									  || ((SEL) == PM_RESET_NRST))

#define CHECK_CLEAR_STA1_WAKEUP(SEL)	(((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP5) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP4) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP3) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP2) \
                                      || ((SEL) == PM_WAKEUP_EXTERNAL_PIN_WKP1))


/**
  * BOR电压点选择
  */
#define PM_BOR_VOLTAGE_POINT_2            ((uint32_t)2<<PM_CAL0_BORSEL0_POS)
#define PM_BOR_VOLTAGE_POINT_3            ((uint32_t)3<<PM_CAL0_BORSEL0_POS)
#define CHECK_PM_BOR_VOLTAGE(CFG)       (((CFG) == PM_BOR_VOLTAGE_POINT_2) \
                                      || ((CFG) == PM_BOR_VOLTAGE_POINT_3))
/**
  * VREF电压点选择
  */
#define PM_VREF_VOLTAGE_4P0V            ((uint32_t)0<<PM_CTL1_VREFSEL0_POS)
#define PM_VREF_VOLTAGE_1P5V            ((uint32_t)1<<PM_CTL1_VREFSEL0_POS)
#define PM_VREF_VOLTAGE_2P0V            ((uint32_t)2<<PM_CTL1_VREFSEL0_POS)
#define PM_VREF_VOLTAGE_3P0V            ((uint32_t)3<<PM_CTL1_VREFSEL0_POS)
#define CHECK_PM_VREF_VOLTAGE(CFG)      (((CFG) == PM_VREF_VOLTAGE_4P0V) \
                                      || ((CFG) == PM_VREF_VOLTAGE_1P5V) \
                                      || ((CFG) == PM_VREF_VOLTAGE_2P0V) \
                                      || ((CFG) == PM_VREF_VOLTAGE_3P0V))


/**
 * 	LPCAN工作时钟选择
 * */
#define PM_LPCAN_SCK_INTLF				((uint32_t)0)
#define PM_LPCAN_SCK_LP4M				((uint32_t)1)
#define CHECK_PM_LPCAN_SCK(CLK)			((CLK) <= PM_LPCAN_SCK_LP4M)



/* 电源管理(PM)控制功能函数定义*********************************************/
void PM_IO_Latch_Enable (FunctionalState NewState);
FlagStatus PM_Get_IO_Latch_Status (void);
void PM_Internal_Low_Frequency_Enable (FunctionalState NewState);
void PM_External_Low_Frequency_Enable (FunctionalState NewState);
void PM_Main_Bandgap_Enable (FunctionalState NewState);
void PM_LDO18_Enable (FunctionalState NewState);
void PM_Backup_Registers_Reset_Config (uint32_t BkpReset);
void PM_Independent_Watchdog_Reset_Config (uint32_t IWDTReset);
void PM_DPRAM_In_Standby_Work_Mode_Config (uint32_t WorkMode);
void PM_LPRAM_DPRAMA_In_Standby_Stop1_Work_Mode_Config (uint32_t WorkMode);
void PM_Backup_POR_Delay_Time_Config (uint32_t DelayTime);
void PM_Main_POR_Delay_Time_Config (uint32_t DelayTime);
void PM_Peripheral_IO_Port_Config (uint32_t PeripheralPort);
void PM_OCAL0LOCK_Enable (FunctionalState NewState);
void PM_MEMSEL_Enable (FunctionalState NewState);
void PM_Flash_Power_Off_Enable (FunctionalState NewState);
void PM_Backup_Write_And_Read_Enable (FunctionalState NewState);
void PM_LPR_Software_Enable (FunctionalState NewState);
void PM_Low_Power_Mode_Config (uint32_t LowPowerMode);
void PM_BOR_Enable (FunctionalState NewState);
void PM_Low_Power_BOR_Enable (FunctionalState NewState);
void PM_Temperature_Sensor_Enable (FunctionalState NewState);
void PM_Temperature_Sensor_Buffer_Enable (FunctionalState NewState);
void PM_Reference_Voltage_Enable (FunctionalState NewState);
void PM_CCP0LPEN_ENABLE(FunctionalState NewState);
void PM_CCP0CLKLPEN_Enable (FunctionalState NewState);
void PM_Peripheral_Voltage_Monitoring_Enable (FunctionalState NewState);
void PM_Voltage_Detection_Config (uint32_t Voltage);
void PM_Voltage_Detection_Enable (FunctionalState NewState);
void PM_EXTLF_PIN_Selection_Config (uint32_t PeripheralPort);
void PM_EXTHF_PIN_Selection_Config (uint32_t PeripheralPort);
void PM_External_Wakeup_Pin_Enable (uint32_t PinSel, FunctionalState NewState);
void PM_External_Wakeup_Edge_Config (uint32_t PinSel, uint32_t TriggerEdge);
void PM_Stop_Mode_Peripheral_INLF_Enable (uint32_t Peripheral,FunctionalState NewState);
void PM_Peripheral_Reset_Config (uint32_t Peripheral, uint32_t ResetStatus);
void PM_PMC_Error_Status_INT_Enable(FunctionalState NewState);
void PM_LP_DEBUG_Enable(FunctionalState NewState);
void PM_LVL_LDO18_Enable(FunctionalState NewState);
void PM_RAM_ECC_Enable(FunctionalState NewState);
void PM_LPCAN_Work_CLK_Select(uint32_t CLK);

#if _CLOSE_SERVICE_
void PM_Low_Power_Bandgap_Enable (FunctionalState NewState);
#endif /* _CLOSE_SERVICE_ */


/* 电源管理(PM)状态标志管理函数定义*****************************************/
RetStatus PM_Clear_Reset_And_Wakeup_Flag (uint32_t EventSel);
FlagStatus PM_Get_Reset_Flag (uint32_t EventSel);
RetStatus PM_Clear_External_Wakeup_Pin_Flag (uint32_t EventSel);
void PM_Clear_All_External_Wakeup_Pin_Flag ();
FlagStatus PM_Get_Low_Power_Running_State (void);
FlagStatus PM_Get_LPR_Status (void);
FlagStatus PM_Get_Peripheral_Voltage_Detection_Status (void);
FlagStatus PM_Stop_Mode_Error_Falg(void);
FlagStatus PM_PD_PMC_Error_Falg(void);
FlagStatus PM_POR18_Finish_Falg(void);
FlagStatus PM_Get_PMC_Error_INT_Falg(void);
void PM_Clear_PMCIF_Flag(void);
void PM_QEI0_Reset_Control(FunctionalState NewState);
void PM_GPIOA_Reset_Control(FunctionalState NewState);
void PM_RTC_Reset_Control(FunctionalState NewState);
void PM_QEI0_Work_Stop_INTLF_Enable(FunctionalState NewState);
void PM_RTC_Work_Stop_INTLF_Enable(FunctionalState NewState);

/* 电源管理(PM)校准控制函数定义*********************************************/
void PM_BOR_Voltage_Config (uint32_t Voltage);
void PM_EXTLF_PIN_Selection_Config(uint32_t PeripheralPort);
void PM_EXTHF_PIN_Selection_Config(uint32_t PeripheralPort);

#if _CLOSE_SERVICE_
void PM_VREF_SELECT (uint32_t Voltage);
void PM_VREF_Software_Enable (FunctionalState NewState);
#endif /* _CLOSE_SERVICE_ */


#endif /* KF32A156_PM_H_ */
