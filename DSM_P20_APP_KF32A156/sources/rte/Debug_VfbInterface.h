/************************************************************************************************
File created time : 2025-05-15 15:14:09
Tool Name :         DSM_If_Generate.py + DSM_If_Generate.xlsx
Filename:           Debug_VfbInterface.h
Author:             Ai
Description:        Generate VFB interface
/************************************************************************************************/
/************************************************************************************************
                                   C O P Y R I G H T  
-------------------------------------------------------------------------------  
Copyright (c) 2013-2025 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved.  
/************************************************************************************************/

#ifndef _DEBUG_VFBINTERFACE_H_
#define _DEBUG_VFBINTERFACE_H_

#include "Common.h"


/*********************************Function declaration*********************************************/
extern void Rte_SetVfb_Debug_Res_Stop_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Stop_Flag(void);

extern void Rte_SetVfb_Debug_Res_Stop_Flag_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Stop_Flag_Reason(void);

extern void Rte_SetVfb_Debug_Res_Open_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Open_Flag(void);

extern void Rte_SetVfb_Debug_Res_Open_Flag_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Open_Flag_Reason(void);

extern void Rte_SetVfb_Debug_Res_Colse_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Colse_Flag(void);

extern void Rte_SetVfb_Debug_Res_Colse_Flag_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_Colse_Flag_Reason(void);

extern void Rte_SetVfb_Debug_Res_MotroFault_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_MotroFault_Flag(void);

extern void Rte_SetVfb_Debug_Res_MassageFault_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_MassageFault_Flag(void);

extern void Rte_SetVfb_Debug_Res_DrRestCAllRet(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_DrRestCAllRet(void);

extern void Rte_SetVfb_Debug_Res_CC1_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC1_Flag(void);

extern void Rte_SetVfb_Debug_Res_CC1_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC1_Reason(void);

extern void Rte_SetVfb_Debug_Res_CC2_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC2_Flag(void);

extern void Rte_SetVfb_Debug_Res_CC2_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC2_Reason(void);

extern void Rte_SetVfb_Debug_Res_CC3_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC3_Flag(void);

extern void Rte_SetVfb_Debug_Res_CC3_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC3_Reason(void);

extern void Rte_SetVfb_Debug_Res_CC4_Flag(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC4_Flag(void);

extern void Rte_SetVfb_Debug_Res_CC4_Reason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CC4_Reason(void);

extern void Rte_SetVfb_Debug_Res_CallRet(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_CallRet(void);

extern void Rte_SetVfb_Debug_Res_State_ResDeal(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Res_State_ResDeal(void);

extern void Rte_SetVfb_Debug_Res_CallPosi_Height(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Res_CallPosi_Height(void);

extern void Rte_SetVfb_Debug_Res_CallPosi_Length(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Res_CallPosi_Length(void);

extern void Rte_SetVfb_Debug_Res_CallPosi_Back(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Res_CallPosi_Back(void);

extern void Rte_SetVfb_Debug_Res_CallPosi_Front(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Res_CallPosi_Front(void);

extern void Rte_SetVfb_Debug_Mas_T1timer(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T1timer(void);

extern void Rte_SetVfb_Debug_Mas_T2timer(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T2timer(void);

extern void Rte_SetVfb_Debug_Mas_T3timer(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T3timer(void);

extern void Rte_SetVfb_Debug_Mas_T4timer(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T4timer(void);

extern void Rte_SetVfb_Debug_Mas_ActCount(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Mas_ActCount(void);

extern void Rte_SetVfb_Debug_Mas_MassagePCStopReason(INT8U  SetValue);
extern INT8U  Rte_GetVfb_Debug_Mas_MassagePCStopReason(void);

extern void Rte_SetVfb_Debug_Mas_T1_Threshold(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T1_Threshold(void);

extern void Rte_SetVfb_Debug_Mas_T2_Threshold(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T2_Threshold(void);

extern void Rte_SetVfb_Debug_Mas_T3_Threshold(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T3_Threshold(void);

extern void Rte_SetVfb_Debug_Mas_T4_Threshold(INT16U SetValue);
extern INT16U Rte_GetVfb_Debug_Mas_T4_Threshold(void);

/***************************end****************************/


#endif   /* _RTE_VFBINTERFACE_H_ */
