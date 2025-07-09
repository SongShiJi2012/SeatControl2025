
/**************************************************************
 * Author:			 JeanYuan
 * Copyright (c) 2013-2019 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved. 
 *	generated :2020-09-07
 **************************************************************/

#ifndef HAL_ADC_H
#define HAL_ADC_H

//#include "system_init.h"
//#include "osif_common.h"
#include "types.h"

typedef void (*pAdcCallFunc)(UINT8 uChannel,UINT16 uSampleNum, UINT16 uSample[]);
typedef uint32_t (*pAdConvertStragy)(UINT32 uAdValue);

#define  ADC_MAX_MULTIPLE_TIMES	(6U)		/*多次采样，最大的采样个数*/
#define  ADC_VREF_VOLT			(3300u)		/*ADC参考电压3.3V*/
#define  ADC_BITS				(12)		/*12位ADC*/

#define  AD_CONVERT_VOLT(AdValue)      ((AdValue*ADC_VREF_VOLT)>>ADC_BITS)		/*将AD值转换为输入端口电压，单位为：mv*/

typedef enum _ADC_INST_MODULE_NUM_
{
	INST_ADC_0= 0u,
    INST_ADC_1,
    INST_ADC_MAX,
}AdcInstanceModuleNum_e;

typedef enum
{
	//ADC通道编号 0-127
	ADC_CHANNEL0 = 0,
	ADC_CHANNEL1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
	ADC_CHANNEL8,
	ADC_CHANNEL9,
	ADC_CHANNEL10,

	ADC_CHANNEL_INVALID_MAX = 128,
}adc_inputchannel_t;

typedef enum _ADC_APP_FUNC_CHAN_NUM_
{
	BAT1_VOLT_DET=0,	/*电源1电压检测*/
	BAT2_VOLT_DET,		/*电源2电压检测*/
	SSB_SW1_DET,		/*SSB1 电压检测*/
	SSB_SW2_DET,		/*SSB2 电压检测*/
	IGN1_IN_DET,		/*IGN1 电压检测*/
	NTC_DET,			/*温度检测，预留*/
	TP_DIG_DET,			/*门把手诊断检测*/
	ADC_DET_MAX,
}AppAdcFunctionChanel_e;

typedef struct _ADC_COMM_CONFIG_T
{
	AppAdcFunctionChanel_e	FuncChanel;
	AdcInstanceModuleNum_e	ModuleNum;
	adc_inputchannel_t		InputChanel;
	pAdConvertStragy		ConvertStragy;
}AdcCommConfig_t;

typedef enum _ADC_OPT_TYPE_T
{
	OPT_ONE_TIME,			/*采集1次,采集完自动停止*/
	OPT_MULTIPLE_TIMES,		/*采集多次*，采集完自动停止*/
	OPT_CONTINUE,			/*持续采样*/
	OPT_MULTIPLE_TIMES_CONTINUE,		/*持续采样，每次采集多个值*/
	OPT_MAX
}AdcOptType;

typedef struct _ADC_CONVET_STRATEGY_T
{
	AdcOptType 	OptType;
	uint8_t 	Times;		/*采集次数 只对采集多次配置，其他类型可不配，最大值为 ADC_MAX_MULTIPLE_TIMES*/
}AdcConvertStragy_t;

typedef struct _ADC_CHANNEL_OPT_CONFIG_T
{
	BOOL		IsUsed;
	AdcOptType 	OptType;
	uint16_t	Times;
	pAdcCallFunc	Cb;
	BOOL        StopChannel;
	uint8_t		AdCnt;									/*当前已经采样个数*/
	uint16_t		AdValue[ADC_MAX_MULTIPLE_TIMES];		/*后续根据需求看是否 使用动态分配内存*/
}AdcChannelOptConfig_t;

typedef struct _ADC_COMM_MANAGE_T
{
	BOOL		Inited;					/*是否已初始化*/	
	AdcChannelOptConfig_t 	Channel[ADC_DET_MAX];
}AdcCommManage_t;

extern BOOL Hal_AdcInit(AdcInstanceModuleNum_e AdcModuleNum);
extern BOOL Hal_StartAdcChannel(AppAdcFunctionChanel_e uChannel, AdcConvertStragy_t *uStragety, pAdcCallFunc uCb);
extern BOOL Hal_StopAdcChannel(AppAdcFunctionChanel_e uChannel);
extern uint16_t Hal_AdcGetValBlocking(AppAdcFunctionChanel_e uChannel);
extern void Hal_AdcTask(void);
extern uint32_t	Hal_AdConvertVolt(AppAdcFunctionChanel_e uChannel, uint32_t uAdValue);
extern BOOL Hal_GetChannelAdValue(AppAdcFunctionChanel_e uChannel, uint32_t * pAdValue);
extern void Hal_AdcInitEx(void);
extern void Hal_AdcDeInit(uint32_t instance);

#endif
