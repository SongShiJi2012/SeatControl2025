#ifndef _H_APPDESC_
#define _H_APPDESC_

#include "DescConfig.h"
#include "DescRWDIDList.h"

#ifdef		AppDesc_GLOBALS
#define		AppDesc_EXT
#else
#define		AppDesc_EXT        extern
#endif

#define D_UDS_ACCESS_MAX_TIMES          2U

/**********************RID Relational Definition *******************************/
#define DESC_MAX_ROUTINE_CONTROL_F020_TIME                  		(5000 / CANDRVCYCTIME)
#define DESC_MAX_Security_60s_TIME                  			(60000 / CANDRVCYCTIME)
#define FIELD_STRENGTH_VALUE_ARRAY_SIZE			2

#define	PINATTACK_TASK_CYCLE_TIME							5
#define	APPDESC_60S											(60 *1000UL/PINATTACK_TASK_CYCLE_TIME)
#define	APPDESC_600S										(600 *1000UL/PINATTACK_TASK_CYCLE_TIME)
#define APPDESC_210MS                                       (210UL/PINATTACK_TASK_CYCLE_TIME)
#define D_DESCNRCEPROMRSP_4000MS          ((DESC_P2EX_CAN_SERVER_MAX * CANDRVCYCTIME)-1000)

#define D_EEPROMNOTBUSYTIMER				(30UL * D_SYS_MS_TIME_BASE)

extern enSrvMemIndex Appdesc_engCurrEEPOpDataID;
extern volatile INT8U Appdesc_u1gClrDTCNeedRspFlg;
typedef struct
{
    INT16U        sDID;
    INT16U         ReadDIDLength;//»Ø¸´³¤¶È
    INT16U         WriteIDLength;
}tLIN_DID_INFO;



/***************************Function Prototype Declartion *******************************/
AppDesc_EXT void AppDescInit(void);
AppDesc_EXT void AppLinDescTask(void);
AppDesc_EXT void AppDescTask(void);
AppDesc_EXT void AppDescSessionChanged(unsigned char cPreSession, unsigned char cNewSession);
AppDesc_EXT void AppDescPinAttackProcess(void);
AppDesc_EXT BOOL Uds_AccessTimesLmt(void);
AppDesc_EXT void Uds_AccessTimeRst(void);
AppDesc_EXT void Uds_AccessTimesClean(void);

AppDesc_EXT volatile INT8U Appdesc_u1gClrDTCNeedRspFlg;
#endif /* _H_APPDESC_ */

