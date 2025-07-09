#ifndef _H_DESC_
#define _H_DESC_


#include "DescConfig.h"

#ifdef		Desc_GLOBALS
#define		Desc_EXT
#else
#define		Desc_EXT        extern
#endif

//对ECU接收到诊断请求报文后，发出响应报文的时间要求
#define DESC_P2_CAN_SERVER_MAX                 (50UL / CANDRVCYCTIME) /* default : 10 */ /* Unit : Value * DescTask call cycle time ,ms; here : 10 * 5ms = 50ms */


//对ECU接收到诊断请求报文后，发出78响应报文的时间要求
#define DESC_P2_CAN_SERVER_TIME                 (30UL / CANDRVCYCTIME) /* default : 10 */ /* Unit : Value * DescTask call cycle time ,ms; here : 10 * 5ms = 50ms */


#define DESC_P2_CAN_CLIENT_MAX                 	(100UL / CANDRVCYCTIME)
#define DESC_RspPendingTM			           	(3500UL / CANDRVCYCTIME)

//当ECU发送负响应代码为0x78的负响应后，到ECU发出响应报文的时间要求
#define DESC_P2EX_CAN_SERVER_MAX               	(5000UL / CANDRVCYCTIME)
#define DESC_P2EX_CAN_CLIENT_MAX               	(5050UL / CANDRVCYCTIME)

#define DESC_DELETE_KEY_TIME                 	(30000UL / CANDRVCYCTIME)

#define DescVehSpdLimit                                               (3)

#define D_RWE2PROMTIME							(3000UL * D_SYS_MS_TIME_BASE)

/* -----------------------------------------------------------------------------
    &&&~ Negative response codes
 ----------------------------------------------------------------------------- */
#define DescNrcNoRsp                                                 (0x00)
#define DescNrcOK                                                    (0x01)

#define kDescNrcGeneralReject                                        (0x10)
#define kDescNrcServiceNotSupported                                  (0x11)
#define kDescNrcSubfunctionNotSupported                              (0x12)
#define kDescNrcIncorrectMessageLengthOrInvalidFormat                (0x13)
#define kDescNrcBusyRepeatRequest                                    (0x21)
#define kDescNrcConditionsNotCorrect                                 (0x22)
#define kDescNrcRequestSequenceError                                 (0x24)
#define	kDescNrcRoutineNotComplete                                 	 (0x23)
#define kDescNrcRequestOutOfRange                                    (0x31)
#define kDescNrcAccessDenied                                         (0x33)
#define kDescNrcInvalidKey                                           (0x35)
#define kDescNrcExceedNumOfAttempts                                  (0x36)
#define kDescNrcTimeDelayNotExpired                                  (0x37)
#define kDescNrcUploadDownloadNotAccepted                            (0x40)
#define kDescNrcImproperDownloadType								 (0x41)
#define kDescNrcCanntDownloadToSpecifiedAddress						 (0x42)
#define kDescNrcCanntDownloadNumberOfBytesRequested					 (0x43)
#define kDescNrcUploadNotAccepted                           	 	 (0x50)
#define kDescNrcImproperUploadType								     (0x51)
#define kDescNrcCanntUploadFromSpecifiedAddress						 (0x52)
#define kDescNrcCanntUploadNumberOfBytesRequested					 (0x53)
#define kDescNrcSameDataWrite										 (0x66)
#define kDescNrcTransferDataSuspended                                (0x71)
#define kDescNrcTransferAborted                                		 (0x72)
#define kDescNrcIllegalAddressInBlockTransfer                        (0x74)
#define kDescNrcIllegalByteCountInBlockTransfer                      (0x75)
#define kDescNrcIllegalBlockTransferType                        	 (0x76)
#define kDescNrcResponsePending                                      (0x78)
#define kDescNrcIncorrectByteCountDuringBlockTransfer                (0x79)
#define kDescNrcServiceNotSupportedInActiveDiagnosticMode            (0x80)
#define kDescNrcRequestedUserPasswordCancelled            		     (0xf0)

#define kDescNrcGeneralProgrammingFailure                            (0x72)
#define kDescNrcWrongBlockSequenceCounter                            (0x73)
#define kDescNrcSubfunctionNotSupportedInActiveSession               (0x7E)
#define kDescNrcServiceNotSupportedInActiveSession                   (0x7F)

#define kDescNrcRpmTooHigh                                           (0x81)
#define kDescNrcRpmTooLow                                            (0x82)
#define kDescNrcEngineIsRunning                                      (0x83)
#define kDescNrcEngineIsNotRunning                                   (0x84)
#define kDescNrcEngineRunTimeTooLow                                  (0x85)
#define kDescNrcTemperatureTooHigh                                   (0x86)
#define kDescNrcTemperatureTooLow                                    (0x87)
#define kDescNrcVehicleSpeedTooHigh                                  (0x88)
#define kDescNrcVehicleSpeedTooLow                                   (0x89)
#define kDescNrcThrottleSpeedTooHigh                                 (0x8A)
#define kDescNrcThrottleSpeedTooLow                                  (0x8B)
#define kDescNrcTransmissionRangeInNeutral                           (0x8C)
#define kDescNrcTransmissionRangeInGears                             (0x8D)
#define kDescNrcBrakeSwitchNotClosed                                 (0x8F)
#define kDescNrcShifterLeverNotInPark                                (0x90)
#define kDescNrcTorqueConverterClutchLocked                          (0x91)
#define kDescNrcVoltageTooHigh                                       (0x92)
#define kDescNrcVoltageTooLow                                        (0x93)
#define kDescNrcnoResponseFromSubnetComponent                        (0x25)

#define DESC_NEGATIVE_RESPONSE_SERVICE_ID                            (0x7f)


/* define session control sub service */
#define         SESN_DS                                     1U      /* Default Session */
#define         SESN_PRGS                                   2U      /* Program Session */
#define         SESN_EXTDS                                  4U      /* extendedDiagnosticSession  */
#define         SESN_VMS                                    8U      /* vehicleManufacturerSpecific */
#define         SESN_SSS                                    16U     /* systemSupplierSpecific */

#define      SESN_DE       SESN_DS|SESN_EXTDS
#define      SESN_DES      SESN_DS|SESN_EXTDS|SESN_SSS
#define      SESN_ES       SESN_EXTDS|SESN_SSS
#define      SESN_DPE      SESN_DS|SESN_PRGS|SESN_EXTDS
#define      SESN_EVS      SESN_EXTDS|SESN_VMS|SESN_SSS
#define      SESN_DEVS     SESN_DS|SESN_EXTDS|SESN_VMS|SESN_SSS
#define      SESN_DPEVS    SESN_DS|SESN_PRGS|SESN_EXTDS|SESN_VMS|SESN_SSS
#define      SESN_PE       SESN_PRGS|SESN_EXTDS
#define      SESN_PS       SESN_PRGS|SESN_SSS

#define      SESN_NULL     0

#define         SA_EXTDS    SESN_EXTDS
#define      	SA_DE       SESN_DS|SESN_EXTDS
#define         SA_ES       SESN_EXTDS|SESN_SSS
#define      	SA_DPE      SESN_DS|SESN_PRGS|SESN_EXTDS
#define         SA_EVS      SESN_EXTDS|SESN_VMS|SESN_SSS
#define         SA_DEVS     SESN_DS|SESN_EXTDS|SESN_VMS|SESN_SSS
#define      	SA_DPEVS    SESN_DS|SESN_PRGS|SESN_EXTDS|SESN_VMS|SESN_SSS
#define      	SA_PE       SESN_PRGS|SESN_EXTDS
#define         SA_PS       SESN_PRGS|SESN_SSS

#define      	SA_NULL     SESN_NULL



/* define Ecu Rest sub service */
#define DESC_ECU_HARD_REST                                          1
#define DESC_ECU_KEY_OFF_ON_REST                                    2
#define DESC_ECU_SOFT_REST                                          3
#define DESC_ENABLE_RAPID_POWER_SHUT_DOWN                           4
#define DESC_DISABLE_RAPID_POWER_SHUT_DOWN                          5


/* define Security Access Sub Service */
#define DESC_SECURITY_ACCESS_REQUEST_EXTSEED                        0x01  
#define DESC_SECURITY_ACCESS_SEND_EXTKEY                            0x02

#define DESC_SECURITY_ACCESS_REQUEST_REPROGRA                       0x03  
#define DESC_SECURITY_ACCESS_SEND_REPROGRA                          0x04


#define SECURITYACCESSDELAYVALUE								100   //Specified by S15,100*100ms = 10s 

/* define Tester Present sub service */
#define DESC_TESTER_PRESENT_ZERO_SUB_FUNC                           0

/* Define ControlDTCSetting sub service */
#define DESC_CONTROL_DTC_SETTING_ON                                 1
#define DESC_CONTROL_DTC_SETTING_OFF                                2

/* define Clear DTC Information DTC group */
#define DESC_CLEAR_ALL_DTC_INFORMATION                              (0x00ffffff)


/* define CAN TEST Type */
#define CANTestRequestMINLength                              2
#define CANTestRequestMAXLength                             33   


#define DESC_TIMER_100MS                                            20 /* unit: DescTask Call Cycle Time * Value, here 5 ms * 20 =  100ms */
#define DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME                     50 /* unit: 100ms, here 50 * 100 ms =  5s */

#define	Desc_mgClrDTC_P2ExTIMES							0x01//tms


typedef struct
{
	INT8U u1RspSID;//22/2E服务的正响应SID	
	INT8U u1DID0;//22/2E服务DID	
	INT8U u1DID1;//22/2E服务DID	
}Desc_stLngTmRspInfo;

typedef enum
{
    eSESSION_DEFAULT                = 0x01,
    eSESSION_PROGRAM                = 0x02,
    eSESSION_EXTENDED               = 0x03,
    eSESSION_VEHICLEFACTURER        = 0x40,
    eSESSION_SYSTEMSUPPLIER         = 0x60,
}eSESSION_TYPE;


typedef enum
{
    eSID_DIAGNOG_SESSION_CONTROL   				    = 0x10,
    eSID_ECU_HARD_RESET					  			= 0x11,
    eSID_CLR_DIAGNOSTIC_DTC							= 0x14,
    eSID_READ_DTC_INFORMATION						= 0x19,
    eSID_READ_DATA_BY_IDENTIFIER   					= 0x22,
    eSID_SECURITY_ACCESS					  		= 0x27,
    eSID_COMMUNICATION_CONTROL						= 0x28,
    eSID_WRITE_DATA_BY_IDENTIFIER					= 0x2e,
    eSID_IOCONTROL_BY_IDENTIFIER			        = 0x2f,
    eSID_ROUTINE_CONTROL							= 0x31,
    eSID_REQUEST_DOWNLOAD							= 0x34,
    eSID_TRANSFER_DATA								= 0x36,
    eSID_REQUEST_TRANSFER_EXIT						= 0x37,
    eSID_TESTER_PRESENT					  			= 0x3e,
    eSID_CONTROL_DTC_SETTING			  		    = 0x85,
    eSID_PERIOD_DID_READ                            = 0x2A,
	eSID_READ_MEMORY_BY_ADDR						= 0x23,
    eSID_CAN_TEST									= 0xB0,
}eSID_TYPE;

typedef enum
{
    eSID_DIAGNOG_SESSION_CONTROL_INDEX   			= 0,
    eSID_ECU_HARD_RESET_INDEX,
    
#if (SID14_CLRDESCINFO_EN == DESC_ENABLE)
    eSID_CLR_DIAGNOSTIC_DTC_INDEX,
#endif
#if (SID19_RDDTCINFO_EN == DESC_ENABLE)
    eSID_READ_DTC_INFORMATION_INDEX,
#endif
#if (SID22_READDID_EN == DESC_ENABLE)
    eSID_READ_DATA_BY_IDENTIFIER_INDEX,
#endif
#if (SID27_SECURITYACCESS_EN == DESC_ENABLE)
    eSID_SECURITY_ACCESS_INDEX,
#endif
#if (SID28_COMCTL_EN == DESC_ENABLE)
    eSID_COMMUNICATION_CONTROL_INDEX,
#endif
#if SID2E_WRITEDID_EN == DESC_ENABLE
    eSID_WRITE_DATA_BY_IDENTIFIER_INDEX,
#endif
#if (SID2F_IOCTRL_EN == DESC_ENABLE)
    eSID_IOCONTROL_BY_IDENTIFIER_INDEX,
#endif
#if (SID31_ROUTINECTRL_EN == DESC_ENABLE)
    eSID_ROUTINE_CONTROL_INDEX,
#endif
#if SID34_REQDWNLOAD_EN == DESC_ENABLE
    eSID_REQUEST_DOWNLOAD_INDEX,
#endif
#if SID36_TRANFDATA_EN == DESC_ENABLE
    eSID_TRANSFER_DATA_INDEX,
#endif
#if SID37_TRANFEXIT_EN == DESC_ENABLE
    eSID_REQUEST_TRANSFER_EXIT_INDEX,
#endif
    eSID_TESTER_PRESENT_INDEX,
#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
    eSID_CONTROL_DTC_SETTING_INDEX,
#endif
#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)
    eSID_READ_PERIODIC_ID_INDEX,
#endif

    eSID_CAN_TEST_INDEX,
}eSID_TYPE_INDEX;


/* 服务诊断信息 */
typedef struct
{
    eSID_TYPE                eSID;
    void                     (*pServerProcess)(void);
}tDESC_INFO;

/*Session 与Security Access信息结构体*/

typedef struct
{
	INT8U            		 SessionAllow;
	INT8U 				 SA_Allow;
}tDESC_SESS_SA_INFO;

typedef struct
{
	tDESC_SESS_SA_INFO		PhySessionSACfg;
	tDESC_SESS_SA_INFO		FucSessionSACfg;
}tDESC_SESSIONSACFG;

      
typedef enum
{
	Desc_enmSecNonLvl,
	Desc_enmSecExtLvl,
	Desc_enmSecProgLvl,
	Desc_enmSecIMMOLvl,
	Desc_enmSecDevelopLvl,
}Desc_enSecLvl;

typedef struct
{
	Desc_enSecLvl CurrLvl;
	Desc_enSecLvl PreLvl;
}Desc_stSecLvl;

Desc_EXT Desc_stSecLvl Desc_stsSecLvl;
Desc_EXT BOOL bKeyLearnFlag;



Desc_EXT volatile INT8U cDescSession;
Desc_EXT volatile INT8U cDescControlDTCSetting;
Desc_EXT volatile INT8U cDescRespNoSend;/* 还未回复Tester的标识 */
Desc_EXT volatile INT8U cDescTesterPresentTimer;
Desc_EXT volatile INT8U cStartRoutineControlFlag;
Desc_EXT volatile INT8U unlockStatus;
Desc_EXT volatile INT8U bSeedReceive;//返回seed标志
Desc_EXT volatile INT8U ProgramFlg; 
Desc_EXT volatile INT8U u1gTesterPrsntFlg;

Desc_EXT volatile INT8U cDescTimer100ms;
Desc_EXT volatile INT8U cDescSessionChangedFlag;
Desc_EXT volatile INT8U cDescPrevSession;

Desc_EXT volatile INT8U u1gSecurityAccessIsDelayEndFlg;

Desc_EXT volatile INT8U Desc_OpTimeLongerThanP2Flag;//置位意味着该诊断操作响应时间会超过P2_CAN_SERVER
Desc_EXT volatile Desc_stLngTmRspInfo Desc_stgLngTmRspInfo;

Desc_EXT volatile  INT8U u1gP2ExCntr;

Desc_EXT volatile  INT8U DescNrc;
Desc_EXT volatile  INT8U DescSuppressPosRspBit;           /* 子功能Bit7 */


Desc_EXT BOOL DiagResetWaitFlag;//复位需等待的标志，主要原因还是EEPROM处于忙
Desc_EXT INT32U DescRepeatRes;

typedef struct DESC_ECU_RESET_REQ
{
	INT8U cDescECUHardRestReq;
	INT8U cDescECUHardRestAnswerfg;
	INT8U cDescECUHardRestAnswerFnish;
	INT8U cDescECUHardRestEepromIdlefg;
}strDescECUResetReq;
extern strDescECUResetReq DescECUResetReq;
extern volatile INT8U cDescECUHardRestAnswerIndex;
/* 子功能Bit7获取 */
#define     DescSuppressRosRspBitSet()      (DescSuppressPosRspBit = ((TpRxInfoStruct.cDataBuf[1] & 0x80)?TRUE:FALSE))

Desc_EXT const tDESC_SESSIONSACFG pDescSessSAConfigTbl[];
Desc_EXT void DescInit(void);


Desc_EXT void DescTask(void);
Desc_EXT void DescSendNegResp(INT8U  cRespCode);
Desc_EXT void DescDiagnosticSessionControl(void);
Desc_EXT void DescSendPosResp(void);
Desc_EXT void DescEcuRest(void);
Desc_EXT void DescTesterPresent(void);
Desc_EXT void DescCANTest(void);
Desc_EXT BOOL DescSessionSA_CfgChk(eSID_TYPE_INDEX SenssionTypeIndex);
Desc_EXT BOOL DescCheckVehSpd(void);
Desc_EXT BOOL DescGetSeatMoveStatusFlg(void);
Desc_EXT INT8U DescGetcDescSession(void);

#endif /* _H_DESC_ */
