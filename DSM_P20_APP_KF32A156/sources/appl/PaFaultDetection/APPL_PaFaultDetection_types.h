/*
 * File: APPL_PaFaultDetection_types.h
 *
 * Code generated for Simulink model 'APPL_PaFaultDetection'.
 *
 * Model version                  : 1.276
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed May  5 15:26:47 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Renesas->RH850
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_APPL_PaFaultDetection_types_h_
#define RTW_HEADER_APPL_PaFaultDetection_types_h_
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
typedef struct tag_RTM_APPL_PaFaultDetection_T RT_MODEL_APPL_PaFaultDetection_T;

#endif                                 /* RTW_HEADER_APPL_PaFaultDetection_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
