/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               prog.c
** Last modified Date:      2017-10-17
** Last Version:            V1.0.0
** Description:
**
**------------------------------------------------------------------------------------------
** Created By:              zyechu
** Created date:            2017-10-17 
** Version:                 V1.0.0
** Descriptions:
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#include "Prog.h"
#include "BootDesc.h"
#include "Output.h"
#include "Bootloader.h"
#include "BootTp.h"
#include "flash_driver.h"

//Bootloader����汾�� F180
const INT8U BootloaderSoftwareVersionNumber[D_CustomerBootVersion_Len_15] =
{'1','1','0','1',0x2D,'D','S','M','P','A','S','B',0x2D,'A','A'};

//Bootloader����汾�� D000
const INT8U DareBootSoftwareVersionNumber[D_DareBootVersion_Len_8] =
{'2','5','0','6','1','3','0','1'};

/*�ж���Ŀe2 �Ƿ��һ������boot ��Ŀ���������һ���ֽ�ȷ��*/
const INT8U E2promInitBootBufDefine[E2PROM_INIT_BOOT_LEN] = {0x5A, 0xA5, 0xAA, DSM_CURRECT_PROJECT};

/*�洢��Eeprom�е�AppCode��Ч�����ݱ�ʶ*/
const INT8U E2promAppCodeValidFlgDefine[D_APP_ValidFlg_Len_8] = {0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A}; // CS = FC
const INT8U E2promAppCodeInvalidFlgDefine[D_APP_ValidFlg_Len_8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*�洢��FLASH�е�AppCode��Ч�����ݱ�ʶ*/
#define     D_AppCodeValidFlgData_Len          (24) /*�洢��FLASH�еļ��AppCode��Ч�Ա�ʶ���ݳ���*/
const INT8U AppCodeValidFlgData[D_AppCodeValidFlgData_Len] =
{
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
};

const INT8U FlashDrvValidFlg[] =
{
	//��������ֵ���ø���FlashDriver���ɵ�Ŀ��������
    0x01,0x60,0x01,0x44,0xD1,0x69,0x00,0x20
};
    
const INT8U	AppFileValidFlg[] =
{
	//��������ֵ���ø���AppCode���ɵ�Ŀ��������
//    0x00,0x70,0x00,0x20,0x11,0x54,0x01,0x00
//		KF32A156����
    0x00,0x00,0x01,0x10//
};

/* crc32 -IEEE 802.3 */
static const  INT32U CRC32TABLE[] =
{
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

BOOL        IsOperateFlash = FALSE; // ��ǰ�Ƿ���дFlash��ʶ
INT32U      ReqDownloadFlashBlock = 0x00; // �������ص�Block��
INT32U      ReqDownloadFlashBlockCnt = 0x00; // ͳ�����ص�Block��


void  Checksum_Crc32_CRCValue(const INT8U *pData, INT32U DataLen)
{
	INT32U TempCRC = u32TempCRCValue;
    while(DataLen --)
    {
        TempCRC = (TempCRC >> 8) ^ CRC32TABLE[(TempCRC ^ (*pData ++)) & 0xFF];
    }
	u32TempCRCValue = TempCRC;
}

void  Checksum_Crc32_CRCAppValue(const INT8U *pData, INT32U DataLen)
{
	INT32U CalCRC = u32CalculateCrc;
	
	while(DataLen --)
	{
		CalCRC = (CalCRC >> 8) ^ CRC32TABLE[(CalCRC ^ (*pData ++)) & 0xFF];	
	}
	u32CalculateCrc = CalCRC;
}


INT32U  Checksum_Crc32(const INT8U *pData, INT32U DataLen)
{
    INT32U CrcValue = 0xFFFFFFFF;
    
    while(DataLen --)
    {
        CrcValue = (CrcValue >> 8) ^ CRC32TABLE[(CrcValue ^ (*pData ++)) & 0xFF];
    }
    
    return (~ CrcValue);
}

INT32U  Checksum_Crc32_FarAddr(INT32U DataAddr, INT32U DataLen)
{
    INT16U  Index = 0;
    INT32U  CrcValue = 0xFFFFFFFF;

    for(Index = 0; Index < DataLen; Index ++)
    {
        CrcValue = (CrcValue >> 8) ^ CRC32TABLE[(CrcValue ^ (*(INT8U *)(DataAddr + Index))) & 0xFF];
    }
    
    return (~ CrcValue);
}

/*******************************************************************************
* �������ƣ�Prog_Init
* ���������������ص�һЩ������ʼ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 
*******************************************************************************/
void    Prog_Init(void)
{
    FlashEraseInfo.StartAddr = 0;
    FlashEraseInfo.EraseLen = 0;
    FlashEraseInfo.RetryCnt = 0;
    FlashEraseInfo.StartEraseFlg = 0; // ��������Flash��ʶ
    FlashEraseInfo.EraseSuccessFlg = 0; // Flash�����Ƿ�ok
    FlashEraseInfo.FlashBlockIndex = 0;
    FlashEraseInfo.EraseFlashRespProcess = NULL;


    DownloadInfo.SectorMaxLen = 0; // ��¼�����󳤶�, ���ݴ������ʼ��ַ��ȡ
    DownloadInfo.FileStartAddr = 0; // AppCode�ļ�����ʼ��ַ
    DownloadInfo.FileDataLen = 0; // ��һ��FlashDrv��AppCode�ļ����ݴ�С, ��FF00 �����������ʱ��ȡ��
    DownloadInfo.FileSurplusDataLen = 0; // ������һ��FlashDrv��AppCode�ļ�ʣ����������ݴ�С    
    DownloadInfo.BlockDataLen = 0; // ������ļ�����, 34����ʱ��ȡ��
    DownloadInfo.BlockSurplusDataLen = 0; // ʣ������ݳ���
    DownloadInfo.CurrentDataLen = 0; // ��ǰ36����һ�δ�������ݳ���
    DownloadInfo.FileLogicStartAddr = 0; // �ļ�����ʼ��ַ,  34����ʱ��ȡ��, �߼���ַ
    DownloadInfo.FileGlobalStartAddr = 0; // �ļ�����ʼ��ַ,  34����ʱ��ȡ��, ȫ�ֵ�ַ
    DownloadInfo.CurrentLogicAddr = 0; // ��ǰ36����һ�δ������ʼ��ַ, ��Ҫÿ���ۼӼ���, �߼���ַ
    DownloadInfo.CurrentGlobalAddr = 0; // �߼���ַ ���ڵ� ȫ�ֵ�ַ
    DownloadInfo.CurrentSequenceCnt = 0; // 36�������ݴ�������к�, ����36�������п���
    DownloadInfo.ExpectedSequenceCnt = 0; // 36�������ݴ�������������к�, ����36�������п���
    DownloadInfo.SameBlockRetryTimesCnt = 0; // 36������ͬ���ݴ���鳢�Դ���Ĵ���, ���3��    
}

/*******************************************************************************
* �������ƣ�GetGlobalAddr
* ������������ȡȫ�ֵ�ַ
* ��ڲ����������AppCode�߼���ַ
* ���ڲ�������
* �� �� ֵ��ȫ�ֵ�ַ
* ��    ע: 
*******************************************************************************/
INT32U    GetGlobalAddr(INT32U  LogicAddr)
{
    INT32U  GlobalAddr = 0x00;

	GlobalAddr=LogicAddr;
    return (GlobalAddr);
}

/*******************************************************************************
* �������ƣ�CheckAppCodeSectorStartAddr
* ������������鴫���AppCode��ʼ��ַ�Ƿ���ȷ
* ��ڲ����������AppCode�߼���ַ
* ���ڲ�������
* �� �� ֵ��TRUE : �����AppCode�߼���ַ��ȷ; FALSE : �����AppCode�߼���ַ����ȷ; 
* ��    ע: 
*******************************************************************************/
BOOL    CheckAppCodeSectorStartAddr(INT32U  LogicAddr)
{
    INT8U   ret = FALSE;
    
	/*��ַsector����,��ַ��Χ��AppCode��Χ��*/
    if(((LogicAddr & (D_FlashOneSector_Len-1u))==0u)&&\
    (LogicAddr>=D_AppCodeStart_Addr)&&(LogicAddr<D_AppCodeEnd_Addr))
    {
    	ret=TRUE;
    }
    return (ret);
}

/*******************************************************************************
* �������ƣ�GetAppCodeSectorMaxLen
* �������������ݴ�������ʼ��ַ��ȡ��ǰSector����󳤶�
* ��ڲ����������AppCode�߼���ַ
* ���ڲ�������
* �� �� ֵ����ǰSector����󳤶�
* ��    ע: 
*******************************************************************************/
INT32U  GetAppCodeSectorMaxLen(INT32U  LogicStartAddr)
{
    INT32U  ret = 0x00;
    INT32U  GlobalAddr = 0x00;

	/*S32K144 FLASH sector�̶�Ϊ4k=4096bytes*/
    ret=D_FlashOneSector_Len;
    return (ret);    
}

/*******************************************************************************
* �������ƣ�GetAppCodeBlockIndex
* �������������ݴ�������ʼ��ַ��ȡ��ǰBlock������
* ��ڲ����������block start�߼���ַ
* ���ڲ�������
* �� �� ֵ����ǰblock����󳤶�
* ��    ע: 
*******************************************************************************/
INT32U  GetAppCodeBlockIndex(INT32U  LogicStartAddr)
{
    INT32U  ret = 0x00;

	if((LogicStartAddr>=D_AppCodeStart_Addr)&&(LogicStartAddr<D_AppCodeEnd_Addr))
	{
		if((LogicStartAddr & (FEATURE_FLS_PF_BLOCK_SECTOR_SIZE-1u))==0u)
		{
			ret=LogicStartAddr/FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
		}
	}

    return (ret);    
}

/*******************************************************************************
* �������ƣ�WriteFlashDrvToRam
* ����������дFlashDrv��Ram
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 
*******************************************************************************/
INT8U    Prog_WriteFlashDrvToRam(void)
{
    INT16U  Index = 0;
    INT16U  tCurrentDataLen = 0;
    INT8U  *pSourceData = NULL; // ����Դ
    INT8U  *pTargetData = NULL; // Ŀ������

    IsOperateFlash = TRUE;

    tCurrentDataLen = DownloadInfo.CurrentDataLen;// ��ȡ��ǰ�����ݳ���
    pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[2]; // ��ȡ��ǰ�����ݵĵ�ַ
    pTargetData = (INT8U*)DownloadInfo.CurrentLogicAddr; // ��ȡĿ�����ݵĵ�ַ
	Checksum_Crc32_CRCValue(pSourceData, tCurrentDataLen);

    if( (tCurrentDataLen > DownloadInfo.BlockSurplusDataLen) || \
    (tCurrentDataLen > DownloadInfo.SectorMaxLen) || (0u == DownloadInfo.BlockSurplusDataLen) )
    {
        return (PROG_REQ_PARERR);
    }

    // ��FlashDrv����copy��Ram��
    for(Index = 0; Index < tCurrentDataLen; Index ++)
    {
        *pTargetData = *pSourceData;
        pSourceData ++;
        pTargetData ++;
    }

    Output_FeedWatchDog();
    Boot_DisableInterrupts;

    // ��RAM�ж�ȡд��������Ժ�һ��
    tCurrentDataLen = DownloadInfo.CurrentDataLen;// ��ȡ��ǰ�����ݳ���
    pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[2]; // ��ȡ��ǰ�����ݵĵ�ַ
    pTargetData = (INT8U*)DownloadInfo.CurrentLogicAddr; // ��ȡĿ�����ݵĵ�ַ
    
    for(Index = 0; Index < tCurrentDataLen; Index ++)
    {
        if(*pTargetData != *pSourceData)
        {
            return (PROG_REQ_PARERR);
        }
        pSourceData ++;
        pTargetData ++;
    }

    Boot_EnableInterrupts;
    Output_FeedWatchDog();
    
    DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen; // ����ʣ������ݳ���
    DownloadInfo.CurrentLogicAddr = DownloadInfo.CurrentLogicAddr + DownloadInfo.CurrentDataLen; // ���µ�ǰ����ʼ��ַ

    IsOperateFlash = FALSE;
    return (PROG_REQ_OK);
}

/*******************************************************************************
* �������ƣ�Prog_WriteAppCodeToRom
* ����������дAppCode��Rom
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 
*******************************************************************************/
INT8U   Prog_WriteAppCodeToRom(INT16U rDataNum)
{
	INT16U	Index = 0;
	INT16U	tCurrentDataLen = 0;
	INT8U  *pSourceData = NULL; // ����Դ
	INT16U i=0,j=0,k=0,ParmCurrentDataLen=0;

	IsOperateFlash = TRUE;

	tCurrentDataLen = DownloadInfo.CurrentDataLen;// ��ȡ��ǰ�����ݳ���
	pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[rDataNum]; // ��ȡ��ǰ�����ݵĵ�ַ

	if( (tCurrentDataLen > DownloadInfo.BlockSurplusDataLen) || \
	(tCurrentDataLen > DownloadInfo.SectorMaxLen) || (0u == DownloadInfo.BlockSurplusDataLen))
	{
		return (PROG_REQ_PARERR);
	}
	if((tCurrentDataLen & (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE - 1U)) != 0U)
	{
		i=tCurrentDataLen/FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
		j=tCurrentDataLen%FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
		for(k=0;k<(FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE-j);k++)
		{
			pSourceData[i*FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE+j+k]=0xFF;
		}

		ParmCurrentDataLen=tCurrentDataLen+(FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE-j);
	}
	else
	{
		ParmCurrentDataLen=tCurrentDataLen;
	}

	Output_FeedWatchDog();
	Boot_DisableInterrupts;
	
	// ��AppCodeд��Flash
	
	localProgFlashParm.length = ParmCurrentDataLen;// ��ȡ��ǰ�����ݳ���
	localProgFlashParm.data = pSourceData; // ��ȡ��ǰ�����ݵĵ�ַ
	localProgFlashParm.address = DownloadInfo.CurrentGlobalAddr; // ��ȡĿ�����ݵĵ�ַ
#if 0
	if(pFlshBufHead != NULL)
	{
		pFlshBufHead->flashWriteFct(&localProgFlashParm);

		if(STATUS_SUCCESS != localProgFlashParm.errorCode)
		{
			return (PROG_REQ_PARERR);
		}
	}
	else
	{
		return (PROG_REQ_PARERR);
	}
#endif
	localProgFlashParm.errorCode=FLASH_DRV_Program(\
	&localProgFlashParm.flashSSDConfig,localProgFlashParm.address,localProgFlashParm.length,localProgFlashParm.data);

	Output_FeedWatchDog();
#if 0   /*�����flash״̬*/
	// ���Flash�����Ƿ����
	if(0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK)) // Flash�Ƿ����
	{
		Index = 1000;
		while(Index)
		{
			Index --;
		}
		if(0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK)) // ��ʱһ��ʱ���ټ��
		{
			return (PROG_REQ_PARERR);
		}
	}
#endif
	// ��Flash�ж�ȡ���� ���� д������ݱȽ�
	for(Index = 0; Index < tCurrentDataLen; Index ++)
	{
		if(*pSourceData ++ != *(INT8U *)(DownloadInfo.CurrentLogicAddr + Index)) // ��ȡFlashʱ, ʹ�õ����߼���ַ
		{
			return (PROG_REQ_PARERR);
		}
	}

	Boot_EnableInterrupts;
	Output_FeedWatchDog();
	
	//����ǰ�����CRC������������CRC��������̫��ʱ��̫�� 20180926 michael
	//---START
	tCurrentDataLen = DownloadInfo.CurrentDataLen;// ��ȡ��ǰ�����ݳ���
	pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[rDataNum]; // ��ȡ��ǰ�����ݵĵ�ַ

	Checksum_Crc32_CRCValue(pSourceData, tCurrentDataLen);
	Checksum_Crc32_CRCAppValue(pSourceData, tCurrentDataLen);
	//---END

	
	DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen; // ����ʣ������ݳ���
	DownloadInfo.CurrentLogicAddr = DownloadInfo.CurrentLogicAddr + DownloadInfo.CurrentDataLen; // ���µ�ǰ����ʼ��ַ
	DownloadInfo.CurrentGlobalAddr = GetGlobalAddr(DownloadInfo.CurrentLogicAddr);
	
	IsOperateFlash = FALSE;
	return (PROG_REQ_OK);	 
}


/*******************************************************************************
* �������ƣ�CheeckFlashDrvIsValid
* ��������������������ص�Flash Drv�ļ��Ƿ�����Ч��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��Flash Drv�ļ��Ƿ���Ч
* ��    ע: 
*******************************************************************************/
BOOL    CheeckFlashDrvIsValid(void)
{
    INT8U   Index = 0;
    const   INT8U   * pFlashDrvValidFlg = NULL;

    pFlashDrvValidFlg = (const INT8U *)&BootTpRxInfoStruct.cDataBuf[2];
    for(Index = 0; Index < sizeof(FlashDrvValidFlg); Index ++)
    {
        if(*pFlashDrvValidFlg ++ != FlashDrvValidFlg[Index])
        {
            return  (FALSE);
        }
    }

    return  (TRUE);
}

/*******************************************************************************
* �������ƣ�CheeckAppFileIsValid
* ��������������������ص�App�ļ��Ƿ�����Ч��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��App�ļ��Ƿ���Ч - оƬ���� - �����ļ�ǰ4���ֽ�Ϊ�̶�ֵ
* ��    ע: 
*******************************************************************************/
BOOL    CheeckAppFileIsValid(void)
{
    INT8U   Index = 0;
    const   INT8U   * pAppFileValidFlg = NULL;

    pAppFileValidFlg = (const INT8U *)&BootTpRxInfoStruct.cDataBuf[2];
    for(Index = 0; Index < sizeof(AppFileValidFlg); Index ++)
    {
        if(*pAppFileValidFlg ++ != AppFileValidFlg[Index])
        {
            return  (FALSE);
        }
    }

    return  (TRUE);
}

/*******************************************************************************
* �������ƣ�CheckAppCoeValidFlg
* �������������AppCode��Ч�Ա�ʶ
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��AppCode�Ƿ���Ч
* ��    ע: 
*******************************************************************************/
BOOL    CheckAppCoeValidFlg(void)
{
    INT8U   Index = 0;
    const   INT8U   * pAppCodeFlag = NULL;
#if 0
    pAppCodeFlag = (const INT8U *)D_AppCodeFlg_StartAddr;
    for(Index = 0; Index < D_AppCodeValidFlgData_Len; Index ++)
    {
        if(*(INT8U *)(pAppCodeFlag ++) != AppCodeValidFlgData[Index])
        {
            return  (FALSE);
        }
    }
#endif
    return  (TRUE);
}

/*******************************************************************************
* �������ƣ�CheckE2promAppCoeValidFlg
* �������������E2promAppCodeValidFlg��Ч��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��E2promAppCodeValidFlg�Ƿ���Ч
* ��    ע: 
*******************************************************************************/
BOOL    CheckE2promAppCoeValidFlg(void)
{
    INT8U   Index = 0;
    INT8U TempBuf[D_APP_ValidFlg_Len_8];

    Srvl_ReadMemIndexData(EN_MemIndex_APP_ValidFlg, TempBuf, D_APP_ValidFlg_Len_8);
    for(Index = 0; Index < D_APP_ValidFlg_Len_8; Index ++)
    {
        if(TempBuf[Index] != E2promAppCodeValidFlgDefine[Index])
        {
            return  (FALSE);
        }
    }
    
    return  (TRUE);
}

