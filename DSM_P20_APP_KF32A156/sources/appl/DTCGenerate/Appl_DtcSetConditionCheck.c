#include "Appl_DtcSetConditionCheck.h"
#include "uds_pub.h"
#include "DiagDTCGenerate.h"
#include "Appl_PowerMangeModel.h"
#include "Ecual_Can.h"
#include "App_ModelHeader.h"
#include "Rte_VfbInterface.h"
#include "MidRelay.h"
#include "CpuPeripheralInit.h"

#define D_JoinCom_HoldOnTime		(15UL*1000UL ) /*can �ڵ�������ʱ�� 15000ms*/
#define D_LostCom_HoldOnTime		(15UL*1000UL ) /*can �ڵ㶪ʧ����ʱ�� 15000ms */
#define D_Busoff_CleanTime		    (8UL*100UL) /*can busoff ����ʱ�� 800ms������8��ʱ��ԼΪ500~600ms*/
#define D_OutPutValid_HoldOnTime	(50UL) /* �������ʱ�� ms*/

#define D_SWAdhesion_HoldOnTime   	(120UL*1000UL) /*����ճ��ʱ�� 120s*/
#define D_RelayAdhesion_HoldOnTime   	(2UL*1000UL) /*�̵���ճ��ʱ�� 2s*/
#define D_HALLERROR_HoldOnTime 		(2UL*1000UL) /*������ʧʱ�� 2s */

static INT8U u8LeftTurnLightErrorFlag = 0x0u;
static INT8U u8RightTurnLightErrorFlag = 0x0u;
static INT8U s_MonitorEnableCriteria[En_DtcType_MaxNum] = {0x00}; //DTC���ǰ������

static BOOL s_resetFlg = FALSE;

static ST_DTCCondInfo  stcondinfo_DTC = //DTC ʹ��������������ȡ�Ķ���
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

/*! @brief ����²�������ָʾ */
static BOOL Diag_NewPwrCycle = FALSE;
/*! @brief �»�������ָʾ */
static BOOL Diag_NewWakeCycle = FALSE;

/*! @brief ͨѶ����Ϲ�������ָʾ */
static BOOL Diag_CommDtcWorkInd = FALSE;
/*! @brief ͨѶ����ϳ�ʱ��������ָʾ */
static BOOL Diag_CommMsgTimeoutInd = FALSE;
/*! @brief ͨѶ������е�ѹ��Χ */
/*
static const INT16U DiagCommVoltRange[(INT8U)EN_DIAG_COMM_ALL_VOLT_STA][2] = {
    {0, 85UL},  // ��ѹ�� 0.1v
    {80UL, 170UL}, // ��ѹ���� 0.1v
    {165UL, 500UL} // ��ѹ�� 0.1v
};*/

strDiagBtsHDriverIsCheckTbl_t DiagBtsHDriverIsCheckTbl[] =
{


	/* ����Ƶƹ�����Եض�· */
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


	/***************************�����***********************************/
	/* ����Ƶƹ�����Եض�· */
	{
		En_Dtc_RearFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* ����ƿ�·��Ե�Դ��· */
	{
		En_Dtc_RearFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* ������� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************λ�õ�1***********************************/
	/* λ�õ�1������Եض�· */
	{
		En_Dtc_SideBeamLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* λ�õ�1��·��Ե�Դ��· */
	{
		En_Dtc_SideBeamLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		10,
		0,
	},


	/* λ�õ�1�� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_RearFogLpPosLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},

	/***************************��ת���***********************************/
	/* ��ת��ƹ�����Եض�· */
	{
		En_Dtc_LeftDIFlasher_OvercurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		8500, /*9.2A*/
	},

	/* ��ת��ƿ�·��Ե�Դ��· */
	{
		En_Dtc_LeftDIFlasher_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* ��ת���һ���� */
	{
		En_Dtc_LeftDIFlasher_OneMainLampOpenLoad,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		100,
		4000,
	},


	/***************************��ת���***********************************/
	/* ��ת��ƹ�����Եض�· */
	{
		En_Dtc_RightDIFlasher_OvercurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		8500, /*9.2A*/
	},

	/* ��ת��ƿ�·��Ե�Դ��· */
	{
		En_Dtc_RightDIFlasher_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* ��ת���һ���� */
	{
		En_Dtc_RightDIFlasher_OneMainLampOpenLoad,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightDirLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		100,
		4000,
	},

	/***************************��ǰ���***********************************/
	/*��������ֵ:0x3A8  ,936*/
	/* ��ǰ��Ƶ�Դ��· */
	{
		En_Dtc_LhFrFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400,
	},

	/* ��ǰ��ƶԵض�· */
	{
		En_Dtc_LhFrFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* ��ǰ����� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************��ǰ���***********************************/
	/* ��ǰ��ƹ�����Եض�· */
	{
		En_Dtc_RhFrFogLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400,
	},

	/* ��ǰ��ƿ�·��Ե�Դ��· */
	{
		En_Dtc_RhFrFogLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* ��ǰ����� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightFogLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************��ǵ�***********************************/
	/* ��ǵƹ�����Եض�· */
	{
		En_Dtc_Leftcornerlamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*5000mA*/
	},

	/* ��ǵƿ�·��Ե�Դ��· */
	{
		En_Dtc_Leftcornerlamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},


	/*��ǵ��� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************�ҽǵ�***********************************/
	/* �ҽǵƹ�����Եض�· */
	{
		En_Dtc_Rightcornerlamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*4.4A*/
	},

	/* �ҽǵƿ�·��Ե�Դ��· */
	{
		En_Dtc_Rightcornerlamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* �ҽǵ��� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_LeftRightCornerLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************�ռ��г���***********************************/
	/* �ռ��г��ƹ�����Եض�· */
	{
		En_Dtc_DayDriveLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		4400, /*4.4A*/
	},

	/* �ռ��г��ƿ�·��Ե�Դ��· */
	{
		En_Dtc_DayDriveLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* �ռ��г����� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_DayRunLpPosLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************������***********************************/
	/* �����ƹ�����Եض�· */
	{
		En_Dtc_ReverseLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* �����ƿ�·��Ե�Դ��· */
	{
		En_Dtc_ReverseLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},


	/* �ҽǵ��� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN0,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},


	/***************************ɲ����***********************************/
	/* ɲ���ƹ�����Եض�· */
	{
		En_Dtc_LBrakeLamp_OverCurrentOrSCG,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OverLoad,
		0,
		9200, /*9.2A*/
	},

	/* ɲ���ƿ�·��Ե�Դ��· */
	{
		En_Dtc_LBrakeLamp_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_OpenLoad,
		100,
		0,
	},

	/* �ҽǵ��� */
	{
		En_Dtc_ReserveNC11_OUT_OpenLoadOrSCV,
		D_DTCTest,

		D_BtsHighDriverChip_ReverseLpBrakeLp,
		D_AdcBtsChlIs_IN1,

		D_DiagBtsHDriver_Fault_LackLoad,
		0,
		0,
	},

	/***************************�Ҷ���***********************************/
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
* @par �ӿ�ԭ��
       static void Diag_IsNewPwrCycle(void)
* @par ����
       �Ƿ����µĵ�Դ��������
* @param[in] void
* @param[out] Diag_NewPwrCycle���µ�Դ����ָʾ
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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
		if((PksPowerModePrev == enIgnSts_eOn) && (PksPowerMode == enIgnSts_eOff))// ON -> OFF Ϊһ���������
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
* @par �ӿ�ԭ��
       static void Diag_IsNewWakeCycle(void)
* @par ����
       �ж��Ƿ�Ϊ�µĻ�������
* @param[in] void
* @param[out] Diag_NewWakeCycle���»�������ָʾ
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       static void Diag_CommVoltCtrl(void)
* @par ����
       ͨѶ��Ϲ�����ѹ��Χ����
* @param[in] DiagCommVoltRange����ѹ���Ʒ�Χ��
* @param[out] Diag_CommDtcWorkInd��ͨѶ����Ϲ���ָʾ
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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
 * @description:	���ù��ϱ�־
 *
 * @input parameters:     ����
 *
 * @output parameters:     void
 *
 * @return:         
 *
 * @note:           ��
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
 * @description:	��ȡ���ϱ�־
 *
 * @input parameters:     ����
 *
 * @output parameters:     ���ϱ�־
 *
 * @return:         
 *
 * @note:           ��
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
* @par �ӿ�ԭ��
       static void Diag_CommLogicCtrl(void)
* @par ����
       ͨѶ����ϵ�ѹ��Χ�ͳ�ʼ��ʱ�����
* @param[in] Diag_NewWakeCycle���»�������ָʾ
* @param[out] Diag_CommDtcWorkInd��ͨѶ��Ϲ���ָʾ
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-11-1
************************************************************************************************************************
*/

static void Diag_CommLogicCtrl(void)
{
}

/***********************************************************************************************
* @function name:   Diag_getMonitorEnableCriteria(INT8U t_index)
*
* @description:      ��ȡDTCǰ�����������־λ
*
* @input parameters:	 t_index��DTC�±�
*
* @output parameters:	  void
*
* @return:		   INT8U ��־λ   			TRUE:��������  			FALSE:����������
*
* @note:		   ��
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
* @description:    ����DTCǰ�����������־λ
*
* @input parameters:	 t_start����ʼ�����±�  t_end�������±꣨������     				flag����־
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   ��
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
* @description:    ���ø�λ��־λ
*
* @input parameters:  flag����λ��־
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   ��
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
* @description:    DTCǰ���������
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
	static INT32U u32CrankTs = 0;	//��Crank����ʱ
	static INT32U u32ONTs = 0;		//ON����ʱ
	static INT32U u32ResetTs = 0; 	//MCU��λ��ʱ
	static INT32U u32VotTs = 0;		//��ѹ�쳣��ʱ

	INT8U sIGNStsCurr =0;// enIgnSts_eOff;
	PowerModeStatus_t sPowerModeCurr = EN_PowerNormal_Sts;//enIgnSts_eOff;

	BOOL condition_reset = FALSE; // MCU��λ5s
	BOOL condition_crank = FALSE; // ��Դ����crank��ת����crank״̬5s
	BOOL condition_ON = FALSE; // ��Դ��ON״̬5s
	BOOL condition_vot = FALSE; // ��ѹ����������9~16V�����ѹ�쳣�ָ�5S

	BOOL Diag280301Flag = FALSE; 	//���28�����ֹ����Ӧ�ñ�������
	BOOL Diag280302Flag = FALSE; 	//���28�����ֹ����Ӧ�ñ�������
	BOOL BUSOffFlag = FALSE;	//busoff����
	BOOL LimphomeFlag = FALSE;	//Limphome����

	BOOL DrHeatFlag = FALSE;	//���ݼ�������
	BOOL PaHeatFlag = FALSE;	//���ݼ�������
	BOOL SteerHeatFlag = FALSE;	//�����̼�������
	BOOL DrVentFlag = FALSE;	//����ͨ������
	BOOL PaVentFlag = FALSE;	//����ͨ������

	BOOL DrHeightCtrl = FALSE;				//���ݸ߶ȿ���	
	BOOL DrLengthCtrl = FALSE;				//�����������	
	BOOL DrBackrestCtrl = FALSE;			//���ݿ�������	
	BOOL DrFrontAngleCtrl = FALSE;			//����ǰ���Ƕȿ���	
	BOOL PaLengthCtrl = FALSE;				//�����������	
	BOOL PaBackrestCtrl = FALSE;			//���ݿ�������	

	INT8U   DrAdjustCfg =FALSE;    
	INT8U   PaAdjustCfg =FALSE;      
	INT8U   DrHeatVentCfg =FALSE;    
	INT8U   PaHeatVentCfg =FALSE;  
	INT8U   seatMassageCfg =FALSE;  
	INT8U   SteerHeatCfg = FALSE;

	INT8U DrMemoryCfg = FALSE;	//����ӭ������
	INT8U PaMemoryCfg = FALSE;	//����ӭ������

    INT8U   DrHeatCfg =FALSE;    /* ���ݼ��������� */
    INT8U   PaHeatCfg =FALSE;    /* ���ݼ��������� */
    INT8U   DrVentCfg =FALSE;    /* ����ͨ�������� */
    INT8U   PaVentCfg =FALSE;    /* ����ͨ�������� */

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

/* ��������Чʱ�������Ӧ��DTC  				start */	
	if(DrAdjustCfg == FALSE)
	{
		Diag_ClearDtcById(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion,8);
		Diag_ClearDtcById(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued,4);
		Diag_ClearDtcById(En_Dtc_DriverSeatHeightRegulatingMotorHallFault,4);
	}

    /* 6����� */
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
/* ��������Чʱ�������Ӧ��DTC  				end */	
	
	//��Ͽ���DTC
	if (cDescControlDTCSetting != DESC_CONTROL_DTC_SETTING_ON)
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, (En_DtcType_MaxNum - 1), FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_CanBusOff, (En_DtcType_MaxNum - 1)); //���ü�ʱ��
		return;
	}
	
	//���28���ƽ���app����
	if(ECUAL_CAN_IS_APP_RX_ENABLE() == TRUE)
	{
		Diag280301Flag = TRUE;
	}
	//���28���ƽ������籨��
	if(OsekNm_GetOsekInOnStatus() == TRUE)
	{
		Diag280302Flag = TRUE;
	}
	//��busoff
	if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_CanBusOff))
	{
		BUSOffFlag = TRUE;
	}

	//��Limphome
	if(FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DsmNodeLimphome))
	{
		LimphomeFlag = TRUE;
	}

	if(CPU_TimerDiffTs(u32ResetTs) > D_DTC_RESET_TIME)//MCU��λ����ʱ5��
	{
		condition_reset = TRUE;
	}
	
	sIGNStsCurr = Rte_GetVfb_PowerMode(); //��ǰ��Դ��λ
	/*��Դ��λ����crank��ת����crank״̬5s֮�� */
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
	/*��Դ��λON��״̬5s֮�� */
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
	//�������ڼ���
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_DrHeat())
	{
		DrHeatFlag = TRUE;
	}
	//�������ڼ���
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_PaHeat())
	{
		PaHeatFlag = TRUE;
	}
	//���������ڼ���
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_ThirdHeat())
	{
		SteerHeatFlag = TRUE;
	}
	//��������ͨ��
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_DrVent())
	{
		DrVentFlag = TRUE;
	}
	//��������ͨ��
	if(enHeatLvlSts_EN_HEAT_LVL_OFF != Rte_GetVfb_PaVent())
	{
		PaVentFlag = TRUE;
	}
	
	//���ݸ߶ȿ�����Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_DrHeightMotorCmd())
	{
		DrHeightCtrl = TRUE;
	}
	//�������������Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_DrLengthMotorCmd())
	{
		DrLengthCtrl = TRUE;
	}
	//���ݿ���������Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_DrBackMotorCmd())
	{
		DrBackrestCtrl = TRUE;
	}
	//����ǰ���Ƕȿ�����Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_DrFrontMotorCmd())
	{
		DrFrontAngleCtrl = TRUE;
	}
	//�������������Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_PaLengthMotorCmd())
	{
		PaLengthCtrl = TRUE;
	}
	//���ݿ���������Ч
	if(EN_MOTOR_DEF != Rte_GetVfb_PaBackMotorCmd())
	{
		PaBackrestCtrl = TRUE;
	}
	
	sPowerModeCurr = Rte_GetVfb_VoltMode();
	/*��ѹ���������ѹ�쳣�ָ�5S֮�ڣ������DTC*/
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


	/*��ѹDTCǰ���������*/
	if((condition_reset == TRUE) && (condition_crank == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SupplyVoltageTooLow, En_Dtc_SupplyVoltageTooHigh); //���ü�ʱ��
	}

	/*bus off DTCǰ���������*/
	if((condition_reset == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, En_Dtc_CanBusOff, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_CanBusOff, En_Dtc_CanBusOff, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_CanBusOff, En_Dtc_CanBusOff); //���ü�ʱ��
	}

	/*Limphone DTCǰ���������*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (Diag280302Flag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DsmNodeLimphome, En_Dtc_DsmNodeLimphome); //���ü�ʱ��
	}
	
	
	/*CAN�ڵ㶪ʧDTCǰ���������
		1.MCU��λ 5S֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5s֮��
		4.û���յ�28 03 disable request
		5.��busoff��limphome���� limphome�����ڽӿ��ڲ����
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) \
		&& (Diag280301Flag == TRUE) && (BUSOffFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_LostCommunicationWithBcm, En_Dtc_LostCommunicationWithBcm); //���ü�ʱ��
	}
	/*CAN�ڵ㶪ʧDTCǰ���������
		1.MCU��λ 5S֮��
		2����Դ״̬�л���ON��5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5s֮��
		4.û���յ�28 03 disable request
		5.��busoff��limphome���� limphome�����ڽӿ��ڲ����
	*/
	if((condition_reset == TRUE) && (condition_ON == TRUE) && (condition_vot == TRUE) \
		&& (Diag280301Flag == TRUE) && (BUSOffFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_LostCommunicationWithGw, En_Dtc_LostCommunicationWithGw); //���ü�ʱ��
	}

	/*	���ݼ������DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�����������ڼ���
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) \
		&& (DrHeatFlag == TRUE) && (DrHeatVentCfg == TRUE) && (DrHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, En_Dtc_DriverSeatHeatingOutputDisconnected); //���ü�ʱ��
	}

	/*	���ݼ���NTC DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (DrHeatVentCfg == TRUE) && (DrHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, En_Dtc_DriverSeatHeatingNtcInputIsInvalid); //���ü�ʱ��
	}
	

	/*	���ݼ������DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�����������ڼ���
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) 
    && (PaHeatFlag == TRUE) && (PaHeatVentCfg == TRUE) && (PaHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, En_Dtc_PassengerSeatHeatingOutputDisconnected); //���ü�ʱ��
	}

	/*	���ݼ���NTC DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (PaHeatVentCfg == TRUE) && (PaHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, En_Dtc_PassengerSeatHeatingNtcInputIsInvalid); //���ü�ʱ��
	}
	
	/*	�����̼������DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�������������ڼ���
	*/
	if((condition_reset == TRUE)  && (condition_vot == TRUE) && (SteerHeatFlag == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, En_Dtc_SteeringWheelHeatingOutputDisconnected); //���ü�ʱ��
	}
	/*	�����̼���NTC DTC���
		1.MCU��λ 5S֮��
		//2.��Դ����crank��ת����crank״̬5s֮�� 
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)  && (SteerHeatCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, En_Dtc_SteeringWheelHeatingNTCInputIsInvalid); //���ü�ʱ��
	}
	/*����ͨ��DTCǰ���������
		1����DSM�ϵ��Ƭ���ϵ�����ʹMCU��λ��5s֮��
		//2����crank���г�����״̬5s�ڲ����
		3����������������ѹ5s֮��
		4��������������ͨ��
	*/
	if((condition_reset == TRUE) && (condition_vot == TRUE)
     && (DrHeatVentCfg == TRUE) && (DrVentCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply); //���ü�ʱ��
	}

	/*����ͨ��DTCǰ���������
	1����DSM�ϵ��Ƭ���ϵ�����ʹMCU��λ��5s֮��
	//2����crank���г�����״̬5s�ڲ����
	3����������������ѹ5s֮��
	4��������������ͨ��
	*/
	/* ���������ͨ�磬��ֹ�������ȼ�ԭ����ϲ�������ģ�͹ر�cmd�� δ�����¼dtc*/
	if((condition_reset == TRUE) && (condition_vot == TRUE) 
     && (PaHeatVentCfg == TRUE) && (PaVentCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply); //���ü�ʱ��
	}

	/*���ݸ߶ȵ��ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�������θ߶ȵ������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrHeightCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeightRegulatingMotorHallFault, En_Dtc_DriverSeatHeightRegulatingMotorHallFault); //���ü�ʱ��
	}
	/*����������ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.������������������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrLengthCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault); //���ü�ʱ��
	}
	/*���ݿ������ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�������ο����������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrBackrestCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg  != 0))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, En_Dtc_DriverSeatBackrestRegulatingMotorHallFault); //���ü�ʱ��
	}
	/*����ǰ���Ƕȵ��ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.��������ǰ���Ƕȵ������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (DrFrontAngleCtrl == TRUE)\
		&& (DrMemoryCfg == TRUE) && (DrAdjustCfg == 2))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault); //���ü�ʱ��
	}

	/*����������ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.������������������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaLengthCtrl == TRUE)\
		&& (PaMemoryCfg == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault); //���ü�ʱ��
	}
	/*���ݿ������ڵ����������DTCǰ���������
		1.MCU��λ 5S֮��
		2.��Դ����crank��ת����crank״̬5s֮��
		3.��ѹ����������ѹģʽ���ѹ�쳣�ָ�5S֮��
		4.�������ο����������������Ч
	*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaBackrestCtrl == TRUE)\
		&& (PaMemoryCfg == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, TRUE);
		
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault); //���ü�ʱ��
	}

	/*���ݼ̵���ճ��DTCǰ���������*/
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
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued); //���ü�ʱ��
	}
	
	/*���ݼ̵���ճ��DTCǰ���������*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (PaAdjustCfg == 1))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued); //���ü�ʱ��
	}
	
	/* ��Ħģ�鼰lin���ݴ���DTC
	1����DSM�ϵ��Ƭ���ϵ�����ʹMCU��λ����DSM������һ֡alive����5s֮��
	2����crank���г�����״̬5s�ڲ����
	3����������������ѹ5s֮��
	4����Ħ���� == 0x01:true*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (seatMassageCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow, En_Dtc_LINError,TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow, En_Dtc_LINError,FALSE);
	}

	
	/*����Ӳ�߿���ճ��*/
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
			Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //���ü�ʱ��
		}
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //���ü�ʱ��
	}

	
	/*����Ӳ�߿���ճ��*/
	if((condition_reset == TRUE) && (condition_crank == TRUE) && (condition_vot == TRUE) && (PaAdjustCfg == TRUE))
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, TRUE);
	}
	else
	{
		Diag_setMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		Diag_Initu32DiagDtcTestFailTs(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion); //���ü�ʱ��
	}

}

/***********************************************************************************************
* @function name:  Diag_Initu32DiagDtcTestFailTs(INT8U t_start, INT8U t_end )
*
* @description:    ����DTC����ʱ��
*
* @input parameters:	 t_start����ʼ�����±�  t_end�������±꣨������
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   ��
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
* @description:    DTC����ӿ�
*
* @input parameters:	void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   ��
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
		//ɾ��ǰ������������ϻ������ﵽ�޷����DTC������
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
* @par �ӿ�ԭ��
       void Diag_DtcRecordHandle(void)
* @par ����
       ���й���DTC����
* @param[in] cDescControlDTCSetting��DTC���ùر�
* @param[out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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

	Diag_CanNodeComLostOpt(); /* can�ڵ��Ķ�ʧ�ж� */
	Diag_LinNodeFaultCheck();
	
	DiagDtcHandleFunc(); //��¼TDC
	
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void Diag_ClearAllDtc(void)
* @par ����
       ɾ������DTC
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       void Diag_ClearDtcById(DiagDtcNameType_t enDtcIndex, INT8U num)
* @par ����
       ɾ����ӦDTC
* @param[in]	enDtcIndex:��ʼɾ����DTC��num��Ҫɾ����DTC��������enDtcIndex��ʼ������
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       INT16U Diag_MatchDtcMaskNum(INT8U mask)
* @par ����
       ��ȡƥ��DTC Mask�Ĺ���������
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       BOOL Diag_MatchDtcMaskCode(INT8U mask, INT8U dtcIndex, INT8U u8DtcCode[], INT8U dtcLen)
* @par ����
       ƥ��DTC Mask��һ�������DTC Code
* @param[in] INT8U mask��DTC����
* @param[in] DiagDtcName_t dtcIndex��DTC����
* @param[in] INT8U dtcLen��DTC����
* @param[out] INT8U dtc[]��DTC
* @returns BOOL���Ƿ�ƥ��
* @pre ��
* @note ��
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       INT8U Diag_GetDtcMask(DiagDtcName_t dtcIndex)
* @par ����

* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       void Diag_GetDtcCode(INT8U dtcIndex, INT8U * u8DtcCode)
* @par ����
       ��ȡDTC
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       INT8U Diag_FindDtcMask(INT8U dtc[], INT8U dtcLen)
* @par ����
       ����DTC���Ҷ�Ӧ���õ�����
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       BOOL Diag_FindVehSnapData(DiagDtcName_t dtcIndex, DiagSnapVehInfo_t *pSnapDat)
* @par ����
       �����������ҳ������ݿ���
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Lews Hammond(������)
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
* @par �ӿ�ԭ��
       BOOL Diag_ReadVehSnapData(INT8U u8DtcCode[3], INT8U recodeNumber, INT8U *pSnapDat, INT16U size, INT16U *length)
* @par ����
       ����������ȡ��������
* @param[in]
* @param[out]
* @returns
* @pre
* @note ע�⻺�泤����>=�������ݳ���
* @author Lews Hammond(������)
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

	/**< ͨ��DTC Code����DTC��� */
	dtcCode = u8DtcCode[0] << 16 | u8DtcCode[1] << 8 | u8DtcCode[2];
	dtcIdx = Diag_FindDtcDataIdx(dtcCode);
	if (dtcIdx == 0xFF)
	{
		return bRet;
	}

	/**< ͨ��DTC IDX����Snap��� */
	idx = Diag_FindVehSnapDataIdx(dtcIdx);
	if (idx == 0xFF)
	{
		return bRet;
	}

	/* �������δ������ȡEEPROM���� */
	if (Diag_SnapQueue[idx].RAM_UpdataFlag == FALSE)
	{
		Srvl_GetDTCExternDataSnapInfo(idx, Diag_SnapQueue[idx].Diag_SnapshotDat);
		Diag_SnapQueue[idx].RAM_UpdataFlag = TRUE;
	}

	/* ���������� */
	pSnapDat[index++] = u8DtcCode[0];
	pSnapDat[index++] = u8DtcCode[1];
	pSnapDat[index++] = u8DtcCode[2];
	pSnapDat[index++] = Diag_GetDtcMask(dtcIdx) & DTCStatusAvailabilityMask;	/* ��λ�� */
	if (recodeNumber == 0xFF || recodeNumber == Diag_SnapConfigList.Snap_RecordNum)
	{
		INT8U i = 0;

		/* ������ȷ��λ��Ϊ1ʱ�������ؿ������� */
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
		/* ��recordNumber��֧��ʱ������Flase */
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
		/**< ͨ��DTC Code����DTC��� */
		dtcIdx = Diag_FindDtcDataIdx(Diag_DtcConfigList[i].Diag_DtcCode);
		if (dtcIdx == 0xFF)
		{
			return FALSE;
		}
		/**< ͨ��DTC IDX����Snap��� */
		idx = Diag_FindVehSnapDataIdx(dtcIdx);
		if (idx == 0xFF)
		{
			continue;
		}
		//mask = Diag_GetDtcMask(dtcIdx) & DTCStatusAvailabilityMask;	/* ��λ�� */
		/* ������ȷ��λ��Ϊ1ʱ�������ؿ������� */
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
* @par �ӿ�ԭ��
       BOOL Diag_DtcMaskSetClrOpt(DiagDtcNameType_t enDtcIndex, BOOL bDtcTestFailed)
* @par ����
       DTC mask����
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

	if (bDtcTestFailed == TRUE) /*���Ķ�ʧ*/
	{
		bDiagDtcAgingInd[enDtcIndex] = TRUE; /* ���ֹ��ϣ��ָ������ϻ� */
		if (DiagDtcMaskDat.Diag_AgingCnt != 0)
		{
			DiagDtcMaskDat.Diag_AgingCnt = 0;
			memWriteInd = TRUE;
		}

		//if (bDiagDtcInd[enDtcIndex] == FALSE)
		{
			//bDiagDtcInd[enDtcIndex] = TRUE; /* ��ϼ�¼һ�� */
#if (D_UDS_DIAG_DTC_MASK_BIT_TEST_FAILED_ENABLE == D_ENABLE)
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed != TRUE)
			{
				memWriteInd = TRUE;
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.TstFailed = TRUE;

				//Jetty 2022-04-18 ֻҪ��һ��TestFailΪTrue�����¼SnapData������TestFail������SnapData, ���ϴ�������¼��255���������ӡ�
				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC = TRUE;

				/* ���ڼ�¼���ϴ��� */
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
			//Jetty 2022-03-25 ֻҪ��һ��TestFailΪTrue�����¼SnapData������TestFail������SnapData, ���ϴ�������¼��255���������ӡ�
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC != TRUE)
			{
//				memWriteInd = TRUE;
//				DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC = TRUE;
//
//				/* ���ڼ�¼���ϴ��� */
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
			bDiagDtcAgingInd[enDtcIndex] = TRUE; /*�ϻ���¼һ��*/
			if (DiagDtcMaskDat.Diag_DtcMask.UdsDtcMaskBits.ConfirmedDTC == TRUE) /*ȷ�Ϲ��ϣ��ż��ϻ�*/
			{
				DiagDtcMaskDat.Diag_AgingCnt++; /*�������ϻ�������һ*/
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
* @par �ӿ�ԭ��
       static void Diag_CanNetworkOpt(void)
* @par ����
       DTC�������DTC����
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
	/*�������лؼ�*/
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
 * @description: ��ȡĳ��ID���ճ�ʱʱ��-��ʵ��
 *
 * @input parameters: INT32U Can_Id CAN ID
 *
 * @output parameters: void
 *
 * @return: ָ��ID��ʱʱ��
 *
 * @note: 0xFFFFU:����ֵ
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
* @par �ӿ�ԭ��
       static void Diag_CanNodeComLostOpt(void)
* @par ����
       DTC can�ڵ��Ķ�ʧ�ж�
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
	BOOL TS_ResetFlg = FALSE; //������������������ʱ���־λ
	INT8U eTimeCount = 0;//������ʼ��ʱ���¼
	INT8U bPowerMode = 0;
	INT8U i = 0;
	
	//bPowerMode = Rte_GetVfb_PowerMode();

	if(ECUAL_CAN_IS_APP_RX_ENABLE() == FALSE)
	{
		//28�����ֹRXͨ�ź󲻼��CAN��ʧ��
		TS_ResetFlg = TRUE;
		//return;
	}
#if 0
	if((bPowerMode != 2u))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		TS_ResetFlg = TRUE;
		//return; /*��Դģʽδ���ã��˴���ʱ���˳���������Ҫ�ſ�*/
	}
	else
	{
		/*ON�缰����û�дﵽ5s��ִ��ͨѶ���������λ*/
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
		/*DSMC��BDCUͨѶ��ʧ����   		 û�н��յ�0x283���ĳ���10���ڣ��ù�����*/
		if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x283) == FALSE)//���յ�����
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
		/*DSMC��GWͨѶ��ʧ����   		 û�н��յ�0x2A7���ĳ���10���ڣ��ù�����*/
		if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x2A7) == FALSE)//���յ�����
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
#if 0 // 231101  ��δʵ��
	/*busoff | limphome �����ͨѶ�������*/
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

	/*if (Diag_CommDtcWorkInd == TRUE) ��ѹ��Χ����������ecu��ʼ�����*/
	/*{
		if (Diag_CommMsgTimeoutInd == TRUE)
		{*/
			/*DSMC��BDCUͨѶ��ʧ����   		 û�н��յ�0x570���ĳ���15s���ù�����*/
			if( Ecual_GetCanMsgLostFlag(eRXINDEX_0x570) == FALSE)//���յ�����
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
			

			/*DSMC��ESPͨѶ��ʧ���� û�н��յ�0x311���ĳ���15s*/
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
			

			/*DSMC��ICCͨѶ��ʧ���� û�н��յ�0x51A���ĳ���15s */
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

			/*DSMC��TBOXͨѶ��ʧ���� û�н��յ�0x529���ĳ���15s */
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
			
			/*DSMC��DCUͨѶ��ʧ���� û�н��յ�0x564��0x566���ĳ���15s */
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
			
			/*DSMC��CSSͨѶ��ʧ���� û�н��յ�0x330���ĳ���15s */
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

			/*DSMC��EMSͨѶ��ʧ���� û�н��յ�0x280���ĳ���15s */
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
			
			/*DSMC��TCMͨѶ��ʧ���� û�н��յ�0x3E0���ĳ���15s */
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

			/*ABS/ESP ͨѶ��ʧ ��⵽0x221����һ���Ķ�ʧ�ҳ���ʱ��t >= 3S���ù�����*/
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

			/*EMS ͨѶ��ʧ ��⵽0x142����һ���Ķ�ʧ�ҳ���ʱ��t >= 3S���ù�����*/
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
			/*TCU ͨѶ��ʧ ��⵽0x123����һ���Ķ�ʧ�ҳ���ʱ��t >= 3S���ù�����*/
			if(Srv_GetMemCfgData(VEHTRANSMISSIONTYPEPRM) == 0x01u) //AMT���Ͳ������DTC
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



			/*ICM ͨѶ��ʧ ��⵽0x510����һ���Ķ�ʧ�ҳ���ʱ��t >= 3S���ù�����*/
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

			/*TBOX ͨѶ��ʧ ����⵽0x1A1��0x585��0x1A7���ľ���ʧ�ҳ���ʱ��t��3S�ù�����*/
			if(Srv_GetMemCfgData(VEHENOTAFUNCSETTINGSTATUS) == 0x01u)
			{
				if(Srv_GetMemCfgData(VEHENPEPSPRM) == 0x00u) //��PEPS�����DTC
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
				else//������PSPS֮�����������Ƿ�ʧ
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
			/*IPM ͨѶ��ʧ ��⵽0x245���Ķ�ʧ�ҳ���ʱ��t >=3S�ù�����*/
			//ADAS����״̬����Ϊ0x0��0x1��0x2�����㱨��245��246��ʧ����ʱ����ֻ��IPMͨѶ��ʧ
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

			/*DMS ͨѶ��ʧ ��⵽0x4A0���Ķ�ʧ�ҳ���ʱ��t >=3S�ù�����*/
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
* @description:    Lin ��Ħģ����ϼ��
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
	/* ��Ħģ�鼰lin���ݴ���DTC
	1����DSM�ϵ��Ƭ���ϵ�����ʹMCU��λ����DSM������һ֡alive����5s֮��
	2����crank���г�����״̬5s�ڲ����
	3����������������ѹ5s֮��*/
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_MassageModuleVoltageTooLow))
	{
		//��Ħģ��Ƿѹ
		if(2 == LinSignalGet_Massage_1_Massage_Error_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooLow, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageModuleVoltageTooLow,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooLow, FALSE);
		}

		//��Ħģ���ѹ
		if(1 == LinSignalGet_Massage_1_Massage_Error_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooHigh, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageModuleVoltageTooHigh,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageModuleVoltageTooHigh, FALSE);
		}
		
		//��Ħģ�����
		if(1 == LinSignalGet_Massage_1_Motor_TimeOutError_FB())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageMotorOvercurrent, TRUE);
			Diag_SetDTCFlg(En_Dtc_MassageMotorOvercurrent,TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_MassageMotorOvercurrent, FALSE);
		}
		
		//lin���ݳ���
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
* @par �ӿ�ԭ��
       static void Diag_VoltAbnromalOpt(void)
* @par ����
       ��ѹ�ж�
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
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};//��0�õĸ���������
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
			/*��ѹ������15.5V*/
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
			/* ��·��ѹ����16.5V */
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
			/* ��·��ѹ������9.5V */
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
			/* ��·��ѹ����8.5V */
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
 * @description:	���μ����������
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
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
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit))//˾��������
	{
		//˾�������μ���ʱ�߶˶̵ش���40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_DrHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, FALSE);
		}

		//˾�������μ���ʱ�߶˿�·����200ms
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
		Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, FALSE);//������ʱ�����־λ �����ٴμ���
		Diag_SetDTCFlg(En_Dtc_DriverSeatHeatingOutputDisconnected, FALSE);
	}


	//&&��˾�����������ڼ���
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit))
	{
		//��˾�������μ���ʱ�߶˶̵ش���40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_PaHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, FALSE);
				
		}

		//��˾�������μ���ʱ�߶˿�·����200ms
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
		Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, FALSE);//������ʱ�����־λ �����ٴμ���
		Diag_SetDTCFlg(En_Dtc_PassengerSeatHeatingOutputDisconnected, FALSE);//������ʱ�����־λ �����ٴμ���
	}
	
	//���������ڼ���
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit))
	{
		//�����̼���ʱ�߶˶̵ش���40ms
		if(EN_ALARM_HEAT_TO_GND == Rte_GetVfb_ThirdHeatCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, FALSE);
				
		}

		//�����̼���ʱ�߶˿�·����200ms
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
		Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, FALSE);//������ʱ�����־λ �����ٴμ���
		Diag_SetDTCFlg(En_Dtc_SteeringWheelHeatingOutputDisconnected, FALSE);//������ʱ�����־λ �����ٴμ���
	}
#endif
}


 /***********************************************************************************************
 * @function name:  DSMDiag_vosSeatHeatSensorFaultCheck(void)
 *
 * @description:	���μ��ȴ��������
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
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
		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_DrHeatNTCFaultSts())//�����¶ȴ������̵�ʱ�����1s
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
		
		if(enHeatNtcFault_EN_NTC_FAULT_OPEN == Rte_GetVfb_DrHeatNTCFaultSts())      //�����¶ȴ������̵�Դ���߿�·ʱ�����1s
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

		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_DrHeatNTCFaultSts() )//�����¶ȴ�����������ʱ�����5s
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

	//����NTC���
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit))
	{

		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_PaHeatNTCFaultSts())//�����¶ȴ������̵�ʱ�����1s
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

		//�����¶ȴ������̵�Դ���߿�·ʱ�����1s
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


		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_PaHeatNTCFaultSts())//�����¶ȴ�����������ʱ�����5s
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
	
	//������NTC���
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit))
	{
		if(enHeatNtcFault_EN_NTC_FAULT_GND == Rte_GetVfb_ThirdHeatNTCFaultSts())//�������¶ȴ������̵�ʱ�����1s
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

		//�������¶ȴ������̵�Դ���߿�·ʱ�����1s
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


		if(enHeatNtcFault_EN_NTC_FAULT_UNC == Rte_GetVfb_ThirdHeatNTCFaultSts())//�������¶ȴ�����������ʱ�����5s
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
 * @description:	����ͨ�������
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
 *
 * @author:          zjx
 *
 * @note:           2024-01-02
 ***********************************************************************************************/
static void DSMDiag_vosSeatVentMotorFaultCheck(void)
{
	
	INT16U vot = 0;

#if 0


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&������������ͨ��
	{

		if(TRUE == Rte_GetVfb_DrVentilatePwrFault())//��������ͨ��ʱ������̵�ʱ�����1s
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
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC���ϲż�ʱ
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


	if(Rte_GetVfb_PaVentilate() != enVentLvlSts_EN_VENT_LVL_OFF)//&&������������ͨ��
	{

		if(TRUE == Rte_GetVfb_PaVentilatePwrFault())//����ͨ��ʱ������̵�ʱ�����1s
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
			if(Diag_ReadDtcTestFailFlag(En_Dtc_VentilationFan2PowerSupplySC) == TRUE) //DTC���ϲż�ʱ
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
 * @description:	����ͨ��PWM�źż��
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��
 *
 * @author:          zjx
 *
 * @note:           2024-01-02
 ***********************************************************************************************/
static void DSMDiag_vosSeatVentPWMSignalFaultCheck(void)
{
#if 1


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&����˾����������ͨ��
	{
		//˾������ͨ��ʱ��PWM����źŶ̵�Դ����ʱ�����1s
		if(enVentCmdFault_EN_VENT_FAULT_LOAD == Rte_GetVfb_DrVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply) == TRUE) //DTC���ϲż�ʱ
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
				
			}
			else
			{
			}
			
		}
		//˾������ͨ��ʱ��PWM����źŶ̵ػ�·����ʱ�����1s
		if(enVentCmdFault_EN_VENT_FAULT_OPEN == Rte_GetVfb_DrVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC���ϲż�ʱ
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
	


	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit))//&&����˾����������ͨ��
	{
		//��˾������ͨ��ʱ��PWM����źŶ̵�Դʱ�����1s
		if(enVentCmdFault_EN_VENT_FAULT_LOAD == Rte_GetVfb_PaVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, TRUE);
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply) == TRUE) //DTC���ϲż�ʱ
			{
				Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, FALSE);
			}
			else
			{
			}
			
		}
		//��˾������ͨ��ʱ��PWM����źŶ̵ػ�·ʱ�����1s
		if(enVentCmdFault_EN_VENT_FAULT_OPEN == Rte_GetVfb_PaVentCmdFaultSts4DTC())
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
			Diag_SetDTCFlg(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, TRUE);
		
		}
		else
		{
			if(Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit) == TRUE) //DTC���ϲż�ʱ
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
* @description:    ���ο��Ƽ��
*
* @input parameters:	 void
*
* @output parameters:	  void
*
* @return:		   void
*
* @note:		   ��
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

		//Ӳ�߿���ճ������-����������ǰ����ճ��
		if(Rte_GetVfb_DrLengthSwitchAdheErr_ForWard() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//Ӳ�߿���ճ������-����������󿪹�ճ��
		if(Rte_GetVfb_DrLengthSwitchAdheErr_Back() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//Ӳ�߿���ճ������-���ݿ�����ǰ����ճ��
		if(Rte_GetVfb_DrBackSwitchAdheErr_ForWard() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//Ӳ�߿���ճ������-���ݿ�����󿪹�ճ��
		if(Rte_GetVfb_DrBackSwitchAdheErr_Back() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		
		//Ӳ�߿���ճ������-���ݸ߶����Ͽ���ճ��
		if(Rte_GetVfb_DrHeightSwitchAdheErr_ForWard() != FALSE) //
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, FALSE);
		}
		
		//Ӳ�߿���ճ������-���ݸ߶����¿���ճ��
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
		//Ӳ�߿���ճ������-�����������Ͽ���ճ��
		if(Rte_GetVfb_DrFrontSwitchAdheErr_ForWard() != FALSE)
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//Ӳ�߿���ճ������-�����������¿���ճ��
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
		//Ӳ�߿���ճ������-����������ǰ����ճ��
		if(Rte_GetVfb_PaLengthSwitchAdheErr_ForWard() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//Ӳ�߿���ճ������-����������󿪹�ճ��
		if(Rte_GetVfb_PaLengthSwitchAdheErr_Back() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, FALSE);
		}

		//Ӳ�߿���ճ������-���ݿ�����ǰ����ճ��
		if(Rte_GetVfb_PaBackSwitchAdheErr_ForWard() != FALSE)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, TRUE);
			
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, FALSE);
		}

		//Ӳ�߿���ճ������-���ݿ�����󿪹�ճ��
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
		//�������������� ���������2s��û�н��յ�����λ�ô���������
		if(Rte_GetVfb_DrHeightDTCHallErr() != FALSE) //���ݸ߶Ȼ�����ʧ
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
		if(Rte_GetVfb_DrLengthDTCHallErr() != FALSE) //�������������ʧ
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
		if(Rte_GetVfb_DrBackDTCHallErr() != FALSE) //���ݿ���������ʧ
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
		if(Rte_GetVfb_DrFrontDTCHallErr() != FALSE) //����ǰ���ǶȻ�����ʧ
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
		if(Rte_GetVfb_PaLengthDTCHallErr() != FALSE) //�������������ʧ
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
		if(Rte_GetVfb_PaBackDTCHallErr() != FALSE) //���ݿ���������ʧ
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, FALSE);
		}
	}
	
	//���ݸ����򡢿����̵�������ճ��
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued))
	{
		if(Rte_GetVfb_DrHeightRelayAdheErr() != FALSE) //���ݸ߶ȼ̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, TRUE);
		}
		else
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, FALSE);
		}
		
		if(Rte_GetVfb_DrLengthRelayAdheErr() != FALSE) //��������̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, TRUE);	
		}
		else //������޵�ѹ��������ʧ
		{
			
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, FALSE);
		}

		if(Rte_GetVfb_DrBackRelayAdheErr() != FALSE) //���ݿ����̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, TRUE);
			
		}
		else //������޵�ѹ��������ʧ
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, FALSE);
		}
	}
	
	//����ǰ���Ƕȼ̵�������ճ��
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued))
	{
		if(Rte_GetVfb_DrFrontRelayAdheErr() != FALSE) //����ǰ���Ƕȼ̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, TRUE);
		}
		else //������޵�ѹ��������ʧ
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, FALSE);
		}
	}
		
	//���ݼ̵�������ճ��
	if(TRUE == Diag_getMonitorEnableCriteria(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued))
	{
		if(Rte_GetVfb_PaLengthRelayAdheErr() != FALSE) //��������̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, TRUE);

		}
		else//������޵�ѹ��������ʧ
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, FALSE);
		}

		if(Rte_GetVfb_PaBackRelayAdheErr() != FALSE) //���ݿ����̵�������ճ�� (�������е�ѹ)
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, TRUE);
			
		}
		else //������޵�ѹ��������ʧ
		{
			Diag_WriteDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, FALSE);
		}
		
	}
	
#endif
}


#if 0
/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Diag_LinNodeComLostOpt(void)
* @par ����
       LIN�ڵ���ع���
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
	INT8U eTimeCount = 0;//������ʼ��ʱ���¼
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
		/*ON�缰����û�дﵽ3s��ִ��ͨѶ���������λ*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			for(eTimeCount = En_Dtc_NocommunicationonLIN1 ; eTimeCount < En_Dtc_LeftDIFlasher_OvercurrentOrSCG ; eTimeCount++)
			{
				u32DiagDtcTestFailTs[eTimeCount] = D_HAL_GET_CUR_MS_TS();
			}
			return;
		}
	}
	if (Diag_CommDtcWorkInd == TRUE) /*��ѹ��Χ����������ecu��ʼ�����*/
	{
		if (Diag_CommMsgTimeoutInd == TRUE)
		{
			if(Srv_GetMemCfgData(VEHENEBSPRM) == 0x00u) //δ����EBSֱ���˳����;
			{
				return ;
			}
			/*LIN1 ͨѶ��ʧ ����⵽Lin1�����б��Ķ�ʧ�ҳ���ʱ��t >= 20���������ڣ��ù�����*/
			if( (Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x34) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x35) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x36) == FALSE) && \
					(Ecual_LinIsMsgRecvValid(LIN_DEV_ID_LIN1, 0x37) == FALSE) )
			{
				if(CPU_TimerDiffTs(u32DiagDtcTestFailTs[En_Dtc_NocommunicationonLIN1]) > D_LostCom_HoldOnTime)
				{
					Diag_WriteDtcTestFailFlag(En_Dtc_NocommunicationonLIN1, TRUE);//N822,lin��ֻ��һ��EBS������EBSӦ��������DTC
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
	/*����������EBS��lin�źŴ���*/
	if(1 == LinRx_0x34_EBS_Error_Ident()) //EBS IDУ�����
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

	if(1 == LinRx_0x34_EBS_Error_Calib()) //EBS����У�����
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

	if(1 == LinRx_0x34_EBS_Resp_Error()) //EBS�ڵ���Ӧ����
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
* @par �ӿ�ԭ��
       static void Diag_TLE75RlyFaltOpt(void)
* @par ����
       TLE75Xz������ع���
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
	/* ACC IGN1 IGN2�̵��� ����״̬�ж� */
	INT8U  bPowerMode = 0;
	bPowerMode = Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);

	if((bPowerMode != 2u) && (bPowerMode != 4U))
	{
		u32PowerOnTs = D_HAL_GET_CUR_MS_TS();
		return;
	}
	else
	{
		/*ON�缰����û�дﵽ3s��ִ��ͨѶ���������λ*/
		if(CPU_TimerDiffTs(u32PowerOnTs) < 3UL * 1000UL)
		{
			return;
		}
	}




}

#endif
/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName)
* @par ����
       BTS������������ж�
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
* @par �ӿ�ԭ��
       static BOOL Diag_BtsHighDriversChipFaultCheck(DiagDtcNameType_t enDtcName)
* @par ����
       BTS������������ж�(�˺���ר������ת��ƺ���ת��ƵĶ�·����)
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
			//������ת��Ƶ�ʱ�����Ϊ0���ú���Ҳֻ�����غ���
			return Diag_ReadDtcTestFailFlag(enDtcName);
		}

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_LackLoad) && \
				(u16LoadUpImA != 0U) && (u16LoadDownImA != 0U) )
		{
			//��ֵ�ķ�Χ
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
			//������ת��Ƶ�ʱ�����Ϊ0���ú���Ҳֻ�����غ���
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
* @par �ӿ�ԭ��
       static BOOL Diag_Bts_PosLp1Ctrl_RearFogLpCtrl_FaltOpt(void)
* @par ����

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

	/* ����� */
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

	/* λ�õ� */
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
* @par �ӿ�ԭ��
       static BOOL Diag_Bts_RightDIFlasher_LeftDIFlasher_FaltOpt(void)
* @par ����

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

	/* ��ת��� */
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

	/* ��ת��� */
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
* @par �ӿ�ԭ��
       static BOOL Diag_Bts_LhFrFogLamp_RhFrFogLamp_FaltOpt(void)
* @par ����

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

	/* ��ǰ��� */
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

	/* ��ǰ��� */
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
* @par �ӿ�ԭ��
	   static BOOL Diag_Bts_LeftRightCornerLp_FaltOpt(void)
* @par ����

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


	/* ��ǵ� */
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

	/* �ҽǵ� */
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
* @par �ӿ�ԭ��
	   static BOOL Diag_Bts_DayRunLpPosLp_FaltOpt(void)
* @par ����

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
	DiagDtcMaskDat_t DiagDtcMaskDat = {0};//�����õĸ�������
	BOOL bRet[4] = {FALSE};
	INT16U u16DriverISTemp = 0 ;
	static INT8U u8OverCurrentCount = 0;
	static INT8U u8OpenLoadCount = 0;
	//enIn[0] = Ecual_GpioGetChlState(EN_OUT_DayRunLpCtrl);
	//enIn[1] = Ecual_GpioGetChlState(EN_OUT_PosLpCtrl);

	/* �ռ��г��� */
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

	/* С��2 */
	if(enIn[1] == EN_GPIO_LEV_HIGH)
	{
		if(Diag_ReadDtcTestFailFlag(En_Dtc_SideBeamLamp_OverCurrentOrSCG) == FALSE)
		{
			u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DayRunLpPosLp, 1); //С�Ƹ���2����
			if(u16DriverISTemp > 4400) //С��2���ص���4.4A
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
			u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DayRunLpPosLp, 1); //С�Ƹ���2����
			if(u16DriverISTemp < 10) //С��2��·����С��0.01A
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
* @par �ӿ�ԭ��
	   static BOOL Diag_Bts_ReverseLpBrakeLp_FaltOpt(void)
* @par ����

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

	/* ������ */
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

	/* ɲ���� */
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
* @par �ӿ�ԭ��
	   static  BOOL Diag_Bts_DOME_LAMP_FaltOpt(void)
* @par ����

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

	/* �Ҷ��� */
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
* @par �ӿ�ԭ��
       static void Diag_TLE75RlyFaltOpt(void)
* @par ����
       TLE75Xz������ع���
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
		/*ON�缰����û�дﵽ3s��ִ��ͨѶ���������λ*/
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
* @par �ӿ�ԭ��
	   static void Diag_OutReserveratureFaultOpt(void)
* @par ����
       �¶ȴ���������
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
		/*ON�缰����û�дﵽ3s��ִ��ͨѶ���������λ*/
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

	if(u16TempDetectSensor >= 50000UL)//��ȡ������ֵ��50000UL������Ҫ���ù��ϲ��ܴ���50000UL
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
* @par �ӿ�ԭ��
	   static void Diag_FeedbackFailure(void)
* @par ����
       �ض���һ�´����¼ (��ǰ����״̬���ش���
       ��ǰ��λ�λ�źŴ���ACC,IG1,IG2�̵�����λ�źŴ���)
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
	/*��ǰ����״̬*/
	
	{
		u32DiagDtcTestFailTs[En_Dtc_DoorLockStatusDrSwitchLogicError] = D_HAL_GET_CUR_MS_TS();
		Diag_WriteDtcTestFailFlag(En_Dtc_DoorLockStatusDrSwitchLogicError, FALSE);
	}

	/*ǰ��λ�λ�ź�*/
	
	{
		u32DiagDtcTestFailTs[En_Dtc_FrontWiperZeroPositionSwitchLogicError] = D_HAL_GET_CUR_MS_TS();
	}

	if(u8CfgVehOpModePrm == 0) //���óɷ�PEPS�ſ�������ЩDTC
	{

	}

}
/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
	   static void Diag_SpecialDtc(void)
* @par ����
       ��Ҫ��������������ON���ģ�����������ȼ̵���
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
		En_Dtc_RearFogLamp_OverCurrentOrSCG, 	/* ����ƹ�����Եض�· */
		En_Dtc_RearFogLamp_OpenLoadOrSCV, 		/* ����ƿ�·��Ե�Դ��· */
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
		En_Dtc_SideBeamLamp_OverCurrentOrSCG,	/* λ�õƹ�����Եض�·   */
		En_Dtc_SideBeamLamp_OpenLoadOrSCV,		/* λ�õƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},

	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LeftDIFlasher_OvercurrentOrSCG, 	/* ��ת��ƹ�����Եض�· */
		En_Dtc_LeftDIFlasher_OpenLoadOrSCV, 	/* ��ת��ƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},

	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_RightDIFlasher_OvercurrentOrSCG, /* ��ת��ƹ�����Եض�· */
		En_Dtc_RightDIFlasher_OpenLoadOrSCV, 	/* ��ת��ƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LhFrFogLamp_OverCurrentOrSCG, 	/* ��ǰ��ƹ�����Եض�· */
		En_Dtc_LhFrFogLamp_OpenLoadOrSCV, 		/* ��ǰ��ƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_RhFrFogLamp_OverCurrentOrSCG, 	/* ��ǰ��ƹ�����Եض�· */
		En_Dtc_RhFrFogLamp_OpenLoadOrSCV, 		/* ��ǰ��ƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_Leftcornerlamp_OverCurrentOrSCG, 	/* ��ǵƹ�����Եض�· */
		En_Dtc_Leftcornerlamp_OpenLoadOrSCV, 		/* ��ǵƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_Rightcornerlamp_OverCurrentOrSCG, 	/* �ҽǵƹ�����Եض�· */
		En_Dtc_Rightcornerlamp_OpenLoadOrSCV, 		/* �ҽǵƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_DayDriveLamp_OverCurrentOrSCG, 		/* �ռ��г��ƹ�����Եض�· */
		En_Dtc_DayDriveLamp_OpenLoadOrSCV, 			/* �ռ��г��ƿ�·��Ե�Դ��· */
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
		En_Dtc_ReverseLamp_OverCurrentOrSCG, 		/* �����ƹ�����Եض�· */
		En_Dtc_ReverseLamp_OpenLoadOrSCV, 			/* �����ƿ�·��Ե�Դ��· */
		0,
		50U,
		1000U, 0,
	},
	{
		&Ecual_GpioGetChlState,
		D_DTCTest,
		NULL,
		0,
		En_Dtc_LBrakeLamp_OverCurrentOrSCG, 		/* ɲ���ƹ�����Եض�· */
		En_Dtc_LBrakeLamp_OpenLoadOrSCV, 			/* ɲ���ƿ�·��Ե�Դ��· */
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
* @par �ӿ�ԭ��
	   static BOOL Diag_LoadDiagCheck(DiagDtcNameType_t enDtcName,INT8U DiagNum)
* @par ����
       �������ȷ��
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
		u16DigTimeout = pDiagResult[DiagNum].DecTotalTs / u16DigTimeout; 	/****�����ʱ��/�������*****/

		u16DriverISTemp = Ecual_AdcGetBoardBtsHighDriverIS(u8BtsHighDrvChip, u8BtsHighDrvChipChl);

		if((u8FaultSort == D_DiagBtsHDriver_Fault_OverLoad) && (u16LoadUpImA != 0U) ) /*�Ե�Դ��·*/
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

		if( (u8FaultSort == D_DiagBtsHDriver_Fault_OpenLoad) && (u16LoadDownImA != 0U) )  /*�Եض�·*/
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
* @par �ӿ�ԭ��
	   void Diag_LoadDiagHandle(void)
* @par ����
       �������
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
			/*�������͵ƹ⹤��ʱ���������*/
			if(EN_GPIO_LEV_HIGH == pDiagLoadDat[index].GpioStatus(pDiagLoadDat[index].GpioSignal))
			{
				Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOverCurrentOrSCG, index);
				Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOpenLoadOrSCV, index);
				//Diag_LoadDiagCheck(pDiagLoadDat[index].DiagOneMainOpenLoad,index);
			}
		}

		for(index = EN_DIAG_LOAD_HIGHBEAMRLY; index < EN_DIAG_LOAD_MAX; index++)
		{
			/*Զ��ƻ��߽���Ƽ̵�������ʱ���������*/

			if(TRUE == pDiagLoadDat[index].RlySta(pDiagLoadDat[index].DriveType))
			{
				u16DigRlyTimeout = pDiagLoadDat[index].PeriodTs;
				u16DigRlyTimeout = pDiagLoadDat[index].DecTotalTs / u16DigRlyTimeout;

				/*********************Զ��ƻ��߽���ƿ�·���**************************************/
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

				/*********************Զ��ƻ��߽���ƿ�·���**************************************/
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
	INT8U sum = 0;  //sum���ص�BCD��
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
* @par �ӿ�ԭ��
	   void GetSnapData(INT8U *msgBuf,INT8U length)
* @par ����
       ��ȡ��������
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
	/*��𿪹ػ�ȡ*/
	BOOL bACCSw = 0;
	BOOL bIGNSw = 0;
	BOOL bStartSw = 0;//Ecual_GetDigitalSwStatus(EN_StartSw);
	INT8U bMode = 0;//Srvl_Get_D_Simulink_PksPwrMode(D_Simulink_PksPwrMode);

	
	/*�������뿪ʼ*/
	cVehSpd = CanRx_0x284_ABS_VehicleSpeed();
	cDataBuf[0] = (INT8U)(cVehSpd >> 8u);
	cDataBuf[1] = (INT8U)(cVehSpd) & 0xFFu;
	msgBuf[index++] = cDataBuf[0];
	msgBuf[index++] = cDataBuf[1];
	/*�����������*/

	
	/*ʱ�����뿪ʼ*/
//	msgBuf[index++] = decimal_bcd_code( CanRx_0x527_EHC6_N_Year());//CanRx_0x581_IC_Year() - 3;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Month());//CanRx_0x581_IC_Month() + 1;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Day());//CanRx_0x581_IC_Date() + 1;
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Hour());//CanRx_0x581_IC_Hour();
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Minute());//CanRx_0x581_IC_Minute();
//	msgBuf[index++] = decimal_bcd_code(CanRx_0x527_EHC6_N_Second());//CanRx_0x581_IC_Second();
	/*ʱ���������*/

	/*��������ѹ���뿪ʼ*/
	cBoardvolt = Srvl_Get_SupplyVoltage();
	cDataBuf[0] = (INT8U)(cBoardvolt >> 8u);
	cDataBuf[1] = (INT8U)(cBoardvolt);
	msgBuf[index++] = cDataBuf[0];
	msgBuf[index++] = cDataBuf[1];
	/*��������ѹ�������*/

	



	msgBuf[index++] = 0;// �����ᴦ����������

}


#if 0
#if 1

/*λ�õ�����ź�*/
BOOL Diag_BCM_PosLmpResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_POSLP1].LmpDigResult;
	return DiagResult;
}

/*ǰ�������ź�*/

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

/*���������ź�*/
BOOL Diag_BCM_RearFogLmpResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;
	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_REARFOGLP].LmpDigResult;
	return DiagResult;
}

/*ת�������ź�*/
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

/*����������ź�*/
BOOL Diag_BCM_ReversinglightResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_REVERSELP].LmpDigResult;
	return DiagResult;
}

/*�ƶ�������ź�*/
BOOL Diag_BCM_BrakelightResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	BOOL DiagResult = pDiagResult[EN_DIAG_LOAD_BRAKELP].LmpDigResult;
	return DiagResult;
}


BOOL DiagResult11 = FALSE;

/*�ռ��г�������ź�*/
BOOL Diag_BCM_DayRunningLampResult(void)
{
	DiagLoadDat_t *pDiagResult = &DiagLoadCtrl;

	DiagResult11 = pDiagResult[EN_DIAG_LOAD_DAYRUNLP].LmpDigResult;

	return DiagResult11;
}
#endif
#endif

