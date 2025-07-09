/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               NXP_SBC_UJA107x.h
** Last modified Date:      2019.3.14
** Last Version:            V1.0.0
** Description:             UJA107x Series header file
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2019.3.12
** Version:                 V1.0.0
** Descriptions:            UJA107x Series header file
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#ifndef __NXP_SBC_UJA107X_H__
#define __NXP_SBC_UJA107X_H__


/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "Common.h"


/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/
/// Configures header file for the existing UJA107x family member, e.g. UJA1078
/// Must be copied to the global project definitions
/// 配置现有UJA107X系列成员的头文件，例如UJA1078必须复制到全局项目定义
#define UJA1078
		
#define NoInterruptPending     		0x7000  //没有中断待处理
#define DeviceIdPattern         	0x4308  //设备ID模式
#define UJA1078_DeviceIdPattern 	0x4308
#define UJA1075_DeviceIdPattern 	0x4208
#define UJA1076_DeviceIdPattern 	0x4008
#define UJA1079_DeviceIdPattern 	0x4200
		 
		
	/// Watchdog and Status Register address  看门狗和状态寄存器的地址
#define WDSR_ADDRESS_MASK 0x0000
	/// Watchdog and Status Register read mask	 看门狗和状态寄存器的读掩码
#define WDSR_READ_MASK 0x1000
	/// Watchdog and Status Register write mask   看门狗和状态寄存器的写掩码
#define WDSR_WRITE_MASK 0xEFFF
	/// Watchdog Mode Control					  看门狗模式控制
#define WDSR_WMC_MASK 0x0800  
	/// Nominal Watchdog Period 				看门狗的周期
#define WDSR_NWP_MASK 0x0700
	/// Watchdog Off Status 						看门狗的关断状态
#define WDSR_WOS_MASK 0x0080
	///  Software Reset 							软件复位
#define WDSR_SWR_MASK 0x0080
	///  V1 Status									V1状态
#define WDSR_V1S_MASK 0x0040
		
#ifndef UJA1079
	/// V2 Status; not available for UJA1079		V2状态
#define WDSR_V2S_MASK 0x0020                     
#endif
		
	/// Wake-Up Status 1							WAKE1状态
#define WDSR_WLS1_MASK 0x0010
	/// Wake-Up Status 2							WAKE2状态
#define WDSR_WLS2_MASK 0x0008                         
		
		
		
		/// Mode Control Register address 模式控制寄存器
#define MCR_ADDRESS_MASK 0x2000
		/// Mode Control Register read mask 	模式控制寄存器读掩码
#define MCR_READ_MASK 0x3000
		/// Mode Control Register write mask	模式控制寄存器写掩码
#define MCR_WRITE_MASK 0xEFFF
		/// Mode Control						模式控制
#define MCR_MC_MASK 0x0c00
		/// Mode Control mask for Normal Mode with disabled V2 (MC = 2) 模式控制掩码对于正常模式下禁止V2
#define MCR_MC2_MASK 0x0800
		/// Mode Control mask for Normal Mode with enabled V2 (MC = 3)	 模式控制掩码对于正常模式下使能V2
#define MCR_MC3_MASK 0x0c00
		/// Mode Control mask for Sleep Mode (MC = 1) 模式控制掩码对于睡眠模式
#define MCR_MC1_MASK 0x0400
		/// Limp Home Warning Control  跛行回家警告控制
#define MCR_LHWC_MASK 0x0200
		/// Limp Home Control		   跛行回家控制
#define MCR_LHC_MASK 0x0100
		/// Enable Control			   EN 控制
#define MCR_ENC_MASK 0x0080
		
#ifndef UJA1076
		/// LIN Slope Control; not available for UJA1076  LIN斜率控制
#define MCR_LSC_MASK 0x0040    
#endif
		
		/// Wake Bias Control  唤醒偏压控制
#define MCR_WBC_MASK 0x0020
		/// Power Distribution Control	 电源描述控制
#define MCR_PDC_MASK 0x0010
		
		
		
		/// Interrupt Control Register address	 中断控制寄存器地址
#define ICR_ADDRESS_MASK 0x4000
		/// Interrupt Control Register read mask 中断控制寄存器读掩码
#define ICR_READ_MASK 0x5000
		/// Interrupt Control Register write mask 中断控制寄存器写掩码
#define ICR_WRITE_MASK 0xEFFF
		/// V1 Undervoltage Interrupt Enable	  V1欠压中断使能
#define ICR_V1UIE_MASK 0x0800
		/// V2 Undervoltage Interrupt Enable	  V2欠压中断使能
#define ICR_V2UIE_MASK 0x0400
		
#ifndef UJA1076
		/// LIN1 Standby Control; not available for UJA1076  LIN 待机模式控制
#define ICR_STBL1C_MASK 0x0200
#endif
		
#ifdef UJA1078
		/// LIN2 Standby Control; only available for UJA1078  LIN2待机模式控制
#define ICR_STBL2C_MASK 0x0100
#endif
		
		/// Wake-Up Interrupt 1 Control 唤醒中断1控制
#define ICR_WIC1_MASK 0x00c0 
		/// Wake-Up Interrupt 2 Control 唤醒中断2控制
#define ICR_WIC2_MASK 0x0030
		
#ifndef UJA1079 
		/// CAN Standby Control; not available for UJA1079 CAN待机模式控制
#define ICR_STBCC_MASK 0x0008
#endif
		/// Reset Threshold Control   复位域控制
#define ICR_RTHC_MASK 0x0004
		/// WAKE1 Sample Enable 	  WAKE1 采样使能
#define ICR_WSE1_MASK 0x0002
		/// WAKE2 Sample Enable 	  WAKE2 采样使能
#define ICR_WSE2_MASK 0x0001
		
		
		
		/// Interrupt Status Register address  中断状态寄存器地址
#define ISR_ADDRESS_MASK 0x6000
		/// Interrupt Status Register read mask   中断状态寄存器读掩码
#define ISR_READ_MASK 0x7000
		/// Interrupt Status Register write mask  中断状态寄存器写掩码
#define ISR_WRITE_MASK 0xEFFF
		/// V1 Undervoltage Interrupt	V1欠压中断
#define ISR_V1UI_MASK 0x0800  
		/// V2 Undervoltage Interrupt	V2欠压中断
#define ISR_V2UI_MASK 0x0400
		/// Interrupt Status Register write mask  中断状态寄存器写全清掩码
#define ISR_WRITE_CLEAN_MASK 0x0FFF
		
#ifndef UJA1076
		/// LIN Wake-Up Interrupt 1 	 LIN1唤醒中断
#define ISR_LWI1_MASK 0x0200    
#endif
		
#ifdef UJA1078
		/// LIN Wake-Up Interrupt 2; only available for UJA1078  LIN2唤醒中断
#define ISR_LWI2_MASK 0x0100
#endif
		
		/// Cyclic Interrupt 循环中断
#define ISR_CI_MASK 0x0080
		/// Wake-Up Interrupt 1   唤醒中断1
#define ISR_WI1_MASK 0x0040
		/// Power-On Status Interrupt	 上电状态中断
#define ISR_POSI_MASK 0x0020
		/// Wake-Up Interrupt 2 		 唤醒中断2
#define ISR_WI2_MASK 0x0010
		
#ifndef UJA1079 
		/// CAN Wake-Up Interrupt; not available for UJA1079  CAN唤醒中断
#define ISR_CWI_MASK 0x0008
#endif


/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/



/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/

/*
**********************************************************************************************************
					FUNCTIONS
**********************************************************************************************************
*/


#endif /* __NXP_SBC_UJA107X_H__ */



