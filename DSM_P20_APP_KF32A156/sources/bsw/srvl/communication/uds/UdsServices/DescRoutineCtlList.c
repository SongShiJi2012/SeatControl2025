/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescRoutineCtlList.c
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             RoutingCtrol�б�
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven Ī����
** Created date:            2013.10.19
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

static INT8U sRoutine0203Sts = FALSE; //�Ƿ�ִ��31 01 02 03���̲��ظ�����Ӧ

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

/*! @brief ����������ͨ����־  */
static BOOL UdsApp_ProgChkCondInd = FALSE;
static  INT8U gRoutCtrlIDIndex = 0;

static BOOL s_learnDrMotorFlg = FALSE;	//�����������ѧϰ�����־λ
static	enLeanStep s_learnDrMotorStep = enStepNULL; //�����������ѧϰ�������
static INT8U s_DrMotorLearnSts = 0; //���ݵ��ѧϰ״̬

static BOOL s_learnPaMotorFlg = FALSE;	//������̸���ѧϰ�����־λ
static	enLeanStep s_learnPaMotorStep = enStepNULL; //������̸���ѧϰ�������
static INT8U s_PaMotorLearnSts = 0; //���ݵ��ѧϰ״̬
static INT8U s_RecoverDefaultFlag = 0x0u;/*�ָ�������־λ*/
static INT8U s_RecoverDefaultFlag2 = 0x0u;/*�ָ�������־λ2*/
static INT8U s_DareTestFlag = 0x0u;/*�ɲ⿪����־*/

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
 * @description:   ��ȡ���̿��Ʊ�־λ
 *
 * @input parameters:   index ��־λ�±�
 *
 * @output parameters:   ��
 *
 * @return:    �����Ƿ�����־
 *
 * @note:     ��
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
 * @description:   �������̿��Ʊ�־λ
 *
 * @input parameters:   index ��־λ�±�, flg ���̿�����־
 *
 * @output parameters:   ��
 *
 * @return:    void
 *
 * @note:     ��
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
* RoutineCtrol���� ��ComStartRoutine
* ����������         ͨ�õ�Routine Ctrol����
***************************************************************************/
/*0x31-01 ����״̬Ϊ1���ֽ�ʱ����*/
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
/*0x31-01 ����״̬Ϊ1���ֽڻ���ֽ�ʱ����*/
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

/*0x31-02 ����״̬Ϊ1���ֽ�ʱ����*/
void DescRoutineCtrl_ComStopRoutine(RoutineResultType *pRoutRst)
{
	if(DESC_ROUTINE_CONTROL_NULL == cDescRoutineControlSequence[gRoutCtrlIDIndex])
	{
		DescNrc = (kDescNrcRequestSequenceError);//���Ƶ�����Ҫ��˳��
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
/*0x31-02 ����״̬Ϊ1���ֽڻ���ֽ�ʱ����*/
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

/*0x31-03 ����״̬Ϊ1���ֽ�ʱ����*/
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
/*0x31-03 ����״̬Ϊ1���ֽڻ���ֽ�ʱ����*/
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
* �������ƣ�DescRoutineControl
* ����������������̿���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
		(Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT))//���ٴ���3km/h
	{
		//nrc22
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}
#endif        
	/*31����֧�ֽ�ֹ�϶���Ӧλ*/
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

                    /* �޲���ģʽ�Ž����жϻỰ */
					if(DescRoutineCtrl_GetDareTestFlag() == FALSE)
                    {
                    	if ((cDescSession & pRoutineCtlTbl[gRoutCtrlIDIndex].SessionAllow) == 0x00U)
                    	{ //�Ự�㲻����Ҫ��
                            DescNrc = kDescNrcServiceNotSupportedInActiveSession;
                            return;
                    	}
    					
    					if(SA_NULL != pRoutineCtlTbl[gRoutCtrlIDIndex].SecurityAllow)
    					{
    						/*�жϰ�ȫ��֤�����Ƿ�ﵽ*/
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
 * @description:   ������������ѧϰ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
	/*�����޻���|| �ֶ�����*/
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
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
		return;
	}
	DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.DRSeatLearning);
	//��������ѧϰ����ʱ���������Ӳֹ��
	Cdd_ClearDriverHardStopData();
	Rte_SetVfb_DrLearnSts(FALSE);//����ѧϰ״̬����������ѧϰ�ɹ����ڶ����Ժ��޷���λby Prima Niu 20250604
    Rte_SetVfb_DrLearnEnable(TRUE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6011_DR_Seat_Position_Learning_StoptRoutile
 *
 * @description:   �ر���������ѧϰ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
	/*�����޻���|| �ֶ�����*/
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
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
		return;
	}
	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.DRSeatLearning);
    Rte_SetVfb_DrLearnEnable(FALSE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6011_DrLearnMotorsStsRoutine(void)
 *
 * @description:	��ѯ���ݵ��ѧϰ״̬
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
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
	/*�����޻���|| �ֶ�����*/
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
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
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
		switch(InLearnExitCause)//���û��ѧϰ�ɹ����ѯʧ��ԭ��û��ʧ��ԭ����ǻ���ѧϰ��
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
 * @description:   ������������ѧϰ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
	/*�����޻���|| �ֶ�����*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0)\
     || (InlearnSts == enLearnSts_enLearnning) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
		return;
	}
	
	DescRoutineCtrl_ComStartRoutine(&AppDesc_stsRoutineResult.PASeatLearning);
	//��������ѧϰ����ʱ���������Ӳֹ��
	Cdd_ClearPassengerHardStopData();
	Rte_SetVfb_PaLearnSts(FALSE);//����ѧϰ״̬����������ѧϰ�ɹ����ڶ����Ժ��޷���λby Prima Niu 20250604
    Rte_SetVfb_PaLearnEnable(TRUE);
}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6012_PA_Seat_Position_Learning_StoptRoutile
 *
 * @description:   �رո�������ѧϰ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
	/*�����޻���|| �ֶ�����*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
		return;
	}
	DescRoutineCtrl_ComStopRoutine(&AppDesc_stsRoutineResult.PASeatLearning);
    Rte_SetVfb_PaLearnEnable(FALSE);

}

/***********************************************************************************************
 * @function name:  DescRoutineCtrl_6012_PaLearnMotorsStsRoutine(void)
 *
 * @description:	��ѯ���ݵ��ѧϰ״̬
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
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
	/*�����޻���|| �ֶ�����*/
	if((PaMemoryCfg == FALSE) || (PaAdjustCfg == 0) || \
	    (Rte_GetVfb_PaLengthSwitchCmd() != EN_MOTOR_DEF) || \
		(Rte_GetVfb_PaBackSwitchCmd() != EN_MOTOR_DEF) || \
	     (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued)) || \
		 (TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
    	DescNrc = kDescNrcConditionsNotCorrect; //����޻�������֧��ѧϰ
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
		switch(InLearnExitCause)//���û��ѧϰ�ɹ����ѯʧ��ԭ��û��ʧ��ԭ����ǻ���ѧϰ��
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
	/*���ٴ���3km/h ��ֹˢд*/
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
 * @description:   ִ�лָ�ԭʼ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
	Rte_SetVfb_DrLearnSts(FALSE);//����ѧϰ״̬����������ѧϰ�ɹ����ڶ����Ժ��޷���λby Prima Niu 20250604
	Rte_SetVfb_PaLearnSts(FALSE);//����ѧϰ״̬����������ѧϰ�ɹ����ڶ����Ժ��޷���λby Prima Niu 20250604
	Desc_OpTimeLongerThanP2Flag = TRUE;
	DescNrc = kDescNrcResponsePending;
}
/***********************************************************************************************
 * @function name:  DescRoutineCtrl_FE10_DareSleep_StartRoutile
 *
 * @description:   ��������
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
 * @description:   �����ɲ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
 * @description:   ֹͣ�ɲ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
 * @description:   ��ѯ�ɲ����
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
 * @description:   ��ȡ��ǰ�Ƿ��ڳɲ�������
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
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
 * @description:   ��ȡ��ϻָ��������������־
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         �Ƿ�ָ�����
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
 * @description:   ������ϻָ��������������־
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
 * @description:   ��ģ�͵��ã���������10ms
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         �Ƿ�ָ�����
 *
 * @note:           ��ģ�͵��ã���������10ms
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
 * @description:    ���ָ�������־λ��ʱ50ms����
 *
 * @input parameters:    void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��Ҫ��10ms�������������ִ��
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
	/*50ms������ָ��������ñ�־λ*/
	if(D_50msTime <= u8Timer50ms)
	{
		u8Timer50ms = 0x0u;
		s_RecoverDefaultFlag = 0x0u;
	}
}

/**************************************************************************
* RoutineCtrol���� ��SysIntoEolMode
* ����������         ����EOLģʽ
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
* RoutineCtrol���� ��SysOnlineTest
* ������������ʼ ���� ��ѯ ���ߵ�������
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
* RoutineCtrol���� ��static void DescRoutineCtrl_ClrPowerOnInfoStartRoutine(void)
* ����������         ����ϵ���Ϣ
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
* RoutineCtrol���� ��DescRoutineCtrl_ForceIntoSleepModeStartRoutine
* ����������         ������������ģʽ
***************************************************************************/
static void DescRoutineCtrl_ForceIntoSleepModeStartRoutine(void)
{
    // �����������
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
* RoutineCtrol���� ��NoFeedWatchDogIntoLimphomeSta
* ������������ʼ ���� ��ѯ  ��ι������limphome״̬
***************************************************************************/
static void DescRoutineCtrl_NoFeedWatchDogIntoLimphomeStaStartRoutine(void)
{
    // �����������
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
  
