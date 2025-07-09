/***********************************************************************************************
 * @file name:      Test.c
 * @description:    ���ļ����ڼ���ECU���������ؽӿڣ��������²��Թ��ܣ�
 *                    - AD����ֵ��ȡ��CAN����
 *                    - ����λ��/���״̬���������ⷢ
 *                    - TLE9210X���������Ϣ�ռ��뷢��
 *                    - EEPROM���ԣ�0xFE06��д�ȣ�
 *                    - IO�ڵ�ƽ��ת���ԣ���PIN59��
 *                    - ͨ��ʱ����ԣ�us����
 *                    - CAN�շ�����������ת��
 *                    - С����Ŀ��λ���ⷢ
 * @note:           ���в��Թ���ͨ��0x6E0֡���ͣ���������ȫ�ֱ�������ִ��ʱ�������ݡ���ʽ����ʱ����Ҫע��رղ����ڲ����Թ���
 * 					���ļ������ڲ�����;��**�Ͻ������������ǲ���ģ���е��ñ��ļ��κνӿں���**
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/

#include "Test.h"
#include "Srvl_CanSignals.h"
#include "CANDrv.h"
#include "Cdd_Hall.h"
#include "ecual_can.h"
#include "TP.h"
#include "Desc.h"
#include "DescRWDIDList.h"
#include "Rte_VfbInterface.h"
#include "ecual_wdog.h"
#include "Debug_VfbInterface.h"
#include "Ecual_Adc.h"
#include "__driver_Flash_API.h"

extern strCanMainMailboxRxbuffCfg CanMainMailboxRxbuffCfg[];
//�������繤��ʦ��DSM�����CAN����IDΪ��0x6E0,0x6E1
extern INT8U Buffer_6E0_C[8];
extern INT8U Buffer_6E1_C[8];
extern INT32U Dma0_Adc0_Buf[D_ADC0_CONTINUOUS_CHANNEL_NUM];
INT8U CanTestCommand = 0xff;
INT8U CanTestAccelerateFlag = 0;
INT8U CanTestParameter = 0;
#define  TEST_CANID 	0x505
typedef enum
{
    TEST_AD_DATA = 0,//ADֵ
    TEST_FAULT_DATA,//��������
    TEST_EM_STATE_DATA,//����˶�״̬
    TEST_SLEEP_DATA,//��������
    TEST_CAN_CHECK,//can���

    TEST_MAX2,
} ETEST2;

/***********************************************************************************************
 * @function name:  Vfb_Reserved_0
 * @description:
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
INT8U Vfb_Reserved_0()
{
	return 0;
}
/***********************************************************************************************
 * @function name:  Vfb_Reserved_1
 * @description:
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
INT8U Vfb_Reserved_1()
{
	return 1;
}
void Ecual_CanSetThirdHeatLvl(INT8U test)
{

}

/***********************************************************************************************
 * @function name: SetCanTestCommand
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void SetCanTestCommand(INT8U val)
{
	CanTestCommand = val;
}
/***********************************************************************************************
 * @function name: SetCanTestCommand
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void SetCanTestAccelerateFlag(INT8U val)
{
	CanTestAccelerateFlag = val;
}
/***********************************************************************************************
 * @function name: SetCanTestParameter
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void SetCanTestParameter(INT8U val)
{
	CanTestParameter = val;
}
/***********************************************************************************************
 * @function name: Fun_TEST_AD_LOOP
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void Fun_TEST_AD_LOOP(INT8U* Buffer)
{
	INT16U temp;

	if(CanTestParameter <= enADC_PaBackHallFB)
	{
		temp = (INT16U)Dma0_Adc0_Buf[CanTestParameter];
	}
	else
	{
		temp = Ecual_GetAD_MesVal(CanTestParameter);
	}

	Buffer[1] = CanTestParameter;
	Buffer[2] = temp >> 8;
	Buffer[3] = temp >> 0;
	CanTestParameter ++;
	if(CanTestParameter >= enADC_MAx)
	{
		CanTestParameter = 0;
	}

	if(CanTestParameter <= enADC_PaBackHallFB)
	{
		temp = (INT16U)Dma0_Adc0_Buf[CanTestParameter];
	}
	else
	{
		temp = Ecual_GetAD_MesVal(CanTestParameter);
	}
	Buffer[4] = CanTestParameter;
	Buffer[5] = temp >> 8;
	Buffer[6] = temp >> 0;
	CanTestParameter ++;
	if(CanTestParameter >= enADC_MAx)
	{
		CanTestParameter = 0;
	}
}
/***********************************************************************************************
 * @function name: Fun_TEST_AD_SINGLE
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void Fun_TEST_AD_SINGLE(INT8U* Buffer)
{
	INT16U temp;

	temp = Ecual_GetAD_MesVal(CanTestParameter);
	Buffer[1] = CanTestParameter;
	Buffer[2] = temp >> 8;
	Buffer[3] = temp >> 0;
}
/***********************************************************************************************
 * @function name: Fun_TEST_VAR_DATA
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void Fun_TEST_VAR_DATA(INT8U* Buffer)
{
	//���Ρ����Ӿ���������3������λ��+��ǰλ��
	INT16U value;

	Buffer[1] = CanTestParameter;

	switch(CanTestParameter)
	{
		case 0 : //��ֹ��
			value = Cdd_GetMotorHardStop(EN_DriverHeight);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_DriverLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_DriverBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 1 : //��ֹ��
			value = Cdd_GetMotorHardStop(EN_DriverFront);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_PassengerLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_PassengerBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 2 : //��ǰλ��
			value = Cdd_GetCurrentHallCnt(EN_DriverHeight);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetCurrentHallCnt(EN_DriverLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetCurrentHallCnt(EN_DriverBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 3 : //��ǰλ��
			value = Cdd_GetCurrentHallCnt(EN_DriverFront);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetCurrentHallCnt(EN_PassengerLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetCurrentHallCnt(EN_PassengerBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 4 : //ǰֹ�� = ��ֹ�� + ���쳤��
			value = Cdd_GetMotorHardStop(EN_DriverHeight) + Cdd_GetMotorSize(EN_DriverHeight);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_DriverLength) + Cdd_GetMotorSize(EN_DriverLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_DriverBack) + Cdd_GetMotorSize(EN_DriverBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 5 : //ǰֹ�� = ��ֹ�� + ���쳤��
			value = Cdd_GetMotorHardStop(EN_DriverFront) + Cdd_GetMotorSize(EN_DriverFront);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_PassengerLength) + Cdd_GetMotorSize(EN_PassengerLength);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Cdd_GetMotorHardStop(EN_PassengerBack) + Cdd_GetMotorSize(EN_PassengerBack);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 6 : //����λ��1
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Height);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 7 : //����λ��1
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Front);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 8 : //����λ��2
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Height);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 9 : //����λ��2
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Front);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 10 : //����λ��3
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Height);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 11 : //����λ��3
			value = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Front);
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Length);
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Back);
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;


		case 12 : //����С��λĿ��λ��
			value = Rte_GetVfb_DrResHeightReCallPosi();
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Rte_GetVfb_DrResLengthReCallPosi();
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Rte_GetVfb_DrResBackReCallPosi();
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 13 : //����С��λĿ��λ�� + ����С����Ŀ��λ��
			value = Rte_GetVfb_DrResFrontReCallPosi();
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Rte_GetVfb_Debug_Res_CallPosi_Height();
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			value = Rte_GetVfb_Debug_Res_CallPosi_Length();
			Buffer[6] = (INT8U)((value >> 8) & 0xFF);
			Buffer[7] = (INT8U)(value & 0xFF);
			break;

		case 14 : //����С����Ŀ��λ��
			value = Rte_GetVfb_Debug_Res_CallPosi_Back();
			Buffer[2] = (INT8U)((value >> 8) & 0xFF);
			Buffer[3] = (INT8U)(value & 0xFF);

			value = Rte_GetVfb_Debug_Res_CallPosi_Front();
			Buffer[4] = (INT8U)((value >> 8) & 0xFF);
			Buffer[5] = (INT8U)(value & 0xFF);

			Buffer[6] = 0xFF;
			Buffer[7] = 0xFF;
			break;

		default:
			break;
	}

	CanTestParameter ++;
	if(CanTestParameter > 14)
	{
		CanTestParameter = 0;
	}
}

/***********************************************************************************************
 * @function name: Fun_TEST_VAR_DATA
 * @description:
 * @author:         2023-4-20 czb
 ***********************************************************************************************/
void Fun_TEST_9210X_DATA(INT8U* Buffer)
{
	INT8U value;

    if(CanTestParameter >= EN_TLE9210X_NUM_MAX)
    {
        CanTestParameter = EN_TLE9210X_NUM_1;
    }

	Buffer[1] = CanTestParameter;

    value = Srvl_Tle9210x_GetFailSafeSts(CanTestParameter);
    value |= (Srvl_Tle9210x_GetChipInitErrSts(CanTestParameter) << 1);
    value |= (Srvl_Tle9210x_GetDataReadErr(CanTestParameter) << 3);
    value |= (Srvl_Tle9210x_GetVMStsErr(CanTestParameter) << 4);
    Buffer[2] = value;


    value = (Srvl_Tle9210x_GetTempSts(CanTestParameter));
    value |= (Srvl_Tle9210x_GetChargePumpUnderVStsErr(CanTestParameter) << 2);
    value |= (Srvl_Tle9210x_GetWdFlag(CanTestParameter) << 3);
    Buffer[3] = value;

    value = (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB1));
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB2) << 2);
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB3) << 4);
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB4) << 6);
    Buffer[4] = value;
    
    value = (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB5) << 0);
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB6) << 2);
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB7) << 4);
    value |= (Srvl_Tle9210x_GetDrainSourceErr(CanTestParameter,TLE9210x_HB8) << 6);
    Buffer[5] = value;

    
    value = (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB1));
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB2) << 2);
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB3) << 4);
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB4) << 6);
    Buffer[6] = value;
    
    value = (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB5) << 0);
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB6) << 2);
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB7) << 4);
    value |= (Srvl_Tle9210x_GetOffStateDiag(CanTestParameter,TLE9210x_HB8) << 6);
    Buffer[7] = value;

}

/***********************************************************************************************
 * @function name:  Test_ReadDID_FE06
 * @description:	�ⲿE2��д
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
void Test_ReadDID_FE06(void)
{
	INT8U Arguments = 0;
	INT32U StartAddr;

	Arguments = TpRxInfoStruct.cDataBuf[3];
	StartAddr = Arguments * 0x80;
	TpTxInfoStruct.wDataLength = 3;
#if 1

	if(StartAddr + 0x80 <= 0x800)
	{
		TpTxInfoStruct.wDataLength += 0x80;
		Srvl_E2Read(StartAddr, 0x80, (INT8U *)(&TpTxInfoStruct.cDataBuf[3]));
	}
	else if(Arguments == 0xFF)
	{
		//����
		INT8U EraseDate[0x100];
		memset(EraseDate , 0xff, 0x100);
		for(int i = 0; i < 8; i++)
		{
			while(Srvl_E2Write(i * 0x100, 0x100, EraseDate) != D_Success);
			ecual_FeedDog();
		}
	}
	else
	{

	}
#endif
	DescNrc = DescNrcOK;
}
/***********************************************************************************************
 * @function name:  Test_ReadDID_FF06
 * @description:	ģ��FLASH��ȡ
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
void Test_ReadDID_FF06(void)
{
	INT8U Arguments = 0;
	INT16U FlashPage;
	INT32U FlashAddress;

	Arguments = TpRxInfoStruct.cDataBuf[3];
	FlashPage = (TpRxInfoStruct.cDataBuf[4] << 8);
	FlashPage += TpRxInfoStruct.cDataBuf[5];

	FlashAddress = FlashPage * 1024 + Arguments * 0x80;
	TpTxInfoStruct.wDataLength = 3;
	TpTxInfoStruct.wDataLength += 0x80;
	/* read Data */
	memcpy((void *)&TpTxInfoStruct.cDataBuf[3], (uint32_t *)(FlashAddress), 0x80);

	DescNrc = DescNrcOK;
}
/***********************************************************************************************
 * @function name:  void Test_SetCan(INT8U *data, INT8U Parameter)
 * @description:    ת����λ������can���ݣ����ECU�����Ƿ���ȷ
 * @input parameters:     Parameter
 * @output parameters:     data
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
static void Test_SetCan(INT8U *data, INT8U Parameter)
{
	//ֱ��ʹ��0x6e1����
	if(Parameter < 30)
	{
//		memcpy(&data[8], CANMsg_RxMsgTbl[Parameter].pu8Buf, 8);
	}
	else if(Parameter >= 30)
	{
		Parameter -= 30;
		memcpy(&data[8], CanMainMailboxRxbuffCfg[Parameter].RxBuff.FrameData.U8Data, 8);
	}

	if(Parameter >= eRXINDEX_MAX)
	{
		memset(&data[8], 0xff, 8);
	}

}
#if D_TEST_TIMER_SW
UINT32 TimerStart;
UINT32 TimerEnd;
UINT64 Test_temp_us;
UINT32 Test_temp;
UINT8 Timer_States;
/***********************************************************************************************
 * @function name:  SetTimerStartValue
 * @description:    ��¼��ʼʱ��
 * @author:         ssj 2022-07-14
 ***********************************************************************************************/
void SetTimerStartValue()
{
	Timer_States = 0;//��ʼ��ʱ
	TimerStart = T21_CNT;
}
/***********************************************************************************************
 * @function name:  SetTimerEndValue
 * @description:    ��¼����ʱ��
 * @author:         ssj 2022-07-14
 ***********************************************************************************************/
void SetTimerEndValue()
{
	TimerEnd = T21_CNT;
	Timer_States = 1;//������ʱ �ɼ���
}
/***********************************************************************************************
 * @function name:  GetDiffTime0
 * @description:    ��������ʱ��ֻ�� ʹ��ͨ�ü�ʱ�� T21 16M(����Ƶ) t = CNT * 1/16M
 * ʹ�÷������ڲ��Եĳ�����ʼ�ֱ����SetTimerStartValue()��SetTimerEndValue() �����ô˺���
 * @author:         ssj 2022-07-14
 ***********************************************************************************************/
INT32U GetDiffTime0()
{
	if(TimerEnd > TimerStart)
	{
		Test_temp = TimerEnd - TimerStart;
	}
	else
	{
		Test_temp = 0xFFFFFFFF - TimerStart + TimerEnd + 1 ;
	}

	return Test_temp;
}
/***********************************************************************************************
 * @function name:  GetDiffTime_us
 * @description:    ��������ʱ��ֻ�� ʹ��ͨ�ü�ʱ�� T21 16M(����Ƶ)
 * ʹ�÷������ڲ��Եĳ�����ʼ�ֱ����SetTimerStartValue()��SetTimerEndValue() �����ô˺���
 * @author:         ssj 2022-07-14
 ***********************************************************************************************/
INT32U GetDiffTime_us()
{
	if(TimerEnd > TimerStart)
	{
		Test_temp_us = TimerEnd - TimerStart;
	}
	else
	{
		Test_temp_us = 0xFFFFFFFF - TimerStart + TimerEnd + 1 ;
	}
//	t = CNT * 1/16M * 1M  (us)
	Test_temp_us = Test_temp_us * 625;
	Test_temp_us = Test_temp_us / 10000;

	return (UINT32)Test_temp_us;
}

/***********************************************************************************************
 * @function name:  Test_Main
 * @description:    ����ʹ��
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-14
 ***********************************************************************************************/
void Test_SendTimeus(void)
{
	INT8U OutData[8] = {0};
	INT32U TempTimeus;

	if(Timer_States == 0)
	{
		return;
	}
	TempTimeus = GetDiffTime_us();
	OutData[0] = TempTimeus >> 24;
	OutData[1] = TempTimeus >> 16;
	OutData[2] = TempTimeus >> 8;
	OutData[3] = TempTimeus >> 0;

	memcpy(Buffer_6E1_C, &OutData[0], 8);
	CANDrvEMsgEventSet(eDSMG_DSM6E1);
}
/***********************************************************************************************
 * @function name:  Test_SendProgramPeriod
 * @description:    ����һ�γ������ڲ��������ͱ�������ʱ���ݣ����������¿�ʼ��һ�ֲ���
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void Test_SendProgramPeriod(void)
{
    SetTimerEndValue();
    Test_SendTimeus();
    SetTimerStartValue();
}

#endif
/***********************************************************************************************
 * @function name:  Test_Dispatch
 * @description:    ���Թ��ܵ��Ⱥ��������� CanTestCommand ���Ʒ��Ͳ�ͬ���Ͳ�������
 *                  ֧�� AD ѭ����������ͨ�� AD���������ݡ�9210X оƬ��Ϣ��
 *                  ÿ 30ms ���ڵ���һ�Σ�����ģʽ�¸��죩��ͨ�� 0x6E0 CAN �����ⷢ
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Test_Dispatch()
{
	INT8U OutData[8] = {0};
	static INT8U TestTimer = 0;//Ĭ��30ms�ⷢһ��

	if(CanTestAccelerateFlag == 1)
	{
		TestTimer = 6;
	}
	TestTimer ++;
	if(CanTestCommand >= TEST_MAX
	|| TestTimer <30)
	{
		return;
	}
	OutData[0] = CanTestCommand;
	switch(CanTestCommand)
	{
		case TEST_AD_LOOP : Fun_TEST_AD_LOOP(OutData);break;
		case TEST_AD_SINGLE : Fun_TEST_AD_SINGLE(OutData);break;
		case TEST_VAR_DATA : Fun_TEST_VAR_DATA(OutData);break;
        case TEST_9210X_DATA:Fun_TEST_9210X_DATA(OutData);break;
        default:break;
	}

//	(void)Ecual_CanSendMsg(0, TEST_CANID, 0x8u,OutData);
	memcpy(Buffer_6E0_C, &OutData[0], 8);
	CANDrvEMsgEventSet(eDSMG_DSM6E0);

	TestTimer = 0;
}
/***********************************************************************************************
 * @function name:  Test_E2Write
 * @description:    ����EEPROM����д��ӿڣ�д�������ڿ��ء��������õ���Ϣ
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
static void Test_E2Write(void)
{
//	static INT16U u16CallCount = 0;
//	static INT16U u16Height = 0;
//	INT8U u8AdjustConfig[15] = {0};
//    uint32_t data[4] = {0};
//    u16CallCount++;
//    u16Height++;
//    if (u16CallCount == 500)
//    {
//    	Ecual_Disable_AllAdcDma();
//    	INT_All_Enable(FALSE);
//		__FLASH_Erase__(0x5A5A6688, 0x7E440, 1024);
//		__FLASH_Program_NBytes__(0x5A5A6688, 0x7E440, 16, data);
//		__FLASH_Program_NBytes__(0x5A5A6688, 0x7E440, 16, data);
//		Ecual_Enable_AllAdcDma();
//		INT_All_Enable(TRUE);
//		u16CallCount = 0;
//		Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_Height, u16Height);// ������д��
//		Srvl_WriteMemIndexData(EN_MemIndex_BoardPowerOnTypeAndCnt, u8AdjustConfig, 15);
//    }
	Srvl_SetMemIndexDataU8(EN_MemIndex_TestMessageSendCfg, 0x00);// ���Ա���
}

/***********************************************************************************************
 * @function name:  Test_Hall
 * @description:    ���ݻ������ݲ��Է��ͣ�����ֽ�˳��
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Test_Hall(void)
{
    INT8U OutData[8] = {0};

    OutData[0] = (INT8U)((Dma0_Adc0_Buf[1] >> 8) & 0xFFU);
    OutData[1] = (INT8U)(Dma0_Adc0_Buf[1] & 0xFFU);
    OutData[2] = (INT8U)((HallDataHandle.HallPwmCnt[EN_DriverLength] >> 8) & 0xFFU);
    OutData[3] = (INT8U)(HallDataHandle.HallPwmCnt[EN_DriverLength] & 0xFFU);

//    OutData[6] = (INT8U)((HallDataHandle.HallPwmCnt[EN_DriverFront] >> 8) & 0xFFU);
//    OutData[7] = (INT8U)(HallDataHandle.HallPwmCnt[EN_DriverFront] & 0xFFU);

    memcpy(Buffer_6E0_C, &OutData[0], 8);
    CANDrvEMsgEventSet(eDSMG_DSM6E0);
//    CANDrvEventMsgTxProcess();
//    CANDrvMSCAN_vogFillTxEmptyBuffers(FALSE);
}
/***********************************************************************************************
 * @function name:  Test_TogglePin59
 * @description:    ÿ�ε��÷�ת PIN59 �ŵ������ƽ��ʹ�� Ecual_GpioWriteOutPutPin �ӿ�
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Test_TogglePin59(void)
{
    static BOOL pinState = 0U;

    if(pinState == 0U)
    {
    	Ecual_GpioWriteCh(EN_Reserve3Out, 1U);  // ����ߵ�ƽ
        pinState = 1U;
    }
    else
    {
    	Ecual_GpioWriteCh(EN_Reserve3Out, 0U);  // ����͵�ƽ
        pinState = 0U;
    }
}
/***********************************************************************************************
 * @function name:  Test_Main
 * @description:    ����ģ������ں��������ڼ��е��ø��ֲ��Ժ������� AD ��ȡ��E2 ���ԡ�IO ��ת�ȣ�
 *                  ����ʵ�ʵ������󣬿����ڲ��ֶ����û����ζ�Ӧ���Ժ�������
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Test_Main(void)
{
	Test_Dispatch();
//	Test_E2Write();
//	Test_SendTimeus();
//	Test_Hall();
//	Test_TogglePin59();
}
