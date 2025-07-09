/*
 * File: Appl_PowerMangeModel.c
 *
 * Code generated for Simulink model 'Appl_PowerMangeModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Apr 28 11:14:22 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_PowerMangeModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_POWER_ADJUST_15800MV
#error The variable for the parameter "D_POWER_ADJUST_15800MV" is not defined
#endif

#ifndef D_POWER_ADJUST_7800MV
#error The variable for the parameter "D_POWER_ADJUST_7800MV" is not defined
#endif

#ifndef D_POWER_HIGH_DN
#error The variable for the parameter "D_POWER_HIGH_DN" is not defined
#endif

#ifndef D_POWER_HIGH_UP
#error The variable for the parameter "D_POWER_HIGH_UP" is not defined
#endif

#ifndef D_POWER_LOW_DN
#error The variable for the parameter "D_POWER_LOW_DN" is not defined
#endif

#ifndef D_POWER_LOW_UP
#error The variable for the parameter "D_POWER_LOW_UP" is not defined
#endif

#ifndef D_POWER_NORMAL_DN
#error The variable for the parameter "D_POWER_NORMAL_DN" is not defined
#endif

#ifndef D_POWER_NORMAL_UP
#error The variable for the parameter "D_POWER_NORMAL_UP" is not defined
#endif

#ifndef D_POWER_OVER_DN
#error The variable for the parameter "D_POWER_OVER_DN" is not defined
#endif

#ifndef D_POWER_STOP_UP
#error The variable for the parameter "D_POWER_STOP_UP" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_POWER_Invalid
#error The variable for the parameter "D_POWER_Invalid" is not defined
#endif

/* Named constants for Chart: '<S16>/Chart' */
#define Appl_PowerMangeModel_IN_Init   ((INT8U)1U)
#define Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_PowerMangeModel_IN_VoltDownWait ((INT8U)2U)
#define Appl_PowerMangeModel_IN_VoltUpWait ((INT8U)3U)

/* Named constants for Chart: '<S6>/AdjustVoltage' */
#define Appl_PowerMangeModel_IN_AbnormalCounting ((INT8U)1U)
#define Appl_PowerMangeModel_IN_Default ((INT8U)1U)
#define Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d ((INT8U)0U)
#define Appl_PowerMangeModel_IN_NormalCounting ((INT8U)2U)
#define Appl_PowerMangeModel_IN_VoltageChecking ((INT8U)2U)

/* Named constants for Chart: '<S8>/CrankUnload' */
#define Appl_PowerMangeModel_IN_CRANK  ((INT8U)1U)
#define Appl_PowerMangeModel_IN_Init_j ((INT8U)2U)

/* Named constants for Chart: '<S8>/KL30VoltageModeChange' */
#define Appl_PowerMangeModel_IN_AboveNormal ((INT8U)1U)
#define Appl_PowerMangeModel_IN_BelowNormal ((INT8U)2U)
#define Appl_PowerMangeModel_IN_High   ((INT8U)1U)
#define Appl_PowerMangeModel_IN_Low    ((INT8U)1U)
#define Appl_PowerMangeModel_IN_Normal ((INT8U)3U)
#define Appl_PowerMangeModel_IN_Over   ((INT8U)2U)
#define Appl_PowerMangeModel_IN_Stop   ((INT8U)2U)

/* Exported block signals */
enSeatMotorRunTye Appl_PwrMng_DriverRunType;/* '<S23>/Appl_PwrMng_DriverRunType'
                                             * 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节
                                             */
enSeatMotorRunTye Appl_PwrMng_PassengerRunType;/* '<S23>/Appl_PwrMng_PassengerRunType'
                                                * 电机动作类型：&#10;0：无动作；&#10;1：HUM；&#10;2：舒适；&#10;3：记忆调用；&#10;4：手动调节；&#10;5：学习调节&#10;6：复位调节&#10;7：档位调节-BM400&#10;8：小憩调节(副驾无)
                                                */
INT16U Appl_PwrMng_SupplyVoltage;      /* '<S23>/Appl_PwrMng_SupplyVoltage'
                                        * 电源电压值
                                        */
INT8U Appl_PwrMng_BCM_PowerMode;       /* '<S23>/Appl_PwrMng_BCM_PowerMode'
                                        * 整车低压电源状态：&#10;0x0:Off &#10;0x1:Acc &#10;0x2:On &#10;0x3:Crank&#10;0x4~0x7:Reserved
                                        */

/* Invariant block signals (default storage) */
const ConstB_Appl_PowerMangeModel_T Appl_PowerMangeModel_ConstB =
{
  3U                                   /* '<S7>/Data Type Conversion2' */
};

/* Block signals (default storage) */
B_Appl_PowerMangeModel_T Appl_PowerMangeModel_B;

/* Block states (default storage) */
DW_Appl_PowerMangeModel_T Appl_PowerMangeModel_DW;

/* Real-time model */
RT_MODEL_Appl_PowerMangeModel_T Appl_PowerMangeModel_M_;
RT_MODEL_Appl_PowerMangeModel_T *const Appl_PowerMangeModel_M =
  &Appl_PowerMangeModel_M_;

/* Exported data definition */

/* Const memory section */
/* Definition for custom storage class: Const */
const INT8U CAL_DownVolt_600ms = 60U;  /* 低压切换时间：600ms */
const INT8U CAL_Filiter_500ms = 50U;   /* 调节电机电压滤波时间：500ms */
const INT8U CAL_UpVolt_200ms = 20U;    /* 高压切换时间：200ms */
static void Appl_PowerMangeModel_ModeChangeFunction_Init(INT16U *rty_UpCount,
  INT16U *rty_DownCount, DW_ModeChangeFunction_Appl_PowerMangeModel_T *localDW);
static void Appl_PowerMangeModel_ModeChangeFunction(INT16U rtu_Voltage, INT16U
  rtu_DownValue, INT16U rtu_UpValue, INT16U *rty_UpCount, INT16U *rty_DownCount,
  DW_ModeChangeFunction_Appl_PowerMangeModel_T *localDW);
static void Appl_PowerMangeModel_LogicCtrl_Init(void);
static void Appl_PowerMangeModel_LogicCtrl(void);
static void Appl_PowerMangeModel_RTE(void);
static void Appl_PowerMangeModel_UpDataInputInfo(void);
static void Appl_PowerMangeModel_UpDataOutputInfo(void);

/*
 * System initialize for function-call system:
 *    '<S15>/ModeChangeFunction'
 *    '<S15>/ModeChangeFunction1'
 *    '<S15>/ModeChangeFunction2'
 */
static void Appl_PowerMangeModel_ModeChangeFunction_Init(INT16U *rty_UpCount,
  INT16U *rty_DownCount, DW_ModeChangeFunction_Appl_PowerMangeModel_T *localDW)
{
  localDW->is_active_c37_Appl_PowerMangeModel = 0U;
  localDW->is_c37_Appl_PowerMangeModel = Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD;
  *rty_UpCount = 0U;
  *rty_DownCount = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S15>/ModeChangeFunction'
 *    '<S15>/ModeChangeFunction1'
 *    '<S15>/ModeChangeFunction2'
 */
static void Appl_PowerMangeModel_ModeChangeFunction(INT16U rtu_Voltage, INT16U
  rtu_DownValue, INT16U rtu_UpValue, INT16U *rty_UpCount, INT16U *rty_DownCount,
  DW_ModeChangeFunction_Appl_PowerMangeModel_T *localDW)
{
  INT32S tmp;
  if (localDW->is_active_c37_Appl_PowerMangeModel == 0U)
  {
    localDW->is_active_c37_Appl_PowerMangeModel = 1U;
    localDW->is_c37_Appl_PowerMangeModel = Appl_PowerMangeModel_IN_Init;
    *rty_UpCount = 1U;
    *rty_DownCount = 1U;
  }
  else
  {
    switch (localDW->is_c37_Appl_PowerMangeModel)
    {
     case Appl_PowerMangeModel_IN_Init:
      if (rtu_Voltage < rtu_DownValue)
      {
        localDW->is_c37_Appl_PowerMangeModel =
          Appl_PowerMangeModel_IN_VoltDownWait;
        *rty_UpCount = 0U;
      }
      else
      {
        if (rtu_Voltage > rtu_UpValue)
        {
          localDW->is_c37_Appl_PowerMangeModel =
            Appl_PowerMangeModel_IN_VoltUpWait;
          *rty_DownCount = 0U;
        }
      }
      break;

     case Appl_PowerMangeModel_IN_VoltDownWait:
      if (rtu_Voltage >= rtu_DownValue)
      {
        localDW->is_c37_Appl_PowerMangeModel = Appl_PowerMangeModel_IN_Init;
        *rty_UpCount = 1U;
        *rty_DownCount = 1U;
      }
      else
      {
        tmp = *rty_DownCount + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        *rty_DownCount = (INT16U)tmp;
      }
      break;

     default:
      if (rtu_Voltage <= rtu_UpValue)
      {
        localDW->is_c37_Appl_PowerMangeModel = Appl_PowerMangeModel_IN_Init;
        *rty_UpCount = 1U;
        *rty_DownCount = 1U;
      }
      else
      {
        tmp = *rty_UpCount + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        *rty_UpCount = (INT16U)tmp;
      }
      break;
    }
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_PowerMangeModel_LogicCtrl_Init(void)
{
  Appl_PowerMangeModel_DW.is_AcquireVoltage =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.is_VoltageChecking =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.is_active_c3_Appl_PowerMangeModel = 0U;
  Appl_PowerMangeModel_DW.InitFlag = 0U;
  Appl_PowerMangeModel_DW.AbnomalCnt = 0U;
  Appl_PowerMangeModel_DW.NomalCnt = 0U;
  Appl_PowerMangeModel_DW.StaticVoltageOKFlag = 0U;
  Appl_PowerMangeModel_B.VoltConditionSatisfy = 0U;
  Appl_PowerMangeModel_DW.is_AboveNormal =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.is_BelowNormal =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.is_active_c34_Appl_PowerMangeModel = 0U;
  Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.DownTimer = 0U;
  Appl_PowerMangeModel_DW.UpTimer = 0U;
  Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_STOP_VOLT;
  Appl_PowerMangeModel_ModeChangeFunction_Init(&Appl_PowerMangeModel_B.UpCount_o,
    &Appl_PowerMangeModel_B.DownCount_b,
    &Appl_PowerMangeModel_DW.ModeChangeFunction);
  Appl_PowerMangeModel_ModeChangeFunction_Init(&Appl_PowerMangeModel_B.UpCount_c,
    &Appl_PowerMangeModel_B.DownCount_n,
    &Appl_PowerMangeModel_DW.ModeChangeFunction1);
  Appl_PowerMangeModel_ModeChangeFunction_Init(&Appl_PowerMangeModel_B.UpCount,
    &Appl_PowerMangeModel_B.DownCount,
    &Appl_PowerMangeModel_DW.ModeChangeFunction2);
  Appl_PowerMangeModel_DW.is_active_c4_Appl_PowerMangeModel = 0U;
  Appl_PowerMangeModel_DW.is_c4_Appl_PowerMangeModel =
    Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
  Appl_PowerMangeModel_DW.TempPowerMode = enFinalPowerMode_EN_STOP_VOLT;
  Appl_PowerMangeModel_B.FinalVoltageMode = enFinalPowerMode_EN_STOP_VOLT;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_PowerMangeModel_LogicCtrl(void)
{
  INT8U RunVoltageOKFlag;
  INT16U tmp;
  INT32S tmp_0;
  if (Appl_PowerMangeModel_DW.is_active_c3_Appl_PowerMangeModel == 0U)
  {
    Appl_PowerMangeModel_DW.is_active_c3_Appl_PowerMangeModel = 1U;

    /* 电压＞16V */
    if (((INT16U)D_POWER_HIGH_DN) < Appl_PwrMng_SupplyVoltage)
    {
      Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((INT8U)D_POWER_Invalid);
    }
    else
    {
      /* 电压 <= 15.8V（高压回差0.2V） */
      if (((INT16U)D_POWER_ADJUST_15800MV) >= Appl_PwrMng_SupplyVoltage)
      {
        Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((BOOL)FALSE);
      }
    }

    /* 电压由高压回到正常范围，或者处在正常范围(9V~16V) */
    if ((((INT16U)D_POWER_LOW_UP) <= Appl_PwrMng_SupplyVoltage) && (((INT16U)
          D_POWER_HIGH_DN) >= Appl_PwrMng_SupplyVoltage) && (((BOOL)FALSE) ==
         Appl_PowerMangeModel_DW.StaticVoltageOKFlag))
    {
      Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((BOOL)TRUE);
    }

    /* 电压< 7.8V || 电压 >16V（低回差1.2V，避免低压继电器无法吸合问题）NXP及芯旺微 */
    Appl_PowerMangeModel_DW.is_AcquireVoltage = Appl_PowerMangeModel_IN_Default;
    Appl_PowerMangeModel_DW.NomalCnt = 0U;

    /* 未初始化过 */
    if (((BOOL)FALSE) == Appl_PowerMangeModel_DW.InitFlag)
    {
      Appl_PowerMangeModel_DW.InitFlag = ((BOOL)TRUE);
      Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)TRUE);
    }

    if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
    {
      tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
      if (tmp_0 > 255)
      {
        tmp_0 = 255;
      }

      Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
    }
    else
    {
      Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
    }

    /* 电压异常滤波时间到 */
    if (CAL_Filiter_500ms <= Appl_PowerMangeModel_DW.AbnomalCnt)
    {
      Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)FALSE);
    }

    /* 电压正常滤波时间到 */
    if (CAL_Filiter_500ms <= Appl_PowerMangeModel_DW.NomalCnt)
    {
      Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)TRUE);
    }
  }
  else
  {
    /* 电压＞16V */
    if (((INT16U)D_POWER_HIGH_DN) < Appl_PwrMng_SupplyVoltage)
    {
      Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((INT8U)D_POWER_Invalid);
    }
    else
    {
      /* 电压 <= 15.8V（高压回差0.2V） */
      if (((INT16U)D_POWER_ADJUST_15800MV) >= Appl_PwrMng_SupplyVoltage)
      {
        Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((BOOL)FALSE);
      }
    }

    /* 电压由高压回到正常范围，或者处在正常范围(9V~16V) */
    if ((((INT16U)D_POWER_LOW_UP) <= Appl_PwrMng_SupplyVoltage) && (((INT16U)
          D_POWER_HIGH_DN) >= Appl_PwrMng_SupplyVoltage) && (((BOOL)FALSE) ==
         Appl_PowerMangeModel_DW.StaticVoltageOKFlag))
    {
      Appl_PowerMangeModel_DW.StaticVoltageOKFlag = ((BOOL)TRUE);
    }

    /* 电压< 7.8V || 电压 >16V（低回差1.2V，避免低压继电器无法吸合问题）NXP及芯旺微 */
    if ((((INT16U)D_POWER_ADJUST_7800MV) > Appl_PwrMng_SupplyVoltage) ||
        (((INT16U)D_POWER_HIGH_DN) < Appl_PwrMng_SupplyVoltage))
    {
      RunVoltageOKFlag = ((BOOL)FALSE);
    }
    else
    {
      RunVoltageOKFlag = ((BOOL)TRUE);
    }

    if (Appl_PowerMangeModel_DW.is_AcquireVoltage ==
        Appl_PowerMangeModel_IN_Default)
    {
      /* 电机调节中，需要注意电压回差，避免无法堵转 */
      if (((enSeatMotorRunTye_EN_NULL != Appl_PwrMng_DriverRunType) ||
           (enSeatMotorRunTye_EN_NULL != Appl_PwrMng_PassengerRunType)) &&
          (((BOOL)TRUE) != RunVoltageOKFlag))
      {
        Appl_PowerMangeModel_DW.is_AcquireVoltage =
          Appl_PowerMangeModel_IN_VoltageChecking;
        Appl_PowerMangeModel_DW.is_VoltageChecking =
          Appl_PowerMangeModel_IN_AbnormalCounting;
        Appl_PowerMangeModel_DW.NomalCnt = 0U;
        if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
        {
          tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
          if (tmp_0 > 255)
          {
            tmp_0 = 255;
          }

          Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
        }
        else
        {
          Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
        }
      }
      else
      {
        /* 电机静止电压条件满足9V~16V */
        if (((BOOL)TRUE) == Appl_PowerMangeModel_DW.StaticVoltageOKFlag)
        {
          Appl_PowerMangeModel_DW.is_AcquireVoltage =
            Appl_PowerMangeModel_IN_VoltageChecking;
          Appl_PowerMangeModel_DW.is_VoltageChecking =
            Appl_PowerMangeModel_IN_NormalCounting;
          Appl_PowerMangeModel_DW.AbnomalCnt = 0U;
          if (Appl_PowerMangeModel_DW.NomalCnt < CAL_Filiter_500ms)
          {
            tmp_0 = Appl_PowerMangeModel_DW.NomalCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            Appl_PowerMangeModel_DW.NomalCnt = (INT8U)tmp_0;
          }
          else
          {
            Appl_PowerMangeModel_DW.NomalCnt = CAL_Filiter_500ms;
          }
        }
        else
        {
          /* 未初始化过 */
          if (((BOOL)FALSE) == Appl_PowerMangeModel_DW.InitFlag)
          {
            Appl_PowerMangeModel_DW.InitFlag = ((BOOL)TRUE);
            Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)TRUE);
          }

          if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
          {
            tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
          }
          else
          {
            Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
          }
        }
      }
    }
    else
    {
      /* 无主副驾调节请求 && (运动电压不满足8.9V~16V || 电机静止电压不满足9V~16V) */
      if ((enSeatMotorRunTye_EN_NULL == Appl_PwrMng_DriverRunType) &&
          (enSeatMotorRunTye_EN_NULL == Appl_PwrMng_PassengerRunType) &&
          ((((BOOL)TRUE) != Appl_PowerMangeModel_DW.StaticVoltageOKFlag) ||
           (((BOOL)TRUE) != RunVoltageOKFlag)))
      {
        Appl_PowerMangeModel_DW.is_VoltageChecking =
          Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
        Appl_PowerMangeModel_DW.is_AcquireVoltage =
          Appl_PowerMangeModel_IN_Default;
        Appl_PowerMangeModel_DW.NomalCnt = 0U;

        /* 未初始化过 */
        if (((BOOL)FALSE) == Appl_PowerMangeModel_DW.InitFlag)
        {
          Appl_PowerMangeModel_DW.InitFlag = ((BOOL)TRUE);
          Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)TRUE);
        }

        if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
        {
          tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
          if (tmp_0 > 255)
          {
            tmp_0 = 255;
          }

          Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
        }
        else
        {
          Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
        }
      }
      else if (Appl_PowerMangeModel_DW.is_VoltageChecking ==
               Appl_PowerMangeModel_IN_AbnormalCounting)
      {
        /* 电机静止电压条件满足9V~16V */
        if (((BOOL)TRUE) == Appl_PowerMangeModel_DW.StaticVoltageOKFlag)
        {
          Appl_PowerMangeModel_DW.is_VoltageChecking =
            Appl_PowerMangeModel_IN_NormalCounting;
          Appl_PowerMangeModel_DW.AbnomalCnt = 0U;
          if (Appl_PowerMangeModel_DW.NomalCnt < CAL_Filiter_500ms)
          {
            tmp_0 = Appl_PowerMangeModel_DW.NomalCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            Appl_PowerMangeModel_DW.NomalCnt = (INT8U)tmp_0;
          }
          else
          {
            Appl_PowerMangeModel_DW.NomalCnt = CAL_Filiter_500ms;
          }
        }
        else if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
        {
          tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
          if (tmp_0 > 255)
          {
            tmp_0 = 255;
          }

          Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
        }
        else
        {
          Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
        }
      }
      else
      {
        /* 电机调节中，需要注意电压回差，避免无法堵转 */
        if (((enSeatMotorRunTye_EN_NULL != Appl_PwrMng_DriverRunType) ||
             (enSeatMotorRunTye_EN_NULL != Appl_PwrMng_PassengerRunType)) &&
            (((BOOL)TRUE) != RunVoltageOKFlag))
        {
          Appl_PowerMangeModel_DW.is_VoltageChecking =
            Appl_PowerMangeModel_IN_AbnormalCounting;
          Appl_PowerMangeModel_DW.NomalCnt = 0U;
          if (Appl_PowerMangeModel_DW.AbnomalCnt < CAL_Filiter_500ms)
          {
            tmp_0 = Appl_PowerMangeModel_DW.AbnomalCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            Appl_PowerMangeModel_DW.AbnomalCnt = (INT8U)tmp_0;
          }
          else
          {
            Appl_PowerMangeModel_DW.AbnomalCnt = CAL_Filiter_500ms;
          }
        }
        else if (Appl_PowerMangeModel_DW.NomalCnt < CAL_Filiter_500ms)
        {
          tmp_0 = Appl_PowerMangeModel_DW.NomalCnt + 1;
          if (tmp_0 > 255)
          {
            tmp_0 = 255;
          }

          Appl_PowerMangeModel_DW.NomalCnt = (INT8U)tmp_0;
        }
        else
        {
          Appl_PowerMangeModel_DW.NomalCnt = CAL_Filiter_500ms;
        }
      }
    }

    /* 电压异常滤波时间到 */
    if (CAL_Filiter_500ms <= Appl_PowerMangeModel_DW.AbnomalCnt)
    {
      Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)FALSE);
    }

    /* 电压正常滤波时间到 */
    if (CAL_Filiter_500ms <= Appl_PowerMangeModel_DW.NomalCnt)
    {
      Appl_PowerMangeModel_B.VoltConditionSatisfy = ((BOOL)TRUE);
    }
  }

  if (Appl_PowerMangeModel_DW.is_active_c34_Appl_PowerMangeModel == 0U)
  {
    Appl_PowerMangeModel_DW.is_active_c34_Appl_PowerMangeModel = 1U;
    Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
      Appl_PowerMangeModel_IN_Normal;
    Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_NORMAL_VOLT;
  }
  else
  {
    switch (Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel)
    {
     case Appl_PowerMangeModel_IN_AboveNormal:
      /* 在AboveNormal切换到Normal条件：
         系统电压>=电压模式上限持续200ms
         且 系统电压>=正常电压下限
         且 系统电压<正常电压上限 */
      if ((Appl_PowerMangeModel_DW.DownTimer >= CAL_UpVolt_200ms) &&
          (Appl_PwrMng_SupplyVoltage >= ((INT16U)D_POWER_NORMAL_DN)) &&
          (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_NORMAL_UP)))
      {
        switch (Appl_PowerMangeModel_DW.is_AboveNormal)
        {
         case Appl_PowerMangeModel_IN_High:
          Appl_PowerMangeModel_DW.UpTimer = 0U;
          Appl_PowerMangeModel_DW.DownTimer = 0U;
          Appl_PowerMangeModel_DW.is_AboveNormal =
            Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
          break;

         case Appl_PowerMangeModel_IN_Over:
          /* 4=过压模式 */
          Appl_PowerMangeModel_DW.DownTimer = 0U;
          Appl_PowerMangeModel_DW.is_AboveNormal =
            Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
          break;
        }

        Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
          Appl_PowerMangeModel_IN_Normal;
        Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_NORMAL_VOLT;
      }
      else
      {
        /* 在AboveNormal直接切换到BelowNormal条件：
           系统电压>=电压模式下限持续600ms 且 系统电压<正常电压下限 */
        if ((Appl_PowerMangeModel_DW.DownTimer >= CAL_DownVolt_600ms) &&
            (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_NORMAL_DN)))
        {
          switch (Appl_PowerMangeModel_DW.is_AboveNormal)
          {
           case Appl_PowerMangeModel_IN_High:
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
            break;

           case Appl_PowerMangeModel_IN_Over:
            /* 4=过压模式 */
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
            break;
          }

          Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
            Appl_PowerMangeModel_IN_BelowNormal;

          /* 系统电压<=低压模式下限 */
          if (Appl_PwrMng_SupplyVoltage <= ((INT16U)D_POWER_LOW_DN))
          {
            Appl_PowerMangeModel_DW.is_BelowNormal =
              Appl_PowerMangeModel_IN_Stop;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_STOP_VOLT;

            /* 系统电压>停止模式上限电压 */
            if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_STOP_UP))
            {
              tmp_0 = Appl_PowerMangeModel_DW.UpTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压<=停止模式上限电压 */
              Appl_PowerMangeModel_DW.UpTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_STOP_VOLT;
            }
          }
          else
          {
            Appl_PowerMangeModel_DW.is_BelowNormal = Appl_PowerMangeModel_IN_Low;
            Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_LOW_VOLT;
          }
        }
        else if (Appl_PowerMangeModel_DW.is_AboveNormal ==
                 Appl_PowerMangeModel_IN_High)
        {
          /* 系统电压>电压模式上限持续200ms */
          if (Appl_PowerMangeModel_DW.UpTimer >= CAL_UpVolt_200ms)
          {
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_Over;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_OVER_VOLT;

            /* 系统电压<过压模式下限 */
            if (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_OVER_DN))
            {
              tmp_0 = Appl_PowerMangeModel_DW.DownTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压>过压模式上限 */
              Appl_PowerMangeModel_DW.DownTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_OVER_VOLT;
            }
          }
          else
          {
            /* 3=高压模式 */
            Appl_PowerMangeModel_ModeChangeFunction(Appl_PwrMng_SupplyVoltage,
              ((INT16U)D_POWER_HIGH_DN), ((INT16U)D_POWER_HIGH_UP),
              &Appl_PowerMangeModel_B.UpCount, &Appl_PowerMangeModel_B.DownCount,
              &Appl_PowerMangeModel_DW.ModeChangeFunction2);
            tmp = Appl_PowerMangeModel_B.UpCount;
            if (Appl_PowerMangeModel_B.UpCount > 255)
            {
              tmp = 255U;
            }

            Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp;
            tmp = Appl_PowerMangeModel_B.DownCount;
            if (Appl_PowerMangeModel_B.DownCount > 255)
            {
              tmp = 255U;
            }

            Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp;
          }
        }
        else
        {
          /* 系统电压<电压模式上限持续200ms
             且 系统电压>=正常电压上限 */
          if ((Appl_PowerMangeModel_DW.DownTimer >= CAL_UpVolt_200ms) &&
              (Appl_PwrMng_SupplyVoltage >= ((INT16U)D_POWER_NORMAL_UP)))
          {
            /* 4=过压模式 */
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_High;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_HIGH_VOLT;
          }
          else
          {
            /* 系统电压<过压模式下限 */
            if (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_OVER_DN))
            {
              tmp_0 = Appl_PowerMangeModel_DW.DownTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压>过压模式上限 */
              Appl_PowerMangeModel_DW.DownTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_OVER_VOLT;
            }
          }
        }
      }
      break;

     case Appl_PowerMangeModel_IN_BelowNormal:
      /* 在Normal切换到BelowNormal条件：
         系统电压<电压模式上限持续600ms
         且 系统电压<正常电压上限
         且 系统电压>正常电压下限 */
      if ((Appl_PowerMangeModel_DW.UpTimer >= CAL_DownVolt_600ms) &&
          (Appl_PwrMng_SupplyVoltage <= ((INT16U)D_POWER_NORMAL_UP)) &&
          (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_LOW_UP)))
      {
        switch (Appl_PowerMangeModel_DW.is_BelowNormal)
        {
         case Appl_PowerMangeModel_IN_Low:
          Appl_PowerMangeModel_DW.UpTimer = 0U;
          Appl_PowerMangeModel_DW.DownTimer = 0U;
          Appl_PowerMangeModel_DW.is_BelowNormal =
            Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
          break;

         case Appl_PowerMangeModel_IN_Stop:
          /* 0=停止模式 */
          Appl_PowerMangeModel_DW.UpTimer = 0U;
          Appl_PowerMangeModel_DW.is_BelowNormal =
            Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
          break;
        }

        Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
          Appl_PowerMangeModel_IN_Normal;
        Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_NORMAL_VOLT;
      }
      else
      {
        /* 在BelowNormal直接切换到AboveNormal条件：
           系统电压>=电压模式上限持续200ms 且 系统电压>正常电压上限 */
        if ((Appl_PowerMangeModel_DW.UpTimer >= CAL_UpVolt_200ms) &&
            (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_NORMAL_UP)))
        {
          switch (Appl_PowerMangeModel_DW.is_BelowNormal)
          {
           case Appl_PowerMangeModel_IN_Low:
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_BelowNormal =
              Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
            break;

           case Appl_PowerMangeModel_IN_Stop:
            /* 0=停止模式 */
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.is_BelowNormal =
              Appl_PowerMangeModel_IN_NO_ACTIVE_CHILD_d;
            break;
          }

          Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
            Appl_PowerMangeModel_IN_AboveNormal;

          /* 系统电压>高压模式上限 */
          if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_HIGH_UP))
          {
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_Over;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_OVER_VOLT;

            /* 系统电压<过压模式下限 */
            if (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_OVER_DN))
            {
              tmp_0 = Appl_PowerMangeModel_DW.DownTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压>过压模式上限 */
              Appl_PowerMangeModel_DW.DownTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_OVER_VOLT;
            }
          }
          else
          {
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_High;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_HIGH_VOLT;
          }
        }
        else if (Appl_PowerMangeModel_DW.is_BelowNormal ==
                 Appl_PowerMangeModel_IN_Low)
        {
          /* 系统电压<电压模式下限持续600ms */
          if (Appl_PowerMangeModel_DW.DownTimer >= CAL_DownVolt_600ms)
          {
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.DownTimer = 0U;
            Appl_PowerMangeModel_DW.is_BelowNormal =
              Appl_PowerMangeModel_IN_Stop;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_STOP_VOLT;

            /* 系统电压>停止模式上限电压 */
            if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_STOP_UP))
            {
              tmp_0 = Appl_PowerMangeModel_DW.UpTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压<=停止模式上限电压 */
              Appl_PowerMangeModel_DW.UpTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_STOP_VOLT;
            }
          }
          else
          {
            /* 1=低压模式 */
            Appl_PowerMangeModel_ModeChangeFunction(Appl_PwrMng_SupplyVoltage,
              ((INT16U)D_POWER_LOW_DN), ((INT16U)D_POWER_LOW_UP),
              &Appl_PowerMangeModel_B.UpCount_o,
              &Appl_PowerMangeModel_B.DownCount_b,
              &Appl_PowerMangeModel_DW.ModeChangeFunction);
            tmp = Appl_PowerMangeModel_B.UpCount_o;
            if (Appl_PowerMangeModel_B.UpCount_o > 255)
            {
              tmp = 255U;
            }

            Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp;
            tmp = Appl_PowerMangeModel_B.DownCount_b;
            if (Appl_PowerMangeModel_B.DownCount_b > 255)
            {
              tmp = 255U;
            }

            Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp;
          }
        }
        else
        {
          /* 系统电压>停止模式上限电压 */
          if ((Appl_PowerMangeModel_DW.UpTimer >= CAL_DownVolt_600ms) &&
              (Appl_PwrMng_SupplyVoltage <= ((INT16U)D_POWER_LOW_UP)))
          {
            /* 0=停止模式 */
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_DW.is_BelowNormal = Appl_PowerMangeModel_IN_Low;
            Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_LOW_VOLT;
          }
          else
          {
            /* 系统电压>停止模式上限电压 */
            if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_STOP_UP))
            {
              tmp_0 = Appl_PowerMangeModel_DW.UpTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压<=停止模式上限电压 */
              Appl_PowerMangeModel_DW.UpTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_STOP_VOLT;
            }
          }
        }
      }
      break;

     default:
      /* 在BelowNormal切换到Normal条件：
         系统电压<电压模式下限持续600ms */
      if (Appl_PowerMangeModel_DW.DownTimer >= CAL_DownVolt_600ms)
      {
        Appl_PowerMangeModel_DW.UpTimer = 0U;
        Appl_PowerMangeModel_DW.DownTimer = 0U;
        Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
          Appl_PowerMangeModel_IN_BelowNormal;

        /* 系统电压<=低压模式下限 */
        if (Appl_PwrMng_SupplyVoltage <= ((INT16U)D_POWER_LOW_DN))
        {
          Appl_PowerMangeModel_DW.is_BelowNormal = Appl_PowerMangeModel_IN_Stop;
          Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_STOP_VOLT;

          /* 系统电压>停止模式上限电压 */
          if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_STOP_UP))
          {
            tmp_0 = Appl_PowerMangeModel_DW.UpTimer + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp_0;
          }
          else
          {
            /* 系统电压<=停止模式上限电压 */
            Appl_PowerMangeModel_DW.UpTimer = 0U;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_STOP_VOLT;
          }
        }
        else
        {
          Appl_PowerMangeModel_DW.is_BelowNormal = Appl_PowerMangeModel_IN_Low;
          Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_LOW_VOLT;
        }
      }
      else
      {
        /* 在Normal切换到AboveNormal条件：
           系统电压>=电压模式上限持续200ms  */
        if (Appl_PowerMangeModel_DW.UpTimer >= CAL_UpVolt_200ms)
        {
          Appl_PowerMangeModel_DW.UpTimer = 0U;
          Appl_PowerMangeModel_DW.DownTimer = 0U;
          Appl_PowerMangeModel_DW.is_c34_Appl_PowerMangeModel =
            Appl_PowerMangeModel_IN_AboveNormal;

          /* 系统电压>高压模式上限 */
          if (Appl_PwrMng_SupplyVoltage > ((INT16U)D_POWER_HIGH_UP))
          {
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_Over;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_OVER_VOLT;

            /* 系统电压<过压模式下限 */
            if (Appl_PwrMng_SupplyVoltage < ((INT16U)D_POWER_OVER_DN))
            {
              tmp_0 = Appl_PowerMangeModel_DW.DownTimer + 1;
              if (tmp_0 > 255)
              {
                tmp_0 = 255;
              }

              Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp_0;
            }
            else
            {
              /* 系统电压>过压模式上限 */
              Appl_PowerMangeModel_DW.DownTimer = 0U;
              Appl_PowerMangeModel_B.OutVoltageMode =
                enFinalPowerMode_EN_OVER_VOLT;
            }
          }
          else
          {
            Appl_PowerMangeModel_DW.is_AboveNormal =
              Appl_PowerMangeModel_IN_High;
            Appl_PowerMangeModel_B.OutVoltageMode =
              enFinalPowerMode_EN_HIGH_VOLT;
          }
        }
        else
        {
          /* 2=正常模式 */
          Appl_PowerMangeModel_ModeChangeFunction(Appl_PwrMng_SupplyVoltage,
            ((INT16U)D_POWER_NORMAL_DN), ((INT16U)D_POWER_NORMAL_UP),
            &Appl_PowerMangeModel_B.UpCount_c,
            &Appl_PowerMangeModel_B.DownCount_n,
            &Appl_PowerMangeModel_DW.ModeChangeFunction1);
          tmp = Appl_PowerMangeModel_B.UpCount_c;
          if (Appl_PowerMangeModel_B.UpCount_c > 255)
          {
            tmp = 255U;
          }

          Appl_PowerMangeModel_DW.UpTimer = (INT8U)tmp;
          tmp = Appl_PowerMangeModel_B.DownCount_n;
          if (Appl_PowerMangeModel_B.DownCount_n > 255)
          {
            tmp = 255U;
          }

          Appl_PowerMangeModel_DW.DownTimer = (INT8U)tmp;
        }
      }
      break;
    }
  }

  if (Appl_PwrMng_BCM_PowerMode <=
      Appl_PowerMangeModel_ConstB.DataTypeConversion2)
  {
    Appl_PowerMangeModel_B.Switch1 = Appl_PwrMng_BCM_PowerMode;
  }
  else
  {
    Appl_PowerMangeModel_B.Switch1 = Appl_PowerMangeModel_DW.Delay_DSTATE;
  }

  if (Appl_PowerMangeModel_DW.is_active_c4_Appl_PowerMangeModel == 0U)
  {
    Appl_PowerMangeModel_DW.is_active_c4_Appl_PowerMangeModel = 1U;
    Appl_PowerMangeModel_DW.is_c4_Appl_PowerMangeModel =
      Appl_PowerMangeModel_IN_Init_j;
  }
  else if (Appl_PowerMangeModel_DW.is_c4_Appl_PowerMangeModel ==
           Appl_PowerMangeModel_IN_CRANK)
  {
    if (Appl_PowerMangeModel_B.Switch1 != (INT32S)enPowerModeSts_EN_CRANK)
    {
      Appl_PowerMangeModel_DW.is_c4_Appl_PowerMangeModel =
        Appl_PowerMangeModel_IN_Init_j;
    }
    else
    {
      Appl_PowerMangeModel_B.FinalVoltageMode =
        Appl_PowerMangeModel_DW.TempPowerMode;
    }
  }
  else if (Appl_PowerMangeModel_B.Switch1 == (INT32S)enPowerModeSts_EN_CRANK)
  {
    Appl_PowerMangeModel_DW.is_c4_Appl_PowerMangeModel =
      Appl_PowerMangeModel_IN_CRANK;
  }
  else
  {
    Appl_PowerMangeModel_B.FinalVoltageMode =
      Appl_PowerMangeModel_B.OutVoltageMode;
    Appl_PowerMangeModel_DW.TempPowerMode =
      Appl_PowerMangeModel_B.OutVoltageMode;
  }

  Appl_PowerMangeModel_DW.Delay_DSTATE = Appl_PowerMangeModel_B.Switch1;
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_PowerMangeModel_RTE(void)
{
  Appl_PwrMng_BCM_PowerMode = CanRx_0x283_BDC_PDU( );
  Appl_PwrMng_DriverRunType = Rte_GetVfb_DrMoveType( );
  Appl_PwrMng_PassengerRunType = Rte_GetVfb_PaMoveType( );
  Appl_PwrMng_SupplyVoltage = Srvl_Get_SupplyVoltage( );
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PowerMangeModel_UpDataInputInfo(void)
{
  Appl_PowerMangeModel_RTE();
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_PowerMangeModel_UpDataOutputInfo(void)
{
  Appl_PowerMangeModel_B.DataTypeConversion = (INT8U)
    Appl_PowerMangeModel_B.FinalVoltageMode;
  Rte_SetVfb_VoltMode(Appl_PowerMangeModel_B.DataTypeConversion);
  Rte_SetVfb_PowerMode(Appl_PowerMangeModel_B.Switch1);
  Rte_SetVfb_VoltSatisfy(Appl_PowerMangeModel_B.VoltConditionSatisfy);
}

/* Model step function */
void Appl_PowerMangeModel_step(void)
{
  Appl_PowerMangeModel_UpDataInputInfo();
  Appl_PowerMangeModel_LogicCtrl();
  Appl_PowerMangeModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_PowerMangeModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_PowerMangeModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_PowerMangeModel_B), 0,
                sizeof(B_Appl_PowerMangeModel_T));

  {
    Appl_PowerMangeModel_B.OutVoltageMode = enFinalPowerMode_EN_STOP_VOLT;
    Appl_PowerMangeModel_B.FinalVoltageMode = enFinalPowerMode_EN_STOP_VOLT;
  }

  /* exported global signals */
  Appl_PwrMng_DriverRunType = enSeatMotorRunTye_EN_NULL;
  Appl_PwrMng_PassengerRunType = enSeatMotorRunTye_EN_NULL;
  Appl_PwrMng_SupplyVoltage = ((INT16U)0U);
  Appl_PwrMng_BCM_PowerMode = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_PowerMangeModel_DW, 0,
                sizeof(DW_Appl_PowerMangeModel_T));
  Appl_PowerMangeModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
