/*
 * File: Appl_VentFault_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_VentFault_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jun  5 21:17:45 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_VentFault_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

/* Named constants for Chart: '<S8>/VentCmdAquireFunction' */
#define Appl_VentFault_CtrlModel_IN_HeatCmdInvalid ((INT8U)1U)
#define Appl_VentFault_CtrlModel_IN_HeatCmdValid ((INT8U)2U)
#define Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)

/* Named constants for Chart: '<S14>/VentCmdDiagnose' */
#define Appl_VentFault_CtrlModel_IN_CmdOpenLoad ((INT8U)1U)
#define Appl_VentFault_CtrlModel_IN_CmdShortToPower ((INT8U)2U)
#define Appl_VentFault_CtrlModel_IN_Default ((INT8U)3U)
#define Appl_VentFault_CtrlModel_IN_HeatCmdDiagnosis ((INT8U)1U)
#define Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m ((INT8U)0U)
#define Appl_VentFault_CtrlModel_IN_VentCmdClose ((INT8U)2U)

/* Exported block signals */
enVentLvlSts VentFault_D_SimuIndex_DRVent;/* '<S21>/VentFault_D_SimuIndex_DRVent'
                                           * 主驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                           */
enVentLvlSts VentFault_D_SimuIndex_PAVent;/* '<S21>/VentFault_D_SimuIndex_PAVent'
                                           * 副驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                           */
enVentLvlSts VentFault_D_SimuIndex_ThirdVent;/* '<S21>/VentFault_D_SimuIndex_ThirdVent'
                                              * 三排通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                              */
INT8U VentFault_DrPWMShortGND;         /* '<S21>/VentFault_DrPWMShortGND'
                                        * 主驾通风PWM短路至地&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_DrPWMShortPWR;         /* '<S21>/VentFault_DrPWMShortPWR'
                                        * 主驾通风PWM短路至电源&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_DrVentCmdIo;           /* '<S21>/VentFault_DrVentCmdIo'
                                        * 主驾通风输出电平
                                        */
INT8U VentFault_DrVentFlg;             /* '<S21>/VentFault_DrVentFlg'
                                        * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_DriverEnableConfig;    /* '<S21>/VentFault_DriverEnableConfig'
                                        * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_PaPWMShortGND;         /* '<S21>/VentFault_PaPWMShortGND'
                                        * 主驾通风PWM短路至地&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_PaPWMShortPWR;         /* '<S21>/VentFault_PaPWMShortPWR'
                                        * 主驾通风PWM短路至电源&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_PaVentCmdIo;           /* '<S21>/VentFault_PaVentCmdIo'
                                        * 副驾通风输出电平
                                        */
INT8U VentFault_PaVentFlg;             /* '<S21>/VentFault_PaVentFlg'
                                        * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_PassengerEnableConfig; /* '<S21>/VentFault_PassengerEnableConfig'
                                        * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_ThirdEnableConfig;     /* '<S21>/VentFault_ThirdEnableConfig'
                                        * 三排通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentFault_ThirdVentCmdIo;        /* '<S21>/VentFault_ThirdVentCmdIo'
                                        * 三排通风输出电平
                                        */

/* Block signals (default storage) */
B_Appl_VentFault_CtrlModel_T Appl_VentFault_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_VentFault_CtrlModel_T Appl_VentFault_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_VentFault_CtrlModel_T Appl_VentFault_CtrlModel_M_;
RT_MODEL_Appl_VentFault_CtrlModel_T *const Appl_VentFault_CtrlModel_M =
  &Appl_VentFault_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT16U CAL_VentCmdOpenTime = 1000U;/* 通风输出判断时间：1000ms */
const volatile INT16U CAL_VentCmdShortTime = 1000U;/* 通风输出短地判断时间：1000ms */
static void Appl_VentFault_CtrlMode_VentCmdAquireFunction_Init(INT8U
  *rty_VentCmd, DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T *localDW);
static void Appl_VentFault_CtrlModel_VentCmdAquireFunction(enVentLvlSts
  rtu_API_VentCmd, INT8U rtu_VentCfg, INT8U rtu_VentFlg, INT8U *rty_VentCmd,
  DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T *localDW);
static void Appl_VentFault_CtrlMo_VentCmdDiagnoseFunction_Init(enVentCmdFault
  *rty_VentCmdFault, INT8U *rty_VentCmdFault4DTC,
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T *localDW);
static void Appl_VentFault_CtrlModel_VentCmdDiagnoseFunction(enHeatIoSts
  rtu_VentCmdIo, INT8U rtu_VentCmd, enVentCmdFault rtu_FaultType, enVentLvlSts
  rtu_VentLvl, enVentCmdFault *rty_VentCmdFault, INT8U *rty_VentCmdFault4DTC,
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T *localDW);
static void Appl_VentFault_CtrlModel_getFaultType_Init(INT8U *rty_FaultType);
static void Appl_VentFault_CtrlModel_getFaultType(INT8U rtu_ShortGND, INT8U
  rtu_ShortPWR, INT8U *rty_FaultType);
static void Appl_VentFault_CtrlModel_LogicCtrl_Init(void);
static void Appl_VentFault_CtrlModel_LogicCtrl(void);
static void Appl_VentFault_CtrlModel_RTE(void);
static void Appl_VentFault_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_VentFault_CtrlModel_UpDataInputInfo(void);
static void Appl_VentFault_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static INT32S Appl_VentFault_CtrlModel_safe_cast_to_enHeatIoSts(INT32S input);
static INT32S Appl_VentFault_CtrlMod_safe_cast_to_enVentCmdFault(INT32S input);

/* Forward declaration for local functions */
static INT32S Appl_VentFault_CtrlMod_safe_cast_to_enHeatCmdFault(INT32S input);

/*
 * System initialize for function-call system:
 *    '<S6>/VentCmdAquireFunction'
 *    '<S6>/VentCmdAquireFunction1'
 *    '<S6>/VentCmdAquireFunction2'
 */
static void Appl_VentFault_CtrlMode_VentCmdAquireFunction_Init(INT8U
  *rty_VentCmd, DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T *localDW)
{
  localDW->is_active_c2_Appl_VentFault_CtrlModel = 0U;
  localDW->is_c2_Appl_VentFault_CtrlModel =
    Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD;
  *rty_VentCmd = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S6>/VentCmdAquireFunction'
 *    '<S6>/VentCmdAquireFunction1'
 *    '<S6>/VentCmdAquireFunction2'
 */
static void Appl_VentFault_CtrlModel_VentCmdAquireFunction(enVentLvlSts
  rtu_API_VentCmd, INT8U rtu_VentCfg, INT8U rtu_VentFlg, INT8U *rty_VentCmd,
  DW_VentCmdAquireFunction_Appl_VentFault_CtrlMode_T *localDW)
{
  if (localDW->is_active_c2_Appl_VentFault_CtrlModel == 0U)
  {
    localDW->is_active_c2_Appl_VentFault_CtrlModel = 1U;
    localDW->is_c2_Appl_VentFault_CtrlModel =
      Appl_VentFault_CtrlModel_IN_HeatCmdInvalid;
    *rty_VentCmd = ((BOOL)FALSE);
  }
  else if (localDW->is_c2_Appl_VentFault_CtrlModel ==
           Appl_VentFault_CtrlModel_IN_HeatCmdInvalid)
  {
    *rty_VentCmd = ((BOOL)FALSE);

    /*  指令有效  */
    if ((enVentLvlSts_EN_VENT_LVL_OFF != rtu_API_VentCmd) && (((BOOL)TRUE) ==
         rtu_VentCfg) && (((BOOL)TRUE) == rtu_VentFlg))
    {
      localDW->is_c2_Appl_VentFault_CtrlModel =
        Appl_VentFault_CtrlModel_IN_HeatCmdValid;
      *rty_VentCmd = ((BOOL)TRUE);
    }
  }
  else
  {
    *rty_VentCmd = ((BOOL)TRUE);

    /*  指令无效  */
    if ((enVentLvlSts_EN_VENT_LVL_OFF == rtu_API_VentCmd) || (((BOOL)TRUE) !=
         rtu_VentCfg) || (((BOOL)TRUE) != rtu_VentFlg))
    {
      localDW->is_c2_Appl_VentFault_CtrlModel =
        Appl_VentFault_CtrlModel_IN_HeatCmdInvalid;
      *rty_VentCmd = ((BOOL)FALSE);
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S7>/VentCmdDiagnoseFunction'
 *    '<S7>/VentCmdDiagnoseFunction1'
 *    '<S7>/VentCmdDiagnoseFunction2'
 */
static void Appl_VentFault_CtrlMo_VentCmdDiagnoseFunction_Init(enVentCmdFault
  *rty_VentCmdFault, INT8U *rty_VentCmdFault4DTC,
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T *localDW)
{
  localDW->is_HeatCmdDiagnosis = Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  localDW->is_active_c4_Appl_VentFault_CtrlModel = 0U;
  localDW->is_c4_Appl_VentFault_CtrlModel =
    Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  localDW->ShortTimer = 0U;
  localDW->OpenTimer = 0U;
  *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
  *rty_VentCmdFault4DTC = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S7>/VentCmdDiagnoseFunction'
 *    '<S7>/VentCmdDiagnoseFunction1'
 *    '<S7>/VentCmdDiagnoseFunction2'
 */
static void Appl_VentFault_CtrlModel_VentCmdDiagnoseFunction(enHeatIoSts
  rtu_VentCmdIo, INT8U rtu_VentCmd, enVentCmdFault rtu_FaultType, enVentLvlSts
  rtu_VentLvl, enVentCmdFault *rty_VentCmdFault, INT8U *rty_VentCmdFault4DTC,
  DW_VentCmdDiagnoseFunction_Appl_VentFault_CtrlMo_T *localDW)
{
  INT32S tmp;
  if (localDW->is_active_c4_Appl_VentFault_CtrlModel == 0U)
  {
    localDW->is_active_c4_Appl_VentFault_CtrlModel = 1U;
    localDW->is_c4_Appl_VentFault_CtrlModel =
      Appl_VentFault_CtrlModel_IN_VentCmdClose;
    localDW->OpenTimer = 0U;
    localDW->ShortTimer = 0U;
    *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
  }
  else if (localDW->is_c4_Appl_VentFault_CtrlModel ==
           Appl_VentFault_CtrlModel_IN_HeatCmdDiagnosis)
  {
    /*  无通风CMD  */
    if (((BOOL)TRUE) != rtu_VentCmd)
    {
      switch (localDW->is_HeatCmdDiagnosis)
      {
       case Appl_VentFault_CtrlModel_IN_CmdOpenLoad:
        localDW->OpenTimer = 0U;
        localDW->is_HeatCmdDiagnosis =
          Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        break;

       case Appl_VentFault_CtrlModel_IN_CmdShortToPower:
        localDW->ShortTimer = 0U;
        localDW->is_HeatCmdDiagnosis =
          Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        break;

       default:
        localDW->is_HeatCmdDiagnosis =
          Appl_VentFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        break;
      }

      localDW->is_c4_Appl_VentFault_CtrlModel =
        Appl_VentFault_CtrlModel_IN_VentCmdClose;
      localDW->OpenTimer = 0U;
      localDW->ShortTimer = 0U;
      *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
    }
    else
    {
      switch (localDW->is_HeatCmdDiagnosis)
      {
       case Appl_VentFault_CtrlModel_IN_CmdOpenLoad:
        /*  pwm输出为高 或为3档 */
        if ((((BOOL)TRUE) == (INT32S)rtu_VentCmdIo) || (rtu_VentLvl ==
             enVentLvlSts_EN_VENT_LVL_3))
        {
          localDW->is_HeatCmdDiagnosis = Appl_VentFault_CtrlModel_IN_Default;
          localDW->OpenTimer = 0U;
          localDW->ShortTimer = 0U;
          *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
          *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_NONE;
        }
        else
        {
          /*  未超时  */
          if (CAL_VentCmdOpenTime > localDW->OpenTimer)
          {
            tmp = localDW->OpenTimer + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            localDW->OpenTimer = (INT16U)tmp;
          }
          else
          {
            /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
            localDW->OpenTimer = CAL_VentCmdOpenTime;
            *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_OPEN;
            *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_OPEN;
          }
        }
        break;

       case Appl_VentFault_CtrlModel_IN_CmdShortToPower:
        /*  pwm输出为低  */
        if (((BOOL)FALSE) == (INT32S)rtu_VentCmdIo)
        {
          localDW->is_HeatCmdDiagnosis = Appl_VentFault_CtrlModel_IN_Default;
          localDW->OpenTimer = 0U;
          localDW->ShortTimer = 0U;
          *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
          *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_NONE;
        }
        else
        {
          /*  未超时  */
          if (CAL_VentCmdShortTime > localDW->ShortTimer)
          {
            tmp = localDW->ShortTimer + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            localDW->ShortTimer = (INT16U)tmp;
          }
          else
          {
            /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
            localDW->ShortTimer = CAL_VentCmdShortTime;
            *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_LOAD;
            *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_LOAD;
          }
        }
        break;

       default:
        /*  pwm输出为高  */
        tmp = rtu_VentCmdIo;
        if (((BOOL)TRUE) == tmp)
        {
          localDW->is_HeatCmdDiagnosis =
            Appl_VentFault_CtrlModel_IN_CmdShortToPower;

          /*  未超时  */
          if (CAL_VentCmdShortTime > localDW->ShortTimer)
          {
            tmp = localDW->ShortTimer + 1;
            if (tmp > 65535)
            {
              tmp = 65535;
            }

            localDW->ShortTimer = (INT16U)tmp;
          }
          else
          {
            /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
            localDW->ShortTimer = CAL_VentCmdShortTime;
            *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_LOAD;
            *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_LOAD;
          }
        }
        else
        {
          /*  pwm输出为低 且不为 3档 */
          if ((((BOOL)FALSE) == tmp) && (rtu_VentLvl !=
               enVentLvlSts_EN_VENT_LVL_3))
          {
            localDW->is_HeatCmdDiagnosis =
              Appl_VentFault_CtrlModel_IN_CmdOpenLoad;

            /*  未超时  */
            if (CAL_VentCmdOpenTime > localDW->OpenTimer)
            {
              tmp = localDW->OpenTimer + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              localDW->OpenTimer = (INT16U)tmp;
            }
            else
            {
              /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
              localDW->OpenTimer = CAL_VentCmdOpenTime;
              *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_OPEN;
              *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_OPEN;
            }
          }
        }
        break;
      }
    }
  }
  else
  {
    /*  通风CMD  */
    if (((BOOL)TRUE) == rtu_VentCmd)
    {
      *rty_VentCmdFault4DTC = (INT8U)rtu_FaultType;
      localDW->is_c4_Appl_VentFault_CtrlModel =
        Appl_VentFault_CtrlModel_IN_HeatCmdDiagnosis;
      switch (rtu_FaultType)
      {
       case enVentCmdFault_EN_VENT_FAULT_LOAD:
        localDW->is_HeatCmdDiagnosis =
          Appl_VentFault_CtrlModel_IN_CmdShortToPower;

        /*  未超时  */
        if (CAL_VentCmdShortTime > localDW->ShortTimer)
        {
          tmp = localDW->ShortTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          localDW->ShortTimer = (INT16U)tmp;
        }
        else
        {
          /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
          localDW->ShortTimer = CAL_VentCmdShortTime;
          *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_LOAD;
          *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_LOAD;
        }
        break;

       case enVentCmdFault_EN_VENT_FAULT_OPEN:
        localDW->is_HeatCmdDiagnosis = Appl_VentFault_CtrlModel_IN_CmdOpenLoad;

        /*  未超时  */
        if (CAL_VentCmdOpenTime > localDW->OpenTimer)
        {
          tmp = localDW->OpenTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          localDW->OpenTimer = (INT16U)tmp;
        }
        else
        {
          /* 设置DTC故障标志位，关闭事件报文主驾通风档位 */
          localDW->OpenTimer = CAL_VentCmdOpenTime;
          *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_OPEN;
          *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_OPEN;
        }
        break;

       default:
        localDW->is_HeatCmdDiagnosis = Appl_VentFault_CtrlModel_IN_Default;
        localDW->OpenTimer = 0U;
        localDW->ShortTimer = 0U;
        *rty_VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
        *rty_VentCmdFault4DTC = (INT8U)enVentCmdFault_EN_VENT_FAULT_NONE;
        break;
      }
    }
  }
}

static INT32S Appl_VentFault_CtrlModel_safe_cast_to_enHeatIoSts(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enHeatIoSts (EN_HEAT_IO_LOW) */
  y = 0;
  if ((input >= 0) && (input <= 1))
  {
    /* Set output value to input value if it is a member of enHeatIoSts */
    y = input;
  }

  return y;
}

static INT32S Appl_VentFault_CtrlMod_safe_cast_to_enVentCmdFault(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enVentCmdFault (EN_VENT_FAULT_NONE) */
  y = 0;
  if ((input >= 0) && (input <= 2))
  {
    /* Set output value to input value if it is a member of enVentCmdFault */
    y = input;
  }

  return y;
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_VentFault_CtrlModel_LogicCtrl_Init(void)
{
  INT8U VentCmd_h;
  Appl_VentFault_CtrlModel_DW.is_active_c1_Appl_VentFault_CtrlModel = 0U;
  Appl_VentFault_CtrlModel_B.DrVentCmd = 0U;
  Appl_VentFault_CtrlModel_B.PaVentCmd = 0U;
  Appl_VentFault_CtrlModel_B.ThirdVentCmd = 0U;
  Appl_VentFault_CtrlMode_VentCmdAquireFunction_Init(&VentCmd_h,
    &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction);
  Appl_VentFault_CtrlMode_VentCmdAquireFunction_Init(&VentCmd_h,
    &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction1);
  Appl_VentFault_CtrlMode_VentCmdAquireFunction_Init(&VentCmd_h,
    &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction2);
  Appl_VentFault_CtrlModel_DW.is_active_c3_Appl_VentFault_CtrlModel = 0U;
  Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts =
    enVentCmdFault_EN_VENT_FAULT_NONE;
  Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts =
    enVentCmdFault_EN_VENT_FAULT_NONE;
  Appl_VentFault_CtrlModel_B.VentFault_ThirdVentCmdFaultSts =
    enVentCmdFault_EN_VENT_FAULT_NONE;
  Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts4DTC = 0U;
  Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts4DTC = 0U;
  Appl_VentFault_CtrlMo_VentCmdDiagnoseFunction_Init
    (&Appl_VentFault_CtrlModel_B.VentCmdFault_h,
     &Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_h,
     &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction);
  Appl_VentFault_CtrlMo_VentCmdDiagnoseFunction_Init
    (&Appl_VentFault_CtrlModel_B.VentCmdFault_k,
     &Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_g,
     &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction1);
  Appl_VentFault_CtrlMo_VentCmdDiagnoseFunction_Init
    (&Appl_VentFault_CtrlModel_B.VentCmdFault, &VentCmd_h,
     &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction2);
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_VentFault_CtrlModel_LogicCtrl(void)
{
  INT8U VentCmdFault4DTC;
  if (Appl_VentFault_CtrlModel_DW.is_active_c1_Appl_VentFault_CtrlModel == 0U)
  {
    Appl_VentFault_CtrlModel_DW.is_active_c1_Appl_VentFault_CtrlModel = 1U;
  }
  else
  {
    Appl_VentFault_CtrlModel_VentCmdAquireFunction(VentFault_D_SimuIndex_DRVent,
      VentFault_DriverEnableConfig, VentFault_DrVentFlg,
      &Appl_VentFault_CtrlModel_B.DrVentCmd,
      &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction);
    Appl_VentFault_CtrlModel_VentCmdAquireFunction(VentFault_D_SimuIndex_PAVent,
      VentFault_PassengerEnableConfig, VentFault_PaVentFlg,
      &Appl_VentFault_CtrlModel_B.PaVentCmd,
      &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction1);
    Appl_VentFault_CtrlModel_VentCmdAquireFunction
      (VentFault_D_SimuIndex_ThirdVent, VentFault_ThirdEnableConfig, (INT8U)
       ((BOOL)TRUE), &Appl_VentFault_CtrlModel_B.ThirdVentCmd,
       &Appl_VentFault_CtrlModel_DW.VentCmdAquireFunction2);
  }

  if (Appl_VentFault_CtrlModel_DW.is_active_c3_Appl_VentFault_CtrlModel == 0U)
  {
    Appl_VentFault_CtrlModel_DW.is_active_c3_Appl_VentFault_CtrlModel = 1U;
  }
  else
  {
    Appl_VentFault_CtrlModel_VentCmdDiagnoseFunction((enHeatIoSts)
      Appl_VentFault_CtrlModel_safe_cast_to_enHeatIoSts(VentFault_DrVentCmdIo),
      Appl_VentFault_CtrlModel_B.DrVentCmd, (enVentCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enVentCmdFault
      (Appl_VentFault_CtrlModel_B.DrFaultType), VentFault_D_SimuIndex_DRVent,
      &Appl_VentFault_CtrlModel_B.VentCmdFault_h,
      &Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_h,
      &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction);
    Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts =
      Appl_VentFault_CtrlModel_B.VentCmdFault_h;
    Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts4DTC =
      Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_h;
    Appl_VentFault_CtrlModel_VentCmdDiagnoseFunction((enHeatIoSts)
      Appl_VentFault_CtrlModel_safe_cast_to_enHeatIoSts(VentFault_PaVentCmdIo),
      Appl_VentFault_CtrlModel_B.PaVentCmd, (enVentCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enVentCmdFault
      (Appl_VentFault_CtrlModel_B.PaFaultType), VentFault_D_SimuIndex_PAVent,
      &Appl_VentFault_CtrlModel_B.VentCmdFault_k,
      &Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_g,
      &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction1);
    Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts =
      Appl_VentFault_CtrlModel_B.VentCmdFault_k;
    Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts4DTC =
      Appl_VentFault_CtrlModel_B.VentCmdFault4DTC_g;
    Appl_VentFault_CtrlModel_VentCmdDiagnoseFunction((enHeatIoSts)
      Appl_VentFault_CtrlModel_safe_cast_to_enHeatIoSts(VentFault_ThirdVentCmdIo),
      Appl_VentFault_CtrlModel_B.ThirdVentCmd, (enVentCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enVentCmdFault
      (Appl_VentFault_CtrlModel_B.ThirdFaultType),
      VentFault_D_SimuIndex_ThirdVent, &Appl_VentFault_CtrlModel_B.VentCmdFault,
      &VentCmdFault4DTC, &Appl_VentFault_CtrlModel_DW.VentCmdDiagnoseFunction2);
    Appl_VentFault_CtrlModel_B.VentFault_ThirdVentCmdFaultSts =
      Appl_VentFault_CtrlModel_B.VentCmdFault;
  }
}

/* System initialize for function-call system: '<S23>/getFaultType' */
static void Appl_VentFault_CtrlModel_getFaultType_Init(INT8U *rty_FaultType)
{
  *rty_FaultType = 0U;
}

/* Output and update for function-call system: '<S23>/getFaultType' */
static void Appl_VentFault_CtrlModel_getFaultType(INT8U rtu_ShortGND, INT8U
  rtu_ShortPWR, INT8U *rty_FaultType)
{
  /* PWM短电源 */
  if (rtu_ShortPWR == ((BOOL)TRUE))
  {
    *rty_FaultType = (INT8U)enVentCmdFault_EN_VENT_FAULT_LOAD;
  }
  else
  {
    /* PWM短地、开路 */
    if (rtu_ShortGND == ((BOOL)TRUE))
    {
      *rty_FaultType = (INT8U)enVentCmdFault_EN_VENT_FAULT_OPEN;
    }
    else
    {
      *rty_FaultType = (INT8U)enVentCmdFault_EN_VENT_FAULT_NONE;
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_VentFault_CtrlModel_RTE(void)
{
  VentFault_D_SimuIndex_DRVent = Rte_GetVfb_DrVent( );
  VentFault_D_SimuIndex_PAVent = Rte_GetVfb_PaVent( );
  VentFault_D_SimuIndex_ThirdVent = Rte_GetVfb_ThirdVent( );
  VentFault_DrPWMShortGND = Diag_ReadDtcTestFailFlag(D_DTC_DrVentPWMGS);
  VentFault_DrPWMShortPWR = Diag_ReadDtcTestFailFlag(D_DTC_DrVentPWMPS);
  VentFault_DrVentCmdIo = Ecual_GetDigitalSwStatus(EN_DRVenFeedback);
  VentFault_DrVentFlg = Rte_GetVfb_DrVentEnable( );
  VentFault_DriverEnableConfig = Rte_GetVfb_DrVentEnable( );
  VentFault_PaPWMShortGND = Diag_ReadDtcTestFailFlag(D_DTC_PaVentPWMGS);
  VentFault_PaPWMShortPWR = Diag_ReadDtcTestFailFlag(D_DTC_PaVentPWMPS);
  VentFault_PaVentCmdIo = Ecual_GetDigitalSwStatus(EN_PaVenFeedback);
  VentFault_PaVentFlg = Rte_GetVfb_SecondVentEnable( );
  VentFault_PassengerEnableConfig = Rte_GetVfb_SecondVentEnable( );
  VentFault_ThirdEnableConfig = Rte_GetVfb_ThirdVentEnable( );
  VentFault_ThirdVentCmdIo = Vfb_Reserved_0( );
}

static INT32S Appl_VentFault_CtrlMod_safe_cast_to_enHeatCmdFault(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enHeatCmdFault (EN_HEAT_FAULT_NONE) */
  y = 0;
  if ((input >= 0) && (input <= 2))
  {
    /* Set output value to input value if it is a member of enHeatCmdFault */
    y = input;
  }

  return y;
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_VentFault_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U VentPWMFault;
  Appl_VentFault_CtrlModel_DW.is_active_c15_Appl_VentFault_CtrlModel = 0U;
  Appl_VentFault_CtrlModel_B.DrFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_VentFault_CtrlModel_B.PaFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_VentFault_CtrlModel_B.ThirdFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_VentFault_CtrlModel_getFaultType_Init(&VentPWMFault);
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_VentFault_CtrlModel_UpDataInputInfo(void)
{
  INT8U VentPWMFault;
  Appl_VentFault_CtrlModel_RTE();
  if (Appl_VentFault_CtrlModel_DW.is_active_c15_Appl_VentFault_CtrlModel == 0U)
  {
    Appl_VentFault_CtrlModel_DW.is_active_c15_Appl_VentFault_CtrlModel = 1U;
  }
  else
  {
    Appl_VentFault_CtrlModel_getFaultType(VentFault_DrPWMShortGND,
      VentFault_PaPWMShortPWR, &VentPWMFault);
    Appl_VentFault_CtrlModel_B.DrFaultType = (enHeatCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enHeatCmdFault(VentPWMFault);
    Appl_VentFault_CtrlModel_getFaultType(VentFault_DrPWMShortPWR, 0,
      &VentPWMFault);
    Appl_VentFault_CtrlModel_B.PaFaultType = (enHeatCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enHeatCmdFault(VentPWMFault);
    Appl_VentFault_CtrlModel_getFaultType(VentFault_PaPWMShortGND, 0,
      &VentPWMFault);
    Appl_VentFault_CtrlModel_B.ThirdFaultType = (enHeatCmdFault)
      Appl_VentFault_CtrlMod_safe_cast_to_enHeatCmdFault(VentPWMFault);
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_VentFault_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_DrVentCmdFaultSts
    (Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts);
  Rte_SetVfb_PaVentCmdFaultSts
    (Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts);
  Rte_SetVfb_ThirdVentCmdFaultSts
    (Appl_VentFault_CtrlModel_B.VentFault_ThirdVentCmdFaultSts);
  Rte_SetVfb_DrVentCmdFaultSts4DTC
    (Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts4DTC);
  Rte_SetVfb_PaVentCmdFaultSts4DTC
    (Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts4DTC);
}

/* Model step function */
void Appl_VentFault_CtrlModel_step(void)
{
  Appl_VentFault_CtrlModel_UpDataInputInfo();
  Appl_VentFault_CtrlModel_LogicCtrl();
  Appl_VentFault_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_VentFault_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_VentFault_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_VentFault_CtrlModel_B), 0,
                sizeof(B_Appl_VentFault_CtrlModel_T));

  {
    Appl_VentFault_CtrlModel_B.VentFault_DRVentCmdFaultSts =
      enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.VentFault_PAVentCmdFaultSts =
      enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.VentFault_ThirdVentCmdFaultSts =
      enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.VentCmdFault = enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.VentCmdFault_k =
      enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.VentCmdFault_h =
      enVentCmdFault_EN_VENT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.DrFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.PaFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_VentFault_CtrlModel_B.ThirdFaultType =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }

  /* exported global signals */
  VentFault_D_SimuIndex_DRVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentFault_D_SimuIndex_PAVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentFault_D_SimuIndex_ThirdVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentFault_DrPWMShortGND = ((INT8U)0U);
  VentFault_DrPWMShortPWR = ((INT8U)0U);
  VentFault_DrVentCmdIo = ((INT8U)0U);
  VentFault_DrVentFlg = ((INT8U)0U);
  VentFault_DriverEnableConfig = ((INT8U)0U);
  VentFault_PaPWMShortGND = ((INT8U)0U);
  VentFault_PaPWMShortPWR = ((INT8U)0U);
  VentFault_PaVentCmdIo = ((INT8U)0U);
  VentFault_PaVentFlg = ((INT8U)0U);
  VentFault_PassengerEnableConfig = ((INT8U)0U);
  VentFault_ThirdEnableConfig = ((INT8U)0U);
  VentFault_ThirdVentCmdIo = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_VentFault_CtrlModel_DW, 0,
                sizeof(DW_Appl_VentFault_CtrlModel_T));
  Appl_VentFault_CtrlModel_UpDataInputInfo_Init();
  Appl_VentFault_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
