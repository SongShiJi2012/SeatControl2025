/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescReadDTCInfo.c
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             读DTC信息
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

#include "uds_pub.h"
#include "Appl_DtcSetConditionCheck.h"
#include "CpuPeripheralInit.h"



#if SID19_RDDTCINFO_EN == DESC_ENABLE

/* 函数声明 */
static void DescRdDTCReportNumberOfDTCByStatusMask(void);
static void DescRdDTCReportDTCByStatusMask(void);
static void DescRdDTCReportSupportedDTC(void);
static void DescRdDTCReportDTCSnapshotRecorByDTCNumber(void);
static void DescRdDTCReportDTCSnapshotIdentification(void);

/*##############################################################################
#  注册服务函数
################################################################################*/

const tRDDTC_INFO pReadDTCInfoTbl[] =
{
	/* Read DTC Req Type             ReqLen   Service */
	{eRDDTC_RepNumOfDTCByStatusMask,  3,  DescRdDTCReportNumberOfDTCByStatusMask},
	{eRDDTC_RepDTCMask,               3,  DescRdDTCReportDTCByStatusMask},
	{eRDDTC_RepSupportedDTC,          2,  DescRdDTCReportSupportedDTC},
//	{eRDDTC_RepDYCSnapshotId,         2,  DescRdDTCReportDTCSnapshotIdentification},
//	{eRDDTC_RepDTCSnapshot,           6,  DescRdDTCReportDTCSnapshotRecorByDTCNumber},
};



/**************************************************************************
* 函数名称：DescReadDTCInformation
* 功能描述：读DTC信息
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
***************************************************************************/
void DescReadDTCInformation(void)
{
#if 1  
	static INT32U t_resetTime = 0;
	INT8U cIndex;
	INT8U cSubServiceFound = FALSE;
	
	if( 2 > TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

	/*唤醒后E2prom操作服务延时3s才可使用，等待E2prom数据加载*/
	if(CPU_TimerDiffTs(t_resetTime) < D_RWE2PROMTIME)
	{
		DescNrc = kDescNrcBusyRepeatRequest;
		return;
	}
	
	//19服务不支持肯定响应位
	if(0x80U == (TpRxInfoStruct.cDataBuf[1] & 0x80U))
	{
		DescNrc = (kDescNrcSubfunctionNotSupported);
		return;
	}
	for(cIndex = 0; cIndex < UBOUND(pReadDTCInfoTbl); cIndex ++)
	{
		if(pReadDTCInfoTbl[cIndex].eSID == TpRxInfoStruct.cDataBuf[1])
		{
			cSubServiceFound = TRUE;
			if(pReadDTCInfoTbl[cIndex].ServerReqLen == TpRxInfoStruct.wDataLength)
			{
				if(DescSessionSA_CfgChk(eSID_READ_DTC_INFORMATION_INDEX))
				{
					return;
				}
				pReadDTCInfoTbl[cIndex].pServerProcess();
			}
			else
			{
				/* Invalid Service Request Length */
				DescNrc = (kDescNrcIncorrectMessageLengthOrInvalidFormat);
			}
			break;
		}
	}
	if(cSubServiceFound == FALSE)
	{
		/*JMC要求功能寻址时,若不支持此服务时无需回复负响应*/
	    if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
	    {
            /* Sub service not support */
            DescNrc = (kDescNrcSubfunctionNotSupported);
	    }
		else
		{
			 DescNrc = (DescNrcNoRsp);
		}
	}
#endif        
}


/*******************************************************************************
**
********************************************************************************/

/* Read DTC Information Sub Function */
void DescRdDTCReportNumberOfDTCByStatusMask(void)
{
	INT16U wDTCCounter = 0;

    wDTCCounter = Diag_MatchDtcMaskNum(TpRxInfoStruct.cDataBuf[2]);

	TpTxInfoStruct.cDataBuf[2] = DTCStatusAvailabilityMask;
	TpTxInfoStruct.cDataBuf[3] = DTCFormatIdentifierISO15031_64DTCFormat;
	TpTxInfoStruct.cDataBuf[4] = (INT8U )(wDTCCounter >> 8);
	TpTxInfoStruct.cDataBuf[5] = (INT8U)(wDTCCounter);
	TpTxInfoStruct.wDataLength = 6;
	DescNrc = DescNrcOK;
}

void DescRdDTCReportDTCByStatusMask(void)
{
 #if 1 /*20230619*/ 
	INT8U cIndex = 0U;
	INT16U wNum = 3U;
    INT8U u8DtcCode[D_DIAG_DTC_CODE_SIZE] = {0};

	TpTxInfoStruct.cDataBuf[2] = DTCStatusAvailabilityMask;
	for(cIndex = 0; cIndex < (INT8U)En_DtcType_MaxNum; cIndex ++)
	{
		if (Diag_MatchDtcMaskCode(TpRxInfoStruct.cDataBuf[2], cIndex, u8DtcCode, D_DIAG_DTC_CODE_SIZE) == TRUE)
		{
			/*Useless if (Impact: Medium) 20230629 by Prima Niu*/
			if((wNum + 4U) < TP_TX_DATA_BUF_SIZE)
			{
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[0];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[1];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[2];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = (INT8U)(Diag_GetDtcMask(cIndex) & DTCStatusAvailabilityMask);
				wNum++;
			}
		}
	}

	
	
	
	TpTxInfoStruct.wDataLength = wNum;
	DescNrc = DescNrcOK;
#endif       
}

void DescRdDTCReportSupportedDTC(void)
{
  #if 1 /*20230619*/
	INT8U cIndex = 0U;
	INT16U wNum = 3U;
	INT8U u8DtcCode[D_DIAG_DTC_CODE_SIZE] = {0};

	TpTxInfoStruct.cDataBuf[2] = DTCStatusAvailabilityMask;
	for(cIndex = 0; cIndex < (INT8U)En_DtcType_MaxNum; cIndex ++)
	{
		/*Useless if (Impact: Medium) 20230629 by Prima Niu*/
		if((wNum + 4U) < TP_TX_DATA_BUF_SIZE)
		{
			BOOL ret = Diag_GetDtcCode(cIndex, u8DtcCode);
			if(ret)
			{
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[0];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[1];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = u8DtcCode[2];
				wNum++;
				TpTxInfoStruct.cDataBuf[wNum] = (INT8U)(Diag_GetDtcMask(cIndex) & DTCStatusAvailabilityMask);
				wNum++;
			}
		}	
	}
	
	TpTxInfoStruct.wDataLength = wNum;
	DescNrc = DescNrcOK;
#endif      
}


void DescRdDTCReportDTCSnapshotRecorByDTCNumber(void)
{
  #if 0 /*20230619*/
	INT8U uRecordNumber = 0U;
	INT16U uLength = 0U;
	INT8U u8DtcCode[D_DIAG_DTC_CODE_SIZE] = {0};
	
	u8DtcCode[0] = TpRxInfoStruct.cDataBuf[2];
	u8DtcCode[1] = TpRxInfoStruct.cDataBuf[3];
	u8DtcCode[2] = TpRxInfoStruct.cDataBuf[4];
	uRecordNumber = TpRxInfoStruct.cDataBuf[5];

	if (Diag_ReadVehSnapData(u8DtcCode, uRecordNumber, &TpTxInfoStruct.cDataBuf[2], \
		sizeof(TpTxInfoStruct.cDataBuf) - 2, &uLength) == TRUE)
	{
		TpTxInfoStruct.cDataBuf[0] = 0x59;
		TpTxInfoStruct.cDataBuf[1] = 0x04;
		TpTxInfoStruct.wDataLength = uLength + 2;

		DescNrc = DescNrcOK;
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
#endif     
}


static void DescRdDTCReportDTCSnapshotIdentification(void)
{
 #if 0 /*20230619*/
	INT16U uLength = 0U;
	if (Diag_ReadVehSnapshotIdentification(&TpTxInfoStruct.cDataBuf[2], &uLength))
	{
		TpTxInfoStruct.cDataBuf[0] = 0x59;
		TpTxInfoStruct.cDataBuf[1] = 0x03;
		TpTxInfoStruct.wDataLength = uLength + 2;

		DescNrc = DescNrcOK;
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
#endif      
}

#endif

/***********************************************************************************************
 * @function name:  DescGetDrHeatDTCFailFlag(void)
 *
 * @description:	读主驾加热是否有DTC故障
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         flg TRUE：有DTC故障   		FALSE：无DTC故障
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-23
 ***********************************************************************************************/
BOOL DescGetDrHeatDTCFailFlag(void)
{
	BOOL flg = FALSE;
 #if 0 /*20230619*/       
	if( Diag_GetDTCFlg(En_Dtc_HeatingMat1SC) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_HeatingMat1OC) == TRUE \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC1SCN) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC1SCS) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC1OutOfRange) == TRUE)
	{
		flg = TRUE;
	}
#endif        
	return flg;
}

/***********************************************************************************************
 * @function name:  DescGetPaHeatDTCFailFlag(void)
 *
 * @description:	读副驾加热是否有DTC故障
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         flg TRUE：有DTC故障   		FALSE：无DTC故障
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-23
 ***********************************************************************************************/
BOOL DescGetPaHeatDTCFailFlag(void)
{
	BOOL flg = FALSE;
#if 0       
	if(Diag_GetDTCFlg(En_Dtc_HeatingMat2SC) == TRUE \
		|| Diag_GetDTCFlg(En_Dtc_HeatingMat2OC) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC2SC) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC2OC) == TRUE  \
		|| Diag_GetDTCFlg(En_Dtc_SensorNTC2OutOfRange) == TRUE)
	{
		flg = TRUE;
	}
#endif        
	return flg;
}

/***********************************************************************************************
 * @function name:  DescGetDrVenDTCFailFlag(void)
 *
 * @description:	读主驾通风是否有DTC故障
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         flg TRUE：有DTC故障   		FALSE：无DTC故障
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-23
 ***********************************************************************************************/
BOOL DescGetDrVenDTCFailFlag(void)
{
	BOOL flg = FALSE;
 #if 0 /*20230619*/       
	if(Diag_GetDTCFlg(En_Dtc_VentilationFanPowerSupplySC) == TRUE \
		|| Diag_GetDTCFlg(En_Dtc_VentilationFanPowerSupplyOutOfRange) == TRUE)
	{
		flg = TRUE;
	}
#endif        
	return flg;
}

/***********************************************************************************************
 * @function name:  DescGetPaVenDTCFailFlag(void)
 *
 * @description:	读副驾通风是否有DTC故障
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         flg TRUE：有DTC故障   		FALSE：无DTC故障
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-23
 ***********************************************************************************************/
BOOL DescGetPaVenDTCFailFlag(void)
{
	BOOL flg = FALSE;
#if 0 /*20230619*/        
	if(Diag_GetDTCFlg(En_Dtc_VentilationFan2PowerSupplySC) == TRUE \
		|| Diag_GetDTCFlg(En_Dtc_VentilationFan2PowerSupplyOutOfRange) == TRUE)
	{
		flg = TRUE;
	}
#endif        
	return flg;
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

