/*
 * common.c
 *
 *  Created on: 2025-5-5
 *      Author: Administrator
 */

#include "Common.h"

/********************************模型使用到的常量********************************/
const volatile INT16U CAL_LockErrNoTime_30ms = 3U;/* 堵转故障消除：30ms */
const volatile INT32U CAL_ManualSwError_2min = 120000U;/* 开关粘连时长：120s */
const volatile INT32U CAL_ManualSwValid_90s = 90000U;/* 开关有效时长：90s */
const volatile INT8U CAL_MotorHallInvalid_2s = 200U;/* 霍尔信号不变化时长：2s */
const volatile INT16U CAL_MotorMaxRunTime_60s = 6000U;/* 电机最大运行时间：60s */
const volatile INT16U CAL_MotorRelayErr_2s = 200U;/* 继电器粘连时间2s */
const volatile INT8U CAL_MotorStall_750ms = 75U;/* 霍尔无变化堵转检测时长：750ms */


/***********************************************************************************************
 * @function name: Com_RamSet
 * @description: 将指定缓冲区写入指定值
 * @input parameters: buff - 目标缓冲区指针 data - 要设置的数值 len - 长度
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
void Com_RamSet(INT8U *buff, INT8U data, INT16U len)
{
    INT16U Index;

    if(buff == NULL || len == 0)
    {
        return;
    }

    for(Index = 0x00; Index < len; Index++)
    {
        buff[Index] = data;
    }
}

/***********************************************************************************************
 * @function name: Com_MemCmp
 * @description: 比较两个内存区域数据是否相同
 * @input parameters: TrgBuff - 目标缓冲区指针 SrcBuff - 源缓冲区指针 Len - 比较长度
 * @output parameters: 无
 * @return: TRUE-一致 FALSE-不一致
 * @author: ssj 20250509
 ***********************************************************************************************/
BOOL Com_MemCmp(INT8U *TrgBuff, INT8U *SrcBuff, INT8U Len)
{
    INT8U Index;

    if((TrgBuff == NULL) || (SrcBuff == NULL) || (Len == 0))
    {
        return FALSE;
    }

    for(Index = 0x00; Index < Len; Index++)
    {
        if(TrgBuff[Index] != SrcBuff[Index])
        {
            return FALSE;
        }
    }

    return TRUE;
}

