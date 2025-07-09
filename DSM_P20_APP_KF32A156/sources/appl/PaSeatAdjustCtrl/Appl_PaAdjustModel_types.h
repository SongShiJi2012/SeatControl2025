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

/* 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节&#10;9：诊断IO控制, */
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

/* 0：无动作；&#10;1：上前；&#10;2：下后；, */
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

/* 电机动作类型：&#10;0：无动作；&#10;1：继电器下后粘连故障上前移动；&#10;2：手动开关有效上前移动；&#10;3：自动开关有效上前移动；&#10;4：继电器向下粘连故障恢复上前移动停止；&#10;5.手动开关无效上前移动停止&#10;6.自动调节开关无效上前移动停止&#10;7.继电器上前粘连故障下后移动&#10;8：手动开关有效上前移动；&#10;9：自动开关有效上前移动；&#10;A：继电器向下粘连故障恢复上前移动停止；&#10;B.手动开关无效上前移动停止&#10;C.手动开关无效上前移动停止&#10;D.自动调节开关无效上前移动停止&#10;E.自动调节开关无效下后移动停止&#10;F.超时停止&#10;10.向上堵转故障停止&#10;11.向下堵转故障停止&#10;12.向上霍尔故障停止&#10;13.向下霍尔故障停止, */
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

/* 座椅调用运动状态：&#10;0：Invalid&#10;1：Running&#10;2：Success&#10;3：Fail, */
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

/* IGN电源档位状态&#10;0：OFF&#10;1：ACC&#10;2：ON&#10;3：CRANK&#10;4：RUN, */
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

/* 电压模式:&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt, */
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
