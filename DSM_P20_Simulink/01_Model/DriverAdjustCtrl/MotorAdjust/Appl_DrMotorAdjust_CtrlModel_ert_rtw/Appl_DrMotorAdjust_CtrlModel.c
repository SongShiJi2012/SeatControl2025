/*
 * File: Appl_DrMotorAdjust_CtrlModel.c
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

#include "Appl_DrMotorAdjust_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_ToleranceDistance
#error The variable for the parameter "D_ToleranceDistance" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_Relay_DownBackFault
#error The variable for the parameter "D_Relay_DownBackFault" is not defined
#endif

#ifndef D_Relay_UpFrontFault
#error The variable for the parameter "D_Relay_UpFrontFault" is not defined
#endif

/* Named constants for Chart: '<S7>/CrankUnloading' */
#define Appl_DrMotorAdjust_CtrlModel_IN_Ban ((INT8U)1U)
#define Appl_DrMotorAdjust_CtrlModel_IN_Init ((INT8U)2U)

/* Named constants for Chart: '<S8>/MotorMotionPriorityDeal' */
#define Appl_DrMotorAdjust_CtrlModel_IN_Action ((INT8U)1U)

/* Named constants for Chart: '<S18>/MotorAdjust' */
#define Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun ((INT8U)1U)
#define Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun ((INT8U)2U)
#define Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval ((INT8U)3U)

/* Exported block signals */
enMosErrSts DrMtr_BackMotorMosErr;     /* '<S27>/DrMtr_BackMotorMosErr'
                                        * Ԥ���������ԭ��
                                        */
enMosErrSts DrMtr_FrontMotorMosErr;    /* '<S27>/DrMtr_FrontMotorMosErr'
                                        * Ԥ���������ԭ��
                                        */
enMosErrSts DrMtr_HeigthMotorMosErr;   /* '<S27>/DrMtr_HeigthMotorMosErr'
                                        * Ԥ���������ԭ��
                                        */
enMosErrSts DrMtr_LengthMotorMosErr;   /* '<S27>/DrMtr_LengthMotorMosErr'
                                        * Ԥ���������ԭ��
                                        */
enIgnSts DrMtr_PowerModeStatus;        /* '<S27>/DrMtr_PowerModeStatus'
                                        * ������Դ��λ
                                        */
enFinalPowerMode DrMtr_VoltMode;       /* '<S27>/DrMtr_VoltMode'
                                        * ��ѹģʽ
                                        */
INT16U DrMtr_BackDefaultStopPos;       /* '<S27>/DrMtr_BackDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrMtr_BackHallPosi;             /* '<S27>/DrMtr_BackHallPosi'
                                        * ��ǰ��������
                                        */
INT16U DrMtr_FrontDefaulStoptPos;      /* '<S27>/DrMtr_FrontDefaulStoptPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrMtr_FrontHallPosi;            /* '<S27>/DrMtr_FrontHallPosi'
                                        * ��ǰ���л���
                                        */
INT16U DrMtr_HeightDefaultStopPos;     /* '<S27>/DrMtr_HeightDefaultStopPos'
                                        * �߶�Ӳֹ��
                                        */
INT16U DrMtr_HeightHallPosi;           /* '<S27>/DrMtr_HeightHallPosi'
                                        * ��ǰ�߶Ȼ���
                                        */
INT16U DrMtr_LengthDefaultStopPos;     /* '<S27>/DrMtr_LengthDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrMtr_LengthHallPosi;           /* '<S27>/DrMtr_LengthHallPosi'
                                        * ��ǰ�������
                                        */
INT16U DrMtr_MemoryBackReqPosi;        /* '<S27>/DrMtr_MemoryBackReqPosi'
                                        * �������-����λ��
                                        */
INT16U DrMtr_MemoryFrontReqPosi;       /* '<S27>/DrMtr_MemoryFrontReqPosi'
                                        * �������-ǰ��λ��
                                        */
INT16U DrMtr_MemoryHeightReqPosi;      /* '<S27>/DrMtr_MemoryHeightReqPosi'
                                        * �������-�߶�λ��
                                        */
INT16U DrMtr_MemoryLengthReqPosi;      /* '<S27>/DrMtr_MemoryLengthReqPosi'
                                        * �������-����λ��
                                        */
INT16U DrMtr_ResBackReqPosi;           /* '<S27>/DrMtr_ResBackReqPosi'
                                        * С����-����λ��
                                        */
INT16U DrMtr_ResFrontReqPosi;          /* '<S27>/DrMtr_ResFrontReqPosi'
                                        * С����-ǰ��λ��
                                        */
INT16U DrMtr_ResHeightReqPosi;         /* '<S27>/DrMtr_ResHeightReqPosi'
                                        * С����-�߶�λ��
                                        */
INT16U DrMtr_ResLengthReqPosi;         /* '<S27>/DrMtr_ResLengthReqPosi'
                                        * С����-����λ��
                                        */
INT16U DrMtr_ResetBackReqPosi;         /* '<S27>/DrMtr_ResetBackReqPosi'
                                        * ��λ����-����λ��
                                        */
INT16U DrMtr_ResetFrontReqPosi;        /* '<S27>/DrMtr_ResetFrontReqPosi'
                                        * ��λ����-ǰ��λ��
                                        */
INT16U DrMtr_ResetHeightReqPosi;       /* '<S27>/DrMtr_ResetHeightReqPosi'
                                        * ��λ����-�߶�λ��
                                        */
INT16U DrMtr_ResetLengthReqPosi;       /* '<S27>/DrMtr_ResetLengthReqPosi'
                                        * ��λ����-����λ��
                                        */
INT16U DrMtr_WelcomeBackReqPosi;       /* '<S27>/DrMtr_WelcomeBackReqPosi'
                                        * ӭ������-����λ��
                                        */
INT16U DrMtr_WelcomeLengthReqPosi;     /* '<S27>/DrMtr_WelcomeLengthReqPosi'
                                        * ӭ������-����λ��
                                        */
INT8U DrMtr_AnyoneHallErr;             /* '<S27>/DrMtr_AnyoneHallErr'
                                        * ��һ�������ϱ�־
                                        */
INT8U DrMtr_AnyoneRelayAdheErr;        /* '<S27>/DrMtr_AnyoneRelayAdheErr'
                                        * ��һ�̵���ճ�����ϱ�־
                                        */
INT8U DrMtr_BackHallErr;               /* '<S27>/DrMtr_BackHallErr'
                                        * ���������ϱ�־λ
                                        */
INT8U DrMtr_BackLearnCmd;              /* '<S27>/DrMtr_BackLearnCmd'
                                        * ѧϰ��������-����
                                        */
INT8U DrMtr_BackMotorTimeOutErr;       /* '<S27>/DrMtr_BackMotorTimeOutErr'
                                        * ����������г�ʱ��־
                                        */
INT8U DrMtr_BackRelayAdhesionErr;      /* '<S27>/DrMtr_BackRelayAdhesionErr'
                                        * �����̵���ճ����־λ
                                        */
INT8U DrMtr_BackSoftStopErr;           /* '<S27>/DrMtr_BackSoftStopErr'
                                        * ����������ֹ��
                                        */
INT8U DrMtr_BackStallErr;              /* '<S27>/DrMtr_BackStallErr'
                                        * ������ת��־λ
                                        */
INT8U DrMtr_BackSwitchAdheErr;         /* '<S27>/DrMtr_BackSwitchAdheErr'
                                        * ��������ճ�����ϱ�־λ
                                        */
INT8U DrMtr_BackSwitchCmd;             /* '<S27>/DrMtr_BackSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
INT8U DrMtr_DiagnoseLearnIn;           /* '<S27>/DrMtr_DiagnoseLearnIn'
                                        * ����ѧϰ��־
                                        */
INT8U DrMtr_FrontHallErr;              /* '<S27>/DrMtr_FrontHallErr'
                                        * ���л����ϱ�־λ
                                        */
INT8U DrMtr_FrontLearnCmd;             /* '<S27>/DrMtr_FrontLearnCmd'
                                        * ѧϰ��������-����
                                        */
INT8U DrMtr_FrontMotorTimeOutErr;      /* '<S27>/DrMtr_FrontMotorTimeOutErr'
                                        * ���е�����г�ʱ��־
                                        */
INT8U DrMtr_FrontRelayAdhesionErr;     /* '<S27>/DrMtr_FrontRelayAdhesionErr'
                                        * ���м̵���ճ����־λ
                                        */
INT8U DrMtr_FrontSoftStopErr;          /* '<S27>/DrMtr_FrontSoftStopErr'
                                        * ���е�����ֹ��
                                        */
INT8U DrMtr_FrontStallErr;             /* '<S27>/DrMtr_FrontStallErr'
                                        * ���ж�ת��־λ
                                        */
INT8U DrMtr_FrontSwitchAdheErr;        /* '<S27>/DrMtr_FrontSwitchAdheErr'
                                        * ���п���ճ�����ϱ�־λ
                                        */
INT8U DrMtr_FrontSwitchCmd;            /* '<S27>/DrMtr_FrontSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
INT8U DrMtr_HeightHallErr;             /* '<S27>/DrMtr_HeightHallErr'
                                        * �߶Ȼ����ϱ�־λ
                                        */
INT8U DrMtr_HeightLearnCmd;            /* '<S27>/DrMtr_HeightLearnCmd'
                                        * ѧϰ��������-�߶�
                                        */
INT8U DrMtr_HeightMotorTimeOutErr;     /* '<S27>/DrMtr_HeightMotorTimeOutErr'
                                        * �߶ȵ�����г�ʱ��־
                                        */
INT8U DrMtr_HeightRelayAdhesionErr;    /* '<S27>/DrMtr_HeightRelayAdhesionErr'
                                        * �߶ȼ̵���ճ����־λ
                                        */
INT8U DrMtr_HeightSoftStopErr;         /* '<S27>/DrMtr_HeightSoftStopErr'
                                        * �߶ȵ�����ֹ��
                                        */
INT8U DrMtr_HeightStallErr;            /* '<S27>/DrMtr_HeightStallErr'
                                        * �߶ȶ�ת��־λ
                                        */
INT8U DrMtr_HeightSwitchAdheErr;       /* '<S27>/DrMtr_HeightSwitchAdheErr'
                                        * �߶ȿ���ճ�����ϱ�־λ
                                        */
INT8U DrMtr_HeightSwitchCmd;           /* '<S27>/DrMtr_HeightSwitchCmd'
                                        * Ӳ�߿�����������-�߶�
                                        */
INT8U DrMtr_LearnSts;                  /* '<S27>/DrMtr_LearnSts'
                                        * ѧϰ״̬
                                        */
INT8U DrMtr_LengthHallErr;             /* '<S27>/DrMtr_LengthHallErr'
                                        * ��������ϱ�־λ
                                        */
INT8U DrMtr_LengthLearnCmd;            /* '<S27>/DrMtr_LengthLearnCmd'
                                        * ѧϰ��������-����
                                        */
INT8U DrMtr_LengthMotorTimeOutErr;     /* '<S27>/DrMtr_LengthMotorTimeOutErr'
                                        * ���������г�ʱ��־
                                        */
INT8U DrMtr_LengthRelayAdhesionErr;    /* '<S27>/DrMtr_LengthRelayAdhesionErr'
                                        * ����̵���ճ����־λ
                                        */
INT8U DrMtr_LengthSoftStopErr;         /* '<S27>/DrMtr_LengthSoftStopErr'
                                        * ���򵽴���ֹ��
                                        */
INT8U DrMtr_LengthStallErr;            /* '<S27>/DrMtr_LengthStallErr'
                                        * �����ת��־λ
                                        */
INT8U DrMtr_LengthSwitchAdheErr;       /* '<S27>/DrMtr_LengthSwitchAdheErr'
                                        * ���򿪹�ճ�����ϱ�־λ
                                        */
INT8U DrMtr_LengthSwitchCmd;           /* '<S27>/DrMtr_LengthSwitchCmd'
                                        * Ӳ�߿�����������-����
                                        */
INT8U DrMtr_VoltSatisfy;               /* '<S27>/DrMtr_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */

/* Block signals (default storage) */
B_Appl_DrMotorAdjust_CtrlModel_T Appl_DrMotorAdjust_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_DrMotorAdjust_CtrlModel_T Appl_DrMotorAdjust_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_DrMotorAdjust_CtrlModel_T Appl_DrMotorAdjust_CtrlModel_M_;
RT_MODEL_Appl_DrMotorAdjust_CtrlModel_T *const Appl_DrMotorAdjust_CtrlModel_M =
  &Appl_DrMotorAdjust_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT8U CAL_HightMotorRunInterval_100ms = 10U;/* ������ڼ��ʱ��100ms */
const volatile INT16U CAL_MotorDiffToStart_100ms = 10U;/* ��ͬ����������ʱ��100ms */
static void Appl_DrMotorAdjust_CtrlModel_LogicCtrl_Init(void);
static void Appl_DrMotorAdjust_CtrlModel_LogicCtrl(void);
static void Appl_DrMotorAdjust_CtrlModel_RTE(void);
static void Appl_DrMotorAdjust_CtrlModel_UpDataInputInfo(void);
static void Appl_DrMotorAdjust_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_DrMotorAdju_inner_default_MotorAdjPriorityPro(INT16U
  *SeatHeightPosiReq, INT16U *SeatLengthPosiReq, INT16U *SeatBackPosiReq, INT16U
  *SeatFrontPosiReq, INT8U *HeightManualAdjSw, INT8U *LengthManualAdjSw);
static INT32S Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts(INT32S input);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_m(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_a(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_e(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_n(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun(const INT16U
  *SeatBackPosiReq, enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye
  *MotorActType_prev_pa);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun(const INT16U
  *SeatBackPosiReq, enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye
  *MotorActType_prev_pa);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_j(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq);
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_l(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq);

/* Function for Chart: '<S6>/MotorAdjustmentPriorityProcessing1' */
static void Appl_DrMotorAdju_inner_default_MotorAdjPriorityPro(INT16U
  *SeatHeightPosiReq, INT16U *SeatLengthPosiReq, INT16U *SeatBackPosiReq, INT16U
  *SeatFrontPosiReq, INT8U *HeightManualAdjSw, INT8U *LengthManualAdjSw)
{
  /* �޹�������״̬ */
  Appl_DrMotorAdjust_CtrlModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
  *HeightManualAdjSw = 0U;
  *LengthManualAdjSw = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
  *SeatHeightPosiReq = 0U;
  *SeatLengthPosiReq = 0U;
  *SeatBackPosiReq = 0U;
  *SeatFrontPosiReq = 0U;
  if ((0 != DrMtr_WelcomeLengthReqPosi) || (0 != DrMtr_WelcomeBackReqPosi))
  {
    /* ���ʵ���������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_ComfortEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = DrMtr_WelcomeLengthReqPosi;
    *SeatBackPosiReq = DrMtr_WelcomeBackReqPosi;
    *SeatFrontPosiReq = 0U;
  }

  if ((0 != DrMtr_MemoryHeightReqPosi) || (0 != DrMtr_MemoryLengthReqPosi) || (0
       != DrMtr_MemoryBackReqPosi) || (0 != DrMtr_MemoryFrontReqPosi))
  {
    /* �������������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_MemoryEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = DrMtr_MemoryHeightReqPosi;
    *SeatLengthPosiReq = DrMtr_MemoryLengthReqPosi;
    *SeatBackPosiReq = DrMtr_MemoryBackReqPosi;
    *SeatFrontPosiReq = DrMtr_MemoryFrontReqPosi;
  }

  if ((0 != DrMtr_ResHeightReqPosi) || (0 != DrMtr_ResLengthReqPosi) || (0 !=
       DrMtr_ResBackReqPosi) || (0 != DrMtr_ResFrontReqPosi))
  {
    /* С�������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_ResEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = DrMtr_ResHeightReqPosi;
    *SeatLengthPosiReq = DrMtr_ResLengthReqPosi;
    *SeatBackPosiReq = DrMtr_ResBackReqPosi;
    *SeatFrontPosiReq = DrMtr_ResFrontReqPosi;
  }

  /*   */
  if ((0 != DrMtr_ResetHeightReqPosi) || (0 != DrMtr_ResetLengthReqPosi) || (0
       != DrMtr_ResetBackReqPosi) || (0 != DrMtr_ResetFrontReqPosi))
  {
    /* ��λ������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_ResetEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = DrMtr_ResetHeightReqPosi;
    *SeatLengthPosiReq = DrMtr_ResetLengthReqPosi;
    *SeatBackPosiReq = DrMtr_ResetBackReqPosi;
    *SeatFrontPosiReq = DrMtr_ResetFrontReqPosi;
  }

  if ((0 != DrMtr_HeightLearnCmd) || (0 != DrMtr_LengthLearnCmd) || (0 !=
       DrMtr_BackLearnCmd) || (0 != DrMtr_FrontLearnCmd))
  {
    /* ѧϰ������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_LearnEnable;
    *HeightManualAdjSw = DrMtr_HeightLearnCmd;
    *LengthManualAdjSw = DrMtr_LengthLearnCmd;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = DrMtr_BackLearnCmd;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = DrMtr_FrontLearnCmd;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = 0U;
    *SeatBackPosiReq = 0U;
    *SeatFrontPosiReq = 0U;
  }

  if ((0 != DrMtr_HeightSwitchCmd) || (0 != DrMtr_LengthSwitchCmd) || (0 !=
       DrMtr_BackSwitchCmd) || (0 != DrMtr_FrontSwitchCmd))
  {
    /* �ֶ�������Ч */
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType =
      enSeatMotorRunTye_EN_ManualEnable;
    *HeightManualAdjSw = DrMtr_HeightSwitchCmd;
    *LengthManualAdjSw = DrMtr_LengthSwitchCmd;
    Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = DrMtr_BackSwitchCmd;
    Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = DrMtr_FrontSwitchCmd;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = 0U;
    *SeatBackPosiReq = 0U;
    *SeatFrontPosiReq = 0U;
  }
}

static INT32S Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enSeatHightMotorRunsts (EN_NULL) */
  y = 0;
  if ((input >= 0) && (input <= 28))
  {
    /* Set output value to input value if it is a member of enSeatHightMotorRunsts */
    y = input;
  }

  return y;
}

/* Function for Chart: '<S20>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_m(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

  /* �߶ȿ������͸ı�
     ���ȼ���Ҫ�趨Ϊ1 */
  if ((*MotorActType_prev_i !=
       Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_b) &&
      (enSeatMotorRunTye_EN_NULL !=
       Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g) && (q1 ==
         DrMtr_HeightSoftStopErr))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
    }
    else
    {
      /* �߶��Զ�������Ч ���õ����������BKֹͣ �Զ����б�־λʧ�� */
      if ((0 == *SeatHeightPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
          enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
      }
      else
      {
        /* �Զ����ڳɹ� ���õ���������ͳɹ�ֹͣ �Զ����б�־λ�ɹ� */
        tmp = DrMtr_HeightHallPosi - *SeatHeightPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
        }
        else
        {
          /*  ������ֹ�� �ҳ�����Χ����Ҫ��ǰ����  */
          if ((0 != *SeatHeightPosiReq) && (*SeatHeightPosiReq >
               DrMtr_HeightHallPosi))
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
          }
          else
          {
            /*  �߶���󵽴�ֹ�㣬���ڶ�ת���ϣ������ɹ�
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == DrMtr_HeightStallErr)
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
            }
            else
            {
              /* �߶��ֶ�������Ч */
              if ((q1 != *HeightManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
              {
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
              }
              else
              {
                /* �߶ȳ�ʱֹͣ-�Ǽ̵���ճ�������� */
                if ((((BOOL)TRUE) == DrMtr_HeightMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != DrMtr_HeightRelayAdhesionErr))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                }
                else
                {
                  /* �߶ȼ̵�����ǰճ������ ��= ��Ч */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       DrMtr_HeightRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                  }
                  else
                  {
                    /*  ���ڻ�������
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == DrMtr_HeightHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                    }
                    else
                    {
                      /*  �߶ȴ���MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_HeigthMotorMosErr)
                      {
                        q1 = DrMtr_HeigthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                      }
                      else
                      {
                        /* �߶��Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S20>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_a(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw)
{
  INT32S q1;
  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

  /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g) && (q1 ==
       DrMtr_HeightSoftStopErr))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
      enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    /* �߶ȿ������͸ı�
       ���ܷ����˶��ɹ����ȼ���Ҫ�趨Ϊ1 */
    if ((*MotorActType_prev_i !=
         Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_b) &&
        (enSeatMotorRunTye_EN_NULL !=
         Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
    }
    else
    {
      /* �߶ȼ̵����º�ճ������ != ��Ч */
      if ((((INT8U)D_Relay_DownBackFault) != DrMtr_HeightRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
      }
      else
      {
        /*  �߶���ǰ����ֹ�㣬���ڶ�ת���ϣ������ɹ�
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == DrMtr_HeightStallErr)
        {
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
        }
        else
        {
          /* �߶��ֶ�������Ч */
          if ((q1 != *HeightManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
          {
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
          }
          else
          {
            /* �߶��Զ�������Ч ���õ����������FUֹͣ �Զ����б�־λʧ�� */
            if ((0 == *SeatHeightPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g))
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
            }
            else
            {
              /* �߶��Զ����ڳɹ� ���õ����������FU�ɹ�ֹͣ �Զ����б�־λ�ɹ� */
              q1 = *SeatHeightPosiReq - DrMtr_HeightHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
              }
              else
              {
                /*  ������ֹ�� �ҳ�����Χ����Ҫ�������  */
                if ((0 != *SeatHeightPosiReq) && (*SeatHeightPosiReq <
                     DrMtr_HeightHallPosi))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                }
                else
                {
                  /* ��ʱֹͣ-�Ǽ̵���ճ�������� */
                  if ((((BOOL)TRUE) == DrMtr_HeightMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != DrMtr_HeightRelayAdhesionErr))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                  }
                  else
                  {
                    /*  �߶ȴ��ڻ�������
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == DrMtr_HeightHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                    }
                    else
                    {
                      /*  �߶ȴ���MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_HeigthMotorMosErr)
                      {
                        q1 = DrMtr_HeigthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
                      }
                      else
                      {
                        /* �Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S21>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_e(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

  /* ����������͸ı�
     ���ȼ���Ҫ�趨Ϊ1 */
  if ((*MotorActType_prev != Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start)
      && (enSeatMotorRunTye_EN_NULL !=
          Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType) && (q1 ==
         DrMtr_LengthSoftStopErr))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
    }
    else
    {
      /* �����Զ�������Ч ���õ����������BKֹͣ �Զ����б�־λʧ�� */
      if ((0 == *SeatLengthPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
          enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
      }
      else
      {
        /* �Զ����ڳɹ� ���õ���������ͳɹ�ֹͣ �Զ����б�־λ�ɹ� */
        tmp = DrMtr_LengthHallPosi - *SeatLengthPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
        }
        else
        {
          /*  ������ֹ�� �ҳ�����Χ����Ҫ��ǰ����  */
          if ((0 != *SeatLengthPosiReq) && (*SeatLengthPosiReq >
               DrMtr_LengthHallPosi))
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
          }
          else
          {
            /*  ������󵽴�ֹ�㣬���ڶ�ת���ϣ������ɹ�
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == DrMtr_LengthStallErr)
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
            }
            else
            {
              /* �����ֶ�������Ч */
              if ((q1 != *LengthManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
              {
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
              }
              else
              {
                /* ����ʱֹͣ-�Ǽ̵���ճ�������� */
                if ((((BOOL)TRUE) == DrMtr_LengthMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != DrMtr_LengthRelayAdhesionErr))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                }
                else
                {
                  /* ����̵�����ǰճ������ ��= ��Ч */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       DrMtr_LengthRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                  }
                  else
                  {
                    /*  ���ڻ�������
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == DrMtr_LengthHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                    }
                    else
                    {
                      /*  ����MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_LengthMotorMosErr)
                      {
                        q1 = DrMtr_LengthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                      }
                      else
                      {
                        /* �����Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S21>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_n(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw)
{
  INT32S q1;
  *H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

  /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType) && (q1 ==
       DrMtr_LengthSoftStopErr))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
      enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    /* ����������͸ı�
       ���ܷ����˶��ɹ����ȼ���Ҫ�趨Ϊ1 */
    if ((*MotorActType_prev !=
         Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start) &&
        (enSeatMotorRunTye_EN_NULL !=
         Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
    }
    else
    {
      /* ����̵����º�ճ������ != ��Ч */
      if ((((INT8U)D_Relay_DownBackFault) != DrMtr_LengthRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
      }
      else
      {
        /*  ������ǰ����ֹ�㣬���ڶ�ת���ϣ������ɹ�
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == DrMtr_LengthStallErr)
        {
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
        }
        else
        {
          /* �����ֶ�������Ч */
          if ((q1 != *LengthManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
          {
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
          }
          else
          {
            /* �����Զ�������Ч ���õ����������FUֹͣ �Զ����б�־λʧ�� */
            if ((0 == *SeatLengthPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType))
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
            }
            else
            {
              /* �����Զ����ڳɹ� ���õ����������FU�ɹ�ֹͣ �Զ����б�־λ�ɹ� */
              q1 = *SeatLengthPosiReq - DrMtr_LengthHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
              }
              else
              {
                /*  ������ֹ�� �ҳ�����Χ����Ҫ�������  */
                if ((0 != *SeatLengthPosiReq) && (*SeatLengthPosiReq <
                     DrMtr_LengthHallPosi))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                }
                else
                {
                  /* ����ʱֹͣ-�Ǽ̵���ճ�������� */
                  if ((((BOOL)TRUE) == DrMtr_LengthMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != DrMtr_LengthRelayAdhesionErr))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                  }
                  else
                  {
                    /*  ������ڻ�������
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == DrMtr_LengthHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                    }
                    else
                    {
                      /*  �������MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_LengthMotorMosErr)
                      {
                        q1 = DrMtr_LengthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
                      }
                      else
                      {
                        /* �Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S18>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun(const INT16U
  *SeatBackPosiReq, enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye
  *MotorActType_prev_pa)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

  /* �����������͸ı�
     ���ȼ���Ҫ�趨Ϊ1 */
  if ((*MotorActType_prev_pa !=
       Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_n) &&
      (enSeatMotorRunTye_EN_NULL !=
       Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m) && (q1 ==
         DrMtr_BackSoftStopErr))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
    }
    else
    {
      /* �����Զ�������Ч ���õ����������BKֹͣ �Զ����б�־λʧ�� */
      if ((0 == *SeatBackPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
          enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
      }
      else
      {
        /* �Զ����ڳɹ� ���õ���������ͳɹ�ֹͣ �Զ����б�־λ�ɹ� */
        tmp = DrMtr_BackHallPosi - *SeatBackPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
        }
        else
        {
          /*  ������ֹ�� �ҳ�����Χ����Ҫ��ǰ����  */
          if ((0 != *SeatBackPosiReq) && (*SeatBackPosiReq > DrMtr_BackHallPosi))
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
          }
          else
          {
            /*  ������󵽴�ֹ�㣬���ڶ�ת���ϣ������ɹ�
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == DrMtr_BackStallErr)
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
            }
            else
            {
              /* �����ֶ�������Ч */
              if ((q1 != Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
              {
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
              }
              else
              {
                /* ������ʱֹͣ-�Ǽ̵���ճ�������� */
                if ((((BOOL)TRUE) == DrMtr_BackMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != DrMtr_BackRelayAdhesionErr))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                }
                else
                {
                  /* �����̵�����ǰճ������ ��= ��Ч */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       DrMtr_BackRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                  }
                  else
                  {
                    /*  ���ڻ�������
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == DrMtr_BackHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                    }
                    else
                    {
                      /*  ����MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_BackMotorMosErr)
                      {
                        q1 = DrMtr_BackMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                      }
                      else
                      {
                        /* �����Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S18>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun(const INT16U
  *SeatBackPosiReq, enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye
  *MotorActType_prev_pa)
{
  INT32S q1;
  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

  /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m) && (q1 ==
       DrMtr_BackSoftStopErr))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
      enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    /* �����������͸ı�
       ���ܷ����˶��ɹ����ȼ���Ҫ�趨Ϊ1 */
    if ((*MotorActType_prev_pa !=
         Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_n) &&
        (enSeatMotorRunTye_EN_NULL !=
         Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
    }
    else
    {
      /* �����̵����º�ճ������ != ��Ч */
      if ((((INT8U)D_Relay_DownBackFault) != DrMtr_BackRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
      }
      else
      {
        /*  ������ǰ����ֹ�㣬���ڶ�ת���ϣ������ɹ�
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == DrMtr_BackStallErr)
        {
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
        }
        else
        {
          /* �����ֶ�������Ч */
          if ((q1 != Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
          {
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
          }
          else
          {
            /* �����Զ�������Ч ���õ����������FUֹͣ �Զ����б�־λʧ�� */
            if ((0 == *SeatBackPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m))
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
            }
            else
            {
              /* �����Զ����ڳɹ� ���õ����������FU�ɹ�ֹͣ �Զ����б�־λ�ɹ� */
              q1 = *SeatBackPosiReq - DrMtr_BackHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
              }
              else
              {
                /*  ������ֹ�� �ҳ�����Χ����Ҫ�������  */
                if ((0 != *SeatBackPosiReq) && (*SeatBackPosiReq <
                     DrMtr_BackHallPosi))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                }
                else
                {
                  /* ������ʱֹͣ-�Ǽ̵���ճ�������� */
                  if ((((BOOL)TRUE) == DrMtr_BackMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != DrMtr_BackRelayAdhesionErr))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                  }
                  else
                  {
                    /*  �������ڻ�������
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == DrMtr_BackHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                    }
                    else
                    {
                      /*  ��������MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_BackMotorMosErr)
                      {
                        q1 = DrMtr_BackMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
                      }
                      else
                      {
                        /* �Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S19>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_j(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

  /* ���п������͸ı�
     ���ȼ���Ҫ�趨Ϊ1 */
  if ((*MotorActType_prev_p !=
       Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_l) &&
      (enSeatMotorRunTye_EN_NULL !=
       Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l) && (q1 ==
         DrMtr_FrontSoftStopErr))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
    }
    else
    {
      /* �����Զ�������Ч ���õ����������BKֹͣ �Զ����б�־λʧ�� */
      if ((0 == *SeatFrontPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
          enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
      }
      else
      {
        /* �Զ����ڳɹ� ���õ���������ͳɹ�ֹͣ �Զ����б�־λ�ɹ� */
        tmp = DrMtr_FrontHallPosi - *SeatFrontPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
        }
        else
        {
          /*  ������ֹ�� �ҳ�����Χ����Ҫ��ǰ����  */
          if ((0 != *SeatFrontPosiReq) && (*SeatFrontPosiReq >
               DrMtr_FrontHallPosi))
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
          }
          else
          {
            /*  ������󵽴�ֹ�㣬���ڶ�ת���ϣ������ɹ�
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == DrMtr_FrontStallErr)
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
            }
            else
            {
              /* �����ֶ�������Ч */
              if ((q1 != Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
              {
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
              }
              else
              {
                /* ���г�ʱֹͣ-�Ǽ̵���ճ�������� */
                if ((((BOOL)TRUE) == DrMtr_FrontMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != DrMtr_FrontRelayAdhesionErr))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                }
                else
                {
                  /* ���м̵�����ǰճ������ ��= ��Ч */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       DrMtr_FrontRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                  }
                  else
                  {
                    /*  ���ڻ�������
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == DrMtr_FrontHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                    }
                    else
                    {
                      /*  ����MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_FrontMotorMosErr)
                      {
                        q1 = DrMtr_FrontMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                      }
                      else
                      {
                        /* �����Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S19>/MotorAdjust' */
static void Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_l(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq)
{
  INT32S q1;
  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

  /* �Զ�����-������ֹ��ֹͣ �ɹ�  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l) && (q1 ==
       DrMtr_FrontSoftStopErr))
  {
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
      enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    /* ���п������͸ı�
       ���ܷ����˶��ɹ����ȼ���Ҫ�趨Ϊ1 */
    if ((*MotorActType_prev_p !=
         Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_l) &&
        (enSeatMotorRunTye_EN_NULL !=
         Appl_DrMotorAdjust_CtrlModel_B.MotorActionType))
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
    }
    else
    {
      /* ���м̵����º�ճ������ != ��Ч */
      if ((((INT8U)D_Relay_DownBackFault) != DrMtr_FrontRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
      {
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
      }
      else
      {
        /*  ������ǰ����ֹ�㣬���ڶ�ת���ϣ������ɹ�
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == DrMtr_FrontStallErr)
        {
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
          *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
          Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
          Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
        }
        else
        {
          /* �����ֶ�������Ч */
          if ((q1 != Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
          {
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
            *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
            Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
            Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
          }
          else
          {
            /* �����Զ�������Ч ���õ����������FUֹͣ �Զ����б�־λʧ�� */
            if ((0 == *SeatFrontPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l))
            {
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
              *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
              Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
              Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
            }
            else
            {
              /* �����Զ����ڳɹ� ���õ����������FU�ɹ�ֹͣ �Զ����б�־λ�ɹ� */
              q1 = *SeatFrontPosiReq - DrMtr_FrontHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
              }
              else
              {
                /*  ������ֹ�� �ҳ�����Χ����Ҫ�������  */
                if ((0 != *SeatFrontPosiReq) && (*SeatFrontPosiReq <
                     DrMtr_FrontHallPosi))
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                }
                else
                {
                  /* ���г�ʱֹͣ-�Ǽ̵���ճ�������� */
                  if ((((BOOL)TRUE) == DrMtr_FrontMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != DrMtr_FrontRelayAdhesionErr))
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                      = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
                    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                  }
                  else
                  {
                    /*  ���д��ڻ�������
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == DrMtr_FrontHallErr)
                    {
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                        = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f =
                        1U;
                      Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                    }
                    else
                    {
                      /*  ���д���MOS����  */
                      if (enMosErrSts_enNULL != DrMtr_FrontMotorMosErr)
                      {
                        q1 = DrMtr_FrontMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_DrMotorAd_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                          = Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
                        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f =
                          1U;
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                        Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
                      }
                      else
                      {
                        /* �Զ����� */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrMotorAdjust_CtrlModel_LogicCtrl_Init(void)
{
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c2_Appl_DrMotorAdjust_CtrlModel = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
  Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c4_Appl_DrMotorAdjust_CtrlModel = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 10U;
  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
    enSeatHightMotorRunsts_EN_NULL;
  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
    enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c18_Appl_DrMotorAdjust_CtrlModel =
    0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 10U;
  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType = enSeatHightMotorRunsts_EN_NULL;
  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
    enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c19_Appl_DrMotorAdjust_CtrlModel =
    0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 10U;
  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
    enSeatHightMotorRunsts_EN_NULL;
  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
    enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c21_Appl_DrMotorAdjust_CtrlModel =
    0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 10U;
  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
    enSeatHightMotorRunsts_EN_NULL;
  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
    enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c17_Appl_DrMotorAdjust_CtrlModel =
    0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_c17_Appl_DrMotorAdjust_CtrlModel = 0;
  Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.is_BackAdjust = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.is_FrontAngleAdjust = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.is_HeightAdjust = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.is_VerticalAdjust = 0;
  Appl_DrMotorAdjust_CtrlModel_DW.is_active_c16_Appl_DrMotorAdjust_CtrlModel =
    0U;
  Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = 0U;
  Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl = 0U;
  Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrMotorAdjust_CtrlModel_LogicCtrl(void)
{
  INT16U SeatHeightPosiReq;
  INT16U SeatLengthPosiReq;
  INT16U SeatBackPosiReq;
  enSeatMoveCmd H_SeatMoveCmd_i;
  enSeatMoveCmd H_SeatMoveCmd;
  enSeatMoveCmd H_SeatMoveCmd_e;
  enSeatMoveCmd H_SeatMoveCmd_p;
  INT16U SeatHeightPosiReq_prev_j;
  enSeatMotorRunTye MotorActType_prev_i;
  INT16U SeatFrontPosiReq;
  INT8U HeightManualAdjSw;
  INT8U LengthManualAdjSw;
  INT32S tmp;
  INT32S tmp_0;
  INT32S tmp_1;
  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c2_Appl_DrMotorAdjust_CtrlModel ==
      0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c2_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdju_inner_default_MotorAdjPriorityPro(&SeatHeightPosiReq,
      &SeatLengthPosiReq, &SeatBackPosiReq, &SeatFrontPosiReq,
      &HeightManualAdjSw, &LengthManualAdjSw);
  }
  else
  {
    Appl_DrMotorAdju_inner_default_MotorAdjPriorityPro(&SeatHeightPosiReq,
      &SeatLengthPosiReq, &SeatBackPosiReq, &SeatFrontPosiReq,
      &HeightManualAdjSw, &LengthManualAdjSw);
  }

  SeatHeightPosiReq_prev_j =
    Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_o;
  Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_o = SeatHeightPosiReq;
  MotorActType_prev_i = Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_b;
  Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_b =
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType;
  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c4_Appl_DrMotorAdjust_CtrlModel ==
      0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c4_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    switch (Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel)
    {
     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_m(&SeatHeightPosiReq,
        &H_SeatMoveCmd_i, &MotorActType_prev_i, &HeightManualAdjSw);
      break;

     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_a(&SeatHeightPosiReq,
        &H_SeatMoveCmd_i, &MotorActType_prev_i, &HeightManualAdjSw);
      break;

     default:
      H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;

      /* �߶ȼ̵�����ǰճ������ == ��Ч */
      if ((((INT8U)D_Relay_UpFrontFault) == DrMtr_HeightRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

        /* �߶��Զ����� */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* �߶��Զ�������Ч�Ҳ�����Χ�� */
        if ((0 != SeatHeightPosiReq) && (((BOOL)FALSE) == DrMtr_HeightStallErr) &&
            (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

          /* �߶��Զ����� */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* �߶��ֶ����� */
          tmp_0 = enSeatMoveCmd_EN_UP_FORWARD;
          if ((tmp_0 == HeightManualAdjSw) && (((BOOL)FALSE) ==
               DrMtr_HeightStallErr) && (((BOOL)FALSE) == DrMtr_HeightHallErr) &&
              (((BOOL)FALSE) == DrMtr_HeightMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
          {
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

            /* �Զ����� */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* �߶ȼ̵����º�ճ������ == ��Ч ���ʱ�����100ms */
            if ((((INT8U)D_Relay_DownBackFault) == DrMtr_HeightRelayAdhesionErr)
                && (CAL_HightMotorRunInterval_100ms <=
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
            {
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

              /* �Զ����� */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* �߶��Զ�������Ч�Ҳ�����Χ�� */
              if ((0 != SeatHeightPosiReq) && (((BOOL)FALSE) ==
                   DrMtr_HeightStallErr) &&
                  (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
              {
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

                /* �Զ����� */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* �߶��ֶ�������Ч */
                tmp_1 = enSeatMoveCmd_EN_DN_BACKWARD;
                if ((tmp_1 == HeightManualAdjSw) && (((BOOL)FALSE) ==
                     DrMtr_HeightStallErr) && (((BOOL)FALSE) ==
                     DrMtr_HeightHallErr) && (((BOOL)FALSE) ==
                     DrMtr_HeightMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e))
                {
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e = 0U;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c4_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* �߶��Զ����� */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* �߶ȵ�������ʱ�� */
                  if (Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp =
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e +
                      1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_e =
                      (INT8U)tmp;
                  }

                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 0U;

                  /* �߶��Զ�������Ч */
                  if (0 != SeatHeightPosiReq)
                  {
                    /* �߶�����ж�Ŀǰ����Ϊ5������ֵ */
                    if ((tmp_0 != DrMtr_HeightSoftStopErr) && (SeatHeightPosiReq
                         > DrMtr_HeightHallPosi) && (((INT16U)
                          D_ToleranceDistance) < SeatHeightPosiReq -
                         DrMtr_HeightHallPosi))
                    {
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_g = 1U;
                    }
                    else
                    {
                      /*  ������ֹ�� �ҳ���Χ  */
                      if ((tmp_1 != DrMtr_HeightSoftStopErr) &&
                          (SeatHeightPosiReq < DrMtr_HeightHallPosi) &&
                          (((INT16U)D_ToleranceDistance) < DrMtr_HeightHallPosi
                           - SeatHeightPosiReq))
                      {
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_k = 1U;
                      }
                      else
                      {
                        /* �߶���Χ�ڣ������ɹ� */
                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  ����λ���б仯 ������״̬  */
                  if (SeatHeightPosiReq_prev_j !=
                      Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_o)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
              }
            }
          }
        }
      }
      break;
    }
  }

  SeatHeightPosiReq = Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start;
  Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start = SeatLengthPosiReq;
  MotorActType_prev_i = Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start;
  Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start =
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType;
  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c18_Appl_DrMotorAdjust_CtrlModel
      == 0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c18_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    switch (Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel)
    {
     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_e(&SeatLengthPosiReq,
        &H_SeatMoveCmd, &MotorActType_prev_i, &LengthManualAdjSw);
      break;

     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_n(&SeatLengthPosiReq,
        &H_SeatMoveCmd, &MotorActType_prev_i, &LengthManualAdjSw);
      break;

     default:
      H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;

      /* ����̵�����ǰճ������ == ��Ч */
      if ((((INT8U)D_Relay_UpFrontFault) == DrMtr_LengthRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

        /* �����Զ����� */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* �����Զ�������Ч�Ҳ�����Χ�� */
        if ((0 != SeatLengthPosiReq) && (((BOOL)FALSE) == DrMtr_LengthStallErr) &&
            (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

          /* �����Զ����� */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* �����ֶ����� */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD == LengthManualAdjSw) &&
              (((BOOL)FALSE) == DrMtr_LengthStallErr) && (((BOOL)FALSE) ==
               DrMtr_LengthHallErr) && (((BOOL)FALSE) ==
               DrMtr_LengthMotorTimeOutErr) && (CAL_HightMotorRunInterval_100ms <=
               Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
          {
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

            /* �Զ����� */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* ����̵����º�ճ������ == ��Ч ���ʱ�����100ms */
            if ((((INT8U)D_Relay_DownBackFault) == DrMtr_LengthRelayAdhesionErr)
                && (CAL_HightMotorRunInterval_100ms <=
                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
            {
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

              /* �Զ����� */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* �����Զ�������Ч�Ҳ�����Χ�� */
              if ((0 != SeatLengthPosiReq) && (((BOOL)FALSE) ==
                   DrMtr_LengthStallErr) &&
                  (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
              {
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

                /* �Զ����� */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* �����ֶ�������Ч */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD == LengthManualAdjSw) &&
                    (((BOOL)FALSE) == DrMtr_LengthStallErr) && (((BOOL)FALSE) ==
                     DrMtr_LengthHallErr) && (((BOOL)FALSE) ==
                     DrMtr_LengthMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime))
                {
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime = 0U;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c18_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* �����Զ����� */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* �����������ʱ�� */
                  if (Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 =
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime + 1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime =
                      (INT8U)tmp_0;
                  }

                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 0U;

                  /* �����Զ�������Ч */
                  if (0 != SeatLengthPosiReq)
                  {
                    /* ��������ж�Ŀǰ����Ϊ5������ֵ */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         DrMtr_LengthSoftStopErr) && (SeatLengthPosiReq >
                         DrMtr_LengthHallPosi) && (((INT16U)D_ToleranceDistance)
                         < SeatLengthPosiReq - DrMtr_LengthHallPosi))
                    {
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag = 1U;
                    }
                    else
                    {
                      /*  ������ֹ�� �ҳ���Χ  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           DrMtr_LengthSoftStopErr) && (SeatLengthPosiReq <
                           DrMtr_LengthHallPosi) && (((INT16U)
                            D_ToleranceDistance) < DrMtr_LengthHallPosi -
                           SeatLengthPosiReq))
                      {
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag = 1U;
                      }
                      else
                      {
                        /* ������Χ�ڣ������ɹ� */
                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  ����λ���б仯 ������״̬  */
                  if (SeatHeightPosiReq !=
                      Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
              }
            }
          }
        }
      }
      break;
    }
  }

  SeatLengthPosiReq = Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_j;
  Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_j = SeatBackPosiReq;
  MotorActType_prev_i = Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_n;
  Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_n =
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType;
  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c19_Appl_DrMotorAdjust_CtrlModel
      == 0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c19_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    switch (Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel)
    {
     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun(&SeatBackPosiReq,
        &H_SeatMoveCmd_e, &MotorActType_prev_i);
      break;

     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun(&SeatBackPosiReq,
        &H_SeatMoveCmd_e, &MotorActType_prev_i);
      break;

     default:
      H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;

      /* �����̵�����ǰճ������ == ��Ч */
      if ((((INT8U)D_Relay_UpFrontFault) == DrMtr_BackRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

        /* �����Զ����� */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* �����Զ�������Ч�Ҳ�����Χ�� */
        if ((0 != SeatBackPosiReq) && (((BOOL)FALSE) == DrMtr_BackStallErr) &&
            (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

          /* �����Զ����� */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* �����ֶ����� */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD ==
               Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw) && (((BOOL)FALSE)
               == DrMtr_BackStallErr) && (((BOOL)FALSE) == DrMtr_BackHallErr) &&
              (((BOOL)FALSE) == DrMtr_BackMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
          {
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

            /* �Զ����� */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* �����̵����º�ճ������ == ��Ч ���ʱ�����100ms */
            if ((((INT8U)D_Relay_DownBackFault) == DrMtr_BackRelayAdhesionErr) &&
                (CAL_HightMotorRunInterval_100ms <=
                 Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
            {
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

              /* �Զ����� */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* �����Զ�������Ч�Ҳ�����Χ�� */
              if ((0 != SeatBackPosiReq) && (((BOOL)FALSE) == DrMtr_BackStallErr)
                  && (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g ==
                      enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
              {
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

                /* �Զ����� */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* �����ֶ�������Ч */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD ==
                     Appl_DrMotorAdjust_CtrlModel_B.BackManualAdjSw) && (((BOOL)
                      FALSE) == DrMtr_BackStallErr) && (((BOOL)FALSE) ==
                     DrMtr_BackHallErr) && (((BOOL)FALSE) ==
                     DrMtr_BackMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a))
                {
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a = 0U;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c19_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* �����Զ����� */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* ������������ʱ�� */
                  if (Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 =
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a +
                      1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_a =
                      (INT8U)tmp_0;
                  }

                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 0U;

                  /* �����Զ�������Ч */
                  if (0 != SeatBackPosiReq)
                  {
                    /* ��������ж�Ŀǰ����Ϊ5������ֵ */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         DrMtr_BackSoftStopErr) && (SeatBackPosiReq >
                         DrMtr_BackHallPosi) && (((INT16U)D_ToleranceDistance) <
                         SeatBackPosiReq - DrMtr_BackHallPosi))
                    {
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_c = 1U;
                    }
                    else
                    {
                      /*  ������ֹ�� �ҳ���Χ  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           DrMtr_BackSoftStopErr) && (SeatBackPosiReq <
                           DrMtr_BackHallPosi) && (((INT16U)D_ToleranceDistance)
                           < DrMtr_BackHallPosi - SeatBackPosiReq))
                      {
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_c = 1U;
                      }
                      else
                      {
                        /* ������Χ�ڣ������ɹ� */
                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  ����λ���б仯 ������״̬  */
                  if (SeatLengthPosiReq !=
                      Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_j)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
              }
            }
          }
        }
      }
      break;
    }
  }

  SeatBackPosiReq = Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_ov;
  Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_ov = SeatFrontPosiReq;
  MotorActType_prev_i = Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_l;
  Appl_DrMotorAdjust_CtrlModel_DW.MotorActType_start_l =
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType;
  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c21_Appl_DrMotorAdjust_CtrlModel
      == 0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c21_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init_Interval;
    H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    switch (Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel)
    {
     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorDownBackRun_j(&H_SeatMoveCmd_p,
        &MotorActType_prev_i, &SeatFrontPosiReq);
      break;

     case Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun:
      Appl_DrMotorAdjust_CtrlModel_H_MotorUpFrontRun_l(&H_SeatMoveCmd_p,
        &MotorActType_prev_i, &SeatFrontPosiReq);
      break;

     default:
      H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;

      /* ���м̵�����ǰճ������ == ��Ч */
      if ((((INT8U)D_Relay_UpFrontFault) == DrMtr_FrontRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
          Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

        /* �����Զ����� */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* �����Զ�������Ч�Ҳ�����Χ�� */
        if ((0 != SeatFrontPosiReq) && (((BOOL)FALSE) == DrMtr_FrontStallErr) &&
            (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
          Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
            Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

          /* �����Զ����� */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* �����ֶ����� */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD ==
               Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw) && (((BOOL)FALSE)
               == DrMtr_FrontStallErr) && (((BOOL)FALSE) == DrMtr_FrontHallErr) &&
              (((BOOL)FALSE) == DrMtr_FrontMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
          {
            Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
            Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel =
              Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

            /* �Զ����� */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* ���м̵����º�ճ������ == ��Ч ���ʱ�����100ms */
            if ((((INT8U)D_Relay_DownBackFault) == DrMtr_FrontRelayAdhesionErr) &&
                (CAL_HightMotorRunInterval_100ms <=
                 Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
            {
              Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
              Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

              /* �Զ����� */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* �����Զ�������Ч�Ҳ�����Χ�� */
              if ((0 != SeatFrontPosiReq) && (((BOOL)FALSE) ==
                   DrMtr_FrontStallErr) &&
                  (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
              {
                Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
                Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                  = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

                /* �Զ����� */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* �����ֶ�������Ч */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD ==
                     Appl_DrMotorAdjust_CtrlModel_B.FrontManualAdjSw) && (((BOOL)
                      FALSE) == DrMtr_FrontStallErr) && (((BOOL)FALSE) ==
                     DrMtr_FrontHallErr) && (((BOOL)FALSE) ==
                     DrMtr_FrontMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f))
                {
                  Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f = 0U;
                  Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_DrMotorAdjust_CtrlModel_DW.is_c21_Appl_DrMotorAdjust_CtrlModel
                    = Appl_DrMotorAdjust_CtrlModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* �����Զ����� */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* ���е�������ʱ�� */
                  if (Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 =
                      Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f +
                      1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_DrMotorAdjust_CtrlModel_DW.HMotorRunIntervalTime_f =
                      (INT8U)tmp_0;
                  }

                  Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 0U;
                  Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 0U;

                  /* �����Զ�������Ч */
                  if (0 != SeatFrontPosiReq)
                  {
                    /* ��������ж�Ŀǰ����Ϊ5������ֵ */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         DrMtr_FrontSoftStopErr) && (SeatFrontPosiReq >
                         DrMtr_FrontHallPosi) && (((INT16U)D_ToleranceDistance) <
                         SeatFrontPosiReq - DrMtr_FrontHallPosi))
                    {
                      Appl_DrMotorAdjust_CtrlModel_DW.UpFrontFlag_b = 1U;
                    }
                    else
                    {
                      /*  ������ֹ�� �ҳ���Χ  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           DrMtr_FrontSoftStopErr) && (SeatFrontPosiReq <
                           DrMtr_FrontHallPosi) && (((INT16U)D_ToleranceDistance)
                           < DrMtr_FrontHallPosi - SeatFrontPosiReq))
                      {
                        Appl_DrMotorAdjust_CtrlModel_DW.DownBackFlag_n = 1U;
                      }
                      else
                      {
                        /* ������Χ�ڣ������ɹ� */
                        Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  ����λ���б仯 ������״̬  */
                  if (SeatBackPosiReq !=
                      Appl_DrMotorAdjust_CtrlModel_DW.SeatHeightPosiReq_start_ov)
                  {
                    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
              }
            }
          }
        }
      }
      break;
    }
  }

  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c17_Appl_DrMotorAdjust_CtrlModel
      == 0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c17_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_c17_Appl_DrMotorAdjust_CtrlModel =
      Appl_DrMotorAdjust_CtrlModel_IN_Init;
    Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
    Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
    Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
    Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
  }
  else if (Appl_DrMotorAdjust_CtrlModel_DW.is_c17_Appl_DrMotorAdjust_CtrlModel ==
           Appl_DrMotorAdjust_CtrlModel_IN_Ban)
  {
    /*  ж��ʵ��   */
    if ((enIgnSts_eCrank != DrMtr_PowerModeStatus) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == DrMtr_VoltMode) && (((BOOL)TRUE) ==
         DrMtr_VoltSatisfy) && (!((BOOL)FALSE)))
    {
      Appl_DrMotorAdjust_CtrlModel_DW.is_c17_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Init;
      Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
      Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
      Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
      Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
    }
  }
  else
  {
    /*  ж�ɽ���  */
    if ((enIgnSts_eCrank == DrMtr_PowerModeStatus) ||
        (enFinalPowerMode_EN_NORMAL_VOLT != DrMtr_VoltMode) || (((BOOL)TRUE) !=
         DrMtr_VoltSatisfy) || ((BOOL)FALSE))
    {
      Appl_DrMotorAdjust_CtrlModel_DW.is_c17_Appl_DrMotorAdjust_CtrlModel =
        Appl_DrMotorAdjust_CtrlModel_IN_Ban;

      /* ���� */
      Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd = 0U;
      Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd = 0U;
      Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd = 0U;
      Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd = 0U;
    }
    else
    {
      Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
      Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
      Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
      Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
    }
  }

  if (Appl_DrMotorAdjust_CtrlModel_DW.is_active_c16_Appl_DrMotorAdjust_CtrlModel
      == 0U)
  {
    Appl_DrMotorAdjust_CtrlModel_DW.is_active_c16_Appl_DrMotorAdjust_CtrlModel =
      1U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_HeightAdjust =
      Appl_DrMotorAdjust_CtrlModel_IN_Init;
    Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_VerticalAdjust =
      Appl_DrMotorAdjust_CtrlModel_IN_Init;
    Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_FrontAngleAdjust =
      Appl_DrMotorAdjust_CtrlModel_IN_Init;
    Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.is_BackAdjust =
      Appl_DrMotorAdjust_CtrlModel_IN_Init;
    Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl = 0U;
    Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = 0U;
  }
  else
  {
    if (Appl_DrMotorAdjust_CtrlModel_DW.is_HeightAdjust ==
        Appl_DrMotorAdjust_CtrlModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL ==
          Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd)
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_HeightAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Init;
        Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = 0U;
      }
      else
      {
        Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd;
        tmp_0 = Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = (INT16U)tmp_0;

        /*  �̵���ճ�� */
        if (((BOOL)FALSE) != DrMtr_HeightRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = 0U;
        }
      }
    }
    else
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL !=
          Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd)
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_HeightAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Action;
        Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd;

        /*  �̵���ճ�� */
        if (((BOOL)FALSE) != DrMtr_HeightRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer = 0U;
        }
      }
    }

    if (Appl_DrMotorAdjust_CtrlModel_DW.is_VerticalAdjust ==
        Appl_DrMotorAdjust_CtrlModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL ==
          Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd)
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_VerticalAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Init;
        Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = 0U;
      }
      else
      {
        Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd;
        tmp_0 = Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != DrMtr_LengthRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = 0U;
        }
      }
    }
    else
    {
      /* �߶ȡ�������û��������ʱ�ѵ� */
      if ((((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer >
            CAL_MotorDiffToStart_100ms)) && ((INT32S)enSeatMoveCmd_EN_NULL !=
           Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_VerticalAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Action;
        Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd;
        if (((BOOL)FALSE) != DrMtr_LengthRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer = 0U;
        }
      }
    }

    if (Appl_DrMotorAdjust_CtrlModel_DW.is_FrontAngleAdjust ==
        Appl_DrMotorAdjust_CtrlModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL ==
          Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd)
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_FrontAngleAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Init;
        Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = 0U;
      }
      else
      {
        Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd;
        tmp_0 = Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != DrMtr_FrontRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = 0U;
        }
      }
    }
    else
    {
      /* �߶ȡ�������û��������ʱ�ѵ� */
      if ((((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer >
            CAL_MotorDiffToStart_100ms)) && (((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer >
            CAL_MotorDiffToStart_100ms)) && ((INT32S)enSeatMoveCmd_EN_NULL !=
           Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_FrontAngleAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Action;
        Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd;
        if (((BOOL)FALSE) != DrMtr_FrontRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer = 0U;
        }
      }
    }

    if (Appl_DrMotorAdjust_CtrlModel_DW.is_BackAdjust ==
        Appl_DrMotorAdjust_CtrlModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL ==
          Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd)
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_BackAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Init;
        Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl = 0U;
        Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = 0U;
      }
      else
      {
        Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd;
        tmp_0 = Appl_DrMotorAdjust_CtrlModel_DW.BackTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != DrMtr_BackRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = 0U;
        }
      }
    }
    else
    {
      /* �߶ȡ�����ǰ�����û��������ʱ�ѵ� */
      if ((((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.HeightMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.HeightTimer >
            CAL_MotorDiffToStart_100ms)) && (((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.LengthMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.LengthTimer >
            CAL_MotorDiffToStart_100ms)) && (((INT32S)enSeatMoveCmd_EN_NULL ==
            Appl_DrMotorAdjust_CtrlModel_B.FrontMotorCmd) ||
           (Appl_DrMotorAdjust_CtrlModel_DW.FrontTimer >
            CAL_MotorDiffToStart_100ms)) && ((INT32S)enSeatMoveCmd_EN_NULL !=
           Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd))
      {
        Appl_DrMotorAdjust_CtrlModel_DW.is_BackAdjust =
          Appl_DrMotorAdjust_CtrlModel_IN_Action;
        Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl =
          Appl_DrMotorAdjust_CtrlModel_B.BackMotorCmd;
        if (((BOOL)FALSE) != DrMtr_BackRelayAdhesionErr)
        {
          Appl_DrMotorAdjust_CtrlModel_DW.BackTimer = 0U;
        }
      }
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_DrMotorAdjust_CtrlModel_RTE(void)
{
  DrMtr_AnyoneHallErr = Rte_GetVfb_DrAnyoneHallErr( );
  DrMtr_AnyoneRelayAdheErr = Rte_GetVfb_DrAnyoneRelayAdheErr( );
  DrMtr_BackDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverBack);
  DrMtr_BackHallErr = Rte_GetVfb_DrBackHallErr( );
  DrMtr_BackHallPosi = Cdd_GetCurrentHallCnt(EN_DriverBack);
  DrMtr_BackLearnCmd = Rte_GetVfb_DrBackLearnCmd( );
  DrMtr_BackMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_DRV_BACK);
  DrMtr_BackMotorTimeOutErr = Rte_GetVfb_DrBackMotorTimeOutErr( );
  DrMtr_BackRelayAdhesionErr = Rte_GetVfb_DrBackRelayAdheErr( );
  DrMtr_BackSoftStopErr = Rte_GetVfb_DrBackSoftStopErr( );
  DrMtr_BackStallErr = Rte_GetVfb_DrBackStallErr( );
  DrMtr_BackSwitchAdheErr = Rte_GetVfb_DrBackSwitchAdheErr( );
  DrMtr_BackSwitchCmd = Rte_GetVfb_DrBackSwitchCmd( );
  DrMtr_DiagnoseLearnIn = Rte_GetVfb_DrLearnEnable( );
  DrMtr_FrontDefaulStoptPos = Cdd_GetMotorHardStop(EN_DriverFront);
  DrMtr_FrontHallErr = Rte_GetVfb_DrFrontHallErr( );
  DrMtr_FrontHallPosi = Cdd_GetCurrentHallCnt(EN_DriverFront);
  DrMtr_FrontLearnCmd = Rte_GetVfb_DrFrontLearnCmd( );
  DrMtr_FrontMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_DRV_FRONT);
  DrMtr_FrontMotorTimeOutErr = Rte_GetVfb_DrFrontMotorTimeOutErr( );
  DrMtr_FrontRelayAdhesionErr = Rte_GetVfb_DrFrontRelayAdheErr( );
  DrMtr_FrontSoftStopErr = Rte_GetVfb_DrFrontSoftStopErr( );
  DrMtr_FrontStallErr = Rte_GetVfb_DrFrontStallErr( );
  DrMtr_FrontSwitchAdheErr = Rte_GetVfb_DrFrontSwitchAdheErr( );
  DrMtr_FrontSwitchCmd = Rte_GetVfb_DrFrontSwitchCmd( );
  DrMtr_HeightDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverHeight);
  DrMtr_HeightHallErr = Rte_GetVfb_DrHeightHallErr( );
  DrMtr_HeightHallPosi = Cdd_GetCurrentHallCnt(EN_DriverHeight);
  DrMtr_HeightLearnCmd = Rte_GetVfb_DrHeightLearnCmd( );
  DrMtr_HeightMotorTimeOutErr = Rte_GetVfb_DrHeightMotorTimeOutErr( );
  DrMtr_HeightRelayAdhesionErr = Rte_GetVfb_DrHeightRelayAdheErr( );
  DrMtr_HeightSoftStopErr = Rte_GetVfb_DrLengthSoftStopErr( );
  DrMtr_HeightStallErr = Rte_GetVfb_DrHeightStallErr( );
  DrMtr_HeightSwitchAdheErr = Rte_GetVfb_DrHeightSwitchAdheErr( );
  DrMtr_HeightSwitchCmd = Rte_GetVfb_DrHeightSwitchCmd( );
  DrMtr_HeigthMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_DRV_HEIGHT);
  DrMtr_LearnSts = Rte_GetVfb_DrLearnSts( );
  DrMtr_LengthDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverLength);
  DrMtr_LengthHallErr = Rte_GetVfb_DrLengthHallErr( );
  DrMtr_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_DriverLength);
  DrMtr_LengthLearnCmd = Rte_GetVfb_DrLengthLearnCmd( );
  DrMtr_LengthMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_DRV_LENGTH);
  DrMtr_LengthMotorTimeOutErr = Rte_GetVfb_DrLengthMotorTimeOutErr( );
  DrMtr_LengthRelayAdhesionErr = Rte_GetVfb_DrLengthRelayAdheErr( );
  DrMtr_LengthSoftStopErr = Rte_GetVfb_DrHeightSoftStopErr( );
  DrMtr_LengthStallErr = Rte_GetVfb_DrLengthStallErr( );
  DrMtr_LengthSwitchAdheErr = Rte_GetVfb_DrLengthSwitchAdheErr( );
  DrMtr_LengthSwitchCmd = Rte_GetVfb_DrLengthSwitchCmd( );
  DrMtr_MemoryBackReqPosi = Rte_GetVfb_DrMemBackReqPosi( );
  DrMtr_MemoryFrontReqPosi = Rte_GetVfb_DrMemFrontReqPosi( );
  DrMtr_MemoryHeightReqPosi = Rte_GetVfb_DrMemHeightReqPosi( );
  DrMtr_MemoryLengthReqPosi = Rte_GetVfb_DrMemLengthReqPosi( );
  DrMtr_PowerModeStatus = Rte_GetVfb_PowerMode( );
  DrMtr_ResBackReqPosi = Rte_GetVfb_DrResBackReqPosi( );
  DrMtr_ResFrontReqPosi = Rte_GetVfb_DrResFrontReqPosi( );
  DrMtr_ResHeightReqPosi = Rte_GetVfb_DrResHeightReqPosi( );
  DrMtr_ResLengthReqPosi = Rte_GetVfb_DrResLengthReqPosi( );
  DrMtr_ResetBackReqPosi = Rte_GetVfb_DrBackResetReqPosi( );
  DrMtr_ResetFrontReqPosi = Rte_GetVfb_DrFrontResetReqPosi( );
  DrMtr_ResetHeightReqPosi = Rte_GetVfb_DrHeightResetReqPosi( );
  DrMtr_ResetLengthReqPosi = Rte_GetVfb_DrLengthResetReqPosi( );
  DrMtr_VoltMode = Rte_GetVfb_VoltMode( );
  DrMtr_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  DrMtr_WelcomeBackReqPosi = Rte_GetVfb_DrWelBackReqPosi( );
  DrMtr_WelcomeLengthReqPosi = Rte_GetVfb_DrWelLengthReqPosi( );
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrMotorAdjust_CtrlModel_UpDataInputInfo(void)
{
  Appl_DrMotorAdjust_CtrlModel_RTE();
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_DrMotorAdjust_CtrlModel_UpDataOutputInfo(void)
{
  Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion2 = (INT8U)
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g;
  Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion3 = (INT8U)
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType;
  Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion4 = (INT8U)
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l;
  Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion5 = (INT8U)
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m;
  Rte_SetVfb_DrMoveType(Appl_DrMotorAdjust_CtrlModel_B.MotorActionType);
  Rte_SetVfb_DrHeightAutoRunFlag
    (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o);
  Rte_SetVfb_DrLengthAutoRunFlag
    (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag);
  Rte_SetVfb_DrBackAutoRunFlag
    (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p);
  Rte_SetVfb_DrFrontAutoRunFlag
    (Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g);
  Rte_SetVfb_DrHeightMotorCmd(Appl_DrMotorAdjust_CtrlModel_B.Can_HeightMotorCtrl);
  Rte_SetVfb_DrLengthMotorCmd(Appl_DrMotorAdjust_CtrlModel_B.Can_LengthMotorCtrl);
  Rte_SetVfb_DrBackMotorCmd(Appl_DrMotorAdjust_CtrlModel_B.Can_BackMotorCtrl);
  Rte_SetVfb_DrFrontMotorCmd(Appl_DrMotorAdjust_CtrlModel_B.Can_FrontMotorCtrl);
  Rte_SetVfb_DrHeightMotorReason
    (Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion2);
  Rte_SetVfb_DrLengthMotorReason
    (Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion3);
  Rte_SetVfb_DrBackMotorReason
    (Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion4);
  Rte_SetVfb_DrFrontMotorReason
    (Appl_DrMotorAdjust_CtrlModel_B.DataTypeConversion5);
}

/* Model step function */
void Appl_DrMotorAdjust_CtrlModel_step(void)
{
  Appl_DrMotorAdjust_CtrlModel_UpDataInputInfo();
  Appl_DrMotorAdjust_CtrlModel_LogicCtrl();
  Appl_DrMotorAdjust_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_DrMotorAdjust_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_DrMotorAdjust_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_DrMotorAdjust_CtrlModel_B), 0,
                sizeof(B_Appl_DrMotorAdjust_CtrlModel_T));

  {
    Appl_DrMotorAdjust_CtrlModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType =
      enSeatHightMotorRunsts_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_g =
      enSeatHightMotorRunsts_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_l =
      enSeatHightMotorRunsts_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_B.H_MotorRunType_m =
      enSeatHightMotorRunsts_EN_NULL;
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_o =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_p =
      enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_DrMotorAdjust_CtrlModel_B.HeightAutoRunFlag_g =
      enSeatAutoRunSts_EN_SEAT_INVALID;
  }

  /* exported global signals */
  DrMtr_BackMotorMosErr = enMosErrSts_enNULL;
  DrMtr_FrontMotorMosErr = enMosErrSts_enNULL;
  DrMtr_HeigthMotorMosErr = enMosErrSts_enNULL;
  DrMtr_LengthMotorMosErr = enMosErrSts_enNULL;
  DrMtr_PowerModeStatus = enIgnSts_eOff;
  DrMtr_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  DrMtr_BackDefaultStopPos = ((INT16U)0U);
  DrMtr_BackHallPosi = ((INT16U)0U);
  DrMtr_FrontDefaulStoptPos = ((INT16U)0U);
  DrMtr_FrontHallPosi = ((INT16U)0U);
  DrMtr_HeightDefaultStopPos = ((INT16U)0U);
  DrMtr_HeightHallPosi = ((INT16U)0U);
  DrMtr_LengthDefaultStopPos = ((INT16U)0U);
  DrMtr_LengthHallPosi = ((INT16U)0U);
  DrMtr_MemoryBackReqPosi = ((INT16U)0U);
  DrMtr_MemoryFrontReqPosi = ((INT16U)0U);
  DrMtr_MemoryHeightReqPosi = ((INT16U)0U);
  DrMtr_MemoryLengthReqPosi = ((INT16U)0U);
  DrMtr_ResBackReqPosi = ((INT16U)0U);
  DrMtr_ResFrontReqPosi = ((INT16U)0U);
  DrMtr_ResHeightReqPosi = ((INT16U)0U);
  DrMtr_ResLengthReqPosi = ((INT16U)0U);
  DrMtr_ResetBackReqPosi = ((INT16U)0U);
  DrMtr_ResetFrontReqPosi = ((INT16U)0U);
  DrMtr_ResetHeightReqPosi = ((INT16U)0U);
  DrMtr_ResetLengthReqPosi = ((INT16U)0U);
  DrMtr_WelcomeBackReqPosi = ((INT16U)0U);
  DrMtr_WelcomeLengthReqPosi = ((INT16U)0U);
  DrMtr_AnyoneHallErr = ((INT8U)0U);
  DrMtr_AnyoneRelayAdheErr = ((INT8U)0U);
  DrMtr_BackHallErr = ((INT8U)0U);
  DrMtr_BackLearnCmd = ((INT8U)0U);
  DrMtr_BackMotorTimeOutErr = ((INT8U)0U);
  DrMtr_BackRelayAdhesionErr = ((INT8U)0U);
  DrMtr_BackSoftStopErr = ((INT8U)0U);
  DrMtr_BackStallErr = ((INT8U)0U);
  DrMtr_BackSwitchAdheErr = ((INT8U)0U);
  DrMtr_BackSwitchCmd = ((INT8U)0U);
  DrMtr_DiagnoseLearnIn = ((INT8U)0U);
  DrMtr_FrontHallErr = ((INT8U)0U);
  DrMtr_FrontLearnCmd = ((INT8U)0U);
  DrMtr_FrontMotorTimeOutErr = ((INT8U)0U);
  DrMtr_FrontRelayAdhesionErr = ((INT8U)0U);
  DrMtr_FrontSoftStopErr = ((INT8U)0U);
  DrMtr_FrontStallErr = ((INT8U)0U);
  DrMtr_FrontSwitchAdheErr = ((INT8U)0U);
  DrMtr_FrontSwitchCmd = ((INT8U)0U);
  DrMtr_HeightHallErr = ((INT8U)0U);
  DrMtr_HeightLearnCmd = ((INT8U)0U);
  DrMtr_HeightMotorTimeOutErr = ((INT8U)0U);
  DrMtr_HeightRelayAdhesionErr = ((INT8U)0U);
  DrMtr_HeightSoftStopErr = ((INT8U)0U);
  DrMtr_HeightStallErr = ((INT8U)0U);
  DrMtr_HeightSwitchAdheErr = ((INT8U)0U);
  DrMtr_HeightSwitchCmd = ((INT8U)0U);
  DrMtr_LearnSts = ((INT8U)0U);
  DrMtr_LengthHallErr = ((INT8U)0U);
  DrMtr_LengthLearnCmd = ((INT8U)0U);
  DrMtr_LengthMotorTimeOutErr = ((INT8U)0U);
  DrMtr_LengthRelayAdhesionErr = ((INT8U)0U);
  DrMtr_LengthSoftStopErr = ((INT8U)0U);
  DrMtr_LengthStallErr = ((INT8U)0U);
  DrMtr_LengthSwitchAdheErr = ((INT8U)0U);
  DrMtr_LengthSwitchCmd = ((INT8U)0U);
  DrMtr_VoltSatisfy = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_DrMotorAdjust_CtrlModel_DW, 0,
                sizeof(DW_Appl_DrMotorAdjust_CtrlModel_T));
  Appl_DrMotorAdjust_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
