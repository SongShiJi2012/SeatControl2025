/*
 * wdog_driver.h
 *
 *  Created on: 2022-6-27
 *      Author: Administrator
 */

#ifndef WDOG_DRIVER_H_
#define WDOG_DRIVER_H_

//#include "kf32a156.h"
//#include "kf32a156_iwdt.h"
#include <stdint.h>

typedef enum
{
    WDOG_INTERNAL_CLOCK = 0x00U,
    WDOG_EXTERNAL_CLOCK
} wdog_clk_source_t;

typedef struct
{
    wdog_clk_source_t    clkSource;       /*!< The clock source of the WDOG */
    uint16_t             timeoutValue;    /*!< The timeout value */
    uint32_t             prescaler; /*!< If true, a fixed 256 prescaling of the counter reference clock is enabled */
} wdog_user_config_t;

extern void WDOG_DRV_Init(wdog_user_config_t* userConfigPtr);
extern void WDOG_DRV_DeInit(void);
extern void WDOG_DRV_Trigger(void);

#endif /* WDOG_DRIVER_H_ */
