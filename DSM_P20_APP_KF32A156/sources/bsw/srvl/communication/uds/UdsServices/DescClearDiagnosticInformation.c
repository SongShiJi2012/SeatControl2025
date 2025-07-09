/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescClearDiagnosticInformation.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             ��������Ϣ
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven Ī����
** Created date:            2013.10.24
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#include "uds_pub.h"
//#include "Srvl_SubComm.h"


// ���DTCʱ����1.2S
void DescClearAllDTCInformation(void)
{
#if 1   /*20230919  δʹ�øù���*/
    Diag_ClearAllDtc();
    Appdesc_u1gClrDTCNeedRspFlg = TRUE; //�˱�־�������Ǳ�־��ǰ����DTC�������
    Desc_OpTimeLongerThanP2Flag = TRUE; //��λ��ζ�Ÿ���ϲ�����Ӧʱ��ᳬ��P2_CAN_SERVER
    Appdesc_engCurrEEPOpDataID = EN_MemIndex_Dtc_Index0 + En_DtcType_MaxNum - 1;//��������Ƿ�д��ɹ�
	DescRepeatRes = D_HAL_GET_CUR_MS_TS();
#endif
}

/********************************************************************
* �������ƣ�DescClearDiagnosticInformation
* ������������������Ϣ
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ���DTCʱ����?S
********************************************************************/
void DescClearDiagnosticInformation(void)
{
	//static INT32U t_resetTime = 0;//���� ����������DTCʧ��
	INT32U  dwGroupOfDTC = 0;

	/*���Ѻ�E2prom����������ʱ3s�ſ�ʹ�ã��ȴ�E2prom���ݼ���*/
	/*if(CPU_TimerDiffTs(t_resetTime) < D_RWE2PROMTIME)
	{
		DescNrc = kDescNrcBusyRepeatRequest;
		return;
	}*/
	
	if(4U != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	
	if(DescSessionSA_CfgChk(eSID_CLR_DIAGNOSTIC_DTC_INDEX))
	{
		return;
	}
#if 1   /*20230919  δʹ�øù���*/
	/*��������ѹ���ܲ���E2prom DTC����E2promͬCAN��ѹһ��*/
	if((DescCheckVehSpd() == FALSE) || (DescGetSeatMoveStatusFlg() == TRUE)) //���ٴ���3km/h���������˶� NRC22
	{
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}
#endif        
	dwGroupOfDTC = TpRxInfoStruct.cDataBuf[1];
	dwGroupOfDTC <<= 8;
	dwGroupOfDTC |= TpRxInfoStruct.cDataBuf[2];
	dwGroupOfDTC <<= 8;
	dwGroupOfDTC |= TpRxInfoStruct.cDataBuf[3];
	
	if(dwGroupOfDTC == DESC_CLEAR_ALL_DTC_INFORMATION)
	{
		DescClearAllDTCInformation();
		DescNrc = (kDescNrcResponsePending);
		TpTxInfoStruct.wDataLength = 1;
	}
	else
	{
		/* Group not support */
		DescNrc = (kDescNrcRequestOutOfRange);
	}
}


/******************************************************************************
**                                  END OF FILE
*******************************************************************************/




