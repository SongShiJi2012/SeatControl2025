#define NM_GLOBALS

#include "Srvl_NM.h"
#include "Appl_PowerMangeModel.h"
#include "Ecual_CAN.h"

StrNmBusoffPara NmBusoffPara;

/*!
************************************************************************************************************************
* 接口原型 static void Nm_BusoffParaInit(void)
* @brief 初始化can busoff 管理参数为默认值
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
* 接口原型 void Nm_InitStart(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(刘发星)
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
* 接口原型 static void Nm_BusoffParaInit(void)
* @brief 网络管理-系统电压异常恢复正常后初始化下can模块,防止电压异常后导致can模块工作异常
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
//    Ecual_ClrCanWakeUpInd(); //清除唤醒源
    NmBusoffPara.bCanTxStopFlg = FALSE;
}

/*!
************************************************************************************************************************
* 接口原型 void Nm_CanBusOffRecoveryProcess(void)
* @brief 网络管理-busoff后的快恢复慢恢复实现
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
        
        if(NmBusoffPara.enBusOffRecoveryMode == BusOffFastRecoveryMode)//快恢复模式
        {
            if(NmBusoffPara.bCanTxStopFlg == TRUE)
            {
                NmBusoffPara.u8BusOffRecoveryCounter++;
                if(NmBusoffPara.u8BusOffRecoveryCounter >= NM_BUS_OFF_FAST_RECOVERY_TIME)
                {
                    NmBusoffPara.u8BusOffRecoveryCounter = 0;
                    NmBusoffPara.bCanTxStopFlg = FALSE;//重新使能发送报文
                    nmSetAlarmStart(1000);
//					Srvl_NMSetSendFlag(OSEK_ENABLE);/*快恢复首先发送NM报文20230314 by Prima Niu*/
                    if(NmBusoffPara.u8BusOffCounter >= NM_COUNT_SHORT_NUMBER)
                    {
                        NmBusoffPara.enBusOffRecoveryMode = BusOffSlowRecoveryMode;//到达指定次数则切换到慢恢复模式
                    }
                }
            }
        }
        else if(NmBusoffPara.enBusOffRecoveryMode == BusOffSlowRecoveryMode)//慢恢复模式
        {
            if(NmBusoffPara.bCanTxStopFlg == TRUE)
            {
                NmBusoffPara.u8BusOffRecoveryCounter++;
                if(NmBusoffPara.u8BusOffRecoveryCounter >= NM_BUS_OFF_SLOW_RECOVERY_TIME)
                {
//					Srvl_NMSetSendFlag(OSEK_ENABLE);/*慢恢复首先发送NM报文20230314 by Prima Niu*/
                    NmBusoffPara.u8BusOffRecoveryCounter = 0;
                    nmSetAlarmStart(1000);
                    NmBusoffPara.bCanTxStopFlg = FALSE;//重新使能发送报文
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
* @par 接口原型
       INT8U Nm_CanGetBusOffTrgCnt(void)
* @par 描述
       获取busoff发生次数
* @param[in] NmBusoffPara.u8BusOffCounter
* @param[out] void
* @returns INT8U：bus off发送次数
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-11-1
************************************************************************************************************************
*/

INT8U Nm_CanGetBusOffTrgCnt(void)
{
    return NmBusoffPara.u8BusOffCounter;
}

/*!
************************************************************************************************************************
* 接口原型 void Nm_ErrorHandle(void)
* @brief can bus error handle
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(刘发星)
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
* 接口原型 BOOL Nm_IsBusOff(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(刘发星)
* @date 2019-8-21
************************************************************************************************************************
*/

BOOL Nm_IsBusOff(void)
{
    return NmBusoffPara.bCANBusOffFlag;
}

/*!
************************************************************************************************************************
* @par 接口原型
       void Nm_MsgTransfer(void)
* @par 描述
       网络管理报文发送
* @param[in] 
* @param[out] 
* @param[out] 
* @returns void
* @pre 无
* @note 周期性调用,NM FIFO中有数据需发送时触发实际发送
* @author Lews Hammond(刘发星)
* @date 2019-10-24
************************************************************************************************************************
*/
void Nm_MsgTransfer(void)
{
//    NmCan_TxPduInd(); /*判断FIFO中是否有数据需要发送*/
}

/*!
************************************************************************************************************************
* 接口原型 void Nm_CanTransferSuccess(void)
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(刘发星)
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
* 接口原型 BOOL Nm_IsCanBusOffTxStopValid(void)
* @brief 网络管理-是否停发can报文
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
* @par 接口原型
       void Nm_MsgReciver(void)
* @par 描述
       网络管理报文接收取缓存处理
* @param[in] 
* @param[out] 
* @param[out] 
* @returns void
* @pre 无
* @note 无
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


