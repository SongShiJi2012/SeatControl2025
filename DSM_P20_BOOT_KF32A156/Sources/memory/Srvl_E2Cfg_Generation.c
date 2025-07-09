/************************************************************************************************
File created time : 2025-06-04 16:32:11
File Name:          Srvl_E2Cfg_Generation.c
Author:             python Script Generation
Description:        E2数据块配置定义表 - 使用excel表进行管理，不可手动修改
************************************************************************************************/



#include "Srvl_E2Cfg_Generation.h"



INT8U u8MEM_DataBlockID_0[32] = {0};
INT8U u8MEM_DataBlockID_1[24] = {0};
INT8U u8MEM_DataBlockID_2[4] = {0};
INT8U u8MEM_DataBlockID_3[32] = {0};
INT8U u8MEM_DataBlockID_4[32] = {0};
INT8U u8MEM_DataBlockID_5[32] = {0};
INT8U u8MEM_DataBlockID_6[32] = {0};
INT8U u8MEM_DataBlockID_7[32] = {0};
INT8U u8MEM_DataBlockID_8[32] = {0};
INT8U u8MEM_DataBlockID_9[32] = {0};
INT8U u8MEM_DataBlockID_10[32] = {0};
INT8U u8MEM_DataBlockID_11[32] = {0};
INT8U u8MEM_DataBlockID_12[32] = {0};
INT8U u8MEM_DataBlockID_13[32] = {0};
INT8U u8MEM_DataBlockID_14[32] = {0};
INT8U u8MEM_DataBlockID_15[24] = {0};
INT8U u8MEM_DataBlockID_16[4] = {0};
INT8U u8MEM_DataBlockID_17[32] = {0};
INT8U u8MEM_DataBlockID_18[32] = {0};
INT8U u8MEM_DataBlockID_19[32] = {0};
INT8U u8MEM_DataBlockID_20[32] = {0};
INT8U u8MEM_DataBlockID_21[32] = {0};
INT8U u8MEM_DataBlockID_22[32] = {0};
INT8U u8MEM_DataBlockID_23[32] = {0};
INT8U u8MEM_DataBlockID_24[32] = {0};
INT8U u8MEM_DataBlockID_25[32] = {0};
INT8U u8MEM_DataBlockID_26[32] = {0};
INT8U u8MEM_DataBlockID_27[32] = {0};



/* E2数据块配置参数表*/
static strEepromDataBlockCfgTable EepromDataBlockCfgTable[] =
{
/*  数据块ID  起始地址         长度    	 备份ID    RAM变量地址              			       读写请求状态          			     读写操作结果*/
    {0 ,    0x0  ,    32,    14        ,    &u8MEM_DataBlockID_0[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {1 ,    0x20 ,    24,    15        ,    &u8MEM_DataBlockID_1[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {2 ,    0x40 ,    4 ,    16        ,    &u8MEM_DataBlockID_2[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {3 ,    0x60 ,    32,    17        ,    &u8MEM_DataBlockID_3[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {4 ,    0x80 ,    32,    18        ,    &u8MEM_DataBlockID_4[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {5 ,    0xA0 ,    32,    19        ,    &u8MEM_DataBlockID_5[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {6 ,    0xC0 ,    32,    20        ,    &u8MEM_DataBlockID_6[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {7 ,    0xE0 ,    32,    21        ,    &u8MEM_DataBlockID_7[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {8 ,    0x100,    32,    22        ,    &u8MEM_DataBlockID_8[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {9 ,    0x120,    32,    23        ,    &u8MEM_DataBlockID_9[0] ,    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {10,    0x140,    32,    24        ,    &u8MEM_DataBlockID_10[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {11,    0x160,    32,    25        ,    &u8MEM_DataBlockID_11[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {12,    0x180,    32,    26        ,    &u8MEM_DataBlockID_12[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {13,    0x1A0,    32,    27        ,    &u8MEM_DataBlockID_13[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {14,    0x1C0,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_14[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {15,    0x1E0,    24,    D_NOBACKUP,    &u8MEM_DataBlockID_15[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {16,    0x200,    4 ,    D_NOBACKUP,    &u8MEM_DataBlockID_16[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {17,    0x220,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_17[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {18,    0x240,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_18[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {19,    0x260,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_19[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {20,    0x280,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_20[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {21,    0x2A0,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_21[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {22,    0x2C0,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_22[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {23,    0x2E0,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_23[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {24,    0x300,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_24[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {25,    0x320,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_25[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {26,    0x340,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_26[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
    {27,    0x360,    32,    D_NOBACKUP,    &u8MEM_DataBlockID_27[0],    EN_EEPROM_STA_IDLE,    E2promNullOp},
};



/* E2自定义枚举参数表*/
static strEepromDataDefineTable EepromDataDefineTable[] =
{
    /*枚举定义    												开始下标    字节长度     						数据块ID */
    {EN_MemIndex_APP_INIT_Data                 ,    0 ,    D_APP_INIT_Data_Len_4                 ,    0},
    {EN_MemIndex_BOOT_INIT_Data                ,    4 ,    D_BOOT_INIT_Data_Len_4                ,    0},
    {EN_MemIndex_DareBootVersion               ,    8 ,    D_DareBootVersion_Len_8               ,    0},
    {EN_MemIndex_CustomerBootVersion           ,    16,    D_CustomerBootVersion_Len_15          ,    0},

    {EN_MemIndex_APP_ValidFlg                  ,    0 ,    D_APP_ValidFlg_Len_8                  ,    1},
    {EN_MemIndex_FingerPrint_ProgramDate_F199  ,    8 ,    D_FingerPrint_ProgramDate_F199_Len_4  ,    1},
    {EN_MemIndex_FingerPrint_RepairShopCodeF198,    12,    D_FingerPrint_RepairShopCodeF198_Len_8,    1},
    {EN_MemIndex_BOOTUdsSecurityAccessTimes    ,    20,    D_BOOTUdsSecurityAccessTimes_Len_1    ,    1},
    {EN_MemIndex_AppUdsSecurityAccessTimes     ,    21,    D_AppUdsSecurityAccessTimes_Len_1     ,    1},
    {EN_MemIndex_Reserved0                     ,    22,    D_Reserved0_Len_1                     ,    1},

    {EN_MemIndex_AppJumpToBootFlg              ,    0 ,    D_AppJumpToBootFlg_Len_1              ,    2},
    {EN_MemIndex_WakeUpSource                  ,    1 ,    D_WakeUpSource_Len_1                  ,    2},
    {EN_MemIndex_Reserved1                     ,    2 ,    D_Reserved1_Len_1                     ,    2},
};



/* 统计使用的ID数量 包含备份ID */
INT16U UseDataBlockID[D_USEID_NUMBER] = {
0, 14, 1, 15, 2, 16, 
};
/* 统计使用的ID数量 不包含备份ID */
INT16U UseDataBlockIDNoBackup[D_USEID_NUMBER_NO_BACKUP] = {
0, 1, 2, 
};
/***********************************************************************
* @function name: Eel_GetE2DataBlockCfgTablePtr
* @description:  获取数据块配置表地址
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
strEepromDataBlockCfgTable * Eel_GetE2DataBlockCfgTablePtr(void)
{
    return &EepromDataBlockCfgTable[0];
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockCfgTableLength
* @description:  获取数据块配置表配置项长度
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetE2DataBlockCfgTableLength(void)
{
    return (sizeof(EepromDataBlockCfgTable)/sizeof(EepromDataBlockCfgTable[0]));
}

/***********************************************************************
* @function name: Eel_GetE2DataDefineTablePtr
* @description:  获取自定义枚举参数表地址
* @author: python
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
strEepromDataDefineTable * Eel_GetE2DataDefineTablePtr(void)
{
    return &EepromDataDefineTable[0];
}

/***********************************************************************
* @function name: Srvl_GetE2DataDefineTableLength
* @description:  获取自定义枚举参数表长度
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetE2DataDefineTableLength(void)
{
    return (sizeof(EepromDataDefineTable)/sizeof(EepromDataDefineTable[0]));
}

/***********************************************************************
* @function name: Srvl_SetE2DataBlockOptResult
* @description:  设置数据块ID的操作结果
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
void Srvl_SetE2DataBlockOptResult(INT16U DataId, enE2promOptResult Result)
{
    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        EepromDataBlockCfgTable[DataId].OptResult = Result;
    }
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockOptResult
* @description:  获取数据块ID的操作结果
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
enE2promOptResult Srvl_GetE2DataBlockOptResult(INT16U DataId)
{
    enE2promOptResult OptResult = E2promNullOp;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        OptResult = EepromDataBlockCfgTable[DataId].OptResult;
    }

    return OptResult;
}

/***********************************************************************
* @function name: Srvl_SetE2DataBlockEepOptReq
* @description:  设置数据块ID的读写请求
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
void Srvl_SetE2DataBlockOptReq(INT16U DataId, EepromOptReq Req)
{
    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        EepromDataBlockCfgTable[DataId].OptReq = Req;
    }
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockEepOptReq
* @description:  获取数据块ID的读写请求
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
EepromOptReq Srvl_GetE2DataBlockEepOptReq(INT16U DataId)
{
    EepromOptReq OptReq = EN_EEPROM_STA_IDLE;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        OptReq = EepromDataBlockCfgTable[DataId].OptReq;
    }

    return OptReq;
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockBufferPtr
* @description:  获取数据块ID的RAM变量缓存数据地址
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT8U * Srvl_GetE2DataBlockBufferPtr(INT16U DataId)
{
    INT8U * pParaBuffer = NULL;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        pParaBuffer = EepromDataBlockCfgTable[DataId].pParaBuffer;
    }

    return pParaBuffer;
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockLength
* @description:  获取数据块ID的RAM变量配置的长度
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT8U Srvl_GetE2DataBlockLength(INT16U DataId)
{
    INT8U DataLength = 0;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        DataLength = EepromDataBlockCfgTable[DataId].DataLength;
    }

    return DataLength;
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockStartAddr
* @description:  获取数据块ID的起始地址
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT32U Srvl_GetE2DataBlockStartAddr(INT16U DataId)
{
    INT32U StartAddr = 0;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        StartAddr = EepromDataBlockCfgTable[DataId].StartAddr;
    }

    return StartAddr;
}

/***********************************************************************
* @function name: Srvl_GetE2DataBlockBackUpID
* @description:  获取数据块ID的备份ID
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetE2DataBlockBackUpID(INT16U DataId)
{
    INT16U BackUpID = 0;

    if(DataId < Srvl_GetE2DataBlockCfgTableLength())
    {
        BackUpID = EepromDataBlockCfgTable[DataId].BackUpID;
    }

    return BackUpID;
}

/***********************************************************************
* @function name: Srvl_GetE2DefineDataBlockID
* @description:  获取E2定义数据块ID
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetE2DefineDataBlockID(enSrvMemIndex MemIndex)
{
    INT16U DataBlockID = 0;

    if(MemIndex < Srvl_GetE2DataDefineTableLength())
    {
        DataBlockID = EepromDataDefineTable[MemIndex].DataBlockID;
    }

    return DataBlockID;
}

/***********************************************************************
* @function name: Srvl_GetE2DefineLen
* @description:  获取E2定义长度
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT8U Srvl_GetE2DefineLen(enSrvMemIndex MemIndex)
{
    INT8U len = 0;

    if(MemIndex < Srvl_GetE2DataDefineTableLength())
    {
        len = EepromDataDefineTable[MemIndex].len;
    }

    return len;
}

/***********************************************************************
* @function name: Srvl_GetE2DefineStartOffset
* @description:  获取E2定义起始偏移
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT8U Srvl_GetE2DefineStartOffset(enSrvMemIndex MemIndex)
{
    INT8U StartOffset = 0;

    if(MemIndex < Srvl_GetE2DataDefineTableLength())
    {
        StartOffset = EepromDataDefineTable[MemIndex].StartOffset;
    }

    return StartOffset;
}

/***********************************************************************
* @function name: Srvl_GetUseDataBlockID
* @description:  获取使用的数据块ID
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetUseDataBlockID(INT16U Index)
{
    INT16U DataBlockID = 0;

    if(Index < D_USEID_NUMBER)
    {
        DataBlockID = UseDataBlockID[Index];
    }

    return DataBlockID;
}
/***********************************************************************
* @function name: Srvl_GetUseDataBlockIDNoBackUp
* @description:  获取使用的数据块ID 不包含备份ID 
* @author: python Script Generation
* @File created time : 2025-06-04 16:32:11
***********************************************************************/
INT16U Srvl_GetUseDataBlockIDNoBackUp(INT16U Index)
{
    INT16U DataBlockID = 0;

    if(Index < D_USEID_NUMBER_NO_BACKUP)
    {
        DataBlockID = UseDataBlockIDNoBackup[Index];
    }

    return DataBlockID;
}
