/*****************************************************************************
               Copyright (C) 2016, Michip Technologies Co., Ltd
                             All Rights Reserved
******************************************************************************
??????: Osek.c
???????: OSEK Network Management
???????: wangyongxiang
????????: 2019-08-04
???���: 0.0.1
??????:
*****************************************************************************/

/* ============================ [ INCLUDES  ] ====================================================== */
#include <Ecual_lin.h>
#include "OsekNm.h"
#include "uds_pub.h"
//#include "Srvl_SimulinkInterface.h"
#include "OSekNmSleep.h"
#include "CpuPeripheralInit.h"
#include "CANDrv.h"
#include "Srvl_NM.h"

volatile INT8U nmSendMess[8];
/* ============================ [ MACROS    ] ====================================================== */
#define rx_limit 4
#define tx_limit 8

#define NET_ID 0

#define NM_LIMPHONE_DELAY_SLEEP_TIME	(5000UL)	/* ����limphome״̬����ʱ����ʱ��   */

/* Alarm Management */
#define nmSetAlarm(Timer)				\
do										\
{										\
	/*NM_ControlBlock[NET_ID].Alarm._##Timer = 1+NM_ControlBlock[NET_ID].nmDirectNMParams._##Timer;*/	\
	NM_ControlBlock[NET_ID].Alarm._##Timer = D_HAL_GET_CUR_MS_TS();	\
}while(0)

/* signal the alarm to process one step/tick forward */
#define nmSingalAlarm(Timer)								\
do															\
{															\
	 if(NM_ControlBlock[NET_ID].Alarm._##Timer > 1)			\
	 {														\
		(NM_ControlBlock[NET_ID].Alarm._##Timer)--;			\
	 }														\
}while(0)

//#define nmIsAlarmTimeout(Timer)  (1 == NM_ControlBlock[NET_ID].Alarm._##Timer)
#define nmIsAlarmTimeout(Timer)  (CPU_TimerDiffTs( NM_ControlBlock[NET_ID].Alarm._##Timer) >= NM_ControlBlock[NET_ID].nmDirectNMParams._##Timer)
	
#define nmIsAlarmStarted(Timer)	 (0 != NM_ControlBlock[NET_ID].Alarm._##Timer)

#define nmCancelAlarm(Timer)					\
do												\
{												\
	NM_ControlBlock[NET_ID].Alarm._##Timer = 0;	\
}while(0)

#define nmSendMessage()					\
do{										\
	StatusType ercd;					\
	ercd = D_Transmit(NetId,&(NM_ControlBlock[NET_ID].nmTxPdu),8);		\
	if(ercd != E_OK)					\
	{									\
		nmSetAlarm(TTx); /* re-Transmit after TTx */						\
	}									\
}while(0)

#define AS_LOG_OSEK_NM 1
#define nmDebug(str) ASLOG(OSEK_NM,str)
/* ============================ [ TYPES     ] ====================================================== */
/* OK we could see terrible thing here, too big the struct is. */
typedef struct
{
	NMType nmType;
	ScalingParamType nmScalingParams; /* not used */
	struct
	{
		uint8_t normal[32];
		uint8_t normalExtended[32];
		uint8_t limphome[32];
	}nmConfig;
	struct
	{
		uint8_t normal[32];
		uint8_t normalExtended[32];
		uint8_t limphome[32];
	}nmCMask;
	struct
	{
		struct{
			SignallingMode SMode;
			//TaskType TaskId;
			//EventMaskType EMask;
		}normal;
		struct{
			SignallingMode SMode;
			//TaskType TaskId;
			//EventMaskType EMask;
		}normalExtended;
		struct{
			SignallingMode SMode;
			//TaskType TaskId;
			//EventMaskType EMask;
		}limphome;
	}nmIndDeltaConfig;
	struct{
		NetworkStatusType SMask;
		NetworkStatusType NetworkStatus;
		SignallingMode SMode;
		//TaskType TaskId;
		//EventMaskType EMask;
	}nmStatus;
	struct{
		SignallingMode SMode;
		//TaskType TaskId;
		//EventMaskType EMask;
	}nmRingDataInd;
	union
	{
		uint32_t w;
		struct
		{
			unsigned stable : 1;
			unsigned limphome : 1;
		}W;
	}nmMerker; /* TODO: what's the meaning? */
	NMStateType nmState;
	struct
	{
		uint8_t NodeId;
		TickType _TTx;
		TickType _TTyp;
		TickType _TMax;
		TickType _TError;
		TickType _TWbs;
		TickType _TTxApp;
	}nmDirectNMParams;
	uint8_t nmRxCount;
	uint8_t nmTxCount;
	struct{
		TickType _TTx;
		TickType _TTyp;
		TickType _TMax;
		TickType _TError;
		TickType _TWbs;
		TickType _TTxApp;
	}Alarm;
	NMPduType nmTxPdu;
}NM_ControlBlockType;
/* ============================ [ DECLARES  ] ====================================================== */
void NMInit(uint8_t NetId);
static void nmInit3(uint8_t NetId);
static void nmAddtoPresent(uint8_t NetId,uint8_t NodeId);
static void nmAddtoLimphome(uint8_t NetId,uint8_t NodeId);
static void nmInitReset5(uint8_t NetId);
static void nmInitReset6(uint8_t NetId);
static void nmAddToConfig(uint8_t NetId,ConfigKindName ConfigKind,uint8_t NodeId);
static void nmRemoveFromConfig(uint8_t NetId,ConfigKindName ConfigKind,uint8_t NodeId);
static void nmNormalStandard(uint8_t NetId,NMPduType* NMPDU);
static uint8_t nmDetermineLS(uint8_t S,uint8_t R,uint8_t L);
static boolean nmIsMeSkipped(uint8_t S,uint8_t R,uint8_t D);
static void nmBusSleep(uint8_t NetId);
static void nmNormalTwbsMain(uint8_t NetId);
static void nmNormalPrepSleepMain(uint8_t NetId);
static void nmLimphomeMain(uint8_t NetId);
static void nmLimphomePrepSleepMain(uint8_t NetId);
static void nmNormalMain(uint8_t NetId);
static void nmTwbsLimphomeMain(uint8_t NetId);
static void nmSleepCheck(uint8_t NetId);

/* ============================ [ DATAS     ] ====================================================== */
NM_ControlBlockType NM_ControlBlock[OSEKNM_NET_NUM];

//static BOOL s_DelayFlag = 0;

static BOOL s_NodeSkippedFlg = 0;



/* ============================ [ LOCALS    ] ====================================================== */
/* nmInit3 is special doesn't mean all the operation of "Leave NMBusSleep" */
static void nmInit3(uint8_t NetId)
{
	/* step 3: config.limphome  := 0 */
	memset(NM_ControlBlock[NetId].nmConfig.limphome,0,32);
	/* step 4: */
	NM_ControlBlock[NetId].nmRxCount = 0;
	NM_ControlBlock[NetId].nmTxCount = 0;
	D_Online(NetId);
	nmInitReset6(NetId);
}
static void nmAddtoPresent(uint8_t NetId,uint8_t NodeId)
{
	uint8_t RefConfig[32]; /* old config */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode != SignalInvalid)
	{
		memcpy(RefConfig,NM_ControlBlock[NetId].nmConfig.normal,32);
	}
	nmAddToConfig(NetId,NM_ckNormal,NodeId);
	nmRemoveFromConfig(NetId,NM_ckLimphome,NodeId);
	/* If enable do Indication */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode != SignalInvalid)
	{
		StatusType ercd;
		ercd = CmpConfig(NetId,NM_ControlBlock[NetId].nmConfig.normal,RefConfig,NM_ControlBlock[NetId].nmCMask.normal);
		if(ercd != E_OK)
		{ /* do ind */
			if(NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode == SignalActivation)
			{
			}
			else
			{

			}
		}
	}
}
static void nmAddtoLimphome(uint8_t NetId,uint8_t NodeId)
{
	uint8_t RefConfig[32]; /* old config */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode != SignalInvalid)
	{
		memcpy(RefConfig,NM_ControlBlock[NetId].nmConfig.limphome,32);
	}
	nmAddToConfig(NetId,NM_ckLimphome,NodeId);
	/* If enable do Indication */
	if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode != SignalInvalid)
	{
		StatusType ercd;
		ercd = CmpConfig(NetId,NM_ControlBlock[NetId].nmConfig.limphome,RefConfig,NM_ControlBlock[NetId].nmCMask.limphome);
		if(ercd != E_OK)
		{ /* do ind */
			if(NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode == SignalActivation)
			{
			}
			else
			{

			}
		}
	}
}
static void nmInitReset5(uint8_t NetId)
{
	nmCancelAlarm(TError);
	NM_ControlBlock[NetId].nmMerker.W.limphome = 0;

	NM_ControlBlock[NetId].nmRxCount = 0;
	NM_ControlBlock[NetId].nmTxCount = 0;
	D_Online(NetId);
	nmInitReset6(NetId);
}
static void nmInitReset6(uint8_t NetId)
{
	NM_ControlBlock[NetId].nmState= NM_stInitReset;
	/* config.present = own station */
	memset(NM_ControlBlock[NetId].nmConfig.normal,0,32);
	nmAddtoPresent(NetId,NM_ControlBlock[NetId].nmDirectNMParams.NodeId);
	/* logical successor := own station */
	NM_ControlBlock[NetId].nmTxPdu.Destination = NM_ControlBlock[NetId].nmDirectNMParams.NodeId;
	NM_ControlBlock[NetId].nmRxCount += 1;
	/* Initialise the NMPDU(Data,OpCode) */
	NM_ControlBlock[NetId].nmTxPdu.OpCode.b = 0;
	memset(NM_ControlBlock[NetId].nmTxPdu.RingData,0,sizeof(RingDataType));
	/* Cancel all Alarm */
	nmCancelAlarm(TTx);
	nmCancelAlarm(TTyp);
	nmCancelAlarm(TMax);
	nmCancelAlarm(TWbs);
	nmCancelAlarm(TError);
	if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
	{
		NM_ControlBlock[NetId].nmTxCount += 1;
		/* Send A alive message */
		NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskAlive;
  		nmSendMessage();
		//nmDebug("nmInitReset6:Send Alive,");
	}
	if((NM_ControlBlock[NetId].nmTxCount <= tx_limit)	&&
		(NM_ControlBlock[NetId].nmRxCount <= rx_limit))
	{
		nmSetAlarm(TTyp);
		NM_ControlBlock[NetId].nmState = NM_stNormal;
		//nmDebug("Set TTyp, enter Normal state.\n");
	}
	else
	{
		nmSetAlarm(TError);
		NM_ControlBlock[NetId].nmState = NM_stLimphome;
		//nmDebug("Set TError, Enter Limphome state.\n");
	}
}
#if 0
StatusType GetStatus(uint8_t NetId,StatusRefType NetworkStatus) {
    /** @req OSEKNM045 */
    StatusType status = E_OK;

    memcpy(NetworkStatus, &NM_ControlBlock[NetId].nmStatus.NetworkStatus, sizeof(NetworkStatusType));
    return status;
}
#endif

StatusType GetStatus(uint8_t NetId,NMStateType* nmState){
    /** @req OSEKNM045 */
    StatusType status = E_OK;

    *nmState = NM_ControlBlock[NetId].nmState;
   
    return status;
}

static void nmNormalStandard(uint8_t NetId,NMPduType* NMPDU)
{
	NM_ControlBlock[NetId].nmRxCount = 0;
	if(NMPDU->OpCode.B.Limphome)
	{
		/* add sender to config.limphome */
		nmAddtoLimphome(NetId,NMPDU->Source);
	}
	else
	{
		/* add sender to config.present */
		nmAddtoPresent(NetId,NMPDU->Source);
		/* determine logical successor */
		NM_ControlBlock[NetId].nmTxPdu.Destination = nmDetermineLS(NMPDU->Source,	\
									NM_ControlBlock[NetId].nmDirectNMParams.NodeId,	\
										NM_ControlBlock[NetId].nmTxPdu.Destination);
		if(NMPDU->OpCode.B.Ring)
		{
			nmCancelAlarm(TTyp);
			nmCancelAlarm(TMax);
			/* see nm253 Figure 4 Mechanism to transfer application data via the logical ring */
			memcpy(NM_ControlBlock[NetId].nmTxPdu.RingData,NMPDU->RingData,sizeof(RingDataType));
			if((NMPDU->Destination == NM_ControlBlock[NetId].nmDirectNMParams.NodeId) /* to me */
				|| (NMPDU->Destination == NMPDU->Source)) /* or D = S */
			{
				nmSetAlarm(TTyp);
				/* Do Ring Data indication */
				if(NM_ControlBlock[NetId].nmRingDataInd.SMode == SignalEvent)
				{
				}
				else if(NM_ControlBlock[NetId].nmRingDataInd.SMode == SignalActivation)
				{
				}
				else
				{
					/* invalid as InitIndRingData hasn't been called before. */
				}

			}
			else
			{
				nmSetAlarm(TMax);
				if(nmIsMeSkipped(NMPDU->Source,NM_ControlBlock[NetId].nmDirectNMParams.NodeId,NMPDU->Destination))
				{
					s_NodeSkippedFlg = TRUE;
//					if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
//					{
//						NM_ControlBlock[NetId].nmTxPdu.OpCode.b= NM_MaskAlive;
//						NM_ControlBlock[NetId].nmTxPdu.Destination= NM_ControlBlock[NetId].nmDirectNMParams.NodeId;
//						if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
//						{
//							NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 1;
//						}
//						nmSendMessage();
//					}
				}
			}
		}
	}
}
static uint8_t nmDetermineLS(uint8_t S,uint8_t R,uint8_t L)
{
	uint8_t newL = L;
	if(L==R)
	{
		newL = S;
	}
	else
	{
		if(L<R)
		{
			if(S<L)
			{
				newL = S; /* SLR */
			}
			else
			{
				if(S<R)
				{
					/* LSR */
				}
				else
				{
					newL = S; /* LRS */
				}
			}
		}
		else
		{
			if(S<L)
			{
				if(S<R)
				{
					/* SRL */
				}
				else
				{
					newL = S; /* RSL */
				}
			}
			else
			{
				/* RLS */
			}
		}
	}
	return newL;
}
static boolean nmIsMeSkipped(uint8_t S,uint8_t R,uint8_t D)
{
	boolean isSkipped = FALSE;
	if(D<R)
	{
		if(S<D)
		{
			/* not skipped SDR */
		}
		else
		{
			if(S<R)
			{
		        isSkipped = TRUE; /* DSR */	
			}
			else
			{
		        /* not skipped DRS */
			}
		}
	}
	else
	{
		if(S<D)
		{
			if(S<R)
			{
				isSkipped = TRUE; /* SRD */
			}
			else
			{
				/* RSD */
			}
		}
		else
		{
			isSkipped = TRUE; /* RDS */
		}
	}
	return isSkipped;
}
static void nmAddToConfig(uint8_t NetId,ConfigKindName ConfigKind,uint8_t NodeId)
{
	ConfigRefType Config = NULL;
	switch(ConfigKind)
	{
		case NM_ckNormal:
			Config = NM_ControlBlock[NetId].nmConfig.normal;
			break;
		case NM_ckNormalExtended:
			Config = NM_ControlBlock[NetId].nmConfig.normalExtended;
			break;
		case NM_ckLimphome:
			Config = NM_ControlBlock[NetId].nmConfig.limphome;
			break;
		default:
			break;
	}
	if(NULL != Config)
	{
		uint8_t byte    = NodeId/8;
		uint8_t bit     = NodeId%8;
		Config[byte] |= (1u<<bit);
	}
}

static void nmRemoveFromConfig(uint8_t NetId,ConfigKindName ConfigKind,uint8_t NodeId)
{
	ConfigRefType Config = NULL;
	switch(ConfigKind)
	{
		case NM_ckNormal:
			Config = NM_ControlBlock[NetId].nmConfig.normal;
			break;
		case NM_ckNormalExtended:
			Config = NM_ControlBlock[NetId].nmConfig.normalExtended;
			break;
		case NM_ckLimphome:
			Config = NM_ControlBlock[NetId].nmConfig.limphome;
			break;
		default:
			break;
	}
	if(NULL != Config)
	{
		uint8_t byte    = NodeId/8;
		uint8_t bit     = NodeId%8;
		Config[byte] &= (~(1u<<bit));
	}
}
static void nmNormalMain(uint8_t NetId)
{
	if(s_NodeSkippedFlg == TRUE)//�ڵ㱻����
	{
		s_NodeSkippedFlg = FALSE;
		if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
		{
			NM_ControlBlock[NetId].nmTxPdu.OpCode.b= NM_MaskAlive;
			//�ڵ㱻���������º�̽ڵ�(�ͻ�����)
//			NM_ControlBlock[NetId].nmTxPdu.Destination= NM_ControlBlock[NetId].nmDirectNMParams.NodeId;
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
			{
				NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 1;
			}
			nmSendMessage();
		}
	}
	if(nmIsAlarmStarted(TTyp))
	{
		//nmSingalAlarm(TTyp);
		if(nmIsAlarmTimeout(TTyp))
		{
			nmCancelAlarm(TTyp);
			nmCancelAlarm(TMax);
			nmSetAlarm(TMax);
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskRing;
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{
					NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 1;
				}
				NM_ControlBlock[NetId].nmTxCount ++;
				nmSendMessage();
			}
			else
			{
			}
			if(NM_ControlBlock[NetId].nmTxCount > tx_limit)
			{
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
			}
			else
			{
				if(NM_ControlBlock[NetId].nmMerker.W.stable)
				{
					NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.configurationstable = 1;
				}
				else
				{
					NM_ControlBlock[NetId].nmMerker.W.stable = 1;
				}
			}
		}
	}

	if(nmIsAlarmStarted(TMax))
	{
//		nmSingalAlarm(TMax);
		if(nmIsAlarmTimeout(TMax))
		{
			nmCancelAlarm(TMax);
			nmInitReset6(NetId);
		}
	}
}
static void nmLimphomeMain(uint8_t NetId)
{
	if(nmIsAlarmStarted(TError))
	{
//		nmSingalAlarm(TError);
		if(nmIsAlarmTimeout(TError))
		{
			nmCancelAlarm(TError);
			D_Online(NetId);
			NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskLimphome;
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
			{
				nmSetAlarm(TMax);
				NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd =1;
				NM_ControlBlock[NetId].nmState = NM_stLimphomePrepSleep;
			}
			else
			{
				nmSetAlarm(TError);
			}
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				/* NM_ControlBlock[NetId].nmTxPdu.Destination = NM_ControlBlock[NetId].nmDirectNMParams.NodeId; */
				nmSendMessage();
			}
		}
	}
}
static void nmNormalPrepSleepMain(uint8_t NetId)
{
	if(nmIsAlarmStarted(TTyp))
	{
//		nmSingalAlarm(TTyp);
		if(nmIsAlarmTimeout(TTyp))
		{
			nmCancelAlarm(TTyp);
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				/* Send ring message with set sleep.ack bit */
				NM_ControlBlock[NetId].nmTxPdu.OpCode.b = NM_MaskRing|NM_MaskSI|NM_MaskSA;
				nmSendMessage();
			}
		}
	}
        
    if(nmIsAlarmStarted(TMax))
	{
//		nmSingalAlarm(TMax);
		if(nmIsAlarmTimeout(TMax))
		{
			nmCancelAlarm(TMax);
			nmInitReset6(NetId);
		}
	}
}
static void nmBusSleep(uint8_t NetId)
{
	NM_D_Init(NetId,BusSleep);
	NM_ControlBlock[NetId].nmState = NM_stBusSleep;
}
static void nmNormalTwbsMain(uint8_t NetId)
{
	if(nmIsAlarmStarted(TWbs))
	{
//		nmSingalAlarm(TWbs);
		if(nmIsAlarmTimeout(TWbs))
		{
			nmCancelAlarm(TWbs);
			nmBusSleep(NetId);
		}
	}
}
static void nmLimphomePrepSleepMain(uint8_t NetId)
{
	if(nmIsAlarmStarted(TMax))
	{
//		nmSingalAlarm(TMax);
		if(nmIsAlarmTimeout(TMax))
		{
			nmCancelAlarm(TMax);
			/* 7 NMInitBusSleep */
			D_Offline(NetId);
			Ecaul_LinTxSleepMsg();//����lin���߱���
			D_OfflineLin(NetId);
			nmSetAlarm(TWbs);
			NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
		}
	}
}
static void nmTwbsLimphomeMain(uint8_t NetId)
{
	if(nmIsAlarmStarted(TWbs))
	{
//		nmSingalAlarm(TWbs);
		if(nmIsAlarmTimeout(TWbs))
		{
			nmCancelAlarm(TWbs);
			nmBusSleep(NetId);
		}
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void InitNMType(uint8_t NetId,NMType nmType)
{
	NM_ControlBlock[NetId].nmType = nmType;
}

void InitNMScaling(uint8_t NetId,ScalingParamType ScalingParams)
{
	NM_ControlBlock[NetId].nmScalingParams = ScalingParams;
}
void InitCMaskTable(uint8_t NetId,ConfigKindName ConfigKind,ConfigRefType CMask)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.normal,CMask,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.normalExtended,CMask,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(NM_ControlBlock[NetId].nmCMask.limphome,CMask,32);
			break;
		default:
			break;
	}
}

void InitTargetConfigTable(uint8_t NetId,ConfigKindName ConfigKind,ConfigRefType TargetConfig)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.normal,TargetConfig,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.normalExtended,TargetConfig,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(NM_ControlBlock[NetId].nmConfig.limphome,TargetConfig,32);
			break;
		default:
			break;
	}
}
#if 0
void InitIndDeltaConfig(uint8_t NetId,ConfigKindName ConfigKind,SignallingMode SMode,	\
				TaskType TaskId,EventMaskType EMask)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normal.EMask = EMask;
			break;
		case NM_ckNormalExtended:
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.normalExtended.EMask = EMask;
			break;
		case NM_ckLimphome:
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.SMode = SMode;
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.TaskId = TaskId;
			NM_ControlBlock[NetId].nmIndDeltaConfig.limphome.EMask = EMask;
			break;
		default:
			break;
	}
}
#endif
void InitSMaskTable(uint8_t NetId,StatusRefType SMask)
{
	NM_ControlBlock[NetId].nmStatus.SMask = *SMask;
}
void InitTargetStatusTable(uint8_t NetId,StatusRefType TargetStatus)
{
	NM_ControlBlock[NetId].nmMerker.w = 0;
	NM_ControlBlock[NetId].nmStatus.NetworkStatus = *TargetStatus;
}
#if 0
void InitIndDeltaStatus(uint8_t NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask)
{
	NM_ControlBlock[NetId].nmStatus.SMode = SMode;
	NM_ControlBlock[NetId].nmStatus.TaskId = TaskId;
	NM_ControlBlock[NetId].nmStatus.EMask = EMask;
}
#endif
StatusType InitConfig(uint8_t NetId)
{

	return E_OK;
}
StatusType GetConfig(uint8_t NetId,ConfigRefType Config,ConfigKindName ConfigKind)
{
	switch(ConfigKind)
	{
		case NM_ckNormal:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.normal,32);
			break;
		case NM_ckNormalExtended:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.normalExtended,32);
			break;
		case NM_ckLimphome:
			(void)memcpy(Config,NM_ControlBlock[NetId].nmConfig.limphome,32);
			break;
		default:
			break;
	}
	return E_OK;
}

StatusType CmpConfig(uint8_t NetId,ConfigRefType TestConfig,ConfigRefType RefConfig,ConfigRefType CMask)
{
	StatusType ercd = E_OK;
	uint8_t i;
	uint8_t result;
	for(i=0;i<32;i++)
	{
		result = TestConfig[i]^RefConfig[i];
		result &= CMask[i];
		result = ~result;
		if(result != 0xFFU)
		{
			ercd = E_NOT_OK; /* TestConfig != RefConfig, */
			break;
		}
	}
	return ercd;
}

void InitDirectNMParams(uint8_t NetId,uint8_t NodeId,TickType TimerTyp,TickType TimerMax, 	\
								TickType TimerError,TickType TimerWaitBusSleep,TickType TimerTx,TickType TimerTxApp)
{
	NM_ControlBlock[NetId].nmDirectNMParams.NodeId = NodeId;
	NM_ControlBlock[NetId].nmDirectNMParams._TTyp = TimerTyp;
	NM_ControlBlock[NetId].nmDirectNMParams._TMax = TimerMax;
	NM_ControlBlock[NetId].nmDirectNMParams._TError = TimerError;
	NM_ControlBlock[NetId].nmDirectNMParams._TWbs = TimerWaitBusSleep;
	NM_ControlBlock[NetId].nmDirectNMParams._TTx = TimerTx;
	NM_ControlBlock[NetId].nmDirectNMParams._TTxApp = TimerTxApp;
	NM_ControlBlock[NetId].nmTxPdu.Source = NodeId;
}

/* see nm253.pdf Figure 30 Start-up of the network */
StatusType StartNM(uint8_t NetId)
{
	StatusType ercd = E_OK;
	/* Reset Control block, value 0 = invalid or initialize value */
	memset(&NM_ControlBlock[NetId],0,sizeof(NM_ControlBlockType));
	/* step 1: */
	NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd = 0;
	NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepAck = 0;
	/* step 2: enter NMInit */
	NM_ControlBlock[NetId].nmState= NM_stInit;
	NMInit(NetId);
	NM_D_Init(NetId,BusInit);
	ECUAL_CAN_DISABLE_APP_TX_ENABLE();
	nmInit3(NetId);
	D_Offline(NetId); //���������������Ӧ�ñ��ģ���ȴ���һ֡���籨���ȷ���
	return ercd;
}

StatusType StopNM(uint8_t NetId)
{
	NM_ControlBlock[NetId].nmState= NM_stOff;
	return E_OK;
}
#if 0
void InitIndRingData(uint8_t NetId,SignallingMode SMode,TaskType TaskId,EventMaskType EMask)
{
	NM_ControlBlock[NetId].nmRingDataInd.SMode = SMode;
	NM_ControlBlock[NetId].nmRingDataInd.TaskId = TaskId;
	NM_ControlBlock[NetId].nmRingDataInd.EMask = EMask;
}
#endif
void ReadRingData(uint8_t NetId,RingDataRefType RingData)
{
	memcpy(RingData,NM_ControlBlock[NetId].nmTxPdu.RingData,sizeof(RingDataType));
}
void TransmitRingData(uint8_t NetId,RingDataRefType RingData)
{
	memcpy(NM_ControlBlock[NetId].nmTxPdu.RingData,RingData,sizeof(RingDataType));
}
StatusType GotoMode(uint8_t NetId,NMModeName NewMode)
{
	if(NewMode == NM_BusSleep)
	{
		NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep = 1;
		switch(NM_ControlBlock[NetId].nmState)
		{
			case NM_stNormal:
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
				{
					/* NMNormal */
				}
				else
				{
					//nmDebug("GotoMode_BusSleep,Enter NormalPrepSleep.\n");
					NM_ControlBlock[NetId].nmState = NM_stNormalPrepSleep;
				}
				break;
			}
			default:
				break;
		}
	}
	else if(NewMode == NM_Awake)
	{
		NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep = 0;
		switch(NM_ControlBlock[NetId].nmState)
		{
			case NM_stNormalPrepSleep:
			{
				NM_ControlBlock[NetId].nmState = NM_stNormal;
				break;
			}
			case NM_stTwbsNormal:
			{
				nmCancelAlarm(TWbs);
				nmInitReset6(NetId);
				break;
			}
			case NM_stBusSleep:
			{
				NM_D_Init(NetId,BusAwake);
				nmInit3(NetId);
				break;
			}
			case NM_stLimphomePrepSleep:
			{
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
				break;
			}
			case NM_stTwbsLimphome:
			{
				nmCancelAlarm(TWbs);
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
				nmSetAlarm(TError);
				break;
			}
			default:
				break;
		}
	}

	return E_OK;
}
StatusType SilentNM(uint8_t NetId)
{
	NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive = 0;
	return E_OK;
}
StatusType TalkNM(uint8_t NetId)
{
	NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive = 1;
	return E_OK;
}
void NM_BusErrorIndication(uint8_t NetId)
{
	D_Offline(NetId);
	NM_D_Init(NetId,BusRestart);
	nmSetAlarm(TError);
	NM_ControlBlock[NetId].nmState = NM_stLimphome;
}
void NM_TxConformation(uint8_t NetId)
{
	NM_ControlBlock[NetId].nmTxCount = 0;
	switch(NM_ControlBlock[NetId].nmState)
	{
		case NM_stNormal:
		{
			if(FALSE == GetAPPCommDisable())//���δ����app����ͣ���ſɿ�����ʱ��
        	{
           		nmSetAlarm(TTxApp);//��һ֡���籨�ķ��ͳɹ���������App���Ķ�ʱ��
        	}
			
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Ring)
			{
				nmCancelAlarm(TTxApp);//����Ring���Ĳ���������Ӧ�ñ��Ķ�ʱ��
				nmCancelAlarm(TTyp);
				nmCancelAlarm(TMax);
				nmSetAlarm(TMax);
				if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepInd)
				{
					if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
					{
						NM_ControlBlock[NetId].nmTxPdu.OpCode.B.SleepAck = 1;
						NM_ControlBlock[NetId].nmState = NM_stNormalPrepSleep;
					}
				}
			}
			break;
		}
		case NM_stNormalPrepSleep:
		{	/* 2 NMInitBusSleep */
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Ring)
			{
				D_Offline(NetId);
				Ecaul_LinTxSleepMsg();//����lin���߱���
				D_OfflineLin(NetId);
				nmSetAlarm(TWbs);
				NM_ControlBlock[NetId].nmState = NM_stTwbsNormal;
			}
			break;
		}
		case NM_stLimphome:
		{
			if(NM_ControlBlock[NetId].nmTxPdu.OpCode.B.Limphome)
			{
				NM_ControlBlock[NetId].nmMerker.W.limphome = 1;
			}
			//busoff 
			if(FALSE == GetAPPCommDisable())//���δ����app����ͣ���ſɿ�����ʱ��
        	{
           		nmSetAlarm(TTxApp);//��һ֡���籨�ķ��ͳɹ���������App���Ķ�ʱ��
        	}
			break;
		}
		default:
			break;
	}
}
void NM_RxIndication(uint8_t NetId,NMPduType* NMPDU)
{
	switch(NM_ControlBlock[NetId].nmState)
	{
		case NM_stNormal:
		case NM_stNormalPrepSleep:
		{
			nmNormalStandard(NetId,NMPDU);
			if(NMPDU->OpCode.B.SleepAck)
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{ /* 2 NMInitBusSleep */
					D_Offline(NetId);
					Ecaul_LinTxSleepMsg();//����lin���߱���
					D_OfflineLin(NetId);
					nmSetAlarm(TWbs);
					NM_ControlBlock[NetId].nmState = NM_stTwbsNormal;
				}
			}
			/* Special process for NM_stNormalPrepSleep only */
			if(NM_stNormalPrepSleep == NM_ControlBlock[NetId].nmState)
			{
				if(NMPDU->OpCode.B.SleepInd)
				{
				}
				else
				{
					NM_ControlBlock[NetId].nmState = NM_stNormal;
				}
			}
			break;
		}
		case NM_stTwbsNormal:
		{
			if(NMPDU->OpCode.B.SleepInd || NMPDU->OpCode.B.SleepAck)
			{  	/* ind = 1 || ack = 1 */
			}
			else
			{	/* = 0 */
				nmCancelAlarm(TWbs);
				nmInitReset6(NetId);
			}
			break;
		}
		case NM_stLimphome:
		{
			if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.NMactive)
			{
				if(NM_ControlBlock[NetId].nmMerker.W.limphome)
				{
					if( (NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep) && (NMPDU->OpCode.B.SleepAck))
					{
						D_Offline(NetId);
						Ecaul_LinTxSleepMsg();//����lin���߱���
						D_OfflineLin(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						// 重置 休眠条件后延时时间计时器
						resetS_delayTimer();
						nmInitReset5(NetId);
					}
				}
				else
				{
					if(NMPDU->OpCode.B.SleepAck)
					{
						D_Offline(NetId);
						Ecaul_LinTxSleepMsg();//����lin���߱���
						D_OfflineLin(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
			}
			else
			{
				if(NM_ControlBlock[NetId].nmMerker.W.limphome)
				{
					if( (NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep) && (NMPDU->OpCode.B.SleepAck))
					{
						D_Offline(NetId);
						Ecaul_LinTxSleepMsg();//����lin���߱���
						D_OfflineLin(NetId);
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
				else
				{
					if(NMPDU->OpCode.B.SleepAck)
					{
						D_Offline(NetId);
						D_OfflineLin(NetId);;
						Ecaul_LinTxSleepMsg();//����lin���߱���
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						nmInitReset5(NetId);
					}
				}
			}
			break;
		}
		case NM_stLimphomePrepSleep:
		{
			if(NM_ControlBlock[NetId].nmMerker.W.limphome)
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{
					if(1 == NMPDU->OpCode.B.SleepAck)//
					{
						D_Offline(NetId);
						D_OfflineLin(NetId);;
						Ecaul_LinTxSleepMsg();//����lin���߱���
						nmSetAlarm(TWbs);
						NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
					}
					else
					{
						// 此时如果是 01 02 04 ，应该继续发limphome，就屏蔽 nmInitReset5(NetId);
						nmInitReset5(NetId);
						setLocalSleepFlag(0);
						resetS_delayTimer();
					}
				}
			}
			else
			{
				if(NM_ControlBlock[NetId].nmStatus.NetworkStatus.W.bussleep)
				{
					if(1 == NMPDU->OpCode.B.SleepInd)
					{
						if(1 == NMPDU->OpCode.B.SleepAck)//
						{
							D_Offline(NetId);
							D_OfflineLin(NetId);;
							Ecaul_LinTxSleepMsg();//����lin���߱���
							nmSetAlarm(TWbs);
							NM_ControlBlock[NetId].nmState = NM_stTwbsLimphome;
						}
					}
					else
					{
						NM_ControlBlock[NetId].nmState = NM_stLimphome;
						nmSetAlarm(TError);
					}
					break;
				}
				else
				{
					NM_ControlBlock[NetId].nmState = NM_stLimphome;
					nmSetAlarm(TError);
				}
			}
		}
		case NM_stTwbsLimphome:
		{
			/* �� Twbs ��ʱǰ������ڵ㲻����˯����������յ��� NM ���� ind��0 �� NM
			����ʱ���ڵ�ȡ�� Twbs ��ʱ������ʱ Terror ��ʱ����Ȼ���˻ص�����״̬��*/
			if( (0 == NMPDU->OpCode.B.SleepInd)  && ( 0 == NMPDU->OpCode.B.SleepAck) )
			{
				D_Online(NetId);
				nmCancelAlarm(TWbs);
				nmSetAlarm(TError);
				NM_ControlBlock[NetId].nmState = NM_stLimphome;
			}
			else
			{
			}
			break;
		}
		default:
			break;
	}
}
void NM_WakeupIndication(uint8_t NetId)
{
	if(NM_stBusSleep == NM_ControlBlock[NetId].nmState)
	{	/* 3 NMInit */
		/* OK Wakeup */
		NM_D_Init(NetId,BusAwake);
		nmInit3(NetId);
	}
}

void NM_MainFuntion(void)
{
//	static NMStateType s_pre_NMstate = NM_stNormal;
//	static INT32U s_SlespDelayTimer = 0;
	NetIdType NetId = 0;

//	if( (s_pre_NMstate != NM_stLimphome) && (NM_ControlBlock[NetId].nmState == NM_stLimphome) )
//	{
//		s_SlespDelayTimer = D_HAL_GET_CUR_MS_TS();
//		s_DelayFlag = TRUE;
//	}
//
//	if(Ecual_TimerDiffTs(s_SlespDelayTimer) > NM_LIMPHONE_DELAY_SLEEP_TIME)
//	{
//		s_DelayFlag = FALSE;
//	}
	
//	s_pre_NMstate = NM_ControlBlock[NetId].nmState;
	nmSleepCheck(NetId);
	if(nmIsAlarmStarted(TTx))
	{
//		nmSingalAlarm(TTx);
		if(nmIsAlarmTimeout(TTx))
		{
			nmCancelAlarm(TTx);
			nmSendMessage();

		}
	}
	/* App Ӧ�ñ��ķ��Ͷ�ʱ����ʱ�����App���ķ��� */
	if(nmIsAlarmStarted(TTxApp))
	{
		if(nmIsAlarmTimeout(TTxApp))
		{
			nmCancelAlarm(TTxApp);
			//�˴�ENABLE/D_Online���Start�ӿڵ�NMDISABLE/D_Offline��ʹӦ�ñ��������籨�ķ��ͺ�TTxAPP���ں��ڷ���
			ECUAL_CAN_ENABLE_APP_TX_ENABLE(); 
			D_Online(NetId);
		}
	}
	switch(NM_ControlBlock[NetId].nmState)
	{
		case NM_stNormal:
			nmNormalMain(NetId);
			break;
		case NM_stLimphome:
			nmLimphomeMain(NetId);
			break;
		case NM_stNormalPrepSleep:
			nmNormalPrepSleepMain(NetId);
			break;
		case NM_stTwbsNormal:
			nmNormalTwbsMain(NetId);
			break;
		case NM_stLimphomePrepSleep:
			nmLimphomePrepSleepMain(NetId);
			break;
		case NM_stTwbsLimphome:
			nmTwbsLimphomeMain(NetId);
			break;
		default:
			break;
	}
}


static void nmSleepCheck(uint8_t NetId)
{
	
    //�������ߵ�����
    if(SleepConditionCheck() == TRUE /*&& (s_DelayFlag == FALSE)*/)
    {

        GotoMode(NetId, NM_BusSleep);
    }
    else
    {
        GotoMode(NetId, NM_Awake);
    }
}

/* ������ʱ�� ����ʱ�������� */
void nmSetAlarmStart(INT32U lat) 	
{
	do								
	{								
		NM_ControlBlock[NET_ID].Alarm._TError = D_HAL_GET_CUR_MS_TS() - lat;
	}												
	while (0);
}

void NmTask(void)
{
    static INT32U CANAppMsgTxTs=0;
    static INT32U CANNmMsgTs=0;
	static INT32U CANACKErrTs = 0;
	static INT32U CANACKErrResetTs = 0;

    volatile NmOsek_enCANSt NmAppComm = NmOsek_engCANAppComm;
	NMStateType NMSts = NM_stNormal;

    if (1)
    {
        /* NM */
        if (CPU_TimerDiffTs(CANNmMsgTs) >= D_SERVICE_DIAG_NM_PERIOD)
        {
            CANNmMsgTs = D_HAL_GET_CUR_MS_TS();
			GetStatus(0,&NMSts);
            if (NMSts != NM_stBusSleep)
            {
                Nm_CanBusOffRecoveryProcess();
            }
            NM_MainFuntion();
        }

        if (FALSE == Nm_IsCanBusOffTxStopValid())
        {
           	if(NmAppComm == NmOsek_enmEnable)
       		{
	            if (CPU_TimerDiffTs(CANAppMsgTxTs) >= D_SERVICE_CAN_MSG_PERIOD)
	            {
	                CANAppMsgTxTs = D_HAL_GET_CUR_MS_TS();

					if(TRUE == Ecual_GetCanACKErrSts())
					{
						if((FALSE == Ecual_GetCANACKErrTxEnable()) \
							&& (CPU_TimerDiffTs(CANACKErrResetTs) >= D_CAN_ACK_ERR_RESET))
						{
							Ecual_SetCANACKErrTxEnable(TRUE);
//							Ecual_CanTransmitAllMsgTick(); //ȷ��150ms���б��ķ���
							CANACKErrTs = D_HAL_GET_CUR_MS_TS();
						}

						if((TRUE == Ecual_GetCANACKErrTxEnable()) \
							&& (CPU_TimerDiffTs(CANACKErrTs) >= D_CAN_ACK_ERR_RESET))
						{
//							Ecual_ResetCan();
							Ecual_SetCANACKErrTxEnable(FALSE);
							CANACKErrResetTs = D_HAL_GET_CUR_MS_TS();
						}

					}
					else
					{
						CANACKErrTs = D_HAL_GET_CUR_MS_TS();
						CANACKErrResetTs = D_HAL_GET_CUR_MS_TS();
					}


//	                Ecual_CanTask();
	            }
       		}

        }
    }
}

