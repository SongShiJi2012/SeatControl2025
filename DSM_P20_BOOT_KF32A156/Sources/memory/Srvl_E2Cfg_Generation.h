/************************************************************************************************
File created time : 2025-06-04 16:32:11
File Name:          Srvl_E2Cfg_Generation.h
Author:             python Script Generation
Description:        E2数据块配置定义表 - 使用excel表进行管理，不可手动修改
************************************************************************************************/



#ifndef _PYTHONE_E2CFG_H_
#define _PYTHONE_E2CFG_H_

#include "Common.h"



/**数据块读写请求枚举**/
typedef enum _EEPROM_OPT_STA_T
{
    EN_EEPROM_STA_IDLE = 0, /*空闲*/
    EN_EEPROM_STA_WRITE,    /*写请求状态*/
    EN_EEPROM_STA_READ,     /*读请求状态*/
} EepromOptReq;

/**数据块读写结果枚举定义**/
typedef enum
{
    E2promNullOp  = 0,   /*初始化*/
    E2promWaitIDL,       /*等待操作*/
    E2promOping,         /*操作中*/
    E2promOpOK,          /*操作成功*/
    E2promOpFail,        /*操作失败*/
} enE2promOptResult;

/**数据块配置数据结构**/
typedef struct EEPROMPARATABLE
{
    INT16U             DataBlockID;         /*ID标识*/
    INT32U             StartAddr;           /*起始地址*/
    INT8U              DataLength;          /*数据长度*/
    INT16U             BackUpID;            /*备份数据标识*/
    INT8U              *pParaBuffer;        /*指向的数据*/
    EepromOptReq       OptReq;              /*读写请求状态*/
    enE2promOptResult  OptResult;           /*读写操作结果*/
} strEepromDataBlockCfgTable;

/**自定义存储项数据结构**/
typedef struct EE_SRV_DATA_TABLE_CFG
{
    INT16U             SrvMemIndex;     /* 自定义枚举 */
    INT8U              StartOffset;     /* 定义存储在数据块中对应RAM变量的起始偏移量 */
    INT8U              len;             /* 定义存储长度 */
    INT16U             DataBlockID;     /* 数据块ID */
} strEepromDataDefineTable;


#define    D_USEID_NUMBER          6     /* 使用ID的数量 */
#define    D_USEID_NUMBER_NO_BACKUP      3  /* 使用ID的数量 不包含备份*/
#define    D_NOBACKUP              0     /* 无备份*/


#define     D_APP_INIT_Data_Len_4                     4
#define     D_BOOT_INIT_Data_Len_4                    4
#define     D_DareBootVersion_Len_8                   8
#define     D_CustomerBootVersion_Len_15              15

#define     D_APP_ValidFlg_Len_8                      8
#define     D_FingerPrint_ProgramDate_F199_Len_4      4
#define     D_FingerPrint_RepairShopCodeF198_Len_8    8
#define     D_BOOTUdsSecurityAccessTimes_Len_1        1
#define     D_AppUdsSecurityAccessTimes_Len_1         1
#define     D_Reserved0_Len_1                         1

#define     D_AppJumpToBootFlg_Len_1                  1
#define     D_WakeUpSource_Len_1                      1
#define     D_Reserved1_Len_1                         1



typedef enum
{
/********数据块ID_0 定义开始********/
    #if 0
    D:APP第一次运行标志 
    #endif
    EN_MemIndex_APP_INIT_Data = 0, /* D_APP_INIT_Data_Len_4 */
    #if 0
	BOOT第一次运行标志
    #endif
    EN_MemIndex_BOOT_INIT_Data, /* D_BOOT_INIT_Data_Len_4 */
    #if 0
	德尔BOOT版本
    #endif
    EN_MemIndex_DareBootVersion, /* D_DareBootVersion_Len_8 */
    #if 0
	客户BOOT版本
    #endif
    EN_MemIndex_CustomerBootVersion, /* D_CustomerBootVersion_Len_15 */
/********数据块ID_0 定义结束********/

/********数据块ID_1 定义开始********/
    #if 0
	APP有效标志
    #endif
    EN_MemIndex_APP_ValidFlg, /* D_APP_ValidFlg_Len_8 */
    #if 0
	刷写维修日期
    #endif
    EN_MemIndex_FingerPrint_ProgramDate_F199, /* D_FingerPrint_ProgramDate_F199_Len_4 */
    #if 0
	售后维修点代码
    #endif
    EN_MemIndex_FingerPrint_RepairShopCodeF198, /* D_FingerPrint_RepairShopCodeF198_Len_8 */
    #if 0
	BOOT安全访问次数
    #endif
    EN_MemIndex_BOOTUdsSecurityAccessTimes, /* D_BOOTUdsSecurityAccessTimes_Len_1 */
    #if 0
	App安全访问次数
    #endif
    EN_MemIndex_AppUdsSecurityAccessTimes, /* D_AppUdsSecurityAccessTimes_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved0, /* D_Reserved0_Len_1 */
/********数据块ID_1 定义结束********/

/********数据块ID_2 定义开始********/
    #if 0
	升级跳转标志
    #endif
    EN_MemIndex_AppJumpToBootFlg, /* D_AppJumpToBootFlg_Len_1 */
    #if 0
	唤醒源
    #endif
    EN_MemIndex_WakeUpSource, /* D_WakeUpSource_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved1, /* D_Reserved1_Len_1 */
/********数据块ID_2 定义结束********/
    EN_MemIndex_Max
} enSrvMemIndex;



/***写入常用函数声明***/
extern strEepromDataBlockCfgTable * Eel_GetE2DataBlockCfgTablePtr(void);
extern INT16U Srvl_GetE2DataBlockCfgTableLength(void);
extern strEepromDataDefineTable * Eel_GetE2DataDefineTablePtr(void);
extern INT16U Srvl_GetE2DataDefineTableLength(void);
extern void Srvl_SetE2DataBlockOptResult(INT16U DataId, enE2promOptResult Result);
extern enE2promOptResult Srvl_GetE2DataBlockOptResult(INT16U DataId);
extern void Srvl_SetE2DataBlockOptReq(INT16U DataId, EepromOptReq Req);
extern EepromOptReq Srvl_GetE2DataBlockEepOptReq(INT16U DataId);
extern INT8U * Srvl_GetE2DataBlockBufferPtr(INT16U DataId);
extern INT8U Srvl_GetE2DataBlockLength(INT16U DataId);
extern INT32U Srvl_GetE2DataBlockStartAddr(INT16U DataId);
extern INT16U Srvl_GetE2DataBlockBackUpID(INT16U DataId);
extern INT16U Srvl_GetE2DefineDataBlockID(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineLen(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineStartOffset(enSrvMemIndex MemIndex);
extern INT16U Srvl_GetUseDataBlockID(INT16U Index);
extern INT16U Srvl_GetUseDataBlockIDNoBackUp(INT16U Index);

#endif
