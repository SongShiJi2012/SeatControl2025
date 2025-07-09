/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               AppE2prom.h
** Last modified Date:      2013.09.03
** Last Version:            V1.0
** Description:             EERPOM应用层
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven 莫松文
** Created date:            2013.09.03
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

#ifndef APPEEPROM_H
#define APPEEPROM_H
#include  "Common.h"
#include "Srvl_E2Operate.h"
#include "Srvl_E2cfg.h"
#include "Srvl_E2Cfg_Generation.h"
#define         D_ReadE2promTimeout_Time        (2000 / 20) // 500
#define         D_WriteE2promTimeout_Time       (5000 / 20) // 1S

#define         RW_START_MASK                               0x01
#define         RW_END_MASK                                 0x10
#define         RW_NULL                                     0x00
//已使用5A A5
#define         EraseFlg       		(0xAA)
#define         D_READ_NUMBER       (6)

// 根据需要增加需要检测EEPROM项的Index
typedef  enum
{
	enCheckFromAppJumpToBootFlg_Idx,

	enCheckE2Idx_Number
} enCheckE2Idx;

#define			NOFLGWR					    	     0xFF
#define         NOBACKUP                             0


typedef void (*pDescRespProcess)(void);

typedef struct
{
	BOOL    CheckReadE2promFlg[D_READ_NUMBER];
	BOOL    CheckWriteE2promFlg[D_READ_NUMBER];
	INT32U  ReadE2promTimeoutCnt[D_READ_NUMBER];
	INT32U  WriteE2promTimeoutCnt[D_READ_NUMBER];
	pDescRespProcess    ReadE2promRespProcess[D_READ_NUMBER];
	pDescRespProcess    WriteE2promRespProcess[D_READ_NUMBER];
} stDescCheckE2promResult;

#define		IsAppE2promWriteEnd(Index)    ((E2promOpOK == Srvl_GetE2DataBlockOptResult(Index)) || (E2promOpFail == Srvl_GetE2DataBlockOptResult(Index)))
#define		IsAppE2promReadEnd(Index)     ((E2promOpOK == Srvl_GetE2DataBlockOptResult(Index)) || (E2promOpFail == Srvl_GetE2DataBlockOptResult(Index)))
#define		IsAppE2promOpOK(Index)        (E2promOpOK == Srvl_GetE2DataBlockOptResult(Srvl_GetE2DefineDataBlockID(Index)))


extern stDescCheckE2promResult DescCheckE2promResult;

extern void  Srvl_E2PowerOnInit(void);
extern void  Srvl_E2Init(void);

extern void Srvl_E2ReadAllTask(void);
extern void Srvl_E2WriteAllTask(void);

extern void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex);
extern void Srvl_E2WritePolling(void);
extern void Srvl_E2ReadPolling(void);

extern void  AppAppE2promSetCheckReadResultFlg(INT8U E2promIndex);
extern void  AppAppE2promSetCheckWriteResultFlg(INT8U E2promIndex);
extern void  AppAppE2promCheckReadAndWiteResultAndResp(void);
#endif  /*_APPEEPROM_H_*/

