/*
 * Ecual_AdcMotor.c
 *
 *  Created on: 2025-3-26
 *      Author: Administrator
 */
#include "Ecual_AdcMotor.h"
#include "Srvl_PowerMode.h"
#include "ecual_pins.h"
#include "MidRelay.h"
#include "Rte_VfbInterface.h"
#include "Ecual_Adc.h"

static INT16U SeatAdjSw_UP_MIN = 0;
static INT16U SeatAdjSw_UP_MAX = 0;
static INT16U SeatAdjSw_DN_MIN = 0;
static INT16U SeatAdjSw_DN_MAX = 0;
static INT16U SeatAdjSw_CLOSE = 0;

static INT16U MotorCurrMax_Len = 750;        //�����ת��ֵ����
static INT16U MotorCurrMax_Front = 750;        //���ж�ת��ֵ����
static INT16U MotorCurrMax_HeiBack = 500; 	 //�߶ȡ��α���ת��ֵ��������
ST_ScanMotorState ScanMotorStateFlag = {0};
typedef INT8U (*MotorCmdGetter)(void);   // ����һ������ָ�����ͣ�����EN_MOTOR_MOVE

static void Ecual_SetDrHeightSwitchCmd(void);
static void Ecual_SetDrLengthSwitchCmd(void);
static void Ecual_SetDrBackSwitchCmd(void);
static void Ecual_SetDrFrontSwitchCmd(void);
static void Ecual_SetPaLengthSwitchCmd(void);
static void Ecual_SetPaBackSwitchCmd(void);


static void Ecual_CheckSeatCurrAdMinMax(void);

static void Ecual_SetMotorOverCurrentFlag(eADCCH ADC_ChannelID, INT16U OverCurrentThreshold, BOOL* pOverCurrentFlag);
static void Ecual_CheckMotorOverCurrents(void);
static void Ecual_UpdateAllRelayFlags(void);
static void Ecual_SetRelayFlag(MotorCmdGetter getMotorCmd, UN_RelayIOState *pRelayDriveSts);
/***********************************************************************************************
 * @function name: Ecual_SetDrHeightSwitchCmd
 * @description:  �������ݸ߶ȵ��ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrHeightSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRHeightForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRHeightBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrLengthSwitchCmd
 * @description:  ��������������ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrLengthSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRLengthForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRLengthBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrBackSwitchCmd
 * @description:  �������ݿ������ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrBackSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRBackForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRBackBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrFrontSwitchCmd
 * @description:  �����������е��ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrFrontSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRFrontForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRFrontBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetPaLengthSwitchCmd
 * @description:  ���ø���������ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetPaLengthSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_PALengthForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_PALengthBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetPaBackSwitchCmd
 * @description:  ���ø��ݿ������ڿ���״̬�������ж���ǰ������Ƿ�ͬʱ��Ч����ǰ��Ч��������ǰ�������ж���󣬾���Ч������Ĭ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetPaBackSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_PABackForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_PABackBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DEF;
	}
}

/***********************************************************************************************
 * @function name:  Ecual_CheckSeatCurrAdMinMax
 * @description:	��ת������ֵ�趨
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
static void Ecual_CheckSeatCurrAdMinMax(void)
{
	//���궨
}
/***********************************************************************************************
 * @function name:  Ecual_SetMotorOverCurrentFlag
 * @description:    ����������Ƿ񳬹���ת��ֵ��������״̬��־λ
 * @input parameters: eADCCH ADC_ChannelID - ADCͨ��ö��ID
 *                    INT16U OverCurrentThreshold - ��ת������ֵ
 *                    BOOL* pOverCurrentFlag - ����洢�ı�־λ��ַ
 * @output parameters: void
 * @return:         void
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_SetMotorOverCurrentFlag(eADCCH ADC_ChannelID, INT16U OverCurrentThreshold, BOOL* pOverCurrentFlag)
{
    if(TRUE == Ecual_GetMesFinishFlg(ADC_ChannelID))
    {
        if(Ecual_GetAD_MesVal(ADC_ChannelID) >= OverCurrentThreshold)
        {
            *pOverCurrentFlag = TRUE;
        }
        else
        {
            *pOverCurrentFlag = FALSE;
        }
    }
}

/***********************************************************************************************
 * @function name:  Ecual_CheckMotorOverCurrents
 * @description:    ͳһ���6������Ķ�ת����״̬�����¶�Ӧ��־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         void
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_CheckMotorOverCurrents(void)
{
    Ecual_SetMotorOverCurrentFlag(enADC_DrHeightMotorIS, MOTOR_CURR_MAX_DR_HEIGHT, &ScanMotorStateFlag.DrHeightOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrLengthMotorIS, MOTOR_CURR_MAX_DR_LENGTH, &ScanMotorStateFlag.DrLengthOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrBackMotorIS, MOTOR_CURR_MAX_DR_BACK, &ScanMotorStateFlag.DrBackOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrFrontMotorIS, MOTOR_CURR_MAX_DR_FRONT, &ScanMotorStateFlag.DrFrontOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_PaLengthMotorIS, MOTOR_CURR_MAX_PA_LENGTH, &ScanMotorStateFlag.PaLengthOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_PaBackMotorIS, MOTOR_CURR_MAX_PA_BACK, &ScanMotorStateFlag.PaBackOverCurrentFlag);
}

/***********************************************************************************************
 * @function name:  Ecual_SetRelayFlag
 * @description:    ͨ�ü̵���״̬���½ӿ� -
 * ���ݴ���ĵ������ӿںͼ̵���״ָ̬�����״̬λ
 * ����P20û�м̵��� ���޸�ģ�� ֻ�õ����������ģ�ͽӿ�
 * @input parameters:     MotorCmdGetter getMotorCmd - ��ȡ�������ĺ���ָ��
 *                      UN_RelayIOState *pRelayDriveSts - �̵���״̬����ָ��
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_SetRelayFlag(MotorCmdGetter getMotorCmd, UN_RelayIOState *pRelayDriveSts)
{
    if((getMotorCmd == NULL) || (pRelayDriveSts == NULL))
    {
        return;
    }

    EN_MOTOR_MOVE enMotorCmd = getMotorCmd();

    if(enMotorCmd == EN_MOTOR_UP_FW_LF)
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = TRUE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = FALSE;
    }
    else if(enMotorCmd == EN_MOTOR_DN_BW_RT)
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = FALSE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = TRUE;
    }
    else
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = FALSE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = FALSE;
    }
}
/***********************************************************************************************
 * @function name:  Ecual_UpdateAllRelayFlags
 * @description:    ͳһ���ø������ݺ͸������е���̵���״̬
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_UpdateAllRelayFlags(void)
{
    Ecual_SetRelayFlag(Rte_GetVfb_DrHeightMotorCmd,   &ScanMotorStateFlag.DrHeightRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrLengthMotorCmd,   &ScanMotorStateFlag.DrLengthRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrBackMotorCmd,     &ScanMotorStateFlag.DrBackRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrFrontMotorCmd,    &ScanMotorStateFlag.DrFrontRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_PaLengthMotorCmd,   &ScanMotorStateFlag.PaLengthRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_PaBackMotorCmd,     &ScanMotorStateFlag.PaBackRelayDriveSts);
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagHeightUp
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagHeightUp()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagHeightDN
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagHeightDN()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagLenghtForward
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagLenghtForward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrLengthRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagLenghtBackward
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagLenghtBackward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrLengthRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagBackForward
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagBackForward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrBackRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagBackBackward
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagBackBackward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrBackRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagFrontUp
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagFrontUp()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrFrontRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagFrontDown
 * @description:	��ȡ�̵�������״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagFrontDown()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrFrontRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagLenghtForward
 * @description:    ��ȡ�����������̵���ǰ������ǰ������״̬
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE��ʾ�̵�������ǰ��״̬��FALSE��ʾ��ǰ��״̬
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagLenghtForward(void)
{
    if(TRUE == ScanMotorStateFlag.PaLengthRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagLenghtBackward
 * @description:    ��ȡ�����������̵������ˣ��������״̬
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE��ʾ�̵������ں���״̬��FALSE��ʾ�Ǻ���״̬
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagLenghtBackward(void)
{
    if(TRUE == ScanMotorStateFlag.PaLengthRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagBackForward
 * @description:    ��ȡ���ݿ�������̵���ǰ������ǰ������״̬
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE��ʾ�̵�������ǰ��״̬��FALSE��ʾ��ǰ��״̬
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagBackForward(void)
{
    if(TRUE == ScanMotorStateFlag.PaBackRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagBackBackward
 * @description:    ��ȡ���ݿ�������̵������ˣ��������״̬
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE��ʾ�̵������ں���״̬��FALSE��ʾ�Ǻ���״̬
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagBackBackward(void)
{
    if(TRUE == ScanMotorStateFlag.PaBackRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL Ecual_GetPaRelayFlagHeightUp()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagHeightDN()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagFrontUp()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagFrontDown()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrHeightSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrHeightSwitchCmd()
{
	return ScanMotorStateFlag.DrHeightSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrLengthSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrLengthSwitchCmd()
{
	return ScanMotorStateFlag.DrLengthSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrBackSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrBackSwitchCmd()
{
	return ScanMotorStateFlag.DrBackSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrFrontSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrFrontSwitchCmd()
{
	return ScanMotorStateFlag.DrFrontSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaLengthSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetPaLengthSwitchCmd()
{
	return ScanMotorStateFlag.PaLengthSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaBackSwitchCmd
 * @description:	��ȡӲ�ߵ��ڿ���״̬
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetPaBackSwitchCmd()
{
	return ScanMotorStateFlag.PaBackSwitch;
}

EN_SW_TYPE Ecual_GetPaHeightSwitchCmd()
{
	return EN_SW_DEF;
}
EN_SW_TYPE Ecual_GetPaFrontSwitchCmd()
{
	return EN_SW_DEF;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrHeightOverCurrentFlag
 * @description:    ��ȡ���ݸ߶ȵ����ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrHeightOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrHeightOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrLengthOverCurrentFlag
 * @description:    ��ȡ������������ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrLengthOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrLengthOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrBackOverCurrentFlag
 * @description:    ��ȡ���ݿ��������ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrBackOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrBackOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrFrontOverCurrentFlag
 * @description:    ��ȡ�������е����ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrFrontOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrFrontOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetPrLengthOverCurrentFlag
 * @description:    ��ȡ������������ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPrLengthOverCurrentFlag(void)
{
    return ScanMotorStateFlag.PaLengthOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetPrBackOverCurrentFlag
 * @description:    ��ȡ���ݿ��������ת������־λ
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - ��ת��־λ״̬
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPrBackOverCurrentFlag(void)
{
    return ScanMotorStateFlag.PaBackOverCurrentFlag;
}

BOOL Ecual_GetPrFrontOverCurrentFlag()
{
	return EN_SW_DEF;
}
BOOL Ecual_GetPrHeightOverCurrentFlag()
{
	return EN_SW_DEF;
}
/***********************************************************************************************
 * @function name:  Ecual_AdcMotorTask
 * @description:	�������
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
void Ecual_AdcMotorPollingTask()
{
	Ecual_SetDrHeightSwitchCmd();
	Ecual_SetDrLengthSwitchCmd();
	Ecual_SetDrBackSwitchCmd();
	Ecual_SetDrFrontSwitchCmd();
	Ecual_SetPaLengthSwitchCmd();
	Ecual_SetPaBackSwitchCmd();

	Ecual_CheckSeatCurrAdMinMax();

	Ecual_UpdateAllRelayFlags();
	Ecual_CheckMotorOverCurrents();
}
