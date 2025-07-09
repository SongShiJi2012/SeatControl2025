/*
 * File: Appl_PaAdjustModel_types.h
 *
 * Code generated for Simulink model 'Appl_PaAdjustModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu May  6 10:45:29 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaAdjustModel_types_h_
#define RTW_HEADER_Appl_PaAdjustModel_types_h_
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

#ifndef DEFINED_TYPEDEF_FOR_enSeatMoveCmd_
#define DEFINED_TYPEDEF_FOR_enSeatMoveCmd_

/* 0���޶�����&#10;1����ǰ��&#10;2���º�, */
typedef enum
{
  enSeatMoveCmd_EN_NULL = 0,           /* Default value */
  enSeatMoveCmd_EN_UP_FORWARD,
  enSeatMoveCmd_EN_DN_BACKWARD
}
enSeatMoveCmd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatHightMotorRunsts_
#define DEFINED_TYPEDEF_FOR_enSeatHightMotorRunsts_

/* ����������ͣ�&#10;0���޶�����&#10;1���̵����º�ճ��������ǰ�ƶ���&#10;2���ֶ�������Ч��ǰ�ƶ���&#10;3���Զ�������Ч��ǰ�ƶ���&#10;4���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��&#10;5.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;6.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ&#10;7.�̵�����ǰճ�������º��ƶ�&#10;8���ֶ�������Ч��ǰ�ƶ���&#10;9���Զ�������Ч��ǰ�ƶ���&#10;A���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��&#10;B.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;C.�ֶ�������Ч��ǰ�ƶ�ֹͣ&#10;D.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ&#10;E.�Զ����ڿ�����Ч�º��ƶ�ֹͣ&#10;F.��ʱֹͣ&#10;10.���϶�ת����ֹͣ&#10;11.���¶�ת����ֹͣ&#10;12.���ϻ�������ֹͣ&#10;13.���»�������ֹͣ, */
typedef enum
{
  enSeatHightMotorRunsts_EN_NULL = 0,  /* Default value */
  enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU,
  enSeatHightMotorRunsts_EN_ManualAdjust_FU,
  enSeatHightMotorRunsts_EN_AutoAdjust_FU,
  enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop,
  enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop,
  enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK,
  enSeatHightMotorRunsts_EN_ManualAdjust_BK,
  enSeatHightMotorRunsts_EN_AutoAdjust_BK,
  enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop,
  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop,
  enSeatHightMotorRunsts_EN_Timeout_Stop,
  enSeatHightMotorRunsts_EN_UpFn_Lock_Stop,
  enSeatHightMotorRunsts_EN_DnBa_Lock_Stop,
  enSeatHightMotorRunsts_EN_UpFn_Hall_Stop,
  enSeatHightMotorRunsts_EN_DnBa_Hall_Stop,
  enSeatHightMotorRunsts_EN_UpFn_MovTypeChange,
  enSeatHightMotorRunsts_EN_DnBa_MovTypeChange
}
enSeatHightMotorRunsts;

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

#ifndef DEFINED_TYPEDEF_FOR_enFinalPowerMode_
#define DEFINED_TYPEDEF_FOR_enFinalPowerMode_

/* ��ѹģʽ:&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt, */
typedef enum
{
  enFinalPowerMode_EN_STOP_VOLT = 0,   /* Default value */
  enFinalPowerMode_EN_LOW_VOLT,
  enFinalPowerMode_EN_NORMAL_VOLT,
  enFinalPowerMode_EN_HIGH_VOLT,
  enFinalPowerMode_EN_OVER_VOLT
}
enFinalPowerMode;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Appl_PaAdjustModel_T RT_MODEL_Appl_PaAdjustModel_T;

#endif                                 /* RTW_HEADER_Appl_PaAdjustModel_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
