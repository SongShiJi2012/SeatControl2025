/************************************************************************************************
File created time : 2025-05-15 15:14:09
Tool Name :         DSM_If_Generate.py + DSM_If_Generate.xlsx
Filename:           Debug_VfbInterface.c
Author:             Ai
Description:        Generate VFB interface
/************************************************************************************************/
/************************************************************************************************
                                   C O P Y R I G H T  
-------------------------------------------------------------------------------  
Copyright (c) 2013-2025 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved.  
/************************************************************************************************/

#include "Debug_VfbInterface.h"

/*********************************Variable Definition *******************************************/
#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Stop_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Stop_Flag_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Open_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Open_Flag_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Colse_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_Colse_Flag_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_MotroFault_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_MassageFault_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_DrRestCAllRet = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC1_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC1_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC2_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC2_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC3_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC3_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC4_Flag = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CC4_Reason = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_CallRet = 0;

#if 0
小憩功能使用
#endif
INT8U  Debug_Res_State_ResDeal = 0;

#if 0
主驾小憩调用位置-高度
#endif
INT16U Debug_Res_CallPosi_Height = 0;

#if 0
主驾小憩调用位置-纵向
#endif
INT16U Debug_Res_CallPosi_Length = 0;

#if 0
主驾小憩调用位置-靠背
#endif
INT16U Debug_Res_CallPosi_Back = 0;

#if 0
主驾小憩调用位置-腿托
#endif
INT16U Debug_Res_CallPosi_Front = 0;

#if 0
按摩模式
#endif
INT16U Debug_Mas_T1timer = 0;

#if 0
按摩模式
#endif
INT16U Debug_Mas_T2timer = 0;

#if 0
按摩模式
#endif
INT16U Debug_Mas_T3timer = 0;

#if 0
按摩模式
#endif
INT16U Debug_Mas_T4timer = 0;

#if 0
按摩模式
#endif
INT8U  Debug_Mas_ActCount = 0;

#if 0
按摩模式
#endif
INT8U  Debug_Mas_MassagePCStopReason = 0;

#if 0
诊断阈值设置
#endif
INT16U Debug_Mas_T1_Threshold = 0;

#if 0
诊断阈值设置
#endif
INT16U Debug_Mas_T2_Threshold = 0;

#if 0
诊断阈值设置
#endif
INT16U Debug_Mas_T3_Threshold = 0;

#if 0
诊断阈值设置
#endif
INT16U Debug_Mas_T4_Threshold = 0;


/*********************************Get/Set Function *********************************************/
void Rte_SetVfb_Debug_Res_Stop_Flag(INT8U  SetValue)
{
    Debug_Res_Stop_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Stop_Flag(void)
{
    return Debug_Res_Stop_Flag;
}

void Rte_SetVfb_Debug_Res_Stop_Flag_Reason(INT8U  SetValue)
{
    Debug_Res_Stop_Flag_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Stop_Flag_Reason(void)
{
    return Debug_Res_Stop_Flag_Reason;
}

void Rte_SetVfb_Debug_Res_Open_Flag(INT8U  SetValue)
{
    Debug_Res_Open_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Open_Flag(void)
{
    return Debug_Res_Open_Flag;
}

void Rte_SetVfb_Debug_Res_Open_Flag_Reason(INT8U  SetValue)
{
    Debug_Res_Open_Flag_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Open_Flag_Reason(void)
{
    return Debug_Res_Open_Flag_Reason;
}

void Rte_SetVfb_Debug_Res_Colse_Flag(INT8U  SetValue)
{
    Debug_Res_Colse_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Colse_Flag(void)
{
    return Debug_Res_Colse_Flag;
}

void Rte_SetVfb_Debug_Res_Colse_Flag_Reason(INT8U  SetValue)
{
    Debug_Res_Colse_Flag_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_Colse_Flag_Reason(void)
{
    return Debug_Res_Colse_Flag_Reason;
}

void Rte_SetVfb_Debug_Res_MotroFault_Flag(INT8U  SetValue)
{
    Debug_Res_MotroFault_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_MotroFault_Flag(void)
{
    return Debug_Res_MotroFault_Flag;
}

void Rte_SetVfb_Debug_Res_MassageFault_Flag(INT8U  SetValue)
{
    Debug_Res_MassageFault_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_MassageFault_Flag(void)
{
    return Debug_Res_MassageFault_Flag;
}

void Rte_SetVfb_Debug_Res_DrRestCAllRet(INT8U  SetValue)
{
    Debug_Res_DrRestCAllRet = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_DrRestCAllRet(void)
{
    return Debug_Res_DrRestCAllRet;
}

void Rte_SetVfb_Debug_Res_CC1_Flag(INT8U  SetValue)
{
    Debug_Res_CC1_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC1_Flag(void)
{
    return Debug_Res_CC1_Flag;
}

void Rte_SetVfb_Debug_Res_CC1_Reason(INT8U  SetValue)
{
    Debug_Res_CC1_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC1_Reason(void)
{
    return Debug_Res_CC1_Reason;
}

void Rte_SetVfb_Debug_Res_CC2_Flag(INT8U  SetValue)
{
    Debug_Res_CC2_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC2_Flag(void)
{
    return Debug_Res_CC2_Flag;
}

void Rte_SetVfb_Debug_Res_CC2_Reason(INT8U  SetValue)
{
    Debug_Res_CC2_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC2_Reason(void)
{
    return Debug_Res_CC2_Reason;
}

void Rte_SetVfb_Debug_Res_CC3_Flag(INT8U  SetValue)
{
    Debug_Res_CC3_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC3_Flag(void)
{
    return Debug_Res_CC3_Flag;
}

void Rte_SetVfb_Debug_Res_CC3_Reason(INT8U  SetValue)
{
    Debug_Res_CC3_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC3_Reason(void)
{
    return Debug_Res_CC3_Reason;
}

void Rte_SetVfb_Debug_Res_CC4_Flag(INT8U  SetValue)
{
    Debug_Res_CC4_Flag = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC4_Flag(void)
{
    return Debug_Res_CC4_Flag;
}

void Rte_SetVfb_Debug_Res_CC4_Reason(INT8U  SetValue)
{
    Debug_Res_CC4_Reason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CC4_Reason(void)
{
    return Debug_Res_CC4_Reason;
}

void Rte_SetVfb_Debug_Res_CallRet(INT8U  SetValue)
{
    Debug_Res_CallRet = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_CallRet(void)
{
    return Debug_Res_CallRet;
}

void Rte_SetVfb_Debug_Res_State_ResDeal(INT8U  SetValue)
{
    Debug_Res_State_ResDeal = SetValue;
}
INT8U  Rte_GetVfb_Debug_Res_State_ResDeal(void)
{
    return Debug_Res_State_ResDeal;
}

void Rte_SetVfb_Debug_Res_CallPosi_Height(INT16U SetValue)
{
    Debug_Res_CallPosi_Height = SetValue;
}
INT16U Rte_GetVfb_Debug_Res_CallPosi_Height(void)
{
    return Debug_Res_CallPosi_Height;
}

void Rte_SetVfb_Debug_Res_CallPosi_Length(INT16U SetValue)
{
    Debug_Res_CallPosi_Length = SetValue;
}
INT16U Rte_GetVfb_Debug_Res_CallPosi_Length(void)
{
    return Debug_Res_CallPosi_Length;
}

void Rte_SetVfb_Debug_Res_CallPosi_Back(INT16U SetValue)
{
    Debug_Res_CallPosi_Back = SetValue;
}
INT16U Rte_GetVfb_Debug_Res_CallPosi_Back(void)
{
    return Debug_Res_CallPosi_Back;
}

void Rte_SetVfb_Debug_Res_CallPosi_Front(INT16U SetValue)
{
    Debug_Res_CallPosi_Front = SetValue;
}
INT16U Rte_GetVfb_Debug_Res_CallPosi_Front(void)
{
    return Debug_Res_CallPosi_Front;
}

void Rte_SetVfb_Debug_Mas_T1timer(INT16U SetValue)
{
    Debug_Mas_T1timer = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T1timer(void)
{
    return Debug_Mas_T1timer;
}

void Rte_SetVfb_Debug_Mas_T2timer(INT16U SetValue)
{
    Debug_Mas_T2timer = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T2timer(void)
{
    return Debug_Mas_T2timer;
}

void Rte_SetVfb_Debug_Mas_T3timer(INT16U SetValue)
{
    Debug_Mas_T3timer = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T3timer(void)
{
    return Debug_Mas_T3timer;
}

void Rte_SetVfb_Debug_Mas_T4timer(INT16U SetValue)
{
    Debug_Mas_T4timer = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T4timer(void)
{
    return Debug_Mas_T4timer;
}

void Rte_SetVfb_Debug_Mas_ActCount(INT8U  SetValue)
{
    Debug_Mas_ActCount = SetValue;
}
INT8U  Rte_GetVfb_Debug_Mas_ActCount(void)
{
    return Debug_Mas_ActCount;
}

void Rte_SetVfb_Debug_Mas_MassagePCStopReason(INT8U  SetValue)
{
    Debug_Mas_MassagePCStopReason = SetValue;
}
INT8U  Rte_GetVfb_Debug_Mas_MassagePCStopReason(void)
{
    return Debug_Mas_MassagePCStopReason;
}

void Rte_SetVfb_Debug_Mas_T1_Threshold(INT16U SetValue)
{
    Debug_Mas_T1_Threshold = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T1_Threshold(void)
{
    return Debug_Mas_T1_Threshold;
}

void Rte_SetVfb_Debug_Mas_T2_Threshold(INT16U SetValue)
{
    Debug_Mas_T2_Threshold = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T2_Threshold(void)
{
    return Debug_Mas_T2_Threshold;
}

void Rte_SetVfb_Debug_Mas_T3_Threshold(INT16U SetValue)
{
    Debug_Mas_T3_Threshold = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T3_Threshold(void)
{
    return Debug_Mas_T3_Threshold;
}

void Rte_SetVfb_Debug_Mas_T4_Threshold(INT16U SetValue)
{
    Debug_Mas_T4_Threshold = SetValue;
}
INT16U Rte_GetVfb_Debug_Mas_T4_Threshold(void)
{
    return Debug_Mas_T4_Threshold;
}

/***************************end****************************/
