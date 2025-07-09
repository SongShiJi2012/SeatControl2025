/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescReqDownload.c
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             ������������
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven Ī����
** Created date:            2013.10.23
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
#include "DescReqDownload.h"
#include "DescConfig.h"


#if SID34_REQDWNLOAD_EN == DESC_ENABLE
/********************************************************************
* �������ƣ�DescRequestDownload
* ���������������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/

void DescRequestDownload(void)
{
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
        TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
    if(DescSessionSA_CfgChk(eSID_REQUEST_DOWNLOAD_INDEX))
    {
        return;
    }
}

#endif

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  

