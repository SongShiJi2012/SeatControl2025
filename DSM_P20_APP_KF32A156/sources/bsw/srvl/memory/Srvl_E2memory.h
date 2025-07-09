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
#include "DiagDTCGenerate.h"

#define         D_ReadE2promTimeout_Time        (2000 / 20) // 500
#define         D_WriteE2promTimeout_Time       (5000 / 20) // 1S

#define         RW_START_MASK                               0x01
#define         RW_END_MASK                                 0x10
#define         RW_NULL                                     0x00
//已使用5A A5
#define         EraseFlg       (0xAA)

// 根据需要增加需要检测EEPROM项的Index
typedef  enum
{
	enCheckFromAppJumpToBootFlg_Idx,

	enCheckE2Idx_Number
} enCheckE2Idx;
extern const enSrvMemIndex E2WriteVerifyIndexList[enCheckE2Idx_Number];//增加对应的定义枚举数组
/*需要升级标识的种类定义*/
#define D_DIAG_NeedUpdateSort_Null				(0U)
#define D_DIAG_NeedUpdateSort_NeedReply			(1U)
#define D_DIAG_NeedUpdateSort_NeedNoReply		(2U)

// D_E2Idx 和 CheckE2IdxOffset 是有偏差的
#define     D_E2IdxAddCheckE2IdxOffset      ((INT8U)FromAppJumpToBootFlg_Index - (INT8U)enCheckFromAppJumpToBootFlg_Idx) // E2项和检测的E2项偏差

typedef enum EN_SYSTEM_CONFIG_INDEX
{
	EN_SteerHeat_SysCfg = 23,				//方向盘加热
	EN_P20_SysCfg = 40,
	EN_P20OffRoadVersion_SysCfg = 41,
	EN_P20PHEV_100km_SysCfg = 42,
	EN_P20PHEV_50km_SysCfg = 43,
}en_System_Config_Index;

typedef enum
{
	eEEOP_WR,
	eEEOP_RD,
} eEEOP_TYPE;

typedef struct
{
	INT8U*              pDatBuf;
	INT16U              DatLen;
	INT32U              EEAddr;
	INT8U               BackUpIndex;
	INT8U               FlgPos;
} stAPPEEDATA_INFO;

typedef struct
{
	enE2promIndex               OpIndex;
	enE2promOptResult        	E2promOpResult[E2promItem_Number];
} stAPPEEOP_INFO;

typedef void (*pDescRespProcess)(enE2promOptResult eWriteResult); // 修改函数指针类型，参数为枚举类型

typedef struct
{
	BOOL    CheckReadE2promFlg[enCheckE2Idx_Number];
	BOOL    CheckWriteE2promFlg[enCheckE2Idx_Number];
	INT32U  ReadE2promTimeoutCnt[enCheckE2Idx_Number];
	INT32U  WriteE2promTimeoutCnt[enCheckE2Idx_Number];
	pDescRespProcess    ReadE2promRespProcess[enCheckE2Idx_Number];
	pDescRespProcess    WriteE2promRespProcess[enCheckE2Idx_Number];
} stDescCheckE2promResult;

extern stDescCheckE2promResult DescCheckE2promResult;
extern stAPPEEOP_INFO AppE2promOpInfo;
extern stCarE2promInfo AppCarE2promInfo;

extern void  Srvl_E2SetWriteFlg(enE2promIndex  eE2promIndex);
extern void  Srvl_E2FlagUpdateTask(void);
extern void  Srvl_E2PowerOnInit(void);
extern void  Srvl_E2SetOpIndex(enE2promIndex  eE2promIndex);
extern void  Srvl_E2SetCheckWriteResultFlg(enCheckE2Idx E2promIndex);
extern void  Srvl_E2CheckWriteResultAndResp(void);
extern BOOL  Srvl_E2IsIndexDTCWriting(void);
extern void  Srvl_E2SeatMemoryPosiInit(void);
extern void  Srvl_E2Init(void);



extern INT8U Srvl_GetRstToFactModeFlg(void);
extern void Srvl_SetRstToFactModeFlg(INT8U flag);
extern INT8U Srvl_getSystemConfigPram(en_System_Config_Index index);
extern BOOL Srvl_SetDTCStatusMask(DiagDtcNameType_t u8DtcIndex, INT8U *u8Buff);
extern BOOL Srvl_GetDTCStatusMask(DiagDtcNameType_t u8DtcIndex, INT8U *u8Buff);
extern enSrvMemIndex Srvl_getClearDTCIndex(void);
extern BOOL Srvl_IsMemDiagDTCIndex(enSrvMemIndex MemIndex);
extern void Srvl_E2ReadAllTask(void);
extern void Srvl_E2WriteAllTask(void);
extern void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex);
extern void Srvl_E2WritePolling(void);
extern void Srvl_E2ReadPolling(void);
extern void Srvl_E2AllDataInit(void);
extern void Srvl_E2WritePollingIfReady(void);

#endif  /*_APPEEPROM_H_*/

