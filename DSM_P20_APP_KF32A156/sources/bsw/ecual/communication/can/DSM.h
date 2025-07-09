/**************************************************************
* Author:           JeanYuan
* Copyright (c) 2013-2020 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved. 
*  generated :Thu Nov 28 14:49:52 2024

**************************************************************/
#ifndef DSM_H
#define DSM_H
#include  "v_def.h"


/**************************************************************/
/* Signal structures                                          */ 
/**************************************************************/

/* Send messages */

typedef struct {
	canbittype 	DSM_DriverHeatStopReason: 4;
	canbittype 	unused0: 1;
	canbittype 	DSM_DriverHeatRunType: 2;
	canbittype 	DSM_RemoteStatus: 1;
	canbittype 	DSM_PassengerHeatStopReason: 4;
	canbittype 	unused1: 1;
	canbittype 	DSM_PassengerHeatRunType: 2;
	canbittype 	DSM_EngineRunStatus: 1;
	canbittype 	DSM_DriverVentilateStopReason: 4;
	canbittype 	unused2: 1;
	canbittype 	DSM_DriverVentRunType: 2;
	canbittype 	VehicleRunStatus: 1;
	canbittype 	DSM_PassengerVentilateStopReason: 4;
	canbittype 	unused3: 1;
	canbittype 	DSM_PassengerVentRunType: 2;
	canbittype 	unused4: 1;
	canbittype 	DSM_WheelHeatStopReason: 4;
	canbittype 	unused5: 1;
	canbittype 	DSM_SteerWheelHeatRunType: 2;
	canbittype 	unused6: 1;
	canbittype 	DSM_ECUVot: 8;
	canbittype 	unused7: 1;
	canbittype 	DSM_CarPowerMode: 3;
	canbittype 	DSM_PassengerMoveType: 4;
	canbittype 	DSM_DrHeightLockSts: 1;
	canbittype 	DSM_DrLengthLockSts: 1;
	canbittype 	DSM_DrBackLockSts: 1;
	canbittype 	DSM_DrFrontLockSts: 1;
	canbittype 	DSM_PaLengthLockSts: 1;
	canbittype 	DSM_PaBackLockSts: 1;
	canbittype 	unused8: 2;
}_c_DSM_0x502_msgType;

typedef struct {
	canbittype 	DSM_DriverHeightMoveReason: 5;
	canbittype 	DSM_DriverHeightCMD: 2;
	canbittype 	DSM_DriverHeightUPSW: 1;
	canbittype 	DSM_DriverLengthMoveReason: 5;
	canbittype 	DSM_DriverLengthCMD: 2;
	canbittype 	DSM_DriverHeightDNSW: 1;
	canbittype 	DSM_DriverBackMoveReason: 5;
	canbittype 	DSM_DriverBackCMD: 2;
	canbittype 	DSM_DriverLengthUPSW: 1;
	canbittype 	DSM_DriverFrontMoveReason: 5;
	canbittype 	DSM_DriverFrontCMD: 2;
	canbittype 	DSM_DriverLengthDNSW: 1;
	canbittype 	DSM_PassengerLengthMoveReason: 5;
	canbittype 	DSM_PassengerLengthCMD: 2;
	canbittype 	DSM_DriverBackUPSW: 1;
	canbittype 	DSM_PassengerBackMoveReason: 5;
	canbittype 	DSM_PassengerBackCMD: 2;
	canbittype 	DSM_DriverBackDNSW: 1;
	canbittype 	DSM_DriverFrontUPSW: 1;
	canbittype 	DSM_DriverFrontDNSW: 1;
	canbittype 	DSM_PassengerLengthUPSW: 1;
	canbittype 	DSM_PassengerLengthDNSW: 1;
	canbittype 	DSM_PassengerBackUPSW: 1;
	canbittype 	DSM_PassengerBackDNSW: 1;
	canbittype 	DSM_PassengerLengthLearnSts: 1;
	canbittype 	DSM_PassengerBackLearnSts: 1;
	canbittype 	DSM_DriverHeightLearnSt: 1;
	canbittype 	DSM_DriverLengthLearnSts: 1;
	canbittype 	DSM_DriverBackLearnSts: 1;
	canbittype 	DSM_DriverFrontLearnSts: 1;
	canbittype 	DSM_DriverMoveType: 4;
}_c_DSM_0x501_msgType;

typedef struct {
	canbittype 	DSM_DrNtcValue_1: 8;
	canbittype 	DSM_DrNtcValue_0: 8;
	canbittype 	DSM_PaNtcValue_1: 8;
	canbittype 	DSM_PaNtcValue_0: 8;
	canbittype 	DSM_SteerNtcValue_1: 8;
	canbittype 	DSM_SteerNtcValue_0: 8;
	canbittype 	unused0: 8;
	canbittype 	unused1: 8;
}_c_DSM_2_msgType;

typedef struct {
	canbittype 	DSM_FLSeatPosMsg: 1;
	canbittype 	DSM_FRSeatPosMsg: 1;
	canbittype 	DSM1_FLSeatMem1Sts: 3;
	canbittype 	DSM_FLSeatMemStsAndMsg: 3;
	canbittype 	DSM3_FLSeatMem3Sts: 3;
	canbittype 	DSM2_FLSeatMem2Sts: 3;
	canbittype 	DSM_St_FLSeatmeet: 2;
	canbittype 	unused0: 2;
	canbittype 	DSM1_FRSeatMem1Sts: 3;
	canbittype 	DSM_FRSeatMemStsAndMsg: 3;
	canbittype 	DSM_St_FRSeatmeet: 2;
	canbittype 	DSM2_FRSeatMem3Sts: 3;
	canbittype 	DSM2_FRSeatMem2Sts: 3;
	canbittype 	DSM_St_PasSeatHeatGear: 2;
	canbittype 	DSM_St_PasSeatHeatSW: 2;
	canbittype 	DSM_St_DriSeatHeatGear: 2;
	canbittype 	DSM_St_DriSeatHeatSW: 2;
	canbittype 	unused1: 4;
	canbittype 	DSM_St_DriSeatVentilationGear: 2;
	canbittype 	DSM_St_DriSeatVentilationSW: 2;
	canbittype 	DSM_MassageMode_FB: 4;
	canbittype 	DSM_St_PasSeatVentilationGear: 2;
	canbittype 	DSM_St_PasSeatVentilationSW: 2;
	canbittype 	IntelligentPowerDown_FB: 1;
	canbittype 	DSM_NapMode_FB: 2;
	canbittype 	DSM_MassageLevel_FB: 3;
	canbittype 	DSM_SwsHeatSts: 2;
}_c_DSM_msgType;

/* Receive messages */

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 8;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 8;
	canbittype 	unused5: 1;
	canbittype 	IVI_NapMode_SwtichSet: 2;
	canbittype 	unused6: 5;
	canbittype 	unused7: 8;
	canbittype 	unused8: 8;
}_c_IVI4_msgType;

typedef struct {
	canbittype 	IVI_St_FLSeatmeet: 2;
	canbittype 	IVI_FLSeatMemSet3: 2;
	canbittype 	IVI_FLSeatMemSet2: 2;
	canbittype 	IVI_FLSeatMemSet1: 2;
	canbittype 	IVI_St_FRSeatmeet: 2;
	canbittype 	IVI_FRSeatMemSet3: 2;
	canbittype 	IVI_FRSeatMemSet2: 2;
	canbittype 	IVI_FRSeatMemSet1: 2;
	canbittype 	unused0: 2;
	canbittype 	IVI_FRSeatHeatSet: 3;
	canbittype 	IVI_FLSeatHeatSet: 3;
	canbittype 	unused1: 2;
	canbittype 	IVI_FRSeatVentnSet: 3;
	canbittype 	IVI_FLSeatVentnSet: 3;
	canbittype 	unused2: 3;
	canbittype 	IVI_MassageLevel_Req: 3;
	canbittype 	IVI_SwsHeatSw: 1;
	canbittype 	unused3: 1;
	canbittype 	unused4: 4;
	canbittype 	IVI_MassageMode_Req: 4;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
}_c_IVI8_DSM_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 8;
	canbittype 	unused2: 8;
	canbittype 	unused3: 4;
	canbittype 	VCU_VehRunSta: 2;
	canbittype 	unused4: 2;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
	canbittype 	unused8: 8;
}_c_VCU1_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 8;
	canbittype 	unused2: 6;
	canbittype 	ECMD_EngineStatus: 2;
	canbittype 	unused3: 8;
	canbittype 	unused4: 8;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
}_c_GWB1_msgType;

typedef struct {
	canbittype 	unused0: 5;
	canbittype 	BDC_FRDoorSts: 1;
	canbittype 	BDC_FLDoorSts: 1;
	canbittype 	unused1: 1;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 8;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
	canbittype 	unused8: 8;
}_c_BDC3_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 8;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 3;
	canbittype 	ABS_VehicleSpeedValid: 1;
	canbittype 	unused5: 4;
	canbittype 	ABS_VehicleSpeed_1: 8;
	canbittype 	ABS_VehicleSpeed_0: 8;
	canbittype 	unused6: 8;
}_c_ABS1_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 5;
	canbittype 	BDC_PDU: 3;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 3;
	canbittype 	BDC_TboxRemoteControlSt: 1;
	canbittype 	unused5: 4;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
	canbittype 	unused8: 8;
}_c_BDC6_PEPS1_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	unused1: 2;
	canbittype 	BDC_TBOX_Req_Steeringwheel_heating: 2;
	canbittype 	unused2: 4;
	canbittype 	unused3: 8;
	canbittype 	BDC_IntelligentPowerDown_Sta: 1;
	canbittype 	unused4: 7;
	canbittype 	unused5: 8;
	canbittype 	BDC_TBOX_Req_PaSeatHeating: 3;
	canbittype 	BDC_TBOX_Req_DrSeatHeating: 3;
	canbittype 	unused6: 2;
	canbittype 	unused7: 2;
	canbittype 	BDC_TBOX_Req_PaSeatVentilating: 3;
	canbittype 	BDC_TBOX_Req_DrSeatVentilating: 3;
	canbittype 	unused8: 8;
}_c_BDC5_msgType;

typedef struct {
	canbittype 	unused0: 2;
	canbittype 	VCU_GearSelDisp: 4;
	canbittype 	unused1: 2;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 8;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
	canbittype 	unused8: 8;
}_c_GWB2_msgType;

typedef struct {
	canbittype 	unused0: 8;
	canbittype 	TCU_GearSelDisp: 4;
	canbittype 	unused1: 4;
	canbittype 	unused2: 8;
	canbittype 	unused3: 8;
	canbittype 	unused4: 8;
	canbittype 	unused5: 8;
	canbittype 	unused6: 8;
	canbittype 	unused7: 8;
}_c_TCU1_msgType;

/**************************************************************/
/* Message unions                                          */ 
/**************************************************************/

/* Send messages */
typedef union {
	canuint8 _c[8];
	_c_DSM_0x502_msgType dsm_0x502;
}_c_DSM_0x502_buf;

typedef union {
	canuint8 _c[8];
	_c_DSM_0x501_msgType dsm_0x501;
}_c_DSM_0x501_buf;

typedef union {
	canuint8 _c[8];
	_c_DSM_2_msgType dsm_2;
}_c_DSM_2_buf;

typedef union {
	canuint8 _c[8];
	_c_DSM_msgType dsm;
}_c_DSM_buf;


/* Receive messages */
typedef union {
	canuint8 _c[8];
	_c_IVI4_msgType ivi4;
}_c_IVI4_buf;

typedef union {
	canuint8 _c[8];
	_c_IVI8_DSM_msgType ivi8_dsm;
}_c_IVI8_DSM_buf;

typedef union {
	canuint8 _c[8];
	_c_VCU1_msgType vcu1;
}_c_VCU1_buf;

typedef union {
	canuint8 _c[8];
	_c_GWB1_msgType gwb1;
}_c_GWB1_buf;

typedef union {
	canuint8 _c[8];
	_c_BDC3_msgType bdc3;
}_c_BDC3_buf;

typedef union {
	canuint8 _c[8];
	_c_ABS1_msgType abs1;
}_c_ABS1_buf;

typedef union {
	canuint8 _c[8];
	_c_BDC6_PEPS1_msgType bdc6_peps1;
}_c_BDC6_PEPS1_buf;

typedef union {
	canuint8 _c[8];
	_c_BDC5_msgType bdc5;
}_c_BDC5_buf;

typedef union {
	canuint8 _c[8];
	_c_GWB2_msgType gwb2;
}_c_GWB2_buf;

typedef union {
	canuint8 _c[8];
	_c_TCU1_msgType tcu1;
}_c_TCU1_buf;


/**************************************************************/
/* Databuffer for send objects                               */ 
/**************************************************************/
extern _c_DSM_0x502_buf MEMORY_FAR  DSM_0x502;
extern _c_DSM_0x501_buf MEMORY_FAR  DSM_0x501;
extern _c_DSM_2_buf MEMORY_FAR  DSM_2;
extern _c_DSM_buf MEMORY_FAR  DSM;

/**************************************************************/
/* receive for send objects                               */ 
/**************************************************************/
extern _c_IVI4_buf MEMORY_FAR  IVI4;
extern _c_IVI8_DSM_buf MEMORY_FAR  IVI8_DSM;
extern _c_VCU1_buf MEMORY_FAR  VCU1;
extern _c_GWB1_buf MEMORY_FAR  GWB1;
extern _c_BDC3_buf MEMORY_FAR  BDC3;
extern _c_ABS1_buf MEMORY_FAR  ABS1;
extern _c_BDC6_PEPS1_buf MEMORY_FAR  BDC6_PEPS1;
extern _c_BDC5_buf MEMORY_FAR  BDC5;
extern _c_GWB2_buf MEMORY_FAR  GWB2;
extern _c_TCU1_buf MEMORY_FAR  TCU1;

/**************************************************************/
/* Signals of send messages                                 */ 
/**************************************************************/
#define b_DSM_0x502_DSM_DriverHeatStopReason_b(x)   DSM_0x502.dsm_0x502.DSM_DriverHeatStopReason=((x));
#define b_DSM_0x502_DSM_DriverHeatRunType_b(x)   DSM_0x502.dsm_0x502.DSM_DriverHeatRunType=((x));
#define b_DSM_0x502_DSM_RemoteStatus_b(x)   DSM_0x502.dsm_0x502.DSM_RemoteStatus=((x));
#define b_DSM_0x502_DSM_PassengerHeatStopReason_b(x)   DSM_0x502.dsm_0x502.DSM_PassengerHeatStopReason=((x));
#define b_DSM_0x502_DSM_PassengerHeatRunType_b(x)   DSM_0x502.dsm_0x502.DSM_PassengerHeatRunType=((x));
#define b_DSM_0x502_DSM_EngineRunStatus_b(x)   DSM_0x502.dsm_0x502.DSM_EngineRunStatus=((x));
#define b_DSM_0x502_DSM_DriverVentilateStopReason_b(x)   DSM_0x502.dsm_0x502.DSM_DriverVentilateStopReason=((x));
#define b_DSM_0x502_DSM_DriverVentRunType_b(x)   DSM_0x502.dsm_0x502.DSM_DriverVentRunType=((x));
#define b_DSM_0x502_VehicleRunStatus_b(x)   DSM_0x502.dsm_0x502.VehicleRunStatus=((x));
#define b_DSM_0x502_DSM_PassengerVentilateStopReason_b(x)   DSM_0x502.dsm_0x502.DSM_PassengerVentilateStopReason=((x));
#define b_DSM_0x502_DSM_PassengerVentRunType_b(x)   DSM_0x502.dsm_0x502.DSM_PassengerVentRunType=((x));
#define b_DSM_0x502_DSM_WheelHeatStopReason_b(x)   DSM_0x502.dsm_0x502.DSM_WheelHeatStopReason=((x));
#define b_DSM_0x502_DSM_SteerWheelHeatRunType_b(x)   DSM_0x502.dsm_0x502.DSM_SteerWheelHeatRunType=((x));
#define b_DSM_0x502_DSM_ECUVot_b(x)   DSM_0x502.dsm_0x502.DSM_ECUVot=((x));
#define b_DSM_0x502_DSM_CarPowerMode_b(x)   DSM_0x502.dsm_0x502.DSM_CarPowerMode=((x));
#define b_DSM_0x502_DSM_PassengerMoveType_b(x)   DSM_0x502.dsm_0x502.DSM_PassengerMoveType=((x));
#define b_DSM_0x502_DSM_DrHeightLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_DrHeightLockSts=((x));
#define b_DSM_0x502_DSM_DrLengthLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_DrLengthLockSts=((x));
#define b_DSM_0x502_DSM_DrBackLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_DrBackLockSts=((x));
#define b_DSM_0x502_DSM_DrFrontLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_DrFrontLockSts=((x));
#define b_DSM_0x502_DSM_PaLengthLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_PaLengthLockSts=((x));
#define b_DSM_0x502_DSM_PaBackLockSts_b(x)   DSM_0x502.dsm_0x502.DSM_PaBackLockSts=((x));

#define b_DSM_0x501_DSM_DriverHeightMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_DriverHeightMoveReason=((x));
#define b_DSM_0x501_DSM_DriverHeightCMD_b(x)   DSM_0x501.dsm_0x501.DSM_DriverHeightCMD=((x));
#define b_DSM_0x501_DSM_DriverHeightUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverHeightUPSW=((x));
#define b_DSM_0x501_DSM_DriverLengthMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_DriverLengthMoveReason=((x));
#define b_DSM_0x501_DSM_DriverLengthCMD_b(x)   DSM_0x501.dsm_0x501.DSM_DriverLengthCMD=((x));
#define b_DSM_0x501_DSM_DriverHeightDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverHeightDNSW=((x));
#define b_DSM_0x501_DSM_DriverBackMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_DriverBackMoveReason=((x));
#define b_DSM_0x501_DSM_DriverBackCMD_b(x)   DSM_0x501.dsm_0x501.DSM_DriverBackCMD=((x));
#define b_DSM_0x501_DSM_DriverLengthUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverLengthUPSW=((x));
#define b_DSM_0x501_DSM_DriverFrontMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_DriverFrontMoveReason=((x));
#define b_DSM_0x501_DSM_DriverFrontCMD_b(x)   DSM_0x501.dsm_0x501.DSM_DriverFrontCMD=((x));
#define b_DSM_0x501_DSM_DriverLengthDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverLengthDNSW=((x));
#define b_DSM_0x501_DSM_PassengerLengthMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerLengthMoveReason=((x));
#define b_DSM_0x501_DSM_PassengerLengthCMD_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerLengthCMD=((x));
#define b_DSM_0x501_DSM_DriverBackUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverBackUPSW=((x));
#define b_DSM_0x501_DSM_PassengerBackMoveReason_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerBackMoveReason=((x));
#define b_DSM_0x501_DSM_PassengerBackCMD_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerBackCMD=((x));
#define b_DSM_0x501_DSM_DriverBackDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverBackDNSW=((x));
#define b_DSM_0x501_DSM_DriverFrontUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverFrontUPSW=((x));
#define b_DSM_0x501_DSM_DriverFrontDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_DriverFrontDNSW=((x));
#define b_DSM_0x501_DSM_PassengerLengthUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerLengthUPSW=((x));
#define b_DSM_0x501_DSM_PassengerLengthDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerLengthDNSW=((x));
#define b_DSM_0x501_DSM_PassengerBackUPSW_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerBackUPSW=((x));
#define b_DSM_0x501_DSM_PassengerBackDNSW_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerBackDNSW=((x));
#define b_DSM_0x501_DSM_PassengerLengthLearnSts_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerLengthLearnSts=((x));
#define b_DSM_0x501_DSM_PassengerBackLearnSts_b(x)   DSM_0x501.dsm_0x501.DSM_PassengerBackLearnSts=((x));
#define b_DSM_0x501_DSM_DriverHeightLearnSt_b(x)   DSM_0x501.dsm_0x501.DSM_DriverHeightLearnSt=((x));
#define b_DSM_0x501_DSM_DriverLengthLearnSts_b(x)   DSM_0x501.dsm_0x501.DSM_DriverLengthLearnSts=((x));
#define b_DSM_0x501_DSM_DriverBackLearnSts_b(x)   DSM_0x501.dsm_0x501.DSM_DriverBackLearnSts=((x));
#define b_DSM_0x501_DSM_DriverFrontLearnSts_b(x)   DSM_0x501.dsm_0x501.DSM_DriverFrontLearnSts=((x));
#define b_DSM_0x501_DSM_DriverMoveType_b(x)   DSM_0x501.dsm_0x501.DSM_DriverMoveType=((x));

#define b_DSM_2_DSM_DrNtcValue_b(x)   DSM_2.dsm_2.DSM_DrNtcValue_1=(canuint8)(((x)>>8)& 0xFF);  \
                               DSM_2.dsm_2.DSM_DrNtcValue_0=(canuint8)((x)& 0xFF);

#define b_DSM_2_DSM_PaNtcValue_b(x)   DSM_2.dsm_2.DSM_PaNtcValue_1=(canuint8)(((x)>>8)& 0xFF);  \
                               DSM_2.dsm_2.DSM_PaNtcValue_0=(canuint8)((x)& 0xFF);

#define b_DSM_2_DSM_SteerNtcValue_b(x)   DSM_2.dsm_2.DSM_SteerNtcValue_1=(canuint8)(((x)>>8)& 0xFF);  \
                               DSM_2.dsm_2.DSM_SteerNtcValue_0=(canuint8)((x)& 0xFF);


#define b_DSM_DSM_FLSeatPosMsg_b(x)   DSM.dsm.DSM_FLSeatPosMsg=((x));
#define b_DSM_DSM_FRSeatPosMsg_b(x)   DSM.dsm.DSM_FRSeatPosMsg=((x));
#define b_DSM_DSM1_FLSeatMem1Sts_b(x)   DSM.dsm.DSM1_FLSeatMem1Sts=((x));
#define b_DSM_DSM_FLSeatMemStsAndMsg_b(x)   DSM.dsm.DSM_FLSeatMemStsAndMsg=((x));
#define b_DSM_DSM3_FLSeatMem3Sts_b(x)   DSM.dsm.DSM3_FLSeatMem3Sts=((x));
#define b_DSM_DSM2_FLSeatMem2Sts_b(x)   DSM.dsm.DSM2_FLSeatMem2Sts=((x));
#define b_DSM_DSM_St_FLSeatmeet_b(x)   DSM.dsm.DSM_St_FLSeatmeet=((x));
#define b_DSM_DSM1_FRSeatMem1Sts_b(x)   DSM.dsm.DSM1_FRSeatMem1Sts=((x));
#define b_DSM_DSM_FRSeatMemStsAndMsg_b(x)   DSM.dsm.DSM_FRSeatMemStsAndMsg=((x));
#define b_DSM_DSM_St_FRSeatmeet_b(x)   DSM.dsm.DSM_St_FRSeatmeet=((x));
#define b_DSM_DSM2_FRSeatMem3Sts_b(x)   DSM.dsm.DSM2_FRSeatMem3Sts=((x));
#define b_DSM_DSM2_FRSeatMem2Sts_b(x)   DSM.dsm.DSM2_FRSeatMem2Sts=((x));
#define b_DSM_DSM_St_PasSeatHeatGear_b(x)   DSM.dsm.DSM_St_PasSeatHeatGear=((x));
#define b_DSM_DSM_St_PasSeatHeatSW_b(x)   DSM.dsm.DSM_St_PasSeatHeatSW=((x));
#define b_DSM_DSM_St_DriSeatHeatGear_b(x)   DSM.dsm.DSM_St_DriSeatHeatGear=((x));
#define b_DSM_DSM_St_DriSeatHeatSW_b(x)   DSM.dsm.DSM_St_DriSeatHeatSW=((x));
#define b_DSM_DSM_St_DriSeatVentilationGear_b(x)   DSM.dsm.DSM_St_DriSeatVentilationGear=((x));
#define b_DSM_DSM_St_DriSeatVentilationSW_b(x)   DSM.dsm.DSM_St_DriSeatVentilationSW=((x));
#define b_DSM_DSM_MassageMode_FB_b(x)   DSM.dsm.DSM_MassageMode_FB=((x));
#define b_DSM_DSM_St_PasSeatVentilationGear_b(x)   DSM.dsm.DSM_St_PasSeatVentilationGear=((x));
#define b_DSM_DSM_St_PasSeatVentilationSW_b(x)   DSM.dsm.DSM_St_PasSeatVentilationSW=((x));
#define b_DSM_IntelligentPowerDown_FB_b(x)   DSM.dsm.IntelligentPowerDown_FB=((x));
#define b_DSM_DSM_NapMode_FB_b(x)   DSM.dsm.DSM_NapMode_FB=((x));
#define b_DSM_DSM_MassageLevel_FB_b(x)   DSM.dsm.DSM_MassageLevel_FB=((x));
#define b_DSM_DSM_SwsHeatSts_b(x)   DSM.dsm.DSM_SwsHeatSts=((x));


/**************************************************************/
/* Signals of receive messages                                 */ 
/**************************************************************/
#define b_IVI4_IVI_NapMode_SwtichSet_b()   IVI4.ivi4.IVI_NapMode_SwtichSet

#define b_IVI8_DSM_IVI_St_FLSeatmeet_b()   IVI8_DSM.ivi8_dsm.IVI_St_FLSeatmeet
#define b_IVI8_DSM_IVI_FLSeatMemSet3_b()   IVI8_DSM.ivi8_dsm.IVI_FLSeatMemSet3
#define b_IVI8_DSM_IVI_FLSeatMemSet2_b()   IVI8_DSM.ivi8_dsm.IVI_FLSeatMemSet2
#define b_IVI8_DSM_IVI_FLSeatMemSet1_b()   IVI8_DSM.ivi8_dsm.IVI_FLSeatMemSet1
#define b_IVI8_DSM_IVI_St_FRSeatmeet_b()   IVI8_DSM.ivi8_dsm.IVI_St_FRSeatmeet
#define b_IVI8_DSM_IVI_FRSeatMemSet3_b()   IVI8_DSM.ivi8_dsm.IVI_FRSeatMemSet3
#define b_IVI8_DSM_IVI_FRSeatMemSet2_b()   IVI8_DSM.ivi8_dsm.IVI_FRSeatMemSet2
#define b_IVI8_DSM_IVI_FRSeatMemSet1_b()   IVI8_DSM.ivi8_dsm.IVI_FRSeatMemSet1
#define b_IVI8_DSM_IVI_FRSeatHeatSet_b()   IVI8_DSM.ivi8_dsm.IVI_FRSeatHeatSet
#define b_IVI8_DSM_IVI_FLSeatHeatSet_b()   IVI8_DSM.ivi8_dsm.IVI_FLSeatHeatSet
#define b_IVI8_DSM_IVI_FRSeatVentnSet_b()   IVI8_DSM.ivi8_dsm.IVI_FRSeatVentnSet
#define b_IVI8_DSM_IVI_FLSeatVentnSet_b()   IVI8_DSM.ivi8_dsm.IVI_FLSeatVentnSet
#define b_IVI8_DSM_IVI_MassageLevel_Req_b()   IVI8_DSM.ivi8_dsm.IVI_MassageLevel_Req
#define b_IVI8_DSM_IVI_SwsHeatSw_b()   IVI8_DSM.ivi8_dsm.IVI_SwsHeatSw
#define b_IVI8_DSM_IVI_MassageMode_Req_b()   IVI8_DSM.ivi8_dsm.IVI_MassageMode_Req

#define b_VCU1_VCU_VehRunSta_b()   VCU1.vcu1.VCU_VehRunSta

#define b_GWB1_ECMD_EngineStatus_b()   GWB1.gwb1.ECMD_EngineStatus

#define b_BDC3_BDC_FRDoorSts_b()   BDC3.bdc3.BDC_FRDoorSts
#define b_BDC3_BDC_FLDoorSts_b()   BDC3.bdc3.BDC_FLDoorSts

#define b_ABS1_ABS_VehicleSpeedValid_b()   ABS1.abs1.ABS_VehicleSpeedValid
#define b_ABS1_ABS_VehicleSpeed_b()   (((canuint16)ABS1.abs1.ABS_VehicleSpeed_1)<<8  \
                 |((canuint16)ABS1.abs1.ABS_VehicleSpeed_0))

#define b_BDC6_PEPS1_BDC_PDU_b()   BDC6_PEPS1.bdc6_peps1.BDC_PDU
#define b_BDC6_PEPS1_BDC_TboxRemoteControlSt_b()   BDC6_PEPS1.bdc6_peps1.BDC_TboxRemoteControlSt

#define b_BDC5_BDC_TBOX_Req_Steeringwheel_heating_b()   BDC5.bdc5.BDC_TBOX_Req_Steeringwheel_heating
#define b_BDC5_BDC_IntelligentPowerDown_Sta_b()   BDC5.bdc5.BDC_IntelligentPowerDown_Sta
#define b_BDC5_BDC_TBOX_Req_PaSeatHeating_b()   BDC5.bdc5.BDC_TBOX_Req_PaSeatHeating
#define b_BDC5_BDC_TBOX_Req_DrSeatHeating_b()   BDC5.bdc5.BDC_TBOX_Req_DrSeatHeating
#define b_BDC5_BDC_TBOX_Req_PaSeatVentilating_b()   BDC5.bdc5.BDC_TBOX_Req_PaSeatVentilating
#define b_BDC5_BDC_TBOX_Req_DrSeatVentilating_b()   BDC5.bdc5.BDC_TBOX_Req_DrSeatVentilating

#define b_GWB2_VCU_GearSelDisp_b()   GWB2.gwb2.VCU_GearSelDisp

#define b_TCU1_TCU_GearSelDisp_b()   TCU1.tcu1.TCU_GearSelDisp


/**************************************************************/
/* Send/Receive structures extern                                */ 
/**************************************************************/
#define kFuncReqSID			            0x600
#define kPhysReqSID			            0x636
#define kPhysResSID			            0x637
#define kIlNumberOfTxObjects				4
#define kCanNumberOfTxObjects				4
#define kCanNumberOfRxObjects				13
#define kIlNumberOfRxTimeoutCounters				13
#define kCanNumberOfRxObjectsFilterList     (13)

#define kIlNumberOfTimerFlagBytes				2
#define _ILTxDSM_0x502     0

#define _ILTxDSM_0x501     1

#define _ILTxDSM_2     2

#define _ILTxDSM     3


extern V_MEMROM0 V_MEMROM1 tCanTxId V_MEMROM2 CanTxId[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclicCycles[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxType[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxEventCycles[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclesFastTime[kCanNumberOfTxObjects];
extern V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclesNRepeatTime[kCanNumberOfTxObjects];

extern V_MEMROM0 V_MEMROM1 tCanRxId V_MEMROM2 CanRxId[kCanNumberOfRxObjects];
extern V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects];
extern V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects];
extern V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects];
extern V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters];
extern V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 IlRxCheckSumFlag[kIlNumberOfRxTimeoutCounters];
extern V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxCyclesFastTime[kIlNumberOfRxTimeoutCounters];
extern V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxCyclesNRepeatTime[kIlNumberOfRxTimeoutCounters];

#define CanGetRxId(i)        CanRxId[i]
#define CanGetRxDataPtr(i)   CanRxDataPtr[i]
#define CanGetRxDataLen(i)   CanRxDataLen[i]
#define IlGetIlRxTimeoutTbl(i)	  IlRxTimeoutTbl[i]
#define CanGetTxId(i)               CanTxId[i]
#define CanGetTxDataPtr(i)   CanTxDataPtr[i]
#define CanGetTxDlc(i)       CanTxDLC[i]

extern canuint8 AppMsgIVI4PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgIVI8_DSMPreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgVCU1PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgGWB1PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgBDC3PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgABS1PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgBDC6_PEPS1PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgBDC5PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgGWB2PreCopy(CanRxInfoStructPtr preParam);
extern canuint8 AppMsgTCU1PreCopy(CanRxInfoStructPtr preParam);


extern void _f_IVI4TimeoutInd(void);
extern void _f_IVI8_DSMTimeoutInd(void);
extern void _f_VCU1TimeoutInd(void);
extern void _f_GWB1TimeoutInd(void);
extern void _f_BDC3TimeoutInd(void);
extern void _f_ABS1TimeoutInd(void);
extern void _f_BDC6_PEPS1TimeoutInd(void);
extern void _f_BDC5TimeoutInd(void);
extern void _f_GWB2TimeoutInd(void);
extern void _f_TCU1TimeoutInd(void);

extern void ILPutTxDSM_0x502_DSM_DriverHeatStopReason(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DriverHeatRunType(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_RemoteStatus(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PassengerHeatStopReason(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PassengerHeatRunType(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_EngineRunStatus(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DriverVentilateStopReason(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DriverVentRunType(canuint8 sigData);
extern void ILPutTxDSM_0x502_VehicleRunStatus(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PassengerVentilateStopReason(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PassengerVentRunType(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_WheelHeatStopReason(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_SteerWheelHeatRunType(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_ECUVot(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_CarPowerMode(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PassengerMoveType(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DrHeightLockSts(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DrLengthLockSts(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DrBackLockSts(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_DrFrontLockSts(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PaLengthLockSts(canuint8 sigData);
extern void ILPutTxDSM_0x502_DSM_PaBackLockSts(canuint8 sigData);

extern void ILPutTxDSM_0x501_DSM_DriverHeightMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverHeightCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverHeightUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverLengthMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverLengthCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverHeightDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverBackMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverBackCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverLengthUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverFrontMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverFrontCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverLengthDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerLengthMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerLengthCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverBackUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerBackMoveReason(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerBackCMD(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverBackDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverFrontUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverFrontDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerLengthUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerLengthDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerBackUPSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerBackDNSW(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerLengthLearnSts(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_PassengerBackLearnSts(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverHeightLearnSt(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverLengthLearnSts(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverBackLearnSts(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverFrontLearnSts(canuint8 sigData);
extern void ILPutTxDSM_0x501_DSM_DriverMoveType(canuint8 sigData);

extern void ILPutTxDSM_2_DSM_DrNtcValue(canuint16 sigData);
extern void ILPutTxDSM_2_DSM_PaNtcValue(canuint16 sigData);
extern void ILPutTxDSM_2_DSM_SteerNtcValue(canuint16 sigData);

extern void ILPutTxDSM_DSM_FLSeatPosMsg(canuint8 sigData);
extern void ILPutTxDSM_DSM_FRSeatPosMsg(canuint8 sigData);
extern void ILPutTxDSM_DSM1_FLSeatMem1Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM_FLSeatMemStsAndMsg(canuint8 sigData);
extern void ILPutTxDSM_DSM3_FLSeatMem3Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM2_FLSeatMem2Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_FLSeatmeet(canuint8 sigData);
extern void ILPutTxDSM_DSM1_FRSeatMem1Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM_FRSeatMemStsAndMsg(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_FRSeatmeet(canuint8 sigData);
extern void ILPutTxDSM_DSM2_FRSeatMem3Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM2_FRSeatMem2Sts(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_PasSeatHeatGear(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_PasSeatHeatSW(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_DriSeatHeatGear(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_DriSeatHeatSW(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_DriSeatVentilationGear(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_DriSeatVentilationSW(canuint8 sigData);
extern void ILPutTxDSM_DSM_MassageMode_FB(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_PasSeatVentilationGear(canuint8 sigData);
extern void ILPutTxDSM_DSM_St_PasSeatVentilationSW(canuint8 sigData);
extern void ILPutTxDSM_IntelligentPowerDown_FB(canuint8 sigData);
extern void ILPutTxDSM_DSM_NapMode_FB(canuint8 sigData);
extern void ILPutTxDSM_DSM_MassageLevel_FB(canuint8 sigData);
extern void ILPutTxDSM_DSM_SwsHeatSts(canuint8 sigData);


#endif
