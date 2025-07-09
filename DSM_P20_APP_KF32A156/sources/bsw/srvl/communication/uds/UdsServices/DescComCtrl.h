/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescComCtrl.h
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             通信控制
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven 莫松文
** Created date:            2013.10.23
** Version:                 V1.0
** Descriptions:            The original version 初始版本
** 
**------------------------------------------------------------------------------------------ 
** Modified By:             
** Modified date:           
** Version:                 
** Description:             
** 
********************************************************************************************/
#ifndef _DESCCOMCTRL_H_
#define _DESCCOMCTRL_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		COMCTL_GLOBALS 
#define		COMCTL_EXT 
#else
#define		COMCTL_EXT        extern
#endif


#define             MSG_TYPE_NORMAL                      0x01
#define             MSG_TYPE_NETWORK                     0x02
#define             MSG_TYPE_ALL                         0x03

#define             MASK_RX_ENABLE                       0x01
#define             MASK_TX_ENABLE                       0x02


typedef enum
{
    eRXENABLE_TXENABLE   = 0x00,
    eRXENABLE_TXDISABLE  = 0x01,
    eRXDISABLE_TXENABLE  = 0x02,
    eRXDISABLE_TXDISABLE = 0x03,
}eCOM_CTL_TYPE;




typedef struct
{
    INT8U             ReqDatLen;
    void                (*ServiceProcess)(INT8U ComMsgType);
}tCOMCTL_INFO;

typedef struct stDESCROUTINFO
{
    eCOM_CTL_TYPE       eComCtrlType;
//     INT8U             SessionAllow;
    tCOMCTL_INFO        ComCtrlInfo;
}tDESC_COM_INFO;       

#if SID28_COMCTL_EN == DESC_ENABLE 

COMCTL_EXT void DescCommunicationControl(void);

COMCTL_EXT void  ComCtrlInit(void);
COMCTL_EXT INT8U GetAPPCommDisable(void);
#endif

#ifdef __cplusplus
}
#endif
 
#endif  /*_DESCCOMCTRL_H_*/

