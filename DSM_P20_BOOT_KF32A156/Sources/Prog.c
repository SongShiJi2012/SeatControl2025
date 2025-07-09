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

//Bootloader软件版本号 F180
const INT8U BootloaderSoftwareVersionNumber[D_CustomerBootVersion_Len_15] =
{'1','1','0','1',0x2D,'D','S','M','P','A','S','B',0x2D,'A','A'};

//Bootloader软件版本号 D000
const INT8U DareBootSoftwareVersionNumber[D_DareBootVersion_Len_8] =
{'2','5','0','6','1','3','0','1'};

/*判断项目e2 是否第一次下载boot 项目区别由最后一个字节确定*/
const INT8U E2promInitBootBufDefine[E2PROM_INIT_BOOT_LEN] = {0x5A, 0xA5, 0xAA, DSM_CURRECT_PROJECT};

/*存储于Eeprom中的AppCode有效性数据标识*/
const INT8U E2promAppCodeValidFlgDefine[D_APP_ValidFlg_Len_8] = {0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A}; // CS = FC
const INT8U E2promAppCodeInvalidFlgDefine[D_APP_ValidFlg_Len_8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*存储于FLASH中的AppCode有效性数据标识*/
#define     D_AppCodeValidFlgData_Len          (24) /*存储于FLASH中的检查AppCode有效性标识数据长度*/
const INT8U AppCodeValidFlgData[D_AppCodeValidFlgData_Len] =
{
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
};

const INT8U FlashDrvValidFlg[] =
{
	//这个数组的值，得根据FlashDriver生成的目标代码更改
    0x01,0x60,0x01,0x44,0xD1,0x69,0x00,0x20
};
    
const INT8U	AppFileValidFlg[] =
{
	//这个数组的值，得根据AppCode生成的目标代码更改
//    0x00,0x70,0x00,0x20,0x11,0x54,0x01,0x00
//		KF32A156特性
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

BOOL        IsOperateFlash = FALSE; // 当前是否在写Flash标识
INT32U      ReqDownloadFlashBlock = 0x00; // 请求下载的Block数
INT32U      ReqDownloadFlashBlockCnt = 0x00; // 统计下载的Block数


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
* 函数名称：Prog_Init
* 功能描述：编程相关的一些变量初始化
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 
*******************************************************************************/
void    Prog_Init(void)
{
    FlashEraseInfo.StartAddr = 0;
    FlashEraseInfo.EraseLen = 0;
    FlashEraseInfo.RetryCnt = 0;
    FlashEraseInfo.StartEraseFlg = 0; // 启动擦除Flash标识
    FlashEraseInfo.EraseSuccessFlg = 0; // Flash擦除是否ok
    FlashEraseInfo.FlashBlockIndex = 0;
    FlashEraseInfo.EraseFlashRespProcess = NULL;


    DownloadInfo.SectorMaxLen = 0; // 记录块的最大长度, 根据传输的起始地址获取
    DownloadInfo.FileStartAddr = 0; // AppCode文件的起始地址
    DownloadInfo.FileDataLen = 0; // 整一个FlashDrv或AppCode文件数据大小, 在FF00 擦除命令服务时获取到
    DownloadInfo.FileSurplusDataLen = 0; // 计算整一个FlashDrv或AppCode文件剩余待传输数据大小    
    DownloadInfo.BlockDataLen = 0; // 传输的文件长度, 34服务时获取到
    DownloadInfo.BlockSurplusDataLen = 0; // 剩余的数据长度
    DownloadInfo.CurrentDataLen = 0; // 当前36服务一次传输的数据长度
    DownloadInfo.FileLogicStartAddr = 0; // 文件的起始地址,  34服务时获取到, 逻辑地址
    DownloadInfo.FileGlobalStartAddr = 0; // 文件的起始地址,  34服务时获取到, 全局地址
    DownloadInfo.CurrentLogicAddr = 0; // 当前36服务一次传输的起始地址, 需要每次累加计算, 逻辑地址
    DownloadInfo.CurrentGlobalAddr = 0; // 逻辑地址 对于的 全局地址
    DownloadInfo.CurrentSequenceCnt = 0; // 36服务数据传输块序列号, 用于36服务序列控制
    DownloadInfo.ExpectedSequenceCnt = 0; // 36服务数据传输块期望的序列号, 用于36服务序列控制
    DownloadInfo.SameBlockRetryTimesCnt = 0; // 36服务相同数据传输块尝试传输的次数, 最多3次    
}

/*******************************************************************************
* 函数名称：GetGlobalAddr
* 功能描述：获取全局地址
* 入口参数：传输的AppCode逻辑地址
* 出口参数：无
* 返 回 值：全局地址
* 备    注: 
*******************************************************************************/
INT32U    GetGlobalAddr(INT32U  LogicAddr)
{
    INT32U  GlobalAddr = 0x00;

	GlobalAddr=LogicAddr;
    return (GlobalAddr);
}

/*******************************************************************************
* 函数名称：CheckAppCodeSectorStartAddr
* 功能描述：检查传输的AppCode起始地址是否正确
* 入口参数：传输的AppCode逻辑地址
* 出口参数：无
* 返 回 值：TRUE : 传输的AppCode逻辑地址正确; FALSE : 传输的AppCode逻辑地址不正确; 
* 备    注: 
*******************************************************************************/
BOOL    CheckAppCodeSectorStartAddr(INT32U  LogicAddr)
{
    INT8U   ret = FALSE;
    
	/*地址sector对齐,地址范围在AppCode范围内*/
    if(((LogicAddr & (D_FlashOneSector_Len-1u))==0u)&&\
    (LogicAddr>=D_AppCodeStart_Addr)&&(LogicAddr<D_AppCodeEnd_Addr))
    {
    	ret=TRUE;
    }
    return (ret);
}

/*******************************************************************************
* 函数名称：GetAppCodeSectorMaxLen
* 功能描述：根据传输块的起始地址获取当前Sector的最大长度
* 入口参数：传输的AppCode逻辑地址
* 出口参数：无
* 返 回 值：当前Sector的最大长度
* 备    注: 
*******************************************************************************/
INT32U  GetAppCodeSectorMaxLen(INT32U  LogicStartAddr)
{
    INT32U  ret = 0x00;
    INT32U  GlobalAddr = 0x00;

	/*S32K144 FLASH sector固定为4k=4096bytes*/
    ret=D_FlashOneSector_Len;
    return (ret);    
}

/*******************************************************************************
* 函数名称：GetAppCodeBlockIndex
* 功能描述：根据传输块的起始地址获取当前Block的索引
* 入口参数：传输的block start逻辑地址
* 出口参数：无
* 返 回 值：当前block的最大长度
* 备    注: 
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
* 函数名称：WriteFlashDrvToRam
* 功能描述：写FlashDrv到Ram
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 
*******************************************************************************/
INT8U    Prog_WriteFlashDrvToRam(void)
{
    INT16U  Index = 0;
    INT16U  tCurrentDataLen = 0;
    INT8U  *pSourceData = NULL; // 数据源
    INT8U  *pTargetData = NULL; // 目标数据

    IsOperateFlash = TRUE;

    tCurrentDataLen = DownloadInfo.CurrentDataLen;// 获取当前的数据长度
    pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[2]; // 获取当前的数据的地址
    pTargetData = (INT8U*)DownloadInfo.CurrentLogicAddr; // 获取目标数据的地址
	Checksum_Crc32_CRCValue(pSourceData, tCurrentDataLen);

    if( (tCurrentDataLen > DownloadInfo.BlockSurplusDataLen) || \
    (tCurrentDataLen > DownloadInfo.SectorMaxLen) || (0u == DownloadInfo.BlockSurplusDataLen) )
    {
        return (PROG_REQ_PARERR);
    }

    // 把FlashDrv数据copy到Ram中
    for(Index = 0; Index < tCurrentDataLen; Index ++)
    {
        *pTargetData = *pSourceData;
        pSourceData ++;
        pTargetData ++;
    }

    Output_FeedWatchDog();
    Boot_DisableInterrupts;

    // 从RAM中读取写入的数据以后一致
    tCurrentDataLen = DownloadInfo.CurrentDataLen;// 获取当前的数据长度
    pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[2]; // 获取当前的数据的地址
    pTargetData = (INT8U*)DownloadInfo.CurrentLogicAddr; // 获取目标数据的地址
    
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
    
    DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen; // 更新剩余的数据长度
    DownloadInfo.CurrentLogicAddr = DownloadInfo.CurrentLogicAddr + DownloadInfo.CurrentDataLen; // 更新当前的起始地址

    IsOperateFlash = FALSE;
    return (PROG_REQ_OK);
}

/*******************************************************************************
* 函数名称：Prog_WriteAppCodeToRom
* 功能描述：写AppCode到Rom
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 
*******************************************************************************/
INT8U   Prog_WriteAppCodeToRom(INT16U rDataNum)
{
	INT16U	Index = 0;
	INT16U	tCurrentDataLen = 0;
	INT8U  *pSourceData = NULL; // 数据源
	INT16U i=0,j=0,k=0,ParmCurrentDataLen=0;

	IsOperateFlash = TRUE;

	tCurrentDataLen = DownloadInfo.CurrentDataLen;// 获取当前的数据长度
	pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[rDataNum]; // 获取当前的数据的地址

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
	
	// 把AppCode写到Flash
	
	localProgFlashParm.length = ParmCurrentDataLen;// 获取当前的数据长度
	localProgFlashParm.data = pSourceData; // 获取当前的数据的地址
	localProgFlashParm.address = DownloadInfo.CurrentGlobalAddr; // 获取目标数据的地址
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
#if 0   /*不检查flash状态*/
	// 检查Flash操作是否空闲
	if(0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK)) // Flash是否空闲
	{
		Index = 1000;
		while(Index)
		{
			Index --;
		}
		if(0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK)) // 延时一段时间再检查
		{
			return (PROG_REQ_PARERR);
		}
	}
#endif
	// 从Flash中读取数据 并与 写入的数据比较
	for(Index = 0; Index < tCurrentDataLen; Index ++)
	{
		if(*pSourceData ++ != *(INT8U *)(DownloadInfo.CurrentLogicAddr + Index)) // 读取Flash时, 使用的是逻辑地址
		{
			return (PROG_REQ_PARERR);
		}
	}

	Boot_EnableInterrupts;
	Output_FeedWatchDog();
	
	//先提前计算好CRC，否则最后计算CRC的运算量太大，时间太久 20180926 michael
	//---START
	tCurrentDataLen = DownloadInfo.CurrentDataLen;// 获取当前的数据长度
	pSourceData = (INT8U*)&BootTpRxInfoStruct.cDataBuf[rDataNum]; // 获取当前的数据的地址

	Checksum_Crc32_CRCValue(pSourceData, tCurrentDataLen);
	Checksum_Crc32_CRCAppValue(pSourceData, tCurrentDataLen);
	//---END

	
	DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen; // 更新剩余的数据长度
	DownloadInfo.CurrentLogicAddr = DownloadInfo.CurrentLogicAddr + DownloadInfo.CurrentDataLen; // 更新当前的起始地址
	DownloadInfo.CurrentGlobalAddr = GetGlobalAddr(DownloadInfo.CurrentLogicAddr);
	
	IsOperateFlash = FALSE;
	return (PROG_REQ_OK);	 
}


/*******************************************************************************
* 函数名称：CheeckFlashDrvIsValid
* 功能描述：检查请求下载的Flash Drv文件是否是有效的
* 入口参数：
* 出口参数：
* 返 回 值：Flash Drv文件是否有效
* 备    注: 
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
* 函数名称：CheeckAppFileIsValid
* 功能描述：检查请求下载的App文件是否是有效的
* 入口参数：
* 出口参数：
* 返 回 值：App文件是否有效 - 芯片特性 - 升级文件前4个字节为固定值
* 备    注: 
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
* 函数名称：CheckAppCoeValidFlg
* 功能描述：检查AppCode有效性标识
* 入口参数：
* 出口参数：
* 返 回 值：AppCode是否有效
* 备    注: 
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
* 函数名称：CheckE2promAppCoeValidFlg
* 功能描述：检查E2promAppCodeValidFlg有效性
* 入口参数：
* 出口参数：
* 返 回 值：E2promAppCodeValidFlg是否有效
* 备    注: 
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

