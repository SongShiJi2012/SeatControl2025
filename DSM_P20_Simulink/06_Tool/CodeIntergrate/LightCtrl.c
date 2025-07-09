/****************************Copyright (c)**************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------
** File Name:               LightCtrl.C
** Last modified Date:      2016.02.29
** Last Version:            V1.0
** Description:
**
**------------------------------------------------------------------------------
** Created By:              zyc
** Created date:            2016.02.29
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
**
**------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
*******************************************************************************/


#include "components.h"
#include "LightCtrl.h"
#include "drv_public.h"
#include "hal_public.h"
#include "app_public.h"
#include "hal_595OutPut.h"
#include "srv_memory.h"
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_can_resolver.h"
#include "hal_light.h"
#include "VoltageCheck.h"

#include "pks.h"
#include "alarm_manage.h"
#include "uds_pub.h"

/* Insert simulink model.h [begin] */
#include "Rte_get_Light.h"
#include "LightCtrl.h"
/* Insert simulink model.h [end] */


#define		D_LightCtrlTask_Period		            			(10U)// 10MS

#define     D_Time_600MS                               			(600U / D_LightCtrlTask_Period) // 600ms

#define     D_Time_125MS                               			(125U / D_LightCtrlTask_Period) // 125ms
#define     D_Time_250MS                               			(250U / D_LightCtrlTask_Period) // 250ms


#define     D_Time_1S                               			(1000U / D_LightCtrlTask_Period) // 1S

#define     D_Time_1Piont5S                             		(1500U / D_LightCtrlTask_Period) // 1.5S

#define     D_Time_3S                               			(3000U / D_LightCtrlTask_Period) // 3S

#define     D_Time_5S                               			(5000U / D_LightCtrlTask_Period) // 5S

#define     D_Time_10S                               			(10000U / D_LightCtrlTask_Period) // 10S


#define 	D_LSLightOn_DelayTime				    			(50U / D_LightCtrlTask_Period) // 50MS
#define 	D_LSLightOff_DelayTime				    			(150U / D_LightCtrlTask_Period) // 150MS

#define 	D_WaittingLin_DelayTime				    			(500U / D_LightCtrlTask_Period) // 500MS

#define     D_FollowMeHomeDoorOpen_Time 		        		(30000U / D_LightCtrlTask_Period) // 30S

#define     D_FollowMeHomeLightOn_Time 		        			(30000U / D_LightCtrlTask_Period) // 30S
#define     D_HighBeamSwPressed_Time                			(100U / D_LightCtrlTask_Period) // 2S - > 100ms

#define     D_FollowMeHome_WaitDoorLockTime         			(2000U / D_LightCtrlTask_Period) // 2S

// --------------------------- Turn Light Flash Time Define --------------------
#define     D_TurnLightFlashNumber_Min	            			(3U)

#define     D_TurnLightFlash_Period_2_5Hz	        			(400U / D_LightCtrlTask_Period) // 
#define     D_TurnLightFlash_Period_1_67Hz	        			(600U / D_LightCtrlTask_Period) // 
#define     D_TurnLightFlash_Period_1_25Hz	        			(800U / D_LightCtrlTask_Period) //


#define     D_TurnLightFlash_On_2_5Hz	           	 			(200U / D_LightCtrlTask_Period) // 
#define     D_TurnLightFlash_On_1_67Hz	           	 			(300U / D_LightCtrlTask_Period) // 
#define     D_TurnLightFlash_On_1_25Hz            				(400U / D_LightCtrlTask_Period) // 



#define     D_PEPSAlarm_SetAlarmSuccess_FlashNumber		        (1U) // ��ȫ����ɹ�������ת��� 600ms ������˸һ��


#define     D_PEPSAlarm_CancelAlarmSuccess_FlashNumber		    (2U) // �����ɹ�������ת��� 800ms ������˸����


#define     D_PEPSAlarm_RemoteSearchCar_FlashNumber		        (3U) // ң��Ѱ��ʱ������ת��� 800ms ������˸����


#define     D_PEPSAlarm_ShortRemoteTrunk_FlashNumber		    (1U) // �̰�ң�ؿ����䣬����ת��� 800ms ������˸һ��


#define     D_PEPSAlarm_ThiefWarning_FlashTimes		            (10) // ������������

#define     D_PEPSAlarm_ThiefWarning_FlashONTime		        (25000U / D_LightCtrlTask_Period) // ������������25S
#define     D_PEPSAlarm_ThiefWarning_FlashOffTime		        (5000U / D_LightCtrlTask_Period) // ������������ֹͣ5S
#define     D_PEPSAlarm_ThiefWarning_FlashTotalTime		        (30000U / D_LightCtrlTask_Period) // ����������������30S


#define     D_PEPSAlarm_SearchCarTime		        			(30000U / D_LightCtrlTask_Period) // ����������������30S



#define     D_DomeLightOnMaxTime_Min            				(RoofLampLightOnMaxTimeCfg) // Min ��
#define 	D_DomeLightOn_MaxTime			    				((INT32U)((INT32U)D_DomeLightOnMaxTime_Min*60*1000 - 30U*1000U) / D_LightCtrlTask_Period) // 8Min=8*60*1000MS
#define 	D_DomeLightOnMaxTime_Min_Default					(8U) // Min

#define		D_DomeLightDimmingON_Time		        			(1500U / D_LightCtrlTask_Period) // 1.5S
#define		D_DomeLightDimmingOFF_Time		        			(2500U / D_LightCtrlTask_Period) // 2.5S
#define		D_DomeLightTurnOff_DelayTime	    				(30000U) // 30S

#define		D_OpenDoorLightDimmingON_Time		        		(1500U / D_LightCtrlTask_Period) // 1.5S
#define		D_OpenDoorLightDimmingOFF_Time		        		(2500U / D_LightCtrlTask_Period) // 2.5S
#define		D_OpenDoorLightTurnOff_DelayTime	    			(8000U) // 8S

#define		D_CornerLeftLightOn_TimeoutTime	    				((INT32U)2*60*1000 / D_LightCtrlTask_Period) // 2Min = 2 * 60S = 120000ms = 12000 * 10ms
#define		D_CornerLightOn_Angle			    				(540U) // 54�� // E = N * 0.1 => 54 = 540 * 0.1
#define		D_CornerLightOff_Angle			    				(500U) // 50��	// E = N * 0.1 => 50 = 500 * 0.1
#define		D_CornerLightOn_MaxSpeed		    				(320U) //40km/h  // Speed = V * 0.125 => 40 = 320 * 0.125
#define		D_CornerLightOff_DelaySpeed 	    				(40U)  // 5km/h ���� // Speed = V * 0.125 => 5 = 40 * 0.125

#define		D_LightForBatterySave_Speed	        				(40U)  // 5km/h  // Speed = V * 0.125 => 5 = 40 * 0.125



#define		D_AllDoor_DoorSts		            				LightCtrlStManage.DoorState
#define		D_FrontLeft_DoorSts		            				(LightCtrlStManage.DoorState & 0x01)
#define		D_FrontRight_DoorSts	            				(LightCtrlStManage.DoorState & 0x02)
#define		D_RearLeft_DoorSts		            				(LightCtrlStManage.DoorState & 0x04)
#define		D_RearRight_DoorSts		            				(LightCtrlStManage.DoorState & 0x08)
#define		D_Trunk_DoorSts			            				(LightCtrlStManage.DoorState & 0x10)

#define		FourDoorClose		                				((0x10 == (D_AllDoor_DoorSts & 0x0F)) ? TRUE : FALSE)  // Close = 0; Open = 1
#define		AllDoorClose		                				((0x00 == (D_AllDoor_DoorSts & 0x1F)) ? TRUE : FALSE)  // Close = 0; Open = 1



#define		D_Driver_DoorLockSts	            				(LightCtrlStManage.DLockState & 0x01)
//#define		D_Passenger_DoorLockSts	            				(LightCtrlStManage.DLockState & 0x02)
//#define		D_Trunk_DoorLockSts		            				(LightCtrlStManage.DLockState & 0x10)





//--------------- Door Status --------------------------------------------------
typedef enum
{
	enDoor_Close,	
	enDoor_Open	
} enDoorSts;

//--------------- Lock Status --------------------------------------------------
typedef      enum
{
	enLock_Locked,
	enLock_Unlocked
} enLockSts;

//----------- PEPS Lock Command ------------------------------------------------
typedef enum
{
	enPEPSLock_Inactive = 0,
	enPEPSLock_RKE,
	enPEPSLock_PKE,
	enPEPSLock_Auto
} enPEPSLockCmd;

//----------- PEPS Unlock Command ----------------------------------------------
typedef enum
{
	enPEPSUnlock_Inactive = 0,
	enPEPSUnlock_RKE,
	enPEPSUnlock_PKE,
	enPEPSUnlock_Auto
} enPEPSUnlockCmd;

//---------------���ص�״̬-----------------------------------------------------
typedef enum
{
	enSw_Off,
	enSw_On
}enSwSts;

//--------------- �����ĸ���״̬ -----------------------------------------------
typedef enum
{
	enLightLoad_Normal,
	enLightLoad_Under,
	enLightLoad_Over
}enLightLoadSts;


typedef		enum
{
	enSteerWheelAngleDir_NotSure,
	enSteerWheelAngleDir_Left,
	enSteerWheelAngleDir_Right
} enSteerWheelAngleDir;


typedef		union
{
	INT8U	Byte;
	struct
	{
		enDoorSts	FrontLeftDoorSts		: 1; // Front Left Door Sts
		enDoorSts	FrontRightDoorSts		: 1; // Front Right Door Sts
		enDoorSts	RearLeftDoorSts			: 1; // Rear Left Door Sts
		enDoorSts	RearRightDoorSts		: 1; // Rear Right Door Sts

		enDoorSts	TrunkDoorSts			: 1; // Trunk Door Sts
		INT8U		Reserved				: 3; // Reserved
	} Bits;
} unDoorSts;
//--------------��������--------------------------------------------------------


enOutputReqType		LeftPosLight_OutputReq; 	// ���λ�õ��������
enOutputStsType		LeftPosLight_OutputSts; 	// ���λ�õ����״̬

enOutputReqType		RightPosLight_OutputReq; 	// �Ҳ�λ�õ��������
enOutputStsType		RightPosLight_OutputSts; 	// �Ҳ�λ�õ����״̬


enOutputReqType		LicenseLight_OutputReq; 	// ���յ��������
enOutputStsType		LicenseLight_OutputSts; 	// ���յ����״̬



enOutputReqType		LowBeam_OutputReq; 	    // ������������
enOutputStsType		LowBeam_OutputSts; 	    // ��������״̬

enOutputReqType		HighBeam_OutputReq; 	    // Զ����������
enOutputStsType		HighBeam_OutputSts; 	    // Զ������״̬

enOutputReqType		TurnLampSts_Left_OutputReq; 	// ��ת����������
enOutputStsType		TurnLampSts_Left_OutputSts; 	// ��ת�����״̬

enOutputReqType		TurnLampSts_Right_OutputReq; 	// ��ת����������
enOutputStsType		TurnLampSts_Right_OutputSts; 	// ��ת�����״̬


enOutputReqType		LeftAssistLight_OutputReq; 	// �������������
enOutputStsType		LeftAssistLight_OutputSts; 	// ���������״̬

enOutputReqType		RightAssistLight_OutputReq; 	// �Ҹ������������
enOutputStsType		RightAssistLight_OutputSts; 	// �Ҹ��������״̬


INT8U				TurnLight_LackSts; // ת���ȱ�����
BOOL				TurnLightLackCfgFlg;

enOutputReqType		Daylight_OutputReq; 	// ����г����������
enOutputStsType		Daylight_OutputSts; 	// ����г������״̬

enOutputReqType		FogLamp_Front_OutputReq; 	// ǰ����������
enOutputStsType		FogLamp_Front_OutputSts; 	// ǰ������״̬

enOutputReqType		FogLamp_Rear_OutputReq; 	// ������������
enOutputStsType		FogLamp_Rear_OutputSts; 	// ��������״̬

enOutputReqType		BrakeLamp_OutputReq; 	// ɲ�����������
enOutputStsType		BrakeLamp_OutputSts; 	// ɲ�������״̬

enOutputReqType		ReverseLamp_OutputReq; 	    // �������������
enOutputStsType		ReverseLamp_OutputSts; 	    // ���������״̬


enOutputReqType     HazardSwLED_OutputReq;     // Σ�տ���LED���������
enOutputStsType     HazardSwLED_OutputSts;     // Σ�տ���LED�����״̬


enLightSts		    IPLightSts;				// ����Ƶ�״̬

enLightSts		    DomeLightSts;				// �����״̬
enLightSts		    OpenDoorLightSts;				// �ſ�����״̬
enLightSts		    AmbienceLightSts;				// ��Χ��״̬


stTurnLightOp	    TurnLightOp;



INT8U               RoofLampLightOnMaxTimeCfg;
INT8U               LightForceToSleepDelayTimeCfg;



enLightSwSts 		LightSwSts;


//static	enLockSts	D_Driver_DoorLockSts = enLock_Locked;

enPEPSLockCmd		        PEPSLockCmd;
enPEPSUnlockCmd		        PEPSUnlockCmd;



enLightLoadSts      TurnLight_Left_LoadSts; // ��ǰת��Ƹ������
enLightLoadSts      TurnLight_Right_LoadSts; // ��ǰת��Ƹ������

enLightLoadSts      PosLight_LoadSts; // λ�õƸ������
enLightLoadSts      RearFogLamp_LoadSts; // ����Ƹ������
enLightLoadSts      BrakeLamp_LoadSts; // ɲ���Ƹ������
enLightLoadSts      ReverseLamp_LoadSts; // �����Ƹ������
enLightLoadSts      Daylight_LoadSts; // �����Ƹ������


static BOOL                        ClosePEPSRkePkeFunction;

static enPEPSRemoteAlarmCmd PEPSRemoteAlarmCmd = enAlarm_Invalid;








enSteerWheelAngleDir	SteerWheelAngleDir;
BOOL					SteerWheelAngleErrorFlg; // ת�Ǵ����־
INT16U		SteerWheelAngle; 	// ��

LightCtrlStManage_t LightCtrlStManage = {0};

static GWBSDM10x16_t 	GWBSDM1CanInfo;
static GWBEMS20x320_t  GWBEms2Info;
static GWBBrake10x130_t GWBBrake1Info;
static MenuSet10x375_t		MenuSet1Info;
static TBOX10x478_t	Tbox1Info;
static TBOX20x479_t	Tbox2Info;
static CP40x473_t  CP4Info;
static PEPS1StInfo0x166_t UpPeps1StInfo;

static GWBEMS50x125_t GWBEMS5Info;

static GWBEPB10x436_t GWBEPB1Info;

static GWBTCM10x326_t GWBTCM1Info;

static PLG10x37A_t PLG10x37AInfo;


static	GWBCRRRL10x34B_t GWBCRRRL10x34BInfo;
static  EMSAPA30x43F_t  EMSAPA30x43FInfo;


static GWBDAC10x41B_t GWBDAC10x41BInfo;
static Audio110x37C_t Audio110x37CInfo;


static strEepromLampOutdoorCtrlSys *pEepOutDoorCtrlParam_InLightFunc = NULL;
static strEepromLampIndoorCtrlSys *pEepInDoorCtrlParam_InLightFunc = NULL;
static strEepromBodyGuardAntitheft *pEepromBodyGuardAntitheft_InLightFunc = NULL; 
static strEepromVehicleModeCfg *pEepromVehicleModeCfg_InLightFunc = NULL; 




/*-----------------------------��Ʊ���-----------------------------------------------*/



INT8U LA1_St_LowBeam = 0;
INT8U LA1_St_PosLamp = 0;

INT8U IBCM_St_LowBeamCommandFR;
INT8U IBCM_St_LowBeamCommandFL;

INT16U Speed;
INT8U ICMS1_S_ExLampCommand;
INT8U ICMS1_St_ExLampAvailable;

INT8U BCM3_St_LowBeamSwEn;




INT8U BCM3_S_ExLampCommand;

static BOOL NearLightFunction = FALSE;//�����
static BOOL AutoLightFunction = FALSE;//�Զ���
static BOOL AutoFollowLightFunction = FALSE;//�Զ����һؼ�
static BOOL ManuFollowLightFunction = FALSE;//�ֶ����һؼ�
static BOOL AutoLeaveLightFunction = FALSE;//�Զ��������
static BOOL SpeedLightFunction = FALSE;//����ά�ֽ���ƹ���

static BOOL FarLightFunction = FALSE;//Զ��ƹ���
static BOOL FlashLightFunction = FALSE;//�����ƹ���
static BOOL HMALightFunction = FALSE;//HMA����
static BOOL LeftTurnAssistFunction = FALSE;//��ת��������
static BOOL RightTurnAssistFunction = FALSE;//��ת��������

static BOOL FarAssistFunction = FALSE;//Զ�⸨������

static BOOL SearchCarNearLightFunction = FALSE;//Ѱ����ʼ�Ľ���ƹ���
static BOOL SearchCarRearFrogLampFunction = FALSE;//Ѱ����ʼ����ƹ���

static BOOL FollowLightFunctionTimeStartFlg = FALSE;//���һؼҿ�ʼ��ʱ��־
static INT32U FollowLightFunctionDoorOpenTime = 0U;//���һؼ��ж��ſ���ʼ��ʱ

static INT32U LeaveLightFunctionLinTime = 0U;//������ҵȴ�LIN�źż�ʱ
static INT32U LeaveLightFunctionOnTime = 0U;//����������ƿ�ʼ��ʱ
static INT32U LeaveLightFunctionOnTimeMax = 0U;//���������������ʱ

static INT32U FollowLightFunctionOnTime = 0U;//���һؼ����ƿ�ʼ��ʱ
static INT32U FollowLightFunctionOnTimeMax = 0U;//���һؼ���������ʱ
static INT8U BCM3_St_ComingHome;//���һؼҹ���״̬����
INT8U MS1_St_Available;
INT8U MS1_St_FollowMeTime;

static INT8U BCM3_St_LeavingHome;//������ҹ���״̬����
INT8U MS1_St_LeaveMeTime;



static enIGN ForSpeedLightPowerState;

static BOOL PositionFunction = FALSE;//λ�õƹ���ʹ�ܱ�־
static BOOL HoldFunction = FALSE;//פ����ʹ�ܱ�־
static INT8U BCM3_W_PosLightNotClose = 0U;

static INT8U BCM3_St_HMA = 0U;
static INT8U LA1_St_HMAAvailable = 0U;//HMA����



INT8U CP4_St_Available = 0U;
INT8U CP4_S_ExLampCommand = 0U;
INT8U CP4Lost = 0U;
INT8U CP4_F_System = 0U;


INT8U RS_St_LampReq = 0U;
INT8U CP4_S_FrontFogLamp = 0U;
INT8U CP4_S_RearFogLamp = 0U;

static INT8U RS_F_Lose = 0U;//�ڵ㶪ʧ
static INT8U RS_F_Communication = 0U;//ͨѶ����
static INT8U RS_F_Voltage = 0U;//��ѹ����
static INT8U RS_LightSensor = 0U;//�ƹ⴫��������


INT8U  LA1_St_Dimmer = 0U;

INT8U  CP4_N_DimmSw = 0U;
INT8U LA1_St_TrunkLamp = 0U;

/*------------------------------------------------------------------------------*/
//--------------��������--------------------------------------------------------





/*******************************************************************************
* �������ƣ�LightCtrl_Init
* �����������ƹ���Ƴ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrlPara_Init(void)
{
	LeftPosLight_OutputReq = enOutputReq_Off;
	LeftPosLight_OutputSts = enOutputSts_Off;

	RightPosLight_OutputReq = enOutputReq_Off;
	RightPosLight_OutputSts = enOutputSts_Off;

	LowBeam_OutputReq = enOutputReq_Off;
	LowBeam_OutputSts = enOutputSts_Off;

	HighBeam_OutputReq = enOutputReq_Off;
	HighBeam_OutputSts = enOutputSts_Off;

	TurnLampSts_Left_OutputReq = enOutputReq_Off;
	TurnLampSts_Left_OutputSts = enOutputSts_Off;

	TurnLampSts_Right_OutputReq = enOutputReq_Off;
	TurnLampSts_Right_OutputSts = enOutputSts_Off;

	Daylight_OutputReq = enOutputReq_Off;
	Daylight_OutputSts = enOutputSts_Off;

	FogLamp_Front_OutputReq = enOutputReq_Off;
	FogLamp_Front_OutputSts = enOutputSts_Off;

	FogLamp_Rear_OutputReq = enOutputReq_Off;
	FogLamp_Rear_OutputSts = enOutputSts_Off;

	BrakeLamp_OutputReq = enOutputReq_Off;
	BrakeLamp_OutputSts = enOutputSts_Off;

	ReverseLamp_OutputReq = enOutputReq_Off;
	ReverseLamp_OutputSts = enOutputSts_Off;

	LeftAssistLight_OutputReq = enOutputReq_Off;
	LeftAssistLight_OutputSts = enOutputSts_Off;

	RightAssistLight_OutputReq = enOutputReq_Off;
	RightAssistLight_OutputSts = enOutputSts_Off;

	DomeLightSts = enLight_Off;



	TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
	TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
	TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	TurnLightOp.TurnLightFlashNumber = 0;
	TurnLightOp.TurnLightFlashTime = 0;

	TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

	TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;

	TurnLight_LackSts = (INT8U)enLack_Non;
	TurnLightLackCfgFlg = FALSE;
	LightCtrlStManage.BatterySaveFlg = FALSE;

	RoofLampLightOnMaxTimeCfg = D_DomeLightOnMaxTime_Min_Default;


}
static void LightCtrl_UpdateInputInfo(void)
{
	
	static INT8U CurrTrunkKeySig =0 ;

	pEepOutDoorCtrlParam_InLightFunc = (strEepromLampOutdoorCtrlSys *)Srv_GetEepromWorkParaCfgPtr(EN_WORK_LAMP_OUTDOOR_CTRLSYS_TYPE);//��ȡ�������
	pEepInDoorCtrlParam_InLightFunc = (strEepromLampIndoorCtrlSys *)Srv_GetEepromWorkParaCfgPtr(EN_WORK_LAMP_INDOOR_CTRLSYS_TYPE);//��ȡ�ڵ�����
	pEepromBodyGuardAntitheft_InLightFunc = (strEepromBodyGuardAntitheft *)Srv_GetEepromWorkParaCfgPtr(EN_WORK_BODY_GUARD_ANTITHEFT_TYPE);
	pEepromVehicleModeCfg_InLightFunc =  (strEepromVehicleModeCfg *)Srv_GetEepromWorkParaCfgPtr(EN_WORK_VEHICLE_MODE_CFG_TYPE);//��������

	LightCtrlStManage.VehExLampSwTypePrm = pEepOutDoorCtrlParam_InLightFunc->VehExLampSwTypePrm;
	LightCtrlStManage.ExlMainOrDiAssistLightPrm =pEepOutDoorCtrlParam_InLightFunc->ExlMainOrDiAssistLightPrm;

	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_SDM_1,(INT8U*)&GWBSDM1CanInfo,sizeof(GWBSDM1CanInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_EMS_2,(INT8U*)&GWBEms2Info,sizeof(GWBEms2Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_BRAKE_1,(INT8U*)&GWBBrake1Info,sizeof(GWBBrake1Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_MENU_SET,(INT8U*)&MenuSet1Info,sizeof(MenuSet1Info));
	
	Hal_CanBcmGetInfo(EN_CAN_MSG_TBOX_1,(INT8U*)&Tbox1Info,sizeof(Tbox1Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_TBOX_2,(INT8U*)&Tbox2Info,sizeof(Tbox2Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_CP_4,(INT8U*)&CP4Info,sizeof(CP4Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_PEPS_1,(INT8U*)&UpPeps1StInfo,sizeof(UpPeps1StInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_EMS_5,(INT8U*)&GWBEMS5Info,sizeof(GWBEMS5Info));
	
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_EPB_1,(INT8U*)&GWBEPB1Info,sizeof(GWBEPB1Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_TCM_1,(INT8U*)&GWBTCM1Info,sizeof(GWBTCM1Info));
	Hal_CanBcmGetInfo(EN_CAN_MSG_PLG_1,(INT8U*)&PLG10x37AInfo,sizeof(PLG10x37AInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_CRRRL_1,(INT8U*)&GWBCRRRL10x34BInfo,sizeof(GWBCRRRL10x34BInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_APA_3,(INT8U*)&EMSAPA30x43FInfo,sizeof(EMSAPA30x43FInfo));

	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_DAC_1,(INT8U*)&GWBDAC10x41BInfo,sizeof(GWBDAC10x41BInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_AUDIO_11,(INT8U*)&Audio110x37CInfo,sizeof(Audio110x37CInfo));

	LightCtrlStManage.TrigCrash = GWBSDM1CanInfo.SDM1_StCrashIntensity;
	LightCtrlStManage.EmsEngineRunningSt = GWBEms2Info.EMS2_StEngineRunning;
	LightCtrlStManage.CurrSp = GWBBrake1Info.BR1_NVehicleSpeed/100;	//(km/h)
	LightCtrlStManage.CurrSpValidSt = ((GWBBrake1Info.BR1_FVehicleSpeed == BR1_F_VEHSPEED_Valid)?0:1);
	LightCtrlStManage.AudioStAutoLock = (INT8U)MenuSet1Info.MS1_StAutoLock;
	LightCtrlStManage.AudioStAutoUnLock = (INT8U)MenuSet1Info.MS1_StAutoUnlock;
	LightCtrlStManage.UnlockTypeConf = (INT8U)MenuSet1Info.MS1_StUnlock;
	//LightCtrlStManage.CurrTboxRemoteLockSt = (INT8U)Tbox1Info.TBOX1_StRemoteLockCommand;
	LightCtrlStManage.CurrTboxDigitalLockSt = (INT8U)Tbox2Info.TBOX2_StDigitalKeyCommand;
	LightCtrlStManage.TrunkVirtualSw = (INT8U)CP4Info.CP4_STrunkVirtualSw;
	CP4_St_Available = CP4Info.CP4_StAvailable;
	CP4_S_ExLampCommand = CP4Info.CP4_SExLampCommand;
	CP4_S_FrontFogLamp = CP4Info.CP4_SFrontFogLamp;
	CP4_S_RearFogLamp = CP4Info.CP4_SRearFogLamp;
	CP4_N_DimmSw = CP4Info.CP4_SDimmSw;
	LightCtrlStManage.LightAlarmStStage = (INT8U)GetAlarmMode();


	/*�ⲿ�ź�*/
	((Hal_GetIoVaild(EN_DRIVER_DOOR_LOCK_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK)));/*����ʻ����״̬*/
	((Hal_GetIoVaild(EN_PASSENGER_DOOR_LOCK_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DLockState,PA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,PA_DOOR_AND_LOCK_ST_MASK)));/*����ʻ����״̬*/
	((Hal_GetIoVaild(EN_RL_DOOR_LOCK_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DLockState,LR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,LR_DOOR_AND_LOCK_ST_MASK)));/*�������״̬*/
	((Hal_GetIoVaild(EN_RR_DOOR_LOCK_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DLockState,RR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,RR_DOOR_AND_LOCK_ST_MASK)));/*�Һ�����״̬*/
	//((Hal_GetIoVaild(EN_TRUNK_RELEASE_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DLockState,BA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,BA_DOOR_AND_LOCK_ST_MASK)));/*��������״̬*/

	/*��״̬*/
	((Hal_ADCGetCheckStPtr()->DriverDoorOpenSta == D_AD_DriveDoorSta_OPEN)?(DLockSetStateMask(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK)));/*����ʻ��״̬*/
	((Hal_GetIoVaild(EN_PASSENGER_DOOR_AJAR_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DoorState,PA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,PA_DOOR_AND_LOCK_ST_MASK)));/*����ʻ��״̬*/
	((Hal_GetIoVaild(EN_RL_DOOR_AJAR_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DoorState,LR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,LR_DOOR_AND_LOCK_ST_MASK)));/*�����״̬*/
	((Hal_GetIoVaild(EN_RR_DOOR_AJAR_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DoorState,RR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,RR_DOOR_AND_LOCK_ST_MASK)));/*�Һ���״̬*/
	((Hal_GetIoVaild(EN_TRUNK_AJAR_SW) == TRUE)?(DLockSetStateMask(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK)));/*�Һ���״̬*/


	//LightCtrlStManage.CurrDriverLockSw = ((Hal_GetIoVaild(EN_DRIVER_DOOR_LOCK_SW) == TRUE)?1:0);
	LightCtrlStManage.DR_AJAR = ((Hal_ADCGetCheckStPtr()->DriverDoorOpenSta == D_AD_DriveDoorSta_CLOSE)?1:0);
	LightCtrlStManage.KEY_IN = ((Hal_GetIoVaild(EN_KEY_IN_SW) == TRUE)?1:0);
	LightCtrlStManage.TrigRKEOpenWin=0;
	LightCtrlStManage.PowerStChanged = 0;

	LightCtrlStManage.PowerMode = PKS_GetCurRunSta();


	LightCtrlStManage.CurrRkeOptCmd =  RKE_GetOptInd();
	//LightCtrlStManage.PeKeyPosState = PE_KEY_POS_UNKNOW;
	//LightCtrlStManage.PeKeylockSig = 0;
	//LightCtrlStManage.PeKeyUnlockSig = 0;
	if(Hal_ADCGetCheckStPtr()->CentrolLockUnlockSW == D_AD_CentrolLockUnlock_Unlock)
	{
		LightCtrlStManage.CentralLockKeySig = 1;
	}
	else if(Hal_ADCGetCheckStPtr()->CentrolLockUnlockSW == D_AD_CentrolLockUnlock_Lock)
	{
		LightCtrlStManage.CentralLockKeySig = 2;
	}
	else
	{
		LightCtrlStManage.CentralLockKeySig = 0;
	}
	LightCtrlStManage.IbcmSetAlarmSt = 0;
	LightCtrlStManage.TrunkSetAlarmSt =0;


	if(((Hal_GetIoVaild(EN_TRUNK_RELEASE_SW) == TRUE)?1:0) != CurrTrunkKeySig)
	{
		CurrTrunkKeySig=((Hal_GetIoVaild(EN_TRUNK_RELEASE_SW) == TRUE)?1:0);
		LightCtrlStManage.TrunkKeySig = CurrTrunkKeySig;
		UpPeps1StInfo.PEPS1_StTrunkExtSW = CurrTrunkKeySig;
		Hal_CanBcmUpdateInfo(EN_CAN_MSG_PEPS_1,(INT8U*)&UpPeps1StInfo,sizeof(UpPeps1StInfo));
	}
	
	
	//��ƿ��ص�λ�ж�
	if(D_VehExLampSwTypePrm_Hard == LightCtrlStManage.VehExLampSwTypePrm)
	{
		if(LightCtrlStManage.LowBeamSwFailure)//��ƿ��ع���
		{
			if((IGNState_ON <= LightCtrlStManage.PowerMode) && (D_ExlEnAutoLightPrm_Disable == LightCtrlStManage.ExlEnAutoLightPrm))
			{
				LightCtrlStManage.LowBeamSw = 1U;
			}
			if((IGNState_ON <= LightCtrlStManage.PowerMode) && (D_ExlEnAutoLightPrm_Enable == LightCtrlStManage.ExlEnAutoLightPrm))
			{
				LightCtrlStManage.AutoSw = 1U;
			}
		}
		else
		{
			
			(D_AD_HeadLightSW_PosLamp == Hal_ADCGetCheckStPtr()->HeadLightSW)?(LightCtrlStManage.PositionSw = 1U):(LightCtrlStManage.PositionSw = 0U);
			(D_AD_HeadLightSW_AutoLamp == Hal_ADCGetCheckStPtr()->HeadLightSW )?(LightCtrlStManage.AutoSw = 1U):(LightCtrlStManage.AutoSw = 0U);
			(D_AD_HeadLightSW_LowBeam == Hal_ADCGetCheckStPtr()->HeadLightSW )?(LightCtrlStManage.LowBeamSw = 1U):(LightCtrlStManage.LowBeamSw = 0U);

			if(D_AD_FogLampSw_FrontFog == Hal_ADCGetCheckStPtr()->FOG_LAMP_SW)//ģ�������ǰ��ƿ���
			{
				//
				//if(FALSE == LightCtrlStManage.PreFogLamp_Front_SW)
				{
					LightCtrlStManage.FogLamp_Front_SW = 1U;//ÿ�������س�����ת
					LightCtrlStManage.PreFogLamp_Front_SW = TRUE;

				}
			}
			else
			{

				LightCtrlStManage.FogLamp_Front_SW = 0U;
			}


			if(D_AD_FogLampSw_RearFog == Hal_ADCGetCheckStPtr()->FOG_LAMP_SW)//ģ�����������ƿ���
			{

				LightCtrlStManage.FogLamp_Rear_SW = 1U;//ÿ�������س�����ת
				LightCtrlStManage.PreFogLamp_Rear_SW = TRUE;
			}
			else
			{
				LightCtrlStManage.FogLamp_Rear_SW = 0U;//ÿ�������س�����ת
			}
		
		}
	}
	else if(D_VehExLampSwTypePrm_CAN == LightCtrlStManage.VehExLampSwTypePrm)
	{
		if(1U == CP4_St_Available)
		{
			if(2U == CP4_S_ExLampCommand)
			{
				LightCtrlStManage.PositionSw = 1U;
			}
			else if(4U	== CP4_S_ExLampCommand)
			{
				LightCtrlStManage.LowBeamSw = 1U;
			}
			else if(3U == CP4_S_ExLampCommand)
			{
				LightCtrlStManage.AutoSw = 1U;
			}
			else
			{
				LightCtrlStManage.AutoSw = 0U;
				LightCtrlStManage.LowBeamSw = 0U;
				LightCtrlStManage.PositionSw = 0U;
			}
			if(1U == CP4_S_FrontFogLamp)
			{
				 LightCtrlStManage.FogLamp_Front_SW = 1U;//����ҲӦ���������ش����ź�2019��12��12��10:37:44
			}		
			else
			{
				LightCtrlStManage.FogLamp_Front_SW = 0U;
			}
			if(1U == CP4_S_RearFogLamp)
			{
				 LightCtrlStManage.FogLamp_Rear_SW = 1U;//����ҲӦ���������ش����ź�2019��12��12��10:37:44
			}		
			else
			{
				LightCtrlStManage.FogLamp_Rear_SW = 0U;
			}
		}
		else if((1U == CP4Lost) || (1U == CP4_F_System))
		{
			if((IGNState_ON <= LightCtrlStManage.PowerMode) && (D_ExlEnAutoLightPrm_Disable == LightCtrlStManage.ExlEnAutoLightPrm))
			{
				LightCtrlStManage.LowBeamSw = 1U;
			}
			if((IGNState_ON <= LightCtrlStManage.PowerMode) && (D_ExlEnAutoLightPrm_Enable == LightCtrlStManage.ExlEnAutoLightPrm))
			{
				LightCtrlStManage.AutoSw = 1U;
			}
		}
		else
		{
			LightCtrlStManage.PositionSw = 0U;
			LightCtrlStManage.LowBeamSw = 0U;
			LightCtrlStManage.AutoSw = 0U;
		}

	}
	/*
	INT8U RSLinLost;
	INT8U RS_F_Communication;
	INT8U RS_F_Voltage;
	INT8U RS_LightSensor;
	INT8U RS_St_LampReq;
	LIN �����Զ��ƹ�������
	RLS �� LIN �ڵ㶪ʧ����ͨѶ����(RS_F_Communication==1)�����ѹ����(RS_F_Voltage==1)�����
	�⴫��������(RS_LightSensor==1)�����Զ��ƹ�������(RS_St_LampReq==1)��
	*/
	if((1U == RS_F_Lose) || (1U == RS_F_Communication) || (1U == RS_F_Voltage) || (1U == RS_LightSensor) || (1U == RS_St_LampReq))
	{
		LightCtrlStManage.LinForAutoLight = 1U;
	}
	else
	{
		LightCtrlStManage.LinForAutoLight = 0U; 
	}

	


	(TRUE == Hal_GetIoVaild(EN_BRAKE_PEDAL_SW))?(LightCtrlStManage.BRAKE_SW = TRUE):(LightCtrlStManage.BRAKE_SW = FALSE);

	
	if(D_AD_DirectionLamp_Left == Hal_ADCGetCheckStPtr()->DIRECTION_LAMP_SW)
	{
		LightCtrlStManage.TurnLightSwSts = enTurnSw_Left;
	}
	else if(D_AD_DirectionLamp_Right == Hal_ADCGetCheckStPtr()->DIRECTION_LAMP_SW)
	{
		LightCtrlStManage.TurnLightSwSts = enTurnSw_Right;
	}
	else
	{
		LightCtrlStManage.TurnLightSwSts = enTurnSw_Off;
	}

	LightCtrlStManage.HighFlashBeamSw = Hal_ADCGetCheckStPtr()->HighFalshBeamSW;


	LightCtrlStManage.IP_ILL_SET_01 = Hal_ADCGetCheckStPtr()->IP_ILLUMINATION_SETTING_01;
	LightCtrlStManage.IP_ILL_SEN_02 = Hal_ADCGetCheckStPtr()->IP_ILLUMINATION_SETTING_02;

	if(DescIOCtl_D500Input_Active == eIOCTL_ACTIVE)
	{
		((DescIOCtl_D500Input_DDLockSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK)));/*����ʻ����״̬*/
		((DescIOCtl_D500Input_PDLockSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DLockState,PA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,PA_DOOR_AND_LOCK_ST_MASK)));/*����ʻ����״̬*/
		((DescIOCtl_D500Input_RLDLockSw= eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DLockState,LR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,LR_DOOR_AND_LOCK_ST_MASK)));/*�������״̬*/
		((DescIOCtl_D500Input_RRDLockSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DLockState,RR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DLockState,RR_DOOR_AND_LOCK_ST_MASK)));/*�Һ�����״̬*/

		
		((DescIOCtl_D500Input_PDAjarSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DoorState,PA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,PA_DOOR_AND_LOCK_ST_MASK)));/*����ʻ��״̬*/
		((DescIOCtl_D500Input_RLDAjarSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DoorState,LR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,LR_DOOR_AND_LOCK_ST_MASK)));/*�����״̬*/
		((DescIOCtl_D500Input_RRDAjarSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DoorState,RR_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,RR_DOOR_AND_LOCK_ST_MASK)));/*�Һ���״̬*/
		((DescIOCtl_D500Input_TAjarSw == eIOCTL_ACTIVE)?(DLockSetStateMask(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK)):(DLockClrStateMask(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK)));/*�Һ���״̬*/

		LightCtrlStManage.KEY_IN= DescIOCtl_D500Input_KeyInSw;
		LightCtrlStManage.TrunkKeySig = DescIOCtl_D500Input_TReleaseSw;
		LightCtrlStManage.BRAKE_SW = DescIOCtl_D500Input_BrakePeadlSw;
	}

	
	if(DescIOCtl_D501Input_Active == eIOCTL_ACTIVE)
	{
		if(DescIOCtl_D501Input_DDAjarOpenSw == eIOCTL_ACTIVE)
		{
			DLockSetStateMask(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK);
		}
		else if(DescIOCtl_D501Input_DDAjarCloseSw == eIOCTL_ACTIVE)
		{
			DLockClrStateMask(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK);
		}

		if(DescIOCtl_D501Input_CenterUnlockSw == eIOCTL_ACTIVE)
		{
			LightCtrlStManage.CentralLockKeySig = 1; 
		}
		else if(DescIOCtl_D501Input_CenterLockSw == eIOCTL_ACTIVE)
		{
			LightCtrlStManage.CentralLockKeySig = 2; 
		}
		else
		{
			LightCtrlStManage.CentralLockKeySig = 0; 
		}
		LightCtrlStManage.PositionSw = DescIOCtl_D501Input_PosLampSw;
		LightCtrlStManage.AutoSw = DescIOCtl_D501Input_AutoLampSw;
		LightCtrlStManage.LowBeamSw = DescIOCtl_D501Input_LowBeamSw;

		if(DescIOCtl_D501Input_DirLeftSw ==1)
		{
			LightCtrlStManage.TurnLightSwSts = enTurnSw_Left;
		}
		else if(DescIOCtl_D501Input_DirRightSw == 2)
		{
			LightCtrlStManage.TurnLightSwSts = enTurnSw_Right;
		}

		if(DescIOCtl_D501Input_HighBeamSw== eIOCTL_ACTIVE)
		{
			LightCtrlStManage.HighFlashBeamSw = 1;
		}
		else if(DescIOCtl_D501Input_FlashBeamSw == eIOCTL_ACTIVE)
		{
			LightCtrlStManage.HighFlashBeamSw = 2;
		}
		
	}

	if(DescIOCtl_D502Input_Active == eIOCTL_ACTIVE)
	{
		if(DescIOCtl_D502Input_FrontFogSw == eIOCTL_ACTIVE)//ģ�������ǰ��ƿ���
		{
			//
			//if(FALSE == LightCtrlStManage.PreFogLamp_Front_SW)
			{
				LightCtrlStManage.FogLamp_Front_SW = 1U;//ÿ�������س�����ת
				LightCtrlStManage.PreFogLamp_Front_SW = TRUE;

			}
		}
		else
		{

			LightCtrlStManage.FogLamp_Front_SW = 0U;
		}


		if(DescIOCtl_D502Input_RearFogSw == eIOCTL_ACTIVE)//ģ�����������ƿ���
		{

			LightCtrlStManage.FogLamp_Rear_SW = 1U;//ÿ�������س�����ת
			LightCtrlStManage.PreFogLamp_Rear_SW = TRUE;
		}
		else
		{
			LightCtrlStManage.FogLamp_Rear_SW = 0U;//ÿ�������س�����ת
		}
	}
}
/*******************************************************************************
* �������ƣ�LightCtrl_IP_Illumination
* ��������������ƴ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void LightCtrl_IP_Illumination(void)
{

	//INT8U TargetLevel = 1U;//Ŀ���趨ֵ
	static INT8U CurrentLevel = 1U;//��ǰֵ
	static BOOL FirstEqual = FALSE;//��һ���������

	static	BOOL		IP_Illumination_DarkenFlag = FALSE;
	static	BOOL		IP_Illumination_BrightenFlag = FALSE;

	INT16U Scale=0, Scale1=0U, Scale2=0;//���ڼ���Ӳ�����زɼ������ݣ����б�������

	LightCtrlStManage.BatSavTimPrm = pEepInDoorCtrlParam_InLightFunc->BatSavTimPrm;
	LightCtrlStManage.ManufMaxTimPrm = pEepromVehicleModeCfg_InLightFunc->ManufMaxTimPrm;

	/*
	����ƽ��������� (1 || 2 || 3)
	1�� λ�õƿ�����Ч��
	2�� ����ƿ�����Ч��
	3�� Auto ������Ч�� LIN �����Զ��ƹ��������ҵ�Դ״̬�� OFF ����
	*/
	if((1U == LightCtrlStManage.PositionSw) || (1U == LightCtrlStManage.LowBeamSw) || \
		((1U == LightCtrlStManage.AutoSw) && (1U == LightCtrlStManage.LinForAutoLight) && (IGNState_OFF != LightCtrlStManage.PowerMode)))
	{
		IP_Illumination_BrightenFlag = TRUE;
		IP_Illumination_DarkenFlag = FALSE;
		LA1_St_Dimmer = 1U;
	}

	/*
	����ƽ��������� ((1 && 2 && 3) || 4)
	1�� λ�õƿ�����Ч��
	2�� ����ƿ�����Ч��
	3�� Auto ������Ч�� �� LIN �������Զ��ƹ����������Դ״̬ OFF ����
	4�� ��������ȫ���״̬��
	*/
	if(((0U == LightCtrlStManage.PositionSw)  && \
		(0U == LightCtrlStManage.LowBeamSw) && \
		((0U == LightCtrlStManage.AutoSw) || (0U == LightCtrlStManage.LinForAutoLight) || (IGNState_OFF == LightCtrlStManage.PowerMode))) || \
		(ALARM_ST_FULL_ARMED == GetAlarmMode()))
	{
		IP_Illumination_BrightenFlag = FALSE;
		IP_Illumination_DarkenFlag = TRUE;
		LA1_St_Dimmer = 0U;
	}

	if(D_VehExLampSwTypePrm_Hard == LightCtrlStManage.VehExLampSwTypePrm)
	{
		Scale1 = LightCtrlStManage.IP_ILL_SET_01*43/10;
		Scale2 = LightCtrlStManage.IP_ILL_SEN_02*43/10;
		if(((Scale1>=300u) && (Scale1<9400u))&&\
		((Scale2>=300u) && (Scale2<9400u))) /*����Ƶ���2������ѹֵ��Ч����0.3V-9.4V*/
		{
			Scale1 = 9400u - Scale1;
			Scale = (Scale1+Scale2) / 2;
			Scale = (Scale-300)*100/(9400-300); /*����ٷֱ�*/
			Scale = ((float)Scale / 6.25); /*�ٷֱȷֳ�16��*/
		}
		else
		{
			LightCtrlStManage.ICMS1_N_DimmSw = 7U;
		}
	#if 0
		Scale = (LightCtrlStManage.IP_ILL_SET_01 + LightCtrlStManage.IP_ILL_SEN_02) / 16U;
		LightCtrlStManage.ICMS1_N_DimmSw = (INT8U)(LightCtrlStManage.IP_ILL_SEN_02 / Scale);//����ı���ϵ����Ҫ���¼���2019��11��12��10:56:29
		if((LightCtrlStManage.IP_ILL_SET_01 > 4000U) || (LightCtrlStManage.IP_ILL_SET_01 < 10U))//��������·����ʱ
		{
			LightCtrlStManage.ICMS1_N_DimmSw = 7U;
		}
		if((LightCtrlStManage.IP_ILL_SEN_02 > 4000U) || (LightCtrlStManage.IP_ILL_SEN_02 < 10U))//��������·����ʱ
		{
			LightCtrlStManage.ICMS1_N_DimmSw = 7U;
		}
	#endif
	}
	else if(D_VehExLampSwTypePrm_CAN == LightCtrlStManage.VehExLampSwTypePrm)
	{
		if(CP4_St_Available)
		{
			LightCtrlStManage.ICMS1_N_DimmSw = CP4_N_DimmSw;
		}
		else
		{
			LightCtrlStManage.ICMS1_N_DimmSw = pEepInDoorCtrlParam_InLightFunc->MstDimmerLightnessPrm;
		}
	}
	if(IP_Illumination_BrightenFlag)
	{
		if(LightCtrlStManage.ICMS1_N_DimmSw > CurrentLevel)
		{
			Hal_IP_IlluminationStart(CurrentLevel);
			CurrentLevel += 1U;
			FirstEqual = FALSE;
		}
		else if(LightCtrlStManage.ICMS1_N_DimmSw < CurrentLevel)
		{
			Hal_IP_IlluminationStart(CurrentLevel);
			CurrentLevel -= 1U;
			FirstEqual = FALSE;
		}
		else
		{
			if(FirstEqual == FALSE)
			{
				Hal_IP_IlluminationStart(CurrentLevel);
				FirstEqual = TRUE;
			}
		}
		IPLightSts = enLight_On;
	}
	if(IP_Illumination_DarkenFlag)//����ӵ�ǰֵһֱ�������ܵ����Ƿ��б仯����ȷ��
	{
		if(1U < CurrentLevel)
		{
			Hal_IP_IlluminationStart(CurrentLevel);
			CurrentLevel -= 1U;
		}
		else
		{
			IP_Illumination_DarkenFlag = FALSE;
			Hal_IP_IlluminationStop();
			IPLightSts = enLight_Off;
		}
	}
}


/*******************************************************************************
* �������ƣ�LightCtrl_DoorStsChangedForBatterySaver
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForBatterySaver(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 6U; index ++)//��Դ������Ҫ�ж�����
			{
				if((D_AllDoor_DoorSts & Mask) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					DoorStsChangedFlag = enDoorSts_OneIsOpened;
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;

}



/*******************************************************************************
* LightCtrl_DoorLockStsChangedForBatterySaver
* ��������������״̬�ı���
* ��ڲ�������
* ���ڲ����������ı����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorLockChanged	    LightCtrl_DoorLockStsChangedForBatterySaver(void)
{
	static VehicleLock_t PreDoorLockSts = EN_VEH_LOCK_UNKOWN;
	enDoorLockChanged DoorLockStsChangedFlag = enDoorLock_NoChanged;

	if((PreDoorLockSts == EN_VEH_LOCK_CLOSE) && (Veh_GetLockSta() == EN_VEH_LOCK_OPEN))
	{
		DoorLockStsChangedFlag = enDoorLock_LockToUnlock;
	}	
	if((PreDoorLockSts == EN_VEH_LOCK_OPEN) && (Veh_GetLockSta() == EN_VEH_LOCK_CLOSE))
	{
		DoorLockStsChangedFlag = enDoorLock_UnlockToLock;
	}
	PreDoorLockSts = Veh_GetLockSta();
	
	return	DoorLockStsChangedFlag;
#if 0
	static	enLockSts	PreFrontLeft_DoorLockSts = enLock_Unlocked;
	enDoorLockChanged		DoorLockStsChangedFlag = enDoorLock_NoChanged;

	if(D_Driver_DoorLockSts != PreFrontLeft_DoorLockSts)
	{
		if((enLock_Locked == PreFrontLeft_DoorLockSts) && (enLock_Unlocked == D_Driver_DoorLockSts))
		{
			DoorLockStsChangedFlag = enDoorLock_LockToUnlock;
		}

		if((enLock_Unlocked == PreFrontLeft_DoorLockSts) && (enLock_Locked == D_Driver_DoorLockSts) && (AllDoorClose == TRUE))//�����г��Źر�added by michael 20161201
		{
			DoorLockStsChangedFlag = enDoorLock_UnlockToLock;
		}
		PreFrontLeft_DoorLockSts = (enLockSts)D_Driver_DoorLockSts;
	}
	return	DoorLockStsChangedFlag;
#endif

}

/*******************************************************************************
* �������ƣ�LightCtrl_LightSwChangedForBatterySaver
* ������������⵽��ƿ��ط����仯
* ��ڲ�������
* ���ڲ�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static BOOL 	LightCtrl_LightSwChangedForBatterySaver(void)
{
	BOOL temp = FALSE;
	static INT8U PrePositionSw = 0U;
	static INT8U PreAutoSw = 0U;
	static INT8U PreLowBeamSw = 0U;
	if(LightCtrlStManage.PositionSw != PrePositionSw)
	{
		 temp = TRUE;
		PrePositionSw = LightCtrlStManage.PositionSw;
	}
	if(LightCtrlStManage.AutoSw != PreAutoSw)
	{
		temp = TRUE;
		PreAutoSw = LightCtrlStManage.AutoSw;
	}
	if(LightCtrlStManage.LowBeamSw != PreLowBeamSw)
	{
		temp = TRUE;
		PreLowBeamSw = LightCtrlStManage.LowBeamSw;
	}
	return	temp;

}


/*******************************************************************************
* �������ƣ�CrashSwChangedForBatterySaver
* ������������ײ�źű仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged CrashSwChangedForBatterySaver(void)
{
	static BOOL  PreCrashSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreCrashSwChanged != LightCtrlStManage.TrigCrash)
	{
		if(PreCrashSwChanged)
		{
			temp = enSw_ValidToUnvalid;
		}
		else
		{
			temp = enSw_UnvalidToValid; 
		}
		PreCrashSwChanged = LightCtrlStManage.TrigCrash;
	}
	return temp;
}

/*******************************************************************************
* �������ƣ�LightCtrl_LightForBatterySaver
* �����������ƹ����ر���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static void	LightCtrl_LightForBatterySaver(void)
{
	static INT32U SetAlarmAfterTime = 0U;
	static INT32U PowerOffAfterTime = 0U;
	static INT32U WorkTime = 0U;

	if(!IsLightPwrVoltNormal())
	{
		LightCtrlStManage.BatterySaveFlg = FALSE;
		Hal_BatterySaverOff();
		return;
	}

	LightCtrlStManage.BatSavTimPrm = pEepInDoorCtrlParam_InLightFunc->BatSavTimPrm;
	LightCtrlStManage.ManufMaxTimPrm = pEepromVehicleModeCfg_InLightFunc->ManufMaxTimPrm;
	/*
	��Դ������Battery Saver������������ (1||2||3||4||5)
	1�� ��״̬�ɱ�����Ϊ������
	2�� ��Դ״̬���� ACC ���� ON ����
	3�� ��⵽��ײ�źţ��� SDM1_St_CrashIntensity �� 0 ��Ϊ�� 0����
	4�� ��⵽�����š�ǰ�ոǡ���������һ�Ŵӹرյ��򿪣�
	5�� ��ƿ��ط����仯��
	*/
	if((enDoorLock_LockToUnlock == LightCtrl_DoorLockStsChangedForBatterySaver()) ||\
		(IGNState_ACC == LightCtrlStManage.PowerMode) || (IGNState_ON == LightCtrlStManage.PowerMode) ||\
		(enSw_UnvalidToValid == CrashSwChangedForBatterySaver()) ||\
		(enDoorSts_OneIsOpened == LightCtrl_DoorStsChangedForBatterySaver()) ||\
		(TRUE == LightCtrl_LightSwChangedForBatterySaver())) // 
	{
		
		SetAlarmAfterTime = 0U;
		PowerOffAfterTime = 0U;
		LightCtrlStManage.BatterySaveFlg = TRUE;
	}
	if(LightCtrlStManage.BatterySaveFlg)
	{
		/*
		��Դ������Battery Saver���ر������� ��1||2��
		1�� ��������ȫ���״̬ 3 ���
		2�� ��Դ״̬���� OFF ����������InlBatSavTimPrm��ʱ��󣻣�Ĭ������ 15 ���ӣ�����ο� EEPROM ���ñ�
		����˵����
		1. ��Ե�Դ�����ر����� 2���ڵ�Դ��������ڼ䣬 ��Դ״̬����ת���� OFF ���� �������������Դ���������������¼�ʱ��
		2. ��Դ�������������ȼ����ڹرյ����ȼ���
		*/
		if(ALARM_ST_FULL_ARMED == GetAlarmMode())
		{
			if(++SetAlarmAfterTime >= D_Time_3S)
			{
				SetAlarmAfterTime = D_Time_3S;
				LightCtrlStManage.BatterySaveFlg = FALSE;
			}
		}
		if(IGNState_OFF == LightCtrlStManage.PowerMode)
		{
			
			if(++PowerOffAfterTime >= (LightCtrlStManage.BatSavTimPrm * 60 *1000 / D_LightCtrlTask_Period))
			{
				PowerOffAfterTime = (LightCtrlStManage.BatSavTimPrm * 60 *1000 / D_LightCtrlTask_Period);
				LightCtrlStManage.BatterySaveFlg = FALSE;
			}
		}
		
	}

	if(TRUE == LightCtrlStManage.BatterySaveFlg)
	{
	    if(enUserMode != LightCtrlStManage.VehOpModePrm)
    	{
    		if(++WorkTime >= (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period))
			{
				WorkTime = (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period);
				Hal_BatterySaverOff();
				LightCtrlStManage.BatterySaveFlg = FALSE;
				return;
			}
    	}
		Hal_BatterySaverOn();
	}
	else
	{
		WorkTime = 0U;
		SetAlarmAfterTime = 0U;
		Hal_BatterySaverOff();
	}

}

/*******************************************************************************
* �������ƣ�LightCtrl_DoorStsChangedForDomeLight
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForDomeLight(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 5; index ++)
			{
				if((enDoor_Close != (D_AllDoor_DoorSts & Mask)) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					if(0x10U == Mask)//���Ŵ�
					{
						DoorStsChangedFlag = enDoorSts_TrunkIsOpened;
					}
					else
					{
						DoorStsChangedFlag = enDoorSts_OneIsOpened;
					}
						
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;
}

/*******************************************************************************
* LightCtrl_DoorLockStsChangedForDomeLight
* ��������������״̬�ı���
* ��ڲ�������
* ���ڲ����������ı����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorLockChanged	    LightCtrl_DoorLockStsChangedForDomeLight(void)
{
	static	enLockSts	PreFrontLeft_DoorLockSts = enLock_Unlocked;
	enDoorLockChanged		DoorLockStsChangedFlag = enDoorLock_NoChanged;

	if(D_Driver_DoorLockSts != PreFrontLeft_DoorLockSts)
	{
		if((enLock_Locked == PreFrontLeft_DoorLockSts) && (enLock_Unlocked == D_Driver_DoorLockSts))
		{
			DoorLockStsChangedFlag = enDoorLock_LockToUnlock;
		}

		if((enLock_Unlocked == PreFrontLeft_DoorLockSts) && (enLock_Locked == D_Driver_DoorLockSts))
		{
			DoorLockStsChangedFlag = enDoorLock_UnlockToLock;
		}
		PreFrontLeft_DoorLockSts = (enLockSts)D_Driver_DoorLockSts;
	}

	return	DoorLockStsChangedFlag;

}

/*******************************************************************************
* �������ƣ�LightCtrl_SysPowerStsChangedForDomeLight
* ����������ϵͳ��Դ�л����
* ��ڲ�������
* ���ڲ�����ϵͳ��Դ�Ƿ��ɷ�OFF�е�OFF
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enIGNStsChanged 	LightCtrl_SysPowerStsChangedForDomeLight(void)
{
	static enIGN PreIGNSts = IGNState_OFF;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;

	if(LightCtrlStManage.PowerMode != PreIGNSts)
	{
		if(IGNState_OFF == LightCtrlStManage.PowerMode) // �ӷ�OFF�е�OFF
		{
			IGNStsChangedFlag = enIGNSts_NonOFFToOFF;
		}

		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((IGNState_OFF == PreIGNSts) || (IGNState_ACC == PreIGNSts))) // ��ON�����е�ON����(����ON)
		{
			IGNStsChangedFlag = enIGNSts_OFFACCToONCRACK;
		}
		PreIGNSts = LightCtrlStManage.PowerMode;
	}
	return	IGNStsChangedFlag;

}


/*******************************************************************************
* �������ƣ�CrashSwChangedForDomeLight
* ������������ײ�źű仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged CrashSwChangedForDomeLight(void)
{
	static BOOL  PreCrashSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreCrashSwChanged != LightCtrlStManage.TrigCrash)
	{
		if(PreCrashSwChanged)
		{
			temp = enSw_ValidToUnvalid;
		}
		else
		{
			temp = enSw_UnvalidToValid; 
		}
		PreCrashSwChanged = LightCtrlStManage.TrigCrash;
	}
	return temp;
}

/*******************************************************************************
* �������ƣ�LightCtrl_DomeLight
* ��������������ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_DomeLight(void)
{
	static	BOOL		DomeLightDimming_DarkenFlag = FALSE;
	static	BOOL		DomeLightDimming_BrightenFlag = FALSE;
	static	INT16U		DomeLightDimming_DarkenTimeCnt = 0;
	static	INT16U		DomeLightDimming_BrightenTimeCnt = 0;
	static	INT32U		DomeLightTurnOffDelayTimeCnt = 0;
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	enDoorLockChanged   DoorLockStsChangedFlag = enDoorLock_NoChanged;
	enIGNStsChanged		IGNStsChangedFlag = enIGNSts_NoChanged;
	static	BOOL		DomeLightTurnOffFlag = FALSE;
	static	BOOL		ChangeToAllDoorCloseStsFlag = FALSE;
	static	INT32U		DomeLightOnTimeCnt = 0;
	static  INT16U 		PowerOnDelayTime = 0;

	static	BOOL		DomeLightCrashFlag = FALSE;//��ײ������־

	static	BOOL		DomeLightCrashTimeOut_DarkenFlag = FALSE;
	static	INT32U      WorkTime = 0U;

	static	BOOL		DomeLightPowerToOFFFlag = FALSE;//��ײ�ڼ��Դģʽ��OFF��־
	
	enSwChanged CrashChangedFlag = enSw_NoChanged;
	DoorStsChangedFlag = LightCtrl_DoorStsChangedForDomeLight();
	DoorLockStsChangedFlag = LightCtrl_DoorLockStsChangedForDomeLight();
	IGNStsChangedFlag = LightCtrl_SysPowerStsChangedForDomeLight();
	CrashChangedFlag =  CrashSwChangedForDomeLight();

	//�ϵ��ӳ�1000ms
	if(++PowerOnDelayTime >= D_Time_1S)
	{
		PowerOnDelayTime = D_Time_1S;
	}
	else
	{
		return;
	}

	if(!IsLightPwrVoltNormal())//��Դģʽ������ֱ�ӷ���
	{
		Hal_DomeLightStop();
		return;
	}

	LightCtrlStManage.VehTrunkCtrlDomePrm = pEepInDoorCtrlParam_InLightFunc->VehTrunkCtrlDomePrm;
	LightCtrlStManage.BatSavTimPrm = pEepInDoorCtrlParam_InLightFunc->BatSavTimPrm;
	LightCtrlStManage.ManufMaxTimPrm = pEepromVehicleModeCfg_InLightFunc->ManufMaxTimPrm;
	
	// iBCM ���յ���ײ�źţ��� SDM1_St_CrashIntensity �� 0 ��Ϊ�� 0��������������
	if(enSw_UnvalidToValid == CrashChangedFlag)
	{
		//LightCtrlStManage.PreTrigCrash = LightCtrlStManage.TrigCrash;
		DomeLightDimming_DarkenFlag = FALSE;
		DomeLightDimming_BrightenFlag = FALSE;
		DomeLightDimming_DarkenTimeCnt = 0;
		DomeLightDimming_BrightenTimeCnt = 0;
		DomeLightTurnOffFlag = FALSE;
		DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
		ChangeToAllDoorCloseStsFlag = FALSE;
		WorkTime = 0U;
		if(DomeLightSts == enLight_Off)
		{
			//�����ǰ��OFF״̬�����µ���
			DomeLightOnTimeCnt = 0;
			DomeLightSts = enLight_On;
			Hal_DomeLightStart(100);
		}
		DomeLightCrashFlag = TRUE;//��ײ������־
		return;
	}
	else if(DomeLightCrashFlag)
	{
		// ���Ƴ�ʱ����
		if(enLight_On == DomeLightSts)
		{
			if(enUserMode != LightCtrlStManage.VehOpModePrm)//���û�ģʽ��ʱ
	    	{
	    		if(++WorkTime >= (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period))
				{
					WorkTime = (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period);
					DomeLightCrashTimeOut_DarkenFlag = TRUE;
					DomeLightSts = enLight_Off;
				}
	    	}
			else 
			{
				if(DomeLightOnTimeCnt ++ >= ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period)) // 8min
				{
					DomeLightOnTimeCnt = ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period);
					DomeLightSts = enLight_Off;
					//Hal_DomeLightStop();
					DomeLightCrashTimeOut_DarkenFlag = TRUE;
				}
			}
			if(enIGNSts_NonOFFToOFF == IGNStsChangedFlag)//�е�Դ״̬���᲻�������ײ�źţ�
			{
				DomeLightPowerToOFFFlag = TRUE;		
			}
			if((TRUE == DomeLightPowerToOFFFlag) && (enIGNSts_OFFToNonOFF == IGNStsChangedFlag))
			{
				DomeLightCrashTimeOut_DarkenFlag = TRUE;
				DomeLightPowerToOFFFlag = FALSE;
			}
		}
		if(TRUE == DomeLightCrashTimeOut_DarkenFlag)
		{
			DomeLightDimming_DarkenTimeCnt ++;
			if(DomeLightDimming_DarkenTimeCnt <= D_DomeLightDimmingOFF_Time)
			{
				if(0 == (DomeLightDimming_DarkenTimeCnt % 5)) // 2500ms ÿ50ms�ı�һ��
				{
					Hal_DomeLightStart((INT8U)(100 - (DomeLightDimming_DarkenTimeCnt / 5 * 2)));
				}
			}
			else
			{
				DomeLightCrashTimeOut_DarkenFlag = FALSE;
				
				DomeLightDimming_DarkenFlag = FALSE;
				DomeLightDimming_DarkenTimeCnt = 0;
				DomeLightTurnOffFlag = FALSE;
				DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
				ChangeToAllDoorCloseStsFlag = FALSE;
				DomeLightSts = enLight_Off;
				Hal_DomeLightStop();

				DomeLightCrashFlag = FALSE;//��ײ������־
				DomeLightOnTimeCnt = 0U;
				WorkTime = 0U;
			}
		}	
		return;
	}

	//LightCtrlStManage.PreTrigCrash =  LightCtrlStManage.TrigCrash;

	

	// ���Ƴ�ʱ����
	if(enLight_On == DomeLightSts)
	{
		if(enUserMode != LightCtrlStManage.VehOpModePrm)//���û�ģʽ��ʱ
    	{
    		if(++WorkTime >= (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period))
			{
				WorkTime = (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period);
				DomeLightTurnOffFlag = TRUE;
			}
    	}
		else 
		{
			if(++DomeLightOnTimeCnt  >= ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period)) //
			{
				DomeLightOnTimeCnt = ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period);
				DomeLightTurnOffFlag = TRUE;
			}
		}
		if((enDoorSts_OneIsOpened == DoorStsChangedFlag) || ((1U == LightCtrlStManage.VehTrunkCtrlDomePrm) && (enDoorSts_TrunkIsOpened == DoorStsChangedFlag)))//5. ���š������������ű��ִ򿪣����Ƶ��� InlBatSavTimPrm-30S ���𡣣�InlBatSavTimPrm Ĭ������Ϊ 15 ���ӣ��� ���Ƶ�����ʱʱ���ڣ��ټ�⵽���Ŵ򿪶��������¼�ʱ��
		{
			//DomeLightOnTimeCnt = 0U;
		}
	}
	else
	{
		DomeLightOnTimeCnt = 0;
		DomeLightTurnOffFlag = FALSE;
	}

	// Normal Control
	switch(DomeLightSts)
	{
		case	enLight_Off:
			/*
			���ƽ��������� ��1||2||3��
			1. ˾������״̬�ɱ�����Ϊ������
			2. ���Ż���������������ɹرձ�Ϊ�򿪣�
			3. ��Դ״̬�� ACC ���� ON ��ת���� OFF ����
			*/
			if( (enDoorSts_OneIsOpened == DoorStsChangedFlag) || \
				((1U == LightCtrlStManage.VehTrunkCtrlDomePrm) && (enDoorSts_TrunkIsOpened == DoorStsChangedFlag))|| \
				(enDoorLock_LockToUnlock == DoorLockStsChangedFlag) || \
				(enIGNSts_NonOFFToOFF == IGNStsChangedFlag))
			{
				// ����һ���Ŵ� �� �����ɱ��������� �� ��OFF�е�OFF
				DomeLightDimming_BrightenFlag = TRUE;
			}

			if(TRUE == DomeLightDimming_BrightenFlag)
			{
				DomeLightDimming_BrightenTimeCnt ++;
				if(DomeLightDimming_BrightenTimeCnt <= D_DomeLightDimmingON_Time)
				{
					if(0 == (DomeLightDimming_BrightenTimeCnt % 3)) // 1500ms ÿ30ms�ı�һ��
					{
						Hal_DomeLightStart((INT8U)(DomeLightDimming_BrightenTimeCnt / 3 * 2));
					}
				}
				else
				{
					DomeLightDimming_BrightenFlag = FALSE;
					DomeLightDimming_BrightenTimeCnt = 0;
					DomeLightSts = enLight_On;
					//Output_DomeLightDutyCycleSet(100);
				}

				// ����ڽ�������,�رն��Ƶ���������,����Ϩ�𶥵� 20160928
				if( (enDoorLock_UnlockToLock == DoorLockStsChangedFlag) || \
						(enIGNSts_OFFACCToONCRACK == IGNStsChangedFlag) || \
						((IGNState_ON <= LightCtrlStManage.PowerMode) && (enDoorSts_AllClosed == DoorStsChangedFlag)) )
				{
					// �����ɽ��������� �� ON�����е�ON����(����ON)  �� ��ON�������һ���Źر�
					DomeLightDimming_BrightenFlag = FALSE;

					DomeLightSts = enLight_On;
					DomeLightDimming_DarkenFlag = TRUE; // ����ڽ�������,�رն��Ƶ���������,����Ϩ�𶥵� 20160928
					DomeLightDimming_DarkenTimeCnt = DomeLightDimming_BrightenTimeCnt; // �����ĵط���Ϩ��
					DomeLightDimming_BrightenTimeCnt = 0;
				}
			}
			break;

		case	enLight_On:
			if(enDoorSts_AllClosed == DoorStsChangedFlag) // ��Դ״̬���� OFF ���� ���š������������Ŵ򿪵�ȫ���رգ����ƽ���
			{
				ChangeToAllDoorCloseStsFlag = TRUE;
			}

			if((IGNState_OFF == LightCtrlStManage.PowerMode) && (TRUE == AllDoorClose)) // �����Źر�,��ʱ30S��Ϩ���ʱ
			{
				if(Hal_TimerDiffTs(DomeLightTurnOffDelayTimeCnt) >= D_DomeLightTurnOff_DelayTime)
				{
					DomeLightTurnOffFlag = TRUE;
				}
				if((enDoorLock_LockToUnlock == DoorLockStsChangedFlag) || ((enDoorSts_OneIsOpened == DoorStsChangedFlag) || \
					((1U == LightCtrlStManage.VehTrunkCtrlDomePrm) && (enDoorSts_TrunkIsOpened == DoorStsChangedFlag))))
				{
					DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
				}
			}
			else
			{
				DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
			}
			/*
			���ƽ��������� ��1||2||3||4||5��
			1. ����״̬�ɽ�����Ϊ���������ƽ���
			2. ��Դ״̬�� OFF ���� ���š�������ȫ�����ڹر�״̬�����ƽ��� 30 ����𡣣�30 ���ڽ�������1,2 ��һ�����ٴ����� �����Ȼ��������������¼�ʱ 30 �����
			3. ���š������Ŵ���ȫ���ر�״̬�� ��Դ״̬�� OFF �� ACC ���� ON �������ƽ���
			4. ��Դ״̬���� OFF ���� ���š������������Ŵ򿪵�ȫ���رգ����ƽ���
			5. ���š������������ű��ִ򿪣����Ƶ��� InlBatSavTimPrm-30S ���𡣣�InlBatSavTimPrm Ĭ������Ϊ 15 ���ӣ��� ���Ƶ�����ʱʱ���ڣ��ټ�⵽���Ŵ򿪶��������¼�ʱ��
			*/
			if( (enDoorLock_UnlockToLock == DoorLockStsChangedFlag) || \
				(enIGNSts_OFFACCToONCRACK == IGNStsChangedFlag) || \
				((TRUE == ChangeToAllDoorCloseStsFlag) && (IGNState_OFF != LightCtrlStManage.PowerMode))||\
					(TRUE == DomeLightTurnOffFlag) )
			{
				// �����ɽ��������� �� ON�����е�ON����(����ON) �� ��ʱ15S�صƱ�־ΪTRUE
				DomeLightDimming_DarkenFlag = TRUE;
				if(TRUE == DomeLightTurnOffFlag)
				{
					DomeLightTurnOffFlag = FALSE;
				}
				ChangeToAllDoorCloseStsFlag = FALSE;
			}

			if(TRUE == DomeLightDimming_DarkenFlag)
			{
				DomeLightDimming_DarkenTimeCnt ++;
				if(DomeLightDimming_DarkenTimeCnt <= D_DomeLightDimmingOFF_Time)
				{
					if(0 == (DomeLightDimming_DarkenTimeCnt % 5)) // 2500ms ÿ50ms�ı�һ��
					{
						Hal_DomeLightStart((INT8U)(100 - (DomeLightDimming_DarkenTimeCnt / 5 * 2)));
					}
				}
				else
				{
					DomeLightDimming_DarkenFlag = FALSE;
					DomeLightDimming_DarkenTimeCnt = 0;
					DomeLightTurnOffFlag = FALSE;
					DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
					ChangeToAllDoorCloseStsFlag = FALSE;
					DomeLightSts = enLight_Off;
					Hal_DomeLightStop();
				}

				// ����ڽ������,�������Ƶ���������,���𽥵������� 20160928
				if( (enDoorSts_OneIsOpened == DoorStsChangedFlag) || \
					((1U == LightCtrlStManage.VehTrunkCtrlDomePrm) && (enDoorSts_TrunkIsOpened == DoorStsChangedFlag)) || \
					(enDoorLock_LockToUnlock == DoorLockStsChangedFlag) || \
					(enIGNSts_NonOFFToOFF == IGNStsChangedFlag) )
				{
					// ����һ���Ŵ� �� �����ɱ��������� �� ��OFF�е�OFF
					DomeLightDimming_DarkenFlag = FALSE;
					DomeLightTurnOffFlag = FALSE;
					DomeLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
					ChangeToAllDoorCloseStsFlag = FALSE;

					DomeLightSts = enLight_Off;
					DomeLightDimming_BrightenFlag = TRUE; // ����ڽ������,�������Ƶ���������,���𽥵������� 20160928
					DomeLightDimming_BrightenTimeCnt = DomeLightDimming_DarkenTimeCnt; // �����ĵط��𽥼�������
					DomeLightDimming_DarkenTimeCnt = 0;
				}
			}

			break;

		default:

			break;
	}

}

/*******************************************************************************
* �������ƣ�LightCtrl_DoorStsChangedForDomeLight
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForDooeOpen(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 5; index ++)
			{
				if(((D_AllDoor_DoorSts & Mask) != enDoor_Close) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					if(0x10u == Mask)//���Ŵ�
					{
						DoorStsChangedFlag = enDoorSts_TrunkIsOpened;
					}
					else
					{
						DoorStsChangedFlag = enDoorSts_OneIsOpened;
					}
						
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;

}

/*******************************************************************************
* LightCtrl_DoorLockStsChangedForDoorOpen
* ��������������״̬�ı���
* ��ڲ�������
* ���ڲ����������ı����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorLockChanged	    LightCtrl_DoorLockStsChangedForDoorOpen(void)
{
	static	enLockSts	PreFrontLeft_DoorLockSts = enLock_Unlocked;
	enDoorLockChanged		DoorLockStsChangedFlag = enDoorLock_NoChanged;

	if(D_Driver_DoorLockSts != PreFrontLeft_DoorLockSts)
	{
		if((enLock_Locked == PreFrontLeft_DoorLockSts) && (enLock_Unlocked == D_Driver_DoorLockSts))
		{
			DoorLockStsChangedFlag = enDoorLock_LockToUnlock;
		}

		if((enLock_Unlocked == PreFrontLeft_DoorLockSts) && (enLock_Locked == D_Driver_DoorLockSts) && (AllDoorClose == TRUE))//�����г��Źر�added by michael 20161201
		{
			DoorLockStsChangedFlag = enDoorLock_UnlockToLock;
		}
		PreFrontLeft_DoorLockSts = (enLockSts)D_Driver_DoorLockSts;
	}

	return	DoorLockStsChangedFlag;

}

/*******************************************************************************
* LightCtrl_SysPowerStsChangedForDoorOpen
* ����������ϵͳ��Դ�л����
* ��ڲ�������
* ���ڲ�����ϵͳ��Դ�Ƿ��ɷ�OFF�е�OFF
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enIGNStsChanged 	LightCtrl_SysPowerStsChangedForDoorOpen(void)
{
	enIGN PreIGNSts = IGNState_OFF;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;

	if(LightCtrlStManage.PowerMode != PreIGNSts)
	{
		if(IGNState_OFF == LightCtrlStManage.PowerMode) // �ӷ�OFF�е�OFF
		{
			IGNStsChangedFlag = enIGNSts_NonOFFToOFF;
		}

		if((IGNState_ON <= LightCtrlStManage.PowerMode) && (IGNState_OFF == PreIGNSts)) // ��ON�����е�ON����(����ON)
		{
			IGNStsChangedFlag = enIGNSts_OFFToNonOFF;
		}
		PreIGNSts = LightCtrlStManage.PowerMode;
	}
	return	IGNStsChangedFlag;

}

/*******************************************************************************
* �������ƣ�LightCtrl_OpenDoorLight
* �������������������ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_OpenDoorLight(void)
{
	static	BOOL		OpenDoorLightDimming_DarkenFlag = FALSE;
	static	BOOL		OpenDoorLightDimming_BrightenFlag = FALSE;
	static	INT16U		OpenDoorLightDimming_DarkenTimeCnt = 0;
	static	INT16U		OpenDoorLightDimming_BrightenTimeCnt = 0;
	static	INT32U		OpenDoorLightTurnOffDelayTimeCnt = 0;
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	enDoorLockChanged   DoorLockStsChangedFlag = enDoorLock_NoChanged;
	enIGNStsChanged		IGNStsChangedFlag = enIGNSts_NoChanged;
	static	BOOL		OpenDoorLightTurnOffFlag = FALSE;
	static	BOOL		ChangeToAllDoorCloseStsFlag = FALSE;
	static	INT32U		OpenDoorLightOnTimeCnt = 0;
	static  INT16U 		PowerOnDelayTime = 0;
	static enTurnLightCtrlMode preTurnLightCtrlMode = enCtrlMode_Non;

	static	BOOL		PreSDM1_St_CrashIntensity = FALSE;//������ײ�ź���һ��״̬
	DoorStsChangedFlag = LightCtrl_DoorStsChangedForDooeOpen();
	DoorLockStsChangedFlag = LightCtrl_DoorLockStsChangedForDoorOpen();
	IGNStsChangedFlag = LightCtrl_SysPowerStsChangedForDoorOpen();

	static	INT32U WorkTime = 9U;
	INT8U AlarmState;

//#define DebugOpenDoorLight
#ifdef DebugOpenDoorLight
	LightCtrlStManage.VehEnDoorOpenLampPrm = 1;
#else

#endif

	LightCtrlStManage.VehEnDoorOpenLampPrm = pEepInDoorCtrlParam_InLightFunc->VehEnDoorOpenLampPrm;
	LightCtrlStManage.BatSavTimPrm = pEepInDoorCtrlParam_InLightFunc->BatSavTimPrm;
	LightCtrlStManage.ManufMaxTimPrm = pEepromVehicleModeCfg_InLightFunc->ManufMaxTimPrm;
	
	if(0U == LightCtrlStManage.VehEnDoorOpenLampPrm)//û�������ſ�������ֱ�ӷ���
	{
		return;
	}


	// �ſ������Ƴ�ʱ����
	if(enLight_On == OpenDoorLightSts)
	{
		if(enUserMode != LightCtrlStManage.VehOpModePrm)//���û�ģʽ��ʱ
    	{
    		if(++WorkTime >= (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period))
			{
				WorkTime = (LightCtrlStManage.ManufMaxTimPrm * 60 *1000 / D_LightCtrlTask_Period);
				OpenDoorLightTurnOffFlag = TRUE;
			}
    	}
		else
		{
			if(++OpenDoorLightOnTimeCnt  >= ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period)) //
			{
				OpenDoorLightOnTimeCnt = ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period);
				OpenDoorLightTurnOffFlag = TRUE;
			}
		}
		if((enDoorSts_OneIsOpened == DoorStsChangedFlag) || (enDoorSts_TrunkIsOpened == DoorStsChangedFlag))//2.
		{
			OpenDoorLightOnTimeCnt = 0U;
		}
	}
	else
	{
		OpenDoorLightOnTimeCnt = 0;
		OpenDoorLightTurnOffFlag = FALSE;
		WorkTime = 0U;
	}

	// Normal Control
	switch(OpenDoorLightSts)
	{
		case	enLight_Off:
			/*
			��Դ״̬���� OFF�� ACC ���� ON ���� ���ţ��������������������ɹرձ�Ϊ�򿪣����������ƽ�����
			*/
			if((enDoorSts_OneIsOpened == DoorStsChangedFlag) ||\
				(enDoorSts_TrunkIsOpened == DoorStsChangedFlag))
			{
				OpenDoorLightDimming_BrightenFlag = TRUE;
			}

			if(TRUE == OpenDoorLightDimming_BrightenFlag)
			{
				OpenDoorLightDimming_BrightenTimeCnt ++;
				if(OpenDoorLightDimming_BrightenTimeCnt <= D_DomeLightDimmingON_Time)
				{
					if(0 == (OpenDoorLightDimming_BrightenTimeCnt % 3)) // 1500ms ÿ30ms�ı�һ��
					{
						Hal_DoorOpenLightStart((INT8U)(OpenDoorLightDimming_BrightenTimeCnt / 3 * 2));
					}
				}
				else
				{
					OpenDoorLightDimming_BrightenFlag = FALSE;
					OpenDoorLightDimming_BrightenTimeCnt = 0;
					OpenDoorLightSts = enLight_On;
					OpenDoorLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
				}
			}
			break;

		case	enLight_On:
			if(enDoorSts_AllClosed == DoorStsChangedFlag) // �ſ��������ڿ���״̬, ���Ŵ򿪵������Źرձ仯,��ʱ8s��Ϩ��
			{
				ChangeToAllDoorCloseStsFlag = TRUE;
			}

			if((TRUE == ChangeToAllDoorCloseStsFlag) && (TRUE == AllDoorClose)) // �����Źر�,��ʱ8S��Ϩ���ʱ
			{
				// 1. ϵͳ��Դ�ڷ�ON, ����û�б���, �ر����һ�ȳ���, �ſ���������ʱ8SϨ��
				// 2. ϵͳ��Դ��ON, �ر����һ�ȳ���,�ſ�������Ϩ��
				// 3. ����ȫ���رգ�����״̬�ӽ�����Ϊ����������Ϩ��
				if(Hal_TimerDiffTs(OpenDoorLightTurnOffDelayTimeCnt) >= D_OpenDoorLightTurnOff_DelayTime)
				{
					OpenDoorLightTurnOffFlag = TRUE;
					ChangeToAllDoorCloseStsFlag = FALSE;
				}
			}
			else
			{
				ChangeToAllDoorCloseStsFlag = FALSE;
				OpenDoorLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
			}
			
			if((ALARM_ST_FULL_ARMED == GetAlarmMode()) || \
				(ALRAM_ST_PARTIAL_ARMED == GetAlarmMode()) || \
				(enIGNSts_OFFToNonOFF == IGNStsChangedFlag) || \
				(TRUE == OpenDoorLightTurnOffFlag) )
			{
				// �����ɽ��������� �� ON�����е�ON����(����ON) �� ��ʱ15S�صƱ�־ΪTRUE
				OpenDoorLightDimming_DarkenFlag = TRUE;
				if(TRUE == OpenDoorLightTurnOffFlag)
				{
					OpenDoorLightTurnOffFlag = FALSE;
				}
			}

			if(TRUE == OpenDoorLightDimming_DarkenFlag)
			{
				OpenDoorLightDimming_DarkenTimeCnt ++;
				if(OpenDoorLightDimming_DarkenTimeCnt <= D_DomeLightDimmingOFF_Time)
				{
					if(0 == (OpenDoorLightDimming_DarkenTimeCnt % 5)) // 2500ms ÿ50ms�ı�һ��
					{
						Hal_DoorOpenLightStart((INT8U)(100 - (OpenDoorLightDimming_DarkenTimeCnt / 5 * 2)));
					}
				}
				else
				{
					OpenDoorLightDimming_DarkenFlag = FALSE;
					OpenDoorLightDimming_DarkenTimeCnt = 0;
					OpenDoorLightTurnOffFlag = FALSE;
					OpenDoorLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
					ChangeToAllDoorCloseStsFlag = FALSE;
					OpenDoorLightSts = enLight_Off;
					Hal_DoorOpenLightStop();
				}

				// ����ڽ������,�������Ƶ���������,���𽥵����ſ����� 
				if((enDoorSts_OneIsOpened == DoorStsChangedFlag) || (enDoorSts_TrunkIsOpened == DoorStsChangedFlag))
				{
					// ����һ���Ŵ� �� �����ɱ��������� �� ��OFF�е�OFF
					OpenDoorLightDimming_DarkenFlag = FALSE;
					OpenDoorLightTurnOffFlag = FALSE;
					OpenDoorLightTurnOffDelayTimeCnt = D_HAL_GET_CUR_MS_TS();
					ChangeToAllDoorCloseStsFlag = FALSE;

					OpenDoorLightSts = enLight_Off;
					OpenDoorLightDimming_BrightenFlag = TRUE; // ����ڽ������,�������Ƶ���������,���𽥵����ſ�����
					OpenDoorLightDimming_BrightenTimeCnt = OpenDoorLightDimming_DarkenTimeCnt; // �����ĵط��𽥼�������
					OpenDoorLightDimming_DarkenTimeCnt = 0;
				}
			}

			break;

		default:

			break;
	}

}

/*******************************************************************************
* �������ƣ�LightCtrl_AmbienceLight
* ������������Χ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��AmbienceLightSts
*******************************************************************************/
void LightCtrl_AmbienceLight(void)
{
  INT8U AUDIO11_St_AmbienceSet = 0U;
  INT8U AUDIO11_St_Available = 0U;
  INT8U vehEnAmbienceLampsPrm = 0U;
  INT8U AUDIO11_St_AmbienceLightnessSet = 0U;
  INT8U MstAmbiencePrm = 0U;//��Χ�ƿ�������
  INT8U	MstEnAmbienceSetPrm = 0U;//������������ʹ��
  INT8U	MstAmbienceLightnessSetPrm = 0U;//��Χ����������
  INT8U	MstEnAmbienceLightnessPrm = 0U;//������������ʹ��

  AUDIO11_St_AmbienceSet = Audio110x37CInfo.AUDIO11_StAmbienceSet;
  AUDIO11_St_Available = Audio110x37CInfo.AUDIO11_StAvailable;
  
  AUDIO11_St_AmbienceLightnessSet = Audio110x37CInfo.AUDIO11_StAmbienceLightnessSet;

//#define DebugAmbienceLight
#ifdef DebugAmbienceLight
	vehEnAmbienceLampsPrm = 1U;
  	MstAmbiencePrm = pEepInDoorCtrlParam_InLightFunc->MstAmbiencePrm;//��Χ�ƿ�������
  	MstEnAmbienceSetPrm = 1U;//������������ʹ��
  	MstAmbienceLightnessSetPrm = pEepInDoorCtrlParam_InLightFunc->MstAmbienceLightnessSetPrm;//��Χ����������
  	MstEnAmbienceLightnessPrm = 1U;//������������ʹ��
#else
	vehEnAmbienceLampsPrm = pEepInDoorCtrlParam_InLightFunc->VehEnAmbienceLampsPrm;
  	MstAmbiencePrm = pEepInDoorCtrlParam_InLightFunc->MstAmbiencePrm;//��Χ�ƿ�������
  	MstEnAmbienceSetPrm = pEepInDoorCtrlParam_InLightFunc->MstEnAmbienceSetPrm;//������������ʹ��
  	MstAmbienceLightnessSetPrm = pEepInDoorCtrlParam_InLightFunc->MstAmbienceLightnessSetPrm;//��Χ����������
  	MstEnAmbienceLightnessPrm = pEepInDoorCtrlParam_InLightFunc->MstEnAmbienceLightnessPrm;//������������ʹ��
#endif
 
	
	if(1U == MstEnAmbienceSetPrm)
	{
		if (AUDIO11_St_Available)
		{
			MstAmbiencePrm = AUDIO11_St_AmbienceSet;
		}
	}
	if(1U == MstEnAmbienceLightnessPrm)
	{
		if (AUDIO11_St_Available)
		{
			MstAmbienceLightnessSetPrm = AUDIO11_St_AmbienceLightnessSet;
		}
	}
  
  if((2U != MstAmbiencePrm) && (enLight_On == IPLightSts))
  {
		
	  if(1U == vehEnAmbienceLampsPrm)
	  {
		  Hal_AmbienceLightStart(MstAmbienceLightnessSetPrm);
	  }
	  if(2U == vehEnAmbienceLampsPrm)
	  {
		  ;//����LIN
	  }
  }
  else
  {
	  Hal_AmbienceLightStop();
  }
}



/*******************************************************************************
* �������ƣ�LightCtrl_PuddleLamp
* ����������ˮ�ӵƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void LightCtrl_PuddleLamp(void)
{
	INT8U PLG1_Lost = 0U;
	static INT32U PuddleLightOnTimeCnt = 0U;
	LightCtrlStManage.VehEnPLGPrm = pEepOutDoorCtrlParam_InLightFunc->VehEnPLGPrm;
	LightCtrlStManage.BatSavTimPrm = pEepInDoorCtrlParam_InLightFunc->BatSavTimPrm;
	if(((1U == LightCtrlStManage.VehEnPLGPrm) && (5U != PLG10x37AInfo.PLG1_StLiftgate)) ||\
		((0U == LightCtrlStManage.VehEnPLGPrm) && (TRUE == DLockIsOneMaskValid(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK))))
	{
		
		if(++PuddleLightOnTimeCnt >= ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period)) //
		{
			PuddleLightOnTimeCnt = ((LightCtrlStManage.BatSavTimPrm * 60 *1000 - 30*1000) / D_LightCtrlTask_Period);
			Hal_PuddleLightOff();
			LA1_St_TrunkLamp = 0U;
		}
		else
		{
			Hal_PuddleLightOn();
			LA1_St_TrunkLamp = 1U;
		}
	}
	else if(((1U == LightCtrlStManage.VehEnPLGPrm) && (5U == PLG10x37AInfo.PLG1_StLiftgate)) ||\
			((1U == LightCtrlStManage.VehEnPLGPrm) && (TRUE == Drv_CanChkMsgTimeOut(EN_CAN_MSG_PLG_1))) ||\
			((0U == LightCtrlStManage.VehEnPLGPrm) && (FALSE == DLockIsOneMaskValid(LightCtrlStManage.DoorState,BA_DOOR_AND_LOCK_ST_MASK))))
	{
		Hal_PuddleLightOff();
		PuddleLightOnTimeCnt = 0U;
		LA1_St_TrunkLamp = 0U;
	}
}

/*******************************************************************************
* �������ƣ�LightCtrl_SysPowerStsChangedForPRNDIndication
* ����������ϵͳ��Դ�л����
* ��ڲ�������
* ���ڲ�����ϵͳ��Դ�Ƿ��ɷ�OFF�е�OFF
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enIGNStsChanged 	LightCtrl_SysPowerStsChangedForPRNDIndication(void)
{
	static enIGN PreIGNSts = IGNState_OFF;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;

	if(LightCtrlStManage.PowerMode != PreIGNSts)
	{
		if(IGNState_OFF == LightCtrlStManage.PowerMode) // �ӷ�OFF�е�OFF
		{
			IGNStsChangedFlag = enIGNSts_NonOFFToOFF;
		}

		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((IGNState_OFF == PreIGNSts) || (IGNState_ACC == PreIGNSts))) // ��ON�����е�ON����(����ON)
		{
			IGNStsChangedFlag = enIGNSts_OFFACCToONCRACK;
		}
		PreIGNSts = LightCtrlStManage.PowerMode;
	}
	return	IGNStsChangedFlag;

}

/*******************************************************************************
* �������ƣ�LightCtrl_PRNDIndication
* ����������PRNDָʾ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void LightCtrl_PRNDIndication(void)
{
	static enIGN PrePDUState;

	static BOOL FirstOutUndefPosition = FALSE;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;
	IGNStsChangedFlag = LightCtrl_SysPowerStsChangedForPRNDIndication();

	BOOL TCMLost = FALSE;
	
#if 0
	LightCtrlStManage.VehManuOrAutoPrm = 0U;
	

#endif
	LightCtrlStManage.VehManuOrAutoPrm = pEepromBodyGuardAntitheft_InLightFunc->VehManuOrAutoPrm;
	if((3U != LightCtrlStManage.VehManuOrAutoPrm) && (enIGNSts_OFFACCToONCRACK == IGNStsChangedFlag))
	{
		Hal_PRNDLightStart(7U,TRUE);
		FirstOutUndefPosition = TRUE;//Ҫ���ȷ�������һ֡���κ󣬲����������������λָʾ
	}
	PrePDUState = LightCtrlStManage.PowerMode;
		
	
	if(FirstOutUndefPosition)
	{
		if(Hal_PRND2ONFirstOutIsCompleted())
		{
			if((3U != LightCtrlStManage.VehManuOrAutoPrm) && (LightCtrlStManage.PowerMode >= IGNState_ON ) && (TRUE == GWBTCM1Info.TCM1_FSLPFlag))
			{
				Hal_PRNDLightStart(GWBTCM1Info.TCM1_NSLP,FALSE);
			}
			else if((3U == LightCtrlStManage.VehManuOrAutoPrm) || (IGNState_ON > LightCtrlStManage.PowerMode) || (FALSE == GWBTCM1Info.TCM1_FSLPFlag) || (TRUE == TCMLost))
			{
				Hal_PRNDLightStop();
				if(IGNState_ON > LightCtrlStManage.PowerMode)//�����TCM�źŶ�ʧ�����ǵ�Դ״̬�仯�������������һ�β���//����ֻ�ǵ�Դ״̬�仯�������һ֡���Σ���ȷ��
				{
					FirstOutUndefPosition = FALSE;
				}

			}
		}

	}

}


/*******************************************************************************
* �������ƣ�LightCtrl_PositionLight
* ����������λ�õƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static void	LightCtrl_PositionLight(void)
{

	
	INT8U  LA1_St_PosLamp = 0U;
	INT8U  IBCM_St_PositionLampCommandFL = 0U;
	INT8U  IBCM_St_PositionLampCommandFR = 0U;

	INT8U ICMS1_S_ExLampCommand = 0U;
	INT8U ICMS1_St_ExLampAvailable = 0U;

	INT8U BCM3_S_ExLampCommand = 0U;

	BOOL DriverDoorCloseFlg = FALSE;

	


	INT8U LA1_St_PosLampL  = 0U;;
	INT8U LA1_St_PosLampR = 0U;

	static BOOL HoldModeRFlg = FALSE;
	static BOOL HoldModeLFlg = FALSE;

	
	
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Light_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_PosLight_Cmd)
		{
			PosLight_OutputReq = enOutputReq_On;
		}
		else
		{
			PosLight_OutputReq = enOutputReq_Off;
		}

		return;
	}
	*/
	// ��Դģʽ������
	/*if(TRUE == Normal)
	{
		PosLight_OutputReq = enOutputReq_Off;
		return;
	}*/
//#define DebugPositionLight

#ifdef DebugPositionLight
	LightCtrlStManage.ExlEnAutoLightPrm = D_ExlEnAutoLightPrm_Disable;
	LightCtrlStManage.VehExLampSwTypePrm = D_VehExLampSwTypePrm_Hard;
	LightCtrlStManage.ExlFPosLampsDiagtypePrm = D_ExlFPosLampsDiagtypePrm_HalogenLamp;
#else
	LightCtrlStManage.ExlEnAutoLightPrm = pEepOutDoorCtrlParam_InLightFunc->ExlEnAutoLightPrm;
	LightCtrlStManage.VehExLampSwTypePrm = pEepOutDoorCtrlParam_InLightFunc->VehExLampSwTypePrm;
	LightCtrlStManage.ExlFPosLampsDiagtypePrm = pEepOutDoorCtrlParam_InLightFunc->ExlFPosLampsDiagtypePrm;
#endif 
	
	/*
	λ�õƹ��ܿ��������� (1 || 2 || 3)
	1. λ�õƿ�����Ч��
	2. ����ƿ�����Ч��
	3. Auto������Ч�� LIN�����Զ��ƹ��������ҵ�Դ״̬��OFF����
	*/
	// Normal Control
	//3.1.1λ�õƹ���
	if((1U == LightCtrlStManage.PositionSw) || (1U == LightCtrlStManage.LowBeamSw) ||\
		((1U == LightCtrlStManage.AutoSw) && (1U == LightCtrlStManage.LinForAutoLight) && (IGNState_OFF != LightCtrlStManage.PowerMode)))
	{	
		//PosLight_OutputReq = enOutputReq_On;	
		PositionFunction = TRUE;
	}
	else
	{
		
		//PosLight_OutputReq = enOutputReq_Off;
		PositionFunction = FALSE;
	}
	//3.1.2פ���ƹ���
	if((FALSE == PositionFunction) && (IGNState_OFF == LightCtrlStManage.PowerMode) && \
		((enTurnSw_Left == LightCtrlStManage.TurnLightSwSts) || (enTurnSw_Right == LightCtrlStManage.TurnLightSwSts)))//
	{
		HoldFunction = TRUE;		
	}
	else
	{
		HoldFunction = FALSE;	
	}
	//3.1.3λ�õƿ���/�ر�
	if(TRUE == PositionFunction)
	{
		LeftPosLight_OutputReq = enOutputReq_On;
		RightPosLight_OutputReq = enOutputReq_On;
		LicenseLight_OutputReq = enOutputReq_On;
	}	
	else if(TRUE == HoldFunction)
	{

		if(enTurnSw_Left == LightCtrlStManage.TurnLightSwSts)
		{
			LeftPosLight_OutputReq = enOutputReq_On;
			RightPosLight_OutputReq = enOutputReq_Off;//Ԥ����λ�õƹ��ܵ�פ���ƹ��� û�йر�����һ��
		}
		else
		{
			RightPosLight_OutputReq = enOutputReq_On;
			LeftPosLight_OutputReq = enOutputReq_Off;//Ԥ����λ�õƹ��ܵ�פ���ƹ��� û�йر�����һ��
		}
	}
	else
	{
		LeftPosLight_OutputReq = enOutputReq_Off;
		RightPosLight_OutputReq = enOutputReq_Off;

		LicenseLight_OutputReq = enOutputReq_Off;

	}

	
	//3.1.4 λ�õ�δ�������߼�����
	/*
	λ�õ�δ�����ѿ��������� (1 && 2 && 3)
	1. ��Դ״̬OFF��
	2. λ�õƹ��ܿ�������פ���ƹ��ܿ�����
	3. �����Ŵ��ڴ�״̬��
	*/
	if((IGNState_OFF == LightCtrlStManage.PowerMode) && ((TRUE == PositionFunction) || (TRUE == PositionFunction)) && \
		(TRUE == DLockIsOneMaskValid(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK)))//λ�õ�δ�����ѿ�ʼ����
	{
		BCM3_W_PosLightNotClose = 1U;

	}
	else
	{
		BCM3_W_PosLightNotClose = 0U;
	}
}

static void NearLightProcess(void)
{
	/*3.2��λ�õƴ����������Ѿ������˴�ƿ�����Ч����/�Զ��ƹ�����*/

	/*3.2.1λ�õƹ���
	����ƿ��ع��ܿ��������� (1 && 2)
	1. ��Դ״̬ ON��
	2. ����ƿ�����Ч��

	Ѱ�������Ľ����
	*/
	if(((IGNState_ON == LightCtrlStManage.PowerMode) && (1U == LightCtrlStManage.LowBeamSw)) || SearchCarNearLightFunction)
	{
		NearLightFunction = TRUE;
	}
	else
	{
		NearLightFunction = FALSE;
	}
}

static void AutoLightProcess(void)
{
	/*3.2.2�Զ����߼�����
	Auto������ƹ��ܿ��������� (1 && 2 && 3 && 4)
	1. �������������⴫����(ExlEnAutoLightPrm==1)��
	2. ��Դ״̬ON����
	3. Auto������Ч��
	4. LIN�����Զ��ƹ�������
	*/
	if((D_ExlEnAutoLightPrm_Enable == LightCtrlStManage.ExlEnAutoLightPrm) && (IGNState_ON == LightCtrlStManage.PowerMode) &&\
		(1U == LightCtrlStManage.AutoSw) && (1U == LightCtrlStManage.LinForAutoLight))
	{
		AutoLightFunction = TRUE;
	}
	else
	{
		AutoLightFunction = FALSE;
	}
}


/*******************************************************************************
* LightCtrl_DoorStsChangedForFollow
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForFollow(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 5; index ++)
			{
				if((enDoor_Close != (D_AllDoor_DoorSts & Mask)) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					if(0x10u == Mask)//���Ŵ�
					{
						DoorStsChangedFlag = enDoorSts_TrunkIsOpened;
					}
					else
					{
						DoorStsChangedFlag = enDoorSts_OneIsOpened;
					}
						
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;

}


/*******************************************************************************
* LightCtrl_SysPowerStsChangedForFollow
* ����������ϵͳ��Դ�л����
* ��ڲ�������
* ���ڲ�����ϵͳ��Դ�Ƿ��ɷ�OFF�е�OFF
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enIGNStsChanged 	LightCtrl_SysPowerStsChangedForFollow(void)
{
	enIGN PreIGNSts = IGNState_OFF;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;

	if(LightCtrlStManage.PowerMode != PreIGNSts)
	{
		if(IGNState_OFF == LightCtrlStManage.PowerMode) // �ӷ�OFF�е�OFF
		{
			IGNStsChangedFlag = enIGNSts_NonOFFToOFF;
		}

		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((IGNState_OFF == PreIGNSts) || (IGNState_ACC == PreIGNSts))) // ��ON�����е�ON����(����ON)
		{
			IGNStsChangedFlag = enIGNSts_OFFACCToONCRACK;
		}
		PreIGNSts = LightCtrlStManage.PowerMode;
	}
	return	IGNStsChangedFlag;

}

static void FollowLightProcess(void)
{
	/*3.2.3 ���һؼ��߼�����
	�Զ����һؼҹ��ܿ��������� (1 && 2 && 3 && 4)
	1. ��������������������(ExlEnAutoLightPrm==1)��
	2. Auto������Ч��
	3. RLS��LIN�����Զ��ƹ�������
	4. ��Դ״̬�Ӵӷ�OFF����OFF��30���ڣ� �����Ŵ��ڴ�״̬��
	*/
	enDoorStsChanged 	FollowDoorChangedFlg = enDoorSts_NoChanged;
	enIGNStsChanged	 FollowIGNChangedFlg = enIGNSts_NoChanged;
	FollowDoorChangedFlg = LightCtrl_DoorStsChangedForFollow();
	FollowIGNChangedFlg = LightCtrl_SysPowerStsChangedForFollow();

	
	if((D_ExlEnAutoLightPrm_Enable == LightCtrlStManage.ExlEnAutoLightPrm) && (1U == LightCtrlStManage.AutoSw) &&\
		(1U == LightCtrlStManage.LinForAutoLight))
	{
		if(enIGNSts_NonOFFToOFF == FollowIGNChangedFlg)
		{
			FollowLightFunctionTimeStartFlg = TRUE;
		}
		if(FollowLightFunctionTimeStartFlg)
		{
			if(++FollowLightFunctionDoorOpenTime < D_FollowMeHomeDoorOpen_Time)
			{
				if(TRUE == DLockIsOneMaskValid(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK))
				{
					AutoFollowLightFunction = TRUE;

					FollowLightFunctionTimeStartFlg = FALSE;
					FollowLightFunctionDoorOpenTime = 0U;
				}
			}
			else
			{
				FollowLightFunctionTimeStartFlg = FALSE;
				FollowLightFunctionDoorOpenTime = 0U;
			}
		}
		
	}
	/*�Զ����һؼҹ��ܹر������� (1 || 2 || 3)
	1. ��Դ״̬�����仯��
	2. Auto������Ч��
	3. ���һؼҹ��ܴﵽ���õ�ʱ�䣻*/
	
	if(AutoFollowLightFunction)
	{
		if((IGNState_OFF != LightCtrlStManage.PowerMode) || (0U == LightCtrlStManage.AutoSw))
		{
			AutoFollowLightFunction = FALSE;
			FollowLightFunctionOnTime = 0U;
		}

		if((1U == LightCtrlStManage.MstEnFollowmeStepPrm) && (1U == MS1_St_Available))
		{
			FollowLightFunctionOnTimeMax = MS1_St_FollowMeTime * D_Time_10S;
		}
		else
		{
			FollowLightFunctionOnTimeMax = LightCtrlStManage.MstAutoFollowMePrm * D_Time_10S;
		}
		if(++FollowLightFunctionOnTime >= FollowLightFunctionOnTimeMax)
		{
			AutoFollowLightFunction = FALSE;
			FollowLightFunctionOnTime = 0U;
		}
		/*�ڰ��һؼҹ��ܿ���ʱ����⵽���Ż��ߺ���״̬���ط����仯����ʱ������*/
		if(enDoorSts_NoChanged != FollowDoorChangedFlg)
		{
			FollowLightFunctionOnTime = 0U;
		}
	}
		
	

	/*3.2.3 ���һؼ��߼�����
	�ֶ����һؼҹ��ܿ��������� (1 && 2)
	1. δ������������������(ExlEnAutoLightPrm == 0)
	2. ��Դ״̬�ӷ�OFF����OFF��30���ڣ� �����ƿ�������Ч��Ϊ��Ч��
	*/
	if(D_ExlEnAutoLightPrm_Disable == LightCtrlStManage.ExlEnAutoLightPrm)
	{
		if(enIGNSts_NonOFFToOFF == FollowIGNChangedFlg)
		{
			FollowLightFunctionTimeStartFlg = TRUE;
		}
		if(FollowLightFunctionTimeStartFlg)
		{
			if(++FollowLightFunctionDoorOpenTime < D_FollowMeHomeDoorOpen_Time)
			{
				if((D_HighFlashBeam_Flash == LightCtrlStManage.HighFlashBeamSw) && (D_HighFlashBeam_Flash != LightCtrlStManage.PreHighFlashBeamSw))
				{
					ManuFollowLightFunction = TRUE;
					LightCtrlStManage.PreHighFlashBeamSw = D_HighFlashBeam_Flash;

					FollowLightFunctionTimeStartFlg = FALSE;
					FollowLightFunctionDoorOpenTime = 0U;
				}
			}
			else
			{
				FollowLightFunctionTimeStartFlg = FALSE;
				FollowLightFunctionDoorOpenTime = 0U;
			}
		}
		
	}

	/*�ֶ����һؼҹ��ܿ��������� (1 && 2)
	1. δ������������������(ExlEnAutoLightPrm==0)
	2. ��Դ״̬�ӷ�OFF����OFF��30���ڣ� �����ƿ�������Ч��Ϊ��Ч��
	*/
	
	if(ManuFollowLightFunction)
	{
		if((IGNState_OFF != LightCtrlStManage.PowerMode) || ((D_HighFlashBeam_Flash == LightCtrlStManage.HighFlashBeamSw) && (D_HighFlashBeam_Flash != LightCtrlStManage.PreHighFlashBeamSw)))
		{
			ManuFollowLightFunction = FALSE;
			FollowLightFunctionOnTime = 0U;
			LightCtrlStManage.PreHighFlashBeamSw = D_HighFlashBeam_Flash;
		}
		if(++FollowLightFunctionDoorOpenTime >= (3 * D_Time_10S))
		{
			ManuFollowLightFunction = FALSE;
			FollowLightFunctionOnTime = 0U;
		}
		/*�ڰ��һؼҹ��ܿ���ʱ����⵽���Ż��ߺ���״̬���ط����仯����ʱ������*/
		if(enDoorSts_NoChanged != FollowDoorChangedFlg)
		{
			FollowLightFunctionOnTime = 0U;
		}
	}

	if((1U == AutoFollowLightFunction) || (1U == ManuFollowLightFunction))
	{
		BCM3_St_ComingHome = 1U;
	}
	else
	{
		BCM3_St_ComingHome = 0U;
	}

}
/*******************************************************************************
* �������ƣ�LightCtrl_DoorStsChangedForLeaveLight
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForLeaveLight(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 5; index ++)
			{
				if((enDoor_Close != (D_AllDoor_DoorSts & Mask)) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					if(0x10u == Mask)//���Ŵ�
					{
						DoorStsChangedFlag = enDoorSts_TrunkIsOpened;
					}
					else
					{
						DoorStsChangedFlag = enDoorSts_OneIsOpened;
					}
						
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;

}

static void LeaveLightProcess(void)
{
	enDoorStsChanged DoorStsChangedForLeaveLight = enDoorSts_NoChanged;
	DoorStsChangedForLeaveLight = LightCtrl_DoorStsChangedForLeaveLight();
	/*3.2.4 ��������߼�����
	������ҹ��ܿ��������� (1 && 2 && 3 && 4)
	1. ��������������������ExlEnAutoLightPrm==1����
	2. Auto ������Ч��
	3. �����������״̬��
	4. �յ��Ϸ�ң��Կ�׻�����Կ�׵Ľ�������� 500ms ���յ� RLS ���� RS_F_Communication==1 ��
	RS_F_Voltage==1 �� RS_LightSensor==1 �� RS_St_LampReq==1���� 500ms ʱ RLS �� LIN �����Զ���
	��������
	*/
	if((D_ExlEnAutoLightPrm_Enable == LightCtrlStManage.ExlEnAutoLightPrm) && (1U == LightCtrlStManage.AutoSw) && (2U == LightCtrlStManage.IbcmSetAlarmSt))
	{
		
		if(RKE_OPT_CMD_UNLOCK == LightCtrlStManage.CurrRkeOptCmd)
		{
			if(FALSE == AutoLeaveLightFunction)
			{
				if(++LeaveLightFunctionLinTime < D_WaittingLin_DelayTime)
				{
					if(1U == LightCtrlStManage.LinForAutoLight)
					{
						AutoLeaveLightFunction = TRUE;

						LeaveLightFunctionLinTime = 0U;
					}
				}
				else
				{
					LeaveLightFunctionLinTime = 0U;
				}	
				}
		}
	}
	/*������ҹ��ܹر������� (1 || 2 || 3 || 4 || 5)
	1. ������ҹ��ܼ����ʱ���ڼ�⵽�������½���ȫ�����
	2. ����һ�ţ����ż����ţ��ſ��仯��
	3. ��Դ״̬�仯��
	4. ��ƿ��ط����仯��
	5. ���һؼҹ��ܴﵽ���õ�ʱ�䣻*/
	if(AutoLeaveLightFunction)
	{
		if((1U == LightCtrlStManage.IbcmSetAlarmSt) ||(enDoorSts_NoChanged != DoorStsChangedForLeaveLight) ||\
			(IGNState_OFF != LightCtrlStManage.PowerMode) || (0U == LightCtrlStManage.AutoSw))
		{
			AutoLeaveLightFunction = FALSE;
			LeaveLightFunctionOnTime = 0U;
		}
		if((1U == LightCtrlStManage.MstEnLeaveMeSetPrm) && (1U == MS1_St_Available))
		{
			LeaveLightFunctionOnTimeMax = MS1_St_LeaveMeTime * D_Time_10S;
		}
		else
		{
			LeaveLightFunctionOnTimeMax = LightCtrlStManage.MstEnLeaveMeSetPrm * D_Time_10S;
		}
		if(++LeaveLightFunctionOnTime >= LeaveLightFunctionOnTimeMax)
		{
			AutoLeaveLightFunction = FALSE;
			LeaveLightFunctionOnTime = 0U;
		}
		BCM3_St_LeavingHome = 1U;
	}
	else
	{
		BCM3_St_LeavingHome = 0U;
	}
}

static 	void SpeedLightProcess(void)
{
	/*3.2.5 ����ά�ֽ���ƹ���
	����ά�ֽ���ƹ��ܿ��������� (1 && 2 && 3 && 4)
	1. ����ƿ�����Ч�� ��������RLS��Auto������Ч��RLS��LIN�����Զ��ƹ�������
	2. ����ƴ������״̬��
	3. ������Ч�Ҵ��ڵ���5��
	4. ��Դ״̬��ON���任ΪOFF/ACC��
	*/
	if(((1U == LightCtrlStManage.LowBeamSw) || ((1U == LightCtrlStManage.AutoSw) && (1U == LightCtrlStManage.LinForAutoLight))) && \
		(enOutputSts_On == LowBeam_OutputSts) && (5U <= LightCtrlStManage.CurrSp))
	{
		if(ForSpeedLightPowerState != LightCtrlStManage.PowerMode)
		{
			if((IGNState_ON == ForSpeedLightPowerState) && ((IGNState_OFF == LightCtrlStManage.PowerMode) || (IGNState_ACC == LightCtrlStManage.PowerMode)))
			{
				SpeedLightFunction = TRUE;//
			}
			ForSpeedLightPowerState = LightCtrlStManage.PowerMode;
		}
		
	}
	if(SpeedLightFunction)
	{
		if(((0U == LightCtrlStManage.LowBeamSw) && (D_ExlEnAutoLightPrm_Disable == LightCtrlStManage.ExlEnAutoLightPrm)) || \
			(0U == LightCtrlStManage.AutoSw) || (0U == LightCtrlStManage.LinForAutoLight) || (5U > LightCtrlStManage.CurrSp))
		{
			SpeedLightFunction = FALSE;//
		}
		if(ForSpeedLightPowerState != LightCtrlStManage.PowerMode)
		{
			if((IGNState_ON == LightCtrlStManage.PowerMode) && ((IGNState_OFF == ForSpeedLightPowerState) || (IGNState_ACC == ForSpeedLightPowerState)))
			{
				SpeedLightFunction = FALSE;//
			}
			ForSpeedLightPowerState = LightCtrlStManage.PowerMode;
		}
	}
}

static enHighFlashBeamSwChanged HighFlashBeamStsChangedForFar(void)
{
	static INT8U PreHighFlashBeamSw = D_HighFlashBeam_NULL;
	enHighFlashBeamSwChanged temp = enHighFlashBeamSw_NoChanged;
	if(PreHighFlashBeamSw != LightCtrlStManage.HighFlashBeamSw)
	{
		if((D_HighFlashBeam_NULL == PreHighFlashBeamSw) && (D_HighFlashBeam_Flash == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_NullToFlash;
		}
		if((D_HighFlashBeam_NULL == PreHighFlashBeamSw) && (D_HighFlashBeam_High == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_NullToHigh;
		}
		if((D_HighFlashBeam_Flash == PreHighFlashBeamSw) && (D_HighFlashBeam_NULL == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_FlashToNull;
		}
		if((D_HighFlashBeam_High == PreHighFlashBeamSw) && (D_HighFlashBeam_NULL == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_HighToNull;
		}
		PreHighFlashBeamSw = LightCtrlStManage.HighFlashBeamSw;
	}
	return temp;
}
static void FarLightProcess(void)
{
	enHighFlashBeamSwChanged HighFlashBeamSwChanged = enHighFlashBeamSw_NoChanged;
	HighFlashBeamSwChanged = HighFlashBeamStsChangedForFar();
	/*3.3.1 Զ����߼�����
	Զ��ƹ��ܿ��������� (1 && 2 && 3)
	1. ��Դ״̬ ON ����
	2. ��������������
	3. Զ�������ر�״̬�£� Զ��ƿ�������Ч��Ϊ��Ч��
	*/
	
	if((IGNState_ON == LightCtrlStManage.PowerMode) && \
		(enOutputSts_On == LowBeam_OutputSts) && \
		((enOutputSts_Off == HighBeam_OutputSts) && (enHighFlashBeamSw_NullToHigh == HighFlashBeamSwChanged)))
	{
		FarLightFunction = TRUE;
	}
	if(FarLightFunction)
	{
		if((IGNState_ON != LightCtrlStManage.PowerMode) || \
			(enOutputSts_Off == LowBeam_OutputSts) || \
			((enOutputSts_On == HighBeam_OutputSts) && (enHighFlashBeamSw_NullToHigh == HighFlashBeamSwChanged)) || \
			((enOutputSts_On == HighBeam_OutputSts) && (enHighFlashBeamSw_NullToFlash == HighFlashBeamSwChanged)) ||\
			(D_MstHMAPrm_Enable == LightCtrlStManage.MstHMAPrm))
		{
			FarLightFunction = FALSE;//
		}
	
	}
}

static void FlashLightProcess(void)
{
	/*3.3.2 �������߼�����
	�����ƹ��ܿ���������
	�����ƿ�����Ч��
	*/
	
	if(D_HighFlashBeam_Flash == LightCtrlStManage.HighFlashBeamSw)
	{
		FlashLightFunction = TRUE;
	}
	else
	{
		FlashLightFunction = FALSE;
	}
}
static enHighFlashBeamSwChanged HighFlashBeamStsChangedForHMA(void)
{
	static INT8U PreHighFlashBeamSw = D_HighFlashBeam_NULL;
	enHighFlashBeamSwChanged temp = enHighFlashBeamSw_NoChanged;
	if(PreHighFlashBeamSw != LightCtrlStManage.HighFlashBeamSw)
	{
		if((D_HighFlashBeam_NULL == PreHighFlashBeamSw) && (D_HighFlashBeam_Flash == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_NullToFlash;
		}
		if((D_HighFlashBeam_NULL == PreHighFlashBeamSw) && (D_HighFlashBeam_High == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_NullToHigh;
		}
		if((D_HighFlashBeam_Flash == PreHighFlashBeamSw) && (D_HighFlashBeam_NULL == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_FlashToNull;
		}
		if((D_HighFlashBeam_High == PreHighFlashBeamSw) && (D_HighFlashBeam_NULL == LightCtrlStManage.HighFlashBeamSw))
		{
			temp = enHighFlashBeamSw_HighToNull;
		}
		PreHighFlashBeamSw = LightCtrlStManage.HighFlashBeamSw;
	}
	return temp;
}

/*******************************************************************************
* LightCtrl_SysPowerStsChangedForHMA
* ����������ϵͳ��Դ�л����
* ��ڲ�������
* ���ڲ�����ϵͳ��Դ�Ƿ��ɷ�OFF�е�OFF
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enIGNStsChanged 	LightCtrl_SysPowerStsChangedForHMA(void)
{
	enIGN PreIGNSts = IGNState_OFF;
	enIGNStsChanged	 IGNStsChangedFlag = enIGNSts_NoChanged;

	if(LightCtrlStManage.PowerMode != PreIGNSts)
	{
		if(IGNState_OFF == LightCtrlStManage.PowerMode) // �ӷ�OFF�е�OFF
		{
			IGNStsChangedFlag = enIGNSts_NonOFFToOFF;
		}

		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((IGNState_OFF == PreIGNSts) || (IGNState_ACC == PreIGNSts))) // ��ON�����е�ON����(����ON)
		{
			IGNStsChangedFlag = enIGNSts_OFFACCToONCRACK;
		}
		PreIGNSts = LightCtrlStManage.PowerMode;
	}
	return	IGNStsChangedFlag;

}

static void HMALightProcess(void)
{
	/*3.3.2 �������߼�����
	�����ƹ��ܿ���������
	�����ƿ�����Ч��
	*/
	static BOOL HMAEnable = FALSE;
	static BOOL HighFlashBeam_HighValid = FALSE;
	static INT32U HighFlashBeam_HighTime = 0U;//Զ��ƿ��س��� 1.5s ���ϣ�





	enHighFlashBeamSwChanged HighFlashBeamSwChangedForHMA = enHighFlashBeamSw_NoChanged;
	enIGNStsChanged  IGNStsChangedForHMA = enIGNSts_NoChanged;
	IGNStsChangedForHMA = 	LightCtrl_SysPowerStsChangedForHMA();
	HighFlashBeamSwChangedForHMA = HighFlashBeamStsChangedForHMA();
	
	if(D_HighFlashBeam_High == LightCtrlStManage.HighFlashBeamSw)
	{
		if(++HighFlashBeam_HighTime >= D_Time_1Piont5S)
		{
			HighFlashBeam_HighTime = D_Time_1Piont5S;
			HighFlashBeam_HighValid = TRUE;
		}
	}
	else
	{
		HighFlashBeam_HighValid = FALSE;
	}
	

	if((D_MstHMAPrm_Enable == LightCtrlStManage.MstHMAPrm) && \
		((enIGNSts_OFFACCToONCRACK == IGNStsChangedForHMA) || \
		((FALSE == HMAEnable) && (IGNState_ON == LightCtrlStManage.PowerMode) && (TRUE == HighFlashBeam_HighValid))))
	{
		HMAEnable = TRUE;
		LA1_St_HMAAvailable = 1U;
	}
	if((D_MstHMAPrm_Enable == LightCtrlStManage.MstHMAPrm) && \
		((IGNState_ON != LightCtrlStManage.PowerMode) || \
		(enHighFlashBeamSw_NullToFlash == HighFlashBeamSwChangedForHMA) || \
		(enHighFlashBeamSw_NullToHigh == HighFlashBeamSwChangedForHMA)))
	{
		HMAEnable = FALSE;
		LA1_St_HMAAvailable = 0U;
	}

	if((FALSE == HMAEnable) && (1U == GWBDAC10x41BInfo.DAC1_StHighbeamReq))
	{
		HMALightFunction = TRUE;
		BCM3_St_HMA = 1U;
	}
	else
	{
		HMALightFunction = FALSE;
		BCM3_St_HMA = 0U;
	}
}



/*******************************************************************************
* �������ƣ�LightCtrl_Headlight
* ����������ǰ�յƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע����������ƺ�Զ���
*******************************************************************************/
void	LightCtrl_Headlight(void)
{

	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Light_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_LowBeam_Cmd)
		{
			LowBeam_OutputReq = enOutputReq_On;
		}
		else
		{
			LowBeam_OutputReq = enOutputReq_Off;
		}

		if(DescIOCtl_enLight_ON == DescIOCtl_HighBeam_Cmd)
		{
			HighBeam_OutputReq = enOutputReq_On;
		}
		else
		{
			HighBeam_OutputReq = enOutputReq_Off;
		}

		return;
	}
	*/
	// Battery Save
	/*
	if(TRUE == LightForBatterySaveFlg)
	{

		HighBeam_OutputReq = enOutputReq_Off;
		if(TRUE == IsLightPwrVoltHigh())
		{
			HighBeamProcFlg = TRUE;
		}
	}
	*/
#ifdef DebugHeadLight
		LightCtrlStManage.VehExLampSwTypePrm = D_VehExLampSwTypePrm_Hard;
		LightCtrlStManage.VehLowBeamTypePrm = D_VehLowBeamType_HalogenLamp;

		LightCtrlStManage.ExlEnAutoLightPrm = D_ExlEnAutoLightPrm_Disable;
		
		LightCtrlStManage.MstAutoFollowMePrm = D_MstAutoFollowMePrm_10S;
		LightCtrlStManage.MstEnFollowmeStepPrm = D_MstEnFollowmeStepPrm_Disable;
		LightCtrlStManage.MstLeaveMePrm = D_MstLeaveMePrm_10S;
		LightCtrlStManage.MstEnLeaveMeSetPrm = D_MstEnLeaveMeSetPrm_Disable;
		
		LightCtrlStManage.MstHMAPrm = D_MstHMAPrm_Disable;
		LightCtrlStManage.VehHighBeamTypePrm = D_VehHighBeamType_HalogenLamp;
#else
		LightCtrlStManage.VehExLampSwTypePrm = pEepOutDoorCtrlParam_InLightFunc->VehExLampSwTypePrm;
		LightCtrlStManage.VehLowBeamTypePrm = pEepOutDoorCtrlParam_InLightFunc->VehLowBeamTypePrm;
		LightCtrlStManage.ExlEnAutoLightPrm = pEepOutDoorCtrlParam_InLightFunc->ExlEnAutoLightPrm;
		LightCtrlStManage.MstAutoFollowMePrm = pEepOutDoorCtrlParam_InLightFunc->MstAutoFollowMePrm;
		LightCtrlStManage.MstEnFollowmeStepPrm = pEepOutDoorCtrlParam_InLightFunc->MstEnFollowmeStepPrm;
		LightCtrlStManage.MstLeaveMePrm = pEepOutDoorCtrlParam_InLightFunc->MstLeaveMePrm;
		LightCtrlStManage.MstEnLeaveMeSetPrm = pEepOutDoorCtrlParam_InLightFunc->MstEnLeaveMeSetPrm;

		LightCtrlStManage.MstHMAPrm = pEepOutDoorCtrlParam_InLightFunc->MstHMAPrm;
		LightCtrlStManage.VehHighBeamTypePrm = pEepOutDoorCtrlParam_InLightFunc->VehHighBeamTypePrm;
#endif 

	NearLightProcess();
	AutoLightProcess();
	FollowLightProcess();
	LeaveLightProcess();
	SpeedLightProcess();

	FarLightProcess();
	FlashLightProcess();
	HMALightProcess();

	
	if((TRUE == NearLightFunction) || \
		(TRUE == AutoLightFunction) || \
		(TRUE == AutoFollowLightFunction) || \
		(TRUE == AutoLeaveLightFunction) || \
		(TRUE == SpeedLightFunction))
	{
		LowBeam_OutputReq = enOutputReq_On;
		LA1_St_LowBeam = 1U;
	}
	else
	{
		LowBeam_OutputReq = enOutputReq_Off;
		LA1_St_LowBeam = 0U;
	}

	if((TRUE == FarLightFunction) || \
		(TRUE == FlashLightFunction) || \
		(TRUE == HMALightFunction))
	{
		HighBeam_OutputReq = enOutputReq_On;

	}
	else
	{
		HighBeam_OutputReq = enOutputReq_Off;

	}

}



/*******************************************************************************
* �������ƣ�FrontFogSwChangedForFogLight
* ����������ǰ��ƿ��ر仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged FrontFogSwChangedForFogLight(void)
{
	static BOOL  PreFrontFogSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreFrontFogSwChanged != LightCtrlStManage.FogLamp_Front_SW)
	{
		if(PreFrontFogSwChanged)
		{
			temp = enSw_ValidToUnvalid;
		}
		else
		{
			temp = enSw_UnvalidToValid; 
		}
		PreFrontFogSwChanged = LightCtrlStManage.FogLamp_Front_SW;
	}
	return temp;
}

/*******************************************************************************
* �������ƣ�LightCtrl_FrontFogLight
* ����������ǰ��ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��ǰ��ƿ����Ǵ��㿪��,����ʱ����Ӧ��״̬������ת
*******************************************************************************/
void	LightCtrl_FrontFogLight(void)
{
	static	BOOL	    FogLamp_Front_Sw_PressFlg = FALSE;
	static	enSwSts		Pre_FogLamp_Front_SwSts = enSw_Off;

	enSwChanged SwChangedForFrontFog =  enSw_NoChanged;
	SwChangedForFrontFog = FrontFogSwChangedForFogLight();


	
#define DebugFrontFog
#ifdef DebugFrontFog
	LightCtrlStManage.VehEnFrontFogLampPrm = 1U;
#else

#endif 
	if(0U == LightCtrlStManage.VehEnFrontFogLampPrm)
	{
		FogLamp_Front_OutputReq = enOutputReq_Off;
		return;
	}
	// Normal Control
	switch(FogLamp_Front_OutputSts)
	{
		case	enOutputSts_Off:
			// ��ON���� �� ǰ��ƿ����а��� �� ��λ�õƵ���״̬
			if((IGNState_ON <= LightCtrlStManage.PowerMode) && (enSw_UnvalidToValid == SwChangedForFrontFog) &&\
				((enOutputSts_On == LeftPosLight_OutputSts) || (enOutputSts_On == RightPosLight_OutputSts)))
			{
				//FogLamp_Front_Sw_PressFlg = TRUE;
				FogLamp_Front_OutputReq = enOutputReq_On;
			}

			break;

		case	enOutputSts_On:
			// IGN ON���� �� ǰ��ƿ����а��� �� λ�õ�Ϩ��
			if( (IGNState_ON > LightCtrlStManage.PowerMode) || \
			((enOutputSts_Off == LeftPosLight_OutputSts) && (enOutputSts_Off == RightPosLight_OutputSts)) || \
			(enSw_UnvalidToValid == SwChangedForFrontFog))
			{
				FogLamp_Front_OutputReq = enOutputReq_Off;
			}
			break;

		default:

			break;
	}

}


/*******************************************************************************
* �������ƣ�RearFogSwChangedForFogLight
* ��������������ƿ��ر仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged RearFogSwChangedForFogLight(void)
{
	static BOOL  PreRearFogSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreRearFogSwChanged != LightCtrlStManage.FogLamp_Rear_SW)
	{
		if(PreRearFogSwChanged)
		{
			temp = enSw_ValidToUnvalid;
		}
		else
		{
			temp = enSw_UnvalidToValid; 
		}
		PreRearFogSwChanged = LightCtrlStManage.FogLamp_Rear_SW;
	}
	return temp;
}

/*******************************************************************************
* �������ƣ�LightCtrl_RearFogLight
* ��������������ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע������ƿ����Ǵ��㿪��,����ʱ����Ӧ��״̬������ת
*******************************************************************************/
void	LightCtrl_RearFogLight(void)
{
	static	BOOL	    FogLamp_Rear_Sw_PressFlg = FALSE;
	static	enSwSts		Pre_FogLamp_Rear_SwSts = enSw_Off;

	enSwChanged SwChangedForRearFog =  enSw_NoChanged;
	SwChangedForRearFog = RearFogSwChangedForFogLight();

	// Normal Control
	switch(FogLamp_Rear_OutputSts)
	{
		case	enOutputSts_Off:
			// ��ON���� �� ����ƿ����а��� �� ��/Զ��Ƶ���״̬
			if(((IGNState_ON <= LightCtrlStManage.PowerMode) && (enSw_UnvalidToValid == SwChangedForRearFog) && \
			((enOutputSts_On == LowBeam_OutputSts) || (enOutputSts_On == FogLamp_Front_OutputSts))) || SearchCarRearFrogLampFunction)
			{
				FogLamp_Rear_Sw_PressFlg = FALSE;
				FogLamp_Rear_OutputReq = enOutputReq_On;
			}
			else // IGN ON����
			{
				FogLamp_Rear_Sw_PressFlg = FALSE;
			}
			break;

		case	enOutputSts_On:
			// IGN ON���� �� ����ƿ����а��� �� �����Զ���Ϩ��
			if(FALSE == SearchCarRearFrogLampFunction)
			{
				if( (IGNState_ON > LightCtrlStManage.PowerMode) || \
				(enSw_UnvalidToValid == SwChangedForRearFog) || \
				((enOutputSts_Off == LowBeam_OutputSts) && (enOutputSts_Off == FogLamp_Front_OutputSts)) )
				{
					FogLamp_Rear_Sw_PressFlg = FALSE;
					FogLamp_Rear_OutputReq = enOutputReq_Off;
				}
			}
			break;

		default:

			break;
	}

}


/*******************************************************************************
* �������ƣ�LightCtrl_FogLight
* ������������ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_FogLight(void)
{
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Fog_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_FFog_Cmd)
		{
			FogLamp_Front_OutputReq = enOutputReq_On;
		}
		else
		{
			FogLamp_Front_OutputReq = enOutputReq_Off;
		}

		if(DescIOCtl_enLight_ON == DescIOCtl_RFog_Cmd)
		{
			FogLamp_Rear_OutputReq = enOutputReq_On;
		}
		else
		{
			FogLamp_Rear_OutputReq = enOutputReq_Off;
		}

		return;
	}
	*/
	LightCtrl_FrontFogLight();
	LightCtrl_RearFogLight();
}

/*******************************************************************************
* �������ƣ�LightCtrl_TurnLightOnOrOffSet
* ����������ת�����������
* ��ڲ�����LightSts: ��Ҫ����ת��Ƶ�״̬; TurnLightSelect: ��Ҫ���õ�ת���
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_TurnLightOnOrOffSet(enOutputReqType OutputReq, enTurnLightSelect TurnLightSelect)
{
	switch(TurnLightSelect)
	{
		case	enTurnLight_Left:
			if(enOutputReq_On == OutputReq)
			{
				TurnLampSts_Left_OutputReq = enOutputReq_On;
			}
			else if(enOutputReq_Off == OutputReq)
			{
				TurnLampSts_Left_OutputReq = enOutputReq_Off;
			}
			else
			{}
			break;

		case	enTurnLight_Right:
			if(enOutputReq_On == OutputReq)
			{
				TurnLampSts_Right_OutputReq = enOutputReq_On;
			}
			else if(enOutputReq_Off == OutputReq)
			{
				TurnLampSts_Right_OutputReq = enOutputReq_Off;
			}
			else
			{}

			break;

		case	enTurnLight_LeftRight:
			if(enOutputReq_On == OutputReq)
			{
				TurnLampSts_Left_OutputReq = enOutputReq_On;
				TurnLampSts_Right_OutputReq = enOutputReq_On;
			}
			else if(enOutputReq_Off == OutputReq)
			{
				TurnLampSts_Left_OutputReq = enOutputReq_Off;
				TurnLampSts_Right_OutputReq = enOutputReq_Off;
			}
			else
			{}

			break;

		default:

			break;
	}

}

void	LightCtrl_CANSiglOnOrOffSet(enOutputReqType OutputReq, enTurnLightSelect TurnLightSelect)
{
	switch(TurnLightSelect)
	{
		case	enTurnLight_Left:
			if(enOutputReq_On == OutputReq)
			{
				//BitsInMsgByteSet(CANMid_GetPMsgTxBuffer(&BCANMidInfo, eBCAN_PMSG_LS_OS_3C3), 0, 2, enOutputSts_On);
			}
			else if(enOutputReq_Off == OutputReq)
			{
				//BitsInMsgByteSet(CANMid_GetPMsgTxBuffer(&BCANMidInfo, eBCAN_PMSG_LS_OS_3C3), 0, 2, enOutputSts_Off);
			}
			else
			{}
			break;

		case	enTurnLight_Right:
			if(enOutputReq_On == OutputReq)
			{
				//BitsInMsgByteSet(CANMid_GetPMsgTxBuffer(&BCANMidInfo, eBCAN_PMSG_LS_OS_3C3), 2, 2, enOutputSts_On);
			}
			else if(enOutputReq_Off == OutputReq)
			{
				//BitsInMsgByteSet(CANMid_GetPMsgTxBuffer(&BCANMidInfo, eBCAN_PMSG_LS_OS_3C3), 2, 2, enOutputSts_Off);
			}
			else
			{}

			break;

		default:

			break;
	}

}
/*******************************************************************************
* �������ƣ�LightCtrl_DoorStsChangedForSearchCar
* ������������״̬�ı���
* ��ڲ�������
* ���ڲ������Ÿı�����
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enDoorStsChanged	LightCtrl_DoorStsChangedForSearchCar(void)
{
	enDoorStsChanged 	DoorStsChangedFlag = enDoorSts_NoChanged;
	static	unDoorSts	PreDoorSts;
	INT8U	index = 0;
	INT8U	Mask = 0x01;

	if(D_AllDoor_DoorSts != PreDoorSts.Byte)
	{
		if(TRUE == AllDoorClose) // All door is closed
		{
			DoorStsChangedFlag = enDoorSts_AllClosed;
		}
		else
		{
			Mask = 0x01;
			for(index = 0; index < 5; index ++)
			{
				if((enDoor_Close != (D_AllDoor_DoorSts & Mask)) && (enDoor_Close == (PreDoorSts.Byte & Mask))) // one door is opened
				{
					if(0x10u == Mask)//���Ŵ�
					{
						DoorStsChangedFlag = enDoorSts_TrunkIsOpened;
					}
					else
					{
						DoorStsChangedFlag = enDoorSts_OneIsOpened;
					}
						
					break;
				}

				Mask <<= 0x01;
			}
		}
		PreDoorSts.Byte = D_AllDoor_DoorSts;
	}
	else
	{
		DoorStsChangedFlag = enDoorSts_NoChanged;
	}

	return	DoorStsChangedFlag;

}


/*******************************************************************************
* �������ƣ�LightCtrl_TurnLightFlash
* ����������ת�����˸����
* ��ڲ�����TurnLightFlashMode: ת�����˸��ģʽѡ��; TurnLightSelect: ��Ҫ���õ�ת���
* ���ڲ�������
* �� �� ֵ��ת�����˸�Ĵ���
* ��    ע��
*******************************************************************************/
INT16U	LightCtrl_TurnLightFlash(enTurnLightFlashMode TurnLightFlashMode, enTurnLightSelect TurnLightSelect)
{
	static	INT32U		TurnLeftLightFlashTimeCnt = 0;      // ת��ʱ��˸��ʱ���ʱ
	static	INT16U		TurnLeftLightFlashNumberCnt = 0;    // ת�����˸�Ĵ�������

	static	INT32U		TurnRightLightFlashTimeCnt = 0;      // ת��ʱ��˸��ʱ���ʱ
	static	INT16U		TurnRightLightFlashNumberCnt = 0;    // ת�����˸�Ĵ�������

	if(enTurnLight_Left == TurnLightSelect)
	{
		switch(TurnLightFlashMode)
		{
			case	enTurnLightFlash_Stop:
				TurnLeftLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
				TurnLeftLightFlashNumberCnt = 0;
				LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				break;

			case	enTurnLightFlash_2_5Hz:
				//TurnLeftLightFlashTimeCnt ++;
				if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_On_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_Period_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnLeftLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnLeftLightFlashNumberCnt ++;
				}
				break;
				
			case	enTurnLightFlash_1_67Hz:
				if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_Period_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnLeftLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnLeftLightFlashNumberCnt ++;
				}
				break;

			case	enTurnLightFlash_1_25Hz:
				if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnLeftLightFlashTimeCnt) <= (D_TurnLightFlash_Period_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnLeftLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnLeftLightFlashNumberCnt ++;
				}
				break;
			default:

				break;
		}
		return	(TurnLeftLightFlashNumberCnt);
	}
	else if(enTurnLight_Right == TurnLightSelect)
	{
		switch(TurnLightFlashMode)
		{
			case	enTurnLightFlash_Stop:
				TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
				TurnRightLightFlashNumberCnt = 0;
				LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				break;

			case	enTurnLightFlash_2_5Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_On_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_Period_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;
				
			case	enTurnLightFlash_1_67Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt)<= (D_TurnLightFlash_Period_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;

			case	enTurnLightFlash_1_25Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_Period_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;
				
			default:

				break;
		}
		return	(TurnRightLightFlashNumberCnt);
	}
	else if(enTurnLight_LeftRight == TurnLightSelect)
	{
		switch(TurnLightFlashMode)
		{
			case	enTurnLightFlash_Stop:
				TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
				TurnRightLightFlashNumberCnt = 0;
				LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				break;

			case	enTurnLightFlash_2_5Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt)<= (D_TurnLightFlash_On_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_Period_2_5Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;
				
			case	enTurnLightFlash_1_67Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_Period_1_67Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;

			case	enTurnLightFlash_1_25Hz:
				if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_On_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_On, TurnLightSelect);
				}
				else if(Hal_TimerDiffTs(TurnRightLightFlashTimeCnt) <= (D_TurnLightFlash_Period_1_25Hz*D_LightCtrlTask_Period))
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
				}
				else
				{
					LightCtrl_TurnLightOnOrOffSet(enOutputReq_Off, TurnLightSelect);
					TurnRightLightFlashTimeCnt = D_HAL_GET_CUR_MS_TS();
					TurnRightLightFlashNumberCnt ++;
				}
				break;

			
			default:

				break;
		}
		return	(TurnRightLightFlashNumberCnt);
	}
	return 0;
}







/*******************************************************************************
* �������ƣ�LightCtrl_TurnLightFlashAccordingToLack
* ��������������ȱ���������ת����Բ�ͬƵ����˸
* ��ڲ�������
* ���ڲ�����TurnLightSelect: ��Ҫ���Ƶ�ת���
* �� �� ֵ��ת�����˸�Ĵ���
* ��    ע��
*******************************************************************************/
INT16U	LightCtrl_TurnLightFlashAccordingToLack(void)
{

	static enLightLoadSts preLeftLightLoadSts = enLightLoad_Normal;
	static enLightLoadSts preRightLightLoadSts = enLightLoad_Normal;

	INT16U	retRight = 0;
	INT16U	retLeft = 0;

	if((preLeftLightLoadSts != TurnLight_Left_LoadSts) || (preRightLightLoadSts != TurnLight_Right_LoadSts))
	{
		preLeftLightLoadSts = TurnLight_Left_LoadSts;
		preRightLightLoadSts = TurnLight_Right_LoadSts;
	}

	/*��״̬�����ı�ʱ�����ԭ�ж�·��·״̬�������ж�*/
	static enTurnLightCtrlMode preLightCtrlMode = enCtrlMode_Non;
	static BOOL	bLeftRightChangeFlg = FALSE;
	if(preLightCtrlMode != TurnLightOp.CurTurnLightCtrlMode)
	{
		if(FALSE == TurnLightLackCfgFlg)//��Ͽ���ʱ������״̬�ı䣬ȱ��״̬�����
		{
			TurnLight_Left_LoadSts = enLightLoad_Normal;
			TurnLight_Right_LoadSts = enLightLoad_Normal;
		}
		preLightCtrlMode = TurnLightOp.CurTurnLightCtrlMode;

		bLeftRightChangeFlg = TRUE;
	}
	//----------����ȱ���������ת���----------------------------------------------
	/*
		���ݿͻ�Ҫ��Ϊ�˰�ȫ���
		����ת��ʱ��PEPS����ʱ���е�ѹ�������ƣ�
		Σ�ձ���ʱ�����ܵ�ѹ������
	*/
	if(enCtrlMode_HazardEmergency == TurnLightOp.CurTurnLightCtrlMode)/*Σ�ձ���ģʽ��*/
	{
		if(enLightLoad_Normal == TurnLight_Left_LoadSts)
		{
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Left);
		}
		else if(enLightLoad_Under == TurnLight_Left_LoadSts)
		{
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_2_5Hz, enTurnLight_Left);
		}
		else if(enLightLoad_Over == TurnLight_Left_LoadSts)
		{
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
			retLeft = D_TurnLightFlashNumber_Min;
		}

		if(enLightLoad_Normal == TurnLight_Right_LoadSts)
		{
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Right);
		}
		else if(enLightLoad_Under == TurnLight_Right_LoadSts)
		{
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_2_5Hz, enTurnLight_Right);
		}
		else if(enLightLoad_Over == TurnLight_Right_LoadSts)
		{
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
			retRight = D_TurnLightFlashNumber_Min;
		}
		
	}
	else if(enCtrlMode_TurnLeft == TurnLightOp.CurTurnLightCtrlMode)/*��תģʽ��*/
	{
		LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);

		if(IsLightPwrVoltNormal() && (TRUE == bLeftRightChangeFlg))
		{
			if(enLightLoad_Normal == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Left);
			}
			else if(enLightLoad_Under == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_2_5Hz, enTurnLight_Left);

			}
			else if(enLightLoad_Over == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
				retLeft = D_TurnLightFlashNumber_Min;

			}
		}
		else
		{
			if(TRUE == IsLightPwrVoltHigh())
			{
				bLeftRightChangeFlg = FALSE;
			}
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
			retLeft = D_TurnLightFlashNumber_Min;

		}
	}
	else if(enCtrlMode_TurnRight == TurnLightOp.CurTurnLightCtrlMode)/*��תģʽ��*/
	{
		LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);

		if(IsLightPwrVoltNormal() && (TRUE == bLeftRightChangeFlg))
		{
			if(enLightLoad_Normal == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Under == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_2_5Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Over == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
				retRight = D_TurnLightFlashNumber_Min;
			}
		}
		else
		{
			if(TRUE == IsLightPwrVoltHigh())
			{
				bLeftRightChangeFlg = FALSE;
			}
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
			retRight = D_TurnLightFlashNumber_Min;

		}
	}
	else if(enCtrlMode_SetAlarmSuccess == TurnLightOp.CurTurnLightCtrlMode)/*�����������*/
	{
		if(IsLightPwrVoltNormal())
		{
			if(enLightLoad_Normal == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_67Hz, enTurnLight_Left);
			}
			else if(enLightLoad_Under == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_67Hz, enTurnLight_Left);
			}
			else if(enLightLoad_Over == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
				retLeft = D_TurnLightFlashNumber_Min;
			}

			if(enLightLoad_Normal == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_67Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Under == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_67Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Over == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
				retRight = D_TurnLightFlashNumber_Min;
			}
		}
		else
		{
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
			retLeft = D_TurnLightFlashNumber_Min;
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
			retRight = D_TurnLightFlashNumber_Min;
		}
	}
	else if((enCtrlMode_Emergency <= TurnLightOp.CurTurnLightCtrlMode) && \
			(TurnLightOp.CurTurnLightCtrlMode <= enCtrlMode_ThiefWarning)) // ��PEPS����ʱ,�����ж�ȱ�����
	{
		if(IsLightPwrVoltNormal())
		{
			if(enLightLoad_Normal == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Left);
			}
			else if(enLightLoad_Under == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Left);
			}
			else if(enLightLoad_Over == TurnLight_Left_LoadSts)
			{
				retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
				retLeft = D_TurnLightFlashNumber_Min;
			}

			if(enLightLoad_Normal == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Under == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_1_25Hz, enTurnLight_Right);
			}
			else if(enLightLoad_Over == TurnLight_Right_LoadSts)
			{
				retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
				retRight = D_TurnLightFlashNumber_Min;
			}
		}
		else
		{
			retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
			retLeft = D_TurnLightFlashNumber_Min;
			retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
			retRight = D_TurnLightFlashNumber_Min;
		}
	}
	else//����ΪNON�ǹر����
	{
		retLeft = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Left);
		//retLeft = D_TurnLightFlashNumber_Min;
		retRight = LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_Right);
		//retRight = D_TurnLightFlashNumber_Min;//���η�ֹ�б���ֱ�ӽ����������ɣ���������ķ�֧
	}
	if(retLeft > retRight)
	{
		return retLeft;
	}
	else
	{
		return retRight;
	}

}

void LightCtrl_SetPepsAlarm(enPEPSRemoteAlarmCmd cmd)
{
	PEPSRemoteAlarmCmd =  cmd;
}

static enPEPSRemoteAlarmCmd LightCtrl_GetPepsAlarm(void)
{
	return PEPSRemoteAlarmCmd;
}


/*******************************************************************************
* �������ƣ�LightCtrl_PepsRemoteAlarmProcess
* ����������PEPS��������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_PepsRemoteAlarmProcess(void)
{
	static  enPEPSRemoteAlarmCmd	tPEPSRemoteAlarmCmd = enAlarm_Invalid;
	static  enPEPSRemoteAlarmCmd	tPrePEPSRemoteAlarmCmd = enAlarm_Invalid;

	tPEPSRemoteAlarmCmd = LightCtrl_GetPepsAlarm(); // �б����ź�ʱ����������2֡
	if(tPEPSRemoteAlarmCmd != tPrePEPSRemoteAlarmCmd)
	{
		tPrePEPSRemoteAlarmCmd = tPEPSRemoteAlarmCmd;
		//SleepOpInfo.unModuleSt.Bits.btPEPSCmd = TRUE;
		switch(tPEPSRemoteAlarmCmd) // ���ݱ���������˸
		{
			case    enAlarm_SetAlarmSuccess:
				// �������AlarmMode1,�������յ�AlarmMode1����,������ִ��AlarmMode1,
				// �˴�TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;��Ϊ���ô��������,ģʽ����Ϊ�иı��,
				// ����ĳ�������,��ģʽ�ı�ʱ�����¼�ʱ����
				if(TRUE == ClosePEPSRkePkeFunction)
				{
					return;
				}

				if(enCtrlMode_SetAlarmSuccess == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
				}
				TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_SetAlarmSuccess;
				TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

				TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;
				break;

			case    enAlarm_CancelAlarmSuccess:
				if(TRUE == ClosePEPSRkePkeFunction)
				{
					return;
				}

				if(enCtrlMode_CancelAlarmSuccess == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
				}
				TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_CancelAlarmSuccess;
				TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

				TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;
				break;

			case    enAlarm_RemoteSearchCar:
				if(TRUE == ClosePEPSRkePkeFunction)
				{
					return;
				}

				if(enCtrlMode_RemoteSearchCar == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
				}
				TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_RemoteSearchCar;
				TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

				TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;
				break;

			case    enAlarm_ShortRemoteTrunk:

				if(enCtrlMode_ShortRemoteTrunk == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
				}
				TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_ShortRemoteTrunk;
				TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

				TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;
				break;

			case    enAlarm_ThiefWarning:
				if(enCtrlMode_ThiefWarning == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnLightOp.PreTurnLightCtrlMode = enCtrlMode_Non;
				}
				TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_ThiefWarning;
				TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;

				TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE;
				break;

			default:

				break;
		}
	}
}

/*******************************************************************************
* �������ƣ�HazardSwChangedForTurnLight
* ����������Σ�ձ����ƿ��ر仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged HazardSwChangedForTurnLight(void)
{
	static BOOL  PreHazardSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreHazardSwChanged != Hal_GetIoVaild(EN_HAZARD_SW))
	{
		if(PreHazardSwChanged)
		{
			temp = enSw_ValidToUnvalid;
		}
		else
		{
			temp = enSw_UnvalidToValid;
		}
		PreHazardSwChanged = Hal_GetIoVaild(EN_HAZARD_SW);
	}
	return temp;
}
/*******************************************************************************
* �������ƣ�LightCtrl_ModeSelect
* ����������ת���ģʽѡ���Լ�����˳�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static void LightCtrl_ModeSelect(void)
{
	static	BOOL					TurnLightFlashThreeTimesFinishFlg = FALSE;
	//----------ת��ƿ���ģʽ�ı�ʱ,��������ر���---------------------------------
	// �˴��������������ڴ�λ��,�����������
		if(TurnLightOp.CurTurnLightCtrlMode != TurnLightOp.PreTurnLightCtrlMode)
		{
			TurnLightOp.TurnLightFlashNumber = 0;
			TurnLightOp.TurnLightFlashTime = 0;
	
			TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;
	
			//TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE; // �����ڴ˴�����, ������Σ�ձ���ʱ,�յ�PEPS����������ϻ�������
	
			TurnLightFlashThreeTimesFinishFlg = FALSE;
	
			TurnLightOp.PreTurnLightCtrlMode = TurnLightOp.CurTurnLightCtrlMode;
		}
	
	
	//---------- ת��ƿ���ģʽѡ�� ------------------------------------------------
		switch(TurnLightOp.CurTurnLightCtrlMode)
		{
			case	enCtrlMode_Non:
				TurnLightOp.TurnLightFlashNumber = 0;
				TurnLightOp.TurnLightFlashTime = 0;
	
				TurnLightOp.PEPSAlarmFlashFinishFlg = FALSE;
	
				//TurnLightOp.PEPSRemoteAlarmFinishFlg = FALSE; // �����ڴ˴�����, ������Σ�ձ���ʱ,�յ�PEPS����������ϻ�������
	
				(void)LightCtrl_TurnLightFlashAccordingToLack();//debug
	
				break;
	
			case	enCtrlMode_Emergency:
			case	enCtrlMode_HazardEmergency:
				(void)LightCtrl_TurnLightFlashAccordingToLack();
				break;
			case	enCtrlMode_TurnLeft:
			case	enCtrlMode_TurnRight:
				TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack();
				if(TurnLightOp.TurnLightFlashNumber >= D_TurnLightFlashNumber_Min) // ����ת��ƿ���ʱ,������˸3��,�Źر�;
				{
					TurnLightOp.TurnLightFlashNumber = D_TurnLightFlashNumber_Min;
					TurnLightFlashThreeTimesFinishFlg = TRUE;
				}
				break;
	
			case	enCtrlMode_SetAlarmSuccess: // Unlock success: turn lamp blink 2 time
				// Turn lamp
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_SetAlarmSuccess_FlashNumber)
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_SetAlarmSuccess_FlashNumber;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				else
				{
					TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack();
				}
	
				if(TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg)
	
				{
					TurnLightOp.TurnLightFlashNumber = 0;
	
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
	
			case	enCtrlMode_CancelAlarmSuccess: // Lock success: turn lamp blink 1 time
				// Turn lamp
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_CancelAlarmSuccess_FlashNumber)
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_CancelAlarmSuccess_FlashNumber;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				else
				{
					TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack();
				}
				
				if(TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg)
	
				{
					TurnLightOp.TurnLightFlashNumber = 0;
	
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
	
			case	enCtrlMode_RemoteSearchCar: // Lock failure: turn lamp blink 3 times, horn honk 1 time
				// Turn lamp
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_RemoteSearchCar_FlashNumber)
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_RemoteSearchCar_FlashNumber;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				else
				{
					TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack();
				}
	
				
	
				if(TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg)
				{
					TurnLightOp.TurnLightFlashNumber = 0;
	
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
	
			case	enCtrlMode_ShortRemoteTrunk: // Searching car: turn lamp blink 10 times, horn honk 2 times
				// Turn lamp
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_ShortRemoteTrunk_FlashNumber)
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_ShortRemoteTrunk_FlashNumber;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				else
				{
					TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack();
				}
	
				if(TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg)
	
				{
					TurnLightOp.TurnLightFlashNumber = 0;
	
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
	
			case	enCtrlMode_ThiefWarning: // Anti-theft: turn lamp blink 30S, horn honk 20S
				if(enAlarm_ThiefWarning != LightCtrl_GetPepsAlarm())
				{
					//��������������ֹͣ����
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
	
				// Turn lamp
				TurnLightOp.TurnLightFlashTime ++;
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_ThiefWarning_FlashTimes)//10��ѭ������
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_ThiefWarning_FlashTimes;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				if(TurnLightOp.TurnLightFlashTime >= D_PEPSAlarm_ThiefWarning_FlashTotalTime)
				{
					TurnLightOp.TurnLightFlashNumber++;//ѭ����һ��
					TurnLightOp.TurnLightFlashTime = 0U;//��ʼ��һ��ѭ��
				}
				else if(TurnLightOp.TurnLightFlashTime <= D_PEPSAlarm_ThiefWarning_FlashONTime)
				{
					(void)LightCtrl_TurnLightFlashAccordingToLack();
				}
				else
				{
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
				}
				
	
				if(TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg)
				{
					TurnLightOp.TurnLightFlashTime = 0;
	
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
			/*
			case	enCtrlMode_AlarmMode6: // Lock car hint: turn lamp blink 3 times, horn honk 3 times
				// Turn lamp
				if(TurnLightOp.TurnLightFlashNumber >= D_PEPSAlarm_Mode6_LockCarHint_FlashNumber)
				{
					TurnLightOp.TurnLightFlashNumber = D_PEPSAlarm_Mode6_LockCarHint_FlashNumber;
					(void)LightCtrl_TurnLightFlash(enTurnLightFlash_Stop, enTurnLight_LeftRight);
					TurnLightOp.PEPSAlarmFlashFinishFlg = TRUE;
				}
				else
				{
					TurnLightOp.TurnLightFlashNumber = LightCtrl_TurnLightFlashAccordingToLack(TurnLightOp.TurnLightSelect);
				}
	
			
	
				if( (TRUE == TurnLightOp.PEPSAlarmFlashFinishFlg) && \
						(TRUE == TurnLightOp.PEPSAlarmHonkFinishFlg) )
				{
					TurnLightOp.TurnLightFlashNumber = 0;
					TurnLightOp.HornHonkNumber = 0;
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					TurnLightOp.PEPSRemoteAlarmFinishFlg = TRUE;
				}
				break;
			*/
			case	enCtrlMode_EmergencyBrake:
				(void)LightCtrl_TurnLightFlashAccordingToLack();
				break;
	
			default:
	
				break;
		}
}


/*******************************************************************************
* �������ƣ�CrashSwChangedForTurnLight
* ������������ײ�źű仯״̬�ж�
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
static enSwChanged CrashSwChangedForTurnLight(void)
{
	static BOOL  PreCrashSwChanged = FALSE;
	enSwChanged temp = enSw_NoChanged;
	if(PreCrashSwChanged != LightCtrlStManage.TrigCrash)
	{
		if(LightCtrlStManage.TrigCrash>0)
		{
			temp = enSw_UnvalidToValid;
		}
		else
		{
			temp = enSw_ValidToUnvalid; 
		}
	}
	PreCrashSwChanged = LightCtrlStManage.TrigCrash;
	return temp;
}


/*******************************************************************************
* �������ƣ�LightCtrl_TurnLight
* ����������ת��ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_TurnLight(void)
{
	static 	INT16U 					KeepEmerBreakTimeCnt = 0;
	
	static  enTurnLightSwSts 		PreTurnLightSwSts = enTurnSw_Off;
	static	BOOL					PreHazardSwPressedFlg = FALSE;


	//INT8U CRRRL1_W_RCW = 0U;
	//INT8U APA3_St_HazardWarningReq = 0U;
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_TurnLight_Active)
	{
		if(DescIOCtl_enTurnLightFlash_1_5Hz == DescIOCtl_TurnLight_Flash_Cmd) // ��ת���ͬʱ��85CMin��˸
		{
			(void)LightCtrl_TurnLightFlash(enTurnLightFlash_1_5Hz, enTurnLight_LeftRight);
		}
		else if(DescIOCtl_enTurnLightFlash_0_75Hz == DescIOCtl_TurnLight_Flash_Cmd) // ��ת���ͬʱ��150CMin��˸
		{
			(void)LightCtrl_TurnLightFlash(enTurnLightFlash_3Hz, enTurnLight_LeftRight);
		}
		else
		{
			if(DescIOCtl_enTurnLight_ON == DescIOCtl_TurnLight_Left_Cmd)
			{
				TurnLampSts_Left_OutputReq = enOutputReq_On;
			}
			else if(DescIOCtl_enTurnLight_Flash == DescIOCtl_TurnLight_Left_Cmd)
			{
				(void)LightCtrl_TurnLightFlash(enTurnLightFlash_1_5Hz, enTurnLight_Left);
			}
			else
			{
				TurnLampSts_Left_OutputReq = enOutputReq_Off;
			}

			if(DescIOCtl_enTurnLight_ON == DescIOCtl_TurnLight_Right_Cmd)
			{
				TurnLampSts_Right_OutputReq = enOutputReq_On;
			}
			else if(DescIOCtl_enTurnLight_Flash == DescIOCtl_TurnLight_Right_Cmd)
			{
				(void)LightCtrl_TurnLightFlash(enTurnLightFlash_1_5Hz, enTurnLight_Right);
			}
			else
			{
				TurnLampSts_Right_OutputReq = enOutputReq_Off;
			}
		}

		return;
	}
	*/

	static BOOL LeftTurnLightEnable = FALSE;//ת��ƿ���������
	static BOOL RightTurnLightEnable = FALSE;//ת��ƿ���������
	static BOOL CrashLightEnable = FALSE;//��ײ����������
	static BOOL EmergencyBrakeLightEnable = FALSE;//�����ƶ�����������

	static BOOL BatteryLightEnable = FALSE;//���ɢ�ȿ���������
	static BOOL RadarLightEnable = FALSE;//���״￪��������
	static BOOL APALightEnable = FALSE;//APA����������
	static BOOL HazardLightEnable = FALSE;//Σ�վ����ƿ���������
	
	//PEPS�������ʹ��
	static BOOL SetAlarmLightEnable = FALSE;//����ɹ�����������
	static BOOL CancelAlarmLightEnable = FALSE;//�����ɹ�����������
	static BOOL RemoteSearchCarLightEnable = FALSE;//Ѱ���ƿ���������
	static BOOL ShortRemoteTrunkLightEnable = FALSE;//ң�ؿ����俪��������
	static BOOL ThiefWarningLightEnable = FALSE;//������������������

	static BOOL TurnLight3TimesFlg = FALSE;
	static INT32U TurnSwValidTime = 0U;//ת�����Чʱ��
	static INT32U CrashWarnigTime = 0U;//��������ʱ��
	static INT32U SearchCarLightOnTime = 0U;//Ѱ��ʱ���������ʱ��
	static INT8U  PreCRRRL1_WRCW =0;
	static INT8U  PreAPA3_StHazardWarningReq=0;

	enSwChanged HazardSwChanged = enSw_NoChanged;

	enSwChanged CrashSingalChanged = enSw_NoChanged;

	enDoorStsChanged SearchCarDoorChanged = enDoorSts_NoChanged;
		
	HazardSwChanged = HazardSwChangedForTurnLight();
	
	CrashSingalChanged = CrashSwChangedForTurnLight();

	SearchCarDoorChanged = LightCtrl_DoorStsChangedForSearchCar();
		
	if(IGNState_ON <= LightCtrlStManage.PowerMode) // ��IGN ON ����
	{
		if(enTurnSw_Left == LightCtrlStManage.TurnLightSwSts)//ת���
		{
			//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_TurnLeft;
			//TurnLightOp.TurnLightSelect = enTurnLight_Left;
			LeftTurnLightEnable = TRUE;
			if(++TurnSwValidTime >= D_Time_600MS)
			{
				TurnSwValidTime = D_Time_600MS;
			}
		}
		else if(enTurnSw_Right == LightCtrlStManage.TurnLightSwSts)
		{
			//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_TurnRight;
			//TurnLightOp.TurnLightSelect = enTurnLight_Right;
			RightTurnLightEnable = TRUE;

			if(++TurnSwValidTime >= D_Time_600MS)
			{
				TurnSwValidTime = D_Time_600MS;
			}
		}
		else
		{
			if(TurnSwValidTime >= D_Time_600MS)//֮ǰ��Чʱ�䣾600ms
			{
				TurnSwValidTime = 0U;
				if(enCtrlMode_TurnLeft == TurnLightOp.CurTurnLightCtrlMode)
				{

					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					LeftTurnLightEnable = FALSE;
				}
				else if(enCtrlMode_TurnRight == TurnLightOp.CurTurnLightCtrlMode)
				{		
					TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
					RightTurnLightEnable = FALSE;
				}
			}
			else
			{
				if(enCtrlMode_TurnLeft == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnSwValidTime = 0U;
					if(TurnLightOp.TurnLightFlashNumber >= D_TurnLightFlashNumber_Min) // ����ת��ƿ���ʱ,������˸3��,�Źر�;
					{
						TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
						LeftTurnLightEnable = FALSE;
					}
				}
				else if(enCtrlMode_TurnRight == TurnLightOp.CurTurnLightCtrlMode)
				{
					TurnSwValidTime = 0U;
					if(TurnLightOp.TurnLightFlashNumber >= D_TurnLightFlashNumber_Min) // ����ת��ƿ���ʱ,������˸3��,�Źر�;
					{
						TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
						RightTurnLightEnable = FALSE;
					}
				}
			}
			
		}
	}
	else
	{
		if((enCtrlMode_TurnLeft == TurnLightOp.CurTurnLightCtrlMode) || (enCtrlMode_TurnRight == TurnLightOp.CurTurnLightCtrlMode))
		{
			TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
			LeftTurnLightEnable = FALSE;
			RightTurnLightEnable = FALSE;
		}
	}
	
	// ��ײ�ź� SDM1_St_CrashIntensity �� 0 ��Ϊ!= 0����!=0 ֮�����䣬 ����ת��� 800ms ������˸��
	if(enSw_UnvalidToValid == CrashSingalChanged) // ��ײ����
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == CrashLightEnable)
		{
			CrashWarnigTime = 0U;
			CrashLightEnable = TRUE;
		}
	}
	if(CrashLightEnable)
	{
		if(++CrashWarnigTime >= D_Time_5S)
		{
			CrashWarnigTime = D_Time_5S;
			if(enSw_UnvalidToValid == HazardSwChanged)
			{
				CrashLightEnable = FALSE;
				CrashWarnigTime = 0U;
			}
		}
	}
	//�����ƶ��ź� BR1_St_EmergencyBrakeLight �� 0 ��Ϊ 1�� ����ת��� 800ms ������˸��
	if(1U == GWBBrake1Info.BR1_StEmergencyBrakeLight)
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == EmergencyBrakeLightEnable)
		{
			EmergencyBrakeLightEnable = TRUE;
		}
	}
	//�����ƶ�������Σ�ձ�����������Ч�Ҵ�<15km/h ��Ϊ>15km/h����Σ�ձ�����������Ч��Ϊ��Ч��
	if(EmergencyBrakeLightEnable)
	{
		if(((LightCtrlStManage.PreSp<15U)&&(15U < LightCtrlStManage.CurrSp))|| (enSw_UnvalidToValid == HazardSwChanged))
		{
			EmergencyBrakeLightEnable = FALSE;
		}
	}
	LightCtrlStManage.PreSp = LightCtrlStManage.CurrSp;//���´���ʱ�ĳ���
	
	//�������ɢ�����źţ��źŴ����룬Ԥ���� �� 0 ��Ϊ 1�� ����ת��� 800ms ������˸��
	/*
	if(1U == ���ɢ��)
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == BatteryLightEnable)
		{
			BatteryLightEnable = TRUE;
		}
	}
	//�������ɢ������Σ�ձ����� Σ�ձ�����������Ч��Ϊ��Ч��
	if(BatteryLightEnable)
	{
		if(enHazardSw_UnvalidToValid == HazardSwChanged)
		{
			BatteryLightEnable = FALSE;
		}
	}
	*/
	//������״ﱨ���ź� CRRRL1_W_RCW �� 0 ��Ϊ 1������ת��� 800ms ������˸��
	if((PreCRRRL1_WRCW != GWBCRRRL10x34BInfo.CRRRL1_WRCW)&&(1== GWBCRRRL10x34BInfo.CRRRL1_WRCW))
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == RadarLightEnable)
		{
			RadarLightEnable = TRUE;
		}
	}
	//������״￪����Σ�ձ����� CRRRL1_W_RCW �� 1 ��Ϊ 0����Σ�ձ�����������Ч��Ϊ��Ч��
	if(RadarLightEnable)
	{
		if((0U == GWBCRRRL10x34BInfo.CRRRL1_WRCW) || (enSw_UnvalidToValid == HazardSwChanged))
		{
			RadarLightEnable = FALSE;
		}
	}
	PreCRRRL1_WRCW = GWBCRRRL10x34BInfo.CRRRL1_WRCW;
	//APA �Զ�������ʾ�ź� APA3_St_HazardWarningReq �� 0 ��Ϊ 1������ת��� 800ms ������˸��
	if((PreAPA3_StHazardWarningReq !=EMSAPA30x43FInfo.APA3_StHazardWarningReq)&&( 1U == EMSAPA30x43FInfo.APA3_StHazardWarningReq))
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == APALightEnable)
		{
			APALightEnable = TRUE;
		}
	}
	//APA �Զ�����������Σ�ձ����� APA3_St_HazardWarningReq �� 0 ��Ϊ 2�� 
	//��Σ�ձ�����������Ч��Ϊ��Ч�����Դ״̬ ON ת�򿪹�����Ч��Ϊ��Ч��
	if(APALightEnable)
	{
		if((2U == EMSAPA30x43FInfo.APA3_StHazardWarningReq) || (enSw_UnvalidToValid == HazardSwChanged) ||\
			((IGNState_ON <= LightCtrlStManage.PowerMode) && (enTurnSw_Off != LightCtrlStManage.TurnLightSwSts)))
		{
			APALightEnable = FALSE;
		}
	}
	PreAPA3_StHazardWarningReq =EMSAPA30x43FInfo.APA3_StHazardWarningReq;
	//Σ�ձ����ر�״̬�£� Σ�ձ���������������Ч��Ϊ��Ч�� ����ת��� 800ms ������˸
	if((enCtrlMode_HazardEmergency != TurnLightOp.CurTurnLightCtrlMode) && \
		(enCtrlMode_Emergency != TurnLightOp.CurTurnLightCtrlMode) && \
		(enSw_UnvalidToValid == HazardSwChanged))
	{
		//TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_HazardEmergency;
		//TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
		if(FALSE == HazardLightEnable)
		{
			HazardLightEnable = TRUE;
		}
	}
	//Σ�ձ������ؿ�����Σ�ձ�����Σ�ձ�����������Ч��Ϊ��Ч��
	if(enCtrlMode_HazardEmergency == TurnLightOp.CurTurnLightCtrlMode)
	{
		if(enSw_UnvalidToValid == HazardSwChanged)
		{
			HazardLightEnable = FALSE;
		}
	}

	//LightCtrl_PepsRemoteAlarmProcess();


	if(enAlarm_ThiefWarning == LightCtrl_GetPepsAlarm())
	{
		ThiefWarningLightEnable = TRUE;//������������������
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
	}
	else if(enAlarm_SetAlarmSuccess == LightCtrl_GetPepsAlarm())
	{
		SetAlarmLightEnable = TRUE;//����ɹ�����������
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
		RemoteSearchCarLightEnable = FALSE;//Ѱ������
		SearchCarNearLightFunction = FALSE;
		SearchCarRearFrogLampFunction = FALSE;
	}
	else if(enAlarm_CancelAlarmSuccess == LightCtrl_GetPepsAlarm())
	{
		CancelAlarmLightEnable = TRUE;//�����ɹ�����������
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
		RemoteSearchCarLightEnable = FALSE;//Ѱ������
		SearchCarNearLightFunction = FALSE;
		SearchCarRearFrogLampFunction = FALSE;
	}
	else if(enAlarm_ShortRemoteTrunk == LightCtrl_GetPepsAlarm())
	{
		ShortRemoteTrunkLightEnable = TRUE;//ң�ؿ����俪��������
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
	}
	else if(enAlarm_RemoteSearchCar == LightCtrl_GetPepsAlarm())
	{
		RemoteSearchCarLightEnable = TRUE;//Ѱ���ƿ���������

		if(LightCtrlStManage.LookforCarSetPrm == 1||LightCtrlStManage.LookforCarSetPrm == 3)
		{
			SearchCarNearLightFunction = TRUE;
		}
		if(LightCtrlStManage.LookforCarSetPrm == 2||LightCtrlStManage.LookforCarSetPrm == 3)
		{
			SearchCarRearFrogLampFunction = TRUE;
		}
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
		SearchCarLightOnTime = 0U;//���յ��źž��������¼�ʱ
	}
	else
	{
		LightCtrl_SetPepsAlarm(enAlarm_Invalid);
	}

	if(ThiefWarningLightEnable)
	{
		if(D_PEPSAlarm_ThiefWarning_FlashTimes <= TurnLightOp.TurnLightFlashNumber)
		{
			ThiefWarningLightEnable = FALSE;
		}
	}

	if(SetAlarmLightEnable)
	{
		if(D_PEPSAlarm_SetAlarmSuccess_FlashNumber <= TurnLightOp.TurnLightFlashNumber)
		{
			SetAlarmLightEnable = FALSE;
		}
	}


	if(CancelAlarmLightEnable)
	{
		if(D_PEPSAlarm_CancelAlarmSuccess_FlashNumber <= TurnLightOp.TurnLightFlashNumber)
		{
			CancelAlarmLightEnable = FALSE;
		}
	}
	
	if(ShortRemoteTrunkLightEnable)
	{
		if(D_PEPSAlarm_ShortRemoteTrunk_FlashNumber <= TurnLightOp.TurnLightFlashNumber)
		{
			ShortRemoteTrunkLightEnable = FALSE;
		}
	}

	if(RemoteSearchCarLightEnable)
	{
		if(D_PEPSAlarm_RemoteSearchCar_FlashNumber <= TurnLightOp.TurnLightFlashNumber)
		{
			RemoteSearchCarLightEnable = FALSE;
		}
		if(enDoorSts_OneIsOpened == SearchCarDoorChanged)
		{
			RemoteSearchCarLightEnable = FALSE;
		}
	}
	if(SearchCarNearLightFunction||SearchCarRearFrogLampFunction)
	{
		if(++SearchCarLightOnTime >= D_PEPSAlarm_SearchCarTime)
		{
			SearchCarLightOnTime = 0U;
			SearchCarNearLightFunction = FALSE;
			SearchCarRearFrogLampFunction = FALSE;
		}
		if(enDoorSts_OneIsOpened == SearchCarDoorChanged)
		{
			SearchCarNearLightFunction = FALSE;
			SearchCarRearFrogLampFunction = FALSE;
		}
	}


	/*P ��ײ��������>P ��������/���/��������>P �����ƶ���������>P �������ɢ��������>P ������״ﱨ������>
	P Σ�ձ�����������=P ��/��ת�򿪹�����>PAPA ������������>P ң�غ���̰�����>P Ѱ������*/
	if(TRUE == CrashLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(ThiefWarningLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_ThiefWarning;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(SetAlarmLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_SetAlarmSuccess;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(CancelAlarmLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_CancelAlarmSuccess;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if((TRUE == EmergencyBrakeLightEnable) || \
			(TRUE == BatteryLightEnable) || \
			(TRUE == RadarLightEnable))
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(TRUE == HazardLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_HazardEmergency;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(TRUE == LeftTurnLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_TurnLeft;
		TurnLightOp.TurnLightSelect = enTurnLight_Left;
	}
	else if(TRUE == RightTurnLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_TurnRight;
		TurnLightOp.TurnLightSelect = enTurnLight_Right;
	}
	else if(APALightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Emergency;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(ShortRemoteTrunkLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_ShortRemoteTrunk;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else if(RemoteSearchCarLightEnable)
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_RemoteSearchCar;
		TurnLightOp.TurnLightSelect = enTurnLight_LeftRight;
	}
	else
	{
		TurnLightOp.CurTurnLightCtrlMode = enCtrlMode_Non;
	}	

	

	LightCtrl_ModeSelect();

}


/*******************************************************************************
* �������ƣ�LightCtrl_BrakeLamp
* ������������������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��static BOOL TurnAssistFunction = FALSE;//ת��������
			static BOOL FarAssistFunction = FALSE;//Զ�⸨������
*******************************************************************************/
void	LightCtrl_AssistLamp(void)
{
	static BOOL TurnAssistEnable = FALSE;
	static BOOL LeftTurnAssist = FALSE;
	static BOOL RightTurnAssist = FALSE;

	static BOOL LeftWheelAssist = FALSE;
	static BOOL RightWheelAssist = FALSE;

	static BOOL ReverseAssist = FALSE;

	GWBEPS30x3A_t  GwbEps;

	INT8U 	EPS3_St_CSWASign = 0U;
	INT16U	EPS3_N_CSWA = 0U;

	Hal_CanBcmGetInfo(EN_CAN_MSG_GWB_EPS_3,(INT8U*)&GwbEps,sizeof(GwbEps));
	
	if(((1U == LightCtrlStManage.ExlMainOrDiAssistLightPrm) || (3U == LightCtrlStManage.ExlMainOrDiAssistLightPrm)) && \
		(IGNState_ON == LightCtrlStManage.PowerMode) && (40U > LightCtrlStManage.CurrSp) && (enOutputSts_On == LowBeam_OutputSts))
	{
		TurnAssistEnable = TRUE;
	}
	else
	{
		TurnAssistEnable = FALSE;
	}

	if(enTurnSw_Left == LightCtrlStManage.TurnLightSwSts)
	{
		LeftTurnAssist = TRUE;
	}
	
	if(enTurnSw_Right == LightCtrlStManage.TurnLightSwSts)
	{
		RightTurnAssist = TRUE;
	}

	if((enTurnSw_Off == LightCtrlStManage.TurnLightSwSts) && (0U == GwbEps.EPS3_StCSWASign) && (80U < (INT32U)(GwbEps.EPS3_NCSWA*0.04375)))
	{
		LeftWheelAssist = TRUE;
	}

	if((enTurnSw_Off == LightCtrlStManage.TurnLightSwSts) && (1U == GwbEps.EPS3_StCSWASign) && (80U < (INT32U)(GwbEps.EPS3_NCSWA*0.04375)))
	{
		RightWheelAssist = TRUE;
	}

	if(LeftTurnAssist)
	{
		if((enTurnSw_Off == LightCtrlStManage.TurnLightSwSts) || (FALSE == TurnAssistEnable))
		{
			LeftTurnAssist = FALSE;
		}
	}

	if(RightTurnAssist)
	{
		if((enTurnSw_Off == LightCtrlStManage.TurnLightSwSts) || (FALSE == TurnAssistEnable))
		{
			RightTurnAssist = FALSE;
		}
	}

	if(LeftWheelAssist)
	{
		if(((0U == GwbEps.EPS3_StCSWASign) && (60U > (INT32U)(GwbEps.EPS3_NCSWA*0.04375))) || (FALSE == TurnAssistEnable))
		{
			LeftWheelAssist = FALSE;
		}
	}

	if(RightWheelAssist)
	{
		if(((1U == GwbEps.EPS3_StCSWASign) && (60U > (INT32U)(GwbEps.EPS3_NCSWA*0.04375))) || (FALSE == TurnAssistEnable))
		{
			RightWheelAssist = FALSE;
		}
	}

	if((TRUE == TurnAssistEnable) && (1U == LightCtrlStManage.ReverseGear_SW))
	{
		ReverseAssist = TRUE;
	}
	else
	{	
		ReverseAssist = FALSE;
	}
	if((TRUE == LeftTurnAssist) || (TRUE == LeftWheelAssist) || (TRUE == ReverseAssist))
	{
		LeftTurnAssistFunction  = TRUE;
	}
	else
	{
		LeftTurnAssistFunction  = FALSE;
	}
	if((TRUE == RightTurnAssist) || (TRUE == RightWheelAssist) || (TRUE == ReverseAssist))
	{
		RightTurnAssistFunction  = TRUE;
	}
	else
	{
		RightTurnAssistFunction  = FALSE;
	}


	if((1U == LightCtrlStManage.ExlMainOrDiAssistLightPrm) && (enOutputSts_On == HighBeam_OutputSts))
	{
		FarAssistFunction  = TRUE;
	}
	else
	{
		FarAssistFunction = FALSE;
	}


	if((TRUE == LeftTurnAssistFunction) || (TRUE == FarAssistFunction))
	{
		LeftAssistLight_OutputReq = enOutputReq_On;
	}
	else
	{
		LeftAssistLight_OutputReq = enOutputReq_Off;
	}

	if((TRUE == RightTurnAssistFunction) || (TRUE == FarAssistFunction))
	{
		RightAssistLight_OutputReq = enOutputReq_On;
	}
	else
	{
		RightAssistLight_OutputReq = enOutputReq_Off;
	}
}

/*******************************************************************************
* �������ƣ�LightCtrl_BrakeLamp
* ����������ɲ���ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_BrakeLamp(void)
{
	static BOOL BrakeLightEnable = FALSE;//�ƶ��ƹ��ܿ�������
	static BOOL EmergencyBrakeLightEnable = FALSE;//�����ƶ�����ɲ���ƹ��ܿ���

	INT8U BR1Lost = 0U;
	INT8U EMS5Lost = 0U;
	INT8U EPB1Lost = 0U;
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Light_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_BrakeLamp_Cmd)
		{
			BrakeLamp_OutputReq = enOutputReq_On;
		}
		else
		{
			BrakeLamp_OutputReq = enOutputReq_Off;
		}

		return;
	}

	

	*/
	
	if(((TRUE ==  LightCtrlStManage.BRAKE_SW) || (1U == GWBBrake1Info.BR1_SBrakePress) || (1U == GWBEMS5Info.EMS5_StBPedalLamp) || \
			((1U == GWBBrake1Info.BR1_StActiveBrake) && (0U == GWBBrake1Info.BR1_FActiveBrake)) || (1U == GWBEPB1Info.EPB1_StPBrakeLight)) && (0U == GWBBrake1Info.BR1_StEmergencyBrakeLight))
	{
		//BrakeLamp_OutputReq = enOutputReq_On;
		BrakeLightEnable = TRUE;
	}
	if((FALSE ==  LightCtrlStManage.BRAKE_SW) && ((0U == GWBBrake1Info.BR1_SBrakePress) || (1U == BR1Lost)) && ((0U == GWBEMS5Info.EMS5_StBPedalLamp) || (1U == EMS5Lost))&& \
			((0U == GWBBrake1Info.BR1_StActiveBrake) || (1U == GWBBrake1Info.BR1_FActiveBrake) || (1U == BR1Lost)) && ((1U != GWBEPB1Info.EPB1_StPBrakeLight) || (1U == EPB1Lost)))
	{
		//BrakeLamp_OutputReq = enOutputReq_Off;
		BrakeLightEnable = FALSE;
	}

	if(1U == GWBBrake1Info.BR1_StEmergencyBrakeLight)
	{
		EmergencyBrakeLightEnable = TRUE;//�����ƶ�����ɲ���ƹ��ܿ���
	}
	if((0U == GWBBrake1Info.BR1_StEmergencyBrakeLight) || (1U == BR1Lost))
	{
		EmergencyBrakeLightEnable = FALSE;//�����ƶ�����ɲ���ƹ��ܹر�
	}

	if(EmergencyBrakeLightEnable)
	{
		if(enOutputReq_FLASH != BrakeLamp_OutputReq)
		{
			BrakeLamp_OutputReq = enOutputReq_FLASH;
			Hal_BrakeLightStart(TRUE);
		}		
	}
	else
	{
		if(BrakeLightEnable)
		{	
			if(enOutputReq_On != BrakeLamp_OutputReq)
			{
				BrakeLamp_OutputReq = enOutputReq_On;
				Hal_BrakeLightStart(FALSE);
			}
		}
		else
		{
			BrakeLamp_OutputReq = enOutputReq_Off;
			Hal_BrakeLightStop();
		}
	}
}


/*******************************************************************************
* �������ƣ�LightCtrl_ReverseLamp
* ���������������ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_ReverseLamp(void)
{

	INT8U TCMLost = 0U;
//#define DebugRerverLight
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Light_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_ReverseLamp_Cmd)
		{
			ReverseLamp_OutputReq = enOutputReq_On;
		}
		else
		{
			ReverseLamp_OutputReq = enOutputReq_Off;
		}

		return;
	}
	*/

#ifdef DebugRerverLight
	//LightCtrlStManage.VehManuOrAutoPrm = D_VehManuOrAutoPrm_MT;
	LightCtrlStManage.PowerMode = IGNState_ON;
	GWBTCM1Info.TCM1_NActualGear = 7U;
#else
	
#endif
	/*TODO:test*/

	if(D_VehManuOrAutoPrm_MT != pEepromBodyGuardAntitheft_InLightFunc->VehManuOrAutoPrm )//�Զ���
	{
		if(0U == TCMLost)
		{
			if(7U == GWBTCM1Info.TCM1_NActualGear) // �Զ����ж�CAN
			{
				LightCtrlStManage.ReverseGear_SW = TRUE;
			}
			else
			{
				LightCtrlStManage.ReverseGear_SW = FALSE;
			}
		}
		else
		{
			LightCtrlStManage.ReverseGear_SW = FALSE;
		}
	}
	else
	{
		(TRUE == Hal_ADCGetCheckStPtr()->REVERSE_GEAR_SW)?(LightCtrlStManage.ReverseGear_SW = TRUE):(LightCtrlStManage.ReverseGear_SW = FALSE);
	}

	if((1U == LightCtrlStManage.ReverseGear_SW) && (IGNState_ON <= LightCtrlStManage.PowerMode))
	{
		ReverseLamp_OutputReq = enOutputReq_On;
	}
	else
	{
		ReverseLamp_OutputReq = enOutputReq_Off;
	}
}


/*******************************************************************************
* �������ƣ�LightCtrl_DaylightLight
* ����������ӭ���ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void LightCtrl_WelcomeLamp(void)
{
	strEepromLampOutdoorCtrlSys *EepLampParam;
	CarWorkMode_e PowerSyt;
	static INT8U PreAlarmSt;		/*��һ�ε����״̬:0�������1��ȫ�����2���������3��������4.������*/
	BcmDoorState0x361_t BcmDoorStInfo;
	static INT32U	LingtSystemTick=0;
	static INT8U	WelcomeLigtSt=0;
	static INT8U   PreRkeLockSt;
	static INT8U   PreDigtalLockSt;
	static INT8U   PreMechLockSt;
	//BcmLampState0x360_t LightCanInfo;


	EepLampParam = (strEepromLampOutdoorCtrlSys *)Srv_GetEepromWorkParaCfgPtr(EN_WORK_LAMP_OUTDOOR_CTRLSYS_TYPE);//��ȡ�������
	//Hal_CanBcmGetInfo(EN_CAN_MSG_BCM_LAMP_1,(INT8U*)&LightCanInfo,sizeof(LightCanInfo));
	if((EepLampParam->VehEnWelLampPrm != 1)||(EepLampParam->MstWelcomeLightPrm !=1))
	{
		LingtSystemTick =0;
		WelcomeLigtSt =0;
		Hal_HC595ChlStaCtrl(eWELCOME_LAMPS_AND_DOOR_HANDLE_LAMP_OUT,FALSE);
		return;
	}

	PowerSyt = (CarWorkMode_e)PKS_GetCurRunSta();
	Hal_CanBcmGetInfo(EN_CAN_MSG_BCM_DOOR_1,(INT8U*)&BcmDoorStInfo,sizeof(BcmDoorStInfo));
	if(((PowerSyt == CAR_WORK_MODE_ST_OFF)&&(((PreAlarmSt==1)||(PreAlarmSt ==2))&&(BcmDoorStInfo.BD1_StSecAlarm==0)))
		||(((PowerSyt == CAR_WORK_MODE_ST_ACC)||(PowerSyt == CAR_WORK_MODE_ST_ON))&&(DLockIsOneMaskValid(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK|PA_DOOR_AND_LOCK_ST_MASK)))
		)//||((EepLampParam->VehAVMWelcomeLightEnablePrm==1)&&()))  ��������
	{
		Hal_HC595ChlStaCtrl(eWELCOME_LAMPS_AND_DOOR_HANDLE_LAMP_OUT,TRUE);
		WelcomeLigtSt =1;
		if(LingtSystemTick==0)
		{
			LingtSystemTick = D_HAL_GET_CUR_MS_TS();
		}
	}



	if(WelcomeLigtSt == 1)
	{
		if(((PowerSyt == CAR_WORK_MODE_ST_OFF)&&((PreAlarmSt==0)&&(BcmDoorStInfo.BD1_StSecAlarm!=0)))
			||(((PowerSyt == CAR_WORK_MODE_ST_ACC)||(PowerSyt == CAR_WORK_MODE_ST_ON))&&(DLockIsOneMaskValid(LightCtrlStManage.DoorState,DR_DOOR_AND_LOCK_STE_MASK|PA_DOOR_AND_LOCK_ST_MASK)==FALSE))
			||(PowerSyt == CAR_WORK_MODE_ST_START))
		{
			Hal_HC595ChlStaCtrl(eWELCOME_LAMPS_AND_DOOR_HANDLE_LAMP_OUT,FALSE);
			WelcomeLigtSt =0;
			LingtSystemTick =0;
		}	

		if(PowerSyt == CAR_WORK_MODE_ST_OFF)
		{
			if((PreMechLockSt!= DLockIsOneMaskValid(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK))&&(DLockIsOneMaskValid(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK)== TRUE)
				||((PreDigtalLockSt!=LightCtrlStManage.CurrTboxDigitalLockSt)&&(LightCtrlStManage.CurrTboxDigitalLockSt == 1))
				||((PreRkeLockSt != LightCtrlStManage.CurrRkeOptCmd)&&(LightCtrlStManage.CurrRkeOptCmd ==RKE_OPT_CMD_UNLOCK)))
			{
				LingtSystemTick = D_HAL_GET_CUR_MS_TS();
			}
		}

		if(((PowerSyt == CAR_WORK_MODE_ST_OFF))&&(LingtSystemTick>0)&&(Hal_TimerDiffTs(LingtSystemTick)>30000))
		{
			Hal_HC595ChlStaCtrl(eWELCOME_LAMPS_AND_DOOR_HANDLE_LAMP_OUT,FALSE);
			WelcomeLigtSt =0;
			LingtSystemTick =0;
		}

		if(PowerSyt > CAR_WORK_MODE_ST_OFF)
		{
			LingtSystemTick = D_HAL_GET_CUR_MS_TS();
		}
	}

	PreAlarmSt = BcmDoorStInfo.BD1_StSecAlarm;
	PreRkeLockSt = LightCtrlStManage.CurrRkeOptCmd;
	PreDigtalLockSt = LightCtrlStManage.CurrTboxDigitalLockSt;
	PreMechLockSt = DLockIsOneMaskValid(LightCtrlStManage.DLockState,DR_DOOR_AND_LOCK_STE_MASK);
}



/*******************************************************************************
* �������ƣ�LightCtrl_DaylightLight
* ��������������г��ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_DaylightLight(void)
{
	// IO Control
	/*
	if(DescIOCtrl_enActive == DescIOCtl_Light_Active)
	{
		if(DescIOCtl_enLight_ON == DescIOCtl_Daylight_Cmd)
		{
			Daylight_OutputReq = enOutputReq_On;
		}
		else
		{
			Daylight_OutputReq = enOutputReq_Off;
		}

		return;
	}
	*/
	if((1U == GWBEms2Info.EMS2_StEngineRunning) || ((2U == GWBEMS5Info.EMS5_StEngineStatus) && (0U == GWBEMS5Info.EMS5_StSSRequest)))
	{
		LightCtrlStManage.RUN = 1U;
	}
	else
	{
		LightCtrlStManage.RUN = 0U;
	}

	// Normal Control
	if((IGNState_ON <= LightCtrlStManage.PowerMode) && (1U == LightCtrlStManage.RUN) && (enOutputSts_Off == LeftPosLight_OutputSts) &&\
	(enOutputSts_Off == RightPosLight_OutputSts) && (enOutputSts_Off == LowBeam_OutputSts) &&\
	(enOutputSts_Off == HighBeam_OutputSts) && (enOutputSts_Off == FogLamp_Front_OutputSts))//�����ռ��г���
	{
		if(enOutputSts_Off == Daylight_OutputSts)
		{
			Daylight_OutputReq = enOutputReq_On;
			Hal_LeftDayLightStart();
			Hal_RightDayLightStart();
			Daylight_OutputSts = enOutputSts_On;
		}
	}
	else
	{
		if(enOutputSts_On == Daylight_OutputSts)
		{
			Daylight_OutputReq = enOutputReq_Off;
			Hal_LeftDayLightStop();
			Hal_RightDayLightStop();
			Daylight_OutputSts = enOutputSts_Off;
		}
	}
}


/*******************************************************************************
* �������ƣ�LightCtrl_HazardSwLED
* ����������Σ�ձ�������ָʾ�ƿ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
*******************************************************************************/
void	LightCtrl_HazardSwLED(void)
{
	// �ӹ��ܹ淶�Ͽ����κ���ת��� �� ��ת���ͬʱ����ʱ��Σ�վ����ƶ�����)
	if((enOutputReq_On == TurnLampSts_Left_OutputReq) && (enOutputReq_On == TurnLampSts_Right_OutputReq))
	{
		HazardSwLED_OutputReq = enOutputReq_On;
	}
	else
	{
		HazardSwLED_OutputReq = enOutputReq_Off;
	}
}

static void LightCtrl_SSBLED(void)
{
	BOOL led1=FALSE, led2=FALSE, led3=FALSE;

	/*�����-��ɫ*/
	if(LightCtrlStManage.LightAlarmStStage == ALARM_ST_DISARM)
	{
		led1 = TRUE;
	}
	/*��ɫLED2*/
	if((LightCtrlStManage.PowerMode == EN_PKS_OPT_ACC) ||\
	(LightCtrlStManage.PowerMode == EN_PKS_OPT_ON))
	{
		if(LightCtrlStManage.EmsEngineRunningSt != EMS2_ST_ENGINERUNNING_EngineRun)
		{
			led2 = TRUE;
		}
	}
	/*��ɫLED3*/
	if(LightCtrlStManage.PowerMode != EN_PKS_OPT_OFF)
	{
		if(LightCtrlStManage.EmsEngineRunningSt == EMS2_ST_ENGINERUNNING_EngineRun)
		{
			led3 = TRUE;
		}
	}
	
	if(led1 == TRUE)
	{
		Led_LightOn(EN_LED_BACK);
	}
	else
	{
		Led_LightOff(EN_LED_BACK);
	}

	if(led2 == TRUE)
	{
		Led_LightOn(EN_LED_YELLOW);
	}
	else
	{
		Led_LightOff(EN_LED_YELLOW);
	}

	if(led3 == TRUE)
	{
		Led_LightOn(EN_LED_GREEN);
	}
	else
	{
		Led_LightOff(EN_LED_GREEN);
	}
}


static  void	LightCtrl_OutPut(void)
{
	static INT16U BrakeLightFlashTime = 0U;
//---------------- Position light output ---------------------------------------
	if(enOutputReq_On == LeftPosLight_OutputReq)                    // ��λ�õ����
	{
		Hal_PosLeftLightOn();
		LeftPosLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_PosLeftLightOff();
		LeftPosLight_OutputSts = enOutputSts_Off;
	}

	
	if(enOutputReq_On == RightPosLight_OutputReq)                    // ��λ�õ����
	{
		Hal_PosRightLightOn();
		RightPosLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_PosRightLightOff();
		RightPosLight_OutputSts = enOutputSts_Off;
	}

//---------------- LicenseLight output ---------------------------------------
	if(enOutputReq_On == LicenseLight_OutputReq)                    //���յ����
	{
		Hal_LicenseLightOn();
		LicenseLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_LicenseLightOff();
		LicenseLight_OutputSts = enOutputSts_Off;
	}

//---------------- Low beam output ---------------------------------------------
	if(enOutputReq_On == LowBeam_OutputReq) 				// ��������
	{
		Hal_LowBeamLeftLightOn();
		Hal_LowBeamRightLightOn();
		LowBeam_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_LowBeamLeftLightOff();
		Hal_LowBeamRightLightOff();
		LowBeam_OutputSts = enOutputSts_Off;
	}

//---------------- High beam output --------------------------------------------
	if(enOutputReq_On == HighBeam_OutputReq) 				// Զ������
	{
		Hal_HighBeamLeftLightOn();
		Hal_HighBeamRightLightOn();
		HighBeam_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_HighBeamLeftLightOff();
		Hal_HighBeamRightLightOff();
		HighBeam_OutputSts = enOutputSts_Off;
	}

//---------------- Turn lamp output --------------------------------------------
	if(enOutputReq_On == TurnLampSts_Left_OutputReq) 		// ��ת������
	{
		Hal_TurnLightLeftOn();
		TurnLampSts_Left_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_TurnLightLeftOff();
		TurnLampSts_Left_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == TurnLampSts_Right_OutputReq) 		// ��ת������
	{
		Hal_TurnLightRightOn();
		TurnLampSts_Right_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_TurnLightRightOff();
		TurnLampSts_Right_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == HazardSwLED_OutputReq) 		// ��ת������
	{
		Hal_HazardLEDOn();
		HazardSwLED_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_HazardLEDOff();
		HazardSwLED_OutputSts = enOutputSts_Off;
	}

//---------------- Daylight lamp output ----------------------------------------
/*	if(enOutputReq_On == Daylight_OutputReq) 				// ����г������
	{
		//Output_DaynightLightOn();
		Hal_GpioWriteCh(EN_RightDrlIN1_OUT, D_OUT_VALID);
		Hal_GpioWriteCh(EN_LeftDrlIN0_OUT, D_OUT_VALID);
		
		Daylight_OutputSts = enOutputSts_On;
	}
	else
	{
		//Output_DaynightLightOff();
		Hal_GpioWriteCh(EN_RightDrlIN1_OUT, D_OUT_INVALID);
		Hal_GpioWriteCh(EN_LeftDrlIN0_OUT, D_OUT_INVALID);
		Daylight_OutputSts = enOutputSts_Off;
	}
*/
//---------------- fog lamp output ---------------------------------------------
	if(enOutputReq_On == FogLamp_Front_OutputReq) // ǰ��Ƶ����
	{
		Hal_FrontFogLeftLightOn();
		Hal_FrontFogRightLightOn();
		FogLamp_Front_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_FrontFogLeftLightOff();
		Hal_FrontFogRightLightOff();
		FogLamp_Front_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == FogLamp_Rear_OutputReq) // �����
	{
		Hal_RearFogLightOn();
		FogLamp_Rear_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_RearFogLightOff();
		FogLamp_Rear_OutputSts = enOutputSts_Off;
	}


//---------------- Brake lamp output -------------------------------------------
	if(enOutputReq_On == BrakeLamp_OutputReq) // ������
	{
		Hal_ChmslLightOn();
		BrakeLightFlashTime = 0U;
		BrakeLamp_OutputSts = enOutputSts_On;
	}
	else if(enOutputReq_FLASH == BrakeLamp_OutputReq)
	{
		BrakeLightFlashTime++;
		if(BrakeLightFlashTime< D_Time_125MS)
		{
			Hal_ChmslLightOn();
		}
		else if(BrakeLightFlashTime < D_Time_250MS)
		{
			Hal_ChmslLightOff();
		}
		else
		{
			BrakeLightFlashTime = 0U;
		}
			
		BrakeLamp_OutputSts = enOutputSts_On;
	}
	else
	{
		BrakeLightFlashTime = 0U;
		Hal_ChmslLightOff();
		BrakeLamp_OutputSts = enOutputSts_Off;
	}

//---------------- Reversed lamp output ----------------------------------------
	if(enOutputReq_On == ReverseLamp_OutputReq) // ������
	{
		Hal_ReversingLightOn();
		ReverseLamp_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_ReversingLightOff();
		ReverseLamp_OutputSts = enOutputSts_Off;
	}

//---------------- corner lamp output ------------------------------------------
	if(enOutputReq_On == LeftAssistLight_OutputReq) // ��ǵ����
	{
		Hal_CornerLeftLightOn();
		LeftAssistLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_CornerLeftLightOff();
		LeftAssistLight_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == RightAssistLight_OutputReq) 			// �ҽǵ����
	{
		Hal_CornerRightLightOn();
		RightAssistLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_CornerRightLightOff();
		RightAssistLight_OutputSts = enOutputSts_Off;
	}
}


static void LightCtrl_UpLoadInfoToCanAndOutput(void)
{
	static INT16U BrakeLightFlashTime = 0U;
	BcmLampState0x360_t LightCanInfo;

	Bcm3StInfo0x364_t 	LightCanInfoTips;
	
	
	INT8U IBCM_St_PositionLampCommandL = 0U;
	INT8U IBCM_St_PositionLampCommandR = 0U;
	
	INT8U IBCM_St_LowBeamCommandR = 0U;
	INT8U IBCM_St_LowBeamCommandL = 0U;
	
	INT8U IBCM_St_HighBeamCommandR = 0U;
	INT8U IBCM_St_HighBeamCommandL = 0U;

	INT8U IBCM_St_DirLampCommandL = 0U;
	INT8U IBCM_St_DirLampCommandR = 0U;
	INT8U IBCM_St_DirLampFlowCommandL = 0U;
	INT8U IBCM_St_DirLampFlowCommandR = 0U;

	INT8U BCMLC3_St_CornerlampL = 0U;
	INT8U BCMLC3_St_CornerlampR = 0U;

	INT8U IBCM_St_DayRunningLampCommandL = 0U;
	INT8U IBCM_St_DayRunningLampCommandR = 0U;
	INT8U BCMLC3_St_DayRunningBreathLampL = 0U;
	INT8U BCMLC3_St_DayRunningBreathLampR = 0U;
	
	Hal_CanBcmGetInfo(EN_CAN_MSG_BCM_LAMP_1,(INT8U*)&LightCanInfo,sizeof(LightCanInfo));
	Hal_CanBcmGetInfo(EN_CAN_MSG_BCM_3,(INT8U*)&LightCanInfoTips,sizeof(LightCanInfoTips));

	LightCanInfoTips.BCM3_WPosLightNotClose = BCM3_W_PosLightNotClose;
	LightCanInfoTips.BCM3_StComingHome = BCM3_St_ComingHome;
	LightCanInfoTips.BCM3_StLeavingHome = BCM3_St_LeavingHome;

	//LightCanInfoTips.BCM3_StHMA = BCM3_St_HMA;
	LightCanInfo.LA1_StHMAAvailable = LA1_St_HMAAvailable;

	LightCanInfo.LA1_StTrunkLamp = LA1_St_TrunkLamp;
	LightCanInfo.LA1_StDimmer = LA1_St_Dimmer;
	if((0U < LightCtrlStManage.ICMS1_N_DimmSw) && (16U > LightCtrlStManage.ICMS1_N_DimmSw))
	{
		LightCanInfo.LA1_NDimmSw = LightCtrlStManage.ICMS1_N_DimmSw - 1U;
	}
	//---------------- Position light output ---------------------------------------

	LightCanInfo.LA1_StPosLampL = 0U;
	LightCanInfo.LA1_StPosLampR = 0U;
	LightCanInfo.LA1_StPosLamp = 0U;
	if(enOutputReq_On == LeftPosLight_OutputReq)                    // ��λ�õ����
	{
		Hal_PosLeftLightOn();
		LeftPosLight_OutputSts = enOutputSts_On;
		if(D_ExlFPosLampsDiagtypePrm_LIN != LightCtrlStManage.ExlFPosLampsDiagtypePrm)
		{	
			if(PositionFunction)
			{
				LightCanInfo.LA1_StPosLampL = 0U;
				LightCanInfo.LA1_StPosLampR = 0U;
				LightCanInfo.LA1_StPosLamp = 1U;
			}
			else
			{
				if(HoldFunction)
				{
					if(enTurnSw_Left == LightCtrlStManage.TurnLightSwSts)
					{
						LightCanInfo.LA1_StPosLampL = 1U;
					}
					else if(enTurnSw_Right == LightCtrlStManage.TurnLightSwSts)
					{
						LightCanInfo.LA1_StPosLampR = 1U;
					}
				}
				
			}
			
		}
		else
		{
			if(PositionFunction)
			{
				LightCanInfo.LA1_StPosLampL = 0U;
				LightCanInfo.LA1_StPosLampR = 0U;
				LightCanInfo.LA1_StPosLamp = 1U;
				
				IBCM_St_PositionLampCommandL = 1U;
				IBCM_St_PositionLampCommandR = 1U;
			}
			else 
			{
				if(HoldFunction)
				{
					if(enTurnSw_Left == LightCtrlStManage.TurnLightSwSts)
					{
						LightCanInfo.LA1_StPosLampL = 1U;
						IBCM_St_PositionLampCommandL = 1U;
					}
					else if(enTurnSw_Right == LightCtrlStManage.TurnLightSwSts)
					{
						LightCanInfo.LA1_StPosLampR = 1U;
						IBCM_St_PositionLampCommandR = 1U;
					}
				}
			}
			
		}
	}
	else
	{
		if(PositionFunction)
		{
			LightCanInfo.LA1_StPosLamp = 0U;
		}
		else if(HoldFunction)
		{
			LightCanInfo.LA1_StPosLamp = 0U;

			IBCM_St_PositionLampCommandL = 0U;

			IBCM_St_PositionLampCommandR = 0U;
		}
		Hal_PosLeftLightOff();
		LeftPosLight_OutputSts = enOutputSts_Off;
	}

	
	if(enOutputReq_On == RightPosLight_OutputReq)                    // ��λ�õ����
	{
		Hal_PosRightLightOn();
		RightPosLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_PosRightLightOff();
		RightPosLight_OutputSts = enOutputSts_Off;
	}

//---------------- LicenseLight output ---------------------------------------
	if(enOutputReq_On == LicenseLight_OutputReq)                    //���յ����
	{
		Hal_LicenseLightOn();
		LicenseLight_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_LicenseLightOff();
		LicenseLight_OutputSts = enOutputSts_Off;
	}

//---------------- Low beam output ---------------------------------------------
	if(enOutputReq_On == LowBeam_OutputReq) 				// ��������
	{
		LightCanInfo.LA1_StLowBean = 1U;
		if(D_VehLowBeamType_LIN != LightCtrlStManage.VehLowBeamTypePrm)
		{
			Hal_LowBeamLeftLightOn();
			Hal_LowBeamRightLightOn();
			
		}
		else
		{
			IBCM_St_LowBeamCommandR = 1U;
			IBCM_St_LowBeamCommandL = 1U;
		}
		LowBeam_OutputSts = enOutputSts_On;
		
	}
	else
	{
		LightCanInfo.LA1_StLowBean = 0U;
		IBCM_St_LowBeamCommandR = 0U;
		IBCM_St_LowBeamCommandL = 0U;
		Hal_LowBeamLeftLightOff();
		Hal_LowBeamRightLightOff();
		LowBeam_OutputSts = enOutputSts_Off;
	}

	if(D_VehExLampSwTypePrm_Hard == LightCtrlStManage.VehExLampSwTypePrm)
	{
		LightCanInfoTips.BCM3_StLowBeamSwEn = 0U;
		LightCanInfoTips.BCM3_StFrontFogSwEn = 0U;
		LightCanInfoTips.BCM3_StRearFogSwEn = 0U;
	}
	else
	{
		if(IGNState_ON <= LightCtrlStManage.PowerMode)
		{
			LightCanInfoTips.BCM3_StLowBeamSwEn = 1U;
		}
		else
		{	
			LightCanInfoTips.BCM3_StLowBeamSwEn = 0U;
		}
		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((enOutputReq_On == LeftPosLight_OutputReq) || (enOutputReq_On == RightPosLight_OutputReq)))
		{
			LightCanInfoTips.BCM3_StFrontFogSwEn = 1U;
		}
		else
		{
			LightCanInfoTips.BCM3_StFrontFogSwEn = 0U;
		}
		if((IGNState_ON <= LightCtrlStManage.PowerMode) && ((enOutputReq_On == FogLamp_Front_OutputReq) || (enOutputReq_On == LowBeam_OutputReq)))
		{
			LightCanInfoTips.BCM3_StRearFogSwEn = 1U;
		}
		else
		{
			LightCanInfoTips.BCM3_StRearFogSwEn = 0U;
		}
	}
	LightCanInfoTips.BCM3_StExLampCommand = Hal_ADCGetCheckStPtr()->HeadLightSW;
//---------------- High beam output --------------------------------------------
	if(enOutputReq_On == HighBeam_OutputReq) 				// Զ������
	{
		LightCanInfo.LA1_StHighBean = 1U;
		if(D_VehHighBeamType_LIN != LightCtrlStManage.VehHighBeamTypePrm)
		{
			Hal_HighBeamLeftLightOn();
			Hal_HighBeamRightLightOn();
		}
		else
		{
			IBCM_St_HighBeamCommandR = 1U;
			IBCM_St_HighBeamCommandL = 1U;
		}
		
		HighBeam_OutputSts = enOutputSts_On;
	}
	else
	{
		LightCanInfo.LA1_StHighBean = 0U;
		IBCM_St_HighBeamCommandR = 0U;
		IBCM_St_HighBeamCommandL = 0U;
		Hal_HighBeamLeftLightOff();
		Hal_HighBeamRightLightOff();
		HighBeam_OutputSts = enOutputSts_Off;
	}
	if(HMALightFunction)
	{
		if(LightCtrlStManage.AutoSw)
		{
			LightCanInfo.LA1_StAutoFrontLight = 1U;
		}
		else
		{
			LightCanInfo.LA1_StAutoFrontLight = 0U;
		}	
	}
	 
//---------------- Turn lamp output --------------------------------------------
	if(enOutputReq_On == TurnLampSts_Left_OutputReq) 		// ��ת������
	{
		LightCanInfo.LA1_StDirectionLampL = 1U;
		Hal_TurnLightLeftOn();
		if(D_ExlFrontDirLampsDiagtypePrm_LIN == LightCtrlStManage.ExlFrontDirLampsDiagtypePrm)
		{
			IBCM_St_DirLampCommandL = 1U;
			IBCM_St_DirLampFlowCommandL = 1U;
		}
		
		TurnLampSts_Left_OutputSts = enOutputSts_On;
	}
	else
	{	
		LightCanInfo.LA1_StDirectionLampL = 0U;

		IBCM_St_DirLampCommandL = 0U;
		IBCM_St_DirLampFlowCommandL = 0U;
			
		Hal_TurnLightLeftOff();
		TurnLampSts_Left_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == TurnLampSts_Right_OutputReq) 		// ��ת������
	{
		LightCanInfo.LA1_StDirectionLampR = 1U;
		Hal_TurnLightRightOn();
		if(D_ExlFrontDirLampsDiagtypePrm_LIN == LightCtrlStManage.ExlFrontDirLampsDiagtypePrm)
		{
			IBCM_St_DirLampCommandR = 1U;
			IBCM_St_DirLampFlowCommandR = 1U;
		}
		TurnLampSts_Right_OutputSts = enOutputSts_On;
	}
	else
	{
		LightCanInfo.LA1_StDirectionLampR = 0U;

		IBCM_St_DirLampCommandR = 0U;
		IBCM_St_DirLampFlowCommandR = 0U;
			
		Hal_TurnLightRightOff();
		TurnLampSts_Right_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == HazardSwLED_OutputReq) 		// Σ�վ��������
	{
		Hal_HazardLEDOn();
		HazardSwLED_OutputSts = enOutputSts_On;
		LightCanInfo.LA1_StHazardWarning = 1U;
	}
	else
	{
		Hal_HazardLEDOff();
		HazardSwLED_OutputSts = enOutputSts_Off;
		LightCanInfo.LA1_StHazardWarning = 0U;
	}

//---------------- Daylight lamp output ----------------------------------------
	if(enOutputReq_On == Daylight_OutputReq) 				// ����г������
	{
		LightCanInfo.LA1_StDayRunLampL = 1U;
		LightCanInfo.LA1_StDayRunLampR = 1U;
		if(D_VehEnDRLPrm_Hard == LightCtrlStManage.VehEnDRLPrm)
		{
			
		}
		else if(D_VehEnDRLPrm_LIN == LightCtrlStManage.VehEnDRLPrm)
		{
			 IBCM_St_DayRunningLampCommandL = 1U;
			 IBCM_St_DayRunningLampCommandR = 1U;
			 BCMLC3_St_DayRunningBreathLampL = 0U;
			 BCMLC3_St_DayRunningBreathLampR = 0U;
		}
	}
	else
	{
		LightCanInfo.LA1_StDayRunLampL = 0U;
		LightCanInfo.LA1_StDayRunLampR = 0U;
		IBCM_St_DayRunningLampCommandL = 0U;
		IBCM_St_DayRunningLampCommandR = 0U;
		BCMLC3_St_DayRunningBreathLampL = 0U;
		BCMLC3_St_DayRunningBreathLampR = 0U;
	}

//---------------- fog lamp output ---------------------------------------------
	if(enOutputReq_On == FogLamp_Front_OutputReq) // ǰ��Ƶ����
	{
		Hal_FrontFogLeftLightOn();
		Hal_FrontFogRightLightOn();
		LightCanInfo.LA1_StFRFogLamp = 1U;
		LightCanInfo.LA1_StFLFogLamp = 1U;
		FogLamp_Front_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_FrontFogLeftLightOff();
		Hal_FrontFogRightLightOff();
		LightCanInfo.LA1_StFRFogLamp = 0U;
		LightCanInfo.LA1_StFLFogLamp = 0U;
		FogLamp_Front_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == FogLamp_Rear_OutputReq) // �����
	{
		Hal_RearFogLightOn();
		LightCanInfo.LA1_StRFogLamp = 1U;
		FogLamp_Rear_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_RearFogLightOff();
		LightCanInfo.LA1_StRFogLamp = 0U;
		FogLamp_Rear_OutputSts = enOutputSts_Off;
	}


//---------------- Brake lamp output -------------------------------------------
	if(enOutputReq_On == BrakeLamp_OutputReq) // ɲ����
	{
		Hal_ChmslLightOn();
		BrakeLightFlashTime = 0U;
		LightCanInfo.LA1_StBrakeLamp = 1U;
		BrakeLamp_OutputSts = enOutputSts_On;
	}
	else if(enOutputReq_FLASH == BrakeLamp_OutputReq)
	{
		BrakeLightFlashTime++;
		if(BrakeLightFlashTime< D_Time_125MS)
		{
			Hal_ChmslLightOn();
		}
		else if(BrakeLightFlashTime < D_Time_250MS)
		{
			Hal_ChmslLightOff();
		}
		else
		{
			BrakeLightFlashTime = 0U;
		}
		LightCanInfo.LA1_StBrakeLamp = 1U;
		BrakeLamp_OutputSts = enOutputSts_On;
	}
	else
	{
		LightCanInfo.LA1_StBrakeLamp = 0U;
		BrakeLightFlashTime = 0U;
		Hal_ChmslLightOff();
		BrakeLamp_OutputSts = enOutputSts_Off;
	}

//---------------- Reversed lamp output ----------------------------------------
	if(enOutputReq_On == ReverseLamp_OutputReq) // ������
	{
		Hal_ReversingLightOn();
		LightCanInfo.LA1_StReverseLamp = 1U;
		ReverseLamp_OutputSts = enOutputSts_On;
	}
	else
	{
		Hal_ReversingLightOff();
		LightCanInfo.LA1_StReverseLamp = 0U;
		ReverseLamp_OutputSts = enOutputSts_Off;
	}

//---------------- corner lamp output ------------------------------------------
	if(enOutputReq_On == LeftAssistLight_OutputReq) // ��ǵ����
	{
		
		LeftAssistLight_OutputSts = enOutputSts_On;

		if(D_MainOrDiAssistLight_TurnBeam == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{
			Hal_CornerLeftLightOn();
			LightCanInfo.LA1_StAssistBeamL = 1U;
		}
		else if(D_MainOrDiAssistLight_HighBeam == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{	
			Hal_CornerLeftLightOn();
			LightCanInfo.LA1_StAssistBeamL = 1U;
		}
		else if(D_MainOrDiAssistLight_LIN == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{
			BCMLC3_St_CornerlampL = 1U;
		}
	}
	else
	{
		Hal_CornerLeftLightOff();
		LightCanInfo.LA1_StAssistBeamL = 0U;
		BCMLC3_St_CornerlampL = 0U;
		LeftAssistLight_OutputSts = enOutputSts_Off;
	}

	if(enOutputReq_On == RightAssistLight_OutputReq) 			// �ҽǵ����
	{
		
		RightAssistLight_OutputSts = enOutputSts_On;
		if(D_MainOrDiAssistLight_TurnBeam == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{
			Hal_CornerRightLightOn();
			LightCanInfo.LA1_StAssistBeamR = 1U;
		}
		else if(D_MainOrDiAssistLight_HighBeam == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{	
			Hal_CornerRightLightOn();
			LightCanInfo.LA1_StAssistBeamR = 1U;
		}
		else if(D_MainOrDiAssistLight_LIN == LightCtrlStManage.ExlMainOrDiAssistLightPrm)
		{
			BCMLC3_St_CornerlampR = 1U;
		}
	}
	else
	{
		Hal_CornerRightLightOff();
		LightCanInfo.LA1_StAssistBeamR = 0U;
		BCMLC3_St_CornerlampR = 0U;
		RightAssistLight_OutputSts = enOutputSts_Off;
	}
	
	Hal_CanBcmUpdateInfo(EN_CAN_MSG_BCM_LAMP_1,(INT8U*)&LightCanInfo,sizeof(LightCanInfo));
	Hal_CanBcmUpdateInfo(EN_CAN_MSG_BCM_3,(INT8U*)&LightCanInfoTips,sizeof(LightCanInfoTips));

}


static ST_Task_SleepWork_Status LightCtrl_SleepWorkStatus = {0};
static TaskStatusInfo_t LightCtrl_TaskSta = EN_TASK_INIT;

/*******************************************************************************
* �������ƣ�LightCtrl_Task
* �����������ƹ��������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��10ms����
*******************************************************************************/
void	LightCtrl_Task(void)
{
	static INT32U Ts = 0U;
	if(Hal_TimerDiffTs(Ts) >= D_LightCtrlTask_Period)
	{
		Ts = D_HAL_GET_CUR_MS_TS();

		PWRCHECK_Task();//ϵͳ��Դ��ѹ�ж�

/* simulink Algorithm will be generated here[begin] */
        InputDataProcess_step();
        untitled1_step();
        untitled2_step();
        Rte_get_ExLamp_step();
        Rte_set_ExLamp_step();
        RrWiperWashCtrl_step();
        Rte_get_Light_step();
        LightCtrl_step();
/* simulink Algorithm will be generated here[end] */


		LightCtrl_UpdateInputInfo();
	
		LightCtrl_IP_Illumination();		//����ƿ���
		LightCtrl_LightForBatterySaver(); 	// ���ر���
		LightCtrl_DomeLight();				// ����ƿ���
		LightCtrl_OpenDoorLight();			// �ſ������ƿ���
		LightCtrl_AmbienceLight();
		LightCtrl_PuddleLamp();				// ˮ�ӵƿ���
		LightCtrl_PRNDIndication();			// PRNDָʾ
		
		LightCtrl_PositionLight(); 		// λ�õƿ���
		LightCtrl_ReverseLamp();		// �����ƿ���
		LightCtrl_Headlight();     		// ǰ�յƿ���(����Զ�����)

		LightCtrl_FogLight(); 			// ��ƿ���
		LightCtrl_TurnLight();			// ת��ƿ���
		LightCtrl_BrakeLamp();          // ɲ���ƿ���
		LightCtrl_AssistLamp();			// �ǵƿ���
		LightCtrl_DaylightLight();		// ����г��ƿ���
		LightCtrl_WelcomeLamp();		//ӭ���ƿ���
		
		LightCtrl_HazardSwLED();        // Σ�ձ�������ָʾ�ƿ���
		LightCtrl_SSBLED(); /*SSB ledָʾ��*/

		//LightCtrl_LightForceSleep();		// �ƹ�ǿ�����ߴ���
		

		LightCtrl_UpLoadInfoToCanAndOutput();
	}
}

static void LightCtrl_Init(void);
static void LightCtrl_TaskServices(void);
static BOOL LightCtrl_TaskIsPermitSleepOrNot(void);
static BOOL LightCtrl_TaskIsReadySleepOrNot(void);
static BOOL LightCtrl_TaskIsWorkingOrNot(void);
static void LightCtrl_TaskMandatoryExit(void);

/*! @brief ������� */
const ST_TaskInfo LightCtrl_TaskInfo =
{
	EN_TASK_ID_SRV_LIGHT,
	LightCtrl_Init,
	LightCtrl_TaskServices,
	LightCtrl_TaskIsPermitSleepOrNot,
	LightCtrl_TaskIsReadySleepOrNot,
	LightCtrl_TaskIsWorkingOrNot,
	LightCtrl_TaskMandatoryExit
};

static void LightCtrl_Init(void)
{
    LightCtrl_TaskSta = EN_TASK_INIT;
    LightCtrl_SleepWorkStatus.Is_Permit_Sleep_Status = FALSE;
    LightCtrl_SleepWorkStatus.Is_Ready_Sleep_Status = FALSE;
    LightCtrl_SleepWorkStatus.Is_Working_Status = FALSE; 
    LightCtrlPara_Init();
	Hal_LightInit();

/* simulink initialize will be generated here[begin] */
    Rte_get_Light_initialize();
    LightCtrl_initialize();
/* simulink initialize will be generated here[end] */

}

static void LightCtrl_TaskServices(void)
{
    switch (LightCtrl_TaskSta)
    {
        case EN_TASK_INIT:
			LightCtrl_Init();
			PWRCHECK_Init();
            LightCtrl_TaskSta = EN_TASK_RUNNING;
            break;
            
        case EN_TASK_RUNNING:
            LightCtrl_Task();
            break;
            
        case EN_TASK_SLEEP:
        case EN_TASK_EXIT:
        default: /* task exit */
            break;
    }
}

static BOOL LightCtrl_TaskIsPermitSleepOrNot(void)
{
    return LightCtrl_SleepWorkStatus.Is_Permit_Sleep_Status;
}


static BOOL LightCtrl_TaskIsReadySleepOrNot(void)
{
    return LightCtrl_SleepWorkStatus.Is_Ready_Sleep_Status;
}

static BOOL LightCtrl_TaskIsWorkingOrNot(void)
{
    return LightCtrl_SleepWorkStatus.Is_Working_Status;
}


static void LightCtrl_TaskMandatoryExit(void)
{
    
}


INT8U	LightCtrl_GetIlluminationLevel(void)
{
	return LightCtrlStManage.ICMS1_N_DimmSw;
}

INT8U LightCtrl_GetLowBeamOptType(void)
{
	INT8U State=0;

	if(NearLightFunction == TRUE)
	{
		State =1; 
	}
	else if(AutoLightFunction == TRUE)
	{
		State =2; 
	}
	else if(AutoFollowLightFunction == TRUE)
	{
		State =3; 
	}
	else if(AutoLeaveLightFunction == TRUE)
	{
		State =4; 
	}
	else if(SpeedLightFunction == TRUE)
	{
		State =5;
	}
	return State;
}


INT8U LightCtrl_GetDirLightType(void)
{
	INT8U State=0;

	if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_HazardEmergency)
	{
		State = 8;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_TurnLeft)
	{
		State = 6;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_TurnRight)
	{
		State = 7;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_SetAlarmSuccess)
	{
		State = 0x0E;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_Emergency)
	{
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_CancelAlarmSuccess)
	{
		State = 0x0D;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_RemoteSearchCar)
	{
		State = 0x01;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_ShortRemoteTrunk)
	{
		State = 0x02;
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_ThiefWarning)
	{
		
	}
	else if(TurnLightOp.CurTurnLightCtrlMode == enCtrlMode_EmergencyBrake)
	{
		State = 0x0B;
	}

	return State;
}
























































