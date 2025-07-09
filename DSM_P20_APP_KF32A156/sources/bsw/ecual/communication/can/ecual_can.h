/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_can.h
*
*  Description:  board CAN abstraction interface header file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-16
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/

#ifndef _ECUAL_CAN_H_
#define _ECUAL_CAN_H_

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "kf32a156_canfd.h"
#include "flexcan_driver.h"
//#include "osif_common.h"
#include "types.h"

/*************************************************************************************************
 * Macro definition
 *************************************************************************************************/
enum
{
    INST_CAN_0 = 0U,
    INST_CAN_1 = 1U,
    
    MAX_CAN_PORT
};

typedef enum {
    CAN_125K = 0,
    CAN_250K,
    CAN_500K,
    CAN_1M,
	CAN_2M
} E_CAN_BANDRATE;


// can mailbox
enum
{
    CAN_MAILBOX_0 = 0,
    CAN_MAILBOX_1,
    CAN_MAILBOX_2,
    CAN_MAILBOX_3,
    CAN_MAILBOX_4,
    CAN_MAILBOX_5,
    CAN_MAILBOX_6,
    CAN_MAILBOX_7,
    CAN_MAILBOX_8,
    CAN_MAILBOX_9,
    CAN_MAILBOX_10,
    CAN_MAILBOX_11,
    CAN_MAILBOX_12,
    CAN_MAILBOX_13,
    CAN_MAILBOX_14,
    CAN_MAILBOX_15,
    CAN_MAILBOX_16,
    CAN_MAILBOX_17,
    CAN_MAILBOX_18,
    CAN_MAILBOX_19,
    CAN_MAILBOX_20,
    CAN_MAILBOX_21,
    CAN_MAILBOX_22,
    CAN_MAILBOX_23,
    CAN_MAILBOX_24,
    CAN_MAILBOX_25,
    CAN_MAILBOX_26,
    CAN_MAILBOX_27,
    CAN_MAILBOX_28,
    CAN_MAILBOX_29,
    CAN_MAILBOX_30,
    CAN_MAILBOX_31,
    CAN_MAILBOX_32,
    CAN_MAILBOX_33,
    CAN_MAILBOX_34,
    CAN_MAILBOX_35,
    CAN_MAILBOX_36,
    CAN_MAILBOX_37,
    CAN_MAILBOX_38,
    CAN_MAILBOX_39,
    CAN_MAILBOX_40,
    CAN_MAILBOX_41,
    CAN_MAILBOX_42,
    CAN_MAILBOX_43,
    CAN_MAILBOX_44,
    CAN_MAILBOX_45,
    CAN_MAILBOX_46,
    CAN_MAILBOX_47,
    CAN_MAILBOX_48,
    CAN_MAILBOX_49,

    CAN_MAILBOX_NUM_MAX
};

/*****
 *   CAN中断源
 */
typedef enum {
    /*  CAN0  */
    INT_SOURCE_CAN0_ORED          = 0,
    INT_SOURCE_CAN0_ERROR         = 1,
    INT_SOURCE_CAN0_WAKEUP        = 2,
    INT_SOURCE_CAN0_ORED_0_15MB   = 3,
    INT_SOURCE_CAN0_ORED_16_31MB  = 4,

    /*  CAN1  */
    INT_SOURCE_CAN1_ORED          = 5,
    INT_SOURCE_CAN1_ERROR         = 6,
    INT_SOURCE_CAN1_ORED_0_15MB   = 7,
    INT_SOURCE_CAN1_ORED_16_31MB  = 8,

    /*  CAN2  */
    INT_SOURCE_CAN2_ORED          = 9,
    INT_SOURCE_CAN2_ERROR         = 10,
    INT_SOURCE_CAN2_ORED_0_15MB   = 11,
    INT_SOURCE_CAN2_ORED_16_31MB  = 12,

    INT_SOURCE_CAN_MAX
} E_CAN_INT_SOURCE_INDEX;


typedef void (*CAN_RemoteWakeup_Callback_t)(void);

/*************************************************************************************************
 * Variable structure declaration
 *************************************************************************************************/

/* 配置msg 进buff(MB)的结构体 */
#if 0
typedef struct 
{
	INT8U NewFrameFlag; /*接收到新的数据标识*/
	INT8U MBIdx;        /*邮箱索引号*/
	INT8U data_length;
	flexcan_msgbuff_id_type_t idType;/*CAN ID类型*/
	INT32U acceptedId; /*此邮箱对应的接收CAN ID*/
	INT32U mask; /*邮箱对应的接收掩码*/
	Canfd_MailboxHeaderType RxBuff; /*接收数据缓存*/
} CAN_MSG_MB_CONFIG_STRU;

/*CAN物理层发送数据结构体*/
typedef struct
{
	volatile INT8U BusyFlag; /*邮箱正在发送中标识,0-空闲 1-忙*/
	INT8U MBIdx; /*邮箱索引号*/
	INT32U acceptedId; /*此邮箱对应的发送CAN ID*/
	INT8U data_length;
	INT8U TxBuff[64]; /*发送数据缓存*/
	flexcan_msgbuff_id_type_t idType;/*CAN ID类型*/
}EcualCanMainMailboxTxbuffCfg;
#endif

/*CAN物理层接收数据结构体*/
typedef struct CANMAINMAILRXBUFFCFG
{
	INT8U NewFrameFlag; /*接收到新的数据标识*/
	INT8U MailBoxIndex; /*邮箱索引号*/
	flexcan_msgbuff_id_type_t eMsgIDType;/*CAN ID类型*/
	INT32U CanRxId; /*此邮箱对应的接收CAN ID*/
	INT32U IndividualMask; /*邮箱对应的接收掩码*/
	//flexcan_msgbuff_t RxBuff; /*接收数据缓存*/
	Canfd_MailboxHeaderType RxBuff; /*接收数据缓存*/
}strCanMainMailboxRxbuffCfg;

/*CAN物理层发送数据结构体*/
typedef struct CANMAINMAILTXBUFFCFG
{
	INT8U BusyFlag; /*邮箱正在发送中标识,0-空闲 1-忙*/
	INT8U MailBoxIndex; /*邮箱索引号*/
	INT32U CanTxId; /*此邮箱对应的发送CAN ID*/
	//INT8U TxBuff[8]; /*发送数据缓存*/
	Canfd_MailboxHeaderType TxBuff; /*发送数据缓存*/
}strCanMainMailboxTxbuffCfg;

void ecual_CAN_SetHwFilter(uint8_t instance,strCanMainMailboxRxbuffCfg* MailboxCfg);
/*************************************************************************************************
 * Function Name:        ecual_CAN_init
 *
 * Description:          初始化CAN，设置相应波特率
 *
 * Input:                const uint32_t instance:  
 *                             常量参数, CAN通道实例, 参考头文件枚举 < INST_ADC0, INST_ADC1 ... >
 *                       E_CAN_BANDRATE eBaudrate:
 *                             设置相应波特率
 *                       flexcan_callback_t pCallback_event:
 *                             设置事件回调函数
 *                       flexcan_error_callback_t pCallback_error:
 *                             设置错误回调函数
 *
 * Output:               none
 *
 * Return:               true is successful
 *
 *************************************************************************************************/
bool_t ecual_CAN_init( const uint32_t instance, 
                       flexcan_callback_t pCallback_event,
                       flexcan_error_callback_t pCallback_error,
                       CAN_RemoteWakeup_Callback_t pCallback_wakeup
                       );

/*****************************************************************************
** Function:    ECUAL_CAN_ConfigTxMb
** Description: 配置CAN的发送邮箱
** Parameter:   
** Return:      
******************************************************************************/
Can_ReturnType ecual_CAN_ConfigTxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg);

/*****************************************************************************
** Function:    ECUAL_CAN_ConfigRxMb
** Description: 配置CAN的接收邮箱
** Parameter:   
** Return:      
******************************************************************************/
bool_t ecual_CAN_ConfigRxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg );

/*****************************************************************************
 ** Function:    ecual_CAN_receive
 **
 ** Description: 设置CAN邮箱处于接收状态（只在调用的过程中开启接收中断）
 **
 ** Parameter:   none
 **
 ** Return:      none
 ******************************************************************************/
bool_t ecual_CAN_receive( const uint8_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *message );

/*****************************************************************************
** Function:    ECUAL_CAN_SendOnce
** Description: 设置CAN邮箱发送一次报文
** Parameter:   
** Return:      
******************************************************************************/
bool_t ecual_CAN_sendOnce( const uint8_t instance,
                           const bool_t isCANFD,
                           strCanMainMailboxTxbuffCfg *pConfigMsg,
                           Canfd_MailboxHeaderType* tx_info
                           );

/*************************************************************************************************
 * @function Name:        ecual_CAN_Deinit
 *
 * @description:          Deinit the special CAN path
 *
 * @parameters:           none
 *
 * @return:               none
 *************************************************************************************************/
void ecual_CAN_Deinit( const uint8_t instance );

/*************************************************************************************************
 * @function Name:        ecual_CAN_setIntSource
 *
 * @description:          设置CAN相关中断源表示值
 *
 * @note:
 *
 * @parameters:           none
 *
 * @return:               none
 *************************************************************************************************/
bool_t ecual_CAN_setIntSource( const E_CAN_INT_SOURCE_INDEX index );

/*************************************************************************************************
 * @function name:      ecual_CAN_clrIntSource
 *
 * @description:        清除CAN中断源表示值
 *
 * @note:
 *
 * @parameters:         none
 *
 * @return:             none
 *************************************************************************************************/
bool_t ecual_CAN_clrIntSource( const E_CAN_INT_SOURCE_INDEX index );

/*************************************************************************************************
 * @function name:      ecual_CAN_IntControl
 *
 * @description:        CAN相关中断控制
 *
 * @note:
 *
 * @parameters:         none
 *
 * @return:             none
 *************************************************************************************************/
bool_t ecual_CAN_IntControl( const E_CAN_INT_SOURCE_INDEX index, const bool_t enable );

void ecual_CAN_NewEnterFreezeMode(const uint8_t instance);
void ecual_CAN_NewExitFreezeMode(const uint8_t instance);


#endif /* _ECUAL_CAN_H_ */

/*************************************************************************************************
 * End of Line
 *************************************************************************************************/
