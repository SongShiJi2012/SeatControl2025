#include   "BootDesc.h"
#include   "Bootloader.h"
#include   "BootCanDrv.h"
#include   "BootTp.h"
#include   "Prog.h"
#include   "BootFlash.h"
#include   "Clib.h"
#include   "cmac.h"
#include <stdbool.h>

volatile BOOT_U16 gRWBootDIDIndex = 0;

stDownloadInfo  DownloadInfo;

stBOOTDescCallBack DescCallBackLst[enCallBackMax];


BOOT_U8 			BootDescSession;
BOOT_U8 			BootDescRespNoSend;
BOOT_U8 			BootDescTesterPresentTimer;
BOOT_U8 			BootDescPrevSession;
BOOT_U8 			BootDescTimer100ms;
BOOT_U16 			BootDescP4Timer;
BOOT_U16			BootDescTimer10s;


BOOT_BOOL			BootSeedReceive;
BOOT_BOOL			BootunlockStatus;
BOOT_BOOL			BootFingerPrintFlg;

BootDesc_stSecLvl  BootDesc_stsSecLvl;
BOOT_BOOL			BootDescSessionChangedFlag;	
BOOT_BOOL 			BootDescECUHardRestReq;
           
Boot_SecurityAccess_stOutInfo  Boot_SecurityAccess_stgOutInfo;
BOOT_U16 			Boot_SecurityAccess_u2gRand;
volatile BOOT_U8 	BootDescNrc;

BOOT_U32 u32TempCRCValue=0;
BOOT_U32 u32AppCompilerCrc = 0;

BOOT_U32 CRCValue;
BOOT_U32 TempCRCValue;
//BOOT_U16    EraseFlashSectorNum = 0;//о��΢��������λ���������Ĳ������� ��λ1K - ���ֲ�����������  ����ȫ������ 20221118 ssj

volatile INT8U u1gSecurityAccessIsDelayEndFlg = TRUE;

const tBOOT_DESC_INFO  pBootDescHandlerTbl[] =
{
	{eBOOT_SID_DIAGNOG_SESSION_CONTROL,   BootDescDiagnosticSessionControl},
	{eBOOT_SID_ECU_HARD_RESET ,           BootDescEcuRest},

#if (BOOTSID22_READDID_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_READ_DATA_BY_IDENTIFIER ,  BootDescReadDataByIdentifier},
#endif
#if (BOOTSID27_SECURITYACCESS_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_SECURITY_ACCESS,           BootDescSecurityAccess},
#endif
#if BOOTSID28_COMCTL_EN
    {eBOOT_SID_COMMUNICATION_CONTROL  ,   DescCommunicationControl},
#endif

#if (BOOTSID2E_WRITEDID_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_WRITE_DATA_BY_IDENTIFIER,  BootDescWriteDataByIdentifier},
#endif
#if (BOOTSID31_ROUTINECTRL_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_ROUTINE_CONTROL,           BootDescRoutineControl},
#endif
#if (BOOTSID34_REQDWNLOAD_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_REQUEST_DOWNLOAD,          BootDescRequestDownload},
#endif
#if (BOOTSID36_TRANFDATA_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_TRANSFER_DATA,             BootDescTransferData},
#endif
#if (BOOTSID37_TRANFEXIT_EN == BOOTDESC_ENABLE)
	{eBOOT_SID_REQUEST_TRANSFER_EXIT,     BootDescRequestTransferExit},
#endif
#if (BOOTSID85_CTRLDTCSET_EN == BOOTDESC_ENABLE)
    {eBOOT_SID_CONTROL_DTC_SETTING,       BootDescControlDTCSetting},
#endif
	{eBOOT_SID_TESTER_PRESENT,			BootDescTesterPresent},
};


const BOOT_U16  wBootDescServiceRespTime[UBOUND(pBootDescHandlerTbl)] =
{
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescDiagnosticSessionControl : 50ms */
	66, 					 	  /* BootDescEcuRest : 200ms                 */
#if (BOOTSID22_READDID_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescReadDataByIdentifier            */
#endif
#if (BOOTSID27_SECURITYACCESS_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescSecurityAccess                  */
#endif
#if (BOOTSID2E_WRITEDID_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescWriteDataByIdentifier  */
#endif
#if (BOOTSID31_ROUTINECTRL_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescRoutineCtrl*/
#endif
#if (BOOTSID34_REQDWNLOAD_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescRequestDownload		    	*/
#endif
#if (BOOTSID36_TRANFDATA_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescTransferData		    	    */
#endif
#if (BOOTSID37_TRANFEXIT_EN == BOOTDESC_ENABLE)
	BOOT_DESC_P2_CAN_SERVER_MAX,  /* BootDescRequestTransferExit           */
#endif
#if (BOOTSID85_CTRLDTCSET_EN == BOOTDESC_ENABLE)
        BOOT_DESC_P2_CAN_SERVER_MAX,  
#endif
	BOOT_DESC_P2_CAN_SERVER_MAX,
};


const BOOT_U8 cBootDescDiagnosticSession[] =
{
	0x01, 0x02, 0x03, 0x40, 0x60,
};
const BOOT_U8 cBootDesSecurityAccessSubID[] =
{
	BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA, 
	BOOT_DESC_SECURITY_ACCESS_SEND_REPROGRA
};
const BOOT_U8 cBootDescSecurityAccessConstantNum[] =
{
	0x08, 0x60, 0x31, 0x55
};

//const BOOT_U8 DefaultKeyMask1[Boot_SecurityAccess_MLVKEYNUM] = {0x7F,0xBE,0x46,0xA7}; // MS3

const BOOT_U8 DefaultKeyMask[Boot_SecurityAccess_MLVKEYNUM] = {0x7C, 0xF3, 0x73, 0x0D}; // CA10



const BOOT_U8 cBootDescRoutineControlTypeID[] =
{
	0x01, 0x02, 0x03,
};

const tDESC_COM_INFO pComCtrlTbl[] =
{
	{eRXENABLE_TXENABLE,   /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxAndTxEnable}},
	//{eRXENABLE_TXDISABLE,  /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxEnableTxDisable}},
 	//{eRXDISABLE_TXENABLE,  /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxDisableAndTxEnable}},
 	{eRXDISABLE_TXDISABLE, /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxAndTxDisable}}
};

INT8U   SecurityAccessLevel = 0;

BOOL    DownloadFlashDrvFlg = FALSE;
BOOL    DownloadAppCodeFlg = FALSE;




/*36��ͬ��������Դ���*/
#define D_SameBlockRetryTimes   (3)

/* ���ڼ�¼��ǰ�����SER ID */
static INT8U diagServiceCurrent;




//---------------------- DID Function Define Start -----------------------------

void   BootDIDReadRamDataComm(const INT8U* pDat, INT8U DatLen)
{
	INT8U i;
	INT8U TxDatLen = 3;
	for(i = 0; i < DatLen; i++)
	{
		BootTpTxInfoStruct.cDataBuf[TxDatLen++] =  pDat[i];
	}
	BootTpTxInfoStruct.wDataLength = TxDatLen;
	BootDescNrc = BootDescNrcOK;
}


void BootDescDID_Read_F180_BootSoftwareVersion(void)
{
	Srvl_ReadMemIndexData(EN_MemIndex_CustomerBootVersion, &BootTpTxInfoStruct.cDataBuf[3], D_CustomerBootVersion_Len_15);
	BootTpTxInfoStruct.wDataLength = D_CustomerBootVersion_Len_15 + 3u;
	BootDescNrc = (BootDescNrcOK);
}

void BootDescDID_Write_F198_Fingerprint_Resp(void)
{
    if(IsAppE2promOpOK(EN_MemIndex_FingerPrint_RepairShopCodeF198)) // дE2prom ok
    {
        BootFingerPrintFlg = TRUE;
        BootTpTxInfoStruct.wDataLength = 3;
    	BootDescNrc = (BootDescNrcOK);     
    }
    else // дE2prom fail
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }   
}

void BootDescDID_Read_F198_FingerPrintRepairShopCode(void)
{
	Srvl_ReadMemIndexData(EN_MemIndex_FingerPrint_RepairShopCodeF198, &BootTpTxInfoStruct.cDataBuf[3], D_FingerPrint_RepairShopCodeF198_Len_8);
	BootTpTxInfoStruct.wDataLength = D_FingerPrint_RepairShopCodeF198_Len_8 + 3u;
	BootDescNrc = (BootDescNrcOK);
}

void BootDescDID_Write_F198_FingerPrintRepairShopCode(void)
{
    INT8U msgBUF[D_FingerPrint_RepairShopCodeF198_Len_8]={0};
    INT16U BlockId = Srvl_GetE2DefineDataBlockID(EN_MemIndex_FingerPrint_RepairShopCodeF198);
    
    if(D_FingerPrint_RepairShopCodeF198_Len_8 != (BootTpRxInfoStruct.wDataLength - 3))
    {
        BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
        return;
    }
    MemCopy(&msgBUF[0],(INT8U*)&BootTpRxInfoStruct.cDataBuf[3], D_FingerPrint_RepairShopCodeF198_Len_8);
	Srvl_WriteMemIndexData(EN_MemIndex_FingerPrint_RepairShopCodeF198, (INT8U*)&msgBUF[0], D_FingerPrint_RepairShopCodeF198_Len_8);
	AppAppE2promSetCheckWriteResultFlg(BlockId);
	DescCheckE2promResult.WriteE2promRespProcess[BlockId] = BootDescDID_Write_F198_Fingerprint_Resp;
}

void BootDescDID_Write_F199_Fingerprint_Resp(void)
{
    if(IsAppE2promOpOK(EN_MemIndex_FingerPrint_ProgramDate_F199)) // дE2prom ok
    {
        BootFingerPrintFlg = TRUE;
        BootTpTxInfoStruct.wDataLength = 3;
    	BootDescNrc = (BootDescNrcOK);     
    }
    else // дE2prom fail
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }   
}

void BootDescDID_Read_F199_FingerPrintProgramDate(void)
{
    Srvl_ReadMemIndexData(EN_MemIndex_FingerPrint_ProgramDate_F199, &BootTpTxInfoStruct.cDataBuf[3], D_FingerPrint_ProgramDate_F199_Len_4);
    BootTpTxInfoStruct.wDataLength = D_FingerPrint_ProgramDate_F199_Len_4 + 3u;
    BootDescNrc = (BootDescNrcOK);
}

void BootDescDID_Write_F199_FingerPrintRepairShopCode(void)
{
    INT8U msgBUF[D_FingerPrint_ProgramDate_F199_Len_4]={0};
    INT16U BlockId = Srvl_GetE2DefineDataBlockID(EN_MemIndex_FingerPrint_ProgramDate_F199);
    
    if(D_FingerPrint_ProgramDate_F199_Len_4 != (BootTpRxInfoStruct.wDataLength - 3))
    {
        BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
        return;
    }
    MemCopy(&msgBUF[0],(INT8U*)&BootTpRxInfoStruct.cDataBuf[3], D_FingerPrint_ProgramDate_F199_Len_4);
    Srvl_WriteMemIndexData(EN_MemIndex_FingerPrint_ProgramDate_F199, (INT8U*)&msgBUF[0], D_FingerPrint_ProgramDate_F199_Len_4);
    AppAppE2promSetCheckWriteResultFlg(BlockId);
    DescCheckE2promResult.WriteE2promRespProcess[BlockId] = BootDescDID_Write_F199_Fingerprint_Resp;
}

void BootDescDID_Read_D000_DareBootVersion(void)
{
    Srvl_ReadMemIndexData(EN_MemIndex_DareBootVersion, &BootTpTxInfoStruct.cDataBuf[3], D_DareBootVersion_Len_8);
    BootTpTxInfoStruct.wDataLength = D_DareBootVersion_Len_8 + 3u;
    BootDescNrc = (BootDescNrcOK);
}

//---------------------- DID List ----------------------------------------------
const tDESC_BOOTDID_INFO pRWBootDIDInfoTbl[] =
{
	{
		0xF180, D_CustomerBootVersion_Len_15,    {BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_FALSE, 
                                    BootDescDID_Read_F180_BootSoftwareVersion},
		                            {__BOOTDIDNOTSUPPORTWRITE}
	},
	{
		0xF198, D_FingerPrint_RepairShopCodeF198_Len_8,	
                                    {BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_FALSE,
                                    BootDescDID_Read_F198_FingerPrintRepairShopCode},
									{BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_TRUE,
									BootDescDID_Write_F198_FingerPrintRepairShopCode}
	},
	{
		0xF199, D_FingerPrint_ProgramDate_F199_Len_4,	{BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_FALSE,
                                    BootDescDID_Read_F199_FingerPrintProgramDate},
									{BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_TRUE,
									BootDescDID_Write_F199_FingerPrintRepairShopCode}
	},
	{
		0xD000, D_DareBootVersion_Len_8,	{BOOT_SESN_DS | BOOT_SESN_PRGS | BOOT_SESN_EXTDS, BOOT_SA_FALSE,
                                    BootDescDID_Read_D000_DareBootVersion},
		                            {__BOOTDIDNOTSUPPORTWRITE}
	},
};



//---------------------- RoutineCtl Function Define Start ----------------------



void    DescRoutineCtrl_F001_CheckMemory_StartRoutile(void)
{
    INT32U tCrcValue = 0xFFFFFFFF;
    INT8U tCrcValueBuff[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    
    if(TRUE == DownloadFlashDrvFlg) // FlashDrv����
    {
        if(0 == DownloadInfo.BlockSurplusDataLen) // FlashDrv�������
        {
            tCrcValue = Checksum_Crc32((const INT8U *)DownloadInfo.FileLogicStartAddr, DownloadInfo.BlockDataLen);
            tCrcValueBuff[0] = (INT8U)(tCrcValue >> 24);
            tCrcValueBuff[1] = (INT8U)(tCrcValue >> 16);
            tCrcValueBuff[2] = (INT8U)(tCrcValue >> 8);
            tCrcValueBuff[3] = (INT8U)(tCrcValue >> 0);
            
            if( (tCrcValueBuff[0] == BootTpRxInfoStruct.cDataBuf[4]) && \
                (tCrcValueBuff[1] == BootTpRxInfoStruct.cDataBuf[5]) && \
                (tCrcValueBuff[2] == BootTpRxInfoStruct.cDataBuf[6]) && \
                (tCrcValueBuff[3] == BootTpRxInfoStruct.cDataBuf[7]) ) // У��CRC32 ͨ��
            {
             //   pFlshBufHead = (tFlashHeader *)&flashDrvBuf[0]; // ��ȡflashDrv�����ĵ�ַ

        		// ����ڵȴ��Ĺ���, �յ���������Ϸ���
        		// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
        		// 20170913 -- zyc
        		BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40;	
        		BootTpTxInfoStruct.cDataBuf[1] = 0x01;
        		BootTpTxInfoStruct.cDataBuf[2] = 0xF0;
        		BootTpTxInfoStruct.cDataBuf[3] = 0x01;		
                BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
                
                BootTpTxInfoStruct.wDataLength = 5;
                BootDescNrc = BootDescNrcOK;
            }
            else // У��CRC32 ûͨ��
            {
        		// ����ڵȴ��Ĺ��̣�,�յ���������Ϸ���
        		// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
        		// 20170913 -- zyc	
        		diagServiceCurrent = 0x31;			
                BootDescNrc = (kBootDescNrcConditionsNotCorrect); // NRC22
            }
        }
        else // FlashDrvû�������
        {
    		// ����ڵȴ��Ĺ��̣�,�յ���������Ϸ���
    		// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    		// 20170913 -- zyc	
    		diagServiceCurrent = 0x31;			
            BootDescNrc = (kBootDescNrcConditionsNotCorrect); // NRC22           
        }
    }
    else // AppCode����
    {
        if(TRUE == DownloadAppCodeFlg)
        {
            if(0 == DownloadInfo.BlockSurplusDataLen)
            {
                tCrcValue = Checksum_Crc32_FarAddr(DownloadInfo.FileLogicStartAddr, DownloadInfo.BlockDataLen);
                tCrcValueBuff[0] = (INT8U)(tCrcValue >> 24);
                tCrcValueBuff[1] = (INT8U)(tCrcValue >> 16);
                tCrcValueBuff[2] = (INT8U)(tCrcValue >> 8);
                tCrcValueBuff[3] = (INT8U)(tCrcValue >> 0);
                
                if( (tCrcValueBuff[0] == BootTpRxInfoStruct.cDataBuf[4]) && \
                    (tCrcValueBuff[1] == BootTpRxInfoStruct.cDataBuf[5]) && \
                    (tCrcValueBuff[2] == BootTpRxInfoStruct.cDataBuf[6]) && \
                    (tCrcValueBuff[3] == BootTpRxInfoStruct.cDataBuf[7]) ) // У��CRC32 ͨ��
                {
            		// ����ڵȴ��Ĺ���, �յ���������Ϸ���
            		// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
            		// 20170913 -- zyc
            		BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40;	
            		BootTpTxInfoStruct.cDataBuf[1] = 0x01;
            		BootTpTxInfoStruct.cDataBuf[2] = 0xF0;
            		BootTpTxInfoStruct.cDataBuf[3] = 0x01;		
                    BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
                    
                    BootTpTxInfoStruct.wDataLength = 5;
                    BootDescNrc = BootDescNrcOK;
                }
                else // У��CRC32 ûͨ��
                {
            		// ����ڵȴ��Ĺ��̣�,�յ���������Ϸ���
            		// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
            		// 20170913 -- zyc	
            		diagServiceCurrent = 0x31;			
                    BootDescNrc = (kBootDescNrcConditionsNotCorrect); // NRC22
                }
            }
            else // FlashDrvû�������
            {
        		// ����ڵȴ��Ĺ��̣�,�յ���������Ϸ���
        		// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
        		// 20170913 -- zyc	
        		diagServiceCurrent = 0x31;			
                BootDescNrc = (kBootDescNrcConditionsNotCorrect); // NRC22           
            }            
        }
		else
		{
			BootDescNrc = (kBootDescNrcRequestSequenceError); // NRC24		 
		}
    } 
}



void    DescRoutineCtrl_FF00_EraseMemory_StartRoutile_Resp(void)
{
    if(TRUE == FlashEraseInfo.EraseSuccessFlg)
    {
    	// ����ڲ����Ĺ���, �յ���������Ϸ���
    	// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    	// 20170913 -- zyc
    	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
    	BootTpTxInfoStruct.cDataBuf[1] = 0x01;
    	BootTpTxInfoStruct.cDataBuf[2] = 0xFF;
    	BootTpTxInfoStruct.cDataBuf[3] = 0x00;    
        BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;

		setFlashStep(EN_STEP_ERASE_FLASH);
        BootTpTxInfoStruct.wDataLength = 5u;
        BootDescNrc = (BootDescNrcOK);        
    }
    else
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }
}


void    DescRoutineCtrl_FF00_EraseMemory_StartRoutile_Callback(void)
{
    // E2prom�е�AppCodeValidFlg�����ɹ���, ����Flash����
    if(IsAppE2promOpOK(EN_MemIndex_APP_ValidFlg)) // ��E2prom ok
    {
        FlashEraseInfo.StartAddr = DownloadInfo.FileStartAddr;
        FlashEraseInfo.EraseLen = DownloadInfo.FileDataLen;
        FlashEraseInfo.StartEraseFlg = TRUE;
        FlashEraseInfo.EraseSuccessFlg = FALSE;
        // Ĭ�ϲ����� D_AppCodeStart_Addr ��ʼ
        FlashEraseInfo.FlashBlockIndex = (D_AppCodeStart_Addr/D_FlashOneSector_Len); 
        FlashEraseInfo.EraseFlashRespProcess = DescRoutineCtrl_FF00_EraseMemory_StartRoutile_Resp;            
    }
    else // ��E2prom fail
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }       
}

void    DescRoutineCtrl_FF00_EraseMemory_StartRoutile(void)
{
    // 31 01 FF 00 44 + 4Byte Addr + 4Byte Len

    // Check flash erase address and length format is ok
    if(BootTpRxInfoStruct.cDataBuf[4] != D_FlashEraseAddrAndLen_Format)
    {
        BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
        return;
    }
	//û��д��ָ��NRC7F Or û��ִ��drive������У��
	if((BootFingerPrintFlg==FALSE) || (getFlashStep() != EN_STEP_INTEGRITY_CHECK_DRIVE))
	{
		BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
		return;
	}
    
    // get memory address
    DownloadInfo.FileStartAddr = ToolMake32Bit( BootTpRxInfoStruct.cDataBuf[5],
                                                BootTpRxInfoStruct.cDataBuf[6],
                                                BootTpRxInfoStruct.cDataBuf[7],
                                                BootTpRxInfoStruct.cDataBuf[8]  );
    // get memory length
    DownloadInfo.FileDataLen = ToolMake32Bit(   BootTpRxInfoStruct.cDataBuf[9],
                                                BootTpRxInfoStruct.cDataBuf[10],
                                                BootTpRxInfoStruct.cDataBuf[11],
                                                BootTpRxInfoStruct.cDataBuf[12] );
//    EraseFlashSectorNum = (DownloadInfo.FileDataLen / D_FlashOneSector_Len) + 1;
	DownloadInfo.FileStartAddr = DownloadInfo.FileStartAddr + BOOT_APPCODE_CRC_VALUE_SIZEOF;
    DownloadInfo.FileSurplusDataLen = DownloadInfo.FileDataLen; 
    
    // Check flash erase address is ok
    if(D_AppCodeStart_Addr != DownloadInfo.FileStartAddr)
    {
        BootDescNrc = (kBootDescNrcRequestOutOfRange);
        return;        
    }
    if((0 == DownloadInfo.FileDataLen) || (DownloadInfo.FileDataLen > D_AppCodeLen))
    {
        BootDescNrc = (kBootDescNrcRequestOutOfRange);
        return;
    }

    ReqDownloadFlashBlockCnt = 0x00;
    
    // �Ȱ�E2prom�е�AppCodeValidFlg����
    g_E2promAppCodeValidFlg = FALSE;
	Srvl_WriteMemIndexData(EN_MemIndex_APP_ValidFlg, (INT8U * )E2promAppCodeInvalidFlgDefine,D_APP_ValidFlg_Len_8);
	AppAppE2promSetCheckWriteResultFlg(EN_MemIndex_APP_ValidFlg);
	DescCheckE2promResult.WriteE2promRespProcess[EN_MemIndex_APP_ValidFlg] = DescRoutineCtrl_FF00_EraseMemory_StartRoutile_Callback;

	BootDescResponsePending(); // 78 Pending
}

void    DescRoutineCtrl_FF01_CheckProgDependence_StartRoutile_Resp(void)
{
    // E2prom�е�AppCodeValidFlgд�ɹ�
    if(IsAppE2promOpOK(EN_MemIndex_APP_ValidFlg)) // дE2prom ok
    {
    	BootEnterAppFlag = TRUE;
    	EnterAppDelayTimeCnt = D_EnterAppDelayTime_1000ms;
		AppCodeValidFlg = CheckAppCoeValidFlg();
	#if (APP_DEBUG!=1u)
		g_E2promAppCodeValidFlg = CheckE2promAppCoeValidFlg();
    #endif
	
    	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
    	BootTpTxInfoStruct.cDataBuf[1] = 0x01;
    	BootTpTxInfoStruct.cDataBuf[2] = 0xFF;
    	BootTpTxInfoStruct.cDataBuf[3] = 0x01;    
        BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
        
        BootTpTxInfoStruct.wDataLength = 5u;
        BootDescNrc = (BootDescNrcOK);           
    }
    else // дE2prom fail
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }    
}

void    DescRoutineCtrl_FF01_CheckProgDependence_StartRoutile(void)
{
	INT32U CalculateCrc = 0x00000000UL;
	CalculateCrc = ~u32CalculateCrc;
    
	//1��app��Ч ��δ����app�� ��ֹ������ֱ�ӹ������̵�����APP����ȴ����ת�����³����ܷ�
	//2.����APPδ��ɣ�NRC22
	//3.appδ������У��
	if( (CheckAppCoeValidFlg() == FALSE && FALSE == DownloadAppCodeFlg ) \
		|| (TRUE == DownloadAppCodeFlg && 0 != DownloadInfo.BlockSurplusDataLen)\
		|| (EN_STEP_INTEGRITY_CHECK_APP != getFlashStep()))
    {
		DownloadAppCodeFlg = FALSE;//����У����û��ͨ��������app��־λ��ΪFALSE����ֹ��������дָ��ʧ��--mantis��6679
		BootDescNrc = (kBootDescNrcConditionsNotCorrect);
		return;
	}

	DownloadAppCodeFlg = FALSE;//����У����û��ͨ��������app��־λ��ΪFALSE����ֹ��������дָ��ʧ��--mantis��6679

	// app�����Լ�鲻ͨ��
	if(CalculateCrc != u32AppCompilerCrc) 
	{
		BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
		BootTpTxInfoStruct.cDataBuf[1] = 0x01;
		BootTpTxInfoStruct.cDataBuf[2] = 0xFF;
		BootTpTxInfoStruct.cDataBuf[3] = 0x01;	  
		BootTpTxInfoStruct.cDataBuf[4] = 1;//ROUTINESTATUSRECODE_INCORRET;

		BootTpTxInfoStruct.wDataLength = 5u;
		BootDescNrc = (BootDescNrcOK);
		return;
	}
		
    if(TRUE == CheckAppCoeValidFlg()) // ���п鶼�������, ���Flash��AppCode�����ʶ�Ƿ����
    {
        // ��E2prom�е�AppCodeValidFlgд��
        Srvl_WriteMemIndexData(EN_MemIndex_APP_ValidFlg, (INT8U * )E2promAppCodeValidFlgDefine,D_APP_ValidFlg_Len_8);
        AppAppE2promSetCheckWriteResultFlg(EN_MemIndex_APP_ValidFlg);
        DescCheckE2promResult.WriteE2promRespProcess[EN_MemIndex_APP_ValidFlg] = DescRoutineCtrl_FF01_CheckProgDependence_StartRoutile_Resp;
		BootDescResponsePending(); // 78 Pending   cd:1457
    }
	else
	{
		BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
	}

}



void    DescRoutineCtrl_FF02_CheckProgPrecondition_StartRoutile(void)
{
	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
	BootTpTxInfoStruct.cDataBuf[1] = 0x01;
	BootTpTxInfoStruct.cDataBuf[2] = 0xFF;
	BootTpTxInfoStruct.cDataBuf[3] = 0x02;	  
	BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
	
	BootTpTxInfoStruct.wDataLength = 5u;
	BootDescNrc = (BootDescNrcOK);

    if(IsE2promPwrVoltNormal())
    {
    	// ����ڲ����Ĺ���, �յ���������Ϸ���
    	// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    	// 20170913 -- zyc
    	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
    	BootTpTxInfoStruct.cDataBuf[1] = 0x01;
    	BootTpTxInfoStruct.cDataBuf[2] = 0xFF;
    	BootTpTxInfoStruct.cDataBuf[3] = 0x02;    
        BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
        
        BootTpTxInfoStruct.wDataLength = 5u;
        BootDescNrc = (BootDescNrcOK);
    }
    else
    {
        diagServiceCurrent = 0x31;
        BootDescNrc = (kBootDescNrcConditionsNotCorrect);
        return;          
    }
}

//unsigned char key[] = {
//  0x2b, 0x7e, 0x15, 0x16,
//  0x28, 0xae, 0xd2, 0xa6,
//  0xab, 0xf7, 0x15, 0x88,
//  0x09, 0xcf, 0x4f, 0x3c,
//};
//unsigned char message[] = {
//  0x6b, 0xc1, 0xbe, 0xe2,
//  0x2e, 0x40, 0x9f, 0x96,
//  0xe9, 0x3d, 0x7e, 0x11,
//  0x73, 0x93, 0x17, 0x2a,
//  0xae, 0x2d, 0x8a, 0x57,
//  0x1e, 0x03, 0xac, 0x9c,
//  0x9e, 0xb7, 0x6f, 0xac,
//  0x45, 0xaf, 0x8e, 0x51,
//  0x30, 0xc8, 0x1c, 0x46,
//  0xa3, 0x5c, 0xe4, 0x11,
//  0xe5, 0xfb, 0xc1, 0x19,
//  0x1a, 0x0a, 0x52, 0xef,
//  0xf6, 0x9f, 0x24, 0x45,
//  0xdf, 0x4f, 0x9b, 0x17,
//  0xad, 0x2b, 0x41, 0x7b,
//  0xe6, 0x6c, 0x37, 0x10
//};
const INT8U key[] = {0x52, 0xA9, 0x60, 0xC5, 0xD0, 0xE3, 0xE5, 0xE7,
					 0x8E, 0x35, 0xD5, 0xFD, 0xDE, 0xA8, 0xB4, 0x79};
void DescRoutineCtrl_0202_CheckMemory_StartRoutile_Callback(void)
{
 	INT8U i;
	INT32U CRC32Value=0x00;
	
	//��ֹǰ�淢�͹�7F 78 �󣬸���Ӧ����3F�����
	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40;	
	 
	if(TRUE == DownloadFlashDrvFlg) // FlashDrv����
	{
		if(0 == DownloadInfo.BlockSurplusDataLen) // FlashDrv�������
		{
			BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
//            CRC32Value = Checksum_Crc32((const INT8U *)DownloadInfo.FileStartAddr,DownloadInfo.BlockDataLen);
			 CRC32Value = ~u32TempCRCValue;
			 for(i = 0; i < 4; i++)
			{
				if( ((INT8U)(CRC32Value >> (32 - (i + 1) * 8))) != BootTpRxInfoStruct.cDataBuf[4 + i])
				{
//					BootDescNrc = kBootDescNrcConditionsNotCorrect;
					BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_INCORRET;
					break;
				}
			}
			BootTpTxInfoStruct.cDataBuf[1] = 0x01;
			BootTpTxInfoStruct.cDataBuf[2] = 0x02;
			BootTpTxInfoStruct.cDataBuf[3] = 0x02;		
			
			BootTpTxInfoStruct.wDataLength = 5;
			BootDescNrc = BootDescNrcOK;
			if(BootTpTxInfoStruct.cDataBuf[4] == ROUTINESTATUSRECODE_CORRET)
			{
				setFlashStep(EN_STEP_INTEGRITY_CHECK_DRIVE);
			}
        }
		else // FlashDrvû�������
		{		
			BootDescNrc = (kBootDescNrcConditionsNotCorrect); // NRC22			 
		}
	}
    else if(TRUE == DownloadAppCodeFlg)
    {
        if(0 == DownloadInfo.BlockSurplusDataLen)
        {
            BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
//          CRC32Value = Checksum_Crc32((const INT8U *)DownloadInfo.FileStartAddr,DownloadInfo.BlockDataLen);
            CRC32Value = ~u32TempCRCValue;

            for(i = 0; i < 4; i++)
            {
                if( ((INT8U)(CRC32Value >> (32 - (i + 1) * 8))) != BootTpRxInfoStruct.cDataBuf[4 + i])
                {
                    DownloadAppCodeFlg = FALSE; //У��û��ͨ��������app��־λ��ΪFALSE����ֹ��������дָ��ʧ��--mantis��6679
                    BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_INCORRET;
                    break;
//                  BootDescNrc = kBootDescNrcConditionsNotCorrect;
//                   return;
                }
            }
            BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40;   
            BootTpTxInfoStruct.cDataBuf[1] = 0x01;
            BootTpTxInfoStruct.cDataBuf[2] = 0x02;
            BootTpTxInfoStruct.cDataBuf[3] = 0x02;      
            
            BootTpTxInfoStruct.wDataLength = 5;
            BootDescNrc = BootDescNrcOK;
            if(BootTpTxInfoStruct.cDataBuf[4] == ROUTINESTATUSRECODE_CORRET)
            {
                setFlashStep(EN_STEP_INTEGRITY_CHECK_APP);
            }
    
        }
        else
        {
            BootDescNrc = (kBootDescNrcConditionsNotCorrect);
        }
    }
    else
    {
        BootDescNrc = (kBootDescNrcRequestSequenceError);
    }
}
/*******************************************************************************
* �������ƣ�DescRoutineCtrl_0202_CheckMemory_StartRoutile,
* �����������������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
void DescRoutineCtrl_0202_CheckMemory_StartRoutile(void)
{
	DescCallBackLst[en_Rountine0202Start].bCheckFlag = TRUE;
	DescCallBackLst[en_Rountine0202Start].RespProcess = DescRoutineCtrl_0202_CheckMemory_StartRoutile_Callback;
	BootDescResponsePending(); // 78 Pending
}

void DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile_Callback(void)
{
	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
    if(IsAppE2promOpOK(EN_MemIndex_AppJumpToBootFlg))
    {
    	BootTpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40u;	
    	BootTpTxInfoStruct.cDataBuf[1] = 0x01;
    	BootTpTxInfoStruct.cDataBuf[2] = 0x02;
    	BootTpTxInfoStruct.cDataBuf[3] = 0x03;    
       // BootTpTxInfoStruct.cDataBuf[4] = ROUTINESTATUSRECODE_CORRET;
        
        BootTpTxInfoStruct.wDataLength = 4u;//���������Ӧ����Ϊ4
        BootDescNrc = (BootDescNrcOK);        
    }
    else 
    {
        BootDescNrc = (kBootDescNrcGeneralProgrammingFailure);
    }       
}

void DescRoutineCtrl_AAAA_EraseE2prom_StartRoutile(void)
{
	INT8U TempBuf[D_BOOT_INIT_Data_Len_4];
	//��һ���ϵ� д��BOOT��ʼ����app��Ч��־ �ⲿEEPROM����Ҫ����
	memset(TempBuf, 0xFF, D_BOOT_INIT_Data_Len_4);
	Srvl_WriteMemIndexData(EN_MemIndex_BOOT_INIT_Data, TempBuf, D_BOOT_INIT_Data_Len_4);
	BootDescNrc = (BootDescNrcOK);
}
void DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile(void)
{
	AppAppE2promSetCheckWriteResultFlg(EN_MemIndex_AppJumpToBootFlg);
	DescCheckE2promResult.WriteE2promRespProcess[EN_MemIndex_AppJumpToBootFlg] = DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile_Callback;
	BootDescResponsePending(); // 78 Pending
}

//---------------------- RoutineCtl List ---------------------------------------
const tBOOTDESC_ROUTINT_INFO pBootRoutineCtlTbl[] =
{
	// �����ڴ�
	{0xFF00, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,	 {	 {9, DescRoutineCtrl_FF00_EraseMemory_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},	   
	
	{0x0202, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,	{	{4, DescRoutineCtrl_0202_CheckMemory_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},
	
	// �߼��������Լ��
	{0xFF01, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,	 {	 {0, DescRoutineCtrl_FF01_CheckProgDependence_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},
	
#if 0
	// ��������
	{0xF001, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,	 {	 {4, DescRoutineCtrl_F001_CheckMemory_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},
	// �����Ԥ����
	{0xFF02, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,	{	{0, DescRoutineCtrl_FF02_CheckProgPrecondition_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},

	{0x0203, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_FALSE,  {	 {0, DescRoutineCtrl_0203_CheckProgPreCond_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	},
	{0xAAAA, BOOT_SESN_PRGS|BOOT_SESN_EXTDS, BOOT_SA_TRUE,  {   {0, DescRoutineCtrl_AAAA_EraseE2prom_StartRoutile},
																{0, NULL},
																{0, NULL}	}
	}
#endif
};




BOOT_U8	BootSessionConverGet(BOOT_U8 SenssionType)
{
	BOOT_U8 SessionTmp = BOOT_SESN_DS;
	switch((eBOOT_SESSION_TYPE)SenssionType)
	{
		case eBOOT_SESSION_DEFAULT:
			SessionTmp = BOOT_SESN_DS;
			break;
		case eBOOT_SESSION_PROGRAM:
			SessionTmp = BOOT_SESN_PRGS;
			break;
		case eBOOT_SESSION_EXTENDED:
			SessionTmp = BOOT_SESN_EXTDS;
			break;
		case eBOOT_SESSION_VEHICLEFACTURER:
			SessionTmp = BOOT_SESN_VMS;
			break;
		case eBOOT_SESSION_SYSTEMSUPPLIER:
			SessionTmp = BOOT_SESN_SSS;
			break;
		default:
			SessionTmp = BOOT_SESN_DS;
			break;
	}
	return SessionTmp;
}


void    ClearAppJumpBootFlg_Resp(void)
{
    if(IsAppE2promOpOK(EN_MemIndex_AppJumpToBootFlg)) // дE2prom ok
    {
        BootTpTxInfoStruct.cDataBuf[0] = 0x10 + 0x40;
        BootTpTxInfoStruct.cDataBuf[1] = 0x02;
    	BootTpTxInfoStruct.cDataBuf[2] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME) >> 8); // ��λ 1ms
    	BootTpTxInfoStruct.cDataBuf[3] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME);
    	BootTpTxInfoStruct.cDataBuf[4] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10) >> 8); // ��λ 10ms
    	BootTpTxInfoStruct.cDataBuf[5] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10);
        BootTpTxInfoStruct.wDataLength = 6;

    	BootDescNrc = (BootDescNrcOK);
	}
	else
	{
	    BootTpTxInfoStruct.cDataBuf[1] = 0x10 + 0x40; // �����ͳһ -0x40
	    BootDescNrc = (kBootDescNrcConditionsNotCorrect);
	}
}
void BootDescInit(void)
{
	INT8U i;
    BootDescSession = BOOT_SESN_DS;
    BootDescNrc = BootDescNrcNoRsp;
	BootDescTesterPresentTimer = 0;
	BootDescP4Timer = 0;
	BootunlockStatus = FALSE;
	BootSeedReceive = FALSE;
	BootDescTimer100ms = BOOT_DESC_TIMER_100MS;
	BootDescSessionChangedFlag = FALSE;
	BootDescPrevSession = 0;
	BootDescRespNoSend = TRUE;
	BootDesc_stsSecLvl.CurrLvl = BootDesc_enmSecNonLvl;
	BootDesc_stsSecLvl.PreLvl = BootDesc_enmSecNonLvl;
	BootFingerPrintFlg = FALSE;
	for(i = 0; i < UBOUND(DescCallBackLst); i++)
	{
		DescCallBackLst[i].RespProcess = NULL;
		DescCallBackLst[i].bCheckFlag = FALSE;
	}
}

void BootDescSendNegResp(BOOT_U8  cRespCode)
{
	BootTpTxInfoStruct.cDataBuf[1] = BootTpTxInfoStruct.cDataBuf[0] - 0x40;
	BootTpTxInfoStruct.cDataBuf[0] = BOOTDESC_NEGATIVE_RESPONSE_SERVICE_ID;
	BootTpTxInfoStruct.cDataBuf[2] = cRespCode;
	BootTpTxInfoStruct.wDataLength = 3;
}

void BootDescResponsePending(void)
{
    BootDescNrc = (kBootDescNrcResponsePending);
}

void BootDescSessionChanged(BOOT_U8	cPreSession, BOOT_U8 cNewSession)
{
    if(BOOT_SESN_PRGS == cNewSession)
    {
        BootEnterAppFlag = FALSE;
        EnterAppDelayTimeCnt = D_EnterAppDelayTime_1000ms;
    }
    else
    {
        AppCodeValidFlg = CheckAppCoeValidFlg();
	#if (APP_DEBUG!=1u)
        g_E2promAppCodeValidFlg = CheckE2promAppCoeValidFlg();
    #endif
        if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg))
        {
            BootEnterAppFlag = TRUE;
            EnterAppDelayTimeCnt = D_EnterAppDelayTime_100ms;
        }
    }
}


/*******************************************************************************
* �������ƣ�BootDescTask
* �������������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: Period is 5ms
*******************************************************************************/
void    BootDescTask(void)
{
	BOOT_U8	cIndex;
	BOOT_U8	cServiceFound = FALSE;
	eBOOT_SID_TYPE eBOOT_ReqSID;

	if(BootDescSessionChangedFlag)
	{
		BootDescSessionChangedFlag = FALSE;
		BootDesc_stsSecLvl.CurrLvl = BootDesc_enmSecNonLvl;
		BootDesc_stsSecLvl.PreLvl = BootDesc_enmSecNonLvl;
		BootDescSessionChanged(BootDescPrevSession, BootDescSession);
	}
	
	if(BootDescTimer100ms > 0)
	{
		BootDescTimer100ms --;
	}
	if(u1gSecurityAccessIsDelayEndFlg == FALSE)
	{
		if(BootDescTimer10s > 0)
		{
			BootDescTimer10s --;
		}
		if(BootDescTimer10s == 0)
		{
			BootDescTimer10s = BOOT_DESC_TIMER_10S;
			u1gSecurityAccessIsDelayEndFlg = TRUE;
		}
	}
	if(BootDescTimer100ms == 0)
	{
		BootDescTimer100ms = BOOT_DESC_TIMER_100MS;
		if(BootDescTesterPresentTimer > 0)
		{
			BootDescTesterPresentTimer  --;
		}
		if(BootDescTesterPresentTimer == 0)
		{
			BootunlockStatus = FALSE;
			BootSeedReceive = FALSE;
#ifdef BOOTCAN_PERIODMSGTX
			Boot_DownloadFlg = FALSE;
#endif
			if(BootDescSession != BOOT_SESN_DS)
			{
				BootDescSessionChanged(BootDescSession, BOOT_SESN_DS);
				BootDescSession = BOOT_SESN_DS;
				DownloadFlashDrvFlg = FALSE;
				DownloadAppCodeFlg = FALSE;

				/* Add: Jetty 20220218 �Ự��ʱ��λ */
				EcuHardReset();
			}
		}
	}
	
	if(TRUE == BootDescECUHardRestReq)
	{
		BootDescECUHardRestReq = FALSE;
        EcuHardReset();
	}
	
	for(cIndex = 0; cIndex < UBOUND(DescCallBackLst); cIndex++)
	{
		if(DescCallBackLst[cIndex].bCheckFlag == TRUE)
		{
			if(DescCallBackLst[cIndex].RespProcess != NULL)
			{
				DescCallBackLst[cIndex].RespProcess();
				DescCallBackLst[cIndex].bCheckFlag = FALSE;
				break;
			}
		}
	}
	
	if(BootTpRxState.engine == BOOT_kRxState_CanFrameReceived)
	{
		//BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		BootTpRxState.engine = BOOT_kRxState_ApplInformed;
		BootDescP4Timer = BOOT_DESC_P2_CAN_SERVER_MAX;
		eBOOT_ReqSID = (eBOOT_SID_TYPE)BootTpRxInfoStruct.cDataBuf[0];
		BootDescNrc = BootDescNrcNoRsp;
		for(cIndex = 0; cIndex < UBOUND(pBootDescHandlerTbl); cIndex ++)
		{
			if((pBootDescHandlerTbl[cIndex].eBOOT_SID == eBOOT_ReqSID) && (NULL != pBootDescHandlerTbl[cIndex].pServerProcess))
			{
				cServiceFound = TRUE;
				BootDescRespNoSend = TRUE;
				BootDescP4Timer = wBootDescServiceRespTime[cIndex];
				BootTpTxInfoStruct.cDataBuf[0] = eBOOT_ReqSID + 0X40;
				/* Service Format is ok */
				BootTpTxInfoStruct.cDataBuf[1] = BootTpRxInfoStruct.cDataBuf[1];
				BootTpTxInfoStruct.cDataBuf[2] = BootTpRxInfoStruct.cDataBuf[2];
				pBootDescHandlerTbl[cIndex].pServerProcess();
				break;
			}
		}
		
		if(cServiceFound == FALSE)
		{
			BootDescP4Timer = BOOT_DESC_P2_CAN_SERVER_MAX;
			if(BootTpRxInfoStruct.cCANIDIndex == TST_BootPhysicalReqPEPS)
			{
				BootTpTxInfoStruct.cDataBuf[0] = BootTpRxInfoStruct.cDataBuf[0] + 0X40;
				BootDescNrc = (kBootDescNrcServiceNotSupported);
				//BootDescNrc = BootDescNrcNoRsp;

			}
			else
			{
				BootTpRxState.engine = BOOT_kRxState_Idle;
				BootTpTxState.engine = BOOT_kTxState_Idle;
				BootDescNrc = BootDescNrcNoRsp;
			}
		}
	}
	
	if(BootDescNrcOK < BootDescNrc)
	{
		/*������� ��������ʹ�ù���Ѱַʱ������ NRC0x11�� NRC0x7F�� NRC0x12�� NRC0x7E�� NRC0x31 ����ķ���
			Ӧ���ģ��������ȴ��� NRC0x78������Ӧ�����͡�*/
		if(((BootDescNrc == kBootDescNrcServiceNotSupported) \
			|| (BootDescNrc == kBootDescNrcSubfunctionNotSupported) \
			|| (BootDescNrc == kBootDescNrcServiceNotSupportedInActiveSession) \
			|| (BootDescNrc == kBootDescNrcSubfunctionNotSupportedInActiveSession) \
			|| (BootDescNrc == kBootDescNrcRequestOutOfRange)) \
			&& (BootTpRxInfoStruct.cCANIDIndex == TST_BootFunctionalReqMS))
		{
			BootDescNrc = BootDescNrcNoRsp;
		}
		else
		{
			BootDescSendNegResp(BootDescNrc);
		}
	}
	
	if(BootDescNrcNoRsp != BootDescNrc)
	{
		BootTpTxStart();
		BootDescNrc = BootDescNrcNoRsp;
	}
	
	if(BootDescP4Timer > 0)
	{
		BootDescP4Timer -- ;
	}
	
	if((BootDescP4Timer == 0) && (BootTpRxState.engine == BOOT_kRxState_ApplInformed) && (BootDescRespNoSend))
	{
		BootDescRespNoSend = FALSE;
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootTpTxState.engine = BOOT_kTxState_Idle;
	}

}

void BootDescDiagnosticSessionControl(void)
{
	BOOT_U8 cIndex;
	BOOT_U8 cTempDescSession;
	BOOT_BOOL cSessionFound = FALSE;
	BootunlockStatus = FALSE;
	BootSeedReceive = FALSE;
	cTempDescSession =  (BootTpRxInfoStruct.cDataBuf[1] & 0x7f);

	if (2 != BootTpRxInfoStruct.wDataLength)
	{
		BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

	
	for(cIndex = 0; cIndex < UBOUND(cBootDescDiagnosticSession); cIndex++)
	{
		if(cBootDescDiagnosticSession[cIndex] == cTempDescSession)
		{
			cSessionFound = TRUE;
		}
	}
	if(FALSE == cSessionFound)
	{
		if(BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_PHYSICAL)
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
		}
		return;
	}
	

	
	cTempDescSession =	BootSessionConverGet(BootTpRxInfoStruct.cDataBuf[1] & 0x7f);
	/*	����Ѱַ�л�1002��̻Ự��ECU������Ӧ add zjx on 20220728	*/
	if((BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_FUNTION) && (BOOT_SESN_PRGS == cTempDescSession))
	{
		BootDescNrc = BootDescNrcNoRsp;
		return;
	}
	
	if(((BOOT_SESN_PRGS == cTempDescSession) && (BOOT_SESN_DS == BootDescSession))||\
	((BOOT_SESN_EXTDS == cTempDescSession) && (BOOT_SESN_PRGS == BootDescSession)))
	{
		BootDescNrc = kBootDescNrcSubfunctionNotSupportedInActiveSession;// 22 -> 7E ��ǰ�Ự��֧���ӹ��� change by zjx on 20220728
		return;
	}
	if(BootDescSession != cTempDescSession)
	{
		if(BOOT_SESN_PRGS == cTempDescSession)
		{
			BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		}
		BootDescSessionChangedFlag = TRUE;
		BootDescPrevSession = BootDescSession;
		BootDescSession = cTempDescSession;
		BootDescTimer100ms = BOOT_DESC_TIMER_100MS;
	}
	else
	{
		if(BOOT_SESN_PRGS == cTempDescSession)
		{
			BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
			BootDescTimer100ms = BOOT_DESC_TIMER_100MS;
			BootDescSession = cTempDescSession;
		}
	}
	if(!(BootTpRxInfoStruct.cDataBuf[1] & 0x80))
	{
	    
        BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
        BootTpTxInfoStruct.cDataBuf[1] = BootTpRxInfoStruct.cDataBuf[1];

		BootTpTxInfoStruct.cDataBuf[2] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME) >> 8); // ��λ 1ms
		BootTpTxInfoStruct.cDataBuf[3] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME);
		BootTpTxInfoStruct.cDataBuf[4] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10) >> 8); // ��λ 10ms
		BootTpTxInfoStruct.cDataBuf[5] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10);
        BootTpTxInfoStruct.wDataLength = 6;
		BootDescNrc = BootDescNrcOK;
	}
	else
	{
        BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootTpTxState.engine = BOOT_kTxState_Idle;
		BootDescNrc = BootDescNrcNoRsp;
	}
}


void EcuHardReset(void)
{
//	static CAN_Type * const g_flexcanBase[] = CAN_BASE_PTRS;
//	CAN_Type * base = g_flexcanBase[INST_CANMAIN];
//	INT_SYS_DisableIRQGlobal();
//	FLEXCAN_ClearErrIntStatusFlag(base);
//
//	SystemSoftwareReset();
//	asm("RESET");
//	while(1);

	SystemSoftwareReset();
	asm("RESET");
	while(1);

}

void BootDescEcuRest(void)
{
	if(2 != BootTpRxInfoStruct.wDataLength)
	{
		BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

	if(((BootTpRxInfoStruct.cDataBuf[1] & 0x7Fu) == BOOT_DESC_ECU_HARD_REST) || \
		((BootTpRxInfoStruct.cDataBuf[1] & 0x7Fu) == BOOT_DESC_ECU_SOFT_REST))
	{
		if((BootTpRxInfoStruct.cDataBuf[1] & 0x80) != 0u) /*��ֹ�϶���Ӧ*/
		{
			if(IsE2promBusy() == FALSE)
			{
                EcuHardReset();
			}
			else
			{
				BootDescNrc = (kBootDescNrcConditionsNotCorrect);
			}
		}
		else
		{
			if(IsE2promBusy() == FALSE)
			{
				/* Hard Reset ECU */
				BootTpTxInfoStruct.wDataLength = 2;
				BootDescNrc = BootDescNrcOK;
				BootDescECUHardRestReq = TRUE;
			}
			else
			{
				BootDescNrc = (kBootDescNrcConditionsNotCorrect);
			}
		}
	}
	else
	{
		/* Sub Service Function Not Support */
		if(BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_PHYSICAL)
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
		}
	}
}

void BootDescTesterPresent(void)
{
	if(2 != BootTpRxInfoStruct.wDataLength)
    {
        BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
        return;
    }
	if((BootTpRxInfoStruct.cDataBuf[1] == BOOT_DESC_TESTER_PRESENT_ZERO_SUB_FUNC) || \
			(BootTpRxInfoStruct.cDataBuf[1] == (BOOT_DESC_TESTER_PRESENT_ZERO_SUB_FUNC | 0x80)))
	{
		BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
		if(BootTpRxInfoStruct.cDataBuf[1] == BOOT_DESC_TESTER_PRESENT_ZERO_SUB_FUNC)
		{
			BootTpTxInfoStruct.wDataLength = 2;
			BootDescNrc = BootDescNrcOK;
		}
		else
		{
			BootTpRxState.engine = BOOT_kRxState_Idle;
			BootTpTxState.engine = BOOT_kTxState_Idle;
		}
	}
	else
	{
		if(BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_PHYSICAL)
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
		}
		else
		{
		}
	}
}


void Boot_SecurityAccess_vogSeedGenerate(void)
{
	BOOT_U8 i, SeedChgFlg = TRUE;

	*((BOOT_U16*)Boot_SecurityAccess_stgOutInfo.u1SecLvSeed) = Boot_SecurityAccess_u2gRand;
	Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2] = ((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[0] << 2) & 0x1C) | \
			((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1] << 5) & 0xE0) | \
			((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1] >> 6) & 0x03);
	Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[3] = ((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1] << 2) & 0x1C) | \
			((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2] << 5) & 0xE0) | \
			((Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2] >> 6) & 0x03);
	for(i = 0; i < Boot_SecurityAccess_MSEEDNUM; i++)
	{
		if(0 != Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[i])
		{
			SeedChgFlg = FALSE;
		}
	}
	if(SeedChgFlg)
	{
		for(i = 0; i < Boot_SecurityAccess_MSEEDNUM; i++)
		{
			Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[i] = i + 0xAA;
		}
	}
}

void BootDesc_SecurityAccessServerAlreadyUnlock(void)
{
	BOOT_U8 cIndex;
	BootSeedReceive = TRUE;
	if(BootTpRxInfoStruct.cDataBuf[1] == BOOT_DESC_SECURITY_ACCESS_REQUEST_EXTSEED 
    || BootTpRxInfoStruct.cDataBuf[1] == BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA)
	{
		BootTpTxInfoStruct.wDataLength = 2;
		for(cIndex = 0; cIndex < Boot_SecurityAccess_MSEEDNUM; cIndex ++)
		{
			BootTpTxInfoStruct.cDataBuf[cIndex + 2] = 0;
			BootTpTxInfoStruct.wDataLength++;
		}
		BootDescNrc = BootDescNrcOK;
	}
}
void BootDesc_SecurityAccessRequestSeed(BOOT_BOOL u1tNotRepeatReqFlg)
{
	BOOT_U8 cIndex = 0;
	BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
	BootSeedReceive = TRUE;
	if(u1tNotRepeatReqFlg)
	{
		Boot_SecurityAccess_vogSeedGenerate();
	}
	BootTpTxInfoStruct.wDataLength = 2;
	for(cIndex = 0; cIndex < Boot_SecurityAccess_MSEEDNUM; cIndex ++)
	{
		BootTpTxInfoStruct.cDataBuf[cIndex + 2] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[cIndex];
		BootTpTxInfoStruct.wDataLength++;
	}
	BootDescNrc = BootDescNrcOK;
}

void BootDesc_vosSecAccessReqSeed(void)
{
	if(BootTpRxInfoStruct.wDataLength == 2)
	{
		if(BootDesc_stsSecLvl.PreLvl != BootDesc_stsSecLvl.CurrLvl)
		{
			BootDesc_stsSecLvl.PreLvl = BootDesc_stsSecLvl.CurrLvl;
			BootSeedReceive = FALSE;
			BootunlockStatus = FALSE;
		}
		if(BootSeedReceive == TRUE)
		{
			if(BootunlockStatus == FALSE)
			{
				BootDesc_SecurityAccessRequestSeed(FALSE);
			}
			else
			{
				BootDesc_SecurityAccessServerAlreadyUnlock();
			}
		}
		else
		{
			if(BootunlockStatus)
			{
				BootDesc_SecurityAccessServerAlreadyUnlock();
			}
			else
			{
				BootDesc_SecurityAccessRequestSeed(TRUE);
			}
		}
	}
	else
	{
		BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
	}
}


/*************************************************************
* �������ƣ�SecurityAccess_vogKeyGenerate
* ������������ȫ���ʲ���Key�㷨
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:MS3��ȫ�����㷨
*************************************************************/
#if 0
void BootSecurityAccess_vogKeyGenerate1(void)
{
	BOOT_U8 u1tIndex0 = 0;
	BOOT_U8 Cal[Boot_SecurityAccess_MLVKEYNUM] = {0};
	for(u1tIndex0 = 0; u1tIndex0 < Boot_SecurityAccess_MLVKEYNUM; u1tIndex0++)
	{
		Cal[u1tIndex0] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[u1tIndex0] ^ DefaultKeyMask1[u1tIndex0];
	}
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[0] = ((Cal[0] & 0x0F)<<4)|(Cal[3] & 0xF0);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[1] = ((Cal[1] & 0x0F)<<4)|((Cal[0] & 0xF0) >> 4);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[2] = (Cal[2] & 0xF0)|((Cal[1] & 0xF0) >> 4);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[3] = ((Cal[3] & 0x0F)<<4)|(Cal[2] & 0x0F);
}
#endif


/*************************************************************
* �������ƣ�SecurityAccess_vogKeyGenerate
* ������������ȫ���ʲ���Key�㷨
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:Lifan CA10��ȫ�����㷨
*************************************************************/
#if 0
void BootSecurityAccess_vogKeyGenerate(void)
{

	BOOT_U8 u1tIndex0 = 0;
	BOOT_U8 Key1[Boot_SecurityAccess_MLVKEYNUM] = {0};
	BOOT_U8 Seed2[Boot_SecurityAccess_MLVKEYNUM] = {0};
	BOOT_U8 Key2[Boot_SecurityAccess_MLVKEYNUM] = {0};
	
	for(u1tIndex0 = 0; u1tIndex0 < Boot_SecurityAccess_MLVKEYNUM; u1tIndex0++)
	{
		Key1[u1tIndex0] = (Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[u1tIndex0] ^ DefaultKeyMask[u1tIndex0]);
	}

	Seed2[0] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[3];
	Seed2[1] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2];
	Seed2[2] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1];
	Seed2[3] = Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[0];

	for(u1tIndex0 = 0; u1tIndex0 < Boot_SecurityAccess_MLVKEYNUM; u1tIndex0++)
	{
		Key2[u1tIndex0] = (Seed2[u1tIndex0] ^ DefaultKeyMask[u1tIndex0]);
	}

	for(u1tIndex0 = 0; u1tIndex0 < Boot_SecurityAccess_MLVKEYNUM; u1tIndex0++)
	{
		Boot_SecurityAccess_stgOutInfo.u1SecLvKey[u1tIndex0] = Key1[u1tIndex0] + Key2[u1tIndex0];
	}
}
#endif


//#define ALGORTITHMASK   (0x77534131ul)
#define UNLOCKKEY       (0x0ul)
#define UNLOCKSEED      (0x0ul)
#define UNDEFINESEED    (0xFFFFFFFFul)
#define SEEDMASK        (0x80000000ul)
#define SHIFTBIT        (1u)

/*************************************************************
* �������ƣ�BootSecurityAccess_vogKeyGenerate
* ������������ȫ���ʲ���Key�㷨
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:�ƶȰ�ȫ�����㷨
*************************************************************/
/*
void BootSecurityAccess_vogKeyGenerate(void)
{
    unsigned char i;
    unsigned long seed = ToolMake32Bit(Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[0],
                                       Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1],
                                       Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2],
                                       Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[3]);
    unsigned long ALGORTITHMASK = ToolMake32Bit(0x77u, 0x53u, 0x41u, 0x35u);
    unsigned long key = UNLOCKKEY;

	if(1 == SecurityAccessLevel)
	{
		ALGORTITHMASK = ToolMake32Bit(0x77u, 0x53u, 0x41u, 0x31u);
	}
	else if(5 == SecurityAccessLevel)
	{
		ALGORTITHMASK = ToolMake32Bit(0x77u, 0x53u, 0x41u, 0x35u);
	}
	
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[0] = ToolGetHiHiByte(UNLOCKKEY);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[1] = ToolGetHiLoByte(UNLOCKKEY);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[2] = ToolGetLoHiByte(UNLOCKKEY);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[3] = ToolGetLoLoByte(UNLOCKKEY);
    
    if(!((seed == UNLOCKSEED) || (seed == UNDEFINESEED)))
    {
        for(i = 0u; i < 35u; i++)
        {
            if(seed & SEEDMASK)
            {
                seed = seed << SHIFTBIT;
                seed = seed ^ ALGORTITHMASK;
            }
            else
            {
                seed = seed << SHIFTBIT;
            }
        }
        key = seed;
    }
    
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[0] = ToolGetHiHiByte(key);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[1] = ToolGetHiLoByte(key);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[2] = ToolGetLoHiByte(key);
    Boot_SecurityAccess_stgOutInfo.u1SecLvKey[3] = ToolGetLoLoByte(key);
}
*/


/*******************************************************************************
* �������ƣ�BootSecurityAccess_vogKeyGenerate
* ������������ȫ���ʲ���Key�㷨
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: ����DSM_C62X��ȫ�����㷨
*******************************************************************************/
#if (DSM_CURRECT_PROJECT == DSM_B60V_PROJECT)

#if 0 //TEST CASE
// SEED 0x6816b4d5
// AF   0x01020304050607080102030405060708
// KEY  0x5a9a4885d4f3be60004798c58272d32f
const INT8U ALGORITHM_FACTORS[16] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
};

#else

#if 1
//BOOT 27/11-12 0x5D9E691BB008DBCDCC0D7B07482C10D3
const INT8U ALGORITHM_FACTORS[16] = {
	0x5D, 0x5F, 0x0D, 0x57, 0x51, 0xAC, 0xB1, 0xDC,
	0x8E, 0xCD, 0xD8, 0xD5, 0xE1, 0x44, 0x65, 0xF6
};
#else
//APP 27/01-02 0x003E3BED9BD0E9A853AD11DC2409FCD9
const INT8U ALGORITHM_FACTORS[16] = {
	0x00, 0x3E, 0x3B, 0xED, 0x9B, 0xD0, 0xE9, 0xA8, 
	0x53, 0xAD, 0x11, 0xDC, 0x24, 0x09, 0xFC, 0xD9
};
#endif
#endif

#elif (DSM_CURRECT_PROJECT == DSM_B30X_PROJECT|| DSM_CURRECT_PROJECT == DSM_PD014_PROJECT)

#if 0 //TEST CASE
// SEED 0x6816b4d5
// AF   0x01020304050607080102030405060708
// KEY  0x5a9a4885d4f3be60004798c58272d32f
const INT8U ALGORITHM_FACTORS[16] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
};

#else

#if 1
//BOOT 27/11-120x463DA8E07DF33E6C3CBAC15C236F4CBB
const INT8U ALGORITHM_FACTORS[16] = {
	0x46, 0x3D, 0xA8, 0xE0, 0x7D, 0xF3, 0x3E, 0x6C,
	0x3C, 0xBA, 0xC1, 0x5C, 0x23, 0x6F, 0x4C, 0xBB
};
#else
//APP 27/01-02 0x003E3BED9BD0E9A853AD11DC2409FCD9
const INT8U ALGORITHM_FACTORS[16] = {
	0x00, 0x3E, 0x3B, 0xED, 0x9B, 0xD0, 0xE9, 0xA8, 
	0x53, 0xAD, 0x11, 0xDC, 0x24, 0x09, 0xFC, 0xD9
};
#endif
#endif

#elif (DSM_CURRECT_PROJECT == DSM_C52X_PROJECT)
#define     MASK_LVL1		(0x141319CEul)
#define	    MASK_LVL2		(0x7E34C58Aul)
#else
#endif

INT32U GENERIC_ALGORITHM( INT32U wSeed, INT32U MASK )
{
	INT8U   iterations;
	INT32U wLastSeed;
	INT32U wTemp;
	INT32U wLSBit;
	INT32U wTop31Bits;
	INT8U   jj,SB1,SB2,SB3;
	INT16U temp;

	wLastSeed = wSeed;
	temp =(INT16U)(( MASK & 0x00000800) >> 10) | ((MASK & 0x00200000)>> 21);

	if(temp == 0)
	{
		wTemp = (INT32U)((wSeed & 0xff000000) >> 24);
	}
	else if(temp == 1)
	{
		wTemp = (INT32U)((wSeed & 0x00ff0000) >> 16);
	}
	else if(temp == 2)
	{
		wTemp = (INT32U)((wSeed & 0x0000ff00) >> 8);
	}
	else
	{
		wTemp = (INT32U)(wSeed & 0x000000ff);
	}

	SB1 = (INT32U)(( MASK & 0x000003FC) >> 2);
	SB2 = (INT32U)((( MASK & 0x7F800000) >> 23) ^ 0xA5);
	SB3 = (INT32U)((( MASK & 0x001FE000) >> 13) ^ 0x5A);
	iterations = (INT32U)(((wTemp ^ SB1) & SB2) + SB3);

	for( jj = 0; jj < iterations; jj++ )
	{
		wTemp = ((wLastSeed & 0x40000000) / 0x40000000) ^ 
		((wLastSeed & 0x01000000) / 0x01000000) ^
		((wLastSeed & 0x1000) / 0x1000) ^ ((wLastSeed  & 0x04) / 0x04);

		wLSBit = (wTemp & 0x00000001) ;
		wLastSeed = (INT32U)(wLastSeed << 1);    /* Left Shift the bits */
		wTop31Bits = (INT32U)(wLastSeed & 0xFFFFFFFE) ;
		wLastSeed = (INT32U)(wTop31Bits | wLSBit);
	}

	if (MASK & 0x00000001)
	{
		wTop31Bits = ((wLastSeed & 0x00FF0000) >>16) |
		((wLastSeed & 0xFF000000) >> 8) |
		((wLastSeed & 0x000000FF) << 8) |
		((wLastSeed & 0x0000FF00) <<16);
	}
	else
	{
		wTop31Bits = wLastSeed;
		wTop31Bits = wTop31Bits ^ MASK;
	}

	return( wTop31Bits );
}

//BOOT��
#define D_MASK 0x21763702  

void  BootSecurityAccess_vogKeyGenerate(void)
{
	INT32U cSeed = 0;
	INT32U cKey = 0;
	
	cSeed = (((INT32U)Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[0]) << 24) | \
			(((INT32U)Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[1]) << 16) | \
			(((INT32U)Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[2]) << 8) | \
			(((INT32U)Boot_SecurityAccess_stgOutInfo.u1SecLvSeed[3]) << 0);
		
	cKey = GENERIC_ALGORITHM(cSeed,D_MASK);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[0] = (INT8U)(cKey >> 24);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[1] = (INT8U)(cKey >> 16);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[2] = (INT8U)(cKey >> 8);
	Boot_SecurityAccess_stgOutInfo.u1SecLvKey[3] = (INT8U)(cKey >> 0);

}


void Sys_WriteUdsSecurityAccessTime(INT8U accessTime)
{
    Srvl_WriteMemIndexData(EN_MemIndex_BOOTUdsSecurityAccessTimes, &BootTpTxInfoStruct.cDataBuf[3], D_BOOTUdsSecurityAccessTimes_Len_1);
}

INT8U Sys_ReadUdsSecurityAccessTime(void)
{
    INT8U u8Temp=0;

    Srvl_ReadMemIndexData(EN_MemIndex_BOOTUdsSecurityAccessTimes, &u8Temp, D_BOOTUdsSecurityAccessTimes_Len_1);
    return u8Temp;
}


BOOL Uds_AccessTimesLmt(void)
{
    BOOL lmtRes = FALSE;
    INT8U accessTimes = Sys_ReadUdsSecurityAccessTime();
    
    accessTimes++;
	if(accessTimes >= D_UDS_ACCESS_MAX_TIMES)
	{
		u1gSecurityAccessIsDelayEndFlg = FALSE;
		lmtRes = TRUE;
	}
	else
	{
	    Sys_WriteUdsSecurityAccessTime(accessTimes);
	}

	return lmtRes;
}

void BootDesc_vosSecAccessSendKey(void)
{
	BOOT_U8 Index;
	BOOT_BOOL bKeyMatch = TRUE;

	if(BootTpRxInfoStruct.wDataLength == Boot_SecurityAccess_MLVKEYNUM + 2)
	{
		BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
        if(BootSeedReceive == TRUE)
        {
    
            /* unlocked ״̬���յ�Key���24*/
            if(BootunlockStatus == TRUE)
            {
                BootDescNrc = (kBootDescNrcRequestSequenceError);
                return;
            }
            BootSecurityAccess_vogKeyGenerate();
            for(Index = 0; Index < Boot_SecurityAccess_MLVKEYNUM; Index++)
            {
                if(BootTpRxInfoStruct.cDataBuf[2 + Index] != Boot_SecurityAccess_stgOutInfo.u1SecLvKey[Index])
                {
                    bKeyMatch = FALSE;
                }
            }
            if(bKeyMatch)
            {
                Sys_WriteUdsSecurityAccessTime(0);
                RamSet(Boot_SecurityAccess_stgOutInfo.u1SecLvSeed, 0, Boot_SecurityAccess_MSEEDNUM);
                BootTpTxInfoStruct.wDataLength = 2;
                BootunlockStatus = TRUE;
                BootDescNrc = BootDescNrcOK;
            }
            else
            {
                /* Invalid Key, Denied */
                if(Uds_AccessTimesLmt() == FALSE)
                {
                    BootDescNrc = (kBootDescNrcInvalidKey);
                }
                else
                {
                    BootSeedReceive = FALSE;
                    BootDescNrc = (kBootDescNrcExceedNumOfAttempts);
                }
    
            }
        }
        else
        {
            BootDescNrc = (kBootDescNrcRequestSequenceError);
        }
    }
    else
    {
        BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
    }
}
void BootDescSecurityAccess(void)
{
	BOOT_U8 wIndex;
	BOOT_BOOL	cSecurityAccessSubFound = FALSE;
	BOOT_U8 u1tSubFun, u1tInfoLen;
	BOOL  Err = FALSE;
    
	if(BootTpRxInfoStruct.cCANIDIndex == BOOT_RX_MSG_PHYSICAL)
	{	
		u1tInfoLen = (BOOT_U8)BootTpRxInfoStruct.wDataLength;
		u1tSubFun = BootTpRxInfoStruct.cDataBuf[1] & 0x7f;
		if(u1tInfoLen == 1)
		{
			BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
			return;
		}
		if((u1tSubFun!=BOOT_DESC_SECURITY_ACCESS_REQUEST_EXTSEED)&&\
		(u1tSubFun!=BOOT_DESC_SECURITY_ACCESS_SEND_EXTKEY)&&\
		(u1tSubFun!=BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA)&&\
		(u1tSubFun!=BOOT_DESC_SECURITY_ACCESS_SEND_REPROGRA))
		{
			BootDescNrc = kBootDescNrcSubfunctionNotSupported;
			return ;
		}
		if(!(u1tInfoLen == 2 || u1tInfoLen == 6))
		{
			BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
			return;
		}
		/*27����֧�ֽ�ֹ�϶���Ӧλ*/
		if(0x80U == (BootTpRxInfoStruct.cDataBuf[1] & 0x80U))
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
			return;
		}
		
		/*��̻Ự������27 01��27 02����ʱ��BCM��ӦNRC7E(����Ҫ��)  */
		if((BOOT_SESN_PRGS == BootDescSession) && \
			((0x02U == (BootTpRxInfoStruct.cDataBuf[1] & 0xFFU)) || (0x01U == (BootTpRxInfoStruct.cDataBuf[1] & 0xFFU))))
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupportedInActiveSession);
			return;
		}


		for(wIndex = 0; wIndex < UBOUND(cBootDesSecurityAccessSubID); wIndex++)
		{
			if(cBootDesSecurityAccessSubID[wIndex] == u1tSubFun)
			{
				cSecurityAccessSubFound = TRUE;
			}
		}

		SecurityAccessLevel = 0;
		if(cSecurityAccessSubFound)
		{
			if(BootDescSession == BOOT_SESN_DS)
			{
				Err = TRUE;
			}
			else if( ((u1tSubFun == BOOT_DESC_SECURITY_ACCESS_REQUEST_EXTSEED) || \
			(u1tSubFun == BOOT_DESC_SECURITY_ACCESS_SEND_EXTKEY) ) && \
			(BootDescSession != BOOT_SESN_EXTDS) )
			{
				Err = TRUE;
			}
			else if(((u1tSubFun == BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA) || \
					 (u1tSubFun == BOOT_DESC_SECURITY_ACCESS_SEND_REPROGRA)) && \
					(BootDescSession != BOOT_SESN_PRGS))
			{
				Err = TRUE;
			}

			if(FALSE == Err)
			{	
				if(u1gSecurityAccessIsDelayEndFlg == TRUE)
				{
					if( (u1tSubFun == BOOT_DESC_SECURITY_ACCESS_REQUEST_EXTSEED) || \
					(u1tSubFun == BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA) )
					{
						BootDesc_stsSecLvl.CurrLvl = ((u1tSubFun + 1U) / 2U);
						SecurityAccessLevel = ((u1tSubFun + 1U) / 2U);
						BootDesc_vosSecAccessReqSeed();
					}
					else if( (u1tSubFun == BOOT_DESC_SECURITY_ACCESS_SEND_EXTKEY) || \
					(u1tSubFun == BOOT_DESC_SECURITY_ACCESS_SEND_REPROGRA) )
					{
						if(BootSeedReceive == TRUE)
						{
							SecurityAccessLevel = (u1tSubFun / 2u);
							BootDesc_vosSecAccessSendKey();
						}
						else
						{
							BootDescNrc = (kBootDescNrcRequestSequenceError);
						}
					}
					else
					{
						BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
					}
				}
				else
				{
					BootDescNrc = (kBootDescNrcTimeDelayNotExpired);
				}
			}
			else
			{
				BootDescNrc = (kBootDescNrcSubfunctionNotSupportedInActiveSession);
			}
		}
		else
		{
			BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
		}
	}
	else
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
	}
}


static void ComCtrlComm(INT8U ComMsgType, INT8U ComCtrlVal)
{
	BootTpTxInfoStruct.wDataLength = 2;
	BootDescNrc = BootDescNrcOK;
}
void ComCtrlRxAndTxEnable(INT8U ComMsgType)
{
	INT8U ComCtrlVal = 0;
	ComCtrlComm(ComMsgType, ComCtrlVal);
}
void ComCtrlRxEnableTxDisable(INT8U ComMsgType)
{
	INT8U ComCtrlVal = 0;
	ComCtrlComm(ComMsgType, ComCtrlVal);
}
void ComCtrlRxDisableAndTxEnable(INT8U ComMsgType)
{
	INT8U ComCtrlVal = 0;
	ComCtrlComm(ComMsgType, ComCtrlVal);
}
void ComCtrlRxAndTxDisable(INT8U ComMsgType)
{
	INT8U ComCtrlVal = 0;
	ComCtrlComm(ComMsgType, ComCtrlVal);
}



/********************************************************************
* �������ƣ�DescCommunicationControl
* �������������ͨ�ſ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescCommunicationControl(void)
{
	INT8U cCtrlSubFuncIDIndex, cCtrlSubFuncID;
	INT8U cCtrlSubFuncIDFound = FALSE;
	cCtrlSubFuncID = (BootTpRxInfoStruct.cDataBuf[1] & 0x7F);
	if(3 != BootTpRxInfoStruct.wDataLength)
	{
		BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	if(BOOT_SESN_EXTDS != BootDescSession)
	{
		if(BootTpRxInfoStruct.cCANIDIndex == TST_BootPhysicalReqPEPS)
	    {
			BootDescNrc = kBootDescNrcServiceNotSupportedInActiveSession;
		}
		return;
	}
	for(cCtrlSubFuncIDIndex = 0; cCtrlSubFuncIDIndex < UBOUND(pComCtrlTbl); cCtrlSubFuncIDIndex ++)
	{
		if(pComCtrlTbl[cCtrlSubFuncIDIndex].eComCtrlType == (eCOM_CTL_TYPE)cCtrlSubFuncID)
		{
			cCtrlSubFuncIDFound = TRUE;
			if((BootTpRxInfoStruct.cDataBuf[1]&0x80u)==0u) /*�ǽ�ֹ�϶���Ӧ*/
			{
				pComCtrlTbl[cCtrlSubFuncIDIndex].ComCtrlInfo.ServiceProcess(BootTpRxInfoStruct.cDataBuf[2]);
			}
			return;
		}
	}
	if(cCtrlSubFuncIDFound == FALSE)
	{
	    if(BootTpRxInfoStruct.cCANIDIndex == TST_BootPhysicalReqPEPS)
	    {
            BootDescNrc = kBootDescNrcSubfunctionNotSupported;
	    }
	}
}


/*******************************************************************************
* �������ƣ�BootDescWrRdDIDOp
* ����������DID��д����
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 22 2E ����
*******************************************************************************/
void BootDescWrRdDIDOp(BOOT_U8 RWSlc)
{
	BOOT_U16 wDID;
	BOOT_BOOL cSubServiceFound = FALSE;
	tR_BOOTDID_INFO tWRBootDIDInfo;
	
    tWRBootDIDInfo.ServiceProcess = NULL;
    
	if((RWSlc==BOOT_DID_W)&&\
	(TST_BootPhysicalReqPEPS != BootTpRxInfoStruct.cCANIDIndex))
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootDescNrc = (BootDescNrcNoRsp);
		return;
	}
	
	if(BOOT_DID_R == RWSlc)
	{
        if(3 != BootTpRxInfoStruct.wDataLength)
        {
            BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
            return;
        }

	}
	else if(BootTpRxInfoStruct.wDataLength < 4)
	{
		BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
		return;
	}

	wDID = BootTpRxInfoStruct.cDataBuf[1];
	wDID <<= 8;
	wDID |= BootTpRxInfoStruct.cDataBuf[2];
	
	for(gRWBootDIDIndex = 0; gRWBootDIDIndex < UBOUND(pRWBootDIDInfoTbl); gRWBootDIDIndex++)
	{
		if(pRWBootDIDInfoTbl[gRWBootDIDIndex].sDID == wDID)
		{
			if(BOOT_DID_R == RWSlc) // Read DID
			{
				tWRBootDIDInfo.SessionAllow = pRWBootDIDInfoTbl[gRWBootDIDIndex].ReadDIDInfo.SessionAllow;
				tWRBootDIDInfo.SecuAcesReq = pRWBootDIDInfoTbl[gRWBootDIDIndex].ReadDIDInfo.SecuAcesReq;
				tWRBootDIDInfo.ServiceProcess = pRWBootDIDInfoTbl[gRWBootDIDIndex].ReadDIDInfo.ServiceProcess;
			}
			else // Write DID
			{
				tWRBootDIDInfo.SessionAllow = pRWBootDIDInfoTbl[gRWBootDIDIndex].WriteIDInfo.SessionAllow;
				tWRBootDIDInfo.SecuAcesReq = pRWBootDIDInfoTbl[gRWBootDIDIndex].WriteIDInfo.SecuAcesReq;
				tWRBootDIDInfo.ServiceProcess = pRWBootDIDInfoTbl[gRWBootDIDIndex].WriteIDInfo.ServiceProcess;
			}
			
			if(NULL != tWRBootDIDInfo.ServiceProcess)
			{
				cSubServiceFound = TRUE;
				
				if(tWRBootDIDInfo.SessionAllow & BootDescSession) // �����ͨ��
				{
					if(((BOOT_SA_TRUE == tWRBootDIDInfo.SecuAcesReq) && (TRUE == BootunlockStatus)) || \
							(BOOT_SA_FALSE == tWRBootDIDInfo.SecuAcesReq))
					{
                        
						tWRBootDIDInfo.ServiceProcess();
					}
					else
					{
						BootDescNrc = (kBootDescNrcAccessDenied);
					}
				}
				else
				{
					BootDescNrc = (kBootDescNrcSubfunctionNotSupportedInActiveSession);
				}
			}
			break;
		}
	}
	
	if(FALSE == cSubServiceFound)
	{
		BootDescNrc = (kBootDescNrcRequestOutOfRange);
	}
}

void BootDescReadDataByIdentifier(void)
{
	BootDescWrRdDIDOp(BOOT_DID_R);
}


void BootDescWriteDataByIdentifier(void)
{
	BootDescWrRdDIDOp(BOOT_DID_W);
}



/*******************************************************************************
* �������ƣ�BootDescRoutineControl
* �������������̿���
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 31 ����
*******************************************************************************/
void BootDescRoutineControl(void)
{
	BOOT_U16 wRoutineCtrlID;
	BOOT_U8  gBootRoutCtrlIDIndex;
	BOOT_U8  cRoutineCtrlTypeIndex;
	BOOT_BOOL cRoutineCtrlIDFound = FALSE;
	BOOT_BOOL cRoutineCtrlTypeFound = FALSE;
	const tBOOT_ROUTINTE_INFO *pBootRoutCtlInfo;

	if(TST_BootPhysicalReqPEPS != BootTpRxInfoStruct.cCANIDIndex)
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootDescNrc = BootDescNrcNoRsp;
		return;
	}
	if(BootTpRxInfoStruct.wDataLength < 4)
	{
		BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	wRoutineCtrlID = BootTpRxInfoStruct.cDataBuf[2];
	wRoutineCtrlID <<= 8;
	wRoutineCtrlID |= BootTpRxInfoStruct.cDataBuf[3];
	
	for(gBootRoutCtrlIDIndex = 0; gBootRoutCtrlIDIndex < UBOUND(pBootRoutineCtlTbl); gBootRoutCtrlIDIndex++)
	{
		if(pBootRoutineCtlTbl[gBootRoutCtrlIDIndex].sDID == wRoutineCtrlID)
		{
			cRoutineCtrlIDFound = TRUE;
			if(pBootRoutineCtlTbl[gBootRoutCtrlIDIndex].SessionAllow & BootDescSession)
			{
				if((pBootRoutineCtlTbl[gBootRoutCtrlIDIndex].SecurityAllow == BOOT_SA_FALSE) ||\
				((BootunlockStatus == TRUE)&&(pBootRoutineCtlTbl[gBootRoutCtrlIDIndex].SecurityAllow == BOOT_SA_TRUE)))
				{
					for(cRoutineCtrlTypeIndex = 0; cRoutineCtrlTypeIndex < UBOUND(cBootDescRoutineControlTypeID); cRoutineCtrlTypeIndex++)
					{
						if(cBootDescRoutineControlTypeID[cRoutineCtrlTypeIndex] == (BootTpRxInfoStruct.cDataBuf[1] & 0x7f))
						{
							pBootRoutCtlInfo = &pBootRoutineCtlTbl[gBootRoutCtrlIDIndex].RoutineInfo[cRoutineCtrlTypeIndex];
							cRoutineCtrlTypeFound = TRUE;
							if(NULL == pBootRoutCtlInfo->ServiceProcess)
							{
								BootDescNrc = kBootDescNrcSubfunctionNotSupported;
							}
							else if(pBootRoutCtlInfo->ReqDatLen == (BootTpRxInfoStruct.wDataLength - 4)) // eg. 31 FF 0A 01 + Data; ����Ҫ -4
							{
								pBootRoutCtlInfo->ServiceProcess();
							}
							else
							{
								BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
							}
							return;
						}
					}
				}
				else
				{
					BootDescNrc = (kBootDescNrcAccessDenied);
				}
			}
			else
			{
				BootDescNrc = (kBootDescNrcServiceNotSupportedInActiveSession);
			}
			return;
		}
	}
	if(cRoutineCtrlIDFound == FALSE)
	{
		BootDescNrc = (kBootDescNrcRequestOutOfRange);
	}
	else if(cRoutineCtrlTypeFound == FALSE)
	{
		BootDescNrc = (kBootDescNrcSubfunctionNotSupported);
	}
}









/*******************************************************************************
* �������ƣ�BootDescRequestDownload
* ������������������
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 34 ����  ����ӦҪ֧�� NRC 11 12 13 22 33 31 7F
*******************************************************************************/
void BootDescRequestDownload(void)
{
	if(TST_BootPhysicalReqPEPS != BootTpRxInfoStruct.cCANIDIndex) // ������������ID ����Ӧ
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootDescNrc = BootDescNrcNoRsp;
		return;
	}

    if(BootTpRxInfoStruct.wDataLength < 5) // ���ݳ��Ȳ��� NRC13
    {
        BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
        return;
    }
	
	if(BOOT_SESN_PRGS != BootDescSession) // ���ڱ�̲�  NRC7F
	{
		BootDescNrc = kBootDescNrcServiceNotSupportedInActiveSession;
		return;
	}

	if(FALSE == BootunlockStatus) // ��ȫ����ûͨ�� NRC33
	{
	    BootDescNrc = (kBootDescNrcAccessDenied);
	    return;
	}

    /* get memory address */
    DownloadInfo.FileLogicStartAddr = ToolMake32Bit( BootTpRxInfoStruct.cDataBuf[3],
                                                     BootTpRxInfoStruct.cDataBuf[4],
                                                     BootTpRxInfoStruct.cDataBuf[5],
                                                     BootTpRxInfoStruct.cDataBuf[6]  );
    if(DownloadInfo.FileLogicStartAddr == 0x20006800u)
    {
    	DownloadInfo.FileLogicStartAddr = 0x10006800u;
    }
    else if (DownloadInfo.FileLogicStartAddr == 0xC001000)
    {
    	DownloadInfo.FileLogicStartAddr = 0x10006800u;
    }

    /* get memory length */
    DownloadInfo.BlockDataLen= ToolMake32Bit(    BootTpRxInfoStruct.cDataBuf[7],
                                                BootTpRxInfoStruct.cDataBuf[8],
                                                BootTpRxInfoStruct.cDataBuf[9],
                                                BootTpRxInfoStruct.cDataBuf[10] );
    if(D_FlashDrvCodeStart_Addr == DownloadInfo.FileLogicStartAddr) // ��ַ��FlashDriver����ĵ�ַ
    {
        DownloadAppCodeFlg = FALSE; // ��� ����App�����ʶ
        
        /* download of flash driver request */
        if((0 == DownloadInfo.BlockDataLen) || (DownloadInfo.BlockDataLen > FLASH_DRV_CODE_SIZE))
        {
            BootDescNrc = (kBootDescNrcRequestOutOfRange);
            return;
        }

        DownloadFlashDrvFlg = TRUE; // ���� ����FlashDrv��ʶ
        setFlashStep(EN_STEP_REQUESTDOWNLOAD_DRIVE);
    }
    else
    {
        if(getFlashStep() != EN_STEP_ERASE_FLASH) //��������APPǰδ����flash������������
        {
            BootDescNrc = kBootDescNrcUploadDownloadNotAccepted;
            return;
        }
        DownloadFlashDrvFlg = FALSE; // ��� ����FlashDrv��ʶ
        DownloadInfo.FileLogicStartAddr = DownloadInfo.FileLogicStartAddr + BOOT_APPCODE_CRC_VALUE_SIZEOF;
        //DownloadInfo.BlockDataLen = DownloadInfo.BlockDataLen - BOOT_APPCODE_CRC_VALUE_SIZEOF;
        if(TRUE == CheckAppCodeSectorStartAddr(DownloadInfo.FileLogicStartAddr)) // ��鴫�����ʼ��ַ�Ƿ���ȷ
        {
            DownloadAppCodeFlg = TRUE; // ���� ����App�����ʶ
            u32TempCRCValue = 0xFFFFFFFFul;
            u32CalculateCrc = 0xFFFFFFFFul;
            setFlashStep(EN_STEP_REQUESTDOWNLOAD_APP);
        }
        else
        {
            BootDescNrc = (kBootDescNrcUploadDownloadNotAccepted);  // NRC70
            return;            
        }
    }

    // 34������ ʣ������ݳ��� = �ļ����ݳ���
    DownloadInfo.BlockSurplusDataLen = DownloadInfo.BlockDataLen;
    
    // ��ȡһЩ��Ϣ, ��ǰ�ĵ�ַ�͵����ļ�����ʼ��ַ
    DownloadInfo.CurrentLogicAddr = DownloadInfo.FileLogicStartAddr;

    // ��ǰ�����кŸ���ʼֵ0
    DownloadInfo.CurrentSequenceCnt = 0;

    // ���������кŸ���ʼֵ1
    DownloadInfo.ExpectedSequenceCnt= 1;
    
    // ��ͬ�鴫�䳢�ԵĴ�������ʼֵ3
    DownloadInfo.SameBlockRetryTimesCnt = D_SameBlockRetryTimes;

    // ���������AppCode, ��������ص�ַ��ȡ��ǰ��Sector����󳤶�
    if(TRUE == DownloadFlashDrvFlg) 
    {
        DownloadInfo.SectorMaxLen = FLASH_DRV_CODE_SIZE;
    }
    else
    {
        if(TRUE == DownloadAppCodeFlg) // ����AppCode
        {
            // ��ȡSector��С
            DownloadInfo.SectorMaxLen = GetAppCodeSectorMaxLen(DownloadInfo.FileLogicStartAddr);

            // ��ȡ�ļ���ʼ��ַ��ȫ�ֵ�ַ
            DownloadInfo.FileGlobalStartAddr = GetGlobalAddr(DownloadInfo.FileLogicStartAddr);
            
            // ��ȡȫ�ֵ�ַ
            DownloadInfo.CurrentGlobalAddr = GetGlobalAddr(DownloadInfo.CurrentLogicAddr);
        }
    }
    

    //fill response data

    // DataFormatIdentifier default is 0x20 // bit7-bit4 �ǿ��С,bit3-bit0 �ǵ�ַ(��ʱ����,��0)
    BootTpTxInfoStruct.cDataBuf[1] = 0x20;
    // MaxNumberOfBlockLength 
    BootTpTxInfoStruct.cDataBuf[2] = ToolGetHiByte(BOOT_TP_RX_DATA_BUF_SIZE);
    BootTpTxInfoStruct.cDataBuf[3] = ToolGetLoByte(BOOT_TP_RX_DATA_BUF_SIZE);
    
    BootTpTxInfoStruct.wDataLength =  (BootTpTxInfoStruct.cDataBuf[1] >> 4) + 2u;
    BootDescNrc = BootDescNrcOK;    
    
}


INT16U DataNum = 0;
BOOT_U32 u32CalculateCrc = 0;
BOOT_U8 u8VertifyFlag = 0;

/*******************************************************************************
* �������ƣ�BootDescTransferData
* ��������������������
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 36 ���� ����ӦҪ֧�� NRC 11 12 13 22 33 31 7F
*******************************************************************************/
void BootDescTransferData(void)
{
    static INT8U FlashBlockCntFlag=0;
    
	if(TST_BootPhysicalReqPEPS != BootTpRxInfoStruct.cCANIDIndex) // ������������ID ����Ӧ
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootDescNrc = BootDescNrcNoRsp;
		return;
	}
	
	if(BootTpRxInfoStruct.wDataLength < 3)
	{
		BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
		return;
	}
    
	if(BOOT_SESN_PRGS != BootDescSession) // ���ڱ�̲�  NRC7F
	{
		BootDescNrc = kBootDescNrcServiceNotSupportedInActiveSession;
		return;
	}

    if(FALSE == BootunlockStatus) // ��ȫ����ûͨ�� NRC33
    {
        BootDescNrc = (kBootDescNrcAccessDenied);
        return;
    }

    DownloadInfo.CurrentDataLen = BootTpRxInfoStruct.wDataLength - 2; // ��ȥ 36 01 ����ID�����к� ��2Byte, �����ľ������ݳ���
    if(DownloadInfo.CurrentDataLen < 1 || DownloadInfo.CurrentDataLen > BOOT_TP_RX_DATA_BUF_SIZE) // ��������һ��, �����ݳ��������Buffer��С��Χ��,�������ݳ��Ȳ��� NRC13
    {
        BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
        return;
    }

    // �����count����
    if(BootTpRxInfoStruct.cDataBuf[1] == DownloadInfo.ExpectedSequenceCnt) // ��������кŵ������������к�
    {
        DownloadInfo.SameBlockRetryTimesCnt = D_SameBlockRetryTimes; // ���³�ʼ��Ϊ����Դ���
    }
    else // ��������кŲ��������������к�
    {
        /*JMCҪ������һ�������кſ���ͨ��*/
        if(((DownloadInfo.ExpectedSequenceCnt==0u)&&(BootTpRxInfoStruct.cDataBuf[1]==0xFF))||\
        ((DownloadInfo.ExpectedSequenceCnt!=0u)&&(BootTpRxInfoStruct.cDataBuf[1]==(DownloadInfo.ExpectedSequenceCnt-1u))))
        {
    		BootTpTxInfoStruct.cDataBuf[0] = 0x36 + 0x40u; 
            BootTpTxInfoStruct.cDataBuf[1] = DownloadInfo.CurrentSequenceCnt;
            BootTpTxInfoStruct.wDataLength = 2; 
            BootDescNrc = BootDescNrcOK;   

            DownloadInfo.SameBlockRetryTimesCnt = D_SameBlockRetryTimes; // ���³�ʼ��Ϊ����Դ���
            return;
        }
        else
        {
            if(DownloadInfo.SameBlockRetryTimesCnt) // ���ڳ��Դ�����Χ��,��������
            {
                DownloadInfo.SameBlockRetryTimesCnt --;
                BootDescNrc = (kBootDescNrcWrongBlockSequenceCounter); // �������ݿ�˳����� NRC73
                return;
            }
            else // ���Դ�����,���ظ���Ӧ
            {
                BootDescNrc = (kBootDescNrcTransferDataSuspended);// ����������ͣ NRC71
				DownloadAppCodeFlg = FALSE;
				DownloadFlashDrvFlg = FALSE;
                return;
            }
        }
    }

    
    // ����FlashDrv ���� AppCode �ж�
    if(TRUE == DownloadFlashDrvFlg) // ���� FlashDrv
    {
        if((0x00 == ReqDownloadFlashBlockCnt) && (0x00 == DownloadInfo.CurrentSequenceCnt)) // ���ص�һ����ʱ, �������ļ���Ϣ
        {
            //���ص�һ��ʱ����ʼ��CRC��ֵ
            u32TempCRCValue = 0xFFFFFFFFul;
            if(FALSE == CheeckFlashDrvIsValid()) // ������صĲ���Flash Drv�ļ�, ����Ӧ
            {
                diagServiceCurrent = 0x36;
                BootDescNrc = kBootDescNrcGeneralProgrammingFailure;
        
                return;
            }
        }

    
        BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME; // ����ʱ��
        if(PROG_REQ_OK == Prog_WriteFlashDrvToRam())// дFlashDrv��Ram
        {
            // �����������к� ��ֵ�� ��ǰ�����к�
            DownloadInfo.CurrentSequenceCnt = DownloadInfo.ExpectedSequenceCnt;
            DownloadInfo.ExpectedSequenceCnt ++;
			if(DownloadInfo.ExpectedSequenceCnt == 0)
			{
				//û�����Ϊ0�Ŀ飬
				//DownloadInfo.ExpectedSequenceCnt = 1;
			}
            
            // Sequence counter value of next transferData request
    		// ���ͨ��36���������ݣ��ڵȴ�д��flash�Ĺ�����,�յ���������Ϸ���
    		// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    		// 20170913 -- zyc
    		BootTpTxInfoStruct.cDataBuf[0] = 0x36 + 0x40u; 
            BootTpTxInfoStruct.cDataBuf[1] = DownloadInfo.CurrentSequenceCnt;
            
            BootTpTxInfoStruct.wDataLength = 2; 
            BootDescNrc = BootDescNrcOK;         
        }
        else
        {
    		// ���ͨ��36���������ݣ��ڵȴ�д��flash�Ĺ�����,�յ���������Ϸ���
    		// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    		// 20170913 -- zyc	
    		diagServiceCurrent = 0x36;
            BootDescNrc = kBootDescNrcGeneralProgrammingFailure;            
        }
        
    }
    else
    {
        if(TRUE == DownloadAppCodeFlg) // ����App����
        {
    		BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME; // ����ʱ��

    		if((FlashBlockCntFlag == 0u) && (0x00 == ReqDownloadFlashBlockCnt) && (0x00 == DownloadInfo.CurrentSequenceCnt)) // ���ص�һ����ʱ, �������ļ���Ϣ
    		{
    			//���ص�һ��Appcodeʱ����ʼ��CRC��ֵ
    			u32TempCRCValue = 0xFFFFFFFFul;

    			if(DownloadInfo.CurrentDataLen < BOOT_APPCODE_CRC_VALUE_SIZEOF)
    			{
    				BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
    				return;
    			}
    			else if(DownloadInfo.CurrentDataLen > BOOT_APPCODE_CRC_VALUE_SIZEOF)
    			{
    				DownloadInfo.CurrentDataLen = DownloadInfo.CurrentDataLen - BOOT_APPCODE_CRC_VALUE_SIZEOF;
    				DownloadInfo.BlockSurplusDataLen -=BOOT_APPCODE_CRC_VALUE_SIZEOF;
    				//DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen;
    				DataNum = 2 + BOOT_APPCODE_CRC_VALUE_SIZEOF;
    				Checksum_Crc32_CRCValue((INT8U*)&BootTpRxInfoStruct.cDataBuf[2], BOOT_APPCODE_CRC_VALUE_SIZEOF);
    				u32AppCompilerCrc = ConverINT8UToINT32U(BootTpRxInfoStruct.cDataBuf[2], \
    													BootTpRxInfoStruct.cDataBuf[3], \
    													BootTpRxInfoStruct.cDataBuf[4], \
    													BootTpRxInfoStruct.cDataBuf[5]);
    				u32CalculateCrc = 0xFFFFFFFFul;
    			}
    			else
    			{
    				Checksum_Crc32_CRCValue((INT8U*)&BootTpRxInfoStruct.cDataBuf[2], DownloadInfo.CurrentDataLen);
    				
    				u32AppCompilerCrc = ConverINT8UToINT32U(BootTpRxInfoStruct.cDataBuf[2], \
    													BootTpRxInfoStruct.cDataBuf[3], \
    													BootTpRxInfoStruct.cDataBuf[4], \
    													BootTpRxInfoStruct.cDataBuf[5]);

    				u32CalculateCrc = 0xFFFFFFFFul;

    				//DownloadInfo.BlockSurplusDataLen -= DownloadInfo.CurrentDataLen; // ����ʣ������ݳ���
    				DownloadInfo.CurrentGlobalAddr = GetGlobalAddr(DownloadInfo.CurrentLogicAddr);

    				DownloadInfo.CurrentSequenceCnt = DownloadInfo.ExpectedSequenceCnt;
    				if(DownloadInfo.ExpectedSequenceCnt == 0u)
    				{
    					FlashBlockCntFlag = 1;
    				}
    				else
    				{
    					FlashBlockCntFlag = 0;
    				}
    				DownloadInfo.ExpectedSequenceCnt ++;
    				BootTpTxInfoStruct.cDataBuf[0] = 0x36 + 0x40u;
    				BootTpTxInfoStruct.cDataBuf[1] = DownloadInfo.CurrentSequenceCnt;
    				BootTpTxInfoStruct.wDataLength = 2;
    				BootDescNrc = BootDescNrcOK;
    				return ;
    			}
    		}
    		else
    		{
    			DataNum = 2;
    		}

    		if(PROG_REQ_OK == Prog_WriteAppCodeToRom(DataNum)) // дAppCode��Rom
    		{
    			// �����������к� ��ֵ�� ��ǰ�����к�
    			DownloadInfo.CurrentSequenceCnt = DownloadInfo.ExpectedSequenceCnt;
    			
    			if(DownloadInfo.ExpectedSequenceCnt == 0u)
    			{
    				FlashBlockCntFlag = 1;
    			}
    			else
    			{
    				FlashBlockCntFlag = 0;
    			}

    			DownloadInfo.ExpectedSequenceCnt ++;
    			if(DownloadInfo.ExpectedSequenceCnt == 0)
    			{
    				//û�����Ϊ0�Ŀ飬
    				//DownloadInfo.ExpectedSequenceCnt = 1;
    			}

    			// Sequence counter value of next transferData request
    			// ���ͨ��36���������ݣ��ڵȴ�д��flash�Ĺ�����,�յ���������Ϸ���
    			// ֮ǰԭ����+0x40�ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    			// 20170913 -- zyc
    			BootTpTxInfoStruct.cDataBuf[0] = 0x36 + 0x40u;
    			BootTpTxInfoStruct.cDataBuf[1] = DownloadInfo.CurrentSequenceCnt;

    			BootTpTxInfoStruct.wDataLength = 2;
    			BootDescNrc = BootDescNrcOK;
		    }
    		else
    		{
    			// ���ͨ��36���������ݣ��ڵȴ�д��flash�Ĺ�����,�յ���������Ϸ���
    			// ֮ǰԭ������Ϸ���ᱻ�޸ĵ�, �ʴ˴�Ҫ��������һ�䴦��
    			// 20170913 -- zyc
    			BootDescNrc = kBootDescNrcGeneralProgrammingFailure;

    			FlashBlockCntFlag = 0;
    		}
    	}
        else
        {
    		BootDescNrc = kBootDescNrcRequestSequenceError;
        }
    }

}



/*******************************************************************************
* �������ƣ�BootDescRequestTransferExit
* �����������������˳�
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 37 ���� ����ӦҪ֧�� NRC 11 12 13 22 33 7F
*******************************************************************************/
void BootDescRequestTransferExit(void)
{
	BootDescNrc = BootDescNrcNoRsp;
	if(TST_BootPhysicalReqPEPS != BootTpRxInfoStruct.cCANIDIndex) // ������������ID ����Ӧ
	{
		BootTpRxState.engine = BOOT_kRxState_Idle;
		BootDescNrc = BootDescNrcNoRsp;
		return;
	}
	
	if(1U != BootTpRxInfoStruct.wDataLength) // 37�������ݳ��� = 1,�������ݳ��Ȳ��� NRC13
	{
		BootDescNrc = (kBootDescNrcIncorrectMessageLengthOrInvalidFormat);
		return;
	}
    
	if(BOOT_SESN_PRGS != BootDescSession) // ���ڱ�̲�  NRC7F
	{
		BootDescNrc = kBootDescNrcServiceNotSupportedInActiveSession;
		return;
	}

    if(FALSE == BootunlockStatus) // ��ȫ����ûͨ�� NRC33
    {
        BootDescNrc = (kBootDescNrcAccessDenied);
        return;
    }

	if((TRUE == DownloadAppCodeFlg || DownloadFlashDrvFlg) && 0 != DownloadInfo.BlockSurplusDataLen) //����δ�����꣬NRC24
    {
		BootDescNrc = (kBootDescNrcConditionsNotCorrect);
		return;
	}

	setFlashStep(EN_STEP_REQUESTEXITDOWNLOAD);
    BootTpTxInfoStruct.wDataLength = 1;
    BootDescNrc = BootDescNrcOK;
}


/********************************************************************
* �������ƣ�BootDescControlDTCSetting
* ������������Ͽ���TDC����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void BootDescControlDTCSetting(void)
{ 		
    /*ֻ֧��$03���ģʽ*/
	if(2 != BootTpRxInfoStruct.wDataLength)
	{
		BootDescNrc = kBootDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	if(BOOT_SESN_EXTDS != BootDescSession)
	{
		if(BootTpRxInfoStruct.cCANIDIndex == TST_BootPhysicalReqPEPS)
    	{
			BootDescNrc = kBootDescNrcServiceNotSupportedInActiveSession;
    	}
		else
		{	
			BootDescNrc = BootDescNrcNoRsp;	
		}
		return;
	}
	if(((BootTpRxInfoStruct.cDataBuf[1] & 0x7F) == BOOT_DESC_CONTROL_DTC_SETTING_ON) || \
	((BootTpRxInfoStruct.cDataBuf[1] & 0x7F) == BOOT_DESC_CONTROL_DTC_SETTING_OFF))
	{
	    //cDescControlDTCSetting = BootTpRxInfoStruct.cDataBuf[1] & 0x7F;
	    BootTpTxInfoStruct.wDataLength = 2;
	    if(BootTpRxInfoStruct.cDataBuf[1] & 0x80)
		{
			BootTpRxState.engine = BOOT_kRxState_Idle;
			BootTpTxState.engine = BOOT_kTxState_Idle;
			BootDescNrc = BootDescNrcNoRsp;
		}
		else
		{
			BootDescNrc = BootDescNrcOK;
		}
	}
	else
	{
	    if(BootTpRxInfoStruct.cCANIDIndex == TST_BootPhysicalReqPEPS)
	    {
	        BootDescNrc = kBootDescNrcSubfunctionNotSupported;
	    }
	}
}
/********************************************************************
* �������ƣ�BootDescSet31ResponsePending
* ������������Ͽ���TDC����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void BootDescSet31ResponsePending(void)
{
	BootTpTxInfoStruct.cDataBuf[0] = 0x71;
	BootDescResponsePending(); // 78 Pending
}
