/*
 * File: Appl_DrRestMode_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_DrRestMode_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Jul  7 18:16:20 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_DrRestMode_CtrlModel_h_
#define RTW_HEADER_Appl_DrRestMode_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_DrRestMode_CtrlModel_COMMON_INCLUDES_
# define Appl_DrRestMode_CtrlModel_COMMON_INCLUDES_
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
#include "Ecual_lin.h"
#include "Appl_DtcSetConditionCheck.h"
#include "ecual_pins.h"
#include "Srvl_NM.h"
#include "Srvl_Tle9210x.h"
#endif                                 /* Appl_DrRestMode_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_DrRestMode_CtrlModel_T
  RT_MODEL_Appl_DrRestMode_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enSeatAutoRunSts_
#define DEFINED_TYPEDEF_FOR_enSeatAutoRunSts_

/* ���ε����˶�״̬��,0��Invalid,1��Running,2��Success,3��Fail, */
typedef enum
{
  enSeatAutoRunSts_EN_SEAT_INVALID = 0,/* Default value */
  enSeatAutoRunSts_EN_SEAT_RUNNING,
  enSeatAutoRunSts_EN_SEAT_SUCCESS,
  enSeatAutoRunSts_EN_SEAT_FAIL
}
enSeatAutoRunSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunType_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunType_

/* ����������ͣ�,0���޶�����,1��HUM��,2�����ʣ�,3��������ã�,4���ֶ����ڣ�,5��ѧϰ����, */
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
  enSeatMotorRunType_EN_ResEnable
}
enSeatMotorRunType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMassageMode_DSM_
#define DEFINED_TYPEDEF_FOR_enMassageMode_DSM_

/* DSM����ģʽ/��Ħģ�鷴��ģʽ:,0x0:Mode1ȫ�����,0x1:Mode2ȫ����,0x2:Mode3�粿����,0x3:Mode4�粿����,0x4:Mode5��������,0x5:Mode6��������,0x6:Mode7��������,0x7:Mode8��������,0x8:����ģʽ, */
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

#ifndef DEFINED_TYPEDEF_FOR_enPowerModeSts_
#define DEFINED_TYPEDEF_FOR_enPowerModeSts_

/* ��Դ��λ״̬,0 : OFF,1 : ACC,2 : ON,3 : CRANK, */
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

/* ��ѹģʽ:,0 : StopVolt,1 : LowVolt,2 : NormalVolt,3 : HighVolt,4 : OverVolt, */
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

#ifndef DEFINED_TYPEDEF_FOR_enAdjustEnable_
#define DEFINED_TYPEDEF_FOR_enAdjustEnable_

/* ���ε��õ������ã�,0x00:manual ,0x01:Six way motor ,0x02:Twelve way motor,, */
typedef enum
{
  enAdjustEnable_EN_Manual = 0,        /* Default value */
  enAdjustEnable_EN_SixWayMotor,
  enAdjustEnable_EN_TwelveWayMotor
}
enAdjustEnable;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enResCallRet_
#define DEFINED_TYPEDEF_FOR_enResCallRet_

/* ���ε����˶�״̬��,0��Init ��ʼ״̬,1��Fail,2��Success,, */
typedef enum
{
  enResCallRet_EN_Init = 0,            /* Default value */
  enResCallRet_EN_Fail,
  enResCallRet_EN_Success
}
enResCallRet;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enNapMode_
#define DEFINED_TYPEDEF_FOR_enNapMode_

/* С�ģʽ,0x0:Inactive,0x1:�ر�С�ģʽ,0x2:��С�ģʽ,0x3:ERROR, */
typedef enum
{
  enNapMode_EN_NapMode_NULL = 0,       /* Default value */
  enNapMode_EN_NapMode_Close,
  enNapMode_EN_NapMode_Open,
  enNapMode_EN_NapMode_ERR
}
enNapMode;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMassageLevel_DSM_
#define DEFINED_TYPEDEF_FOR_enMassageLevel_DSM_

/* DSM����λ����Ħģ�鷴����λ:,0x0:OFF,0x1:Level1,0x2:Level2,0x3:Level3,0x4:AUTO  OFF�Զ��ر�, */
typedef enum
{
  enMassageLevel_DSM_EN_OFF = 0,       /* Default value */
  enMassageLevel_DSM_EN_L1,
  enMassageLevel_DSM_EN_L2,
  enMassageLevel_DSM_EN_L3,
  enMassageLevel_DSM_EN_AUTO_OFF
}
enMassageLevel_DSM;

#endif

/* Block signals (default storage) */
typedef struct
{
  INT16U Add;                          /* '<S24>/Add' */
  INT16U CallHallVall_Length;          /* '<S17>/Char_CallHallVall_Length' */
  INT16U ResCallPosi_Height;           /* '<S5>/ResDeal' */
  INT16U ResCallPosi_Length;           /* '<S5>/ResDeal' */
  INT16U ResCallPosi_Front;            /* '<S5>/ResDeal' */
  INT16U ResCallPosi_Back;             /* '<S5>/ResDeal' */
  INT16U ResReCallPosi_Back;           /* '<S5>/ResDeal' */
  INT16U ResReCallPosi_Front;          /* '<S5>/ResDeal' */
  INT16U ResReCallPosi_Height;         /* '<S5>/ResDeal' */
  INT16U ResReCallPosi_Length;         /* '<S5>/ResDeal' */
  INT16U In1;                          /* '<S5>/ResDeal' */
  INT16U ln2;                          /* '<S5>/ResDeal' */
  INT16U In3;                          /* '<S5>/ResDeal' */
  INT16U ln4;                          /* '<S5>/ResDeal' */
  INT16U In1_h;                        /* '<S5>/ResDeal' */
  INT16U ln2_b;                        /* '<S5>/ResDeal' */
  INT16U In3_e;                        /* '<S5>/ResDeal' */
  INT16U ln4_i;                        /* '<S5>/ResDeal' */
  INT8U Stop_Flag;                     /* '<S30>/Stop_Flag' */
  INT8U Stop_Flag_Reason;              /* '<S30>/Stop_Flag' */
  INT8U Open_Flag;                     /* '<S29>/Open_Flag' */
  INT8U Open_Flag_Reason;              /* '<S29>/Open_Flag' */
  INT8U MotroFault_Flag;               /* '<S28>/MotorFault_Flag' */
  INT8U MassageFault_Flag;             /* '<S27>/MassageFault_Flag' */
  INT8U Close_Flag;                    /* '<S25>/Colse_Flag' */
  INT8U Close_Flag_Reason;             /* '<S25>/Colse_Flag' */
  INT8U CallRet;                       /* '<S16>/GetCallRet' */
  INT8U CC4_Flag;                      /* '<S15>/CC4_Flag' */
  INT8U CC4_Reason;                    /* '<S15>/CC4_Flag' */
  INT8U CC3_Flag;                      /* '<S14>/CC3_Flag' */
  INT8U CC3_Reason;                    /* '<S14>/CC3_Flag' */
  INT8U CC2_Flag;                      /* '<S13>/CC2_Flag' */
  INT8U CC2_Reason;                    /* '<S13>/CC2_Flag' */
  INT8U CC1_Flag;                      /* '<S12>/CC1_Flag' */
  INT8U CC1_Reason;                    /* '<S12>/CC1_Flag' */
  INT8U Stop_Flag_f;                   /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U Stop_Flag_Reason_o;            /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U Open_Flag_e;                   /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U Open_Flag_Reason_b;            /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U Close_Flag_f;                  /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U Close_Flag_Reason_h;           /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U MotorFault_Flag;               /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U MassageFault_Flag_l;           /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U DrRestCAll_Ret;                /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC1_Flag_m;                    /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC1_Reason_m;                  /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC2_Flag_m;                    /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC2_Reason_b;                  /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC3_Flag_b;                    /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC3_Reason_n;                  /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC4_Flag_g;                    /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U CC4_Reason_p;                  /* '<S1>/BusConversion_InsertedFor_ResOut_at_inport_0' */
  INT8U DSM_MassageLevel_Req;          /* '<S5>/ResDeal' */
  INT8U DSM_MassageMode_Req;           /* '<S5>/ResDeal' */
  INT8U DSM_NapMode_FB;                /* '<S5>/ResDeal' */
  INT8U State_ResDeal;                 /* '<S5>/ResDeal' */
}
B_Appl_DrRestMode_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT32U Temp_Drs_Distance;            /* '<S17>/Char_CallHallVall_Length' */
  enSeatMotorRunType DrRes_CurrentMoveType_start;/* '<S16>/GetCallRet' */
  enSeatMotorRunType DrRes_CurrentMoveType_start_m;/* '<S5>/ResDeal' */
  INT16U TempCallPosi_Height;          /* '<S5>/ResDeal' */
  INT16U TempCallPosi_Length;          /* '<S5>/ResDeal' */
  INT16U TempCallPosi_Back;            /* '<S5>/ResDeal' */
  INT16U TempCallPosi_Front;           /* '<S5>/ResDeal' */
  INT8U is_active_c4_Appl_DrRestMode_CtrlModel;/* '<S30>/Stop_Flag' */
  INT8U is_c4_Appl_DrRestMode_CtrlModel;/* '<S30>/Stop_Flag' */
  INT8U is_active_c14_Appl_DrRestMode_CtrlModel;/* '<S29>/Open_Flag' */
  INT8U is_c14_Appl_DrRestMode_CtrlModel;/* '<S29>/Open_Flag' */
  INT8U RequestTimer;                  /* '<S29>/Open_Flag' */
  INT8U is_active_c16_Appl_DrRestMode_CtrlModel;/* '<S28>/MotorFault_Flag' */
  INT8U is_c16_Appl_DrRestMode_CtrlModel;/* '<S28>/MotorFault_Flag' */
  INT8U is_active_c17_Appl_DrRestMode_CtrlModel;/* '<S27>/MassageFault_Flag' */
  INT8U is_c17_Appl_DrRestMode_CtrlModel;/* '<S27>/MassageFault_Flag' */
  INT8U is_active_c15_Appl_DrRestMode_CtrlModel;/* '<S25>/Colse_Flag' */
  INT8U is_c15_Appl_DrRestMode_CtrlModel;/* '<S25>/Colse_Flag' */
  INT8U is_Init;                       /* '<S25>/Colse_Flag' */
  INT8U RequestTimer_h;                /* '<S25>/Colse_Flag' */
  INT8U is_active_c5_Appl_DrRestMode_CtrlModel;/* '<S17>/Char_CallHallVall_Length' */
  INT8U is_active_c2_Appl_DrRestMode_CtrlModel;/* '<S16>/GetCallRet' */
  INT8U is_c2_Appl_DrRestMode_CtrlModel;/* '<S16>/GetCallRet' */
  INT8U is_active_c7_Appl_DrRestMode_CtrlModel;/* '<S15>/CC4_Flag' */
  INT8U is_c7_Appl_DrRestMode_CtrlModel;/* '<S15>/CC4_Flag' */
  INT8U is_active_c1_Appl_DrRestMode_CtrlModel;/* '<S14>/CC3_Flag' */
  INT8U is_c1_Appl_DrRestMode_CtrlModel;/* '<S14>/CC3_Flag' */
  INT8U is_active_c6_Appl_DrRestMode_CtrlModel;/* '<S13>/CC2_Flag' */
  INT8U is_c6_Appl_DrRestMode_CtrlModel;/* '<S13>/CC2_Flag' */
  INT8U is_active_c11_Appl_DrRestMode_CtrlModel;/* '<S12>/CC1_Flag' */
  INT8U is_c11_Appl_DrRestMode_CtrlModel;/* '<S12>/CC1_Flag' */
  INT8U is_active_c8_Appl_DrRestMode_CtrlModel;/* '<S5>/ResDeal' */
  INT8U is_c8_Appl_DrRestMode_CtrlModel;/* '<S5>/ResDeal' */
  INT8U is_Inactive;                   /* '<S5>/ResDeal' */
  INT8U is_Active;                     /* '<S5>/ResDeal' */
  INT8U WaitTimer;                     /* '<S5>/ResDeal' */
  INT8U SaveReTimer;                   /* '<S5>/ResDeal' */
  INT8U StartFlag;                     /* '<S5>/ResDeal' */
  INT8U SavePosiCnt;                   /* '<S5>/ResDeal' */
  INT8U OpenToStop_Flag;               /* '<S5>/ResDeal' */
}
DW_Appl_DrRestMode_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_DrRestMode_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_DrRestMode_CtrlModel_T Appl_DrRestMode_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_DrRestMode_CtrlModel_T Appl_DrRestMode_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMotorRunType DrRes_CurrentMoveType;/* '<S11>/DrRes_CurrentMoveType'
                                                 * ���ݵ����ǰ��������
                                                 */
extern enSeatAutoRunSts DrRes_BackAutoRunFlag;/* '<S11>/DrRes_BackAutoRunFlag'
                                               * ���ݿ����Զ�����״̬
                                               */
extern enSeatAutoRunSts DrRes_FrontAutoRunFlag;/* '<S11>/DrRes_FrontAutoRunFlag'
                                                * ����ǰ���Ƕ��Զ�����״̬
                                                */
extern enSeatAutoRunSts DrRes_HeightAutoRunFlag;/* '<S11>/DrRes_HeightAutoRunFlag'
                                                 * ���ݸ߶��Զ�����״̬
                                                 */
extern enSeatAutoRunSts DrRes_LengthAutoRunFlag;/* '<S11>/DrRes_LengthAutoRunFlag'
                                                 * ���������Զ�����״̬
                                                 */
extern enPowerModeSts DrRes_PowerMode; /* '<S11>/DrRes_PowerMode'
                                        * ������Դģʽ
                                        */
extern enMassageMode_DSM DrRes_MassageMode_FB;/* '<S11>/DrRes_MassageMode_FB'
                                               * ��Ħģʽ����-LIN���ź�
                                               */
extern enFinalPowerMode DrRes_VoltMode;/* '<S11>/DrRes_VoltMode'
                                        * ������ѹģʽ
                                        */
extern INT16U DrRes_BackDefaultMotorSize;/* '<S11>/DrRes_BackDefaultMotorSize'
                                          * �����������
                                          */
extern INT16U DrRes_BackDefaultStopPos;/* '<S11>/DrRes_BackDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
extern INT16U DrRes_BackHallPosi;      /* '<S11>/DrRes_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
extern INT16U DrRes_FrontDefaulMotorSize;/* '<S11>/DrRes_FrontDefaulMotorSize'
                                          * ���й������
                                          */
extern INT16U DrRes_FrontDefaulStoptPos;/* '<S11>/DrRes_FrontDefaulStoptPos'
                                         * ����Ӳֹ��
                                         */
extern INT16U DrRes_FrontHallPosi;     /* '<S11>/DrRes_FrontHallPosi'
                                        * ����ǰ���Ƕȵ�ǰ����λ��
                                        */
extern INT16U DrRes_HeightDefaultMotorSize;/* '<S11>/DrRes_HeightDefaultMotorSize'
                                            * �߶ȹ������
                                            */
extern INT16U DrRes_HeightDefaultStopPos;/* '<S11>/DrRes_HeightDefaultStopPos'
                                          * �߶�Ӳֹ��
                                          */
extern INT16U DrRes_HeightHallPosi;    /* '<S11>/DrRes_HeightHallPosi'
                                        * ���ݸ߶ȵ�ǰ����λ��
                                        */
extern INT16U DrRes_LengthDefaultMotorSize;/* '<S11>/DrRes_LengthDefaultMotorSize'
                                            * ����������
                                            */
extern INT16U DrRes_LengthDefaultStopPos;/* '<S11>/DrRes_LengthDefaultStopPos'
                                          * ����Ӳֹ��
                                          */
extern INT16U DrRes_LengthHallPosi;    /* '<S11>/DrRes_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
extern INT16U DrResl_ReCallPosi_Back;  /* '<S11>/DrResl_ReCallPosi_Back'
                                        * ����С��λλ��-����
                                        */
extern INT16U DrResl_ReCallPosi_Front; /* '<S11>/DrResl_ReCallPosi_Front'
                                        * ����С��λλ��-����
                                        */
extern INT16U DrResl_ReCallPosi_Height;/* '<S11>/DrResl_ReCallPosi_Height'
                                        * ����С��λλ��-�߶�
                                        */
extern INT16U DrResl_ReCallPosi_Length;/* '<S11>/DrResl_ReCallPosi_Length'
                                        * ����С��λλ��-����
                                        */
extern INT8U DrRes_AdjustEnable;       /* '<S11>/DrRes_AdjustEnable'
                                        * �������ε���
                                        */
extern INT8U DrRes_AnyoneHallFaultSts; /* '<S11>/DrRes_AnyoneHallFaultSts'
                                        * ������һ����������ϱ�־λ
                                        */
extern INT8U DrRes_AnyoneRelayFaultSts;/* '<S11>/DrRes_AnyoneRelayFaultSts'
                                        * ��һ�̵���ճ�����ϱ�־
                                        */
extern INT8U DrRes_BackLockFault;      /* '<S11>/DrRes_BackLockFault'
                                        * �������ο�����ת��־λ
                                        */
extern INT8U DrRes_DescBackHallFault;  /* '<S11>/DrRes_DescBackHallFault'
                                        * ��������������ϱ�־λ
                                        */
extern INT8U DrRes_DescFrontHallFault; /* '<S11>/DrRes_DescFrontHallFault'
                                        * ���е���������ϱ�־λ
                                        */
extern INT8U DrRes_DescHeightHallFault;/* '<S11>/DrRes_DescHeightHallFault'
                                        * �߶ȵ���������ϱ�־λ
                                        */
extern INT8U DrRes_DescLengthHallFault;/* '<S11>/DrRes_DescLengthHallFault'
                                        * �������������ϱ�־λ
                                        */
extern INT8U DrRes_EngineRunFlag;      /* '<S11>/DrRes_EngineRunFlag'
                                        * ����������״̬
                                        */
extern INT8U DrRes_FrontLockFault;     /* '<S11>/DrRes_FrontLockFault'
                                        * �����������ж�ת��־λ
                                        */
extern INT8U DrRes_HeightLockFault;    /* '<S11>/DrRes_HeightLockFault'
                                        * �������θ߶ȶ�ת��־λ
                                        */
extern INT8U DrRes_IVI_NapMode_SwtichSet;/* '<S11>/DrRes_IVI_NapMode_SwtichSet'
                                          * �ģʽ�������趨
                                          */
extern INT8U DrRes_LengthLockFault;    /* '<S11>/DrRes_LengthLockFault'
                                        * �������������ת��־λ
                                        */
extern INT8U DrRes_SeatLearnResult;    /* '<S11>/DrRes_SeatLearnResult'
                                        * ��������ѧϰ״̬��־λ
                                        */
extern INT8U DrRes_SeatMassageCfg;     /* '<S11>/DrRes_SeatMassageCfg'
                                        *  ��Ħ��������ʹ�ܱ�־λ
                                        */
extern INT8U DrRes_VehicleRunFlag;     /* '<S11>/DrRes_VehicleRunFlag'
                                        * ��������״̬
                                        */
extern INT8U DrRes_VoltSatisfy;        /* '<S11>/DrRes_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */
extern INT8U DrRes_WelcomeEnable;      /* '<S11>/DrRes_WelcomeEnable'
                                        *  ���ݼ���ӭ������ʹ�ܱ�־λ
                                        */

/* Model entry point functions */
extern void Appl_DrRestMode_CtrlModel_initialize(void);
extern void Appl_DrRestMode_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_DrRestMode_CtrlModel_T *const Appl_DrRestMode_CtrlModel_M;

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
 * '<Root>' : 'Appl_DrRestMode_CtrlModel'
 * '<S1>'   : 'Appl_DrRestMode_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_DrRestMode_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_DrRestMode_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_DrRestMode_CtrlModel/LogicCtrl/ResCtrl'
 * '<S6>'   : 'Appl_DrRestMode_CtrlModel/LogicCtrl/ResCtrl/ResDeal'
 * '<S7>'   : 'Appl_DrRestMode_CtrlModel/LogicCtrl/ResCtrl/ResDeal/SaveResReCallPosi'
 * '<S8>'   : 'Appl_DrRestMode_CtrlModel/LogicCtrl/ResCtrl/ResDeal/SetResCallPosi'
 * '<S9>'   : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1'
 * '<S10>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2'
 * '<S11>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/RTE'
 * '<S12>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC1'
 * '<S13>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC2'
 * '<S14>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC3'
 * '<S15>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC4'
 * '<S16>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CallRet'
 * '<S17>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/GetHallValue'
 * '<S18>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC1/CC1_Flag'
 * '<S19>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC2/CC2_Flag'
 * '<S20>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC3/CC3_Flag'
 * '<S21>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CC4/CC4_Flag'
 * '<S22>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/CallRet/GetCallRet'
 * '<S23>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/GetHallValue/Char_CallHallVall_Length'
 * '<S24>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess1/GetHallValue/GetHallValue2'
 * '<S25>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/CLOSE'
 * '<S26>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/GetDrRestCAllRet'
 * '<S27>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/MassageFault'
 * '<S28>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/MotorFault'
 * '<S29>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/OPEN'
 * '<S30>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/STOP'
 * '<S31>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/CLOSE/Colse_Flag'
 * '<S32>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/MassageFault/MassageFault_Flag'
 * '<S33>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/MotorFault/MotorFault_Flag'
 * '<S34>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/OPEN/Open_Flag'
 * '<S35>'  : 'Appl_DrRestMode_CtrlModel/UpDataInputInfo/InputSignalProcess2/STOP/Stop_Flag'
 */
#endif                                 /* RTW_HEADER_Appl_DrRestMode_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
