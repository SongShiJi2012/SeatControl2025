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
 * @description:     ��ʼ�����Ź�
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

    /*32kʱ�ӣ�128��Ƶ*/
    if (TimerCnt > 0x0FFF)
    {
    	TimerCnt = 0x0FFF; /*���16s*/
    }
    else if (TimerCnt == 0)
	{
    	TimerCnt = 1;
	}


    /*�ȳ�ʼ�����Ź��ٳ�ʼ��CAN����Ҫ�������������  �����ȳ�ʼ�����Ź�*/
    SFR_SET_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
  	SFR_SET_BIT_ASM(PM_CAL0, 30);
  	SFR_CLR_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);

    watchdog_Config.clkSource = WDOG_INTERNAL_CLOCK; /*32k  ֻ֧���ڲ�����ʱ��*/
    watchdog_Config.prescaler = IWDT_PRESCALER_128;
    watchdog_Config.timeoutValue  = TimerCnt;
    WDOG_DRV_Init(&watchdog_Config);
}

/***********************************************************************************************
 * @function name: void ecual_WDOG_dinit(void)
 * @description:    �رտ��Ź�
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
 * @description:     ���Ź�ι��
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
 * @description:     ���Ź�ι��
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

