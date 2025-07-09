/*
 * File: Appl_DrLearn_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_DrLearn_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:36:37 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_DrLearn_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_FirstMove
#error The variable for the parameter "D_FirstMove" is not defined
#endif

#ifndef D_FourthlyMove
#error The variable for the parameter "D_FourthlyMove" is not defined
#endif

#ifndef D_Invalid
#error The variable for the parameter "D_Invalid" is not defined
#endif

#ifndef D_SecondMove
#error The variable for the parameter "D_SecondMove" is not defined
#endif

#ifndef D_ThirdlyMove
#error The variable for the parameter "D_ThirdlyMove" is not defined
#endif

/* Named constants for Chart: '<S6>/AutoLearnCmdProcess' */
#define Appl_DrLearn_CtrlModel_IN_Disable ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_Enable ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)

/* Named constants for Chart: '<S7>/Learn' */
#define Appl_DrLearn_CtrlModel_IN_BackLearn ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_FrontLearn ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_HeightLearn ((INT8U)3U)
#define Appl_DrLearn_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_LearnLogicalDeal ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_LearnReady ((INT8U)3U)
#define Appl_DrLearn_CtrlModel_IN_Learning ((INT8U)4U)
#define Appl_DrLearn_CtrlModel_IN_LengthLearn ((INT8U)5U)

/* Named constants for Chart: '<S16>/OneClickResetConditionProcess' */
#define Appl_DrLearn_CtrlModel_IN_Active ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_Inactive ((INT8U)2U)

/* Named constants for Chart: '<S9>/Reset' */
#define Appl_DrLearn_CtrlModel_IN_BM400 ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_BackReset ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_FrontReset ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_HeightReset ((INT8U)3U)
#define Appl_DrLearn_CtrlModel_IN_Init_p ((INT8U)4U)
#define Appl_DrLearn_CtrlModel_IN_LengthReset ((INT8U)5U)
#define Appl_DrLearn_CtrlModel_IN_P20  ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_ResetInit ((INT8U)1U)
#define Appl_DrLearn_CtrlModel_IN_ResetLogicalDeal ((INT8U)2U)
#define Appl_DrLearn_CtrlModel_IN_Reseting ((INT8U)6U)

/* Exported block signals */
enVehTypePrm DrLearn_VehiclePrm;       /* '<S21>/DrLearn_VehiclePrm'
                                        * 车型：C62X、C52X…
                                        */
enSeatMotorRunTye DrLearn_CurrMotorCtrlType;/* '<S21>/DrLearn_CurrMotorCtrlType'
                                             * 当前操作类型
                                             */
enSeatAutoRunSts DrLearn_BackAutoRunFlag;/* '<S21>/DrLearn_BackAutoRunFlag'
                                          * 主驾靠背自动运行标志位
                                          */
enSeatAutoRunSts DrLearn_FrontAutoRunFlag;/* '<S21>/DrLearn_FrontAutoRunFlag'
                                           * 主驾前部角度自动运行标志位
                                           */
enSeatAutoRunSts DrLearn_HeightAutoRunFlag;/* '<S21>/DrLearn_HeightAutoRunFlag'
                                            * 主驾高度自动运行标志位
                                            */
enSeatAutoRunSts DrLearn_LengthAutoRunFlag;/* '<S21>/DrLearn_LengthAutoRunFlag'
                                            * 主驾纵向自动运行标志位
                                            */
enIgnSts DrLearn_PowerModeStatus;      /* '<S21>/DrLearn_PowerModeStatus'
                                        * 整车电源档位
                                        */
enDrAdjustEnable DrLearn_AdjustEnable; /* '<S21>/DrLearn_AdjustEnable'
                                        * 主驾座椅调节:
                                        */
INT16U DrLearn_BackDefaultStopPos;     /* '<S21>/DrLearn_BackDefaultStopPos'
                                        * 靠背硬止点
                                        */
INT16U DrLearn_FrontDefaulStoptPos;    /* '<S21>/DrLearn_FrontDefaulStoptPos'
                                        * 腿托硬止点
                                        */
INT16U DrLearn_HeightDefaultStopPos;   /* '<S21>/DrLearn_HeightDefaultStopPos'
                                        * 高度硬止点
                                        */
INT16U DrLearn_LengthDefaultStopPos;   /* '<S21>/DrLearn_LengthDefaultStopPos'
                                        * 纵向硬止点
                                        */
INT8U DrLearn_AnyoneHallErr;           /* '<S21>/DrLearn_AnyoneHallErr'
                                        * 任一霍尔故障标志
                                        */
INT8U DrLearn_AnyoneRelayAdheErr;      /* '<S21>/DrLearn_AnyoneRelayAdheErr'
                                        * 任一继电器粘连故障标志
                                        */
INT8U DrLearn_BackMotorTimeOutErr;     /* '<S21>/DrLearn_BackMotorTimeOutErr'
                                        * 靠背电机运行超时标志
                                        */
INT8U DrLearn_BackStallErr;            /* '<S21>/DrLearn_BackStallErr'
                                        * 靠背堵转标志位
                                        */
INT8U DrLearn_DescSession;             /* '<S21>/DrLearn_DescSession'
                                        * 会话
                                        */
INT8U DrLearn_DiagnoseLearnIn;         /* '<S21>/DrLearn_DiagnoseLearnIn'
                                        * 请求学习标志
                                        */
INT8U DrLearn_FrontMotorTimeOutErr;    /* '<S21>/DrLearn_FrontMotorTimeOutErr'
                                        * 腿托电机运行超时标志
                                        */
INT8U DrLearn_FrontStallErr;           /* '<S21>/DrLearn_FrontStallErr'
                                        * 腿托堵转标志位
                                        */
INT8U DrLearn_GetRecoverDefaultFlag;   /* '<S21>/DrLearn_GetRecoverDefaultFlag'
                                        * 恢复出厂设置
                                        */
INT8U DrLearn_HeightMotorTimeOutErr;   /* '<S21>/DrLearn_HeightMotorTimeOutErr'
                                        * 高度电机运行超时标志
                                        */
INT8U DrLearn_HeightStallErr;          /* '<S21>/DrLearn_HeightStallErr'
                                        * 高度堵转标志位
                                        */
INT8U DrLearn_LearnSts;                /* '<S21>/DrLearn_LearnSts'
                                        * 学习状态
                                        */
INT8U DrLearn_LengthMotorTimeOutErr;   /* '<S21>/DrLearn_LengthMotorTimeOutErr'
                                        * 纵向电机运行超时标志
                                        */
INT8U DrLearn_LengthStallErr;          /* '<S21>/DrLearn_LengthStallErr'
                                        * 纵向堵转标志位
                                        */
INT8U DrLearn_OTAMode;                 /* '<S21>/DrLearn_OTAMode'
                                        * OTA-P20为预留
                                        */
INT8U DrLearn_VehSpdUnder3KMFlag;      /* '<S21>/DrLearn_VehSpdUnder3KMFlag'
                                        * 车速大于3的标志位
                                        */
INT8U DrLearn_VoltSatisfy;             /* '<S21>/DrLearn_VoltSatisfy'
                                        * 电机调节电压是否满足
                                        */
INT8U DrLearn_WelcomeEnable;           /* '<S21>/DrLearn_WelcomeEnable'
                                        * 主驾迎宾使能状态
                                        */

/* Invariant block signals (default storage) */
const ConstB_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_ConstB =
{
  0.0                                  /* '<S20>/Constant6' */
};

/* Block signals (default storage) */
B_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_DrLearn_CtrlModel_T Appl_DrLearn_CtrlModel_M_;
RT_MODEL_Appl_DrLearn_CtrlModel_T *const Appl_DrLearn_CtrlModel_M =
  &Appl_DrLearn_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT32U CAL_LearnAllTimeMax_150s = 15000U;/* 全程学习最长时间：150s */
const volatile INT16U CAL_LearnSingleTimeMax_60s = 6000U;/* 学习最长时间：60s */
static void Appl_DrLearn_CtrlModel_LogicCtrl_Init(void);
static void Appl_DrLearn_CtrlModel_LogicCtrl(void);
static void Appl_DrLearn_CtrlModel_RTE(void);
static void Appl_DrLearn_CtrlModel_UpDataInputInfo(void);
static void Appl_DrLearn_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_DrLearn_CtrlModel_inner_default_LearnReady(void);
static INT32S Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(INT32S input);
static void Appl_DrLearn_CtrlModel_enter_atomic_Init(void);
static void Appl_DrLearn_CtrlModel_Learning(void);
static void Appl_DrLearn_CtrlModel_LearnLogicalDeal(const INT8U *LearnCondition,
  const INT8U *MtrCtrl_DiagnoseLearnIn_prev, const enDrAdjustEnable
  *MtrCtrl_AdjustEnable_prev);
static void Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal(void);
static void Appl_DrLearn_CtrlModel_enter_atomic_ResetInit(void);
static void Appl_DrLearn_CtrlModel_ResetLogicalDeal(const INT8U *LearnCondition,
  const INT8U *ResetReq, const enVehTypePrm *MtrCtrl_VehiclePrm_prev);
static void Appl_DrLearn_CtrlM_enter_internal_ResetLogicalDeal(void);

/* Function for Chart: '<S7>/Learn' */
static void Appl_DrLearn_CtrlModel_inner_default_LearnReady(void)
{
  if (DrLearn_AdjustEnable == enDrAdjustEnable_EN_DrTwelveWayMotor)
  {
    Appl_DrLearn_CtrlModel_DW.Hight = ((INT8U)D_FirstMove);
    Appl_DrLearn_CtrlModel_DW.H_Move = enSWMoveCmd_enDOWN_BACK;
    Appl_DrLearn_CtrlModel_DW.Length_c = ((INT8U)D_SecondMove);
    Appl_DrLearn_CtrlModel_DW.L_Move = 1.0;
    Appl_DrLearn_CtrlModel_DW.Back_e = ((INT8U)D_ThirdlyMove);
    Appl_DrLearn_CtrlModel_DW.B_Move = enSWMoveCmd_enUP_FORWARD;
    Appl_DrLearn_CtrlModel_DW.Front_p = ((INT8U)D_FourthlyMove);
    Appl_DrLearn_CtrlModel_DW.F_Move = enSWMoveCmd_enUP_FORWARD;
  }

  if (DrLearn_AdjustEnable == enDrAdjustEnable_EN_DrSixWayMotor)
  {
    Appl_DrLearn_CtrlModel_DW.Hight = ((INT8U)D_FirstMove);
    Appl_DrLearn_CtrlModel_DW.H_Move = enSWMoveCmd_enDOWN_BACK;
    Appl_DrLearn_CtrlModel_DW.Length_c = ((INT8U)D_SecondMove);
    Appl_DrLearn_CtrlModel_DW.L_Move = 1.0;
    Appl_DrLearn_CtrlModel_DW.Back_e = ((INT8U)D_ThirdlyMove);
    Appl_DrLearn_CtrlModel_DW.B_Move = enSWMoveCmd_enUP_FORWARD;
    Appl_DrLearn_CtrlModel_DW.Front_p = ((INT8U)D_Invalid);
    Appl_DrLearn_CtrlModel_DW.F_Move = enSWMoveCmd_en_NULL;
  }
}

static INT32S Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enSWMoveCmd (en_NULL) */
  y = 0;
  if ((input >= 0) && (input <= 2))
  {
    /* Set output value to input value if it is a member of enSWMoveCmd */
    y = input;
  }

  return y;
}

/* Function for Chart: '<S7>/Learn' */
static void Appl_DrLearn_CtrlModel_enter_atomic_Init(void)
{
  Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
  Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
  Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
    Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
    Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
    Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
    Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
  Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
  Appl_DrLearn_CtrlModel_DW.Hight = ((INT8U)D_FirstMove);
  Appl_DrLearn_CtrlModel_DW.H_Move = enSWMoveCmd_enDOWN_BACK;
  Appl_DrLearn_CtrlModel_DW.Length_c = ((INT8U)D_SecondMove);
  Appl_DrLearn_CtrlModel_DW.L_Move = 1.0;
  Appl_DrLearn_CtrlModel_DW.Back_e = ((INT8U)D_ThirdlyMove);
  Appl_DrLearn_CtrlModel_DW.B_Move = enSWMoveCmd_enUP_FORWARD;
  Appl_DrLearn_CtrlModel_DW.Front_p = ((INT8U)D_FourthlyMove);
  Appl_DrLearn_CtrlModel_DW.F_Move = enSWMoveCmd_enUP_FORWARD;
}

/* Function for Chart: '<S7>/Learn' */
static void Appl_DrLearn_CtrlModel_Learning(void)
{
  /* 根据配置的设定顺序执行 */
  if (Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
      Appl_DrLearn_CtrlModel_DW.Hight)
  {
    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_DrLearn_CtrlModel_IN_HeightLearn;
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = Appl_DrLearn_CtrlModel_DW.H_Move;
    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else if (Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_DrLearn_CtrlModel_DW.Length_c)
  {
    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_DrLearn_CtrlModel_IN_LengthLearn;
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    if (Appl_DrLearn_CtrlModel_DW.L_Move < 2.147483648E+9)
    {
      if (Appl_DrLearn_CtrlModel_DW.L_Move >= -2.147483648E+9)
      {
        Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd((INT32S)
          Appl_DrLearn_CtrlModel_DW.L_Move);
      }
      else
      {
        Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(MIN_int32_T);
      }
    }
    else
    {
      Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(MAX_int32_T);
    }

    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else if (Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_DrLearn_CtrlModel_DW.Front_p)
  {
    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_DrLearn_CtrlModel_IN_FrontLearn;
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = Appl_DrLearn_CtrlModel_DW.F_Move;
  }
  else if (Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_DrLearn_CtrlModel_DW.Back_e)
  {
    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_DrLearn_CtrlModel_IN_BackLearn;
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.BackLearnSW = Appl_DrLearn_CtrlModel_DW.B_Move;
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else
  {
    /* 4个方向均学习完成后开始复位 */
    if (((Appl_DrLearn_CtrlModel_DW.Hight + Appl_DrLearn_CtrlModel_DW.Length_c)
         + Appl_DrLearn_CtrlModel_DW.Back_e) + Appl_DrLearn_CtrlModel_DW.Front_p
        == Appl_DrLearn_CtrlModel_DW.LearnResult)
    {
      Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enLearnAllSuccess;
      Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
        Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_LearnReady;
      Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
      Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
      Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
      Appl_DrLearn_CtrlModel_inner_default_LearnReady();
    }
  }
}

/* Function for Chart: '<S7>/Learn' */
static void Appl_DrLearn_CtrlModel_LearnLogicalDeal(const INT8U *LearnCondition,
  const INT8U *MtrCtrl_DiagnoseLearnIn_prev, const enDrAdjustEnable
  *MtrCtrl_AdjustEnable_prev)
{
  INT32S tmp;
  if (*MtrCtrl_AdjustEnable_prev !=
      Appl_DrLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start)
  {
    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_DrLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enCfgW_ADJUST;
    Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
    Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
      Appl_DrLearn_CtrlModel_IN_LearnReady;
    Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
    Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
    Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
    Appl_DrLearn_CtrlModel_inner_default_LearnReady();
  }
  else
  {
    /* 诊断退出 */
    if ((*MtrCtrl_DiagnoseLearnIn_prev !=
         Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start) &&
        (Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start == ((BOOL)FALSE)))
    {
      Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
        Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_DrLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enDescStop;
      Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
      Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_LearnReady;
      Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
      Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
      Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
        Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
      Appl_DrLearn_CtrlModel_inner_default_LearnReady();
    }
    else
    {
      /* 高度电机运行超时 */
      if (Appl_DrLearn_CtrlModel_DW.HeightLearnTimer >
          CAL_LearnSingleTimeMax_60s)
      {
        Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
          Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_DrLearn_CtrlModel_B.LearnExitCause =
          enLearnExitCause_enMotorRunOverTime_H;
        Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
        Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
          Appl_DrLearn_CtrlModel_IN_LearnReady;
        Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
        Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
        Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
        Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
        Appl_DrLearn_CtrlModel_inner_default_LearnReady();
      }
      else
      {
        /* 学习条件不满足 */
        if (((BOOL)FALSE) == *LearnCondition)
        {
          Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
            Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_DrLearn_CtrlModel_B.LearnExitCause =
            Appl_DrLearn_CtrlModel_B.LearnConditionExitCause;
          Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
          Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
            Appl_DrLearn_CtrlModel_IN_Init;
          Appl_DrLearn_CtrlModel_enter_atomic_Init();
        }
        else
        {
          /* 纵向电机运行超时 */
          if (Appl_DrLearn_CtrlModel_DW.LengthLearnTimer >
              CAL_LearnSingleTimeMax_60s)
          {
            Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
              Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
            Appl_DrLearn_CtrlModel_B.LearnExitCause =
              enLearnExitCause_enMotorRunOverTime_L;
            Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
            Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
              Appl_DrLearn_CtrlModel_IN_LearnReady;
            Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
            Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
            Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
              Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
              Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
              Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
              Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
            Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
            Appl_DrLearn_CtrlModel_inner_default_LearnReady();
          }
          else
          {
            /* 靠背电机运行超时 */
            if (Appl_DrLearn_CtrlModel_DW.BackLearnTimer >
                CAL_LearnSingleTimeMax_60s)
            {
              Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_DrLearn_CtrlModel_B.LearnExitCause =
                enLearnExitCause_enMotorRunOverTime_B;
              Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
              Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
                Appl_DrLearn_CtrlModel_IN_LearnReady;
              Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
              Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
              Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
              Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
              Appl_DrLearn_CtrlModel_inner_default_LearnReady();
            }
            else
            {
              /* 腿托电机运行超时 */
              if (Appl_DrLearn_CtrlModel_DW.FrontLearnTimer >
                  CAL_LearnSingleTimeMax_60s)
              {
                Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                  Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
                Appl_DrLearn_CtrlModel_B.LearnExitCause =
                  enLearnExitCause_enMotorRunOverTime_F;
                Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
                Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
                  Appl_DrLearn_CtrlModel_IN_LearnReady;
                Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
                Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
                Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                  Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                  Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                  Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                  Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
                Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
                Appl_DrLearn_CtrlModel_inner_default_LearnReady();
              }
              else
              {
                switch (Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal)
                {
                 case Appl_DrLearn_CtrlModel_IN_BackLearn:
                  if (((BOOL)TRUE) == DrLearn_BackStallErr)
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnResult +
                      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_DrLearn_CtrlModel_IN_Learning;
                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_DrLearn_CtrlModel_DW.BackLearnTimer++;
                  }
                  break;

                 case Appl_DrLearn_CtrlModel_IN_FrontLearn:
                  if (((BOOL)TRUE) == DrLearn_FrontStallErr)
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnResult +
                      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_DrLearn_CtrlModel_IN_Learning;
                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_DrLearn_CtrlModel_DW.FrontLearnTimer++;
                  }
                  break;

                 case Appl_DrLearn_CtrlModel_IN_HeightLearn:
                  /* 学习成功后记录当前的学习结果 */
                  if (((BOOL)TRUE) == DrLearn_HeightStallErr)
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnResult +
                      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_DrLearn_CtrlModel_IN_Learning;
                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_DrLearn_CtrlModel_DW.HeightLearnTimer++;
                  }
                  break;

                 case Appl_DrLearn_CtrlModel_IN_Learning:
                  Appl_DrLearn_CtrlModel_Learning();
                  break;

                 default:
                  if (((BOOL)TRUE) == DrLearn_LengthStallErr)
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnResult +
                      Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_DrLearn_CtrlModel_IN_Learning;
                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_DrLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_DrLearn_CtrlModel_DW.LengthLearnTimer++;
                  }
                  break;
                }
              }
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal(void)
{
  Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_PositionTransform =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_DrLearn_CtrlModel_enter_atomic_ResetInit(void)
{
  Appl_DrLearn_CtrlModel_DW.CurrentResetSts = (INT8U)0x00;
  Appl_DrLearn_CtrlModel_DW.ResetResult = (INT8U)0x00;
  Appl_DrLearn_CtrlModel_B.BackPosiReq = (INT16U)0x00;
  Appl_DrLearn_CtrlModel_B.LengthPosiReq = (INT16U)0x00;
  Appl_DrLearn_CtrlModel_B.FrontPosiReq = (INT16U)0x00;
  Appl_DrLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
  Appl_DrLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
  Appl_DrLearn_CtrlModel_DW.RestTimer = 0U;
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_DrLearn_CtrlModel_ResetLogicalDeal(const INT8U *LearnCondition,
  const INT8U *ResetReq, const enVehTypePrm *MtrCtrl_VehiclePrm_prev)
{
  INT32S tmp;

  /* 复位成功 */
  tmp = ((Appl_DrLearn_CtrlModel_DW.Height + Appl_DrLearn_CtrlModel_DW.Length) +
         Appl_DrLearn_CtrlModel_DW.Back) + Appl_DrLearn_CtrlModel_DW.Front;
  if ((tmp == Appl_DrLearn_CtrlModel_DW.ResetResult) && (1 ==
       Appl_DrLearn_CtrlModel_DW.ResetType))
  {
    Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal();
    Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enResetSuccess;
    Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
      Appl_DrLearn_CtrlModel_IN_ResetInit;
    Appl_DrLearn_CtrlModel_enter_atomic_ResetInit();
    if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
    {
      Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
      Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
      Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
      Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
    }

    if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
        (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
    {
      if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
      {
        Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
      }
      else
      {
        tmp = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
      }
    }
  }
  else
  {
    /* 退出复位或者任意方向复位失败 */
    if (((((BOOL)FALSE) == *ResetReq) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          DrLearn_HeightAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          DrLearn_BackAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          DrLearn_LengthAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          DrLearn_FrontAutoRunFlag) || (*MtrCtrl_VehiclePrm_prev !=
          Appl_DrLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start)) && (1 ==
         Appl_DrLearn_CtrlModel_DW.ResetType))
    {
      Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal();
      Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enResetFail;
      Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_ResetInit;
      Appl_DrLearn_CtrlModel_enter_atomic_ResetInit();
      if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
      {
        Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
        Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
        Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
        Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
      }

      if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
          (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
      {
        if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
        {
          Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
        }
        else
        {
          tmp = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
        }
      }
    }
    else
    {
      /* 通过学习完成后复位的方式触发不反馈失败  且调节类型非复位行为  */
      if (((enSeatAutoRunSts_EN_SEAT_FAIL == DrLearn_HeightAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == DrLearn_BackAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == DrLearn_LengthAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == DrLearn_FrontAutoRunFlag) ||
           (*LearnCondition == ((BOOL)FALSE)) ||
           ((Appl_DrLearn_CtrlModel_DW.RestTimer > 2) &&
            (DrLearn_CurrMotorCtrlType != enSeatMotorRunTye_EN_ResetEnable)) ||
           (*MtrCtrl_VehiclePrm_prev !=
            Appl_DrLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start)) && (2 ==
           Appl_DrLearn_CtrlModel_DW.ResetType))
      {
        Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal();
        Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
          Appl_DrLearn_CtrlModel_IN_ResetInit;
        Appl_DrLearn_CtrlModel_enter_atomic_ResetInit();
        if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
        {
          Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
          Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
          Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
          Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
        }

        if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
            (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
        {
          if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
          {
            Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
            Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
          }
          else
          {
            tmp = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
          }
        }
      }
      else
      {
        /* 通过学习完成后复位的方式触发不反馈成功 */
        if ((tmp == Appl_DrLearn_CtrlModel_DW.ResetResult) && (2 ==
             Appl_DrLearn_CtrlModel_DW.ResetType))
        {
          Appl_DrLearn_CtrlMo_exit_internal_ResetLogicalDeal();
          Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
            Appl_DrLearn_CtrlModel_IN_ResetInit;
          Appl_DrLearn_CtrlModel_enter_atomic_ResetInit();
          if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
          {
            Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
            Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
            Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
            Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
          }

          if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
              (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
          {
            if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
            {
              Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
              Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
            }
            else
            {
              tmp = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
            }
          }
        }
        else
        {
          if (Appl_DrLearn_CtrlModel_DW.is_PositionTransform ==
              Appl_DrLearn_CtrlModel_IN_BM400)
          {
            /* 反馈位置坐标 */
            if (Appl_DrLearn_CtrlModel_DW.Back ==
                Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = DrLearn_BackDefaultStopPos +
                Appl_DrLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_DrLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
            }
            else if (Appl_DrLearn_CtrlModel_DW.Length ==
                     Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = DrLearn_LengthDefaultStopPos +
                Appl_DrLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_DrLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
            }
            else if (Appl_DrLearn_CtrlModel_DW.Front ==
                     Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = DrLearn_FrontDefaulStoptPos +
                Appl_DrLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_DrLearn_CtrlModel_B.FrontPosiReq = (INT16U)tmp;
            }
            else
            {
              if (Appl_DrLearn_CtrlModel_DW.Height ==
                  Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
              {
                Appl_DrLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
              }
            }
          }

          switch (Appl_DrLearn_CtrlModel_DW.is_ResetPosition)
          {
           case Appl_DrLearn_CtrlModel_IN_BackReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == DrLearn_BackAutoRunFlag)
            {
              tmp = Appl_DrLearn_CtrlModel_DW.ResetResult +
                Appl_DrLearn_CtrlModel_DW.Back;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                Appl_DrLearn_CtrlModel_IN_Reseting;
              tmp = Appl_DrLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_DrLearn_CtrlModel_IN_FrontReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == DrLearn_FrontAutoRunFlag)
            {
              tmp = Appl_DrLearn_CtrlModel_DW.ResetResult +
                Appl_DrLearn_CtrlModel_DW.Front;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                Appl_DrLearn_CtrlModel_IN_Reseting;
              tmp = Appl_DrLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_DrLearn_CtrlModel_IN_HeightReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == DrLearn_HeightAutoRunFlag)
            {
              tmp = Appl_DrLearn_CtrlModel_DW.ResetResult +
                Appl_DrLearn_CtrlModel_DW.Height;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                Appl_DrLearn_CtrlModel_IN_Reseting;
              tmp = Appl_DrLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_DrLearn_CtrlModel_IN_Init_p:
            Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
              Appl_DrLearn_CtrlModel_IN_Reseting;
            tmp = Appl_DrLearn_CtrlModel_DW.MotorResetSts + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_DrLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            break;

           case Appl_DrLearn_CtrlModel_IN_LengthReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == DrLearn_LengthAutoRunFlag)
            {
              tmp = Appl_DrLearn_CtrlModel_DW.ResetResult +
                Appl_DrLearn_CtrlModel_DW.Length;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                Appl_DrLearn_CtrlModel_IN_Reseting;
              tmp = Appl_DrLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_DrLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           default:
            /* 靠背复位 */
            if (Appl_DrLearn_CtrlModel_DW.Back ==
                Appl_DrLearn_CtrlModel_DW.MotorResetSts)
            {
              Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                Appl_DrLearn_CtrlModel_IN_BackReset;
              Appl_DrLearn_CtrlModel_DW.CurrentResetSts =
                Appl_DrLearn_CtrlModel_DW.Back;
            }
            else
            {
              /* 纵向复位 */
              if (Appl_DrLearn_CtrlModel_DW.Length ==
                  Appl_DrLearn_CtrlModel_DW.MotorResetSts)
              {
                Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                  Appl_DrLearn_CtrlModel_IN_LengthReset;
                Appl_DrLearn_CtrlModel_DW.CurrentResetSts =
                  Appl_DrLearn_CtrlModel_DW.Length;
              }
              else
              {
                /* 高度复位 */
                if (Appl_DrLearn_CtrlModel_DW.Height ==
                    Appl_DrLearn_CtrlModel_DW.MotorResetSts)
                {
                  Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                    Appl_DrLearn_CtrlModel_IN_HeightReset;
                  Appl_DrLearn_CtrlModel_DW.CurrentResetSts =
                    Appl_DrLearn_CtrlModel_DW.Height;
                }
                else
                {
                  /* 腿托复位 */
                  if (Appl_DrLearn_CtrlModel_DW.Front ==
                      Appl_DrLearn_CtrlModel_DW.MotorResetSts)
                  {
                    Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
                      Appl_DrLearn_CtrlModel_IN_FrontReset;
                    Appl_DrLearn_CtrlModel_DW.CurrentResetSts =
                      Appl_DrLearn_CtrlModel_DW.Front;
                  }
                }
              }
            }
            break;
          }

          /*  复位时间  */
          if (Appl_DrLearn_CtrlModel_DW.RestTimer <= 200)
          {
            tmp = Appl_DrLearn_CtrlModel_DW.RestTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_DrLearn_CtrlModel_DW.RestTimer = (INT8U)tmp;
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_DrLearn_CtrlM_enter_internal_ResetLogicalDeal(void)
{
  INT32S tmp;
  if (enVehTypePrm_enP20 == DrLearn_VehiclePrm)
  {
    Appl_DrLearn_CtrlModel_DW.is_PositionTransform =
      Appl_DrLearn_CtrlModel_IN_P20;
    tmp = DrLearn_HeightDefaultStopPos + 306;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_DrLearn_CtrlModel_B.HeightPosiReq = (INT16U)tmp;
    tmp = DrLearn_LengthDefaultStopPos + 522;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_DrLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
    tmp = DrLearn_FrontDefaulStoptPos + 122;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_DrLearn_CtrlModel_B.FrontPosiReq = (INT16U)tmp;
    tmp = DrLearn_BackDefaultStopPos + 2185;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_DrLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
  }
  else
  {
    Appl_DrLearn_CtrlModel_DW.is_PositionTransform =
      Appl_DrLearn_CtrlModel_IN_BM400;

    /* 反馈位置坐标 */
    if (Appl_DrLearn_CtrlModel_DW.Back ==
        Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = DrLearn_BackDefaultStopPos +
        Appl_DrLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_DrLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
    }
    else if (Appl_DrLearn_CtrlModel_DW.Length ==
             Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = DrLearn_LengthDefaultStopPos +
        Appl_DrLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_DrLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
    }
    else if (Appl_DrLearn_CtrlModel_DW.Front ==
             Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = DrLearn_FrontDefaulStoptPos +
        Appl_DrLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_DrLearn_CtrlModel_B.FrontPosiReq = (INT16U)tmp;
    }
    else
    {
      if (Appl_DrLearn_CtrlModel_DW.Height ==
          Appl_DrLearn_CtrlModel_DW.CurrentResetSts)
      {
        Appl_DrLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
      }
    }
  }

  Appl_DrLearn_CtrlModel_DW.is_ResetPosition = Appl_DrLearn_CtrlModel_IN_Init_p;
  Appl_DrLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_DrLearn_CtrlModel_DW.ResetResult = 0U;
  Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
  if (1 == Appl_DrLearn_CtrlModel_DW.ResetType)
  {
    Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enResetWaiting;
  }

  /*  复位时间  */
  if (Appl_DrLearn_CtrlModel_DW.RestTimer <= 200)
  {
    tmp = Appl_DrLearn_CtrlModel_DW.RestTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    Appl_DrLearn_CtrlModel_DW.RestTimer = (INT8U)tmp;
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrLearn_CtrlModel_LogicCtrl_Init(void)
{
  Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_active_c1_Appl_DrLearn_CtrlModel = 0U;
  Appl_DrLearn_CtrlModel_B.LearnConditionExitCause = enLearnExitCause_enInvalid;
  Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_active_c42_Appl_DrLearn_CtrlModel = 0U;
  Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.Hight = 0U;
  Appl_DrLearn_CtrlModel_DW.Length_c = 0U;
  Appl_DrLearn_CtrlModel_DW.Back_e = 0U;
  Appl_DrLearn_CtrlModel_DW.H_Move = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_DW.L_Move = 0.0;
  Appl_DrLearn_CtrlModel_DW.B_Move = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_DW.F_Move = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
  Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
  Appl_DrLearn_CtrlModel_DW.Front_p = 0U;
  Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
  Appl_DrLearn_CtrlModel_DW.HeightLearnTimer = 0.0;
  Appl_DrLearn_CtrlModel_DW.LengthLearnTimer = 0.0;
  Appl_DrLearn_CtrlModel_DW.BackLearnTimer = 0.0;
  Appl_DrLearn_CtrlModel_DW.FrontLearnTimer = 0.0;
  Appl_DrLearn_CtrlModel_B.HeightLearnSW = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_B.LengthLearnSW = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_B.BackLearnSW = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_B.FrontLearnSW = enSWMoveCmd_en_NULL;
  Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
  Appl_DrLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
  Appl_DrLearn_CtrlModel_DW.is_active_c7_Appl_DrLearn_CtrlModel = 0U;
  Appl_DrLearn_CtrlModel_DW.is_c7_Appl_DrLearn_CtrlModel =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_PositionTransform =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_ResetPosition =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.is_active_c2_Appl_DrLearn_CtrlModel = 0U;
  Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
    Appl_DrLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_DrLearn_CtrlModel_DW.Height = 0U;
  Appl_DrLearn_CtrlModel_DW.Length = 0U;
  Appl_DrLearn_CtrlModel_DW.Back = 0U;
  Appl_DrLearn_CtrlModel_DW.Front = 0U;
  Appl_DrLearn_CtrlModel_DW.CurrentResetSts = 0U;
  Appl_DrLearn_CtrlModel_DW.ResetResult = 0U;
  Appl_DrLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_DrLearn_CtrlModel_DW.ResetType = 0U;
  Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
  Appl_DrLearn_CtrlModel_DW.RestTimer = 0U;
  Appl_DrLearn_CtrlModel_B.HeightPosiReq = 0U;
  Appl_DrLearn_CtrlModel_B.LengthPosiReq = 0U;
  Appl_DrLearn_CtrlModel_B.BackPosiReq = 0U;
  Appl_DrLearn_CtrlModel_B.FrontPosiReq = 0U;
  Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_DrLearn_CtrlModel_LogicCtrl(void)
{
  INT32S rtb_Switch;
  BOOL rtb_AND;
  INT8U LearnCondition;
  INT8U MtrCtrl_DiagnoseLearnIn_prev;
  enDrAdjustEnable MtrCtrl_AdjustEnable_prev;
  DOUBLE MtrCtrl_HIDO_SeatsButtonResetReq_prev;
  enLearnSts MtrCtrl_LearnSts_prev;
  enVehTypePrm MtrCtrl_VehiclePrm_prev;
  if (Appl_DrLearn_CtrlModel_DW.is_active_c1_Appl_DrLearn_CtrlModel == 0U)
  {
    Appl_DrLearn_CtrlModel_DW.is_active_c1_Appl_DrLearn_CtrlModel = 1U;
    Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
      Appl_DrLearn_CtrlModel_IN_Enable;
    LearnCondition = ((BOOL)TRUE);
    Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
      enLearnExitCause_enInvalid;
  }
  else if (Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment ==
           Appl_DrLearn_CtrlModel_IN_Disable)
  {
    LearnCondition = ((BOOL)FALSE);

    /* 电压在9-16V、非OTA
       无霍尔故障、继电器粘连故障、车速条件满足   */
    if ((((BOOL)TRUE) == DrLearn_VoltSatisfy) && (((BOOL)FALSE) ==
         DrLearn_OTAMode) && (((BOOL)FALSE) == DrLearn_AnyoneHallErr) && (((BOOL)
          FALSE) == DrLearn_AnyoneRelayAdheErr) && (((BOOL)TRUE) ==
         DrLearn_VehSpdUnder3KMFlag) && (enSeatMotorRunTye_EN_ManualEnable !=
         DrLearn_CurrMotorCtrlType) && ((DrLearn_AdjustEnable ==
          enDrAdjustEnable_EN_DrSixWayMotor) || (DrLearn_AdjustEnable ==
          enDrAdjustEnable_EN_DrTwelveWayMotor)) && (DrLearn_WelcomeEnable != 0))
    {
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Enable;
      LearnCondition = ((BOOL)TRUE);
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enInvalid;
    }
  }
  else
  {
    LearnCondition = ((BOOL)TRUE);

    /* 电压非9-16V、OTA
       任一霍尔故障、继电器粘连故障、车速条件不满足 */
    if (((BOOL)FALSE) != DrLearn_AnyoneRelayAdheErr)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enRelayAdhesionFault;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) != DrLearn_AnyoneHallErr)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enHallFault;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) != DrLearn_OTAMode)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause = enLearnExitCause_enOTA;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)TRUE) != DrLearn_VehSpdUnder3KMFlag)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enVehSpeed;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (enSeatMotorRunTye_EN_ManualEnable == DrLearn_CurrMotorCtrlType)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enManualInterupt;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) == DrLearn_VoltSatisfy)
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enVoltFault;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if ((DrLearn_AdjustEnable != enDrAdjustEnable_EN_DrSixWayMotor) &&
             (DrLearn_AdjustEnable != enDrAdjustEnable_EN_DrTwelveWayMotor))
    {
      Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enCfgW_ADJUST;
      Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_DrLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else
    {
      if (0 == DrLearn_WelcomeEnable)
      {
        Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
          enLearnExitCause_enCfgW_MEMORY;
        Appl_DrLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
          Appl_DrLearn_CtrlModel_IN_Disable;
        LearnCondition = ((BOOL)FALSE);
      }
    }
  }

  MtrCtrl_DiagnoseLearnIn_prev =
    Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start;
  Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start =
    DrLearn_DiagnoseLearnIn;
  MtrCtrl_AdjustEnable_prev =
    Appl_DrLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start;
  Appl_DrLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start = DrLearn_AdjustEnable;
  if (Appl_DrLearn_CtrlModel_DW.is_active_c42_Appl_DrLearn_CtrlModel == 0U)
  {
    Appl_DrLearn_CtrlModel_DW.is_active_c42_Appl_DrLearn_CtrlModel = 1U;
    Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
      Appl_DrLearn_CtrlModel_IN_Init;
    Appl_DrLearn_CtrlModel_enter_atomic_Init();
  }
  else
  {
    switch (Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel)
    {
     case Appl_DrLearn_CtrlModel_IN_Init:
      /*  满足学习条件 */
      if (((BOOL)TRUE) == LearnCondition)
      {
        Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
          Appl_DrLearn_CtrlModel_IN_LearnReady;
        Appl_DrLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
        Rte_SetVfb_DrLearnEnable(Appl_DrLearn_CtrlModel_B.Sts);
        Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
          Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_DrLearn_CtrlModel_DW.LearnResult = 0U;
        Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
        Appl_DrLearn_CtrlModel_inner_default_LearnReady();
      }
      break;

     case Appl_DrLearn_CtrlModel_IN_LearnLogicalDeal:
      Appl_DrLearn_CtrlModel_LearnLogicalDeal(&LearnCondition,
        &MtrCtrl_DiagnoseLearnIn_prev, &MtrCtrl_AdjustEnable_prev);
      break;

     default:
      /* 学习条件不满足 */
      if (((BOOL)FALSE) == LearnCondition)
      {
        Appl_DrLearn_CtrlModel_B.LearnExitCause =
          Appl_DrLearn_CtrlModel_B.LearnConditionExitCause;
        Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
          Appl_DrLearn_CtrlModel_IN_Init;
        Appl_DrLearn_CtrlModel_enter_atomic_Init();
      }
      else
      {
        /* 诊断请求自动学习 */
        if ((MtrCtrl_DiagnoseLearnIn_prev !=
             Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start) &&
            (Appl_DrLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start == ((BOOL)
              TRUE)))
        {
          Appl_DrLearn_CtrlModel_DW.HeightLearnTimer = 0.0;
          Appl_DrLearn_CtrlModel_DW.LengthLearnTimer = 0.0;
          Appl_DrLearn_CtrlModel_DW.BackLearnTimer = 0.0;
          Appl_DrLearn_CtrlModel_DW.FrontLearnTimer = 0.0;
          Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enLearnning;
          Appl_DrLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
          Appl_DrLearn_CtrlModel_DW.is_c42_Appl_DrLearn_CtrlModel =
            Appl_DrLearn_CtrlModel_IN_LearnLogicalDeal;
          Appl_DrLearn_CtrlModel_DW.is_LearnLogicalDeal =
            Appl_DrLearn_CtrlModel_IN_Learning;
          Appl_DrLearn_CtrlModel_DW.LearnAllRunTime = 0U;
          rtb_Switch = Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
          if (rtb_Switch > 255)
          {
            rtb_Switch = 255;
          }

          Appl_DrLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)rtb_Switch;
          Appl_DrLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
            Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_DrLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
            Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_DrLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
            Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_DrLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
            Appl_DrLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);

          /* 根据之前配置的电机动作顺序
             （1 2 3 4）查找动作顺序* */
        }
        else
        {
          Appl_DrLearn_CtrlModel_inner_default_LearnReady();
        }
      }
      break;
    }
  }

  if (DrLearn_AdjustEnable == enDrAdjustEnable_EN_DrTwelveWayMotor)
  {
    rtb_Switch = DrLearn_FrontDefaulStoptPos;
  }
  else
  {
    rtb_Switch = 30000;
  }

  rtb_AND = ((DrLearn_HeightDefaultStopPos != 0) &&
             (DrLearn_HeightDefaultStopPos != 65535) &&
             (DrLearn_LengthDefaultStopPos != 0) &&
             (DrLearn_LengthDefaultStopPos != 65535) &&
             (DrLearn_BackDefaultStopPos != 0) && (DrLearn_BackDefaultStopPos !=
              65535) && (rtb_Switch != 0) && (rtb_Switch != 65535));
  if (Appl_DrLearn_CtrlModel_DW.is_active_c7_Appl_DrLearn_CtrlModel == 0U)
  {
    Appl_DrLearn_CtrlModel_DW.is_active_c7_Appl_DrLearn_CtrlModel = 1U;
    Appl_DrLearn_CtrlModel_DW.is_c7_Appl_DrLearn_CtrlModel =
      Appl_DrLearn_CtrlModel_IN_Inactive;
    MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)FALSE);
  }
  else if (Appl_DrLearn_CtrlModel_DW.is_c7_Appl_DrLearn_CtrlModel ==
           Appl_DrLearn_CtrlModel_IN_Active)
  {
    MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)TRUE);

    /* 电源模式非ON档 */
    if ((enIgnSts_eOn != DrLearn_PowerModeStatus) || (((BOOL)TRUE) ==
         DrLearn_AnyoneHallErr) || (((BOOL)FALSE) == DrLearn_AnyoneRelayAdheErr)
        || (((BOOL)TRUE) != rtb_AND) || (((BOOL)TRUE) ==
         DrLearn_GetRecoverDefaultFlag) || (((BOOL)FALSE) ==
         Appl_DrLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm))
    {
      Appl_DrLearn_CtrlModel_DW.is_c7_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_Inactive;
      MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)FALSE);
    }
    else
    {
      /* 任一无霍尔故障 */
      /* 无继电器粘连故障 */
      /* 未学习 */
      /* 恢复出厂 */
      /* 复位电机配置 */
    }
  }
  else
  {
    MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)FALSE);

    /* 电源模式为ON档
       无霍尔故障、无继电器粘连故障
       已学习成功
       配置有一键复位功能 */
    if ((enIgnSts_eOn == DrLearn_PowerModeStatus) && (((BOOL)FALSE) ==
         DrLearn_AnyoneHallErr) && (((BOOL)FALSE) == DrLearn_AnyoneRelayAdheErr)
        && (((BOOL)TRUE) == rtb_AND) && (((BOOL)TRUE) ==
         Appl_DrLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm))
    {
      Appl_DrLearn_CtrlModel_DW.is_c7_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_Active;
      MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)TRUE);
    }
  }

  MtrCtrl_HIDO_SeatsButtonResetReq_prev =
    Appl_DrLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start;
  Appl_DrLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start =
    Appl_DrLearn_CtrlModel_ConstB.MtrCtrl_HIDO_SeatsButtonResetReq;
  MtrCtrl_LearnSts_prev = Appl_DrLearn_CtrlModel_DW.MtrCtrl_LearnSts_start;
  Appl_DrLearn_CtrlModel_DW.MtrCtrl_LearnSts_start =
    Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts;
  MtrCtrl_VehiclePrm_prev = Appl_DrLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start;
  Appl_DrLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start = DrLearn_VehiclePrm;
  if (Appl_DrLearn_CtrlModel_DW.is_active_c2_Appl_DrLearn_CtrlModel == 0U)
  {
    Appl_DrLearn_CtrlModel_DW.is_active_c2_Appl_DrLearn_CtrlModel = 1U;
    Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
      Appl_DrLearn_CtrlModel_IN_ResetInit;
    Appl_DrLearn_CtrlModel_enter_atomic_ResetInit();
    if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
    {
      Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
      Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
      Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
      Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
    }

    if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
        (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
    {
      if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
      {
        Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
      }
      else
      {
        rtb_Switch = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
        if (rtb_Switch > 255)
        {
          rtb_Switch = 255;
        }

        Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)rtb_Switch;
      }
    }
  }
  else if (Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel ==
           Appl_DrLearn_CtrlModel_IN_ResetInit)
  {
    /*   */
    if ((((BOOL)TRUE) == MtrCtrl_DiagnoseLearnIn_prev) &&
        ((MtrCtrl_HIDO_SeatsButtonResetReq_prev !=
          Appl_DrLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start) &&
         (Appl_DrLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start ==
          0x01)) && (enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
    {
      Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
      Appl_DrLearn_CtrlModel_DW.RestTimer = 0U;
      Appl_DrLearn_CtrlModel_DW.ResetType = 1U;
      Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
      Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
      Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_FirstMove);
      Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_ThirdlyMove);
      Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enResetWaiting;
      Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_ResetLogicalDeal;
      Appl_DrLearn_CtrlM_enter_internal_ResetLogicalDeal();
    }
    else if ((MtrCtrl_LearnSts_prev !=
              Appl_DrLearn_CtrlModel_DW.MtrCtrl_LearnSts_start) &&
             (Appl_DrLearn_CtrlModel_DW.MtrCtrl_LearnSts_start ==
              enLearnSts_enLearnAllSuccess))
    {
      Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
      Appl_DrLearn_CtrlModel_DW.RestTimer = 0U;
      Appl_DrLearn_CtrlModel_DW.ResetType = 2U;
      Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
      Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
      Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
      Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
      Appl_DrLearn_CtrlModel_DW.is_c2_Appl_DrLearn_CtrlModel =
        Appl_DrLearn_CtrlModel_IN_ResetLogicalDeal;
      Appl_DrLearn_CtrlM_enter_internal_ResetLogicalDeal();
    }
    else
    {
      if (!(enVehTypePrm_enBM400 == DrLearn_VehiclePrm))
      {
        Appl_DrLearn_CtrlModel_DW.Height = ((INT8U)D_FirstMove);
        Appl_DrLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
        Appl_DrLearn_CtrlModel_DW.Back = ((INT8U)D_ThirdlyMove);
        Appl_DrLearn_CtrlModel_DW.Front = ((INT8U)D_FourthlyMove);
      }

      if ((Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
          (Appl_DrLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
      {
        if (Appl_DrLearn_CtrlModel_DW.SendTimer > 10)
        {
          Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_DrLearn_CtrlModel_DW.SendTimer = 0U;
        }
        else
        {
          rtb_Switch = Appl_DrLearn_CtrlModel_DW.SendTimer + 1;
          if (rtb_Switch > 255)
          {
            rtb_Switch = 255;
          }

          Appl_DrLearn_CtrlModel_DW.SendTimer = (INT8U)rtb_Switch;
        }
      }
    }
  }
  else
  {
    Appl_DrLearn_CtrlModel_ResetLogicalDeal(&LearnCondition,
      &MtrCtrl_DiagnoseLearnIn_prev, &MtrCtrl_VehiclePrm_prev);
  }

  Appl_DrLearn_CtrlModel_B.DataTypeConversion = rtb_AND;
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_DrLearn_CtrlModel_RTE(void)
{
  DrLearn_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
  DrLearn_AnyoneHallErr = Rte_GetVfb_DrAnyoneHallErr( );
  DrLearn_AnyoneRelayAdheErr = Rte_GetVfb_DrAnyoneRelayAdheErr( );
  DrLearn_BackAutoRunFlag = Rte_GetVfb_DrBackAutoRunFlag( );
  DrLearn_BackDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverBack);
  DrLearn_BackMotorTimeOutErr = Rte_GetVfb_DrBackMotorTimeOutErr( );
  DrLearn_BackStallErr = Rte_GetVfb_DrBackStallErr( );
  DrLearn_CurrMotorCtrlType = Rte_GetVfb_DrMoveType( );
  DrLearn_DescSession = DescGetcDescSession( );
  DrLearn_DiagnoseLearnIn = Rte_GetVfb_DrLearnEnable( );
  DrLearn_FrontAutoRunFlag = Rte_GetVfb_DrFrontAutoRunFlag( );
  DrLearn_FrontDefaulStoptPos = Cdd_GetMotorHardStop(EN_DriverFront);
  DrLearn_FrontMotorTimeOutErr = Rte_GetVfb_DrFrontMotorTimeOutErr( );
  DrLearn_FrontStallErr = Rte_GetVfb_DrFrontStallErr( );
  DrLearn_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  DrLearn_HeightAutoRunFlag = Rte_GetVfb_DrHeightAutoRunFlag( );
  DrLearn_HeightDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverHeight);
  DrLearn_HeightMotorTimeOutErr = Rte_GetVfb_DrHeightMotorTimeOutErr( );
  DrLearn_HeightStallErr = Rte_GetVfb_DrHeightStallErr( );
  DrLearn_LearnSts = Rte_GetVfb_DrLearnSts( );
  DrLearn_LengthAutoRunFlag = Rte_GetVfb_DrLengthAutoRunFlag( );
  DrLearn_LengthDefaultStopPos = Cdd_GetMotorHardStop(EN_DriverLength);
  DrLearn_LengthMotorTimeOutErr = Rte_GetVfb_DrLengthMotorTimeOutErr( );
  DrLearn_LengthStallErr = Rte_GetVfb_DrLengthStallErr( );
  DrLearn_OTAMode = Vfb_Reserved_0( );
  DrLearn_PowerModeStatus = Rte_GetVfb_PowerMode( );
  DrLearn_VehSpdUnder3KMFlag = DescCheckVehSpd( );
  DrLearn_VehiclePrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  DrLearn_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  DrLearn_WelcomeEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_DrLearn_CtrlModel_UpDataInputInfo(void)
{
  Appl_DrLearn_CtrlModel_RTE();
  Appl_DrLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi = ((BOOL)FALSE);
  Appl_DrLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi = ((BOOL)FALSE);
  Appl_DrLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi = ((BOOL)FALSE);
  Appl_DrLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm = ((BOOL)TRUE);
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_DrLearn_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_DrLearnSts(Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts);
  Rte_SetVfb_DrHeightLearnCmd(Appl_DrLearn_CtrlModel_B.HeightLearnSW);
  Rte_SetVfb_DrLengthLearnCmd(Appl_DrLearn_CtrlModel_B.LengthLearnSW);
  Rte_SetVfb_DrBackLearnCmd(Appl_DrLearn_CtrlModel_B.BackLearnSW);
  Rte_SetVfb_DrFrontLearnCmd(Appl_DrLearn_CtrlModel_B.FrontLearnSW);
  Rte_SetVfb_LearnExitCause(Appl_DrLearn_CtrlModel_B.LearnExitCause);
  Rte_SetVfb_DrLearnResult(Appl_DrLearn_CtrlModel_B.DataTypeConversion);
  Rte_SetVfb_DrHeightResetReqPosi(Appl_DrLearn_CtrlModel_B.HeightPosiReq);
  Rte_SetVfb_DrLengthResetReqPosi(Appl_DrLearn_CtrlModel_B.LengthPosiReq);
  Rte_SetVfb_DrBackResetReqPosi(Appl_DrLearn_CtrlModel_B.BackPosiReq);
  Rte_SetVfb_DrFrontResetReqPosi(Appl_DrLearn_CtrlModel_B.FrontPosiReq);
}

/* Model step function */
void Appl_DrLearn_CtrlModel_step(void)
{
  Appl_DrLearn_CtrlModel_UpDataInputInfo();
  Appl_DrLearn_CtrlModel_LogicCtrl();
  Appl_DrLearn_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_DrLearn_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_DrLearn_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_DrLearn_CtrlModel_B), 0,
                sizeof(B_Appl_DrLearn_CtrlModel_T));

  {
    Appl_DrLearn_CtrlModel_B.HeightLearnSW = enSWMoveCmd_en_NULL;
    Appl_DrLearn_CtrlModel_B.LengthLearnSW = enSWMoveCmd_en_NULL;
    Appl_DrLearn_CtrlModel_B.BackLearnSW = enSWMoveCmd_en_NULL;
    Appl_DrLearn_CtrlModel_B.FrontLearnSW = enSWMoveCmd_en_NULL;
    Appl_DrLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
    Appl_DrLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
    Appl_DrLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
    Appl_DrLearn_CtrlModel_B.LearnConditionExitCause =
      enLearnExitCause_enInvalid;
  }

  /* exported global signals */
  DrLearn_VehiclePrm = enVehTypePrm_enP20;
  DrLearn_CurrMotorCtrlType = enSeatMotorRunTye_EN_NULL;
  DrLearn_BackAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrLearn_FrontAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrLearn_HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrLearn_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  DrLearn_PowerModeStatus = enIgnSts_eOff;
  DrLearn_AdjustEnable = enDrAdjustEnable_EN_DrManual;
  DrLearn_BackDefaultStopPos = ((INT16U)0U);
  DrLearn_FrontDefaulStoptPos = ((INT16U)0U);
  DrLearn_HeightDefaultStopPos = ((INT16U)0U);
  DrLearn_LengthDefaultStopPos = ((INT16U)0U);
  DrLearn_AnyoneHallErr = ((INT8U)0U);
  DrLearn_AnyoneRelayAdheErr = ((INT8U)0U);
  DrLearn_BackMotorTimeOutErr = ((INT8U)0U);
  DrLearn_BackStallErr = ((INT8U)0U);
  DrLearn_DescSession = ((INT8U)0U);
  DrLearn_DiagnoseLearnIn = ((INT8U)0U);
  DrLearn_FrontMotorTimeOutErr = ((INT8U)0U);
  DrLearn_FrontStallErr = ((INT8U)0U);
  DrLearn_GetRecoverDefaultFlag = ((INT8U)0U);
  DrLearn_HeightMotorTimeOutErr = ((INT8U)0U);
  DrLearn_HeightStallErr = ((INT8U)0U);
  DrLearn_LearnSts = ((INT8U)0U);
  DrLearn_LengthMotorTimeOutErr = ((INT8U)0U);
  DrLearn_LengthStallErr = ((INT8U)0U);
  DrLearn_OTAMode = ((INT8U)0U);
  DrLearn_VehSpdUnder3KMFlag = ((INT8U)0U);
  DrLearn_VoltSatisfy = ((INT8U)0U);
  DrLearn_WelcomeEnable = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_DrLearn_CtrlModel_DW, 0,
                sizeof(DW_Appl_DrLearn_CtrlModel_T));
  Appl_DrLearn_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
