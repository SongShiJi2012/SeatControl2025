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
                                        * ��ƿ���״̬��0��OFF��1��λ�õƣ�2���Զ��ƣ�3������ƣ�ģ������
                                        */
extern INT8U TurnLampSw;               /* '<Root>/getAPI1'
                                        * ת�򿪹�״̬��OFF/Dir_Left/Dir_Right��ģ������
                                        */
extern INT8U HighBeamSw;               /* '<Root>/getAPI2'
                                        * Զ��ƿ��أ�OFF/HighBeam/Flash��ģ��㴥��NULL  (0u)��High  (1u)��Flash  (2u)
                                        */
extern INT8U HarzedLampSw;             /* '<Root>/getAPI3'
                                        * Σ�ձ�������״̬�����ֵ㴥����Чֵ��Low
                                        */
extern INT8U FogLampSw;                /* '<Root>/getAPI4'
                                        * ��ƿ��أ�OFF/Front Fog/Rear Fog��ģ��㴥
                                        */
extern INT8U ReverseLampSw;            /* '<Root>/getAPI5'
                                        * ����������״̬������������ ��Чֵ��Low
                                        */
extern INT8U BrakeLampSw;              /* '<Root>/getAPI6'
                                        * ɲ������״̬������������ ��Чֵ��high
                                        */
extern INT8U FL_DIR_Fault_Sts;         /* '<Root>/getAPI7'
                                        * ��ǰ LED ת��ƹ��Ϸ���״̬��������������Чֵ��high
                                        */
extern INT8U FR_DIR_Fault_Sts;         /* '<Root>/getAPI8'
                                        * ��ǰ LED ת��ƹ��Ϸ���״̬��������������Чֵ��high
                                        */
extern INT8U DriverDoorAjar;           /* '<Root>/getAPI9'
                                        * ˾����״̬��ģ��������Close/Open/Invalid�����庬��
                                        */
extern INT8U PassDoorAjar;             /* '<Root>/getAPI10'
                                        * ��˾����״̬��Close/Open/Invalid������������ ��Чֵ��Low
                                        */
extern INT8U RLeftDoorAjar;            /* '<Root>/getAPI11'
                                        * �����״̬������������ ��Чֵ��Low
                                        */
extern INT8U RRightDoorAjar;           /* '<Root>/getAPI12'
                                        * �Һ���״̬������������ ��Чֵ��Low
                                        */
extern INT8U TrunkDoorAjar;            /* '<Root>/getAPI13'
                                        * ������״̬������������ ��Чֵ��Low
                                        */
extern INT8U PowerMode;                /* '<Root>/getAPI14'
                                        * ��Դģʽ��0��OFF��1��ACC��2��ON��3��START
                                        */
extern INT8U VehOpModePrm;             /* '<Root>/getAPI15'
                                        * ��������ģʽ��Ĭ��ֵ��0�� 0���û�ģʽ 1������ģʽ�� 2������ģʽ�� 3��Ԥ��
                                        */
extern INT8U VehManufMaxTimPrm;        /* '<Root>/getAPI16'
                                        * ����������ģʽ���ʱ�����ã�Ĭ��ֵ��5��1 ��λΪһ���ӣ�ȡֵ��Χ��1~7
                                        */
extern INT8U VehManuOrAutoGearPrm;     /* '<Root>/getAPI17'
                                        * �Զ�/�ֶ����������ã� 0:Automatic gearbox with electronic gear shifter 1:Automatic gearbox with one-way solenoid 2:Automatic gearbox with two-way solenoid 3:Manual gearbox fitted
                                        */
extern INT8U VehEnFrontFogLampPrm;     /* '<Root>/getAPI18'
                                        * ǰ������ã�0:No Front Fog Lamps 1:Front Fog Lamps fitted
                                        */
extern INT8U VehEnDRLPrm;              /* '<Root>/getAPI19'
                                        * �ռ��г������ã�0:No DRL 1:Hardwired DRL 2:LIN DRL 3:Reserved
                                        */
extern INT8U ExlFrontDirLampsDiagtypePrm;/* '<Root>/getAPI20'
                                          * ǰת����������ã� 0:Halogen Direction lamp fitted 1:LED Direction lamp fitted 2:LIN Direction lamp fitted 3:Reserved
                                          */
extern INT8U VehLowBeamTypePrm;        /* '<Root>/getAPI21'
                                        * ��������ͣ� 0:Halogen Low Beam fitted 1:Xenon Low Beam fitted 2:LED Low Beam fitted 3:Seperate LIN controller
                                        */
extern INT8U VehHighBeamTypePrm;       /* '<Root>/getAPI22'
                                        * Զ������ͣ� 0:Halogen High Beam fitted 1:Xenon High Beam fitted 2:LED High Beam fitted 3:Seperate LIN controller 4:High Beam Solenoid fitted 5:Reserved
                                        */
extern INT8U ExlBeamHeightAdjustPrm;   /* '<Root>/getAPI23'
                                        * ��Ƹ߶ȵ��ڷ�ʽ 0:No Height Adjust Function 1:Harewire 2:LIN 3:Reserved
                                        */
extern INT8U ExlFPosLampsDiagtypePrm;  /* '<Root>/getAPI24'
                                        * ǰλ�õ����� 0:Halogen Position lamp fitted 1:LED Position lamp fitted 2:LIN Position lamp fitted 3:Reserved
                                        */
extern INT8U VehEnWelLampPrm;          /* '<Root>/getAPI25'
                                        * �Ƿ�����ӭ���� 0:No Welcome lamp 1:Welcome lamp fitted
                                        */
extern INT8U VehExLampSwTypePrm;       /* '<Root>/getAPI26'
                                        * ��ƿ������� 0:Hardwire switch 1:CAN signal switch 2:LIN signal switch 3:Reserved
                                        */
extern INT8U VehAVMWelcomeLightEnablePrm;/* '<Root>/getAPI27'
                                          * AVM ӭ�������� 0: Not Available 1�� Available
                                          */
extern INT8U ExlMainOrDiAssistLightPrm;/* '<Root>/getAPI28'
                                        * Զ�⸨����ת���� 0:No Assist light 1:Enable Dirlight Assist 2:Enable Main Beam Assist 3:LIN control
                                        */
extern INT8U ExlEnOffAutoLightPrm;     /* '<Root>/getAPI29'
                                        * �Զ��ƹ��� OFF����ƿ��أ� (Ԥ��) 0:Disable 1:Enable
                                        */
extern INT8U ExlEnAutoLightPrm;        /* '<Root>/getAPI30'
                                        * �Զ��ƹ�ʹ�������֣�0:Disable 1:Enable
                                        */
extern INT8U SecHazardPeriodNumPrm;    /* '<Root>/getAPI31'
                                        * ����������˫������˸�����ڸ����� 0:10-period 1-9: 1-9-period A: 0-period B-F: 11-15-period
                                        */
extern INT8U MstWelcomeLightPrm;       /* '<Root>/getAPI32'
                                        * ӭ���ƹ����Ƿ����ü��0:Not active 1:Active
                                        */
extern INT8U MstAutoFollowMePrm;       /* '<Root>/getAPI33'
                                        * �Զ����һؼҹ������ã�0:OFF 1:10s 2:20s 3:30s
                                        */
extern INT8U MstLeaveMePrm;            /* '<Root>/getAPI34'
                                        * ������ҹ������ã�0:OFF 1:10s 2:20s 3:30s
                                        */
extern INT8U MstEnWelcomeLightPrm;     /* '<Root>/getAPI35'
                                        * ӭ���ƹ�����������ʹ��λ��0:Not active 1:Active
                                        */
extern INT8U MstEnFollowmeSetPrm;      /* '<Root>/getAPI36'
                                        * �Զ����һؼҹ�����������ʹ��λ��0:Not active 1:Active
                                        */
extern INT8U MstEnLeaveMeSetPrm;       /* '<Root>/getAPI37'
                                        * ������ҹ�����������ʹ��λ��0:Not active 1:Active
                                        */
extern INT8U ExlBeamHeightPrm;         /* '<Root>/getAPI38'
                                        * ��Ƹ߶ȵ��ڵ�λ���ã�0x0: 0 0x1: 1 0x2: 2 0x3: 3
                                        */
extern INT8U ExlEnBeamHeightPrm;       /* '<Root>/getAPI39'
                                        * ��Ƹ߶ȵ��ڵ�λ��������ʹ�ܣ�0:Not active 1:Active
                                        */
extern INT8U MstHMAPrm;                /* '<Root>/getAPI40'
                                        * Զ�� HMA �������ã�0:Not active 1:Active
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
