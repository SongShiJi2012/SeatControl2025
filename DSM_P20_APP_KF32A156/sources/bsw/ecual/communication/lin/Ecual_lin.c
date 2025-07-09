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
#include "CpuPeripheralInit.h"  /*�໥���ã��з��գ���Ҫ�Ѷ�ʱ��Ӧ�ù��ܵ��������ĵ�*/
#include "OsekNm.h"
#include <Mcal_Lin.h>

extern LinDeviceComm_t LinDevCommManage[D_LIN_DEV_ID_LIN1_EN];
extern LinMsgMaxrix_t  ebsLinMsgMaxrix[LIN_DOOR_MSG_MARRIX_LEN];
extern LinScheduleList_t  ebsLinScheManage[LIN_DOOR_SCHE_MANAGE_LEN];
extern LinTaskManage_t LinTaskManage;

static void Ecual_LinRecvCallBack(LinChlIdx_t eLinChan,LinInfo_t * LinInfo);

 /***********************************************************************************************
  * @function name: void Ecual_LinInit(void)
  * @description:     ��ʼ��LIN
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
  * @description:     ����ʼ��LIN
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
* �ӿ�ԭ�� INT32S Ecual_LinSendData(LinCommMsg_t *TransmitMsg)
* @brief LIN��������
* @param[in] LinCommMsg_t *TransmitMsg
* @returns ���ͽ����0 OK ������ ����ֵ
* @note ��
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
* �ӿ�ԭ�� INT32S Ecual_LinRecvData(LinCommMsg_t *RecvMsg)
* @brief LIN��������
* @param[in] LinCommMsg_t *RecvMsg
* @returns ���ͽ����0 OK ������ ����ֵ
* @note ��
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
				LinFrame.eCheckSumType = eLIN_Classic;//ԭ��Ϊ��ǿ��
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
 * @description:    ����Ϣ�����в���ָ��idMessage
 * @input parameters:     LinMsgMaxrix_t *list����Ϣ�����׵�ַ��INT8U cnt����Ϣ������INT8U id��Ҫ���ҵ�id
 * @output parameters:    void
 * @return:         LinMsgMaxrix_t* ���ҵ�����Ϣָ�룬����ʧ�ܷ���NULL
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
 * @description:    ���ȱ�����������ѭ����ֱ�Ӳ���ȫ�ֱ���LinTaskManage��
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
 * @description:    ����LIN��Ϣ���շ�����������֡���¼�֡
 * @input parameters:     LinMsgMaxrix_t *msg, LinCommMsg_t *comm
 * @output parameters:    void
 * @return:         INT32S (0=�ɹ�)
 * @author:         ssj 14:13
 ***********************************************************************************************/
static INT32S Ecual_LinMsgProcess(LinMsgMaxrix_t *msg, LinCommMsg_t *comm)
{
    INT32S ret = 0;//�����������Ĭ�Ϸ��ͳɹ�

    if(msg->MsgDir == EN_LIN_DIR_TX)    // ����
    {
        if(msg->MsgType) // ����֡
        {
            if(TRUE == NM_GetLinMsgTxInd())
            {
                ret = Ecual_LinSendData(comm);
            }
        }
        else // �¼�֡
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
    else    // ����
    {
        if(msg->MsgType) // ����֡
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
        else // �¼�֡
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
 * @description:    LIN��������ͨѶ���̴����������ȡ���Ϣ���ҡ��շ�����������л�
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

    // ��ǰ���ȱ���ָ��
    LinScheduleList_t *pCurSche = LinTaskManage.LinScheList + LinTaskManage.Index;
    // ��ǰ���ȱ����Ӧ����ϢID
    INT8U curMsgId = pCurSche->idMessage;
    // ��Ϣ�����׵�ַ
    LinMsgMaxrix_t *pMsgMatrix = LinTaskManage.LinMaxrixList;
    // ��Ϣ��������
    INT8U msgMatrixCount = LinTaskManage.MsgCnt;

    // ���ҵ�ǰ��ϢID����Ϣ�����е���ϸ����
    LinMsgMaxrix_t *pMsg = Ecual_FindLinMsg(pMsgMatrix, msgMatrixCount, curMsgId);
    if((pMsg == NULL) || (!pMsg->TxAndRxFlag))
    {
        Ecual_MoveToNextIndex();//���µ��ȱ��������
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
            Ecual_MoveToNextIndex();//���µ��ȱ��������
        }
    }
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� BOOL Ecual_LinIsMsgRecvValid(LinDeviceId_e 	DevId,INT8U idMessage)
* @brief LIN��Ϣ�����Ƿ���Ч
* @param[in] TRUE ��Ч��FALSE ��Ч
* @returns 
* @note ��
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
* �ӿ�ԭ�� void Ecual_LinRecvCallBack(LinInfo_t * LinInfo)
* @brief Door LIN������Ϣ�жϻص�����
* @param[in] ������Ϣ
* @returns 
* @note ��
* @author Jean Yuan
* @date 2020-05-13
************************************************************************************************************************
*/
static void Ecual_LinRecvCallBack(LinChlIdx_t eLinChan,LinInfo_t * LinInfo)
{
	INT8U i = 0;
	LinMsgMaxrix_t	*LinMaxrixList =NULL;

	/*Ӳ��linͨ��ӳ�䵽 LinTaskManage*/
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
 * @description:    �ж� LIN ���� ID Ϊ 0x1B ����Ϣ�Ƿ�ʧ
 * @input parameters:     void
 * @output parameters:     void
 * @return:         BOOL���ͣ�����Ϣ��Ч�򷵻� TRUE����ʾ��Ϣ��ʧ
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
 * @description:    ���ݴ����id������LinMaxrix�б��ж�Ӧ��Ϣ�ṹ�壬����TxAndRxFlag��1
 * @input parameters: INT8U id: ��ϢID
 * @output parameters: ��
 * @return:         void
 * @author:         ssj 2025-06-17 16:XX
 ***********************************************************************************************/
void Ecual_LinSetDiagEvent(INT8U id)
{
    LinMsgMaxrix_t *LinMaxrixList = LinTaskManage.LinMaxrixList; // ָ�������׵�ַ
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
 * @description:    ���ݴ����id������LinMaxrix�б��ж�Ӧ��Ϣ�ṹ�壬��ֵ���ݵ���Buffer��
 * @input parameters: INT8U id: ��ϢID
 *                    INT8U len: ���ݳ���
 *                    INT8U* databuf: ����Դָ��
 * @output parameters: ��
 * @return:         void
 * @author:         ssj 2025-06-17 16:XX
 ***********************************************************************************************/
void Ecaul_LinSetDiagData(INT8U id, INT8U len, INT8U* databuf)
{
    LinMsgMaxrix_t *LinMaxrixList = LinTaskManage.LinMaxrixList; // ָ�������׵�ַ
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
 * @description:    LIN���߷���SLEEP��ϱ��ģ�����������¼�����
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


