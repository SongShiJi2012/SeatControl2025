#include "CANDrvMSCAN.h"
#include "flexcan_driver.h"
#include "DescConfig.h"
#include "kf32a156_canfd.h"
#include "kf32a156_gpio.h"
#include "OsekNm_Cfg.h"
#include "Srvl_NM.h"
#define CANRXMAILBOXSTARTINDEX		D_CANFD_MAILBOX_RX_START /*CAN接收起始邮箱*/
#define CANTXMAILBOXSTARTINDEX		D_CANFD_MAILBOX_TX_START /*CAN发送起始邮箱*/

CANMsgRxType CANMsgRxDrv = {0};
CANMsgTxType CANMsgTxDrv = {0};

#define CANMAINRXNUM		D_CANFD_MAILBOX_RX_NUM /*需要接收的CANID表*/
INT8U CANWakeupFlg = FALSE; //CAN唤醒标志
BOOL s_bCanTxStopFlg = FALSE;//CAN发送停止标志

strCanMainMailboxRxbuffCfg CanMainMailboxRxbuffCfg[CANMAINRXNUM] =
{
    /*应用报文0~7*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 0u, FLEXCAN_MSG_ID_STD, 0x238, 0x000, {0}},        /*PEPS232*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 1u, FLEXCAN_MSG_ID_STD, 0x26E, 0x000, {0}},        /*EMS261*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 2u, FLEXCAN_MSG_ID_STD, 0x281, 0x000, {0}},        /*TCU240 */
    {FALSE, CANRXMAILBOXSTARTINDEX + 3u, FLEXCAN_MSG_ID_STD, 0x283, 0x000, {0}},        /*ESP1B0 */
    {FALSE, CANRXMAILBOXSTARTINDEX + 4u, FLEXCAN_MSG_ID_STD, 0x284, 0x000, {0}},        /*EMS266*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 5u, FLEXCAN_MSG_ID_STD, 0x28E, 0x000, {0}},        /*AC3F2*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 6u, FLEXCAN_MSG_ID_STD, 0x2A7, 0x000, {0}},        /*BCM282*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 7u, FLEXCAN_MSG_ID_STD, 0x2AE, 0x000, {0}},        /*BCM285*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 8u, FLEXCAN_MSG_ID_STD, 0x351, 0x000, {0}},       /*IBS2E5*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 9u, FLEXCAN_MSG_ID_STD, 0x367, 0x000, {0}},       /*PEPS234*/
    /*诊断报文*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 10u, FLEXCAN_MSG_ID_STD, DESC_REQID_PHY, 0x000, {0}},  /*诊断仪向控制器的物理请求 CAN 标识符*/
    {FALSE, CANRXMAILBOXSTARTINDEX + 11u, FLEXCAN_MSG_ID_STD, DESC_REQID_FUC, 0x000, {0}},  /*诊断仪向所有 ECU 发送功能请求报文时的 CAN 标识符*/
    /*网络管理报文*/
    {FALSE, CANRXMAILBOXSTARTINDEX +12u, FLEXCAN_MSG_ID_STD, D_CAN_NM_BASE_ADDR, 0x0FF, {0}},     /*网络管理报文*/

};

#define CANMAINTXNUM		(D_CANFD_MAILBOX_TX_NUM) /*需要发送的CANID表*/
strCanMainMailboxTxbuffCfg CanMainMailboxTxbuffCfg[CANMAINTXNUM] =
{
	{FALSE, CANTXMAILBOXSTARTINDEX + 0u, 0, {0}},
};

//Variables definition----------------------------------------------------------------------
#define CANDrvMSCAN_TXBUFFER_NUM					3
#define CANDrvMSCAN_TxBUFFER0						(0x00u)
#define CANDrvMSCAN_TxBUFFER1						(0x01u)
#define CANDrvMSCAN_TxBUFFER2						(0x02u)

BOOL g_bCANWakeUpFlg = FALSE;
INT8U CanRxMbIdErrIndex = 0; //CAN_MB_ID配置失败序号
/*发送标识,标识已填充过发送的数据,低三位每一位代表一个邮箱号,高五位代表发送的ID类型*/
static INT8U CANDrvMSCAN_u1sTxConfirmFlg[CANDrvMSCAN_TXBUFFER_NUM];

//Module function prototype declaration----------------------------------------------
static void CANDrvMSCAN_vosTxComfirm(INT8U u1tTxBEmptyNum);
static void CANDrvMSCAN_vosSetTxBuffersMsgIDIndex(INT32U MsgID, INT8U u1tTxBNo);

static INT8U s_CANDrvMSCANTxtimer = 0;
#define  D_CANDRVMSCAN_MAX_TIME   	100 //1ms 任务  100ms

uint8_t Can_transmit_repeat(Canfd_MailboxHeaderType* MailBoxTx,Can_MailboxNumType TxMailIndex)
{
	/*48M  0x003fff:7ms, 0x00ffff:28ms, 0x016000:39ms  0x01ffff:57ms
			 * 0x03ffff:123ms, 0x07ffff:231ms, 0x0fffff:462ms  0xffffff:7s*/
	volatile int overtime1 = 0x3fff;
	volatile int overtime2 = 0xffff;
	volatile uint8_t ret = 0;
	volatile Kf32a_Canfd_Reg *ControllerRegPtr = (Kf32a_Canfd_Reg *)Can_m_ControllersInfo[CANfd6].BaseAddress;

	s_CANDrvMSCANTxtimer = 0;
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
 * @description:     芯旺微芯片发送丢帧，需要一段时间内检查仲裁失败
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2023-3-1 czb
 ***********************************************************************************************/
void CANDrvMSCAN_CheckARBSTART(void)
{
	if(D_CANDRVMSCAN_MAX_TIME > s_CANDrvMSCANTxtimer)
	{
		s_CANDrvMSCANTxtimer++;

		if(CanMainMailboxTxbuffCfg[0].BusyFlag == TRUE)
		{
		    Can_m_FdTransmit(CANfd6);
		}
	}
}
/***********************************************************************************************
 * @function name: CANDrv_GetCanTxStopFlag
 * @description: 获取CAN发送停止标志位状态
 * @input parameters: void
 * @output parameters: void
 * @return: BOOL 当前CAN发送是否被停止
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
BOOL CANDrv_GetCanTxStopFlag(void)
{
    return s_bCanTxStopFlg;
}
/***********************************************************************************************
 * @function name: CANDrv_SetCanTxStopFlag
 * @description: 设置CAN发送停止标志位状态
 * @input parameters:
 *     BOOL bFlagValue 设置的标志值
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-05-19
 ***********************************************************************************************/
void CANDrv_SetCanTxStopFlag(BOOL bFlagValue)
{
	s_bCanTxStopFlg = bFlagValue;
}


/**************************************************************************
* 函数名称：CANDrvMSCAN_TxDisable
* 功能描述：CAN模块禁能发送
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
***************************************************************************/
void CANDrvMSCAN_TxDisable(void)
{
	
}

/**************************************************************************
* 函数名称：static void CANDrvMSCAN_vosTxComfirm(INT8U u1tTxBEmptyNum)
* 功能描述：CAN驱动层发送完毕确认
* 入口参数：u1tTxBEmptyNum-发送完毕的邮箱号
* 出口参数：无
* 返 回 值：无
* 备    注: 无
***************************************************************************/
static void CANDrvMSCAN_vosTxComfirm(INT8U u1tTxBEmptyNum)
{
	INT8U u1tIdx;
	INT8U u1tTxBEmptyFlg = 0;

	u1tTxBEmptyFlg = 0x01u << u1tTxBEmptyNum; /*发送完成邮箱号对应的标识*/
	for(u1tIdx = 0; u1tIdx < CANDrvMSCAN_TXBUFFER_NUM; u1tIdx++)
	{
		if(CANDrvMSCAN_u1sTxConfirmFlg[u1tIdx] & u1tTxBEmptyFlg)//该发送buffer是否有填充过发送数据
		{
			//Set corresponding txbuffer Flg  to be not loaded anything.
			switch((CANDrvMSCAN_u1sTxConfirmFlg[u1tIdx] >> 3))//获取该buffer发送的信息对应的索引
			{
				case eTXINDEX_NM:
//					NmOsek_u1gTxConfirmFlg = TRUE;//发送完毕确认
					CANDrvMSCAN_u1sTxConfirmFlg[u1tIdx] = 0x00U;
					CanIf_OsekNmUserTxConfirmation();//P20在发送回调中调用
					break;
				case eTXINDEX_DIAG:
					TP_u1gPhisicalRspTxFnshFlg = TRUE;//物理响应
					TPTxProcess();						//需打开，否则TP层诊断测试不通过 michael 20180223
					CANDrvMSCAN_u1sTxConfirmFlg[u1tIdx] = 0x00U;
					break;
				default:
					break;
			}
		}
	}
}

void CANDrvMSCAN_vogBusOffRecoveryReq(void)
{
//	UJA1078_StartupOprTask();
//	UJA1078_EnterNormalOperation();
	CANDrvInit();
	CANDrvMSCAN_u1gMSCANInit();
//	CanOnline(FALSE);
}

/*Set corresponding Tx Buffer is loaded defined Message,which is used to confirm transmition completedly*/
static void CANDrvMSCAN_vosSetTxBuffersMsgIDIndex(INT32U MsgID, INT8U u1tTxBNo)
{
	INT8U u1tMsgIDIndex = 0;
	INT8U u1TxMask = 0;

	u1TxMask = 0x01u << u1tTxBNo;
	switch(MsgID)
	{
		case  NM_CANID:
			u1tMsgIDIndex = (INT8U)eTXINDEX_NM;
			break;
		case  DESC_RSPID:
			u1tMsgIDIndex = (INT8U)eTXINDEX_DIAG;
			break;
		default:
			return;
	}
	switch(u1tTxBNo)
	{
			/*低3bit代表使用了哪个发送寄存器*/
		case CANDrvMSCAN_TxBUFFER0:
			CANDrvMSCAN_u1sTxConfirmFlg[0] = (u1tMsgIDIndex << 3) | (u1TxMask);
			break;
		case CANDrvMSCAN_TxBUFFER1:
			CANDrvMSCAN_u1sTxConfirmFlg[1] = (u1tMsgIDIndex << 3) | (u1TxMask);
			break;
		case CANDrvMSCAN_TxBUFFER2:
			CANDrvMSCAN_u1sTxConfirmFlg[2] = (u1tMsgIDIndex << 3) | (u1TxMask);
			break;
		default:
			return;
	}
}
void CANDrvMSCAN_vogFillTxEmptyBuffers(INT8U InIntFlag)
{
	INT8U i = 0, j = 0, u1tDataLen = 0;
	volatile INT8U *pu1tData;

    volatile Kf32a_Canfd_Reg *ControllerRegPtr = (Kf32a_Canfd_Reg *)Can_m_ControllersInfo[0].BaseAddress;
    Canfd_MailboxHeaderType* MailBoxTxbuffCfg = NULL;
    INT8U ConFlg = 0;
    INT8U SendFlg = 0;
    static INT16U s_ReadPoint = 0xFFFF;

	while(CANMsgTxDrv.cMsgNum > 0u)
	{
		if(CANMsgTxDrv.cReadPointer >= MAX_CAN_MSG_TX_BUF_SIZE)
		{
			CANMsgTxDrv.cReadPointer = 0;
		}
		for(i = 0; i < CANMAINTXNUM; i++)
		{
			MailBoxTxbuffCfg = &CanMainMailboxTxbuffCfg[i].TxBuff;
			MailBoxTxbuffCfg->Can_id = CAN_DATA_STANDARD ;
			MailBoxTxbuffCfg->FrameData.Data_Length = Data_Length_8;
			MailBoxTxbuffCfg->Can_frame = CAN_FRAME_CLASSICAL;
			MailBoxTxbuffCfg->BRS = CANFD_BRS_DISABLE;
			MailBoxTxbuffCfg->TransceiveType = MAIL_TRANSMIT;
			MailBoxTxbuffCfg->Timestamp = 0;

			if(CanMainMailboxTxbuffCfg[i].BusyFlag == FALSE)
			{

				pu1tData = CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cReadPointer].cData;
				u1tDataLen = CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cReadPointer].cDataLength;
				for(j = 0; j < u1tDataLen; j++)
				{
					MailBoxTxbuffCfg->FrameData.U8Data[j] = *(pu1tData++);
				}
				CanMainMailboxTxbuffCfg[i].CanTxId = CANMsgTxDrv.CANMsgBuf[CANMsgTxDrv.cReadPointer].cCANIDIndex;

				if(CanMainMailboxTxbuffCfg[i].CanTxId == DESC_RSPID)
				{
					MailBoxTxbuffCfg->FrameData.Data_Length = u1tDataLen;
				}

				CANDrvMSCAN_vosSetTxBuffersMsgIDIndex(CanMainMailboxTxbuffCfg[i].CanTxId, i);

				MailBoxTxbuffCfg->Id = CanMainMailboxTxbuffCfg[i].CanTxId;

				/* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
//				FunctionalState Res = FALSE;
//				INT8U Cnt = 3;
//				while(Cnt--)
//				{
//					Res = ecual_CAN_ConfigTxMb(INST_CAN0, CanMainMailboxTxbuffCfg[i].MailBoxIndex, MailBoxTxbuffCfg);
//
//					if(TRUE == Res)
//					{
//						CanMainMailboxTxbuffCfg[i].BusyFlag = TRUE;
//						break;
//					}
//				}
//
//				if(FALSE == Res)  /*写邮箱失败 跳出循环*/
//				{
//					break;
//				}

//				if(FALSE == ecual_CAN_ConfigTxMb(INST_CAN0, CanMainMailboxTxbuffCfg[i].MailBoxIndex, MailBoxTxbuffCfg))
//				{
//					return;
//				}
				//这里是调试can发送的代码 暂时保留
//				if(CanMainMailboxTxbuffCfg[i].CanTxId == 0x426)
//				{
//					#define IDADDR_VAL   (*((volatile uint32_t*)(0x1FFEF024)))
//					#define BYTE0_VAL   (*((volatile uint8_t*)(0x1FFEF025)))
//
//					RxFlag = 1;
//					MailBoxTxbuffCfg->FrameData.U8Data[6] = IDADDR_VAL >> 21;
//					MailBoxTxbuffCfg->FrameData.U8Data[7] = BYTE0_VAL;
//				}
//
//				if(CanMainMailboxTxbuffCfg[i].CanTxId == 0x50B)
//				{
//					MailBoxTxbuffCfg->FrameData.U8Data[7] = tESTD;
//					tESTD ++;
//				}
				if((D_CANDRVMSCAN_MAX_TIME <= s_CANDrvMSCANTxtimer) || (s_ReadPoint == CANMsgTxDrv.cReadPointer))
				{
                    ControllerRegPtr->CANFD_CTLR0.B.TXR = 0x00;
                    ControllerRegPtr->CANFD_CTLR0.B.ATX = 0x01;
                    asm("nop");asm("nop");asm("nop");
                    ControllerRegPtr->CANFD_CTLR0.B.ATX = 0x00;
                    ControllerRegPtr->CANFD_CTLR0.B.TXR = 0x01;
				}
                s_ReadPoint = CANMsgTxDrv.cReadPointer;

				ConFlg = ecual_CAN_ConfigTxMb(INST_CAN0, CanMainMailboxTxbuffCfg[i].MailBoxIndex, MailBoxTxbuffCfg);
				/* Execute send non-blocking */
				if(CAN_OK == ConFlg)
				{
				    SendFlg = ecual_CAN_sendOnce(INST_CAN0, FALSE, &(CanMainMailboxTxbuffCfg[i]), MailBoxTxbuffCfg);
				}

				if((CAN_OK == ConFlg) && (TRUE == SendFlg))
				{
	                s_CANDrvMSCANTxtimer = 0;
	                if(InIntFlag == FALSE)
	                {
	                    if((cDescECUHardRestAnswerIndex == CANMsgTxDrv.cReadPointer) && (DescECUResetReq.cDescECUHardRestReq))
	                    {
	                    	DescECUResetReq.cDescECUHardRestAnswerFnish =  TRUE;
	                    }
	                }
	                CanMainMailboxTxbuffCfg[i].BusyFlag = TRUE;
	                CANMsgTxDrv.cMsgNum --;
	                CANMsgTxDrv.cReadPointer++;
                    break; /*找到空闲邮箱发送,跳出看是否还有数据需发送*/
				}
			}
			else
			{
				if(D_CANDRVMSCAN_MAX_TIME <= s_CANDrvMSCANTxtimer)
				{
					CanMainMailboxTxbuffCfg[i].BusyFlag = FALSE;
				}
			}
		}

		if(i >= CANMAINTXNUM) /*无空闲邮箱,跳出本次发送*/
		{
			break;
		}
	}
}

void CANDrvMSCAN_vogWakeUPIntRoutine(void)
{
	g_bCANWakeUpFlg = TRUE;
	CANTxEnable();
}


void CANDrvMSCAN_vogErrIntRoutine(uint8_t instance, flexcan_event_type_t eventType,flexcan_state_t* flexcanState)
{
//	NmCanError();
//	NM_u1gCANBusOff = TRUE;
//
//	CANDrvMSCAN_vogBusOffRecoveryReq();
//	CANDrv_SetCanTxStopFlag(TRUE);
//	nmBusOffCounter++;//Bus Off 计数

//	if(FLEXCAN_EVENT_BUSERROR == eventType)  /*bus error*/
//	{
//		INT8U i = 0;
//		Canfd_MailboxHeaderType* MailBoxRxbuffCfg = NULL;
//		INT8U CanIndex[CAN_INSTANCE_COUNT] = CAN_BASE_PTRS;
//		INT8U Index = CanIndex[instance];
//
//		INT_SYS_DisableIRQGlobal();
//		for(i = 0; i < CANMAINRXNUM; i++)
//		{
//			MailBoxRxbuffCfg = &CanMainMailboxRxbuffCfg[i].RxBuff;
//			Can_m_FdMailBoxCode_Set(Index,i,MailBoxRxbuffCfg);
//		}
//		INT_SYS_EnableIRQGlobal();
//	}
	//2024.01.04
	//    NmCanError();
		NM_BusErrorIndication(0);

	//    CanOnline();
	//    Srvl_Pwr_SetNormalMode();
		CANDrvMSCAN_vogBusOffRecoveryReq();

	    NmBusoffPara.bCANBusOffFlag = TRUE;
	    NmBusoffPara.bCanTxStopFlg = TRUE;
	    NmBusoffPara.bCanBusOffRecoveryInd = TRUE;
	    NmBusoffPara.u8BusOffCounter++;

	    if( NmBusoffPara.bCANBusOffFlag == FALSE)
	    {
	    	NmBusoffPara.bCANBusOffFlag = TRUE;
			NmBusoffPara.u8BusOffRecoveryCounter = 0;
		}
}


void CANDrvMSCAN_vogRxIntRoutine(INT32U CANID, INT8U *pBuff, INT8U len)
{
	volatile INT8U *pu1tData;
	INT8U u1tIdx;

	/*放在此处,只有需要接收的CAN ID才能唤醒控制器*/
	if(g_bCANWakeUpFlg == TRUE)
	{
		g_bCANWakeUpFlg = FALSE;
		ComCtrlOpt.NMComMsg.Bits.TxEnable = TRUE;
	}

	if(CANMsgRxDrv.cMsgNum < MAX_CAN_MSG_RX_BUF_SIZE)
	{
		if(CANMsgRxDrv.cWritePointer >= MAX_CAN_MSG_RX_BUF_SIZE)
		{
			CANMsgRxDrv.cWritePointer = 0;
		}

		CANMsgRxDrv.CANMsgBuf[CANMsgRxDrv.cWritePointer].cCANID = CANID;
		pu1tData = CANMsgRxDrv.CANMsgBuf[CANMsgRxDrv.cWritePointer].cData;
		//高负载情况下 长度会错误  - 20230110
		//一个月没有出现取出长度错误的问题（4月7号 czb），恢复原来长度判断,正常就是应该这样做- 20230330
		//旧的sdk在busoff的时候 会产生数据长度大于8的情况   小于8的时候在应用层会丢掉 不处理  - 新的sdk暂时没发现数据长度错误 - 20230718
		if(len > 8)
		{
			len = 8;
		}
		for(u1tIdx = 0; u1tIdx < len; u1tIdx ++)
		{
			pu1tData[u1tIdx] = pBuff[u1tIdx];
		}
		CANMsgRxDrv.CANMsgBuf[CANMsgRxDrv.cWritePointer].cDataLength = len;
		CANMsgRxDrv.cWritePointer ++;
		CANMsgRxDrv.cMsgNum ++;
	}
}


void CANDrvMSCAN_vogTxEIntRoutine(INT8U IdleNum)
{
	Nm_BusoffParaInit();
	CANDrv_SetCanTxStopFlag(FALSE);
	CANDrvMSCAN_vosTxComfirm(IdleNum);
//	CANDrvMSCAN_vogFillTxEmptyBuffers(TRUE);//打开会影响发送，出现报文漏发的情况
}

/**************************************************************************
* 函数名称：void CanMainRxTxCallFunc(INT8U instance, flexcan_event_type_t eventType,flexcan_state_t *flexcanState)
* 功能描述：CAN接收发送完毕中断调用
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
***************************************************************************/
//void CanMainRxTxCallFunc(INT8U instance, flexcan_event_type_t eventType, flexcan_state_t *flexcanState)
void CanMainRxTxCallFunc(uint8_t instance, flexcan_event_type_t eventType,uint32_t buffIdx, flexcan_state_t *flexcanState)
{
	INT8U i = 0;
	INT32U CANId = 0;
	INT8U CANLen = 0;
    Canfd_MailboxHeaderType* MailBoxRxbuffCfg = NULL;

	/*接收完成*/
	if(eventType == FLEXCAN_EVENT_RX_COMPLETE)
	{
		for(i = 0; i < CANMAINRXNUM; i++)
		{
			CANWakeupFlg = TRUE;
			//if(FLEXCAN_DRV_GetTransferStatus(instance, CanMainMailboxRxbuffCfg[i].MailBoxIndex) == STATUS_SUCCESS)  /*20220924无需接收状态判断*/
			if(buffIdx == CanMainMailboxRxbuffCfg[i].MailBoxIndex)
			{
				CANDrv_SetCanTxStopFlag(FALSE); /*增加接收到别的节点发送的报文时,清停止发送的标识*/
				CanMainMailboxRxbuffCfg[i].NewFrameFlag = TRUE;

				MailBoxRxbuffCfg = &CanMainMailboxRxbuffCfg[i].RxBuff;
				CANId = MailBoxRxbuffCfg->Id;
				CANLen = MailBoxRxbuffCfg->FrameData.Data_Length;
				CANDrvMSCAN_vogRxIntRoutine(CANId, MailBoxRxbuffCfg->FrameData.U8Data,CANLen);

				/* Start receiving data in RX_MAILBOX. */
				FLEXCAN_DRV_Receive(instance,buffIdx, MailBoxRxbuffCfg);
                break;
            }
		}
	}
	/*发送完成*/
	if(eventType == FLEXCAN_EVENT_TX_COMPLETE)
	{
		for(i = 0; i < CANMAINTXNUM; i++)
		{
			//if(FLEXCAN_DRV_GetTransferStatus(instance, CanMainMailboxTxbuffCfg[i].MailBoxIndex) == STATUS_SUCCESS)
			if(buffIdx == CanMainMailboxTxbuffCfg[i].MailBoxIndex)
			{
				CanMainMailboxTxbuffCfg[i].BusyFlag = FALSE;
				CANDrvMSCAN_vogTxEIntRoutine(i);
				break;
			}
		}
	}
}

void CANDrvMSCAN_ClearTxBuffer(void)
{
    INT8U i = 0;

    CANMsgTxDrv.cMsgNum = 0;
    /*初始化接收发送配置*/
    for(i = 0; i < CANMAINTXNUM; i++)
    {
        CanMainMailboxTxbuffCfg[i].BusyFlag = FALSE;
    }
    memset(&CANMsgTxDrv,0,sizeof(CANMsgTxType)); /*清空发送缓存*/

}

/**************************************************************************
* 函数名称：void CANDrvMSCAN_u1gMSCANInit(void)
* 功能描述：配置底层CAN初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
***************************************************************************/
void CANDrvMSCAN_u1gMSCANInit(void)
{
	INT8U i = 0;
	INT8U CfgRxMbTimeCnt = 0;
	INT8U Ret = FALSE;
	Canfd_MailboxHeaderType* MailBoxRxbuffCfg = NULL;

	INT_SYS_DisableIRQGlobal();
	for(i = 0; i < CANMAINRXNUM; i++)
	{
		ecual_CAN_SetHwFilter(INST_CAN0,&CanMainMailboxRxbuffCfg[i]);
	}
	ecual_CAN_init(INST_CAN0, CanMainRxTxCallFunc, CANDrvMSCAN_vogErrIntRoutine, NULL);

	for(i = 0; i < CANMAINRXNUM; i++)
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
	/*初始化接收发送配置*/
	for(i = 0; i < CANMAINRXNUM; i++)
	{
		CanMainMailboxRxbuffCfg[i].NewFrameFlag = FALSE;
	}
	for(i = 0; i < CANMAINTXNUM; i++)
	{
		CanMainMailboxTxbuffCfg[i].BusyFlag = FALSE;
	}

	memset(&CANMsgTxDrv,0,sizeof(CANMsgTxType)); /*清空发送缓存*/

	//CANTxEnable();
	INT_SYS_EnableIRQGlobal();
}

