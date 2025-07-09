#include "system_init.h"
#include "hal_adc.h"
#include "adc_driver.h"

//��������
static UINT32 Hal_AdConvertStragy_1(UINT32 uAdValue);
static UINT32 Hal_AdConvertStragy_2(UINT32 uAdValue);
static UINT32 Hal_AdConvertStragy_3(UINT32 uAdValue);
BOOL Hal_AdcInit(AdcInstanceModuleNum_e AdcModuleNum);

//��������
AdcCommManage_t G_AdcCommManage;

/*ADC�ײ���س�ʼ��*/
BOOL Hal_AdcInit(AdcInstanceModuleNum_e AdcModuleNum)
{
	UINT32 instance = AdcModuleNum;

	ADC_DRV_AdcInit(instance);

	return TRUE;
}


/*��ȡĳ��ͨ��ADֵ,�����ʹ�ö�β������ԣ��򷵻����µ�һ��ADֵ*/
BOOL Hal_GetChannelAdValue(AppAdcFunctionChanel_e uChannel,UINT32 * pAdValue)
{
		if((uChannel >= ADC_DET_MAX)||(G_AdcCommManage.Inited == FALSE)||(pAdValue ==NULL))
	{
		return FALSE;
	}

	if(G_AdcCommManage.Channel[uChannel].AdCnt>0)
	{
		*pAdValue = G_AdcCommManage.Channel[uChannel].AdValue[G_AdcCommManage.Channel[uChannel].AdCnt-1];
		return TRUE;
	}

	return FALSE;
}

void Hal_AdcInitEx(void)
{
	/*ADC0 module configuration*/
	Hal_AdcInit(INST_ADC_0);
	//Hal_AdcInit(INST_ADC_1);

	memset(&G_AdcCommManage,0,sizeof(G_AdcCommManage));
	G_AdcCommManage.Inited = TRUE;
}

void Hal_AdcDeInit(uint32_t instance)
{
	 ADC_DRV_AdcDeInit(instance);
}

