#ifndef SRVL_CANSIGNALS_H
#define SRVL_CANSIGNALS_H
/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include  "v_def.h"
#include  "DSM.h"

extern canuint8 CanRx_0x367_IVI_NapMode_SwtichSet(void);
extern canuint8 CanRx_0x351_IVI_FLSeatMemSet1(void);
extern canuint8 CanRx_0x351_IVI_FLSeatMemSet2(void);
extern canuint8 CanRx_0x351_IVI_FLSeatMemSet3(void);
extern canuint8 CanRx_0x351_IVI_St_FLSeatmeet(void);
extern canuint8 CanRx_0x351_IVI_FRSeatMemSet1(void);
extern canuint8 CanRx_0x351_IVI_FRSeatMemSet2(void);
extern canuint8 CanRx_0x351_IVI_FRSeatMemSet3(void);
extern canuint8 CanRx_0x351_IVI_St_FRSeatmeet(void);
extern canuint8 CanRx_0x351_IVI_FLSeatHeatSet(void);
extern canuint8 CanRx_0x351_IVI_FRSeatHeatSet(void);
extern canuint8 CanRx_0x351_IVI_FLSeatVentnSet(void);
extern canuint8 CanRx_0x351_IVI_FRSeatVentnSet(void);
extern canuint8 CanRx_0x351_IVI_SwsHeatSw(void);
extern canuint8 CanRx_0x351_IVI_MassageLevel_Req(void);
extern canuint8 CanRx_0x351_IVI_MassageMode_Req(void);
extern canuint8 CanRx_0x28E_BDC_FLDoorSts(void);
extern canuint8 CanRx_0x28E_BDC_FRDoorSts(void);
extern canuint8 CanRx_0x281_BDC_TBOX_Req_DrSeatHeating(void);
extern canuint8 CanRx_0x281_BDC_TBOX_Req_PaSeatHeating(void);
extern canuint8 CanRx_0x281_BDC_TBOX_Req_DrSeatVentilating(void);
extern canuint8 CanRx_0x281_BDC_TBOX_Req_PaSeatVentilating(void);
extern canuint8 CanRx_0x281_BDC_TBOX_Req_Steeringwheel_heating(void);
extern canuint8 CanRx_0x283_BDC_PDU(void);
extern canuint8 CanRx_0x283_BDC_TboxRemoteControlSt(void);
extern canuint8 CanRx_0x238_TCU_GearSelDisp(void);
extern canuint8 CanRx_0x284_ABS_VehicleSpeedValid(void);
extern canuint16 CanRx_0x284_ABS_VehicleSpeed(void);
extern canuint8 CanRx_0x2A7_ECMD_EngineStatus(void);
extern canuint8 CanRx_0x2AE_VCU_VehRunSta(void);
extern canuint8 CanRx_0x26E_VCU_GearSelDisp(void);

extern void  CanTx_0x3B2_DSM_FLSeatMemStsAndMsg(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_FLSeatmeet(canuint8 sigData);
extern void  CanTx_0x3B2_DSM1_FLSeatMem1Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM2_FLSeatMem2Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM3_FLSeatMem3Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_FRSeatMemStsAndMsg(canuint8 sigData);
extern void  CanTx_0x3B2_DSM1_FRSeatMem1Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM2_FRSeatMem2Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM2_FRSeatMem3Sts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_FRSeatmeet(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_DriSeatHeatSW(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_DriSeatHeatGear(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_PasSeatHeatSW(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_PasSeatHeatGear(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_DriSeatVentilationSW(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_DriSeatVentilationGear(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_PasSeatVentilationSW(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_St_PasSeatVentilationGear(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_FLSeatPosMsg(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_FRSeatPosMsg(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_SwsHeatSts(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_MassageLevel_FB(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_MassageMode_FB(canuint8 sigData);
extern void  CanTx_0x3B2_DSM_NapMode_FB(canuint8 sigData);

#endif
