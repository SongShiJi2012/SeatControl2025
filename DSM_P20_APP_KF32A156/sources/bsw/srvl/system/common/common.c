/*
 * common.c
 *
 *  Created on: 2025-5-5
 *      Author: Administrator
 */

#include "Common.h"

/********************************ģ��ʹ�õ��ĳ���********************************/
const volatile INT16U CAL_LockErrNoTime_30ms = 3U;/* ��ת����������30ms */
const volatile INT32U CAL_ManualSwError_2min = 120000U;/* ����ճ��ʱ����120s */
const volatile INT32U CAL_ManualSwValid_90s = 90000U;/* ������Чʱ����90s */
const volatile INT8U CAL_MotorHallInvalid_2s = 200U;/* �����źŲ��仯ʱ����2s */
const volatile INT16U CAL_MotorMaxRunTime_60s = 6000U;/* ����������ʱ�䣺60s */
const volatile INT16U CAL_MotorRelayErr_2s = 200U;/* �̵���ճ��ʱ��2s */
const volatile INT8U CAL_MotorStall_750ms = 75U;/* �����ޱ仯��ת���ʱ����750ms */


/***********************************************************************************************
 * @function name: Com_RamSet
 * @description: ��ָ��������д��ָ��ֵ
 * @input parameters: buff - Ŀ�껺����ָ�� data - Ҫ���õ���ֵ len - ����
 * @output parameters: ��
 * @return: ��
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
 * @description: �Ƚ������ڴ����������Ƿ���ͬ
 * @input parameters: TrgBuff - Ŀ�껺����ָ�� SrcBuff - Դ������ָ�� Len - �Ƚϳ���
 * @output parameters: ��
 * @return: TRUE-һ�� FALSE-��һ��
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

