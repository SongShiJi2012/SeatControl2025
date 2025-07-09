/*
 * File: Appl_PaLearn_CtrlModel_types.h
 *
 * Code generated for Simulink model 'Appl_PaLearn_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sun May  9 10:03:54 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaLearn_CtrlModel_types_h_
#define RTW_HEADER_Appl_PaLearn_CtrlModel_types_h_
#ifndef DEFINED_TYPEDEF_FOR_enLearnExitCause_
#define DEFINED_TYPEDEF_FOR_enLearnExitCause_

/* enInvalid (��Ч)&#10;enRelayAdhesionFault���̵������ϣ�&#10;enHallFault���������ϣ�&#10;enOTA��OTA��&#10;enVehSpeed�����ٳ�����&#10;enManualInterupt���ֶ��жϣ�&#10;enVoltFault����ѹ���ϣ�&#10;enLearnOverTime(ѧϰ��ʱ)&#10;enMotorRunOverTime_H(�߶ȵ�����г�ʱ)&#10;enMotorRunOverTime_L(���������г�ʱ)&#10;enMotorRunOverTime_B(����������г�ʱ)&#10;enMotorRunOverTime_F(���е�����г�ʱ)&#10;enDescStop(���ֹͣ)&#10;, */
typedef enum
{
  enLearnExitCause_enInvalid = 0,      /* Default value */
  enLearnExitCause_enRelayAdhesionFault,
  enLearnExitCause_enHallFault,
  enLearnExitCause_enOTA,
  enLearnExitCause_enVehSpeed,
  enLearnExitCause_enManualInterupt,
  enLearnExitCause_enVoltFault,
  enLearnExitCause_enLearnOverTime,
  enLearnExitCause_enMotorRunOverTime_H,
  enLearnExitCause_enMotorRunOverTime_L,
  enLearnExitCause_enMotorRunOverTime_B,
  enLearnExitCause_enMotorRunOverTime_F,
  enLearnExitCause_enDescStop,
  enLearnExitCause_enCfgW_ADJUST,
  enLearnExitCause_enCfgW_MEMORY
}
enLearnExitCause;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSWMoveCmd_
#define DEFINED_TYPEDEF_FOR_enSWMoveCmd_

/* 0���޶���&#10;1����ǰ&#10;2���º�, */
typedef enum
{
  enSWMoveCmd_en_NULL = 0,             /* Default value */
  enSWMoveCmd_enUP_FORWARD,
  enSWMoveCmd_enDOWN_BACK
}
enSWMoveCmd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enLearnSts_
#define DEFINED_TYPEDEF_FOR_enLearnSts_

/* 0x0:enNull;(��ѧϰ)&#10;0x1:enLearnning;��ѧϰ�У�&#10;0x2:enLearnAllSuccess;��ѧϰ�ɹ���, */
typedef enum
{
  enLearnSts_enNULL = 0,               /* Default value */
  enLearnSts_enLearnning,
  enLearnSts_enLearnAllSuccess
}
enLearnSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enDrAdjustEnable_
#define DEFINED_TYPEDEF_FOR_enDrAdjustEnable_

/* �������ε��õ������ã�&#10;0x00:manual &#10;0x01:Six way motor &#10;0x02:Twelve way motor, */
typedef enum
{
  enDrAdjustEnable_EN_DrManual = 0,    /* Default value */
  enDrAdjustEnable_EN_DrSixWayMotor,
  enDrAdjustEnable_EN_DrTwelveWayMotor
}
enDrAdjustEnable;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enBackGear_
#define DEFINED_TYPEDEF_FOR_enBackGear_

/* enNULL���޿�����λ����&#10;enBackGear_0������0����&#10;enBackGear_1������1����&#10;enBackGear_2������2����&#10;enBackGear_3������3����&#10;enBackGear_4������4����&#10;enBackGear_5������5����&#10;enBackGear_6������6����&#10;enBackGear_7������7����&#10;enBackGear_8������8����, */
typedef enum
{
  enBackGear_enNULL = 0,               /* Default value */
  enBackGear_enBackGear_0,
  enBackGear_enBackGear_1,
  enBackGear_enBackGear_2,
  enBackGear_enBackGear_3,
  enBackGear_enBackGear_4,
  enBackGear_enBackGear_5,
  enBackGear_enBackGear_6,
  enBackGear_enBackGear_7,
  enBackGear_enBackGear_8
}
enBackGear;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enFrontGear_
#define DEFINED_TYPEDEF_FOR_enFrontGear_

/* enNULL�������е�λ����&#10;enFrontGear_0������0����&#10;enFrontGear_1������1����&#10;enFrontGear_2������2����&#10;enFrontGear_3������3����&#10;enFrontGear_4������4����&#10;enFrontGear_5������5����&#10;enFrontGear_6������6����&#10;enFrontGear_7������7����&#10;enFrontGear_8������8����, */
typedef enum
{
  enFrontGear_enNULL = 0,              /* Default value */
  enFrontGear_enFrontGear_0,
  enFrontGear_enFrontGear_1,
  enFrontGear_enFrontGear_2,
  enFrontGear_enFrontGear_3,
  enFrontGear_enFrontGear_4,
  enFrontGear_enFrontGear_5,
  enFrontGear_enFrontGear_6,
  enFrontGear_enFrontGear_7,
  enFrontGear_enFrontGear_8
}
enFrontGear;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enLengthGear_
#define DEFINED_TYPEDEF_FOR_enLengthGear_

/* enNULL��������λ����&#10;enLengthGear_0������0����&#10;enLengthGear_1������1����&#10;enLengthGear_2������2����&#10;enLengthGear_3������3����&#10;enLengthGear_4������4����&#10;enLengthGear_5������5����&#10;enLengthGear_6������6����, */
typedef enum
{
  enLengthGear_enNULL = 0,             /* Default value */
  enLengthGear_enLengthGear_0,
  enLengthGear_enLengthGear_1,
  enLengthGear_enLengthGear_2,
  enLengthGear_enLengthGear_3,
  enLengthGear_enLengthGear_4,
  enLengthGear_enLengthGear_5,
  enLengthGear_enLengthGear_6
}
enLengthGear;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enResetSts_
#define DEFINED_TYPEDEF_FOR_enResetSts_

/* 0x0:Inactive&#10;0x1:Waiting&#10;0x2:Success&#10;0x3:Fail, */
typedef enum
{
  enResetSts_enInactive = 0,           /* Default value */
  enResetSts_enResetWaiting,
  enResetSts_enResetSuccess,
  enResetSts_enResetFail
}
enResetSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatAutoRunSts_
#define DEFINED_TYPEDEF_FOR_enSeatAutoRunSts_

/* ���ε����˶�״̬��&#10;0��Invalid&#10;1��Running&#10;2��Success&#10;3��Fail, */
typedef enum
{
  enSeatAutoRunSts_EN_SEAT_INVALID = 0,/* Default value */
  enSeatAutoRunSts_EN_SEAT_RUNNING,
  enSeatAutoRunSts_EN_SEAT_SUCCESS,
  enSeatAutoRunSts_EN_SEAT_FAIL
}
enSeatAutoRunSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_

/* ����������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����&#10;6����λ����&#10;7����λ����-BM400&#10;8��С����&#10;9�����IO����, */
typedef enum
{
  enSeatMotorRunTye_EN_NULL = 0,       /* Default value */
  enSeatMotorRunTye_EN_HUMEnable,
  enSeatMotorRunTye_EN_ComfortEnable,
  enSeatMotorRunTye_EN_MemoryEnable,
  enSeatMotorRunTye_EN_ManualEnable,
  enSeatMotorRunTye_EN_LearnEnable,
  enSeatMotorRunTye_EN_ResetEnable,
  enSeatMotorRunTye_EN_GearEnable,
  enSeatMotorRunTye_EN_ResEnable,
  enSeatMotorRunTye_EN_DiagIOEnable
}
enSeatMotorRunTye;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enIgnSts_
#define DEFINED_TYPEDEF_FOR_enIgnSts_

/* IGN��Դ��λ״̬&#10;0��OFF&#10;1��ACC&#10;2��ON&#10;3��CRANK&#10;4��RUN, */
typedef enum
{
  enIgnSts_eOff = 0,                   /* Default value */
  enIgnSts_eAcc,
  enIgnSts_eOn,
  enIgnSts_eCrank,
  enIgnSts_eRun
}
enIgnSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enVehTypePrm_
#define DEFINED_TYPEDEF_FOR_enVehTypePrm_

/* �������ã�&#10;0��P20&#10;1��BM400, */
typedef enum
{
  enVehTypePrm_enP20 = 0,              /* Default value */
  enVehTypePrm_enBM400
}
enVehTypePrm;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Appl_PaLearn_CtrlModel_T
  RT_MODEL_Appl_PaLearn_CtrlModel_T;

#endif                                 /* RTW_HEADER_Appl_PaLearn_CtrlModel_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
