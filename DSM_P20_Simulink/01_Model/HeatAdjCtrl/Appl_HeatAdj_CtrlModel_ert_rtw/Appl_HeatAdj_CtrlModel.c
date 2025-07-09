/*
 * File: Appl_HeatAdj_CtrlModel.c
 *
 * Code generated for Simulink model 'Appl_HeatAdj_CtrlModel'.
 *
 * Model version                  : V1.00
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun 10 14:45:13 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Appl_HeatAdj_CtrlModel.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef D_1stLevel_36
#error The variable for the parameter "D_1stLevel_36" is not defined
#endif

#ifndef D_2ndLevel_39
#error The variable for the parameter "D_2ndLevel_39" is not defined
#endif

#ifndef D_3rdLevel_45
#error The variable for the parameter "D_3rdLevel_45" is not defined
#endif

#ifndef D_3rdLevel_48
#error The variable for the parameter "D_3rdLevel_48" is not defined
#endif

#ifndef D_SwsLevel_Temp
#error The variable for the parameter "D_SwsLevel_Temp" is not defined
#endif

#ifndef FALSE
#error The variable for the parameter "FALSE" is not defined
#endif

#ifndef TRUE
#error The variable for the parameter "TRUE" is not defined
#endif

#ifndef D_DRVHEAT_PID_D
#error The variable for the parameter "D_DRVHEAT_PID_D" is not defined
#endif

#ifndef D_DRVHEAT_PID_I
#error The variable for the parameter "D_DRVHEAT_PID_I" is not defined
#endif

#ifndef D_DRVHEAT_PID_P
#error The variable for the parameter "D_DRVHEAT_PID_P" is not defined
#endif

#ifndef D_HEAT_HEAT_DEF
#error The variable for the parameter "D_HEAT_HEAT_DEF" is not defined
#endif

#ifndef OFF
#error The variable for the parameter "OFF" is not defined
#endif

#ifndef ON
#error The variable for the parameter "ON" is not defined
#endif

/* Named constants for Chart: '<S9>/CANAquireFunction' */
#define Appl_HeatAdj_CtrlModel_IN_CloseSts ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_HeatDisable ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_ValidSts ((INT8U)3U)

/* Named constants for Chart: '<S30>/LevelLimit' */
#define Appl_HeatAdj_CtrlModel_IN_Default ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_ForbidStatus ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_k ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_Run  ((INT8U)3U)

/* Named constants for Chart: '<S39>/Timeout' */
#define Appl_HeatAdj_CtrlModel_IN_Default_c ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_kh ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_TimeCountStatus ((INT8U)2U)

/* Named constants for Chart: '<S34>/StopFunction' */
#define Appl_HeatAdj_CtrlModel_IN_Default_o ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_p ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_ValidSts_g ((INT8U)2U)

/* Named constants for Chart: '<S58>/HeatOut' */
#define Appl_HeatAdj_CtrlModel_IN_AllOut ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_j ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_None ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_PwmOut ((INT8U)3U)

/* Named constants for Chart: '<S105>/OppositeMessageDeal' */
#define Appl_HeatAdj_CtrlModel_IN_Default_p ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_Fault ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_i ((INT8U)0U)

/* Named constants for Chart: '<S118>/Function' */
#define Appl_HeatAdj_CtrlModel_IN_Default_l ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_HeatConflict ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_h ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_Valid ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_VentilateConflict ((INT8U)3U)

/* Named constants for Chart: '<S126>/OppositeMessageDeal' */
#define Appl_HeatAdj_CtrlModel_IN_HMIInit ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_HMIValid ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_hk ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_TboxInit ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_TboxValid ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_TotalInit ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_TotalValid ((INT8U)2U)

/* Named constants for Chart: '<S37>/Timeout' */
#define Appl_HeatAdj_CtrlModel_IN_Default_m ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_Init ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_TimeCountStatus_l ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_TimeoutSts ((INT8U)2U)

/* Named constants for Chart: '<S38>/Timeout' */
#define Appl_HeatAdj_CtrlModel_IN_Default_mn ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_Init_n ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eq ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_TimeCountStatus_c ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_TimeoutSts_f ((INT8U)2U)

/* Named constants for Chart: '<S60>/HeatOut' */
#define Appl_HeatAdj_CtrlModel_IN_AllOut_d ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eu ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_None_c ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_PwmOut_o ((INT8U)3U)

/* Named constants for Chart: '<S5>/HeatLevelDeal' */
#define Appl_HeatAdj_CtrlModel_IN_BM400_ThirdHeatLevelDeal ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5 ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_P20_SteerWheeling ((INT8U)2U)

/* Named constants for Chart: '<S5>/OutputDeal' */
#define Appl_HeatAdj_CtrlModel_IN_Default_h ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_ErrSts ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_FalseSts ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_Init_c ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_ProjectP20 ((INT8U)2U)
#define Appl_HeatAdj_CtrlModel_IN_Run_k ((INT8U)2U)

/* Named constants for Chart: '<S90>/Deal' */
#define Appl_HeatAdj_CtrlModel_IN_Default_f ((INT8U)1U)
#define Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_db ((INT8U)0U)
#define Appl_HeatAdj_CtrlModel_IN_ValidSts_p ((INT8U)2U)

/* Exported block signals */
enVehicleRunType HeatAdj_VCU_VehRunSta;/* '<S89>/HeatAdj_VCU_VehRunSta'
                                        * Vehicle Running Status&#10;整车运行状态&#10;0x0：HV OFF&#10;0x1：HV ON&#10;0x2：Ready&#10;0x3：Invalid
                                        */
enProjectType HeatAdj_CarType;         /* '<S89>/HeatAdj_CarType'
                                        * 车型：C62X、C52X…&#10;0：P20车型&#10;1：BM400车型
                                        */
enPowerModeSts HeatAdj_PowerMode;      /* '<S89>/HeatAdj_PowerMode'
                                        * 整车电源档位&#10;0 ： OFF&#10;1 ： ACC&#10;2 ： ON&#10;3 ： CRANK
                                        */
enHeatStopReason HeatAdj_DrHeatStopReason;/* '<S89>/HeatAdj_DrHeatStopReason'
                                           * 主驾加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                           */
enHeatStopReason HeatAdj_PaHeatStopReason;/* '<S89>/HeatAdj_PaHeatStopReason'
                                           * 副驾加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                           */
enHeatStopReason HeatAdj_ThirdHeatStopReason;/* '<S89>/HeatAdj_ThirdHeatStopReason '
                                              * 三排加热禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能
                                              */
enHeatNtcFault HeatAdj_DriverNTCFaultSts;/* '<S89>/HeatAdj_DriverNTCFaultSts'
                                          * 主驾加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                          */
enHeatNtcFault HeatAdj_PassengerNTCFaultSts;/* '<S89>/HeatAdj_PassengerNTCFaultSts '
                                             * 副驾加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                             */
enHeatNtcFault HeatAdj_ThirdNTCFaultSts;/* '<S89>/HeatAdj_ThirdNTCFaultSts'
                                         * 三排加热NTC故障状态&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误
                                         */
enHeatLvlSts HeatAdj_D_SimuIndex_DRHeat;/* '<S89>/HeatAdj_D_SimuIndex_DRHeat'
                                         * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                         */
enHeatLvlSts HeatAdj_D_SimuIndex_PAHeat;/* '<S89>/HeatAdj_D_SimuIndex_PAHeat'
                                         * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                         */
enHeatLvlSts HeatAdj_D_SimuIndex_ThirdHeat;/* '<S89>/HeatAdj_D_SimuIndex_ThirdHeat'
                                            * 加热档位状态：&#10;0：OFF&#10;1：LV1&#10;2：LV2&#10;3：LV3
                                            */
enHeatIoCmdLvl HeatAdj_DriverDiagCmd;  /* '<S89>/HeatAdj_DriverDiagCmd'
                                        * 主驾加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                        */
enHeatIoCmdLvl HeatAdj_PassengerDiagCmd;/* '<S89>/HeatAdj_PassengerDiagCmd'
                                         * 副驾加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                         */
enHeatIoCmdLvl HeatAdj_ThirdDiagCmd;   /* '<S89>/HeatAdj_ThirdDiagCmd'
                                        * 三排加热诊断IO控制命令&#10;0：退出控制&#10;1：OFF&#10;2：level1&#10;3：level2&#10;4：level3
                                        */
enHeatCmdFault HeatAdj_DriverCmdFaultSts;/* '<S89>/HeatAdj_DriverCmdFaultSts'
                                          * 主驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                          */
enHeatCmdFault HeatAdj_DriverCmdFaultSts4DTC;/* '<S89>/HeatAdj_DriverCmdFaultSts4DTC'
                                              * 主驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                              */
enHeatCmdFault HeatAdj_PassengerCmdFaultSts;/* '<S89>/HeatAdj_PassengerCmdFaultSts'
                                             * 副驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                             */
enHeatCmdFault HeatAdj_PassengerCmdFaultSts4DTC;/* '<S89>/HeatAdj_PassengerCmdFaultSts4DTC'
                                                 * 副驾加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                                 */
enHeatCmdFault HeatAdj_ThirdCmdFaultSts;/* '<S89>/HeatAdj_ThirdCmdFaultSts'
                                         * 三排加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                         */
enHeatCmdFault HeatAdj_ThirdCmdFaultSts4DTC;/* '<S89>/HeatAdj_ThirdCmdFaultSts4DTC'
                                             * 三排加热输出故障状态&#10;0：无故障&#10;1：短路到地&#10;2：开路
                                             */
enFinalPowerMode HeatAdj_VoltMode;     /* '<S89>/HeatAdj_VoltMode'
                                        * 整车电压模式&#10;0 ： StopVolt&#10;1 ： LowVolt&#10;2 ： NormalVolt&#10;3 ： HighVolt&#10;4 ： OverVolt
                                        */
enEngineType HeatAdj_ECMD_EngineStatus;/* '<S89>/HeatAdj_ECMD_EngineStatus'
                                        * 发动机运行状态
                                        */
INT16U HeatAdj_DrHeatNtcAdc;           /* '<S89>/HeatAdj_DrHeatNtcAdc'
                                        * NTC 温度值
                                        */
INT16U HeatAdj_PaHeatNtcAdc;           /* '<S89>/HeatAdj_PaHeatNtcAdc'
                                        * NTC 温度值
                                        */
INT16U HeatAdj_ThirdHeatNtcAdc;        /* '<S89>/HeatAdj_ThirdHeatNtcAdc'
                                        * NTC 温度值
                                        */
INT8U HeatAdj_CanDrvHeatLvl;           /* '<S89>/HeatAdj_CanDrvHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
INT8U HeatAdj_CanPasHeatLvl;           /* '<S89>/HeatAdj_CanPasHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
INT8U HeatAdj_CanThirdHeatLvl;         /* '<S89>/HeatAdj_CanThirdHeatLvl'
                                        * 输出档位信号&#10;0:1档&#10;1:2档&#10;2:3档
                                        */
INT8U HeatAdj_DCDCSwitchSts;           /* '<S89>/HeatAdj_DCDCSwitchSts'
                                        * 获取DCDC节点开关使能状态 DSM_BM400专用接口，通风加热前置条件为Enable&#10;0x0：Disable&#10;0x1：Enable
                                        */
INT8U HeatAdj_DrVentFlg;               /* '<S89>/HeatAdj_DrVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U HeatAdj_DriverHMI_Message;       /* '<S89>/HeatAdj_DriverHMI_Message'
                                        * 主驾加热HMI等级报文
                                        */
INT8U HeatAdj_DriverTbox_Message;      /* '<S89>/HeatAdj_DriverTbox_Message'
                                        * 主驾加热Tbox等级报文
                                        */
INT8U HeatAdj_DriverVentEnableConfig;  /* '<S89>/HeatAdj_DriverVentEnableConfig'
                                        * 主驾通风使能配置&#10;0：不存在&#10;1：存在
                                        */
INT8U HeatAdj_Driver_HMI_VentilateMsg; /* '<S89>/HeatAdj_Driver_HMI_VentilateMsg'
                                        * 主驾通风HMI报文
                                        */
INT8U HeatAdj_Driver_Tbox_VentilateMsg;/* '<S89>/HeatAdj_Driver_Tbox_VentilateMsg'
                                        * 主驾通风Tbox报文
                                        */
INT8U HeatAdj_HeatMsgLostFlag;         /* '<S89>/HeatAdj_HeatMsgLostFlag'
                                        * 加热报文掉线
                                        */
INT8U HeatAdj_MemDiagDrHeatConfig;     /* '<S89>/HeatAdj_MemDiagDrHeatConfig'
                                        * 主驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemDiagDrHeatFlg;        /* '<S89>/HeatAdj_MemDiagDrHeatFlg'
                                        * 主驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemDiagPaHeatConfig;     /* '<S89>/HeatAdj_MemDiagPaHeatConfig'
                                        * 副驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemDiagPaHeatFlg;        /* '<S89>/HeatAdj_MemDiagPaHeatFlg'
                                        * 副驾通风加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemDiagThirdHeatConfig;  /* '<S89>/HeatAdj_MemDiagThirdHeatConfig'
                                        * P20方向盘加热使能配置（P20诊断）&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemIndexDrHeatConfig;    /* '<S89>/HeatAdj_MemIndexDrHeatConfig'
                                        * 加热配置&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemIndexPaHeatConfig;    /* '<S89>/HeatAdj_MemIndexPaHeatConfig'
                                        * 加热配置&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_MemIndexThirdHeatConfig; /* '<S89>/HeatAdj_MemIndexThirdHeatConfig'
                                        * 加热配置&#10;0：无&#10;1：有
                                        */
INT8U HeatAdj_P20_PHEV_EngineCfg;      /* '<S89>/HeatAdj_P20_PHEV_EngineCfg'
                                        * 加热P20PHEV发动机使能配置&#10;0：无加热P20PHEV发动机&#10;1：有加热P20PHEV发动机
                                        */
INT8U HeatAdj_PaVentFlg;               /* '<S89>/HeatAdj_PaVentFlg'
                                        * 通风使能配置&#10;0：禁能&#10;1：使能
                                        */
INT8U HeatAdj_PassengerHMI_Message;    /* '<S89>/HeatAdj_PassengerHMI_Message'
                                        * 副驾加热HMI等级报文
                                        */
INT8U HeatAdj_PassengerTbox_Message;   /* '<S89>/HeatAdj_PassengerTbox_Message'
                                        * 副驾加热Tbox等级报文
                                        */
INT8U HeatAdj_PassengerVentEnableConfig;/* '<S89>/HeatAdj_PassengerVentEnableConfig'
                                         * 二排通风配置&#10;0：不存在&#10;1：存在
                                         */
INT8U HeatAdj_Passenger_HMI_VentilateMsg;/* '<S89>/HeatAdj_Passenger_HMI_VentilateMsg'
                                          * 副驾通风HMI报文
                                          */
INT8U HeatAdj_Passenger_Tbox_VentilateMsg;/* '<S89>/HeatAdj_Passenger_Tbox_VentilateMsg'
                                           * 副驾通风Tbox报文
                                           */
INT8U HeatAdj_PlatformEngineEnableConfig;/* '<S89>/HeatAdj_PlatformEngineEnableConfig'
                                          * 加热发动机使能配置&#10;0：无发动机使能&#10;1：有发动机使能
                                          */
INT8U HeatAdj_PlatformVehicleEnableConfig;/* '<S89>/HeatAdj_PlatformVehicleEnableConfig'
                                           * 加热整车运行使能配置&#10;0：无整车运行状态判断使能&#10;1：有整车运行状态判断使能
                                           */
INT8U HeatAdj_RecoverDefaultFlag;      /* '<S89>/HeatAdj_RecoverDefaultFlag'
                                        * 恢复出厂命令&#10;0：无效；&#10;1：有效
                                        */
INT8U HeatAdj_RemoteEnableConfig;      /* '<S89>/HeatAdj_RemoteEnableConfig'
                                        * 加热远程使能配置&#10;0：无远程使能&#10;1：有远程使能
                                        */
INT8U HeatAdj_RemoteMsgLostFlag;       /* '<S89>/HeatAdj_RemoteMsgLostFlag'
                                        * 加热远程报文掉线
                                        */
INT8U HeatAdj_RunMaxTime;              /* '<S89>/HeatAdj_RunMaxTime'
                                        * 加热超时时间配置&#10;0：无超时&#10;1-255min
                                        */
INT8U HeatAdj_TboxRemoteSts;           /* '<S89>/HeatAdj_TboxRemoteSts'
                                        * 加热远程模式状态&#10;0：无远程模式&#10;1：进远程模式
                                        */
INT8U HeatAdj_ThirdDiagMaxTime;        /* '<S89>/HeatAdj_ThirdDiagMaxTime'
                                        * 方向盘加热最大时间，单位：s
                                        */
INT8U HeatAdj_ThirdHMI_Message;        /* '<S89>/HeatAdj_ThirdHMI_Message'
                                        * 三排加热HMI等级报文
                                        */
INT8U HeatAdj_ThirdTbox_Message;       /* '<S89>/HeatAdj_ThirdTbox_Message'
                                        * 三排加热Tbox等级报文
                                        */
INT8U HeatAdj_ThirdVentEnableConfig;   /* '<S89>/HeatAdj_ThirdVentEnableConfig'
                                        * 三排通风使能配置&#10;0：不存在&#10;1：存在
                                        */
INT8U HeatAdj_Third_HMI_VentilateMsg;  /* '<S89>/HeatAdj_Third_HMI_VentilateMsg'
                                        * 三排通风HMI报文
                                        */
INT8U HeatAdj_Third_Tbox_VentilateMsg; /* '<S89>/HeatAdj_Third_Tbox_VentilateMsg'
                                        * 三排通风Tbox报文
                                        */
INT8U HeatAdj_TimeOutPrm;              /* '<S89>/HeatAdj_TimeOutPrm'
                                        * 加热超时使能配置&#10;0：禁能&#10;1：使能
                                        */

/* Constant parameters (default storage) */
const ConstP_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_ConstP =
{
  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S96>/Constant5'
   */
  {
    0U, 20U
  }
};

/* Block signals (default storage) */
B_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_B;

/* Block states (default storage) */
DW_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_DW;

/* Real-time model */
RT_MODEL_Appl_HeatAdj_CtrlModel_T Appl_HeatAdj_CtrlModel_M_;
RT_MODEL_Appl_HeatAdj_CtrlModel_T *const Appl_HeatAdj_CtrlModel_M =
  &Appl_HeatAdj_CtrlModel_M_;

/* Exported data definition */

/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile INT32U CAL_LEVEL3_TIMEOUT = 780000U;/* 3档加热超时切温度（13min） */
const volatile INT32U CAL_SW_20min_TIMEOUT = 1200000U;/* 方向盘加热计时（20min） */
static void mul_wide_u32(INT32U in0, INT32U in1, INT32U *ptrOutBitsHi, INT32U
  *ptrOutBitsLo);
static INT32U mul_u32_sat(INT32U a, INT32U b);
static void Appl_HeatAdj_CtrlModel_CANAquireFunction_Init(INT8U *rty_IVISwCan,
  DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_CANAquireFunction(INT8U rtu_HeatLevel, INT8U
  rtu_IVISwsHeat, enPowerModeSts rtu_PowerMode, INT8U *rty_IVISwCan,
  DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init(INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_LevelAquireFunction(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, INT8U rtu_CAN_Message, enHeatStopReason
  rtu_DisableSts, INT8U rtu_ComPCFlag, INT8U rtu_CanLvl, INT8U rtu_Type, INT8U
  *rty_Level, DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1_Init(INT8U *rty_Level,
  DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1(INT8U rtu_EnableCfg,
  INT8U rtu_CAN_Message, enHeatStopReason rtu_DisableSts, INT8U rtu_ComPCFlag,
  INT8U *rty_Level, DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_MixConflic(INT8U rtu_MixFlg, INT8U rtu_Valid,
  INT8U *rty_OutValid);
static void Appl_HeatAdj_CtrlModel_LevelLimitFunction_Init(enHeatLvlSts
  *rty_Level, enHeatStopReason *rty_StopReason, enHeatStopReason
  *rty_CANStopReason, DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_LevelLimitFunction(enHeatLvlSts
  rtu_OriginalLevel, INT8U rtu_Error, INT8U rtu_OppositeCmd, enProjectType
  rtu_CarType, INT8U rtu_Heat_CanMessageLostFlag, INT8U
  rtu_Heat_RecoverDefaultFlag, enHeatLvlSts *rty_Level, enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(INT32U *rty_OutTs);
static void Appl_HeatAdj_CtrlModel_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
  INT32U *rty_OutTs);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction2_Init(enHeatLvlSts *rty_Level,
  INT8U *rty_TimeoutFlag, DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction2(enHeatLvlSts rtu_InLevel,
  INT32U rtu_SwTimeout, enHeatLvlSts *rty_Level, INT8U *rty_TimeoutFlag,
  DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_StopFunction_Init(enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_StopFunction(enHeatStopReason rtu_ComStop,
  INT8U rtu_Timeout, enHeatStopReason rtu_ComCANStop, enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_DiagnoseFunction_Init(enHeatLvlSts *rty_Level,
  enHeatType *rty_Type, DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_DiagnoseFunction(INT8U rtu_DiagCommand,
  enHeatLvlSts rtu_InLevel, enHeatType rtu_CurrentType, enHeatLvlSts *rty_Level,
  enHeatType *rty_Type, DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_PidGetPwm_Init(INT16U *rty_PwmCnt,
  DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_PidGetPwm(INT16U rtu_CurrentTemp, INT16U
  rtu_SetTemp, INT16U *rty_PwmCnt, DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T
  *localDW);
static void Appl_HeatAdj_CtrlModel_HeatOutFunction_Init(INT8U *rty_HeatOutGpio,
  INT8U *rty_HeatOutPwmCnt, B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localB,
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_HeatOutFunction(INT16U rtu_SetTemp, INT16U
  rtu_CurrentTemp, enHeatLvlSts rtu_HeatLvl, INT8U *rty_HeatOutGpio, INT8U
  *rty_HeatOutPwmCnt, B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localB,
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(INT8U *rty_HeatError,
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_ErrorFunction2(INT8U rtu_FirstFaultSts, INT8U
  rtu_SecondFaultSts, INT8U *rty_HeatError,
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_MsgConflictFunction2_Init(INT8U
  *rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_MsgConflictFunction2(INT8U rtu_CarTypeCfg,
  INT8U rtu_HMI_Message, INT8U rtu_Tbox_Message, INT8U rtu_VentValidFlag, INT8U *
  rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_OppositeMessageDeal_Init(INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_OppositeMessageDeal(enProjectType
  rtu_CarTypeCfg, INT8U rtu_RemoteModeFlag, INT8U rtu_HMI_Message, INT8U
  rtu_Tbox_Message, INT8U rtu_VentCfg, INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T *localDW);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS(void);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction_Init(void);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction(void);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p(void);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction1_Init(void);
static void Appl_HeatAdj_CtrlModel_TimeoutFunction1(void);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k(void);
static void Appl_HeatAdj_CtrlModel_TempFunction_Init(void);
static void Appl_HeatAdj_CtrlModel_TempFunction(void);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa(void);
static void Appl_HeatAdj_CtrlModel_TempFunction1_Init(void);
static void Appl_HeatAdj_CtrlModel_TempFunction1(void);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h(void);
static void Appl_HeatAdj_CtrlModel_TempFunction2_Init(void);
static void Appl_HeatAdj_CtrlModel_TempFunction2(void);
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e(void);
static void Appl_HeatAdj_CtrlModel_HeatOutFunction2_Init(void);
static void Appl_HeatAdj_CtrlModel_HeatOutFunction2(void);
static void Appl_HeatAdj_CtrlModel_LogicCtrl_Init(void);
static void Appl_HeatAdj_CtrlModel_LogicCtrl(void);
static void Appl_HeatAdj_CtrlModel_RTE(void);
static void Appl_HeatAdj_CtrlModel_UpDataInputInfo_Init(void);
static void Appl_HeatAdj_CtrlModel_UpDataInputInfo(void);
static void Appl_HeatAdj_CtrlModel_UpDataOutputInfo(void);

/* Forward declaration for local functions */
static void Appl_HeatAdj_CtrlModel_inner_default_LevelAquire(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, INT8U rtu_CAN_Message, enHeatStopReason
  rtu_DisableSts, INT8U rtu_ComPCFlag, INT8U rtu_CanLvl, INT8U rtu_Type, INT8U
  *rty_Level);

/* Forward declaration for local functions */
static void Appl_HeatAdj_CtrlModel_inner_default_LevelAquire_e(INT8U
  rtu_EnableCfg, INT8U rtu_CAN_Message, enHeatStopReason rtu_DisableSts, INT8U
  rtu_ComPCFlag, INT8U *rty_Level);

/* Forward declaration for local functions */
static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts(INT32S input);

/* Forward declaration for local functions */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl(void);

/* Forward declaration for local functions */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl_g(void);

/* Forward declaration for local functions */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl_h(void);

/* Forward declaration for local functions */
static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(INT32S input);
static void Appl_HeatA_enter_internal_BM400_ThirdHeatLevelDeal(INT8U
  *EnableCfg_l, enProjectType *CarTypeCfg_me, INT8U *CAN_Message_e,
  enHeatStopReason *DisableSts_he, INT8U *ComPCFlag_lf, INT8U *CanLvl_pr);
static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts(INT32S input);
static void mul_wide_u32(INT32U in0, INT32U in1, INT32U *ptrOutBitsHi, INT32U
  *ptrOutBitsLo)
{
  INT32U outBitsLo;
  INT32U in0Lo;
  INT32U in0Hi;
  INT32U in1Lo;
  INT32U in1Hi;
  INT32U productHiLo;
  INT32U productLoHi;
  in0Hi = in0 >> 16U;
  in0Lo = in0 & 65535U;
  in1Hi = in1 >> 16U;
  in1Lo = in1 & 65535U;
  productHiLo = in0Hi * in1Lo;
  productLoHi = in0Lo * in1Hi;
  in0Lo *= in1Lo;
  in1Lo = 0U;
  outBitsLo = (productLoHi << 16U) + in0Lo;
  if (outBitsLo < in0Lo)
  {
    in1Lo = 1U;
  }

  in0Lo = outBitsLo;
  outBitsLo += productHiLo << 16U;
  if (outBitsLo < in0Lo)
  {
    in1Lo++;
  }

  *ptrOutBitsHi = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi)
    + in1Lo;
  *ptrOutBitsLo = outBitsLo;
}

static INT32U mul_u32_sat(INT32U a, INT32U b)
{
  INT32U result;
  INT32U u32_chi;
  mul_wide_u32(a, b, &u32_chi, &result);
  if (u32_chi)
  {
    result = MAX_uint32_T;
  }

  return result;
}

/* System initialize for function-call system: '<S6>/CANAquireFunction' */
static void Appl_HeatAdj_CtrlModel_CANAquireFunction_Init(INT8U *rty_IVISwCan,
  DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c45_Appl_HeatAdj_CtrlModel = 0U;
  localDW->is_c45_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD;
  localDW->TempMsg = 0U;
  localDW->ValidCnt = 0U;
  *rty_IVISwCan = 0U;
}

/* Output and update for function-call system: '<S6>/CANAquireFunction' */
static void Appl_HeatAdj_CtrlModel_CANAquireFunction(INT8U rtu_HeatLevel, INT8U
  rtu_IVISwsHeat, enPowerModeSts rtu_PowerMode, INT8U *rty_IVISwCan,
  DW_CANAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  INT8U IVISwsHeat_prev;
  INT32S tmp;
  if (localDW->temporalCounter_i1 < 7U)
  {
    localDW->temporalCounter_i1++;
  }

  IVISwsHeat_prev = localDW->IVISwsHeat_start;
  localDW->IVISwsHeat_start = rtu_IVISwsHeat;
  if (localDW->is_active_c45_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c45_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_c45_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_HeatDisable;
    *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_NONE;
    localDW->TempMsg = 0U;
  }
  else
  {
    switch (localDW->is_c45_Appl_HeatAdj_CtrlModel)
    {
     case Appl_HeatAdj_CtrlModel_IN_CloseSts:
      /* IVI_SwsHeatSw = 0x0:Not Pressed
         || 事件报文超时后（Event = 20ms） */
      if ((0 == rtu_IVISwsHeat) || (localDW->temporalCounter_i1 >= 5))
      {
        localDW->is_c45_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_HeatDisable;
        *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_NONE;
        localDW->TempMsg = 0U;
      }
      break;

     case Appl_HeatAdj_CtrlModel_IN_HeatDisable:
      /* (非OFF 电 && 加热未启动 && 开关变为有效)
         || 加热已开启 */
      if (((enPowerModeSts_EN_OFF != rtu_PowerMode) && ((INT32S)
            enHeatLvlSts_EN_HEAT_LVL_OFF == rtu_HeatLevel) && ((IVISwsHeat_prev
             != localDW->IVISwsHeat_start) && (localDW->IVISwsHeat_start == 1)))
          || ((INT32S)enHeatLvlSts_EN_HEAT_LVL_OFF != rtu_HeatLevel))
      {
        localDW->is_c45_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_ValidSts;

        /* 加热已通过其他方式开启 */
        if (((INT32S)enHeatLvlSts_EN_HEAT_LVL_OFF != rtu_HeatLevel) && ((INT32S)
             enSteerHeatType_EN_STEER_OPEN != localDW->TempMsg))
        {
          *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_NONE;
        }
        else
        {
          *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_OPEN;
          localDW->TempMsg = (INT8U)enSteerHeatType_EN_STEER_OPEN;
        }

        if (localDW->ValidCnt < 3)
        {
          tmp = localDW->ValidCnt + 1;
          if (tmp > 255)
          {
            tmp = 255;
          }

          localDW->ValidCnt = (INT8U)tmp;
        }
        else
        {
          localDW->ValidCnt = 3U;
        }
      }
      break;

     default:
      /* (非OFF 电 && 加热已启动 && 开关变为有效)
         || OFF电 */
      tmp = enHeatLvlSts_EN_HEAT_LVL_OFF;
      if (((enPowerModeSts_EN_OFF != rtu_PowerMode) && (tmp != rtu_HeatLevel) &&
           ((IVISwsHeat_prev != localDW->IVISwsHeat_start) &&
            (localDW->IVISwsHeat_start == 1))) || (enPowerModeSts_EN_OFF ==
           rtu_PowerMode))
      {
        localDW->TempMsg = 0U;
        localDW->ValidCnt = 0U;
        localDW->is_c45_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_CloseSts;
        localDW->temporalCounter_i1 = 0U;
        *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_CLOSE;
      }
      else
      {
        /* 其他模式、故障关闭加热 */
        if ((tmp == rtu_HeatLevel) && (3 == localDW->ValidCnt))
        {
          localDW->ValidCnt = 0U;
          localDW->is_c45_Appl_HeatAdj_CtrlModel =
            Appl_HeatAdj_CtrlModel_IN_HeatDisable;
          *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_NONE;
          localDW->TempMsg = 0U;
        }
        else
        {
          /* 加热已通过其他方式开启 */
          if ((tmp != rtu_HeatLevel) && ((INT32S)enSteerHeatType_EN_STEER_OPEN
               != localDW->TempMsg))
          {
            *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_NONE;
          }
          else
          {
            *rty_IVISwCan = (INT8U)enSteerHeatType_EN_STEER_OPEN;
            localDW->TempMsg = (INT8U)enSteerHeatType_EN_STEER_OPEN;
          }

          if (localDW->ValidCnt < 3)
          {
            tmp = localDW->ValidCnt + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            localDW->ValidCnt = (INT8U)tmp;
          }
          else
          {
            localDW->ValidCnt = 3U;
          }
        }
      }
      break;
    }
  }
}

/* Function for Chart: '<S10>/LevelAquireFunction' */
static void Appl_HeatAdj_CtrlModel_inner_default_LevelAquire(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, INT8U rtu_CAN_Message, enHeatStopReason
  rtu_DisableSts, INT8U rtu_ComPCFlag, INT8U rtu_CanLvl, INT8U rtu_Type, INT8U
  *rty_Level)
{
  INT8U TempMsg;
  BOOL StopFlag;
  INT32S tmp;
  BOOL guard1 = false;

  /* 加热功能禁能
     || 通用前置条件不满足) */
  if ((enHeatStopReason_EN_HEAT_STOP_R_NONE != rtu_DisableSts) || (((BOOL)FALSE)
       == rtu_EnableCfg) || (((BOOL)TRUE) != rtu_ComPCFlag))
  {
    *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
    StopFlag = ((BOOL)TRUE);
  }
  else
  {
    StopFlag = ((BOOL)FALSE);
  }

  if (((BOOL)FALSE) == StopFlag)
  {
    guard1 = false;
    if (enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg)
    {
      /*  open 信号 且为HMI控制 */
      if ((5 == rtu_CAN_Message) && (rtu_Type == ((BOOL)FALSE)))
      {
        tmp = rtu_CanLvl + 1;
        if (tmp > 255)
        {
          tmp = 255;
        }

        *rty_Level = (INT8U)tmp;
      }
      else if (4 == rtu_CAN_Message)
      {
        *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
      }
      else
      {
        tmp = rtu_CAN_Message + 1;
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
      *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
    }

    if (guard1)
    {
      if ((1 < TempMsg) && (5 > TempMsg))
      {
        switch (TempMsg)
        {
         case 2:
          *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_1;
          break;

         case 3:
          *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_2;
          break;

         default:
          *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_3;
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
    *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
  }
}

/*
 * System initialize for function-call system:
 *    '<S6>/LevelAquireFunction'
 *    '<S6>/LevelAquireFunction3'
 *    '<S6>/LevelAquireFunction1'
 *    '<S6>/LevelAquireFunction4'
 *    '<S6>/LevelAquireFunction2'
 *    '<S6>/LevelAquireFunction5'
 */
static void Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init(INT8U *rty_Level,
  DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c41_Appl_HeatAdj_CtrlModel = 0U;
  *rty_Level = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S6>/LevelAquireFunction'
 *    '<S6>/LevelAquireFunction3'
 *    '<S6>/LevelAquireFunction1'
 *    '<S6>/LevelAquireFunction4'
 *    '<S6>/LevelAquireFunction2'
 *    '<S6>/LevelAquireFunction5'
 */
static void Appl_HeatAdj_CtrlModel_LevelAquireFunction(INT8U rtu_EnableCfg,
  enProjectType rtu_CarTypeCfg, INT8U rtu_CAN_Message, enHeatStopReason
  rtu_DisableSts, INT8U rtu_ComPCFlag, INT8U rtu_CanLvl, INT8U rtu_Type, INT8U
  *rty_Level, DW_LevelAquireFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c41_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c41_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_inner_default_LevelAquire(rtu_EnableCfg,
      rtu_CarTypeCfg, rtu_CAN_Message, rtu_DisableSts, rtu_ComPCFlag, rtu_CanLvl,
      rtu_Type, rty_Level);
  }
  else
  {
    Appl_HeatAdj_CtrlModel_inner_default_LevelAquire(rtu_EnableCfg,
      rtu_CarTypeCfg, rtu_CAN_Message, rtu_DisableSts, rtu_ComPCFlag, rtu_CanLvl,
      rtu_Type, rty_Level);
  }
}

/* Function for Chart: '<S17>/SwLevelAquireFunction' */
static void Appl_HeatAdj_CtrlModel_inner_default_LevelAquire_e(INT8U
  rtu_EnableCfg, INT8U rtu_CAN_Message, enHeatStopReason rtu_DisableSts, INT8U
  rtu_ComPCFlag, INT8U *rty_Level)
{
  BOOL StopFlag;

  /* 存在禁能条件时，不再输出有效加热请求
     加热功能禁能
     || 通用前置条件不满足) */
  if ((enHeatStopReason_EN_HEAT_STOP_R_NONE != rtu_DisableSts) || (((BOOL)FALSE)
       == rtu_EnableCfg) || (((BOOL)TRUE) != rtu_ComPCFlag))
  {
    *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
    StopFlag = ((BOOL)TRUE);
  }
  else
  {
    StopFlag = ((BOOL)FALSE);
  }

  if (((BOOL)FALSE) == StopFlag)
  {
    /* P20
       0x0:无动作
       0x1:开始
       0x2:关闭
       0x3:无效值 */
    switch (rtu_CAN_Message)
    {
     case 0x02:
      *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
      break;

     case 0x01:
      /* P20
         0x0:无动作
         0x1:开始
         0x2:关闭
         0x3:无效值 */
      *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_3;
      break;

     default:
      *rty_Level = (INT8U)0xFF;
      break;
    }
  }
  else
  {
    *rty_Level = (INT8U)enHeatLvlSts_EN_HEAT_LVL_OFF;
  }
}

/*
 * System initialize for function-call system:
 *    '<S6>/SwLevelAquireFunction1'
 *    '<S6>/SwLevelAquireFunction'
 */
static void Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1_Init(INT8U *rty_Level,
  DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c49_Appl_HeatAdj_CtrlModel = 0U;
  *rty_Level = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S6>/SwLevelAquireFunction1'
 *    '<S6>/SwLevelAquireFunction'
 */
static void Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1(INT8U rtu_EnableCfg,
  INT8U rtu_CAN_Message, enHeatStopReason rtu_DisableSts, INT8U rtu_ComPCFlag,
  INT8U *rty_Level, DW_SwLevelAquireFunction1_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c49_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c49_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_inner_default_LevelAquire_e(rtu_EnableCfg,
      rtu_CAN_Message, rtu_DisableSts, rtu_ComPCFlag, rty_Level);
  }
  else
  {
    Appl_HeatAdj_CtrlModel_inner_default_LevelAquire_e(rtu_EnableCfg,
      rtu_CAN_Message, rtu_DisableSts, rtu_ComPCFlag, rty_Level);
  }
}

/* Output and update for function-call system: '<S7>/MixConflic' */
static void Appl_HeatAdj_CtrlModel_MixConflic(INT8U rtu_MixFlg, INT8U rtu_Valid,
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
 *    '<S7>/LevelLimitFunction'
 *    '<S7>/LevelLimitFunction1'
 *    '<S7>/LevelLimitFunction2'
 */
static void Appl_HeatAdj_CtrlModel_LevelLimitFunction_Init(enHeatLvlSts
  *rty_Level, enHeatStopReason *rty_StopReason, enHeatStopReason
  *rty_CANStopReason, DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c4_Appl_HeatAdj_CtrlModel = 0U;
  localDW->is_c4_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_k;
  *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
  *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
  *rty_CANStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S7>/LevelLimitFunction'
 *    '<S7>/LevelLimitFunction1'
 *    '<S7>/LevelLimitFunction2'
 */
static void Appl_HeatAdj_CtrlModel_LevelLimitFunction(enHeatLvlSts
  rtu_OriginalLevel, INT8U rtu_Error, INT8U rtu_OppositeCmd, enProjectType
  rtu_CarType, INT8U rtu_Heat_CanMessageLostFlag, INT8U
  rtu_Heat_RecoverDefaultFlag, enHeatLvlSts *rty_Level, enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_LevelLimitFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c4_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c4_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_c4_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Default;
    *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
  }
  else
  {
    switch (localDW->is_c4_Appl_HeatAdj_CtrlModel)
    {
     case Appl_HeatAdj_CtrlModel_IN_Default:
      /* 请求工作 */
      if (enHeatLvlSts_EN_HEAT_LVL_OFF != rtu_OriginalLevel)
      {
        localDW->is_c4_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_ForbidStatus;
        *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
        *rty_CANStopReason = *rty_StopReason;

        /* 存在故障 */
        if (((BOOL)TRUE) == rtu_Error)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
        }

        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
        }

        /* 恢复出厂 */
        if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
        }

        /* BM400掉线禁能 */
        if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
            (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
        }
      }
      break;

     case Appl_HeatAdj_CtrlModel_IN_ForbidStatus:
      /* 无用户请求，可准备下一轮禁能原因检测 */
      if (enHeatLvlSts_EN_HEAT_LVL_OFF == rtu_OriginalLevel)
      {
        /* 暂时屏蔽，查看是否需要一直保存禁能原因 */
        *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
        localDW->is_c4_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_Default;
        *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
      }
      else
      {
        /* 无故障
           && 互斥命令无效
           && 无恢复出厂命令
           && （BM400控制报文在线 || 非BM400车型）  */
        if ((((BOOL)TRUE) != rtu_Error) && (((BOOL)TRUE) != rtu_OppositeCmd) &&
            (((BOOL)TRUE) != rtu_Heat_RecoverDefaultFlag) &&
            ((enProjectType_EN_PROJECT_BM400 != rtu_CarType) || (((BOOL)FALSE) ==
              rtu_Heat_CanMessageLostFlag)))
        {
          /* 暂时屏蔽，查看是否需要一直保存禁能原因 */
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
          localDW->is_c4_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Run;
          *rty_Level = rtu_OriginalLevel;
          *rty_CANStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
        }
        else
        {
          /* 存在故障 */
          if (((BOOL)TRUE) == rtu_Error)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
          }

          /* 互斥命令有效 */
          if (((BOOL)TRUE) == rtu_OppositeCmd)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
          }

          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
          }

          /* BM400掉线禁能 */
          if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
              (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
          }
        }
      }
      break;

     default:
      /* 存在故障 */
      if (((BOOL)TRUE) == rtu_Error)
      {
        *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
        localDW->is_c4_Appl_HeatAdj_CtrlModel =
          Appl_HeatAdj_CtrlModel_IN_ForbidStatus;
        *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
        *rty_CANStopReason = *rty_StopReason;

        /* 存在故障 */
        if (((BOOL)TRUE) == rtu_Error)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
        }

        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
        }

        /* 恢复出厂 */
        if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
        }

        /* BM400掉线禁能 */
        if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
            (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
        }
      }
      else
      {
        /* 互斥命令有效 */
        if (((BOOL)TRUE) == rtu_OppositeCmd)
        {
          *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
          localDW->is_c4_Appl_HeatAdj_CtrlModel =
            Appl_HeatAdj_CtrlModel_IN_ForbidStatus;
          *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
          *rty_CANStopReason = *rty_StopReason;

          /* 存在故障 */
          if (((BOOL)TRUE) == rtu_Error)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
          }

          /* 互斥命令有效 */
          if (((BOOL)TRUE) == rtu_OppositeCmd)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
          }

          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
          }

          /* BM400掉线禁能 */
          if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
              (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
          }
        }
        else
        {
          /* 恢复出厂 */
          if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
          {
            *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
            localDW->is_c4_Appl_HeatAdj_CtrlModel =
              Appl_HeatAdj_CtrlModel_IN_ForbidStatus;
            *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
            *rty_CANStopReason = *rty_StopReason;

            /* 存在故障 */
            if (((BOOL)TRUE) == rtu_Error)
            {
              *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
            }

            /* 互斥命令有效 */
            if (((BOOL)TRUE) == rtu_OppositeCmd)
            {
              *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
            }

            /* 恢复出厂 */
            if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
            {
              *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
            }

            /* BM400掉线禁能 */
            if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
                (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
            {
              *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
            }
          }
          else
          {
            /* BM400掉线禁能 */
            if ((((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag) &&
                (enProjectType_EN_PROJECT_BM400 == rtu_CarType))
            {
              *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
              localDW->is_c4_Appl_HeatAdj_CtrlModel =
                Appl_HeatAdj_CtrlModel_IN_ForbidStatus;
              *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
              *rty_CANStopReason = *rty_StopReason;

              /* 存在故障 */
              if (((BOOL)TRUE) == rtu_Error)
              {
                *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FAULT;
              }

              /* 互斥命令有效 */
              if (((BOOL)TRUE) == rtu_OppositeCmd)
              {
                *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_CMD;
              }

              /* 恢复出厂 */
              if (((BOOL)TRUE) == rtu_Heat_RecoverDefaultFlag)
              {
                *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_FACTORY;
              }

              /* BM400掉线禁能 */
              if (((BOOL)TRUE) == rtu_Heat_CanMessageLostFlag)
              {
                *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_LOSS;
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

/* Output and update for function-call system: '<S49>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c = D_HAL_GET_CUR_MS_TS( );
}

/*
 * System initialize for function-call system:
 *    '<S49>/TimeDiffTs'
 *    '<S53>/TimeDiffTs'
 *    '<S76>/TimeDiffTs'
 *    '<S80>/TimeDiffTs'
 *    '<S84>/TimeDiffTs'
 *    '<S70>/TimeDiffTs'
 */
static void Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(INT32U *rty_OutTs)
{
  *rty_OutTs = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S49>/TimeDiffTs'
 *    '<S53>/TimeDiffTs'
 *    '<S76>/TimeDiffTs'
 *    '<S80>/TimeDiffTs'
 *    '<S84>/TimeDiffTs'
 *    '<S70>/TimeDiffTs'
 */
static void Appl_HeatAdj_CtrlModel_TimeDiffTs(INT32U rtu_lastTs, INT32U rtu_Ts,
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

/* System initialize for function-call system: '<S7>/TimeoutFunction' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction_Init(void)
{
  INT32U OutTs_pt;
  Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o;
  Appl_HeatAdj_CtrlModel_DW.is_active_c34_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c34_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o;
  Appl_HeatAdj_CtrlModel_DW.Timer_o = 0U;
  Appl_HeatAdj_CtrlModel_B.TimeoutFlag_b = 0U;
  Appl_HeatAdj_CtrlModel_B.Level_b = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs_pt);
}

/* Output and update for function-call system: '<S7>/TimeoutFunction' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction(void)
{
  INT32U OutTs_pt;
  enHeatLvlSts InLevel_prev_n;
  InLevel_prev_n = Appl_HeatAdj_CtrlModel_DW.InLevel_start_d;
  Appl_HeatAdj_CtrlModel_DW.InLevel_start_d = Appl_HeatAdj_CtrlModel_B.InLevel;
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c34_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c34_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c34_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_m;
    Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c34_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_m)
  {
    /* 有超时配置
       && 启动加热&&有时间值  */
    if ((((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.TimeoutPrm) &&
        (enHeatLvlSts_EN_HEAT_LVL_OFF != Appl_HeatAdj_CtrlModel_B.InLevel) &&
        (0U != Appl_HeatAdj_CtrlModel_B.MaxTime_h))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c34_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_TimeCountStatus_l;
      Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
        Appl_HeatAdj_CtrlModel_IN_Init;
      Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_HeatAdj_CtrlModel_DW.Timer_o =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
    }
    else
    {
      Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
    }
  }
  else
  {
    /* 无超时配置 */
    if ((((BOOL)TRUE) != Appl_HeatAdj_CtrlModel_B.TimeoutPrm) || (0U ==
         Appl_HeatAdj_CtrlModel_B.MaxTime_h))
    {
      switch (Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c)
      {
       case Appl_HeatAdj_CtrlModel_IN_Init:
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_HeatAdj_CtrlModel_DW.Timer_o =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o;
        break;

       case Appl_HeatAdj_CtrlModel_IN_TimeoutSts:
        Appl_HeatAdj_CtrlModel_DW.Timer_o = 0U;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_o;
        break;
      }

      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_b = ((BOOL)FALSE);
      Appl_HeatAdj_CtrlModel_DW.is_c34_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_m;
      Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
    }
    else if (Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c ==
             Appl_HeatAdj_CtrlModel_IN_Init)
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_DW.Timer_o,
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c, &OutTs_pt);
      if (OutTs_pt >= Appl_HeatAdj_CtrlModel_B.MaxTime_h)
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_HeatAdj_CtrlModel_DW.Timer_o =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
        Appl_HeatAdj_CtrlModel_B.TimeoutFlag_b = ((BOOL)TRUE);
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
          Appl_HeatAdj_CtrlModel_IN_TimeoutSts;
        Appl_HeatAdj_CtrlModel_B.Level_b = enHeatLvlSts_EN_HEAT_LVL_OFF;
      }
      else if ((InLevel_prev_n != Appl_HeatAdj_CtrlModel_DW.InLevel_start_d) &&
               (InLevel_prev_n == enHeatLvlSts_EN_HEAT_LVL_OFF))
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_HeatAdj_CtrlModel_DW.Timer_o =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
          Appl_HeatAdj_CtrlModel_IN_Init;
        Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
        Appl_HeatAdj_CtrlModel_DW.Timer_o =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
      }
    }
    else if ((InLevel_prev_n != Appl_HeatAdj_CtrlModel_DW.InLevel_start_d) &&
             (InLevel_prev_n == enHeatLvlSts_EN_HEAT_LVL_OFF))
    {
      Appl_HeatAdj_CtrlModel_DW.Timer_o = 0U;
      Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus_c =
        Appl_HeatAdj_CtrlModel_IN_Init;
      Appl_HeatAdj_CtrlModel_B.Level_b = Appl_HeatAdj_CtrlModel_B.InLevel;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS();
      Appl_HeatAdj_CtrlModel_DW.Timer_o =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_c;
    }
    else
    {
      Appl_HeatAdj_CtrlModel_B.Level_b = enHeatLvlSts_EN_HEAT_LVL_OFF;
    }
  }
}

/* Output and update for function-call system: '<S53>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S7>/TimeoutFunction1' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction1_Init(void)
{
  INT32U OutTs_n;
  Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eq;
  Appl_HeatAdj_CtrlModel_DW.is_active_c5_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c5_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eq;
  Appl_HeatAdj_CtrlModel_DW.Timer = 0U;
  Appl_HeatAdj_CtrlModel_B.TimeoutFlag_j = 0U;
  Appl_HeatAdj_CtrlModel_B.Level_i = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs_n);
}

/* Output and update for function-call system: '<S7>/TimeoutFunction1' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction1(void)
{
  INT32U OutTs_n;
  enHeatLvlSts InLevel_prev;
  InLevel_prev = Appl_HeatAdj_CtrlModel_DW.InLevel_start;
  Appl_HeatAdj_CtrlModel_DW.InLevel_start = Appl_HeatAdj_CtrlModel_B.InLevel_p;
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c5_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c5_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c5_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_mn;
    Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c5_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_mn)
  {
    /* 有超时配置
       && 启动加热&&有时间值  */
    if ((((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.TimeoutPrm_k) &&
        (enHeatLvlSts_EN_HEAT_LVL_OFF != Appl_HeatAdj_CtrlModel_B.InLevel_p) &&
        (0U != Appl_HeatAdj_CtrlModel_B.MaxTime_k))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c5_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_TimeCountStatus_c;
      Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
        Appl_HeatAdj_CtrlModel_IN_Init_n;
      Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
      Appl_HeatAdj_CtrlModel_DW.Timer =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
    }
    else
    {
      Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
    }
  }
  else
  {
    /* 无超时配置 */
    if ((((BOOL)TRUE) != Appl_HeatAdj_CtrlModel_B.TimeoutPrm_k) || (0U ==
         Appl_HeatAdj_CtrlModel_B.MaxTime_k))
    {
      switch (Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus)
      {
       case Appl_HeatAdj_CtrlModel_IN_Init_n:
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
        Appl_HeatAdj_CtrlModel_DW.Timer =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eq;
        break;

       case Appl_HeatAdj_CtrlModel_IN_TimeoutSts_f:
        Appl_HeatAdj_CtrlModel_DW.Timer = 0U;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eq;
        break;
      }

      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_j = ((BOOL)FALSE);
      Appl_HeatAdj_CtrlModel_DW.is_c5_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_mn;
      Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
    }
    else if (Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus ==
             Appl_HeatAdj_CtrlModel_IN_Init_n)
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
      Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_DW.Timer,
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a, &OutTs_n);
      if (OutTs_n >= Appl_HeatAdj_CtrlModel_B.MaxTime_k)
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
        Appl_HeatAdj_CtrlModel_DW.Timer =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
        Appl_HeatAdj_CtrlModel_B.TimeoutFlag_j = ((BOOL)TRUE);
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_HeatAdj_CtrlModel_IN_TimeoutSts_f;
        Appl_HeatAdj_CtrlModel_B.Level_i = enHeatLvlSts_EN_HEAT_LVL_OFF;
      }
      else if ((InLevel_prev != Appl_HeatAdj_CtrlModel_DW.InLevel_start) &&
               (InLevel_prev == enHeatLvlSts_EN_HEAT_LVL_OFF))
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
        Appl_HeatAdj_CtrlModel_DW.Timer =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
        Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
          Appl_HeatAdj_CtrlModel_IN_Init_n;
        Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
        Appl_HeatAdj_CtrlModel_DW.Timer =
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
      }
    }
    else if ((InLevel_prev != Appl_HeatAdj_CtrlModel_DW.InLevel_start) &&
             (InLevel_prev == enHeatLvlSts_EN_HEAT_LVL_OFF))
    {
      Appl_HeatAdj_CtrlModel_DW.Timer = 0U;
      Appl_HeatAdj_CtrlModel_DW.is_TimeCountStatus =
        Appl_HeatAdj_CtrlModel_IN_Init_n;
      Appl_HeatAdj_CtrlModel_B.Level_i = Appl_HeatAdj_CtrlModel_B.InLevel_p;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_p();
      Appl_HeatAdj_CtrlModel_DW.Timer =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_a;
    }
    else
    {
      Appl_HeatAdj_CtrlModel_B.Level_i = enHeatLvlSts_EN_HEAT_LVL_OFF;
    }
  }
}

/* System initialize for function-call system: '<S7>/TimeoutFunction2' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction2_Init(enHeatLvlSts *rty_Level,
  INT8U *rty_TimeoutFlag, DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c25_Appl_HeatAdj_CtrlModel = 0U;
  localDW->is_c25_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_kh;
  *rty_TimeoutFlag = 0U;
  *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
}

/* Output and update for function-call system: '<S7>/TimeoutFunction2' */
static void Appl_HeatAdj_CtrlModel_TimeoutFunction2(enHeatLvlSts rtu_InLevel,
  INT32U rtu_SwTimeout, enHeatLvlSts *rty_Level, INT8U *rty_TimeoutFlag,
  DW_TimeoutFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c25_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c25_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_c25_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Default_c;
    *rty_Level = rtu_InLevel;
    *rty_TimeoutFlag = ((BOOL)FALSE);
  }
  else if (localDW->is_c25_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_c)
  {
    /* 超时  */
    if (rtu_SwTimeout == (INT32U)(INT32S)((BOOL)TRUE))
    {
      localDW->is_c25_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_TimeCountStatus;
      *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
      *rty_TimeoutFlag = ((BOOL)TRUE);
    }
    else
    {
      *rty_Level = rtu_InLevel;
      *rty_TimeoutFlag = ((BOOL)FALSE);
    }
  }
  else
  {
    /* 无超时 */
    if (rtu_SwTimeout != (INT32U)(INT32S)((BOOL)TRUE))
    {
      localDW->is_c25_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_c;
      *rty_Level = rtu_InLevel;
      *rty_TimeoutFlag = ((BOOL)FALSE);
    }
    else
    {
      *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
      *rty_TimeoutFlag = ((BOOL)TRUE);
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S7>/StopFunction'
 *    '<S7>/StopFunction1'
 *    '<S7>/StopFunction2'
 */
static void Appl_HeatAdj_CtrlModel_StopFunction_Init(enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c12_Appl_HeatAdj_CtrlModel = 0U;
  localDW->is_c12_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_p;
  *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
  *rty_CANStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S7>/StopFunction'
 *    '<S7>/StopFunction1'
 *    '<S7>/StopFunction2'
 */
static void Appl_HeatAdj_CtrlModel_StopFunction(enHeatStopReason rtu_ComStop,
  INT8U rtu_Timeout, enHeatStopReason rtu_ComCANStop, enHeatStopReason
  *rty_StopReason, enHeatStopReason *rty_CANStopReason,
  DW_StopFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c12_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c12_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_c12_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Default_o;
    *rty_StopReason = rtu_ComStop;
    *rty_CANStopReason = rtu_ComCANStop;
  }
  else if (localDW->is_c12_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_o)
  {
    /* 无通用限制
       &&超时限制有效  */
    if ((enHeatStopReason_EN_HEAT_STOP_R_NONE == rtu_ComStop) && (((BOOL)TRUE) ==
         rtu_Timeout))
    {
      localDW->is_c12_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_ValidSts_g;
      *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_TIME;
      *rty_CANStopReason = enHeatStopReason_EN_HEAT_STOP_R_TIME;
    }
    else
    {
      *rty_StopReason = rtu_ComStop;
      *rty_CANStopReason = rtu_ComCANStop;
    }
  }
  else
  {
    /* 无超时限制 */
    if (((BOOL)FALSE) == rtu_Timeout)
    {
      localDW->is_c12_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_o;
      *rty_StopReason = rtu_ComStop;
      *rty_CANStopReason = rtu_ComCANStop;
    }
    else
    {
      *rty_StopReason = enHeatStopReason_EN_HEAT_STOP_R_TIME;
      *rty_CANStopReason = enHeatStopReason_EN_HEAT_STOP_R_TIME;
    }
  }
}

static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enHeatLvlSts (EN_HEAT_LVL_OFF) */
  y = 0;
  if ((input >= 0) && (input <= 3))
  {
    /* Set output value to input value if it is a member of enHeatLvlSts */
    y = input;
  }

  return y;
}

/*
 * System initialize for function-call system:
 *    '<S7>/DiagnoseFunction'
 *    '<S7>/DiagnoseFunction1'
 *    '<S7>/DiagnoseFunction2'
 */
static void Appl_HeatAdj_CtrlModel_DiagnoseFunction_Init(enHeatLvlSts *rty_Level,
  enHeatType *rty_Type, DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c13_Appl_HeatAdj_CtrlModel = 0U;
  *rty_Level = enHeatLvlSts_EN_HEAT_LVL_OFF;
  *rty_Type = enHeatType_EN_HEAT_TYPE_NONE;
}

/*
 * Output and update for function-call system:
 *    '<S7>/DiagnoseFunction'
 *    '<S7>/DiagnoseFunction1'
 *    '<S7>/DiagnoseFunction2'
 */
static void Appl_HeatAdj_CtrlModel_DiagnoseFunction(INT8U rtu_DiagCommand,
  enHeatLvlSts rtu_InLevel, enHeatType rtu_CurrentType, enHeatLvlSts *rty_Level,
  enHeatType *rty_Type, DW_DiagnoseFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c13_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c13_Appl_HeatAdj_CtrlModel = 1U;

    /*  无诊断指令  */
    if ((0 == rtu_DiagCommand) || (rtu_DiagCommand > 4))
    {
      *rty_Level = rtu_InLevel;
      *rty_Type = rtu_CurrentType;
    }
    else
    {
      *rty_Level = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts(rtu_DiagCommand - 1);
      *rty_Type = enHeatType_EN_HEAT_TYPE_DIAG;
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
      *rty_Level = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts(rtu_DiagCommand - 1);
      *rty_Type = enHeatType_EN_HEAT_TYPE_DIAG;
    }
  }
}

/* Output and update for function-call system: '<S76>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h = D_HAL_GET_CUR_MS_TS( );
}

/* Function for Chart: '<S61>/TempFunction' */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl(void)
{
  INT32U OutTs_c;
  INT32S tmp;

  /*  P20方向盘加热等级  */
  tmp = enProjectType_EN_PROJECT_P20;
  if ((tmp == Appl_HeatAdj_CtrlModel_B.ProjectType) && (((BOOL)TRUE) ==
       Appl_HeatAdj_CtrlModel_B.ThirdHeat))
  {
    Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_SwsLevel_Temp);
    Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k();
    Appl_HeatAdj_CtrlModel_DW.TimeCnt_g =
      Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h;
  }
  else
  {
    /*  等级1  */
    switch (Appl_HeatAdj_CtrlModel_B.AimLevel)
    {
     case enHeatLvlSts_EN_HEAT_LVL_1:
      Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_1stLevel_36);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_g =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_2:
      /*  等级2  */
      Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_2ndLevel_39);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_g =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_3:
      /*  等级3  */
      /*  小于13min 且为P20 且本次未降至 45度(防止32bit计数超时重新小于13min)  */
      if (tmp == Appl_HeatAdj_CtrlModel_B.ProjectType)
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k();
        Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_DW.TimeCnt_g,
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h, &OutTs_c);
        if ((OutTs_c <= CAL_LEVEL3_TIMEOUT) &&
            (Appl_HeatAdj_CtrlModel_B.AimTemp_a != ((INT16U)D_3rdLevel_45)))
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_3rdLevel_48);
        }
        else
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_3rdLevel_45);
        }
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.AimTemp_a = ((INT16U)D_3rdLevel_45);
      }
      break;

     default:
      Appl_HeatAdj_CtrlModel_B.AimTemp_a = 0U;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_k();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_g =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_h;
      break;
    }
  }
}

/* System initialize for function-call system: '<S8>/TempFunction' */
static void Appl_HeatAdj_CtrlModel_TempFunction_Init(void)
{
  INT32U OutTs_c;
  Appl_HeatAdj_CtrlModel_DW.is_active_c15_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.TimeCnt_g = 0U;
  Appl_HeatAdj_CtrlModel_B.AimTemp_a = 0U;
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs_c);
}

/* Output and update for function-call system: '<S8>/TempFunction' */
static void Appl_HeatAdj_CtrlModel_TempFunction(void)
{
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c15_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c15_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl();
  }
  else
  {
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl();
  }
}

/* Output and update for function-call system: '<S80>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j = D_HAL_GET_CUR_MS_TS( );
}

/* Function for Chart: '<S62>/TempFunction' */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl_g(void)
{
  INT32U OutTs_px;
  INT32S tmp;

  /*  P20方向盘加热等级  */
  tmp = enProjectType_EN_PROJECT_P20;
  if ((tmp == Appl_HeatAdj_CtrlModel_B.ProjectType_p) && (((BOOL)TRUE) ==
       Appl_HeatAdj_CtrlModel_B.ThirdHeat_i))
  {
    Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_SwsLevel_Temp);
    Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa();
    Appl_HeatAdj_CtrlModel_DW.TimeCnt_o =
      Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j;
  }
  else
  {
    /*  等级1  */
    switch (Appl_HeatAdj_CtrlModel_B.AimLevel_c)
    {
     case enHeatLvlSts_EN_HEAT_LVL_1:
      Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_1stLevel_36);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_o =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_2:
      /*  等级2  */
      Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_2ndLevel_39);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_o =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_3:
      /*  等级3  */
      /*  小于13min 且为P20 且本次未降至 45度(防止32bit计数超时重新小于13min)  */
      if (tmp == Appl_HeatAdj_CtrlModel_B.ProjectType_p)
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa();
        Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_DW.TimeCnt_o,
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j, &OutTs_px);
        if ((OutTs_px <= CAL_LEVEL3_TIMEOUT) &&
            (Appl_HeatAdj_CtrlModel_B.AimTemp_h != ((INT16U)D_3rdLevel_45)))
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_3rdLevel_48);
        }
        else
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_3rdLevel_45);
        }
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.AimTemp_h = ((INT16U)D_3rdLevel_45);
      }
      break;

     default:
      Appl_HeatAdj_CtrlModel_B.AimTemp_h = 0U;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_pa();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt_o =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_j;
      break;
    }
  }
}

/* System initialize for function-call system: '<S8>/TempFunction1' */
static void Appl_HeatAdj_CtrlModel_TempFunction1_Init(void)
{
  INT32U OutTs_px;
  Appl_HeatAdj_CtrlModel_DW.is_active_c54_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.TimeCnt_o = 0U;
  Appl_HeatAdj_CtrlModel_B.AimTemp_h = 0U;
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs_px);
}

/* Output and update for function-call system: '<S8>/TempFunction1' */
static void Appl_HeatAdj_CtrlModel_TempFunction1(void)
{
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c54_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c54_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl_g();
  }
  else
  {
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl_g();
  }
}

/* Output and update for function-call system: '<S84>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l = D_HAL_GET_CUR_MS_TS( );
}

/* Function for Chart: '<S63>/TempFunction' */
static void Appl_HeatAdj_CtrlModel_inner_default_TempLvl_h(void)
{
  INT32U OutTs_p;
  INT32S tmp;

  /*  P20方向盘加热等级  */
  tmp = enProjectType_EN_PROJECT_P20;
  if ((tmp == Appl_HeatAdj_CtrlModel_B.ProjectType_d) && (((BOOL)TRUE) ==
       Appl_HeatAdj_CtrlModel_B.ThirdHeat_o))
  {
    Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_SwsLevel_Temp);
    Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h();
    Appl_HeatAdj_CtrlModel_DW.TimeCnt =
      Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l;
  }
  else
  {
    /*  等级1  */
    switch (Appl_HeatAdj_CtrlModel_B.AimLevel_d)
    {
     case enHeatLvlSts_EN_HEAT_LVL_1:
      Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_1stLevel_36);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_2:
      /*  等级2  */
      Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_2ndLevel_39);
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l;
      break;

     case enHeatLvlSts_EN_HEAT_LVL_3:
      /*  等级3  */
      /*  小于13min 且为P20 且本次未降至 45度(防止32bit计数超时重新小于13min)  */
      if (tmp == Appl_HeatAdj_CtrlModel_B.ProjectType_d)
      {
        Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h();
        Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_DW.TimeCnt,
          Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l, &OutTs_p);
        if ((OutTs_p <= CAL_LEVEL3_TIMEOUT) && (Appl_HeatAdj_CtrlModel_B.AimTemp
             != ((INT16U)D_3rdLevel_45)))
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_3rdLevel_48);
        }
        else
        {
          Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_3rdLevel_45);
        }
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.AimTemp = ((INT16U)D_3rdLevel_45);
      }
      break;

     default:
      Appl_HeatAdj_CtrlModel_B.AimTemp = 0U;
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_h();
      Appl_HeatAdj_CtrlModel_DW.TimeCnt =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS_l;
      break;
    }
  }
}

/* System initialize for function-call system: '<S8>/TempFunction2' */
static void Appl_HeatAdj_CtrlModel_TempFunction2_Init(void)
{
  INT32U OutTs_p;
  Appl_HeatAdj_CtrlModel_DW.is_active_c57_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.TimeCnt = 0U;
  Appl_HeatAdj_CtrlModel_B.AimTemp = 0U;
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs_p);
}

/* Output and update for function-call system: '<S8>/TempFunction2' */
static void Appl_HeatAdj_CtrlModel_TempFunction2(void)
{
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c57_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c57_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl_h();
  }
  else
  {
    Appl_HeatAdj_CtrlModel_inner_default_TempLvl_h();
  }
}

/*
 * System initialize for function-call system:
 *    '<S64>/PidGetPwm'
 *    '<S67>/PidGetPwm'
 *    '<S70>/PidGetPwm'
 */
static void Appl_HeatAdj_CtrlModel_PidGetPwm_Init(INT16U *rty_PwmCnt,
  DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->SumError = 0U;
  localDW->LastError = 0U;
  *rty_PwmCnt = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S64>/PidGetPwm'
 *    '<S67>/PidGetPwm'
 *    '<S70>/PidGetPwm'
 */
static void Appl_HeatAdj_CtrlModel_PidGetPwm(INT16U rtu_CurrentTemp, INT16U
  rtu_SetTemp, INT16U *rty_PwmCnt, DW_PidGetPwm_Appl_HeatAdj_CtrlModel_T
  *localDW)
{
  INT32U q0;
  INT32U qY;
  INT32U qY_0;
  INT32S Error;

  /*  局部初始化  */
  /*  PID 计算  */
  Error = rtu_SetTemp - rtu_CurrentTemp;
  if (Error < 0)
  {
    Error = 0;
  }

  qY_0 = localDW->SumError + Error;
  if (qY_0 < localDW->SumError)
  {
    qY_0 = MAX_uint32_T;
  }

  localDW->SumError = qY_0;
  qY_0 = Error - localDW->LastError;
  if (qY_0 > (INT32U)Error)
  {
    qY_0 = 0U;
  }

  localDW->LastError = (INT32U)Error;
  q0 = (INT32U)((INT8U)D_DRVHEAT_PID_P) * Error;
  qY = q0 + mul_u32_sat(((INT8U)D_DRVHEAT_PID_I), localDW->SumError);
  if (qY < q0)
  {
    qY = MAX_uint32_T;
  }

  qY_0 = ((INT8U)D_DRVHEAT_PID_D) * qY_0 + qY;
  if (qY_0 < qY)
  {
    qY_0 = MAX_uint32_T;
  }

  if (qY_0 > 65535U)
  {
    qY_0 = 65535U;
  }

  *rty_PwmCnt = (INT16U)qY_0;
  if (*rty_PwmCnt > 100)
  {
    *rty_PwmCnt = 100U;
  }
}

/*
 * System initialize for function-call system:
 *    '<S8>/HeatOutFunction'
 *    '<S8>/HeatOutFunction1'
 */
static void Appl_HeatAdj_CtrlModel_HeatOutFunction_Init(INT8U *rty_HeatOutGpio,
  INT8U *rty_HeatOutPwmCnt, B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localB,
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_j;
  localDW->is_active_c16_Appl_HeatAdj_CtrlModel = 0U;
  localDW->TimeCnt = 0U;
  *rty_HeatOutGpio = 0U;
  *rty_HeatOutPwmCnt = 0U;
  Appl_HeatAdj_CtrlModel_PidGetPwm_Init(&localB->PwmCnt, &localDW->PidGetPwm);
}

/*
 * Output and update for function-call system:
 *    '<S8>/HeatOutFunction'
 *    '<S8>/HeatOutFunction1'
 */
static void Appl_HeatAdj_CtrlModel_HeatOutFunction(INT16U rtu_SetTemp, INT16U
  rtu_CurrentTemp, enHeatLvlSts rtu_HeatLvl, INT8U *rty_HeatOutGpio, INT8U
  *rty_HeatOutPwmCnt, B_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localB,
  DW_HeatOutFunction_Appl_HeatAdj_CtrlModel_T *localDW)
{
  INT16U tmp;
  INT32S tmp_0;
  if (localDW->is_active_c16_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c16_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_None;
  }
  else
  {
    switch (localDW->is_Controll)
    {
     case Appl_HeatAdj_CtrlModel_IN_AllOut:
      /* 全开 进 关  */
      if ((rtu_SetTemp <= rtu_CurrentTemp) || (enHeatLvlSts_EN_HEAT_LVL_OFF ==
           rtu_HeatLvl))
      {
        localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_None;
      }
      else
      {
        /*  全开 进PID  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < rtu_HeatLvl) && (rtu_SetTemp >
             rtu_CurrentTemp) && (rtu_SetTemp - rtu_CurrentTemp < ((INT8U)
              D_HEAT_HEAT_DEF)))
        {
          localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_PwmOut;
          localB->CurrentTemp = rtu_CurrentTemp;
          localB->SetTemp = rtu_SetTemp;
          Appl_HeatAdj_CtrlModel_PidGetPwm(localB->CurrentTemp, localB->SetTemp,
            &localB->PwmCnt, &localDW->PidGetPwm);
          tmp = localB->PwmCnt;
          if (localB->PwmCnt > 255)
          {
            tmp = 255U;
          }

          *rty_HeatOutPwmCnt = (INT8U)tmp;

          /*  100计数  */
          if (localDW->TimeCnt <= 100)
          {
            tmp_0 = localDW->TimeCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            localDW->TimeCnt = (INT8U)tmp_0;
            if (localDW->TimeCnt <= *rty_HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              *rty_HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              *rty_HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            localDW->TimeCnt = 0U;
            Appl_HeatAdj_CtrlModel_PidGetPwm(localB->CurrentTemp,
              localB->SetTemp, &localB->PwmCnt, &localDW->PidGetPwm);
            tmp = localB->PwmCnt;
            if (localB->PwmCnt > 255)
            {
              tmp = 255U;
            }

            *rty_HeatOutPwmCnt = (INT8U)tmp;
          }
        }
        else
        {
          *rty_HeatOutGpio = ((INT8U)ON);
          *rty_HeatOutPwmCnt = 100U;
          localDW->TimeCnt = 0U;
        }
      }
      break;

     case Appl_HeatAdj_CtrlModel_IN_None:
      /*  加热误差在3度 全开  */
      if ((enHeatLvlSts_EN_HEAT_LVL_OFF < rtu_HeatLvl) && (rtu_SetTemp >
           rtu_CurrentTemp) && (rtu_SetTemp - rtu_CurrentTemp >= ((INT8U)
            D_HEAT_HEAT_DEF)))
      {
        localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_AllOut;
      }
      else
      {
        /*  关 进 PID  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < rtu_HeatLvl) && (rtu_SetTemp >
             rtu_CurrentTemp) && (rtu_SetTemp - rtu_CurrentTemp < ((INT8U)
              D_HEAT_HEAT_DEF)))
        {
          localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_PwmOut;
          localB->CurrentTemp = rtu_CurrentTemp;
          localB->SetTemp = rtu_SetTemp;
          Appl_HeatAdj_CtrlModel_PidGetPwm(localB->CurrentTemp, localB->SetTemp,
            &localB->PwmCnt, &localDW->PidGetPwm);
          tmp = localB->PwmCnt;
          if (localB->PwmCnt > 255)
          {
            tmp = 255U;
          }

          *rty_HeatOutPwmCnt = (INT8U)tmp;

          /*  100计数  */
          if (localDW->TimeCnt <= 100)
          {
            tmp_0 = localDW->TimeCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            localDW->TimeCnt = (INT8U)tmp_0;
            if (localDW->TimeCnt <= *rty_HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              *rty_HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              *rty_HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            localDW->TimeCnt = 0U;
            Appl_HeatAdj_CtrlModel_PidGetPwm(localB->CurrentTemp,
              localB->SetTemp, &localB->PwmCnt, &localDW->PidGetPwm);
            tmp = localB->PwmCnt;
            if (localB->PwmCnt > 255)
            {
              tmp = 255U;
            }

            *rty_HeatOutPwmCnt = (INT8U)tmp;
          }
        }
        else
        {
          *rty_HeatOutGpio = ((INT8U)OFF);
          *rty_HeatOutPwmCnt = 0U;
          localDW->TimeCnt = 0U;
        }
      }
      break;

     default:
      /*  PID 进 关  */
      if ((rtu_SetTemp <= rtu_CurrentTemp) || (enHeatLvlSts_EN_HEAT_LVL_OFF ==
           rtu_HeatLvl))
      {
        localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_None;
      }
      else
      {
        /*  加热误差在3度 全开  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < rtu_HeatLvl) && (rtu_SetTemp >
             rtu_CurrentTemp) && (rtu_SetTemp - rtu_CurrentTemp >= ((INT8U)
              D_HEAT_HEAT_DEF)))
        {
          localDW->is_Controll = Appl_HeatAdj_CtrlModel_IN_AllOut;
        }
        else
        {
          /*  100计数  */
          if (localDW->TimeCnt <= 100)
          {
            tmp_0 = localDW->TimeCnt + 1;
            if (tmp_0 > 255)
            {
              tmp_0 = 255;
            }

            localDW->TimeCnt = (INT8U)tmp_0;
            if (localDW->TimeCnt <= *rty_HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              *rty_HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              *rty_HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            localDW->TimeCnt = 0U;
            localB->CurrentTemp = rtu_CurrentTemp;
            localB->SetTemp = rtu_SetTemp;
            Appl_HeatAdj_CtrlModel_PidGetPwm(localB->CurrentTemp,
              localB->SetTemp, &localB->PwmCnt, &localDW->PidGetPwm);
            tmp = localB->PwmCnt;
            if (localB->PwmCnt > 255)
            {
              tmp = 255U;
            }

            *rty_HeatOutPwmCnt = (INT8U)tmp;
          }
        }
      }
      break;
    }
  }
}

/* Output and update for function-call system: '<S70>/D_HAL_GET_CUR_MS_TS' */
static void Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e(void)
{
  Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS = D_HAL_GET_CUR_MS_TS( );
}

/* System initialize for function-call system: '<S8>/HeatOutFunction2' */
static void Appl_HeatAdj_CtrlModel_HeatOutFunction2_Init(void)
{
  INT16U PwmCnt;
  INT32U OutTs;
  Appl_HeatAdj_CtrlModel_DW.is_Controll =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_eu;
  Appl_HeatAdj_CtrlModel_DW.is_active_c32_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
  Appl_HeatAdj_CtrlModel_B.HeatOutGpio = 0U;
  Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = 0U;
  Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = 0U;
  Appl_HeatAdj_CtrlModel_B.Sw20minTimer = 0U;
  Appl_HeatAdj_CtrlModel_PidGetPwm_Init(&PwmCnt,
    &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
  Appl_HeatAdj_CtrlModel_TimeDiffTs_Init(&OutTs);
}

/* Output and update for function-call system: '<S8>/HeatOutFunction2' */
static void Appl_HeatAdj_CtrlModel_HeatOutFunction2(void)
{
  INT16U PwmCnt;
  INT32U OutTs;
  INT32S tmp;
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c32_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c32_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_Controll = Appl_HeatAdj_CtrlModel_IN_None_c;

    /* 方向盘加热开启且加热温度≥目标温度 */
    if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
        (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m >=
         Appl_HeatAdj_CtrlModel_B.SetTemp_a - 20))
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e();
      Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_B.Sw20minTimer,
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS, &OutTs);
      if (OutTs < Appl_HeatAdj_CtrlModel_B.MaxTime)
      {
        Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)FALSE);
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e();
      Appl_HeatAdj_CtrlModel_B.Sw20minTimer =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
    }

    if (enHeatLvlSts_EN_HEAT_LVL_OFF == Appl_HeatAdj_CtrlModel_B.HeatLvl_i)
    {
      Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)FALSE);
    }
  }
  else
  {
    switch (Appl_HeatAdj_CtrlModel_DW.is_Controll)
    {
     case Appl_HeatAdj_CtrlModel_IN_AllOut_d:
      /* 全开 进 关  */
      if ((Appl_HeatAdj_CtrlModel_B.SetTemp_a <=
           Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) ||
          (enHeatLvlSts_EN_HEAT_LVL_OFF == Appl_HeatAdj_CtrlModel_B.HeatLvl_i))
      {
        Appl_HeatAdj_CtrlModel_DW.is_Controll = Appl_HeatAdj_CtrlModel_IN_None_c;
      }
      else
      {
        /*  全开 进PID  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a >
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a -
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m < ((INT8U)D_HEAT_HEAT_DEF)))
        {
          Appl_HeatAdj_CtrlModel_DW.is_Controll =
            Appl_HeatAdj_CtrlModel_IN_PwmOut_o;
          Appl_HeatAdj_CtrlModel_PidGetPwm
            (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m,
             Appl_HeatAdj_CtrlModel_B.SetTemp_a, &PwmCnt,
             &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
          if (PwmCnt > 255)
          {
            PwmCnt = 255U;
          }

          Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = (INT8U)PwmCnt;

          /*  100计数  */
          if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <= 100)
          {
            tmp = Appl_HeatAdj_CtrlModel_DW.TimeCnt_c + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = (INT8U)tmp;
            if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <=
                Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
            Appl_HeatAdj_CtrlModel_PidGetPwm
              (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m,
               Appl_HeatAdj_CtrlModel_B.SetTemp_a, &PwmCnt,
               &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
            if (PwmCnt > 255)
            {
              PwmCnt = 255U;
            }

            Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = (INT8U)PwmCnt;
          }
        }
        else
        {
          Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)ON);
          Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = 100U;
          Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
        }
      }
      break;

     case Appl_HeatAdj_CtrlModel_IN_None_c:
      /*  加热误差在3度 全开  */
      if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
          (Appl_HeatAdj_CtrlModel_B.SetTemp_a >
           Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) &&
          (Appl_HeatAdj_CtrlModel_B.SetTemp_a -
           Appl_HeatAdj_CtrlModel_B.CurrentTemp_m >= ((INT8U)D_HEAT_HEAT_DEF)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_Controll =
          Appl_HeatAdj_CtrlModel_IN_AllOut_d;
      }
      else
      {
        /*  关 进 PID  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a >
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a -
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m < ((INT8U)D_HEAT_HEAT_DEF)))
        {
          Appl_HeatAdj_CtrlModel_DW.is_Controll =
            Appl_HeatAdj_CtrlModel_IN_PwmOut_o;
          Appl_HeatAdj_CtrlModel_PidGetPwm
            (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m,
             Appl_HeatAdj_CtrlModel_B.SetTemp_a, &PwmCnt,
             &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
          if (PwmCnt > 255)
          {
            PwmCnt = 255U;
          }

          Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = (INT8U)PwmCnt;

          /*  100计数  */
          if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <= 100)
          {
            tmp = Appl_HeatAdj_CtrlModel_DW.TimeCnt_c + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = (INT8U)tmp;
            if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <=
                Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
            Appl_HeatAdj_CtrlModel_PidGetPwm
              (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m,
               Appl_HeatAdj_CtrlModel_B.SetTemp_a, &PwmCnt,
               &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
            if (PwmCnt > 255)
            {
              PwmCnt = 255U;
            }

            Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = (INT8U)PwmCnt;
          }
        }
        else
        {
          Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)OFF);
          Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = 0U;
          Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
        }
      }
      break;

     default:
      /*  PID 进 关  */
      if ((Appl_HeatAdj_CtrlModel_B.SetTemp_a <=
           Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) ||
          (enHeatLvlSts_EN_HEAT_LVL_OFF == Appl_HeatAdj_CtrlModel_B.HeatLvl_i))
      {
        Appl_HeatAdj_CtrlModel_DW.is_Controll = Appl_HeatAdj_CtrlModel_IN_None_c;
      }
      else
      {
        /*  加热误差在3度 全开  */
        if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a >
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m) &&
            (Appl_HeatAdj_CtrlModel_B.SetTemp_a -
             Appl_HeatAdj_CtrlModel_B.CurrentTemp_m >= ((INT8U)D_HEAT_HEAT_DEF)))
        {
          Appl_HeatAdj_CtrlModel_DW.is_Controll =
            Appl_HeatAdj_CtrlModel_IN_AllOut_d;
        }
        else
        {
          /*  100计数  */
          if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <= 100)
          {
            tmp = Appl_HeatAdj_CtrlModel_DW.TimeCnt_c + 1;
            if (tmp > 255)
            {
              tmp = 255;
            }

            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = (INT8U)tmp;
            if (Appl_HeatAdj_CtrlModel_DW.TimeCnt_c <=
                Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt)
            {
              /*  引脚拉高  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)ON);
            }
            else
            {
              /*  引脚拉低  */
              Appl_HeatAdj_CtrlModel_B.HeatOutGpio = ((INT8U)OFF);
            }
          }
          else
          {
            /*  计算pid 算pwm  */
            Appl_HeatAdj_CtrlModel_DW.TimeCnt_c = 0U;
            Appl_HeatAdj_CtrlModel_PidGetPwm
              (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m,
               Appl_HeatAdj_CtrlModel_B.SetTemp_a, &PwmCnt,
               &Appl_HeatAdj_CtrlModel_DW.PidGetPwm);
            if (PwmCnt > 255)
            {
              PwmCnt = 255U;
            }

            Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt = (INT8U)PwmCnt;
          }
        }
      }
      break;
    }

    /* 方向盘加热开启且加热温度≥目标温度 */
    if ((enHeatLvlSts_EN_HEAT_LVL_OFF < Appl_HeatAdj_CtrlModel_B.HeatLvl_i) &&
        (Appl_HeatAdj_CtrlModel_B.CurrentTemp_m >=
         Appl_HeatAdj_CtrlModel_B.SetTemp_a - 20))
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e();
      Appl_HeatAdj_CtrlModel_TimeDiffTs(Appl_HeatAdj_CtrlModel_B.Sw20minTimer,
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS, &OutTs);
      if (OutTs < Appl_HeatAdj_CtrlModel_B.MaxTime)
      {
        Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)FALSE);
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)TRUE);
      }
    }
    else
    {
      Appl_HeatAdj_CtrlModel_D_HAL_GET_CUR_MS_TS_e();
      Appl_HeatAdj_CtrlModel_B.Sw20minTimer =
        Appl_HeatAdj_CtrlModel_B.D_HAL_GET_CUR_MS_TS;
    }

    if (enHeatLvlSts_EN_HEAT_LVL_OFF == Appl_HeatAdj_CtrlModel_B.HeatLvl_i)
    {
      Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag = ((BOOL)FALSE);
    }
  }
}

static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(INT32S input)
{
  INT32S y;

  /* Initialize output value to default value for enHeatLvlSts (EN_HEAT_LVL_OFF) */
  y = 0;
  if ((input >= 0) && (input <= 3))
  {
    /* Set output value to input value if it is a member of enHeatLvlSts */
    y = input;
  }

  return y;
}

/* Function for Chart: '<S5>/HeatLevelDeal' */
static void Appl_HeatA_enter_internal_BM400_ThirdHeatLevelDeal(INT8U
  *EnableCfg_l, enProjectType *CarTypeCfg_me, INT8U *CAN_Message_e,
  enHeatStopReason *DisableSts_he, INT8U *ComPCFlag_lf, INT8U *CanLvl_pr)
{
  INT8U Local3rdTboxHeatLevel;
  INT32S tmp;
  *EnableCfg_l = Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig;
  *CarTypeCfg_me = HeatAdj_CarType;
  *CAN_Message_e = Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message;
  *DisableSts_he = HeatAdj_ThirdHeatStopReason;
  *ComPCFlag_lf = Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag;
  *CanLvl_pr = HeatAdj_CanThirdHeatLvl;
  Appl_HeatAdj_CtrlModel_B.Type_o = ((BOOL)FALSE);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction(*EnableCfg_l, *CarTypeCfg_me,
    *CAN_Message_e, *DisableSts_he, *ComPCFlag_lf, *CanLvl_pr,
    Appl_HeatAdj_CtrlModel_B.Type_o, &Appl_HeatAdj_CtrlModel_B.Level_j,
    &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction4);

  /*  三排加热大屏判断  */
  tmp = enHeatLvlSts_EN_HEAT_LVL_3;
  if (Appl_HeatAdj_CtrlModel_B.Level_j <= tmp)
  {
    Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType = enHeatType_EN_HEAT_TYPE_HMI;
    Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
      (Appl_HeatAdj_CtrlModel_B.Level_j);
  }

  if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
  {
    Appl_HeatAdj_CtrlModel_B.EnableCfg_lg =
      Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig;
    Appl_HeatAdj_CtrlModel_B.CarTypeCfg_e = HeatAdj_CarType;
    Appl_HeatAdj_CtrlModel_B.CAN_Message_ns =
      Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message;
    Appl_HeatAdj_CtrlModel_B.DisableSts_b = HeatAdj_ThirdHeatStopReason;
    Appl_HeatAdj_CtrlModel_B.ComPCFlag_f =
      Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag;
    Appl_HeatAdj_CtrlModel_B.CanLvl_f = HeatAdj_CanThirdHeatLvl;
    Appl_HeatAdj_CtrlModel_B.Type_m = ((BOOL)TRUE);
    Appl_HeatAdj_CtrlModel_LevelAquireFunction
      (Appl_HeatAdj_CtrlModel_B.EnableCfg_lg,
       Appl_HeatAdj_CtrlModel_B.CarTypeCfg_e,
       Appl_HeatAdj_CtrlModel_B.CAN_Message_ns,
       Appl_HeatAdj_CtrlModel_B.DisableSts_b,
       Appl_HeatAdj_CtrlModel_B.ComPCFlag_f, Appl_HeatAdj_CtrlModel_B.CanLvl_f,
       Appl_HeatAdj_CtrlModel_B.Type_m, &Appl_HeatAdj_CtrlModel_B.Level_kl,
       &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction5);
    Local3rdTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_kl;
  }
  else
  {
    Local3rdTboxHeatLevel = (INT8U)0xFF;
  }

  /*  三排加热远程判断  */
  if (Local3rdTboxHeatLevel <= tmp)
  {
    Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType = enHeatType_EN_HEAT_TYPE_TBOX;
    Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(Local3rdTboxHeatLevel);
  }
}

static INT32S Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts(INT32S input)
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

/* System initialize for atomic system: '<Root>/LogicCtrl' */
static void Appl_HeatAdj_CtrlModel_LogicCtrl_Init(void)
{
  INT8U Level_m;
  enHeatStopReason CANStopReason_c;
  enHeatLvlSts Level_l;
  enHeatStopReason CANStopReason_b;
  enHeatType Type_h;
  Appl_HeatAdj_CtrlModel_DW.is_ThirdHeatLevelDeal =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_active_c3_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType = enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
    enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType = enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_CANAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.IVISwCan,
     &Appl_HeatAdj_CtrlModel_DW.CANAquireFunction);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_he,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_c0,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction3);
  Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1_Init(&Level_m,
    &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction1);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_h,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction1);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_j,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction4);
  Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1_Init(&Level_m,
    &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_ax,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction2);
  Appl_HeatAdj_CtrlModel_LevelAquireFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_kl,
     &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction5);
  Appl_HeatAdj_CtrlModel_DW.is_active_c2_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_B.DrHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_B.ThirdHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_B.PaHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.HeatDriverRunType = enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_B.HeatPassengerRunType = enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_B.HeatThirdRunType = enHeatType_EN_HEAT_TYPE_NONE;
  Appl_HeatAdj_CtrlModel_B.DrCANHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_B.PaCANHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_B.ThirdCANHeatStopReason =
    enHeatStopReason_EN_HEAT_STOP_R_NONE;
  Appl_HeatAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_be, &Appl_HeatAdj_CtrlModel_B.StopReason_c,
     &Appl_HeatAdj_CtrlModel_B.CANStopReason_j,
     &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction);
  Appl_HeatAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_g, &Appl_HeatAdj_CtrlModel_B.StopReason_ew,
     &Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
     &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction1);
  Appl_HeatAdj_CtrlModel_LevelLimitFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.Level_p, &Appl_HeatAdj_CtrlModel_B.StopReason_d,
     &CANStopReason_c, &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction2);
  Appl_HeatAdj_CtrlModel_TimeoutFunction_Init();
  Appl_HeatAdj_CtrlModel_TimeoutFunction1_Init();
  Appl_HeatAdj_CtrlModel_TimeoutFunction2_Init(&Level_l, &Level_m,
    &Appl_HeatAdj_CtrlModel_DW.TimeoutFunction2);
  Appl_HeatAdj_CtrlModel_StopFunction_Init(&CANStopReason_c, &CANStopReason_b,
    &Appl_HeatAdj_CtrlModel_DW.StopFunction);
  Appl_HeatAdj_CtrlModel_StopFunction_Init(&CANStopReason_c, &CANStopReason_b,
    &Appl_HeatAdj_CtrlModel_DW.StopFunction1);
  Appl_HeatAdj_CtrlModel_StopFunction_Init(&CANStopReason_c, &CANStopReason_b,
    &Appl_HeatAdj_CtrlModel_DW.StopFunction2);
  Appl_HeatAdj_CtrlModel_DiagnoseFunction_Init(&Level_l, &Type_h,
    &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction);
  Appl_HeatAdj_CtrlModel_DiagnoseFunction_Init(&Level_l, &Type_h,
    &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction1);
  Appl_HeatAdj_CtrlModel_DiagnoseFunction_Init(&Level_l, &Type_h,
    &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction2);
  Appl_HeatAdj_CtrlModel_DW.is_CANOutputDeal =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_Drv =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_Pas =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_Treble =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_DrErr =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_PaErr =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_ThirdErr =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
  Appl_HeatAdj_CtrlModel_DW.is_active_c14_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = 0U;
  Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = 0U;
  Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = 0U;
  Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
  Appl_HeatAdj_CtrlModel_B.HeatAdj_DRHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  Appl_HeatAdj_CtrlModel_B.HeatAdj_PAHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  Appl_HeatAdj_CtrlModel_B.HeatAdj_ThirdHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  Appl_HeatAdj_CtrlModel_B.OutDrRunState = 0U;
  Appl_HeatAdj_CtrlModel_B.OutPaRunState = 0U;
  Appl_HeatAdj_CtrlModel_B.Out3rdRunState = 0U;
  Appl_HeatAdj_CtrlModel_B.Sw20minTimerOut = 0U;
  Appl_HeatAdj_CtrlModel_TempFunction_Init();
  Appl_HeatAdj_CtrlModel_TempFunction1_Init();
  Appl_HeatAdj_CtrlModel_TempFunction2_Init();
  Appl_HeatAdj_CtrlModel_HeatOutFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.HeatOutGpio_e,
     &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_ik,
     &Appl_HeatAdj_CtrlModel_B.HeatOutFunction,
     &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction);
  Appl_HeatAdj_CtrlModel_HeatOutFunction_Init
    (&Appl_HeatAdj_CtrlModel_B.HeatOutGpio_l,
     &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_i,
     &Appl_HeatAdj_CtrlModel_B.HeatOutFunction1,
     &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction1);
  Appl_HeatAdj_CtrlModel_HeatOutFunction2_Init();
}

/* Output and update for atomic system: '<Root>/LogicCtrl' */
static void Appl_HeatAdj_CtrlModel_LogicCtrl(void)
{
  INT8U LocalDrTboxHeatLevel;
  enHeatLvlSts Level_l;
  enProjectType CarTypeCfg_me;
  INT8U CAN_Message_e;
  enHeatStopReason DisableSts_he;
  INT8U ComPCFlag_lf;
  INT8U CanLvl_pr;
  INT32S tmp;
  Appl_HeatAdj_CtrlModel_B.EngineRunningFlag_n =
    Appl_HeatAdj_CtrlModel_B.EngineRunningFlag;
  Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_c =
    Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot;
  Appl_HeatAdj_CtrlModel_B.VehicleRunFlag_m =
    Appl_HeatAdj_CtrlModel_B.VehicleRunFlag;
  Appl_HeatAdj_CtrlModel_B.DrHeatConfig_d =
    Appl_HeatAdj_CtrlModel_B.DrHeatConfig;
  Appl_HeatAdj_CtrlModel_B.PaHeatConfig_k =
    Appl_HeatAdj_CtrlModel_B.PaHeatConfig;
  Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig_l =
    Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig;
  Appl_HeatAdj_CtrlModel_B.DrVentConfig_l =
    Appl_HeatAdj_CtrlModel_B.DrVentConfig;
  Appl_HeatAdj_CtrlModel_B.PaVentConfig_d =
    Appl_HeatAdj_CtrlModel_B.PaVentConfig;
  Appl_HeatAdj_CtrlModel_B.ThirdVentConfig_c =
    Appl_HeatAdj_CtrlModel_B.ThirdVentConfig;
  Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag_n =
    Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag;
  if (Appl_HeatAdj_CtrlModel_DW.is_active_c3_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c3_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_LevelAquireFunction
      (Appl_HeatAdj_CtrlModel_B.DrHeatConfig, HeatAdj_CarType,
       Appl_HeatAdj_CtrlModel_B.DriverHMI_Message, HeatAdj_DrHeatStopReason,
       Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanDrvHeatLvl,
       (INT8U)((BOOL)FALSE), &Appl_HeatAdj_CtrlModel_B.Level_he,
       &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction);

    /*  主驾加热大屏判断  */
    if (Appl_HeatAdj_CtrlModel_B.Level_he <= (INT32S)enHeatLvlSts_EN_HEAT_LVL_3)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType =
        enHeatType_EN_HEAT_TYPE_HMI;
      Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
        (Appl_HeatAdj_CtrlModel_B.Level_he);
    }

    if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
    {
      Appl_HeatAdj_CtrlModel_LevelAquireFunction
        (Appl_HeatAdj_CtrlModel_B.DrHeatConfig, HeatAdj_CarType,
         Appl_HeatAdj_CtrlModel_B.DriverTbox_Message, HeatAdj_DrHeatStopReason,
         Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanDrvHeatLvl,
         (INT8U)((BOOL)TRUE), &Appl_HeatAdj_CtrlModel_B.Level_h,
         &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction1);
      LocalDrTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_h;
    }
    else
    {
      LocalDrTboxHeatLevel = (INT8U)0xFF;
    }

    /*  主驾加热远程判断  */
    if (LocalDrTboxHeatLevel <= (INT32S)enHeatLvlSts_EN_HEAT_LVL_3)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType =
        enHeatType_EN_HEAT_TYPE_TBOX;
      Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(LocalDrTboxHeatLevel);
    }

    Appl_HeatAdj_CtrlModel_LevelAquireFunction
      (Appl_HeatAdj_CtrlModel_B.PaHeatConfig, HeatAdj_CarType,
       Appl_HeatAdj_CtrlModel_B.PassengerHMI_Message, HeatAdj_PaHeatStopReason,
       Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanPasHeatLvl,
       (INT8U)((BOOL)FALSE), &Appl_HeatAdj_CtrlModel_B.Level_ax,
       &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction2);

    /*  副驾加热大屏判断 */
    if (Appl_HeatAdj_CtrlModel_B.Level_ax <= (INT32S)enHeatLvlSts_EN_HEAT_LVL_3)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
        enHeatType_EN_HEAT_TYPE_HMI;
      Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
        (Appl_HeatAdj_CtrlModel_B.Level_ax);
    }

    if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
    {
      Appl_HeatAdj_CtrlModel_LevelAquireFunction
        (Appl_HeatAdj_CtrlModel_B.PaHeatConfig, HeatAdj_CarType,
         Appl_HeatAdj_CtrlModel_B.PassengerTbox_Message,
         HeatAdj_PaHeatStopReason, Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag,
         HeatAdj_CanPasHeatLvl, (INT8U)((BOOL)TRUE),
         &Appl_HeatAdj_CtrlModel_B.Level_c0,
         &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction3);
      LocalDrTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_c0;
    }
    else
    {
      LocalDrTboxHeatLevel = (INT8U)0xFF;
    }

    /*  副驾加热远程判断  */
    if (LocalDrTboxHeatLevel <= (INT32S)enHeatLvlSts_EN_HEAT_LVL_3)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
        enHeatType_EN_HEAT_TYPE_TBOX;
      Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(LocalDrTboxHeatLevel);
    }

    Appl_HeatAdj_CtrlModel_DW.is_ThirdHeatLevelDeal =
      Appl_HeatAdj_CtrlModel_IN_BM400_ThirdHeatLevelDeal;
    Appl_HeatA_enter_internal_BM400_ThirdHeatLevelDeal(&LocalDrTboxHeatLevel,
      &CarTypeCfg_me, &CAN_Message_e, &DisableSts_he, &ComPCFlag_lf, &CanLvl_pr);
  }
  else
  {
    Appl_HeatAdj_CtrlModel_LevelAquireFunction
      (Appl_HeatAdj_CtrlModel_B.DrHeatConfig, HeatAdj_CarType,
       Appl_HeatAdj_CtrlModel_B.DriverHMI_Message, HeatAdj_DrHeatStopReason,
       Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanDrvHeatLvl,
       (INT8U)((BOOL)FALSE), &Appl_HeatAdj_CtrlModel_B.Level_he,
       &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction);

    /*  主驾加热大屏判断  */
    tmp = enHeatLvlSts_EN_HEAT_LVL_3;
    if (Appl_HeatAdj_CtrlModel_B.Level_he <= tmp)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType =
        enHeatType_EN_HEAT_TYPE_HMI;
      Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
        (Appl_HeatAdj_CtrlModel_B.Level_he);
    }

    if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
    {
      Appl_HeatAdj_CtrlModel_LevelAquireFunction
        (Appl_HeatAdj_CtrlModel_B.DrHeatConfig, HeatAdj_CarType,
         Appl_HeatAdj_CtrlModel_B.DriverTbox_Message, HeatAdj_DrHeatStopReason,
         Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanDrvHeatLvl,
         (INT8U)((BOOL)TRUE), &Appl_HeatAdj_CtrlModel_B.Level_h,
         &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction1);
      LocalDrTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_h;
    }
    else
    {
      LocalDrTboxHeatLevel = (INT8U)0xFF;
    }

    /*  主驾加热远程判断  */
    if (LocalDrTboxHeatLevel <= tmp)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType =
        enHeatType_EN_HEAT_TYPE_TBOX;
      Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(LocalDrTboxHeatLevel);
    }

    Appl_HeatAdj_CtrlModel_LevelAquireFunction
      (Appl_HeatAdj_CtrlModel_B.PaHeatConfig, HeatAdj_CarType,
       Appl_HeatAdj_CtrlModel_B.PassengerHMI_Message, HeatAdj_PaHeatStopReason,
       Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanPasHeatLvl,
       (INT8U)((BOOL)FALSE), &Appl_HeatAdj_CtrlModel_B.Level_ax,
       &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction2);

    /*  副驾加热大屏判断 */
    if (Appl_HeatAdj_CtrlModel_B.Level_ax <= tmp)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
        enHeatType_EN_HEAT_TYPE_HMI;
      Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
        (Appl_HeatAdj_CtrlModel_B.Level_ax);
    }

    if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
    {
      Appl_HeatAdj_CtrlModel_LevelAquireFunction
        (Appl_HeatAdj_CtrlModel_B.PaHeatConfig, HeatAdj_CarType,
         Appl_HeatAdj_CtrlModel_B.PassengerTbox_Message,
         HeatAdj_PaHeatStopReason, Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag,
         HeatAdj_CanPasHeatLvl, (INT8U)((BOOL)TRUE),
         &Appl_HeatAdj_CtrlModel_B.Level_c0,
         &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction3);
      LocalDrTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_c0;
    }
    else
    {
      LocalDrTboxHeatLevel = (INT8U)0xFF;
    }

    /*  副驾加热远程判断  */
    if (LocalDrTboxHeatLevel <= tmp)
    {
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
        enHeatType_EN_HEAT_TYPE_TBOX;
      Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = (enHeatLvlSts)
        Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(LocalDrTboxHeatLevel);
    }

    if (Appl_HeatAdj_CtrlModel_DW.is_ThirdHeatLevelDeal ==
        Appl_HeatAdj_CtrlModel_IN_BM400_ThirdHeatLevelDeal)
    {
      /* P20车型方向盘加热 */
      if (enProjectType_EN_PROJECT_P20 == HeatAdj_CarType)
      {
        Appl_HeatAdj_CtrlModel_DW.is_ThirdHeatLevelDeal =
          Appl_HeatAdj_CtrlModel_IN_P20_SteerWheeling;
        Appl_HeatAdj_CtrlModel_CANAquireFunction((INT8U)
          HeatAdj_D_SimuIndex_ThirdHeat,
          Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message, HeatAdj_PowerMode,
          &Appl_HeatAdj_CtrlModel_B.IVISwCan,
          &Appl_HeatAdj_CtrlModel_DW.CANAquireFunction);
        Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1
          (Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig,
           Appl_HeatAdj_CtrlModel_B.IVISwCan, HeatAdj_ThirdHeatStopReason,
           Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, &LocalDrTboxHeatLevel,
           &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction);

        /*  三排加热大屏判断  */
        if (LocalDrTboxHeatLevel <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_HMI;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (LocalDrTboxHeatLevel);
        }

        if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
        {
          Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1
            (Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig,
             Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message,
             HeatAdj_ThirdHeatStopReason,
             Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, &LocalDrTboxHeatLevel,
             &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction1);
        }
        else
        {
          LocalDrTboxHeatLevel = (INT8U)0xFF;
        }

        /*  三排加热远程判断  */
        if (LocalDrTboxHeatLevel <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_TBOX;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (LocalDrTboxHeatLevel);
        }
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.Type_o = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_LevelAquireFunction
          (Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig, HeatAdj_CarType,
           Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message,
           HeatAdj_ThirdHeatStopReason,
           Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, HeatAdj_CanThirdHeatLvl,
           Appl_HeatAdj_CtrlModel_B.Type_o, &Appl_HeatAdj_CtrlModel_B.Level_j,
           &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction4);

        /*  三排加热大屏判断  */
        if (Appl_HeatAdj_CtrlModel_B.Level_j <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_HMI;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (Appl_HeatAdj_CtrlModel_B.Level_j);
        }

        if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
        {
          Appl_HeatAdj_CtrlModel_B.EnableCfg_lg =
            Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig;
          Appl_HeatAdj_CtrlModel_B.CarTypeCfg_e = HeatAdj_CarType;
          Appl_HeatAdj_CtrlModel_B.CAN_Message_ns =
            Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message;
          Appl_HeatAdj_CtrlModel_B.DisableSts_b = HeatAdj_ThirdHeatStopReason;
          Appl_HeatAdj_CtrlModel_B.ComPCFlag_f =
            Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag;
          Appl_HeatAdj_CtrlModel_B.CanLvl_f = HeatAdj_CanThirdHeatLvl;
          Appl_HeatAdj_CtrlModel_B.Type_m = ((BOOL)TRUE);
          Appl_HeatAdj_CtrlModel_LevelAquireFunction
            (Appl_HeatAdj_CtrlModel_B.EnableCfg_lg,
             Appl_HeatAdj_CtrlModel_B.CarTypeCfg_e,
             Appl_HeatAdj_CtrlModel_B.CAN_Message_ns,
             Appl_HeatAdj_CtrlModel_B.DisableSts_b,
             Appl_HeatAdj_CtrlModel_B.ComPCFlag_f,
             Appl_HeatAdj_CtrlModel_B.CanLvl_f, Appl_HeatAdj_CtrlModel_B.Type_m,
             &Appl_HeatAdj_CtrlModel_B.Level_kl,
             &Appl_HeatAdj_CtrlModel_DW.LevelAquireFunction5);
          LocalDrTboxHeatLevel = Appl_HeatAdj_CtrlModel_B.Level_kl;
        }
        else
        {
          LocalDrTboxHeatLevel = (INT8U)0xFF;
        }

        /*  三排加热远程判断  */
        if (LocalDrTboxHeatLevel <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_TBOX;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (LocalDrTboxHeatLevel);
        }
      }
    }
    else
    {
      /* 三排加热 */
      if (enProjectType_EN_PROJECT_P20 != HeatAdj_CarType)
      {
        Appl_HeatAdj_CtrlModel_DW.is_ThirdHeatLevelDeal =
          Appl_HeatAdj_CtrlModel_IN_BM400_ThirdHeatLevelDeal;
        Appl_HeatA_enter_internal_BM400_ThirdHeatLevelDeal(&LocalDrTboxHeatLevel,
          &CarTypeCfg_me, &CAN_Message_e, &DisableSts_he, &ComPCFlag_lf,
          &CanLvl_pr);
      }
      else
      {
        Appl_HeatAdj_CtrlModel_CANAquireFunction((INT8U)
          HeatAdj_D_SimuIndex_ThirdHeat,
          Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message, HeatAdj_PowerMode,
          &Appl_HeatAdj_CtrlModel_B.IVISwCan,
          &Appl_HeatAdj_CtrlModel_DW.CANAquireFunction);
        Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1
          (Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig,
           Appl_HeatAdj_CtrlModel_B.IVISwCan, HeatAdj_ThirdHeatStopReason,
           Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, &LocalDrTboxHeatLevel,
           &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction);

        /*  三排加热大屏判断  */
        if (LocalDrTboxHeatLevel <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_HMI;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (LocalDrTboxHeatLevel);
        }

        if (((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot)
        {
          Appl_HeatAdj_CtrlModel_SwLevelAquireFunction1
            (Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig,
             Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message,
             HeatAdj_ThirdHeatStopReason,
             Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag, &LocalDrTboxHeatLevel,
             &Appl_HeatAdj_CtrlModel_DW.SwLevelAquireFunction1);
        }
        else
        {
          LocalDrTboxHeatLevel = (INT8U)0xFF;
        }

        /*  三排加热远程判断  */
        if (LocalDrTboxHeatLevel <= tmp)
        {
          Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType =
            enHeatType_EN_HEAT_TYPE_TBOX;
          Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = (enHeatLvlSts)
            Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n
            (LocalDrTboxHeatLevel);
        }
      }
    }
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c2_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c2_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Driver_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.DriverVentilateValid, &LocalDrTboxHeatLevel);
    CAN_Message_e = LocalDrTboxHeatLevel;
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Passenger_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.PassengerVentilateValid, &LocalDrTboxHeatLevel);
    ComPCFlag_lf = LocalDrTboxHeatLevel;
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Third_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.ThirdVentilateValid, &LocalDrTboxHeatLevel);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel,
       Appl_HeatAdj_CtrlModel_B.DriverHeatError, CAN_Message_e, HeatAdj_CarType,
       HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_be,
       &Appl_HeatAdj_CtrlModel_B.StopReason_c,
       &Appl_HeatAdj_CtrlModel_B.CANStopReason_j,
       &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel,
       Appl_HeatAdj_CtrlModel_B.PassengerHeatError, ComPCFlag_lf,
       HeatAdj_CarType, HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_g,
       &Appl_HeatAdj_CtrlModel_B.StopReason_ew,
       &Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
       &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction1);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel,
       Appl_HeatAdj_CtrlModel_B.ThirdHeatError, LocalDrTboxHeatLevel,
       HeatAdj_CarType, HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_p, &Appl_HeatAdj_CtrlModel_B.StopReason_d,
       &DisableSts_he, &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction2);
    Appl_HeatAdj_CtrlModel_B.TimeoutPrm = HeatAdj_TimeOutPrm;
    Appl_HeatAdj_CtrlModel_B.MaxTime_h = Appl_HeatAdj_CtrlModel_B.Product;
    Appl_HeatAdj_CtrlModel_B.InLevel = Appl_HeatAdj_CtrlModel_B.Level_be;
    Appl_HeatAdj_CtrlModel_TimeoutFunction();
    Appl_HeatAdj_CtrlModel_B.TimeoutPrm_k = HeatAdj_TimeOutPrm;
    Appl_HeatAdj_CtrlModel_B.MaxTime_k = Appl_HeatAdj_CtrlModel_B.Product;
    Appl_HeatAdj_CtrlModel_B.InLevel_p = Appl_HeatAdj_CtrlModel_B.Level_g;
    Appl_HeatAdj_CtrlModel_TimeoutFunction1();
    Appl_HeatAdj_CtrlModel_TimeoutFunction2(Appl_HeatAdj_CtrlModel_B.Level_p,
      (INT32U)Appl_HeatAdj_CtrlModel_DW.Delay_DSTATE_c, &Level_l,
      &LocalDrTboxHeatLevel, &Appl_HeatAdj_CtrlModel_DW.TimeoutFunction2);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_c,
      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_b,
      Appl_HeatAdj_CtrlModel_B.CANStopReason_j,
      &Appl_HeatAdj_CtrlModel_B.DrHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.DrCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_ew,
      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_j,
      Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
      &Appl_HeatAdj_CtrlModel_B.PaHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.PaCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction1);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_d,
      LocalDrTboxHeatLevel, Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
      &Appl_HeatAdj_CtrlModel_B.ThirdHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.ThirdCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction2);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_DriverDiagCmd,
      Appl_HeatAdj_CtrlModel_B.Level_b,
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType,
      &Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatDriverRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_PassengerDiagCmd,
      Appl_HeatAdj_CtrlModel_B.Level_i,
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType,
      &Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatPassengerRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction1);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_ThirdDiagCmd, Level_l,
      Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType,
      &Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatThirdRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction2);
  }
  else
  {
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Driver_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.DriverVentilateValid, &LocalDrTboxHeatLevel);
    CAN_Message_e = LocalDrTboxHeatLevel;
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Passenger_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.PassengerVentilateValid, &LocalDrTboxHeatLevel);
    ComPCFlag_lf = LocalDrTboxHeatLevel;
    Appl_HeatAdj_CtrlModel_MixConflic
      (Appl_HeatAdj_CtrlModel_B.Third_MixConflicFlg,
       Appl_HeatAdj_CtrlModel_B.ThirdVentilateValid, &LocalDrTboxHeatLevel);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel,
       Appl_HeatAdj_CtrlModel_B.DriverHeatError, CAN_Message_e, HeatAdj_CarType,
       HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_be,
       &Appl_HeatAdj_CtrlModel_B.StopReason_c,
       &Appl_HeatAdj_CtrlModel_B.CANStopReason_j,
       &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel,
       Appl_HeatAdj_CtrlModel_B.PassengerHeatError, ComPCFlag_lf,
       HeatAdj_CarType, HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_g,
       &Appl_HeatAdj_CtrlModel_B.StopReason_ew,
       &Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
       &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction1);
    Appl_HeatAdj_CtrlModel_LevelLimitFunction
      (Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel,
       Appl_HeatAdj_CtrlModel_B.ThirdHeatError, LocalDrTboxHeatLevel,
       HeatAdj_CarType, HeatAdj_HeatMsgLostFlag, HeatAdj_RecoverDefaultFlag,
       &Appl_HeatAdj_CtrlModel_B.Level_p, &Appl_HeatAdj_CtrlModel_B.StopReason_d,
       &DisableSts_he, &Appl_HeatAdj_CtrlModel_DW.LevelLimitFunction2);
    Appl_HeatAdj_CtrlModel_B.TimeoutPrm = HeatAdj_TimeOutPrm;
    Appl_HeatAdj_CtrlModel_B.MaxTime_h = Appl_HeatAdj_CtrlModel_B.Product;
    Appl_HeatAdj_CtrlModel_B.InLevel = Appl_HeatAdj_CtrlModel_B.Level_be;
    Appl_HeatAdj_CtrlModel_TimeoutFunction();
    Appl_HeatAdj_CtrlModel_B.TimeoutPrm_k = HeatAdj_TimeOutPrm;
    Appl_HeatAdj_CtrlModel_B.MaxTime_k = Appl_HeatAdj_CtrlModel_B.Product;
    Appl_HeatAdj_CtrlModel_B.InLevel_p = Appl_HeatAdj_CtrlModel_B.Level_g;
    Appl_HeatAdj_CtrlModel_TimeoutFunction1();
    Appl_HeatAdj_CtrlModel_TimeoutFunction2(Appl_HeatAdj_CtrlModel_B.Level_p,
      (INT32U)Appl_HeatAdj_CtrlModel_DW.Delay_DSTATE_c, &Level_l,
      &LocalDrTboxHeatLevel, &Appl_HeatAdj_CtrlModel_DW.TimeoutFunction2);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_c,
      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_b,
      Appl_HeatAdj_CtrlModel_B.CANStopReason_j,
      &Appl_HeatAdj_CtrlModel_B.DrHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.DrCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_ew,
      Appl_HeatAdj_CtrlModel_B.TimeoutFlag_j,
      Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
      &Appl_HeatAdj_CtrlModel_B.PaHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.PaCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction1);
    Appl_HeatAdj_CtrlModel_StopFunction(Appl_HeatAdj_CtrlModel_B.StopReason_d,
      LocalDrTboxHeatLevel, Appl_HeatAdj_CtrlModel_B.CANStopReason_ky,
      &Appl_HeatAdj_CtrlModel_B.ThirdHeatStopReason,
      &Appl_HeatAdj_CtrlModel_B.ThirdCANHeatStopReason,
      &Appl_HeatAdj_CtrlModel_DW.StopFunction2);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_DriverDiagCmd,
      Appl_HeatAdj_CtrlModel_B.Level_b,
      Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType,
      &Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatDriverRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_PassengerDiagCmd,
      Appl_HeatAdj_CtrlModel_B.Level_i,
      Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType,
      &Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatPassengerRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction1);
    Appl_HeatAdj_CtrlModel_DiagnoseFunction((INT8U)HeatAdj_ThirdDiagCmd, Level_l,
      Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType,
      &Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatThirdRunType,
      &Appl_HeatAdj_CtrlModel_DW.DiagnoseFunction2);
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c14_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c14_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_CANOutputDeal =
      Appl_HeatAdj_CtrlModel_IN_Default_h;
    Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel =
      Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel;
    Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel =
      Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel;
    Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel =
      Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
    Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_DW.is_DrErr = Appl_HeatAdj_CtrlModel_IN_FalseSts;
    Appl_HeatAdj_CtrlModel_B.OutDrRunState =
      Appl_HeatAdj_CtrlModel_DW.LocalDrRunState;
    Appl_HeatAdj_CtrlModel_DW.is_PaErr = Appl_HeatAdj_CtrlModel_IN_FalseSts;
    Appl_HeatAdj_CtrlModel_B.OutPaRunState =
      Appl_HeatAdj_CtrlModel_DW.LocalPaRunState;
    Appl_HeatAdj_CtrlModel_DW.is_ThirdErr = Appl_HeatAdj_CtrlModel_IN_FalseSts;
    Appl_HeatAdj_CtrlModel_B.Out3rdRunState =
      Appl_HeatAdj_CtrlModel_DW.Local3rdRunState;
    Appl_HeatAdj_CtrlModel_B.AimLevel = Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType = (INT8U)HeatAdj_CarType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_TempFunction();
    Appl_HeatAdj_CtrlModel_B.AimLevel_c =
      Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType_p = (INT8U)HeatAdj_CarType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat_i = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_TempFunction1();
    Appl_HeatAdj_CtrlModel_B.AimLevel_d =
      Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType_d = (INT8U)HeatAdj_CarType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat_o = ((BOOL)TRUE);
    Appl_HeatAdj_CtrlModel_TempFunction2();
    Appl_HeatAdj_CtrlModel_HeatOutFunction(Appl_HeatAdj_CtrlModel_B.AimTemp_a,
      HeatAdj_DrHeatNtcAdc, Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatOutGpio_e,
      &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_ik,
      &Appl_HeatAdj_CtrlModel_B.HeatOutFunction,
      &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction);
    Appl_HeatAdj_CtrlModel_B.HeatAdj_DRHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio_e);
    Appl_HeatAdj_CtrlModel_HeatOutFunction(Appl_HeatAdj_CtrlModel_B.AimTemp_h,
      HeatAdj_PaHeatNtcAdc, Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatOutGpio_l,
      &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_i,
      &Appl_HeatAdj_CtrlModel_B.HeatOutFunction1,
      &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction1);
    Appl_HeatAdj_CtrlModel_B.HeatAdj_PAHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio_l);
    Appl_HeatAdj_CtrlModel_B.SetTemp_a = Appl_HeatAdj_CtrlModel_B.AimTemp;
    Appl_HeatAdj_CtrlModel_B.CurrentTemp_m = HeatAdj_ThirdHeatNtcAdc;
    Appl_HeatAdj_CtrlModel_B.HeatLvl_i =
      Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
    Appl_HeatAdj_CtrlModel_B.MaxTime = Appl_HeatAdj_CtrlModel_B.Switch;
    Appl_HeatAdj_CtrlModel_HeatOutFunction2();
    Appl_HeatAdj_CtrlModel_B.HeatAdj_ThirdHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio);
    Appl_HeatAdj_CtrlModel_DW.Delay_DSTATE_c =
      Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag;
    Appl_HeatAdj_CtrlModel_B.Sw20minTimerOut =
      Appl_HeatAdj_CtrlModel_B.Sw20minTimer;
  }
  else
  {
    if (Appl_HeatAdj_CtrlModel_DW.is_CANOutputDeal ==
        Appl_HeatAdj_CtrlModel_IN_Default_h)
    {
      /*  P20的车型  */
      if (enProjectType_EN_PROJECT_P20 == HeatAdj_CarType)
      {
        Appl_HeatAdj_CtrlModel_DW.is_CANOutputDeal =
          Appl_HeatAdj_CtrlModel_IN_ProjectP20;

        /* Initial Value(Hex)初始值:0x0 */
        Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel =
          enHeatLvlSts_EN_HEAT_LVL_OFF;
        Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel =
          enHeatLvlSts_EN_HEAT_LVL_OFF;
        Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel =
          enHeatLvlSts_EN_HEAT_LVL_OFF;
        Appl_HeatAdj_CtrlModel_DW.is_Drv = Appl_HeatAdj_CtrlModel_IN_Init_c;
        Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.is_Pas = Appl_HeatAdj_CtrlModel_IN_Init_c;
        Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.is_Treble = Appl_HeatAdj_CtrlModel_IN_Init_c;
        Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel;
        Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel;
        Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
        Appl_HeatAdj_CtrlModel_B.OutDrRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_B.OutPaRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
      }
    }
    else
    {
      /*  非P20车型  */
      if (enProjectType_EN_PROJECT_P20 != HeatAdj_CarType)
      {
        Appl_HeatAdj_CtrlModel_DW.is_Treble =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
        Appl_HeatAdj_CtrlModel_DW.is_Pas =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
        Appl_HeatAdj_CtrlModel_DW.is_Drv =
          Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_b5;
        Appl_HeatAdj_CtrlModel_DW.is_CANOutputDeal =
          Appl_HeatAdj_CtrlModel_IN_Default_h;
        Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel;
        Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel;
        Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel =
          Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
        Appl_HeatAdj_CtrlModel_B.OutDrRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_B.OutPaRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
        Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
      }
      else
      {
        if (Appl_HeatAdj_CtrlModel_DW.is_Drv == Appl_HeatAdj_CtrlModel_IN_Init_c)
        {
          /*  主驾加热指令  */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF !=
              Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Drv = Appl_HeatAdj_CtrlModel_IN_Run_k;

            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  主驾加热无指令 ,档位反馈关闭前档位 */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF ==
              Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Drv = Appl_HeatAdj_CtrlModel_IN_Init_c;
            Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)FALSE);
          }
          else
          {
            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.LocalDrRunState = ((BOOL)TRUE);
          }
        }

        if (Appl_HeatAdj_CtrlModel_DW.is_Pas == Appl_HeatAdj_CtrlModel_IN_Init_c)
        {
          /*  副驾加热指令  */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF !=
              Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Pas = Appl_HeatAdj_CtrlModel_IN_Run_k;

            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  副驾加热无指令 ,档位反馈关闭前档位 */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF ==
              Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Pas = Appl_HeatAdj_CtrlModel_IN_Init_c;
            Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)FALSE);
          }
          else
          {
            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.LocalPaRunState = ((BOOL)TRUE);
          }
        }

        if (Appl_HeatAdj_CtrlModel_DW.is_Treble ==
            Appl_HeatAdj_CtrlModel_IN_Init_c)
        {
          /*  三排加热无指令  */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF !=
              Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Treble =
              Appl_HeatAdj_CtrlModel_IN_Run_k;

            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)TRUE);
          }
        }
        else
        {
          /*  三排加热无指令 ,档位反馈关闭前档位 */
          if (enHeatLvlSts_EN_HEAT_LVL_OFF ==
              Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel)
          {
            Appl_HeatAdj_CtrlModel_DW.is_Treble =
              Appl_HeatAdj_CtrlModel_IN_Init_c;
            Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)FALSE);
          }
          else
          {
            /* 0x0:Level 1  1档
               0x1:Level 2   2档
               0x2:Level 3   3档 */
            if ((INT32S)Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel < -2147483647)
            {
              Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n(MIN_int32_T);
            }
            else
            {
              Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = (enHeatLvlSts)
                Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatLvlSts_n((INT32S)
                Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel - 1);
            }

            Appl_HeatAdj_CtrlModel_DW.Local3rdRunState = ((BOOL)TRUE);
          }
        }
      }
    }

    if (Appl_HeatAdj_CtrlModel_DW.is_DrErr == Appl_HeatAdj_CtrlModel_IN_ErrSts)
    {
      /* 无故障 或RUN状态  */
      if ((Appl_HeatAdj_CtrlModel_DW.LocalDrRunState == ((BOOL)TRUE)) ||
          (Appl_HeatAdj_CtrlModel_B.DriverHeatErrorDtc == ((BOOL)FALSE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_DrErr = Appl_HeatAdj_CtrlModel_IN_FalseSts;
        Appl_HeatAdj_CtrlModel_B.OutDrRunState =
          Appl_HeatAdj_CtrlModel_DW.LocalDrRunState;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.OutDrRunState = 2U;
      }
    }
    else
    {
      /*  无指令 且存在故障  */
      if ((Appl_HeatAdj_CtrlModel_DW.LocalDrRunState == ((BOOL)FALSE)) &&
          (Appl_HeatAdj_CtrlModel_B.DriverHeatErrorDtc == ((BOOL)TRUE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_DrErr = Appl_HeatAdj_CtrlModel_IN_ErrSts;
        Appl_HeatAdj_CtrlModel_B.OutDrRunState = 2U;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.OutDrRunState =
          Appl_HeatAdj_CtrlModel_DW.LocalDrRunState;
      }
    }

    if (Appl_HeatAdj_CtrlModel_DW.is_PaErr == Appl_HeatAdj_CtrlModel_IN_ErrSts)
    {
      /* 无故障 或RUN状态  */
      if ((Appl_HeatAdj_CtrlModel_DW.LocalPaRunState == ((BOOL)TRUE)) ||
          (Appl_HeatAdj_CtrlModel_B.PassengerHeatErrorDtc == ((BOOL)FALSE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_PaErr = Appl_HeatAdj_CtrlModel_IN_FalseSts;
        Appl_HeatAdj_CtrlModel_B.OutPaRunState =
          Appl_HeatAdj_CtrlModel_DW.LocalPaRunState;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.OutPaRunState = 2U;
      }
    }
    else
    {
      /*  无指令 且存在故障  */
      if ((Appl_HeatAdj_CtrlModel_DW.LocalPaRunState == ((BOOL)FALSE)) &&
          (Appl_HeatAdj_CtrlModel_B.PassengerHeatErrorDtc == ((BOOL)TRUE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_PaErr = Appl_HeatAdj_CtrlModel_IN_ErrSts;
        Appl_HeatAdj_CtrlModel_B.OutPaRunState = 2U;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.OutPaRunState =
          Appl_HeatAdj_CtrlModel_DW.LocalPaRunState;
      }
    }

    if (Appl_HeatAdj_CtrlModel_DW.is_ThirdErr ==
        Appl_HeatAdj_CtrlModel_IN_ErrSts)
    {
      /* 无故障 或RUN状态  */
      if ((Appl_HeatAdj_CtrlModel_DW.Local3rdRunState == ((BOOL)TRUE)) ||
          (Appl_HeatAdj_CtrlModel_B.ThirdHeatErrorDtc == ((BOOL)FALSE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_ThirdErr =
          Appl_HeatAdj_CtrlModel_IN_FalseSts;
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState =
          Appl_HeatAdj_CtrlModel_DW.Local3rdRunState;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState = 2U;
      }
    }
    else
    {
      /*  无指令 且存在故障  */
      if ((Appl_HeatAdj_CtrlModel_DW.Local3rdRunState == ((BOOL)FALSE)) &&
          (Appl_HeatAdj_CtrlModel_B.ThirdHeatErrorDtc == ((BOOL)TRUE)))
      {
        Appl_HeatAdj_CtrlModel_DW.is_ThirdErr = Appl_HeatAdj_CtrlModel_IN_ErrSts;
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState = 2U;
      }
      else
      {
        Appl_HeatAdj_CtrlModel_B.Out3rdRunState =
          Appl_HeatAdj_CtrlModel_DW.Local3rdRunState;
      }
    }

    Appl_HeatAdj_CtrlModel_B.AimLevel = Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType = (INT8U)HeatAdj_CarType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_TempFunction();
    Appl_HeatAdj_CtrlModel_B.AimLevel_c =
      Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType_p =
      Appl_HeatAdj_CtrlModel_B.ProjectType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat_i = ((BOOL)FALSE);
    Appl_HeatAdj_CtrlModel_TempFunction1();
    Appl_HeatAdj_CtrlModel_B.AimLevel_d =
      Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
    Appl_HeatAdj_CtrlModel_B.ProjectType_d =
      Appl_HeatAdj_CtrlModel_B.ProjectType;
    Appl_HeatAdj_CtrlModel_B.ThirdHeat_o = ((BOOL)TRUE);
    Appl_HeatAdj_CtrlModel_TempFunction2();
    Appl_HeatAdj_CtrlModel_HeatOutFunction(Appl_HeatAdj_CtrlModel_B.AimTemp_a,
      HeatAdj_DrHeatNtcAdc, Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatOutGpio_e,
      &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_ik,
      &Appl_HeatAdj_CtrlModel_B.HeatOutFunction,
      &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction);
    Appl_HeatAdj_CtrlModel_B.HeatAdj_DRHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio_e);
    Appl_HeatAdj_CtrlModel_HeatOutFunction(Appl_HeatAdj_CtrlModel_B.AimTemp_h,
      HeatAdj_PaHeatNtcAdc, Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel,
      &Appl_HeatAdj_CtrlModel_B.HeatOutGpio_l,
      &Appl_HeatAdj_CtrlModel_B.HeatOutPwmCnt_i,
      &Appl_HeatAdj_CtrlModel_B.HeatOutFunction1,
      &Appl_HeatAdj_CtrlModel_DW.HeatOutFunction1);
    Appl_HeatAdj_CtrlModel_B.HeatAdj_PAHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio_l);
    Appl_HeatAdj_CtrlModel_B.SetTemp_a = Appl_HeatAdj_CtrlModel_B.AimTemp;
    Appl_HeatAdj_CtrlModel_B.CurrentTemp_m = HeatAdj_ThirdHeatNtcAdc;
    Appl_HeatAdj_CtrlModel_B.HeatLvl_i =
      Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel;
    Appl_HeatAdj_CtrlModel_B.MaxTime = Appl_HeatAdj_CtrlModel_B.Switch;
    Appl_HeatAdj_CtrlModel_HeatOutFunction2();
    Appl_HeatAdj_CtrlModel_B.HeatAdj_ThirdHeatIo = (enHeatIoSts)
      Appl_HeatAdj_CtrlModel_safe_cast_to_enHeatIoSts
      (Appl_HeatAdj_CtrlModel_B.HeatOutGpio);
    Appl_HeatAdj_CtrlModel_DW.Delay_DSTATE_c =
      Appl_HeatAdj_CtrlModel_B.SwTimeoutFlag;
    Appl_HeatAdj_CtrlModel_B.Sw20minTimerOut =
      Appl_HeatAdj_CtrlModel_B.Sw20minTimer;
  }
}

/*
 * System initialize for function-call system:
 *    '<S102>/ErrorFunction2'
 *    '<S102>/ErrorFunction3'
 *    '<S102>/ErrorFunction1'
 *    '<S102>/ErrorFunction4'
 *    '<S102>/ErrorFunction'
 *    '<S102>/ErrorFunction5'
 */
static void Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(INT8U *rty_HeatError,
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_active_c21_Appl_HeatAdj_CtrlModel = 0U;
  localDW->is_c21_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_i;
  *rty_HeatError = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S102>/ErrorFunction2'
 *    '<S102>/ErrorFunction3'
 *    '<S102>/ErrorFunction1'
 *    '<S102>/ErrorFunction4'
 *    '<S102>/ErrorFunction'
 *    '<S102>/ErrorFunction5'
 */
static void Appl_HeatAdj_CtrlModel_ErrorFunction2(INT8U rtu_FirstFaultSts, INT8U
  rtu_SecondFaultSts, INT8U *rty_HeatError,
  DW_ErrorFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c21_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c21_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_c21_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Default_p;
    *rty_HeatError = ((BOOL)FALSE);
  }
  else if (localDW->is_c21_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_p)
  {
    *rty_HeatError = ((BOOL)FALSE);

    /* 任一故障输入 */
    if ((((BOOL)FALSE) != rtu_FirstFaultSts) || (((BOOL)FALSE) !=
         rtu_SecondFaultSts))
    {
      localDW->is_c21_Appl_HeatAdj_CtrlModel = Appl_HeatAdj_CtrlModel_IN_Fault;
      *rty_HeatError = ((BOOL)TRUE);
    }
  }
  else
  {
    *rty_HeatError = ((BOOL)TRUE);

    /* 无故障输入 */
    if ((((BOOL)FALSE) == rtu_FirstFaultSts) && (((BOOL)FALSE) ==
         rtu_SecondFaultSts))
    {
      localDW->is_c21_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_p;
      *rty_HeatError = ((BOOL)FALSE);
    }
  }
}

/*
 * System initialize for function-call system:
 *    '<S115>/MsgConflictFunction2'
 *    '<S115>/MsgConflictFunction1'
 *    '<S115>/MsgConflictFunction'
 */
static void Appl_HeatAdj_CtrlModel_MsgConflictFunction2_Init(INT8U
  *rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_HMI_MessageDeal = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_h;
  localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_h;
  localDW->is_Tbox_MessageDeal = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_h;
  localDW->is_active_c48_Appl_HeatAdj_CtrlModel = 0U;
  localDW->HMI_Flag = 0U;
  localDW->Tbox_Flag = 0U;
  *rty_OutMsgHMI = 0U;
  *rty_OutMsgTbox = 0U;
  *rty_MixConflictFlg = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S115>/MsgConflictFunction2'
 *    '<S115>/MsgConflictFunction1'
 *    '<S115>/MsgConflictFunction'
 */
static void Appl_HeatAdj_CtrlModel_MsgConflictFunction2(INT8U rtu_CarTypeCfg,
  INT8U rtu_HMI_Message, INT8U rtu_Tbox_Message, INT8U rtu_VentValidFlag, INT8U *
  rty_OutMsgHMI, INT8U *rty_OutMsgTbox, INT8U *rty_MixConflictFlg,
  DW_MsgConflictFunction2_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c48_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c48_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_HMI_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
    localDW->HMI_Flag = ((BOOL)FALSE);
    localDW->is_Tbox_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
    localDW->Tbox_Flag = ((BOOL)FALSE);
    localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
    *rty_OutMsgHMI = rtu_HMI_Message;
    *rty_OutMsgTbox = rtu_Tbox_Message;
    *rty_MixConflictFlg = ((BOOL)FALSE);
  }
  else
  {
    if (localDW->is_HMI_MessageDeal == Appl_HeatAdj_CtrlModel_IN_Default_l)
    {
      /* HMI加热报文有效0x0:Inactive；0x1:Level 1；1档;0x2:Level 2；2档;0x3:Level 3；3档；0x4:OFF: 0x05 OPEN */
      if (((INT32S)enHeatLvlSts_EN_HEAT_LVL_1 == rtu_HMI_Message) || ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_2 == rtu_HMI_Message) || ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_3 == rtu_HMI_Message) || (4 ==
           rtu_HMI_Message) || (5 == rtu_HMI_Message))
      {
        localDW->is_HMI_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Valid;
        localDW->HMI_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* HMI加热报文无效，20240507NXM增加关闭4 */
      if (((INT32S)enHeatLvlSts_EN_HEAT_LVL_1 != rtu_HMI_Message) && ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_2 != rtu_HMI_Message) && ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_3 != rtu_HMI_Message) && (4 !=
           rtu_HMI_Message) && (5 != rtu_HMI_Message))
      {
        localDW->is_HMI_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
        localDW->HMI_Flag = ((BOOL)FALSE);
      }
    }

    if (localDW->is_Tbox_MessageDeal == Appl_HeatAdj_CtrlModel_IN_Default_l)
    {
      /* Tbox加热报文有效0x0:No Request；0x1:Heat_1；0x2:Heat_2；0x3:Heat_3；0x4:Close */
      if (((INT32S)enHeatLvlSts_EN_HEAT_LVL_1 == rtu_Tbox_Message) || ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_2 == rtu_Tbox_Message) || ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_3 == rtu_Tbox_Message) || (4 ==
           rtu_Tbox_Message))
      {
        localDW->is_Tbox_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Valid;
        localDW->Tbox_Flag = ((BOOL)TRUE);
      }
    }
    else
    {
      /* Tbox加热报文无效，20240507NXM增加关闭4 */
      if (((INT32S)enHeatLvlSts_EN_HEAT_LVL_1 != rtu_Tbox_Message) && ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_2 != rtu_Tbox_Message) && ((INT32S)
           enHeatLvlSts_EN_HEAT_LVL_3 != rtu_Tbox_Message) && (4 !=
           rtu_Tbox_Message))
      {
        localDW->is_Tbox_MessageDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
        localDW->Tbox_Flag = ((BOOL)FALSE);
      }
    }

    switch (localDW->is_MessageConflictDeal)
    {
     case Appl_HeatAdj_CtrlModel_IN_Default_l:
      /* P20车型HMI、TBOX加热报文同时有效 */
      if (((INT32S)enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg) && (((BOOL)
            FALSE) != localDW->HMI_Flag) && (((BOOL)FALSE) != localDW->Tbox_Flag))
      {
        localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_HeatConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)FALSE);
      }
      else
      {
        /* 通风加热报文同时有效 不包含关闭  */
        if ((((BOOL)FALSE) != rtu_VentValidFlag) && (((((BOOL)FALSE) !=
               localDW->HMI_Flag) && (4 != rtu_HMI_Message)) || ((((BOOL)FALSE)
               != localDW->Tbox_Flag) && (4 != rtu_Tbox_Message))))
        {
          localDW->is_MessageConflictDeal =
            Appl_HeatAdj_CtrlModel_IN_VentilateConflict;
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

     case Appl_HeatAdj_CtrlModel_IN_HeatConflict:
      /* 通风加热报文同时有效，20240507NXM */
      if ((((BOOL)FALSE) != rtu_VentValidFlag) && ((((BOOL)FALSE) !=
            localDW->HMI_Flag) || (((BOOL)FALSE) != localDW->Tbox_Flag)))
      {
        localDW->is_MessageConflictDeal =
          Appl_HeatAdj_CtrlModel_IN_VentilateConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)TRUE);
      }
      else
      {
        /* 非P20车型||P20车型加热报文不同时有效，20240507NXM */
        if (((INT32S)enProjectType_EN_PROJECT_P20 != rtu_CarTypeCfg) || ((((BOOL)
               FALSE) == localDW->HMI_Flag) || (((BOOL)FALSE) ==
              localDW->Tbox_Flag)))
        {
          localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
          *rty_OutMsgHMI = rtu_HMI_Message;
          *rty_OutMsgTbox = rtu_Tbox_Message;
          *rty_MixConflictFlg = ((BOOL)FALSE);
        }
      }
      break;

     default:
      /* P20车型HMI、TBOX加热报文同时有效 */
      if (((INT32S)enProjectType_EN_PROJECT_P20 == rtu_CarTypeCfg) && (((BOOL)
            FALSE) != localDW->HMI_Flag) && (((BOOL)FALSE) != localDW->Tbox_Flag)
          && (((BOOL)FALSE) == rtu_VentValidFlag))
      {
        localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_HeatConflict;
        *rty_OutMsgHMI = 0U;
        *rty_OutMsgTbox = 0U;
        *rty_MixConflictFlg = ((BOOL)FALSE);
      }
      else
      {
        /* 通风加热报文不同时有效或关闭，20240507NXM修改跳转顺序 */
        if ((((BOOL)FALSE) == rtu_VentValidFlag) || (4 == rtu_HMI_Message) || (4
             == rtu_Tbox_Message))
        {
          localDW->is_MessageConflictDeal = Appl_HeatAdj_CtrlModel_IN_Default_l;
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
 * System initialize for function-call system:
 *    '<S125>/OppositeMessageDeal'
 *    '<S125>/OppositeMessageDeal1'
 *    '<S125>/OppositeMessageDeal2'
 */
static void Appl_HeatAdj_CtrlModel_OppositeMessageDeal_Init(INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T *localDW)
{
  localDW->is_HMIMessageDeal = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_hk;
  localDW->is_TboxMessageDeal = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_hk;
  localDW->is_VenStatus = Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_hk;
  localDW->is_active_c9_Appl_HeatAdj_CtrlModel = 0U;
  localDW->TempHMI = 0U;
  localDW->TempTbox = 0U;
  *rty_VenSts = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S125>/OppositeMessageDeal'
 *    '<S125>/OppositeMessageDeal1'
 *    '<S125>/OppositeMessageDeal2'
 */
static void Appl_HeatAdj_CtrlModel_OppositeMessageDeal(enProjectType
  rtu_CarTypeCfg, INT8U rtu_RemoteModeFlag, INT8U rtu_HMI_Message, INT8U
  rtu_Tbox_Message, INT8U rtu_VentCfg, INT8U *rty_VenSts,
  DW_OppositeMessageDeal_Appl_HeatAdj_CtrlModel_T *localDW)
{
  if (localDW->is_active_c9_Appl_HeatAdj_CtrlModel == 0U)
  {
    localDW->is_active_c9_Appl_HeatAdj_CtrlModel = 1U;
    localDW->is_HMIMessageDeal = Appl_HeatAdj_CtrlModel_IN_HMIInit;
    localDW->TempHMI = ((BOOL)FALSE);
    localDW->is_TboxMessageDeal = Appl_HeatAdj_CtrlModel_IN_TboxInit;
    localDW->TempTbox = ((BOOL)FALSE);
    localDW->is_VenStatus = Appl_HeatAdj_CtrlModel_IN_TotalInit;
    *rty_VenSts = ((BOOL)FALSE);
  }
  else
  {
    if (localDW->is_HMIMessageDeal == Appl_HeatAdj_CtrlModel_IN_HMIInit)
    {
      /* HMI档位请求有效 */
      if (((enProjectType_EN_PROJECT_BM400 != rtu_CarTypeCfg) && ((0x1 ==
             rtu_HMI_Message) || (0x2 == rtu_HMI_Message) || (0x3 ==
             rtu_HMI_Message) || (0x5 == rtu_HMI_Message))) ||
          ((enProjectType_EN_PROJECT_BM400 == rtu_CarTypeCfg) && ((0x8 ==
             rtu_HMI_Message) || (0x9 == rtu_HMI_Message) || (0xA ==
             rtu_HMI_Message))))
      {
        localDW->is_HMIMessageDeal = Appl_HeatAdj_CtrlModel_IN_HMIValid;
        localDW->TempHMI = ((BOOL)TRUE);
      }
    }
    else
    {
      /* HMI报文关闭 */
      if (((enProjectType_EN_PROJECT_BM400 != rtu_CarTypeCfg) && (0x1 !=
            rtu_HMI_Message) && (0x2 != rtu_HMI_Message) && (0x3 !=
            rtu_HMI_Message) && (0x5 != rtu_HMI_Message)) ||
          ((enProjectType_EN_PROJECT_BM400 == rtu_CarTypeCfg) && (0x8 !=
            rtu_HMI_Message) && (0x9 != rtu_HMI_Message) && (0xA !=
            rtu_HMI_Message)))
      {
        localDW->is_HMIMessageDeal = Appl_HeatAdj_CtrlModel_IN_HMIInit;
        localDW->TempHMI = ((BOOL)FALSE);
      }
    }

    if (localDW->is_TboxMessageDeal == Appl_HeatAdj_CtrlModel_IN_TboxInit)
    {
      /* Tbox档位请求有效 */
      if ((((BOOL)TRUE) == rtu_RemoteModeFlag) && ((0x1 == rtu_Tbox_Message) ||
           (0x2 == rtu_Tbox_Message) || (0x3 == rtu_Tbox_Message)))
      {
        localDW->is_TboxMessageDeal = Appl_HeatAdj_CtrlModel_IN_TboxValid;
        localDW->TempTbox = ((BOOL)TRUE);
      }
    }
    else
    {
      /* Tbox报文关闭 */
      if ((((BOOL)FALSE) == rtu_RemoteModeFlag) || ((0x1 != rtu_Tbox_Message) &&
           (0x2 != rtu_Tbox_Message) && (0x3 != rtu_Tbox_Message)))
      {
        localDW->is_TboxMessageDeal = Appl_HeatAdj_CtrlModel_IN_TboxInit;
        localDW->TempTbox = ((BOOL)FALSE);
      }
    }

    if (localDW->is_VenStatus == Appl_HeatAdj_CtrlModel_IN_TotalInit)
    {
      *rty_VenSts = ((BOOL)FALSE);

      /* 档位请求有效 且配置有效 */
      if (((((BOOL)TRUE) == localDW->TempHMI) || (((BOOL)TRUE) ==
            localDW->TempTbox)) && (rtu_VentCfg == ((BOOL)TRUE)))
      {
        localDW->is_VenStatus = Appl_HeatAdj_CtrlModel_IN_TotalValid;
        *rty_VenSts = ((BOOL)TRUE);
      }
    }
    else
    {
      *rty_VenSts = ((BOOL)TRUE);

      /*  档位请求无效 或配置无效  */
      if (((((BOOL)FALSE) == localDW->TempHMI) && (((BOOL)FALSE) ==
            localDW->TempTbox)) || (rtu_VentCfg == ((BOOL)FALSE)))
      {
        localDW->is_VenStatus = Appl_HeatAdj_CtrlModel_IN_TotalInit;
        *rty_VenSts = ((BOOL)FALSE);
      }
    }
  }
}

/*
 * Output and update for atomic system: '<S3>/RTE'
 * Block description for: '<S3>/RTE'
 *   接口自动生成
 */
static void Appl_HeatAdj_CtrlModel_RTE(void)
{
  HeatAdj_CanDrvHeatLvl = Ecual_CanGetDrvHeatLvl( );
  HeatAdj_CanPasHeatLvl = Ecual_CanGetPasHeatLvl( );
  HeatAdj_CanThirdHeatLvl = Ecual_CanGetThirdHeatLvl( );
  HeatAdj_CarType = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
  HeatAdj_DCDCSwitchSts = Vfb_Reserved_0( );
  HeatAdj_D_SimuIndex_DRHeat = Rte_GetVfb_DrHeat( );
  HeatAdj_D_SimuIndex_PAHeat = Rte_GetVfb_PaHeat( );
  HeatAdj_D_SimuIndex_ThirdHeat = Rte_GetVfb_ThirdHeat( );
  HeatAdj_DrHeatNtcAdc = Ecual_AdcGetDrNTCTempValue( );
  HeatAdj_DrHeatStopReason = Rte_GetVfb_DrHeatStopReason( );
  HeatAdj_DrVentFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentFlg);
  HeatAdj_DriverCmdFaultSts = Rte_GetVfb_DrHeatCmdFaultSts( );
  HeatAdj_DriverCmdFaultSts4DTC = Rte_GetVfb_DrHeatCmdFaultSts4DTC( );
  HeatAdj_DriverDiagCmd = Desc_DiagOutCtrlPram(EN_DRHEAT);
  HeatAdj_DriverHMI_Message = CanRx_0x351_IVI_FLSeatHeatSet( );
  HeatAdj_DriverNTCFaultSts = Rte_GetVfb_DrHeatNTCFaultSts( );
  HeatAdj_DriverTbox_Message = CanRx_0x281_BDC_TBOX_Req_DrSeatHeating( );
  HeatAdj_DriverVentEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrvVentConfig);
  HeatAdj_Driver_HMI_VentilateMsg = CanRx_0x351_IVI_FLSeatVentnSet( );
  HeatAdj_Driver_Tbox_VentilateMsg = CanRx_0x281_BDC_TBOX_Req_DrSeatVentilating(
    );
  HeatAdj_ECMD_EngineStatus = CanRx_0x2A7_ECMD_EngineStatus( );
  HeatAdj_HeatMsgLostFlag = Ecual_CanGetHeatMsgLostFlag( );
  HeatAdj_MemDiagDrHeatConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_DrVentAndHeatConfig);
  HeatAdj_MemDiagDrHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeatFlg);
  HeatAdj_MemDiagPaHeatConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_PaVentAndHeatConfig);
  HeatAdj_MemDiagPaHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaHeatFlg);
  HeatAdj_MemDiagThirdHeatConfig = Srvl_getSystemConfigPram(EN_SteerHeat_SysCfg);
  HeatAdj_MemIndexDrHeatConfig = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeatConfig);
  HeatAdj_MemIndexPaHeatConfig = Srvl_GetMemIndexDataU8(EN_MemIndex_PaHeatFlg);
  HeatAdj_MemIndexThirdHeatConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_ThirdHeatConfig);
  HeatAdj_P20_PHEV_EngineCfg = Srvl_GetMemIndexDataU8
    (EN_MemIndex_Heat_P20_PHEV_EngineCfg);
  HeatAdj_PaHeatNtcAdc = Ecual_AdcGetPaNTCTempValue( );
  HeatAdj_PaHeatStopReason = Rte_GetVfb_PaHeatStopReason( );
  HeatAdj_PaVentFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentFlg);
  HeatAdj_PassengerCmdFaultSts = Rte_GetVfb_PaHeatCmdFaultSts( );
  HeatAdj_PassengerCmdFaultSts4DTC = Rte_GetVfb_PaHeatCmdFaultSts4DTC( );
  HeatAdj_PassengerDiagCmd = Desc_DiagOutCtrlPram(EN_PAHEAT);
  HeatAdj_PassengerHMI_Message = CanRx_0x351_IVI_FRSeatHeatSet( );
  HeatAdj_PassengerNTCFaultSts = Rte_GetVfb_PaHeatNTCFaultSts( );
  HeatAdj_PassengerTbox_Message = CanRx_0x281_BDC_TBOX_Req_PaSeatHeating( );
  HeatAdj_PassengerVentEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_SecondVentConfig);
  HeatAdj_Passenger_HMI_VentilateMsg = CanRx_0x351_IVI_FRSeatVentnSet( );
  HeatAdj_Passenger_Tbox_VentilateMsg =
    CanRx_0x281_BDC_TBOX_Req_PaSeatVentilating( );
  HeatAdj_PlatformEngineEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_Heat_PlatformEngineEnableConfig);
  HeatAdj_PlatformVehicleEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_Heat_PlatFormVehicleEnableConfig);
  HeatAdj_PowerMode = Rte_GetVfb_PowerMode( );
  HeatAdj_RecoverDefaultFlag = GetRecoverDefaultFlag( );
  HeatAdj_RemoteEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_Heat_RemoteEnableConfig);
  HeatAdj_RemoteMsgLostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x283);
  HeatAdj_RunMaxTime = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_RunMaxTime);
  HeatAdj_TboxRemoteSts = CanRx_0x283_BDC_TboxRemoteControlSt( );
  HeatAdj_ThirdCmdFaultSts = Rte_GetVfb_ThirdHeatCmdFaultSts( );
  HeatAdj_ThirdCmdFaultSts4DTC = Rte_GetVfb_ThirdHeatCmdFaultSts4DTC( );
  HeatAdj_ThirdDiagCmd = Desc_DiagOutCtrlPram(EN_WHEEL);
  HeatAdj_ThirdDiagMaxTime = Rte_GetVfb_SwHeatMaxTime( );
  HeatAdj_ThirdHMI_Message = CanRx_0x351_IVI_SwsHeatSw( );
  HeatAdj_ThirdHeatNtcAdc = Ecual_AdcGetCenterNTCTempValue( );
  HeatAdj_ThirdHeatStopReason = Rte_GetVfb_ThirdHeatStopReason( );
  HeatAdj_ThirdNTCFaultSts = Rte_GetVfb_ThirdHeatNTCFaultSts( );
  HeatAdj_ThirdTbox_Message = CanRx_0x281_BDC_TBOX_Req_Steeringwheel_heating( );
  HeatAdj_ThirdVentEnableConfig = Srvl_GetMemIndexDataU8
    (EN_MemIndex_ThirdVentConfig);
  HeatAdj_Third_HMI_VentilateMsg = Vfb_Reserved_0( );
  HeatAdj_Third_Tbox_VentilateMsg = Vfb_Reserved_0( );
  HeatAdj_TimeOutPrm = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_TimeOutPrm);
  HeatAdj_VCU_VehRunSta = CanRx_0x2AE_VCU_VehRunSta( );
  HeatAdj_VoltMode = Rte_GetVfb_VoltMode( );
}

/* System initialize for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_HeatAdj_CtrlModel_UpDataInputInfo_Init(void)
{
  INT8U HeatErr_b;
  Appl_HeatAdj_CtrlModel_DW.is_active_c7_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c7_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_db;
  Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_active_c44_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c44_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_db;
  Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_active_c39_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c39_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_db;
  Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_active_c10_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_B.DriverHeatError = 0U;
  Appl_HeatAdj_CtrlModel_B.PassengerHeatError = 0U;
  Appl_HeatAdj_CtrlModel_B.ThirdHeatError = 0U;
  Appl_HeatAdj_CtrlModel_B.DriverHeatErrorDtc = 0U;
  Appl_HeatAdj_CtrlModel_B.PassengerHeatErrorDtc = 0U;
  Appl_HeatAdj_CtrlModel_B.ThirdHeatErrorDtc = 0U;
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction2);
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction3);
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction1);
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction4);
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction);
  Appl_HeatAdj_CtrlModel_ErrorFunction2_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.ErrorFunction5);
  Appl_HeatAdj_CtrlModel_DW.is_active_c8_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_B.DriverVentilateValid = 0U;
  Appl_HeatAdj_CtrlModel_B.PassengerVentilateValid = 0U;
  Appl_HeatAdj_CtrlModel_B.ThirdVentilateValid = 0U;
  Appl_HeatAdj_CtrlModel_OppositeMessageDeal_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal);
  Appl_HeatAdj_CtrlModel_OppositeMessageDeal_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal1);
  Appl_HeatAdj_CtrlModel_OppositeMessageDeal_Init(&HeatErr_b,
    &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal2);
  Appl_HeatAdj_CtrlModel_DW.is_active_c37_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_B.DriverHMI_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.DriverTbox_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.PassengerHMI_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.PassengerTbox_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message = 0U;
  Appl_HeatAdj_CtrlModel_B.Driver_MixConflicFlg = 0U;
  Appl_HeatAdj_CtrlModel_B.Passenger_MixConflicFlg = 0U;
  Appl_HeatAdj_CtrlModel_B.Third_MixConflicFlg = 0U;
  Appl_HeatAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_HeatAdj_CtrlModel_B.OutMsgHMI_g,
     &Appl_HeatAdj_CtrlModel_B.OutMsgTbox_bz,
     &Appl_HeatAdj_CtrlModel_B.MixConflictFlg_a,
     &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction2);
  Appl_HeatAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_HeatAdj_CtrlModel_B.OutMsgHMI_n,
     &Appl_HeatAdj_CtrlModel_B.OutMsgTbox_b,
     &Appl_HeatAdj_CtrlModel_B.MixConflictFlg_p,
     &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction1);
  Appl_HeatAdj_CtrlModel_MsgConflictFunction2_Init
    (&Appl_HeatAdj_CtrlModel_B.OutMsgHMI, &Appl_HeatAdj_CtrlModel_B.OutMsgTbox,
     &Appl_HeatAdj_CtrlModel_B.MixConflictFlg,
     &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction);
  Appl_HeatAdj_CtrlModel_DW.is_active_c6_Appl_HeatAdj_CtrlModel = 0U;
  Appl_HeatAdj_CtrlModel_DW.is_c6_Appl_HeatAdj_CtrlModel =
    Appl_HeatAdj_CtrlModel_IN_NO_ACTIVE_CHILD_db;
  Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = 0U;
}

/* Output and update for atomic system: '<Root>/UpDataInputInfo' */
static void Appl_HeatAdj_CtrlModel_UpDataInputInfo(void)
{
  INT8U rtb_Switch;
  Appl_HeatAdj_CtrlModel_RTE();
  Appl_HeatAdj_CtrlModel_B.Product = 60U *
    Appl_HeatAdj_CtrlModel_ConstP.Constant5_Value[HeatAdj_CarType] * 1000U;
  if ((INT8U)HeatAdj_CarType != 0)
  {
    rtb_Switch = HeatAdj_DCDCSwitchSts;
  }
  else
  {
    rtb_Switch = ((BOOL)TRUE);
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c7_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c7_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c7_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_f;
    Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = ((BOOL)FALSE);
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c7_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_f)
  {
    Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = ((BOOL)FALSE);

    /* （平台发动机配置字使能
       && P20车型配置字禁能
       && 发动机状态为运行）
       || 平台发动机配置字禁能
       || 非P20车型 */
    if (((((BOOL)TRUE) == HeatAdj_PlatformEngineEnableConfig) && (((BOOL)FALSE) ==
          HeatAdj_P20_PHEV_EngineCfg) && (enEngineType_EN_ENGINE_RUNNING ==
          HeatAdj_ECMD_EngineStatus)) || (((BOOL)FALSE) ==
         HeatAdj_PlatformEngineEnableConfig) || (enProjectType_EN_PROJECT_P20 !=
         HeatAdj_CarType))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c7_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_ValidSts_p;
      Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = ((BOOL)TRUE);

    /* 平台发动机配置字使能
       && (P20车型配置字使能
       || 发动机状态非运行) */
    if ((((BOOL)TRUE) == HeatAdj_PlatformEngineEnableConfig) && ((((BOOL)TRUE) ==
          HeatAdj_P20_PHEV_EngineCfg) || ((enEngineType_EN_ENGINE_RUNNING !=
           HeatAdj_ECMD_EngineStatus) && (enEngineType_EN_ENGINE_RESERVED !=
           HeatAdj_ECMD_EngineStatus))))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c7_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_f;
      Appl_HeatAdj_CtrlModel_B.EngineRunningFlag = ((BOOL)FALSE);
    }
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c44_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c44_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c44_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_f;
    Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = ((BOOL)FALSE);
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c44_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_f)
  {
    Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = ((BOOL)FALSE);

    /* （平台发动机配置字使能
       && P20车型配置字使能
       && VCU_VehRunSta= 0x1:HV ON /0x2:Ready）
       || 平台发动机配置字禁能
       || 非P20车型 */
    if (((((BOOL)TRUE) == HeatAdj_PlatformVehicleEnableConfig) && (((BOOL)TRUE) ==
          HeatAdj_P20_PHEV_EngineCfg) && ((enVehicleRunType_EN_HV_ON ==
           HeatAdj_VCU_VehRunSta) || (enVehicleRunType_EN_HV_READY ==
           HeatAdj_VCU_VehRunSta))) || (((BOOL)FALSE) ==
         HeatAdj_PlatformVehicleEnableConfig) || (enProjectType_EN_PROJECT_P20
         != HeatAdj_CarType))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c44_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_ValidSts_p;
      Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = ((BOOL)TRUE);

    /* 平台整车配置字使能
       && P20车型配置字使能
       && V整车运行状态非0x1:HV ON /0x2:Ready(0x3:Invalid保持上一状态) */
    if ((((BOOL)TRUE) == HeatAdj_PlatformVehicleEnableConfig) && ((((BOOL)TRUE)
          != HeatAdj_P20_PHEV_EngineCfg) || (enVehicleRunType_EN_HV_OFF ==
          HeatAdj_VCU_VehRunSta)))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c44_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_f;
      Appl_HeatAdj_CtrlModel_B.VehicleRunFlag = ((BOOL)FALSE);
    }
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c39_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c39_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c39_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_f;
    Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c39_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_f)
  {
    Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);

    /* 非OFF电 && DCDC开关状态为使能
       && 正常电压模式下
       && (发动机运行中 || 整车运行状态满足) */
    if ((enPowerModeSts_EN_OFF != HeatAdj_PowerMode) && (((BOOL)TRUE) ==
         rtb_Switch) && (enFinalPowerMode_EN_NORMAL_VOLT == HeatAdj_VoltMode) &&
        ((((BOOL)TRUE) == Appl_HeatAdj_CtrlModel_B.EngineRunningFlag) || (((BOOL)
           TRUE) == Appl_HeatAdj_CtrlModel_B.VehicleRunFlag)))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c39_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_ValidSts_p;
      Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)TRUE);

    /* OFF电 || DCDC开关状态为非使能 || 非正常电压
       || (发动机不在运行中 && 整车运行状态不满足) */
    if ((enPowerModeSts_EN_OFF == HeatAdj_PowerMode) || (((BOOL)TRUE) !=
         rtb_Switch) || (enFinalPowerMode_EN_NORMAL_VOLT != HeatAdj_VoltMode) ||
        ((((BOOL)TRUE) != Appl_HeatAdj_CtrlModel_B.EngineRunningFlag) && (((BOOL)
           TRUE) != Appl_HeatAdj_CtrlModel_B.VehicleRunFlag)))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c39_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_f;
      Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag = ((BOOL)FALSE);
    }
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c10_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c10_Appl_HeatAdj_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)HeatAdj_DriverCmdFaultSts,
      (INT8U)HeatAdj_DriverNTCFaultSts,
      &Appl_HeatAdj_CtrlModel_B.DriverHeatError,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction);
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)HeatAdj_PassengerCmdFaultSts,
      (INT8U)HeatAdj_PassengerNTCFaultSts,
      &Appl_HeatAdj_CtrlModel_B.PassengerHeatError,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction1);
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)HeatAdj_ThirdCmdFaultSts,
      (INT8U)HeatAdj_ThirdNTCFaultSts, &Appl_HeatAdj_CtrlModel_B.ThirdHeatError,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction2);
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)HeatAdj_DriverCmdFaultSts4DTC,
      (INT8U)HeatAdj_DriverNTCFaultSts,
      &Appl_HeatAdj_CtrlModel_B.DriverHeatErrorDtc,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction3);
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)
      HeatAdj_PassengerCmdFaultSts4DTC, (INT8U)HeatAdj_PassengerNTCFaultSts,
      &Appl_HeatAdj_CtrlModel_B.PassengerHeatErrorDtc,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction4);
    Appl_HeatAdj_CtrlModel_ErrorFunction2((INT8U)HeatAdj_ThirdCmdFaultSts4DTC,
      (INT8U)HeatAdj_ThirdNTCFaultSts,
      &Appl_HeatAdj_CtrlModel_B.ThirdHeatErrorDtc,
      &Appl_HeatAdj_CtrlModel_DW.ErrorFunction5);
  }

  rtb_Switch = (INT8U)HeatAdj_CarType;
  if (rtb_Switch == 0)
  {
    Appl_HeatAdj_CtrlModel_B.DrVentConfig = (INT8U)((HeatAdj_DrVentFlg != 0) &&
      (HeatAdj_MemDiagDrHeatConfig != 0));
    Appl_HeatAdj_CtrlModel_B.PaVentConfig = (INT8U)((HeatAdj_PaVentFlg != 0) &&
      (HeatAdj_MemDiagPaHeatConfig != 0));
    Appl_HeatAdj_CtrlModel_B.ThirdVentConfig = HeatAdj_MemDiagThirdHeatConfig;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.DrVentConfig = HeatAdj_DriverVentEnableConfig;
    Appl_HeatAdj_CtrlModel_B.PaVentConfig = HeatAdj_PassengerVentEnableConfig;
    Appl_HeatAdj_CtrlModel_B.ThirdVentConfig = HeatAdj_ThirdVentEnableConfig;
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c8_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c8_Appl_HeatAdj_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_OppositeMessageDeal(HeatAdj_CarType,
      Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot,
      HeatAdj_Driver_HMI_VentilateMsg, HeatAdj_Driver_Tbox_VentilateMsg,
      Appl_HeatAdj_CtrlModel_B.DrVentConfig,
      &Appl_HeatAdj_CtrlModel_B.DriverVentilateValid,
      &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal);
    Appl_HeatAdj_CtrlModel_OppositeMessageDeal(HeatAdj_CarType,
      Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot,
      HeatAdj_Passenger_HMI_VentilateMsg, HeatAdj_Passenger_Tbox_VentilateMsg,
      Appl_HeatAdj_CtrlModel_B.PaVentConfig,
      &Appl_HeatAdj_CtrlModel_B.PassengerVentilateValid,
      &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal1);
    Appl_HeatAdj_CtrlModel_OppositeMessageDeal(HeatAdj_CarType,
      Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot,
      HeatAdj_Third_Tbox_VentilateMsg, HeatAdj_Third_HMI_VentilateMsg,
      Appl_HeatAdj_CtrlModel_B.ThirdVentConfig,
      &Appl_HeatAdj_CtrlModel_B.ThirdVentilateValid,
      &Appl_HeatAdj_CtrlModel_DW.OppositeMessageDeal2);
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c37_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c37_Appl_HeatAdj_CtrlModel = 1U;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_MsgConflictFunction2((INT8U)HeatAdj_CarType,
      HeatAdj_DriverHMI_Message, HeatAdj_DriverTbox_Message,
      Appl_HeatAdj_CtrlModel_B.DriverVentilateValid,
      &Appl_HeatAdj_CtrlModel_B.OutMsgHMI, &Appl_HeatAdj_CtrlModel_B.OutMsgTbox,
      &Appl_HeatAdj_CtrlModel_B.MixConflictFlg,
      &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction);
    Appl_HeatAdj_CtrlModel_B.DriverHMI_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgHMI;
    Appl_HeatAdj_CtrlModel_B.DriverTbox_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgTbox;
    Appl_HeatAdj_CtrlModel_B.Driver_MixConflicFlg =
      Appl_HeatAdj_CtrlModel_B.MixConflictFlg;
    Appl_HeatAdj_CtrlModel_MsgConflictFunction2((INT8U)HeatAdj_CarType,
      HeatAdj_PassengerHMI_Message, HeatAdj_PassengerTbox_Message,
      Appl_HeatAdj_CtrlModel_B.PassengerVentilateValid,
      &Appl_HeatAdj_CtrlModel_B.OutMsgHMI_n,
      &Appl_HeatAdj_CtrlModel_B.OutMsgTbox_b,
      &Appl_HeatAdj_CtrlModel_B.MixConflictFlg_p,
      &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction1);
    Appl_HeatAdj_CtrlModel_B.PassengerHMI_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgHMI_n;
    Appl_HeatAdj_CtrlModel_B.PassengerTbox_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgTbox_b;
    Appl_HeatAdj_CtrlModel_B.Passenger_MixConflicFlg =
      Appl_HeatAdj_CtrlModel_B.MixConflictFlg_p;
    Appl_HeatAdj_CtrlModel_MsgConflictFunction2((INT8U)HeatAdj_CarType,
      HeatAdj_ThirdHMI_Message, HeatAdj_ThirdTbox_Message,
      Appl_HeatAdj_CtrlModel_B.ThirdVentilateValid,
      &Appl_HeatAdj_CtrlModel_B.OutMsgHMI_g,
      &Appl_HeatAdj_CtrlModel_B.OutMsgTbox_bz,
      &Appl_HeatAdj_CtrlModel_B.MixConflictFlg_a,
      &Appl_HeatAdj_CtrlModel_DW.MsgConflictFunction2);
    Appl_HeatAdj_CtrlModel_B.ThirdHMI_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgHMI_g;
    Appl_HeatAdj_CtrlModel_B.ThirdTbox_Message =
      Appl_HeatAdj_CtrlModel_B.OutMsgTbox_bz;
    Appl_HeatAdj_CtrlModel_B.Third_MixConflicFlg =
      Appl_HeatAdj_CtrlModel_B.MixConflictFlg_a;
  }

  if (Appl_HeatAdj_CtrlModel_DW.is_active_c6_Appl_HeatAdj_CtrlModel == 0U)
  {
    Appl_HeatAdj_CtrlModel_DW.is_active_c6_Appl_HeatAdj_CtrlModel = 1U;
    Appl_HeatAdj_CtrlModel_DW.is_c6_Appl_HeatAdj_CtrlModel =
      Appl_HeatAdj_CtrlModel_IN_Default_f;
    Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = ((BOOL)FALSE);
  }
  else if (Appl_HeatAdj_CtrlModel_DW.is_c6_Appl_HeatAdj_CtrlModel ==
           Appl_HeatAdj_CtrlModel_IN_Default_f)
  {
    Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = ((BOOL)FALSE);

    /* 平台远程配置字使能
       && 远程报文在线
       && 车辆变为远程模式 */
    if ((((BOOL)TRUE) == HeatAdj_RemoteEnableConfig) && (((BOOL)FALSE) ==
         HeatAdj_RemoteMsgLostFlag) && (HeatAdj_TboxRemoteSts == ((BOOL)TRUE)))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c6_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_ValidSts_p;
      Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = ((BOOL)TRUE);
    }
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = ((BOOL)TRUE);

    /* 平台远程配置字禁能
       || 远程报文掉线
       || （车辆变为非远程模式&&远程报文在线） */
    if ((((BOOL)FALSE) == HeatAdj_RemoteEnableConfig) || (((BOOL)TRUE) ==
         HeatAdj_RemoteMsgLostFlag) || ((HeatAdj_TboxRemoteSts == ((BOOL)FALSE))
         && (((BOOL)FALSE) == HeatAdj_RemoteMsgLostFlag)))
    {
      Appl_HeatAdj_CtrlModel_DW.is_c6_Appl_HeatAdj_CtrlModel =
        Appl_HeatAdj_CtrlModel_IN_Default_f;
      Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_ot = ((BOOL)FALSE);
    }
  }

  if (rtb_Switch > 0)
  {
    Appl_HeatAdj_CtrlModel_B.DrHeatConfig = HeatAdj_MemIndexDrHeatConfig;
    Appl_HeatAdj_CtrlModel_B.PaHeatConfig = HeatAdj_MemIndexPaHeatConfig;
    Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig = HeatAdj_MemIndexThirdHeatConfig;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.DrHeatConfig = (INT8U)((HeatAdj_MemDiagDrHeatConfig
      != 0) && (HeatAdj_MemDiagDrHeatFlg != 0));
    Appl_HeatAdj_CtrlModel_B.PaHeatConfig = (INT8U)((HeatAdj_MemDiagPaHeatConfig
      != 0) && (HeatAdj_MemDiagPaHeatFlg != 0));
    Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig = HeatAdj_MemDiagThirdHeatConfig;
  }

  if (HeatAdj_ThirdDiagMaxTime != 0)
  {
    Appl_HeatAdj_CtrlModel_B.Switch = 1000U * HeatAdj_ThirdDiagMaxTime;
  }
  else
  {
    Appl_HeatAdj_CtrlModel_B.Switch = CAL_SW_20min_TIMEOUT;
  }
}

/* Output and update for atomic system: '<Root>/UpDataOutputInfo' */
static void Appl_HeatAdj_CtrlModel_UpDataOutputInfo(void)
{
  Rte_SetVfb_SecondHeatEnable(Appl_HeatAdj_CtrlModel_B.PaHeatConfig_k);
  Rte_SetVfb_SecondVentEnable(Appl_HeatAdj_CtrlModel_B.PaVentConfig_d);
  Rte_SetVfb_ThirdHeatEnable(Appl_HeatAdj_CtrlModel_B.ThirdHeatConfig_l);
  Rte_SetVfb_ThirdHeatRunState(Appl_HeatAdj_CtrlModel_B.Out3rdRunState);
  Rte_SetVfb_ThirdVentEnable(Appl_HeatAdj_CtrlModel_B.ThirdVentConfig_c);
  Rte_SetVfb_CANDrHeatStopReason(Appl_HeatAdj_CtrlModel_B.DrCANHeatStopReason);
  Rte_SetVfb_CANPaHeatStopReason(Appl_HeatAdj_CtrlModel_B.ThirdCANHeatStopReason);
  Rte_SetVfb_CANThirdHeatStopReason(Appl_HeatAdj_CtrlModel_B.PaCANHeatStopReason);
  Ecual_CanSetThirdHeatSts(Appl_HeatAdj_CtrlModel_B.Out3rdRunState);
  Ecual_CanSetDrvHeatSts(Appl_HeatAdj_CtrlModel_B.OutDrRunState);
  Ecual_CanSetPasHeatSts(Appl_HeatAdj_CtrlModel_B.OutPaRunState);
  Rte_SetVfb_HVCommPC(Appl_HeatAdj_CtrlModel_B.ComPCSatisfiedFlag_n);
  Rte_SetVfb_DrHeat(Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel);
  Rte_SetVfb_DrHeatIo(Appl_HeatAdj_CtrlModel_B.HeatAdj_DRHeatIo);
  Rte_SetVfb_DrHeatEnable(Appl_HeatAdj_CtrlModel_B.DrHeatConfig_d);
  Rte_SetVfb_DrHeatRunState(Appl_HeatAdj_CtrlModel_B.OutDrRunState);
  Rte_SetVfb_DrHeatStopReason(Appl_HeatAdj_CtrlModel_B.DrHeatStopReason);
  Rte_SetVfb_DrHeatType(Appl_HeatAdj_CtrlModel_B.HeatDriverRunType);
  Rte_SetVfb_DrVentEnable(Appl_HeatAdj_CtrlModel_B.DrVentConfig_l);
  CanTx_0x3B2_DSM_St_DriSeatHeatGear(Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel);
  Rte_SetVfb_EngineRunFlag(Appl_HeatAdj_CtrlModel_B.EngineRunningFlag_n);
  Rte_SetVfb_PaHeat(Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel);
  Rte_SetVfb_PaHeatIo(Appl_HeatAdj_CtrlModel_B.HeatAdj_PAHeatIo);
  Rte_SetVfb_PaHeatRunState(Appl_HeatAdj_CtrlModel_B.OutPaRunState);
  Rte_SetVfb_PaHeatStopReason(Appl_HeatAdj_CtrlModel_B.PaHeatStopReason);
  Rte_SetVfb_PaHeatType(Appl_HeatAdj_CtrlModel_B.HeatPassengerRunType);
  CanTx_0x3B2_DSM_St_PasSeatHeatGear(Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel);
  Rte_SetVfb_RemoteModeFlag(Appl_HeatAdj_CtrlModel_B.RemoteModeFlag_c);
  DiagSetSwHeatTimer(Appl_HeatAdj_CtrlModel_B.Sw20minTimerOut);
  Rte_SetVfb_ThirdHeat(Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel);
  Rte_SetVfb_ThirdHeatIo(Appl_HeatAdj_CtrlModel_B.HeatAdj_ThirdHeatIo);
  Ecual_CanSetThirdHeatLvl(Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel);
  Rte_SetVfb_ThirdHeatStopReason(Appl_HeatAdj_CtrlModel_B.ThirdHeatStopReason);
  Rte_SetVfb_ThirdHeatType(Appl_HeatAdj_CtrlModel_B.HeatThirdRunType);
  Rte_SetVfb_VehicleRunFlag(Appl_HeatAdj_CtrlModel_B.VehicleRunFlag_m);
}

/* Model step function */
void Appl_HeatAdj_CtrlModel_step(void)
{
  Appl_HeatAdj_CtrlModel_UpDataInputInfo();
  Appl_HeatAdj_CtrlModel_LogicCtrl();
  Appl_HeatAdj_CtrlModel_UpDataOutputInfo();
}

/* Model initialize function */
void Appl_HeatAdj_CtrlModel_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Appl_HeatAdj_CtrlModel_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Appl_HeatAdj_CtrlModel_B), 0,
                sizeof(B_Appl_HeatAdj_CtrlModel_T));

  {
    Appl_HeatAdj_CtrlModel_B.CarTypeCfg_e = enProjectType_EN_PROJECT_P20;
    Appl_HeatAdj_CtrlModel_B.HeatDriverRunType = enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.HeatPassengerRunType = enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.HeatThirdRunType = enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.OrgHeatDriverRunType = enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.OrgHeatPassengerRunType =
      enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.OrgHeatThirdRunType = enHeatType_EN_HEAT_TYPE_NONE;
    Appl_HeatAdj_CtrlModel_B.DrHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.ThirdHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.PaHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.DrCANHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.PaCANHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.ThirdCANHeatStopReason =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.StopReason_d = enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.StopReason_ew =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.CANStopReason_ky =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.StopReason_c = enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.CANStopReason_j =
      enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.DisableSts_b = enHeatStopReason_EN_HEAT_STOP_R_NONE;
    Appl_HeatAdj_CtrlModel_B.OutDrCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.OutPaCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Out3rdCANHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.AimLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.AimLevel_c = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.AimLevel_d = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.HeatLvl_i = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.DiagDrHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.DiagPaHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Diag3rdHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.InLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.InLevel_p = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Level_i = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Level_b = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Level_p = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Level_g = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Level_be = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.OriginalDrHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.OriginalPaHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.Original3rdHeatLevel = enHeatLvlSts_EN_HEAT_LVL_OFF;
    Appl_HeatAdj_CtrlModel_B.HeatAdj_DRHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
    Appl_HeatAdj_CtrlModel_B.HeatAdj_PAHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
    Appl_HeatAdj_CtrlModel_B.HeatAdj_ThirdHeatIo = enHeatIoSts_EN_HEAT_IO_LOW;
  }

  /* exported global signals */
  HeatAdj_VCU_VehRunSta = enVehicleRunType_EN_HV_OFF;
  HeatAdj_CarType = enProjectType_EN_PROJECT_P20;
  HeatAdj_PowerMode = enPowerModeSts_EN_OFF;
  HeatAdj_DrHeatStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
  HeatAdj_PaHeatStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
  HeatAdj_ThirdHeatStopReason = enHeatStopReason_EN_HEAT_STOP_R_NONE;
  HeatAdj_DriverNTCFaultSts = enHeatNtcFault_EN_NTC_FAULT_NONE;
  HeatAdj_PassengerNTCFaultSts = enHeatNtcFault_EN_NTC_FAULT_NONE;
  HeatAdj_ThirdNTCFaultSts = enHeatNtcFault_EN_NTC_FAULT_NONE;
  HeatAdj_D_SimuIndex_DRHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatAdj_D_SimuIndex_PAHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatAdj_D_SimuIndex_ThirdHeat = enHeatLvlSts_EN_HEAT_LVL_OFF;
  HeatAdj_DriverDiagCmd = enHeatIoCmdLvl_EN_HEAT_IO_LVL_NONE;
  HeatAdj_PassengerDiagCmd = enHeatIoCmdLvl_EN_HEAT_IO_LVL_NONE;
  HeatAdj_ThirdDiagCmd = enHeatIoCmdLvl_EN_HEAT_IO_LVL_NONE;
  HeatAdj_DriverCmdFaultSts = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_DriverCmdFaultSts4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_PassengerCmdFaultSts = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_PassengerCmdFaultSts4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_ThirdCmdFaultSts = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_ThirdCmdFaultSts4DTC = enHeatCmdFault_EN_HEAT_FAULT_NONE;
  HeatAdj_VoltMode = enFinalPowerMode_EN_NORMAL_VOLT;
  HeatAdj_ECMD_EngineStatus = enEngineType_EN_ENGINE_STOP;
  HeatAdj_DrHeatNtcAdc = ((INT16U)0U);
  HeatAdj_PaHeatNtcAdc = ((INT16U)0U);
  HeatAdj_ThirdHeatNtcAdc = ((INT16U)0U);
  HeatAdj_CanDrvHeatLvl = ((INT8U)0U);
  HeatAdj_CanPasHeatLvl = ((INT8U)0U);
  HeatAdj_CanThirdHeatLvl = ((INT8U)0U);
  HeatAdj_DCDCSwitchSts = ((INT8U)0U);
  HeatAdj_DrVentFlg = ((INT8U)0U);
  HeatAdj_DriverHMI_Message = ((INT8U)0U);
  HeatAdj_DriverTbox_Message = ((INT8U)0U);
  HeatAdj_DriverVentEnableConfig = ((INT8U)0U);
  HeatAdj_Driver_HMI_VentilateMsg = ((INT8U)0U);
  HeatAdj_Driver_Tbox_VentilateMsg = ((INT8U)0U);
  HeatAdj_HeatMsgLostFlag = ((INT8U)0U);
  HeatAdj_MemDiagDrHeatConfig = ((INT8U)0U);
  HeatAdj_MemDiagDrHeatFlg = ((INT8U)0U);
  HeatAdj_MemDiagPaHeatConfig = ((INT8U)0U);
  HeatAdj_MemDiagPaHeatFlg = ((INT8U)0U);
  HeatAdj_MemDiagThirdHeatConfig = ((INT8U)0U);
  HeatAdj_MemIndexDrHeatConfig = ((INT8U)0U);
  HeatAdj_MemIndexPaHeatConfig = ((INT8U)0U);
  HeatAdj_MemIndexThirdHeatConfig = ((INT8U)0U);
  HeatAdj_P20_PHEV_EngineCfg = ((INT8U)0U);
  HeatAdj_PaVentFlg = ((INT8U)0U);
  HeatAdj_PassengerHMI_Message = ((INT8U)0U);
  HeatAdj_PassengerTbox_Message = ((INT8U)0U);
  HeatAdj_PassengerVentEnableConfig = ((INT8U)0U);
  HeatAdj_Passenger_HMI_VentilateMsg = ((INT8U)0U);
  HeatAdj_Passenger_Tbox_VentilateMsg = ((INT8U)0U);
  HeatAdj_PlatformEngineEnableConfig = ((INT8U)0U);
  HeatAdj_PlatformVehicleEnableConfig = ((INT8U)0U);
  HeatAdj_RecoverDefaultFlag = ((INT8U)0U);
  HeatAdj_RemoteEnableConfig = ((INT8U)0U);
  HeatAdj_RemoteMsgLostFlag = ((INT8U)0U);
  HeatAdj_RunMaxTime = ((INT8U)0U);
  HeatAdj_TboxRemoteSts = ((INT8U)0U);
  HeatAdj_ThirdDiagMaxTime = ((INT8U)0U);
  HeatAdj_ThirdHMI_Message = ((INT8U)0U);
  HeatAdj_ThirdTbox_Message = ((INT8U)0U);
  HeatAdj_ThirdVentEnableConfig = ((INT8U)0U);
  HeatAdj_Third_HMI_VentilateMsg = ((INT8U)0U);
  HeatAdj_Third_Tbox_VentilateMsg = ((INT8U)0U);
  HeatAdj_TimeOutPrm = ((INT8U)0U);

  /* states (dwork) */
  (void) memset((void *)&Appl_HeatAdj_CtrlModel_DW, 0,
                sizeof(DW_Appl_HeatAdj_CtrlModel_T));
  Appl_HeatAdj_CtrlModel_UpDataInputInfo_Init();
  Appl_HeatAdj_CtrlModel_LogicCtrl_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
