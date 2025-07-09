/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescTransferData.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             传输数据
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven 莫松文
** Created date:            2013.10.24
** Version:                 V1.0
** Descriptions:            The original version 初始版本
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
* 函数名称：DescTransferData
* 功能描述：诊断传输数据
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
  

