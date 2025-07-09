#ifndef TP_H
#define TP_H
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include  "Common.h"

#define TP_TASK_CALL_CYCLE_TIME           CANDRVCYCTIME   /* unit : ms */


/* define TP task return value 

N_OK:
  This value means that the service execution has completed successfully. 
  This value can be issued to a service user on both the sender and receiver side
N_TIMEOUT_A:
  This value is issued to the protocol user when the timer N_Ar/N_As has passed 
  its time-out value N_Asmax/N_Armax. 
  This value can be issued to service user on both the sender and receiver side.
N_TIMEOUT_Bs:
  This value is issued to the service user when the timer N_Bs has passed its 
  time-out value N_Bsmax. 
  This value can be issued to the service user on the sender side only.
N_TIMEOUT_Cr:
  This value is issued to the service user when the timer N_Cr has passed 
  its time-out value N_Crmax. 
  This value can be issued to the service user on the receiver side only.
N_WRONG_SN:
  This value is issued to the service user upon reception of an unexpected 
  sequence number (PCI.SN) value. 
  This value can be issued to the service user on the receiver side only.
N_INVALID_FS:
  This value is issued to the service user when an invalid or unknown FlowStatus
  value has been received in a flow control (FC) N_PDU. 
  This value can be issued to the service user on the sender side only.
N_UNEXP_PDU:
  This value is issued to the service user upon reception of an unexpected 
  protocol data unit. 
  This value can be issued to the service user on the receiver side only.
N_WFT_OVRN:
  This value is issued to the service user upon reception of flow control WAIT 
  frame that exceeds the maximum counter N_WFTmax.
N_BUFFER_OVFLW:
  This value is issued to the service user upon reception of a flow control (FC) 
  N_PDU with FlowStatus = OVFLW. 
  It indicates that the buffer on the receiver side of a segmented message transmission 
  cannot store the number of bytes specified by the FirstFrame DataLength (FF_DL) 
  parameter in the FirstFrame and therefore the transmission of the segmented message 
  was aborted. This value can be issued to the service user on the sender side only.
N_ERROR:
  This is the general error value. 
  This value shall be issued to the service user when a error has been detected 
  by the network layer and no other parameter value can be used to better describe 
  the error. This value can be issued to the service user on both the sender and 
  receiver side.

*/

#define N_OK                              0
#define N_TIMEOUT_A                       1
#define N_TIMEOUT_Bs                      2
#define N_TIMEOUT_Cr                      3
#define N_WRONG_SN                        4
#define N_INVALID_FS                      5
#define N_UNEXP_PDU                       6
#define N_WFT_OVRN                        7
#define N_BUFFER_OVFLW                    8
#define N_INVALID_MSG_DATA_LENGTH         9
#define N_INVALID_MSG_TYPE                10
#define N_INVALID_SF_DATA_LENGTH          11
#define N_INVALID_FF_DATA_LENGTH          12
#define N_DEFFERENT_CAN_ID_RQ             13
#define N_ERROR                           14


#define D_TP_TX_MAX_LEN						8
#define D_UDS_TP_FRAME_LEN                  D_TP_TX_MAX_LEN


/* define TP message type */
#define TP_MSG_SF                         0
#define TP_MSG_FF                         1
#define TP_MSG_CF                         2
#define TP_MSG_FC                         3

/* define TP Flow Control Status */

#define FC_CONTINUE_TO_SEND               0	//0 继续发送	1 等待	2 溢出
#define FC_WAIT                           		    1
#define FC_STATUS_OVER_FLOW               2

#define FC_BLOCK_SIZE                     8
#define FC_STMIN                          20               //S15+A16 PEPS

/* define TP message type mask */
#define TP_MSG_TYPE_MASK                  0xf0

/* define TP message parameter mask */
#define TP_MSG_PARAMETER_MASK             0x0f

//#define TP_EXTENDED_ADDRESS_USED

#ifdef TP_EXTENDED_ADDRESS_USED
#define SF_MAX_DATA_LENGTH                6
#define FF_MIN_DATA_LENGTH                6
#define FF_DATA_LENGTH				   5
#define CF_MAX_DATA_LENGTH                6
#else
#define SF_MAX_DATA_LENGTH                7
#define FF_MIN_DATA_LENGTH                7
#define FF_DATA_LENGTH                    	   6
#define CF_MAX_DATA_LENGTH                7
#endif

#define SF_MAX_DATA_LENGTH_WITH_STD_ADDR  7
#define TP_MAX_TX_SIZE                    0x0fff

#define TP_TX_DATA_BUF_SIZE               512 /*modify for GWM*/ /* Do not less than this value */
#define TP_RX_DATA_BUF_SIZE               257

#define kTpOn                             1
#define kTpOff                            0

#define TP_USE_ONLY_FIRST_FC              kTpOn
#define TP_USE_STMIN_OF_FC                kTpOn
#define TP_USE_EXTENDED_API_BS            kTpOff
#define TP_USE_EXTENDED_API_STMIN         kTpOff

/* Tp Tx Time out Definition */
#define TP_TX_TIME_N_As                   14  /*modify for S15+A16*/  /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 10 * 5 = 50ms */
#define TP_TX_WAIT_SF_CONFIRM_TIME        TP_TX_TIME_N_As
#define TP_TX_WAIT_FF_CONFIRM_TIME        TP_TX_TIME_N_As
#define TP_TX_WAIT_CF_CONFIRM_TIME        TP_TX_TIME_N_As
#define TP_TX_TIME_N_Bs                   30   /*modify for S15+A16*/  /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 30 * 5 = 150ms */
#define TP_TX_WAIT_FC_TIME                        TP_TX_TIME_N_Bs
#define TP_TX_TIME_N_Cs                   0    /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 0 * 5 = 0ms */
#define TP_TX_WAIT_SEND_CF_TIME           TP_TX_TIME_N_Cs

/* Tp Rx Time out Definition */
#define TP_RX_TIME_N_Br                   0 	 /* Unit: Value * CAN_DRV_TASK_CALL_CYCLE_TIME, ms . Here 0 * 5 = 0ms */
#define TP_RX_WAIT_TO_SEND_FC_TIME        TP_RX_TIME_N_Br
#define TP_RX_TIME_N_Ar                   14  /*modify for S15+A16*/   /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 10 * 5 = 50ms */
#define TP_RX_WAIT_FC_CONFIRM_TIME        TP_RX_TIME_N_Ar
#define TP_RX_WAIT_N_Cr                   30	 /* Unit: Value * TP_TASK_CALL_CYCLE_TIME, ms . Here 30 * 5 = 150ms */
#define TP_RX_WAIT_CF_TIME                TP_RX_WAIT_N_Cr

/*******************************************************************************
* Transport protocol states
*******************************************************************************/

typedef enum
{
	kRxState_Idle = 0,
	kRxState_ApplInformed,
	kRxState_CanFrameReceived,
	kRxState_WaitCF,//等待连续帧状态
	kRxState_WaitFC,//等待流控帧的发送
	kRxState_WaitForFCConfIsr,
#if defined (TP_ENABLE_ISO_15765_2_2)
  kRxState_WaitForFCOverConfIsr,
#endif
  kRxState_Error
} tTpRxStateEngine;

typedef enum
{
	kTxState_Idle = 0,
	kTxState_SendRespFrame,
	kTxState_WaitFC,//等待接收流控帧
	kTxState_WaitForTpTxCF,////处于等待连续帧发送状态
	kTxState_WaitForMinTimer,
	kTxState_WaitForSFConfIsr,        /* Single Frame           */
	kTxState_WaitForFFConfIsr,        /* First Frame            */
	kTxState_WaitForCFConfIsr,        /* Consecutive Frame      */
	kTxState_WaitForLastCFConfIsr,    /* Last Consecutive Frame */
	kTxState_Error
} tTpTxStateEngine;

typedef INT8U tTpEngineTimer ;
typedef struct TpStateTag
{
  tTpEngineTimer Timer;
  INT8U cBSCounter;
  tTpTxStateEngine engine;
} tTpTxState;


/*******************************************************************************
* Global transport layer data for receive channels
*******************************************************************************/
/*lint -save -e46*/
typedef struct 
{
  tTpEngineTimer Timer;
  INT8U cBSCounter;
  tTpRxStateEngine engine;
} tTpRxState;

typedef struct 
{
  INT8U cCANIDIndex;

  volatile INT8U cDataBuf[TP_RX_DATA_BUF_SIZE];
  /* Description : List of pointer to receive buffers from the application      */

  INT16U wDataIndex;
  /* Description : Index to Received data - used instead of DataSegments        */
  /* Val. range / Coding: 0..4095                                               */

  INT16U wDataLength;
  /* Description : Length of data to be transmitted. The size of this variable  */
  /*               limits the maximum size of messages.                         */
  /* Val. range / Coding: 0..4095                                               */

  #if defined (TP_ENABLE_EXTENDED_ADDRESSING)
    # if (TP_USE_MULTIPLE_BASEADDRESS == kTpOn)
      INT16U wBaseAddress;
    /* Description :                                                              */
    /* Val. range / Coding: 0..0x7ff                                              */
    # endif
  #endif

  #if defined (TP_ENABLE_EXTENDED_ADDRESSING)       || \
      defined (TP_ENABLE_NORMAL_FIXED_ADDRESSING)   || \
      defined (TP_ENABLE_MIXED_29_ADDRESSING)
    # if (TP_USE_GATEWAY_API == kTpOn) 
      INT8U cTargetAddress;
      /* Description :                                                              */
      /* Val. range / Coding: 0..0xff                                               */
    # endif
    INT8U cSourceAddress;
    /* Description :                                                              */
    /* Val. range / Coding: 0..0xff                                               */
  #endif

  #if defined (TP_ENABLE_MIXED_29_ADDRESSING)       || \
      defined (TP_ENABLE_MIXED_11_ADDRESSING)
    INT16U wAddressExtension;
    /* Description :                                                              */
    /* Val. range / Coding: 0..0xff                                               */
  #endif

    INT8U cBlockSize;
  /* Description :                                                              */
  /* Val. range / Coding: 0..0xff                                               */

    INT8U cSTMin;
  /* Description :                                                              */
  /* Val. range / Coding: 0..0xff                                               */
  
  INT8U cFCStatus;
  
  INT8U cSequenceNumber;
  /* Description : SequenceNumber SN                                            */
  /* Val. range / Coding: 0..0xf                                                */
} tTpRxInfoStruct;

typedef struct 
{
  INT8U cCANIDIndex;
  
  volatile INT8U  cDataBuf[TP_TX_DATA_BUF_SIZE];
  /* Description : List of pointer to transmit buffers from the application     */
  
  INT16U wDataWriteIndex;
  
  INT16U wDataReadIndex;
  /* Description : Index to transmit data - used instead of DataSegments        */
  /* Val. range / Coding: 0..4095                                               */
  
  INT16U wDataLength;
  /* Description : Length of data to be transmitted. The size of this variable  */
  /*               limits the maximum size of messages.                         */
  /* Val. range / Coding: 0..4095                                               */

  #if defined (TP_ENABLE_EXTENDED_ADDRESSING)
    # if (TP_USE_MULTIPLE_BASEADDRESS == kTpOn)
      INT16U wBaseAddress;
    /* Description :                                                              */
    /* Val. range / Coding: 0..0x7ff                                              */
    # endif
  #endif

  #if defined (TP_ENABLE_EXTENDED_ADDRESSING)       || \
      defined (TP_ENABLE_NORMAL_FIXED_ADDRESSING)   || \
      defined (TP_ENABLE_MIXED_29_ADDRESSING)
    INT16U  wTargetAddress;
  /* Description :                                                              */
  /* Val. range / Coding: 0..                                                   */
  #endif

  #if defined (TP_ENABLE_MIXED_29_ADDRESSING)       || \
      defined (TP_ENABLE_MIXED_11_ADDRESSING)
    INT8U cAddressExtension;
  /* Description :                                                              */
  /* Val. range / Coding: 0..0xff                                               */
  #endif

  #if (TP_USE_ONLY_FIRST_FC == kTpOn)
    INT8U cBlockSize;
  /* Description :                                                              */
  /* Val. range / Coding: 0..                                                   */
  #endif

  #if (TP_USE_STMIN_OF_FC == kTpOn)
    INT8U cSTMin;
    /* Description : Global value to store the requested min. separation time     */ 
    /*               received in the flow control frames. The received STmin      */
    /*               value will be adjusted to multiples of TpTxCallCycle.        */
    /* Val. range / Coding: 0..255 / in ms                                        */
  #endif
  INT8U cSequenceNumber;    
  /* Description : SequenceNumber SN                                            */
  /* Val. range / Coding: 0..0xf                                                */
} tTpTxInfoStruct;



/* Global variable definition */

extern volatile INT8U cTpTxBuf[8];
extern volatile INT8U cTpRxErrorType;
extern volatile tTpTxState TpTxState;
extern volatile tTpRxState TpRxState;
extern volatile tTpTxInfoStruct TpTxInfoStruct;
extern volatile tTpRxInfoStruct TpRxInfoStruct;
extern volatile INT8U cTpFCStatus;
extern volatile INT8U cTpFCSeperationTimeMin;
extern volatile INT8U FirstFCflg;
extern volatile INT8U FirstcSTMin; 
extern volatile INT8U TP_u1gPhisicalRspTxFnshFlg;
void TPInit(void);
void TPRxTask(void);
void TPRxProcess(INT8U cMsgIndex, INT8U cCANIDIndex);
void TPTxTask(void);
void TPTxProcess(void);
void TpTxConsecutiveFrame(void);  
void TpTxStart(void);
#endif /* _H_TP_  */

