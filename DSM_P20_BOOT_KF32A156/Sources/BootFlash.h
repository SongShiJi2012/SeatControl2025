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

/*flash drive addr ��RAM�еķ���*/
#define     D_FlashDrvStart_Addr                (0x10006800u) /*FlashDrv����ʼ��ַ*/
#define     FLASH_DRV_BUF_SIZE                  (0x600) /*32Byte Flash Info + 1212Byte FlashDrv���� + 304Byte Null */

#define     D_FlashDrvCodeStart_Addr            (D_FlashDrvStart_Addr) /*Flash��������ʼ��ַ*/
#define     FLASH_DRV_CODE_SIZE                 (FLASH_DRV_BUF_SIZE) /*Flash ���������С*/

/*AppCode ����ʼ��ַ*/
#define     D_AppCodeStart_Addr                 (0x00015800u) /*AppCode����ʼ��ַ*/
#define     D_AppCodeEnd_Addr                 	(0x00046FFFu) /*AppCode�Ľ�����ַ*/
#define 	D_AppCodeLen						(400ul*1024ul) /*app�������� 400K оƬʵ����� 512k(��) - 86k(boot) = 426k*/

/*AppCode valid Flag ��FLASH�з���ĵ�ַ*/
#define     D_AppCodeFlg_StartAddr          (0x00014000u) /*AppCodeValidFlg����Ϊ24Byte*/
#define     D_AppCodeFlg_EndAddr            (0x00014FFFu) 

#define     D_FlashEraseRetry_Times                 (3) // Flash �������Դ���
#define     D_FlashOneSector_Len                    (FEATURE_FLS_PF_BLOCK_SECTOR_SIZE) // Flashһ��Sector�Ĵ�С4096Bytes
/*�˲���ֻ�������ֵ  ʵ�ʲ�������Ŀǰ������λ���������ĳ��� + 1 о��΢ƽ̨һ�β���1K*/
#define 	D_FlashSectorNum						(400u) /*Flash=400*1k=400k bytes*/

#define 	D_EraseSize								(100u) /*�����ȴ�*/

typedef enum
{
	EN_STEP_NULL,				
	EN_STEP_REQUESTDOWNLOAD_DRIVE,	//������������
	EN_STEP_INTEGRITY_CHECK_DRIVE,	//drive������У�� 
	EN_STEP_ERASE_FLASH,			//����flash
	EN_STEP_REQUESTDOWNLOAD_APP,	//��������APP
	EN_STEP_INTEGRITY_CHECK_APP,	//app������У�� 
	EN_STEP_DEPENDENCY_CHECK_APP,	//app�����Լ��
	EN_STEP_REQUESTEXITDOWNLOAD,	//�����˳�����
	
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

/* ֧�ֵ�block ���� */
#define FBL_MTAB_NO_OF_BLOCKS   (0x02u)

typedef struct
{
    INT8U State;
    INT16U len;
    INT16U surplusLen;/* ʣ�೤�� */
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
    BOOL    StartEraseFlg; // ��������Flash��ʶ
    BOOL    EraseSuccessFlg; // Flash�����Ƿ�ok
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

