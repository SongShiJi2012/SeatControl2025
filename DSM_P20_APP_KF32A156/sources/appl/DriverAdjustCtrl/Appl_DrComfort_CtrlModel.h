/*
 * File: Appl_DrComfort_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_DrComfort_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 15:17:49 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_DrComfort_CtrlModel_h_
#define RTW_HEADER_Appl_DrComfort_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_DrComfort_CtrlModel_COMMON_INCLUDES_
# define Appl_DrComfort_CtrlModel_COMMON_INCLUDES_
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
#include "Srvl_NM.h"
#endif                                 /* Appl_DrComfort_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_DrComfort_CtrlModel_T
  RT_MODEL_Appl_DrComfort_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enWelcomeSts_
#define DEFINED_TYPEDEF_FOR_enWelcomeSts_

/* ����ӭ������״̬��&#10;0x00: enNULL Ĭ�ϳ�ʼ��״̬&#10;0x01:EN_BackwardStsSuccess ���Ƴɹ�&#10;0x02:EN_ForwardStsSuccessǰ�Ƴɹ�&#10;0x03:EN_BackMoveFail����ʧ��&#10;0x04:EN_ForwardMoveFailǰ��ʧ��&#10;0x05:EN_BackMovingExForWardǰ�ƴ�Ϻ���&#10;0x06:EN_ForWardMovingExBack���ƴ��ǰ��&#10;0x07:EN_ExitWelcomeFun�˳�ӭ��&#10;0x08:EN_Wel_BWOngoing������&#10;0x09:EN_Wel_FWOngoingǰ����, */
typedef enum
{
  enWelcomeSts_EN_NULL = 0,            /* Default value */
  enWelcomeSts_EN_BackwardStsSuccess,
  enWelcomeSts_EN_ForwardStsSuccess,
  enWelcomeSts_EN_BackMoveFail,
  enWelcomeSts_EN_ForwardMoveFail,
  enWelcomeSts_EN_BackMovingExForWard,
  enWelcomeSts_EN_ForWardMovingExBack,
  enWelcomeSts_EN_ExitWelcomeFun,
  enWelcomeSts_EN_Wel_BWOngoing,
  enWelcomeSts_EN_Wel_FWOngoing
}
enWelcomeSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enWelStopCause_
#define DEFINED_TYPEDEF_FOR_enWelStopCause_

/* ӭ����������ֹͣԭ��&#10;0x00: enNull Ĭ�ϳ�ʼ��״̬&#10;0x01: enIVIPrmClose �������ùر�&#10;0x02: enHallFault ��������&#10;0x03: enLockFault��ת����&#10;0x04: enRelayFault�̵�������&#10;0x05: enBusoff Busoff����&#10;0x06: enOtherMove �����ȼ������ж�&#10;0x07: enNotGearPN ��PN��&#10;0x08: enNotLearn δѧϰ&#10;0x09: enBDCDoorLost��״̬���ĵ���&#10;0x0A: enVoltageError��ѹ������&#10;0x0B: enNapMode С�ģʽ������&#10;0x0C: enBWMoveSuccess ���Ƴɹ�&#10;0x0D: enFWMoveSuccess ǰ�Ƴɹ�, */
typedef enum
{
  enWelStopCause_EN_WelStop_NULL = 0,  /* Default value */
  enWelStopCause_EN_WelStop_PRM,
  enWelStopCause_EN_WelStop_HallFault,
  enWelStopCause_EN_WelStop_RelayFault,
  enWelStopCause_EN_WelStop_LockFault,
  enWelStopCause_EN_WelStop_Busoff,
  enWelStopCause_EN_WelStop_OtherMove,
  enWelStopCause_EN_WelStop_enNotGearPN,
  enWelStopCause_EN_WelStop_enNotLearn,
  enWelStopCause_EN_WelStop_enBDCDoorLost,
  enWelStopCause_EN_WelStop_VoltageError,
  enWelStopCause_EN_WelStop_NapMode,
  enWelStopCause_EN_WelStop_enBWMoveSuccess,
  enWelStopCause_EN_WelStop_enFWMoveSuccess
}
enWelStopCause;

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

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunType_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunType_

/* ����������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����, */
typedef enum
{
  enSeatMotorRunType_EN_NULL = 0,      /* Default value */
  enSeatMotorRunType_EN_HUMEnable,
  enSeatMotorRunType_EN_ComfortEnable,
  enSeatMotorRunType_EN_MemoryEnable,
  enSeatMotorRunType_EN_ManualEnable,
  enSeatMotorRunType_EN_LearnEnable,
  enSeatMotorRunType_EN_ResetEnable,
  enSeatMotorRunType_EN_GearEnable
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

#ifndef DEFINED_TYPEDEF_FOR_enWelcomeRunSts_
#define DEFINED_TYPEDEF_FOR_enWelcomeRunSts_

/* ӭ����������״̬&#10;0x00: enNull Ĭ�ϳ�ʼ��״̬&#10;0x01: enBWMoveSuccess ���Ƴɹ�&#10;0x02: enFWMoveSuccess ǰ�Ƴɹ�&#10;0x03: enBWMoveFail ����ʧ��&#10;0x04: enFWMoveFail ǰ��ʧ��&#10;0x05: enFWBreakBW ���ƹ�����ִ��ǰ��&#10;0x06: enBWBreakFW ǰ�ƹ�����ִ�к���&#10;0x07: enBWOngoing ���ƹ�����&#10;0x08: enFWOngoing ǰ�ƹ�����&#10;0x09: enExit �˳�ӭ������, */
typedef enum
{
  enWelcomeRunSts_EN_Wel_NULL = 0,     /* Default value */
  enWelcomeRunSts_EN_Wel_BWMoveSuccess,
  enWelcomeRunSts_EN_Wel_FWMoveSuccess,
  enWelcomeRunSts_EN_Wel_BWMoveFail,
  enWelcomeRunSts_EN_Wel_FWMoveFail,
  enWelcomeRunSts_EN_Wel_FWBreakBW,
  enWelcomeRunSts_EN_Wel_BWBreakFW,
  enWelcomeRunSts_EN_Wel_BWOngoing,
  enWelcomeRunSts_EN_Wel_FWOngoing,
  enWelcomeRunSts_EN_Wel_Exit
}
enWelcomeRunSts;

#endif

/* Block signals (default storage) */
typedef struct
{
  enWelStopCause WelcomeStopReason;    /* '<S17>/Precondition_Trigger' */
  INT16U BackMoreThanHall;             /* '<S13>/Add' */
  INT16U In1;                          /* '<S17>/Precondition_Trigger' */
  INT16U In1_j;                        /* '<S17>/Precondition_Trigger' */
  INT16U WelcomeReqPosi;               /* '<S5>/WelcomeLogic' */
  INT16U WelcomeBackReqPosi;           /* '<S5>/WelcomeLogic' */
  INT16U In1_e;                        /* '<S5>/WelcomeLogic' */
  INT16U In1_k;                        /* '<S5>/WelcomeLogic' */
  INT16U In1_b;                        /* '<S5>/WelcomeLogic' */
  INT8U BackwardTriggerCondition;      /* '<S17>/Precondition_Trigger' */
  INT8U ForwardTriggerCondition;       /* '<S17>/Precondition_Trigger' */
  INT8U MtrWel_WelcomeSwitch_p;        /* '<S24>/MtrWel_WelcomeSwitch' */
  INT8U ComfortOpenMsg;                /* '<S16>/ComfortDeal' */
  INT8U in;                            /* '<S16>/ComfortDeal' */
  INT8U BackMoreThanFlg;               /* '<S13>/Chart' */
  INT8U DataTypeConversion;            /* '<S5>/Data Type Conversion' */
  INT8U WelcomeStopReasonOut;          /* '<S5>/WelcomeLogic' */
  INT8U WelcomeRunStatus;              /* '<S5>/WelcomeLogic' */
  INT8U WelcomeReqCMD;                 /* '<S5>/WelcomeLogic' */
  INT8U In1_ks;                        /* '<S5>/WelcomeLogic' */
}
B_Appl_DrComfort_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enWelcomeSts WelcomeStatus;          /* '<S5>/WelcomeLogic' */
  INT8U is_active_c7_Appl_DrComfort_CtrlModel;/* '<S17>/Precondition_Trigger' */
  INT8U is_CommonCondition;            /* '<S17>/Precondition_Trigger' */
  INT8U is_DoorSts;                    /* '<S17>/Precondition_Trigger' */
  INT8U is_BackwardTriggerCondition;   /* '<S17>/Precondition_Trigger' */
  INT8U is_ForwardTriggercondition;    /* '<S17>/Precondition_Trigger' */
  INT8U WaitTimeCnt;                   /* '<S17>/Precondition_Trigger' */
  INT8U LocalDoorSts;                  /* '<S17>/Precondition_Trigger' */
  INT8U temporalCounter_i1;            /* '<S17>/Precondition_Trigger' */
  INT8U temporalCounter_i2;            /* '<S17>/Precondition_Trigger' */
  INT8U MtrWel_LengthCmd_start;        /* '<S17>/Precondition_Trigger' */
  INT8U LocalDoorSts_start;            /* '<S17>/Precondition_Trigger' */
  INT8U is_active_c11_Appl_DrComfort_CtrlModel;/* '<S16>/ComfortDeal' */
  INT8U is_c11_Appl_DrComfort_CtrlModel;/* '<S16>/ComfortDeal' */
  INT8U is_Configurable;               /* '<S16>/ComfortDeal' */
  INT8U InitTimer;                     /* '<S16>/ComfortDeal' */
  INT8U is_active_c6_Appl_DrComfort_CtrlModel;/* '<S14>/GearDeal' */
  INT8U is_c6_Appl_DrComfort_CtrlModel;/* '<S14>/GearDeal' */
  INT8U is_active_c2_Appl_DrComfort_CtrlModel;/* '<S13>/Chart' */
  INT8U is_More;                       /* '<S13>/Chart' */
  INT8U is_active_c3_Appl_DrComfort_CtrlModel;/* '<S5>/WelcomeLogic' */
  INT8U is_c3_Appl_DrComfort_CtrlModel;/* '<S5>/WelcomeLogic' */
  INT8U is_WelcomeActive;              /* '<S5>/WelcomeLogic' */
  INT8U is_WelcomeBackward;            /* '<S5>/WelcomeLogic' */
  INT8U WelcomeFromeInitFlag;          /* '<S5>/WelcomeLogic' */
  INT8U InitTimer_h;                   /* '<S5>/WelcomeLogic' */
  INT8U BackwardTriggerCondition_start;/* '<S5>/WelcomeLogic' */
  INT8U ForwardTriggerCondition_start; /* '<S5>/WelcomeLogic' */
}
DW_Appl_DrComfort_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_DrComfort_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_DrComfort_CtrlModel_T Appl_DrComfort_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_DrComfort_CtrlModel_T Appl_DrComfort_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enWelcomeSts MtrWel_WelcomeStatus;/* '<S12>/MtrWel_WelcomeStatus'
                                          * ����ӭ������״̬
                                          */
extern enVehTypePrm MtrWel_VehiclePrm; /* '<S12>/MtrWel_VehiclePrm'
                                        * ���ͣ�C62X��C52X��
                                        */
extern enSeatMotorRunType MtrWel_CurrentMoveType;/* '<S12>/MtrWel_CurrentMoveType'
                                                  * ���ݵ����ǰ��������
                                                  */
extern enSeatAutoRunSts MtrWel_LengthAutoRunFlag;/* '<S12>/MtrWel_LengthAutoRunFlag'
                                                  * ���������Զ����б�־λ
                                                  */
extern enNapMode MtrWel_NapMode;       /* '<S12>/MtrWel_NapMode'
                                        * С�ģʽ
                                        */
extern enFinalPowerMode MtrWel_VoltMode;/* '<S12>/MtrWel_VoltMode'
                                         * ������ѹģʽ
                                         */
extern enDrAdjustEnable MtrWel_AdjustEnable;/* '<S12>/MtrWel_AdjustEnable'
                                             * �������ε���:
                                             */
extern INT16U MtrWel_BackHallPosi;     /* '<S12>/MtrWel_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
extern INT16U MtrWel_BackMotorSize;    /* '<S12>/MtrWel_BackMotorSize'
                                        * ���ݿ������쳤��
                                        */
extern INT16U MtrWel_BackStopPosi;     /* '<S12>/MtrWel_BackStopPosi'
                                        * ���ݿ���ֹ��
                                        */
extern INT16U MtrWel_LengthBWTargetPosi;/* '<S12>/MtrWel_LengthBWTargetPosi'
                                         * �����������Ŀ��λ��
                                         */
extern INT16U MtrWel_LengthFWTargetPosi;/* '<S12>/MtrWel_LengthFWTargetPosi'
                                         * ��������ǰ��Ŀ��λ��
                                         */
extern INT16U MtrWel_LengthHallPosi;   /* '<S12>/MtrWel_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
extern INT16U MtrWel_LengthStopPosi;   /* '<S12>/MtrWel_LengthStopPosi'
                                        * ��������ֹ��
                                        */
extern INT8U MtrWel_0x238_GearLostFlag;/* '<S12>/MtrWel_0x238_GearLostFlag'
                                        * 0x238���ĵ��߱�־λ
                                        */
extern INT8U MtrWel_0x238_TCU_GearSelDisp;/* '<S12>/MtrWel_0x238_TCU_GearSelDisp'
                                           * ��λ״̬
                                           */
extern INT8U MtrWel_0x26E_GearSelLostFlag;/* '<S12>/MtrWel_0x26E_GearSelLostFlag'
                                           * 0x26E���ĵ��߱�־λ
                                           */
extern INT8U MtrWel_0x26E_VCU_GearSelDisp;/* '<S12>/MtrWel_0x26E_VCU_GearSelDisp'
                                           * ��λ״̬
                                           */
extern INT8U MtrWel_0x28E_BDCLostFlag; /* '<S12>/MtrWel_0x28E_BDCLostFlag'
                                        * 0x281���ĵ��߱�־λ
                                        */
extern INT8U MtrWel_0x351_IVI_St_FLSeatmeet;/* '<S12>/MtrWel_0x351_IVI_St_FLSeatmeet'
                                             * ����ӭ��ʹ��
                                             */
extern INT8U MtrWel_BDC_FLDoorSts;     /* '<S12>/MtrWel_BDC_FLDoorSts'
                                        * ��ǰ��״̬
                                        */
extern INT8U MtrWel_BackHallFaultSts;  /* '<S12>/MtrWel_BackHallFaultSts'
                                        * ������������
                                        */
extern INT8U MtrWel_BackLockSts;       /* '<S12>/MtrWel_BackLockSts'
                                        * ���ݿ�����ת״̬
                                        */
extern INT8U MtrWel_BackRelayFaultSts; /* '<S12>/MtrWel_BackRelayFaultSts'
                                        * �����̵���ճ��
                                        */
extern INT8U MtrWel_BusoffFlag;        /* '<S12>/MtrWel_BusoffFlag'
                                        * ����busoff��־λ
                                        */
extern INT8U MtrWel_GetRecoverDefaultFlag;/* '<S12>/MtrWel_GetRecoverDefaultFlag'
                                           * �ָ���������
                                           */
extern INT8U MtrWel_LengthCmd;         /* '<S12>/MtrWel_LengthCmd'
                                        * ����������
                                        */
extern INT8U MtrWel_LengthHallFaultSts;/* '<S12>/MtrWel_LengthHallFaultSts'
                                        * �����������
                                        */
extern INT8U MtrWel_LengthLockSts;     /* '<S12>/MtrWel_LengthLockSts'
                                        * ���������ת״̬
                                        */
extern INT8U MtrWel_LengthRelayFaultSts;/* '<S12>/MtrWel_LengthRelayFaultSts'
                                         * ����̵���ճ��
                                         */
extern INT8U MtrWel_P20_PHEV_EngineCfg;/* '<S12>/MtrWel_P20_PHEV_EngineCfg'
                                        * ����P20PHEV������ʹ������
                                        */
extern INT8U MtrWel_UpdatePosiFlag;    /* '<S12>/MtrWel_UpdatePosiFlag'
                                        * ����ӭ��λ�ø��±�־
                                        */
extern INT8U MtrWel_VoltSatisfy;       /* '<S12>/MtrWel_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */
extern INT8U MtrWel_WelcomeEnable;     /* '<S12>/MtrWel_WelcomeEnable'
                                        * ����ӭ��ʹ��״̬
                                        */
extern INT8U MtrWel_WelcomeSwitch;     /* '<S12>/MtrWel_WelcomeSwitch'
                                        * ����ӭ������״̬
                                        */

/* Model entry point functions */
extern void Appl_DrComfort_CtrlModel_initialize(void);
extern void Appl_DrComfort_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_DrComfort_CtrlModel_T *const Appl_DrComfort_CtrlModel_M;

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
 * '<Root>' : 'Appl_DrComfort_CtrlModel'
 * '<S1>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_DrComfort_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_DrComfort_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_DrComfort_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic'
 * '<S7>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeBWTargertPosi'
 * '<S8>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeFWTargertPosi'
 * '<S9>'   : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeStatus'
 * '<S10>'  : 'Appl_DrComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeUpdatePosiFlag'
 * '<S11>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S12>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/RTE'
 * '<S13>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/BackHallChek '
 * '<S14>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/GearMessageDeal'
 * '<S15>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/IntelligentPowerDown'
 * '<S16>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM'
 * '<S17>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition_Trigger'
 * '<S18>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/BackHallChek /Chart'
 * '<S19>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/GearMessageDeal/GearDeal'
 * '<S20>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/IntelligentPowerDown/IntelligentPowerDownDeal'
 * '<S21>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM/ComfortDeal'
 * '<S22>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM/ComfortDeal/SetComfortPrm'
 * '<S23>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition_Trigger/Precondition_Trigger'
 * '<S24>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition_Trigger/Precondition_Trigger/Get_DoorSts'
 * '<S25>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition_Trigger/Precondition_Trigger/Set_DoorSts'
 * '<S26>'  : 'Appl_DrComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition_Trigger/Precondition_Trigger/Set_WelcomeUpdatePosiFlag'
 */
#endif                                 /* RTW_HEADER_Appl_DrComfort_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
