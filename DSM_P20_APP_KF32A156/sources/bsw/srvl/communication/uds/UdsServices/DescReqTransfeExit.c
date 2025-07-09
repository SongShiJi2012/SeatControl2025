/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescReqTransfeExit.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             请求退出数据传输
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
#include "DescReqTransfeExit.h"
#include "DescConfig.h"


#if SID37_TRANFEXIT_EN == DESC_ENABLE
/********************************************************************
* 函数名称：DescRequestTransferExit
* 功能描述：诊断请求传输退出
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
  


