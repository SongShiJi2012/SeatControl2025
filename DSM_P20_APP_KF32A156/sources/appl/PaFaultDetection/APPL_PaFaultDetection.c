/*
 * File: APPL_PaFaultDetection.c
 *
 * Code generated for Simulink model 'APPL_PaFaultDetection'.
 *
 * Model version                  : 1.296
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sun Jul  4 09:59:38 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "APPL_PaFaultDetection.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_StallCurrent
#error The variable for the parameter "D_StallCurrent" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_DrSoftStopDef_B
#error The variable for the parameter "D_DrSoftStopDef_B" is not defined
#endif

#ifndef D_DrSoftStopDef_F
#error The variable for the parameter "D_DrSoftStopDef_F" is not defined
#endif

#ifndef D_DrSoftStopDef_H
#error The variable for the parameter "D_DrSoftStopDef_H" is not defined
#endif

#ifndef D_DrSoftStopDef_L
#error The variable for the parameter "D_DrSoftStopDef_L" is not defined
#endif

#ifndef D_Relay_DownBackFault
#error The variable for the parameter "D_Relay_DownBackFault" is not defined
#endif

#ifndef D_Relay_UpFrontFault
#error The variable for the parameter "D_Relay_UpFrontFault" is not defined
#endif

/* Named constants for Chart: '<S22>/RelayFault' */
#define APPL_PaFaultDetection_IN_Judge ((INT8U)1U)
#define APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_h ((INT8U)0U)
#define APPL_PaFaultDetection_IN_Normal ((INT8U)2U)

/* Named constants for Chart: '<S5>/SwitchErrorDetection' */
#define APPL_PaFaultDetection_IN_Invalid ((INT8U)1U)
#define APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l ((INT8U)0U)
#define APPL_PaFaultDetection_IN_Valid ((INT8U)2U)

/* Named constants for Chart: '<S6>/HallErrorDetection' */
#define APPL_PaFaultDetection_IN_Init  ((INT8U)1U)
#define APPL_PaFaultDetection_IN_Judge_o ((INT8U)2U)
#define APPL_PaFaultDetection_IN_MotorHallDetect ((INT8U)2U)
#define APPL_PaFaultDetection_IN_Normal_c ((INT8U)3U)

/* Named constants for Chart: '<S7>/MotorTimeOutDetection' */
#define APPL_PaFaultDetection_IN_Action ((INT8U)1U)
#define APPL_PaFaultDetection_IN_Init_e ((INT8U)2U)

/* Named constants for Chart: '<S9>/SoftStopPointDetection' */
#define APPL_PaFaultDetection_IN_LeftUpFront ((INT8U)2U)
#define APPL_PaFaultDetection_IN_RightDnBack ((INT8U)3U)

/* Named constants for Chart: '<S10>/StallErrorDetection' */
#define APPL_PaFaultDetection_IN_Judge_e ((INT8U)1U)
#define APPL_PaFaultDetection_IN_Normal_o ((INT8U)2U)

/* Named constants for Chart: '<S11>/ SWProcess ' */
#define APPL_PaFaultDetection_IN_DSM_SWAdjust ((INT8U)1U)
#define APPL_PaFaultDetection_IN_Disable ((INT8U)1U)
#define APPL_PaFaultDetection_IN_Enable ((INT8U)2U)

/* Exported block signals */
enSeatMoveCmd MtrCtrlFault_PaBackSwitch;/* '<S38>/MtrCtrlFault_PaBackSwitch'
                                         * 硬线调节开关输入方向-副驾靠背
                                         */
enSeatMoveCmd MtrCtrlFault_PaFrontSwitch;/* '<S38>/MtrCtrlFault_PaFrontSwitch'
                                          * 硬线调节开关输入方向-副驾腿托
                                          */
enSeatMoveCmd MtrCtrlFault_PaHeightSwitch;/* '<S38>/MtrCtrlFault_PaHeightSwitch'
                                           * 硬线调节开关输入方向-副驾高度
                                           */
enSeatMoveCmd MtrCtrlFault_PaLengthSwitch;/* '<S38>/MtrCtrlFault_PaLengthSwitch'
                                           * 硬线调节开关输入方向-副驾纵向
                                           */
enIgnSts MtrCtrlFault_PaPowerModeStatus;/* '<S38>/MtrCtrlFault_PaPowerModeStatus'
                                         * 整车电源档位
                                         */
INT16U MtrCtrlFault_PaBackHallCnt;     /* '<S38>/MtrCtrlFault_PaBackHallCnt'
                                        * 靠背当前霍尔
                                        */
INT16U MtrCtrlFault_PaBackMotorSize;   /* '<S38>/MtrCtrlFault_PaBackMotorSize'
                                        * 靠背导轨长度
                                        */
INT16U MtrCtrlFault_PaBackStopPosi;    /* '<S38>/MtrCtrlFault_PaBackStopPosi'
                                        * 靠背硬止点位置
                                        */
INT16U MtrCtrlFault_PaFrontHallCnt;    /* '<S38>/MtrCtrlFault_PaFrontHallCnt'
                                        * 腿托当前霍尔
                                        */
INT16U MtrCtrlFault_PaFrontMotorSize;  /* '<S38>/MtrCtrlFault_PaFrontMotorSize'
                                        * 腿托导轨长度
                                        */
INT16U MtrCtrlFault_PaFrontStopPosi;   /* '<S38>/MtrCtrlFault_PaFrontStopPosi'
                                        * 腿托硬止点位置
                                        */
INT16U MtrCtrlFault_PaHeightHallCnt;   /* '<S38>/MtrCtrlFault_PaHeightHallCnt'
                                        * 高度当前霍尔
                                        */
INT16U MtrCtrlFault_PaHeightMotorSize; /* '<S38>/MtrCtrlFault_PaHeightMotorSize'
                                        * 高度导轨长度
                                        */
INT16U MtrCtrlFault_PaHeightStopPosi;  /* '<S38>/MtrCtrlFault_PaHeightStopPosi'
                                        * 高度硬止点位置
                                        */
INT16U MtrCtrlFault_PaLengthHallCnt;   /* '<S38>/MtrCtrlFault_PaLengthHallCnt'
                                        * 纵向当前霍尔
                                        */
INT16U MtrCtrlFault_PaLengthMotorSize; /* '<S38>/MtrCtrlFault_PaLengthMotorSize'
                                        * 纵向导轨长度
                                        */
INT16U MtrCtrlFault_PaLengthStopPosi;  /* '<S38>/MtrCtrlFault_PaLengthStopPosi'
                                        * 纵向硬止点位置
                                        */
INT8U MtrCtrlFault_PaAdjustCfg;        /* '<S38>/MtrCtrlFault_PaAdjustCfg'
                                        *  副驾座椅调节配置  0x00:手动调节  0x01:四向电机
                                        */
INT8U MtrCtrlFault_PaBackBackwardVolt; /* '<S38>/MtrCtrlFault_PaBackBackwardVolt'
                                        * 靠背向后
                                        */
INT8U MtrCtrlFault_PaBackCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaBackCurrentOverFlag'
                                          * 靠背反馈电流超过堵转阈值标志
                                          */
INT8U MtrCtrlFault_PaBackForwardVolt;  /* '<S38>/MtrCtrlFault_PaBackForwardVolt'
                                        * 靠背向前
                                        */
INT8U MtrCtrlFault_PaBackLearnFlag;    /* '<S38>/MtrCtrlFault_PaBackLearnFlag'
                                        * 靠背电机学习标志
                                        */
INT8U MtrCtrlFault_PaBackMotorCmd;     /* '<S38>/MtrCtrlFault_PaBackMotorCmd'
                                        * 模型输出到电机的CMD-副驾靠背
                                        */
INT8U MtrCtrlFault_PaBackSoftStopCnt;  /* '<S38>/MtrCtrlFault_PaBackSoftStopCnt'
                                        * 靠背到达软止点次数（E2）
                                        */
INT8U MtrCtrlFault_PaFrontCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaFrontCurrentOverFlag'
                                           * 腿托反馈电流超过堵转阈值标志
                                           */
INT8U MtrCtrlFault_PaFrontDownVolt;    /* '<S38>/MtrCtrlFault_PaFrontDownVolt'
                                        * 腿托向下
                                        */
INT8U MtrCtrlFault_PaFrontLearnFlag;   /* '<S38>/MtrCtrlFault_PaFrontLearnFlag'
                                        * 腿托电机学习标志
                                        */
INT8U MtrCtrlFault_PaFrontMotorCmd;    /* '<S38>/MtrCtrlFault_PaFrontMotorCmd'
                                        * 模型输出到电机的CMD-副驾腿托
                                        */
INT8U MtrCtrlFault_PaFrontSoftStopCnt; /* '<S38>/MtrCtrlFault_PaFrontSoftStopCnt'
                                        * 腿托到达软止点次数（E2）
                                        */
INT8U MtrCtrlFault_PaFrontUpVolt;      /* '<S38>/MtrCtrlFault_PaFrontUpVolt'
                                        * 腿托向上
                                        */
INT8U MtrCtrlFault_PaHeightCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaHeightCurrentOverFlag'
                                            * 高度反馈电流超过堵转阈值标志
                                            */
INT8U MtrCtrlFault_PaHeightDownVolt;   /* '<S38>/MtrCtrlFault_PaHeightDownVolt'
                                        * 高度向下
                                        */
INT8U MtrCtrlFault_PaHeightLearnFlag;  /* '<S38>/MtrCtrlFault_PaHeightLearnFlag'
                                        * 高度电机学习标志
                                        */
INT8U MtrCtrlFault_PaHeightMotorCmd;   /* '<S38>/MtrCtrlFault_PaHeightMotorCmd'
                                        * 模型输出到电机的CMD-副驾高度
                                        */
INT8U MtrCtrlFault_PaHeightSoftStopCnt;/* '<S38>/MtrCtrlFault_PaHeightSoftStopCnt'
                                        * 高度到达软止点次数（E2）
                                        */
INT8U MtrCtrlFault_PaHeightUpVolt;     /* '<S38>/MtrCtrlFault_PaHeightUpVolt'
                                        * 高度向上
                                        */
INT8U MtrCtrlFault_PaLengthBackwardVolt;/* '<S38>/MtrCtrlFault_PaLengthBackwardVolt'
                                         * 纵向向后
                                         */
INT8U MtrCtrlFault_PaLengthCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaLengthCurrentOverFlag'
                                            * 纵向反馈电流超过堵转阈值标志
                                            */
INT8U MtrCtrlFault_PaLengthForwardVolt;/* '<S38>/MtrCtrlFault_PaLengthForwardVolt'
                                        * 纵向向前
                                        */
INT8U MtrCtrlFault_PaLengthLearnFlag;  /* '<S38>/MtrCtrlFault_PaLengthLearnFlag'
                                        * 纵向电机学习标志
                                        */
INT8U MtrCtrlFault_PaLengthMotorCmd;   /* '<S38>/MtrCtrlFault_PaLengthMotorCmd'
                                        * 模型输出到电机的CMD-副驾纵向
                                        */
INT8U MtrCtrlFault_PaLengthSoftStopCnt;/* '<S38>/MtrCtrlFault_PaLengthSoftStopCnt'
                                        * 纵向到达软止点次数（E2）
                                        */
INT8U MtrCtrlFault_PaMemoryCfg;        /* '<S38>/MtrCtrlFault_PaMemoryCfg'
                                        *  副驾记忆迎宾配置  0:不存在  2：存在
                                        */
INT8U MtrCtrlFault_PaMotorSoftStopCntMax;/* '<S38>/MtrCtrlFault_PaMotorSoftStopCntMax'
                                          * 软止点最大调节次数（E2）
                                          */

/* Block signals (default storage) */
B_APPL_PaFaultDetection_T APPL_PaFaultDetection_B;

/* Block states (default storage) */
DW_APPL_PaFaultDetection_T APPL_PaFaultDetection_DW;

/* Real-time model */
RT_MODEL_APPL_PaFaultDetection_T APPL_PaFaultDetection_M_;
RT_MODEL_APPL_PaFaultDetection_T *const APPL_PaFaultDetection_M =
  &APPL_PaFaultDetection_M_;
static void APPL_PaFaultDetection_TimeDiffTs_Init(INT32U *rty_OutTs);
static void APPL_PaFaultDetection_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
  INT32U *rty_OutTs);
static void APPL_PaFaultDetection_GetDefTime_Init(INT32U *rty_OutTs);
static void APPL_PaFaultDetection_GetDefTime(INT32U rtu_DefTs, INT32U rtu_Ts,
  INT32U *rty_OutTs);
static void APPL_PaFaultDetection_CheckMidRelayFault_Init(INT8U
  *rty_MidRelayFault, INT8U *rty_MidRelayTimer,
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T *localDW);
static void APPL_PaFaultDetection_CheckMidRelayFault(INT8U rtu_MotorCmd, INT8U
  rtu_UpForwardVolt, INT8U rtu_DownBackwardVolt, INT8U *rty_MidRelayFault, INT8U
  *rty_MidRelayTimer, DW_CheckMidRelayFault_APPL_PaFaultDetection_T *localDW);
static void APPL_PaFaultDetection_GetCurMsTs(void);
static void APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt(void);
static void APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt(void);
static void APPL_PaFaultDetection_RTE_InputSignal(void);
static void APPL_PaFaultDetection_UpDataInputInfo(void);
static void APPL_PaFaultDetection_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void APPL_PaFaultDetection_inner_default_Judge_a(void);
static void APPL_PaFaultDetection_inner_default_Judge_aa(void);
static void APPL_PaFaultDetection_inner_default_Judge(const INT16U
  *MtrCtrlFault_LengthHallCnt_prev);
static void APPL_PaFaultDetection_inner_default_Judge_b(const INT16U
  *MtrCtrlFault_BackHallCnt_prev);
static void APPL_PaFaultDetection_enter_atomic_Init(void);
static INT32S APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd(INT32S input);

/* Output and update for function-call system: '<S12>/GetCurMsTs' */
static void APPL_PaFaultDetection_GetCurMsTs(void)
{
  APPL_PaFaultDetection_B.DrAdj_CurMsTs = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S12>/TimeDiffTs' */
static void APPL_PaFaultDetection_TimeDiffTs_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/* Output and update for function-call system: '<S12>/TimeDiffTs' */
static void APPL_PaFaultDetection_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
  INT32U *rty_OutTs)
{
  INT32U qY;
  INT32U q0;

  /*  入参比当前大  */
  if (rtu_lastTs > rtu_Ts)
  {
    q0 = 0xFFFFFFFF - rtu_lastTs;
    qY = q0 + rtu_Ts;
    if (qY < q0)
    {
      qY = MAX_uint32_T;
    }

    q0 = qY + 1U;
    if (q0 < qY)
    {
      q0 = MAX_uint32_T;
    }

    *rty_OutTs = q0;
  }
  else
  {
    qY = rtu_Ts - rtu_lastTs;
    if (qY > rtu_Ts)
    {
      qY = 0U;
    }

    *rty_OutTs = qY;
  }
}

/* System initialize for function-call system: '<S12>/GetDefTime' */
static void APPL_PaFaultDetection_GetDefTime_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/* Output and update for function-call system: '<S12>/GetDefTime' */
static void APPL_PaFaultDetection_GetDefTime(INT32U rtu_DefTs, INT32U rtu_Ts,
  INT32U *rty_OutTs)
{
  INT32U qY;

  /*  设置比当前小  */
  if (rtu_DefTs < rtu_Ts)
  {
    *rty_OutTs = 0xFFFFFFFF - rtu_DefTs;
  }
  else
  {
    qY = rtu_Ts - rtu_DefTs;
    if (qY > rtu_Ts)
    {
      qY = 0U;
    }

    *rty_OutTs = qY;
  }
}

/*
 * System initialize for function-call system:
 *    '<S21>/CheckMidRelayFault'
 *    '<S21>/CheckMidRelayFault1'
 *    '<S21>/CheckMidRelayFault2'
 *    '<S21>/CheckMidRelayFault3'
 */
static void APPL_PaFaultDetection_CheckMidRelayFault_Init(INT8U
  *rty_MidRelayFault, INT8U *rty_MidRelayTimer,
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T *localDW)
{
  localDW->is_active_c4_APPL_PaFaultDetection = 0U;
  localDW->is_c4_APPL_PaFaultDetection =
    APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_h;
  *rty_MidRelayFault = 0U;
  *rty_MidRelayTimer = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S21>/CheckMidRelayFault'
 *    '<S21>/CheckMidRelayFault1'
 *    '<S21>/CheckMidRelayFault2'
 *    '<S21>/CheckMidRelayFault3'
 */
static void APPL_PaFaultDetection_CheckMidRelayFault(INT8U rtu_MotorCmd, INT8U
  rtu_UpForwardVolt, INT8U rtu_DownBackwardVolt, INT8U *rty_MidRelayFault, INT8U
  *rty_MidRelayTimer, DW_CheckMidRelayFault_APPL_PaFaultDetection_T *localDW)
{
  INT16U tmp;
  INT32S tmp_0;
  INT32S tmp_1;
  if (localDW->is_active_c4_APPL_PaFaultDetection == 0U)
  {
    localDW->is_active_c4_APPL_PaFaultDetection = 1U;
    localDW->is_c4_APPL_PaFaultDetection = APPL_PaFaultDetection_IN_Normal;
    *rty_MidRelayFault = ((BOOL)FALSE);
    *rty_MidRelayTimer = 0U;
  }
  else if (localDW->is_c4_APPL_PaFaultDetection ==
           APPL_PaFaultDetection_IN_Judge)
  {
    /* 继电器粘连消失：
       1、没有控制开启命令，同时没有电压输出，认为继电器粘连消失
       2、控制开启命令，存在对应的电压输出，认为继电器粘连消失 */
    if ((((INT32S)enSeatMoveCmd_EN_NULL == rtu_MotorCmd) && (((BOOL)FALSE) ==
          rtu_UpForwardVolt) && (((BOOL)FALSE) == rtu_DownBackwardVolt)) ||
        (((INT32S)enSeatMoveCmd_EN_UP_FORWARD == rtu_MotorCmd) && (((BOOL)TRUE) ==
          rtu_UpForwardVolt) && (((BOOL)FALSE) == rtu_DownBackwardVolt)) ||
        (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD == rtu_MotorCmd) && (((BOOL)FALSE)
          == rtu_UpForwardVolt) && (((BOOL)TRUE) == rtu_DownBackwardVolt)))
    {
      localDW->is_c4_APPL_PaFaultDetection = APPL_PaFaultDetection_IN_Normal;
      *rty_MidRelayFault = ((BOOL)FALSE);
      *rty_MidRelayTimer = 0U;
    }
    else if (CAL_MotorRelayErr_2s <= *rty_MidRelayTimer)
    {
      tmp = CAL_MotorRelayErr_2s;
      if (CAL_MotorRelayErr_2s > 255)
      {
        tmp = 255U;
      }

      *rty_MidRelayTimer = (INT8U)tmp;
      if (((INT32S)enSeatMoveCmd_EN_UP_FORWARD != rtu_MotorCmd) && (((BOOL)FALSE)
           != rtu_UpForwardVolt))
      {
        *rty_MidRelayFault = ((INT8U)D_Relay_UpFrontFault);
      }
      else
      {
        if (((INT32S)enSeatMoveCmd_EN_DN_BACKWARD != rtu_MotorCmd) && (((BOOL)
              FALSE) != rtu_DownBackwardVolt))
        {
          *rty_MidRelayFault = ((INT8U)D_Relay_DownBackFault);
        }
      }
    }
    else
    {
      tmp_0 = *rty_MidRelayTimer + 1;
      if (tmp_0 > 255)
      {
        tmp_0 = 255;
      }

      *rty_MidRelayTimer = (INT8U)tmp_0;
    }
  }
  else
  {
    /* 没有输出命令但输出反馈有电压 满足前置条件 */
    tmp_0 = enSeatMoveCmd_EN_UP_FORWARD;
    tmp_1 = enSeatMoveCmd_EN_DN_BACKWARD;
    if ((((INT32S)enSeatMoveCmd_EN_NULL == rtu_MotorCmd) && ((((BOOL)FALSE) !=
           rtu_UpForwardVolt) || (((BOOL)FALSE) != rtu_DownBackwardVolt))) ||
        ((tmp_0 == rtu_MotorCmd) && (((BOOL)FALSE) != rtu_DownBackwardVolt)) ||
        ((tmp_1 == rtu_MotorCmd) && (((BOOL)FALSE) != rtu_UpForwardVolt)))
    {
      localDW->is_c4_APPL_PaFaultDetection = APPL_PaFaultDetection_IN_Judge;
      if (CAL_MotorRelayErr_2s <= *rty_MidRelayTimer)
      {
        tmp = CAL_MotorRelayErr_2s;
        if (CAL_MotorRelayErr_2s > 255)
        {
          tmp = 255U;
        }

        *rty_MidRelayTimer = (INT8U)tmp;
        if ((tmp_0 != rtu_MotorCmd) && (((BOOL)FALSE) != rtu_UpForwardVolt))
        {
          *rty_MidRelayFault = ((INT8U)D_Relay_UpFrontFault);
        }
        else
        {
          if ((tmp_1 != rtu_MotorCmd) && (((BOOL)FALSE) != rtu_DownBackwardVolt))
          {
            *rty_MidRelayFault = ((INT8U)D_Relay_DownBackFault);
          }
        }
      }
      else
      {
        tmp_0 = *rty_MidRelayTimer + 1;
        if (tmp_0 > 255)
        {
          tmp_0 = 255;
        }

        *rty_MidRelayTimer = (INT8U)tmp_0;
      }
    }
    else
    {
      /* 输出命令向前/向上命令却有向后/向下电压  */
      /* 输出命令向后/向下命令却有向前/向上电压  */
    }
  }
}

/* Output and update for function-call system: '<S30>/DrAdj_SetLengthSoftStopCnt' */
static void APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_PaLengthSoftStopCnt,
    APPL_PaFaultDetection_B.Cnt_h);
}

/* Output and update for function-call system: '<S30>/DrAdj_SetBackSoftStopCnt' */
static void APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_PaBackSoftStopCnt,
    APPL_PaFaultDetection_B.Cnt_i);
}

/*
 * Output and update for atomic system: '<S3>/RTE_InputSignal'
 * Block description for: '<S3>/RTE_InputSignal'
 *   接口自动生成
 */
static void APPL_PaFaultDetection_RTE_InputSignal(void)
{
  MtrCtrlFault_PaAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
  MtrCtrlFault_PaBackBackwardVolt = Ecual_GetPaRelayFlagBackBackward( );
  MtrCtrlFault_PaBackCurrentOverFlag = Ecual_GetPrBackOverCurrentFlag( );
  MtrCtrlFault_PaBackForwardVolt = Ecual_GetPaRelayFlagBackForward( );
  MtrCtrlFault_PaBackHallCnt = Cdd_GetCurrentHallCnt(EN_PassengerBack);
  MtrCtrlFault_PaBackLearnFlag = Cdd_GetMotorLearnFlag(EN_PassengerBack);
  MtrCtrlFault_PaBackMotorCmd = Rte_GetVfb_PaBackMotorCmd( );
  MtrCtrlFault_PaBackMotorSize = Cdd_GetMotorSize(EN_PassengerBack);
  MtrCtrlFault_PaBackSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaBackSoftStopCnt);
  MtrCtrlFault_PaBackStopPosi = Cdd_GetMotorHardStop(EN_PassengerBack);
  MtrCtrlFault_PaBackSwitch = Ecual_GetPaBackSwitchCmd( );
  MtrCtrlFault_PaFrontCurrentOverFlag = Ecual_GetPrFrontOverCurrentFlag( );
  MtrCtrlFault_PaFrontDownVolt = Ecual_GetPaRelayFlagFrontDown( );
  MtrCtrlFault_PaFrontHallCnt = Cdd_GetCurrentHallCnt(EN_PaResever_2);
  MtrCtrlFault_PaFrontLearnFlag = Cdd_GetMotorLearnFlag(EN_PaResever_2);
  MtrCtrlFault_PaFrontMotorCmd = Rte_GetVfb_PaFrontMotorCmd( );
  MtrCtrlFault_PaFrontMotorSize = Cdd_GetMotorSize(EN_PaResever_2);
  MtrCtrlFault_PaFrontSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaFrontSoftStopCnt);
  MtrCtrlFault_PaFrontStopPosi = Cdd_GetMotorHardStop(EN_PaResever_2);
  MtrCtrlFault_PaFrontSwitch = Ecual_GetPaFrontSwitchCmd( );
  MtrCtrlFault_PaFrontUpVolt = Ecual_GetPaRelayFlagFrontUp( );
  MtrCtrlFault_PaHeightCurrentOverFlag = Ecual_GetPrHeightOverCurrentFlag( );
  MtrCtrlFault_PaHeightDownVolt = Ecual_GetPaRelayFlagHeightDN( );
  MtrCtrlFault_PaHeightHallCnt = Cdd_GetCurrentHallCnt(EN_PaResever_1);
  MtrCtrlFault_PaHeightLearnFlag = Cdd_GetMotorLearnFlag(EN_PaResever_1);
  MtrCtrlFault_PaHeightMotorCmd = Rte_GetVfb_PaHeightMotorCmd( );
  MtrCtrlFault_PaHeightMotorSize = Cdd_GetMotorSize(EN_PaResever_1);
  MtrCtrlFault_PaHeightSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaHeightSoftStopCnt);
  MtrCtrlFault_PaHeightStopPosi = Cdd_GetMotorHardStop(EN_PaResever_1);
  MtrCtrlFault_PaHeightSwitch = Ecual_GetPaHeightSwitchCmd( );
  MtrCtrlFault_PaHeightUpVolt = Ecual_GetPaRelayFlagHeightUp( );
  MtrCtrlFault_PaLengthBackwardVolt = Ecual_GetPaRelayFlagLenghtBackward( );
  MtrCtrlFault_PaLengthCurrentOverFlag = Ecual_GetPrLengthOverCurrentFlag( );
  MtrCtrlFault_PaLengthForwardVolt = Ecual_GetPaRelayFlagLenghtForward( );
  MtrCtrlFault_PaLengthHallCnt = Cdd_GetCurrentHallCnt(EN_PassengerLength);
  MtrCtrlFault_PaLengthLearnFlag = Cdd_GetMotorLearnFlag(EN_PassengerLength);
  MtrCtrlFault_PaLengthMotorCmd = Rte_GetVfb_PaLengthMotorCmd( );
  MtrCtrlFault_PaLengthMotorSize = Cdd_GetMotorSize(EN_PassengerLength);
  MtrCtrlFault_PaLengthSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaLengthSoftStopCnt);
  MtrCtrlFault_PaLengthStopPosi = Cdd_GetMotorHardStop(EN_PassengerLength);
  MtrCtrlFault_PaLengthSwitch = Ecual_GetPaLengthSwitchCmd( );
  MtrCtrlFault_PaMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
  MtrCtrlFault_PaMotorSoftStopCntMax = Srvl_GetMemIndexDataU8
    (EN_MemIndex_MotorSoftStopCntMax);
  MtrCtrlFault_PaPowerModeStatus = Rte_GetVfb_PowerMode( );
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void APPL_PaFaultDetection_UpDataInputInfo(void)
{
  APPL_PaFaultDetection_RTE_InputSignal();
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void APPL_PaFaultDetection_UpDataOutputInfo(void)
{
  APPL_PaFaultDetection_B.DataTypeConversion1 = (INT8U)
    ((APPL_PaFaultDetection_B.HeightStallFault != 0) ||
     (APPL_PaFaultDetection_B.LengthStallFault != 0) ||
     (APPL_PaFaultDetection_B.BackStallFault != 0) ||
     (APPL_PaFaultDetection_B.FrontStallFault != 0));
  APPL_PaFaultDetection_B.DataTypeConversion2 = (INT8U)
    ((APPL_PaFaultDetection_B.HeightMidRelayFault != 0) ||
     (APPL_PaFaultDetection_B.LengthMidRelayFault != 0) ||
     (APPL_PaFaultDetection_B.BackMidRelayFault != 0) ||
     (APPL_PaFaultDetection_B.FrontMidRelayFault != 0));
  APPL_PaFaultDetection_B.DataTypeConversion3 = (INT8U)
    ((APPL_PaFaultDetection_B.HeightSoftStopFault != 0) ||
     (APPL_PaFaultDetection_B.LengthSoftStopFault != 0) ||
     (APPL_PaFaultDetection_B.BackSoftStopFault != 0) ||
     (APPL_PaFaultDetection_B.FrontSoftStopFault != 0));
  APPL_PaFaultDetection_B.DataTypeConversion4 = (INT8U)
    ((APPL_PaFaultDetection_B.HeightSwAdhesionFault != 0) ||
     (APPL_PaFaultDetection_B.LengthSwAdhesionFault != 0) ||
     (APPL_PaFaultDetection_B.BackSwAdhesionFault != 0) ||
     (APPL_PaFaultDetection_B.FrontSwAdhesionFault != 0));
  APPL_PaFaultDetection_B.DataTypeConversion5 = (INT8U)
    ((APPL_PaFaultDetection_B.Desc_HeightHallDTC != 0) ||
     (APPL_PaFaultDetection_B.Desc_LengthHallDTC != 0) ||
     (APPL_PaFaultDetection_B.Desc_BackHallDTC != 0) ||
     (APPL_PaFaultDetection_B.Desc_FrontHallDTC != 0));
  APPL_PaFaultDetection_B.DataTypeConversion6 = (INT8U)
    ((APPL_PaFaultDetection_B.HeightHallFault != 0) ||
     (APPL_PaFaultDetection_B.LengthHallFault != 0) ||
     (APPL_PaFaultDetection_B.BackHallFault != 0) ||
     (APPL_PaFaultDetection_B.FrontHallFault != 0));
  Rte_SetVfb_PaHeightMotorTimeOutErr(APPL_PaFaultDetection_B.HeightTimeOutFlag);
  Rte_SetVfb_PaLengthMotorTimeOutErr(APPL_PaFaultDetection_B.LengthTimeOutFlag);
  Rte_SetVfb_PaHeightSwitchCmd(APPL_PaFaultDetection_B.CurrentHeightSwCmd);
  Rte_SetVfb_PaLengthSwitchCmd(APPL_PaFaultDetection_B.CurrentLengthSwCmd);
  Rte_SetVfb_PaBackSwitchCmd(APPL_PaFaultDetection_B.CurrentBackSwCmd);
  Rte_SetVfb_PaFrontSwitchCmd(APPL_PaFaultDetection_B.CurrentFrontSwCmd);
  Rte_SetVfb_PaHeightSwitchAdheErr(APPL_PaFaultDetection_B.HeightSwAdhesionFault);
  Rte_SetVfb_PaLengthSwitchAdheErr(APPL_PaFaultDetection_B.LengthSwAdhesionFault);
  Rte_SetVfb_PaBackMotorTimeOutErr(APPL_PaFaultDetection_B.BackTimeOutFlag);
  Rte_SetVfb_PaBackSwitchAdheErr(APPL_PaFaultDetection_B.BackSwAdhesionFault);
  Rte_SetVfb_PaFrontSwitchAdheErr(APPL_PaFaultDetection_B.FrontSwAdhesionFault);
  Rte_SetVfb_PaFrontMotorTimeOutErr(APPL_PaFaultDetection_B.FrontTimeOutFlag);
  Rte_SetVfb_PaAnyoneSwitchAdheErr(APPL_PaFaultDetection_B.DataTypeConversion4);
  Rte_SetVfb_PaHeightHallErr(APPL_PaFaultDetection_B.HeightHallFault);
  Rte_SetVfb_PaLengthHallErr(APPL_PaFaultDetection_B.LengthHallFault);
  Rte_SetVfb_DrBackHallErr(APPL_PaFaultDetection_B.BackHallFault);
  Rte_SetVfb_PaHeightStallErr(APPL_PaFaultDetection_B.HeightStallFault);
  Rte_SetVfb_PaLengthStallErr(APPL_PaFaultDetection_B.LengthStallFault);
  Rte_SetVfb_PaBackStallErr(APPL_PaFaultDetection_B.BackStallFault);
  Rte_SetVfb_PaFrontStallErr(APPL_PaFaultDetection_B.FrontStallFault);
  Rte_SetVfb_PaAnyoneStallErr(APPL_PaFaultDetection_B.DataTypeConversion1);
  Rte_SetVfb_PaAnyoneRelayAdheErr(APPL_PaFaultDetection_B.DataTypeConversion2);
  Rte_SetVfb_PaLengthSwitchAdheErr_ForWard
    (APPL_PaFaultDetection_B.LengthSwUpAdhesionFault);
  Rte_SetVfb_PaAnyoneSoftStopErr(APPL_PaFaultDetection_B.DataTypeConversion3);
  Rte_SetVfb_PaAnyoneDTCHallErr(APPL_PaFaultDetection_B.DataTypeConversion5);
  Rte_SetVfb_PaHeightRelayAdheErr(APPL_PaFaultDetection_B.HeightMidRelayFault);
  Rte_SetVfb_PaLengthRelayAdheErr(APPL_PaFaultDetection_B.LengthMidRelayFault);
  Rte_SetVfb_PaBackRelayAdheErr(APPL_PaFaultDetection_B.BackMidRelayFault);
  Rte_SetVfb_PaFrontRelayAdheErr(APPL_PaFaultDetection_B.FrontMidRelayFault);
  Rte_SetVfb_PaAnyoneHallErr(APPL_PaFaultDetection_B.DataTypeConversion6);
  Rte_SetVfb_PaLengthSwitchAdheErr_Back
    (APPL_PaFaultDetection_B.LengthSwDownAdhesionFault);
  Rte_SetVfb_PaHeightSoftStopErr(APPL_PaFaultDetection_B.HeightSoftStopFault);
  Rte_SetVfb_PaLengthSoftStopErr(APPL_PaFaultDetection_B.LengthSoftStopFault);
  Rte_SetVfb_PaBackSoftStopErr(APPL_PaFaultDetection_B.BackSoftStopFault);
  Rte_SetVfb_PaFrontSoftStopErr(APPL_PaFaultDetection_B.FrontSoftStopFault);
  Rte_SetVfb_PaHeightDTCHallErr(APPL_PaFaultDetection_B.Desc_HeightHallDTC);
  Rte_SetVfb_PaLengthDTCHallErr(APPL_PaFaultDetection_B.Desc_LengthHallDTC);
  Rte_SetVfb_PaBackSwitchAdheErr_ForWard
    (APPL_PaFaultDetection_B.BackSwUpAdhesionFault);
  Rte_SetVfb_PaBackDTCHallErr(APPL_PaFaultDetection_B.Desc_BackHallDTC);
  Rte_SetVfb_PaFrontDTCHallErr(APPL_PaFaultDetection_B.Desc_FrontHallDTC);
  Rte_SetVfb_PaFrontHallErr(APPL_PaFaultDetection_B.FrontHallFault);
  Rte_SetVfb_PaBackSwitchAdheErr_Back
    (APPL_PaFaultDetection_B.BackSwDownAdhesionFault);
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_PaFaultDetection_inner_default_Judge_a(void)
{
  INT32S tmp;

  /* 达到堵转电流 且无霍尔变化 */
  if (APPL_PaFaultDetection_DW.LocalLengthHallCnt ==
      MtrCtrlFault_PaLengthHallCnt)
  {
    if (1 == MtrCtrlFault_PaLengthCurrentOverFlag)
    {
      if (APPL_PaFaultDetection_DW.CurrentOverTimer2 < 255)
      {
        /*  纵向大电流计时器 */
        tmp = APPL_PaFaultDetection_DW.CurrentOverTimer2 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_PaFaultDetection_DW.CurrentOverTimer2 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_PaFaultDetection_DW.CurrentOverTimer2 = 0U;
    }

    /* 纵向的堵转条件检测 */
    if ((APPL_PaFaultDetection_DW.LengthStallTimer > CAL_MotorStall_750ms) &&
        (APPL_PaFaultDetection_DW.CurrentOverTimer2 > 20))
    {
      APPL_PaFaultDetection_DW.LengthStallTimer = CAL_MotorStall_750ms;
      APPL_PaFaultDetection_B.LengthStallFault = 1U;
      APPL_PaFaultDetection_DW.LengthStallNoTimer = 0U;
    }
    else
    {
      tmp = APPL_PaFaultDetection_DW.LengthStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_PaFaultDetection_DW.LengthStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_PaFaultDetection_DW.LengthStallTimer = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer2 = 0U;
  }

  APPL_PaFaultDetection_DW.LocalLengthHallCnt = MtrCtrlFault_PaLengthHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaLengthMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_PaFaultDetection_B.LengthSwCmd))
  {
    tmp = APPL_PaFaultDetection_DW.LengthStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_PaFaultDetection_DW.LengthStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_PaFaultDetection_inner_default_Judge_aa(void)
{
  INT32S tmp;

  /*  无霍尔变化超时检测 */
  if (APPL_PaFaultDetection_DW.LocalBackHallCnt == MtrCtrlFault_PaBackHallCnt)
  {
    if (1 == MtrCtrlFault_PaBackCurrentOverFlag)
    {
      if (APPL_PaFaultDetection_DW.CurrentOverTimer3 < 255)
      {
        /*  靠背大电流计时器 */
        tmp = APPL_PaFaultDetection_DW.CurrentOverTimer3 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_PaFaultDetection_DW.CurrentOverTimer3 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_PaFaultDetection_DW.CurrentOverTimer3 = 0U;
    }

    /* 靠背的堵转条件检测 */
    if ((APPL_PaFaultDetection_DW.BackStallTimer > CAL_MotorStall_750ms) &&
        (APPL_PaFaultDetection_DW.CurrentOverTimer3 > 20))
    {
      APPL_PaFaultDetection_DW.BackStallTimer = CAL_MotorStall_750ms;
      APPL_PaFaultDetection_B.BackStallFault = 1U;
      APPL_PaFaultDetection_DW.BackStallNoTimer = 0U;
    }
    else
    {
      tmp = APPL_PaFaultDetection_DW.BackStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_PaFaultDetection_DW.BackStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_PaFaultDetection_DW.BackStallTimer = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer3 = 0U;
  }

  APPL_PaFaultDetection_DW.LocalBackHallCnt = MtrCtrlFault_PaBackHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaBackMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_PaFaultDetection_B.BackSwCmd))
  {
    tmp = APPL_PaFaultDetection_DW.BackStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_PaFaultDetection_DW.BackStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_PaFaultDetection_inner_default_Judge(const INT16U
  *MtrCtrlFault_LengthHallCnt_prev)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_PaFaultDetection_DW.LengthHallTimer)
  {
    /* 粘连或无电机动作 */
    if ((MtrCtrlFault_PaLengthForwardVolt == MtrCtrlFault_PaLengthBackwardVolt) ||
        ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaLengthMotorCmd))
    {
      APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
    }
    else
    {
      tmp = APPL_PaFaultDetection_DW.LengthHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_PaFaultDetection_DW.LengthHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_PaFaultDetection_DW.LengthHallTimer = CAL_MotorHallInvalid_2s;
    APPL_PaFaultDetection_B.LengthHallFault = 1U;
    APPL_PaFaultDetection_B.Desc_LengthHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (*MtrCtrlFault_LengthHallCnt_prev !=
      APPL_PaFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start)
  {
    APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
    APPL_PaFaultDetection_B.LengthHallFault = 0U;
    APPL_PaFaultDetection_B.Desc_LengthHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_PaFaultDetection_inner_default_Judge_b(const INT16U
  *MtrCtrlFault_BackHallCnt_prev)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_PaFaultDetection_DW.BackHallTimer)
  {
    /* 粘连或无电机动作 */
    if ((MtrCtrlFault_PaBackForwardVolt == MtrCtrlFault_PaBackBackwardVolt) ||
        ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaBackMotorCmd))
    {
      APPL_PaFaultDetection_DW.BackHallTimer = 0U;
    }
    else
    {
      tmp = APPL_PaFaultDetection_DW.BackHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_PaFaultDetection_DW.BackHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_PaFaultDetection_DW.BackHallTimer = CAL_MotorHallInvalid_2s;
    APPL_PaFaultDetection_B.BackHallFault = 1U;
    APPL_PaFaultDetection_B.Desc_BackHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (*MtrCtrlFault_BackHallCnt_prev !=
      APPL_PaFaultDetection_DW.MtrCtrlFault_BackHallCnt_start)
  {
    APPL_PaFaultDetection_DW.BackHallTimer = 0U;
    APPL_PaFaultDetection_B.BackHallFault = 0U;
    APPL_PaFaultDetection_B.Desc_BackHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_PaFaultDetection_enter_atomic_Init(void)
{
  APPL_PaFaultDetection_B.HeightHallFault = 0U;
  APPL_PaFaultDetection_B.Desc_HeightHallDTC = 0U;
  APPL_PaFaultDetection_B.LengthHallFault = 0U;
  APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
  APPL_PaFaultDetection_B.Desc_LengthHallDTC = 0U;
  APPL_PaFaultDetection_B.BackHallFault = 0U;
  APPL_PaFaultDetection_DW.BackHallTimer = 0U;
  APPL_PaFaultDetection_B.Desc_BackHallDTC = 0U;
  APPL_PaFaultDetection_B.FrontHallFault = 0U;
  APPL_PaFaultDetection_B.Desc_FrontHallDTC = 0U;
}

static INT32S APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enSeatMoveCmd (EN_NULL) */
  y = 0;
  if ((input >= 0) && (input <= 2))
  {
    /* Set output value to input value if it is a member of enSeatMoveCmd */
    y = input;
  }

  return y;
}

/* Model step function */
void APPL_PaFaultDetection_step(void)
{
  enSeatMoveCmd MtrCtrlFault_DRLengthSwitch_prev;
  enSeatMoveCmd MtrCtrlFault_DRBackSwitch_prev;
  INT32U OutTs_e;
  INT16U MtrCtrlFault_LengthHallCnt_prev;
  INT16U MtrCtrlFault_BackHallCnt_prev;
  INT32S tmp;
  APPL_PaFaultDetection_UpDataInputInfo();
  MtrCtrlFault_DRLengthSwitch_prev =
    APPL_PaFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start;
  APPL_PaFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start =
    MtrCtrlFault_PaLengthSwitch;
  MtrCtrlFault_DRBackSwitch_prev =
    APPL_PaFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start;
  APPL_PaFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start =
    MtrCtrlFault_PaBackSwitch;
  if (APPL_PaFaultDetection_DW.is_active_c8_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c8_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_LengthSwitchErrorDeal =
      APPL_PaFaultDetection_IN_Invalid;
    APPL_PaFaultDetection_GetCurMsTs();
    APPL_PaFaultDetection_DW.LengthSwTimer =
      APPL_PaFaultDetection_B.DrAdj_CurMsTs;
    APPL_PaFaultDetection_B.LengthSwAdhesionFault = ((BOOL)FALSE);
    APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
    APPL_PaFaultDetection_DW.is_BackSwitchErrorDeal =
      APPL_PaFaultDetection_IN_Invalid;
    APPL_PaFaultDetection_GetCurMsTs();
    APPL_PaFaultDetection_DW.BackSwTimer = APPL_PaFaultDetection_B.DrAdj_CurMsTs;
    APPL_PaFaultDetection_B.BackSwAdhesionFault = ((BOOL)FALSE);
    APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
  }
  else
  {
    if (APPL_PaFaultDetection_DW.is_LengthSwitchErrorDeal ==
        APPL_PaFaultDetection_IN_Invalid)
    {
      /* 开关有效   */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaLengthSwitch)
      {
        APPL_PaFaultDetection_DW.is_LengthSwitchErrorDeal =
          APPL_PaFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_TimeDiffTs(APPL_PaFaultDetection_DW.LengthSwTimer,
          APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_PaFaultDetection_GetCurMsTs();
          APPL_PaFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_PaFaultDetection_DW.LengthSwTimer = OutTs_e;
          APPL_PaFaultDetection_B.LengthSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_PaLengthSwitch)
          {
            APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_PaFaultDetection_B.LengthSwCmd = MtrCtrlFault_PaLengthSwitch;
          APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_DW.LengthSwTimer =
          APPL_PaFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaLengthSwitch) ||
          (MtrCtrlFault_DRLengthSwitch_prev !=
           APPL_PaFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start))
      {
        APPL_PaFaultDetection_DW.is_LengthSwitchErrorDeal =
          APPL_PaFaultDetection_IN_Invalid;
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_DW.LengthSwTimer =
          APPL_PaFaultDetection_B.DrAdj_CurMsTs;
        APPL_PaFaultDetection_B.LengthSwAdhesionFault = ((BOOL)FALSE);
        APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_TimeDiffTs(APPL_PaFaultDetection_DW.LengthSwTimer,
          APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_PaFaultDetection_GetCurMsTs();
          APPL_PaFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_PaFaultDetection_DW.LengthSwTimer = OutTs_e;
          APPL_PaFaultDetection_B.LengthSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_PaLengthSwitch)
          {
            APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_PaFaultDetection_B.LengthSwCmd = MtrCtrlFault_PaLengthSwitch;
          APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_PaFaultDetection_DW.is_BackSwitchErrorDeal ==
        APPL_PaFaultDetection_IN_Invalid)
    {
      /* 开关有效   */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaBackSwitch)
      {
        APPL_PaFaultDetection_DW.is_BackSwitchErrorDeal =
          APPL_PaFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_TimeDiffTs(APPL_PaFaultDetection_DW.BackSwTimer,
          APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_PaFaultDetection_GetCurMsTs();
          APPL_PaFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_PaFaultDetection_DW.BackSwTimer = OutTs_e;
          APPL_PaFaultDetection_B.BackSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_PaBackSwitch)
          {
            APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_PaFaultDetection_B.BackSwCmd = MtrCtrlFault_PaBackSwitch;
          APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_DW.BackSwTimer =
          APPL_PaFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaBackSwitch) ||
          (MtrCtrlFault_DRBackSwitch_prev !=
           APPL_PaFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start))
      {
        APPL_PaFaultDetection_DW.is_BackSwitchErrorDeal =
          APPL_PaFaultDetection_IN_Invalid;
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_DW.BackSwTimer =
          APPL_PaFaultDetection_B.DrAdj_CurMsTs;
        APPL_PaFaultDetection_B.BackSwAdhesionFault = ((BOOL)FALSE);
        APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_PaFaultDetection_GetCurMsTs();
        APPL_PaFaultDetection_TimeDiffTs(APPL_PaFaultDetection_DW.BackSwTimer,
          APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_PaFaultDetection_GetCurMsTs();
          APPL_PaFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_PaFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_PaFaultDetection_DW.BackSwTimer = OutTs_e;
          APPL_PaFaultDetection_B.BackSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_PaBackSwitch)
          {
            APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_PaFaultDetection_B.BackSwCmd = MtrCtrlFault_PaBackSwitch;
          APPL_PaFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_PaFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }
  }

  MtrCtrlFault_DRLengthSwitch_prev = APPL_PaFaultDetection_DW.LengthSwCmd_start;
  APPL_PaFaultDetection_DW.LengthSwCmd_start =
    APPL_PaFaultDetection_B.LengthSwCmd;
  MtrCtrlFault_DRBackSwitch_prev = APPL_PaFaultDetection_DW.BackSwCmd_start;
  APPL_PaFaultDetection_DW.BackSwCmd_start = APPL_PaFaultDetection_B.BackSwCmd;
  if (APPL_PaFaultDetection_DW.is_active_c10_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c10_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_LengthStallError =
      APPL_PaFaultDetection_IN_Normal_o;
    APPL_PaFaultDetection_B.LengthStallFault = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer2 = 0U;
    APPL_PaFaultDetection_DW.is_BackStallError =
      APPL_PaFaultDetection_IN_Normal_o;
    APPL_PaFaultDetection_B.BackStallFault = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer3 = 0U;
  }
  else
  {
    if (APPL_PaFaultDetection_DW.is_LengthStallError ==
        APPL_PaFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms < APPL_PaFaultDetection_DW.LengthStallNoTimer)
          || (MtrCtrlFault_DRLengthSwitch_prev !=
              APPL_PaFaultDetection_DW.LengthSwCmd_start) ||
          (MtrCtrlFault_PaPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_PaFaultDetection_DW.LengthStallTimer = 0U;
        APPL_PaFaultDetection_DW.LengthStallNoTimer = 0U;
        APPL_PaFaultDetection_DW.is_LengthStallError =
          APPL_PaFaultDetection_IN_Normal_o;
        APPL_PaFaultDetection_B.LengthStallFault = 0U;
        APPL_PaFaultDetection_DW.CurrentOverTimer2 = 0U;
      }
      else
      {
        APPL_PaFaultDetection_inner_default_Judge_a();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaLengthMotorCmd) &&
          (MtrCtrlFault_PaPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_PaFaultDetection_DW.is_LengthStallError =
          APPL_PaFaultDetection_IN_Judge_e;
        APPL_PaFaultDetection_inner_default_Judge_a();
      }
    }

    if (APPL_PaFaultDetection_DW.is_BackStallError ==
        APPL_PaFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms < APPL_PaFaultDetection_DW.BackStallNoTimer) ||
          (MtrCtrlFault_DRBackSwitch_prev !=
           APPL_PaFaultDetection_DW.BackSwCmd_start) ||
          (MtrCtrlFault_PaPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_PaFaultDetection_DW.BackStallTimer = 0U;
        APPL_PaFaultDetection_DW.BackStallNoTimer = 0U;
        APPL_PaFaultDetection_DW.is_BackStallError =
          APPL_PaFaultDetection_IN_Normal_o;
        APPL_PaFaultDetection_B.BackStallFault = 0U;
        APPL_PaFaultDetection_DW.CurrentOverTimer3 = 0U;
      }
      else
      {
        APPL_PaFaultDetection_inner_default_Judge_aa();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaBackMotorCmd) &&
          (MtrCtrlFault_PaPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_PaFaultDetection_DW.is_BackStallError =
          APPL_PaFaultDetection_IN_Judge_e;
        APPL_PaFaultDetection_inner_default_Judge_aa();
      }
    }
  }

  MtrCtrlFault_LengthHallCnt_prev =
    APPL_PaFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start;
  APPL_PaFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start =
    MtrCtrlFault_PaLengthHallCnt;
  MtrCtrlFault_DRLengthSwitch_prev =
    APPL_PaFaultDetection_DW.LengthSwCmd_start_g;
  APPL_PaFaultDetection_DW.LengthSwCmd_start_g =
    APPL_PaFaultDetection_B.LengthSwCmd;
  MtrCtrlFault_BackHallCnt_prev =
    APPL_PaFaultDetection_DW.MtrCtrlFault_BackHallCnt_start;
  APPL_PaFaultDetection_DW.MtrCtrlFault_BackHallCnt_start =
    MtrCtrlFault_PaBackHallCnt;
  MtrCtrlFault_DRBackSwitch_prev = APPL_PaFaultDetection_DW.BackSwCmd_start_c;
  APPL_PaFaultDetection_DW.BackSwCmd_start_c = APPL_PaFaultDetection_B.BackSwCmd;
  if (APPL_PaFaultDetection_DW.is_active_c9_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c9_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_c9_APPL_PaFaultDetection =
      APPL_PaFaultDetection_IN_Init;
    APPL_PaFaultDetection_enter_atomic_Init();
  }
  else if (APPL_PaFaultDetection_DW.is_c9_APPL_PaFaultDetection ==
           APPL_PaFaultDetection_IN_Init)
  {
    APPL_PaFaultDetection_B.HeightHallFault = 0U;
    APPL_PaFaultDetection_B.Desc_HeightHallDTC = 0U;
    APPL_PaFaultDetection_B.FrontHallFault = 0U;
    APPL_PaFaultDetection_B.Desc_FrontHallDTC = 0U;

    /*  有记忆功能 且非不可调节配置  */
    if ((((BOOL)TRUE) == MtrCtrlFault_PaMemoryCfg) && (((BOOL)TRUE) ==
         MtrCtrlFault_PaAdjustCfg))
    {
      APPL_PaFaultDetection_DW.is_c9_APPL_PaFaultDetection =
        APPL_PaFaultDetection_IN_MotorHallDetect;
      APPL_PaFaultDetection_DW.is_LengthHallError =
        APPL_PaFaultDetection_IN_Normal_c;
      APPL_PaFaultDetection_B.LengthHallFault = 0U;
      APPL_PaFaultDetection_DW.is_BackHallError =
        APPL_PaFaultDetection_IN_Normal_c;
      APPL_PaFaultDetection_B.BackHallFault = 0U;
    }
  }
  else
  {
    /*  无记忆功能 ||不可调节配置  */
    if ((((BOOL)TRUE) != MtrCtrlFault_PaMemoryCfg) || (((BOOL)TRUE) !=
         MtrCtrlFault_PaAdjustCfg))
    {
      if (APPL_PaFaultDetection_DW.is_BackHallError ==
          APPL_PaFaultDetection_IN_Judge_o)
      {
        APPL_PaFaultDetection_DW.BackHallTimer = 0U;
        APPL_PaFaultDetection_DW.is_BackHallError =
          APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      }
      else
      {
        APPL_PaFaultDetection_DW.is_BackHallError =
          APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      }

      if (APPL_PaFaultDetection_DW.is_LengthHallError ==
          APPL_PaFaultDetection_IN_Judge_o)
      {
        APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
        APPL_PaFaultDetection_DW.is_LengthHallError =
          APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      }
      else
      {
        APPL_PaFaultDetection_DW.is_LengthHallError =
          APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      }

      APPL_PaFaultDetection_DW.is_c9_APPL_PaFaultDetection =
        APPL_PaFaultDetection_IN_Init;
      APPL_PaFaultDetection_enter_atomic_Init();
    }
    else
    {
      switch (APPL_PaFaultDetection_DW.is_LengthHallError)
      {
       case APPL_PaFaultDetection_IN_Init:
        /*  满足前置条件  */
        if (((BOOL)TRUE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.is_LengthHallError =
            APPL_PaFaultDetection_IN_Normal_c;
          APPL_PaFaultDetection_B.LengthHallFault = 0U;
        }
        break;

       case APPL_PaFaultDetection_IN_Judge_o:
        /*  不满足前置条件  */
        if (((BOOL)FALSE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
          APPL_PaFaultDetection_DW.is_LengthHallError =
            APPL_PaFaultDetection_IN_Init;
          APPL_PaFaultDetection_B.LengthHallFault = 0U;
          APPL_PaFaultDetection_B.Desc_LengthHallDTC = 0U;
        }
        else
        {
          /* 无调节动作 */
          if (((MtrCtrlFault_DRLengthSwitch_prev !=
                APPL_PaFaultDetection_DW.LengthSwCmd_start_g) ||
               (enSeatMoveCmd_EN_NULL == APPL_PaFaultDetection_B.LengthSwCmd)) &&
              ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaLengthMotorCmd))
          {
            APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
            APPL_PaFaultDetection_DW.is_LengthHallError =
              APPL_PaFaultDetection_IN_Normal_c;
            APPL_PaFaultDetection_B.LengthHallFault = 0U;
          }
          else
          {
            APPL_PaFaultDetection_inner_default_Judge
              (&MtrCtrlFault_LengthHallCnt_prev);
          }
        }
        break;

       default:
        /*  不满足前置条件  */
        if (((BOOL)FALSE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.is_LengthHallError =
            APPL_PaFaultDetection_IN_Init;
          APPL_PaFaultDetection_B.LengthHallFault = 0U;
          APPL_PaFaultDetection_B.Desc_LengthHallDTC = 0U;
        }
        else
        {
          /* 有调节动作 */
          if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaLengthMotorCmd)
          {
            APPL_PaFaultDetection_DW.is_LengthHallError =
              APPL_PaFaultDetection_IN_Judge_o;
            APPL_PaFaultDetection_inner_default_Judge
              (&MtrCtrlFault_LengthHallCnt_prev);
          }
        }
        break;
      }

      switch (APPL_PaFaultDetection_DW.is_BackHallError)
      {
       case APPL_PaFaultDetection_IN_Init:
        /*  满足前置条件  */
        if (((BOOL)TRUE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.is_BackHallError =
            APPL_PaFaultDetection_IN_Normal_c;
          APPL_PaFaultDetection_B.BackHallFault = 0U;
        }
        break;

       case APPL_PaFaultDetection_IN_Judge_o:
        /*  不满足前置条件  */
        if (((BOOL)FALSE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.BackHallTimer = 0U;
          APPL_PaFaultDetection_DW.is_BackHallError =
            APPL_PaFaultDetection_IN_Init;
          APPL_PaFaultDetection_B.BackHallFault = 0U;
          APPL_PaFaultDetection_B.Desc_BackHallDTC = 0U;
        }
        else
        {
          /* 无调节动作 */
          if (((MtrCtrlFault_DRBackSwitch_prev !=
                APPL_PaFaultDetection_DW.BackSwCmd_start_c) ||
               (enSeatMoveCmd_EN_NULL == APPL_PaFaultDetection_B.BackSwCmd)) &&
              ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaBackMotorCmd))
          {
            APPL_PaFaultDetection_DW.BackHallTimer = 0U;
            APPL_PaFaultDetection_DW.is_BackHallError =
              APPL_PaFaultDetection_IN_Normal_c;
            APPL_PaFaultDetection_B.BackHallFault = 0U;
          }
          else
          {
            APPL_PaFaultDetection_inner_default_Judge_b
              (&MtrCtrlFault_BackHallCnt_prev);
          }
        }
        break;

       default:
        /*  不满足前置条件  */
        if (((BOOL)FALSE) == APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_PaFaultDetection_DW.is_BackHallError =
            APPL_PaFaultDetection_IN_Init;
          APPL_PaFaultDetection_B.BackHallFault = 0U;
          APPL_PaFaultDetection_B.Desc_BackHallDTC = 0U;
        }
        else
        {
          /* 有调节动作 */
          if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaBackMotorCmd)
          {
            APPL_PaFaultDetection_DW.is_BackHallError =
              APPL_PaFaultDetection_IN_Judge_o;
            APPL_PaFaultDetection_inner_default_Judge_b
              (&MtrCtrlFault_BackHallCnt_prev);
          }
        }
        break;
      }
    }
  }

  if (APPL_PaFaultDetection_DW.is_active_c3_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c3_APPL_PaFaultDetection = 1U;

    /* [HeightMidRelayFault, HeightMidRelayTimer] = CheckMidRelayFault(MtrCtrlFault_HeightMotorCmd,MtrCtrlFault_HeightUpVolt,MtrCtrlFault_HeightDownVolt); */
    APPL_PaFaultDetection_CheckMidRelayFault(MtrCtrlFault_PaLengthMotorCmd,
      MtrCtrlFault_PaLengthForwardVolt, MtrCtrlFault_PaLengthBackwardVolt,
      &APPL_PaFaultDetection_B.MidRelayFault_f,
      &APPL_PaFaultDetection_B.MidRelayTimer_pv,
      &APPL_PaFaultDetection_DW.CheckMidRelayFault1);
    APPL_PaFaultDetection_B.LengthMidRelayFault =
      APPL_PaFaultDetection_B.MidRelayFault_f;
    APPL_PaFaultDetection_CheckMidRelayFault(MtrCtrlFault_PaBackMotorCmd,
      MtrCtrlFault_PaBackForwardVolt, MtrCtrlFault_PaBackBackwardVolt,
      &APPL_PaFaultDetection_B.MidRelayFault_p,
      &APPL_PaFaultDetection_B.MidRelayTimer_p,
      &APPL_PaFaultDetection_DW.CheckMidRelayFault2);
    APPL_PaFaultDetection_B.BackMidRelayFault =
      APPL_PaFaultDetection_B.MidRelayFault_p;

    /* [FrontMidRelayFault, FrontMidRelayTimer] = CheckMidRelayFault3(MtrCtrlFault_FrontMotorCmd,MtrCtrlFault_FrontUpVolt,MtrCtrlFault_FrontDownVolt); */
  }
  else
  {
    /* [HeightMidRelayFault, HeightMidRelayTimer] = CheckMidRelayFault(MtrCtrlFault_HeightMotorCmd,MtrCtrlFault_HeightUpVolt,MtrCtrlFault_HeightDownVolt); */
    APPL_PaFaultDetection_CheckMidRelayFault(MtrCtrlFault_PaLengthMotorCmd,
      MtrCtrlFault_PaLengthForwardVolt, MtrCtrlFault_PaLengthBackwardVolt,
      &APPL_PaFaultDetection_B.MidRelayFault_f,
      &APPL_PaFaultDetection_B.MidRelayTimer_pv,
      &APPL_PaFaultDetection_DW.CheckMidRelayFault1);
    APPL_PaFaultDetection_B.LengthMidRelayFault =
      APPL_PaFaultDetection_B.MidRelayFault_f;
    APPL_PaFaultDetection_CheckMidRelayFault(MtrCtrlFault_PaBackMotorCmd,
      MtrCtrlFault_PaBackForwardVolt, MtrCtrlFault_PaBackBackwardVolt,
      &APPL_PaFaultDetection_B.MidRelayFault_p,
      &APPL_PaFaultDetection_B.MidRelayTimer_p,
      &APPL_PaFaultDetection_DW.CheckMidRelayFault2);
    APPL_PaFaultDetection_B.BackMidRelayFault =
      APPL_PaFaultDetection_B.MidRelayFault_p;

    /* [FrontMidRelayFault, FrontMidRelayTimer] = CheckMidRelayFault3(MtrCtrlFault_FrontMotorCmd,MtrCtrlFault_FrontUpVolt,MtrCtrlFault_FrontDownVolt); */
  }

  if (APPL_PaFaultDetection_DW.is_active_c33_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c33_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_LengthSoft = APPL_PaFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt >=
        MtrCtrlFault_PaMotorSoftStopCntMax)
    {
      APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)enSeatMoveCmd_EN_NULL;
    }

    APPL_PaFaultDetection_DW.is_BackSoft = APPL_PaFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_PaFaultDetection_DW.BackSoftStopBufCnt >=
        MtrCtrlFault_PaMotorSoftStopCntMax)
    {
      APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)enSeatMoveCmd_EN_NULL;
    }
  }
  else
  {
    APPL_PaFaultDetection_DW.LengthSoftStopBufCnt =
      MtrCtrlFault_PaLengthSoftStopCnt;
    APPL_PaFaultDetection_DW.BackSoftStopBufCnt = MtrCtrlFault_PaBackSoftStopCnt;
    switch (APPL_PaFaultDetection_DW.is_LengthSoft)
    {
     case APPL_PaFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      tmp = enSeatMoveCmd_EN_UP_FORWARD;
      if ((0 != MtrCtrlFault_PaLengthStopPosi) && (0xFFFF !=
           MtrCtrlFault_PaLengthStopPosi) &&
          (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt <
           MtrCtrlFault_PaMotorSoftStopCntMax) && (MtrCtrlFault_PaLengthMotorCmd
           == tmp) && (APPL_PaFaultDetection_B.LengthSoftStopFault != tmp))
      {
        APPL_PaFaultDetection_DW.is_LengthSoft =
          APPL_PaFaultDetection_IN_LeftUpFront;
        APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_PaLengthHallCnt >= (MtrCtrlFault_PaLengthStopPosi +
             MtrCtrlFault_PaLengthMotorSize) - ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_PaFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_PaFaultDetection_B.Cnt_h =
            APPL_PaFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_PaLengthStopPosi) && (0xFFFF !=
             MtrCtrlFault_PaLengthStopPosi) &&
            (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt <
             MtrCtrlFault_PaMotorSoftStopCntMax) &&
            (MtrCtrlFault_PaLengthMotorCmd == (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD) &&
            (APPL_PaFaultDetection_B.LengthSoftStopFault != (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD))
        {
          APPL_PaFaultDetection_DW.is_LengthSoft =
            APPL_PaFaultDetection_IN_RightDnBack;
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最小软止点  */
          if (MtrCtrlFault_PaLengthHallCnt <= MtrCtrlFault_PaLengthStopPosi +
              ((INT8U)D_DrSoftStopDef_L))
          {
            tmp = APPL_PaFaultDetection_DW.LengthSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_PaFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
            APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_DN_BACKWARD;
            APPL_PaFaultDetection_B.Cnt_h =
              APPL_PaFaultDetection_DW.LengthSoftStopBufCnt;
            APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt >=
              MtrCtrlFault_PaMotorSoftStopCntMax)
          {
            APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_PaFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_PaLengthMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_PaFaultDetection_B.LengthSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_PaFaultDetection_DW.is_LengthSoft = APPL_PaFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt >=
            MtrCtrlFault_PaMotorSoftStopCntMax)
        {
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_PaLengthHallCnt >= (MtrCtrlFault_PaLengthStopPosi +
             MtrCtrlFault_PaLengthMotorSize) - ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_PaFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_PaFaultDetection_B.Cnt_h =
            APPL_PaFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_PaLengthMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_PaFaultDetection_B.LengthSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_PaFaultDetection_DW.is_LengthSoft = APPL_PaFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_PaFaultDetection_DW.LengthSoftStopBufCnt >=
            MtrCtrlFault_PaMotorSoftStopCntMax)
        {
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_PaLengthHallCnt <= MtrCtrlFault_PaLengthStopPosi +
            ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_PaFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_PaFaultDetection_B.Cnt_h =
            APPL_PaFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetLengthSoftStopCnt();
        }
      }
      break;
    }

    switch (APPL_PaFaultDetection_DW.is_BackSoft)
    {
     case APPL_PaFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      if ((0 != MtrCtrlFault_PaBackStopPosi) && (0xFFFF !=
           MtrCtrlFault_PaBackStopPosi) &&
          (APPL_PaFaultDetection_DW.BackSoftStopBufCnt <
           MtrCtrlFault_PaMotorSoftStopCntMax) && (MtrCtrlFault_PaBackMotorCmd ==
           (INT32S)enSeatMoveCmd_EN_UP_FORWARD) &&
          (APPL_PaFaultDetection_B.BackSoftStopFault != (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_PaFaultDetection_DW.is_BackSoft =
          APPL_PaFaultDetection_IN_LeftUpFront;
        APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_PaBackHallCnt >= (MtrCtrlFault_PaBackStopPosi +
             MtrCtrlFault_PaBackMotorSize) - ((INT8U)D_DrSoftStopDef_B))
        {
          tmp = APPL_PaFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_PaFaultDetection_B.Cnt_i =
            APPL_PaFaultDetection_DW.BackSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_PaBackStopPosi) && (0xFFFF !=
             MtrCtrlFault_PaBackStopPosi) &&
            (APPL_PaFaultDetection_DW.BackSoftStopBufCnt <
             MtrCtrlFault_PaMotorSoftStopCntMax) && (MtrCtrlFault_PaBackMotorCmd
             == (INT32S)enSeatMoveCmd_EN_DN_BACKWARD) &&
            (APPL_PaFaultDetection_B.BackSoftStopFault != (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD))
        {
          APPL_PaFaultDetection_DW.is_BackSoft =
            APPL_PaFaultDetection_IN_RightDnBack;
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最小软止点  */
          if (MtrCtrlFault_PaBackHallCnt <= MtrCtrlFault_PaBackStopPosi +
              ((INT8U)D_DrSoftStopDef_B))
          {
            tmp = APPL_PaFaultDetection_DW.BackSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_PaFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
            APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_DN_BACKWARD;
            APPL_PaFaultDetection_B.Cnt_i =
              APPL_PaFaultDetection_DW.BackSoftStopBufCnt;
            APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_PaFaultDetection_DW.BackSoftStopBufCnt >=
              MtrCtrlFault_PaMotorSoftStopCntMax)
          {
            APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_PaFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_PaBackMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_PaFaultDetection_B.BackSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_PaFaultDetection_DW.is_BackSoft = APPL_PaFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_PaFaultDetection_DW.BackSoftStopBufCnt >=
            MtrCtrlFault_PaMotorSoftStopCntMax)
        {
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_PaBackHallCnt >= (MtrCtrlFault_PaBackStopPosi +
             MtrCtrlFault_PaBackMotorSize) - ((INT8U)D_DrSoftStopDef_B))
        {
          tmp = APPL_PaFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_PaFaultDetection_B.Cnt_i =
            APPL_PaFaultDetection_DW.BackSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_PaBackMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_PaFaultDetection_B.BackSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_PaFaultDetection_DW.is_BackSoft = APPL_PaFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_PaFaultDetection_DW.BackSoftStopBufCnt >=
            MtrCtrlFault_PaMotorSoftStopCntMax)
        {
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_PaBackHallCnt <= MtrCtrlFault_PaBackStopPosi + ((INT8U)
             D_DrSoftStopDef_B))
        {
          tmp = APPL_PaFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_PaFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_PaFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_PaFaultDetection_B.Cnt_i =
            APPL_PaFaultDetection_DW.BackSoftStopBufCnt;
          APPL_PaFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      break;
    }
  }

  APPL_PaFaultDetection_UpDataOutputInfo();
  if (APPL_PaFaultDetection_DW.is_active_c16_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c16_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_VerticalAdjust = APPL_PaFaultDetection_IN_Init_e;
    APPL_PaFaultDetection_DW.LengthTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.LengthSwCmd)
    {
      APPL_PaFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
    }

    APPL_PaFaultDetection_DW.is_BackAdjust = APPL_PaFaultDetection_IN_Init_e;
    APPL_PaFaultDetection_DW.BackTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.BackSwCmd)
    {
      APPL_PaFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
    }
  }
  else
  {
    if (APPL_PaFaultDetection_DW.is_VerticalAdjust ==
        APPL_PaFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaLengthMotorCmd)
      {
        APPL_PaFaultDetection_DW.is_VerticalAdjust =
          APPL_PaFaultDetection_IN_Init_e;
        APPL_PaFaultDetection_DW.LengthTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.LengthSwCmd)
        {
          APPL_PaFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_PaFaultDetection_DW.LengthTimer < CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_PaFaultDetection_DW.LengthTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_PaFaultDetection_DW.LengthTimer = (INT16U)tmp;
      }
      else
      {
        APPL_PaFaultDetection_B.LengthTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* 高度、纵向电机没有命令或计时已到 */
      if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaLengthMotorCmd)
      {
        APPL_PaFaultDetection_DW.is_VerticalAdjust =
          APPL_PaFaultDetection_IN_Action;
        if (APPL_PaFaultDetection_DW.LengthTimer < CAL_MotorMaxRunTime_60s)
        {
          tmp = APPL_PaFaultDetection_DW.LengthTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          APPL_PaFaultDetection_DW.LengthTimer = (INT16U)tmp;
        }
        else
        {
          APPL_PaFaultDetection_B.LengthTimeOutFlag = ((BOOL)TRUE);
        }
      }
      else
      {
        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.LengthSwCmd)
        {
          APPL_PaFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_PaFaultDetection_DW.is_BackAdjust ==
        APPL_PaFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_PaBackMotorCmd)
      {
        APPL_PaFaultDetection_DW.is_BackAdjust = APPL_PaFaultDetection_IN_Init_e;
        APPL_PaFaultDetection_DW.BackTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.BackSwCmd)
        {
          APPL_PaFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_PaFaultDetection_DW.BackTimer < CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_PaFaultDetection_DW.BackTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_PaFaultDetection_DW.BackTimer = (INT16U)tmp;
      }
      else
      {
        APPL_PaFaultDetection_B.BackTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* 高度、纵向、前部电机没有命令或计时已到 */
      if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_PaBackMotorCmd)
      {
        APPL_PaFaultDetection_DW.is_BackAdjust = APPL_PaFaultDetection_IN_Action;
        if (APPL_PaFaultDetection_DW.BackTimer < CAL_MotorMaxRunTime_60s)
        {
          tmp = APPL_PaFaultDetection_DW.BackTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          APPL_PaFaultDetection_DW.BackTimer = (INT16U)tmp;
        }
        else
        {
          APPL_PaFaultDetection_B.BackTimeOutFlag = ((BOOL)TRUE);
        }
      }
      else
      {
        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_PaFaultDetection_B.BackSwCmd)
        {
          APPL_PaFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
        }
      }
    }
  }

  if (APPL_PaFaultDetection_DW.is_active_c1_APPL_PaFaultDetection == 0U)
  {
    APPL_PaFaultDetection_DW.is_active_c1_APPL_PaFaultDetection = 1U;
    APPL_PaFaultDetection_DW.is_c1_APPL_PaFaultDetection =
      APPL_PaFaultDetection_IN_Init_e;
    APPL_PaFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_PaFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_PaFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_PaFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
  }
  else if (APPL_PaFaultDetection_DW.is_c1_APPL_PaFaultDetection ==
           APPL_PaFaultDetection_IN_DSM_SWAdjust)
  {
    /*  crank档 或 不可调节配置  */
    if ((enIgnSts_eCrank == MtrCtrlFault_PaPowerModeStatus) || (((BOOL)TRUE) !=
         MtrCtrlFault_PaAdjustCfg))
    {
      APPL_PaFaultDetection_DW.is_BackSWProcess =
        APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_PaFaultDetection_DW.is_LengthSWProcess =
        APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_PaFaultDetection_DW.is_c1_APPL_PaFaultDetection =
        APPL_PaFaultDetection_IN_Init_e;
      APPL_PaFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_PaFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_PaFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_PaFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    }
    else
    {
      if (APPL_PaFaultDetection_DW.is_LengthSWProcess ==
          APPL_PaFaultDetection_IN_Disable)
      {
        /*  纵向本地开关命令故障处理  */
        if (((INT32S)APPL_PaFaultDetection_B.LengthSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.LengthSwAdhesionFault) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.LengthMidRelayFault) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.LengthStallFault))
        {
          APPL_PaFaultDetection_DW.is_LengthSWProcess =
            APPL_PaFaultDetection_IN_Enable;
          APPL_PaFaultDetection_B.CurrentLengthSwCmd =
            APPL_PaFaultDetection_B.LengthSwCmd;
        }
      }
      else if (((INT32S)APPL_PaFaultDetection_B.LengthSwCmd == ((BOOL)FALSE)) ||
               (((BOOL)FALSE) != APPL_PaFaultDetection_B.LengthSwAdhesionFault) ||
               (((BOOL)TRUE) == APPL_PaFaultDetection_B.LengthMidRelayFault) ||
               (((BOOL)TRUE) == APPL_PaFaultDetection_B.LengthStallFault))
      {
        APPL_PaFaultDetection_DW.is_LengthSWProcess =
          APPL_PaFaultDetection_IN_Disable;
        APPL_PaFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
          APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      }
      else
      {
        APPL_PaFaultDetection_B.CurrentLengthSwCmd =
          APPL_PaFaultDetection_B.LengthSwCmd;
      }

      if (APPL_PaFaultDetection_DW.is_BackSWProcess ==
          APPL_PaFaultDetection_IN_Disable)
      {
        /*  靠背本地开关命令故障处理  */
        if (((INT32S)APPL_PaFaultDetection_B.BackSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.BackMidRelayFault) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.BackSwAdhesionFault) &&
            (((BOOL)FALSE) == APPL_PaFaultDetection_B.BackStallFault))
        {
          APPL_PaFaultDetection_DW.is_BackSWProcess =
            APPL_PaFaultDetection_IN_Enable;
          APPL_PaFaultDetection_B.CurrentBackSwCmd =
            APPL_PaFaultDetection_B.BackSwCmd;
        }
      }
      else if (((INT32S)APPL_PaFaultDetection_B.BackSwCmd == ((BOOL)FALSE)) ||
               (((BOOL)FALSE) != APPL_PaFaultDetection_B.BackMidRelayFault) ||
               (((BOOL)TRUE) == APPL_PaFaultDetection_B.BackSwAdhesionFault) ||
               (((BOOL)TRUE) == APPL_PaFaultDetection_B.BackStallFault))
      {
        APPL_PaFaultDetection_DW.is_BackSWProcess =
          APPL_PaFaultDetection_IN_Disable;
        APPL_PaFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
          APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      }
      else
      {
        APPL_PaFaultDetection_B.CurrentBackSwCmd =
          APPL_PaFaultDetection_B.BackSwCmd;
      }
    }
  }
  else
  {
    APPL_PaFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_PaFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
      APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));

    /*  非CRANK档位 且非不可调节配置  */
    if ((enIgnSts_eCrank != MtrCtrlFault_PaPowerModeStatus) && (((BOOL)TRUE) ==
         MtrCtrlFault_PaAdjustCfg))
    {
      APPL_PaFaultDetection_DW.is_c1_APPL_PaFaultDetection =
        APPL_PaFaultDetection_IN_DSM_SWAdjust;
      APPL_PaFaultDetection_DW.is_LengthSWProcess =
        APPL_PaFaultDetection_IN_Disable;
      APPL_PaFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_PaFaultDetection_DW.is_BackSWProcess =
        APPL_PaFaultDetection_IN_Disable;
      APPL_PaFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
        APPL_PaFaultDetection_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    }
  }
}

/* Model initialize function */
void APPL_PaFaultDetection_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(APPL_PaFaultDetection_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &APPL_PaFaultDetection_B), 0,
                sizeof(B_APPL_PaFaultDetection_T));

  {
    APPL_PaFaultDetection_B.CurrentHeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentLengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentBackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentFrontSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
  }

  /* exported global signals */
  MtrCtrlFault_PaBackSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_PaFrontSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_PaHeightSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_PaLengthSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_PaPowerModeStatus = enIgnSts_eOff;
  MtrCtrlFault_PaBackHallCnt = ((INT16U)0U);
  MtrCtrlFault_PaBackMotorSize = ((INT16U)0U);
  MtrCtrlFault_PaBackStopPosi = ((INT16U)0U);
  MtrCtrlFault_PaFrontHallCnt = ((INT16U)0U);
  MtrCtrlFault_PaFrontMotorSize = ((INT16U)0U);
  MtrCtrlFault_PaFrontStopPosi = ((INT16U)0U);
  MtrCtrlFault_PaHeightHallCnt = ((INT16U)0U);
  MtrCtrlFault_PaHeightMotorSize = ((INT16U)0U);
  MtrCtrlFault_PaHeightStopPosi = ((INT16U)0U);
  MtrCtrlFault_PaLengthHallCnt = ((INT16U)0U);
  MtrCtrlFault_PaLengthMotorSize = ((INT16U)0U);
  MtrCtrlFault_PaLengthStopPosi = ((INT16U)0U);
  MtrCtrlFault_PaAdjustCfg = ((INT8U)1U);
  MtrCtrlFault_PaBackBackwardVolt = ((INT8U)0U);
  MtrCtrlFault_PaBackCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_PaBackForwardVolt = ((INT8U)0U);
  MtrCtrlFault_PaBackLearnFlag = ((INT8U)0U);
  MtrCtrlFault_PaBackMotorCmd = ((INT8U)0U);
  MtrCtrlFault_PaBackSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_PaFrontCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_PaFrontDownVolt = ((INT8U)0U);
  MtrCtrlFault_PaFrontLearnFlag = ((INT8U)0U);
  MtrCtrlFault_PaFrontMotorCmd = ((INT8U)0U);
  MtrCtrlFault_PaFrontSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_PaFrontUpVolt = ((INT8U)0U);
  MtrCtrlFault_PaHeightCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_PaHeightDownVolt = ((INT8U)0U);
  MtrCtrlFault_PaHeightLearnFlag = ((INT8U)0U);
  MtrCtrlFault_PaHeightMotorCmd = ((INT8U)0U);
  MtrCtrlFault_PaHeightSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_PaHeightUpVolt = ((INT8U)0U);
  MtrCtrlFault_PaLengthBackwardVolt = ((INT8U)0U);
  MtrCtrlFault_PaLengthCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_PaLengthForwardVolt = ((INT8U)0U);
  MtrCtrlFault_PaLengthLearnFlag = ((INT8U)0U);
  MtrCtrlFault_PaLengthMotorCmd = ((INT8U)0U);
  MtrCtrlFault_PaLengthSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_PaMemoryCfg = ((INT8U)0U);
  MtrCtrlFault_PaMotorSoftStopCntMax = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&APPL_PaFaultDetection_DW, 0,
                sizeof(DW_APPL_PaFaultDetection_T));

  {
    INT32U OutTs_e;
    INT8U MidRelayFault_n;
    INT8U MidRelayTimer_e;
    APPL_PaFaultDetection_DW.is_BackSwitchErrorDeal =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_LengthSwitchErrorDeal =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c8_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.LengthSwTimer = 0U;
    APPL_PaFaultDetection_DW.BackSwTimer = 0U;
    APPL_PaFaultDetection_B.HeightSwAdhesionFault = 0U;
    APPL_PaFaultDetection_B.LengthSwAdhesionFault = 0U;
    APPL_PaFaultDetection_B.BackSwAdhesionFault = 0U;
    APPL_PaFaultDetection_B.FrontSwAdhesionFault = 0U;
    APPL_PaFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.LengthSwUpAdhesionFault = 0U;
    APPL_PaFaultDetection_B.LengthSwDownAdhesionFault = 0U;
    APPL_PaFaultDetection_B.BackSwUpAdhesionFault = 0U;
    APPL_PaFaultDetection_B.BackSwDownAdhesionFault = 0U;
    APPL_PaFaultDetection_TimeDiffTs_Init(&OutTs_e);
    APPL_PaFaultDetection_GetDefTime_Init(&OutTs_e);
    APPL_PaFaultDetection_DW.is_BackStallError =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_LengthStallError =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c10_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.LengthStallTimer = 0U;
    APPL_PaFaultDetection_DW.BackStallTimer = 0U;
    APPL_PaFaultDetection_DW.LengthStallNoTimer = 0U;
    APPL_PaFaultDetection_DW.BackStallNoTimer = 0U;
    APPL_PaFaultDetection_DW.LocalLengthHallCnt = 0U;
    APPL_PaFaultDetection_DW.LocalBackHallCnt = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer2 = 0U;
    APPL_PaFaultDetection_DW.CurrentOverTimer3 = 0U;
    APPL_PaFaultDetection_B.HeightStallFault = 0U;
    APPL_PaFaultDetection_B.LengthStallFault = 0U;
    APPL_PaFaultDetection_B.BackStallFault = 0U;
    APPL_PaFaultDetection_B.FrontStallFault = 0U;
    APPL_PaFaultDetection_DW.is_BackHallError =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_LengthHallError =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c9_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.is_c9_APPL_PaFaultDetection =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.LengthHallTimer = 0U;
    APPL_PaFaultDetection_DW.BackHallTimer = 0U;
    APPL_PaFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC = true;
    APPL_PaFaultDetection_B.Desc_HeightHallDTC = 0U;
    APPL_PaFaultDetection_B.Desc_LengthHallDTC = 0U;
    APPL_PaFaultDetection_B.Desc_BackHallDTC = 0U;
    APPL_PaFaultDetection_B.Desc_FrontHallDTC = 0U;
    APPL_PaFaultDetection_B.HeightHallFault = 0U;
    APPL_PaFaultDetection_B.LengthHallFault = 0U;
    APPL_PaFaultDetection_B.BackHallFault = 0U;
    APPL_PaFaultDetection_B.FrontHallFault = 0U;
    APPL_PaFaultDetection_DW.is_active_c3_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_B.HeightMidRelayFault = 0U;
    APPL_PaFaultDetection_B.LengthMidRelayFault = 0U;
    APPL_PaFaultDetection_B.BackMidRelayFault = 0U;
    APPL_PaFaultDetection_B.FrontMidRelayFault = 0U;
    APPL_PaFaultDetection_CheckMidRelayFault_Init(&MidRelayFault_n,
      &MidRelayTimer_e, &APPL_PaFaultDetection_DW.CheckMidRelayFault);
    APPL_PaFaultDetection_CheckMidRelayFault_Init
      (&APPL_PaFaultDetection_B.MidRelayFault_f,
       &APPL_PaFaultDetection_B.MidRelayTimer_pv,
       &APPL_PaFaultDetection_DW.CheckMidRelayFault1);
    APPL_PaFaultDetection_CheckMidRelayFault_Init
      (&APPL_PaFaultDetection_B.MidRelayFault_p,
       &APPL_PaFaultDetection_B.MidRelayTimer_p,
       &APPL_PaFaultDetection_DW.CheckMidRelayFault2);
    APPL_PaFaultDetection_CheckMidRelayFault_Init(&MidRelayFault_n,
      &MidRelayTimer_e, &APPL_PaFaultDetection_DW.CheckMidRelayFault3);
    APPL_PaFaultDetection_DW.is_BackSoft =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_LengthSoft =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c33_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.LengthSoftStopBufCnt = 0U;
    APPL_PaFaultDetection_DW.BackSoftStopBufCnt = 0U;
    APPL_PaFaultDetection_B.HeightSoftStopFault = 0U;
    APPL_PaFaultDetection_B.LengthSoftStopFault = 0U;
    APPL_PaFaultDetection_B.BackSoftStopFault = 0U;
    APPL_PaFaultDetection_B.FrontSoftStopFault = 0U;
    APPL_PaFaultDetection_DW.is_BackAdjust =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_VerticalAdjust =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c16_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.BackTimer = 0U;
    APPL_PaFaultDetection_DW.LengthTimer = 0U;
    APPL_PaFaultDetection_B.HeightTimeOutFlag = 0U;
    APPL_PaFaultDetection_B.LengthTimeOutFlag = 0U;
    APPL_PaFaultDetection_B.BackTimeOutFlag = 0U;
    APPL_PaFaultDetection_B.FrontTimeOutFlag = 0U;
    APPL_PaFaultDetection_DW.is_BackSWProcess =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_LengthSWProcess =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_DW.is_active_c1_APPL_PaFaultDetection = 0U;
    APPL_PaFaultDetection_DW.is_c1_APPL_PaFaultDetection =
      APPL_PaFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_PaFaultDetection_B.CurrentHeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentLengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentBackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_PaFaultDetection_B.CurrentFrontSwCmd = enSeatMoveCmd_EN_NULL;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
