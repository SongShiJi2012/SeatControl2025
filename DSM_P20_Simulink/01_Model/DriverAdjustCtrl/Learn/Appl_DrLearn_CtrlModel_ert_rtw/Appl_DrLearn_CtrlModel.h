/*
 * File: Appl_DrLearn_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_DrLearn_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:36:37 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_DrLearn_CtrlModel_h_
#define RTW_HEADER_Appl_DrLearn_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_DrLearn_CtrlModel_COMMON_INCLUDES_
# define Appl_DrLearn_CtrlModel_COMMON_INCLUDES_
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
#include "LdfFile_RLS_TwoInOne_V10.h"
#include "hal_lin.h"
#include "Appl_DtcSetConditionCheck.h"
#include "ecual_pins.h"
#endif                                 /* Appl_DrLearn_CtrlModel_COMMON_INCLUDES_ */

/* Includes for objects with custom storage classes. */
#include "Common.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Appl_DrLearn_CtrlModel_T
  RT_MODEL_Appl_DrLearn_CtrlModel_T;

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
B_Appl_DrLearn_CtrlModel_T;

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
  enDrAdjustEnable MtrCtrl_AdjustEnable_start;/* '<S7>/Learn' */
  enVehTypePrm MtrCtrl_VehiclePrm_start;/* '<S9>/Reset' */
  INT16U LearnAllRunTime;              /* '<S7>/Learn' */
  INT8U is_active_c2_Appl_DrLearn_CtrlModel;/* '<S9>/Reset' */
  INT8U is_c2_Appl_DrLearn_CtrlModel;  /* '<S9>/Reset' */
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
  INT8U is_active_c7_Appl_DrLearn_CtrlModel;/* '<S16>/OneClickResetConditionProcess' */
  INT8U is_c7_Appl_DrLearn_CtrlModel;  /* '<S16>/OneClickResetConditionProcess' */
  INT8U is_active_c42_Appl_DrLearn_CtrlModel;/* '<S7>/Learn' */
  INT8U is_c42_Appl_DrLearn_CtrlModel; /* '<S7>/Learn' */
  INT8U is_LearnLogicalDeal;           /* '<S7>/Learn' */
  INT8U Hight;                         /* '<S7>/Learn' */
  INT8U Length_c;                      /* '<S7>/Learn' */
  INT8U Back_e;                        /* '<S7>/Learn' */
  INT8U LearnResult;                   /* '<S7>/Learn' */
  INT8U MotorMtrCtrl_LearnSts;         /* '<S7>/Learn' */
  INT8U Front_p;                       /* '<S7>/Learn' */
  INT8U MtrCtrl_DiagnoseLearnIn_start; /* '<S7>/Learn' */
  INT8U is_active_c1_Appl_DrLearn_CtrlModel;/* '<S6>/AutoLearnCmdProcess' */
  INT8U is_PublicPreconditionJudgment; /* '<S6>/AutoLearnCmdProcess' */
}
DW_Appl_DrLearn_CtrlModel_T;

/* Invariant block signals (default storage) */
typedef struct
{
  const DOUBLE MtrCtrl_HIDO_SeatsButtonResetReq;/* '<S20>/Constant6' */
}
ConstB_Appl_DrLearn_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_DrLearn_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_DW;
extern const ConstB_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_ConstB;/* constant block i/o */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVehTypePrm DrLearn_VehiclePrm;/* '<S21>/DrLearn_VehiclePrm'
                                        * ���ͣ�C62X��C52X��
                                        */
extern enSeatMotorRunTye DrLearn_CurrMotorCtrlType;/* '<S21>/DrLearn_CurrMotorCtrlType'
                                                    * ��ǰ��������
                                                    */
extern enSeatAutoRunSts DrLearn_BackAutoRunFlag;/* '<S21>/DrLearn_BackAutoRunFlag'
                                                 * ���ݿ����Զ����б�־λ
                                                 */
extern enSeatAutoRunSts DrLearn_FrontAutoRunFlag;/* '<S21>/DrLearn_FrontAutoRunFlag'
                                                  * ����ǰ���Ƕ��Զ����б�־λ
                                                  */
extern enSeatAutoRunSts DrLearn_HeightAutoRunFlag;/* '<S21>/DrLearn_HeightAutoRunFlag'
                                                   * ���ݸ߶��Զ����б�־λ
                                                   */
extern enSeatAutoRunSts DrLearn_LengthAutoRunFlag;/* '<S21>/DrLearn_LengthAutoRunFlag'
                                                   * ���������Զ����б�־λ
                                                   */
extern enIgnSts DrLearn_PowerModeStatus;/* '<S21>/DrLearn_PowerModeStatus'
                                         * ������Դ��λ
                                         */
extern enDrAdjustEnable DrLearn_AdjustEnable;/* '<S21>/DrLearn_AdjustEnable'
                                              * �������ε���:
                                              */
extern INT16U DrLearn_BackDefaultStopPos;/* '<S21>/DrLearn_BackDefaultStopPos'
                                          * ����Ӳֹ��
                                          */
extern INT16U DrLearn_FrontDefaulStoptPos;/* '<S21>/DrLearn_FrontDefaulStoptPos'
                                           * ����Ӳֹ��
                                           */
extern INT16U DrLearn_HeightDefaultStopPos;/* '<S21>/DrLearn_HeightDefaultStopPos'
                                            * �߶�Ӳֹ��
                                            */
extern INT16U DrLearn_LengthDefaultStopPos;/* '<S21>/DrLearn_LengthDefaultStopPos'
                                            * ����Ӳֹ��
                                            */
extern INT8U DrLearn_AnyoneHallErr;    /* '<S21>/DrLearn_AnyoneHallErr'
                                        * ��һ�������ϱ�־
                                        */
extern INT8U DrLearn_AnyoneRelayAdheErr;/* '<S21>/DrLearn_AnyoneRelayAdheErr'
                                         * ��һ�̵���ճ�����ϱ�־
                                         */
extern INT8U DrLearn_BackMotorTimeOutErr;/* '<S21>/DrLearn_BackMotorTimeOutErr'
                                          * ����������г�ʱ��־
                                          */
extern INT8U DrLearn_BackStallErr;     /* '<S21>/DrLearn_BackStallErr'
                                        * ������ת��־λ
                                        */
extern INT8U DrLearn_DescSession;      /* '<S21>/DrLearn_DescSession'
                                        * �Ự
                                        */
extern INT8U DrLearn_DiagnoseLearnIn;  /* '<S21>/DrLearn_DiagnoseLearnIn'
                                        * ����ѧϰ��־
                                        */
extern INT8U DrLearn_FrontMotorTimeOutErr;/* '<S21>/DrLearn_FrontMotorTimeOutErr'
                                           * ���е�����г�ʱ��־
                                           */
extern INT8U DrLearn_FrontStallErr;    /* '<S21>/DrLearn_FrontStallErr'
                                        * ���ж�ת��־λ
                                        */
extern INT8U DrLearn_GetRecoverDefaultFlag;/* '<S21>/DrLearn_GetRecoverDefaultFlag'
                                            * �ָ���������
                                            */
extern INT8U DrLearn_HeightMotorTimeOutErr;/* '<S21>/DrLearn_HeightMotorTimeOutErr'
                                            * �߶ȵ�����г�ʱ��־
                                            */
extern INT8U DrLearn_HeightStallErr;   /* '<S21>/DrLearn_HeightStallErr'
                                        * �߶ȶ�ת��־λ
                                        */
extern INT8U DrLearn_LearnSts;         /* '<S21>/DrLearn_LearnSts'
                                        * ѧϰ״̬
                                        */
extern INT8U DrLearn_LengthMotorTimeOutErr;/* '<S21>/DrLearn_LengthMotorTimeOutErr'
                                            * ���������г�ʱ��־
                                            */
extern INT8U DrLearn_LengthStallErr;   /* '<S21>/DrLearn_LengthStallErr'
                                        * �����ת��־λ
                                        */
extern INT8U DrLearn_OTAMode;          /* '<S21>/DrLearn_OTAMode'
                                        * OTA-P20ΪԤ��
                                        */
extern INT8U DrLearn_VehSpdUnder3KMFlag;/* '<S21>/DrLearn_VehSpdUnder3KMFlag'
                                         * ���ٴ���3�ı�־λ
                                         */
extern INT8U DrLearn_VoltSatisfy;      /* '<S21>/DrLearn_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */
extern INT8U DrLearn_WelcomeEnable;    /* '<S21>/DrLearn_WelcomeEnable'
                                        * ����ӭ��ʹ��״̬
                                        */

/* Model entry point functions */
extern void Appl_DrLearn_CtrlModel_initialize(void);
extern void Appl_DrLearn_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_DrLearn_CtrlModel_T *const Appl_DrLearn_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT32U CAL_LearnAllTimeMax_150s;/* ȫ��ѧϰ�ʱ�䣺150s */
extern const volatile INT16U CAL_LearnSingleTimeMax_60s;/* ѧϰ�ʱ�䣺60s */

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
 * '<Root>' : 'Appl_DrLearn_CtrlModel'
 * '<S1>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_DrLearn_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_DrLearn_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_DrLearn_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnConditionDeal'
 * '<S7>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal'
 * '<S8>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal'
 * '<S9>'   : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetReqDeal'
 * '<S10>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnConditionDeal/AutoLearnCmdProcess'
 * '<S11>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn'
 * '<S12>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/MotorLearnOrderPrm'
 * '<S13>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/SetDescLearnSts'
 * '<S14>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/SetDescLearnStsForDebug'
 * '<S15>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/LearnReqDeal/Learn/MotorLearnOrderPrm/Chart'
 * '<S16>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess'
 * '<S17>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess/Enumerated Constant'
 * '<S18>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetConditionDeal/OneClickResetConditionProcess/OneClickResetConditionProcess'
 * '<S19>'  : 'Appl_DrLearn_CtrlModel/LogicCtrl/LocalAdjustCtrl/ResetReqDeal/Reset'
 * '<S20>'  : 'Appl_DrLearn_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S21>'  : 'Appl_DrLearn_CtrlModel/UpDataInputInfo/RTE'
 */
#endif                                 /* RTW_HEADER_Appl_DrLearn_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
