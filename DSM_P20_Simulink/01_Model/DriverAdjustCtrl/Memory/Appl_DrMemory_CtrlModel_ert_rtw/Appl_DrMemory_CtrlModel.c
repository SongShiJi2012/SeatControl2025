/*
 * File: Appl_DrMemory_CtrlModel.c
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

#include "Appl_DrMemory_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_DRMEM_SPEED_5
#error The variable for the parameter "D_DRMEM_SPEED_5" is not defined
#endif

#ifndef D_ToleranceDistance
#error The variable for the parameter "D_ToleranceDistance" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

/* Named constants for Chart: '<S5>/MemoryCall' */
#define Appl_DrMemory_CtrlMod_IN_MemoryCallDefaultFeedback ((INT8U)1U)
#define Appl_DrMemory_CtrlMode_IN_MemoryCallResultFeedback ((INT8U)2U)
#define Appl_DrMemory_CtrlModel_IN_Fail ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_MemoryCallActive ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_MemoryCallInactive ((INT8U)2U)
#define Appl_DrMemory_CtrlModel_IN_MemoryCallMotorStop ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_MemoryCallRun ((INT8U)2U)
#define Appl_DrMemory_CtrlModel_IN_MessageSendFinish ((INT8U)2U)
#define Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e ((INT8U)0U)
#define Appl_DrMemory_CtrlModel_IN_Succeed ((INT8U)3U)
#define Appl_DrMemory_CtrlModel_IN_Wait ((INT8U)4U)

/* Named constants for Chart: '<S5>/MemoryRemindLogic' */
#define Appl_DrMemory_CtrlModel_IN_PositionChange1 ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_PositionNoChange1 ((INT8U)2U)

/* Named constants for Chart: '<S5>/MemorySetLogic' */
#define Appl_DrMemory_CtrlModel_IN_MemorySetActive ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_MemorySetInactive ((INT8U)2U)

/* Named constants for Chart: '<S46>/CallMemory' */
#define Appl_DrMemory_CtrlModel_IN_AcquireMemory1stPosi ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_AcquireMemory2ndPosi ((INT8U)2U)
#define Appl_DrMemory_CtrlModel_IN_AcquireMemory3rdPosi ((INT8U)3U)
#define Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i ((INT8U)0U)
#define Appl_DrMemory_CtrlModel_IN_NoneMemoryCall ((INT8U)4U)

/* Named constants for Chart: '<S47>/HmiDeal' */
#define Appl_DrMemory_CtrlModel_IN_ButtonConflict ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_NoButtonConflict ((INT8U)2U)

/* Named constants for Chart: '<S48>/MemoryRemindPrecondition' */
#define Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_PreconditionSatisfied ((INT8U)2U)

/* Named constants for Chart: '<S50>/SpeedDeal' */
#define Appl_DrMemory_CtrlModel_IN_LessThan5 ((INT8U)1U)
#define Appl_DrMemory_CtrlModel_IN_MoreThan5 ((INT8U)2U)

/* Exported block signals */
enSeatMotorRunType DrMem_AnyoneRelayFaultSts;/* '<S45>/DrMem_AnyoneRelayFaultSts'
                                              * ������һ�̵���ճ�����ϱ�־
                                              */
enSeatAutoRunSts DrMem_BackAutoRunFlag;/* '<S45>/DrMem_BackAutoRunFlag'
                                        * ���ݿ����Զ����б�־λ
                                        */
enSeatAutoRunSts DrMem_FrontAutoRunFlag;/* '<S45>/DrMem_FrontAutoRunFlag'
                                         * ����ǰ���Ƕ��Զ����б�־λ
                                         */
enSeatAutoRunSts DrMem_HeightAutoRunFlag;/* '<S45>/DrMem_HeightAutoRunFlag'
                                          * ���ݸ߶��Զ����б�־λ
                                          */
enSeatAutoRunSts DrMem_LengthAutoRunFlag;/* '<S45>/DrMem_LengthAutoRunFlag'
                                          * ���������Զ����б�־λ
                                          */
enPowerModeSts DrMem_PowerMode;        /* '<S45>/DrMem_PowerMode'
                                        * ������Դ��λ
                                        */
enNapMode DrMem_NapMode;               /* '<S45>/DrMem_NapMode'
                                        * С�ģʽ
                                        */
enMemSet DrMem_IVI_FLSeatMemSet1;      /* '<S45>/DrMem_IVI_FLSeatMemSet1'
                                        * ��������1
                                        */
enMemSet DrMem_IVI_FLSeatMemSet2;      /* '<S45>/DrMem_IVI_FLSeatMemSet2'
                                        * ��������2
                                        */
enMemSet DrMem_IVI_FLSeatMemSet3;      /* '<S45>/DrMem_IVI_FLSeatMemSet3'
                                        * ��������3
                                        */
enFinalPowerMode DrMem_VoltMode;       /* '<S45>/DrMem_VoltMode'
                                        * ������ѹģʽ
                                        */
INT16U DrMem_BackHallPosi;             /* '<S45>/DrMem_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
INT16U DrMem_BackMem1;                 /* '<S45>/DrMem_BackMem1'
                                        * ���ݼ���1��������λ��
                                        */
INT16U DrMem_BackMem2;                 /* '<S45>/DrMem_BackMem2'
                                        * ���ݼ���2��������λ��
                                        */
INT16U DrMem_BackMem3;                 /* '<S45>/DrMem_BackMem3'
                                        * ���ݼ���3��������λ��
                                        */
INT16U DrMem_FrontHallPosi;            /* '<S45>/DrMem_FrontHallPosi'
                                        * ����ǰ���Ƕȵ�ǰ����λ��
                                        */
INT16U DrMem_FrontMem1;                /* '<S45>/DrMem_FrontMem1'
                                        * ���ݼ���1ǰ���ǶȻ���λ��
                                        */
INT16U DrMem_FrontMem2;                /* '<S45>/DrMem_FrontMem2'
                                        * ���ݼ���2ǰ���ǶȻ���λ��
                                        */
INT16U DrMem_FrontMem3;                /* '<S45>/DrMem_FrontMem3'
                                        * ���ݼ���3ǰ���ǶȻ���λ��
                                        */
INT16U DrMem_GetRecoverDefaultFlag;    /* '<S45>/DrMem_GetRecoverDefaultFlag'
                                        *  �ָ���������
                                        */
INT16U DrMem_HeightHallPosi;           /* '<S45>/DrMem_HeightHallPosi'
                                        * ���ݸ߶ȵ�ǰ����λ��
                                        */
INT16U DrMem_HeightMem1;               /* '<S45>/DrMem_HeightMem1'
                                        * ���ݼ���1�߶Ȼ���λ��
                                        */
INT16U DrMem_HeightMem2;               /* '<S45>/DrMem_HeightMem2'
                                        * ���ݼ���2�߶Ȼ���λ��
                                        */
INT16U DrMem_HeightMem3;               /* '<S45>/DrMem_HeightMem3'
                                        * ���ݼ���3�߶Ȼ���λ��
                                        */
INT16U DrMem_LengthHallPosi;           /* '<S45>/DrMem_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
INT16U DrMem_LengthMem1;               /* '<S45>/DrMem_LengthMem1'
                                        * ���ݼ���1�������λ��
                                        */
INT16U DrMem_LengthMem2;               /* '<S45>/DrMem_LengthMem2'
                                        * ���ݼ���2�������λ��
                                        */
INT16U DrMem_LengthMem3;               /* '<S45>/DrMem_LengthMem3'
                                        * ���ݼ���3�������λ��
                                        */
INT16U DrMem_VehicleSpeed;             /* '<S45>/DrMem_VehicleSpeed'
                                        * ����
                                        */
INT8U DrMem_0x284_SpeedLostFlag;       /* '<S45>/DrMem_0x284_SpeedLostFlag'
                                        * 0x284���ĵ��߱�־λ
                                        */
INT8U DrMem_AdjustEnable;              /* '<S45>/DrMem_AdjustEnable'
                                        * �������ε���
                                        */
INT8U DrMem_AnyoneLockFaultSts;        /* '<S45>/DrMem_AnyoneLockFaultSts'
                                        * ������һ�����ת״̬
                                        */
INT8U DrMem_BackLockFault;             /* '<S45>/DrMem_BackLockFault'
                                        * �������ο�����ת
                                        */
INT8U DrMem_BackSwitch;                /* '<S45>/DrMem_BackSwitch'
                                        * ������������
                                        */
INT8U DrMem_CurrentMoveType;           /* '<S45>/DrMem_CurrentMoveType'
                                        * ���ݵ����ǰ�������ͣ�
                                        */
INT8U DrMem_DtcAnyoneHallFaultSts;     /* '<S45>/DrMem_DtcAnyoneHallFaultSts'
                                        * ������һ�����������
                                        */
INT8U DrMem_FLSeatPosMsg;              /* '<S45>/DrMem_FLSeatPosMsg'
                                        * ������ʾ��������
                                        */
INT8U DrMem_FrontLockFault;            /* '<S45>/DrMem_FrontLockFault'
                                        * �����������ж�ת
                                        */
INT8U DrMem_FrontSwitch;               /* '<S45>/DrMem_FrontSwitch'
                                        * ���п�������
                                        */
INT8U DrMem_Gear_PN_FlagOut;           /* '<S45>/DrMem_Gear_PN_FlagOut'
                                        * PN����־λ
                                        */
INT8U DrMem_HeightLockFault;           /* '<S45>/DrMem_HeightLockFault'
                                        * �������θ߶ȶ�ת
                                        */
INT8U DrMem_HeightSwitch;              /* '<S45>/DrMem_HeightSwitch'
                                        * �߶ȿ�������
                                        */
INT8U DrMem_LengthLockFault;           /* '<S45>/DrMem_LengthLockFault'
                                        * �������������ת
                                        */
INT8U DrMem_LengthSwitch;              /* '<S45>/DrMem_LengthSwitch'
                                        * ���򿪹�����
                                        */
INT8U DrMem_MemoryConfig;              /* '<S45>/DrMem_MemoryConfig'
                                        * �������μ���ӭ��ʹ��:
                                        */
INT8U DrMem_SeatLearnResult;           /* '<S45>/DrMem_SeatLearnResult'
                                        * ��������ѧϰ״̬
                                        */
INT8U DrMem_SeatMemory1Valid;          /* '<S45>/DrMem_SeatMemory1Valid'
                                        * ����1λ����Ч��־
                                        */
INT8U DrMem_SeatMemory2Valid;          /* '<S45>/DrMem_SeatMemory2Valid'
                                        * ����2λ����Ч��־
                                        */
INT8U DrMem_SeatMemory3Valid;          /* '<S45>/DrMem_SeatMemory3Valid'
                                        * ����3λ����Ч��־
                                        */
INT8U DrMem_VehicleSpeedValid;         /* '<S45>/DrMem_VehicleSpeedValid'
                                        * ������Ч��
                                        */
INT8U DrMem_VoltSatisfy;               /* '<S45>/DrMem_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ�����
                                        */

/* Block signals (default storage) */
B_Appl_DrMemory_CtrlModel_T Appl_DrMemory_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_DrMemory_CtrlModel_T Appl_DrMemory_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_DrMemory_CtrlModel_T Appl_DrMemory_CtrlModel_M_;
RT_MODEL_Appl_DrMemory_CtrlModel_T *const Appl_DrMemory_CtrlModel_M =
  &Appl_DrMemory_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT8U CAL_DrMem_100MS = 10U;/* ��ʱ100ms */
const volatile INT8U CAL_DrMem_90MS = 50U;/* ��ʱ90ms */
static void Appl_DrMemory_CtrlModel_MemCallWaitFBFunc_Init(enMemCallFb
  *rty_CallFB1, enMemCallFb *rty_CallFB2, enMemCallFb *rty_CallFB3);
static void Appl_DrMemory_CtrlModel_MemCallWaitFBFunc(INT8U rtu_ButtonNum,
  enMemCallFb rtu_FBSts, enMemCallFb *rty_CallFB1, enMemCallFb *rty_CallFB2,
  enMemCallFb *rty_CallFB3);
static void Appl_DrMemory_CtrlModel_PosiCompareFunc_Init(INT8U *rty_Result);
static void Appl_DrMemory_CtrlModel_PosiCompareFunc(INT16U rtu_MemH, INT16U
  rtu_MenL, INT16U rtu_MemB, INT16U rtu_MemF, INT16U rtu_CurrentH, INT16U
  rtu_CurrentL, INT16U rtu_CurrentB, INT16U rtu_CurrentF, INT8U rtu_AdjustEnable,
  INT8U rtu_PosiReq, INT8U *rty_Result);
static void Appl_DrMemory_CtrlModel_SetCanSendEvent(void);
static void Appl_DrMemory_CtrlModel_SetCanMemCall1(void);
static void Appl_DrMemory_CtrlModel_SetCanMemCall2(void);
static void Appl_DrMemory_CtrlModel_GetCanSendEvent(void);
static void Appl_DrMemory_CtrlModel_SetCanMemCall3(void);
static void Appl_DrMemory_CtrlModel_SetCanSendEvent_g(void);
static void Appl_DrMemory_CtrlModel_GetCanSendEvent_b(void);
static void Appl_DrMemory_CtrlModel_SetCanSendFLSeatMemSts(void);
static void Appl_DrMemory_CtrlModel_LogicCtrl_Init(void);
static void Appl_DrMemory_CtrlModel_LogicCtrl(void);
static void Appl_DrMemory_CtrlModel_RTE(void);
static void Appl_DrMemory_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_DrMemory_CtrlModel_UpDataInputInfo(void);
static void Appl_DrMemory_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_DrMemory_CtrlModel_inner_default_Wait(void);
static void Appl_DrMemory_CtrlModel_inner_default_Wait_i(void);

/* System initialize for function-call system: '<S6>/MemCallWaitFBFunc' */
static void Appl_DrMemory_CtrlModel_MemCallWaitFBFunc_Init(enMemCallFb
  *rty_CallFB1, enMemCallFb *rty_CallFB2, enMemCallFb *rty_CallFB3)
{
  *rty_CallFB1 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB2 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB3 = enMemCallFb_EN_MemCallFb_NULL;
}

/* Output and update for function-call system: '<S6>/MemCallWaitFBFunc' */
static void Appl_DrMemory_CtrlModel_MemCallWaitFBFunc(INT8U rtu_ButtonNum,
  enMemCallFb rtu_FBSts, enMemCallFb *rty_CallFB1, enMemCallFb *rty_CallFB2,
  enMemCallFb *rty_CallFB3)
{
  *rty_CallFB1 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB2 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB3 = enMemCallFb_EN_MemCallFb_NULL;

  /*  ����λ��1������  */
  switch (rtu_ButtonNum)
  {
   case 1:
    *rty_CallFB1 = rtu_FBSts;
    break;

   case 2:
    /*  ����λ��2 ������  */
    *rty_CallFB2 = rtu_FBSts;
    break;

   default:
    *rty_CallFB3 = rtu_FBSts;
    break;
  }
}

/* Output and update for function-call system: '<S6>/SetCanSendEvent' */
static void Appl_DrMemory_CtrlModel_SetCanSendEvent(void)
{
  Rte_SetCanEvent_0x3B2(((INT16U)0U));
}

/* Output and update for function-call system: '<S6>/SetCanMemCall1' */
static void Appl_DrMemory_CtrlModel_SetCanMemCall1(void)
{
  CanTx_0x3B2_DSM1_FLSeatMem1Sts(Appl_DrMemory_CtrlModel_B.In1_g);
}

/* Output and update for function-call system: '<S6>/SetCanMemCall2' */
static void Appl_DrMemory_CtrlModel_SetCanMemCall2(void)
{
  CanTx_0x3B2_DSM2_FLSeatMem2Sts(Appl_DrMemory_CtrlModel_B.In1_l);
}

/* Output and update for function-call system: '<S6>/GetCanSendEvent' */
static void Appl_DrMemory_CtrlModel_GetCanSendEvent(void)
{
  Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_m =
    Rte_GetCanEventSendTimes_0x3B2( );
}

/* Output and update for function-call system: '<S6>/SetCanMemCall3' */
static void Appl_DrMemory_CtrlModel_SetCanMemCall3(void)
{
  CanTx_0x3B2_DSM3_FLSeatMem3Sts(Appl_DrMemory_CtrlModel_B.In1_k);
}

/* Output and update for function-call system: '<S8>/SetCanSendEvent' */
static void Appl_DrMemory_CtrlModel_SetCanSendEvent_g(void)
{
  Rte_SetCanEvent_0x3B2(((INT16U)0U));
}

/* Output and update for function-call system: '<S8>/GetCanSendEvent' */
static void Appl_DrMemory_CtrlModel_GetCanSendEvent_b(void)
{
  Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_i =
    Rte_GetCanEventSendTimes_0x3B2( );
}

/* Output and update for function-call system: '<S8>/SetCanSendFLSeatMemSts' */
static void Appl_DrMemory_CtrlModel_SetCanSendFLSeatMemSts(void)
{
  CanTx_0x3B2_DSM_FLSeatMemStsAndMsg(Appl_DrMemory_CtrlModel_B.In1);
}

/* Function for Chart: '<S5>/MemoryCall' */
static void Appl_DrMemory_CtrlModel_inner_default_Wait(void)
{
  /* ��ȡ�������1Ŀ��λ�� */
  if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call1)
  {
    Appl_DrMemory_CtrlModel_DW.MemoryButtonNum =
      enMemCallFb_EN_MemCallFb_Succeed;
    Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_DrMemory_CtrlModel_B.MemoryValid;
    Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_DrMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryBackPosi;
    Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /* ��ȡ�������2Ŀ��λ�� */
  if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call2)
  {
    Appl_DrMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_Faild;
    Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_DrMemory_CtrlModel_B.MemoryValid;
    Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_DrMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryBackPosi;
    Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /* ��ȡ�������3Ŀ��λ�� */
  if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call3)
  {
    Appl_DrMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_Wait;
    Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_DrMemory_CtrlModel_B.MemoryValid;
    Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_DrMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryBackPosi;
    Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_DrMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /*  ���ò����� ֹͣ����˶�  */
  if ((Appl_DrMemory_CtrlModel_B.MemCallPC_Flag == ((BOOL)FALSE)) ||
      (Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq == ((BOOL)FALSE)))
  {
    Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
    Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatBackPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
  }
  else
  {
    Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_Wait;
  }
}

/* Function for Chart: '<S5>/MemorySetLogic' */
static void Appl_DrMemory_CtrlModel_inner_default_Wait_i(void)
{
  INT32S tmp;

  /* ��ʼǰ������������ */
  if (Appl_DrMemory_CtrlModel_B.MemSetPC_Flag == ((BOOL)FALSE))
  {
    Appl_DrMemory_CtrlModel_DW.WaitTimer = 0U;
  }
  else
  {
    /* ��������1 */
    if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set1)
    {
      Appl_DrMemory_CtrlModel_DW.FLTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S1;

      /*  ���书��ʹ��  */
      if ((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2))
      {
        Appl_DrMemory_CtrlModel_B.CurrentH_h = DrMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem1_Height,
          Appl_DrMemory_CtrlModel_B.CurrentH_h);
        Appl_DrMemory_CtrlModel_B.CurrentL_b = DrMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem1_Length,
          Appl_DrMemory_CtrlModel_B.CurrentL_b);
        Appl_DrMemory_CtrlModel_B.CurrentB_o = DrMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem1_Back,
          Appl_DrMemory_CtrlModel_B.CurrentB_o);
        Appl_DrMemory_CtrlModel_B.CurrentF_e = DrMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem1_Front,
          Appl_DrMemory_CtrlModel_B.CurrentF_e);
        Appl_DrMemory_CtrlModel_B.Sts_n = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_DrMem1_ValidFlag,
          Appl_DrMemory_CtrlModel_B.Sts_n);
      }
    }

    /* ��������2 */
    if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set2)
    {
      Appl_DrMemory_CtrlModel_DW.FLTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S2;

      /*  ���书��ʹ��  */
      if ((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2))
      {
        Appl_DrMemory_CtrlModel_B.CurrentH_ke = DrMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem2_Height,
          Appl_DrMemory_CtrlModel_B.CurrentH_ke);
        Appl_DrMemory_CtrlModel_B.CurrentL_l = DrMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem2_Length,
          Appl_DrMemory_CtrlModel_B.CurrentL_l);
        Appl_DrMemory_CtrlModel_B.CurrentB_c = DrMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem2_Back,
          Appl_DrMemory_CtrlModel_B.CurrentB_c);
        Appl_DrMemory_CtrlModel_B.CurrentF_h = DrMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem2_Front,
          Appl_DrMemory_CtrlModel_B.CurrentF_h);
        Appl_DrMemory_CtrlModel_B.Sts_g = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_DrMem2_ValidFlag,
          Appl_DrMemory_CtrlModel_B.Sts_g);
      }
    }

    /* ��������3 */
    if (Appl_DrMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set3)
    {
      Appl_DrMemory_CtrlModel_DW.FLTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S3;

      /*  ���书��ʹ��  */
      if ((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2))
      {
        Appl_DrMemory_CtrlModel_B.CurrentH_k = DrMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_Height,
          Appl_DrMemory_CtrlModel_B.CurrentH_k);
        Appl_DrMemory_CtrlModel_B.CurrentL_g = DrMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_Length,
          Appl_DrMemory_CtrlModel_B.CurrentL_g);
        Appl_DrMemory_CtrlModel_B.CurrentB_l = DrMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_Back,
          Appl_DrMemory_CtrlModel_B.CurrentB_l);
        Appl_DrMemory_CtrlModel_B.CurrentF_a = DrMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_Front,
          Appl_DrMemory_CtrlModel_B.CurrentF_a);
        Appl_DrMemory_CtrlModel_B.Sts = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_DrMem3_ValidFlag,
          Appl_DrMemory_CtrlModel_B.Sts);
      }
    }

    Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;

    /* ʹ����ʱ����EEPROM������� */
    if (Appl_DrMemory_CtrlModel_DW.WaitTimer < CAL_DrMem_100MS)
    {
      tmp = Appl_DrMemory_CtrlModel_DW.WaitTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_DrMemory_CtrlModel_DW.WaitTimer = (INT8U)tmp;
    }
    else
    {
      Appl_DrMemory_CtrlModel_DW.WaitTimer = CAL_DrMem_100MS;
    }
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrMemory_CtrlModel_LogicCtrl_Init(void)
{
  enMemCallFb CallFB1;
  enMemCallFb CallFB2;
  enMemCallFb CallFB3;
  Appl_DrMemory_CtrlModel_DW.is_MemoryCallLogic =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.is_active_c8_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_NULL;
  Appl_DrMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_NULL;
  Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = 0U;
  Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = 0U;
  Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
  Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq = 0U;
  Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
  Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
  Appl_DrMemory_CtrlModel_B.SeatBackPosiReq = 0U;
  Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
  Appl_DrMemory_CtrlModel_B.MemCallStopReason = enMemStopCause_EN_MemStop_NULL;
  Appl_DrMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_DrMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_DrMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_DrMemory_CtrlModel_MemCallWaitFBFunc_Init(&CallFB1, &CallFB2, &CallFB3);
  Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.is_active_c3_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_DW.is_c3_Appl_DrMemory_CtrlModel =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag = 0U;
  Appl_DrMemory_CtrlModel_DW.WaitTimer = 0U;
  Appl_DrMemory_CtrlModel_DW.FLTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
  Appl_DrMemory_CtrlModel_DW.WaitTimeCnt = 0U;
  Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
  Appl_DrMemory_CtrlModel_B.MemSetStopReason = enMemStopCause_EN_MemStop_NULL;
  Appl_DrMemory_CtrlModel_DW.is_active_c5_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_DW.is_c5_Appl_DrMemory_CtrlModel =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
  Appl_DrMemory_CtrlModel_B.FLSeatPosMsg = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrMemory_CtrlModel_LogicCtrl(void)
{
  enMemBtn SeatMemBtn_prev_g;
  INT8U DrMem_CurrentMoveType_prev;
  INT32S tmp;
  BOOL guard1 = false;
  BOOL guard2 = false;
  Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag_c =
    Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag;
  Appl_DrMemory_CtrlModel_B.PreMemRemindStop_d =
    Appl_DrMemory_CtrlModel_B.PreMemRemindStop;
  SeatMemBtn_prev_g = Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g;
  Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g =
    Appl_DrMemory_CtrlModel_B.SeatMemBtn;
  if (Appl_DrMemory_CtrlModel_DW.is_active_c8_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c8_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_MemoryCallLogic =
      Appl_DrMemory_CtrlModel_IN_MemoryCallInactive;
    Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = ((BOOL)FALSE);
    Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
    Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatBackPosiReq = 0U;
    Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
    Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
      Appl_DrMemory_CtrlMod_IN_MemoryCallDefaultFeedback;
    Appl_DrMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
  }
  else
  {
    if (Appl_DrMemory_CtrlModel_DW.is_MemoryCallLogic ==
        Appl_DrMemory_CtrlModel_IN_MemoryCallActive)
    {
      if (Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m == ((BOOL)TRUE))
      {
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
          Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallLogic =
          Appl_DrMemory_CtrlModel_IN_MemoryCallInactive;
        Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
          enMemCallFb_EN_MemCallFb_NULL;
        Appl_DrMemory_CtrlModel_DW.MemoryButtonNum =
          enMemCallFb_EN_MemCallFb_NULL;
        Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = ((BOOL)FALSE);
        Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
        Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
        Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
        Appl_DrMemory_CtrlModel_B.SeatBackPosiReq = 0U;
        Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
      }
      else
      {
        switch (Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive)
        {
         case Appl_DrMemory_CtrlModel_IN_Fail:
          /* Srvl_CAN�������ķ������ || ��ʱ90ms */
          if (Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f >= 2)
          {
            Appl_DrMemory_CtrlModel_GetCanSendEvent();
            if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
            {
              Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_DrMemory_CtrlModel_IN_MessageSendFinish;
              Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = ((BOOL)TRUE);
              Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
                enMemCallFb_EN_MemCallFb_NULL;
            }
            else
            {
              /* SetCanSendEvent(); */
              tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = (INT16U)tmp;
            }
          }
          else
          {
            /* SetCanSendEvent(); */
            tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = (INT16U)tmp;
          }
          break;

         case Appl_DrMemory_CtrlModel_IN_MessageSendFinish:
          break;

         case Appl_DrMemory_CtrlModel_IN_Succeed:
          /* Srvl_CAN�������ķ������ || ��ʱ90ms */
          if (Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f >= 2)
          {
            Appl_DrMemory_CtrlModel_GetCanSendEvent();
            if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
            {
              Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_DrMemory_CtrlModel_IN_MessageSendFinish;
              Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = ((BOOL)TRUE);
              Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
                enMemCallFb_EN_MemCallFb_NULL;
            }
            else
            {
              /* SetCanSendEvent(); */
              tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = (INT16U)tmp;
            }
          }
          else
          {
            /* SetCanSendEvent(); */
            tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = (INT16U)tmp;
          }
          break;

         default:
          /* �������ǰ������������ */
          if (Appl_DrMemory_CtrlModel_B.MemCallPC_Flag == ((BOOL)FALSE))
          {
            Appl_DrMemory_CtrlModel_B.MemCallStopReason =
              Appl_DrMemory_CtrlModel_B.PreMemCallStop;
            Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
              Appl_DrMemory_CtrlModel_IN_Fail;
            Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
              enMemCallFb_EN_MemCallFb_Faild;
            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = 0U;
          }
          else
          {
            /*  λ��δ����  */
            if (Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq == ((BOOL)FALSE))
            {
              Appl_DrMemory_CtrlModel_B.MemCallStopReason =
                enMemStopCause_EN_MemStop_PosiError;
              Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_DrMemory_CtrlModel_IN_MessageSendFinish;
              Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag_m = ((BOOL)TRUE);
              Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
                enMemCallFb_EN_MemCallFb_NULL;
            }
            else
            {
              /* 1.�˴��ӿ���Ҫ�����ģ��ȷ�Ϸ���ֵ
                 2.����ת������������
                 �߶��Զ����гɹ���־λ == FALSE
                 || �����Զ����гɹ���־λ == FALSE
                 || �����Զ����гɹ���־λ == FALSE
                 || ǰ���Զ����гɹ���־λ == FALSE
               /MemCallStopReason = 0xC:enMotorRunError    */
              if ((DrMem_HeightAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
                  (DrMem_LengthAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
                  (DrMem_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
                  (DrMem_FrontAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL))
              {
                Appl_DrMemory_CtrlModel_B.MemCallStopReason =
                  enMemStopCause_EN_MemStop_MotorRunErr;
                Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
                  Appl_DrMemory_CtrlModel_IN_Fail;
                Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
                  enMemCallFb_EN_MemCallFb_Faild;
                Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = 0U;
              }
              else
              {
                /* (�߶��Զ����гɹ���־λ == TRUE || �߶ȶ�ת)
                   && (�����Զ����гɹ���־λ == TRUE || �����ת)
                   && (�����Զ����гɹ���־λ == TRUE || ������ת)
                   && (ǰ���Զ����гɹ���־λ == TRUE || ǰ����ת)    */
                if (((DrMem_HeightAutoRunFlag ==
                      enSeatAutoRunSts_EN_SEAT_SUCCESS) ||
                     (DrMem_HeightLockFault == ((BOOL)TRUE))) &&
                    ((DrMem_LengthAutoRunFlag ==
                      enSeatAutoRunSts_EN_SEAT_SUCCESS) ||
                     (DrMem_LengthLockFault == ((BOOL)TRUE))) &&
                    ((DrMem_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_SUCCESS)
                     || (DrMem_BackLockFault == ((BOOL)TRUE))) &&
                    ((DrMem_FrontAutoRunFlag == enSeatAutoRunSts_EN_SEAT_SUCCESS)
                     || (DrMem_FrontLockFault == ((BOOL)TRUE))))
                {
                  Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
                    Appl_DrMemory_CtrlModel_IN_Succeed;
                  Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts =
                    enMemCallFb_EN_MemCallFb_Succeed;
                  Appl_DrMemory_CtrlModel_DW.WaitTimeCnt_f = 0U;
                }
                else
                {
                  Appl_DrMemory_CtrlModel_inner_default_Wait();
                }
              }
            }
          }
          break;
        }
      }
    }
    else
    {
      /* SeatMemBtn��ΪCallButton1 */
      if (((SeatMemBtn_prev_g != Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g) &&
           (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g ==
            enMemBtn_EN_MemBtn_Call1)) || ((SeatMemBtn_prev_g !=
            Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g) &&
           (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g ==
            enMemBtn_EN_MemBtn_Call2)) || ((SeatMemBtn_prev_g !=
            Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g) &&
           (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start_g ==
            enMemBtn_EN_MemBtn_Call3)))
      {
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallLogic =
          Appl_DrMemory_CtrlModel_IN_MemoryCallActive;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallActive =
          Appl_DrMemory_CtrlModel_IN_Wait;
        Appl_DrMemory_CtrlModel_inner_default_Wait();
      }
      else
      {
        /* SeatMemBtn��ΪCallButton2 */
        /* SeatMemBtn��ΪCallButton3 */
      }
    }

    if (Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback ==
        Appl_DrMemory_CtrlMod_IN_MemoryCallDefaultFeedback)
    {
      /* ������ÿ�ʼ���� */
      if (Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts ==
          enMemCallFb_EN_MemCallFb_Wait)
      {
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
          Appl_DrMemory_CtrlMode_IN_MemoryCallResultFeedback;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_DrMemory_CtrlModel_IN_MemoryCallRun;
        Appl_DrMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_DrMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_DrMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem3StsFb);
      }
      else
      {
        /* �������ֱ�ӽ��� */
        if ((Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts ==
             enMemCallFb_EN_MemCallFb_Succeed) ||
            (Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts ==
             enMemCallFb_EN_MemCallFb_Faild))
        {
          Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
            Appl_DrMemory_CtrlMode_IN_MemoryCallResultFeedback;
          Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
            Appl_DrMemory_CtrlModel_IN_MemoryCallMotorStop;
          Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
          Appl_DrMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
            Appl_DrMemory_CtrlModel_DW.MemoryButtonNum,
            Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts,
            &Appl_DrMemory_CtrlModel_B.SeatMem1StsFb,
            &Appl_DrMemory_CtrlModel_B.SeatMem2StsFb,
            &Appl_DrMemory_CtrlModel_B.SeatMem3StsFb);
          Appl_DrMemory_CtrlModel_B.In1_g = (INT16U)
            Appl_DrMemory_CtrlModel_B.SeatMem1StsFb;
          Appl_DrMemory_CtrlModel_SetCanMemCall1();
          Appl_DrMemory_CtrlModel_B.In1_l = (INT16U)
            Appl_DrMemory_CtrlModel_B.SeatMem2StsFb;
          Appl_DrMemory_CtrlModel_SetCanMemCall2();
          Appl_DrMemory_CtrlModel_B.In1_k = (INT16U)
            Appl_DrMemory_CtrlModel_B.SeatMem3StsFb;
          Appl_DrMemory_CtrlModel_SetCanMemCall3();
          Appl_DrMemory_CtrlModel_SetCanSendEvent();
        }
      }
    }
    else if (Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback ==
             Appl_DrMemory_CtrlModel_IN_MemoryCallMotorStop)
    {
      /* 1��ʱ90ms */
      guard1 = false;
      if (Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt >= CAL_DrMem_90MS)
      {
        guard1 = true;
      }
      else
      {
        Appl_DrMemory_CtrlModel_GetCanSendEvent();
        if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
        {
          guard1 = true;
        }
        else
        {
          tmp = Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt = (INT16U)tmp;
        }
      }

      if (guard1)
      {
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
          Appl_DrMemory_CtrlMod_IN_MemoryCallDefaultFeedback;
        Appl_DrMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
        Appl_DrMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
        Appl_DrMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
      }
    }
    else
    {
      /* ������ý��� */
      if ((Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts ==
           enMemCallFb_EN_MemCallFb_Succeed) ||
          (Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts ==
           enMemCallFb_EN_MemCallFb_Faild))
      {
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_DrMemory_CtrlModel_IN_MemoryCallMotorStop;
        Appl_DrMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
        Appl_DrMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_DrMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_DrMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem3StsFb);
        Appl_DrMemory_CtrlModel_B.In1_g = (INT16U)
          Appl_DrMemory_CtrlModel_B.SeatMem1StsFb;
        Appl_DrMemory_CtrlModel_SetCanMemCall1();
        Appl_DrMemory_CtrlModel_B.In1_l = (INT16U)
          Appl_DrMemory_CtrlModel_B.SeatMem2StsFb;
        Appl_DrMemory_CtrlModel_SetCanMemCall2();
        Appl_DrMemory_CtrlModel_B.In1_k = (INT16U)
          Appl_DrMemory_CtrlModel_B.SeatMem3StsFb;
        Appl_DrMemory_CtrlModel_SetCanMemCall3();
        Appl_DrMemory_CtrlModel_SetCanSendEvent();
      }
      else
      {
        Appl_DrMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_DrMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_DrMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_DrMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_DrMemory_CtrlModel_B.SeatMem3StsFb);
      }
    }
  }

  SeatMemBtn_prev_g = Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start;
  Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start =
    Appl_DrMemory_CtrlModel_B.SeatMemBtn;
  if (Appl_DrMemory_CtrlModel_DW.is_active_c3_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c3_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_c3_Appl_DrMemory_CtrlModel =
      Appl_DrMemory_CtrlModel_IN_MemorySetInactive;
    Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
    Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)FALSE);
  }
  else if (Appl_DrMemory_CtrlModel_DW.is_c3_Appl_DrMemory_CtrlModel ==
           Appl_DrMemory_CtrlModel_IN_MemorySetActive)
  {
    if (Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag == ((BOOL)TRUE))
    {
      Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
        Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_e;
      Appl_DrMemory_CtrlModel_DW.is_c3_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_MemorySetInactive;
      Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)FALSE);
    }
    else
    {
      guard1 = false;
      guard2 = false;
      switch (Appl_DrMemory_CtrlModel_DW.is_MemorySetActive)
      {
       case Appl_DrMemory_CtrlModel_IN_Fail:
        /* Srvl_CAN�������ķ������ || ��ʱ90ms */
        if (Appl_DrMemory_CtrlModel_DW.WaitTimeCnt >= CAL_DrMem_90MS)
        {
          guard1 = true;
        }
        else
        {
          Appl_DrMemory_CtrlModel_GetCanSendEvent_b();
          if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_i == ((BOOL)TRUE))
          {
            guard1 = true;
          }
          else
          {
            tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt = (INT16U)tmp;
          }
        }
        break;

       case Appl_DrMemory_CtrlModel_IN_MessageSendFinish:
        break;

       case Appl_DrMemory_CtrlModel_IN_Succeed:
        /* Srvl_CAN�������ķ������ || ��ʱ90ms */
        if (Appl_DrMemory_CtrlModel_DW.WaitTimeCnt >= CAL_DrMem_90MS)
        {
          guard2 = true;
        }
        else
        {
          Appl_DrMemory_CtrlModel_GetCanSendEvent_b();
          if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_i == ((BOOL)TRUE))
          {
            guard2 = true;
          }
          else
          {
            tmp = Appl_DrMemory_CtrlModel_DW.WaitTimeCnt + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt = (INT16U)tmp;
          }
        }
        break;

       default:
        /* ǰ������������ */
        if (Appl_DrMemory_CtrlModel_B.MemSetPC_Flag == ((BOOL)FALSE))
        {
          Appl_DrMemory_CtrlModel_B.MemSetStopReason =
            Appl_DrMemory_CtrlModel_B.PreMemSetStop;
          Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
            Appl_DrMemory_CtrlModel_IN_Fail;
          Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts =
            enMemSetFb_EN_MemSetFb_Fail;
          Appl_DrMemory_CtrlModel_DW.WaitTimer = 0U;
          Appl_DrMemory_CtrlModel_DW.WaitTimeCnt = 0U;
          Appl_DrMemory_CtrlModel_B.In1 = (INT16U)
            Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts;
          Appl_DrMemory_CtrlModel_SetCanSendFLSeatMemSts();
          Appl_DrMemory_CtrlModel_SetCanSendEvent_g();
        }
        else
        {
          /* �洢���� */
          if (Appl_DrMemory_CtrlModel_DW.WaitTimer >= CAL_DrMem_100MS)
          {
            Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
              Appl_DrMemory_CtrlModel_IN_Succeed;
            Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts =
              Appl_DrMemory_CtrlModel_DW.FLTempSeatMemSetSts;
            Appl_DrMemory_CtrlModel_DW.WaitTimer = 0U;
            Appl_DrMemory_CtrlModel_DW.WaitTimeCnt = 0U;
            Appl_DrMemory_CtrlModel_B.In1 = (INT16U)
              Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts;
            Appl_DrMemory_CtrlModel_SetCanSendFLSeatMemSts();
            Appl_DrMemory_CtrlModel_SetCanSendEvent_g();
          }
          else
          {
            Appl_DrMemory_CtrlModel_inner_default_Wait_i();
          }
        }
        break;
      }

      if (guard2)
      {
        Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
          Appl_DrMemory_CtrlModel_IN_MessageSendFinish;
        Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)TRUE);
        Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      }

      if (guard1)
      {
        Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
          Appl_DrMemory_CtrlModel_IN_MessageSendFinish;
        Appl_DrMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)TRUE);
        Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      }
    }
  }
  else
  {
    /* SeatMemBtn��ΪMemorizeButton1 */
    if (((SeatMemBtn_prev_g != Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start) &&
         (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start == enMemBtn_EN_MemBtn_Set1))
        || ((SeatMemBtn_prev_g != Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start) &&
            (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start ==
             enMemBtn_EN_MemBtn_Set2)) || ((SeatMemBtn_prev_g !=
          Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start) &&
         (Appl_DrMemory_CtrlModel_DW.SeatMemBtn_start == enMemBtn_EN_MemBtn_Set3)))
    {
      Appl_DrMemory_CtrlModel_DW.is_c3_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_MemorySetActive;
      Appl_DrMemory_CtrlModel_DW.is_MemorySetActive =
        Appl_DrMemory_CtrlModel_IN_Wait;
      Appl_DrMemory_CtrlModel_inner_default_Wait_i();
    }
    else
    {
      /* SeatMemBtn��ΪMemorizeButton2 */
      /* SeatMemBtn��ΪMemorizeButton3 */
    }
  }

  DrMem_CurrentMoveType_prev =
    Appl_DrMemory_CtrlModel_DW.DrMem_CurrentMoveType_start;
  Appl_DrMemory_CtrlModel_DW.DrMem_CurrentMoveType_start = DrMem_CurrentMoveType;
  if (Appl_DrMemory_CtrlModel_DW.is_active_c5_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c5_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_c5_Appl_DrMemory_CtrlModel =
      Appl_DrMemory_CtrlModel_IN_PositionNoChange1;
    Appl_DrMemory_CtrlModel_B.FLSeatPosMsg = ((BOOL)FALSE);
  }
  else if (Appl_DrMemory_CtrlModel_DW.is_c5_Appl_DrMemory_CtrlModel ==
           Appl_DrMemory_CtrlModel_IN_PositionChange1)
  {
    /*  �ָ�������־λ == TRUE ��ǰ������������  */
    guard1 = false;
    if ((DrMem_GetRecoverDefaultFlag == ((BOOL)TRUE)) ||
        (Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag == ((BOOL)FALSE)))
    {
      guard1 = true;
    }
    else
    {
      /*  �췢ʱ�䳬ʱ  */
      Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_a =
        Rte_GetCanEventSendTimes_0x3B2( );
      if (Appl_DrMemory_CtrlModel_B.DrMem_FrontHallPosi_a == ((BOOL)TRUE))
      {
        guard1 = true;
      }
    }

    if (guard1)
    {
      Appl_DrMemory_CtrlModel_DW.is_c5_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_PositionNoChange1;
      Appl_DrMemory_CtrlModel_B.FLSeatPosMsg = ((BOOL)FALSE);
    }
  }
  else
  {
    /* ���㡾ǰ��������&&����������1��
       �˶��������ֶ����ڱ�Ϊ��ֹ
       && MemRemindPC_Flag == TRUE
       &&(Result1st != TRUE
       || Result2nd != TRUE
       || Result3rd != TRUE)  */
    if ((DrMem_CurrentMoveType_prev !=
         Appl_DrMemory_CtrlModel_DW.DrMem_CurrentMoveType_start) &&
        (DrMem_CurrentMoveType_prev == (INT32S)
         enSeatMotorRunType_EN_ManualEnable) && (DrMem_CurrentMoveType ==
         (INT32S)enSeatMotorRunType_EN_NULL) &&
        (Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag == ((BOOL)TRUE)) &&
        ((Appl_DrMemory_CtrlModel_B.Result1st != 2) ||
         (Appl_DrMemory_CtrlModel_B.Result2nd != 2) ||
         (Appl_DrMemory_CtrlModel_B.Result3rd != 2)) &&
        (Appl_DrMemory_CtrlModel_B.Result1st != ((BOOL)TRUE)) &&
        (Appl_DrMemory_CtrlModel_B.Result2nd != ((BOOL)TRUE)) &&
        (Appl_DrMemory_CtrlModel_B.Result3rd != ((BOOL)TRUE)))
    {
      Appl_DrMemory_CtrlModel_DW.is_c5_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_PositionChange1;
      Appl_DrMemory_CtrlModel_B.FLSeatPosMsg = ((BOOL)TRUE);
      Appl_DrMemory_CtrlModel_B.In1_h = Appl_DrMemory_CtrlModel_B.FLSeatPosMsg;
      CanTx_0x3B2_DSM_FLSeatPosMsg(Appl_DrMemory_CtrlModel_B.In1_h);
      Rte_SetCanEvent_0x3B2(((INT16U)0U));
    }
  }
}

/* System initialize for function-call system: '<S53>/PosiCompareFunc' */
static void Appl_DrMemory_CtrlModel_PosiCompareFunc_Init(INT8U *rty_Result)
{
  *rty_Result = 0U;
}

/* Output and update for function-call system: '<S53>/PosiCompareFunc' */
static void Appl_DrMemory_CtrlModel_PosiCompareFunc(INT16U rtu_MemH, INT16U
  rtu_MenL, INT16U rtu_MemB, INT16U rtu_MemF, INT16U rtu_CurrentH, INT16U
  rtu_CurrentL, INT16U rtu_CurrentB, INT16U rtu_CurrentF, INT8U rtu_AdjustEnable,
  INT8U rtu_PosiReq, INT8U *rty_Result)
{
  /*  û�м���λ��  */
  if (rtu_PosiReq == ((BOOL)FALSE))
  {
    /*  δ����λ��  */
    *rty_Result = 2U;
  }
  else
  {
    /*  ��ǰλ���ڼ���λ�÷�Χ��      */
    if ((rtu_CurrentH <= rtu_MemH + ((INT16U)D_ToleranceDistance)) && (rtu_MemH <=
         rtu_CurrentH + ((INT16U)D_ToleranceDistance)) && (rtu_CurrentL <=
         rtu_MenL + ((INT16U)D_ToleranceDistance)) && (rtu_MenL <= rtu_CurrentL
         + ((INT16U)D_ToleranceDistance)) && (rtu_CurrentB <= rtu_MemB +
         ((INT16U)D_ToleranceDistance)) && (rtu_MemB <= rtu_CurrentB + ((INT16U)
          D_ToleranceDistance)))
    {
      *rty_Result = ((BOOL)TRUE);
    }
    else
    {
      *rty_Result = ((BOOL)FALSE);
    }

    /*  8�����  */
    if (rtu_AdjustEnable == 2)
    {
      /*  ǰ���Ƕ���λ��   */
      if ((rtu_CurrentF <= rtu_MemF + ((INT16U)D_ToleranceDistance)) &&
          (rtu_MemF <= rtu_CurrentF + ((INT16U)D_ToleranceDistance)) &&
          (*rty_Result == ((BOOL)TRUE)))
      {
        *rty_Result = ((BOOL)TRUE);
      }
      else
      {
        *rty_Result = ((BOOL)FALSE);
      }
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_DrMemory_CtrlModel_RTE(void)
{
  DrMem_0x284_SpeedLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x284);
  DrMem_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
  DrMem_AnyoneLockFaultSts = Rte_GetVfb_DrAnyoneStallErr( );
  DrMem_AnyoneRelayFaultSts = Rte_GetVfb_DrAnyoneRelayAdheErr( );
  DrMem_BackAutoRunFlag = Rte_GetVfb_DrBackAutoRunFlag( );
  DrMem_BackHallPosi = Cdd_GetCurrentHallCnt(EN_DriverBack);
  DrMem_BackLockFault = Rte_GetVfb_DrBackStallErr( );
  DrMem_BackMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Back);
  DrMem_BackMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Back);
  DrMem_BackMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Back);
  DrMem_BackSwitch = Rte_GetVfb_DrBackSwitchCmd( );
  DrMem_CurrentMoveType = Rte_GetVfb_DrMoveType( );
  DrMem_DtcAnyoneHallFaultSts = Rte_GetVfb_DrAnyoneHallErr( );
  DrMem_FLSeatPosMsg = Srvl_GetMemIndexDataU8(EN_MemIndex_FLSeatPosMsg);
  DrMem_FrontAutoRunFlag = Rte_GetVfb_DrFrontAutoRunFlag( );
  DrMem_FrontHallPosi = Cdd_GetCurrentHallCnt(EN_DriverFront);
  DrMem_FrontLockFault = Rte_GetVfb_DrFrontStallErr( );
  DrMem_FrontMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Front);
  DrMem_FrontMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Front);
  DrMem_FrontMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Front);
  DrMem_FrontSwitch = Rte_GetVfb_DrFrontSwitchCmd( );
  DrMem_Gear_PN_FlagOut = Rte_GetCAN_Gear_PN_Flag( );
  DrMem_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  DrMem_HeightAutoRunFlag = Rte_GetVfb_DrHeightAutoRunFlag( );
  DrMem_HeightHallPosi = Cdd_GetCurrentHallCnt(EN_DriverHeight);
  DrMem_HeightLockFault = Rte_GetVfb_DrHeightStallErr( );
  DrMem_HeightMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Height);
  DrMem_HeightMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Height);
  DrMem_HeightMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Height);
  DrMem_HeightSwitch = Rte_GetVfb_DrHeightSwitchCmd( );
  DrMem_IVI_FLSeatMemSet1 = CanRx_0x351_IVI_FLSeatMemSet1( );
  DrMem_IVI_FLSeatMemSet2 = CanRx_0x351_IVI_FLSeatMemSet2( );
  DrMem_IVI_FLSeatMemSet3 = CanRx_0x351_IVI_FLSeatMemSet3( );
  DrMem_LengthAutoRunFlag = Rte_GetVfb_DrLengthAutoRunFlag( );
  DrMem_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_DriverLength);
  DrMem_LengthLockFault = Rte_GetVfb_DrLengthStallErr( );
  DrMem_LengthMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem1_Length);
  DrMem_LengthMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem2_Length);
  DrMem_LengthMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_DrMem3_Length);
  DrMem_LengthSwitch = Rte_GetVfb_DrLengthSwitchCmd( );
  DrMem_MemoryConfig = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
  DrMem_NapMode = Rte_GetVfb_NapMode( );
  DrMem_PowerMode = Rte_GetVfb_PowerMode( );
  DrMem_SeatLearnResult = Rte_GetVfb_DrLearnResult( );
  DrMem_SeatMemory1Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMem1_ValidFlag);
  DrMem_SeatMemory2Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMem2_ValidFlag);
  DrMem_SeatMemory3Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMem3_ValidFlag);
  DrMem_VehicleSpeed = CanRx_0x284_ABS_VehicleSpeed( );
  DrMem_VehicleSpeedValid = CanRx_0x284_ABS_VehicleSpeedValid( );
  DrMem_VoltMode = Rte_GetVfb_VoltMode( );
  DrMem_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrMemory_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U Result;
  Appl_DrMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_DW.is_active_c6_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  Appl_DrMemory_CtrlModel_DW.is_active_c1_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = 0U;
  Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = 0U;
  Appl_DrMemory_CtrlModel_B.MemoryBackPosi = 0U;
  Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = 0U;
  Appl_DrMemory_CtrlModel_B.MemoryValid = 0U;
  Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_DW.is_active_c2_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = 0U;
  Appl_DrMemory_CtrlModel_B.PreMemRemindStop = enMemStopCause_EN_MemStop_NULL;
  Appl_DrMemory_CtrlModel_B.Result1st = 0U;
  Appl_DrMemory_CtrlModel_B.Result2nd = 0U;
  Appl_DrMemory_CtrlModel_B.Result3rd = 0U;
  Appl_DrMemory_CtrlModel_PosiCompareFunc_Init(&Result);
  Appl_DrMemory_CtrlModel_DW.is_active_c11_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_DW.is_c11_Appl_DrMemory_CtrlModel =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = 0U;
  Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
    Appl_DrMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_DrMemory_CtrlModel_DW.is_active_c7_Appl_DrMemory_CtrlModel = 0U;
  Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = 0U;
  Appl_DrMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
  Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = 0U;
  Appl_DrMemory_CtrlModel_B.PreMemCallStop = enMemStopCause_EN_MemStop_NULL;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrMemory_CtrlModel_UpDataInputInfo(void)
{
  INT32S ActionFlag;
  INT8U ActionCnt;
  Appl_DrMemory_CtrlModel_RTE();
  if (Appl_DrMemory_CtrlModel_DW.is_active_c6_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c6_Appl_DrMemory_CtrlModel = 1U;

    /*  ����1  */
    /* ����2  */
    /*  ����3  */
    /*  ���ڳ�ͻ  */
    Appl_DrMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
      Appl_DrMemory_CtrlModel_IN_ButtonConflict;
    Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  }
  else
  {
    ActionCnt = 0U;

    /*  ����1  */
    if ((DrMem_IVI_FLSeatMemSet1 > enMemSet_EN_MemSet_NULL) &&
        (DrMem_IVI_FLSeatMemSet1 < enMemSet_EN_MemSet_Clean))
    {
      ActionCnt = 1U;
    }

    /* ����2  */
    if ((DrMem_IVI_FLSeatMemSet2 > enMemSet_EN_MemSet_NULL) &&
        (DrMem_IVI_FLSeatMemSet2 < enMemSet_EN_MemSet_Clean))
    {
      ActionCnt++;
    }

    /*  ����3  */
    if ((DrMem_IVI_FLSeatMemSet3 > enMemSet_EN_MemSet_NULL) &&
        (DrMem_IVI_FLSeatMemSet3 < enMemSet_EN_MemSet_Clean))
    {
      ActionCnt++;
    }

    /*  ���ڳ�ͻ  */
    if (ActionCnt >= 2)
    {
      ActionFlag = ((BOOL)FALSE);
    }
    else
    {
      ActionFlag = ((BOOL)TRUE);
    }

    if (Appl_DrMemory_CtrlModel_DW.is_AcquireMemoryButtonReq ==
        Appl_DrMemory_CtrlModel_IN_ButtonConflict)
    {
      /* �ޱ��ĳ�ͻ */
      if (ActionFlag == ((BOOL)TRUE))
      {
        Appl_DrMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
          Appl_DrMemory_CtrlModel_IN_NoButtonConflict;

        /*     */
        if (DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set1;
        }

        /*  ����λ��1  */
        if (DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call1;
        }

        /*  ����λ��2  */
        if (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set2;
        }

        /*  ����λ��2  */
        if (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call2;
        }

        /*  ����λ��3  */
        if (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set3;
        }

        /*  ����λ��3  */
        if (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call3;
        }

        /*  �޼�������  */
        if ((DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_NULL) &&
            (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_NULL) &&
            (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_NULL))
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
        }
      }
    }
    else
    {
      /* ���ĳ�ͻ */
      if (ActionFlag == ((BOOL)FALSE))
      {
        Appl_DrMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
          Appl_DrMemory_CtrlModel_IN_ButtonConflict;
        Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
      }
      else
      {
        /*     */
        if (DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set1;
        }

        /*  ����λ��1  */
        if (DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call1;
        }

        /*  ����λ��2  */
        if (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set2;
        }

        /*  ����λ��2  */
        if (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call2;
        }

        /*  ����λ��3  */
        if (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_Mem)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set3;
        }

        /*  ����λ��3  */
        if (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_Call)
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call3;
        }

        /*  �޼�������  */
        if ((DrMem_IVI_FLSeatMemSet1 == enMemSet_EN_MemSet_NULL) &&
            (DrMem_IVI_FLSeatMemSet2 == enMemSet_EN_MemSet_NULL) &&
            (DrMem_IVI_FLSeatMemSet3 == enMemSet_EN_MemSet_NULL))
        {
          Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
        }
      }
    }
  }

  if (Appl_DrMemory_CtrlModel_DW.is_active_c1_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c1_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
      Appl_DrMemory_CtrlModel_IN_NoneMemoryCall;
    Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = 0U;
    Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = 0U;
    Appl_DrMemory_CtrlModel_B.MemoryBackPosi = 0U;
    Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = 0U;
    Appl_DrMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
  }
  else
  {
    switch (Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel)
    {
     case Appl_DrMemory_CtrlModel_IN_AcquireMemory1stPosi:
      /*  �޵���  */
      if ((Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��3  */
        switch (Appl_DrMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call3:
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory3rdPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem3;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem3;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem3;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem3;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory3Valid;
          break;

         case enMemBtn_EN_MemBtn_Call2:
          /*  ����λ��2  */
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory2ndPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem2;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem2;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem2;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem2;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory2Valid;
          break;
        }
      }
      break;

     case Appl_DrMemory_CtrlModel_IN_AcquireMemory2ndPosi:
      /*  �޵���  */
      if ((Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��1  */
        switch (Appl_DrMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call1:
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory1stPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem1;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem1;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem1;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem1;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory1Valid;
          break;

         case enMemBtn_EN_MemBtn_Call3:
          /*  ����λ��3  */
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory3rdPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem3;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem3;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem3;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem3;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory3Valid;
          break;
        }
      }
      break;

     case Appl_DrMemory_CtrlModel_IN_AcquireMemory3rdPosi:
      /*  �޵���  */
      if ((Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_DrMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_DrMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��1  */
        switch (Appl_DrMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call1:
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory1stPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem1;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem1;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem1;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem1;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory1Valid;
          break;

         case enMemBtn_EN_MemBtn_Call2:
          /*  ����λ��2  */
          Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
            Appl_DrMemory_CtrlModel_IN_AcquireMemory2ndPosi;
          Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem2;
          Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem2;
          Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem2;
          Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem2;
          Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory2Valid;
          break;
        }
      }
      break;

     default:
      /*  ����λ��1  */
      switch (Appl_DrMemory_CtrlModel_B.SeatMemBtn)
      {
       case enMemBtn_EN_MemBtn_Call1:
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_AcquireMemory1stPosi;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem1;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem1;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem1;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem1;
        Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory1Valid;
        break;

       case enMemBtn_EN_MemBtn_Call2:
        /*  ����λ��2  */
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_AcquireMemory2ndPosi;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem2;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem2;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem2;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem2;
        Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory2Valid;
        break;

       case enMemBtn_EN_MemBtn_Call3:
        /*  ����λ��3  */
        Appl_DrMemory_CtrlModel_DW.is_c1_Appl_DrMemory_CtrlModel =
          Appl_DrMemory_CtrlModel_IN_AcquireMemory3rdPosi;
        Appl_DrMemory_CtrlModel_B.MemoryHeightPosi = DrMem_HeightMem3;
        Appl_DrMemory_CtrlModel_B.MemoryLengthPosi = DrMem_LengthMem3;
        Appl_DrMemory_CtrlModel_B.MemoryBackPosi = DrMem_BackMem3;
        Appl_DrMemory_CtrlModel_B.MemoryFrontPosi = DrMem_FrontMem3;
        Appl_DrMemory_CtrlModel_B.MemoryValid = DrMem_SeatMemory3Valid;
        break;
      }
      break;
    }
  }

  if (Appl_DrMemory_CtrlModel_DW.is_active_c2_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c2_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
      Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
  }
  else
  {
    Appl_DrMemory_CtrlModel_PosiCompareFunc(DrMem_HeightMem1, DrMem_LengthMem1,
      DrMem_BackMem1, DrMem_FrontMem1, DrMem_HeightHallPosi,
      DrMem_LengthHallPosi, DrMem_BackHallPosi, DrMem_FrontHallPosi,
      DrMem_AdjustEnable, DrMem_SeatMemory1Valid,
      &Appl_DrMemory_CtrlModel_B.Result3rd);
    Appl_DrMemory_CtrlModel_B.Result1st = Appl_DrMemory_CtrlModel_B.Result3rd;
    Appl_DrMemory_CtrlModel_PosiCompareFunc(DrMem_HeightMem2, DrMem_LengthMem2,
      DrMem_BackMem2, DrMem_FrontMem2, DrMem_HeightHallPosi,
      DrMem_LengthHallPosi, DrMem_BackHallPosi, DrMem_FrontHallPosi,
      DrMem_AdjustEnable, DrMem_SeatMemory2Valid,
      &Appl_DrMemory_CtrlModel_B.Result3rd);
    Appl_DrMemory_CtrlModel_B.Result2nd = Appl_DrMemory_CtrlModel_B.Result3rd;
    Appl_DrMemory_CtrlModel_PosiCompareFunc(DrMem_HeightMem3, DrMem_LengthMem3,
      DrMem_BackMem3, DrMem_FrontMem3, DrMem_HeightHallPosi,
      DrMem_LengthHallPosi, DrMem_BackHallPosi, DrMem_FrontHallPosi,
      DrMem_AdjustEnable, DrMem_SeatMemory3Valid,
      &Appl_DrMemory_CtrlModel_B.Result3rd);
    if (Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal ==
        Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);

      /* ���ݵ������� == 1 ���� == 2
         &&���书��ʹ�� == 0x1:TRUE
         && ������ʾ����ʹ�� == 0x1:Enable
         && ��ѹģʽ == ����
       /PreMemRemindStop = 0x0:enNone; */
      if (((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2)) &&
          (DrMem_MemoryConfig == ((BOOL)TRUE)) && (DrMem_VoltSatisfy == ((BOOL)
            TRUE)) && (DrMem_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_DrMemory_CtrlModel_B.PreMemRemindStop =
          enMemStopCause_EN_MemStop_NULL;
        Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
          Appl_DrMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)TRUE);

      /* ���ݵ������� != 1 �� != 2
         || F101���书�� != 0x1:TRUE
         || ������ʾ�������� != 0x1:Enable
       /PreMemRemindStop = 0xA:enConfigError; */
      if ((DrMem_MemoryConfig != ((BOOL)TRUE)) || ((DrMem_AdjustEnable != 1) &&
           (DrMem_AdjustEnable != 2)))
      {
        Appl_DrMemory_CtrlModel_B.PreMemRemindStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
          Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* ��ѹģʽ != ����
         /PreMemRemindStop = 0xE:enVoltageError; */
        if ((DrMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
            (DrMem_VoltSatisfy != ((BOOL)TRUE)))
        {
          Appl_DrMemory_CtrlModel_B.PreMemRemindStop =
            enMemStopCause_EN_MemStop_VoltageErr;
          Appl_DrMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
            Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_DrMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
        }
      }
    }
  }

  if (Appl_DrMemory_CtrlModel_DW.is_active_c11_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c11_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_c11_Appl_DrMemory_CtrlModel =
      Appl_DrMemory_CtrlModel_IN_MoreThan5;
    Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = ((BOOL)FALSE);
  }
  else if (Appl_DrMemory_CtrlModel_DW.is_c11_Appl_DrMemory_CtrlModel ==
           Appl_DrMemory_CtrlModel_IN_LessThan5)
  {
    Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = ((BOOL)TRUE);

    /* ABS���Ĳ�����
       || �����ź���Ч�� != 0x0:valid
       || ���� > D_5km_per_hour */
    if ((DrMem_0x284_SpeedLostFlag == ((BOOL)TRUE)) || (DrMem_VehicleSpeedValid
         != ((BOOL)FALSE)) || (DrMem_VehicleSpeed > ((INT16U)D_DRMEM_SPEED_5)))
    {
      Appl_DrMemory_CtrlModel_DW.is_c11_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_MoreThan5;
      Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = ((BOOL)FALSE);
    }
  }
  else
  {
    Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = ((BOOL)FALSE);

    /* ABS��������
       && �����ź���Ч�� == 0x0:valid
       && ���� �� D_5km_per_hour */
    if ((DrMem_0x284_SpeedLostFlag == ((BOOL)FALSE)) && (DrMem_VehicleSpeedValid
         == ((BOOL)FALSE)) && (DrMem_VehicleSpeed <= ((INT16U)D_DRMEM_SPEED_5)))
    {
      Appl_DrMemory_CtrlModel_DW.is_c11_Appl_DrMemory_CtrlModel =
        Appl_DrMemory_CtrlModel_IN_LessThan5;
      Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag = ((BOOL)TRUE);
    }
  }

  if (Appl_DrMemory_CtrlModel_DW.is_active_c7_Appl_DrMemory_CtrlModel == 0U)
  {
    Appl_DrMemory_CtrlModel_DW.is_active_c7_Appl_DrMemory_CtrlModel = 1U;
    Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
      Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
    Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
      Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
  }
  else
  {
    if (Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal ==
        Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);

      /* �������� == 1six way motor ||  2 twelve way motor
         && ���书��ʹ�� == 0x1:TRUE
         && ������ѧϰ
         && �����˶����� == 0x0:enNULL
         && ���λ������ϱ�־λ == FALSE
         && ���μ̵���ճ�����ϱ�־λ == FALSE
         && ���ζ�ת���ϱ�־λ == FALSE
         && IVI_NapMode_SwtichSet != 0x1:��С�ģʽ
         && ��ѹģʽ == ����
         && DrMem_NapMode != enNapMode.EN_NapMode_Open/PreMemSetStop = 0x0:enNone; */
      if (((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2)) &&
          (DrMem_MemoryConfig == ((BOOL)TRUE)) && (DrMem_SeatLearnResult ==
           ((BOOL)TRUE)) && (DrMem_CurrentMoveType == (INT32S)
                             enSeatMotorRunType_EN_NULL) &&
          (DrMem_DtcAnyoneHallFaultSts == ((BOOL)FALSE)) && ((INT32S)
           DrMem_AnyoneRelayFaultSts == ((BOOL)FALSE)) &&
          (DrMem_AnyoneLockFaultSts == ((BOOL)FALSE)) && (DrMem_VoltSatisfy ==
           ((BOOL)TRUE)) && (DrMem_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_DrMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
        Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
          Appl_DrMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)TRUE);

      /* ���书��ʹ�� != 0x1:TRUE
       /PreMemCallStop = 0xA:enConfigError; */
      if (((DrMem_AdjustEnable != 1) && (DrMem_AdjustEnable != 2)) ||
          (DrMem_MemoryConfig != ((BOOL)TRUE)))
      {
        Appl_DrMemory_CtrlModel_B.PreMemSetStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
          Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* !������ѧϰ
         /PreMemSetStop = 0x1:enNotLearn; */
        if (DrMem_SeatLearnResult != ((BOOL)TRUE))
        {
          Appl_DrMemory_CtrlModel_B.PreMemSetStop =
            enMemStopCause_EN_MemStop_Learn;
          Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
            Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
        }
        else
        {
          /* �����˶����� != 0x0:enNULL
           /PreMemSetStop = 0x2:enOtherMove; */
          if (DrMem_CurrentMoveType != (INT32S)enSeatMotorRunType_EN_NULL)
          {
            Appl_DrMemory_CtrlModel_B.PreMemSetStop =
              enMemStopCause_EN_MemStop_OtherMove;
            Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
              Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
            Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
          }
          else
          {
            /* ���λ������ϱ�־λ != FALSE
             /PreMemSetStop = 0x3:enHallError; */
            if (DrMem_DtcAnyoneHallFaultSts != ((BOOL)FALSE))
            {
              Appl_DrMemory_CtrlModel_B.PreMemSetStop =
                enMemStopCause_EN_MemStop_HallErr;
              Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
              Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
            }
            else
            {
              /* ���μ̵���ճ�����ϱ�־λ != FALSE
               /PreMemSetStop = 0x4:enRelayError; */
              if ((INT32S)DrMem_AnyoneRelayFaultSts != ((BOOL)FALSE))
              {
                Appl_DrMemory_CtrlModel_B.PreMemSetStop =
                  enMemStopCause_EN_MemStop_RelayErr;
                Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                  Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
              }
              else
              {
                /* ��ѹģʽ != ����
                 /PreMemSetStop = 0xE:enVoltageError; */
                if ((DrMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
                    (((BOOL)TRUE) != DrMem_VoltSatisfy))
                {
                  Appl_DrMemory_CtrlModel_B.PreMemSetStop =
                    enMemStopCause_EN_MemStop_VoltageErr;
                  Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                    Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                  Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
                }
                else
                {
                  /* ���ζ�ת���ϱ�־λ != FALSE
                   /PreMemSetStop = 0x5:EN_MemStop_StallErr(; */
                  if (DrMem_AnyoneLockFaultSts != ((BOOL)FALSE))
                  {
                    Appl_DrMemory_CtrlModel_B.PreMemSetStop =
                      enMemStopCause_EN_MemStop_StallErr;
                    Appl_DrMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                      Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                    Appl_DrMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
                  }
                }
              }
            }
          }
        }
      }
    }

    if (Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal ==
        Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);

      /* �������� == 1six way motor ||  2 twelve way motor
         &&���书��ʹ�� == 0x1:TRUE
         && ��Դ��λ != 0x3:enCRANK
         && GearPN_Flag == TRUE
         && ������ѧϰ
         && ���μ̵���ճ�����ϱ�־λ == FALSE
         && SpeedLessThan5_Flag == TRUE
         && �����˶����� <= 0x3:enMemory
         && ��ѹģʽ == ����
         && ���ΰ�����־λ == FALSE
         && DSM_NapMode_FB != 0x2:��С�ģʽ
       /PreMemCallStop = 0x0:enNone; */
      if (((DrMem_AdjustEnable == 1) || (DrMem_AdjustEnable == 2)) &&
          (DrMem_MemoryConfig == ((BOOL)TRUE)) && (DrMem_PowerMode !=
           enPowerModeSts_EN_CRANK) && (DrMem_Gear_PN_FlagOut == ((BOOL)TRUE)) &&
          (DrMem_SeatLearnResult == ((BOOL)TRUE)) && ((INT32S)
           DrMem_AnyoneRelayFaultSts == ((BOOL)FALSE)) &&
          (Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag == ((BOOL)TRUE)) &&
          (DrMem_HeightSwitch == ((BOOL)FALSE)) && (DrMem_LengthSwitch == ((BOOL)
            FALSE)) && (DrMem_BackSwitch == ((BOOL)FALSE)) &&
          ((DrMem_FrontSwitch == ((BOOL)FALSE)) || (DrMem_AdjustEnable == 1)) &&
          (DrMem_CurrentMoveType <= (INT32S)enSeatMotorRunType_EN_MemoryEnable) &&
          (DrMem_VoltSatisfy == ((BOOL)TRUE)) && (DrMem_VoltMode ==
           enFinalPowerMode_EN_NORMAL_VOLT) && (DrMem_NapMode !=
           enNapMode_EN_NapMode_Open))
      {
        Appl_DrMemory_CtrlModel_B.PreMemCallStop =
          enMemStopCause_EN_MemStop_NULL;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
          Appl_DrMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)TRUE);

      /* ���书��ʹ�� != 0x1:TRUE
       /PreMemCallStop = 0xA:enConfigError; */
      if (((DrMem_AdjustEnable != 1) && (DrMem_AdjustEnable != 2)) ||
          (DrMem_MemoryConfig != ((BOOL)TRUE)))
      {
        Appl_DrMemory_CtrlModel_B.PreMemCallStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
          Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* !������ѧϰ
         /PreMemSetStop = 0x1:enNotLearn; */
        if (DrMem_SeatLearnResult != ((BOOL)TRUE))
        {
          Appl_DrMemory_CtrlModel_B.PreMemCallStop =
            enMemStopCause_EN_MemStop_Learn;
          Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
            Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
        }
        else
        {
          /* �����˶����� > 0x3:enMemory
           /PreMemCallStop = 0x2:enOtherMove; */
          if (DrMem_CurrentMoveType > (INT32S)enSeatMotorRunType_EN_MemoryEnable)
          {
            Appl_DrMemory_CtrlModel_B.PreMemCallStop =
              enMemStopCause_EN_MemStop_OtherMove;
            Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
              Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
            Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
          }
          else
          {
            /* ���μ̵���ճ�����ϱ�־λ != FALSE
             /PreMemSetStop = 0x4:enRelayError; */
            if ((INT32S)DrMem_AnyoneRelayFaultSts != ((BOOL)FALSE))
            {
              Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                enMemStopCause_EN_MemStop_RelayErr;
              Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
              Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
            }
            else
            {
              /* IVI_NapMode_SwtichSet == 0x1:��С�ģʽ
               /PreMemSetStop = 0xB:enNapError; */
              if (DrMem_NapMode == enNapMode_EN_NapMode_Open)
              {
                Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                  enMemStopCause_EN_MemStop_NapError;
                Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                  Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
              }
              else
              {
                /* ��ѹģʽ != ����
                 /PreMemSetStop = 0xE:enVoltageError; */
                if ((DrMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
                    (((BOOL)TRUE) != DrMem_VoltSatisfy))
                {
                  Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                    enMemStopCause_EN_MemStop_VoltageErr;
                  Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                    Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                  Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
                }
                else
                {
                  /* ��Դ��λ == 0x3:enCRANK
                   /PreMemCallStop = 0x6:enNotON; */
                  if (DrMem_PowerMode == enPowerModeSts_EN_CRANK)
                  {
                    Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                      enMemStopCause_EN_MemStop_NotON;
                    Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                      Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                    Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
                  }
                  else
                  {
                    /* GearPN_Flag != TRUE
                     /PreMemCallStop = 0x7:enNotGearPN; */
                    if (DrMem_Gear_PN_FlagOut != ((BOOL)TRUE))
                    {
                      Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                        enMemStopCause_EN_MemStop_NotGearPN;
                      Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                        Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                      Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
                    }
                    else
                    {
                      /* SpeedLessThan5_Flag != TRUE
                       /PreMemCallStop = 0x8:enSpeedError; */
                      if (Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag !=
                          ((BOOL)TRUE))
                      {
                        Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                          enMemStopCause_EN_MemStop_SpeedError;
                        Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal
                          = Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                        Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
                      }
                      else
                      {
                        /* ����״̬ != FALSE
                         /PreMemSetStop = 0x5:EN_MemStop_StallErr(; */
                        if ((DrMem_HeightSwitch != ((BOOL)FALSE)) ||
                            (DrMem_LengthSwitch != ((BOOL)FALSE)) ||
                            (DrMem_BackSwitch != ((BOOL)FALSE)) ||
                            ((DrMem_FrontSwitch != ((BOOL)FALSE)) &&
                             (DrMem_AdjustEnable == 2)))
                        {
                          Appl_DrMemory_CtrlModel_B.PreMemCallStop =
                            enMemStopCause_EN_MemStop_StallErr;
                          Appl_DrMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal
                            = Appl_DrMemory_CtrlMode_IN_PreconditionNotSatisfied;
                          Appl_DrMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)
                            FALSE);
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

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_DrMemory_CtrlModel_UpDataOutputInfo(void)
{
  CanTx_0x3B2_DSM_FLSeatMemStsAndMsg(Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts);
  CanTx_0x3B2_DSM_FLSeatPosMsg(Appl_DrMemory_CtrlModel_B.FLSeatPosMsg);
  Rte_SetVfb_MemCallStopReason(Appl_DrMemory_CtrlModel_B.MemCallStopReason);
  Rte_SetVfb_MemSetStopReason(Appl_DrMemory_CtrlModel_B.MemSetStopReason);
  Rte_SetVfb_PreMemRemindStop(Appl_DrMemory_CtrlModel_B.PreMemRemindStop_d);
  Rte_SetVfb_DrMemBackReqPosi(Appl_DrMemory_CtrlModel_B.SeatBackPosiReq);
  Rte_SetVfb_DrMemFrontReqPosi(Appl_DrMemory_CtrlModel_B.SeatFrontPosiReq);
  Rte_SetVfb_DrMemHeightReqPosi(Appl_DrMemory_CtrlModel_B.SeatHeightPosiReq);
  Rte_SetVfb_DrMemLengthReqPosi(Appl_DrMemory_CtrlModel_B.SeatLengthPosiReq);
  CanTx_0x3B2_DSM1_FLSeatMem1Sts(Appl_DrMemory_CtrlModel_B.SeatMem1StsFb);
  CanTx_0x3B2_DSM2_FLSeatMem2Sts(Appl_DrMemory_CtrlModel_B.SeatMem2StsFb);
  CanTx_0x3B2_DSM3_FLSeatMem3Sts(Appl_DrMemory_CtrlModel_B.SeatMem3StsFb);
  Rte_SetVfb_SeatMemoryValidReq(Appl_DrMemory_CtrlModel_B.SeatMemoryValidReq);
  Rte_SetVfb_SpeedLessThan5_Flag(Appl_DrMemory_CtrlModel_B.SpeedLessThan5_Flag_c);
}

/* Model step function */
void Appl_DrMemory_CtrlModel_step(void)
{
  Appl_DrMemory_CtrlModel_UpDataInputInfo();
  Appl_DrMemory_CtrlModel_LogicCtrl();
  Appl_DrMemory_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_DrMemory_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_DrMemory_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_DrMemory_CtrlModel_B), 0,
                sizeof(B_Appl_DrMemory_CtrlModel_T));

  {
    Appl_DrMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.PreMemCallStop = enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.PreMemRemindStop = enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.PreMemRemindStop_d =
      enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.MemSetStopReason = enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.MemCallStopReason = enMemStopCause_EN_MemStop_NULL;
    Appl_DrMemory_CtrlModel_B.FLSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_DrMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  }

  /* exported global signals */
  DrMem_AnyoneRelayFaultSts = enSeatMotorRunType_EN_NULL;
  DrMem_BackAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrMem_FrontAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrMem_HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrMem_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrMem_PowerMode = enPowerModeSts_EN_OFF;
  DrMem_NapMode = enNapMode_EN_NapMode_NULL;
  DrMem_IVI_FLSeatMemSet1 = enMemSet_EN_MemSet_NULL;
  DrMem_IVI_FLSeatMemSet2 = enMemSet_EN_MemSet_NULL;
  DrMem_IVI_FLSeatMemSet3 = enMemSet_EN_MemSet_NULL;
  DrMem_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  DrMem_BackHallPosi = ((INT16U)0U);
  DrMem_BackMem1 = ((INT16U)0U);
  DrMem_BackMem2 = ((INT16U)0U);
  DrMem_BackMem3 = ((INT16U)0U);
  DrMem_FrontHallPosi = ((INT16U)0U);
  DrMem_FrontMem1 = ((INT16U)0U);
  DrMem_FrontMem2 = ((INT16U)0U);
  DrMem_FrontMem3 = ((INT16U)0U);
  DrMem_GetRecoverDefaultFlag = ((INT16U)0U);
  DrMem_HeightHallPosi = ((INT16U)0U);
  DrMem_HeightMem1 = ((INT16U)0U);
  DrMem_HeightMem2 = ((INT16U)0U);
  DrMem_HeightMem3 = ((INT16U)0U);
  DrMem_LengthHallPosi = ((INT16U)0U);
  DrMem_LengthMem1 = ((INT16U)0U);
  DrMem_LengthMem2 = ((INT16U)0U);
  DrMem_LengthMem3 = ((INT16U)0U);
  DrMem_VehicleSpeed = ((INT16U)0U);
  DrMem_0x284_SpeedLostFlag = ((INT8U)0U);
  DrMem_AdjustEnable = ((INT8U)0U);
  DrMem_AnyoneLockFaultSts = ((INT8U)0U);
  DrMem_BackLockFault = ((INT8U)0U);
  DrMem_BackSwitch = ((INT8U)0U);
  DrMem_CurrentMoveType = ((INT8U)0U);
  DrMem_DtcAnyoneHallFaultSts = ((INT8U)0U);
  DrMem_FLSeatPosMsg = ((INT8U)0U);
  DrMem_FrontLockFault = ((INT8U)0U);
  DrMem_FrontSwitch = ((INT8U)0U);
  DrMem_Gear_PN_FlagOut = ((INT8U)0U);
  DrMem_HeightLockFault = ((INT8U)0U);
  DrMem_HeightSwitch = ((INT8U)0U);
  DrMem_LengthLockFault = ((INT8U)0U);
  DrMem_LengthSwitch = ((INT8U)0U);
  DrMem_MemoryConfig = ((INT8U)0U);
  DrMem_SeatLearnResult = ((INT8U)0U);
  DrMem_SeatMemory1Valid = ((INT8U)0U);
  DrMem_SeatMemory2Valid = ((INT8U)0U);
  DrMem_SeatMemory3Valid = ((INT8U)0U);
  DrMem_VehicleSpeedValid = ((INT8U)0U);
  DrMem_VoltSatisfy = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_DrMemory_CtrlModel_DW, 0,
                sizeof(DW_Appl_DrMemory_CtrlModel_T));
  Appl_DrMemory_CtrlModel_UpDataInputInfo_Init();
  Appl_DrMemory_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
