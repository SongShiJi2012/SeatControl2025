/*
 * File: APPL_PaFaultDetection.h
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

#ifndef RTW_HEADER_APPL_PaFaultDetection_h_
#define RTW_HEADER_APPL_PaFaultDetection_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef APPL_PaFaultDetection_COMMON_INCLUDES_
# define APPL_PaFaultDetection_COMMON_INCLUDES_
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
#endif                                 /* APPL_PaFaultDetection_COMMON_INCLUDES_ */

#include "APPL_PaFaultDetection_types.h"

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
  INT8U is_active_c4_APPL_PaFaultDetection;/* '<S22>/RelayFault' */
  INT8U is_c4_APPL_PaFaultDetection;   /* '<S22>/RelayFault' */
}
DW_CheckMidRelayFault_APPL_PaFaultDetection_T;

/* Block signals (default storage) */
typedef struct
{
  INT32U DrAdj_CurMsTs;                /* '<S13>/DrAdj_LenAdjSize' */
  enSeatMoveCmd CurrentHeightSwCmd;    /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentLengthSwCmd;    /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentBackSwCmd;      /* '<S11>/ SWProcess ' */
  enSeatMoveCmd CurrentFrontSwCmd;     /* '<S11>/ SWProcess ' */
  enSeatMoveCmd LengthSwCmd;           /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd BackSwCmd;             /* '<S5>/SwitchErrorDetection' */
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
  INT8U MotorCmd;                      /* '<S8>/MidRelayErrorDetection' */
  INT8U UpForwardVolt;                 /* '<S8>/MidRelayErrorDetection' */
  INT8U DownBackwardVolt;              /* '<S8>/MidRelayErrorDetection' */
  INT8U MotorCmd_p;                    /* '<S8>/MidRelayErrorDetection' */
  INT8U UpForwardVolt_c;               /* '<S8>/MidRelayErrorDetection' */
  INT8U DownBackwardVolt_h;            /* '<S8>/MidRelayErrorDetection' */
  INT8U MidRelayFault_p;               /* '<S24>/RelayFault' */
  INT8U MidRelayTimer_p;               /* '<S24>/RelayFault' */
  INT8U MidRelayFault_f;               /* '<S23>/RelayFault' */
  INT8U MidRelayTimer_pv;              /* '<S23>/RelayFault' */
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
  INT8U LengthSwUpAdhesionFault;       /* '<S5>/SwitchErrorDetection' */
  INT8U LengthSwDownAdhesionFault;     /* '<S5>/SwitchErrorDetection' */
  INT8U BackSwUpAdhesionFault;         /* '<S5>/SwitchErrorDetection' */
  INT8U BackSwDownAdhesionFault;       /* '<S5>/SwitchErrorDetection' */
}
B_APPL_PaFaultDetection_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
  INT32U LengthSwTimer;                /* '<S5>/SwitchErrorDetection' */
  INT32U BackSwTimer;                  /* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd LengthSwCmd_start;     /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd BackSwCmd_start;       /* '<S10>/StallErrorDetection' */
  enSeatMoveCmd LengthSwCmd_start_g;   /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd BackSwCmd_start_c;     /* '<S6>/HallErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRLengthSwitch_start;/* '<S5>/SwitchErrorDetection' */
  enSeatMoveCmd MtrCtrlFault_DRBackSwitch_start;/* '<S5>/SwitchErrorDetection' */
  INT16U LocalLengthHallCnt;           /* '<S10>/StallErrorDetection' */
  INT16U LocalBackHallCnt;             /* '<S10>/StallErrorDetection' */
  INT16U BackTimer;                    /* '<S7>/MotorTimeOutDetection' */
  INT16U LengthTimer;                  /* '<S7>/MotorTimeOutDetection' */
  INT16U MtrCtrlFault_LengthHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT16U MtrCtrlFault_BackHallCnt_start;/* '<S6>/HallErrorDetection' */
  INT8U is_active_c1_APPL_PaFaultDetection;/* '<S11>/ SWProcess ' */
  INT8U is_c1_APPL_PaFaultDetection;   /* '<S11>/ SWProcess ' */
  INT8U is_LengthSWProcess;            /* '<S11>/ SWProcess ' */
  INT8U is_BackSWProcess;              /* '<S11>/ SWProcess ' */
  INT8U is_active_c10_APPL_PaFaultDetection;/* '<S10>/StallErrorDetection' */
  INT8U is_LengthStallError;           /* '<S10>/StallErrorDetection' */
  INT8U is_BackStallError;             /* '<S10>/StallErrorDetection' */
  INT8U LengthStallTimer;              /* '<S10>/StallErrorDetection' */
  INT8U BackStallTimer;                /* '<S10>/StallErrorDetection' */
  INT8U LengthStallNoTimer;            /* '<S10>/StallErrorDetection' */
  INT8U BackStallNoTimer;              /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer2;             /* '<S10>/StallErrorDetection' */
  INT8U CurrentOverTimer3;             /* '<S10>/StallErrorDetection' */
  INT8U is_active_c33_APPL_PaFaultDetection;/* '<S9>/SoftStopPointDetection' */
  INT8U is_LengthSoft;                 /* '<S9>/SoftStopPointDetection' */
  INT8U is_BackSoft;                   /* '<S9>/SoftStopPointDetection' */
  INT8U LengthSoftStopBufCnt;          /* '<S9>/SoftStopPointDetection' */
  INT8U BackSoftStopBufCnt;            /* '<S9>/SoftStopPointDetection' */
  INT8U is_active_c3_APPL_PaFaultDetection;/* '<S8>/MidRelayErrorDetection' */
  INT8U is_active_c16_APPL_PaFaultDetection;/* '<S7>/MotorTimeOutDetection' */
  INT8U is_VerticalAdjust;             /* '<S7>/MotorTimeOutDetection' */
  INT8U is_BackAdjust;                 /* '<S7>/MotorTimeOutDetection' */
  INT8U is_active_c9_APPL_PaFaultDetection;/* '<S6>/HallErrorDetection' */
  INT8U is_c9_APPL_PaFaultDetection;   /* '<S6>/HallErrorDetection' */
  INT8U is_LengthHallError;            /* '<S6>/HallErrorDetection' */
  INT8U is_BackHallError;              /* '<S6>/HallErrorDetection' */
  INT8U LengthHallTimer;               /* '<S6>/HallErrorDetection' */
  INT8U BackHallTimer;                 /* '<S6>/HallErrorDetection' */
  INT8U is_active_c8_APPL_PaFaultDetection;/* '<S5>/SwitchErrorDetection' */
  INT8U is_LengthSwitchErrorDeal;      /* '<S5>/SwitchErrorDetection' */
  INT8U is_BackSwitchErrorDeal;        /* '<S5>/SwitchErrorDetection' */
  BOOL DrAdj_Dtc_HeatingMat1SC;        /* '<S6>/HallErrorDetection' */
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T CheckMidRelayFault3;/* '<S21>/CheckMidRelayFault3' */
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T CheckMidRelayFault2;/* '<S21>/CheckMidRelayFault2' */
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T CheckMidRelayFault1;/* '<S21>/CheckMidRelayFault1' */
  DW_CheckMidRelayFault_APPL_PaFaultDetection_T CheckMidRelayFault;/* '<S21>/CheckMidRelayFault' */
}
DW_APPL_PaFaultDetection_T;

/* Real-time Model Data Structure */
struct tag_RTM_APPL_PaFaultDetection_T
{
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_APPL_PaFaultDetection_T APPL_PaFaultDetection_B;

/* Block states (default storage) */
extern DW_APPL_PaFaultDetection_T APPL_PaFaultDetection_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern enSeatMoveCmd MtrCtrlFault_PaBackSwitch;/* '<S38>/MtrCtrlFault_PaBackSwitch'
                                                * 硬线调节开关输入方向-副驾靠背
                                                */
extern enSeatMoveCmd MtrCtrlFault_PaFrontSwitch;/* '<S38>/MtrCtrlFault_PaFrontSwitch'
                                                 * 硬线调节开关输入方向-副驾腿托
                                                 */
extern enSeatMoveCmd MtrCtrlFault_PaHeightSwitch;/* '<S38>/MtrCtrlFault_PaHeightSwitch'
                                                  * 硬线调节开关输入方向-副驾高度
                                                  */
extern enSeatMoveCmd MtrCtrlFault_PaLengthSwitch;/* '<S38>/MtrCtrlFault_PaLengthSwitch'
                                                  * 硬线调节开关输入方向-副驾纵向
                                                  */
extern enIgnSts MtrCtrlFault_PaPowerModeStatus;/* '<S38>/MtrCtrlFault_PaPowerModeStatus'
                                                * 整车电源档位
                                                */
extern INT16U MtrCtrlFault_PaBackHallCnt;/* '<S38>/MtrCtrlFault_PaBackHallCnt'
                                          * 靠背当前霍尔
                                          */
extern INT16U MtrCtrlFault_PaBackMotorSize;/* '<S38>/MtrCtrlFault_PaBackMotorSize'
                                            * 靠背导轨长度
                                            */
extern INT16U MtrCtrlFault_PaBackStopPosi;/* '<S38>/MtrCtrlFault_PaBackStopPosi'
                                           * 靠背硬止点位置
                                           */
extern INT16U MtrCtrlFault_PaFrontHallCnt;/* '<S38>/MtrCtrlFault_PaFrontHallCnt'
                                           * 腿托当前霍尔
                                           */
extern INT16U MtrCtrlFault_PaFrontMotorSize;/* '<S38>/MtrCtrlFault_PaFrontMotorSize'
                                             * 腿托导轨长度
                                             */
extern INT16U MtrCtrlFault_PaFrontStopPosi;/* '<S38>/MtrCtrlFault_PaFrontStopPosi'
                                            * 腿托硬止点位置
                                            */
extern INT16U MtrCtrlFault_PaHeightHallCnt;/* '<S38>/MtrCtrlFault_PaHeightHallCnt'
                                            * 高度当前霍尔
                                            */
extern INT16U MtrCtrlFault_PaHeightMotorSize;/* '<S38>/MtrCtrlFault_PaHeightMotorSize'
                                              * 高度导轨长度
                                              */
extern INT16U MtrCtrlFault_PaHeightStopPosi;/* '<S38>/MtrCtrlFault_PaHeightStopPosi'
                                             * 高度硬止点位置
                                             */
extern INT16U MtrCtrlFault_PaLengthHallCnt;/* '<S38>/MtrCtrlFault_PaLengthHallCnt'
                                            * 纵向当前霍尔
                                            */
extern INT16U MtrCtrlFault_PaLengthMotorSize;/* '<S38>/MtrCtrlFault_PaLengthMotorSize'
                                              * 纵向导轨长度
                                              */
extern INT16U MtrCtrlFault_PaLengthStopPosi;/* '<S38>/MtrCtrlFault_PaLengthStopPosi'
                                             * 纵向硬止点位置
                                             */
extern INT8U MtrCtrlFault_PaAdjustCfg; /* '<S38>/MtrCtrlFault_PaAdjustCfg'
                                        *  副驾座椅调节配置  0x00:手动调节  0x01:四向电机
                                        */
extern INT8U MtrCtrlFault_PaBackBackwardVolt;/* '<S38>/MtrCtrlFault_PaBackBackwardVolt'
                                              * 靠背向后
                                              */
extern INT8U MtrCtrlFault_PaBackCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaBackCurrentOverFlag'
                                                 * 靠背反馈电流超过堵转阈值标志
                                                 */
extern INT8U MtrCtrlFault_PaBackForwardVolt;/* '<S38>/MtrCtrlFault_PaBackForwardVolt'
                                             * 靠背向前
                                             */
extern INT8U MtrCtrlFault_PaBackLearnFlag;/* '<S38>/MtrCtrlFault_PaBackLearnFlag'
                                           * 靠背电机学习标志
                                           */
extern INT8U MtrCtrlFault_PaBackMotorCmd;/* '<S38>/MtrCtrlFault_PaBackMotorCmd'
                                          * 模型输出到电机的CMD-副驾靠背
                                          */
extern INT8U MtrCtrlFault_PaBackSoftStopCnt;/* '<S38>/MtrCtrlFault_PaBackSoftStopCnt'
                                             * 靠背到达软止点次数（E2）
                                             */
extern INT8U MtrCtrlFault_PaFrontCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaFrontCurrentOverFlag'
                                                  * 腿托反馈电流超过堵转阈值标志
                                                  */
extern INT8U MtrCtrlFault_PaFrontDownVolt;/* '<S38>/MtrCtrlFault_PaFrontDownVolt'
                                           * 腿托向下
                                           */
extern INT8U MtrCtrlFault_PaFrontLearnFlag;/* '<S38>/MtrCtrlFault_PaFrontLearnFlag'
                                            * 腿托电机学习标志
                                            */
extern INT8U MtrCtrlFault_PaFrontMotorCmd;/* '<S38>/MtrCtrlFault_PaFrontMotorCmd'
                                           * 模型输出到电机的CMD-副驾腿托
                                           */
extern INT8U MtrCtrlFault_PaFrontSoftStopCnt;/* '<S38>/MtrCtrlFault_PaFrontSoftStopCnt'
                                              * 腿托到达软止点次数（E2）
                                              */
extern INT8U MtrCtrlFault_PaFrontUpVolt;/* '<S38>/MtrCtrlFault_PaFrontUpVolt'
                                         * 腿托向上
                                         */
extern INT8U MtrCtrlFault_PaHeightCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaHeightCurrentOverFlag'
                                                   * 高度反馈电流超过堵转阈值标志
                                                   */
extern INT8U MtrCtrlFault_PaHeightDownVolt;/* '<S38>/MtrCtrlFault_PaHeightDownVolt'
                                            * 高度向下
                                            */
extern INT8U MtrCtrlFault_PaHeightLearnFlag;/* '<S38>/MtrCtrlFault_PaHeightLearnFlag'
                                             * 高度电机学习标志
                                             */
extern INT8U MtrCtrlFault_PaHeightMotorCmd;/* '<S38>/MtrCtrlFault_PaHeightMotorCmd'
                                            * 模型输出到电机的CMD-副驾高度
                                            */
extern INT8U MtrCtrlFault_PaHeightSoftStopCnt;/* '<S38>/MtrCtrlFault_PaHeightSoftStopCnt'
                                               * 高度到达软止点次数（E2）
                                               */
extern INT8U MtrCtrlFault_PaHeightUpVolt;/* '<S38>/MtrCtrlFault_PaHeightUpVolt'
                                          * 高度向上
                                          */
extern INT8U MtrCtrlFault_PaLengthBackwardVolt;/* '<S38>/MtrCtrlFault_PaLengthBackwardVolt'
                                                * 纵向向后
                                                */
extern INT8U MtrCtrlFault_PaLengthCurrentOverFlag;/* '<S38>/MtrCtrlFault_PaLengthCurrentOverFlag'
                                                   * 纵向反馈电流超过堵转阈值标志
                                                   */
extern INT8U MtrCtrlFault_PaLengthForwardVolt;/* '<S38>/MtrCtrlFault_PaLengthForwardVolt'
                                               * 纵向向前
                                               */
extern INT8U MtrCtrlFault_PaLengthLearnFlag;/* '<S38>/MtrCtrlFault_PaLengthLearnFlag'
                                             * 纵向电机学习标志
                                             */
extern INT8U MtrCtrlFault_PaLengthMotorCmd;/* '<S38>/MtrCtrlFault_PaLengthMotorCmd'
                                            * 模型输出到电机的CMD-副驾纵向
                                            */
extern INT8U MtrCtrlFault_PaLengthSoftStopCnt;/* '<S38>/MtrCtrlFault_PaLengthSoftStopCnt'
                                               * 纵向到达软止点次数（E2）
                                               */
extern INT8U MtrCtrlFault_PaMemoryCfg; /* '<S38>/MtrCtrlFault_PaMemoryCfg'
                                        *  副驾记忆迎宾配置  0:不存在  2：存在
                                        */
extern INT8U MtrCtrlFault_PaMotorSoftStopCntMax;/* '<S38>/MtrCtrlFault_PaMotorSoftStopCntMax'
                                                 * 软止点最大调节次数（E2）
                                                 */

/* Model entry point functions */
extern void APPL_PaFaultDetection_initialize(void);
extern void APPL_PaFaultDetection_step(void);

/* Real-time Model object */
extern RT_MODEL_APPL_PaFaultDetection_T *const APPL_PaFaultDetection_M;

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
 * '<Root>' : 'APPL_PaFaultDetection'
 * '<S1>'   : 'APPL_PaFaultDetection/LogicCtrl'
 * '<S2>'   : 'APPL_PaFaultDetection/Model Info'
 * '<S3>'   : 'APPL_PaFaultDetection/UpDataInputInfo'
 * '<S4>'   : 'APPL_PaFaultDetection/UpDataOutputInfo'
 * '<S5>'   : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec'
 * '<S6>'   : 'APPL_PaFaultDetection/LogicCtrl/HallError'
 * '<S7>'   : 'APPL_PaFaultDetection/LogicCtrl/MotorTimeOut'
 * '<S8>'   : 'APPL_PaFaultDetection/LogicCtrl/RelayError'
 * '<S9>'   : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint'
 * '<S10>'  : 'APPL_PaFaultDetection/LogicCtrl/StallError'
 * '<S11>'  : 'APPL_PaFaultDetection/LogicCtrl/SwitchErrDeal'
 * '<S12>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection'
 * '<S13>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetCurMsTs'
 * '<S14>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetDefTime'
 * '<S15>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/TimeDiffTs'
 * '<S16>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/GetDefTime/Chart'
 * '<S17>'  : 'APPL_PaFaultDetection/LogicCtrl/AdheAndEffec/SwitchErrorDetection/TimeDiffTs/Chart'
 * '<S18>'  : 'APPL_PaFaultDetection/LogicCtrl/HallError/HallErrorDetection'
 * '<S19>'  : 'APPL_PaFaultDetection/LogicCtrl/MotorTimeOut/Enumerated Constant'
 * '<S20>'  : 'APPL_PaFaultDetection/LogicCtrl/MotorTimeOut/MotorTimeOutDetection'
 * '<S21>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection'
 * '<S22>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault'
 * '<S23>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault1'
 * '<S24>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault2'
 * '<S25>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault3'
 * '<S26>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault/RelayFault'
 * '<S27>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault1/RelayFault'
 * '<S28>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault2/RelayFault'
 * '<S29>'  : 'APPL_PaFaultDetection/LogicCtrl/RelayError/MidRelayErrorDetection/CheckMidRelayFault3/RelayFault'
 * '<S30>'  : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection'
 * '<S31>'  : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetBackSoftStopCnt'
 * '<S32>'  : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetFrontSoftStopCnt'
 * '<S33>'  : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetHeightSoftStopCnt'
 * '<S34>'  : 'APPL_PaFaultDetection/LogicCtrl/SoftStopPoint/SoftStopPointDetection/DrAdj_SetLengthSoftStopCnt'
 * '<S35>'  : 'APPL_PaFaultDetection/LogicCtrl/StallError/StallErrorDetection'
 * '<S36>'  : 'APPL_PaFaultDetection/LogicCtrl/SwitchErrDeal/ SWProcess '
 * '<S37>'  : 'APPL_PaFaultDetection/UpDataInputInfo/InputSignalProcess'
 * '<S38>'  : 'APPL_PaFaultDetection/UpDataInputInfo/RTE_InputSignal'
 */
#endif                                 /* RTW_HEADER_APPL_PaFaultDetection_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
