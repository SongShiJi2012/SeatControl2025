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
/// ��������UJA107Xϵ�г�Ա��ͷ�ļ�������UJA1078���븴�Ƶ�ȫ����Ŀ����
#define UJA1078
		
#define NoInterruptPending     		0x7000  //û���жϴ�����
#define DeviceIdPattern         	0x4308  //�豸IDģʽ
#define UJA1078_DeviceIdPattern 	0x4308
#define UJA1075_DeviceIdPattern 	0x4208
#define UJA1076_DeviceIdPattern 	0x4008
#define UJA1079_DeviceIdPattern 	0x4200
		 
		
	/// Watchdog and Status Register address  ���Ź���״̬�Ĵ����ĵ�ַ
#define WDSR_ADDRESS_MASK 0x0000
	/// Watchdog and Status Register read mask	 ���Ź���״̬�Ĵ����Ķ�����
#define WDSR_READ_MASK 0x1000
	/// Watchdog and Status Register write mask   ���Ź���״̬�Ĵ�����д����
#define WDSR_WRITE_MASK 0xEFFF
	/// Watchdog Mode Control					  ���Ź�ģʽ����
#define WDSR_WMC_MASK 0x0800  
	/// Nominal Watchdog Period 				���Ź�������
#define WDSR_NWP_MASK 0x0700
	/// Watchdog Off Status 						���Ź��Ĺض�״̬
#define WDSR_WOS_MASK 0x0080
	///  Software Reset 							�����λ
#define WDSR_SWR_MASK 0x0080
	///  V1 Status									V1״̬
#define WDSR_V1S_MASK 0x0040
		
#ifndef UJA1079
	/// V2 Status; not available for UJA1079		V2״̬
#define WDSR_V2S_MASK 0x0020                     
#endif
		
	/// Wake-Up Status 1							WAKE1״̬
#define WDSR_WLS1_MASK 0x0010
	/// Wake-Up Status 2							WAKE2״̬
#define WDSR_WLS2_MASK 0x0008                         
		
		
		
		/// Mode Control Register address ģʽ���ƼĴ���
#define MCR_ADDRESS_MASK 0x2000
		/// Mode Control Register read mask 	ģʽ���ƼĴ���������
#define MCR_READ_MASK 0x3000
		/// Mode Control Register write mask	ģʽ���ƼĴ���д����
#define MCR_WRITE_MASK 0xEFFF
		/// Mode Control						ģʽ����
#define MCR_MC_MASK 0x0c00
		/// Mode Control mask for Normal Mode with disabled V2 (MC = 2) ģʽ���������������ģʽ�½�ֹV2
#define MCR_MC2_MASK 0x0800
		/// Mode Control mask for Normal Mode with enabled V2 (MC = 3)	 ģʽ���������������ģʽ��ʹ��V2
#define MCR_MC3_MASK 0x0c00
		/// Mode Control mask for Sleep Mode (MC = 1) ģʽ�����������˯��ģʽ
#define MCR_MC1_MASK 0x0400
		/// Limp Home Warning Control  ���лؼҾ������
#define MCR_LHWC_MASK 0x0200
		/// Limp Home Control		   ���лؼҿ���
#define MCR_LHC_MASK 0x0100
		/// Enable Control			   EN ����
#define MCR_ENC_MASK 0x0080
		
#ifndef UJA1076
		/// LIN Slope Control; not available for UJA1076  LINб�ʿ���
#define MCR_LSC_MASK 0x0040    
#endif
		
		/// Wake Bias Control  ����ƫѹ����
#define MCR_WBC_MASK 0x0020
		/// Power Distribution Control	 ��Դ��������
#define MCR_PDC_MASK 0x0010
		
		
		
		/// Interrupt Control Register address	 �жϿ��ƼĴ�����ַ
#define ICR_ADDRESS_MASK 0x4000
		/// Interrupt Control Register read mask �жϿ��ƼĴ���������
#define ICR_READ_MASK 0x5000
		/// Interrupt Control Register write mask �жϿ��ƼĴ���д����
#define ICR_WRITE_MASK 0xEFFF
		/// V1 Undervoltage Interrupt Enable	  V1Ƿѹ�ж�ʹ��
#define ICR_V1UIE_MASK 0x0800
		/// V2 Undervoltage Interrupt Enable	  V2Ƿѹ�ж�ʹ��
#define ICR_V2UIE_MASK 0x0400
		
#ifndef UJA1076
		/// LIN1 Standby Control; not available for UJA1076  LIN ����ģʽ����
#define ICR_STBL1C_MASK 0x0200
#endif
		
#ifdef UJA1078
		/// LIN2 Standby Control; only available for UJA1078  LIN2����ģʽ����
#define ICR_STBL2C_MASK 0x0100
#endif
		
		/// Wake-Up Interrupt 1 Control �����ж�1����
#define ICR_WIC1_MASK 0x00c0 
		/// Wake-Up Interrupt 2 Control �����ж�2����
#define ICR_WIC2_MASK 0x0030
		
#ifndef UJA1079 
		/// CAN Standby Control; not available for UJA1079 CAN����ģʽ����
#define ICR_STBCC_MASK 0x0008
#endif
		/// Reset Threshold Control   ��λ�����
#define ICR_RTHC_MASK 0x0004
		/// WAKE1 Sample Enable 	  WAKE1 ����ʹ��
#define ICR_WSE1_MASK 0x0002
		/// WAKE2 Sample Enable 	  WAKE2 ����ʹ��
#define ICR_WSE2_MASK 0x0001
		
		
		
		/// Interrupt Status Register address  �ж�״̬�Ĵ�����ַ
#define ISR_ADDRESS_MASK 0x6000
		/// Interrupt Status Register read mask   �ж�״̬�Ĵ���������
#define ISR_READ_MASK 0x7000
		/// Interrupt Status Register write mask  �ж�״̬�Ĵ���д����
#define ISR_WRITE_MASK 0xEFFF
		/// V1 Undervoltage Interrupt	V1Ƿѹ�ж�
#define ISR_V1UI_MASK 0x0800  
		/// V2 Undervoltage Interrupt	V2Ƿѹ�ж�
#define ISR_V2UI_MASK 0x0400
		/// Interrupt Status Register write mask  �ж�״̬�Ĵ���дȫ������
#define ISR_WRITE_CLEAN_MASK 0x0FFF
		
#ifndef UJA1076
		/// LIN Wake-Up Interrupt 1 	 LIN1�����ж�
#define ISR_LWI1_MASK 0x0200    
#endif
		
#ifdef UJA1078
		/// LIN Wake-Up Interrupt 2; only available for UJA1078  LIN2�����ж�
#define ISR_LWI2_MASK 0x0100
#endif
		
		/// Cyclic Interrupt ѭ���ж�
#define ISR_CI_MASK 0x0080
		/// Wake-Up Interrupt 1   �����ж�1
#define ISR_WI1_MASK 0x0040
		/// Power-On Status Interrupt	 �ϵ�״̬�ж�
#define ISR_POSI_MASK 0x0020
		/// Wake-Up Interrupt 2 		 �����ж�2
#define ISR_WI2_MASK 0x0010
		
#ifndef UJA1079 
		/// CAN Wake-Up Interrupt; not available for UJA1079  CAN�����ж�
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



