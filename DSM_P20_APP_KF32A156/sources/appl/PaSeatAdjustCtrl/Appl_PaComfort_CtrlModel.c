/*
 * File: Appl_PaComfort_CtrlModel.c
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

#include "Appl_PaComfort_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_WelcomeDistance
#error The variable for the parameter "D_WelcomeDistance" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_CLOSE
#error The variable for the parameter "D_CLOSE" is not defined
#endif

#ifndef D_InitDelayTime
#error The variable for the parameter "D_InitDelayTime" is not defined
#endif

#ifndef D_OPEN
#error The variable for the parameter "D_OPEN" is not defined
#endif

#ifndef D_SoftDistancePaLegnth
#error The variable for the parameter "D_SoftDistancePaLegnth" is not defined
#endif

/* Named constants for Chart: '<S5>/WelcomeLogic' */
#define Appl_PaComfort_CtrlModel_IN_BackCheck ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_BackwardRunning ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_BackwardSuccess ((INT8U)3U)
#define Appl_PaComfort_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_PaComfort_CtrlModel_IN_WelcomeActive ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_WelcomeBackward ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_WelcomeDefault ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_WelcomeForward ((INT8U)3U)
#define Appl_PaComfort_CtrlModel_IN_WelcomeInactive ((INT8U)3U)

/* Named constants for Chart: '<S13>/Chart' */
#define Appl_PaComfort_CtrlModel_IN_Init_p ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_MoreThan ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g ((INT8U)0U)

/* Named constants for Chart: '<S14>/ComfortDeal' */
#define Appl_PaComfort_CtrlModel_IN_Configurable ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_Disable ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_Enable ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_Init_h ((INT8U)2U)

/* Named constants for Chart: '<S15>/Precondition' */
#define Appl_PaComfort_CtrlModel_IN_BWActive ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_BWInactive ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_CommonActive ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_CommonInactive ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_CommonInit ((INT8U)3U)
#define Appl_PaComfort_CtrlModel_IN_DoorInit ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_DoorSts1 ((INT8U)2U)
#define Appl_PaComfort_CtrlModel_IN_FWActive ((INT8U)1U)
#define Appl_PaComfort_CtrlModel_IN_FWInactive ((INT8U)2U)

/* Exported block signals */
enWelcomeSts MtrPAWel_WelcomeStatus;   /* '<S12>/MtrPAWel_WelcomeStatus'
                                        * ����ӭ��״̬��&#10;0x00: enNULL Ĭ�ϳ�ʼ��״̬&#10;0x01: enBackwardSts ����״̬&#10;0x02: enForwardSts ǰ��״̬
                                        */
enVehTypePrm MtrPAWel_VehiclePrm;      /* '<S12>/MtrPAWel_VehiclePrm'
                                        * ���ͣ�C62X��C52X��&#10; 0��P20����&#10; 1��BM400����
                                        */
enSeatMotorRunType MtrPAWel_CurrentMoveType;/* '<S12>/MtrPAWel_CurrentMoveType'
                                             * ���ݵ����ǰ�������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����
                                             */
enSeatAutoRunSts MtrPAWel_LengthAutoRunFlag;/* '<S12>/MtrPAWel_LengthAutoRunFlag'
                                             * ���������Զ����б�־λ
                                             */
enFinalPowerMode MtrPAWel_VoltMode;    /* '<S12>/MtrPAWel_VoltMode'
                                        * ������ѹģʽ&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
INT16U MtrPAWel_BackHallPosi;          /* '<S12>/MtrPAWel_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
INT16U MtrPAWel_BackMotorSize;         /* '<S12>/MtrPAWel_BackMotorSize'
                                        * ���ݿ������쳤��
                                        */
INT16U MtrPAWel_BackStopPosi;          /* '<S12>/MtrPAWel_BackStopPosi'
                                        * ���ݿ���ֹ��
                                        */
INT16U MtrPAWel_LengthBWTargetPosi;    /* '<S12>/MtrPAWel_LengthBWTargetPosi'
                                        * �����������Ŀ��λ��
                                        */
INT16U MtrPAWel_LengthFWTargetPosi;    /* '<S12>/MtrPAWel_LengthFWTargetPosi'
                                        * ��������ǰ��Ŀ��λ��
                                        */
INT16U MtrPAWel_LengthHallPosi;        /* '<S12>/MtrPAWel_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
INT16U MtrPAWel_LengthStopPosi;        /* '<S12>/MtrPAWel_LengthStopPosi'
                                        * ��������ֹ��
                                        */
INT8U MtrPAWel_0x28E_BDCLostFlag;      /* '<S12>/MtrPAWel_0x28E_BDCLostFlag'
                                        * 0x28E���ĵ��߱�־λ&#10;0x0:����&#10;0x1:����
                                        */
INT8U MtrPAWel_0x351_IVI_St_FRSeatmeet;/* '<S12>/MtrPAWel_0x351_IVI_St_FRSeatmeet'
                                        * ����ӭ��ʹ��&#10;0x0:Inactive��&#10;0x1:Open&#10;0x2:Close&#10;0x3:Reserved
                                        */
INT8U MtrPAWel_AdjustEnable;           /* '<S12>/MtrPAWel_AdjustEnable'
                                        * �������ε���:&#10;0x00:manual&#10;0x01:Four way motor
                                        */
INT8U MtrPAWel_BDC_FRDoorSts;          /* '<S12>/MtrPAWel_BDC_FRDoorSts'
                                        * ��ǰ��״̬&#10;0x0:Close&#10;0x1:Open
                                        */
INT8U MtrPAWel_BackHallFaultSts;       /* '<S12>/MtrPAWel_BackHallFaultSts'
                                        * ���ݿ�����������&#10;0���޹���&#10;1���й���
                                        */
INT8U MtrPAWel_BackLockSts;            /* '<S12>/MtrPAWel_BackLockSts'
                                        * ���ݿ�����ת״̬&#10;0����&#10;1����
                                        */
INT8U MtrPAWel_BackRelayFaultSts;      /* '<S12>/MtrPAWel_BackRelayFaultSts'
                                        * ���ݿ����̵���ճ��&#10;0���޹��ϣ�&#10;1��D_Relay_UpFrontFault��ǰճ�����ϣ�&#10;2��D_Relay_DownBackFault�º�ճ�����ϣ�
                                        */
INT8U MtrPAWel_BusoffFlag;             /* '<S12>/MtrPAWel_BusoffFlag'
                                        * ����busoff��־λ&#10;0��������&#10;1��busoff����
                                        */
INT8U MtrPAWel_GearPNFlag;             /* '<S12>/MtrPAWel_GearPNFlag'
                                        * �Ƿ���P/N����&#10;0��No&#10;1��Yes
                                        */
INT8U MtrPAWel_GetRecoverDefaultFlag;  /* '<S12>/MtrPAWel_GetRecoverDefaultFlag'
                                        * �ָ���������&#10;0���ǻָ�������&#10;1���ָ��������ã�
                                        */
INT8U MtrPAWel_LengthCmd;              /* '<S12>/MtrPAWel_LengthCmd'
                                        * ��������������:&#10;0:��&#10;1����ǰ&#10;2�����
                                        */
INT8U MtrPAWel_LengthHallFaultSts;     /* '<S12>/MtrPAWel_LengthHallFaultSts'
                                        * ������������������&#10;0����&#10;1����
                                        */
INT8U MtrPAWel_LengthLockSts;          /* '<S12>/MtrPAWel_LengthLockSts'
                                        * ���������ת״̬&#10;0����&#10;1����
                                        */
INT8U MtrPAWel_LengthRelayFaultSts;    /* '<S12>/MtrPAWel_LengthRelayFaultSts'
                                        * ��������̵���ճ�����ϱ�־&#10;0���޹���&#10;1���й���
                                        */
INT8U MtrPAWel_UpdatePosiFlag;         /* '<S12>/MtrPAWel_UpdatePosiFlag'
                                        * ����ӭ��λ�ø��±�־:&#10; 0��������&#10; 1������
                                        */
INT8U MtrPAWel_VoltSatisfy;            /* '<S12>/MtrPAWel_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ����㣺&#10;0��������&#10;1������
                                        */
INT8U MtrPAWel_WelcomeEnable;          /* '<S12>/MtrPAWel_WelcomeEnable'
                                        * ����ӭ��ʹ��״̬:&#10;0������&#10;1��ʹ��
                                        */
INT8U MtrPAWel_WelcomeSwitch;          /* '<S12>/MtrPAWel_WelcomeSwitch'
                                        * ����ӭ������״̬:&#10;0���ر�&#10;1������
                                        */

/* Block signals (default storage) */
B_Appl_PaComfort_CtrlModel_T Appl_PaComfort_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_PaComfort_CtrlModel_T Appl_PaComfort_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_PaComfort_CtrlModel_T Appl_PaComfort_CtrlModel_M_;
RT_MODEL_Appl_PaComfort_CtrlModel_T *const Appl_PaComfort_CtrlModel_M =
  &Appl_PaComfort_CtrlModel_M_;
static void Appl_PaComfort_CtrlModel_Set_WelcomeUpdatePosiFlag(void);
static void Appl_PaComfort_CtrlModel_Set_WelcomeStatus(void);
static void Appl_PaComfort_CtrlModel_LogicCtrl_Init(void);
static void Appl_PaComfort_CtrlModel_LogicCtrl(void);
static void Appl_PaComfort_CtrlModel_SetComfortPrm(void);
static void Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d(void);
static void Appl_PaComfort_CtrlModel_Get_DoorSts(void);
static void Appl_PaComfort_CtrlModel_RTE(void);
static void Appl_PaComfort_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_PaComfort_CtrlModel_UpDataInputInfo(void);
static void Appl_PaComfort_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_PaComfort_CtrlModel_WelcomeActive(const INT8U
  *BackwardTriggerCondition_prev, const INT8U *ForwardTriggerCondition_prev);

/* Output and update for function-call system: '<S6>/Set_WelcomeUpdatePosiFlag' */
static void Appl_PaComfort_CtrlModel_Set_WelcomeUpdatePosiFlag(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomePaUpdate
    ,Appl_PaComfort_CtrlModel_B.In1_d);
}

/* Output and update for function-call system: '<S6>/Set_WelcomeStatus' */
static void Appl_PaComfort_CtrlModel_Set_WelcomeStatus(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_PaWelcomeStatus,
    Appl_PaComfort_CtrlModel_B.In1_h);
}

/* Function for Chart: '<S5>/WelcomeLogic' */
static void Appl_PaComfort_CtrlModel_WelcomeActive(const INT8U
  *BackwardTriggerCondition_prev, const INT8U *ForwardTriggerCondition_prev)
{
  INT16U LocalLengthReqPosi;
  INT32S tmp;
  INT32S tmp_0;

  /* ǰ�ƹ�����||���ƹ�����ǰ�����������㣬�´���Ҫ����Ŀ������ */
  if (((Appl_PaComfort_CtrlModel_DW.WelcomeStatus ==
        enWelcomeSts_EN_Wel_FWOngoing) ||
       (Appl_PaComfort_CtrlModel_DW.WelcomeStatus ==
        enWelcomeSts_EN_Wel_BWOngoing)) && (enWelStopCause_EN_WelStop_NULL !=
       Appl_PaComfort_CtrlModel_B.WelcomeStopReason))
  {
    Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
      Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
      Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
      Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
      Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
    Appl_PaComfort_CtrlModel_B.In1_d = ((BOOL)TRUE);
    Appl_PaComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
    Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
      Appl_PaComfort_CtrlModel_IN_WelcomeInactive;

    /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
       ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
    Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
    Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
    Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
    Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
    Appl_PaComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
    Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
      Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
    Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
    Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 10U;

    /* ����������ԭ��ǿգ���������ֹͣԭ�� */
    if (enWelStopCause_EN_WelStop_NULL !=
        Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
    {
      Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
        Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
      Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 12U;

      /* mantis��7341����EEPORM�洢ʧ�� */
      Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
        Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
      Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
    }
  }
  else
  {
    /* ��������������� */
    if (((BOOL)TRUE) == MtrPAWel_LengthHallFaultSts)
    {
      Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
        Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
        Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
        Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
        enWelStopCause_EN_WelStop_HallFault;
      Appl_PaComfort_CtrlModel_B.In1_d = ((BOOL)TRUE);
      Appl_PaComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
      Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
        Appl_PaComfort_CtrlModel_IN_WelcomeInactive;

      /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
         ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
      Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
      Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
      Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
      Appl_PaComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
      Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
        Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
      Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
      Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 10U;

      /* ����������ԭ��ǿգ���������ֹͣԭ�� */
      if (enWelStopCause_EN_WelStop_NULL !=
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
      {
        Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
        Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 12U;

        /* mantis��7341����EEPORM�洢ʧ�� */
        Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
          Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
        Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
      }
    }
    else
    {
      /* ǰ�����������㣬�Ҳ���Ҫ����Ŀ������ */
      if (enWelStopCause_EN_WelStop_NULL !=
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
      {
        Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
          Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
        Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
          Appl_PaComfort_CtrlModel_IN_WelcomeInactive;

        /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
           ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
        Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
        Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
          Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
        Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
        Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 10U;

        /* ����������ԭ��ǿգ���������ֹͣԭ�� */
        if (enWelStopCause_EN_WelStop_NULL !=
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
        {
          Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
          Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 12U;

          /* mantis��7341����EEPORM�洢ʧ�� */
          Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
            Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
          Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
        }
      }
      else
      {
        /*  ������������ */
        if (((BOOL)TRUE) == MtrPAWel_BackHallFaultSts)
        {
          Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
            Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
            Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            enWelStopCause_EN_WelStop_HallFault;
          Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
            Appl_PaComfort_CtrlModel_IN_WelcomeInactive;

          /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
             ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
          Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
          Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
          Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
          Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
          Appl_PaComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
          Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
            Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
          Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
          Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 10U;

          /* ����������ԭ��ǿգ���������ֹͣԭ�� */
          if (enWelStopCause_EN_WelStop_NULL !=
              Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
          {
            Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
              Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
            Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 12U;

            /* mantis��7341����EEPORM�洢ʧ�� */
            Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
          }
        }
        else
        {
          switch (Appl_PaComfort_CtrlModel_DW.is_WelcomeActive)
          {
           case Appl_PaComfort_CtrlModel_IN_WelcomeBackward:
            /* ����ǰ������ */
            if ((*ForwardTriggerCondition_prev !=
                 Appl_PaComfort_CtrlModel_DW.ForwardTriggerCondition_start) &&
                (Appl_PaComfort_CtrlModel_DW.ForwardTriggerCondition_start ==
                 ((BOOL)TRUE)))
            {
              /* WelcomeStatus = enWelcomeSts.EN_BackMovingExForWard */
              Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_PaComfort_CtrlModel_IN_WelcomeForward;

              /* ӭ��״̬ = ǰ��
                 ��ֹͻȻ������´β�����ִ�к��� */
              Appl_PaComfort_CtrlModel_DW.WelcomeStatus =
                enWelcomeSts_EN_Wel_FWOngoing;
              Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
                Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
              Appl_PaComfort_CtrlModel_Set_WelcomeStatus();

              /* ӭ��ǰ�ƣ�
                 1.����״̬ = ǰ�������У�
                 2.�������� = ǰ�ƣ�
                 3.ӭ������ = ǰ��Ŀ�����ꣻ */
              Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                enWelcomeRunSts_EN_Wel_FWOngoing;
              Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              Appl_PaComfort_CtrlModel_B.WelcomeReqPosi =
                MtrPAWel_LengthFWTargetPosi;
              Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
            }
            else
            {
              /* ��Ĭ��״̬����&& (EEPROMҪ�����ӭ������ || ���������쳣)  */
              if ((((BOOL)TRUE) ==
                   Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag) && ((((BOOL)
                     TRUE) == MtrPAWel_UpdatePosiFlag) ||
                   (MtrPAWel_LengthBWTargetPosi == 0) ||
                   (MtrPAWel_LengthBWTargetPosi == 0xFFFF) ||
                   (MtrPAWel_LengthFWTargetPosi == 0) ||
                   (MtrPAWel_LengthFWTargetPosi == 0xFFFF) ||
                   (MtrPAWel_LengthFWTargetPosi < MtrPAWel_LengthBWTargetPosi)))
              {
                /* ���ʼ����ת��־λ�������ӭ�������־λ������ǰ������ */
                Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
                tmp = MtrPAWel_LengthHallPosi - ((INT16U)D_WelcomeDistance);
                if (tmp < 0)
                {
                  tmp = 0;
                }

                Appl_PaComfort_CtrlModel_B.In1_d = ((BOOL)FALSE);
                Appl_PaComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
                Appl_PaComfort_CtrlModel_B.In1_e = MtrPAWel_LengthHallPosi;
                Srvl_SetMemIndexDataU16(EN_MemIndex_PaWelcome_LenTar_ForWard
                  ,Appl_PaComfort_CtrlModel_B.In1_e);

                /* ����Ŀ��λ���Ƿ񳬹���ֹ�� */
                tmp_0 = MtrPAWel_LengthStopPosi + ((INT8U)D_SoftDistancePaLegnth);
                if ((INT16U)tmp > tmp_0)
                {
                  LocalLengthReqPosi = (INT16U)tmp;
                }
                else
                {
                  if (tmp_0 > 65535)
                  {
                    tmp_0 = 65535;
                  }

                  LocalLengthReqPosi = (INT16U)tmp_0;
                }

                /* �洢����Ŀ������ */
                Appl_PaComfort_CtrlModel_B.In1_p = LocalLengthReqPosi;
                Srvl_SetMemIndexDataU16(EN_MemIndex_PaWelcome_LenTar_BackWard
                  ,Appl_PaComfort_CtrlModel_B.In1_p);
              }
              else
              {
                LocalLengthReqPosi = MtrPAWel_LengthBWTargetPosi;
              }

              switch (Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward)
              {
               case Appl_PaComfort_CtrlModel_IN_BackCheck:
                /*  ��������Ƕ�����  */
                if (Appl_PaComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)TRUE))
                {
                  Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_PaComfort_CtrlModel_IN_BackwardRunning;
                  Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                  Appl_PaComfort_CtrlModel_DW.WelcomeStatus =
                    enWelcomeSts_EN_Wel_BWOngoing;
                  Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                    enWelcomeRunSts_EN_Wel_BWOngoing;
                  Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
                  Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = LocalLengthReqPosi;
                }
                else
                {
                  /*  ����������Ƕ�����  */
                  if (Appl_PaComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
                  {
                    Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi =
                      Appl_PaComfort_CtrlModel_B.BackMoreThanHall;
                    Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
                  }

                  Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 14U;
                }
                break;

               case Appl_PaComfort_CtrlModel_IN_BackwardRunning:
                /* ���е�����Ŀ��λ�� */
                if (enSeatAutoRunSts_EN_SEAT_SUCCESS ==
                    MtrPAWel_LengthAutoRunFlag)
                {
                  Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
                  Appl_PaComfort_CtrlModel_DW.WelcomeStatus =
                    enWelcomeSts_EN_BackwardStsSuccess;
                  Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                    enWelcomeRunSts_EN_Wel_BWMoveSuccess;
                  Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
                    Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
                  Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
                  Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_PaComfort_CtrlModel_IN_BackwardSuccess;

                  /* ӭ��Ĭ��״̬��1.�������� = �ޣ�
                     2.ӭ������ = 0�� */
                  Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                  Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                  Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                }
                else
                {
                  Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = LocalLengthReqPosi;
                }
                break;
              }
            }
            break;

           case Appl_PaComfort_CtrlModel_IN_WelcomeDefault:
            /* �����������&&��һ��δ�ɹ�ִ�к��� */
            if ((*BackwardTriggerCondition_prev !=
                 Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start) &&
                (Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start ==
                 ((BOOL)TRUE)) && (enWelcomeSts_EN_BackwardStsSuccess !=
                                   Appl_PaComfort_CtrlModel_DW.WelcomeStatus))
            {
              Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)TRUE);
              Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_PaComfort_CtrlModel_IN_WelcomeBackward;
              Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_PaComfort_CtrlModel_IN_BackCheck;

              /*  ����������Ƕ�����  */
              if (Appl_PaComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
              {
                Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi =
                  Appl_PaComfort_CtrlModel_B.BackMoreThanHall;
                Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              }

              Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 14U;
            }
            else
            {
              /* ���Ƴɹ�&&û�д�Ϲ�������ԭ��mantis��7341�� */
              if ((enWelcomeSts_EN_BackwardStsSuccess ==
                   Appl_PaComfort_CtrlModel_DW.WelcomeStatus) &&
                  (MtrPAWel_UpdatePosiFlag == ((BOOL)FALSE)))
              {
                Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_PaComfort_CtrlModel_IN_WelcomeBackward;
                Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                  Appl_PaComfort_CtrlModel_IN_BackwardSuccess;

                /* ӭ��Ĭ��״̬��1.�������� = �ޣ�
                   2.ӭ������ = 0�� */
                Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                  enWelcomeRunSts_EN_Wel_BWMoveSuccess;
              }
            }
            break;

           default:
            /* ����������� */
            if ((*BackwardTriggerCondition_prev !=
                 Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start) &&
                (Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start ==
                 ((BOOL)TRUE)))
            {
              /* WelcomeStatus = enWelcomeSts.EN_ForWardMovingExBack */
              Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_PaComfort_CtrlModel_IN_WelcomeBackward;
              Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_PaComfort_CtrlModel_IN_BackCheck;

              /*  ����������Ƕ�����  */
              if (Appl_PaComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
              {
                Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi =
                  Appl_PaComfort_CtrlModel_B.BackMoreThanHall;
                Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              }

              Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 14U;
            }
            else
            {
              /* �˶���Ŀ������ */
              if (enSeatAutoRunSts_EN_SEAT_SUCCESS == MtrPAWel_LengthAutoRunFlag)
              {
                Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
                Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                  enWelcomeRunSts_EN_Wel_FWMoveSuccess;
                Appl_PaComfort_CtrlModel_DW.WelcomeStatus =
                  enWelcomeSts_EN_ForwardStsSuccess;
                Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
                  Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
                Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
                Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_PaComfort_CtrlModel_IN_WelcomeDefault;

                /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
                Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
              }
            }
            break;
          }
        }
      }
    }
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaComfort_CtrlModel_LogicCtrl_Init(void)
{
  Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaComfort_CtrlModel_DW.is_WelcomeBackward =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaComfort_CtrlModel_DW.is_active_c3_Appl_PaComfort_CtrlModel = 0U;
  Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaComfort_CtrlModel_DW.WelcomeFromeInitFlag = 0U;
  Appl_PaComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
  Appl_PaComfort_CtrlModel_DW.InitTimer_n = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaComfort_CtrlModel_LogicCtrl(void)
{
  INT8U BackwardTriggerCondition_prev;
  INT8U ForwardTriggerCondition_prev;
  INT32S tmp;
  Appl_PaComfort_CtrlModel_B.DataTypeConversion = (INT8U)
    (Appl_PaComfort_CtrlModel_B.ComfortOpenMsg == 0);
  BackwardTriggerCondition_prev =
    Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start;
  Appl_PaComfort_CtrlModel_DW.BackwardTriggerCondition_start =
    Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition;
  ForwardTriggerCondition_prev =
    Appl_PaComfort_CtrlModel_DW.ForwardTriggerCondition_start;
  Appl_PaComfort_CtrlModel_DW.ForwardTriggerCondition_start =
    Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition;
  if (Appl_PaComfort_CtrlModel_DW.is_active_c3_Appl_PaComfort_CtrlModel == 0U)
  {
    Appl_PaComfort_CtrlModel_DW.is_active_c3_Appl_PaComfort_CtrlModel = 1U;
    Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
      Appl_PaComfort_CtrlModel_IN_Init;
    Appl_PaComfort_CtrlModel_DW.InitTimer_n = 0U;
  }
  else
  {
    switch (Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel)
    {
     case Appl_PaComfort_CtrlModel_IN_Init:
      /* ��ʼ����ɣ���ȡӭ��״̬ */
      if (Appl_PaComfort_CtrlModel_DW.InitTimer_n > ((INT8U)D_InitDelayTime))
      {
        Appl_PaComfort_CtrlModel_DW.InitTimer_n = 0U;
        Appl_PaComfort_CtrlModel_DW.WelcomeStatus = MtrPAWel_WelcomeStatus;
        Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 13U;
        Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
          Appl_PaComfort_CtrlModel_IN_WelcomeActive;
        Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_PaComfort_CtrlModel_IN_WelcomeDefault;

        /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      }
      else
      {
        tmp = Appl_PaComfort_CtrlModel_DW.InitTimer_n + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_PaComfort_CtrlModel_DW.InitTimer_n = (INT8U)tmp;
      }
      break;

     case Appl_PaComfort_CtrlModel_IN_WelcomeActive:
      Appl_PaComfort_CtrlModel_WelcomeActive(&BackwardTriggerCondition_prev,
        &ForwardTriggerCondition_prev);
      break;

     default:
      /* ӭ��ǰ���������� */
      if (enWelStopCause_EN_WelStop_NULL ==
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
      {
        Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 11U;
        Appl_PaComfort_CtrlModel_DW.is_c3_Appl_PaComfort_CtrlModel =
          Appl_PaComfort_CtrlModel_IN_WelcomeActive;
        Appl_PaComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_PaComfort_CtrlModel_IN_WelcomeDefault;

        /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_PaComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      }
      else
      {
        /* ����������ԭ��ǿգ���������ֹͣԭ�� */
        if (enWelStopCause_EN_WelStop_NULL !=
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason)
        {
          Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason;
          Appl_PaComfort_CtrlModel_B.WelcomeRunStatus = 12U;

          /* mantis��7341����EEPORM�洢ʧ�� */
          Appl_PaComfort_CtrlModel_B.In1_h = (INT8U)
            Appl_PaComfort_CtrlModel_DW.WelcomeStatus;
          Appl_PaComfort_CtrlModel_Set_WelcomeStatus();
        }
      }
      break;
    }
  }
}

/* Output and update for function-call system: '<S17>/SetComfortPrm' */
static void Appl_PaComfort_CtrlModel_SetComfortPrm(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_PaWelcomeSwitch,
    Appl_PaComfort_CtrlModel_B.in);
}

/* Output and update for function-call system: '<S19>/Set_WelcomeUpdatePosiFlag' */
static void Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomePaUpdate,
    Appl_PaComfort_CtrlModel_B.In1);
}

/* Output and update for function-call system: '<S19>/Get_DoorSts' */
static void Appl_PaComfort_CtrlModel_Get_DoorSts(void)
{
  Appl_PaComfort_CtrlModel_B.MtrWel_WelcomeSwitch = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaDoorSts);
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_PaComfort_CtrlModel_RTE(void)
{
  MtrPAWel_0x28E_BDCLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x28E);
  MtrPAWel_0x351_IVI_St_FRSeatmeet = CanRx_0x351_IVI_St_FRSeatmeet( );
  MtrPAWel_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
  MtrPAWel_BDC_FRDoorSts = CanRx_0x28E_BDC_FRDoorSts( );
  MtrPAWel_BackHallFaultSts = Rte_GetVfb_PaBackHallErr( );
  MtrPAWel_BackHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerBack);
  MtrPAWel_BackLockSts = Rte_GetVfb_PaBackStallErr( );
  MtrPAWel_BackMotorSize = Cdd_GetMotorSize(EN_PassengerBack);
  MtrPAWel_BackRelayFaultSts = Rte_GetVfb_PaBackRelayAdheErr( );
  MtrPAWel_BackStopPosi = Cdd_GetMotorHardStop(EN_PassengerBack);
  MtrPAWel_BusoffFlag = Nm_IsBusOff( );
  MtrPAWel_CurrentMoveType = Rte_GetVfb_PaMoveType( );
  MtrPAWel_GearPNFlag = Rte_GetCAN_Gear_PN_Flag( );
  MtrPAWel_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  MtrPAWel_LengthAutoRunFlag = Rte_GetVfb_PaLengthAutoRunFlag( );
  MtrPAWel_LengthBWTargetPosi = Srvl_GetMemIndexDataU16
    (EN_MemIndex_PaWelcome_LenTar_BackWard);
  MtrPAWel_LengthCmd = Rte_GetVfb_PaLengthMotorCmd( );
  MtrPAWel_LengthFWTargetPosi = Srvl_GetMemIndexDataU16
    (EN_MemIndex_PaWelcome_LenTar_ForWard);
  MtrPAWel_LengthHallFaultSts = Rte_GetVfb_PaLengthHallErr( );
  MtrPAWel_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerLength);
  MtrPAWel_LengthLockSts = Rte_GetVfb_PaLengthStallErr( );
  MtrPAWel_LengthRelayFaultSts = Rte_GetVfb_PaLengthRelayAdheErr( );
  MtrPAWel_LengthStopPosi = Cdd_GetMotorHardStop(EN_PassengerLength);
  MtrPAWel_UpdatePosiFlag = Srvl_GetMemIndexDataU8(EN_MemIndex_WelcomePaUpdate);
  MtrPAWel_VehiclePrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  MtrPAWel_VoltMode = Rte_GetVfb_VoltMode( );
  MtrPAWel_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  MtrPAWel_WelcomeEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
  MtrPAWel_WelcomeStatus = Srvl_GetMemIndexDataU8(EN_MemIndex_PaWelcomeStatus);
  MtrPAWel_WelcomeSwitch = Srvl_GetMemIndexDataU8(EN_MemIndex_PaWelcomeSwitch);
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaComfort_CtrlModel_UpDataInputInfo_Init(void)
{
  Appl_PaComfort_CtrlModel_DW.is_More =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.is_active_c2_Appl_PaComfort_CtrlModel = 0U;
  Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = 0U;
  Appl_PaComfort_CtrlModel_DW.is_Configurable =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.is_active_c11_Appl_PaComfort_CtrlModel = 0U;
  Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.InitTimer = 0U;
  Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = 0U;
  Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.is_DoorSts =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.is_BackwardTriggerCondition =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.temporalCounter_i1 = 0U;
  Appl_PaComfort_CtrlModel_DW.is_ForwardTriggercondition =
    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
  Appl_PaComfort_CtrlModel_DW.temporalCounter_i2 = 0U;
  Appl_PaComfort_CtrlModel_DW.is_active_c7_Appl_PaComfort_CtrlModel = 0U;
  Appl_PaComfort_CtrlModel_DW.LocalDoorSts = 0U;
  Appl_PaComfort_CtrlModel_DW.WaitTimeCnt = 0U;
  Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = 0U;
  Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = 0U;
  Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
    enWelStopCause_EN_WelStop_VoltageError;
  Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start =
    Appl_PaComfort_CtrlModel_DW.LocalDoorSts;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaComfort_CtrlModel_UpDataInputInfo(void)
{
  INT16U rtb_BackMoreThanHall;
  BOOL rtb_SeatLearnResult_p;
  INT8U rtb_ComfortOpenFlag;
  INT8U LocalDoorSts_prev;
  INT8U MtrPAWel_LengthCmd_prev;
  INT32S tmp;
  Appl_PaComfort_CtrlModel_RTE();
  if (Appl_PaComfort_CtrlModel_DW.is_active_c2_Appl_PaComfort_CtrlModel == 0U)
  {
    Appl_PaComfort_CtrlModel_DW.is_active_c2_Appl_PaComfort_CtrlModel = 1U;
    tmp = (INT32S)((INT32U)MtrPAWel_BackMotorSize >> 2) + MtrPAWel_BackStopPosi;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    rtb_BackMoreThanHall = (INT16U)tmp;
    Appl_PaComfort_CtrlModel_DW.is_More = Appl_PaComfort_CtrlModel_IN_Init_p;
    Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);
  }
  else
  {
    tmp = (INT32S)((INT32U)MtrPAWel_BackMotorSize >> 2) + MtrPAWel_BackStopPosi;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    rtb_BackMoreThanHall = (INT16U)tmp;
    if (Appl_PaComfort_CtrlModel_DW.is_More ==
        Appl_PaComfort_CtrlModel_IN_Init_p)
    {
      Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);

      /*  ���ھ�ǰֹ��60��λ��  */
      if (MtrPAWel_BackHallPosi > (INT16U)tmp)
      {
        Appl_PaComfort_CtrlModel_DW.is_More =
          Appl_PaComfort_CtrlModel_IN_MoreThan;
        Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)TRUE);

      /*  С�ڵ��ھ�ǰֹ��60��λ��  */
      if (MtrPAWel_BackHallPosi <= (INT16U)tmp)
      {
        Appl_PaComfort_CtrlModel_DW.is_More = Appl_PaComfort_CtrlModel_IN_Init_p;
        Appl_PaComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);
      }
    }
  }

  Appl_PaComfort_CtrlModel_B.BackMoreThanHall = (INT16U)(rtb_BackMoreThanHall +
    40U);
  if (Appl_PaComfort_CtrlModel_DW.is_active_c11_Appl_PaComfort_CtrlModel == 0U)
  {
    Appl_PaComfort_CtrlModel_DW.is_active_c11_Appl_PaComfort_CtrlModel = 1U;
    Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
      Appl_PaComfort_CtrlModel_IN_Init_h;
    Appl_PaComfort_CtrlModel_DW.InitTimer = 1U;
    rtb_ComfortOpenFlag = ((BOOL)FALSE);
    Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
  }
  else if (Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel ==
           Appl_PaComfort_CtrlModel_IN_Configurable)
  {
    /* �ָ��������� */
    if (((BOOL)TRUE) == MtrPAWel_GetRecoverDefaultFlag)
    {
      Appl_PaComfort_CtrlModel_DW.is_Configurable =
        Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
      Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
        Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
      Appl_PaComfort_CtrlModel_B.in = ((BOOL)TRUE);
      Appl_PaComfort_CtrlModel_SetComfortPrm();
      Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
        Appl_PaComfort_CtrlModel_IN_Init_h;
      Appl_PaComfort_CtrlModel_DW.InitTimer = 1U;
      rtb_ComfortOpenFlag = ((BOOL)FALSE);
      Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
    }
    else
    {
      /* ((ӭ������ || ����Ϊ�ֶ����� || ��ѹ������ģʽ)&&P20����)
         || ��P20���� */
      if ((enVehTypePrm_enP20 != MtrPAWel_VehiclePrm) || ((((BOOL)TRUE) !=
            MtrPAWel_WelcomeEnable) || ((INT32S)enDrAdjustEnable_EN_DrManual ==
            MtrPAWel_AdjustEnable) || (enFinalPowerMode_EN_NORMAL_VOLT !=
            MtrPAWel_VoltMode)))
      {
        Appl_PaComfort_CtrlModel_DW.is_Configurable =
          Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
        Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
          Appl_PaComfort_CtrlModel_IN_Init_h;
        Appl_PaComfort_CtrlModel_DW.InitTimer = 1U;
        rtb_ComfortOpenFlag = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
      }
      else if (Appl_PaComfort_CtrlModel_DW.is_Configurable ==
               Appl_PaComfort_CtrlModel_IN_Disable)
      {
        rtb_ComfortOpenFlag = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);

        /* ��IVI_St_FLSeatmeet=0x1:Openʱ�����ε������ʽ���ʹ�� */
        if (1 == MtrPAWel_0x351_IVI_St_FRSeatmeet)
        {
          Appl_PaComfort_CtrlModel_DW.is_Configurable =
            Appl_PaComfort_CtrlModel_IN_Enable;
          rtb_ComfortOpenFlag = ((BOOL)TRUE);

          /* *ComfortOpenMsg ���ķ��ͱ���****************ComfortOpenFlagӭ�������Ƿ���������PC1ӭ�����ܴ��ڿ���״̬ */
          Appl_PaComfort_CtrlModel_B.in = ((BOOL)TRUE);
          Appl_PaComfort_CtrlModel_SetComfortPrm();
          Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
        }
      }
      else
      {
        rtb_ComfortOpenFlag = ((BOOL)TRUE);
        Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);

        /* ��IVI_St_FLSeatmeet=0x2:Closeʱ�����ε������ʽ������ */
        if (2 == MtrPAWel_0x351_IVI_St_FRSeatmeet)
        {
          Appl_PaComfort_CtrlModel_DW.is_Configurable =
            Appl_PaComfort_CtrlModel_IN_Disable;
          rtb_ComfortOpenFlag = ((BOOL)FALSE);
          Appl_PaComfort_CtrlModel_B.in = ((BOOL)FALSE);
          Appl_PaComfort_CtrlModel_SetComfortPrm();
          Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);
        }
      }
    }
  }
  else
  {
    rtb_ComfortOpenFlag = ((BOOL)FALSE);
    Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);

    /* EEPROMӭ��Ϊʹ��&&���ε綯����&&P20����&&��ʼ�����&&������ѹ */
    if ((((BOOL)TRUE) == MtrPAWel_WelcomeEnable) && (((INT32S)
          enDrAdjustEnable_EN_DrSixWayMotor == MtrPAWel_AdjustEnable) ||
         ((INT32S)enDrAdjustEnable_EN_DrTwelveWayMotor == MtrPAWel_AdjustEnable))
        && (enVehTypePrm_enP20 == MtrPAWel_VehiclePrm) &&
        (Appl_PaComfort_CtrlModel_DW.InitTimer > ((INT8U)D_InitDelayTime)) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == MtrPAWel_VoltMode))
    {
      Appl_PaComfort_CtrlModel_DW.InitTimer = 0U;
      Appl_PaComfort_CtrlModel_DW.is_c11_Appl_PaComfort_CtrlModel =
        Appl_PaComfort_CtrlModel_IN_Configurable;
      if (MtrPAWel_WelcomeSwitch == 1)
      {
        Appl_PaComfort_CtrlModel_DW.is_Configurable =
          Appl_PaComfort_CtrlModel_IN_Enable;
        rtb_ComfortOpenFlag = ((BOOL)TRUE);

        /* *ComfortOpenMsg ���ķ��ͱ���****************ComfortOpenFlagӭ�������Ƿ���������PC1ӭ�����ܴ��ڿ���״̬ */
        Appl_PaComfort_CtrlModel_B.in = ((BOOL)TRUE);
        Appl_PaComfort_CtrlModel_SetComfortPrm();
        Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
      }
      else
      {
        Appl_PaComfort_CtrlModel_DW.is_Configurable =
          Appl_PaComfort_CtrlModel_IN_Disable;
        rtb_ComfortOpenFlag = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_B.in = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_SetComfortPrm();
        Appl_PaComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);
      }
    }
    else
    {
      tmp = Appl_PaComfort_CtrlModel_DW.InitTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_PaComfort_CtrlModel_DW.InitTimer = (INT8U)tmp;
    }
  }

  rtb_SeatLearnResult_p = ((MtrPAWel_LengthStopPosi != 0) &&
    (MtrPAWel_LengthStopPosi != 65535) && ((MtrPAWel_BackStopPosi != 0) &&
    (MtrPAWel_BackStopPosi != 65535)));
  if (Appl_PaComfort_CtrlModel_DW.temporalCounter_i1 < 3U)
  {
    Appl_PaComfort_CtrlModel_DW.temporalCounter_i1++;
  }

  if (Appl_PaComfort_CtrlModel_DW.temporalCounter_i2 < 3U)
  {
    Appl_PaComfort_CtrlModel_DW.temporalCounter_i2++;
  }

  LocalDoorSts_prev = Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start;
  Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start =
    Appl_PaComfort_CtrlModel_DW.LocalDoorSts;
  MtrPAWel_LengthCmd_prev = Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start;
  Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start = MtrPAWel_LengthCmd;
  if (Appl_PaComfort_CtrlModel_DW.is_active_c7_Appl_PaComfort_CtrlModel == 0U)
  {
    Appl_PaComfort_CtrlModel_DW.is_active_c7_Appl_PaComfort_CtrlModel = 1U;
    Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
      Appl_PaComfort_CtrlModel_IN_CommonInit;
    Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
      enWelStopCause_EN_WelStop_VoltageError;
    Appl_PaComfort_CtrlModel_DW.is_DoorSts =
      Appl_PaComfort_CtrlModel_IN_DoorInit;
    Appl_PaComfort_CtrlModel_DW.WaitTimeCnt = 0U;
    Appl_PaComfort_CtrlModel_DW.LocalDoorSts = (INT8U)0xFF;

    /*  ��������仯 �ҷ����ʹ��ܵ��� ��Ҫ��������λ��  */
    if ((enSeatMotorRunType_EN_ComfortEnable != MtrPAWel_CurrentMoveType) &&
        (enSeatMotorRunType_EN_NULL != MtrPAWel_CurrentMoveType) &&
        (((MtrPAWel_LengthCmd !=
           Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start) &&
          (Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start == 1)) ||
         ((MtrPAWel_LengthCmd !=
           Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start) &&
          (Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start == 2))))
    {
      Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
      Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
    }
  }
  else
  {
    switch (Appl_PaComfort_CtrlModel_DW.is_CommonCondition)
    {
     case Appl_PaComfort_CtrlModel_IN_CommonActive:
      /* ӭ������ */
      if (((BOOL)TRUE) != rtb_ComfortOpenFlag)
      {
        Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
          Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
        Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
          enWelStopCause_EN_WelStop_PRM;
        Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
        Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
        Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
          Appl_PaComfort_CtrlModel_IN_CommonInactive;
      }
      else
      {
        /* ������򿿱���ת���� */
        if ((((BOOL)FALSE) != MtrPAWel_LengthLockSts) || (((BOOL)FALSE) !=
             MtrPAWel_BackLockSts))
        {
          Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
            Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
            enWelStopCause_EN_WelStop_LockFault;
          Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
          Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
          Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
            Appl_PaComfort_CtrlModel_IN_CommonInactive;
        }
        else
        {
          /* ��������򿿱��̵������� */
          if ((((BOOL)FALSE) != MtrPAWel_LengthRelayFaultSts) || (((BOOL)FALSE)
               != MtrPAWel_BackRelayFaultSts))
          {
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
              enWelStopCause_EN_WelStop_RelayFault;
            Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
              Appl_PaComfort_CtrlModel_IN_CommonInactive;
          }
          else
          {
            /* ��busoff���� */
            if (((BOOL)FALSE) != MtrPAWel_BusoffFlag)
            {
              Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                enWelStopCause_EN_WelStop_Busoff;
              Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                Appl_PaComfort_CtrlModel_IN_CommonInactive;
            }
            else
            {
              /* ���򡢿���δѧϰ */
              if (((BOOL)TRUE) != rtb_SeatLearnResult_p)
              {
                Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
                Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                  enWelStopCause_EN_WelStop_enNotLearn;
                Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
                Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
                Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_PaComfort_CtrlModel_IN_CommonInactive;
              }
              else
              {
                /* �и�����ӭ���˶������� */
                if (enSeatMotorRunType_EN_ComfortEnable <
                    MtrPAWel_CurrentMoveType)
                {
                  Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_PaComfort_CtrlModel_IN_NO_ACTIVE_CHILD_g;
                  Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                    enWelStopCause_EN_WelStop_OtherMove;
                  Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
                  Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
                  Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_PaComfort_CtrlModel_IN_CommonInactive;
                }
                else
                {
                  /* ���źŶ�ʧ */
                  if (((BOOL)TRUE) == MtrPAWel_0x28E_BDCLostFlag)
                  {
                    Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                      enWelStopCause_EN_WelStop_enBDCDoorLost;
                    Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                      Appl_PaComfort_CtrlModel_IN_CommonInactive;
                  }
                  else
                  {
                    /* ��ѹ������ģʽ */
                    if ((enFinalPowerMode_EN_NORMAL_VOLT != MtrPAWel_VoltMode) ||
                        (((BOOL)TRUE) != MtrPAWel_VoltSatisfy))
                    {
                      Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                        enWelStopCause_EN_WelStop_VoltageError;
                      Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                        Appl_PaComfort_CtrlModel_IN_CommonInactive;
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;

     case Appl_PaComfort_CtrlModel_IN_CommonInactive:
      /* ӭ��ʹ�� && �������ת���� && ������̵���ճ������
         && �޿�����ת���� && �޿����̵���ճ������&& ��busoff����
         && ����������ѧϰ &&�޸����ȼ��˶� && ��ѹ����
         && TRUE == Gear_PN_Flag ... */
      if ((((BOOL)TRUE) == rtb_ComfortOpenFlag) && (((BOOL)FALSE) ==
           MtrPAWel_LengthLockSts) && (((BOOL)FALSE) ==
           MtrPAWel_LengthRelayFaultSts) && (((BOOL)FALSE) ==
           MtrPAWel_BackLockSts) && (((BOOL)FALSE) == MtrPAWel_BackRelayFaultSts)
          && (((BOOL)FALSE) == MtrPAWel_BusoffFlag) && (((BOOL)TRUE) ==
           rtb_SeatLearnResult_p) && (enSeatMotorRunType_EN_ComfortEnable >=
           MtrPAWel_CurrentMoveType) && (((BOOL)FALSE) ==
           MtrPAWel_0x28E_BDCLostFlag) && (enFinalPowerMode_EN_NORMAL_VOLT ==
           MtrPAWel_VoltMode) && (((BOOL)TRUE) == MtrPAWel_VoltSatisfy))
      {
        Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
          enWelStopCause_EN_WelStop_NULL;
        Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
          Appl_PaComfort_CtrlModel_IN_CommonActive;
      }
      break;

     default:
      /* ӭ��ʹ�� && �������ת���� && ������̵���ճ������
         && �޿�����ת���� && �޿����̵���ճ������ && ��busoff����
         && ����������ѧϰ &&�޸����ȼ��˶� && ��ѹ����
         && TRUE == Gear_PN_Flag ... */
      if ((((BOOL)TRUE) == rtb_ComfortOpenFlag) && (((BOOL)FALSE) ==
           MtrPAWel_LengthLockSts) && (((BOOL)FALSE) ==
           MtrPAWel_LengthRelayFaultSts) && (((BOOL)FALSE) ==
           MtrPAWel_BackLockSts) && (((BOOL)FALSE) == MtrPAWel_BackRelayFaultSts)
          && (((BOOL)FALSE) == MtrPAWel_BusoffFlag) && (((BOOL)TRUE) ==
           rtb_SeatLearnResult_p) && (enSeatMotorRunType_EN_ComfortEnable >=
           MtrPAWel_CurrentMoveType) && (((BOOL)FALSE) ==
           MtrPAWel_0x28E_BDCLostFlag) && (enFinalPowerMode_EN_NORMAL_VOLT ==
           MtrPAWel_VoltMode) && (((BOOL)TRUE) == MtrPAWel_VoltSatisfy))
      {
        Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
          enWelStopCause_EN_WelStop_NULL;
        Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
          Appl_PaComfort_CtrlModel_IN_CommonActive;
      }
      else
      {
        /* ӭ������ */
        if (((BOOL)TRUE) != rtb_ComfortOpenFlag)
        {
          /* Set_WelcomeUpdatePosiFlag(TRUE); */
          Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
            enWelStopCause_EN_WelStop_PRM;
          Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
            Appl_PaComfort_CtrlModel_IN_CommonInactive;
        }
        else
        {
          /* ������򿿱���ת���� */
          if ((((BOOL)FALSE) != MtrPAWel_LengthLockSts) || (((BOOL)FALSE) !=
               MtrPAWel_BackLockSts))
          {
            /* Set_WelcomeUpdatePosiFlag(TRUE); */
            Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
              enWelStopCause_EN_WelStop_LockFault;
            Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
              Appl_PaComfort_CtrlModel_IN_CommonInactive;
          }
          else
          {
            /* ��������򿿱��̵������� */
            if ((((BOOL)FALSE) != MtrPAWel_LengthRelayFaultSts) || (((BOOL)FALSE)
                 != MtrPAWel_BackRelayFaultSts))
            {
              Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                enWelStopCause_EN_WelStop_RelayFault;
              Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                Appl_PaComfort_CtrlModel_IN_CommonInactive;
            }
            else
            {
              /* ��busoff���� */
              if (((BOOL)FALSE) != MtrPAWel_BusoffFlag)
              {
                Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                  enWelStopCause_EN_WelStop_Busoff;
                Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_PaComfort_CtrlModel_IN_CommonInactive;
              }
              else
              {
                /* ���򡢿���δѧϰ */
                if (((BOOL)TRUE) != rtb_SeatLearnResult_p)
                {
                  /* Set_WelcomeUpdatePosiFlag(TRUE); */
                  Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                    enWelStopCause_EN_WelStop_enNotLearn;
                  Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_PaComfort_CtrlModel_IN_CommonInactive;
                }
                else
                {
                  /* �и�����ӭ���˶������� */
                  if (enSeatMotorRunType_EN_ComfortEnable <
                      MtrPAWel_CurrentMoveType)
                  {
                    /* Set_WelcomeUpdatePosiFlag(TRUE); */
                    Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                      enWelStopCause_EN_WelStop_OtherMove;
                    Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                      Appl_PaComfort_CtrlModel_IN_CommonInactive;
                  }
                  else
                  {
                    /* ���źŶ�ʧ */
                    if (((BOOL)TRUE) == MtrPAWel_0x28E_BDCLostFlag)
                    {
                      Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                        enWelStopCause_EN_WelStop_enBDCDoorLost;
                      Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                        Appl_PaComfort_CtrlModel_IN_CommonInactive;
                    }
                    else
                    {
                      /* ��ѹ������ģʽ */
                      if ((enFinalPowerMode_EN_NORMAL_VOLT != MtrPAWel_VoltMode)
                          || (((BOOL)TRUE) != MtrPAWel_VoltSatisfy))
                      {
                        Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
                          enWelStopCause_EN_WelStop_VoltageError;
                        Appl_PaComfort_CtrlModel_DW.is_CommonCondition =
                          Appl_PaComfort_CtrlModel_IN_CommonInactive;
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
    }

    if (Appl_PaComfort_CtrlModel_DW.is_DoorSts ==
        Appl_PaComfort_CtrlModel_IN_DoorInit)
    {
      /*  �ȴ���ȡe2p����  */
      if (Appl_PaComfort_CtrlModel_DW.WaitTimeCnt > 20)
      {
        Appl_PaComfort_CtrlModel_DW.WaitTimeCnt = 0U;
        Appl_PaComfort_CtrlModel_Get_DoorSts();
        Appl_PaComfort_CtrlModel_DW.LocalDoorSts =
          Appl_PaComfort_CtrlModel_B.MtrWel_WelcomeSwitch;
        Appl_PaComfort_CtrlModel_DW.is_DoorSts =
          Appl_PaComfort_CtrlModel_IN_DoorSts1;
        Appl_PaComfort_CtrlModel_DW.is_BackwardTriggerCondition =
          Appl_PaComfort_CtrlModel_IN_BWInactive;
        Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);
        Appl_PaComfort_CtrlModel_DW.is_ForwardTriggercondition =
          Appl_PaComfort_CtrlModel_IN_FWInactive;
        Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);
      }
      else
      {
        tmp = Appl_PaComfort_CtrlModel_DW.WaitTimeCnt + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_PaComfort_CtrlModel_DW.WaitTimeCnt = (INT8U)tmp;
        Appl_PaComfort_CtrlModel_Get_DoorSts();
        Appl_PaComfort_CtrlModel_DW.LocalDoorSts =
          Appl_PaComfort_CtrlModel_B.MtrWel_WelcomeSwitch;
      }
    }
    else
    {
      Appl_PaComfort_CtrlModel_DW.LocalDoorSts = MtrPAWel_BDC_FRDoorSts;
      Appl_PaComfort_CtrlModel_Get_DoorSts();
      if (Appl_PaComfort_CtrlModel_DW.is_BackwardTriggerCondition ==
          Appl_PaComfort_CtrlModel_IN_BWActive)
      {
        Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)TRUE);

        /* 2���������� */
        if (Appl_PaComfort_CtrlModel_DW.temporalCounter_i1 >= 2)
        {
          Appl_PaComfort_CtrlModel_DW.is_BackwardTriggerCondition =
            Appl_PaComfort_CtrlModel_IN_BWInactive;
          Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);
        }
      }
      else
      {
        Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);

        /*  ӭ����������
           C5����ǰ����״̬�ɹرա��򿪣�BDC_FRDoorSts=0x0:Close��0x1:Open����ǰ�������� */
        if ((LocalDoorSts_prev != Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start)
            && (Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start == ((INT8U)D_OPEN))
            && (Appl_PaComfort_CtrlModel_B.MtrWel_WelcomeSwitch <= ((INT8U)
              D_OPEN)))
        {
          Appl_PaComfort_CtrlModel_DW.is_BackwardTriggerCondition =
            Appl_PaComfort_CtrlModel_IN_BWActive;
          Appl_PaComfort_CtrlModel_DW.temporalCounter_i1 = 0U;
          Appl_PaComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)TRUE);
        }
      }

      if (Appl_PaComfort_CtrlModel_DW.is_ForwardTriggercondition ==
          Appl_PaComfort_CtrlModel_IN_FWActive)
      {
        Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)TRUE);

        /* 2���������� */
        if (Appl_PaComfort_CtrlModel_DW.temporalCounter_i2 >= 2)
        {
          Appl_PaComfort_CtrlModel_DW.is_ForwardTriggercondition =
            Appl_PaComfort_CtrlModel_IN_FWInactive;
          Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);
        }
      }
      else
      {
        Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);

        /*  ӭ��ǰ������
           C6����ǰ����״̬�ɴ򿪡��رգ�BDC_FRDoorSts=0x1:Open��0x0:Close����ǰ�������� */
        if ((LocalDoorSts_prev != Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start)
            && (Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start == ((INT8U)
              D_CLOSE)) && (Appl_PaComfort_CtrlModel_B.MtrWel_WelcomeSwitch <=
                            ((INT8U)D_OPEN)))
        {
          Appl_PaComfort_CtrlModel_DW.is_ForwardTriggercondition =
            Appl_PaComfort_CtrlModel_IN_FWActive;
          Appl_PaComfort_CtrlModel_DW.temporalCounter_i2 = 0U;
          Appl_PaComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)TRUE);
        }
      }

      /*  ��״̬�仯 ������  */
      if ((LocalDoorSts_prev != Appl_PaComfort_CtrlModel_DW.LocalDoorSts_start) &&
          (Appl_PaComfort_CtrlModel_DW.LocalDoorSts <= ((INT8U)D_OPEN)))
      {
        Appl_PaComfort_CtrlModel_B.In1_l =
          Appl_PaComfort_CtrlModel_DW.LocalDoorSts;
        Srvl_SetMemIndexDataU8(EN_MemIndex_PaDoorSts,
          Appl_PaComfort_CtrlModel_B.In1_l);
      }
    }

    /*  ��������仯 �ҷ����ʹ��ܵ��� ��Ҫ��������λ��  */
    if ((enSeatMotorRunType_EN_ComfortEnable != MtrPAWel_CurrentMoveType) &&
        (enSeatMotorRunType_EN_NULL != MtrPAWel_CurrentMoveType) &&
        (((MtrPAWel_LengthCmd_prev !=
           Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start) &&
          (Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start == 1)) ||
         ((MtrPAWel_LengthCmd_prev !=
           Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start) &&
          (Appl_PaComfort_CtrlModel_DW.MtrPAWel_LengthCmd_start == 2))))
    {
      Appl_PaComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
      Appl_PaComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
    }
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_PaComfort_CtrlModel_UpDataOutputInfo(void)
{
  CanTx_0x3B2_DSM_St_FRSeatmeet(Appl_PaComfort_CtrlModel_B.DataTypeConversion);
  Rte_SetVfb_PaWelBackReqPosi(Appl_PaComfort_CtrlModel_B.WelcomeBackReqPosi);
  Rte_SetVfb_PaWelLengthReqCMD(Appl_PaComfort_CtrlModel_B.WelcomeReqCMD);
  Rte_SetVfb_PaWelLengthReqPosi(Appl_PaComfort_CtrlModel_B.WelcomeReqPosi);
  Rte_SetVfb_PaWelcomeRunSts(Appl_PaComfort_CtrlModel_B.WelcomeRunStatus);
  Rte_SetVfb_PaWelcomeStopReason(Appl_PaComfort_CtrlModel_B.WelcomeStopReasonOut);
}

/* Model step function */
void Appl_PaComfort_CtrlModel_step(void)
{
  Appl_PaComfort_CtrlModel_UpDataInputInfo();
  Appl_PaComfort_CtrlModel_LogicCtrl();
  Appl_PaComfort_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_PaComfort_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_PaComfort_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_PaComfort_CtrlModel_B), 0,
                sizeof(B_Appl_PaComfort_CtrlModel_T));

  {
    Appl_PaComfort_CtrlModel_B.WelcomeStopReason =
      enWelStopCause_EN_WelStop_NULL;
  }

  /* exported global signals */
  MtrPAWel_WelcomeStatus = enWelcomeSts_EN_NULL;
  MtrPAWel_VehiclePrm = enVehTypePrm_enP20;
  MtrPAWel_CurrentMoveType = enSeatMotorRunType_EN_NULL;
  MtrPAWel_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  MtrPAWel_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  MtrPAWel_BackHallPosi = ((INT16U)0U);
  MtrPAWel_BackMotorSize = ((INT16U)0U);
  MtrPAWel_BackStopPosi = ((INT16U)0U);
  MtrPAWel_LengthBWTargetPosi = ((INT16U)0U);
  MtrPAWel_LengthFWTargetPosi = ((INT16U)0U);
  MtrPAWel_LengthHallPosi = ((INT16U)0U);
  MtrPAWel_LengthStopPosi = ((INT16U)0U);
  MtrPAWel_0x28E_BDCLostFlag = ((INT8U)0U);
  MtrPAWel_0x351_IVI_St_FRSeatmeet = ((INT8U)0U);
  MtrPAWel_AdjustEnable = ((INT8U)0U);
  MtrPAWel_BDC_FRDoorSts = ((INT8U)0U);
  MtrPAWel_BackHallFaultSts = ((INT8U)0U);
  MtrPAWel_BackLockSts = ((INT8U)0U);
  MtrPAWel_BackRelayFaultSts = ((INT8U)0U);
  MtrPAWel_BusoffFlag = ((INT8U)0U);
  MtrPAWel_GearPNFlag = ((INT8U)0U);
  MtrPAWel_GetRecoverDefaultFlag = ((INT8U)0U);
  MtrPAWel_LengthCmd = ((INT8U)0U);
  MtrPAWel_LengthHallFaultSts = ((INT8U)0U);
  MtrPAWel_LengthLockSts = ((INT8U)0U);
  MtrPAWel_LengthRelayFaultSts = ((INT8U)0U);
  MtrPAWel_UpdatePosiFlag = ((INT8U)0U);
  MtrPAWel_VoltSatisfy = ((INT8U)0U);
  MtrPAWel_WelcomeEnable = ((INT8U)0U);
  MtrPAWel_WelcomeSwitch = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_PaComfort_CtrlModel_DW, 0,
                sizeof(DW_Appl_PaComfort_CtrlModel_T));
  Appl_PaComfort_CtrlModel_UpDataInputInfo_Init();
  Appl_PaComfort_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
