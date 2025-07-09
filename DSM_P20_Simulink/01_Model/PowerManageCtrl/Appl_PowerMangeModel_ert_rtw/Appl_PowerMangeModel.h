/*
 * File: Appl_PowerMangeModel.h
 *
 * Code generated for Simulink model 'Appl_PowerMangeModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Apr 28 11:14:22 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PowerMangeModel_h_
#define RTW_HEADER_Appl_PowerMangeModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_PowerMangeModel_COMMON_INCLUDES_
# define Appl_PowerMangeModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_PowerMangeModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_PowerMangeModel_T RT_MODEL_Appl_PowerMangeModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enPowerModeSts_
#define DEFINED_TYPEDEF_FOR_enPowerModeSts_

/* 电源档位状态&#10;0 : OFF&#10;1 :ON&#10;2 : CRANK, */
typedef enum
{
  enPowerModeSts_EN_OFF = 0,           /* Default value */
  enPowerModeSts_EN_ACC,
  enPowerModeSts_EN_ON,
  enPowerModeSts_EN_CRANK
}
enPowerModeSts;

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

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_

/* 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节, */
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
  enSeatMotorRunTye_EN_ResEnable
}
enSeatMotorRunTye;

#endif

/* Block states (default storage) for system '<S15>/ModeChangeFunction' */
typedef struct
{
  INT8U is_active_c37_Appl_PowerMangeModel;/* '<S16>/Chart' */
  INT8U is_c37_Appl_PowerMangeModel;   /* '<S16>/Chart' */
}
DW_ModeChangeFunction_Appl_PowerMangeModel_T;

/* Block signals (default storage) */
typedef struct
{
  enFinalPowerMode OutVoltageMode;     /* '<S8>/KL30VoltageModeChange' */
  enFinalPowerMode FinalVoltageMode;   /* '<S8>/CrankUnload' */
  INT16U UpCount;                      /* '<S18>/Chart' */
  INT16U DownCount;                    /* '<S18>/Chart' */
  INT16U UpCount_c;                    /* '<S17>/Chart' */
  INT16U DownCount_n;                  /* '<S17>/Chart' */
  INT16U UpCount_o;                    /* '<S16>/Chart' */
  INT16U DownCount_b;                  /* '<S16>/Chart' */
  INT8U DataTypeConversion;            /* '<S4>/Data Type Conversion' */
  INT8U Switch1;                       /* '<S7>/Switch1' */
  INT8U VoltConditionSatisfy;          /* '<S6>/AdjustVoltage' */
}
B_Appl_PowerMangeModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enFinalPowerMode TempPowerMode;      /* '<S8>/CrankUnload' */
  INT8U Delay_DSTATE;                  /* '<S7>/Delay' */
  INT8U is_active_c34_Appl_PowerMangeModel;/* '<S8>/KL30VoltageModeChange' */
  INT8U is_c34_Appl_PowerMangeModel;   /* '<S8>/KL30VoltageModeChange' */
  INT8U is_BelowNormal;                /* '<S8>/KL30VoltageModeChange' */
  INT8U is_AboveNormal;                /* '<S8>/KL30VoltageModeChange' */
  INT8U DownTimer;                     /* '<S8>/KL30VoltageModeChange' */
  INT8U UpTimer;                       /* '<S8>/KL30VoltageModeChange' */
  INT8U is_active_c4_Appl_PowerMangeModel;/* '<S8>/CrankUnload' */
  INT8U is_c4_Appl_PowerMangeModel;    /* '<S8>/CrankUnload' */
  INT8U is_active_c3_Appl_PowerMangeModel;/* '<S6>/AdjustVoltage' */
  INT8U is_AcquireVoltage;             /* '<S6>/AdjustVoltage' */
  INT8U is_VoltageChecking;            /* '<S6>/AdjustVoltage' */
  INT8U InitFlag;                      /* '<S6>/AdjustVoltage' */
  INT8U AbnomalCnt;                    /* '<S6>/AdjustVoltage' */
  INT8U NomalCnt;                      /* '<S6>/AdjustVoltage' */
  INT8U StaticVoltageOKFlag;           /* '<S6>/AdjustVoltage' */
  DW_ModeChangeFunction_Appl_PowerMangeModel_T ModeChangeFunction2;/* '<S15>/ModeChangeFunction2' */
  DW_ModeChangeFunction_Appl_PowerMangeModel_T ModeChangeFunction1;/* '<S15>/ModeChangeFunction1' */
  DW_ModeChangeFunction_Appl_PowerMangeModel_T ModeChangeFunction;/* '<S15>/ModeChangeFunction' */
}
DW_Appl_PowerMangeModel_T;

/* Invariant block signals (default storage) */
typedef struct
{
  const INT8U DataTypeConversion2;     /* '<S7>/Data Type Conversion2' */
}
ConstB_Appl_PowerMangeModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_PowerMangeModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_PowerMangeModel_T Appl_PowerMangeModel_B;

/* Block states (default storage) */
extern DW_Appl_PowerMangeModel_T Appl_PowerMangeModel_DW;
extern const ConstB_Appl_PowerMangeModel_T Appl_PowerMangeModel_ConstB;/* constant block i/o */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMotorRunTye Appl_PwrMng_DriverRunType;/* '<S23>/Appl_PwrMng_DriverRunType'
                                                    * 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节
                                                    */
extern enSeatMotorRunTye Appl_PwrMng_PassengerRunType;/* '<S23>/Appl_PwrMng_PassengerRunType'
                                                       * 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节(副驾无)
                                                       */
extern INT16U Appl_PwrMng_SupplyVoltage;/* '<S23>/Appl_PwrMng_SupplyVoltage'
                                         * 电源电压值
                                         */
extern INT8U Appl_PwrMng_BCM_PowerMode;/* '<S23>/Appl_PwrMng_BCM_PowerMode'
                                        * 整车低压电源状态：&#10;0x0:Off &#10;0x1:Acc &#10;0x2:On &#10;0x3:Crank&#10;0x4~0x7:Reserved
                                        */

/* Model entry point functions */
extern void Appl_PowerMangeModel_initialize(void);
extern void Appl_PowerMangeModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_PowerMangeModel_T *const Appl_PowerMangeModel_M;

/* Exported data declaration */

/* Const memory section */
/* Declaration for custom storage class: Const */
extern const INT8U CAL_DownVolt_600ms; /* 低压切换时间：600ms */
extern const INT8U CAL_Filiter_500ms;  /* 调节电机电压滤波时间：500ms */
extern const INT8U CAL_UpVolt_200ms;   /* 高压切换时间：200ms */

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
 * '<Root>' : 'Appl_PowerMangeModel'
 * '<S1>'   : 'Appl_PowerMangeModel/LogicCtrl'
 * '<S2>'   : 'Appl_PowerMangeModel/Model Info'
 * '<S3>'   : 'Appl_PowerMangeModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_PowerMangeModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl'
 * '<S6>'   : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/AdjustVoltageCtrl'
 * '<S7>'   : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/PowerManageCtrl'
 * '<S8>'   : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl'
 * '<S9>'   : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/AdjustVoltageCtrl/AdjustVoltage'
 * '<S10>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/PowerManageCtrl/Enumerated Constant'
 * '<S11>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/PowerManageCtrl/Enumerated Constant1'
 * '<S12>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/PowerManageCtrl/Enumerated Constant4'
 * '<S13>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/PowerManageCtrl/Enumerated Constant5'
 * '<S14>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/CrankUnload'
 * '<S15>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange'
 * '<S16>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction'
 * '<S17>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction1'
 * '<S18>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction2'
 * '<S19>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction/Chart'
 * '<S20>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction1/Chart'
 * '<S21>'  : 'Appl_PowerMangeModel/LogicCtrl/PowerManageCtrl/VoltageManageCtrl/KL30VoltageModeChange/ModeChangeFunction2/Chart'
 * '<S22>'  : 'Appl_PowerMangeModel/UpDataInputInfo/InputSignalProcess'
 * '<S23>'  : 'Appl_PowerMangeModel/UpDataInputInfo/RTE'
 */
#endif                                 /* RTW_HEADER_Appl_PowerMangeModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
