/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               文件名(Srvl_Eeprom.c)
** Created By:              czy
** Created date:            2025-05-29
** Version:                 V1.0
** Descriptions:            eeprom封装
**
**------------------------------------------------------------------------------------------------
** Modified By:				
** Modified date:			
** Version:					
** Description:				
**
**************************************************************************************************/

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "Srvl_Eeprom.h"
#include "CpuPeripheralInit.h"
#include "fee.h"
#include "EmulatedEE.h"
#include "kflog.h"
#include "Srvl_E2Operate.h"

/*
eeprom:
1.设置2k内容 - 1k数据：每块可写448byte-缓存448byte
2.总需4k空间实际存储2k数据
3.基本满足需求-假设每块1天实际需擦写100次、5年寿命
(100/2)*365*5=91250次
4.单独写操作一块数据所需15ms
*/

#define EN_SRVL_EEPROM_SECTOR_MAX (448U)

const Srvl_Eeprom_ConfType s_Srvl_Eeprom_Conf[EN_EERPROM_SECTOR_NUM_MAX] = 
{
    {0                                                  ,EN_EERPROM_SECTOR_NUM_0,EN_SRVL_EERPROM_SECTOR_0},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_1,EN_EERPROM_SECTOR_NUM_1,EN_SRVL_EERPROM_SECTOR_1},
//    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_2,EN_EERPROM_SECTOR_NUM_2,EN_SRVL_EERPROM_SECTOR_2},
//    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_3,EN_EERPROM_SECTOR_NUM_3,EN_SRVL_EERPROM_SECTOR_3},
//    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_4,EN_EERPROM_SECTOR_NUM_4,EN_SRVL_EERPROM_SECTOR_4},
//    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_5,EN_EERPROM_SECTOR_NUM_5,EN_SRVL_EERPROM_SECTOR_5},
};

/***********************************************************************
* @function name: Srvl_Eeprom_init
* @description: 初始化
* @input parameters: void
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.05.29
***********************************************************************/
void Srvl_Eeprom_init(void)
{
    enEepromSectorNumType SectorNum = EN_EERPROM_SECTOR_NUM_0;

    for(SectorNum = EN_EERPROM_SECTOR_NUM_0; SectorNum < EN_EERPROM_SECTOR_NUM_MAX;SectorNum++)
    {
        EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[SectorNum].FlashSector,SectorNum);
        FEE_Init();
    }
}

/***********************************************************************
* @function name: Srvl_Eeprom_Write
* @description: 对eeprom写数据
* @input parameters: void
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.05.29
***********************************************************************/
FEE_StatusType Srvl_Eeprom_Write(INT32U WriteAddr, INT32U DataLength, const INT32U *Buffers)
{
    INT32U WriteAddrBuf = 0;
    enEepromSectorNumType SetNum = EN_EERPROM_SECTOR_NUM_0;
    FEE_StatusType kvStatus = FEE_STATUS_OK;

    if(WriteAddr >= EN_SRVL_EEPROM_SECTOR_MAX*EN_EERPROM_SECTOR_NUM_MAX)//超范围
    {
        return FEE_STATUS_PARAM_ERR;
    }
    
    SetNum = WriteAddr /EN_SRVL_EEPROM_SECTOR_MAX;
    WriteAddrBuf = WriteAddr % EN_SRVL_EEPROM_SECTOR_MAX;
    EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[SetNum].FlashSector,s_Srvl_Eeprom_Conf[SetNum].SectorNum);
    kvStatus = FEE_Write(WriteAddrBuf,DataLength,Buffers);
    return kvStatus;
}

/***********************************************************************
* @function name: Srvl_Eeprom_Read
* @description: 对eeprom读数据
* @input parameters: void
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.05.29
***********************************************************************/
FEE_StatusType Srvl_Eeprom_Read(INT32U ReadAddr, INT32U DataLength, INT32U *Buffers)
{
    INT32U ReadAddrBuf = 0;
    enEepromSectorNumType SetNum = EN_EERPROM_SECTOR_NUM_0;
    FEE_StatusType kvStatus = FEE_STATUS_OK;

    if(ReadAddr >= EN_SRVL_EEPROM_SECTOR_MAX*EN_EERPROM_SECTOR_NUM_MAX)//超范围
    {
        return FEE_STATUS_PARAM_ERR;
    }

    SetNum = ReadAddr /EN_SRVL_EEPROM_SECTOR_MAX;
    ReadAddrBuf = ReadAddr % EN_SRVL_EEPROM_SECTOR_MAX;
    EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[SetNum].FlashSector,s_Srvl_Eeprom_Conf[SetNum].SectorNum);
    kvStatus = FEE_Read(ReadAddrBuf,DataLength,Buffers);
    return kvStatus;
}



