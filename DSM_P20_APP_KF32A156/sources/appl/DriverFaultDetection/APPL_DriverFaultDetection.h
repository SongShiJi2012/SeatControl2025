/*
 * File: APPL_DriverFaultDetection.h
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

#ifndef RTW_HEADER_APPL_DriverFaultDetection_h_
#define RTW_HEADER_APPL_DriverFaultDetection_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef APPL_DriverFaultDetection_COMMON_INCLUDES_
# define APPL_DriverFaultDetection_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Ecual_Adc.h"
#include "Rte_VfbInterface.h"
#include "Cdd_Hall.h"
#include "Srvl_E2cfg.h"
#include "Srvl_E2memory.h"
#include "Ecual_AdcMotor.h"
#include "CpuPeripheralInit.h"
#include "Srvl_PowerMode.h"
#include "Desc.h"
#include "Test.h"
#include "Rte_CanInterface.h"
#include "Srvl_CanSignals.h"
#include "Debug_VfbInterface.h"
#include "LdfFile_DSM_TwoInOne_V10.h"
#include "Ecual_lin.h"
#include "Appl_DtcSetConditionCheck.h"
#include "ecual_pins.h"
#include "Srvl_NM.h"
#include "Srvl_Tle9210x.h"
#endif                                 /* APPL_DriverFaultDetection_COMMON_INCLUDES_ */

#include "APPL_DriverFaultDetection_types.h"

/* Includes for objects with custom storage classes. */
#include "Common.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S21>/CheckMidRelayFault' */
typedef struct
{
  INT8U is_active_c4_APPL_DriverFaultDetection;/* '<S22>/RelayFault' */
  INT8U is_c4_APPL_DriverFaultDetection;/* '<S22>/RelayFault' */
}
DW_CheckMidRelayFault_APPL_DriverFaultDetection_T;

/* Block signals (default storage) */
typedef struct
{
  INT32U DrAdj_CurMsTs;                /* '<S13>/DrAdj_LenAdjSize' */
  enSeatMoveCmd CurrentHeightSwCmd;    /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentLengthSwCmd;    /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentBackSwCmd;      /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentFrontSwCmd;     /* '<S11>/ SWProcess ' */
  enSeatMoveCmd HeightSwCmd;           /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd LengthSwCmd;           /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd BackSwCmd;             /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd FrontSwCmd;            /* '<S5>/SwitchErrorDetection' */
  INT8U DataTypeConversion1;           /* '<S4>/Data Type Conversion1' */
  INT8U DataTypeConversion2;           /* '<S4>/Data Type Conversion2' */
  INT8U DataTypeConversion3;           /* '<S4>/Data Type Conversion3' */
  INT8U DataTypeConversion4;           /* '<S4>/Data Type Conversion4' */
  INT8U DataTypeConversion5;           /* '<S4>/Data Type Conversion5' */
  INT8U DataTypeConversion6;           /* '<S4>/Data Type Conversion6' */
  INT8U HeightStallFault;              /* '<S10>/StallErrorDetection' */
  INT8U LengthStallFault;              /* '<S10>/StallErrorDetection' */
  INT8U BackStallFault;                /* '<S10>/StallErrorDetection' */
  INT8U FrontStallFault;               /* '<S10>/StallErrorDetection' */
  INT8U HeightSoftStopFault;           /* '<S9>/SoftStopPointDetection' */
  INT8U LengthSoftStopFault;           /* '<S9>/SoftStopPointDetection' */
  INT8U BackSoftStopFault;             /* '<S9>/SoftStopPointDetection' */
  INT8U FrontSoftStopFault;            /* '<S9>/SoftStopPointDetection' */
  INT8U Cnt;                           /* '<S9>/SoftStopPointDetection' */
  INT8U Cnt_h;                         /* '<S9>/SoftStopPointDetection' */
  INT8U Cnt_i;                         /* '<S9>/SoftStopPointDetection' */
  INT8U Cnt_f;                         /* '<S9>/SoftStopPointDetection' */
  INT8U HeightMidRelayFault;           /* '<S8>/MidRelayErrorDetection' */
  INT8U LengthMidRelayFault;           /* '<S8>/MidRelayErrorDetection' */
  INT8U BackMidRelayFault;             /* '<S8>/MidRelayErrorDetection' */
  INT8U FrontMidRelayFault;            /* '<S8>/MidRelayErrorDetection' */
  INT8U MidRelayFault;                 /* '<S25>/RelayFault' */
  INT8U MidRelayTimer;                 /* '<S25>/RelayFault' */
  INT8U MidRelayFault_p;               /* '<S24>/RelayFault' */
  INT8U MidRelayTimer_p;               /* '<S24>/RelayFault' */
  INT8U MidRelayFault_f;               /* '<S23>/RelayFault' */
  INT8U MidRelayTimer_pv;              /* '<S23>/RelayFault' */
  INT8U MidRelayFault_n;               /* '<S22>/RelayFault' */
  INT8U MidRelayTimer_e;               /* '<S22>/RelayFault' */
  INT8U HeightTimeOutFlag;             /* '<S7>/MotorTimeOutDetection' */
  INT8U LengthTimeOutFlag;             /* '<S7>/MotorTimeOutDetection' */
  INT8U BackTimeOutFlag;               /* '<S7>/MotorTimeOutDetection' */
  INT8U FrontTimeOutFlag;              /* '<S7>/MotorTimeOutDetection' */
  INT8U Desc_HeightHallDTC;            /* '<S6>/HallErrorDetection' */
  INT8U Desc_LengthHallDTC;            /* '<S6>/HallErrorDetection' */
  INT8U Desc_BackHallDTC;              /* '<S6>/HallErrorDetection' */
  INT8U Desc_FrontHallDTC;             /* '<S6>/HallErrorDetection' */
  INT8U HeightHallFault;               /* '<S6>/HallErrorDetection' */
  INT8U LengthHallFault;               /* '<S6>/HallErrorDetection' */
  INT8U BackHallFault;                 /* '<S6>/HallErrorDetection' */
  INT8U FrontHallFault;                /* '<S6>/HallErrorDetection' */
  INT8U HeightSwAdhesionFault;         /* '<S5>/SwitchErrorDetection' */
  INT8U LengthSwAdhesionFault;         /* '<S5>/SwitchErrorDetection' */
  INT8U BackSwAdhesionFault;           /* '<S5>/SwitchErrorDetection' */
  INT8U FrontSwAdhesionFault;          /* '<S5>/SwitchErrorDetection' */
  INT8U HeightSwUpAdhesionFault;       /* '<S5>/SwitchErrorDetection' */
  INT8U HeightSwDownAdhesionFault;     /* '<S5>/SwitchErrorDetection' */
  INT8U LengthSwUpAdhesionFault;       /* '<S5>/SwitchErrorDetection' */
  INT8U LengthSwDownAdhesionFault;     /* '<S5>/SwitchErrorDetection' */
  INT8U BackSwUpAdhesionFault;         /* '<S5>/SwitchErrorDetection' */
  INT8U BackSwDownAdhesionFault;       /* '<S5>/SwitchErrorDetection' */
  INT8U FrontSwUpAdhesionFault;        /* '<S5>/SwitchErrorDetection' */
  INT8U FrontSwDownAdhesionFault;      /* '<S5>/SwitchErrorDetection' */
}
B_APPL_DriverFaultDetection_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT32U HeightSwTimer;                /* '<S5>/SwitchErrorDetection' */
  INT32U LengthSwTimer;                /* '<S5>/SwitchErrorDetection' */
  INT32U BackSwTimer;                  /* '<S5>/SwitchErrorDetection' */
  INT32U FrontSwTimer;                 /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd HeightSwCmd_start;     /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd LengthSwCmd_start;     /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd BackSwCmd_start;       /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd FrontSwCmd_start;      /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd HeightSwCmd_start_i;   /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd LengthSwCmd_start_c;   /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd BackSwCmd_start_l;     /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd FrontSwCmd_prev_j;     /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd FrontSwCmd_start_k;    /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRHeightSwitch_start;/* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRLengthSwitch_start;/* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRBackSwitch_start;/* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRFrontSwitch_start;/* '<S5>/SwitchErrorDetection' */
  INT16U LocalLengthHallCnt;           /* '<S10>/StallErrorDetection' */
  INT16U LocalHeightHallCnt;           /* '<S10>/StallErrorDetection' */
  INT16U LocalBackHallCnt;             /* '<S10>/StallErrorDetection' */
  INT16U LocalFrontHallCnt;            /* '<S10>/StallErrorDetection' */
  INT16U BackTimer;                    /* '<S7>/MotorTimeOutDetection' */
  INT16U FrontTimer;                   /* '<S7>/MotorTimeOutDetection' */
  INT16U HeightTimer;                  /* '<S7>/MotorTimeOutDetection' */
  INT16U LengthTimer;                  /* '<S7>/MotorTimeOutDetection' */
  INT16U MtrCtrlFault_HeightHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT16U MtrCtrlFault_LengthHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT16U MtrCtrlFault_BackHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT16U MtrCtrlFault_FrontHallCnt_prev;/* '<S6>/HallErrorDetection' */
  INT16U MtrCtrlFault_FrontHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT8U is_active_c1_APPL_DriverFaultDetection;/* '<S11>/ SWProcess ' */
  INT8U is_c1_APPL_DriverFaultDetection;/* '<S11>/ SWProcess ' */
  INT8U is_HeightSWProcess;            /* '<S11>/ SWProcess ' */
  INT8U is_LengthSWProcess;            /* '<S11>/ SWProcess ' */
  INT8U is_BackSWProcess;              /* '<S11>/ SWProcess ' */
  INT8U is_FrontSWProcess;             /* '<S11>/ SWProcess ' */
  INT8U is_active_c10_APPL_DriverFaultDetection;/* '<S10>/StallErrorDetection' */
  INT8U is_HeightStallError;           /* '<S10>/StallErrorDetection' */
  INT8U is_LengthStallError;           /* '<S10>/StallErrorDetection' */
  INT8U is_BackStallError;             /* '<S10>/StallErrorDetection' */
  INT8U is_FrontStallError;            /* '<S10>/StallErrorDetection' */
  INT8U HeightStallTimer;              /* '<S10>/StallErrorDetection' */
  INT8U LengthStallTimer;              /* '<S10>/StallErrorDetection' */
  INT8U BackStallTimer;                /* '<S10>/StallErrorDetection' */
  INT8U FrontStallTimer;               /* '<S10>/StallErrorDetection' */
  INT8U HeightStallNoTimer;            /* '<S10>/StallErrorDetection' */
  INT8U LengthStallNoTimer;            /* '<S10>/StallErrorDetection' */
  INT8U BackStallNoTimer;              /* '<S10>/StallErrorDetection' */
  INT8U FrontStallNoTimer;             /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer1;             /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer2;             /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer3;             /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer4;             /* '<S10>/StallErrorDetection' */
  INT8U is_active_c33_APPL_DriverFaultDetection;/* '<S9>/SoftStopPointDetection' */
  INT8U is_HeightSoft;                 /* '<S9>/SoftStopPointDetection' */
  INT8U is_LengthSoft;                 /* '<S9>/SoftStopPointDetection' */
  INT8U is_BackSoft;                   /* '<S9>/SoftStopPointDetection' */
  INT8U is_FrontSoft;                  /* '<S9>/SoftStopPointDetection' */
  INT8U HeightSoftStopBufCnt;          /* '<S9>/SoftStopPointDetection' */
  INT8U LengthSoftStopBufCnt;          /* '<S9>/SoftStopPointDetection' */
  INT8U BackSoftStopBufCnt;            /* '<S9>/SoftStopPointDetection' */
  INT8U FrontSoftStopBufCnt;           /* '<S9>/SoftStopPointDetection' */
  INT8U is_active_c3_APPL_DriverFaultDetection;/* '<S8>/MidRelayErrorDetection' */
  INT8U is_active_c16_APPL_DriverFaultDetection;/* '<S7>/MotorTimeOutDetection' */
  INT8U is_HeightAdjust;               /* '<S7>/MotorTimeOutDetection' */
  INT8U is_VerticalAdjust;             /* '<S7>/MotorTimeOutDetection' */
  INT8U is_BackAdjust;                 /* '<S7>/MotorTimeOutDetection' */
  INT8U is_FrontAngleAdjust;           /* '<S7>/MotorTimeOutDetection' */
  INT8U is_active_c9_APPL_DriverFaultDetection;/* '<S6>/HallErrorDetection' */
  INT8U is_c9_APPL_DriverFaultDetection;/* '<S6>/HallErrorDetection' */
  INT8U is_HeightHallError;            /* '<S6>/HallErrorDetection' */
  INT8U is_LengthHallError;            /* '<S6>/HallErrorDetection' */
  INT8U is_BackHallError;              /* '<S6>/HallErrorDetection' */
  INT8U is_FrontHallError3;            /* '<S6>/HallErrorDetection' */
  INT8U HeightHallTimer;               /* '<S6>/HallErrorDetection' */
  INT8U LengthHallTimer;               /* '<S6>/HallErrorDetection' */
  INT8U BackHallTimer;                 /* '<S6>/HallErrorDetection' */
  INT8U FrontHallTimer;                /* '<S6>/HallErrorDetection' */
  INT8U is_active_c8_APPL_DriverFaultDetection;/* '<S5>/SwitchErrorDetection' */
  INT8U is_HeightSwitchErrorDeal;      /* '<S5>/SwitchErrorDetection' */
  INT8U is_LengthSwitchErrorDeal;      /* '<S5>/SwitchErrorDetection' */
  INT8U is_BackSwitchErrorDeal;        /* '<S5>/SwitchErrorDetection' */
  INT8U is_FrontSwitchErrorDeal;       /* '<S5>/SwitchErrorDetection' */
  BOOL DrAdj_Dtc_HeatingMat1SC;        /* '<S6>/HallErrorDetection' */
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T CheckMidRelayFault3;/* '<S21>/CheckMidRelayFault3' */
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T CheckMidRelayFault2;/* '<S21>/CheckMidRelayFault2' */
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T CheckMidRelayFault1;/* '<S21>/CheckMidRelayFault1' */
  DW_CheckMidRelayFault_APPL_DriverFaultDetection_T CheckMidRelayFault;/* '<S21>/CheckMidRelayFault' */
}
DW_APPL_DriverFaultDetection_T;

/* Real-time Model Data Structure */
struct tag_RTM_APPL_DriverFaultDetection_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_APPL_DriverFaultDetection_T APPL_DriverFaultDetection_B;

/* Block states (default storage) */
extern DW_APPL_DriverFaultDetection_T APPL_DriverFaultDetection_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMoveCmd MtrCtrlFault_DrBackSwitch;/* '<S38>/MtrCtrlFault_DrBackSwitch'
                                                * 硬线调节开关输入方向-主驾靠背
                                                */
extern enSeatMoveCmd MtrCtrlFault_DrFrontSwitch;/* '<S38>/MtrCtrlFault_DrFrontSwitch'
                                                 * 硬线调节开关输入方向-主驾腿托
                                                 */
extern enSeatMoveCmd MtrCtrlFault_DrHeightSwitch;/* '<S38>/MtrCtrlFault_DrHeightSwitch'
                                                  * 硬线调节开关输入方向-主驾高度
                                                  */
extern enSeatMoveCmd MtrCtrlFault_DrLengthSwitch;/* '<S38>/MtrCtrlFault_DrLengthSwitch'
                                                  * 硬线调节开关输入方向-主驾纵向
                                                  */
extern enIgnSts MtrCtrlFault_DrPowerModeStatus;/* '<S38>/MtrCtrlFault_DrPowerModeStatus'
                                                * 整车电源档位
                                                */
extern enDrAdjustEnable MtrCtrlFault_DrAdjustCfg;/* '<S38>/MtrCtrlFault_DrAdjustCfg'
                                                  * 主驾座椅调节配置  0x00:手动调节  0x01:六向电机  0x02:十二向电机
                                                  */
extern INT16U MtrCtrlFault_DrBackHallCnt;/* '<S38>/MtrCtrlFault_DrBackHallCnt'
                                          * 当前霍尔-主驾靠背
                                          */
extern INT16U MtrCtrlFault_DrBackMotorSize;/* '<S38>/MtrCtrlFault_DrBackMotorSize'
                                            * 导轨长度-主驾靠背
                                            */
extern INT16U MtrCtrlFault_DrBackStopPosi;/* '<S38>/MtrCtrlFault_DrBackStopPosi'
                                           * 硬止点位置-主驾靠背
                                           */
extern INT16U MtrCtrlFault_DrFrontHallCnt;/* '<S38>/MtrCtrlFault_DrFrontHallCnt'
                                           * 当前霍尔-主驾腿托
                                           */
extern INT16U MtrCtrlFault_DrFrontMotorSize;/* '<S38>/MtrCtrlFault_DrFrontMotorSize'
                                             * 导轨长度-主驾腿托
                                             */
extern INT16U MtrCtrlFault_DrFrontStopPosi;/* '<S38>/MtrCtrlFault_DrFrontStopPosi'
                                            * 硬止点位置-主驾腿托
                                            */
extern INT16U MtrCtrlFault_DrHeightHallCnt;/* '<S38>/MtrCtrlFault_DrHeightHallCnt'
                                            * 当前霍尔-主驾高度
                                            */
extern INT16U MtrCtrlFault_DrHeightMotorSize;/* '<S38>/MtrCtrlFault_DrHeightMotorSize'
                                              * 导轨长度-主驾高度
                                              */
extern INT16U MtrCtrlFault_DrHeightStopPosi;/* '<S38>/MtrCtrlFault_DrHeightStopPosi'
                                             * 硬止点位置-主驾高度
                                             */
extern INT16U MtrCtrlFault_DrLengthHallCnt;/* '<S38>/MtrCtrlFault_DrLengthHallCnt'
                                            * 当前霍尔-主驾纵向
                                            */
extern INT16U MtrCtrlFault_DrLengthMotorSize;/* '<S38>/MtrCtrlFault_DrLengthMotorSize'
                                              * 导轨长度-主驾纵向
                                              */
extern INT16U MtrCtrlFault_DrLengthStopPosi;/* '<S38>/MtrCtrlFault_DrLengthStopPosi'
                                             * 硬止点位置-主驾纵向
                                             */
extern INT8U MtrCtrlFault_DrBackBackwardVolt;/* '<S38>/MtrCtrlFault_DrBackBackwardVolt'
                                              * 主驾靠背向后
                                              */
extern INT8U MtrCtrlFault_DrBackCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrBackCurrentOverFlag'
                                                 * 反馈电流超过堵转阈值标志-主驾靠背
                                                 */
extern INT8U MtrCtrlFault_DrBackForwardVolt;/* '<S38>/MtrCtrlFault_DrBackForwardVolt'
                                             * 主驾靠背向前
                                             */
extern INT8U MtrCtrlFault_DrBackLearnFlag;/* '<S38>/MtrCtrlFault_DrBackLearnFlag'
                                           * 电机学习标志-主驾靠背
                                           */
extern INT8U MtrCtrlFault_DrBackMotorCmd;/* '<S38>/MtrCtrlFault_DrBackMotorCmd'
                                          * 模型输出到电机的CMD-主驾靠背
                                          */
extern INT8U MtrCtrlFault_DrBackSoftStopCnt;/* '<S38>/MtrCtrlFault_DrBackSoftStopCnt'
                                             * 到达软止点次数(E2)-主驾靠背
                                             */
extern INT8U MtrCtrlFault_DrFrontCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrFrontCurrentOverFlag'
                                                  * 反馈电流超过堵转阈值标志-主驾腿托
                                                  */
extern INT8U MtrCtrlFault_DrFrontDownVolt;/* '<S38>/MtrCtrlFault_DrFrontDownVolt'
                                           * 主驾腿托向下
                                           */
extern INT8U MtrCtrlFault_DrFrontLearnFlag;/* '<S38>/MtrCtrlFault_DrFrontLearnFlag'
                                            * 电机学习标志-主驾腿托
                                            */
extern INT8U MtrCtrlFault_DrFrontMotorCmd;/* '<S38>/MtrCtrlFault_DrFrontMotorCmd'
                                           * 模型输出到电机的CMD-主驾腿托
                                           */
extern INT8U MtrCtrlFault_DrFrontSoftStopCnt;/* '<S38>/MtrCtrlFault_DrFrontSoftStopCnt'
                                              * 到达软止点次数(E2)-主驾腿托
                                              */
extern INT8U MtrCtrlFault_DrFrontUpVolt;/* '<S38>/MtrCtrlFault_DrFrontUpVolt'
                                         * 主驾腿托向上
                                         */
extern INT8U MtrCtrlFault_DrHeightCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrHeightCurrentOverFlag'
                                                   * 反馈电流超过堵转阈值标志-主驾高度
                                                   */
extern INT8U MtrCtrlFault_DrHeightDownVolt;/* '<S38>/MtrCtrlFault_DrHeightDownVolt'
                                            * 主驾高度向下
                                            */
extern INT8U MtrCtrlFault_DrHeightLearnFlag;/* '<S38>/MtrCtrlFault_DrHeightLearnFlag'
                                             * 电机学习标志-主驾高度
                                             */
extern INT8U MtrCtrlFault_DrHeightMotorCmd;/* '<S38>/MtrCtrlFault_DrHeightMotorCmd'
                                            * 模型输出到电机的CMD-主驾高度
                                            */
extern INT8U MtrCtrlFault_DrHeightSoftStopCnt;/* '<S38>/MtrCtrlFault_DrHeightSoftStopCnt'
                                               * 到达软止点次数(E2)-主驾高度
                                               */
extern INT8U MtrCtrlFault_DrHeightUpVolt;/* '<S38>/MtrCtrlFault_DrHeightUpVolt'
                                          * 主驾高度向上
                                          */
extern INT8U MtrCtrlFault_DrLengthBackwardVolt;/* '<S38>/MtrCtrlFault_DrLengthBackwardVolt'
                                                * 主驾纵向向后
                                                */
extern INT8U MtrCtrlFault_DrLengthCurrentOverFlag;/* '<S38>/MtrCtrlFault_DrLengthCurrentOverFlag'
                                                   * 反馈电流超过堵转阈值标志-主驾纵向
                                                   */
extern INT8U MtrCtrlFault_DrLengthForwardVolt;/* '<S38>/MtrCtrlFault_DrLengthForwardVolt'
                                               * 主驾纵向向前
                                               */
extern INT8U MtrCtrlFault_DrLengthLearnFlag;/* '<S38>/MtrCtrlFault_DrLengthLearnFlag'
                                             * 电机学习标志-主驾纵向
                                             */
extern INT8U MtrCtrlFault_DrLengthMotorCmd;/* '<S38>/MtrCtrlFault_DrLengthMotorCmd'
                                            * 模型输出到电机的CMD-主驾纵向
                                            */
extern INT8U MtrCtrlFault_DrLengthSoftStopCnt;/* '<S38>/MtrCtrlFault_DrLengthSoftStopCnt'
                                               * 到达软止点次数(E2)-主驾纵向
                                               */
extern INT8U MtrCtrlFault_DrMemoryCfg; /* '<S38>/MtrCtrlFault_DrMemoryCfg'
                                        *  主驾记忆迎宾配置  0:不存在  2：存在
                                        */
extern INT8U MtrCtrlFault_DrMotorSoftStopCntMax;/* '<S38>/MtrCtrlFault_DrMotorSoftStopCntMax'
                                                 * 软止点最大调节次数（E2）
                                                 */

/* Model entry point functions */
extern void APPL_DriverFaultDetection_initialize(void);
extern void APPL_DriverFaultDetection_step(void);

/* Real-time Model object */
extern RT_MODEL_APPL_DriverFaultDetection_T *const APPL_DriverFaultDetection_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'APPL_DriverFaultDetection'
 * '<S1>'   : 'APPL_DriverFaultDetection/LogicCtrl'
 * '<S2>'   : 'APPL_DriverFaultDetection/Model Info'
 * '<S3>'   : 'APPL_DriverFaultDetection/UpDataInputInfo'
 * '<S4>'   : 'APPL_DriverFaultDetection/UpDataOutputInfo'
 * '<S5>'   : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec'
 * '<S6>'   : 'APPL_DriverFaultDetection/LogicCtrl/HallError'
 * '<S7>'   : 'APPL_DriverFaultDetection/LogicCtrl/MotorTimeOut'
 * '<S8>'   : 'APPL_DriverFaultDetection/LogicCtrl/RelayError'
 * '<S9>'   : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint'
 * '<S10>'  : 'APPL_DriverFaultDetection/LogicCtrl/StallError'
 * '<S11>'  : 'APPL_DriverFaultDetection/LogicCtrl/SwitchErrDeal'
 * '<S12>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection'
 * '<S13>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetCurMsTs'
 * '<S14>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetDefTime'
 * '<S15>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/TimeDiffTs'
 * '<S16>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetDefTime/Chart'
 * '<S17>'  : 'APPL_DriverFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/TimeDiffTs/Chart'
 * '<S18>'  : 'APPL_DriverFaultDetection/LogicCtrl/HallError/HallErrorDetection'
 * '<S19>'  : 'APPL_DriverFaultDetection/LogicCtrl/MotorTimeOut/Enumerated Constant'
 * '<S20>'  : 'APPL_DriverFaultDetection/LogicCtrl/MotorTimeOut/MotorTimeOutDetection'
 * '<S21>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection'
 * '<S22>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault'
 * '<S23>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault1'
 * '<S24>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault2'
 * '<S25>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault3'
 * '<S26>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault/RelayFault'
 * '<S27>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault1/RelayFault'
 * '<S28>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault2/RelayFault'
 * '<S29>'  : 'APPL_DriverFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault3/RelayFault'
 * '<S30>'  : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection'
 * '<S31>'  : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetBackSoftStopCnt'
 * '<S32>'  : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetFrontSoftStopCnt'
 * '<S33>'  : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetHeightSoftStopCnt'
 * '<S34>'  : 'APPL_DriverFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetLengthSoftStopCnt'
 * '<S35>'  : 'APPL_DriverFaultDetection/LogicCtrl/StallError/StallErrorDetection'
 * '<S36>'  : 'APPL_DriverFaultDetection/LogicCtrl/SwitchErrDeal/ SWProcess '
 * '<S37>'  : 'APPL_DriverFaultDetection/UpDataInputInfo/InputSignalProcess'
 * '<S38>'  : 'APPL_DriverFaultDetection/UpDataInputInfo/RTE_InputSignal'
 */
#endif                                 /* RTW_HEADER_APPL_DriverFaultDetection_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
