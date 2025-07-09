/*****************************************************************************
               Copyright (C) 2016, Michip Technologies Co., Ltd
                             All Rights Reserved
******************************************************************************
Դ�ļ���: Osek.c
�ļ�����: OSEK Network Management
������Ϣ: wangyongxiang
��������: 2019-08-04
���°汾: 0.0.1
��ϸ˵��: 
*****************************************************************************/
#ifndef COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_
#define COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Ecual_CAN.h"
#include "CANDrvMSCAN.h"
/* ============================ [ MACROS    ] ====================================================== */
#define OSEK_NM 1   //log  wyx
#define OSEKNM_NET_NUM 1

#define PDUR_ID_OSEK_NM_RX   0
#define PDUR_ID2_OSEK_NM_TX  0

/*网络管理报文ID取值范围*/
#define D_CAN_NM_BASE_ADDR              	(0x480U)
#define D_CAN_NM_END_ADDR               	(0x48FU)//P20 客户只支持480到48F

#define NM_CANID 							(0x488U)
#define NM_DLC 								(8U)

#define D_CAN_COMM_PERIOD                               5

#define D_SYS_MS_TIME_BASE                  1UL

#define D_SERVICE_CAN_MSG_PERIOD        (1U * D_SYS_MS_TIME_BASE)  /*CAN发送时间不准*/

#define D_SERVICE_DIAG_NM_PERIOD        (5U * D_SYS_MS_TIME_BASE)


#define D_CAN_ACK_ERR_RESET      		(150U * D_SYS_MS_TIME_BASE) /*ACK无应答持续发送时间*/
/* ============================ [ TYPES     ] ====================================================== */
typedef uint32_t Can_IdType;

typedef enum
{
	NmOsek_enmEnable,
	NmOsek_enmDisable,
}NmOsek_enCANSt;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void CanIf_OsekNmUserTxConfirmation();
void Osek_RxIndication(INT8U RSCAN0Chl, const CANMsgRxBase * pFrame);

extern void OsekNm_Stop(void);
extern void OsekNm_Start(void);
extern volatile NmOsek_enCANSt NmOsek_engCANAppComm;

extern INT8U OsekNm_GetOsekInOnStatus(void);

#endif /* COM_AS_APPLICATION_COMMON_CONFIG_OSEKNM_CFG_H_ */
