/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescControlDTCSetting.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             DTC��������
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
#define   DTCCTLSET_GLOBALS

#include "uds_pub.h"


#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)

/********************************************************************
* �������ƣ�DescControlDTCSetting
* ������������Ͽ���TDC����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescControlDTCSetting(void)
{ 		
    /*ֻ֧��$03���ģʽ*/
	if(2 != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

    //�Ự����
    if (SESN_EXTDS != cDescSession)
    {
       	if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
    	{
			DescNrc = kDescNrcServiceNotSupportedInActiveSession;
    	}
		else
		{	
			DescNrc = DescNrcNoRsp;	
		}
        return;
    }

	if(DescCheckVehSpd() == FALSE)//���ٴ���3km/h
	{
		//�ٶȴ���3����ʹ��
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}

	if(((TpRxInfoStruct.cDataBuf[1] & 0x7F) == DESC_CONTROL_DTC_SETTING_ON) || \
	((TpRxInfoStruct.cDataBuf[1] & 0x7F) == DESC_CONTROL_DTC_SETTING_OFF))
	{
	    if(DescSessionSA_CfgChk(eSID_CONTROL_DTC_SETTING_INDEX))
	    {
	        return;
	    }
	    cDescControlDTCSetting = TpRxInfoStruct.cDataBuf[1] & 0x7F;
	    TpTxInfoStruct.wDataLength = 2;

	    if(TpRxInfoStruct.cDataBuf[1] & 0x80)
		{
			TpRxState.engine = kRxState_Idle;
			TpTxState.engine = kTxState_Idle;
			DescNrc = DescNrcNoRsp;
		}
		else
		{
			DescNrc = DescNrcOK;
		}
	}
	else
	{
	    if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
	    {
	        DescNrc = kDescNrcSubfunctionNotSupported;
	    }
	}
}
#endif

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


