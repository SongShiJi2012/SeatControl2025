/*
 * File: Appl_DrComfort_CtrlModel.c
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

#include "Appl_DrComfort_CtrlModel.h"

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

#ifndef D_SoftDistanceDrLegnth
#error The variable for the parameter "D_SoftDistanceDrLegnth" is not defined
#endif

/* Named constants for Chart: '<S5>/WelcomeLogic' */
#define Appl_DrComfort_CtrlModel_IN_BackCheck ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_BackwardRunning ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_BackwardSuccess ((INT8U)3U)
#define Appl_DrComfort_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_DrComfort_CtrlModel_IN_WelcomeActive ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_WelcomeBackward ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_WelcomeDefault ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_WelcomeForward ((INT8U)3U)
#define Appl_DrComfort_CtrlModel_IN_WelcomeInactive ((INT8U)3U)

/* Named constants for Chart: '<S13>/Chart' */
#define Appl_DrComfort_CtrlModel_IN_Init_b ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_MoreThan ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c ((INT8U)0U)

/* Named constants for Chart: '<S14>/GearDeal' */
#define Appl_DrComfort_CtrlModel_IN_Gear_Not_PN ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_Gear_PN ((INT8U)2U)

/* Named constants for Chart: '<S16>/ComfortDeal' */
#define Appl_DrComfort_CtrlModel_IN_Configurable ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_Disable ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_Enable ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_Init_h ((INT8U)2U)

/* Named constants for Chart: '<S17>/Precondition_Trigger' */
#define Appl_DrComfort_CtrlModel_IN_BWActive ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_BWInactive ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_CommonActive ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_CommonInactive ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_CommonInit ((INT8U)3U)
#define Appl_DrComfort_CtrlModel_IN_DoorInit ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_DoorSts ((INT8U)2U)
#define Appl_DrComfort_CtrlModel_IN_FWActive ((INT8U)1U)
#define Appl_DrComfort_CtrlModel_IN_FWInactive ((INT8U)2U)

/* Exported block signals */
enWelcomeSts MtrWel_WelcomeStatus;     /* '<S12>/MtrWel_WelcomeStatus'
                                        * ����ӭ������״̬
                                        */
enVehTypePrm MtrWel_VehiclePrm;        /* '<S12>/MtrWel_VehiclePrm'
                                        * ���ͣ�C62X��C52X��
                                        */
enSeatMotorRunType MtrWel_CurrentMoveType;/* '<S12>/MtrWel_CurrentMoveType'
                                           * ���ݵ����ǰ��������
                                           */
enSeatAutoRunSts MtrWel_LengthAutoRunFlag;/* '<S12>/MtrWel_LengthAutoRunFlag'
                                           * ���������Զ����б�־λ
                                           */
enNapMode MtrWel_NapMode;              /* '<S12>/MtrWel_NapMode'
                                        * С�ģʽ
                                        */
enFinalPowerMode MtrWel_VoltMode;      /* '<S12>/MtrWel_VoltMode'
                                        * ������ѹģʽ
                                        */
enDrAdjustEnable MtrWel_AdjustEnable;  /* '<S12>/MtrWel_AdjustEnable'
                                        * �������ε���:
                                        */
INT16U MtrWel_BackHallPosi;            /* '<S12>/MtrWel_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
INT16U MtrWel_BackMotorSize;           /* '<S12>/MtrWel_BackMotorSize'
                                        * ���ݿ������쳤��
                                        */
INT16U MtrWel_BackStopPosi;            /* '<S12>/MtrWel_BackStopPosi'
                                        * ���ݿ���ֹ��
                                        */
INT16U MtrWel_LengthBWTargetPosi;      /* '<S12>/MtrWel_LengthBWTargetPosi'
                                        * �����������Ŀ��λ��
                                        */
INT16U MtrWel_LengthFWTargetPosi;      /* '<S12>/MtrWel_LengthFWTargetPosi'
                                        * ��������ǰ��Ŀ��λ��
                                        */
INT16U MtrWel_LengthHallPosi;          /* '<S12>/MtrWel_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
INT16U MtrWel_LengthStopPosi;          /* '<S12>/MtrWel_LengthStopPosi'
                                        * ��������ֹ��
                                        */
INT8U MtrWel_0x238_GearLostFlag;       /* '<S12>/MtrWel_0x238_GearLostFlag'
                                        * 0x238���ĵ��߱�־λ
                                        */
INT8U MtrWel_0x238_TCU_GearSelDisp;    /* '<S12>/MtrWel_0x238_TCU_GearSelDisp'
                                        * ��λ״̬
                                        */
INT8U MtrWel_0x26E_GearSelLostFlag;    /* '<S12>/MtrWel_0x26E_GearSelLostFlag'
                                        * 0x26E���ĵ��߱�־λ
                                        */
INT8U MtrWel_0x26E_VCU_GearSelDisp;    /* '<S12>/MtrWel_0x26E_VCU_GearSelDisp'
                                        * ��λ״̬
                                        */
INT8U MtrWel_0x28E_BDCLostFlag;        /* '<S12>/MtrWel_0x28E_BDCLostFlag'
                                        * 0x281���ĵ��߱�־λ
                                        */
INT8U MtrWel_0x351_IVI_St_FLSeatmeet;  /* '<S12>/MtrWel_0x351_IVI_St_FLSeatmeet'
                                        * ����ӭ��ʹ��
                                        */
INT8U MtrWel_BDC_FLDoorSts;            /* '<S12>/MtrWel_BDC_FLDoorSts'
                                        * ��ǰ��״̬
                                        */
INT8U MtrWel_BackHallFaultSts;         /* '<S12>/MtrWel_BackHallFaultSts'
                                        * ������������
                                        */
INT8U MtrWel_BackLockSts;              /* '<S12>/MtrWel_BackLockSts'
                                        * ���ݿ�����ת״̬
                                        */
INT8U MtrWel_BackRelayFaultSts;        /* '<S12>/MtrWel_BackRelayFaultSts'
                                        * �����̵���ճ��
                                        */
INT8U MtrWel_BusoffFlag;               /* '<S12>/MtrWel_BusoffFlag'
                                        * ����busoff��־λ
                                        */
INT8U MtrWel_GetRecoverDefaultFlag;    /* '<S12>/MtrWel_GetRecoverDefaultFlag'
                                        * �ָ���������
                                        */
INT8U MtrWel_LengthCmd;                /* '<S12>/MtrWel_LengthCmd'
                                        * ����������
                                        */
INT8U MtrWel_LengthHallFaultSts;       /* '<S12>/MtrWel_LengthHallFaultSts'
                                        * �����������
                                        */
INT8U MtrWel_LengthLockSts;            /* '<S12>/MtrWel_LengthLockSts'
                                        * ���������ת״̬
                                        */
INT8U MtrWel_LengthRelayFaultSts;      /* '<S12>/MtrWel_LengthRelayFaultSts'
                                        * ����̵���ճ��
                                        */
INT8U MtrWel_P20_PHEV_EngineCfg;       /* '<S12>/MtrWel_P20_PHEV_EngineCfg'
                                        * ����P20PHEV������ʹ������
                                        */
INT8U MtrWel_UpdatePosiFlag;           /* '<S12>/MtrWel_UpdatePosiFlag'
                                        * ����ӭ��λ�ø��±�־
                                        */
INT8U MtrWel_VoltSatisfy;              /* '<S12>/MtrWel_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */
INT8U MtrWel_WelcomeEnable;            /* '<S12>/MtrWel_WelcomeEnable'
                                        * ����ӭ��ʹ��״̬
                                        */
INT8U MtrWel_WelcomeSwitch;            /* '<S12>/MtrWel_WelcomeSwitch'
                                        * ����ӭ������״̬
                                        */

/* Block signals (default storage) */
B_Appl_DrComfort_CtrlModel_T Appl_DrComfort_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_DrComfort_CtrlModel_T Appl_DrComfort_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_DrComfort_CtrlModel_T Appl_DrComfort_CtrlModel_M_;
RT_MODEL_Appl_DrComfort_CtrlModel_T *const Appl_DrComfort_CtrlModel_M =
  &Appl_DrComfort_CtrlModel_M_;
static void Appl_DrComfort_CtrlModel_Set_WelcomeUpdatePosiFlag(void);
static void Appl_DrComfort_CtrlModel_Set_WelcomeStatus(void);
static void Appl_DrComfort_CtrlModel_LogicCtrl_Init(void);
static void Appl_DrComfort_CtrlModel_LogicCtrl(void);
static void Appl_DrComfort_CtrlModel_SetComfortPrm(void);
static void Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d(void);
static void Appl_DrComfort_CtrlModel_Get_DoorSts(void);
static void Appl_DrComfort_CtrlModel_RTE(void);
static void Appl_DrComfort_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_DrComfort_CtrlModel_UpDataInputInfo(void);
static void Appl_DrComfort_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_DrComfort_CtrlModel_WelcomeActive(const INT8U
  *BackwardTriggerCondition_prev, const INT8U *ForwardTriggerCondition_prev);

/* Forward declaration for local functions */
static void Appl_DrComfort_CtrlModel_CommonCondition(const INT8U *Gear_PN_Flag,
  const INT8U *ComfortOpenFlag, const BOOL *SeatLearnResult);

/* Output and update for function-call system: '<S6>/Set_WelcomeUpdatePosiFlag' */
static void Appl_DrComfort_CtrlModel_Set_WelcomeUpdatePosiFlag(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomeDrUpate,
    Appl_DrComfort_CtrlModel_B.In1_e);
}

/* Output and update for function-call system: '<S6>/Set_WelcomeStatus' */
static void Appl_DrComfort_CtrlModel_Set_WelcomeStatus(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomeStatus,
    Appl_DrComfort_CtrlModel_B.In1_ks);
}

/* Function for Chart: '<S5>/WelcomeLogic' */
static void Appl_DrComfort_CtrlModel_WelcomeActive(const INT8U
  *BackwardTriggerCondition_prev, const INT8U *ForwardTriggerCondition_prev)
{
  INT16U LocalLengthReqPosi;
  INT32S tmp;
  INT32S tmp_0;

  /* ǰ�ƹ�����||���ƹ�����ǰ�����������㣬�´���Ҫ����Ŀ������ */
  if (((Appl_DrComfort_CtrlModel_DW.WelcomeStatus ==
        enWelcomeSts_EN_Wel_FWOngoing) ||
       (Appl_DrComfort_CtrlModel_DW.WelcomeStatus ==
        enWelcomeSts_EN_Wel_BWOngoing)) && (enWelStopCause_EN_WelStop_NULL !=
       Appl_DrComfort_CtrlModel_B.WelcomeStopReason))
  {
    Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
      Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
      Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
      Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
      Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
    Appl_DrComfort_CtrlModel_B.In1_e = ((BOOL)TRUE);
    Appl_DrComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
    Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
      Appl_DrComfort_CtrlModel_IN_WelcomeInactive;

    /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
       ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
    Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
    Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
    Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
    Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
    Appl_DrComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
    Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
      Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
    Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
    Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 10U;

    /* ����������ԭ��ǿգ���������ֹͣԭ�� */
    if (enWelStopCause_EN_WelStop_NULL !=
        Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
    {
      Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
        Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
      Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 12U;

      /* mantis��7341����EEPORM�洢ʧ�� */
      Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
        Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
      Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
    }
  }
  else
  {
    /* ��������������� */
    if (((BOOL)TRUE) == MtrWel_LengthHallFaultSts)
    {
      Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
        enWelStopCause_EN_WelStop_HallFault;
      Appl_DrComfort_CtrlModel_B.In1_e = ((BOOL)TRUE);
      Appl_DrComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
      Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_WelcomeInactive;

      /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
         ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
      Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
      Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
      Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
      Appl_DrComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
      Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
        Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
      Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
      Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 10U;

      /* ����������ԭ��ǿգ���������ֹͣԭ�� */
      if (enWelStopCause_EN_WelStop_NULL !=
          Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
      {
        Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
          Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
        Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 12U;

        /* mantis��7341����EEPORM�洢ʧ�� */
        Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
          Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
        Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
      }
    }
    else
    {
      /*  ������������  */
      if (((BOOL)TRUE) == MtrWel_BackHallFaultSts)
      {
        Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
          Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
          enWelStopCause_EN_WelStop_HallFault;
        Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
          Appl_DrComfort_CtrlModel_IN_WelcomeInactive;

        /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
           ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
        Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
        Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
          Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
        Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
        Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 10U;

        /* ����������ԭ��ǿգ���������ֹͣԭ�� */
        if (enWelStopCause_EN_WelStop_NULL !=
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
        {
          Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
          Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 12U;

          /* mantis��7341����EEPORM�洢ʧ�� */
          Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
            Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
          Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
        }
      }
      else
      {
        /* ǰ�����������㣬�Ҳ���Ҫ����Ŀ������ */
        if (enWelStopCause_EN_WelStop_NULL !=
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
        {
          Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
            Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
            Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
          Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
            Appl_DrComfort_CtrlModel_IN_WelcomeInactive;

          /* ����ֹͣԭ��������������������ꡢ����ӭ��״̬
             ӭ��δ���1.�������� = �ޣ� 2.ӭ������ = 0�� */
          Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
          Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
          Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
          Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
          Appl_DrComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
          Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
            Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
          Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
          Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 10U;

          /* ����������ԭ��ǿգ���������ֹͣԭ�� */
          if (enWelStopCause_EN_WelStop_NULL !=
              Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
          {
            Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 12U;

            /* mantis��7341����EEPORM�洢ʧ�� */
            Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
          }
        }
        else
        {
          switch (Appl_DrComfort_CtrlModel_DW.is_WelcomeActive)
          {
           case Appl_DrComfort_CtrlModel_IN_WelcomeBackward:
            /* ����ǰ������ */
            if ((*ForwardTriggerCondition_prev !=
                 Appl_DrComfort_CtrlModel_DW.ForwardTriggerCondition_start) &&
                (Appl_DrComfort_CtrlModel_DW.ForwardTriggerCondition_start ==
                 ((BOOL)TRUE)))
            {
              /* WelcomeStatus = enWelcomeSts.EN_BackMovingExForWard */
              Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_DrComfort_CtrlModel_IN_WelcomeForward;

              /* ӭ��״̬ = ǰ��
                 ��ֹͻȻ������´β�����ִ�к��� */
              Appl_DrComfort_CtrlModel_DW.WelcomeStatus =
                enWelcomeSts_EN_Wel_FWOngoing;
              Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
                Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
              Appl_DrComfort_CtrlModel_Set_WelcomeStatus();

              /* ӭ��ǰ�ƣ�
                 1.����״̬ = ǰ�������У�
                 2.�������� = ǰ�ƣ�
                 3.ӭ������ = ǰ��Ŀ�����ꣻ */
              Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                enWelcomeRunSts_EN_Wel_FWOngoing;
              Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              Appl_DrComfort_CtrlModel_B.WelcomeReqPosi =
                MtrWel_LengthFWTargetPosi;
              Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
            }
            else
            {
              /* ��Ĭ��״̬����&&EEPROMҪ�����ӭ������ ���������쳣  */
              if ((((BOOL)TRUE) ==
                   Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag) && ((((BOOL)
                     TRUE) == MtrWel_UpdatePosiFlag) ||
                   (MtrWel_LengthBWTargetPosi == 0) ||
                   (MtrWel_LengthBWTargetPosi == 0xFFFF) ||
                   (MtrWel_LengthFWTargetPosi == 0) ||
                   (MtrWel_LengthFWTargetPosi == 0xFFFF) ||
                   (MtrWel_LengthFWTargetPosi < MtrWel_LengthBWTargetPosi)))
              {
                /* ���ʼ����ת��־λ�������ӭ�������־λ������ǰ������ */
                Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)FALSE);
                tmp = MtrWel_LengthHallPosi - ((INT16U)D_WelcomeDistance);
                if (tmp < 0)
                {
                  tmp = 0;
                }

                Appl_DrComfort_CtrlModel_B.In1_e = ((BOOL)FALSE);
                Appl_DrComfort_CtrlModel_Set_WelcomeUpdatePosiFlag();
                Appl_DrComfort_CtrlModel_B.In1_b = MtrWel_LengthHallPosi;
                Srvl_SetMemIndexDataU16(EN_MemIndex_DrWelcome_LenTar_ForWard,
                  Appl_DrComfort_CtrlModel_B.In1_b);

                /* ����Ŀ��λ���Ƿ񳬹���ֹ�� */
                tmp_0 = MtrWel_LengthStopPosi + ((INT8U)D_SoftDistanceDrLegnth);
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
                Appl_DrComfort_CtrlModel_B.In1_k = LocalLengthReqPosi;
                Srvl_SetMemIndexDataU16(EN_MemIndex_DrWelcome_LenTar_BackWard,
                  Appl_DrComfort_CtrlModel_B.In1_k);
              }
              else
              {
                LocalLengthReqPosi = MtrWel_LengthBWTargetPosi;
              }

              switch (Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward)
              {
               case Appl_DrComfort_CtrlModel_IN_BackCheck:
                /*  ��������Ƕ�����  */
                if (Appl_DrComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)TRUE))
                {
                  Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_DrComfort_CtrlModel_IN_BackwardRunning;
                  Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                  Appl_DrComfort_CtrlModel_DW.WelcomeStatus =
                    enWelcomeSts_EN_Wel_BWOngoing;
                  Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                    enWelcomeRunSts_EN_Wel_BWOngoing;
                  Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
                  Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = LocalLengthReqPosi;
                }
                else
                {
                  /*  ����������Ƕ�����  */
                  if (Appl_DrComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
                  {
                    Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi =
                      Appl_DrComfort_CtrlModel_B.BackMoreThanHall;
                    Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
                  }

                  Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 14U;
                }
                break;

               case Appl_DrComfort_CtrlModel_IN_BackwardRunning:
                /* ���е�����Ŀ��λ�� */
                if (enSeatAutoRunSts_EN_SEAT_SUCCESS == MtrWel_LengthAutoRunFlag)
                {
                  Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
                  Appl_DrComfort_CtrlModel_DW.WelcomeStatus =
                    enWelcomeSts_EN_BackwardStsSuccess;
                  Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                    enWelcomeRunSts_EN_Wel_BWMoveSuccess;
                  Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
                    Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
                  Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
                  Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                    Appl_DrComfort_CtrlModel_IN_BackwardSuccess;

                  /* ӭ��Ĭ��״̬��1.�������� = �ޣ�
                     2.ӭ������ = 0�� */
                  Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                  Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                  Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                }
                else
                {
                  Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = LocalLengthReqPosi;
                }
                break;
              }
            }
            break;

           case Appl_DrComfort_CtrlModel_IN_WelcomeDefault:
            /* �����������&&��һ��δ�ɹ�ִ�к��� */
            if ((*BackwardTriggerCondition_prev !=
                 Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start) &&
                (Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start ==
                 ((BOOL)TRUE)) && (enWelcomeSts_EN_BackwardStsSuccess !=
                                   Appl_DrComfort_CtrlModel_DW.WelcomeStatus))
            {
              Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = ((BOOL)TRUE);
              Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_DrComfort_CtrlModel_IN_WelcomeBackward;
              Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_DrComfort_CtrlModel_IN_BackCheck;

              /*  ����������Ƕ�����  */
              if (Appl_DrComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
              {
                Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi =
                  Appl_DrComfort_CtrlModel_B.BackMoreThanHall;
                Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              }

              Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 14U;
            }
            else
            {
              /* ���Ƴɹ�&&û�д�Ϲ�������ԭ��mantis��7341�� */
              if ((enWelcomeSts_EN_BackwardStsSuccess ==
                   Appl_DrComfort_CtrlModel_DW.WelcomeStatus) &&
                  (MtrWel_UpdatePosiFlag == ((BOOL)FALSE)))
              {
                Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_DrComfort_CtrlModel_IN_WelcomeBackward;
                Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                  Appl_DrComfort_CtrlModel_IN_BackwardSuccess;

                /* ӭ��Ĭ��״̬��1.�������� = �ޣ�
                   2.ӭ������ = 0�� */
                Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
                Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                  enWelcomeRunSts_EN_Wel_BWMoveSuccess;
              }
            }
            break;

           default:
            /* ����������� */
            if ((*BackwardTriggerCondition_prev !=
                 Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start) &&
                (Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start ==
                 ((BOOL)TRUE)))
            {
              /* WelcomeStatus = enWelcomeSts.EN_ForWardMovingExBack */
              Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                Appl_DrComfort_CtrlModel_IN_WelcomeBackward;
              Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
                Appl_DrComfort_CtrlModel_IN_BackCheck;

              /*  ����������Ƕ�����  */
              if (Appl_DrComfort_CtrlModel_B.BackMoreThanFlg == ((BOOL)FALSE))
              {
                Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi =
                  Appl_DrComfort_CtrlModel_B.BackMoreThanHall;
                Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)TRUE);
              }

              Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 14U;
            }
            else
            {
              /* �˶���Ŀ������ */
              if (enSeatAutoRunSts_EN_SEAT_SUCCESS == MtrWel_LengthAutoRunFlag)
              {
                Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
                Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = (INT8U)
                  enWelcomeRunSts_EN_Wel_FWMoveSuccess;
                Appl_DrComfort_CtrlModel_DW.WelcomeStatus =
                  enWelcomeSts_EN_ForwardStsSuccess;
                Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
                  Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
                Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
                Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
                  Appl_DrComfort_CtrlModel_IN_WelcomeDefault;

                /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
                Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
                Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
                Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
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
static void Appl_DrComfort_CtrlModel_LogicCtrl_Init(void)
{
  Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrComfort_CtrlModel_DW.is_WelcomeBackward =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrComfort_CtrlModel_DW.is_active_c3_Appl_DrComfort_CtrlModel = 0U;
  Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrComfort_CtrlModel_DW.WelcomeFromeInitFlag = 0U;
  Appl_DrComfort_CtrlModel_DW.WelcomeStatus = enWelcomeSts_EN_NULL;
  Appl_DrComfort_CtrlModel_DW.InitTimer_h = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrComfort_CtrlModel_LogicCtrl(void)
{
  INT8U BackwardTriggerCondition_prev;
  INT8U ForwardTriggerCondition_prev;
  INT32S tmp;
  Appl_DrComfort_CtrlModel_B.DataTypeConversion = (INT8U)
    (Appl_DrComfort_CtrlModel_B.ComfortOpenMsg == 0);
  BackwardTriggerCondition_prev =
    Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start;
  Appl_DrComfort_CtrlModel_DW.BackwardTriggerCondition_start =
    Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition;
  ForwardTriggerCondition_prev =
    Appl_DrComfort_CtrlModel_DW.ForwardTriggerCondition_start;
  Appl_DrComfort_CtrlModel_DW.ForwardTriggerCondition_start =
    Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition;
  if (Appl_DrComfort_CtrlModel_DW.is_active_c3_Appl_DrComfort_CtrlModel == 0U)
  {
    Appl_DrComfort_CtrlModel_DW.is_active_c3_Appl_DrComfort_CtrlModel = 1U;
    Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
      Appl_DrComfort_CtrlModel_IN_Init;
    Appl_DrComfort_CtrlModel_DW.InitTimer_h = 0U;
  }
  else
  {
    switch (Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel)
    {
     case Appl_DrComfort_CtrlModel_IN_Init:
      /* ��ʼ����ɣ���ȡӭ��״̬ */
      if (Appl_DrComfort_CtrlModel_DW.InitTimer_h > ((INT8U)D_InitDelayTime))
      {
        Appl_DrComfort_CtrlModel_DW.InitTimer_h = 0U;
        Appl_DrComfort_CtrlModel_DW.WelcomeStatus = MtrWel_WelcomeStatus;
        Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 13U;
        Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
          Appl_DrComfort_CtrlModel_IN_WelcomeActive;
        Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_DrComfort_CtrlModel_IN_WelcomeDefault;

        /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      }
      else
      {
        tmp = Appl_DrComfort_CtrlModel_DW.InitTimer_h + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_DrComfort_CtrlModel_DW.InitTimer_h = (INT8U)tmp;
      }
      break;

     case Appl_DrComfort_CtrlModel_IN_WelcomeActive:
      Appl_DrComfort_CtrlModel_WelcomeActive(&BackwardTriggerCondition_prev,
        &ForwardTriggerCondition_prev);
      break;

     default:
      /* ӭ��ǰ���������� */
      if (enWelStopCause_EN_WelStop_NULL ==
          Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
      {
        Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 11U;
        Appl_DrComfort_CtrlModel_DW.is_c3_Appl_DrComfort_CtrlModel =
          Appl_DrComfort_CtrlModel_IN_WelcomeActive;
        Appl_DrComfort_CtrlModel_DW.is_WelcomeActive =
          Appl_DrComfort_CtrlModel_IN_WelcomeDefault;

        /* ӭ��Ĭ��״̬��1.�������� = �ޣ� 2.ӭ������ = 0�� */
        Appl_DrComfort_CtrlModel_B.WelcomeReqCMD = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.WelcomeReqPosi = 0U;
        Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi = 0U;
      }
      else
      {
        /* ����������ԭ��ǿգ���������ֹͣԭ�� */
        if (enWelStopCause_EN_WelStop_NULL !=
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason)
        {
          Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut = (INT8U)
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason;
          Appl_DrComfort_CtrlModel_B.WelcomeRunStatus = 12U;

          /* mantis��7341����EEPORM�洢ʧ�� */
          Appl_DrComfort_CtrlModel_B.In1_ks = (INT8U)
            Appl_DrComfort_CtrlModel_DW.WelcomeStatus;
          Appl_DrComfort_CtrlModel_Set_WelcomeStatus();
        }
      }
      break;
    }
  }
}

/* Output and update for function-call system: '<S21>/SetComfortPrm' */
static void Appl_DrComfort_CtrlModel_SetComfortPrm(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomeSwitch,Appl_DrComfort_CtrlModel_B.in);
}

/* Output and update for function-call system: '<S23>/Set_WelcomeUpdatePosiFlag' */
static void Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_WelcomeDrUpate,
    Appl_DrComfort_CtrlModel_B.In1);
}

/* Output and update for function-call system: '<S23>/Get_DoorSts' */
static void Appl_DrComfort_CtrlModel_Get_DoorSts(void)
{
  Appl_DrComfort_CtrlModel_B.MtrWel_WelcomeSwitch_p = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrDoorSts);
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_DrComfort_CtrlModel_RTE(void)
{
  MtrWel_0x238_GearLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x238);
  MtrWel_0x238_TCU_GearSelDisp = CanRx_0x238_TCU_GearSelDisp( );
  MtrWel_0x26E_GearSelLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x26E);
  MtrWel_0x26E_VCU_GearSelDisp = CanRx_0x26E_VCU_GearSelDisp( );
  MtrWel_0x28E_BDCLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x28E);
  MtrWel_0x351_IVI_St_FLSeatmeet = CanRx_0x351_IVI_St_FLSeatmeet( );
  MtrWel_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
  MtrWel_BDC_FLDoorSts = CanRx_0x28E_BDC_FLDoorSts( );
  MtrWel_BackHallFaultSts = Rte_GetVfb_DrBackHallErr( );
  MtrWel_BackHallPosi = Cdd_GetCurrentHallCnt(EN_DriverBack);
  MtrWel_BackLockSts = Rte_GetVfb_DrBackStallErr( );
  MtrWel_BackMotorSize = Cdd_GetMotorSize(EN_DriverBack);
  MtrWel_BackRelayFaultSts = Rte_GetVfb_DrBackRelayAdheErr( );
  MtrWel_BackStopPosi = Cdd_GetMotorHardStop(EN_DriverBack);
  MtrWel_BusoffFlag = Nm_IsBusOff( );
  MtrWel_CurrentMoveType = Rte_GetVfb_DrMoveType( );
  MtrWel_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  MtrWel_LengthAutoRunFlag = Rte_GetVfb_DrLengthAutoRunFlag( );
  MtrWel_LengthBWTargetPosi = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrWelcome_LenTar_BackWard);
  MtrWel_LengthCmd = Rte_GetVfb_DrHeightMotorCmd( );
  MtrWel_LengthFWTargetPosi = Srvl_GetMemIndexDataU16
    (EN_MemIndex_DrWelcome_LenTar_ForWard);
  MtrWel_LengthHallFaultSts = Rte_GetVfb_DrLengthHallErr( );
  MtrWel_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_DriverLength);
  MtrWel_LengthLockSts = Rte_GetVfb_DrLengthStallErr( );
  MtrWel_LengthRelayFaultSts = Rte_GetVfb_DrLengthRelayAdheErr( );
  MtrWel_LengthStopPosi = Cdd_GetMotorHardStop(EN_DriverLength);
  MtrWel_NapMode = Rte_GetVfb_NapMode( );
  MtrWel_P20_PHEV_EngineCfg = Srvl_GetMemIndexDataU8
    (EN_MemIndex_Heat_P20_PHEV_EngineCfg);
  MtrWel_UpdatePosiFlag = Srvl_GetMemIndexDataU8(EN_MemIndex_WelcomeDrUpate);
  MtrWel_VehiclePrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  MtrWel_VoltMode = Rte_GetVfb_VoltMode( );
  MtrWel_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  MtrWel_WelcomeEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
  MtrWel_WelcomeStatus = Srvl_GetMemIndexDataU8(EN_MemIndex_WelcomeStatus);
  MtrWel_WelcomeSwitch = Srvl_GetMemIndexDataU8(EN_MemIndex_WelcomeSwitch);
}

/* Function for Chart: '<S17>/Precondition_Trigger' */
static void Appl_DrComfort_CtrlModel_CommonCondition(const INT8U *Gear_PN_Flag,
  const INT8U *ComfortOpenFlag, const BOOL *SeatLearnResult)
{
  switch (Appl_DrComfort_CtrlModel_DW.is_CommonCondition)
  {
   case Appl_DrComfort_CtrlModel_IN_CommonActive:
    /* ӭ������ */
    if (((BOOL)TRUE) != *ComfortOpenFlag)
    {
      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
      Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
        enWelStopCause_EN_WelStop_PRM;
      Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
      Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
        Appl_DrComfort_CtrlModel_IN_CommonInactive;
    }
    else
    {
      /* ������򿿱���ת���� */
      if ((((BOOL)FALSE) != MtrWel_LengthLockSts) || (((BOOL)FALSE) !=
           MtrWel_BackLockSts))
      {
        Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
          Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
        Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
          enWelStopCause_EN_WelStop_LockFault;
        Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
        Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
        Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
          Appl_DrComfort_CtrlModel_IN_CommonInactive;
      }
      else
      {
        /* ��������򿿱��̵������� */
        if ((((BOOL)FALSE) != MtrWel_LengthRelayFaultSts) || (((BOOL)FALSE) !=
             MtrWel_BackRelayFaultSts))
        {
          Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
            enWelStopCause_EN_WelStop_RelayFault;
          Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
            Appl_DrComfort_CtrlModel_IN_CommonInactive;
        }
        else
        {
          /* ��busoff���� */
          if (((BOOL)FALSE) != MtrWel_BusoffFlag)
          {
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
              enWelStopCause_EN_WelStop_Busoff;
            Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
              Appl_DrComfort_CtrlModel_IN_CommonInactive;
          }
          else
          {
            /* ��PN�� */
            if (((BOOL)TRUE) != *Gear_PN_Flag)
            {
              Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                enWelStopCause_EN_WelStop_enNotGearPN;
              Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                Appl_DrComfort_CtrlModel_IN_CommonInactive;
            }
            else
            {
              /* ����򿿱�δѧϰ */
              if (((BOOL)TRUE) != *SeatLearnResult)
              {
                Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
                Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                  enWelStopCause_EN_WelStop_enNotLearn;
                Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
                Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
                Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_DrComfort_CtrlModel_IN_CommonInactive;
              }
              else
              {
                /* �и�����ӭ���˶������� */
                if (enSeatMotorRunType_EN_ComfortEnable < MtrWel_CurrentMoveType)
                {
                  Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
                  Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                    enWelStopCause_EN_WelStop_OtherMove;
                  Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
                  Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
                  Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_DrComfort_CtrlModel_IN_CommonInactive;
                }
                else
                {
                  /* ���źŶ�ʧ */
                  if (((BOOL)TRUE) == MtrWel_0x28E_BDCLostFlag)
                  {
                    Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                      enWelStopCause_EN_WelStop_enBDCDoorLost;
                    Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                      Appl_DrComfort_CtrlModel_IN_CommonInactive;
                  }
                  else
                  {
                    /* ��ѹ������ģʽ */
                    if ((enFinalPowerMode_EN_NORMAL_VOLT != MtrWel_VoltMode) ||
                        (((BOOL)TRUE) != MtrWel_VoltSatisfy))
                    {
                      Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                        enWelStopCause_EN_WelStop_VoltageError;
                      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                        Appl_DrComfort_CtrlModel_IN_CommonInactive;
                    }
                    else
                    {
                      /* ����С�ģʽ����״̬ */
                      if (enNapMode_EN_NapMode_Open == MtrWel_NapMode)
                      {
                        Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                          enWelStopCause_EN_WelStop_NapMode;
                        Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                          Appl_DrComfort_CtrlModel_IN_CommonInactive;
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
    break;

   case Appl_DrComfort_CtrlModel_IN_CommonInactive:
    /* ӭ��ʹ�� && �������ת���� && ������̵���ճ������
       && �޿�����ת���� && �޿����̵���ճ������&& ��busoff����
       && PN�� && ����������ѧϰ &&�޸����ȼ��˶� && ��ѹ���� && ������С�ģʽ����״̬ */
    if ((((BOOL)TRUE) == *ComfortOpenFlag) && (((BOOL)FALSE) ==
         MtrWel_LengthLockSts) && (((BOOL)FALSE) == MtrWel_LengthRelayFaultSts) &&
        (((BOOL)FALSE) == MtrWel_BackLockSts) && (((BOOL)FALSE) ==
         MtrWel_BackRelayFaultSts) && (((BOOL)FALSE) == MtrWel_BusoffFlag) &&
        (((BOOL)TRUE) == *Gear_PN_Flag) && (((BOOL)TRUE) == *SeatLearnResult) &&
        (enSeatMotorRunType_EN_ComfortEnable >= MtrWel_CurrentMoveType) &&
        (((BOOL)FALSE) == MtrWel_0x28E_BDCLostFlag) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == MtrWel_VoltMode) && (((BOOL)TRUE) ==
         MtrWel_VoltSatisfy) && (enNapMode_EN_NapMode_Open != MtrWel_NapMode))
    {
      Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
        enWelStopCause_EN_WelStop_NULL;
      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
        Appl_DrComfort_CtrlModel_IN_CommonActive;
    }
    break;

   default:
    /* ӭ��ʹ�� && �������ת���� && ������̵���ճ������
       && �޿�����ת���� && �޿����̵���ճ������&& ��busoff����
       && PN�� && ����������ѧϰ &&�޸����ȼ��˶� && ��ѹ���� && ������С�ģʽ����״̬ */
    if ((((BOOL)TRUE) == *ComfortOpenFlag) && (((BOOL)FALSE) ==
         MtrWel_LengthLockSts) && (((BOOL)FALSE) == MtrWel_LengthRelayFaultSts) &&
        (((BOOL)FALSE) == MtrWel_BackLockSts) && (((BOOL)FALSE) ==
         MtrWel_BackRelayFaultSts) && (((BOOL)FALSE) == MtrWel_BusoffFlag) &&
        (((BOOL)TRUE) == *Gear_PN_Flag) && (((BOOL)TRUE) == *SeatLearnResult) &&
        (enSeatMotorRunType_EN_ComfortEnable >= MtrWel_CurrentMoveType) &&
        (((BOOL)FALSE) == MtrWel_0x28E_BDCLostFlag) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == MtrWel_VoltMode) && (((BOOL)TRUE) ==
         MtrWel_VoltSatisfy) && (enNapMode_EN_NapMode_Open != MtrWel_NapMode))
    {
      Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
        enWelStopCause_EN_WelStop_NULL;
      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
        Appl_DrComfort_CtrlModel_IN_CommonActive;
    }
    else
    {
      /* ӭ������ */
      if (((BOOL)TRUE) != *ComfortOpenFlag)
      {
        /* Set_WelcomeUpdatePosiFlag(TRUE); */
        Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
          enWelStopCause_EN_WelStop_PRM;
        Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
          Appl_DrComfort_CtrlModel_IN_CommonInactive;
      }
      else
      {
        /* ������򿿱���ת���� */
        if ((((BOOL)FALSE) != MtrWel_LengthLockSts) || (((BOOL)FALSE) !=
             MtrWel_BackLockSts))
        {
          /* Set_WelcomeUpdatePosiFlag(TRUE); */
          Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
            enWelStopCause_EN_WelStop_LockFault;
          Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
            Appl_DrComfort_CtrlModel_IN_CommonInactive;
        }
        else
        {
          /* ��������򿿱��̵������� */
          if ((((BOOL)FALSE) != MtrWel_LengthRelayFaultSts) || (((BOOL)FALSE) !=
               MtrWel_BackRelayFaultSts))
          {
            Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
              enWelStopCause_EN_WelStop_RelayFault;
            Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
              Appl_DrComfort_CtrlModel_IN_CommonInactive;
          }
          else
          {
            /* ��busoff���� */
            if (((BOOL)FALSE) != MtrWel_BusoffFlag)
            {
              Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                enWelStopCause_EN_WelStop_Busoff;
              Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                Appl_DrComfort_CtrlModel_IN_CommonInactive;
            }
            else
            {
              /* ��PN�� */
              if (((BOOL)TRUE) != *Gear_PN_Flag)
              {
                Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                  enWelStopCause_EN_WelStop_enNotGearPN;
                Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                  Appl_DrComfort_CtrlModel_IN_CommonInactive;
              }
              else
              {
                /* ����򿿱�δѧϰ */
                if (((BOOL)TRUE) != *SeatLearnResult)
                {
                  /* Set_WelcomeUpdatePosiFlag(TRUE); */
                  Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                    enWelStopCause_EN_WelStop_enNotLearn;
                  Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                    Appl_DrComfort_CtrlModel_IN_CommonInactive;
                }
                else
                {
                  /* �и�����ӭ���˶������� */
                  if (enSeatMotorRunType_EN_ComfortEnable <
                      MtrWel_CurrentMoveType)
                  {
                    /* Set_WelcomeUpdatePosiFlag(TRUE); */
                    Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                      enWelStopCause_EN_WelStop_OtherMove;
                    Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                      Appl_DrComfort_CtrlModel_IN_CommonInactive;
                  }
                  else
                  {
                    /* ���źŶ�ʧ */
                    if (((BOOL)TRUE) == MtrWel_0x28E_BDCLostFlag)
                    {
                      Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                        enWelStopCause_EN_WelStop_enBDCDoorLost;
                      Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                        Appl_DrComfort_CtrlModel_IN_CommonInactive;
                    }
                    else
                    {
                      /* ��ѹ������ģʽ */
                      if ((enFinalPowerMode_EN_NORMAL_VOLT != MtrWel_VoltMode) ||
                          (((BOOL)TRUE) != MtrWel_VoltSatisfy))
                      {
                        Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                          enWelStopCause_EN_WelStop_VoltageError;
                        Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                          Appl_DrComfort_CtrlModel_IN_CommonInactive;
                      }
                      else
                      {
                        /* ����С�ģʽ����״̬ */
                        if (enNapMode_EN_NapMode_Open == MtrWel_NapMode)
                        {
                          Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
                            enWelStopCause_EN_WelStop_NapMode;
                          Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
                            Appl_DrComfort_CtrlModel_IN_CommonInactive;
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
    break;
  }
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrComfort_CtrlModel_UpDataInputInfo_Init(void)
{
  Appl_DrComfort_CtrlModel_DW.is_More =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.is_active_c2_Appl_DrComfort_CtrlModel = 0U;
  Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = 0U;
  Appl_DrComfort_CtrlModel_DW.is_active_c6_Appl_DrComfort_CtrlModel = 0U;
  Appl_DrComfort_CtrlModel_DW.is_c6_Appl_DrComfort_CtrlModel =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.is_Configurable =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.is_active_c11_Appl_DrComfort_CtrlModel = 0U;
  Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.InitTimer = 0U;
  Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = 0U;
  Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.is_DoorSts =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.is_BackwardTriggerCondition =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.temporalCounter_i1 = 0U;
  Appl_DrComfort_CtrlModel_DW.is_ForwardTriggercondition =
    Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_DrComfort_CtrlModel_DW.temporalCounter_i2 = 0U;
  Appl_DrComfort_CtrlModel_DW.is_active_c7_Appl_DrComfort_CtrlModel = 0U;
  Appl_DrComfort_CtrlModel_DW.WaitTimeCnt = 0U;
  Appl_DrComfort_CtrlModel_DW.LocalDoorSts = 0U;
  Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = 0U;
  Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = 0U;
  Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
    enWelStopCause_EN_WelStop_VoltageError;
  Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start =
    Appl_DrComfort_CtrlModel_DW.LocalDoorSts;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrComfort_CtrlModel_UpDataInputInfo(void)
{
  INT16U rtb_BackMoreThanHall;
  INT8U Gear_PN_Flag;
  INT8U ComfortOpenFlag;
  INT8U LocalDoorSts_prev;
  BOOL SeatLearnResult;
  INT8U MtrWel_LengthCmd_prev;
  INT32S tmp;
  Appl_DrComfort_CtrlModel_RTE();
  if (Appl_DrComfort_CtrlModel_DW.is_active_c2_Appl_DrComfort_CtrlModel == 0U)
  {
    Appl_DrComfort_CtrlModel_DW.is_active_c2_Appl_DrComfort_CtrlModel = 1U;
    tmp = (INT32S)((INT32U)MtrWel_BackMotorSize >> 2) + MtrWel_BackStopPosi;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    rtb_BackMoreThanHall = (INT16U)tmp;
    Appl_DrComfort_CtrlModel_DW.is_More = Appl_DrComfort_CtrlModel_IN_Init_b;
    Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);
  }
  else
  {
    tmp = (INT32S)((INT32U)MtrWel_BackMotorSize >> 2) + MtrWel_BackStopPosi;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    rtb_BackMoreThanHall = (INT16U)tmp;
    if (Appl_DrComfort_CtrlModel_DW.is_More ==
        Appl_DrComfort_CtrlModel_IN_Init_b)
    {
      Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);

      /*  ���ھ�ǰֹ��60��λ��  */
      if (MtrWel_BackHallPosi > (INT16U)tmp)
      {
        Appl_DrComfort_CtrlModel_DW.is_More =
          Appl_DrComfort_CtrlModel_IN_MoreThan;
        Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)TRUE);

      /*  С�ڵ��ھ�ǰֹ��60��λ��  */
      if (MtrWel_BackHallPosi <= (INT16U)tmp)
      {
        Appl_DrComfort_CtrlModel_DW.is_More = Appl_DrComfort_CtrlModel_IN_Init_b;
        Appl_DrComfort_CtrlModel_B.BackMoreThanFlg = ((BOOL)FALSE);
      }
    }
  }

  Appl_DrComfort_CtrlModel_B.BackMoreThanHall = (INT16U)(rtb_BackMoreThanHall +
    40U);
  if (Appl_DrComfort_CtrlModel_DW.is_active_c6_Appl_DrComfort_CtrlModel == 0U)
  {
    Appl_DrComfort_CtrlModel_DW.is_active_c6_Appl_DrComfort_CtrlModel = 1U;
    Appl_DrComfort_CtrlModel_DW.is_c6_Appl_DrComfort_CtrlModel =
      Appl_DrComfort_CtrlModel_IN_Gear_Not_PN;
    Gear_PN_Flag = ((BOOL)FALSE);
  }
  else if (Appl_DrComfort_CtrlModel_DW.is_c6_Appl_DrComfort_CtrlModel ==
           Appl_DrComfort_CtrlModel_IN_Gear_Not_PN)
  {
    Gear_PN_Flag = ((BOOL)FALSE);

    /* �ͳ����ĵ��� || PN������ */
    if ((((((BOOL)TRUE) == MtrWel_0x238_GearLostFlag) || (0 ==
           MtrWel_0x238_TCU_GearSelDisp) || (6 == MtrWel_0x238_TCU_GearSelDisp))
         && (((BOOL)FALSE) == MtrWel_P20_PHEV_EngineCfg)) || (((((BOOL)TRUE) ==
           MtrWel_0x26E_GearSelLostFlag) || (0 == MtrWel_0x26E_VCU_GearSelDisp) ||
          (6 == MtrWel_0x26E_VCU_GearSelDisp)) && (((BOOL)FALSE) !=
          MtrWel_P20_PHEV_EngineCfg)))
    {
      Appl_DrComfort_CtrlModel_DW.is_c6_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_Gear_PN;
      Gear_PN_Flag = ((BOOL)TRUE);
    }
    else
    {
      /* �糵���ĵ��� || PN������ */
    }
  }
  else
  {
    Gear_PN_Flag = ((BOOL)TRUE);

    /* �ͳ��������� && ��PN������ */
    if ((((5 == MtrWel_0x238_TCU_GearSelDisp) || (7 ==
           MtrWel_0x238_TCU_GearSelDisp) || (0xF == MtrWel_0x238_TCU_GearSelDisp))
         && (((BOOL)FALSE) == MtrWel_P20_PHEV_EngineCfg)) || (((5 ==
           MtrWel_0x26E_VCU_GearSelDisp) || (7 == MtrWel_0x26E_VCU_GearSelDisp) ||
          (0xF == MtrWel_0x26E_VCU_GearSelDisp)) && (((BOOL)FALSE) !=
          MtrWel_P20_PHEV_EngineCfg)))
    {
      Appl_DrComfort_CtrlModel_DW.is_c6_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_Gear_Not_PN;
      Gear_PN_Flag = ((BOOL)FALSE);
    }
    else
    {
      /* �糵���ĵ��� || ��PN������ */
    }
  }

  if (Appl_DrComfort_CtrlModel_DW.is_active_c11_Appl_DrComfort_CtrlModel == 0U)
  {
    Appl_DrComfort_CtrlModel_DW.is_active_c11_Appl_DrComfort_CtrlModel = 1U;
    Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
      Appl_DrComfort_CtrlModel_IN_Init_h;
    Appl_DrComfort_CtrlModel_DW.InitTimer = 1U;
    ComfortOpenFlag = ((BOOL)FALSE);
    Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
  }
  else if (Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel ==
           Appl_DrComfort_CtrlModel_IN_Configurable)
  {
    /* �ָ��������� */
    if (((BOOL)TRUE) == MtrWel_GetRecoverDefaultFlag)
    {
      Appl_DrComfort_CtrlModel_DW.is_Configurable =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
      Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
      Appl_DrComfort_CtrlModel_B.in = ((BOOL)TRUE);
      Appl_DrComfort_CtrlModel_SetComfortPrm();
      Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_Init_h;
      Appl_DrComfort_CtrlModel_DW.InitTimer = 1U;
      ComfortOpenFlag = ((BOOL)FALSE);
      Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
    }
    else
    {
      /* ((ӭ������ || ���η�6&&12����� || ��ѹ������ģʽ)&&P20����)
         || ��P20���� */
      if ((enVehTypePrm_enP20 != MtrWel_VehiclePrm) || ((((BOOL)TRUE) !=
            MtrWel_WelcomeEnable) || ((enDrAdjustEnable_EN_DrSixWayMotor !=
             MtrWel_AdjustEnable) && (enDrAdjustEnable_EN_DrTwelveWayMotor !=
             MtrWel_AdjustEnable)) || (enFinalPowerMode_EN_NORMAL_VOLT !=
            MtrWel_VoltMode)))
      {
        Appl_DrComfort_CtrlModel_DW.is_Configurable =
          Appl_DrComfort_CtrlModel_IN_NO_ACTIVE_CHILD_c;
        Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
          Appl_DrComfort_CtrlModel_IN_Init_h;
        Appl_DrComfort_CtrlModel_DW.InitTimer = 1U;
        ComfortOpenFlag = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
      }
      else if (Appl_DrComfort_CtrlModel_DW.is_Configurable ==
               Appl_DrComfort_CtrlModel_IN_Disable)
      {
        ComfortOpenFlag = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);

        /* ��IVI_St_FLSeatmeet=0x1:Openʱ�����ε������ʽ���ʹ�� */
        if (1 == MtrWel_0x351_IVI_St_FLSeatmeet)
        {
          Appl_DrComfort_CtrlModel_DW.is_Configurable =
            Appl_DrComfort_CtrlModel_IN_Enable;
          ComfortOpenFlag = ((BOOL)TRUE);

          /* *ComfortOpenMsg ���ķ��ͱ���****************ComfortOpenFlagӭ�������Ƿ���������PC1ӭ�����ܴ��ڿ���״̬ */
          Appl_DrComfort_CtrlModel_B.in = ((BOOL)TRUE);
          Appl_DrComfort_CtrlModel_SetComfortPrm();
          Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
        }
      }
      else
      {
        ComfortOpenFlag = ((BOOL)TRUE);
        Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);

        /* ��IVI_St_FLSeatmeet=0x2:Closeʱ�����ε������ʽ������ */
        if (2 == MtrWel_0x351_IVI_St_FLSeatmeet)
        {
          Appl_DrComfort_CtrlModel_DW.is_Configurable =
            Appl_DrComfort_CtrlModel_IN_Disable;
          ComfortOpenFlag = ((BOOL)FALSE);
          Appl_DrComfort_CtrlModel_B.in = ((BOOL)FALSE);
          Appl_DrComfort_CtrlModel_SetComfortPrm();
          Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);
        }
      }
    }
  }
  else
  {
    ComfortOpenFlag = ((BOOL)FALSE);
    Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);

    /* EEPROMӭ��Ϊʹ��&&���ε綯����&&P20����&&��ʼ�����&&������ѹ */
    if ((((BOOL)TRUE) == MtrWel_WelcomeEnable) &&
        ((enDrAdjustEnable_EN_DrSixWayMotor == MtrWel_AdjustEnable) ||
         (enDrAdjustEnable_EN_DrTwelveWayMotor == MtrWel_AdjustEnable)) &&
        (enVehTypePrm_enP20 == MtrWel_VehiclePrm) &&
        (Appl_DrComfort_CtrlModel_DW.InitTimer > ((INT8U)D_InitDelayTime)) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == MtrWel_VoltMode))
    {
      Appl_DrComfort_CtrlModel_DW.InitTimer = 0U;
      Appl_DrComfort_CtrlModel_DW.is_c11_Appl_DrComfort_CtrlModel =
        Appl_DrComfort_CtrlModel_IN_Configurable;
      if (MtrWel_WelcomeSwitch == 1)
      {
        Appl_DrComfort_CtrlModel_DW.is_Configurable =
          Appl_DrComfort_CtrlModel_IN_Enable;
        ComfortOpenFlag = ((BOOL)TRUE);

        /* *ComfortOpenMsg ���ķ��ͱ���****************ComfortOpenFlagӭ�������Ƿ���������PC1ӭ�����ܴ��ڿ���״̬ */
        Appl_DrComfort_CtrlModel_B.in = ((BOOL)TRUE);
        Appl_DrComfort_CtrlModel_SetComfortPrm();
        Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)TRUE);
      }
      else
      {
        Appl_DrComfort_CtrlModel_DW.is_Configurable =
          Appl_DrComfort_CtrlModel_IN_Disable;
        ComfortOpenFlag = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_B.in = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_SetComfortPrm();
        Appl_DrComfort_CtrlModel_B.ComfortOpenMsg = ((BOOL)FALSE);
      }
    }
    else
    {
      tmp = Appl_DrComfort_CtrlModel_DW.InitTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_DrComfort_CtrlModel_DW.InitTimer = (INT8U)tmp;
    }
  }

  SeatLearnResult = ((MtrWel_LengthStopPosi != 0) && (MtrWel_LengthStopPosi !=
    65535) && ((MtrWel_BackStopPosi != 0) && (MtrWel_BackStopPosi != 65535)));
  if (Appl_DrComfort_CtrlModel_DW.temporalCounter_i1 < 3U)
  {
    Appl_DrComfort_CtrlModel_DW.temporalCounter_i1++;
  }

  if (Appl_DrComfort_CtrlModel_DW.temporalCounter_i2 < 3U)
  {
    Appl_DrComfort_CtrlModel_DW.temporalCounter_i2++;
  }

  MtrWel_LengthCmd_prev = Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start;
  Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start = MtrWel_LengthCmd;
  LocalDoorSts_prev = Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start;
  Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start =
    Appl_DrComfort_CtrlModel_DW.LocalDoorSts;
  if (Appl_DrComfort_CtrlModel_DW.is_active_c7_Appl_DrComfort_CtrlModel == 0U)
  {
    Appl_DrComfort_CtrlModel_DW.is_active_c7_Appl_DrComfort_CtrlModel = 1U;
    Appl_DrComfort_CtrlModel_DW.is_CommonCondition =
      Appl_DrComfort_CtrlModel_IN_CommonInit;
    Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
      enWelStopCause_EN_WelStop_VoltageError;
    Appl_DrComfort_CtrlModel_DW.is_DoorSts =
      Appl_DrComfort_CtrlModel_IN_DoorInit;
    Appl_DrComfort_CtrlModel_DW.WaitTimeCnt = 0U;
    Appl_DrComfort_CtrlModel_DW.LocalDoorSts = (INT8U)0xFF;

    /*  ��������仯 �ҷ����ʹ��ܵ��� ��Ҫ��������λ��  */
    if ((enSeatMotorRunType_EN_ComfortEnable != MtrWel_CurrentMoveType) &&
        (enSeatMotorRunType_EN_NULL != MtrWel_CurrentMoveType) &&
        (((MtrWel_LengthCmd !=
           Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start) &&
          (Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start == 1)) ||
         ((MtrWel_LengthCmd !=
           Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start) &&
          (Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start == 2))))
    {
      Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
      Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
    }
  }
  else
  {
    Appl_DrComfort_CtrlModel_CommonCondition(&Gear_PN_Flag, &ComfortOpenFlag,
      &SeatLearnResult);
    if (Appl_DrComfort_CtrlModel_DW.is_DoorSts ==
        Appl_DrComfort_CtrlModel_IN_DoorInit)
    {
      /*  �ȴ���ȡe2p����  */
      if (Appl_DrComfort_CtrlModel_DW.WaitTimeCnt > 20)
      {
        Appl_DrComfort_CtrlModel_DW.WaitTimeCnt = 0U;
        Appl_DrComfort_CtrlModel_Get_DoorSts();
        Appl_DrComfort_CtrlModel_DW.LocalDoorSts =
          Appl_DrComfort_CtrlModel_B.MtrWel_WelcomeSwitch_p;
        Appl_DrComfort_CtrlModel_DW.is_DoorSts =
          Appl_DrComfort_CtrlModel_IN_DoorSts;
        Appl_DrComfort_CtrlModel_DW.is_BackwardTriggerCondition =
          Appl_DrComfort_CtrlModel_IN_BWInactive;
        Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);
        Appl_DrComfort_CtrlModel_DW.is_ForwardTriggercondition =
          Appl_DrComfort_CtrlModel_IN_FWInactive;
        Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);
      }
      else
      {
        tmp = Appl_DrComfort_CtrlModel_DW.WaitTimeCnt + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_DrComfort_CtrlModel_DW.WaitTimeCnt = (INT8U)tmp;
        Appl_DrComfort_CtrlModel_Get_DoorSts();
        Appl_DrComfort_CtrlModel_DW.LocalDoorSts =
          Appl_DrComfort_CtrlModel_B.MtrWel_WelcomeSwitch_p;
      }
    }
    else
    {
      Appl_DrComfort_CtrlModel_DW.LocalDoorSts = MtrWel_BDC_FLDoorSts;
      Appl_DrComfort_CtrlModel_Get_DoorSts();
      if (Appl_DrComfort_CtrlModel_DW.is_BackwardTriggerCondition ==
          Appl_DrComfort_CtrlModel_IN_BWActive)
      {
        Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)TRUE);

        /* 2���������� */
        if (Appl_DrComfort_CtrlModel_DW.temporalCounter_i1 >= 2)
        {
          Appl_DrComfort_CtrlModel_DW.is_BackwardTriggerCondition =
            Appl_DrComfort_CtrlModel_IN_BWInactive;
          Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);
        }
      }
      else
      {
        Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)FALSE);

        /*  ӭ����������
           C5����ǰ����״̬�ɹرա��򿪣�BDC_FLDoorSts=0x0:Close��0x1:Open����ǰ�������� */
        if ((LocalDoorSts_prev != Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start)
            && (Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start == ((INT8U)D_OPEN))
            && (Appl_DrComfort_CtrlModel_B.MtrWel_WelcomeSwitch_p <= ((INT8U)
              D_OPEN)))
        {
          Appl_DrComfort_CtrlModel_DW.is_BackwardTriggerCondition =
            Appl_DrComfort_CtrlModel_IN_BWActive;
          Appl_DrComfort_CtrlModel_DW.temporalCounter_i1 = 0U;
          Appl_DrComfort_CtrlModel_B.BackwardTriggerCondition = ((BOOL)TRUE);
        }
      }

      if (Appl_DrComfort_CtrlModel_DW.is_ForwardTriggercondition ==
          Appl_DrComfort_CtrlModel_IN_FWActive)
      {
        Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)TRUE);

        /* 2���������� */
        if (Appl_DrComfort_CtrlModel_DW.temporalCounter_i2 >= 2)
        {
          Appl_DrComfort_CtrlModel_DW.is_ForwardTriggercondition =
            Appl_DrComfort_CtrlModel_IN_FWInactive;
          Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);
        }
      }
      else
      {
        Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)FALSE);

        /*  ӭ��ǰ������
           C6����ǰ����״̬�ɴ򿪡��رգ�BDC_FLDoorSts=0x1:Open��0x0:Close����ǰ�������� */
        if ((LocalDoorSts_prev != Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start)
            && (Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start == ((INT8U)
              D_CLOSE)) && (Appl_DrComfort_CtrlModel_B.MtrWel_WelcomeSwitch_p <=
                            ((INT8U)D_OPEN)))
        {
          Appl_DrComfort_CtrlModel_DW.is_ForwardTriggercondition =
            Appl_DrComfort_CtrlModel_IN_FWActive;
          Appl_DrComfort_CtrlModel_DW.temporalCounter_i2 = 0U;
          Appl_DrComfort_CtrlModel_B.ForwardTriggerCondition = ((BOOL)TRUE);
        }
      }

      /*  ��״̬�仯 ������  */
      if ((LocalDoorSts_prev != Appl_DrComfort_CtrlModel_DW.LocalDoorSts_start) &&
          (Appl_DrComfort_CtrlModel_DW.LocalDoorSts <= ((INT8U)D_OPEN)))
      {
        Appl_DrComfort_CtrlModel_B.In1_j =
          Appl_DrComfort_CtrlModel_DW.LocalDoorSts;
        Srvl_SetMemIndexDataU8(EN_MemIndex_DrDoorSts,
          Appl_DrComfort_CtrlModel_B.In1_j);
      }
    }

    /*  ��������仯 �ҷ����ʹ��ܵ��� ��Ҫ��������λ��  */
    if ((enSeatMotorRunType_EN_ComfortEnable != MtrWel_CurrentMoveType) &&
        (enSeatMotorRunType_EN_NULL != MtrWel_CurrentMoveType) &&
        (((MtrWel_LengthCmd_prev !=
           Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start) &&
          (Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start == 1)) ||
         ((MtrWel_LengthCmd_prev !=
           Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start) &&
          (Appl_DrComfort_CtrlModel_DW.MtrWel_LengthCmd_start == 2))))
    {
      Appl_DrComfort_CtrlModel_B.In1 = ((BOOL)TRUE);
      Appl_DrComfort_CtrlMod_Set_WelcomeUpdatePosiFlag_d();
    }
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_DrComfort_CtrlModel_UpDataOutputInfo(void)
{
  CanTx_0x3B2_DSM_St_FLSeatmeet(Appl_DrComfort_CtrlModel_B.DataTypeConversion);
  Rte_SetVfb_DrWelBackReqPosi(Appl_DrComfort_CtrlModel_B.WelcomeBackReqPosi);
  Rte_SetVfb_DrWelLengthReqCMD(Appl_DrComfort_CtrlModel_B.WelcomeReqCMD);
  Rte_SetVfb_DrWelLengthReqPosi(Appl_DrComfort_CtrlModel_B.WelcomeReqPosi);
  Rte_SetVfb_DrWelcomeRunSts(Appl_DrComfort_CtrlModel_B.WelcomeRunStatus);
  Rte_SetVfb_DrWelcomeStopReason(Appl_DrComfort_CtrlModel_B.WelcomeStopReasonOut);
}

/* Model step function */
void Appl_DrComfort_CtrlModel_step(void)
{
  Appl_DrComfort_CtrlModel_UpDataInputInfo();
  Appl_DrComfort_CtrlModel_LogicCtrl();
  Appl_DrComfort_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_DrComfort_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_DrComfort_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_DrComfort_CtrlModel_B), 0,
                sizeof(B_Appl_DrComfort_CtrlModel_T));

  {
    Appl_DrComfort_CtrlModel_B.WelcomeStopReason =
      enWelStopCause_EN_WelStop_NULL;
  }

  /* exported global signals */
  MtrWel_WelcomeStatus = enWelcomeSts_EN_NULL;
  MtrWel_VehiclePrm = enVehTypePrm_enP20;
  MtrWel_CurrentMoveType = enSeatMotorRunType_EN_NULL;
  MtrWel_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  MtrWel_NapMode = enNapMode_EN_NapMode_NULL;
  MtrWel_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  MtrWel_AdjustEnable = enDrAdjustEnable_EN_DrManual;
  MtrWel_BackHallPosi = ((INT16U)0U);
  MtrWel_BackMotorSize = ((INT16U)0U);
  MtrWel_BackStopPosi = ((INT16U)0U);
  MtrWel_LengthBWTargetPosi = ((INT16U)0U);
  MtrWel_LengthFWTargetPosi = ((INT16U)0U);
  MtrWel_LengthHallPosi = ((INT16U)0U);
  MtrWel_LengthStopPosi = ((INT16U)0U);
  MtrWel_0x238_GearLostFlag = ((INT8U)0U);
  MtrWel_0x238_TCU_GearSelDisp = ((INT8U)0U);
  MtrWel_0x26E_GearSelLostFlag = ((INT8U)0U);
  MtrWel_0x26E_VCU_GearSelDisp = ((INT8U)0U);
  MtrWel_0x28E_BDCLostFlag = ((INT8U)0U);
  MtrWel_0x351_IVI_St_FLSeatmeet = ((INT8U)0U);
  MtrWel_BDC_FLDoorSts = ((INT8U)0U);
  MtrWel_BackHallFaultSts = ((INT8U)0U);
  MtrWel_BackLockSts = ((INT8U)0U);
  MtrWel_BackRelayFaultSts = ((INT8U)0U);
  MtrWel_BusoffFlag = ((INT8U)0U);
  MtrWel_GetRecoverDefaultFlag = ((INT8U)0U);
  MtrWel_LengthCmd = ((INT8U)0U);
  MtrWel_LengthHallFaultSts = ((INT8U)0U);
  MtrWel_LengthLockSts = ((INT8U)0U);
  MtrWel_LengthRelayFaultSts = ((INT8U)0U);
  MtrWel_P20_PHEV_EngineCfg = ((INT8U)0U);
  MtrWel_UpdatePosiFlag = ((INT8U)0U);
  MtrWel_VoltSatisfy = ((INT8U)0U);
  MtrWel_WelcomeEnable = ((INT8U)0U);
  MtrWel_WelcomeSwitch = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_DrComfort_CtrlModel_DW, 0,
                sizeof(DW_Appl_DrComfort_CtrlModel_T));
  Appl_DrComfort_CtrlModel_UpDataInputInfo_Init();
  Appl_DrComfort_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
