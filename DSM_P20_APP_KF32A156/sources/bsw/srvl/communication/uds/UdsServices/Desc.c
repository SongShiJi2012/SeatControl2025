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
* �������ƣ�DescInit
* ������������ϳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ���� 
* ��    ע: ��
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
   // Diag_setReserFlg(TRUE);  /*20230919 ���ø�λ��־*/
}

/********************************************************************
* �������ƣ�SessionConverGet
* ����������ֵת��Ϊ��Ӧ�ķ����
* ��ڲ�����SenssionType�����������
* ���ڲ�������
* �� �� ֵ��������Ӧ�ķ���� 
* ��    ע: ��
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
* �������ƣ�SessionSA_CfgChk
* ����������Session��SA ���ü��
* ��ڲ�����SenssionTypeIndex�����������
* ���ڲ�������
* �� �� ֵ��
* ��    ע: ��
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
			RetVal = TRUE;//�ûỰ�㲻֧��
			DescNrc = kDescNrcServiceNotSupportedInActiveSession;
		}
		else if(SA_NULL != pDescSessSAConfigTbl[SenssionTypeIndex].PhySessionSACfg.SA_Allow)
		{
			if(unlockStatus == FALSE)//��ȫ����û��ͨ��
			{
				RetVal = TRUE;//���ʽ�ֹ
				DescNrc = kDescNrcAccessDenied;
			}
		}
	}
	else if(TpRxInfoStruct.cCANIDIndex == TST_FunctionalReq)
	{
		if(!(pDescSessSAConfigTbl[SenssionTypeIndex].FucSessionSACfg.SessionAllow & cDescSession))
		{
			/*JMCҪ����Ѱַʱ,����֧�ִ˷���ʱ����ظ�����Ӧ*/
			RetVal = TRUE; 
			//DescNrc = kDescNrcServiceNotSupportedInActiveSession;
		}
	}
	return RetVal;
}


/********************************************************************
* �������ƣ�DescTimeManage
* �������������ʱ�����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescTimeManage(void)//��ͨ�ķ�EEPROM����ϲ���ִ�иú�������Ч��������ΪcDescRespNoSend��TpTxStart()�����
{
    INT8U DescNrcTime = DescNrcNoRsp;

    if(wDescP4Timer > 0)//��ϼ�ʱ��
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
                u1gP2ExCntr = Desc_mgClrDTC_P2ExTIMES;//14���������λظ�78�Ļ���
            }
            else
            {
                wDescP4Timer = DESC_RspPendingTM;
                TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
                DescNrcTime = kDescNrcResponsePending;	//��������æ����ʱ�޷�����ǰ����
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
            wDescP4Timer = DESC_P2EX_CAN_SERVER_MAX; //��ͨ��EEPROM��������Ӧ78����Ӧ������ڴ�ʱ����ڻظ�
        }
        else if(DescRoutineCtrl_GetRecoverDefaultFlag() == TRUE)
        {
                wDescP4Timer = DESC_P2EX_CAN_SERVER_MAX; //��ͨ��EEPROM��������Ӧ78����Ӧ������ڴ�ʱ����ڻظ�
        }
        else
        {
            wDescP4Timer = DESC_RspPendingTM; //DTC��������Ӧ78����Ӧ������ڴ�ʱ����ڻظ�
        }
 #endif         
        TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
        DescNrcTime = kDescNrcResponsePending;
        Desc_OpTimeLongerThanP2Flag = FALSE;
        cDescRespNoSend = TRUE; //only 0x78 rsp is send,the real rsp is not sent.����78��û�ظ���Ӧ
       
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
* �������ƣ�DescTask
* �����������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescTask(void)
{
    INT8U cIndex;//,*pu1Tmp;
    INT8U cServiceFound = FALSE;
    eSID_TYPE eReqSID;
    INT8U u8Length = 0;
		
    if(cDescSessionChangedFlag)//��Ϸ�����Ƿ�ı�
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
        if(cDescTesterPresentTimer == 0)//3E�����ʱ����5s
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

#if 1	 /*20230921   δ���Ӹù���*/
	/*��ѯ��λ�����Ƿ���Ч*/
    if(DescECUResetReq.cDescECUHardRestReq == TRUE)
    {
//        if((IsE2promIDLE() == FALSE) && (DiagResetWaitFlag==FALSE)) /*�޴洢����*/
        {
            if(DescECUResetReq.cDescECUHardRestAnswerfg == TRUE) /*��Ҫ��ϻظ���ϵ����*/
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
	
    if(TpRxState.engine == kRxState_CanFrameReceived)//�Ƿ���յ�CAN��Ϣ
    {
    	//Srvl_Pwr_UpdateForceIntoSleepTs();//�յ������������ˢ��ǿ�ƽ������ߵ�ʱ�� 2021.3.13   20230921����
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
						/*���������DTCʱ��Appdesc_u1gClrDTCNeedRspFlg��Desc_OpTimeLongerThanP2Flag������False*/
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
          //  Appdesc_u1gClrDTCNeedRspFlg = FALSE;  /*20230919  δ��EEPROM*/ 
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
			//Jetty 2022-6-14 ���������Ӧ�������Ӧ78 [14/22/2e]������
			cDescRespNoSend = FALSE;
		}

		
        if(DescNrcOK < DescNrc)
        {
        	
			/*������� ��������ʹ�ù���Ѱַʱ������ NRC0x11�� NRC0x7F�� NRC0x12�� NRC0x7E�� NRC0x31 ����ķ���
				Ӧ���ģ��������ȴ��� NRC0x78������Ӧ�����͡�*/
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
            	DescSendNegResp(DescNrc);//���ø���Ӧ������
			}
        }
		 //����Ӧ �л��Ựʱ������Ӧ���������10 02ʱ��û����Ӧ78������P2��ʱ�����⣨ԭ������30ms����ת��boot������Ӧ����ʱ�䳬����50ms��
        if(DescNrcNoRsp != DescNrc && ((kDescNrcResponsePending != DescNrc) || (eSID_DIAGNOG_SESSION_CONTROL == eReqSID)))
        {
            TpTxStart();//�����78�ظ����⴦��
            DescNrc = DescNrcNoRsp;
        }
    }
	
    AppLinDescTask();//LIN�¼�����Ϻ�������
    AppDescTask();
    DescTimeManage();//���ʱ�����
    UdsApp_2APeriodSchedule();
    AppDescPinAttackProcess();
    Uds_AccessTimesClean();
    RecoverDefaultFlagFunction();/*��Ҫ��10ms����ִ��������*/
    ClearDiagConfigChangeFlagFunction();/*��Ҫ��10ms����ִ��������*/
}

/********************************************************************
* �������ƣ�DescSendNegResp
* ������������Ϸ���������Ӧ
* ��ڲ�����������Ӧ�Ĵ���
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
 * @description: EEPROM д�����ص�������������д�����ж��Ƿ��� ECU Ӳ��λ�򷵻ظ���Ӧ
 * @input parameters: enE2promOptResult WriteResult ���� EEPROM д����
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
static void DescChangeToProSectionReset(enE2promOptResult WriteResult)
{
	if(E2promOpOK == WriteResult)
	{
		DescECUResetReq.cDescECUHardRestReq = TRUE;
		DescECUResetReq.cDescECUHardRestAnswerfg = FALSE;
		DescECUResetReq.cDescECUHardRestAnswerFnish = FALSE; /*�ظ����֮��λ*/
	}
	else
	{
		DescNrc = kDescNrcTransferAborted; //0x72
		DescSendNegResp(DescNrc); // ���ø���Ӧ������
		TpTxStart();
	}
}

/********************************************************************
* �������ƣ�DescDiagnosticSessionControl
* ������������Ϸ�������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
       
		//��������ѹ���ٶȴ���4����ʹ��, ��ǰ����չ�Ự��
		if((SESN_EXTDS != cDescSession))
		{
			DescNrc = kDescNrcSubfunctionNotSupportedInActiveSession; //NRC7E
			return;
		}
		 if((DescCheckVehSpd() == FALSE) || \
			(Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT))
        {
            // ��鲢�����������������л�����̻Ự��
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
		/*�л�����̽���,�ظ���ɺ�λ*/
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
		
		/*�л�����̽���,��λ*/
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
* �������ƣ�DescEcuRest
* ������������ϸ�λECU
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
	if(DescCheckVehSpd() == FALSE || DescGetSeatMoveStatusFlg() == TRUE)//���ٴ���3km/h | �����δ��ڿ���״̬
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
				CPU_ECUSoftwareReset();//ֱ�Ӹ�λ�����϶���Ӧ
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
* �������ƣ�DescTesterPresent
* ����������3E����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
#if 0 /*20230919  δ��EEPROM*/             
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
        else//��ֹ�϶���Ӧ
        {
            /* Don't Send Response, But you need to Reset TpRx and TpTx State to Idle state in order to
            receive next request service */
#if 0 /*20230919  δ��EEPROM*/           
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
 * @description:	�����������
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         BOOL ���ٴ���3km/h�ҳ�����Ч������FALSE,���򷵻�TRUE
 *
 * @note:           ��
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
 * @description:	�Ựģʽ
 * @input parameters:     void
 * @output parameters:     void
 * @return:         �Ựģʽ
 * @note:           ��
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
 * @description:	��ȡ�������˶�״̬��־
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         fla  FALSE:û�������ڶ���TRUE�������γ����˶�״̬
 *
 * @note:           ��
 *
 * @author:          zjx
 *
 * @note:           2023-06-01
 ***********************************************************************************************/

BOOL DescGetSeatMoveStatusFlg(void)
{
	BOOL fla = FALSE;
#if 1 /*20230919  δʹ�øù���*/
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
* �������ƣ�DescCANTest
* ����������CANͨ�Ų���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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


