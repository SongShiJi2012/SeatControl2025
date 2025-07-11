/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_pm.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
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
  * 内部测试输出BUFFER工作时钟分频
  */
#define PM_BUFFER_SCLK_DIV_1            ((uint32_t)0<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_2            ((uint32_t)1<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_4            ((uint32_t)2<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_8            ((uint32_t)3<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_16           ((uint32_t)4<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_32           ((uint32_t)5<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_64           ((uint32_t)6<<PM_CTL1_BUFCLKDIV0_POS)
#define PM_BUFFER_SCLK_DIV_128          ((uint32_t)7<<PM_CTL1_BUFCLKDIV0_POS)
#define CHECK_PM_BUFFER_SCLK_SCALER(DIV) \
                                        (((DIV) == PM_BUFFER_SCLK_DIV_1) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_2) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_4) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_8) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_16) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_32) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_64) \
                                      || ((DIV) == PM_BUFFER_SCLK_DIV_128))

/**
  * BAT_BOR电压点选择
  */
#define PM_BATTERY_VOLTAGE_1P6V         ((uint32_t)0<<PM_CTL1_BATBORSEL0_POS)
#define PM_BATTERY_VOLTAGE_1P8V         ((uint32_t)1<<PM_CTL1_BATBORSEL0_POS)
#define PM_BATTERY_VOLTAGE_2P06V        ((uint32_t)2<<PM_CTL1_BATBORSEL0_POS)
#define PM_BATTERY_VOLTAGE_2P4V         ((uint32_t)3<<PM_CTL1_BATBORSEL0_POS)
#define PM_BATTERY_VOLTAGE_2P88V        ((uint32_t)4<<PM_CTL1_BATBORSEL0_POS)
#define PM_BATTERY_VOLTAGE_3P6V         ((uint32_t)5<<PM_CTL1_BATBORSEL0_POS)
#define CHECK_PM_BATTERY_VOLTAGE(VOL)   (((VOL) == PM_BATTERY_VOLTAGE_1P6V) \
                                      || ((VOL) == PM_BATTERY_VOLTAGE_1P8V) \
                                      || ((VOL) == PM_BATTERY_VOLTAGE_2P06V) \
                                      || ((VOL) == PM_BATTERY_VOLTAGE_2P4V) \
                                      || ((VOL) == PM_BATTERY_VOLTAGE_2P88V) \
                                      || ((VOL) == PM_BATTERY_VOLTAGE_3P6V))

/**
  * 电压检测点
  */
#define PM_VOLTAGE_DETECTION_2P1V       ((uint32_t)0<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P25V      ((uint32_t)1<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P4V       ((uint32_t)2<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P55V      ((uint32_t)3<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P7V       ((uint32_t)4<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P85V      ((uint32_t)5<<PM_CTL1_PVDS0_POS)
#define PM_VOLTAGE_DETECTION_2P95V      ((uint32_t)6<<PM_CTL1_PVDS0_POS)
#define CHECK_PM_VOLTAGE_DETECTION(VOL) (((VOL) == PM_VOLTAGE_DETECTION_2P1V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P25V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P4V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P55V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P7V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P85V) \
                                      || ((VOL) == PM_VOLTAGE_DETECTION_2P95V))

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
#define PM_PERIPHERAL_EWM               ((uint32_t)2)
#define PM_PERIPHERAL_USART0            ((uint32_t)3)
#define CHECK_PM_PERIPHERAL(PERIPH)     (((PERIPH) == PM_PERIPHERAL_CAN6) \
                                      || ((PERIPH) == PM_PERIPHERAL_CCP) \
                                      || ((PERIPH) == PM_PERIPHERAL_EWM) \
                                      || ((PERIPH) == PM_PERIPHERAL_USART0))

/**
  * 复位/唤醒事件
  */
#define PM_RESET_IWDT                   (PM_STA0_IWDTF_POS)
#define PM_WAKEUP_RTC_ALARM             (PM_STA0_RTCALRF_POS)
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
  * 零温漂电流档校准
  */
#define PM_CURRENT_OUTPUT_2uA           ((uint32_t)0<<PM_CAL0_ZEROTISTRIM0_POS)
#define PM_CURRENT_REDUCE_10_PERCENT    ((uint32_t)1<<PM_CAL0_ZEROTISTRIM0_POS)
#define PM_CURRENT_INCREASE_10_PERCENT  ((uint32_t)2<<PM_CAL0_ZEROTISTRIM0_POS)
#define PM_CURRENT_INCREASE_20_PERCENT  ((uint32_t)3<<PM_CAL0_ZEROTISTRIM0_POS)
#define CHECK_PM_CURRENT_CONFIG(CFG)    (((CFG) == PM_CURRENT_OUTPUT_2uA) \
                                      || ((CFG) == PM_CURRENT_REDUCE_10_PERCENT) \
                                      || ((CFG) == PM_CURRENT_INCREASE_10_PERCENT) \
                                      || ((CFG) == PM_CURRENT_INCREASE_20_PERCENT))

/**
  * BOR电压点选择
  */
#define PM_BOR_VOLTAGE_2P45V            ((uint32_t)2<<PM_CAL0_BORSEL0_POS)
#define PM_BOR_VOLTAGE_2P65V            ((uint32_t)3<<PM_CAL0_BORSEL0_POS)
#define CHECK_PM_BOR_VOLTAGE(CFG)       (((CFG) == PM_BOR_VOLTAGE_2P45V) \
                                      || ((CFG) == PM_BOR_VOLTAGE_2P65V))
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
  * MR电压选择
  */
#define PM_MR_VOLTAGE_1P2V              ((uint32_t)0)
#define PM_MR_VOLTAGE_1P08V             ((uint32_t)1)
#define PM_MR_VOLTAGE_1P32V             ((uint32_t)2)
#define CHECK_PM_MR_VOLTAGE(CFG)        (((CFG) == PM_MR_VOLTAGE_1P2V) \
                                      || ((CFG) == PM_MR_VOLTAGE_1P08V) \
                                      || ((CFG) == PM_MR_VOLTAGE_1P32V))

/**
  * MR或MR_HV模块选择
  */
#define PM_MRHV_VOLTAGE_1P2V              ((uint32_t)0)
#define PM_MRHV_VOLTAGE_0P9V              ((uint32_t)1)
#define PM_MRHV_VOLTAGE_1V                ((uint32_t)2)
#define PM_MRHV_VOLTAGE_1P32V             ((uint32_t)3)
#define CHECK_PM_MRHV_VOLTAGE(CFG)        (((CFG) == PM_MRHV_VOLTAGE_1P2V) \
                                      || ((CFG) == PM_MRHV_VOLTAGE_0P9V) \
                                      || ((CFG) == PM_MRHV_VOLTAGE_1V) \
                                      || ((CFG) == PM_MRHV_VOLTAGE_1P32V))

/**
  * PM校准基准
  */
#define PM_REFERENCE_LDO12              (PM_CAL0_BGTRIMMRLDO0_POS)
#define PM_REFERENCE_LDO18              (PM_CAL0_BGTRIMFLLDO0_POS)
#define CHECK_PM_REFERENCE(SEL)         (((SEL) == PM_REFERENCE_LDO12) \
                                      || ((SEL) == PM_REFERENCE_LDO18))

/**
  * 参考BUFFER基准校准
  */
#define CHECK_PM_BUFFER_CALIBRATION(CFG) \
                                        (((CFG) >> 5) == 0)

/**
  * LDO12基准校准
  */
#define CHECK_PM_LDO12_CALIBRATION(CFG) (((CFG) >> 5) == 0)

/**
  * LDO18基准校准
  */
#define CHECK_PM_LDO18_CALIBRATION(CFG) (((CFG) >> 5) == 0)

/**
  * 内部低频振荡器偏置电流
  */
#define PM_INTLF_BIAS_CURRENT_10nA      ((uint32_t)0<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_12P5nA    ((uint32_t)1<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_15nA      ((uint32_t)2<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_17P5nA    ((uint32_t)3<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_0nA       ((uint32_t)4<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_2P5nA     ((uint32_t)5<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_5nA       ((uint32_t)6<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define PM_INTLF_BIAS_CURRENT_7P5nA     ((uint32_t)7<<PM_CAL1_LSI_TRIM_BIAS0_POS)
#define CHECK_PM_INTLF_BIAS_CURRENT(SEL) \
                                        (((SEL) == PM_INTLF_BIAS_CURRENT_10nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_12P5nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_15nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_17P5nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_0nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_2P5nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_5nA) \
                                      || ((SEL) == PM_INTLF_BIAS_CURRENT_7P5nA))

/**
  * 外部低频振荡器偏置电流
  */
#define PM_EXTLF_BIAS_CURRENT_20nA      ((uint32_t)0<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_25nA      ((uint32_t)1<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_30nA      ((uint32_t)2<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_35nA      ((uint32_t)3<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_0nA       ((uint32_t)4<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_5nA       ((uint32_t)5<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_10nA      ((uint32_t)6<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define PM_EXTLF_BIAS_CURRENT_15nA      ((uint32_t)7<<PM_CAL1_LSE_TRIMBIAS0_POS)
#define CHECK_PM_EXTLF_BIAS_CURRENT(SEL) \
                                        (((SEL) == PM_EXTLF_BIAS_CURRENT_20nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_25nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_30nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_35nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_0nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_5nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_10nA) \
                                      || ((SEL) == PM_EXTLF_BIAS_CURRENT_15nA))

/**
  * 内部低频振荡器电容校准
  */
#define CHECK_PM_CAPACITANCE_CALIBRATION(CFG) \
                                        (((CFG) >> 5) == 0)

/**
  * 低功耗偏置电流校准
  */
#define CHECK_PM_LP_BIAS_CALIBRATION(CFG) \
                                        (((CFG) >> 3) == 0)

/**
  * LPBG PUMP校准
  */
#define CHECK_PM_PUMP_CALIBRATION(CFG) (((CFG) >> 3) == 0)

/**
  * 外部低频振荡器N管偏置校准
  */
#define PM_BRANCH_CURRENT_NONE          ((uint32_t)0<<PM_CAL1_LSE_TRIM_NBIAS0_POS)
#define PM_BRANCH_CURRENT_50_PERCENT    ((uint32_t)1<<PM_CAL1_LSE_TRIM_NBIAS0_POS)
#define PM_BRANCH_CURRENT_150_PERCENT   ((uint32_t)2<<PM_CAL1_LSE_TRIM_NBIAS0_POS)
#define PM_BRANCH_CURRENT_200_PERCENT   ((uint32_t)3<<PM_CAL1_LSE_TRIM_NBIAS0_POS)
#define CHECK_PM_BRANCH_CURRENT(SEL)    (((SEL) == PM_BRANCH_CURRENT_NONE) \
                                      || ((SEL) == PM_BRANCH_CURRENT_50_PERCENT) \
                                      || ((SEL) == PM_BRANCH_CURRENT_150_PERCENT) \
                                      || ((SEL) == PM_BRANCH_CURRENT_200_PERCENT))

/**
 * 	LPR类型选择
 * */
#define PM_LPR_MODE_CAPLESS				((uint32_t)0)
#define PM_LPR_MODE_CAP					((uint32_t)1)
#define CHECK_PM_BKPLPR_MODE(MODE)			((MODE) <= PM_LPR_MODE_CAP)

/**
 * 	外部复位引脚选择
 * */
#define PM_NRST0_PIN					((uint32_t)0)
#define PM_NRST1_PIN					((uint32_t)1)
#define CHECK_PM_NRST_PIN(PIN)			((PIN) <= PM_NRST1_PIN)


/**
 * 	LPCAN工作时钟选择
 * */
#define PM_LPCAN_SCK_INTLF				((uint32_t)0)
#define PM_LPCAN_SCK_LP4M				((uint32_t)1)
#define CHECK_PM_LPCAN_SCK(CLK)			((CLK) <= PM_LPCAN_SCK_LP4M)

/**
 * 	LPR12 capless 功耗控制
 * */
#define PM_LPR12_PC_MAX_90uA			((uint32_t)0)
#define PM_LPR12_PC_MIN_20uA			((uint32_t)1)
#define PM_LPR12_PC_MEDIUM_40uA			((uint32_t)2)
#define CHECK_PM_LPR12_PC(VALUE)		((VALUE) <= PM_LPR12_PC_MEDIUM_40uA)

/**
 *  参考 BUFFER 基准校准
 * */
#define CHECK_PM_BGTRIMREBUF_VALUE(VALUE) 	((VALUE) <= 0x3F)

/**
 * 	LPR12 capless 电流调整位
 * */
#define CHECK_PM_LPR12_CAPLESS_I(VALUE)		((VALUE) <= 0x1F)

#if _CLOSE_SERVICE_
/**
  * 功耗模式时序选择
  */
#define PM_POWER_DISSIPATION_SCHEME1    ((uint32_t)0<<PM_CTL0_PDMSEL_POS)
#define PM_POWER_DISSIPATION_SCHEME2    ((uint32_t)1<<PM_CTL0_PDMSEL_POS)
#define CHECK_PM_POWER_DISSIPATION(CFG) (((CFG) == PM_POWER_DISSIPATION_SCHEME1) \
                                      || ((CFG) == PM_POWER_DISSIPATION_SCHEME2))

/**
  * POR12关闭到LDO关闭的延时时间配置
  */
#define PM_POWER_DISSIPATION_500ns      ((uint32_t)1<<PM_CTL0_PDMDELAY0_POS)
#define PM_POWER_DISSIPATION_500ns_1T   ((uint32_t)2<<PM_CTL0_PDMDELAY0_POS)
#define PM_POWER_DISSIPATION_500ns_2P5T ((uint32_t)3<<PM_CTL0_PDMDELAY0_POS)
#define CHECK_PM_POWER_DISSIPATION_DELAY(TIME) \
                                        (((TIME) == PM_POWER_DISSIPATION_500ns) \
                                      || ((TIME) == PM_POWER_DISSIPATION_500ns_1T) \
                                      || ((TIME) == PM_POWER_DISSIPATION_500ns_2P5T))

/**
  * STOP模式唤醒时对系统时钟的控制
  */
#define PM_RELEASE_SYSCLK_WAIT_MR       ((uint32_t)0<<PM_CTL0_STOPSEL_POS)
#define PM_RELEASE_SYSCLK_IMMEDIATELY   ((uint32_t)1<<PM_CTL0_STOPSEL_POS)
#define CHECK_PM_RELEASE_SYSCLK(CFG)    (((CFG) == PM_RELEASE_SYSCLK_WAIT_MR) \
                                      || ((CFG) == PM_RELEASE_SYSCLK_IMMEDIATELY))

/**
  * 主电压调制器MR上电延时
  */
#define PM_RELEASE_SYSCLK_WAIT_MR       ((uint32_t)0<<PM_CTL0_STOPSEL_POS)
#define PM_RELEASE_SYSCLK_IMMEDIATELY   ((uint32_t)1<<PM_CTL0_STOPSEL_POS)
#define CHECK_PM_RELEASE_SYSCLK(CFG)    (((CFG) == PM_RELEASE_SYSCLK_WAIT_MR) \
                                      || ((CFG) == PM_RELEASE_SYSCLK_IMMEDIATELY))

/**
  * LDO18内置模块选择
  */
#define PM_LDO18_CAP                    ((uint32_t)0<<PM_CAL0_LDO18SEL_POS)
#define PM_LDO18_CAPLESS                ((uint32_t)1<<PM_CAL0_LDO18SEL_POS)
#define CHECK_PM_LDO18_MODULE(CFG)      (((CFG) == PM_LDO18_CAPLESS) \
                                      || ((CFG) == PM_LDO18_CAP))

/**
  * MR_BG模式选择
  */
#define PM_LOW_POWER_MODE               ((uint32_t)0<<PM_CAL0_MRBGSEL_POS)
#define PM_HIGH_POWER_MODE              ((uint32_t)1<<PM_CAL0_MRBGSEL_POS)
#define CHECK_PM_MR_BG_MODE(SEL)        (((SEL) == PM_LOW_POWER_MODE) \
                                      || ((SEL) == PM_HIGH_POWER_MODE))

/**
  * LPR内置模块选择
  */
#define PM_LPR_DEFAULT                  ((uint32_t)0<<PM_CAL0_LPRSEL_POS)
#define PM_LPR_BACKUP                   ((uint32_t)1<<PM_CAL0_LPRSEL_POS)
#define CHECK_PM_LPR_MODE(SEL)          (((SEL) == PM_LPR_DEFAULT) \
                                      || ((SEL) == PM_LPR_BACKUP))

#endif /* _CLOSE_SERVICE_ */


/* 电源管理(PM)控制功能函数定义*********************************************/
void PM_IO_Latch_Enable (FunctionalState NewState);
FlagStatus PM_Get_IO_Latch_Status (void);
void PM_Internal_Low_Frequency_Enable (FunctionalState NewState);
void PM_External_Low_Frequency_Enable (FunctionalState NewState);
void PM_External_Low_Frequency_Clock_Enable (FunctionalState NewState);
void PM_Main_Bandgap_Enable (FunctionalState NewState);
void PM_LDO18_Enable (FunctionalState NewState);
void PM_Backup_Registers_Reset_Config (uint32_t BkpReset);
void PM_Independent_Watchdog_Reset_Config (uint32_t IWDTReset);
void PM_DPRAM_In_Standby_Work_Mode_Config (uint32_t WorkMode);
void PM_LPRAM_In_Standby_Stop1_Work_Mode_Config (uint32_t WorkMode);
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
void PM_Internal_Test_Buffer_Clock_Enable (FunctionalState NewState);
void PM_Internal_Test_Buffer_Clock_Scaler_Config (uint32_t SclkScaler);
void PM_CCP0LPEN_ENABLE(FunctionalState NewState);
void PM_CCP0CLKLPEN_Enable (FunctionalState NewState);
void PM_PLL0_Output_Buffer_Enable (FunctionalState NewState);
void PM_PLL1_Output_Buffer_Enable (FunctionalState NewState);
void PM_PLL2_Output_Buffer_Enable (FunctionalState NewState);
void PM_PLL0LDO_Output_Buffer_Enable (FunctionalState NewState);
void PM_PLL1LDO_Output_Buffer_Enable (FunctionalState NewState);
void PM_PLL2LDO_Output_Buffer_Enable (FunctionalState NewState);
void PM_Battery_BOR_Config (uint32_t Voltage);
void PM_Battery_BOR_Enable (FunctionalState NewState);
void PM_Peripheral_Voltage_Monitoring_Enable (FunctionalState NewState);
void PM_Voltage_Detection_Config (uint32_t Voltage);
void PM_Voltage_Detection_Enable (FunctionalState NewState);
void PM_EXTLF_PIN_Selection_Config (uint32_t PeripheralPort);
void PM_EXTHF_PIN_Selection_Config (uint32_t PeripheralPort);
void PM_External_Wakeup_Pin_Enable (uint32_t PinSel, FunctionalState NewState);
void PM_External_Wakeup_Edge_Config (uint32_t PinSel, uint32_t TriggerEdge);
void PM_Stop_Mode_Peripheral_INLF_Enable (uint32_t Peripheral,FunctionalState NewState);
void PM_Peripheral_Reset_Config (uint32_t Peripheral, uint32_t ResetStatus);
void PM_BKP_LPR_Type_Select(uint32_t LPRMODE);
void PM_LP_DEBUG_Enable(FunctionalState NewState);
void PM_LVL_LDO18_Enable(FunctionalState NewState);
void PM_RAM_ECC_Enable(FunctionalState NewState);
void PM_LPCAN_Work_CLK_Select(uint32_t CLK);

#if _CLOSE_SERVICE_
void PM_Vdd_Por_Enable (FunctionalState NewState);
void PM_Low_Power_Bandgap_Enable (FunctionalState NewState);
void PM_Power_Dissipation_Mode_Config (uint32_t Mode);
void PM_Power_Dissipation_Mode_Delay_Config (uint32_t DelayTime);
void PM_Internal_Test_Buffer_Enable (FunctionalState NewState);
#endif /* _CLOSE_SERVICE_ */


/* 电源管理(PM)状态标志管理函数定义*****************************************/
RetStatus PM_Clear_Reset_And_Wakeup_Flag (uint32_t EventSel);
FlagStatus PM_Get_Reset_Flag (uint32_t EventSel);
RetStatus PM_Clear_External_Wakeup_Pin_Flag (uint32_t EventSel);
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
void PM_Reset_Pin_Config(uint32_t NRSTPIN, FunctionalState NewState);

/* 电源管理(PM)校准控制函数定义*********************************************/
void PM_Zero_Drift_Current_Config (uint32_t Calibration);
void PM_BOR_Voltage_Config (uint32_t Voltage);
void PM_Main_Regulator_Voltage_Config (uint32_t MRSel, uint32_t Voltage);
void PM_Main_Regulator_HV_Enable (FunctionalState NewState);
void PM_Reference_Calibration_Config (uint32_t Reference,
                    uint32_t Calibration);
void PM_INTLF_Bias_Current_Config (uint32_t Calibration);
void PM_EXTLF_Bias_Current_Config (uint32_t Calibration);
void PM_INTLF_Capacitance_Calibration_Config (uint32_t Calibration);
void PM_LP_Bias_Calibration_Config (uint32_t Calibration);
void PM_LPBG_Pump_Calibration_Config (uint32_t Calibration);
void PM_EXTLF_N_Bias_Current_Config (uint32_t Calibration);
void PM_IWDT_Enable(FunctionalState NewState);

#if _CLOSE_SERVICE_
void PM_LDO18_Module_Config (uint32_t LDO18Config);
void PM_Main_Regulator_Bandgap_Config (uint32_t ModeSel);
//void PM_LPR_Module_Config (uint32_t ModeSel);
void PM_VREF_SELECT (uint32_t Voltage);
void PM_VREF_Software_Enable (FunctionalState NewState);
#endif /* _CLOSE_SERVICE_ */


#endif /* KF32A156_PM_H_ */
