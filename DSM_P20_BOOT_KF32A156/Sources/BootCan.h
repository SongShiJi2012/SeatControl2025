#ifndef   _BOOTCAN_H
#define    _BOOTCAN_H
#include  "Common.h"
#include "flexcan_driver.h"

#define			BOOTMSCAN_INPUT					0
#define			BOOTMSCAN_OUTPUT				1 
#define CANMAINENGPIO		(PTE)
#define CANMAINENPIN		(1ul<<13u)
//#define BOOTCANEnable() 	PINS_DRV_ClearPins(CANMAINENGPIO,CANMAINENPIN)
//#define BOOTCANDisable() 	PINS_DRV_SetPins(CANMAINENGPIO,CANMAINENPIN)
#define BOOTCANEnable() 	
#define BOOTCANDisable() 	

#define INST_CAN0  INST_CAN_0

#define 	    BOOT_MAX_CAN_MSG_RX_BUF_SIZE        (15)   // 30
#define 	    BOOT_MAX_CAN_MSG_TX_BUF_SIZE        (10)     // 10

#define	BOOT_CAN_CANID_EXT					(0x80000000)
#define	BOOT_CAN_CANID_STD_MSK				(0x000007ff)
#define	BOOT_CAN_CANID_EXT_MSK				(0x1fffffff)

#if 0
/*CAN物理层接收数据结构体*/
typedef struct CANMAINMAILRXBUFFCFG
{
	INT8U NewFrameFlag; /*接收到新的数据标识*/
	INT8U MailBoxIndex; /*邮箱索引号*/
	flexcan_msgbuff_id_type_t eMsgIDType;/*CAN ID类型*/
	INT32U CanRxId; /*此邮箱对应的接收CAN ID*/
	INT32U IndividualMask; /*邮箱对应的接收掩码*/
	flexcan_msgbuff_t RxBuff; /*接收数据缓存*/
}strCanMainMailboxRxbuffCfg;

/*CAN物理层发送数据结构体*/
typedef struct CANMAINMAILTXBUFFCFG
{
	INT8U BusyFlag; /*邮箱正在发送中标识,0-空闲 1-忙*/
	INT8U MailBoxIndex; /*邮箱索引号*/
	INT32U CanTxId; /*此邮箱对应的发送CAN ID*/
	INT8U TxBuff[8]; /*发送数据缓存*/
}strCanMainMailboxTxbuffCfg;
#endif

typedef struct
{
	INT32U  		cCANID;
	INT8U     	cDataLength;
	INT8U  		cData[8];
} stCANMsgRxBase;

typedef struct
{
	flexcan_msgbuff_id_type_t IdType;
	INT32U		cCANIDIndex;
	INT8U  		cDataLength;
	INT8U  		cData[8];
} stCANMsgTxBase;

typedef struct
{
	INT8U 		cWritePointer;
	INT8U 		cReadPointer;
	INT8U 		cMsgNum;
  stCANMsgRxBase 	CANMsgBuf[BOOT_MAX_CAN_MSG_RX_BUF_SIZE];
} stCANMsgRxType;

typedef struct
{
	INT8U 		cWritePointer;
	INT8U 		cReadPointer;
	INT8U 		cMsgNum;
  stCANMsgTxBase 		CANMsgBuf[BOOT_MAX_CAN_MSG_TX_BUF_SIZE];
} stCANMsgTxType;


extern stCANMsgRxType 			BootCANMsgRxDrv;
extern stCANMsgTxType 			BootCANMsgTxDrv;
extern BOOL        	BootCANInitOKFlag;


void     BootCANTRX(INT8U InIntFlag);
void     BootCANREC(INT32U CANID,INT8U *pBuff,INT8U len);
void     BootCANERR(void);
void     BootCANaFCANinit(void);
void     BootCANInit(void);
void     BootCANTask(void);
void 	 BootCAN_CheckARBSTART(void);
void CANTX_TEXT(void);

#endif

