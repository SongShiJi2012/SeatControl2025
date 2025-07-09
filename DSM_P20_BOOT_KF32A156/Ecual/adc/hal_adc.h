
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

#define  ADC_MAX_MULTIPLE_TIMES	(6U)		/*��β��������Ĳ�������*/
#define  ADC_VREF_VOLT			(3300u)		/*ADC�ο���ѹ3.3V*/
#define  ADC_BITS				(12)		/*12λADC*/

#define  AD_CONVERT_VOLT(AdValue)      ((AdValue*ADC_VREF_VOLT)>>ADC_BITS)		/*��ADֵת��Ϊ����˿ڵ�ѹ����λΪ��mv*/

typedef enum _ADC_INST_MODULE_NUM_
{
	INST_ADC_0= 0u,
    INST_ADC_1,
    INST_ADC_MAX,
}AdcInstanceModuleNum_e;

typedef enum
{
	//ADCͨ����� 0-127
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
	BAT1_VOLT_DET=0,	/*��Դ1��ѹ���*/
	BAT2_VOLT_DET,		/*��Դ2��ѹ���*/
	SSB_SW1_DET,		/*SSB1 ��ѹ���*/
	SSB_SW2_DET,		/*SSB2 ��ѹ���*/
	IGN1_IN_DET,		/*IGN1 ��ѹ���*/
	NTC_DET,			/*�¶ȼ�⣬Ԥ��*/
	TP_DIG_DET,			/*�Ű�����ϼ��*/
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
	OPT_ONE_TIME,			/*�ɼ�1��,�ɼ����Զ�ֹͣ*/
	OPT_MULTIPLE_TIMES,		/*�ɼ����*���ɼ����Զ�ֹͣ*/
	OPT_CONTINUE,			/*��������*/
	OPT_MULTIPLE_TIMES_CONTINUE,		/*����������ÿ�βɼ����ֵ*/
	OPT_MAX
}AdcOptType;

typedef struct _ADC_CONVET_STRATEGY_T
{
	AdcOptType 	OptType;
	uint8_t 	Times;		/*�ɼ����� ֻ�Բɼ�������ã��������Ϳɲ��䣬���ֵΪ ADC_MAX_MULTIPLE_TIMES*/
}AdcConvertStragy_t;

typedef struct _ADC_CHANNEL_OPT_CONFIG_T
{
	BOOL		IsUsed;
	AdcOptType 	OptType;
	uint16_t	Times;
	pAdcCallFunc	Cb;
	BOOL        StopChannel;
	uint8_t		AdCnt;									/*��ǰ�Ѿ���������*/
	uint16_t		AdValue[ADC_MAX_MULTIPLE_TIMES];		/*�������������Ƿ� ʹ�ö�̬�����ڴ�*/
}AdcChannelOptConfig_t;

typedef struct _ADC_COMM_MANAGE_T
{
	BOOL		Inited;					/*�Ƿ��ѳ�ʼ��*/	
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
