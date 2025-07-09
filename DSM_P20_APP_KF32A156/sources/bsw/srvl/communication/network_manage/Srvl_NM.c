#define NM_GLOBALS

#include "Srvl_NM.h"
#include "Appl_PowerMangeModel.h"
#include "Ecual_CAN.h"

StrNmBusoffPara NmBusoffPara;

/*!
************************************************************************************************************************
* �ӿ�ԭ�� static void Nm_BusoffParaInit(void)
* @brief ��ʼ��can busoff �������ΪĬ��ֵ
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author 
* @date 2021-2-05
************************************************************************************************************************
*/
void Nm_BusoffParaInit(void)
{
    NmBusoffPara.bCANBusOffFlag = FALSE;
    NmBusoffPara.bCanTxStopFlg = FALSE;
    NmBusoffPara.bCanBusOffRecoveryInd = FALSE;
    
    NmBusoffPara.enBusOffRecoveryMode = BusOffFastRecoveryMode;
    NmBusoffPara.u8BusOffRecoveryCounter  = 0;
    NmBusoffPara.u8BusOffCounter  = 0;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� void Nm_InitStart(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-8-20
************************************************************************************************************************
*/
void Nm_InitStart(void)
{
//    enFinalPowerMode tPowerMode = Srvl_Pwr_GetPwrMode(); /*2024.01.04*/
    
    Nm_BusoffParaInit();
//    Nm_CanInit();

//    if(tPowerMode != EN_SYS_WAKEP_UP_CHK) 
    {
		StartNM(0);
    }
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� static void Nm_BusoffParaInit(void)
* @brief �������-ϵͳ��ѹ�쳣�ָ��������ʼ����canģ��,��ֹ��ѹ�쳣����canģ�鹤���쳣
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author 
* @date 2021-2-05
************************************************************************************************************************
*/
void Nm_SysVoltAbnormalRecv(void)
{
//    Ecual_CanInit(); /*  2024.01.04 */
    Nm_InitStart();
//    Ecual_ClrCanWakeUpInd(); //�������Դ
    NmBusoffPara.bCanTxStopFlg = FALSE;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� void Nm_CanBusOffRecoveryProcess(void)
* @brief �������-busoff��Ŀ�ָ����ָ�ʵ��
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author 
* @date 2021-2-05
************************************************************************************************************************
*/
void Nm_CanBusOffRecoveryProcess(void)
{
    if(NmBusoffPara.bCANBusOffFlag == TRUE)
    {
        if (NmBusoffPara.bCanBusOffRecoveryInd == TRUE)
        {
            NmBusoffPara.bCanBusOffRecoveryInd = FALSE;
            CANDrvMSCAN_vogBusOffRecoveryReq();
        }
        
        if(NmBusoffPara.enBusOffRecoveryMode == BusOffFastRecoveryMode)//��ָ�ģʽ
        {
            if(NmBusoffPara.bCanTxStopFlg == TRUE)
            {
                NmBusoffPara.u8BusOffRecoveryCounter++;
                if(NmBusoffPara.u8BusOffRecoveryCounter >= NM_BUS_OFF_FAST_RECOVERY_TIME)
                {
                    NmBusoffPara.u8BusOffRecoveryCounter = 0;
                    NmBusoffPara.bCanTxStopFlg = FALSE;//����ʹ�ܷ��ͱ���
                    nmSetAlarmStart(1000);
//					Srvl_NMSetSendFlag(OSEK_ENABLE);/*��ָ����ȷ���NM����20230314 by Prima Niu*/
                    if(NmBusoffPara.u8BusOffCounter >= NM_COUNT_SHORT_NUMBER)
                    {
                        NmBusoffPara.enBusOffRecoveryMode = BusOffSlowRecoveryMode;//����ָ���������л������ָ�ģʽ
                    }
                }
            }
        }
        else if(NmBusoffPara.enBusOffRecoveryMode == BusOffSlowRecoveryMode)//���ָ�ģʽ
        {
            if(NmBusoffPara.bCanTxStopFlg == TRUE)
            {
                NmBusoffPara.u8BusOffRecoveryCounter++;
                if(NmBusoffPara.u8BusOffRecoveryCounter >= NM_BUS_OFF_SLOW_RECOVERY_TIME)
                {
//					Srvl_NMSetSendFlag(OSEK_ENABLE);/*���ָ����ȷ���NM����20230314 by Prima Niu*/
                    NmBusoffPara.u8BusOffRecoveryCounter = 0;
                    nmSetAlarmStart(1000);
                    NmBusoffPara.bCanTxStopFlg = FALSE;//����ʹ�ܷ��ͱ���
                }
            }
        }
		else
		{}

        if (NmBusoffPara.u8BusOffCounter >= NM_COUNT_BUSOFF_LIMIT)
        {
            NmBusoffPara.u8BusOffCounter = NM_COUNT_BUSOFF_LIMIT;
        }
    }
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT8U Nm_CanGetBusOffTrgCnt(void)
* @par ����
       ��ȡbusoff��������
* @param[in] NmBusoffPara.u8BusOffCounter
* @param[out] void
* @returns INT8U��bus off���ʹ���
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-11-1
************************************************************************************************************************
*/

INT8U Nm_CanGetBusOffTrgCnt(void)
{
    return NmBusoffPara.u8BusOffCounter;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� void Nm_ErrorHandle(void)
* @brief can bus error handle
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-8-21
************************************************************************************************************************
*/

void Nm_ErrorHandle(uint32_t eCode, uint8_t RxErrCnt, uint8_t TxErrCnt)
{
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

/*!
************************************************************************************************************************
* �ӿ�ԭ�� BOOL Nm_IsBusOff(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-8-21
************************************************************************************************************************
*/

BOOL Nm_IsBusOff(void)
{
    return NmBusoffPara.bCANBusOffFlag;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void Nm_MsgTransfer(void)
* @par ����
       ��������ķ���
* @param[in] 
* @param[out] 
* @param[out] 
* @returns void
* @pre ��
* @note �����Ե���,NM FIFO���������跢��ʱ����ʵ�ʷ���
* @author Lews Hammond(������)
* @date 2019-10-24
************************************************************************************************************************
*/
void Nm_MsgTransfer(void)
{
//    NmCan_TxPduInd(); /*�ж�FIFO���Ƿ���������Ҫ����*/
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� void Nm_CanTransferSuccess(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-8-21
************************************************************************************************************************
*/
void Nm_CanTransferSuccess(void)
{
    /*BusOff Recovery*/
    NmBusoffPara.bCANBusOffFlag = FALSE;
    NmBusoffPara.bCanTxStopFlg = FALSE;
    NmBusoffPara.u8BusOffCounter  = 0;
    NmBusoffPara.enBusOffRecoveryMode = BusOffFastRecoveryMode;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� BOOL Nm_IsCanBusOffTxStopValid(void)
* @brief �������-�Ƿ�ͣ��can����
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author 
* @date 2021-2-05
************************************************************************************************************************
*/
BOOL Nm_IsCanBusOffTxStopValid(void)
{
    return NmBusoffPara.bCanTxStopFlg;
}


/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void Nm_MsgReciver(void)
* @par ����
       ��������Ľ���ȡ���洦��
* @param[in] 
* @param[out] 
* @param[out] 
* @returns void
* @pre ��
* @note ��
* @author 
* @date 2021-02-04   
************************************************************************************************************************
*/
void Nm_MsgReciver(void)
{
    INT8U i = 0;
    INT32U msgId = 0;
    INT8U msgDlc = 0;
//    INT8U msgBuf[D_NM_FRAME_LEN] = {0};
    
//    volatile INT32U * pNmRxId = &CanRxActualNmId;
//    volatile INT8U * pNmRxBuf = nmRecvMess;
    BOOL tNmCtrl = ECUAL_CAN_IS_NM_RX_ENABLE();

	if(tNmCtrl != FALSE)
	{
//		if (NmCan_LData_RxDate(&msgId, &msgDlc, msgBuf) == TRUE)
		{
			if(msgDlc > 1U)
			{
//				*pNmRxId = msgId;
				for (i = 0; i < msgDlc; i++)
				{
//					pNmRxBuf[i] = msgBuf[i];
				}
//				NmPrecopy();
			}
		}
	}
}


