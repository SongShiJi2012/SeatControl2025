
#ifndef CAN_DRV_H
#define CAN_DRV_H

/********************************************************************************
**  Include files
********************************************************************************/
#include  "Common.h"
#include "flexcan_driver.h"
#define DIAG_DEFAULT_VALUE		(0x00)

#define PEPS_NM_MSG_NEED_TX_FLAG_MASK          			0x1000 //bit12 is NM message mask
#define TST_PHYSICAL_RESP_NEED_TX_FLAG_MASK   		    0x2000 //bit13 is Phy-Rsp mask
#define TP_FC_NEED_TX_FLAG_MASK               			0x4000 //bit14 is FC mask

#define     CANDRVCYCTIME                               5



/*TX Cycle time parameters*/
#define MSG_CYCLE_BASE_TIME               			    (INT8U)(0)
#define MSG_CYCLE_TX_TOLERANCE100MS           		    (-5)
#define MSG_CYCLE_200MS                                 ((200 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_100MS                                 ((100 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_80MS                                  ((80 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_20MS                                  ((20 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_40MS                                  ((40 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_50MS                                  ((50 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
#define MSG_CYCLE_10MS                                  ((10 + MSG_CYCLE_TX_TOLERANCE100MS) / (MSG_CYCLE_BASE_TIME+1)/ CANDRVCYCTIME)
/*ע��:��Ҫ�� eRXINDEX ö��˳��һ��,������λ*/
typedef union
{
	INT8U u1aData[2];	// ���뱣���� eRXINDEX ö��������ƥ��
	struct
	{
		/*0~7*/
		INT8U Flag_0x367	:	1;
		INT8U Flag_0x351	:	1;
		INT8U Flag_0x2AE	:	1;
		INT8U Flag_0x2A7	:	1;
		INT8U Flag_0x28E	:	1;
		INT8U Flag_0x284	:	1;
		INT8U Flag_0x283	:	1;
		INT8U Flag_0x281	:	1;

		INT8U Flag_0x26E	:	1;
		INT8U Flag_0x238	:	1;
	}Bits;
}unCANMsgFlag;
/* RX ID Index,���յ���Ӧ�ñ���ID���� ע��:��Ҫ��CanRxId ˳��һ��  */
typedef enum
{
	eRXINDEX_0x367 = 0,
	eRXINDEX_0x351,
	eRXINDEX_0x2AE,
	eRXINDEX_0x2A7,
	eRXINDEX_0x28E,
	eRXINDEX_0x284,
	eRXINDEX_0x283,
	eRXINDEX_0x281,

	eRXINDEX_0x26E,
	eRXINDEX_0x238,

	eRXINDEX_MAX
}eRXINDEX;

typedef enum
{
    CANMSG_FLAG_Lost    = 0,  	// ���Ķ�ʧ��־
    CANMSG_FLAG_Online,  		// �������߱�־����ʾ���ĵ�ǰ�Ƿ����߽���
    CANMSG_FLAG_Update,  		// �������ݸ��±�־����ʾ���������Ƿ����¸���
    CANMSG_FLAG_MAX          	// ��־�������������ڱ߽��жϻ������С����
} eCANMsgFlagIndex ;

//Tx Base Msg Info
typedef struct
{
	flexcan_msgbuff_id_type_t IdType;
	INT32U TxID;
	INT8U TxLen;
	INT8U *pTxSrcBuf;
}CANTxBaseInfo;

//Event Message Info
typedef struct
{
	CANTxBaseInfo TxBaseInfo;
	INT8U EventPeriod;
	INT8U EventSendTims;
}CANTxEMsgInfo;
/*Tx ID Index*/
typedef enum
{
	eTXINDEX_NM,
	eTXINDEX_DIAG,
} eTXINDEX;

/*�¼��ͷ��ͱ���ö��,�����÷�������λ*/
typedef enum
{
	eDSMG_DSM6E0,
	eDSMG_DSM6E1,
	eEMSG_MAX,
}eEMSG_INDEX;

/*�����ͷ��ͱ���ö��*/
typedef enum
{
	eDSMG_0x502,
	eDSMG_0x501,
	eDSMG_0x500,
	eDSMG_0x3B2,
	eDSMG_MAX,
}ePEMSG_INDEX;
/* �¼���Ϣ */
typedef struct
{
    INT8U                SndCycTimer;
    INT8U                SndTimes;
}tCANDRV_EMSG_INFO;

typedef struct
{
    INT8U                MsgMaxNo;
    INT16U                EventSendOverMask;  
    INT16U                NeedSendMask;  
    void                     (*pMsgILInit)(eEMSG_INDEX eIndex); 
    tCANDRV_EMSG_INFO        pMsgInfoTbl[eEMSG_MAX];  
}tCANDRV_EMSG_OPT;

/* �����¼� */
typedef struct
{      
    INT8U                SndCycTimer;
    INT8U                SndTimes;
}tCANDRV_PEMSG_INFO;

typedef struct
{
    INT8U				MsgMaxNo;
    INT16U				NeedSendMask;
    void				(*pMsgILInit)(ePEMSG_INDEX eIndex);
    tCANDRV_PEMSG_INFO	pMsgInfoTbl[eDSMG_MAX];
}tCANDRV_PEMSG_OPT;

/* ͨ�ſ��� */
typedef union
{
    INT8U               All;
    struct
    {
        INT8U            RxEnable            :1;
        INT8U            TxEnable            :1;   
        INT8U            Rsv                 :6;  
        
    }Bits;
    
}uCOMCTRL_INFO;

typedef struct
{
    uCOMCTRL_INFO           NormalComMsg;
    uCOMCTRL_INFO           NMComMsg;
}tCOMCTRL_OPT;

extern tCANDRV_PEMSG_OPT CANDrvPEMsgOpt;
extern tCANDRV_EMSG_OPT  CANDrvEMsgOpt;
extern volatile INT16U cMsgNeedTxIndFlag;
extern  tCOMCTRL_OPT      ComCtrlOpt;
extern  tCOMCTRL_OPT      DescComCtrlOpt;		//ͨ��$28�������õ�ֵ

/*������Ϣ���͹���*/
#define ECUAL_CAN_DISABLE_NM_TX_ENABLE()	((ComCtrlOpt.NMComMsg.Bits.TxEnable = 0))
#define ECUAL_CAN_ENABLE_NM_TX_ENABLE()		((ComCtrlOpt.NMComMsg.Bits.TxEnable = 1))
#define ECUAL_CAN_IS_NM_TX_ENABLE()         ((ComCtrlOpt.NMComMsg.Bits.TxEnable == 1) ? (TRUE) : (FALSE))

/*������Ϣ���չ���*/
#define ECUAL_CAN_DISABLE_NM_RX_ENABLE()	((ComCtrlOpt.NMComMsg.Bits.RxEnable = 0))
#define ECUAL_CAN_ENABLE_NM_RX_ENABLE()		((ComCtrlOpt.NMComMsg.Bits.RxEnable = 1))
#define ECUAL_CAN_IS_NM_RX_ENABLE()         ((ComCtrlOpt.NMComMsg.Bits.RxEnable == 1) ? (TRUE) : (FALSE))

/*APP��Ϣ���͹���*/
#define ECUAL_CAN_DISABLE_APP_TX_ENABLE()	((ComCtrlOpt.NormalComMsg.Bits.TxEnable = 0))
#define ECUAL_CAN_ENABLE_APP_TX_ENABLE()	((ComCtrlOpt.NormalComMsg.Bits.TxEnable = 1))
#define ECUAL_CAN_IS_APP_TX_ENABLE()        ((ComCtrlOpt.NormalComMsg.Bits.TxEnable == 1) ? (TRUE) : (FALSE))

/*APP��Ϣ���չ���*/
#define ECUAL_CAN_DISABLE_APP_RX_ENABLE()	((ComCtrlOpt.NormalComMsg.Bits.RxEnable = 0))
#define ECUAL_CAN_ENABLE_APP_RX_ENABLE()	((ComCtrlOpt.NormalComMsg.Bits.RxEnable = 1))
#define ECUAL_CAN_IS_APP_RX_ENABLE()        ((ComCtrlOpt.NormalComMsg.Bits.RxEnable == 1) ? (TRUE) : (FALSE))
BOOL Ecual_GetCANACKErrTxEnable(void);

void Ecual_SetCANACKErrTxEnable(BOOL t_enable);
BOOL Ecual_GetCanACKErrSts(void);
static void StdMsgRxProcess(INT8U cMsgIndex);
static void CANDrvRxTask(void);
static BOOL Ecual_GetCanFlag(eCANMsgFlagIndex flagIndex, eRXINDEX CanIdIndex);
static void Ecual_SetCanFlag(eCANMsgFlagIndex flagIndex, eRXINDEX CanIdIndex, BOOL value);

extern void CANDrvInit(void);
extern void CANDrvTxTask(void);
extern void CANDrvNMTxProcess(void);
extern void CANDrv_TxTimeReset(void);
extern void Ecual_SetPEMsgEventTrigger(ePEMSG_INDEX Index);
extern void CANDrvEMsgEventSet(eEMSG_INDEX Index);

extern BOOL Ecual_CanGetUdsMsgRecFlg(void);
extern BOOL Ecual_GetCanMsgLostFlag(eRXINDEX CanIdIndex);
extern void Ecual_CanRxStateInit(void);
extern void Ecual_CanRxStateMonitor(void);
extern void Ecual_CanCheckSendTask(void);
extern void Ecual_CanTaskInit(void);
extern void Ecual_CanTask(void);
extern void Ecual_FNOSInit(void);
extern void CANDrvEventMsgTxProcess(void);
#endif /* _H_CAN_DRV_ */

