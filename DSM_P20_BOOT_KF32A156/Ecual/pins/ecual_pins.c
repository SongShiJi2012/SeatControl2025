/*************************************************************************************************
 *  Copyright (c) 2019, ancle.co.
 *  All rights reserved.
 *
 *  FileName:     ecual_pins.c
 *
 *  Description:  board bins abstraction interface file
 *
 *  FileVersion:  V1.00
 *
 *  Date:         2019-03-15
 *
 *  Author:       ancle
 *
 *  Note:
 *       Rev.001    ancle    2019-03-15       New Create;
 *
 *       Rev.002    pannu    2019-05-07       Change PTA16、PA15、PTE6、PTD28、PTD29 config;
 *
 *       Rev.003    pannu    2019-05-08       根据IO资源分配表，对所有引脚重新配置；
 *                                            但需要使用外部中断的引脚没有进行配置为外部中断，
 *                                            以免进入中断没有清标志位导致死机; 当需要使用时再配置
 
 *       Rev.004    pannu    2019-05-09       PORTD 24由原来的使能下拉，修改为禁止，因为GPIO并没有配置
 *       Rev.005    pannu    2019-05-27       PORTA 28由原来的悬空，修改为输出低电平，不然BLE模块一直复位
 *
 *************************************************************************************************/

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "ecual_pins.h"

extern const pin_settings_config_t g_pin_mux_InitConfigArr[SELECT_PLATFORM_PINS];
extern const pin_settings_config_t g_pin_mux_OffModeConfigArr[SELECT_PLATFORM_PINS];
/*************************************************************************************************
 * @function name:      ecual_pins_init
 *
 * @description:        板集所有pin脚初始化
 *
 * @parameters:         none
 *
 * @return:             0 is successful
 *************************************************************************************************/
status_t ecual_pins_init( ePinsConfigMode Mode )
{
    status_t rt = STATUS_ERROR;

    if( Mode < PINS_MODE_MAX )
    {   
        switch ( Mode )
        {
        case PINS_MODE_INIT:
            {
                rt = PINS_DRV_Init( SELECT_PLATFORM_PINS, g_pin_mux_InitConfigArr );
            }
            break;
#if 0
        case PINS_MODE_NORAML:
            {
                rt = PINS_DRV_Init( Select_S32K1xx_PINs, g_pin_mux_NormalConfigArr );
            }
            break;

        case PINS_MODE_SUSPEND:
            {
                rt = PINS_DRV_Init( Select_S32K1xx_PINs, g_pin_mux_SuspendModeConfigArr );
            }   
            break; 
#endif
        case PINS_MODE_OFFMODE:
            {
                rt = PINS_DRV_Init( SELECT_PLATFORM_PINS, g_pin_mux_OffModeConfigArr );
            }
            break;

        default:
            break;
        }
    }

    return rt;
}

/*************************************************************************************************
 * Function Name:        ecual_PIN_output
 *
 * Description:          PIN脚输出电平
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *                       uint8_t value:               输出值  ( high or low )
 *
 * Output:               none
 *
 * Return:               none
 *
 *************************************************************************************************/
void ecual_PIN_output( user_pin_defines pinIndex, uint8_t value )
{
    if ( pinIndex < sizeof(g_pin_mux_InitConfigArr)/sizeof(pin_settings_config_t) )
    {
        value = value && 1;

        PINS_DRV_WritePin( g_pin_mux_InitConfigArr[pinIndex].base, g_pin_mux_InitConfigArr[pinIndex].m_Pin, value );
    }
}

/*************************************************************************************************
 * Function Name:        ecual_PIN_get
 *
 * Description:          获取PIN脚输入电平
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *
 * Output:               none
 *
 * Return:               1 is high, 0 is low
 *
 *************************************************************************************************/
uint8_t ecual_PIN_get( user_pin_defines pinIndex )
{
    if ( pinIndex < sizeof(g_pin_mux_InitConfigArr)/sizeof(pin_settings_config_t) )
    {
        uint32_t value;
        
        value = PINS_DRV_ReadPins( g_pin_mux_InitConfigArr[pinIndex].base);

        return (value & (1 << g_pin_mux_InitConfigArr[pinIndex].m_Pin)) && 1;
    }
    
    return 0;
}

/*************************************************************************************************
 * Function Name:        ecual_PIN_getpinsoutput
 *
 * Description:          获取输出引脚的电平状态
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *
 * Output:               none
 *
 * Return:               1 is high, 0 is low
 *
 *************************************************************************************************/
uint8_t ecual_PIN_getpinsoutput( user_pin_defines pinIndex )
{
	if ( pinIndex < sizeof(g_pin_mux_InitConfigArr)/sizeof(pin_settings_config_t) )
	{
		uint32_t value;

		value = GPIO_Read_Output_Data( g_pin_mux_InitConfigArr[pinIndex].base );

		return (value & (1 << g_pin_mux_InitConfigArr[pinIndex].m_Pin)) && 1;
	}

	return 0;
}

/*************************************************************************************************
 * Function Name:        ecual_PIN_SetEnableFlag
 *
 * Description:          设置引脚使能标志
 *
 * Input:                [in] type : 配置的引脚模式结构体类型
 *                         [in] pin_index : 引脚索引号
 *                         [in] enable : 使能标志
 *
 * Output:               none
 *
 * Return:               true is success
 *
 *************************************************************************************************/
bool_t ecual_PIN_SetEnableFlag( ePinsConfigMode type, uint8_t pin_index, bool_t enable)
{
    bool_t rt = FALSE;
#if 0
    if( pin_index < SELECT_PLATFORM_PINS )
    {
        switch( type )
        {
        case PINS_MODE_INIT:
            {
                g_pin_mux_InitConfigArr[pin_index].pinEnable = enable;
            }
            break;

#if 0
        case PINS_MODE_NORAML:
            {
                g_pin_mux_NormalConfigArr[pin_index].pinEnable = enable;
            }
            break;
        case PINS_MODE_SUSPEND:
            {
                g_pin_mux_SuspendModeConfigArr[pin_index].pinEnable = enable;
            }
            break;
#endif
        case PINS_MODE_OFFMODE:
            {
               
                g_pin_mux_OffModeConfigArr[pin_index].pinEnable = enable;
            }
            break;

        default :
            break;
        }

        rt = TRUE;
    }
#endif
    return rt;
}

