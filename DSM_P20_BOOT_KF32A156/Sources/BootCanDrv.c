#include   "BootCanDrv.h"
#include   "Bootloader.h"
#include   "BootCan.h"
#include   "BootTp.h"
#include   "Prog.h"

#ifdef BOOTCAN_PERIODMSGTX

BOOT_U8 DebugDataPMsgTx[8];

const tBOOT_CANTX_PMSG_INFO pBootCANSigTxPMsgTbl[eBOOT_PMSG_MAX] =
{
	{0x55A, BOOT_MSG_RUNNING_VALID_DLC, DebugDataPMsgTx, BOOT_MSG_10MS_TIME},
};
#endif


#ifdef BOOTCAN_PERIODMSGTX
BOOT_U8 BootCANDrv_MsgMaxNoGet(eBOOT_MSG_TYPE eMsgType)
{
	BOOT_U8 Len = 0;
	switch(eMsgType)
	{
		case eBOOT_MSG_EVENT:
			break;
		case eBOOT_MSG_PERIOD:
			Len = UBOUND(pBootCANSigTxPMsgTbl);
			break;
		case eBOOT_MSG_PERIODEVNET:
			break;
		default:
			break;
	}
	return Len;
}
#endif

#ifdef BOOTCAN_PERIODMSGTX
void BootCANDrv_vosPMsgManage(void)
{
	BOOT_U8 cIndex;
	for(cIndex = 0; cIndex < BOOT_CANDrvPMsgOpt.MsgMaxNo; cIndex++)
	{
		if(0 == BOOT_CANDrvPMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer)
		{
			BOOT_CANDrvPMsgOpt.NeedSendMask |= (0x01 << cIndex);
		}
		else
		{
			BOOT_CANDrvPMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer--;
		}
	}
}
#endif

#ifdef BOOTCAN_PERIODMSGTX
void BootCANDrv_vosPMsgInit(eBOOT_PMSG_INDEX eIndex)
{
	switch(eIndex)
	{
		case eBOOT_PMSG_TST:
			BootCAN_stgMsgTST.TstFrameID = 0x33;
			BootCAN_stgMsgTST.ErrType = 0x00;
			break;
		default:
			break;
	}
}
#endif

#ifdef BOOTCAN_PERIODMSGTX
void BootCANDrv_vogTask(void)
{
	BOOT_U8 cIndex;
    for(cIndex = 0; cIndex < BOOT_CANDrvPMsgOpt.MsgMaxNo; cIndex++)
    {
        if(0 == BOOT_CANDrvPMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer)
        {
            BOOT_CANDrvPMsgOpt.NeedSendMask |= (0x01 << cIndex);
        }
        else 
        {
            BOOT_CANDrvPMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer--;
        }
    }
}
#endif

#ifdef BOOTCAN_PERIODMSGTX
void BootCANDrvPeriodMsgTxProcess(void)
{
	BOOT_U8 cDataLen, cIndex;
	BOOT_U16 TmpFlgMask;
	BOOT_U8 *pu1tTxMsgInfo;
	BOOT_U8 u1tDLC;
	const tBOOT_CANTX_BASE_INFO* pCANTxMsgInfo;
	if(0 == BOOT_CANDrvPMsgOpt.NeedSendMask)
	{
		return;
	}
	for(cIndex = 0, TmpFlgMask = 0x01; cIndex < BOOT_CANDrvPMsgOpt.MsgMaxNo; cIndex++)
	{
		if(BOOT_MAX_CAN_MSG_TX_BUF_SIZE > BootCANMsgTxDrv.cMsgNum)
		{
			if(BOOT_CANDrvPMsgOpt.NeedSendMask & TmpFlgMask)
			{
				BOOT_CANDrvPMsgOpt.NeedSendMask &= ~TmpFlgMask;
				BOOT_CANDrvPMsgOpt.pBootMsgILInit((eBOOT_PMSG_INDEX)cIndex);
				pCANTxMsgInfo = &pBootCANSigTxPMsgTbl[cIndex].TxBaseInfo;
				if(BootCANMsgTxDrv.cWritePointer >= BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
				{
					BootCANMsgTxDrv.cWritePointer = 0;
				}
				BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cCANIDIndex = pCANTxMsgInfo->TxID;
				pu1tTxMsgInfo = pCANTxMsgInfo->pTxSrcBuf;
				u1tDLC = pCANTxMsgInfo->TxLen;
				for(cDataLen = 0; cDataLen < u1tDLC; cDataLen ++)
				{
					BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[cDataLen] = *pu1tTxMsgInfo++;
				}
				BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cDataLength = u1tDLC;
				BootCANMsgTxDrv.cWritePointer ++;
				BootCANMsgTxDrv.cMsgNum ++;
				BOOT_CANDrvPMsgOpt.pMsgInfoTbl[cIndex].SndCycTimer = pBootCANSigTxPMsgTbl[cIndex].Period;
			}
			BootDescP4Timer = BOOT_DESC_P2_CAN_SERVER_MAX;
			TmpFlgMask <<= 1;
		}
		else
		{
			break;
		}
	}
}
#endif

void BootCANDrvTask(void)
{
	BootCANDrvRxTask();
	BootCANDrvTxTask();
}

void BootCANDrvInit(void)
{
#ifdef BOOTCAN_PERIODMSGTX
	BOOT_U8 i;
#endif
	INT_All_Enable(FALSE);//加中断保护，解决初始化过程进入接收中断，造成cMsgNum与cWritePointer数据
	BootCANMsgRxDrv.cMsgNum = 0;
	BootCANMsgRxDrv.cWritePointer = 0;
	BootCANMsgRxDrv.cReadPointer = 0;
	BootCANMsgTxDrv.cMsgNum = 0;
	BootCANMsgTxDrv.cWritePointer = 0;
	BootCANMsgTxDrv.cReadPointer = 0;
	INT_All_Enable(TRUE);
#ifdef BOOTCAN_PERIODMSGTX
	BOOT_CANDrvPMsgOpt.MsgMaxNo = BootCANDrv_MsgMaxNoGet(eBOOT_MSG_PERIOD);
	BOOT_CANDrvPMsgOpt.NeedSendMask = 0;
	BOOT_CANDrvPMsgOpt.pBootMsgILInit = BootCANDrv_vosPMsgInit;
	for(i = 0; i < UBOUND(BOOT_CANDrvPMsgOpt.pMsgInfoTbl); i++)
	{
		BOOT_CANDrvPMsgOpt.pMsgInfoTbl[i].SndCycTimer = pBootCANSigTxPMsgTbl[i].Period;
	}
	Boot_DownloadFlg = FALSE;
#endif
}

void BootCANDrvRxTask(void)
{
	while(BootCANMsgRxDrv.cMsgNum)
	{
		if(BootCANMsgRxDrv.cReadPointer >= BOOT_MAX_CAN_MSG_RX_BUF_SIZE)
		{
			BootCANMsgRxDrv.cReadPointer = 0;
		}
		//Jetty 2022-5-20 BootStdMsgRxProcess函数由于条件不处理数据时，读指针不更新，防止数据丢失。
		if (BootStdMsgRxProcess(BootCANMsgRxDrv.cReadPointer) == TRUE)
		{
			Boot_DisableInterrupts;
			BootCANMsgRxDrv.cMsgNum --;
			BootCANMsgRxDrv.cReadPointer ++;
			Boot_EnableInterrupts;
		}
		else
		{
		}
	}
}

BOOL BootStdMsgRxProcess(BOOT_U8  cMsgIndex)
{
	BOOT_U32 	USHID;
	BOOL ret = FALSE;

	USHID = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cCANID;


	if(FALSE == IsOperateFlash) // 如果在写Flash,则不去接收诊断数据, 否则新的诊断数据会覆盖之前的数据,因为TP共用一个Buffer,这样会导致正在写的数据被更改,导致写失败
	{
    	if(USHID == BOOT_RX_MSG_PHYSICAL_ID)
    	{
    		BootTPRxProcess(cMsgIndex, BOOT_RX_MSG_PHYSICAL);
    	}
    	else if(USHID == BOOT_RX_MSG_FUNTION_ID)
    	{
    		BootTPRxProcess(cMsgIndex, BOOT_RX_MSG_FUNTION);
    	}
    	ret = TRUE;
	}
	return ret;
}


void BootCANDrvTxTask(void)
{
#ifdef	BOOTCAN_PERIODMSGTX
	BootCANDrvPeriodMsgTxProcess();
#endif
	BootTST_PhysicalRespTxProcess();
	BootTST_PhysicalRespFlowControlTxProcess();
	//Boot_DisableInterrupts;
//	BootCANTRX(FALSE);
	//Boot_EnableInterrupts;
}

void BootTST_PhysicalRespTxProcess(void)
{
	BOOT_U8 cDataLen;

	if(BootMsgNeedTxIndFlag & BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK)
	{
		if(BootCANMsgTxDrv.cMsgNum < BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
		{
			BootMsgNeedTxIndFlag &= ~ BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
			if(BootCANMsgTxDrv.cWritePointer >= BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
			{
				BootCANMsgTxDrv.cWritePointer = 0;
			}
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cCANIDIndex = BOOTDESC_RSPID;
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].IdType=FLEXCAN_MSG_ID_STD;
			for(cDataLen = 0; cDataLen < 8; cDataLen ++)
			{
				BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[cDataLen] = BootTpTxBuf[cDataLen];
			}
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cDataLength = 8;
			BootCANMsgTxDrv.cWritePointer ++;
			BootCANMsgTxDrv.cMsgNum ++;
		}
	}
}

void BootTST_PhysicalRespFlowControlTxProcess(void)
{
	BOOT_U8 cDataLen;

	if(BootMsgNeedTxIndFlag & BOOT_TP_FC_NEED_TX_FLAG_MASK)
	{
		if(BootCANMsgTxDrv.cMsgNum < BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
		{
			BootMsgNeedTxIndFlag &= ~ BOOT_TP_FC_NEED_TX_FLAG_MASK;
			if(BootCANMsgTxDrv.cWritePointer >= BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
			{
				BootCANMsgTxDrv.cWritePointer = 0;
			}
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cCANIDIndex = BOOTDESC_RSPID;
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].IdType = FLEXCAN_MSG_ID_STD;
			for(cDataLen = 0; cDataLen < 8; cDataLen ++)
			{
				BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[cDataLen] = DIAG_DEFAULT_VALUE;
			}
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[0] = (BOOT_TP_MSG_FC << 4) | (BootTpRxInfoStruct.cFCStatus & 0x0f);
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[1] = BootTpRxInfoStruct.cBlockSize;
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cData[2] = BootTpRxInfoStruct.cSTMin;
			BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cWritePointer].cDataLength = 8;
			BootCANMsgTxDrv.cWritePointer ++;
			BootCANMsgTxDrv.cMsgNum ++;
		}
	}
}

