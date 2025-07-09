/*
 * File: Appl_MassageMode_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_MassageMode_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:48:18 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_MassageMode_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_T3
#error The variable for the parameter "D_T3" is not defined
#endif

#ifndef D_T4
#error The variable for the parameter "D_T4" is not defined
#endif

#ifndef D_T1
#error The variable for the parameter "D_T1" is not defined
#endif

#ifndef D_T2
#error The variable for the parameter "D_T2" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_ActMax
#error The variable for the parameter "D_ActMax" is not defined
#endif

/* Named constants for Chart: '<S5>/MassageLogicDeal' */
#define Appl_MassageMode_CtrlModel_IN_MassageActive ((INT8U)1U)
#define Appl_MassageMode_CtrlModel_IN_MassageClose ((INT8U)1U)
#define Appl_MassageMode_CtrlModel_IN_MassageHaveFault ((INT8U)1U)
#define Appl_MassageMode_CtrlModel_IN_MassageInactive ((INT8U)2U)
#define Appl_MassageMode_CtrlModel_IN_MassageNoneFault ((INT8U)2U)
#define Appl_MassageMode_CtrlModel_IN_MassageOpen ((INT8U)2U)
#define Appl_MassageMode_CtrlModel_IN_MassageTimeout ((INT8U)3U)

/* Named constants for Chart: '<S17>/MassagePreconditionDeal' */
#define Appl_MassageMode_CtrlModel_IN_FALSE ((INT8U)1U)
#define Appl_MassageMode_CtrlModel_IN_Init ((INT8U)2U)
#define Appl_MassageMode_CtrlModel_IN_NO_ACTIVE_CHILD_c ((INT8U)0U)
#define Appl_MassageMode_CtrlModel_IN_TRUE ((INT8U)3U)

/* Exported block signals */
enVehTypePrm Mas_VehiclePrm;           /* '<S15>/Mas_VehiclePrm'
                                        * 车型配置
                                        */
enPowerModeSts Mas_PowerMode;          /* '<S15>/Mas_PowerMode'
                                        * 整车电源档位
                                        */
enMassageMode_IVI Mas_IVI_MassageMode_Req;/* '<S15>/Mas_IVI_MassageMode_Req'
                                           * 大屏的按摩按式请求&#10;0x0：Inactive&#10;0x1: 猫步、全身放松&#10;0x2: 波浪形、全身激活&#10;0x3：伸展形、肩部激活&#10;0x4: 腰部、肩部放松&#10;0x5：肩部、腰部激活&#10;0x6：蛇形、腰部放松&#10;0x7：单排、背部激活&#10;0x8：蝶形、背部放松&#10;0x9-0x14：Reserved
                                           */
enMassageMode_DSM Mas_Massage_ModeSts_FB;/* '<S15>/Mas_Massage_ModeSts_FB'
                                          * 按摩模式反馈-LIN&#10;0x0: 全身放松&#10;0x1: 全身激活&#10;0x2：肩部激活&#10;0x3: 肩部放松&#10;0x4：腰部激活&#10;0x5：腰部放松&#10;0x6：背部激活&#10;0x7：背部放松&#10;0x8：Error模块故障&#10;0x9~0xE：Reserved
                                          */
enMassageMode_DSM Mas_Res_MassageMode_Req;/* '<S15>/Mas_Res_MassageMode_Req'
                                           * 小憩的按摩模式请求
                                           */
enMassageMode_DSM Mas_SeatMassageMode; /* '<S15>/Mas_SeatMassageMode'
                                        * 按摩模式反馈：&#10; 0x0: 全身放松&#10; 0x1: 全身激活&#10; 0x2：肩部激活&#10; 0x3: 肩部放松&#10; 0x4：腰部激活&#10; 0x5：腰部放松&#10; 0x6：背部激活&#10; 0x7：背部放松&#10; 0x8：Error模块故障
                                        */
enMassageLevel_IVI Mas_IVI_MassageLevel_Req;/* '<S15>/Mas_IVI_MassageLevel_Req'
                                             * 大屏的按摩档位请求&#10;0x0:Inactive&#10;0x1: Level 1&#10;0x2: Level 2&#10;0x3: Level 3&#10;0x4: OFF
                                             */
enMassageLevel_DSM Mas_Massage_LevelSts_FB;/* '<S15>/Mas_Massage_LevelSts_FB'
                                            * 按摩模块的档位反馈-LIN&#10;0x0:OFF&#10;0x1: Level 1&#10;0x2: Level 2&#10;0x3: Level 3&#10;0x4: AUTO  OFF自动关闭
                                            */
enMassageLevel_DSM Mas_Res_MassageLevel_Req;/* '<S15>/Mas_Res_MassageLevel_Req'
                                             * 小憩的按摩档位请求
                                             */
enFinalPowerMode Mas_VoltMode;         /* '<S15>/Mas_VoltMode'
                                        * 整车电压模式&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
INT16U Mas_DiagTimeT1;                 /* '<S15>/Mas_DiagTimeT1'
                                        * T1阈值
                                        */
INT16U Mas_DiagTimeT2;                 /* '<S15>/Mas_DiagTimeT2'
                                        * T2阈值
                                        */
INT16U Mas_DiagTimeT3;                 /* '<S15>/Mas_DiagTimeT3'
                                        * T3阈值
                                        */
INT16U Mas_DiagTimeT4;                 /* '<S15>/Mas_DiagTimeT4'
                                        * T4阈值
                                        */
INT8U Mas_EngineRunFlag;               /* '<S15>/Mas_EngineRunFlag'
                                        * 发动机运行状态&#10;0：无效&#10;1：有效
                                        */
INT8U Mas_IVI_NapMode_SwtichSet;       /* '<S15>/Mas_IVI_NapMode_SwtichSet'
                                        * 憩模式键按下设定&#10;0x0:Inactive&#10;0x1:打开小憩模式&#10;0x2:关闭小憩模式&#10;0x3:Reserved
                                        */
INT8U Mas_Massage_0x1B_LostFlag;       /* '<S15>/Mas_Massage_0x1B_LostFlag'
                                        * LIN丢失标志位
                                        */
INT8U Mas_RecoverDefaultFlag;          /* '<S15>/Mas_RecoverDefaultFlag'
                                        * 恢复出厂命令&#10;0：无效；&#10;1：有效
                                        */
INT8U Mas_SeatMassageCfg;              /* '<S15>/Mas_SeatMassageCfg'
                                        *  按摩功能配置使能标志位
                                        */
INT8U Mas_VehicleRunFlag;              /* '<S15>/Mas_VehicleRunFlag'
                                        * 整车运行状态&#10;0：无效&#10;1：有效
                                        */

/* Block signals (default storage) */
B_Appl_MassageMode_CtrlModel_T Appl_MassageMode_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_MassageMode_CtrlModel_T Appl_MassageMode_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_MassageMode_CtrlModel_T Appl_MassageMode_CtrlModel_M_;
RT_MODEL_Appl_MassageMode_CtrlModel_T *const Appl_MassageMode_CtrlModel_M =
  &Appl_MassageMode_CtrlModel_M_;
static void Appl_MassageMode_CtrlModel_SaveMassageMode(void);
static void Appl_MassageMode_CtrlModel_SaveMassageMode_a(void);
static void Appl_MassageMode_CtrlModel_LogicCtrl_Init(void);
static void Appl_MassageMode_CtrlModel_LogicCtrl(void);
static void Appl_MassageMode_CtrlModel_SaveMassageMode_a1(void);
static void Appl_MassageMode_CtrlModel_RTE(void);
static void Appl_MassageMode_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_MassageMode_CtrlModel_UpDataInputInfo(void);
static void Appl_MassageMode_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static INT32S Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(INT32S input);
static INT32S Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM(INT32S input);
static void Appl_MassageMode_inner_default_MassageStopCount_T2(const
  enMassageLevel_IVI *Mas_IVI_MassageLevel_Req_prev);
static void Appl_MassageMode_CtrlM_enter_internal_MassageClose(const
  enMassageLevel_IVI *Mas_IVI_MassageLevel_Req_prev);
static void Appl_MassageMode_Ctrl_enter_atomic_MassageInactive(void);

/* Output and update for function-call system: '<S10>/SaveMassageMode' */
static void Appl_MassageMode_CtrlModel_SaveMassageMode(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_MassageMode,
    Appl_MassageMode_CtrlModel_B.Mode_d);
}

/* Output and update for function-call system: '<S7>/SaveMassageMode' */
static void Appl_MassageMode_CtrlModel_SaveMassageMode_a(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_MassageMode,
    Appl_MassageMode_CtrlModel_B.Mode_l);
}

static INT32S Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enMassageMode_DSM (EN_M1) */
  y = 0;
  if ((input >= 0) && (input <= 8))
  {
    /* Set output value to input value if it is a member of enMassageMode_DSM */
    y = input;
  }

  return y;
}

static INT32S Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enMassageLevel_DSM (EN_OFF) */
  y = 0;
  if ((input >= 0) && (input <= 5))
  {
    /* Set output value to input value if it is a member of enMassageLevel_DSM */
    y = input;
  }

  return y;
}

/* Function for Chart: '<S5>/MassageLogicDeal' */
static void Appl_MassageMode_inner_default_MassageStopCount_T2(const
  enMassageLevel_IVI *Mas_IVI_MassageLevel_Req_prev)
{
  INT32S tmp;
  BOOL guard1 = false;

  /* 超时关闭次数是否到阈值 */
  if ((Appl_MassageMode_CtrlModel_B.AcTCount < ((INT8U)D_ActMax)) &&
      (Appl_MassageMode_CtrlModel_B.T4timer < Appl_MassageMode_CtrlModel_B.T4Max))
  {
    /* T4计时是否到阈值 */
    guard1 = false;
    if (Appl_MassageMode_CtrlModel_DW.AutoOffFlag == ((BOOL)FALSE))
    {
      guard1 = true;
    }
    else if (Appl_MassageMode_CtrlModel_DW.Timer_TutoOff >= 20)
    {
      if (((*Mas_IVI_MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start ==
            enMassageLevel_IVI_EN_L1)) || ((*Mas_IVI_MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start ==
            enMassageLevel_IVI_EN_L2)) || ((*Mas_IVI_MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start ==
            enMassageLevel_IVI_EN_L3)))
      {
        guard1 = true;
      }
      else
      {
        /*  自动关闭后模式转发的处理 -与正常转发逻辑保持一致 */
        if ((Mas_Massage_ModeSts_FB <= enMassageMode_DSM_EN_MError) &&
            (Appl_MassageMode_CtrlModel_B.Switch !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_B.Switch != enMassageLevel_DSM_EN_OFF) &&
            (Mas_Massage_0x1B_LostFlag != ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
            Mas_Massage_ModeSts_FB;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_SeatMassageMode;
        }
      }
    }
    else
    {
      tmp = Appl_MassageMode_CtrlModel_DW.Timer_TutoOff + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      Appl_MassageMode_CtrlModel_DW.Timer_TutoOff = (INT8U)tmp;

      /* A2档位AutoOFF，模式保持 */
      Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
        enMassageLevel_DSM_EN_AUTO_OFF;
      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
        enMassageLevel_DSM_EN_AUTO_OFF;
    }

    if (guard1)
    {
      Appl_MassageMode_CtrlModel_B.T2timer = 0U;

      /* A3正常转发 */
      Appl_MassageMode_CtrlModel_B.IVILevel = Mas_IVI_MassageLevel_Req;
      Appl_MassageMode_CtrlModel_B.IVIMode = (enMassageMode_DSM)
        Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
        (Mas_IVI_MassageMode_Req);
      Appl_MassageMode_CtrlModel_B.MassageLevel =
        Appl_MassageMode_CtrlModel_B.Switch;
      Appl_MassageMode_CtrlModel_B.MassageMode = Mas_Massage_ModeSts_FB;
      Appl_MassageMode_CtrlModel_B.LostFlag = Mas_Massage_0x1B_LostFlag;
      Appl_MassageMode_CtrlModel_B.ModeEEPROM = Mas_SeatMassageMode;
      if (Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel ==
          0U)
      {
        Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel =
          1U;

        /* 是否为IVI关闭指令 */
        if (Appl_MassageMode_CtrlModel_B.IVILevel == enMassageLevel_IVI_EN_OFF)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
        }
        else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L1) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L2) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L3))
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
            Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
            (Appl_MassageMode_CtrlModel_B.IVILevel);
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq =
            enMassageLevel_DSM_EN_Inactive;
        }

        /* 是否为Massage节点有效指令 */
        if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
            enMassageLevel_DSM_EN_L3)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
          Appl_MassageMode_CtrlModel_DW.LevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
        }

        /* 是否为IVI有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.IVIMode <= enMassageMode_IVI_EN_M8) &&
            (Appl_MassageMode_CtrlModel_B.IVIMode !=
             enMassageMode_IVI_EN_Inactive) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF))
        {
          if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(MIN_int32_T);
          }
          else
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
              Appl_MassageMode_CtrlModel_B.IVIMode - 1);
          }

          Appl_MassageMode_CtrlModel_B.Mode_d =
            Appl_MassageMode_CtrlModel_B.DSMModeReq;
          Appl_MassageMode_CtrlModel_SaveMassageMode();
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeReq =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }

        /* Massage节点有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
             enMassageMode_DSM_EN_MError) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF)
            && (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.MassageMode;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }
      }
      else
      {
        /* 是否为IVI关闭指令 */
        if (Appl_MassageMode_CtrlModel_B.IVILevel == enMassageLevel_IVI_EN_OFF)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
        }
        else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L1) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L2) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L3))
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
            Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
            (Appl_MassageMode_CtrlModel_B.IVILevel);
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq =
            enMassageLevel_DSM_EN_Inactive;
        }

        /* 是否为Massage节点有效指令 */
        if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
            enMassageLevel_DSM_EN_L3)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
          Appl_MassageMode_CtrlModel_DW.LevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
        }

        /* 是否为IVI有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.IVIMode <= enMassageMode_IVI_EN_M8) &&
            (Appl_MassageMode_CtrlModel_B.IVIMode !=
             enMassageMode_IVI_EN_Inactive) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF))
        {
          if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(MIN_int32_T);
          }
          else
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
              Appl_MassageMode_CtrlModel_B.IVIMode - 1);
          }

          Appl_MassageMode_CtrlModel_B.Mode_d =
            Appl_MassageMode_CtrlModel_B.DSMModeReq;
          Appl_MassageMode_CtrlModel_SaveMassageMode();
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeReq =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }

        /* Massage节点有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
             enMassageMode_DSM_EN_MError) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF)
            && (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.MassageMode;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }
      }

      Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
        Appl_MassageMode_CtrlModel_B.DSMLevelReq;
      Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)
        Appl_MassageMode_CtrlModel_B.DSMModeReq;
      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
        Appl_MassageMode_CtrlModel_B.DSMLevelFB;
      Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
        Appl_MassageMode_CtrlModel_B.DSMModeFB;
    }
  }
  else
  {
    /* T2计时是否到阈值 */
    if (Appl_MassageMode_CtrlModel_B.T2timer <
        Appl_MassageMode_CtrlModel_B.T2Max)
    {
      tmp = Appl_MassageMode_CtrlModel_B.T2timer + 1;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_MassageMode_CtrlModel_B.T2timer = (INT16U)tmp;
      Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
        enMassageLevel_DSM_EN_AUTO_OFF;
      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
        enMassageLevel_DSM_EN_AUTO_OFF;
    }
    else
    {
      /* A1，T2保持，其余清除；报文正常转发 */
      Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
      Appl_MassageMode_CtrlModel_B.T2timer = 0U;
      Appl_MassageMode_CtrlModel_B.T3timer = 0U;
      Appl_MassageMode_CtrlModel_B.T4timer = 0U;
      Appl_MassageMode_CtrlModel_B.AcTCount = 0U;
      Appl_MassageMode_CtrlModel_B.IVILevel = Mas_IVI_MassageLevel_Req;
      Appl_MassageMode_CtrlModel_B.IVIMode = (enMassageMode_DSM)
        Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
        (Mas_IVI_MassageMode_Req);
      Appl_MassageMode_CtrlModel_B.MassageLevel =
        Appl_MassageMode_CtrlModel_B.Switch;
      Appl_MassageMode_CtrlModel_B.MassageMode = Mas_Massage_ModeSts_FB;
      Appl_MassageMode_CtrlModel_B.LostFlag = Mas_Massage_0x1B_LostFlag;
      Appl_MassageMode_CtrlModel_B.ModeEEPROM = Mas_SeatMassageMode;
      if (Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel ==
          0U)
      {
        Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel =
          1U;

        /* 是否为IVI关闭指令 */
        if (Appl_MassageMode_CtrlModel_B.IVILevel == enMassageLevel_IVI_EN_OFF)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
        }
        else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L1) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L2) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L3))
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
            Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
            (Appl_MassageMode_CtrlModel_B.IVILevel);
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq =
            enMassageLevel_DSM_EN_Inactive;
        }

        /* 是否为Massage节点有效指令 */
        if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
            enMassageLevel_DSM_EN_L3)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
          Appl_MassageMode_CtrlModel_DW.LevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
        }

        /* 是否为IVI有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.IVIMode <= enMassageMode_IVI_EN_M8) &&
            (Appl_MassageMode_CtrlModel_B.IVIMode !=
             enMassageMode_IVI_EN_Inactive) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF))
        {
          if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(MIN_int32_T);
          }
          else
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
              Appl_MassageMode_CtrlModel_B.IVIMode - 1);
          }

          Appl_MassageMode_CtrlModel_B.Mode_d =
            Appl_MassageMode_CtrlModel_B.DSMModeReq;
          Appl_MassageMode_CtrlModel_SaveMassageMode();
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeReq =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }

        /* Massage节点有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
             enMassageMode_DSM_EN_MError) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF)
            && (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.MassageMode;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }
      }
      else
      {
        /* 是否为IVI关闭指令 */
        if (Appl_MassageMode_CtrlModel_B.IVILevel == enMassageLevel_IVI_EN_OFF)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
        }
        else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L1) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L2) ||
                 (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_L3))
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
            Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
            (Appl_MassageMode_CtrlModel_B.IVILevel);
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelReq =
            enMassageLevel_DSM_EN_Inactive;
        }

        /* 是否为Massage节点有效指令 */
        if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
            enMassageLevel_DSM_EN_L3)
        {
          Appl_MassageMode_CtrlModel_B.DSMLevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
          Appl_MassageMode_CtrlModel_DW.LevelFB =
            Appl_MassageMode_CtrlModel_B.MassageLevel;
        }

        /* 是否为IVI有效指令&&按摩档位已打开 */
        tmp = Appl_MassageMode_CtrlModel_B.IVIMode;
        if ((tmp <= (INT32S)enMassageMode_IVI_EN_M8) && (tmp != (INT32S)
             enMassageMode_IVI_EN_Inactive) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF))
        {
          if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM(MIN_int32_T);
          }
          else
          {
            Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
              Appl_MassageMode_CtrlModel_B.IVIMode - 1);
          }

          Appl_MassageMode_CtrlModel_B.Mode_d =
            Appl_MassageMode_CtrlModel_B.DSMModeReq;
          Appl_MassageMode_CtrlModel_SaveMassageMode();
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeReq =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }

        /* Massage节点有效指令&&按摩档位已打开 */
        if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
             enMassageMode_DSM_EN_MError) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB !=
             enMassageLevel_DSM_EN_AUTO_OFF) &&
            (Appl_MassageMode_CtrlModel_DW.LevelFB != enMassageLevel_DSM_EN_OFF)
            && (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.MassageMode;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSMModeFB =
            Appl_MassageMode_CtrlModel_B.ModeEEPROM;
        }
      }

      Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
        Appl_MassageMode_CtrlModel_B.DSMLevelReq;
      Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)
        Appl_MassageMode_CtrlModel_B.DSMModeReq;
      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
        Appl_MassageMode_CtrlModel_B.DSMLevelFB;
      Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
        Appl_MassageMode_CtrlModel_B.DSMModeFB;
    }
  }
}

/* Function for Chart: '<S5>/MassageLogicDeal' */
static void Appl_MassageMode_CtrlM_enter_internal_MassageClose(const
  enMassageLevel_IVI *Mas_IVI_MassageLevel_Req_prev)
{
  INT32S tmp;
  INT32U tmp_0;
  Appl_MassageMode_inner_default_MassageStopCount_T2
    (Mas_IVI_MassageLevel_Req_prev);

  /* 是否由按摩开启状态进入 */
  if (Appl_MassageMode_CtrlModel_DW.MassageOpenFlag == ((BOOL)TRUE))
  {
    /* T1计时是否已到阈值 */
    if (Appl_MassageMode_CtrlModel_B.T1timer <
        Appl_MassageMode_CtrlModel_B.T1Max)
    {
      tmp = Appl_MassageMode_CtrlModel_B.T1timer + 1;
      if (tmp > 65535)
      {
        tmp = 65535;
      }

      Appl_MassageMode_CtrlModel_B.T1timer = (INT16U)tmp;
    }
    else
    {
      tmp_0 = Appl_MassageMode_CtrlModel_B.T1Max;
      if (Appl_MassageMode_CtrlModel_B.T1Max > 65535U)
      {
        tmp_0 = 65535U;
      }

      Appl_MassageMode_CtrlModel_B.T1timer = (INT16U)tmp_0;

      /* T2没有启动计时，避免T1计时到阈值后T2停止计时mantis：7343 */
      if (0 == Appl_MassageMode_CtrlModel_B.T2timer)
      {
        Appl_MassageMode_CtrlModel_B.T3timer = 0U;
        Appl_MassageMode_CtrlModel_B.T4timer = 0U;
        Appl_MassageMode_CtrlModel_B.AcTCount = 0U;
      }
    }
  }
}

/* Function for Chart: '<S5>/MassageLogicDeal' */
static void Appl_MassageMode_Ctrl_enter_atomic_MassageInactive(void)
{
  Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)FALSE);
  Appl_MassageMode_CtrlModel_DW.ExitFlag = ((BOOL)FALSE);
  Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
  Appl_MassageMode_CtrlModel_B.T1timer = 0U;
  Appl_MassageMode_CtrlModel_B.T2timer = 0U;
  Appl_MassageMode_CtrlModel_B.T3timer = 0U;
  Appl_MassageMode_CtrlModel_B.T4timer = 0U;
  Appl_MassageMode_CtrlModel_B.AcTCount = 0U;
  Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
    enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)Mas_SeatMassageMode;
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_MassageMode_CtrlModel_LogicCtrl_Init(void)
{
  Appl_MassageMode_CtrlModel_DW.is_MassageActive = 0;
  Appl_MassageMode_CtrlModel_DW.is_MassageInactive = 0;
  Appl_MassageMode_CtrlModel_DW.is_active_c8_Appl_MassageMode_CtrlModel = 0U;
  Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel = 0;
  Appl_MassageMode_CtrlModel_DW.AutoOffFlag = 0U;
  Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = 0U;
  Appl_MassageMode_CtrlModel_DW.ExitFlag = 0U;
  Appl_MassageMode_CtrlModel_DW.Timer_TutoOff = 0U;
  Appl_MassageMode_CtrlModel_B.MassageLevel_Req = 0U;
  Appl_MassageMode_CtrlModel_B.MassageMode_Req = 0U;
  Appl_MassageMode_CtrlModel_B.T2timer = 0U;
  Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = enMassageMode_DSM_EN_M1;
  Appl_MassageMode_CtrlModel_B.T1timer = 0U;
  Appl_MassageMode_CtrlModel_B.T3timer = 0U;
  Appl_MassageMode_CtrlModel_B.T4timer = 0U;
  Appl_MassageMode_CtrlModel_B.AcTCount = 0U;
  Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel = 0U;
  Appl_MassageMode_CtrlModel_DW.LevelFB = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.DSMModeFB = enMassageMode_DSM_EN_M1;
  Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.DSMModeReq = enMassageMode_DSM_EN_M1;
  Appl_MassageMode_CtrlModel_B.DSMLevelFB = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_DW.is_active_c6_Appl_MassageMode_CtrlModel = 0U;
  Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req = enMassageLevel_DSM_EN_OFF;
  Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req = enMassageMode_DSM_EN_M1;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_MassageMode_CtrlModel_LogicCtrl(void)
{
  enMassageLevel_IVI Mas_IVI_MassageLevel_Req_prev;
  enMassageLevel_DSM Mas_Massage_LevelSts_FB_prev;
  INT8U MassageLevel_Req_prev;
  INT8U MassageMode_Req_prev;
  INT32S tmp;
  INT32U qY;
  Appl_MassageMode_CtrlModel_B.MassagePCStopReason_l =
    Appl_MassageMode_CtrlModel_B.MassagePCStopReason;
  Mas_IVI_MassageLevel_Req_prev =
    Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start;
  Appl_MassageMode_CtrlModel_DW.Mas_IVI_MassageLevel_Req_start =
    Mas_IVI_MassageLevel_Req;
  Mas_Massage_LevelSts_FB_prev =
    Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start;
  Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start =
    Appl_MassageMode_CtrlModel_B.Switch;
  if (Appl_MassageMode_CtrlModel_DW.is_active_c8_Appl_MassageMode_CtrlModel ==
      0U)
  {
    Appl_MassageMode_CtrlModel_DW.is_active_c8_Appl_MassageMode_CtrlModel = 1U;
    Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel =
      Appl_MassageMode_CtrlModel_IN_MassageInactive;
    Appl_MassageMode_Ctrl_enter_atomic_MassageInactive();
    Appl_MassageMode_CtrlModel_DW.is_MassageInactive =
      Appl_MassageMode_CtrlModel_IN_MassageNoneFault;
    Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_SeatMassageMode;
  }
  else if (Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel ==
           Appl_MassageMode_CtrlModel_IN_MassageActive)
  {
    /* Massage_ModeSts_FB ==
       0x8:enMassageError */
    if (Mas_Massage_ModeSts_FB == enMassageMode_DSM_EN_MError)
    {
      if (Appl_MassageMode_CtrlModel_DW.is_MassageActive ==
          Appl_MassageMode_CtrlModel_IN_MassageOpen)
      {
        Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)TRUE);
        Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
        Appl_MassageMode_CtrlModel_DW.is_MassageActive = 0;
      }
      else
      {
        Appl_MassageMode_CtrlModel_DW.is_MassageActive = 0;
      }

      Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel =
        Appl_MassageMode_CtrlModel_IN_MassageInactive;
      Appl_MassageMode_Ctrl_enter_atomic_MassageInactive();
      Appl_MassageMode_CtrlModel_DW.is_MassageInactive =
        Appl_MassageMode_CtrlModel_IN_MassageHaveFault;
      Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_Massage_ModeSts_FB;
    }
    else
    {
      /* 不满足CC1 */
      if (Appl_MassageMode_CtrlModel_B.MassagePC_Flag != ((BOOL)TRUE))
      {
        if (Appl_MassageMode_CtrlModel_DW.is_MassageActive ==
            Appl_MassageMode_CtrlModel_IN_MassageOpen)
        {
          Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)TRUE);
          Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
          Appl_MassageMode_CtrlModel_DW.is_MassageActive = 0;
        }
        else
        {
          Appl_MassageMode_CtrlModel_DW.is_MassageActive = 0;
        }

        Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel =
          Appl_MassageMode_CtrlModel_IN_MassageInactive;
        Appl_MassageMode_Ctrl_enter_atomic_MassageInactive();
        Appl_MassageMode_CtrlModel_DW.is_MassageInactive =
          Appl_MassageMode_CtrlModel_IN_MassageNoneFault;
        Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_SeatMassageMode;
      }
      else
      {
        switch (Appl_MassageMode_CtrlModel_DW.is_MassageActive)
        {
         case Appl_MassageMode_CtrlModel_IN_MassageClose:
          /* C1 && C4 */
          if ((((Mas_Massage_LevelSts_FB_prev !=
                 Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start) &&
                (Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start ==
                 enMassageLevel_DSM_EN_L1)) || ((Mas_Massage_LevelSts_FB_prev !=
                 Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start) &&
                (Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start ==
                 enMassageLevel_DSM_EN_L2)) || ((Mas_Massage_LevelSts_FB_prev !=
                 Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start) &&
                (Appl_MassageMode_CtrlModel_DW.Mas_Massage_LevelSts_FB_start ==
                 enMassageLevel_DSM_EN_L3))) &&
              ((Appl_MassageMode_CtrlModel_B.T2timer >=
                Appl_MassageMode_CtrlModel_B.T2Max) ||
               (Appl_MassageMode_CtrlModel_B.T2timer == 0)))
          {
            Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)FALSE);
            Appl_MassageMode_CtrlModel_B.T2timer = 0U;
            Appl_MassageMode_CtrlModel_DW.Timer_TutoOff = 0U;
            Appl_MassageMode_CtrlModel_DW.is_MassageActive =
              Appl_MassageMode_CtrlModel_IN_MassageOpen;
            qY = Appl_MassageMode_CtrlModel_B.T3timer + 1U;
            if (qY < Appl_MassageMode_CtrlModel_B.T3timer)
            {
              qY = MAX_uint32_T;
            }

            Appl_MassageMode_CtrlModel_B.T3timer = qY;
            qY = Appl_MassageMode_CtrlModel_B.T4timer + 1U;
            if (qY < Appl_MassageMode_CtrlModel_B.T4timer)
            {
              qY = MAX_uint32_T;
            }

            Appl_MassageMode_CtrlModel_B.T4timer = qY;

            /* A3正常转发 */
            Appl_MassageMode_CtrlModel_B.IVILevel = Mas_IVI_MassageLevel_Req;
            Appl_MassageMode_CtrlModel_B.IVIMode = (enMassageMode_DSM)
              Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
              (Mas_IVI_MassageMode_Req);
            Appl_MassageMode_CtrlModel_B.MassageLevel =
              Appl_MassageMode_CtrlModel_B.Switch;
            Appl_MassageMode_CtrlModel_B.MassageMode = Mas_Massage_ModeSts_FB;
            Appl_MassageMode_CtrlModel_B.LostFlag = Mas_Massage_0x1B_LostFlag;
            Appl_MassageMode_CtrlModel_B.ModeEEPROM = Mas_SeatMassageMode;
            if (Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel
                == 0U)
            {
              Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel
                = 1U;

              /* 是否为IVI关闭指令 */
              if (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_OFF)
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                  enMassageLevel_DSM_EN_OFF;
              }
              else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L1) ||
                       (Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L2) ||
                       (Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L3))
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
                  Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
                  (Appl_MassageMode_CtrlModel_B.IVILevel);
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                  enMassageLevel_DSM_EN_Inactive;
              }

              /* 是否为Massage节点有效指令 */
              if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
                  enMassageLevel_DSM_EN_L3)
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelFB =
                  Appl_MassageMode_CtrlModel_B.MassageLevel;
                Appl_MassageMode_CtrlModel_DW.LevelFB =
                  Appl_MassageMode_CtrlModel_B.MassageLevel;
              }

              /* 是否为IVI有效指令&&按摩档位已打开 */
              if ((Appl_MassageMode_CtrlModel_B.IVIMode <=
                   enMassageMode_IVI_EN_M8) &&
                  (Appl_MassageMode_CtrlModel_B.IVIMode !=
                   enMassageMode_IVI_EN_Inactive) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_AUTO_OFF) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_OFF))
              {
                if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                    Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
                    (MIN_int32_T);
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                    Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
                    Appl_MassageMode_CtrlModel_B.IVIMode - 1);
                }

                Appl_MassageMode_CtrlModel_B.Mode_d =
                  Appl_MassageMode_CtrlModel_B.DSMModeReq;
                Appl_MassageMode_CtrlModel_SaveMassageMode();
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMModeReq =
                  Appl_MassageMode_CtrlModel_B.ModeEEPROM;
              }

              /* Massage节点有效指令&&按摩档位已打开 */
              if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
                   enMassageMode_DSM_EN_MError) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_AUTO_OFF) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_OFF) &&
                  (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
              {
                Appl_MassageMode_CtrlModel_B.DSMModeFB =
                  Appl_MassageMode_CtrlModel_B.MassageMode;
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMModeFB =
                  Appl_MassageMode_CtrlModel_B.ModeEEPROM;
              }
            }
            else
            {
              /* 是否为IVI关闭指令 */
              if (Appl_MassageMode_CtrlModel_B.IVILevel ==
                  enMassageLevel_IVI_EN_OFF)
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                  enMassageLevel_DSM_EN_OFF;
              }
              else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L1) ||
                       (Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L2) ||
                       (Appl_MassageMode_CtrlModel_B.IVILevel ==
                        enMassageLevel_IVI_EN_L3))
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
                  Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
                  (Appl_MassageMode_CtrlModel_B.IVILevel);
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                  enMassageLevel_DSM_EN_Inactive;
              }

              /* 是否为Massage节点有效指令 */
              if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
                  enMassageLevel_DSM_EN_L3)
              {
                Appl_MassageMode_CtrlModel_B.DSMLevelFB =
                  Appl_MassageMode_CtrlModel_B.MassageLevel;
                Appl_MassageMode_CtrlModel_DW.LevelFB =
                  Appl_MassageMode_CtrlModel_B.MassageLevel;
              }

              /* 是否为IVI有效指令&&按摩档位已打开 */
              tmp = Appl_MassageMode_CtrlModel_B.IVIMode;
              if ((tmp <= (INT32S)enMassageMode_IVI_EN_M8) && (tmp != (INT32S)
                   enMassageMode_IVI_EN_Inactive) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_AUTO_OFF) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_OFF))
              {
                if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                    Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
                    (MIN_int32_T);
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                    Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
                    Appl_MassageMode_CtrlModel_B.IVIMode - 1);
                }

                Appl_MassageMode_CtrlModel_B.Mode_d =
                  Appl_MassageMode_CtrlModel_B.DSMModeReq;
                Appl_MassageMode_CtrlModel_SaveMassageMode();
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMModeReq =
                  Appl_MassageMode_CtrlModel_B.ModeEEPROM;
              }

              /* Massage节点有效指令&&按摩档位已打开 */
              if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
                   enMassageMode_DSM_EN_MError) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_AUTO_OFF) &&
                  (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                   enMassageLevel_DSM_EN_OFF) &&
                  (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
              {
                Appl_MassageMode_CtrlModel_B.DSMModeFB =
                  Appl_MassageMode_CtrlModel_B.MassageMode;
              }
              else
              {
                Appl_MassageMode_CtrlModel_B.DSMModeFB =
                  Appl_MassageMode_CtrlModel_B.ModeEEPROM;
              }
            }

            Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
              Appl_MassageMode_CtrlModel_B.DSMLevelReq;
            Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)
              Appl_MassageMode_CtrlModel_B.DSMModeReq;
            Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
              Appl_MassageMode_CtrlModel_B.DSMLevelFB;
            Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
              Appl_MassageMode_CtrlModel_B.DSMModeFB;
          }
          else
          {
            Appl_MassageMode_inner_default_MassageStopCount_T2
              (&Mas_IVI_MassageLevel_Req_prev);

            /* 是否由按摩开启状态进入 */
            if (Appl_MassageMode_CtrlModel_DW.MassageOpenFlag == ((BOOL)TRUE))
            {
              /* T1计时是否已到阈值 */
              if (Appl_MassageMode_CtrlModel_B.T1timer <
                  Appl_MassageMode_CtrlModel_B.T1Max)
              {
                tmp = Appl_MassageMode_CtrlModel_B.T1timer + 1;
                if (tmp > 65535)
                {
                  tmp = 65535;
                }

                Appl_MassageMode_CtrlModel_B.T1timer = (INT16U)tmp;
              }
              else
              {
                qY = Appl_MassageMode_CtrlModel_B.T1Max;
                if (Appl_MassageMode_CtrlModel_B.T1Max > 65535U)
                {
                  qY = 65535U;
                }

                Appl_MassageMode_CtrlModel_B.T1timer = (INT16U)qY;

                /* T2没有启动计时，避免T1计时到阈值后T2停止计时mantis：7343 */
                if (0 == Appl_MassageMode_CtrlModel_B.T2timer)
                {
                  Appl_MassageMode_CtrlModel_B.T3timer = 0U;
                  Appl_MassageMode_CtrlModel_B.T4timer = 0U;
                  Appl_MassageMode_CtrlModel_B.AcTCount = 0U;
                }
              }
            }
          }
          break;

         case Appl_MassageMode_CtrlModel_IN_MassageOpen:
          /* C2 */
          if (Appl_MassageMode_CtrlModel_B.Switch == enMassageLevel_DSM_EN_OFF)
          {
            Appl_MassageMode_CtrlModel_B.T3timer = 0U;
            Appl_MassageMode_CtrlModel_B.T1timer = 0U;
            Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)TRUE);
            Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
            Appl_MassageMode_CtrlModel_DW.is_MassageActive =
              Appl_MassageMode_CtrlModel_IN_MassageClose;
            Appl_MassageMode_CtrlM_enter_internal_MassageClose
              (&Mas_IVI_MassageLevel_Req_prev);
          }
          else
          {
            /* C3  */
            if ((Appl_MassageMode_CtrlModel_B.T3timer >=
                 Appl_MassageMode_CtrlModel_B.T3Max) ||
                (Appl_MassageMode_CtrlModel_B.T4timer >=
                 Appl_MassageMode_CtrlModel_B.T4Max))
            {
              Appl_MassageMode_CtrlModel_DW.MassageOpenFlag = ((BOOL)TRUE);
              Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)FALSE);
              Appl_MassageMode_CtrlModel_DW.is_MassageActive =
                Appl_MassageMode_CtrlModel_IN_MassageTimeout;

              /* 是否连续开启 */
              if ((Appl_MassageMode_CtrlModel_B.T3timer >=
                   Appl_MassageMode_CtrlModel_B.T3Max) &&
                  (Appl_MassageMode_CtrlModel_B.T1timer <
                   Appl_MassageMode_CtrlModel_B.T1Max))
              {
                tmp = Appl_MassageMode_CtrlModel_B.AcTCount + 1;
                if (tmp > 255)
                {
                  tmp = 255;
                }

                Appl_MassageMode_CtrlModel_B.AcTCount = (INT8U)tmp;
              }

              Appl_MassageMode_CtrlModel_DW.ExitFlag = ((BOOL)TRUE);
            }
            else
            {
              qY = Appl_MassageMode_CtrlModel_B.T3timer + 1U;
              if (qY < Appl_MassageMode_CtrlModel_B.T3timer)
              {
                qY = MAX_uint32_T;
              }

              Appl_MassageMode_CtrlModel_B.T3timer = qY;
              qY = Appl_MassageMode_CtrlModel_B.T4timer + 1U;
              if (qY < Appl_MassageMode_CtrlModel_B.T4timer)
              {
                qY = MAX_uint32_T;
              }

              Appl_MassageMode_CtrlModel_B.T4timer = qY;

              /* A3正常转发 */
              Appl_MassageMode_CtrlModel_B.IVILevel = Mas_IVI_MassageLevel_Req;
              Appl_MassageMode_CtrlModel_B.IVIMode = (enMassageMode_DSM)
                Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
                (Mas_IVI_MassageMode_Req);
              Appl_MassageMode_CtrlModel_B.MassageLevel =
                Appl_MassageMode_CtrlModel_B.Switch;
              Appl_MassageMode_CtrlModel_B.MassageMode = Mas_Massage_ModeSts_FB;
              Appl_MassageMode_CtrlModel_B.LostFlag = Mas_Massage_0x1B_LostFlag;
              Appl_MassageMode_CtrlModel_B.ModeEEPROM = Mas_SeatMassageMode;
              if (Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel
                  == 0U)
              {
                Appl_MassageMode_CtrlModel_DW.is_active_c5_Appl_MassageMode_CtrlModel
                  = 1U;

                /* 是否为IVI关闭指令 */
                if (Appl_MassageMode_CtrlModel_B.IVILevel ==
                    enMassageLevel_IVI_EN_OFF)
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                    enMassageLevel_DSM_EN_OFF;
                }
                else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L1) ||
                         (Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L2) ||
                         (Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L3))
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
                    Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
                    (Appl_MassageMode_CtrlModel_B.IVILevel);
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                    enMassageLevel_DSM_EN_Inactive;
                }

                /* 是否为Massage节点有效指令 */
                if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
                    enMassageLevel_DSM_EN_L3)
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelFB =
                    Appl_MassageMode_CtrlModel_B.MassageLevel;
                  Appl_MassageMode_CtrlModel_DW.LevelFB =
                    Appl_MassageMode_CtrlModel_B.MassageLevel;
                }

                /* 是否为IVI有效指令&&按摩档位已打开 */
                if ((Appl_MassageMode_CtrlModel_B.IVIMode <=
                     enMassageMode_IVI_EN_M8) &&
                    (Appl_MassageMode_CtrlModel_B.IVIMode !=
                     enMassageMode_IVI_EN_Inactive) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_AUTO_OFF) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_OFF))
                {
                  if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
                  {
                    Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                      Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
                      (MIN_int32_T);
                  }
                  else
                  {
                    Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                      Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
                      Appl_MassageMode_CtrlModel_B.IVIMode - 1);
                  }

                  Appl_MassageMode_CtrlModel_B.Mode_d =
                    Appl_MassageMode_CtrlModel_B.DSMModeReq;
                  Appl_MassageMode_CtrlModel_SaveMassageMode();
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq =
                    Appl_MassageMode_CtrlModel_B.ModeEEPROM;
                }

                /* Massage节点有效指令&&按摩档位已打开 */
                if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
                     enMassageMode_DSM_EN_MError) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_AUTO_OFF) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_OFF) &&
                    (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeFB =
                    Appl_MassageMode_CtrlModel_B.MassageMode;
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeFB =
                    Appl_MassageMode_CtrlModel_B.ModeEEPROM;
                }
              }
              else
              {
                /* 是否为IVI关闭指令 */
                if (Appl_MassageMode_CtrlModel_B.IVILevel ==
                    enMassageLevel_IVI_EN_OFF)
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                    enMassageLevel_DSM_EN_OFF;
                }
                else if ((Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L1) ||
                         (Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L2) ||
                         (Appl_MassageMode_CtrlModel_B.IVILevel ==
                          enMassageLevel_IVI_EN_L3))
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq = (enMassageLevel_DSM)
                    Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
                    (Appl_MassageMode_CtrlModel_B.IVILevel);
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelReq =
                    enMassageLevel_DSM_EN_Inactive;
                }

                /* 是否为Massage节点有效指令 */
                if (Appl_MassageMode_CtrlModel_B.MassageLevel <=
                    enMassageLevel_DSM_EN_L3)
                {
                  Appl_MassageMode_CtrlModel_B.DSMLevelFB =
                    Appl_MassageMode_CtrlModel_B.MassageLevel;
                  Appl_MassageMode_CtrlModel_DW.LevelFB =
                    Appl_MassageMode_CtrlModel_B.MassageLevel;
                }

                /* 是否为IVI有效指令&&按摩档位已打开 */
                if ((Appl_MassageMode_CtrlModel_B.IVIMode <=
                     enMassageMode_IVI_EN_M8) &&
                    (Appl_MassageMode_CtrlModel_B.IVIMode !=
                     enMassageMode_IVI_EN_Inactive) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_AUTO_OFF) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_OFF))
                {
                  if ((INT32S)Appl_MassageMode_CtrlModel_B.IVIMode < -2147483647)
                  {
                    Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                      Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
                      (MIN_int32_T);
                  }
                  else
                  {
                    Appl_MassageMode_CtrlModel_B.DSMModeReq = (enMassageMode_DSM)
                      Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM((INT32S)
                      Appl_MassageMode_CtrlModel_B.IVIMode - 1);
                  }

                  Appl_MassageMode_CtrlModel_B.Mode_d =
                    Appl_MassageMode_CtrlModel_B.DSMModeReq;
                  Appl_MassageMode_CtrlModel_SaveMassageMode();
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeReq =
                    Appl_MassageMode_CtrlModel_B.ModeEEPROM;
                }

                /* Massage节点有效指令&&按摩档位已打开 */
                if ((Appl_MassageMode_CtrlModel_B.MassageMode <=
                     enMassageMode_DSM_EN_MError) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_AUTO_OFF) &&
                    (Appl_MassageMode_CtrlModel_DW.LevelFB !=
                     enMassageLevel_DSM_EN_OFF) &&
                    (Appl_MassageMode_CtrlModel_B.LostFlag != ((BOOL)TRUE)))
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeFB =
                    Appl_MassageMode_CtrlModel_B.MassageMode;
                }
                else
                {
                  Appl_MassageMode_CtrlModel_B.DSMModeFB =
                    Appl_MassageMode_CtrlModel_B.ModeEEPROM;
                }
              }

              Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
                Appl_MassageMode_CtrlModel_B.DSMLevelReq;
              Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)
                Appl_MassageMode_CtrlModel_B.DSMModeReq;
              Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
                Appl_MassageMode_CtrlModel_B.DSMLevelFB;
              Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
                Appl_MassageMode_CtrlModel_B.DSMModeFB;
            }
          }
          break;

         default:
          /* C3 */
          if (Appl_MassageMode_CtrlModel_DW.ExitFlag == ((BOOL)TRUE))
          {
            Appl_MassageMode_CtrlModel_DW.ExitFlag = ((BOOL)FALSE);
            Appl_MassageMode_CtrlModel_B.T3timer = 0U;
            Appl_MassageMode_CtrlModel_B.T1timer = 0U;
            Appl_MassageMode_CtrlModel_DW.AutoOffFlag = ((BOOL)TRUE);
            Appl_MassageMode_CtrlModel_DW.is_MassageActive =
              Appl_MassageMode_CtrlModel_IN_MassageClose;
            Appl_MassageMode_CtrlM_enter_internal_MassageClose
              (&Mas_IVI_MassageLevel_Req_prev);
          }
          else
          {
            /* 是否连续开启 */
            if ((Appl_MassageMode_CtrlModel_B.T3timer >=
                 Appl_MassageMode_CtrlModel_B.T3Max) &&
                (Appl_MassageMode_CtrlModel_B.T1timer <
                 Appl_MassageMode_CtrlModel_B.T1Max))
            {
              tmp = Appl_MassageMode_CtrlModel_B.AcTCount + 1;
              if (tmp > 255)
              {
                tmp = 255;
              }

              Appl_MassageMode_CtrlModel_B.AcTCount = (INT8U)tmp;
            }

            Appl_MassageMode_CtrlModel_DW.ExitFlag = ((BOOL)TRUE);
          }
          break;
        }
      }
    }
  }
  else
  {
    /* 满足CC1 */
    if (Appl_MassageMode_CtrlModel_B.MassagePC_Flag == ((BOOL)TRUE))
    {
      Appl_MassageMode_CtrlModel_DW.is_MassageInactive = 0;
      Appl_MassageMode_CtrlModel_DW.is_c8_Appl_MassageMode_CtrlModel =
        Appl_MassageMode_CtrlModel_IN_MassageActive;
      Appl_MassageMode_CtrlModel_DW.is_MassageActive =
        Appl_MassageMode_CtrlModel_IN_MassageClose;
      Appl_MassageMode_CtrlM_enter_internal_MassageClose
        (&Mas_IVI_MassageLevel_Req_prev);
    }
    else
    {
      /* 考虑恢复出厂ModeReq */
      Appl_MassageMode_CtrlModel_B.MassageLevel_Req = (INT8U)
        enMassageLevel_DSM_EN_OFF;
      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB =
        enMassageLevel_DSM_EN_OFF;
      Appl_MassageMode_CtrlModel_B.MassageMode_Req = (INT8U)Mas_SeatMassageMode;
      if (Appl_MassageMode_CtrlModel_DW.is_MassageInactive ==
          Appl_MassageMode_CtrlModel_IN_MassageHaveFault)
      {
        /* Massage_ModeSts_FB
           != 0x8:enMassageError
           || 恢复出厂模式 == TRUE */
        if ((Mas_Massage_ModeSts_FB != enMassageMode_DSM_EN_MError) ||
            (Mas_RecoverDefaultFlag == ((BOOL)TRUE)))
        {
          Appl_MassageMode_CtrlModel_DW.is_MassageInactive =
            Appl_MassageMode_CtrlModel_IN_MassageNoneFault;
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_SeatMassageMode;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
            Mas_Massage_ModeSts_FB;
        }
      }
      else
      {
        /* Massage_ModeSts_FB
           ==0x8:enMassageError mantis(7247) */
        if (Mas_Massage_ModeSts_FB == enMassageMode_DSM_EN_MError)
        {
          Appl_MassageMode_CtrlModel_DW.is_MassageInactive =
            Appl_MassageMode_CtrlModel_IN_MassageHaveFault;
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB =
            Mas_Massage_ModeSts_FB;
        }
        else
        {
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = Mas_SeatMassageMode;
        }
      }
    }
  }

  Mas_Massage_LevelSts_FB_prev =
    Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start;
  Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start =
    Mas_Res_MassageLevel_Req;
  MassageLevel_Req_prev = Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start;
  Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start =
    Appl_MassageMode_CtrlModel_B.MassageLevel_Req;
  MassageMode_Req_prev = Appl_MassageMode_CtrlModel_DW.MassageMode_Req_start;
  Appl_MassageMode_CtrlModel_DW.MassageMode_Req_start =
    Appl_MassageMode_CtrlModel_B.MassageMode_Req;
  if (Appl_MassageMode_CtrlModel_DW.is_active_c6_Appl_MassageMode_CtrlModel ==
      0U)
  {
    Appl_MassageMode_CtrlModel_DW.is_active_c6_Appl_MassageMode_CtrlModel = 1U;

    /* (小憩按摩请求变为Level3或OFF)&&未开启T2计时 */
    if ((((Mas_Res_MassageLevel_Req !=
           Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start) &&
          (Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start ==
           enMassageLevel_DSM_EN_L3)) || ((Mas_Res_MassageLevel_Req !=
           Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start) &&
          (Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start ==
           enMassageLevel_DSM_EN_OFF))) &&
        ((Appl_MassageMode_CtrlModel_B.T2timer >=
          Appl_MassageMode_CtrlModel_B.T2Max) ||
         (Appl_MassageMode_CtrlModel_B.T2timer == 0)))
    {
      /* 开启小憩的时候才更新档位 */
      if (Mas_Res_MassageLevel_Req == enMassageLevel_DSM_EN_L3)
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req =
          Mas_Res_MassageMode_Req;
        Appl_MassageMode_CtrlModel_B.Mode_l =
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req;
        Appl_MassageMode_CtrlModel_SaveMassageMode_a();
      }

      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req =
        Mas_Res_MassageLevel_Req;
    }
    else
    {
      /* 按摩档位 */
      if (((Appl_MassageMode_CtrlModel_B.MassageLevel_Req !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_OFF)) ||
          ((Appl_MassageMode_CtrlModel_B.MassageLevel_Req !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L1)) ||
          ((Appl_MassageMode_CtrlModel_B.MassageLevel_Req !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L2)) ||
          ((Appl_MassageMode_CtrlModel_B.MassageLevel_Req !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L3)) ||
          ((Appl_MassageMode_CtrlModel_B.MassageLevel_Req !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_AUTO_OFF)))
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req = (enMassageLevel_DSM)
          Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
          (Appl_MassageMode_CtrlModel_B.MassageLevel_Req);
      }

      /* 模式请求变化 */
      if (Appl_MassageMode_CtrlModel_B.MassageMode_Req !=
          Appl_MassageMode_CtrlModel_DW.MassageMode_Req_start)
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req = (enMassageMode_DSM)
          Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
          (Appl_MassageMode_CtrlModel_B.MassageMode_Req);
      }
    }
  }
  else
  {
    /* (小憩按摩请求变为Level3或OFF)&&未开启T2计时 */
    if ((((Mas_Massage_LevelSts_FB_prev !=
           Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start) &&
          (Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start ==
           enMassageLevel_DSM_EN_L3)) || ((Mas_Massage_LevelSts_FB_prev !=
           Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start) &&
          (Appl_MassageMode_CtrlModel_DW.Mas_Res_MassageLevel_Req_start ==
           enMassageLevel_DSM_EN_OFF))) &&
        ((Appl_MassageMode_CtrlModel_B.T2timer >=
          Appl_MassageMode_CtrlModel_B.T2Max) ||
         (Appl_MassageMode_CtrlModel_B.T2timer == 0)))
    {
      /* 开启小憩的时候才更新档位 */
      if (Mas_Res_MassageLevel_Req == enMassageLevel_DSM_EN_L3)
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req =
          Mas_Res_MassageMode_Req;
        Appl_MassageMode_CtrlModel_B.Mode_l =
          Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req;
        Appl_MassageMode_CtrlModel_SaveMassageMode_a();
      }

      Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req =
        Mas_Res_MassageLevel_Req;
    }
    else
    {
      /* 按摩档位 */
      if (((MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_OFF)) || ((MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L1)) || ((MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L2)) || ((MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_L3)) || ((MassageLevel_Req_prev !=
            Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start) &&
           (Appl_MassageMode_CtrlModel_DW.MassageLevel_Req_start == (INT32S)
            enMassageLevel_DSM_EN_AUTO_OFF)))
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req = (enMassageLevel_DSM)
          Appl_MassageMode_C_safe_cast_to_enMassageLevel_DSM
          (Appl_MassageMode_CtrlModel_B.MassageLevel_Req);
      }

      /* 模式请求变化 */
      if (MassageMode_Req_prev !=
          Appl_MassageMode_CtrlModel_DW.MassageMode_Req_start)
      {
        Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req = (enMassageMode_DSM)
          Appl_MassageMode_Ct_safe_cast_to_enMassageMode_DSM
          (Appl_MassageMode_CtrlModel_B.MassageMode_Req);
      }
    }
  }
}

/* Output and update for function-call system: '<S19>/SaveMassageMode' */
static void Appl_MassageMode_CtrlModel_SaveMassageMode_a1(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_MassageMode,
    Appl_MassageMode_CtrlModel_B.Mode);
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_MassageMode_CtrlModel_RTE(void)
{
  Mas_DiagTimeT1 = Rte_GetVfb_Debug_Mas_T1_Threshold( );
  Mas_DiagTimeT2 = Rte_GetVfb_Debug_Mas_T2_Threshold( );
  Mas_DiagTimeT3 = Rte_GetVfb_Debug_Mas_T3_Threshold( );
  Mas_DiagTimeT4 = Rte_GetVfb_Debug_Mas_T4_Threshold( );
  Mas_EngineRunFlag = Rte_GetVfb_EngineRunFlag( );
  Mas_IVI_MassageLevel_Req = CanRx_0x351_IVI_MassageLevel_Req( );
  Mas_IVI_MassageMode_Req = CanRx_0x351_IVI_MassageMode_Req( );
  Mas_IVI_NapMode_SwtichSet = CanRx_0x367_IVI_NapMode_SwtichSet( );
  Mas_Massage_0x1B_LostFlag = Ecual_LinGetLostPid( );
  Mas_Massage_LevelSts_FB = LinSignalGet_Massage_1_Massage_LevelSts_FB( );
  Mas_Massage_ModeSts_FB = LinSignalGet_Massage_1_Massage_ModeSts_FB( );
  Mas_PowerMode = Rte_GetVfb_PowerMode( );
  Mas_RecoverDefaultFlag = GetRecoverDefaultFlag( );
  Mas_Res_MassageLevel_Req = Rte_GetVfb_Res_MassageLevel_Req( );
  Mas_Res_MassageMode_Req = Rte_GetVfb_Res_MassageMode_Req( );
  Mas_SeatMassageCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageConfig);
  Mas_SeatMassageMode = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageMode);
  Mas_VehiclePrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  Mas_VehicleRunFlag = Rte_GetVfb_VehicleRunFlag( );
  Mas_VoltMode = Rte_GetVfb_VoltMode( );
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_MassageMode_CtrlModel_UpDataInputInfo_Init(void)
{
  Appl_MassageMode_CtrlModel_DW.is_active_c11_Appl_MassageMode_CtrlModel = 0U;
  Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel =
    Appl_MassageMode_CtrlModel_IN_NO_ACTIVE_CHILD_c;
  Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer = 0U;
  Appl_MassageMode_CtrlModel_B.MassagePC_Flag = 0U;
  Appl_MassageMode_CtrlModel_B.MassagePCStopReason = 0U;
  Appl_MassageMode_CtrlModel_DW.is_active_c1_Appl_MassageMode_CtrlModel = 0U;
  Appl_MassageMode_CtrlModel_B.T1Max = 0U;
  Appl_MassageMode_CtrlModel_B.T2Max = 0U;
  Appl_MassageMode_CtrlModel_B.T3Max = 0U;
  Appl_MassageMode_CtrlModel_B.T4Max = 0U;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_MassageMode_CtrlModel_UpDataInputInfo(void)
{
  INT32S tmp;
  BOOL guard1 = false;
  BOOL guard2 = false;
  Appl_MassageMode_CtrlModel_RTE();
  if (Mas_Massage_0x1B_LostFlag != 0)
  {
    Appl_MassageMode_CtrlModel_B.Switch = enMassageLevel_DSM_EN_OFF;
  }
  else
  {
    Appl_MassageMode_CtrlModel_B.Switch = Mas_Massage_LevelSts_FB;
  }

  if (Appl_MassageMode_CtrlModel_DW.is_active_c11_Appl_MassageMode_CtrlModel ==
      0U)
  {
    Appl_MassageMode_CtrlModel_DW.is_active_c11_Appl_MassageMode_CtrlModel = 1U;
    Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel =
      Appl_MassageMode_CtrlModel_IN_Init;
    Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)FALSE);
  }
  else
  {
    guard1 = false;
    guard2 = false;
    switch (Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel)
    {
     case Appl_MassageMode_CtrlModel_IN_FALSE:
      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)FALSE);

      /* 电源档位 == ON
         && (发动机运行状态 == TRUE || 整车运行状态 == TRUE)
         && Massage_ModeSts_FB != 0x8:enMassageError
         && 按摩配置字 == TRUE
         && 车辆类型 == P20
         && 恢复出厂模式 != TRUE
         && 电压处于正常模式
       /MassagePCStopReason = 0x0:enNone; */
      if ((Mas_PowerMode == enPowerModeSts_EN_ON) && ((Mas_VehicleRunFlag ==
            ((BOOL)TRUE)) || (Mas_EngineRunFlag == ((BOOL)TRUE))) &&
          (Mas_Massage_ModeSts_FB != enMassageMode_DSM_EN_MError) &&
          (Mas_SeatMassageCfg == ((BOOL)TRUE)) && (Mas_VehiclePrm ==
           enVehTypePrm_enP20) && ((Mas_RecoverDefaultFlag != ((BOOL)TRUE)) &&
           (Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer >= 200)) &&
          (Mas_VoltMode == enFinalPowerMode_EN_NORMAL_VOLT))
      {
        Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
          enMasReason_enNone;
        Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel =
          Appl_MassageMode_CtrlModel_IN_TRUE;
        Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)TRUE);
      }
      else
      {
        if (Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer < 200)
        {
          tmp = Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer = (INT16U)tmp;
        }

        if (Mas_RecoverDefaultFlag == ((BOOL)TRUE))
        {
          Appl_MassageMode_CtrlModel_B.Mode = enMassageMode_DSM_EN_M1;
          Appl_MassageMode_CtrlModel_SaveMassageMode_a1();
        }
      }
      break;

     case Appl_MassageMode_CtrlModel_IN_Init:
      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)FALSE);

      /* MassagePC未置位原因 Mas_PowerMode 不满足条件 */
      if (Mas_PowerMode != enPowerModeSts_EN_ON)
      {
        Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
          enMasReason_enPowerError;
        guard2 = true;
      }
      else
      {
        /* MassagePC未置位原因 Mas_VehicleRunFlag 不满足条件 */
        if ((Mas_VehicleRunFlag != ((BOOL)TRUE)) && (Mas_EngineRunFlag != ((BOOL)
              TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
            enMasReason_enRunError;
          guard2 = true;
        }
        else
        {
          /* MassagePC未置位原因 ：Mas_MassageMode_FB 不满足条件 */
          if (Mas_Massage_ModeSts_FB == enMassageMode_DSM_EN_MError)
          {
            Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
              enMasReason_enNodeError;
            guard2 = true;
          }
          else
          {
            /* MassagePC未置位原因 ：Mas_SeatMassageCfg不满足条件 */
            if (Mas_SeatMassageCfg != ((BOOL)TRUE))
            {
              Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                enMasReason_enConfigError;
              guard2 = true;
            }
            else
            {
              /* MassagePC未置位原因 ：Mas_VehiclePrm 不满足条件 */
              if (Mas_VehiclePrm != enVehTypePrm_enP20)
              {
                Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                  enMasReason_enCarTypeError;
                guard2 = true;
              }
              else
              {
                /* MassagePC未置位原因 ：Mas_RecoverDefaultFlag 不满足条件   */
                if (Mas_RecoverDefaultFlag == ((BOOL)TRUE))
                {
                  Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                    enMasReason_enRecoverError;
                  guard2 = true;
                }
                else
                {
                  /* MassagePC未置位原因 ：Mas_VoltMode 不满足条件 */
                  if (Mas_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT)
                  {
                    Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                      enMasReason_enPowerModeError;
                    guard2 = true;
                  }
                  else
                  {
                    /* 电源档位 == ON
                       && (发动机运行状态 == TRUE || 整车运行状态 == TRUE)
                       && Massage_ModeSts_FB != 0x8:enMassageError
                       && 按摩配置字 == TRUE
                       && 车辆类型 == P20
                       && 恢复出厂模式 != TRUE
                       && 电压处于正常模式
                     /MassagePCStopReason = 0x0:enNone; */
                    if ((Mas_PowerMode == enPowerModeSts_EN_ON) &&
                        ((Mas_VehicleRunFlag == ((BOOL)TRUE)) ||
                         (Mas_EngineRunFlag == ((BOOL)TRUE))) &&
                        (Mas_Massage_ModeSts_FB != enMassageMode_DSM_EN_MError) &&
                        (Mas_SeatMassageCfg == ((BOOL)TRUE)) && (Mas_VehiclePrm ==
                         enVehTypePrm_enP20) && (Mas_RecoverDefaultFlag !=
                         ((BOOL)TRUE)) && (Mas_VoltMode ==
                                           enFinalPowerMode_EN_NORMAL_VOLT))
                    {
                      Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                        enMasReason_enNone;
                      Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel
                        = Appl_MassageMode_CtrlModel_IN_TRUE;
                      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)TRUE);
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
      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)TRUE);

      /* MassagePC未置位原因 Mas_PowerMode 不满足条件 */
      if (Mas_PowerMode != enPowerModeSts_EN_ON)
      {
        Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
          enMasReason_enPowerError;
        guard1 = true;
      }
      else
      {
        /* MassagePC未置位原因 Mas_VehicleRunFlag 不满足条件 */
        if ((Mas_VehicleRunFlag != ((BOOL)TRUE)) && (Mas_EngineRunFlag != ((BOOL)
              TRUE)))
        {
          Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
            enMasReason_enRunError;
          guard1 = true;
        }
        else
        {
          /* MassagePC未置位原因 ：Mas_MassageMode_FB 不满足条件 */
          if (Mas_Massage_ModeSts_FB == enMassageMode_DSM_EN_MError)
          {
            Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
              enMasReason_enNodeError;
            guard1 = true;
          }
          else
          {
            /* MassagePC未置位原因 ：Mas_SeatMassageCfg不满足条件 */
            if (Mas_SeatMassageCfg != ((BOOL)TRUE))
            {
              Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                enMasReason_enConfigError;
              guard1 = true;
            }
            else
            {
              /* MassagePC未置位原因 ：Mas_VehiclePrm 不满足条件 */
              if (Mas_VehiclePrm != enVehTypePrm_enP20)
              {
                Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                  enMasReason_enCarTypeError;
                guard1 = true;
              }
              else
              {
                /* MassagePC未置位原因 ：Mas_RecoverDefaultFlag 不满足条件   */
                if (Mas_RecoverDefaultFlag == ((BOOL)TRUE))
                {
                  Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                    enMasReason_enRecoverError;
                  Appl_MassageMode_CtrlModel_DW.RecoverDefaultDelayTimer = 0U;
                  Appl_MassageMode_CtrlModel_B.Mode = enMassageMode_DSM_EN_M1;
                  Appl_MassageMode_CtrlModel_SaveMassageMode_a1();
                  guard1 = true;
                }
                else
                {
                  /* MassagePC未置位原因 ：Mas_VoltMode 不满足条件 */
                  if (Mas_VoltMode != enFinalPowerMode_EN_NORMAL_VOLT)
                  {
                    Appl_MassageMode_CtrlModel_B.MassagePCStopReason = (INT8U)
                      enMasReason_enPowerModeError;
                    guard1 = true;
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
      Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel =
        Appl_MassageMode_CtrlModel_IN_FALSE;
      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)FALSE);
    }

    if (guard1)
    {
      Appl_MassageMode_CtrlModel_DW.is_c11_Appl_MassageMode_CtrlModel =
        Appl_MassageMode_CtrlModel_IN_FALSE;
      Appl_MassageMode_CtrlModel_B.MassagePC_Flag = ((BOOL)FALSE);
    }
  }

  if (Appl_MassageMode_CtrlModel_DW.is_active_c1_Appl_MassageMode_CtrlModel ==
      0U)
  {
    Appl_MassageMode_CtrlModel_DW.is_active_c1_Appl_MassageMode_CtrlModel = 1U;

    /*  是否诊断配置  */
    if (Mas_DiagTimeT1 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T1Max = ((INT16U)D_T1);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T1Max = (INT32U)(Mas_DiagTimeT1 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT2 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T2Max = ((INT16U)D_T2);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T2Max = (INT32U)(Mas_DiagTimeT2 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT3 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T3Max = ((INT32U)D_T3);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T3Max = (INT32U)(Mas_DiagTimeT3 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT4 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T4Max = ((INT32U)D_T4);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T4Max = (INT32U)(Mas_DiagTimeT4 * 100);
    }
  }
  else
  {
    /*  是否诊断配置  */
    if (Mas_DiagTimeT1 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T1Max = ((INT16U)D_T1);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T1Max = (INT32U)(Mas_DiagTimeT1 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT2 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T2Max = ((INT16U)D_T2);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T2Max = (INT32U)(Mas_DiagTimeT2 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT3 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T3Max = ((INT32U)D_T3);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T3Max = (INT32U)(Mas_DiagTimeT3 * 100);
    }

    /*  是否诊断配置  */
    if (Mas_DiagTimeT4 == 0)
    {
      Appl_MassageMode_CtrlModel_B.T4Max = ((INT32U)D_T4);
    }
    else
    {
      Appl_MassageMode_CtrlModel_B.T4Max = (INT32U)(Mas_DiagTimeT4 * 100);
    }
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_MassageMode_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_Debug_Mas_ActCount(Appl_MassageMode_CtrlModel_B.AcTCount);
  CanTx_0x3B2_DSM_MassageLevel_FB
    (Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB);
  LinSignalSet_DSM_1_1_DSM_MassageLevel_Req
    (Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req);
  CanTx_0x3B2_DSM_MassageMode_FB(Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB);
  LinSignalSet_DSM_1_1_DSM_MassageMode_Req
    (Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req);
  Rte_SetVfb_Debug_Mas_MassagePCStopReason
    (Appl_MassageMode_CtrlModel_B.MassagePCStopReason_l);
  Rte_SetVfb_Debug_Mas_T1timer(Appl_MassageMode_CtrlModel_B.T1timer);
  Rte_SetVfb_Debug_Mas_T2timer(Appl_MassageMode_CtrlModel_B.T2timer);
  Rte_SetVfb_Debug_Mas_T3timer(Appl_MassageMode_CtrlModel_B.T3timer);
  Rte_SetVfb_Debug_Mas_T4timer(Appl_MassageMode_CtrlModel_B.T4timer);
}

/* Model step function */
void Appl_MassageMode_CtrlModel_step(void)
{
  Appl_MassageMode_CtrlModel_UpDataInputInfo();
  Appl_MassageMode_CtrlModel_LogicCtrl();
  Appl_MassageMode_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_MassageMode_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_MassageMode_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_MassageMode_CtrlModel_B), 0,
                sizeof(B_Appl_MassageMode_CtrlModel_T));

  {
    Appl_MassageMode_CtrlModel_B.Mode = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.DSM_MassageMode_Req = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.Mode_l = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.DSM_MassageMode_FB = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.IVIMode = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.MassageMode = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.ModeEEPROM = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.DSMModeFB = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.DSMModeReq = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.Mode_d = enMassageMode_DSM_EN_M1;
    Appl_MassageMode_CtrlModel_B.IVILevel = enMassageLevel_IVI_EN_Inactive;
    Appl_MassageMode_CtrlModel_B.Switch = enMassageLevel_DSM_EN_OFF;
    Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_Req =
      enMassageLevel_DSM_EN_OFF;
    Appl_MassageMode_CtrlModel_B.DSM_MassageLevel_FB = enMassageLevel_DSM_EN_OFF;
    Appl_MassageMode_CtrlModel_B.MassageLevel = enMassageLevel_DSM_EN_OFF;
    Appl_MassageMode_CtrlModel_B.DSMLevelReq = enMassageLevel_DSM_EN_OFF;
    Appl_MassageMode_CtrlModel_B.DSMLevelFB = enMassageLevel_DSM_EN_OFF;
  }

  /* exported global signals */
  Mas_VehiclePrm = enVehTypePrm_enP20;
  Mas_PowerMode = enPowerModeSts_EN_OFF;
  Mas_IVI_MassageMode_Req = enMassageMode_IVI_EN_Inactive;
  Mas_Massage_ModeSts_FB = enMassageMode_DSM_EN_M1;
  Mas_Res_MassageMode_Req = enMassageMode_DSM_EN_M1;
  Mas_SeatMassageMode = enMassageMode_DSM_EN_M1;
  Mas_IVI_MassageLevel_Req = enMassageLevel_IVI_EN_Inactive;
  Mas_Massage_LevelSts_FB = enMassageLevel_DSM_EN_OFF;
  Mas_Res_MassageLevel_Req = enMassageLevel_DSM_EN_OFF;
  Mas_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  Mas_DiagTimeT1 = ((INT16U)0U);
  Mas_DiagTimeT2 = ((INT16U)0U);
  Mas_DiagTimeT3 = ((INT16U)0U);
  Mas_DiagTimeT4 = ((INT16U)0U);
  Mas_EngineRunFlag = ((INT8U)0U);
  Mas_IVI_NapMode_SwtichSet = ((INT8U)0U);
  Mas_Massage_0x1B_LostFlag = ((INT8U)0U);
  Mas_RecoverDefaultFlag = ((INT8U)0U);
  Mas_SeatMassageCfg = ((INT8U)0U);
  Mas_VehicleRunFlag = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_MassageMode_CtrlModel_DW, 0,
                sizeof(DW_Appl_MassageMode_CtrlModel_T));
  Appl_MassageMode_CtrlModel_UpDataInputInfo_Init();
  Appl_MassageMode_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
