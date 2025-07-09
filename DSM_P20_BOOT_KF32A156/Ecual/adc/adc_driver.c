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
    /* 初始化 ADC时钟源选择 */
    adcInitStruct->m_Clock = ADC_SCLK;

    /* 初始化 ADC时钟分频 */
    adcInitStruct->m_ClockDiv = ADC_CLK_DIV_2;

    /* 初始化 ADC扫描模式使能 */
    adcInitStruct->m_ScanMode = FALSE;

    /* 初始化 ADC连续转换模式 */
    adcInitStruct->m_ContinuousMode = ADC_SINGLE_MODE;

    /* 初始化 ADC转换结果输出格式 */
    adcInitStruct->m_DataAlign = ADC_DATAALIGN_LEFT;

    /* 初始化 ADC常规通道外部触发转换模式使能 */
    adcInitStruct->m_ExternalTrig_EN = FALSE;

    /* 初始化 ADC常规通道外部触发事件 */
    adcInitStruct->m_ExternalTrig = ADC_EXTERNALTRIG_CCP1_CH1;

    /* 初始化 ADC高优先级通道外部触发转换模式使能 */
    adcInitStruct->m_HPExternalTrig_EN = FALSE;

    /* 初始化 高优先级通道外部触发事件 */
    adcInitStruct->m_HPExternalTrig = ADC_HPEXTERNALTRIG_CCP1_CH1;

    /* 初始化 ADC参考电压选择 */
    adcInitStruct->m_VoltageRef = ADC_REF_AVDD;

    /* 初始化 ADC常规通道扫描长度 */
    adcInitStruct->m_NumOfConv = 1;

    /* 初始化 ADC高优先级通道扫描长度 */
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
	systick_delay_ms(5); /*初始化完必须延迟5ms*/
	//ADC_Set_INT_Enable (base,ADC_INT_HPEND, TRUE);
	//INT_Interrupt_Priority_Config(Int,1,0);//抢占优先级1,子优先级0
	//INT_Clear_Interrupt_Flag(Int);//清中断标志
	//INT_Interrupt_Enable(Int,TRUE);//外设中断使能
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ADC_DRV_GetADC0Value
 * Description   :
 *
 *END**************************************************************************/
uint16_t ADC_DRV_TestGetADC0Value(void)//阻塞单次采集test
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


uint16_t ADC_DRV_TestADCValue(uint8_t instance ,uint8_t Channel)//阻塞单次采集test
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
