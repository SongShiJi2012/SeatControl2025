/*
 * File: Appl_VentAdj_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_VentAdj_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 15:00:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_VentAdj_CtrlModel_h_
#define RTW_HEADER_Appl_VentAdj_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_VentAdj_CtrlModel_COMMON_INCLUDES_
# define Appl_VentAdj_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_VentAdj_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_VentAdj_CtrlModel_T
  RT_MODEL_Appl_VentAdj_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enVentStopReason_
#define DEFINED_TYPEDEF_FOR_enVentStopReason_

/* 通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能, */
typedef enum
{
  enVentStopReason_EN_VENT_STOP_R_NONE = 0,/* Default value */
  enVentStopReason_EN_VENT_STOP_R_VOL,
  enVentStopReason_EN_VENT_STOP_R_FAULT,
  enVentStopReason_EN_VENT_STOP_R_CMD,
  enVentStopReason_EN_VENT_STOP_R_FACTORY,
  enVentStopReason_EN_VENT_STOP_R_TIME,
  enVentStopReason_EN_VENT_STOP_R_LOSS
}
enVentStopReason;

#endif

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

#ifndef DEFINED_TYPEDEF_FOR_enVentType_
#define DEFINED_TYPEDEF_FOR_enVentType_

/* 通风类型&#10;0：无&#10;1：HMI&#10;2：Tbox&#10;3：诊断, */
typedef enum
{
  enVentType_EN_VENT_TYPE_NONE = 0,    /* Default value */
  enVentType_EN_VENT_TYPE_HMI,
  enVentType_EN_VENT_TYPE_TBOX,
  enVentType_EN_VENT_TYPE_DIAG
}
enVentType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enProjectType_
#define DEFINED_TYPEDEF_FOR_enProjectType_

/* 项目类型&#10;0：P20车型&#10;1：BM400车型, */
typedef enum
{
  enProjectType_EN_PROJECT_P20 = 0,    /* Default value */
  enProjectType_EN_PROJECT_BM400
}
enProjectType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enPowerModeSts_
#define DEFINED_TYPEDEF_FOR_enPowerModeSts_

/* 电源档位状态&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK, */
typedef enum
{
  enPowerModeSts_EN_OFF = 0,           /* Default value */
  enPowerModeSts_EN_ACC,
  enPowerModeSts_EN_ON,
  enPowerModeSts_EN_CRANK
}
enPowerModeSts;

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

#ifndef DEFINED_TYPEDEF_FOR_enVentIoCmdLvl_
#define DEFINED_TYPEDEF_FOR_enVentIoCmdLvl_

/* 通风IO控制档位状态:&#10;0：无控制&#10;1：OFF&#10;2：LV1&#10;3：LV2&#10;4：LV3, */
typedef enum
{
  enVentIoCmdLvl_EN_VENT_IO_LVL_NONE = 0,/* Default value */
  enVentIoCmdLvl_EN_VENT_IO_LVL_OFF,
  enVentIoCmdLvl_EN_VENT_IO_LVL_1,
  enVentIoCmdLvl_EN_VENT_IO_LVL_2,
  enVentIoCmdLvl_EN_VENT_IO_LVL_3
}
enVentIoCmdLvl;

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

/* Block states (default storage) for system '<S6>/LevelLimitFunction' */
typedef struct
{
  INT8U is_active_c21_Appl_VentAdj_CtrlModel;/* '<S12>/LevelLimit' */
  INT8U is_c21_Appl_VentAdj_CtrlModel; /* '<S12>/LevelLimit' */
}
DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<S6>/StopFunction' */
typedef struct
{
  INT8U is_active_c12_Appl_VentAdj_CtrlModel;/* '<S16>/StopFunction' */
  INT8U is_c12_Appl_VentAdj_CtrlModel; /* '<S16>/StopFunction' */
}
DW_StopFunction_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<S6>/DiagnoseFunction' */
typedef struct
{
  INT8U is_active_c13_Appl_VentAdj_CtrlModel;/* '<S9>/Diagnose' */
}
DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<S8>/LevelAquireFunction' */
typedef struct
{
  INT8U is_active_c27_Appl_VentAdj_CtrlModel;/* '<S45>/LevelAquireFunction' */
}
DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<S67>/OppositeMessageDeal' */
typedef struct
{
  INT8U is_active_c18_Appl_VentAdj_CtrlModel;/* '<S68>/OppositeMessageDeal' */
  INT8U is_HMIMessageDeal;             /* '<S68>/OppositeMessageDeal' */
  INT8U is_TboxMessageDeal;            /* '<S68>/OppositeMessageDeal' */
  INT8U is_VenStatus;                  /* '<S68>/OppositeMessageDeal' */
  INT8U TempHMI;                       /* '<S68>/OppositeMessageDeal' */
  INT8U TempTbox;                      /* '<S68>/OppositeMessageDeal' */
}
DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<S75>/MsgConflictFunction2' */
typedef struct
{
  INT8U is_active_c32_Appl_VentAdj_CtrlModel;/* '<S78>/Function' */
  INT8U is_HMI_MessageDeal;            /* '<S78>/Function' */
  INT8U is_Tbox_MessageDeal;           /* '<S78>/Function' */
  INT8U is_MessageConflictDeal;        /* '<S78>/Function' */
  INT8U HMI_Flag;                      /* '<S78>/Function' */
  INT8U Tbox_Flag;                     /* '<S78>/Function' */
}
DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T;

/* Block signals (default storage) */
typedef struct
{
  INT32U MaxTime;                      /* '<S5>/LimitDeal' */
  INT32U MaxTime_h;                    /* '<S5>/LimitDeal' */
  INT32U MaxTime_k;                    /* '<S5>/LimitDeal' */
  INT32U D_HAL_GET_CUR_MS_TS;          /* '<S40>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_b;        /* '<S36>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_b5;       /* '<S32>/DrAdj_LenAdjSize' */
  enVentType RunType;                  /* '<S51>/VentRunType' */
  enVentType VentDriverRunType;        /* '<S5>/LimitDeal' */
  enVentType VentPassengerRunType;     /* '<S5>/LimitDeal' */
  enVentType VentThirdRunType;         /* '<S5>/LimitDeal' */
  enVentStopReason DrVentStopReason;   /* '<S5>/LimitDeal' */
  enVentStopReason ThirdHeatStopReason;/* '<S5>/LimitDeal' */
  enVentStopReason PaVentStopReason;   /* '<S5>/LimitDeal' */
  enVentStopReason StopReason;         /* '<S18>/StopFunction' */
  enVentStopReason StopReason_n;       /* '<S17>/StopFunction' */
  enVentStopReason StopReason_l;       /* '<S16>/StopFunction' */
  enVentStopReason StopReason_nd;      /* '<S14>/LevelLimit' */
  enVentStopReason StopReason_lr;      /* '<S13>/LevelLimit' */
  enVentStopReason StopReason_g;       /* '<S12>/LevelLimit' */
  enVentLvlSts OriginalDrVentLevel;    /* '<S5>/VentLevelDeal' */
  enVentLvlSts OriginalPaVentLevel;    /* '<S5>/VentLevelDeal' */
  enVentLvlSts Original3rdVentLevel;   /* '<S5>/VentLevelDeal' */
  enVentLvlSts OutDrCANVentLevel;      /* '<S5>/OutputDeal' */
  enVentLvlSts OutPaCANVentLevel;      /* '<S5>/OutputDeal' */
  enVentLvlSts Out3rdCANVentLevel;     /* '<S5>/OutputDeal' */
  enVentLvlSts DiagDrVentLevel;        /* '<S5>/LimitDeal' */
  enVentLvlSts DiagPaVentLevel;        /* '<S5>/LimitDeal' */
  enVentLvlSts Diag3rdVentLevel;       /* '<S5>/LimitDeal' */
  enVentLvlSts InLevel;                /* '<S5>/LimitDeal' */
  enVentLvlSts InLevel_f;              /* '<S5>/LimitDeal' */
  enVentLvlSts InLevel_j;              /* '<S5>/LimitDeal' */
  enVentLvlSts Level_o;                /* '<S21>/Timeout' */
  enVentLvlSts Level_ip;               /* '<S20>/Timeout' */
  enVentLvlSts Level_p;                /* '<S19>/Timeout' */
  enVentLvlSts Level_b;                /* '<S14>/LevelLimit' */
  enVentLvlSts Level_c;                /* '<S13>/LevelLimit' */
  enVentLvlSts Level_h;                /* '<S12>/LevelLimit' */
  INT8U DriverHMI_VentMessage;         /* '<S65>/VentMessage' */
  INT8U DriverTbox_VentMessage;        /* '<S65>/VentMessage' */
  INT8U PassengerHMI_VentMessage;      /* '<S65>/VentMessage' */
  INT8U PassengerTbox_VentMessage;     /* '<S65>/VentMessage' */
  INT8U ThirdHMI_VentMessage;          /* '<S65>/VentMessage' */
  INT8U ThirdTbox_VentMessage;         /* '<S65>/VentMessage' */
  INT8U Driver_MixConflicFlg;          /* '<S65>/VentMessage' */
  INT8U Passenger_MixConflicFlg;       /* '<S65>/VentMessage' */
  INT8U Third_MixConflicFlg;           /* '<S65>/VentMessage' */
  INT8U OutMsgHMI;                     /* '<S76>/Function' */
  INT8U OutMsgTbox;                    /* '<S76>/Function' */
  INT8U MixConflictFlg;                /* '<S76>/Function' */
  INT8U OutMsgHMI_b;                   /* '<S77>/Function' */
  INT8U OutMsgTbox_i;                  /* '<S77>/Function' */
  INT8U MixConflictFlg_j;              /* '<S77>/Function' */
  INT8U OutMsgHMI_j;                   /* '<S78>/Function' */
  INT8U OutMsgTbox_e;                  /* '<S78>/Function' */
  INT8U MixConflictFlg_h;              /* '<S78>/Function' */
  INT8U DriverHeatValid;               /* '<S62>/HeatMessage' */
  INT8U PassengerHeatValid;            /* '<S62>/HeatMessage' */
  INT8U ThirdHeatValid;                /* '<S62>/HeatMessage' */
  INT8U ComPCSatisfiedFlag;            /* '<S61>/Deal' */
  INT8U Level_e;                       /* '<S50>/LevelAquireFunction' */
  INT8U Level_f;                       /* '<S47>/LevelAquireFunction' */
  INT8U Level_d;                       /* '<S49>/LevelAquireFunction' */
  INT8U Level_k;                       /* '<S46>/LevelAquireFunction' */
  INT8U Level_l;                       /* '<S48>/LevelAquireFunction' */
  INT8U Level_fi;                      /* '<S45>/LevelAquireFunction' */
  INT8U OutDrRunState;                 /* '<S5>/OutputDeal' */
  INT8U OutPaRunState;                 /* '<S5>/OutputDeal' */
  INT8U Out3rdRunState;                /* '<S5>/OutputDeal' */
  INT8U TimeoutPrm;                    /* '<S5>/LimitDeal' */
  INT8U TimeoutPrm_b;                  /* '<S5>/LimitDeal' */
  INT8U TimeoutPrm_o;                  /* '<S5>/LimitDeal' */
  INT8U TimeoutFlag;                   /* '<S21>/Timeout' */
  INT8U TimeoutFlag_h;                 /* '<S20>/Timeout' */
  INT8U TimeoutFlag_l;                 /* '<S19>/Timeout' */
  BOOL PaVentFlg;                      /* '<S64>/Logical Operator' */
  BOOL DrvVentFlg;                     /* '<S64>/Logical Operator1' */
}
B_Appl_VentAdj_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT32U Timer;                        /* '<S21>/Timeout' */
  INT32U Timer_n;                      /* '<S20>/Timeout' */
  INT32U Timer_a;                      /* '<S19>/Timeout' */
  enVentLvlSts InLevel_start;          /* '<S21>/Timeout' */
  enVentLvlSts InLevel_start_n;        /* '<S20>/Timeout' */
  enVentLvlSts InLevel_start_a;        /* '<S19>/Timeout' */
  INT8U is_active_c28_Appl_VentAdj_CtrlModel;/* '<S65>/VentMessage' */
  INT8U is_active_c6_Appl_VentAdj_CtrlModel;/* '<S62>/HeatMessage' */
  INT8U is_active_c39_Appl_VentAdj_CtrlModel;/* '<S61>/Deal' */
  INT8U is_c39_Appl_VentAdj_CtrlModel; /* '<S61>/Deal' */
  INT8U is_active_c3_Appl_VentAdj_CtrlModel;/* '<S5>/VentLevelDeal' */
  INT8U is_active_c14_Appl_VentAdj_CtrlModel;/* '<S5>/OutputDeal' */
  INT8U is_CANOutputDeal;              /* '<S5>/OutputDeal' */
  INT8U is_Drv;                        /* '<S5>/OutputDeal' */
  INT8U is_Pas;                        /* '<S5>/OutputDeal' */
  INT8U is_Treble;                     /* '<S5>/OutputDeal' */
  INT8U is_DrvErr;                     /* '<S5>/OutputDeal' */
  INT8U is_PasErr;                     /* '<S5>/OutputDeal' */
  INT8U is_TrebleErr;                  /* '<S5>/OutputDeal' */
  INT8U LocalDrRunState;               /* '<S5>/OutputDeal' */
  INT8U LocalPaRunState;               /* '<S5>/OutputDeal' */
  INT8U Local3rdRunState;              /* '<S5>/OutputDeal' */
  INT8U is_active_c2_Appl_VentAdj_CtrlModel;/* '<S5>/LimitDeal' */
  INT8U is_active_c19_Appl_VentAdj_CtrlModel;/* '<S21>/Timeout' */
  INT8U is_c19_Appl_VentAdj_CtrlModel; /* '<S21>/Timeout' */
  INT8U is_TimeCountStatus;            /* '<S21>/Timeout' */
  INT8U is_active_c5_Appl_VentAdj_CtrlModel;/* '<S20>/Timeout' */
  INT8U is_c5_Appl_VentAdj_CtrlModel;  /* '<S20>/Timeout' */
  INT8U is_TimeCountStatus_m;          /* '<S20>/Timeout' */
  INT8U is_active_c24_Appl_VentAdj_CtrlModel;/* '<S19>/Timeout' */
  INT8U is_c24_Appl_VentAdj_CtrlModel; /* '<S19>/Timeout' */
  INT8U is_TimeCountStatus_d;          /* '<S19>/Timeout' */
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T MsgConflictFunction;/* '<S75>/MsgConflictFunction' */
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T MsgConflictFunction1;/* '<S75>/MsgConflictFunction1' */
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T MsgConflictFunction2;/* '<S75>/MsgConflictFunction2' */
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T OppositeMessageDeal2;/* '<S67>/OppositeMessageDeal2' */
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T OppositeMessageDeal1;/* '<S67>/OppositeMessageDeal1' */
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T OppositeMessageDeal;/* '<S67>/OppositeMessageDeal' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction5;/* '<S8>/LevelAquireFunction5' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction2;/* '<S8>/LevelAquireFunction2' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction4;/* '<S8>/LevelAquireFunction4' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction1;/* '<S8>/LevelAquireFunction1' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction3;/* '<S8>/LevelAquireFunction3' */
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T LevelAquireFunction;/* '<S8>/LevelAquireFunction' */
  DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T DiagnoseFunction2;/* '<S6>/DiagnoseFunction2' */
  DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T DiagnoseFunction1;/* '<S6>/DiagnoseFunction1' */
  DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T DiagnoseFunction;/* '<S6>/DiagnoseFunction' */
  DW_StopFunction_Appl_VentAdj_CtrlModel_T StopFunction2;/* '<S6>/StopFunction2' */
  DW_StopFunction_Appl_VentAdj_CtrlModel_T StopFunction1;/* '<S6>/StopFunction1' */
  DW_StopFunction_Appl_VentAdj_CtrlModel_T StopFunction;/* '<S6>/StopFunction' */
  DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T LevelLimitFunction2;/* '<S6>/LevelLimitFunction2' */
  DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T LevelLimitFunction1;/* '<S6>/LevelLimitFunction1' */
  DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T LevelLimitFunction;/* '<S6>/LevelLimitFunction' */
}
DW_Appl_VentAdj_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_VentAdj_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_VentAdj_CtrlModel_T Appl_VentAdj_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_VentAdj_CtrlModel_T Appl_VentAdj_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVentStopReason VentAdj_DrVentStopReason;/* '<S60>/VentAdj_DrVentStopReason'
                                                  * 主驾通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                  */
extern enVentStopReason VentAdj_PaVentStopReason;/* '<S60>/VentAdj_PaVentStopReason'
                                                  * 副驾通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                  */
extern enVentStopReason VentAdj_ThirdVentStopReason;/* '<S60>/VentAdj_ThirdVentStopReason '
                                                     * 三排通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                     */
extern enVentLvlSts VentAdj_D_SimuIndex_DRVent;/* '<S60>/VentAdj_D_SimuIndex_DRVent'
                                                * 主驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                */
extern enVentLvlSts VentAdj_D_SimuIndex_PAVent;/* '<S60>/VentAdj_D_SimuIndex_PAVent'
                                                * 副驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                */
extern enVentLvlSts VentAdj_D_SimuIndex_ThirdVent;/* '<S60>/VentAdj_D_SimuIndex_ThirdVent'
                                                   * 三排通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                   */
extern enVentIoCmdLvl VentAdj_DriverDiagCmd;/* '<S60>/VentAdj_DriverDiagCmd'
                                             * 主驾通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                             */
extern enVentIoCmdLvl VentAdj_PassengerDiagCmd;/* '<S60>/VentAdj_PassengerDiagCmd'
                                                * 副驾通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                                */
extern enVentIoCmdLvl VentAdj_ThirdDiagCmd;/* '<S60>/VentAdj_ThirdDiagCmd'
                                            * 三排通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                            */
extern enVentCmdFault VentAdj_DriverCmdFaultSts;/* '<S60>/VentAdj_DriverCmdFaultSts'
                                                 * 主驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                 */
extern enVentCmdFault VentAdj_DriverCmdFaultSts4DTC;/* '<S60>/VentAdj_DriverCmdFaultSts4DTC'
                                                     * 主驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                     */
extern enVentCmdFault VentAdj_PasCmdFaultSts;/* '<S60>/VentAdj_PasCmdFaultSts'
                                              * 副驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                              */
extern enVentCmdFault VentAdj_PasCmdFaultSts4DTC;/* '<S60>/VentAdj_PasCmdFaultSts4DTC'
                                                  * 副驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                  */
extern enVentCmdFault VentAdj_ThirdCmdFaultSts;/* '<S60>/VentAdj_ThirdCmdFaultSts'
                                                * 三排通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                */
extern enVentCmdFault VentAdj_ThirdCmdFaultSts4DTC;/* '<S60>/VentAdj_ThirdCmdFaultSts4DTC'
                                                    * 三排通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                    */
extern enProjectType VentAdj_CarType;  /* '<S60>/VentAdj_CarType'
                                        * 车型：C62X、C52X…&#10;0：P20车型&#10;1：BM400车型
                                        */
extern enPowerModeSts VentAdj_PowerMode;/* '<S60>/VentAdj_PowerMode'
                                         * 整车电源档位&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK
                                         */
extern enFinalPowerMode VentAdj_VoltMode;/* '<S60>/VentAdj_VoltMode'
                                          * 整车电压模式&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                          */
extern INT8U VentAdj_3rdHeatFlg;       /* '<S60>/VentAdj_3rdHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_CanDrvVentLvl;    /* '<S60>/VentAdj_CanDrvVentLvl'
                                        * 输出通风等级
                                        */
extern INT8U VentAdj_CanPasVentLvl;    /* '<S60>/VentAdj_CanPasVentLvl'
                                        * 输出通风等级
                                        */
extern INT8U VentAdj_CanThirdVentLvl;  /* '<S60>/VentAdj_CanThirdVentLvl'
                                        * 输出通风等级
                                        */
extern INT8U VentAdj_DrHeatFlg;        /* '<S60>/VentAdj_DrHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_DrVentFlg;        /* '<S60>/VentAdj_DrVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_DriverEnableConfig;/* '<S60>/VentAdj_DriverEnableConfig'
                                         * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                         */
extern INT8U VentAdj_DriverHMI_VentMessage;/* '<S60>/VentAdj_DriverHMI_VentMessage'
                                            * 主驾通风HMI等级报文
                                            */
extern INT8U VentAdj_DriverTbox_VentMessage;/* '<S60>/VentAdj_DriverTbox_VentMessage'
                                             * 主驾通风Tbox等级报文
                                             */
extern INT8U VentAdj_Driver_HMI_HeatMsg;/* '<S60>/VentAdj_Driver_HMI_HeatMsg'
                                         * 主驾加热HMI报文
                                         */
extern INT8U VentAdj_Driver_Tbox_HeatMsg;/* '<S60>/VentAdj_Driver_Tbox_HeatMsg'
                                          * 主驾加热Tbox报文
                                          */
extern INT8U VentAdj_EngineRunFlag;    /* '<S60>/VentAdj_EngineRunFlag'
                                        * 发动机运行状态
                                        */
extern INT8U VentAdj_PaHeatFlg;        /* '<S60>/VentAdj_PaHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_PaVentFlg;        /* '<S60>/VentAdj_PaVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_PassengerEnableConfig;/* '<S60>/VentAdj_PassengerEnableConfig'
                                            * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                            */
extern INT8U VentAdj_PassengerHMI_VentMessage;/* '<S60>/VentAdj_PassengerHMI_VentMessage'
                                               * 副驾通风HMI等级报文
                                               */
extern INT8U VentAdj_PassengerTbox_VentMessage;/* '<S60>/VentAdj_PassengerTbox_VentMessage'
                                                * 副驾通风Tbox等级报文
                                                */
extern INT8U VentAdj_Passenger_HMI_HeatMsg;/* '<S60>/VentAdj_Passenger_HMI_HeatMsg'
                                            * 副驾加热HMI报文
                                            */
extern INT8U VentAdj_Passenger_Tbox_HeatMsg;/* '<S60>/VentAdj_Passenger_Tbox_HeatMsg'
                                             * 副驾加热Tbox报文
                                             */
extern INT8U VentAdj_RecoverDefaultFlag;/* '<S60>/VentAdj_RecoverDefaultFlag'
                                         * 恢复出厂命令&#10;0：无效；&#10;1：有效
                                         */
extern INT8U VentAdj_RemoteModeFlag;   /* '<S60>/VentAdj_RemoteModeFlag'
                                        * 通风远程模式状态&#10;0：无远程模式&#10;1：进远程模式
                                        */
extern INT8U VentAdj_RunMaxTime;       /* '<S60>/VentAdj_RunMaxTime'
                                        * 通风超时时间配置&#10;0：无超时&#10;1-255min
                                        */
extern INT8U VentAdj_ThirdEnableConfig;/* '<S60>/VentAdj_ThirdEnableConfig'
                                        * 三排通风使能配置&#10;0:不存在&#10;1：存在
                                        */
extern INT8U VentAdj_ThirdHMI_VentMessage;/* '<S60>/VentAdj_ThirdHMI_VentMessage'
                                           * 三排通风HMI等级报文
                                           */
extern INT8U VentAdj_ThirdTbox_VentMessage;/* '<S60>/VentAdj_ThirdTbox_VentMessage'
                                            * 三排通风Tbox等级报文
                                            */
extern INT8U VentAdj_Third_HMI_HeatMsg;/* '<S60>/VentAdj_Third_HMI_HeatMsg'
                                        * 三排加热HMI报文
                                        */
extern INT8U VentAdj_Third_Tbox_HeatMsg;/* '<S60>/VentAdj_Third_Tbox_HeatMsg'
                                         * 三排加热Tbox报文
                                         */
extern INT8U VentAdj_TimeOutPrm;       /* '<S60>/VentAdj_TimeOutPrm'
                                        * 通风超时使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U VentAdj_VehicleRunFlag;   /* '<S60>/VentAdj_VehicleRunFlag'
                                        * 整车运行状态&#10;0：无&#10;1：运行
                                        */
extern INT8U VentAdj_VentMsgLostFlag;  /* '<S60>/VentAdj_VentMsgLostFlag'
                                        * 通风报文掉线
                                        */

/* Model entry point functions */
extern void Appl_VentAdj_CtrlModel_initialize(void);
extern void Appl_VentAdj_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_VentAdj_CtrlModel_T *const Appl_VentAdj_CtrlModel_M;

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
 * '<Root>' : 'Appl_VentAdj_CtrlModel'
 * '<S1>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_VentAdj_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_VentAdj_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_VentAdj_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal'
 * '<S7>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal'
 * '<S8>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal'
 * '<S9>'   : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction'
 * '<S10>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction1'
 * '<S11>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction2'
 * '<S12>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction'
 * '<S13>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction1'
 * '<S14>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction2'
 * '<S15>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/MixConflic'
 * '<S16>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction'
 * '<S17>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction1'
 * '<S18>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction2'
 * '<S19>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction'
 * '<S20>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1'
 * '<S21>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2'
 * '<S22>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction/Diagnose'
 * '<S23>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction1/Diagnose'
 * '<S24>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction2/Diagnose'
 * '<S25>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction/LevelLimit'
 * '<S26>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction1/LevelLimit'
 * '<S27>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction2/LevelLimit'
 * '<S28>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction/StopFunction'
 * '<S29>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction1/StopFunction'
 * '<S30>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction2/StopFunction'
 * '<S31>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout'
 * '<S32>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/D_HAL_GET_CUR_MS_TS'
 * '<S33>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/TimeDiffTs'
 * '<S34>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/TimeDiffTs/Chart'
 * '<S35>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout'
 * '<S36>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/D_HAL_GET_CUR_MS_TS'
 * '<S37>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/TimeDiffTs'
 * '<S38>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/TimeDiffTs/Chart'
 * '<S39>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2/Timeout'
 * '<S40>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2/Timeout/D_HAL_GET_CUR_MS_TS'
 * '<S41>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2/Timeout/TimeDiffTs'
 * '<S42>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2/Timeout/TimeDiffTs/Chart'
 * '<S43>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/DutyFunction'
 * '<S44>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/DutyFunction/Duty'
 * '<S45>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction'
 * '<S46>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction1'
 * '<S47>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction2'
 * '<S48>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction3'
 * '<S49>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction4'
 * '<S50>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction5'
 * '<S51>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/VentRunTypeFunction'
 * '<S52>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction/LevelAquireFunction'
 * '<S53>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction1/LevelAquireFunction'
 * '<S54>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction2/LevelAquireFunction'
 * '<S55>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction3/LevelAquireFunction'
 * '<S56>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction4/LevelAquireFunction'
 * '<S57>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/LevelAquireFunction5/LevelAquireFunction'
 * '<S58>'  : 'Appl_VentAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/VentLevelDeal/VentRunTypeFunction/VentRunType'
 * '<S59>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S60>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/RTE'
 * '<S61>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/CommonPreconditionDeal'
 * '<S62>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage'
 * '<S63>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/MaxTime'
 * '<S64>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/Subsystem'
 * '<S65>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage'
 * '<S66>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/CommonPreconditionDeal/Deal'
 * '<S67>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage'
 * '<S68>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal'
 * '<S69>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal1'
 * '<S70>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal2'
 * '<S71>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal/OppositeMessageDeal'
 * '<S72>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal1/OppositeMessageDeal'
 * '<S73>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/OppositeMessageDeal2/OppositeMessageDeal'
 * '<S74>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/MaxTime/TimeChangeToCycle5'
 * '<S75>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage'
 * '<S76>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction'
 * '<S77>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction1'
 * '<S78>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction2'
 * '<S79>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction/Function'
 * '<S80>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction1/Function'
 * '<S81>'  : 'Appl_VentAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentMessage/VentMessage/MsgConflictFunction2/Function'
 */
#endif                                 /* RTW_HEADER_Appl_VentAdj_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
