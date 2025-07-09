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
#include "Srvl_CanSignals.h"

/*
eeprom:
1.����2k���� - 1k���ݣ�ÿ���д448byte-����448byte
2.����4k�ռ�ʵ�ʴ洢2k����
3.������������-����ÿ��1��ʵ�����д100�Ρ�5������
(100/2)*365*5=91250��
4.����д����һ����������15ms
*/

#define EN_SRVL_EEPROM_SECTOR_MAX (448U)
#define EN_SRVL_EEPROM_ALIGNMENT_SIZE (4U)  // 4�ֽڶ���

const Srvl_Eeprom_ConfType s_Srvl_Eeprom_Conf[EN_EERPROM_SECTOR_NUM_MAX] = 
{
    {0                                                  ,EN_EERPROM_SECTOR_NUM_0,EN_SRVL_EERPROM_SECTOR_0},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_1,EN_EERPROM_SECTOR_NUM_1,EN_SRVL_EERPROM_SECTOR_1},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_2,EN_EERPROM_SECTOR_NUM_2,EN_SRVL_EERPROM_SECTOR_2},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_3,EN_EERPROM_SECTOR_NUM_3,EN_SRVL_EERPROM_SECTOR_3},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_4,EN_EERPROM_SECTOR_NUM_4,EN_SRVL_EERPROM_SECTOR_4},
    {EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_5,EN_EERPROM_SECTOR_NUM_5,EN_SRVL_EERPROM_SECTOR_5},
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
    FEE_StatusType kvStatus = FEE_STATUS_OK;
    INT32U remainingLength = DataLength;
    const INT32U *currentBuffer = Buffers;

    enEepromSectorNumType currentSetNum;
    INT32U sectorOffset,maxWriteLen,chunkSize;
    
    // ����ַ�����ݳ����Ƿ�4�ֽڶ���
    if((WriteAddr & (EN_SRVL_EEPROM_ALIGNMENT_SIZE - 1)) != 0 
    || (DataLength & (EN_SRVL_EEPROM_ALIGNMENT_SIZE - 1)) != 0) 
    {
        return FEE_STATUS_ALIGNMENT;
    }
    while (remainingLength > 0) 
    {
        // ���㵱ǰ������������ƫ��
        currentSetNum = WriteAddr / EN_SRVL_EEPROM_SECTOR_MAX;
        sectorOffset = WriteAddr % EN_SRVL_EEPROM_SECTOR_MAX;
        maxWriteLen = EN_SRVL_EEPROM_SECTOR_MAX - sectorOffset;
        chunkSize = (remainingLength <= maxWriteLen) ? remainingLength : maxWriteLen;

        // ����������Ƿ���Ч
        if (currentSetNum >= EN_EERPROM_SECTOR_NUM_MAX) {return FEE_STATUS_ADDR_ERR;}

        // ���õ�ǰ����
        EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[currentSetNum].FlashSector,
            s_Srvl_Eeprom_Conf[currentSetNum].SectorNum);
        
        // д������
        kvStatus = FEE_Write(sectorOffset, chunkSize, currentBuffer);
        if (kvStatus != FEE_STATUS_OK) {return kvStatus;}

        // ����ƫ�ƺͳ���
        WriteAddr += chunkSize;
        currentBuffer += chunkSize / sizeof(INT32U); // �ƽ�������ָ��
        if(remainingLength >= chunkSize){remainingLength -= chunkSize;}
         else {return FEE_STATUS_PARAM_ERR;}//Ԥ���쳣��ѭ��
    }
    
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
    FEE_StatusType kvStatus = FEE_STATUS_OK;
    INT32U remainingLength = DataLength;
    INT32U *currentBuffer = Buffers;
    enEepromSectorNumType currentSetNum;
    INT32U sectorOffset,maxReadLen,chunkSize;
    
    // ����ַ�����ݳ����Ƿ�4�ֽڶ���
    if((ReadAddr & (EN_SRVL_EEPROM_ALIGNMENT_SIZE - 1)) != 0 
    || (DataLength & (EN_SRVL_EEPROM_ALIGNMENT_SIZE - 1)) != 0) 
    {
        return FEE_STATUS_ALIGNMENT;
    }
    
    // ����ַ��Χ�Ƿ���Ч
    if(ReadAddr >= EN_SRVL_EEPROM_SECTOR_MAX * EN_EERPROM_SECTOR_NUM_MAX) 
    {
        return FEE_STATUS_ADDR_ERR;
    }
    
    while (remainingLength > 0) 
    {
        // ���㵱ǰ������������ƫ��
        currentSetNum = ReadAddr / EN_SRVL_EEPROM_SECTOR_MAX;
        sectorOffset = ReadAddr % EN_SRVL_EEPROM_SECTOR_MAX;
        
        maxReadLen = EN_SRVL_EEPROM_SECTOR_MAX - sectorOffset;
        chunkSize = (remainingLength <= maxReadLen) ? remainingLength : maxReadLen;
        
        // ����������Ƿ���Ч
        if (currentSetNum >= EN_EERPROM_SECTOR_NUM_MAX) 
        {
            return FEE_STATUS_ADDR_ERR;
        }

        // ���õ�ǰ����
        EmulatedEE_SetSector(s_Srvl_Eeprom_Conf[currentSetNum].FlashSector, 
                            s_Srvl_Eeprom_Conf[currentSetNum].SectorNum);
        
        // ��ȡ����
        kvStatus = FEE_Read(sectorOffset, chunkSize, currentBuffer);
        if (kvStatus != FEE_STATUS_OK) { return kvStatus;}

        // ����ƫ�ƺͳ��ȣ���4�ֽڵ�λ�ƽ���
        ReadAddr += chunkSize;
        currentBuffer += (chunkSize / sizeof(INT32U));  // �����ƽ�ָ��
        if(remainingLength >= chunkSize){remainingLength -= chunkSize;}
         else {return FEE_STATUS_PARAM_ERR;}//Ԥ���쳣��ѭ��
    }
    
    return kvStatus;
}

INT32U TestWriteAddr = 0;
INT32U TestWriteLength = 4;
INT32U TestWriteData[2] = {0};
INT8U TestWriteDatab8[8] = {0};
INT32U TestReadData[2] = {0};
INT32U TestWriteFlg = 2000;
INT8U TestWriteResult = 0;
INT8U TestReadResult = 0;
void Srvl_Eeprom_Test(void)
{
    INT32U i = 0;
    INT32U buff = 0;
    INT8U RxBuf = 0;
    static INT8U RxBufff = 0;
//    for(i = 0; i < TestWriteLength; i+=4)
//    {
//        TestWriteData[i/4] = ((i/4)<< 24) | ((i/4)<<16) | ((i/4)<<8) | ((i/4)<<0);
//    }
    //16.38ms
    if(TestWriteFlg < 448)
    {
        TestWriteFlg += 4;
        buff = TestWriteFlg;
        TestWriteData[0] = ((buff/4)<< 24) | ((buff/4)<<16) | ((buff/4)<<8) | ((buff/4)<<0);
        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        TestWriteResult = Srvl_Eeprom_Write(TestWriteAddr, TestWriteLength, (const INT32U *)TestWriteData);//9.4ms //17.2ms  //��ҳʱ�� 53.3ms
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);
        kf_printf("WW:%d 0x%x",TestWriteAddr,TestWriteData[0]);
        TestWriteAddr+=4;
    }
    RxBuf = CanRx_0x367_IVI_NapMode_SwtichSet();
    //if(TestWriteFlg ==1001)
    if(RxBuf != RxBufff)
    {
        RxBufff = RxBuf;
       // TestWriteFlg = 504;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Height,TestWriteData[0]);
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Length,TestWriteData[1]);
        //TestWriteResult = Srvl_Eeprom_Write(TestWriteAddr,TestWriteLength,TestWriteDatab8);//9.4ms //17.2ms  //��ҳʱ�� 53.3ms
        kf_printf("WW:%d 0x%x",TestWriteAddr,TestWriteData[0]);
    }

    
    TestReadData[0]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Height);
    TestReadData[1]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Length);
    if(TestWriteFlg == 1000)
    {
        TestWriteFlg = 504;
        PINS_DRV_WritePin(GPIOD_SFR,13U,0);
        TestReadResult = Srvl_Eeprom_Read(TestWriteAddr, TestWriteLength, (INT32U *)TestReadData);
        PINS_DRV_WritePin(GPIOD_SFR,13U,1);
        kf_printf("DD:0x%x 0x%x",TestReadData[0],TestReadData[1]);
    }
}


