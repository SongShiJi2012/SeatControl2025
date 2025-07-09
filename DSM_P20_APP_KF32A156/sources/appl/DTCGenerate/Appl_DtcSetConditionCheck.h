#ifndef _DIAG_DTC_CONDITION_CHECK_H
#define _DIAG_DTC_CONDITION_CHECK_H

#include "Common.h"
#include "ecual_pins.h"
#include "DiagDTCGenerate.h"

typedef enum _POWER_STATUS_T_
{
	EN_PowerModeUnknown_Sts = 0U,
	EN_PowerLow_Sts,
	EN_PowerNormal_Sts,
	EN_PowerHigh_Sts,
	EN_PowerModeAll_Sts,
}PowerModeStatus_t;

#define D_ENABLE_UDS_SNAPSHOT       D_DISABLE //不 使能UDS快照记录

#define D_LF_ANT_DIAG_PERIOD        (5U * D_SYS_MS_TIME_BASE)

#define D_LF_ANT_STRENG_TEST_PERIOD (500U * D_SYS_MS_TIME_BASE)

#define D_DIAG_SNAPSHOT_QUEUE_SIZE  11U  //data + Cnt

#define D_DIAG_DTC_CODE_SIZE        3U

#define D_COMM_DIAG_START_INIT_TIME         (3U * D_SYS_SEC_TIME_BASE)
#define D_COMM_DIAG_VOLT_PERIOD             (5U * D_SYS_MS_TIME_BASE)
#define D_COMM_TIMEOUT_DIAG_INIT_TIME       (4000U * D_SYS_MS_TIME_BASE)
#define D_COMM_DIAG_VOLT_START_CNT          (500U / D_COMM_DIAG_VOLT_PERIOD)
#define D_COMM_DIAG_BUS_OFF_REC_TIME        (3U * D_SYS_SEC_TIME_BASE)

#define D_DIAG_LOAD_PERIOD_TIME        		(50U * D_SYS_MS_TIME_BASE)

#define D_TURN_LIGHT_COUNT                  (10u)

#define D_DTC_ON_TIME						(5000UL * D_SYS_MS_TIME_BASE)	

#define D_DTC_CRANK_TIME					(5000UL * D_SYS_MS_TIME_BASE)	

#define D_DTC_RESET_TIME					(5000UL * D_SYS_MS_TIME_BASE)	

#define D_DTC_VOT_TIME						(5000UL * D_SYS_MS_TIME_BASE)		

#define D_DTC_LIMPHOME_TIME					(1000UL * D_SYS_MS_TIME_BASE)	

#define D_DTC_NTC_SC						(1000UL)	//NTC短地时间
#define D_DTC_NTC_OC						(1000UL)	//NTC短电源或开路时间
#define D_DTC_NTC_UN						(1000UL)	//NTC不可信时间

#define D_DTC_OUTPUT_SC						(40UL)	//加热输出短地时间
#define D_DTC_OUTPUT_OC						(200UL)	//加热输出断路时间


#define D_DTC_PWM_SC						(40UL)	//通风PWM短地时间
#define D_DTC_PWM_OC						(200UL)	//通风PWM短电源或断路时间

#define D_HgihVotValue				(16500UL) /** 供电电压过高阈值 16V（+0.5V） **/
#define D_Hgih2NormalVotValue		(16000UL) /** 供电电压过高恢复阈值 16V（-0.5V） **/

#define D_LowVotValue				(8500UL) /** 供电电压过低阈值 9.0V（-0.5V）**/
#define D_Low2NormalVotValue		(9000UL) /** 供电电压过低恢复阈值 9.0V（+0.5V）**/

#define D_Vot_DTC_TIME				(2000UL)	/* 电压异常DTC检测故障设置、恢复持续时间 */


#define DTCStatusAvailabilityMask                                           0x09U /*support DTC status bit 0,4*/
/*! @brief 诊断DTC Mask配置 */
#define D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_ENABLE                          D_ENABLE
#define D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_THIS_OPERATION_CYCLE_ENABLE     D_DISABLE
#define D_UDS_DIAG_DTC_MASK_BIT_PENDING_DTC_ENABLE                          D_DISABLE
#define D_UDS_DIAG_DTC_MASK_BIT_CONFIRM_DTC_ENABLE                          D_ENABLE
#define D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_SINCE_LAST_CLEAR_ENABLE  D_DISABLE
#define D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_SINCE_LAST_CLEAR_ENABLE         D_DISABLE
#define D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_THIS_CYCLE_ENABLE        D_DISABLE
//#define D_UDS_DIAG_DTC_MASK_BIT_WARNING_INDICATOR_REQ_ENABLE                D_DISABLE
//Bit7 Warning Indicator 暂时不做，只有有报警输出的DTC才需要设置，没有则保持0

#if (D_GPIO_CONFIG_TABLE_VER == D_GPIO_CONFIG_TABLE_VER_20230114)
#define D_DTCTest   (0)
#else
#define D_DTCTest   (EN_MCU_PIN39_PWR_AD)
#endif

//主驾输出短地
#define D_DTC_DrHeatOutputGS 	En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit
//主驾输出开路
#define D_DTC_DrHeatOutputOp 	En_Dtc_DriverSeatHeatingOutputDisconnected
//副驾输出短地
#define D_DTC_PaHeatOutputGS 	En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit
//副驾输出开路
#define D_DTC_PaHeatOutputOp 	En_Dtc_PassengerSeatHeatingOutputDisconnected
//方向盘加热对地短路
#define D_DTC_3rdHeatOutputGS    En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit
//方向盘加热开路
#define D_DTC_3rdHeatOutputOp    En_Dtc_SteeringWheelHeatingOutputDisconnected

//主驾PWM短地/开路
#define D_DTC_DrVentPWMGS 	En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit
//主驾PWM短电源
#define D_DTC_DrVentPWMPS 	En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply

//副驾PWM短地/开路
#define D_DTC_PaVentPWMGS 	En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit
//副驾PWM短电源
#define D_DTC_PaVentPWMPS 	En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply

#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)

typedef enum DIAG_DTC_SNAP_RECORD_NUM_T
{
    EN_DTC_SNAP_RECORD_RESRVED = 0U,
    EN_DTC_SNAP_VEHICLE_INFO = 1U,
    EN_DTC_SNAP_ALL_RECORD_NUM
}DiagDtcSnapRecordNum_t;

typedef struct
{
    INT16U Snap_DataId;                     /*!< 快照数据ID */
	INT16U Snap_DataLen;					/*!< 快照数据长度 */
}DiagDtcSnapDID_t;

typedef struct DIAG_DTC_SNAP_CONFIG_T
{
	DiagDtcSnapDID_t	*did;
	INT16S				size;				/**< 快照DID个数 */
    DiagDtcSnapRecordNum_t Snap_RecordNum;  /*!< 快照数据记录号 */
}DiagDtcSnapConfig_t;


typedef struct DIAG_SNAPSHOT_QUEUE_T
{
	DiagDtcNameType_t Diag_DtcInx;							/*!< DTC索引 */
	INT16U			  Index;								/*!< 快照索引 */
	BOOL			  RAM_UpdataFlag;						/*!< RAM更新标志位 0：未更新，1：已更新 */
    INT8U Diag_SnapshotDat[D_DIAG_SNAPSHOT_QUEUE_SIZE];     /*!< 故障快照数据缓存 */
	
    /* ……可增加其他快照数据（其它快照暂不考虑） */
    INT8U Diag_SnapFrontInx;                                /*!< 故障快照前索引 */
    INT8U Diag_SnapRearInx;                                 /*!< 故障快照后索引 */
    INT8U Diag_SnapSize;                                    /*!< 故障快照存储数量 */
}DiagSnapshotQue_t;

#endif

//添加DTC监测使能及有关采取动作
typedef struct
{
	BOOL      monitorenable_DTC;
	BOOL      takenflg_DTC[En_DtcType_MaxNum];  
}ST_DTCCondInfo;
	

typedef union UDS_DTC_STATUS_MASK_T
{
    INT8U Diag_DtcByte;
    struct {
    	INT8U TstFailed					        :1;///该DTC最近的测试结果为失败
    	INT8U TstFailedThisOpCycle       		:1;///当前监视循环报告该DTC处于故障状态
    	INT8U PendingDTC                 		:1;///DTC在当前或前一个监视循环处于故障状态
    	INT8U ConfirmedDTC               		:1;///DTC在请求时经过确认
    	INT8U TstNotCmpltdSinceLstClr    	    :1;///自从上一次故障码清除后测试尚未完成
    	INT8U TstFailedSinceLstClr       		:1;///自从上一次故障码清除后测试至少失败一次
    	INT8U TstNotCmpltdThisOpCycle     	    :1;///本监视循环测试未完成
    	INT8U WrnngIndicatorRequested     	    :1;///与该DTC相关的报警指示灯的状态
    }UdsDtcMaskBits;
}UdsDTCStatusMaskBit_t;


typedef struct DIAG_DTC_MASK_DATA_T
{
    UdsDTCStatusMaskBit_t Diag_DtcMask;
    INT8U Diag_FailCnt;
    INT8U Diag_AgingCnt;
}DiagDtcMaskDat_t;

typedef struct DIAG_DTC_DATA_T
{
#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
    DiagSnapshotQue_t Diag_SnapDat;                           /*!< DTC快照数据 */
#endif
    DiagDtcMaskDat_t Diag_DtcMask[En_DtcType_MaxNum];         /*!< DTC掩码数据 */
}DiagDtcData_t;


typedef enum DIAG_COMM_VOLT_STATE_T
{
    EN_DIAG_COMM_LOW_VOLT_STA = 0U,     /*!< 诊断运行电压低 */
    EN_DIAG_COMM_NORMAL_VOLT_STA,       /*!< 诊断运行电压正常 */
    EN_DIAG_COMM_HIGH_VOLT_STA,         /*!< 诊断运行电压高 */
    EN_DIAG_COMM_ALL_VOLT_STA
}DiagCommVoltSta_t;

typedef enum _GPIO_SIGNAL_NAME_T
{
	EN_GPIO_ALL_NUM
}GpioSignalName_t;
typedef struct DIAG_BTS_HDIRVER_IS_CHECK_TBL_T
{
	DiagDtcNameType_t DtcName; 
	GpioSignalName_t GpioName;
	
	INT8U u8BtsHighDrvChip;
	INT8U u8BtsHighDrvChipChl;

	INT8U u8FaultSort;
	INT16U u16LoadDownImA;
	INT16U u16LoadUpImA;

	INT8U u16DigTimeout;
	
}strDiagBtsHDriverIsCheckTbl_t;

#define D_DiagBtsHDriver_Fault_NULL			(0U)
#define D_DiagBtsHDriver_Fault_OpenLoad		(1U)
#define D_DiagBtsHDriver_Fault_OverLoad		(2U)
#define D_DiagBtsHDriver_Fault_LackLoad	    (3U)


typedef struct
{
	INT8U BCM_PosLmpDig;
	INT8U BCM_FrntFogLmpDig;
	INT8U BCM_RearFogLmpDig;
	INT8U BCM_TurnIndicatorDig;
	INT8U BCM_reversinglightDig;
	INT8U BCM_BrakelightDig;
	INT8U BCM_DayRunningLampDig;
}Bcm_Dig_t;


typedef GpioLevel_t (*pGpioLevel)(GpioSignalName_t);


typedef enum DIAG_LOAD_TYPE_T
{
    EN_DIAG_LOAD_REARFOGLP = 0,  			/*后雾灯*/
	EN_DIAG_LOAD_POSLP1,				/*位置灯*/
	EN_DIAG_LOAD_RIGHTDIRLP, 			/*右转向灯*/
	EN_DIAG_LOAD_LEFTDIRLP,				/*左转向灯*/
	EN_DIAG_LOAD_FRONTLEFTFOGLP,		/*前左雾灯*/
	EN_DIAG_LOAD_FRONTRIGHTFOGLP,		/*前右雾灯*/
	EN_DIAG_LOAD_LEFTRIGHTFOGLP,		/*左转向灯*/	
	EN_DIAG_LOAD_RIGHTCORNERLP,			/*右转向灯*/	
	EN_DIAG_LOAD_DAYRUNLP,				/*日行灯*/
	EN_DIAG_LOAD_POSP2,					/*位置灯2*/
	EN_DIAG_LOAD_REVERSELP,				/*倒车灯*/ 
	EN_DIAG_LOAD_BRAKELP,				/*刹车灯*/ 
	EN_DIAG_LOAD_HIGHBEAMRLY,			/*远光灯继电器*/ 
	EN_DIAG_LOAD_LOWBEAMRLY,			/*近光灯继电器*/
	EN_DIAG_LOAD_MAX,					
}DiagLoadType_t;



typedef enum
{
    EN_ALARM_HEAT_NONE,         /* 无故障 */
    EN_ALARM_HEAT_TO_GND,       /* 短路地 */
    EN_ALARM_HEAT_TO_BAT,       /* 短路到电源或开路 */
    EN_ALARM_HEAT_NTC_OPENLOAD,     /* 加热NTC开路 */
    EN_ALARM_HEAT_UNCREDIBLE,   /* 不可信错误 */
    EN_ALARM_HEAT_MAX,
}en_Appl_SeatAlarmHeatType;
#define D_AdcBtsChlIs_IN0			(0U)
#define D_AdcBtsChlIs_IN1			(1U)
#define D_AdcBtsChlIs_ChlNum		(2U)

typedef struct DIAG_LOAD_T
{
	pGpioLevel 	 		GpioStatus;
	GpioSignalName_t 	GpioSignal;
	INT8U           	RlySta;
	INT8U           	DriveType;
	DiagDtcNameType_t   DiagOverCurrentOrSCG;
	DiagDtcNameType_t   DiagOpenLoadOrSCV;
	DiagDtcNameType_t   DiagOneMainOpenLoad;
	INT32U 				PeriodTs;
	INT32U 				DecTotalTs;
	INT8U 				LmpDigResult;
}DiagLoadDat_t;

typedef struct 
{
	INT32U CanId;	//can ID
	INT16U cycle;	//报文周期
	INT16U timeout;	//超时时间
	INT16U regain;	//超时恢复时间
}st_CanMSG_timePram;

typedef enum 
{
	EN_BCM_INDEX = 0,
	EN_GW_INDEX,
	EN_CAN_NODE_MAX,
}en_CAN_INDEX;

void Diag_ClearAllDtc(void);

void Diag_ClearDtcById(DiagDtcNameType_t enDtcIndex, INT8U num);

INT16U Diag_MatchDtcMaskNum(INT8U mask);

BOOL Diag_MatchDtcMaskCode(INT8U mask, INT8U dtcIndex, INT8U dtc[], INT8U dtcLen);

INT8U Diag_GetDtcMask(INT8U dtcIndex);

BOOL Diag_GetDtcCode(INT8U dtcIndex, INT8U * u8DtcCode);

INT8U Diag_FindDtcMask(INT8U dtc[], INT8U dtcLen);

BOOL Diag_DtcMaskSetClrOpt(DiagDtcNameType_t enDtcIndex, BOOL bDtcTestFailed);

INT8U Diag_getMonitorEnableCriteria(INT8U t_index);

void Diag_setReserFlg(INT8U flag);


void Diag_MonitorEnableCriteriaCheck(void);

void Diag_DtcRecordHandle(void);

BOOL Diag_BCM_PosLmpResult(void);

BOOL Diag_BCM_FrntFogLmpResult(void);

BOOL Diag_BCM_RearFogLmpResult(void);

BOOL Diag_BCM_TurnIndicatorResult(void);

BOOL Diag_BCM_ReversinglightResult(void);

BOOL Diag_BCM_DayRunningLampResult(void);

BOOL Diag_BCM_BrakelightResult(void);

INT8U GetLeftTurnLightError(void);

INT8U GetRightTurnLightError(void);

BOOL Diag_ReadVehSnapshotIdentification(INT8U *pSnapDat,INT16U *length);

BOOL Diag_GetDTCFlg(DiagDtcNameType_t t_type);
#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
BOOL Diag_ReadVehSnapData(INT8U u8DtcCode[3], INT8U recodeNumber, INT8U *pSnapDat, INT16U size, INT16U *length);
#endif

#endif

