/*
 * File: Appl_MassageMode_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_MassageMode_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:48:18 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_MassageMode_CtrlModel_h_
#define RTW_HEADER_Appl_MassageMode_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_MassageMode_CtrlModel_COMMON_INCLUDES_
# define Appl_MassageMode_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_MassageMode_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_MassageMode_CtrlModel_T
  RT_MODEL_Appl_MassageMode_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enMassageLevel_DSM_
#define DEFINED_TYPEDEF_FOR_enMassageLevel_DSM_

/* DSM����λ����Ħģ�鷴����λ:&#10;0x0:OFF&#10;0x1:Level1&#10;0x2:Level2&#10;0x3:Level3&#10;0x4:AUTO  OFF�Զ��ر�&#10;0x5:Inactive, */
typedef enum
{
  enMassageLevel_DSM_EN_OFF = 0,       /* Default value */
  enMassageLevel_DSM_EN_L1,
  enMassageLevel_DSM_EN_L2,
  enMassageLevel_DSM_EN_L3,
  enMassageLevel_DSM_EN_AUTO_OFF,
  enMassageLevel_DSM_EN_Inactive
}
enMassageLevel_DSM;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMassageMode_DSM_
#define DEFINED_TYPEDEF_FOR_enMassageMode_DSM_

/* DSM����ģʽ/��Ħģ�鷴��ģʽ:&#10;0x0:Mode1ȫ�����&#10;0x1:Mode2ȫ����&#10;0x2:Mode3�粿����&#10;0x3:Mode4�粿����&#10;0x4:Mode5��������&#10;0x5:Mode6��������&#10;0x6:Mode7��������&#10;0x7:Mode8��������&#10;0x8:����ģʽ, */
typedef enum
{
  enMassageMode_DSM_EN_M1 = 0,         /* Default value */
  enMassageMode_DSM_EN_M2,
  enMassageMode_DSM_EN_M3,
  enMassageMode_DSM_EN_M4,
  enMassageMode_DSM_EN_M5,
  enMassageMode_DSM_EN_M6,
  enMassageMode_DSM_EN_M7,
  enMassageMode_DSM_EN_M8,
  enMassageMode_DSM_EN_MError
}
enMassageMode_DSM;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMassageLevel_IVI_
#define DEFINED_TYPEDEF_FOR_enMassageLevel_IVI_

/* IVI����λ:&#10;0x0:Inactive&#10;0x1:Level1&#10;0x2:Level2&#10;0x3:Level3&#10;0x4:OFF, */
typedef enum
{
  enMassageLevel_IVI_EN_Inactive = 0,  /* Default value */
  enMassageLevel_IVI_EN_L1,
  enMassageLevel_IVI_EN_L2,
  enMassageLevel_IVI_EN_L3,
  enMassageLevel_IVI_EN_OFF
}
enMassageLevel_IVI;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMassageMode_IVI_
#define DEFINED_TYPEDEF_FOR_enMassageMode_IVI_

/* IVI����ģʽ:&#10;0x0:Inactive&#10;0x1:Mode1ȫ�����&#10;0x2:Mode2ȫ����&#10;0x3:Mode3�粿����&#10;0x4:Mode4�粿����&#10;0x5:Mode5��������&#10;0x6:Mode6��������&#10;0x7:Mode7��������&#10;0x8:Mode8��������, */
typedef enum
{
  enMassageMode_IVI_EN_Inactive = 0,   /* Default value */
  enMassageMode_IVI_EN_M1,
  enMassageMode_IVI_EN_M2,
  enMassageMode_IVI_EN_M3,
  enMassageMode_IVI_EN_M4,
  enMassageMode_IVI_EN_M5,
  enMassageMode_IVI_EN_M6,
  enMassageMode_IVI_EN_M7,
  enMassageMode_IVI_EN_M8
}
enMassageMode_IVI;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enPowerModeSts_
#define DEFINED_TYPEDEF_FOR_enPowerModeSts_

/* ��Դ��λ״̬&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK, */
typedef enum
{
  enPowerModeSts_EN_OFF = 0,           /* Default value */
  enPowerModeSts_EN_ACC,
  enPowerModeSts_EN_ON,
  enPowerModeSts_EN_CRANK
}
enPowerModeSts;

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

#ifndef DEFINED_TYPEDEF_FOR_enMasReason_
#define DEFINED_TYPEDEF_FOR_enMasReason_

/* ǰ������������ԭ��&#10;0x0:enNone���ޣ�&#10;0x1:enPowerError&#10;0x2:enRunError&#10;0x3:enNodeError&#10;0x4:enConfigError&#10;0x5:enCarTypeError&#10;0x6:enRecoverError&#10;0x6:enPowerModeError, */
typedef enum
{
  enMasReason_enNone = 0,              /* Default value */
  enMasReason_enPowerError,
  enMasReason_enRunError,
  enMasReason_enNodeError,
  enMasReason_enConfigError,
  enMasReason_enCarTypeError,
  enMasReason_enRecoverError,
  enMasReason_enPowerModeError
}
enMasReason;

#endif

/* Block signals (default storage) */
typedef struct
{
  DOUBLE SFunction_o6;                 /* '<S18>/ThresholdDeal' */
  DOUBLE SFunction_o7;                 /* '<S18>/ThresholdDeal' */
  DOUBLE SFunction_o11;                /* '<S5>/MassageLogicDeal' */
  DOUBLE SFunction_o12;                /* '<S5>/MassageLogicDeal' */
  INT32U T1Max;                        /* '<S18>/ThresholdDeal' */
  INT32U T2Max;                        /* '<S18>/ThresholdDeal' */
  INT32U T3Max;                        /* '<S18>/ThresholdDeal' */
  INT32U T4Max;                        /* '<S18>/ThresholdDeal' */
  INT32U T3timer;                      /* '<S5>/MassageLogicDeal' */
  INT32U T4timer;                      /* '<S5>/MassageLogicDeal' */
  enMassageMode_DSM Mode;              /* '<S17>/MassagePreconditionDeal' */
  enMassageMode_DSM DSM_MassageMode_Req;/* '<S5>/MassagePriority' */
  enMassageMode_DSM Mode_l;            /* '<S5>/MassagePriority' */
  enMassageMode_DSM DSM_MassageMode_FB;/* '<S5>/MassageLogicDeal' */
  enMassageMode_DSM IVIMode;           /* '<S5>/MassageLogicDeal' */
  enMassageMode_DSM MassageMode;       /* '<S5>/MassageLogicDeal' */
  enMassageMode_DSM ModeEEPROM;        /* '<S5>/MassageLogicDeal' */
  enMassageMode_DSM DSMModeFB;         /* '<S8>/MassageDistributeFunc' */
  enMassageMode_DSM DSMModeReq;        /* '<S8>/MassageDistributeFunc' */
  enMassageMode_DSM Mode_d;            /* '<S8>/MassageDistributeFunc' */
  enMassageLevel_IVI IVILevel;         /* '<S5>/MassageLogicDeal' */
  enMassageLevel_DSM Switch;           /* '<S16>/Switch' */
  enMassageLevel_DSM DSM_MassageLevel_Req;/* '<S5>/MassagePriority' */
  enMassageLevel_DSM DSM_MassageLevel_FB;/* '<S5>/MassageLogicDeal' */
  enMassageLevel_DSM MassageLevel;     /* '<S5>/MassageLogicDeal' */
  enMassageLevel_DSM DSMLevelReq;      /* '<S8>/MassageDistributeFunc' */
  enMassageLevel_DSM DSMLevelFB;       /* '<S8>/MassageDistributeFunc' */
  INT16U T2timer;                      /* '<S5>/MassageLogicDeal' */
  INT16U T1timer;                      /* '<S5>/MassageLogicDeal' */
  INT8U MassagePC_Flag;                /* '<S17>/MassagePreconditionDeal' */
  INT8U MassagePCStopReason;           /* '<S17>/MassagePreconditionDeal' */
  INT8U MassagePCStopReason_l;         /* '<S1>/BusConversion_InsertedFor_LogicOut_at_inport_0' */
  INT8U MassageLevel_Req;              /* '<S5>/MassageLogicDeal' */
  INT8U MassageMode_Req;               /* '<S5>/MassageLogicDeal' */
  INT8U AcTCount;                      /* '<S5>/MassageLogicDeal' */
  INT8U LostFlag;                      /* '<S5>/MassageLogicDeal' */
}
B_Appl_MassageMode_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enMassageLevel_DSM Mas_Res_MassageLevel_Req_start;/* '<S5>/MassagePriority' */
  enMassageLevel_DSM Mas_Massage_LevelSts_FB_start;/* '<S5>/MassageLogicDeal' */
  enMassageLevel_DSM LevelFB;          /* '<S8>/MassageDistributeFunc' */
  enMassageLevel_IVI Mas_IVI_MassageLevel_Req_start;/* '<S5>/MassageLogicDeal' */
  INT16U RecoverDefaultDelayTimer;     /* '<S17>/MassagePreconditionDeal' */
  INT8U is_active_c1_Appl_MassageMode_CtrlModel;/* '<S18>/ThresholdDeal' */
  INT8U is_active_c11_Appl_MassageMode_CtrlModel;/* '<S17>/MassagePreconditionDeal' */
  INT8U is_c11_Appl_MassageMode_CtrlModel;/* '<S17>/MassagePreconditionDeal' */
  INT8U is_active_c6_Appl_MassageMode_CtrlModel;/* '<S5>/MassagePriority' */
  INT8U MassageLevel_Req_start;        /* '<S5>/MassagePriority' */
  INT8U MassageMode_Req_start;         /* '<S5>/MassagePriority' */
  INT8U is_active_c8_Appl_MassageMode_CtrlModel;/* '<S5>/MassageLogicDeal' */
  INT8U is_c8_Appl_MassageMode_CtrlModel;/* '<S5>/MassageLogicDeal' */
  INT8U is_MassageActive;              /* '<S5>/MassageLogicDeal' */
  INT8U is_MassageInactive;            /* '<S5>/MassageLogicDeal' */
  INT8U AutoOffFlag;                   /* '<S5>/MassageLogicDeal' */
  INT8U MassageOpenFlag;               /* '<S5>/MassageLogicDeal' */
  INT8U ExitFlag;                      /* '<S5>/MassageLogicDeal' */
  INT8U Timer_TutoOff;                 /* '<S5>/MassageLogicDeal' */
  INT8U is_active_c5_Appl_MassageMode_CtrlModel;/* '<S8>/MassageDistributeFunc' */
}
DW_Appl_MassageMode_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_MassageMode_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_MassageMode_CtrlModel_T Appl_MassageMode_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_MassageMode_CtrlModel_T Appl_MassageMode_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVehTypePrm Mas_VehiclePrm;    /* '<S15>/Mas_VehiclePrm'
                                        * ��������
                                        */
extern enPowerModeSts Mas_PowerMode;   /* '<S15>/Mas_PowerMode'
                                        * ������Դ��λ
                                        */
extern enMassageMode_IVI Mas_IVI_MassageMode_Req;/* '<S15>/Mas_IVI_MassageMode_Req'
                                                  * �����İ�Ħ��ʽ����&#10;0x0��Inactive&#10;0x1: è����ȫ�����&#10;0x2: �����Ρ�ȫ����&#10;0x3����չ�Ρ��粿����&#10;0x4: �������粿����&#10;0x5���粿����������&#10;0x6�����Ρ���������&#10;0x7�����š���������&#10;0x8�����Ρ���������&#10;0x9-0x14��Reserved
                                                  */
extern enMassageMode_DSM Mas_Massage_ModeSts_FB;/* '<S15>/Mas_Massage_ModeSts_FB'
                                                 * ��Ħģʽ����-LIN&#10;0x0: ȫ�����&#10;0x1: ȫ����&#10;0x2���粿����&#10;0x3: �粿����&#10;0x4����������&#10;0x5����������&#10;0x6����������&#10;0x7����������&#10;0x8��Errorģ�����&#10;0x9~0xE��Reserved
                                                 */
extern enMassageMode_DSM Mas_Res_MassageMode_Req;/* '<S15>/Mas_Res_MassageMode_Req'
                                                  * С�İ�Ħģʽ����
                                                  */
extern enMassageMode_DSM Mas_SeatMassageMode;/* '<S15>/Mas_SeatMassageMode'
                                              * ��Ħģʽ������&#10; 0x0: ȫ�����&#10; 0x1: ȫ����&#10; 0x2���粿����&#10; 0x3: �粿����&#10; 0x4����������&#10; 0x5����������&#10; 0x6����������&#10; 0x7����������&#10; 0x8��Errorģ�����
                                              */
extern enMassageLevel_IVI Mas_IVI_MassageLevel_Req;/* '<S15>/Mas_IVI_MassageLevel_Req'
                                                    * �����İ�Ħ��λ����&#10;0x0:Inactive&#10;0x1: Level 1&#10;0x2: Level 2&#10;0x3: Level 3&#10;0x4: OFF
                                                    */
extern enMassageLevel_DSM Mas_Massage_LevelSts_FB;/* '<S15>/Mas_Massage_LevelSts_FB'
                                                   * ��Ħģ��ĵ�λ����-LIN&#10;0x0:OFF&#10;0x1: Level 1&#10;0x2: Level 2&#10;0x3: Level 3&#10;0x4: AUTO  OFF�Զ��ر�
                                                   */
extern enMassageLevel_DSM Mas_Res_MassageLevel_Req;/* '<S15>/Mas_Res_MassageLevel_Req'
                                                    * С�İ�Ħ��λ����
                                                    */
extern enFinalPowerMode Mas_VoltMode;  /* '<S15>/Mas_VoltMode'
                                        * ������ѹģʽ&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
extern INT16U Mas_DiagTimeT1;          /* '<S15>/Mas_DiagTimeT1'
                                        * T1��ֵ
                                        */
extern INT16U Mas_DiagTimeT2;          /* '<S15>/Mas_DiagTimeT2'
                                        * T2��ֵ
                                        */
extern INT16U Mas_DiagTimeT3;          /* '<S15>/Mas_DiagTimeT3'
                                        * T3��ֵ
                                        */
extern INT16U Mas_DiagTimeT4;          /* '<S15>/Mas_DiagTimeT4'
                                        * T4��ֵ
                                        */
extern INT8U Mas_EngineRunFlag;        /* '<S15>/Mas_EngineRunFlag'
                                        * ����������״̬&#10;0����Ч&#10;1����Ч
                                        */
extern INT8U Mas_IVI_NapMode_SwtichSet;/* '<S15>/Mas_IVI_NapMode_SwtichSet'
                                        * �ģʽ�������趨&#10;0x0:Inactive&#10;0x1:��С�ģʽ&#10;0x2:�ر�С�ģʽ&#10;0x3:Reserved
                                        */
extern INT8U Mas_Massage_0x1B_LostFlag;/* '<S15>/Mas_Massage_0x1B_LostFlag'
                                        * LIN��ʧ��־λ
                                        */
extern INT8U Mas_RecoverDefaultFlag;   /* '<S15>/Mas_RecoverDefaultFlag'
                                        * �ָ���������&#10;0����Ч��&#10;1����Ч
                                        */
extern INT8U Mas_SeatMassageCfg;       /* '<S15>/Mas_SeatMassageCfg'
                                        *  ��Ħ��������ʹ�ܱ�־λ
                                        */
extern INT8U Mas_VehicleRunFlag;       /* '<S15>/Mas_VehicleRunFlag'
                                        * ��������״̬&#10;0����Ч&#10;1����Ч
                                        */

/* Model entry point functions */
extern void Appl_MassageMode_CtrlModel_initialize(void);
extern void Appl_MassageMode_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_MassageMode_CtrlModel_T *const Appl_MassageMode_CtrlModel_M;

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
 * '<Root>' : 'Appl_MassageMode_CtrlModel'
 * '<S1>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_MassageMode_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_MassageMode_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_MassageMode_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal'
 * '<S6>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal'
 * '<S7>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassagePriority'
 * '<S8>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal/MassageDistributeFunc'
 * '<S9>'   : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal/MemCallWaitFBFunc'
 * '<S10>'  : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal/MassageDistributeFunc/MassageDistributeFunc'
 * '<S11>'  : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal/MassageDistributeFunc/MassageDistributeFunc/SaveMassageMode'
 * '<S12>'  : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassageLogicDeal/MemCallWaitFBFunc/Chart'
 * '<S13>'  : 'Appl_MassageMode_CtrlModel/LogicCtrl/MassageLogicDeal/MassagePriority/SaveMassageMode'
 * '<S14>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S15>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/RTE'
 * '<S16>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/LinLostDeal'
 * '<S17>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/MassagePreconditionDeal'
 * '<S18>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal'
 * '<S19>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/MassagePreconditionDeal/MassagePreconditionDeal'
 * '<S20>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/MassagePreconditionDeal/MassagePreconditionDeal/SaveMassageMode'
 * '<S21>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal/ThresholdDeal'
 * '<S22>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal/ThresholdDeal/MassageTimeCaliFunc'
 * '<S23>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal/ThresholdDeal/MemCallWaitFBFunc'
 * '<S24>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal/ThresholdDeal/MassageTimeCaliFunc/MassageTimeCaliFunc'
 * '<S25>'  : 'Appl_MassageMode_CtrlModel/UpDataInputInfo/InputSignalProcess/ThresholdDeal/ThresholdDeal/MemCallWaitFBFunc/Chart'
 */
#endif                                 /* RTW_HEADER_Appl_MassageMode_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
