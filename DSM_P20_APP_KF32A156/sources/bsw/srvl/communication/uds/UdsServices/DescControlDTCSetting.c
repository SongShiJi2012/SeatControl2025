/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescControlDTCSetting.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             DTC控制设置
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
#define   DTCCTLSET_GLOBALS

#include "uds_pub.h"


#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)

/********************************************************************
* 函数名称：DescControlDTCSetting
* 功能描述：诊断控制TDC设置
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescControlDTCSetting(void)
{ 		
    /*只支持$03诊断模式*/
	if(2 != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

    //会话层检测
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

	if(DescCheckVehSpd() == FALSE)//车速大于3km/h
	{
		//速度大于3不给使用
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


