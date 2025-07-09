/*
 * File: Appl_HeatFault_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_HeatFault_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jun  5 14:54:30 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_HeatFault_CtrlModel_h_
#define RTW_HEADER_Appl_HeatFault_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_HeatFault_CtrlModel_COMMON_INCLUDES_
# define Appl_HeatFault_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_HeatFault_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_HeatFault_CtrlModel_T
  RT_MODEL_Appl_HeatFault_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enHeatLvlSts_
#define DEFINED_TYPEDEF_FOR_enHeatLvlSts_

/* 加热档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3, */
typedef enum
{
  enHeatLvlSts_EN_HEAT_LVL_OFF = 0,    /* Default value */
  enHeatLvlSts_EN_HEAT_LVL_1,
  enHeatLvlSts_EN_HEAT_LVL_2,
  enHeatLvlSts_EN_HEAT_LVL_3
}
enHeatLvlSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enHeatCmdFault_
#define DEFINED_TYPEDEF_FOR_enHeatCmdFault_

/* 加热故障&#10;0：无故障&#10;1：短路到地&#10;2：开路, */
typedef enum
{
  enHeatCmdFault_EN_HEAT_FAULT_NONE = 0,/* Default value */
  enHeatCmdFault_EN_HEAT_FAULT_GND,
  enHeatCmdFault_EN_HEAT_FAULT_OPEN
}
enHeatCmdFault;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enHeatNtcFault_
#define DEFINED_TYPEDEF_FOR_enHeatNtcFault_

/* NTC故障&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误, */
typedef enum
{
  enHeatNtcFault_EN_NTC_FAULT_NONE = 0,/* Default value */
  enHeatNtcFault_EN_NTC_FAULT_GND,
  enHeatNtcFault_EN_NTC_FAULT_OPEN,
  enHeatNtcFault_EN_NTC_FAULT_UNC
}
enHeatNtcFault;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enHeatIoSts_
#define DEFINED_TYPEDEF_FOR_enHeatIoSts_

/* 加热硬线状态&#10;0：低电平&#10;1：高电平, */
typedef enum
{
  enHeatIoSts_EN_HEAT_IO_LOW = 0,      /* Default value */
  enHeatIoSts_EN_HEAT_IO_HIGH
}
enHeatIoSts;

#endif

/* Block states (default storage) for system '<S6>/HeatCmdAquireFunction' */
typedef struct
{
  INT8U is_active_c2_Appl_HeatFault_CtrlModel;/* '<S8>/HeatCmdAquireFunction' */
  INT8U is_c2_Appl_HeatFault_CtrlModel;/* '<S8>/HeatCmdAquireFunction' */
}
DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T;

/* Block states (default storage) for system '<S7>/HeatCmdDiagnoseFunction' */
typedef struct
{
  INT8U is_active_c4_Appl_HeatFault_CtrlModel;/* '<S14>/HeatCmdDiagnose' */
  INT8U is_c4_Appl_HeatFault_CtrlModel;/* '<S14>/HeatCmdDiagnose' */
  INT8U is_HeatCmdDiagnosis;           /* '<S14>/HeatCmdDiagnose' */
  INT8U ShortTimer;                    /* '<S14>/HeatCmdDiagnose' */
  INT8U OpenTimer;                     /* '<S14>/HeatCmdDiagnose' */
  INT8U RecoverTimer;                  /* '<S14>/HeatCmdDiagnose' */
}
DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T;

/* Block states (default storage) for system '<S7>/HeatNTCDiagnoseFunction' */
typedef struct
{
  INT16U ShortTimer;                   /* '<S17>/HeatCmdDiagnose' */
  INT16U WaitAquireTimer;              /* '<S17>/HeatCmdDiagnose' */
  INT16U OpenTimer;                    /* '<S17>/HeatCmdDiagnose' */
  INT16U OverTimer;                    /* '<S17>/HeatCmdDiagnose' */
  INT16U RecoveryTimer;                /* '<S17>/HeatCmdDiagnose' */
  INT8U is_active_c5_Appl_HeatFault_CtrlModel;/* '<S17>/HeatCmdDiagnose' */
  INT8U is_c5_Appl_HeatFault_CtrlModel;/* '<S17>/HeatCmdDiagnose' */
}
DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T;

/* Block signals (default storage) */
typedef struct
{
  enHeatNtcFault HeatFault_DRHeatNTCFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatNtcFault HeatFault_PAHeatNTCFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatNtcFault HeatFault_ThirdHeatNTCFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatNtcFault HeatNTCFault;         /* '<S19>/HeatCmdDiagnose' */
  enHeatNtcFault HeatNTCFault_b;       /* '<S18>/HeatCmdDiagnose' */
  enHeatNtcFault HeatNTCFault_h;       /* '<S17>/HeatCmdDiagnose' */
  enHeatCmdFault DrFaultType;          /* '<S28>/GetFaultType' */
  enHeatCmdFault PaFaultType;          /* '<S28>/GetFaultType' */
  enHeatCmdFault ThirdFaultType;       /* '<S28>/GetFaultType' */
  enHeatCmdFault HeatFault_DRHeatCmdFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatFault_PAHeatCmdFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatFault_ThirdHeatCmdFaultSts;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatFault_DRHeatCmdFaultSts4DTC;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatFault_PAHeatCmdFaultSts4DTC;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatFault_ThirdHeatCmdFaultSts4DTC;/* '<S5>/HeatDiagnoseDeal' */
  enHeatCmdFault HeatCmdFault;         /* '<S16>/HeatCmdDiagnose' */
  enHeatCmdFault HeatCmdFault4DTC;     /* '<S16>/HeatCmdDiagnose' */
  enHeatCmdFault HeatCmdFault_b;       /* '<S15>/HeatCmdDiagnose' */
  enHeatCmdFault HeatCmdFault4DTC_c;   /* '<S15>/HeatCmdDiagnose' */
  enHeatCmdFault HeatCmdFault_e;       /* '<S14>/HeatCmdDiagnose' */
  enHeatCmdFault HeatCmdFault4DTC_f;   /* '<S14>/HeatCmdDiagnose' */
  INT8U DrHeatCmd;                     /* '<S5>/HeatCommandDeal' */
  INT8U PaHeatCmd;                     /* '<S5>/HeatCommandDeal' */
  INT8U ThirdHeatCmd;                  /* '<S5>/HeatCommandDeal' */
}
B_Appl_HeatFault_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT8U is_active_c15_Appl_HeatFault_CtrlModel;/* '<S28>/GetFaultType' */
  INT8U is_active_c3_Appl_HeatFault_CtrlModel;/* '<S5>/HeatDiagnoseDeal' */
  INT8U is_active_c9_Appl_HeatFault_CtrlModel;/* '<S16>/HeatCmdDiagnose' */
  INT8U is_c9_Appl_HeatFault_CtrlModel;/* '<S16>/HeatCmdDiagnose' */
  INT8U is_HeatCmdDiagnosis;           /* '<S16>/HeatCmdDiagnose' */
  INT8U ShortTimer;                    /* '<S16>/HeatCmdDiagnose' */
  INT8U OpenTimer;                     /* '<S16>/HeatCmdDiagnose' */
  INT8U RecoverTimer;                  /* '<S16>/HeatCmdDiagnose' */
  INT8U is_active_c1_Appl_HeatFault_CtrlModel;/* '<S5>/HeatCommandDeal' */
  DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T HeatNTCDiagnoseFunction2;/* '<S7>/HeatNTCDiagnoseFunction2' */
  DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T HeatNTCDiagnoseFunction1;/* '<S7>/HeatNTCDiagnoseFunction1' */
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T HeatCmdDiagnoseFunction1;/* '<S7>/HeatCmdDiagnoseFunction1' */
  DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T HeatNTCDiagnoseFunction;/* '<S7>/HeatNTCDiagnoseFunction' */
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T HeatCmdDiagnoseFunction;/* '<S7>/HeatCmdDiagnoseFunction' */
  DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T HeatCmdAquireFunction2;/* '<S6>/HeatCmdAquireFunction2' */
  DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T HeatCmdAquireFunction1;/* '<S6>/HeatCmdAquireFunction1' */
  DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T HeatCmdAquireFunction;/* '<S6>/HeatCmdAquireFunction' */
}
DW_Appl_HeatFault_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_HeatFault_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_HeatFault_CtrlModel_T Appl_HeatFault_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_HeatFault_CtrlModel_T Appl_HeatFault_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enHeatLvlSts HeatFalut_D_SimuIndex_DRHeat;/* '<S27>/HeatFalut_D_SimuIndex_DRHeat'
                                                  * 主驾加热档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                  */
extern enHeatLvlSts HeatFalut_D_SimuIndex_PAHeat;/* '<S27>/HeatFalut_D_SimuIndex_PAHeat'
                                                  * 副驾加热档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                  */
extern enHeatLvlSts HeatFalut_D_SimuIndex_ThirdHeat;/* '<S27>/HeatFalut_D_SimuIndex_ThirdHeat'
                                                     * 三排加热档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                     */
extern enHeatIoSts HeatFalut_D_SimuIndex_DRHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_DRHeatIo'
                                                   * 主驾加热硬线状态&#10;0：低电平&#10;1：高电平
                                                   */
extern enHeatIoSts HeatFalut_D_SimuIndex_PAHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_PAHeatIo'
                                                   * 副驾加热硬线状态&#10;0：低电平&#10;1：高电平
                                                   */
extern enHeatIoSts HeatFalut_D_SimuIndex_ThirdHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_ThirdHeatIo'
                                                      * 三排加热硬线状态&#10;0：低电平&#10;1：高电平
                                                      */
extern enHeatIoSts HeatFalut_MemIndexDrHeatConfig;/* '<S27>/HeatFalut_MemIndexDrHeatConfig'
                                                   * 主驾加热配置&#10;0：无&#10;1：有
                                                   */
extern INT16U HeatFalut_DrHeatIsAdc;   /* '<S27>/HeatFalut_DrHeatIsAdc'
                                        * 主驾加热输出电流值AD
                                        */
extern INT16U HeatFalut_DrHeatNtcAdc;  /* '<S27>/HeatFalut_DrHeatNtcAdc'
                                        * 主驾NTC 温度值
                                        */
extern INT16U HeatFalut_PaHeatIsAdc;   /* '<S27>/HeatFalut_PaHeatIsAdc'
                                        * 副驾加热输出电流值AD
                                        */
extern INT16U HeatFalut_PaHeatNtcAdc;  /* '<S27>/HeatFalut_PaHeatNtcAdc'
                                        * 副驾NTC 温度值
                                        */
extern INT16U HeatFalut_ThirdHeatIsAdc;/* '<S27>/HeatFalut_ThirdHeatIsAdc'
                                        * 三排加热输出电流值AD
                                        */
extern INT16U HeatFalut_ThirdHeatNtcAdc;/* '<S27>/HeatFalut_ThirdHeatNtcAdc'
                                         * 三排NTC 温度值-预留
                                         */
extern INT8U HeatFalut_3rdCmdOpenload; /* '<S27>/HeatFalut_3rdCmdOpenload'
                                        * 三排加热CMD是否开路DTC&#10;0：否&#10;1：是
                                        */
extern INT8U HeatFalut_3rdCmdShortGND; /* '<S27>/HeatFalut_3rdCmdShortGND'
                                        * 三排加热CMD是否短路到地DTC&#10;0：否&#10;1：是
                                        */
extern INT8U HeatFalut_DrCmdOpenload;  /* '<S27>/HeatFalut_DrCmdOpenload'
                                        * 主驾加热CMD是否开路DTC&#10;0：否&#10;1：是
                                        */
extern INT8U HeatFalut_DrCmdShortGND;  /* '<S27>/HeatFalut_DrCmdShortGND'
                                        * 主驾加热CMD是否短路到地DTC&#10;0：否&#10;1：是
                                        */
extern INT8U HeatFalut_MemDiagDrHeatFlg;/* '<S27>/HeatFalut_MemDiagDrHeatFlg'
                                         * 主驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                         */
extern INT8U HeatFalut_MemDiagPaHeatFlg;/* '<S27>/HeatFalut_MemDiagPaHeatFlg'
                                         * 副驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                         */
extern INT8U HeatFalut_MemIndexPaHeatConfig;/* '<S27>/HeatFalut_MemIndexPaHeatConfig'
                                             * 副驾加热配置&#10;0：无&#10;1：有
                                             */
extern INT8U HeatFalut_MemIndexThirdHeatConfig;/* '<S27>/HeatFalut_MemIndexThirdHeatConfig'
                                                * 三排加热配置&#10;0：无&#10;1：有
                                                */
extern INT8U HeatFalut_PaCmdOpenload;  /* '<S27>/HeatFalut_PaCmdOpenload'
                                        * 副驾加热CMD是否开路DTC&#10;0：否&#10;1：是
                                        */
extern INT8U HeatFalut_PaCmdShortGND;  /* '<S27>/HeatFalut_PaCmdShortGND'
                                        * 副驾加热CMD是否短路到地DTC&#10;0：否&#10;1：是
                                        */

/* Model entry point functions */
extern void Appl_HeatFault_CtrlModel_initialize(void);
extern void Appl_HeatFault_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_HeatFault_CtrlModel_T *const Appl_HeatFault_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT8U CAL_CmdOpenTime;/* 加热输出判断时间：200ms */
extern const volatile INT8U CAL_CmdShortTime;/* 加热输出短地判断时间：200ms */
extern const volatile INT8U CAL_NTCOpenTime;/* NTC开路判断时间：1000ms */
extern const volatile INT16U CAL_NTCOverTime;/* NTC不可信判断时间：5000ms */
extern const volatile INT8U CAL_NTCShortTime;/* NTC短地判断时间：1000ms */
extern const volatile INT8U CAL_NTCWaitTime;/* NTC采集滤波时间：1000ms */

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
 * '<Root>' : 'Appl_HeatFault_CtrlModel'
 * '<S1>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_HeatFault_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_HeatFault_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_HeatFault_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl'
 * '<S6>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal'
 * '<S7>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal'
 * '<S8>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction'
 * '<S9>'   : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction1'
 * '<S10>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction2'
 * '<S11>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction/HeatCmdAquireFunction'
 * '<S12>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction1/HeatCmdAquireFunction'
 * '<S13>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatCommandDeal/HeatCmdAquireFunction2/HeatCmdAquireFunction'
 * '<S14>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction'
 * '<S15>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction1'
 * '<S16>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction2'
 * '<S17>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction'
 * '<S18>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction1'
 * '<S19>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction2'
 * '<S20>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction/HeatCmdDiagnose'
 * '<S21>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction1/HeatCmdDiagnose'
 * '<S22>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatCmdDiagnoseFunction2/HeatCmdDiagnose'
 * '<S23>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction/HeatCmdDiagnose'
 * '<S24>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction1/HeatCmdDiagnose'
 * '<S25>'  : 'Appl_HeatFault_CtrlModel/LogicCtrl/HeatDiagnoseCtrl/HeatDiagnoseDeal/HeatNTCDiagnoseFunction2/HeatCmdDiagnose'
 * '<S26>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S27>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/RTE'
 * '<S28>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/InputSignalProcess/CMD_Process'
 * '<S29>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/InputSignalProcess/CMD_Process/GetFaultType'
 * '<S30>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/InputSignalProcess/CMD_Process/GetFaultType/getFaultType'
 * '<S31>'  : 'Appl_HeatFault_CtrlModel/UpDataInputInfo/InputSignalProcess/CMD_Process/GetFaultType/getFaultType/Chart'
 */
#endif                                 /* RTW_HEADER_Appl_HeatFault_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
