/*
 * File: Appl_PaComfort_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_PaComfort_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 15:19:39 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaComfort_CtrlModel_h_
#define RTW_HEADER_Appl_PaComfort_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_PaComfort_CtrlModel_COMMON_INCLUDES_
# define Appl_PaComfort_CtrlModel_COMMON_INCLUDES_
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
#include "Srvl_NM.h"
#endif                                 /* Appl_PaComfort_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_PaComfort_CtrlModel_T
  RT_MODEL_Appl_PaComfort_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enWelcomeSts_
#define DEFINED_TYPEDEF_FOR_enWelcomeSts_

/* ����ӭ������״̬��&#10;0x00: enNULL Ĭ�ϳ�ʼ��״̬&#10;0x01: enBackwardSts ����״̬&#10;0x02: enForwardSts ǰ��״̬, */
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

/* ӭ����������ֹͣԭ��&#10;0x00: enNull Ĭ�ϳ�ʼ��״̬&#10;0x01: enIVIPrmClose �������ùر�&#10;0x02: enHallFault ��������&#10;0x03: enLockFault��ת����&#10;0x04: enRelayFault�̵�������&#10;0x05: enBusoff Busoff����&#10;0x06: enOtherMove �����ȼ������ж�&#10;0x07: enNotGearPN ��PN��&#10;0x08: enNotLearn δѧϰ&#10;0x09: enBDCDoorLost��״̬���ĵ���&#10;0x0A: enVoltageError��ѹ������&#10;0x0B: enLengthMoveFaild �����ƶ�����ʧ��&#10;0x0C: enBWMoveSuccess ���Ƴɹ�&#10;0x0D: enFWMoveSuccess ǰ�Ƴɹ�, */
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
  enWelStopCause_EN_WelStop_LengthMoveFaild,
  enWelStopCause_EN_WelStop_enBWMoveSuccess,
  enWelStopCause_EN_WelStop_enFWMoveSuccess
}
enWelStopCause;

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
  enWelStopCause WelcomeStopReason;    /* '<S15>/Precondition' */
  INT16U BackMoreThanHall;             /* '<S13>/Add' */
  INT16U In1;                          /* '<S15>/Precondition' */
  INT16U WelcomeReqPosi;               /* '<S5>/WelcomeLogic' */
  INT16U WelcomeBackReqPosi;           /* '<S5>/WelcomeLogic' */
  INT16U In1_d;                        /* '<S5>/WelcomeLogic' */
  INT16U In1_p;                        /* '<S5>/WelcomeLogic' */
  INT16U In1_e;                        /* '<S5>/WelcomeLogic' */
  INT8U BackwardTriggerCondition;      /* '<S15>/Precondition' */
  INT8U ForwardTriggerCondition;       /* '<S15>/Precondition' */
  INT8U In1_l;                         /* '<S15>/Precondition' */
  INT8U MtrWel_WelcomeSwitch;          /* '<S20>/MtrWel_WelcomeSwitch' */
  INT8U ComfortOpenMsg;                /* '<S14>/ComfortDeal' */
  INT8U in;                            /* '<S14>/ComfortDeal' */
  INT8U BackMoreThanFlg;               /* '<S13>/Chart' */
  INT8U DataTypeConversion;            /* '<S5>/Data Type Conversion' */
  INT8U WelcomeStopReasonOut;          /* '<S5>/WelcomeLogic' */
  INT8U WelcomeRunStatus;              /* '<S5>/WelcomeLogic' */
  INT8U WelcomeReqCMD;                 /* '<S5>/WelcomeLogic' */
  INT8U In1_h;                         /* '<S5>/WelcomeLogic' */
}
B_Appl_PaComfort_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enWelcomeSts WelcomeStatus;          /* '<S5>/WelcomeLogic' */
  INT8U is_active_c7_Appl_PaComfort_CtrlModel;/* '<S15>/Precondition' */
  INT8U is_CommonCondition;            /* '<S15>/Precondition' */
  INT8U is_DoorSts;                    /* '<S15>/Precondition' */
  INT8U is_BackwardTriggerCondition;   /* '<S15>/Precondition' */
  INT8U is_ForwardTriggercondition;    /* '<S15>/Precondition' */
  INT8U LocalDoorSts;                  /* '<S15>/Precondition' */
  INT8U WaitTimeCnt;                   /* '<S15>/Precondition' */
  INT8U temporalCounter_i1;            /* '<S15>/Precondition' */
  INT8U temporalCounter_i2;            /* '<S15>/Precondition' */
  INT8U LocalDoorSts_start;            /* '<S15>/Precondition' */
  INT8U MtrPAWel_LengthCmd_start;      /* '<S15>/Precondition' */
  INT8U is_active_c11_Appl_PaComfort_CtrlModel;/* '<S14>/ComfortDeal' */
  INT8U is_c11_Appl_PaComfort_CtrlModel;/* '<S14>/ComfortDeal' */
  INT8U is_Configurable;               /* '<S14>/ComfortDeal' */
  INT8U InitTimer;                     /* '<S14>/ComfortDeal' */
  INT8U is_active_c2_Appl_PaComfort_CtrlModel;/* '<S13>/Chart' */
  INT8U is_More;                       /* '<S13>/Chart' */
  INT8U is_active_c3_Appl_PaComfort_CtrlModel;/* '<S5>/WelcomeLogic' */
  INT8U is_c3_Appl_PaComfort_CtrlModel;/* '<S5>/WelcomeLogic' */
  INT8U is_WelcomeActive;              /* '<S5>/WelcomeLogic' */
  INT8U is_WelcomeBackward;            /* '<S5>/WelcomeLogic' */
  INT8U WelcomeFromeInitFlag;          /* '<S5>/WelcomeLogic' */
  INT8U InitTimer_n;                   /* '<S5>/WelcomeLogic' */
  INT8U BackwardTriggerCondition_start;/* '<S5>/WelcomeLogic' */
  INT8U ForwardTriggerCondition_start; /* '<S5>/WelcomeLogic' */
}
DW_Appl_PaComfort_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_PaComfort_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_PaComfort_CtrlModel_T Appl_PaComfort_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_PaComfort_CtrlModel_T Appl_PaComfort_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enWelcomeSts MtrPAWel_WelcomeStatus;/* '<S12>/MtrPAWel_WelcomeStatus'
                                            * ����ӭ��״̬��&#10;0x00: enNULL Ĭ�ϳ�ʼ��״̬&#10;0x01: enBackwardSts ����״̬&#10;0x02: enForwardSts ǰ��״̬
                                            */
extern enVehTypePrm MtrPAWel_VehiclePrm;/* '<S12>/MtrPAWel_VehiclePrm'
                                         * ���ͣ�C62X��C52X��&#10; 0��P20����&#10; 1��BM400����
                                         */
extern enSeatMotorRunType MtrPAWel_CurrentMoveType;/* '<S12>/MtrPAWel_CurrentMoveType'
                                                    * ���ݵ����ǰ�������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����
                                                    */
extern enSeatAutoRunSts MtrPAWel_LengthAutoRunFlag;/* '<S12>/MtrPAWel_LengthAutoRunFlag'
                                                    * ���������Զ����б�־λ
                                                    */
extern enFinalPowerMode MtrPAWel_VoltMode;/* '<S12>/MtrPAWel_VoltMode'
                                           * ������ѹģʽ&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                           */
extern INT16U MtrPAWel_BackHallPosi;   /* '<S12>/MtrPAWel_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
extern INT16U MtrPAWel_BackMotorSize;  /* '<S12>/MtrPAWel_BackMotorSize'
                                        * ���ݿ������쳤��
                                        */
extern INT16U MtrPAWel_BackStopPosi;   /* '<S12>/MtrPAWel_BackStopPosi'
                                        * ���ݿ���ֹ��
                                        */
extern INT16U MtrPAWel_LengthBWTargetPosi;/* '<S12>/MtrPAWel_LengthBWTargetPosi'
                                           * �����������Ŀ��λ��
                                           */
extern INT16U MtrPAWel_LengthFWTargetPosi;/* '<S12>/MtrPAWel_LengthFWTargetPosi'
                                           * ��������ǰ��Ŀ��λ��
                                           */
extern INT16U MtrPAWel_LengthHallPosi; /* '<S12>/MtrPAWel_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
extern INT16U MtrPAWel_LengthStopPosi; /* '<S12>/MtrPAWel_LengthStopPosi'
                                        * ��������ֹ��
                                        */
extern INT8U MtrPAWel_0x28E_BDCLostFlag;/* '<S12>/MtrPAWel_0x28E_BDCLostFlag'
                                         * 0x28E���ĵ��߱�־λ&#10;0x0:����&#10;0x1:����
                                         */
extern INT8U MtrPAWel_0x351_IVI_St_FRSeatmeet;/* '<S12>/MtrPAWel_0x351_IVI_St_FRSeatmeet'
                                               * ����ӭ��ʹ��&#10;0x0:Inactive��&#10;0x1:Open&#10;0x2:Close&#10;0x3:Reserved
                                               */
extern INT8U MtrPAWel_AdjustEnable;    /* '<S12>/MtrPAWel_AdjustEnable'
                                        * �������ε���:&#10;0x00:manual&#10;0x01:Four way motor
                                        */
extern INT8U MtrPAWel_BDC_FRDoorSts;   /* '<S12>/MtrPAWel_BDC_FRDoorSts'
                                        * ��ǰ��״̬&#10;0x0:Close&#10;0x1:Open
                                        */
extern INT8U MtrPAWel_BackHallFaultSts;/* '<S12>/MtrPAWel_BackHallFaultSts'
                                        * ���ݿ�����������&#10;0���޹���&#10;1���й���
                                        */
extern INT8U MtrPAWel_BackLockSts;     /* '<S12>/MtrPAWel_BackLockSts'
                                        * ���ݿ�����ת״̬&#10;0����&#10;1����
                                        */
extern INT8U MtrPAWel_BackRelayFaultSts;/* '<S12>/MtrPAWel_BackRelayFaultSts'
                                         * ���ݿ����̵���ճ��&#10;0���޹��ϣ�&#10;1��D_Relay_UpFrontFault��ǰճ�����ϣ�&#10;2��D_Relay_DownBackFault�º�ճ�����ϣ�
                                         */
extern INT8U MtrPAWel_BusoffFlag;      /* '<S12>/MtrPAWel_BusoffFlag'
                                        * ����busoff��־λ&#10;0��������&#10;1��busoff����
                                        */
extern INT8U MtrPAWel_GearPNFlag;      /* '<S12>/MtrPAWel_GearPNFlag'
                                        * �Ƿ���P/N����&#10;0��No&#10;1��Yes
                                        */
extern INT8U MtrPAWel_GetRecoverDefaultFlag;/* '<S12>/MtrPAWel_GetRecoverDefaultFlag'
                                             * �ָ���������&#10;0���ǻָ�������&#10;1���ָ��������ã�
                                             */
extern INT8U MtrPAWel_LengthCmd;       /* '<S12>/MtrPAWel_LengthCmd'
                                        * ��������������:&#10;0:��&#10;1����ǰ&#10;2�����
                                        */
extern INT8U MtrPAWel_LengthHallFaultSts;/* '<S12>/MtrPAWel_LengthHallFaultSts'
                                          * ������������������&#10;0����&#10;1����
                                          */
extern INT8U MtrPAWel_LengthLockSts;   /* '<S12>/MtrPAWel_LengthLockSts'
                                        * ���������ת״̬&#10;0����&#10;1����
                                        */
extern INT8U MtrPAWel_LengthRelayFaultSts;/* '<S12>/MtrPAWel_LengthRelayFaultSts'
                                           * ��������̵���ճ�����ϱ�־&#10;0���޹���&#10;1���й���
                                           */
extern INT8U MtrPAWel_UpdatePosiFlag;  /* '<S12>/MtrPAWel_UpdatePosiFlag'
                                        * ����ӭ��λ�ø��±�־:&#10; 0��������&#10; 1������
                                        */
extern INT8U MtrPAWel_VoltSatisfy;     /* '<S12>/MtrPAWel_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ����㣺&#10;0��������&#10;1������
                                        */
extern INT8U MtrPAWel_WelcomeEnable;   /* '<S12>/MtrPAWel_WelcomeEnable'
                                        * ����ӭ��ʹ��״̬:&#10;0������&#10;1��ʹ��
                                        */
extern INT8U MtrPAWel_WelcomeSwitch;   /* '<S12>/MtrPAWel_WelcomeSwitch'
                                        * ����ӭ������״̬:&#10;0���ر�&#10;1������
                                        */

/* Model entry point functions */
extern void Appl_PaComfort_CtrlModel_initialize(void);
extern void Appl_PaComfort_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_PaComfort_CtrlModel_T *const Appl_PaComfort_CtrlModel_M;

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
 * '<Root>' : 'Appl_PaComfort_CtrlModel'
 * '<S1>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_PaComfort_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_PaComfort_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_PaComfort_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic'
 * '<S7>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeBWTargertPosi'
 * '<S8>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeFWTargertPosi'
 * '<S9>'   : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeStatus'
 * '<S10>'  : 'Appl_PaComfort_CtrlModel/LogicCtrl/LocalAdjustCtrl/WelcomeLogic/Set_WelcomeUpdatePosiFlag'
 * '<S11>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S12>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/RTE'
 * '<S13>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/BackHallChek '
 * '<S14>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM'
 * '<S15>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition'
 * '<S16>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/BackHallChek /Chart'
 * '<S17>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM/ComfortDeal'
 * '<S18>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePRM/ComfortDeal/SetComfortPrm'
 * '<S19>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition/Precondition'
 * '<S20>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition/Precondition/Get_DoorSts'
 * '<S21>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition/Precondition/Set_DoorSts'
 * '<S22>'  : 'Appl_PaComfort_CtrlModel/UpDataInputInfo/InputSignalProcess/WelcomePrecondition/Precondition/Set_WelcomeUpdatePosiFlag'
 */
#endif                                 /* RTW_HEADER_Appl_PaComfort_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
