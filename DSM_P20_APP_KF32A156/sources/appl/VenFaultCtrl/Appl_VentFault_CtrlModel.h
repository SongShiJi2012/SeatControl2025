/*
 * File: Appl_VentFault_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_VentFault_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jun  5 21:17:45 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_VentFault_CtrlModel_h_
#define RTW_HEADER_Appl_VentFault_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_VentFault_CtrlModel_COMMON_INCLUDES_
# define Appl_VentFault_CtrlModel_COMMON_INCLUDES_
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
#include <LdfFile_DSM_TwoInOne_V10.h>
#include <Ecual_lin.h>
#include "Appl_DtcSetConditionCheck.h"
#include "ecual_pins.h"
#endif                                 /* Appl_VentFault_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_VentFault_CtrlModel_T
  RT_MODEL_Appl_VentFault_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enVentLvlSts_
#define DEFINED_TYPEDEF_FOR_enVentLvlSts_

/* 通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3, */
typedef enum
{
  enVentLvlSts_EN_VENT_LVL_OFF = 0,    /* Default value */
  enVentLvlSts_EN_VENT_LVL_1,
  enVentLvlSts_EN_VENT_LVL_2,
  enVentLvlSts_EN_VENT_LVL_3
}
enVentLvlSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enVentCmdFault_
#define DEFINED_TYPEDEF_FOR_enVentCmdFault_

/* 通风故障&#10;0：无&#10;1：开路&#10;2：短电源, */
typedef enum
{
  enVentCmdFault_EN_VENT_FAULT_NONE = 0,/* Default value */
  enVentCmdFault_EN_VENT_FAULT_OPEN,
  enVentCmdFault_EN_VENT_FAULT_LOAD
}
enVentCmdFault;

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

/* Block states (default storage) for system '<S6>/VentCmdAquireFunction' */
typedef struct
{
  INT8U is_active_c2_Appl_VentFault_CtrlModel;/* '<S8>/VentCmdAquireFunction' */
  INT8U is_c2_Appl_VentFault_CtrlModel;/* '<S8>/VentCmdAquireFunction' */
}
DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T;

/* Block states (default storage) for system '<S7>/VentCmdDiagnoseFunction' */
typedef struct
{
  INT16U ShortTimer;                   /* '<S14>/VentCmdDiagnose' */
  INT16U OpenTimer;                    /* '<S14>/VentCmdDiagnose' */
  INT8U is_active_c4_Appl_VentFault_CtrlModel;/* '<S14>/VentCmdDiagnose' */
  INT8U is_c4_Appl_VentFault_CtrlModel;/* '<S14>/VentCmdDiagnose' */
  INT8U is_HeatCmdDiagnosis;           /* '<S14>/VentCmdDiagnose' */
}
DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T;

/* Block signals (default storage) */
typedef struct
{
  enVentCmdFault VentFault_DRVentCmdFaultSts;/* '<S5>/VentDiagnoseDeal' */
  enVentCmdFault VentFault_PAVentCmdFaultSts;/* '<S5>/VentDiagnoseDeal' */
  enVentCmdFault VentFault_ThirdVentCmdFaultSts;/* '<S5>/VentDiagnoseDeal' */
  enVentCmdFault VentCmdFault;         /* '<S16>/VentCmdDiagnose' */
  enVentCmdFault VentCmdFault_k;       /* '<S15>/VentCmdDiagnose' */
  enVentCmdFault VentCmdFault_h;       /* '<S14>/VentCmdDiagnose' */
  enHeatCmdFault DrFaultType;          /* '<S22>/GetFaultType' */
  enHeatCmdFault PaFaultType;          /* '<S22>/GetFaultType' */
  enHeatCmdFault ThirdFaultType;       /* '<S22>/GetFaultType' */
  INT8U VentFault_DRVentCmdFaultSts4DTC;/* '<S5>/VentDiagnoseDeal' */
  INT8U VentFault_PAVentCmdFaultSts4DTC;/* '<S5>/VentDiagnoseDeal' */
  INT8U VentCmdFault4DTC_g;            /* '<S15>/VentCmdDiagnose' */
  INT8U VentCmdFault4DTC_h;            /* '<S14>/VentCmdDiagnose' */
  INT8U DrVentCmd;                     /* '<S5>/VentCommandDeal' */
  INT8U PaVentCmd;                     /* '<S5>/VentCommandDeal' */
  INT8U ThirdVentCmd;                  /* '<S5>/VentCommandDeal' */
}
B_Appl_VentFault_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT8U is_active_c15_Appl_VentFault_CtrlModel;/* '<S22>/GetFaultType' */
  INT8U is_active_c3_Appl_VentFault_CtrlModel;/* '<S5>/VentDiagnoseDeal' */
  INT8U is_active_c1_Appl_VentFault_CtrlModel;/* '<S5>/VentCommandDeal' */
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T VentCmdDiagnoseFunction2;/* '<S7>/VentCmdDiagnoseFunction2' */
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T VentCmdDiagnoseFunction1;/* '<S7>/VentCmdDiagnoseFunction1' */
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T VentCmdDiagnoseFunction;/* '<S7>/VentCmdDiagnoseFunction' */
  DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T VentCmdAquireFunction2;/* '<S6>/VentCmdAquireFunction2' */
  DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T VentCmdAquireFunction1;/* '<S6>/VentCmdAquireFunction1' */
  DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T VentCmdAquireFunction;/* '<S6>/VentCmdAquireFunction' */
}
DW_Appl_VentFault_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_VentFault_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_VentFault_CtrlModel_T Appl_VentFault_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_VentFault_CtrlModel_T Appl_VentFault_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVentLvlSts VentFault_D_SimuIndex_DRVent;/* '<S21>/VentFault_D_SimuIndex_DRVent'
                                                  * 主驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                  */
extern enVentLvlSts VentFault_D_SimuIndex_PAVent;/* '<S21>/VentFault_D_SimuIndex_PAVent'
                                                  * 副驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                  */
extern enVentLvlSts VentFault_D_SimuIndex_ThirdVent;/* '<S21>/VentFault_D_SimuIndex_ThirdVent'
                                                     * 三排通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                     */
extern INT8U VentFault_DrPWMShortGND;  /* '<S21>/VentFault_DrPWMShortGND'
                                        * 主驾通风PWM短路至地&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_DrPWMShortPWR;  /* '<S21>/VentFault_DrPWMShortPWR'
                                        * 主驾通风PWM短路至电源&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_DrVentCmdIo;    /* '<S21>/VentFault_DrVentCmdIo'
                                        * 主驾通风输出电平
                                        */
extern INT8U VentFault_DrVentFlg;      /* '<S21>/VentFault_DrVentFlg'
                                        * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_DriverEnableConfig;/* '<S21>/VentFault_DriverEnableConfig'
                                           * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                           */
extern INT8U VentFault_PaPWMShortGND;  /* '<S21>/VentFault_PaPWMShortGND'
                                        * 主驾通风PWM短路至地&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_PaPWMShortPWR;  /* '<S21>/VentFault_PaPWMShortPWR'
                                        * 主驾通风PWM短路至电源&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_PaVentCmdIo;    /* '<S21>/VentFault_PaVentCmdIo'
                                        * 副驾通风输出电平
                                        */
extern INT8U VentFault_PaVentFlg;      /* '<S21>/VentFault_PaVentFlg'
                                        * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentFault_PassengerEnableConfig;/* '<S21>/VentFault_PassengerEnableConfig'
                                              * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                              */
extern INT8U VentFault_ThirdEnableConfig;/* '<S21>/VentFault_ThirdEnableConfig'
                                          * 三排通风使能配置&#10;0:不存在&#10;1：存在
                                          */
extern INT8U VentFault_ThirdVentCmdIo; /* '<S21>/VentFault_ThirdVentCmdIo'
                                        * 三排通风输出电平
                                        */

/* Model entry point functions */
extern void Appl_VentFault_CtrlModel_initialize(void);
extern void Appl_VentFault_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_VentFault_CtrlModel_T *const Appl_VentFault_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT16U CAL_VentCmdOpenTime;/* 通风输出判断时间：1000ms */
extern const volatile INT16U CAL_VentCmdShortTime;/* 通风输出短地判断时间：1000ms */

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
 * '<Root>' : 'Appl_VentFault_CtrlModel'
 * '<S1>'   : 'Appl_VentFault_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_VentFault_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_VentFault_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_VentFault_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl'
 * '<S6>'   : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal'
 * '<S7>'   : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal'
 * '<S8>'   : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction'
 * '<S9>'   : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction1'
 * '<S10>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction2'
 * '<S11>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction/VentCmdAquireFunction'
 * '<S12>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction1/VentCmdAquireFunction'
 * '<S13>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentCommandDeal/VentCmdAquireFunction2/VentCmdAquireFunction'
 * '<S14>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction'
 * '<S15>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction1'
 * '<S16>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction2'
 * '<S17>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction/VentCmdDiagnose'
 * '<S18>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction1/VentCmdDiagnose'
 * '<S19>'  : 'Appl_VentFault_CtrlModel/LogicCtrl/VentDiagnoseCtrl/VentDiagnoseDeal/VentCmdDiagnoseFunction2/VentCmdDiagnose'
 * '<S20>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S21>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/RTE'
 * '<S22>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/InputSignalProcess/PWM_Process'
 * '<S23>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/InputSignalProcess/PWM_Process/GetFaultType'
 * '<S24>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/InputSignalProcess/PWM_Process/GetFaultType/getFaultType'
 * '<S25>'  : 'Appl_VentFault_CtrlModel/UpDataInputInfo/InputSignalProcess/PWM_Process/GetFaultType/getFaultType/Chart'
 */
#endif                                 /* RTW_HEADER_Appl_VentFault_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
