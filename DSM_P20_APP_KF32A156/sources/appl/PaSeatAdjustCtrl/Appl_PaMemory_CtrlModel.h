/*
 * File: Appl_PaMemory_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_PaMemory_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:53:19 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaMemory_CtrlModel_h_
#define RTW_HEADER_Appl_PaMemory_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_PaMemory_CtrlModel_COMMON_INCLUDES_
# define Appl_PaMemory_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_PaMemory_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_PaMemory_CtrlModel_T
  RT_MODEL_Appl_PaMemory_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enMemCallFb_
#define DEFINED_TYPEDEF_FOR_enMemCallFb_

/* 记忆调用反馈状态:&#10;0x0: Inactive&#10;0x1: Call Memory Position Succeed&#10;0x2: Call Memory Position Faild&#10;0x3: Waiting&#10;0x4: Clean Up Memory Position Succeed&#10;0x5: Clean Up Memory Position Faild&#10;0x6: Reserved&#10;0x7: Invalid, */
typedef enum
{
  enMemCallFb_EN_MemCallFb_NULL = 0,   /* Default value */
  enMemCallFb_EN_MemCallFb_Succeed,
  enMemCallFb_EN_MemCallFb_Faild,
  enMemCallFb_EN_MemCallFb_Wait,
  enMemCallFb_EN_MemCallFb_CleanS,
  enMemCallFb_EN_MemCallFb_CleanF,
  enMemCallFb_EN_MemCallFb_Res,
  enMemCallFb_EN_MemCallFb_Invalid
}
enMemCallFb;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMemStopCause_
#define DEFINED_TYPEDEF_FOR_enMemStopCause_

/* 记忆功能停止原因：&#10;0：无&#10;1：未学习&#10;2：座椅运动&#10;3：霍尔故障&#10;4：继电器粘连&#10;5：堵转故障&#10;6：非ON档&#10;7：档位非P/N&#10;8：车速故障&#10;9：位置错误&#10;10：记忆功能失能&#10;11：小憩模式打开&#10;12：电机运动&#10;13：e2p故障&#10;14：电压故障, */
typedef enum
{
  enMemStopCause_EN_MemStop_NULL = 0,  /* Default value */
  enMemStopCause_EN_MemStop_Learn,
  enMemStopCause_EN_MemStop_OtherMove,
  enMemStopCause_EN_MemStop_HallErr,
  enMemStopCause_EN_MemStop_RelayErr,
  enMemStopCause_EN_MemStop_StallErr,
  enMemStopCause_EN_MemStop_NotON,
  enMemStopCause_EN_MemStop_NotGearPN,
  enMemStopCause_EN_MemStop_SpeedError,
  enMemStopCause_EN_MemStop_PosiError,
  enMemStopCause_EN_MemStop_ConfigError,
  enMemStopCause_EN_MemStop_NapError,
  enMemStopCause_EN_MemStop_MotorRunErr,
  enMemStopCause_EN_MemStop_EEPROMErr,
  enMemStopCause_EN_MemStop_VoltageErr
}
enMemStopCause;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMemSetFb_
#define DEFINED_TYPEDEF_FOR_enMemSetFb_

/* 记忆设置状态&#10;0：无动作&#10;1：位置1记忆成功&#10;2：位置2记忆成功&#10;3：位置3记忆成功&#10;4：位置记忆失败&#10;5-7：预留, */
typedef enum
{
  enMemSetFb_EN_MemSetFb_NULL = 0,     /* Default value */
  enMemSetFb_EN_MemSetFb_S1,
  enMemSetFb_EN_MemSetFb_S2,
  enMemSetFb_EN_MemSetFb_S3,
  enMemSetFb_EN_MemSetFb_Fail
}
enMemSetFb;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMemBtn_
#define DEFINED_TYPEDEF_FOR_enMemBtn_

/* 记忆按钮请求&#10;0：无&#10;1：记忆1&#10;2：调用1&#10;3：清除1&#10;4：记忆2&#10;5：调用2&#10;6：清除2&#10;7：记忆3&#10;8：调用3&#10;9：清除3, */
typedef enum
{
  enMemBtn_EN_MemBtn_NULL = 0,         /* Default value */
  enMemBtn_EN_MemBtn_Set1,
  enMemBtn_EN_MemBtn_Call1,
  enMemBtn_EN_MemBtn_Clear1,
  enMemBtn_EN_MemBtn_Set2,
  enMemBtn_EN_MemBtn_Call2,
  enMemBtn_EN_MemBtn_Clear2,
  enMemBtn_EN_MemBtn_Set3,
  enMemBtn_EN_MemBtn_Call3,
  enMemBtn_EN_MemBtn_Clear3
}
enMemBtn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunType_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunType_

/* 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节;&#10;6：复位&#10;7：档位&#10;8：小憩&#10;9：诊断IO控制, */
typedef enum
{
  enSeatMotorRunType_EN_NULL = 0,      /* Default value */
  enSeatMotorRunType_EN_HUMEnable,
  enSeatMotorRunType_EN_ComfortEnable,
  enSeatMotorRunType_EN_MemoryEnable,
  enSeatMotorRunType_EN_ManualEnable,
  enSeatMotorRunType_EN_LearnEnable,
  enSeatMotorRunType_EN_ResetEnable,
  enSeatMotorRunType_EN_GearEnable,
  enSeatMotorRunType_EN_ResEnable,
  enSeatMotorRunType_EN_DiagIOEnable
}
enSeatMotorRunType;

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

#ifndef DEFINED_TYPEDEF_FOR_enMemSet_
#define DEFINED_TYPEDEF_FOR_enMemSet_

/* 记忆设置&#10;0：无&#10;1：请求位置 &#10;2：记忆当前位置, */
typedef enum
{
  enMemSet_EN_MemSet_NULL = 0,         /* Default value */
  enMemSet_EN_MemSet_Call,
  enMemSet_EN_MemSet_Mem,
  enMemSet_EN_MemSet_Clean
}
enMemSet;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enNapMode_
#define DEFINED_TYPEDEF_FOR_enNapMode_

/* 小憩模式&#10;0x0:Inactive&#10;0x1:关闭小憩模式&#10;0x2:打开小憩模式&#10;0x3:ERROR, */
typedef enum
{
  enNapMode_EN_NapMode_NULL = 0,       /* Default value */
  enNapMode_EN_NapMode_Close,
  enNapMode_EN_NapMode_Open,
  enNapMode_EN_NapMode_ERR
}
enNapMode;

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

/* Block signals (default storage) */
typedef struct
{
  enMemStopCause PreMemSetStop;        /* '<S49>/PreconditionDeal' */
  enMemStopCause PreMemCallStop;       /* '<S49>/PreconditionDeal' */
  enMemStopCause PreMemRemindStop;     /* '<S48>/MemoryRemindPrecondition' */
  enMemStopCause PreMemRemindStop_d;   /* '<S1>/BusConversion_InsertedFor_MemoryOut_at_inport_0' */
  enMemStopCause MemSetStopReason;     /* '<S5>/MemorySetLogic' */
  enMemStopCause MemCallStopReason;    /* '<S5>/MemoryCall' */
  enMemSetFb FRSeatMemSetSts;          /* '<S5>/MemorySetLogic' */
  enMemCallFb SeatMem1StsFb;           /* '<S5>/MemoryCall' */
  enMemCallFb SeatMem2StsFb;           /* '<S5>/MemoryCall' */
  enMemCallFb SeatMem3StsFb;           /* '<S5>/MemoryCall' */
  enMemBtn SeatMemBtn;                 /* '<S47>/HmiDeal' */
  INT16U MemoryHeightPosi;             /* '<S46>/CallMemory' */
  INT16U MemoryLengthPosi;             /* '<S46>/CallMemory' */
  INT16U MemoryBackPosi;               /* '<S46>/CallMemory' */
  INT16U MemoryFrontPosi;              /* '<S46>/CallMemory' */
  INT16U In1;                          /* '<S5>/MemorySetLogic' */
  INT16U In1_n;                        /* '<S5>/MemorySetLogic' */
  INT16U DrMem_FrontHallPosi;          /* '<S21>/DrMem_FrontHallPosi' */
  INT16U CurrentH_k;                   /* '<S25>/ThirdPosiMemSetFunc' */
  INT16U CurrentL_g;                   /* '<S25>/ThirdPosiMemSetFunc' */
  INT16U CurrentB_l;                   /* '<S25>/ThirdPosiMemSetFunc' */
  INT16U CurrentF_a;                   /* '<S25>/ThirdPosiMemSetFunc' */
  INT16U Sts;                          /* '<S25>/ThirdPosiMemSetFunc' */
  INT16U CurrentH_ke;                  /* '<S22>/SecondPosiMemSetFunc' */
  INT16U CurrentL_l;                   /* '<S22>/SecondPosiMemSetFunc' */
  INT16U CurrentB_c;                   /* '<S22>/SecondPosiMemSetFunc' */
  INT16U CurrentF_h;                   /* '<S22>/SecondPosiMemSetFunc' */
  INT16U Sts_g;                        /* '<S22>/SecondPosiMemSetFunc' */
  INT16U CurrentH_h;                   /* '<S20>/FirstPosiMemSetFunc' */
  INT16U CurrentL_b;                   /* '<S20>/FirstPosiMemSetFunc' */
  INT16U CurrentB_o;                   /* '<S20>/FirstPosiMemSetFunc' */
  INT16U CurrentF_e;                   /* '<S20>/FirstPosiMemSetFunc' */
  INT16U Sts_n;                        /* '<S20>/FirstPosiMemSetFunc' */
  INT16U In1_b;                        /* '<S5>/MemoryRemindLogic' */
  INT16U In1_e;                        /* '<S5>/MemoryRemindLogic' */
  INT16U Sts_a;                        /* '<S5>/MemoryRemindLogic' */
  INT16U DrMem_FrontHallPosi_a;        /* '<S16>/DrMem_FrontHallPosi' */
  INT16U SeatHeightPosiReq;            /* '<S5>/MemoryCall' */
  INT16U SeatLengthPosiReq;            /* '<S5>/MemoryCall' */
  INT16U SeatBackPosiReq;              /* '<S5>/MemoryCall' */
  INT16U SeatFrontPosiReq;             /* '<S5>/MemoryCall' */
  INT16U In1_l;                        /* '<S5>/MemoryCall' */
  INT16U In1_h;                        /* '<S5>/MemoryCall' */
  INT16U In1_ny;                       /* '<S5>/MemoryCall' */
  INT16U In1_lu;                       /* '<S5>/MemoryCall' */
  INT16U DrMem_FrontHallPosi_m;        /* '<S9>/DrMem_FrontHallPosi' */
  INT8U MemSetPC_Flag;                 /* '<S49>/PreconditionDeal' */
  INT8U MemCallPC_Flag;                /* '<S49>/PreconditionDeal' */
  INT8U MemRemindPC_Flag;              /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result1st;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result2nd;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result3rd;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U MemoryValid;                   /* '<S46>/CallMemory' */
  INT8U FRSeatPosMsg;                  /* '<S5>/MemoryRemindLogic' */
  INT8U SeatMemoryValidReq;            /* '<S5>/MemoryCall' */
}
B_Appl_PaMemory_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enMemCallFb MemoryCallFbSts;         /* '<S5>/MemoryCall' */
  enMemCallFb MemoryButtonNum;         /* '<S5>/MemoryCall' */
  enMemSetFb FRTempSeatMemSetSts;      /* '<S5>/MemorySetLogic' */
  enMemBtn SeatMemBtn_start;           /* '<S5>/MemorySetLogic' */
  enMemBtn SeatMemBtn_start_l;         /* '<S5>/MemoryCall' */
  INT16U WaitTimeCnt;                  /* '<S5>/MemorySetLogic' */
  INT16U WaitTimeCnt_m;                /* '<S5>/MemoryCall' */
  INT16U FbWaitTimeCnt;                /* '<S5>/MemoryCall' */
  INT8U is_active_c7_Appl_PaMemory_CtrlModel;/* '<S49>/PreconditionDeal' */
  INT8U is_MemorySetPreconditionDeal;  /* '<S49>/PreconditionDeal' */
  INT8U is_MemoryCallPreconditionDeal; /* '<S49>/PreconditionDeal' */
  INT8U is_active_c2_Appl_PaMemory_CtrlModel;/* '<S48>/MemoryRemindPrecondition' */
  INT8U is_MemoryRemindPreconditionDeal;/* '<S48>/MemoryRemindPrecondition' */
  INT8U is_active_c6_Appl_PaMemory_CtrlModel;/* '<S47>/HmiDeal' */
  INT8U is_AcquireMemoryButtonReq;     /* '<S47>/HmiDeal' */
  INT8U is_active_c1_Appl_PaMemory_CtrlModel;/* '<S46>/CallMemory' */
  INT8U is_c1_Appl_PaMemory_CtrlModel; /* '<S46>/CallMemory' */
  INT8U is_active_c3_Appl_PaMemory_CtrlModel;/* '<S5>/MemorySetLogic' */
  INT8U is_c3_Appl_PaMemory_CtrlModel; /* '<S5>/MemorySetLogic' */
  INT8U is_MemorySetActive;            /* '<S5>/MemorySetLogic' */
  INT8U MsgSendFinishedFlag;           /* '<S5>/MemorySetLogic' */
  INT8U WaitTimer;                     /* '<S5>/MemorySetLogic' */
  INT8U is_active_c5_Appl_PaMemory_CtrlModel;/* '<S5>/MemoryRemindLogic' */
  INT8U is_c5_Appl_PaMemory_CtrlModel; /* '<S5>/MemoryRemindLogic' */
  INT8U PaMem_CurrentMoveType_start;   /* '<S5>/MemoryRemindLogic' */
  INT8U is_active_c8_Appl_PaMemory_CtrlModel;/* '<S5>/MemoryCall' */
  INT8U is_MemoryCallLogic;            /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallActive;           /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallMessageFeedback;  /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallResultFeedback;   /* '<S5>/MemoryCall' */
  INT8U MsgSendFinishedFlag_j;         /* '<S5>/MemoryCall' */
}
DW_Appl_PaMemory_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_PaMemory_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_PaMemory_CtrlModel_T Appl_PaMemory_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_PaMemory_CtrlModel_T Appl_PaMemory_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMotorRunType PaMem_AnyoneRelayFaultSts;/* '<S45>/PaMem_AnyoneRelayFaultSts'
                                                     * 副驾任一继电器粘连故障标志&#10;0：无故障&#10;1：有故障
                                                     */
extern enSeatAutoRunSts PaMem_BackAutoRunFlag;/* '<S45>/PaMem_BackAutoRunFlag'
                                               * 副驾靠背自动运行标志位
                                               */
extern enSeatAutoRunSts PaMem_FrontAutoRunFlag;/* '<S45>/PaMem_FrontAutoRunFlag'
                                                * 副驾前部角度自动运行标志位
                                                */
extern enSeatAutoRunSts PaMem_HeightAutoRunFlag;/* '<S45>/PaMem_HeightAutoRunFlag'
                                                 * 副驾高度自动运行标志位
                                                 */
extern enSeatAutoRunSts PaMem_LengthAutoRunFlag;/* '<S45>/PaMem_LengthAutoRunFlag'
                                                 * 副驾纵向自动运行标志位
                                                 */
extern enPowerModeSts PaMem_PowerMode; /* '<S45>/PaMem_PowerMode'
                                        * 整车电源档位&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK
                                        */
extern enNapMode PaMem_NapMode;        /* '<S45>/PaMem_NapMode'
                                        * 小憩模式&#10;0x0:Inactive&#10;0x1:关闭小憩模式&#10;0x2:打开小憩模式&#10;0x3:ERROR
                                        */
extern enMemSet PaMem_IVI_FRSeatMemSet1;/* '<S45>/PaMem_IVI_FRSeatMemSet1'
                                         * 记忆设置&#10;0：无&#10;1：请求位置 &#10;2：记忆当前位置
                                         */
extern enMemSet PaMem_IVI_FRSeatMemSet2;/* '<S45>/PaMem_IVI_FRSeatMemSet2'
                                         * 记忆设置&#10;0：无&#10;1：请求位置 &#10;2：记忆当前位置
                                         */
extern enMemSet PaMem_IVI_FRSeatMemSet3;/* '<S45>/PaMem_IVI_FRSeatMemSet3'
                                         * 记忆设置&#10;0：无&#10;1：请求位置 &#10;2：记忆当前位置
                                         */
extern enFinalPowerMode PaMem_VoltMode;/* '<S45>/PaMem_VoltMode'
                                        * 整车电压模式&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
extern INT16U PaMem_BackHallPosi;      /* '<S45>/PaMem_BackHallPosi'
                                        * 副驾靠背当前霍尔位置
                                        */
extern INT16U PaMem_BackMem1;          /* '<S45>/PaMem_BackMem1'
                                        * 副驾记忆1靠背霍尔位置
                                        */
extern INT16U PaMem_BackMem2;          /* '<S45>/PaMem_BackMem2'
                                        * 副驾记忆2靠背霍尔位置
                                        */
extern INT16U PaMem_BackMem3;          /* '<S45>/PaMem_BackMem3'
                                        * 副驾记忆3靠背霍尔位置
                                        */
extern INT16U PaMem_FrontHallPosi;     /* '<S45>/PaMem_FrontHallPosi'
                                        * 副驾前部角度当前霍尔位置
                                        */
extern INT16U PaMem_FrontMem1;         /* '<S45>/PaMem_FrontMem1'
                                        * 副驾记忆1前部角度霍尔位置
                                        */
extern INT16U PaMem_FrontMem2;         /* '<S45>/PaMem_FrontMem2'
                                        * 副驾记忆2前部角度霍尔位置
                                        */
extern INT16U PaMem_FrontMem3;         /* '<S45>/PaMem_FrontMem3'
                                        * 副驾记忆3前部角度霍尔位置
                                        */
extern INT16U PaMem_GetRecoverDefaultFlag;/* '<S45>/PaMem_GetRecoverDefaultFlag'
                                           *  恢复出厂设置
                                           */
extern INT16U PaMem_HeightHallPosi;    /* '<S45>/PaMem_HeightHallPosi'
                                        * 副驾高度当前霍尔位置
                                        */
extern INT16U PaMem_HeightMem1;        /* '<S45>/PaMem_HeightMem1'
                                        * 副驾记忆1高度霍尔位置
                                        */
extern INT16U PaMem_HeightMem2;        /* '<S45>/PaMem_HeightMem2'
                                        * 副驾记忆2高度霍尔位置
                                        */
extern INT16U PaMem_HeightMem3;        /* '<S45>/PaMem_HeightMem3'
                                        * 副驾记忆3高度霍尔位置
                                        */
extern INT16U PaMem_LengthHallPosi;    /* '<S45>/PaMem_LengthHallPosi'
                                        * 副驾纵向当前霍尔位置
                                        */
extern INT16U PaMem_LengthMem1;        /* '<S45>/PaMem_LengthMem1'
                                        * 副驾记忆1纵向霍尔位置
                                        */
extern INT16U PaMem_LengthMem2;        /* '<S45>/PaMem_LengthMem2'
                                        * 副驾记忆2纵向霍尔位置
                                        */
extern INT16U PaMem_LengthMem3;        /* '<S45>/PaMem_LengthMem3'
                                        * 副驾记忆3纵向霍尔位置
                                        */
extern INT8U PaMem_AdjustEnable;       /* '<S45>/PaMem_AdjustEnable'
                                        * 副驾座椅调节:&#10;0x00:manual&#10;0x01:Six way motor&#10;0x02:Twelve way motor
                                        */
extern INT8U PaMem_BackLockFault;      /* '<S45>/PaMem_BackLockFault'
                                        * 副驾座椅靠背堵转&#10;0：无堵转；&#10;1：已堵转
                                        */
extern INT8U PaMem_CurrentMoveType;    /* '<S45>/PaMem_CurrentMoveType'
                                        * 副驾电机当前动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节
                                        */
extern INT8U PaMem_DtcAnyoneHallFaultSts;/* '<S45>/PaMem_DtcAnyoneHallFaultSts'
                                          * 副驾任一电机霍尔故障&#10;0：无&#10;1：有
                                          */
extern INT8U PaMem_FRSeatPosMsg;       /* '<S45>/PaMem_FRSeatPosMsg'
                                        * 记忆提示反馈报文&#10;0：无变化&#10;1：有变化
                                        */
extern INT8U PaMem_FrontLockFault;     /* '<S45>/PaMem_FrontLockFault'
                                        * 副驾座椅腿托堵转&#10;0：无堵转；&#10;1：已堵转
                                        */
extern INT8U PaMem_Gear_PN_FlagOut;    /* '<S45>/PaMem_Gear_PN_FlagOut'
                                        * PN档标志位&#10;0：非PN；&#10;1：PN档
                                        */
extern INT8U PaMem_HeightLockFault;    /* '<S45>/PaMem_HeightLockFault'
                                        * 副驾座椅高度堵转&#10;0：无堵转；&#10;1：已堵转
                                        */
extern INT8U PaMem_LengthLockFault;    /* '<S45>/PaMem_LengthLockFault'
                                        * 副驾座椅纵向堵转&#10;0：无堵转；&#10;1：已堵转
                                        */
extern INT8U PaMem_PABackSwitch;       /* '<S45>/PaMem_PABackSwitch'
                                        * 靠背开关命令
                                        */
extern INT8U PaMem_PAFrontSwitch;      /* '<S45>/PaMem_PAFrontSwitch'
                                        * 腿托开关命令
                                        */
extern INT8U PaMem_PAHeightSwitch;     /* '<S45>/PaMem_PAHeightSwitch'
                                        * 高度开关命令
                                        */
extern INT8U PaMem_PALengthSwitch;     /* '<S45>/PaMem_PALengthSwitch'
                                        * 纵向开关命令
                                        */
extern INT8U PaMem_PaAnyoneLockFaultSts;/* '<S45>/PaMem_PaAnyoneLockFaultSts'
                                         * 副驾任一堵转状态&#10;0：无效&#10;2：有效
                                         */
extern INT8U PaMem_PaMemoryConfig;     /* '<S45>/PaMem_PaMemoryConfig'
                                        * 副驾记忆迎宾配置
                                        */
extern INT8U PaMem_SeatLearnResult;    /* '<S45>/PaMem_SeatLearnResult'
                                        * 副驾座椅学习结果&#10;0：未学习；&#10;1：已学习
                                        */
extern INT8U PaMem_SeatMemory1Valid;   /* '<S45>/PaMem_SeatMemory1Valid'
                                        * 记忆位置有效标志&#10;0：无效&#10;1：有效
                                        */
extern INT8U PaMem_SeatMemory2Valid;   /* '<S45>/PaMem_SeatMemory2Valid'
                                        * 记忆位置有效标志&#10;0：无效&#10;1：有效
                                        */
extern INT8U PaMem_SeatMemory3Valid;   /* '<S45>/PaMem_SeatMemory3Valid'
                                        * 记忆位置有效标志&#10;0：无效&#10;1：有效
                                        */
extern INT8U PaMem_SpeedLessThan5_Flag;/* '<S45>/PaMem_SpeedLessThan5_Flag'
                                        * 车速小于5&#10;0：无&#10;1：超过
                                        */
extern INT8U PaMem_VoltSatisfy;        /* '<S45>/PaMem_VoltSatisfy'
                                        * 电机调节电压是否满足：&#10;0：不满足&#10;1：满足
                                        */

/* Model entry point functions */
extern void Appl_PaMemory_CtrlModel_initialize(void);
extern void Appl_PaMemory_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_PaMemory_CtrlModel_T *const Appl_PaMemory_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT8U CAL_PaMem_100MS;/* 延时100ms */
extern const volatile INT8U CAL_PaMem_90MS;/* 延时90ms */

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
 * '<Root>' : 'Appl_PaMemory_CtrlModel'
 * '<S1>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_PaMemory_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_PaMemory_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_PaMemory_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall'
 * '<S7>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic'
 * '<S8>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic'
 * '<S9>'   : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/GetCanSendEvent'
 * '<S10>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/MemCallWaitFBFunc'
 * '<S11>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanSendEvent'
 * '<S12>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanSendFRSeatMem1Sts'
 * '<S13>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanSendFRSeatMem2Sts'
 * '<S14>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanSendFRSeatMem3Sts'
 * '<S15>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/MemCallWaitFBFunc/Chart'
 * '<S16>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/GetCanSendEvent'
 * '<S17>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/SetCanSendEvent'
 * '<S18>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/SetCanSendFRSeatPosMsg'
 * '<S19>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/WriteFLSeatPosMsg'
 * '<S20>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc'
 * '<S21>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/GetCanSendEvent'
 * '<S22>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc'
 * '<S23>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SetCanSendEvent'
 * '<S24>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SetCanSendMemStsAndMsg'
 * '<S25>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc'
 * '<S26>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc'
 * '<S27>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryBack'
 * '<S28>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryFront'
 * '<S29>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryHight'
 * '<S30>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryLength'
 * '<S31>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryValid'
 * '<S32>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc'
 * '<S33>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryBack'
 * '<S34>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryFront'
 * '<S35>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryHight'
 * '<S36>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryLength'
 * '<S37>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryValid'
 * '<S38>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc'
 * '<S39>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryBack'
 * '<S40>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryFront'
 * '<S41>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryHight'
 * '<S42>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryLength'
 * '<S43>'  : 'Appl_PaMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryValid'
 * '<S44>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S45>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/RTE'
 * '<S46>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/CallMemDeal'
 * '<S47>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/HmiMessageDeal'
 * '<S48>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal'
 * '<S49>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemorySetCallPreconditionDeal'
 * '<S50>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/CallMemDeal/CallMemory'
 * '<S51>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/HmiMessageDeal/HmiDeal'
 * '<S52>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition'
 * '<S53>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition/PosiCompareFunc'
 * '<S54>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition/PosiCompareFunc/PosiCompareFunc'
 * '<S55>'  : 'Appl_PaMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemorySetCallPreconditionDeal/PreconditionDeal'
 */
#endif                                 /* RTW_HEADER_Appl_PaMemory_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
