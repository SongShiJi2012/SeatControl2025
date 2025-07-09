#ifndef _BOOTFLASH_H
#define _BOOTFLASH_H

#include  "Common.h"
#include "flash_driver.h"
#include "Srvl_E2memory.h"

typedef       unsigned  char                        FLASH_BOOL;
typedef       unsigned  char                        FLASH_U8;
typedef       unsigned  short                       FLASH_U16;
typedef       unsigned  long                         FLASH_U32;

/* flash page size */
#define FLASH_SEGMENT_SIZE          (0X300u)
#define FLASH_PRIT_SIZE             (0x08)

/*flash drive addr 在RAM中的分配*/
#define     D_FlashDrvStart_Addr                (0x10006800u) /*FlashDrv的起始地址*/
#define     FLASH_DRV_BUF_SIZE                  (0x600) /*32Byte Flash Info + 1212Byte FlashDrv代码 + 304Byte Null */

#define     D_FlashDrvCodeStart_Addr            (D_FlashDrvStart_Addr) /*Flash驱动的起始地址*/
#define     FLASH_DRV_CODE_SIZE                 (FLASH_DRV_BUF_SIZE) /*Flash 驱动代码大小*/

/*AppCode 的起始地址*/
#define     D_AppCodeStart_Addr                 (0x00015800u) /*AppCode的起始地址*/
#define     D_AppCodeEnd_Addr                 	(0x00046FFFu) /*AppCode的结束地址*/
#define 	D_AppCodeLen						(400ul*1024ul) /*app长度限制 400K 芯片实际最高 512k(总) - 86k(boot) = 426k*/

/*AppCode valid Flag 在FLASH中分配的地址*/
#define     D_AppCodeFlg_StartAddr          (0x00014000u) /*AppCodeValidFlg长度为24Byte*/
#define     D_AppCodeFlg_EndAddr            (0x00014FFFu) 

#define     D_FlashEraseRetry_Times                 (3) // Flash 擦除尝试次数
#define     D_FlashOneSector_Len                    (FEATURE_FLS_PF_BLOCK_SECTOR_SIZE) // Flash一个Sector的大小4096Bytes
/*此参数只限制最大值  实际擦除长度目前采用上位机发过来的长度 + 1 芯旺微平台一次擦除1K*/
#define 	D_FlashSectorNum						(400u) /*Flash=400*1k=400k bytes*/

#define 	D_EraseSize								(100u) /*擦除等待*/

typedef enum
{
	EN_STEP_NULL,				
	EN_STEP_REQUESTDOWNLOAD_DRIVE,	//请求下载驱动
	EN_STEP_INTEGRITY_CHECK_DRIVE,	//drive完整性校验 
	EN_STEP_ERASE_FLASH,			//擦除flash
	EN_STEP_REQUESTDOWNLOAD_APP,	//请求下载APP
	EN_STEP_INTEGRITY_CHECK_APP,	//app完整性校验 
	EN_STEP_DEPENDENCY_CHECK_APP,	//app依赖性检查
	EN_STEP_REQUESTEXITDOWNLOAD,	//请求退出下载
	
	EN_STEP_MAX,
}en_FlashStep;



/* flash handle intput parameters */
typedef struct
{
    INT8U   minorVersion;
    INT8U   majorVersion;
    INT8U   patchLevel;
    INT8U   reserved1;
    INT8U   reserved2;
    status_t   errorCode;
	flash_ssd_config_t flashSSDConfig;
	
    INT16U  length;
    INT32U  address;
    INT8U   *data;
    void    (* wdTriggerFct)(void);
    INT8U   intendedData[FLASH_PRIT_SIZE];
    INT8U   actualData[FLASH_PRIT_SIZE];
    INT32U  errorAddress;
} tFlashParam;

typedef void (* tFlashFctType)( tFlashParam * flashParam );

/* flash file header ,printf s19 */
typedef struct
{
    INT8U   version;
    INT8U   reserved;
    INT8U   maskType;
    INT8U   CPUType;
    tFlashFctType flashInitFct;
    tFlashFctType flashDeinitFct;
    tFlashFctType flashEraseFct;
    tFlashFctType flashWriteFct;

	INT8U	TempBuff[12];
} tFlashHeader;

typedef void (*ProgCallBackType)(INT8U);

/* 支持的block 数量 */
#define FBL_MTAB_NO_OF_BLOCKS   (0x02u)

typedef struct
{
    INT8U State;
    INT16U len;
    INT16U surplusLen;/* 剩余长度 */
    INT32U adr;
    INT8U RetyCnt;
    INT8U blockStu[FBL_MTAB_NO_OF_BLOCKS];
    //ProgCallBackType pfProgCallBack;
} ProgDealType;

typedef struct
{
    
    INT32U  StartAddr;
    INT32U  EraseLen;
    INT8U   RetryCnt;
    BOOL    StartEraseFlg; // 启动擦除Flash标识
    BOOL    EraseSuccessFlg; // Flash擦除是否ok
    INT32U FlashBlockIndex;
    pDescRespProcess  EraseFlashRespProcess;
}stFlashEraseInfo;

#if 0
#pragma     DATA_SEG    FLASH_DRIVE_CODE
FLASH_EXT       FLASH_U8 flashDrvBuf[FLASH_DRV_BUF_SIZE];
#pragma     DATA_SEG    DEFAULT
#endif
extern FLASH_U8 flashDrvBuf[FLASH_DRV_BUF_SIZE];

extern tFlashParam         localProgFlashParm;
extern stFlashEraseInfo    FlashEraseInfo;
extern const   tFlashHeader    *pFlshBufHead;
extern INT8U   ProgflashBuf[FLASH_SEGMENT_SIZE];

extern void BootFlash_Init(void);
FLASH_U8    Flash_GetByteFlash(FLASH_U32 Addr, FLASH_U8 * Data);
FLASH_U8    Flash_EraseVerify(FLASH_BOOL * Blank);
BOOL        EraseFlashBySectorNumber(INT32U FlashStartAddr);
void        EraseAllAppCodeFlashBlockTask(void);
void   	    BootFlashTask(void);
extern void BootDescSet31ResponsePending(void);
//void FlashTest(void);
extern INT8U getFlashStep(void);
extern void setFlashStep(INT8U step);


#endif

