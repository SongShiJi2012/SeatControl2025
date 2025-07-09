/*******************************************************************************
 *  $File Name$       : adc_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "adc_driver.h"
#include <string.h>
#include "kf32a156_int.h"
#include "system_init.h"

/* Table of base addresses for ADC instances. */
static ADC_SFRmap * const s_adcBase[ADC_INSTANCE_COUNT] = ADC_BASE_PTRS;
static uint16_t const s_adcInt[ADCINT_INSTANCE_COUNT] = ADC_INT_PTRS;

static ADC_InitTypeDef ADC_InitStructure;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void ADC_DRV_StructInit (ADC_InitTypeDef* adcInitStruct);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_RegularChannelConfig
 * Description   :
 *
 *END**************************************************************************/
void ADC_DRV_RegularChannelConfig (const	uint32_t instance, const uint32_t channel)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	ADC_Regular_Channel_Config(base, channel, 01);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_SoftwareStartConv
 * Description   :
 *
 *END**************************************************************************/
void ADC_DRV_SoftwareStartConv(const uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	ADC_Software_Start_Conv(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_GetConvCompleteFlag
 * Description   :
 *
 *END**************************************************************************/
bool ADC_DRV_GetConvCompleteFlag(const uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	return (ADC_Get_INT_Flag(base, ADC_INT_EOC));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_GetConversionValue
 * Description   :
 *
 *END**************************************************************************/
uint16_t ADC_DRV_GetConversionValue (const uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	return (ADC_Get_Conversion_Value(base));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_StructInit
 * Description   :
 *
 *END**************************************************************************/
static void ADC_DRV_StructInit (ADC_InitTypeDef* adcInitStruct)
{
    /* ��ʼ�� ADCʱ��Դѡ�� */
    adcInitStruct->m_Clock = ADC_SCLK;

    /* ��ʼ�� ADCʱ�ӷ�Ƶ */
    adcInitStruct->m_ClockDiv = ADC_CLK_DIV_2;

    /* ��ʼ�� ADCɨ��ģʽʹ�� */
    adcInitStruct->m_ScanMode = FALSE;

    /* ��ʼ�� ADC����ת��ģʽ */
    adcInitStruct->m_ContinuousMode = ADC_SINGLE_MODE;

    /* ��ʼ�� ADCת����������ʽ */
    adcInitStruct->m_DataAlign = ADC_DATAALIGN_LEFT;

    /* ��ʼ�� ADC����ͨ���ⲿ����ת��ģʽʹ�� */
    adcInitStruct->m_ExternalTrig_EN = FALSE;

    /* ��ʼ�� ADC����ͨ���ⲿ�����¼� */
    adcInitStruct->m_ExternalTrig = ADC_EXTERNALTRIG_CCP1_CH1;

    /* ��ʼ�� ADC�����ȼ�ͨ���ⲿ����ת��ģʽʹ�� */
    adcInitStruct->m_HPExternalTrig_EN = FALSE;

    /* ��ʼ�� �����ȼ�ͨ���ⲿ�����¼� */
    adcInitStruct->m_HPExternalTrig = ADC_HPEXTERNALTRIG_CCP1_CH1;

    /* ��ʼ�� ADC�ο���ѹѡ�� */
    adcInitStruct->m_VoltageRef = ADC_REF_AVDD;

    /* ��ʼ�� ADC����ͨ��ɨ�賤�� */
    adcInitStruct->m_NumOfConv = 1;

    /* ��ʼ�� ADC�����ȼ�ͨ��ɨ�賤�� */
    adcInitStruct->m_NumOfHPConv = 1;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_AdcInit
 * Description   :
 *
 *END**************************************************************************/
void ADC_DRV_AdcInit(const uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];
	uint16_t Int = s_adcInt[instance];

	/*reset ADC0 module,enable ADC0 clock source******************************/
	ADC_Reset (base);
	ADC_DRV_StructInit(&ADC_InitStructure);
	/*select HFCLK as the ADC0 sampling clock source***************************
	**You can also select SCLK or LFCLK as the ADC0 sampling clock************/
	ADC_InitStructure.m_Clock = ADC_HFCLK;   /*16M*/
	/*ADC sampling clock Divider configuration********************************/
	ADC_InitStructure.m_ClockDiv = ADC_CLK_DIV_2;
	/*disable adc scan mode***************************************************/
	ADC_InitStructure.m_ScanMode = FALSE;
	/*select single adc sampling mode ****************************************/
	ADC_InitStructure.m_ContinuousMode = ADC_SINGLE_MODE;//
	/*Right-aligned sampling result data *************************************/
	ADC_InitStructure.m_DataAlign = ADC_DATAALIGN_RIGHT;
	/*disable External trigger************************************************/
	ADC_InitStructure.m_ExternalTrig_EN = FALSE;
	/*select Vdd as ADC refrence voltage**************************************/
	ADC_InitStructure.m_VoltageRef = ADC_REF_VREF;

	ADC_Configuration (base, &ADC_InitStructure);
	ADC_Cmd (base, TRUE);
	systick_delay_ms(5); /*��ʼ��������ӳ�5ms*/
	//ADC_Set_INT_Enable (base,ADC_INT_HPEND, TRUE);
	//INT_Interrupt_Priority_Config(Int,1,0);//��ռ���ȼ�1,�����ȼ�0
	//INT_Clear_Interrupt_Flag(Int);//���жϱ�־
	//INT_Interrupt_Enable(Int,TRUE);//�����ж�ʹ��
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_GetADC0Value
 * Description   :
 *
 *END**************************************************************************/
uint16_t ADC_DRV_TestGetADC0Value(void)//�������βɼ�test
{
	/*wait for the adc conversion to complete*/
	while(!ADC_Get_INT_Flag(ADC0_SFR,ADC_INT_EOC));

	ADC_Regular_Channel_Config(ADC0_SFR,ADC_CHANNEL_2,01);
	/*software triger adc Conversion*/
	ADC_Software_Start_Conv(ADC0_SFR);
	/*wait for the adc conversion to complete*/
	while(!ADC_Get_INT_Flag(ADC0_SFR,ADC_INT_EOC));

	return 0;
}



void ADC_DRV_AdcDeInit(uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	ADC_Cmd(base,FALSE);
	memset(base,0,sizeof(ADC_SFRmap));
	memset(&ADC_InitStructure,0,sizeof(ADC_InitTypeDef));
	ADC_Configuration (base, &ADC_InitStructure);

	//ADC_Reset(base);
}


uint16_t ADC_DRV_TestADCValue(uint8_t instance ,uint8_t Channel)//�������βɼ�test
{
	uint16_t dat1;
	ADC_SFRmap * const base = s_adcBase[instance];

	/*wait for the adc conversion to complete*/
//	while(!ADC_Get_INT_Flag(base,ADC_INT_EOC));

	ADC_Regular_Channel_Config(base,Channel,01);
	/*software triger adc Conversion*/
	ADC_Software_Start_Conv(base);
	/*wait for the adc conversion to complete*/
	while(!ADC_Get_INT_Flag(base,ADC_INT_EOC));

	dat1 = ADC_Get_Conversion_Value(base);
	return dat1;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
