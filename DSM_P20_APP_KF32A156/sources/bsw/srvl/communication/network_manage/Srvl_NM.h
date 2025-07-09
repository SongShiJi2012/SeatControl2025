#ifndef __SRVL_NM_H__
#define __SRVL_NM_H__


//#include "Ecual_Public.h"
#include "OsekNm.h"
//#include "Srvl_SubComm.h"

#ifdef     NM_GLOBALS
#define     NM_EXT    
#else    
#define   NM_EXT      extern
#endif

#define TX_TIMEOUT          (150/FNOS_TASK_CYCLE_TIME)    //150ms
#define TX_RECOVERY         (150/FNOS_TASK_CYCLE_TIME)

#define NM_BUS_OFF_FAST_RECOVERY_TIME        (100/5U)
#define NM_BUS_OFF_SLOW_RECOVERY_TIME        (1000/5U)

#define NM_FAST_RECOVERY_CONSECUTIVE_EXE_MAXTIMES    (5)
#define NM_COUNT_SHORT_NUMBER                        (5)
#define NM_COUNT_BUSOFF_DTC_NUMBER                   (3)
#define NM_COUNT_BUSOFF_LIMIT                        (50)

typedef enum
{
    BusOffFastRecoveryMode,
    BusOffSlowRecoveryMode,
}enBusOffMode;

typedef struct NM_BUSOFF_PARA
{
	volatile BOOL bCANBusOffFlag; /*bus off��ʶ*/
	BOOL bCanBusOffRecoveryInd; /*bus off����Ҫ��ʼ��can�ı�ʶ*/
	BOOL bCanTxStopFlg; /*bus off��ֹͣ����can����,���������Ŀ�ָ�,���ָ�ʱ���ſ��Է���*/

	enBusOffMode enBusOffRecoveryMode; /*can�����ָ�ͨ������*/
	INT8U u8BusOffRecoveryCounter; /*��ָ�,���ָ���ʱʱ��*/
	INT8U u8BusOffCounter; /*bus off�ƴ���ֵ*/
	
}StrNmBusoffPara;


NM_EXT void Nm_CanBusOffRecoveryProcess(void);

extern StrNmBusoffPara NmBusoffPara;
void Nm_BusoffParaInit(void);
void Nm_SysVoltAbnormalRecv(void);

void Nm_ErrorHandle(uint32_t eCode, uint8_t RxErrCnt, uint8_t TxErrCnt);

BOOL Nm_IsBusOff(void);

INT8U Nm_CanGetBusOffTrgCnt(void);

void Nm_CanTransferSuccess(void);

void Nm_MsgTransfer(void);

BOOL Nm_IsCanBusOffTxStopValid(void);


void Nm_InitStart(void);

void Nm_MsgReciver(void);

#endif /* _H_NM_ */

