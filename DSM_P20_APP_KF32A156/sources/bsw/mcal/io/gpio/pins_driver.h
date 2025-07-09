/*******************************************************************************
 *  $File Name$       : pins_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef PINS_DRIVER_H
#define PINS_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_gpio.h"
#include "status.h"
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define KF32A156MQV_PINS_144        ( 89u )//对应的MCU平台所使用的有效的端口数定义

#define SELECT_PLATFORM_PINS	KF32A156MQV_PINS_144
/*!
 * @brief Type of a GPIO channel representation
 * Implements : pins_channel_type_t_Class
 */
typedef uint32_t pins_channel_type_t;

typedef uint8_t pins_level_type_t;

typedef GPIO_SFRmap GPIO_Type;

#define pin_settings_config_t PIN_settings_config_t

/*!
 * @brief Configures the Pin mux selection
 * Implements : port_mux_t_Class
 */
typedef enum
{
    PORT_MUX_ALT0	             = GPIO_RMP_AF0,
    PORT_MUX_ALT1	             = GPIO_RMP_AF1,
    PORT_MUX_ALT2                = GPIO_RMP_AF2,
    PORT_MUX_ALT3                = GPIO_RMP_AF3,
    PORT_MUX_ALT4                = GPIO_RMP_AF4,
    PORT_MUX_ALT5                = GPIO_RMP_AF5,
    PORT_MUX_ALT6                = GPIO_RMP_AF6,
    PORT_MUX_ALT7                = GPIO_RMP_AF7,
    PORT_MUX_ALT8                = GPIO_RMP_AF8,
    PORT_MUX_ALT9                = GPIO_RMP_AF9,
    PORT_MUX_ALT10               = GPIO_RMP_AF10,
    PORT_MUX_ALT11               = GPIO_RMP_AF11,
    PORT_MUX_ALT12               = GPIO_RMP_AF12,
    PORT_MUX_ALT13               = GPIO_RMP_AF13,
    PORT_MUX_ALT14               = GPIO_RMP_AF14,
} port_mux_t;

//platform
typedef struct
{
	GPIO_SFRmap* base;
	bool pinEnable;
    uint32_t m_Pin;                     /* GPIO端口掩码，取值为宏“GPIO端口掩码”中的一个或多个组合 */
    uint16_t m_PinNum;
    GPIOMode_TypeDef m_Mode;            /* GPIO输出模式，取值为枚举类型GPIOMode_TypeDef中的一个 */
    GPIOSpeed_TypeDef m_Speed;          /* GPIO输出速度。取值为枚举类型GPIOSpeed_TypeDef中的一个 */
    GPIOPOD_TypeDef m_OpenDrain;        /* GPIO开漏控制， 取值为枚举类型GPIOPOD_TypeDef中的一个 */
    GPIOPU_TypeDef m_PullUp;            /* GPIO上拉配置， 取值为枚举类型GPIOPU_TypeDef中的一个 */
    GPIOPD_TypeDef m_PullDown;          /* GPIO下拉配置，   取值为枚举类型GPIOPU_TypeDef中的一个 */
    port_mux_t mux;
    pins_level_type_t           initValue;
}PIN_settings_config_t;
/*!
 * @brief Configures the port data direction
 * Implements : port_data_direction_t_Class
 */
typedef enum
{
    GPIO_INPUT_DIRECTION       = 0x0U,  /*!< General purpose input direction.       */
    GPIO_OUTPUT_DIRECTION      = 0x1U,  /*!< General purpose output direction.      */
    GPIO_UNSPECIFIED_DIRECTION = 0x2U   /*!< General purpose unspecified direction. */
} port_data_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return The status of the operation
 */
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[]);
/*!
 * @brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param[in] pin Pin number to be written
 * @param[in] value Pin value to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_WritePin(GPIO_Type *base,
                       pins_channel_type_t pin,
                       pins_level_type_t value);
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_TogglePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * Implements    : PINS_DRV_WritePin_Activity
 *END**************************************************************************/
void PINS_DRV_TogglePin(GPIO_Type *base,
                       pins_channel_type_t pin);

/*!
 * @brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
pins_channel_type_t PINS_DRV_GetPinsOutput (GPIO_Type *base);

/*!
 * @brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @param[in] base GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is read as LOW
 *        - 1: corresponding pin is read as HIGH
 */
pins_channel_type_t PINS_DRV_ReadPins(GPIO_Type *base);

#endif /* PINS_DRIVER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
