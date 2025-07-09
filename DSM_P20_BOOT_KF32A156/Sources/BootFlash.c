#include "BootFlash.h"
#include "Bootloader.h"
#include "Prog.h"
#include "Output.h"
#include "BootDesc.h"
//#include "S32K144_features.h"
//#include "device_registers.h"


#ifndef ALIGN
/* Compiler Related Definitions */
#ifdef __CC_ARM                         /* ARM Compiler */
    #define ALIGN(n)                    __attribute__((aligned(n)))
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)                    PRAGMA(data_alignment=n)
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    #define ALIGN(n)                    __attribute__((aligned(n)))
#endif /* Compiler Related Definitions */
#endif


#define     D_FlashDrvInitDebug_Flg     0

/*FlashDriver in RAM*/
#define FLASHDRIVERINRAM   __attribute__((section (".FlashDriverInRam")))

const flash_user_config_t FlashAsEepromCfg_InitConfig0 = {
    .PFlashBase  = 0x00000000U,                     /* Base address of Program Flash block */
    .PFlashSize  = 0x00080000U,                     /* Size of Program Flash block         */
    .DFlashBase  = EEPROM_ADDRESS,                     /* Base address of Data Flash block    */
    .DFlashSize   = 0x0800,                     /* Base address of FlexRAM block */
    /* If using callback, any code reachable from this function must not be placed in a Flash block targeted for a program/erase operation.*/
    .CallBack    = NULL_CALLBACK
};
static flash_ssd_config_t gst_Flash_SSDConfig;

/* Function declarations */
void FTFC_IRQHandler(void);

tFlashParam localProgFlashParm; /*对Flash操作时当做参数传入的结构体*/


// 此处的地址要跟.prm文件的一致
FLASH_U8  flashDrvBuf[FLASH_DRV_BUF_SIZE] =
//FLASH_U8 FLASHDRIVERINRAM flashDrvBuf[FLASH_DRV_BUF_SIZE] =
{
#if D_FlashDrvInitDebug_Flg
    0x01, 0x60, 0x01, 0x44, 0x3D, 0xD0, 0x00, 0x3D, 0xE6, 0x00, 0x3D, 0xF1, 0x00, 0x3E, 0x9F, 0x00, 0x3B, 0xCC, 0x01, 0x18,
    0x7B, 0x01, 0x00, 0x1D, 0x01, 0x05, 0x03, 0xEE, 0x80, 0x62, 0x04, 0x6A, 0x02, 0x69, 0x05, 0x1B, 0x82, 0x0A, 0xB7, 0x45, 0x62, 0x04, 0xC6, 0x02, 0x6B, 0x02, 0x69, 0x05, 0x0A, 0x3B, 0xB7, 0x45,
    0x62, 0x04, 0xC6, 0x03, 0x6B, 0x02, 0xEC, 0x08, 0x8C, 0x00, 0x03, 0x22, 0x05, 0x8C, 0x00, 0x02, 0x24, 0x07, 0xC6, 0x02, 0x6B, 0x05, 0x06, 0x3E, 0x9C, 0xC6, 0x55, 0x5B, 0x3F, 0x58, 0x5B, 0x3F,
    0x39, 0x14, 0x10, 0x18, 0x0D, 0xB0, 0x3D, 0xB0, 0x86, 0x30, 0x7A, 0x01, 0x06, 0x1E, 0x01, 0x06, 0x80, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x08, 0x6B, 0x05, 0x20, 0x68,
    0x79, 0x01, 0x02, 0xC6, 0x0A, 0x7B, 0x01, 0x0A, 0xEE, 0x80, 0x19, 0x08, 0xE6, 0x41, 0x7B, 0x01, 0x0B, 0x72, 0x01, 0x02, 0xEC, 0x0A, 0xC4, 0xF8, 0x7C, 0x01, 0x0A, 0xC6, 0x80, 0x7B, 0x01, 0x06,
    0x1F, 0x01, 0x06, 0x80, 0xFB, 0x1F, 0x01, 0x06, 0x10, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x09, 0x6B, 0x05, 0x20, 0x30, 0x1F, 0x01, 0x06, 0x20, 0x0E, 0x18, 0x09, 0xAF,
    0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x09, 0x6B, 0x05, 0x20, 0x1D, 0x1F, 0x01, 0x06, 0x03, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x03, 0x6B, 0x05, 0x20, 0x0A, 0x18, 0x09,
    0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0x69, 0x05, 0x1B, 0x82, 0x0A, 0x1B, 0x97, 0x3B, 0xC7, 0x87, 0x6C, 0x86, 0x6B, 0x89, 0x6B, 0x8A, 0x6C, 0x84, 0x6C, 0x82, 0x6B, 0x88, 0xEE, 0x80, 0x62, 0x04,
    0xC6, 0x04, 0x6B, 0x02, 0x39, 0x14, 0x10, 0x18, 0x0D, 0xB0, 0x3D, 0xB0, 0xC6, 0x30, 0x7B, 0x01, 0x06, 0xEE, 0x80, 0xEC, 0x0A, 0xC4, 0xF8, 0x6C, 0x84, 0xEC, 0x08, 0x6C, 0x82, 0xE6, 0x0B, 0xC4,
    0x07, 0x6B, 0x88, 0xC7, 0x87, 0x6C, 0x86, 0x06, 0x3F, 0xB3, 0x79, 0x01, 0x02, 0xC6, 0x06, 0x7B, 0x01, 0x0A, 0xA6, 0x83, 0x7A, 0x01, 0x0B, 0x72, 0x01, 0x02, 0xEC, 0x84, 0x7C, 0x01, 0x0A, 0x69,
    0x89, 0x72, 0x01, 0x02, 0xE6, 0x88, 0x26, 0x08, 0xEE, 0x80, 0xED, 0x86, 0xAD, 0x06, 0x25, 0x4A, 0xEC, 0x84, 0x84, 0x3F, 0x3B, 0xEC, 0x86, 0xC7, 0x84, 0xC0, 0x3B, 0xEC, 0x86, 0xC4, 0x3F, 0x87,
    0xB7, 0x45, 0x3A, 0x59, 0xB7, 0xC5, 0x55, 0x45, 0xB7, 0xC5, 0x59, 0xB7, 0xC5, 0x55, 0x45, 0x3B, 0xEC, 0x82, 0x34, 0xEA, 0x81, 0xAA, 0xB1, 0x8A, 0x80, 0x6C, 0x82, 0xE6, 0x8D, 0x87, 0xE3, 0x82,
    0xCE, 0x00, 0x00, 0xB7, 0x46, 0x3A, 0xC9, 0x00, 0x89, 0x00, 0x16, 0x3D, 0xB2, 0x7D, 0x01, 0x0A, 0xE6, 0x8A, 0xC0, 0x02, 0x6B, 0x8A, 0x1B, 0x82, 0x20, 0x13, 0xEC, 0x0C, 0xE3, 0x86, 0x3B, 0xC7,
    0x31, 0x16, 0x3D, 0xB2, 0x7D, 0x01, 0x0A, 0xEE, 0x86, 0x1A, 0x02, 0x6E, 0x86, 0xE6, 0x89, 0xCB, 0x02, 0x6B, 0x89, 0xC1, 0x08, 0x25, 0x8A, 0xC6, 0x80, 0x7B, 0x01, 0x06, 0x1F, 0x01, 0x06, 0x80,
    0xFB, 0x1F, 0x01, 0x06, 0x10, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x09, 0x6B, 0x05, 0x20, 0x51, 0x1F, 0x01, 0x06, 0x20, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE,
    0x80, 0xC6, 0x09, 0x6B, 0x05, 0x20, 0x3E, 0x1F, 0x01, 0x06, 0x03, 0x04, 0xC6, 0x01, 0x6B, 0x8A, 0xEC, 0x84, 0xC3, 0x00, 0x08, 0x6C, 0x84, 0xEC, 0x82, 0xC9, 0x00, 0x89, 0x00, 0x6C, 0x82, 0xEE,
    0x80, 0xEC, 0x86, 0xAC, 0x06, 0x18, 0x25, 0xFF, 0x21, 0xE6, 0x8A, 0x27, 0x0E, 0x18, 0x09, 0xAF, 0x3D, 0xB0, 0x38, 0xEE, 0x80, 0xC6, 0x03, 0x6B, 0x05, 0x20, 0x0A, 0x18, 0x09, 0xAF, 0x3D, 0xB0,
    0x38, 0xEE, 0x80, 0x69, 0x05, 0x1B, 0x8B, 0x0A,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, //后面36Byte没有使用到, 用0xFF填充
#else
    0x00
#endif    
};


#if D_FlashDrvInitDebug_Flg
const tFlashHeader  *pFlshBufHead = (const tFlashHeader *)&flashDrvBuf[0];
#else
const   tFlashHeader    *pFlshBufHead = NULL;
#endif

stFlashEraseInfo    FlashEraseInfo;
INT8U   ProgflashBuf[FLASH_SEGMENT_SIZE];


static INT8U s_flash_step = EN_STEP_NULL;


/***********************************************************************
 * @function name: getFlashStep
 * 
 * @description: 获取当前已完成刷写步骤
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: s_flash_step 当前已完成刷写步骤
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-12-05 11:50
 ***********************************************************************/
INT8U getFlashStep(void)
{
	return s_flash_step;
}

/***********************************************************************
 * @function name: setFlashStep
 * 
 * @description: 设置当前已完成的刷写步骤
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-12-05 11:50
 ***********************************************************************/
void setFlashStep(INT8U step)
{
	s_flash_step = step;
}

/*******************************************************************************
* 函数名称：EraseFlashBySectorNumber
* 功能描述：Flash擦除
* 入口参数：FlashStartAddr : Flash的起始地址
* 出口参数：无
* 返 回 值：擦除是否成功, TRUE = 成功; FALSE = 失败.
* 备    注: 此函数仅适用Flash地址是连续的
*******************************************************************************/
BOOL EraseFlashBySectorNumber(INT32U FlashStartAddr)
{
    BOOL    ret = FALSE;
	INT8U i=0;
	
	/*flash驱动函数为空;擦除起始地址不是1个sector对齐;擦除sector个数大于AppCode分配的大小*/
    //if((NULL == pFlshBufHead)||((FlashStartAddr%D_FlashOneSector_Len)!=0u))
    if(((FlashStartAddr%D_FlashOneSector_Len)!=0u))
    {
        ret = FALSE;
        return (ret);
    }

    Boot_DisableInterrupts;
    
    // 擦除Flash
    FlashEraseInfo.RetryCnt = D_FlashEraseRetry_Times;
    for(i=0;i<D_FlashEraseRetry_Times;i++)
    {
		localProgFlashParm.address = FlashStartAddr;
		localProgFlashParm.length = D_FlashOneSector_Len;
	#if 0
		// flashEraseFct 擦除函数, 只需输入需要擦除块的地址即可, 对应会输出擦除OK还是擦除失败对应的ErrorCode
		pFlshBufHead->flashEraseFct(&localProgFlashParm);
	#endif
		 Output_FeedWatchDog();
		localProgFlashParm.errorCode=FLASH_DRV_EraseSector(&localProgFlashParm.flashSSDConfig,localProgFlashParm.address,localProgFlashParm.length);
		 Output_FeedWatchDog();
		// 检查擦除结果
		if(STATUS_SUCCESS == localProgFlashParm.errorCode)
		{
			ret = TRUE;
			break;
		}
   	}
    Boot_EnableInterrupts;
    
    return (ret);
}

/*******************************************************************************
* 函数名称：EraseAllAppCodeFlashBlockTask
* 功能描述：擦除AppCode的所有Flash Block任务
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 该函数10ms调用一次, 每次进入会擦除一个Block,如果一次性擦除所有Flash,由于时间比较久,诊断响应会超时
            擦除所有块需要时间 5S
*******************************************************************************/
void    EraseAllAppCodeFlashBlockTask(void)
{
    static      BOOL    FlashInitFlg = FALSE;
    volatile    BOOL    IsOkEraseFlashSector = FALSE;
    // 如果擦除Flash时,没有初始Flash,则先初始化Flash
    #if 0
    if((TRUE == FlashEraseInfo.StartEraseFlg) && (FALSE == FlashInitFlg))
    {
        if(NULL == pFlshBufHead)
        {
            FlashEraseInfo.StartEraseFlg = FALSE;
            FlashEraseInfo.EraseSuccessFlg = FALSE;
            FlashEraseInfo.EraseFlashRespProcess();            
            return;
        }

        FlashInitFlg = TRUE;
        IsOperateFlash = TRUE;
        pFlshBufHead->flashInitFct(&localProgFlashParm);
        return; // 初始需要一定时间
    }
    #endif
    if(TRUE == FlashEraseInfo.StartEraseFlg)
    {
    	/*在AppCode分配的地址范围内*/
		if((FlashEraseInfo.FlashBlockIndex>=(D_AppCodeStart_Addr/D_FlashOneSector_Len))&&\
		(FlashEraseInfo.FlashBlockIndex<(D_FlashSectorNum+(D_AppCodeStart_Addr/D_FlashOneSector_Len))))
		{
			IsOkEraseFlashSector=EraseFlashBySectorNumber(FlashEraseInfo.FlashBlockIndex*D_FlashOneSector_Len);
		}
		else
		{
			IsOkEraseFlashSector = FALSE;
		}
		
        Output_FeedWatchDog();
        // 判断擦除Sector是否成功
        if(TRUE == IsOkEraseFlashSector)
        {
            FlashEraseInfo.FlashBlockIndex ++;
            if(FlashEraseInfo.FlashBlockIndex % D_EraseSize == 0)
            {
            	//发送等待
            	BootDescSet31ResponsePending();
            }

            // 判断擦除Sector总数量
//            if((EraseFlashSectorNum + (D_AppCodeStart_Addr/D_FlashOneSector_Len)) == FlashEraseInfo.FlashBlockIndex)
            if((D_FlashSectorNum + (D_AppCodeStart_Addr/D_FlashOneSector_Len)) == FlashEraseInfo.FlashBlockIndex)
            {
                IsOperateFlash = FALSE;
                FlashEraseInfo.StartEraseFlg = FALSE;
                FlashEraseInfo.EraseSuccessFlg = TRUE; // Flash 擦除成功
                FlashEraseInfo.EraseFlashRespProcess();                
            }
        }
        else
        {
            IsOperateFlash = FALSE;
            FlashEraseInfo.StartEraseFlg = FALSE;
            FlashEraseInfo.EraseSuccessFlg = FALSE;
            FlashEraseInfo.EraseFlashRespProcess();
        }
    }
}

/*
**********************************************************************************************************
* Function Name : FlexRAM_As_EEPROM_Config
* Description   : Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region
* Date          : 2018/04/10
* Parameter     : void
* Return Code   : return status
* Author        : HaiBin Cai
**********************************************************************************************************
*/
static status_t FlexRAM_As_EEPROM_Config(void)
{
    status_t len_Ret = STATUS_ERROR;
    status_t len_DEFlashPartitionRet = STATUS_ERROR;
    status_t len_FlashInitRet = STATUS_ERROR;
    status_t len_SetFlexRamRet = STATUS_ERROR;
    INT8U lu8Cnt = 3U;
#ifndef FLASH_TARGET    
/* Reprogram secure byte in Flash configuration field */
#if (FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD == 1u)
    INT32U lu32Address = 0x408u;
    INT32U lu32Size = FTFx_PHRASE_SIZE;
    INT8U lu8Unsecure_Key[FTFx_PHRASE_SIZE] = {0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFEu, 0xFFu, 0xFFu, 0xFFu};
#else   /* FEATURE_FLASH_HAS_PROGRAM_LONGWORD_CMD */
    INT32U lu32Address = 0x40Cu;
    INT32U lu32Size = FTFx_LONGWORD_SIZE;
    INT8U lu8Unsecure_Key[FTFx_LONGWORD_SIZE] = {0xFEu, 0xFFu, 0xFFu, 0xFFu};
#endif  /* FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD */
#endif /* FLASH_TARGET */

#if ((FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u))
    /* Config FlexRAM as EEPROM if it is currently used as traditional RAM */
    if (gst_Flash_SSDConfig.EEESize == 0u)
    {
#ifndef FLASH_TARGET
        /* First, erase all Flash blocks if code is placed in RAM to ensure
        * the IFR region is blank before partitioning FLexNVM and FlexRAM */
        len_Ret = FLASH_DRV_EraseAllBlock(&gst_Flash_SSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == len_Ret);

        /* Verify the erase operation at margin level value of 1 */
        len_Ret = FLASH_DRV_VerifyAllBlock(&gst_Flash_SSDConfig, 1u);
        DEV_ASSERT(STATUS_SUCCESS == len_Ret);

        len_Ret = FLASH_DRV_Program(&gst_Flash_SSDConfig, lu32Address, lu32Size, lu8Unsecure_Key);
        DEV_ASSERT(STATUS_SUCCESS == len_Ret);
#endif /* FLASH_TARGET */

        /* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
        * DEFlashPartition will be failed if the IFR region isn't blank.
        * Refer to the device document for valid EEPROM Data Size Code
        * and FlexNVM Partition Code. For example on S32K144:
        * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
        * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
        while((len_DEFlashPartitionRet != STATUS_SUCCESS) && (lu8Cnt > 0U))
        {
            lu8Cnt--;
            len_DEFlashPartitionRet = FLASH_DRV_DEFlashPartition(&gst_Flash_SSDConfig, 0x02u, 0x08u, 0x0u, false, true);
        }
        lu8Cnt = 3U;
        
        /* Re-initialize the driver to update the new EEPROM configuration */
        while((len_FlashInitRet != STATUS_SUCCESS) && (lu8Cnt > 0U))
        {
            lu8Cnt--;
            len_FlashInitRet = FLASH_DRV_Init(&FlashAsEepromCfg_InitConfig0, &gst_Flash_SSDConfig);
        }
        lu8Cnt = 3U;
        
        /* Make FlexRAM available for EEPROM */
        while((len_SetFlexRamRet != STATUS_SUCCESS) && (lu8Cnt > 0U))
        {
            lu8Cnt--;
            len_SetFlexRamRet = FLASH_DRV_SetFlexRamFunction(&gst_Flash_SSDConfig, EEE_ENABLE, 0x00u, NULL);
        }
        if((len_DEFlashPartitionRet == STATUS_SUCCESS) && (len_FlashInitRet == STATUS_SUCCESS) && (len_SetFlexRamRet == STATUS_SUCCESS))
        {
            len_Ret = STATUS_SUCCESS;
        }
        else
        {
            len_Ret = STATUS_ERROR;
        }
    }
    else    /* FLexRAM is already configured as EEPROM */
    {
        /* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
        * are already partitioned successfully before */
        while((len_Ret != STATUS_SUCCESS) && (lu8Cnt > 0U))
        {
            lu8Cnt--;
            len_Ret = FLASH_DRV_SetFlexRamFunction(&gst_Flash_SSDConfig, EEE_ENABLE, 0x00u, NULL);
        }
    }
#endif /* (FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u) */
    return len_Ret;
}

void BootFlash_Init(void)
{
    status_t len_Ret = STATUS_ERROR;
    len_Ret = FLASH_DRV_Init(&FlashAsEepromCfg_InitConfig0, &gst_Flash_SSDConfig);
	if(len_Ret==STATUS_SUCCESS)
	{
		len_Ret=FlexRAM_As_EEPROM_Config();
		MemCopy((INT8U *)(&localProgFlashParm.flashSSDConfig),(INT8U *)(&gst_Flash_SSDConfig),sizeof(gst_Flash_SSDConfig));
	}
}

/*******************************************************************************
* 函数名称：EraseAppCodeFlashBlock
* 功能描述：擦除AppCode Flash Block
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 擦除Flash sector
*******************************************************************************/
void    EraseAppCodeFlashBlock(void)
{
    static      BOOL    FlashInitFlg = FALSE;
    volatile    BOOL    IsOkEraseFlashSector = FALSE;
#if 0
    // 如果擦除Flash时,没有初始Flash,则先初始化Flash
    if((TRUE == FlashEraseInfo.StartEraseFlg) && (FALSE == FlashInitFlg))
    {
        if(NULL == pFlshBufHead)
        {
            FlashEraseInfo.StartEraseFlg = FALSE;
            FlashEraseInfo.EraseSuccessFlg = FALSE;
            FlashEraseInfo.EraseFlashRespProcess();            
            return;
        }
        
        FlashInitFlg = TRUE;
        IsOperateFlash = TRUE;
        pFlshBufHead->flashInitFct(&localProgFlashParm);
        return; // 初始需要一定时间
    }
#endif
    if(TRUE == FlashEraseInfo.StartEraseFlg)
    {
    	/*在AppCode分配的地址范围内*/
		if((FlashEraseInfo.FlashBlockIndex>=(D_AppCodeStart_Addr/D_FlashOneSector_Len))&&\
		(FlashEraseInfo.FlashBlockIndex<(D_FlashSectorNum+(D_AppCodeStart_Addr/D_FlashOneSector_Len))))
		{
			IsOkEraseFlashSector=EraseFlashBySectorNumber(FlashEraseInfo.FlashBlockIndex*D_FlashOneSector_Len);
		}
		else
		{
			IsOkEraseFlashSector = FALSE;
		}

        Output_FeedWatchDog();

        // 判断擦除Sector是否成功
        if(TRUE == IsOkEraseFlashSector)
        {
            FlashEraseInfo.EraseSuccessFlg = TRUE;
        }
        else
        {
            FlashEraseInfo.EraseSuccessFlg = FALSE;
        }
        IsOperateFlash = FALSE;
        FlashEraseInfo.StartEraseFlg = FALSE;
        FlashEraseInfo.EraseFlashRespProcess(); 
    }
}

void FTFC_IRQHandler(void)
{
    /* Disable Flash Command Complete interrupt */
  //  FTFx_FCNFG &= (~FTFx_FCNFG_CCIE_MASK);

    return;
}
