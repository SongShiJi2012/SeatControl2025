#ifndef        _BOOTCANDRV_H
#define         _BOOTCANDRV_H
#include  "Common.h"

#define          BOOT_RX_MSG_PHYSICAL                              	0
#define          BOOT_RX_MSG_FUNTION					 			1

#define			 BOOT_RX_MSG_PHYSICAL_ID							BOOTDESC_REQID_PHY
#define			 BOOT_RX_MSG_FUNTION_ID								BOOTDESC_REQID_FUC

#define			BOOT_MSK_CANID		   							    (0x00000fff)
#define 		BOOT_BCM_MSG_NEED_TX_FLAG_MASK             			(0x01)
#define 		BOOT_TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK   	        (0x02)
#define 		BOOT_TP_FC_NEED_TX_FLAG_MASK               			(0x04)
           
#define			BOOT_MSG_RUNNING_VALID_DLC					        (8)
#define			BOOT_MSG_PERIOD_TX_BASE_TIME				        (5)
#define			BOOT_MSG_10MS_TIME						            (10 / BOOT_MSG_PERIOD_TX_BASE_TIME - 1)
#define 		BOOT_MSG_CYCLE_BASE_TIME                            (1)

typedef enum
{
	eBOOT_MSG_EVENT,
	eBOOT_MSG_PERIOD,
	eBOOT_MSG_PERIODEVNET,
	eBOOT_MSG_TYPE_MAX,
} eBOOT_MSG_TYPE;

typedef enum
{
	eBOOT_PMSG_TST,
	eBOOT_PMSG_MAX,
} eBOOT_PMSG_INDEX;

typedef struct
{
	BOOT_U8                SndCycTimer;
} tBOOT_CANDRV_PMSG_INFO;

typedef struct
{
	BOOT_U8                		MsgMaxNo;
	BOOT_U16               		NeedSendMask;
	void                  		(*pBootMsgILInit)(eBOOT_PMSG_INDEX eIndex);
	tBOOT_CANDRV_PMSG_INFO      pMsgInfoTbl[eBOOT_PMSG_MAX];
} tBOOT_CANDRV_PMSG_OPT;

typedef struct
{
	BOOT_U16			RxID;
	BOOT_U8         	cDLC;
	BOOT_U8				*pRxDstBuf;
} tBOOT_CANRX_INFO;

typedef struct
{
	BOOT_U16			TxID;
	BOOT_U8				TxLen;
	BOOT_U8				*pTxSrcBuf;
} tBOOT_CANTX_BASE_INFO;

typedef struct
{
	tBOOT_CANTX_BASE_INFO       TxBaseInfo;
	BOOT_U8        				Period;
} tBOOT_CANTX_PMSG_INFO;

typedef struct
{
	BOOT_U8		TstFrameID;
	BOOT_U8		ErrType;
} BootCAN_stMsgTST;


#ifdef BOOTCAN_PERIODMSGTX
extern BOOT_U8 DebugDataPMsgTx[8];
extern volatile BootCAN_stMsgTST    BootCAN_stgMsgTST;
extern tBOOT_CANDRV_PMSG_OPT  BOOT_CANDrvPMsgOpt;
extern volatile BOOT_U8 Boot_DownloadFlg;
#endif



void    BootCANDrvTask(void);
void    BootCANDrvInit(void);
void    BootCANDrvRxTask(void);
BOOL	BootStdMsgRxProcess(BOOT_U8 cMsgIndex);
void    BootCANDrvTxTask(void);
void	BootTST_PhysicalRespTxProcess(void);
void    BootTST_PhysicalRespFlowControlTxProcess(void);
void 	BootCANDrv_vogTask(void);

#endif


