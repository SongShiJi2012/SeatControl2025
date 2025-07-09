#include   "BootTp.h"
#include   "BootCanDrv.h"
#include   "BootCan.h"
#include   "BootDesc.h"


BOOT_U8				BootMsgNeedTxIndFlag;
BOOT_U8				BootTpTxBuf[8];
BOOT_U8				BootTpRxErrorType;
stTpTxState 				BootTpTxState;
stTpRxState 				BootTpRxState;
stTpTxInfoStruct 			BootTpTxInfoStruct;
stTpRxInfoStruct 			BootTpRxInfoStruct;
volatile BOOT_U8 Boot_FirstFCflg;
volatile BOOT_U8 Boot_FirstcSTMin; 
volatile BOOT_U8 Boot_TP_u1gPhisicalRspTxFnshFlg;


static BOOL TpTesterFrameHandle(INT8U *pdata, INT8U len);


void BootTPInit(void)
{
	BootTpTxState.cBSCounter = 0;
	BootTpTxState.engine = BOOT_kTxState_Idle;
	BootTpTxState.Timer = 0;
	BootTpRxState.cBSCounter = 0;
	BootTpRxState.engine = BOOT_kRxState_Idle;
	BootTpRxState.Timer = 0;
	BootTpTxInfoStruct.cCANIDIndex = 0;
	BootTpTxInfoStruct.cBlockSize = 0;
	BootTpTxInfoStruct.wDataReadIndex = 0;
	BootTpTxInfoStruct.wDataLength = 0;
	BootTpTxInfoStruct.cSequenceNumber = 0;
	BootTpTxInfoStruct.cSTMin = 0;
	BootTpTxInfoStruct.wDataWriteIndex = 0;
	BootTpRxInfoStruct.cCANIDIndex = 0;
	BootTpRxInfoStruct.wDataIndex = 0;
	BootTpRxInfoStruct.wDataLength = 0;
	BootTpRxInfoStruct.cSequenceNumber = 0;
	Boot_FirstFCflg = FALSE;
	Boot_FirstcSTMin = 0;
}

void BootTPTxTask(void)
{
	if(Boot_TP_u1gPhisicalRspTxFnshFlg)
	{
		Boot_TP_u1gPhisicalRspTxFnshFlg = FALSE;
		BootTPTxProcess();
	}
	if(BootTpTxState.Timer)
	{
		BootTpTxState.Timer --;
	}
	if(BootTpTxState.Timer == 0)
	{
		if(BootTpTxState.engine == BOOT_kTxState_WaitForTpTxCF)
		{
			BootTpTxConsecutiveFrame();
		}
		else if(BootTpTxState.engine != BOOT_kTxState_Idle)
		{
			BootTpTxState.engine = BOOT_kTxState_Idle;
		}
	}
}

void BootTPRxTask(void)
{
	if(BootTpRxState.Timer)
	{
		BootTpRxState.Timer --;
	}
	if(BootTpRxState.Timer == 0)
	{
		if(BootTpRxState.engine == BOOT_kRxState_WaitFC)
		{
			BootTpRxState.engine = BOOT_kRxState_WaitForFCConfIsr;
			BootCANDrvTxTask();
		}
		else if((BootTpRxState.engine != BOOT_kRxState_CanFrameReceived) && (BootTpRxState.engine != BOOT_kRxState_ApplInformed))
		{
			BootTpRxState.engine = BOOT_kRxState_Idle;
		}
		else if((BootTpRxState.engine == BOOT_kRxState_ApplInformed) && (BootTpTxState.engine == BOOT_kTxState_Idle))
		{
			BootTpRxState.engine = BOOT_kRxState_Idle;
		}
	}
}

void BootTPRxProcess(BOOT_U8 cMsgIndex, BOOT_U8 cCANIDInd)
{
	static BOOT_U16  s_blokCnt = 0;
	BOOT_U8 	cTPMsgType;
	BOOT_U8 	cTPMsgParameter;
	BOOT_U16 	wDataLen;
	BOOT_U16  	wIndex;

	if(BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength != 8)
	{
		BootTpRxErrorType = BOOT_N_INVALID_MSG_DATA_LENGTH;
		return;
	}
	
	/*boot诊断服务中,不响应功能寻址在线服务*/
	/*if((cCANIDInd == BOOT_RX_MSG_FUNTION) && \
		((BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1] == 0x3eu)&&(BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2] == 0x80u)))
	{
		BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		return;
	}*/

	cTPMsgType = (BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[0] & BOOT_TP_MSG_TYPE_MASK) >> 4;
	cTPMsgParameter = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[0] & BOOT_TP_MSG_PARAMETER_MASK;
	if((BootTpRxState.engine == BOOT_kRxState_CanFrameReceived) || \
			((BootTpRxState.engine == BOOT_kRxState_ApplInformed) && \
			 (BootTpTxState.engine != BOOT_kTxState_Idle) && \
			 (cTPMsgType != BOOT_TP_MSG_FC)))
	{
		return;
	}
	switch(cTPMsgType)
	{
		
		case BOOT_TP_MSG_SF:
			if((cTPMsgParameter == 0) || (cTPMsgParameter > BOOT_SF_MAX_DATA_LENGTH))
			{
				BootTpRxErrorType  = BOOT_N_INVALID_SF_DATA_LENGTH;
				return;
			}
			
			/*if(BootTpRxState.engine != BOOT_kRxState_Idle)
			{
				BootTpRxErrorType = BOOT_N_UNEXP_PDU;
				if((cCANIDInd == BOOT_RX_MSG_FUNTION) && (BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1] == 0x3eu))
				{
					return;
				}
			}*/
			if (TpTesterFrameHandle(BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData, BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength) == TRUE)
			{
				BootTpRxInfoStruct.cCANIDIndex = cCANIDInd;
				BootTpRxInfoStruct.wDataIndex = 0;
				BootTpRxInfoStruct.wDataLength = cTPMsgParameter;
				for(wIndex = 0; wIndex < cTPMsgParameter; wIndex++)
				{
					BootTpRxInfoStruct.cDataBuf[wIndex] = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1 + wIndex];
				}
				BootTpRxState.engine = BOOT_kRxState_CanFrameReceived;
			}
			break;
		case BOOT_TP_MSG_FF:
			if(BootTpRxState.engine != BOOT_kRxState_Idle)
			{
				BootTpRxErrorType = BOOT_N_UNEXP_PDU;
			}
			wDataLen = cTPMsgParameter;
			wDataLen <<= 8;
			wDataLen |= (BOOT_U16)(BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1]);
			if(wDataLen <= BOOT_FF_MIN_DATA_LENGTH)
			{
				BootTpRxErrorType  = BOOT_N_INVALID_FF_DATA_LENGTH;
				return;
			}
			else if(wDataLen > BOOT_TP_RX_DATA_BUF_SIZE)
			{
				BootTpRxErrorType = BOOT_N_BUFFER_OVFLW;
				BootTpRxInfoStruct.cFCStatus = BOOT_FC_STATUS_OVER_FLOW;
				BootTpRxInfoStruct.cBlockSize = BOOT_FC_BLOCK_SIZE;
				BootTpRxInfoStruct.cSTMin = BOOT_FC_STMIN;
				BootMsgNeedTxIndFlag |= BOOT_TP_FC_NEED_TX_FLAG_MASK;
				BootTpRxState.engine = BOOT_kRxState_Idle;
				return;
			}
			BootTpRxInfoStruct.cCANIDIndex = cCANIDInd;
			if(BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_FUNTION)
			{
				return;
			}
			BootTpRxInfoStruct.wDataIndex = BOOT_FF_DATA_LENGTH;
			BootTpRxInfoStruct.wDataLength = wDataLen;
			for(wIndex = 0; wIndex < BOOT_FF_DATA_LENGTH; wIndex++)
			{
				BootTpRxInfoStruct.cDataBuf[wIndex] = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2 + wIndex];
			}
			s_blokCnt = 0;
			BootTpRxState.cBSCounter = 0;
			BootTpRxInfoStruct.cSequenceNumber = 0;
			BootTpRxState.engine = BOOT_kRxState_WaitFC;
			BootTpRxState.Timer = BOOT_TP_RX_WAIT_TO_SEND_FC_TIME;
			BootTpRxInfoStruct.cFCStatus = BOOT_FC_CONTINUE_TO_SEND;
			BootTpRxInfoStruct.cBlockSize = BOOT_FC_BLOCK_SIZE;
			BootTpRxInfoStruct.cSTMin = BOOT_FC_STMIN;
			BootMsgNeedTxIndFlag |= BOOT_TP_FC_NEED_TX_FLAG_MASK;
			if(BootTpRxState.Timer == 0)
			{
				BootCANDrvTxTask();
				BootTpRxState.engine = BOOT_kRxState_WaitCF;
				BootTpRxState.Timer = BOOT_TP_RX_WAIT_CF_TIME;
			}
			break;
		case BOOT_TP_MSG_CF:
			if(cCANIDInd == BOOT_RX_MSG_FUNTION)
			{
				return;
			}
			if(BootTpRxState.engine != BOOT_kRxState_WaitCF)
			{
				BootTpRxErrorType = BOOT_N_UNEXP_PDU;
				return;
			}
			s_blokCnt++;
			BootTpRxInfoStruct.cSequenceNumber ++;
			if(BootTpRxInfoStruct.cSequenceNumber > 0x0f)
			{
				BootTpRxInfoStruct.cSequenceNumber = 0;
			}
			if(cTPMsgParameter != BootTpRxInfoStruct.cSequenceNumber)
			{
				BootTpRxErrorType = BOOT_N_WRONG_SN;
				BootTpRxState.engine = BOOT_kRxState_Idle;
				return;
			}
			if(BootTpRxInfoStruct.cCANIDIndex != cCANIDInd)
			{
				BootTpRxErrorType = BOOT_N_DEFFERENT_CAN_ID_RQ;
				return;
			}
			wIndex = 1;
			for(; BootTpRxInfoStruct.wDataIndex < BootTpRxInfoStruct.wDataLength; BootTpRxInfoStruct.wDataIndex++)
			{
				if(wIndex >= 8)
				{
					break;
				}
				BootTpRxInfoStruct.cDataBuf[BootTpRxInfoStruct.wDataIndex] = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[wIndex];
				wIndex ++;
			}
			BootTpRxState.Timer = BOOT_TP_RX_WAIT_CF_TIME;
			if(BootTpRxInfoStruct.wDataLength <= BootTpRxInfoStruct.wDataIndex)
			{
				BootTpRxState.engine = BOOT_kRxState_CanFrameReceived;
				break;
			}
			if(s_blokCnt == BOOT_FC_BLOCK_SIZE)
			{
				BootMsgNeedTxIndFlag |= BOOT_TP_FC_NEED_TX_FLAG_MASK;
				s_blokCnt = 0;
			}
			break;
		case BOOT_TP_MSG_FC:
			if(cCANIDInd == BOOT_RX_MSG_FUNTION)
			{
				return;
			}
			if((BootTpTxState.engine == BOOT_kTxState_WaitFC) || (BootTpTxState.engine == BOOT_kTxState_WaitForFFConfIsr))
			{
				if(cTPMsgParameter == BOOT_FC_CONTINUE_TO_SEND)
				{
					BootTpTxInfoStruct.cBlockSize = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1];
					if(Boot_FirstFCflg == FALSE)
					{
						BootTpTxInfoStruct.cSTMin = BootCANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2];
						Boot_FirstcSTMin = BootTpTxInfoStruct.cSTMin;
					}
					else
					{
						BootTpTxInfoStruct.cSTMin = Boot_FirstcSTMin;
					}
					Boot_FirstFCflg = TRUE;
					if(BootTpTxInfoStruct.cSTMin <= 0x7f)
					{
						BootTpTxInfoStruct.cSTMin = BootTpTxInfoStruct.cSTMin / BOOT_TP_TASK_CALL_CYCLE_TIME;
					}
					else if((BootTpTxInfoStruct.cSTMin >= 0xf1) && (BootTpTxInfoStruct.cSTMin <= 0xF9))
					{
						BootTpTxInfoStruct.cSTMin = 0;
					}
					else
					{
						BootTpTxInfoStruct.cSTMin = 0x7f / BOOT_TP_TASK_CALL_CYCLE_TIME;
					}
					if(BootTpTxInfoStruct.cSTMin == 0)
					{
						BootTpTxInfoStruct.cSTMin = 1;
					}
					BootTpTxState.engine = BOOT_kTxState_WaitForTpTxCF;
					BootTpTxState.Timer = BootTpTxInfoStruct.cSTMin + 1;/* 第一帧连续帧发送时间 + 1,修复第一帧连续帧与流控帧的时间间隔小于stmin时间问题*/
					if(BootTpTxState.Timer == 0)
					{
						BootTpTxConsecutiveFrame();
					}
				}
				else if(cTPMsgParameter == BOOT_FC_WAIT)
				{
					//BootTpTxState.Timer = BOOT_TP_TX_WAIT_FC_TIME;
					BootTpRxState.engine = BOOT_kRxState_Idle;
				}
				else if(cTPMsgParameter == BOOT_FC_STATUS_OVER_FLOW)
				{
					BootTpRxState.engine = BOOT_kRxState_Idle;
				}
			}
			break;
		default:
			BootTpRxErrorType = BOOT_N_INVALID_MSG_TYPE;
			return;
			//break;
	}
}

void BootTPTxProcess(void)
{
	switch(BootTpTxState.engine)
	{
		case BOOT_kTxState_WaitForSFConfIsr:
			BootTpTxState.engine = BOOT_kTxState_Idle;
			BootTpRxState.engine = BOOT_kRxState_Idle;
			break;
		case BOOT_kTxState_WaitForFFConfIsr:
			BootTpTxState.Timer = BOOT_TP_TX_WAIT_FC_TIME;
			BootTpTxState.engine = BOOT_kTxState_WaitFC;
			break;
		case BOOT_kTxState_WaitForCFConfIsr:
			if(BootTpTxInfoStruct.cBlockSize == 0)
			{
				BootTpTxState.engine = BOOT_kTxState_WaitForTpTxCF;
				BootTpTxState.Timer = BootTpTxInfoStruct.cSTMin + 1;
				if(BootTpTxState.Timer == 0)
				{
					BootTpTxConsecutiveFrame();
				}
			}
			else
			{
				if(BootTpTxState.cBSCounter >= (BootTpTxInfoStruct.cBlockSize - 1))
				{
					BootTpTxState.engine = BOOT_kTxState_WaitFC;
					BootTpTxState.Timer = BOOT_TP_TX_WAIT_FC_TIME;
					BootTpTxState.cBSCounter = 0;
				}
				else
				{
					BootTpTxState.cBSCounter ++;
					BootTpTxState.engine = BOOT_kTxState_WaitForTpTxCF;
					BootTpTxState.Timer = BootTpTxInfoStruct.cSTMin + 1;
					if(BootTpTxState.Timer == 0)
					{
						BootTpTxConsecutiveFrame();
					}
				}
			}
			break;
		case BOOT_kTxState_WaitForLastCFConfIsr:
			BootTpTxState.engine = BOOT_kTxState_Idle;
			BootTpRxState.engine = BOOT_kRxState_Idle;
			break;
		default:
			break;
	}
}

void BootTpTxStart(void)
{
	BOOT_U16  wIndex;

	for(wIndex = 0; wIndex < 8; wIndex ++)
	{
		BootTpTxBuf[wIndex] = DIAG_DEFAULT_VALUE;
	}
	if(BootTpTxInfoStruct.wDataLength <= BOOT_SF_MAX_DATA_LENGTH_WITH_STD_ADDR)
	{
		BootTpTxBuf[0] = (BOOT_TP_MSG_SF << 4) | (((BOOT_U8)(BootTpTxInfoStruct.wDataLength)) & 0x0f);
		for(wIndex = 0; wIndex < BootTpTxInfoStruct.wDataLength; wIndex ++)
		{
			BootTpTxBuf[wIndex + 1] = BootTpTxInfoStruct.cDataBuf[wIndex];
		}
		BootTpTxState.engine = BOOT_kTxState_WaitForSFConfIsr;
		BootTpTxState.Timer = BOOT_TP_TX_WAIT_SF_CONFIRM_TIME;
		BootMsgNeedTxIndFlag |=  BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
		BootCANDrvTxTask();
	}
	else if(BootTpTxInfoStruct.wDataLength <= BOOT_TP_MAX_TX_SIZE)
	{
		Boot_FirstFCflg = FALSE;
		BootTpTxBuf[0] = (BOOT_TP_MSG_FF << 4) | (((BOOT_U8)(BootTpTxInfoStruct.wDataLength >> 8)) & 0x0f);
		BootTpTxBuf[1] = (BOOT_U8)(BootTpTxInfoStruct.wDataLength);
		for(wIndex = 0; wIndex < BOOT_FF_DATA_LENGTH; wIndex ++)
		{
			BootTpTxBuf[wIndex + 2] = BootTpTxInfoStruct.cDataBuf[wIndex];
		}
		BootTpTxInfoStruct.wDataReadIndex = BOOT_FF_DATA_LENGTH;
		BootTpTxState.engine = BOOT_kTxState_WaitForFFConfIsr;
		BootTpTxState.cBSCounter = 0;
		BootTpTxInfoStruct.cSequenceNumber = 1;
		BootTpTxState.Timer = BOOT_TP_TX_WAIT_FF_CONFIRM_TIME;
		BootMsgNeedTxIndFlag |=  BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
		BootCANDrvTxTask();
	}
	else
	{
		BootTpTxState.engine = BOOT_kTxState_Idle;
	}
}

void BootTpTxConsecutiveFrame(void)
{
	BOOT_U16  	wIndex2;
	BOOT_U8  	cIndex1;

	for(cIndex1 = 0; cIndex1 < 8; cIndex1 ++)
	{
		BootTpTxBuf[cIndex1] = DIAG_DEFAULT_VALUE; //  北汽填充0xCC
	}
	BootTpTxBuf[0] = (BOOT_TP_MSG_CF << 4) | (BootTpTxInfoStruct.cSequenceNumber & 0x0f);
	BootTpTxInfoStruct.cSequenceNumber ++;
	if(BootTpTxInfoStruct.cSequenceNumber > 0x0f)
	{
		BootTpTxInfoStruct.cSequenceNumber = 0;
	}
	cIndex1 = 1;
	wIndex2 = BootTpTxInfoStruct.wDataReadIndex % BOOT_TP_TX_DATA_BUF_SIZE;
	for(; BootTpTxInfoStruct.wDataReadIndex < BootTpTxInfoStruct.wDataLength; BootTpTxInfoStruct.wDataReadIndex ++)
	{
		if(cIndex1 >= 8)
		{
			break;
		}
		if(wIndex2 >= BOOT_TP_TX_DATA_BUF_SIZE)
		{
			wIndex2 = 0;
		}
		BootTpTxBuf[cIndex1] = BootTpTxInfoStruct.cDataBuf[wIndex2];
		wIndex2 ++;
		cIndex1 ++;
	}
	if(BootTpTxInfoStruct.wDataReadIndex >= BootTpTxInfoStruct.wDataLength)
	{
		BootTpTxState.engine = BOOT_kTxState_WaitForLastCFConfIsr;
	}
	else
	{
		BootTpTxState.engine = BOOT_kTxState_WaitForCFConfIsr;
	}
	BootTpTxState.Timer = BOOT_TP_TX_WAIT_CF_CONFIRM_TIME;
	BootMsgNeedTxIndFlag |=  BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
	BootCANDrvTxTask();
}



static BOOL TpTesterFrameHandle(INT8U *pdata, INT8U len)
{
	INT8U  i;
	BOOL ret = FALSE;

	do
	{
/*		if (BootTpRxState.engine == BOOT_kRxState_Idle)
		{
			// 空闲接收的第一次报文
			ret = TRUE;
			break;
		}
*/
		
		if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x00)
		{
			// 需响应02 7e 00				
			for (i = 0; i < D_TP_TX_MAX_LEN; i++)
			{
				BootTpTxBuf[i] = DIAG_DEFAULT_VALUE;
			}

			BootTpTxBuf[0] = 0x02;
			BootTpTxBuf[1] = 0x7e;
			BootTpTxBuf[2] = 0x00;
			
			BootMsgNeedTxIndFlag |=  BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
			BootCANDrvTxTask();

			// 需重置会话时间
			BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x80)
		{
			// 需重置会话时间，无需响应
			BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else
		{
			ret = TRUE;
		}
	} while (0);
	

	return ret;
}



