/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_wdog.c
*
*  Description:  board WDG abstraction interface file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-15
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/
#include "ecual_wdog.h"
#include "wdog_driver.h"
#include "kf32a156_iwdt.h"
#include "ecual_pins.h"
/*************************************************************************************************
 * Variable declaration
 *************************************************************************************************/

/***********************************************************************************************
 * @function name: void ecual_WDOG_init(void)
 * @description:     初始化看门狗
 * 			 T =  prescaler*timeoutValue/clkSource
 *   			 WDOG_INTERNAL_CLOCK 32K
 * @input parameters:      TimerValue  ms
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_WDOG_init(uint16_t TimerValue)
{
    wdog_user_config_t watchdog_Config;
    uint16_t TimerCnt = (TimerValue >> 2);

    /*32k时钟，128分频*/
    if (TimerCnt > 0x0FFF)
    {
    	TimerCnt = 0x0FFF; /*最多16s*/
    }
    else if (TimerCnt == 0)
	{
    	TimerCnt = 1;
	}


    /*先初始化看门狗再初始化CAN，需要加下面三个语句  建议先初始化看门狗*/
    SFR_SET_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
  	SFR_SET_BIT_ASM(PM_CAL0, 30);
  	SFR_CLR_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);

    watchdog_Config.clkSource = WDOG_INTERNAL_CLOCK; /*32k  只支持内部低速时钟*/
    watchdog_Config.prescaler = IWDT_PRESCALER_128;
    watchdog_Config.timeoutValue  = TimerCnt;
    WDOG_DRV_Init(&watchdog_Config);
}

/***********************************************************************************************
 * @function name: void ecual_WDOG_dinit(void)
 * @description:    关闭看门狗
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_WDOG_dinit(void)
{
    WDOG_DRV_DeInit();
}

/***********************************************************************************************
 * @function name: void ecual_FeedDog( void )
 * @description:     看门狗喂狗
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_FeedDog( void )
{
    WDOG_DRV_Trigger();
    Ecual_FeedOutsideDog();
}

/***********************************************************************************************
 * @function name: void ecual_FeedDog( void )
 * @description:     看门狗喂狗
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void Ecual_FeedOutsideDog(void)
{
    Ecual_GpioToggleCh(EN_WdogOut);\
}

