/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "TP.h"
#include "CANDrv.h"
#include "Desc.h"

volatile INT8U  cTpTxBuf[8];
volatile INT8U cTpRxErrorType;
volatile tTpTxState TpTxState;
volatile tTpRxState TpRxState;
volatile tTpTxInfoStruct TpTxInfoStruct;

//从TpRxInfoStruct结构获取接收到的诊断数据发送给BPM
volatile tTpRxInfoStruct TpRxInfoStruct;//底层can接收的数据存放到该变量
volatile INT8U cTpFCSeperationTimeMin;
volatile INT8U FirstFCflg;
volatile INT8U FirstcSTMin;
volatile INT8U TP_u1gPhisicalRspTxFnshFlg;


static BOOL TpTesterFrameHandle(INT8U *pdata, INT8U len);

//#pragma  text  "TP_Text"
void TPInit(void)
{
	TpTxState.cBSCounter = 0;
	TpTxState.engine = kTxState_Idle;
	TpTxState.Timer = 0;
	TpRxState.cBSCounter = 0;
	TpRxState.engine = kRxState_Idle;
	TpRxState.Timer = 0;
	TpTxInfoStruct.cCANIDIndex = 0;
	TpTxInfoStruct.cBlockSize = 0;
	TpTxInfoStruct.wDataReadIndex = 0;
	TpTxInfoStruct.wDataLength = 0;
	TpTxInfoStruct.cSequenceNumber = 0;
	TpTxInfoStruct.cSTMin = 0;
	TpTxInfoStruct.wDataWriteIndex = 0;
	TpRxInfoStruct.cCANIDIndex = 0;
	TpRxInfoStruct.wDataIndex = 0;
	TpRxInfoStruct.wDataLength = 0;
	TpRxInfoStruct.cSequenceNumber = 0;
	FirstFCflg = FALSE;
	FirstcSTMin = 0;
}

void TPTxTask(void)
{
	if(TP_u1gPhisicalRspTxFnshFlg)//物理响应完成标志，发送完一帧进入
	{
		TP_u1gPhisicalRspTxFnshFlg = FALSE;
		TPTxProcess();
	}
	/* Tp Tx Timer Management */
	if(TpTxState.Timer)
	{
		TpTxState.Timer --;//控制发送时间间隔
	}
	if(TpTxState.Timer == 0)
	{
		/* Tp Tx Time Out */
		if(TpTxState.engine == kTxState_WaitForTpTxCF)
		{
			TpTxConsecutiveFrame();//处于等待连续帧发送状态
		}
		else if(TpTxState.engine != kTxState_Idle)
		{
			TpTxState.engine = kTxState_Idle;
		}
	}
}

void TPRxTask(void)
{
	/* Tp Rx Timer Management */
	if(TpRxState.Timer)
	{
		TpRxState.Timer --;
	}
	if(TpRxState.Timer == 0)
	{
		/* Tp Rx Time Out!!! */
		if(TpRxState.engine == kRxState_WaitFC)//主机接收端需要进行流控处理
		{
			TpRxState.engine = kRxState_WaitForFCConfIsr;//等待流控发送完成确认
			CANDrvTxTask();
		}
		else if((TpRxState.engine != kRxState_CanFrameReceived) && (TpRxState.engine != kRxState_ApplInformed))
		{
			TpRxState.engine = kRxState_Idle;
		}
		else if((TpRxState.engine == kRxState_ApplInformed) && (TpTxState.engine == kTxState_Idle))
		{
			TpRxState.engine = kRxState_Idle;
		}
	}
}

//主机在发送的时候接收到流控帧，则需要控制流量
//主机在接收的时候发送流控制给诊断仪控制流量传输
void TPRxProcess(INT8U cMsgIndex, INT8U cCANIDInd)//接收CAN物理层诊断数据时调用
{
	static INT8U s_blockCnt = 0;
	INT8U cTPMsgType;
	INT8U cTPMsgParameter;
	INT16U wDataLen;
	INT16U  wIndex;
	if(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength != 8)//诊断数据一帧刚好是8字节
	{
		/* Formate error! Ignore it. Only for Ford */
		cTpRxErrorType = N_INVALID_MSG_DATA_LENGTH;
		return;
	}

	//TP 帧类型
	cTPMsgType = (CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[0] & TP_MSG_TYPE_MASK) >> 4;
	
	cTPMsgParameter = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[0] & TP_MSG_PARAMETER_MASK;
	if((TpRxState.engine == kRxState_CanFrameReceived) ||\
		((TpRxState.engine == kRxState_ApplInformed) && (TpTxState.engine != kTxState_Idle) && (cTPMsgType != TP_MSG_FC)))
	{
		/* There is Request has not response yet */
		/*{
			static INT8U test;
			test++;
		}*/
		return;
	}
	switch(cTPMsgType)
	{
		case TP_MSG_SF:   /* Single Frame */
			if(TpRxState.engine != kRxState_Idle)
			{
				/* Accept it and look it as a new request */
				cTpRxErrorType = N_UNEXP_PDU;
			}
			if((cTPMsgParameter == 0) || (cTPMsgParameter > SF_MAX_DATA_LENGTH))
			{
				/* Invalid Single Frame Data Length, Ignore the single frame request */
				cTpRxErrorType  = N_INVALID_SF_DATA_LENGTH;
				return;
			}
			/*
			TpRxInfoStruct.cCANIDIndex = cCANIDInd;
			TpRxInfoStruct.wDataIndex = 0;
			TpRxInfoStruct.wDataLength = cTPMsgParameter;
			for(wIndex = 0; wIndex < cTPMsgParameter; wIndex++)
			{
				TpRxInfoStruct.cDataBuf[wIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1 + wIndex];
			}
			TpRxState.engine = kRxState_CanFrameReceived;//所有帧都接收完
			*/
			if (TpTesterFrameHandle(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData, CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength) == TRUE)//3E处理 zjx 20220602
			{	
				TpRxInfoStruct.cCANIDIndex = cCANIDInd;
				TpRxInfoStruct.wDataIndex = 0;
				TpRxInfoStruct.wDataLength = cTPMsgParameter;
				for(wIndex = 0; wIndex < SF_MAX_DATA_LENGTH; wIndex++)
				{
					TpRxInfoStruct.cDataBuf[wIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1 + wIndex];
				}
				TpRxState.engine = kRxState_CanFrameReceived;//所有帧都接收完
				
			}
			break;
		case TP_MSG_FF:		/* First Frame */
			if(TpRxState.engine != kRxState_Idle)
			{
				/* Accept it and look it as a new request */
				cTpRxErrorType = N_UNEXP_PDU;
			}
			wDataLen = cTPMsgParameter;
			wDataLen <<= 8;
			wDataLen |= (INT16U)(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1]);
			if(wDataLen <= FF_MIN_DATA_LENGTH)
			{
				/* Invalid First Frame Data Length, Ignore the first frame request */
				cTpRxErrorType  = N_INVALID_FF_DATA_LENGTH;
				return;
			}
			else if(wDataLen > TP_RX_DATA_BUF_SIZE)		//这次传输的有效总字节，除了一些标志
			{
				/* Rx Data Buffer is too small to accept the request data */
				cTpRxErrorType = N_BUFFER_OVFLW;
				/* Send a FlowControl N_PDU with the parameter FlowStatus = Overflow. */
				TpRxInfoStruct.cFCStatus = FC_STATUS_OVER_FLOW;		//如果数据超出buffer大小则反馈的流控帧溢出
				TpRxInfoStruct.cBlockSize = FC_BLOCK_SIZE;
				TpRxInfoStruct.cSTMin = FC_STMIN;            //0;  FOR GW  BCM
				cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;//需要流控
				TpRxState.engine = kRxState_Idle;
				return;
			}
			
			if(cCANIDInd == TST_FunctionalReq)
 			{
 				TpRxState.engine = kRxState_Idle;
				TpTxState.engine = kTxState_Idle;
 				return;
 			}
			
			TpRxInfoStruct.cCANIDIndex = cCANIDInd;
			TpRxInfoStruct.wDataIndex = FF_DATA_LENGTH;//首帧已拷贝了FF_DATA_LENGTH字节有效数据
			TpRxInfoStruct.wDataLength = wDataLen;//全部数据长度
			for(wIndex = 0; wIndex < FF_DATA_LENGTH; wIndex++)
			{
				TpRxInfoStruct.cDataBuf[wIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2 + wIndex];
			}
			s_blockCnt = 0;
			TpRxState.cBSCounter = 0;
			TpRxInfoStruct.cSequenceNumber = 0;
			TpRxState.engine = kRxState_WaitFC;
			TpRxState.Timer = TP_RX_WAIT_TO_SEND_FC_TIME;
			TpRxInfoStruct.cFCStatus = FC_CONTINUE_TO_SEND;//接收完首帧FF后发送FC提示继续发送
			TpRxInfoStruct.cBlockSize = FC_BLOCK_SIZE;
			TpRxInfoStruct.cSTMin = FC_STMIN;
			cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;
			if(TpRxState.Timer == 0)
			{
				/* Send the Flow Control immediately */
				CANDrvTxTask();							//等待发送流控帧，不会进入此发送流控帧，在TPRxTask发送
				TpRxState.engine = kRxState_WaitCF;
				TpRxState.Timer = TP_RX_WAIT_CF_TIME;
			}
			/* Send a FlowControl N_PDU with the parameter FlowStatus = Continue to Send. */
			break;
		case TP_MSG_CF:	 /* Consecutive Frame */
 			if(cCANIDInd == TST_FunctionalReq)
 			{
 				TpRxState.engine = kRxState_Idle;
				TpTxState.engine = kTxState_Idle;
 				return;
 			}
			if(TpRxState.engine != kRxState_WaitCF)//需要当前处于等待连续帧状态
			{
				/* Ignore it */
				cTpRxErrorType = N_UNEXP_PDU;
				return;
			}
			s_blockCnt++;
			TpRxInfoStruct.cSequenceNumber ++;
			if(TpRxInfoStruct.cSequenceNumber > 0x0f)
			{
				TpRxInfoStruct.cSequenceNumber = 0;
			}
			/* Check sequence number */
			if(cTPMsgParameter != TpRxInfoStruct.cSequenceNumber)//是否符合顺序
			{
				/* Sequence number error */
				cTpRxErrorType = N_WRONG_SN;
				TpRxState.engine = kRxState_Idle;
				return;
			}
			if(TpRxInfoStruct.cCANIDIndex != cCANIDInd)//判断当前帧的CANID与首帧(FF)获取的CANID是否一致
			{
				/* Deferent CAN ID request, Ignore the request */
				cTpRxErrorType = N_DEFFERENT_CAN_ID_RQ;
				return;
			}
			wIndex = 1;
			for(; TpRxInfoStruct.wDataIndex < TpRxInfoStruct.wDataLength; TpRxInfoStruct.wDataIndex++)
			{
				if(wIndex >= 8)
					break;
				TpRxInfoStruct.cDataBuf[TpRxInfoStruct.wDataIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[wIndex];//拷贝CF帧的数据到Buf
				wIndex ++;
			}
			TpRxState.Timer = TP_RX_WAIT_CF_TIME;
			if(TpRxInfoStruct.wDataLength <= TpRxInfoStruct.wDataIndex)
			{
				/* This is the last data frame */
				TpRxState.engine = kRxState_CanFrameReceived;//所有帧都接收完
				break;
			}
			if(s_blockCnt == FC_BLOCK_SIZE)
			{
				cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;
				s_blockCnt = 0;
			}
			break;
		case TP_MSG_FC://主机收到流控帧，按照帧的指示来控制流量的发送
			if(cCANIDInd == TST_FunctionalReq)
 			{
 				TpRxState.engine = kRxState_Idle;
				TpTxState.engine = kTxState_Idle;
 				return;
 			}

			//发送状态机发送完FF帧以后会进入该状态
			if((TpTxState.engine == kTxState_WaitFC) || (TpTxState.engine == kTxState_WaitForFFConfIsr))
			{
				if(cTPMsgParameter == FC_CONTINUE_TO_SEND)//0 继续发送	1 等待	2 溢出
				{
					TpTxInfoStruct.cBlockSize = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1];//允许一次连续发送CF的数量
					//TpTxInfoStruct.cSequenceNumber = 1; /*modify for diagnostic 20090731*/
					if(FirstFCflg == FALSE)
					{
						TpTxInfoStruct.cSTMin = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2];//发送要求时间
						FirstcSTMin = TpTxInfoStruct.cSTMin;

					}
					else
					{
						TpTxInfoStruct.cSTMin = FirstcSTMin;
					}
					FirstFCflg = TRUE;

					if(TpTxInfoStruct.cSTMin <= 0x7f)
					{
						TpTxInfoStruct.cSTMin = TpTxInfoStruct.cSTMin / TP_TASK_CALL_CYCLE_TIME;
					}
					else if((TpTxInfoStruct.cSTMin >= 0xf1) && (TpTxInfoStruct.cSTMin <= 0xF9))
					{
						/*modify for diagnostic 20090731*/
						TpTxInfoStruct.cSTMin = 0;
					}
					else
					{
						TpTxInfoStruct.cSTMin = 0x7f / TP_TASK_CALL_CYCLE_TIME;
					}
					if(TpTxInfoStruct.cSTMin == 0)
					{
						TpTxInfoStruct.cSTMin = 1; /* Force Tp to send the respone frame every TP_TASK_CALL_CYCLE_TIME */
					}
					TpTxState.engine = kTxState_WaitForTpTxCF;
					TpTxState.Timer = TpTxInfoStruct.cSTMin + 1;/* 第一帧连续帧发送时间 + 1,修复第一帧连续帧与流控帧的时间间隔小于stmin时间问题*/
					if(TpTxState.Timer == 0)                       /*modify for  gwm 20110713*/
					{
						/* You need to send Consecutive Frame immediately */
						TpTxConsecutiveFrame();
					}
				}
				else if(cTPMsgParameter == FC_WAIT)
				{
					//TpTxState.Timer = TP_TX_WAIT_FC_TIME;     /*del    for  gwm 20110713*/
					TpTxState.engine = kTxState_Idle;  			 /*modify  for  DFMC 201202*/
				}
				else if(cTPMsgParameter == FC_STATUS_OVER_FLOW)
				{
					/* Tp Tx Data is too big in size to be send! */
					//AppTpTxDataSizeExceeded();
				}
			}
			break;
		default:
			cTpRxErrorType = N_INVALID_MSG_TYPE;
			return;
			//break;
	}
}


void TPTxProcess(void)//发送完成处理
{
	switch(TpTxState.engine)
	{
		case kTxState_WaitForSFConfIsr://SF帧发送完成处理
			/* Single Frame Successfully Transmited */
			TpTxState.engine = kTxState_Idle;
			TpRxState.engine = kRxState_Idle;
			break;
		case kTxState_WaitForFFConfIsr://FF帧发送完成处理
			/* First Frame Successfully Transmited */
			TpTxState.Timer = TP_TX_WAIT_FC_TIME;//发送完FF以后等待流控
			TpTxState.engine = kTxState_WaitFC;
			break;
		case kTxState_WaitForCFConfIsr:
			if(TpTxInfoStruct.cBlockSize == 0)//Blocksize = 0: 再无流控制帧
			{
				/* Send All Message */
				TpTxState.engine = kTxState_WaitForTpTxCF;
				TpTxState.Timer = TpTxInfoStruct.cSTMin + 1; //for test 20090915
				if(TpTxState.Timer == 0)
				{
					/* You need to send Consecutive Frame immediately */
					TpTxConsecutiveFrame();
				}
			}
			else
			{
				/* Send Block Data */
				if(TpTxState.cBSCounter >= (TpTxInfoStruct.cBlockSize - 1)) /*modify for diagnostic 20090731*/
				{
					/* Wait For Flow Control */
					TpTxState.engine = kTxState_WaitFC;//处于流控状态，发送完blocksize后又进入等待流控帧状态
					TpTxState.Timer = TP_TX_WAIT_FC_TIME;
					TpTxState.cBSCounter = 0;
				}
				else
				{
					TpTxState.cBSCounter ++;
					TpTxState.engine = kTxState_WaitForTpTxCF;
					TpTxState.Timer = TpTxInfoStruct.cSTMin + 1; //for test 20090915
					if(TpTxState.Timer == 0)
					{
						/* You need to send Consecutive Frame immediately */
						TpTxConsecutiveFrame();
					}
				}
			}
			break;
		case kTxState_WaitForLastCFConfIsr:
			TpTxState.engine = kTxState_Idle;
			TpRxState.engine = kRxState_Idle;
			break;
		default:
			break;
	}
}

void TpTxStart(void)
{
	INT16U  wIndex;
	cDescRespNoSend = FALSE;
	for(wIndex = 0; wIndex < 8; wIndex ++)
	{
		cTpTxBuf[wIndex] = DIAG_DEFAULT_VALUE;
	}
	
	if(TpTxInfoStruct.wDataLength <= SF_MAX_DATA_LENGTH_WITH_STD_ADDR)//需要发送的数据长度< 7，则使用单帧发送
	{
		/* Send single frame */
		cTpTxBuf[0] = (TP_MSG_SF << 4) | (((INT8U)(TpTxInfoStruct.wDataLength)) & 0x0f);
		for(wIndex = 0; wIndex < TpTxInfoStruct.wDataLength; wIndex ++)
		{
			cTpTxBuf[wIndex + 1] = TpTxInfoStruct.cDataBuf[wIndex];
		}
		TpTxState.engine = kTxState_WaitForSFConfIsr;
		TpTxState.Timer = TP_TX_WAIT_SF_CONFIRM_TIME;
		cMsgNeedTxIndFlag |=  TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
		CANDrvTxTask();
	}
	else if(TpTxInfoStruct.wDataLength <= TP_MAX_TX_SIZE)
	{
		/* Send First Frame */
		FirstFCflg = FALSE; /*modify for GWM 20110713*/	//流控标志
		cTpTxBuf[0] = (TP_MSG_FF << 4) | (((INT8U)(TpTxInfoStruct.wDataLength >> 8)) & 0x0f);
		cTpTxBuf[1] = (INT8U)(TpTxInfoStruct.wDataLength);
		for(wIndex = 0; wIndex < FF_DATA_LENGTH; wIndex ++)
		{
			cTpTxBuf[wIndex + 2] = TpTxInfoStruct.cDataBuf[wIndex];
		}
		TpTxInfoStruct.wDataReadIndex = FF_DATA_LENGTH;
		TpTxState.engine = kTxState_WaitForFFConfIsr;//发送完进入接收流控状态
		TpTxState.cBSCounter = 0;
		TpTxInfoStruct.cSequenceNumber = 1; /*modify for diagnostic 20090731*/
		TpTxState.Timer = TP_TX_WAIT_FF_CONFIRM_TIME;
		cMsgNeedTxIndFlag |=  TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
		CANDrvTxTask();
		//发送完会进入接收流控帧，然后kTxState_WaitForTpTxCF进入连续帧发送
	//	DescRdDTC_vogTpTxBufFreeCallBack();
	}
	else
	{
		/* Tp Tx Size Error! */
		TpTxState.engine = kTxState_Idle;
	}
}

void TpTxConsecutiveFrame(void)
{
	INT16U  wIndex2;
	INT8U  cIndex1;
	for(cIndex1 = 0; cIndex1 < 8; cIndex1 ++)
	{
		cTpTxBuf[cIndex1] = DIAG_DEFAULT_VALUE;
	}
	cTpTxBuf[0] = (TP_MSG_CF << 4) | (TpTxInfoStruct.cSequenceNumber & 0x0f);
	TpTxInfoStruct.cSequenceNumber ++;
	if(TpTxInfoStruct.cSequenceNumber > 0x0f)
		TpTxInfoStruct.cSequenceNumber = 0;
	cIndex1 = 1;
	wIndex2 = TpTxInfoStruct.wDataReadIndex % TP_TX_DATA_BUF_SIZE;
	for(; TpTxInfoStruct.wDataReadIndex < TpTxInfoStruct.wDataLength; TpTxInfoStruct.wDataReadIndex ++)
	{
		if(cIndex1 >= 8)
			break;
		if(wIndex2 >= TP_TX_DATA_BUF_SIZE)
			wIndex2 = 0;
		cTpTxBuf[cIndex1] = TpTxInfoStruct.cDataBuf[wIndex2];//拷贝需要发送的数据到cTpTxBuf，限制为8字节
		wIndex2 ++;
		cIndex1 ++;
	}
	if(TpTxInfoStruct.wDataReadIndex >= TpTxInfoStruct.wDataLength)
	{
		TpTxState.engine = kTxState_WaitForLastCFConfIsr;//发送最后一帧,全部发送完
	}
	else
	{
		TpTxState.engine = kTxState_WaitForCFConfIsr;///连续发送
	}
	TpTxState.Timer = TP_TX_WAIT_CF_CONFIRM_TIME;
	cMsgNeedTxIndFlag |=  TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;//物理响应call: CANDrvDescPhysicalRespTxProcess
	CANDrvTxTask();
//	DescRdDTC_vogTpTxBufFreeCallBack();
}
/**
 *
 * TP层处理3E服务 
 * add by zjx in 20220602
 *
**/
static BOOL TpTesterFrameHandle(INT8U *pdata, INT8U len)
{
	INT8U  i;
	BOOL ret = FALSE;

	do
	{
	/*
		if (TpRxState.engine == kRxState_Idle)
		{
			// 空闲接收的第一次报文
			ret = TRUE;
			break;
		}
	*/
		
		if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x00)
		{
			// 需响应02 7e 00				
			for (i = 0; i < D_UDS_TP_FRAME_LEN; i++)
			{
				cTpTxBuf[i] = DIAG_DEFAULT_VALUE;
			}

			cTpTxBuf[0] = 0x02;
			cTpTxBuf[1] = 0x7e;
			cTpTxBuf[2] = 0x00;
			//Hal_SetMsgNeedTxIndFlagMask(D_DIAG_PHY_RESP_NEED_TX_FLAG_MASK);
			//UdsCan_LData_TransferHandle();
			cMsgNeedTxIndFlag |= TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
			CANDrvTxTask();
			// 需重置会话时间
			cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x80)
		{
			// 需重置会话时间，无需响应
			cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else
		{
			ret = TRUE;
		}
	} while (0);
	

	return ret;
}


