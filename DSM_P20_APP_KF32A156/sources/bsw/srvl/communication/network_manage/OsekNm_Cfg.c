/*****************************************************************************
               Copyright (C) 2016, Michip Technologies Co., Ltd
                             All Rights Reserved
******************************************************************************
?0?6?1?7?0?4?1?7?1?7?1?7: Osek.c
?1?7?0?4?1?7?1?7?1?7?1?7?1?7: OSEK Network Management
?1?7?1?7?1?7?1?7?1?7?1?7?0?4: wangyongxiang
?1?7?1?7?1?7?1?7?1?7?1?7?1?7?1?7: 2019-08-04
?1?7?1?7?1?7°汾: 0.0.1
?1?7?1?7?0?6?0?5?1?7?1?7: 
*****************************************************************************/
/* ============================ [ INCLUDES  ] ====================================================== */
#include "OsekNm.h"
#include <string.h>
//#include "Ecual_Api.h"
//#include "Ecual_Gpio.h"
//#include "Ecual_lin.h"
#include "CANDrv.h"
#include "OsekNmSleep.h"
/* ============================ [ MACROS    ] ====================================================== */
// NM Main Task Tick = 1 ms
//#define tTyp 20
//#define tMax 52
//#define tError 200
//#define tWBS   300
//#define tTx    4
#define tTyp 100
#define tMax 260
#define tError 1000
#define tWBS   1500
#define tTx    20
#define tTxApp	100



/* IPC Source Id */
#define OSEK_IPC_SID      0x08 
#define MJENV_OSEKNM_NODE_ID()  OSEK_IPC_SID
#define CANIF_ID_OSEK_NM_TX CANIF_TX_509

static enum {OsekIn_STARTED, OsekIn_STOPPED } OsekInStatus = OsekIn_STARTED;
static enum {OsekOd_STARTED, OsekOd_STOPPED } OsekOdStatus = OsekOd_STARTED;

volatile NmOsek_enCANSt NmOsek_engCANAppComm;

/*! @brief 开始lin报文传输指示 */
static BOOL ArNm_LinMsgStartTxCtrlInd = TRUE;
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void NM_D_Init(NetIdType NetId,RoutineRefType InitRoutine)
{
        InitRoutine(NetId);
}
void D_Offline(NetIdType NetId)
{
	//Switch off transmit path
	NmOsek_engCANAppComm = NmOsek_enmDisable;
	CANDrv_SetCanTxStopFlag(TRUE);//禅道1454
}
void D_Online(NetIdType NetId)
{
	//Switch on transmit path
	NmOsek_engCANAppComm = NmOsek_enmEnable;
	D_OnlineLin(NetId);
	CANDrv_SetCanTxStopFlag(FALSE);
}

/***********************************************************************************************
 * @function name: D_OfflineLin
 * @description: 设置LIN离线状态（禁止报文发送）
 * @input parameters: NetId 网络节点ID
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-06-18
 ***********************************************************************************************/
void D_OfflineLin(NetIdType NetId)
{
    ArNm_LinMsgStartTxCtrlInd = FALSE;
}

/***********************************************************************************************
 * @function name: D_OnlineLin
 * @description: 设置LIN在线状态（允许报文发送）
 * @input parameters: NetId 网络节点ID
 * @output parameters: void
 * @return: void
 * @author: ssj 2025-06-18
 ***********************************************************************************************/
void D_OnlineLin(NetIdType NetId)
{
    ArNm_LinMsgStartTxCtrlInd = TRUE;
}

/***********************************************************************************************
 * @function name: NM_GetLinMsgTxInd
 * @description: Lin报文发送标志位
 * @input parameters: void
 * @output parameters: void
 * @return: 是否发送Lin报文（BOOL）
 * @author: ssj 2025-06-18
 ***********************************************************************************************/
BOOL NM_GetLinMsgTxInd(void)
{
    return ArNm_LinMsgStartTxCtrlInd;
}

#if 0 //P20 发送接口
uint8_t D_Transmit(NetIdType NetId,NMPduType* NMPDU,uint8_t DataLengthTx)
{

	if(FALSE == Ecual_GetCANACKErrTxEnable()) //ACK无应答，不发送网络报文
	{
		return 1;
	}
	CANMsgRxBase pdu;
	uint8_t data[8];
	uint8_t i;

	memset(&pdu,0,sizeof(CANMsgRxBase));
	pdu.ID = NMPDU->Source + NM_CANID;
	pdu.DLC = DataLengthTx;
        
	memcpy(&data[2],NMPDU->RingData,DataLengthTx - 2);
        
	data[0] = NMPDU->Destination;
	data[1] = NMPDU->OpCode.b;
        
	for(i = 0; i <= pdu.DLC; i++)
	{
		pdu.DB[i] = data[i];
	}  

	if (OsekOdStatus == OsekOd_STARTED)
	{
		Ecual_CANSendQueue(NetId,&pdu);
		return 0;
	}
	else
	{
		return 1;
	}
           /*
*/
}
#endif
#if 1
uint8_t D_Transmit(NetIdType NetId,NMPduType* NMPDU,uint8_t DataLengthTx)
{
	if(FALSE == Ecual_GetCANACKErrTxEnable()) //ACK无应答，不发送网络报文
	{
		return 1;
	}
	memcpy((uint8_t *)&nmSendMess[2], NMPDU->RingData, DataLengthTx - 2);
        
	nmSendMess[0] = NMPDU->Destination;
	nmSendMess[1] = NMPDU->OpCode.b;

	if (OsekOdStatus == OsekOd_STARTED)
	{
		cMsgNeedTxIndFlag |= PEPS_NM_MSG_NEED_TX_FLAG_MASK;
		return 0;
	}
	else
	{
		return 1;
	}
           /*        
*/
}
#endif
/* Function needed by DLL */
void BusInit(NetIdType NetId)
{
	//Ecual_CANInit(0,CAN_BITRATE_500K);
}
void BusSleep(NetIdType NetId)
{	
    OsekNmSleep_SleepPre();
//	Ecual_LinStop(D_LIN_INSTANCE);
//
//	Ecual_GpioWriteCh(EN_MCU_PIN99_LIN_SLP, EN_GPIO_LEV_LOW);/*LIN休眠*/
//	Ecual_EcuSleepPre();/*确保休眠最后一步执行此函数2024.5.24 by Prima Niu */
	
//	Ecual_GpioWriteCh(EN_MCU_PIN34_CAN_EN, EN_GPIO_LEV_HIGH);/*EN引脚低高平待机模式*/
//	Ecual_GpioWriteCh(EN_MCU_PIN77_CAN_STB, EN_GPIO_LEV_LOW);
}
void BusAwake(NetIdType NetId)
{
	
}
void BusRestart(NetIdType NetId)
{

}

/* This is an example of how to write NMInit() */
void NMInit(NetIdType NetId)
{
	uint8_t config[32];
	NetworkStatusType status;
	(void)memset(config,0x01,32); /*care node :0,8,16,24,32,... */

	if(NetId == 0)
	{
		InitNMType(NetId,NM_DIRECT);
		InitNMScaling(NetId,0xFF); /* TODO: not used */
		InitCMaskTable(NetId,NM_ckNormal,config);
		InitCMaskTable(NetId,NM_ckLimphome,config);
		memset(&status,0,sizeof(NetworkStatusType));
		status.W.NMactive = 1;
		InitSMaskTable(NetId,&status); /* TODO : not implemented for indication */
		InitTargetStatusTable(NetId,&status);
		InitDirectNMParams(NetId,MJENV_OSEKNM_NODE_ID(),tTyp,tMax,tError,tWBS,tTx,tTxApp);
	}
}


void CanIf_OsekNmUserTxConfirmation()
{
	NM_TxConformation((NetIdType)0);
}

void CanIf_OsekNmUserRxIndication(INT8U RSCAN0Chl, const uint8_t *sduPtr, uint8_t dlc, Can_IdType canId)
{
	NMPduType pdu;
	pdu.Source = canId&0x7F;
        
	pdu.Destination = sduPtr[0];
	pdu.OpCode.b=sduPtr[1];

	memset(pdu.RingData,0,6);
	memcpy(pdu.RingData,&sduPtr[2],dlc-2);
	NM_RxIndication(RSCAN0Chl,&pdu);        
}

void Osek_RxIndication(INT8U RSCAN0Chl, const CANMsgRxBase * pFrame)
{
  if (OsekInStatus == OsekIn_STARTED)
  {
      CanIf_OsekNmUserRxIndication(RSCAN0Chl,pFrame->cData,pFrame->cDataLength,pFrame->cCANID);
  }
}

/*****************************************************************************
?1?7?1?7?1?7?1?7?1?7?1?7?1?7?1?7: void OsekNm_Stop(void)
?1?7?1?7?1?7?1?7?1?7?1?7?0?4: v0.1 2017-02-15 fabby
?1?7?1?7?1?7?1?7?0?5?1?7?1?7: ?0?5?0?9
*****************************************************************************/
void OsekNm_Stop(void)
{
    OsekInStatus = OsekIn_STOPPED;
    OsekOdStatus = OsekOd_STOPPED;
}

/*****************************************************************************
?1?7?1?7?1?7?1?7?1?7?1?7?1?7?1?7: void OsekNm_Start(void)
?1?7?1?7?1?7?1?7?1?7?1?7?0?4: v0.1 2017-02-15 fabby
?1?7?1?7?1?7?1?7?0?5?1?7?1?7: ?1?7?1?7?1?7?1?7
*****************************************************************************/
void OsekNm_Start(void)
{
    OsekInStatus = OsekIn_STARTED;
    OsekOdStatus = OsekOd_STARTED;
}


/***********************************************************************
 * @function name: OsekNm_GetOsekInOnStatus
 * 
 * @description: 获取网络收发状态
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-06-06 16:19
 ***********************************************************************/
INT8U OsekNm_GetOsekInOnStatus(void)
{
	return (INT8U)(OsekInStatus == OsekIn_STARTED ? 1 : 0);
}
