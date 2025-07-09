/*
 * File: Appl_DrMotorAdjust_CtrlModel.h
 *
 * Code generated for Simulink model 'Appl_DrMotorAdjust_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jul  3 11:47:12 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_DrMotorAdjust_CtrlModel_h_
#define RTW_HEADER_Appl_DrMotorAdjust_CtrlModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_DrMotorAdjust_CtrlModel_COMMON_INCLUDES_
# define Appl_DrMotorAdjust_CtrlModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_DrMotorAdjust_CtrlModel_COMMON_INCLUDES_ */

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
typedef struct tag_RTM_Appl_DrMotorAdjust_CtrlModel_T
  RT_MODEL_Appl_DrMotorAdjust_CtrlModel_T;

#ifndef DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_
#define DEFINED_TYPEDEF_FOR_enSeatMotorRunTye_

/* ����������ͣ�,0���޶�����,1��HUM��,2�����ʣ�,3��������ã�,4���ֶ����ڣ�,5��ѧϰ����,6����λ����,7����λ����-BM400,8��С����,9�����IO����, */
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
  enSeatMotorRunTye_EN_ResEnable,
  enSeatMotorRunTye_EN_DiagIOEnable
}
enSeatMotorRunTye;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatMoveCmd_
#define DEFINED_TYPEDEF_FOR_enSeatMoveCmd_

/* 0���޶�����,1����ǰ��,2���º�, */
typedef enum
{
  enSeatMoveCmd_EN_NULL = 0,           /* Default value */
  enSeatMoveCmd_EN_UP_FORWARD,
  enSeatMoveCmd_EN_DN_BACKWARD
}
enSeatMoveCmd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enMosErrSts_
#define DEFINED_TYPEDEF_FOR_enMosErrSts_

/* Ԥ������ԭ��,0:��,1:оƬ��ʼ��,2:��ȫ���� ,3:VM�쳣,4:�¶��쳣 ,5:�����쳣,6:©Դ���� ,7:��̬���� , */
typedef enum
{
  enMosErrSts_enNULL = 0,              /* Default value */
  enMosErrSts_enMosInitErr,
  enMosErrSts_enMosSafeFailErr,
  enMosErrSts_enMosVmErr,
  enMosErrSts_enMosTempErr,
  enMosErrSts_enMosPumpErr,
  enMosErrSts_enMosDsErr,
  enMosErrSts_enMosOffErr
}
enMosErrSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enSeatHightMotorRunsts_
#define DEFINED_TYPEDEF_FOR_enSeatHightMotorRunsts_

/* ����������ͣ�,0���޶�����,1���̵����º�ճ��������ǰ�ƶ���,2���ֶ�������Ч��ǰ�ƶ���,3���Զ�������Ч��ǰ�ƶ���,4���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��,5.�ֶ�������Ч��ǰ�ƶ�ֹͣ,6.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ,7.�̵�����ǰճ�������º��ƶ�,8���ֶ�������Ч��ǰ�ƶ���,9���Զ�������Ч��ǰ�ƶ���,A���̵�������ճ�����ϻָ���ǰ�ƶ�ֹͣ��,B.�ֶ�������Ч��ǰ�ƶ�ֹͣ,C.�ֶ�������Ч��ǰ�ƶ�ֹͣ,D.�Զ����ڿ�����Ч��ǰ�ƶ�ֹͣ,E.�Զ����ڿ�����Ч�º��ƶ�ֹͣ,F.��ʱֹͣ,10.���϶�ת����ֹͣ,11.���¶�ת����ֹͣ,12.���ϻ�������ֹͣ,13.���»�������ֹͣ,14.Ԥ����ʼ��ֹͣ,15.Ԥ����ȫ����ֹͣ,16.Ԥ��VM����ֹͣ,17.Ԥ���¶ȹ���ֹͣ,18.Ԥ�����ù���ֹͣ,19.Ԥ��©Դ����ֹͣ,1A.Ԥ����̬������ֹͣ, */
typedef enum
{
  enSeatHightMotorRunsts_EN_NULL = 0,  /* Default value */
  enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU,
  enSeatHightMotorRunsts_EN_ManualAdjust_FU,
  enSeatHightMotorRunsts_EN_AutoAdjust_FU,
  enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop,
  enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop,
  enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK,
  enSeatHightMotorRunsts_EN_ManualAdjust_BK,
  enSeatHightMotorRunsts_EN_AutoAdjust_BK,
  enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop,
  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop,
  enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop,
  enSeatHightMotorRunsts_EN_Timeout_Stop,
  enSeatHightMotorRunsts_EN_UpFn_Lock_Stop,
  enSeatHightMotorRunsts_EN_DnBa_Lock_Stop,
  enSeatHightMotorRunsts_EN_UpFn_Hall_Stop,
  enSeatHightMotorRunsts_EN_DnBa_Hall_Stop,
  enSeatHightMotorRunsts_EN_UpFn_MovTypeChange,
  enSeatHightMotorRunsts_EN_DnBa_MovTypeChange,
  enSeatHightMotorRunsts_EN_Mos_MovTypeInit,
  enSeatHightMotorRunsts_EN_Mos_MovTypeSafe,
  enSeatHightMotorRunsts_EN_Mos_MovTypeVm,
  enSeatHightMotorRunsts_EN_Mos_MovTypeTemp,
  enSeatHightMotorRunsts_EN_Mos_MovTypePump,
  enSeatHightMotorRunsts_EN_Mos_MovTypeDs,
  enSeatHightMotorRunsts_EN_Mos_MovTypeOff
}
enSeatHightMotorRunsts;

#endif

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

#ifndef DEFINED_TYPEDEF_FOR_enIgnSts_
#define DEFINED_TYPEDEF_FOR_enIgnSts_

/* IGN��Դ��λ״̬,0��OFF,1��ACC,2��ON,3��CRANK,4��RUN, */
typedef enum
{
  enIgnSts_eOff = 0,                   /* Default value */
  enIgnSts_eAcc,
  enIgnSts_eOn,
  enIgnSts_eCrank,
  enIgnSts_eRun
}
enIgnSts;

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

/* Block signals (default storage) */
typedef struct
{
  enSeatMotorRunTye MotorActionType;   /* '<S6>/MotorAdjustmentPriorityProcessing1' */
  enSeatHightMotorRunsts H_MotorRunType;/* '<S21>/MotorAdjust' */
  enSeatHightMotorRunsts H_MotorRunType_g;/* '<S20>/MotorAdjust' */
  enSeatHightMotorRunsts H_MotorRunType_l;/* '<S19>/MotorAdjust' */
  enSeatHightMotorRunsts H_MotorRunType_m;/* '<S18>/MotorAdjust' */
  enSeatAutoRunSts HeightAutoRunFlag;  /* '<S21>/MotorAdjust' */
  enSeatAutoRunSts HeightAutoRunFlag_o;/* '<S20>/MotorAdjust' */
  enSeatAutoRunSts HeightAutoRunFlag_p;/* '<S19>/MotorAdjust' */
  enSeatAutoRunSts HeightAutoRunFlag_g;/* '<S18>/MotorAdjust' */
  INT8U DataTypeConversion2;           /* '<S4>/Data Type Conversion2' */
  INT8U DataTypeConversion3;           /* '<S4>/Data Type Conversion3' */
  INT8U DataTypeConversion4;           /* '<S4>/Data Type Conversion4' */
  INT8U DataTypeConversion5;           /* '<S4>/Data Type Conversion5' */
  INT8U Can_HeightMotorCtrl;           /* '<S8>/MotorMotionPriorityDeal' */
  INT8U Can_LengthMotorCtrl;           /* '<S8>/MotorMotionPriorityDeal' */
  INT8U Can_BackMotorCtrl;             /* '<S8>/MotorMotionPriorityDeal' */
  INT8U Can_FrontMotorCtrl;            /* '<S8>/MotorMotionPriorityDeal' */
  INT8U HeightMotorCmd;                /* '<S7>/CrankUnloading' */
  INT8U LengthMotorCmd;                /* '<S7>/CrankUnloading' */
  INT8U BackMotorCmd;                  /* '<S7>/CrankUnloading' */
  INT8U FrontMotorCmd;                 /* '<S7>/CrankUnloading' */
  INT8U BackManualAdjSw;               /* '<S6>/MotorAdjustmentPriorityProcessing1' */
  INT8U FrontManualAdjSw;              /* '<S6>/MotorAdjustmentPriorityProcessing1' */
}
B_Appl_DrMotorAdjust_CtrlModel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  enSeatMotorRunTye MotorActType_start;/* '<S21>/MotorAdjust' */
  enSeatMotorRunTye MotorActType_start_b;/* '<S20>/MotorAdjust' */
  enSeatMotorRunTye MotorActType_start_l;/* '<S19>/MotorAdjust' */
  enSeatMotorRunTye MotorActType_start_n;/* '<S18>/MotorAdjust' */
  INT16U SeatHeightPosiReq_start;      /* '<S21>/MotorAdjust' */
  INT16U SeatHeightPosiReq_start_o;    /* '<S20>/MotorAdjust' */
  INT16U SeatHeightPosiReq_start_ov;   /* '<S19>/MotorAdjust' */
  INT16U SeatHeightPosiReq_start_j;    /* '<S18>/MotorAdjust' */
  INT16U FrontTimer;                   /* '<S8>/MotorMotionPriorityDeal' */
  INT16U HeightTimer;                  /* '<S8>/MotorMotionPriorityDeal' */
  INT16U LengthTimer;                  /* '<S8>/MotorMotionPriorityDeal' */
  INT16U BackTimer;                    /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_active_c18_Appl_DrMotorAdjust_CtrlModel;/* '<S21>/MotorAdjust' */
  INT8U is_c18_Appl_DrMotorAdjust_CtrlModel;/* '<S21>/MotorAdjust' */
  INT8U DownBackFlag;                  /* '<S21>/MotorAdjust' */
  INT8U UpFrontFlag;                   /* '<S21>/MotorAdjust' */
  INT8U HMotorRunIntervalTime;         /* '<S21>/MotorAdjust' */
  INT8U is_active_c4_Appl_DrMotorAdjust_CtrlModel;/* '<S20>/MotorAdjust' */
  INT8U is_c4_Appl_DrMotorAdjust_CtrlModel;/* '<S20>/MotorAdjust' */
  INT8U DownBackFlag_k;                /* '<S20>/MotorAdjust' */
  INT8U UpFrontFlag_g;                 /* '<S20>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_e;       /* '<S20>/MotorAdjust' */
  INT8U is_active_c21_Appl_DrMotorAdjust_CtrlModel;/* '<S19>/MotorAdjust' */
  INT8U is_c21_Appl_DrMotorAdjust_CtrlModel;/* '<S19>/MotorAdjust' */
  INT8U DownBackFlag_n;                /* '<S19>/MotorAdjust' */
  INT8U UpFrontFlag_b;                 /* '<S19>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_f;       /* '<S19>/MotorAdjust' */
  INT8U is_active_c19_Appl_DrMotorAdjust_CtrlModel;/* '<S18>/MotorAdjust' */
  INT8U is_c19_Appl_DrMotorAdjust_CtrlModel;/* '<S18>/MotorAdjust' */
  INT8U DownBackFlag_c;                /* '<S18>/MotorAdjust' */
  INT8U UpFrontFlag_c;                 /* '<S18>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_a;       /* '<S18>/MotorAdjust' */
  INT8U is_active_c16_Appl_DrMotorAdjust_CtrlModel;/* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_HeightAdjust;               /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_VerticalAdjust;             /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_BackAdjust;                 /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_FrontAngleAdjust;           /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_active_c17_Appl_DrMotorAdjust_CtrlModel;/* '<S7>/CrankUnloading' */
  INT8U is_c17_Appl_DrMotorAdjust_CtrlModel;/* '<S7>/CrankUnloading' */
  INT8U is_active_c2_Appl_DrMotorAdjust_CtrlModel;/* '<S6>/MotorAdjustmentPriorityProcessing1' */
}
DW_Appl_DrMotorAdjust_CtrlModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_DrMotorAdjust_CtrlModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_DrMotorAdjust_CtrlModel_T Appl_DrMotorAdjust_CtrlModel_B;

/* Block states (default storage) */
extern DW_Appl_DrMotorAdjust_CtrlModel_T Appl_DrMotorAdjust_CtrlModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enMosErrSts DrMtr_BackMotorMosErr;/* '<S27>/DrMtr_BackMotorMosErr'
                                          * Ԥ���������ԭ��
                                          */
extern enMosErrSts DrMtr_FrontMotorMosErr;/* '<S27>/DrMtr_FrontMotorMosErr'
                                           * Ԥ���������ԭ��
                                           */
extern enMosErrSts DrMtr_HeigthMotorMosErr;/* '<S27>/DrMtr_HeigthMotorMosErr'
                                            * Ԥ���������ԭ��
                                            */
extern enMosErrSts DrMtr_LengthMotorMosErr;/* '<S27>/DrMtr_LengthMotorMosErr'
                                            * Ԥ���������ԭ��
                                            */
extern enIgnSts DrMtr_PowerModeStatus; /* '<S27>/DrMtr_PowerModeStatus'
                                        * ������Դ��λ
                                        */
extern enFinalPowerMode DrMtr_VoltMode;/* '<S27>/DrMtr_VoltMode'
                                        * ��ѹģʽ
                                        */
extern INT16U DrMtr_BackDefaultStopPos;/* '<S27>/DrMtr_BackDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
extern INT16U DrMtr_BackHallPosi;      /* '<S27>/DrMtr_BackHallPosi'
                                        * ��ǰ��������
                                        */
extern INT16U DrMtr_FrontDefaulStoptPos;/* '<S27>/DrMtr_FrontDefaulStoptPos'
                                         * ����Ӳֹ��
                                         */
extern INT16U DrMtr_FrontHallPosi;     /* '<S27>/DrMtr_FrontHallPosi'
                                        * ��ǰ���л���
                                        */
extern INT16U DrMtr_HeightDefaultStopPos;/* '<S27>/DrMtr_HeightDefaultStopPos'
                                          * �߶�Ӳֹ��
                                          */
extern INT16U DrMtr_HeightHallPosi;    /* '<S27>/DrMtr_HeightHallPosi'
                                        * ��ǰ�߶Ȼ���
                                        */
extern INT16U DrMtr_LengthDefaultStopPos;/* '<S27>/DrMtr_LengthDefaultStopPos'
                                          * ����Ӳֹ��
                                          */
extern INT16U DrMtr_LengthHallPosi;    /* '<S27>/DrMtr_LengthHallPosi'
                                        * ��ǰ�������
                                        */
extern INT16U DrMtr_MemoryBackReqPosi; /* '<S27>/DrMtr_MemoryBackReqPosi'
                                        * �������-����λ��
                                        */
extern INT16U DrMtr_MemoryFrontReqPosi;/* '<S27>/DrMtr_MemoryFrontReqPosi'
                                        * �������-ǰ��λ��
                                        */
extern INT16U DrMtr_MemoryHeightReqPosi;/* '<S27>/DrMtr_MemoryHeightReqPosi'
                                         * �������-�߶�λ��
                                         */
extern INT16U DrMtr_MemoryLengthReqPosi;/* '<S27>/DrMtr_MemoryLengthReqPosi'
                                         * �������-����λ��
                                         */
extern INT16U DrMtr_ResBackReqPosi;    /* '<S27>/DrMtr_ResBackReqPosi'
                                        * С����-����λ��
                                        */
extern INT16U DrMtr_ResFrontReqPosi;   /* '<S27>/DrMtr_ResFrontReqPosi'
                                        * С����-ǰ��λ��
                                        */
extern INT16U DrMtr_ResHeightReqPosi;  /* '<S27>/DrMtr_ResHeightReqPosi'
                                        * С����-�߶�λ��
                                        */
extern INT16U DrMtr_ResLengthReqPosi;  /* '<S27>/DrMtr_ResLengthReqPosi'
                                        * С����-����λ��
                                        */
extern INT16U DrMtr_ResetBackReqPosi;  /* '<S27>/DrMtr_ResetBackReqPosi'
                                        * ��λ����-����λ��
                                        */
extern INT16U DrMtr_ResetFrontReqPosi; /* '<S27>/DrMtr_ResetFrontReqPosi'
                                        * ��λ����-ǰ��λ��
                                        */
extern INT16U DrMtr_ResetHeightReqPosi;/* '<S27>/DrMtr_ResetHeightReqPosi'
                                        * ��λ����-�߶�λ��
                                        */
extern INT16U DrMtr_ResetLengthReqPosi;/* '<S27>/DrMtr_ResetLengthReqPosi'
                                        * ��λ����-����λ��
                                        */
extern INT16U DrMtr_WelcomeBackReqPosi;/* '<S27>/DrMtr_WelcomeBackReqPosi'
                                        * ӭ������-����λ��
                                        */
extern INT16U DrMtr_WelcomeLengthReqPosi;/* '<S27>/DrMtr_WelcomeLengthReqPosi'
                                          * ӭ������-����λ��
                                          */
extern INT8U DrMtr_AnyoneHallErr;      /* '<S27>/DrMtr_AnyoneHallErr'
                                        * ��һ�������ϱ�־
                                        */
extern INT8U DrMtr_AnyoneRelayAdheErr; /* '<S27>/DrMtr_AnyoneRelayAdheErr'
                                        * ��һ�̵���ճ�����ϱ�־
                                        */
extern INT8U DrMtr_BackHallErr;        /* '<S27>/DrMtr_BackHallErr'
                                        * ���������ϱ�־λ
                                        */
extern INT8U DrMtr_BackLearnCmd;       /* '<S27>/DrMtr_BackLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U DrMtr_BackMotorTimeOutErr;/* '<S27>/DrMtr_BackMotorTimeOutErr'
                                        * ����������г�ʱ��־
                                        */
extern INT8U DrMtr_BackRelayAdhesionErr;/* '<S27>/DrMtr_BackRelayAdhesionErr'
                                         * �����̵���ճ����־λ
                                         */
extern INT8U DrMtr_BackSoftStopErr;    /* '<S27>/DrMtr_BackSoftStopErr'
                                        * ����������ֹ��
                                        */
extern INT8U DrMtr_BackStallErr;       /* '<S27>/DrMtr_BackStallErr'
                                        * ������ת��־λ
                                        */
extern INT8U DrMtr_BackSwitchAdheErr;  /* '<S27>/DrMtr_BackSwitchAdheErr'
                                        * ��������ճ�����ϱ�־λ
                                        */
extern INT8U DrMtr_BackSwitchCmd;      /* '<S27>/DrMtr_BackSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
extern INT8U DrMtr_DiagnoseLearnIn;    /* '<S27>/DrMtr_DiagnoseLearnIn'
                                        * ����ѧϰ��־
                                        */
extern INT8U DrMtr_FrontHallErr;       /* '<S27>/DrMtr_FrontHallErr'
                                        * ���л����ϱ�־λ
                                        */
extern INT8U DrMtr_FrontLearnCmd;      /* '<S27>/DrMtr_FrontLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U DrMtr_FrontMotorTimeOutErr;/* '<S27>/DrMtr_FrontMotorTimeOutErr'
                                         * ���е�����г�ʱ��־
                                         */
extern INT8U DrMtr_FrontRelayAdhesionErr;/* '<S27>/DrMtr_FrontRelayAdhesionErr'
                                          * ���м̵���ճ����־λ
                                          */
extern INT8U DrMtr_FrontSoftStopErr;   /* '<S27>/DrMtr_FrontSoftStopErr'
                                        * ���е�����ֹ��
                                        */
extern INT8U DrMtr_FrontStallErr;      /* '<S27>/DrMtr_FrontStallErr'
                                        * ���ж�ת��־λ
                                        */
extern INT8U DrMtr_FrontSwitchAdheErr; /* '<S27>/DrMtr_FrontSwitchAdheErr'
                                        * ���п���ճ�����ϱ�־λ
                                        */
extern INT8U DrMtr_FrontSwitchCmd;     /* '<S27>/DrMtr_FrontSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
extern INT8U DrMtr_HeightHallErr;      /* '<S27>/DrMtr_HeightHallErr'
                                        * �߶Ȼ����ϱ�־λ
                                        */
extern INT8U DrMtr_HeightLearnCmd;     /* '<S27>/DrMtr_HeightLearnCmd'
                                        * ѧϰ��������-�߶�
                                        */
extern INT8U DrMtr_HeightMotorTimeOutErr;/* '<S27>/DrMtr_HeightMotorTimeOutErr'
                                          * �߶ȵ�����г�ʱ��־
                                          */
extern INT8U DrMtr_HeightRelayAdhesionErr;/* '<S27>/DrMtr_HeightRelayAdhesionErr'
                                           * �߶ȼ̵���ճ����־λ
                                           */
extern INT8U DrMtr_HeightSoftStopErr;  /* '<S27>/DrMtr_HeightSoftStopErr'
                                        * �߶ȵ�����ֹ��
                                        */
extern INT8U DrMtr_HeightStallErr;     /* '<S27>/DrMtr_HeightStallErr'
                                        * �߶ȶ�ת��־λ
                                        */
extern INT8U DrMtr_HeightSwitchAdheErr;/* '<S27>/DrMtr_HeightSwitchAdheErr'
                                        * �߶ȿ���ճ�����ϱ�־λ
                                        */
extern INT8U DrMtr_HeightSwitchCmd;    /* '<S27>/DrMtr_HeightSwitchCmd'
                                        * Ӳ�߿�����������-�߶�
                                        */
extern INT8U DrMtr_LearnSts;           /* '<S27>/DrMtr_LearnSts'
                                        * ѧϰ״̬
                                        */
extern INT8U DrMtr_LengthHallErr;      /* '<S27>/DrMtr_LengthHallErr'
                                        * ��������ϱ�־λ
                                        */
extern INT8U DrMtr_LengthLearnCmd;     /* '<S27>/DrMtr_LengthLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U DrMtr_LengthMotorTimeOutErr;/* '<S27>/DrMtr_LengthMotorTimeOutErr'
                                          * ���������г�ʱ��־
                                          */
extern INT8U DrMtr_LengthRelayAdhesionErr;/* '<S27>/DrMtr_LengthRelayAdhesionErr'
                                           * ����̵���ճ����־λ
                                           */
extern INT8U DrMtr_LengthSoftStopErr;  /* '<S27>/DrMtr_LengthSoftStopErr'
                                        * ���򵽴���ֹ��
                                        */
extern INT8U DrMtr_LengthStallErr;     /* '<S27>/DrMtr_LengthStallErr'
                                        * �����ת��־λ
                                        */
extern INT8U DrMtr_LengthSwitchAdheErr;/* '<S27>/DrMtr_LengthSwitchAdheErr'
                                        * ���򿪹�ճ�����ϱ�־λ
                                        */
extern INT8U DrMtr_LengthSwitchCmd;    /* '<S27>/DrMtr_LengthSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
extern INT8U DrMtr_VoltSatisfy;        /* '<S27>/DrMtr_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */

/* Model entry point functions */
extern void Appl_DrMotorAdjust_CtrlModel_initialize(void);
extern void Appl_DrMotorAdjust_CtrlModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_DrMotorAdjust_CtrlModel_T *const
  Appl_DrMotorAdjust_CtrlModel_M;

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile INT8U CAL_HightMotorRunInterval_100ms;/* ������ڼ��ʱ��100ms */
extern const volatile INT16U CAL_MotorDiffToStart_100ms;/* ��ͬ����������ʱ��100ms */

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
 * '<Root>' : 'Appl_DrMotorAdjust_CtrlModel'
 * '<S1>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl'
 * '<S2>'   : 'Appl_DrMotorAdjust_CtrlModel/Model Info'
 * '<S3>'   : 'Appl_DrMotorAdjust_CtrlModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_DrMotorAdjust_CtrlModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/AdjustRequestPriority'
 * '<S7>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/CrankAndVoltageDeal'
 * '<S8>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority'
 * '<S9>'   : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust'
 * '<S10>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/AdjustRequestPriority/MotorAdjustmentPriorityProcessing1'
 * '<S11>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/CrankAndVoltageDeal/CrankUnloading'
 * '<S12>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/BackDelay'
 * '<S13>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/Enumerated Constant'
 * '<S14>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/FrontDelay'
 * '<S15>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/HeightDelay'
 * '<S16>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/LengthDelay'
 * '<S17>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/MotorMotionPriorityDeal'
 * '<S18>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/BackMotorRun'
 * '<S19>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/FrontMotorRun'
 * '<S20>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/HeightMotorRun'
 * '<S21>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/LengthMotorRun'
 * '<S22>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/BackMotorRun/MotorAdjust'
 * '<S23>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/FrontMotorRun/MotorAdjust'
 * '<S24>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/HeightMotorRun/MotorAdjust'
 * '<S25>'  : 'Appl_DrMotorAdjust_CtrlModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/LengthMotorRun/MotorAdjust'
 * '<S26>'  : 'Appl_DrMotorAdjust_CtrlModel/UpDataInputInfo/InputSignalProcess'
 * '<S27>'  : 'Appl_DrMotorAdjust_CtrlModel/UpDataInputInfo/RTE'
 * '<S28>'  : 'Appl_DrMotorAdjust_CtrlModel/UpDataOutputInfo/HardwareOutput'
 */
#endif                                 /* RTW_HEADER_Appl_DrMotorAdjust_CtrlModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
