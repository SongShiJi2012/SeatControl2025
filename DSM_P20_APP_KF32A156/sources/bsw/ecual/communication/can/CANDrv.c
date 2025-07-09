/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "CANDrv.h"
#include "kf32a156_int.h"
#include "CANDrvMSCAN.h"
#include "DescConfig.h"
#include "DSM.h"
//#include "NM.h"
#include "OsekNm_Cfg.h"
#include "OsekNm.h"
#define		CANDrv_DisableInterrupts 	INT_SYS_DisableIRQGlobal()
#define		CANDrv_EnableInterrupts		INT_SYS_EnableIRQGlobal()

tCANDRV_PEMSG_OPT CANDrvPEMsgOpt;
tCANDRV_EMSG_OPT  CANDrvEMsgOpt;
volatile INT16U cMsgNeedTxIndFlag;
tCOMCTRL_OPT      ComCtrlOpt;
tCOMCTRL_OPT      DescComCtrlOpt;		//ͨ��$28�������õ�ֵ

INT8U Buffer_6E0_C[8];
INT8U Buffer_6E1_C[8];
static unCANMsgFlag CanStateFlags[CANMSG_FLAG_MAX];
static INT32U CanMsgRxTimer[eRXINDEX_MAX];
volatile BOOL FirstRFWakeupFlg;
/* CAN������Ϣ �¼����� - P20���¼����ͱ��� ��ʱ��������ؽӿ�*/
const CANTxEMsgInfo CANMsg_EMsgTbl[] =
{
    { {FLEXCAN_MSG_ID_STD,	0x6E0,	8,	(INT8U*)&Buffer_6E0_C},	MSG_CYCLE_20MS,	1},
    { {FLEXCAN_MSG_ID_STD,	0x6E1,	8,	(INT8U*)&Buffer_6E1_C},	MSG_CYCLE_20MS,	1},
};
static BOOL s_CAN_ACK_Err_Tx_Enable = TRUE;
static BOOL s_CAN_ACK_Err = FALSE;

static BOOL s_CANDrv_UdsMsgRecFlg = FALSE;//��ϱ��Ľ��ձ�־
static INT32U s_CANDrv_UdsMsgRecTime = 0;//��ϱ��Ľ��ձ�־
/***********************************************************************
 * @function name: Ecual_GetCanACKErrSts
 *
 * @description: ��ȡCAN ACK��Ӧ�����״̬
 *
 * @input parameters: void
 *
 * @output parameters: void
 *
 * @return: TRUE:������Ӧ�����  FALSE����
 *
 * @note:
 *
 * @author: Michael Xin
 *
 * @date: 2022-11-02 17:00
 ***********************************************************************/
BOOL Ecual_GetCanACKErrSts(void)
{
	return s_CAN_ACK_Err;
}
BOOL Ecual_GetCANACKErrTxEnable(void)
{
   return s_CAN_ACK_Err_Tx_Enable;
}

void Ecual_SetCANACKErrTxEnable(BOOL t_enable)
{
   s_CAN_ACK_Err_Tx_Enable = t_enable;
}
void CANDrv_TxTimeReset(void)
{
    INT8U  i;

    CANDrvPEMsgOpt.MsgMaxNo = eDSMG_MAX;
    CANDrvPEMsgOpt.NeedSendMask = 0;

    for(i = 0; i < UBOUND(CANDrvPEMsgOpt.pMsgInfoTbl); i++)
    {
        CANDrvPEMsgOpt.pMsgInfoTbl[i].SndCycTimer = MSG_CYCLE_100MS + (i*4);
        CANDrvPEMsgOpt.pMsgInfoTbl[i].SndTimes = 0;
    }

}
/*************************************************************
* �������ƣ�CANIL_vosEMsgInit
* �����������¼�����Ϣ��ʼ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANIL_vosEMsgInit(eEMSG_INDEX eIndex)
{
	switch(eIndex)
	{

		default:
			break;
	}
}
/*************************************************************
* �������ƣ�CANIL_vosPEMsgInit
* ���������������¼�����Ϣ��ʼ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANIL_vosPEMsgInit(ePEMSG_INDEX eIndex)
{
}
/*************************************************************
* �������ƣ�CANDrvInit
* ����������CAN�������ʼ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvInit(void)
{
	INT8U  i;
	INT_All_Enable(FALSE);//���жϱ����������ʼ�����̽�������жϣ����cMsgNum��cWritePointer���ݲ�һ�µ�����

	CANMsgRxDrv.cMsgNum = 0;
	CANMsgRxDrv.cWritePointer = 0;
	CANMsgRxDrv.cReadPointer = 0;
	CANMsgTxDrv.cMsgNum = 0;
	CANMsgTxDrv.cWritePointer = 0;
	CANMsgTxDrv.cReadPointer = 0;

	cMsgNeedTxIndFlag = 0x0000U;

	CANDrvEMsgOpt.MsgMaxNo = eEMSG_MAX;
	CANDrvEMsgOpt.NeedSendMask = 0;
	CANDrvEMsgOpt.EventSendOverMask = 0;

	INT_All_Enable(TRUE);
#if 1
	CANDrvEMsgOpt.pMsgILInit = CANIL_vosEMsgInit;
	for(i = 0; i < UBOUND(CANDrvEMsgOpt.pMsgInfoTbl); i++)
	{
		CANDrvEMsgOpt.pMsgInfoTbl[i].SndCycTimer = 0;//CANMsg_EMsgTbl[i].EventPeriod;
		CANDrvEMsgOpt.pMsgInfoTbl[i].SndTimes = 0;
	}
#endif

	CANDrvPEMsgOpt.MsgMaxNo = eDSMG_MAX;
	CANDrvPEMsgOpt.NeedSendMask = 0;
	CANDrvPEMsgOpt.pMsgILInit = CANIL_vosPEMsgInit;
	for(i = 0; i < UBOUND(CANDrvPEMsgOpt.pMsgInfoTbl); i++)
	{
//		CANDrvPEMsgOpt.pMsgInfoTbl[i].SndCycTimer = MSG_CYCLE_100MS + (i*4);
		//����1444 ����0x3B2����
		CANDrvPEMsgOpt.pMsgInfoTbl[eDSMG_MAX - i - 1].SndCycTimer = (i*4);
		CANDrvPEMsgOpt.pMsgInfoTbl[i].SndTimes = 0;
	}

}

/*************************************************************
* �������ƣ�CANDrvRxTask
* ����������CAN�������������
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvRxTask(void)
{
	while(CANMsgRxDrv.cMsgNum)
	{
		if(CANMsgRxDrv.cReadPointer >= MAX_CAN_MSG_RX_BUF_SIZE) 
		{
			CANMsgRxDrv.cReadPointer = 0;
		}
		StdMsgRxProcess(CANMsgRxDrv.cReadPointer);
		CANDrv_DisableInterrupts;
		CANMsgRxDrv.cMsgNum --;
		CANMsgRxDrv.cReadPointer ++;
		CANDrv_EnableInterrupts;
	}
}
/***********************************************************************************************
 * @function name: Ecual_CopyDataToRxMsg
 * @description: �����յ��� CAN �������ݴ��������������Ƶ�ָ�����ջ������������ý��ձ�־λ
 * @input parameters: INT8U u1tRxMsgIndex - ���ջ�����������INT8U cMsgIndex - �������ջ�������
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-16
 ***********************************************************************************************/
static void Ecual_CopyDataToRxMsg(eRXINDEX u1tRxMsgIndex, INT8U cMsgIndex)
{
	INT8U u1tIdx, *pu1tRxMsgInfo;
	INT8U u1tDLC = CanGetRxDataLen(u1tRxMsgIndex);

	/* ���������ݳ��Ȳ��㣬ֱ�ӷ��� */
	if (CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength < u1tDLC)
	{
		return;
	}

	/* ��ȡ���ջ�����ָ�� */
	pu1tRxMsgInfo = CanGetRxDataPtr(u1tRxMsgIndex);

	/* �жϱ�������ֹ���ݳ�ͻ */
	INT_All_Enable(FALSE);
	memcpy(pu1tRxMsgInfo, CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData, u1tDLC);
	INT_All_Enable(TRUE);

	/* ���ý��ձ�־λ */
	Ecual_SetCanFlag(CANMSG_FLAG_Online, u1tRxMsgIndex, TRUE);
	Ecual_SetCanFlag(CANMSG_FLAG_Update, u1tRxMsgIndex, TRUE);
}

/*************************************************************
* �������ƣ�Ecual_GetNMRxIDAndData
* ������������ȡ�������CAN�ź�
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
static void Ecual_GetNMRxIDAndData(INT8U cMsgIndex, INT32U u1tMsgID)
{
//	INT8U cIndex = 0;
//
//	CanRxActualNmId = u1tMsgID;
//	INT_All_Enable(FALSE);//���жϱ�����- ��Ҫ��©֡���в���
//	for(cIndex = 0; cIndex < 8; cIndex++)
//	{
//		nmRecvMess[cIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[cIndex];
//	}
//	INT_All_Enable(TRUE);
}
/***********************************************************************
 * @function name: Ecual_CanSetUdsMsgReceiveFlg
 * @description: ����can��Ͻ��ձ�־
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: Michael Xin
 * @date: 2025-06-10 17:00
 ***********************************************************************/
static void Ecual_CanSetUdsMsgReceiveFlg(BOOL Flg)
{
    s_CANDrv_UdsMsgRecFlg = Flg;
    s_CANDrv_UdsMsgRecTime = D_HAL_GET_CUR_MS_TS();
}


/*************************************************************
* �������ƣ�StdMsgRxProcess
* ��������������CAN��Ϣ����
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
static void StdMsgRxProcess(INT8U  cMsgIndex)
{
	INT8U cIDIndex;
	INT32U u2tCurMsgID;
    
	CANWakeupFlg = TRUE; //���յ�CAN����
	
	u2tCurMsgID = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cCANID;
	/*Ӧ�ñ���*/
	if(TRUE == ComCtrlOpt.NormalComMsg.Bits.RxEnable)
	{
		for(cIDIndex = 0; cIDIndex < eRXINDEX_MAX; cIDIndex ++)
		{
			if(CanGetRxId(cIDIndex) == u2tCurMsgID)
			{
				Ecual_CopyDataToRxMsg(cIDIndex, cMsgIndex);
				return;
			}
		}
	}
	/*��ϱ���*/
	if(u2tCurMsgID == DESC_REQID_PHY)
	{
		TPRxProcess(cMsgIndex, TST_PhysicalReq);
        Ecual_CanSetUdsMsgReceiveFlg(TRUE);
		return;
	}
	else if(u2tCurMsgID == DESC_REQID_FUC)
	{
		TPRxProcess(cMsgIndex, TST_FunctionalReq);
        Ecual_CanSetUdsMsgReceiveFlg(TRUE);
		return;
	}
	/*���������*/
//	if((ComCtrlOpt.NMComMsg.Bits.RxEnable == TRUE) && (DescComCtrlOpt.NMComMsg.Bits.RxEnable == TRUE))
//	{
//		//ֻ�����籨��������ղŽ���
//		if((u2tCurMsgID >= NM_BaseAddr) && (u2tCurMsgID <= NM_EndAddr))
//		{
//			if(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength > 1u)
//			{
//				Ecual_GetNMRxIDAndData(cMsgIndex, u2tCurMsgID);
//				NmPrecopy();
//			}
//		}
//	}
	if((u2tCurMsgID >= D_CAN_NM_BASE_ADDR) && (u2tCurMsgID <= D_CAN_NM_END_ADDR))
	{
		CANMsgRxBase pFrame = CANMsgRxDrv.CANMsgBuf[cMsgIndex];
		Osek_RxIndication(0U, &pFrame);
	}
}
/*************************************************************
* �������ƣ�Ecual_IsTestMessageSendEnable
* �����������Ƿ��Ͳ��Ա���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
static BOOL Ecual_IsTestMessageSendEnable(INT16U u16CanID)
{
	BOOL bRet = TRUE;
	INT16U u16TestCanMsgID1_NodeBcm[] = {0x500, 0x501, 0x502}; /*���Ա���*/
	INT8U i = 0;
	un_TestMessageSendCfg t_testMessageSendCfg = {0};

	Srvl_ReadMemIndexData(EN_MemIndex_TestMessageSendCfg, &t_testMessageSendCfg.byte, D_TestMessageSendCfg_Len_1);
	for(i = 0; i < UBOUND(u16TestCanMsgID1_NodeBcm); i++)
	{
		if((u16CanID == u16TestCanMsgID1_NodeBcm[i]) && ((t_testMessageSendCfg.byte & (1 << i)  ) == 0))
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

/*************************************************************
* �������ƣ�CANDrvEventMsgTxProcess
* �����������¼���CAN�źŷ��ʹ���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvEventMsgTxProcess(void)
{
#if 1
	INT8U cDataLen, cIndex;
	INT16U TmpFlgMask;
	INT8U *pu1tTxMsgInfo;
	INT8U u1tDLC;
	const CANTxBaseInfo* pCANTxMsgInfo;

	if(0 == CANDrvEMsgOpt.NeedSendMask)
	{
		return;
	}
	for(cIndex = 0, TmpFlgMask = 0x01; cIndex < CANDrvEMsgOpt.MsgMaxNo; cIndex++)
	{
		if(MAX_CAN_MSG_TX_BUF_SIZE > CANMsgTxDrv.cMsgNum)
		{
			if(CANDrvEMsgOpt.NeedSendMask & TmpFlgMask)
			{
				CANDrvEMsgOpt.NeedSendMask &= ~TmpFlgMask;
				pCANTxMsgInfo = &CANMsg_EMsgTbl[cIndex].TxBaseInfo;
				if(CANMsgTxDrv.cWritePointer >= MAX_CAN_MSG_TX_BUF_SIZE)
				{
					CANMsgTxDrv.cWritePointer = 0;
				}
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cCANIDIndex = pCANTxMsgInfo->TxID;

				pu1tTxMsgInfo = pCANTxMsgInfo->pTxSrcBuf;
				u1tDLC = pCANTxMsgInfo->TxLen;
				for(cDataLen = 0; cDataLen < u1tDLC; cDataLen ++)
				{
					CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[cDataLen] = *pu1tTxMsgInfo++;
				}
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = pCANTxMsgInfo->IdType;
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cDataLength = u1tDLC;
				CANMsgTxDrv.cWritePointer ++;
				CANMsgTxDrv.cMsgNum ++;
				if(0u != CANDrvEMsgOpt.pMsgInfoTbl[cIndex].SndTimes)
				{
					CANDrvEMsgOpt.pMsgInfoTbl[cIndex].SndTimes--;
				}

				if(0u == CANDrvEMsgOpt.pMsgInfoTbl[cIndex].SndTimes)
				{
					CANDrvEMsgOpt.pMsgILInit(cIndex);
					CANDrvEMsgOpt.EventSendOverMask &= ~TmpFlgMask;
				}
				CANDrvEMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer = CANMsg_EMsgTbl[cIndex].EventPeriod;

			}
			TmpFlgMask <<= 1u;
		}
		else
		{
			break;
		}
	}
#endif
}
/*************************************************************
* �������ƣ�CANDrvPeriodEventMsgTxProcess
* ���������������¼���CAN�źŷ��ʹ���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvPeriodEventMsgTxProcess(void)
{
	INT8U cDataLen, cIndex;
	INT16U TmpFlgMask;
	INT8U *pu1tTxMsgInfo;
	INT8U u1tDLC;
	static INT8U EpFlag[eDSMG_MAX] = {0};

	if(0 == CANDrvPEMsgOpt.NeedSendMask)
	{
		return;
	}

	for(cIndex = 0, TmpFlgMask = 0x01; cIndex < CANDrvPEMsgOpt.MsgMaxNo; cIndex++)
	{
		if(Ecual_IsTestMessageSendEnable(CanGetTxId(cIndex)) == FALSE)
		{
			TmpFlgMask <<= 1u;
			continue;
		}
		if(MAX_CAN_MSG_TX_BUF_SIZE > CANMsgTxDrv.cMsgNum)
		{	
			if((CANDrvPEMsgOpt.NeedSendMask & TmpFlgMask) != 0u)
			{
				CANDrvPEMsgOpt.NeedSendMask &= ~TmpFlgMask;
				if(CANMsgTxDrv.cWritePointer >= MAX_CAN_MSG_TX_BUF_SIZE)
				{
					CANMsgTxDrv.cWritePointer = 0;
				}
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cCANIDIndex = CanGetTxId(cIndex);
				
				pu1tTxMsgInfo = CanGetTxDataPtr(cIndex);
				u1tDLC = CanGetTxDlc(cIndex);
				for(cDataLen = 0; cDataLen < u1tDLC; cDataLen ++)
				{
					CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[cDataLen] = *pu1tTxMsgInfo++;
				}
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;//P20��Ŀֻ�б�׼֡
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cDataLength = u1tDLC;
				CANMsgTxDrv.cWritePointer ++;
				CANMsgTxDrv.cMsgNum ++;

				if(0u != CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndTimes)
				{
					CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndTimes--;
					CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer = IlTxCyclesFastTime[cIndex]/CANDRVCYCTIME - 1;
				}
				else
				{
					CANDrvPEMsgOpt.pMsgILInit((ePEMSG_INDEX)cIndex);
                    CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer = IlTxCyclicCycles[cIndex]/CANDRVCYCTIME - 1;
				}

			}
			TmpFlgMask <<= 1u;
		}
		else
		{
			break;
		}
	}
}

/*************************************************************
* �������ƣ�CANDrvNMTxProcess
* �����������������CAN�źŷ��ʹ���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvNMTxProcess(void)
{
	INT8U cDataLen;

	if(cMsgNeedTxIndFlag & PEPS_NM_MSG_NEED_TX_FLAG_MASK)
	{
		if(CANMsgTxDrv.cMsgNum < MAX_CAN_MSG_TX_BUF_SIZE)
		{
			cMsgNeedTxIndFlag &= ~ PEPS_NM_MSG_NEED_TX_FLAG_MASK;
			if(CANMsgTxDrv.cWritePointer >= MAX_CAN_MSG_TX_BUF_SIZE)
			{
				CANMsgTxDrv.cWritePointer = 0;
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cCANIDIndex = NM_CANID;
			for(cDataLen = 0; cDataLen < NM_DLC; cDataLen ++)
			{
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[cDataLen] = nmSendMess[cDataLen];
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cDataLength = NM_DLC;
			CANMsgTxDrv.cWritePointer ++;
			CANMsgTxDrv.cMsgNum ++;
		}
	}
}
/*************************************************************
* �������ƣ�CANDrvDescPhysicalRespTxProcess
* �����������������Ѱַ��Ӧ���ʹ���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvDescPhysicalRespTxProcess(void)
{
	INT8U cDataLen;
	if(cMsgNeedTxIndFlag & TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK)
	{
		/* TST_PhysicalResp msg need to be transmited */
		if(CANMsgTxDrv.cMsgNum < MAX_CAN_MSG_TX_BUF_SIZE)
		{
			cMsgNeedTxIndFlag &= ~ TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
			if(CANMsgTxDrv.cWritePointer >= MAX_CAN_MSG_TX_BUF_SIZE)
			{
				CANMsgTxDrv.cWritePointer = 0;
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cCANIDIndex = DESC_RSPID;
			for(cDataLen = 0; cDataLen < 8; cDataLen ++)
			{
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[cDataLen] = cTpTxBuf[cDataLen];
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cDataLength = 8;
            CANMsgTxDrv.cWritePointer ++;//ͬ��46DB�޸�1101��λ����Ӧ����
            CANMsgTxDrv.cMsgNum ++;
            if((DescECUResetReq.cDescECUHardRestAnswerfg) && (DescECUResetReq.cDescECUHardRestReq))
			{
            	DescECUResetReq.cDescECUHardRestAnswerfg = FALSE;
				cDescECUHardRestAnswerIndex = CANMsgTxDrv.cWritePointer;
                if(cDescECUHardRestAnswerIndex >= MAX_CAN_MSG_TX_BUF_SIZE)
                {
                    cDescECUHardRestAnswerIndex = 0;
                }
			}
		}
	}
}

/*************************************************************
* �������ƣ�CANDrvDescPhysicalRespFlowControlTxProcess
* �����������������Ѱַ��Ӧ���ط��ʹ���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void CANDrvDescPhysicalRespFlowControlTxProcess(void)
{
	INT8U cDataLen;
	if(cMsgNeedTxIndFlag & TP_FC_NEED_TX_FLAG_MASK)
	{
		/* TP Flow control message need to be sent */
		if(CANMsgTxDrv.cMsgNum < MAX_CAN_MSG_TX_BUF_SIZE)
		{
			cMsgNeedTxIndFlag &= (INT16U) ~ TP_FC_NEED_TX_FLAG_MASK;
			if(CANMsgTxDrv.cWritePointer >= MAX_CAN_MSG_TX_BUF_SIZE)
			{
				CANMsgTxDrv.cWritePointer = 0;
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cCANIDIndex = DESC_RSPID;
			for(cDataLen = 0; cDataLen < 8; cDataLen ++)
			{
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[cDataLen] = DIAG_DEFAULT_VALUE;
			}
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[0] = (TP_MSG_FC << 4) | (TpRxInfoStruct.cFCStatus & 0x0f);
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[1] = TpRxInfoStruct.cBlockSize;
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cData[2] = TpRxInfoStruct.cSTMin;
			CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].cDataLength = 8;
			CANMsgTxDrv.cWritePointer ++;
			CANMsgTxDrv.cMsgNum ++;   /* Need to disable CAN TX interrupt */
		}
	}
}

/***********************************************************************************************
 * @function name:  Ecual_SetPEMsgEventTrigger
 * @description:    ����ָ��PE��Ϣ���¼��������ڶ�ʱ��ֵ�ͷ��ʹ���
 * @input parameters:     ePEMSG_INDEX Index
 * @output parameters:     ��
 * @return:         ��
 * @note:
 * @author:         ssj + 2025-04-24 10:05
 ***********************************************************************************************/
void Ecual_SetPEMsgEventTrigger(ePEMSG_INDEX Index)
{
    if (CANDrvPEMsgOpt.pMsgInfoTbl[Index].SndCycTimer > MSG_CYCLE_80MS)
    {
        CANDrvPEMsgOpt.pMsgInfoTbl[Index].SndCycTimer -= MSG_CYCLE_80MS;
    }
    else
    {
        CANDrvPEMsgOpt.pMsgInfoTbl[Index].SndCycTimer = MSG_CYCLE_BASE_TIME;
    }

    CANDrvPEMsgOpt.pMsgInfoTbl[Index].SndTimes = IlTxCyclesNRepeatTime[Index];
}

/**************************************************************************
* �������ƣ�CANDrvEMsgEventSet
* �����������¼���Ϣ����
* ��ڲ�����Index:��Ϣ���к�
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
***************************************************************************/
void CANDrvEMsgEventSet(eEMSG_INDEX Index)
{
	if(0 == CANDrvEMsgOpt.pMsgInfoTbl[Index].SndTimes)
	{
		CANDrvEMsgOpt.NeedSendMask |= (0x01u << Index);
		CANDrvEMsgOpt.EventSendOverMask |= (0x01u << Index);
		CANDrvEMsgOpt.pMsgInfoTbl[Index].SndCycTimer = 0;
		CANDrvEMsgOpt.pMsgInfoTbl[Index].SndTimes = CANMsg_EMsgTbl[Index].EventSendTims;
	}
}
/***********************************************************************************************
 * @function name: Ecual_UpdatePeriodicMsgSendMask
 * @description: ��������Ա��ĵķ������ڼ�ʱ���������´���������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
static void Ecual_UpdatePeriodicMsgSendMask(void)
{
	INT8U cIndex;

	for(cIndex = 0; cIndex < CANDrvPEMsgOpt.MsgMaxNo; cIndex++)
	{
		if(0 == CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer)
		{
			CANDrvPEMsgOpt.NeedSendMask |= (0x01 << cIndex);
		}
		else
		{
			CANDrvPEMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer--;
		}
	}
}
/**************************************************************************
* �������ƣ�CANDrvTxTask
* ������������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
***************************************************************************/
void CANDrvTxTask(void)
{
//	if(TRUE == (ComCtrlOpt.NMComMsg.Bits.TxEnable & DescComCtrlOpt.NMComMsg.Bits.TxEnable))
	if(TRUE == (ComCtrlOpt.NMComMsg.Bits.TxEnable))
	{
		CANDrvNMTxProcess();
	}

//	if(TRUE == (ComCtrlOpt.NormalComMsg.Bits.TxEnable & DescComCtrlOpt.NormalComMsg.Bits.TxEnable))
	if(TRUE == (ComCtrlOpt.NormalComMsg.Bits.TxEnable))
	{
		CANDrvEventMsgTxProcess();
		CANDrvPeriodEventMsgTxProcess();
	}
	CANDrvDescPhysicalRespTxProcess();
	CANDrvDescPhysicalRespFlowControlTxProcess();
//	CANDrvMSCAN_vogFillTxEmptyBuffers(FALSE);
}
/***********************************************************************************************
 * @function name: Ecual_CanRxStateInit
 * @description: ��ʼ��CAN���ձ���״̬���������ճ�ʱ��ʱ����ȫ����־λ����
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_CanRxStateInit(void)
{
	INT8U index;
	for(index = 0; index < eRXINDEX_MAX; index++)
	{
		CanMsgRxTimer[index] = IlGetIlRxTimeoutTbl(index)/CANDRVCYCTIME;
	}

	memset(CanStateFlags, 0, sizeof(CanStateFlags));
}
/***********************************************************************************************
 * @function name: Ecual_GetCanMsgLostFlag
 * @description:  ��ȡָ�����ĵġ���ʧ��־λ��״̬
 * @input parameters:
 *   CanIdIndex - ����ö�� eRXINDEX
 * @output parameters: void
 * @return: BOOL - TRUE ��ʾ��־λ��Ч��FALSE ��ʾ��Ч
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
BOOL Ecual_GetCanMsgLostFlag(eRXINDEX CanIdIndex)
{
    return Ecual_GetCanFlag(CANMSG_FLAG_Lost, CanIdIndex);
}
/***********************************************************************************************
 * @function name: Ecual_GetCanFlag
 * @description:  ��ȡָ����־���ͺͱ��ĵı�־λ
 * @input parameters:
 *   flagIndex - ��־λ�����±�ö�� eCANMsgFlagIndex
 *   CanIdIndex     - ����ö�� eRXINDEX
 * @output parameters: void
 * @return: BOOL - ��־λ״̬ TRUE �� FALSE
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
BOOL Ecual_GetCanFlag(eCANMsgFlagIndex flagIndex, eRXINDEX CanIdIndex)
{
    INT8U byteIdx;
    INT8U bitIdx;
    INT8U mask;

    if ((INT16U)CanIdIndex >= eRXINDEX_MAX || flagIndex >= CANMSG_FLAG_MAX)
    {
        return FALSE;
    }

    byteIdx = CanIdIndex / 8u;
    bitIdx = CanIdIndex % 8u;
    mask = (1u << bitIdx);

    if ((CanStateFlags[flagIndex].u1aData[byteIdx] & mask) != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name: Ecual_SetCanFlag
 * @description:  ����ָ����־���ͺͱ��ĵı�־λ
 * @input parameters:
 *   flagIndex - ��־λ�����±�ö�� eCANMsgFlagIndex
 *   CanIdIndex     - ����ö�� eRXINDEX
 *   value     - ��־λֵ TRUE �� FALSE
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_SetCanFlag(eCANMsgFlagIndex flagIndex, eRXINDEX CanIdIndex, BOOL value)
{
    INT8U byteIdx;
    INT8U bitIdx;
    INT8U mask;

    if ((INT16U)CanIdIndex >= eRXINDEX_MAX || flagIndex >= CANMSG_FLAG_MAX)
    {
        return;
    }

    byteIdx = CanIdIndex / 8u;
    bitIdx = CanIdIndex % 8u;
    mask = (1u << bitIdx);

    if (value == TRUE)
    {
        CanStateFlags[flagIndex].u1aData[byteIdx] |= mask;
    }
    else
    {
        CanStateFlags[flagIndex].u1aData[byteIdx] &= (INT8U)(~mask);
    }
}
/***********************************************************************************************
 * @function name:    Ecual_ClearCanRxBuffer
 * @description:      ���ָ��������CAN���ձ������ݻ������ݣ���0��
 * @input parameters: u1tPMsgIdx��������ı�������
 * @output parameters: void
 * @return:           void
 * @author:           ssj 2025-05-16
 ***********************************************************************************************/
static void Ecual_ClearCanRxBuffer(eRXINDEX Index)
{
    INT8U *RxDataPtr = CanGetRxDataPtr(Index);
    INT8U u8DLC = CanGetRxDataLen(Index);

    memset(RxDataPtr, 0, u8DLC);
}
/***********************************************************************************************
 * @function name: static void Ecual_CanRxStateMonitor(void)
 * @description: ���CAN���ձ����Ƿ�ʧ��������״̬���¼�ʱ���Ͷ�ʧ��־λ
 * @input parameters: void
 * @output parameters: ��
 * @return: void
 * @note: ssj 2025-05-16
 ***********************************************************************************************/
void Ecual_CanRxStateMonitor(void)
{
	/* �������������ڱ������ձ��ļ�ر� */
	INT8U index;

	/* ��־λ���Ƿ���Ҫ���б��Ķ�ʧ��⣨CANδBUS OFF �ҵ�ǰΪ��������ģʽ�� */
	BOOL bNeedCheckMsgLost = FALSE;;

	/* �жϵ�ǰ�Ƿ�����Ҫ��ⱨ�Ķ�ʧ��״̬ */
//	if((NM_u1gCANBusOff == FALSE) && (SleepGetRunMode() == eRUNMODE_NORMAL))
//	{
//		bNeedCheckMsgLost = TRUE;
//	}
#if 0
	�޷������ߣ����δ˴�by Prima Niu20250604
	if(bNeedCheckMsgLost != TRUE)
	{
		/* �����ʱ���������ĳ�ʱ���������� */
		for(index = 0; index < eRXINDEX_MAX; index++)
		{
			CanMsgRxTimer[index] = IlGetIlRxTimeoutTbl(index)/CANDRVCYCTIME;
		}
		return;
	}
#endif
	for(index = (eRXINDEX)0; index < eRXINDEX_MAX; index++)
	{
        if(Ecual_GetCanFlag(CANMSG_FLAG_Online, index) == TRUE)
        {
        	/* ����������߾͸�λCAN���ձ��ĳ�ʱ��� */
        	Ecual_SetCanFlag(CANMSG_FLAG_Lost, index, FALSE);
            Ecual_SetCanFlag(CANMSG_FLAG_Online, index, FALSE);
        	CanMsgRxTimer[index] = IlGetIlRxTimeoutTbl(index)/CANDRVCYCTIME;
        }

		if(CanMsgRxTimer[index] == 0u)
		{
			/* ���δ���Ϊ�Ѷ�ʧ������ս��ձ��Ļ��� */
			if(Ecual_GetCanFlag(CANMSG_FLAG_Lost, index) == FALSE)
			{
				Ecual_SetCanFlag(CANMSG_FLAG_Lost, index, TRUE);
				Ecual_ClearCanRxBuffer(index);
			}
		}
		else
		{
			CanMsgRxTimer[index]--;
		}
	}
}

/***********************************************************************************************
 * @function name: Ecual_FNOSInit
 * @description: ��ʼ����ع��ܣ�����״λ��ѱ�־����ʼ��CAN����ʹ��CAN����
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_FNOSInit(void)
{
	FirstRFWakeupFlg = FALSE;
	Ecual_CanTaskInit();
	CANDrv_SetCanTxStopFlag(FALSE);
}
/***********************************************************************************************
 * @function name: Ecual_CanTaskInit
 * @description: ��ʼ��CAN���񣬰���MSCANģ�顢�������ģ�鼰��������ź�
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_CanTaskInit(void)
{
	if (FALSE == FirstRFWakeupFlg)
	{
		FirstRFWakeupFlg = TRUE;
	    (void)CANDrvMSCAN_u1gMSCANInit();
//		NMInit();

        //checkģʽ״̬�£����������������ֹ��������ķ���
        //if(eRUNMODE_CheckWakeUp != SleepOpInfo.eRunMode)
//        {
//           StartNM(0);
//        }

	}
}

/***********************************************************************************************
 * @function name: Ecual_CanCheckSendTask
 * @description: ִ��CAN���������飬��NM״̬ΪON��δ��ֹ����ʱ��䷢�ͻ�������ͬʱ����ٲÿ�ʼ
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_CanCheckSendTask(void)
{
//	if(NmOsek_engState == NmOsek_enmON)
	{
		if(FALSE == CANDrv_GetCanTxStopFlag())
		{
			CANDrvMSCAN_vogFillTxEmptyBuffers(FALSE);
		}
	}

	CANDrvMSCAN_CheckARBSTART();
}


/***********************************************************************************************
 * @function name: Ecual_CanUdsMsgReceiveSleepCheck
 * @description: ��Ͻ��ճ�ʱ����
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
static void Ecual_CanUdsMsgReceiveSleepCheck(void)
{
    if(CPU_TimerDiffTs(s_CANDrv_UdsMsgRecTime) > 5000)
    {
    	s_CANDrv_UdsMsgRecFlg = FALSE;
    }
}

/***********************************************************************************************
 * @function name: Ecual_CanGetUdsMsgRecFlg
 * @description: ������Ͻ��ճ�ʱ����
 * @input parameters: BOOL
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
BOOL Ecual_CanGetUdsMsgRecFlg(void)
{
    return s_CANDrv_UdsMsgRecFlg;
}

/***********************************************************************************************
 * @function name: Ecual_CanTask
 * @description: CANͨ��������������������ա����͡��������TP������������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void Ecual_CanTask(void)
{
//	if(NmOsek_engState == NmOsek_enmON)
	{
 		CANDrvRxTask();
//		if(!NMOsek_vstgFuncIO.OutInfo.u1SlpFlg)
//		{
//			CANBusOffRecoveryProcess();
//		}

		NmTask();
        Ecual_CanUdsMsgReceiveSleepCheck();

		if (FALSE == CANDrv_GetCanTxStopFlag())
		{
	    	CANDrvTxTask();
		}

		if(NmOsek_engCANAppComm == NmOsek_enmEnable)
		{
			Ecual_UpdatePeriodicMsgSendMask();
	       	TPRxTask();
	       	TPTxTask();
		    DescTask();
		}
	}
}
/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


