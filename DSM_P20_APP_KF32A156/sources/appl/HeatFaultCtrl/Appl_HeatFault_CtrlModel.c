/*
 * File: Appl_HeatFault_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_HeatFault_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jul  1 10:44:06 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_HeatFault_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_HEATFALUT_CmdOpenLoad
#error The variable for the parameter "D_HEATFALUT_CmdOpenLoad" is not defined
#endif

#ifndef D_HEATFALUT_CmdOpenLoad_W
#error The variable for the parameter "D_HEATFALUT_CmdOpenLoad_W" is not defined
#endif

#ifndef D_HEATFALUT_CmdShortToGnd
#error The variable for the parameter "D_HEATFALUT_CmdShortToGnd" is not defined
#endif

#ifndef D_HEATFALUT_NtcMax
#error The variable for the parameter "D_HEATFALUT_NtcMax" is not defined
#endif

#ifndef D_HEATFALUT_NtcMin
#error The variable for the parameter "D_HEATFALUT_NtcMin" is not defined
#endif

#ifndef D_HEATFALUT_NtcOpenLoad
#error The variable for the parameter "D_HEATFALUT_NtcOpenLoad" is not defined
#endif

#ifndef D_HEATFALUT_NtcShortToGnd
#error The variable for the parameter "D_HEATFALUT_NtcShortToGnd" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

/* Named constants for Chart: '<S8>/HeatCmdAquireFunction' */
#define Appl_HeatFault_CtrlModel_IN_HeatCmdInvalid ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_HeatCmdValid ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)

/* Named constants for Chart: '<S14>/HeatCmdDiagnose' */
#define Appl_HeatFault_CtrlModel_IN_CmdOpenLoad ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_CmdShortToGND ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_Default ((INT8U)3U)
#define Appl_HeatFault_CtrlModel_IN_HeatCmdClose ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_HeatCmdDiagnosis ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f ((INT8U)0U)
#define Appl_HeatFault_CtrlModel_IN_OpenLow ((INT8U)4U)
#define Appl_HeatFault_CtrlModel_IN_ShortLow ((INT8U)5U)

/* Named constants for Chart: '<S17>/HeatCmdDiagnose' */
#define Appl_HeatFault_CtrlModel_IN_Default_h ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_m ((INT8U)0U)
#define Appl_HeatFault_CtrlModel_IN_NTCOpenLoad ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_NTCOverRange ((INT8U)3U)
#define Appl_HeatFault_CtrlModel_IN_NTCShortToGND ((INT8U)4U)

/* Named constants for Chart: '<S16>/HeatCmdDiagnose' */
#define Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_Default_o ((INT8U)3U)
#define Appl_HeatFault_CtrlModel_IN_HeatCmdClose_p ((INT8U)1U)
#define Appl_HeatFault_CtrlModel_IN_HeatCmdDiagnosis_o ((INT8U)2U)
#define Appl_HeatFault_CtrlModel_IN_OpenLow_a ((INT8U)4U)
#define Appl_HeatFault_CtrlModel_IN_ShortLow_k ((INT8U)5U)

/* Exported block signals */
enHeatLvlSts HeatFalut_D_SimuIndex_DRHeat;/* '<S27>/HeatFalut_D_SimuIndex_DRHeat'
                                           * 主驾加热档位状态: 0：OFF 1：LV1 2：LV2 3：LV3
                                           */
enHeatLvlSts HeatFalut_D_SimuIndex_PAHeat;/* '<S27>/HeatFalut_D_SimuIndex_PAHeat'
                                           * 副驾加热档位状态: 0：OFF 1：LV1 2：LV2 3：LV3
                                           */
enHeatLvlSts HeatFalut_D_SimuIndex_ThirdHeat;/* '<S27>/HeatFalut_D_SimuIndex_ThirdHeat'
                                              * 三排加热档位状态: 0：OFF 1：LV1 2：LV2 3：LV3
                                              */
enHeatIoSts HeatFalut_D_SimuIndex_DRHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_DRHeatIo'
                                            * 主驾加热硬线状态 0：低电平 1：高电平
                                            */
enHeatIoSts HeatFalut_D_SimuIndex_PAHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_PAHeatIo'
                                            * 副驾加热硬线状态 0：低电平 1：高电平
                                            */
enHeatIoSts HeatFalut_D_SimuIndex_ThirdHeatIo;/* '<S27>/HeatFalut_D_SimuIndex_ThirdHeatIo'
                                               * 三排加热硬线状态 0：低电平 1：高电平
                                               */
enHeatIoSts HeatFalut_MemIndexDrHeatConfig;/* '<S27>/HeatFalut_MemIndexDrHeatConfig'
                                            * 主驾加热配置 0：无 1：有
                                            */
INT16U HeatFalut_DrHeatIsAdc;          /* '<S27>/HeatFalut_DrHeatIsAdc'
                                        * 主驾加热输出电流值AD
                                        */
INT16U HeatFalut_DrHeatNtcAdc;         /* '<S27>/HeatFalut_DrHeatNtcAdc'
                                        * 主驾NTC 温度值
                                        */
INT16U HeatFalut_PaHeatIsAdc;          /* '<S27>/HeatFalut_PaHeatIsAdc'
                                        * 副驾加热输出电流值AD
                                        */
INT16U HeatFalut_PaHeatNtcAdc;         /* '<S27>/HeatFalut_PaHeatNtcAdc'
                                        * 副驾NTC 温度值
                                        */
INT16U HeatFalut_ThirdHeatIsAdc;       /* '<S27>/HeatFalut_ThirdHeatIsAdc'
                                        * 三排加热输出电流值AD
                                        */
INT16U HeatFalut_ThirdHeatNtcAdc;      /* '<S27>/HeatFalut_ThirdHeatNtcAdc'
                                        * 三排NTC 温度值-预留
                                        */
INT8U HeatFalut_3rdCmdOpenload;        /* '<S27>/HeatFalut_3rdCmdOpenload'
                                        * 三排加热CMD是否开路DTC 0：否 1：是
                                        */
INT8U HeatFalut_3rdCmdShortGND;        /* '<S27>/HeatFalut_3rdCmdShortGND'
                                        * 三排加热CMD是否短路到地DTC 0：否 1：是
                                        */
INT8U HeatFalut_DrCmdOpenload;         /* '<S27>/HeatFalut_DrCmdOpenload'
                                        * 主驾加热CMD是否开路DTC 0：否 1：是
                                        */
INT8U HeatFalut_DrCmdShortGND;         /* '<S27>/HeatFalut_DrCmdShortGND'
                                        * 主驾加热CMD是否短路到地DTC 0：否 1：是
                                        */
INT8U HeatFalut_MemDiagDrHeatFlg;      /* '<S27>/HeatFalut_MemDiagDrHeatFlg'
                                        * 主驾通风加热使能配置（P20诊断） 0：无 1：有
                                        */
INT8U HeatFalut_MemDiagPaHeatFlg;      /* '<S27>/HeatFalut_MemDiagPaHeatFlg'
                                        * 副驾通风加热使能配置（P20诊断） 0：无 1：有
                                        */
INT8U HeatFalut_MemIndexPaHeatConfig;  /* '<S27>/HeatFalut_MemIndexPaHeatConfig'
                                        * 副驾加热配置 0：无 1：有
                                        */
INT8U HeatFalut_MemIndexThirdHeatConfig;/* '<S27>/HeatFalut_MemIndexThirdHeatConfig'
                                         * 三排加热配置 0：无 1：有
                                         */
INT8U HeatFalut_PaCmdOpenload;         /* '<S27>/HeatFalut_PaCmdOpenload'
                                        * 副驾加热CMD是否开路DTC 0：否 1：是
                                        */
INT8U HeatFalut_PaCmdShortGND;         /* '<S27>/HeatFalut_PaCmdShortGND'
                                        * 副驾加热CMD是否短路到地DTC 0：否 1：是
                                        */

/* Block signals (default storage) */
B_Appl_HeatFault_CtrlModel_T Appl_HeatFault_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_HeatFault_CtrlModel_T Appl_HeatFault_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_HeatFault_CtrlModel_T Appl_HeatFault_CtrlModel_M_;
RT_MODEL_Appl_HeatFault_CtrlModel_T *const Appl_HeatFault_CtrlModel_M =
  &Appl_HeatFault_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT8U CAL_CmdOpenTime = 20U;/* 加热输出判断时间：200ms */
const volatile INT8U CAL_CmdShortTime = 20U;/* 加热输出短地判断时间：200ms */
const volatile INT8U CAL_NTCOpenTime = 100U;/* NTC开路判断时间：1000ms */
const volatile INT16U CAL_NTCOverTime = 500U;/* NTC不可信判断时间：5000ms */
const volatile INT8U CAL_NTCShortTime = 100U;/* NTC短地判断时间：1000ms */
const volatile INT8U CAL_NTCWaitTime = 100U;/* NTC采集滤波时间：1000ms */
static void Appl_HeatFault_CtrlMode_HeatCmdAquireFunction_Init(INT8U
  *rty_HeatCmd, DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T *localDW);
static void Appl_HeatFault_CtrlModel_HeatCmdAquireFunction(enHeatLvlSts
  rtu_API_HeatCmd, INT8U rtu_HeatCfg, INT8U rtu_HeatFlg, INT8U *rty_HeatCmd,
  DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T *localDW);
static void Appl_HeatFault_CtrlMo_HeatCmdDiagnoseFunction_Init(enHeatCmdFault
  *rty_HeatCmdFault, enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnoseFunction(enHeatIoSts
  rtu_HeatIOSts, INT8U rtu_HeatCmd, INT16U rtu_HeatIS, DOUBLE rtu_FaultType,
  enHeatCmdFault *rty_HeatCmdFault, enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);
static void Appl_HeatFault_CtrlMo_HeatNTCDiagnoseFunction_Init(enHeatNtcFault
  *rty_HeatNTCFault, DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);
static void Appl_HeatFault_CtrlModel_HeatNTCDiagnoseFunction(INT16U rtu_HeatNTC,
  INT16U rtu_NtcMin, INT16U rtu_NtcMax, enHeatNtcFault *rty_HeatNTCFault,
  DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);
static void Appl_HeatFault_CtrlModel_getFaultType_Init(INT8U *rty_FaultType);
static void Appl_HeatFault_CtrlModel_getFaultType(INT8U rtu_ShortGND, INT8U
  rtu_Openload, INT8U *rty_FaultType);
static void Appl_HeatFault_CtrlModel_LogicCtrl_Init(void);
static void Appl_HeatFault_CtrlModel_LogicCtrl(void);
static void Appl_HeatFault_CtrlModel_RTE(void);
static void Appl_HeatFault_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_HeatFault_CtrlModel_UpDataInputInfo(void);
static void Appl_HeatFault_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnosis(enHeatIoSts rtu_HeatIOSts,
  INT8U rtu_HeatCmd, INT16U rtu_HeatIS, enHeatCmdFault *rty_HeatCmdFault,
  enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);
static INT32S Appl_HeatFault_CtrlMod_safe_cast_to_enHeatCmdFault(INT32S input);

/* Forward declaration for local functions */
static void Appl_HeatFault_CtrlModel_inner_default_Default(enHeatNtcFault
  *rty_HeatNTCFault, DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW);

/* Forward declaration for local functions */
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnosis_o(const enHeatIoSts
  *HeatIOSts_f, const INT8U *HeatCmd_n, const INT16U *HeatIS_c);
static INT32S Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_f(INT32S input);

/* Forward declaration for local functions */
static INT32S Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_j(INT32S input);

/*
 * System initialize for function-call system:
 *    '<S6>/HeatCmdAquireFunction'
 *    '<S6>/HeatCmdAquireFunction1'
 *    '<S6>/HeatCmdAquireFunction2'
 */
static void Appl_HeatFault_CtrlMode_HeatCmdAquireFunction_Init(INT8U
  *rty_HeatCmd, DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T *localDW)
{
  localDW->is_active_c2_Appl_HeatFault_CtrlModel = 0U;
  localDW->is_c2_Appl_HeatFault_CtrlModel =
    Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD;
  *rty_HeatCmd = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S6>/HeatCmdAquireFunction'
 *    '<S6>/HeatCmdAquireFunction1'
 *    '<S6>/HeatCmdAquireFunction2'
 */
static void Appl_HeatFault_CtrlModel_HeatCmdAquireFunction(enHeatLvlSts
  rtu_API_HeatCmd, INT8U rtu_HeatCfg, INT8U rtu_HeatFlg, INT8U *rty_HeatCmd,
  DW_HeatCmdAquireFunction_Appl_HeatFault_CtrlMode_T *localDW)
{
  if (localDW->is_active_c2_Appl_HeatFault_CtrlModel == 0U)
  {
    localDW->is_active_c2_Appl_HeatFault_CtrlModel = 1U;
    localDW->is_c2_Appl_HeatFault_CtrlModel =
      Appl_HeatFault_CtrlModel_IN_HeatCmdInvalid;
    *rty_HeatCmd = ((BOOL)FALSE);
  }
  else if (localDW->is_c2_Appl_HeatFault_CtrlModel ==
           Appl_HeatFault_CtrlModel_IN_HeatCmdInvalid)
  {
    *rty_HeatCmd = ((BOOL)FALSE);

    /*  指令有效  */
    if ((enHeatLvlSts_EN_HEAT_LVL_OFF != rtu_API_HeatCmd) && (((BOOL)TRUE) ==
         rtu_HeatCfg) && (((BOOL)TRUE) == rtu_HeatFlg))
    {
      localDW->is_c2_Appl_HeatFault_CtrlModel =
        Appl_HeatFault_CtrlModel_IN_HeatCmdValid;
      *rty_HeatCmd = ((BOOL)TRUE);
    }
  }
  else
  {
    *rty_HeatCmd = ((BOOL)TRUE);

    /*  指令无效  */
    if ((enHeatLvlSts_EN_HEAT_LVL_OFF == rtu_API_HeatCmd) || (((BOOL)TRUE) !=
         rtu_HeatCfg) || (((BOOL)TRUE) != rtu_HeatFlg))
    {
      localDW->is_c2_Appl_HeatFault_CtrlModel =
        Appl_HeatFault_CtrlModel_IN_HeatCmdInvalid;
      *rty_HeatCmd = ((BOOL)FALSE);
    }
  }
}

/* Function for Chart: '<S14>/HeatCmdDiagnose' */
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnosis(enHeatIoSts rtu_HeatIOSts,
  INT8U rtu_HeatCmd, INT16U rtu_HeatIS, enHeatCmdFault *rty_HeatCmdFault,
  enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  INT32S tmp;

  /*  无加热CMD  */
  if (((BOOL)TRUE) != rtu_HeatCmd)
  {
    switch (localDW->is_HeatCmdDiagnosis)
    {
     case Appl_HeatFault_CtrlModel_IN_CmdOpenLoad:
      localDW->OpenTimer = 0U;
      localDW->is_HeatCmdDiagnosis =
        Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f;
      break;

     case Appl_HeatFault_CtrlModel_IN_CmdShortToGND:
      localDW->ShortTimer = 0U;
      localDW->is_HeatCmdDiagnosis =
        Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f;
      break;

     default:
      localDW->is_HeatCmdDiagnosis =
        Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f;
      break;
    }

    localDW->is_c4_Appl_HeatFault_CtrlModel =
      Appl_HeatFault_CtrlModel_IN_HeatCmdClose;
    localDW->OpenTimer = 0U;
    localDW->ShortTimer = 0U;
    *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }
  else
  {
    switch (localDW->is_HeatCmdDiagnosis)
    {
     case Appl_HeatFault_CtrlModel_IN_CmdOpenLoad:
      /*  低电平  */
      if (enHeatIoSts_EN_HEAT_IO_LOW == rtu_HeatIOSts)
      {
        localDW->OpenTimer = 0U;
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_OpenLow;
      }
      else
      {
        /*  输出电流开路恢复  */
        if (((INT16U)D_HEATFALUT_CmdOpenLoad) <= rtu_HeatIS)
        {
          localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_Default;
          localDW->OpenTimer = 0U;
          localDW->ShortTimer = 0U;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
          localDW->RecoverTimer = 0U;

          /*  未超时  */
          if (CAL_CmdShortTime > localDW->RecoverTimer)
          {
            tmp = localDW->RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            localDW->RecoverTimer = (INT8U)tmp;
          }
          else
          {
            localDW->RecoverTimer = CAL_CmdShortTime;
            *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
        else
        {
          /*  输出电流对地短路  */
          if (((INT16U)D_HEATFALUT_CmdShortToGnd) < rtu_HeatIS)
          {
            localDW->OpenTimer = 0U;
            localDW->is_HeatCmdDiagnosis =
              Appl_HeatFault_CtrlModel_IN_CmdShortToGND;

            /*  未超时  */
            if (CAL_CmdShortTime > localDW->ShortTimer)
            {
              tmp = localDW->ShortTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              localDW->ShortTimer = (INT8U)tmp;
            }
            else
            {
              localDW->ShortTimer = CAL_CmdShortTime;
              *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_GND;
              *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_GND;
            }
          }
          else
          {
            /*  未超时  */
            if (CAL_CmdOpenTime > localDW->OpenTimer)
            {
              tmp = localDW->OpenTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              localDW->OpenTimer = (INT8U)tmp;
            }
            else
            {
              localDW->OpenTimer = CAL_CmdOpenTime;
              *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
              *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            }
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_CmdShortToGND:
      /*  低电平  */
      if (enHeatIoSts_EN_HEAT_IO_LOW == rtu_HeatIOSts)
      {
        localDW->ShortTimer = 0U;
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_ShortLow;
      }
      else
      {
        /*  输出电流对地短路恢复  */
        if (((INT16U)D_HEATFALUT_CmdShortToGnd) >= rtu_HeatIS)
        {
          localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_Default;
          localDW->OpenTimer = 0U;
          localDW->ShortTimer = 0U;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
          localDW->RecoverTimer = 0U;

          /*  未超时  */
          if (CAL_CmdShortTime > localDW->RecoverTimer)
          {
            tmp = localDW->RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            localDW->RecoverTimer = (INT8U)tmp;
          }
          else
          {
            localDW->RecoverTimer = CAL_CmdShortTime;
            *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
        else
        {
          /*  输出电流开路  */
          if (((INT16U)D_HEATFALUT_CmdOpenLoad) > rtu_HeatIS)
          {
            localDW->ShortTimer = 0U;
            localDW->is_HeatCmdDiagnosis =
              Appl_HeatFault_CtrlModel_IN_CmdOpenLoad;

            /*  未超时  */
            if (CAL_CmdOpenTime > localDW->OpenTimer)
            {
              tmp = localDW->OpenTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              localDW->OpenTimer = (INT8U)tmp;
            }
            else
            {
              localDW->OpenTimer = CAL_CmdOpenTime;
              *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
              *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            }
          }
          else
          {
            /*  未超时  */
            if (CAL_CmdShortTime > localDW->ShortTimer)
            {
              tmp = localDW->ShortTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              localDW->ShortTimer = (INT8U)tmp;
            }
            else
            {
              localDW->ShortTimer = CAL_CmdShortTime;
              *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_GND;
              *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_GND;
            }
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_Default:
      /*  输出电流对地短路  */
      if (((INT16U)D_HEATFALUT_CmdShortToGnd) < rtu_HeatIS)
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdShortToGND;

        /*  未超时  */
        if (CAL_CmdShortTime > localDW->ShortTimer)
        {
          tmp = localDW->ShortTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->ShortTimer = (INT8U)tmp;
        }
        else
        {
          localDW->ShortTimer = CAL_CmdShortTime;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_GND;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_GND;
        }
      }
      else
      {
        /*  输出电流开路  */
        if (((INT16U)D_HEATFALUT_CmdOpenLoad) > rtu_HeatIS)
        {
          localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdOpenLoad;

          /*  未超时  */
          if (CAL_CmdOpenTime > localDW->OpenTimer)
          {
            tmp = localDW->OpenTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            localDW->OpenTimer = (INT8U)tmp;
          }
          else
          {
            localDW->OpenTimer = CAL_CmdOpenTime;
            *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          }
        }
        else
        {
          /*  未超时  */
          if (CAL_CmdShortTime > localDW->RecoverTimer)
          {
            tmp = localDW->RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            localDW->RecoverTimer = (INT8U)tmp;
          }
          else
          {
            localDW->RecoverTimer = CAL_CmdShortTime;
            *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_OpenLow:
      /*  高电平  */
      if (enHeatIoSts_EN_HEAT_IO_HIGH == rtu_HeatIOSts)
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdOpenLoad;

        /*  未超时  */
        if (CAL_CmdOpenTime > localDW->OpenTimer)
        {
          tmp = localDW->OpenTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->OpenTimer = (INT8U)tmp;
        }
        else
        {
          localDW->OpenTimer = CAL_CmdOpenTime;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
        }
      }
      break;

     default:
      /*  高电平  */
      if (enHeatIoSts_EN_HEAT_IO_HIGH == rtu_HeatIOSts)
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdShortToGND;

        /*  未超时  */
        if (CAL_CmdShortTime > localDW->ShortTimer)
        {
          tmp = localDW->ShortTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->ShortTimer = (INT8U)tmp;
        }
        else
        {
          localDW->ShortTimer = CAL_CmdShortTime;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_GND;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_GND;
        }
      }
      break;
    }
  }
}

static INT32S Appl_HeatFault_CtrlMod_safe_cast_to_enHeatCmdFault(INT32S input)
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

/*
 * System initialize for function-call system:
 *    '<S7>/HeatCmdDiagnoseFunction'
 *    '<S7>/HeatCmdDiagnoseFunction1'
 */
static void Appl_HeatFault_CtrlMo_HeatCmdDiagnoseFunction_Init(enHeatCmdFault
  *rty_HeatCmdFault, enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f;
  localDW->is_active_c4_Appl_HeatFault_CtrlModel = 0U;
  localDW->is_c4_Appl_HeatFault_CtrlModel =
    Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_f;
  localDW->ShortTimer = 0U;
  localDW->OpenTimer = 0U;
  localDW->RecoverTimer = 0U;
  *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S7>/HeatCmdDiagnoseFunction'
 *    '<S7>/HeatCmdDiagnoseFunction1'
 */
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnoseFunction(enHeatIoSts
  rtu_HeatIOSts, INT8U rtu_HeatCmd, INT16U rtu_HeatIS, DOUBLE rtu_FaultType,
  enHeatCmdFault *rty_HeatCmdFault, enHeatCmdFault *rty_HeatCmdFault4DTC,
  DW_HeatCmdDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  INT32S tmp;
  if (localDW->is_active_c4_Appl_HeatFault_CtrlModel == 0U)
  {
    localDW->is_active_c4_Appl_HeatFault_CtrlModel = 1U;
    localDW->is_c4_Appl_HeatFault_CtrlModel =
      Appl_HeatFault_CtrlModel_IN_HeatCmdClose;
    localDW->OpenTimer = 0U;
    localDW->ShortTimer = 0U;
    *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }
  else if (localDW->is_c4_Appl_HeatFault_CtrlModel ==
           Appl_HeatFault_CtrlModel_IN_HeatCmdClose)
  {
    /*  加热CMD  */
    if (((BOOL)TRUE) == rtu_HeatCmd)
    {
      if (rtu_FaultType < 2.147483648E+9)
      {
        if (rtu_FaultType >= -2.147483648E+9)
        {
          *rty_HeatCmdFault4DTC = (enHeatCmdFault)
            Appl_HeatFault_CtrlMod_safe_cast_to_enHeatCmdFault((INT32S)
            rtu_FaultType);
        }
        else
        {
          *rty_HeatCmdFault4DTC = (enHeatCmdFault)
            Appl_HeatFault_CtrlMod_safe_cast_to_enHeatCmdFault(MIN_int32_T);
        }
      }
      else
      {
        *rty_HeatCmdFault4DTC = (enHeatCmdFault)
          Appl_HeatFault_CtrlMod_safe_cast_to_enHeatCmdFault(MAX_int32_T);
      }

      localDW->is_c4_Appl_HeatFault_CtrlModel =
        Appl_HeatFault_CtrlModel_IN_HeatCmdDiagnosis;
      if (rtu_FaultType == 1.0)
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdShortToGND;

        /*  未超时  */
        if (CAL_CmdShortTime > localDW->ShortTimer)
        {
          tmp = localDW->ShortTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->ShortTimer = (INT8U)tmp;
        }
        else
        {
          localDW->ShortTimer = CAL_CmdShortTime;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_GND;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_GND;
        }
      }
      else if (rtu_FaultType == 2.0)
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_CmdOpenLoad;

        /*  未超时  */
        if (CAL_CmdOpenTime > localDW->OpenTimer)
        {
          tmp = localDW->OpenTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->OpenTimer = (INT8U)tmp;
        }
        else
        {
          localDW->OpenTimer = CAL_CmdOpenTime;
          *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_OPEN;
        }
      }
      else
      {
        localDW->is_HeatCmdDiagnosis = Appl_HeatFault_CtrlModel_IN_Default;
        localDW->OpenTimer = 0U;
        localDW->ShortTimer = 0U;
        *rty_HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
        localDW->RecoverTimer = 0U;

        /*  未超时  */
        if (CAL_CmdShortTime > localDW->RecoverTimer)
        {
          tmp = localDW->RecoverTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->RecoverTimer = (INT8U)tmp;
        }
        else
        {
          localDW->RecoverTimer = CAL_CmdShortTime;
          *rty_HeatCmdFault4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
        }
      }
    }
  }
  else
  {
    Appl_HeatFault_CtrlModel_HeatCmdDiagnosis(rtu_HeatIOSts, rtu_HeatCmd,
      rtu_HeatIS, rty_HeatCmdFault, rty_HeatCmdFault4DTC, localDW);
  }
}

/* Function for Chart: '<S17>/HeatCmdDiagnose' */
static void Appl_HeatFault_CtrlModel_inner_default_Default(enHeatNtcFault
  *rty_HeatNTCFault, DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  INT32S tmp;

  /*  等待超时  */
  if (CAL_NTCWaitTime > localDW->WaitAquireTimer)
  {
    tmp = localDW->WaitAquireTimer + 1;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    localDW->WaitAquireTimer = (INT16U)tmp;
  }
  else
  {
    localDW->WaitAquireTimer = CAL_NTCWaitTime;
  }

  if (*rty_HeatNTCFault != enHeatNtcFault_EN_NTC_FAULT_NONE)
  {
    tmp = localDW->RecoveryTimer + 1;
    if (tmp > 65535)
    {
      tmp = 65535;
    }

    localDW->RecoveryTimer = (INT16U)tmp;

    /*  NTC不可信故障 */
    if (*rty_HeatNTCFault == enHeatNtcFault_EN_NTC_FAULT_UNC)
    {
      /* 计时超过5s */
      if (CAL_NTCOverTime < localDW->RecoveryTimer)
      {
        localDW->RecoveryTimer = CAL_NTCOverTime;
        *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_NONE;
      }
    }
    else
    {
      /* 开路和短地时间皆为1s */
      if (CAL_NTCOpenTime < localDW->RecoveryTimer)
      {
        localDW->RecoveryTimer = CAL_NTCOpenTime;
        *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_NONE;
      }
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S7>/HeatNTCDiagnoseFunction'
 *    '<S7>/HeatNTCDiagnoseFunction1'
 *    '<S7>/HeatNTCDiagnoseFunction2'
 */
static void Appl_HeatFault_CtrlMo_HeatNTCDiagnoseFunction_Init(enHeatNtcFault
  *rty_HeatNTCFault, DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  localDW->is_active_c5_Appl_HeatFault_CtrlModel = 0U;
  localDW->is_c5_Appl_HeatFault_CtrlModel =
    Appl_HeatFault_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  localDW->ShortTimer = 0U;
  localDW->WaitAquireTimer = 0U;
  localDW->OpenTimer = 0U;
  localDW->OverTimer = 0U;
  localDW->RecoveryTimer = 0U;
  *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S7>/HeatNTCDiagnoseFunction'
 *    '<S7>/HeatNTCDiagnoseFunction1'
 *    '<S7>/HeatNTCDiagnoseFunction2'
 */
static void Appl_HeatFault_CtrlModel_HeatNTCDiagnoseFunction(INT16U rtu_HeatNTC,
  INT16U rtu_NtcMin, INT16U rtu_NtcMax, enHeatNtcFault *rty_HeatNTCFault,
  DW_HeatNTCDiagnoseFunction_Appl_HeatFault_CtrlMo_T *localDW)
{
  INT32S tmp;
  if (localDW->is_active_c5_Appl_HeatFault_CtrlModel == 0U)
  {
    localDW->is_active_c5_Appl_HeatFault_CtrlModel = 1U;
    localDW->is_c5_Appl_HeatFault_CtrlModel =
      Appl_HeatFault_CtrlModel_IN_Default_h;
    localDW->WaitAquireTimer = 1U;
    localDW->RecoveryTimer = 0U;
    Appl_HeatFault_CtrlModel_inner_default_Default(rty_HeatNTCFault, localDW);
  }
  else
  {
    switch (localDW->is_c5_Appl_HeatFault_CtrlModel)
    {
     case Appl_HeatFault_CtrlModel_IN_Default_h:
      /*  对地恢复  */
      if ((((INT16U)D_HEATFALUT_NtcShortToGnd) >= rtu_HeatNTC) &&
          (CAL_NTCWaitTime <= localDW->WaitAquireTimer))
      {
        localDW->WaitAquireTimer = 0U;
        localDW->is_c5_Appl_HeatFault_CtrlModel =
          Appl_HeatFault_CtrlModel_IN_NTCShortToGND;

        /*  短地超时  */
        if (CAL_NTCShortTime > localDW->ShortTimer)
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
          localDW->ShortTimer = CAL_NTCShortTime;
          *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_GND;
        }
      }
      else
      {
        /*  NTC开路  */
        if ((((INT16U)D_HEATFALUT_NtcOpenLoad) < rtu_HeatNTC) &&
            (CAL_NTCWaitTime <= localDW->WaitAquireTimer))
        {
          localDW->WaitAquireTimer = 0U;
          localDW->is_c5_Appl_HeatFault_CtrlModel =
            Appl_HeatFault_CtrlModel_IN_NTCOpenLoad;

          /*  开路超时  */
          if (CAL_NTCOpenTime > localDW->OpenTimer)
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
            localDW->OpenTimer = CAL_NTCOpenTime;
            *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_OPEN;
          }
        }
        else
        {
          /*  NTC 不可信  */
          if (((rtu_NtcMax < rtu_HeatNTC) || (rtu_NtcMin > rtu_HeatNTC)) &&
              (CAL_NTCWaitTime <= localDW->WaitAquireTimer))
          {
            localDW->WaitAquireTimer = 0U;
            localDW->is_c5_Appl_HeatFault_CtrlModel =
              Appl_HeatFault_CtrlModel_IN_NTCOverRange;

            /*  不可信超时  */
            if (CAL_NTCOverTime > localDW->OverTimer)
            {
              tmp = localDW->OverTimer + 1;
              if (tmp > 65535)
              {
                tmp = 65535;
              }

              localDW->OverTimer = (INT16U)tmp;
            }
            else
            {
              localDW->OverTimer = CAL_NTCOverTime;
              *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_UNC;
            }
          }
          else
          {
            Appl_HeatFault_CtrlModel_inner_default_Default(rty_HeatNTCFault,
              localDW);
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_NTCOpenLoad:
      /*  NTC开路恢复 */
      if (((INT16U)D_HEATFALUT_NtcOpenLoad) >= rtu_HeatNTC)
      {
        localDW->OpenTimer = 0U;
        localDW->is_c5_Appl_HeatFault_CtrlModel =
          Appl_HeatFault_CtrlModel_IN_Default_h;
        localDW->WaitAquireTimer = 1U;
        localDW->RecoveryTimer = 0U;
        Appl_HeatFault_CtrlModel_inner_default_Default(rty_HeatNTCFault, localDW);
      }
      else
      {
        /*  开路超时  */
        if (CAL_NTCOpenTime > localDW->OpenTimer)
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
          localDW->OpenTimer = CAL_NTCOpenTime;
          *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_OPEN;
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_NTCOverRange:
      /*  NTC不可信恢复  */
      if (((rtu_NtcMax >= rtu_HeatNTC) && (rtu_NtcMin <= rtu_HeatNTC)) ||
          (((INT16U)D_HEATFALUT_NtcOpenLoad) < rtu_HeatNTC) || (((INT16U)
            D_HEATFALUT_NtcShortToGnd) >= rtu_HeatNTC))
      {
        localDW->OverTimer = 0U;
        localDW->is_c5_Appl_HeatFault_CtrlModel =
          Appl_HeatFault_CtrlModel_IN_Default_h;
        localDW->WaitAquireTimer = 1U;
        localDW->RecoveryTimer = 0U;
        Appl_HeatFault_CtrlModel_inner_default_Default(rty_HeatNTCFault, localDW);
      }
      else
      {
        /*  不可信超时  */
        if (CAL_NTCOverTime > localDW->OverTimer)
        {
          tmp = localDW->OverTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          localDW->OverTimer = (INT16U)tmp;
        }
        else
        {
          localDW->OverTimer = CAL_NTCOverTime;
          *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_UNC;
        }
      }
      break;

     default:
      /*  对地短路  */
      if (((INT16U)D_HEATFALUT_NtcShortToGnd) < rtu_HeatNTC)
      {
        localDW->ShortTimer = 0U;
        localDW->is_c5_Appl_HeatFault_CtrlModel =
          Appl_HeatFault_CtrlModel_IN_Default_h;
        localDW->WaitAquireTimer = 1U;
        localDW->RecoveryTimer = 0U;
        Appl_HeatFault_CtrlModel_inner_default_Default(rty_HeatNTCFault, localDW);
      }
      else
      {
        /*  短地超时  */
        if (CAL_NTCShortTime > localDW->ShortTimer)
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
          localDW->ShortTimer = CAL_NTCShortTime;
          *rty_HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_GND;
        }
      }
      break;
    }
  }
}

/* Function for Chart: '<S16>/HeatCmdDiagnose' */
static void Appl_HeatFault_CtrlModel_HeatCmdDiagnosis_o(const enHeatIoSts
  *HeatIOSts_f, const INT8U *HeatCmd_n, const INT16U *HeatIS_c)
{
  INT32S tmp;

  /*  无加热CMD  */
  if (((BOOL)TRUE) != *HeatCmd_n)
  {
    switch (Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis)
    {
     case Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g:
      Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
      Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis = 0;
      break;

     case Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e:
      Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
      Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis = 0;
      break;

     default:
      Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis = 0;
      break;
    }

    Appl_HeatFault_CtrlModel_DW.is_c9_Appl_HeatFault_CtrlModel =
      Appl_HeatFault_CtrlModel_IN_HeatCmdClose_p;
    Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
    Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }
  else
  {
    switch (Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis)
    {
     case Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g:
      /*  低电平  */
      if (enHeatIoSts_EN_HEAT_IO_LOW == *HeatIOSts_f)
      {
        Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
        Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
          Appl_HeatFault_CtrlModel_IN_OpenLow_a;
      }
      else
      {
        /*  输出电流开路恢复  */
        if (((INT16U)D_HEATFALUT_CmdOpenLoad_W) <= *HeatIS_c)
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_Default_o;
          Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
          Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_NONE;
          Appl_HeatFault_CtrlModel_DW.RecoverTimer = 0U;

          /*  未超时  */
          if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.RecoverTimer)
          {
            tmp = Appl_HeatFault_CtrlModel_DW.RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.RecoverTimer = (INT8U)tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.RecoverTimer = CAL_CmdShortTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
        else
        {
          /*  输出电流对地短路  */
          if (((INT16U)D_HEATFALUT_CmdShortToGnd) < *HeatIS_c)
          {
            Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
            Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
              Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e;

            /*  未超时  */
            if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.ShortTimer)
            {
              tmp = Appl_HeatFault_CtrlModel_DW.ShortTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_HeatFault_CtrlModel_DW.ShortTimer = (INT8U)tmp;
            }
            else
            {
              Appl_HeatFault_CtrlModel_DW.ShortTimer = CAL_CmdShortTime;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault =
                enHeatCmdFault_EN_HEAT_FAULT_GND;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
                enHeatCmdFault_EN_HEAT_FAULT_GND;
            }
          }
          else
          {
            /*  未超时  */
            if (CAL_CmdOpenTime > Appl_HeatFault_CtrlModel_DW.OpenTimer)
            {
              tmp = Appl_HeatFault_CtrlModel_DW.OpenTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_HeatFault_CtrlModel_DW.OpenTimer = (INT8U)tmp;
            }
            else
            {
              Appl_HeatFault_CtrlModel_DW.OpenTimer = CAL_CmdOpenTime;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault =
                enHeatCmdFault_EN_HEAT_FAULT_OPEN;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
                enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            }
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e:
      /*  低电平  */
      if (enHeatIoSts_EN_HEAT_IO_LOW == *HeatIOSts_f)
      {
        Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
        Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
          Appl_HeatFault_CtrlModel_IN_ShortLow_k;
      }
      else
      {
        /*  输出电流对地短路恢复  */
        if (((INT16U)D_HEATFALUT_CmdShortToGnd) >= *HeatIS_c)
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_Default_o;
          Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
          Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_NONE;
          Appl_HeatFault_CtrlModel_DW.RecoverTimer = 0U;

          /*  未超时  */
          if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.RecoverTimer)
          {
            tmp = Appl_HeatFault_CtrlModel_DW.RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.RecoverTimer = (INT8U)tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.RecoverTimer = CAL_CmdShortTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
        else
        {
          /*  输出电流开路  */
          if (((INT16U)D_HEATFALUT_CmdOpenLoad_W) > *HeatIS_c)
          {
            Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
            Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
              Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g;

            /*  未超时  */
            if (CAL_CmdOpenTime > Appl_HeatFault_CtrlModel_DW.OpenTimer)
            {
              tmp = Appl_HeatFault_CtrlModel_DW.OpenTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_HeatFault_CtrlModel_DW.OpenTimer = (INT8U)tmp;
            }
            else
            {
              Appl_HeatFault_CtrlModel_DW.OpenTimer = CAL_CmdOpenTime;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault =
                enHeatCmdFault_EN_HEAT_FAULT_OPEN;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
                enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            }
          }
          else
          {
            /*  未超时  */
            if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.ShortTimer)
            {
              tmp = Appl_HeatFault_CtrlModel_DW.ShortTimer + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_HeatFault_CtrlModel_DW.ShortTimer = (INT8U)tmp;
            }
            else
            {
              Appl_HeatFault_CtrlModel_DW.ShortTimer = CAL_CmdShortTime;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault =
                enHeatCmdFault_EN_HEAT_FAULT_GND;
              Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
                enHeatCmdFault_EN_HEAT_FAULT_GND;
            }
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_Default_o:
      /*  输出电流对地短路  */
      if (((INT16U)D_HEATFALUT_CmdShortToGnd) < *HeatIS_c)
      {
        Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
          Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e;

        /*  未超时  */
        if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.ShortTimer)
        {
          tmp = Appl_HeatFault_CtrlModel_DW.ShortTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_HeatFault_CtrlModel_DW.ShortTimer = (INT8U)tmp;
        }
        else
        {
          Appl_HeatFault_CtrlModel_DW.ShortTimer = CAL_CmdShortTime;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_GND;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
            enHeatCmdFault_EN_HEAT_FAULT_GND;
        }
      }
      else
      {
        /*  输出电流开路  */
        if (((INT16U)D_HEATFALUT_CmdOpenLoad_W) > *HeatIS_c)
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g;

          /*  未超时  */
          if (CAL_CmdOpenTime > Appl_HeatFault_CtrlModel_DW.OpenTimer)
          {
            tmp = Appl_HeatFault_CtrlModel_DW.OpenTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.OpenTimer = (INT8U)tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.OpenTimer = CAL_CmdOpenTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault =
              enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          }
        }
        else
        {
          /*  未超时  */
          if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.RecoverTimer)
          {
            tmp = Appl_HeatFault_CtrlModel_DW.RecoverTimer + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.RecoverTimer = (INT8U)tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.RecoverTimer = CAL_CmdShortTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
      }
      break;

     case Appl_HeatFault_CtrlModel_IN_OpenLow_a:
      /*  高电平  */
      if (enHeatIoSts_EN_HEAT_IO_HIGH == *HeatIOSts_f)
      {
        Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
          Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g;

        /*  未超时  */
        if (CAL_CmdOpenTime > Appl_HeatFault_CtrlModel_DW.OpenTimer)
        {
          tmp = Appl_HeatFault_CtrlModel_DW.OpenTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_HeatFault_CtrlModel_DW.OpenTimer = (INT8U)tmp;
        }
        else
        {
          Appl_HeatFault_CtrlModel_DW.OpenTimer = CAL_CmdOpenTime;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
            enHeatCmdFault_EN_HEAT_FAULT_OPEN;
        }
      }
      break;

     default:
      /*  高电平  */
      if (enHeatIoSts_EN_HEAT_IO_HIGH == *HeatIOSts_f)
      {
        Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
          Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e;

        /*  未超时  */
        if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.ShortTimer)
        {
          tmp = Appl_HeatFault_CtrlModel_DW.ShortTimer + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          Appl_HeatFault_CtrlModel_DW.ShortTimer = (INT8U)tmp;
        }
        else
        {
          Appl_HeatFault_CtrlModel_DW.ShortTimer = CAL_CmdShortTime;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_GND;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
            enHeatCmdFault_EN_HEAT_FAULT_GND;
        }
      }
      break;
    }
  }
}

static INT32S Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_f(INT32S input)
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

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_HeatFault_CtrlModel_LogicCtrl_Init(void)
{
  INT8U HeatCmd_j;
  Appl_HeatFault_CtrlModel_DW.is_active_c1_Appl_HeatFault_CtrlModel = 0U;
  Appl_HeatFault_CtrlModel_B.DrHeatCmd = 0U;
  Appl_HeatFault_CtrlModel_B.PaHeatCmd = 0U;
  Appl_HeatFault_CtrlModel_B.ThirdHeatCmd = 0U;
  Appl_HeatFault_CtrlMode_HeatCmdAquireFunction_Init(&HeatCmd_j,
    &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction);
  Appl_HeatFault_CtrlMode_HeatCmdAquireFunction_Init(&HeatCmd_j,
    &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction1);
  Appl_HeatFault_CtrlMode_HeatCmdAquireFunction_Init(&HeatCmd_j,
    &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction2);
  Appl_HeatFault_CtrlModel_DW.is_active_c3_Appl_HeatFault_CtrlModel = 0U;
  Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatNTCFaultSts =
    enHeatNtcFault_EN_NTC_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatNTCFaultSts =
    enHeatNtcFault_EN_NTC_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatNTCFaultSts =
    enHeatNtcFault_EN_NTC_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts4DTC =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts4DTC =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts4DTC =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlMo_HeatCmdDiagnoseFunction_Init
    (&Appl_HeatFault_CtrlModel_B.HeatCmdFault_e,
     &Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_f,
     &Appl_HeatFault_CtrlModel_DW.HeatCmdDiagnoseFunction);
  Appl_HeatFault_CtrlMo_HeatNTCDiagnoseFunction_Init
    (&Appl_HeatFault_CtrlModel_B.HeatNTCFault_h,
     &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction);
  Appl_HeatFault_CtrlMo_HeatCmdDiagnoseFunction_Init
    (&Appl_HeatFault_CtrlModel_B.HeatCmdFault_b,
     &Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_c,
     &Appl_HeatFault_CtrlModel_DW.HeatCmdDiagnoseFunction1);
  Appl_HeatFault_CtrlMo_HeatNTCDiagnoseFunction_Init
    (&Appl_HeatFault_CtrlModel_B.HeatNTCFault_b,
     &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction1);
  Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis = 0;
  Appl_HeatFault_CtrlModel_DW.is_active_c9_Appl_HeatFault_CtrlModel = 0U;
  Appl_HeatFault_CtrlModel_DW.is_c9_Appl_HeatFault_CtrlModel = 0;
  Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
  Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
  Appl_HeatFault_CtrlModel_DW.RecoverTimer = 0U;
  Appl_HeatFault_CtrlModel_B.HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
    enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlMo_HeatNTCDiagnoseFunction_Init
    (&Appl_HeatFault_CtrlModel_B.HeatNTCFault,
     &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction2);
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_HeatFault_CtrlModel_LogicCtrl(void)
{
  INT32S HeatCmdFault4DTC_tmp;
  if (Appl_HeatFault_CtrlModel_DW.is_active_c1_Appl_HeatFault_CtrlModel == 0U)
  {
    Appl_HeatFault_CtrlModel_DW.is_active_c1_Appl_HeatFault_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatFault_CtrlModel_HeatCmdAquireFunction(HeatFalut_D_SimuIndex_DRHeat,
      (INT8U)HeatFalut_MemIndexDrHeatConfig, HeatFalut_MemDiagDrHeatFlg,
      &Appl_HeatFault_CtrlModel_B.DrHeatCmd,
      &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction);
    Appl_HeatFault_CtrlModel_HeatCmdAquireFunction(HeatFalut_D_SimuIndex_PAHeat,
      HeatFalut_MemIndexPaHeatConfig, HeatFalut_MemDiagPaHeatFlg,
      &Appl_HeatFault_CtrlModel_B.PaHeatCmd,
      &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction1);
    Appl_HeatFault_CtrlModel_HeatCmdAquireFunction
      (HeatFalut_D_SimuIndex_ThirdHeat, HeatFalut_MemIndexThirdHeatConfig,
       (INT8U)((BOOL)TRUE), &Appl_HeatFault_CtrlModel_B.ThirdHeatCmd,
       &Appl_HeatFault_CtrlModel_DW.HeatCmdAquireFunction2);
  }

  if (Appl_HeatFault_CtrlModel_DW.is_active_c3_Appl_HeatFault_CtrlModel == 0U)
  {
    Appl_HeatFault_CtrlModel_DW.is_active_c3_Appl_HeatFault_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatFault_CtrlModel_HeatCmdDiagnoseFunction
      (HeatFalut_D_SimuIndex_DRHeatIo, Appl_HeatFault_CtrlModel_B.DrHeatCmd,
       HeatFalut_DrHeatIsAdc, (DOUBLE)Appl_HeatFault_CtrlModel_B.DrFaultType,
       &Appl_HeatFault_CtrlModel_B.HeatCmdFault_e,
       &Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_f,
       &Appl_HeatFault_CtrlModel_DW.HeatCmdDiagnoseFunction);
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault_e;
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts4DTC =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_f;
    Appl_HeatFault_CtrlModel_HeatNTCDiagnoseFunction(HeatFalut_DrHeatNtcAdc,
      ((INT16U)D_HEATFALUT_NtcMin), ((INT16U)D_HEATFALUT_NtcMax),
      &Appl_HeatFault_CtrlModel_B.HeatNTCFault_h,
      &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction);
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatNTCFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatNTCFault_h;
    Appl_HeatFault_CtrlModel_HeatCmdDiagnoseFunction
      (HeatFalut_D_SimuIndex_PAHeatIo, Appl_HeatFault_CtrlModel_B.PaHeatCmd,
       HeatFalut_PaHeatIsAdc, (DOUBLE)Appl_HeatFault_CtrlModel_B.PaFaultType,
       &Appl_HeatFault_CtrlModel_B.HeatCmdFault_b,
       &Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_c,
       &Appl_HeatFault_CtrlModel_DW.HeatCmdDiagnoseFunction1);
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault_b;
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts4DTC =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_c;
    Appl_HeatFault_CtrlModel_HeatNTCDiagnoseFunction(HeatFalut_PaHeatNtcAdc,
      ((INT16U)D_HEATFALUT_NtcMin), ((INT16U)D_HEATFALUT_NtcMax),
      &Appl_HeatFault_CtrlModel_B.HeatNTCFault_b,
      &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction1);
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatNTCFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatNTCFault_b;
    if (Appl_HeatFault_CtrlModel_DW.is_active_c9_Appl_HeatFault_CtrlModel == 0U)
    {
      Appl_HeatFault_CtrlModel_DW.is_active_c9_Appl_HeatFault_CtrlModel = 1U;
      Appl_HeatFault_CtrlModel_DW.is_c9_Appl_HeatFault_CtrlModel =
        Appl_HeatFault_CtrlModel_IN_HeatCmdClose_p;
      Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
      Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
      Appl_HeatFault_CtrlModel_B.HeatCmdFault =
        enHeatCmdFault_EN_HEAT_FAULT_NONE;
    }
    else if (Appl_HeatFault_CtrlModel_DW.is_c9_Appl_HeatFault_CtrlModel ==
             Appl_HeatFault_CtrlModel_IN_HeatCmdClose_p)
    {
      /*  加热CMD  */
      if (((BOOL)TRUE) == Appl_HeatFault_CtrlModel_B.ThirdHeatCmd)
      {
        HeatCmdFault4DTC_tmp = Appl_HeatFault_CtrlModel_B.ThirdFaultType;
        Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC = (enHeatCmdFault)
          Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_f
          (HeatCmdFault4DTC_tmp);
        Appl_HeatFault_CtrlModel_DW.is_c9_Appl_HeatFault_CtrlModel =
          Appl_HeatFault_CtrlModel_IN_HeatCmdDiagnosis_o;
        if (HeatCmdFault4DTC_tmp == 1)
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_CmdShortToGND_e;

          /*  未超时  */
          if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.ShortTimer)
          {
            HeatCmdFault4DTC_tmp = Appl_HeatFault_CtrlModel_DW.ShortTimer + 1;
            if (HeatCmdFault4DTC_tmp > 255)
            {
              HeatCmdFault4DTC_tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.ShortTimer = (INT8U)HeatCmdFault4DTC_tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.ShortTimer = CAL_CmdShortTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault =
              enHeatCmdFault_EN_HEAT_FAULT_GND;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_GND;
          }
        }
        else if (HeatCmdFault4DTC_tmp == 2)
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_CmdOpenLoad_g;

          /*  未超时  */
          if (CAL_CmdOpenTime > Appl_HeatFault_CtrlModel_DW.OpenTimer)
          {
            HeatCmdFault4DTC_tmp = Appl_HeatFault_CtrlModel_DW.OpenTimer + 1;
            if (HeatCmdFault4DTC_tmp > 255)
            {
              HeatCmdFault4DTC_tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.OpenTimer = (INT8U)HeatCmdFault4DTC_tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.OpenTimer = CAL_CmdOpenTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault =
              enHeatCmdFault_EN_HEAT_FAULT_OPEN;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_OPEN;
          }
        }
        else
        {
          Appl_HeatFault_CtrlModel_DW.is_HeatCmdDiagnosis =
            Appl_HeatFault_CtrlModel_IN_Default_o;
          Appl_HeatFault_CtrlModel_DW.OpenTimer = 0U;
          Appl_HeatFault_CtrlModel_DW.ShortTimer = 0U;
          Appl_HeatFault_CtrlModel_B.HeatCmdFault =
            enHeatCmdFault_EN_HEAT_FAULT_NONE;
          Appl_HeatFault_CtrlModel_DW.RecoverTimer = 0U;

          /*  未超时  */
          if (CAL_CmdShortTime > Appl_HeatFault_CtrlModel_DW.RecoverTimer)
          {
            HeatCmdFault4DTC_tmp = Appl_HeatFault_CtrlModel_DW.RecoverTimer + 1;
            if (HeatCmdFault4DTC_tmp > 255)
            {
              HeatCmdFault4DTC_tmp = 255;
            }

            Appl_HeatFault_CtrlModel_DW.RecoverTimer = (INT8U)
              HeatCmdFault4DTC_tmp;
          }
          else
          {
            Appl_HeatFault_CtrlModel_DW.RecoverTimer = CAL_CmdShortTime;
            Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
              enHeatCmdFault_EN_HEAT_FAULT_NONE;
          }
        }
      }
    }
    else
    {
      Appl_HeatFault_CtrlModel_HeatCmdDiagnosis_o
        (&HeatFalut_D_SimuIndex_ThirdHeatIo,
         &Appl_HeatFault_CtrlModel_B.ThirdHeatCmd, &HeatFalut_ThirdHeatIsAdc);
    }

    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault;
    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts4DTC =
      Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC;
    Appl_HeatFault_CtrlModel_HeatNTCDiagnoseFunction(HeatFalut_ThirdHeatNtcAdc,
      ((INT16U)D_HEATFALUT_NtcMin), ((INT16U)D_HEATFALUT_NtcMax),
      &Appl_HeatFault_CtrlModel_B.HeatNTCFault,
      &Appl_HeatFault_CtrlModel_DW.HeatNTCDiagnoseFunction2);
    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatNTCFaultSts =
      Appl_HeatFault_CtrlModel_B.HeatNTCFault;
  }
}

/* System initialize for function-call system: '<S29>/getFaultType' */
static void Appl_HeatFault_CtrlModel_getFaultType_Init(INT8U *rty_FaultType)
{
  *rty_FaultType = 0U;
}

/* Output and update for function-call system: '<S29>/getFaultType' */
static void Appl_HeatFault_CtrlModel_getFaultType(INT8U rtu_ShortGND, INT8U
  rtu_Openload, INT8U *rty_FaultType)
{
  if (((BOOL)TRUE) == rtu_ShortGND)
  {
    *rty_FaultType = (INT8U)enHeatCmdFault_EN_HEAT_FAULT_GND;
  }
  else if (((BOOL)TRUE) == rtu_Openload)
  {
    *rty_FaultType = (INT8U)enHeatCmdFault_EN_HEAT_FAULT_OPEN;
  }
  else
  {
    *rty_FaultType = (INT8U)enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_HeatFault_CtrlModel_RTE(void)
{
  HeatFalut_3rdCmdOpenload = Diag_ReadDtcTestFailFlag(D_DTC_3rdHeatOutputOp);
  HeatFalut_3rdCmdShortGND = Diag_ReadDtcTestFailFlag(D_DTC_3rdHeatOutputGS);
  HeatFalut_D_SimuIndex_DRHeat = Rte_GetVfb_DrHeat( );
  HeatFalut_D_SimuIndex_DRHeatIo = Rte_GetVfb_DrHeatIo( );
  HeatFalut_D_SimuIndex_PAHeat = Rte_GetVfb_PaHeat( );
  HeatFalut_D_SimuIndex_PAHeatIo = Rte_GetVfb_PaHeatIo( );
  HeatFalut_D_SimuIndex_ThirdHeat = Rte_GetVfb_ThirdHeat( );
  HeatFalut_D_SimuIndex_ThirdHeatIo = Rte_GetVfb_ThirdHeatIo( );
  HeatFalut_DrCmdOpenload = Diag_ReadDtcTestFailFlag(D_DTC_DrHeatOutputOp);
  HeatFalut_DrCmdShortGND = Diag_ReadDtcTestFailFlag(D_DTC_DrHeatOutputGS);
  HeatFalut_DrHeatIsAdc = Ecual_AdcGetChlStatus(enADC_DrHeaterIS);
  HeatFalut_DrHeatNtcAdc = Ecual_AdcGetChlStatus(enADC_DrHeaterNTC);
  HeatFalut_MemDiagDrHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeatFlg);
  HeatFalut_MemDiagPaHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaHeatFlg);
  HeatFalut_MemIndexDrHeatConfig = Rte_GetVfb_DrHeatEnable( );
  HeatFalut_MemIndexPaHeatConfig = Rte_GetVfb_SecondHeatEnable( );
  HeatFalut_MemIndexThirdHeatConfig = Rte_GetVfb_ThirdHeatEnable( );
  HeatFalut_PaCmdOpenload = Diag_ReadDtcTestFailFlag(D_DTC_PaHeatOutputOp);
  HeatFalut_PaCmdShortGND = Diag_ReadDtcTestFailFlag(D_DTC_PaHeatOutputGS);
  HeatFalut_PaHeatIsAdc = Ecual_AdcGetChlStatus(enADC_PaHeaterIS);
  HeatFalut_PaHeatNtcAdc = Ecual_AdcGetChlStatus(enADC_PaHeaterNTC);
  HeatFalut_ThirdHeatIsAdc = Ecual_AdcGetChlStatus(enADC_SteerHeaterIS);
  HeatFalut_ThirdHeatNtcAdc = Ecual_AdcGetChlStatus(enADC_SteerHeaterNTC);
}

static INT32S Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_j(INT32S input)
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
static void Appl_HeatFault_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U FaultType_e;
  Appl_HeatFault_CtrlModel_DW.is_active_c15_Appl_HeatFault_CtrlModel = 0U;
  Appl_HeatFault_CtrlModel_B.DrFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.PaFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_B.ThirdFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  Appl_HeatFault_CtrlModel_getFaultType_Init(&FaultType_e);
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_HeatFault_CtrlModel_UpDataInputInfo(void)
{
  INT8U FaultType_e;
  Appl_HeatFault_CtrlModel_RTE();
  if (Appl_HeatFault_CtrlModel_DW.is_active_c15_Appl_HeatFault_CtrlModel == 0U)
  {
    Appl_HeatFault_CtrlModel_DW.is_active_c15_Appl_HeatFault_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatFault_CtrlModel_getFaultType(HeatFalut_DrCmdShortGND,
      HeatFalut_DrCmdOpenload, &FaultType_e);
    Appl_HeatFault_CtrlModel_B.DrFaultType = (enHeatCmdFault)
      Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_j(FaultType_e);
    Appl_HeatFault_CtrlModel_getFaultType(HeatFalut_PaCmdShortGND,
      HeatFalut_PaCmdOpenload, &FaultType_e);
    Appl_HeatFault_CtrlModel_B.PaFaultType = (enHeatCmdFault)
      Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_j(FaultType_e);
    Appl_HeatFault_CtrlModel_getFaultType(HeatFalut_3rdCmdShortGND,
      HeatFalut_3rdCmdOpenload, &FaultType_e);
    Appl_HeatFault_CtrlModel_B.ThirdFaultType = (enHeatCmdFault)
      Appl_HeatFault_CtrlM_safe_cast_to_enHeatCmdFault_j(FaultType_e);
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_HeatFault_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_DrHeatCmdFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts);
  Rte_SetVfb_DrHeatCmdFaultSts4DTC
    (Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts4DTC);
  Rte_SetVfb_DrHeatNTCFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatNTCFaultSts);
  Rte_SetVfb_PaHeatCmdFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts);
  Rte_SetVfb_PaHeatCmdFaultSts4DTC
    (Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts4DTC);
  Rte_SetVfb_PaHeatNTCFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatNTCFaultSts);
  Rte_SetVfb_ThirdHeatCmdFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts);
  Rte_SetVfb_ThirdHeatCmdFaultSts4DTC
    (Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts4DTC);
  Rte_SetVfb_ThirdHeatNTCFaultSts
    (Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatNTCFaultSts);
}

/* Model step function */
void Appl_HeatFault_CtrlModel_step(void)
{
  Appl_HeatFault_CtrlModel_UpDataInputInfo();
  Appl_HeatFault_CtrlModel_LogicCtrl();
  Appl_HeatFault_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_HeatFault_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_HeatFault_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_HeatFault_CtrlModel_B), 0,
                sizeof(B_Appl_HeatFault_CtrlModel_T));

  {
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatNTCFaultSts =
      enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatNTCFaultSts =
      enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatNTCFaultSts =
      enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatNTCFault = enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatNTCFault_b = enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatNTCFault_h = enHeatNtcFault_EN_NTC_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.DrFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.PaFaultType = enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.ThirdFaultType =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_DRHeatCmdFaultSts4DTC =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_PAHeatCmdFaultSts4DTC =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatFault_ThirdHeatCmdFaultSts4DTC =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault = enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault_b =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_c =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault_e =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
    Appl_HeatFault_CtrlModel_B.HeatCmdFault4DTC_f =
      enHeatCmdFault_EN_HEAT_FAULT_NONE;
  }

  /* exported global signals */
  HeatFalut_D_SimuIndex_DRHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatFalut_D_SimuIndex_PAHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatFalut_D_SimuIndex_ThirdHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatFalut_D_SimuIndex_DRHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  HeatFalut_D_SimuIndex_PAHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  HeatFalut_D_SimuIndex_ThirdHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  HeatFalut_MemIndexDrHeatConfig = enHeatIoSts_EN_HEAT_IO_LOW;
  HeatFalut_DrHeatIsAdc = ((INT16U)0U);
  HeatFalut_DrHeatNtcAdc = ((INT16U)0U);
  HeatFalut_PaHeatIsAdc = ((INT16U)0U);
  HeatFalut_PaHeatNtcAdc = ((INT16U)0U);
  HeatFalut_ThirdHeatIsAdc = ((INT16U)0U);
  HeatFalut_ThirdHeatNtcAdc = ((INT16U)0U);
  HeatFalut_3rdCmdOpenload = ((INT8U)0U);
  HeatFalut_3rdCmdShortGND = ((INT8U)0U);
  HeatFalut_DrCmdOpenload = ((INT8U)0U);
  HeatFalut_DrCmdShortGND = ((INT8U)0U);
  HeatFalut_MemDiagDrHeatFlg = ((INT8U)0U);
  HeatFalut_MemDiagPaHeatFlg = ((INT8U)0U);
  HeatFalut_MemIndexPaHeatConfig = ((INT8U)0U);
  HeatFalut_MemIndexThirdHeatConfig = ((INT8U)0U);
  HeatFalut_PaCmdOpenload = ((INT8U)0U);
  HeatFalut_PaCmdShortGND = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_HeatFault_CtrlModel_DW, 0,
                sizeof(DW_Appl_HeatFault_CtrlModel_T));
  Appl_HeatFault_CtrlModel_UpDataInputInfo_Init();
  Appl_HeatFault_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
