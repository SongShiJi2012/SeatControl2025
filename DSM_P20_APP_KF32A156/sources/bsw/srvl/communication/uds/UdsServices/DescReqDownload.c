/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescReqDownload.c
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             请求下载升级
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven 莫松文
** Created date:            2013.10.23
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
#include "DescReqDownload.h"
#include "DescConfig.h"


#if SID34_REQDWNLOAD_EN == DESC_ENABLE
/********************************************************************
* 函数名称：DescRequestDownload
* 功能描述：诊断请求下载
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
  

