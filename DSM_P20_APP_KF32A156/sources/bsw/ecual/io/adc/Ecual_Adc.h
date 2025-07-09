#ifndef ADC_H
#define ADC_H
#include "Common.h"

#define ADC_MOTORD_POWER_LOW         (90UL)	//座椅电机电压限制	9V
#define ADC_MOTORD_POWER_HIGHT       (155UL)//座椅电机电压限制	15.5V
#define ADC_FIL_TIME_VOL_L       	 (25UL)	//低电、高压压检测滤波时间 250MS
#define ADC_FIL_TIME_VOL_H       	 (25UL)	//正常检测滤波时间


#define	PWR_A_9V_ADC		(1885UL)		/*POWER 9VADC采集的值是1885*/
#define	PWR_A_12V_ADC		(2485UL)		/*POWER 12VADC采集的值是2485*/

#define	PWR_A_V(Volt)		(200UL * Volt + 85)		/*换算比例*/

#define BUFF_SIZE		(10UL) /*最大采集数据buff*/
#define HALL_BUFF_SIZE		(1UL) /*HALL采集数据buff*/
#define SEMI_BUFF_SIZE		(5UL) /*5次采集数据buff*/
#define THREE_BUFF_SIZE		(3UL) /*后视镜霍尔采集数据buff*/
#define SLEEP_BUFF_SIZE		(2UL) /*休眠时最大采集数据buff*/
#define AD_Threshold    (4096UL)/*12bitAD精度*/



#if 1
#define First_Measure    (32UL) /*首次采集的通道范围*/
#define Second_Measure   (60UL) /*第二次采集的通道范围*/
#define MEASURE_FIR    (31UL) /*首次采集的通道范围*/
#define MEASURE_SEC    (64UL) /*第二次采集的通道范围*/
#define MEASURE_THI    (68UL) /*第三次采集的通道范围*/

#endif

#if 0
#define First_Measure    (27UL) /*首次采集的通道范围*/
#define Second_Measure   (47UL) /*第二次采集的通道范围*/
#define Tcond_Measure   (67UL) /*第二次采集的通道范围*/
#endif



#define LowVol_Delay      (120UL)        //600ms
#define HighVol_Delay     (40UL)       //200ms

#define AD_Drift      (0UL)       //Power_A\B零漂



#define ERR_OK           0U            /* OK */
#define ERR_RANGE        2U            /* Parameter out of range. */
#define ERR_OVERFLOW     4U            /* Timer overflow. */
#define ERR_BUSY         8U            /* Device is busy. */
#define ERR_NOTAVAIL     9U            /* Requested value or method not available. */

/* ADC通道 */
typedef enum
{
    enADC_DrHeightHallFB,            // 主驾高度霍尔反馈（AD检）
    enADC_DrLengthHallFB,            // 主驾纵向霍尔反馈（AD检）
    enADC_DrBackHallFB,              // 主驾靠背霍尔反馈（AD检）
    enADC_DrFrontHallFB,             // 主驾坐垫前部角度霍尔反馈（AD检）
    enADC_PaLengthHallFB,            // 副驾纵向霍尔反馈（AD检）
    enADC_PaBackHallFB,              // 副驾靠背霍尔反馈（AD检）

    enADC_DrHeightMotorIS,           // 主驾高度调节电机电流检测（AD检）【低边采集】
    enADC_DrLengthMotorIS,           // 主驾纵向调节电机电流检测（AD检）预驱2 CS01【高边采集】
    enADC_DrBackMotorIS,             // 主驾靠背调节电机电流检测（AD检）【低边采集】
    enADC_DrFrontMotorIS,            // 主驾前部角度调节电机电流检测（AD检）预驱2 CS02【高边采集】
    enADC_PaLengthMotorIS,           // 副驾纵向调节电机电流检测（AD检）预驱1 CS01【高边采集】
    enADC_PaBackMotorIS,             // 副驾靠背调节电机电流检测（AD检）预驱1 CS02【高边采集】

    enADC_DrHeaterIS,                // 主驾加热电流反馈（AD检）
    enADC_PaHeaterIS,                // 副驾加热电流反馈（AD检）
    enADC_Heater3IS,                 // 加热3&4电流检测（AD检）
    enADC_Heater4IS,                 // 加热3&4电流检测（AD检）
    enADC_SteerHeaterIS,             // 方向盘加热电流反馈（AD检）

    enADC_DrHeaterNTC,               // 主驾加热NTC采集（AD检）【NTC1】
    enADC_PaHeaterNTC,               // 副驾加热NCT采集（AD检）【NTC2】
    enADC_NTC3,                      // NTC3采集（AD检）
    enADC_NTC4,                      // NTC4采集（AD检）
    enADC_SteerHeaterNTC,            // 方向盘加热NTC采集（AD检）【NTC5】
    enADC_BoardNTC,                  // 板端NTC采集（AD检）

    enADC_HallPowerFB,               // 霍尔供电反馈（预留）（AD检）
    enADC_MemoryAdjSw,               // 记忆调节开关（预留）（AD检）
    enADC_KL30Detect,                // KL30检测
    enADC_MAx,                		 // ADC通道数

} eADCCH;

/***********************************************************************************************
 * @description: 定义 ADC 普通通道连续转换道数
 ***********************************************************************************************/
#define D_ADC_MAX_CONTINUOUS_CHANNEL_NUM  (16u)  								/* ADC 最大连续转换通道数 */

#define D_ADC0_CONTINUOUS_CHANNEL_NUM     (6)  	/* ADC0 连续转换通道数 - 霍尔采集有时间要求 需要单独采集 */
#define D_ADC1_CONTINUOUS_CHANNEL_NUM     (D_ADC_MAX_CONTINUOUS_CHANNEL_NUM)  /* ADC1 连续转换通道数 */
#define D_ADC2_CONTINUOUS_CHANNEL_NUM     (enADC_MAx - D_ADC0_CONTINUOUS_CHANNEL_NUM - D_ADC1_CONTINUOUS_CHANNEL_NUM)  /* ADC1 连续转换通道数 */

/*AD模块*/
typedef enum ADCX
{
	ADCx_0 = 0, /*ADC0*/
	ADCx_1, 	/*ADC1*/
	ADCx_2, 	/*ADC2*/
	ADCx_Max, 	/* */
}enADCx;

/*AD通道*/
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

/*通道使能标识*/
typedef enum ADCCHLSW
{
	ChlSw_OFF = 0, /*通道关闭*/
	ChlSw_ON, /*通道打开*/
}enADCChlSw;

/*通道采集满标识*/
typedef enum ADCCHLFULLSTA
{
	ChlFullSta_NO = 0, /*采集buff未满*/
	ChlFullSta_OK, /*采集buff已满*/
}enADCChlFullSta;

/*通道错误标识*/
typedef enum ADCCHLERRFLAG
{
	ChlErr_OK = 0, /*通道采样正常*/
	ChlErr_ERR, /*通道采样错误*/
}enADCChlErrFlag;

/*ADC采样通道管理*/
typedef struct ADCCHLMANAGE
{
	enADCx ADCx; /*对应硬件AD模块*/
	enumADCxChl ADCxChl; /*对应硬件AD通道*/

	eADCCH ADCName; /*采集通道名称*/
	enADCChlSw ChlSw; /*通道是否采样开关*/
	enADCChlFullSta ChlFullSta; /*通道采样buff是否已满状态*/

	INT8U SampleCycT; /*调用多少次采样一次,采集周期=SampleCycT*最小调用时间*/
	INT8U SampleCycCnt; /*调用次数计次*/
	
	INT8U SampleNum; /*需采集次数, <=BUFF_SIZE */
	INT8U SampleIndex; /*采集的缓存的下坐标*/
	
	enADCChlErrFlag ErrorFlag; /*通道错误标识*/
	INT16U SampleBuffer[BUFF_SIZE]; /*采集的AD缓存buffer*/

	void (*pFuncSwitchChl)(void);   /*多通道切换*/

	BOOL    MesFinishFlg;             /*测量完成Flag*/
	INT16U  MesVal;                   /*测量值*/
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


