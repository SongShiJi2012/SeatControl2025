/*
 * File: Appl_DrRestMode_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_DrRestMode_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:42:06 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_DrRestMode_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_DRMEM_SPEED_5
#error The variable for the parameter "D_DRMEM_SPEED_5" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_ClickNapBackPosi
#error The variable for the parameter "D_ClickNapBackPosi" is not defined
#endif

#ifndef D_ClickNapLengthPosi
#error The variable for the parameter "D_ClickNapLengthPosi" is not defined
#endif

#ifndef D_SoftDistanceDrLegnth
#error The variable for the parameter "D_SoftDistanceDrLegnth" is not defined
#endif

/* Named constants for Chart: '<S5>/ResDeal' */
#define Appl_DrRestMode_CtrlModel_IN_Active ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_Call ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_CallOver ((INT8U)2U)
#define Appl_DrRestMode_CtrlModel_IN_Fault ((INT8U)2U)
#define Appl_DrRestMode_CtrlModel_IN_Inactive ((INT8U)3U)
#define Appl_DrRestMode_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_DrRestMode_CtrlModel_IN_ReCall ((INT8U)2U)
#define Appl_DrRestMode_CtrlModel_IN_WaitInit ((INT8U)3U)

/* Named constants for Chart: '<S12>/CC1_Flag' */
#define Appl_DrRestMode_CtrlModel_IN_FALSE ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_Init_h ((INT8U)2U)
#define Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c ((INT8U)0U)
#define Appl_DrRestMode_CtrlModel_IN_TRUE ((INT8U)3U)

/* Named constants for Chart: '<S15>/CC4_Flag' */
#define Appl_DrRestMode_CtrlModel_IN_TRUE_n ((INT8U)2U)

/* Named constants for Chart: '<S16>/GetCallRet' */
#define Appl_DrRestMode_CtrlModel_IN_Init_l ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_Ret ((INT8U)2U)

/* Named constants for Chart: '<S25>/Colse_Flag' */
#define Appl_DrRestMode_CtrlModel_IN_CLOSE ((INT8U)1U)
#define Appl_DrRestMode_CtrlModel_IN_Ready ((INT8U)3U)

/* Named constants for Chart: '<S29>/Open_Flag' */
#define Appl_DrRestMode_CtrlModel_IN_Open ((INT8U)3U)
#define Appl_DrRestMode_CtrlModel_IN_Ready_b ((INT8U)4U)

/* Exported block signals */
enSeatMotorRunType DrRes_CurrentMoveType;/* '<S11>/DrRes_CurrentMoveType'
                                          * ���ݵ����ǰ��������
                                          */
enSeatAutoRunSts DrRes_BackAutoRunFlag;/* '<S11>/DrRes_BackAutoRunFlag'
                                        * ���ݿ����Զ�����״̬
                                        */
enSeatAutoRunSts DrRes_FrontAutoRunFlag;/* '<S11>/DrRes_FrontAutoRunFlag'
                                         * ����ǰ���Ƕ��Զ�����״̬
                                         */
enSeatAutoRunSts DrRes_HeightAutoRunFlag;/* '<S11>/DrRes_HeightAutoRunFlag'
                                          * ���ݸ߶��Զ�����״̬
                                          */
enSeatAutoRunSts DrRes_LengthAutoRunFlag;/* '<S11>/DrRes_LengthAutoRunFlag'
                                          * ���������Զ�����״̬
                                          */
enPowerModeSts DrRes_PowerMode;        /* '<S11>/DrRes_PowerMode'
                                        * ������Դģʽ
                                        */
enMassageMode_DSM DrRes_MassageMode_FB;/* '<S11>/DrRes_MassageMode_FB'
                                        * ��Ħģʽ����-LIN���ź�
                                        */
enFinalPowerMode DrRes_VoltMode;       /* '<S11>/DrRes_VoltMode'
                                        * ������ѹģʽ
                                        */
INT16U DrRes_BackDefaultMotorSize;     /* '<S11>/DrRes_BackDefaultMotorSize'
                                        * �����������
                                        */
INT16U DrRes_BackDefaultStopPos;       /* '<S11>/DrRes_BackDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrRes_BackHallPosi;             /* '<S11>/DrRes_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
INT16U DrRes_FrontDefaulMotorSize;     /* '<S11>/DrRes_FrontDefaulMotorSize'
                                        * ���й������
                                        */
INT16U DrRes_FrontDefaulStoptPos;      /* '<S11>/DrRes_FrontDefaulStoptPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrRes_FrontHallPosi;            /* '<S11>/DrRes_FrontHallPosi'
                                        * ����ǰ���Ƕȵ�ǰ����λ��
                                        */
INT16U DrRes_HeightDefaultMotorSize;   /* '<S11>/DrRes_HeightDefaultMotorSize'
                                        * �߶ȹ������
                                        */
INT16U DrRes_HeightDefaultStopPos;     /* '<S11>/DrRes_HeightDefaultStopPos'
                                        * �߶�Ӳֹ��
                                        */
INT16U DrRes_HeightHallPosi;           /* '<S11>/DrRes_HeightHallPosi'
                                        * ���ݸ߶ȵ�ǰ����λ��
                                        */
INT16U DrRes_LengthDefaultMotorSize;   /* '<S11>/DrRes_LengthDefaultMotorSize'
                                        * ����������
                                        */
INT16U DrRes_LengthDefaultStopPos;     /* '<S11>/DrRes_LengthDefaultStopPos'
                                        * ����Ӳֹ��
                                        */
INT16U DrRes_LengthHallPosi;           /* '<S11>/DrRes_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
INT16U DrResl_ReCallPosi_Back;         /* '<S11>/DrResl_ReCallPosi_Back'
                                        * ����С��λλ��-����
                                        */
INT16U DrResl_ReCallPosi_Front;        /* '<S11>/DrResl_ReCallPosi_Front'
                                        * ����С��λλ��-����
                                        */
INT16U DrResl_ReCallPosi_Height;       /* '<S11>/DrResl_ReCallPosi_Height'
                                        * ����С��λλ��-�߶�
                                        */
INT16U DrResl_ReCallPosi_Length;       /* '<S11>/DrResl_ReCallPosi_Length'
                                        * ����С��λλ��-����
                                        */
INT8U DrRes_AdjustEnable;              /* '<S11>/DrRes_AdjustEnable'
                                        * �������ε���
                                        */
INT8U DrRes_AnyoneHallFaultSts;        /* '<S11>/DrRes_AnyoneHallFaultSts'
                                        * ������һ����������ϱ�־λ
                                        */
INT8U DrRes_AnyoneRelayFaultSts;       /* '<S11>/DrRes_AnyoneRelayFaultSts'
                                        * ��һ�̵���ճ�����ϱ�־
                                        */
INT8U DrRes_BackLockFault;             /* '<S11>/DrRes_BackLockFault'
                                        * �������ο�����ת��־λ
                                        */
INT8U DrRes_DescBackHallFault;         /* '<S11>/DrRes_DescBackHallFault'
                                        * ��������������ϱ�־λ
                                        */
INT8U DrRes_DescFrontHallFault;        /* '<S11>/DrRes_DescFrontHallFault'
                                        * ���е���������ϱ�־λ
                                        */
INT8U DrRes_DescHeightHallFault;       /* '<S11>/DrRes_DescHeightHallFault'
                                        * �߶ȵ���������ϱ�־λ
                                        */
INT8U DrRes_DescLengthHallFault;       /* '<S11>/DrRes_DescLengthHallFault'
                                        * �������������ϱ�־λ
                                        */
INT8U DrRes_EngineRunFlag;             /* '<S11>/DrRes_EngineRunFlag'
                                        * ����������״̬
                                        */
INT8U DrRes_FrontLockFault;            /* '<S11>/DrRes_FrontLockFault'
                                        * �����������ж�ת��־λ
                                        */
INT8U DrRes_HeightLockFault;           /* '<S11>/DrRes_HeightLockFault'
                                        * �������θ߶ȶ�ת��־λ
                                        */
INT8U DrRes_IVI_NapMode_SwtichSet;     /* '<S11>/DrRes_IVI_NapMode_SwtichSet'
                                        * �ģʽ�������趨
                                        */
INT8U DrRes_LengthLockFault;           /* '<S11>/DrRes_LengthLockFault'
                                        * �������������ת��־λ
                                        */
INT8U DrRes_SeatLearnResult;           /* '<S11>/DrRes_SeatLearnResult'
                                        * ��������ѧϰ״̬��־λ
                                        */
INT8U DrRes_SeatMassageCfg;            /* '<S11>/DrRes_SeatMassageCfg'
                                        *  ��Ħ��������ʹ�ܱ�־λ
                                        */
INT8U DrRes_VehicleRunFlag;            /* '<S11>/DrRes_VehicleRunFlag'
                                        * ��������״̬
                                        */
INT8U DrRes_VoltSatisfy;               /* '<S11>/DrRes_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */
INT8U DrRes_WelcomeEnable;             /* '<S11>/DrRes_WelcomeEnable'
                                        *  ���ݼ���ӭ������ʹ�ܱ�־λ
                                        */

/* Block signals (default storage) */
B_Appl_DrRestMode_CtrlModel_T Appl_DrRestMode_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_DrRestMode_CtrlModel_T Appl_DrRestMode_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_DrRestMode_CtrlModel_T Appl_DrRestMode_CtrlModel_M_;
RT_MODEL_Appl_DrRestMode_CtrlModel_T *const Appl_DrRestMode_CtrlModel_M =
  &Appl_DrRestMode_CtrlModel_M_;
static void Appl_DrRestMode_CtrlModel_LogicCtrl_Init(void);
static void Appl_DrRestMode_CtrlModel_LogicCtrl(void);
static void Appl_DrRestMode_CtrlModel_RTE(void);
static void Appl_DrRestMode_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_DrRestMode_CtrlModel_UpDataInputInfo(void);
static void Appl_DrRestMode_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_DrRestMode_CtrlModel_inner_default_Init(const
  enSeatMotorRunType *DrRes_CurrentMoveType_prev_c);

/* Function for Chart: '<S5>/ResDeal' */
static void Appl_DrRestMode_CtrlModel_inner_default_Init(const
  enSeatMotorRunType *DrRes_CurrentMoveType_prev_c)
{
  INT32S tmp;

  /*  �ӳ�20ms�洢  */
  if (Appl_DrRestMode_CtrlModel_DW.SaveReTimer > 2)
  {
    if (((*DrRes_CurrentMoveType_prev_c !=
          Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start_p) &&
         ((INT32S)Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start_p ==
          0)) || (DrResl_ReCallPosi_Height == 0) || (DrResl_ReCallPosi_Length ==
         0) || (DrResl_ReCallPosi_Back == 0) || (DrResl_ReCallPosi_Front == 0) ||
        (DrResl_ReCallPosi_Height == 0xFFFF) || (DrResl_ReCallPosi_Length ==
         0xFFFF) || (DrResl_ReCallPosi_Back == 0xFFFF) ||
        (DrResl_ReCallPosi_Front == 0xFFFF))
    {
      Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 0U;
    }
  }
  else
  {
    tmp = Appl_DrRestMode_CtrlModel_DW.SaveReTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    Appl_DrRestMode_CtrlModel_DW.SaveReTimer = (INT8U)tmp;
  }

  /*  �������δ��  */
  if (Appl_DrRestMode_CtrlModel_DW.SavePosiCnt < 10)
  {
    /*  ���»�λλ��  */
    Appl_DrRestMode_CtrlModel_B.In1 = DrRes_HeightHallPosi;
    Appl_DrRestMode_CtrlModel_B.ln2 = DrRes_LengthHallPosi;
    Appl_DrRestMode_CtrlModel_B.In3 = DrRes_BackHallPosi;
    Appl_DrRestMode_CtrlModel_B.ln4 = DrRes_FrontHallPosi;
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrRes_ReCallPosi_Height,
      Appl_DrRestMode_CtrlModel_B.In1);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrRes_ReCallPosi_Length,
      Appl_DrRestMode_CtrlModel_B.ln2);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrRes_ReCallPosi_Back,
      Appl_DrRestMode_CtrlModel_B.In3);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrRes_ReCallPosi_Front,
      Appl_DrRestMode_CtrlModel_B.ln4);
    tmp = Appl_DrRestMode_CtrlModel_DW.SavePosiCnt + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = (INT8U)tmp;
  }

  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Height = DrRes_HeightHallPosi;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Length =
    Appl_DrRestMode_CtrlModel_B.CallHallVall_Length;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Back =
    Appl_DrRestMode_CtrlModel_B.Add;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Front = DrRes_FrontHallPosi;
  Appl_DrRestMode_CtrlModel_B.In1_h =
    Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Height;
  Appl_DrRestMode_CtrlModel_B.ln2_b =
    Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Length;
  Appl_DrRestMode_CtrlModel_B.In3_e =
    Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Back;
  Appl_DrRestMode_CtrlModel_B.ln4_i =
    Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Front;
  Rte_SetVfb_Debug_Res_CallPosi_Height(Appl_DrRestMode_CtrlModel_B.In1_h);
  Rte_SetVfb_Debug_Res_CallPosi_Length(Appl_DrRestMode_CtrlModel_B.ln2_b);
  Rte_SetVfb_Debug_Res_CallPosi_Back(Appl_DrRestMode_CtrlModel_B.In3_e);
  Rte_SetVfb_Debug_Res_CallPosi_Front(Appl_DrRestMode_CtrlModel_B.ln4_i);
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrRestMode_CtrlModel_LogicCtrl_Init(void)
{
  Appl_DrRestMode_CtrlModel_DW.is_Active =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrRestMode_CtrlModel_DW.is_Inactive =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrRestMode_CtrlModel_DW.is_active_c8_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrRestMode_CtrlModel_DW.WaitTimer = 0U;
  Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 0U;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Height = 0U;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Length = 0U;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Back = 0U;
  Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Front = 0U;
  Appl_DrRestMode_CtrlModel_DW.StartFlag = 0U;
  Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 0U;
  Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = 0U;
  Appl_DrRestMode_CtrlModel_B.DSM_MassageMode_Req = 0U;
  Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = 0U;
  Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
  Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
  Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
  Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
  Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Back = 0U;
  Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Front = 0U;
  Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Height = 0U;
  Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Length = 0U;
  Appl_DrRestMode_CtrlModel_B.State_ResDeal = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrRestMode_CtrlModel_LogicCtrl(void)
{
  enSeatMotorRunType DrRes_CurrentMoveType_prev_c;
  INT32S tmp;
  Appl_DrRestMode_CtrlModel_B.Stop_Flag_f =
    Appl_DrRestMode_CtrlModel_B.Stop_Flag;
  Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason_o =
    Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason;
  Appl_DrRestMode_CtrlModel_B.Open_Flag_e =
    Appl_DrRestMode_CtrlModel_B.Open_Flag;
  Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason_b =
    Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason;
  Appl_DrRestMode_CtrlModel_B.Close_Flag_f =
    Appl_DrRestMode_CtrlModel_B.Close_Flag;
  Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason_h =
    Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason;
  Appl_DrRestMode_CtrlModel_B.MotorFault_Flag =
    Appl_DrRestMode_CtrlModel_B.MotroFault_Flag;
  Appl_DrRestMode_CtrlModel_B.MassageFault_Flag_l =
    Appl_DrRestMode_CtrlModel_B.MassageFault_Flag;
  Appl_DrRestMode_CtrlModel_B.DrRestCAll_Ret =
    Appl_DrRestMode_CtrlModel_B.CallRet;
  Appl_DrRestMode_CtrlModel_B.CC1_Flag_m = Appl_DrRestMode_CtrlModel_B.CC1_Flag;
  Appl_DrRestMode_CtrlModel_B.CC1_Reason_m =
    Appl_DrRestMode_CtrlModel_B.CC1_Reason;
  Appl_DrRestMode_CtrlModel_B.CC2_Flag_m = Appl_DrRestMode_CtrlModel_B.CC2_Flag;
  Appl_DrRestMode_CtrlModel_B.CC2_Reason_b =
    Appl_DrRestMode_CtrlModel_B.CC2_Reason;
  Appl_DrRestMode_CtrlModel_B.CC3_Flag_b = Appl_DrRestMode_CtrlModel_B.CC3_Flag;
  Appl_DrRestMode_CtrlModel_B.CC3_Reason_n =
    Appl_DrRestMode_CtrlModel_B.CC3_Reason;
  Appl_DrRestMode_CtrlModel_B.CC4_Flag_g = Appl_DrRestMode_CtrlModel_B.CC4_Flag;
  Appl_DrRestMode_CtrlModel_B.CC4_Reason_p =
    Appl_DrRestMode_CtrlModel_B.CC4_Reason;
  DrRes_CurrentMoveType_prev_c =
    Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start_p;
  Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start_p =
    DrRes_CurrentMoveType;
  if (Appl_DrRestMode_CtrlModel_DW.is_active_c8_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c8_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Inactive;
    Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
      enNapMode_EN_NapMode_Close;
    Appl_DrRestMode_CtrlModel_DW.is_Inactive =
      Appl_DrRestMode_CtrlModel_IN_WaitInit;
    Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 0U;
    Appl_DrRestMode_CtrlModel_DW.WaitTimer = 0U;
    Appl_DrRestMode_CtrlModel_DW.StartFlag = 0U;
  }
  else
  {
    switch (Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_Active:
      Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
        enNapMode_EN_NapMode_Open;

      /*
         ||��Ħ���ϱ�־λ==1 */
      if ((Appl_DrRestMode_CtrlModel_B.MassageFault_Flag == 1) ||
          (DrRes_AnyoneRelayFaultSts == 1))
      {
        Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
          enMassageLevel_DSM_EN_OFF;
        Appl_DrRestMode_CtrlModel_DW.is_Active =
          Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Fault;
        Appl_DrRestMode_CtrlModel_B.State_ResDeal = 5U;
        Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
          enNapMode_EN_NapMode_ERR;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
      }
      else
      {
        /* С�ر������־==1 */
        if (Appl_DrRestMode_CtrlModel_B.Close_Flag == ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height =
            DrResl_ReCallPosi_Height;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length =
            DrResl_ReCallPosi_Length;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = DrResl_ReCallPosi_Back;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front =
            DrResl_ReCallPosi_Front;
          Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
            enMassageLevel_DSM_EN_OFF;
          Appl_DrRestMode_CtrlModel_DW.is_Active =
            Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
            Appl_DrRestMode_CtrlModel_IN_Inactive;
          Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
            enNapMode_EN_NapMode_Close;
          Appl_DrRestMode_CtrlModel_DW.is_Inactive =
            Appl_DrRestMode_CtrlModel_IN_ReCall;
          Appl_DrRestMode_CtrlModel_B.State_ResDeal = 2U;
        }
        else
        {
          /* С�ֹͣ������־==1 */
          if (Appl_DrRestMode_CtrlModel_B.Stop_Flag == ((BOOL)TRUE))
          {
            Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
              enMassageLevel_DSM_EN_OFF;
            Appl_DrRestMode_CtrlModel_DW.is_Active =
              Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
            Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
              Appl_DrRestMode_CtrlModel_IN_Inactive;
            Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
              enNapMode_EN_NapMode_Close;
            Appl_DrRestMode_CtrlModel_DW.is_Inactive =
              Appl_DrRestMode_CtrlModel_IN_Init;
            Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
            Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
            Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
            Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
            Appl_DrRestMode_CtrlModel_B.State_ResDeal = 1U;
            Appl_DrRestMode_CtrlModel_DW.StartFlag = ((BOOL)TRUE);
            Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 10U;
            Appl_DrRestMode_CtrlModel_inner_default_Init
              (&DrRes_CurrentMoveType_prev_c);
          }
          else if (Appl_DrRestMode_CtrlModel_DW.is_Active ==
                   Appl_DrRestMode_CtrlModel_IN_Call)
          {
            Appl_DrRestMode_CtrlModel_B.State_ResDeal = 3U;
            Appl_DrRestMode_CtrlModel_B.DSM_MassageMode_Req = (INT8U)
              enMassageMode_DSM_EN_M1;

            /* ������ϱ�־λ==1 */
            if (Appl_DrRestMode_CtrlModel_B.MotroFault_Flag == 1)
            {
              Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
                enMassageLevel_DSM_EN_OFF;
              Appl_DrRestMode_CtrlModel_DW.is_Active =
                Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
                Appl_DrRestMode_CtrlModel_IN_Fault;
              Appl_DrRestMode_CtrlModel_B.State_ResDeal = 5U;
              Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
                enNapMode_EN_NapMode_ERR;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
            }
            else
            {
              /* С���óɹ���־==1
                 ||С����ʧ�ܱ�־==1 */
              if (Appl_DrRestMode_CtrlModel_B.CallRet != (INT32S)
                  enResCallRet_EN_Init)
              {
                Appl_DrRestMode_CtrlModel_DW.is_Active =
                  Appl_DrRestMode_CtrlModel_IN_CallOver;
                Appl_DrRestMode_CtrlModel_B.State_ResDeal = 4U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
              }
            }
          }
          else
          {
            Appl_DrRestMode_CtrlModel_B.State_ResDeal = 4U;
          }
        }
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Fault:
      Appl_DrRestMode_CtrlModel_B.State_ResDeal = 5U;
      Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
        enNapMode_EN_NapMode_ERR;

      /* ��Ħ���ϱ�־λ==0
         && ������ϱ�־λ==0
         && �̵���ճ������״̬==0 */
      if ((Appl_DrRestMode_CtrlModel_B.MassageFault_Flag == 0) &&
          (Appl_DrRestMode_CtrlModel_B.MotroFault_Flag == 0) &&
          (DrRes_AnyoneRelayFaultSts == 0))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Inactive;
        Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
          enNapMode_EN_NapMode_Close;
        Appl_DrRestMode_CtrlModel_DW.is_Inactive =
          Appl_DrRestMode_CtrlModel_IN_Init;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
        Appl_DrRestMode_CtrlModel_B.State_ResDeal = 1U;
        Appl_DrRestMode_CtrlModel_DW.StartFlag = ((BOOL)TRUE);
        Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 10U;
        Appl_DrRestMode_CtrlModel_inner_default_Init
          (&DrRes_CurrentMoveType_prev_c);
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
        enNapMode_EN_NapMode_Close;

      /* С���������־==1
         && (��Ħ���ϱ�־λ==1
         || �̵���ճ������״̬==1  */
      if ((Appl_DrRestMode_CtrlModel_B.Open_Flag == ((BOOL)TRUE)) &&
          ((Appl_DrRestMode_CtrlModel_B.MassageFault_Flag == 1) ||
           (DrRes_AnyoneRelayFaultSts == 1)))
      {
        Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
          enMassageLevel_DSM_EN_OFF;
        switch (Appl_DrRestMode_CtrlModel_DW.is_Inactive)
        {
         case Appl_DrRestMode_CtrlModel_IN_Init:
          Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 0U;
          Appl_DrRestMode_CtrlModel_DW.is_Inactive =
            Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
          break;

         case Appl_DrRestMode_CtrlModel_IN_WaitInit:
          Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 3U;
          Appl_DrRestMode_CtrlModel_DW.is_Inactive =
            Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
          break;

         default:
          Appl_DrRestMode_CtrlModel_DW.is_Inactive =
            Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
          break;
        }

        Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Fault;
        Appl_DrRestMode_CtrlModel_B.State_ResDeal = 5U;
        Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
          enNapMode_EN_NapMode_ERR;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
        Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
      }
      else
      {
        /* С���������־==1 ��ʱ���ѵȴ����
         /��λλ��=��һ�εĻ�λ���� */
        if ((Appl_DrRestMode_CtrlModel_B.Open_Flag == ((BOOL)TRUE)) &&
            (Appl_DrRestMode_CtrlModel_DW.WaitTimer >= 20) &&
            (Appl_DrRestMode_CtrlModel_DW.StartFlag == ((BOOL)TRUE)))
        {
          Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Height =
            DrResl_ReCallPosi_Height;
          Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Length =
            DrResl_ReCallPosi_Length;
          Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Back =
            DrResl_ReCallPosi_Back;
          Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Front =
            DrResl_ReCallPosi_Front;
          switch (Appl_DrRestMode_CtrlModel_DW.is_Inactive)
          {
           case Appl_DrRestMode_CtrlModel_IN_Init:
            Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 0U;
            Appl_DrRestMode_CtrlModel_DW.is_Inactive =
              Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
            break;

           case Appl_DrRestMode_CtrlModel_IN_WaitInit:
            Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 3U;
            Appl_DrRestMode_CtrlModel_DW.is_Inactive =
              Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
            break;

           default:
            Appl_DrRestMode_CtrlModel_DW.is_Inactive =
              Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
            break;
          }

          Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
            Appl_DrRestMode_CtrlModel_IN_Active;
          Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
            enNapMode_EN_NapMode_Open;
          Appl_DrRestMode_CtrlModel_DW.is_Active =
            Appl_DrRestMode_CtrlModel_IN_Call;
          Appl_DrRestMode_CtrlModel_B.State_ResDeal = 3U;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height =
            Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Height;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length =
            Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Length;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back =
            Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Back;
          Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front =
            Appl_DrRestMode_CtrlModel_DW.TempCallPosi_Front;
          Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
            enMassageLevel_DSM_EN_L3;
          Appl_DrRestMode_CtrlModel_B.DSM_MassageMode_Req = (INT8U)
            enMassageMode_DSM_EN_M1;
        }
        else
        {
          switch (Appl_DrRestMode_CtrlModel_DW.is_Inactive)
          {
           case Appl_DrRestMode_CtrlModel_IN_Init:
            Appl_DrRestMode_CtrlModel_B.State_ResDeal = 1U;
            Appl_DrRestMode_CtrlModel_inner_default_Init
              (&DrRes_CurrentMoveType_prev_c);
            break;

           case Appl_DrRestMode_CtrlModel_IN_ReCall:
            Appl_DrRestMode_CtrlModel_B.State_ResDeal = 2U;

            /* ������ϱ�־λ==1
               ||��Ħ���ϱ�־λ==1
               ||�̵���ճ������״̬==1 */
            if ((Appl_DrRestMode_CtrlModel_B.MotroFault_Flag == 1) ||
                (Appl_DrRestMode_CtrlModel_B.MassageFault_Flag == 1) ||
                (DrRes_AnyoneRelayFaultSts == 1))
            {
              Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req = (INT8U)
                enMassageLevel_DSM_EN_OFF;
              Appl_DrRestMode_CtrlModel_DW.is_Inactive =
                Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_DrRestMode_CtrlModel_DW.is_c8_Appl_DrRestMode_CtrlModel =
                Appl_DrRestMode_CtrlModel_IN_Fault;
              Appl_DrRestMode_CtrlModel_B.State_ResDeal = 5U;
              Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB = (INT8U)
                enNapMode_EN_NapMode_ERR;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
            }
            else
            {
              /* С���óɹ���־==1
                 ||С����ʧ�ܱ�־==1
                 ||С�ֹͣ������־==1 */
              if ((Appl_DrRestMode_CtrlModel_B.Stop_Flag == ((BOOL)TRUE)) ||
                  (Appl_DrRestMode_CtrlModel_B.CallRet != (INT32S)
                   enResCallRet_EN_Init))
              {
                Appl_DrRestMode_CtrlModel_DW.is_Inactive =
                  Appl_DrRestMode_CtrlModel_IN_Init;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
                Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
                Appl_DrRestMode_CtrlModel_B.State_ResDeal = 1U;
                Appl_DrRestMode_CtrlModel_DW.StartFlag = ((BOOL)TRUE);
                Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 10U;
                Appl_DrRestMode_CtrlModel_inner_default_Init
                  (&DrRes_CurrentMoveType_prev_c);
              }
            }
            break;

           default:
            /*  λ�ö�ȡ���  */
            if (Appl_DrRestMode_CtrlModel_DW.WaitTimer >= 20)
            {
              Appl_DrRestMode_CtrlModel_DW.SaveReTimer = 3U;
              Appl_DrRestMode_CtrlModel_DW.is_Inactive =
                Appl_DrRestMode_CtrlModel_IN_Init;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back = 0U;
              Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front = 0U;
              Appl_DrRestMode_CtrlModel_B.State_ResDeal = 1U;
              Appl_DrRestMode_CtrlModel_DW.StartFlag = ((BOOL)TRUE);
              Appl_DrRestMode_CtrlModel_DW.SavePosiCnt = 10U;
              Appl_DrRestMode_CtrlModel_inner_default_Init
                (&DrRes_CurrentMoveType_prev_c);
            }
            else
            {
              tmp = Appl_DrRestMode_CtrlModel_DW.WaitTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrRestMode_CtrlModel_DW.WaitTimer = (INT8U)tmp;
            }
            break;
          }
        }
      }
      break;
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_DrRestMode_CtrlModel_RTE(void)
{
  DrRes_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
  DrRes_AnyoneHallFaultSts = Rte_GetVfb_DrAnyoneHallErr( );
  DrRes_AnyoneRelayFaultSts = Rte_GetVfb_DrAnyoneRelayAdheErr( );
  DrRes_BackAutoRunFlag = Rte_GetVfb_DrBackAutoRunFlag( );
  DrRes_BackDefaultMotorSize = Cdd_GetMotorSize(EN_DriverBack);
  DrRes_BackDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverBack);
  DrRes_BackHallPosi = Cdd_GetCurrentHallCnt(EN_DriverBack);
  DrRes_BackLockFault = Rte_GetVfb_DrBackStallErr( );
  DrRes_CurrentMoveType = Rte_GetVfb_DrMoveType( );
  DrRes_DescBackHallFault = Rte_GetVfb_DrBackHallErr( );
  DrRes_DescFrontHallFault = Rte_GetVfb_DrFrontHallErr( );
  DrRes_DescHeightHallFault = Rte_GetVfb_DrHeightHallErr( );
  DrRes_DescLengthHallFault = Rte_GetVfb_DrLengthHallErr( );
  DrRes_EngineRunFlag = Rte_GetVfb_EngineRunFlag( );
  DrRes_FrontAutoRunFlag = Rte_GetVfb_DrFrontAutoRunFlag( );
  DrRes_FrontDefaulMotorSize = Cdd_GetMotorSize(EN_DriverFront);
  DrRes_FrontDefaulStoptPos = Cdd_GetMotorHardStop(EN_DriverFront);
  DrRes_FrontHallPosi = Cdd_GetCurrentHallCnt(EN_DriverFront);
  DrRes_FrontLockFault = Rte_GetVfb_DrFrontStallErr( );
  DrRes_HeightAutoRunFlag = Rte_GetVfb_DrHeightAutoRunFlag( );
  DrRes_HeightDefaultMotorSize = Cdd_GetMotorSize(EN_DriverHeight);
  DrRes_HeightDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverHeight);
  DrRes_HeightHallPosi = Cdd_GetCurrentHallCnt(EN_DriverHeight);
  DrRes_HeightLockFault = Rte_GetVfb_DrHeightStallErr( );
  DrRes_IVI_NapMode_SwtichSet = CanRx_0x367_IVI_NapMode_SwtichSet( );
  DrRes_LengthAutoRunFlag = Rte_GetVfb_DrLengthAutoRunFlag( );
  DrRes_LengthDefaultMotorSize = Cdd_GetMotorSize(EN_DriverLength);
  DrRes_LengthDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverLength);
  DrRes_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_DriverLength);
  DrRes_LengthLockFault = Rte_GetVfb_DrLengthStallErr( );
  DrRes_MassageMode_FB = LinSignalGet_Massage_1_Massage_ModeSts_FB( );
  DrRes_PowerMode = Rte_GetVfb_PowerMode( );
  DrRes_SeatLearnResult = Rte_GetVfb_DrLearnResult( );
  DrRes_SeatMassageCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageConfig);
  DrRes_VehicleRunFlag = Rte_GetVfb_VehicleRunFlag( );
  DrRes_VoltMode = Rte_GetVfb_VoltMode( );
  DrRes_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  DrRes_WelcomeEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
  DrResl_ReCallPosi_Back = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrRes_ReCallPosi_Back);
  DrResl_ReCallPosi_Front = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrRes_ReCallPosi_Front);
  DrResl_ReCallPosi_Height = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrRes_ReCallPosi_Height);
  DrResl_ReCallPosi_Length = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrRes_ReCallPosi_Length);
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrRestMode_CtrlModel_UpDataInputInfo_Init(void)
{
  Appl_DrRestMode_CtrlModel_DW.is_active_c11_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.CC1_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.CC1_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c6_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.CC2_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.CC2_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c1_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.CC3_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.CC3_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c7_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c7_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.CC4_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.CC4_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c2_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.CallRet = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c5_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.Temp_Drs_Distance = 0U;
  Appl_DrRestMode_CtrlModel_B.CallHallVall_Length = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_Init =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_DW.is_active_c15_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = 0U;
  Appl_DrRestMode_CtrlModel_B.Close_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c17_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c17_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c16_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c16_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c14_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_DW.RequestTimer = 0U;
  Appl_DrRestMode_CtrlModel_B.Open_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_active_c4_Appl_DrRestMode_CtrlModel = 0U;
  Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
    Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrRestMode_CtrlModel_B.Stop_Flag = 0U;
  Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = 0U;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrRestMode_CtrlModel_UpDataInputInfo(void)
{
  INT32U Temp_Drs_SoftStopPosi;
  enSeatMotorRunType DrRes_CurrentMoveType_prev;
  INT32S tmp;
  INT32U qY;
  BOOL guard1 = false;
  BOOL guard2 = false;
  Appl_DrRestMode_CtrlModel_RTE();
  if (Appl_DrRestMode_CtrlModel_DW.is_active_c11_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c11_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)TRUE);
    Appl_DrRestMode_CtrlModel_B.CC1_Reason = ((BOOL)FALSE);
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)FALSE);

      /* PC1&&PC2&&PC3&&PC4 &&PC5&&PC6&&PC8
         &&(PC9 ||PC10)

         ��ѹ��������ģʽ
         &&���F101�������֣������ΰ�Ħ���ܡ�= 0x01:Ture
         &&���F101�������֣����������ε��ڡ�= 0x02:Twelve way motor
         &&���F101�������֣������ݼ���ӭ�����ܡ�=0x01: TRUE
         &&����������ѧϰ
         &&�������θ��������������ڱ��ص����˶���
         &&ϵͳ��Դ����ON��
         &&���յ�������ΪECMD_EngineStatus=0x2=engine running��������DID F1FA�������֣���P20PHEV_100km & P20PHEV_50km��=0x00��Falseʱ���ã�
         || �յ���������״̬ΪVCU_VehRunSta= 0x1:HV ON /0x2:Ready��������DID F1FA�������֣���P20PHEV_100km / P20PHEV_50km��=0x01��Tureʱ���ã���  */
      if ((DrRes_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT) && (((BOOL)TRUE) ==
           DrRes_VoltSatisfy) && (DrRes_SeatMassageCfg == ((BOOL)TRUE)) &&
          (DrRes_AdjustEnable == (INT32S)enAdjustEnable_EN_TwelveWayMotor) &&
          (DrRes_WelcomeEnable == ((BOOL)TRUE)) && (DrRes_SeatLearnResult ==
           ((BOOL)TRUE)) && (DrRes_CurrentMoveType !=
                             enSeatMotorRunType_EN_ManualEnable) &&
          (DrRes_PowerMode == enPowerModeSts_EN_ON) && ((DrRes_EngineRunFlag ==
            ((BOOL)TRUE)) || (DrRes_VehicleRunFlag == ((BOOL)TRUE))))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_TRUE;
        Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)TRUE);
        Appl_DrRestMode_CtrlModel_B.CC1_Reason = ((BOOL)FALSE);
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)TRUE);

      /* CC1δ��λԭ�� ��DrRes_VoltMode����������  */
      if ((DrRes_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) || (((BOOL)TRUE)
           != DrRes_VoltSatisfy))
      {
        Appl_DrRestMode_CtrlModel_B.CC1_Reason = 1U;
        guard2 = true;
      }
      else
      {
        /* CC1δ��λԭ�� ��DrRes_SeatMassageCfg����������  */
        if (DrRes_SeatMassageCfg != ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.CC1_Reason = 2U;
          guard2 = true;
        }
        else
        {
          /* CC1δ��λԭ�� ��DrRes_AdjustEnable ���������� */
          if (DrRes_AdjustEnable != (INT32S)enAdjustEnable_EN_TwelveWayMotor)
          {
            Appl_DrRestMode_CtrlModel_B.CC1_Reason = 3U;
            guard2 = true;
          }
          else
          {
            /* CC1δ��λԭ�� ��DrRes_WelcomeEnable����������  */
            if (DrRes_WelcomeEnable != ((BOOL)TRUE))
            {
              Appl_DrRestMode_CtrlModel_B.CC1_Reason = 4U;
              guard2 = true;
            }
            else
            {
              /* CC1δ��λԭ�� ��DrRes_SeatLearnResult ���������� */
              if (DrRes_SeatLearnResult != ((BOOL)TRUE))
              {
                Appl_DrRestMode_CtrlModel_B.CC1_Reason = 5U;
                guard2 = true;
              }
              else
              {
                /* CC1δ��λԭ�� ��DrRes_CurrentMoveType����������  */
                if (DrRes_CurrentMoveType == enSeatMotorRunType_EN_ManualEnable)
                {
                  Appl_DrRestMode_CtrlModel_B.CC1_Reason = 6U;
                  guard2 = true;
                }
                else
                {
                  /* CC1δ��λԭ�� ��DrRes_PowerMode����������  */
                  if (DrRes_PowerMode != enPowerModeSts_EN_ON)
                  {
                    Appl_DrRestMode_CtrlModel_B.CC1_Reason = 7U;
                    guard2 = true;
                  }
                  else
                  {
                    /* CC1δ��λԭ�� ��DrRes_EngineRunFlag/��DrRes_VehicleRunFlag����������  */
                    if ((DrRes_EngineRunFlag != ((BOOL)TRUE)) &&
                        (DrRes_VehicleRunFlag != ((BOOL)TRUE)))
                    {
                      Appl_DrRestMode_CtrlModel_B.CC1_Reason = 8U;
                      guard2 = true;
                    }
                    else
                    {
                      /* PC1&&PC2&&PC3&&PC4 &&PC5&&PC6&&PC8
                         &&(PC9 ||PC10)

                         ��ѹ��������ģʽ
                         &&���F101�������֣������ΰ�Ħ���ܡ�= 0x01:Ture
                         &&���F101�������֣����������ε��ڡ�= 0x02:Twelve way motor
                         &&���F101�������֣������ݼ���ӭ�����ܡ�=0x01: TRUE
                         &&����������ѧϰ
                         &&�������θ��������������ڱ��ص����˶���
                         &&ϵͳ��Դ����ON��
                         &&���յ�������ΪECMD_EngineStatus=0x2=engine running��������DID F1FA�������֣���P20PHEV_100km & P20PHEV_50km��=0x00��Falseʱ���ã�
                         || �յ���������״̬ΪVCU_VehRunSta= 0x1:HV ON /0x2:Ready��������DID F1FA�������֣���P20PHEV_100km / P20PHEV_50km��=0x01��Tureʱ���ã���  */
                      if ((DrRes_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT) &&
                          (((BOOL)TRUE) == DrRes_VoltSatisfy) &&
                          (DrRes_SeatMassageCfg == ((BOOL)TRUE)) &&
                          (DrRes_AdjustEnable == (INT32S)
                           enAdjustEnable_EN_TwelveWayMotor) &&
                          (DrRes_WelcomeEnable == ((BOOL)TRUE)) &&
                          (DrRes_SeatLearnResult == ((BOOL)TRUE)) &&
                          (DrRes_CurrentMoveType !=
                           enSeatMotorRunType_EN_ManualEnable) &&
                          (DrRes_PowerMode == enPowerModeSts_EN_ON) &&
                          ((DrRes_EngineRunFlag == ((BOOL)TRUE)) ||
                           (DrRes_VehicleRunFlag == ((BOOL)TRUE))))
                      {
                        Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel
                          = Appl_DrRestMode_CtrlModel_IN_TRUE;
                        Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)TRUE);
                        Appl_DrRestMode_CtrlModel_B.CC1_Reason = ((BOOL)FALSE);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)TRUE);

      /* CC1δ��λԭ�� ��DrRes_VoltMode����������  */
      if ((DrRes_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) || (((BOOL)TRUE)
           != DrRes_VoltSatisfy))
      {
        Appl_DrRestMode_CtrlModel_B.CC1_Reason = 1U;
        guard1 = true;
      }
      else
      {
        /* CC1δ��λԭ�� ��DrRes_SeatMassageCfg����������  */
        if (DrRes_SeatMassageCfg != ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.CC1_Reason = 2U;
          guard1 = true;
        }
        else
        {
          /* CC1δ��λԭ�� ��DrRes_AdjustEnable ���������� */
          if (DrRes_AdjustEnable != (INT32S)enAdjustEnable_EN_TwelveWayMotor)
          {
            Appl_DrRestMode_CtrlModel_B.CC1_Reason = 3U;
            guard1 = true;
          }
          else
          {
            /* CC1δ��λԭ�� ��DrRes_WelcomeEnable����������  */
            if (DrRes_WelcomeEnable != ((BOOL)TRUE))
            {
              Appl_DrRestMode_CtrlModel_B.CC1_Reason = 4U;
              guard1 = true;
            }
            else
            {
              /* CC1δ��λԭ�� ��DrRes_SeatLearnResult ���������� */
              if (DrRes_SeatLearnResult != ((BOOL)TRUE))
              {
                Appl_DrRestMode_CtrlModel_B.CC1_Reason = 5U;
                guard1 = true;
              }
              else
              {
                /* CC1δ��λԭ�� ��DrRes_CurrentMoveType����������  */
                if (DrRes_CurrentMoveType == enSeatMotorRunType_EN_ManualEnable)
                {
                  Appl_DrRestMode_CtrlModel_B.CC1_Reason = 6U;
                  guard1 = true;
                }
                else
                {
                  /* CC1δ��λԭ�� ��DrRes_PowerMode����������  */
                  if (DrRes_PowerMode != enPowerModeSts_EN_ON)
                  {
                    Appl_DrRestMode_CtrlModel_B.CC1_Reason = 7U;
                    guard1 = true;
                  }
                  else
                  {
                    /* CC1δ��λԭ�� ��DrRes_EngineRunFlag/��DrRes_VehicleRunFlag����������  */
                    if ((DrRes_EngineRunFlag != ((BOOL)TRUE)) &&
                        (DrRes_VehicleRunFlag != ((BOOL)TRUE)))
                    {
                      Appl_DrRestMode_CtrlModel_B.CC1_Reason = 8U;
                      guard1 = true;
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;
    }

    if (guard2)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c11_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC1_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c6_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c6_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)FALSE);
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)FALSE);

      /*  !PC3 ||!PC4 ||!PC5
         ���F101�������֣����������ε��ڡ���= 0x02:Twelve way motor
         || ���F101�������֣������ݼ���ӭ�����ܡ���=0x01: TRUE
         ||��������δѧϰ   */
      if ((DrRes_AdjustEnable != (INT32S)enAdjustEnable_EN_TwelveWayMotor) ||
          (DrRes_WelcomeEnable != ((BOOL)TRUE)) || (DrRes_SeatLearnResult !=
           ((BOOL)TRUE)))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_TRUE;
        Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)TRUE);
        Appl_DrRestMode_CtrlModel_B.CC2_Reason = ((BOOL)FALSE);
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)FALSE);

      /* CC2δ��λԭ�� ��DrRes_AdjustEnable����������  */
      if (DrRes_AdjustEnable == (INT32S)enAdjustEnable_EN_TwelveWayMotor)
      {
        Appl_DrRestMode_CtrlModel_B.CC2_Reason = 1U;
        guard2 = true;
      }
      else
      {
        /* CC2δ��λԭ�� ��DrRes_WelcomeEnable ���������� */
        if (DrRes_WelcomeEnable == ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.CC2_Reason = 2U;
          guard2 = true;
        }
        else
        {
          /* CC2δ��λԭ�� ��DrRes_SeatLearnResult����������  */
          if (DrRes_SeatLearnResult == ((BOOL)TRUE))
          {
            Appl_DrRestMode_CtrlModel_B.CC2_Reason = 3U;
            guard2 = true;
          }
          else
          {
            /*  !PC3 ||!PC4 ||!PC5
               ���F101�������֣����������ε��ڡ���= 0x02:Twelve way motor
               || ���F101�������֣������ݼ���ӭ�����ܡ���=0x01: TRUE
               ||��������δѧϰ   */
            if ((DrRes_AdjustEnable != (INT32S)enAdjustEnable_EN_TwelveWayMotor)
                || (DrRes_WelcomeEnable != ((BOOL)TRUE)) ||
                (DrRes_SeatLearnResult != ((BOOL)TRUE)))
            {
              Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
                Appl_DrRestMode_CtrlModel_IN_TRUE;
              Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)TRUE);
              Appl_DrRestMode_CtrlModel_B.CC2_Reason = ((BOOL)FALSE);
            }
          }
        }
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)TRUE);

      /* CC2δ��λԭ�� ��DrRes_AdjustEnable����������  */
      if (DrRes_AdjustEnable == (INT32S)enAdjustEnable_EN_TwelveWayMotor)
      {
        Appl_DrRestMode_CtrlModel_B.CC2_Reason = 1U;
        guard1 = true;
      }
      else
      {
        /* CC2δ��λԭ�� ��DrRes_WelcomeEnable ���������� */
        if (DrRes_WelcomeEnable == ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.CC2_Reason = 2U;
          guard1 = true;
        }
        else
        {
          /* CC2δ��λԭ�� ��DrRes_SeatLearnResult����������  */
          if (DrRes_SeatLearnResult == ((BOOL)TRUE))
          {
            Appl_DrRestMode_CtrlModel_B.CC2_Reason = 3U;
            guard1 = true;
          }
        }
      }
      break;
    }

    if (guard2)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c6_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC2_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c1_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c1_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)FALSE);
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)FALSE);

      /*  !PC2 ||!PC8 ||��!PC9 && !PC10 ��
         ���F101�������֣������ΰ�Ħ���ܡ���= 0x01:Ture
         ||ϵͳ��Դ������ON��
         ||���յ�������ΪECMD_EngineStatus��=0x2=engine running��������DID F1FA�������֣���P20PHEV_100km & P20PHEV_50km��=0x00��Falseʱ���ã�
         && �յ���������״̬ΪVCU_VehRunSta��= 0x1:HV ON /0x2:Ready��������DID F1FA�������֣���P20PHEV_100km / P20PHEV_50km��=0x01��Tureʱ���ã���  */
      if ((DrRes_SeatMassageCfg != ((BOOL)TRUE)) || (DrRes_PowerMode !=
           enPowerModeSts_EN_ON) || ((DrRes_EngineRunFlag != ((BOOL)TRUE)) &&
           (DrRes_VehicleRunFlag != ((BOOL)TRUE))))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_TRUE;
        Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)TRUE);
        Appl_DrRestMode_CtrlModel_B.CC3_Reason = ((BOOL)FALSE);
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)FALSE);

      /* CC3δ��λԭ�� ��DrRes_SeatMassageCfg ����������  */
      if (DrRes_SeatMassageCfg == ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.CC3_Reason = 1U;
        guard2 = true;
      }
      else
      {
        /* CC3δ��λԭ�� ��DrRes_PowerMode ���������� */
        if (DrRes_PowerMode == enPowerModeSts_EN_ON)
        {
          Appl_DrRestMode_CtrlModel_B.CC3_Reason = 2U;
          guard2 = true;
        }
        else
        {
          /* CC3δ��λԭ�� ��DrRes_EngineRunFlag/DrRes_VehicleRunFlag����������  */
          if ((DrRes_EngineRunFlag == ((BOOL)TRUE)) && (DrRes_VehicleRunFlag ==
               ((BOOL)TRUE)))
          {
            Appl_DrRestMode_CtrlModel_B.CC3_Reason = 3U;
            guard2 = true;
          }
          else
          {
            /*  !PC2 ||!PC8 ||��!PC9 && !PC10 ��
               ���F101�������֣������ΰ�Ħ���ܡ���= 0x01:Ture
               ||ϵͳ��Դ������ON��
               ||���յ�������ΪECMD_EngineStatus��=0x2=engine running��������DID F1FA�������֣���P20PHEV_100km & P20PHEV_50km��=0x00��Falseʱ���ã�
               && �յ���������״̬ΪVCU_VehRunSta��= 0x1:HV ON /0x2:Ready��������DID F1FA�������֣���P20PHEV_100km / P20PHEV_50km��=0x01��Tureʱ���ã���  */
            if ((DrRes_SeatMassageCfg != ((BOOL)TRUE)) || (DrRes_PowerMode !=
                 enPowerModeSts_EN_ON) || ((DrRes_EngineRunFlag == ((BOOL)TRUE))
                 || (DrRes_VehicleRunFlag == ((BOOL)TRUE))))
            {
              Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
                Appl_DrRestMode_CtrlModel_IN_TRUE;
              Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)TRUE);
              Appl_DrRestMode_CtrlModel_B.CC3_Reason = ((BOOL)FALSE);
            }
          }
        }
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)TRUE);

      /* CC3δ��λԭ�� ��DrRes_SeatMassageCfg ����������  */
      if (DrRes_SeatMassageCfg == ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.CC3_Reason = 1U;
        guard1 = true;
      }
      else
      {
        /* CC3δ��λԭ�� ��DrRes_PowerMode ���������� */
        if (DrRes_PowerMode == enPowerModeSts_EN_ON)
        {
          Appl_DrRestMode_CtrlModel_B.CC3_Reason = 2U;
          guard1 = true;
        }
        else
        {
          /* CC3δ��λԭ�� ��DrRes_EngineRunFlag/DrRes_VehicleRunFlag����������  */
          if ((DrRes_EngineRunFlag == ((BOOL)TRUE)) || (DrRes_VehicleRunFlag ==
               ((BOOL)TRUE)))
          {
            Appl_DrRestMode_CtrlModel_B.CC3_Reason = 3U;
            guard1 = true;
          }
        }
      }
      break;
    }

    if (guard2)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c1_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC3_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c7_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c7_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c7_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_FALSE;
    Appl_DrRestMode_CtrlModel_B.CC4_Flag = ((BOOL)FALSE);
  }
  else if (Appl_DrRestMode_CtrlModel_DW.is_c7_Appl_DrRestMode_CtrlModel ==
           Appl_DrRestMode_CtrlModel_IN_FALSE)
  {
    Appl_DrRestMode_CtrlModel_B.CC4_Flag = ((BOOL)FALSE);

    /*  C6 & C7
       ������������һ�����������   */
    if ((DrRes_DescHeightHallFault != ((BOOL)TRUE)) &&
        (DrRes_DescLengthHallFault != ((BOOL)TRUE)) && (DrRes_DescBackHallFault
         != ((BOOL)TRUE)) && (DrRes_DescFrontHallFault != ((BOOL)TRUE)) &&
        (DrRes_HeightLockFault != ((BOOL)TRUE)) && (DrRes_LengthLockFault !=
         ((BOOL)TRUE)) && (DrRes_BackLockFault != ((BOOL)TRUE)) &&
        (DrRes_FrontLockFault != ((BOOL)TRUE)))
    {
      Appl_DrRestMode_CtrlModel_DW.is_c7_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_TRUE_n;
      Appl_DrRestMode_CtrlModel_B.CC4_Flag = ((BOOL)TRUE);
      Appl_DrRestMode_CtrlModel_B.CC4_Reason = ((BOOL)FALSE);
    }
  }
  else
  {
    Appl_DrRestMode_CtrlModel_B.CC4_Flag = ((BOOL)TRUE);

    /* CC4δ��λԭ�� ��DrRes_AnyoneHallFaultSts ���������� */
    if ((DrRes_DescHeightHallFault == ((BOOL)TRUE)) ||
        (DrRes_DescLengthHallFault == ((BOOL)TRUE)) || (DrRes_DescBackHallFault ==
         ((BOOL)TRUE)) || (DrRes_DescFrontHallFault == ((BOOL)TRUE)) ||
        (DrRes_HeightLockFault == ((BOOL)TRUE)) || (DrRes_LengthLockFault ==
         ((BOOL)TRUE)) || (DrRes_BackLockFault == ((BOOL)TRUE)) ||
        (DrRes_FrontLockFault == ((BOOL)TRUE)))
    {
      Appl_DrRestMode_CtrlModel_B.CC4_Reason = 1U;
      Appl_DrRestMode_CtrlModel_DW.is_c7_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.CC4_Flag = ((BOOL)FALSE);
    }
  }

  DrRes_CurrentMoveType_prev =
    Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start;
  Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start =
    DrRes_CurrentMoveType;
  if (Appl_DrRestMode_CtrlModel_DW.is_active_c2_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c2_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_l;
    Appl_DrRestMode_CtrlModel_B.CallRet = (INT8U)enResCallRet_EN_Init;
  }
  else if (Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel ==
           Appl_DrRestMode_CtrlModel_IN_Init_l)
  {
    /*
       �߶��Զ����гɹ���־λ == FALSE
       || �����Զ����гɹ���־λ == FALSE
       || �����Զ����гɹ���־λ == FALSE
       || ǰ���Զ����гɹ���־λ == FALSE
     */
    if ((DrRes_HeightAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
        (DrRes_LengthAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
        (DrRes_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
        (DrRes_FrontAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
        ((DrRes_CurrentMoveType != enSeatMotorRunType_EN_ResEnable) &&
         (DrRes_CurrentMoveType != enSeatMotorRunType_EN_HUMEnable) &&
         (DrRes_CurrentMoveType != enSeatMotorRunType_EN_ComfortEnable) &&
         (DrRes_CurrentMoveType != enSeatMotorRunType_EN_MemoryEnable) &&
         (DrRes_CurrentMoveType != enSeatMotorRunType_EN_NULL)))
    {
      Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_Ret;
      Appl_DrRestMode_CtrlModel_B.CallRet = (INT8U)enResCallRet_EN_Fail;
    }
    else
    {
      /* (�߶��Զ����гɹ���־λ == 2 || �߶ȶ�ת)
         && (�����Զ����гɹ���־λ == 2 || �����ת)
         && (�����Զ����гɹ���־λ == 2 || ������ת)
         && (ǰ���Զ����гɹ���־λ == 2 || ǰ����ת)    */
      if (((DrRes_HeightAutoRunFlag == enSeatAutoRunSts_EN_SEAT_SUCCESS) ||
           (DrRes_HeightLockFault == ((BOOL)TRUE))) && ((DrRes_LengthAutoRunFlag
            == enSeatAutoRunSts_EN_SEAT_SUCCESS) || (DrRes_LengthLockFault ==
            ((BOOL)TRUE))) && ((DrRes_BackAutoRunFlag ==
            enSeatAutoRunSts_EN_SEAT_SUCCESS) || (DrRes_BackLockFault == ((BOOL)
             TRUE))) && ((DrRes_FrontAutoRunFlag ==
                          enSeatAutoRunSts_EN_SEAT_SUCCESS) ||
                         (DrRes_FrontLockFault == ((BOOL)TRUE))))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Ret;
        Appl_DrRestMode_CtrlModel_B.CallRet = (INT8U)enResCallRet_EN_Success;
      }
    }
  }
  else
  {
    /*     */
    if (((DrRes_HeightAutoRunFlag == enSeatAutoRunSts_EN_SEAT_INVALID) &&
         (DrRes_LengthAutoRunFlag == enSeatAutoRunSts_EN_SEAT_INVALID) &&
         (DrRes_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_INVALID) &&
         (DrRes_FrontAutoRunFlag == enSeatAutoRunSts_EN_SEAT_INVALID) &&
         (DrRes_CurrentMoveType == enSeatMotorRunType_EN_NULL)) ||
        ((DrRes_CurrentMoveType_prev !=
          Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start) &&
         (Appl_DrRestMode_CtrlModel_DW.DrRes_CurrentMoveType_start ==
          enSeatMotorRunType_EN_ResEnable)))
    {
      Appl_DrRestMode_CtrlModel_DW.is_c2_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_Init_l;
      Appl_DrRestMode_CtrlModel_B.CallRet = (INT8U)enResCallRet_EN_Init;
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c5_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c5_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.Temp_Drs_Distance = (INT32U)
      (DrRes_LengthDefaultMotorSize * ((INT8U)D_ClickNapLengthPosi) / 100);
  }
  else
  {
    /* ����������������ֹ������   */
    qY = DrRes_LengthHallPosi - Appl_DrRestMode_CtrlModel_DW.Temp_Drs_Distance;
    if (qY > DrRes_LengthHallPosi)
    {
      qY = 0U;
    }

    Temp_Drs_SoftStopPosi = (INT32U)(DrRes_LengthDefaultStopPos + ((INT8U)
      D_SoftDistanceDrLegnth));

    /* �������������ֹ������ - ���ƶ�����������  */
    if (qY > Temp_Drs_SoftStopPosi)
    {
      Appl_DrRestMode_CtrlModel_B.CallHallVall_Length = (INT16U)qY;
    }
    else
    {
      /*  ��ǰ����С�ں�ֹ������ ������ */
      if (DrRes_LengthHallPosi <= Temp_Drs_SoftStopPosi)
      {
        Appl_DrRestMode_CtrlModel_B.CallHallVall_Length = 0U;
      }
      else
      {
        Appl_DrRestMode_CtrlModel_B.CallHallVall_Length = (INT16U)
          Temp_Drs_SoftStopPosi;
      }
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c15_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c15_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_DW.is_Init = Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
  }
  else if (Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel ==
           Appl_DrRestMode_CtrlModel_IN_CLOSE)
  {
    Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)TRUE);
    if ((Appl_DrRestMode_CtrlModel_DW.RequestTimer_h >= 20) &&
        (Appl_DrRestMode_CtrlModel_B.CC3_Flag != ((BOOL)TRUE)))
    {
      Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_Init_h;
      Appl_DrRestMode_CtrlModel_DW.is_Init = Appl_DrRestMode_CtrlModel_IN_Init_h;
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
    }
    else
    {
      tmp = Appl_DrRestMode_CtrlModel_DW.RequestTimer_h + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = (INT8U)tmp;
    }
  }
  else if (Appl_DrRestMode_CtrlModel_B.CC3_Flag == ((BOOL)TRUE))
  {
    Appl_DrRestMode_CtrlModel_DW.is_Init =
      Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
    Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_CLOSE;
    Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)TRUE);
    Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = 0U;
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_DrRestMode_CtrlModel_DW.is_Init)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);

      /*  (PC7&&PC11&&C5)||CC3
         ������������һ����̵���ճ������
         && ��Ħģ���޹��ϣ�DSM_MassageMode_FB��0x8��Errorģ�����
       */
      if ((DrRes_AnyoneRelayFaultSts != ((BOOL)TRUE)) || (DrRes_MassageMode_FB
           != enMassageMode_DSM_EN_MError))
      {
        Appl_DrRestMode_CtrlModel_DW.is_Init =
          Appl_DrRestMode_CtrlModel_IN_Ready;
        Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = 0U;
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);

      /* Close_Flagδ��λԭ�� ��DrRes_AnyoneRelayFaultSts����������  */
      if (DrRes_AnyoneRelayFaultSts == ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = 1U;
        guard2 = true;
      }
      else
      {
        /* Close_Flagδ��λԭ�� ��DrRes_MassageMode_FB����������  */
        if (DrRes_MassageMode_FB == enMassageMode_DSM_EN_MError)
        {
          Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = 2U;
          guard2 = true;
        }
        else
        {
          /*  (PC7&&PC11&&C5)||CC3
             ������������һ����̵���ճ������
             && ��Ħģ���޹��ϣ�DSM_MassageMode_FB��0x8��Errorģ�����
           */
          if ((DrRes_AnyoneRelayFaultSts != ((BOOL)TRUE)) ||
              (DrRes_MassageMode_FB != enMassageMode_DSM_EN_MError))
          {
            Appl_DrRestMode_CtrlModel_DW.is_Init =
              Appl_DrRestMode_CtrlModel_IN_Ready;
            Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
            Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = ((BOOL)FALSE);
            Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = 0U;
          }
        }
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);

      /* Close_Flagδ��λԭ�� ��DrRes_AnyoneRelayFaultSts����������  */
      if (DrRes_AnyoneRelayFaultSts == ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = 1U;
        guard1 = true;
      }
      else
      {
        /* Close_Flagδ��λԭ�� ��DrRes_MassageMode_FB����������  */
        if (DrRes_MassageMode_FB == enMassageMode_DSM_EN_MError)
        {
          Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason = 2U;
          guard1 = true;
        }
        else
        {
          /* �յ�С�ģʽ�����źţ�IVI_NapMode_SwtichSet����0x2:�ر�С�ģʽ */
          if (DrRes_IVI_NapMode_SwtichSet == 2)
          {
            Appl_DrRestMode_CtrlModel_DW.is_Init =
              Appl_DrRestMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
            Appl_DrRestMode_CtrlModel_DW.is_c15_Appl_DrRestMode_CtrlModel =
              Appl_DrRestMode_CtrlModel_IN_CLOSE;
            Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)TRUE);
            Appl_DrRestMode_CtrlModel_DW.RequestTimer_h = 0U;
          }
        }
      }
      break;
    }

    if (guard2)
    {
      Appl_DrRestMode_CtrlModel_DW.is_Init = Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_DrRestMode_CtrlModel_DW.is_Init = Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.Close_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c17_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c17_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c17_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_TRUE_n;
    Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = ((BOOL)TRUE);
  }
  else if (Appl_DrRestMode_CtrlModel_DW.is_c17_Appl_DrRestMode_CtrlModel ==
           Appl_DrRestMode_CtrlModel_IN_FALSE)
  {
    Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = ((BOOL)FALSE);

    /*  ��PC11
       ��Ħģ���޹��ϣ�DSM_MassageMode_FB==0x8��Errorģ����� */
    if (DrRes_MassageMode_FB == enMassageMode_DSM_EN_MError)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c17_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_TRUE_n;
      Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = ((BOOL)TRUE);
    if (DrRes_MassageMode_FB != enMassageMode_DSM_EN_MError)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c17_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.MassageFault_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c16_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c16_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c16_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_TRUE_n;
    Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = ((BOOL)TRUE);
  }
  else if (Appl_DrRestMode_CtrlModel_DW.is_c16_Appl_DrRestMode_CtrlModel ==
           Appl_DrRestMode_CtrlModel_IN_FALSE)
  {
    Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = ((BOOL)FALSE);

    /*  ��CC4
       CC4��־λ == 0  */
    if (Appl_DrRestMode_CtrlModel_B.CC4_Flag == 0)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c16_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_TRUE_n;
      Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = ((BOOL)TRUE);
    if (Appl_DrRestMode_CtrlModel_B.CC4_Flag == ((BOOL)TRUE))
    {
      Appl_DrRestMode_CtrlModel_DW.is_c16_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.MotroFault_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c14_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c14_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
  }
  else
  {
    switch (Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);

      /*  CC1&&PC7&&PC11&&C4
         CC1��־λ == 1
         && ������������һ����̵���ճ������
         && ��Ħģ���޹��ϣ�DSM_MassageMode_FB��0x8��Errorģ�����
       */
      if (Appl_DrRestMode_CtrlModel_B.CC1_Flag == ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Ready_b;
        Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_DW.RequestTimer = 0U;
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);

      /* Open_Flagδ��λԭ�� ��CC1_Flag����������  */
      if (Appl_DrRestMode_CtrlModel_B.CC1_Flag != ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = 1U;
        Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_FALSE;
        Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
      }
      else
      {
        /*  CC1&&PC7&&PC11&&C4
           CC1��־λ == 1
           && ������������һ����̵���ճ������
           && ��Ħģ���޹��ϣ�DSM_MassageMode_FB��0x8��Errorģ�����
         */
        if (Appl_DrRestMode_CtrlModel_B.CC1_Flag == ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
            Appl_DrRestMode_CtrlModel_IN_Ready_b;
          Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
          Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = ((BOOL)FALSE);
          Appl_DrRestMode_CtrlModel_DW.RequestTimer = 0U;
        }
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Open:
      Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)TRUE);
      if (Appl_DrRestMode_CtrlModel_DW.RequestTimer >= 20)
      {
        Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_Ready_b;
        Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = ((BOOL)FALSE);
        Appl_DrRestMode_CtrlModel_DW.RequestTimer = 0U;
      }
      else
      {
        tmp = Appl_DrRestMode_CtrlModel_DW.RequestTimer + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_DrRestMode_CtrlModel_DW.RequestTimer = (INT8U)tmp;
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);

      /* Open_Flagδ��λԭ�� ��CC1_Flag����������  */
      if (Appl_DrRestMode_CtrlModel_B.CC1_Flag != ((BOOL)TRUE))
      {
        Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = 1U;
        Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_FALSE;
        Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)FALSE);
      }
      else
      {
        /*  CC1&&PC7&&PC11&&C4
           �յ�С�ģʽ�����źţ�IVI_NapMode_SwtichSet����0x1:��С�ģʽ  */
        if (DrRes_IVI_NapMode_SwtichSet == 1)
        {
          Appl_DrRestMode_CtrlModel_DW.is_c14_Appl_DrRestMode_CtrlModel =
            Appl_DrRestMode_CtrlModel_IN_Open;
          Appl_DrRestMode_CtrlModel_B.Open_Flag = ((BOOL)TRUE);
          Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason = ((BOOL)FALSE);
          Appl_DrRestMode_CtrlModel_DW.RequestTimer = 0U;
        }
      }
      break;
    }
  }

  if (Appl_DrRestMode_CtrlModel_DW.is_active_c4_Appl_DrRestMode_CtrlModel == 0U)
  {
    Appl_DrRestMode_CtrlModel_DW.is_active_c4_Appl_DrRestMode_CtrlModel = 1U;
    Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
      Appl_DrRestMode_CtrlModel_IN_Init_h;
    Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)FALSE);
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel)
    {
     case Appl_DrRestMode_CtrlModel_IN_FALSE:
      Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)FALSE);

      /* !PC1||CC2
         ��ѹ����������ģʽ
         ||CC2��־λ == 1 */
      if ((DrRes_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) || (((BOOL)TRUE)
           != DrRes_VoltSatisfy) || (Appl_DrRestMode_CtrlModel_B.CC2_Flag ==
           ((BOOL)TRUE)))
      {
        Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
          Appl_DrRestMode_CtrlModel_IN_TRUE;
        Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)TRUE);
        Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = ((BOOL)FALSE);
      }
      break;

     case Appl_DrRestMode_CtrlModel_IN_Init_h:
      Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)FALSE);

      /* Stop_Flagδ��λԭ�� ��DrRes_VoltMode ����������  */
      if ((DrRes_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT) && (((BOOL)TRUE) ==
           DrRes_VoltSatisfy))
      {
        Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = 1U;
        guard2 = true;
      }
      else
      {
        /* Stop_Flagδ��λԭ�� ��CC2_Flag ����������  */
        if (Appl_DrRestMode_CtrlModel_B.CC2_Flag != ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = 2U;
          guard2 = true;
        }
        else
        {
          /* !PC1||CC2
             ��ѹ����������ģʽ
             ||CC2��־λ == 1 */
          if ((DrRes_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) || (((BOOL)
                TRUE) != DrRes_VoltSatisfy) ||
              (Appl_DrRestMode_CtrlModel_B.CC2_Flag == ((BOOL)TRUE)))
          {
            Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
              Appl_DrRestMode_CtrlModel_IN_TRUE;
            Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)TRUE);
            Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = ((BOOL)FALSE);
          }
        }
      }
      break;

     default:
      Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)TRUE);

      /* Stop_Flagδ��λԭ�� ��DrRes_VoltMode ����������  */
      if ((DrRes_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT) && (((BOOL)TRUE) ==
           DrRes_VoltSatisfy))
      {
        Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = 1U;
        guard1 = true;
      }
      else
      {
        /* Stop_Flagδ��λԭ�� ��CC2_Flag ����������  */
        if (Appl_DrRestMode_CtrlModel_B.CC2_Flag != ((BOOL)TRUE))
        {
          Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason = 2U;
          guard1 = true;
        }
      }
      break;
    }

    if (guard2)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_DrRestMode_CtrlModel_DW.is_c4_Appl_DrRestMode_CtrlModel =
        Appl_DrRestMode_CtrlModel_IN_FALSE;
      Appl_DrRestMode_CtrlModel_B.Stop_Flag = ((BOOL)FALSE);
    }
  }

  Appl_DrRestMode_CtrlModel_B.Add = (INT16U)((INT32U)(INT16U)((INT32U)
    DrRes_BackDefaultMotorSize * ((INT8U)D_ClickNapBackPosi) / 100U) +
    DrRes_BackDefaultStopPos);
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_DrRestMode_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_Res_MassageLevel_Req
    (Appl_DrRestMode_CtrlModel_B.DSM_MassageLevel_Req);
  Rte_SetVfb_Res_MassageMode_Req(Appl_DrRestMode_CtrlModel_B.DSM_MassageMode_Req);
  CanTx_0x3B2_DSM_NapMode_FB(Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB);
  Rte_SetVfb_NapMode(Appl_DrRestMode_CtrlModel_B.DSM_NapMode_FB);
  Rte_SetVfb_Debug_Res_Stop_Flag(Appl_DrRestMode_CtrlModel_B.Stop_Flag_f);
  Rte_SetVfb_Debug_Res_CC1_Flag(Appl_DrRestMode_CtrlModel_B.CC1_Flag_m);
  Rte_SetVfb_Debug_Res_CC1_Reason(Appl_DrRestMode_CtrlModel_B.CC1_Reason_m);
  Rte_SetVfb_Debug_Res_CC2_Flag(Appl_DrRestMode_CtrlModel_B.CC2_Flag_m);
  Rte_SetVfb_Debug_Res_CC2_Reason(Appl_DrRestMode_CtrlModel_B.CC2_Reason_b);
  Rte_SetVfb_Debug_Res_CC3_Flag(Appl_DrRestMode_CtrlModel_B.CC3_Flag_b);
  Rte_SetVfb_Debug_Res_CC3_Reason(Appl_DrRestMode_CtrlModel_B.CC3_Reason_n);
  Rte_SetVfb_Debug_Res_CC4_Flag(Appl_DrRestMode_CtrlModel_B.CC4_Flag_g);
  Rte_SetVfb_Debug_Res_CC4_Reason(Appl_DrRestMode_CtrlModel_B.CC4_Reason_p);
  Rte_SetVfb_Debug_Res_Stop_Flag_Reason
    (Appl_DrRestMode_CtrlModel_B.Stop_Flag_Reason_o);
  Rte_SetVfb_Debug_Res_Open_Flag(Appl_DrRestMode_CtrlModel_B.Open_Flag_e);
  Rte_SetVfb_Debug_Res_Open_Flag_Reason
    (Appl_DrRestMode_CtrlModel_B.Open_Flag_Reason_b);
  Rte_SetVfb_Debug_Res_Colse_Flag(Appl_DrRestMode_CtrlModel_B.Close_Flag_f);
  Rte_SetVfb_Debug_Res_Colse_Flag_Reason
    (Appl_DrRestMode_CtrlModel_B.Close_Flag_Reason_h);
  Rte_SetVfb_Debug_Res_MotroFault_Flag
    (Appl_DrRestMode_CtrlModel_B.MotorFault_Flag);
  Rte_SetVfb_Debug_Res_MassageFault_Flag
    (Appl_DrRestMode_CtrlModel_B.MassageFault_Flag_l);
  Rte_SetVfb_Debug_Res_DrRestCAllRet(Appl_DrRestMode_CtrlModel_B.DrRestCAll_Ret);
  Rte_SetVfb_DrResBackReqPosi(Appl_DrRestMode_CtrlModel_B.ResCallPosi_Back);
  Rte_SetVfb_DrResFrontReqPosi(Appl_DrRestMode_CtrlModel_B.ResCallPosi_Front);
  Rte_SetVfb_DrResHeightReqPosi(Appl_DrRestMode_CtrlModel_B.ResCallPosi_Height);
  Rte_SetVfb_DrResLengthReqPosi(Appl_DrRestMode_CtrlModel_B.ResCallPosi_Length);
  Rte_SetVfb_DrResBackReCallPosi(Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Back);
  Rte_SetVfb_DrResFrontReCallPosi
    (Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Front);
  Rte_SetVfb_DrResHeightReCallPosi
    (Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Height);
  Rte_SetVfb_DrResLengthReCallPosi
    (Appl_DrRestMode_CtrlModel_B.ResReCallPosi_Length);
  Rte_SetVfb_Debug_Res_State_ResDeal(Appl_DrRestMode_CtrlModel_B.State_ResDeal);
}

/* Model step function */
void Appl_DrRestMode_CtrlModel_step(void)
{
  Appl_DrRestMode_CtrlModel_UpDataInputInfo();
  Appl_DrRestMode_CtrlModel_LogicCtrl();
  Appl_DrRestMode_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_DrRestMode_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_DrRestMode_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_DrRestMode_CtrlModel_B), 0,
                sizeof(B_Appl_DrRestMode_CtrlModel_T));

  /* exported global signals */
  DrRes_CurrentMoveType = enSeatMotorRunType_EN_NULL;
  DrRes_BackAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrRes_FrontAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrRes_HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrRes_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrRes_PowerMode = enPowerModeSts_EN_OFF;
  DrRes_MassageMode_FB = enMassageMode_DSM_EN_M1;
  DrRes_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  DrRes_BackDefaultMotorSize = ((INT16U)0U);
  DrRes_BackDefaultStopPos = ((INT16U)0U);
  DrRes_BackHallPosi = ((INT16U)0U);
  DrRes_FrontDefaulMotorSize = ((INT16U)0U);
  DrRes_FrontDefaulStoptPos = ((INT16U)0U);
  DrRes_FrontHallPosi = ((INT16U)0U);
  DrRes_HeightDefaultMotorSize = ((INT16U)0U);
  DrRes_HeightDefaultStopPos = ((INT16U)0U);
  DrRes_HeightHallPosi = ((INT16U)0U);
  DrRes_LengthDefaultMotorSize = ((INT16U)0U);
  DrRes_LengthDefaultStopPos = ((INT16U)0U);
  DrRes_LengthHallPosi = ((INT16U)0U);
  DrResl_ReCallPosi_Back = ((INT16U)0U);
  DrResl_ReCallPosi_Front = ((INT16U)0U);
  DrResl_ReCallPosi_Height = ((INT16U)0U);
  DrResl_ReCallPosi_Length = ((INT16U)0U);
  DrRes_AdjustEnable = ((INT8U)0U);
  DrRes_AnyoneHallFaultSts = ((INT8U)0U);
  DrRes_AnyoneRelayFaultSts = ((INT8U)0U);
  DrRes_BackLockFault = ((INT8U)0U);
  DrRes_DescBackHallFault = ((INT8U)0U);
  DrRes_DescFrontHallFault = ((INT8U)0U);
  DrRes_DescHeightHallFault = ((INT8U)0U);
  DrRes_DescLengthHallFault = ((INT8U)0U);
  DrRes_EngineRunFlag = ((INT8U)0U);
  DrRes_FrontLockFault = ((INT8U)0U);
  DrRes_HeightLockFault = ((INT8U)0U);
  DrRes_IVI_NapMode_SwtichSet = ((INT8U)0U);
  DrRes_LengthLockFault = ((INT8U)0U);
  DrRes_SeatLearnResult = ((INT8U)0U);
  DrRes_SeatMassageCfg = ((INT8U)0U);
  DrRes_VehicleRunFlag = ((INT8U)0U);
  DrRes_VoltSatisfy = ((INT8U)0U);
  DrRes_WelcomeEnable = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_DrRestMode_CtrlModel_DW, 0,
                sizeof(DW_Appl_DrRestMode_CtrlModel_T));
  Appl_DrRestMode_CtrlModel_UpDataInputInfo_Init();
  Appl_DrRestMode_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
