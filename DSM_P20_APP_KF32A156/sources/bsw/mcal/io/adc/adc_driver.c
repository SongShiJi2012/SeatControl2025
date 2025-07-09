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
static void ADC_Struct_Init(ADC_InitTypeDef *adcInitStruct);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_RegularChannelConfig
 * Description   :
 *
 *END**************************************************************************/
void ADC_DRV_RegularChannelConfig(const uint32_t instance, const uint32_t channel, uint32_t Rank)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	Rank = Rank + 1;/* Rank �� 1 ��ʼ */

	ADC_Regular_Channel_Config(base, channel, Rank);
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

void ADC_DRV_AdcDeInit(uint32_t instance)
{
	ADC_SFRmap * const base = s_adcBase[instance];

	ADC_Cmd(base,FALSE);
	memset(base,0,sizeof(ADC_SFRmap));
	memset(&ADC_InitStructure,0,sizeof(ADC_InitTypeDef));
	ADC_Configuration (base, &ADC_InitStructure);

	//ADC_Reset(base);
}

/**
 *  @brief : ��ʼ��ADC���ýṹ��
 *  @param[in]  adcInitStruct: ����ʼ���Ľṹ��ָ��
 *  @param[out] ��
 *  @retval : ��
 */
static void ADC_Struct_Init(ADC_InitTypeDef *adcInitStruct)
{
    /* ADCʱ��Դѡ�� */
    adcInitStruct->m_Clock = ADC_SCLK;

    /* ADCʱ�ӷ�Ƶ */
    adcInitStruct->m_ClockDiv = ADC_CLK_DIV_2;

    /* �ر�ADCɨ��ģʽ */
    adcInitStruct->m_ScanMode = FALSE;

    /* ����Ϊ����ת��ģʽ */
    adcInitStruct->m_ContinuousMode = ADC_SINGLE_MODE;

    /* ADCת������Ҷ��� */
    adcInitStruct->m_DataAlign = ADC_DATAALIGN_RIGHT;

    /* ��ֹ����ͨ���ⲿ���� */
    adcInitStruct->m_ExternalTrig_EN = FALSE;

    /* �ⲿ����Դ */
    adcInitStruct->m_ExternalTrig = ADC_EXTERNALTRIG_CCP1_CH1;

    /* ��ֹ�����ȼ�ͨ���ⲿ���� */
    adcInitStruct->m_HPExternalTrig_EN = FALSE;

    /* �����ȼ��ⲿ����Դ */
    adcInitStruct->m_HPExternalTrig = ADC_HPEXTERNALTRIG_CCP1_CH1;

    /* ADC�ο���ѹѡ�� */
    adcInitStruct->m_VoltageRef = ADC_REF_AVDD;

    /* ����ͨ��ɨ�賤�� */
    adcInitStruct->m_NumOfConv = 1;

    /* �����ȼ�ͨ��ɨ�賤�� */
    adcInitStruct->m_NumOfHPConv = 1;
}

/***********************************************************************************************
 * @function name:  ADC_DRV_Adc0InitScanMode
 * @description:    ��ʼ�� ADC0 ɨ��ģʽ�����ò���ʱ�ӡ�ɨ��ͨ�������ο���ѹ�Ȳ�����
 * @input parameters: ScanNumber - Ҫɨ���ͨ������
 * @output parameters: None
 * @return:         None
 * @note:           ���� ADC �����ӳ���ȷ���ȶ�����ʱ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void ADC_DRV_InitScanMode(ADC_SFRmap *ADCx, uint8_t ScanNumber)
{
    ADC_InitTypeDef ADC_InitStructure;

    /* ��λ ADC ģ�飬���� ADC ʱ�� */
    ADC_Reset(ADCx);

    /* ��ʼ�� ADC ������Ϣ�ṹ�� */
    ADC_Struct_Init(&ADC_InitStructure);
    /* ѡ�� HFCLK ��Ϊ ADC ����ʱ��Դ */
    ADC_InitStructure.m_Clock = ADC_HFCLK;
    /* ���� ADC ����ʱ�ӷ�Ƶϵ�� */
    ADC_InitStructure.m_ClockDiv = ADC_CLK_DIV_16;
    /* ʹ�� ADC ɨ��ģʽ */
    ADC_InitStructure.m_ScanMode = TRUE;
    /* ѡ�񵥴�ת��ģʽ��Ϊ ADC ת��ģʽ */
    ADC_InitStructure.m_ContinuousMode = ADC_SINGLE_MODE;
    /* ��������Ҷ��� */
    ADC_InitStructure.m_DataAlign = ADC_DATAALIGN_RIGHT;
    /* �����ⲿ���� */
    ADC_InitStructure.m_ExternalTrig_EN = FALSE;
    /* �ⲿ����Դ���ò�����Ҫ */
    /* ѡ�� Vdd ��Ϊ ADC �ο���ѹ */
    ADC_InitStructure.m_VoltageRef = ADC_REF_AVDD;
    /* ���ó���ͨ��ɨ�賤�� */
    ADC_InitStructure.m_NumOfConv = ScanNumber;
    /* ��ʼ������ ADC ģ�� */
    ADC_Configuration(ADCx, &ADC_InitStructure);

    /* ʹ�� ADC */
    ADC_Cmd(ADCx, TRUE);
    /* ���� ADC ������ӳ� */
    Delay(0xffu);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
