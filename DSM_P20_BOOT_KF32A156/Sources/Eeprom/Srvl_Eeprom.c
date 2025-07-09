/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               �ļ���(Srvl_Eeprom.c)
** Created By:              czy
** Created date:            2025-05-29
** Version:                 V1.0
** Descriptions:            eeprom��װ
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
1.����2k���� - 1k���ݣ�ÿ���д448byte-����448byte
2.����4k�ռ�ʵ�ʴ洢2k����
3.������������-����ÿ��1��ʵ�����д100�Ρ�5������
(100/2)*365*5=91250��
4.����д����һ����������15ms
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
* @description: ��ʼ��
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
* @description: ��eepromд����
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

    if(WriteAddr >= EN_SRVL_EEPROM_SECTOR_MAX*EN_EERPROM_SECTOR_NUM_MAX)//����Χ
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
* @description: ��eeprom������
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

    if(ReadAddr >= EN_SRVL_EEPROM_SECTOR_MAX*EN_EERPROM_SECTOR_NUM_MAX)//����Χ
    {
        return FEE_STATUS_PARAM_ERR;
    }

    SetNum = ReadAddr /EN_SRVL_EEPROM_SECTOR_MAX;
    ReadAddrBuf = ReadAddr % EN_SRVL_EEPROM_SECTOR_MAX;
    EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[SetNum].FlashSector,s_Srvl_Eeprom_Conf[SetNum].SectorNum);
    kvStatus = FEE_Read(ReadAddrBuf,DataLength,Buffers);
    return kvStatus;
}



