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

	Rank = Rank + 1;/* Rank 从 1 开始 */

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
 *  @brief : 初始化ADC配置结构体
 *  @param[in]  adcInitStruct: 待初始化的结构体指针
 *  @param[out] 无
 *  @retval : 无
 */
static void ADC_Struct_Init(ADC_InitTypeDef *adcInitStruct)
{
    /* ADC时钟源选择 */
    adcInitStruct->m_Clock = ADC_SCLK;

    /* ADC时钟分频 */
    adcInitStruct->m_ClockDiv = ADC_CLK_DIV_2;

    /* 关闭ADC扫描模式 */
    adcInitStruct->m_ScanMode = FALSE;

    /* 配置为单次转换模式 */
    adcInitStruct->m_ContinuousMode = ADC_SINGLE_MODE;

    /* ADC转换结果右对齐 */
    adcInitStruct->m_DataAlign = ADC_DATAALIGN_RIGHT;

    /* 禁止常规通道外部触发 */
    adcInitStruct->m_ExternalTrig_EN = FALSE;

    /* 外部触发源 */
    adcInitStruct->m_ExternalTrig = ADC_EXTERNALTRIG_CCP1_CH1;

    /* 禁止高优先级通道外部触发 */
    adcInitStruct->m_HPExternalTrig_EN = FALSE;

    /* 高优先级外部触发源 */
    adcInitStruct->m_HPExternalTrig = ADC_HPEXTERNALTRIG_CCP1_CH1;

    /* ADC参考电压选择 */
    adcInitStruct->m_VoltageRef = ADC_REF_AVDD;

    /* 常规通道扫描长度 */
    adcInitStruct->m_NumOfConv = 1;

    /* 高优先级通道扫描长度 */
    adcInitStruct->m_NumOfHPConv = 1;
}

/***********************************************************************************************
 * @function name:  ADC_DRV_Adc0InitScanMode
 * @description:    初始化 ADC0 扫描模式，配置采样时钟、扫描通道数、参考电压等参数。
 * @input parameters: ScanNumber - 要扫描的通道数量
 * @output parameters: None
 * @return:         None
 * @note:           启用 ADC 后需延迟以确保稳定采样时钟
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void ADC_DRV_InitScanMode(ADC_SFRmap *ADCx, uint8_t ScanNumber)
{
    ADC_InitTypeDef ADC_InitStructure;

    /* 复位 ADC 模块，启用 ADC 时钟 */
    ADC_Reset(ADCx);

    /* 初始化 ADC 配置信息结构体 */
    ADC_Struct_Init(&ADC_InitStructure);
    /* 选择 HFCLK 作为 ADC 采样时钟源 */
    ADC_InitStructure.m_Clock = ADC_HFCLK;
    /* 配置 ADC 采样时钟分频系数 */
    ADC_InitStructure.m_ClockDiv = ADC_CLK_DIV_16;
    /* 使能 ADC 扫描模式 */
    ADC_InitStructure.m_ScanMode = TRUE;
    /* 选择单次转换模式作为 ADC 转换模式 */
    ADC_InitStructure.m_ContinuousMode = ADC_SINGLE_MODE;
    /* 采样结果右对齐 */
    ADC_InitStructure.m_DataAlign = ADC_DATAALIGN_RIGHT;
    /* 禁用外部触发 */
    ADC_InitStructure.m_ExternalTrig_EN = FALSE;
    /* 外部触发源配置不再需要 */
    /* 选择 Vdd 作为 ADC 参考电压 */
    ADC_InitStructure.m_VoltageRef = ADC_REF_AVDD;
    /* 设置常规通道扫描长度 */
    ADC_InitStructure.m_NumOfConv = ScanNumber;
    /* 初始化配置 ADC 模块 */
    ADC_Configuration(ADCx, &ADC_InitStructure);

    /* 使能 ADC */
    ADC_Cmd(ADCx, TRUE);
    /* 启用 ADC 后必须延迟 */
    Delay(0xffu);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
