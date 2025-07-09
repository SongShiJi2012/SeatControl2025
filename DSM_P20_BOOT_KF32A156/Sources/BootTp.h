#ifndef       _BOOTTP_H
#define       _BOOTTP_H
#include  "Common.h"

#define DIAG_DEFAULT_VALUE		(0x00)


#define BOOT_TP_TASK_CALL_CYCLE_TIME                    5

#define BOOT_N_OK                              			0
#define BOOT_N_TIMEOUT_A                       			1
#define BOOT_N_TIMEOUT_Bs                      			2
#define BOOT_N_TIMEOUT_Cr                      			3
#define BOOT_N_WRONG_SN                        			4
#define BOOT_N_INVALID_FS                      			5
#define BOOT_N_UNEXP_PDU                       		    6
#define BOOT_N_WFT_OVRN                        			7
#define BOOT_N_BUFFER_OVFLW                    			8
#define BOOT_N_INVALID_MSG_DATA_LENGTH         		    9
#define BOOT_N_INVALID_MSG_TYPE                			10
#define BOOT_N_INVALID_SF_DATA_LENGTH          		    11
#define BOOT_N_INVALID_FF_DATA_LENGTH          		    12
#define BOOT_N_DEFFERENT_CAN_ID_RQ             		    13
#define BOOT_N_ERROR                           			14


#define D_TP_TX_MAX_LEN									8

#define BOOT_TP_MSG_SF                         			0
#define BOOT_TP_MSG_FF                         			1
#define BOOT_TP_MSG_CF                         			2
#define BOOT_TP_MSG_FC                         			3

#define BOOT_FC_CONTINUE_TO_SEND               			0 //0 继续发送	1 等待	2 溢出
#define BOOT_FC_WAIT                           			1
#define BOOT_FC_STATUS_OVER_FLOW              	 		2

#define BOOT_FC_BLOCK_SIZE                             0
#define BOOT_FC_STMIN                                  0x00 //S15+A16 PEPS
#define BOOT_TP_MSG_TYPE_MASK                  		   0xf0

#define BOOT_TP_MSG_PARAMETER_MASK             		   0x0f


#define BOOT_SF_MAX_DATA_LENGTH                			7
#define BOOT_FF_MIN_DATA_LENGTH                			7
#define BOOT_FF_DATA_LENGTH                    			6
#define BOOT_CF_MAX_DATA_LENGTH                			7


#define BOOT_SF_MAX_DATA_LENGTH_WITH_STD_ADDR           7
#define BOOT_TP_MAX_TX_SIZE                    			0x0fff

#define BOOT_TP_TX_DATA_BUF_SIZE               			(64) // 
#define BOOT_TP_RX_DATA_BUF_SIZE               			(2 + 1024) // 36服务中, 36 + 01 + 数据,  最大传输的数据512Byte

#define BOOT_kTpOn                             			1
#define BOOT_kTpOff                            			0

#define BOOT_TP_USE_ONLY_FIRST_FC              			BOOT_kTpOn
#define BOOT_TP_USE_STMIN_OF_FC                			BOOT_kTpOn
#define BOOT_TP_USE_EXTENDED_API_BS            		    BOOT_kTpOff
#define BOOT_TP_USE_EXTENDED_API_STMIN         		    BOOT_kTpOff


#define BOOT_TP_TX_TIME_N_As                   			14  /*modify for S15+A16*/  /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 10 * 5 = 50ms */
#define BOOT_TP_TX_WAIT_SF_CONFIRM_TIME        		    BOOT_TP_TX_TIME_N_As
#define BOOT_TP_TX_WAIT_FF_CONFIRM_TIME        		    BOOT_TP_TX_TIME_N_As
#define BOOT_TP_TX_WAIT_CF_CONFIRM_TIME        		    BOOT_TP_TX_TIME_N_As
#define BOOT_TP_TX_TIME_N_Bs                  			30 /*modify for S15+A16*/  /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 30 * 5 = 150ms */ 
#define BOOT_TP_TX_WAIT_FC_TIME                			BOOT_TP_TX_TIME_N_Bs
#define BOOT_TP_TX_TIME_N_Cs                   			0 /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 0 * 5 = 0ms */   
#define BOOT_TP_TX_WAIT_SEND_CF_TIME           		    BOOT_TP_TX_TIME_N_Cs


#define BOOT_TP_RX_TIME_N_Br                   			0 /* Unit: Value * CAN_DRV_TASK_CALL_CYCLE_TIME, ms . Here 0 * 5 = 0ms */
#define BOOT_TP_RX_WAIT_TO_SEND_FC_TIME        	        BOOT_TP_RX_TIME_N_Br
#define BOOT_TP_RX_TIME_N_Ar                   			14 /*modify for S15+A16*/   /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 10 * 5 = 50ms */
#define BOOT_TP_RX_WAIT_FC_CONFIRM_TIME        		    BOOT_TP_RX_TIME_N_Ar
#define BOOT_TP_RX_WAIT_N_Cr                   			30	 /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 30 * 5 = 150ms */
#define BOOT_TP_RX_WAIT_CF_TIME                			BOOT_TP_RX_WAIT_N_Cr


typedef enum {
  BOOT_kRxState_Idle = 0,
  BOOT_kRxState_ApplInformed,
  BOOT_kRxState_CanFrameReceived,
  BOOT_kRxState_WaitCF,
  BOOT_kRxState_WaitFC,
  BOOT_kRxState_WaitForFCConfIsr,
  BOOT_kRxState_Error
}eTpRxStateEngine;

typedef enum {
  BOOT_kTxState_Idle = 0,
  BOOT_kTxState_SendRespFrame,
  BOOT_kTxState_WaitFC,
  BOOT_kTxState_WaitForTpTxCF,
  BOOT_kTxState_WaitForMinTimer,
  BOOT_kTxState_WaitForSFConfIsr, 				
  BOOT_kTxState_WaitForFFConfIsr, 
  BOOT_kTxState_WaitForCFConfIsr,
  BOOT_kTxState_WaitForLastCFConfIsr,
  BOOT_kTxState_Error
} eTpTxStateEngine;

typedef struct 
{
	BOOT_U8 		Timer;
	BOOT_U8 		cBSCounter;
	eTpTxStateEngine 		engine;
} stTpTxState;


typedef struct 
{
	BOOT_U8			Timer;
	BOOT_U8 		cBSCounter;
	eTpRxStateEngine 		engine;
} stTpRxState;

typedef struct 
{
	BOOT_U8 		cCANIDIndex;
	BOOT_U8 		cDataBuf[BOOT_TP_RX_DATA_BUF_SIZE];
	BOOT_U16 		wDataIndex;
	BOOT_U16 		wDataLength;
	BOOT_U8 		cBlockSize;
	BOOT_U8 		cSTMin;
	BOOT_U8 		cFCStatus;
	BOOT_U8 		cSequenceNumber;
} stTpRxInfoStruct;

typedef struct 
{
	BOOT_U8 		cCANIDIndex;
	BOOT_U8  		cDataBuf[BOOT_TP_TX_DATA_BUF_SIZE];
	BOOT_U16 		wDataWriteIndex;
	BOOT_U16 		wDataReadIndex;
	BOOT_U16 		wDataLength;
	BOOT_U8 		cBlockSize;
	BOOT_U8 		cSTMin;
	BOOT_U8 		cSequenceNumber;    
} stTpTxInfoStruct;

extern BOOT_U8				BootMsgNeedTxIndFlag;
extern BOOT_U8				BootTpTxBuf[8];
extern BOOT_U8				BootTpRxErrorType;
extern stTpTxState 				BootTpTxState;
extern stTpRxState 				BootTpRxState;
extern stTpTxInfoStruct 			BootTpTxInfoStruct;
extern stTpRxInfoStruct 			BootTpRxInfoStruct;
extern volatile BOOT_U8 Boot_FirstFCflg;
extern volatile BOOT_U8 Boot_FirstcSTMin; 
extern volatile BOOT_U8 Boot_TP_u1gPhisicalRspTxFnshFlg;


void         BootTPInit(void);
void         BootTPRxProcess(BOOT_U8 cMsgIndex, BOOT_U8 cCANIDInd);
void         BootTPRxTask(void);
void         BootTpTxConsecutiveFrame(void);
void         BootTPTxProcess(void);
void         BootTpTxStart(void);
void         BootTPTxTask(void);

#endif

