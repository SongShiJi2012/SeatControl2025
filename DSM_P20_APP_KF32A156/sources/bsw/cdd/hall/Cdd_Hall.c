/*
 * Cdd_Hall.c
 *
 *  Created on: 2025-3-18
 *      Author: Administrator
 */
#include "Cdd_Hall.h"
#include "CpuPeripheralInit.h"
#include "Srvl_E2memory.h"
#include "Ecual_Adc.h"
#include "stdlib.h"
#include "Test.h"
#include "DescRoutineCtlList.h"
#include "Srvl_PowerMode.h"
#include "Rte_VfbInterface.h"
#include "MidRelay.h"
#include "adc_driver.h"

extern INT32U Dma0_Adc0_Buf[D_ADC0_CONTINUOUS_CHANNEL_NUM];//�������ݲ����Ƶ�ԭ�ӿ� ֱ�����жϴ���

typedef struct
{
	EN_MOTOR_MOVE LastCmd;
	INT32U DelayedCollectionTimer;
} HALL_CMD_STATE_T;
static INT16U s_HallDiffValue = 400;   		 /*Hall�źŲ�ֵ*/
INT8U HallState[EN_SeatSwitchMax] = {0};			 //��������״̬ 1-��������   2-�½�����
strHALLERR HallErr;
static BOOL s_HallAllStopFlag = TRUE;  // ���л���ͨ���Ƿ�ȫ��ֹͣ�ɼ���־��TRUE ��ʾ��ȫ��ֹͣ

/*����ͨ����¼����һ������*/
strADCHALLDATA HallDataHandle =
{
	{30000,30000,30000,30000,30000,30000}, //��ǰ��¼��PWM����λ�����
	{1044,1047,3672,448,1045,3354},  //������쳤��PWM��
	{30000,30000,30000,30000,30000,30000},  //�����Ӳֹ��λ�ã��¡��󡢿���
	{30000,30000,30000,30000,30000,30000},  //��һ�ε����Ӳֹ��λ�ã��¡��󡢿���
};
static void Cdd_HallAcquire(INT8U i, INT16U HallCurVal, EN_MOTOR_MOVE MotorCmd, BOOL StallErrFlag);
static void Cdd_HallStoreAll(void);
static void Cdd_HallCounterUpdata(INT8U i);
/*��ȡ���ε���״̬*/
static const MotorFun s_MotorCmdFunc[EN_SeatSwitchMax] =
{
	Rte_GetVfb_DrHeightMotorCmd,
	Rte_GetVfb_DrLengthMotorCmd,
	Rte_GetVfb_DrBackMotorCmd,
	Rte_GetVfb_DrFrontMotorCmd,
//	Rte_GetVfb_PaHeightMotorCmd,
	Rte_GetVfb_PaLengthMotorCmd,
	Rte_GetVfb_PaBackMotorCmd,
//	Rte_GetVfb_PaFrontMotorCmd,
};
static const MotorFun s_StallErrFunc[EN_SeatSwitchMax] =
{
	Rte_GetVfb_DrHeightStallErr,
	Rte_GetVfb_DrLengthStallErr,
	Rte_GetVfb_DrBackStallErr,
	Rte_GetVfb_DrFrontStallErr,
//	Rte_GetVfb_PaHeightStallErr,
	Rte_GetVfb_PaLengthStallErr,
	Rte_GetVfb_PaBackStallErr,
//	Rte_GetVfb_PaFrontStallErr,
};
/***********************************************************************
 * @function name: Cdd_HallCounterUpdata
 *
 * @description:��ת�궨ʱ�����������Լ�������ֵ����
 *
 * @input parameters: ͨ��
 *
 * @output parameters:
 *
 * @return:
 *
 * @note:
 *
 * @author: Prima Niu
 *
 * @date: 2023-05-15
 ***********************************************************************/
static void Cdd_HallCounterUpdata(INT8U i)
{
	INT8U j = 0;
	INT16U Adjust_offset = 0;
	INT16U MemPosi_Adjust = 0;
    INT8U MemChangeFlg = 0;
    INT8U CurHallCntEnIndex = 0;//��ǰ����
    INT8U MemHallCntEnIndex = 0;//�����������
    INT8U ResHallCntEnIndex = 0;//С��������
    INT8U SoftStopCntEnIndex = 0;//���ת����
    INT8U HardStopCntEnIndex = 0;//Ӳֹ������

    if(i <= EN_DriverFront)
    {
    	//����
        MemHallCntEnIndex = EN_MemIndex_DrMem1_Height + i;
        CurHallCntEnIndex = EN_MemIndex_DrCurHallCnt_Height + i;
        SoftStopCntEnIndex = EN_MemIndex_DrHeightSoftStopCnt + i;
        HardStopCntEnIndex = EN_MemIndex_DrHardStopPos_Height + i;
        ResHallCntEnIndex = EN_MemIndex_DrRes_ReCallPosi_Height + i;
    }
    else
    {
    	//����
        MemHallCntEnIndex = EN_MemIndex_PaMem1_Length + i - EN_PassengerLength;//�Ӹ�������ʼ ��ȥ����4��
        CurHallCntEnIndex = EN_MemIndex_PaCurHallCnt_Length + i - EN_PassengerLength;
        SoftStopCntEnIndex = EN_MemIndex_PaLengthSoftStopCnt + i - EN_PassengerLength;
        HardStopCntEnIndex = EN_MemIndex_PaHardStopPos_Length + i - EN_PassengerLength;
    }

	//��ֹ��С��-100%����-100%~0��������ǰ��ת��������С��-100%�������˺��ת�������ֹ����µ�-100%����ǰλ�ü����Լ�����λ��ȫ������ƫ����
	if(HallDataHandle.HardStopPos[i] < (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]))
	{
		Adjust_offset = (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]) - HallDataHandle.HardStopPos[i];
		HallDataHandle.HallPwmCnt[i] = HallDataHandle.HallPwmCnt[i] + Adjust_offset;
		HallDataHandle.HardStopPos[i] = (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]);
	}
	//��ֹ�����0%����0~100%�������˺��ת�����ߴ���100%��������ǰ��ת�������ֹ����µ�0%����ǰλ�ü����Լ�����λ��ȫ������ƫ����
	if(HallDataHandle.HardStopPos[i] > D_ADC_HALL_DEF)
	{
		Adjust_offset = HallDataHandle.HardStopPos[i] - D_ADC_HALL_DEF;
		HallDataHandle.HallPwmCnt[i] = HallDataHandle.HallPwmCnt[i] - Adjust_offset;
		HallDataHandle.HardStopPos[i] = D_ADC_HALL_DEF;
    }
	//��Ҫ������ǰ�ķ���
	Srvl_SetMemIndexDataU16(CurHallCntEnIndex, HallDataHandle.HallPwmCnt[i]);

    if(MemChangeFlg == FALSE && HallDataHandle.PreHardStopPos[i] != 0xFFFF && HallDataHandle.PreHardStopPos[i] != 0)
    {
        /* ǰӲֹ�� ���� ��Ӳֹ�� */
        if(HallDataHandle.PreHardStopPos[i] > HallDataHandle.HardStopPos[i])
        {
            Adjust_offset = HallDataHandle.PreHardStopPos[i] - HallDataHandle.HardStopPos[i];
            MemChangeFlg = 1;
        }
        else if(HallDataHandle.PreHardStopPos[i] < HallDataHandle.HardStopPos[i])
        {
            Adjust_offset = HallDataHandle.HardStopPos[i] - HallDataHandle.PreHardStopPos[i];
            MemChangeFlg = 2;
        }
        else
        {

        }

        if(MemChangeFlg > FALSE)
        {
            for(j = 0;j < 3;j ++)
            {
                //���¶�Ӧ����ļ���λ�ò���
            	MemHallCntEnIndex = MemHallCntEnIndex + j * 5;
                MemPosi_Adjust = Srvl_GetMemIndexDataU16(MemHallCntEnIndex);
                //����100%��ͬ�����ƣ��������ı�
                if((MemPosi_Adjust != 0x0000) && (MemPosi_Adjust != 0xFFFF))
                {
                    if(MemChangeFlg == 1)
                    {
                        if(MemPosi_Adjust >= HallDataHandle.HardStopPos[i] + Adjust_offset)
                        {
                            MemPosi_Adjust = MemPosi_Adjust - Adjust_offset;
                        }
                        else
                        {
                            MemPosi_Adjust = HallDataHandle.HardStopPos[i];
                        }
                        Srvl_SetMemIndexDataU16(MemHallCntEnIndex, MemPosi_Adjust);
                    }
                    else if(MemChangeFlg == 2)
                    {
                        if(MemPosi_Adjust <= HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i] + Adjust_offset)
                        {
                            MemPosi_Adjust = MemPosi_Adjust + Adjust_offset;
                        }
                        else
                        {
                            MemPosi_Adjust = HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i];
                        }
                        Srvl_SetMemIndexDataU16(MemHallCntEnIndex, MemPosi_Adjust);
                    }
                    else
                    {

                    }
                }
            }
             //����С�λ��
             if(i <= EN_DriverFront)
             {
                 MemPosi_Adjust = Srvl_GetMemIndexDataU16(ResHallCntEnIndex);
                 if((MemPosi_Adjust != 0x0000) && (MemPosi_Adjust != 0xFFFF))
                 {
                     if(MemChangeFlg == 1)
                     {
                         if(MemPosi_Adjust >= HallDataHandle.HardStopPos[i] + Adjust_offset)
                         {
                             MemPosi_Adjust = MemPosi_Adjust - Adjust_offset;
                         }
                         else
                         {
                             MemPosi_Adjust = HallDataHandle.HardStopPos[i];
                         }
                         Srvl_SetMemIndexDataU16(ResHallCntEnIndex, MemPosi_Adjust);
                     }
                     else if(MemChangeFlg == 2)
                     {
                         if(MemPosi_Adjust <= HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i] + Adjust_offset)
                         {
                             MemPosi_Adjust = MemPosi_Adjust + Adjust_offset;
                         }
                         else
                         {
                             MemPosi_Adjust = HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i];
                         }
                         Srvl_SetMemIndexDataU16(ResHallCntEnIndex, MemPosi_Adjust);
                     }
                     else
                     {

                     }
                 }
             }
         }
     }

    /* ���¿�ʼ��������ֹ�� */
    Srvl_SetMemIndexDataU8(SoftStopCntEnIndex, 0);
    Srvl_SetMemIndexDataU16(HardStopCntEnIndex, HallDataHandle.HardStopPos[i]);
    HallDataHandle.PreHardStopPos[i] = HallDataHandle.HardStopPos[i];
}
/***********************************************************************
 * @function name: Cdd_HallValUpdata
 *
 * @description: Ѱ����Сֵ����
 *
 * @input parameters: SeekFlag:����Сֵ��־λ
 * Count:��������ţ�ChlValue:���ʵʱ�ɼ�Hall�ź�AD����
 * @output parameters:
 *
 * @return:
 *
 * @note:
 *
 * @author: Prima Niu
 *
 * @date: 2023-03-21 13:30
 ***********************************************************************/
static INT16U Cdd_HallValUpdata(INT8U HallState, INT16U HallPreVal, INT16U HallCurVal)
{
	if((HallPreVal > HallCurVal) && (2 == HallState))
	{
		//����������С��
		HallPreVal = HallCurVal;
	}

	if((HallPreVal < HallCurVal) && (1 == HallState))
	{
		//�������������
		HallPreVal = HallCurVal;
	}

	return HallPreVal;
}


/***********************************************************************************************
 * @function name:  Cdd_GetSeatPosi
 * @description:       ��������λ��
 * @input parameters:  chl��Precent
 * @output parameters: Posi
 * @return:            Posi
 * @note:
 * @author:            czy
 * @note:              2022-09-8
 ***********************************************************************************************/
INT16U Cdd_GetSeatPosi(enSWITCH chl,INT16U Precent)
{
    INT16U Posi = 0;

    strADCHALLDATA HallData = Cdd_HallDataGet();  //��ȡ��ǰ����������PWMֵ

    Posi = HallData.HardStopPos[chl] + (INT16U)((INT32U)Precent * HallData.StopPosCnt[chl]/D_POSI);

    return Posi;

}
/********************************************************************
* �������ƣ�Cdd_HallDataGet
* ������������ȡ������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
strADCHALLDATA Cdd_HallDataGet(void)
{
	return HallDataHandle;
}
/***********************************************************************************************
 * @function name:  BOOL Cdd_IsHallAllStop(void)
 * @description:    �ж����л���ͨ���Ƿ���ֹͣ�ɼ�
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         TRUE��ȫ��ֹͣ��FALSE���вɼ���
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
BOOL Cdd_IsHallAllStop(void)
{
    return s_HallAllStopFlag;
}

/***********************************************************************************************
 * @function name:  Cdd_HallDmaHandler
 * @description:    ����DMA�����������ݣ����ڻ����������쳣����-��������1ms
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
void Cdd_HallDmaHandler(void)
{
	static HALL_CMD_STATE_T HallCmdState[EN_SeatSwitchMax];
	static BOOL g_HallStoreFlag = FALSE;
	INT8U i = 0;
	INT16U AD_Value = 0;
	EN_MOTOR_MOVE MotorCmd = EN_MOTOR_DEF;
	BOOL StallErrFlag = FALSE;

	s_HallAllStopFlag  = TRUE;

	//����ADCChlManage�Ļ���ͨ��Ҫ��EN_SeatSwitchMaxö��ͨ������һ��
	for(i = enADC_DrHeightHallFB; i <= enADC_PaBackHallFB; i++)
	{
		MotorCmd = s_MotorCmdFunc[i]();
		StallErrFlag = s_StallErrFunc[i]();
		// ����״̬��ֻҪ���˶�����͸���
		if(MotorCmd != EN_MOTOR_DEF)
		{
			HallCmdState[i].LastCmd = MotorCmd;
			HallCmdState[i].DelayedCollectionTimer = HALL_KEEP_TIME_MS;
		}

		// ��ǰ������� ���� ���ӳٲɼ�ʱ����
		if((MotorCmd != EN_MOTOR_DEF)
		|| (HallCmdState[i].DelayedCollectionTimer != 0))
		{
			s_HallAllStopFlag  = FALSE;

			AD_Value = Dma0_Adc0_Buf[i];/* ֱ�ӻ�ȡDMA���˺������ */
//			if(ERR_OK == Ecual_AD_MeasureChan(i, &AD_Value))/*ԭƽ̨�ӿ� ��ȡ����ת��ADֵ*/
			{
				Cdd_HallAcquire(i, AD_Value, HallCmdState[i].LastCmd, StallErrFlag);//��������
			}
		}
		//��ʱ�����������Լ� ���Կ�����1ms����ʱ�Լ�
		if(HallCmdState[i].DelayedCollectionTimer > 0)
		{
			HallCmdState[i].DelayedCollectionTimer --;
		}
	}

	// �ж��Ƿ�����ͨ��������ȫֹͣ��ִ��һ�δ洢
	if((s_HallAllStopFlag  == TRUE) && (g_HallStoreFlag == TRUE))
	{
		Cdd_HallStoreAll();
		g_HallStoreFlag = FALSE;
	}
	else if(s_HallAllStopFlag  != TRUE)
	{
		g_HallStoreFlag = TRUE;
	}
	else
	{

	}
}

/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description: ��ȡ��ǰλ�û�������
 * @input parameters: ���ε��ڷ���
 * @output parameters:
 * @return: ��ǰ�����������
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetCurrentHallCnt(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.HallPwmCnt[Posi];
	}

	return HallCnt;
}
/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description:��ȡ���쳤��
 * @input parameters: ���ε��ڷ���
 * @output parameters:
 * @return:
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetMotorSize(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.StopPosCnt[Posi];
	}

	return HallCnt;
}
/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description: ��ȡӲֹ��λ��
 * @input parameters: ���ε��ڷ���
 * @output parameters:
 * @return:
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetMotorHardStop(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.HardStopPos[Posi];
	}

	return HallCnt;
}
/***********************************************************************************************
 * @function name:  Cdd_GetMotorLearnFlag
 * @description:	��ȡ���ѧϰ״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Cdd_GetMotorLearnFlag(enSWITCH Posi)
{
	BOOL temp = 0;
	if(Posi < EN_SeatSwitchMax)
	{
		if(HallDataHandle.HardStopPos[Posi] != 0
		&& HallDataHandle.HardStopPos[Posi] != 0xFFFF)
		{
			temp = 1;
		}
	}

	return temp;
}
/***********************************************************************************************
 * @function name:  Cdd_HallStoreAll
 * @description:	������ǰ���ݴ洢������
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
static void Cdd_HallStoreAll(void)
{
	for(INT8U i = 0; i < EN_SeatSwitchMax; i++)
	{
		INT16U hallValue = HallDataHandle.HallPwmCnt[i];
		enSrvMemIndex memIndex;

		switch(i)
		{
			case EN_DriverHeight : memIndex = EN_MemIndex_DrCurHallCnt_Height; break;
			case EN_DriverLength : memIndex = EN_MemIndex_DrCurHallCnt_Length; break;
			case EN_DriverBack   : memIndex = EN_MemIndex_DrCurHallCnt_Back; break;
			case EN_DriverFront  : memIndex = EN_MemIndex_DrCurHallCnt_Front; break;

			default:
				continue;  // δ֪ͨ��������
		}

		Srvl_SetMemIndexDataU16(memIndex, hallValue);
	}
}
/***********************************************************************************************
 * @function name:  Rte_LoadHallDataToRam
 * @description:    ��EEPROM�ж�ȡ��ǰ����ֵ��Ӳֹ�����ݣ�д�뵽HallDataHandle�ṹ����
 * @input parameters:     ��
 * @output parameters:     ��
 * @return:         BOOL�������ɹ�����TRUE
 * @note:
 * @author:         ssj + 2025-04-24 11:10
 ***********************************************************************************************/
void Cdd_ReadAllHallFromE2(void)
{
    HallDataHandle.HallPwmCnt[EN_DriverHeight]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Height);
    HallDataHandle.HallPwmCnt[EN_DriverLength]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Length);
    HallDataHandle.HallPwmCnt[EN_DriverBack]    = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Back);
    HallDataHandle.HallPwmCnt[EN_DriverFront]   = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Front);

    HallDataHandle.HardStopPos[EN_DriverHeight] = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height);
    HallDataHandle.HardStopPos[EN_DriverLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Length);
    HallDataHandle.HardStopPos[EN_DriverBack]   = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back);
    HallDataHandle.HardStopPos[EN_DriverFront]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Front);

    HallDataHandle.HallPwmCnt[EN_PassengerLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Length);
    HallDataHandle.HallPwmCnt[EN_PassengerBack] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Back);

    HallDataHandle.HardStopPos[EN_PassengerLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Length);
    HallDataHandle.HardStopPos[EN_PassengerBack] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Back);

    memcpy(&HallDataHandle.PreHardStopPos[0], &HallDataHandle.HardStopPos[0], sizeof(HallDataHandle.PreHardStopPos));
}

/***********************************************************************************************
 * @function name: Cdd_ClearDriverHardStopData
 * @description: ������ݵ�Ӳֹ�����ݣ����� RAM �е� HardStopPos �� EEPROM �е������Ϣ
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
void Cdd_ClearDriverHardStopData(void)
{
    /* ��� RAM ������Ӳֹ������ */
    HallDataHandle.HardStopPos[EN_DriverHeight] = 0;
    HallDataHandle.HardStopPos[EN_DriverLength] = 0;
    HallDataHandle.HardStopPos[EN_DriverBack] = 0;
    HallDataHandle.HardStopPos[EN_DriverFront] = 0;

    HallDataHandle.PreHardStopPos[EN_DriverHeight] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverLength] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverBack] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverFront] = 0;

    /* ��� EEPROM ������Ӳֹ�������Ϣ */
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Length, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Front, 0xFFFF);
}
/***********************************************************************************************
 * @function name: Cdd_ClearPassengerHardStopData
 * @description: ������ݵ�Ӳֹ�����ݣ����� RAM �е� HardStopPos �� EEPROM �е������Ϣ
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
void Cdd_ClearPassengerHardStopData(void)
{
    /* ��� RAM �и���Ӳֹ������ */
    HallDataHandle.HardStopPos[EN_PaResever_1] = 0;
    HallDataHandle.HardStopPos[EN_PassengerLength] = 0;
    HallDataHandle.HardStopPos[EN_PassengerBack] = 0;
    HallDataHandle.HardStopPos[EN_PaResever_2] = 0;

    HallDataHandle.PreHardStopPos[EN_PaResever_1] = 0;
    HallDataHandle.PreHardStopPos[EN_PassengerLength] = 0;
    HallDataHandle.PreHardStopPos[EN_PassengerBack] = 0;
    HallDataHandle.PreHardStopPos[EN_PaResever_2] = 0;

    /* ��� EEPROM �и���Ӳֹ�������Ϣ */
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Height, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Length, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Back, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Front, 0xFFFF);
}
/***********************************************************************************************
 * @function name:  Cdd_HallAcquire
 * @description:    ��ָ��ͨ�������źŽ��в�������ʵ�ֱ��ؼ�⡢�����������ת�궨
 * @input parameters:     i������ͨ������ HallCurVal����ǰAD����ֵ MotorCmd����ǰ�˶����� StallErrFlag����ת��־
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
static void Cdd_HallAcquire(INT8U i, INT16U HallCurVal, EN_MOTOR_MOVE MotorCmd, BOOL StallErrFlag)
{
	static INT16U HallPreVal[EN_SeatSwitchMax] = {0};  //��һ�εĲɼ�ֵ

	if(EN_MOTOR_UP_FW_LF == MotorCmd)
	{
		//���ؿ��ص��ڷ�����ת���궨���죬д��궨��־���������ڷ�ʽ�����б궨
		if(TRUE == StallErrFlag)
		{
			HallDataHandle.HardStopPos[i] = HallDataHandle.HallPwmCnt[i] - HallDataHandle.StopPosCnt[i];
			Cdd_HallCounterUpdata(i);
		}
		//ǰһ��AD��ֵ�뵱ǰ�����Աȣ��ߵ͵�ƽ���400��8V����ʱ����ֵADԼ540��
		if(abs(HallPreVal[i] - HallCurVal) > s_HallDiffValue)
		{
			//���ؼ��
			if(HallState[i] == 1)//�������� ����⵽��ǰAD����һ��ADС����Ϊ���½��� ���򲻸��»�����
			{
				if(HallCurVal < HallPreVal[i])
				{
					HallState[i] = 2;//��
					HallDataHandle.HallPwmCnt[i]++;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//�������ֵ
				}
			}
			else if(HallState[i] == 2)//�������� ����⵽��ǰAD����һ��AD������Ϊ�������� ���򲻸��»�����
			{
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//��
					HallDataHandle.HallPwmCnt[i]++;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//������Сֵ
				}

			}
			else
			{
				//��һ���ϵ� ֱ�Ӹ���
				HallDataHandle.HallPwmCnt[i]++;
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//������
				}
				else
				{
					HallState[i] = 2;//�½���
				}
			}

			//��HALL����HALL����(����10�����ⶶ��)
			if(++HallErr.HallNorCnt[i] >= HALLNORTIME)
			{
				HallErr.HallNorCnt[i] = HALLNORTIME;
				HallErr.HallNorFlg[i] = TRUE;

				HallErr.HallErrCnt[i] = 0;
				HallErr.HallErrFlg[i] = FALSE;
			}
			//��������
			HallPreVal[i] = HallCurVal;
		}
		else
		{
			//�п��������HALL��ʱ����Ҫ����PWMƵ����أ�ʱ�������PWM���ڣ�
			if(++HallErr.HallErrCnt[i] >= D_HALLTIME)
			{
				HallErr.HallErrCnt[i] = D_HALLTIME;
				HallErr.HallErrFlg[i] = TRUE;
			}
			/* ������һ�ε���Сֵ/���ֵ */
			HallPreVal[i] = Cdd_HallValUpdata(HallState[i], HallPreVal[i], HallCurVal);
		}
	}
	else if(EN_MOTOR_DN_BW_RT == MotorCmd)
	{
		//���ؿ��ص��ڷ�����ת���궨���죬д��궨��־���������ڷ�ʽ�����б궨
//		if((EN_CURR_DN_ERR == ScanIOStateFlag.MOTOR_CURR[i]) && (EN_SW_DN_BW_RT == SEAT_ADJUST_SW[i]))
		if(TRUE == StallErrFlag)
		{
			HallDataHandle.HardStopPos[i] = HallDataHandle.HallPwmCnt[i];
			Cdd_HallCounterUpdata(i);
		}
		//ǰһ��AD��ֵ�뵱ǰ�����Աȣ��ߵ͵�ƽ���400��8V����ʱ����ֵADԼ540��
		if(abs(HallPreVal[i] - HallCurVal) > s_HallDiffValue)
		{
			//���ؼ��
			if(HallState[i] == 1)//�������� ����⵽��ǰAD����һ��ADС����Ϊ���½��� ���򲻸��»�����
			{
				if(HallCurVal < HallPreVal[i])
				{
					HallState[i] = 2;//��
					HallDataHandle.HallPwmCnt[i]--;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//�������ֵ
				}
			}
			else if(HallState[i] == 2)//�������� ����⵽��ǰAD����һ��AD������Ϊ�������� ���򲻸��»�����
			{
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//��
					HallDataHandle.HallPwmCnt[i]--;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//������Сֵ
				}

			}
			else
			{
				//��һ���ϵ� ֱ�Ӹ���
				HallDataHandle.HallPwmCnt[i]--;
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//������
				}
				else
				{
					HallState[i] = 2;//�½���
				}
			}
			//��HALL����HALL����(����10�����ⶶ��)
			if(++HallErr.HallNorCnt[i] >= HALLNORTIME)
			{
				HallErr.HallNorCnt[i] = HALLNORTIME;
				HallErr.HallNorFlg[i] = TRUE;

				HallErr.HallErrCnt[i] = 0;
				HallErr.HallErrFlg[i] = FALSE;
			}
			//��������
			HallPreVal[i] = HallCurVal;
		}
		else
		{
			//�п��������HALL��ʱ����Ҫ����PWMƵ����أ�ʱ�������PWM���ڣ�
			if(++HallErr.HallErrCnt[i] >= D_HALLTIME)
			{
				HallErr.HallErrCnt[i] = D_HALLTIME;
				HallErr.HallErrFlg[i] = TRUE;
			}
			/* ������һ�ε���Сֵ/���ֵ  */
			HallPreVal[i] = Cdd_HallValUpdata(HallState[i], HallPreVal[i], HallCurVal);
		}
	}
	else
	{
		//�޲���CMD����ʱ����������HALL��������HALL����������ʶ
		HallErr.HallNorCnt[i] = 0;
		HallErr.HallNorFlg[i] = FALSE;
		//��������
		HallPreVal[i] = HallCurVal;
	}
}
/***********************************************************************************************
 * @function name:  Ecual_HandleHallAndTriggerAdc
 * @description:    �������DMA���ݣ�����ADC0ת���������DMA0���±�־λ
 * 					����DMA����ʱ����ģ��E2����flash�ӿڳ�ͻ�������ڶ�ʱ�ж��е��ô�����
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
void Ecual_HandleHallAndTriggerAdc(void)
{
	static INT32U u32HallAdcTrigTimer = 0;
    if(CPU_TimerDiffTs(u32HallAdcTrigTimer) >= 1)
    {
    	u32HallAdcTrigTimer = D_HAL_GET_CUR_MS_TS();
		Cdd_HallDmaHandler();
		//��������� �������ʱ DMA����ǰ����ж�
		Ecual_SetDma0_Adc0_UpdateFlag(FALSE);
		ADC_DRV_SoftwareStartConv(ADCx_0);
    }
}

