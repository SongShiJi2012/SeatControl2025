/************************************************************************************************
File created time : 2025-05-15 15:14:09
Tool Name :         DSM_If_Generate.py + DSM_If_Generate.xlsx
Filename:           Rte_VfbInterface.h
Author:             Ai
Description:        Generate VFB interface
/************************************************************************************************/
/************************************************************************************************
                                   C O P Y R I G H T  
-------------------------------------------------------------------------------  
Copyright (c) 2013-2025 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved.  
/************************************************************************************************/

#ifndef _RTE_VFBINTERFACE_H_
#define _RTE_VFBINTERFACE_H_

#include "Common.h"


/*********************************Function declaration*********************************************/
extern void Rte_SetVfb_DrHeightSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightSwitchCmd(void);

extern void Rte_SetVfb_DrLengthSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthSwitchCmd(void);

extern void Rte_SetVfb_DrBackSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackSwitchCmd(void);

extern void Rte_SetVfb_DrFrontSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontSwitchCmd(void);

extern void Rte_SetVfb_DrHeightMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightMotorCmd(void);

extern void Rte_SetVfb_DrLengthMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthMotorCmd(void);

extern void Rte_SetVfb_DrBackMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackMotorCmd(void);

extern void Rte_SetVfb_DrFrontMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontMotorCmd(void);

extern void Rte_SetVfb_DrHeightMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightMotorReason(void);

extern void Rte_SetVfb_DrLengthMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthMotorReason(void);

extern void Rte_SetVfb_DrBackMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackMotorReason(void);

extern void Rte_SetVfb_DrFrontMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontMotorReason(void);

extern void Rte_SetVfb_DrHeightAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightAutoRunFlag(void);

extern void Rte_SetVfb_DrLengthAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthAutoRunFlag(void);

extern void Rte_SetVfb_DrBackAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackAutoRunFlag(void);

extern void Rte_SetVfb_DrFrontAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontAutoRunFlag(void);

extern void Rte_SetVfb_DrMoveType(INT8U SetValue);
extern INT8U Rte_GetVfb_DrMoveType(void);

extern void Rte_SetVfb_DrHeightHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightHallErr(void);

extern void Rte_SetVfb_DrLengthHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthHallErr(void);

extern void Rte_SetVfb_DrBackHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackHallErr(void);

extern void Rte_SetVfb_DrFrontHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontHallErr(void);

extern void Rte_SetVfb_DrAnyoneHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneHallErr(void);

extern void Rte_SetVfb_DrHeightDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightDTCHallErr(void);

extern void Rte_SetVfb_DrLengthDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthDTCHallErr(void);

extern void Rte_SetVfb_DrBackDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackDTCHallErr(void);

extern void Rte_SetVfb_DrFrontDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontDTCHallErr(void);

extern void Rte_SetVfb_DrAnyoneDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneDTCHallErr(void);

extern void Rte_SetVfb_DrHeightStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightStallErr(void);

extern void Rte_SetVfb_DrLengthStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthStallErr(void);

extern void Rte_SetVfb_DrBackStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackStallErr(void);

extern void Rte_SetVfb_DrFrontStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontStallErr(void);

extern void Rte_SetVfb_DrAnyoneStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneStallErr(void);

extern void Rte_SetVfb_DrHeightRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightRelayAdheErr(void);

extern void Rte_SetVfb_DrLengthRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthRelayAdheErr(void);

extern void Rte_SetVfb_DrBackRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackRelayAdheErr(void);

extern void Rte_SetVfb_DrFrontRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontRelayAdheErr(void);

extern void Rte_SetVfb_DrAnyoneRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneRelayAdheErr(void);

extern void Rte_SetVfb_DrHeightSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightSwitchAdheErr(void);

extern void Rte_SetVfb_DrLengthSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthSwitchAdheErr(void);

extern void Rte_SetVfb_DrBackSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackSwitchAdheErr(void);

extern void Rte_SetVfb_DrFrontSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontSwitchAdheErr(void);

extern void Rte_SetVfb_DrHeightSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_DrHeightSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightSwitchAdheErr_Back(void);

extern void Rte_SetVfb_DrLengthSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_DrLengthSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthSwitchAdheErr_Back(void);

extern void Rte_SetVfb_DrBackSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_DrBackSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackSwitchAdheErr_Back(void);

extern void Rte_SetVfb_DrFrontSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_DrFrontSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontSwitchAdheErr_Back(void);

extern void Rte_SetVfb_DrAnyoneSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneSwitchAdheErr(void);

extern void Rte_SetVfb_DrHeightSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightSoftStopErr(void);

extern void Rte_SetVfb_DrLengthSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthSoftStopErr(void);

extern void Rte_SetVfb_DrBackSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackSoftStopErr(void);

extern void Rte_SetVfb_DrFrontSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontSoftStopErr(void);

extern void Rte_SetVfb_DrAnyoneSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrAnyoneSoftStopErr(void);

extern void Rte_SetVfb_DrHeightMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightMotorTimeOutErr(void);

extern void Rte_SetVfb_DrLengthMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthMotorTimeOutErr(void);

extern void Rte_SetVfb_DrBackMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackMotorTimeOutErr(void);

extern void Rte_SetVfb_DrFrontMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontMotorTimeOutErr(void);

extern void Rte_SetVfb_PaHeightSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightSwitchCmd(void);

extern void Rte_SetVfb_PaLengthSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthSwitchCmd(void);

extern void Rte_SetVfb_PaBackSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackSwitchCmd(void);

extern void Rte_SetVfb_PaFrontSwitchCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontSwitchCmd(void);

extern void Rte_SetVfb_PaHeightMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightMotorCmd(void);

extern void Rte_SetVfb_PaLengthMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthMotorCmd(void);

extern void Rte_SetVfb_PaBackMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackMotorCmd(void);

extern void Rte_SetVfb_PaFrontMotorCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontMotorCmd(void);

extern void Rte_SetVfb_PaHeightMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightMotorReason(void);

extern void Rte_SetVfb_PaLengthMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthMotorReason(void);

extern void Rte_SetVfb_PaBackMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackMotorReason(void);

extern void Rte_SetVfb_PaFrontMotorReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontMotorReason(void);

extern void Rte_SetVfb_PaHeightAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightAutoRunFlag(void);

extern void Rte_SetVfb_PaLengthAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthAutoRunFlag(void);

extern void Rte_SetVfb_PaBackAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackAutoRunFlag(void);

extern void Rte_SetVfb_PaFrontAutoRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontAutoRunFlag(void);

extern void Rte_SetVfb_PaMoveType(INT8U SetValue);
extern INT8U Rte_GetVfb_PaMoveType(void);

extern void Rte_SetVfb_PaHeightHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightHallErr(void);

extern void Rte_SetVfb_PaLengthHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthHallErr(void);

extern void Rte_SetVfb_PaBackHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackHallErr(void);

extern void Rte_SetVfb_PaFrontHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontHallErr(void);

extern void Rte_SetVfb_PaAnyoneHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneHallErr(void);

extern void Rte_SetVfb_PaHeightDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightDTCHallErr(void);

extern void Rte_SetVfb_PaLengthDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthDTCHallErr(void);

extern void Rte_SetVfb_PaBackDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackDTCHallErr(void);

extern void Rte_SetVfb_PaFrontDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontDTCHallErr(void);

extern void Rte_SetVfb_PaAnyoneDTCHallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneDTCHallErr(void);

extern void Rte_SetVfb_PaHeightStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightStallErr(void);

extern void Rte_SetVfb_PaLengthStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthStallErr(void);

extern void Rte_SetVfb_PaBackStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackStallErr(void);

extern void Rte_SetVfb_PaFrontStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontStallErr(void);

extern void Rte_SetVfb_PaAnyoneStallErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneStallErr(void);

extern void Rte_SetVfb_PaHeightRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightRelayAdheErr(void);

extern void Rte_SetVfb_PaLengthRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthRelayAdheErr(void);

extern void Rte_SetVfb_PaBackRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackRelayAdheErr(void);

extern void Rte_SetVfb_PaFrontRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontRelayAdheErr(void);

extern void Rte_SetVfb_PaAnyoneRelayAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneRelayAdheErr(void);

extern void Rte_SetVfb_PaHeightSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightSwitchAdheErr(void);

extern void Rte_SetVfb_PaLengthSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthSwitchAdheErr(void);

extern void Rte_SetVfb_PaBackSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackSwitchAdheErr(void);

extern void Rte_SetVfb_PaFrontSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontSwitchAdheErr(void);

extern void Rte_SetVfb_PaHeightSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_PaHeightSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightSwitchAdheErr_Back(void);

extern void Rte_SetVfb_PaLengthSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_PaLengthSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthSwitchAdheErr_Back(void);

extern void Rte_SetVfb_PaBackSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_PaBackSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackSwitchAdheErr_Back(void);

extern void Rte_SetVfb_PaFrontSwitchAdheErr_ForWard(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontSwitchAdheErr_ForWard(void);

extern void Rte_SetVfb_PaFrontSwitchAdheErr_Back(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontSwitchAdheErr_Back(void);

extern void Rte_SetVfb_PaAnyoneSwitchAdheErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneSwitchAdheErr(void);

extern void Rte_SetVfb_PaHeightSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightSoftStopErr(void);

extern void Rte_SetVfb_PaLengthSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthSoftStopErr(void);

extern void Rte_SetVfb_PaBackSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackSoftStopErr(void);

extern void Rte_SetVfb_PaFrontSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontSoftStopErr(void);

extern void Rte_SetVfb_PaAnyoneSoftStopErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaAnyoneSoftStopErr(void);

extern void Rte_SetVfb_PaHeightMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightMotorTimeOutErr(void);

extern void Rte_SetVfb_PaLengthMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthMotorTimeOutErr(void);

extern void Rte_SetVfb_PaBackMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackMotorTimeOutErr(void);

extern void Rte_SetVfb_PaFrontMotorTimeOutErr(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontMotorTimeOutErr(void);

extern void Rte_SetVfb_DrWelLengthReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrWelLengthReqPosi(void);

extern void Rte_SetVfb_DrWelBackReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrWelBackReqPosi(void);

extern void Rte_SetVfb_PaWelLengthReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaWelLengthReqPosi(void);

extern void Rte_SetVfb_PaWelBackReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaWelBackReqPosi(void);

extern void Rte_SetVfb_DrMemHeightReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrMemHeightReqPosi(void);

extern void Rte_SetVfb_DrMemLengthReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrMemLengthReqPosi(void);

extern void Rte_SetVfb_DrMemBackReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrMemBackReqPosi(void);

extern void Rte_SetVfb_DrMemFrontReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrMemFrontReqPosi(void);

extern void Rte_SetVfb_PaMemHeightReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaMemHeightReqPosi(void);

extern void Rte_SetVfb_PaMemLengthReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaMemLengthReqPosi(void);

extern void Rte_SetVfb_PaMemBackReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaMemBackReqPosi(void);

extern void Rte_SetVfb_PaMemFrontReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaMemFrontReqPosi(void);

extern void Rte_SetVfb_DrResHeightReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResHeightReqPosi(void);

extern void Rte_SetVfb_DrResLengthReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResLengthReqPosi(void);

extern void Rte_SetVfb_DrResBackReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResBackReqPosi(void);

extern void Rte_SetVfb_DrResFrontReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResFrontReqPosi(void);

extern void Rte_SetVfb_DrResHeightReCallPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResHeightReCallPosi(void);

extern void Rte_SetVfb_DrResLengthReCallPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResLengthReCallPosi(void);

extern void Rte_SetVfb_DrResBackReCallPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResBackReCallPosi(void);

extern void Rte_SetVfb_DrResFrontReCallPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrResFrontReCallPosi(void);

extern void Rte_SetVfb_DrHeat(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeat(void);

extern void Rte_SetVfb_PaHeat(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeat(void);

extern void Rte_SetVfb_ThirdHeat(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeat(void);

extern void Rte_SetVfb_DrHeatIo(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatIo(void);

extern void Rte_SetVfb_PaHeatIo(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatIo(void);

extern void Rte_SetVfb_ThirdHeatIo(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatIo(void);

extern void Rte_SetVfb_DrHeatCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatCmdFaultSts(void);

extern void Rte_SetVfb_PaHeatCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatCmdFaultSts(void);

extern void Rte_SetVfb_ThirdHeatCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatCmdFaultSts(void);

extern void Rte_SetVfb_DrHeatNTCFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatNTCFaultSts(void);

extern void Rte_SetVfb_PaHeatNTCFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatNTCFaultSts(void);

extern void Rte_SetVfb_ThirdHeatNTCFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatNTCFaultSts(void);

extern void Rte_SetVfb_DrHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatStopReason(void);

extern void Rte_SetVfb_PaHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatStopReason(void);

extern void Rte_SetVfb_ThirdHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatStopReason(void);

extern void Rte_SetVfb_DrHeatType(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatType(void);

extern void Rte_SetVfb_PaHeatType(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatType(void);

extern void Rte_SetVfb_ThirdHeatType(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatType(void);

extern void Rte_SetVfb_EngineRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_EngineRunFlag(void);

extern void Rte_SetVfb_RemoteModeFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_RemoteModeFlag(void);

extern void Rte_SetVfb_DrHeatRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatRunState(void);

extern void Rte_SetVfb_PaHeatRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatRunState(void);

extern void Rte_SetVfb_ThirdHeatRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatRunState(void);

extern void Rte_SetVfb_DrVent(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVent(void);

extern void Rte_SetVfb_PaVent(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVent(void);

extern void Rte_SetVfb_ThirdVent(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVent(void);

extern void Rte_SetVfb_DrVentCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentCmdFaultSts(void);

extern void Rte_SetVfb_PaVentCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVentCmdFaultSts(void);

extern void Rte_SetVfb_ThirdVentCmdFaultSts(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVentCmdFaultSts(void);

extern void Rte_SetVfb_DrVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentStopReason(void);

extern void Rte_SetVfb_PaVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVentStopReason(void);

extern void Rte_SetVfb_ThirdVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVentStopReason(void);

extern void Rte_SetVfb_DrVentType(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentType(void);

extern void Rte_SetVfb_PaVentType(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVentType(void);

extern void Rte_SetVfb_ThirdVentType(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVentType(void);

extern void Rte_SetVfb_DrVentRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentRunState(void);

extern void Rte_SetVfb_PaVentRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVentRunState(void);

extern void Rte_SetVfb_ThirdVentRunState(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVentRunState(void);

extern void Rte_SetVfb_DrLearnEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLearnEnable(void);

extern void Rte_SetVfb_DrLearnSts(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLearnSts(void);

extern void Rte_SetVfb_LearnExitCause(INT8U SetValue);
extern INT8U Rte_GetVfb_LearnExitCause(void);

extern void Rte_SetVfb_DrHeatCmdFaultSts4DTC(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatCmdFaultSts4DTC(void);

extern void Rte_SetVfb_PaHeatCmdFaultSts4DTC(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeatCmdFaultSts4DTC(void);

extern void Rte_SetVfb_ThirdHeatCmdFaultSts4DTC(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatCmdFaultSts4DTC(void);

extern void Rte_SetVfb_DrVentCmdFaultSts4DTC(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentCmdFaultSts4DTC(void);

extern void Rte_SetVfb_PaVentCmdFaultSts4DTC(INT8U SetValue);
extern INT8U Rte_GetVfb_PaVentCmdFaultSts4DTC(void);

extern void Rte_SetVfb_PaLearnSts(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLearnSts(void);

extern void Rte_SetVfb_PaLearnExitCause(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLearnExitCause(void);

extern void Rte_SetVfb_VehicleRunFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_VehicleRunFlag(void);

extern void Rte_SetVfb_GearP(INT8U SetValue);
extern INT8U Rte_GetVfb_GearP(void);

extern void Rte_SetVfb_BusoffFlag(INT8U SetValue);
extern INT8U Rte_GetVfb_BusoffFlag(void);

extern void Rte_SetVfb_DrWelcomeRunSts(INT8U SetValue);
extern INT8U Rte_GetVfb_DrWelcomeRunSts(void);

extern void Rte_SetVfb_PaWelcomeRunSts(INT8U SetValue);
extern INT8U Rte_GetVfb_PaWelcomeRunSts(void);

extern void Rte_SetVfb_DrWelcomeStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_DrWelcomeStopReason(void);

extern void Rte_SetVfb_PaWelcomeStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaWelcomeStopReason(void);

extern void Rte_SetVfb_DrWelLengthReqCMD(INT8U SetValue);
extern INT8U Rte_GetVfb_DrWelLengthReqCMD(void);

extern void Rte_SetVfb_PaWelLengthReqCMD(INT8U SetValue);
extern INT8U Rte_GetVfb_PaWelLengthReqCMD(void);

extern void Rte_SetVfb_DrLearnResult(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLearnResult(void);

extern void Rte_SetVfb_PaLearnResult(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLearnResult(void);

extern void Rte_SetVfb_GearPN(INT8U SetValue);
extern INT8U Rte_GetVfb_GearPN(void);

extern void Rte_SetVfb_PaLearnEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLearnEnable(void);

extern void Rte_SetVfb_NapMode(INT8U SetValue);
extern INT8U Rte_GetVfb_NapMode(void);

extern void Rte_SetVfb_MemSetStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_MemSetStopReason(void);

extern void Rte_SetVfb_SeatMemoryValidReq(INT8U SetValue);
extern INT8U Rte_GetVfb_SeatMemoryValidReq(void);

extern void Rte_SetVfb_MemCallStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_MemCallStopReason(void);

extern void Rte_SetVfb_PreMemRemindStop(INT8U SetValue);
extern INT8U Rte_GetVfb_PreMemRemindStop(void);

extern void Rte_SetVfb_SpeedLessThan5_Flag(INT8U SetValue);
extern INT8U Rte_GetVfb_SpeedLessThan5_Flag(void);

extern void Rte_SetVfb_CANDrHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANDrHeatStopReason(void);

extern void Rte_SetVfb_CANPaHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANPaHeatStopReason(void);

extern void Rte_SetVfb_CANThirdHeatStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANThirdHeatStopReason(void);

extern void Rte_SetVfb_CANDrVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANDrVentStopReason(void);

extern void Rte_SetVfb_CANPaVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANPaVentStopReason(void);

extern void Rte_SetVfb_CANThirdVentStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_CANThirdVentStopReason(void);

extern void Rte_SetVfb_DrHeatEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeatEnable(void);

extern void Rte_SetVfb_SecondHeatEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_SecondHeatEnable(void);

extern void Rte_SetVfb_ThirdHeatEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdHeatEnable(void);

extern void Rte_SetVfb_DrVentEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_DrVentEnable(void);

extern void Rte_SetVfb_SecondVentEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_SecondVentEnable(void);

extern void Rte_SetVfb_ThirdVentEnable(INT8U SetValue);
extern INT8U Rte_GetVfb_ThirdVentEnable(void);

extern void Rte_SetVfb_PaMemSetStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaMemSetStopReason(void);

extern void Rte_SetVfb_PaSeatMemoryValidReq(INT8U SetValue);
extern INT8U Rte_GetVfb_PaSeatMemoryValidReq(void);

extern void Rte_SetVfb_PaMemCallStopReason(INT8U SetValue);
extern INT8U Rte_GetVfb_PaMemCallStopReason(void);

extern void Rte_SetVfb_PaPreMemRemindStop(INT8U SetValue);
extern INT8U Rte_GetVfb_PaPreMemRemindStop(void);

extern void Rte_SetVfb_HVCommPC(INT8U SetValue);
extern INT8U Rte_GetVfb_HVCommPC(void);

extern void Rte_SetVfb_tPwrDnSts(INT8U SetValue);
extern INT8U Rte_GetVfb_tPwrDnSts(void);

extern void Rte_SetVfb_Res_MassageLevel_Req(INT8U SetValue);
extern INT8U Rte_GetVfb_Res_MassageLevel_Req(void);

extern void Rte_SetVfb_Res_MassageMode_Req(INT8U SetValue);
extern INT8U Rte_GetVfb_Res_MassageMode_Req(void);

extern void Rte_SetVfb_VoltMode(INT8U SetValue);
extern INT8U Rte_GetVfb_VoltMode(void);

extern void Rte_SetVfb_PowerMode(INT8U SetValue);
extern INT8U Rte_GetVfb_PowerMode(void);

extern void Rte_SetVfb_VoltSatisfy(INT8U SetValue);
extern INT8U Rte_GetVfb_VoltSatisfy(void);

extern void Rte_SetVfb_SwHeatMaxTime(INT8U SetValue);
extern INT8U Rte_GetVfb_SwHeatMaxTime(void);

extern void Rte_SetVfb_DrHeightLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrHeightLearnCmd(void);

extern void Rte_SetVfb_DrLengthLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrLengthLearnCmd(void);

extern void Rte_SetVfb_DrBackLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrBackLearnCmd(void);

extern void Rte_SetVfb_DrFrontLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_DrFrontLearnCmd(void);

extern void Rte_SetVfb_PaHeightLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaHeightLearnCmd(void);

extern void Rte_SetVfb_PaLengthLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaLengthLearnCmd(void);

extern void Rte_SetVfb_PaBackLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaBackLearnCmd(void);

extern void Rte_SetVfb_PaFrontLearnCmd(INT8U SetValue);
extern INT8U Rte_GetVfb_PaFrontLearnCmd(void);

extern void Rte_SetVfb_DrHeightResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrHeightResetReqPosi(void);

extern void Rte_SetVfb_DrLengthResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrLengthResetReqPosi(void);

extern void Rte_SetVfb_DrBackResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrBackResetReqPosi(void);

extern void Rte_SetVfb_DrFrontResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_DrFrontResetReqPosi(void);

extern void Rte_SetVfb_PaHeightResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaHeightResetReqPosi(void);

extern void Rte_SetVfb_PaLengthResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaLengthResetReqPosi(void);

extern void Rte_SetVfb_PaBackResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaBackResetReqPosi(void);

extern void Rte_SetVfb_PaFrontResetReqPosi(INT16U SetValue);
extern INT16U Rte_GetVfb_PaFrontResetReqPosi(void);

/***************************end****************************/


#endif   /* _RTE_VFBINTERFACE_H_ */
