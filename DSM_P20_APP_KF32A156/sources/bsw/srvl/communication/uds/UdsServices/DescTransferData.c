/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescTransferData.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             ��������
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



/********************************************************************
* �������ƣ�DescTransferData
* ������������ϴ�������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/

void DescTransferData(void)
{
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
        TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
    if(DescSessionSA_CfgChk(eSID_TRANSFER_DATA_INDEX))
    {
        return;
    }
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  

