/*
 * File: Appl_PaMemory_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_PaMemory_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:53:19 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_PaMemory_CtrlModel.h"

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

/* Named constants for Chart: '<S5>/MemoryCall' */
#define Appl_PaMemory_CtrlMod_IN_MemoryCallDefaultFeedback ((INT8U)1U)
#define Appl_PaMemory_CtrlMode_IN_MemoryCallResultFeedback ((INT8U)2U)
#define Appl_PaMemory_CtrlModel_IN_Fail ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_MemoryCallActive ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_MemoryCallInactive ((INT8U)2U)
#define Appl_PaMemory_CtrlModel_IN_MemoryCallMotorStop ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_MemoryCallRun ((INT8U)2U)
#define Appl_PaMemory_CtrlModel_IN_MessageSendFinish ((INT8U)2U)
#define Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m ((INT8U)0U)
#define Appl_PaMemory_CtrlModel_IN_Succeed ((INT8U)3U)
#define Appl_PaMemory_CtrlModel_IN_Wait ((INT8U)4U)

/* Named constants for Chart: '<S5>/MemoryRemindLogic' */
#define Appl_PaMemory_CtrlModel_IN_PositionChange1 ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_PositionNoChange1 ((INT8U)2U)

/* Named constants for Chart: '<S5>/MemorySetLogic' */
#define Appl_PaMemory_CtrlModel_IN_MemorySetActive ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_MemorySetInactive ((INT8U)2U)

/* Named constants for Chart: '<S46>/CallMemory' */
#define Appl_PaMemory_CtrlModel_IN_AcquireMemory1stPosi ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_AcquireMemory2ndPosi ((INT8U)2U)
#define Appl_PaMemory_CtrlModel_IN_AcquireMemory3rdPosi ((INT8U)3U)
#define Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i ((INT8U)0U)
#define Appl_PaMemory_CtrlModel_IN_NoneMemoryCall ((INT8U)4U)

/* Named constants for Chart: '<S47>/HmiDeal' */
#define Appl_PaMemory_CtrlModel_IN_ButtonConflict ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_NoButtonConflict ((INT8U)2U)

/* Named constants for Chart: '<S48>/MemoryRemindPrecondition' */
#define Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied ((INT8U)1U)
#define Appl_PaMemory_CtrlModel_IN_PreconditionSatisfied ((INT8U)2U)

/* Exported block signals */
enSeatMotorRunType PaMem_AnyoneRelayFaultSts;/* '<S45>/PaMem_AnyoneRelayFaultSts'
                                              * ������һ�̵���ճ�����ϱ�־&#10;0���޹���&#10;1���й���
                                              */
enSeatAutoRunSts PaMem_BackAutoRunFlag;/* '<S45>/PaMem_BackAutoRunFlag'
                                        * ���ݿ����Զ����б�־λ
                                        */
enSeatAutoRunSts PaMem_FrontAutoRunFlag;/* '<S45>/PaMem_FrontAutoRunFlag'
                                         * ����ǰ���Ƕ��Զ����б�־λ
                                         */
enSeatAutoRunSts PaMem_HeightAutoRunFlag;/* '<S45>/PaMem_HeightAutoRunFlag'
                                          * ���ݸ߶��Զ����б�־λ
                                          */
enSeatAutoRunSts PaMem_LengthAutoRunFlag;/* '<S45>/PaMem_LengthAutoRunFlag'
                                          * ���������Զ����б�־λ
                                          */
enPowerModeSts PaMem_PowerMode;        /* '<S45>/PaMem_PowerMode'
                                        * ������Դ��λ&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK
                                        */
enNapMode PaMem_NapMode;               /* '<S45>/PaMem_NapMode'
                                        * С�ģʽ&#10;0x0:Inactive&#10;0x1:�ر�С�ģʽ&#10;0x2:��С�ģʽ&#10;0x3:ERROR
                                        */
enMemSet PaMem_IVI_FRSeatMemSet1;      /* '<S45>/PaMem_IVI_FRSeatMemSet1'
                                        * ��������&#10;0����&#10;1������λ�� &#10;2�����䵱ǰλ��
                                        */
enMemSet PaMem_IVI_FRSeatMemSet2;      /* '<S45>/PaMem_IVI_FRSeatMemSet2'
                                        * ��������&#10;0����&#10;1������λ�� &#10;2�����䵱ǰλ��
                                        */
enMemSet PaMem_IVI_FRSeatMemSet3;      /* '<S45>/PaMem_IVI_FRSeatMemSet3'
                                        * ��������&#10;0����&#10;1������λ�� &#10;2�����䵱ǰλ��
                                        */
enFinalPowerMode PaMem_VoltMode;       /* '<S45>/PaMem_VoltMode'
                                        * ������ѹģʽ&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
INT16U PaMem_BackHallPosi;             /* '<S45>/PaMem_BackHallPosi'
                                        * ���ݿ�����ǰ����λ��
                                        */
INT16U PaMem_BackMem1;                 /* '<S45>/PaMem_BackMem1'
                                        * ���ݼ���1��������λ��
                                        */
INT16U PaMem_BackMem2;                 /* '<S45>/PaMem_BackMem2'
                                        * ���ݼ���2��������λ��
                                        */
INT16U PaMem_BackMem3;                 /* '<S45>/PaMem_BackMem3'
                                        * ���ݼ���3��������λ��
                                        */
INT16U PaMem_FrontHallPosi;            /* '<S45>/PaMem_FrontHallPosi'
                                        * ����ǰ���Ƕȵ�ǰ����λ��
                                        */
INT16U PaMem_FrontMem1;                /* '<S45>/PaMem_FrontMem1'
                                        * ���ݼ���1ǰ���ǶȻ���λ��
                                        */
INT16U PaMem_FrontMem2;                /* '<S45>/PaMem_FrontMem2'
                                        * ���ݼ���2ǰ���ǶȻ���λ��
                                        */
INT16U PaMem_FrontMem3;                /* '<S45>/PaMem_FrontMem3'
                                        * ���ݼ���3ǰ���ǶȻ���λ��
                                        */
INT16U PaMem_GetRecoverDefaultFlag;    /* '<S45>/PaMem_GetRecoverDefaultFlag'
                                        *  �ָ���������
                                        */
INT16U PaMem_HeightHallPosi;           /* '<S45>/PaMem_HeightHallPosi'
                                        * ���ݸ߶ȵ�ǰ����λ��
                                        */
INT16U PaMem_HeightMem1;               /* '<S45>/PaMem_HeightMem1'
                                        * ���ݼ���1�߶Ȼ���λ��
                                        */
INT16U PaMem_HeightMem2;               /* '<S45>/PaMem_HeightMem2'
                                        * ���ݼ���2�߶Ȼ���λ��
                                        */
INT16U PaMem_HeightMem3;               /* '<S45>/PaMem_HeightMem3'
                                        * ���ݼ���3�߶Ȼ���λ��
                                        */
INT16U PaMem_LengthHallPosi;           /* '<S45>/PaMem_LengthHallPosi'
                                        * ��������ǰ����λ��
                                        */
INT16U PaMem_LengthMem1;               /* '<S45>/PaMem_LengthMem1'
                                        * ���ݼ���1�������λ��
                                        */
INT16U PaMem_LengthMem2;               /* '<S45>/PaMem_LengthMem2'
                                        * ���ݼ���2�������λ��
                                        */
INT16U PaMem_LengthMem3;               /* '<S45>/PaMem_LengthMem3'
                                        * ���ݼ���3�������λ��
                                        */
INT8U PaMem_AdjustEnable;              /* '<S45>/PaMem_AdjustEnable'
                                        * �������ε���:&#10;0x00:manual&#10;0x01:Six way motor&#10;0x02:Twelve way motor
                                        */
INT8U PaMem_BackLockFault;             /* '<S45>/PaMem_BackLockFault'
                                        * �������ο�����ת&#10;0���޶�ת��&#10;1���Ѷ�ת
                                        */
INT8U PaMem_CurrentMoveType;           /* '<S45>/PaMem_CurrentMoveType'
                                        * ���ݵ����ǰ�������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����
                                        */
INT8U PaMem_DtcAnyoneHallFaultSts;     /* '<S45>/PaMem_DtcAnyoneHallFaultSts'
                                        * ������һ�����������&#10;0����&#10;1����
                                        */
INT8U PaMem_FRSeatPosMsg;              /* '<S45>/PaMem_FRSeatPosMsg'
                                        * ������ʾ��������&#10;0���ޱ仯&#10;1���б仯
                                        */
INT8U PaMem_FrontLockFault;            /* '<S45>/PaMem_FrontLockFault'
                                        * �����������ж�ת&#10;0���޶�ת��&#10;1���Ѷ�ת
                                        */
INT8U PaMem_Gear_PN_FlagOut;           /* '<S45>/PaMem_Gear_PN_FlagOut'
                                        * PN����־λ&#10;0����PN��&#10;1��PN��
                                        */
INT8U PaMem_HeightLockFault;           /* '<S45>/PaMem_HeightLockFault'
                                        * �������θ߶ȶ�ת&#10;0���޶�ת��&#10;1���Ѷ�ת
                                        */
INT8U PaMem_LengthLockFault;           /* '<S45>/PaMem_LengthLockFault'
                                        * �������������ת&#10;0���޶�ת��&#10;1���Ѷ�ת
                                        */
INT8U PaMem_PABackSwitch;              /* '<S45>/PaMem_PABackSwitch'
                                        * ������������
                                        */
INT8U PaMem_PAFrontSwitch;             /* '<S45>/PaMem_PAFrontSwitch'
                                        * ���п�������
                                        */
INT8U PaMem_PAHeightSwitch;            /* '<S45>/PaMem_PAHeightSwitch'
                                        * �߶ȿ�������
                                        */
INT8U PaMem_PALengthSwitch;            /* '<S45>/PaMem_PALengthSwitch'
                                        * ���򿪹�����
                                        */
INT8U PaMem_PaAnyoneLockFaultSts;      /* '<S45>/PaMem_PaAnyoneLockFaultSts'
                                        * ������һ��ת״̬&#10;0����Ч&#10;2����Ч
                                        */
INT8U PaMem_PaMemoryConfig;            /* '<S45>/PaMem_PaMemoryConfig'
                                        * ���ݼ���ӭ������
                                        */
INT8U PaMem_SeatLearnResult;           /* '<S45>/PaMem_SeatLearnResult'
                                        * ��������ѧϰ���&#10;0��δѧϰ��&#10;1����ѧϰ
                                        */
INT8U PaMem_SeatMemory1Valid;          /* '<S45>/PaMem_SeatMemory1Valid'
                                        * ����λ����Ч��־&#10;0����Ч&#10;1����Ч
                                        */
INT8U PaMem_SeatMemory2Valid;          /* '<S45>/PaMem_SeatMemory2Valid'
                                        * ����λ����Ч��־&#10;0����Ч&#10;1����Ч
                                        */
INT8U PaMem_SeatMemory3Valid;          /* '<S45>/PaMem_SeatMemory3Valid'
                                        * ����λ����Ч��־&#10;0����Ч&#10;1����Ч
                                        */
INT8U PaMem_SpeedLessThan5_Flag;       /* '<S45>/PaMem_SpeedLessThan5_Flag'
                                        * ����С��5&#10;0����&#10;1������
                                        */
INT8U PaMem_VoltSatisfy;               /* '<S45>/PaMem_VoltSatisfy'
                                        * ������ڵ�ѹ�Ƿ����㣺&#10;0��������&#10;1������
                                        */

/* Block signals (default storage) */
B_Appl_PaMemory_CtrlModel_T Appl_PaMemory_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_PaMemory_CtrlModel_T Appl_PaMemory_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_PaMemory_CtrlModel_T Appl_PaMemory_CtrlModel_M_;
RT_MODEL_Appl_PaMemory_CtrlModel_T *const Appl_PaMemory_CtrlModel_M =
  &Appl_PaMemory_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT8U CAL_PaMem_100MS = 10U;/* ��ʱ100ms */
const volatile INT8U CAL_PaMem_90MS = 50U;/* ��ʱ90ms */
static void Appl_PaMemory_CtrlModel_MemCallWaitFBFunc_Init(enMemCallFb
  *rty_CallFB1, enMemCallFb *rty_CallFB2, enMemCallFb *rty_CallFB3);
static void Appl_PaMemory_CtrlModel_MemCallWaitFBFunc(INT8U rtu_ButtonNum,
  enMemCallFb rtu_FBSts, enMemCallFb *rty_CallFB1, enMemCallFb *rty_CallFB2,
  enMemCallFb *rty_CallFB3);
static void Appl_PaMemory_CtrlModel_PosiCompareFunc_Init(INT8U *rty_Result);
static void Appl_PaMemory_CtrlModel_PosiCompareFunc(INT16U rtu_MemH, INT16U
  rtu_MenL, INT16U rtu_MemB, INT16U rtu_MemF, INT16U rtu_CurrentH, INT16U
  rtu_CurrentL, INT16U rtu_CurrentB, INT16U rtu_CurrentF, INT8U rtu_PosiReq,
  INT8U *rty_Result);
static void Appl_PaMemory_CtrlModel_SetCanSendEvent(void);
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem1Sts(void);
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem2Sts(void);
static void Appl_PaMemory_CtrlModel_GetCanSendEvent(void);
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem3Sts(void);
static void Appl_PaMemory_CtrlModel_SetCanSendEvent_g(void);
static void Appl_PaMemory_CtrlModel_GetCanSendEvent_b(void);
static void Appl_PaMemory_CtrlModel_SetCanSendMemStsAndMsg(void);
static void Appl_PaMemory_CtrlModel_LogicCtrl_Init(void);
static void Appl_PaMemory_CtrlModel_LogicCtrl(void);
static void Appl_PaMemory_CtrlModel_RTE(void);
static void Appl_PaMemory_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_PaMemory_CtrlModel_UpDataInputInfo(void);
static void Appl_PaMemory_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_PaMemory_CtrlModel_inner_default_Wait(void);
static void Appl_PaMemory_CtrlModel_inner_default_Wait_i(void);

/* System initialize for function-call system: '<S6>/MemCallWaitFBFunc' */
static void Appl_PaMemory_CtrlModel_MemCallWaitFBFunc_Init(enMemCallFb
  *rty_CallFB1, enMemCallFb *rty_CallFB2, enMemCallFb *rty_CallFB3)
{
  *rty_CallFB1 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB2 = enMemCallFb_EN_MemCallFb_NULL;
  *rty_CallFB3 = enMemCallFb_EN_MemCallFb_NULL;
}

/* Output and update for function-call system: '<S6>/MemCallWaitFBFunc' */
static void Appl_PaMemory_CtrlModel_MemCallWaitFBFunc(INT8U rtu_ButtonNum,
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
static void Appl_PaMemory_CtrlModel_SetCanSendEvent(void)
{
  Rte_SetCanEvent_0x3B2(Appl_PaMemory_CtrlModel_B.In1_l);
}

/* Output and update for function-call system: '<S6>/SetCanSendFRSeatMem1Sts' */
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem1Sts(void)
{
  CanTx_0x3B2_DSM1_FRSeatMem1Sts(Appl_PaMemory_CtrlModel_B.In1_h);
}

/* Output and update for function-call system: '<S6>/SetCanSendFRSeatMem2Sts' */
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem2Sts(void)
{
  CanTx_0x3B2_DSM2_FRSeatMem2Sts(Appl_PaMemory_CtrlModel_B.In1_ny);
}

/* Output and update for function-call system: '<S6>/GetCanSendEvent' */
static void Appl_PaMemory_CtrlModel_GetCanSendEvent(void)
{
  Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_m =
    Rte_GetCanEventSendTimes_0x3B2( );
}

/* Output and update for function-call system: '<S6>/SetCanSendFRSeatMem3Sts' */
static void Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem3Sts(void)
{
  CanTx_0x3B2_DSM2_FRSeatMem3Sts(Appl_PaMemory_CtrlModel_B.In1_lu);
}

/* Output and update for function-call system: '<S8>/SetCanSendEvent' */
static void Appl_PaMemory_CtrlModel_SetCanSendEvent_g(void)
{
  Rte_SetCanEvent_0x3B2(Appl_PaMemory_CtrlModel_B.In1);
}

/* Output and update for function-call system: '<S8>/GetCanSendEvent' */
static void Appl_PaMemory_CtrlModel_GetCanSendEvent_b(void)
{
  Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi = Rte_GetCanEventSendTimes_0x3B2
    ( );
}

/* Output and update for function-call system: '<S8>/SetCanSendMemStsAndMsg' */
static void Appl_PaMemory_CtrlModel_SetCanSendMemStsAndMsg(void)
{
  CanTx_0x3B2_DSM_FRSeatMemStsAndMsg(Appl_PaMemory_CtrlModel_B.In1_n);
}

/* Function for Chart: '<S5>/MemoryCall' */
static void Appl_PaMemory_CtrlModel_inner_default_Wait(void)
{
  /* ��ȡ�������1Ŀ��λ�� */
  if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call1)
  {
    Appl_PaMemory_CtrlModel_DW.MemoryButtonNum =
      enMemCallFb_EN_MemCallFb_Succeed;
    Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_PaMemory_CtrlModel_B.MemoryValid;
    Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_PaMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryBackPosi;
    Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /* ��ȡ�������2Ŀ��λ�� */
  if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call2)
  {
    Appl_PaMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_Faild;
    Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_PaMemory_CtrlModel_B.MemoryValid;
    Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_PaMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryBackPosi;
    Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /* ��ȡ�������3Ŀ��λ�� */
  if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Call3)
  {
    Appl_PaMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_Wait;
    Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq =
      Appl_PaMemory_CtrlModel_B.MemoryValid;
    Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryHeightPosi;
    Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryLengthPosi;
    Appl_PaMemory_CtrlModel_B.SeatBackPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryBackPosi;
    Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq =
      Appl_PaMemory_CtrlModel_B.MemoryFrontPosi;
  }

  /*  ���ò����� ֹͣ����˶�  */
  if ((Appl_PaMemory_CtrlModel_B.MemCallPC_Flag == ((BOOL)FALSE)) ||
      (Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq == ((BOOL)FALSE)))
  {
    Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
    Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatBackPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
  }
  else
  {
    Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_Wait;
  }
}

/* Function for Chart: '<S5>/MemorySetLogic' */
static void Appl_PaMemory_CtrlModel_inner_default_Wait_i(void)
{
  INT32S tmp;

  /* ��ʼǰ������������ */
  if (Appl_PaMemory_CtrlModel_B.MemSetPC_Flag == ((BOOL)FALSE))
  {
    Appl_PaMemory_CtrlModel_DW.WaitTimer = 0U;
  }
  else
  {
    /* ��������1 */
    if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set1)
    {
      Appl_PaMemory_CtrlModel_DW.FRTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S1;

      /*  ���书��ʹ��  */
      if (PaMem_AdjustEnable == ((BOOL)TRUE))
      {
        Appl_PaMemory_CtrlModel_B.CurrentH_h = PaMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem1_Height,
          Appl_PaMemory_CtrlModel_B.CurrentH_h);
        Appl_PaMemory_CtrlModel_B.CurrentL_b = PaMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem1_Length,
          Appl_PaMemory_CtrlModel_B.CurrentL_b);
        Appl_PaMemory_CtrlModel_B.CurrentB_o = PaMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem1_Back,
          Appl_PaMemory_CtrlModel_B.CurrentB_o);
        Appl_PaMemory_CtrlModel_B.CurrentF_e = PaMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem1_Front,
          Appl_PaMemory_CtrlModel_B.CurrentF_e);
        Appl_PaMemory_CtrlModel_B.Sts_n = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_PaMem1_ValidFlag,
          Appl_PaMemory_CtrlModel_B.Sts_n);
      }
    }

    /* ��������2 */
    if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set2)
    {
      Appl_PaMemory_CtrlModel_DW.FRTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S2;

      /*  ���书��ʹ��  */
      if (PaMem_AdjustEnable == ((BOOL)TRUE))
      {
        Appl_PaMemory_CtrlModel_B.CurrentH_ke = PaMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem2_Height,
          Appl_PaMemory_CtrlModel_B.CurrentH_ke);
        Appl_PaMemory_CtrlModel_B.CurrentL_l = PaMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem2_Length,
          Appl_PaMemory_CtrlModel_B.CurrentL_l);
        Appl_PaMemory_CtrlModel_B.CurrentB_c = PaMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem2_Back,
          Appl_PaMemory_CtrlModel_B.CurrentB_c);
        Appl_PaMemory_CtrlModel_B.CurrentF_h = PaMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem2_Front,
          Appl_PaMemory_CtrlModel_B.CurrentF_h);
        Appl_PaMemory_CtrlModel_B.Sts_g = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_PaMem2_ValidFlag,
          Appl_PaMemory_CtrlModel_B.Sts_g);
      }
    }

    /* ��������3 */
    if (Appl_PaMemory_CtrlModel_B.SeatMemBtn == enMemBtn_EN_MemBtn_Set3)
    {
      Appl_PaMemory_CtrlModel_DW.FRTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_S3;

      /*  ���书��ʹ��  */
      if (PaMem_AdjustEnable == ((BOOL)TRUE))
      {
        Appl_PaMemory_CtrlModel_B.CurrentH_k = PaMem_HeightHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem3_Height,
          Appl_PaMemory_CtrlModel_B.CurrentH_k);
        Appl_PaMemory_CtrlModel_B.CurrentL_g = PaMem_LengthHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem3_Length,
          Appl_PaMemory_CtrlModel_B.CurrentL_g);
        Appl_PaMemory_CtrlModel_B.CurrentB_l = PaMem_BackHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem3_Back,
          Appl_PaMemory_CtrlModel_B.CurrentB_l);
        Appl_PaMemory_CtrlModel_B.CurrentF_a = PaMem_FrontHallPosi;
        Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem3_Front,
          Appl_PaMemory_CtrlModel_B.CurrentF_a);
        Appl_PaMemory_CtrlModel_B.Sts = ((BOOL)TRUE);
        Srvl_SetMemIndexDataU8(EN_MemIndex_PaMem3_ValidFlag,
          Appl_PaMemory_CtrlModel_B.Sts);
      }
    }

    Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;

    /* ʹ����ʱ����EEPROM������� */
    if (Appl_PaMemory_CtrlModel_DW.WaitTimer < CAL_PaMem_100MS)
    {
      tmp = Appl_PaMemory_CtrlModel_DW.WaitTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_PaMemory_CtrlModel_DW.WaitTimer = (INT8U)tmp;
    }
    else
    {
      Appl_PaMemory_CtrlModel_DW.WaitTimer = CAL_PaMem_100MS;
    }
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaMemory_CtrlModel_LogicCtrl_Init(void)
{
  enMemCallFb CallFB1;
  enMemCallFb CallFB2;
  enMemCallFb CallFB3;
  Appl_PaMemory_CtrlModel_DW.is_MemoryCallLogic =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.is_active_c8_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_NULL;
  Appl_PaMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_NULL;
  Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = 0U;
  Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = 0U;
  Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
  Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq = 0U;
  Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
  Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
  Appl_PaMemory_CtrlModel_B.SeatBackPosiReq = 0U;
  Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
  Appl_PaMemory_CtrlModel_B.MemCallStopReason = enMemStopCause_EN_MemStop_NULL;
  Appl_PaMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_PaMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_PaMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
  Appl_PaMemory_CtrlModel_MemCallWaitFBFunc_Init(&CallFB1, &CallFB2, &CallFB3);
  Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.is_active_c3_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_DW.is_c3_Appl_PaMemory_CtrlModel =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag = 0U;
  Appl_PaMemory_CtrlModel_DW.WaitTimer = 0U;
  Appl_PaMemory_CtrlModel_DW.FRTempSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
  Appl_PaMemory_CtrlModel_DW.WaitTimeCnt = 0U;
  Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
  Appl_PaMemory_CtrlModel_B.MemSetStopReason = enMemStopCause_EN_MemStop_NULL;
  Appl_PaMemory_CtrlModel_DW.is_active_c5_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_DW.is_c5_Appl_PaMemory_CtrlModel =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_PaMemory_CtrlModel_B.FRSeatPosMsg = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaMemory_CtrlModel_LogicCtrl(void)
{
  enMemBtn SeatMemBtn_prev_c;
  INT8U PaMem_CurrentMoveType_prev;
  INT32S tmp;
  BOOL guard1 = false;
  BOOL guard2 = false;
  Appl_PaMemory_CtrlModel_B.PreMemRemindStop_d =
    Appl_PaMemory_CtrlModel_B.PreMemRemindStop;
  SeatMemBtn_prev_c = Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l;
  Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l =
    Appl_PaMemory_CtrlModel_B.SeatMemBtn;
  if (Appl_PaMemory_CtrlModel_DW.is_active_c8_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c8_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_MemoryCallLogic =
      Appl_PaMemory_CtrlModel_IN_MemoryCallInactive;
    Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_DW.MemoryButtonNum = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = ((BOOL)FALSE);
    Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
    Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatBackPosiReq = 0U;
    Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
    Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
      Appl_PaMemory_CtrlMod_IN_MemoryCallDefaultFeedback;
    Appl_PaMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
  }
  else
  {
    if (Appl_PaMemory_CtrlModel_DW.is_MemoryCallLogic ==
        Appl_PaMemory_CtrlModel_IN_MemoryCallActive)
    {
      if (Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j == ((BOOL)TRUE))
      {
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
          Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallLogic =
          Appl_PaMemory_CtrlModel_IN_MemoryCallInactive;
        Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
          enMemCallFb_EN_MemCallFb_NULL;
        Appl_PaMemory_CtrlModel_DW.MemoryButtonNum =
          enMemCallFb_EN_MemCallFb_NULL;
        Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = ((BOOL)FALSE);
        Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq = ((BOOL)FALSE);
        Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq = 0U;
        Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq = 0U;
        Appl_PaMemory_CtrlModel_B.SeatBackPosiReq = 0U;
        Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq = 0U;
      }
      else
      {
        switch (Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive)
        {
         case Appl_PaMemory_CtrlModel_IN_Fail:
          /* Srvl_CAN�������ķ������ || ��ʱ90ms */
          if (Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m >= 2)
          {
            Appl_PaMemory_CtrlModel_GetCanSendEvent();
            if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
            {
              Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_PaMemory_CtrlModel_IN_MessageSendFinish;
              Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = ((BOOL)TRUE);
              Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
                enMemCallFb_EN_MemCallFb_NULL;
            }
            else
            {
              /* SetCanSendEvent(0x3B2); */
              tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = (INT16U)tmp;
            }
          }
          else
          {
            /* SetCanSendEvent(0x3B2); */
            tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = (INT16U)tmp;
          }
          break;

         case Appl_PaMemory_CtrlModel_IN_MessageSendFinish:
          break;

         case Appl_PaMemory_CtrlModel_IN_Succeed:
          /* Srvl_CAN�������ķ������ || ��ʱ90ms */
          if (Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m >= 2)
          {
            Appl_PaMemory_CtrlModel_GetCanSendEvent();
            if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
            {
              Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_PaMemory_CtrlModel_IN_MessageSendFinish;
              Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = ((BOOL)TRUE);
              Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
                enMemCallFb_EN_MemCallFb_NULL;
            }
            else
            {
              /* SetCanSendEvent(0x3B2); */
              tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = (INT16U)tmp;
            }
          }
          else
          {
            /* SetCanSendEvent(0x3B2); */
            tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = (INT16U)tmp;
          }
          break;

         default:
          /* �������ǰ������������ */
          if (Appl_PaMemory_CtrlModel_B.MemCallPC_Flag == ((BOOL)FALSE))
          {
            Appl_PaMemory_CtrlModel_B.MemCallStopReason =
              Appl_PaMemory_CtrlModel_B.PreMemCallStop;
            Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
              Appl_PaMemory_CtrlModel_IN_Fail;
            Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
              enMemCallFb_EN_MemCallFb_Faild;
            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = 0U;
          }
          else
          {
            /*  λ��δ����  */
            if (Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq == ((BOOL)FALSE))
            {
              Appl_PaMemory_CtrlModel_B.MemCallStopReason =
                enMemStopCause_EN_MemStop_PosiError;
              Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
                Appl_PaMemory_CtrlModel_IN_MessageSendFinish;
              Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag_j = ((BOOL)TRUE);
              Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
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
               /MemCallStopReason = 0xC:enMotorRunError
                 PaMem_HeightAutoRunFlag == enSeatAutoRunSts.EN_SEAT_FAIL ||   || PaMem_FrontAutoRunFlag == enSeatAutoRunSts.EN_SEAT_FAIL */
              if ((PaMem_LengthAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL) ||
                  (PaMem_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_FAIL))
              {
                Appl_PaMemory_CtrlModel_B.MemCallStopReason =
                  enMemStopCause_EN_MemStop_MotorRunErr;
                Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
                  Appl_PaMemory_CtrlModel_IN_Fail;
                Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
                  enMemCallFb_EN_MemCallFb_Faild;
                Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = 0U;
              }
              else
              {
                /* (�߶��Զ����гɹ���־λ == TRUE || �߶ȶ�ת)
                   && (�����Զ����гɹ���־λ == TRUE || �����ת)
                   && (�����Զ����гɹ���־λ == TRUE || ������ת)
                   && (ǰ���Զ����гɹ���־λ == TRUE || ǰ����ת)
                   (PaMem_HeightAutoRunFlag == enSeatAutoRunSts.EN_SEAT_SUCCESS || PaMem_HeightLockFault == TRUE) &&   */
                if (((PaMem_LengthAutoRunFlag ==
                      enSeatAutoRunSts_EN_SEAT_SUCCESS) ||
                     (PaMem_LengthLockFault == ((BOOL)TRUE))) &&
                    ((PaMem_BackAutoRunFlag == enSeatAutoRunSts_EN_SEAT_SUCCESS)
                     || (PaMem_BackLockFault == ((BOOL)TRUE))))
                {
                  /* && (PaMem_FrontAutoRunFlag == enSeatAutoRunSts.EN_SEAT_SUCCESS || PaMem_FrontLockFault == TRUE) */
                  Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
                    Appl_PaMemory_CtrlModel_IN_Succeed;
                  Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts =
                    enMemCallFb_EN_MemCallFb_Succeed;
                  Appl_PaMemory_CtrlModel_DW.WaitTimeCnt_m = 0U;
                }
                else
                {
                  Appl_PaMemory_CtrlModel_inner_default_Wait();
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
      if (((SeatMemBtn_prev_c != Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l) &&
           (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l ==
            enMemBtn_EN_MemBtn_Call1)) || ((SeatMemBtn_prev_c !=
            Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l) &&
           (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l ==
            enMemBtn_EN_MemBtn_Call2)) || ((SeatMemBtn_prev_c !=
            Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l) &&
           (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start_l ==
            enMemBtn_EN_MemBtn_Call3)))
      {
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallLogic =
          Appl_PaMemory_CtrlModel_IN_MemoryCallActive;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallActive =
          Appl_PaMemory_CtrlModel_IN_Wait;
        Appl_PaMemory_CtrlModel_inner_default_Wait();
      }
      else
      {
        /* SeatMemBtn��ΪCallButton2 */
        /* SeatMemBtn��ΪCallButton3 */
      }
    }

    if (Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback ==
        Appl_PaMemory_CtrlMod_IN_MemoryCallDefaultFeedback)
    {
      /* ������ÿ�ʼ���� */
      if (Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts ==
          enMemCallFb_EN_MemCallFb_Wait)
      {
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
          Appl_PaMemory_CtrlMode_IN_MemoryCallResultFeedback;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_PaMemory_CtrlModel_IN_MemoryCallRun;
        Appl_PaMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_PaMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_PaMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem3StsFb);
      }
      else
      {
        /* �������ֱ�ӽ��� */
        if ((Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts ==
             enMemCallFb_EN_MemCallFb_Succeed) ||
            (Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts ==
             enMemCallFb_EN_MemCallFb_Faild))
        {
          Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
            Appl_PaMemory_CtrlMode_IN_MemoryCallResultFeedback;
          Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
            Appl_PaMemory_CtrlModel_IN_MemoryCallMotorStop;
          Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
          Appl_PaMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
            Appl_PaMemory_CtrlModel_DW.MemoryButtonNum,
            Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts,
            &Appl_PaMemory_CtrlModel_B.SeatMem1StsFb,
            &Appl_PaMemory_CtrlModel_B.SeatMem2StsFb,
            &Appl_PaMemory_CtrlModel_B.SeatMem3StsFb);
          Appl_PaMemory_CtrlModel_B.In1_h = (INT16U)
            Appl_PaMemory_CtrlModel_B.SeatMem1StsFb;
          Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem1Sts();
          Appl_PaMemory_CtrlModel_B.In1_ny = (INT16U)
            Appl_PaMemory_CtrlModel_B.SeatMem2StsFb;
          Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem2Sts();
          Appl_PaMemory_CtrlModel_B.In1_lu = (INT16U)
            Appl_PaMemory_CtrlModel_B.SeatMem3StsFb;
          Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem3Sts();
          Appl_PaMemory_CtrlModel_B.In1_l = (INT16U)0x3B2;
          Appl_PaMemory_CtrlModel_SetCanSendEvent();
        }
      }
    }
    else if (Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback ==
             Appl_PaMemory_CtrlModel_IN_MemoryCallMotorStop)
    {
      /* ��ʱ90ms */
      guard1 = false;
      if (Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt >= CAL_PaMem_90MS)
      {
        guard1 = true;
      }
      else
      {
        Appl_PaMemory_CtrlModel_GetCanSendEvent();
        if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_m == ((BOOL)TRUE))
        {
          guard1 = true;
        }
        else
        {
          tmp = Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt = (INT16U)tmp;
        }
      }

      if (guard1)
      {
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallMessageFeedback =
          Appl_PaMemory_CtrlMod_IN_MemoryCallDefaultFeedback;
        Appl_PaMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
        Appl_PaMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
        Appl_PaMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
      }
    }
    else
    {
      /* ������ý��� */
      if ((Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts ==
           enMemCallFb_EN_MemCallFb_Succeed) ||
          (Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts ==
           enMemCallFb_EN_MemCallFb_Faild))
      {
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallResultFeedback =
          Appl_PaMemory_CtrlModel_IN_MemoryCallMotorStop;
        Appl_PaMemory_CtrlModel_DW.FbWaitTimeCnt = 0U;
        Appl_PaMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_PaMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_PaMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem3StsFb);
        Appl_PaMemory_CtrlModel_B.In1_h = (INT16U)
          Appl_PaMemory_CtrlModel_B.SeatMem1StsFb;
        Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem1Sts();
        Appl_PaMemory_CtrlModel_B.In1_ny = (INT16U)
          Appl_PaMemory_CtrlModel_B.SeatMem2StsFb;
        Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem2Sts();
        Appl_PaMemory_CtrlModel_B.In1_lu = (INT16U)
          Appl_PaMemory_CtrlModel_B.SeatMem3StsFb;
        Appl_PaMemory_CtrlModel_SetCanSendFRSeatMem3Sts();
        Appl_PaMemory_CtrlModel_B.In1_l = (INT16U)0x3B2;
        Appl_PaMemory_CtrlModel_SetCanSendEvent();
      }
      else
      {
        Appl_PaMemory_CtrlModel_MemCallWaitFBFunc((INT8U)
          Appl_PaMemory_CtrlModel_DW.MemoryButtonNum,
          Appl_PaMemory_CtrlModel_DW.MemoryCallFbSts,
          &Appl_PaMemory_CtrlModel_B.SeatMem1StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem2StsFb,
          &Appl_PaMemory_CtrlModel_B.SeatMem3StsFb);
      }
    }
  }

  SeatMemBtn_prev_c = Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start;
  Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start =
    Appl_PaMemory_CtrlModel_B.SeatMemBtn;
  if (Appl_PaMemory_CtrlModel_DW.is_active_c3_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c3_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_c3_Appl_PaMemory_CtrlModel =
      Appl_PaMemory_CtrlModel_IN_MemorySetInactive;
    Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
    Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)FALSE);
  }
  else if (Appl_PaMemory_CtrlModel_DW.is_c3_Appl_PaMemory_CtrlModel ==
           Appl_PaMemory_CtrlModel_IN_MemorySetActive)
  {
    if (Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag == ((BOOL)TRUE))
    {
      Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
        Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_m;
      Appl_PaMemory_CtrlModel_DW.is_c3_Appl_PaMemory_CtrlModel =
        Appl_PaMemory_CtrlModel_IN_MemorySetInactive;
      Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)FALSE);
    }
    else
    {
      guard1 = false;
      guard2 = false;
      switch (Appl_PaMemory_CtrlModel_DW.is_MemorySetActive)
      {
       case Appl_PaMemory_CtrlModel_IN_Fail:
        /* Srvl_CAN�������ķ������ || ��ʱ90ms */
        if (Appl_PaMemory_CtrlModel_DW.WaitTimeCnt >= CAL_PaMem_90MS)
        {
          guard1 = true;
        }
        else
        {
          Appl_PaMemory_CtrlModel_GetCanSendEvent_b();
          if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi == ((BOOL)TRUE))
          {
            guard1 = true;
          }
          else
          {
            tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt = (INT16U)tmp;
          }
        }
        break;

       case Appl_PaMemory_CtrlModel_IN_MessageSendFinish:
        break;

       case Appl_PaMemory_CtrlModel_IN_Succeed:
        /* Srvl_CAN�������ķ������ || ��ʱ90ms */
        if (Appl_PaMemory_CtrlModel_DW.WaitTimeCnt >= CAL_PaMem_90MS)
        {
          guard2 = true;
        }
        else
        {
          Appl_PaMemory_CtrlModel_GetCanSendEvent_b();
          if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi == ((BOOL)TRUE))
          {
            guard2 = true;
          }
          else
          {
            tmp = Appl_PaMemory_CtrlModel_DW.WaitTimeCnt + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt = (INT16U)tmp;
          }
        }
        break;

       default:
        /* ǰ������������ */
        if (Appl_PaMemory_CtrlModel_B.MemSetPC_Flag == ((BOOL)FALSE))
        {
          Appl_PaMemory_CtrlModel_B.MemSetStopReason =
            Appl_PaMemory_CtrlModel_B.PreMemSetStop;
          Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
            Appl_PaMemory_CtrlModel_IN_Fail;
          Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts =
            enMemSetFb_EN_MemSetFb_Fail;
          Appl_PaMemory_CtrlModel_DW.WaitTimer = 0U;
          Appl_PaMemory_CtrlModel_DW.WaitTimeCnt = 0U;
          Appl_PaMemory_CtrlModel_B.In1_n = (INT16U)
            Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts;
          Appl_PaMemory_CtrlModel_SetCanSendMemStsAndMsg();
          Appl_PaMemory_CtrlModel_B.In1 = (INT16U)0x3B2;
          Appl_PaMemory_CtrlModel_SetCanSendEvent_g();
        }
        else
        {
          /* �洢���� */
          if (Appl_PaMemory_CtrlModel_DW.WaitTimer >= CAL_PaMem_100MS)
          {
            Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
              Appl_PaMemory_CtrlModel_IN_Succeed;
            Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts =
              Appl_PaMemory_CtrlModel_DW.FRTempSeatMemSetSts;
            Appl_PaMemory_CtrlModel_DW.WaitTimer = 0U;
            Appl_PaMemory_CtrlModel_DW.WaitTimeCnt = 0U;
            Appl_PaMemory_CtrlModel_B.In1_n = (INT16U)
              Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts;
            Appl_PaMemory_CtrlModel_SetCanSendMemStsAndMsg();
            Appl_PaMemory_CtrlModel_B.In1 = (INT16U)0x3B2;
            Appl_PaMemory_CtrlModel_SetCanSendEvent_g();
          }
          else
          {
            Appl_PaMemory_CtrlModel_inner_default_Wait_i();
          }
        }
        break;
      }

      if (guard2)
      {
        Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
          Appl_PaMemory_CtrlModel_IN_MessageSendFinish;
        Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)TRUE);
        Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      }

      if (guard1)
      {
        Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
          Appl_PaMemory_CtrlModel_IN_MessageSendFinish;
        Appl_PaMemory_CtrlModel_DW.MsgSendFinishedFlag = ((BOOL)TRUE);
        Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
      }
    }
  }
  else
  {
    /* SeatMemBtn��ΪMemorizeButton1 */
    if (((SeatMemBtn_prev_c != Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start) &&
         (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start == enMemBtn_EN_MemBtn_Set1))
        || ((SeatMemBtn_prev_c != Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start) &&
            (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start ==
             enMemBtn_EN_MemBtn_Set2)) || ((SeatMemBtn_prev_c !=
          Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start) &&
         (Appl_PaMemory_CtrlModel_DW.SeatMemBtn_start == enMemBtn_EN_MemBtn_Set3)))
    {
      Appl_PaMemory_CtrlModel_DW.is_c3_Appl_PaMemory_CtrlModel =
        Appl_PaMemory_CtrlModel_IN_MemorySetActive;
      Appl_PaMemory_CtrlModel_DW.is_MemorySetActive =
        Appl_PaMemory_CtrlModel_IN_Wait;
      Appl_PaMemory_CtrlModel_inner_default_Wait_i();
    }
    else
    {
      /* SeatMemBtn��ΪMemorizeButton2 */
      /* SeatMemBtn��ΪMemorizeButton3 */
    }
  }

  PaMem_CurrentMoveType_prev =
    Appl_PaMemory_CtrlModel_DW.PaMem_CurrentMoveType_start;
  Appl_PaMemory_CtrlModel_DW.PaMem_CurrentMoveType_start = PaMem_CurrentMoveType;
  if (Appl_PaMemory_CtrlModel_DW.is_active_c5_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c5_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_c5_Appl_PaMemory_CtrlModel =
      Appl_PaMemory_CtrlModel_IN_PositionNoChange1;
    Appl_PaMemory_CtrlModel_B.FRSeatPosMsg = ((BOOL)FALSE);
  }
  else if (Appl_PaMemory_CtrlModel_DW.is_c5_Appl_PaMemory_CtrlModel ==
           Appl_PaMemory_CtrlModel_IN_PositionChange1)
  {
    /* �ָ�������־λ == TRUE  */
    guard1 = false;
    if ((PaMem_GetRecoverDefaultFlag == ((BOOL)TRUE)) ||
        (Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag == ((BOOL)FALSE)))
    {
      guard1 = true;
    }
    else
    {
      /* ��ʱʱ�� */
      Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_a =
        Rte_GetCanEventSendTimes_0x3B2( );
      if (Appl_PaMemory_CtrlModel_B.DrMem_FrontHallPosi_a == ((BOOL)TRUE))
      {
        guard1 = true;
      }
    }

    if (guard1)
    {
      Appl_PaMemory_CtrlModel_DW.is_c5_Appl_PaMemory_CtrlModel =
        Appl_PaMemory_CtrlModel_IN_PositionNoChange1;
      Appl_PaMemory_CtrlModel_B.FRSeatPosMsg = ((BOOL)FALSE);
    }
  }
  else
  {
    /* ���㡾ǰ��������&&����������1��
       �˶��������ֶ����ڱ�Ϊ��ֹ
       && MemRemindPC_Flag == TRUE
       &&(Result1st != TRUE
       || Result2nd != TRUE
       || Result3rd != TRUE)   */
    if ((PaMem_CurrentMoveType_prev !=
         Appl_PaMemory_CtrlModel_DW.PaMem_CurrentMoveType_start) &&
        (PaMem_CurrentMoveType_prev == (INT32S)
         enSeatMotorRunType_EN_ManualEnable) && (PaMem_CurrentMoveType ==
         (INT32S)enSeatMotorRunType_EN_NULL) &&
        (Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag == ((BOOL)TRUE)) &&
        ((Appl_PaMemory_CtrlModel_B.Result1st != 2) ||
         (Appl_PaMemory_CtrlModel_B.Result2nd != 2) ||
         (Appl_PaMemory_CtrlModel_B.Result3rd != 2)) &&
        (Appl_PaMemory_CtrlModel_B.Result1st != ((BOOL)TRUE)) &&
        (Appl_PaMemory_CtrlModel_B.Result2nd != ((BOOL)TRUE)) &&
        (Appl_PaMemory_CtrlModel_B.Result3rd != ((BOOL)TRUE)))
    {
      Appl_PaMemory_CtrlModel_DW.is_c5_Appl_PaMemory_CtrlModel =
        Appl_PaMemory_CtrlModel_IN_PositionChange1;
      Appl_PaMemory_CtrlModel_B.FRSeatPosMsg = ((BOOL)TRUE);
      Appl_PaMemory_CtrlModel_B.In1_e = Appl_PaMemory_CtrlModel_B.FRSeatPosMsg;
      CanTx_0x3B2_DSM_FRSeatPosMsg(Appl_PaMemory_CtrlModel_B.In1_e);
      Appl_PaMemory_CtrlModel_B.In1_b = (INT16U)0x3B2;
      Rte_SetCanEvent_0x3B2(Appl_PaMemory_CtrlModel_B.In1_b);
    }
  }
}

/* System initialize for function-call system: '<S52>/PosiCompareFunc' */
static void Appl_PaMemory_CtrlModel_PosiCompareFunc_Init(INT8U *rty_Result)
{
  *rty_Result = 0U;
}

/* Output and update for function-call system: '<S52>/PosiCompareFunc' */
static void Appl_PaMemory_CtrlModel_PosiCompareFunc(INT16U rtu_MemH, INT16U
  rtu_MenL, INT16U rtu_MemB, INT16U rtu_MemF, INT16U rtu_CurrentH, INT16U
  rtu_CurrentL, INT16U rtu_CurrentB, INT16U rtu_CurrentF, INT8U rtu_PosiReq,
  INT8U *rty_Result)
{
  /*  û�м���λ��  */
  if (rtu_PosiReq == ((BOOL)FALSE))
  {
    *rty_Result = 2U;
  }
  else
  {
    /*  ��ǰλ���ڼ���λ�÷�Χ��        */
    if ((rtu_CurrentH <= rtu_MemH + ((INT16U)D_ToleranceDistance)) && (rtu_MemH <=
         rtu_CurrentH + ((INT16U)D_ToleranceDistance)) && (rtu_CurrentL <=
         rtu_MenL + ((INT16U)D_ToleranceDistance)) && (rtu_MenL <= rtu_CurrentL
         + ((INT16U)D_ToleranceDistance)) && (rtu_CurrentB <= rtu_MemB +
         ((INT16U)D_ToleranceDistance)) && (rtu_MemB <= rtu_CurrentB + ((INT16U)
          D_ToleranceDistance)) && (rtu_CurrentF <= rtu_MemF + ((INT16U)
          D_ToleranceDistance)) && (rtu_MemF <= rtu_CurrentF + ((INT16U)
          D_ToleranceDistance)))
    {
      *rty_Result = ((BOOL)TRUE);
    }
    else
    {
      *rty_Result = ((BOOL)FALSE);
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   �ӿ��Զ�����
 */
static void Appl_PaMemory_CtrlModel_RTE(void)
{
  PaMem_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
  PaMem_AnyoneRelayFaultSts = Rte_GetVfb_PaAnyoneRelayAdheErr( );
  PaMem_BackAutoRunFlag = Rte_GetVfb_PaBackAutoRunFlag( );
  PaMem_BackHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerBack);
  PaMem_BackLockFault = Rte_GetVfb_PaBackStallErr( );
  PaMem_BackMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Back);
  PaMem_BackMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Back);
  PaMem_BackMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Back);
  PaMem_CurrentMoveType = Rte_GetVfb_PaMoveType( );
  PaMem_DtcAnyoneHallFaultSts = Rte_GetVfb_PaAnyoneDTCHallErr( );
  PaMem_FRSeatPosMsg = Srvl_GetMemIndexDataU8(EN_MemIndex_FRSeatPosMsg);
  PaMem_FrontAutoRunFlag = Rte_GetVfb_PaFrontAutoRunFlag( );
  PaMem_FrontHallPosi = Cdd_GetCurrentHallCnt(EN_PaResever_2);
  PaMem_FrontLockFault = Rte_GetVfb_PaFrontStallErr( );
  PaMem_FrontMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Front);
  PaMem_FrontMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Front);
  PaMem_FrontMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Front);
  PaMem_Gear_PN_FlagOut = Rte_GetCAN_Gear_PN_Flag( );
  PaMem_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  PaMem_HeightAutoRunFlag = Rte_GetVfb_PaHeightAutoRunFlag( );
  PaMem_HeightHallPosi = Cdd_GetCurrentHallCnt(EN_PaResever_1);
  PaMem_HeightLockFault = Rte_GetVfb_PaHeightStallErr( );
  PaMem_HeightMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Height);
  PaMem_HeightMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Height);
  PaMem_HeightMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Height);
  PaMem_IVI_FRSeatMemSet1 = CanRx_0x351_IVI_FRSeatMemSet1( );
  PaMem_IVI_FRSeatMemSet2 = CanRx_0x351_IVI_FRSeatMemSet2( );
  PaMem_IVI_FRSeatMemSet3 = CanRx_0x351_IVI_FRSeatMemSet3( );
  PaMem_LengthAutoRunFlag = Rte_GetVfb_PaLengthAutoRunFlag( );
  PaMem_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerLength);
  PaMem_LengthLockFault = Rte_GetVfb_PaLengthStallErr( );
  PaMem_LengthMem1 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem1_Length);
  PaMem_LengthMem2 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem2_Length);
  PaMem_LengthMem3 = Srvl_GetMemIndexDataU16(EN_MemIndex_PaMem3_Length);
  PaMem_NapMode = Rte_GetVfb_NapMode( );
  PaMem_PABackSwitch = Rte_GetVfb_PaBackSwitchCmd( );
  PaMem_PAFrontSwitch = Rte_GetVfb_PaFrontSwitchCmd( );
  PaMem_PAHeightSwitch = Rte_GetVfb_PaHeightSwitchCmd( );
  PaMem_PALengthSwitch = Rte_GetVfb_PaLengthSwitchCmd( );
  PaMem_PaAnyoneLockFaultSts = Rte_GetVfb_PaAnyoneStallErr( );
  PaMem_PaMemoryConfig = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
  PaMem_PowerMode = Rte_GetVfb_PowerMode( );
  PaMem_SeatLearnResult = Rte_GetVfb_PaLearnResult( );
  PaMem_SeatMemory1Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMem1_ValidFlag);
  PaMem_SeatMemory2Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMem2_ValidFlag);
  PaMem_SeatMemory3Valid = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMem3_ValidFlag);
  PaMem_SpeedLessThan5_Flag = Rte_GetVfb_SpeedLessThan5_Flag( );
  PaMem_VoltMode = Rte_GetVfb_VoltMode( );
  PaMem_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaMemory_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U Result;
  Appl_PaMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_PaMemory_CtrlModel_DW.is_active_c6_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  Appl_PaMemory_CtrlModel_DW.is_active_c1_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = 0U;
  Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = 0U;
  Appl_PaMemory_CtrlModel_B.MemoryBackPosi = 0U;
  Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = 0U;
  Appl_PaMemory_CtrlModel_B.MemoryValid = 0U;
  Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_PaMemory_CtrlModel_DW.is_active_c2_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = 0U;
  Appl_PaMemory_CtrlModel_B.PreMemRemindStop = enMemStopCause_EN_MemStop_NULL;
  Appl_PaMemory_CtrlModel_B.Result1st = 0U;
  Appl_PaMemory_CtrlModel_B.Result2nd = 0U;
  Appl_PaMemory_CtrlModel_B.Result3rd = 0U;
  Appl_PaMemory_CtrlModel_PosiCompareFunc_Init(&Result);
  Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
    Appl_PaMemory_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  Appl_PaMemory_CtrlModel_DW.is_active_c7_Appl_PaMemory_CtrlModel = 0U;
  Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = 0U;
  Appl_PaMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
  Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = 0U;
  Appl_PaMemory_CtrlModel_B.PreMemCallStop = enMemStopCause_EN_MemStop_NULL;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaMemory_CtrlModel_UpDataInputInfo(void)
{
  INT32S ActionFlag;
  INT8U ActionCnt;
  Appl_PaMemory_CtrlModel_RTE();
  if (Appl_PaMemory_CtrlModel_DW.is_active_c6_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c6_Appl_PaMemory_CtrlModel = 1U;

    /*  ����1  */
    /* ����2  */
    /*  ����3  */
    /*  ���ڳ�ͻ  */
    Appl_PaMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
      Appl_PaMemory_CtrlModel_IN_ButtonConflict;
    Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  }
  else
  {
    ActionCnt = 0U;

    /*  ����1  */
    if ((PaMem_IVI_FRSeatMemSet1 > enMemSet_EN_MemSet_NULL) &&
        (PaMem_IVI_FRSeatMemSet1 < enMemSet_EN_MemSet_Clean))
    {
      ActionCnt = 1U;
    }

    /* ����2  */
    if ((PaMem_IVI_FRSeatMemSet2 > enMemSet_EN_MemSet_NULL) &&
        (PaMem_IVI_FRSeatMemSet2 < enMemSet_EN_MemSet_Clean))
    {
      ActionCnt++;
    }

    /*  ����3  */
    if ((PaMem_IVI_FRSeatMemSet3 > enMemSet_EN_MemSet_NULL) &&
        (PaMem_IVI_FRSeatMemSet3 < enMemSet_EN_MemSet_Clean))
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

    if (Appl_PaMemory_CtrlModel_DW.is_AcquireMemoryButtonReq ==
        Appl_PaMemory_CtrlModel_IN_ButtonConflict)
    {
      /* �ޱ��ĳ�ͻ */
      if (ActionFlag == ((BOOL)TRUE))
      {
        Appl_PaMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
          Appl_PaMemory_CtrlModel_IN_NoButtonConflict;

        /*  ����λ��1  */
        if (PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set1;
        }

        /*  ����λ��1  */
        if (PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call1;
        }

        /*  ����λ��2  */
        if (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set2;
        }

        /*  ����λ��2  */
        if (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call2;
        }

        /*  ����λ��3  */
        if (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set3;
        }

        /*  ����λ��3  */
        if (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call3;
        }

        /*  �޼�������  */
        if ((PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_NULL) &&
            (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_NULL) &&
            (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_NULL))
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
        }
      }
    }
    else
    {
      /* ���ĳ�ͻ */
      if (ActionFlag == ((BOOL)FALSE))
      {
        Appl_PaMemory_CtrlModel_DW.is_AcquireMemoryButtonReq =
          Appl_PaMemory_CtrlModel_IN_ButtonConflict;
        Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
      }
      else
      {
        /*  ����λ��1  */
        if (PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set1;
        }

        /*  ����λ��1  */
        if (PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call1;
        }

        /*  ����λ��2  */
        if (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set2;
        }

        /*  ����λ��2  */
        if (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call2;
        }

        /*  ����λ��3  */
        if (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_Mem)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Set3;
        }

        /*  ����λ��3  */
        if (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_Call)
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_Call3;
        }

        /*  �޼�������  */
        if ((PaMem_IVI_FRSeatMemSet1 == enMemSet_EN_MemSet_NULL) &&
            (PaMem_IVI_FRSeatMemSet2 == enMemSet_EN_MemSet_NULL) &&
            (PaMem_IVI_FRSeatMemSet3 == enMemSet_EN_MemSet_NULL))
        {
          Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
        }
      }
    }
  }

  if (Appl_PaMemory_CtrlModel_DW.is_active_c1_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c1_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
      Appl_PaMemory_CtrlModel_IN_NoneMemoryCall;
    Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = 0U;
    Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = 0U;
    Appl_PaMemory_CtrlModel_B.MemoryBackPosi = 0U;
    Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = 0U;
    Appl_PaMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
  }
  else
  {
    switch (Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel)
    {
     case Appl_PaMemory_CtrlModel_IN_AcquireMemory1stPosi:
      /*  �޵���  */
      if ((Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��3  */
        switch (Appl_PaMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call3:
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory3rdPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem3;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem3;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem3;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem3;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory3Valid;
          break;

         case enMemBtn_EN_MemBtn_Call2:
          /*  ����λ��2  */
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory2ndPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem2;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem2;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem2;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem2;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory2Valid;
          break;
        }
      }
      break;

     case Appl_PaMemory_CtrlModel_IN_AcquireMemory2ndPosi:
      /*  �޵���  */
      if ((Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��1  */
        switch (Appl_PaMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call1:
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory1stPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem1;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem1;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem1;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem1;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory1Valid;
          break;

         case enMemBtn_EN_MemBtn_Call3:
          /*  ����λ��3  */
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory3rdPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem3;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem3;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem3;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem3;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory3Valid;
          break;
        }
      }
      break;

     case Appl_PaMemory_CtrlModel_IN_AcquireMemory3rdPosi:
      /*  �޵���  */
      if ((Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call1) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call2) &&
          (Appl_PaMemory_CtrlModel_B.SeatMemBtn != enMemBtn_EN_MemBtn_Call3))
      {
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_NoneMemoryCall;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = 0U;
        Appl_PaMemory_CtrlModel_B.MemoryValid = ((BOOL)FALSE);
      }
      else
      {
        /*  ����λ��1  */
        switch (Appl_PaMemory_CtrlModel_B.SeatMemBtn)
        {
         case enMemBtn_EN_MemBtn_Call1:
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory1stPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem1;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem1;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem1;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem1;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory1Valid;
          break;

         case enMemBtn_EN_MemBtn_Call2:
          /*  ����λ��2  */
          Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
            Appl_PaMemory_CtrlModel_IN_AcquireMemory2ndPosi;
          Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem2;
          Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem2;
          Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem2;
          Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem2;
          Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory2Valid;
          break;
        }
      }
      break;

     default:
      /*  ����λ��1  */
      switch (Appl_PaMemory_CtrlModel_B.SeatMemBtn)
      {
       case enMemBtn_EN_MemBtn_Call1:
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_AcquireMemory1stPosi;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem1;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem1;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem1;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem1;
        Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory1Valid;
        break;

       case enMemBtn_EN_MemBtn_Call2:
        /*  ����λ��2  */
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_AcquireMemory2ndPosi;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem2;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem2;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem2;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem2;
        Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory2Valid;
        break;

       case enMemBtn_EN_MemBtn_Call3:
        /*  ����λ��3  */
        Appl_PaMemory_CtrlModel_DW.is_c1_Appl_PaMemory_CtrlModel =
          Appl_PaMemory_CtrlModel_IN_AcquireMemory3rdPosi;
        Appl_PaMemory_CtrlModel_B.MemoryHeightPosi = PaMem_HeightMem3;
        Appl_PaMemory_CtrlModel_B.MemoryLengthPosi = PaMem_LengthMem3;
        Appl_PaMemory_CtrlModel_B.MemoryBackPosi = PaMem_BackMem3;
        Appl_PaMemory_CtrlModel_B.MemoryFrontPosi = PaMem_FrontMem3;
        Appl_PaMemory_CtrlModel_B.MemoryValid = PaMem_SeatMemory3Valid;
        break;
      }
      break;
    }
  }

  if (Appl_PaMemory_CtrlModel_DW.is_active_c2_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c2_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
      Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
  }
  else
  {
    Appl_PaMemory_CtrlModel_PosiCompareFunc(0, PaMem_LengthMem1, PaMem_BackMem1,
      0, 0, PaMem_LengthHallPosi, PaMem_BackHallPosi, 0, PaMem_SeatMemory1Valid,
      &Appl_PaMemory_CtrlModel_B.Result3rd);
    Appl_PaMemory_CtrlModel_B.Result1st = Appl_PaMemory_CtrlModel_B.Result3rd;
    Appl_PaMemory_CtrlModel_PosiCompareFunc(0, PaMem_LengthMem2, PaMem_BackMem2,
      0, 0, PaMem_LengthHallPosi, PaMem_BackHallPosi, 0, PaMem_SeatMemory2Valid,
      &Appl_PaMemory_CtrlModel_B.Result3rd);
    Appl_PaMemory_CtrlModel_B.Result2nd = Appl_PaMemory_CtrlModel_B.Result3rd;
    Appl_PaMemory_CtrlModel_PosiCompareFunc(0, PaMem_LengthMem3, PaMem_BackMem3,
      0, 0, PaMem_LengthHallPosi, PaMem_BackHallPosi, 0, PaMem_SeatMemory3Valid,
      &Appl_PaMemory_CtrlModel_B.Result3rd);
    if (Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal ==
        Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);

      /* ���书��ʹ�� == 0x1:TRUE
         && ������ʾ����ʹ�� == 0x1:Enable
         && ��ѹģʽ == ����
       /PreMemRemindStop = 0x0:enNone; */
      if ((PaMem_AdjustEnable == ((BOOL)TRUE)) && (PaMem_PaMemoryConfig ==
           ((BOOL)TRUE)) && (PaMem_VoltSatisfy == ((BOOL)TRUE)) &&
          (PaMem_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_PaMemory_CtrlModel_B.PreMemRemindStop =
          enMemStopCause_EN_MemStop_NULL;
        Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
          Appl_PaMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)TRUE);

      /* F101���书�� != 0x1:TRUE
         || ������ʾ�������� != 0x1:Enable
       /PreMemRemindStop = 0xA:enConfigError; */
      if ((PaMem_AdjustEnable != ((BOOL)TRUE)) || (PaMem_PaMemoryConfig !=
           ((BOOL)TRUE)))
      {
        Appl_PaMemory_CtrlModel_B.PreMemRemindStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
          Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* ��ѹģʽ != ����
         /PreMemRemindStop = 0xE:enVoltageError; */
        if ((PaMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
            (PaMem_VoltSatisfy != ((BOOL)TRUE)))
        {
          Appl_PaMemory_CtrlModel_B.PreMemRemindStop =
            enMemStopCause_EN_MemStop_VoltageErr;
          Appl_PaMemory_CtrlModel_DW.is_MemoryRemindPreconditionDeal =
            Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_PaMemory_CtrlModel_B.MemRemindPC_Flag = ((BOOL)FALSE);
        }
      }
    }
  }

  if (Appl_PaMemory_CtrlModel_DW.is_active_c7_Appl_PaMemory_CtrlModel == 0U)
  {
    Appl_PaMemory_CtrlModel_DW.is_active_c7_Appl_PaMemory_CtrlModel = 1U;
    Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
      Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
    Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
      Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
    Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
  }
  else
  {
    if (Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal ==
        Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);

      /* ����ʻ��������==TRUE
         &&���书��ʹ�� == 0x1:TRUE
         && ������ѧϰ
         && �����˶����� == 0x0:enNULL
         && ���λ������ϱ�־λ == FALSE
         && ���μ̵���ճ�����ϱ�־λ == FALSE
         && ���ζ�ת���ϱ�־λ == FALSE
         && IVI_NapMode_SwtichSet != 0x1:��С�ģʽ
         && ��ѹģʽ == ����
       /PreMemSetStop = 0x0:enNone; */
      if ((PaMem_AdjustEnable == ((BOOL)TRUE)) && (PaMem_PaMemoryConfig ==
           ((BOOL)TRUE)) && (PaMem_SeatLearnResult == ((BOOL)TRUE)) &&
          (PaMem_CurrentMoveType == (INT32S)enSeatMotorRunType_EN_NULL) &&
          (PaMem_DtcAnyoneHallFaultSts == ((BOOL)FALSE)) && ((INT32S)
           PaMem_AnyoneRelayFaultSts == ((BOOL)FALSE)) &&
          (PaMem_PaAnyoneLockFaultSts == ((BOOL)FALSE)) && (PaMem_VoltSatisfy ==
           ((BOOL)TRUE)) && (PaMem_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_PaMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
        Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
          Appl_PaMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)TRUE);

      /* ���书��ʹ�� != 0x1:TRUE
       /PreMemCallStop = 0xA:enConfigError; */
      if ((PaMem_AdjustEnable != ((BOOL)TRUE)) || (PaMem_PaMemoryConfig !=
           ((BOOL)TRUE)))
      {
        Appl_PaMemory_CtrlModel_B.PreMemSetStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
          Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* !������ѧϰ
         /PreMemSetStop = 0x1:enNotLearn; */
        if (PaMem_SeatLearnResult != ((BOOL)TRUE))
        {
          Appl_PaMemory_CtrlModel_B.PreMemSetStop =
            enMemStopCause_EN_MemStop_Learn;
          Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
            Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
        }
        else
        {
          /* �����˶����� != 0x0:enNULL
           /PreMemSetStop = 0x2:enOtherMove; */
          if (PaMem_CurrentMoveType != (INT32S)enSeatMotorRunType_EN_NULL)
          {
            Appl_PaMemory_CtrlModel_B.PreMemSetStop =
              enMemStopCause_EN_MemStop_OtherMove;
            Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
              Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
            Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
          }
          else
          {
            /* ���λ������ϱ�־λ != FALSE
             /PreMemSetStop = 0x3:enHallError; */
            if (PaMem_DtcAnyoneHallFaultSts != ((BOOL)FALSE))
            {
              Appl_PaMemory_CtrlModel_B.PreMemSetStop =
                enMemStopCause_EN_MemStop_HallErr;
              Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
              Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
            }
            else
            {
              /* ���μ̵���ճ�����ϱ�־λ != FALSE
               /PreMemSetStop = 0x4:enRelayError; */
              if ((INT32S)PaMem_AnyoneRelayFaultSts != ((BOOL)FALSE))
              {
                Appl_PaMemory_CtrlModel_B.PreMemSetStop =
                  enMemStopCause_EN_MemStop_RelayErr;
                Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                  Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
              }
              else
              {
                /* IVI_NapMode_SwtichSet == 0x1:��С�ģʽ
                 /PreMemSetStop = 0xB:enNapError; */
                /* ��ѹģʽ != ����
                 /PreMemSetStop = 0xE:enVoltageError; */
                if ((PaMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
                    (PaMem_VoltSatisfy != ((BOOL)TRUE)))
                {
                  Appl_PaMemory_CtrlModel_B.PreMemSetStop =
                    enMemStopCause_EN_MemStop_VoltageErr;
                  Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                    Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                  Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
                }
                else
                {
                  /* ���ζ�ת���ϱ�־λ != FALSE
                   /PreMemSetStop = 0x:EN_MemStop_StallErr; */
                  if (PaMem_PaAnyoneLockFaultSts != ((BOOL)FALSE))
                  {
                    Appl_PaMemory_CtrlModel_B.PreMemSetStop =
                      enMemStopCause_EN_MemStop_StallErr;
                    Appl_PaMemory_CtrlModel_DW.is_MemorySetPreconditionDeal =
                      Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                    Appl_PaMemory_CtrlModel_B.MemSetPC_Flag = ((BOOL)FALSE);
                  }
                }
              }
            }
          }
        }
      }
    }

    if (Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal ==
        Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied)
    {
      Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);

      /* ����ʻ��������==TRUE
         && ���书��ʹ�� == 0x1:TRUE
         && ��Դ��λ != 0x3:enCRANK
         && ������ѧϰ
         && ���μ̵���ճ�����ϱ�־λ == FALSE
         && SpeedLessThan5_Flag == TRUE
         && �����˶����� <= 0x3:enMemory
         && ��ѹģʽ == ����
         && ���ΰ�����־λ == FALSE
         && DSM_NapMode_FB != 0x2:��С�ģʽ
       /PreMemCallStop = 0x0:enNone;
         && PaMem_Gear_PN_FlagOut == TRUE ... */
      if ((PaMem_AdjustEnable == ((BOOL)TRUE)) && (PaMem_PaMemoryConfig ==
           ((BOOL)TRUE)) && (PaMem_PowerMode != enPowerModeSts_EN_CRANK) &&
          (PaMem_SeatLearnResult == ((BOOL)TRUE)) && ((INT32S)
           PaMem_AnyoneRelayFaultSts == ((BOOL)FALSE)) && (PaMem_CurrentMoveType
           <= (INT32S)enSeatMotorRunType_EN_MemoryEnable) && (PaMem_VoltSatisfy ==
           ((BOOL)TRUE)) && (PaMem_PALengthSwitch == ((BOOL)FALSE)) &&
          (PaMem_PABackSwitch == ((BOOL)FALSE)) && (PaMem_VoltMode ==
           enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_PaMemory_CtrlModel_B.PreMemCallStop =
          enMemStopCause_EN_MemStop_NULL;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
          Appl_PaMemory_CtrlModel_IN_PreconditionSatisfied;
        Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)TRUE);

      /* ���书��ʹ�� != 0x1:TRUE
       /PreMemCallStop = 0xA:enConfigError; */
      if ((PaMem_AdjustEnable != ((BOOL)TRUE)) || (PaMem_PaMemoryConfig !=
           ((BOOL)TRUE)))
      {
        Appl_PaMemory_CtrlModel_B.PreMemCallStop =
          enMemStopCause_EN_MemStop_ConfigError;
        Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
          Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
        Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
      }
      else
      {
        /* !������ѧϰ
         /PreMemSetStop = 0x1:enNotLearn; */
        if (PaMem_SeatLearnResult != ((BOOL)TRUE))
        {
          Appl_PaMemory_CtrlModel_B.PreMemCallStop =
            enMemStopCause_EN_MemStop_Learn;
          Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
            Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
          Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
        }
        else
        {
          /* �����˶����� > 0x3:enMemory
           /PreMemCallStop = 0x2:enOtherMove; */
          if (PaMem_CurrentMoveType > (INT32S)enSeatMotorRunType_EN_MemoryEnable)
          {
            Appl_PaMemory_CtrlModel_B.PreMemCallStop =
              enMemStopCause_EN_MemStop_OtherMove;
            Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
              Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
            Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
          }
          else
          {
            /* ���μ̵���ճ�����ϱ�־λ != FALSE
             /PreMemSetStop = 0x4:enRelayError; */
            if ((INT32S)PaMem_AnyoneRelayFaultSts != ((BOOL)FALSE))
            {
              Appl_PaMemory_CtrlModel_B.PreMemCallStop =
                enMemStopCause_EN_MemStop_RelayErr;
              Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
              Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
            }
            else
            {
              /* IVI_NapMode_SwtichSet == 0x1:��С�ģʽ
               /PreMemSetStop = 0xB:enNapError; */
              /* ��ѹģʽ != ����
               /PreMemSetStop = 0xE:enVoltageError; */
              if ((PaMem_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT) ||
                  (PaMem_VoltSatisfy != ((BOOL)TRUE)))
              {
                Appl_PaMemory_CtrlModel_B.PreMemCallStop =
                  enMemStopCause_EN_MemStop_VoltageErr;
                Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                  Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
              }
              else
              {
                /* ��Դ��λ == 0x3:enCRANK
                 /PreMemCallStop = 0x6:enNotON; */
                if (PaMem_PowerMode == enPowerModeSts_EN_CRANK)
                {
                  Appl_PaMemory_CtrlModel_B.PreMemCallStop =
                    enMemStopCause_EN_MemStop_NotON;
                  Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                    Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                  Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
                }
                else
                {
                  /* SpeedLessThan5_Flag != TRUE
                   /PreMemCallStop = 0x8:enSpeedError; */
                  /* ���ΰ�����־λ != FALSE
                   /PreMemSetStop = 0x:EN_MemStop_StallErr; */
                  if ((PaMem_PALengthSwitch != ((BOOL)FALSE)) ||
                      (PaMem_PABackSwitch != ((BOOL)FALSE)))
                  {
                    Appl_PaMemory_CtrlModel_B.PreMemCallStop =
                      enMemStopCause_EN_MemStop_StallErr;
                    Appl_PaMemory_CtrlModel_DW.is_MemoryCallPreconditionDeal =
                      Appl_PaMemory_CtrlMode_IN_PreconditionNotSatisfied;
                    Appl_PaMemory_CtrlModel_B.MemCallPC_Flag = ((BOOL)FALSE);
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
static void Appl_PaMemory_CtrlModel_UpDataOutputInfo(void)
{
  CanTx_0x3B2_DSM_FRSeatMemStsAndMsg(Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts);
  CanTx_0x3B2_DSM_FRSeatPosMsg(Appl_PaMemory_CtrlModel_B.FRSeatPosMsg);
  Rte_SetVfb_PaMemCallStopReason(Appl_PaMemory_CtrlModel_B.MemCallStopReason);
  Rte_SetVfb_PaMemSetStopReason(Appl_PaMemory_CtrlModel_B.MemSetStopReason);
  Rte_SetVfb_PaPreMemRemindStop(Appl_PaMemory_CtrlModel_B.PreMemRemindStop_d);
  Rte_SetVfb_PaMemBackReqPosi(Appl_PaMemory_CtrlModel_B.SeatBackPosiReq);
  Rte_SetVfb_PaMemFrontReqPosi(Appl_PaMemory_CtrlModel_B.SeatFrontPosiReq);
  Rte_SetVfb_PaMemHeightReqPosi(Appl_PaMemory_CtrlModel_B.SeatHeightPosiReq);
  Rte_SetVfb_PaMemLengthReqPosi(Appl_PaMemory_CtrlModel_B.SeatLengthPosiReq);
  CanTx_0x3B2_DSM1_FRSeatMem1Sts(Appl_PaMemory_CtrlModel_B.SeatMem1StsFb);
  CanTx_0x3B2_DSM2_FRSeatMem2Sts(Appl_PaMemory_CtrlModel_B.SeatMem2StsFb);
  CanTx_0x3B2_DSM2_FRSeatMem3Sts(Appl_PaMemory_CtrlModel_B.SeatMem3StsFb);
  Rte_SetVfb_PaSeatMemoryValidReq(Appl_PaMemory_CtrlModel_B.SeatMemoryValidReq);
}

/* Model step function */
void Appl_PaMemory_CtrlModel_step(void)
{
  Appl_PaMemory_CtrlModel_UpDataInputInfo();
  Appl_PaMemory_CtrlModel_LogicCtrl();
  Appl_PaMemory_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_PaMemory_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_PaMemory_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_PaMemory_CtrlModel_B), 0,
                sizeof(B_Appl_PaMemory_CtrlModel_T));

  {
    Appl_PaMemory_CtrlModel_B.PreMemSetStop = enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.PreMemCallStop = enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.PreMemRemindStop = enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.PreMemRemindStop_d =
      enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.MemSetStopReason = enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.MemCallStopReason = enMemStopCause_EN_MemStop_NULL;
    Appl_PaMemory_CtrlModel_B.FRSeatMemSetSts = enMemSetFb_EN_MemSetFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMem1StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMem2StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMem3StsFb = enMemCallFb_EN_MemCallFb_NULL;
    Appl_PaMemory_CtrlModel_B.SeatMemBtn = enMemBtn_EN_MemBtn_NULL;
  }

  /* exported global signals */
  PaMem_AnyoneRelayFaultSts = enSeatMotorRunType_EN_NULL;
  PaMem_BackAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaMem_FrontAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaMem_HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaMem_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaMem_PowerMode = enPowerModeSts_EN_OFF;
  PaMem_NapMode = enNapMode_EN_NapMode_NULL;
  PaMem_IVI_FRSeatMemSet1 = enMemSet_EN_MemSet_NULL;
  PaMem_IVI_FRSeatMemSet2 = enMemSet_EN_MemSet_NULL;
  PaMem_IVI_FRSeatMemSet3 = enMemSet_EN_MemSet_NULL;
  PaMem_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  PaMem_BackHallPosi = ((INT16U)0U);
  PaMem_BackMem1 = ((INT16U)0U);
  PaMem_BackMem2 = ((INT16U)0U);
  PaMem_BackMem3 = ((INT16U)0U);
  PaMem_FrontHallPosi = ((INT16U)0U);
  PaMem_FrontMem1 = ((INT16U)0U);
  PaMem_FrontMem2 = ((INT16U)0U);
  PaMem_FrontMem3 = ((INT16U)0U);
  PaMem_GetRecoverDefaultFlag = ((INT16U)0U);
  PaMem_HeightHallPosi = ((INT16U)0U);
  PaMem_HeightMem1 = ((INT16U)0U);
  PaMem_HeightMem2 = ((INT16U)0U);
  PaMem_HeightMem3 = ((INT16U)0U);
  PaMem_LengthHallPosi = ((INT16U)0U);
  PaMem_LengthMem1 = ((INT16U)0U);
  PaMem_LengthMem2 = ((INT16U)0U);
  PaMem_LengthMem3 = ((INT16U)0U);
  PaMem_AdjustEnable = ((INT8U)0U);
  PaMem_BackLockFault = ((INT8U)0U);
  PaMem_CurrentMoveType = ((INT8U)0U);
  PaMem_DtcAnyoneHallFaultSts = ((INT8U)0U);
  PaMem_FRSeatPosMsg = ((INT8U)0U);
  PaMem_FrontLockFault = ((INT8U)0U);
  PaMem_Gear_PN_FlagOut = ((INT8U)0U);
  PaMem_HeightLockFault = ((INT8U)0U);
  PaMem_LengthLockFault = ((INT8U)0U);
  PaMem_PABackSwitch = ((INT8U)0U);
  PaMem_PAFrontSwitch = ((INT8U)0U);
  PaMem_PAHeightSwitch = ((INT8U)0U);
  PaMem_PALengthSwitch = ((INT8U)0U);
  PaMem_PaAnyoneLockFaultSts = ((INT8U)0U);
  PaMem_PaMemoryConfig = ((INT8U)0U);
  PaMem_SeatLearnResult = ((INT8U)0U);
  PaMem_SeatMemory1Valid = ((INT8U)0U);
  PaMem_SeatMemory2Valid = ((INT8U)0U);
  PaMem_SeatMemory3Valid = ((INT8U)0U);
  PaMem_SpeedLessThan5_Flag = ((INT8U)0U);
  PaMem_VoltSatisfy = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_PaMemory_CtrlModel_DW, 0,
                sizeof(DW_Appl_PaMemory_CtrlModel_T));
  Appl_PaMemory_CtrlModel_UpDataInputInfo_Init();
  Appl_PaMemory_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
