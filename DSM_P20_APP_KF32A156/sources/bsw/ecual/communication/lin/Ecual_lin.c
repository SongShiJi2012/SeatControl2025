/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               hal_lin.c
** Created By:              chenzibo
** Created date:            2022.12.27
** Version:                 V1.0
** Descriptions:
**
**------------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
**************************************************************************************************/

#include <Ecual_lin.h>
#include <Ecual_linCfg.h>
#include "CpuPeripheralInit.h"  /*相互调用，有风险，需要把定时器应用功能单独做成文档*/
#include "OsekNm.h"
#include <Mcal_Lin.h>

extern LinDeviceComm_t LinDevCommManage[D_LIN_DEV_ID_LIN1_EN];
extern LinMsgMaxrix_t  ebsLinMsgMaxrix[LIN_DOOR_MSG_MARRIX_LEN];
extern LinScheduleList_t  ebsLinScheManage[LIN_DOOR_SCHE_MANAGE_LEN];
extern LinTaskManage_t LinTaskManage;

static void Ecual_LinRecvCallBack(LinChlIdx_t eLinChan,LinInfo_t * LinInfo);

 /***********************************************************************************************
  * @function name: void Ecual_LinInit(void)
  * @description:     初始化LIN
  * @input parameters:      void
  * @output parameters:     void
  * @return:         void
  * @note:
  * @author:         2022-12-16 czb
  ***********************************************************************************************/
void Ecual_LinInit(void)
{
#if (D_LIN_POLL_EN != 0U)
	Mcal_LinInit(LinDevCommManage,Ecual_LinRecvCallBack);
#endif
}

 /***********************************************************************************************
  * @function name: void Ecal_LinDeinit(void)
  * @description:     反初始化LIN
  * @input parameters:      void
  * @output parameters:     void
  * @return:         void
  * @note:
  * @author:         2022-12-16 czb
  ***********************************************************************************************/
void Ecal_LinDeinit(void)
{
#if (D_LIN_POLL_EN != 0U)
	Mcal_LinDeInit(LinDevCommManage);
#endif
}

/*!
************************************************************************************************************************
* 接口原型 INT32S Ecual_LinSendData(LinCommMsg_t *TransmitMsg)
* @brief LIN发送数据
* @param[in] LinCommMsg_t *TransmitMsg
* @returns 发送结果：0 OK ，其他 错误值
* @note 无
* @author Jean Yuan
* @date 2020-05-13
************************************************************************************************************************
*/
static INT32S Ecual_LinSendData(LinCommMsg_t *TransmitMsg)
{
	INT8U i = 0;
	LinFrame_t LinFrame={0};
	INT32S ret = 0;

	if((TransmitMsg->buffer == NULL)||(TransmitMsg->len >8))
		return -1;

	for(i=0;i<UBOUND(LinDevCommManage);i++)
	{
		if(TransmitMsg->DevId == LinDevCommManage[i].LinUartIndex)
		{
			memcpy(LinFrame.au8Data,TransmitMsg->buffer,TransmitMsg->len);
			if(TransmitMsg->idMessage == 0x3c)
			{
				LinFrame.eCheckSumType = eLIN_Classic;
			}
			else
			{
				LinFrame.eCheckSumType = eLIN_Enhanced;
			}
			LinFrame.eTransmitType = eLIN_DataSend;
			LinFrame.u8DataLen = TransmitMsg->len;
			LinFrame.u8PID = TransmitMsg->idMessage;
			ret = Drv_LinMasterSend(LinDevCommManage[i].LinUartIndex,&LinFrame);
			break;
		}
	}
	
	return ret;
}


/*!
************************************************************************************************************************
* 接口原型 INT32S Ecual_LinRecvData(LinCommMsg_t *RecvMsg)
* @brief LIN接收数据
* @param[in] LinCommMsg_t *RecvMsg
* @returns 发送结果：0 OK ，其他 错误值
* @note 无
* @author Jean Yuan
* @date 2020-05-13
************************************************************************************************************************
*/

static INT32S Ecual_LinRecvData(LinCommMsg_t *RecvMsg)
{
	INT8U i = 0;
	INT16S length=0;
	LinFrame_t LinFrame={0};
	uint8_t Cnt = 3;
	
	if((RecvMsg->buffer == NULL)||(RecvMsg->len >8))
		return -1;
	
	for(i=0;i<UBOUND(LinDevCommManage);i++)
	{
		if(RecvMsg->DevId == LinDevCommManage[i].LinUartIndex)
		{
			if(RecvMsg->idMessage == 0x7d)
			{
				LinFrame.eCheckSumType = eLIN_Classic;//原来为增强型
			}
			else
			{
				LinFrame.eCheckSumType = eLIN_Enhanced;
			}
			LinFrame.eTransmitType = eLIN_DataReq;
			LinFrame.u8PID = RecvMsg->idMessage;
			LinFrame.u8DataLen = RecvMsg->len;
			while(Cnt--)
			{
				if(0 == Drv_LinMasterSend(LinDevCommManage[i].LinUartIndex,&LinFrame))
				{
					break;
				}
			}
			break;
		}
	}
	return length;
}
/***********************************************************************************************
 * @function name:  Ecual_FindLinMsg
 * @description:    在消息矩阵中查找指定idMessage
 * @input parameters:     LinMsgMaxrix_t *list：消息矩阵首地址，INT8U cnt：消息数量，INT8U id：要查找的id
 * @output parameters:    void
 * @return:         LinMsgMaxrix_t* 查找到的消息指针，查找失败返回NULL
 * @author:         ssj 14:18
 * @note:
 ***********************************************************************************************/
static LinMsgMaxrix_t* Ecual_FindLinMsg(LinMsgMaxrix_t *list, INT8U cnt, INT8U id)
{
    INT8U j;
    for(j = 0; j < cnt; j++)
    {
        if(list->idMessage == id)
        {
            return list;
        }
        list++;
    }
    return NULL;
}
/***********************************************************************************************
 * @function name:  Ecual_MoveToNextIndex
 * @description:    调度表索引递增并循环（直接操作全局变量LinTaskManage）
 * @input parameters:     void
 * @output parameters:    void
 * @return:         void
 * @author:         ssj 15:22
 * @note:
 ***********************************************************************************************/
static void Ecual_MoveToNextIndex(void)
{
    LinTaskManage.Index++;
    if(LinTaskManage.Index >= LinTaskManage.SumCnt)
    {
        LinTaskManage.Index = 0;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_LinMsgProcess
 * @description:    处理LIN消息的收发，包含周期帧与事件帧
 * @input parameters:     LinMsgMaxrix_t *msg, LinCommMsg_t *comm
 * @output parameters:    void
 * @return:         INT32S (0=成功)
 * @author:         ssj 14:13
 ***********************************************************************************************/
static INT32S Ecual_LinMsgProcess(LinMsgMaxrix_t *msg, LinCommMsg_t *comm)
{
    INT32S ret = 0;//如果不发送则默认发送成功

    if(msg->MsgDir == EN_LIN_DIR_TX)    // 发送
    {
        if(msg->MsgType) // 周期帧
        {
            if(TRUE == NM_GetLinMsgTxInd())
            {
                ret = Ecual_LinSendData(comm);
            }
        }
        else // 事件帧
        {
            if(msg->TxAndRxFlag)
            {
                ret = Ecual_LinSendData(comm);
                if(ret == 0)
                {
                    msg->TxAndRxFlag = 0;
                }
            }
        }
    }
    else    // 接收
    {
        if(msg->MsgType) // 周期帧
        {
            if(TRUE == NM_GetLinMsgTxInd())
            {
                ret = Ecual_LinRecvData(comm);
                if(CPU_TimerDiffTs(msg->RecvErrTimes) >= ECUAL_LIN_TIMEOUT_MAX)
                {
                    msg->MsgSt.LinMsg_RxVaildFlg = 0;
                }
            }
        }
        else // 事件帧
        {
            if(msg->TxAndRxFlag)
            {
                ret = Ecual_LinRecvData(comm);
                if(ret == 0)
                {
                    msg->TxAndRxFlag = 0;
                }
            }
        }
    }
    return ret;
}
/***********************************************************************************************
 * @function name:  Ecual_LINSchTick
 * @description:    LIN总线正常通讯流程处理，包括调度、消息查找、收发处理和索引切换
 * @input parameters:     void
 * @output parameters:    void
 * @return:         void
 * @author:         ssj 14:28
 * @note:
 ***********************************************************************************************/
void Ecual_LINSchTick(void)
{
    INT32S ret = 0;

    if(LinTaskManage.IsHandUp)
    {
        return;
    }

    // 当前调度表项指针
    LinScheduleList_t *pCurSche = LinTaskManage.LinScheList + LinTaskManage.Index;
    // 当前调度表项对应的消息ID
    INT8U curMsgId = pCurSche->idMessage;
    // 消息矩阵首地址
    LinMsgMaxrix_t *pMsgMatrix = LinTaskManage.LinMaxrixList;
    // 消息矩阵总数
    INT8U msgMatrixCount = LinTaskManage.MsgCnt;

    // 查找当前消息ID在消息矩阵中的详细属性
    LinMsgMaxrix_t *pMsg = Ecual_FindLinMsg(pMsgMatrix, msgMatrixCount, curMsgId);
    if((pMsg == NULL) || (!pMsg->TxAndRxFlag))
    {
        Ecual_MoveToNextIndex();//更新调度表调度索引
        return;
    }

    LinScheduleList_t *pSche = LinTaskManage.LinScheList + LinTaskManage.Index;
    if(CPU_TimerDiffTs(LinTaskManage.TimeTick) >= pSche->DelayTime)
    {
        LinTaskManage.TimeTick = D_HAL_GET_CUR_MS_TS();

        LinCommMsg_t CommMsg;
        CommMsg.DevId = LinTaskManage.DeviceId;
        CommMsg.idMessage = pMsg->PidMessage;
        CommMsg.buffer = pMsg->Buffer;
        CommMsg.len = pMsg->MsgDlc;

        ret = Ecual_LinMsgProcess(pMsg, &CommMsg);

        if(ret == 0)
        {
            Ecual_MoveToNextIndex();//更新调度表调度索引
        }
    }
}

/*!
************************************************************************************************************************
* 接口原型 BOOL Ecual_LinIsMsgRecvValid(LinDeviceId_e 	DevId,INT8U idMessage)
* @brief LIN消息接收是否有效
* @param[in] TRUE 有效，FALSE 无效
* @returns 
* @note 无
* @author Jean Yuan
* @date 2020-05-13
************************************************************************************************************************
*/
BOOL Ecual_LinIsMsgRecvValid(LinChlIdx_t DevId,INT8U idMessage)
{
	INT8U i;
	INT8U j;
	LinMsgMaxrix_t	* LinMaxrixList = NULL;

	if(LinTaskManage.DeviceId == DevId)
	{
		LinMaxrixList = LinTaskManage.LinMaxrixList;
		for(j=0;j<LinTaskManage.MsgCnt;j++)
		{
			if(LinMaxrixList->idMessage == idMessage)
			{
				return (BOOL)LinMaxrixList->MsgSt.LinMsg_RxVaildFlg;
			}
			LinMaxrixList++;
		}
	}

	return FALSE;
}

/*!
************************************************************************************************************************
* 接口原型 void Ecual_LinRecvCallBack(LinInfo_t * LinInfo)
* @brief Door LIN接收消息中断回调函数
* @param[in] 接收信息
* @returns 
* @note 无
* @author Jean Yuan
* @date 2020-05-13
************************************************************************************************************************
*/
static void Ecual_LinRecvCallBack(LinChlIdx_t eLinChan,LinInfo_t * LinInfo)
{
	INT8U i = 0;
	LinMsgMaxrix_t	*LinMaxrixList =NULL;

	/*硬件lin通道映射到 LinTaskManage*/
	switch(eLinChan)
	{
		case LIN_DEV1:
		{
			LinMaxrixList = LinTaskManage.LinMaxrixList;
		}
		 break;
		 
		default:
		break;
	}

	if(LinMaxrixList != NULL)
	{
		for(i = 0; i < LinTaskManage.MsgCnt; i++)
		{
			if(LinMaxrixList->PidMessage == LinInfo->stFrame.u8PID)
			{
				if(LinInfo->eStatus == eLIN_RECVSUCCESS)
				{
					memset(LinMaxrixList->Buffer, 0, LinMaxrixList->MsgDlc);
					memcpy(LinMaxrixList->Buffer,LinInfo->stFrame.au8Data,LinMaxrixList->MsgDlc);
					LinMaxrixList->MsgSt.LinMsg_RxVaildFlg = 1;
					LinMaxrixList->RecvErrTimes = D_HAL_GET_CUR_MS_TS();
				}
				return;
			}
			LinMaxrixList++;
		}
	}
}

/***********************************************************************************************
 * @function name:  Ecual_LinGetLostPid()
 * @description:    判断 LIN 总线 ID 为 0x1B 的消息是否丢失
 * @input parameters:     void
 * @output parameters:     void
 * @return:         BOOL类型，若消息无效则返回 TRUE，表示消息丢失
 * @note:
 * @author:         ssj 2025-04-29
 ***********************************************************************************************/
BOOL Ecual_LinGetLostPid()
{
	INT8U LostFlag = FALSE;

	if(FALSE == Ecual_LinIsMsgRecvValid(LIN_DEV1, 0x1B))
	{
		LostFlag = TRUE;
	}

	return LostFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_LinSetDiagEvent
 * @description:    根据传入的id，查找LinMaxrix列表中对应消息结构体，将其TxAndRxFlag置1
 * @input parameters: INT8U id: 消息ID
 * @output parameters: 无
 * @return:         void
 * @author:         ssj 2025-06-17 16:XX
 ***********************************************************************************************/
void Ecual_LinSetDiagEvent(INT8U id)
{
    LinMsgMaxrix_t *LinMaxrixList = LinTaskManage.LinMaxrixList; // 指向数组首地址
    INT8U i;
    INT8U index = 0xFF;

    for(i = 0; i < LIN_DOOR_MSG_MARRIX_LEN; i++)
    {
        if(LinMaxrixList[i].idMessage == id)
        {
            index = i;
            break;
        }
    }

    if(index != 0xFF)
    {
        LinMaxrixList[index].TxAndRxFlag = 1;
    }
}

/***********************************************************************************************
 * @function name:  Ecaul_LinSetDiagData
 * @description:    根据传入的id，查找LinMaxrix列表中对应消息结构体，赋值数据到其Buffer中
 * @input parameters: INT8U id: 消息ID
 *                    INT8U len: 数据长度
 *                    INT8U* databuf: 数据源指针
 * @output parameters: 无
 * @return:         void
 * @author:         ssj 2025-06-17 16:XX
 ***********************************************************************************************/
void Ecaul_LinSetDiagData(INT8U id, INT8U len, INT8U* databuf)
{
    LinMsgMaxrix_t *LinMaxrixList = LinTaskManage.LinMaxrixList; // 指向数组首地址
    INT8U i;
    INT8U index = 0xFF;

    if(databuf == NULL)
    {
        return;
    }

    for(i = 0; i < LIN_DOOR_MSG_MARRIX_LEN; i++)
    {
        if(LinMaxrixList[i].idMessage == id)
        {
            index = i;
            break;
        }
    }

    if(index != 0xFF && LinMaxrixList[index].Buffer != NULL)
    {
        for(i = 0; i < len && i < LinMaxrixList[index].MsgDlc; i++)
        {
            LinMaxrixList[index].Buffer[i] = databuf[i];
        }
    }
}

/***********************************************************************************************
 * @function name:  Ecaul_LinTxSleepMsg
 * @description:    LIN总线发送SLEEP诊断报文，并触发相关事件处理
 * @input parameters:     void
 * @output parameters:    void
 * @return:         void
 * @author:         ssj 2025-06-18 15:25
 * @note:
 ***********************************************************************************************/
void Ecaul_LinTxSleepMsg(void)
{
    INT8U tData[8] = {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    Ecaul_LinSetDiagData(0x3C, 8, tData);
    Ecual_LinSetDiagEvent(0x3C);
}


