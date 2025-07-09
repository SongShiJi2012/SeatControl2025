#ifndef ADC_H
#define ADC_H
#include "Common.h"

#define ADC_MOTORD_POWER_LOW         (90UL)	//���ε����ѹ����	9V
#define ADC_MOTORD_POWER_HIGHT       (155UL)//���ε����ѹ����	15.5V
#define ADC_FIL_TIME_VOL_L       	 (25UL)	//�͵硢��ѹѹ����˲�ʱ�� 250MS
#define ADC_FIL_TIME_VOL_H       	 (25UL)	//��������˲�ʱ��


#define	PWR_A_9V_ADC		(1885UL)		/*POWER 9VADC�ɼ���ֵ��1885*/
#define	PWR_A_12V_ADC		(2485UL)		/*POWER 12VADC�ɼ���ֵ��2485*/

#define	PWR_A_V(Volt)		(200UL * Volt + 85)		/*�������*/

#define BUFF_SIZE		(10UL) /*���ɼ�����buff*/
#define HALL_BUFF_SIZE		(1UL) /*HALL�ɼ�����buff*/
#define SEMI_BUFF_SIZE		(5UL) /*5�βɼ�����buff*/
#define THREE_BUFF_SIZE		(3UL) /*���Ӿ������ɼ�����buff*/
#define SLEEP_BUFF_SIZE		(2UL) /*����ʱ���ɼ�����buff*/
#define AD_Threshold    (4096UL)/*12bitAD����*/



#if 1
#define First_Measure    (32UL) /*�״βɼ���ͨ����Χ*/
#define Second_Measure   (60UL) /*�ڶ��βɼ���ͨ����Χ*/
#define MEASURE_FIR    (31UL) /*�״βɼ���ͨ����Χ*/
#define MEASURE_SEC    (64UL) /*�ڶ��βɼ���ͨ����Χ*/
#define MEASURE_THI    (68UL) /*�����βɼ���ͨ����Χ*/

#endif

#if 0
#define First_Measure    (27UL) /*�״βɼ���ͨ����Χ*/
#define Second_Measure   (47UL) /*�ڶ��βɼ���ͨ����Χ*/
#define Tcond_Measure   (67UL) /*�ڶ��βɼ���ͨ����Χ*/
#endif



#define LowVol_Delay      (120UL)        //600ms
#define HighVol_Delay     (40UL)       //200ms

#define AD_Drift      (0UL)       //Power_A\B��Ư



#define ERR_OK           0U            /* OK */
#define ERR_RANGE        2U            /* Parameter out of range. */
#define ERR_OVERFLOW     4U            /* Timer overflow. */
#define ERR_BUSY         8U            /* Device is busy. */
#define ERR_NOTAVAIL     9U            /* Requested value or method not available. */

/* ADCͨ�� */
typedef enum
{
    enADC_DrHeightHallFB,            // ���ݸ߶Ȼ���������AD�죩
    enADC_DrLengthHallFB,            // �����������������AD�죩
    enADC_DrBackHallFB,              // ���ݿ�������������AD�죩
    enADC_DrFrontHallFB,             // ��������ǰ���ǶȻ���������AD�죩
    enADC_PaLengthHallFB,            // �����������������AD�죩
    enADC_PaBackHallFB,              // ���ݿ�������������AD�죩

    enADC_DrHeightMotorIS,           // ���ݸ߶ȵ��ڵ��������⣨AD�죩���ͱ߲ɼ���
    enADC_DrLengthMotorIS,           // ����������ڵ��������⣨AD�죩Ԥ��2 CS01���߲߱ɼ���
    enADC_DrBackMotorIS,             // ���ݿ������ڵ��������⣨AD�죩���ͱ߲ɼ���
    enADC_DrFrontMotorIS,            // ����ǰ���Ƕȵ��ڵ��������⣨AD�죩Ԥ��2 CS02���߲߱ɼ���
    enADC_PaLengthMotorIS,           // ����������ڵ��������⣨AD�죩Ԥ��1 CS01���߲߱ɼ���
    enADC_PaBackMotorIS,             // ���ݿ������ڵ��������⣨AD�죩Ԥ��1 CS02���߲߱ɼ���

    enADC_DrHeaterIS,                // ���ݼ��ȵ���������AD�죩
    enADC_PaHeaterIS,                // ���ݼ��ȵ���������AD�죩
    enADC_Heater3IS,                 // ����3&4������⣨AD�죩
    enADC_Heater4IS,                 // ����3&4������⣨AD�죩
    enADC_SteerHeaterIS,             // �����̼��ȵ���������AD�죩

    enADC_DrHeaterNTC,               // ���ݼ���NTC�ɼ���AD�죩��NTC1��
    enADC_PaHeaterNTC,               // ���ݼ���NCT�ɼ���AD�죩��NTC2��
    enADC_NTC3,                      // NTC3�ɼ���AD�죩
    enADC_NTC4,                      // NTC4�ɼ���AD�죩
    enADC_SteerHeaterNTC,            // �����̼���NTC�ɼ���AD�죩��NTC5��
    enADC_BoardNTC,                  // ���NTC�ɼ���AD�죩

    enADC_HallPowerFB,               // �������練����Ԥ������AD�죩
    enADC_MemoryAdjSw,               // ������ڿ��أ�Ԥ������AD�죩
    enADC_KL30Detect,                // KL30���
    enADC_MAx,                		 // ADCͨ����

} eADCCH;

/***********************************************************************************************
 * @description: ���� ADC ��ͨͨ������ת������
 ***********************************************************************************************/
#define D_ADC_MAX_CONTINUOUS_CHANNEL_NUM  (16u)  								/* ADC �������ת��ͨ���� */

#define D_ADC0_CONTINUOUS_CHANNEL_NUM     (6)  	/* ADC0 ����ת��ͨ���� - �����ɼ���ʱ��Ҫ�� ��Ҫ�����ɼ� */
#define D_ADC1_CONTINUOUS_CHANNEL_NUM     (D_ADC_MAX_CONTINUOUS_CHANNEL_NUM)  /* ADC1 ����ת��ͨ���� */
#define D_ADC2_CONTINUOUS_CHANNEL_NUM     (enADC_MAx - D_ADC0_CONTINUOUS_CHANNEL_NUM - D_ADC1_CONTINUOUS_CHANNEL_NUM)  /* ADC1 ����ת��ͨ���� */

/*ADģ��*/
typedef enum ADCX
{
	ADCx_0 = 0, /*ADC0*/
	ADCx_1, 	/*ADC1*/
	ADCx_2, 	/*ADC2*/
	ADCx_Max, 	/* */
}enADCx;

/*ADͨ��*/
typedef enum ADCXCHL
{
	Chl_0 = 0,
	Chl_1,
	Chl_2,
	Chl_3,
	Chl_4,
	Chl_5,
	Chl_6,
	Chl_7,
	Chl_8,
	Chl_9,
	Chl_10,
	Chl_11,
	Chl_12,
	Chl_13,
	Chl_14,
	Chl_15,
	Chl_16,
	Chl_17,
	Chl_18,
	Chl_19,
	Chl_20,
	Chl_21,
	Chl_22,
	Chl_23,
	Chl_24,
	Chl_25,
	Chl_26,
	Chl_27,
	Chl_28,
	Chl_29,
	Chl_30,
	Chl_31,
	Chl_32,
	Chl_33,
	Chl_34,
	Chl_35,
	Chl_36,
	Chl_37,
	Chl_38,
	Chl_39,
	Chl_40,
	Chl_41,
	Chl_42,
	Chl_43,
	Chl_44,
	Chl_45,
	Chl_46,
	Chl_47,
	Chl_48,
	Chl_49,
	Chl_50,
	Chl_51,
	Chl_52,
	Chl_53,
	Chl_54,
	Chl_55,
	Chl_56,
	Chl_57,
	Chl_58,
	Chl_59,
	Chl_60,
	Chl_61,
	Chl_62,
	Chl_63,
	Chl_64,
	Chl_65,
	Chl_66,
	Chl_67,
	Chl_68,
	Chl_69,
	Chl_70,
	Chl_71,
	Chl_72,
	Chl_73,
	Chl_74,
	Chl_75,
	Chl_76,
	Chl_77,
	Chl_78,
	Chl_79,
	Chl_80,
	Chl_81,
	Chl_82,
	Chl_83,
	Chl_84,
	Chl_85,
	Chl_86,
	Chl_87,
	Chl_88,
	Chl_89,
	Chl_90,
	Chl_91,
	Chl_92,
	Chl_93,
	Chl_94,
	Chl_95,
	Chl_96,
	Chl_97,
	Chl_98,
	Chl_99,
	Chl_100,
	Chl_101,
	Chl_102,
	Chl_103,
	Chl_104,
	Chl_105,
	Chl_106,
	Chl_107,
	Chl_108,
	Chl_109,
	Chl_110,
	Chl_111,
	Chl_112,
	Chl_113,
	Chl_114,
	Chl_115,
	Chl_116,
	Chl_117,
	Chl_118,
	Chl_119,
	Chl_120,
	Chl_121,
	Chl_122,
	Chl_123,
	Chl_124,
	Chl_125,
	Chl_126,
	Chl_127,
	Chl_Max
}enumADCxChl;

/*ͨ��ʹ�ܱ�ʶ*/
typedef enum ADCCHLSW
{
	ChlSw_OFF = 0, /*ͨ���ر�*/
	ChlSw_ON, /*ͨ����*/
}enADCChlSw;

/*ͨ���ɼ�����ʶ*/
typedef enum ADCCHLFULLSTA
{
	ChlFullSta_NO = 0, /*�ɼ�buffδ��*/
	ChlFullSta_OK, /*�ɼ�buff����*/
}enADCChlFullSta;

/*ͨ�������ʶ*/
typedef enum ADCCHLERRFLAG
{
	ChlErr_OK = 0, /*ͨ����������*/
	ChlErr_ERR, /*ͨ����������*/
}enADCChlErrFlag;

/*ADC����ͨ������*/
typedef struct ADCCHLMANAGE
{
	enADCx ADCx; /*��ӦӲ��ADģ��*/
	enumADCxChl ADCxChl; /*��ӦӲ��ADͨ��*/

	eADCCH ADCName; /*�ɼ�ͨ������*/
	enADCChlSw ChlSw; /*ͨ���Ƿ��������*/
	enADCChlFullSta ChlFullSta; /*ͨ������buff�Ƿ�����״̬*/

	INT8U SampleCycT; /*���ö��ٴβ���һ��,�ɼ�����=SampleCycT*��С����ʱ��*/
	INT8U SampleCycCnt; /*���ô����ƴ�*/
	
	INT8U SampleNum; /*��ɼ�����, <=BUFF_SIZE */
	INT8U SampleIndex; /*�ɼ��Ļ����������*/
	
	enADCChlErrFlag ErrorFlag; /*ͨ�������ʶ*/
	INT16U SampleBuffer[BUFF_SIZE]; /*�ɼ���AD����buffer*/

	void (*pFuncSwitchChl)(void);   /*��ͨ���л�*/

	BOOL    MesFinishFlg;             /*�������Flag*/
	INT16U  MesVal;                   /*����ֵ*/
}strADCChlManage;


extern INT8U Ecual_AD_MeasureChan(INT8U Channel, INT16U *pADValue);
extern void Ecual_AD_Step_Task(void);

extern BOOL Ecual_GetMesFinishFlg(eADCCH Chl);
extern void Ecual_SetMesFinishFlg(eADCCH Chl, BOOL Flg);
extern INT16U Ecual_GetAD_MesVal(eADCCH Chl);
extern void Ecual_AdcScanAll(void);
extern void Ecual_ADC_SoftwareStartConv(void);
extern INT16U Ecual_AdcGetChlStatus(eADCCH ADChl);
extern INT16U Ecual_AdcGetDrNTCTempValue(void);
extern INT16U Ecual_AdcGetPaNTCTempValue(void);
extern INT16U Ecual_AdcGetCenterNTCTempValue(void);
extern INT16U Ecual_ADC_GetCurrentBoardTemp(void);
extern void Ecual_ADC_Init(void);

extern void Ecual_SetDma0_Adc0_UpdateFlag(BOOL flag);
extern BOOL Ecual_GetDma0_Adc0_UpdateFlag(void);
extern void Ecual_SetDma1_Adc1_UpdateFlag(BOOL flag);
extern BOOL Ecual_GetDma1_Adc1_UpdateFlag(void);
extern BOOL Ecual_GetDma1_Adc2_UpdateFlag(void);
extern void Ecual_SetDma1_Adc2_UpdateFlag(BOOL flag);
extern void Ecual_SetAllAdcDmaUpdateFlag(void);
extern void Ecual_ClrAllAdcDmaUpdateFlag(void);
extern INT8U Ecual_AreAllAdcDmaUpdated(void);

extern void Ecual_ADC_Task(void);
extern void Ecual_Disable_AllAdcDma(void);
extern void Ecual_Enable_AllAdcDma(void);

#endif


