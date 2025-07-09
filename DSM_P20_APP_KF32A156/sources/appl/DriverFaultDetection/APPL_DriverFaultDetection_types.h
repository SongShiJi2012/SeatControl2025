/*
 * File: APPL_DriverFaultDetection_types.h
 *
 * Code generated for Simulink model 'APPL_DriverFaultDetection'.
 *
 * Model version                  : 1.321
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Jun  3 19:20:38 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_APPL_DriverFaultDetection_types_h_
#define RTW_HEADER_APPL_DriverFaultDetection_types_h_
#ifndef DEFINED_TYPEDEF_FOR_enSeatMoveCmd_
#define DEFINED_TYPEDEF_FOR_enSeatMoveCmd_

/* 电机控制命令&#10;0 : 无命令&#10;1 : 向上/向前&#10;2 : 向下/向后, */
typedef enum
{
  enSeatMoveCmd_EN_NULL = 0,           /* Default value */
  enSeatMoveCmd_EN_UP_FORWARD,
  enSeatMoveCmd_EN_DN_BACKWARD
}
enSeatMoveCmd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enDrAdjustEnable_
#define DEFINED_TYPEDEF_FOR_enDrAdjustEnable_

/* 主驾座椅调用调节配置：&#10;0x00:manual &#10;0x01:Six way motor &#10;0x02:Twelve way motor, */
typedef enum
{
  enDrAdjustEnable_EN_DrManual = 0,
  enDrAdjustEnable_EN_DrSixWayMotor,
  enDrAdjustEnable_EN_DrTwelveWayMotor /* Default value */
}
enDrAdjustEnable;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enIgnSts_
#define DEFINED_TYPEDEF_FOR_enIgnSts_

/* IGN电源档位状态&#10;0：OFF&#10;1：ACC&#10;2：ON&#10;3：CRANK&#10;4：RUN, */
typedef enum
{
  enIgnSts_eOff = 0,                   /* Default value */
  enIgnSts_eAcc,
  enIgnSts_eOn,
  enIgnSts_eCrank,
  enIgnSts_eRun
}
enIgnSts;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_APPL_DriverFaultDetection_T
  RT_MODEL_APPL_DriverFaultDetection_T;

#endif                                 /* RTW_HEADER_APPL_DriverFaultDetection_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
