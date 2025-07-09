#define   Desc_GLOBALS

#include "uds_pub.h"
#include "Appl_PowerMangeModel.h"
#include "Ecual_Adc.h"
#include "ecual_wdog.h"

static volatile unsigned short wDescP4Timer = 0;
strDescECUResetReq DescECUResetReq;
BOOL bKeyLearnFlag = FALSE;
volatile INT8U cDescECUHardRestAnswerIndex = 0;

#define    SERVICE_LEN_CHECK            0xff

const tDESC_INFO  pDescHandlerTbl[] =
{
    {eSID_DIAGNOG_SESSION_CONTROL,   DescDiagnosticSessionControl},
    {eSID_ECU_HARD_RESET ,           DescEcuRest},
#if (SID14_CLRDESCINFO_EN == DESC_ENABLE)
    {eSID_CLR_DIAGNOSTIC_DTC ,       DescClearDiagnosticInformation},
#endif
#if (SID19_RDDTCINFO_EN == DESC_ENABLE)
    {eSID_READ_DTC_INFORMATION   ,   DescReadDTCInformation},
#endif
#if (SID22_READDID_EN == DESC_ENABLE)
    {eSID_READ_DATA_BY_IDENTIFIER ,  DescReadDataByIdentifier},
#endif
#if (SID27_SECURITYACCESS_EN == DESC_ENABLE)
    {eSID_SECURITY_ACCESS,           DescSecurityAccess},
#endif
#if SID28_COMCTL_EN
    {eSID_COMMUNICATION_CONTROL  ,   DescCommunicationControl},
#endif
#if SID2E_WRITEDID_EN == DESC_ENABLE
    {eSID_WRITE_DATA_BY_IDENTIFIER,  DescWriteDataByIdentifier},
#endif
#if (SID2F_IOCTRL_EN == DESC_ENABLE)
    {eSID_IOCONTROL_BY_IDENTIFIER,   DescInputOutputControlByIdentifier},
#endif
#if (SID31_ROUTINECTRL_EN == DESC_ENABLE)
    {eSID_ROUTINE_CONTROL,           DescRoutineControl},
#endif
#if SID34_REQDWNLOAD_EN == DESC_ENABLE
    {eSID_REQUEST_DOWNLOAD,          DescRequestDownload},
#endif
#if SID36_TRANFDATA_EN == DESC_ENABLE
    {eSID_TRANSFER_DATA,             DescTransferData},
#endif
#if SID37_TRANFEXIT_EN == DESC_ENABLE
    {eSID_REQUEST_TRANSFER_EXIT,     DescRequestTransferExit},
#endif
    {eSID_TESTER_PRESENT,            DescTesterPresent},
#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
    {eSID_CONTROL_DTC_SETTING,       DescControlDTCSetting},
#endif
#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)
    {eSID_PERIOD_DID_READ,           UdsApp_2AReadPeriodDid},
#endif
#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)
	{eSID_READ_MEMORY_BY_ADDR,		 UdsApp_23ReadMemoryByAddr},
#endif

    {eSID_CAN_TEST,                  DescCANTest},
};

const tDESC_SESSIONSACFG pDescSessSAConfigTbl[] = 
{
	{{SESN_DE,  SA_NULL},	{SESN_DE,	SA_NULL}},
		
	{{SESN_DE,	SA_NULL},	{SESN_DE,	SA_NULL}},
	
#if (SID14_CLRDESCINFO_EN == DESC_ENABLE)
	{{SESN_DE,	SA_NULL},   {SESN_DE,	SA_NULL}},
#endif

#if (SID19_RDDTCINFO_EN == DESC_ENABLE)
	{{SESN_DE,	SA_NULL},	{SESN_DE,	SA_NULL}},
#endif

#if (SID22_READDID_EN == DESC_ENABLE)
	{{SESN_DE,	SA_NULL},	{SESN_DE,   SA_NULL}},
#endif

#if (SID27_SECURITYACCESS_EN == DESC_ENABLE)
	{{SESN_EXTDS,	SESN_NULL},	{SESN_NULL,	    SA_NULL}},	
#endif

#if (SID28_COMCTL_EN == DESC_ENABLE)
	{{SESN_EXTDS,	SESN_NULL},	{SESN_EXTDS,	SA_NULL}},
#endif

#if SID2E_WRITEDID_EN == DESC_ENABLE
	{{SESN_EXTDS,	SA_EXTDS},{SESN_NULL,	SA_NULL}},
#endif
	
#if (SID2F_IOCTRL_EN == DESC_ENABLE)
	{{SESN_EXTDS,	SA_EXTDS},{SESN_NULL,	SA_NULL}},	
#endif
	
#if (SID31_ROUTINECTRL_EN == DESC_ENABLE)
   	{{SESN_EXTDS,	SA_EXTDS},{SESN_NULL,	SA_NULL}},
#endif

#if SID34_REQDWNLOAD_EN == DESC_ENABLE
    {{SESN_NULL,	SA_NULL},	{SESN_NULL,	SA_NULL}},
#endif
#if SID36_TRANFDATA_EN == DESC_ENABLE
    {{SESN_NULL,	SA_NULL},	{SESN_NULL,	SA_NULL}},
#endif
#if SID37_TRANFEXIT_EN == DESC_ENABLE
    {{SESN_NULL,	SA_NULL},	{SESN_NULL,	SA_NULL}},
#endif
    {{SESN_DPEVS,	SA_NULL},	{SESN_DPEVS,SA_NULL}},
		
#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
    {{SESN_EXTDS,	SA_NULL},	{SESN_EXTDS,SA_NULL}},
#endif

#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)
    {{SESN_EXTDS,	SESN_EXTDS},	{SA_NULL,SA_NULL}},
#endif

#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)
	{{SESN_DPEVS,	 SA_NULL},	  {SESN_DPEVS, SA_NULL}},
#endif

    {{SESN_DPEVS,	SA_NULL},	{SESN_DPEVS,SA_NULL}},
};


const INT8U cDescDiagnosticSession[] =
{
    0x01, 0x02, 0x03
};


const INT16U  wDescServiceRespTime[UBOUND(pDescHandlerTbl)] =
{
    /* Unit: Value * DescTask Call Cycle Time , ms ; here: value * 5ms = ? ms */
    DESC_P2_CAN_SERVER_MAX,  /* DescDiagnosticSessionControl : 50ms */
    40, 					 /* DescEcuRest : 200ms                 */
    #if (SID14_CLRDESCINFO_EN == DESC_ENABLE)
    200, 					 /* DescClearDiagnosticInformation: 1000ms */
   	#endif
	#if (SID19_RDDTCINFO_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescReadDTCInformation              */
    #endif
	#if (SID22_READDID_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescReadDataByIdentifier            */
    #endif
	#if (SID27_SECURITYACCESS_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescSecurityAccess                  */
    #endif
	#if (SID28_COMCTL_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,	 /* DescCommunicationControl       */
    #endif
	#if (SID2E_WRITEDID_EN == DESC_ENABLE)
    1000, 					 /* DescWriteDataByIdentifier: 5000ms   */
    #endif
	#if (SID2F_IOCTRL_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescInputOutputControlByIdentifier  */
    #endif
	#if (SID31_ROUTINECTRL_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescRoutineControl                  */
    #endif
	#if (SID34_REQDWNLOAD_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescRequestDownload		    */
    #endif
	#if (SID36_TRANFDATA_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescTransferData		    	    */
    #endif
	#if (SID37_TRANFEXIT_EN == DESC_ENABLE)
    DESC_P2_CAN_SERVER_MAX,  /* DescRequestTransferExit           */
    #endif
    DESC_P2_CAN_SERVER_MAX,  /* DescTesterPresent		           */
    #if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
    40, 					 /* DescControlDTCSetting: 200ms  */
    #endif

    DESC_P2_CAN_SERVER_MAX,  /* DescCANTest                           */
};

static void DescChangeToProSectionReset(enE2promOptResult WriteResult);

/********************************************************************
* 函数名称：DescInit
* 功能描述：诊断初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无 
* 备    注: 无
********************************************************************/
void DescInit(void)
{
    cDescTesterPresentTimer = 0;
    cDescSession = SESN_DS;
    wDescP4Timer = 0;
    DescRoutineCtrlSequenceSet(0);
    setRoutine0203Sts(FALSE);
    cDescTimer100ms = DESC_TIMER_100MS;
    cDescControlDTCSetting = DESC_CONTROL_DTC_SETTING_ON;
    cDescSessionChangedFlag = FALSE;
    cDescPrevSession = 0;
    cDescRespNoSend = FALSE;
    ProgramFlg = FALSE;
    u1gTesterPrsntFlg = FALSE;
    DescECUResetReq.cDescECUHardRestReq = FALSE;
    DescECUResetReq.cDescECUHardRestAnswerfg = FALSE;
    DescECUResetReq.cDescECUHardRestAnswerFnish = FALSE;

    unlockStatus = FALSE;
    bSeedReceive = FALSE;
    g_u8PINCodeAuthFailCnt = 0;
    PINCodeMatchFlgSet(FALSE);

    Desc_OpTimeLongerThanP2Flag = FALSE;
    u1gP2ExCntr = Desc_mgClrDTC_P2ExTIMES;
    Desc_stsSecLvl.CurrLvl = Desc_enmSecNonLvl;
    Desc_stsSecLvl.PreLvl = Desc_enmSecNonLvl;
    DiagResetWaitFlag = FALSE;
    AppDescInit();
   // Diag_setReserFlg(TRUE);  /*20230919 设置复位标志*/
}

/********************************************************************
* 函数名称：SessionConverGet
* 功能描述：值转换为相应的服务层
* 入口参数：SenssionType：服务层类型
* 出口参数：无
* 返 回 值：返回相应的服务层 
* 备    注: 无
********************************************************************/
INT8U SessionConverGet(INT8U SenssionType)
{
    INT8U  SessionTmp = SESN_DS;
    switch((eSESSION_TYPE)SenssionType)
    {
    case eSESSION_DEFAULT:
        SessionTmp = SESN_DS;
        break;
    case eSESSION_PROGRAM:
        SessionTmp = SESN_PRGS;
        break;
    case eSESSION_EXTENDED:
        SessionTmp = SESN_EXTDS;
        break;
    case eSESSION_VEHICLEFACTURER:
        SessionTmp = SESN_VMS;
        break;
    case eSESSION_SYSTEMSUPPLIER:
        SessionTmp = SESN_SSS;
        break;
    default:
        SessionTmp = SESN_DS;
        break;
    }
    return SessionTmp;
}

/********************************************************************
* 函数名称：SessionSA_CfgChk
* 功能描述：Session与SA 配置检查
* 入口参数：SenssionTypeIndex：服务层索引
* 出口参数：无
* 返 回 值：
* 备    注: 无
********************************************************************/
BOOL DescSessionSA_CfgChk(eSID_TYPE_INDEX SenssionTypeIndex)
{
	BOOL	RetVal = FALSE;

    if(DescRoutineCtrl_GetDareTestFlag() == TRUE)
    {
        return FALSE;
    }
    
	if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
	{
		if(!(pDescSessSAConfigTbl[SenssionTypeIndex].PhySessionSACfg.SessionAllow & cDescSession))
		{
			RetVal = TRUE;//该会话层不支持
			DescNrc = kDescNrcServiceNotSupportedInActiveSession;
		}
		else if(SA_NULL != pDescSessSAConfigTbl[SenssionTypeIndex].PhySessionSACfg.SA_Allow)
		{
			if(unlockStatus == FALSE)//安全访问没有通过
			{
				RetVal = TRUE;//访问禁止
				DescNrc = kDescNrcAccessDenied;
			}
		}
	}
	else if(TpRxInfoStruct.cCANIDIndex == TST_FunctionalReq)
	{
		if(!(pDescSessSAConfigTbl[SenssionTypeIndex].FucSessionSACfg.SessionAllow & cDescSession))
		{
			/*JMC要求功能寻址时,若不支持此服务时无需回复负响应*/
			RetVal = TRUE; 
			//DescNrc = kDescNrcServiceNotSupportedInActiveSession;
		}
	}
	return RetVal;
}


/********************************************************************
* 函数名称：DescTimeManage
* 功能描述：诊断时间管理
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescTimeManage(void)//普通的非EEPROM的诊断不会执行该函数的有效操作，因为cDescRespNoSend会TpTxStart()被清除
{
    INT8U DescNrcTime = DescNrcNoRsp;

    if(wDescP4Timer > 0)//诊断计时器
    {
        wDescP4Timer -- ;
    }

    if((wDescP4Timer == 0) && /*(TpRxState.engine == kRxState_ApplInformed) && */(cDescRespNoSend)\
    && (Desc_OpTimeLongerThanP2Flag == FALSE))
    {
#if 1 /*20230619*/
        if(Srvl_IsMemDiagDTCIndex(Appdesc_engCurrEEPOpDataID) == FALSE)
        {
            /* P4 Timer Time Out, You must send out Response within P4 timer time out */
            cDescRespNoSend = FALSE;
            Appdesc_u1gClrDTCNeedRspFlg = FALSE;
            TpRxState.engine = kRxState_Idle;
            TpTxState.engine = kTxState_Idle;
            DescNrcTime = DescNrcNoRsp;
        }
        else if(DescRoutineCtrl_GetRecoverDefaultFlag() == TRUE)
        {
            cDescRespNoSend = FALSE;
            TpRxState.engine = kRxState_Idle;
            TpTxState.engine = kTxState_Idle;
            DescNrcTime = DescNrcNoRsp;
            DescRoutineCtrl_SetRecoverDefaultFlag(FALSE);
        }
        else
#endif          
        {
       
            if(u1gP2ExCntr == 0x00)
            {
                Desc_OpTimeLongerThanP2Flag = FALSE;
                u1gP2ExCntr = Desc_mgClrDTC_P2ExTIMES;//14服务有两次回复78的机会
            }
            else
            {
                wDescP4Timer = DESC_RspPendingTM;
                TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
                DescNrcTime = kDescNrcResponsePending;	//服务器正忙，暂时无法处理当前请求
                cDescRespNoSend = TRUE;//only 0x78 rsp is send,the real rsp is not sent.
                u1gP2ExCntr--;
            }
        }

    }
    else if( (wDescP4Timer == 0) && /*(TpRxState.engine == kRxState_ApplInformed) && */(cDescRespNoSend)\
    && (Desc_OpTimeLongerThanP2Flag == TRUE) )
    {
#if 1 /*20230619*/
        if(Srvl_IsMemDiagDTCIndex(Appdesc_engCurrEEPOpDataID) == FALSE) 
        {
            wDescP4Timer = DESC_P2EX_CAN_SERVER_MAX; //普通的EEPROM操作，回应78负响应码后需在此时间段内回复
        }
        else if(DescRoutineCtrl_GetRecoverDefaultFlag() == TRUE)
        {
                wDescP4Timer = DESC_P2EX_CAN_SERVER_MAX; //普通的EEPROM操作，回应78负响应码后需在此时间段内回复
        }
        else
        {
            wDescP4Timer = DESC_RspPendingTM; //DTC操作，回应78负响应码后需在此时间段内回复
        }
 #endif         
        TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
        DescNrcTime = kDescNrcResponsePending;
        Desc_OpTimeLongerThanP2Flag = FALSE;
        cDescRespNoSend = TRUE; //only 0x78 rsp is send,the real rsp is not sent.发送78后还没回复响应
       
    }
	
    if(DescNrcOK < DescNrcTime)
    {
        DescSendNegResp(DescNrcTime);
    }
    if(DescNrcNoRsp != DescNrcTime)
    {
        TpTxStart();
    }
}

/********************************************************************
* 函数名称：DescTask
* 功能描述：诊断任务
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescTask(void)
{
    INT8U cIndex;//,*pu1Tmp;
    INT8U cServiceFound = FALSE;
    eSID_TYPE eReqSID;
    INT8U u8Length = 0;
		
    if(cDescSessionChangedFlag)//诊断服务层是否改变
    {
        cDescSessionChangedFlag = FALSE;
        Desc_stsSecLvl.CurrLvl = Desc_enmSecNonLvl;
        Desc_stsSecLvl.PreLvl = Desc_enmSecNonLvl;
        AppDescSessionChanged(cDescPrevSession, cDescSession);
//		SetAPPCommDisable(FALSE);
    }
	
    if(cDescTimer100ms > 0)
    {
        cDescTimer100ms --;
    }
    if(cDescTimer100ms == 0)
    {
        cDescTimer100ms = DESC_TIMER_100MS;
        if(cDescTesterPresentTimer > 0)
        {
            cDescTesterPresentTimer  --;
            u1gTesterPrsntFlg = TRUE;
        }
        if(cDescTesterPresentTimer == 0)//3E服务计时到，5s
        {
            /* Tester present time out */
            unlockStatus = FALSE;
            bSeedReceive = FALSE;
            u1gTesterPrsntFlg = FALSE;
            if(cDescSession != SESN_DS)
            {
                /* Sub service function not support */
                AppDescSessionChanged(cDescSession, SESN_DS);
                cDescSession = SESN_DS;
            }
        }
        else
        {
        }
        
    }

#if 1	 /*20230921   未增加该功能*/
	/*查询复位请求是否有效*/
    if(DescECUResetReq.cDescECUHardRestReq == TRUE)
    {
//        if((IsE2promIDLE() == FALSE) && (DiagResetWaitFlag==FALSE)) /*无存储操作*/
        {
            if(DescECUResetReq.cDescECUHardRestAnswerfg == TRUE) /*需要诊断回复完毕的情况*/
            {
                if(DescECUResetReq.cDescECUHardRestAnswerFnish == TRUE)
                {
                    DescECUResetReq.cDescECUHardRestReq = FALSE;
                    ecual_FeedDog();
                    CPU_ECUSoftwareReset();
                }
            }
            else
            {
            	ecual_FeedDog();
            	CPU_ECUSoftwareReset();
            }
        }
    }
#endif
	
    if(TpRxState.engine == kRxState_CanFrameReceived)//是否接收到CAN信息
    {
    	//Srvl_Pwr_UpdateForceIntoSleepTs();//收到诊断命令重新刷新强制进入休眠的时间 2021.3.13   20230921屏蔽
        cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;  /*modify for diagnostic 20101117*/
        /* There is a CAN Request Msg received */
        TpRxState.engine = kRxState_ApplInformed;

        eReqSID = (eSID_TYPE)TpRxInfoStruct.cDataBuf[0];
        DescNrc = DescNrcNoRsp;
        DescSuppressPosRspBit = FALSE;
        for(cIndex = 0; cIndex < UBOUND(pDescHandlerTbl); cIndex ++)
        {
            if((pDescHandlerTbl[cIndex].eSID == eReqSID) && (NULL != pDescHandlerTbl[cIndex].pServerProcess))
            {
				/* Service Found */
				if((eSID_TESTER_PRESENT != eReqSID) || \
				((eSID_TESTER_PRESENT == eReqSID) && (TpRxInfoStruct.cDataBuf[1] == 0x00)))
				{     
					if(TRUE == Appdesc_u1gClrDTCNeedRspFlg)
					{
						/*当正在清除DTC时，Appdesc_u1gClrDTCNeedRspFlg和Desc_OpTimeLongerThanP2Flag不能置False*/
					}
					else
					{
						Desc_OpTimeLongerThanP2Flag = FALSE;
						wDescP4Timer = DESC_P2_CAN_SERVER_TIME;
					}
                                    
				}
				cServiceFound = TRUE;
				cDescRespNoSend = TRUE;
				TpTxInfoStruct.cDataBuf[0] = eReqSID + 0X40;
				/* Service Format is ok */
				TpTxInfoStruct.cDataBuf[1] = TpRxInfoStruct.cDataBuf[1]; /* Positive Response Sub Function ID */
				TpTxInfoStruct.cDataBuf[2] = TpRxInfoStruct.cDataBuf[2]; /* Positive Response Sub Function ID */

				if(eReqSID == eSID_ROUTINE_CONTROL || eReqSID == eSID_WRITE_DATA_BY_IDENTIFIER || eReqSID == eSID_CLR_DIAGNOSTIC_DTC||eReqSID == eSID_READ_DATA_BY_IDENTIFIER)
				{
					Desc_stgLngTmRspInfo.u1RspSID = eReqSID + 0X40;
					Desc_stgLngTmRspInfo.u1DID0 = TpRxInfoStruct.cDataBuf[1];
					Desc_stgLngTmRspInfo.u1DID1 = TpRxInfoStruct.cDataBuf[2];
					//TpTxInfoStruct.wDataLength = 3;
				}
				
				pDescHandlerTbl[cIndex].pServerProcess();
				break;
            }
        }
		
        if(cServiceFound == FALSE)
        {
          //  Appdesc_u1gClrDTCNeedRspFlg = FALSE;  /*20230919  未加EEPROM*/ 
            Desc_OpTimeLongerThanP2Flag = FALSE;
            wDescP4Timer = DESC_P2_CAN_SERVER_TIME;
            /* Service Not Support */
            if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
            {
                TpTxInfoStruct.cDataBuf[0] = TpRxInfoStruct.cDataBuf[0] + 0X40;
                DescNrc = kDescNrcServiceNotSupported;
            }
            else
            {
                TpRxState.engine = kRxState_Idle;
                TpTxState.engine = kTxState_Idle;
                DescNrc = DescNrcNoRsp;
            }
        }
		if(DescNrcNoRsp == DescNrc)
		{
			//Jetty 2022-6-14 解决无需响应情况下响应78 [14/22/2e]的问题
			cDescRespNoSend = FALSE;
		}

		
        if(DescNrcOK < DescNrc)
        {
        	
			/*北汽企标 当请求报文使用功能寻址时，具有 NRC0x11、 NRC0x7F、 NRC0x12、 NRC0x7E、 NRC0x31 否定码的否定响
				应报文，除非已先传输 NRC0x78，否则应不发送。*/
			if(((DescNrc == kDescNrcServiceNotSupported) \
				|| (DescNrc == kDescNrcSubfunctionNotSupported) \
				|| (DescNrc == kDescNrcServiceNotSupportedInActiveSession) \
				|| (DescNrc == kDescNrcSubfunctionNotSupportedInActiveSession) \
				|| (DescNrc == kDescNrcRequestOutOfRange)) \
				&& (TpRxInfoStruct.cCANIDIndex == TST_FunctionalReq))
			{
				DescNrc = DescNrcNoRsp;
			}
			else
			{
            	DescSendNegResp(DescNrc);//设置负响应的数据
			}
        }
		 //有响应 切换会话时马上响应，解决当切10 02时，没有响应78，导致P2超时的问题（原因是在30ms内跳转至boot，但响应的总时间超过了50ms）
        if(DescNrcNoRsp != DescNrc && ((kDescNrcResponsePending != DescNrc) || (eSID_DIAGNOG_SESSION_CONTROL == eReqSID)))
        {
            TpTxStart();//如果有78回复在这处理
            DescNrc = DescNrcNoRsp;
        }
    }
	
    AppLinDescTask();//LIN事件型诊断函数处理
    AppDescTask();
    DescTimeManage();//诊断时间管理
    UdsApp_2APeriodSchedule();
    AppDescPinAttackProcess();
    Uds_AccessTimesClean();
    RecoverDefaultFlagFunction();/*需要在10ms任务执行周期内*/
    ClearDiagConfigChangeFlagFunction();/*需要在10ms任务执行周期内*/
}

/********************************************************************
* 函数名称：DescSendNegResp
* 功能描述：诊断发送消极响应
* 入口参数：消极响应的代码
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescSendNegResp(INT8U  cRespCode)
{
    TpTxInfoStruct.cDataBuf[1] = TpTxInfoStruct.cDataBuf[0] - 0x40;
    TpTxInfoStruct.cDataBuf[0] = DESC_NEGATIVE_RESPONSE_SERVICE_ID;
    TpTxInfoStruct.cDataBuf[2] = cRespCode;
    TpTxInfoStruct.wDataLength = 3;
}

/***********************************************************************************************
 * @function name: static void DescChangeToProSectionReset
 * @description: EEPROM 写入结果回调处理函数，根据写入结果判断是否发起 ECU 硬复位或返回负响应
 * @input parameters: enE2promOptResult WriteResult —— EEPROM 写入结果
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
static void DescChangeToProSectionReset(enE2promOptResult WriteResult)
{
	if(E2promOpOK == WriteResult)
	{
		DescECUResetReq.cDescECUHardRestReq = TRUE;
		DescECUResetReq.cDescECUHardRestAnswerfg = FALSE;
		DescECUResetReq.cDescECUHardRestAnswerFnish = FALSE; /*回复完成之后复位*/
	}
	else
	{
		DescNrc = kDescNrcTransferAborted; //0x72
		DescSendNegResp(DescNrc); // 设置负响应的数据
		TpTxStart();
	}
}

/********************************************************************
* 函数名称：DescDiagnosticSessionControl
* 功能描述：诊断服务层控制
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescDiagnosticSessionControl(void)
{
    INT8U wIndex;
    INT8U cTempDescSession;
    INT8U cSessionFound = FALSE;
    const INT16U P2ServerMax = (INT16U)(DESC_P2_CAN_SERVER_MAX * CANDRVCYCTIME);
    const INT16U P2_ServerMax = (INT16U)((DESC_P2EX_CAN_SERVER_MAX * CANDRVCYCTIME/10));
	BOOL tSpdCond = FALSE, tEngineCond = FALSE;
	INT8U u8Temp = 0;
	INT16U u16Speed = 0;

    unlockStatus = FALSE;
    bSeedReceive = FALSE;
	cTempDescSession =  (TpRxInfoStruct.cDataBuf[1] & 0x7f);
	
	if (2 != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	

	for(wIndex = 0; wIndex < UBOUND(cDescDiagnosticSession); wIndex++)
	{
		if(cDescDiagnosticSession[wIndex] == cTempDescSession)
		{
			/*  Session Found */
			cSessionFound = TRUE;
		}
	}
	
	if(FALSE == cSessionFound)
	{
		DescNrc = kDescNrcSubfunctionNotSupported;
		return;
	}
	
    cTempDescSession =  SessionConverGet(TpRxInfoStruct.cDataBuf[1] & 0x7f);
    if (SESN_PRGS == cTempDescSession)
    {
       
		//非正常电压和速度大于4不给使用, 当前是扩展会话层
		if((SESN_EXTDS != cDescSession))
		{
			DescNrc = kDescNrcSubfunctionNotSupportedInActiveSession; //NRC7E
			return;
		}
		 if((DescCheckVehSpd() == FALSE) || \
			(Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT))
        {
            // 检查并满足编程条件才允许切换至编程会话层
            DescNrc = kDescNrcConditionsNotCorrect;//NRC22
            return;
        }
    }

    if(cDescSession != cTempDescSession)
    {
        cDescSessionChangedFlag = TRUE;
        cDescPrevSession = cDescSession;
        cDescSession = cTempDescSession;
    }
    else
    {
        /* Session Not Change */
    }
    
	if((TpRxInfoStruct.cDataBuf[1] & 0x80) == 0u)
	{
		/*切换到编程进程,回复完成后复位*/
		if(SESN_PRGS == cTempDescSession)
		{
			if( (tSpdCond == TRUE) || (tEngineCond == TRUE))
			{
				DescNrc = (kDescNrcConditionsNotCorrect);
				return;
			}
			u8Temp = D_DIAG_NeedUpdateSort_NeedReply;
			Srvl_SetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg, u8Temp);
			Srvl_E2SetE2WritePollingIndex(EN_MemIndex_AppJumpToBootFlg);
			DescCheckE2promResult.CheckWriteE2promFlg[enCheckFromAppJumpToBootFlg_Idx] = TRUE;
			DescCheckE2promResult.WriteE2promRespProcess[enCheckFromAppJumpToBootFlg_Idx] = DescChangeToProSectionReset;
			DescNrc = kDescNrcResponsePending;
		}
		else
		{
			setRoutine0203Sts(FALSE);
			TpTxInfoStruct.cDataBuf[1] = TpRxInfoStruct.cDataBuf[1];
			TpTxInfoStruct.cDataBuf[2] = (INT8U)(P2ServerMax >> 8U);
			TpTxInfoStruct.cDataBuf[3] = (INT8U)P2ServerMax;
			TpTxInfoStruct.cDataBuf[4] = (INT8U)(P2_ServerMax >> 8U);
			TpTxInfoStruct.cDataBuf[5] = (INT8U)(P2_ServerMax % 256U);
			TpTxInfoStruct.wDataLength = 6;
			DescNrc = DescNrcOK;

		}
	}
	else
	{
		/* Don't Send Response, But you need to Reset TpRx and TpTx State to Idle state in order to
		receive next request service */
		TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		//TpTxState.engine = kTxState_Idle;
		
		/*切换到编程进程,复位*/
		if(SESN_PRGS == cTempDescSession)
		{
			u8Temp = D_DIAG_NeedUpdateSort_NeedReply;
			Srvl_SetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg, u8Temp);
			Srvl_E2SetE2WritePollingIndex(EN_MemIndex_AppJumpToBootFlg);
			DescCheckE2promResult.CheckWriteE2promFlg[enCheckFromAppJumpToBootFlg_Idx] = TRUE;
			DescCheckE2promResult.WriteE2promRespProcess[enCheckFromAppJumpToBootFlg_Idx] = DescChangeToProSectionReset;
			
			DescNrc = kDescNrcResponsePending;
		}
		
	}
    
}


void DescSendPosResp(void)
{
    TpTxStart();
}

/********************************************************************
* 函数名称：DescEcuRest
* 功能描述：诊断复位ECU
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescEcuRest(void)
{
	BOOL tSpdCond = FALSE;
	INT16U u16Speed = 0;
	if(2U != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	if(DescCheckVehSpd() == FALSE || DescGetSeatMoveStatusFlg() == TRUE)//车速大于3km/h | 有座椅处于控制状态
	{
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}

	if(((TpRxInfoStruct.cDataBuf[1] & 0x7FU) == DESC_ECU_HARD_REST) ||
	((TpRxInfoStruct.cDataBuf[1] & 0x7FU) == DESC_ECU_SOFT_REST))
	{
		if(DescSessionSA_CfgChk(eSID_ECU_HARD_RESET_INDEX))
		{
			return;
		}

		if(TpRxInfoStruct.cDataBuf[1] & 0x80)
		{
			if(IsE2promBusy() == FALSE) /*20230919*/
			{
				CPU_ECUSoftwareReset();//直接复位，不肯定响应
			}
			else
			{
				DescNrc = (kDescNrcConditionsNotCorrect);
			}
            TpRxState.engine = kRxState_Idle;
            TpTxState.engine = kTxState_Idle;
            DescNrc = DescNrcNoRsp;
		}
		else
		{
			if(IsE2promBusy() == FALSE)
			{
				/* Hard Reset ECU */
				TpTxInfoStruct.wDataLength = 2;
				DescNrc = DescNrcOK;
				DescECUResetReq.cDescECUHardRestAnswerfg = TRUE;
				DescECUResetReq.cDescECUHardRestReq = TRUE;
			}
			else
			{
				DiagResetWaitFlag = TRUE;
				DescNrc = kDescNrcResponsePending;
//				Ecual_SetEEPROMCheckFlag(1);
				Desc_stgLngTmRspInfo.u1RspSID = 0x51;
				Desc_stgLngTmRspInfo.u1DID0 = TpRxInfoStruct.cDataBuf[1];
				DescRepeatRes = D_HAL_GET_CUR_MS_TS();
			}
		}
	}
	else
	{
		/* Sub Service Function Not Support */
		if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
		{
			DescNrc = (kDescNrcSubfunctionNotSupported);
		}
	}
}

/********************************************************************
* 函数名称：DescTesterPresent
* 功能描述：3E服务
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescTesterPresent(void)
{
    if(2U != TpRxInfoStruct.wDataLength)
    {
        DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
        return;
    }
    if(DESC_TESTER_PRESENT_ZERO_SUB_FUNC == (TpRxInfoStruct.cDataBuf[1] & 0x7FU))
    {
        cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
        cDescTimer100ms = DESC_TIMER_100MS;
        if(TpRxInfoStruct.cDataBuf[1] == DESC_TESTER_PRESENT_ZERO_SUB_FUNC)
        {
            TpTxInfoStruct.wDataLength = 2;
            DescNrc = DescNrcOK;
#if 0 /*20230919  未加EEPROM*/             
            if(Appdesc_engCurrEEPOpDataID < EN_MemIndex_Max)
            {
                cDescRespNoSend = TRUE;
            }
            else
            {
                cDescRespNoSend = FALSE;
            }
#endif            
        }
        else//禁止肯定响应
        {
            /* Don't Send Response, But you need to Reset TpRx and TpTx State to Idle state in order to
            receive next request service */
#if 0 /*20230919  未加EEPROM*/           
            if(Appdesc_engCurrEEPOpDataID < EN_MemIndex_Max)
            {
                cDescRespNoSend = TRUE;
            }
            else
            {
                cDescRespNoSend = FALSE;
            }
#endif            
            TpRxState.engine = kRxState_Idle;
            TpTxState.engine = kTxState_Idle;
            DescNrc = DescNrcNoRsp;
        }
    }
    else
    {
        /* Sub Service Function Not Support */
        if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
        {
            DescNrc = kDescNrcSubfunctionNotSupported;
        }
    }
}


/***********************************************************************************************
 * @function name:  DescCheckVehSpd(void)
 *
 * @description:	车速条件检查
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         BOOL 车速大于3km/h且车速有效，返回FALSE,否则返回TRUE
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-07
 ***********************************************************************************************/
BOOL DescCheckVehSpd(void)
{
	if(((CanRx_0x284_ABS_VehicleSpeed() * 0.01 ) >= DescVehSpdLimit) && (CanRx_0x284_ABS_VehicleSpeedValid() == 0))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	return TRUE;
}
/***********************************************************************************************
 * @function name:  DescGetcDescSession(void)
 * @description:	会话模式
 * @input parameters:     void
 * @output parameters:     void
 * @return:         会话模式
 * @note:           无
 * @author:          zjx
 * @note:           2023-04-07
 ***********************************************************************************************/
INT8U DescGetcDescSession(void)
{
	return cDescSession;
}


/***********************************************************************************************
 * @function name:  DescGetSeatMoveStatusFlg
 *
 * @description:	获取座椅在运动状态标志
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         fla  FALSE:没有座椅在动；TRUE：有座椅初于运动状态
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-06-01
 ***********************************************************************************************/

BOOL DescGetSeatMoveStatusFlg(void)
{
	BOOL fla = FALSE;
#if 1 /*20230919  未使用该功能*/
	if( (Rte_GetVfb_DrHeightMotorCmd() != NULL) || \
		(Rte_GetVfb_DrLengthMotorCmd() != NULL) || \
		(Rte_GetVfb_DrBackMotorCmd() != NULL) || \
		(Rte_GetVfb_DrFrontMotorCmd() != NULL) || \
		(Rte_GetVfb_PaLengthMotorCmd() != NULL) || \
		(Rte_GetVfb_PaBackMotorCmd() != NULL))
	{
		fla = TRUE;
	}
#endif
	return fla;
}


/********************************************************************
* 函数名称：DescCANTest
* 功能描述：CAN通信测试
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescCANTest(void)
{
    INT8U cIndex;
    INT8U cDataLen;
    cDataLen = (INT8U)(TpRxInfoStruct.wDataLength - 2);
    if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
    {
        if(cDescSession != SESN_PRGS)
        {
            if((TpRxInfoStruct.wDataLength > CANTestRequestMINLength) && (TpRxInfoStruct.wDataLength < CANTestRequestMAXLength))
            {
                for(cIndex = 0; cIndex < cDataLen; cIndex++)
                {
                    TpTxInfoStruct.cDataBuf[2 + cIndex] = TpRxInfoStruct.cDataBuf[2 + cIndex];
                }
                TpTxInfoStruct.wDataLength = TpRxInfoStruct.wDataLength;
                DescNrc = DescNrcOK;
            }
            else
            {
                /* Invalid Service Request Length */
                DescNrc = (kDescNrcIncorrectMessageLengthOrInvalidFormat);
            }
        }
        else
        {
            DescNrc = (kDescNrcServiceNotSupportedInActiveSession);
        }
    }
    else
    {
    }
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


