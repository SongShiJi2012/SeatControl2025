/*
 * File: Appl_HeatAdj_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_HeatAdj_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:45:13 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_HeatAdj_CtrlModel_h_
#define RTW_HEADER_Appl_HeatAdj_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_HeatAdj_CtrlModel_COMMON_INCLUDES_
# define Appl_HeatAdj_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_HeatAdj_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_HeatAdj_CtrlModel_T
  RT_MODEL_Appl_HeatAdj_CtrlModel_T;

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

#ifndef DEFINED_TYPEDEF_FOR_enHeatType_
#define DEFINED_TYPEDEF_FOR_enHeatType_

/* 加热类型&#10;0：无&#10;1：HMI&#10;2：Tbox&#10;3：诊断, */
typedef enum
{
  enHeatType_EN_HEAT_TYPE_NONE = 0,    /* Default value */
  enHeatType_EN_HEAT_TYPE_HMI,
  enHeatType_EN_HEAT_TYPE_TBOX,
  enHeatType_EN_HEAT_TYPE_DIAG
}
enHeatType;

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

#ifndef DEFINED_TYPEDEF_FOR_enHeatStopReason_
#define DEFINED_TYPEDEF_FOR_enHeatStopReason_

/* 加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能, */
typedef enum
{
  enHeatStopReason_EN_HEAT_STOP_R_NONE = 0,/* Default value */
  enHeatStopReason_EN_HEAT_STOP_R_VOL,
  enHeatStopReason_EN_HEAT_STOP_R_FAULT,
  enHeatStopReason_EN_HEAT_STOP_R_CMD,
  enHeatStopReason_EN_HEAT_STOP_R_FACTORY,
  enHeatStopReason_EN_HEAT_STOP_R_TIME,
  enHeatStopReason_EN_HEAT_STOP_R_LOSS
}
enHeatStopReason;

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

#ifndef DEFINED_TYPEDEF_FOR_enHeatIoCmdLvl_
#define DEFINED_TYPEDEF_FOR_enHeatIoCmdLvl_

/* 加热IO控制档位状态:&#10;0：无控制&#10;1：OFF&#10;2：LV1&#10;3：LV2&#10;4：LV3, */
typedef enum
{
  enHeatIoCmdLvl_EN_HEAT_IO_LVL_NONE = 0,/* Default value */
  enHeatIoCmdLvl_EN_HEAT_IO_LVL_OFF,
  enHeatIoCmdLvl_EN_HEAT_IO_LVL_1,
  enHeatIoCmdLvl_EN_HEAT_IO_LVL_2,
  enHeatIoCmdLvl_EN_HEAT_IO_LVL_3
}
enHeatIoCmdLvl;

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

#ifndef DEFINED_TYPEDEF_FOR_enEngineType_
#define DEFINED_TYPEDEF_FOR_enEngineType_

/* 发动机状态:&#10;0：not running&#10;1：CRANK&#10;2：RUNNING&#10;3：FAULT, */
typedef enum
{
  enEngineType_EN_ENGINE_STOP = 0,     /* Default value */
  enEngineType_EN_ENGINE_RESERVED,
  enEngineType_EN_ENGINE_RUNNING,
  enEngineType_EN_ENGINE_CRANKING
}
enEngineType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enVehicleRunType_
#define DEFINED_TYPEDEF_FOR_enVehicleRunType_

/* 整车运行状态:&#10;0x0:HV OFF&#10;0x1:HV ON&#10;0x2:Ready&#10;0x3:Invalid, */
typedef enum
{
  enVehicleRunType_EN_HV_OFF = 0,      /* Default value */
  enVehicleRunType_EN_HV_ON,
  enVehicleRunType_EN_HV_READY,
  enVehicleRunType_EN_HV_INVALID
}
enVehicleRunType;

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

#ifndef DEFINED_TYPEDEF_FOR_enSteerHeatType_
#define DEFINED_TYPEDEF_FOR_enSteerHeatType_

/* 方向盘加热&#10;0x0:无动作&#10;0x1:开始&#10;0x2:关闭&#10;0x3:无效值, */
typedef enum
{
  enSteerHeatType_EN_STEER_NONE = 0,   /* Default value */
  enSteerHeatType_EN_STEER_OPEN,
  enSteerHeatType_EN_STEER_CLOSE,
  enSteerHeatType_EN_STEER_INVALID
}
enSteerHeatType;

#endif

/* Block states (default storage) for system '<S6>/CANAquireFunction' */
typedef struct
{
  INT8U is_active_c45_Appl_HeatAdj_CtrlModel;/* '<S9>/CANAquireFunction' */
  INT8U is_c45_Appl_HeatAdj_CtrlModel; /* '<S9>/CANAquireFunction' */
  INT8U TempMsg;                       /* '<S9>/CANAquireFunction' */
  INT8U ValidCnt;                      /* '<S9>/CANAquireFunction' */
  INT8U temporalCounter_i1;            /* '<S9>/CANAquireFunction' */
  INT8U IVISwsHeat_start;              /* '<S9>/CANAquireFunction' */
}
DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S6>/LevelAquireFunction' */
typedef struct
{
  INT8U is_active_c41_Appl_HeatAdj_CtrlModel;/* '<S10>/LevelAquireFunction' */
}
DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S6>/SwLevelAquireFunction1' */
typedef struct
{
  INT8U is_active_c49_Appl_HeatAdj_CtrlModel;/* '<S17>/SwLevelAquireFunction' */
}
DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S7>/LevelLimitFunction' */
typedef struct
{
  INT8U is_active_c4_Appl_HeatAdj_CtrlModel;/* '<S30>/LevelLimit' */
  INT8U is_c4_Appl_HeatAdj_CtrlModel;  /* '<S30>/LevelLimit' */
}
DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S7>/TimeoutFunction2' */
typedef struct
{
  INT8U is_active_c25_Appl_HeatAdj_CtrlModel;/* '<S39>/Timeout' */
  INT8U is_c25_Appl_HeatAdj_CtrlModel; /* '<S39>/Timeout' */
}
DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S7>/StopFunction' */
typedef struct
{
  INT8U is_active_c12_Appl_HeatAdj_CtrlModel;/* '<S34>/StopFunction' */
  INT8U is_c12_Appl_HeatAdj_CtrlModel; /* '<S34>/StopFunction' */
}
DW_StopFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S7>/DiagnoseFunction' */
typedef struct
{
  INT8U is_active_c13_Appl_HeatAdj_CtrlModel;/* '<S27>/Diagnose' */
}
DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S64>/PidGetPwm' */
typedef struct
{
  INT32U SumError;                     /* '<S65>/Pid ' */
  INT32U LastError;                    /* '<S65>/Pid ' */
}
DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T;

/* Block signals for system '<S8>/HeatOutFunction' */
typedef struct
{
  INT16U CurrentTemp;                  /* '<S58>/HeatOut' */
  INT16U SetTemp;                      /* '<S58>/HeatOut' */
  INT16U PwmCnt;                       /* '<S65>/Pid ' */
}
B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S8>/HeatOutFunction' */
typedef struct
{
  INT8U is_active_c16_Appl_HeatAdj_CtrlModel;/* '<S58>/HeatOut' */
  INT8U is_Controll;                   /* '<S58>/HeatOut' */
  INT8U TimeCnt;                       /* '<S58>/HeatOut' */
  DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T PidGetPwm;/* '<S64>/PidGetPwm' */
}
DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S102>/ErrorFunction2' */
typedef struct
{
  INT8U is_active_c21_Appl_HeatAdj_CtrlModel;/* '<S105>/OppositeMessageDeal' */
  INT8U is_c21_Appl_HeatAdj_CtrlModel; /* '<S105>/OppositeMessageDeal' */
}
DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S115>/MsgConflictFunction2' */
typedef struct
{
  INT8U is_active_c48_Appl_HeatAdj_CtrlModel;/* '<S118>/Function' */
  INT8U is_HMI_MessageDeal;            /* '<S118>/Function' */
  INT8U is_Tbox_MessageDeal;           /* '<S118>/Function' */
  INT8U is_MessageConflictDeal;        /* '<S118>/Function' */
  INT8U HMI_Flag;                      /* '<S118>/Function' */
  INT8U Tbox_Flag;                     /* '<S118>/Function' */
}
DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<S125>/OppositeMessageDeal' */
typedef struct
{
  INT8U is_active_c9_Appl_HeatAdj_CtrlModel;/* '<S126>/OppositeMessageDeal' */
  INT8U is_HMIMessageDeal;             /* '<S126>/OppositeMessageDeal' */
  INT8U is_TboxMessageDeal;            /* '<S126>/OppositeMessageDeal' */
  INT8U is_VenStatus;                  /* '<S126>/OppositeMessageDeal' */
  INT8U TempHMI;                       /* '<S126>/OppositeMessageDeal' */
  INT8U TempTbox;                      /* '<S126>/OppositeMessageDeal' */
}
DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T;

/* Block signals (default storage) */
typedef struct
{
  INT32U Product;                      /* '<S96>/Product' */
  INT32U Switch;                       /* '<S96>/Switch' */
  INT32U Sw20minTimerOut;              /* '<S5>/OutputDeal' */
  INT32U MaxTime;                      /* '<S5>/OutputDeal' */
  INT32U Sw20minTimer;                 /* '<S60>/HeatOut' */
  INT32U D_HAL_GET_CUR_MS_TS;          /* '<S71>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_l;        /* '<S85>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_j;        /* '<S81>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_h;        /* '<S77>/DrAdj_LenAdjSize' */
  INT32U MaxTime_h;                    /* '<S5>/LimitDeal' */
  INT32U MaxTime_k;                    /* '<S5>/LimitDeal' */
  INT32U D_HAL_GET_CUR_MS_TS_a;        /* '<S54>/DrAdj_LenAdjSize' */
  INT32U D_HAL_GET_CUR_MS_TS_c;        /* '<S50>/DrAdj_LenAdjSize' */
  enProjectType CarTypeCfg_e;          /* '<S5>/HeatLevelDeal' */
  enHeatType HeatDriverRunType;        /* '<S5>/LimitDeal' */
  enHeatType HeatPassengerRunType;     /* '<S5>/LimitDeal' */
  enHeatType HeatThirdRunType;         /* '<S5>/LimitDeal' */
  enHeatType OrgHeatDriverRunType;     /* '<S5>/HeatLevelDeal' */
  enHeatType OrgHeatPassengerRunType;  /* '<S5>/HeatLevelDeal' */
  enHeatType OrgHeatThirdRunType;      /* '<S5>/HeatLevelDeal' */
  enHeatStopReason DrHeatStopReason;   /* '<S5>/LimitDeal' */
  enHeatStopReason ThirdHeatStopReason;/* '<S5>/LimitDeal' */
  enHeatStopReason PaHeatStopReason;   /* '<S5>/LimitDeal' */
  enHeatStopReason DrCANHeatStopReason;/* '<S5>/LimitDeal' */
  enHeatStopReason PaCANHeatStopReason;/* '<S5>/LimitDeal' */
  enHeatStopReason ThirdCANHeatStopReason;/* '<S5>/LimitDeal' */
  enHeatStopReason StopReason_d;       /* '<S32>/LevelLimit' */
  enHeatStopReason StopReason_ew;      /* '<S31>/LevelLimit' */
  enHeatStopReason CANStopReason_ky;   /* '<S31>/LevelLimit' */
  enHeatStopReason StopReason_c;       /* '<S30>/LevelLimit' */
  enHeatStopReason CANStopReason_j;    /* '<S30>/LevelLimit' */
  enHeatStopReason DisableSts_b;       /* '<S5>/HeatLevelDeal' */
  enHeatLvlSts OutDrCANHeatLevel;      /* '<S5>/OutputDeal' */
  enHeatLvlSts OutPaCANHeatLevel;      /* '<S5>/OutputDeal' */
  enHeatLvlSts Out3rdCANHeatLevel;     /* '<S5>/OutputDeal' */
  enHeatLvlSts AimLevel;               /* '<S5>/OutputDeal' */
  enHeatLvlSts AimLevel_c;             /* '<S5>/OutputDeal' */
  enHeatLvlSts AimLevel_d;             /* '<S5>/OutputDeal' */
  enHeatLvlSts HeatLvl_i;              /* '<S5>/OutputDeal' */
  enHeatLvlSts DiagDrHeatLevel;        /* '<S5>/LimitDeal' */
  enHeatLvlSts DiagPaHeatLevel;        /* '<S5>/LimitDeal' */
  enHeatLvlSts Diag3rdHeatLevel;       /* '<S5>/LimitDeal' */
  enHeatLvlSts InLevel;                /* '<S5>/LimitDeal' */
  enHeatLvlSts InLevel_p;              /* '<S5>/LimitDeal' */
  enHeatLvlSts Level_i;                /* '<S38>/Timeout' */
  enHeatLvlSts Level_b;                /* '<S37>/Timeout' */
  enHeatLvlSts Level_p;                /* '<S32>/LevelLimit' */
  enHeatLvlSts Level_g;                /* '<S31>/LevelLimit' */
  enHeatLvlSts Level_be;               /* '<S30>/LevelLimit' */
  enHeatLvlSts OriginalDrHeatLevel;    /* '<S5>/HeatLevelDeal' */
  enHeatLvlSts OriginalPaHeatLevel;    /* '<S5>/HeatLevelDeal' */
  enHeatLvlSts Original3rdHeatLevel;   /* '<S5>/HeatLevelDeal' */
  enHeatIoSts HeatAdj_DRHeatIo;        /* '<S5>/OutputDeal' */
  enHeatIoSts HeatAdj_PAHeatIo;        /* '<S5>/OutputDeal' */
  enHeatIoSts HeatAdj_ThirdHeatIo;     /* '<S5>/OutputDeal' */
  INT16U SetTemp_a;                    /* '<S5>/OutputDeal' */
  INT16U CurrentTemp_m;                /* '<S5>/OutputDeal' */
  INT16U AimTemp;                      /* '<S63>/TempFunction' */
  INT16U AimTemp_h;                    /* '<S62>/TempFunction' */
  INT16U AimTemp_a;                    /* '<S61>/TempFunction' */
  INT8U DrVentConfig;                  /* '<S94>/Switch1' */
  INT8U PaVentConfig;                  /* '<S94>/Switch1' */
  INT8U ThirdVentConfig;               /* '<S94>/Switch1' */
  INT8U DrHeatConfig;                  /* '<S94>/Switch' */
  INT8U PaHeatConfig;                  /* '<S94>/Switch' */
  INT8U ThirdHeatConfig;               /* '<S94>/Switch' */
  INT8U DriverVentilateValid;          /* '<S99>/VentilateMessage' */
  INT8U PassengerVentilateValid;       /* '<S99>/VentilateMessage' */
  INT8U ThirdVentilateValid;           /* '<S99>/VentilateMessage' */
  INT8U VehicleRunFlag;                /* '<S98>/VehicleRunStatus' */
  INT8U RemoteModeFlag_ot;             /* '<S97>/RemoteMode' */
  INT8U DriverHMI_Message;             /* '<S95>/HeatMessage' */
  INT8U DriverTbox_Message;            /* '<S95>/HeatMessage' */
  INT8U PassengerHMI_Message;          /* '<S95>/HeatMessage' */
  INT8U PassengerTbox_Message;         /* '<S95>/HeatMessage' */
  INT8U ThirdHMI_Message;              /* '<S95>/HeatMessage' */
  INT8U ThirdTbox_Message;             /* '<S95>/HeatMessage' */
  INT8U Driver_MixConflicFlg;          /* '<S95>/HeatMessage' */
  INT8U Passenger_MixConflicFlg;       /* '<S95>/HeatMessage' */
  INT8U Third_MixConflicFlg;           /* '<S95>/HeatMessage' */
  INT8U OutMsgHMI;                     /* '<S116>/Function' */
  INT8U OutMsgTbox;                    /* '<S116>/Function' */
  INT8U MixConflictFlg;                /* '<S116>/Function' */
  INT8U OutMsgHMI_n;                   /* '<S117>/Function' */
  INT8U OutMsgTbox_b;                  /* '<S117>/Function' */
  INT8U MixConflictFlg_p;              /* '<S117>/Function' */
  INT8U OutMsgHMI_g;                   /* '<S118>/Function' */
  INT8U OutMsgTbox_bz;                 /* '<S118>/Function' */
  INT8U MixConflictFlg_a;              /* '<S118>/Function' */
  INT8U DriverHeatError;               /* '<S93>/EorrorProcess' */
  INT8U PassengerHeatError;            /* '<S93>/EorrorProcess' */
  INT8U ThirdHeatError;                /* '<S93>/EorrorProcess' */
  INT8U DriverHeatErrorDtc;            /* '<S93>/EorrorProcess' */
  INT8U PassengerHeatErrorDtc;         /* '<S93>/EorrorProcess' */
  INT8U ThirdHeatErrorDtc;             /* '<S93>/EorrorProcess' */
  INT8U EngineRunningFlag;             /* '<S92>/EngineStatus' */
  INT8U ComPCSatisfiedFlag;            /* '<S90>/Deal' */
  INT8U EngineRunningFlag_n;           /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U RemoteModeFlag_c;              /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U VehicleRunFlag_m;              /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U DrHeatConfig_d;                /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U PaHeatConfig_k;                /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U ThirdHeatConfig_l;             /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U DrVentConfig_l;                /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U PaVentConfig_d;                /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U ThirdVentConfig_c;             /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U ComPCSatisfiedFlag_n;          /* '<S1>/BusConversion_InsertedFor_HeatOut_at_inport_0' */
  INT8U OutDrRunState;                 /* '<S5>/OutputDeal' */
  INT8U OutPaRunState;                 /* '<S5>/OutputDeal' */
  INT8U Out3rdRunState;                /* '<S5>/OutputDeal' */
  INT8U ProjectType;                   /* '<S5>/OutputDeal' */
  INT8U ThirdHeat;                     /* '<S5>/OutputDeal' */
  INT8U ProjectType_p;                 /* '<S5>/OutputDeal' */
  INT8U ThirdHeat_i;                   /* '<S5>/OutputDeal' */
  INT8U ProjectType_d;                 /* '<S5>/OutputDeal' */
  INT8U ThirdHeat_o;                   /* '<S5>/OutputDeal' */
  INT8U HeatOutGpio;                   /* '<S60>/HeatOut' */
  INT8U HeatOutPwmCnt;                 /* '<S60>/HeatOut' */
  INT8U SwTimeoutFlag;                 /* '<S60>/HeatOut' */
  INT8U HeatOutGpio_l;                 /* '<S59>/HeatOut' */
  INT8U HeatOutPwmCnt_i;               /* '<S59>/HeatOut' */
  INT8U HeatOutGpio_e;                 /* '<S58>/HeatOut' */
  INT8U HeatOutPwmCnt_ik;              /* '<S58>/HeatOut' */
  INT8U TimeoutPrm;                    /* '<S5>/LimitDeal' */
  INT8U TimeoutPrm_k;                  /* '<S5>/LimitDeal' */
  INT8U TimeoutFlag_j;                 /* '<S38>/Timeout' */
  INT8U TimeoutFlag_b;                 /* '<S37>/Timeout' */
  INT8U Type_o;                        /* '<S5>/HeatLevelDeal' */
  INT8U EnableCfg_lg;                  /* '<S5>/HeatLevelDeal' */
  INT8U CAN_Message_ns;                /* '<S5>/HeatLevelDeal' */
  INT8U ComPCFlag_f;                   /* '<S5>/HeatLevelDeal' */
  INT8U CanLvl_f;                      /* '<S5>/HeatLevelDeal' */
  INT8U Type_m;                        /* '<S5>/HeatLevelDeal' */
  INT8U Level_kl;                      /* '<S15>/LevelAquireFunction' */
  INT8U Level_ax;                      /* '<S12>/LevelAquireFunction' */
  INT8U Level_j;                       /* '<S14>/LevelAquireFunction' */
  INT8U Level_h;                       /* '<S11>/LevelAquireFunction' */
  INT8U Level_c0;                      /* '<S13>/LevelAquireFunction' */
  INT8U Level_he;                      /* '<S10>/LevelAquireFunction' */
  INT8U IVISwCan;                      /* '<S9>/CANAquireFunction' */
  B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T HeatOutFunction1;/* '<S8>/HeatOutFunction1' */
  B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T HeatOutFunction;/* '<S8>/HeatOutFunction' */
}
B_Appl_HeatAdj_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT32U TimeCnt;                      /* '<S63>/TempFunction' */
  INT32U TimeCnt_o;                    /* '<S62>/TempFunction' */
  INT32U TimeCnt_g;                    /* '<S61>/TempFunction' */
  INT32U Timer;                        /* '<S38>/Timeout' */
  INT32U Timer_o;                      /* '<S37>/Timeout' */
  enHeatLvlSts InLevel_start;          /* '<S38>/Timeout' */
  enHeatLvlSts InLevel_start_d;        /* '<S37>/Timeout' */
  INT8U Delay_DSTATE_c;                /* '<S5>/Delay' */
  INT8U is_active_c8_Appl_HeatAdj_CtrlModel;/* '<S99>/VentilateMessage' */
  INT8U is_active_c44_Appl_HeatAdj_CtrlModel;/* '<S98>/VehicleRunStatus' */
  INT8U is_c44_Appl_HeatAdj_CtrlModel; /* '<S98>/VehicleRunStatus' */
  INT8U is_active_c6_Appl_HeatAdj_CtrlModel;/* '<S97>/RemoteMode' */
  INT8U is_c6_Appl_HeatAdj_CtrlModel;  /* '<S97>/RemoteMode' */
  INT8U is_active_c37_Appl_HeatAdj_CtrlModel;/* '<S95>/HeatMessage' */
  INT8U is_active_c10_Appl_HeatAdj_CtrlModel;/* '<S93>/EorrorProcess' */
  INT8U is_active_c7_Appl_HeatAdj_CtrlModel;/* '<S92>/EngineStatus' */
  INT8U is_c7_Appl_HeatAdj_CtrlModel;  /* '<S92>/EngineStatus' */
  INT8U is_active_c39_Appl_HeatAdj_CtrlModel;/* '<S90>/Deal' */
  INT8U is_c39_Appl_HeatAdj_CtrlModel; /* '<S90>/Deal' */
  INT8U is_active_c14_Appl_HeatAdj_CtrlModel;/* '<S5>/OutputDeal' */
  INT8U is_CANOutputDeal;              /* '<S5>/OutputDeal' */
  INT8U is_Drv;                        /* '<S5>/OutputDeal' */
  INT8U is_Pas;                        /* '<S5>/OutputDeal' */
  INT8U is_Treble;                     /* '<S5>/OutputDeal' */
  INT8U is_DrErr;                      /* '<S5>/OutputDeal' */
  INT8U is_PaErr;                      /* '<S5>/OutputDeal' */
  INT8U is_ThirdErr;                   /* '<S5>/OutputDeal' */
  INT8U LocalDrRunState;               /* '<S5>/OutputDeal' */
  INT8U LocalPaRunState;               /* '<S5>/OutputDeal' */
  INT8U Local3rdRunState;              /* '<S5>/OutputDeal' */
  INT8U is_active_c32_Appl_HeatAdj_CtrlModel;/* '<S60>/HeatOut' */
  INT8U is_Controll;                   /* '<S60>/HeatOut' */
  INT8U TimeCnt_c;                     /* '<S60>/HeatOut' */
  INT8U is_active_c57_Appl_HeatAdj_CtrlModel;/* '<S63>/TempFunction' */
  INT8U is_active_c54_Appl_HeatAdj_CtrlModel;/* '<S62>/TempFunction' */
  INT8U is_active_c15_Appl_HeatAdj_CtrlModel;/* '<S61>/TempFunction' */
  INT8U is_active_c2_Appl_HeatAdj_CtrlModel;/* '<S5>/LimitDeal' */
  INT8U is_active_c5_Appl_HeatAdj_CtrlModel;/* '<S38>/Timeout' */
  INT8U is_c5_Appl_HeatAdj_CtrlModel;  /* '<S38>/Timeout' */
  INT8U is_TimeCountStatus;            /* '<S38>/Timeout' */
  INT8U is_active_c34_Appl_HeatAdj_CtrlModel;/* '<S37>/Timeout' */
  INT8U is_c34_Appl_HeatAdj_CtrlModel; /* '<S37>/Timeout' */
  INT8U is_TimeCountStatus_c;          /* '<S37>/Timeout' */
  INT8U is_active_c3_Appl_HeatAdj_CtrlModel;/* '<S5>/HeatLevelDeal' */
  INT8U is_ThirdHeatLevelDeal;         /* '<S5>/HeatLevelDeal' */
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T OppositeMessageDeal2;/* '<S125>/OppositeMessageDeal2' */
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T OppositeMessageDeal1;/* '<S125>/OppositeMessageDeal1' */
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T OppositeMessageDeal;/* '<S125>/OppositeMessageDeal' */
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T MsgConflictFunction;/* '<S115>/MsgConflictFunction' */
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T MsgConflictFunction1;/* '<S115>/MsgConflictFunction1' */
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T MsgConflictFunction2;/* '<S115>/MsgConflictFunction2' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction5;/* '<S102>/ErrorFunction5' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction;/* '<S102>/ErrorFunction' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction4;/* '<S102>/ErrorFunction4' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction1;/* '<S102>/ErrorFunction1' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction3;/* '<S102>/ErrorFunction3' */
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T ErrorFunction2;/* '<S102>/ErrorFunction2' */
  DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T PidGetPwm;/* '<S70>/PidGetPwm' */
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T HeatOutFunction1;/* '<S8>/HeatOutFunction1' */
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T HeatOutFunction;/* '<S8>/HeatOutFunction' */
  DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T DiagnoseFunction2;/* '<S7>/DiagnoseFunction2' */
  DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T DiagnoseFunction1;/* '<S7>/DiagnoseFunction1' */
  DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T DiagnoseFunction;/* '<S7>/DiagnoseFunction' */
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T StopFunction2;/* '<S7>/StopFunction2' */
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T StopFunction1;/* '<S7>/StopFunction1' */
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T StopFunction;/* '<S7>/StopFunction' */
  DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T TimeoutFunction2;/* '<S7>/TimeoutFunction2' */
  DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T LevelLimitFunction2;/* '<S7>/LevelLimitFunction2' */
  DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T LevelLimitFunction1;/* '<S7>/LevelLimitFunction1' */
  DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T LevelLimitFunction;/* '<S7>/LevelLimitFunction' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction5;/* '<S6>/LevelAquireFunction5' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction2;/* '<S6>/LevelAquireFunction2' */
  DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T SwLevelAquireFunction;/* '<S6>/SwLevelAquireFunction' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction4;/* '<S6>/LevelAquireFunction4' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction1;/* '<S6>/LevelAquireFunction1' */
  DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T SwLevelAquireFunction1;/* '<S6>/SwLevelAquireFunction1' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction3;/* '<S6>/LevelAquireFunction3' */
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T LevelAquireFunction;/* '<S6>/LevelAquireFunction' */
  DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T CANAquireFunction;/* '<S6>/CANAquireFunction' */
}
DW_Appl_HeatAdj_CtrlModel_T;

/* Constant parameters (default storage) */
typedef struct
{
  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S96>/Constant5'
   */
  INT32U Constant5_Value[2];
}
ConstP_Appl_HeatAdj_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_HeatAdj_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_DW;

/* Constant parameters (default storage) */
extern const ConstP_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enVehicleRunType HeatAdj_VCU_VehRunSta;/* '<S89>/HeatAdj_VCU_VehRunSta'
                                               * Vehicle Running Status&#10;整车运行状态&#10;0x0：HV OFF&#10;0x1：HV ON&#10;0x2：Ready&#10;0x3：Invalid
                                               */
extern enProjectType HeatAdj_CarType;  /* '<S89>/HeatAdj_CarType'
                                        * 车型：C62X、C52X…&#10;0：P20车型&#10;1：BM400车型
                                        */
extern enPowerModeSts HeatAdj_PowerMode;/* '<S89>/HeatAdj_PowerMode'
                                         * 整车电源档位&#10;0 ： OFF&#10;1 ： ACC&#10;2 ： ON&#10;3 ： CRANK
                                         */
extern enHeatStopReason HeatAdj_DrHeatStopReason;/* '<S89>/HeatAdj_DrHeatStopReason'
                                                  * 主驾加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                  */
extern enHeatStopReason HeatAdj_PaHeatStopReason;/* '<S89>/HeatAdj_PaHeatStopReason'
                                                  * 副驾加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                  */
extern enHeatStopReason HeatAdj_ThirdHeatStopReason;/* '<S89>/HeatAdj_ThirdHeatStopReason '
                                                     * 三排加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                                     */
extern enHeatNtcFault HeatAdj_DriverNTCFaultSts;/* '<S89>/HeatAdj_DriverNTCFaultSts'
                                                 * 主驾加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                                 */
extern enHeatNtcFault HeatAdj_PassengerNTCFaultSts;/* '<S89>/HeatAdj_PassengerNTCFaultSts '
                                                    * 副驾加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                                    */
extern enHeatNtcFault HeatAdj_ThirdNTCFaultSts;/* '<S89>/HeatAdj_ThirdNTCFaultSts'
                                                * 三排加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                                */
extern enHeatLvlSts HeatAdj_D_SimuIndex_DRHeat;/* '<S89>/HeatAdj_D_SimuIndex_DRHeat'
                                                * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                */
extern enHeatLvlSts HeatAdj_D_SimuIndex_PAHeat;/* '<S89>/HeatAdj_D_SimuIndex_PAHeat'
                                                * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                */
extern enHeatLvlSts HeatAdj_D_SimuIndex_ThirdHeat;/* '<S89>/HeatAdj_D_SimuIndex_ThirdHeat'
                                                   * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                                   */
extern enHeatIoCmdLvl HeatAdj_DriverDiagCmd;/* '<S89>/HeatAdj_DriverDiagCmd'
                                             * 主驾加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                             */
extern enHeatIoCmdLvl HeatAdj_PassengerDiagCmd;/* '<S89>/HeatAdj_PassengerDiagCmd'
                                                * 副驾加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                                */
extern enHeatIoCmdLvl HeatAdj_ThirdDiagCmd;/* '<S89>/HeatAdj_ThirdDiagCmd'
                                            * 三排加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                            */
extern enHeatCmdFault HeatAdj_DriverCmdFaultSts;/* '<S89>/HeatAdj_DriverCmdFaultSts'
                                                 * 主驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                 */
extern enHeatCmdFault HeatAdj_DriverCmdFaultSts4DTC;/* '<S89>/HeatAdj_DriverCmdFaultSts4DTC'
                                                     * 主驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                     */
extern enHeatCmdFault HeatAdj_PassengerCmdFaultSts;/* '<S89>/HeatAdj_PassengerCmdFaultSts'
                                                    * 副驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                    */
extern enHeatCmdFault HeatAdj_PassengerCmdFaultSts4DTC;/* '<S89>/HeatAdj_PassengerCmdFaultSts4DTC'
                                                        * 副驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                        */
extern enHeatCmdFault HeatAdj_ThirdCmdFaultSts;/* '<S89>/HeatAdj_ThirdCmdFaultSts'
                                                * 三排加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                */
extern enHeatCmdFault HeatAdj_ThirdCmdFaultSts4DTC;/* '<S89>/HeatAdj_ThirdCmdFaultSts4DTC'
                                                    * 三排加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                    */
extern enFinalPowerMode HeatAdj_VoltMode;/* '<S89>/HeatAdj_VoltMode'
                                          * 整车电压模式&#10;0 ： StopVolt&#10;1 ： LowVolt&#10;2 ： NormalVolt&#10;3 ： HighVolt&#10;4 ： OverVolt
                                          */
extern enEngineType HeatAdj_ECMD_EngineStatus;/* '<S89>/HeatAdj_ECMD_EngineStatus'
                                               * 发动机运行状态
                                               */
extern INT16U HeatAdj_DrHeatNtcAdc;    /* '<S89>/HeatAdj_DrHeatNtcAdc'
                                        * NTC 温度值
                                        */
extern INT16U HeatAdj_PaHeatNtcAdc;    /* '<S89>/HeatAdj_PaHeatNtcAdc'
                                        * NTC 温度值
                                        */
extern INT16U HeatAdj_ThirdHeatNtcAdc; /* '<S89>/HeatAdj_ThirdHeatNtcAdc'
                                        * NTC 温度值
                                        */
extern INT8U HeatAdj_CanDrvHeatLvl;    /* '<S89>/HeatAdj_CanDrvHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
extern INT8U HeatAdj_CanPasHeatLvl;    /* '<S89>/HeatAdj_CanPasHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
extern INT8U HeatAdj_CanThirdHeatLvl;  /* '<S89>/HeatAdj_CanThirdHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
extern INT8U HeatAdj_DCDCSwitchSts;    /* '<S89>/HeatAdj_DCDCSwitchSts'
                                        * 获取DCDC节点开关使能状态 DSM_BM400专用接口，通风加热前置条件为Enable&#10;0x0：Disable&#10;0x1：Enable
                                        */
extern INT8U HeatAdj_DrVentFlg;        /* '<S89>/HeatAdj_DrVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U HeatAdj_DriverHMI_Message;/* '<S89>/HeatAdj_DriverHMI_Message'
                                        * 主驾加热HMI等级报文
                                        */
extern INT8U HeatAdj_DriverTbox_Message;/* '<S89>/HeatAdj_DriverTbox_Message'
                                         * 主驾加热Tbox等级报文
                                         */
extern INT8U HeatAdj_DriverVentEnableConfig;/* '<S89>/HeatAdj_DriverVentEnableConfig'
                                             * 主驾通风使能配置&#10;0：不存在&#10;1：存在
                                             */
extern INT8U HeatAdj_Driver_HMI_VentilateMsg;/* '<S89>/HeatAdj_Driver_HMI_VentilateMsg'
                                              * 主驾通风HMI报文
                                              */
extern INT8U HeatAdj_Driver_Tbox_VentilateMsg;/* '<S89>/HeatAdj_Driver_Tbox_VentilateMsg'
                                               * 主驾通风Tbox报文
                                               */
extern INT8U HeatAdj_HeatMsgLostFlag;  /* '<S89>/HeatAdj_HeatMsgLostFlag'
                                        * 加热报文掉线
                                        */
extern INT8U HeatAdj_MemDiagDrHeatConfig;/* '<S89>/HeatAdj_MemDiagDrHeatConfig'
                                          * 主驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                          */
extern INT8U HeatAdj_MemDiagDrHeatFlg; /* '<S89>/HeatAdj_MemDiagDrHeatFlg'
                                        * 主驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
extern INT8U HeatAdj_MemDiagPaHeatConfig;/* '<S89>/HeatAdj_MemDiagPaHeatConfig'
                                          * 副驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                          */
extern INT8U HeatAdj_MemDiagPaHeatFlg; /* '<S89>/HeatAdj_MemDiagPaHeatFlg'
                                        * 副驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
extern INT8U HeatAdj_MemDiagThirdHeatConfig;/* '<S89>/HeatAdj_MemDiagThirdHeatConfig'
                                             * P20方向盘加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                             */
extern INT8U HeatAdj_MemIndexDrHeatConfig;/* '<S89>/HeatAdj_MemIndexDrHeatConfig'
                                           * 加热配置&#10;0：无&#10;1：有
                                           */
extern INT8U HeatAdj_MemIndexPaHeatConfig;/* '<S89>/HeatAdj_MemIndexPaHeatConfig'
                                           * 加热配置&#10;0：无&#10;1：有
                                           */
extern INT8U HeatAdj_MemIndexThirdHeatConfig;/* '<S89>/HeatAdj_MemIndexThirdHeatConfig'
                                              * 加热配置&#10;0：无&#10;1：有
                                              */
extern INT8U HeatAdj_P20_PHEV_EngineCfg;/* '<S89>/HeatAdj_P20_PHEV_EngineCfg'
                                         * 加热P20PHEV发动机使能配置&#10;0：无加热P20PHEV发动机&#10;1：有加热P20PHEV发动机
                                         */
extern INT8U HeatAdj_PaVentFlg;        /* '<S89>/HeatAdj_PaVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
extern INT8U HeatAdj_PassengerHMI_Message;/* '<S89>/HeatAdj_PassengerHMI_Message'
                                           * 副驾加热HMI等级报文
                                           */
extern INT8U HeatAdj_PassengerTbox_Message;/* '<S89>/HeatAdj_PassengerTbox_Message'
                                            * 副驾加热Tbox等级报文
                                            */
extern INT8U HeatAdj_PassengerVentEnableConfig;/* '<S89>/HeatAdj_PassengerVentEnableConfig'
                                                * 二排通风配置&#10;0：不存在&#10;1：存在
                                                */
extern INT8U HeatAdj_Passenger_HMI_VentilateMsg;/* '<S89>/HeatAdj_Passenger_HMI_VentilateMsg'
                                                 * 副驾通风HMI报文
                                                 */
extern INT8U HeatAdj_Passenger_Tbox_VentilateMsg;/* '<S89>/HeatAdj_Passenger_Tbox_VentilateMsg'
                                                  * 副驾通风Tbox报文
                                                  */
extern INT8U HeatAdj_PlatformEngineEnableConfig;/* '<S89>/HeatAdj_PlatformEngineEnableConfig'
                                                 * 加热发动机使能配置&#10;0：无发动机使能&#10;1：有发动机使能
                                                 */
extern INT8U HeatAdj_PlatformVehicleEnableConfig;/* '<S89>/HeatAdj_PlatformVehicleEnableConfig'
                                                  * 加热整车运行使能配置&#10;0：无整车运行状态判断使能&#10;1：有整车运行状态判断使能
                                                  */
extern INT8U HeatAdj_RecoverDefaultFlag;/* '<S89>/HeatAdj_RecoverDefaultFlag'
                                         * 恢复出厂命令&#10;0：无效；&#10;1：有效
                                         */
extern INT8U HeatAdj_RemoteEnableConfig;/* '<S89>/HeatAdj_RemoteEnableConfig'
                                         * 加热远程使能配置&#10;0：无远程使能&#10;1：有远程使能
                                         */
extern INT8U HeatAdj_RemoteMsgLostFlag;/* '<S89>/HeatAdj_RemoteMsgLostFlag'
                                        * 加热远程报文掉线
                                        */
extern INT8U HeatAdj_RunMaxTime;       /* '<S89>/HeatAdj_RunMaxTime'
                                        * 加热超时时间配置&#10;0：无超时&#10;1-255min
                                        */
extern INT8U HeatAdj_TboxRemoteSts;    /* '<S89>/HeatAdj_TboxRemoteSts'
                                        * 加热远程模式状态&#10;0：无远程模式&#10;1：进远程模式
                                        */
extern INT8U HeatAdj_ThirdDiagMaxTime; /* '<S89>/HeatAdj_ThirdDiagMaxTime'
                                        * 方向盘加热最大时间，单位：s
                                        */
extern INT8U HeatAdj_ThirdHMI_Message; /* '<S89>/HeatAdj_ThirdHMI_Message'
                                        * 三排加热HMI等级报文
                                        */
extern INT8U HeatAdj_ThirdTbox_Message;/* '<S89>/HeatAdj_ThirdTbox_Message'
                                        * 三排加热Tbox等级报文
                                        */
extern INT8U HeatAdj_ThirdVentEnableConfig;/* '<S89>/HeatAdj_ThirdVentEnableConfig'
                                            * 三排通风使能配置&#10;0：不存在&#10;1：存在
                                            */
extern INT8U HeatAdj_Third_HMI_VentilateMsg;/* '<S89>/HeatAdj_Third_HMI_VentilateMsg'
                                             * 三排通风HMI报文
                                             */
extern INT8U HeatAdj_Third_Tbox_VentilateMsg;/* '<S89>/HeatAdj_Third_Tbox_VentilateMsg'
                                              * 三排通风Tbox报文
                                              */
extern INT8U HeatAdj_TimeOutPrm;       /* '<S89>/HeatAdj_TimeOutPrm'
                                        * 加热超时使能配置&#10;0：禁能&#10;1：使能
                                        */

/* Model entry point functions */
extern void Appl_HeatAdj_CtrlModel_initialize(void);
extern void Appl_HeatAdj_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_HeatAdj_CtrlModel_T *const Appl_HeatAdj_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT32U CAL_LEVEL3_TIMEOUT;/* 3档加热超时切温度（13min） */
extern const volatile INT32U CAL_SW_20min_TIMEOUT;/* 方向盘加热计时（20min） */

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
 * '<Root>' : 'Appl_HeatAdj_CtrlModel'
 * '<S1>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_HeatAdj_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_HeatAdj_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal'
 * '<S7>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal'
 * '<S8>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal'
 * '<S9>'   : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/CANAquireFunction'
 * '<S10>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction'
 * '<S11>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction1'
 * '<S12>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction2'
 * '<S13>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction3'
 * '<S14>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction4'
 * '<S15>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction5'
 * '<S16>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/SwLevelAquireFunction'
 * '<S17>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/SwLevelAquireFunction1'
 * '<S18>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/CANAquireFunction/CANAquireFunction'
 * '<S19>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction/LevelAquireFunction'
 * '<S20>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction1/LevelAquireFunction'
 * '<S21>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction2/LevelAquireFunction'
 * '<S22>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction3/LevelAquireFunction'
 * '<S23>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction4/LevelAquireFunction'
 * '<S24>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/LevelAquireFunction5/LevelAquireFunction'
 * '<S25>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/SwLevelAquireFunction/SwLevelAquireFunction'
 * '<S26>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/HeatLevelDeal/SwLevelAquireFunction1/SwLevelAquireFunction'
 * '<S27>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction'
 * '<S28>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction1'
 * '<S29>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction2'
 * '<S30>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction'
 * '<S31>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction1'
 * '<S32>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction2'
 * '<S33>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/MixConflic'
 * '<S34>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction'
 * '<S35>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction1'
 * '<S36>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction2'
 * '<S37>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction'
 * '<S38>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1'
 * '<S39>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2'
 * '<S40>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction/Diagnose'
 * '<S41>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction1/Diagnose'
 * '<S42>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/DiagnoseFunction2/Diagnose'
 * '<S43>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction/LevelLimit'
 * '<S44>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction1/LevelLimit'
 * '<S45>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/LevelLimitFunction2/LevelLimit'
 * '<S46>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction/StopFunction'
 * '<S47>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction1/StopFunction'
 * '<S48>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/StopFunction2/StopFunction'
 * '<S49>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout'
 * '<S50>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/D_HAL_GET_CUR_MS_TS'
 * '<S51>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/TimeDiffTs'
 * '<S52>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction/Timeout/TimeDiffTs/Chart'
 * '<S53>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout'
 * '<S54>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/D_HAL_GET_CUR_MS_TS'
 * '<S55>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/TimeDiffTs'
 * '<S56>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction1/Timeout/TimeDiffTs/Chart'
 * '<S57>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/LimitDeal/TimeoutFunction2/Timeout'
 * '<S58>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction'
 * '<S59>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction1'
 * '<S60>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2'
 * '<S61>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction'
 * '<S62>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction1'
 * '<S63>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction2'
 * '<S64>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction/HeatOut'
 * '<S65>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction/HeatOut/PidGetPwm'
 * '<S66>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction/HeatOut/PidGetPwm/Pid '
 * '<S67>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction1/HeatOut'
 * '<S68>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction1/HeatOut/PidGetPwm'
 * '<S69>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction1/HeatOut/PidGetPwm/Pid '
 * '<S70>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut'
 * '<S71>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut/D_HAL_GET_CUR_MS_TS'
 * '<S72>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut/PidGetPwm'
 * '<S73>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut/TimeDiffTs'
 * '<S74>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut/PidGetPwm/Pid '
 * '<S75>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/HeatOutFunction2/HeatOut/TimeDiffTs/Chart'
 * '<S76>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction/TempFunction'
 * '<S77>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction/TempFunction/D_HAL_GET_CUR_MS_TS'
 * '<S78>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction/TempFunction/TimeDiffTs'
 * '<S79>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction/TempFunction/TimeDiffTs/Chart'
 * '<S80>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction1/TempFunction'
 * '<S81>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction1/TempFunction/D_HAL_GET_CUR_MS_TS'
 * '<S82>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction1/TempFunction/TimeDiffTs'
 * '<S83>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction1/TempFunction/TimeDiffTs/Chart'
 * '<S84>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction2/TempFunction'
 * '<S85>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction2/TempFunction/D_HAL_GET_CUR_MS_TS'
 * '<S86>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction2/TempFunction/TimeDiffTs'
 * '<S87>'  : 'Appl_HeatAdj_CtrlModel/LogicCtrl/LocalAdjustCtrl/OutputDeal/TempFunction2/TempFunction/TimeDiffTs/Chart'
 * '<S88>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S89>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/RTE'
 * '<S90>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/CommonPreconditionDeal'
 * '<S91>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/DCDC_SwitchSts'
 * '<S92>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EngineRunning'
 * '<S93>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess'
 * '<S94>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatAndVentlateConfig'
 * '<S95>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage'
 * '<S96>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/MaxTime'
 * '<S97>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/RemoteMode'
 * '<S98>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VehRunSta'
 * '<S99>'  : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage'
 * '<S100>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/CommonPreconditionDeal/Deal'
 * '<S101>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EngineRunning/EngineStatus'
 * '<S102>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess'
 * '<S103>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction'
 * '<S104>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction1'
 * '<S105>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction2'
 * '<S106>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction3'
 * '<S107>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction4'
 * '<S108>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction5'
 * '<S109>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction/OppositeMessageDeal'
 * '<S110>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction1/OppositeMessageDeal'
 * '<S111>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction2/OppositeMessageDeal'
 * '<S112>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction3/OppositeMessageDeal'
 * '<S113>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction4/OppositeMessageDeal'
 * '<S114>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/EorrorProcess/EorrorProcess/ErrorFunction5/OppositeMessageDeal'
 * '<S115>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage'
 * '<S116>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction'
 * '<S117>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction1'
 * '<S118>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction2'
 * '<S119>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction/Function'
 * '<S120>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction1/Function'
 * '<S121>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/HeatMessage/HeatMessage/MsgConflictFunction2/Function'
 * '<S122>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/MaxTime/TimeChangeToCycle5'
 * '<S123>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/RemoteMode/RemoteMode'
 * '<S124>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VehRunSta/VehicleRunStatus'
 * '<S125>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage'
 * '<S126>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal'
 * '<S127>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal1'
 * '<S128>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal2'
 * '<S129>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal/OppositeMessageDeal'
 * '<S130>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal1/OppositeMessageDeal'
 * '<S131>' : 'Appl_HeatAdj_CtrlModel/UpDataInputInfo/InputSignalProcess/VentilateMessage/VentilateMessage/OppositeMessageDeal2/OppositeMessageDeal'
 */
#endif                                 /* RTW_HEADER_Appl_HeatAdj_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
