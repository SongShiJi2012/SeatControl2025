/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescReadDTCInfo.h
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             读DTC信息
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

#ifndef _DESCREADDTCINFO_H_
#define _DESCREADDTCINFO_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		RDDTC_GLOBALS 
#define		RDDTC_EXT 
#else
#define		RDDTC_EXT        extern
#endif

#define DTCStatusAvailabilityMask                           						0x09U /*support DTC status bit 0,4*/
#define DTCFormatIdentifierISO15031_64DTCFormat             			            0    /*Haima Use ISO15031_64DTCFormat*/
#define DTCFormatIdentifierISO14229_1DTCFormat              				        1



/* 读DTC请求类型 */
typedef enum
{
    eRDDTC_RepNumOfDTCByStatusMask    = 0x01,
    eRDDTC_RepDTCMask                 = 0x02,
    eRDDTC_RepDYCSnapshotId			  = 0x03,
    eRDDTC_RepDTCSnapshot             = 0x04,
    eRDDTC_RepDTCExtDatRecByDTCNum    = 0x06,
    eRDDTC_RepSupportedDTC            = 0x0A
}eRDDTC_REQTYPE;

typedef void (* DescFuncType)(void);

/* 读DTC诊断信息 */
typedef struct
{
    eRDDTC_REQTYPE          eSID;
    INT8U                 ServerReqLen;
    DescFuncType            pServerProcess;
}tRDDTC_INFO;









// RDDTC_EXT void DescRdDTC_vogTpTxBufFreeCallBack(void);
#if SID19_RDDTCINFO_EN == DESC_ENABLE
RDDTC_EXT void DescReadDTCInformation(void);
#endif



 
#ifdef __cplusplus
}
#endif


BOOL DescGetDrHeatDTCFailFlag(void);
BOOL DescGetPaHeatDTCFailFlag(void);
BOOL DescGetDrVenDTCFailFlag(void);
BOOL DescGetPaVenDTCFailFlag(void);


#endif  /*_DESCREADDTCINFO_H_*/

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  

