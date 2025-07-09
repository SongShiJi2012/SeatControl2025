/*******************************************************************************
 *  $File Name$       : adc_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_adc.h"
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 /** Number of instances of the ADC module. */
#define ADC_INSTANCE_COUNT                       (3u)//KF32A156 : ADC0 ADC1 ADC2
/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base pointer */
#define ADC0                                     (ADC0_SFR)
/** Peripheral ADC1 base pointer */
#define ADC1                                     (ADC1_SFR)
/** Peripheral ADC1 base pointer */
#define ADC2                                     (ADC2_SFR)
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0, ADC1 ,ADC2 }


 /** Number of instances of the ADC module. */
#define ADCINT_INSTANCE_COUNT                       (3u)//KF32A156 : ADC0 ADC1 ADC2
/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base pointer */
#define Adc0_It                                     (INT_ADC0)
/** Peripheral ADC1 base pointer */
#define Adc1_It                                     (INT_ADC1)
/** Peripheral ADC1 base pointer */
#define Adc2_It                                     (INT_ADC2)
/** Array initializer of ADC peripheral base pointers */
#define ADC_INT_PTRS                            { Adc0_It, Adc1_It ,Adc2_It }
/*******************************************************************************
 * API
 ******************************************************************************/
//º¯ÊýÉùÃ÷
extern void ADC_DRV_RegularChannelConfig (const uint32_t instance, const uint32_t channel);
extern void ADC_DRV_SoftwareStartConv(const uint32_t instance);
extern bool ADC_DRV_GetConvCompleteFlag(const uint32_t instance);
extern uint16_t ADC_DRV_GetConversionValue (const uint32_t instance);
extern void ADC_DRV_AdcInit(const uint32_t instance);
extern void ADC_DRV_AdcDeInit(uint32_t instance);
//test
extern uint16_t ADC_DRV_TestGetADC0Value(void);
extern uint16_t ADC_DRV_TestADCValue(uint8_t instance ,uint8_t Channel);
#endif /* ADC_DRIVER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
