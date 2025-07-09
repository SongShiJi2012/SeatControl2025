/************************************************************************************************
File created time : 2024-05-09 11:45:03
Tool Name : LinSignalsAnalysisAndGenerateV1.5.py
************************************************************************************************/
#ifndef LDFFILE_RLS_TWOINONE_V10_H

#define LDFFILE_RLS_TWOINONE_V10_H

#include "Common.h"

/* DSM */

/* DSM_1_1-0x1A */
#define D_DSM_1_1_Len 	8U
typedef union Union_DSM_1_1
{
	INT8U buff[D_DSM_1_1_Len] ; 
	struct { 
		INT8U Reserved_1	: 8; 
		INT8U DSM_MassageLevel_Req	: 3; 
		INT8U DSM_MassageMode_Req	: 4; 
	} Bits; 

}unDSM_1_1DSM_1_1;


/* Massage */

/* Massage_1-0x1B */
#define D_Massage_1_Len 	8U
typedef union Union_MASSAGE_1
{
	INT8U buff[D_Massage_1_Len] ; 
	struct { 
		INT8U Reserved_1	: 8; 
		INT8U Massage_LevelSts_FB	: 3; 
		INT8U Massage_ModeSts_FB	: 4; 
		INT8U Massage_Error_FB_L	: 1; 
		INT8U Massage_Error_FB_H	: 1; 
		INT8U Motor_TimeOutError_FB	: 2; 
		INT8U Massage_1_LIN_Response_Error	: 1; 
	} Bits; 

}unMassage_1Massage_1;

/*********************************************************************************
 LinNode: DSM,
 FrameName: DSM_1_1,
 FrameId: 0x1A,
 SignalName: DSM_MassageLevel_Req
 Description: 
physical_value, 0, 7, 1, 0 ;
logical_value, 0, "OFF" ;
logical_value, 1, " Level 1" ;
logical_value, 2, " Level 2" ;
logical_value, 3, " Level 3" ;
logical_value, 4, " AUTO  OFF自动关闭" ;
logical_value, 5, "reserved" ;
logical_value, 6, "reserved" ;
logical_value, 7, "reserved" ;
*************************************************************************************/
void LinSignalSet_DSM_1_1_DSM_MassageLevel_Req(INT8U u8Data); 

/*********************************************************************************
 LinNode: DSM,
 FrameName: DSM_1_1,
 FrameId: 0x1A,
 SignalName: DSM_MassageMode_Req
 Description: 
physical_value, 0, 15, 1, 0 ;
logical_value, 0, " 全身放松" ;
logical_value, 1, " 全身激活" ;
logical_value, 2, "肩部激活" ;
logical_value, 3, " 肩部放松" ;
logical_value, 4, "腰部激活" ;
logical_value, 5, "腰部放松" ;
logical_value, 6, "背部激活" ;
logical_value, 7, "背部放松" ;
logical_value, 8, "Error模块故障" ;
logical_value, 9, "Reserved" ;
logical_value, 16, "Reserved" ;
logical_value, 17, "Reserved" ;
logical_value, 18, "Reserved" ;
logical_value, 19, "Reserved" ;
logical_value, 20, "Reserved" ;
*************************************************************************************/
void LinSignalSet_DSM_1_1_DSM_MassageMode_Req(INT8U u8Data); 

/*********************************************************************************
 LinNode: Massage,
 FrameName: Massage_1,
 FrameId: 0x1B,
 SignalName: Massage_LevelSts_FB
 Description: 
physical_value, 0, 7, 1, 0 ;
logical_value, 0, "OFF" ;
logical_value, 1, " Level 1" ;
logical_value, 2, " Level 2" ;
logical_value, 3, " Level 3" ;
logical_value, 4, " AUTO  OFF自动关闭" ;
logical_value, 5, "reserved" ;
logical_value, 6, "reserved" ;
logical_value, 7, "reserved" ;
*************************************************************************************/
INT8U LinSignalGet_Massage_1_Massage_LevelSts_FB(void); 

/*********************************************************************************
 LinNode: Massage,
 FrameName: Massage_1,
 FrameId: 0x1B,
 SignalName: Massage_ModeSts_FB
 Description: 
physical_value, 0, 15, 1, 0 ;
logical_value, 0, " 全身放松" ;
logical_value, 1, " 全身激活" ;
logical_value, 2, "肩部激活" ;
logical_value, 3, " 肩部放松" ;
logical_value, 4, "腰部激活" ;
logical_value, 5, "腰部放松" ;
logical_value, 6, "背部激活" ;
logical_value, 7, "背部放松" ;
logical_value, 8, "Error模块故障" ;
logical_value, 9, "Reserved" ;
logical_value, 16, "Reserved" ;
logical_value, 17, "Reserved" ;
logical_value, 18, "Reserved" ;
logical_value, 19, "Reserved" ;
logical_value, 20, "Reserved" ;
*************************************************************************************/
INT8U LinSignalGet_Massage_1_Massage_ModeSts_FB(void); 

/*********************************************************************************
 LinNode: Massage,
 FrameName: Massage_1,
 FrameId: 0x1B,
 SignalName: Massage_Error_FB
 Description: 
physical_value, 0, 3, 1, 0 ;
logical_value, 0, "无故障" ;
logical_value, 1, "过压" ;
logical_value, 2, " 欠压" ;
logical_value, 3, " Reserved" ;
*************************************************************************************/
INT8U LinSignalGet_Massage_1_Massage_Error_FB(void); 

/*********************************************************************************
 LinNode: Massage,
 FrameName: Massage_1,
 FrameId: 0x1B,
 SignalName: Motor_TimeOutError_FB
 Description: 
physical_value, 0, 3, 1, 0 ;
logical_value, 0, "无故障" ;
logical_value, 1, "过流" ;
*************************************************************************************/
INT8U LinSignalGet_Massage_1_Motor_TimeOutError_FB(void); 

/*********************************************************************************
 LinNode: Massage,
 FrameName: Massage_1,
 FrameId: 0x1B,
 SignalName: Massage_1_LIN_Response_Error
 Description: 
physical_value, 0, 1, 1, 0 ;
logical_value, 0, " No error" ;
logical_value, 1, " Error" ;
*************************************************************************************/
INT8U LinSignalGet_Massage_1_Massage_1_LIN_Response_Error(void); 



/************************************************************************************************
 The interface of FramsId Buffer
************************************************************************************************/

extern unDSM_1_1DSM_1_1 LinMsg_DSM_1_1;
extern unMassage_1Massage_1 LinMsg_Massage_1;
INT8U * LinMsgGetFrameBuffPtr_DSM_1_1(void); /* FrameName: DSM_1_1*/ 
INT8U * LinMsgGetFrameBuffPtr_Massage_1(void); /* FrameName: Massage_1*/ 


#endif 

