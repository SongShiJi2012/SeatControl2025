/*
 * File: Appl_PaAdjustModel.h
 *
 * Code generated for Simulink model 'Appl_PaAdjustModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jul  3 11:49:21 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Appl_PaAdjustModel_h_
#define RTW_HEADER_Appl_PaAdjustModel_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef Appl_PaAdjustModel_COMMON_INCLUDES_
# define Appl_PaAdjustModel_COMMON_INCLUDES_
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
#endif                                 /* Appl_PaAdjustModel_COMMON_INCLUDES_ */

#include "Appl_PaAdjustModel_types.h"

/* Includes for objects with custom storage classes. */
#include "Appl_DrMotorAdjust_CtrlModel.h"
#include "Common.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct
{
  enSeatMotorRunTye MotorActionType;   /* '<S6>/PaMotorAdjustmentPriorityProcessing' */
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
  INT8U BackManualAdjSw;               /* '<S6>/PaMotorAdjustmentPriorityProcessing' */
  INT8U FrontManualAdjSw;              /* '<S6>/PaMotorAdjustmentPriorityProcessing' */
}
B_Appl_PaAdjustModel_T;

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
  INT8U is_active_c18_Appl_PaAdjustModel;/* '<S21>/MotorAdjust' */
  INT8U is_c18_Appl_PaAdjustModel;     /* '<S21>/MotorAdjust' */
  INT8U DownBackFlag;                  /* '<S21>/MotorAdjust' */
  INT8U UpFrontFlag;                   /* '<S21>/MotorAdjust' */
  INT8U HMotorRunIntervalTime;         /* '<S21>/MotorAdjust' */
  INT8U is_active_c4_Appl_PaAdjustModel;/* '<S20>/MotorAdjust' */
  INT8U is_c4_Appl_PaAdjustModel;      /* '<S20>/MotorAdjust' */
  INT8U DownBackFlag_k;                /* '<S20>/MotorAdjust' */
  INT8U UpFrontFlag_g;                 /* '<S20>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_e;       /* '<S20>/MotorAdjust' */
  INT8U is_active_c21_Appl_PaAdjustModel;/* '<S19>/MotorAdjust' */
  INT8U is_c21_Appl_PaAdjustModel;     /* '<S19>/MotorAdjust' */
  INT8U DownBackFlag_n;                /* '<S19>/MotorAdjust' */
  INT8U UpFrontFlag_b;                 /* '<S19>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_f;       /* '<S19>/MotorAdjust' */
  INT8U is_active_c19_Appl_PaAdjustModel;/* '<S18>/MotorAdjust' */
  INT8U is_c19_Appl_PaAdjustModel;     /* '<S18>/MotorAdjust' */
  INT8U DownBackFlag_c;                /* '<S18>/MotorAdjust' */
  INT8U UpFrontFlag_c;                 /* '<S18>/MotorAdjust' */
  INT8U HMotorRunIntervalTime_a;       /* '<S18>/MotorAdjust' */
  INT8U is_active_c16_Appl_PaAdjustModel;/* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_HeightAdjust;               /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_VerticalAdjust;             /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_BackAdjust;                 /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_FrontAngleAdjust;           /* '<S8>/MotorMotionPriorityDeal' */
  INT8U is_active_c17_Appl_PaAdjustModel;/* '<S7>/CrankUnloading' */
  INT8U is_c17_Appl_PaAdjustModel;     /* '<S7>/CrankUnloading' */
  INT8U is_active_c2_Appl_PaAdjustModel;/* '<S6>/PaMotorAdjustmentPriorityProcessing' */
}
DW_Appl_PaAdjustModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_Appl_PaAdjustModel_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Appl_PaAdjustModel_T Appl_PaAdjustModel_B;

/* Block states (default storage) */
extern DW_Appl_PaAdjustModel_T Appl_PaAdjustModel_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enMosErrSts PaMtr_BackMotorMosErr;/* '<S27>/PaMtr_BackMotorMosErr'
                                          * Ԥ���������ԭ��
                                          */
extern enMosErrSts PaMtr_FrontMotorMosErr;/* '<S27>/PaMtr_FrontMotorMosErr'
                                           * Ԥ���������ԭ��
                                           */
extern enMosErrSts PaMtr_HeigthMotorMosErr;/* '<S27>/PaMtr_HeigthMotorMosErr'
                                            * Ԥ���������ԭ��
                                            */
extern enMosErrSts PaMtr_LengthMotorMosErr;/* '<S27>/PaMtr_LengthMotorMosErr'
                                            * Ԥ���������ԭ��
                                            */
extern enIgnSts PaMtr_PowerModeStatus; /* '<S27>/PaMtr_PowerModeStatus'
                                        * ������Դ��λ
                                        */
extern enFinalPowerMode PaMtr_VoltMode;/* '<S27>/PaMtr_VoltMode'
                                        * ������ѹģʽ
                                        */
extern INT16U PaMtr_BackDefaultStopPos;/* '<S27>/PaMtr_BackDefaultStopPos'
                                        * Ӳֹ������-���ݿ���
                                        */
extern INT16U PaMtr_BackHallPosi;      /* '<S27>/PaMtr_BackHallPosi'
                                        * ��ǰ��������-���ݿ���
                                        */
extern INT16U PaMtr_FrontDefaulStoptPos;/* '<S27>/PaMtr_FrontDefaulStoptPos'
                                         * Ӳֹ������-��������
                                         */
extern INT16U PaMtr_FrontHallPosi;     /* '<S27>/PaMtr_FrontHallPosi'
                                        * ��ǰ��������-��������
                                        */
extern INT16U PaMtr_HeightDefaultStopPos;/* '<S27>/PaMtr_HeightDefaultStopPos'
                                          * Ӳֹ������-���ݸ߶�
                                          */
extern INT16U PaMtr_HeightHallPosi;    /* '<S27>/PaMtr_HeightHallPosi'
                                        * ��ǰ��������-���ݸ߶�
                                        */
extern INT16U PaMtr_LengthDefaultStopPos;/* '<S27>/PaMtr_LengthDefaultStopPos'
                                          * Ӳֹ������-��������
                                          */
extern INT16U PaMtr_LengthHallPosi;    /* '<S27>/PaMtr_LengthHallPosi'
                                        * ��ǰ��������-��������
                                        */
extern INT16U PaMtr_MemoryBackReqPosi; /* '<S27>/PaMtr_MemoryBackReqPosi'
                                        * �������-���ݿ���λ��
                                        */
extern INT16U PaMtr_MemoryFrontReqPosi;/* '<S27>/PaMtr_MemoryFrontReqPosi'
                                        * �������-����ǰ��λ��
                                        */
extern INT16U PaMtr_MemoryHeightReqPosi;/* '<S27>/PaMtr_MemoryHeightReqPosi'
                                         * �������-���ݸ߶�λ��
                                         */
extern INT16U PaMtr_MemoryLengthReqPosi;/* '<S27>/PaMtr_MemoryLengthReqPosi'
                                         * �������-��������λ��
                                         */
extern INT16U PaMtr_ResetBackReqPosi;  /* '<S27>/PaMtr_ResetBackReqPosi'
                                        * ��λ����-����λ��
                                        */
extern INT16U PaMtr_ResetFrontReqPosi; /* '<S27>/PaMtr_ResetFrontReqPosi'
                                        * ��λ����-ǰ��λ��
                                        */
extern INT16U PaMtr_ResetHeightReqPosi;/* '<S27>/PaMtr_ResetHeightReqPosi'
                                        * ��λ����-�߶�λ��
                                        */
extern INT16U PaMtr_ResetLengthReqPosi;/* '<S27>/PaMtr_ResetLengthReqPosi'
                                        * ��λ����-����λ��
                                        */
extern INT16U PaMtr_WelcomeBackReqPosi;/* '<S27>/PaMtr_WelcomeBackReqPosi'
                                        * ӭ������-���ݿ���λ��
                                        */
extern INT16U PaMtr_WelcomeLengthReqPosi;/* '<S27>/PaMtr_WelcomeLengthReqPosi'
                                          * ӭ������-��������λ��
                                          */
extern INT8U PaMtr_AnyoneHallErr;      /* '<S27>/PaMtr_AnyoneHallErr'
                                        * ��һ�������ϱ�־
                                        */
extern INT8U PaMtr_AnyoneRelayAdheErr; /* '<S27>/PaMtr_AnyoneRelayAdheErr'
                                        * ��һ�̵���ճ�����ϱ�־
                                        */
extern INT8U PaMtr_BackHallErr;        /* '<S27>/PaMtr_BackHallErr'
                                        * �����ϱ�־λ-���ݿ���
                                        */
extern INT8U PaMtr_BackLearnCmd;       /* '<S27>/PaMtr_BackLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U PaMtr_BackMotorTimeOutErr;/* '<S27>/PaMtr_BackMotorTimeOutErr'
                                        * ������г�ʱ��־-���ݿ���
                                        */
extern INT8U PaMtr_BackRelayAdhesionErr;/* '<S27>/PaMtr_BackRelayAdhesionErr'
                                         * �̵���ճ����־λ-���ݿ���
                                         */
extern INT8U PaMtr_BackSoftStopErr;    /* '<S27>/PaMtr_BackSoftStopErr'
                                        * ������ֹ��-���ݿ���
                                        */
extern INT8U PaMtr_BackStallErr;       /* '<S27>/PaMtr_BackStallErr'
                                        * ��ת��־λ-���ݿ���
                                        */
extern INT8U PaMtr_BackSwitchAdheErr;  /* '<S27>/PaMtr_BackSwitchAdheErr'
                                        * ����ճ�����ϱ�־λ-���ݿ���
                                        */
extern INT8U PaMtr_BackSwitchCmd;      /* '<S27>/PaMtr_BackSwitchCmd'
                                        * Ӳ�߿�����������-���ݿ���
                                        */
extern INT8U PaMtr_DiagnoseLearnIn;    /* '<S27>/PaMtr_DiagnoseLearnIn'
                                        * ����ѧϰ��־
                                        */
extern INT8U PaMtr_FrontHallErr;       /* '<S27>/PaMtr_FrontHallErr'
                                        * �����ϱ�־λ-��������
                                        */
extern INT8U PaMtr_FrontLearnCmd;      /* '<S27>/PaMtr_FrontLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U PaMtr_FrontMotorTimeOutErr;/* '<S27>/PaMtr_FrontMotorTimeOutErr'
                                         * ������г�ʱ��־-��������
                                         */
extern INT8U PaMtr_FrontRelayAdhesionErr;/* '<S27>/PaMtr_FrontRelayAdhesionErr'
                                          * �̵���ճ����־λ-��������
                                          */
extern INT8U PaMtr_FrontSoftStopErr;   /* '<S27>/PaMtr_FrontSoftStopErr'
                                        * ������ֹ��-��������
                                        */
extern INT8U PaMtr_FrontStallErr;      /* '<S27>/PaMtr_FrontStallErr'
                                        * ��ת��־λ-��������
                                        */
extern INT8U PaMtr_FrontSwitchAdheErr; /* '<S27>/PaMtr_FrontSwitchAdheErr'
                                        * ����ճ�����ϱ�־λ-��������
                                        */
extern INT8U PaMtr_FrontSwitchCmd;     /* '<S27>/PaMtr_FrontSwitchCmd'
                                        * Ӳ�߿�����������-��������
                                        */
extern INT8U PaMtr_HeightHallErr;      /* '<S27>/PaMtr_HeightHallErr'
                                        * �����ϱ�־λ-���ݸ߶�
                                        */
extern INT8U PaMtr_HeightLearnCmd;     /* '<S27>/PaMtr_HeightLearnCmd'
                                        * ѧϰ��������-�߶�
                                        */
extern INT8U PaMtr_HeightMotorTimeOutErr;/* '<S27>/PaMtr_HeightMotorTimeOutErr'
                                          * ������г�ʱ��־-���ݸ߶�
                                          */
extern INT8U PaMtr_HeightRelayAdhesionErr;/* '<S27>/PaMtr_HeightRelayAdhesionErr'
                                           * �̵���ճ����־λ-���ݸ߶�
                                           */
extern INT8U PaMtr_HeightSoftStopErr;  /* '<S27>/PaMtr_HeightSoftStopErr'
                                        * ������ֹ��-���ݸ߶�
                                        */
extern INT8U PaMtr_HeightStallErr;     /* '<S27>/PaMtr_HeightStallErr'
                                        * ��ת��־λ-���ݸ߶�
                                        */
extern INT8U PaMtr_HeightSwitchAdheErr;/* '<S27>/PaMtr_HeightSwitchAdheErr'
                                        * ����ճ�����ϱ�־λ-���ݸ߶�
                                        */
extern INT8U PaMtr_HeightSwitchCmd;    /* '<S27>/PaMtr_HeightSwitchCmd'
                                        * Ӳ�߿�����������-���ݸ߶�
                                        */
extern INT8U PaMtr_LearnSts;           /* '<S27>/PaMtr_LearnSts'
                                        * ѧϰ״̬
                                        */
extern INT8U PaMtr_LengthHallErr;      /* '<S27>/PaMtr_LengthHallErr'
                                        * �����ϱ�־λ-��������
                                        */
extern INT8U PaMtr_LengthLearnCmd;     /* '<S27>/PaMtr_LengthLearnCmd'
                                        * ѧϰ��������-����
                                        */
extern INT8U PaMtr_LengthMotorTimeOutErr;/* '<S27>/PaMtr_LengthMotorTimeOutErr'
                                          * ������г�ʱ��־-��������
                                          */
extern INT8U PaMtr_LengthRelayAdhesionErr;/* '<S27>/PaMtr_LengthRelayAdhesionErr'
                                           * �̵���ճ����־λ-��������
                                           */
extern INT8U PaMtr_LengthSoftStopErr;  /* '<S27>/PaMtr_LengthSoftStopErr'
                                        * ������ֹ��-��������
                                        */
extern INT8U PaMtr_LengthStallErr;     /* '<S27>/PaMtr_LengthStallErr'
                                        * ��ת��־λ-��������
                                        */
extern INT8U PaMtr_LengthSwitchAdheErr;/* '<S27>/PaMtr_LengthSwitchAdheErr'
                                        * ����ճ�����ϱ�־λ-��������
                                        */
extern INT8U PaMtr_LengthSwitchCmd;    /* '<S27>/PaMtr_LengthSwitchCmd'
                                        * Ӳ�߿�����������-��������
                                        */
extern INT8U PaMtr_VoltSatisfy;        /* '<S27>/PaMtr_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */

/* Model entry point functions */
extern void Appl_PaAdjustModel_initialize(void);
extern void Appl_PaAdjustModel_step(void);

/* Real-time Model object */
extern RT_MODEL_Appl_PaAdjustModel_T *const Appl_PaAdjustModel_M;

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
 * '<Root>' : 'Appl_PaAdjustModel'
 * '<S1>'   : 'Appl_PaAdjustModel/LogicCtrl'
 * '<S2>'   : 'Appl_PaAdjustModel/Model Info'
 * '<S3>'   : 'Appl_PaAdjustModel/UpDataInputInfo'
 * '<S4>'   : 'Appl_PaAdjustModel/UpDataOutputInfo'
 * '<S5>'   : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl'
 * '<S6>'   : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/AdjustRequestPriority'
 * '<S7>'   : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/CrankAndVoltageDeal'
 * '<S8>'   : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority'
 * '<S9>'   : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust'
 * '<S10>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/AdjustRequestPriority/PaMotorAdjustmentPriorityProcessing'
 * '<S11>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/CrankAndVoltageDeal/CrankUnloading'
 * '<S12>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/BackDelay'
 * '<S13>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/Enumerated Constant'
 * '<S14>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/FrontDelay'
 * '<S15>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/HeightDelay'
 * '<S16>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/LengthDelay'
 * '<S17>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/FourMotorPriority/MotorMotionPriorityDeal'
 * '<S18>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/BackMotorRun'
 * '<S19>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/FrontMotorRun'
 * '<S20>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/HeightMotorRun'
 * '<S21>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/LengthMotorRun'
 * '<S22>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/BackMotorRun/MotorAdjust'
 * '<S23>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/FrontMotorRun/MotorAdjust'
 * '<S24>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/HeightMotorRun/MotorAdjust'
 * '<S25>'  : 'Appl_PaAdjustModel/LogicCtrl/LocalAdjustCtrl/MotorAdjust/LengthMotorRun/MotorAdjust'
 * '<S26>'  : 'Appl_PaAdjustModel/UpDataInputInfo/InputSignalProcess'
 * '<S27>'  : 'Appl_PaAdjustModel/UpDataInputInfo/RTE'
 * '<S28>'  : 'Appl_PaAdjustModel/UpDataOutputInfo/HardwareOutput'
 */
#endif                                 /* RTW_HEADER_Appl_PaAdjustModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
