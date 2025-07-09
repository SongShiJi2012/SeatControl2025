/*
 * File: Appl_PaAdjustModel.c
 *
 * Code generated for Simulink model 'Appl_PaAdjustModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat Jul  3 11:49:21 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_PaAdjustModel.h"

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

#ifndef D_Relay_DownBackFault
#error The variable for the parameter "D_Relay_DownBackFault" is not defined
#endif

#ifndef D_Relay_UpFrontFault
#error The variable for the parameter "D_Relay_UpFrontFault" is not defined
#endif

/* Named constants for Chart: '<S7>/CrankUnloading' */
#define Appl_PaAdjustModel_IN_Ban      ((INT8U)1U)
#define Appl_PaAdjustModel_IN_Init     ((INT8U)2U)

/* Named constants for Chart: '<S8>/MotorMotionPriorityDeal' */
#define Appl_PaAdjustModel_IN_Action   ((INT8U)1U)

/* Named constants for Chart: '<S18>/MotorAdjust' */
#define Appl_PaAdjustModel_IN_H_MotorDownBackRun ((INT8U)1U)
#define Appl_PaAdjustModel_IN_H_MotorUpFrontRun ((INT8U)2U)
#define Appl_PaAdjustModel_IN_Init_Interval ((INT8U)3U)

/* Exported block signals */
enMosErrSts PaMtr_BackMotorMosErr;     /* '<S27>/PaMtr_BackMotorMosErr'
                                        * 预驱电机故障原因
                                        */
enMosErrSts PaMtr_FrontMotorMosErr;    /* '<S27>/PaMtr_FrontMotorMosErr'
                                        * 预驱电机故障原因
                                        */
enMosErrSts PaMtr_HeigthMotorMosErr;   /* '<S27>/PaMtr_HeigthMotorMosErr'
                                        * 预驱电机故障原因
                                        */
enMosErrSts PaMtr_LengthMotorMosErr;   /* '<S27>/PaMtr_LengthMotorMosErr'
                                        * 预驱电机故障原因
                                        */
enIgnSts PaMtr_PowerModeStatus;        /* '<S27>/PaMtr_PowerModeStatus'
                                        * 整车电源档位
                                        */
enFinalPowerMode PaMtr_VoltMode;       /* '<S27>/PaMtr_VoltMode'
                                        * 整车电压模式
                                        */
INT16U PaMtr_BackDefaultStopPos;       /* '<S27>/PaMtr_BackDefaultStopPos'
                                        * 硬止点坐标-副驾靠背
                                        */
INT16U PaMtr_BackHallPosi;             /* '<S27>/PaMtr_BackHallPosi'
                                        * 当前霍尔坐标-副驾靠背
                                        */
INT16U PaMtr_FrontDefaulStoptPos;      /* '<S27>/PaMtr_FrontDefaulStoptPos'
                                        * 硬止点坐标-副驾腿托
                                        */
INT16U PaMtr_FrontHallPosi;            /* '<S27>/PaMtr_FrontHallPosi'
                                        * 当前霍尔坐标-副驾腿托
                                        */
INT16U PaMtr_HeightDefaultStopPos;     /* '<S27>/PaMtr_HeightDefaultStopPos'
                                        * 硬止点坐标-副驾高度
                                        */
INT16U PaMtr_HeightHallPosi;           /* '<S27>/PaMtr_HeightHallPosi'
                                        * 当前霍尔坐标-副驾高度
                                        */
INT16U PaMtr_LengthDefaultStopPos;     /* '<S27>/PaMtr_LengthDefaultStopPos'
                                        * 硬止点坐标-副驾纵向
                                        */
INT16U PaMtr_LengthHallPosi;           /* '<S27>/PaMtr_LengthHallPosi'
                                        * 当前霍尔坐标-副驾纵向
                                        */
INT16U PaMtr_MemoryBackReqPosi;        /* '<S27>/PaMtr_MemoryBackReqPosi'
                                        * 记忆调用-副驾靠背位置
                                        */
INT16U PaMtr_MemoryFrontReqPosi;       /* '<S27>/PaMtr_MemoryFrontReqPosi'
                                        * 记忆调用-副驾前部位置
                                        */
INT16U PaMtr_MemoryHeightReqPosi;      /* '<S27>/PaMtr_MemoryHeightReqPosi'
                                        * 记忆调用-副驾高度位置
                                        */
INT16U PaMtr_MemoryLengthReqPosi;      /* '<S27>/PaMtr_MemoryLengthReqPosi'
                                        * 记忆调用-副驾纵向位置
                                        */
INT16U PaMtr_ResetBackReqPosi;         /* '<S27>/PaMtr_ResetBackReqPosi'
                                        * 复位调用-靠背位置
                                        */
INT16U PaMtr_ResetFrontReqPosi;        /* '<S27>/PaMtr_ResetFrontReqPosi'
                                        * 复位调用-前部位置
                                        */
INT16U PaMtr_ResetHeightReqPosi;       /* '<S27>/PaMtr_ResetHeightReqPosi'
                                        * 复位调用-高度位置
                                        */
INT16U PaMtr_ResetLengthReqPosi;       /* '<S27>/PaMtr_ResetLengthReqPosi'
                                        * 复位调用-纵向位置
                                        */
INT16U PaMtr_WelcomeBackReqPosi;       /* '<S27>/PaMtr_WelcomeBackReqPosi'
                                        * 迎宾调用-副驾靠背位置
                                        */
INT16U PaMtr_WelcomeLengthReqPosi;     /* '<S27>/PaMtr_WelcomeLengthReqPosi'
                                        * 迎宾调用-副驾纵向位置
                                        */
INT8U PaMtr_AnyoneHallErr;             /* '<S27>/PaMtr_AnyoneHallErr'
                                        * 任一霍尔故障标志
                                        */
INT8U PaMtr_AnyoneRelayAdheErr;        /* '<S27>/PaMtr_AnyoneRelayAdheErr'
                                        * 任一继电器粘连故障标志
                                        */
INT8U PaMtr_BackHallErr;               /* '<S27>/PaMtr_BackHallErr'
                                        * 霍故障标志位-副驾靠背
                                        */
INT8U PaMtr_BackLearnCmd;              /* '<S27>/PaMtr_BackLearnCmd'
                                        * 学习输入请求-靠背
                                        */
INT8U PaMtr_BackMotorTimeOutErr;       /* '<S27>/PaMtr_BackMotorTimeOutErr'
                                        * 电机运行超时标志-副驾靠背
                                        */
INT8U PaMtr_BackRelayAdhesionErr;      /* '<S27>/PaMtr_BackRelayAdhesionErr'
                                        * 继电器粘连标志位-副驾靠背
                                        */
INT8U PaMtr_BackSoftStopErr;           /* '<S27>/PaMtr_BackSoftStopErr'
                                        * 到达软止点-副驾靠背
                                        */
INT8U PaMtr_BackStallErr;              /* '<S27>/PaMtr_BackStallErr'
                                        * 堵转标志位-副驾靠背
                                        */
INT8U PaMtr_BackSwitchAdheErr;         /* '<S27>/PaMtr_BackSwitchAdheErr'
                                        * 开关粘连故障标志位-副驾靠背
                                        */
INT8U PaMtr_BackSwitchCmd;             /* '<S27>/PaMtr_BackSwitchCmd'
                                        * 硬线开关输入请求-副驾靠背
                                        */
INT8U PaMtr_DiagnoseLearnIn;           /* '<S27>/PaMtr_DiagnoseLearnIn'
                                        * 请求学习标志
                                        */
INT8U PaMtr_FrontHallErr;              /* '<S27>/PaMtr_FrontHallErr'
                                        * 霍故障标志位-副驾腿托
                                        */
INT8U PaMtr_FrontLearnCmd;             /* '<S27>/PaMtr_FrontLearnCmd'
                                        * 学习输入请求-腿托
                                        */
INT8U PaMtr_FrontMotorTimeOutErr;      /* '<S27>/PaMtr_FrontMotorTimeOutErr'
                                        * 电机运行超时标志-副驾腿托
                                        */
INT8U PaMtr_FrontRelayAdhesionErr;     /* '<S27>/PaMtr_FrontRelayAdhesionErr'
                                        * 继电器粘连标志位-副驾腿托
                                        */
INT8U PaMtr_FrontSoftStopErr;          /* '<S27>/PaMtr_FrontSoftStopErr'
                                        * 到达软止点-副驾腿托
                                        */
INT8U PaMtr_FrontStallErr;             /* '<S27>/PaMtr_FrontStallErr'
                                        * 堵转标志位-副驾腿托
                                        */
INT8U PaMtr_FrontSwitchAdheErr;        /* '<S27>/PaMtr_FrontSwitchAdheErr'
                                        * 开关粘连故障标志位-副驾腿托
                                        */
INT8U PaMtr_FrontSwitchCmd;            /* '<S27>/PaMtr_FrontSwitchCmd'
                                        * 硬线开关输入请求-副驾腿托
                                        */
INT8U PaMtr_HeightHallErr;             /* '<S27>/PaMtr_HeightHallErr'
                                        * 霍故障标志位-副驾高度
                                        */
INT8U PaMtr_HeightLearnCmd;            /* '<S27>/PaMtr_HeightLearnCmd'
                                        * 学习输入请求-高度
                                        */
INT8U PaMtr_HeightMotorTimeOutErr;     /* '<S27>/PaMtr_HeightMotorTimeOutErr'
                                        * 电机运行超时标志-副驾高度
                                        */
INT8U PaMtr_HeightRelayAdhesionErr;    /* '<S27>/PaMtr_HeightRelayAdhesionErr'
                                        * 继电器粘连标志位-副驾高度
                                        */
INT8U PaMtr_HeightSoftStopErr;         /* '<S27>/PaMtr_HeightSoftStopErr'
                                        * 到达软止点-副驾高度
                                        */
INT8U PaMtr_HeightStallErr;            /* '<S27>/PaMtr_HeightStallErr'
                                        * 堵转标志位-副驾高度
                                        */
INT8U PaMtr_HeightSwitchAdheErr;       /* '<S27>/PaMtr_HeightSwitchAdheErr'
                                        * 开关粘连故障标志位-副驾高度
                                        */
INT8U PaMtr_HeightSwitchCmd;           /* '<S27>/PaMtr_HeightSwitchCmd'
                                        * 硬线开关输入请求-副驾高度
                                        */
INT8U PaMtr_LearnSts;                  /* '<S27>/PaMtr_LearnSts'
                                        * 学习状态
                                        */
INT8U PaMtr_LengthHallErr;             /* '<S27>/PaMtr_LengthHallErr'
                                        * 霍故障标志位-副驾纵向
                                        */
INT8U PaMtr_LengthLearnCmd;            /* '<S27>/PaMtr_LengthLearnCmd'
                                        * 学习输入请求-纵向
                                        */
INT8U PaMtr_LengthMotorTimeOutErr;     /* '<S27>/PaMtr_LengthMotorTimeOutErr'
                                        * 电机运行超时标志-副驾纵向
                                        */
INT8U PaMtr_LengthRelayAdhesionErr;    /* '<S27>/PaMtr_LengthRelayAdhesionErr'
                                        * 继电器粘连标志位-副驾纵向
                                        */
INT8U PaMtr_LengthSoftStopErr;         /* '<S27>/PaMtr_LengthSoftStopErr'
                                        * 到达软止点-副驾纵向
                                        */
INT8U PaMtr_LengthStallErr;            /* '<S27>/PaMtr_LengthStallErr'
                                        * 堵转标志位-副驾纵向
                                        */
INT8U PaMtr_LengthSwitchAdheErr;       /* '<S27>/PaMtr_LengthSwitchAdheErr'
                                        * 开关粘连故障标志位-副驾纵向
                                        */
INT8U PaMtr_LengthSwitchCmd;           /* '<S27>/PaMtr_LengthSwitchCmd'
                                        * 硬线开关输入请求-副驾纵向
                                        */
INT8U PaMtr_VoltSatisfy;               /* '<S27>/PaMtr_VoltSatisfy'
                                        * 电机调节电压是否满足
                                        */

/* Block signals (default storage) */
B_Appl_PaAdjustModel_T Appl_PaAdjustModel_B;

/* Block states (default storage) */
DW_Appl_PaAdjustModel_T Appl_PaAdjustModel_DW;

/* Real-time model */
RT_MODEL_Appl_PaAdjustModel_T Appl_PaAdjustModel_M_;
RT_MODEL_Appl_PaAdjustModel_T *const Appl_PaAdjustModel_M =
  &Appl_PaAdjustModel_M_;
static void Appl_PaAdjustModel_LogicCtrl_Init(void);
static void Appl_PaAdjustModel_LogicCtrl(void);
static void Appl_PaAdjustModel_RTE(void);
static void Appl_PaAdjustModel_UpDataInputInfo(void);
static void Appl_PaAdjustModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_PaAdjustMod_inner_default_MotorAdjPriorityPro(INT16U
  *SeatHeightPosiReq, INT16U *SeatLengthPosiReq, INT16U *SeatBackPosiReq, INT16U
  *SeatFrontPosiReq, INT8U *HeightManualAdjSw, INT8U *LengthManualAdjSw);
static INT32S Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts(INT32S input);
static void Appl_PaAdjustModel_H_MotorDownBackRun_m(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw);
static void Appl_PaAdjustModel_H_MotorUpFrontRun_a(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw);
static void Appl_PaAdjustModel_H_MotorDownBackRun_e(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw);
static void Appl_PaAdjustModel_H_MotorUpFrontRun_n(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw);
static void Appl_PaAdjustModel_H_MotorDownBackRun(const INT16U *SeatBackPosiReq,
  enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye *MotorActType_prev_pa);
static void Appl_PaAdjustModel_H_MotorUpFrontRun(const INT16U *SeatBackPosiReq,
  enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye *MotorActType_prev_pa);
static void Appl_PaAdjustModel_H_MotorDownBackRun_j(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq);
static void Appl_PaAdjustModel_H_MotorUpFrontRun_l(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq);

/* Function for Chart: '<S6>/PaMotorAdjustmentPriorityProcessing' */
static void Appl_PaAdjustMod_inner_default_MotorAdjPriorityPro(INT16U
  *SeatHeightPosiReq, INT16U *SeatLengthPosiReq, INT16U *SeatBackPosiReq, INT16U
  *SeatFrontPosiReq, INT8U *HeightManualAdjSw, INT8U *LengthManualAdjSw)
{
  /* 无功能请求状态 */
  Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
  *HeightManualAdjSw = 0U;
  *LengthManualAdjSw = 0U;
  Appl_PaAdjustModel_B.BackManualAdjSw = 0U;
  Appl_PaAdjustModel_B.FrontManualAdjSw = 0U;
  *SeatHeightPosiReq = 0U;
  *SeatLengthPosiReq = 0U;
  *SeatBackPosiReq = 0U;
  *SeatFrontPosiReq = 0U;
  if ((0 != PaMtr_WelcomeLengthReqPosi) || (0 != PaMtr_WelcomeBackReqPosi))
  {
    /* 舒适调节请求有效 */
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_ComfortEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_PaAdjustModel_B.BackManualAdjSw = 0U;
    Appl_PaAdjustModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = PaMtr_WelcomeLengthReqPosi;
    *SeatBackPosiReq = PaMtr_WelcomeBackReqPosi;
    *SeatFrontPosiReq = 0U;
  }

  if ((0 != PaMtr_MemoryHeightReqPosi) || (0 != PaMtr_MemoryLengthReqPosi) || (0
       != PaMtr_MemoryBackReqPosi) || (0 != PaMtr_MemoryFrontReqPosi))
  {
    /* 记忆调节请求有效 */
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_MemoryEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_PaAdjustModel_B.BackManualAdjSw = 0U;
    Appl_PaAdjustModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = PaMtr_MemoryHeightReqPosi;
    *SeatLengthPosiReq = PaMtr_MemoryLengthReqPosi;
    *SeatBackPosiReq = PaMtr_MemoryBackReqPosi;
    *SeatFrontPosiReq = PaMtr_MemoryFrontReqPosi;
  }

  /*   */
  if ((0 != PaMtr_ResetHeightReqPosi) || (0 != PaMtr_ResetLengthReqPosi) || (0
       != PaMtr_ResetBackReqPosi) || (0 != PaMtr_ResetFrontReqPosi))
  {
    /* 复位调节有效 */
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_ResetEnable;
    *HeightManualAdjSw = 0U;
    *LengthManualAdjSw = 0U;
    Appl_PaAdjustModel_B.BackManualAdjSw = 0U;
    Appl_PaAdjustModel_B.FrontManualAdjSw = 0U;
    *SeatHeightPosiReq = PaMtr_ResetHeightReqPosi;
    *SeatLengthPosiReq = PaMtr_ResetLengthReqPosi;
    *SeatBackPosiReq = PaMtr_ResetBackReqPosi;
    *SeatFrontPosiReq = PaMtr_ResetFrontReqPosi;
  }

  if ((0 != PaMtr_HeightLearnCmd) || (0 != PaMtr_LengthLearnCmd) || (0 !=
       PaMtr_BackLearnCmd) || (0 != PaMtr_FrontLearnCmd))
  {
    /* 学习调节有效 */
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_LearnEnable;
    *HeightManualAdjSw = PaMtr_HeightLearnCmd;
    *LengthManualAdjSw = PaMtr_LengthLearnCmd;
    Appl_PaAdjustModel_B.BackManualAdjSw = PaMtr_BackLearnCmd;
    Appl_PaAdjustModel_B.FrontManualAdjSw = PaMtr_FrontLearnCmd;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = 0U;
    *SeatBackPosiReq = 0U;
    *SeatFrontPosiReq = 0U;
  }

  if ((0 != PaMtr_HeightSwitchCmd) || (0 != PaMtr_LengthSwitchCmd) || (0 !=
       PaMtr_BackSwitchCmd) || (0 != PaMtr_FrontSwitchCmd))
  {
    /* 手动调节有效 */
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_ManualEnable;
    *HeightManualAdjSw = PaMtr_HeightSwitchCmd;
    *LengthManualAdjSw = PaMtr_LengthSwitchCmd;
    Appl_PaAdjustModel_B.BackManualAdjSw = PaMtr_BackSwitchCmd;
    Appl_PaAdjustModel_B.FrontManualAdjSw = PaMtr_FrontSwitchCmd;
    *SeatHeightPosiReq = 0U;
    *SeatLengthPosiReq = 0U;
    *SeatBackPosiReq = 0U;
    *SeatFrontPosiReq = 0U;
  }
}

static INT32S Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enSeatHightMotorRunsts (EN_NULL) */
  y = 0;
  if ((input >= 0) && (input <= 28))
  {
    /* Set output value to input value if it is a member of enSeatHightMotorRunsts */
    y = input;
  }

  return y;
}

/* Function for Chart: '<S20>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorDownBackRun_m(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

  /* 高度控制类型改变
     优先级需要设定为1 */
  if ((*MotorActType_prev_i != Appl_PaAdjustModel_DW.MotorActType_start_b) &&
      (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_o = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.H_MotorRunType_g =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    /* 自动调节-到达软止点停止 成功  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_PaAdjustModel_B.H_MotorRunType_g) && (q1 ==
         PaMtr_HeightSoftStopErr))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_PaAdjustModel_B.H_MotorRunType_g =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
    }
    else
    {
      /* 高度自动调节无效 设置电机运行类型BK停止 自动运行标志位失败 */
      if ((0 == *SeatHeightPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_PaAdjustModel_B.H_MotorRunType_g))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_PaAdjustModel_B.HeightAutoRunFlag_o = enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
      }
      else
      {
        /* 自动调节成功 设置电机运行类型成功停止 自动运行标志位成功 */
        tmp = PaMtr_HeightHallPosi - *SeatHeightPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_PaAdjustModel_B.H_MotorRunType_g) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
        }
        else
        {
          /*  不在软止点 且超过误差范围，需要向前驱动  */
          if ((0 != *SeatHeightPosiReq) && (*SeatHeightPosiReq >
               PaMtr_HeightHallPosi))
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_PaAdjustModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
          }
          else
          {
            /*  高度向后到达止点，存在堵转故障，反馈成功
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == PaMtr_HeightStallErr)
            {
              Appl_PaAdjustModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
            }
            else
            {
              /* 高度手动调节无效 */
              if ((q1 != *HeightManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_PaAdjustModel_B.H_MotorRunType_g))
              {
                Appl_PaAdjustModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
              }
              else
              {
                /* 高度超时停止-非继电器粘连的驱动 */
                if ((((BOOL)TRUE) == PaMtr_HeightMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != PaMtr_HeightRelayAdhesionErr))
                {
                  Appl_PaAdjustModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                }
                else
                {
                  /* 高度继电器上前粘连故障 ！= 有效 */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       PaMtr_HeightRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_PaAdjustModel_B.H_MotorRunType_g))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_g =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                  }
                  else
                  {
                    /*  存在霍尔故障
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == PaMtr_HeightHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_g =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                    }
                    else
                    {
                      /*  存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_HeigthMotorMosErr)
                      {
                        q1 = PaMtr_HeigthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                      }
                      else
                      {
                        /* 高度自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_PaAdjustModel_B.H_MotorRunType_g)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S20>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorUpFrontRun_a(const INT16U
  *SeatHeightPosiReq, enSeatMoveCmd *H_SeatMoveCmd_i, const enSeatMotorRunTye
  *MotorActType_prev_i, INT8U *HeightManualAdjSw)
{
  INT32S q1;
  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

  /* 自动调节-到达软止点停止 成功  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_PaAdjustModel_B.H_MotorRunType_g) && (q1 == PaMtr_HeightSoftStopErr))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_o = enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_PaAdjustModel_B.H_MotorRunType_g =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    /* 高度控制类型改变
       不能返回运动成功优先级需要设定为1 */
    if ((*MotorActType_prev_i != Appl_PaAdjustModel_DW.MotorActType_start_b) &&
        (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_PaAdjustModel_B.H_MotorRunType_g =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
    }
    else
    {
      /* 高度继电器下后粘连故障 != 有效 */
      if ((((INT8U)D_Relay_DownBackFault) != PaMtr_HeightRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_PaAdjustModel_B.H_MotorRunType_g))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
      }
      else
      {
        /*  高度向前到达止点，存在堵转故障，反馈成功
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == PaMtr_HeightStallErr)
        {
          Appl_PaAdjustModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
        }
        else
        {
          /* 高度手动调节无效 */
          if ((q1 != *HeightManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_PaAdjustModel_B.H_MotorRunType_g))
          {
            Appl_PaAdjustModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
          }
          else
          {
            /* 高度自动调节无效 设置电机运行类型FU停止 自动运行标志位失败 */
            if ((0 == *SeatHeightPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_PaAdjustModel_B.H_MotorRunType_g))
            {
              Appl_PaAdjustModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
            }
            else
            {
              /* 高度自动调节成功 设置电机运行类型FU成功停止 自动运行标志位成功 */
              q1 = *SeatHeightPosiReq - PaMtr_HeightHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_PaAdjustModel_B.H_MotorRunType_g) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_PaAdjustModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
              }
              else
              {
                /*  不在软止点 且超过误差范围，需要向后驱动  */
                if ((0 != *SeatHeightPosiReq) && (*SeatHeightPosiReq <
                     PaMtr_HeightHallPosi))
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_PaAdjustModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                }
                else
                {
                  /* 超时停止-非继电器粘连的驱动 */
                  if ((((BOOL)TRUE) == PaMtr_HeightMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != PaMtr_HeightRelayAdhesionErr))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_g =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                  }
                  else
                  {
                    /*  高度存在霍尔故障
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == PaMtr_HeightHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_g =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                    }
                    else
                    {
                      /*  高度存在MOS故障  */
                      if (enMosErrSts_enNULL == PaMtr_HeigthMotorMosErr)
                      {
                        q1 = PaMtr_HeigthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_g =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
                      }
                      else
                      {
                        /* 自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_PaAdjustModel_B.H_MotorRunType_g)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S21>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorDownBackRun_e(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

  /* 纵向控制类型改变
     优先级需要设定为1 */
  if ((*MotorActType_prev != Appl_PaAdjustModel_DW.MotorActType_start) &&
      (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.H_MotorRunType =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    /* 自动调节-到达软止点停止 成功  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_PaAdjustModel_B.H_MotorRunType) && (q1 == PaMtr_LengthSoftStopErr))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_PaAdjustModel_B.H_MotorRunType =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
    }
    else
    {
      /* 纵向自动调节无效 设置电机运行类型BK停止 自动运行标志位失败 */
      if ((0 == *SeatLengthPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_PaAdjustModel_B.H_MotorRunType))
      {
        Appl_PaAdjustModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
      }
      else
      {
        /* 自动调节成功 设置电机运行类型成功停止 自动运行标志位成功 */
        tmp = PaMtr_LengthHallPosi - *SeatLengthPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_PaAdjustModel_B.H_MotorRunType) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
        }
        else
        {
          /*  不在软止点 且超过误差范围，需要向前驱动  */
          if ((0 != *SeatLengthPosiReq) && (*SeatLengthPosiReq >
               PaMtr_LengthHallPosi))
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_PaAdjustModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
          }
          else
          {
            /*  纵向向后到达止点，存在堵转故障，反馈成功
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == PaMtr_LengthStallErr)
            {
              Appl_PaAdjustModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
            }
            else
            {
              /* 纵向手动调节无效 */
              if ((q1 != *LengthManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_PaAdjustModel_B.H_MotorRunType))
              {
                Appl_PaAdjustModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
              }
              else
              {
                /* 纵向超时停止-非继电器粘连的驱动 */
                if ((((BOOL)TRUE) == PaMtr_LengthMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != PaMtr_LengthRelayAdhesionErr))
                {
                  Appl_PaAdjustModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_PaAdjustModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                }
                else
                {
                  /* 纵向继电器上前粘连故障 ！= 有效 */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       PaMtr_LengthRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_PaAdjustModel_B.H_MotorRunType))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                  }
                  else
                  {
                    /*  存在MOS故障  */
                    if (enMosErrSts_enNULL != PaMtr_LengthMotorMosErr)
                    {
                      q1 = PaMtr_LengthMotorMosErr;
                      if (q1 > 2147483626)
                      {
                        Appl_PaAdjustModel_B.H_MotorRunType =
                          (enSeatHightMotorRunsts)
                          Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                          (MAX_int32_T);
                      }
                      else
                      {
                        Appl_PaAdjustModel_B.H_MotorRunType =
                          (enSeatHightMotorRunsts)
                          Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts(21
                          + q1);
                      }

                      Appl_PaAdjustModel_B.HeightAutoRunFlag =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                    }
                    else
                    {
                      /*  存在霍尔故障
                         FALSE == Relay_FaultSts && */
                      if (((BOOL)TRUE) == PaMtr_LengthHallErr)
                      {
                        Appl_PaAdjustModel_B.H_MotorRunType =
                          enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                        Appl_PaAdjustModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                      }
                      else
                      {
                        /* 纵向自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_PaAdjustModel_B.H_MotorRunType)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S21>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorUpFrontRun_n(const INT16U
  *SeatLengthPosiReq, enSeatMoveCmd *H_SeatMoveCmd, const enSeatMotorRunTye
  *MotorActType_prev, INT8U *LengthManualAdjSw)
{
  INT32S q1;
  *H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

  /* 自动调节-到达软止点停止 成功  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_PaAdjustModel_B.H_MotorRunType) && (q1 == PaMtr_LengthSoftStopErr))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_PaAdjustModel_B.H_MotorRunType =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    /* 纵向控制类型改变
       不能返回运动成功优先级需要设定为1 */
    if ((*MotorActType_prev != Appl_PaAdjustModel_DW.MotorActType_start) &&
        (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_PaAdjustModel_B.H_MotorRunType =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
    }
    else
    {
      /* 纵向继电器下后粘连故障 != 有效 */
      if ((((INT8U)D_Relay_DownBackFault) != PaMtr_LengthRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_PaAdjustModel_B.H_MotorRunType))
      {
        Appl_PaAdjustModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
      }
      else
      {
        /*  纵向向前到达止点，存在堵转故障，反馈成功
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == PaMtr_LengthStallErr)
        {
          Appl_PaAdjustModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_PaAdjustModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
        }
        else
        {
          /* 纵向手动调节无效 */
          if ((q1 != *LengthManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_PaAdjustModel_B.H_MotorRunType))
          {
            Appl_PaAdjustModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
          }
          else
          {
            /* 纵向自动调节无效 设置电机运行类型FU停止 自动运行标志位失败 */
            if ((0 == *SeatLengthPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_PaAdjustModel_B.H_MotorRunType))
            {
              Appl_PaAdjustModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
            }
            else
            {
              /* 纵向自动调节成功 设置电机运行类型FU成功停止 自动运行标志位成功 */
              q1 = *SeatLengthPosiReq - PaMtr_LengthHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_PaAdjustModel_B.H_MotorRunType) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_PaAdjustModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
              }
              else
              {
                /*  不在软止点 且超过误差范围，需要向后驱动  */
                if ((0 != *SeatLengthPosiReq) && (*SeatLengthPosiReq <
                     PaMtr_LengthHallPosi))
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_PaAdjustModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                }
                else
                {
                  /* 纵向超时停止-非继电器粘连的驱动 */
                  if ((((BOOL)TRUE) == PaMtr_LengthMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != PaMtr_LengthRelayAdhesionErr))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_PaAdjustModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                  }
                  else
                  {
                    /*  纵向存在霍尔故障
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == PaMtr_LengthHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                    }
                    else
                    {
                      /*  纵向存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_LengthMotorMosErr)
                      {
                        q1 = PaMtr_LengthMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
                      }
                      else
                      {
                        /* 自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_PaAdjustModel_B.H_MotorRunType)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S18>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorDownBackRun(const INT16U *SeatBackPosiReq,
  enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye *MotorActType_prev_pa)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

  /* 靠背控制类型改变
     优先级需要设定为1 */
  if ((*MotorActType_prev_pa != Appl_PaAdjustModel_DW.MotorActType_start_n) &&
      (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_g = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.H_MotorRunType_m =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    /* 自动调节-到达软止点停止 成功  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_PaAdjustModel_B.H_MotorRunType_m) && (q1 == PaMtr_BackSoftStopErr))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_PaAdjustModel_B.H_MotorRunType_m =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
    }
    else
    {
      /* 靠背自动调节无效 设置电机运行类型BK停止 自动运行标志位失败 */
      if ((0 == *SeatBackPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_PaAdjustModel_B.H_MotorRunType_m))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_PaAdjustModel_B.HeightAutoRunFlag_g = enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
      }
      else
      {
        /* 自动调节成功 设置电机运行类型成功停止 自动运行标志位成功 */
        tmp = PaMtr_BackHallPosi - *SeatBackPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_PaAdjustModel_B.H_MotorRunType_m) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
        }
        else
        {
          /*  不在软止点 且超过误差范围，需要向前驱动  */
          if ((0 != *SeatBackPosiReq) && (*SeatBackPosiReq > PaMtr_BackHallPosi))
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_PaAdjustModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
          }
          else
          {
            /*  靠背向后到达止点，存在堵转故障，反馈成功
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == PaMtr_BackStallErr)
            {
              Appl_PaAdjustModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
            }
            else
            {
              /* 靠背手动调节无效 */
              if ((q1 != Appl_PaAdjustModel_B.BackManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_PaAdjustModel_B.H_MotorRunType_m))
              {
                Appl_PaAdjustModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
              }
              else
              {
                /* 靠背超时停止-非继电器粘连的驱动 */
                if ((((BOOL)TRUE) == PaMtr_BackMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != PaMtr_BackRelayAdhesionErr))
                {
                  Appl_PaAdjustModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                }
                else
                {
                  /* 靠背继电器上前粘连故障 ！= 有效 */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       PaMtr_BackRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_PaAdjustModel_B.H_MotorRunType_m))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_m =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                  }
                  else
                  {
                    /*  存在霍尔故障
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == PaMtr_BackHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_m =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                    }
                    else
                    {
                      /*  存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_BackMotorMosErr)
                      {
                        q1 = PaMtr_BackMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                      }
                      else
                      {
                        /* 靠背自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_PaAdjustModel_B.H_MotorRunType_m)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S18>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorUpFrontRun(const INT16U *SeatBackPosiReq,
  enSeatMoveCmd *H_SeatMoveCmd_e, const enSeatMotorRunTye *MotorActType_prev_pa)
{
  INT32S q1;
  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

  /* 自动调节-到达软止点停止 成功  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_PaAdjustModel_B.H_MotorRunType_m) && (q1 == PaMtr_BackSoftStopErr))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_g = enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_PaAdjustModel_B.H_MotorRunType_m =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    /* 靠背控制类型改变
       不能返回运动成功优先级需要设定为1 */
    if ((*MotorActType_prev_pa != Appl_PaAdjustModel_DW.MotorActType_start_n) &&
        (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_PaAdjustModel_B.H_MotorRunType_m =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
    }
    else
    {
      /* 靠背继电器下后粘连故障 != 有效 */
      if ((((INT8U)D_Relay_DownBackFault) != PaMtr_BackRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_PaAdjustModel_B.H_MotorRunType_m))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
      }
      else
      {
        /*  靠背向前到达止点，存在堵转故障，反馈成功
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == PaMtr_BackStallErr)
        {
          Appl_PaAdjustModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
        }
        else
        {
          /* 靠背手动调节无效 */
          if ((q1 != Appl_PaAdjustModel_B.BackManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_PaAdjustModel_B.H_MotorRunType_m))
          {
            Appl_PaAdjustModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
          }
          else
          {
            /* 靠背自动调节无效 设置电机运行类型FU停止 自动运行标志位失败 */
            if ((0 == *SeatBackPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_PaAdjustModel_B.H_MotorRunType_m))
            {
              Appl_PaAdjustModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
            }
            else
            {
              /* 靠背自动调节成功 设置电机运行类型FU成功停止 自动运行标志位成功 */
              q1 = *SeatBackPosiReq - PaMtr_BackHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_PaAdjustModel_B.H_MotorRunType_m) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_PaAdjustModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
              }
              else
              {
                /*  不在软止点 且超过误差范围，需要向后驱动  */
                if ((0 != *SeatBackPosiReq) && (*SeatBackPosiReq <
                     PaMtr_BackHallPosi))
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_PaAdjustModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                }
                else
                {
                  /* 靠背超时停止-非继电器粘连的驱动 */
                  if ((((BOOL)TRUE) == PaMtr_BackMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != PaMtr_BackRelayAdhesionErr))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_m =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                  }
                  else
                  {
                    /*  靠背存在霍尔故障
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == PaMtr_BackHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_m =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                    }
                    else
                    {
                      /*  靠背存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_BackMotorMosErr)
                      {
                        q1 = PaMtr_BackMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_m =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
                      }
                      else
                      {
                        /* 自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_PaAdjustModel_B.H_MotorRunType_m)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S19>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorDownBackRun_j(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq)
{
  INT32S tmp;
  INT32S q1;
  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

  /* 腿托控制类型改变
     优先级需要设定为1 */
  if ((*MotorActType_prev_p != Appl_PaAdjustModel_DW.MotorActType_start_l) &&
      (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_p = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.H_MotorRunType_l =
      enSeatHightMotorRunsts_EN_DnBa_MovTypeChange;
    Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    /* 自动调节-到达软止点停止 成功  */
    q1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
         Appl_PaAdjustModel_B.H_MotorRunType_l) && (q1 == PaMtr_FrontSoftStopErr))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
        enSeatAutoRunSts_EN_SEAT_SUCCESS;
      Appl_PaAdjustModel_B.H_MotorRunType_l =
        enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
      Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
    }
    else
    {
      /* 腿托自动调节无效 设置电机运行类型BK停止 自动运行标志位失败 */
      if ((0 == *SeatFrontPosiReq) && (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
           Appl_PaAdjustModel_B.H_MotorRunType_l))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
        Appl_PaAdjustModel_B.HeightAutoRunFlag_p = enSeatAutoRunSts_EN_SEAT_FAIL;
        Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
      }
      else
      {
        /* 自动调节成功 设置电机运行类型成功停止 自动运行标志位成功 */
        tmp = PaMtr_FrontHallPosi - *SeatFrontPosiReq;
        if (tmp < 0)
        {
          tmp = -tmp;
        }

        if ((enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
             Appl_PaAdjustModel_B.H_MotorRunType_l) && (((INT16U)
              D_ToleranceDistance) >= tmp))
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
          Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
        }
        else
        {
          /*  不在软止点 且超过误差范围，需要向前驱动  */
          if ((0 != *SeatFrontPosiReq) && (*SeatFrontPosiReq >
               PaMtr_FrontHallPosi))
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_INVALID;
            Appl_PaAdjustModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_AutoAdjust_BK_Stop;
            Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
          }
          else
          {
            /*  腿托向后到达止点，存在堵转故障，反馈成功
               FALSE == Relay_FaultSts && */
            if (((BOOL)TRUE) == PaMtr_FrontStallErr)
            {
              Appl_PaAdjustModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_DnBa_Lock_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_SUCCESS;
              Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
            }
            else
            {
              /* 腿托手动调节无效 */
              if ((q1 != Appl_PaAdjustModel_B.FrontManualAdjSw) &&
                  (enSeatHightMotorRunsts_EN_ManualAdjust_BK ==
                   Appl_PaAdjustModel_B.H_MotorRunType_l))
              {
                Appl_PaAdjustModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_ManualAdjust_BK_Stop;
                Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
              }
              else
              {
                /* 腿托超时停止-非继电器粘连的驱动 */
                if ((((BOOL)TRUE) == PaMtr_FrontMotorTimeOutErr) && (((INT8U)
                      D_Relay_UpFrontFault) != PaMtr_FrontRelayAdhesionErr))
                {
                  Appl_PaAdjustModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_AutoAdjust_BKSuccess_Stop;
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_FAIL;
                  Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                }
                else
                {
                  /* 腿托继电器上前粘连故障 ！= 有效 */
                  if ((((INT8U)D_Relay_UpFrontFault) !=
                       PaMtr_FrontRelayAdhesionErr) &&
                      (enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK ==
                       Appl_PaAdjustModel_B.H_MotorRunType_l))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_l =
                      enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK_Stop;
                    Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                  }
                  else
                  {
                    /*  存在霍尔故障
                       FALSE == Relay_FaultSts && */
                    if (((BOOL)TRUE) == PaMtr_FrontHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_l =
                        enSeatHightMotorRunsts_EN_DnBa_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                    }
                    else
                    {
                      /*  存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_FrontMotorMosErr)
                      {
                        q1 = PaMtr_FrontMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                      }
                      else
                      {
                        /* 腿托自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                            Appl_PaAdjustModel_B.H_MotorRunType_l)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* Function for Chart: '<S19>/MotorAdjust' */
static void Appl_PaAdjustModel_H_MotorUpFrontRun_l(enSeatMoveCmd
  *H_SeatMoveCmd_p, const enSeatMotorRunTye *MotorActType_prev_p, INT16U
  *SeatFrontPosiReq)
{
  INT32S q1;
  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

  /* 自动调节-到达软止点停止 成功  */
  q1 = enSeatMoveCmd_EN_UP_FORWARD;
  if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
       Appl_PaAdjustModel_B.H_MotorRunType_l) && (q1 == PaMtr_FrontSoftStopErr))
  {
    Appl_PaAdjustModel_B.HeightAutoRunFlag_p = enSeatAutoRunSts_EN_SEAT_SUCCESS;
    Appl_PaAdjustModel_B.H_MotorRunType_l =
      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
    Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    /* 腿托控制类型改变
       不能返回运动成功优先级需要设定为1 */
    if ((*MotorActType_prev_p != Appl_PaAdjustModel_DW.MotorActType_start_l) &&
        (enSeatMotorRunTye_EN_NULL != Appl_PaAdjustModel_B.MotorActionType))
    {
      Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
        enSeatAutoRunSts_EN_SEAT_INVALID;
      Appl_PaAdjustModel_B.H_MotorRunType_l =
        enSeatHightMotorRunsts_EN_UpFn_MovTypeChange;
      Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init_Interval;
      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
      Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
      Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
    }
    else
    {
      /* 腿托继电器下后粘连故障 != 有效 */
      if ((((INT8U)D_Relay_DownBackFault) != PaMtr_FrontRelayAdhesionErr) &&
          (enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU ==
           Appl_PaAdjustModel_B.H_MotorRunType_l))
      {
        Appl_PaAdjustModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU_Stop;
        Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_Init_Interval;
        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
        Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
        Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
      }
      else
      {
        /*  腿托向前到达止点，存在堵转故障，反馈成功
           FALSE == Relay_FaultSts && */
        if (((BOOL)TRUE) == PaMtr_FrontStallErr)
        {
          Appl_PaAdjustModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_UpFn_Lock_Stop;
          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_SUCCESS;
          Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_Init_Interval;
          *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
          Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
          Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
        }
        else
        {
          /* 腿托手动调节无效 */
          if ((q1 != Appl_PaAdjustModel_B.FrontManualAdjSw) &&
              (enSeatHightMotorRunsts_EN_ManualAdjust_FU ==
               Appl_PaAdjustModel_B.H_MotorRunType_l))
          {
            Appl_PaAdjustModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU_Stop;
            Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_Init_Interval;
            *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
            Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
            Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
          }
          else
          {
            /* 腿托自动调节无效 设置电机运行类型FU停止 自动运行标志位失败 */
            if ((0 == *SeatFrontPosiReq) &&
                (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                 Appl_PaAdjustModel_B.H_MotorRunType_l))
            {
              Appl_PaAdjustModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
              Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_FAIL;
              Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_Init_Interval;
              *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
              Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
              Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
            }
            else
            {
              /* 腿托自动调节成功 设置电机运行类型FU成功停止 自动运行标志位成功 */
              q1 = *SeatFrontPosiReq - PaMtr_FrontHallPosi;
              if (q1 < 0)
              {
                q1 = -q1;
              }

              if ((enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                   Appl_PaAdjustModel_B.H_MotorRunType_l) && (((INT16U)
                    D_ToleranceDistance) >= q1))
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_SUCCESS;
                Appl_PaAdjustModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_Init_Interval;
                *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
              }
              else
              {
                /*  不在软止点 且超过误差范围，需要向后驱动  */
                if ((0 != *SeatFrontPosiReq) && (*SeatFrontPosiReq <
                     PaMtr_FrontHallPosi))
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                  Appl_PaAdjustModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_AutoAdjust_FU_Stop;
                  Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_Init_Interval;
                  *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                  Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                }
                else
                {
                  /* 腿托超时停止-非继电器粘连的驱动 */
                  if ((((BOOL)TRUE) == PaMtr_FrontMotorTimeOutErr) && (((INT8U)
                        D_Relay_DownBackFault) != PaMtr_FrontRelayAdhesionErr))
                  {
                    Appl_PaAdjustModel_B.H_MotorRunType_l =
                      enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_FAIL;
                    Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                      Appl_PaAdjustModel_IN_Init_Interval;
                    *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                    Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                    Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                  }
                  else
                  {
                    /*  腿托存在霍尔故障
                       FALSE == Relay_FaultSts &&  */
                    if (((BOOL)TRUE) == PaMtr_FrontHallErr)
                    {
                      Appl_PaAdjustModel_B.H_MotorRunType_l =
                        enSeatHightMotorRunsts_EN_UpFn_Hall_Stop;
                      Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                        enSeatAutoRunSts_EN_SEAT_FAIL;
                      Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                        Appl_PaAdjustModel_IN_Init_Interval;
                      *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                      Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                      Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                      Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                    }
                    else
                    {
                      /*  腿托存在MOS故障  */
                      if (enMosErrSts_enNULL != PaMtr_FrontMotorMosErr)
                      {
                        q1 = PaMtr_FrontMotorMosErr;
                        if (q1 > 2147483626)
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (MAX_int32_T);
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.H_MotorRunType_l =
                            (enSeatHightMotorRunsts)
                            Appl_PaAdjustM_safe_cast_to_enSeatHightMotorRunsts
                            (21 + q1);
                        }

                        Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_FAIL;
                        Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                          Appl_PaAdjustModel_IN_Init_Interval;
                        *H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
                        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
                        Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                        Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
                      }
                      else
                      {
                        /* 自动调节 */
                        if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                            Appl_PaAdjustModel_B.H_MotorRunType_l)
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_RUNNING;
                        }
                        else
                        {
                          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                            enSeatAutoRunSts_EN_SEAT_INVALID;
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

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaAdjustModel_LogicCtrl_Init(void)
{
  Appl_PaAdjustModel_DW.is_active_c2_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
  Appl_PaAdjustModel_B.BackManualAdjSw = 0U;
  Appl_PaAdjustModel_B.FrontManualAdjSw = 0U;
  Appl_PaAdjustModel_DW.is_active_c4_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel = 0;
  Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
  Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 10U;
  Appl_PaAdjustModel_B.H_MotorRunType_g = enSeatHightMotorRunsts_EN_NULL;
  Appl_PaAdjustModel_B.HeightAutoRunFlag_o = enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_PaAdjustModel_DW.is_active_c18_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel = 0;
  Appl_PaAdjustModel_DW.DownBackFlag = 0U;
  Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
  Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 10U;
  Appl_PaAdjustModel_B.H_MotorRunType = enSeatHightMotorRunsts_EN_NULL;
  Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_PaAdjustModel_DW.is_active_c19_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel = 0;
  Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
  Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 10U;
  Appl_PaAdjustModel_B.H_MotorRunType_m = enSeatHightMotorRunsts_EN_NULL;
  Appl_PaAdjustModel_B.HeightAutoRunFlag_g = enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_PaAdjustModel_DW.is_active_c21_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel = 0;
  Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
  Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 10U;
  Appl_PaAdjustModel_B.H_MotorRunType_l = enSeatHightMotorRunsts_EN_NULL;
  Appl_PaAdjustModel_B.HeightAutoRunFlag_p = enSeatAutoRunSts_EN_SEAT_INVALID;
  Appl_PaAdjustModel_DW.is_active_c17_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.is_c17_Appl_PaAdjustModel = 0;
  Appl_PaAdjustModel_B.HeightMotorCmd = 0U;
  Appl_PaAdjustModel_B.LengthMotorCmd = 0U;
  Appl_PaAdjustModel_B.BackMotorCmd = 0U;
  Appl_PaAdjustModel_B.FrontMotorCmd = 0U;
  Appl_PaAdjustModel_DW.is_BackAdjust = 0;
  Appl_PaAdjustModel_DW.is_FrontAngleAdjust = 0;
  Appl_PaAdjustModel_DW.is_HeightAdjust = 0;
  Appl_PaAdjustModel_DW.is_VerticalAdjust = 0;
  Appl_PaAdjustModel_DW.is_active_c16_Appl_PaAdjustModel = 0U;
  Appl_PaAdjustModel_DW.FrontTimer = 0U;
  Appl_PaAdjustModel_DW.HeightTimer = 0U;
  Appl_PaAdjustModel_DW.LengthTimer = 0U;
  Appl_PaAdjustModel_DW.BackTimer = 0U;
  Appl_PaAdjustModel_B.Can_HeightMotorCtrl = 0U;
  Appl_PaAdjustModel_B.Can_LengthMotorCtrl = 0U;
  Appl_PaAdjustModel_B.Can_BackMotorCtrl = 0U;
  Appl_PaAdjustModel_B.Can_FrontMotorCtrl = 0U;
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_PaAdjustModel_LogicCtrl(void)
{
  INT16U SeatHeightPosiReq;
  INT16U SeatLengthPosiReq;
  INT16U SeatBackPosiReq;
  enSeatMoveCmd H_SeatMoveCmd_i;
  enSeatMoveCmd H_SeatMoveCmd;
  enSeatMoveCmd H_SeatMoveCmd_e;
  enSeatMoveCmd H_SeatMoveCmd_p;
  INT16U SeatHeightPosiReq_prev_j;
  enSeatMotorRunTye MotorActType_prev_i;
  INT16U SeatFrontPosiReq;
  INT8U HeightManualAdjSw;
  INT8U LengthManualAdjSw;
  INT32S tmp;
  INT32S tmp_0;
  INT32S tmp_1;
  if (Appl_PaAdjustModel_DW.is_active_c2_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c2_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustMod_inner_default_MotorAdjPriorityPro(&SeatHeightPosiReq,
      &SeatLengthPosiReq, &SeatBackPosiReq, &SeatFrontPosiReq,
      &HeightManualAdjSw, &LengthManualAdjSw);
  }
  else
  {
    Appl_PaAdjustMod_inner_default_MotorAdjPriorityPro(&SeatHeightPosiReq,
      &SeatLengthPosiReq, &SeatBackPosiReq, &SeatFrontPosiReq,
      &HeightManualAdjSw, &LengthManualAdjSw);
  }

  SeatHeightPosiReq_prev_j = Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_o;
  Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_o = SeatHeightPosiReq;
  MotorActType_prev_i = Appl_PaAdjustModel_DW.MotorActType_start_b;
  Appl_PaAdjustModel_DW.MotorActType_start_b =
    Appl_PaAdjustModel_B.MotorActionType;
  if (Appl_PaAdjustModel_DW.is_active_c4_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c4_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;
  }
  else
  {
    switch (Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel)
    {
     case Appl_PaAdjustModel_IN_H_MotorDownBackRun:
      Appl_PaAdjustModel_H_MotorDownBackRun_m(&SeatHeightPosiReq,
        &H_SeatMoveCmd_i, &MotorActType_prev_i, &HeightManualAdjSw);
      break;

     case Appl_PaAdjustModel_IN_H_MotorUpFrontRun:
      Appl_PaAdjustModel_H_MotorUpFrontRun_a(&SeatHeightPosiReq,
        &H_SeatMoveCmd_i, &MotorActType_prev_i, &HeightManualAdjSw);
      break;

     default:
      H_SeatMoveCmd_i = enSeatMoveCmd_EN_NULL;

      /* 高度继电器上前粘连故障 == 有效 */
      if ((((INT8U)D_Relay_UpFrontFault) == PaMtr_HeightRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
      {
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
        Appl_PaAdjustModel_B.H_MotorRunType_g =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

        /* 高度自动调节 */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_PaAdjustModel_B.H_MotorRunType_g)
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* 高度自动调节有效且不在误差范围内 */
        if ((0 != SeatHeightPosiReq) && (((BOOL)FALSE) == PaMtr_HeightStallErr) &&
            (Appl_PaAdjustModel_B.HeightAutoRunFlag_o ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_PaAdjustModel_DW.DownBackFlag_k == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
        {
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
          Appl_PaAdjustModel_B.H_MotorRunType_g =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

          /* 高度自动调节 */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_PaAdjustModel_B.H_MotorRunType_g)
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* 高度手动调节 */
          tmp_0 = enSeatMoveCmd_EN_UP_FORWARD;
          if ((tmp_0 == HeightManualAdjSw) && (((BOOL)FALSE) ==
               PaMtr_HeightStallErr) && (((BOOL)FALSE) == PaMtr_HeightHallErr) &&
              (((BOOL)FALSE) == PaMtr_HeightMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
          {
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
            Appl_PaAdjustModel_B.H_MotorRunType_g =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

            /* 自动调节 */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_PaAdjustModel_B.H_MotorRunType_g)
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* 高度继电器下后粘连故障 == 有效 间隔时间大于100ms */
            if ((((INT8U)D_Relay_DownBackFault) == PaMtr_HeightRelayAdhesionErr)
                && (CAL_HightMotorRunInterval_100ms <=
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
            {
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
              Appl_PaAdjustModel_B.H_MotorRunType_g =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

              /* 自动调节 */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_PaAdjustModel_B.H_MotorRunType_g)
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* 高度自动调节有效且不在误差范围内 */
              if ((0 != SeatHeightPosiReq) && (((BOOL)FALSE) ==
                   PaMtr_HeightStallErr) &&
                  (Appl_PaAdjustModel_B.HeightAutoRunFlag_o ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_PaAdjustModel_DW.UpFrontFlag_g == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
              {
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
                Appl_PaAdjustModel_B.H_MotorRunType_g =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_i = enSeatMoveCmd_EN_UP_FORWARD;

                /* 自动调节 */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_PaAdjustModel_B.H_MotorRunType_g)
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* 高度手动调节有效 */
                tmp_1 = enSeatMoveCmd_EN_DN_BACKWARD;
                if ((tmp_1 == HeightManualAdjSw) && (((BOOL)FALSE) ==
                     PaMtr_HeightStallErr) && (((BOOL)FALSE) ==
                     PaMtr_HeightHallErr) && (((BOOL)FALSE) ==
                     PaMtr_HeightMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e))
                {
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = 0U;
                  Appl_PaAdjustModel_B.H_MotorRunType_g =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_PaAdjustModel_DW.is_c4_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_i = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* 高度自动调节 */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_PaAdjustModel_B.H_MotorRunType_g)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* 高度电机调间隔时间 */
                  if (Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp = Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e + 1;
                    if (tmp > 255)
                    {
                      tmp = 255;
                    }

                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_e = (INT8U)tmp;
                  }

                  Appl_PaAdjustModel_DW.DownBackFlag_k = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_g = 0U;

                  /* 高度自动调节有效 */
                  if (0 != SeatHeightPosiReq)
                  {
                    /* 高度误差判断目前定义为5霍尔数值 */
                    if ((tmp_0 != PaMtr_HeightSoftStopErr) && (SeatHeightPosiReq
                         > PaMtr_HeightHallPosi) && (((INT16U)
                          D_ToleranceDistance) < SeatHeightPosiReq -
                         PaMtr_HeightHallPosi))
                    {
                      Appl_PaAdjustModel_DW.UpFrontFlag_g = 1U;
                    }
                    else
                    {
                      /*  不在软止点 且超误差范围  */
                      if ((tmp_1 != PaMtr_HeightSoftStopErr) &&
                          (SeatHeightPosiReq < PaMtr_HeightHallPosi) &&
                          (((INT16U)D_ToleranceDistance) < PaMtr_HeightHallPosi
                           - SeatHeightPosiReq))
                      {
                        Appl_PaAdjustModel_DW.DownBackFlag_k = 1U;
                      }
                      else
                      {
                        /* 高度误差范围内，反馈成功 */
                        Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_PaAdjustModel_B.H_MotorRunType_g =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  调用位置有变化 则先清状态  */
                  if (SeatHeightPosiReq_prev_j !=
                      Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_o)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_o =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
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

  SeatHeightPosiReq = Appl_PaAdjustModel_DW.SeatHeightPosiReq_start;
  Appl_PaAdjustModel_DW.SeatHeightPosiReq_start = SeatLengthPosiReq;
  MotorActType_prev_i = Appl_PaAdjustModel_DW.MotorActType_start;
  Appl_PaAdjustModel_DW.MotorActType_start =
    Appl_PaAdjustModel_B.MotorActionType;
  if (Appl_PaAdjustModel_DW.is_active_c18_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c18_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag = 0U;
  }
  else
  {
    switch (Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel)
    {
     case Appl_PaAdjustModel_IN_H_MotorDownBackRun:
      Appl_PaAdjustModel_H_MotorDownBackRun_e(&SeatLengthPosiReq, &H_SeatMoveCmd,
        &MotorActType_prev_i, &LengthManualAdjSw);
      break;

     case Appl_PaAdjustModel_IN_H_MotorUpFrontRun:
      Appl_PaAdjustModel_H_MotorUpFrontRun_n(&SeatLengthPosiReq, &H_SeatMoveCmd,
        &MotorActType_prev_i, &LengthManualAdjSw);
      break;

     default:
      H_SeatMoveCmd = enSeatMoveCmd_EN_NULL;

      /* 纵向继电器上前粘连故障 == 有效 */
      if ((((INT8U)D_Relay_UpFrontFault) == PaMtr_LengthRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
      {
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
        Appl_PaAdjustModel_B.H_MotorRunType =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

        /* 纵向自动调节 */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_PaAdjustModel_B.H_MotorRunType)
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* 纵向自动调节有效且不在误差范围内 */
        if ((0 != SeatLengthPosiReq) && (((BOOL)FALSE) == PaMtr_LengthStallErr) &&
            (Appl_PaAdjustModel_B.HeightAutoRunFlag ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_PaAdjustModel_DW.DownBackFlag == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
        {
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
          Appl_PaAdjustModel_B.H_MotorRunType =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

          /* 纵向自动调节 */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_PaAdjustModel_B.H_MotorRunType)
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* 纵向手动调节 */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD == LengthManualAdjSw) &&
              (((BOOL)FALSE) == PaMtr_LengthStallErr) && (((BOOL)FALSE) ==
               PaMtr_LengthHallErr) && (((BOOL)FALSE) ==
               PaMtr_LengthMotorTimeOutErr) && (CAL_HightMotorRunInterval_100ms <=
               Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
          {
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
            Appl_PaAdjustModel_B.H_MotorRunType =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

            /* 自动调节 */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_PaAdjustModel_B.H_MotorRunType)
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* 纵向继电器下后粘连故障 == 有效 间隔时间大于100ms */
            if ((((INT8U)D_Relay_DownBackFault) == PaMtr_LengthRelayAdhesionErr)
                && (CAL_HightMotorRunInterval_100ms <=
                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
            {
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
              Appl_PaAdjustModel_B.H_MotorRunType =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

              /* 自动调节 */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_PaAdjustModel_B.H_MotorRunType)
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* 纵向自动调节有效且不在误差范围内 */
              if ((0 != SeatLengthPosiReq) && (((BOOL)FALSE) ==
                   PaMtr_LengthStallErr) &&
                  (Appl_PaAdjustModel_B.HeightAutoRunFlag ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_PaAdjustModel_DW.UpFrontFlag == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
              {
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
                Appl_PaAdjustModel_B.H_MotorRunType =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd = enSeatMoveCmd_EN_UP_FORWARD;

                /* 自动调节 */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_PaAdjustModel_B.H_MotorRunType)
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* 纵向手动调节有效 */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD == LengthManualAdjSw) &&
                    (((BOOL)FALSE) == PaMtr_LengthStallErr) && (((BOOL)FALSE) ==
                     PaMtr_LengthHallErr) && (((BOOL)FALSE) ==
                     PaMtr_LengthMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_PaAdjustModel_DW.HMotorRunIntervalTime))
                {
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime = 0U;
                  Appl_PaAdjustModel_B.H_MotorRunType =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_PaAdjustModel_DW.is_c18_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* 纵向自动调节 */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_PaAdjustModel_B.H_MotorRunType)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* 纵向电机调间隔时间 */
                  if (Appl_PaAdjustModel_DW.HMotorRunIntervalTime <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 = Appl_PaAdjustModel_DW.HMotorRunIntervalTime + 1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime = (INT8U)tmp_0;
                  }

                  Appl_PaAdjustModel_DW.DownBackFlag = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag = 0U;

                  /* 纵向自动调节有效 */
                  if (0 != SeatLengthPosiReq)
                  {
                    /* 纵向误差判断目前定义为5霍尔数值 */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         PaMtr_LengthSoftStopErr) && (SeatLengthPosiReq >
                         PaMtr_LengthHallPosi) && (((INT16U)D_ToleranceDistance)
                         < SeatLengthPosiReq - PaMtr_LengthHallPosi))
                    {
                      Appl_PaAdjustModel_DW.UpFrontFlag = 1U;
                    }
                    else
                    {
                      /*  不在软止点 且超误差范围  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           PaMtr_LengthSoftStopErr) && (SeatLengthPosiReq <
                           PaMtr_LengthHallPosi) && (((INT16U)
                            D_ToleranceDistance) < PaMtr_LengthHallPosi -
                           SeatLengthPosiReq))
                      {
                        Appl_PaAdjustModel_DW.DownBackFlag = 1U;
                      }
                      else
                      {
                        /* 纵向误差范围内，反馈成功 */
                        Appl_PaAdjustModel_B.HeightAutoRunFlag =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_PaAdjustModel_B.H_MotorRunType =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  调用位置有变化 则先清状态  */
                  if (SeatHeightPosiReq !=
                      Appl_PaAdjustModel_DW.SeatHeightPosiReq_start)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
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

  SeatLengthPosiReq = Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_j;
  Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_j = SeatBackPosiReq;
  MotorActType_prev_i = Appl_PaAdjustModel_DW.MotorActType_start_n;
  Appl_PaAdjustModel_DW.MotorActType_start_n =
    Appl_PaAdjustModel_B.MotorActionType;
  if (Appl_PaAdjustModel_DW.is_active_c19_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c19_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;
  }
  else
  {
    switch (Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel)
    {
     case Appl_PaAdjustModel_IN_H_MotorDownBackRun:
      Appl_PaAdjustModel_H_MotorDownBackRun(&SeatBackPosiReq, &H_SeatMoveCmd_e,
        &MotorActType_prev_i);
      break;

     case Appl_PaAdjustModel_IN_H_MotorUpFrontRun:
      Appl_PaAdjustModel_H_MotorUpFrontRun(&SeatBackPosiReq, &H_SeatMoveCmd_e,
        &MotorActType_prev_i);
      break;

     default:
      H_SeatMoveCmd_e = enSeatMoveCmd_EN_NULL;

      /* 靠背继电器上前粘连故障 == 有效 */
      if ((((INT8U)D_Relay_UpFrontFault) == PaMtr_BackRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
      {
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
        Appl_PaAdjustModel_B.H_MotorRunType_m =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

        /* 靠背自动调节 */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_PaAdjustModel_B.H_MotorRunType_m)
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* 靠背自动调节有效且不在误差范围内 */
        if ((0 != SeatBackPosiReq) && (((BOOL)FALSE) == PaMtr_BackStallErr) &&
            (Appl_PaAdjustModel_B.HeightAutoRunFlag_g ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_PaAdjustModel_DW.DownBackFlag_c == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
        {
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
          Appl_PaAdjustModel_B.H_MotorRunType_m =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

          /* 靠背自动调节 */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_PaAdjustModel_B.H_MotorRunType_m)
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* 靠背手动调节 */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD ==
               Appl_PaAdjustModel_B.BackManualAdjSw) && (((BOOL)FALSE) ==
               PaMtr_BackStallErr) && (((BOOL)FALSE) == PaMtr_BackHallErr) &&
              (((BOOL)FALSE) == PaMtr_BackMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
          {
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
            Appl_PaAdjustModel_B.H_MotorRunType_m =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

            /* 自动调节 */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_PaAdjustModel_B.H_MotorRunType_m)
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* 靠背继电器下后粘连故障 == 有效 间隔时间大于100ms */
            if ((((INT8U)D_Relay_DownBackFault) == PaMtr_BackRelayAdhesionErr) &&
                (CAL_HightMotorRunInterval_100ms <=
                 Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
            {
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
              Appl_PaAdjustModel_B.H_MotorRunType_m =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

              /* 自动调节 */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_PaAdjustModel_B.H_MotorRunType_m)
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* 靠背自动调节有效且不在误差范围内 */
              if ((0 != SeatBackPosiReq) && (((BOOL)FALSE) == PaMtr_BackStallErr)
                  && (Appl_PaAdjustModel_B.HeightAutoRunFlag_g ==
                      enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_PaAdjustModel_DW.UpFrontFlag_c == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
              {
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
                Appl_PaAdjustModel_B.H_MotorRunType_m =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_e = enSeatMoveCmd_EN_UP_FORWARD;

                /* 自动调节 */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_PaAdjustModel_B.H_MotorRunType_m)
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* 靠背手动调节有效 */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD ==
                     Appl_PaAdjustModel_B.BackManualAdjSw) && (((BOOL)FALSE) ==
                     PaMtr_BackStallErr) && (((BOOL)FALSE) == PaMtr_BackHallErr)
                    && (((BOOL)FALSE) == PaMtr_BackMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a))
                {
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = 0U;
                  Appl_PaAdjustModel_B.H_MotorRunType_m =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_PaAdjustModel_DW.is_c19_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_e = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* 靠背自动调节 */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_PaAdjustModel_B.H_MotorRunType_m)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* 靠背电机调间隔时间 */
                  if (Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 = Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a + 1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_a = (INT8U)tmp_0;
                  }

                  Appl_PaAdjustModel_DW.DownBackFlag_c = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_c = 0U;

                  /* 靠背自动调节有效 */
                  if (0 != SeatBackPosiReq)
                  {
                    /* 靠背误差判断目前定义为5霍尔数值 */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         PaMtr_BackSoftStopErr) && (SeatBackPosiReq >
                         PaMtr_BackHallPosi) && (((INT16U)D_ToleranceDistance) <
                         SeatBackPosiReq - PaMtr_BackHallPosi))
                    {
                      Appl_PaAdjustModel_DW.UpFrontFlag_c = 1U;
                    }
                    else
                    {
                      /*  不在软止点 且超误差范围  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           PaMtr_BackSoftStopErr) && (SeatBackPosiReq <
                           PaMtr_BackHallPosi) && (((INT16U)D_ToleranceDistance)
                           < PaMtr_BackHallPosi - SeatBackPosiReq))
                      {
                        Appl_PaAdjustModel_DW.DownBackFlag_c = 1U;
                      }
                      else
                      {
                        /* 靠背误差范围内，反馈成功 */
                        Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_PaAdjustModel_B.H_MotorRunType_m =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  调用位置有变化 则先清状态  */
                  if (SeatLengthPosiReq !=
                      Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_j)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_g =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
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

  SeatBackPosiReq = Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_ov;
  Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_ov = SeatFrontPosiReq;
  MotorActType_prev_i = Appl_PaAdjustModel_DW.MotorActType_start_l;
  Appl_PaAdjustModel_DW.MotorActType_start_l =
    Appl_PaAdjustModel_B.MotorActionType;
  if (Appl_PaAdjustModel_DW.is_active_c21_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c21_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
      Appl_PaAdjustModel_IN_Init_Interval;
    H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;
    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 1U;
    Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
    Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;
  }
  else
  {
    switch (Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel)
    {
     case Appl_PaAdjustModel_IN_H_MotorDownBackRun:
      Appl_PaAdjustModel_H_MotorDownBackRun_j(&H_SeatMoveCmd_p,
        &MotorActType_prev_i, &SeatFrontPosiReq);
      break;

     case Appl_PaAdjustModel_IN_H_MotorUpFrontRun:
      Appl_PaAdjustModel_H_MotorUpFrontRun_l(&H_SeatMoveCmd_p,
        &MotorActType_prev_i, &SeatFrontPosiReq);
      break;

     default:
      H_SeatMoveCmd_p = enSeatMoveCmd_EN_NULL;

      /* 腿托继电器上前粘连故障 == 有效 */
      if ((((INT8U)D_Relay_UpFrontFault) == PaMtr_FrontRelayAdhesionErr) &&
          (CAL_HightMotorRunInterval_100ms <=
           Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
      {
        Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
        Appl_PaAdjustModel_B.H_MotorRunType_l =
          enSeatHightMotorRunsts_EN_DnFURelayAdhesion_BK;
        Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
          Appl_PaAdjustModel_IN_H_MotorDownBackRun;
        H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

        /* 腿托自动调节 */
        if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
            Appl_PaAdjustModel_B.H_MotorRunType_l)
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_RUNNING;
        }
        else
        {
          Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
            enSeatAutoRunSts_EN_SEAT_INVALID;
        }
      }
      else
      {
        /* 腿托自动调节有效且不在误差范围内 */
        if ((0 != SeatFrontPosiReq) && (((BOOL)FALSE) == PaMtr_FrontStallErr) &&
            (Appl_PaAdjustModel_B.HeightAutoRunFlag_p ==
             enSeatAutoRunSts_EN_SEAT_INVALID) &&
            (Appl_PaAdjustModel_DW.DownBackFlag_n == 1) &&
            (CAL_HightMotorRunInterval_100ms <=
             Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
        {
          Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
          Appl_PaAdjustModel_B.H_MotorRunType_l =
            enSeatHightMotorRunsts_EN_AutoAdjust_BK;
          Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
            Appl_PaAdjustModel_IN_H_MotorDownBackRun;
          H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

          /* 腿托自动调节 */
          if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
              Appl_PaAdjustModel_B.H_MotorRunType_l)
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_RUNNING;
          }
          else
          {
            Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
              enSeatAutoRunSts_EN_SEAT_INVALID;
          }
        }
        else
        {
          /* 腿托手动调节 */
          if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD ==
               Appl_PaAdjustModel_B.FrontManualAdjSw) && (((BOOL)FALSE) ==
               PaMtr_FrontStallErr) && (((BOOL)FALSE) == PaMtr_FrontHallErr) &&
              (((BOOL)FALSE) == PaMtr_FrontMotorTimeOutErr) &&
              (CAL_HightMotorRunInterval_100ms <=
               Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
          {
            Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
            Appl_PaAdjustModel_B.H_MotorRunType_l =
              enSeatHightMotorRunsts_EN_ManualAdjust_FU;
            Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
              Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
            H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

            /* 自动调节 */
            if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                Appl_PaAdjustModel_B.H_MotorRunType_l)
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_RUNNING;
            }
            else
            {
              Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                enSeatAutoRunSts_EN_SEAT_INVALID;
            }
          }
          else
          {
            /* 腿托继电器下后粘连故障 == 有效 间隔时间大于100ms */
            if ((((INT8U)D_Relay_DownBackFault) == PaMtr_FrontRelayAdhesionErr) &&
                (CAL_HightMotorRunInterval_100ms <=
                 Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
            {
              Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
              Appl_PaAdjustModel_B.H_MotorRunType_l =
                enSeatHightMotorRunsts_EN_DnBkRelayAdhesion_FU;
              Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
              H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

              /* 自动调节 */
              if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                  Appl_PaAdjustModel_B.H_MotorRunType_l)
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_RUNNING;
              }
              else
              {
                Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                  enSeatAutoRunSts_EN_SEAT_INVALID;
              }
            }
            else
            {
              /* 腿托自动调节有效且不在误差范围内 */
              if ((0 != SeatFrontPosiReq) && (((BOOL)FALSE) ==
                   PaMtr_FrontStallErr) &&
                  (Appl_PaAdjustModel_B.HeightAutoRunFlag_p ==
                   enSeatAutoRunSts_EN_SEAT_INVALID) &&
                  (Appl_PaAdjustModel_DW.UpFrontFlag_b == 1) &&
                  (CAL_HightMotorRunInterval_100ms <=
                   Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
              {
                Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
                Appl_PaAdjustModel_B.H_MotorRunType_l =
                  enSeatHightMotorRunsts_EN_AutoAdjust_FU;
                Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                  Appl_PaAdjustModel_IN_H_MotorUpFrontRun;
                H_SeatMoveCmd_p = enSeatMoveCmd_EN_UP_FORWARD;

                /* 自动调节 */
                if (enSeatHightMotorRunsts_EN_AutoAdjust_FU ==
                    Appl_PaAdjustModel_B.H_MotorRunType_l)
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_RUNNING;
                }
                else
                {
                  Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                    enSeatAutoRunSts_EN_SEAT_INVALID;
                }
              }
              else
              {
                /* 腿托手动调节有效 */
                if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD ==
                     Appl_PaAdjustModel_B.FrontManualAdjSw) && (((BOOL)FALSE) ==
                     PaMtr_FrontStallErr) && (((BOOL)FALSE) ==
                     PaMtr_FrontHallErr) && (((BOOL)FALSE) ==
                     PaMtr_FrontMotorTimeOutErr) &&
                    (CAL_HightMotorRunInterval_100ms <=
                     Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f))
                {
                  Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = 0U;
                  Appl_PaAdjustModel_B.H_MotorRunType_l =
                    enSeatHightMotorRunsts_EN_ManualAdjust_BK;
                  Appl_PaAdjustModel_DW.is_c21_Appl_PaAdjustModel =
                    Appl_PaAdjustModel_IN_H_MotorDownBackRun;
                  H_SeatMoveCmd_p = enSeatMoveCmd_EN_DN_BACKWARD;

                  /* 腿托自动调节 */
                  if (enSeatHightMotorRunsts_EN_AutoAdjust_BK ==
                      Appl_PaAdjustModel_B.H_MotorRunType_l)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_RUNNING;
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }
                }
                else
                {
                  /* 腿托电机调间隔时间 */
                  if (Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f <
                      CAL_HightMotorRunInterval_100ms)
                  {
                    tmp_0 = Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f + 1;
                    if (tmp_0 > 255)
                    {
                      tmp_0 = 255;
                    }

                    Appl_PaAdjustModel_DW.HMotorRunIntervalTime_f = (INT8U)tmp_0;
                  }

                  Appl_PaAdjustModel_DW.DownBackFlag_n = 0U;
                  Appl_PaAdjustModel_DW.UpFrontFlag_b = 0U;

                  /* 腿托自动调节有效 */
                  if (0 != SeatFrontPosiReq)
                  {
                    /* 腿托误差判断目前定义为5霍尔数值 */
                    if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD !=
                         PaMtr_FrontSoftStopErr) && (SeatFrontPosiReq >
                         PaMtr_FrontHallPosi) && (((INT16U)D_ToleranceDistance) <
                         SeatFrontPosiReq - PaMtr_FrontHallPosi))
                    {
                      Appl_PaAdjustModel_DW.UpFrontFlag_b = 1U;
                    }
                    else
                    {
                      /*  不在软止点 且超误差范围  */
                      if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD !=
                           PaMtr_FrontSoftStopErr) && (SeatFrontPosiReq <
                           PaMtr_FrontHallPosi) && (((INT16U)D_ToleranceDistance)
                           < PaMtr_FrontHallPosi - SeatFrontPosiReq))
                      {
                        Appl_PaAdjustModel_DW.DownBackFlag_n = 1U;
                      }
                      else
                      {
                        /* 腿托误差范围内，反馈成功 */
                        Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                          enSeatAutoRunSts_EN_SEAT_SUCCESS;
                        Appl_PaAdjustModel_B.H_MotorRunType_l =
                          enSeatHightMotorRunsts_EN_AutoAdjust_FUSuccess_Stop;
                      }
                    }
                  }
                  else
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
                  }

                  /*  调用位置有变化 则先清状态  */
                  if (SeatBackPosiReq !=
                      Appl_PaAdjustModel_DW.SeatHeightPosiReq_start_ov)
                  {
                    Appl_PaAdjustModel_B.HeightAutoRunFlag_p =
                      enSeatAutoRunSts_EN_SEAT_INVALID;
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

  if (Appl_PaAdjustModel_DW.is_active_c17_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c17_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_c17_Appl_PaAdjustModel = Appl_PaAdjustModel_IN_Init;
    Appl_PaAdjustModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
    Appl_PaAdjustModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
    Appl_PaAdjustModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
    Appl_PaAdjustModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
  }
  else if (Appl_PaAdjustModel_DW.is_c17_Appl_PaAdjustModel ==
           Appl_PaAdjustModel_IN_Ban)
  {
    /*  卸荷使能  */
    if ((enIgnSts_eCrank != PaMtr_PowerModeStatus) &&
        (enFinalPowerMode_EN_NORMAL_VOLT == PaMtr_VoltMode) && (((BOOL)TRUE) ==
         PaMtr_VoltSatisfy) && (!((BOOL)FALSE)))
    {
      Appl_PaAdjustModel_DW.is_c17_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Init;
      Appl_PaAdjustModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
      Appl_PaAdjustModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
      Appl_PaAdjustModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
      Appl_PaAdjustModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
    }
  }
  else
  {
    /*  卸荷禁能  */
    if ((enIgnSts_eCrank == PaMtr_PowerModeStatus) ||
        (enFinalPowerMode_EN_NORMAL_VOLT != PaMtr_VoltMode) || (((BOOL)TRUE) !=
         PaMtr_VoltSatisfy) || ((BOOL)FALSE))
    {
      Appl_PaAdjustModel_DW.is_c17_Appl_PaAdjustModel =
        Appl_PaAdjustModel_IN_Ban;

      /* 禁能 */
      Appl_PaAdjustModel_B.HeightMotorCmd = 0U;
      Appl_PaAdjustModel_B.LengthMotorCmd = 0U;
      Appl_PaAdjustModel_B.BackMotorCmd = 0U;
      Appl_PaAdjustModel_B.FrontMotorCmd = 0U;
    }
    else
    {
      Appl_PaAdjustModel_B.HeightMotorCmd = (INT8U)H_SeatMoveCmd_i;
      Appl_PaAdjustModel_B.LengthMotorCmd = (INT8U)H_SeatMoveCmd;
      Appl_PaAdjustModel_B.BackMotorCmd = (INT8U)H_SeatMoveCmd_e;
      Appl_PaAdjustModel_B.FrontMotorCmd = (INT8U)H_SeatMoveCmd_p;
    }
  }

  if (Appl_PaAdjustModel_DW.is_active_c16_Appl_PaAdjustModel == 0U)
  {
    Appl_PaAdjustModel_DW.is_active_c16_Appl_PaAdjustModel = 1U;
    Appl_PaAdjustModel_DW.is_HeightAdjust = Appl_PaAdjustModel_IN_Init;
    Appl_PaAdjustModel_B.Can_HeightMotorCtrl = 0U;
    Appl_PaAdjustModel_DW.HeightTimer = 0U;
    Appl_PaAdjustModel_DW.is_VerticalAdjust = Appl_PaAdjustModel_IN_Init;
    Appl_PaAdjustModel_B.Can_LengthMotorCtrl = 0U;
    Appl_PaAdjustModel_DW.LengthTimer = 0U;
    Appl_PaAdjustModel_DW.is_FrontAngleAdjust = Appl_PaAdjustModel_IN_Init;
    Appl_PaAdjustModel_B.Can_FrontMotorCtrl = 0U;
    Appl_PaAdjustModel_DW.FrontTimer = 0U;
    Appl_PaAdjustModel_DW.is_BackAdjust = Appl_PaAdjustModel_IN_Init;
    Appl_PaAdjustModel_B.Can_BackMotorCtrl = 0U;
    Appl_PaAdjustModel_DW.BackTimer = 0U;
  }
  else
  {
    if (Appl_PaAdjustModel_DW.is_HeightAdjust == Appl_PaAdjustModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.HeightMotorCmd)
      {
        Appl_PaAdjustModel_DW.is_HeightAdjust = Appl_PaAdjustModel_IN_Init;
        Appl_PaAdjustModel_B.Can_HeightMotorCtrl = 0U;
        Appl_PaAdjustModel_DW.HeightTimer = 0U;
      }
      else
      {
        Appl_PaAdjustModel_B.Can_HeightMotorCtrl =
          Appl_PaAdjustModel_B.HeightMotorCmd;
        tmp_0 = Appl_PaAdjustModel_DW.HeightTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_PaAdjustModel_DW.HeightTimer = (INT16U)tmp_0;

        /*  继电器粘连 */
        if (((BOOL)FALSE) != PaMtr_HeightRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.HeightTimer = 0U;
        }
      }
    }
    else
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL != Appl_PaAdjustModel_B.HeightMotorCmd)
      {
        Appl_PaAdjustModel_DW.is_HeightAdjust = Appl_PaAdjustModel_IN_Action;
        Appl_PaAdjustModel_B.Can_HeightMotorCtrl =
          Appl_PaAdjustModel_B.HeightMotorCmd;

        /*  继电器粘连 */
        if (((BOOL)FALSE) != PaMtr_HeightRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.HeightTimer = 0U;
        }
      }
    }

    if (Appl_PaAdjustModel_DW.is_VerticalAdjust == Appl_PaAdjustModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.LengthMotorCmd)
      {
        Appl_PaAdjustModel_DW.is_VerticalAdjust = Appl_PaAdjustModel_IN_Init;
        Appl_PaAdjustModel_B.Can_LengthMotorCtrl = 0U;
        Appl_PaAdjustModel_DW.LengthTimer = 0U;
      }
      else
      {
        Appl_PaAdjustModel_B.Can_LengthMotorCtrl =
          Appl_PaAdjustModel_B.LengthMotorCmd;
        tmp_0 = Appl_PaAdjustModel_DW.LengthTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_PaAdjustModel_DW.LengthTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != PaMtr_LengthRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.LengthTimer = 0U;
        }
      }
    }
    else
    {
      /* 高度、纵向电机没有命令或计时已到 */
      if ((((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.HeightMotorCmd)
           || (Appl_PaAdjustModel_DW.HeightTimer > CAL_MotorDiffToStart_100ms)) &&
          ((INT32S)enSeatMoveCmd_EN_NULL != Appl_PaAdjustModel_B.LengthMotorCmd))
      {
        Appl_PaAdjustModel_DW.is_VerticalAdjust = Appl_PaAdjustModel_IN_Action;
        Appl_PaAdjustModel_B.Can_LengthMotorCtrl =
          Appl_PaAdjustModel_B.LengthMotorCmd;
        if (((BOOL)FALSE) != PaMtr_LengthRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.LengthTimer = 0U;
        }
      }
    }

    if (Appl_PaAdjustModel_DW.is_FrontAngleAdjust ==
        Appl_PaAdjustModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.FrontMotorCmd)
      {
        Appl_PaAdjustModel_DW.is_FrontAngleAdjust = Appl_PaAdjustModel_IN_Init;
        Appl_PaAdjustModel_B.Can_FrontMotorCtrl = 0U;
        Appl_PaAdjustModel_DW.FrontTimer = 0U;
      }
      else
      {
        Appl_PaAdjustModel_B.Can_FrontMotorCtrl =
          Appl_PaAdjustModel_B.FrontMotorCmd;
        tmp_0 = Appl_PaAdjustModel_DW.FrontTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_PaAdjustModel_DW.FrontTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != PaMtr_FrontRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.FrontTimer = 0U;
        }
      }
    }
    else
    {
      /* 高度、纵向电机没有命令或计时已到 */
      if ((((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.HeightMotorCmd)
           || (Appl_PaAdjustModel_DW.HeightTimer > CAL_MotorDiffToStart_100ms)) &&
          (((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.LengthMotorCmd)
           || (Appl_PaAdjustModel_DW.LengthTimer > CAL_MotorDiffToStart_100ms)) &&
          ((INT32S)enSeatMoveCmd_EN_NULL != Appl_PaAdjustModel_B.FrontMotorCmd))
      {
        Appl_PaAdjustModel_DW.is_FrontAngleAdjust = Appl_PaAdjustModel_IN_Action;
        Appl_PaAdjustModel_B.Can_FrontMotorCtrl =
          Appl_PaAdjustModel_B.FrontMotorCmd;
        if (((BOOL)FALSE) != PaMtr_FrontRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.FrontTimer = 0U;
        }
      }
    }

    if (Appl_PaAdjustModel_DW.is_BackAdjust == Appl_PaAdjustModel_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.BackMotorCmd)
      {
        Appl_PaAdjustModel_DW.is_BackAdjust = Appl_PaAdjustModel_IN_Init;
        Appl_PaAdjustModel_B.Can_BackMotorCtrl = 0U;
        Appl_PaAdjustModel_DW.BackTimer = 0U;
      }
      else
      {
        Appl_PaAdjustModel_B.Can_BackMotorCtrl =
          Appl_PaAdjustModel_B.BackMotorCmd;
        tmp_0 = Appl_PaAdjustModel_DW.BackTimer + 1;
        if (tmp_0 > 65535)
        {
          tmp_0 = 65535;
        }

        Appl_PaAdjustModel_DW.BackTimer = (INT16U)tmp_0;
        if (((BOOL)FALSE) != PaMtr_BackRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.BackTimer = 0U;
        }
      }
    }
    else
    {
      /* 高度、纵向、前部电机没有命令或计时已到 */
      if ((((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.HeightMotorCmd)
           || (Appl_PaAdjustModel_DW.HeightTimer > CAL_MotorDiffToStart_100ms)) &&
          (((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.LengthMotorCmd)
           || (Appl_PaAdjustModel_DW.LengthTimer > CAL_MotorDiffToStart_100ms)) &&
          (((INT32S)enSeatMoveCmd_EN_NULL == Appl_PaAdjustModel_B.FrontMotorCmd)
           || (Appl_PaAdjustModel_DW.FrontTimer > CAL_MotorDiffToStart_100ms)) &&
          ((INT32S)enSeatMoveCmd_EN_NULL != Appl_PaAdjustModel_B.BackMotorCmd))
      {
        Appl_PaAdjustModel_DW.is_BackAdjust = Appl_PaAdjustModel_IN_Action;
        Appl_PaAdjustModel_B.Can_BackMotorCtrl =
          Appl_PaAdjustModel_B.BackMotorCmd;
        if (((BOOL)FALSE) != PaMtr_BackRelayAdhesionErr)
        {
          Appl_PaAdjustModel_DW.BackTimer = 0U;
        }
      }
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_PaAdjustModel_RTE(void)
{
  PaMtr_AnyoneHallErr = Rte_GetVfb_PaAnyoneHallErr( );
  PaMtr_AnyoneRelayAdheErr = Rte_GetVfb_PaAnyoneRelayAdheErr( );
  PaMtr_BackDefaultStopPos = Cdd_GetMotorHardStop(EN_PassengerBack);
  PaMtr_BackHallErr = Rte_GetVfb_PaBackHallErr( );
  PaMtr_BackHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerBack);
  PaMtr_BackLearnCmd = Rte_GetVfb_PaBackLearnCmd( );
  PaMtr_BackMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_PAS_BACK);
  PaMtr_BackMotorTimeOutErr = Rte_GetVfb_PaBackMotorTimeOutErr( );
  PaMtr_BackRelayAdhesionErr = Rte_GetVfb_PaBackRelayAdheErr( );
  PaMtr_BackSoftStopErr = Rte_GetVfb_PaBackSoftStopErr( );
  PaMtr_BackStallErr = Rte_GetVfb_PaBackStallErr( );
  PaMtr_BackSwitchAdheErr = Rte_GetVfb_PaBackSwitchAdheErr( );
  PaMtr_BackSwitchCmd = Rte_GetVfb_PaBackSwitchCmd( );
  PaMtr_DiagnoseLearnIn = Rte_GetVfb_PaLearnEnable( );
  PaMtr_FrontDefaulStoptPos = Cdd_GetMotorHardStop(EN_PaResever_2);
  PaMtr_FrontHallErr = Rte_GetVfb_PaFrontHallErr( );
  PaMtr_FrontHallPosi = Cdd_GetCurrentHallCnt(EN_PaResever_2);
  PaMtr_FrontLearnCmd = Rte_GetVfb_PaFrontLearnCmd( );
  PaMtr_FrontMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_PAS_FRONT);
  PaMtr_FrontMotorTimeOutErr = Rte_GetVfb_PaFrontMotorTimeOutErr( );
  PaMtr_FrontRelayAdhesionErr = Rte_GetVfb_PaFrontRelayAdheErr( );
  PaMtr_FrontSoftStopErr = Rte_GetVfb_PaFrontSoftStopErr( );
  PaMtr_FrontStallErr = Rte_GetVfb_PaFrontStallErr( );
  PaMtr_FrontSwitchAdheErr = Rte_GetVfb_PaFrontSwitchAdheErr( );
  PaMtr_FrontSwitchCmd = Rte_GetVfb_PaFrontSwitchCmd( );
  PaMtr_HeightDefaultStopPos = Cdd_GetMotorHardStop(EN_PaResever_1);
  PaMtr_HeightHallErr = Rte_GetVfb_PaHeightHallErr( );
  PaMtr_HeightHallPosi = Cdd_GetCurrentHallCnt(EN_PaResever_1);
  PaMtr_HeightLearnCmd = Rte_GetVfb_PaHeightLearnCmd( );
  PaMtr_HeightMotorTimeOutErr = Rte_GetVfb_PaHeightMotorTimeOutErr( );
  PaMtr_HeightRelayAdhesionErr = Rte_GetVfb_PaHeightRelayAdheErr( );
  PaMtr_HeightSoftStopErr = Rte_GetVfb_PaLengthSoftStopErr( );
  PaMtr_HeightStallErr = Rte_GetVfb_PaHeightStallErr( );
  PaMtr_HeightSwitchAdheErr = Rte_GetVfb_PaHeightSwitchAdheErr( );
  PaMtr_HeightSwitchCmd = Rte_GetVfb_PaHeightSwitchCmd( );
  PaMtr_HeigthMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_PAS_HEIGHT);
  PaMtr_LearnSts = Rte_GetVfb_PaLearnSts( );
  PaMtr_LengthDefaultStopPos = Cdd_GetMotorHardStop(EN_PassengerLength);
  PaMtr_LengthHallErr = Rte_GetVfb_PaLengthHallErr( );
  PaMtr_LengthHallPosi = Cdd_GetCurrentHallCnt(EN_PassengerLength);
  PaMtr_LengthLearnCmd = Rte_GetVfb_PaLengthLearnCmd( );
  PaMtr_LengthMotorMosErr = Srvl_Tle9210x_GetMotorErr(EN_SEAT_PAS_LENGTH);
  PaMtr_LengthMotorTimeOutErr = Rte_GetVfb_PaLengthMotorTimeOutErr( );
  PaMtr_LengthRelayAdhesionErr = Rte_GetVfb_PaLengthRelayAdheErr( );
  PaMtr_LengthSoftStopErr = Rte_GetVfb_PaHeightSoftStopErr( );
  PaMtr_LengthStallErr = Rte_GetVfb_PaLengthStallErr( );
  PaMtr_LengthSwitchAdheErr = Rte_GetVfb_PaLengthSwitchAdheErr( );
  PaMtr_LengthSwitchCmd = Rte_GetVfb_PaLengthSwitchCmd( );
  PaMtr_MemoryBackReqPosi = Rte_GetVfb_PaMemBackReqPosi( );
  PaMtr_MemoryFrontReqPosi = Rte_GetVfb_PaMemFrontReqPosi( );
  PaMtr_MemoryHeightReqPosi = Rte_GetVfb_PaMemHeightReqPosi( );
  PaMtr_MemoryLengthReqPosi = Rte_GetVfb_PaMemLengthReqPosi( );
  PaMtr_PowerModeStatus = Rte_GetVfb_PowerMode( );
  PaMtr_ResetBackReqPosi = Rte_GetVfb_PaBackResetReqPosi( );
  PaMtr_ResetFrontReqPosi = Rte_GetVfb_PaFrontResetReqPosi( );
  PaMtr_ResetHeightReqPosi = Rte_GetVfb_PaHeightResetReqPosi( );
  PaMtr_ResetLengthReqPosi = Rte_GetVfb_PaLengthResetReqPosi( );
  PaMtr_VoltMode = Rte_GetVfb_VoltMode( );
  PaMtr_VoltSatisfy = Rte_GetVfb_VoltSatisfy( );
  PaMtr_WelcomeBackReqPosi = Rte_GetVfb_PaWelBackReqPosi( );
  PaMtr_WelcomeLengthReqPosi = Rte_GetVfb_PaWelLengthReqPosi( );
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_PaAdjustModel_UpDataInputInfo(void)
{
  Appl_PaAdjustModel_RTE();
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_PaAdjustModel_UpDataOutputInfo(void)
{
  Appl_PaAdjustModel_B.DataTypeConversion2 = (INT8U)
    Appl_PaAdjustModel_B.H_MotorRunType_g;
  Appl_PaAdjustModel_B.DataTypeConversion3 = (INT8U)
    Appl_PaAdjustModel_B.H_MotorRunType;
  Appl_PaAdjustModel_B.DataTypeConversion4 = (INT8U)
    Appl_PaAdjustModel_B.H_MotorRunType_l;
  Appl_PaAdjustModel_B.DataTypeConversion5 = (INT8U)
    Appl_PaAdjustModel_B.H_MotorRunType_m;
  Rte_SetVfb_PaMoveType(Appl_PaAdjustModel_B.MotorActionType);
  Rte_SetVfb_PaHeightAutoRunFlag(Appl_PaAdjustModel_B.HeightAutoRunFlag_o);
  Rte_SetVfb_PaLengthAutoRunFlag(Appl_PaAdjustModel_B.HeightAutoRunFlag);
  Rte_SetVfb_PaBackAutoRunFlag(Appl_PaAdjustModel_B.HeightAutoRunFlag_g);
  Rte_SetVfb_PaFrontAutoRunFlag(Appl_PaAdjustModel_B.HeightAutoRunFlag_p);
  Rte_SetVfb_PaHeightMotorCmd(Appl_PaAdjustModel_B.Can_HeightMotorCtrl);
  Rte_SetVfb_PaLengthMotorCmd(Appl_PaAdjustModel_B.Can_LengthMotorCtrl);
  Rte_SetVfb_PaBackMotorCmd(Appl_PaAdjustModel_B.Can_BackMotorCtrl);
  Rte_SetVfb_PaFrontMotorCmd(Appl_PaAdjustModel_B.Can_FrontMotorCtrl);
  Rte_SetVfb_PaHeightMotorReason(Appl_PaAdjustModel_B.DataTypeConversion2);
  Rte_SetVfb_PaLengthMotorReason(Appl_PaAdjustModel_B.DataTypeConversion3);
  Rte_SetVfb_PaBackMotorReason(Appl_PaAdjustModel_B.DataTypeConversion4);
  Rte_SetVfb_PaFrontMotorReason(Appl_PaAdjustModel_B.DataTypeConversion5);
}

/* Model step function */
void Appl_PaAdjustModel_step(void)
{
  Appl_PaAdjustModel_UpDataInputInfo();
  Appl_PaAdjustModel_LogicCtrl();
  Appl_PaAdjustModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_PaAdjustModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_PaAdjustModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_PaAdjustModel_B), 0,
                sizeof(B_Appl_PaAdjustModel_T));

  {
    Appl_PaAdjustModel_B.MotorActionType = enSeatMotorRunTye_EN_NULL;
    Appl_PaAdjustModel_B.H_MotorRunType = enSeatHightMotorRunsts_EN_NULL;
    Appl_PaAdjustModel_B.H_MotorRunType_g = enSeatHightMotorRunsts_EN_NULL;
    Appl_PaAdjustModel_B.H_MotorRunType_l = enSeatHightMotorRunsts_EN_NULL;
    Appl_PaAdjustModel_B.H_MotorRunType_m = enSeatHightMotorRunsts_EN_NULL;
    Appl_PaAdjustModel_B.HeightAutoRunFlag = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.HeightAutoRunFlag_o = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.HeightAutoRunFlag_p = enSeatAutoRunSts_EN_SEAT_INVALID;
    Appl_PaAdjustModel_B.HeightAutoRunFlag_g = enSeatAutoRunSts_EN_SEAT_INVALID;
  }

  /* exported global signals */
  PaMtr_BackMotorMosErr = enMosErrSts_enNULL;
  PaMtr_FrontMotorMosErr = enMosErrSts_enNULL;
  PaMtr_HeigthMotorMosErr = enMosErrSts_enNULL;
  PaMtr_LengthMotorMosErr = enMosErrSts_enNULL;
  PaMtr_PowerModeStatus = enIgnSts_eOff;
  PaMtr_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  PaMtr_BackDefaultStopPos = ((INT16U)0U);
  PaMtr_BackHallPosi = ((INT16U)0U);
  PaMtr_FrontDefaulStoptPos = ((INT16U)0U);
  PaMtr_FrontHallPosi = ((INT16U)0U);
  PaMtr_HeightDefaultStopPos = ((INT16U)0U);
  PaMtr_HeightHallPosi = ((INT16U)0U);
  PaMtr_LengthDefaultStopPos = ((INT16U)0U);
  PaMtr_LengthHallPosi = ((INT16U)0U);
  PaMtr_MemoryBackReqPosi = ((INT16U)0U);
  PaMtr_MemoryFrontReqPosi = ((INT16U)0U);
  PaMtr_MemoryHeightReqPosi = ((INT16U)0U);
  PaMtr_MemoryLengthReqPosi = ((INT16U)0U);
  PaMtr_ResetBackReqPosi = ((INT16U)0U);
  PaMtr_ResetFrontReqPosi = ((INT16U)0U);
  PaMtr_ResetHeightReqPosi = ((INT16U)0U);
  PaMtr_ResetLengthReqPosi = ((INT16U)0U);
  PaMtr_WelcomeBackReqPosi = ((INT16U)0U);
  PaMtr_WelcomeLengthReqPosi = ((INT16U)0U);
  PaMtr_AnyoneHallErr = ((INT8U)0U);
  PaMtr_AnyoneRelayAdheErr = ((INT8U)0U);
  PaMtr_BackHallErr = ((INT8U)0U);
  PaMtr_BackLearnCmd = ((INT8U)0U);
  PaMtr_BackMotorTimeOutErr = ((INT8U)0U);
  PaMtr_BackRelayAdhesionErr = ((INT8U)0U);
  PaMtr_BackSoftStopErr = ((INT8U)0U);
  PaMtr_BackStallErr = ((INT8U)0U);
  PaMtr_BackSwitchAdheErr = ((INT8U)0U);
  PaMtr_BackSwitchCmd = ((INT8U)0U);
  PaMtr_DiagnoseLearnIn = ((INT8U)0U);
  PaMtr_FrontHallErr = ((INT8U)0U);
  PaMtr_FrontLearnCmd = ((INT8U)0U);
  PaMtr_FrontMotorTimeOutErr = ((INT8U)0U);
  PaMtr_FrontRelayAdhesionErr = ((INT8U)0U);
  PaMtr_FrontSoftStopErr = ((INT8U)0U);
  PaMtr_FrontStallErr = ((INT8U)0U);
  PaMtr_FrontSwitchAdheErr = ((INT8U)0U);
  PaMtr_FrontSwitchCmd = ((INT8U)0U);
  PaMtr_HeightHallErr = ((INT8U)0U);
  PaMtr_HeightLearnCmd = ((INT8U)0U);
  PaMtr_HeightMotorTimeOutErr = ((INT8U)0U);
  PaMtr_HeightRelayAdhesionErr = ((INT8U)0U);
  PaMtr_HeightSoftStopErr = ((INT8U)0U);
  PaMtr_HeightStallErr = ((INT8U)0U);
  PaMtr_HeightSwitchAdheErr = ((INT8U)0U);
  PaMtr_HeightSwitchCmd = ((INT8U)0U);
  PaMtr_LearnSts = ((INT8U)0U);
  PaMtr_LengthHallErr = ((INT8U)0U);
  PaMtr_LengthLearnCmd = ((INT8U)0U);
  PaMtr_LengthMotorTimeOutErr = ((INT8U)0U);
  PaMtr_LengthRelayAdhesionErr = ((INT8U)0U);
  PaMtr_LengthSoftStopErr = ((INT8U)0U);
  PaMtr_LengthStallErr = ((INT8U)0U);
  PaMtr_LengthSwitchAdheErr = ((INT8U)0U);
  PaMtr_LengthSwitchCmd = ((INT8U)0U);
  PaMtr_VoltSatisfy = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_PaAdjustModel_DW, 0,
                sizeof(DW_Appl_PaAdjustModel_T));
  Appl_PaAdjustModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
