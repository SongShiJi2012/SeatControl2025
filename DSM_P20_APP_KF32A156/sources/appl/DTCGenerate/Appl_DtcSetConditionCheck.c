#include "Appl_DtcSetConditionCheck.h"
#include "uds_pub.h"
#include "DiagDTCGenerate.h"
#include "Appl_PowerMangeModel.h"
#include "Ecual_Can.h"
#include "App_ModelHeader.h"
#include "Rte_VfbInterface.h"
#include "MidRelay.h"
#include "CpuPeripheralInit.h"

#define D_JoinCom_HoldOnTime		(15UL*1000UL ) /*can 节点加入持续时间 15000ms*/
#define D_LostCom_HoldOnTime		(15UL*1000UL ) /*can 节点丢失持续时间 15000ms */
#define D_Busoff_CleanTime		    (8UL*100UL) /*can busoff 清零时间 800ms，干扰8次时间约为500~600ms*/
#define D_OutPutValid_HoldOnTime	(50UL) /* 输出保持时间 ms*/

#define D_SWAdhesion_HoldOnTime   	(120UL*1000UL) /*开关粘连时间 120s*/
#define D_RelayAdhesion_HoldOnTime   	(2UL*1000UL) /*继电器粘连时间 2s*/
#define D_HALLERROR_HoldOnTime 		(2UL*1000UL) /*霍尔丢失时间 2s */

static INT8U u8LeftTurnLightErrorFlag = 0x0u;
static INT8U u8RightTurnLightErrorFlag = 0x0u;
static INT8U s_MonitorEnableCriteria[En_DtcType_MaxNum] = {0x00}; //DTC检测前置条件

static BOOL s_resetFlg = FALSE;

static ST_DTCCondInfo  stcondinfo_DTC = //DTC 使能设置条件及采取的动作
{
	TRUE,
	{0},
};

#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)

static const DiagDtcSnapDID_t Diag_SnapDid[] =
{
	{
		0x3190,
		2,
	},
	{
		0x3191,
		6,
	},
	{
		0x3192,
		2,
	}
	
};

static const DiagDtcSnapConfig_t Diag_SnapConfigList =
{
	Diag_SnapDid,
	sizeof(Diag_SnapDid) / sizeof(DiagDtcSnapDID_t),
	EN_DTC_SNAP_VEHICLE_INFO,
};


static DiagSnapshotQue_t Diag_SnapQueue[] =
{
//	{En_Dtc_Batteryvoltageistoolow, 							0, FALSE, {0, }, },
//	{En_Dtc_Batteryvoltageistoohigh, 							1, FALSE, {0, }, },
//	{En_Dtc_DSMCBUSOFF, 										2, FALSE, {0, }, },
//	{En_Dtc_DSMCLimpHome, 										3, FALSE, {0, }, },
	/*{En_Dtc_HeatingMat1SC, 										4, FALSE, {0, }, },
	{En_Dtc_HeatingMat1OC, 										5, FALSE, {0, }, },
	{En_Dtc_SensorNTC1SCN, 										6, FALSE, {0, }, },
	{En_Dtc_SensorNTC1SCS, 										7, FALSE, {0, }, },
	{En_Dtc_SensorNTC1OutOfRange, 								8, FALSE, {0, }, },
	{En_Dtc_HeatingMat2SC, 										9, FALSE, {0, }, },
	{En_Dtc_HeatingMat2OC,   	   								10, FALSE, {0, }, },
	{En_Dtc_SensorNTC2SC,       	   							11, FALSE, {0, }, },
	{En_Dtc_SensorNTC2OC,   	   								12, FALSE, {0, }, },
	{En_Dtc_SensorNTC2OutOfRange,   	   	   					13, FALSE, {0, }, },
	{En_Dtc_VentilationFanPowerSupplySC,   						14, FALSE, {0, }, },
	{En_Dtc_VentilationFan2PowerSupplySC,   	   				15, FALSE, {0, }, },
	{En_Dtc_VentilationFanPowerSupplyOutOfRange,  				16, FALSE, {0, }, },
	{En_Dtc_VentilationFan2PowerSupplyOutOfRange, 				17, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Height_SW_adhesion,  						18, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Length_SW_adhesion,  						19, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Cushion_Front_Height_Angle_SW_adhesion,  	20, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Backrest_Recline_SW_adhesion,  				21, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Height_MotorHALLError,  					22, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Length_MotorHALLError,  					23, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Cushion_Front_Height_Angle_MotorHALLError,  24, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Backrest_Recline_MotorHALLError,  			25, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Height_Relay_Error,  						26, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Length_Relay_Error,  						27, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Cushion_Front_Height_Angle_Relay_Error,  	28, FALSE, {0, }, },
	{En_Dtc_DR_Seat_Backrest_Recline_Relay_Error,  				29, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Height_UP_DN_SW,  							30, FALSE, {0, }, },
	{En_Dtc_PASeat_Length_SW_adhesion,  						31, FALSE, {0, }, },
	{En_Dtc_PA_Seat_LegRest_Front_UP_DN_SW,  					32, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Backrest_Recline_SW_adhesion,  				33, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Height_MotorHALLError,  					34, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Length_MotorHALLError,  					35, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Cushion_Front_Height_Angle_MotorHALLError,  36, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Backrest_Recline_MotorHALLError,  			37, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Height_Relay_Error,  						38, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Cushion_Front_Height_Angle_Relay_Error,  	40, FALSE, {0, }, },
	{En_Dtc_PA_Seat_Backrest_Recline_Relay_Error,  				41, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithBDCU,  						42, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithESP,  							43, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithICC,  							44, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithTBOX,  						45, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithDCU,  							46, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithCSS,  							47, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithEMS,  							48, FALSE, {0, }, },
	{En_Dtc_LostCommunicationWithTCM,  							49, FALSE, {0, }, },*/
};



#endif

static const st_CanMSG_timePram s_CanMSG_timePram[] = 
{
	{0x283, 	100,  	10 * 100, 	10 * 100},
	{0x2A7, 	20,  	10 * 20, 	10 * 20},
};

/*! @brief 诊断新操作周期指示 */
static BOOL Diag_NewPwrCycle = FALSE;
/*! @brief 新唤醒周期指示 */
static BOOL Diag_NewWakeCycle = FALSE;

/*! @brief 通讯类诊断工作运行指示 */
static BOOL Diag_CommDtcWorkInd = FALSE;
/*! @brief 通讯类诊断超时工作运行指示 */
static BOOL Diag_CommMsgTimeoutInd = FALSE;
/*! @brief 通讯诊断运行电压范围 */
/*
static const INT16U DiagCommVoltRange[(INT8U)EN_DIAG_COMM_ALL_VOLT_STA][2] = {
    {0, 85UL},  // 电压低 0.1v
    {80UL, 170UL}, // 电压正常 0.1v
    {165UL, 500UL} // 电压高 0.1v
};*/

strDiagBtsHDriverIsCheckTbl_t DiagBtsHDriverIsCheckTbl[] =
{


	/* 后雾灯灯过流或对地短路 */
		{
			En_Dtc_SupplyVoltageTooLow,
			D_DTCTest,
	
			1,
			D_AdcBtsChlIs_IN0,
	
			D_DiagBtsHDriver_Fault_OverLoad,
			0,
			9200, /*9.2A*/
		},
#if 0


	/***************************后雾灯***********************************/
	/* 后雾灯灯过流或对地短路 */
	{
		En_Dtc_RearFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* 后雾灯开路或对电源短路 */
	{
		En_Dtc_RearFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 后雾灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************位置灯1***********************************/
	/* 位置灯1过流或对地短路 */
	{
		En_Dtc_SideBeamLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* 位置灯1开路或对电源短路 */
	{
		En_Dtc_SideBeamLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		10,
		0,
	},


	/* 位置灯1损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},

	/***************************左转向灯***********************************/
	/* 左转向灯过流或对地短路 */
	{
		En_Dtc_LeftDIFlasher_OvercurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		8500, /*9.2A*/
	},

	/* 左转向灯开路或对电源短路 */
	{
		En_Dtc_LeftDIFlasher_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 左转向灯一灯损坏 */
	{
		En_Dtc_LeftDIFlasher_OneMainLampOpenLoad,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		100,
		4000,
	},


	/***************************右转向灯***********************************/
	/* 右转向灯过流或对地短路 */
	{
		En_Dtc_RightDIFlasher_OvercurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		8500, /*9.2A*/
	},

	/* 右转向灯开路或对电源短路 */
	{
		En_Dtc_RightDIFlasher_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 右转向灯一灯损坏 */
	{
		En_Dtc_RightDIFlasher_OneMainLampOpenLoad,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		100,
		4000,
	},

	/***************************左前雾灯***********************************/
	/*正常点亮值:0x3A8  ,936*/
	/* 左前雾灯电源短路 */
	{
		En_Dtc_LhFrFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400,
	},

	/* 左前雾灯对地短路 */
	{
		En_Dtc_LhFrFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 左前雾灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************右前雾灯***********************************/
	/* 右前雾灯过流或对地短路 */
	{
		En_Dtc_RhFrFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400,
	},

	/* 右前雾灯开路或对电源短路 */
	{
		En_Dtc_RhFrFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 右前雾灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************左角灯***********************************/
	/* 左角灯过流或对地短路 */
	{
		En_Dtc_Leftcornerlamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*5000mA*/
	},

	/* 左角灯开路或对电源短路 */
	{
		En_Dtc_Leftcornerlamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},


	/*左角灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************右角灯***********************************/
	/* 右角灯过流或对地短路 */
	{
		En_Dtc_Rightcornerlamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*4.4A*/
	},

	/* 右角灯开路或对电源短路 */
	{
		En_Dtc_Rightcornerlamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 右角灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************日间行车灯***********************************/
	/* 日间行车灯过流或对地短路 */
	{
		En_Dtc_DayDriveLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*4.4A*/
	},

	/* 日间行车灯开路或对电源短路 */
	{
		En_Dtc_DayDriveLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 日间行车灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************倒车灯***********************************/
	/* 倒车灯过流或对地短路 */
	{
		En_Dtc_ReverseLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* 倒车灯开路或对电源短路 */
	{
		En_Dtc_ReverseLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},


	/* 右角灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************刹车灯***********************************/
	/* 刹车灯过流或对地短路 */
	{
		En_Dtc_LBrakeLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* 刹车灯开路或对电源短路 */
	{
		En_Dtc_LBrakeLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* 右角灯损坏 */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},

	/***************************室顶灯***********************************/
	{
		En_Dtc_RoomLampShortcircuittoVbat,
		D_DTCTest,

		D_BtsHighDriverChip_RoomLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400,
	},
#endif
};

#define IO_DiagBtsHDriverIsCheckTbl_NUM			(sizeof(DiagBtsHDriverIsCheckTbl) / sizeof(DiagBtsHDriverIsCheckTbl[0]))


static BOOL bDiagDtcInd[En_DtcType_MaxNum];
static BOOL bDiagDtcAgingInd[En_DtcType_MaxNum] = {0};
static INT32U u32DiagDtcTestFailTs[En_DtcType_MaxNum] = {0};
static INT8U u32BtsErrorCount[En_DtcType_MaxNum] = {0};
static BOOL bBtsRet[En_DtcType_MaxNum] = {0};

static void GetSnapData(INT8U *msgBuf, INT8U length);

static void Diag_CanNetworkOpt(void);
static void Diag_CanNodeComLostOpt(void);
static void Diag_LinNodeFaultCheck(void);
static void Diag_VoltAbnromalOpt(void);
static void DSMDiag_vosSeatHeatDriveFaultCheck(void);
static void DSMDiag_vosSeatHeatSensorFaultCheck(void);
static void DSMDiag_vosSeatVentMotorFaultCheck(void);
static void DSMDiag_vosSeatVentPWMSignalFaultCheck(void);
static void DSMDiag_vosSeatAdjustProcFaultCheck(void);

//static void Diag_LinNodeComLostOpt(void);
//static void Diag_FeedbackFailure(void);
//static void Diag_SpecialDtc(void);
static void Diag_IsNewPwrCycle(void);
static void Diag_IsNewWakeCycle(void);
static void Diag_CommVoltCtrl(void);
static void Diag_CommLogicCtrl(void);
//static void Diag_TLE75RlyFaltOpt(void);


static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName);
static BOOL Diag_Bts_PosLp1Ctrl_RearFogLpCtrl_FaltOpt(void);
static BOOL Diag_Bts_RightDIFlasher_LeftDIFlasher_FaltOpt(void);
static BOOL Diag_Bts_LhFrFogLamp_RhFrFogLamp_FaltOpt(void);
static BOOL Diag_Bts_LeftRightCornerLp_FaltOpt(void);
static BOOL Diag_Bts_ReverseLpBrakeLp_FaltOpt(void);
static BOOL Diag_Bts_DayRunLpPosLp_FaltOpt(void);
static BOOL Diag_Bts_DOME_LAMP_FaltOpt(void);

//static void Diag_BtsHighDriversChipFaultOpt(void);
//static void Diag_OutReserveratureFaultOpt(void);

void Diag_setMonitorEnableCriteria(INT8U t_start, INT8U t_end, INT8U flag);
void Diag_Initu32DiagDtcTestFailTs(INT8U t_start, INT8U t_end);


void Diag_DtcRecordHandle(void);

static BOOL Diag_BtsHighDriversChipSpeFaultCheck(DiagDtcNameType_t enDtcName);

static void Diag_SetDTCFlg(DiagDtcNameType_t t_type, BOOL flg);

/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_IsNewPwrCycle(void)
* @par 描述
       是否是新的电源操作周期
* @param[in] void
* @param[out] Diag_NewPwrCycle：新电源周期指示
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-10-31
************************************************************************************************************************
*/
static void Diag_IsNewPwrCycle(void)
{
	static enIgnSts PksPowerModePrev = 0;
	enIgnSts PksPowerMode = 0;
	INT8U msgBuf[8] = {0xFF};

	PksPowerMode = (enIgnSts)Rte_GetVfb_PowerMode();

	if( PksPowerModePrev != PksPowerMode)
	{
		if((PksPowerModePrev == enIgnSts_eOn) && (PksPowerMode == enIgnSts_eOff))// ON -> OFF 为一个点火周期
		{
			//Ecual_CanSendMsg(FRAME_TYPE_STD,0x739,8,msgBuf);
			Diag_NewPwrCycle = TRUE;
		}
		PksPowerModePrev = PksPowerMode;
	}
	else
	{
		Diag_NewPwrCycle = FALSE;
	}
	
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_IsNewWakeCycle(void)
* @par 描述
       判断是否为新的唤醒周期
* @param[in] void
* @param[out] Diag_NewWakeCycle：新唤醒周期指示
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-11-1
************************************************************************************************************************
*/

static void Diag_IsNewWakeCycle(void)
{
//	static SysPowerMode_t PwrModePrev = EN_SYS_NORMAL_MODE;
//	SysPowerMode_t PwrMode = EN_SYS_NORMAL_MODE;
//
//	PwrMode = Srvl_Pwr_GetPwrMode();
//	if( PwrModePrev != PwrMode)
//	{
//		PwrModePrev = PwrMode;
//		if(PwrModePrev != EN_SYS_SLEEP_MODE)
//		{
//			Diag_NewWakeCycle = TRUE;
//		}
//	}
//	else
//	{
//		Diag_NewWakeCycle = FALSE;
//	}

}


/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_CommVoltCtrl(void)
* @par 描述
       通讯诊断工作电压范围控制
* @param[in] DiagCommVoltRange：电压控制范围表
* @param[out] Diag_CommDtcWorkInd：通讯类诊断工作指示
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-11-4
************************************************************************************************************************
*/

static void Diag_CommVoltCtrl(void)
{
	Diag_CommDtcWorkInd = FALSE;
	if( (NmOsek_engCANAppComm == NmOsek_enmEnable) && (Nm_IsBusOff() == FALSE) )
	{
		Diag_CommDtcWorkInd = TRUE;
	}
}


/***********************************************************************************************
 * @function name:  Diag_SetDTCFlg(DiagDtcNameType_t t_type, BOOL flg)
 *
 * @description:	设置故障标志
 *
 * @input parameters:     类型
 *
 * @output parameters:     void
 *
 * @return:         
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-15
 ***********************************************************************************************/
static void Diag_SetDTCFlg(DiagDtcNameType_t t_type, BOOL flg)
{
	stcondinfo_DTC.takenflg_DTC[t_type] = flg;
}

/***********************************************************************************************
 * @function name:  Diag_GetDTCFlg(DiagDtcNameType_t t_type)
 *
 * @description:	获取故障标志
 *
 * @input parameters:     类型
 *
 * @output parameters:     故障标志
 *
 * @return:         
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-15
 ***********************************************************************************************/
BOOL Diag_GetDTCFlg(DiagDtcNameType_t t_type)
{
	return stcondinfo_DTC.takenflg_DTC[t_type];
}


/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_CommLogicCtrl(void)
* @par 描述
       通讯类诊断电压范围和初始化时间控制
* @param[in] Diag_NewWakeCycle：新唤醒周期指示
* @param[out] Diag_CommDtcWorkInd：通讯诊断工作指示
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-11-1
************************************************************************************************************************
*/

static void Diag_CommLogicCtrl(void)
{
}

/***********************************************************************************************
* @function name:   Diag_getMonitorEnableCriteria(INT8U t_index)
*
* @description:      获取DTC前置条件满足标志位
*
* @input parameters:	 t_index：DTC下标
*
* @output parameters:	  void
*
* @return:		   INT8U 标志位   			TRUE:满足条件  			FALSE:不满足条件
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-06-28
***********************************************************************************************/
INT8U Diag_getMonitorEnableCriteria(INT8U t_index)
{
	if (t_index < En_DtcType_MaxNum)
	{
		return s_MonitorEnableCriteria[t_index];
	}
}


/***********************************************************************************************
* @function name:  Diag_setMonitorEnableCriteria(INT8U t_start, INT8U t_end, INT8U flag)
*
* @description:    设置DTC前置条件满足标志位
*
* @input parameters:	 t_start：开始设置下标  t_end：结束下标（包含）     				flag：标志
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-06-28
***********************************************************************************************/
void Diag_setMonitorEnableCriteria(INT8U t_start, INT8U t_end, INT8U flag)
{
	INT8U i = 0;
	for (i = t_start; i < (t_end + 1); ++i)
	{
		s_MonitorEnableCriteria[i] = flag;
	}
}

/***********************************************************************************************
* @function name:  Diag_setReserFlg(INT8U flag)
*
* @description:    设置复位标志位
*
* @input parameters:  flag：复位标志
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-06-30
***********************************************************************************************/
void Diag_setReserFlg(INT8U flag)
{
	s_resetFlg = flag;
}


/***********************************************************************************************
* @function name:  Diag_MonitorEnableCriteriaCheck(void)
*
* @description:    DTC前置条件检查
*
* @input parameters:	 void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   10ms
*
* @author:			zjx
*
* @note:		   2023-06-28
***********************************************************************************************/
void Diag_MonitorEnableCriteriaCheck(void)
{

	static INT32U u32CycTs = 0;
	static INT8U sIGNStsPre = 0;//enIgnSts_eOff;
	static PowerModeStatus_t sPowerModePre = EN_PowerNormal_Sts;//EN_PowerNormal_Sts;
	static INT32U u32CrankTs = 0;	//非Crank档计时
	static INT32U u32ONTs = 0;		//ON档计时
	static INT32U u32ResetTs = 0; 	//MCU复位计时
	static INT32U u32VotTs = 0;		//电压异常计时

	INT8U sIGNStsCurr =0;// enIgnSts_eOff;
	PowerModeStatus_t sPowerModeCurr = EN_PowerNormal_Sts;//enIgnSts_eOff;

	BOOL condition_reset = FALSE; // MCU复位5s
	BOOL condition_crank = FALSE; // 电源不在crank或转到非crank状态5s
	BOOL condition_ON = FALSE; // 电源在ON状态5s
	BOOL condition_vot = FALSE; // 电压正常工作（9~16V）或电压异常恢复5S

	BOOL Diag280301Flag = FALSE; 	//诊断28服务禁止接收应用报文条件
	BOOL Diag280302Flag = FALSE; 	//诊断28服务禁止接收应用报文条件
	BOOL BUSOffFlag = FALSE;	//busoff条件
	BOOL LimphomeFlag = FALSE;	//Limphome条件

	BOOL DrHeatFlag = FALSE;	//主驾加热条件
	BOOL PaHeatFlag = FALSE;	//副驾加热条件
	BOOL SteerHeatFlag = FALSE;	//方向盘加热条件
	BOOL DrVentFlag = FALSE;	//主驾通风条件
	BOOL PaVentFlag = FALSE;	//副驾通风条件

	BOOL DrHeightCtrl = FALSE;				//主驾高度控制	
	BOOL DrLengthCtrl = FALSE;				//主驾纵向控制	
	BOOL DrBackrestCtrl = FALSE;			//主驾靠背控制	
	BOOL DrFrontAngleCtrl = FALSE;			//主驾前部角度控制	
	BOOL PaLengthCtrl = FALSE;				//副驾纵向控制	
	BOOL PaBackrestCtrl = FALSE;			//副驾靠背控制	

	INT8U   DrAdjustCfg =FALSE;    
	INT8U   PaAdjustCfg =FALSE;      
	INT8U   DrHeatVentCfg =FALSE;    
	INT8U   PaHeatVentCfg =FALSE;  
	INT8U   seatMassageCfg =FALSE;  
	INT8U   SteerHeatCfg = FALSE;

	INT8U DrMemoryCfg = FALSE;	//主驾迎宾配置
	INT8U PaMemoryCfg = FALSE;	//副驾迎宾配置

    INT8U   DrHeatCfg =FALSE;    /* 主驾加热配置字 */
    INT8U   PaHeatCfg =FALSE;    /* 副驾加热配置字 */
    INT8U   DrVentCfg =FALSE;    /* 主驾通风配置字 */
    INT8U   PaVentCfg =FALSE;    /* 副驾通风配置字 */

#if 0
	static INT16U testIn = 0;
	INT8U cData[8] = {0};
	INT16U cis = 0;
#endif

	if(CPU_TimerDiffTs(u32CycTs) < 10UL)
	{
		return;
	}
	u32CycTs = D_HAL_GET_CUR_MS_TS();

	if(s_resetFlg == TRUE)
	{
		s_resetFlg = FALSE;
		u32ResetTs = D_HAL_GET_CUR_MS_TS();
	}

	DrMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	PaMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	
	DrAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	PaAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	DrHeatVentCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig);
	PaHeatVentCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig);
	seatMassageCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageConfig);
	SteerHeatCfg = Srvl_getSystemConfigPram(EN_SteerHeat_SysCfg);

    DrHeatCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeatFlg);
    DrVentCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentFlg);
    PaHeatCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaHeatFlg);
    PaVentCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentFlg);

/* 配置字无效时，清除相应的DTC  				start */	
	if(DrAdjustCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion,8);
		Diag_ClearDtcById(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued,4);
		Diag_ClearDtcById(En_Dtc_DriverSeatHeightRegulatingMotorHallFault,4);
	}

    /* 6向调节 */
    if(DrAdjustCfg  == 1)
    {
        Diag_ClearDtcById(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault,1);
    }

	if(PaAdjustCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion,4);
		Diag_ClearDtcById(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued,2);
		Diag_ClearDtcById(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault,2);
	}
	
	if(DrHeatVentCfg == FALSE || DrHeatCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit,5);
	}

	if(DrHeatVentCfg == FALSE || DrVentCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit,2);
	}
	
	if(PaHeatVentCfg == FALSE || PaHeatCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit,5);
	}
    
	if(PaHeatVentCfg == FALSE || PaVentCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit,2);
	}
    
	if(seatMassageCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_MassageModuleVoltageTooLow,4);
	}
	
	if(SteerHeatCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit,5);
	}

	if(DrMemoryCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_DriverSeatHeightRegulatingMotorHallFault,4);
	}

	if(PaMemoryCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault,2);
	}
/* 配置字无效时，清除相应的DTC  				end */	
	
	//诊断控制DTC
	if (cDescControlDTCSetting != DESC_CONTROL_DTC_SETTING_ON)
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, (En_DtcType_MaxNum - 1), FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_CanBusOff, (En_DtcType_MaxNum - 1)); //重置计时器
		return;
	}
	
	//诊断28控制接收app报文
	if(ECUAL_CAN_IS_APP_RX_ENABLE() == TRUE)
	{
		Diag280301Flag = TRUE;
	}
	//诊断28控制接收网络报文
	if(OsekNm_GetOsekInOnStatus() == TRUE)
	{
		Diag280302Flag = TRUE;
	}
	//非busoff
	if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_CanBusOff))
	{
		BUSOffFlag = TRUE;
	}

	//非Limphome
	if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DsmNodeLimphome))
	{
		LimphomeFlag = TRUE;
	}

	if(CPU_TimerDiffTs(u32ResetTs) > D_DTC_RESET_TIME)//MCU复位后延时5秒
	{
		condition_reset = TRUE;
	}
	
	sIGNStsCurr = Rte_GetVfb_PowerMode(); //当前电源档位
	/*电源档位不在crank或转到非crank状态5s之后 */
	if( enPowerModeSts_EN_CRANK == sIGNStsCurr)
	{
		u32CrankTs = D_HAL_GET_CUR_MS_TS();
		sIGNStsPre = sIGNStsCurr;
	}
	else
	{
		if(sIGNStsPre == enPowerModeSts_EN_CRANK)
		{
			if(CPU_TimerDiffTs(u32CrankTs) < D_DTC_CRANK_TIME)
			{
				
			}
			else
			{
				sIGNStsPre = sIGNStsCurr;
				condition_crank = TRUE;
			}
		}
		else
		{
			sIGNStsPre = sIGNStsCurr;
			condition_crank = TRUE;
		}
	}
	/*电源档位ON档状态5s之后 */
	if( enPowerModeSts_EN_ON != sIGNStsCurr)
	{
		u32ONTs = D_HAL_GET_CUR_MS_TS();
	}
	else
	{
		if(CPU_TimerDiffTs(u32ONTs) < D_DTC_CRANK_TIME)
		{
			
		}
		else
		{
			condition_ON = TRUE;
		}
		
	}
	//主驾正在加热
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_DrHeat())
	{
		DrHeatFlag = TRUE;
	}
	//副驾正在加热
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_PaHeat())
	{
		PaHeatFlag = TRUE;
	}
	//方向盘正在加热
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_ThirdHeat())
	{
		SteerHeatFlag = TRUE;
	}
	//主驾正在通风
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_DrVent())
	{
		DrVentFlag = TRUE;
	}
	//副驾正在通风
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_PaVent())
	{
		PaVentFlag = TRUE;
	}
	
	//主驾高度控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_DrHeightMotorCmd())
	{
		DrHeightCtrl = TRUE;
	}
	//主驾纵向控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_DrLengthMotorCmd())
	{
		DrLengthCtrl = TRUE;
	}
	//主驾靠背控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_DrBackMotorCmd())
	{
		DrBackrestCtrl = TRUE;
	}
	//主驾前部角度控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_DrFrontMotorCmd())
	{
		DrFrontAngleCtrl = TRUE;
	}
	//副驾纵向控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_PaLengthMotorCmd())
	{
		PaLengthCtrl = TRUE;
	}
	//副驾靠背控制有效
	if(EN_MOTOR_DEF != Rte_GetVfb_PaBackMotorCmd())
	{
		PaBackrestCtrl = TRUE;
	}
	
	sPowerModeCurr = Rte_GetVfb_VoltMode();
	/*电压不正常或电压异常恢复5S之内，不检测DTC*/
	if(EN_PowerNormal_Sts != sPowerModeCurr)
	{
		u32VotTs = D_HAL_GET_CUR_MS_TS();
		sPowerModePre = sPowerModeCurr;
	}
	else
	{
		if(sPowerModePre != sPowerModeCurr)
		{
			if(CPU_TimerDiffTs(u32VotTs) < D_DTC_VOT_TIME)
			{
				
			}
			else
			{
				sPowerModePre = sPowerModeCurr;
				condition_vot = TRUE;
			}
		}
		else
		{
			condition_vot = TRUE;
		}
	}
#if 0

	cData[0] = condition_reset;
	cData[1] = condition_crank;
	cData[2] = condition_vot;
	cData[3] = ++testIn >> 8;
	cData[4] = testIn;
	cData[5] = 0;
	cData[6] = 0;
	Ecual_CanSendMsg(FRAME_TYPE_STD, 0x666, 0x8u, cData);
#endif	


	/*电压DTC前置条件检测*/
	if((condition_reset == TRUE) && (condition_crank == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh); //重置计时器
	}

	/*bus off DTC前置条件检测*/
	if((condition_reset == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, En_Dtc_CanBusOff, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, En_Dtc_CanBusOff, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_CanBusOff, En_Dtc_CanBusOff); //重置计时器
	}

	/*Limphone DTC前置条件检测*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (Diag280302Flag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome); //重置计时器
	}
	
	
	/*CAN节点丢失DTC前置条件检测
		1.MCU复位 5S之后
		3.电压处于正常电压模式或电压异常恢复5s之后
		4.没有收到28 03 disable request
		5.无busoff或limphome故障 limphome条件在接口内部检测
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) \
		&& (Diag280301Flag == TRUE) && (BUSOffFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm); //重置计时器
	}
	/*CAN节点丢失DTC前置条件检测
		1.MCU复位 5S之后
		2、电源状态切换到ON档5s之后；
		3.电压处于正常电压模式或电压异常恢复5s之后
		4.没有收到28 03 disable request
		5.无busoff或limphome故障 limphome条件在接口内部检测
	*/
	if((condition_reset == TRUE) && (condition_ON == TRUE) && (condition_vot == TRUE) \
		&& (Diag280301Flag == TRUE) && (BUSOffFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw); //重置计时器
	}

	/*	主驾加热输出DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.主驾座椅正在加热
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) \
		&& (DrHeatFlag == TRUE) && (DrHeatVentCfg == TRUE) && (DrHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected); //重置计时器
	}

	/*	主驾加热NTC DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (DrHeatVentCfg == TRUE) && (DrHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid); //重置计时器
	}
	

	/*	副驾加热输出DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.副驾座椅正在加热
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) 
    && (PaHeatFlag == TRUE) && (PaHeatVentCfg == TRUE) && (PaHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected); //重置计时器
	}

	/*	副驾加热NTC DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (PaHeatVentCfg == TRUE) && (PaHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid); //重置计时器
	}
	
	/*	方向盘加热输出DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.方向盘座椅正在加热
	*/
	if((condition_reset == TRUE)  && (condition_vot == TRUE) && (SteerHeatFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected); //重置计时器
	}
	/*	方向盘加热NTC DTC检测
		1.MCU复位 5S之后
		//2.电源不在crank或转到非crank状态5s之后 
		3.电压处于正常电压模式或电压异常恢复5S之后
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)  && (SteerHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid); //重置计时器
	}
	/*主驾通风DTC前置条件检测
		1、（DSM上电或单片机上电或软件使MCU复位）5s之后
		//2、在crank或切出其他状态5s内不检测
		3、处于正常工作电压5s之后；
		4、主驾座椅正在通风
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (DrHeatVentCfg == TRUE) && (DrVentCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply); //重置计时器
	}

	/*副驾通风DTC前置条件检测
	1、（DSM上电或单片机上电或软件使MCU复位）5s之后
	//2、在crank或切出其他状态5s内不检测
	3、处于正常工作电压5s之后；
	4、副驾座椅正在通风
	*/
	/* 不检测正在通风，防止任务优先级原因故障产生且在模型关闭cmd后 未进入记录dtc*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) 
     && (PaHeatVentCfg == TRUE) && (PaVentCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply); //重置计时器
	}

	/*主驾高度调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.主驾座椅高度调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrHeightCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault); //重置计时器
	}
	/*主驾纵向调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.主驾座椅纵向调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrLengthCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault); //重置计时器
	}
	/*主驾靠背调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.主驾座椅靠背调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrBackrestCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault); //重置计时器
	}
	/*主驾前部角度调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.主驾座椅前部角度调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrFrontAngleCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg == 2))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault); //重置计时器
	}

	/*副驾纵向调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.副驾座椅纵向调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaLengthCtrl == TRUE)\
		&& (PaMemoryCfg == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault); //重置计时器
	}
	/*副驾靠背调节电机霍尔故障DTC前置条件检测
		1.MCU复位 5S之后
		2.电源不在crank或转到非crank状态5s之后
		3.电压处于正常电压模式或电压异常恢复5S之后
		4.副驾座椅靠背调节输出命令有效
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaBackrestCtrl == TRUE)\
		&& (PaMemoryCfg == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault); //重置计时器
	}

	/*主驾继电器粘连DTC前置条件检测*/
	if((condition_reset == TRUE) && (condition_crank == TRUE))
	{
		if(DrAdjustCfg == 2)
		{
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, TRUE);
		}
		else if(DrAdjustCfg == 1)
		{	
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, TRUE);
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, FALSE);
		}	
		else
		{
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, FALSE);
		}
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued); //重置计时器
	}
	
	/*副驾继电器粘连DTC前置条件检测*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (PaAdjustCfg == 1))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued); //重置计时器
	}
	
	/* 按摩模块及lin数据错误DTC
	1、（DSM上电或单片机上电或软件使MCU复位）且DSM发出第一帧alive报文5s之后；
	2、在crank或切出其他状态5s内不检测
	3、处于正常工作电压5s之后；
	4、按摩配置 == 0x01:true*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (seatMassageCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow, En_Dtc_LINError,TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow, En_Dtc_LINError,FALSE);
	}

	
	/*主驾硬线开关粘连*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) )
	{
		if(DrAdjustCfg == 2)
		{
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, TRUE);

		}
		else if (DrAdjustCfg == 1)
		{
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, TRUE);
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, FALSE);
		}
		else
		{
			Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
			Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //重置计时器
		}
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //重置计时器
	}

	
	/*副驾硬线开关粘连*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //重置计时器
	}

}

/***********************************************************************************************
* @function name:  Diag_Initu32DiagDtcTestFailTs(INT8U t_start, INT8U t_end )
*
* @description:    重置DTC检测计时器
*
* @input parameters:	 t_start：开始设置下标  t_end：结束下标（包含）
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-06-29
***********************************************************************************************/
void Diag_Initu32DiagDtcTestFailTs(INT8U t_start, INT8U t_end)
{
	INT8U i = 0;
	for (i = t_start; i < (t_end + 1); ++i)
	{
		u32DiagDtcTestFailTs[i] = D_HAL_GET_CUR_MS_TS();
	}
}

/***********************************************************************************************
* @function name:  DiagDtcHandleFunc(INT8U t_start, INT8U t_end )
*
* @description:    DTC处理接口
*
* @input parameters:	void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-07-04
***********************************************************************************************/
void DiagDtcHandleFunc(void)
{
	pt2Func *ptrDtcHandleFunc = Diag_GetDtcHandleFuncPtr();
	INT8U i = 0;
	for (i = 0; i < En_DtcType_MaxNum; i++)
	{
		//删除前提条件，解决老化次数达到无法清除DTC的问题
		if ((ptrDtcHandleFunc[i] != NULL))
		{
			ptrDtcHandleFunc[i]();
		}
	}
	
//	if( (ptrDtcHandleFunc != NULL) \
//		&& (t_start >= En_Dtc_CanBusOff) &&  (t_start < En_DtcType_MaxNum) \
//		&& (t_start <= t_end) && (t_end < En_DtcType_MaxNum))
//	{
//		for (i = t_start; i < t_end + 1; i++)
//		{
//			if (ptrDtcHandleFunc[i] != NULL)
//			{
//				ptrDtcHandleFunc[i]();
//			}
//		}
//	}
}

/*!
************************************************************************************************************************
* @par 接口原型
       void Diag_DtcRecordHandle(void)
* @par 描述
       所有故障DTC处理
* @param[in] cDescControlDTCSetting：DTC设置关闭
* @param[out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-10-30
************************************************************************************************************************
*/
void Diag_DtcRecordHandle(void)
{
	INT8U i = 0;
	
	static INT32U u32CycTs = 0;	
	
//	if(CPU_TimerDiffTs(u32CycTs) < 10UL)
//	{
//		return;
//	}
//	u32CycTs = D_HAL_GET_CUR_MS_TS();
	
	Diag_IsNewPwrCycle();

	if (cDescControlDTCSetting != DESC_CONTROL_DTC_SETTING_ON)
	{
		return;
	}


	Diag_VoltAbnromalOpt();

	
//	Diag_IsNewPwrCycle();
	Diag_IsNewWakeCycle();
	Diag_CommLogicCtrl();

	
	Diag_CanNetworkOpt();
	

	DSMDiag_vosSeatHeatDriveFaultCheck();
	DSMDiag_vosSeatHeatSensorFaultCheck();

//	DSMDiag_vosSeatVentMotorFaultCheck();
	DSMDiag_vosSeatVentPWMSignalFaultCheck();


	DSMDiag_vosSeatAdjustProcFaultCheck();

	Diag_CanNodeComLostOpt(); /* can节点文丢失判断 */
	Diag_LinNodeFaultCheck();
	
	DiagDtcHandleFunc(); //记录TDC
	
}

/*!
************************************************************************************************************************
* @par 接口原型
       void Diag_ClearAllDtc(void)
* @par 描述
       删除所有DTC
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-28
************************************************************************************************************************
*/

void Diag_ClearAllDtc(void)
{
	DiagDtcNameType_t enDtcIndex = En_Dtc_CanBusOff;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};

	for (enDtcIndex = En_Dtc_CanBusOff; enDtcIndex < (INT8U)En_DtcType_MaxNum; enDtcIndex++)
	{
		bDiagDtcInd[enDtcIndex] = FALSE;
		bDiagDtcAgingInd[enDtcIndex] = FALSE;
		Srvl_SetDTCStatusMask(enDtcIndex, (INT8U *)&DiagDtcMaskDat);
		Diag_WriteDtcTestFailFlag(enDtcIndex, FALSE);
	}
}

/*!
************************************************************************************************************************
* @par 接口原型
       void Diag_ClearDtcById(DiagDtcNameType_t enDtcIndex, INT8U num)
* @par 描述
       删除对应DTC
* @param[in]	enDtcIndex:开始删除的DTC，num：要删除的DTC数量（从enDtcIndex开始计数）
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-28
************************************************************************************************************************
*/

void Diag_ClearDtcById(DiagDtcNameType_t enDtcIndex, INT8U num)
{
	DiagDtcNameType_t start_index = enDtcIndex;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	DiagDtcNameType_t i = 0;
	
	for(i = start_index; i < start_index + num; i++)
	{
		if(i >= En_DtcType_MaxNum )
		{
			return;
		}
		bDiagDtcInd[i] = FALSE;
		bDiagDtcAgingInd[i] = FALSE;
		Srvl_SetDTCStatusMask(i, (INT8U *)&DiagDtcMaskDat);
		Diag_WriteDtcTestFailFlag(i, FALSE);
	}
}

/*!
************************************************************************************************************************
* @par 接口原型
       INT16U Diag_MatchDtcMaskNum(INT8U mask)
* @par 描述
       获取匹配DTC Mask的故障码数量
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/

INT16U Diag_MatchDtcMaskNum(INT8U mask)
{
	INT8U i = 0;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	INT16U tMatchCnt = 0u;
	BOOL bRet = FALSE;

	for (i = 0; i < (INT8U)En_DtcType_MaxNum; i++)
	{
		bRet = Srvl_GetDTCStatusMask(i, (INT8U *)&DiagDtcMaskDat);
		if( bRet == TRUE )
		{
			if((mask & DiagDtcMaskDat.Diag_DtcMask.Diag_DtcByte) != 0x00U)
			{
				tMatchCnt++;
			}
		}
	}

	return tMatchCnt;
}

/*!
************************************************************************************************************************
* @par 接口原型
       BOOL Diag_MatchDtcMaskCode(INT8U mask, INT8U dtcIndex, INT8U u8DtcCode[], INT8U dtcLen)
* @par 描述
       匹配DTC Mask，一致则输出DTC Code
* @param[in] INT8U mask：DTC掩码
* @param[in] DiagDtcName_t dtcIndex：DTC名称
* @param[in] INT8U dtcLen：DTC长度
* @param[out] INT8U dtc[]：DTC
* @returns BOOL：是否匹配
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/
BOOL Diag_MatchDtcMaskCode(INT8U mask, INT8U dtcIndex, INT8U u8DtcCode[], INT8U dtcLen)
{
	BOOL tMatchInd = FALSE;
	DiagDtcCfgList_t * DtcConfigListPtr = NULL;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	BOOL bRet = FALSE;

	if(dtcIndex < (INT8U)En_DtcType_MaxNum)
	{
		bRet = Srvl_GetDTCStatusMask(dtcIndex, (INT8U *)&DiagDtcMaskDat);
		if( bRet == TRUE )
		{
			if((mask & DiagDtcMaskDat.Diag_DtcMask.Diag_DtcByte) != 0x00U)
			{
				DtcConfigListPtr = Diag_GetDtcConfigListPtr();
				if(DtcConfigListPtr != NULL)
				{
					u8DtcCode[0] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 16U) & 0xFFU;
					u8DtcCode[1] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 8U) & 0xFFU;
					u8DtcCode[2] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 0U) & 0xFFU;
					tMatchInd = TRUE;
				}
			}
		}
	}

	return tMatchInd;
}

/*!
************************************************************************************************************************
* @par 接口原型
       INT8U Diag_GetDtcMask(DiagDtcName_t dtcIndex)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/

INT8U Diag_GetDtcMask(INT8U dtcIndex)
{
	INT8U u8Mask = 0x00U;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	BOOL bRet = FALSE;

	if(dtcIndex < (INT8U)En_DtcType_MaxNum)
	{
		bRet = Srvl_GetDTCStatusMask(dtcIndex, (INT8U *)&DiagDtcMaskDat);
		if( bRet == TRUE )
		{
			u8Mask = DiagDtcMaskDat.Diag_DtcMask.Diag_DtcByte;
		}
	}

	return u8Mask;
}

/*!
************************************************************************************************************************
* @par 接口原型
       void Diag_GetDtcCode(INT8U dtcIndex, INT8U * u8DtcCode)
* @par 描述
       获取DTC
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/

BOOL Diag_GetDtcCode(INT8U dtcIndex, INT8U * u8DtcCode)
{
	DiagDtcCfgList_t * DtcConfigListPtr = NULL;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	BOOL bRet = FALSE;

	if(dtcIndex < (INT8U)En_DtcType_MaxNum)
	{
		bRet = Srvl_GetDTCStatusMask(dtcIndex, (INT8U *)&DiagDtcMaskDat);
		if( bRet == TRUE )
		{
			DtcConfigListPtr = Diag_GetDtcConfigListPtr();
			if( (DtcConfigListPtr != NULL) && (u8DtcCode != NULL) && (DtcConfigListPtr[dtcIndex].Diag_DtcEnable != D_DISABLE))
			{
				bRet = TRUE;
				u8DtcCode[0] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 16U) & 0xFFU;
				u8DtcCode[1] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 8U) & 0xFFU;
				u8DtcCode[2] = (DtcConfigListPtr[dtcIndex].Diag_DtcCode >> 0U) & 0xFFU;
				return bRet;
			}
			bRet = FALSE;
		}
	}

	return bRet;
}

/*!
************************************************************************************************************************
* @par 接口原型
       INT8U Diag_FindDtcMask(INT8U dtc[], INT8U dtcLen)
* @par 描述
       根据DTC查找对应配置的索引
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/

INT8U Diag_FindDtcMask(INT8U dtc[], INT8U dtcLen)
{
	INT8U i = 0;
	INT8U j = 0;

	if (dtc == NULL)
	{
		return 0xFFU;
	}

	if (dtcLen != D_DIAG_DTC_CODE_SIZE)
	{
		return 0xFFU;
	}


	return i + j;
}

#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
/*!
************************************************************************************************************************
* @par 接口原型
       BOOL Diag_FindVehSnapData(DiagDtcName_t dtcIndex, DiagSnapVehInfo_t *pSnapDat)
* @par 描述
       根据索引查找车身数据快照
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/
static INT8U Diag_FindVehSnapDataIdx(INT8U dtcIndex)
{
	BOOL idx = 0xFF;
	INT8U i = 0;

	for (i = 0; i < sizeof(Diag_SnapQueue) / sizeof(DiagSnapshotQue_t); i++)
	{
		if (Diag_SnapQueue[i].Diag_DtcInx == dtcIndex)
		{
			idx = Diag_SnapQueue[i].Index;
		}
	}

	return idx;
}


static INT8U Diag_FindDtcDataIdx(INT32U u8DtcCode)
{
	DiagDtcCfgList_t *pCfg = Diag_GetDtcConfigListPtr();
	INT8U i, idx = 0xFF;

	for (i = 0; i < En_DtcType_MaxNum; i++)
	{
		if (pCfg[i].Diag_DtcCode == u8DtcCode)
		{
			idx = i;
		}
	}

	return idx;
}


/*!
************************************************************************************************************************
* @par 接口原型
       BOOL Diag_ReadVehSnapData(INT8U u8DtcCode[3], INT8U recodeNumber, INT8U *pSnapDat, INT16U size, INT16U *length)
* @par 描述
       根据索引读取快照数据
* @param[in]
* @param[out]
* @returns
* @pre
* @note 注意缓存长度需>=快照数据长度
* @author Lews Hammond(刘发星)
* @date 2019-9-30
************************************************************************************************************************
*/
BOOL Diag_ReadVehSnapData(INT8U u8DtcCode[3], INT8U recodeNumber, INT8U *pSnapDat, INT16U size, INT16U *length)
{
	BOOL bRet = FALSE;
	INT8U idx = 0, dtcIdx = 0, index = 0, offset = 0;
	INT8U tBufInx = 0;
	INT32U dtcCode = 0;

	if (pSnapDat == NULL || length == NULL || u8DtcCode == NULL)
	{
		return bRet;
	}

	/**< 通过DTC Code搜索DTC序号 */
	dtcCode = u8DtcCode[0] << 16 | u8DtcCode[1] << 8 | u8DtcCode[2];
	dtcIdx = Diag_FindDtcDataIdx(dtcCode);
	if (dtcIdx == 0xFF)
	{
		return bRet;
	}

	/**< 通过DTC IDX搜索Snap序号 */
	idx = Diag_FindVehSnapDataIdx(dtcIdx);
	if (idx == 0xFF)
	{
		return bRet;
	}

	/* 如果数据未更新则取EEPROM数据 */
	if (Diag_SnapQueue[idx].RAM_UpdataFlag == FALSE)
	{
		Srvl_GetDTCExternDataSnapInfo(idx, Diag_SnapQueue[idx].Diag_SnapshotDat);
		Diag_SnapQueue[idx].RAM_UpdataFlag = TRUE;
	}

	/* 填充快照数据 */
	pSnapDat[index++] = u8DtcCode[0];
	pSnapDat[index++] = u8DtcCode[1];
	pSnapDat[index++] = u8DtcCode[2];
	pSnapDat[index++] = Diag_GetDtcMask(dtcIdx) & DTCStatusAvailabilityMask;	/* 掩位码 */
	if (recodeNumber == 0xFF || recodeNumber == Diag_SnapConfigList.Snap_RecordNum)
	{
		INT8U i = 0;

		/* 当故障确认位不为1时，不返回快照数据 */
		if (pSnapDat[index - 1] & 0x08)
		{
			pSnapDat[index++] = Diag_SnapConfigList.Snap_RecordNum;
			pSnapDat[index++] = Diag_SnapConfigList.size;
			for (i = 0; i < Diag_SnapConfigList.size; i++)
			{
				pSnapDat[index++] = Diag_SnapConfigList.did[i].Snap_DataId >> 8;
				pSnapDat[index++] = Diag_SnapConfigList.did[i].Snap_DataId & 0xFF;
				Srvl_MemCopy(&pSnapDat[index], &Diag_SnapQueue[idx].Diag_SnapshotDat[offset], \
						Diag_SnapConfigList.did[i].Snap_DataLen);
				index += Diag_SnapConfigList.did[i].Snap_DataLen;
				offset += Diag_SnapConfigList.did[i].Snap_DataLen;
			}
		}
		*length = index;
	}
	else
	{
		/* 当recordNumber不支持时，返回Flase */
		return bRet;
	}

	return TRUE;
}


BOOL Diag_ReadVehSnapshotIdentification(INT8U *pSnapDat,INT16U *length)
{
	BOOL bRet = FALSE;
	INT8U i = 0,dtcIdx = 0, index = 0,  mask = 0 ,idx = 0;
	
	DiagDtcCfgList_t *Diag_DtcConfigList =  Diag_GetDtcConfigListPtr();

	if (pSnapDat == NULL || length == NULL)
	{
		return bRet;
	}

	for(i = 0; i < En_DtcType_MaxNum; i++)
	{
		/**< 通过DTC Code搜索DTC序号 */
		dtcIdx = Diag_FindDtcDataIdx(Diag_DtcConfigList[i].Diag_DtcCode);
		if (dtcIdx == 0xFF)
		{
			return FALSE;
		}
		/**< 通过DTC IDX搜索Snap序号 */
		idx = Diag_FindVehSnapDataIdx(dtcIdx);
		if (idx == 0xFF)
		{
			continue;
		}
		//mask = Diag_GetDtcMask(dtcIdx) & DTCStatusAvailabilityMask;	/* 掩位码 */
		/* 当故障确认位不为1时，不返回快照数据 */
		//if (mask & 0x08)
		//{
		
			pSnapDat[index++] =  (INT8U)(Diag_DtcConfigList[i].Diag_DtcCode >> 16);
			pSnapDat[index++] =  (INT8U)(Diag_DtcConfigList[i].Diag_DtcCode >> 8);
			pSnapDat[index++] =  (INT8U)(Diag_DtcConfigList[i].Diag_DtcCode >> 0);
			
			pSnapDat[index++] =  Diag_SnapConfigList.Snap_RecordNum;
		//}
	}
	*length = index;
	return TRUE;
}



#endif

/*!
************************************************************************************************************************
* @par 接口原型
       BOOL Diag_DtcMaskSetClrOpt(DiagDtcNameType_t enDtcIndex, BOOL bDtcTestFailed)
* @par 描述
       DTC mask处理
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2020-9-22
************************************************************************************************************************
*/
BOOL Diag_DtcMaskSetClrOpt(DiagDtcNameType_t enDtcIndex, BOOL bDtcTestFailed)
{
	BOOL memWriteInd = FALSE;
	INT16U AgingCntLmt = 0;
	INT16U RecordCntLmt = 0;
	INT16U diagPeriod = 0;
	INT8U snapIdx = 0;

	DiagDtcCfgList_t *DtcConfigListPtr = Diag_GetDtcConfigListPtr();
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};
	BOOL bRet = FALSE;


	if (enDtcIndex >= En_DtcType_MaxNum)
	{
		return memWriteInd;
	}

	bRet = Srvl_GetDTCStatusMask(enDtcIndex, (INT8U *)&DiagDtcMaskDat);
	if( bRet != TRUE )
	{
		return memWriteInd;
	}

	if(DtcConfigListPtr == NULL)
	{
		return memWriteInd;
	}

	AgingCntLmt = DtcConfigListPtr[(INT8U)enDtcIndex].Diag_AgingTimes;
	RecordCntLmt = DtcConfigListPtr[(INT8U)enDtcIndex].Diag_FailValidCnt;
	diagPeriod = DtcConfigListPtr[(INT8U)enDtcIndex].Diag_SampleTime;

	if (Diag_NewPwrCycle == TRUE)
	{
#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_ENABLE == D_ENABLE)
		if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed != FALSE)
		{
			DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed = FALSE;
			memWriteInd = TRUE;
		}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_THIS_OPERATION_CYCLE_ENABLE == D_ENABLE)
		if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedThisOpCycle != FALSE)
		{
			memWriteInd = TRUE;
			DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedThisOpCycle = FALSE;
		}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_THIS_CYCLE_ENABLE == D_ENABLE)
		if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdThisOpCycle != TRUE)
		{
			memWriteInd = TRUE;
			DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdThisOpCycle = TRUE;
		}
#endif

		bDiagDtcInd[enDtcIndex] = FALSE;
		bDiagDtcAgingInd[enDtcIndex] = FALSE;
	}
	else
	{
		bDiagDtcAgingInd[enDtcIndex] = TRUE;
	}

	if (bDtcTestFailed == TRUE) /*报文丢失*/
	{
		bDiagDtcAgingInd[enDtcIndex] = TRUE; /* 出现故障，恢复后不算老化 */
		if (DiagDtcMaskDat.Diag_AgingCnt != 0)
		{
			DiagDtcMaskDat.Diag_AgingCnt = 0;
			memWriteInd = TRUE;
		}

		//if (bDiagDtcInd[enDtcIndex] == FALSE)
		{
			//bDiagDtcInd[enDtcIndex] = TRUE; /* 诊断记录一次 */
#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_ENABLE == D_ENABLE)
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed != TRUE)
			{
				memWriteInd = TRUE;
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed = TRUE;

				//Jetty 2022-04-18 只要第一次TestFail为True，则记录SnapData，连续TestFail不更新SnapData, 故障次数最大记录到255次数后不增加。
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC = TRUE;

				/* 用于记录故障次数 */
				DiagDtcMaskDat.Diag_FailCnt = DiagDtcMaskDat.Diag_FailCnt < 0xFF ?
											  DiagDtcMaskDat.Diag_FailCnt + 1 : 0xFF;

#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
				snapIdx = Diag_FindVehSnapDataIdx(enDtcIndex);
				if (snapIdx != 0xFF)
				{
					GetSnapData(Diag_SnapQueue[snapIdx].Diag_SnapshotDat, 20);
					//Srvl_MemSetValue(Diag_SnapQueue[snapIdx].Diag_SnapshotDat, snapIdx, 17);
					Diag_SnapQueue[snapIdx].Diag_SnapshotDat[10] = DiagDtcMaskDat.Diag_FailCnt;
					Diag_SnapQueue[snapIdx].RAM_UpdataFlag = TRUE;
					Srvl_SetDTCExternDataSnapInfo(snapIdx, Diag_SnapQueue[snapIdx].Diag_SnapshotDat);
				}
#endif
			}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_THIS_OPERATION_CYCLE_ENABLE == D_ENABLE)
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedThisOpCycle != TRUE)
			{
				memWriteInd = TRUE;
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedThisOpCycle = TRUE;
			}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_PENDING_DTC_ENABLE == D_ENABLE)
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.PendingDTC != TRUE)
			{
				memWriteInd = TRUE;
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.PendingDTC = TRUE;
			}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_SINCE_LAST_CLEAR_ENABLE == D_ENABLE)
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedSinceLstClr != TRUE)
			{
				memWriteInd = TRUE;
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailedSinceLstClr = TRUE;
			}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_CONFIRM_DTC_ENABLE == D_ENABLE)
			//Jetty 2022-03-25 只要第一次TestFail为True，则记录SnapData，连续TestFail不更新SnapData, 故障次数最大记录到255次数后不增加。
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC != TRUE)
			{
//				memWriteInd = TRUE;
//				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC = TRUE;
//
//				/* 用于记录故障次数 */
//				DiagDtcMaskDat.Diag_FailCnt = DiagDtcMaskDat.Diag_FailCnt < 0xFF ?
//					DiagDtcMaskDat.Diag_FailCnt + 1 : 0xFF;
//
//        #if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
//				snapIdx = Diag_FindVehSnapDataIdx(enDtcIndex);
//				if (snapIdx != 0xFF)
//				{
//					//TODO
//					GetSnapData(Diag_SnapQueue[snapIdx].Diag_SnapshotDat, 20);
//					//Srvl_MemSetValue(Diag_SnapQueue[snapIdx].Diag_SnapshotDat, snapIdx, 17);
//					Diag_SnapQueue[snapIdx].Diag_SnapshotDat[16] = DiagDtcMaskDat.Diag_FailCnt;
//					Diag_SnapQueue[snapIdx].RAM_UpdataFlag = TRUE;
//					Srvl_SetDTCExternDataSnapInfo(snapIdx, Diag_SnapQueue[snapIdx].Diag_SnapshotDat);
//				}
//        #endif
			}
#endif
		}
	}
	else
	{
#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_ENABLE == D_ENABLE)
		if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed != FALSE)
		{
			memWriteInd = TRUE;
			DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed = FALSE;
		}
#endif
		//bDiagDtcInd[enDtcIndex] = FALSE;
		

		if (bDiagDtcAgingInd[enDtcIndex] == FALSE)
		{
			bDiagDtcAgingInd[enDtcIndex] = TRUE; /*老化记录一次*/
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC == TRUE) /*确认故障，才加老化*/
			{
				DiagDtcMaskDat.Diag_AgingCnt++; /*新周期老化次数加一*/
				memWriteInd = TRUE;
			}
			
			if (DiagDtcMaskDat.Diag_AgingCnt >= AgingCntLmt)
			{
				DiagDtcMaskDat.Diag_AgingCnt = 0;

#if (D_UDS_DIAG_DTC_MASK_BIT_CONFIRM_DTC_ENABLE == D_ENABLE)
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC = FALSE;
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_PENDING_DTC_ENABLE == D_ENABLE)
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.PendingDTC = FALSE;
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_SINCE_LAST_CLEAR_ENABLE == D_ENABLE)
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdSinceLstClr = TRUE;
#endif

#if (D_ENABLE_UDS_SNAPSHOT == D_ENABLE)
				// TODO: Snapshort data clear...
#endif
				memWriteInd = TRUE;
			}

		}
	}

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_THIS_CYCLE_ENABLE == D_ENABLE)
	if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdThisOpCycle != FALSE)
	{
		memWriteInd = TRUE;
		DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdThisOpCycle = FALSE;
	}
#endif

#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_NOT_COMPLETED_SINCE_LAST_CLEAR_ENABLE == D_ENABLE)
	if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdSinceLstClr == TRUE)
	{
		memWriteInd = TRUE;
		DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstNotCmpltdSinceLstClr = FALSE;
	}
#endif

	if( memWriteInd == TRUE)
	{
		Srvl_SetDTCStatusMask(enDtcIndex, (INT8U *)&DiagDtcMaskDat);
	}

	return memWriteInd;
}


/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_CanNetworkOpt(void)
* @par 描述
       DTC网络相关DTC配置
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-9-25
************************************************************************************************************************
*/
static void Diag_CanNetworkOpt(void)
{
	static INT32U u32DelayTs = 0x0u;
	static INT32U u32LimphomeTs = 0x0u;
	NMStateType LimphomeSts = NM_stNormal;
	/*网络跛行回家*/
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DsmNodeLimphome))
	{
		GetStatus(OSEK_NM,&LimphomeSts);
		if((NM_stLimphome == LimphomeSts) || (NM_stLimphomePrepSleep == LimphomeSts) || (NM_stTwbsLimphome == LimphomeSts))
		{
//			if(CPU_TimerDiffTs(u32LimphomeTs) > D_DTC_LIMPHOME_TIME)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DsmNodeLimphome, TRUE);
			}
		}
		else
		{
//			u32LimphomeTs = D_HAL_GET_CUR_MS_TS();
			Diag_WriteDtcTestFailFlag(En_Dtc_DsmNodeLimphome, FALSE);
		}

	}
	/*busoff*/
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_CanBusOff))
	{
		if(D_BUSOFF_COUNT > Nm_CanGetBusOffTrgCnt())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_CanBusOff, FALSE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_CanBusOff, TRUE);
		}
	}
	
	/*if(0x0u == Ecual_GetCanBusoffCount())
	{
		u32DelayTs = D_HAL_GET_CUR_MS_TS();
	}
	if(CPU_TimerDiffTs(u32DelayTs) > D_Busoff_CleanTime)
	{
		Ecual_SetCanBusoffCount(0x0u);
	}*/
}
/***********************************************************************
 * @function name: Ecual_GetCANTimeoutDuration
 *
 * @description: 获取某个ID接收超时时长-待实现
 *
 * @input parameters: INT32U Can_Id CAN ID
 *
 * @output parameters: void
 *
 * @return: 指定ID超时时长
 *
 * @note: 0xFFFFU:错误值
 *
 * @author: Prima Niu
 *
 * @date: 2023-06-28 19:10
 ***********************************************************************/
INT16U Ecual_GetCANTimeoutDuration(eRXINDEX CanIdIndex)
{
	INT16U	Result = 0xFFFFU;

	Result = IlGetIlRxTimeoutTbl(CanIdIndex);

	return Result;
}
/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_CanNodeComLostOpt(void)
* @par 描述
       DTC can节点文丢失判断
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-12
************************************************************************************************************************
*/
static void Diag_CanNodeComLostOpt(void)
{

	static INT32U u32PowerOnTs = 0;
	BOOL TS_ResetFlg = FALSE; //不满足检测条件，重置时间标志位
	INT8U eTimeCount = 0;//用来初始化时间记录
	INT8U bPowerMode = 0;
	INT8U i = 0;
	
	//bPowerMode = Rte_GetVfb_PowerMode();

	if(ECUAL_CAN_IS_APP_RX_ENABLE() == FALSE)
	{
		//28服务禁止RX通信后不检测CAN丢失；
		TS_ResetFlg = TRUE;
		//return;
	}
#if 0
	if((bPowerMode != 2u))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		TS_ResetFlg = TRUE;
		//return; /*电源模式未设置，此处暂时不退出，后续需要放开*/
	}
	else
	{
		/*ON电及以上没有达到5s不执行通讯类故障码置位*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 5UL * 1000UL)
		{
			//for(eTimeCount = En_Dtc_BCANPEPSAbsent ; eTimeCount < En_Dtc_NocommunicationonLIN1 ; eTimeCount++)
			//{
			//	u32DiagDtcTestFailTs[eTimeCount] = D_HAL_GET_CUR_MS_TS();
			//}
			TS_ResetFlg = TRUE;
			//return;
		}
	}
#endif
	if((FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DsmNodeLimphome))\
		&& (TRUE == Diag_getMonitorEnableCriteria(En_Dtc_LostCommunicationWithBcm)))
	{
		/*DSMC与BDCU通讯丢失故障   		 没有接收到0x283报文超过10周期，置故障码*/
		if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x283) == FALSE)//接收到报文
		{
			if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithBcm))
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm]) > s_CanMSG_timePram[EN_BCM_INDEX].regain)
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm] = D_HAL_GET_CUR_MS_TS();
					Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithBcm, FALSE);
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm] = D_HAL_GET_CUR_MS_TS();
			}
		}
		else
		{
			if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithBcm))
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm]) > (s_CanMSG_timePram[EN_BCM_INDEX].timeout - Ecual_GetCANTimeoutDuration(eRXINDEX_0x283)))
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithBcm, TRUE);
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBcm] = D_HAL_GET_CUR_MS_TS();
			}
		}
	}
		
	if((FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DsmNodeLimphome)) \
	&& (TRUE == Diag_getMonitorEnableCriteria(En_Dtc_LostCommunicationWithGw)))
	{
		/*DSMC与GW通讯丢失故障   		 没有接收到0x2A7报文超过10周期，置故障码*/
		if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x2A7) == FALSE)//接收到报文
		{
			if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithGw))
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw]) > s_CanMSG_timePram[EN_GW_INDEX].regain)
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw] = D_HAL_GET_CUR_MS_TS();
					Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithGw, FALSE);
				}
//				printf("0x2A7 FALSE\r\n");
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw] = D_HAL_GET_CUR_MS_TS();
			}
		}
		else
		{
			if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithGw))
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw]) > (s_CanMSG_timePram[EN_GW_INDEX].timeout - Ecual_GetCANTimeoutDuration(eRXINDEX_0x2A7)))
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithGw, TRUE);
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw] = D_HAL_GET_CUR_MS_TS();
				}
//				printf("0x2A7 TRUE\r\n");
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithGw] = D_HAL_GET_CUR_MS_TS();
			}
		}
	}
#if 0 // 231101  暂未实现
	/*busoff | limphome 不检测通讯类故障码*/
	if((TRUE == Nm_IsBusOff()) || (Diag_ReadDtcTestFailFlag(En_Dtc_DSMCLimpHome) == TRUE))
	{	
		TS_ResetFlg = TRUE;
		//return;
	}

	if(TRUE == TS_ResetFlg)
	{
		for( i = En_Dtc_LostCommunicationWithBDCU; i < En_DtcType_MaxNum; i++)
		{
			u32DiagDtcTestFailTs[i] = D_HAL_GET_CUR_MS_TS();
		}
		return;
	}
	
	/*Diag_CommDtcWorkInd = TRUE;*/
	/*Diag_CommMsgTimeoutInd = TRUE;*/

	/*if (Diag_CommDtcWorkInd == TRUE) 电压范围正常、其他ecu初始化完成*/
	/*{
		if (Diag_CommMsgTimeoutInd == TRUE)
		{*/
			/*DSMC与BDCU通讯丢失故障   		 没有接收到0x570报文超过15s，置故障码*/
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x570) == FALSE)//接收到报文
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithBDCU))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithBDCU, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithBDCU))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x570)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithBDCU, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithBDCU] = D_HAL_GET_CUR_MS_TS();
				}
			}
			

			/*DSMC与ESP通讯丢失故障 没有接收到0x311报文超过15s*/
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x311) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithESP))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithESP, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithESP))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x311)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithESP, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithESP] = D_HAL_GET_CUR_MS_TS();
				}
			}
			

			/*DSMC与ICC通讯丢失故障 没有接收到0x51A报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x51A) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithICC))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithICC, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithICC))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x51A)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithICC, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithICC] = D_HAL_GET_CUR_MS_TS();
				}
			}

			/*DSMC与TBOX通讯丢失故障 没有接收到0x529报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x529) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithTBOX))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithTBOX, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithTBOX))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x529)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithTBOX, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTBOX] = D_HAL_GET_CUR_MS_TS();
				}
			}
			
			/*DSMC与DCU通讯丢失故障 没有接收到0x564、0x566报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x564) == FALSE || Ecual_GetCanMsgLostFlag(eRXINDEX_0x566) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithDCU))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithDCU, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithDCU))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x566)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithDCU, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithDCU] = D_HAL_GET_CUR_MS_TS();
				}
			}
			
			/*DSMC与CSS通讯丢失故障 没有接收到0x330报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x330) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithCSS))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithCSS, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithCSS))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x330)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithCSS, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithCSS] = D_HAL_GET_CUR_MS_TS();
				}
			}

			/*DSMC与EMS通讯丢失故障 没有接收到0x280报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x280) == FALSE )
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithEMS))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithEMS, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithEMS))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x280)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithEMS, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithEMS] = D_HAL_GET_CUR_MS_TS();
				}
			}
			
			/*DSMC与TCM通讯丢失故障 没有接收到0x3E0报文超过15s */
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x3E0) == FALSE)
			{
				if(TRUE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithTCM))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM]) > D_JoinCom_HoldOnTime)
					{
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM] = D_HAL_GET_CUR_MS_TS();
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithTCM, FALSE);
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{	
				if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_LostCommunicationWithTCM))
				{
					if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM]) > (D_LostCom_HoldOnTime - Ecual_GetCANTimeoutDuration(eRXINDEX_0x3E0)))
					{
						Diag_WriteDtcTestFailFlag(En_Dtc_LostCommunicationWithTCM, TRUE);
						u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM] = D_HAL_GET_CUR_MS_TS();
					}
				}
				else
				{
					u32DiagDtcTestFailTs[En_Dtc_LostCommunicationWithTCM] = D_HAL_GET_CUR_MS_TS();
				}
			}
#endif
			#if 0
			//}

			/*ABS/ESP 通讯丢失 检测到0x221中任一报文丢失且持续时间t >= 3S，置故障码*/
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x221) == FALSE )
			{
				//u32DiagDtcTestFailTs[En_Dtc_BCANABSAbsent] = D_HAL_GET_CUR_MS_TS();
				//Diag_WriteDtcTestFailFlag(En_Dtc_BCANABSAbsent, FALSE);
			}
			else
			{
				//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANABSAbsent]) > D_LostCom_HoldOnTime)
				{
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANABSAbsent, TRUE);
				}
			}

			/*EMS 通讯丢失 检测到0x142中任一报文丢失且持续时间t >= 3S，置故障码*/
			if(Srv_GetMemCfgData(VEHTRANSMISSIONTYPEPRM) == 0x00u)
			{
				if( (Ecual_GetCanMsgLostFlag(eRXINDEX_0x142) == FALSE) || \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x101) == FALSE) || \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x105) == FALSE) || \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x107) == FALSE)	|| \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x108) == FALSE) || \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x364) == FALSE)
				  )
				{
					//u32DiagDtcTestFailTs[En_Dtc_BCANEMSAbsent] = D_HAL_GET_CUR_MS_TS();
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANEMSAbsent, FALSE);
				}
				else
				{
					//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANEMSAbsent]) > D_LostCom_HoldOnTime)
					{
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANEMSAbsent, TRUE);
					}
				}
			}
			else
			{
				if((Ecual_GetCanMsgLostFlag(eRXINDEX_0x108) == FALSE) || \
						(Ecual_GetCanMsgLostFlag(eRXINDEX_0x10B) == FALSE))
				{
					//u32DiagDtcTestFailTs[En_Dtc_BCANEMSAbsent] = D_HAL_GET_CUR_MS_TS();
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANEMSAbsent, FALSE);
				}
				else
				{
					//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANEMSAbsent]) > D_LostCom_HoldOnTime)
					{
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANEMSAbsent, TRUE);
					}
				}
			}
			/*TCU 通讯丢失 检测到0x123中任一报文丢失且持续时间t >= 3S，置故障码*/
			if(Srv_GetMemCfgData(VEHTRANSMISSIONTYPEPRM) == 0x01u) //AMT车型才有这个DTC
			{
				if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x123) == FALSE )
				{
					//u32DiagDtcTestFailTs[En_Dtc_BCANTCUAbsent] = D_HAL_GET_CUR_MS_TS();
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTCUAbsent, FALSE);
				}
				else
				{
					//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANTCUAbsent]) > D_LostCom_HoldOnTime)
					{
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTCUAbsent, TRUE);
					}
				}
			}



			/*ICM 通讯丢失 检测到0x510中任一报文丢失且持续时间t >= 3S，置故障码*/
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x510) == FALSE )
			{
				//u32DiagDtcTestFailTs[En_Dtc_BCANICAbsent] = D_HAL_GET_CUR_MS_TS();
				//Diag_WriteDtcTestFailFlag(En_Dtc_BCANICAbsent, FALSE);
			}
			else
			{
				//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANICAbsent]) > D_LostCom_HoldOnTime)
				{
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANICAbsent, TRUE);
				}
			}

			/*TBOX 通讯丢失 检测检测到0x1A1、0x585、0x1A7报文均丢失且持续时间t≥3S置故障码*/
			if(Srv_GetMemCfgData(VEHENOTAFUNCSETTINGSTATUS) == 0x01u)
			{
				if(Srv_GetMemCfgData(VEHENPEPSPRM) == 0x00u) //非PEPS有这个DTC
				{
					if( (Ecual_GetCanMsgLostFlag(eRXINDEX_0x1A1) == FALSE) || \
							(Ecual_GetCanMsgLostFlag(eRXINDEX_0x585) == FALSE) || \
							(Ecual_GetCanMsgLostFlag(eRXINDEX_0x1A7) == FALSE))
					{
						//u32DiagDtcTestFailTs[En_Dtc_BCANTBOXAbsent] = D_HAL_GET_CUR_MS_TS();
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTBOXAbsent, FALSE);
					}
					else
					{
						//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANTBOXAbsent]) > D_LostCom_HoldOnTime)
						{
							//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTBOXAbsent, TRUE);
						}
					}
				}
				else//配置了PSPS之后检测这两个是否丢失
				{
					if((Ecual_GetCanMsgLostFlag(eRXINDEX_0x585) == FALSE) || \
							(Ecual_GetCanMsgLostFlag(eRXINDEX_0x1A7) == FALSE))
					{
						//u32DiagDtcTestFailTs[En_Dtc_BCANTBOXAbsent] = D_HAL_GET_CUR_MS_TS();
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTBOXAbsent, FALSE);
					}
					else
					{
						//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANTBOXAbsent]) > D_LostCom_HoldOnTime)
						{
							//Diag_WriteDtcTestFailFlag(En_Dtc_BCANTBOXAbsent, TRUE);
						}
					}
				}
			}
			/*IPM 通讯丢失 检测到0x245报文丢失且持续时间t >=3S置故障码*/
			//ADAS配置状态配置为0x0或0x1或0x2，满足报文245或246丢失条件时，都只报IPM通讯丢失
			if(Srv_GetMemCfgData(VEHADASSETTINGSTATUS) != 0x03u)
			{
				if((Ecual_GetCanMsgLostFlag(eRXINDEX_0x245) == FALSE) || (Ecual_GetCanMsgLostFlag(eRXINDEX_0x246) == FALSE))
				{
					//u32DiagDtcTestFailTs[En_Dtc_BCANIPMAbsent] = D_HAL_GET_CUR_MS_TS();
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANIPMAbsent, FALSE);
				}
				else
				{
					//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANIPMAbsent]) > D_LostCom_HoldOnTime)
					{
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANIPMAbsent, TRUE);
					}
				}
			}

			/*DMS 通讯丢失 检测到0x4A0报文丢失且持续时间t >=3S置故障码*/
			if(Srv_GetMemCfgData(VEHENDMSPRM) == 0x01u)
			{
				if(Ecual_GetCanMsgLostFlag(eRXINDEX_0x4A0) == FALSE)
				{
					//u32DiagDtcTestFailTs[En_Dtc_BCANDMSAbsent] = D_HAL_GET_CUR_MS_TS();
					//Diag_WriteDtcTestFailFlag(En_Dtc_BCANDMSAbsent, FALSE);
				}
				else
				{
					//if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_BCANDMSAbsent]) > D_LostCom_HoldOnTime)
					{
						//Diag_WriteDtcTestFailFlag(En_Dtc_BCANDMSAbsent, TRUE);
					}
				}
			}
			#endif
		/*}
	}*/
			
}

/***********************************************************************************************
* @function name:  Diag_LinNodeFaultCheck(void)
*
* @description:    Lin 按摩模块故障检测
*
* @input parameters:	 void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   10ms
*
* @author:			zjx
*
* @note:		   2024-04-11
***********************************************************************************************/

static void Diag_LinNodeFaultCheck(void)
{
	/* 按摩模块及lin数据错误DTC
	1、（DSM上电或单片机上电或软件使MCU复位）且DSM发出第一帧alive报文5s之后；
	2、在crank或切出其他状态5s内不检测
	3、处于正常工作电压5s之后；*/
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow))
	{
		//按摩模块欠压
		if(2 == LinSignalGet_Massage_1_Massage_Error_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooLow, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageModuleVoltageTooLow,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooLow, FALSE);
		}

		//按摩模块过压
		if(1 == LinSignalGet_Massage_1_Massage_Error_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooHigh, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageModuleVoltageTooHigh,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooHigh, FALSE);
		}
		
		//按摩模块过流
		if(1 == LinSignalGet_Massage_1_Motor_TimeOutError_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageMotorOvercurrent, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageMotorOvercurrent,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageMotorOvercurrent, FALSE);
		}
		
		//lin数据出错
		if(TRUE == Ecual_LinGetLostPid())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_LINError, TRUE);
			Diag_SetDTCFlg(En_Dtc_LINError,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_LINError, FALSE);
		}
	}
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_VoltAbnromalOpt(void)
* @par 描述
       电压判断
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-13
************************************************************************************************************************
*/
static void Diag_VoltAbnromalOpt(void)
{ 
#if 1
	static INT32U u32CycTs = 0;
	INT16U u16SysVolt = 0;
	static INT8U voltagelowRecoverCnt = 0;
	static INT8U voltageHighRecoverCnt = 0 ;
	DiagDtcNameType_t enDtcIndex = En_Dtc_SupplyVoltageTooLow;
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};//清0用的辅助参数；
	INT8U msgBuf[8] = {0};

	//INT8U cData[8] = {0};
	/*	if(CPU_TimerDiffTs(u32CycTs) < 100UL)
		{
			return;
		}
		u32CycTs = D_HAL_GET_CUR_MS_TS();*/

	if( TRUE == Diag_getMonitorEnableCriteria(En_Dtc_SupplyVoltageTooLow) )
	{
		u16SysVolt = Srvl_Get_SupplyVoltage();

		if(Diag_ReadDtcTestFailFlag(En_Dtc_SupplyVoltageTooHigh) == TRUE)
		{
			/*电压不高于15.5V*/
			if(u16SysVolt < D_Hgih2NormalVotValue)
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh]) >= D_Vot_DTC_TIME)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_SupplyVoltageTooHigh, FALSE);
					u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh] = D_HAL_GET_CUR_MS_TS(); 
			}
		}
		else
		{
			/* 电路电压高于16.5V */
			if(u16SysVolt > D_HgihVotValue)
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh]) >= D_Vot_DTC_TIME)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_SupplyVoltageTooHigh, TRUE);
					u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh] = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh] = D_HAL_GET_CUR_MS_TS();
			}
		}

		if(Diag_ReadDtcTestFailFlag(En_Dtc_SupplyVoltageTooLow) == TRUE)
		{
			/* 电路电压不低于9.5V */
			 if(u16SysVolt > D_Low2NormalVotValue)
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow]) >= D_Vot_DTC_TIME)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_SupplyVoltageTooLow, FALSE);
					u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow] = D_HAL_GET_CUR_MS_TS(); 
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow] = D_HAL_GET_CUR_MS_TS(); 
			}
		}
		else
		{
			/* 电路电压低于8.5V */
			if(u16SysVolt < D_LowVotValue)
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow]) >= D_Vot_DTC_TIME)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_SupplyVoltageTooLow, TRUE);
					u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow] = D_HAL_GET_CUR_MS_TS(); 
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow] = D_HAL_GET_CUR_MS_TS();
			}
		}
	}
	else
	{
		u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooLow] = D_HAL_GET_CUR_MS_TS();
		u32DiagDtcTestFailTs[En_Dtc_SupplyVoltageTooHigh] = D_HAL_GET_CUR_MS_TS();
	}
#endif
}

#if 1
/***********************************************************************************************
 * @function name:  DSMDiag_vosSeatHeatDriveFaultCheck(void)
 *
 * @description:	座椅加热驱动检测
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-11
 ***********************************************************************************************/
static void DSMDiag_vosSeatHeatDriveFaultCheck(void)
{
#if 1
//	INT8U cData[8] = {0};
//	INT16U cis = 0;
//	cData[0] = Rte_GetVfb_DrHeat();
//	cData[1] = Rte_GetVfb_DrHeatCmdFault();
//	cis = Ecual_AdcGetChlStatus(EN_Chl_DrHeatIS);
//	cData[2] = (INT8U)(cis >> 8);
//	cData[3] = (INT8U)(cis >> 0);
		
	//Ecual_CanSendMsg(FRAME_TYPE_STD, 0x666, 0x8u, cData);
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit))//司机侧座椅
	{
		//司机侧座椅加热时高端短地大于40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_DrHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, FALSE);
		}

		//司机侧座椅加热时高端开路大于200ms
		if(EN_ALARM_HEAT_TO_BAT == Rte_GetVfb_DrHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputDisconnected, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputDisconnected, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputDisconnected, FALSE); 
		}

	}
	else
	{
		Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, FALSE);//不加热时，清标志位 允许再次加热
		Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputDisconnected, FALSE);
	}


	//&&副司机侧座椅正在加热
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit))
	{
		//副司机侧座椅加热时高端短地大于40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_PaHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, FALSE);
				
		}

		//副司机侧座椅加热时高端开路大于200ms
		if(EN_ALARM_HEAT_TO_BAT == Rte_GetVfb_PaHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputDisconnected, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputDisconnected, TRUE);
		}
		else
 		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputDisconnected, FALSE);
				
		}
		
	}
	else
	{
		Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, FALSE);//不加热时，清标志位 允许再次加热
		Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputDisconnected, FALSE);//不加热时，清标志位 允许再次加热
	}
	
	//方向盘正在加热
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit))
	{
		//方向盘加热时高端短地大于40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_ThirdHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, FALSE);
				
		}

		//方向盘加热时高端开路大于200ms
		if(EN_ALARM_HEAT_TO_BAT == Rte_GetVfb_ThirdHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputDisconnected, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputDisconnected, TRUE);
		
		}
		else
 		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputDisconnected, FALSE);
				
		}
		
	}
	else
	{
		Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, FALSE);//不加热时，清标志位 允许再次加热
		Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputDisconnected, FALSE);//不加热时，清标志位 允许再次加热
	}
#endif
}


 /***********************************************************************************************
 * @function name:  DSMDiag_vosSeatHeatSensorFaultCheck(void)
 *
 * @description:	座椅加热传感器检测
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2024-01-02
 ***********************************************************************************************/
static void DSMDiag_vosSeatHeatSensorFaultCheck(void)
{
//	static INT8U testIn = 0;
//	INT8U cData[8] = {0};
//	INT16U cis = 0;
//	cData[0] = Rte_GetVfb_DrNTCFault();
//	cData[1] = Rte_GetVfb_PaNTCFault();
//	cis = Ecual_AdcGetChlStatus(EN_Chl_DrHeatNTC);;
//	cData[2] = (INT8U)(cis >> 8);
//	cData[3] = (INT8U)(cis >> 0);
//	cis = Ecual_AdcGetChlStatus(EN_Chl_PaHeatNTC);;
//	cData[4] = (INT8U)(cis >> 8);
//	cData[5] = (INT8U)(cis >> 0);
//	cData[6] = testIn++;
//	Ecual_CanSendMsg(FRAME_TYPE_STD, 0x666, 0x8u, cData);
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit))
	{
		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_DrHeatNTCFaultSts())//主驾温度传感器短地时间大于1s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, TRUE);
			
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, FALSE);
				Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, FALSE);
			}
		}
		
		if(enHeatNtcFault_EN_NTC_FAULT_OPEN == Rte_GetVfb_DrHeatNTCFaultSts())      //主驾温度传感器短电源或者开路时间大于1s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, TRUE); 
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, TRUE);
		}
		else
		{	
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, FALSE);
				Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, FALSE);
			}
			else
			{
			}

		}

		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_DrHeatNTCFaultSts() )//主驾温度传感器不可信时间大于5s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcInputIsInvalid, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcInputIsInvalid, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcInputIsInvalid) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingNtcInputIsInvalid, FALSE);
			
				Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingNtcInputIsInvalid, FALSE);
			}
			else
			{
			}
		}
	}

	//副驾NTC检测
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit))
	{

		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_PaHeatNTCFaultSts())//副驾温度传感器短地时间大于1s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, TRUE);
		}
		else
		{	
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, FALSE);
				Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, FALSE);
			}
			else
			{
			}
		}

		//副驾温度传感器短电源或者开路时间大于1s
		if(enHeatNtcFault_EN_NTC_FAULT_OPEN == Rte_GetVfb_PaHeatNTCFaultSts())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, FALSE);
				Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, FALSE);
			}
			else
			{}
			
		}


		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_PaHeatNTCFaultSts())//副驾温度传感器不可信时间大于5s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcInputIsInvalid) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, FALSE);
				Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, FALSE);
			}
			else
			{
			}
		}
	}
	
	//方向盘NTC检测
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit))
	{
		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_ThirdHeatNTCFaultSts())//方向盘温度传感器短地时间大于1s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, TRUE);
		}
		else
		{	
			if(Diag_ReadDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, FALSE);
				Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, FALSE);
			}
			else
			{
			}
		}

		//方向盘温度传感器短电源或者开路时间大于1s
		if(enHeatNtcFault_EN_NTC_FAULT_OPEN == Rte_GetVfb_ThirdHeatNTCFaultSts())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, FALSE);
				Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, FALSE);
			}
			else
			{}
			
		}


		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_ThirdHeatNTCFaultSts())//方向盘温度传感器不可信时间大于5s
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCInputIsInvalid) == TRUE)
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, FALSE);
				Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, FALSE);
			}
			else
			{
			}
		}
	}

}
#endif

 /***********************************************************************************************
 * @function name:  DSMDiag_vosSeatVentMotorFaultCheck(void)
 *
 * @description:	座椅通风电机检测
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2024-01-02
 ***********************************************************************************************/
static void DSMDiag_vosSeatVentMotorFaultCheck(void)
{
	
	INT16U vot = 0;

#if 0


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&主驾座椅正在通风
	{

		if(TRUE == Rte_GetVfb_DrVentilatePwrFault())//主驾座椅通风时，电机短地时间大于1s
		{
			if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit]) > (1000u))
			{
				u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit] = D_HAL_GET_CUR_MS_TS();
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
				
				Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
				
			}
		}
		else
		{	
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC故障才计时
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit]) > (1000u))
				{
					u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit] = D_HAL_GET_CUR_MS_TS();
					Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
				
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit] = D_HAL_GET_CUR_MS_TS();
			}
		}

	}
	else
	{
		u32DiagDtcTestFailTs[En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit] = D_HAL_GET_CUR_MS_TS();
		Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
	}


	if(Rte_GetVfb_PaVentilate() != enVentLvlSts_EN_VENT_LVL_OFF)//&&副驾座椅正在通风
	{

		if(TRUE == Rte_GetVfb_PaVentilatePwrFault())//座椅通风时，电机短地时间大于1s
		{
			if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC]) > (1000u))
			{
				u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC] = D_HAL_GET_CUR_MS_TS();
				Diag_WriteDtcTestFailFlag(En_Dtc_VentilationFan2PowerSupplySC, TRUE);
				Diag_SetDTCFlg(En_Dtc_VentilationFan2PowerSupplySC, TRUE);
				//stcondinfo_DTC.takenflg_DTC.SeatPAVenMotorShrtToGNDFlg = TRUE;
			}
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_VentilationFan2PowerSupplySC) == TRUE) //DTC故障才计时
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC]) > (1000u))
				{
					u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC] = D_HAL_GET_CUR_MS_TS();
					Diag_WriteDtcTestFailFlag(En_Dtc_VentilationFan2PowerSupplySC, FALSE);
					//stcondinfo_DTC.takenflg_DTC.SeatDRVenMotorShrtToGNDFlg = FALSE;
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC] = D_HAL_GET_CUR_MS_TS();
			}
			
		}

	}
	else
	{
		u32DiagDtcTestFailTs[En_Dtc_VentilationFan2PowerSupplySC] = D_HAL_GET_CUR_MS_TS();
		Diag_SetDTCFlg(En_Dtc_VentilationFan2PowerSupplySC, FALSE);
	}
				
#endif
}


 /***********************************************************************************************
 * @function name:  DSMDiag_vosSeatVentPWMSignalFaultCheck(void)
 *
 * @description:	座椅通风PWM信号检测
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2024-01-02
 ***********************************************************************************************/
static void DSMDiag_vosSeatVentPWMSignalFaultCheck(void)
{
#if 1


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&主驾司机座椅正在通风
	{
		//司机座椅通风时，PWM输出信号短电源故障时间大于1s
		if(enVentCmdFault_EN_VENT_FAULT_LOAD == Rte_GetVfb_DrVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply) == TRUE) //DTC故障才计时
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
				
			}
			else
			{
			}
			
		}
		//司机座椅通风时，PWM输出信号短地或开路故障时间大于1s
		if(enVentCmdFault_EN_VENT_FAULT_OPEN == Rte_GetVfb_DrVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC故障才计时
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
				
			}
		}
	}
	else
	{
		Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
		Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
	}
	


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&副驾司机座椅正在通风
	{
		//副司机座椅通风时，PWM输出信号短电源时间大于1s
		if(enVentCmdFault_EN_VENT_FAULT_LOAD == Rte_GetVfb_PaVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply) == TRUE) //DTC故障才计时
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
			}
			else
			{
			}
			
		}
		//副司机座椅通风时，PWM输出信号短地或开路时间大于1s
		if(enVentCmdFault_EN_VENT_FAULT_OPEN == Rte_GetVfb_PaVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
		
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC故障才计时
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
				
			}
		}
	}
	else
	{
		Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
		Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, FALSE);
	}
	
#endif
	
}


/***********************************************************************************************
* @function name:  DSMDiag_vosSeatAdjustProcFaultCheck(void)
*
* @description:    座椅控制检测
*
* @input parameters:	 void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   无
*
* @author:			zjx
*
* @note:		   2023-04-17
***********************************************************************************************/
static void DSMDiag_vosSeatAdjustProcFaultCheck(void) 
{
#if 1

	INT8U cData[8] = {0};
	INT16U cis = 0;
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion))
	{

		//硬线开关粘连故障-主驾纵向向前开关粘连
		if(Rte_GetVfb_DrLengthSwitchAdheErr_ForWard() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//硬线开关粘连故障-主驾纵向向后开关粘连
		if(Rte_GetVfb_DrLengthSwitchAdheErr_Back() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//硬线开关粘连故障-主驾靠背向前开关粘连
		if(Rte_GetVfb_DrBackSwitchAdheErr_ForWard() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//硬线开关粘连故障-主驾靠背向后开关粘连
		if(Rte_GetVfb_DrBackSwitchAdheErr_Back() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		
		//硬线开关粘连故障-主驾高度向上开关粘连
		if(Rte_GetVfb_DrHeightSwitchAdheErr_ForWard() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//硬线开关粘连故障-主驾高度向下开关粘连
		if(Rte_GetVfb_DrHeightSwitchAdheErr_Back() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, FALSE);
		}
	}
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion))
	{
		//硬线开关粘连故障-主驾腿托向上开关粘连
		if(Rte_GetVfb_DrFrontSwitchAdheErr_ForWard() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//硬线开关粘连故障-主驾腿托向下开关粘连
		if(Rte_GetVfb_DrFrontSwitchAdheErr_Back() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, FALSE);
		}
	}

	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion))
	{
		//硬线开关粘连故障-副驾纵向向前开关粘连
		if(Rte_GetVfb_PaLengthSwitchAdheErr_ForWard() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//硬线开关粘连故障-副驾纵向向后开关粘连
		if(Rte_GetVfb_PaLengthSwitchAdheErr_Back() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, FALSE);
		}

		//硬线开关粘连故障-副驾靠背向前开关粘连
		if(Rte_GetVfb_PaBackSwitchAdheErr_ForWard() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//硬线开关粘连故障-副驾靠背向后开关粘连
		if(Rte_GetVfb_PaBackSwitchAdheErr_Back() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		}
	}

	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingMotorHallFault))
	{
		//霍尔传感器故障 电机启动后，2s内没有接收到座椅位置传感器脉冲
		if(Rte_GetVfb_DrHeightDTCHallErr() != FALSE) //主驾高度霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, FALSE);
		}
	}
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault))
	{
		if(Rte_GetVfb_DrLengthDTCHallErr() != FALSE) //主驾纵向霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, FALSE);
		}
	}
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault))
	{
		if(Rte_GetVfb_DrBackDTCHallErr() != FALSE) //主驾靠背霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, FALSE);
		}
	}
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault))
	{
		if(Rte_GetVfb_DrFrontDTCHallErr() != FALSE) //主驾前部角度霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, FALSE);
		}
	}
		
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault))
	{
		if(Rte_GetVfb_PaLengthDTCHallErr() != FALSE) //副驾纵向霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, FALSE);
		}
	}
	
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault))
	{
		if(Rte_GetVfb_PaBackDTCHallErr() != FALSE) //副驾靠背霍尔丢失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, FALSE);
		}
	}
	
	//主驾高纵向、靠背继电器开关粘连
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued))
	{
		if(Rte_GetVfb_DrHeightRelayAdheErr() != FALSE) //主驾高度继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, FALSE);
		}
		
		if(Rte_GetVfb_DrLengthRelayAdheErr() != FALSE) //主驾纵向继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, TRUE);	
		}
		else //无命令，无电压，故障消失
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, FALSE);
		}

		if(Rte_GetVfb_DrBackRelayAdheErr() != FALSE) //主驾靠背继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, TRUE);
			
		}
		else //无命令，无电压，故障消失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, FALSE);
		}
	}
	
	//主驾前部角度继电器开关粘连
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued))
	{
		if(Rte_GetVfb_DrFrontRelayAdheErr() != FALSE) //主驾前部角度继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, TRUE);
		}
		else //无命令，无电压，故障消失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, FALSE);
		}
	}
		
	//副驾继电器开关粘连
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued))
	{
		if(Rte_GetVfb_PaLengthRelayAdheErr() != FALSE) //副驾纵向继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, TRUE);

		}
		else//无命令，无电压，故障消失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, FALSE);
		}

		if(Rte_GetVfb_PaBackRelayAdheErr() != FALSE) //副驾靠背继电器开关粘连 (无命令有电压)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, TRUE);
			
		}
		else //无命令，无电压，故障消失
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, FALSE);
		}
		
	}
	
#endif
}


#if 0
/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_LinNodeComLostOpt(void)
* @par 描述
       LIN节点相关故障
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-13
************************************************************************************************************************
*/
static void Diag_LinNodeComLostOpt(void)
{
	static INT32U u32CycTs = 0;
	static INT32U u32PowerOnTs = 0;
	INT8U bPowerMode = 0;
	INT8U eTimeCount = 0;//用来初始化时间记录
	static INT8U errorCount[En_DtcType_MaxNum] = {0};
	if(CPU_TimerDiffTs(u32CycTs) < 100UL)
	{
		return;
	}
	u32CycTs = D_HAL_GET_CUR_MS_TS();
	bPowerMode = Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);
	if((bPowerMode != 2u) && (bPowerMode != 4U))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		return;
	}
	else
	{
		/*ON电及以上没有达到3s不执行通讯类故障码置位*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			for(eTimeCount = En_Dtc_NocommunicationonLIN1 ; eTimeCount < En_Dtc_LeftDIFlasher_OvercurrentOrSCG ; eTimeCount++)
			{
				u32DiagDtcTestFailTs[eTimeCount] = D_HAL_GET_CUR_MS_TS();
			}
			return;
		}
	}
	if (Diag_CommDtcWorkInd == TRUE) /*电压范围正常、其他ecu初始化完成*/
	{
		if (Diag_CommMsgTimeoutInd == TRUE)
		{
			if(Srv_GetMemCfgData(VEHENEBSPRM) == 0x00u) //未配置EBS直接退出检测;
			{
				return ;
			}
			/*LIN1 通讯丢失 若检测到Lin1上所有报文丢失且持续时间t >= 20倍发送周期，置故障码*/
			if( (Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x34) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x35) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x36) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x37) == FALSE) )
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_NocommunicationonLIN1]) > D_LostCom_HoldOnTime)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_NocommunicationonLIN1, TRUE);//N822,lin上只有一个EBS，丢了EBS应该置两个DTC
					Diag_WriteDtcTestFailFlag(En_Dtc_LIN_EBS_Absent, TRUE);
				}
			}
			else
			{
				u32DiagDtcTestFailTs[En_Dtc_NocommunicationonLIN1] = D_HAL_GET_CUR_MS_TS();
				Diag_WriteDtcTestFailFlag(En_Dtc_NocommunicationonLIN1, FALSE);
				Diag_WriteDtcTestFailFlag(En_Dtc_LIN_EBS_Absent, FALSE);
			}
		}
	}
	/*后续代码是EBS的lin信号错误*/
	if(1 == LinRx_0x34_EBS_Error_Ident()) //EBS ID校验错误
	{
		errorCount[En_Dtc_EBS_Error_Ident] = errorCount[En_Dtc_EBS_Error_Ident] + 1;
		if(errorCount[En_Dtc_EBS_Error_Ident] > 4)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_EBS_Error_Ident, TRUE);
			errorCount[En_Dtc_EBS_Error_Ident] = 4;
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_EBS_Error_Ident, FALSE);
		errorCount[En_Dtc_EBS_Error_Ident] = 0;
	}

	if(1 == LinRx_0x34_EBS_Error_Calib()) //EBS数据校验故障
	{
		errorCount[En_Dtc_EBS_Error_Calib] = errorCount[En_Dtc_EBS_Error_Calib] + 1;
		if(errorCount[En_Dtc_EBS_Error_Calib] > 4)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_EBS_Error_Calib, TRUE);
			errorCount[En_Dtc_EBS_Error_Calib] = 4;
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_EBS_Error_Calib, FALSE);
		errorCount[En_Dtc_EBS_Error_Calib] = 0;
	}

	if(1 == LinRx_0x34_EBS_Resp_Error()) //EBS节点响应错误
	{
		errorCount[En_Dtc_EBSRespError] = errorCount[En_Dtc_EBSRespError] + 1;
		if(errorCount[En_Dtc_EBSRespError] > 4)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_EBSRespError, TRUE);
			errorCount[En_Dtc_EBSRespError] = 4;
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_EBSRespError, FALSE);
		errorCount[En_Dtc_EBSRespError] = 0;
	}
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_TLE75RlyFaltOpt(void)
* @par 描述
       TLE75Xz驱动相关故障
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-16
************************************************************************************************************************
*/

static void Diag_TLE75RlyFaltOpt(void)
{
	INT8U u8CfgVehOpModePrm = Srv_GetMemCfgData((INT8U)VEHENPEPSPRM);
	BOOL bIGNSw = FALSE;
	static INT32U u32PowerOnTs = 0;
	static INT8U TleErrorCount[En_DtcType_MaxNum] = {0};
	/* ACC IGN1 IGN2继电器 错误状态判断 */
	INT8U  bPowerMode = 0;
	bPowerMode = Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);

	if((bPowerMode != 2u) && (bPowerMode != 4U))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		return;
	}
	else
	{
		/*ON电及以上没有达到3s不执行通讯类故障码置位*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			return;
		}
	}




}

#endif
/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName)
* @par 描述
       BTS高驱输出错误判断
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-17
************************************************************************************************************************
*/
static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName)
{
	INT8U i = 0;
	strDiagBtsHDriverIsCheckTbl_t *pDiagBtsHDriverIsCheck = NULL;

	GpioSignalName_t GpioName = EN_GPIO_ALL_NUM;
	INT8U u8BtsHighDrvChip = 0;
	INT8U u8BtsHighDrvChipChl = 0;
	INT8U u8FaultSort = 0;
	INT16U u16LoadDownImA = 0;
	INT16U u16LoadUpImA = 0;

	INT16U u16DriverISTemp = 0;
	BOOL bRet = FALSE;
	static INT8U errorCount[En_DtcType_MaxNum] = {0};

	for(i = 0; i < (INT16U)IO_DiagBtsHDriverIsCheckTbl_NUM ; i++)
	{
		if(DiagBtsHDriverIsCheckTbl[i].DtcName ==  enDtcName)
		{
			pDiagBtsHDriverIsCheck = &DiagBtsHDriverIsCheckTbl[i];
			break;
		}
	}

	if(pDiagBtsHDriverIsCheck != NULL)
	{
		GpioName = pDiagBtsHDriverIsCheck->GpioName;
		u8BtsHighDrvChip = pDiagBtsHDriverIsCheck->u8BtsHighDrvChip;
		u8BtsHighDrvChipChl = pDiagBtsHDriverIsCheck->u8BtsHighDrvChipChl;

		u8FaultSort = pDiagBtsHDriverIsCheck->u8FaultSort;
		u16LoadDownImA = pDiagBtsHDriverIsCheck->u16LoadDownImA;
		u16LoadUpImA = pDiagBtsHDriverIsCheck->u16LoadUpImA;


//		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OpenLoad) && (u16LoadDownImA != 0U) )
		{
			if(u16DriverISTemp < u16LoadDownImA)
			{
				if(errorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					errorCount[enDtcName] = D_TURN_LIGHT_COUNT;
					bRet = TRUE;
				}
				else
				{
					errorCount[enDtcName] = errorCount[enDtcName] + 1;
				}
			}
			else
			{
				errorCount[enDtcName] = 0;
			}
		}

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OverLoad) && (u16LoadUpImA != 0U) )
		{
			if(u16DriverISTemp > u16LoadUpImA)
			{
				if(errorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					errorCount[enDtcName] = D_TURN_LIGHT_COUNT;
					bRet = TRUE;
				}
				else
				{
					errorCount[enDtcName] = errorCount[enDtcName] + 1;
				}
			}
			else
			{
				errorCount[enDtcName] = 0;
			}
		}

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_LackLoad) && \
				(u16LoadUpImA != 0U) && (u16LoadDownImA != 0U) )
		{
			if( (u16DriverISTemp > u16LoadDownImA) && (u16DriverISTemp < u16LoadUpImA) )
			{
				if(errorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					bRet = TRUE;
					errorCount[enDtcName] = D_TURN_LIGHT_COUNT;
				}
				else
				{
					errorCount[enDtcName] = errorCount[enDtcName] + 1;
				}
			}
			else
			{
				errorCount[enDtcName] = 0;
			}
		}

		Diag_WriteDtcTestFailFlag(enDtcName, bRet);
	}

	return bRet;
}


static BOOL Diag_ReturnValueDeal(BOOL *bReturnValue, INT8U u8DTCTypeCnt)
{
	BOOL bRet = FALSE;
	INT8U u8Counter = 0x0u;

	for(u8Counter = 0; u8Counter < u8DTCTypeCnt; u8Counter ++)
	{
		if(TRUE == bReturnValue[u8Counter])
		{
			bRet = TRUE;
			break;
		}
		else
		{
			bRet = FALSE;
		}
	}
	return bRet;
}
#if 0
/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName)
* @par 描述
       BTS高驱输出错误判断(此函数专用于左转向灯和右转向灯的短路及损坏)
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-17
************************************************************************************************************************
*/
static BOOL Diag_BtsHighDriversChipSpeFaultCheck(DiagDtcNameType_t enDtcName)
{
	INT8U i = 0;
	strDiagBtsHDriverIsCheckTbl_t *pDiagBtsHDriverIsCheck = NULL;

	GpioSignalName_t GpioName = EN_GPIO_ALL_NUM;
	INT8U u8BtsHighDrvChip = 0;
	INT8U u8BtsHighDrvChipChl = 0;
	INT8U u8FaultSort = 0;
	INT16U u16LoadDownImA = 0;
	INT16U u16LoadUpImA = 0;

	INT16U u16DriverISTemp = 0;
	static BOOL bRet[En_DtcType_MaxNum] = {0};

	for(i = 0; i < (INT16U)IO_DiagBtsHDriverIsCheckTbl_NUM ; i++)
	{
		if(DiagBtsHDriverIsCheckTbl[i].DtcName ==  enDtcName)
		{
			pDiagBtsHDriverIsCheck = &DiagBtsHDriverIsCheckTbl[i];
			break;
		}
	}

	if(pDiagBtsHDriverIsCheck != NULL)
	{
		GpioName = pDiagBtsHDriverIsCheck->GpioName;
		u8BtsHighDrvChip = pDiagBtsHDriverIsCheck->u8BtsHighDrvChip;
		u8BtsHighDrvChipChl = pDiagBtsHDriverIsCheck->u8BtsHighDrvChipChl;

		u8FaultSort = pDiagBtsHDriverIsCheck->u8FaultSort;
		u16LoadDownImA = pDiagBtsHDriverIsCheck->u16LoadDownImA;
		u16LoadUpImA = pDiagBtsHDriverIsCheck->u16LoadUpImA;

		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);
		if(u16DriverISTemp == 0U)
		{
			//刚驱动转向灯的时候电流为0，该函数也只检测过载和损坏
			return Diag_ReadDtcTestFailFlag(enDtcName);
		}

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_LackLoad) && \
				(u16LoadUpImA != 0U) && (u16LoadDownImA != 0U) )
		{
			//损坏值的范围
			if( (u16DriverISTemp > u16LoadDownImA) && (u16DriverISTemp < u16LoadUpImA) )
			{
				if(u32BtsErrorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					bBtsRet[enDtcName] = TRUE;
					u32BtsErrorCount[enDtcName] = D_TURN_LIGHT_COUNT;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] + 1;
				}
			}
			else
			{
				if(u32BtsErrorCount[enDtcName] != 0)
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] - 1;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = 0;
					bBtsRet[enDtcName] = FALSE;
				}
			}
		}
		Diag_WriteDtcTestFailFlag(enDtcName, bBtsRet[enDtcName]);
	}

	return bBtsRet[enDtcName];
}

static BOOL Diag_BtsHighDriversChipSpeFaultCheckOver(DiagDtcNameType_t enDtcName)
{
	INT8U i = 0;
	strDiagBtsHDriverIsCheckTbl_t *pDiagBtsHDriverIsCheck = NULL;

	GpioSignalName_t GpioName = EN_GPIO_ALL_NUM;
	INT8U u8BtsHighDrvChip = 0;
	INT8U u8BtsHighDrvChipChl = 0;
	INT8U u8FaultSort = 0;
	INT16U u16LoadDownImA = 0;
	INT16U u16LoadUpImA = 0;

	INT16U u16DriverISTemp = 0;
	static BOOL bRet = FALSE;

	for(i = 0; i < (INT16U)IO_DiagBtsHDriverIsCheckTbl_NUM ; i++)
	{
		if(DiagBtsHDriverIsCheckTbl[i].DtcName ==  enDtcName)
		{
			pDiagBtsHDriverIsCheck = &DiagBtsHDriverIsCheckTbl[i];
			break;
		}
	}

	if(pDiagBtsHDriverIsCheck != NULL)
	{
		GpioName = pDiagBtsHDriverIsCheck->GpioName;
		u8BtsHighDrvChip = pDiagBtsHDriverIsCheck->u8BtsHighDrvChip;
		u8BtsHighDrvChipChl = pDiagBtsHDriverIsCheck->u8BtsHighDrvChipChl;

		u8FaultSort = pDiagBtsHDriverIsCheck->u8FaultSort;
		u16LoadDownImA = pDiagBtsHDriverIsCheck->u16LoadDownImA;
		u16LoadUpImA = pDiagBtsHDriverIsCheck->u16LoadUpImA;

		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);
		if(u16DriverISTemp == 0U)
		{
			//刚驱动转向灯的时候电流为0，该函数也只检测过载和损坏
			return Diag_ReadDtcTestFailFlag(enDtcName);
		}
		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OverLoad) && (u16LoadUpImA != 0U) )
		{
			if(u16DriverISTemp > u16LoadUpImA)
			{
				if(u32BtsErrorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					bBtsRet[enDtcName] = TRUE;
					u32BtsErrorCount[enDtcName] = D_TURN_LIGHT_COUNT;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] + 1;
				}
			}
			else
			{
				if(u32BtsErrorCount[enDtcName] != 0)
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] - 1;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = 0;
					bBtsRet[enDtcName] = FALSE;
				}
			}
		}
		Diag_WriteDtcTestFailFlag(enDtcName, bBtsRet[enDtcName]);
	}

	return bBtsRet[enDtcName];
}

static BOOL Diag_BtsHighDriversChipSpeFaultCheckOPEN(DiagDtcNameType_t enDtcName)
{
	INT8U i = 0;
	strDiagBtsHDriverIsCheckTbl_t *pDiagBtsHDriverIsCheck = NULL;

	GpioSignalName_t GpioName = EN_GPIO_ALL_NUM;
	INT8U u8BtsHighDrvChip = 0;
	INT8U u8BtsHighDrvChipChl = 0;
	INT8U u8FaultSort = 0;
	INT16U u16LoadDownImA = 0;
	INT16U u16LoadUpImA = 0;

	INT16U u16DriverISTemp = 0;
	static BOOL bRet = FALSE;

	for(i = 0; i < (INT16U)IO_DiagBtsHDriverIsCheckTbl_NUM ; i++)
	{
		if(DiagBtsHDriverIsCheckTbl[i].DtcName ==  enDtcName)
		{
			pDiagBtsHDriverIsCheck = &DiagBtsHDriverIsCheckTbl[i];
			break;
		}
	}

	if(pDiagBtsHDriverIsCheck != NULL)
	{
		GpioName = pDiagBtsHDriverIsCheck->GpioName;
		u8BtsHighDrvChip = pDiagBtsHDriverIsCheck->u8BtsHighDrvChip;
		u8BtsHighDrvChipChl = pDiagBtsHDriverIsCheck->u8BtsHighDrvChipChl;

		u8FaultSort = pDiagBtsHDriverIsCheck->u8FaultSort;
		u16LoadDownImA = pDiagBtsHDriverIsCheck->u16LoadDownImA;
		u16LoadUpImA = pDiagBtsHDriverIsCheck->u16LoadUpImA;

		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OpenLoad) && (u16LoadDownImA != 0U) )
		{
			if(u16DriverISTemp < u16LoadDownImA)
			{
				if(u32BtsErrorCount[enDtcName] >= D_TURN_LIGHT_COUNT)
				{
					u32BtsErrorCount[enDtcName] = D_TURN_LIGHT_COUNT;
					bBtsRet[enDtcName] = TRUE;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] + 1;
				}
			}
			else
			{
				if(u32BtsErrorCount[enDtcName] != 0)
				{
					u32BtsErrorCount[enDtcName] = u32BtsErrorCount[enDtcName] - 1;
				}
				else
				{
					u32BtsErrorCount[enDtcName] = 0;
					bBtsRet[enDtcName] = FALSE;
				}
			}
		}

		Diag_WriteDtcTestFailFlag(enDtcName, bBtsRet[enDtcName]);
	}

	return bBtsRet[enDtcName];
}

/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Diag_Bts_PosLp1Ctrl_RearFogLpCtrl_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-16
************************************************************************************************************************
*/
static BOOL Diag_Bts_PosLp1Ctrl_RearFogLpCtrl_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	BOOL bRet[4] = {FALSE};

	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_RearFogLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_PosLp1Ctrl);

	/* 后雾灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_RearFogLamp_OverCurrentOrSCG);
			bRet[1] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_RearFogLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_RearFogLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_RearFogLamp_OpenLoadOrSCV, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 位置灯 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[1]) > D_OutPutValid_HoldOnTime)
		{
			bRet[2] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_SideBeamLamp_OverCurrentOrSCG);
			bRet[3] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_SideBeamLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OpenLoadOrSCV, FALSE);
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 4);
}

/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Diag_Bts_RightDIFlasher_LeftDIFlasher_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-16
************************************************************************************************************************
*/
static BOOL Diag_Bts_RightDIFlasher_LeftDIFlasher_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	BOOL bRet[6] = {FALSE};
	static INT8U u8PreRightTurnLightErrorFlag = 0x0u;
	INT8U u8TurnSts = Srvl_Get_D_Simulink_TurnLightSt(D_Simulink_TurnLightSt);
	if(u8TurnSts == 0)
	{
		//u32BtsErrorCount[En_Dtc_RightDIFlasher_OvercurrentOrSCG] = 0;
		//u32BtsErrorCount[En_Dtc_RightDIFlasher_OneMainLampOpenLoad] = 0;
		//u32BtsErrorCount[En_Dtc_LeftDIFlasher_OvercurrentOrSCG] = 0;
		//u32BtsErrorCount[En_Dtc_LeftDIFlasher_OneMainLampOpenLoad] = 0;
		//u32BtsErrorCount[En_Dtc_LeftDIFlasher_OpenLoadOrSCV] = 0;
		//u32BtsErrorCount[En_Dtc_RightDIFlasher_OpenLoadOrSCV] = 0;
		u8LeftTurnLightErrorFlag = 0;
		u8RightTurnLightErrorFlag = 0;
		bBtsRet[En_Dtc_RightDIFlasher_OvercurrentOrSCG] = FALSE;
		bBtsRet[En_Dtc_RightDIFlasher_OneMainLampOpenLoad] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OvercurrentOrSCG] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OneMainLampOpenLoad] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OpenLoadOrSCV] = FALSE;
		bBtsRet[En_Dtc_RightDIFlasher_OpenLoadOrSCV] = FALSE;
		Diag_WriteDtcTestFailFlag(En_Dtc_RightDIFlasher_OvercurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_RightDIFlasher_OneMainLampOpenLoad, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_LeftDIFlasher_OvercurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_LeftDIFlasher_OneMainLampOpenLoad, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_LeftDIFlasher_OpenLoadOrSCV, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_RightDIFlasher_OpenLoadOrSCV, FALSE);
	}
	if(Srvl_Get_D_Simulink_TurnDiagFg(D_Simulink_TurnDiagFg) == 0)
	{
		return FALSE;
	}
	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_RightDirLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_LeftDirLpCtrl);

	/* 右转向灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{

		//bRet[0] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheckOver(En_Dtc_RightDIFlasher_OvercurrentOrSCG);
		//bRet[1] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheckOPEN(En_Dtc_RightDIFlasher_OpenLoadOrSCV);
		//bRet[2] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheck(En_Dtc_RightDIFlasher_OneMainLampOpenLoad);
		if((bRet[0] != FALSE) || (bRet[1] != FALSE) || (bRet[2] != FALSE))
		{
			u8RightTurnLightErrorFlag = 0x1u;
		}
		else
		{
			u8RightTurnLightErrorFlag = 0x0u;
		}
	}
	else
	{
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 左转向灯 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		//bRet[3] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheckOver(En_Dtc_LeftDIFlasher_OvercurrentOrSCG);
		//bRet[4] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheckOPEN(En_Dtc_LeftDIFlasher_OpenLoadOrSCV);
		//bRet[5] = (BOOL)Diag_BtsHighDriversChipSpeFaultCheck(En_Dtc_LeftDIFlasher_OneMainLampOpenLoad);
		if((bRet[3] != FALSE) || (bRet[4] != FALSE) || (bRet[5] != FALSE))
		{
			u8LeftTurnLightErrorFlag = 0x1u;
		}
		else
		{
			u8LeftTurnLightErrorFlag = 0x0u;
		}
	}
	else
	{
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 6);
}

INT8U GetLeftTurnLightError(void)
{
	return u8LeftTurnLightErrorFlag;
}

INT8U GetRightTurnLightError(void)
{
	return u8RightTurnLightErrorFlag;
}

/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Diag_Bts_LhFrFogLamp_RhFrFogLamp_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-16
************************************************************************************************************************
*/
static BOOL Diag_Bts_LhFrFogLamp_RhFrFogLamp_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	BOOL bRet[4] = {FALSE};

	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_FrontLeftFogLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_FrontRightFogLpCtrl);

	/* 左前雾灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			//bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_LhFrFogLamp_OverCurrentOrSCG);
			//bRet[1] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_LhFrFogLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_LhFrFogLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_LhFrFogLamp_OpenLoadOrSCV, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 右前雾灯 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[1]) > D_OutPutValid_HoldOnTime)
		{
			bRet[2] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_RhFrFogLamp_OverCurrentOrSCG);
			bRet[3] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_RhFrFogLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_RhFrFogLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_RhFrFogLamp_OpenLoadOrSCV, FALSE);
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 4);
}

/*!
************************************************************************************************************************
* @par 接口原型
	   static BOOL Diag_Bts_LeftRightCornerLp_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static BOOL Diag_Bts_LeftRightCornerLp_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	BOOL bRet[4] = {FALSE};

	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_LeftCornerLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_RightCornerLpCtrl);


	/* 左角灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_Leftcornerlamp_OverCurrentOrSCG);
			bRet[1] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_Leftcornerlamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_Leftcornerlamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_Leftcornerlamp_OpenLoadOrSCV, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 右角灯 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[1]) > D_OutPutValid_HoldOnTime)
		{
			bRet[2] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_Rightcornerlamp_OverCurrentOrSCG);
			bRet[3] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_Rightcornerlamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_Rightcornerlamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_Rightcornerlamp_OpenLoadOrSCV, FALSE);
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 4);
}

/*!
************************************************************************************************************************
* @par 接口原型
	   static BOOL Diag_Bts_DayRunLpPosLp_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static BOOL Diag_Bts_DayRunLpPosLp_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};//清零用的辅助函数
	BOOL bRet[4] = {FALSE};
	INT16U u16DriverISTemp = 0 ;
	static INT8U u8OverCurrentCount = 0;
	static INT8U u8OpenLoadCount = 0;
	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_DayRunLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_PosLpCtrl);

	/* 日间行车灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_DayDriveLamp_OverCurrentOrSCG);
			bRet[1] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_DayDriveLamp_OpenLoadOrSCV);
		}

	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_DayDriveLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_DayDriveLamp_OpenLoadOrSCV, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 小灯2 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(Diag_ReadDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG) == FALSE)
		{
			u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DayRunLpPosLp, 1); //小灯负载2电流
			if(u16DriverISTemp > 4400) //小灯2过载电流4.4A
			{
				if(u8OverCurrentCount >= D_TURN_LIGHT_COUNT)
				{
					u8OverCurrentCount = D_TURN_LIGHT_COUNT;
					Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG, TRUE);
				}
				else
				{
					u8OverCurrentCount = u8OverCurrentCount + 1;
				}

			}
			else
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG, FALSE);
				u8OverCurrentCount = 0;
			}
		}

		if(Diag_ReadDtcTestFailFlag(En_Dtc_SideBeamLamp_OpenLoadOrSCV) == FALSE)
		{
			u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DayRunLpPosLp, 1); //小灯负载2电流
			if(u16DriverISTemp < 10) //小灯2开路电流小于0.01A
			{
				if(u8OpenLoadCount >= D_TURN_LIGHT_COUNT)
				{
					u8OpenLoadCount = D_TURN_LIGHT_COUNT;
					Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OpenLoadOrSCV, TRUE);
				}
				else
				{
					u8OpenLoadCount = u8OpenLoadCount + 1;
				}
			}
			else
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OpenLoadOrSCV, FALSE);
				u8OpenLoadCount = 0;
			}
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_SideBeamLamp_OpenLoadOrSCV, FALSE);
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 4);
}


/*!
************************************************************************************************************************
* @par 接口原型
	   static BOOL Diag_Bts_ReverseLpBrakeLp_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static BOOL Diag_Bts_ReverseLpBrakeLp_FaltOpt(void)
{
	GpioLevel_t enIn[2] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[2] = {0};
	BOOL bRet[4] = {FALSE};

	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_ReverseLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_BrakeLpCtrl);

	/* 倒车灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_ReverseLamp_OverCurrentOrSCG);
			bRet[1] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_ReverseLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_ReverseLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_ReverseLamp_OpenLoadOrSCV, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}

	/* 刹车灯 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[1]) > D_OutPutValid_HoldOnTime)
		{
			bRet[2] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_LBrakeLamp_OverCurrentOrSCG);
			bRet[3] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_LBrakeLamp_OpenLoadOrSCV);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_LBrakeLamp_OverCurrentOrSCG, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_LBrakeLamp_OpenLoadOrSCV, FALSE);
		Ts[1] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 4);
}
/*!
************************************************************************************************************************
* @par 接口原型
	   static  BOOL Diag_Bts_DOME_LAMP_FaltOpt(void)
* @par 描述

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/

static BOOL Diag_Bts_DOME_LAMP_FaltOpt(void)
{
	GpioLevel_t enIn[1] = { EN_GPIO_LEV_NONE };
	static INT32U Ts[1] = {0};
	BOOL bRet[4] = {FALSE};

	//enIn[0] = Ecual_GpioGetChlState(EN_PWM_OUT_DomeLpCtrl);

	/* 室顶灯 */
	if(enIn[0] == EN_GPIO_LEV_HIGH)
	{
		if(CPU_TimerDiffTs(Ts[0]) > D_OutPutValid_HoldOnTime)
		{
			bRet[0] = Diag_BtsHighDriversChipFaultCheck(En_Dtc_RoomLampShortcircuittoVbat);
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_RoomLampShortcircuittoVbat, FALSE);
		Ts[0] = D_HAL_GET_CUR_MS_TS();
	}
	return Diag_ReturnValueDeal(bRet, 2);
}
/*!
************************************************************************************************************************
* @par 接口原型
       static void Diag_TLE75RlyFaltOpt(void)
* @par 描述
       TLE75Xz驱动相关故障
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-16
************************************************************************************************************************
*/
static void Diag_BtsHighDriversChipFaultOpt(void)
{
	static INT32U u32CycTs = 0;
	static INT32U u32PowerOnTs = 0;
	INT8U bPowerMode = 0;
	INT8U eTimeCount = 0;
	if(CPU_TimerDiffTs(u32CycTs) < 50UL)
	{
		return;
	}
	u32CycTs = D_HAL_GET_CUR_MS_TS();
	bPowerMode = Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);
	if((bPowerMode != 2u) && (bPowerMode != 4U))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		for(eTimeCount = En_Dtc_LeftDIFlasher_OvercurrentOrSCG ; eTimeCount < En_Dtc_ReserveNC7_OUT_OverCurrentOrSCG ; eTimeCount++)
		{
			Diag_WriteDtcTestFailFlag(eTimeCount, FALSE);
		}
		for(eTimeCount = En_Dtc_RearFogLamp_OverCurrentOrSCG ; eTimeCount < En_Dtc_ReserveNC9_OUT_OverCurrentOrSCG ; eTimeCount++)
		{
			Diag_WriteDtcTestFailFlag(eTimeCount, FALSE);
		}
		u32BtsErrorCount[En_Dtc_RightDIFlasher_OvercurrentOrSCG] = 0;
		u32BtsErrorCount[En_Dtc_RightDIFlasher_OneMainLampOpenLoad] = 0;
		u32BtsErrorCount[En_Dtc_LeftDIFlasher_OvercurrentOrSCG] = 0;
		u32BtsErrorCount[En_Dtc_LeftDIFlasher_OneMainLampOpenLoad] = 0;
		u32BtsErrorCount[En_Dtc_LeftDIFlasher_OpenLoadOrSCV] = 0;
		u32BtsErrorCount[En_Dtc_RightDIFlasher_OpenLoadOrSCV] = 0;
		u8LeftTurnLightErrorFlag = 0;
		u8RightTurnLightErrorFlag = 0;
		bBtsRet[En_Dtc_RightDIFlasher_OvercurrentOrSCG] = FALSE;
		bBtsRet[En_Dtc_RightDIFlasher_OneMainLampOpenLoad] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OvercurrentOrSCG] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OneMainLampOpenLoad] = FALSE;
		bBtsRet[En_Dtc_LeftDIFlasher_OpenLoadOrSCV] = FALSE;
		bBtsRet[En_Dtc_RightDIFlasher_OpenLoadOrSCV] = FALSE;

		return;
	}
	else
	{
		/*ON电及以上没有达到3s不执行通讯类故障码置位*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			return;
		}
	}

	Diag_Bts_PosLp1Ctrl_RearFogLpCtrl_FaltOpt();
	Diag_Bts_RightDIFlasher_LeftDIFlasher_FaltOpt();
	Diag_Bts_LhFrFogLamp_RhFrFogLamp_FaltOpt();
	Diag_Bts_LeftRightCornerLp_FaltOpt();
	Diag_Bts_DayRunLpPosLp_FaltOpt();
	Diag_Bts_ReverseLpBrakeLp_FaltOpt();
	Diag_Bts_DOME_LAMP_FaltOpt();
}

/*!
************************************************************************************************************************
* @par 接口原型
	   static void Diag_OutReserveratureFaultOpt(void)
* @par 描述
       温度传感器故障
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static void Diag_OutReserveratureFaultOpt(void)
{
	INT16U u16TempDetectSensor = 0;
	static INT32U u32PowerOnTs = 0;
	static INT8U bErrorCount1 = 0;
	static INT8U bErrorCount2 = 0;
	INT8U bPowerMode = 0;
	bPowerMode = Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);
	if((bPowerMode != 2u) && (bPowerMode != 4U))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		return;
	}
	else
	{
		/*ON电及以上没有达到3s不执行通讯类故障码置位*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			bErrorCount1 = 0;
			bErrorCount2 = 0;
			return;
		}
	}
#if  0
	u16TempDetectSensor = Ecual_AdcGetChlStatus(EN_Chl_TempDetectSensor);
	if(u16TempDetectSensor < D_TEMPSHORT_VALUE)
	{
		bErrorCount1++;
		if(bErrorCount1 > 20)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_OutReserveratureShortcircuittoGND, TRUE);
			bErrorCount1 = 20;
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_OutReserveratureShortcircuittoGND, FALSE);
		bErrorCount1 = 0;
	}

	if(u16TempDetectSensor >= 50000UL)//读取出来的值是50000UL，所以要报该故障不能大于50000UL
	{
		bErrorCount2++;
		if(bErrorCount2 > 20)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_OutReserveratureShortcircuittoVbat, TRUE);
			bErrorCount2 = 20;
		}
	}
	else
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_OutReserveratureShortcircuittoVbat, FALSE);
		bErrorCount2 = 0;
	}
#endif
}

/*!
************************************************************************************************************************
* @par 接口原型
	   static void Diag_FeedbackFailure(void)
* @par 描述
       回读不一致错误记录 (左前门锁状态开关错误
       ，前雨刮回位信号错误，ACC,IG1,IG2继电器回位信号错误)
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static void Diag_FeedbackFailure(void)
{
	INT8U msgBuf[8] = {0};
	INT8U u8CfgVehOpModePrm = Srv_GetMemCfgData((INT8U)VEHENPEPSPRM);
	//msgBuf[0] = BCM_FrontWiperSts;
	/*左前门锁状态*/
	
	{
		u32DiagDtcTestFailTs[En_Dtc_DoorLockStatusDrSwitchLogicError] = D_HAL_GET_CUR_MS_TS();
		Diag_WriteDtcTestFailFlag(En_Dtc_DoorLockStatusDrSwitchLogicError, FALSE);
	}

	/*前雨刮回位信号*/
	
	{
		u32DiagDtcTestFailTs[En_Dtc_FrontWiperZeroPositionSwitchLogicError] = D_HAL_GET_CUR_MS_TS();
	}

	if(u8CfgVehOpModePrm == 0) //配置成非PEPS才可以用这些DTC
	{

	}

}
/*!
************************************************************************************************************************
* @par 接口原型
	   static void Diag_SpecialDtc(void)
* @par 描述
       主要是拿来处理不用上ON档的，比如防盗喇叭继电器
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-8-18
************************************************************************************************************************
*/
static void Diag_SpecialDtc(void)
{
	
	{
		Diag_WriteDtcTestFailFlag(En_Dtc_SireRelay_ShortCircuitToBat, FALSE);
		Diag_WriteDtcTestFailFlag(En_Dtc_SireRelay_OpenLoadOrSCG, FALSE);
	}
}

DiagLoadDat_t DiagLoadCtrl[EN_DIAG_LOAD_MAX] =
{
#if 0
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_RearFogLamp_OverCurrentOrSCG, 	/* 后雾灯过流或对地短路 */
		En_Dtc_RearFogLamp_OpenLoadOrSCV, 		/* 后雾灯开路或对电源短路 */
		0,
		50U,
		1000U,
		0,
	},

	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_SideBeamLamp_OverCurrentOrSCG,	/* 位置灯过流或对地短路   */
		En_Dtc_SideBeamLamp_OpenLoadOrSCV,		/* 位置灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},

	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LeftDIFlasher_OvercurrentOrSCG, 	/* 左转向灯过流或对地短路 */
		En_Dtc_LeftDIFlasher_OpenLoadOrSCV, 	/* 左转向灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},

	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_RightDIFlasher_OvercurrentOrSCG, /* 右转向灯过流或对地短路 */
		En_Dtc_RightDIFlasher_OpenLoadOrSCV, 	/* 右转向灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LhFrFogLamp_OverCurrentOrSCG, 	/* 左前雾灯过流或对地短路 */
		En_Dtc_LhFrFogLamp_OpenLoadOrSCV, 		/* 左前雾灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_RhFrFogLamp_OverCurrentOrSCG, 	/* 右前雾灯过流或对地短路 */
		En_Dtc_RhFrFogLamp_OpenLoadOrSCV, 		/* 右前雾灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_Leftcornerlamp_OverCurrentOrSCG, 	/* 左角灯过流或对地短路 */
		En_Dtc_Leftcornerlamp_OpenLoadOrSCV, 		/* 左角灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_Rightcornerlamp_OverCurrentOrSCG, 	/* 右角灯过流或对地短路 */
		En_Dtc_Rightcornerlamp_OpenLoadOrSCV, 		/* 右角灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_DayDriveLamp_OverCurrentOrSCG, 		/* 日间行车灯过流或对地短路 */
		En_Dtc_DayDriveLamp_OpenLoadOrSCV, 			/* 日间行车灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		0,
		0,
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_ReverseLamp_OverCurrentOrSCG, 		/* 倒车灯过流或对地短路 */
		En_Dtc_ReverseLamp_OpenLoadOrSCV, 			/* 倒车灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LBrakeLamp_OverCurrentOrSCG, 		/* 刹车灯过流或对地短路 */
		En_Dtc_LBrakeLamp_OpenLoadOrSCV, 			/* 刹车灯开路或对电源短路 */
		0,
		50U,
		1000U, 0,
	},
	//{NULL, 0, &Ecual_Tle75xxxCtrlStaGet,	eHighBeamRly, 0, 0, 0, 50U,	1000U, 0,},
	//{NULL, 0, &Ecual_Tle75xxxCtrlStaGet,	eLowBeamRly, 0, 0, 0, 50U,	1000U, 0,},
#endif
};


/*!
************************************************************************************************************************
* @par 接口原型
	   static BOOL Diag_LoadDiagCheck(DiagDtcNameType_t enDtcName,INT8U DiagNum)
* @par 描述
       负载诊断确认
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-10-23
************************************************************************************************************************
*/

static BOOL Diag_LoadDiagCheck(DiagDtcNameType_t enDtcName, INT8U DiagNum)
{
	strDiagBtsHDriverIsCheckTbl_t *pDiagBtsHDriverIsCheck = NULL;
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;
	GpioSignalName_t GpioName = EN_GPIO_ALL_NUM;
	INT8U u8BtsHighDrvChip = 0;
	INT8U u8BtsHighDrvChipChl = 0;
	INT8U u8FaultSort = 0;
	INT16U u16LoadDownImA = 0;
	INT16U u16LoadUpImA = 0;
	INT32U u16DigTimeout = 0;
	INT16U u16DriverISTemp = 0;
	INT8U i = 0;
	static INT8U DigLoadCnt[EN_DIAG_LOAD_MAX][4] = {0};


	for(i = 0; i < (INT16U)IO_DiagBtsHDriverIsCheckTbl_NUM ; i++)
	{
		if(DiagBtsHDriverIsCheckTbl[i].DtcName ==  enDtcName)
		{
			pDiagBtsHDriverIsCheck = &DiagBtsHDriverIsCheckTbl[i];
			break;
		}
	}

	if(pDiagBtsHDriverIsCheck != NULL)
	{
		u8BtsHighDrvChip = pDiagBtsHDriverIsCheck->u8BtsHighDrvChip;
		u8BtsHighDrvChipChl = pDiagBtsHDriverIsCheck->u8BtsHighDrvChipChl;

		u8FaultSort = pDiagBtsHDriverIsCheck->u8FaultSort;
		u16LoadDownImA = pDiagBtsHDriverIsCheck->u16LoadDownImA;
		u16LoadUpImA = pDiagBtsHDriverIsCheck->u16LoadUpImA;
		u16DigTimeout = pDiagResult[DiagNum].PeriodTs;
		u16DigTimeout = pDiagResult[DiagNum].DecTotalTs / u16DigTimeout; 	/****检测总时长/检测周期*****/

		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);

		if((u8FaultSort == D_DiagBtsHDriver_Fault_OverLoad) && (u16LoadUpImA != 0U) ) /*对电源短路*/
		{
			if(u16DriverISTemp > u16LoadUpImA)
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OverLoad]++;
				if(DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OverLoad] >= u16DigTimeout)
				{
					pDiagResult[DiagNum].LmpDigResult = TRUE;
				}
			}
			else
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OverLoad] = 0;
				pDiagResult[DiagNum].LmpDigResult = FALSE;
			}
		}

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OpenLoad) && (u16LoadDownImA != 0U) )  /*对地短路*/
		{
			if(u16DriverISTemp < u16LoadDownImA)
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OpenLoad]++;
				if(DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OpenLoad] >= u16DigTimeout)
				{
					pDiagResult[DiagNum].LmpDigResult = TRUE;
				}
			}
			else
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_OpenLoad] = 0;
				pDiagResult[DiagNum].LmpDigResult = FALSE;
			}
		}


		if(u8FaultSort == D_DiagBtsHDriver_Fault_LackLoad)
		{
			if(u16DriverISTemp >= u16LoadDownImA)
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_LackLoad]++;
				if(DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_LackLoad] >= u16DigTimeout)
				{
					pDiagResult[DiagNum].LmpDigResult = TRUE;
				}
			}
			else
			{
				DigLoadCnt[DiagNum][D_DiagBtsHDriver_Fault_LackLoad] = 0;
				pDiagResult[DiagNum].LmpDigResult = FALSE;
			}
		}
	}
	return ;
}
#endif

/*!
************************************************************************************************************************
* @par 接口原型
	   void Diag_LoadDiagHandle(void)
* @par 描述
       负载诊断
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-10-23
************************************************************************************************************************
*/
void Diag_LoadDiagHandle(void)
{
#if 0

	DiagLoadDat_t *pDiagLoadDat = &DiagLoadCtrl;
	INT8U index = 0;
	static INT8U DigLoadRlyCnt[2] = {0};
	INT32U u16DigRlyTimeout = 0;
	static INT32U DiagPeriodTs = 0;


	if(CPU_TimerDiffTs(DiagPeriodTs) >= D_DIAG_LOAD_PERIOD_TIME)
	{
		DiagPeriodTs = D_HAL_GET_CUR_MS_TS();

		for(index = EN_DIAG_LOAD_REARFOGLP; index < EN_DIAG_LOAD_HIGHBEAMRLY; index++)
		{
			/*各种类型灯光工作时启动检测试*/
			if(EN_GPIO_LEV_HIGH == pDiagLoadDat[index].GpioStatus(pDiagLoadDat[index].GpioSignal))
			{
				Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOverCurrentOrSCG, index);
				Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOpenLoadOrSCV, index);
				//Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOneMainOpenLoad,index);
			}
		}

		for(index = EN_DIAG_LOAD_HIGHBEAMRLY; index < EN_DIAG_LOAD_MAX; index++)
		{
			/*远光灯或者近光灯继电器工作时启动检测试*/

			if(TRUE == pDiagLoadDat[index].RlySta(pDiagLoadDat[index].DriveType))
			{
				u16DigRlyTimeout = pDiagLoadDat[index].PeriodTs;
				u16DigRlyTimeout = pDiagLoadDat[index].DecTotalTs / u16DigRlyTimeout;

				/*********************远光灯或者近光灯开路检测**************************************/
				if(Ecual_Tle75xxxGetDiagnosisStatus(pDiagLoadDat[index].DriveType) == eChlDiagSta_OverLoad)
				{
					DigLoadRlyCnt[index]++;
					if(DigLoadRlyCnt[index] >= u16DigRlyTimeout)
					{
						pDiagLoadDat[index].LmpDigResult = TRUE;
						DigLoadRlyCnt[index] = u16DigRlyTimeout;
					}
				}
				else
				{
					if(pDiagLoadDat[index].LmpDigResult == TRUE)
					{
						if(DigLoadRlyCnt[index] > 0 )
							DigLoadRlyCnt[index]--;
						if(DigLoadRlyCnt[index] == 0)
						{
							pDiagLoadDat[index].LmpDigResult = FALSE;
						}
					}
					else
					{
						DigLoadRlyCnt[index] = 0;
						pDiagLoadDat[index].LmpDigResult = FALSE;
					}
				}

				/*********************远光灯或者近光灯开路检测**************************************/
				if(Ecual_Tle75xxxGetDiagnosisStatus(pDiagLoadDat[index].DriveType) == eChlDiagSta_OpenLoad)
				{
					DigLoadRlyCnt[index]++;
					if(DigLoadRlyCnt[index] >= u16DigRlyTimeout)
					{
						pDiagLoadDat[index].LmpDigResult = TRUE;
						DigLoadRlyCnt[index] = u16DigRlyTimeout;
					}
				}
				else
				{
					if(pDiagLoadDat[index].LmpDigResult == TRUE)
					{
						if(DigLoadRlyCnt[index] > 0 )
							DigLoadRlyCnt[index]--;
						if(DigLoadRlyCnt[index] == 0)
						{
							pDiagLoadDat[index].LmpDigResult = FALSE;
						}
					}
					else
					{
						DigLoadRlyCnt[index] = 0;
						pDiagLoadDat[index].LmpDigResult = FALSE;
					}
				}
			}
		}
	}
	
#endif

}

INT8U decimal_bcd_code(INT8U decimal)
{
	INT8U sum = 0;  //sum返回的BCD码
 	INT8U i = 0;
	for ( i = 0; decimal > 0; i++)
	{
		sum |= ((decimal % 10 ) << ( 4*i));
 
		decimal /= 10;
	}
 
	return sum;
}

/*!
************************************************************************************************************************
* @par 接口原型
	   void GetSnapData(INT8U *msgBuf,INT8U length)
* @par 描述
       获取快照数据
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date 2021-10-23
************************************************************************************************************************
*/
static void GetSnapData(INT8U *msgBuf, INT8U length)
{
	INT8U index = 0;
	INT8U cDataBuf[3] = {0x1Fu};
	INT16U cBoardvolt = 0;
	INT16U cEngSpeed = 0;
	INT16U cVehSpd = 0;
	/*点火开关获取*/
	BOOL bACCSw = 0;
	BOOL bIGNSw = 0;
	BOOL bStartSw = 0;//Ecual_GetDigitalSwStatus(EN_StartSw);
	INT8U bMode = 0;//Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);

	
	/*车速填入开始*/
	cVehSpd = CanRx_0x284_ABS_VehicleSpeed();
	cDataBuf[0] = (INT8U)(cVehSpd >> 8u);
	cDataBuf[1] = (INT8U)(cVehSpd) & 0xFFu;
	msgBuf[index++] = cDataBuf[0];
	msgBuf[index++] = cDataBuf[1];
	/*车速填入结束*/

	
	/*时间填入开始*/
//	msgBuf[index++] = decimal_bcd_code( CanRx_0x527_EHC6_N_Year());//CanRx_0x581_IC_Year() - 3;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Month());//CanRx_0x581_IC_Month() + 1;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Day());//CanRx_0x581_IC_Date() + 1;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Hour());//CanRx_0x581_IC_Hour();
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Minute());//CanRx_0x581_IC_Minute();
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Second());//CanRx_0x581_IC_Second();
	/*时间填入结束*/

	/*控制器电压填入开始*/
	cBoardvolt = Srvl_Get_SupplyVoltage();
	cDataBuf[0] = (INT8U)(cBoardvolt >> 8u);
	cDataBuf[1] = (INT8U)(cBoardvolt);
	msgBuf[index++] = cDataBuf[0];
	msgBuf[index++] = cDataBuf[1];
	/*控制器电压填入结束*/

	



	msgBuf[index++] = 0;// 后续会处理故障码次数

}


#if 0
#if 1

/*位置灯诊断信号*/
BOOL Diag_BCM_PosLmpResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_POSLP1].LmpDigResult;
	return DiagResult;
}

/*前雾灯诊断信号*/

BOOL DiagLLmpResult = FALSE;
BOOL DiagRLmpResult = FALSE;


BOOL Diag_BCM_FrntFogLmpResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;
	BOOL DiagResult = FALSE;

	DiagLLmpResult = pDiagResult[EN_DIAG_LOAD_FRONTLEFTFOGLP].LmpDigResult;
	DiagRLmpResult = pDiagResult[EN_DIAG_LOAD_FRONTRIGHTFOGLP].LmpDigResult;

	if((DiagLLmpResult == TRUE) || (DiagRLmpResult == TRUE))
	{
		DiagResult = TRUE;
	}

	return DiagResult;
}

/*后雾灯诊断信号*/
BOOL Diag_BCM_RearFogLmpResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;
	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_REARFOGLP].LmpDigResult;
	return DiagResult;
}

/*转向灯诊断信号*/
BOOL Diag_BCM_TurnIndicatorResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = FALSE;
	BOOL DiagRLmpResult = FALSE;
	BOOL DiagLLmpResult = FALSE;

	DiagRLmpResult = pDiagResult[EN_DIAG_LOAD_RIGHTDIRLP].LmpDigResult;
	DiagLLmpResult = pDiagResult[EN_DIAG_LOAD_LEFTDIRLP].LmpDigResult;

	if((DiagRLmpResult == TRUE) || (DiagLLmpResult == TRUE))
	{
		DiagResult = TRUE;
	}

	return DiagResult;
}

/*倒车灯诊断信号*/
BOOL Diag_BCM_ReversinglightResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_REVERSELP].LmpDigResult;
	return DiagResult;
}

/*制动灯诊断信号*/
BOOL Diag_BCM_BrakelightResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_BRAKELP].LmpDigResult;
	return DiagResult;
}


BOOL DiagResult11 = FALSE;

/*日间行车灯诊断信号*/
BOOL Diag_BCM_DayRunningLampResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	DiagResult11 = pDiagResult[EN_DIAG_LOAD_DAYRUNLP].LmpDigResult;

	return DiagResult11;
}
#endif
#endif

