/*
 * File: Appl_PaLearn_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_PaLearn_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:51:19 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_PaLearn_CtrlModel.h"

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
#define Appl_PaLearn_CtrlModel_IN_Disable ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_Enable ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)

/* Named constants for Chart: '<S7>/Learn' */
#define Appl_PaLearn_CtrlModel_IN_BackLearn ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_FrontLearn ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_HeightLearn ((INT8U)3U)
#define Appl_PaLearn_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_LearnLogicalDeal ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_LearnReady ((INT8U)3U)
#define Appl_PaLearn_CtrlModel_IN_Learning ((INT8U)4U)
#define Appl_PaLearn_CtrlModel_IN_LengthLearn ((INT8U)5U)

/* Named constants for Chart: '<S16>/OneClickResetConditionProcess' */
#define Appl_PaLearn_CtrlModel_IN_Active ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_Inactive ((INT8U)2U)

/* Named constants for Chart: '<S9>/Reset' */
#define Appl_PaLearn_CtrlModel_IN_BM400 ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_BackReset ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_FrontReset ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_HeightReset ((INT8U)3U)
#define Appl_PaLearn_CtrlModel_IN_Init_p ((INT8U)4U)
#define Appl_PaLearn_CtrlModel_IN_LengthReset ((INT8U)5U)
#define Appl_PaLearn_CtrlModel_IN_P20  ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_ResetInit ((INT8U)1U)
#define Appl_PaLearn_CtrlModel_IN_ResetLogicalDeal ((INT8U)2U)
#define Appl_PaLearn_CtrlModel_IN_Reseting ((INT8U)6U)

/* Exported block signals */
enVehTypePrm PaLearn_VehiclePrm;       /* '<S21>/PaLearn_VehiclePrm'
                                        * 车型：C62X、C52X…
                                        */
enSeatMotorRunTye PaLearn_CurrMotorCtrlType;/* '<S21>/PaLearn_CurrMotorCtrlType'
                                             * 副驾当前操作类型
                                             */
enSeatAutoRunSts PaLearn_BackAutoRunFlag;/* '<S21>/PaLearn_BackAutoRunFlag'
                                          * 副驾靠背自动运行标志位
                                          */
enSeatAutoRunSts PaLearn_FrontAutoRunFlag;/* '<S21>/PaLearn_FrontAutoRunFlag'
                                           * 副驾前部角度自动运行标志位
                                           */
enSeatAutoRunSts PaLearn_HeightAutoRunFlag;/* '<S21>/PaLearn_HeightAutoRunFlag'
                                            * 副驾高度自动运行标志位
                                            */
enSeatAutoRunSts PaLearn_LengthAutoRunFlag;/* '<S21>/PaLearn_LengthAutoRunFlag'
                                            * 副驾纵向自动运行标志位
                                            */
enIgnSts PaLearn_PowerModeStatus;      /* '<S21>/PaLearn_PowerModeStatus'
                                        * 整车电源档位
                                        */
INT16U PaLearn_BackDefaultStopPos;     /* '<S21>/PaLearn_BackDefaultStopPos'
                                        * 副驾靠背硬止点
                                        */
INT16U PaLearn_FrontDefaulStoptPos;    /* '<S21>/PaLearn_FrontDefaulStoptPos'
                                        * 副驾腿托硬止点
                                        */
INT16U PaLearn_HeightDefaultStopPos;   /* '<S21>/PaLearn_HeightDefaultStopPos'
                                        * 副驾高度硬止点
                                        */
INT16U PaLearn_LengthDefaultStopPos;   /* '<S21>/PaLearn_LengthDefaultStopPos'
                                        * 副驾纵向硬止点
                                        */
INT8U PaLearn_AdjustEnable;            /* '<S21>/PaLearn_AdjustEnable'
                                        * 座椅调节:
                                        */
INT8U PaLearn_AnyoneHallErr;           /* '<S21>/PaLearn_AnyoneHallErr'
                                        * 副驾任一霍尔故障标志
                                        */
INT8U PaLearn_AnyoneRelayAdheErr;      /* '<S21>/PaLearn_AnyoneRelayAdheErr'
                                        * 副驾任一继电器粘连故障标志
                                        */
INT8U PaLearn_BackMotorTimeOutErr;     /* '<S21>/PaLearn_BackMotorTimeOutErr'
                                        * 副驾靠背电机运行超时标志
                                        */
INT8U PaLearn_BackStallErr;            /* '<S21>/PaLearn_BackStallErr'
                                        * 副驾靠背堵转标志位
                                        */
INT8U PaLearn_DescSession;             /* '<S21>/PaLearn_DescSession'
                                        * 会话
                                        */
INT8U PaLearn_DiagnoseLearnIn;         /* '<S21>/PaLearn_DiagnoseLearnIn'
                                        * 副驾请求学习标志
                                        */
INT8U PaLearn_FrontMotorTimeOutErr;    /* '<S21>/PaLearn_FrontMotorTimeOutErr'
                                        * 副驾腿托电机运行超时标志
                                        */
INT8U PaLearn_FrontStallErr;           /* '<S21>/PaLearn_FrontStallErr'
                                        * 副驾腿托堵转标志位
                                        */
INT8U PaLearn_GetRecoverDefaultFlag;   /* '<S21>/PaLearn_GetRecoverDefaultFlag'
                                        * 恢复出厂设置
                                        */
INT8U PaLearn_HeightMotorTimeOutErr;   /* '<S21>/PaLearn_HeightMotorTimeOutErr'
                                        * 副驾高度电机运行超时标志
                                        */
INT8U PaLearn_HeightStallErr;          /* '<S21>/PaLearn_HeightStallErr'
                                        * 副驾高度堵转标志位
                                        */
INT8U PaLearn_LearnSts;                /* '<S21>/PaLearn_LearnSts'
                                        * 副驾学习状态
                                        */
INT8U PaLearn_LengthMotorTimeOutErr;   /* '<S21>/PaLearn_LengthMotorTimeOutErr'
                                        * 副驾纵向电机运行超时标志
                                        */
INT8U PaLearn_LengthStallErr;          /* '<S21>/PaLearn_LengthStallErr'
                                        * 副驾纵向堵转标志位
                                        */
INT8U PaLearn_OTAMode;                 /* '<S21>/PaLearn_OTAMode'
                                        * OTA-P20为预留信号
                                        */
INT8U PaLearn_VehSpdUnder3KMFlag;      /* '<S21>/PaLearn_VehSpdUnder3KMFlag'
                                        * 车速大于3的标志位
                                        */
INT8U PaLearn_VoltSatisfy;             /* '<S21>/PaLearn_VoltSatisfy'
                                        * 电机调节电压是否满足
                                        */
INT8U PaLearn_WelcomeEnable;           /* '<S21>/PaLearn_WelcomeEnable'
                                        * 副驾迎宾使能状态
                                        */

/* Invariant block signals (default storage) */
const ConstB_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_ConstB =
{
  0.0                                  /* '<S20>/Constant6' */
};

/* Block signals (default storage) */
B_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_PaLearn_CtrlModel_T Appl_PaLearn_CtrlModel_M_;
RT_MODEL_Appl_PaLearn_CtrlModel_T *const Appl_PaLearn_CtrlModel_M =
  &Appl_PaLearn_CtrlModel_M_;
static void Appl_PaLearn_CtrlModel_LogicCtrl_Init(void);
static void Appl_PaLearn_CtrlModel_LogicCtrl(void);
static void Appl_PaLearn_CtrlModel_RTE(void);
static void Appl_PaLearn_CtrlModel_UpDataInputInfo(void);
static void Appl_PaLearn_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static INT32S Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(INT32S input);
static void Appl_PaLearn_CtrlModel_enter_atomic_Init(void);
static void Appl_PaLearn_CtrlModel_Learning(void);
static void Appl_PaLearn_CtrlModel_LearnLogicalDeal(const INT8U *LearnCondition,
  const INT8U *MtrCtrl_DiagnoseLearnIn_prev, const INT8U
  *MtrCtrl_AdjustEnable_prev);
static void Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal(void);
static void Appl_PaLearn_CtrlModel_enter_atomic_ResetInit(void);
static void Appl_PaLearn_CtrlModel_ResetLogicalDeal(const INT8U *LearnCondition,
  const INT8U *ResetReq, const enVehTypePrm *MtrCtrl_VehiclePrm_prev);
static void Appl_PaLearn_CtrlM_enter_internal_ResetLogicalDeal(void);
static INT32S Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(INT32S input)
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
static void Appl_PaLearn_CtrlModel_enter_atomic_Init(void)
{
  Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
  Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
  Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
    Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
    Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
    Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
    Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
  Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
  Appl_PaLearn_CtrlModel_DW.Hight = ((INT8U)D_Invalid);
  Appl_PaLearn_CtrlModel_DW.H_Move = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_DW.Length_c = ((INT8U)D_FirstMove);
  Appl_PaLearn_CtrlModel_DW.L_Move = 1.0;
  Appl_PaLearn_CtrlModel_DW.Back_e = ((INT8U)D_SecondMove);
  Appl_PaLearn_CtrlModel_DW.B_Move = enSWMoveCmd_enUP_FORWARD;
  Appl_PaLearn_CtrlModel_DW.Front_p = ((INT8U)D_Invalid);
  Appl_PaLearn_CtrlModel_DW.F_Move = enSWMoveCmd_en_NULL;
}

/* Function for Chart: '<S7>/Learn' */
static void Appl_PaLearn_CtrlModel_Learning(void)
{
  /* 根据配置的设定顺序执行 */
  if (Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
      Appl_PaLearn_CtrlModel_DW.Hight)
  {
    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_PaLearn_CtrlModel_IN_HeightLearn;
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = Appl_PaLearn_CtrlModel_DW.H_Move;
    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else if (Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_PaLearn_CtrlModel_DW.Length_c)
  {
    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_PaLearn_CtrlModel_IN_LengthLearn;
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    if (Appl_PaLearn_CtrlModel_DW.L_Move < 2.147483648E+9)
    {
      if (Appl_PaLearn_CtrlModel_DW.L_Move >= -2.147483648E+9)
      {
        Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd((INT32S)
          Appl_PaLearn_CtrlModel_DW.L_Move);
      }
      else
      {
        Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(MIN_int32_T);
      }
    }
    else
    {
      Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(MAX_int32_T);
    }

    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else if (Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_PaLearn_CtrlModel_DW.Front_p)
  {
    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_PaLearn_CtrlModel_IN_FrontLearn;
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = Appl_PaLearn_CtrlModel_DW.F_Move;
  }
  else if (Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts ==
           Appl_PaLearn_CtrlModel_DW.Back_e)
  {
    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_PaLearn_CtrlModel_IN_BackLearn;
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.BackLearnSW = Appl_PaLearn_CtrlModel_DW.B_Move;
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
  }
  else
  {
    /* 4个方向均学习完成后开始复位 */
    if (((Appl_PaLearn_CtrlModel_DW.Hight + Appl_PaLearn_CtrlModel_DW.Length_c)
         + Appl_PaLearn_CtrlModel_DW.Back_e) + Appl_PaLearn_CtrlModel_DW.Front_p
        == Appl_PaLearn_CtrlModel_DW.LearnResult)
    {
      Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enLearnAllSuccess;
      Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
        Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_LearnReady;
      Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
      Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
      Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
    }
  }
}

/* Function for Chart: '<S7>/Learn' */
static void Appl_PaLearn_CtrlModel_LearnLogicalDeal(const INT8U *LearnCondition,
  const INT8U *MtrCtrl_DiagnoseLearnIn_prev, const INT8U
  *MtrCtrl_AdjustEnable_prev)
{
  INT32S tmp;
  if (*MtrCtrl_AdjustEnable_prev !=
      Appl_PaLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start)
  {
    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
      Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
    Appl_PaLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enCfgW_ADJUST;
    Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
    Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
      Appl_PaLearn_CtrlModel_IN_LearnReady;
    Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
    Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
    Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
    Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
  }
  else
  {
    /* 诊断退出 */
    if ((*MtrCtrl_DiagnoseLearnIn_prev !=
         Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start) &&
        (Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start == ((BOOL)FALSE)))
    {
      Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
        Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
      Appl_PaLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enDescStop;
      Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
      Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_LearnReady;
      Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
      Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
      Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
        Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
      Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
    }
    else
    {
      /* 高度电机运行超时 */
      if (Appl_PaLearn_CtrlModel_DW.HeightLearnTimer >
          CAL_LearnSingleTimeMax_60s)
      {
        Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
          Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
        Appl_PaLearn_CtrlModel_B.LearnExitCause =
          enLearnExitCause_enMotorRunOverTime_H;
        Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
        Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
          Appl_PaLearn_CtrlModel_IN_LearnReady;
        Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
        Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
        Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
        Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
      }
      else
      {
        /* 学习条件不满足 */
        if (((BOOL)FALSE) == *LearnCondition)
        {
          Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
            Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
          Appl_PaLearn_CtrlModel_B.LearnExitCause =
            Appl_PaLearn_CtrlModel_B.LearnConditionExitCause;
          Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
          Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
            Appl_PaLearn_CtrlModel_IN_Init;
          Appl_PaLearn_CtrlModel_enter_atomic_Init();
        }
        else
        {
          /* 纵向电机运行超时 */
          if (Appl_PaLearn_CtrlModel_DW.LengthLearnTimer >
              CAL_LearnSingleTimeMax_60s)
          {
            Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
              Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
            Appl_PaLearn_CtrlModel_B.LearnExitCause =
              enLearnExitCause_enMotorRunOverTime_L;
            Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
            Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
              Appl_PaLearn_CtrlModel_IN_LearnReady;
            Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
            Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
            Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
              Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
              Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
              Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
              Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
            Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
            Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
          }
          else
          {
            /* 靠背电机运行超时 */
            if (Appl_PaLearn_CtrlModel_DW.BackLearnTimer >
                CAL_LearnSingleTimeMax_60s)
            {
              Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
              Appl_PaLearn_CtrlModel_B.LearnExitCause =
                enLearnExitCause_enMotorRunOverTime_B;
              Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
              Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
                Appl_PaLearn_CtrlModel_IN_LearnReady;
              Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
              Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
              Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                (enLearnSts_enNULL);
              Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
              Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
            }
            else
            {
              /* 腿托电机运行超时 */
              if (Appl_PaLearn_CtrlModel_DW.FrontLearnTimer >
                  CAL_LearnSingleTimeMax_60s)
              {
                Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                  Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
                Appl_PaLearn_CtrlModel_B.LearnExitCause =
                  enLearnExitCause_enMotorRunOverTime_F;
                Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
                Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
                  Appl_PaLearn_CtrlModel_IN_LearnReady;
                Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
                Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
                Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                  Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                  Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                  Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                  Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                  (enLearnSts_enNULL);
                Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
                Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
              }
              else
              {
                switch (Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal)
                {
                 case Appl_PaLearn_CtrlModel_IN_BackLearn:
                  if (((BOOL)TRUE) == PaLearn_BackStallErr)
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnResult +
                      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_PaLearn_CtrlModel_IN_Learning;
                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_PaLearn_CtrlModel_DW.BackLearnTimer++;
                  }
                  break;

                 case Appl_PaLearn_CtrlModel_IN_FrontLearn:
                  if (((BOOL)TRUE) == PaLearn_FrontStallErr)
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnResult +
                      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_PaLearn_CtrlModel_IN_Learning;
                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_PaLearn_CtrlModel_DW.FrontLearnTimer++;
                  }
                  break;

                 case Appl_PaLearn_CtrlModel_IN_HeightLearn:
                  /* 学习成功后记录当前的学习结果 */
                  if (((BOOL)TRUE) == PaLearn_HeightStallErr)
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnResult +
                      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_PaLearn_CtrlModel_IN_Learning;
                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_PaLearn_CtrlModel_DW.HeightLearnTimer++;
                  }
                  break;

                 case Appl_PaLearn_CtrlModel_IN_Learning:
                  Appl_PaLearn_CtrlModel_Learning();
                  break;

                 default:
                  if (((BOOL)TRUE) == PaLearn_LengthStallErr)
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnResult +
                      Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnResult = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
                      Appl_PaLearn_CtrlModel_IN_Learning;
                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
                    tmp = Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
                    Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);
                    Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
                      Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd
                      (enLearnSts_enNULL);

                    /* 根据之前配置的电机动作顺序
                       （1 2 3 4）查找动作顺序* */
                  }
                  else
                  {
                    tmp = Appl_PaLearn_CtrlModel_DW.LearnAllRunTime + 1;
                    if (tmp > 65535)
                    {
                      tmp = 65535;
                    }

                    Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = (INT16U)tmp;
                    Appl_PaLearn_CtrlModel_DW.LengthLearnTimer++;
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
static void Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal(void)
{
  Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_PositionTransform =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_PaLearn_CtrlModel_enter_atomic_ResetInit(void)
{
  Appl_PaLearn_CtrlModel_DW.CurrentResetSts = (INT8U)0x00;
  Appl_PaLearn_CtrlModel_DW.ResetResult = (INT8U)0x00;
  Appl_PaLearn_CtrlModel_B.BackPosiReq = (INT16U)0x00;
  Appl_PaLearn_CtrlModel_B.LengthPosiReq = (INT16U)0x00;
  Appl_PaLearn_CtrlModel_B.FrontPosiReq = (INT16U)0x00;
  Appl_PaLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
  Appl_PaLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
  Appl_PaLearn_CtrlModel_DW.RestTimer = 0U;
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_PaLearn_CtrlModel_ResetLogicalDeal(const INT8U *LearnCondition,
  const INT8U *ResetReq, const enVehTypePrm *MtrCtrl_VehiclePrm_prev)
{
  INT32S tmp;

  /* 复位成功 */
  tmp = ((Appl_PaLearn_CtrlModel_DW.Height + Appl_PaLearn_CtrlModel_DW.Length) +
         Appl_PaLearn_CtrlModel_DW.Back) + Appl_PaLearn_CtrlModel_DW.Front;
  if ((tmp == Appl_PaLearn_CtrlModel_DW.ResetResult) && (1 ==
       Appl_PaLearn_CtrlModel_DW.ResetType))
  {
    Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal();
    Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enResetSuccess;
    Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
      Appl_PaLearn_CtrlModel_IN_ResetInit;
    Appl_PaLearn_CtrlModel_enter_atomic_ResetInit();
    if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
    {
      Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
      Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
      Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
      Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
    }

    if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
        (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
    {
      if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
      {
        Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
      }
      else
      {
        tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
      }
    }
  }
  else
  {
    /* 退出复位或者任意方向复位失败 */
    if (((((BOOL)FALSE) == *ResetReq) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          PaLearn_HeightAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          PaLearn_BackAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          PaLearn_LengthAutoRunFlag) || (enSeatAutoRunSts_EN_SEAT_FAIL ==
          PaLearn_FrontAutoRunFlag) || (*MtrCtrl_VehiclePrm_prev !=
          Appl_PaLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start)) && (1 ==
         Appl_PaLearn_CtrlModel_DW.ResetType))
    {
      Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal();
      Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enResetFail;
      Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_ResetInit;
      Appl_PaLearn_CtrlModel_enter_atomic_ResetInit();
      if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
      {
        Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
        Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
        Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
        Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
      }

      if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
          (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
      {
        if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
        {
          Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
        }
        else
        {
          tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
        }
      }
    }
    else
    {
      /* 通过学习完成后复位的方式触发不反馈失败  且调节类型非复位行为  */
      if (((enSeatAutoRunSts_EN_SEAT_FAIL == PaLearn_HeightAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == PaLearn_BackAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == PaLearn_LengthAutoRunFlag) ||
           (enSeatAutoRunSts_EN_SEAT_FAIL == PaLearn_FrontAutoRunFlag) ||
           (*LearnCondition == ((BOOL)FALSE)) ||
           ((Appl_PaLearn_CtrlModel_DW.RestTimer > 2) &&
            (PaLearn_CurrMotorCtrlType != enSeatMotorRunTye_EN_ResetEnable)) ||
           (*MtrCtrl_VehiclePrm_prev !=
            Appl_PaLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start)) && (2 ==
           Appl_PaLearn_CtrlModel_DW.ResetType))
      {
        Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal();
        Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
          Appl_PaLearn_CtrlModel_IN_ResetInit;
        Appl_PaLearn_CtrlModel_enter_atomic_ResetInit();
        if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
        {
          Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
          Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
          Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
          Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
        }

        if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
            (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
        {
          if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
          {
            Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
            Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
          }
          else
          {
            tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
          }
        }
      }
      else
      {
        /* 通过学习完成后复位的方式触发不反馈成功 */
        if ((tmp == Appl_PaLearn_CtrlModel_DW.ResetResult) && (2 ==
             Appl_PaLearn_CtrlModel_DW.ResetType))
        {
          Appl_PaLearn_CtrlMo_exit_internal_ResetLogicalDeal();
          Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
            Appl_PaLearn_CtrlModel_IN_ResetInit;
          Appl_PaLearn_CtrlModel_enter_atomic_ResetInit();
          if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
          {
            Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
            Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
            Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
            Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
          }

          if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
              (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
          {
            if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
            {
              Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
              Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
            }
            else
            {
              tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
            }
          }
        }
        else
        {
          if (Appl_PaLearn_CtrlModel_DW.is_PositionTransform ==
              Appl_PaLearn_CtrlModel_IN_BM400)
          {
            /* 反馈位置坐标 */
            if (Appl_PaLearn_CtrlModel_DW.Back ==
                Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = PaLearn_BackDefaultStopPos +
                Appl_PaLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_PaLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
            }
            else if (Appl_PaLearn_CtrlModel_DW.Length ==
                     Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = PaLearn_LengthDefaultStopPos +
                Appl_PaLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_PaLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
            }
            else if (Appl_PaLearn_CtrlModel_DW.Front ==
                     Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
            {
              tmp = PaLearn_FrontDefaulStoptPos +
                Appl_PaLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              Appl_PaLearn_CtrlModel_B.FrontPosiReq = (INT16U)tmp;
            }
            else
            {
              if (Appl_PaLearn_CtrlModel_DW.Height ==
                  Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
              {
                Appl_PaLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
              }
            }
          }

          switch (Appl_PaLearn_CtrlModel_DW.is_ResetPosition)
          {
           case Appl_PaLearn_CtrlModel_IN_BackReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == PaLearn_BackAutoRunFlag)
            {
              tmp = Appl_PaLearn_CtrlModel_DW.ResetResult +
                Appl_PaLearn_CtrlModel_DW.Back;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                Appl_PaLearn_CtrlModel_IN_Reseting;
              tmp = Appl_PaLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_PaLearn_CtrlModel_IN_FrontReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == PaLearn_FrontAutoRunFlag)
            {
              tmp = Appl_PaLearn_CtrlModel_DW.ResetResult +
                Appl_PaLearn_CtrlModel_DW.Front;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                Appl_PaLearn_CtrlModel_IN_Reseting;
              tmp = Appl_PaLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_PaLearn_CtrlModel_IN_HeightReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == PaLearn_HeightAutoRunFlag)
            {
              tmp = Appl_PaLearn_CtrlModel_DW.ResetResult +
                Appl_PaLearn_CtrlModel_DW.Height;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                Appl_PaLearn_CtrlModel_IN_Reseting;
              tmp = Appl_PaLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           case Appl_PaLearn_CtrlModel_IN_Init_p:
            Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
              Appl_PaLearn_CtrlModel_IN_Reseting;
            tmp = Appl_PaLearn_CtrlModel_DW.MotorResetSts + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_PaLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            break;

           case Appl_PaLearn_CtrlModel_IN_LengthReset:
            if (enSeatAutoRunSts_EN_SEAT_SUCCESS == PaLearn_LengthAutoRunFlag)
            {
              tmp = Appl_PaLearn_CtrlModel_DW.ResetResult +
                Appl_PaLearn_CtrlModel_DW.Length;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.ResetResult = (INT8U)tmp;
              Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                Appl_PaLearn_CtrlModel_IN_Reseting;
              tmp = Appl_PaLearn_CtrlModel_DW.MotorResetSts + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_PaLearn_CtrlModel_DW.MotorResetSts = (INT8U)tmp;
            }
            break;

           default:
            /* 靠背复位 */
            if (Appl_PaLearn_CtrlModel_DW.Back ==
                Appl_PaLearn_CtrlModel_DW.MotorResetSts)
            {
              Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                Appl_PaLearn_CtrlModel_IN_BackReset;
              Appl_PaLearn_CtrlModel_DW.CurrentResetSts =
                Appl_PaLearn_CtrlModel_DW.Back;
            }
            else
            {
              /* 纵向复位 */
              if (Appl_PaLearn_CtrlModel_DW.Length ==
                  Appl_PaLearn_CtrlModel_DW.MotorResetSts)
              {
                Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                  Appl_PaLearn_CtrlModel_IN_LengthReset;
                Appl_PaLearn_CtrlModel_DW.CurrentResetSts =
                  Appl_PaLearn_CtrlModel_DW.Length;
              }
              else
              {
                /* 高度复位 */
                if (Appl_PaLearn_CtrlModel_DW.Height ==
                    Appl_PaLearn_CtrlModel_DW.MotorResetSts)
                {
                  Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                    Appl_PaLearn_CtrlModel_IN_HeightReset;
                  Appl_PaLearn_CtrlModel_DW.CurrentResetSts =
                    Appl_PaLearn_CtrlModel_DW.Height;
                }
                else
                {
                  /* 腿托复位 */
                  if (Appl_PaLearn_CtrlModel_DW.Front ==
                      Appl_PaLearn_CtrlModel_DW.MotorResetSts)
                  {
                    Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
                      Appl_PaLearn_CtrlModel_IN_FrontReset;
                    Appl_PaLearn_CtrlModel_DW.CurrentResetSts =
                      Appl_PaLearn_CtrlModel_DW.Front;
                  }
                }
              }
            }
            break;
          }

          /*  复位时间  */
          if (Appl_PaLearn_CtrlModel_DW.RestTimer <= 200)
          {
            tmp = Appl_PaLearn_CtrlModel_DW.RestTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_PaLearn_CtrlModel_DW.RestTimer = (INT8U)tmp;
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S9>/Reset' */
static void Appl_PaLearn_CtrlM_enter_internal_ResetLogicalDeal(void)
{
  INT32S tmp;
  if (enVehTypePrm_enP20 == PaLearn_VehiclePrm)
  {
    Appl_PaLearn_CtrlModel_DW.is_PositionTransform =
      Appl_PaLearn_CtrlModel_IN_P20;

    /* 轨道长度 50%  */
    tmp = PaLearn_LengthDefaultStopPos + 521;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_PaLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
    tmp = PaLearn_BackDefaultStopPos + 2180;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    Appl_PaLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
  }
  else
  {
    Appl_PaLearn_CtrlModel_DW.is_PositionTransform =
      Appl_PaLearn_CtrlModel_IN_BM400;

    /* 反馈位置坐标 */
    if (Appl_PaLearn_CtrlModel_DW.Back ==
        Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = PaLearn_BackDefaultStopPos +
        Appl_PaLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_PaLearn_CtrlModel_B.BackPosiReq = (INT16U)tmp;
    }
    else if (Appl_PaLearn_CtrlModel_DW.Length ==
             Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = PaLearn_LengthDefaultStopPos +
        Appl_PaLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_PaLearn_CtrlModel_B.LengthPosiReq = (INT16U)tmp;
    }
    else if (Appl_PaLearn_CtrlModel_DW.Front ==
             Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
    {
      tmp = PaLearn_FrontDefaulStoptPos +
        Appl_PaLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_PaLearn_CtrlModel_B.FrontPosiReq = (INT16U)tmp;
    }
    else
    {
      if (Appl_PaLearn_CtrlModel_DW.Height ==
          Appl_PaLearn_CtrlModel_DW.CurrentResetSts)
      {
        Appl_PaLearn_CtrlModel_B.HeightPosiReq = (INT16U)0x00;
      }
    }
  }

  Appl_PaLearn_CtrlModel_DW.is_ResetPosition = Appl_PaLearn_CtrlModel_IN_Init_p;
  Appl_PaLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_PaLearn_CtrlModel_DW.ResetResult = 0U;
  Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
  if (1 == Appl_PaLearn_CtrlModel_DW.ResetType)
  {
    Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enResetWaiting;
  }

  /*  复位时间  */
  if (Appl_PaLearn_CtrlModel_DW.RestTimer <= 200)
  {
    tmp = Appl_PaLearn_CtrlModel_DW.RestTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    Appl_PaLearn_CtrlModel_DW.RestTimer = (INT8U)tmp;
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaLearn_CtrlModel_LogicCtrl_Init(void)
{
  Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_active_c1_Appl_PaLearn_CtrlModel = 0U;
  Appl_PaLearn_CtrlModel_B.LearnConditionExitCause = enLearnExitCause_enInvalid;
  Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_active_c42_Appl_PaLearn_CtrlModel = 0U;
  Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.Hight = 0U;
  Appl_PaLearn_CtrlModel_DW.Length_c = 0U;
  Appl_PaLearn_CtrlModel_DW.Back_e = 0U;
  Appl_PaLearn_CtrlModel_DW.H_Move = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_DW.L_Move = 0.0;
  Appl_PaLearn_CtrlModel_DW.B_Move = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_DW.F_Move = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
  Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
  Appl_PaLearn_CtrlModel_DW.Front_p = 0U;
  Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
  Appl_PaLearn_CtrlModel_DW.HeightLearnTimer = 0.0;
  Appl_PaLearn_CtrlModel_DW.LengthLearnTimer = 0.0;
  Appl_PaLearn_CtrlModel_DW.BackLearnTimer = 0.0;
  Appl_PaLearn_CtrlModel_DW.FrontLearnTimer = 0.0;
  Appl_PaLearn_CtrlModel_B.HeightLearnSW = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_B.LengthLearnSW = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_B.BackLearnSW = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_B.FrontLearnSW = enSWMoveCmd_en_NULL;
  Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
  Appl_PaLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
  Appl_PaLearn_CtrlModel_DW.is_active_c7_Appl_PaLearn_CtrlModel = 0U;
  Appl_PaLearn_CtrlModel_DW.is_c7_Appl_PaLearn_CtrlModel =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_PositionTransform =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_ResetPosition =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.is_active_c2_Appl_PaLearn_CtrlModel = 0U;
  Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
    Appl_PaLearn_CtrlModel_IN_NO_ACTIVE_CHILD;
  Appl_PaLearn_CtrlModel_DW.Height = 0U;
  Appl_PaLearn_CtrlModel_DW.Length = 0U;
  Appl_PaLearn_CtrlModel_DW.Back = 0U;
  Appl_PaLearn_CtrlModel_DW.Front = 0U;
  Appl_PaLearn_CtrlModel_DW.CurrentResetSts = 0U;
  Appl_PaLearn_CtrlModel_DW.ResetResult = 0U;
  Appl_PaLearn_CtrlModel_DW.MotorResetSts = 0U;
  Appl_PaLearn_CtrlModel_DW.ResetType = 0U;
  Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
  Appl_PaLearn_CtrlModel_DW.RestTimer = 0U;
  Appl_PaLearn_CtrlModel_B.HeightPosiReq = 0U;
  Appl_PaLearn_CtrlModel_B.LengthPosiReq = 0U;
  Appl_PaLearn_CtrlModel_B.BackPosiReq = 0U;
  Appl_PaLearn_CtrlModel_B.FrontPosiReq = 0U;
  Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaLearn_CtrlModel_LogicCtrl(void)
{
  BOOL rtb_AND;
  INT8U LearnCondition;
  INT8U MtrCtrl_DiagnoseLearnIn_prev;
  INT8U MtrCtrl_AdjustEnable_prev;
  DOUBLE MtrCtrl_HIDO_SeatsButtonResetReq_prev;
  enLearnSts MtrCtrl_LearnSts_prev;
  enVehTypePrm MtrCtrl_VehiclePrm_prev;
  INT32S tmp;
  if (Appl_PaLearn_CtrlModel_DW.is_active_c1_Appl_PaLearn_CtrlModel == 0U)
  {
    Appl_PaLearn_CtrlModel_DW.is_active_c1_Appl_PaLearn_CtrlModel = 1U;
    Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
      Appl_PaLearn_CtrlModel_IN_Enable;
    LearnCondition = ((BOOL)TRUE);
    Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
      enLearnExitCause_enInvalid;
  }
  else if (Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment ==
           Appl_PaLearn_CtrlModel_IN_Disable)
  {
    LearnCondition = ((BOOL)FALSE);

    /* 电压在9-16V、非OTA
       无霍尔故障、继电器粘连故障、车速条件满足  */
    if ((((BOOL)TRUE) == PaLearn_VoltSatisfy) && (((BOOL)FALSE) ==
         PaLearn_OTAMode) && (((BOOL)FALSE) == PaLearn_AnyoneHallErr) && (((BOOL)
          FALSE) == PaLearn_AnyoneRelayAdheErr) && (((BOOL)TRUE) ==
         PaLearn_VehSpdUnder3KMFlag) && (enSeatMotorRunTye_EN_ManualEnable !=
         PaLearn_CurrMotorCtrlType) && (PaLearn_AdjustEnable != 0) &&
        (PaLearn_WelcomeEnable != 0))
    {
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Enable;
      LearnCondition = ((BOOL)TRUE);
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enInvalid;
    }
  }
  else
  {
    LearnCondition = ((BOOL)TRUE);

    /* 电压非9-16V、OTA
       任一霍尔故障、继电器粘连故障、车速条件不满足 */
    if (((BOOL)FALSE) != PaLearn_AnyoneRelayAdheErr)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enRelayAdhesionFault;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) != PaLearn_AnyoneHallErr)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enHallFault;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) != PaLearn_OTAMode)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause = enLearnExitCause_enOTA;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)TRUE) != PaLearn_VehSpdUnder3KMFlag)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enVehSpeed;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (enSeatMotorRunTye_EN_ManualEnable == PaLearn_CurrMotorCtrlType)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enManualInterupt;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (((BOOL)FALSE) == PaLearn_VoltSatisfy)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enVoltFault;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else if (PaLearn_AdjustEnable == 0)
    {
      Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
        enLearnExitCause_enCfgW_ADJUST;
      Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
        Appl_PaLearn_CtrlModel_IN_Disable;
      LearnCondition = ((BOOL)FALSE);
    }
    else
    {
      if (0 == PaLearn_WelcomeEnable)
      {
        Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
          enLearnExitCause_enCfgW_MEMORY;
        Appl_PaLearn_CtrlModel_DW.is_PublicPreconditionJudgment =
          Appl_PaLearn_CtrlModel_IN_Disable;
        LearnCondition = ((BOOL)FALSE);
      }
    }
  }

  MtrCtrl_DiagnoseLearnIn_prev =
    Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start;
  Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start =
    PaLearn_DiagnoseLearnIn;
  MtrCtrl_AdjustEnable_prev =
    Appl_PaLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start;
  Appl_PaLearn_CtrlModel_DW.MtrCtrl_AdjustEnable_start = PaLearn_AdjustEnable;
  if (Appl_PaLearn_CtrlModel_DW.is_active_c42_Appl_PaLearn_CtrlModel == 0U)
  {
    Appl_PaLearn_CtrlModel_DW.is_active_c42_Appl_PaLearn_CtrlModel = 1U;
    Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
      Appl_PaLearn_CtrlModel_IN_Init;
    Appl_PaLearn_CtrlModel_enter_atomic_Init();
  }
  else
  {
    switch (Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel)
    {
     case Appl_PaLearn_CtrlModel_IN_Init:
      /*  满足学习条件 */
      if (((BOOL)TRUE) == LearnCondition)
      {
        Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
          Appl_PaLearn_CtrlModel_IN_LearnReady;
        Appl_PaLearn_CtrlModel_B.Sts = ((BOOL)FALSE);
        Rte_SetVfb_DrLearnEnable(Appl_PaLearn_CtrlModel_B.Sts);
        Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
          Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
        Appl_PaLearn_CtrlModel_DW.LearnResult = 0U;
        Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = 0U;
      }
      break;

     case Appl_PaLearn_CtrlModel_IN_LearnLogicalDeal:
      Appl_PaLearn_CtrlModel_LearnLogicalDeal(&LearnCondition,
        &MtrCtrl_DiagnoseLearnIn_prev, &MtrCtrl_AdjustEnable_prev);
      break;

     default:
      /* 学习条件不满足 */
      if (((BOOL)FALSE) == LearnCondition)
      {
        Appl_PaLearn_CtrlModel_B.LearnExitCause =
          Appl_PaLearn_CtrlModel_B.LearnConditionExitCause;
        Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
          Appl_PaLearn_CtrlModel_IN_Init;
        Appl_PaLearn_CtrlModel_enter_atomic_Init();
      }
      else
      {
        /* 诊断请求自动学习 */
        if ((MtrCtrl_DiagnoseLearnIn_prev !=
             Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start) &&
            (Appl_PaLearn_CtrlModel_DW.MtrCtrl_DiagnoseLearnIn_start == ((BOOL)
              TRUE)))
        {
          Appl_PaLearn_CtrlModel_DW.HeightLearnTimer = 0.0;
          Appl_PaLearn_CtrlModel_DW.LengthLearnTimer = 0.0;
          Appl_PaLearn_CtrlModel_DW.BackLearnTimer = 0.0;
          Appl_PaLearn_CtrlModel_DW.FrontLearnTimer = 0.0;
          Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enLearnning;
          Appl_PaLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
          Appl_PaLearn_CtrlModel_DW.is_c42_Appl_PaLearn_CtrlModel =
            Appl_PaLearn_CtrlModel_IN_LearnLogicalDeal;
          Appl_PaLearn_CtrlModel_DW.is_LearnLogicalDeal =
            Appl_PaLearn_CtrlModel_IN_Learning;
          Appl_PaLearn_CtrlModel_DW.LearnAllRunTime = 0U;
          tmp = Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_PaLearn_CtrlModel_DW.MotorMtrCtrl_LearnSts = (INT8U)tmp;
          Appl_PaLearn_CtrlModel_B.HeightLearnSW = (enSWMoveCmd)
            Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_PaLearn_CtrlModel_B.LengthLearnSW = (enSWMoveCmd)
            Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_PaLearn_CtrlModel_B.BackLearnSW = (enSWMoveCmd)
            Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);
          Appl_PaLearn_CtrlModel_B.FrontLearnSW = (enSWMoveCmd)
            Appl_PaLearn_CtrlModel_safe_cast_to_enSWMoveCmd(enLearnSts_enNULL);

          /* 根据之前配置的电机动作顺序
             （1 2 3 4）查找动作顺序* */
        }
      }
      break;
    }
  }

  rtb_AND = ((PaLearn_LengthDefaultStopPos != 0) &&
             (PaLearn_LengthDefaultStopPos != 65535) &&
             (PaLearn_BackDefaultStopPos != 0) && (PaLearn_BackDefaultStopPos !=
              65535));
  if (Appl_PaLearn_CtrlModel_DW.is_active_c7_Appl_PaLearn_CtrlModel == 0U)
  {
    Appl_PaLearn_CtrlModel_DW.is_active_c7_Appl_PaLearn_CtrlModel = 1U;
    Appl_PaLearn_CtrlModel_DW.is_c7_Appl_PaLearn_CtrlModel =
      Appl_PaLearn_CtrlModel_IN_Inactive;
    MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)FALSE);
  }
  else if (Appl_PaLearn_CtrlModel_DW.is_c7_Appl_PaLearn_CtrlModel ==
           Appl_PaLearn_CtrlModel_IN_Active)
  {
    MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)TRUE);

    /* 电源模式非ON档 */
    if ((enIgnSts_eOn != PaLearn_PowerModeStatus) || (((BOOL)TRUE) ==
         PaLearn_AnyoneHallErr) || (((BOOL)FALSE) == PaLearn_AnyoneRelayAdheErr)
        || (((BOOL)TRUE) != rtb_AND) || (((BOOL)TRUE) ==
         PaLearn_GetRecoverDefaultFlag) || (((BOOL)FALSE) ==
         Appl_PaLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm))
    {
      Appl_PaLearn_CtrlModel_DW.is_c7_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_Inactive;
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
    if ((enIgnSts_eOn == PaLearn_PowerModeStatus) && (((BOOL)FALSE) ==
         PaLearn_AnyoneHallErr) && (((BOOL)FALSE) == PaLearn_AnyoneRelayAdheErr)
        && (((BOOL)TRUE) == rtb_AND) && (((BOOL)TRUE) ==
         Appl_PaLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm))
    {
      Appl_PaLearn_CtrlModel_DW.is_c7_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_Active;
      MtrCtrl_DiagnoseLearnIn_prev = ((BOOL)TRUE);
    }
  }

  MtrCtrl_HIDO_SeatsButtonResetReq_prev =
    Appl_PaLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start;
  Appl_PaLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start =
    Appl_PaLearn_CtrlModel_ConstB.MtrCtrl_HIDO_SeatsButtonResetReq;
  MtrCtrl_LearnSts_prev = Appl_PaLearn_CtrlModel_DW.MtrCtrl_LearnSts_start;
  Appl_PaLearn_CtrlModel_DW.MtrCtrl_LearnSts_start =
    Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts;
  MtrCtrl_VehiclePrm_prev = Appl_PaLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start;
  Appl_PaLearn_CtrlModel_DW.MtrCtrl_VehiclePrm_start = PaLearn_VehiclePrm;
  if (Appl_PaLearn_CtrlModel_DW.is_active_c2_Appl_PaLearn_CtrlModel == 0U)
  {
    Appl_PaLearn_CtrlModel_DW.is_active_c2_Appl_PaLearn_CtrlModel = 1U;
    Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
      Appl_PaLearn_CtrlModel_IN_ResetInit;
    Appl_PaLearn_CtrlModel_enter_atomic_ResetInit();
    if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
    {
      Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
      Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
      Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
      Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
    }

    if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
        (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
    {
      if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
      {
        Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
        Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
      }
      else
      {
        tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
      }
    }
  }
  else if (Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel ==
           Appl_PaLearn_CtrlModel_IN_ResetInit)
  {
    /* （满足复位条件且收到复位信号）或（学习状态变为成功） */
    if ((((BOOL)TRUE) == MtrCtrl_DiagnoseLearnIn_prev) &&
        ((MtrCtrl_HIDO_SeatsButtonResetReq_prev !=
          Appl_PaLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start) &&
         (Appl_PaLearn_CtrlModel_DW.MtrCtrl_HIDO_SeatsButtonResetReq_start ==
          0x01)) && (enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
    {
      Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
      Appl_PaLearn_CtrlModel_DW.RestTimer = 0U;
      Appl_PaLearn_CtrlModel_DW.ResetType = 1U;
      Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
      Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_SecondMove);
      Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_FirstMove);
      Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_ThirdlyMove);
      Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enResetWaiting;
      Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_ResetLogicalDeal;
      Appl_PaLearn_CtrlM_enter_internal_ResetLogicalDeal();
    }
    else if ((MtrCtrl_LearnSts_prev !=
              Appl_PaLearn_CtrlModel_DW.MtrCtrl_LearnSts_start) &&
             (Appl_PaLearn_CtrlModel_DW.MtrCtrl_LearnSts_start ==
              enLearnSts_enLearnAllSuccess))
    {
      Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
      Appl_PaLearn_CtrlModel_DW.RestTimer = 0U;
      Appl_PaLearn_CtrlModel_DW.ResetType = 2U;
      Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
      Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
      Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
      Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
      Appl_PaLearn_CtrlModel_DW.is_c2_Appl_PaLearn_CtrlModel =
        Appl_PaLearn_CtrlModel_IN_ResetLogicalDeal;
      Appl_PaLearn_CtrlM_enter_internal_ResetLogicalDeal();
    }
    else
    {
      if (!(enVehTypePrm_enBM400 == PaLearn_VehiclePrm))
      {
        Appl_PaLearn_CtrlModel_DW.Height = ((INT8U)D_Invalid);
        Appl_PaLearn_CtrlModel_DW.Length = ((INT8U)D_FirstMove);
        Appl_PaLearn_CtrlModel_DW.Back = ((INT8U)D_SecondMove);
        Appl_PaLearn_CtrlModel_DW.Front = ((INT8U)D_Invalid);
      }

      if ((Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetFail) ||
          (Appl_PaLearn_CtrlModel_B.ResetSts == enResetSts_enResetSuccess))
      {
        if (Appl_PaLearn_CtrlModel_DW.SendTimer > 10)
        {
          Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
          Appl_PaLearn_CtrlModel_DW.SendTimer = 0U;
        }
        else
        {
          tmp = Appl_PaLearn_CtrlModel_DW.SendTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_PaLearn_CtrlModel_DW.SendTimer = (INT8U)tmp;
        }
      }
    }
  }
  else
  {
    Appl_PaLearn_CtrlModel_ResetLogicalDeal(&LearnCondition,
      &MtrCtrl_DiagnoseLearnIn_prev, &MtrCtrl_VehiclePrm_prev);
  }

  Appl_PaLearn_CtrlModel_B.DataTypeConversion = rtb_AND;
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_PaLearn_CtrlModel_RTE(void)
{
  PaLearn_AdjustEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
  PaLearn_AnyoneHallErr = Rte_GetVfb_PaAnyoneHallErr( );
  PaLearn_AnyoneRelayAdheErr = Rte_GetVfb_PaAnyoneRelayAdheErr( );
  PaLearn_BackAutoRunFlag = Rte_GetVfb_PaBackAutoRunFlag( );
  PaLearn_BackDefaultStopPos = Cdd_GetMotorHardStop(EN_PassengerBack);
  PaLearn_BackMotorTimeOutErr = Rte_GetVfb_PaBackMotorTimeOutErr( );
  PaLearn_BackStallErr = Rte_GetVfb_PaBackStallErr( );
  PaLearn_CurrMotorCtrlType = Rte_GetVfb_PaMoveType( );
  PaLearn_DescSession = DescGetcDescSession( );
  PaLearn_DiagnoseLearnIn = Rte_GetVfb_PaLearnEnable( );
  PaLearn_FrontAutoRunFlag = Rte_GetVfb_PaFrontAutoRunFlag( );
  PaLearn_FrontDefaulStoptPos = Cdd_GetMotorHardStop(EN_PaResever_2);
  PaLearn_FrontMotorTimeOutErr = Rte_GetVfb_PaFrontMotorTimeOutErr( );
  PaLearn_FrontStallErr = Rte_GetVfb_PaFrontStallErr( );
  PaLearn_GetRecoverDefaultFlag = GetRecoverDefaultFlag( );
  PaLearn_HeightAutoRunFlag = Rte_GetVfb_PaHeightAutoRunFlag( );
  PaLearn_HeightDefaultStopPos = Cdd_GetMotorHardStop(EN_PaResever_1);
  PaLearn_HeightMotorTimeOutErr = Rte_GetVfb_PaHeightMotorTimeOutErr( );
  PaLearn_HeightStallErr = Rte_GetVfb_PaHeightStallErr( );
  PaLearn_LearnSts = Rte_GetVfb_PaLearnSts( );
  PaLearn_LengthAutoRunFlag = Rte_GetVfb_PaLengthAutoRunFlag( );
  PaLearn_LengthDefaultStopPos = Cdd_GetMotorHardStop(EN_PassengerLength);
  PaLearn_LengthMotorTimeOutErr = Rte_GetVfb_PaLengthMotorTimeOutErr( );
  PaLearn_LengthStallErr = Rte_GetVfb_PaLengthStallErr( );
  PaLearn_OTAMode = Vfb_Reserved_0( );
  PaLearn_PowerModeStatus = Rte_GetVfb_PowerMode( );
  PaLearn_VehSpdUnder3KMFlag = DescCheckVehSpd( );
  PaLearn_VehiclePrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  PaLearn_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  PaLearn_WelcomeEnable = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaLearn_CtrlModel_UpDataInputInfo(void)
{
  Appl_PaLearn_CtrlModel_RTE();
  Appl_PaLearn_CtrlModel_B.MtrCtrl_BackGear_4Posi = ((BOOL)FALSE);
  Appl_PaLearn_CtrlModel_B.MtrCtrl_LengthGear_0Posi = ((BOOL)FALSE);
  Appl_PaLearn_CtrlModel_B.MtrCtrl_enFrontGear_0Posi = ((BOOL)FALSE);
  Appl_PaLearn_CtrlModel_B.MtrCtrl_MotorResetFunPrm = ((BOOL)TRUE);
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_PaLearn_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_PaLearnSts(Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts);
  Rte_SetVfb_PaHeightLearnCmd(Appl_PaLearn_CtrlModel_B.HeightLearnSW);
  Rte_SetVfb_PaLengthLearnCmd(Appl_PaLearn_CtrlModel_B.LengthLearnSW);
  Rte_SetVfb_PaBackLearnCmd(Appl_PaLearn_CtrlModel_B.BackLearnSW);
  Rte_SetVfb_PaFrontLearnCmd(Appl_PaLearn_CtrlModel_B.FrontLearnSW);
  Rte_SetVfb_PaLearnExitCause(Appl_PaLearn_CtrlModel_B.LearnExitCause);
  Rte_SetVfb_PaLearnResult(Appl_PaLearn_CtrlModel_B.DataTypeConversion);
  Rte_SetVfb_PaHeightResetReqPosi(Appl_PaLearn_CtrlModel_B.HeightPosiReq);
  Rte_SetVfb_PaLengthResetReqPosi(Appl_PaLearn_CtrlModel_B.LengthPosiReq);
  Rte_SetVfb_PaBackResetReqPosi(Appl_PaLearn_CtrlModel_B.BackPosiReq);
  Rte_SetVfb_PaFrontResetReqPosi(Appl_PaLearn_CtrlModel_B.FrontPosiReq);
}

/* Model step function */
void Appl_PaLearn_CtrlModel_step(void)
{
  Appl_PaLearn_CtrlModel_UpDataInputInfo();
  Appl_PaLearn_CtrlModel_LogicCtrl();
  Appl_PaLearn_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_PaLearn_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_PaLearn_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_PaLearn_CtrlModel_B), 0,
                sizeof(B_Appl_PaLearn_CtrlModel_T));

  {
    Appl_PaLearn_CtrlModel_B.HeightLearnSW = enSWMoveCmd_en_NULL;
    Appl_PaLearn_CtrlModel_B.LengthLearnSW = enSWMoveCmd_en_NULL;
    Appl_PaLearn_CtrlModel_B.BackLearnSW = enSWMoveCmd_en_NULL;
    Appl_PaLearn_CtrlModel_B.FrontLearnSW = enSWMoveCmd_en_NULL;
    Appl_PaLearn_CtrlModel_B.ResetSts = enResetSts_enInactive;
    Appl_PaLearn_CtrlModel_B.MtrCtrl_LearnSts = enLearnSts_enNULL;
    Appl_PaLearn_CtrlModel_B.LearnExitCause = enLearnExitCause_enInvalid;
    Appl_PaLearn_CtrlModel_B.LearnConditionExitCause =
      enLearnExitCause_enInvalid;
  }

  /* exported global signals */
  PaLearn_VehiclePrm = enVehTypePrm_enP20;
  PaLearn_CurrMotorCtrlType = enSeatMotorRunTye_EN_NULL;
  PaLearn_BackAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaLearn_FrontAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaLearn_HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaLearn_LengthAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  PaLearn_PowerModeStatus = enIgnSts_eOff;
  PaLearn_BackDefaultStopPos = ((INT16U)0U);
  PaLearn_FrontDefaulStoptPos = ((INT16U)0U);
  PaLearn_HeightDefaultStopPos = ((INT16U)0U);
  PaLearn_LengthDefaultStopPos = ((INT16U)0U);
  PaLearn_AdjustEnable = ((INT8U)0U);
  PaLearn_AnyoneHallErr = ((INT8U)0U);
  PaLearn_AnyoneRelayAdheErr = ((INT8U)0U);
  PaLearn_BackMotorTimeOutErr = ((INT8U)0U);
  PaLearn_BackStallErr = ((INT8U)0U);
  PaLearn_DescSession = ((INT8U)0U);
  PaLearn_DiagnoseLearnIn = ((INT8U)0U);
  PaLearn_FrontMotorTimeOutErr = ((INT8U)0U);
  PaLearn_FrontStallErr = ((INT8U)0U);
  PaLearn_GetRecoverDefaultFlag = ((INT8U)0U);
  PaLearn_HeightMotorTimeOutErr = ((INT8U)0U);
  PaLearn_HeightStallErr = ((INT8U)0U);
  PaLearn_LearnSts = ((INT8U)0U);
  PaLearn_LengthMotorTimeOutErr = ((INT8U)0U);
  PaLearn_LengthStallErr = ((INT8U)0U);
  PaLearn_OTAMode = ((INT8U)0U);
  PaLearn_VehSpdUnder3KMFlag = ((INT8U)0U);
  PaLearn_VoltSatisfy = ((INT8U)0U);
  PaLearn_WelcomeEnable = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_PaLearn_CtrlModel_DW, 0,
                sizeof(DW_Appl_PaLearn_CtrlModel_T));
  Appl_PaLearn_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
