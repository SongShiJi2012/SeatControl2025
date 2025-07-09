#include   "BootCan.h"
#include   "BootTp.h"
#include   "BootCanDrv.h"
#include   "BootDesc.h"
#include "ecual_can.h"
#include "Bootloader.h"
#include "CpuPeripheralInit.h"
#include "kf32a156_gpio.h"

stCANMsgRxType 			BootCANMsgRxDrv;
stCANMsgTxType 			BootCANMsgTxDrv;
BOOL        	BootCANInitOKFlag;

#define CANRXMAILBOXSTARTINDEX		D_CANFD_MAILBOX_RX_START /*CAN������ʼ����*/
#define CANTXMAILBOXSTARTINDEX		D_CANFD_MAILBOX_TX_START /*CAN������ʼ����*/
#define  D_CANDRVMSCAN_MAX_TIME   	100 //1ms ����  100ms
#define CANMAINRXNUM		D_CANFD_MAILBOX_RX_NUM /*��Ҫ���յ�CANID��*/
strCanMainMailboxRxbuffCfg CanMainMailboxRxbuffCfg[CANMAINRXNUM] =
{
		/*Ӧ�ñ���    �˲�����0���˲���1�����˲�*/
	{FALSE,CANRXMAILBOXSTARTINDEX+0u,FLEXCAN_MSG_ID_STD,BOOTDESC_REQID_PHY,0x000,{0}}, 	/*���������������������� CAN ��ʶ��*/
	{FALSE,CANRXMAILBOXSTARTINDEX+1u,FLEXCAN_MSG_ID_STD,BOOTDESC_REQID_FUC,0x000,{0}},	/*����������� ECU ���͹���������ʱ�� CAN ��ʶ��*/
};

#define CANMAINTXNUM		D_CANFD_MAILBOX_TX_NUM /*��Ҫ���͵�CANID��*/
strCanMainMailboxTxbuffCfg CanMainMailboxTxbuffCfg[CANMAINTXNUM] =
{
	{FALSE,CANTXMAILBOXSTARTINDEX+0u,0,{0}},//�����䷢�͸�Ϊ�����䷢�� �����䷢��ʧ��ʱ�򣬵ײ��޷��ж����ĸ�����ʧ�� �޷��ط�  20230110
//	{FALSE,CANTXMAILBOXSTARTINDEX+0u,0,{0}},
//	{FALSE,CANTXMAILBOXSTARTINDEX+0u,0,{0}},
};

static INT8U s_BootCanTxtimer = 0;

uint8_t Can_transmit_repeat(Canfd_MailboxHeaderType* MailBoxTx,Can_MailboxNumType TxMailIndex)
{
	/*48M  0x003fff:7ms, 0x00ffff:28ms, 0x016000:39ms  0x01ffff:57ms
			 * 0x03ffff:123ms, 0x07ffff:231ms, 0x0fffff:462ms  0xffffff:7s*/
	volatile int overtime1 = 0x3fff;
	volatile int overtime2 = 0xffff;
	volatile uint8_t ret = 0;
	volatile Kf32a_Canfd_Reg *ControllerRegPtr = (Kf32a_Canfd_Reg *)Can_m_ControllersInfo[CANfd6].BaseAddress;

	s_BootCanTxtimer = 0;
	/*copy data*/
//	INT_All_Enable(FALSE);
	while((!ret)&&(overtime1--))
	{
		if((ControllerRegPtr->CANFD_CTLR0.B.TCSTA == 0x01)||(ControllerRegPtr->CANFD_CTLR0.B.TXSTA == 0x00))
		{
			GPIO_Toggle_Output_Data_Config(GPIOF_SFR,GPIO_PIN_MASK_14);
			if(Can_m_FdMailBox_Write(CANfd6,TxMailIndex,MailBoxTx) != CAN_OK)
			{
				//failed !!!
				ret = 0;
				Can_m_FdTransmit(CANfd6);
			}
			else
			{
				//success !!!
				Can_m_FdTransmit(CANfd6);
//				while((ControllerRegPtr->CANFD_CTLR0.B.TXSTA == 1)&&(overtime2--));
//				while((ControllerRegPtr->CANFD_CTLR0.B.TCSTA == 0)&&(overtime2--));

				if(overtime2 < 0)
				{
					//failed overtime
					ret = 0;
				}
				else
				{
					ret = 1;
				}
			}
		}
		else
		{
			//failed !!!
			ret = 0;
			Can_m_FdTransmit(CANfd6);
		}
	}
//	INT_All_Enable(TRUE);

	if(overtime1<0)
		return 0;  //failed
	else
		return 1;  //success
}

/***********************************************************************************************
 * @function name: void BootCAN_CheckARBSTART(void)
 * @description:     о��΢оƬ���Ͷ�֡����Ҫһ��ʱ���ڼ���ٲ�ʧ��
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2023-3-1 czb
 ***********************************************************************************************/
void BootCAN_CheckARBSTART(void)
{
	if(D_CANDRVMSCAN_MAX_TIME > s_BootCanTxtimer)
	{
		s_BootCanTxtimer++;

		if(CanMainMailboxTxbuffCfg[0].BusyFlag == TRUE)
		{
			Can_m_FdTransmit(CANfd6);
		}
	}
}


void BootCANTRX(INT8U InIntFlag)
{
	INT8U i=0,j=0,u1tDataLen=0;
	volatile INT8U *pu1tData;
	Canfd_MailboxHeaderType* MailBoxTxbuffCfg = NULL;
	volatile Kf32a_Canfd_Reg *ControllerRegPtr = (Kf32a_Canfd_Reg *)Can_m_ControllersInfo[0].BaseAddress;

    INT8U ConFlg = 0;
    INT8U SendFlg = 0;
    static INT16U s_ReadPoint = 0xFFFF;

	while(BootCANMsgTxDrv.cMsgNum > 0u)
	{
		if(BootCANMsgTxDrv.cReadPointer >= BOOT_MAX_CAN_MSG_TX_BUF_SIZE)
		{
			BootCANMsgTxDrv.cReadPointer = 0;
		}
		for(i=0;i<CANMAINTXNUM;i++)
		{
			MailBoxTxbuffCfg = &CanMainMailboxTxbuffCfg[i].TxBuff;
			MailBoxTxbuffCfg->Can_id = CAN_DATA_STANDARD ;
			MailBoxTxbuffCfg->FrameData.Data_Length = Data_Length_8;
			MailBoxTxbuffCfg->Can_frame = CAN_FRAME_CLASSICAL;
			MailBoxTxbuffCfg->BRS = CANFD_BRS_DISABLE;
			MailBoxTxbuffCfg->TransceiveType = MAIL_TRANSMIT;
			MailBoxTxbuffCfg->Timestamp = 0;

			if(CanMainMailboxTxbuffCfg[i].BusyFlag==FALSE)
			{
				s_BootCanTxtimer = 0;
				CanMainMailboxTxbuffCfg[i].BusyFlag=TRUE;

				pu1tData = BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cReadPointer].cData;
				u1tDataLen = BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cReadPointer].cDataLength;
				for(j = 0; j < u1tDataLen; j++)
				{
					MailBoxTxbuffCfg->FrameData.U8Data[j] = *(pu1tData++);
				}
				CanMainMailboxTxbuffCfg[i].CanTxId = BootCANMsgTxDrv.CANMsgBuf[BootCANMsgTxDrv.cReadPointer].cCANIDIndex;

				MailBoxTxbuffCfg->FrameData.Data_Length  = u1tDataLen;

				MailBoxTxbuffCfg->Id = CanMainMailboxTxbuffCfg[i].CanTxId;
#if 0
				BootCANMsgTxDrv.cMsgNum --;
				BootCANMsgTxDrv.cReadPointer++;

				/* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
		    	ecual_CAN_ConfigTxMb(INST_CAN0, CanMainMailboxTxbuffCfg[i].MailBoxIndex, MailBoxTxbuffCfg);
				/* Execute send non-blocking */
				ecual_CAN_sendOnce(INST_CAN0, FALSE, &(CanMainMailboxTxbuffCfg[i]), MailBoxTxbuffCfg);


				if(InIntFlag==FALSE)
				{
				#if 0
					if((cDescECUHardRestAnswerIndex == CANMsgTxDrv.cReadPointer) && (cDescECUHardRestReq))
					{
						cDescECUHardRestAnswerFnish =  TRUE;
					}
				#endif
				}
#else
				/* �����ٲ�ʧ�ܣ��ж��ط����ص�����״̬�����·��� */
				if(D_CANDRVMSCAN_MAX_TIME <= s_BootCanTxtimer || (s_ReadPoint == BootCANMsgTxDrv.cReadPointer))
				{
					ControllerRegPtr->CANFD_CTLR0.B.TXR = 0x00;
					ControllerRegPtr->CANFD_CTLR0.B.ATX = 0x01;
					asm("nop");asm("nop");asm("nop");
					ControllerRegPtr->CANFD_CTLR0.B.ATX = 0x00;
					ControllerRegPtr->CANFD_CTLR0.B.TXR = 0x01;
				}

				ConFlg = ecual_CAN_ConfigTxMb(INST_CAN0, CanMainMailboxTxbuffCfg[i].MailBoxIndex, MailBoxTxbuffCfg);
				/* Execute send non-blocking */
				if(CAN_OK == ConFlg)
				{
					SendFlg = ecual_CAN_sendOnce(INST_CAN0, FALSE, &(CanMainMailboxTxbuffCfg[i]), MailBoxTxbuffCfg);
				}

				if((CAN_OK == ConFlg) && (TRUE == SendFlg))
				{
					s_BootCanTxtimer = 0;
					CanMainMailboxTxbuffCfg[i].BusyFlag = TRUE;
					BootCANMsgTxDrv.cMsgNum --;
					BootCANMsgTxDrv.cReadPointer++;
					Boot_TP_u1gPhisicalRspTxFnshFlg = TRUE;

				}
#endif
				break;
			}
			else
			{
				if(D_CANDRVMSCAN_MAX_TIME <= s_BootCanTxtimer)
				{
					CanMainMailboxTxbuffCfg[i].BusyFlag = FALSE;
				}
			}
		}

		if(i>=CANMAINTXNUM) /*I??OIDOEIa,Io3o???I.cEI*/
		{
			break;
		}
	}
}

void BootCANREC(INT32U CANID,INT8U *pBuff,INT8U len)
{
	volatile INT8U *pu1tData;
	INT8U u1tIdx;

	if(BootCANMsgRxDrv.cMsgNum < BOOT_MAX_CAN_MSG_RX_BUF_SIZE)
	{
		if(BootCANMsgRxDrv.cWritePointer >= BOOT_MAX_CAN_MSG_RX_BUF_SIZE)
		{
			BootCANMsgRxDrv.cWritePointer = 0;
		}
			
		BootCANMsgRxDrv.CANMsgBuf[BootCANMsgRxDrv.cWritePointer].cCANID = CANID;
		pu1tData = BootCANMsgRxDrv.CANMsgBuf[BootCANMsgRxDrv.cWritePointer].cData;
		//�ɵ�sdk��busoff��ʱ�� ��������ݳ��ȴ���8�����   С��8��ʱ����Ӧ�ò�ᶪ�� ������  - �µ�sdk��ʱû�������ݳ��ȴ��� - 20230718
		if(len > 8)
		{
			len = 8;
		}
		for(u1tIdx = 0; u1tIdx < len; u1tIdx ++)
		{
			pu1tData[u1tIdx] = pBuff[u1tIdx];
		}
		BootCANMsgRxDrv.CANMsgBuf[BootCANMsgRxDrv.cWritePointer].cDataLength = len;//�߸�������� ���Ȼ����
		BootCANMsgRxDrv.cWritePointer ++;
		BootCANMsgRxDrv.cMsgNum ++;
#if CANTXDEBUG
		GPIO_Set_Output_Data_Bits(GPIOF_SFR,GPIO_PIN_MASK_14,Bit_SET);
		GPIO_Set_Output_Data_Bits(GPIOF_SFR,GPIO_PIN_MASK_14,Bit_RESET);
#endif
	}
}

void 	BootCANERR(void)
{
}


/**************************************************************************
* �������ƣ�void CanMainRxTxCallFunc(INT8U instance, flexcan_event_type_t eventType,flexcan_state_t *flexcanState)
* ����������CAN���շ�������жϵ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
***************************************************************************/
void CanMainRxTxCallFunc(INT8U instance, flexcan_event_type_t eventType,uint32_t buffIdx,flexcan_state_t *flexcanState)
{
	INT8U i=0;
	INT32U CANId=0;
	INT8U CANLen = 0;
	Canfd_MailboxHeaderType* MailBoxRxbuffCfg = NULL;

	/*�������*/
	if(eventType==FLEXCAN_EVENT_RX_COMPLETE)
	{
		for(i=0;i<CANMAINRXNUM;i++)
		{
			if(buffIdx == CanMainMailboxRxbuffCfg[i].MailBoxIndex)
			{
				CanMainMailboxRxbuffCfg[i].NewFrameFlag=TRUE;

				MailBoxRxbuffCfg = &CanMainMailboxRxbuffCfg[i].RxBuff;
				CANId = MailBoxRxbuffCfg->Id;
				CANLen = MailBoxRxbuffCfg->FrameData.Data_Length;

				BootCANREC(CANId, MailBoxRxbuffCfg->FrameData.U8Data,CANLen);
				/* Start receiving data in RX_MAILBOX. */
				FLEXCAN_DRV_Receive(instance,buffIdx, MailBoxRxbuffCfg);

			}
		}
	}
	/*�������*/
	if(eventType==FLEXCAN_EVENT_TX_COMPLETE)
	{
		for(i=0;i<CANMAINTXNUM;i++)
		{
			//if(FLEXCAN_DRV_GetTransferStatus(instance, CanMainMailboxTxbuffCfg[i].MailBoxIndex) == STATUS_SUCCESS)
			if(buffIdx == CanMainMailboxTxbuffCfg[i].MailBoxIndex)
			{
				CanMainMailboxTxbuffCfg[i].BusyFlag=FALSE;
//				BootCANTRX(TRUE);//ͬ��app �����жϷ���
			}
		}
	}
}


void CANDrvMSCAN_vogErrIntRoutine(uint8_t instance, flexcan_event_type_t eventType,flexcan_state_t *flexcanState)
{
	BootCANDrvInit();
	BootCANaFCANinit();

	BootTPInit();
	BootDescInit();
}

void BootCANaFCANinit(void)
{
	INT8U i=0;
	INT8U CfgRxMbTimeCnt = 0;
	INT8U Ret = FALSE;
	Canfd_MailboxHeaderType* MailBoxRxbuffCfg = NULL;

	Boot_DisableInterrupts;
	for(i = 0; i < CANMAINRXNUM; i++)
	{
		ecual_CAN_SetHwFilter(INST_CAN0,&CanMainMailboxRxbuffCfg[i]);
	}
	ecual_CAN_init(INST_CAN0, CanMainRxTxCallFunc, CANDrvMSCAN_vogErrIntRoutine, NULL);

    for(i=0;i<CANMAINRXNUM;i++)
    {    
    	MailBoxRxbuffCfg = &CanMainMailboxRxbuffCfg[i].RxBuff;

		MailBoxRxbuffCfg->Can_id = CAN_DATA_STANDARD ;
		MailBoxRxbuffCfg->FrameData.Data_Length = Data_Length_8;
		MailBoxRxbuffCfg->Can_frame = CAN_FRAME_CLASSICAL;
		MailBoxRxbuffCfg->BRS = CANFD_BRS_DISABLE;
		MailBoxRxbuffCfg->TransceiveType = MAIL_RECEIVE;
		MailBoxRxbuffCfg->Timestamp = 0;
		MailBoxRxbuffCfg->Id = CanMainMailboxRxbuffCfg[i].CanRxId;

		CfgRxMbTimeCnt = 3;
		while(CfgRxMbTimeCnt)
		{
			/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
			Ret = ecual_CAN_ConfigRxMb(INST_CAN0, CanMainMailboxRxbuffCfg[i].MailBoxIndex, MailBoxRxbuffCfg);
			if(TRUE == Ret)
			{
				break;
			}
			CfgRxMbTimeCnt--;
		}
		/* Start receiving data in RX_MAILBOX. */
		ecual_CAN_receive(INST_CAN0, CanMainMailboxRxbuffCfg[i].MailBoxIndex,MailBoxRxbuffCfg);
	}
	/*?????????*/
	for(i = 0; i < CANMAINRXNUM; i++)
	{
		CanMainMailboxRxbuffCfg[i].NewFrameFlag=FALSE;
	}
	for(i=0;i<CANMAINTXNUM;i++)
	{
		CanMainMailboxTxbuffCfg[i].BusyFlag=FALSE;
	}

	memset(&BootCANMsgTxDrv,0,sizeof(stCANMsgTxType)); /*��շ��ͻ���*/

	BootCANInitOKFlag = TRUE;
	BOOTCANEnable();
	Boot_EnableInterrupts;
}

void BootCANInit(void)
{
	//if(BootCANInitOKFlag == FALSE)
	{
		BootTPInit();
		BootCANDrvInit();
		BootDescInit();
	}
}

void   BootCANTask(void)
{

#ifdef BOOTCAN_PERIODMSGTX
	if(Boot_DownloadFlg == FALSE)
	{
		BootCANDrv_vogTask();
	}
#endif
	BootTPRxTask();
	BootTPTxTask();
	BootCANDrvTask();
	BootDescTask();
	//BootFlashTask();
	BootCANDrvTxTask();
}


void CANTX_TEXT(void)
{
	INT8U TxBuff[8];
	INT8U Ret;
	INT16U ID = 0x123;

	Canfd_MailboxHeaderType dataInfo =
	{
		.Can_id = FLEXCAN_MSG_ID_STD,
		.FrameData.Data_Length = Data_Length_8,
		.Can_frame = CAN_FRAME_CLASSICAL,
		.Id = 0x123,
		.BRS = CANFD_BRS_DISABLE,
		.TransceiveType = MAIL_TRANSMIT,
		.Timestamp = 0U
	};

	static uint16_t timer = 0;

	timer++;
	timer %= 10;

	if(timer != 0)
	{
		return;
	}

    TxBuff[0] = 0;
    TxBuff[1] = 1;
    TxBuff[2] = 2;
    TxBuff[3] = 3;
    TxBuff[4] = 4;
    TxBuff[5] = 5;
    TxBuff[6] = 6;
    TxBuff[7] = 7;

    memcpy(dataInfo.FrameData.U8Data, TxBuff,8);

   // if(FLEXCAN_MB_IDLE == canCom_State[INST_CAN0].mbs[28].state)
    {
		/* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
		Ret = FLEXCAN_DRV_ConfigTxMb(INST_CAN0, 45, &dataInfo, ID);
		/* Execute send non-blocking */
		Ret = FLEXCAN_DRV_Send(INST_CAN0, 45, &dataInfo, ID, &TxBuff[0]);
    }
}


void CANTX_TEXT5000(void)
{
	INT8U i;
	static uint32_t cnt = 0;

	cnt++;

	if(cnt > 50000)
	{
		return;
	}

	Canfd_MailboxHeaderType dataInfo =
	{
		.Can_id = FLEXCAN_MSG_ID_STD,
		.FrameData.Data_Length = Data_Length_8,
		.Can_frame = CAN_FRAME_CLASSICAL,
		.Id = 0x7ff,
		.BRS = CANFD_BRS_DISABLE,
		.TransceiveType = MAIL_TRANSMIT,
		.Timestamp = 0U
	};

    for(i = 0; i<8; i++)
    {
    	dataInfo.FrameData.U8Data[i] = i;
    }

    Can_transmit_repeat(&dataInfo,45);
}

