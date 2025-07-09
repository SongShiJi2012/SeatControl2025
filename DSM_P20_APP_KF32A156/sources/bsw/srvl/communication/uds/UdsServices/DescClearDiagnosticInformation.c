/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescClearDiagnosticInformation.c
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             清除诊断信息
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
//#include "Srvl_SubComm.h"


// 清除DTC时间大概1.2S
void DescClearAllDTCInformation(void)
{
#if 1   /*20230919  未使用该功能*/
    Diag_ClearAllDtc();
    Appdesc_u1gClrDTCNeedRspFlg = TRUE; //此标志的作用是标志当前进入DTC清除操作
    Desc_OpTimeLongerThanP2Flag = TRUE; //置位意味着该诊断操作响应时间会超过P2_CAN_SERVER
    Appdesc_engCurrEEPOpDataID = EN_MemIndex_Dtc_Index0 + En_DtcType_MaxNum - 1;//开启检测是否写入成功
	DescRepeatRes = D_HAL_GET_CUR_MS_TS();
#endif
}

/********************************************************************
* 函数名称：DescClearDiagnosticInformation
* 功能描述：清除诊断信息
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 清除DTC时间大概?S
********************************************************************/
void DescClearDiagnosticInformation(void)
{
	//static INT32U t_resetTime = 0;//屏蔽 否则升级清DTC失败
	INT32U  dwGroupOfDTC = 0;

	/*唤醒后E2prom操作服务延时3s才可使用，等待E2prom数据加载*/
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
#if 1   /*20230919  未使用该功能*/
	/*非正常电压不能操作E2prom DTC操作E2prom同CAN电压一致*/
	if((DescCheckVehSpd() == FALSE) || (DescGetSeatMoveStatusFlg() == TRUE)) //车速大于3km/h、座椅在运动 NRC22
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




