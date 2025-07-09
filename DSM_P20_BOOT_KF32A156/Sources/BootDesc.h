#ifndef         _BOOTDESC_H
#define          _BOOTDESC_H
#include  "Common.h"


typedef          void (* BootDescPtr)(void);
typedef struct BOOT_Desc_CallBack
{
	BOOL bCheckFlag;
	BootDescPtr RespProcess;
}stBOOTDescCallBack;

typedef enum
{	
	en_Rountine0202Start = 0,
	enCallBackMax
}enBootDescCallBack;

#define			GetDatBufAndLen(pt)					(pt),	UBOUND(pt)

#define         BOOT_DESC_CYCTIME													5

#define 		BOOT_DESC_P2_CAN_SERVER_MAX                             			(50/BOOT_DESC_CYCTIME)
#define 		BOOT_DESC_P2_CAN_CLIENT_MAX                 						(150/BOOT_DESC_CYCTIME)
#define			BOOT_DESC_RspPendingTM			             						(3500/BOOT_DESC_CYCTIME)

//��ECU���͸���Ӧ����Ϊ0x78�ĸ���Ӧ�󣬵�ECU������Ӧ���ĵ�ʱ��Ҫ��
#define			BOOT_DESC_P2EX_CAN_SERVER_MAX             							(5000/BOOT_DESC_CYCTIME)
#define			BOOT_DESC_P2EX_CAN_CLIENT_MAX              							(5000/BOOT_DESC_CYCTIME)

#define 		BOOT_DESC_TIMER_100MS                                            	(100/BOOT_DESC_CYCTIME)
#define 		BOOT_DESC_TIMER_10S                                            		(10000/BOOT_DESC_CYCTIME)
#define 		BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME                     	(5000 / 100) // 5s = 50 * 100MS


#define 		BOOT_DESC_TESTER_PRESENT_ZERO_SUB_FUNC                           	0

#define         BOOT_DESC_ECU_HARD_REST                                             1
#define         BOOT_DESC_ECU_SOFT_REST                                             3


#define 	Boot_SecurityAccess_MCONSTANTNUM				   					4
#define 	Boot_SecurityAccess_MSEEDNUM				   		    			4
#define 	Boot_SecurityAccess_MLVKEYNUM				   	    				4
//��ȫ���ʴ���
#define     D_UDS_ACCESS_MAX_TIMES          3U


/* define Security Access Sub Service */
#define BOOT_DESC_SECURITY_ACCESS_REQUEST_EXTSEED                        0x01  
#define BOOT_DESC_SECURITY_ACCESS_SEND_EXTKEY                            0x02

#define BOOT_DESC_SECURITY_ACCESS_REQUEST_REPROGRA                       0x03  
#define BOOT_DESC_SECURITY_ACCESS_SEND_REPROGRA                          0x04



/* Define ControlDTCSetting sub service */
#define BOOT_DESC_CONTROL_DTC_SETTING_ON                            1
#define BOOT_DESC_CONTROL_DTC_SETTING_OFF                           2


#define BootDescNrcNoRsp                                                 (0x00)
#define BootDescNrcOK                                                    (0x01)
// 0x01 ~ 0x0F ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcGeneralReject                                        (0x10)
#define kBootDescNrcServiceNotSupported                                  (0x11)
#define kBootDescNrcSubfunctionNotSupported                              (0x12)
#define kBootDescNrcIncorrectMessageLengthOrInvalidFormat                (0x13)
// 0x15 ~ 0x20 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcBusyRepeatRequest                                    (0x21)
#define kBootDescNrcConditionsNotCorrect                                 (0x22)
// 0x23 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define	kBootDescNrcRoutineNotComplete                                 	 (0x23)
#define kBootDescNrcRequestSequenceError                                 (0x24)
// 0x27 ~ 0x30 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcRequestOutOfRange                                    (0x31)
// 0x32 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcAccessDenied                                         (0x33)
// 0x34 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcInvalidKey                                           (0x35)
#define kBootDescNrcExceedNumOfAttempts                                  (0x36)
#define kBootDescNrcTimeDelayNotExpired                                  (0x37)
// 0x38 ~ 0x4F reservedByExtendedDataLinkSecurityDocument, this range of values is reserved by ISO 15764 for Extneded data link security

#define kBootDescNrcImproperDownloadType								 (0x41)
#define kBootDescNrcCanntDownloadToSpecifiedAddress						 (0x42)
#define kBootDescNrcCanntDownloadNumberOfBytesRequested					 (0x43)
// 0x50 ~ 0x6F ISOSAEReserved, this range of values is reserved by this document for future definitin
#define kBootDescNrcUploadNotAccepted                           	 	 (0x50)
#define kBootDescNrcImproperUploadType								     (0x51)
#define kBootDescNrcCanntUploadFromSpecifiedAddress						 (0x52)
#define kBootDescNrcCanntUploadNumberOfBytesRequested					 (0x53)
#define kBootDescNrcSameDataWrite										 (0x66)

#define kBootDescNrcUploadDownloadNotAccepted                            (0x70)
#define kBootDescNrcTransferDataSuspended                                (0x71)
#define kBootDescNrcGeneralProgrammingFailure                            (0x72)
#define kBootDescNrcWrongBlockSequenceCounter                            (0x73)
// 0x74 ~ 0x77 ISOSAEReserved, this range of values is reserved by this document for future definitin
#define kBootDescNrcResponsePending                                      (0x78)
// 0x79 ~ 0x7D ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcIncorrectByteCountDuringBlockTransfer                (0x79)
#define kBootDescNrcServiceNotSupportedInActiveDiagnosticMode            (0x80)
#define kBootDescNrcRequestedUserPasswordCancelled            		     (0xF0)
#define kBootDescNrcSubfunctionNotSupportedInActiveSession               (0x7E)
#define kBootDescNrcServiceNotSupportedInActiveSession                   (0x7F)
// 0x80 ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin
#define kBootDescNrcRpmTooHigh                                           (0x81)
#define kBootDescNrcRpmTooLow                                            (0x82)
#define kBootDescNrcEngineIsRunning                                      (0x83)
#define kBootDescNrcEngineIsNotRunning                                   (0x84)
#define kBootDescNrcEngineRunTimeTooLow                                  (0x85)
#define kBootDescNrcTemperatureTooHigh                                   (0x86)
#define kBootDescNrcTemperatureTooLow                                    (0x87)
#define kBootDescNrcVehicleSpeedTooHigh                                  (0x88)
#define kBootDescNrcVehicleSpeedTooLow                                   (0x89)
#define kBootDescNrcThrottleSpeedTooHigh                                 (0x8A)
#define kBootDescNrcThrottleSpeedTooLow                                  (0x8B)
#define kBootDescNrcTransmissionRangeInNeutral                           (0x8C)
#define kBootDescNrcTransmissionRangeInGears                             (0x8D)
#define kBootDescNrcBrakeSwitchNotClosed                                 (0x8F)
#define kBootDescNrcShifterLeverNotInPark                                (0x90)
#define kBootDescNrcTorqueConverterClutchLocked                          (0x91)
#define kBootDescNrcVoltageTooHigh                                       (0x92)
#define kBootDescNrcVoltageTooLow                                        (0x93)
// 0x94 ~ 0xFE reservedForSpecificConditionsNotCorrect, this range of values is reserved by ISO 14229 for future definitin
#define kBootDownloadAppPrgCheckSumError                                 (0x94)

// 0xFF ISOSAEReserved, this range of values is reserved by ISO 14229 for future definitin



#define BOOTDESC_NEGATIVE_RESPONSE_SERVICE_ID                            (0x7F)

#define         BOOT_SESN_DS                                     1U      /* Default Session Ĭ�ϻỰ*/
#define         BOOT_SESN_PRGS                                   2U      /* Program Session ��̻���*/
#define         BOOT_SESN_EXTDS                                  4U      /* extendedDiagnosticSession  ��չ��ϻỰ*/
#define         BOOT_SESN_VMS                                    8U      /* vehicleManufacturerSpecific */
#define         BOOT_SESN_SSS                                    16U     /* systemSupplierSpecific */
#define			BOOT_RX_MSGBUFF_SID_LEN							(1)
#define			BOOT_RX_MSGBUFF_SN_LEN							(1)
#define			BOOT_RX_MSGBUFF_ADDR_LEN						(3)
#define			BOOT_RX_MSGBUFF_CS_LEN							(1)

#define			BOOT_RX_MSGBUFF_SID								(0)
#define			BOOT_RX_MSGBUFF_SN								(BOOT_RX_MSGBUFF_SID+1)
#define			BOOT_RX_MSGBUFF_ADDR_START						(BOOT_RX_MSGBUFF_SN+1)
#define			BOOT_RX_MSGBUFF_DATA_START						(BOOT_RX_MSGBUFF_ADDR_START+BOOT_RX_MSGBUFF_ADDR_LEN)


#define 		BOOT_APPCODE_CRC_VALUE_SIZEOF 					(8)

#define 	ConverINT8UToINT32U(hiHiByte,hiLoByte,loHiByte,loLoByte)       ((INT32U)((((INT32U)(hiHiByte))<<24)| \
                                                                     (((INT32U)(hiLoByte))<<16)| \
                                                                     (((INT32U)(loHiByte))<<8) | \
                                                                     ((INT32U)(loLoByte))))

/* �ƶ� routine ������� */
//#define     ROUTINESTATUSRECODE_CORRET              (0x00)
//#define     ROUTINESTATUSRECODE_INCORRET            (0x01)

/* �ղ� routine ������� */
#define     ROUTINESTATUSRECODE_CORRET              (0x01)
#define     ROUTINESTATUSRECODE_INCORRET            (0x02)


#define     D_FlashEraseAddrAndLen_Format           (0x44) // ������淶 31���� FF 00


typedef enum
{
	TST_BootPhysicalReqPEPS,
	TST_BootFunctionalReqMS,
	RX_Boot_NM,
} eRX_BOOTDESC_TYPE;


typedef struct
{
	BOOT_U8 u1RspSID;
	BOOT_U8 u1DID0;
	BOOT_U8 u1DID1;
} BootDesc_stLngTmRspInfo;

typedef enum
{
	eBOOT_SESSION_DEFAULT                = 0x01,
	eBOOT_SESSION_PROGRAM                = 0x02,
	eBOOT_SESSION_EXTENDED               = 0x03,
	eBOOT_SESSION_VEHICLEFACTURER        = 0x40,
	eBOOT_SESSION_SYSTEMSUPPLIER         = 0x60,
} eBOOT_SESSION_TYPE;

typedef enum
{
	eBOOT_SID_DIAGNOG_SESSION_CONTROL   				= 0x10,
	eBOOT_SID_ECU_HARD_RESET					  		= 0x11,
	eBOOT_SID_CLR_DIAGNOSTIC_DTC						= 0x14,
	eBOOT_SID_READ_DTC_INFORMATION						= 0x19,
	eBOOT_SID_READ_DATA_BY_IDENTIFIER   				= 0x22,
	eBOOT_SID_SECURITY_ACCESS					  		= 0x27,
	eBOOT_SID_COMMUNICATION_CONTROL						= 0x28,
	eBOOT_SID_WRITE_DATA_BY_IDENTIFIER					= 0x2e,
	eBOOT_SID_IOCONTROL_BY_IDENTIFIER			        = 0x2f,
	eBOOT_SID_ROUTINE_CONTROL							= 0x31,
	eBOOT_SID_REQUEST_DOWNLOAD							= 0x34,
	eBOOT_SID_TRANSFER_DATA								= 0x36,
	eBOOT_SID_REQUEST_TRANSFER_EXIT						= 0x37,
	eBOOT_SID_TESTER_PRESENT					  		= 0x3e,
	eBOOT_SID_CONTROL_DTC_SETTING			  		    = 0x85,
} eBOOT_SID_TYPE;
typedef struct
{
	eBOOT_SID_TYPE                eBOOT_SID;
	void                     (*pServerProcess)(void);
} tBOOT_DESC_INFO;

typedef enum
{
	BootDesc_enmSecNonLvl,
	BootDesc_enmSecBootLvl,
	BootDesc_enmSecLvl1,
	BootDesc_enmSecLvl2
}BootDesc_enSecLvl;
typedef struct
{
	BootDesc_enSecLvl CurrLvl;
	BootDesc_enSecLvl PreLvl;
}BootDesc_stSecLvl;
typedef struct
{
	BOOT_U8 u1SecLvSeed[Boot_SecurityAccess_MSEEDNUM];
	BOOT_U8 u1SecLvKey[Boot_SecurityAccess_MLVKEYNUM];
	BOOT_U8 u1SecLvConst[Boot_SecurityAccess_MCONSTANTNUM];
} Boot_SecurityAccess_stOutInfo;


#define     BOOT_DID_R                   0
#define     BOOT_DID_W                   1
#define     BOOT_SA_FALSE                0
#define     BOOT_SA_TRUE                 1
#define     __BOOTDIDNOTSUPPORTWRITE           0, BOOT_SA_FALSE, NULL
#define		__BOOTDIDNOTSUPPORTREAD			   0, BOOT_SA_FALSE, NULL



typedef struct
{
	BOOT_U8	SessionAllow;
	BOOT_U8	SecuAcesReq;
	void		(*ServiceProcess)(void);
} tR_BOOTDID_INFO;

typedef struct
{
	BOOT_U8	    SessionAllow;
	BOOT_U8	    SecuAcesReq;
	void		(*ServiceProcess)(void);
} tW_BOOTDID_INFO;

typedef struct
{
	BOOT_U16			sDID;
	BOOT_U8			    ReqDatLen;
	tR_BOOTDID_INFO     ReadDIDInfo;
	tW_BOOTDID_INFO     WriteIDInfo;
} tDESC_BOOTDID_INFO;

#define     __BOOTRIDNOTSUPPORT           {0,NULL}
typedef struct
{
	BOOT_U8         ReqDatLen;
	void                (*ServiceProcess)(void);
} tBOOT_ROUTINTE_INFO;

typedef	enum{
	Routinenotactivated,
	Routineinprogress,
	RoutinecompletedwithOK,
	RoutinecompletedNOK,
	RoutinestopOK,
}RoutineResultType;

typedef struct
{
	BOOT_U16         sDID;
	BOOT_U8         SessionAllow;
    INT8U             SecurityAllow; /*���������Ƿ���Ҫ��ȫ��֤,�����̵���������*/
	tBOOT_ROUTINTE_INFO     RoutineInfo[3];
} tBOOTDESC_ROUTINT_INFO;

typedef enum
{
    eRXENABLE_TXENABLE   = 0x00,
    eRXENABLE_TXDISABLE  = 0x01,
    eRXDISABLE_TXENABLE  = 0x02,
    eRXDISABLE_TXDISABLE = 0x03,
}eCOM_CTL_TYPE;

typedef struct
{
    INT8U             ReqDatLen;
    void                (*ServiceProcess)(INT8U ComMsgType);
}tCOMCTL_INFO;

typedef struct stDESCROUTINFO
{
    eCOM_CTL_TYPE       eComCtrlType;
//     INT8U             SessionAllow;
    tCOMCTL_INFO        ComCtrlInfo;
}tDESC_COM_INFO;       

// ������ص���Ϣ
typedef struct
{
    INT32U  SectorMaxLen; // ��¼�����󳤶�, ���ݴ������ʼ��ַ��ȡ, ���ڱȽ��жϴ�������ݳ����Ƿ񳬳���Ĵ�С��

    INT32U  FileStartAddr; // AppCode�ļ�����ʼ��ַ
    INT32U  FileDataLen; // ��һ��AppCode�ļ����ݴ�С, ��FF00 �����������ʱ��ȡ��
    INT32U  FileSurplusDataLen; // ������һ��AppCode�ļ�ʣ����������ݴ�С
    
    INT32U  BlockDataLen; // ÿ����ĳ���, 0x4000 - 0x7FFF��һ����; 0x088000 - 0x08BFFF��һ���� ...; ��34�����л�ȡ
    INT32U  BlockSurplusDataLen; // ÿ��Block���������, ����ÿ��Blockʣ�����������ݳ���
    INT16U  CurrentDataLen; // ��ǰ36����һ�δ�������ݳ���
    INT32U  FileLogicStartAddr; // �ļ�����ʼ��ַ,  34����ʱ��ȡ��, �߼���ַ
    INT32U  FileGlobalStartAddr; // �ļ�����ʼ��ַ,  34����ʱ��ȡ��, ȫ�ֵ�ַ
    INT32U  CurrentLogicAddr; // ��ǰ36����һ�δ������ʼ��ַ, ��Ҫÿ���ۼӼ���, �߼���ַ
    INT32U  CurrentGlobalAddr; // �߼���ַ ���ڵ� ȫ�ֵ�ַ
    INT8U   CurrentSequenceCnt; // 36�������ݴ�������к�, ����36�������п���
    INT8U   ExpectedSequenceCnt; // 36�������ݴ�������������к�, ����36�������п���
    INT8U   SameBlockRetryTimesCnt; // 36������ͬ���ݴ���鳢�Դ���Ĵ���, ���3��
    
}stDownloadInfo;


extern stDownloadInfo  DownloadInfo;


extern BOOT_U8 			BootDescSession;
extern BOOT_U8 			BootDescRespNoSend;
extern BOOT_U8 			BootDescTesterPresentTimer;
extern BOOT_U8 			BootDescPrevSession;
extern BOOT_U8 			BootDescTimer100ms;
extern BOOT_U16 			BootDescP4Timer;
extern BOOT_U16			BootDescTimer10s;


extern BOOT_BOOL			BootSeedReceive;
extern BOOT_BOOL			BootunlockStatus;

extern BootDesc_stSecLvl  BootDesc_stsSecLvl;
extern BOOT_BOOL			BootDescSessionChangedFlag;	
extern BOOT_BOOL 			BootDescECUHardRestReq;
           
extern Boot_SecurityAccess_stOutInfo  Boot_SecurityAccess_stgOutInfo;
extern BOOT_U16 			Boot_SecurityAccess_u2gRand;
extern volatile BOOT_U8 	BootDescNrc;
extern BOOT_U16    EraseFlashSectorNum;

extern BOOT_U32 CRCValue;
extern BOOT_U32 TempCRCValue;

extern BOOL    DownloadFlashDrvFlg;
extern BOOL    DownloadAppCodeFlg;

extern BOOT_U32 u32TempCRCValue;
extern BOOL    DownloadFlashDrvFlg;
extern BOOL    DownloadAppCodeFlg;
extern BOOT_U32 u32CalculateCrc;

void BootVersionWrite(void);

void   BootDescInit(void);
void   BootDescResponsePending(void);
void   BootDescTask(void);
void   BootDescSessionChanged(BOOT_U8	cPreSession, BOOT_U8 cNewSession);
void   BootDescDiagnosticSessionControl(void);
void   EcuHardReset(void);
void   BootDescEcuRest(void);
void 	BootDescTesterPresent(void);
void   BootDescSecurityAccess(void);

void 	BootDescDID_Read_FD41_PEPSStatus(void);
void   BootDescDID_Read_FD42_ReadFlashData(void);
void   BootDescDID_Read_FD43_WriteData(void);
void 	BootDescDID_Read_FD44_FlashOptSt(void);
void 	BootDescDID_Read_FD45_BootDesc_Index(void);


void	BootDescReadDataByIdentifier(void);
void   BootDescWriteDataByIdentifier(void);
void   BootDescRoutineControl(void);
void 	BootDescRequestDownload(void);
void 	BootDescTransferData(void);
void 	BootDescRequestTransferExit(void);

void ComCtrlRxAndTxEnable(INT8U ComMsgType);
void ComCtrlRxEnableTxDisable(INT8U ComMsgType);
void ComCtrlRxDisableAndTxEnable(INT8U ComMsgType);
void ComCtrlRxAndTxDisable(INT8U ComMsgType);
void DescCommunicationControl(void);
void BootDescControlDTCSetting(void);

#endif

