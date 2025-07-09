/*
 * File: Appl_DrMemory_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_DrMemory_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:39:39 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_DrMemory_CtrlModel_h_
#define RTW_HEADER_Appl_DrMemory_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_DrMemory_CtrlModel_COMMON_INCLUDES_
# define Appl_DrMemory_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_DrMemory_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_DrMemory_CtrlModel_T
  RT_MODEL_Appl_DrMemory_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enMemCallFb_
#define DEFINED_TYPEDEF_FOR_enMemCallFb_

/* ������÷���״̬:&#10;0x0: Inactive&#10;0x1: Call Memory Position Succeed&#10;0x2: Call Memory Position Faild&#10;0x3: Waiting&#10;0x4: Clean Up Memory Position Succeed&#10;0x5: Clean Up Memory Position Faild&#10;0x6: Reserved&#10;0x7: Invalid, */
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

/* ���书��ֹͣԭ��&#10;0����&#10;1��δѧϰ&#10;2�������˶�&#10;3����������&#10;4���̵���ճ��&#10;5����ת����&#10;6����ON��&#10;7����λ��P/N&#10;8�����ٹ���&#10;9��λ�ô���&#10;10�����书��ʧ��&#10;11��С�ģʽ��&#10;12������˶�&#10;13��e2p����&#10;14����ѹ����, */
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

/* ��������״̬&#10;0���޶���&#10;1��λ��1����ɹ�&#10;2��λ��2����ɹ�&#10;3��λ��3����ɹ�&#10;4��λ�ü���ʧ��&#10;5-7��Ԥ��, */
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

/* ���䰴ť����&#10;0����&#10;1������1&#10;2������1&#10;3�����1&#10;4������2&#10;5������2&#10;6�����2&#10;7������3&#10;8������3&#10;9�����3, */
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

/* ����������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����;&#10;6����λ&#10;7����λ&#10;8��С�&#10;9�����IO����, */
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

#ifndef DEFINED_TYPEDEF_FOR_enMemSet_
#define DEFINED_TYPEDEF_FOR_enMemSet_

/* ��������&#10;0����&#10;1������λ�� &#10;2�����䵱ǰλ��, */
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

/* С�ģʽ&#10;0x0:Inactive&#10;0x1:�ر�С�ģʽ&#10;0x2:��С�ģʽ&#10;0x3:ERROR, */
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

/* Block signals (default storage) */
typedef struct
{
  enMemStopCause PreMemSetStop;        /* '<S49>/PreconditionDeal' */
  enMemStopCause PreMemCallStop;       /* '<S49>/PreconditionDeal' */
  enMemStopCause PreMemRemindStop;     /* '<S48>/MemoryRemindPrecondition' */
  enMemStopCause PreMemRemindStop_d;   /* '<S1>/BusConversion_InsertedFor_MemoryOut_at_inport_0' */
  enMemStopCause MemSetStopReason;     /* '<S5>/MemorySetLogic' */
  enMemStopCause MemCallStopReason;    /* '<S5>/MemoryCall' */
  enMemSetFb FLSeatMemSetSts;          /* '<S5>/MemorySetLogic' */
  enMemCallFb SeatMem1StsFb;           /* '<S5>/MemoryCall' */
  enMemCallFb SeatMem2StsFb;           /* '<S5>/MemoryCall' */
  enMemCallFb SeatMem3StsFb;           /* '<S5>/MemoryCall' */
  enMemBtn SeatMemBtn;                 /* '<S47>/HmiDeal' */
  INT16U MemoryHeightPosi;             /* '<S46>/CallMemory' */
  INT16U MemoryLengthPosi;             /* '<S46>/CallMemory' */
  INT16U MemoryBackPosi;               /* '<S46>/CallMemory' */
  INT16U MemoryFrontPosi;              /* '<S46>/CallMemory' */
  INT16U In1;                          /* '<S5>/MemorySetLogic' */
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
  INT16U Sts_j;                        /* '<S5>/MemoryRemindLogic' */
  INT16U In1_h;                        /* '<S5>/MemoryRemindLogic' */
  INT16U DrMem_FrontHallPosi_a;        /* '<S16>/DrMem_FrontHallPosi' */
  INT16U SeatHeightPosiReq;            /* '<S5>/MemoryCall' */
  INT16U SeatLengthPosiReq;            /* '<S5>/MemoryCall' */
  INT16U SeatBackPosiReq;              /* '<S5>/MemoryCall' */
  INT16U SeatFrontPosiReq;             /* '<S5>/MemoryCall' */
  INT16U In1_g;                        /* '<S5>/MemoryCall' */
  INT16U In1_l;                        /* '<S5>/MemoryCall' */
  INT16U In1_k;                        /* '<S5>/MemoryCall' */
  INT16U DrMem_FrontHallPosi_m;        /* '<S9>/DrMem_FrontHallPosi' */
  INT8U SpeedLessThan5_Flag;           /* '<S50>/SpeedDeal' */
  INT8U MemSetPC_Flag;                 /* '<S49>/PreconditionDeal' */
  INT8U MemCallPC_Flag;                /* '<S49>/PreconditionDeal' */
  INT8U MemRemindPC_Flag;              /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result1st;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result2nd;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U Result3rd;                     /* '<S48>/MemoryRemindPrecondition' */
  INT8U MemoryValid;                   /* '<S46>/CallMemory' */
  INT8U SpeedLessThan5_Flag_c;         /* '<S1>/BusConversion_InsertedFor_MemoryOut_at_inport_0' */
  INT8U DrMem_FrontHallPosi_i;         /* '<S21>/DrMem_FrontHallPosi' */
  INT8U FLSeatPosMsg;                  /* '<S5>/MemoryRemindLogic' */
  INT8U SeatMemoryValidReq;            /* '<S5>/MemoryCall' */
}
B_Appl_DrMemory_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enMemCallFb MemoryCallFbSts;         /* '<S5>/MemoryCall' */
  enMemCallFb MemoryButtonNum;         /* '<S5>/MemoryCall' */
  enMemSetFb FLTempSeatMemSetSts;      /* '<S5>/MemorySetLogic' */
  enMemBtn SeatMemBtn_start;           /* '<S5>/MemorySetLogic' */
  enMemBtn SeatMemBtn_start_g;         /* '<S5>/MemoryCall' */
  INT16U WaitTimeCnt;                  /* '<S5>/MemorySetLogic' */
  INT16U WaitTimeCnt_f;                /* '<S5>/MemoryCall' */
  INT16U FbWaitTimeCnt;                /* '<S5>/MemoryCall' */
  INT8U is_active_c11_Appl_DrMemory_CtrlModel;/* '<S50>/SpeedDeal' */
  INT8U is_c11_Appl_DrMemory_CtrlModel;/* '<S50>/SpeedDeal' */
  INT8U is_active_c7_Appl_DrMemory_CtrlModel;/* '<S49>/PreconditionDeal' */
  INT8U is_MemorySetPreconditionDeal;  /* '<S49>/PreconditionDeal' */
  INT8U is_MemoryCallPreconditionDeal; /* '<S49>/PreconditionDeal' */
  INT8U is_active_c2_Appl_DrMemory_CtrlModel;/* '<S48>/MemoryRemindPrecondition' */
  INT8U is_MemoryRemindPreconditionDeal;/* '<S48>/MemoryRemindPrecondition' */
  INT8U is_active_c6_Appl_DrMemory_CtrlModel;/* '<S47>/HmiDeal' */
  INT8U is_AcquireMemoryButtonReq;     /* '<S47>/HmiDeal' */
  INT8U is_active_c1_Appl_DrMemory_CtrlModel;/* '<S46>/CallMemory' */
  INT8U is_c1_Appl_DrMemory_CtrlModel; /* '<S46>/CallMemory' */
  INT8U is_active_c3_Appl_DrMemory_CtrlModel;/* '<S5>/MemorySetLogic' */
  INT8U is_c3_Appl_DrMemory_CtrlModel; /* '<S5>/MemorySetLogic' */
  INT8U is_MemorySetActive;            /* '<S5>/MemorySetLogic' */
  INT8U MsgSendFinishedFlag;           /* '<S5>/MemorySetLogic' */
  INT8U WaitTimer;                     /* '<S5>/MemorySetLogic' */
  INT8U is_active_c5_Appl_DrMemory_CtrlModel;/* '<S5>/MemoryRemindLogic' */
  INT8U is_c5_Appl_DrMemory_CtrlModel; /* '<S5>/MemoryRemindLogic' */
  INT8U DrMem_CurrentMoveType_start;   /* '<S5>/MemoryRemindLogic' */
  INT8U is_active_c8_Appl_DrMemory_CtrlModel;/* '<S5>/MemoryCall' */
  INT8U is_MemoryCallLogic;            /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallActive;           /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallMessageFeedback;  /* '<S5>/MemoryCall' */
  INT8U is_MemoryCallResultFeedback;   /* '<S5>/MemoryCall' */
  INT8U MsgSendFinishedFlag_m;         /* '<S5>/MemoryCall' */
}
DW_Appl_DrMemory_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_DrMemory_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_DrMemory_CtrlModel_T Appl_DrMemory_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_DrMemory_CtrlModel_T Appl_DrMemory_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMotorRunType DrMem_AnyoneRelayFaultSts;/* '<S45>/DrMem_AnyoneRelayFaultSts'
                                                     * ������һ�̵���ճ�����ϱ�־
                                                     */
extern enSeatAutoRunSts DrMem_BackAutoRunFlag;/* '<S45>/DrMem_BackAutoRunFlag'
                                               * ���ݿ����Զ����б�־λ
                                               */
extern enSeatAutoRunSts DrMem_FrontAutoRunFlag;/* '<S45>/DrMem_FrontAutoRunFlag'
                                                * ����ǰ���Ƕ��Զ����б�־λ
                                                */
extern enSeatAutoRunSts DrMem_HeightAutoRunFlag;/* '<S45>/DrMem_HeightAutoRunFlag'
                                                 * ���ݸ߶��Զ����б�־λ
                                                 */
extern enSeatAutoRunSts DrMem_LengthAutoRunFlag;/* '<S45>/DrMem_LengthAutoRunFlag'
                                                 * ���������Զ����б�־λ
                                                 */
extern enPowerModeSts DrMem_PowerMode; /* '<S45>/DrMem_PowerMode'
                                        * ������Դ��λ
                                        */
extern enNapMode DrMem_NapMode;        /* '<S45>/DrMem_NapMode'
                                        * С�ģʽ
                                        */
extern enMemSet DrMem_IVI_FLSeatMemSet1;/* '<S45>/DrMem_IVI_FLSeatMemSet1'
                                         * ��������1
                                         */
extern enMemSet DrMem_IVI_FLSeatMemSet2;/* '<S45>/DrMem_IVI_FLSeatMemSet2'
                                         * ��������2
                                         */
extern enMemSet DrMem_IVI_FLSeatMemSet3;/* '<S45>/DrMem_IVI_FLSeatMemSet3'
                                         * ��������3
                                         */
extern enFinalPowerMode DrMem_VoltMode;/* '<S45>/DrMem_VoltMode'
                                        * ������ѹģʽ
                                        */
extern INT16U DrMem_BackHallPosi;      /* '<S45>/DrMem_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
extern INT16U DrMem_BackMem1;          /* '<S45>/DrMem_BackMem1'
                                        * ���ݼ���1��������λ��
                                        */
extern INT16U DrMem_BackMem2;          /* '<S45>/DrMem_BackMem2'
                                        * ���ݼ���2��������λ��
                                        */
extern INT16U DrMem_BackMem3;          /* '<S45>/DrMem_BackMem3'
                                        * ���ݼ���3��������λ��
                                        */
extern INT16U DrMem_FrontHallPosi;     /* '<S45>/DrMem_FrontHallPosi'
                                        * ����ǰ���Ƕȵ�ǰ����λ��
                                        */
extern INT16U DrMem_FrontMem1;         /* '<S45>/DrMem_FrontMem1'
                                        * ���ݼ���1ǰ���ǶȻ���λ��
                                        */
extern INT16U DrMem_FrontMem2;         /* '<S45>/DrMem_FrontMem2'
                                        * ���ݼ���2ǰ���ǶȻ���λ��
                                        */
extern INT16U DrMem_FrontMem3;         /* '<S45>/DrMem_FrontMem3'
                                        * ���ݼ���3ǰ���ǶȻ���λ��
                                        */
extern INT16U DrMem_GetRecoverDefaultFlag;/* '<S45>/DrMem_GetRecoverDefaultFlag'
                                           *  �ָ���������
                                           */
extern INT16U DrMem_HeightHallPosi;    /* '<S45>/DrMem_HeightHallPosi'
                                        * ���ݸ߶ȵ�ǰ����λ��
                                        */
extern INT16U DrMem_HeightMem1;        /* '<S45>/DrMem_HeightMem1'
                                        * ���ݼ���1�߶Ȼ���λ��
                                        */
extern INT16U DrMem_HeightMem2;        /* '<S45>/DrMem_HeightMem2'
                                        * ���ݼ���2�߶Ȼ���λ��
                                        */
extern INT16U DrMem_HeightMem3;        /* '<S45>/DrMem_HeightMem3'
                                        * ���ݼ���3�߶Ȼ���λ��
                                        */
extern INT16U DrMem_LengthHallPosi;    /* '<S45>/DrMem_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
extern INT16U DrMem_LengthMem1;        /* '<S45>/DrMem_LengthMem1'
                                        * ���ݼ���1�������λ��
                                        */
extern INT16U DrMem_LengthMem2;        /* '<S45>/DrMem_LengthMem2'
                                        * ���ݼ���2�������λ��
                                        */
extern INT16U DrMem_LengthMem3;        /* '<S45>/DrMem_LengthMem3'
                                        * ���ݼ���3�������λ��
                                        */
extern INT16U DrMem_VehicleSpeed;      /* '<S45>/DrMem_VehicleSpeed'
                                        * ����
                                        */
extern INT8U DrMem_0x284_SpeedLostFlag;/* '<S45>/DrMem_0x284_SpeedLostFlag'
                                        * 0x284���ĵ��߱�־λ
                                        */
extern INT8U DrMem_AdjustEnable;       /* '<S45>/DrMem_AdjustEnable'
                                        * �������ε���
                                        */
extern INT8U DrMem_AnyoneLockFaultSts; /* '<S45>/DrMem_AnyoneLockFaultSts'
                                        * ������һ�����ת״̬
                                        */
extern INT8U DrMem_BackLockFault;      /* '<S45>/DrMem_BackLockFault'
                                        * �������ο�����ת
                                        */
extern INT8U DrMem_BackSwitch;         /* '<S45>/DrMem_BackSwitch'
                                        * ������������
                                        */
extern INT8U DrMem_CurrentMoveType;    /* '<S45>/DrMem_CurrentMoveType'
                                        * ���ݵ����ǰ�������ͣ�
                                        */
extern INT8U DrMem_DtcAnyoneHallFaultSts;/* '<S45>/DrMem_DtcAnyoneHallFaultSts'
                                          * ������һ�����������
                                          */
extern INT8U DrMem_FLSeatPosMsg;       /* '<S45>/DrMem_FLSeatPosMsg'
                                        * ������ʾ��������
                                        */
extern INT8U DrMem_FrontLockFault;     /* '<S45>/DrMem_FrontLockFault'
                                        * �����������ж�ת
                                        */
extern INT8U DrMem_FrontSwitch;        /* '<S45>/DrMem_FrontSwitch'
                                        * ���п�������
                                        */
extern INT8U DrMem_Gear_PN_FlagOut;    /* '<S45>/DrMem_Gear_PN_FlagOut'
                                        * PN����־λ
                                        */
extern INT8U DrMem_HeightLockFault;    /* '<S45>/DrMem_HeightLockFault'
                                        * �������θ߶ȶ�ת
                                        */
extern INT8U DrMem_HeightSwitch;       /* '<S45>/DrMem_HeightSwitch'
                                        * �߶ȿ�������
                                        */
extern INT8U DrMem_LengthLockFault;    /* '<S45>/DrMem_LengthLockFault'
                                        * �������������ת
                                        */
extern INT8U DrMem_LengthSwitch;       /* '<S45>/DrMem_LengthSwitch'
                                        * ���򿪹�����
                                        */
extern INT8U DrMem_MemoryConfig;       /* '<S45>/DrMem_MemoryConfig'
                                        * �������μ���ӭ��ʹ��:
                                        */
extern INT8U DrMem_SeatLearnResult;    /* '<S45>/DrMem_SeatLearnResult'
                                        * ��������ѧϰ״̬
                                        */
extern INT8U DrMem_SeatMemory1Valid;   /* '<S45>/DrMem_SeatMemory1Valid'
                                        * ����1λ����Ч��־
                                        */
extern INT8U DrMem_SeatMemory2Valid;   /* '<S45>/DrMem_SeatMemory2Valid'
                                        * ����2λ����Ч��־
                                        */
extern INT8U DrMem_SeatMemory3Valid;   /* '<S45>/DrMem_SeatMemory3Valid'
                                        * ����3λ����Ч��־
                                        */
extern INT8U DrMem_VehicleSpeedValid;  /* '<S45>/DrMem_VehicleSpeedValid'
                                        * ������Ч��
                                        */
extern INT8U DrMem_VoltSatisfy;        /* '<S45>/DrMem_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */

/* Model entry point functions */
extern void Appl_DrMemory_CtrlModel_initialize(void);
extern void Appl_DrMemory_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_DrMemory_CtrlModel_T *const Appl_DrMemory_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT8U CAL_DrMem_100MS;/* ��ʱ100ms */
extern const volatile INT8U CAL_DrMem_90MS;/* ��ʱ90ms */

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
 * '<Root>' : 'Appl_DrMemory_CtrlModel'
 * '<S1>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_DrMemory_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_DrMemory_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_DrMemory_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall'
 * '<S7>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic'
 * '<S8>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic'
 * '<S9>'   : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/GetCanSendEvent'
 * '<S10>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/MemCallWaitFBFunc'
 * '<S11>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanMemCall1'
 * '<S12>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanMemCall2'
 * '<S13>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanMemCall3'
 * '<S14>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/SetCanSendEvent'
 * '<S15>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryCall/MemCallWaitFBFunc/Chart'
 * '<S16>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/GetCanSendEvent'
 * '<S17>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/SetCanSendEvent'
 * '<S18>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/SetCanSendFLSeatPosMsg'
 * '<S19>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemoryRemindLogic/WriteFLSeatPosMsg'
 * '<S20>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc'
 * '<S21>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/GetCanSendEvent'
 * '<S22>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc'
 * '<S23>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SetCanSendEvent'
 * '<S24>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SetCanSendFLSeatMemSts'
 * '<S25>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc'
 * '<S26>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc'
 * '<S27>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryBack'
 * '<S28>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryFront'
 * '<S29>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryHight'
 * '<S30>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryLength'
 * '<S31>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/FirstPosiMemSetFunc/FirstPosiMemSetFunc/MemoryValid'
 * '<S32>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc'
 * '<S33>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryBack'
 * '<S34>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryFront'
 * '<S35>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryHight'
 * '<S36>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryLength'
 * '<S37>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/SecondPosiMemSetFunc/SecondPosiMemSetFunc/MemoryValid'
 * '<S38>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc'
 * '<S39>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryBack'
 * '<S40>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryFront'
 * '<S41>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryHight'
 * '<S42>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryLength'
 * '<S43>'  : 'Appl_DrMemory_CtrlModel/LogicCtrl/LocalAdjustCtrl/MemorySetLogic/ThirdPosiMemSetFunc/ThirdPosiMemSetFunc/MemoryValid'
 * '<S44>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S45>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/RTE'
 * '<S46>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/CallMemDeal'
 * '<S47>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/HmiMessageDeal'
 * '<S48>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal'
 * '<S49>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemorySetCallPreconditionDeal'
 * '<S50>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/VehicleSpeedDeal'
 * '<S51>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/CallMemDeal/CallMemory'
 * '<S52>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/HmiMessageDeal/HmiDeal'
 * '<S53>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition'
 * '<S54>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition/PosiCompareFunc'
 * '<S55>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemoryRemindPreconditionDeal/MemoryRemindPrecondition/PosiCompareFunc/PosiCompareFunc'
 * '<S56>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/MemorySetCallPreconditionDeal/PreconditionDeal'
 * '<S57>'  : 'Appl_DrMemory_CtrlModel/UpDataInputInfo/InputSignalProcess/VehicleSpeedDeal/SpeedDeal'
 */
#endif                                 /* RTW_HEADER_Appl_DrMemory_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
