/*****************************************************************************
               Copyright (C) 2016, Michip Technologies Co., Ltd
                             All Rights Reserved
******************************************************************************
??????: Osek.c
???????: OSEK Network Management
???????: wangyongxiang
????????: 2019-08-04
???¡ã·Ú: 0.0.1
??????: 
*****************************************************************************/
#ifndef COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_
#define COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <string.h>
#include <stdint.h>
//#include "Platform_Types.h"
typedef uint8_t StatusType;
typedef uint32_t TickType;
typedef unsigned char boolean;

#ifndef E_OK
    #define E_OK (0x00)
#endif

#ifndef E_NOT_OK
    #define E_NOT_OK (0x01)
#endif

//#ifndef	TRUE
//#define TRUE           	    (0x01)
//#endif
//
//#ifndef FALSE
//#define FALSE         	    (0x00)
//#endif

/* ============================ [ MACROS    ] ====================================================== */
/* Mask bit for ScalingParamType */
/* If 1 the function is supported, 0 not */
#define NM_BusSleepSupport             0x01
#define NM_StatusDeltaSupport          0x02
#define NM_NormalConfigDeltaSupport    0x04
#define NM_LimphomeConfigDeltaSupport  0x08
#define NM_RingdataSupport             0x10

// Macros for OpCode
#define NM_MaskAlive   	 (1<<0)
#define NM_MaskRing   	 (1<<1)
#define NM_MaskLimphome  (1<<2)
#define NM_MaskSI        (1<<4)   /* sleep ind */
#define NM_MaskSA        (1<<5)   /* sleep ack */
/* ============================ [ TYPES     ] ====================================================== */
/* @ nm253.pdf 4.3 P89 */
typedef uint8_t NetIdType;
typedef uint8_t NodeIdType;
typedef void (*RoutineRefType)(NetIdType NetId);
/* import EventMaskType from OS */
typedef enum{
	SignalInvalid = 0,
	SignalActivation,
	SignalEvent
}SignallingMode;
/* import StatusType / TaskRefType / TickType from OS */
/* -- Private Types */
typedef enum
{
	NM_DIRECT = 0,
	NM_INDIRECT
}NMType;

typedef uint8_t ScalingParamType; /* 8 bit is enough TODO: not used */

/* @ nm253.pdf 4.4.2 P92 */
typedef uint8_t* ConfigRefType;
typedef enum
{
	NM_ckNormal = 1,              /* supported by direct and indirect NM */
	NM_ckNormalExtended,          /* only supported by indirect NM */
	NM_ckLimphome                 /* only supported by direct NM */
}ConfigKindName;
typedef ConfigRefType ConfigHandleType;
typedef union
{
	uint32_t w;
	struct{
		unsigned NMactive:1;
		unsigned bussleep:1;
		unsigned configurationstable:1;
	}W;
}NetworkStatusType;

typedef NetworkStatusType* StatusRefType;
/* @ nm253.pdf 4.4.3.1 P98 */
typedef enum
{
	NM_BusSleep = 1,
	NM_Awake
}NMModeName;
typedef enum
{
	NM_stOff = 0,
	NM_stInit,
	NM_stInitReset,
	NM_stNormal,
	NM_stNormalPrepSleep,
	NM_stTwbsNormal,
	NM_stBusSleep,
	NM_stLimphome,
	NM_stLimphomePrepSleep,
	NM_stTwbsLimphome,
	NM_stOn /* in fact if not Off then ON. */
	// ...  and so on
}NMStateType;
typedef StatusRefType StatusHandleType;

/* @ nm253.pdf 4.4.5.3.1 P103 */
typedef uint8_t RingDataType[6];
typedef RingDataType* RingDataRefType;

typedef struct
{
	uint8_t Source;
	uint8_t Destination;
	union
	{
		uint8_t b;
		struct {
			uint8_t Alive     :1;
			uint8_t Ring      :1;
			uint8_t Limphome  :1;
			uint8_t reserved1 :1;
			uint8_t SleepInd  :1;
			uint8_t SleepAck  :1;
			uint8_t reserved2 :2;
		}B;
	}OpCode;
	RingDataType RingData ;
}NMPduType;

#include "OsekNm_Cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
extern volatile INT8U nmSendMess[8];
/* ============================ [ FUNCTIONS ] ====================================================== */
/* @ nm253.pdf 4.4.1.1 P89 System Generation Support */
void InitNMType(NetIdType NetId,NMType nmType);
void InitNMScaling(NetIdType NetId,ScalingParamType ScalingParams);
void SelectHWRoutines(NetIdType NetId,RoutineRefType BusInit,RoutineRefType BusAwake,	\
				RoutineRefType BusSleep,RoutineRefType BusRestart,RoutineRefType BusShutdown);
void InitCMaskTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType CMask);
void InitTargetConfigTable(NetIdType NetId,ConfigKindName ConfigKind,ConfigRefType TargetConfig);
void InitSMaskTable(NetIdType NetId,StatusRefType SMask);
void InitTargetStatusTable(NetIdType NetId,StatusRefType TargetStatus);
/* @ nm253.pdf 4.4.2.3 P95 Services */
StatusType InitConfig(NetIdType NetId);
StatusType GetConfig(NetIdType NetId,ConfigRefType Config,ConfigKindName ConfigKind);
StatusType CmpConfig(NetIdType NetId,ConfigRefType TestConfig,ConfigRefType RefConfig,ConfigRefType CMask);
StatusType SelectDeltaConfig(NetIdType NetId,ConfigKindName ConfigKind,ConfigHandleType ConfigHandle,ConfigHandleType CMaskHandle);

StatusType StartNM(NetIdType NetId);
StatusType StopNM(NetIdType NetId);
StatusType GotoMode(NetIdType NetId,NMModeName NewMode);
//StatusType GetStatus(NetIdType NetId,StatusRefType NetworkStatus);
StatusType GetStatus(NetIdType NetId,NMStateType *nmState);
StatusType CmpStatus(NetIdType NetId,StatusRefType TestStatus,StatusRefType RefStatus,StatusRefType SMask);
StatusType SelectDeltaStatus(NetIdType NetId,StatusHandleType StatusHandle,StatusHandleType SMaskHandle);

/* FOR DIRECT NM */
void InitDirectNMParams(NetIdType NetId,NodeIdType NodeId,TickType TimerTyp,TickType TimerMax, 	\
								TickType TimerError,TickType TimerWaitBusSleep,TickType TimerTx,TickType TimerTxApp);
StatusType SilentNM(NetIdType);
StatusType TalkNM(NetIdType);

void ReadRingData(NetIdType NetId,RingDataRefType RingData);
void TransmitRingData(NetIdType NetId,RingDataRefType RingData);

/* FOR INDIRECT NM */
void InitIndirectNMParams(NetIdType NetId,NodeIdType NodeId,TickType TOB,TickType TimerError,TickType TimerWaitBusSleep);
void InitExtNodeMonitiring(NetIdType NetId,NodeIdType NodeId,uint8_t DeltaInc,uint8_t DeltaDec);


void NM_TxConformation(NetIdType NetId);
void NM_RxIndication(NetIdType NetId,NMPduType* NMPDU);
void NM_WakeupIndication(NetIdType NetId);
void NM_BusErrorIndication(NetIdType NetId);

void NM_MainFuntion(void);

void NM_D_Init(NetIdType NetId,RoutineRefType InitRoutine);
void D_Offline(NetIdType NetId);
void D_Online(NetIdType NetId);
void D_OfflineLin(NetIdType NetId);
void D_OnlineLin(NetIdType NetId);
StatusType D_Transmit(NetIdType NetId,NMPduType* NMPDU,uint8_t DataLengthTx);


/* Function needed by DLL */
void BusInit(NetIdType NetId);
void BusSleep(NetIdType NetId);
void BusAwake(NetIdType NetId);
void BusRestart(NetIdType NetId);

void nmSetAlarmStart(INT32U lat);

BOOL NM_GetLinMsgTxInd(void);
void NmTask(void);
#endif /* COM_AS_INFRASTRUCTURE_INCLUDE_OSEKNM_H_ */
