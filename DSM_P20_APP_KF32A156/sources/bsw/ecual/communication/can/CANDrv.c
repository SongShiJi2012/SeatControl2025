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
tCOMCTRL_OPT      DescComCtrlOpt;		//通过$28服务设置的值

INT8U Buffer_6E0_C[8];
INT8U Buffer_6E1_C[8];
static unCANMsgFlag CanStateFlags[CANMSG_FLAG_MAX];
static INT32U CanMsgRxTimer[eRXINDEX_MAX];
volatile BOOL FirstRFWakeupFlg;
/* CAN发送信息 事件报文 - P20无事件发送报文 暂时不处理相关接口*/
const CANTxEMsgInfo CANMsg_EMsgTbl[] =
{
    { {FLEXCAN_MSG_ID_STD,	0x6E0,	8,	(INT8U*)&Buffer_6E0_C},	MSG_CYCLE_20MS,	1},
    { {FLEXCAN_MSG_ID_STD,	0x6E1,	8,	(INT8U*)&Buffer_6E1_C},	MSG_CYCLE_20MS,	1},
};
static BOOL s_CAN_ACK_Err_Tx_Enable = TRUE;
static BOOL s_CAN_ACK_Err = FALSE;

static BOOL s_CANDrv_UdsMsgRecFlg = FALSE;//诊断报文接收标志
static INT32U s_CANDrv_UdsMsgRecTime = 0;//诊断报文接收标志
/***********************************************************************
 * @function name: Ecual_GetCanACKErrSts
 *
 * @description: 获取CAN ACK无应答错误状态
 *
 * @input parameters: void
 *
 * @output parameters: void
 *
 * @return: TRUE:发生无应答错误  FALSE：无
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
* 函数名称：CANIL_vosEMsgInit
* 功能描述：事件型消息初始化
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
* 函数名称：CANIL_vosPEMsgInit
* 功能描述：周期事件型消息初始化
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void CANIL_vosPEMsgInit(ePEMSG_INDEX eIndex)
{
}
/*************************************************************
* 函数名称：CANDrvInit
* 功能描述：CAN驱动层初始化
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void CANDrvInit(void)
{
	INT8U  i;
	INT_All_Enable(FALSE);//加中断保护，解决初始化过程进入接收中断，造成cMsgNum与cWritePointer数据不一致的问题

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
		//禅道1444 优先0x3B2发送
		CANDrvPEMsgOpt.pMsgInfoTbl[eDSMG_MAX - i - 1].SndCycTimer = (i*4);
		CANDrvPEMsgOpt.pMsgInfoTbl[i].SndTimes = 0;
	}

}

/*************************************************************
* 函数名称：CANDrvRxTask
* 功能描述：CAN驱动层接收任务
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
 * @description: 将接收到的 CAN 报文数据从驱动缓冲区复制到指定接收缓冲区，并设置接收标志位
 * @input parameters: INT8U u1tRxMsgIndex - 接收缓冲区索引；INT8U cMsgIndex - 驱动接收缓存索引
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-16
 ***********************************************************************************************/
static void Ecual_CopyDataToRxMsg(eRXINDEX u1tRxMsgIndex, INT8U cMsgIndex)
{
	INT8U u1tIdx, *pu1tRxMsgInfo;
	INT8U u1tDLC = CanGetRxDataLen(u1tRxMsgIndex);

	/* 若驱动数据长度不足，直接返回 */
	if (CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength < u1tDLC)
	{
		return;
	}

	/* 获取接收缓冲区指针 */
	pu1tRxMsgInfo = CanGetRxDataPtr(u1tRxMsgIndex);

	/* 中断保护，防止数据冲突 */
	INT_All_Enable(FALSE);
	memcpy(pu1tRxMsgInfo, CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData, u1tDLC);
	INT_All_Enable(TRUE);

	/* 设置接收标志位 */
	Ecual_SetCanFlag(CANMSG_FLAG_Online, u1tRxMsgIndex, TRUE);
	Ecual_SetCanFlag(CANMSG_FLAG_Update, u1tRxMsgIndex, TRUE);
}

/*************************************************************
* 函数名称：Ecual_GetNMRxIDAndData
* 功能描述：获取网络管理CAN信号
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
static void Ecual_GetNMRxIDAndData(INT8U cMsgIndex, INT32U u1tMsgID)
{
//	INT8U cIndex = 0;
//
//	CanRxActualNmId = u1tMsgID;
//	INT_All_Enable(FALSE);//加中断保护，- 需要对漏帧进行测试
//	for(cIndex = 0; cIndex < 8; cIndex++)
//	{
//		nmRecvMess[cIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[cIndex];
//	}
//	INT_All_Enable(TRUE);
}
/***********************************************************************
 * @function name: Ecual_CanSetUdsMsgReceiveFlg
 * @description: 设置can诊断接收标志
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
* 函数名称：StdMsgRxProcess
* 功能描述：接收CAN信息处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
static void StdMsgRxProcess(INT8U  cMsgIndex)
{
	INT8U cIDIndex;
	INT32U u2tCurMsgID;
    
	CANWakeupFlg = TRUE; //接收到CAN报文
	
	u2tCurMsgID = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cCANID;
	/*应用报文*/
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
	/*诊断报文*/
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
	/*网络管理报文*/
//	if((ComCtrlOpt.NMComMsg.Bits.RxEnable == TRUE) && (DescComCtrlOpt.NMComMsg.Bits.RxEnable == TRUE))
//	{
//		//只有网络报文允许接收才解析
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
* 函数名称：Ecual_IsTestMessageSendEnable
* 功能描述：是否发送测试报文
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
static BOOL Ecual_IsTestMessageSendEnable(INT16U u16CanID)
{
	BOOL bRet = TRUE;
	INT16U u16TestCanMsgID1_NodeBcm[] = {0x500, 0x501, 0x502}; /*测试报文*/
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
* 函数名称：CANDrvEventMsgTxProcess
* 功能描述：事件型CAN信号发送处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
* 函数名称：CANDrvPeriodEventMsgTxProcess
* 功能描述：周期事件型CAN信号发送处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
				CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;//P20项目只有标准帧
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
* 函数名称：CANDrvNMTxProcess
* 功能描述：网络管理CAN信号发送处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
* 函数名称：CANDrvDescPhysicalRespTxProcess
* 功能描述：诊断物理寻址响应发送处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
            CANMsgTxDrv.cWritePointer ++;//同步46DB修改1101复位不响应问题
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
* 函数名称：CANDrvDescPhysicalRespFlowControlTxProcess
* 功能描述：诊断物理寻址响应流控发送处理
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
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
 * @description:    设置指定PE消息的事件发送周期定时器值和发送次数
 * @input parameters:     ePEMSG_INDEX Index
 * @output parameters:     无
 * @return:         无
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
* 函数名称：CANDrvEMsgEventSet
* 功能描述：事件消息设置
* 入口参数：Index:消息序列号
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
 * @description: 检查周期性报文的发送周期计时器，并更新待发送掩码
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
* 函数名称：CANDrvTxTask
* 功能描述：发送任务
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
 * @description: 初始化CAN接收报文状态，包括接收超时计时器和全部标志位清零
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
 * @description:  获取指定报文的“丢失标志位”状态
 * @input parameters:
 *   CanIdIndex - 报文枚举 eRXINDEX
 * @output parameters: void
 * @return: BOOL - TRUE 表示标志位有效，FALSE 表示无效
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
BOOL Ecual_GetCanMsgLostFlag(eRXINDEX CanIdIndex)
{
    return Ecual_GetCanFlag(CANMSG_FLAG_Lost, CanIdIndex);
}
/***********************************************************************************************
 * @function name: Ecual_GetCanFlag
 * @description:  获取指定标志类型和报文的标志位
 * @input parameters:
 *   flagIndex - 标志位数据下标枚举 eCANMsgFlagIndex
 *   CanIdIndex     - 报文枚举 eRXINDEX
 * @output parameters: void
 * @return: BOOL - 标志位状态 TRUE 或 FALSE
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
 * @description:  设置指定标志类型和报文的标志位
 * @input parameters:
 *   flagIndex - 标志位数据下标枚举 eCANMsgFlagIndex
 *   CanIdIndex     - 报文枚举 eRXINDEX
 *   value     - 标志位值 TRUE 或 FALSE
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
 * @description:      清除指定索引的CAN接收报文数据缓存内容（置0）
 * @input parameters: u1tPMsgIdx：待清除的报文索引
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
 * @description: 监测CAN接收报文是否丢失，并根据状态更新计时器和丢失标志位
 * @input parameters: void
 * @output parameters: 无
 * @return: void
 * @note: ssj 2025-05-16
 ***********************************************************************************************/
void Ecual_CanRxStateMonitor(void)
{
	/* 索引变量，用于遍历接收报文监控表 */
	INT8U index;

	/* 标志位：是否需要进行报文丢失检测（CAN未BUS OFF 且当前为正常运行模式） */
	BOOL bNeedCheckMsgLost = FALSE;;

	/* 判断当前是否处于需要检测报文丢失的状态 */
//	if((NM_u1gCANBusOff == FALSE) && (SleepGetRunMode() == eRUNMODE_NORMAL))
//	{
//		bNeedCheckMsgLost = TRUE;
//	}
#if 0
	无法检测掉线，屏蔽此处by Prima Niu20250604
	if(bNeedCheckMsgLost != TRUE)
	{
		/* 不检测时，仅将报文超时计数器重置 */
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
        	/* 如果报文在线就复位CAN接收报文超时检测 */
        	Ecual_SetCanFlag(CANMSG_FLAG_Lost, index, FALSE);
            Ecual_SetCanFlag(CANMSG_FLAG_Online, index, FALSE);
        	CanMsgRxTimer[index] = IlGetIlRxTimeoutTbl(index)/CANDRVCYCTIME;
        }

		if(CanMsgRxTimer[index] == 0u)
		{
			/* 如果未标记为已丢失，则清空接收报文缓存 */
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
 * @description: 初始化相关功能，清除首次唤醒标志，初始化CAN任务，使能CAN发送
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
 * @description: 初始化CAN任务，包括MSCAN模块、网络管理模块及清除唤醒信号
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

        //check模式状态下，不开启网络管理，防止网络管理报文发出
        //if(eRUNMODE_CheckWakeUp != SleepOpInfo.eRunMode)
//        {
//           StartNM(0);
//        }

	}
}

/***********************************************************************************************
 * @function name: Ecual_CanCheckSendTask
 * @description: 执行CAN发送任务检查，当NM状态为ON且未禁止发送时填充发送缓冲区，同时检查仲裁开始
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
 * @description: 诊断接收超时处理
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
 * @description: 返回诊断接收超时处理
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
 * @description: CAN通信任务主函数，处理接收、发送、网络管理、TP及描述符任务
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


