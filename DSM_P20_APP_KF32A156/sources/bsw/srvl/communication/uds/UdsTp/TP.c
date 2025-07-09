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

//��TpRxInfoStruct�ṹ��ȡ���յ���������ݷ��͸�BPM
volatile tTpRxInfoStruct TpRxInfoStruct;//�ײ�can���յ����ݴ�ŵ��ñ���
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
	if(TP_u1gPhisicalRspTxFnshFlg)//������Ӧ��ɱ�־��������һ֡����
	{
		TP_u1gPhisicalRspTxFnshFlg = FALSE;
		TPTxProcess();
	}
	/* Tp Tx Timer Management */
	if(TpTxState.Timer)
	{
		TpTxState.Timer --;//���Ʒ���ʱ����
	}
	if(TpTxState.Timer == 0)
	{
		/* Tp Tx Time Out */
		if(TpTxState.engine == kTxState_WaitForTpTxCF)
		{
			TpTxConsecutiveFrame();//���ڵȴ�����֡����״̬
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
		if(TpRxState.engine == kRxState_WaitFC)//�������ն���Ҫ�������ش���
		{
			TpRxState.engine = kRxState_WaitForFCConfIsr;//�ȴ����ط������ȷ��
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

//�����ڷ��͵�ʱ����յ�����֡������Ҫ��������
//�����ڽ��յ�ʱ���������Ƹ�����ǿ�����������
void TPRxProcess(INT8U cMsgIndex, INT8U cCANIDInd)//����CAN������������ʱ����
{
	static INT8U s_blockCnt = 0;
	INT8U cTPMsgType;
	INT8U cTPMsgParameter;
	INT16U wDataLen;
	INT16U  wIndex;
	if(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength != 8)//�������һ֡�պ���8�ֽ�
	{
		/* Formate error! Ignore it. Only for Ford */
		cTpRxErrorType = N_INVALID_MSG_DATA_LENGTH;
		return;
	}

	//TP ֡����
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
			TpRxState.engine = kRxState_CanFrameReceived;//����֡��������
			*/
			if (TpTesterFrameHandle(CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData, CANMsgRxDrv.CANMsgBuf[cMsgIndex].cDataLength) == TRUE)//3E���� zjx 20220602
			{	
				TpRxInfoStruct.cCANIDIndex = cCANIDInd;
				TpRxInfoStruct.wDataIndex = 0;
				TpRxInfoStruct.wDataLength = cTPMsgParameter;
				for(wIndex = 0; wIndex < SF_MAX_DATA_LENGTH; wIndex++)
				{
					TpRxInfoStruct.cDataBuf[wIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1 + wIndex];
				}
				TpRxState.engine = kRxState_CanFrameReceived;//����֡��������
				
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
			else if(wDataLen > TP_RX_DATA_BUF_SIZE)		//��δ������Ч���ֽڣ�����һЩ��־
			{
				/* Rx Data Buffer is too small to accept the request data */
				cTpRxErrorType = N_BUFFER_OVFLW;
				/* Send a FlowControl N_PDU with the parameter FlowStatus = Overflow. */
				TpRxInfoStruct.cFCStatus = FC_STATUS_OVER_FLOW;		//������ݳ���buffer��С����������֡���
				TpRxInfoStruct.cBlockSize = FC_BLOCK_SIZE;
				TpRxInfoStruct.cSTMin = FC_STMIN;            //0;  FOR GW  BCM
				cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;//��Ҫ����
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
			TpRxInfoStruct.wDataIndex = FF_DATA_LENGTH;//��֡�ѿ�����FF_DATA_LENGTH�ֽ���Ч����
			TpRxInfoStruct.wDataLength = wDataLen;//ȫ�����ݳ���
			for(wIndex = 0; wIndex < FF_DATA_LENGTH; wIndex++)
			{
				TpRxInfoStruct.cDataBuf[wIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2 + wIndex];
			}
			s_blockCnt = 0;
			TpRxState.cBSCounter = 0;
			TpRxInfoStruct.cSequenceNumber = 0;
			TpRxState.engine = kRxState_WaitFC;
			TpRxState.Timer = TP_RX_WAIT_TO_SEND_FC_TIME;
			TpRxInfoStruct.cFCStatus = FC_CONTINUE_TO_SEND;//��������֡FF����FC��ʾ��������
			TpRxInfoStruct.cBlockSize = FC_BLOCK_SIZE;
			TpRxInfoStruct.cSTMin = FC_STMIN;
			cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;
			if(TpRxState.Timer == 0)
			{
				/* Send the Flow Control immediately */
				CANDrvTxTask();							//�ȴ���������֡���������˷�������֡����TPRxTask����
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
			if(TpRxState.engine != kRxState_WaitCF)//��Ҫ��ǰ���ڵȴ�����֡״̬
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
			if(cTPMsgParameter != TpRxInfoStruct.cSequenceNumber)//�Ƿ����˳��
			{
				/* Sequence number error */
				cTpRxErrorType = N_WRONG_SN;
				TpRxState.engine = kRxState_Idle;
				return;
			}
			if(TpRxInfoStruct.cCANIDIndex != cCANIDInd)//�жϵ�ǰ֡��CANID����֡(FF)��ȡ��CANID�Ƿ�һ��
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
				TpRxInfoStruct.cDataBuf[TpRxInfoStruct.wDataIndex] = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[wIndex];//����CF֡�����ݵ�Buf
				wIndex ++;
			}
			TpRxState.Timer = TP_RX_WAIT_CF_TIME;
			if(TpRxInfoStruct.wDataLength <= TpRxInfoStruct.wDataIndex)
			{
				/* This is the last data frame */
				TpRxState.engine = kRxState_CanFrameReceived;//����֡��������
				break;
			}
			if(s_blockCnt == FC_BLOCK_SIZE)
			{
				cMsgNeedTxIndFlag |= TP_FC_NEED_TX_FLAG_MASK;
				s_blockCnt = 0;
			}
			break;
		case TP_MSG_FC://�����յ�����֡������֡��ָʾ�����������ķ���
			if(cCANIDInd == TST_FunctionalReq)
 			{
 				TpRxState.engine = kRxState_Idle;
				TpTxState.engine = kTxState_Idle;
 				return;
 			}

			//����״̬��������FF֡�Ժ������״̬
			if((TpTxState.engine == kTxState_WaitFC) || (TpTxState.engine == kTxState_WaitForFFConfIsr))
			{
				if(cTPMsgParameter == FC_CONTINUE_TO_SEND)//0 ��������	1 �ȴ�	2 ���
				{
					TpTxInfoStruct.cBlockSize = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[1];//����һ����������CF������
					//TpTxInfoStruct.cSequenceNumber = 1; /*modify for diagnostic 20090731*/
					if(FirstFCflg == FALSE)
					{
						TpTxInfoStruct.cSTMin = CANMsgRxDrv.CANMsgBuf[cMsgIndex].cData[2];//����Ҫ��ʱ��
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
					TpTxState.Timer = TpTxInfoStruct.cSTMin + 1;/* ��һ֡����֡����ʱ�� + 1,�޸���һ֡����֡������֡��ʱ����С��stminʱ������*/
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


void TPTxProcess(void)//������ɴ���
{
	switch(TpTxState.engine)
	{
		case kTxState_WaitForSFConfIsr://SF֡������ɴ���
			/* Single Frame Successfully Transmited */
			TpTxState.engine = kTxState_Idle;
			TpRxState.engine = kRxState_Idle;
			break;
		case kTxState_WaitForFFConfIsr://FF֡������ɴ���
			/* First Frame Successfully Transmited */
			TpTxState.Timer = TP_TX_WAIT_FC_TIME;//������FF�Ժ�ȴ�����
			TpTxState.engine = kTxState_WaitFC;
			break;
		case kTxState_WaitForCFConfIsr:
			if(TpTxInfoStruct.cBlockSize == 0)//Blocksize = 0: ����������֡
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
					TpTxState.engine = kTxState_WaitFC;//��������״̬��������blocksize���ֽ���ȴ�����֡״̬
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
	
	if(TpTxInfoStruct.wDataLength <= SF_MAX_DATA_LENGTH_WITH_STD_ADDR)//��Ҫ���͵����ݳ���< 7����ʹ�õ�֡����
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
		FirstFCflg = FALSE; /*modify for GWM 20110713*/	//���ر�־
		cTpTxBuf[0] = (TP_MSG_FF << 4) | (((INT8U)(TpTxInfoStruct.wDataLength >> 8)) & 0x0f);
		cTpTxBuf[1] = (INT8U)(TpTxInfoStruct.wDataLength);
		for(wIndex = 0; wIndex < FF_DATA_LENGTH; wIndex ++)
		{
			cTpTxBuf[wIndex + 2] = TpTxInfoStruct.cDataBuf[wIndex];
		}
		TpTxInfoStruct.wDataReadIndex = FF_DATA_LENGTH;
		TpTxState.engine = kTxState_WaitForFFConfIsr;//����������������״̬
		TpTxState.cBSCounter = 0;
		TpTxInfoStruct.cSequenceNumber = 1; /*modify for diagnostic 20090731*/
		TpTxState.Timer = TP_TX_WAIT_FF_CONFIRM_TIME;
		cMsgNeedTxIndFlag |=  TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;
		CANDrvTxTask();
		//�����������������֡��Ȼ��kTxState_WaitForTpTxCF��������֡����
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
		cTpTxBuf[cIndex1] = TpTxInfoStruct.cDataBuf[wIndex2];//������Ҫ���͵����ݵ�cTpTxBuf������Ϊ8�ֽ�
		wIndex2 ++;
		cIndex1 ++;
	}
	if(TpTxInfoStruct.wDataReadIndex >= TpTxInfoStruct.wDataLength)
	{
		TpTxState.engine = kTxState_WaitForLastCFConfIsr;//�������һ֡,ȫ��������
	}
	else
	{
		TpTxState.engine = kTxState_WaitForCFConfIsr;///��������
	}
	TpTxState.Timer = TP_TX_WAIT_CF_CONFIRM_TIME;
	cMsgNeedTxIndFlag |=  TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK;//������Ӧcall: CANDrvDescPhysicalRespTxProcess
	CANDrvTxTask();
//	DescRdDTC_vogTpTxBufFreeCallBack();
}
/**
 *
 * TP�㴦��3E���� 
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
			// ���н��յĵ�һ�α���
			ret = TRUE;
			break;
		}
	*/
		
		if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x00)
		{
			// ����Ӧ02 7e 00				
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
			// �����ûỰʱ��
			cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else if (pdata[0] == 0x02 && pdata[1] == 0x3E && pdata[2] == 0x80)
		{
			// �����ûỰʱ�䣬������Ӧ
			cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		else
		{
			ret = TRUE;
		}
	} while (0);
	

	return ret;
}


