/*******************************************************************************
 *  $File Name$       : pins_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "pins_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void PINS_Init(const pin_settings_config_t * config);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_Init
 * Description   :
 *
 * Implements    :
 *END**************************************************************************/
static void PINS_Init(const pin_settings_config_t * config)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.m_Mode = config->m_Mode;
	GPIO_InitStructure.m_OpenDrain = config->m_OpenDrain;
	GPIO_InitStructure.m_PullDown = config->m_PullDown;
	GPIO_InitStructure.m_PullUp = config->m_PullUp;
	GPIO_InitStructure.m_Speed = config->m_Speed;
	GPIO_InitStructure.m_Pin = config->m_Pin;

	if(GPIO_MODE_RMP == GPIO_InitStructure.m_Mode)
	{
		GPIO_Configuration(config->base , &GPIO_InitStructure);
		GPIO_Pin_RMP_Config(config->base, config->m_PinNum, config->mux);
	}
	else if(GPIO_MODE_AN == GPIO_InitStructure.m_Mode)
	{
		//ADC口不需要输入输出配置
		GPIO_Write_Mode_Bits(config->base, GPIO_InitStructure.m_Pin, GPIO_InitStructure.m_Mode);
	}
	else if(GPIO_MODE_OUT == GPIO_InitStructure.m_Mode)
	{
		GPIO_Set_Output_Data_Bits(config->base, GPIO_InitStructure.m_Pin, config->initValue );
		//普通输出IO口不需要重映射,默认是GPIO
		GPIO_Write_Mode_Bits(config->base, GPIO_InitStructure.m_Pin, GPIO_InitStructure.m_Mode);
	}
	else
	{
		//普通输入IO口不需要重映射,默认是GPIO
		GPIO_Configuration(config->base , &GPIO_InitStructure);
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_Init
 * Description   : This function configures the pins with the options provided
 * in the given structure.
 *
 * Implements    : PINS_DRV_Init_Activity
 *END**************************************************************************/
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[])
{
    uint32_t i;
    for (i = 0U; i < pinCount; i++)
    {
    	if( config[i].pinEnable == TRUE )
    	{
    		PINS_Init(&config[i]);
    	}
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_WritePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * Implements    : PINS_DRV_WritePin_Activity
 *END**************************************************************************/
void PINS_DRV_WritePin(GPIO_Type *base,
                       pins_channel_type_t pin,
                       pins_level_type_t value)
{
	uint32_t  PinNum = 0x01;

	PinNum <<= pin;

	GPIO_Set_Output_Data_Bits(base, PinNum, value);
}
                       
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_TogglePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * Implements    : PINS_DRV_WritePin_Activity
 *END**************************************************************************/
void PINS_DRV_TogglePin(GPIO_Type *base,
                       pins_channel_type_t pin)
{
	uint32_t  PinNum = 0x01;

	PinNum <<= pin;

	GPIO_Toggle_Output_Data_Config(base, PinNum);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinsOutput
 * Description   : This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * Implements    : PINS_DRV_GetPinsOutput_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPinsOutput(GPIO_Type *base)
{
    return GPIO_Read_Output_Data(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ReadPins
 * Description   : This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * Implements    : PINS_DRV_ReadPins_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_ReadPins(GPIO_Type *base)
{
    return  GPIO_Read_Input_Data(base);
}

/******************************************************************************
 * EOF
 *****************************************************************************/
