#ifndef CAN_DRV_MSCAN_H
#define CAN_DRV_MSCAN_H

#include  "Common.h"
#include "ecual_can.h"
#include "pins_driver.h"

#define INST_CAN0  INST_CAN_0

/*20220924 NXP里面CAN发送使能引脚，无实际意义*/
//macro definition------------------------------------------------------------
#define CANMAINENGPIO		(GPIOC_SFR)
#define CANMAINENPIN		(4u)
#define CANTxEnable() 		PINS_DRV_WritePin(CANMAINENGPIO, CANMAINENPIN, D_HIGH)
#define CANTxDisable() 		PINS_DRV_WritePin(CANMAINENGPIO, CANMAINENPIN, D_LOW)

//constant macro definition-----------------------------------------------
#define MAX_CAN_MSG_RX_BUF_SIZE         			(160u)
#define MAX_CAN_MSG_TX_BUF_SIZE         			(40u)
#define CAN_SET_RXMBID_ERRCNT         				(3ul)

typedef enum
{
	enHSCAN,
	enMSCAN,
} CANDrvMSCAN_enBaudRate;

typedef enum
{
	enCANsleepReq,
	enCANcloseReq,
} CANDrvMSCAN_enCANmodeReq;

typedef struct CANMsgRxBase
{
	INT32U    cCANID;
	INT8U   cDataLength;
	INT8U   cData[8];
} CANMsgRxBase;

typedef struct CANMsgTxBase
{
	flexcan_msgbuff_id_type_t IdType;
	INT32U   cCANIDIndex;
	INT8U  cDataLength;
	INT8U  cData[8];
} CANMsgTxBase;

typedef struct CANMsgRxType
{
	INT8U   cWritePointer;
	INT8U   cReadPointer;
	INT8U   cMsgNum;
	CANMsgRxBase    CANMsgBuf[MAX_CAN_MSG_RX_BUF_SIZE];
} CANMsgRxType;

typedef struct CANMsgTxType
{
	INT8U cWritePointer;
	INT8U cReadPointer;
	INT8U cMsgNum;
	CANMsgTxBase CANMsgBuf[MAX_CAN_MSG_TX_BUF_SIZE];
} CANMsgTxType;


//variables definition-------------------------------------------------------------
extern BOOL g_bCANWakeUpFlg;
extern CANMsgRxType CANMsgRxDrv;
extern CANMsgTxType CANMsgTxDrv;
extern INT8U CanRxMbIdErrIndex;
extern INT8U CANWakeupFlg;

//Function declaration-----------------------------------------------------------
//void CANDrvMSCAN_vogErrIntRoutine(void) ;

INT32U CANGetConfigDrvMbRxID(flexcan_msgbuff_id_type_t MbIDType, INT32U msgId);
void CANDrvMSCAN_u1gMSCANInit(void);
void CANDrvMSCAN_vogFillTxEmptyBuffers(INT8U InIntFlag);
INT8U CANDrvMSCAN_u1gBusSleepReq(void);
void CANDrvMSCAN_vogBusOffRecoveryReq(void);
void CANDrvMSCAN_vogWakeUPIntRoutine(void);
extern void CANDrvMSCAN_CheckARBSTART(void);
extern void CANDrvMSCAN_ClearTxBuffer(void);
extern BOOL CANDrv_GetCanTxStopFlag(void);
extern void CANDrv_SetCanTxStopFlag(BOOL bFlagValue);

#endif

/* end of file */
