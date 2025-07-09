/*
 * File: Rte_get_Light.h
 *
 * Code generated for Simulink model 'Rte_get_Light'.
 *
 * Model version                  : 1.107
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Mar 17 11:27:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Rte_get_Light_h_
#define RTW_HEADER_Rte_get_Light_h_
#include <stddef.h>
#ifndef Rte_get_Light_COMMON_INCLUDES_
# define Rte_get_Light_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_Get_API.h"
#endif                                 /* Rte_get_Light_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Rte_get_Light_T RT_MODEL_Rte_get_Light_T;

/* Real-time Model Data Structure */
struct tag_RTM_Rte_get_Light_T
{
  const char_T * volatile errorStatus;
};

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern INT8U ExLampSw;                 /* '<Root>/getAPI'
                                        * 大灯开关状态，0：OFF，1：位置灯，2：自动灯，3：近光灯，模拟自锁
                                        */
extern INT8U TurnLampSw;               /* '<Root>/getAPI1'
                                        * 转向开关状态，OFF/Dir_Left/Dir_Right，模拟自锁
                                        */
extern INT8U HighBeamSw;               /* '<Root>/getAPI2'
                                        * 远光灯开关，OFF/HighBeam/Flash，模拟点触，NULL  (0u)，High  (1u)，Flash  (2u)
                                        */
extern INT8U HarzedLampSw;             /* '<Root>/getAPI3'
                                        * 危险报警开关状态，数字点触，有效值：Low
                                        */
extern INT8U FogLampSw;                /* '<Root>/getAPI4'
                                        * 雾灯开关，OFF/Front Fog/Rear Fog，模拟点触
                                        */
extern INT8U ReverseLampSw;            /* '<Root>/getAPI5'
                                        * 倒车挡开关状态，数字自锁， 有效值：Low
                                        */
extern INT8U BrakeLampSw;              /* '<Root>/getAPI6'
                                        * 刹车开关状态，数字自锁， 有效值：high
                                        */
extern INT8U FL_DIR_Fault_Sts;         /* '<Root>/getAPI7'
                                        * 左前 LED 转向灯故障反馈状态，数字自锁，有效值：high
                                        */
extern INT8U FR_DIR_Fault_Sts;         /* '<Root>/getAPI8'
                                        * 右前 LED 转向灯故障反馈状态，数字自锁，有效值：high
                                        */
extern INT8U DriverDoorAjar;           /* '<Root>/getAPI9'
                                        * 司机门状态，模拟自锁，Close/Open/Invalid，具体含义
                                        */
extern INT8U PassDoorAjar;             /* '<Root>/getAPI10'
                                        * 副司机门状态，Close/Open/Invalid，数字自锁， 有效值：Low
                                        */
extern INT8U RLeftDoorAjar;            /* '<Root>/getAPI11'
                                        * 左后门状态，数字自锁， 有效值：Low
                                        */
extern INT8U RRightDoorAjar;           /* '<Root>/getAPI12'
                                        * 右后门状态，数字自锁， 有效值：Low
                                        */
extern INT8U TrunkDoorAjar;            /* '<Root>/getAPI13'
                                        * 后备箱门状态，数字自锁， 有效值：Low
                                        */
extern INT8U PowerMode;                /* '<Root>/getAPI14'
                                        * 电源模式，0：OFF，1：ACC，2：ON，3：START
                                        */
extern INT8U VehOpModePrm;             /* '<Root>/getAPI15'
                                        * 车辆工作模式，默认值：0， 0：用户模式 1：工厂模式， 2：运输模式， 3：预留
                                        */
extern INT8U VehManufMaxTimPrm;        /* '<Root>/getAPI16'
                                        * 工厂和运输模式最大时间配置，默认值：5，1 单位为一分钟，取值范围：1~7
                                        */
extern INT8U VehManuOrAutoGearPrm;     /* '<Root>/getAPI17'
                                        * 自动/手动档车型配置， 0:Automatic gearbox with electronic gear shifter 1:Automatic gearbox with one-way solenoid 2:Automatic gearbox with two-way solenoid 3:Manual gearbox fitted
                                        */
extern INT8U VehEnFrontFogLampPrm;     /* '<Root>/getAPI18'
                                        * 前雾灯配置，0:No Front Fog Lamps 1:Front Fog Lamps fitted
                                        */
extern INT8U VehEnDRLPrm;              /* '<Root>/getAPI19'
                                        * 日间行车灯配置，0:No DRL 1:Hardwired DRL 2:LIN DRL 3:Reserved
                                        */
extern INT8U ExlFrontDirLampsDiagtypePrm;/* '<Root>/getAPI20'
                                          * 前转向灯类型配置， 0:Halogen Direction lamp fitted 1:LED Direction lamp fitted 2:LIN Direction lamp fitted 3:Reserved
                                          */
extern INT8U VehLowBeamTypePrm;        /* '<Root>/getAPI21'
                                        * 近光灯类型， 0:Halogen Low Beam fitted 1:Xenon Low Beam fitted 2:LED Low Beam fitted 3:Seperate LIN controller
                                        */
extern INT8U VehHighBeamTypePrm;       /* '<Root>/getAPI22'
                                        * 远光灯类型， 0:Halogen High Beam fitted 1:Xenon High Beam fitted 2:LED High Beam fitted 3:Seperate LIN controller 4:High Beam Solenoid fitted 5:Reserved
                                        */
extern INT8U ExlBeamHeightAdjustPrm;   /* '<Root>/getAPI23'
                                        * 大灯高度调节方式 0:No Height Adjust Function 1:Harewire 2:LIN 3:Reserved
                                        */
extern INT8U ExlFPosLampsDiagtypePrm;  /* '<Root>/getAPI24'
                                        * 前位置灯类型 0:Halogen Position lamp fitted 1:LED Position lamp fitted 2:LIN Position lamp fitted 3:Reserved
                                        */
extern INT8U VehEnWelLampPrm;          /* '<Root>/getAPI25'
                                        * 是否配置迎宾灯 0:No Welcome lamp 1:Welcome lamp fitted
                                        */
extern INT8U VehExLampSwTypePrm;       /* '<Root>/getAPI26'
                                        * 大灯开关类型 0:Hardwire switch 1:CAN signal switch 2:LIN signal switch 3:Reserved
                                        */
extern INT8U VehAVMWelcomeLightEnablePrm;/* '<Root>/getAPI27'
                                          * AVM 迎宾灯允许 0: Not Available 1： Available
                                          */
extern INT8U ExlMainOrDiAssistLightPrm;/* '<Root>/getAPI28'
                                        * 远光辅助或转向辅助 0:No Assist light 1:Enable Dirlight Assist 2:Enable Main Beam Assist 3:LIN control
                                        */
extern INT8U ExlEnOffAutoLightPrm;     /* '<Root>/getAPI29'
                                        * 自动灯光在 OFF（大灯开关） (预留) 0:Disable 1:Enable
                                        */
extern INT8U ExlEnAutoLightPrm;        /* '<Root>/getAPI30'
                                        * 自动灯光使能配置字，0:Disable 1:Enable
                                        */
extern INT8U SecHazardPeriodNumPrm;    /* '<Root>/getAPI31'
                                        * 触发报警后双闪灯闪烁的周期个数， 0:10-period 1-9: 1-9-period A: 0-period B-F: 11-15-period
                                        */
extern INT8U MstWelcomeLightPrm;       /* '<Root>/getAPI32'
                                        * 迎宾灯功能是否设置激活，0:Not active 1:Active
                                        */
extern INT8U MstAutoFollowMePrm;       /* '<Root>/getAPI33'
                                        * 自动伴我回家功能设置，0:OFF 1:10s 2:20s 3:30s
                                        */
extern INT8U MstLeaveMePrm;            /* '<Root>/getAPI34'
                                        * 伴我离家功能设置，0:OFF 1:10s 2:20s 3:30s
                                        */
extern INT8U MstEnWelcomeLightPrm;     /* '<Root>/getAPI35'
                                        * 迎宾灯功能设置网络使能位，0:Not active 1:Active
                                        */
extern INT8U MstEnFollowmeSetPrm;      /* '<Root>/getAPI36'
                                        * 自动伴我回家功能设置网络使能位，0:Not active 1:Active
                                        */
extern INT8U MstEnLeaveMeSetPrm;       /* '<Root>/getAPI37'
                                        * 伴我离家功能设置网络使能位，0:Not active 1:Active
                                        */
extern INT8U ExlBeamHeightPrm;         /* '<Root>/getAPI38'
                                        * 大灯高度调节档位设置，0x0: 0 0x1: 1 0x2: 2 0x3: 3
                                        */
extern INT8U ExlEnBeamHeightPrm;       /* '<Root>/getAPI39'
                                        * 大灯高度调节档位设置网络使能，0:Not active 1:Active
                                        */
extern INT8U MstHMAPrm;                /* '<Root>/getAPI40'
                                        * 远光 HMA 功能配置，0:Not active 1:Active
                                        */

/* Model entry point functions */
extern void Rte_get_Light_initialize(void);
extern void Rte_get_Light_step(void);

/* Real-time Model object */
extern RT_MODEL_Rte_get_Light_T *const Rte_get_Light_M;

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
 * '<Root>' : 'Rte_get_Light'
 */
#endif                                 /* RTW_HEADER_Rte_get_Light_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
