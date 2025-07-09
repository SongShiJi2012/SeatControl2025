/*
 * File: Rte_get_Light.c
 *
 * Code generated for Simulink model 'Rte_get_Light'.
 *
 * Model version                  : 1.107
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Mar 17 11:27:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Rte_get_Light.h"

/* Exported block signals */
INT8U ExLampSw;                        /* '<Root>/getAPI'
                                        * 大灯开关状态，0：OFF，1：位置灯，2：自动灯，3：近光灯，模拟自锁
                                        */
INT8U TurnLampSw;                      /* '<Root>/getAPI1'
                                        * 转向开关状态，OFF/Dir_Left/Dir_Right，模拟自锁
                                        */
INT8U HighBeamSw;                      /* '<Root>/getAPI2'
                                        * 远光灯开关，OFF/HighBeam/Flash，模拟点触，NULL  (0u)，High  (1u)，Flash  (2u)
                                        */
INT8U HarzedLampSw;                    /* '<Root>/getAPI3'
                                        * 危险报警开关状态，数字点触，有效值：Low
                                        */
INT8U FogLampSw;                       /* '<Root>/getAPI4'
                                        * 雾灯开关，OFF/Front Fog/Rear Fog，模拟点触
                                        */
INT8U ReverseLampSw;                   /* '<Root>/getAPI5'
                                        * 倒车挡开关状态，数字自锁， 有效值：Low
                                        */
INT8U BrakeLampSw;                     /* '<Root>/getAPI6'
                                        * 刹车开关状态，数字自锁， 有效值：high
                                        */
INT8U FL_DIR_Fault_Sts;                /* '<Root>/getAPI7'
                                        * 左前 LED 转向灯故障反馈状态，数字自锁，有效值：high
                                        */
INT8U FR_DIR_Fault_Sts;                /* '<Root>/getAPI8'
                                        * 右前 LED 转向灯故障反馈状态，数字自锁，有效值：high
                                        */
INT8U DriverDoorAjar;                  /* '<Root>/getAPI9'
                                        * 司机门状态，模拟自锁，Close/Open/Invalid，具体含义
                                        */
INT8U PassDoorAjar;                    /* '<Root>/getAPI10'
                                        * 副司机门状态，Close/Open/Invalid，数字自锁， 有效值：Low
                                        */
INT8U RLeftDoorAjar;                   /* '<Root>/getAPI11'
                                        * 左后门状态，数字自锁， 有效值：Low
                                        */
INT8U RRightDoorAjar;                  /* '<Root>/getAPI12'
                                        * 右后门状态，数字自锁， 有效值：Low
                                        */
INT8U TrunkDoorAjar;                   /* '<Root>/getAPI13'
                                        * 后备箱门状态，数字自锁， 有效值：Low
                                        */
INT8U PowerMode;                       /* '<Root>/getAPI14'
                                        * 电源模式，0：OFF，1：ACC，2：ON，3：START
                                        */
INT8U VehOpModePrm;                    /* '<Root>/getAPI15'
                                        * 车辆工作模式，默认值：0， 0：用户模式 1：工厂模式， 2：运输模式， 3：预留
                                        */
INT8U VehManufMaxTimPrm;               /* '<Root>/getAPI16'
                                        * 工厂和运输模式最大时间配置，默认值：5，1 单位为一分钟，取值范围：1~7
                                        */
INT8U VehManuOrAutoGearPrm;            /* '<Root>/getAPI17'
                                        * 自动/手动档车型配置， 0:Automatic gearbox with electronic gear shifter 1:Automatic gearbox with one-way solenoid 2:Automatic gearbox with two-way solenoid 3:Manual gearbox fitted
                                        */
INT8U VehEnFrontFogLampPrm;            /* '<Root>/getAPI18'
                                        * 前雾灯配置，0:No Front Fog Lamps 1:Front Fog Lamps fitted
                                        */
INT8U VehEnDRLPrm;                     /* '<Root>/getAPI19'
                                        * 日间行车灯配置，0:No DRL 1:Hardwired DRL 2:LIN DRL 3:Reserved
                                        */
INT8U ExlFrontDirLampsDiagtypePrm;     /* '<Root>/getAPI20'
                                        * 前转向灯类型配置， 0:Halogen Direction lamp fitted 1:LED Direction lamp fitted 2:LIN Direction lamp fitted 3:Reserved
                                        */
INT8U VehLowBeamTypePrm;               /* '<Root>/getAPI21'
                                        * 近光灯类型， 0:Halogen Low Beam fitted 1:Xenon Low Beam fitted 2:LED Low Beam fitted 3:Seperate LIN controller
                                        */
INT8U VehHighBeamTypePrm;              /* '<Root>/getAPI22'
                                        * 远光灯类型， 0:Halogen High Beam fitted 1:Xenon High Beam fitted 2:LED High Beam fitted 3:Seperate LIN controller 4:High Beam Solenoid fitted 5:Reserved
                                        */
INT8U ExlBeamHeightAdjustPrm;          /* '<Root>/getAPI23'
                                        * 大灯高度调节方式 0:No Height Adjust Function 1:Harewire 2:LIN 3:Reserved
                                        */
INT8U ExlFPosLampsDiagtypePrm;         /* '<Root>/getAPI24'
                                        * 前位置灯类型 0:Halogen Position lamp fitted 1:LED Position lamp fitted 2:LIN Position lamp fitted 3:Reserved
                                        */
INT8U VehEnWelLampPrm;                 /* '<Root>/getAPI25'
                                        * 是否配置迎宾灯 0:No Welcome lamp 1:Welcome lamp fitted
                                        */
INT8U VehExLampSwTypePrm;              /* '<Root>/getAPI26'
                                        * 大灯开关类型 0:Hardwire switch 1:CAN signal switch 2:LIN signal switch 3:Reserved
                                        */
INT8U VehAVMWelcomeLightEnablePrm;     /* '<Root>/getAPI27'
                                        * AVM 迎宾灯允许 0: Not Available 1： Available
                                        */
INT8U ExlMainOrDiAssistLightPrm;       /* '<Root>/getAPI28'
                                        * 远光辅助或转向辅助 0:No Assist light 1:Enable Dirlight Assist 2:Enable Main Beam Assist 3:LIN control
                                        */
INT8U ExlEnOffAutoLightPrm;            /* '<Root>/getAPI29'
                                        * 自动灯光在 OFF（大灯开关） (预留) 0:Disable 1:Enable
                                        */
INT8U ExlEnAutoLightPrm;               /* '<Root>/getAPI30'
                                        * 自动灯光使能配置字，0:Disable 1:Enable
                                        */
INT8U SecHazardPeriodNumPrm;           /* '<Root>/getAPI31'
                                        * 触发报警后双闪灯闪烁的周期个数， 0:10-period 1-9: 1-9-period A: 0-period B-F: 11-15-period
                                        */
INT8U MstWelcomeLightPrm;              /* '<Root>/getAPI32'
                                        * 迎宾灯功能是否设置激活，0:Not active 1:Active
                                        */
INT8U MstAutoFollowMePrm;              /* '<Root>/getAPI33'
                                        * 自动伴我回家功能设置，0:OFF 1:10s 2:20s 3:30s
                                        */
INT8U MstLeaveMePrm;                   /* '<Root>/getAPI34'
                                        * 伴我离家功能设置，0:OFF 1:10s 2:20s 3:30s
                                        */
INT8U MstEnWelcomeLightPrm;            /* '<Root>/getAPI35'
                                        * 迎宾灯功能设置网络使能位，0:Not active 1:Active
                                        */
INT8U MstEnFollowmeSetPrm;             /* '<Root>/getAPI36'
                                        * 自动伴我回家功能设置网络使能位，0:Not active 1:Active
                                        */
INT8U MstEnLeaveMeSetPrm;              /* '<Root>/getAPI37'
                                        * 伴我离家功能设置网络使能位，0:Not active 1:Active
                                        */
INT8U ExlBeamHeightPrm;                /* '<Root>/getAPI38'
                                        * 大灯高度调节档位设置，0x0: 0 0x1: 1 0x2: 2 0x3: 3
                                        */
INT8U ExlEnBeamHeightPrm;              /* '<Root>/getAPI39'
                                        * 大灯高度调节档位设置网络使能，0:Not active 1:Active
                                        */
INT8U MstHMAPrm;                       /* '<Root>/getAPI40'
                                        * 远光 HMA 功能配置，0:Not active 1:Active
                                        */

/* Real-time model */
RT_MODEL_Rte_get_Light_T Rte_get_Light_M_;
RT_MODEL_Rte_get_Light_T *const Rte_get_Light_M = &Rte_get_Light_M_;

/* Model step function */
void Rte_get_Light_step(void)
{
  ExLampSw = get_ExLampSw(getParam);
  TurnLampSw = get_TurnLampSw(getParam);
  HighBeamSw = get_HighBeamSw(getParam);
  HarzedLampSw = get_HarzedLampSw(getParam);
  FogLampSw = get_FogLampSw(getParam);
  ReverseLampSw = get_ReverseLampSw(getParam);
  BrakeLampSw = get_BrakeLampSw(getParam);
  FL_DIR_Fault_Sts = get_FL_DIR_Fault_Sts(getParam);
  FR_DIR_Fault_Sts = get_FR_DIR_Fault_Sts(getParam);
  DriverDoorAjar = get_DriverDoorAjar(getParam);
  PassDoorAjar = get_PassDoorAjar(getParam);
  RLeftDoorAjar = get_RLeftDoorAjar(getParam);
  RRightDoorAjar = get_RRightDoorAjar(getParam);
  TrunkDoorAjar = get_TrunkDoorAjar(getParam);
  PowerMode = get_PowerMode(getParam);
  VehOpModePrm = get_VehOpModePrm(getParam);
  VehManufMaxTimPrm = get_VehManufMaxTimPrm(getParam);
  VehManuOrAutoGearPrm = get_VehManuOrAutoGearPrm(getParam);
  VehEnFrontFogLampPrm = get_VehEnFrontFogLampPrm(getParam);
  VehEnDRLPrm = get_VehEnDRLPrm(getParam);
  ExlFrontDirLampsDiagtypePrm = get_ExlFrontDirLampsDiagtypePrm(getParam);
  VehLowBeamTypePrm = get_VehLowBeamTypePrm(getParam);
  VehHighBeamTypePrm = get_VehHighBeamTypePrm(getParam);
  ExlBeamHeightAdjustPrm = get_ExlBeamHeightAdjustPrm(getParam);
  ExlFPosLampsDiagtypePrm = get_ExlFPosLampsDiagtypePrm(getParam);
  VehEnWelLampPrm = get_VehEnWelLampPrm(getParam);
  VehExLampSwTypePrm = get_VehExLampSwTypePrm(getParam);
  VehAVMWelcomeLightEnablePrm = get_VehAVMWelcomeLightEnablePrm(getParam);
  ExlMainOrDiAssistLightPrm = get_ExlMainOrDiAssistLightPrm(getParam);
  ExlEnOffAutoLightPrm = get_ExlEnOffAutoLightPrm(getParam);
  ExlEnAutoLightPrm = get_ExlEnAutoLightPrm(getParam);
  SecHazardPeriodNumPrm = get_SecHazardPeriodNumPrm(getParam);
  MstWelcomeLightPrm = get_MstWelcomeLightPrm(getParam);
  MstAutoFollowMePrm = get_MstAutoFollowMePrm(getParam);
  MstLeaveMePrm = get_MstLeaveMePrm(getParam);
  MstEnWelcomeLightPrm = get_MstEnWelcomeLightPrm(getParam);
  MstEnFollowmeSetPrm = get_MstEnFollowmeSetPrm(getParam);
  MstEnLeaveMeSetPrm = get_MstEnLeaveMeSetPrm(getParam);
  ExlBeamHeightPrm = get_ExlBeamHeightPrm(getParam);
  ExlEnBeamHeightPrm = get_ExlEnBeamHeightPrm(getParam);
  MstHMAPrm = get_MstHMAPrm(getParam);
}

/* Model initialize function */
void Rte_get_Light_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Rte_get_Light_M, (NULL));

  /* block I/O */

  /* exported global signals */
  ExLampSw = ((INT8U)0U);
  TurnLampSw = ((INT8U)0U);
  HighBeamSw = ((INT8U)0U);
  HarzedLampSw = ((INT8U)0U);
  FogLampSw = ((INT8U)0U);
  ReverseLampSw = ((INT8U)0U);
  BrakeLampSw = ((INT8U)0U);
  FL_DIR_Fault_Sts = ((INT8U)0U);
  FR_DIR_Fault_Sts = ((INT8U)0U);
  DriverDoorAjar = ((INT8U)0U);
  PassDoorAjar = ((INT8U)0U);
  RLeftDoorAjar = ((INT8U)0U);
  RRightDoorAjar = ((INT8U)0U);
  TrunkDoorAjar = ((INT8U)0U);
  PowerMode = ((INT8U)0U);
  VehOpModePrm = ((INT8U)0U);
  VehManufMaxTimPrm = ((INT8U)5U);
  VehManuOrAutoGearPrm = ((INT8U)0U);
  VehEnFrontFogLampPrm = ((INT8U)1U);
  VehEnDRLPrm = ((INT8U)1U);
  ExlFrontDirLampsDiagtypePrm = ((INT8U)1U);
  VehLowBeamTypePrm = ((INT8U)1U);
  VehHighBeamTypePrm = ((INT8U)1U);
  ExlBeamHeightAdjustPrm = ((INT8U)1U);
  ExlFPosLampsDiagtypePrm = ((INT8U)1U);
  VehEnWelLampPrm = ((INT8U)1U);
  VehExLampSwTypePrm = ((INT8U)0U);
  VehAVMWelcomeLightEnablePrm = ((INT8U)1U);
  ExlMainOrDiAssistLightPrm = ((INT8U)0U);
  ExlEnOffAutoLightPrm = ((INT8U)0U);
  ExlEnAutoLightPrm = ((INT8U)1U);
  SecHazardPeriodNumPrm = ((INT8U)0U);
  MstWelcomeLightPrm = ((INT8U)0U);
  MstAutoFollowMePrm = ((INT8U)0U);
  MstLeaveMePrm = ((INT8U)0U);
  MstEnWelcomeLightPrm = ((INT8U)1U);
  MstEnFollowmeSetPrm = ((INT8U)1U);
  MstEnLeaveMeSetPrm = ((INT8U)1U);
  ExlBeamHeightPrm = ((INT8U)0U);
  ExlEnBeamHeightPrm = ((INT8U)1U);
  MstHMAPrm = ((INT8U)1U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
