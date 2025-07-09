/*
 * File: Appl_VentAdj_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_VentAdj_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 15:00:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_VentAdj_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_VENT_LVL_1_PRECENT
#error The variable for the parameter "D_VENT_LVL_1_PRECENT" is not defined
#endif

#ifndef D_VENT_LVL_2_PRECENT
#error The variable for the parameter "D_VENT_LVL_2_PRECENT" is not defined
#endif

#ifndef D_VENT_LVL_3_PRECENT
#error The variable for the parameter "D_VENT_LVL_3_PRECENT" is not defined
#endif

/* Named constants for Chart: '<S12>/LevelLimit' */
#define Appl_VentAdj_CtrlModel_IN_Default ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_ForbidStatus ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_Run  ((INT8U)3U)

/* Named constants for Chart: '<S16>/StopFunction' */
#define Appl_VentAdj_CtrlModel_IN_Default_l ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_ValidSts ((INT8U)2U)

/* Named constants for Chart: '<S68>/OppositeMessageDeal' */
#define Appl_VentAdj_CtrlModel_IN_HMIInit ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_HMIValid ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_np ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_TboxInit ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_TboxValid ((INT8U)2U)

/* Named constants for Chart: '<S78>/Function' */
#define Appl_VentAdj_CtrlModel_IN_Default_c ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_HeatConflict ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_bo ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_Valid ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_VentilateConflict ((INT8U)3U)

/* Named constants for Chart: '<S19>/Timeout' */
#define Appl_VentAdj_CtrlModel_IN_Default_f ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_m ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_TimeCountStatus ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_TimeoutSts ((INT8U)2U)

/* Named constants for Chart: '<S20>/Timeout' */
#define Appl_VentAdj_CtrlModel_IN_Default_k ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_Init_g ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_f ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_TimeCountStatus_e ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_TimeoutSts_h ((INT8U)2U)

/* Named constants for Chart: '<S21>/Timeout' */
#define Appl_VentAdj_CtrlModel_IN_Default_b ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_Init_o ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_a ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_TimeCountStatus_g ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_TimeoutSts_m ((INT8U)2U)

/* Named constants for Chart: '<S5>/OutputDeal' */
#define Appl_VentAdj_CtrlModel_IN_Default_d ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_FalseSts ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_Init_k ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_ProjectP20 ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_Run_p ((INT8U)2U)
#define Appl_VentAdj_CtrlModel_IN_SuccSts ((INT8U)2U)

/* Named constants for Chart: '<S61>/Deal' */
#define Appl_VentAdj_CtrlModel_IN_Default_i ((INT8U)1U)
#define Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_gp ((INT8U)0U)
#define Appl_VentAdj_CtrlModel_IN_ValidSts_e ((INT8U)2U)

/* Exported block signals */
enVentStopReason VentAdj_DrVentStopReason;/* '<S60>/VentAdj_DrVentStopReason'
                                           * 主驾通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                           */
enVentStopReason VentAdj_PaVentStopReason;/* '<S60>/VentAdj_PaVentStopReason'
                                           * 副驾通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                           */
enVentStopReason VentAdj_ThirdVentStopReason;/* '<S60>/VentAdj_ThirdVentStopReason '
                                              * 三排通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                              */
enVentLvlSts VentAdj_D_SimuIndex_DRVent;/* '<S60>/VentAdj_D_SimuIndex_DRVent'
                                         * 主驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                         */
enVentLvlSts VentAdj_D_SimuIndex_PAVent;/* '<S60>/VentAdj_D_SimuIndex_PAVent'
                                         * 副驾通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                         */
enVentLvlSts VentAdj_D_SimuIndex_ThirdVent;/* '<S60>/VentAdj_D_SimuIndex_ThirdVent'
                                            * 三排通风档位状态:&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                            */
enVentIoCmdLvl VentAdj_DriverDiagCmd;  /* '<S60>/VentAdj_DriverDiagCmd'
                                        * 主驾通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                        */
enVentIoCmdLvl VentAdj_PassengerDiagCmd;/* '<S60>/VentAdj_PassengerDiagCmd'
                                         * 副驾通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                         */
enVentIoCmdLvl VentAdj_ThirdDiagCmd;   /* '<S60>/VentAdj_ThirdDiagCmd'
                                        * 三排通风诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                        */
enVentCmdFault VentAdj_DriverCmdFaultSts;/* '<S60>/VentAdj_DriverCmdFaultSts'
                                          * 主驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                          */
enVentCmdFault VentAdj_DriverCmdFaultSts4DTC;/* '<S60>/VentAdj_DriverCmdFaultSts4DTC'
                                              * 主驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                              */
enVentCmdFault VentAdj_PasCmdFaultSts; /* '<S60>/VentAdj_PasCmdFaultSts'
                                        * 副驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                        */
enVentCmdFault VentAdj_PasCmdFaultSts4DTC;/* '<S60>/VentAdj_PasCmdFaultSts4DTC'
                                           * 副驾通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                           */
enVentCmdFault VentAdj_ThirdCmdFaultSts;/* '<S60>/VentAdj_ThirdCmdFaultSts'
                                         * 三排通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                         */
enVentCmdFault VentAdj_ThirdCmdFaultSts4DTC;/* '<S60>/VentAdj_ThirdCmdFaultSts4DTC'
                                             * 三排通风输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                             */
enProjectType VentAdj_CarType;         /* '<S60>/VentAdj_CarType'
                                        * 车型：C62X、C52X…&#10;0：P20车型&#10;1：BM400车型
                                        */
enPowerModeSts VentAdj_PowerMode;      /* '<S60>/VentAdj_PowerMode'
                                        * 整车电源档位&#10;0 : OFF&#10;1 : ACC&#10;2 : ON&#10;3 : CRANK
                                        */
enFinalPowerMode VentAdj_VoltMode;     /* '<S60>/VentAdj_VoltMode'
                                        * 整车电压模式&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt
                                        */
INT8U VentAdj_3rdHeatFlg;              /* '<S60>/VentAdj_3rdHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_CanDrvVentLvl;           /* '<S60>/VentAdj_CanDrvVentLvl'
                                        * 输出通风等级
                                        */
INT8U VentAdj_CanPasVentLvl;           /* '<S60>/VentAdj_CanPasVentLvl'
                                        * 输出通风等级
                                        */
INT8U VentAdj_CanThirdVentLvl;         /* '<S60>/VentAdj_CanThirdVentLvl'
                                        * 输出通风等级
                                        */
INT8U VentAdj_DrHeatFlg;               /* '<S60>/VentAdj_DrHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_DrVentFlg;               /* '<S60>/VentAdj_DrVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_DriverEnableConfig;      /* '<S60>/VentAdj_DriverEnableConfig'
                                        * 主驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentAdj_DriverHMI_VentMessage;   /* '<S60>/VentAdj_DriverHMI_VentMessage'
                                        * 主驾通风HMI等级报文
                                        */
INT8U VentAdj_DriverTbox_VentMessage;  /* '<S60>/VentAdj_DriverTbox_VentMessage'
                                        * 主驾通风Tbox等级报文
                                        */
INT8U VentAdj_Driver_HMI_HeatMsg;      /* '<S60>/VentAdj_Driver_HMI_HeatMsg'
                                        * 主驾加热HMI报文
                                        */
INT8U VentAdj_Driver_Tbox_HeatMsg;     /* '<S60>/VentAdj_Driver_Tbox_HeatMsg'
                                        * 主驾加热Tbox报文
                                        */
INT8U VentAdj_EngineRunFlag;           /* '<S60>/VentAdj_EngineRunFlag'
                                        * 发动机运行状态
                                        */
INT8U VentAdj_PaHeatFlg;               /* '<S60>/VentAdj_PaHeatFlg'
                                        * 加热使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_PaVentFlg;               /* '<S60>/VentAdj_PaVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_PassengerEnableConfig;   /* '<S60>/VentAdj_PassengerEnableConfig'
                                        * 副驾通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentAdj_PassengerHMI_VentMessage;/* '<S60>/VentAdj_PassengerHMI_VentMessage'
                                        * 副驾通风HMI等级报文
                                        */
INT8U VentAdj_PassengerTbox_VentMessage;/* '<S60>/VentAdj_PassengerTbox_VentMessage'
                                         * 副驾通风Tbox等级报文
                                         */
INT8U VentAdj_Passenger_HMI_HeatMsg;   /* '<S60>/VentAdj_Passenger_HMI_HeatMsg'
                                        * 副驾加热HMI报文
                                        */
INT8U VentAdj_Passenger_Tbox_HeatMsg;  /* '<S60>/VentAdj_Passenger_Tbox_HeatMsg'
                                        * 副驾加热Tbox报文
                                        */
INT8U VentAdj_RecoverDefaultFlag;      /* '<S60>/VentAdj_RecoverDefaultFlag'
                                        * 恢复出厂命令&#10;0：无效；&#10;1：有效
                                        */
INT8U VentAdj_RemoteModeFlag;          /* '<S60>/VentAdj_RemoteModeFlag'
                                        * 通风远程模式状态&#10;0：无远程模式&#10;1：进远程模式
                                        */
INT8U VentAdj_RunMaxTime;              /* '<S60>/VentAdj_RunMaxTime'
                                        * 通风超时时间配置&#10;0：无超时&#10;1-255min
                                        */
INT8U VentAdj_ThirdEnableConfig;       /* '<S60>/VentAdj_ThirdEnableConfig'
                                        * 三排通风使能配置&#10;0:不存在&#10;1：存在
                                        */
INT8U VentAdj_ThirdHMI_VentMessage;    /* '<S60>/VentAdj_ThirdHMI_VentMessage'
                                        * 三排通风HMI等级报文
                                        */
INT8U VentAdj_ThirdTbox_VentMessage;   /* '<S60>/VentAdj_ThirdTbox_VentMessage'
                                        * 三排通风Tbox等级报文
                                        */
INT8U VentAdj_Third_HMI_HeatMsg;       /* '<S60>/VentAdj_Third_HMI_HeatMsg'
                                        * 三排加热HMI报文
                                        */
INT8U VentAdj_Third_Tbox_HeatMsg;      /* '<S60>/VentAdj_Third_Tbox_HeatMsg'
                                        * 三排加热Tbox报文
                                        */
INT8U VentAdj_TimeOutPrm;              /* '<S60>/VentAdj_TimeOutPrm'
                                        * 通风超时使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U VentAdj_VehicleRunFlag;          /* '<S60>/VentAdj_VehicleRunFlag'
                                        * 整车运行状态&#10;0：无&#10;1：运行
                                        */
INT8U VentAdj_VentMsgLostFlag;         /* '<S60>/VentAdj_VentMsgLostFlag'
                                        * 通风报文掉线
                                        */

/* Block signals (default storage) */
B_Appl_VentAdj_CtrlModel_T Appl_VentAdj_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_VentAdj_CtrlModel_T Appl_VentAdj_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_VentAdj_CtrlModel_T Appl_VentAdj_CtrlModel_M_;
RT_MODEL_Appl_VentAdj_CtrlModel_T *const Appl_VentAdj_CtrlModel_M =
  &Appl_VentAdj_CtrlModel_M_;
static void Appl_VentAdj_CtrlModel_MixConflic(INT8U rtu_MixFlg, INT8U rtu_Valid,
  INT8U *rty_OutValid);
static void Appl_VentAdj_CtrlModel_LevelLimitFunction_Init(enVentLvlSts
  *rty_Level, enVentStopReason *rty_StopReason,
  DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_LevelLimitFunction(enVentLvlSts
  rtu_OriginalLevel, INT8U rtu_Error, INT8U rtu_OppositeCmd, enProjectType
  rtu_CarType, INT8U rtu_Vent_CanMessageLostFlag, INT8U
  rtu_Vent_RecoverDefaultFlag, enVentLvlSts *rty_Level, enVentStopReason
  *rty_StopReason, DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_TimeDiffTs_Init(INT32U *rty_OutTs);
static void Appl_VentAdj_CtrlModel_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
  INT32U *rty_OutTs);
static void Appl_VentAdj_CtrlModel_StopFunction_Init(enVentStopReason
  *rty_StopReason, DW_StopFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_StopFunction(enVentStopReason rtu_ComStop,
  INT8U rtu_Timeout, enVentStopReason *rty_StopReason,
  DW_StopFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_DiagnoseFunction_Init(enVentLvlSts *rty_Level,
  enVentType *rty_Type, DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_DiagnoseFunction(INT8U rtu_DiagCommand,
  enVentLvlSts rtu_InLevel, enVentType rtu_CurrentType, enVentLvlSts *rty_Level,
  enVentType *rty_Type, DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_DutyFunction_Init(INT8U *rty_AimDuty);
static void Appl_VentAdj_CtrlModel_DutyFunction(enVentLvlSts rtu_AimLevel, INT8U
  *rty_AimDuty);
static void Appl_VentAdj_CtrlModel_VentRunTypeFunction_Init(enVentType
  *rty_RunType, enVentLvlSts *rty_OutLevel);
static void Appl_VentAdj_CtrlModel_VentRunTypeFunction(INT8U rtu_InLevel,
  enVentLvlSts rtu_PreLevel, enVentType rtu_InType, enVentType *rty_RunType,
  enVentLvlSts *rty_OutLevel);
static void Appl_VentAdj_CtrlModel_LevelAquireFunction_Init(INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_LevelAquireFunction(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, enPowerModeSts rtu_PowerMode, INT8U
  rtu_EngineSts, INT8U rtu_CAN_Message, enVentStopReason rtu_DisableSts, INT8U
  rtu_CAN_Lvl, INT8U rtu_Type, INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_OppositeMessageDeal_Init(INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_OppositeMessageDeal(enProjectType
  rtu_CarTypeCfg, INT8U rtu_RemoteModeFlag, INT8U rtu_HMI_Message, INT8U
  rtu_Tbox_Message, INT8U rtu_HeatCfg, INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_MsgConflictFunction2_Init(INT8U
  *rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_MsgConflictFunction2(INT8U rtu_CarTypeCfg,
  INT8U rtu_HMI_Message, INT8U rtu_Tbox_Message, INT8U rtu_VentValidFlag, INT8U *
  rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T *localDW);
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction_Init(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction(void);
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction1_Init(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction1(void);
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction2_Init(void);
static void Appl_VentAdj_CtrlModel_TimeoutFunction2(void);
static void Appl_VentAdj_CtrlModel_LogicCtrl_Init(void);
static void Appl_VentAdj_CtrlModel_LogicCtrl(void);
static void Appl_VentAdj_CtrlModel_RTE(void);
static void Appl_VentAdj_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_VentAdj_CtrlModel_UpDataInputInfo(void);
static void Appl_VentAdj_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static INT32S Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts(INT32S input);

/* Forward declaration for local functions */
static INT32S Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts_m(INT32S input);

/* Forward declaration for local functions */
static void Appl_VentAdj_CtrlModel_inner_default_LevelAquire(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, enPowerModeSts rtu_PowerMode, INT8U
  rtu_EngineSts, INT8U rtu_CAN_Message, enVentStopReason rtu_DisableSts, INT8U
  rtu_CAN_Lvl, INT8U rtu_Type, INT8U *rty_Level);

/* Output and update for function-call system: '<S6>/MixConflic' */
static void Appl_VentAdj_CtrlModel_MixConflic(INT8U rtu_MixFlg, INT8U rtu_Valid,
  INT8U *rty_OutValid)
{
  if (rtu_MixFlg != 0)
  {
    *rty_OutValid = ((BOOL)FALSE);
  }
  else
  {
    *rty_OutValid = rtu_Valid;
  }
}

/*
 * System initialize for function-call system:
 *    '<S6>/LevelLimitFunction'
 *    '<S6>/LevelLimitFunction1'
 *    '<S6>/LevelLimitFunction2'
 */
static void Appl_VentAdj_CtrlModel_LevelLimitFunction_Init(enVentLvlSts
  *rty_Level, enVentStopReason *rty_StopReason,
  DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c21_Appl_VentAdj_CtrlModel = 0U;
  localDW->is_c21_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD;
  *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;
  *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S6>/LevelLimitFunction'
 *    '<S6>/LevelLimitFunction1'
 *    '<S6>/LevelLimitFunction2'
 */
static void Appl_VentAdj_CtrlModel_LevelLimitFunction(enVentLvlSts
  rtu_OriginalLevel, INT8U rtu_Error, INT8U rtu_OppositeCmd, enProjectType
  rtu_CarType, INT8U rtu_Vent_CanMessageLostFlag, INT8U
  rtu_Vent_RecoverDefaultFlag, enVentLvlSts *rty_Level, enVentStopReason
  *rty_StopReason, DW_LevelLimitFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c21_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c21_Appl_VentAdj_CtrlModel = 1U;
    localDW->is_c21_Appl_VentAdj_CtrlModel = Appl_VentAdj_CtrlModel_IN_Default;
    *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;
  }
  else
  {
    switch (localDW->is_c21_Appl_VentAdj_CtrlModel)
    {
     case Appl_VentAdj_CtrlModel_IN_Default:
      /* 请求工作 */
      if (enVentLvlSts_EN_VENT_LVL_OFF != rtu_OriginalLevel)
      {
        localDW->is_c21_Appl_VentAdj_CtrlModel =
          Appl_VentAdj_CtrlModel_IN_ForbidStatus;
        *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;

        /* 存在故障 */
        if ((INT32S)enVentCmdFault_EN_VENT_FAULT_NONE != rtu_Error)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FAULT;
        }

        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
        }

        /* 恢复出厂 */
        if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
        }

        /* BM400掉线禁能 */
        if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
            (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
        }
      }
      break;

     case Appl_VentAdj_CtrlModel_IN_ForbidStatus:
      /* 无用户请求，可准备下一轮禁能原因检测 */
      if (enVentLvlSts_EN_VENT_LVL_OFF == rtu_OriginalLevel)
      {
        *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
        localDW->is_c21_Appl_VentAdj_CtrlModel =
          Appl_VentAdj_CtrlModel_IN_Default;
        *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;
      }
      else
      {
        /* 无故障
           && 互斥命令无效
           && 无恢复出厂命令
           && （BM400控制报文在线 || 非BM400车型）  */
        if (((INT32S)enVentCmdFault_EN_VENT_FAULT_NONE == rtu_Error) && (((BOOL)
              TRUE) != rtu_OppositeCmd) && (((BOOL)TRUE) !=
             rtu_Vent_RecoverDefaultFlag) && ((enProjectType_EN_PROJECT_BM400 !=
              rtu_CarType) || (((BOOL)FALSE) == rtu_Vent_CanMessageLostFlag)))
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
          localDW->is_c21_Appl_VentAdj_CtrlModel = Appl_VentAdj_CtrlModel_IN_Run;
          *rty_Level = rtu_OriginalLevel;
        }
        else
        {
          /* 存在故障 */
          if ((INT32S)enVentCmdFault_EN_VENT_FAULT_NONE != rtu_Error)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FAULT;
          }

          /* 互斥命令有效 */
          if (((BOOL)TRUE) == rtu_OppositeCmd)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
          }

          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
          }

          /* BM400掉线禁能 */
          if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
              (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
          }
        }
      }
      break;

     default:
      /* 存在故障 */
      if ((INT32S)enVentCmdFault_EN_VENT_FAULT_NONE != rtu_Error)
      {
        *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FAULT;
        localDW->is_c21_Appl_VentAdj_CtrlModel =
          Appl_VentAdj_CtrlModel_IN_ForbidStatus;
        *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;

        /* 存在故障 */
        *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FAULT;

        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
        }

        /* 恢复出厂 */
        if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
        }

        /* BM400掉线禁能 */
        if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
            (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
        }
      }
      else
      {
        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
          localDW->is_c21_Appl_VentAdj_CtrlModel =
            Appl_VentAdj_CtrlModel_IN_ForbidStatus;
          *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;

          /* 存在故障 */
          /* 互斥命令有效 */
          if (((BOOL)TRUE) == rtu_OppositeCmd)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
          }

          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
          }

          /* BM400掉线禁能 */
          if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
              (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
          }
        }
        else
        {
          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
          {
            *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
            localDW->is_c21_Appl_VentAdj_CtrlModel =
              Appl_VentAdj_CtrlModel_IN_ForbidStatus;
            *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;

            /* 存在故障 */
            /* 互斥命令有效 */
            if (((BOOL)TRUE) == rtu_OppositeCmd)
            {
              *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
            }

            /* 恢复出厂 */
            if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
            {
              *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
            }

            /* BM400掉线禁能 */
            if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
                (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
            {
              *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
            }
          }
          else
          {
            /* BM400掉线禁能 */
            if ((((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag) &&
                (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
            {
              *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
              localDW->is_c21_Appl_VentAdj_CtrlModel =
                Appl_VentAdj_CtrlModel_IN_ForbidStatus;
              *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;

              /* 存在故障 */
              /* 互斥命令有效 */
              if (((BOOL)TRUE) == rtu_OppositeCmd)
              {
                *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_CMD;
              }

              /* 恢复出厂 */
              if (((BOOL)TRUE) == rtu_Vent_RecoverDefaultFlag)
              {
                *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_FACTORY;
              }

              /* BM400掉线禁能 */
              if (((BOOL)TRUE) == rtu_Vent_CanMessageLostFlag)
              {
                *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_LOSS;
              }
            }
            else
            {
              *rty_Level = rtu_OriginalLevel;
            }
          }
        }
      }
      break;
    }
  }
}

/* Output and update for function-call system: '<S31>/D_HAL_GET_CUR_MS_TS' */
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS(void)
{
  Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5 = D_HAL_GET_CUR_MS_TS( );
}

/*
 * System initialize for function-call system:
 *    '<S31>/TimeDiffTs'
 *    '<S35>/TimeDiffTs'
 *    '<S39>/TimeDiffTs'
 */
static void Appl_VentAdj_CtrlModel_TimeDiffTs_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S31>/TimeDiffTs'
 *    '<S35>/TimeDiffTs'
 *    '<S39>/TimeDiffTs'
 */
static void Appl_VentAdj_CtrlModel_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
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

/* System initialize for function-call system: '<S6>/TimeoutFunction' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction_Init(void)
{
  INT32U OutTs_m;
  Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_VentAdj_CtrlModel_DW.is_active_c24_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_DW.is_c24_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_m;
  Appl_VentAdj_CtrlModel_DW.Timer_a = 0U;
  Appl_VentAdj_CtrlModel_B.TimeoutFlag_l = 0U;
  Appl_VentAdj_CtrlModel_B.Level_p = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_TimeDiffTs_Init(&OutTs_m);
}

/* Output and update for function-call system: '<S6>/TimeoutFunction' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction(void)
{
  INT32U OutTs_m;
  enVentLvlSts InLevel_prev_e;
  InLevel_prev_e = Appl_VentAdj_CtrlModel_DW.InLevel_start_a;
  Appl_VentAdj_CtrlModel_DW.InLevel_start_a = Appl_VentAdj_CtrlModel_B.InLevel;
  if (Appl_VentAdj_CtrlModel_DW.is_active_c24_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c24_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_DW.is_c24_Appl_VentAdj_CtrlModel =
      Appl_VentAdj_CtrlModel_IN_Default_f;
    Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
  }
  else if (Appl_VentAdj_CtrlModel_DW.is_c24_Appl_VentAdj_CtrlModel ==
           Appl_VentAdj_CtrlModel_IN_Default_f)
  {
    /* 有超时配置
       && 启动加热&&有时间值  */
    if ((((BOOL)TRUE) == Appl_VentAdj_CtrlModel_B.TimeoutPrm) &&
        (enVentLvlSts_EN_VENT_LVL_OFF != Appl_VentAdj_CtrlModel_B.InLevel) &&
        (0U != Appl_VentAdj_CtrlModel_B.MaxTime))
    {
      Appl_VentAdj_CtrlModel_DW.is_c24_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_TimeCountStatus;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
        Appl_VentAdj_CtrlModel_IN_Init;
      Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_VentAdj_CtrlModel_DW.Timer_a =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
    }
  }
  else
  {
    /* 无超时配置 */
    if ((((BOOL)TRUE) != Appl_VentAdj_CtrlModel_B.TimeoutPrm) || (0U ==
         Appl_VentAdj_CtrlModel_B.MaxTime))
    {
      switch (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d)
      {
       case Appl_VentAdj_CtrlModel_IN_Init:
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_VentAdj_CtrlModel_DW.Timer_a =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        break;

       case Appl_VentAdj_CtrlModel_IN_TimeoutSts:
        Appl_VentAdj_CtrlModel_DW.Timer_a = 0U;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_m;
        break;
      }

      Appl_VentAdj_CtrlModel_B.TimeoutFlag_l = ((BOOL)FALSE);
      Appl_VentAdj_CtrlModel_DW.is_c24_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_Default_f;
      Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
    }
    else if (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d ==
             Appl_VentAdj_CtrlModel_IN_Init)
    {
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_VentAdj_CtrlModel_TimeDiffTs(Appl_VentAdj_CtrlModel_DW.Timer_a,
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5, &OutTs_m);
      if (OutTs_m >= Appl_VentAdj_CtrlModel_B.MaxTime)
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_VentAdj_CtrlModel_DW.Timer_a =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
        Appl_VentAdj_CtrlModel_B.TimeoutFlag_l = ((BOOL)TRUE);
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
          Appl_VentAdj_CtrlModel_IN_TimeoutSts;
        Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
      }
      else if ((InLevel_prev_e != Appl_VentAdj_CtrlModel_DW.InLevel_start_a) &&
               (InLevel_prev_e == enVentLvlSts_EN_VENT_LVL_OFF))
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_VentAdj_CtrlModel_DW.Timer_a =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
          Appl_VentAdj_CtrlModel_IN_Init;
        Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_VentAdj_CtrlModel_DW.Timer_a =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
      }
    }
    else if ((InLevel_prev_e != Appl_VentAdj_CtrlModel_DW.InLevel_start_a) &&
             (InLevel_prev_e == enVentLvlSts_EN_VENT_LVL_OFF))
    {
      Appl_VentAdj_CtrlModel_DW.Timer_a = 0U;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_d =
        Appl_VentAdj_CtrlModel_IN_Init;
      Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_VentAdj_CtrlModel_DW.Timer_a =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b5;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_p = Appl_VentAdj_CtrlModel_B.InLevel;
    }
  }
}

/* Output and update for function-call system: '<S35>/D_HAL_GET_CUR_MS_TS' */
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a(void)
{
  Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S6>/TimeoutFunction1' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction1_Init(void)
{
  INT32U OutTs_o;
  Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_f;
  Appl_VentAdj_CtrlModel_DW.is_active_c5_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_DW.is_c5_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_f;
  Appl_VentAdj_CtrlModel_DW.Timer_n = 0U;
  Appl_VentAdj_CtrlModel_B.TimeoutFlag_h = 0U;
  Appl_VentAdj_CtrlModel_B.Level_ip = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_TimeDiffTs_Init(&OutTs_o);
}

/* Output and update for function-call system: '<S6>/TimeoutFunction1' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction1(void)
{
  INT32U OutTs_o;
  enVentLvlSts InLevel_prev_f;
  InLevel_prev_f = Appl_VentAdj_CtrlModel_DW.InLevel_start_n;
  Appl_VentAdj_CtrlModel_DW.InLevel_start_n = Appl_VentAdj_CtrlModel_B.InLevel_f;
  if (Appl_VentAdj_CtrlModel_DW.is_active_c5_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c5_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_DW.is_c5_Appl_VentAdj_CtrlModel =
      Appl_VentAdj_CtrlModel_IN_Default_k;
    Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
  }
  else if (Appl_VentAdj_CtrlModel_DW.is_c5_Appl_VentAdj_CtrlModel ==
           Appl_VentAdj_CtrlModel_IN_Default_k)
  {
    /* 有超时配置
       && 启动加热&&有时间值  */
    if ((((BOOL)TRUE) == Appl_VentAdj_CtrlModel_B.TimeoutPrm_b) &&
        (enVentLvlSts_EN_VENT_LVL_OFF != Appl_VentAdj_CtrlModel_B.InLevel_f) &&
        (0U != Appl_VentAdj_CtrlModel_B.MaxTime_h))
    {
      Appl_VentAdj_CtrlModel_DW.is_c5_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_TimeCountStatus_e;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
        Appl_VentAdj_CtrlModel_IN_Init_g;
      Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
      Appl_VentAdj_CtrlModel_DW.Timer_n =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
    }
  }
  else
  {
    /* 无超时配置 */
    if ((((BOOL)TRUE) != Appl_VentAdj_CtrlModel_B.TimeoutPrm_b) || (0U ==
         Appl_VentAdj_CtrlModel_B.MaxTime_h))
    {
      switch (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m)
      {
       case Appl_VentAdj_CtrlModel_IN_Init_g:
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
        Appl_VentAdj_CtrlModel_DW.Timer_n =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_f;
        break;

       case Appl_VentAdj_CtrlModel_IN_TimeoutSts_h:
        Appl_VentAdj_CtrlModel_DW.Timer_n = 0U;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_f;
        break;
      }

      Appl_VentAdj_CtrlModel_B.TimeoutFlag_h = ((BOOL)FALSE);
      Appl_VentAdj_CtrlModel_DW.is_c5_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_Default_k;
      Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
    }
    else if (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m ==
             Appl_VentAdj_CtrlModel_IN_Init_g)
    {
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
      Appl_VentAdj_CtrlModel_TimeDiffTs(Appl_VentAdj_CtrlModel_DW.Timer_n,
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b, &OutTs_o);
      if (OutTs_o >= Appl_VentAdj_CtrlModel_B.MaxTime_h)
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
        Appl_VentAdj_CtrlModel_DW.Timer_n =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
        Appl_VentAdj_CtrlModel_B.TimeoutFlag_h = ((BOOL)TRUE);
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
          Appl_VentAdj_CtrlModel_IN_TimeoutSts_h;
        Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
      }
      else if ((InLevel_prev_f != Appl_VentAdj_CtrlModel_DW.InLevel_start_n) &&
               (InLevel_prev_f == enVentLvlSts_EN_VENT_LVL_OFF))
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
        Appl_VentAdj_CtrlModel_DW.Timer_n =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
          Appl_VentAdj_CtrlModel_IN_Init_g;
        Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
        Appl_VentAdj_CtrlModel_DW.Timer_n =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
      }
    }
    else if ((InLevel_prev_f != Appl_VentAdj_CtrlModel_DW.InLevel_start_n) &&
             (InLevel_prev_f == enVentLvlSts_EN_VENT_LVL_OFF))
    {
      Appl_VentAdj_CtrlModel_DW.Timer_n = 0U;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus_m =
        Appl_VentAdj_CtrlModel_IN_Init_g;
      Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_a();
      Appl_VentAdj_CtrlModel_DW.Timer_n =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_b;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_ip = Appl_VentAdj_CtrlModel_B.InLevel_f;
    }
  }
}

/* Output and update for function-call system: '<S39>/D_HAL_GET_CUR_MS_TS' */
static void Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa(void)
{
  Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S6>/TimeoutFunction2' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction2_Init(void)
{
  INT32U OutTs;
  Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_a;
  Appl_VentAdj_CtrlModel_DW.is_active_c19_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_DW.is_c19_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_a;
  Appl_VentAdj_CtrlModel_DW.Timer = 0U;
  Appl_VentAdj_CtrlModel_B.TimeoutFlag = 0U;
  Appl_VentAdj_CtrlModel_B.Level_o = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_TimeDiffTs_Init(&OutTs);
}

/* Output and update for function-call system: '<S6>/TimeoutFunction2' */
static void Appl_VentAdj_CtrlModel_TimeoutFunction2(void)
{
  INT32U OutTs;
  enVentLvlSts InLevel_prev;
  InLevel_prev = Appl_VentAdj_CtrlModel_DW.InLevel_start;
  Appl_VentAdj_CtrlModel_DW.InLevel_start = Appl_VentAdj_CtrlModel_B.InLevel_j;
  if (Appl_VentAdj_CtrlModel_DW.is_active_c19_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c19_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_DW.is_c19_Appl_VentAdj_CtrlModel =
      Appl_VentAdj_CtrlModel_IN_Default_b;
    Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
  }
  else if (Appl_VentAdj_CtrlModel_DW.is_c19_Appl_VentAdj_CtrlModel ==
           Appl_VentAdj_CtrlModel_IN_Default_b)
  {
    /* 有超时配置
       && 启动加热&&有时间值  */
    if ((((BOOL)TRUE) == Appl_VentAdj_CtrlModel_B.TimeoutPrm_o) &&
        (enVentLvlSts_EN_VENT_LVL_OFF != Appl_VentAdj_CtrlModel_B.InLevel_j) &&
        (0U != Appl_VentAdj_CtrlModel_B.MaxTime_k))
    {
      Appl_VentAdj_CtrlModel_DW.is_c19_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_TimeCountStatus_g;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
        Appl_VentAdj_CtrlModel_IN_Init_o;
      Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
      Appl_VentAdj_CtrlModel_DW.Timer =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
    }
  }
  else
  {
    /* 无超时配置 */
    if ((((BOOL)TRUE) != Appl_VentAdj_CtrlModel_B.TimeoutPrm_o) || (0U ==
         Appl_VentAdj_CtrlModel_B.MaxTime_k))
    {
      switch (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus)
      {
       case Appl_VentAdj_CtrlModel_IN_Init_o:
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
        Appl_VentAdj_CtrlModel_DW.Timer =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_a;
        break;

       case Appl_VentAdj_CtrlModel_IN_TimeoutSts_m:
        Appl_VentAdj_CtrlModel_DW.Timer = 0U;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_a;
        break;
      }

      Appl_VentAdj_CtrlModel_B.TimeoutFlag = ((BOOL)FALSE);
      Appl_VentAdj_CtrlModel_DW.is_c19_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_Default_b;
      Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
    }
    else if (Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus ==
             Appl_VentAdj_CtrlModel_IN_Init_o)
    {
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
      Appl_VentAdj_CtrlModel_TimeDiffTs(Appl_VentAdj_CtrlModel_DW.Timer,
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS, &OutTs);
      if (OutTs >= Appl_VentAdj_CtrlModel_B.MaxTime_k)
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
        Appl_VentAdj_CtrlModel_DW.Timer =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
        Appl_VentAdj_CtrlModel_B.TimeoutFlag = ((BOOL)TRUE);
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_VentAdj_CtrlModel_IN_TimeoutSts_m;
        Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
      }
      else if ((InLevel_prev != Appl_VentAdj_CtrlModel_DW.InLevel_start) &&
               (InLevel_prev == enVentLvlSts_EN_VENT_LVL_OFF))
      {
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
        Appl_VentAdj_CtrlModel_DW.Timer =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
        Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_VentAdj_CtrlModel_IN_Init_o;
        Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
        Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
        Appl_VentAdj_CtrlModel_DW.Timer =
          Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
      }
    }
    else if ((InLevel_prev != Appl_VentAdj_CtrlModel_DW.InLevel_start) &&
             (InLevel_prev == enVentLvlSts_EN_VENT_LVL_OFF))
    {
      Appl_VentAdj_CtrlModel_DW.Timer = 0U;
      Appl_VentAdj_CtrlModel_DW.is_TimeCountStatus =
        Appl_VentAdj_CtrlModel_IN_Init_o;
      Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
      Appl_VentAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_aa();
      Appl_VentAdj_CtrlModel_DW.Timer =
        Appl_VentAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
    }
    else
    {
      Appl_VentAdj_CtrlModel_B.Level_o = Appl_VentAdj_CtrlModel_B.InLevel_j;
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S6>/StopFunction'
 *    '<S6>/StopFunction1'
 *    '<S6>/StopFunction2'
 */
static void Appl_VentAdj_CtrlModel_StopFunction_Init(enVentStopReason
  *rty_StopReason, DW_StopFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c12_Appl_VentAdj_CtrlModel = 0U;
  localDW->is_c12_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o;
  *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S6>/StopFunction'
 *    '<S6>/StopFunction1'
 *    '<S6>/StopFunction2'
 */
static void Appl_VentAdj_CtrlModel_StopFunction(enVentStopReason rtu_ComStop,
  INT8U rtu_Timeout, enVentStopReason *rty_StopReason,
  DW_StopFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c12_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c12_Appl_VentAdj_CtrlModel = 1U;
    localDW->is_c12_Appl_VentAdj_CtrlModel = Appl_VentAdj_CtrlModel_IN_Default_l;
  }
  else if (localDW->is_c12_Appl_VentAdj_CtrlModel ==
           Appl_VentAdj_CtrlModel_IN_Default_l)
  {
    /* 无通用限制
       &&超时限制有效  */
    if ((enVentStopReason_EN_VENT_STOP_R_NONE == rtu_ComStop) && (((BOOL)TRUE) ==
         rtu_Timeout))
    {
      localDW->is_c12_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_ValidSts;
      *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_TIME;
    }
    else
    {
      *rty_StopReason = rtu_ComStop;
    }
  }
  else
  {
    /* 无超时限制 */
    if (((BOOL)FALSE) == rtu_Timeout)
    {
      localDW->is_c12_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_Default_l;
    }
    else
    {
      *rty_StopReason = enVentStopReason_EN_VENT_STOP_R_TIME;
    }
  }
}

static INT32S Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enVentLvlSts (EN_VENT_LVL_OFF) */
  y = 0;
  if ((input >= 0) && (input <= 3))
  {
    /* Set output value to input value if it is a member of enVentLvlSts */
    y = input;
  }

  return y;
}

/*
 * System initialize for function-call system:
 *    '<S6>/DiagnoseFunction'
 *    '<S6>/DiagnoseFunction1'
 *    '<S6>/DiagnoseFunction2'
 */
static void Appl_VentAdj_CtrlModel_DiagnoseFunction_Init(enVentLvlSts *rty_Level,
  enVentType *rty_Type, DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c13_Appl_VentAdj_CtrlModel = 0U;
  *rty_Level = enVentLvlSts_EN_VENT_LVL_OFF;
  *rty_Type = enVentType_EN_VENT_TYPE_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S6>/DiagnoseFunction'
 *    '<S6>/DiagnoseFunction1'
 *    '<S6>/DiagnoseFunction2'
 */
static void Appl_VentAdj_CtrlModel_DiagnoseFunction(INT8U rtu_DiagCommand,
  enVentLvlSts rtu_InLevel, enVentType rtu_CurrentType, enVentLvlSts *rty_Level,
  enVentType *rty_Type, DW_DiagnoseFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c13_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c13_Appl_VentAdj_CtrlModel = 1U;

    /*  无诊断指令  */
    if ((0 == rtu_DiagCommand) || (rtu_DiagCommand > 4))
    {
      *rty_Level = rtu_InLevel;
      *rty_Type = rtu_CurrentType;
    }
    else
    {
      *rty_Level = (enVentLvlSts)
        Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts(rtu_DiagCommand - 1);
      *rty_Type = enVentType_EN_VENT_TYPE_DIAG;
    }
  }
  else
  {
    /*  无诊断指令  */
    if ((0 == rtu_DiagCommand) || (rtu_DiagCommand > 4))
    {
      *rty_Level = rtu_InLevel;
      *rty_Type = rtu_CurrentType;
    }
    else
    {
      *rty_Level = (enVentLvlSts)
        Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts(rtu_DiagCommand - 1);
      *rty_Type = enVentType_EN_VENT_TYPE_DIAG;
    }
  }
}

/* System initialize for function-call system: '<S7>/DutyFunction' */
static void Appl_VentAdj_CtrlModel_DutyFunction_Init(INT8U *rty_AimDuty)
{
  *rty_AimDuty = 0U;
}

/* Output and update for function-call system: '<S7>/DutyFunction' */
static void Appl_VentAdj_CtrlModel_DutyFunction(enVentLvlSts rtu_AimLevel, INT8U
  *rty_AimDuty)
{
  *rty_AimDuty = 100U;

  /*  通风1档  */
  if (enVentLvlSts_EN_VENT_LVL_1 == rtu_AimLevel)
  {
    *rty_AimDuty = ((INT8U)D_VENT_LVL_1_PRECENT);
  }

  /*  通风2档  */
  if (enVentLvlSts_EN_VENT_LVL_2 == rtu_AimLevel)
  {
    *rty_AimDuty = ((INT8U)D_VENT_LVL_2_PRECENT);
  }

  /*  通风3档  */
  if (enVentLvlSts_EN_VENT_LVL_3 == rtu_AimLevel)
  {
    *rty_AimDuty = ((INT8U)D_VENT_LVL_3_PRECENT);
  }
}

static INT32S Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts_m(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enVentLvlSts (EN_VENT_LVL_OFF) */
  y = 0;
  if ((input >= 0) && (input <= 3))
  {
    /* Set output value to input value if it is a member of enVentLvlSts */
    y = input;
  }

  return y;
}

/* System initialize for function-call system: '<S8>/VentRunTypeFunction' */
static void Appl_VentAdj_CtrlModel_VentRunTypeFunction_Init(enVentType
  *rty_RunType, enVentLvlSts *rty_OutLevel)
{
  *rty_RunType = enVentType_EN_VENT_TYPE_NONE;
  *rty_OutLevel = enVentLvlSts_EN_VENT_LVL_OFF;
}

/* Output and update for function-call system: '<S8>/VentRunTypeFunction' */
static void Appl_VentAdj_CtrlModel_VentRunTypeFunction(INT8U rtu_InLevel,
  enVentLvlSts rtu_PreLevel, enVentType rtu_InType, enVentType *rty_RunType,
  enVentLvlSts *rty_OutLevel)
{
  *rty_OutLevel = rtu_PreLevel;

  /*  有效档位  */
  if (rtu_InLevel <= (INT32S)enVentLvlSts_EN_VENT_LVL_3)
  {
    *rty_RunType = rtu_InType;
    *rty_OutLevel = (enVentLvlSts)
      Appl_VentAdj_CtrlModel_safe_cast_to_enVentLvlSts_m(rtu_InLevel);
  }

  /*  通风档位关闭  */
  if (rtu_InLevel == (INT32S)enVentLvlSts_EN_VENT_LVL_OFF)
  {
    *rty_RunType = enVentType_EN_VENT_TYPE_NONE;
  }
}

/* Function for Chart: '<S45>/LevelAquireFunction' */
static void Appl_VentAdj_CtrlModel_inner_default_LevelAquire(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, enPowerModeSts rtu_PowerMode, INT8U
  rtu_EngineSts, INT8U rtu_CAN_Message, enVentStopReason rtu_DisableSts, INT8U
  rtu_CAN_Lvl, INT8U rtu_Type, INT8U *rty_Level)
{
  INT8U TempMsg;
  BOOL StopFlag;
  INT32S tmp;
  BOOL guard1 = false;

  /* 加热功能禁能
     || OFF 电
     || 发动机不在运行中 */
  if ((enVentStopReason_EN_VENT_STOP_R_NONE != rtu_DisableSts) || (((BOOL)FALSE)
       == rtu_EnableCfg) || (enPowerModeSts_EN_OFF == rtu_PowerMode) || (((BOOL)
        TRUE) != rtu_EngineSts))
  {
    *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_OFF;
    StopFlag = ((BOOL)TRUE);
  }
  else
  {
    StopFlag = ((BOOL)FALSE);
  }

  if (StopFlag == ((BOOL)FALSE))
  {
    guard1 = false;
    if (enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg)
    {
      /*  一键开启 且为Hmi控制  */
      if ((5 == rtu_CAN_Message) && (rtu_Type == 0))
      {
        tmp = rtu_CAN_Lvl + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        *rty_Level = (INT8U)tmp;
      }
      else if (4 == rtu_CAN_Message)
      {
        *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_OFF;
      }
      else
      {
        tmp = rtu_CAN_Message + 7;
        if (tmp > 255)
        {
          tmp = 255;
        }

        TempMsg = (INT8U)tmp;
        guard1 = true;
      }
    }
    else if (1 != rtu_CAN_Message)
    {
      TempMsg = rtu_CAN_Message;
      guard1 = true;
    }
    else
    {
      *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_OFF;
    }

    if (guard1)
    {
      if ((7 < TempMsg) && (11 > TempMsg))
      {
        switch (TempMsg)
        {
         case 8:
          *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_1;
          break;

         case 9:
          *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_2;
          break;

         default:
          *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_3;
          break;
        }
      }
      else
      {
        *rty_Level = (INT8U)0xFF;
      }
    }
  }
  else
  {
    *rty_Level = (INT8U)enVentLvlSts_EN_VENT_LVL_OFF;
  }
}

/*
 * System initialize for function-call system:
 *    '<S8>/LevelAquireFunction'
 *    '<S8>/LevelAquireFunction3'
 *    '<S8>/LevelAquireFunction1'
 *    '<S8>/LevelAquireFunction4'
 *    '<S8>/LevelAquireFunction2'
 *    '<S8>/LevelAquireFunction5'
 */
static void Appl_VentAdj_CtrlModel_LevelAquireFunction_Init(INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c27_Appl_VentAdj_CtrlModel = 0U;
  *rty_Level = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S8>/LevelAquireFunction'
 *    '<S8>/LevelAquireFunction3'
 *    '<S8>/LevelAquireFunction1'
 *    '<S8>/LevelAquireFunction4'
 *    '<S8>/LevelAquireFunction2'
 *    '<S8>/LevelAquireFunction5'
 */
static void Appl_VentAdj_CtrlModel_LevelAquireFunction(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, enPowerModeSts rtu_PowerMode, INT8U
  rtu_EngineSts, INT8U rtu_CAN_Message, enVentStopReason rtu_DisableSts, INT8U
  rtu_CAN_Lvl, INT8U rtu_Type, INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c27_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c27_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_inner_default_LevelAquire(rtu_EnableCfg,
      rtu_CarTypeCfg, rtu_PowerMode, rtu_EngineSts, rtu_CAN_Message,
      rtu_DisableSts, rtu_CAN_Lvl, rtu_Type, rty_Level);
  }
  else
  {
    Appl_VentAdj_CtrlModel_inner_default_LevelAquire(rtu_EnableCfg,
      rtu_CarTypeCfg, rtu_PowerMode, rtu_EngineSts, rtu_CAN_Message,
      rtu_DisableSts, rtu_CAN_Lvl, rtu_Type, rty_Level);
  }
}

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_VentAdj_CtrlModel_LogicCtrl_Init(void)
{
  enVentLvlSts OutLevel;
  enVentType Type_hk;
  INT8U AimDuty;
  Appl_VentAdj_CtrlModel_DW.is_active_c3_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_VentRunTypeFunction_Init
    (&Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_fi,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_l,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction3);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_k,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction1);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_d,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction4);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_f,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction2);
  Appl_VentAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_e,
     &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction5);
  Appl_VentAdj_CtrlModel_DW.is_active_c2_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_B.DrVentStopReason =
    enVentStopReason_EN_VENT_STOP_R_NONE;
  Appl_VentAdj_CtrlModel_B.ThirdHeatStopReason =
    enVentStopReason_EN_VENT_STOP_R_NONE;
  Appl_VentAdj_CtrlModel_B.PaVentStopReason =
    enVentStopReason_EN_VENT_STOP_R_NONE;
  Appl_VentAdj_CtrlModel_B.DiagDrVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.DiagPaVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.VentDriverRunType = enVentType_EN_VENT_TYPE_NONE;
  Appl_VentAdj_CtrlModel_B.VentPassengerRunType = enVentType_EN_VENT_TYPE_NONE;
  Appl_VentAdj_CtrlModel_B.VentThirdRunType = enVentType_EN_VENT_TYPE_NONE;
  Appl_VentAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_h, &Appl_VentAdj_CtrlModel_B.StopReason_g,
     &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction);
  Appl_VentAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_c, &Appl_VentAdj_CtrlModel_B.StopReason_lr,
     &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction1);
  Appl_VentAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_VentAdj_CtrlModel_B.Level_b, &Appl_VentAdj_CtrlModel_B.StopReason_nd,
     &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction2);
  Appl_VentAdj_CtrlModel_TimeoutFunction_Init();
  Appl_VentAdj_CtrlModel_TimeoutFunction1_Init();
  Appl_VentAdj_CtrlModel_TimeoutFunction2_Init();
  Appl_VentAdj_CtrlModel_StopFunction_Init
    (&Appl_VentAdj_CtrlModel_B.StopReason_l,
     &Appl_VentAdj_CtrlModel_DW.StopFunction);
  Appl_VentAdj_CtrlModel_StopFunction_Init
    (&Appl_VentAdj_CtrlModel_B.StopReason_n,
     &Appl_VentAdj_CtrlModel_DW.StopFunction1);
  Appl_VentAdj_CtrlModel_StopFunction_Init(&Appl_VentAdj_CtrlModel_B.StopReason,
    &Appl_VentAdj_CtrlModel_DW.StopFunction2);
  Appl_VentAdj_CtrlModel_DiagnoseFunction_Init(&OutLevel, &Type_hk,
    &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction);
  Appl_VentAdj_CtrlModel_DiagnoseFunction_Init(&OutLevel, &Type_hk,
    &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction1);
  Appl_VentAdj_CtrlModel_DiagnoseFunction_Init(&OutLevel, &Type_hk,
    &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction2);
  Appl_VentAdj_CtrlModel_DW.is_CANOutputDeal = 0;
  Appl_VentAdj_CtrlModel_DW.is_Drv = 0;
  Appl_VentAdj_CtrlModel_DW.is_Pas = 0;
  Appl_VentAdj_CtrlModel_DW.is_Treble = 0;
  Appl_VentAdj_CtrlModel_DW.is_DrvErr = 0;
  Appl_VentAdj_CtrlModel_DW.is_PasErr = 0;
  Appl_VentAdj_CtrlModel_DW.is_TrebleErr = 0;
  Appl_VentAdj_CtrlModel_DW.is_active_c14_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_DW.LocalDrRunState = 0U;
  Appl_VentAdj_CtrlModel_DW.LocalPaRunState = 0U;
  Appl_VentAdj_CtrlModel_DW.Local3rdRunState = 0U;
  Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
  Appl_VentAdj_CtrlModel_B.OutDrRunState = 0U;
  Appl_VentAdj_CtrlModel_B.OutPaRunState = 0U;
  Appl_VentAdj_CtrlModel_B.Out3rdRunState = 0U;
  Appl_VentAdj_CtrlModel_DutyFunction_Init(&AimDuty);
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_VentAdj_CtrlModel_LogicCtrl(void)
{
  INT8U LocalDriverHeatValid;
  INT8U LocalPassengerHeatValid;
  enVentType rtb_OrgVentDriverRunType;
  enVentType rtb_OrgVentPassengerRunType;
  enVentLvlSts OutLevel;
  INT8U Switch;
  if (Appl_VentAdj_CtrlModel_DW.is_active_c3_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c3_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
      Appl_VentAdj_CtrlModel_B.DrvVentFlg, VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.DriverHMI_VentMessage, VentAdj_DrVentStopReason,
      VentAdj_CanDrvVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_fi,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_fi,
      Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    rtb_OrgVentDriverRunType = Appl_VentAdj_CtrlModel_B.RunType;
    Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
        Appl_VentAdj_CtrlModel_B.DrvVentFlg, VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.DriverTbox_VentMessage,
        VentAdj_DrVentStopReason, VentAdj_CanDrvVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_l,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction3);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_l,
         Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      rtb_OrgVentDriverRunType = Appl_VentAdj_CtrlModel_B.RunType;
      Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = OutLevel;
    }

    Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
      Appl_VentAdj_CtrlModel_B.PaVentFlg, VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.PassengerHMI_VentMessage,
      VentAdj_PaVentStopReason, VentAdj_CanPasVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_k,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction1);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_k,
      Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    rtb_OrgVentPassengerRunType = Appl_VentAdj_CtrlModel_B.RunType;
    Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
        Appl_VentAdj_CtrlModel_B.PaVentFlg, VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.PassengerTbox_VentMessage,
        VentAdj_PaVentStopReason, VentAdj_CanPasVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_d,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction4);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_d,
         Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      rtb_OrgVentPassengerRunType = Appl_VentAdj_CtrlModel_B.RunType;
      Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = OutLevel;
    }

    Appl_VentAdj_CtrlModel_LevelAquireFunction(VentAdj_ThirdEnableConfig,
      VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.ThirdHMI_VentMessage, VentAdj_ThirdVentStopReason,
      VentAdj_CanThirdVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_f,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction2);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_f,
      Appl_VentAdj_CtrlModel_B.Original3rdVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction(VentAdj_ThirdEnableConfig,
        VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.ThirdTbox_VentMessage,
        VentAdj_ThirdVentStopReason, VentAdj_CanThirdVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_e,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction5);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_e,
         Appl_VentAdj_CtrlModel_B.Original3rdVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = OutLevel;
    }
  }
  else
  {
    Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
      Appl_VentAdj_CtrlModel_B.DrvVentFlg, VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.DriverHMI_VentMessage, VentAdj_DrVentStopReason,
      VentAdj_CanDrvVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_fi,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_fi,
      Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    rtb_OrgVentDriverRunType = Appl_VentAdj_CtrlModel_B.RunType;
    Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
        Appl_VentAdj_CtrlModel_B.DrvVentFlg, VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.DriverTbox_VentMessage,
        VentAdj_DrVentStopReason, VentAdj_CanDrvVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_l,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction3);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_l,
         Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      rtb_OrgVentDriverRunType = Appl_VentAdj_CtrlModel_B.RunType;
      Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = OutLevel;
    }

    Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
      Appl_VentAdj_CtrlModel_B.PaVentFlg, VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.PassengerHMI_VentMessage,
      VentAdj_PaVentStopReason, VentAdj_CanPasVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_k,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction1);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_k,
      Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    rtb_OrgVentPassengerRunType = Appl_VentAdj_CtrlModel_B.RunType;
    Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction((INT8U)
        Appl_VentAdj_CtrlModel_B.PaVentFlg, VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.PassengerTbox_VentMessage,
        VentAdj_PaVentStopReason, VentAdj_CanPasVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_d,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction4);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_d,
         Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      rtb_OrgVentPassengerRunType = Appl_VentAdj_CtrlModel_B.RunType;
      Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = OutLevel;
    }

    Appl_VentAdj_CtrlModel_LevelAquireFunction(VentAdj_ThirdEnableConfig,
      VentAdj_CarType, VentAdj_PowerMode,
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
      Appl_VentAdj_CtrlModel_B.ThirdHMI_VentMessage, VentAdj_ThirdVentStopReason,
      VentAdj_CanThirdVentLvl, (INT8U)((BOOL)FALSE),
      &Appl_VentAdj_CtrlModel_B.Level_f,
      &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction2);
    Appl_VentAdj_CtrlModel_VentRunTypeFunction(Appl_VentAdj_CtrlModel_B.Level_f,
      Appl_VentAdj_CtrlModel_B.Original3rdVentLevel, enVentType_EN_VENT_TYPE_HMI,
      &Appl_VentAdj_CtrlModel_B.RunType, &OutLevel);
    Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = OutLevel;
    if (((BOOL)TRUE) == VentAdj_RemoteModeFlag)
    {
      Appl_VentAdj_CtrlModel_LevelAquireFunction(VentAdj_ThirdEnableConfig,
        VentAdj_CarType, VentAdj_PowerMode,
        Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag,
        Appl_VentAdj_CtrlModel_B.ThirdTbox_VentMessage,
        VentAdj_ThirdVentStopReason, VentAdj_CanThirdVentLvl, (INT8U)((BOOL)TRUE),
        &Appl_VentAdj_CtrlModel_B.Level_e,
        &Appl_VentAdj_CtrlModel_DW.LevelAquireFunction5);
      Appl_VentAdj_CtrlModel_VentRunTypeFunction
        (Appl_VentAdj_CtrlModel_B.Level_e,
         Appl_VentAdj_CtrlModel_B.Original3rdVentLevel,
         enVentType_EN_VENT_TYPE_TBOX, &Appl_VentAdj_CtrlModel_B.RunType,
         &OutLevel);
      Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = OutLevel;
    }
  }

  if (Appl_VentAdj_CtrlModel_DW.is_active_c2_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c2_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Driver_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.DriverHeatValid, &Switch);
    LocalDriverHeatValid = Switch;
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Passenger_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.PassengerHeatValid, &Switch);
    LocalPassengerHeatValid = Switch;
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Third_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.ThirdHeatValid, &Switch);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel, (INT8U)
       VentAdj_DriverCmdFaultSts, LocalDriverHeatValid, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_h, &Appl_VentAdj_CtrlModel_B.StopReason_g,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel, (INT8U)
       VentAdj_PasCmdFaultSts, LocalPassengerHeatValid, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_c,
       &Appl_VentAdj_CtrlModel_B.StopReason_lr,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction1);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.Original3rdVentLevel, (INT8U)
       VentAdj_ThirdCmdFaultSts, Switch, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_b,
       &Appl_VentAdj_CtrlModel_B.StopReason_nd,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction2);
    Appl_VentAdj_CtrlModel_B.TimeoutPrm = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel = Appl_VentAdj_CtrlModel_B.Level_h;
    Appl_VentAdj_CtrlModel_TimeoutFunction();
    Appl_VentAdj_CtrlModel_B.TimeoutPrm_b = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime_h = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel_f = Appl_VentAdj_CtrlModel_B.Level_c;
    Appl_VentAdj_CtrlModel_TimeoutFunction1();
    Appl_VentAdj_CtrlModel_B.TimeoutPrm_o = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime_k = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel_j = Appl_VentAdj_CtrlModel_B.Level_b;
    Appl_VentAdj_CtrlModel_TimeoutFunction2();
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_g,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag_l,
      &Appl_VentAdj_CtrlModel_B.StopReason_l,
      &Appl_VentAdj_CtrlModel_DW.StopFunction);
    Appl_VentAdj_CtrlModel_B.DrVentStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason_l;
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_lr,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag_h,
      &Appl_VentAdj_CtrlModel_B.StopReason_n,
      &Appl_VentAdj_CtrlModel_DW.StopFunction1);
    Appl_VentAdj_CtrlModel_B.PaVentStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason_n;
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_nd,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag, &Appl_VentAdj_CtrlModel_B.StopReason,
      &Appl_VentAdj_CtrlModel_DW.StopFunction2);
    Appl_VentAdj_CtrlModel_B.ThirdHeatStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason;
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_DriverDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_p, rtb_OrgVentDriverRunType,
      &Appl_VentAdj_CtrlModel_B.DiagDrVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentDriverRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction);
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_PassengerDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_ip, rtb_OrgVentPassengerRunType,
      &Appl_VentAdj_CtrlModel_B.DiagPaVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentPassengerRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction1);
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_ThirdDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_o, Appl_VentAdj_CtrlModel_B.RunType,
      &Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentThirdRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction2);
  }
  else
  {
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Driver_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.DriverHeatValid, &Switch);
    LocalDriverHeatValid = Switch;
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Passenger_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.PassengerHeatValid, &Switch);
    LocalPassengerHeatValid = Switch;
    Appl_VentAdj_CtrlModel_MixConflic
      (Appl_VentAdj_CtrlModel_B.Third_MixConflicFlg,
       Appl_VentAdj_CtrlModel_B.ThirdHeatValid, &Switch);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel, (INT8U)
       VentAdj_DriverCmdFaultSts, LocalDriverHeatValid, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_h, &Appl_VentAdj_CtrlModel_B.StopReason_g,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel, (INT8U)
       VentAdj_PasCmdFaultSts, LocalPassengerHeatValid, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_c,
       &Appl_VentAdj_CtrlModel_B.StopReason_lr,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction1);
    Appl_VentAdj_CtrlModel_LevelLimitFunction
      (Appl_VentAdj_CtrlModel_B.Original3rdVentLevel, (INT8U)
       VentAdj_ThirdCmdFaultSts, Switch, VentAdj_CarType,
       VentAdj_VentMsgLostFlag, VentAdj_RecoverDefaultFlag,
       &Appl_VentAdj_CtrlModel_B.Level_b,
       &Appl_VentAdj_CtrlModel_B.StopReason_nd,
       &Appl_VentAdj_CtrlModel_DW.LevelLimitFunction2);
    Appl_VentAdj_CtrlModel_B.TimeoutPrm = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel = Appl_VentAdj_CtrlModel_B.Level_h;
    Appl_VentAdj_CtrlModel_TimeoutFunction();
    Appl_VentAdj_CtrlModel_B.TimeoutPrm_b = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime_h = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel_f = Appl_VentAdj_CtrlModel_B.Level_c;
    Appl_VentAdj_CtrlModel_TimeoutFunction1();
    Appl_VentAdj_CtrlModel_B.TimeoutPrm_o = VentAdj_TimeOutPrm;
    Appl_VentAdj_CtrlModel_B.MaxTime_k = VentAdj_RunMaxTime;
    Appl_VentAdj_CtrlModel_B.InLevel_j = Appl_VentAdj_CtrlModel_B.Level_b;
    Appl_VentAdj_CtrlModel_TimeoutFunction2();
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_g,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag_l,
      &Appl_VentAdj_CtrlModel_B.StopReason_l,
      &Appl_VentAdj_CtrlModel_DW.StopFunction);
    Appl_VentAdj_CtrlModel_B.DrVentStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason_l;
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_lr,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag_h,
      &Appl_VentAdj_CtrlModel_B.StopReason_n,
      &Appl_VentAdj_CtrlModel_DW.StopFunction1);
    Appl_VentAdj_CtrlModel_B.PaVentStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason_n;
    Appl_VentAdj_CtrlModel_StopFunction(Appl_VentAdj_CtrlModel_B.StopReason_nd,
      Appl_VentAdj_CtrlModel_B.TimeoutFlag, &Appl_VentAdj_CtrlModel_B.StopReason,
      &Appl_VentAdj_CtrlModel_DW.StopFunction2);
    Appl_VentAdj_CtrlModel_B.ThirdHeatStopReason =
      Appl_VentAdj_CtrlModel_B.StopReason;
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_DriverDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_p, rtb_OrgVentDriverRunType,
      &Appl_VentAdj_CtrlModel_B.DiagDrVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentDriverRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction);
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_PassengerDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_ip, rtb_OrgVentPassengerRunType,
      &Appl_VentAdj_CtrlModel_B.DiagPaVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentPassengerRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction1);
    Appl_VentAdj_CtrlModel_DiagnoseFunction((INT8U)VentAdj_ThirdDiagCmd,
      Appl_VentAdj_CtrlModel_B.Level_o, Appl_VentAdj_CtrlModel_B.RunType,
      &Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel,
      &Appl_VentAdj_CtrlModel_B.VentThirdRunType,
      &Appl_VentAdj_CtrlModel_DW.DiagnoseFunction2);
  }

  if (Appl_VentAdj_CtrlModel_DW.is_active_c14_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c14_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_DW.is_CANOutputDeal =
      Appl_VentAdj_CtrlModel_IN_Default_d;
    Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
      Appl_VentAdj_CtrlModel_B.DiagDrVentLevel;
    Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
      Appl_VentAdj_CtrlModel_B.DiagPaVentLevel;
    Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
      Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel;
    Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
    Appl_VentAdj_CtrlModel_DW.is_DrvErr = Appl_VentAdj_CtrlModel_IN_FalseSts;
    Appl_VentAdj_CtrlModel_B.OutDrRunState =
      Appl_VentAdj_CtrlModel_DW.LocalDrRunState;
    Appl_VentAdj_CtrlModel_DW.is_PasErr = Appl_VentAdj_CtrlModel_IN_FalseSts;
    Appl_VentAdj_CtrlModel_B.OutPaRunState =
      Appl_VentAdj_CtrlModel_DW.LocalPaRunState;
    Appl_VentAdj_CtrlModel_DW.is_TrebleErr = Appl_VentAdj_CtrlModel_IN_FalseSts;
    Appl_VentAdj_CtrlModel_B.Out3rdRunState =
      Appl_VentAdj_CtrlModel_DW.Local3rdRunState;
    Appl_VentAdj_CtrlModel_DutyFunction(Appl_VentAdj_CtrlModel_B.DiagDrVentLevel,
      &Switch);
    Appl_VentAdj_CtrlModel_DutyFunction(Appl_VentAdj_CtrlModel_B.DiagPaVentLevel,
      &Switch);
    Appl_VentAdj_CtrlModel_DutyFunction
      (Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel, &Switch);
  }
  else
  {
    if (Appl_VentAdj_CtrlModel_DW.is_CANOutputDeal ==
        Appl_VentAdj_CtrlModel_IN_Default_d)
    {
      /*  P20的车型  */
      if (enProjectType_EN_PROJECT_P20 == VentAdj_CarType)
      {
        Appl_VentAdj_CtrlModel_DW.is_CANOutputDeal =
          Appl_VentAdj_CtrlModel_IN_ProjectP20;

        /* Initial Value(Hex)初始值:0x0 */
        Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
          enVentLvlSts_EN_VENT_LVL_OFF;
        Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
          enVentLvlSts_EN_VENT_LVL_OFF;
        Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
          enVentLvlSts_EN_VENT_LVL_OFF;
        Appl_VentAdj_CtrlModel_DW.is_Drv = Appl_VentAdj_CtrlModel_IN_Init_k;
        Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_DW.is_Pas = Appl_VentAdj_CtrlModel_IN_Init_k;
        Appl_VentAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_DW.is_Treble = Appl_VentAdj_CtrlModel_IN_Init_k;
        Appl_VentAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
          Appl_VentAdj_CtrlModel_B.DiagDrVentLevel;
        Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
          Appl_VentAdj_CtrlModel_B.DiagPaVentLevel;
        Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
          Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel;
        Appl_VentAdj_CtrlModel_B.OutDrRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_B.OutPaRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_B.Out3rdRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
      }
    }
    else
    {
      /*  非P20车型  */
      if (enProjectType_EN_PROJECT_P20 != VentAdj_CarType)
      {
        Appl_VentAdj_CtrlModel_DW.is_Treble = 0;
        Appl_VentAdj_CtrlModel_DW.is_Pas = 0;
        Appl_VentAdj_CtrlModel_DW.is_Drv = 0;
        Appl_VentAdj_CtrlModel_DW.is_CANOutputDeal =
          Appl_VentAdj_CtrlModel_IN_Default_d;
        Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
          Appl_VentAdj_CtrlModel_B.DiagDrVentLevel;
        Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
          Appl_VentAdj_CtrlModel_B.DiagPaVentLevel;
        Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
          Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel;
        Appl_VentAdj_CtrlModel_B.OutDrRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_B.OutPaRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_B.Out3rdRunState = ((BOOL)FALSE);
        Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
      }
      else
      {
        if (Appl_VentAdj_CtrlModel_DW.is_Drv == Appl_VentAdj_CtrlModel_IN_Init_k)
        {
          /*  主驾通风指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF !=
              Appl_VentAdj_CtrlModel_B.DiagDrVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Drv = Appl_VentAdj_CtrlModel_IN_Run_p;
            Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
              Appl_VentAdj_CtrlModel_B.DiagDrVentLevel;
            Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  主驾通风无指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF ==
              Appl_VentAdj_CtrlModel_B.DiagDrVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Drv = Appl_VentAdj_CtrlModel_IN_Init_k;
            Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
          }
          else
          {
            Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel =
              Appl_VentAdj_CtrlModel_B.DiagDrVentLevel;
            Appl_VentAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)TRUE);
          }
        }

        if (Appl_VentAdj_CtrlModel_DW.is_Pas == Appl_VentAdj_CtrlModel_IN_Init_k)
        {
          /*  副驾通风指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF !=
              Appl_VentAdj_CtrlModel_B.DiagPaVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Pas = Appl_VentAdj_CtrlModel_IN_Run_p;
            Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
              Appl_VentAdj_CtrlModel_B.DiagPaVentLevel;
            Appl_VentAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  副驾通风无指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF ==
              Appl_VentAdj_CtrlModel_B.DiagPaVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Pas = Appl_VentAdj_CtrlModel_IN_Init_k;
            Appl_VentAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
          }
          else
          {
            Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel =
              Appl_VentAdj_CtrlModel_B.DiagPaVentLevel;
            Appl_VentAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)TRUE);
          }
        }

        if (Appl_VentAdj_CtrlModel_DW.is_Treble ==
            Appl_VentAdj_CtrlModel_IN_Init_k)
        {
          /*  三排通风无指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF !=
              Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Treble =
              Appl_VentAdj_CtrlModel_IN_Run_p;
            Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
              Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel;
            Appl_VentAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  三排通风无指令  */
          if (enVentLvlSts_EN_VENT_LVL_OFF ==
              Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel)
          {
            Appl_VentAdj_CtrlModel_DW.is_Treble =
              Appl_VentAdj_CtrlModel_IN_Init_k;
            Appl_VentAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
          }
          else
          {
            Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel =
              Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel;
            Appl_VentAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)TRUE);
          }
        }
      }
    }

    if (Appl_VentAdj_CtrlModel_DW.is_DrvErr ==
        Appl_VentAdj_CtrlModel_IN_FalseSts)
    {
      /*  无指令 且存在故障  */
      if ((Appl_VentAdj_CtrlModel_DW.LocalDrRunState == ((BOOL)FALSE)) &&
          ((INT32S)VentAdj_DriverCmdFaultSts4DTC != ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_DrvErr = Appl_VentAdj_CtrlModel_IN_SuccSts;
        Appl_VentAdj_CtrlModel_B.OutDrRunState = 2U;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.OutDrRunState =
          Appl_VentAdj_CtrlModel_DW.LocalDrRunState;
      }
    }
    else
    {
      /* 无故障 或RUN状态  */
      if ((Appl_VentAdj_CtrlModel_DW.LocalDrRunState == ((BOOL)TRUE)) ||
          ((INT32S)VentAdj_DriverCmdFaultSts4DTC == ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_DrvErr = Appl_VentAdj_CtrlModel_IN_FalseSts;
        Appl_VentAdj_CtrlModel_B.OutDrRunState =
          Appl_VentAdj_CtrlModel_DW.LocalDrRunState;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.OutDrRunState = 2U;
      }
    }

    if (Appl_VentAdj_CtrlModel_DW.is_PasErr ==
        Appl_VentAdj_CtrlModel_IN_FalseSts)
    {
      /*  无指令 且存在故障  */
      if ((Appl_VentAdj_CtrlModel_DW.LocalPaRunState == ((BOOL)FALSE)) &&
          ((INT32S)VentAdj_PasCmdFaultSts4DTC != ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_PasErr = Appl_VentAdj_CtrlModel_IN_SuccSts;
        Appl_VentAdj_CtrlModel_B.OutPaRunState = 2U;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.OutPaRunState =
          Appl_VentAdj_CtrlModel_DW.LocalPaRunState;
      }
    }
    else
    {
      /* 无故障 或RUN状态  */
      if ((Appl_VentAdj_CtrlModel_DW.LocalPaRunState == ((BOOL)TRUE)) ||
          ((INT32S)VentAdj_PasCmdFaultSts4DTC == ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_PasErr = Appl_VentAdj_CtrlModel_IN_FalseSts;
        Appl_VentAdj_CtrlModel_B.OutPaRunState =
          Appl_VentAdj_CtrlModel_DW.LocalPaRunState;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.OutPaRunState = 2U;
      }
    }

    if (Appl_VentAdj_CtrlModel_DW.is_TrebleErr ==
        Appl_VentAdj_CtrlModel_IN_FalseSts)
    {
      /*  无指令 且存在故障  */
      if ((Appl_VentAdj_CtrlModel_DW.Local3rdRunState == ((BOOL)FALSE)) &&
          ((INT32S)VentAdj_ThirdCmdFaultSts4DTC != ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_TrebleErr =
          Appl_VentAdj_CtrlModel_IN_SuccSts;
        Appl_VentAdj_CtrlModel_B.Out3rdRunState = 2U;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.Out3rdRunState =
          Appl_VentAdj_CtrlModel_DW.Local3rdRunState;
      }
    }
    else
    {
      /* 无故障 或RUN状态  */
      if ((Appl_VentAdj_CtrlModel_DW.Local3rdRunState == ((BOOL)TRUE)) ||
          ((INT32S)VentAdj_ThirdCmdFaultSts4DTC == ((BOOL)FALSE)))
      {
        Appl_VentAdj_CtrlModel_DW.is_TrebleErr =
          Appl_VentAdj_CtrlModel_IN_FalseSts;
        Appl_VentAdj_CtrlModel_B.Out3rdRunState =
          Appl_VentAdj_CtrlModel_DW.Local3rdRunState;
      }
      else
      {
        Appl_VentAdj_CtrlModel_B.Out3rdRunState = 2U;
      }
    }

    Appl_VentAdj_CtrlModel_DutyFunction(Appl_VentAdj_CtrlModel_B.DiagDrVentLevel,
      &Switch);
    Appl_VentAdj_CtrlModel_DutyFunction(Appl_VentAdj_CtrlModel_B.DiagPaVentLevel,
      &Switch);
    Appl_VentAdj_CtrlModel_DutyFunction
      (Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel, &Switch);
  }
}

/*
 * System initialize for function-call system:
 *    '<S67>/OppositeMessageDeal'
 *    '<S67>/OppositeMessageDeal1'
 *    '<S67>/OppositeMessageDeal2'
 */
static void Appl_VentAdj_CtrlModel_OppositeMessageDeal_Init(INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_HMIMessageDeal = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_np;
  localDW->is_TboxMessageDeal = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_np;
  localDW->is_VenStatus = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_np;
  localDW->is_active_c18_Appl_VentAdj_CtrlModel = 0U;
  localDW->TempHMI = 0U;
  localDW->TempTbox = 0U;
  *rty_VenSts = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S67>/OppositeMessageDeal'
 *    '<S67>/OppositeMessageDeal1'
 *    '<S67>/OppositeMessageDeal2'
 */
static void Appl_VentAdj_CtrlModel_OppositeMessageDeal(enProjectType
  rtu_CarTypeCfg, INT8U rtu_RemoteModeFlag, INT8U rtu_HMI_Message, INT8U
  rtu_Tbox_Message, INT8U rtu_HeatCfg, INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c18_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c18_Appl_VentAdj_CtrlModel = 1U;
    localDW->is_HMIMessageDeal = Appl_VentAdj_CtrlModel_IN_HMIInit;
    localDW->TempHMI = ((BOOL)FALSE);
    localDW->is_TboxMessageDeal = Appl_VentAdj_CtrlModel_IN_TboxInit;
    localDW->TempTbox = ((BOOL)FALSE);
    localDW->is_VenStatus = Appl_VentAdj_CtrlModel_IN_TboxInit;
    *rty_VenSts = ((BOOL)FALSE);
  }
  else
  {
    if (localDW->is_HMIMessageDeal == Appl_VentAdj_CtrlModel_IN_HMIInit)
    {
      /* 档位请求有效 */
      if (((enProjectType_EN_PROJECT_BM400 != rtu_CarTypeCfg) && ((0x1 ==
             rtu_HMI_Message) || (0x2 == rtu_HMI_Message) || (0x3 ==
             rtu_HMI_Message) || (0x5 == rtu_HMI_Message))) ||
          ((enProjectType_EN_PROJECT_BM400 == rtu_CarTypeCfg) && ((0x2 ==
             rtu_HMI_Message) || (0x3 == rtu_HMI_Message) || (0x4 ==
             rtu_HMI_Message))))
      {
        localDW->is_HMIMessageDeal = Appl_VentAdj_CtrlModel_IN_HMIValid;
        localDW->TempHMI = ((BOOL)TRUE);
      }
    }
    else
    {
      /* HMI报文关闭 */
      if (((enProjectType_EN_PROJECT_BM400 != rtu_CarTypeCfg) && (0x1 !=
            rtu_HMI_Message) && (0x2 != rtu_HMI_Message) && (0x3 !=
            rtu_HMI_Message) && (0x5 != rtu_HMI_Message)) ||
          ((enProjectType_EN_PROJECT_BM400 == rtu_CarTypeCfg) && (0x2 !=
            rtu_HMI_Message) && (0x3 != rtu_HMI_Message) && (0x4 !=
            rtu_HMI_Message)))
      {
        localDW->is_HMIMessageDeal = Appl_VentAdj_CtrlModel_IN_HMIInit;
        localDW->TempHMI = ((BOOL)FALSE);
      }
    }

    if (localDW->is_TboxMessageDeal == Appl_VentAdj_CtrlModel_IN_TboxInit)
    {
      /* 档位请求有效 */
      if ((((BOOL)TRUE) == rtu_RemoteModeFlag) && ((0x1 == rtu_Tbox_Message) ||
           (0x2 == rtu_Tbox_Message) || (0x3 == rtu_Tbox_Message)))
      {
        localDW->is_TboxMessageDeal = Appl_VentAdj_CtrlModel_IN_TboxValid;
        localDW->TempTbox = ((BOOL)TRUE);
      }
    }
    else
    {
      /* Tbox报文关闭 */
      if ((0x0 == rtu_Tbox_Message) || (((BOOL)FALSE) == rtu_RemoteModeFlag))
      {
        localDW->is_TboxMessageDeal = Appl_VentAdj_CtrlModel_IN_TboxInit;
        localDW->TempTbox = ((BOOL)FALSE);
      }
    }

    if (localDW->is_VenStatus == Appl_VentAdj_CtrlModel_IN_TboxInit)
    {
      *rty_VenSts = ((BOOL)FALSE);

      /*  档位请求有效 且加热配置  */
      if (((((BOOL)TRUE) == localDW->TempHMI) || (((BOOL)TRUE) ==
            localDW->TempTbox)) && (rtu_HeatCfg == ((BOOL)TRUE)))
      {
        localDW->is_VenStatus = Appl_VentAdj_CtrlModel_IN_TboxValid;
        *rty_VenSts = ((BOOL)TRUE);
      }
    }
    else
    {
      *rty_VenSts = ((BOOL)TRUE);

      /*  档位请求无效 或加热无配置  */
      if (((((BOOL)FALSE) == localDW->TempHMI) && (((BOOL)FALSE) ==
            localDW->TempTbox)) || (rtu_HeatCfg == ((BOOL)FALSE)))
      {
        localDW->is_VenStatus = Appl_VentAdj_CtrlModel_IN_TboxInit;
        *rty_VenSts = ((BOOL)FALSE);
      }
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S75>/MsgConflictFunction2'
 *    '<S75>/MsgConflictFunction1'
 *    '<S75>/MsgConflictFunction'
 */
static void Appl_VentAdj_CtrlModel_MsgConflictFunction2_Init(INT8U
  *rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T *localDW)
{
  localDW->is_HMI_MessageDeal = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_bo;
  localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_bo;
  localDW->is_Tbox_MessageDeal = Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_bo;
  localDW->is_active_c32_Appl_VentAdj_CtrlModel = 0U;
  localDW->HMI_Flag = 0U;
  localDW->Tbox_Flag = 0U;
  *rty_OutMsgHMI = 0U;
  *rty_OutMsgTbox = 0U;
  *rty_MixConflictFlg = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S75>/MsgConflictFunction2'
 *    '<S75>/MsgConflictFunction1'
 *    '<S75>/MsgConflictFunction'
 */
static void Appl_VentAdj_CtrlModel_MsgConflictFunction2(INT8U rtu_CarTypeCfg,
  INT8U rtu_HMI_Message, INT8U rtu_Tbox_Message, INT8U rtu_VentValidFlag, INT8U *
  rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_VentAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c32_Appl_VentAdj_CtrlModel == 0U)
  {
    localDW->is_active_c32_Appl_VentAdj_CtrlModel = 1U;
    localDW->is_HMI_MessageDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
    localDW->HMI_Flag = ((BOOL)FALSE);
    localDW->is_Tbox_MessageDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
    localDW->Tbox_Flag = ((BOOL)FALSE);
    localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
    *rty_OutMsgHMI = rtu_HMI_Message;
    *rty_OutMsgTbox = rtu_Tbox_Message;
    *rty_MixConflictFlg = ((BOOL)FALSE);
  }
  else
  {
    if (localDW->is_HMI_MessageDeal == Appl_VentAdj_CtrlModel_IN_Default_c)
    {
      /* HMI通风报文有效0x0:Inactive；0x1:Level 1；1档;0x2:Level 2；2档;0x3:Level 3；3档；0x4:OFF: 0x05 OPEN */
      if (((INT32S)enVentLvlSts_EN_VENT_LVL_1 == rtu_HMI_Message) || ((INT32S)
           enVentLvlSts_EN_VENT_LVL_2 == rtu_HMI_Message) || ((INT32S)
           enVentLvlSts_EN_VENT_LVL_3 == rtu_HMI_Message) || (4 ==
           rtu_HMI_Message) || (5 == rtu_HMI_Message))
      {
        localDW->is_HMI_MessageDeal = Appl_VentAdj_CtrlModel_IN_Valid;
        localDW->HMI_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* HMI通风报文无效，20240507NXM增加关闭4 */
      if (((INT32S)enVentLvlSts_EN_VENT_LVL_1 != rtu_HMI_Message) && ((INT32S)
           enVentLvlSts_EN_VENT_LVL_2 != rtu_HMI_Message) && ((INT32S)
           enVentLvlSts_EN_VENT_LVL_3 != rtu_HMI_Message) && (4 !=
           rtu_HMI_Message) && (5 != rtu_HMI_Message))
      {
        localDW->is_HMI_MessageDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
        localDW->HMI_Flag = ((BOOL)FALSE);
      }
    }

    if (localDW->is_Tbox_MessageDeal == Appl_VentAdj_CtrlModel_IN_Default_c)
    {
      /* Tbox通风报文有效0x0:No Request；0x1:Heat_1；0x2:Heat_2；0x3:Heat_3；0x4:Close */
      if (((INT32S)enVentLvlSts_EN_VENT_LVL_1 == rtu_Tbox_Message) || ((INT32S)
           enVentLvlSts_EN_VENT_LVL_2 == rtu_Tbox_Message) || ((INT32S)
           enVentLvlSts_EN_VENT_LVL_3 == rtu_Tbox_Message) || (4 ==
           rtu_Tbox_Message))
      {
        localDW->is_Tbox_MessageDeal = Appl_VentAdj_CtrlModel_IN_Valid;
        localDW->Tbox_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* Tbox通风报文无效，20240507NXM增加关闭4 */
      if (((INT32S)enVentLvlSts_EN_VENT_LVL_1 != rtu_Tbox_Message) && ((INT32S)
           enVentLvlSts_EN_VENT_LVL_2 != rtu_Tbox_Message) && ((INT32S)
           enVentLvlSts_EN_VENT_LVL_3 != rtu_Tbox_Message) && (4 !=
           rtu_Tbox_Message))
      {
        localDW->is_Tbox_MessageDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
        localDW->Tbox_Flag = ((BOOL)FALSE);
      }
    }

    switch (localDW->is_MessageConflictDeal)
    {
     case Appl_VentAdj_CtrlModel_IN_Default_c:
      /* P20车型HMI、TBOX通风报文同时有效 */
      if (((INT32S)enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg) && (((BOOL)
            FALSE) != localDW->HMI_Flag) && (((BOOL)FALSE) != localDW->Tbox_Flag))
      {
        localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_HeatConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)FALSE);
      }
      else
      {
        /* 通风加热报文同时有效 且非关闭状态  */
        if ((((BOOL)FALSE) != rtu_VentValidFlag) && (((((BOOL)FALSE) !=
               localDW->HMI_Flag) && (4 != rtu_HMI_Message)) || ((((BOOL)FALSE)
               != localDW->Tbox_Flag) && (4 != rtu_Tbox_Message))))
        {
          localDW->is_MessageConflictDeal =
            Appl_VentAdj_CtrlModel_IN_VentilateConflict;
          *rty_OutMsgHMI = 0U;
          *rty_OutMsgTbox = 0U;
          *rty_MixConflictFlg = ((BOOL)TRUE);
        }
        else
        {
          *rty_OutMsgHMI = rtu_HMI_Message;
          *rty_OutMsgTbox = rtu_Tbox_Message;
          *rty_MixConflictFlg = ((BOOL)FALSE);
        }
      }
      break;

     case Appl_VentAdj_CtrlModel_IN_HeatConflict:
      /* 通风加热报文同时有效，20240507NXM */
      if ((((BOOL)FALSE) != rtu_VentValidFlag) && ((((BOOL)FALSE) !=
            localDW->HMI_Flag) || (((BOOL)FALSE) != localDW->Tbox_Flag)))
      {
        localDW->is_MessageConflictDeal =
          Appl_VentAdj_CtrlModel_IN_VentilateConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)TRUE);
      }
      else
      {
        /* 非P20车型||P20车型通风报文不同时有效，20240507NXM */
        if (((INT32S)enProjectType_EN_PROJECT_P20 != rtu_CarTypeCfg) || ((((BOOL)
               FALSE) == localDW->HMI_Flag) || (((BOOL)FALSE) ==
              localDW->Tbox_Flag)))
        {
          localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
          *rty_OutMsgHMI = rtu_HMI_Message;
          *rty_OutMsgTbox = rtu_Tbox_Message;
          *rty_MixConflictFlg = ((BOOL)FALSE);
        }
      }
      break;

     default:
      /* P20车型HMI、TBOX通风报文同时有效 */
      if (((INT32S)enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg) && (((BOOL)
            FALSE) != localDW->HMI_Flag) && (((BOOL)FALSE) != localDW->Tbox_Flag)
          && (((BOOL)FALSE) == rtu_VentValidFlag))
      {
        localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_HeatConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)FALSE);
      }
      else
      {
        /* 通风加热报文不同时有效 或关闭，20240507NXM修改跳转顺序 */
        if ((((BOOL)FALSE) == rtu_VentValidFlag) || (4 == rtu_HMI_Message) || (4
             == rtu_Tbox_Message))
        {
          localDW->is_MessageConflictDeal = Appl_VentAdj_CtrlModel_IN_Default_c;
          *rty_OutMsgHMI = rtu_HMI_Message;
          *rty_OutMsgTbox = rtu_Tbox_Message;
          *rty_MixConflictFlg = ((BOOL)FALSE);
        }
      }
      break;
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_VentAdj_CtrlModel_RTE(void)
{
  VentAdj_3rdHeatFlg = Rte_GetVfb_ThirdHeatEnable( );
  VentAdj_CanDrvVentLvl = Ecual_CanGetDrvVentLvl( );
  VentAdj_CanPasVentLvl = Ecual_CanGetPasVentLvl( );
  VentAdj_CanThirdVentLvl = Ecual_CanGetThirdVentLvl( );
  VentAdj_CarType = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  VentAdj_D_SimuIndex_DRVent = Rte_GetVfb_DrVent( );
  VentAdj_D_SimuIndex_PAVent = Rte_GetVfb_PaVent( );
  VentAdj_D_SimuIndex_ThirdVent = Rte_GetVfb_ThirdVent( );
  VentAdj_DrHeatFlg = Rte_GetVfb_DrHeatEnable( );
  VentAdj_DrVentFlg = Rte_GetVfb_DrVentEnable( );
  VentAdj_DrVentStopReason = Rte_GetVfb_DrVentStopReason( );
  VentAdj_DriverCmdFaultSts = Rte_GetVfb_DrVentCmdFaultSts( );
  VentAdj_DriverCmdFaultSts4DTC = Rte_GetVfb_DrVentCmdFaultSts4DTC( );
  VentAdj_DriverDiagCmd = Desc_DiagOutCtrlPram(EN_DRVENTILATE);
  VentAdj_DriverEnableConfig = Rte_GetVfb_DrVentEnable( );
  VentAdj_DriverHMI_VentMessage = CanRx_0x351_IVI_FLSeatVentnSet( );
  VentAdj_DriverTbox_VentMessage = CanRx_0x281_BDC_TBOX_Req_DrSeatVentilating( );
  VentAdj_Driver_HMI_HeatMsg = CanRx_0x351_IVI_FLSeatHeatSet( );
  VentAdj_Driver_Tbox_HeatMsg = CanRx_0x281_BDC_TBOX_Req_DrSeatHeating( );
  VentAdj_EngineRunFlag = Rte_GetVfb_EngineRunFlag( );
  VentAdj_PaHeatFlg = Rte_GetVfb_SecondHeatEnable( );
  VentAdj_PaVentFlg = Rte_GetVfb_SecondVentEnable( );
  VentAdj_PaVentStopReason = Rte_GetVfb_PaVentStopReason( );
  VentAdj_PasCmdFaultSts = Rte_GetVfb_PaVentCmdFaultSts( );
  VentAdj_PasCmdFaultSts4DTC = Rte_GetVfb_PaVentCmdFaultSts4DTC( );
  VentAdj_PassengerDiagCmd = Desc_DiagOutCtrlPram(EN_PAVENTILATE);
  VentAdj_PassengerEnableConfig = Rte_GetVfb_SecondVentEnable( );
  VentAdj_PassengerHMI_VentMessage = CanRx_0x351_IVI_FRSeatVentnSet( );
  VentAdj_PassengerTbox_VentMessage = CanRx_0x281_BDC_TBOX_Req_PaSeatVentilating
    ( );
  VentAdj_Passenger_HMI_HeatMsg = CanRx_0x351_IVI_FRSeatHeatSet( );
  VentAdj_Passenger_Tbox_HeatMsg = CanRx_0x281_BDC_TBOX_Req_PaSeatHeating( );
  VentAdj_PowerMode = Rte_GetVfb_PowerMode( );
  VentAdj_RecoverDefaultFlag = GetRecoverDefaultFlag( );
  VentAdj_RemoteModeFlag = Rte_GetVfb_RemoteModeFlag( );
  VentAdj_RunMaxTime = Srvl_GetMemIndexDataU8(EN_MemIndex_Vent_RunMaxTime);
  VentAdj_ThirdCmdFaultSts = Rte_GetVfb_ThirdVentCmdFaultSts( );
  VentAdj_ThirdCmdFaultSts4DTC = Vfb_Reserved_0( );
  VentAdj_ThirdDiagCmd = Vfb_Reserved_0( );
  VentAdj_ThirdEnableConfig = Rte_GetVfb_ThirdVentEnable( );
  VentAdj_ThirdHMI_VentMessage = Vfb_Reserved_0( );
  VentAdj_ThirdTbox_VentMessage = Vfb_Reserved_0( );
  VentAdj_ThirdVentStopReason = Rte_GetVfb_ThirdVentStopReason( );
  VentAdj_Third_HMI_HeatMsg = CanRx_0x351_IVI_SwsHeatSw( );
  VentAdj_Third_Tbox_HeatMsg = CanRx_0x281_BDC_TBOX_Req_Steeringwheel_heating( );
  VentAdj_TimeOutPrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Vent_TimeOutPrm);
  VentAdj_VehicleRunFlag = Rte_GetVfb_VehicleRunFlag( );
  VentAdj_VentMsgLostFlag = Vfb_Reserved_0( );
  VentAdj_VoltMode = Rte_GetVfb_VoltMode( );
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_VentAdj_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U VenSts_b;
  Appl_VentAdj_CtrlModel_DW.is_active_c39_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_DW.is_c39_Appl_VentAdj_CtrlModel =
    Appl_VentAdj_CtrlModel_IN_NO_ACTIVE_CHILD_gp;
  Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = 0U;
  Appl_VentAdj_CtrlModel_DW.is_active_c6_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_B.DriverHeatValid = 0U;
  Appl_VentAdj_CtrlModel_B.PassengerHeatValid = 0U;
  Appl_VentAdj_CtrlModel_B.ThirdHeatValid = 0U;
  Appl_VentAdj_CtrlModel_OppositeMessageDeal_Init(&VenSts_b,
    &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal);
  Appl_VentAdj_CtrlModel_OppositeMessageDeal_Init(&VenSts_b,
    &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal1);
  Appl_VentAdj_CtrlModel_OppositeMessageDeal_Init(&VenSts_b,
    &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal2);
  Appl_VentAdj_CtrlModel_DW.is_active_c28_Appl_VentAdj_CtrlModel = 0U;
  Appl_VentAdj_CtrlModel_B.DriverHMI_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.DriverTbox_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.PassengerHMI_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.PassengerTbox_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.ThirdHMI_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.ThirdTbox_VentMessage = 0U;
  Appl_VentAdj_CtrlModel_B.Driver_MixConflicFlg = 0U;
  Appl_VentAdj_CtrlModel_B.Passenger_MixConflicFlg = 0U;
  Appl_VentAdj_CtrlModel_B.Third_MixConflicFlg = 0U;
  Appl_VentAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_VentAdj_CtrlModel_B.OutMsgHMI_j,
     &Appl_VentAdj_CtrlModel_B.OutMsgTbox_e,
     &Appl_VentAdj_CtrlModel_B.MixConflictFlg_h,
     &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction2);
  Appl_VentAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_VentAdj_CtrlModel_B.OutMsgHMI_b,
     &Appl_VentAdj_CtrlModel_B.OutMsgTbox_i,
     &Appl_VentAdj_CtrlModel_B.MixConflictFlg_j,
     &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction1);
  Appl_VentAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_VentAdj_CtrlModel_B.OutMsgHMI, &Appl_VentAdj_CtrlModel_B.OutMsgTbox,
     &Appl_VentAdj_CtrlModel_B.MixConflictFlg,
     &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction);
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_VentAdj_CtrlModel_UpDataInputInfo(void)
{
  Appl_VentAdj_CtrlModel_RTE();
  if (Appl_VentAdj_CtrlModel_DW.is_active_c39_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c39_Appl_VentAdj_CtrlModel = 1U;
    Appl_VentAdj_CtrlModel_DW.is_c39_Appl_VentAdj_CtrlModel =
      Appl_VentAdj_CtrlModel_IN_Default_i;
    Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);
  }
  else if (Appl_VentAdj_CtrlModel_DW.is_c39_Appl_VentAdj_CtrlModel ==
           Appl_VentAdj_CtrlModel_IN_Default_i)
  {
    Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);

    /* (发动机运行中 || 整车运行状态满足) && 正常电压模式 */
    if (((((BOOL)TRUE) == VentAdj_EngineRunFlag) || (((BOOL)TRUE) ==
          VentAdj_VehicleRunFlag)) && (enFinalPowerMode_EN_NORMAL_VOLT ==
         VentAdj_VoltMode))
    {
      Appl_VentAdj_CtrlModel_DW.is_c39_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_ValidSts_e;
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)TRUE);

    /* (发动机不在运行中 && 整车运行状态不满足) || 非正常电压模式 */
    if (((((BOOL)TRUE) != VentAdj_EngineRunFlag) && (((BOOL)TRUE) !=
          VentAdj_VehicleRunFlag)) || (enFinalPowerMode_EN_NORMAL_VOLT !=
         VentAdj_VoltMode))
    {
      Appl_VentAdj_CtrlModel_DW.is_c39_Appl_VentAdj_CtrlModel =
        Appl_VentAdj_CtrlModel_IN_Default_i;
      Appl_VentAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);
    }
  }

  if (Appl_VentAdj_CtrlModel_DW.is_active_c6_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c6_Appl_VentAdj_CtrlModel = 1U;
  }
  else
  {
    Appl_VentAdj_CtrlModel_OppositeMessageDeal(VentAdj_CarType,
      VentAdj_RemoteModeFlag, VentAdj_Driver_HMI_HeatMsg,
      VentAdj_Driver_Tbox_HeatMsg, VentAdj_DrHeatFlg,
      &Appl_VentAdj_CtrlModel_B.DriverHeatValid,
      &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal);
    Appl_VentAdj_CtrlModel_OppositeMessageDeal(VentAdj_CarType,
      VentAdj_RemoteModeFlag, VentAdj_Passenger_HMI_HeatMsg,
      VentAdj_Passenger_Tbox_HeatMsg, VentAdj_PaHeatFlg,
      &Appl_VentAdj_CtrlModel_B.PassengerHeatValid,
      &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal1);
    Appl_VentAdj_CtrlModel_OppositeMessageDeal(VentAdj_CarType,
      VentAdj_RemoteModeFlag, VentAdj_Third_HMI_HeatMsg,
      VentAdj_Third_Tbox_HeatMsg, VentAdj_3rdHeatFlg,
      &Appl_VentAdj_CtrlModel_B.ThirdHeatValid,
      &Appl_VentAdj_CtrlModel_DW.OppositeMessageDeal2);
  }

  if (Appl_VentAdj_CtrlModel_DW.is_active_c28_Appl_VentAdj_CtrlModel == 0U)
  {
    Appl_VentAdj_CtrlModel_DW.is_active_c28_Appl_VentAdj_CtrlModel = 1U;
  }
  else
  {
    Appl_VentAdj_CtrlModel_MsgConflictFunction2((INT8U)VentAdj_CarType,
      VentAdj_DriverHMI_VentMessage, VentAdj_DriverTbox_VentMessage,
      Appl_VentAdj_CtrlModel_B.DriverHeatValid,
      &Appl_VentAdj_CtrlModel_B.OutMsgHMI, &Appl_VentAdj_CtrlModel_B.OutMsgTbox,
      &Appl_VentAdj_CtrlModel_B.MixConflictFlg,
      &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction);
    Appl_VentAdj_CtrlModel_B.DriverHMI_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgHMI;
    Appl_VentAdj_CtrlModel_B.DriverTbox_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgTbox;
    Appl_VentAdj_CtrlModel_B.Driver_MixConflicFlg =
      Appl_VentAdj_CtrlModel_B.MixConflictFlg;
    Appl_VentAdj_CtrlModel_MsgConflictFunction2((INT8U)VentAdj_CarType,
      VentAdj_PassengerHMI_VentMessage, VentAdj_PassengerTbox_VentMessage,
      Appl_VentAdj_CtrlModel_B.PassengerHeatValid,
      &Appl_VentAdj_CtrlModel_B.OutMsgHMI_b,
      &Appl_VentAdj_CtrlModel_B.OutMsgTbox_i,
      &Appl_VentAdj_CtrlModel_B.MixConflictFlg_j,
      &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction1);
    Appl_VentAdj_CtrlModel_B.PassengerHMI_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgHMI_b;
    Appl_VentAdj_CtrlModel_B.PassengerTbox_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgTbox_i;
    Appl_VentAdj_CtrlModel_B.Passenger_MixConflicFlg =
      Appl_VentAdj_CtrlModel_B.MixConflictFlg_j;
    Appl_VentAdj_CtrlModel_MsgConflictFunction2((INT8U)VentAdj_CarType,
      VentAdj_ThirdHMI_VentMessage, VentAdj_ThirdTbox_VentMessage,
      Appl_VentAdj_CtrlModel_B.ThirdHeatValid,
      &Appl_VentAdj_CtrlModel_B.OutMsgHMI_j,
      &Appl_VentAdj_CtrlModel_B.OutMsgTbox_e,
      &Appl_VentAdj_CtrlModel_B.MixConflictFlg_h,
      &Appl_VentAdj_CtrlModel_DW.MsgConflictFunction2);
    Appl_VentAdj_CtrlModel_B.ThirdHMI_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgHMI_j;
    Appl_VentAdj_CtrlModel_B.ThirdTbox_VentMessage =
      Appl_VentAdj_CtrlModel_B.OutMsgTbox_e;
    Appl_VentAdj_CtrlModel_B.Third_MixConflicFlg =
      Appl_VentAdj_CtrlModel_B.MixConflictFlg_h;
  }

  Appl_VentAdj_CtrlModel_B.PaVentFlg = ((VentAdj_PassengerEnableConfig != 0) &&
    (VentAdj_PaVentFlg != 0));
  Appl_VentAdj_CtrlModel_B.DrvVentFlg = ((VentAdj_DriverEnableConfig != 0) &&
    (VentAdj_DrVentFlg != 0));
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_VentAdj_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_ThirdVentRunState(Appl_VentAdj_CtrlModel_B.Out3rdRunState);
  Rte_SetVfb_DrVent(Appl_VentAdj_CtrlModel_B.DiagDrVentLevel);
  Rte_SetVfb_DrVentRunState(Appl_VentAdj_CtrlModel_B.OutDrRunState);
  Ecual_CanSetDrvVentSts(Appl_VentAdj_CtrlModel_B.OutDrRunState);
  Rte_SetVfb_DrVentStopReason(Appl_VentAdj_CtrlModel_B.DrVentStopReason);
  Rte_SetVfb_DrVentType(Appl_VentAdj_CtrlModel_B.VentDriverRunType);
  Ecual_CanSetDrvVentLvl(Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel);
  Rte_SetVfb_PaVent(Appl_VentAdj_CtrlModel_B.DiagPaVentLevel);
  Rte_SetVfb_PaVentRunState(Appl_VentAdj_CtrlModel_B.OutPaRunState);
  Ecual_CanSetPasVentSts(Appl_VentAdj_CtrlModel_B.OutPaRunState);
  Rte_SetVfb_PaVentStopReason(Appl_VentAdj_CtrlModel_B.PaVentStopReason);
  Rte_SetVfb_PaVentType(Appl_VentAdj_CtrlModel_B.VentPassengerRunType);
  Ecual_CanSetPasVentLvl(Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel);
  Rte_SetVfb_ThirdVent(Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel);
  Ecual_CanSetThirdVentLvl(Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel);
  Rte_SetVfb_ThirdVentStopReason(Appl_VentAdj_CtrlModel_B.ThirdHeatStopReason);
  Rte_SetVfb_ThirdVentType(Appl_VentAdj_CtrlModel_B.VentThirdRunType);
}

/* Model step function */
void Appl_VentAdj_CtrlModel_step(void)
{
  Appl_VentAdj_CtrlModel_UpDataInputInfo();
  Appl_VentAdj_CtrlModel_LogicCtrl();
  Appl_VentAdj_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_VentAdj_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_VentAdj_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_VentAdj_CtrlModel_B), 0,
                sizeof(B_Appl_VentAdj_CtrlModel_T));

  {
    Appl_VentAdj_CtrlModel_B.RunType = enVentType_EN_VENT_TYPE_NONE;
    Appl_VentAdj_CtrlModel_B.VentDriverRunType = enVentType_EN_VENT_TYPE_NONE;
    Appl_VentAdj_CtrlModel_B.VentPassengerRunType = enVentType_EN_VENT_TYPE_NONE;
    Appl_VentAdj_CtrlModel_B.VentThirdRunType = enVentType_EN_VENT_TYPE_NONE;
    Appl_VentAdj_CtrlModel_B.DrVentStopReason =
      enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.ThirdHeatStopReason =
      enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.PaVentStopReason =
      enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason_n = enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason_l = enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason_nd =
      enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason_lr =
      enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.StopReason_g = enVentStopReason_EN_VENT_STOP_R_NONE;
    Appl_VentAdj_CtrlModel_B.OriginalDrVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.OriginalPaVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Original3rdVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.OutDrCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.OutPaCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Out3rdCANVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.DiagDrVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.DiagPaVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Diag3rdVentLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.InLevel = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.InLevel_f = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.InLevel_j = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_o = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_ip = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_p = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_b = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_c = enVentLvlSts_EN_VENT_LVL_OFF;
    Appl_VentAdj_CtrlModel_B.Level_h = enVentLvlSts_EN_VENT_LVL_OFF;
  }

  /* exported global signals */
  VentAdj_DrVentStopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
  VentAdj_PaVentStopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
  VentAdj_ThirdVentStopReason = enVentStopReason_EN_VENT_STOP_R_NONE;
  VentAdj_D_SimuIndex_DRVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentAdj_D_SimuIndex_PAVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentAdj_D_SimuIndex_ThirdVent = enVentLvlSts_EN_VENT_LVL_OFF;
  VentAdj_DriverDiagCmd = enVentIoCmdLvl_EN_VENT_IO_LVL_NONE;
  VentAdj_PassengerDiagCmd = enVentIoCmdLvl_EN_VENT_IO_LVL_NONE;
  VentAdj_ThirdDiagCmd = enVentIoCmdLvl_EN_VENT_IO_LVL_NONE;
  VentAdj_DriverCmdFaultSts = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_DriverCmdFaultSts4DTC = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_PasCmdFaultSts = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_PasCmdFaultSts4DTC = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_ThirdCmdFaultSts = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_ThirdCmdFaultSts4DTC = enVentCmdFault_EN_VENT_FAULT_NONE;
  VentAdj_CarType = enProjectType_EN_PROJECT_P20;
  VentAdj_PowerMode = enPowerModeSts_EN_OFF;
  VentAdj_VoltMode = enFinalPowerMode_EN_STOP_VOLT;
  VentAdj_3rdHeatFlg = ((INT8U)0U);
  VentAdj_CanDrvVentLvl = ((INT8U)0U);
  VentAdj_CanPasVentLvl = ((INT8U)0U);
  VentAdj_CanThirdVentLvl = ((INT8U)0U);
  VentAdj_DrHeatFlg = ((INT8U)0U);
  VentAdj_DrVentFlg = ((INT8U)0U);
  VentAdj_DriverEnableConfig = ((INT8U)0U);
  VentAdj_DriverHMI_VentMessage = ((INT8U)0U);
  VentAdj_DriverTbox_VentMessage = ((INT8U)0U);
  VentAdj_Driver_HMI_HeatMsg = ((INT8U)0U);
  VentAdj_Driver_Tbox_HeatMsg = ((INT8U)0U);
  VentAdj_EngineRunFlag = ((INT8U)0U);
  VentAdj_PaHeatFlg = ((INT8U)0U);
  VentAdj_PaVentFlg = ((INT8U)0U);
  VentAdj_PassengerEnableConfig = ((INT8U)0U);
  VentAdj_PassengerHMI_VentMessage = ((INT8U)0U);
  VentAdj_PassengerTbox_VentMessage = ((INT8U)0U);
  VentAdj_Passenger_HMI_HeatMsg = ((INT8U)0U);
  VentAdj_Passenger_Tbox_HeatMsg = ((INT8U)0U);
  VentAdj_RecoverDefaultFlag = ((INT8U)0U);
  VentAdj_RemoteModeFlag = ((INT8U)0U);
  VentAdj_RunMaxTime = ((INT8U)0U);
  VentAdj_ThirdEnableConfig = ((INT8U)0U);
  VentAdj_ThirdHMI_VentMessage = ((INT8U)0U);
  VentAdj_ThirdTbox_VentMessage = ((INT8U)0U);
  VentAdj_Third_HMI_HeatMsg = ((INT8U)0U);
  VentAdj_Third_Tbox_HeatMsg = ((INT8U)0U);
  VentAdj_TimeOutPrm = ((INT8U)0U);
  VentAdj_VehicleRunFlag = ((INT8U)0U);
  VentAdj_VentMsgLostFlag = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_VentAdj_CtrlModel_DW, 0,
                sizeof(DW_Appl_VentAdj_CtrlModel_T));
  Appl_VentAdj_CtrlModel_UpDataInputInfo_Init();
  Appl_VentAdj_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
