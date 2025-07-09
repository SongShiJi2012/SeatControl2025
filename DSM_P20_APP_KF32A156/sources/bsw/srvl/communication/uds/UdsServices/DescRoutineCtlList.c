/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescRoutineCtlList.c
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             RoutingCtrol列表
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven 莫松文
** Created date:            2013.10.19
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
#include "Appl_PaLearn_CtrlModel_types.h"
#include "Appl_DrMotorAdjust_CtrlModel.h"
#include "Rte_VfbInterface.h"
#include "Srvl_E2memory.h"
#include "MidRelay.h"
#include "OsekNmSleep.h"
//#include "Ecual_Gpio.h"
//#include "Ecual_PWM.h"
//#include "Srvl_Comm.h"
#define 	AppDesc_MKEYMAXNUM					2

#define		__ROUTINE_SUBF_NOT_SUPPORT			0,NULL

static INT8U sRoutine0203Sts = FALSE; //是否执行31 01 02 03例程并回复正响应

const INT8U cDescRoutineControlTypeID[] =
{
	0x01, 0x02, 0x03,
};

typedef struct
{
	RoutineResultType ClrPowerOnInfoRlt;
	RoutineResultType ForceIntoSleepModeRlt;
    RoutineResultType SysOnlineTestMode;
    RoutineResultType SysIntoEolMode;
    RoutineResultType NoFeedWatchDogIntoLimphome;
    RoutineResultType CheckProgram;
	RoutineResultType DRSeatHeat;
	RoutineResultType PASeatHeat;
	RoutineResultType DRSeatVentilation;
	RoutineResultType PASeatVentilation;
	RoutineResultType DRSeatLearning;
	RoutineResultType PASeatLearning;
	RoutineResultType DareTest;
	RoutineResultType DareSleep;
} stRoutine_Result;

static BOOL s_RoutineCtrlFlg[EN_ROUTINECTRLTYPEMAX] = {0};

static stRoutine_Result AppDesc_stsRoutineResult = {0};

/*! @brief 编程条件检查通过标志  */
static BOOL UdsApp_ProgChkCondInd = FALSE;
static  INT8U gRoutCtrlIDIndex = 0;

static BOOL s_learnDrMotorFlg = FALSE;	//诊断例程主驾学习电机标志位
static	enLeanStep s_learnDrMotorStep = enStepNULL; //诊断例程主驾学习电机步骤
static INT8U s_DrMotorLearnSts = 0; //主驾电机学习状态

static BOOL s_learnPaMotorFlg = FALSE;	//诊断例程副驾学习电机标志位
static	enLeanStep s_learnPaMotorStep = enStepNULL; //诊断例程副驾学习电机步骤
static INT8U s_PaMotorLearnSts = 0; //副驾电机学习状态
static INT8U s_RecoverDefaultFlag = 0x0u;/*恢复出厂标志位*/
static INT8U s_RecoverDefaultFlag2 = 0x0u;/*恢复出厂标志位2*/
static INT8U s_DareTestFlag = 0x0u;/*成测开启标志*/

#define     SK_THROW(A,B)       (((A)<<4) | (B))

static BOOL SysEolModeInd = FALSE;
static UdsRoutineEolResult_t UdsRoutineEolResult = EN_UDS_ROUTINE_EOL_SUCCESS;

static BOOL SysOnlineTestModeInd = FALSE;

static BOOL bForceIntoSleepModeInd = FALSE;

static BOOL bNoFeedWatchDogIntoLimphomeFlag = FALSE;

static void UdsApp_RountineCtrl_SysIntoEolModeStart(void);
static void UdsApp_RountineCtrl_SysIntoEolModeStop(void);
static void UdsApp_RountineCtrl_SysIntoEolModeResult(void);

static void DescRoutineCtrl_SysOnlineTestStartRoutine(void);
static void DescRoutineCtrl_SysOnlineTestStopRoutine(void);
static void DescRoutineCtrl_SysOnlineTestRequestRoutineResults(void);
static void UdsApp_ClrSysOnlineTestModeInd(void);

static void DescRoutineCtrl_ClrPowerOnInfoStartRoutine(void);
static void DescRoutineCtrl_ClrPowerOnInfoStopRoutine(void);
static void DescRoutineCtrl_ClrPowerOnInfoReqRoutineRlt(void);

static void DescRoutineCtrl_ComRequestRoutineResults(RoutineResultType RoutRstTmp);

static void DescRoutineCtrl_ForceIntoSleepModeStartRoutine(void);

static void DescRoutineCtrl_NoFeedWatchDogIntoLimphomeStaStartRoutine(void);
static void DescRoutineCtrl_NoFeedWatchDogIntoLimphomeStaReqRlt(void);
static void UdsApp_ClrNoFeedWatchDogIntoLimphomeStaInd(void);

void DescRoutineCtrl_6011_DR_Seat_Position_Learning_StartRoutile(void);
void DescRoutineCtrl_6011_DR_Seat_Position_Learning_StopRoutile(void);
static void DescRoutineCtrl_6011_DR_Seat_Position_Learning_ReqRoutineRlt(void);

void DescRoutineCtrl_6012_PA_Seat_Position_Learning_StartRoutile(void);
void DescRoutineCtrl_6012_PA_Seat_Position_Learning_StopRoutile(void);
static void DescRoutineCtrl_6012_PA_Seat_Position_Learning_ReqRoutineRlt(void);

static void DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile(void);

static void DescRoutineCtrl_6010_RestoreDefaultSettings_StartRoutile(void);

static void DescRoutineCtrl_FE0F_DareTest_StartRoutile(void);
static void DescRoutineCtrl_FE0F_DareTest_StopRoutile(void);
static void DescRoutineCtrl_FE0F_DareTest_ReqRoutineRlt(void);

static void DescRoutineCtrl_FE10_DareSleep_StartRoutile(void);

const tDESC_ROUTINT_INFO pRoutineCtlTbl[]={
	/* SID  ReqDatLen  SessionAllow ServiceProcess */
							   
{0x6011, SESN_EXTDS|SESN_SSS, Desc_enmSecExtLvl, {{4,DescRoutineCtrl_6011_DR_Seat_Position_Learning_StartRoutile},
							   {4,DescRoutineCtrl_6011_DR_Seat_Position_Learning_StopRoutile},
							   {4,DescRoutineCtrl_6011_DR_Seat_Position_Learning_ReqRoutineRlt}}},	

{0x6012, SESN_EXTDS|SESN_SSS, Desc_enmSecExtLvl, {{4,DescRoutineCtrl_6012_PA_Seat_Position_Learning_StartRoutile},
							   {4,DescRoutineCtrl_6012_PA_Seat_Position_Learning_StopRoutile},
							   {4,DescRoutineCtrl_6012_PA_Seat_Position_Learning_ReqRoutineRlt}}},								   


{0x6010, SESN_EXTDS|SESN_SSS, Desc_enmSecExtLvl, {{4,DescRoutineCtrl_6010_RestoreDefaultSettings_StartRoutile},
							{__ROUTINE_SUBF_NOT_SUPPORT},
							{__ROUTINE_SUBF_NOT_SUPPORT}}},
{0xFE0F, SESN_EXTDS|SESN_SSS, Desc_enmSecExtLvl, {{4,DescRoutineCtrl_FE0F_DareTest_StartRoutile},
								   {4,DescRoutineCtrl_FE0F_DareTest_StopRoutile},
								   {4,DescRoutineCtrl_FE0F_DareTest_ReqRoutineRlt}}},		
{0xFE10, SESN_EXTDS|SESN_SSS, Desc_enmSecExtLvl, {{4,DescRoutineCtrl_FE10_DareSleep_StartRoutile},
                                   {__ROUTINE_SUBF_NOT_SUPPORT},
                                   {__ROUTINE_SUBF_NOT_SUPPORT}}},

};

volatile INT8U cDescRoutineControlSequence[UBOUND(pRoutineCtlTbl)];

void setRoutine0203Sts(INT8U Sts)
{
	sRoutine0203Sts = Sts;
}

INT8U getRoutine0203Sts(void)
{
	return sRoutine0203Sts;
}

/***********************************************************************************************
 * @function name:  DescRoutine_getRoutineCtrFlg
 *
 * @description:   获取例程控制标志位
 *
 * @input parameters:   index 标志位下标
 *
 * @output parameters:   无
 *
 * @return:    例程是否开启标志
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-03-16
 ***********************************************************************************************/
BOOL DescRoutine_getRoutineCtrFlg(enRoutineCtrlType index)
{
	return s_RoutineCtrlFlg[index];
}

/***********************************************************************************************
 * @function name:  DescRoutine_setRoutineCtrFlg
 *
 * @description:   设置例程控制标志位
 *
 * @input parameters:   index 标志位下标, flg 例程开启标志
 *
 * @output parameters:   无
 *
 * @return:    void
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-03-18
 ***********************************************************************************************/
void DescRoutine_setRoutineCtrFlg(enRoutineCtrlType index, BOOL flg)
{
	s_RoutineCtrlFlg[index] = flg;
}

/**************************************************************************
* RoutineCtrol类名 ：ComStartRoutine
* 功能描述：         通用的Routine Ctrol服务
***************************************************************************/
/*0x31-01 返回状态为1个字节时调用*/
void DescRoutineCtrl_ComStartRoutine(RoutineResultType* pRoutRst)
{
	cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_START_ROUTINE;
	*pRoutRst = RoutineStartSuccess;
	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.cDataBuf[4] = (INT8U) * pRoutRst;
	if(!DescSuppressPosRspBit)
	{
    	TpTxInfoStruct.wDataLength = 5;
    	DescNrc = DescNrcOK;
	}
}
/*0x31-01 返回状态为1个字节或多字节时调用*/
void DescRoutineCtrl_ComStartRoutineWtihLen(INT8U *pRoutRst, INT8U * pRoutRstTmp, INT8U RoutRstTmpLen)
{
    INT8U i=0;
    
    if(RoutRstTmpLen <= 4u)
    {
        cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_START_ROUTINE;
        TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
        for(i=0; i<RoutRstTmpLen; i++)
        {
            pRoutRst[i] = pRoutRstTmp[i];
            TpTxInfoStruct.cDataBuf[4u + i] = pRoutRst[i];
        }
        if(!DescSuppressPosRspBit)
        {
            TpTxInfoStruct.wDataLength = 4u+RoutRstTmpLen;
            DescNrc = DescNrcOK;
        }
    }
}

/*0x31-02 返回状态为1个字节时调用*/
void DescRoutineCtrl_ComStopRoutine(RoutineResultType *pRoutRst)
{
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);//控制的序列要按顺序
	}
	else
	{
		if(cDescRoutineControlSequence[gRoutCtrlIDIndex] != DESC_ROUTINE_CONTROL_STOP_ROUTINE)
		{
			*pRoutRst = RoutinestopOK;
		}
		else
		{
			*pRoutRst = RoutinecompletedNOK;
		}
		cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_STOP_ROUTINE;
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		TpTxInfoStruct.cDataBuf[4] = (INT8U) * pRoutRst;
		if(!DescSuppressPosRspBit)
		{
    		TpTxInfoStruct.wDataLength = 5;
    		DescNrc = DescNrcOK;
		}
	}
}
/*0x31-02 返回状态为1个字节或多字节时调用*/
void DescRoutineCtrl_ComStopRoutineWtihLen(INT8U *pRoutRst, INT8U * pRoutRstTmp, INT8U RoutRstTmpLen)
{
    INT8U i=0;
    
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);
	}
	else
	{
	    if(RoutRstTmpLen <= 4u)
	    {
            cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_STOP_ROUTINE;
            TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
            for(i=0; i<RoutRstTmpLen; i++)
            {
                pRoutRst[i] = pRoutRstTmp[i];
                TpTxInfoStruct.cDataBuf[4u + i] = pRoutRst[i];
            }
            if(!DescSuppressPosRspBit)
            {
                TpTxInfoStruct.wDataLength = 4u+RoutRstTmpLen;
                DescNrc = DescNrcOK;
            }
	    }
	}
}

/*0x31-03 返回状态为1个字节时调用*/
static void DescRoutineCtrl_ComRequestRoutineResults(RoutineResultType RoutRstTmp)
{
	RoutineResultType RoutRst = Routinenotactivated;
	
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);
	}
	else
	{
		if(cDescRoutineControlSequence[gRoutCtrlIDIndex] != DESC_ROUTINE_CONTROL_STOP_ROUTINE)
		{
			RoutRst = RoutRstTmp;
			cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_REQUEST_ROUTINE_RESULT;
		}
		else
		{
			RoutRst = Routinenotactivated;
		}
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		TpTxInfoStruct.cDataBuf[4] = (INT8U) RoutRst;
		if(!DescSuppressPosRspBit)
		{
    		TpTxInfoStruct.wDataLength = 5;
    		DescNrc = DescNrcOK;
		}
	}
}
/*0x31-03 返回状态为1个字节或多字节时调用*/
void DescRoutineCtrl_ComRequestRoutineResultsWtihLen(INT8U *pRoutRst, INT8U * pRoutRstTmp, INT8U RoutRstTmpLen)
{
    INT8U i = 0;
    
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);
	}
	else
	{
		if(cDescRoutineControlSequence[gRoutCtrlIDIndex] != DESC_ROUTINE_CONTROL_STOP_ROUTINE)
		{
		    if(RoutRstTmpLen <= 4u)
		    {
                TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		        for(i=0; i<RoutRstTmpLen; i++ )
		        {
		            pRoutRst[i] = pRoutRstTmp[i];
                    TpTxInfoStruct.cDataBuf[4 + i] = pRoutRst[i];
		        }
		        
                if(!DescSuppressPosRspBit)
                {
                    TpTxInfoStruct.wDataLength = 4+RoutRstTmpLen;
                    DescNrc = DescNrcOK;
                }
		    }
			cDescRoutineControlSequence[gRoutCtrlIDIndex] = DESC_ROUTINE_CONTROL_REQUEST_ROUTINE_RESULT;

		}
		else
		{
			*pRoutRst = Routinenotactivated;

            TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
            TpTxInfoStruct.cDataBuf[4] = (INT8U) * pRoutRst;
            if(!DescSuppressPosRspBit)
            {
                TpTxInfoStruct.wDataLength = 5;
                DescNrc = DescNrcOK;
            }
		}
	}
}


void DescRoutineCtrlSequenceSet(INT8U SetDat)
{
	INT8U i;
	for(i = 0; i < UBOUND(cDescRoutineControlSequence); i++)
	{
		cDescRoutineControlSequence[i] = SetDat;
	}
	
	for(i = 0; i < EN_ROUTINECTRLTYPEMAX; i++)
	{
		s_RoutineCtrlFlg[i] = SetDat;
	}
	
}

/********************************************************************
* 函数名称：DescRoutineControl
* 功能描述：诊断例程控制
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescRoutineControl(void)
{
	INT16U  wRoutineCtrlID;
	INT8U cRoutineCtrlTypeIndex;
	INT8U cRoutineCtrlIDFound = FALSE;
	INT8U cRoutineCtrlTypeFound = FALSE;
	const tROUTINTE_INFO *pRoutCtlInfo;
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
		TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
	if(TpRxInfoStruct.wDataLength < 4)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
#if 1 /*20230919*/
	if((DescCheckVehSpd() == FALSE) || \
		(Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT))//车速大于3km/h
	{
		//nrc22
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}
#endif        
	/*31服务不支持禁止肯定响应位*/
	if(0x80U == (TpRxInfoStruct.cDataBuf[1] & 0x80U))
	{
		DescNrc = (kDescNrcSubfunctionNotSupported);
		return;
	}
	wRoutineCtrlID = TpRxInfoStruct.cDataBuf[2];
	wRoutineCtrlID <<= 8;
	wRoutineCtrlID |= TpRxInfoStruct.cDataBuf[3];

	
	if(DescSessionSA_CfgChk(eSID_ROUTINE_CONTROL_INDEX))
	{
		return;
	}

    for(cRoutineCtrlTypeIndex = 0; cRoutineCtrlTypeIndex < UBOUND(cDescRoutineControlTypeID); cRoutineCtrlTypeIndex++)
    {
        if(cDescRoutineControlTypeID[cRoutineCtrlTypeIndex] == (TpRxInfoStruct.cDataBuf[1] & 0x7f))
        {
            cRoutineCtrlTypeFound = TRUE;
            DescSuppressRosRspBitSet();
            for(gRoutCtrlIDIndex = 0; gRoutCtrlIDIndex < UBOUND(pRoutineCtlTbl); gRoutCtrlIDIndex++)
            {
                if(pRoutineCtlTbl[gRoutCtrlIDIndex].sDID == wRoutineCtrlID)
                {
                    cRoutineCtrlIDFound = TRUE;

                    /* 无测试模式才进入判断会话 */
					if(DescRoutineCtrl_GetDareTestFlag() == FALSE)
                    {
                    	if ((cDescSession & pRoutineCtlTbl[gRoutCtrlIDIndex].SessionAllow) == 0x00U)
                    	{ //会话层不满足要求
                            DescNrc = kDescNrcServiceNotSupportedInActiveSession;
                            return;
                    	}
    					
    					if(SA_NULL != pRoutineCtlTbl[gRoutCtrlIDIndex].SecurityAllow)
    					{
    						/*判断安全认证级别是否达到*/
    						if ( Desc_stsSecLvl.CurrLvl < pRoutineCtlTbl[gRoutCtrlIDIndex].SecurityAllow) 
    						{
    							DescNrc = kDescNrcAccessDenied;
    							return; 
    						}
    					}
                    }
					
                    pRoutCtlInfo = &pRoutineCtlTbl[gRoutCtrlIDIndex].RoutineInfo[cRoutineCtrlTypeIndex];
                    if(NULL == pRoutCtlInfo->ServiceProcess)
					{
						DescNrc = kDescNrcSubfunctionNotSupported;
					}
					else if(pRoutCtlInfo->ReqDatLen == TpRxInfoStruct.wDataLength)
					{
						pRoutCtlInfo->ServiceProcess();
					}
					else
					{
						/* Invalid Service Request Length */
						DescNrc = (kDescNrcIncorrectMessageLengthOrInvalidFormat);
					}
                }
            }
            if(cRoutineCtrlIDFound == FALSE)
        	{
        		DescNrc = (kDescNrcRequestOutOfRange);
        	}
        }
    }
    if(cRoutineCtrlTypeFound == FALSE)
    {
        if(TST_PhysicalReq == TpRxInfoStruct.cCANIDIndex)
        {
            DescNrc = (kDescNrcSubfunctionNotSupported);
        }
    }

}

BOOL UdsApp_GetSysEolModeInd(void)
{
    return SysEolModeInd;
}



/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6011_DR_Seat_Position_Learning_StartRoutile
 *
 * @description:   开启主驾座椅学习例程
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-05-25
 ***********************************************************************************************/
void DescRoutineCtrl_6011_DR_Seat_Position_Learning_StartRoutile(void)
{
	INT8U i = 0;
	
	INT8U DrMemoryCfg = 0;
	INT8U DrAdjustCfg = 0;
	INT8U InlearnSts = 0;

	DrMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	DrAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	InlearnSts = Rte_GetVfb_DrLearnSts();
	/*主驾无霍尔|| 手动调节*/
	if((DrMemoryCfg == FALSE) || (DrAdjustCfg == 0) \
    || (DrAdjustCfg == 3) || (InlearnSts == enLearnSts_enLearnning) || \
    	(Rte_GetVfb_DrHeightSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrBackSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrFrontSwitchCmd() != EN_MOTOR_DEF) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.DRSeatLearning);
	//开启主驾学习例程时，清除主驾硬止点
	Cdd_ClearDriverHardStopData();
	Rte_SetVfb_DrLearnSts(FALSE);//清零学习状态，避免连续学习成功，第二次以后无法复位by Prima Niu 20250604
    Rte_SetVfb_DrLearnEnable(TRUE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6011_DR_Seat_Position_Learning_StoptRoutile
 *
 * @description:   关闭主驾座椅学习例程
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-05-25
 ***********************************************************************************************/
void DescRoutineCtrl_6011_DR_Seat_Position_Learning_StopRoutile(void)
{
	INT8U DrMemoryCfg = 0;
	INT8U DrAdjustCfg = 0;
	
	DrMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	DrAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	/*主驾无霍尔|| 手动调节*/
	if((DrMemoryCfg == FALSE) || (DrAdjustCfg == 0) || (DrAdjustCfg == 3) || \
    	(Rte_GetVfb_DrHeightSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrBackSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrFrontSwitchCmd() != EN_MOTOR_DEF) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.DRSeatLearning);
    Rte_SetVfb_DrLearnEnable(FALSE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6011_DrLearnMotorsStsRoutine(void)
 *
 * @description:	查询主驾电机学习状态
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-25
 ***********************************************************************************************/
static void DescRoutineCtrl_6011_DR_Seat_Position_Learning_ReqRoutineRlt(void)
{

	INT8U i = 0;
	INT8U temp = 0;
	INT8U InlearnSts = 0;
	INT8U InLearnExitCause = 0;
	static INT8U OutlearnSts = 0;
	INT8U DrMemoryCfg = 0;
	INT8U DrAdjustCfg = 0;
	
	DrMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	DrAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	/*主驾无霍尔|| 手动调节*/
	if((DrMemoryCfg == FALSE) || (DrAdjustCfg == 0) || (DrAdjustCfg == 3) || \
    	(Rte_GetVfb_DrHeightSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrBackSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_DrFrontSwitchCmd() != EN_MOTOR_DEF) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued)) || \
		(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);
		return;
	}

	InlearnSts = Rte_GetVfb_DrLearnSts();
	InLearnExitCause = Rte_GetVfb_LearnExitCause();

	if(InlearnSts == enLearnSts_enLearnAllSuccess)
	{
		OutlearnSts = DESC_ALL_learned_successful;
	}
	else
	{
		switch(InLearnExitCause)//如果没有学习成功则查询失败原因，没有失败原因就是还在学习中
		{
			case enLearnExitCause_enInvalid :
				OutlearnSts = DESC_learnning;
				break;
			case enLearnExitCause_enMotorRunOverTime_L :
			case enLearnExitCause_enMotorRunOverTime_B :
			case enLearnExitCause_enMotorRunOverTime_F :
			case enLearnExitCause_enMotorRunOverTime_H :
			case enLearnExitCause_enRelayAdhesionFault :
			case enLearnExitCause_enHallFault :
			case enLearnExitCause_enOTA :
			case enLearnExitCause_enVehSpeed :
			case enLearnExitCause_enManualInterupt :
			case enLearnExitCause_enVoltFault :
			case enLearnExitCause_enLearnOverTime :
			case enLearnExitCause_enDescStop :
				OutlearnSts = DESC_learned_fault;
				break;
			default:OutlearnSts = DESC_ALL_not_learned; break;
		}
	}
	TpTxInfoStruct.cDataBuf[2] = 0x60UL;
	TpTxInfoStruct.cDataBuf[3] = 0x11UL;

	TpTxInfoStruct.cDataBuf[4] = OutlearnSts;
	TpTxInfoStruct.wDataLength = 5;
	DescNrc = DescNrcOK;    

}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6012_PA_Seat_Position_Learning_StartRoutile
 *
 * @description:   开启副驾座椅学习例程
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-05-25
 ***********************************************************************************************/
void DescRoutineCtrl_6012_PA_Seat_Position_Learning_StartRoutile(void)
{
	INT8U i = 0;
	INT8U PaMemoryCfg = 0;
	INT8U PaAdjustCfg = 0;
	INT8U InlearnSts = 0;
    
	PaMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	PaAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	InlearnSts = Rte_GetVfb_PaLearnSts();
	/*副驾无霍尔|| 手动调节*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0)\
     || (InlearnSts == enLearnSts_enLearnning) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	
	DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.PASeatLearning);
	//开启副驾学习例程时，清除副驾硬止点
	Cdd_ClearPassengerHardStopData();
	Rte_SetVfb_PaLearnSts(FALSE);//清零学习状态，避免连续学习成功，第二次以后无法复位by Prima Niu 20250604
    Rte_SetVfb_PaLearnEnable(TRUE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6012_PA_Seat_Position_Learning_StoptRoutile
 *
 * @description:   关闭副驾座椅学习例程
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-05-25
 ***********************************************************************************************/
void DescRoutineCtrl_6012_PA_Seat_Position_Learning_StopRoutile(void)
{
	INT8U PaMemoryCfg = 0;
	INT8U PaAdjustCfg = 0;
	
	PaMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	PaAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	/*副驾无霍尔|| 手动调节*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.PASeatLearning);
    Rte_SetVfb_PaLearnEnable(FALSE);

}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6012_PaLearnMotorsStsRoutine(void)
 *
 * @description:	查询副驾电机学习状态
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-25
 ***********************************************************************************************/
static void DescRoutineCtrl_6012_PA_Seat_Position_Learning_ReqRoutineRlt(void)
{

	INT8U temp = 0;
	INT8U InlearnSts = 0;
	INT8U InLearnExitCause = 0;
	static INT8U OutlearnSts = 0;
	INT8U PaMemoryCfg = 0;
	INT8U PaAdjustCfg = 0;
	
	PaMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	PaAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	/*副驾无霍尔|| 手动调节*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //电机无霍尔，不支持学习
		return;
	}
	
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);
		return;
	}  
	
	InlearnSts = Rte_GetVfb_PaLearnSts();
	InLearnExitCause = Rte_GetVfb_PaLearnExitCause();

	if(InlearnSts == enLearnSts_enLearnAllSuccess)
	{
		OutlearnSts = DESC_ALL_learned_successful;
	}
	else
	{
		switch(InLearnExitCause)//如果没有学习成功则查询失败原因，没有失败原因就是还在学习中
		{
			case enLearnExitCause_enInvalid :
				OutlearnSts = DESC_learnning;
				break;
			case enLearnExitCause_enMotorRunOverTime_L :
			case enLearnExitCause_enMotorRunOverTime_B :
			case enLearnExitCause_enMotorRunOverTime_F :
			case enLearnExitCause_enMotorRunOverTime_H :
			case enLearnExitCause_enRelayAdhesionFault :
			case enLearnExitCause_enHallFault :
			case enLearnExitCause_enOTA :
			case enLearnExitCause_enVehSpeed :
			case enLearnExitCause_enManualInterupt :
			case enLearnExitCause_enVoltFault :
			case enLearnExitCause_enLearnOverTime :
			case enLearnExitCause_enDescStop :
				OutlearnSts = DESC_learned_fault;
				break;
			default:OutlearnSts = DESC_ALL_not_learned; break;
		}
	}
	
	TpTxInfoStruct.cDataBuf[2] = 0x60UL;
	TpTxInfoStruct.cDataBuf[3] = 0x12UL;
	TpTxInfoStruct.cDataBuf[4] = OutlearnSts;
	TpTxInfoStruct.wDataLength = 5;
	DescNrc = DescNrcOK;
        
}




void DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile(void)
{
	/*车速大于3km/h 禁止刷写*/
	//if((1 == b_WCBS_ESP_5_WCBS_ESP5_F_VehicleSpeed_b()) && ((( b_WCBS_ESP_5_WCBS_ESP5_N_VehicleSpeed_b() ) * 0.05625) > 3) )
	{
	//	DescNrc = kDescNrcConditionsNotCorrect;
	//	return;
	}
	sRoutine0203Sts = TRUE;
	 
	TpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;
	TpTxInfoStruct.cDataBuf[1] = 0x01;
	TpTxInfoStruct.cDataBuf[2] = 0x02;
	TpTxInfoStruct.cDataBuf[3] = 0x03;    
	//TpTxInfoStruct.cDataBuf[4] = 0x00;
	
	TpTxInfoStruct.wDataLength = 4u;
	// DescRoutineCtrl_ComStartRoutine(0x00);
	 DescNrc = DescNrcOK;
}
/***********************************************************************************************
 * @function name:  DescRoutineCtrl_3174_RestoreDefaultSettings_StartRoutile
 *
 * @description:   执行恢复原始数据
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    zjx
 *
 * @note:    2023-03-10
 ***********************************************************************************************/
void DescRoutineCtrl_6010_RestoreDefaultSettings_StartRoutile(void)
{

	Srvl_E2AllDataInit();
	Cdd_ReadAllHallFromE2();
	s_RecoverDefaultFlag = TRUE;
	s_RecoverDefaultFlag2 = TRUE;
	DescRoutineCtrlSequenceSet(0);//mantis 6884
	Rte_SetVfb_DrLearnSts(FALSE);//清零学习状态，避免连续学习成功，第二次以后无法复位by Prima Niu 20250604
	Rte_SetVfb_PaLearnSts(FALSE);//清零学习状态，避免连续学习成功，第二次以后无法复位by Prima Niu 20250604
	Desc_OpTimeLongerThanP2Flag = TRUE;
	DescNrc = kDescNrcResponsePending;
}
/***********************************************************************************************
 * @function name:  DescRoutineCtrl_FE10_DareSleep_StartRoutile
 *
 * @description:   启动休眠
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    LC
 *
 * @note:    2024-04-18
 ***********************************************************************************************/
 static void DescRoutineCtrl_FE10_DareSleep_StartRoutile(void)
{
    OsekNmSleep_SetDescSleepFlg(TRUE);
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.DareSleep);
}


/***********************************************************************************************
 * @function name:  DescRoutineCtrl_FE0F_DareTest_StartRoutile
 *
 * @description:   启动成测测试
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    LC
 *
 * @note:    2024-04-18
 ***********************************************************************************************/

void DescRoutineCtrl_FE0F_DareTest_StartRoutile(void)
{
	s_DareTestFlag = TRUE;
	Srvl_SetMemIndexDataU8(EN_MemIndex_TestMode, TRUE);
	DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.DareTest);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_FE0F_DareTest_StopRoutile
 *
 * @description:   停止成测测试
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    LC
 *
 * @note:    2024-04-18
 ***********************************************************************************************/

void DescRoutineCtrl_FE0F_DareTest_StopRoutile(void)
{
	s_DareTestFlag = FALSE;
	Srvl_SetMemIndexDataU8(EN_MemIndex_TestMode, FALSE);
	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.DareTest);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_FE0F_DareTest_ReqRoutineRlt
 *
 * @description:   查询成测测试
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    LC
 *
 * @note:    2024-04-18
 ***********************************************************************************************/

void DescRoutineCtrl_FE0F_DareTest_ReqRoutineRlt(void)
{
	TpTxInfoStruct.cDataBuf[4] = DescRoutineCtrl_GetDareTestFlag();
	TpTxInfoStruct.wDataLength = 5;
	DescNrc = DescNrcOK;
}
/***********************************************************************************************
 * @function name:  DescRoutineCtrl_GetDareTestFlag
 *
 * @description:   获取当前是否在成测例程中
 *
 * @input parameters:   无
 *
 * @output parameters:   无
 *
 * @return:    无
 *
 * @note:     无
 *
 * @author:    LC
 *
 * @note:    2024-04-18
 ***********************************************************************************************/

INT8U DescRoutineCtrl_GetDareTestFlag(void)
{
	return (Srvl_GetMemIndexDataU8(EN_MemIndex_TestMode) == TRUE)?(TRUE):(FALSE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_GetRecoverDefaultFlag
 *
 * @description:   获取诊断恢复出厂设置命令标志
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         是否恢复出厂
 *
 * @note:         
 *
 * @author:       zjx
 *
 * @date:           2023.06.20
 ***********************************************************************************************/
INT8U DescRoutineCtrl_GetRecoverDefaultFlag(void)
{
	return s_RecoverDefaultFlag2;
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_GetRecoverDefaultFlag
 *
 * @description:   设置诊断恢复出厂设置命令标志
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         void
 *
 * @note:         
 *
 * @author:       zjx
 *
 * @date:           2023.06.20
 ***********************************************************************************************/
void DescRoutineCtrl_SetRecoverDefaultFlag(INT8U flg)
{
	s_RecoverDefaultFlag2 = flg;
}

/***********************************************************************************************
 * @function name:  RecoverDefaultFlagFunction
 *
 * @description:   供模型调用，调用周期10ms
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         是否恢复出厂
 *
 * @note:           供模型调用，调用周期10ms
 *
 * @author:         Prima Niu
 *
 * @date:           2022.10.22
 ***********************************************************************************************/
INT8U GetRecoverDefaultFlag(void)
{
	return s_RecoverDefaultFlag;
}

/***********************************************************************************************
 * @function name:  RecoverDefaultFlagFunction
 *
 * @description:    将恢复出厂标志位延时50ms清零
 *
 * @input parameters:    void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           需要在10ms任务调度周期内执行
 *
 * @author:         Prima Niu
 *
 * @date:           2022.10.22
 ***********************************************************************************************/
void RecoverDefaultFlagFunction(void)
{
	static INT8U u8Timer50ms = 0x0u;
	
	
	if(0x1u == s_RecoverDefaultFlag)
	{
		(u8Timer50ms < D_50msTime)?(u8Timer50ms ++):(u8Timer50ms = D_50msTime);
	}
	/*50ms后清零恢复出厂设置标志位*/
	if(D_50msTime <= u8Timer50ms)
	{
		u8Timer50ms = 0x0u;
		s_RecoverDefaultFlag = 0x0u;
	}
}

/**************************************************************************
* RoutineCtrol类名 ：SysIntoEolMode
* 功能描述：         进入EOL模式
***************************************************************************/
static void UdsApp_RountineCtrl_SysIntoEolModeStart(void)
{
    SysEolModeInd = TRUE;
    UdsRoutineEolResult = EN_UDS_ROUTINE_EOL_SUCCESS;
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.SysIntoEolMode);
}

static void UdsApp_RountineCtrl_SysIntoEolModeStop(void)
{
	if(SysEolModeInd == TRUE)
	{
		SysEolModeInd = FALSE;
    	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.SysIntoEolMode);
	}
	else
	{
		DescNrc = kDescNrcRequestSequenceError;
	}

}

static void UdsApp_RountineCtrl_SysIntoEolModeResult(void)
{
	RoutineResultType RoutRstTmp = Routinenotactivated;
	
	if(SysEolModeInd == TRUE)
	{
		RoutRstTmp = Routineinprogress;
		AppDesc_stsRoutineResult.SysIntoEolMode = Routineinprogress;
		
	}
    DescRoutineCtrl_ComRequestRoutineResults(RoutRstTmp);
}

void UdsApp_RoutineCtrlSetEolEskDataException(void)
{
    UdsRoutineEolResult = EN_UDS_ROUTINE_EOL_ESK_VALUE_EXCEPTION;
}


/**************************************************************************
* RoutineCtrol类名 ：SysOnlineTest
* 功能描述：开始 结束 查询 在线调试流程
***************************************************************************/
static void DescRoutineCtrl_SysOnlineTestStartRoutine(void)
{
    SysOnlineTestModeInd = TRUE;
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.SysOnlineTestMode);
}

static void DescRoutineCtrl_SysOnlineTestStopRoutine(void)
{
    SysOnlineTestModeInd = FALSE;
    DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.SysOnlineTestMode);
}

static void DescRoutineCtrl_SysOnlineTestRequestRoutineResults(void)
{
	RoutineResultType RoutRstTmp = Routinenotactivated;
	
	if(SysOnlineTestModeInd == TRUE)
	{
		RoutRstTmp = Routineinprogress;
		
	}
	
	AppDesc_stsRoutineResult.SysOnlineTestMode = RoutRstTmp;
    DescRoutineCtrl_ComRequestRoutineResults(RoutRstTmp);
}

static void UdsApp_ClrSysOnlineTestModeInd(void)
{
    SysOnlineTestModeInd = FALSE;
}

BOOL UdsApp_GetSysOnlineTestModeInd(void)
{
    return SysOnlineTestModeInd;
}




/**************************************************************************
* RoutineCtrol类名 ：static void DescRoutineCtrl_ClrPowerOnInfoStartRoutine(void)
* 功能描述：         清除上电信息
***************************************************************************/
static void DescRoutineCtrl_ClrPowerOnInfoStartRoutine(void)
{
#if 0
    if (UdsApp_GetSysEolModeInd() == FALSE)
    {
        DescNrc = kDescNrcConditionsNotCorrect;
        return;
    }
    
    Srvl_ClrSavedBoardPowerOnCnt();
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.ClrPowerOnInfoRlt);
#endif    
}

static void DescRoutineCtrl_ClrPowerOnInfoStopRoutine(void)
{
    DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.ClrPowerOnInfoRlt);
}

static void DescRoutineCtrl_ClrPowerOnInfoReqRoutineRlt(void)
{
#if 0
  RoutineResultType RoutRstTmp = Routineinprogress;

	if((Srvl_GetEepromIndexOperateEnd(EN_SRV_MemIndex_BoardPowerOnTypeAndCnt) == TRUE))
	{
		RoutRstTmp = RoutinestopOK;
		
		if(Srvl_GetEepromIndexOptRlt(EN_SRV_MemIndex_BoardPowerOnTypeAndCnt) == TRUE)
		{
			RoutRstTmp = RoutinecompletedwithOK;
		}
		else
		{
			RoutRstTmp = RoutinecompletedNOK;
		}
	}
	
	AppDesc_stsRoutineResult.ClrPowerOnInfoRlt = RoutRstTmp;
    DescRoutineCtrl_ComRequestRoutineResults(RoutRstTmp);
#endif    
}

void UdsRoutineCtrl_SessionChangedToDefault(void)
{
	SysEolModeInd = FALSE;
	UdsRoutineEolResult = EN_UDS_ROUTINE_EOL_SUCCESS;
	SysOnlineTestModeInd = FALSE;
    bNoFeedWatchDogIntoLimphomeFlag = FALSE;
}

/**************************************************************************
* RoutineCtrol类名 ：DescRoutineCtrl_ForceIntoSleepModeStartRoutine
* 功能描述：         立即进入休眠模式
***************************************************************************/
static void DescRoutineCtrl_ForceIntoSleepModeStartRoutine(void)
{
    // 运行条件检测
    if( (UdsApp_GetSysOnlineTestModeInd() == FALSE))
    {
        DescNrc = kDescNrcConditionsNotCorrect;
        return;
    }
    
    bForceIntoSleepModeInd = TRUE;
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.ForceIntoSleepModeRlt);
}

BOOL UdsRoutineCtrl_ForceIntoSleepModeInd(void)
{
	BOOL bRet=FALSE;

    //if( Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode) == 0U )
    {
		bRet = bForceIntoSleepModeInd;
    }
    
	return bRet;
}

/**************************************************************************
* RoutineCtrol类名 ：NoFeedWatchDogIntoLimphomeSta
* 功能描述：开始 结束 查询  不喂狗进入limphome状态
***************************************************************************/
static void DescRoutineCtrl_NoFeedWatchDogIntoLimphomeStaStartRoutine(void)
{
    // 运行条件检测
    if (UdsApp_GetSysOnlineTestModeInd() == FALSE)
    {
        DescNrc = kDescNrcConditionsNotCorrect;
        return;
    }

    bNoFeedWatchDogIntoLimphomeFlag = TRUE;
    DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.NoFeedWatchDogIntoLimphome);
}

static void DescRoutineCtrl_NoFeedWatchDogIntoLimphomeStaReqRlt(void)
{
	RoutineResultType RoutRstTmp = Routinenotactivated;
	
	if(bNoFeedWatchDogIntoLimphomeFlag == TRUE)
	{
		RoutRstTmp = RoutinestopOK;
	}
	
	AppDesc_stsRoutineResult.NoFeedWatchDogIntoLimphome = RoutRstTmp;
    DescRoutineCtrl_ComRequestRoutineResults(RoutRstTmp);
}

static void UdsApp_ClrNoFeedWatchDogIntoLimphomeStaInd(void)
{
    bNoFeedWatchDogIntoLimphomeFlag = FALSE;
}

BOOL UdsApp_GetNoFeedWatchDogIntoLimphomeStaInd(void)
{
	BOOL bIntoLimphomeFlag = FALSE;
	
    if (UdsApp_GetSysOnlineTestModeInd() == TRUE)
    {
    	bIntoLimphomeFlag = bNoFeedWatchDogIntoLimphomeFlag;
    }
    
    return bIntoLimphomeFlag;
}




/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  
