/*
 * File: Appl_PaLearn_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_PaLearn_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:51:19 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaLearn_CtrlModel_h_
#define RTW_HEADER_Appl_PaLearn_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_PaLearn_CtrlModel_COMMON_INCLUDES_
# define Appl_PaLearn_CtrlModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Ecual_Adc.h"
#include "Rte_VfbInterface.h"
#include "Cdd_Hall.h"
#include "Srvl_E2cfg.h"
#include "Srvl_E2memory.h"
#include "Ecual_AdcMotor.h"
#include "CpuPeripheralInit.h"
#include "Srvl_PowerMode.h"
#include "Desc.h"
#include "Test.h"
#include "Rte_CanInterface.h"
#include "Srvl_CanSignals.h"
#include "Debug_VfbInterface.h"
#include "LdfFile_DSM_TwoInOne_V10.h"
#include <Ecual_lin.h>
#include "Appl_DtcSetConditionCheck.h"
#include "ecual_pins.h"
#endif                                 /* Appl_PaLearn_CtrlModel_COMMON_INCLUDES_ */

#include "Appl_PaLearn_CtrlModel_types.h"

/* Includes for objects with custom storage classes. */
#include "Appl_DrLearn_CtrlModel.h"
#include "Common.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct
{
  DOUBLE SFunction_o8;                 /* '<S7>/Learn' */
  DOUBLE SFunction_o9;                 /* '<S7>/Learn' */
  enSWMoveCmd HeightLearnSW;           /* '<S7>/Learn' */
  enSWMoveCmd LengthLearnSW;           /* '<S7>/Learn' */
  enSWMoveCmd BackLearnSW;             /* '<S7>/Learn' */
  enSWMoveCmd FrontLearnSW;            /* '<S7>/Learn' */
  enResetSts ResetSts;                 /* '<S9>/Reset' */
  enLearnSts MtrCtrl_LearnSts;         /* '<S7>/Learn' */
  enLearnExitCause LearnExitCause;     /* '<S7>/Learn' */
  enLearnExitCause LearnConditionExitCause;/* '<S6>/AutoLearnCmdProcess' */
  INT16U HeightPosiReq;                /* '<S9>/Reset' */
  INT16U LengthPosiReq;                /* '<S9>/Reset' */
  INT16U BackPosiReq;                  /* '<S9>/Reset' */
  INT16U FrontPosiReq;                 /* '<S9>/Reset' */
  INT8U DataTypeConversion;            /* '<S16>/Data Type Conversion' */
  INT8U Sts;                           /* '<S7>/Learn' */
  BOOL MtrCtrl_BackGear_4Posi;         /* '<S20>/Constant14' */
  BOOL MtrCtrl_LengthGear_0Posi;       /* '<S20>/Constant19' */
  BOOL MtrCtrl_enFrontGear_0Posi;      /* '<S20>/Constant26' */
  BOOL MtrCtrl_MotorResetFunPrm;       /* '<S20>/Constant5' */
}
B_Appl_PaLearn_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  DOUBLE MtrCtrl_HIDO_SeatsButtonResetReq_start;/* '<S9>/Reset' */
  DOUBLE L_Move;                       /* '<S7>/Learn' */
  DOUBLE HeightLearnTimer;             /* '<S7>/Learn' */
  DOUBLE LengthLearnTimer;             /* '<S7>/Learn' */
  DOUBLE BackLearnTimer;               /* '<S7>/Learn' */
  DOUBLE FrontLearnTimer;              /* '<S7>/Learn' */
  enSWMoveCmd H_Move;                  /* '<S7>/Learn' */
  enSWMoveCmd B_Move;                  /* '<S7>/Learn' */
  enSWMoveCmd F_Move;                  /* '<S7>/Learn' */
  enLearnSts MtrCtrl_LearnSts_start;   /* '<S9>/Reset' */
  enVehTypePrm MtrCtrl_VehiclePrm_start;/* '<S9>/Reset' */
  INT16U LearnAllRunTime;              /* '<S7>/Learn' */
  INT8U is_active_c2_Appl_PaLearn_CtrlModel;/* '<S9>/Reset' */
  INT8U is_c2_Appl_PaLearn_CtrlModel;  /* '<S9>/Reset' */
  INT8U is_PositionTransform;          /* '<S9>/Reset' */
  INT8U is_ResetPosition;              /* '<S9>/Reset' */
  INT8U Height;                        /* '<S9>/Reset' */
  INT8U Length;                        /* '<S9>/Reset' */
  INT8U Back;                          /* '<S9>/Reset' */
  INT8U Front;                         /* '<S9>/Reset' */
  INT8U CurrentResetSts;               /* '<S9>/Reset' */
  INT8U ResetResult;                   /* '<S9>/Reset' */
  INT8U MotorResetSts;                 /* '<S9>/Reset' */
  INT8U ResetType;                     /* '<S9>/Reset' */
  INT8U SendTimer;                     /* '<S9>/Reset' */
  INT8U RestTimer;                     /* '<S9>/Reset' */
  INT8U is_active_c7_Appl_PaLearn_CtrlModel;/* '<S16>/OneClickResetConditionProcess' */
  INT8U is_c7_Appl_PaLearn_CtrlModel;  /* '<S16>/OneClickResetConditionProcess' */
  INT8U is_active_c42_Appl_PaLearn_CtrlModel;/* '<S7>/Learn' */
  INT8U is_c42_Appl_PaLearn_CtrlModel; /* '<S7>/Learn' */
  INT8U is_LearnLogicalDeal;           /* '<S7>/Learn' */
  INT8U Hight;                         /* '<S7>/Learn' */
  INT8U Length_c;                      /* '<S7>/Learn' */
  INT8U Back_e;                        /* '<S7>/Learn' */
  INT8U LearnResult;                   /* '<S7>/Learn' */
  INT8U MotorMtrCtrl_LearnSts;         /* '<S7>/Learn' */
  INT8U Front_p;                       /* '<S7>/Learn' */
  INT8U MtrCtrl_DiagnoseLearnIn_start; /* '<S7>/Learn' */
  INT8U MtrCtrl_AdjustEnable_start;    /* '<S7>/Learn' */
  INT8U is_active_c1_Appl_PaLearn_CtrlModel;/* '<S6>/AutoLearnCmdProcess' */
  INT8U is_PublicPreconditionJudgment; /* '<S6>/AutoLearnCmdProcess' */
}
DW_Appl_PaLearn_CtrlModel_T;

/* Invariant block signals (default storage) */
typedef struct
{
  const DOUBLE MtrCtrl_HIDO_SeatsButtonResetReq;/* '<S20>/Constant6' */
}
ConstB_Appl_PaLearn_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_PaLearn_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_DW;
extern const ConstB_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_ConstB;/* constant block i/o */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVehTypePrm PaLearn_VehiclePrm;/* '<S21>/PaLearn_VehiclePrm'
                                        * 车型：C62X、C52X…
                                        */
extern enSeatMotorRunTye PaLearn_CurrMotorCtrlType;/* '<S21>/PaLearn_CurrMotorCtrlType'
                                                    * 副驾当前操作类型
                                                    */
extern enSeatAutoRunSts PaLearn_BackAutoRunFlag;/* '<S21>/PaLearn_BackAutoRunFlag'
                                                 * 副驾靠背自动运行标志位
                                                 */
extern enSeatAutoRunSts PaLearn_FrontAutoRunFlag;/* '<S21>/PaLearn_FrontAutoRunFlag'
                                                  * 副驾前部角度自动运行标志位
                                                  */
extern enSeatAutoRunSts PaLearn_HeightAutoRunFlag;/* '<S21>/PaLearn_HeightAutoRunFlag'
                                                   * 副驾高度自动运行标志位
                                                   */
extern enSeatAutoRunSts PaLearn_LengthAutoRunFlag;/* '<S21>/PaLearn_LengthAutoRunFlag'
                                                   * 副驾纵向自动运行标志位
                                                   */
extern enIgnSts PaLearn_PowerModeStatus;/* '<S21>/PaLearn_PowerModeStatus'
                                         * 整车电源档位
                                         */
extern INT16U PaLearn_BackDefaultStopPos;/* '<S21>/PaLearn_BackDefaultStopPos'
                                          * 副驾靠背硬止点
                                          */
extern INT16U PaLearn_FrontDefaulStoptPos;/* '<S21>/PaLearn_FrontDefaulStoptPos'
                                           * 副驾腿托硬止点
                                           */
extern INT16U PaLearn_HeightDefaultStopPos;/* '<S21>/PaLearn_HeightDefaultStopPos'
                                            * 副驾高度硬止点
                                            */
extern INT16U PaLearn_LengthDefaultStopPos;/* '<S21>/PaLearn_LengthDefaultStopPos'
                                            * 副驾纵向硬止点
                                            */
extern INT8U PaLearn_AdjustEnable;     /* '<S21>/PaLearn_AdjustEnable'
                                        * 座椅调节:
                                        */
extern INT8U PaLearn_AnyoneHallErr;    /* '<S21>/PaLearn_AnyoneHallErr'
                                        * 副驾任一霍尔故障标志
                                        */
extern INT8U PaLearn_AnyoneRelayAdheErr;/* '<S21>/PaLearn_AnyoneRelayAdheErr'
                                         * 副驾任一继电器粘连故障标志
                                         */
extern INT8U PaLearn_BackMotorTimeOutErr;/* '<S21>/PaLearn_BackMotorTimeOutErr'
                                          * 副驾靠背电机运行超时标志
                                          */
extern INT8U PaLearn_BackStallErr;     /* '<S21>/PaLearn_BackStallErr'
                                        * 副驾靠背堵转标志位
                                        */
extern INT8U PaLearn_DescSession;      /* '<S21>/PaLearn_DescSession'
                                        * 会话
                                        */
extern INT8U PaLearn_DiagnoseLearnIn;  /* '<S21>/PaLearn_DiagnoseLearnIn'
                                        * 副驾请求学习标志
                                        */
extern INT8U PaLearn_FrontMotorTimeOutErr;/* '<S21>/PaLearn_FrontMotorTimeOutErr'
                                           * 副驾腿托电机运行超时标志
                                           */
extern INT8U PaLearn_FrontStallErr;    /* '<S21>/PaLearn_FrontStallErr'
                                        * 副驾腿托堵转标志位
                                        */
extern INT8U PaLearn_GetRecoverDefaultFlag;/* '<S21>/PaLearn_GetRecoverDefaultFlag'
                                            * 恢复出厂设置
                                            */
extern INT8U PaLearn_HeightMotorTimeOutErr;/* '<S21>/PaLearn_HeightMotorTimeOutErr'
                                            * 副驾高度电机运行超时标志
                                            */
extern INT8U PaLearn_HeightStallErr;   /* '<S21>/PaLearn_HeightStallErr'
                                        * 副驾高度堵转标志位
                                        */
extern INT8U PaLearn_LearnSts;         /* '<S21>/PaLearn_LearnSts'
                                        * 副驾学习状态
                                        */
extern INT8U PaLearn_LengthMotorTimeOutErr;/* '<S21>/PaLearn_LengthMotorTimeOutErr'
                                            * 副驾纵向电机运行超时标志
                                            */
extern INT8U PaLearn_LengthStallErr;   /* '<S21>/PaLearn_LengthStallErr'
                                        * 副驾纵向堵转标志位
                                        */
extern INT8U PaLearn_OTAMode;          /* '<S21>/PaLearn_OTAMode'
                                        * OTA-P20为预留信号
                                        */
extern INT8U PaLearn_VehSpdUnder3KMFlag;/* '<S21>/PaLearn_VehSpdUnder3KMFlag'
                                         * 车速大于3的标志位
                                         */
extern INT8U PaLearn_VoltSatisfy;      /* '<S21>/PaLearn_VoltSatisfy'
                                        * 电机调节电压是否满足
                                        */
extern INT8U PaLearn_WelcomeEnable;    /* '<S21>/PaLearn_WelcomeEnable'
                                        * 副驾迎宾使能状态
                                        */

/* Model entry point functions */
extern void Appl_PaLearn_CtrlModel_initialize(void);
extern void Appl_PaLearn_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_PaLearn_CtrlModel_T *const Appl_PaLearn_CtrlModel_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Appl_PaLearn_CtrlModel'
 * '<S1>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_PaLearn_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_PaLearn_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_PaLearn_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnConditionDeal'
 * '<S7>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal'
 * '<S8>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal'
 * '<S9>'   : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetReqDeal'
 * '<S10>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnConditionDeal/AutoLearnCmdProcess'
 * '<S11>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn'
 * '<S12>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/MotorLearnOrderPrm'
 * '<S13>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/SetDescLearnSts'
 * '<S14>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/SetDescLearnStsForDebug'
 * '<S15>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/MotorLearnOrderPrm/Chart'
 * '<S16>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess'
 * '<S17>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess/Enumerated Constant'
 * '<S18>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess/OneClickResetConditionProcess'
 * '<S19>'  : 'Appl_PaLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetReqDeal/Reset'
 * '<S20>'  : 'Appl_PaLearn_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S21>'  : 'Appl_PaLearn_CtrlModel/UpDataInputInfo/RTE'
 * '<S22>'  : 'Appl_PaLearn_CtrlModel/UpDataOutputInfo/HardwareOutput'
 */
#endif                                 /* RTW_HEADER_Appl_PaLearn_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
