/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescReqTransfeExit.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             �����˳����ݴ���
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
#include "DescReqTransfeExit.h"
#include "DescConfig.h"


#if SID37_TRANFEXIT_EN == DESC_ENABLE
/********************************************************************
* �������ƣ�DescRequestTransferExit
* ��������������������˳�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescRequestTransferExit(void)
{
    if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
        TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
    if(DescSessionSA_CfgChk(eSID_REQUEST_TRANSFER_EXIT_INDEX))
    {
        return;
    }
}

#endif

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  


