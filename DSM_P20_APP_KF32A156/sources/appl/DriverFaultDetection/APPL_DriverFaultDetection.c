/*
 * File: APPL_DriverFaultDetection.c
 *
 * Code generated for Simulink model 'APPL_DriverFaultDetection'.
 *
 * Model version                  : 1.338
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sun Jul  4 09:36:20 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "APPL_DriverFaultDetection.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
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
#define APPL_DriverFaultDetection_IN_Judge ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_h ((INT8U)0U)
#define APPL_DriverFaultDetection_IN_Normal ((INT8U)2U)

/* Named constants for Chart: '<S5>/SwitchErrorDetection' */
#define APPL_DriverFaultDetection_IN_Invalid ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l ((INT8U)0U)
#define APPL_DriverFaultDetection_IN_Valid ((INT8U)2U)

/* Named constants for Chart: '<S6>/HallErrorDetection' */
#define APPL_DriverFaultDetection_IN_Init ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_Judge_o ((INT8U)2U)
#define APPL_DriverFaultDetection_IN_MotorHallDetect ((INT8U)2U)
#define APPL_DriverFaultDetection_IN_Normal_c ((INT8U)3U)

/* Named constants for Chart: '<S7>/MotorTimeOutDetection' */
#define APPL_DriverFaultDetection_IN_Action ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_Init_e ((INT8U)2U)

/* Named constants for Chart: '<S9>/SoftStopPointDetection' */
#define APPL_DriverFaultDetection_IN_LeftUpFront ((INT8U)2U)
#define APPL_DriverFaultDetection_IN_RightDnBack ((INT8U)3U)

/* Named constants for Chart: '<S10>/StallErrorDetection' */
#define APPL_DriverFaultDetection_IN_Judge_e ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_Normal_o ((INT8U)2U)

/* Named constants for Chart: '<S11>/ SWProcess ' */
#define APPL_DriverFaultDetection_IN_DSM_SWAdjust ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_Disable ((INT8U)1U)
#define APPL_DriverFaultDetection_IN_Enable ((INT8U)2U)

/* Exported block signals */
enSeatMoveCmd MtrCtrlFault_DrBackSwitch;/* '<S38>/MtrCtrlFault_DrBackSwitch'
                                         * 硬线调节开关输入方向-主驾靠背
                                         */
enSeatMoveCmd MtrCtrlFault_DrFrontSwitch;/* '<S38>/MtrCtrlFault_DrFrontSwitch'
                                          * 硬线调节开关输入方向-主驾腿托
                                          */
enSeatMoveCmd MtrCtrlFault_DrHeightSwitch;/* '<S38>/MtrCtrlFault_DrHeightSwitch'
                                           * 硬线调节开关输入方向-主驾高度
                                           */
enSeatMoveCmd MtrCtrlFault_DrLengthSwitch;/* '<S38>/MtrCtrlFault_DrLengthSwitch'
                                           * 硬线调节开关输入方向-主驾纵向
                                           */
enIgnSts MtrCtrlFault_DrPowerModeStatus;/* '<S38>/MtrCtrlFault_DrPowerModeStatus'
                                         * 整车电源档位
                                         */
enDrAdjustEnable MtrCtrlFault_DrAdjustCfg;/* '<S38>/MtrCtrlFault_DrAdjustCfg'
                                           * 主驾座椅调节配置  0x00:手动调节  0x01:六向电机  0x02:十二向电机
                                           */
INT16U MtrCtrlFault_DrBackHallCnt;     /* '<S38>/MtrCtrlFault_DrBackHallCnt'
                                        * 当前霍尔-主驾靠背
                                        */
INT16U MtrCtrlFault_DrBackMotorSize;   /* '<S38>/MtrCtrlFault_DrBackMotorSize'
                                        * 导轨长度-主驾靠背
                                        */
INT16U MtrCtrlFault_DrBackStopPosi;    /* '<S38>/MtrCtrlFault_DrBackStopPosi'
                                        * 硬止点位置-主驾靠背
                                        */
INT16U MtrCtrlFault_DrFrontHallCnt;    /* '<S38>/MtrCtrlFault_DrFrontHallCnt'
                                        * 当前霍尔-主驾腿托
                                        */
INT16U MtrCtrlFault_DrFrontMotorSize;  /* '<S38>/MtrCtrlFault_DrFrontMotorSize'
                                        * 导轨长度-主驾腿托
                                        */
INT16U MtrCtrlFault_DrFrontStopPosi;   /* '<S38>/MtrCtrlFault_DrFrontStopPosi'
                                        * 硬止点位置-主驾腿托
                                        */
INT16U MtrCtrlFault_DrHeightHallCnt;   /* '<S38>/MtrCtrlFault_DrHeightHallCnt'
                                        * 当前霍尔-主驾高度
                                        */
INT16U MtrCtrlFault_DrHeightMotorSize; /* '<S38>/MtrCtrlFault_DrHeightMotorSize'
                                        * 导轨长度-主驾高度
                                        */
INT16U MtrCtrlFault_DrHeightStopPosi;  /* '<S38>/MtrCtrlFault_DrHeightStopPosi'
                                        * 硬止点位置-主驾高度
                                        */
INT16U MtrCtrlFault_DrLengthHallCnt;   /* '<S38>/MtrCtrlFault_DrLengthHallCnt'
                                        * 当前霍尔-主驾纵向
                                        */
INT16U MtrCtrlFault_DrLengthMotorSize; /* '<S38>/MtrCtrlFault_DrLengthMotorSize'
                                        * 导轨长度-主驾纵向
                                        */
INT16U MtrCtrlFault_DrLengthStopPosi;  /* '<S38>/MtrCtrlFault_DrLengthStopPosi'
                                        * 硬止点位置-主驾纵向
                                        */
INT8U MtrCtrlFault_DrBackBackwardVolt; /* '<S38>/MtrCtrlFault_DrBackBackwardVolt'
                                        * 主驾靠背向后
                                        */
INT8U MtrCtrlFault_DrBackCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrBackCurrentOverFlag'
                                          * 反馈电流超过堵转阈值标志-主驾靠背
                                          */
INT8U MtrCtrlFault_DrBackForwardVolt;  /* '<S38>/MtrCtrlFault_DrBackForwardVolt'
                                        * 主驾靠背向前
                                        */
INT8U MtrCtrlFault_DrBackLearnFlag;    /* '<S38>/MtrCtrlFault_DrBackLearnFlag'
                                        * 电机学习标志-主驾靠背
                                        */
INT8U MtrCtrlFault_DrBackMotorCmd;     /* '<S38>/MtrCtrlFault_DrBackMotorCmd'
                                        * 模型输出到电机的CMD-主驾靠背
                                        */
INT8U MtrCtrlFault_DrBackSoftStopCnt;  /* '<S38>/MtrCtrlFault_DrBackSoftStopCnt'
                                        * 到达软止点次数(E2)-主驾靠背
                                        */
INT8U MtrCtrlFault_DrFrontCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrFrontCurrentOverFlag'
                                           * 反馈电流超过堵转阈值标志-主驾腿托
                                           */
INT8U MtrCtrlFault_DrFrontDownVolt;    /* '<S38>/MtrCtrlFault_DrFrontDownVolt'
                                        * 主驾腿托向下
                                        */
INT8U MtrCtrlFault_DrFrontLearnFlag;   /* '<S38>/MtrCtrlFault_DrFrontLearnFlag'
                                        * 电机学习标志-主驾腿托
                                        */
INT8U MtrCtrlFault_DrFrontMotorCmd;    /* '<S38>/MtrCtrlFault_DrFrontMotorCmd'
                                        * 模型输出到电机的CMD-主驾腿托
                                        */
INT8U MtrCtrlFault_DrFrontSoftStopCnt; /* '<S38>/MtrCtrlFault_DrFrontSoftStopCnt'
                                        * 到达软止点次数(E2)-主驾腿托
                                        */
INT8U MtrCtrlFault_DrFrontUpVolt;      /* '<S38>/MtrCtrlFault_DrFrontUpVolt'
                                        * 主驾腿托向上
                                        */
INT8U MtrCtrlFault_DrHeightCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrHeightCurrentOverFlag'
                                            * 反馈电流超过堵转阈值标志-主驾高度
                                            */
INT8U MtrCtrlFault_DrHeightDownVolt;   /* '<S38>/MtrCtrlFault_DrHeightDownVolt'
                                        * 主驾高度向下
                                        */
INT8U MtrCtrlFault_DrHeightLearnFlag;  /* '<S38>/MtrCtrlFault_DrHeightLearnFlag'
                                        * 电机学习标志-主驾高度
                                        */
INT8U MtrCtrlFault_DrHeightMotorCmd;   /* '<S38>/MtrCtrlFault_DrHeightMotorCmd'
                                        * 模型输出到电机的CMD-主驾高度
                                        */
INT8U MtrCtrlFault_DrHeightSoftStopCnt;/* '<S38>/MtrCtrlFault_DrHeightSoftStopCnt'
                                        * 到达软止点次数(E2)-主驾高度
                                        */
INT8U MtrCtrlFault_DrHeightUpVolt;     /* '<S38>/MtrCtrlFault_DrHeightUpVolt'
                                        * 主驾高度向上
                                        */
INT8U MtrCtrlFault_DrLengthBackwardVolt;/* '<S38>/MtrCtrlFault_DrLengthBackwardVolt'
                                         * 主驾纵向向后
                                         */
INT8U MtrCtrlFault_DrLengthCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrLengthCurrentOverFlag'
                                            * 反馈电流超过堵转阈值标志-主驾纵向
                                            */
INT8U MtrCtrlFault_DrLengthForwardVolt;/* '<S38>/MtrCtrlFault_DrLengthForwardVolt'
                                        * 主驾纵向向前
                                        */
INT8U MtrCtrlFault_DrLengthLearnFlag;  /* '<S38>/MtrCtrlFault_DrLengthLearnFlag'
                                        * 电机学习标志-主驾纵向
                                        */
INT8U MtrCtrlFault_DrLengthMotorCmd;   /* '<S38>/MtrCtrlFault_DrLengthMotorCmd'
                                        * 模型输出到电机的CMD-主驾纵向
                                        */
INT8U MtrCtrlFault_DrLengthSoftStopCnt;/* '<S38>/MtrCtrlFault_DrLengthSoftStopCnt'
                                        * 到达软止点次数(E2)-主驾纵向
                                        */
INT8U MtrCtrlFault_DrMemoryCfg;        /* '<S38>/MtrCtrlFault_DrMemoryCfg'
                                        *  主驾记忆迎宾配置  0:不存在  2：存在
                                        */
INT8U MtrCtrlFault_DrMotorSoftStopCntMax;/* '<S38>/MtrCtrlFault_DrMotorSoftStopCntMax'
                                          * 软止点最大调节次数（E2）
                                          */

/* Block signals (default storage) */
B_APPL_DriverFaultDetection_T APPL_DriverFaultDetection_B;

/* Block states (default storage) */
DW_APPL_DriverFaultDetection_T APPL_DriverFaultDetection_DW;

/* Real-time model */
RT_MODEL_APPL_DriverFaultDetection_T APPL_DriverFaultDetection_M_;
RT_MODEL_APPL_DriverFaultDetection_T *const APPL_DriverFaultDetection_M =
  &APPL_DriverFaultDetection_M_;
static void APPL_DriverFaultDetection_TimeDiffTs_Init(INT32U *rty_OutTs);
static void APPL_DriverFaultDetection_TimeDiffTs(INT32U rtu_lastTs, INT32U
  rtu_Ts, INT32U *rty_OutTs);
static void APPL_DriverFaultDetection_GetDefTime_Init(INT32U *rty_OutTs);
static void APPL_DriverFaultDetection_GetDefTime(INT32U rtu_DefTs, INT32U rtu_Ts,
  INT32U *rty_OutTs);
static void APPL_DriverFaultDetection_CheckMidRelayFault_Init(INT8U
  *rty_MidRelayFault, INT8U *rty_MidRelayTimer,
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T *localDW);
static void APPL_DriverFaultDetection_CheckMidRelayFault(INT8U rtu_MotorCmd,
  INT8U rtu_UpForwardVolt, INT8U rtu_DownBackwardVolt, INT8U *rty_MidRelayFault,
  INT8U *rty_MidRelayTimer, DW_CheckMidRelayFault_APPL_DriverFaultDetection_T
  *localDW);
static void APPL_DriverFaultDetection_GetCurMsTs(void);
static void APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt(void);
static void APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt(void);
static void APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt(void);
static void APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt(void);
static void APPL_DriverFaultDetection_RTE_InputSignal(void);
static void APPL_DriverFaultDetection_UpDataInputInfo(void);
static void APPL_DriverFaultDetection_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void APPL_DriverFaultDetection_inner_default_Judge_a(void);
static void APPL_DriverFaultDetection_inner_default_Judge_aa(void);
static void APPL_DriverFaultDetection_inner_default_Judge_aae(void);
static void APPL_DriverFaultDetection_inner_default_Judge_aaed(void);
static void APPL_DriverFaultDetection_inner_default_Judge(const INT16U
  *MtrCtrlFault_HeightHallCnt_prev);
static void APPL_DriverFaultDetection_inner_default_Judge_b(const INT16U
  *MtrCtrlFault_LengthHallCnt_prev);
static void APPL_DriverFaultDetection_inner_default_Judge_bv(INT16U
  *MtrCtrlFault_BackHallCnt_prev);
static void APPL_DriverFaultDetection_inner_default_Judge_bvr(void);
static void APPL_DriverFaultDetection_enter_atomic_Init(void);
static void APPL_DriverFaultDetection_MotorHallDetect(const INT16U
  *MtrCtrlFault_HeightHallCnt_prev, const enSeatMoveCmd *HeightSwCmd_prev_f,
  const INT16U *MtrCtrlFault_LengthHallCnt_prev, enSeatMoveCmd
  *LengthSwCmd_prev_c, INT16U *MtrCtrlFault_BackHallCnt_prev, enSeatMoveCmd
  *BackSwCmd_prev_n);
static void APPL_DriverFaultDetect_inner_default_MidRelayError(void);
static INT32S APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd(INT32S input);

/* Output and update for function-call system: '<S12>/GetCurMsTs' */
static void APPL_DriverFaultDetection_GetCurMsTs(void)
{
  APPL_DriverFaultDetection_B.DrAdj_CurMsTs = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S12>/TimeDiffTs' */
static void APPL_DriverFaultDetection_TimeDiffTs_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/* Output and update for function-call system: '<S12>/TimeDiffTs' */
static void APPL_DriverFaultDetection_TimeDiffTs(INT32U rtu_lastTs, INT32U
  rtu_Ts, INT32U *rty_OutTs)
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
static void APPL_DriverFaultDetection_GetDefTime_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/* Output and update for function-call system: '<S12>/GetDefTime' */
static void APPL_DriverFaultDetection_GetDefTime(INT32U rtu_DefTs, INT32U rtu_Ts,
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
static void APPL_DriverFaultDetection_CheckMidRelayFault_Init(INT8U
  *rty_MidRelayFault, INT8U *rty_MidRelayTimer,
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T *localDW)
{
  localDW->is_active_c4_APPL_DriverFaultDetection = 0U;
  localDW->is_c4_APPL_DriverFaultDetection =
    APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_h;
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
static void APPL_DriverFaultDetection_CheckMidRelayFault(INT8U rtu_MotorCmd,
  INT8U rtu_UpForwardVolt, INT8U rtu_DownBackwardVolt, INT8U *rty_MidRelayFault,
  INT8U *rty_MidRelayTimer, DW_CheckMidRelayFault_APPL_DriverFaultDetection_T
  *localDW)
{
  INT16U tmp;
  INT32S tmp_0;
  INT32S tmp_1;
  if (localDW->is_active_c4_APPL_DriverFaultDetection == 0U)
  {
    localDW->is_active_c4_APPL_DriverFaultDetection = 1U;
    localDW->is_c4_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_Normal;
    *rty_MidRelayFault = ((BOOL)FALSE);
    *rty_MidRelayTimer = 0U;
  }
  else if (localDW->is_c4_APPL_DriverFaultDetection ==
           APPL_DriverFaultDetection_IN_Judge)
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
      localDW->is_c4_APPL_DriverFaultDetection =
        APPL_DriverFaultDetection_IN_Normal;
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
      localDW->is_c4_APPL_DriverFaultDetection =
        APPL_DriverFaultDetection_IN_Judge;
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

/* Output and update for function-call system: '<S30>/DrAdj_SetHeightSoftStopCnt' */
static void APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_DrHeightSoftStopCnt,
    APPL_DriverFaultDetection_B.Cnt);
}

/* Output and update for function-call system: '<S30>/DrAdj_SetLengthSoftStopCnt' */
static void APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_DrLengthSoftStopCnt,
    APPL_DriverFaultDetection_B.Cnt_h);
}

/* Output and update for function-call system: '<S30>/DrAdj_SetBackSoftStopCnt' */
static void APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_DrBackSoftStopCnt,
    APPL_DriverFaultDetection_B.Cnt_i);
}

/* Output and update for function-call system: '<S30>/DrAdj_SetFrontSoftStopCnt' */
static void APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt(void)
{
  Srvl_SetMemIndexDataU8(EN_MemIndex_DrFrontSoftStopCnt,
    APPL_DriverFaultDetection_B.Cnt_f);
}

/*
 * Output and update for atomic system: '<S3>/RTE_InputSignal'
 * Block description for: '<S3>/RTE_InputSignal'
 *   接口自动生成
 */
static void APPL_DriverFaultDetection_RTE_InputSignal(void)
{
  MtrCtrlFault_DrAdjustCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
  MtrCtrlFault_DrBackBackwardVolt = Ecual_GetDrRelayFlagBackBackward( );
  MtrCtrlFault_DrBackCurrentOverFlag = Ecual_GetDrBackOverCurrentFlag( );
  MtrCtrlFault_DrBackForwardVolt = Ecual_GetDrRelayFlagBackForward( );
  MtrCtrlFault_DrBackHallCnt = Cdd_GetCurrentHallCnt(EN_DriverBack);
  MtrCtrlFault_DrBackLearnFlag = Cdd_GetMotorLearnFlag(EN_DriverBack);
  MtrCtrlFault_DrBackMotorCmd = Rte_GetVfb_DrBackMotorCmd( );
  MtrCtrlFault_DrBackMotorSize = Cdd_GetMotorSize(EN_DriverBack);
  MtrCtrlFault_DrBackSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrBackSoftStopCnt);
  MtrCtrlFault_DrBackStopPosi = Cdd_GetMotorHardStop(EN_DriverBack);
  MtrCtrlFault_DrBackSwitch = Ecual_GetDrBackSwitchCmd( );
  MtrCtrlFault_DrFrontCurrentOverFlag = Ecual_GetDrFrontOverCurrentFlag( );
  MtrCtrlFault_DrFrontDownVolt = Ecual_GetDrRelayFlagFrontDown( );
  MtrCtrlFault_DrFrontHallCnt = Cdd_GetCurrentHallCnt(EN_DriverFront);
  MtrCtrlFault_DrFrontLearnFlag = Cdd_GetMotorLearnFlag(EN_DriverFront);
  MtrCtrlFault_DrFrontMotorCmd = Rte_GetVfb_DrFrontMotorCmd( );
  MtrCtrlFault_DrFrontMotorSize = Cdd_GetMotorSize(EN_DriverFront);
  MtrCtrlFault_DrFrontSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrFrontSoftStopCnt);
  MtrCtrlFault_DrFrontStopPosi = Cdd_GetMotorHardStop(EN_DriverFront);
  MtrCtrlFault_DrFrontSwitch = Ecual_GetDrFrontSwitchCmd( );
  MtrCtrlFault_DrFrontUpVolt = Ecual_GetDrRelayFlagFrontUp( );
  MtrCtrlFault_DrHeightCurrentOverFlag = Ecual_GetDrHeightOverCurrentFlag( );
  MtrCtrlFault_DrHeightDownVolt = Ecual_GetDrRelayFlagHeightDN( );
  MtrCtrlFault_DrHeightHallCnt = Cdd_GetCurrentHallCnt(EN_DriverHeight);
  MtrCtrlFault_DrHeightLearnFlag = Cdd_GetMotorLearnFlag(EN_DriverHeight);
  MtrCtrlFault_DrHeightMotorCmd = Rte_GetVfb_DrHeightMotorCmd( );
  MtrCtrlFault_DrHeightMotorSize = Cdd_GetMotorSize(EN_DriverHeight);
  MtrCtrlFault_DrHeightSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrHeightSoftStopCnt);
  MtrCtrlFault_DrHeightStopPosi = Cdd_GetMotorHardStop(EN_DriverHeight);
  MtrCtrlFault_DrHeightSwitch = Ecual_GetDrHeightSwitchCmd( );
  MtrCtrlFault_DrHeightUpVolt = Ecual_GetDrRelayFlagHeightUp( );
  MtrCtrlFault_DrLengthBackwardVolt = Ecual_GetDrRelayFlagLenghtBackward( );
  MtrCtrlFault_DrLengthCurrentOverFlag = Ecual_GetDrLengthOverCurrentFlag( );
  MtrCtrlFault_DrLengthForwardVolt = Ecual_GetDrRelayFlagLenghtForward( );
  MtrCtrlFault_DrLengthHallCnt = Cdd_GetCurrentHallCnt(EN_DriverLength);
  MtrCtrlFault_DrLengthLearnFlag = Cdd_GetMotorLearnFlag(EN_DriverLength);
  MtrCtrlFault_DrLengthMotorCmd = Rte_GetVfb_DrLengthMotorCmd( );
  MtrCtrlFault_DrLengthMotorSize = Cdd_GetMotorSize(EN_DriverLength);
  MtrCtrlFault_DrLengthSoftStopCnt = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrLengthSoftStopCnt);
  MtrCtrlFault_DrLengthStopPosi = Cdd_GetMotorHardStop(EN_DriverLength);
  MtrCtrlFault_DrLengthSwitch = Ecual_GetDrLengthSwitchCmd( );
  MtrCtrlFault_DrMemoryCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
  MtrCtrlFault_DrMotorSoftStopCntMax = Srvl_GetMemIndexDataU8
    (EN_MemIndex_MotorSoftStopCntMax);
  MtrCtrlFault_DrPowerModeStatus = Rte_GetVfb_PowerMode( );
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void APPL_DriverFaultDetection_UpDataInputInfo(void)
{
  APPL_DriverFaultDetection_RTE_InputSignal();
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void APPL_DriverFaultDetection_UpDataOutputInfo(void)
{
  APPL_DriverFaultDetection_B.DataTypeConversion1 = (INT8U)
    ((APPL_DriverFaultDetection_B.HeightStallFault != 0) ||
     (APPL_DriverFaultDetection_B.LengthStallFault != 0) ||
     (APPL_DriverFaultDetection_B.BackStallFault != 0) ||
     (APPL_DriverFaultDetection_B.FrontStallFault != 0));
  APPL_DriverFaultDetection_B.DataTypeConversion2 = (INT8U)
    ((APPL_DriverFaultDetection_B.HeightMidRelayFault != 0) ||
     (APPL_DriverFaultDetection_B.LengthMidRelayFault != 0) ||
     (APPL_DriverFaultDetection_B.BackMidRelayFault != 0) ||
     (APPL_DriverFaultDetection_B.FrontMidRelayFault != 0));
  APPL_DriverFaultDetection_B.DataTypeConversion3 = (INT8U)
    ((APPL_DriverFaultDetection_B.HeightSoftStopFault != 0) ||
     (APPL_DriverFaultDetection_B.LengthSoftStopFault != 0) ||
     (APPL_DriverFaultDetection_B.BackSoftStopFault != 0) ||
     (APPL_DriverFaultDetection_B.FrontSoftStopFault != 0));
  APPL_DriverFaultDetection_B.DataTypeConversion4 = (INT8U)
    ((APPL_DriverFaultDetection_B.HeightSwAdhesionFault != 0) ||
     (APPL_DriverFaultDetection_B.LengthSwAdhesionFault != 0) ||
     (APPL_DriverFaultDetection_B.BackSwAdhesionFault != 0) ||
     (APPL_DriverFaultDetection_B.FrontSwAdhesionFault != 0));
  APPL_DriverFaultDetection_B.DataTypeConversion5 = (INT8U)
    ((APPL_DriverFaultDetection_B.Desc_HeightHallDTC != 0) ||
     (APPL_DriverFaultDetection_B.Desc_LengthHallDTC != 0) ||
     (APPL_DriverFaultDetection_B.Desc_BackHallDTC != 0) ||
     (APPL_DriverFaultDetection_B.Desc_FrontHallDTC != 0));
  APPL_DriverFaultDetection_B.DataTypeConversion6 = (INT8U)
    ((APPL_DriverFaultDetection_B.HeightHallFault != 0) ||
     (APPL_DriverFaultDetection_B.LengthHallFault != 0) ||
     (APPL_DriverFaultDetection_B.BackHallFault != 0) ||
     (APPL_DriverFaultDetection_B.FrontHallFault != 0));
  Rte_SetVfb_DrHeightMotorTimeOutErr
    (APPL_DriverFaultDetection_B.HeightTimeOutFlag);
  Rte_SetVfb_DrBackSwitchAdheErr_Back
    (APPL_DriverFaultDetection_B.BackSwDownAdhesionFault);
  Rte_SetVfb_DrFrontSwitchAdheErr_ForWard
    (APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault);
  Rte_SetVfb_DrFrontSwitchAdheErr_Back
    (APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault);
  Rte_SetVfb_DrLengthMotorTimeOutErr
    (APPL_DriverFaultDetection_B.LengthTimeOutFlag);
  Rte_SetVfb_DrHeightSwitchCmd(APPL_DriverFaultDetection_B.CurrentHeightSwCmd);
  Rte_SetVfb_DrLengthSwitchCmd(APPL_DriverFaultDetection_B.CurrentLengthSwCmd);
  Rte_SetVfb_DrBackSwitchCmd(APPL_DriverFaultDetection_B.CurrentBackSwCmd);
  Rte_SetVfb_DrFrontSwitchCmd(APPL_DriverFaultDetection_B.CurrentFrontSwCmd);
  Rte_SetVfb_DrHeightSwitchAdheErr
    (APPL_DriverFaultDetection_B.HeightSwAdhesionFault);
  Rte_SetVfb_DrLengthSwitchAdheErr
    (APPL_DriverFaultDetection_B.LengthSwAdhesionFault);
  Rte_SetVfb_DrBackMotorTimeOutErr(APPL_DriverFaultDetection_B.BackTimeOutFlag);
  Rte_SetVfb_DrBackSwitchAdheErr(APPL_DriverFaultDetection_B.BackSwAdhesionFault);
  Rte_SetVfb_DrFrontSwitchAdheErr
    (APPL_DriverFaultDetection_B.FrontSwAdhesionFault);
  Rte_SetVfb_DrFrontMotorTimeOutErr(APPL_DriverFaultDetection_B.FrontTimeOutFlag);
  Rte_SetVfb_DrAnyoneSwitchAdheErr
    (APPL_DriverFaultDetection_B.DataTypeConversion4);
  Rte_SetVfb_DrHeightHallErr(APPL_DriverFaultDetection_B.HeightHallFault);
  Rte_SetVfb_DrLengthHallErr(APPL_DriverFaultDetection_B.LengthHallFault);
  Rte_SetVfb_DrBackHallErr(APPL_DriverFaultDetection_B.BackHallFault);
  Rte_SetVfb_DrHeightStallErr(APPL_DriverFaultDetection_B.HeightStallFault);
  Rte_SetVfb_DrLengthStallErr(APPL_DriverFaultDetection_B.LengthStallFault);
  Rte_SetVfb_DrBackStallErr(APPL_DriverFaultDetection_B.BackStallFault);
  Rte_SetVfb_DrFrontStallErr(APPL_DriverFaultDetection_B.FrontStallFault);
  Rte_SetVfb_DrAnyoneStallErr(APPL_DriverFaultDetection_B.DataTypeConversion1);
  Rte_SetVfb_DrAnyoneRelayAdheErr
    (APPL_DriverFaultDetection_B.DataTypeConversion2);
  Rte_SetVfb_DrHeightSwitchAdheErr_ForWard
    (APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault);
  Rte_SetVfb_DrAnyoneSoftStopErr(APPL_DriverFaultDetection_B.DataTypeConversion3);
  Rte_SetVfb_DrAnyoneDTCHallErr(APPL_DriverFaultDetection_B.DataTypeConversion5);
  Rte_SetVfb_DrHeightRelayAdheErr
    (APPL_DriverFaultDetection_B.HeightMidRelayFault);
  Rte_SetVfb_DrLengthRelayAdheErr
    (APPL_DriverFaultDetection_B.LengthMidRelayFault);
  Rte_SetVfb_DrBackRelayAdheErr(APPL_DriverFaultDetection_B.BackMidRelayFault);
  Rte_SetVfb_DrFrontRelayAdheErr(APPL_DriverFaultDetection_B.FrontMidRelayFault);
  Rte_SetVfb_DrAnyoneHallErr(APPL_DriverFaultDetection_B.DataTypeConversion6);
  Rte_SetVfb_DrHeightSwitchAdheErr_Back
    (APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault);
  Rte_SetVfb_DrHeightSoftStopErr(APPL_DriverFaultDetection_B.HeightSoftStopFault);
  Rte_SetVfb_DrLengthSoftStopErr(APPL_DriverFaultDetection_B.LengthSoftStopFault);
  Rte_SetVfb_DrBackSoftStopErr(APPL_DriverFaultDetection_B.BackSoftStopFault);
  Rte_SetVfb_DrFrontSoftStopErr(APPL_DriverFaultDetection_B.FrontSoftStopFault);
  Rte_SetVfb_DrHeightDTCHallErr(APPL_DriverFaultDetection_B.Desc_HeightHallDTC);
  Rte_SetVfb_DrLengthDTCHallErr(APPL_DriverFaultDetection_B.Desc_LengthHallDTC);
  Rte_SetVfb_DrLengthSwitchAdheErr_ForWard
    (APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault);
  Rte_SetVfb_DrBackDTCHallErr(APPL_DriverFaultDetection_B.Desc_BackHallDTC);
  Rte_SetVfb_DrFrontDTCHallErr(APPL_DriverFaultDetection_B.Desc_FrontHallDTC);
  Rte_SetVfb_DrFrontHallErr(APPL_DriverFaultDetection_B.FrontHallFault);
  Rte_SetVfb_DrLengthSwitchAdheErr_Back
    (APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault);
  Rte_SetVfb_DrBackSwitchAdheErr_ForWard
    (APPL_DriverFaultDetection_B.BackSwUpAdhesionFault);
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_a(void)
{
  INT32S tmp;

  /* 达到堵转电流 且无霍尔变化  */
  if (APPL_DriverFaultDetection_DW.LocalHeightHallCnt ==
      MtrCtrlFault_DrHeightHallCnt)
  {
    if (1 == MtrCtrlFault_DrHeightCurrentOverFlag)
    {
      if (APPL_DriverFaultDetection_DW.CurrentOverTimer1 < 255)
      {
        /*  高度大电流计时器 - 启动电压不超过30ms */
        tmp = APPL_DriverFaultDetection_DW.CurrentOverTimer1 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_DriverFaultDetection_DW.CurrentOverTimer1 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_DriverFaultDetection_DW.CurrentOverTimer1 = 0U;
    }

    /* 高度的堵转条件检测 */
    if ((APPL_DriverFaultDetection_DW.HeightStallTimer > CAL_MotorStall_750ms) &&
        (APPL_DriverFaultDetection_DW.CurrentOverTimer1 > 20))
    {
      APPL_DriverFaultDetection_B.HeightStallFault = 1U;
      APPL_DriverFaultDetection_DW.HeightStallTimer = CAL_MotorStall_750ms;
      APPL_DriverFaultDetection_DW.HeightStallNoTimer = 0U;
    }
    else
    {
      /*  高度无霍尔计时器 */
      tmp = APPL_DriverFaultDetection_DW.HeightStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.HeightStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.HeightStallTimer = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer1 = 0U;
  }

  APPL_DriverFaultDetection_DW.LocalHeightHallCnt = MtrCtrlFault_DrHeightHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrHeightMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.HeightSwCmd))
  {
    tmp = APPL_DriverFaultDetection_DW.HeightStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_DriverFaultDetection_DW.HeightStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_aa(void)
{
  INT32S tmp;

  /* 达到堵转电流 且无霍尔变化 */
  if (APPL_DriverFaultDetection_DW.LocalLengthHallCnt ==
      MtrCtrlFault_DrLengthHallCnt)
  {
    if (1 == MtrCtrlFault_DrLengthCurrentOverFlag)
    {
      if (APPL_DriverFaultDetection_DW.CurrentOverTimer2 < 255)
      {
        /*  纵向大电流计时器 */
        tmp = APPL_DriverFaultDetection_DW.CurrentOverTimer2 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_DriverFaultDetection_DW.CurrentOverTimer2 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_DriverFaultDetection_DW.CurrentOverTimer2 = 0U;
    }

    /* 纵向的堵转条件检测 */
    if ((APPL_DriverFaultDetection_DW.LengthStallTimer > CAL_MotorStall_750ms) &&
        (APPL_DriverFaultDetection_DW.CurrentOverTimer2 > 20))
    {
      APPL_DriverFaultDetection_DW.LengthStallTimer = CAL_MotorStall_750ms;
      APPL_DriverFaultDetection_B.LengthStallFault = 1U;
      APPL_DriverFaultDetection_DW.LengthStallNoTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.LengthStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.LengthStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.LengthStallTimer = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer2 = 0U;
  }

  APPL_DriverFaultDetection_DW.LocalLengthHallCnt = MtrCtrlFault_DrLengthHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrLengthMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.LengthSwCmd))
  {
    tmp = APPL_DriverFaultDetection_DW.LengthStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_DriverFaultDetection_DW.LengthStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_aae(void)
{
  INT32S tmp;

  /*  无霍尔变化超时检测 */
  if (APPL_DriverFaultDetection_DW.LocalBackHallCnt ==
      MtrCtrlFault_DrBackHallCnt)
  {
    if (1 == MtrCtrlFault_DrBackCurrentOverFlag)
    {
      if (APPL_DriverFaultDetection_DW.CurrentOverTimer3 < 255)
      {
        /*  靠背大电流计时器 */
        tmp = APPL_DriverFaultDetection_DW.CurrentOverTimer3 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_DriverFaultDetection_DW.CurrentOverTimer3 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_DriverFaultDetection_DW.CurrentOverTimer3 = 0U;
    }

    /* 靠背的堵转条件检测 */
    if ((APPL_DriverFaultDetection_DW.BackStallTimer > CAL_MotorStall_750ms) &&
        (APPL_DriverFaultDetection_DW.CurrentOverTimer3 > 20))
    {
      APPL_DriverFaultDetection_DW.BackStallTimer = CAL_MotorStall_750ms;
      APPL_DriverFaultDetection_B.BackStallFault = 1U;
      APPL_DriverFaultDetection_DW.BackStallNoTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.BackStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.BackStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.BackStallTimer = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer3 = 0U;
  }

  APPL_DriverFaultDetection_DW.LocalBackHallCnt = MtrCtrlFault_DrBackHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrBackMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.BackSwCmd))
  {
    tmp = APPL_DriverFaultDetection_DW.BackStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_DriverFaultDetection_DW.BackStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S10>/StallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_aaed(void)
{
  INT32S tmp;

  /*  无霍尔变化超时检测 */
  if (APPL_DriverFaultDetection_DW.LocalFrontHallCnt ==
      MtrCtrlFault_DrFrontHallCnt)
  {
    if (1 == MtrCtrlFault_DrFrontCurrentOverFlag)
    {
      if (APPL_DriverFaultDetection_DW.CurrentOverTimer4 < 255)
      {
        /*  靠背大电流计时器 */
        tmp = APPL_DriverFaultDetection_DW.CurrentOverTimer4 + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        APPL_DriverFaultDetection_DW.CurrentOverTimer4 = (INT8U)tmp;
      }
    }
    else
    {
      APPL_DriverFaultDetection_DW.CurrentOverTimer4 = 0U;
    }

    /* 靠背的堵转条件检测 */
    if ((APPL_DriverFaultDetection_DW.FrontStallTimer > CAL_MotorStall_750ms) &&
        (APPL_DriverFaultDetection_DW.CurrentOverTimer4 > 20))
    {
      APPL_DriverFaultDetection_DW.FrontStallTimer = CAL_MotorStall_750ms;
      APPL_DriverFaultDetection_B.FrontStallFault = 1U;
      APPL_DriverFaultDetection_DW.FrontStallNoTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.FrontStallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.FrontStallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.FrontStallTimer = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer4 = 0U;
  }

  APPL_DriverFaultDetection_DW.LocalFrontHallCnt = MtrCtrlFault_DrFrontHallCnt;

  /* 无调节动作 同时没有本地开关 */
  if (((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrFrontMotorCmd) &&
      (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.FrontSwCmd))
  {
    tmp = APPL_DriverFaultDetection_DW.FrontStallNoTimer + 1;
    if (tmp > 255)
    {
      tmp = 255;
    }

    APPL_DriverFaultDetection_DW.FrontStallNoTimer = (INT8U)tmp;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge(const INT16U
  *MtrCtrlFault_HeightHallCnt_prev)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_DriverFaultDetection_DW.HeightHallTimer)
  {
    /*  粘连或无电机动作  */
    if ((MtrCtrlFault_DrHeightUpVolt == MtrCtrlFault_DrHeightDownVolt) ||
        ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrHeightMotorCmd))
    {
      APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.HeightHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.HeightHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.HeightHallTimer = CAL_MotorHallInvalid_2s;
    APPL_DriverFaultDetection_B.HeightHallFault = 1U;
    APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (*MtrCtrlFault_HeightHallCnt_prev !=
      APPL_DriverFaultDetection_DW.MtrCtrlFault_HeightHallCnt_start)
  {
    APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
    APPL_DriverFaultDetection_B.HeightHallFault = 0U;
    APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_b(const INT16U
  *MtrCtrlFault_LengthHallCnt_prev)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_DriverFaultDetection_DW.LengthHallTimer)
  {
    /* 粘连或无电机动作 */
    if ((MtrCtrlFault_DrLengthForwardVolt == MtrCtrlFault_DrLengthBackwardVolt) ||
        ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrLengthMotorCmd))
    {
      APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.LengthHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.LengthHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.LengthHallTimer = CAL_MotorHallInvalid_2s;
    APPL_DriverFaultDetection_B.LengthHallFault = 1U;
    APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (*MtrCtrlFault_LengthHallCnt_prev !=
      APPL_DriverFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start)
  {
    APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
    APPL_DriverFaultDetection_B.LengthHallFault = 0U;
    APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_bv(INT16U
  *MtrCtrlFault_BackHallCnt_prev)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_DriverFaultDetection_DW.BackHallTimer)
  {
    /* 粘连或无电机动作 */
    if ((MtrCtrlFault_DrBackForwardVolt == MtrCtrlFault_DrBackBackwardVolt) ||
        ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrBackMotorCmd))
    {
      APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.BackHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.BackHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.BackHallTimer = CAL_MotorHallInvalid_2s;
    APPL_DriverFaultDetection_B.BackHallFault = 1U;
    APPL_DriverFaultDetection_B.Desc_BackHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (*MtrCtrlFault_BackHallCnt_prev !=
      APPL_DriverFaultDetection_DW.MtrCtrlFault_BackHallCnt_start)
  {
    APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
    APPL_DriverFaultDetection_B.BackHallFault = 0U;
    APPL_DriverFaultDetection_B.Desc_BackHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_inner_default_Judge_bvr(void)
{
  INT32S tmp;

  /* 2s超时检测 */
  if (CAL_MotorHallInvalid_2s > APPL_DriverFaultDetection_DW.FrontHallTimer)
  {
    /* 粘连或无电机动作 */
    if ((MtrCtrlFault_DrFrontUpVolt == MtrCtrlFault_DrFrontDownVolt) || ((INT32S)
         enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrFrontMotorCmd))
    {
      APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
    }
    else
    {
      tmp = APPL_DriverFaultDetection_DW.FrontHallTimer + 1;
      if (tmp > 255)
      {
        tmp = 255;
      }

      APPL_DriverFaultDetection_DW.FrontHallTimer = (INT8U)tmp;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.FrontHallTimer = CAL_MotorHallInvalid_2s;
    APPL_DriverFaultDetection_B.FrontHallFault = 1U;
    APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 1U;
  }

  /* 霍尔计数变化 */
  if (APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_prev !=
      APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_start)
  {
    APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
    APPL_DriverFaultDetection_B.FrontHallFault = 0U;
    APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 0U;
  }
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_enter_atomic_Init(void)
{
  APPL_DriverFaultDetection_B.HeightHallFault = 0U;
  APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
  APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 0U;
  APPL_DriverFaultDetection_B.LengthHallFault = 0U;
  APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
  APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 0U;
  APPL_DriverFaultDetection_B.BackHallFault = 0U;
  APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
  APPL_DriverFaultDetection_B.Desc_BackHallDTC = 0U;
  APPL_DriverFaultDetection_B.FrontHallFault = 0U;
  APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
  APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 0U;
}

/* Function for Chart: '<S6>/HallErrorDetection' */
static void APPL_DriverFaultDetection_MotorHallDetect(const INT16U
  *MtrCtrlFault_HeightHallCnt_prev, const enSeatMoveCmd *HeightSwCmd_prev_f,
  const INT16U *MtrCtrlFault_LengthHallCnt_prev, enSeatMoveCmd
  *LengthSwCmd_prev_c, INT16U *MtrCtrlFault_BackHallCnt_prev, enSeatMoveCmd
  *BackSwCmd_prev_n)
{
  /*  无记忆功能 ||不可调节配置  */
  if ((((BOOL)TRUE) != MtrCtrlFault_DrMemoryCfg) ||
      ((enDrAdjustEnable_EN_DrSixWayMotor != MtrCtrlFault_DrAdjustCfg) &&
       (enDrAdjustEnable_EN_DrTwelveWayMotor != MtrCtrlFault_DrAdjustCfg)))
  {
    if (APPL_DriverFaultDetection_DW.is_FrontHallError3 ==
        APPL_DriverFaultDetection_IN_Judge_o)
    {
      APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
      APPL_DriverFaultDetection_DW.is_FrontHallError3 =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }
    else
    {
      APPL_DriverFaultDetection_DW.is_FrontHallError3 =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }

    if (APPL_DriverFaultDetection_DW.is_BackHallError ==
        APPL_DriverFaultDetection_IN_Judge_o)
    {
      APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
      APPL_DriverFaultDetection_DW.is_BackHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }
    else
    {
      APPL_DriverFaultDetection_DW.is_BackHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }

    if (APPL_DriverFaultDetection_DW.is_LengthHallError ==
        APPL_DriverFaultDetection_IN_Judge_o)
    {
      APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
      APPL_DriverFaultDetection_DW.is_LengthHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }
    else
    {
      APPL_DriverFaultDetection_DW.is_LengthHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }

    if (APPL_DriverFaultDetection_DW.is_HeightHallError ==
        APPL_DriverFaultDetection_IN_Judge_o)
    {
      APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
      APPL_DriverFaultDetection_DW.is_HeightHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }
    else
    {
      APPL_DriverFaultDetection_DW.is_HeightHallError =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    }

    APPL_DriverFaultDetection_DW.is_c9_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_Init;
    APPL_DriverFaultDetection_enter_atomic_Init();
  }
  else
  {
    switch (APPL_DriverFaultDetection_DW.is_HeightHallError)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  满足前置条件  */
      if (((BOOL)TRUE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_HeightHallError =
          APPL_DriverFaultDetection_IN_Normal_c;
        APPL_DriverFaultDetection_B.HeightHallFault = 0U;
      }
      break;

     case APPL_DriverFaultDetection_IN_Judge_o:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
        APPL_DriverFaultDetection_DW.is_HeightHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.HeightHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 0U;
      }
      else
      {
        /*    */
        if (((*HeightSwCmd_prev_f !=
              APPL_DriverFaultDetection_DW.HeightSwCmd_start_i) ||
             (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.HeightSwCmd))
            && ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrHeightMotorCmd))
        {
          APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
          APPL_DriverFaultDetection_DW.is_HeightHallError =
            APPL_DriverFaultDetection_IN_Normal_c;
          APPL_DriverFaultDetection_B.HeightHallFault = 0U;
        }
        else
        {
          APPL_DriverFaultDetection_inner_default_Judge
            (MtrCtrlFault_HeightHallCnt_prev);
        }
      }
      break;

     default:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_HeightHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.HeightHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 0U;
      }
      else
      {
        /* 有调节动作 */
        if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrHeightMotorCmd)
        {
          APPL_DriverFaultDetection_DW.is_HeightHallError =
            APPL_DriverFaultDetection_IN_Judge_o;
          APPL_DriverFaultDetection_inner_default_Judge
            (MtrCtrlFault_HeightHallCnt_prev);
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_LengthHallError)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  满足前置条件  */
      if (((BOOL)TRUE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_LengthHallError =
          APPL_DriverFaultDetection_IN_Normal_c;
        APPL_DriverFaultDetection_B.LengthHallFault = 0U;
      }
      break;

     case APPL_DriverFaultDetection_IN_Judge_o:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
        APPL_DriverFaultDetection_DW.is_LengthHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.LengthHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 0U;
      }
      else
      {
        /* 无调节动作 */
        if (((*LengthSwCmd_prev_c !=
              APPL_DriverFaultDetection_DW.LengthSwCmd_start_c) ||
             (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.LengthSwCmd))
            && ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrLengthMotorCmd))
        {
          APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
          APPL_DriverFaultDetection_DW.is_LengthHallError =
            APPL_DriverFaultDetection_IN_Normal_c;
          APPL_DriverFaultDetection_B.LengthHallFault = 0U;
        }
        else
        {
          APPL_DriverFaultDetection_inner_default_Judge_b
            (MtrCtrlFault_LengthHallCnt_prev);
        }
      }
      break;

     default:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_LengthHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.LengthHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 0U;
      }
      else
      {
        /* 有调节动作 */
        if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrLengthMotorCmd)
        {
          APPL_DriverFaultDetection_DW.is_LengthHallError =
            APPL_DriverFaultDetection_IN_Judge_o;
          APPL_DriverFaultDetection_inner_default_Judge_b
            (MtrCtrlFault_LengthHallCnt_prev);
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_BackHallError)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  满足前置条件  */
      if (((BOOL)TRUE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_BackHallError =
          APPL_DriverFaultDetection_IN_Normal_c;
        APPL_DriverFaultDetection_B.BackHallFault = 0U;
      }
      break;

     case APPL_DriverFaultDetection_IN_Judge_o:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
        APPL_DriverFaultDetection_DW.is_BackHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.BackHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_BackHallDTC = 0U;
      }
      else
      {
        /* 无调节动作 */
        if (((*BackSwCmd_prev_n !=
              APPL_DriverFaultDetection_DW.BackSwCmd_start_l) ||
             (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.BackSwCmd)) &&
            ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrBackMotorCmd))
        {
          APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
          APPL_DriverFaultDetection_DW.is_BackHallError =
            APPL_DriverFaultDetection_IN_Normal_c;
          APPL_DriverFaultDetection_B.BackHallFault = 0U;
        }
        else
        {
          APPL_DriverFaultDetection_inner_default_Judge_bv
            (MtrCtrlFault_BackHallCnt_prev);
        }
      }
      break;

     default:
      /*  不满足前置条件  */
      if (((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_BackHallError =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.BackHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_BackHallDTC = 0U;
      }
      else
      {
        /* 有调节动作 */
        if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrBackMotorCmd)
        {
          APPL_DriverFaultDetection_DW.is_BackHallError =
            APPL_DriverFaultDetection_IN_Judge_o;
          APPL_DriverFaultDetection_inner_default_Judge_bv
            (MtrCtrlFault_BackHallCnt_prev);
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_FrontHallError3)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  满足前置条件  */
      if (((BOOL)TRUE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
      {
        APPL_DriverFaultDetection_DW.is_FrontHallError3 =
          APPL_DriverFaultDetection_IN_Normal_c;
        APPL_DriverFaultDetection_B.FrontHallFault = 0U;
      }
      break;

     case APPL_DriverFaultDetection_IN_Judge_o:
      /*  不满足前置条件  */
      if ((((BOOL)FALSE) == APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
          || (enDrAdjustEnable_EN_DrTwelveWayMotor != MtrCtrlFault_DrAdjustCfg))
      {
        APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
        APPL_DriverFaultDetection_DW.is_FrontHallError3 =
          APPL_DriverFaultDetection_IN_Init;
        APPL_DriverFaultDetection_B.FrontHallFault = 0U;
        APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 0U;
      }
      else
      {
        /* 无调节动作 */
        if ((((APPL_DriverFaultDetection_DW.FrontSwCmd_prev_j !=
               APPL_DriverFaultDetection_DW.FrontSwCmd_start_k) ||
              (enSeatMoveCmd_EN_NULL == APPL_DriverFaultDetection_B.FrontSwCmd))
             && ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrFrontMotorCmd))
            || (enDrAdjustEnable_EN_DrTwelveWayMotor != MtrCtrlFault_DrAdjustCfg))
        {
          APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
          APPL_DriverFaultDetection_DW.is_FrontHallError3 =
            APPL_DriverFaultDetection_IN_Normal_c;
          APPL_DriverFaultDetection_B.FrontHallFault = 0U;
        }
        else
        {
          APPL_DriverFaultDetection_inner_default_Judge_bvr();
        }
      }
      break;

     default:
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrFrontMotorCmd) &&
          (enDrAdjustEnable_EN_DrTwelveWayMotor == MtrCtrlFault_DrAdjustCfg))
      {
        APPL_DriverFaultDetection_DW.is_FrontHallError3 =
          APPL_DriverFaultDetection_IN_Judge_o;
        APPL_DriverFaultDetection_inner_default_Judge_bvr();
      }
      else
      {
        /*  不满足前置条件  */
        if (((BOOL)FALSE) ==
            APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC)
        {
          APPL_DriverFaultDetection_DW.is_FrontHallError3 =
            APPL_DriverFaultDetection_IN_Init;
          APPL_DriverFaultDetection_B.FrontHallFault = 0U;
          APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 0U;
        }
      }
      break;
    }
  }
}

/* Function for Chart: '<S8>/MidRelayErrorDetection' */
static void APPL_DriverFaultDetect_inner_default_MidRelayError(void)
{
  APPL_DriverFaultDetection_CheckMidRelayFault(MtrCtrlFault_DrHeightMotorCmd,
    MtrCtrlFault_DrHeightUpVolt, MtrCtrlFault_DrHeightDownVolt,
    &APPL_DriverFaultDetection_B.MidRelayFault_n,
    &APPL_DriverFaultDetection_B.MidRelayTimer_e,
    &APPL_DriverFaultDetection_DW.CheckMidRelayFault);
  APPL_DriverFaultDetection_B.HeightMidRelayFault =
    APPL_DriverFaultDetection_B.MidRelayFault_n;
  APPL_DriverFaultDetection_CheckMidRelayFault(MtrCtrlFault_DrLengthMotorCmd,
    MtrCtrlFault_DrLengthForwardVolt, MtrCtrlFault_DrLengthBackwardVolt,
    &APPL_DriverFaultDetection_B.MidRelayFault_f,
    &APPL_DriverFaultDetection_B.MidRelayTimer_pv,
    &APPL_DriverFaultDetection_DW.CheckMidRelayFault1);
  APPL_DriverFaultDetection_B.LengthMidRelayFault =
    APPL_DriverFaultDetection_B.MidRelayFault_f;
  APPL_DriverFaultDetection_CheckMidRelayFault(MtrCtrlFault_DrBackMotorCmd,
    MtrCtrlFault_DrBackForwardVolt, MtrCtrlFault_DrBackBackwardVolt,
    &APPL_DriverFaultDetection_B.MidRelayFault_p,
    &APPL_DriverFaultDetection_B.MidRelayTimer_p,
    &APPL_DriverFaultDetection_DW.CheckMidRelayFault2);
  APPL_DriverFaultDetection_B.BackMidRelayFault =
    APPL_DriverFaultDetection_B.MidRelayFault_p;
  APPL_DriverFaultDetection_CheckMidRelayFault(MtrCtrlFault_DrFrontMotorCmd,
    MtrCtrlFault_DrFrontUpVolt, MtrCtrlFault_DrFrontDownVolt,
    &APPL_DriverFaultDetection_B.MidRelayFault,
    &APPL_DriverFaultDetection_B.MidRelayTimer,
    &APPL_DriverFaultDetection_DW.CheckMidRelayFault3);
  APPL_DriverFaultDetection_B.FrontMidRelayFault =
    APPL_DriverFaultDetection_B.MidRelayFault;
}

static INT32S APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd(INT32S input)
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
void APPL_DriverFaultDetection_step(void)
{
  enSeatMoveCmd MtrCtrlFault_DRHeightSwitch_prev;
  enSeatMoveCmd MtrCtrlFault_DRLengthSwitch_prev;
  enSeatMoveCmd MtrCtrlFault_DRBackSwitch_prev;
  enSeatMoveCmd MtrCtrlFault_DRFrontSwitch_prev;
  INT32U OutTs_e;
  INT16U MtrCtrlFault_HeightHallCnt_prev;
  INT16U MtrCtrlFault_LengthHallCnt_prev;
  INT16U MtrCtrlFault_BackHallCnt_prev;
  INT32S tmp;
  APPL_DriverFaultDetection_UpDataInputInfo();
  MtrCtrlFault_DRHeightSwitch_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_DRHeightSwitch_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_DRHeightSwitch_start =
    MtrCtrlFault_DrHeightSwitch;
  MtrCtrlFault_DRLengthSwitch_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start =
    MtrCtrlFault_DrLengthSwitch;
  MtrCtrlFault_DRBackSwitch_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start =
    MtrCtrlFault_DrBackSwitch;
  MtrCtrlFault_DRFrontSwitch_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_DRFrontSwitch_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_DRFrontSwitch_start =
    MtrCtrlFault_DrFrontSwitch;
  if (APPL_DriverFaultDetection_DW.is_active_c8_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c8_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_HeightSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_Invalid;
    APPL_DriverFaultDetection_GetCurMsTs();
    APPL_DriverFaultDetection_DW.HeightSwTimer =
      APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
    APPL_DriverFaultDetection_B.HeightSwAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_DW.is_LengthSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_Invalid;
    APPL_DriverFaultDetection_GetCurMsTs();
    APPL_DriverFaultDetection_DW.LengthSwTimer =
      APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
    APPL_DriverFaultDetection_B.LengthSwAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_DW.is_BackSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_Invalid;
    APPL_DriverFaultDetection_GetCurMsTs();
    APPL_DriverFaultDetection_DW.BackSwTimer =
      APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
    APPL_DriverFaultDetection_B.BackSwAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_DW.is_FrontSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_Invalid;
    APPL_DriverFaultDetection_GetCurMsTs();
    APPL_DriverFaultDetection_DW.FrontSwTimer =
      APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
    APPL_DriverFaultDetection_B.FrontSwAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)FALSE);
    APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)FALSE);
  }
  else
  {
    if (APPL_DriverFaultDetection_DW.is_HeightSwitchErrorDeal ==
        APPL_DriverFaultDetection_IN_Invalid)
    {
      /* 开关有效  */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrHeightSwitch)
      {
        APPL_DriverFaultDetection_DW.is_HeightSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.HeightSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.HeightSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.HeightSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrHeightSwitch)
          {
            APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.HeightSwCmd = MtrCtrlFault_DrHeightSwitch;
          APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.HeightSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrHeightSwitch) ||
          (MtrCtrlFault_DRHeightSwitch_prev !=
           APPL_DriverFaultDetection_DW.MtrCtrlFault_DRHeightSwitch_start))
      {
        APPL_DriverFaultDetection_DW.is_HeightSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Invalid;
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.HeightSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
        APPL_DriverFaultDetection_B.HeightSwAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.HeightSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.HeightSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.HeightSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrHeightSwitch)
          {
            APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.HeightSwCmd = MtrCtrlFault_DrHeightSwitch;
          APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_DriverFaultDetection_DW.is_LengthSwitchErrorDeal ==
        APPL_DriverFaultDetection_IN_Invalid)
    {
      /* 开关有效   */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrLengthSwitch)
      {
        APPL_DriverFaultDetection_DW.is_LengthSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.LengthSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.LengthSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.LengthSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrLengthSwitch)
          {
            APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.LengthSwCmd = MtrCtrlFault_DrLengthSwitch;
          APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.LengthSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrLengthSwitch) ||
          (MtrCtrlFault_DRLengthSwitch_prev !=
           APPL_DriverFaultDetection_DW.MtrCtrlFault_DRLengthSwitch_start))
      {
        APPL_DriverFaultDetection_DW.is_LengthSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Invalid;
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.LengthSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
        APPL_DriverFaultDetection_B.LengthSwAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.LengthSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.LengthSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.LengthSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrLengthSwitch)
          {
            APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.LengthSwCmd = MtrCtrlFault_DrLengthSwitch;
          APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_DriverFaultDetection_DW.is_BackSwitchErrorDeal ==
        APPL_DriverFaultDetection_IN_Invalid)
    {
      /* 开关有效   */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrBackSwitch)
      {
        APPL_DriverFaultDetection_DW.is_BackSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.BackSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.BackSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.BackSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrBackSwitch)
          {
            APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.BackSwCmd = MtrCtrlFault_DrBackSwitch;
          APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.BackSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrBackSwitch) ||
          (MtrCtrlFault_DRBackSwitch_prev !=
           APPL_DriverFaultDetection_DW.MtrCtrlFault_DRBackSwitch_start))
      {
        APPL_DriverFaultDetection_DW.is_BackSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Invalid;
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.BackSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
        APPL_DriverFaultDetection_B.BackSwAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.BackSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.BackSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.BackSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrBackSwitch)
          {
            APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.BackSwCmd = MtrCtrlFault_DrBackSwitch;
          APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_DriverFaultDetection_DW.is_FrontSwitchErrorDeal ==
        APPL_DriverFaultDetection_IN_Invalid)
    {
      /* 开关有效   */
      if (enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrFrontSwitch)
      {
        APPL_DriverFaultDetection_DW.is_FrontSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Valid;

        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.FrontSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.FrontSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.FrontSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrFrontSwitch)
          {
            APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.FrontSwCmd = MtrCtrlFault_DrFrontSwitch;
          APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
      else
      {
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.FrontSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
      }
    }
    else
    {
      /*  跳变 无效  */
      if ((enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrFrontSwitch) ||
          (MtrCtrlFault_DRFrontSwitch_prev !=
           APPL_DriverFaultDetection_DW.MtrCtrlFault_DRFrontSwitch_start))
      {
        APPL_DriverFaultDetection_DW.is_FrontSwitchErrorDeal =
          APPL_DriverFaultDetection_IN_Invalid;
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_DW.FrontSwTimer =
          APPL_DriverFaultDetection_B.DrAdj_CurMsTs;
        APPL_DriverFaultDetection_B.FrontSwAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
        APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)FALSE);
        APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)FALSE);
      }
      else
      {
        /* 持续有效时间超过90s，则诊断为开关粘滞故障 */
        APPL_DriverFaultDetection_GetCurMsTs();
        APPL_DriverFaultDetection_TimeDiffTs
          (APPL_DriverFaultDetection_DW.FrontSwTimer,
           APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
        if (OutTs_e >= CAL_ManualSwValid_90s)
        {
          APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
          APPL_DriverFaultDetection_GetCurMsTs();
          APPL_DriverFaultDetection_GetDefTime(CAL_ManualSwValid_90s,
            APPL_DriverFaultDetection_B.DrAdj_CurMsTs, &OutTs_e);
          APPL_DriverFaultDetection_DW.FrontSwTimer = OutTs_e;
          APPL_DriverFaultDetection_B.FrontSwAdhesionFault = ((BOOL)TRUE);
          if (enSeatMoveCmd_EN_UP_FORWARD == MtrCtrlFault_DrFrontSwitch)
          {
            APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)TRUE);
          }
          else
          {
            APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)TRUE);
          }
        }
        else
        {
          APPL_DriverFaultDetection_B.FrontSwCmd = MtrCtrlFault_DrFrontSwitch;
          APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = ((BOOL)FALSE);
          APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = ((BOOL)FALSE);
        }
      }
    }
  }

  MtrCtrlFault_DRHeightSwitch_prev =
    APPL_DriverFaultDetection_DW.HeightSwCmd_start;
  APPL_DriverFaultDetection_DW.HeightSwCmd_start =
    APPL_DriverFaultDetection_B.HeightSwCmd;
  MtrCtrlFault_DRLengthSwitch_prev =
    APPL_DriverFaultDetection_DW.LengthSwCmd_start;
  APPL_DriverFaultDetection_DW.LengthSwCmd_start =
    APPL_DriverFaultDetection_B.LengthSwCmd;
  MtrCtrlFault_DRBackSwitch_prev = APPL_DriverFaultDetection_DW.BackSwCmd_start;
  APPL_DriverFaultDetection_DW.BackSwCmd_start =
    APPL_DriverFaultDetection_B.BackSwCmd;
  MtrCtrlFault_DRFrontSwitch_prev =
    APPL_DriverFaultDetection_DW.FrontSwCmd_start;
  APPL_DriverFaultDetection_DW.FrontSwCmd_start =
    APPL_DriverFaultDetection_B.FrontSwCmd;
  if (APPL_DriverFaultDetection_DW.is_active_c10_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c10_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_HeightStallError =
      APPL_DriverFaultDetection_IN_Normal_o;
    APPL_DriverFaultDetection_B.HeightStallFault = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer1 = 0U;
    APPL_DriverFaultDetection_DW.is_LengthStallError =
      APPL_DriverFaultDetection_IN_Normal_o;
    APPL_DriverFaultDetection_B.LengthStallFault = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer2 = 0U;
    APPL_DriverFaultDetection_DW.is_BackStallError =
      APPL_DriverFaultDetection_IN_Normal_o;
    APPL_DriverFaultDetection_B.BackStallFault = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer3 = 0U;
    APPL_DriverFaultDetection_DW.is_FrontStallError =
      APPL_DriverFaultDetection_IN_Normal_o;
    APPL_DriverFaultDetection_B.FrontStallFault = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer4 = 0U;
  }
  else
  {
    if (APPL_DriverFaultDetection_DW.is_HeightStallError ==
        APPL_DriverFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms <
           APPL_DriverFaultDetection_DW.HeightStallNoTimer) ||
          (MtrCtrlFault_DRHeightSwitch_prev !=
           APPL_DriverFaultDetection_DW.HeightSwCmd_start) ||
          (MtrCtrlFault_DrPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.HeightStallTimer = 0U;
        APPL_DriverFaultDetection_DW.HeightStallNoTimer = 0U;
        APPL_DriverFaultDetection_DW.is_HeightStallError =
          APPL_DriverFaultDetection_IN_Normal_o;
        APPL_DriverFaultDetection_B.HeightStallFault = 0U;
        APPL_DriverFaultDetection_DW.CurrentOverTimer1 = 0U;
      }
      else
      {
        APPL_DriverFaultDetection_inner_default_Judge_a();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrHeightMotorCmd) &&
          (MtrCtrlFault_DrPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.is_HeightStallError =
          APPL_DriverFaultDetection_IN_Judge_e;
        APPL_DriverFaultDetection_inner_default_Judge_a();
      }
    }

    if (APPL_DriverFaultDetection_DW.is_LengthStallError ==
        APPL_DriverFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms <
           APPL_DriverFaultDetection_DW.LengthStallNoTimer) ||
          (MtrCtrlFault_DRLengthSwitch_prev !=
           APPL_DriverFaultDetection_DW.LengthSwCmd_start) ||
          (MtrCtrlFault_DrPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.LengthStallTimer = 0U;
        APPL_DriverFaultDetection_DW.LengthStallNoTimer = 0U;
        APPL_DriverFaultDetection_DW.is_LengthStallError =
          APPL_DriverFaultDetection_IN_Normal_o;
        APPL_DriverFaultDetection_B.LengthStallFault = 0U;
        APPL_DriverFaultDetection_DW.CurrentOverTimer2 = 0U;
      }
      else
      {
        APPL_DriverFaultDetection_inner_default_Judge_aa();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrLengthMotorCmd) &&
          (MtrCtrlFault_DrPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.is_LengthStallError =
          APPL_DriverFaultDetection_IN_Judge_e;
        APPL_DriverFaultDetection_inner_default_Judge_aa();
      }
    }

    if (APPL_DriverFaultDetection_DW.is_BackStallError ==
        APPL_DriverFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms <
           APPL_DriverFaultDetection_DW.BackStallNoTimer) ||
          (MtrCtrlFault_DRBackSwitch_prev !=
           APPL_DriverFaultDetection_DW.BackSwCmd_start) ||
          (MtrCtrlFault_DrPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.BackStallTimer = 0U;
        APPL_DriverFaultDetection_DW.BackStallNoTimer = 0U;
        APPL_DriverFaultDetection_DW.is_BackStallError =
          APPL_DriverFaultDetection_IN_Normal_o;
        APPL_DriverFaultDetection_B.BackStallFault = 0U;
        APPL_DriverFaultDetection_DW.CurrentOverTimer3 = 0U;
      }
      else
      {
        APPL_DriverFaultDetection_inner_default_Judge_aae();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrBackMotorCmd) &&
          (MtrCtrlFault_DrPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.is_BackStallError =
          APPL_DriverFaultDetection_IN_Judge_e;
        APPL_DriverFaultDetection_inner_default_Judge_aae();
      }
    }

    if (APPL_DriverFaultDetection_DW.is_FrontStallError ==
        APPL_DriverFaultDetection_IN_Judge_e)
    {
      /*  超过故障计时 或按键变化  */
      if ((CAL_LockErrNoTime_30ms <
           APPL_DriverFaultDetection_DW.FrontStallNoTimer) ||
          (MtrCtrlFault_DRFrontSwitch_prev !=
           APPL_DriverFaultDetection_DW.FrontSwCmd_start) ||
          (MtrCtrlFault_DrPowerModeStatus == enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.FrontStallTimer = 0U;
        APPL_DriverFaultDetection_DW.FrontStallNoTimer = 0U;
        APPL_DriverFaultDetection_DW.is_FrontStallError =
          APPL_DriverFaultDetection_IN_Normal_o;
        APPL_DriverFaultDetection_B.FrontStallFault = 0U;
        APPL_DriverFaultDetection_DW.CurrentOverTimer4 = 0U;
      }
      else
      {
        APPL_DriverFaultDetection_inner_default_Judge_aaed();
      }
    }
    else
    {
      /* 有调节动作 */
      if (((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrFrontMotorCmd) &&
          (MtrCtrlFault_DrPowerModeStatus != enIgnSts_eCrank))
      {
        APPL_DriverFaultDetection_DW.is_FrontStallError =
          APPL_DriverFaultDetection_IN_Judge_e;
        APPL_DriverFaultDetection_inner_default_Judge_aaed();
      }
    }
  }

  MtrCtrlFault_HeightHallCnt_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_HeightHallCnt_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_HeightHallCnt_start =
    MtrCtrlFault_DrHeightHallCnt;
  MtrCtrlFault_DRHeightSwitch_prev =
    APPL_DriverFaultDetection_DW.HeightSwCmd_start_i;
  APPL_DriverFaultDetection_DW.HeightSwCmd_start_i =
    APPL_DriverFaultDetection_B.HeightSwCmd;
  MtrCtrlFault_LengthHallCnt_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_LengthHallCnt_start =
    MtrCtrlFault_DrLengthHallCnt;
  MtrCtrlFault_DRLengthSwitch_prev =
    APPL_DriverFaultDetection_DW.LengthSwCmd_start_c;
  APPL_DriverFaultDetection_DW.LengthSwCmd_start_c =
    APPL_DriverFaultDetection_B.LengthSwCmd;
  MtrCtrlFault_BackHallCnt_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_BackHallCnt_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_BackHallCnt_start =
    MtrCtrlFault_DrBackHallCnt;
  MtrCtrlFault_DRBackSwitch_prev =
    APPL_DriverFaultDetection_DW.BackSwCmd_start_l;
  APPL_DriverFaultDetection_DW.BackSwCmd_start_l =
    APPL_DriverFaultDetection_B.BackSwCmd;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_prev =
    APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_start;
  APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_start =
    MtrCtrlFault_DrFrontHallCnt;
  APPL_DriverFaultDetection_DW.FrontSwCmd_prev_j =
    APPL_DriverFaultDetection_DW.FrontSwCmd_start_k;
  APPL_DriverFaultDetection_DW.FrontSwCmd_start_k =
    APPL_DriverFaultDetection_B.FrontSwCmd;
  if (APPL_DriverFaultDetection_DW.is_active_c9_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.MtrCtrlFault_FrontHallCnt_prev =
      MtrCtrlFault_DrFrontHallCnt;
    APPL_DriverFaultDetection_DW.FrontSwCmd_prev_j =
      APPL_DriverFaultDetection_B.FrontSwCmd;
    APPL_DriverFaultDetection_DW.is_active_c9_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_c9_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_Init;
    APPL_DriverFaultDetection_enter_atomic_Init();
  }
  else if (APPL_DriverFaultDetection_DW.is_c9_APPL_DriverFaultDetection ==
           APPL_DriverFaultDetection_IN_Init)
  {
    /*  有记忆功能 且非不可调节配置  */
    if ((((BOOL)TRUE) == MtrCtrlFault_DrMemoryCfg) &&
        ((enDrAdjustEnable_EN_DrSixWayMotor == MtrCtrlFault_DrAdjustCfg) ||
         (enDrAdjustEnable_EN_DrTwelveWayMotor == MtrCtrlFault_DrAdjustCfg)))
    {
      APPL_DriverFaultDetection_DW.is_c9_APPL_DriverFaultDetection =
        APPL_DriverFaultDetection_IN_MotorHallDetect;
      APPL_DriverFaultDetection_DW.is_HeightHallError =
        APPL_DriverFaultDetection_IN_Normal_c;
      APPL_DriverFaultDetection_B.HeightHallFault = 0U;
      APPL_DriverFaultDetection_DW.is_LengthHallError =
        APPL_DriverFaultDetection_IN_Normal_c;
      APPL_DriverFaultDetection_B.LengthHallFault = 0U;
      APPL_DriverFaultDetection_DW.is_BackHallError =
        APPL_DriverFaultDetection_IN_Normal_c;
      APPL_DriverFaultDetection_B.BackHallFault = 0U;
      APPL_DriverFaultDetection_DW.is_FrontHallError3 =
        APPL_DriverFaultDetection_IN_Normal_c;
      APPL_DriverFaultDetection_B.FrontHallFault = 0U;
    }
  }
  else
  {
    APPL_DriverFaultDetection_MotorHallDetect(&MtrCtrlFault_HeightHallCnt_prev,
      &MtrCtrlFault_DRHeightSwitch_prev, &MtrCtrlFault_LengthHallCnt_prev,
      &MtrCtrlFault_DRLengthSwitch_prev, &MtrCtrlFault_BackHallCnt_prev,
      &MtrCtrlFault_DRBackSwitch_prev);
  }

  if (APPL_DriverFaultDetection_DW.is_active_c3_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c3_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetect_inner_default_MidRelayError();
  }
  else
  {
    APPL_DriverFaultDetect_inner_default_MidRelayError();
  }

  if (APPL_DriverFaultDetection_DW.is_active_c33_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c33_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_HeightSoft =
      APPL_DriverFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt >=
        MtrCtrlFault_DrMotorSoftStopCntMax)
    {
      APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
        enSeatMoveCmd_EN_NULL;
    }

    APPL_DriverFaultDetection_DW.is_LengthSoft =
      APPL_DriverFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt >=
        MtrCtrlFault_DrMotorSoftStopCntMax)
    {
      APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
        enSeatMoveCmd_EN_NULL;
    }

    APPL_DriverFaultDetection_DW.is_BackSoft = APPL_DriverFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt >=
        MtrCtrlFault_DrMotorSoftStopCntMax)
    {
      APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
        enSeatMoveCmd_EN_NULL;
    }

    APPL_DriverFaultDetection_DW.is_FrontSoft =
      APPL_DriverFaultDetection_IN_Init;

    /* 超过计数无故障  */
    if (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt >=
        MtrCtrlFault_DrMotorSoftStopCntMax)
    {
      APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
        enSeatMoveCmd_EN_NULL;
    }
  }
  else
  {
    APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt =
      MtrCtrlFault_DrHeightSoftStopCnt;
    APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt =
      MtrCtrlFault_DrLengthSoftStopCnt;
    APPL_DriverFaultDetection_DW.BackSoftStopBufCnt =
      MtrCtrlFault_DrBackSoftStopCnt;
    APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt =
      MtrCtrlFault_DrFrontSoftStopCnt;
    switch (APPL_DriverFaultDetection_DW.is_HeightSoft)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      tmp = enSeatMoveCmd_EN_UP_FORWARD;
      if ((0 != MtrCtrlFault_DrHeightStopPosi) && (0xFFFF !=
           MtrCtrlFault_DrHeightStopPosi) &&
          (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt <
           MtrCtrlFault_DrMotorSoftStopCntMax) && (MtrCtrlFault_DrHeightMotorCmd
           == tmp) && (APPL_DriverFaultDetection_B.HeightSoftStopFault != tmp))
      {
        APPL_DriverFaultDetection_DW.is_HeightSoft =
          APPL_DriverFaultDetection_IN_LeftUpFront;
        APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrHeightHallCnt >= (MtrCtrlFault_DrHeightStopPosi +
             MtrCtrlFault_DrHeightMotorSize) - ((INT8U)D_DrSoftStopDef_H))
        {
          tmp = APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt =
            APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_DrHeightStopPosi) && (0xFFFF !=
             MtrCtrlFault_DrHeightStopPosi) &&
            (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt <
             MtrCtrlFault_DrMotorSoftStopCntMax) &&
            (MtrCtrlFault_DrHeightMotorCmd == (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD) &&
            (APPL_DriverFaultDetection_B.HeightSoftStopFault != (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD))
        {
          APPL_DriverFaultDetection_DW.is_HeightSoft =
            APPL_DriverFaultDetection_IN_RightDnBack;
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最小软止点  */
          if (MtrCtrlFault_DrHeightHallCnt <= MtrCtrlFault_DrHeightStopPosi +
              ((INT8U)D_DrSoftStopDef_H))
          {
            tmp = APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt = (INT8U)tmp;
            APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_DN_BACKWARD;
            APPL_DriverFaultDetection_B.Cnt =
              APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt;
            APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt >=
              MtrCtrlFault_DrMotorSoftStopCntMax)
          {
            APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_DriverFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrHeightMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.HeightSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_HeightSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrHeightHallCnt >= (MtrCtrlFault_DrHeightStopPosi +
             MtrCtrlFault_DrHeightMotorSize) - ((INT8U)D_DrSoftStopDef_H))
        {
          tmp = APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt =
            APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrHeightMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.HeightSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_DriverFaultDetection_DW.is_HeightSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_DrHeightHallCnt <= MtrCtrlFault_DrHeightStopPosi +
            ((INT8U)D_DrSoftStopDef_H))
        {
          tmp = APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.HeightSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_DriverFaultDetection_B.Cnt =
            APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetHeightSoftStopCnt();
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_LengthSoft)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      if ((0 != MtrCtrlFault_DrLengthStopPosi) && (0xFFFF !=
           MtrCtrlFault_DrLengthStopPosi) &&
          (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt <
           MtrCtrlFault_DrMotorSoftStopCntMax) && (MtrCtrlFault_DrLengthMotorCmd
           == (INT32S)enSeatMoveCmd_EN_UP_FORWARD) &&
          (APPL_DriverFaultDetection_B.LengthSoftStopFault != (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_LengthSoft =
          APPL_DriverFaultDetection_IN_LeftUpFront;
        APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrLengthHallCnt >= (MtrCtrlFault_DrLengthStopPosi +
             MtrCtrlFault_DrLengthMotorSize) - ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt_h =
            APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_DrLengthStopPosi) && (0xFFFF !=
             MtrCtrlFault_DrLengthStopPosi) &&
            (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt <
             MtrCtrlFault_DrMotorSoftStopCntMax) &&
            (MtrCtrlFault_DrLengthMotorCmd == (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD) &&
            (APPL_DriverFaultDetection_B.LengthSoftStopFault != (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD))
        {
          APPL_DriverFaultDetection_DW.is_LengthSoft =
            APPL_DriverFaultDetection_IN_RightDnBack;
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最小软止点  */
          if (MtrCtrlFault_DrLengthHallCnt <= MtrCtrlFault_DrLengthStopPosi +
              ((INT8U)D_DrSoftStopDef_L))
          {
            tmp = APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
            APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_DN_BACKWARD;
            APPL_DriverFaultDetection_B.Cnt_h =
              APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt;
            APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt >=
              MtrCtrlFault_DrMotorSoftStopCntMax)
          {
            APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_DriverFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrLengthMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.LengthSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_LengthSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrLengthHallCnt >= (MtrCtrlFault_DrLengthStopPosi +
             MtrCtrlFault_DrLengthMotorSize) - ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt_h =
            APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrLengthMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.LengthSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_DriverFaultDetection_DW.is_LengthSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_DrLengthHallCnt <= MtrCtrlFault_DrLengthStopPosi +
            ((INT8U)D_DrSoftStopDef_L))
        {
          tmp = APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.LengthSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_DriverFaultDetection_B.Cnt_h =
            APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt;
          APPL_DriverFaultDetecti_DrAdj_SetLengthSoftStopCnt();
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_BackSoft)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      if ((0 != MtrCtrlFault_DrBackStopPosi) && (0xFFFF !=
           MtrCtrlFault_DrBackStopPosi) &&
          (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt <
           MtrCtrlFault_DrMotorSoftStopCntMax) && (MtrCtrlFault_DrBackMotorCmd ==
           (INT32S)enSeatMoveCmd_EN_UP_FORWARD) &&
          (APPL_DriverFaultDetection_B.BackSoftStopFault != (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_BackSoft =
          APPL_DriverFaultDetection_IN_LeftUpFront;
        APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrBackHallCnt >= (MtrCtrlFault_DrBackStopPosi +
             MtrCtrlFault_DrBackMotorSize) - ((INT8U)D_DrSoftStopDef_B))
        {
          tmp = APPL_DriverFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt_i =
            APPL_DriverFaultDetection_DW.BackSoftStopBufCnt;
          APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_DrBackStopPosi) && (0xFFFF !=
             MtrCtrlFault_DrBackStopPosi) &&
            (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt <
             MtrCtrlFault_DrMotorSoftStopCntMax) && (MtrCtrlFault_DrBackMotorCmd
             == (INT32S)enSeatMoveCmd_EN_DN_BACKWARD) &&
            (APPL_DriverFaultDetection_B.BackSoftStopFault != (INT32S)
             enSeatMoveCmd_EN_DN_BACKWARD))
        {
          APPL_DriverFaultDetection_DW.is_BackSoft =
            APPL_DriverFaultDetection_IN_RightDnBack;
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最小软止点  */
          if (MtrCtrlFault_DrBackHallCnt <= MtrCtrlFault_DrBackStopPosi +
              ((INT8U)D_DrSoftStopDef_B))
          {
            tmp = APPL_DriverFaultDetection_DW.BackSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_DriverFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
            APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_DN_BACKWARD;
            APPL_DriverFaultDetection_B.Cnt_i =
              APPL_DriverFaultDetection_DW.BackSoftStopBufCnt;
            APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt >=
              MtrCtrlFault_DrMotorSoftStopCntMax)
          {
            APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_DriverFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrBackMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.BackSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_BackSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrBackHallCnt >= (MtrCtrlFault_DrBackStopPosi +
             MtrCtrlFault_DrBackMotorSize) - ((INT8U)D_DrSoftStopDef_B))
        {
          tmp = APPL_DriverFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt_i =
            APPL_DriverFaultDetection_DW.BackSoftStopBufCnt;
          APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrBackMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.BackSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_DriverFaultDetection_DW.is_BackSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.BackSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_DrBackHallCnt <= MtrCtrlFault_DrBackStopPosi + ((INT8U)
             D_DrSoftStopDef_B))
        {
          tmp = APPL_DriverFaultDetection_DW.BackSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.BackSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.BackSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_DriverFaultDetection_B.Cnt_i =
            APPL_DriverFaultDetection_DW.BackSoftStopBufCnt;
          APPL_DriverFaultDetection_DrAdj_SetBackSoftStopCnt();
        }
      }
      break;
    }

    switch (APPL_DriverFaultDetection_DW.is_FrontSoft)
    {
     case APPL_DriverFaultDetection_IN_Init:
      /*  已学习硬止点
         软止点计数小于 最大值
         有控制指令  */
      if ((0 != MtrCtrlFault_DrFrontStopPosi) && (0xFFFF !=
           MtrCtrlFault_DrFrontStopPosi) &&
          (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt <
           MtrCtrlFault_DrMotorSoftStopCntMax) && (MtrCtrlFault_DrFrontMotorCmd ==
           (INT32S)enSeatMoveCmd_EN_DN_BACKWARD) &&
          (APPL_DriverFaultDetection_B.FrontSoftStopFault != (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_DriverFaultDetection_DW.is_FrontSoft =
          APPL_DriverFaultDetection_IN_RightDnBack;
        APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_DrFrontHallCnt <= MtrCtrlFault_DrFrontStopPosi +
            ((INT8U)D_DrSoftStopDef_F))
        {
          tmp = APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_DriverFaultDetection_B.Cnt_f =
            APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt;
          APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt();
        }
      }
      else
      {
        /*  已学习硬止点
           软止点计数小于 最大值
           有控制指令  */
        if ((0 != MtrCtrlFault_DrFrontStopPosi) && (0xFFFF !=
             MtrCtrlFault_DrFrontStopPosi) &&
            (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt <
             MtrCtrlFault_DrMotorSoftStopCntMax) &&
            (MtrCtrlFault_DrFrontMotorCmd == (INT32S)enSeatMoveCmd_EN_UP_FORWARD)
            && (APPL_DriverFaultDetection_B.FrontSoftStopFault != (INT32S)
                enSeatMoveCmd_EN_UP_FORWARD))
        {
          APPL_DriverFaultDetection_DW.is_FrontSoft =
            APPL_DriverFaultDetection_IN_LeftUpFront;
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;

          /*  超过最大软止点  */
          if (MtrCtrlFault_DrFrontHallCnt >= (MtrCtrlFault_DrFrontStopPosi +
               MtrCtrlFault_DrFrontMotorSize) - ((INT8U)D_DrSoftStopDef_F))
          {
            tmp = APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt = (INT8U)tmp;
            APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_UP_FORWARD;
            APPL_DriverFaultDetection_B.Cnt_f =
              APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt;
            APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt();
          }
        }
        else
        {
          /* 超过计数无故障  */
          if (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt >=
              MtrCtrlFault_DrMotorSoftStopCntMax)
          {
            APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
              enSeatMoveCmd_EN_NULL;
          }
        }
      }
      break;

     case APPL_DriverFaultDetection_IN_LeftUpFront:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrFrontMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.FrontSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_UP_FORWARD))
      {
        APPL_DriverFaultDetection_DW.is_FrontSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最大软止点  */
        if (MtrCtrlFault_DrFrontHallCnt >= (MtrCtrlFault_DrFrontStopPosi +
             MtrCtrlFault_DrFrontMotorSize) - ((INT8U)D_DrSoftStopDef_F))
        {
          tmp = APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_UP_FORWARD;
          APPL_DriverFaultDetection_B.Cnt_f =
            APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt;
          APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt();
        }
      }
      break;

     default:
      /* 无控制指令  */
      if ((MtrCtrlFault_DrFrontMotorCmd == (INT32S)enSeatMoveCmd_EN_NULL) ||
          (APPL_DriverFaultDetection_B.FrontSoftStopFault == (INT32S)
           enSeatMoveCmd_EN_DN_BACKWARD))
      {
        APPL_DriverFaultDetection_DW.is_FrontSoft =
          APPL_DriverFaultDetection_IN_Init;

        /* 超过计数无故障  */
        if (APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt >=
            MtrCtrlFault_DrMotorSoftStopCntMax)
        {
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_NULL;
        }
      }
      else
      {
        APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
          enSeatMoveCmd_EN_NULL;

        /*  超过最小软止点  */
        if (MtrCtrlFault_DrFrontHallCnt <= MtrCtrlFault_DrFrontStopPosi +
            ((INT8U)D_DrSoftStopDef_F))
        {
          tmp = APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt = (INT8U)tmp;
          APPL_DriverFaultDetection_B.FrontSoftStopFault = (INT8U)
            enSeatMoveCmd_EN_DN_BACKWARD;
          APPL_DriverFaultDetection_B.Cnt_f =
            APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt;
          APPL_DriverFaultDetectio_DrAdj_SetFrontSoftStopCnt();
        }
      }
      break;
    }
  }

  APPL_DriverFaultDetection_UpDataOutputInfo();
  if (APPL_DriverFaultDetection_DW.is_active_c16_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c16_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_HeightAdjust =
      APPL_DriverFaultDetection_IN_Init_e;
    APPL_DriverFaultDetection_DW.HeightTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.HeightSwCmd)
    {
      APPL_DriverFaultDetection_B.HeightTimeOutFlag = ((BOOL)FALSE);
    }

    APPL_DriverFaultDetection_DW.is_VerticalAdjust =
      APPL_DriverFaultDetection_IN_Init_e;
    APPL_DriverFaultDetection_DW.LengthTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.LengthSwCmd)
    {
      APPL_DriverFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
    }

    APPL_DriverFaultDetection_DW.is_BackAdjust =
      APPL_DriverFaultDetection_IN_Init_e;
    APPL_DriverFaultDetection_DW.BackTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.BackSwCmd)
    {
      APPL_DriverFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
    }

    APPL_DriverFaultDetection_DW.is_FrontAngleAdjust =
      APPL_DriverFaultDetection_IN_Init_e;
    APPL_DriverFaultDetection_DW.FrontTimer = 0U;

    /*  按键无效  */
    if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.FrontSwCmd)
    {
      APPL_DriverFaultDetection_B.FrontTimeOutFlag = ((BOOL)FALSE);
    }
  }
  else
  {
    if (APPL_DriverFaultDetection_DW.is_HeightAdjust ==
        APPL_DriverFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrHeightMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_HeightAdjust =
          APPL_DriverFaultDetection_IN_Init_e;
        APPL_DriverFaultDetection_DW.HeightTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.HeightSwCmd)
        {
          APPL_DriverFaultDetection_B.HeightTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_DriverFaultDetection_DW.HeightTimer <
               CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_DriverFaultDetection_DW.HeightTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_DriverFaultDetection_DW.HeightTimer = (INT16U)tmp;
      }
      else
      {
        APPL_DriverFaultDetection_B.HeightTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrHeightMotorCmd)
    {
      APPL_DriverFaultDetection_DW.is_HeightAdjust =
        APPL_DriverFaultDetection_IN_Action;
      if (APPL_DriverFaultDetection_DW.HeightTimer < CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_DriverFaultDetection_DW.HeightTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_DriverFaultDetection_DW.HeightTimer = (INT16U)tmp;
      }
      else
      {
        APPL_DriverFaultDetection_B.HeightTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /*  按键无效  */
      if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.HeightSwCmd)
      {
        APPL_DriverFaultDetection_B.HeightTimeOutFlag = ((BOOL)FALSE);
      }
    }

    if (APPL_DriverFaultDetection_DW.is_VerticalAdjust ==
        APPL_DriverFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrLengthMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_VerticalAdjust =
          APPL_DriverFaultDetection_IN_Init_e;
        APPL_DriverFaultDetection_DW.LengthTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.LengthSwCmd)
        {
          APPL_DriverFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_DriverFaultDetection_DW.LengthTimer <
               CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_DriverFaultDetection_DW.LengthTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_DriverFaultDetection_DW.LengthTimer = (INT16U)tmp;
      }
      else
      {
        APPL_DriverFaultDetection_B.LengthTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* 高度、纵向电机没有命令或计时已到 */
      if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrLengthMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_VerticalAdjust =
          APPL_DriverFaultDetection_IN_Action;
        if (APPL_DriverFaultDetection_DW.LengthTimer < CAL_MotorMaxRunTime_60s)
        {
          tmp = APPL_DriverFaultDetection_DW.LengthTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          APPL_DriverFaultDetection_DW.LengthTimer = (INT16U)tmp;
        }
        else
        {
          APPL_DriverFaultDetection_B.LengthTimeOutFlag = ((BOOL)TRUE);
        }
      }
      else
      {
        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.LengthSwCmd)
        {
          APPL_DriverFaultDetection_B.LengthTimeOutFlag = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_DriverFaultDetection_DW.is_BackAdjust ==
        APPL_DriverFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrBackMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_BackAdjust =
          APPL_DriverFaultDetection_IN_Init_e;
        APPL_DriverFaultDetection_DW.BackTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.BackSwCmd)
        {
          APPL_DriverFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_DriverFaultDetection_DW.BackTimer < CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_DriverFaultDetection_DW.BackTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_DriverFaultDetection_DW.BackTimer = (INT16U)tmp;
      }
      else
      {
        APPL_DriverFaultDetection_B.BackTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* 高度、纵向、前部电机没有命令或计时已到 */
      if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrBackMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_BackAdjust =
          APPL_DriverFaultDetection_IN_Action;
        if (APPL_DriverFaultDetection_DW.BackTimer < CAL_MotorMaxRunTime_60s)
        {
          tmp = APPL_DriverFaultDetection_DW.BackTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          APPL_DriverFaultDetection_DW.BackTimer = (INT16U)tmp;
        }
        else
        {
          APPL_DriverFaultDetection_B.BackTimeOutFlag = ((BOOL)TRUE);
        }
      }
      else
      {
        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.BackSwCmd)
        {
          APPL_DriverFaultDetection_B.BackTimeOutFlag = ((BOOL)FALSE);
        }
      }
    }

    if (APPL_DriverFaultDetection_DW.is_FrontAngleAdjust ==
        APPL_DriverFaultDetection_IN_Action)
    {
      if ((INT32S)enSeatMoveCmd_EN_NULL == MtrCtrlFault_DrFrontMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_FrontAngleAdjust =
          APPL_DriverFaultDetection_IN_Init_e;
        APPL_DriverFaultDetection_DW.FrontTimer = 0U;

        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.FrontSwCmd)
        {
          APPL_DriverFaultDetection_B.FrontTimeOutFlag = ((BOOL)FALSE);
        }
      }
      else if (APPL_DriverFaultDetection_DW.FrontTimer < CAL_MotorMaxRunTime_60s)
      {
        tmp = APPL_DriverFaultDetection_DW.FrontTimer + 1;
        if (tmp > 65535)
        {
          tmp = 65535;
        }

        APPL_DriverFaultDetection_DW.FrontTimer = (INT16U)tmp;
      }
      else
      {
        APPL_DriverFaultDetection_B.FrontTimeOutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* 高度、纵向电机没有命令或计时已到 */
      if ((INT32S)enSeatMoveCmd_EN_NULL != MtrCtrlFault_DrFrontMotorCmd)
      {
        APPL_DriverFaultDetection_DW.is_FrontAngleAdjust =
          APPL_DriverFaultDetection_IN_Action;
        if (APPL_DriverFaultDetection_DW.FrontTimer < CAL_MotorMaxRunTime_60s)
        {
          tmp = APPL_DriverFaultDetection_DW.FrontTimer + 1;
          if (tmp > 65535)
          {
            tmp = 65535;
          }

          APPL_DriverFaultDetection_DW.FrontTimer = (INT16U)tmp;
        }
        else
        {
          APPL_DriverFaultDetection_B.FrontTimeOutFlag = ((BOOL)TRUE);
        }
      }
      else
      {
        /*  按键无效  */
        if (((BOOL)FALSE) == (INT32S)APPL_DriverFaultDetection_B.FrontSwCmd)
        {
          APPL_DriverFaultDetection_B.FrontTimeOutFlag = ((BOOL)FALSE);
        }
      }
    }
  }

  if (APPL_DriverFaultDetection_DW.is_active_c1_APPL_DriverFaultDetection == 0U)
  {
    APPL_DriverFaultDetection_DW.is_active_c1_APPL_DriverFaultDetection = 1U;
    APPL_DriverFaultDetection_DW.is_c1_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_Init_e;
    APPL_DriverFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
      APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_DriverFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
      APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_DriverFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
      APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    APPL_DriverFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
      APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
  }
  else if (APPL_DriverFaultDetection_DW.is_c1_APPL_DriverFaultDetection ==
           APPL_DriverFaultDetection_IN_DSM_SWAdjust)
  {
    /*  crank档 或 不可调节配置  */
    if ((enIgnSts_eCrank == MtrCtrlFault_DrPowerModeStatus) ||
        ((enDrAdjustEnable_EN_DrSixWayMotor != MtrCtrlFault_DrAdjustCfg) &&
         (enDrAdjustEnable_EN_DrTwelveWayMotor != MtrCtrlFault_DrAdjustCfg)))
    {
      APPL_DriverFaultDetection_DW.is_FrontSWProcess =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_DriverFaultDetection_DW.is_BackSWProcess =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_DriverFaultDetection_DW.is_LengthSWProcess =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_DriverFaultDetection_DW.is_HeightSWProcess =
        APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
      APPL_DriverFaultDetection_DW.is_c1_APPL_DriverFaultDetection =
        APPL_DriverFaultDetection_IN_Init_e;
      APPL_DriverFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    }
    else
    {
      if (APPL_DriverFaultDetection_DW.is_HeightSWProcess ==
          APPL_DriverFaultDetection_IN_Disable)
      {
        /*  高度本地开关命令故障处理  */
        if (((INT32S)APPL_DriverFaultDetection_B.HeightSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.HeightSwAdhesionFault)
            && (((BOOL)FALSE) == APPL_DriverFaultDetection_B.HeightMidRelayFault)
            && (((BOOL)FALSE) == APPL_DriverFaultDetection_B.HeightStallFault))
        {
          APPL_DriverFaultDetection_DW.is_HeightSWProcess =
            APPL_DriverFaultDetection_IN_Enable;
          APPL_DriverFaultDetection_B.CurrentHeightSwCmd =
            APPL_DriverFaultDetection_B.HeightSwCmd;
        }
      }
      else if (((INT32S)APPL_DriverFaultDetection_B.HeightSwCmd == ((BOOL)FALSE))
               || (((BOOL)FALSE) !=
                   APPL_DriverFaultDetection_B.HeightSwAdhesionFault) || (((BOOL)
                 TRUE) == APPL_DriverFaultDetection_B.HeightMidRelayFault) ||
               (((BOOL)TRUE) == APPL_DriverFaultDetection_B.HeightStallFault))
      {
        APPL_DriverFaultDetection_DW.is_HeightSWProcess =
          APPL_DriverFaultDetection_IN_Disable;
        APPL_DriverFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
          APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)
          FALSE));
      }
      else
      {
        APPL_DriverFaultDetection_B.CurrentHeightSwCmd =
          APPL_DriverFaultDetection_B.HeightSwCmd;
      }

      if (APPL_DriverFaultDetection_DW.is_LengthSWProcess ==
          APPL_DriverFaultDetection_IN_Disable)
      {
        /*  纵向本地开关命令故障处理  */
        if (((INT32S)APPL_DriverFaultDetection_B.LengthSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.LengthSwAdhesionFault)
            && (((BOOL)FALSE) == APPL_DriverFaultDetection_B.LengthMidRelayFault)
            && (((BOOL)FALSE) == APPL_DriverFaultDetection_B.LengthStallFault))
        {
          APPL_DriverFaultDetection_DW.is_LengthSWProcess =
            APPL_DriverFaultDetection_IN_Enable;
          APPL_DriverFaultDetection_B.CurrentLengthSwCmd =
            APPL_DriverFaultDetection_B.LengthSwCmd;
        }
      }
      else if (((INT32S)APPL_DriverFaultDetection_B.LengthSwCmd == ((BOOL)FALSE))
               || (((BOOL)FALSE) !=
                   APPL_DriverFaultDetection_B.LengthSwAdhesionFault) || (((BOOL)
                 TRUE) == APPL_DriverFaultDetection_B.LengthMidRelayFault) ||
               (((BOOL)TRUE) == APPL_DriverFaultDetection_B.LengthStallFault))
      {
        APPL_DriverFaultDetection_DW.is_LengthSWProcess =
          APPL_DriverFaultDetection_IN_Disable;
        APPL_DriverFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
          APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)
          FALSE));
      }
      else
      {
        APPL_DriverFaultDetection_B.CurrentLengthSwCmd =
          APPL_DriverFaultDetection_B.LengthSwCmd;
      }

      if (APPL_DriverFaultDetection_DW.is_BackSWProcess ==
          APPL_DriverFaultDetection_IN_Disable)
      {
        /*  靠背本地开关命令故障处理  */
        if (((INT32S)APPL_DriverFaultDetection_B.BackSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.BackMidRelayFault) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.BackSwAdhesionFault) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.BackStallFault))
        {
          APPL_DriverFaultDetection_DW.is_BackSWProcess =
            APPL_DriverFaultDetection_IN_Enable;
          APPL_DriverFaultDetection_B.CurrentBackSwCmd =
            APPL_DriverFaultDetection_B.BackSwCmd;
        }
      }
      else if (((INT32S)APPL_DriverFaultDetection_B.BackSwCmd == ((BOOL)FALSE)) ||
               (((BOOL)FALSE) != APPL_DriverFaultDetection_B.BackMidRelayFault) ||
               (((BOOL)TRUE) == APPL_DriverFaultDetection_B.BackSwAdhesionFault)
               || (((BOOL)TRUE) == APPL_DriverFaultDetection_B.BackStallFault))
      {
        APPL_DriverFaultDetection_DW.is_BackSWProcess =
          APPL_DriverFaultDetection_IN_Disable;
        APPL_DriverFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
          APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)
          FALSE));
      }
      else
      {
        APPL_DriverFaultDetection_B.CurrentBackSwCmd =
          APPL_DriverFaultDetection_B.BackSwCmd;
      }

      if (APPL_DriverFaultDetection_DW.is_FrontSWProcess ==
          APPL_DriverFaultDetection_IN_Disable)
      {
        /*  腿托本地开关命令故障处理 && 配置字满足 */
        if (((INT32S)APPL_DriverFaultDetection_B.FrontSwCmd != ((BOOL)FALSE)) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.FrontSwAdhesionFault) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.FrontMidRelayFault) &&
            (((BOOL)FALSE) == APPL_DriverFaultDetection_B.FrontStallFault) &&
            (enDrAdjustEnable_EN_DrTwelveWayMotor == MtrCtrlFault_DrAdjustCfg))
        {
          APPL_DriverFaultDetection_DW.is_FrontSWProcess =
            APPL_DriverFaultDetection_IN_Enable;
          APPL_DriverFaultDetection_B.CurrentFrontSwCmd =
            APPL_DriverFaultDetection_B.FrontSwCmd;
        }
      }
      else if (((INT32S)APPL_DriverFaultDetection_B.FrontSwCmd == ((BOOL)FALSE))
               || (((BOOL)FALSE) !=
                   APPL_DriverFaultDetection_B.FrontSwAdhesionFault) || (((BOOL)
                 TRUE) == APPL_DriverFaultDetection_B.FrontMidRelayFault) ||
               (((BOOL)TRUE) == APPL_DriverFaultDetection_B.FrontStallFault) ||
               (enDrAdjustEnable_EN_DrTwelveWayMotor != MtrCtrlFault_DrAdjustCfg))
      {
        APPL_DriverFaultDetection_DW.is_FrontSWProcess =
          APPL_DriverFaultDetection_IN_Disable;
        APPL_DriverFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
          APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)
          FALSE));
      }
      else
      {
        APPL_DriverFaultDetection_B.CurrentFrontSwCmd =
          APPL_DriverFaultDetection_B.FrontSwCmd;
      }
    }
  }
  else
  {
    /*  非CRANK档位 且非不可调节配置  */
    if ((enIgnSts_eCrank != MtrCtrlFault_DrPowerModeStatus) &&
        ((enDrAdjustEnable_EN_DrSixWayMotor == MtrCtrlFault_DrAdjustCfg) ||
         (enDrAdjustEnable_EN_DrTwelveWayMotor == MtrCtrlFault_DrAdjustCfg)))
    {
      APPL_DriverFaultDetection_DW.is_c1_APPL_DriverFaultDetection =
        APPL_DriverFaultDetection_IN_DSM_SWAdjust;
      APPL_DriverFaultDetection_DW.is_HeightSWProcess =
        APPL_DriverFaultDetection_IN_Disable;
      APPL_DriverFaultDetection_B.CurrentHeightSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_DW.is_LengthSWProcess =
        APPL_DriverFaultDetection_IN_Disable;
      APPL_DriverFaultDetection_B.CurrentLengthSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_DW.is_BackSWProcess =
        APPL_DriverFaultDetection_IN_Disable;
      APPL_DriverFaultDetection_B.CurrentBackSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
      APPL_DriverFaultDetection_DW.is_FrontSWProcess =
        APPL_DriverFaultDetection_IN_Disable;
      APPL_DriverFaultDetection_B.CurrentFrontSwCmd = (enSeatMoveCmd)
        APPL_DriverFaultDetecti_safe_cast_to_enSeatMoveCmd((INT32S)((BOOL)FALSE));
    }
  }
}

/* Model initialize function */
void APPL_DriverFaultDetection_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(APPL_DriverFaultDetection_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &APPL_DriverFaultDetection_B), 0,
                sizeof(B_APPL_DriverFaultDetection_T));

  {
    APPL_DriverFaultDetection_B.CurrentHeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentLengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentBackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentFrontSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
  }

  /* exported global signals */
  MtrCtrlFault_DrBackSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_DrFrontSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_DrHeightSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_DrLengthSwitch = enSeatMoveCmd_EN_NULL;
  MtrCtrlFault_DrPowerModeStatus = enIgnSts_eOff;
  MtrCtrlFault_DrAdjustCfg = enDrAdjustEnable_EN_DrTwelveWayMotor;
  MtrCtrlFault_DrBackHallCnt = ((INT16U)0U);
  MtrCtrlFault_DrBackMotorSize = ((INT16U)0U);
  MtrCtrlFault_DrBackStopPosi = ((INT16U)0U);
  MtrCtrlFault_DrFrontHallCnt = ((INT16U)0U);
  MtrCtrlFault_DrFrontMotorSize = ((INT16U)0U);
  MtrCtrlFault_DrFrontStopPosi = ((INT16U)0U);
  MtrCtrlFault_DrHeightHallCnt = ((INT16U)0U);
  MtrCtrlFault_DrHeightMotorSize = ((INT16U)0U);
  MtrCtrlFault_DrHeightStopPosi = ((INT16U)0U);
  MtrCtrlFault_DrLengthHallCnt = ((INT16U)0U);
  MtrCtrlFault_DrLengthMotorSize = ((INT16U)0U);
  MtrCtrlFault_DrLengthStopPosi = ((INT16U)0U);
  MtrCtrlFault_DrBackBackwardVolt = ((INT8U)0U);
  MtrCtrlFault_DrBackCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_DrBackForwardVolt = ((INT8U)0U);
  MtrCtrlFault_DrBackLearnFlag = ((INT8U)0U);
  MtrCtrlFault_DrBackMotorCmd = ((INT8U)0U);
  MtrCtrlFault_DrBackSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_DrFrontCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_DrFrontDownVolt = ((INT8U)0U);
  MtrCtrlFault_DrFrontLearnFlag = ((INT8U)0U);
  MtrCtrlFault_DrFrontMotorCmd = ((INT8U)0U);
  MtrCtrlFault_DrFrontSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_DrFrontUpVolt = ((INT8U)0U);
  MtrCtrlFault_DrHeightCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_DrHeightDownVolt = ((INT8U)0U);
  MtrCtrlFault_DrHeightLearnFlag = ((INT8U)0U);
  MtrCtrlFault_DrHeightMotorCmd = ((INT8U)0U);
  MtrCtrlFault_DrHeightSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_DrHeightUpVolt = ((INT8U)0U);
  MtrCtrlFault_DrLengthBackwardVolt = ((INT8U)0U);
  MtrCtrlFault_DrLengthCurrentOverFlag = ((INT8U)0U);
  MtrCtrlFault_DrLengthForwardVolt = ((INT8U)0U);
  MtrCtrlFault_DrLengthLearnFlag = ((INT8U)0U);
  MtrCtrlFault_DrLengthMotorCmd = ((INT8U)0U);
  MtrCtrlFault_DrLengthSoftStopCnt = ((INT8U)0U);
  MtrCtrlFault_DrMemoryCfg = ((INT8U)0U);
  MtrCtrlFault_DrMotorSoftStopCntMax = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&APPL_DriverFaultDetection_DW, 0,
                sizeof(DW_APPL_DriverFaultDetection_T));

  {
    INT32U OutTs_e;
    APPL_DriverFaultDetection_DW.is_BackSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_LengthSwitchErrorDeal =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c8_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.HeightSwTimer = 0U;
    APPL_DriverFaultDetection_DW.LengthSwTimer = 0U;
    APPL_DriverFaultDetection_DW.BackSwTimer = 0U;
    APPL_DriverFaultDetection_DW.FrontSwTimer = 0U;
    APPL_DriverFaultDetection_B.HeightSwAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.LengthSwAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.BackSwAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.FrontSwAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.HeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.LengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.BackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.FrontSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.HeightSwUpAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.HeightSwDownAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.LengthSwUpAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.LengthSwDownAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.BackSwUpAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.BackSwDownAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.FrontSwUpAdhesionFault = 0U;
    APPL_DriverFaultDetection_B.FrontSwDownAdhesionFault = 0U;
    APPL_DriverFaultDetection_TimeDiffTs_Init(&OutTs_e);
    APPL_DriverFaultDetection_GetDefTime_Init(&OutTs_e);
    APPL_DriverFaultDetection_DW.is_BackStallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontStallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightStallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_LengthStallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c10_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.HeightStallTimer = 0U;
    APPL_DriverFaultDetection_DW.LengthStallTimer = 0U;
    APPL_DriverFaultDetection_DW.BackStallTimer = 0U;
    APPL_DriverFaultDetection_DW.FrontStallTimer = 0U;
    APPL_DriverFaultDetection_DW.HeightStallNoTimer = 0U;
    APPL_DriverFaultDetection_DW.LengthStallNoTimer = 0U;
    APPL_DriverFaultDetection_DW.BackStallNoTimer = 0U;
    APPL_DriverFaultDetection_DW.FrontStallNoTimer = 0U;
    APPL_DriverFaultDetection_DW.LocalLengthHallCnt = 0U;
    APPL_DriverFaultDetection_DW.LocalHeightHallCnt = 0U;
    APPL_DriverFaultDetection_DW.LocalBackHallCnt = 0U;
    APPL_DriverFaultDetection_DW.LocalFrontHallCnt = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer1 = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer2 = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer3 = 0U;
    APPL_DriverFaultDetection_DW.CurrentOverTimer4 = 0U;
    APPL_DriverFaultDetection_B.HeightStallFault = 0U;
    APPL_DriverFaultDetection_B.LengthStallFault = 0U;
    APPL_DriverFaultDetection_B.BackStallFault = 0U;
    APPL_DriverFaultDetection_B.FrontStallFault = 0U;
    APPL_DriverFaultDetection_DW.is_BackHallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontHallError3 =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightHallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_LengthHallError =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c9_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.is_c9_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.HeightHallTimer = 0U;
    APPL_DriverFaultDetection_DW.LengthHallTimer = 0U;
    APPL_DriverFaultDetection_DW.BackHallTimer = 0U;
    APPL_DriverFaultDetection_DW.FrontHallTimer = 0U;
    APPL_DriverFaultDetection_DW.DrAdj_Dtc_HeatingMat1SC = true;
    APPL_DriverFaultDetection_B.Desc_HeightHallDTC = 0U;
    APPL_DriverFaultDetection_B.Desc_LengthHallDTC = 0U;
    APPL_DriverFaultDetection_B.Desc_BackHallDTC = 0U;
    APPL_DriverFaultDetection_B.Desc_FrontHallDTC = 0U;
    APPL_DriverFaultDetection_B.HeightHallFault = 0U;
    APPL_DriverFaultDetection_B.LengthHallFault = 0U;
    APPL_DriverFaultDetection_B.BackHallFault = 0U;
    APPL_DriverFaultDetection_B.FrontHallFault = 0U;
    APPL_DriverFaultDetection_DW.is_active_c3_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_B.HeightMidRelayFault = 0U;
    APPL_DriverFaultDetection_B.LengthMidRelayFault = 0U;
    APPL_DriverFaultDetection_B.BackMidRelayFault = 0U;
    APPL_DriverFaultDetection_B.FrontMidRelayFault = 0U;
    APPL_DriverFaultDetection_CheckMidRelayFault_Init
      (&APPL_DriverFaultDetection_B.MidRelayFault_n,
       &APPL_DriverFaultDetection_B.MidRelayTimer_e,
       &APPL_DriverFaultDetection_DW.CheckMidRelayFault);
    APPL_DriverFaultDetection_CheckMidRelayFault_Init
      (&APPL_DriverFaultDetection_B.MidRelayFault_f,
       &APPL_DriverFaultDetection_B.MidRelayTimer_pv,
       &APPL_DriverFaultDetection_DW.CheckMidRelayFault1);
    APPL_DriverFaultDetection_CheckMidRelayFault_Init
      (&APPL_DriverFaultDetection_B.MidRelayFault_p,
       &APPL_DriverFaultDetection_B.MidRelayTimer_p,
       &APPL_DriverFaultDetection_DW.CheckMidRelayFault2);
    APPL_DriverFaultDetection_CheckMidRelayFault_Init
      (&APPL_DriverFaultDetection_B.MidRelayFault,
       &APPL_DriverFaultDetection_B.MidRelayTimer,
       &APPL_DriverFaultDetection_DW.CheckMidRelayFault3);
    APPL_DriverFaultDetection_DW.is_BackSoft =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontSoft =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightSoft =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_LengthSoft =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c33_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.HeightSoftStopBufCnt = 0U;
    APPL_DriverFaultDetection_DW.LengthSoftStopBufCnt = 0U;
    APPL_DriverFaultDetection_DW.BackSoftStopBufCnt = 0U;
    APPL_DriverFaultDetection_DW.FrontSoftStopBufCnt = 0U;
    APPL_DriverFaultDetection_B.HeightSoftStopFault = 0U;
    APPL_DriverFaultDetection_B.LengthSoftStopFault = 0U;
    APPL_DriverFaultDetection_B.BackSoftStopFault = 0U;
    APPL_DriverFaultDetection_B.FrontSoftStopFault = 0U;
    APPL_DriverFaultDetection_DW.is_BackAdjust =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontAngleAdjust =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightAdjust =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_VerticalAdjust =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c16_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.BackTimer = 0U;
    APPL_DriverFaultDetection_DW.FrontTimer = 0U;
    APPL_DriverFaultDetection_DW.HeightTimer = 0U;
    APPL_DriverFaultDetection_DW.LengthTimer = 0U;
    APPL_DriverFaultDetection_B.HeightTimeOutFlag = 0U;
    APPL_DriverFaultDetection_B.LengthTimeOutFlag = 0U;
    APPL_DriverFaultDetection_B.BackTimeOutFlag = 0U;
    APPL_DriverFaultDetection_B.FrontTimeOutFlag = 0U;
    APPL_DriverFaultDetection_DW.is_BackSWProcess =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_FrontSWProcess =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_HeightSWProcess =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_LengthSWProcess =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_DW.is_active_c1_APPL_DriverFaultDetection = 0U;
    APPL_DriverFaultDetection_DW.is_c1_APPL_DriverFaultDetection =
      APPL_DriverFaultDetection_IN_NO_ACTIVE_CHILD_l;
    APPL_DriverFaultDetection_B.CurrentHeightSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentLengthSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentBackSwCmd = enSeatMoveCmd_EN_NULL;
    APPL_DriverFaultDetection_B.CurrentFrontSwCmd = enSeatMoveCmd_EN_NULL;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
