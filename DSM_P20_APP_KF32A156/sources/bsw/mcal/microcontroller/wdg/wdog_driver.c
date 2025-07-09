/*
 * wdog_driver.c
 *
 *  Created on: 2022-6-27
 *      Author: Administrator
 */
#include "wdog_driver.h"
#include "kf32a156_iwdt.h"
#include "kf32a156_pm.h"
#include "kf32a156_bkp.h"
#include "devassert.h"

/***********************************************************************************************
 * @function name: void WDOG_DRV_Init(wdog_user_config_t * userConfigPtr)
 * @description:    初始化看门狗
 * @input parameters:      userConfigPtr
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void WDOG_DRV_Init(wdog_user_config_t * userConfigPtr)
{
	DEV_ASSERT(userConfigPtr != NULL);
	//IWDG_Config(timeout,IWDT_PRESCALER_64);
	/*enable BKP write and read*************************************************/
	BKP_Write_And_Read_Enable(TRUE);
	/*Exit reset state**********************************************************/
	PM_Independent_Watchdog_Reset_Config(PERIPHERAL_OUTRST_STATUS);
	/*select INTLF as the IWDG clock source*************************************/
	PM_Internal_Low_Frequency_Enable(TRUE);
	/*T = (1/32K)*Prescaler*Overflow*******************************************/
	IWDT_Overflow_Config (userConfigPtr->timeoutValue);
	IWDT_Prescaler_Config(userConfigPtr->prescaler);
	/*enable IWDG*/
	IWDT_Enable(TRUE);
}

/***********************************************************************************************
 * @function name: void WDOG_DRV_DeInit(void)
 * @description:    关闭看门狗
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void WDOG_DRV_DeInit(void)
{
	IWDT_Enable(FALSE);
	IWDT_CTL = 0x0000FFF4;
	IWDT_FD = 0x00000000;
}

/***********************************************************************************************
 * @function name: void WDOG_DRV_DeInit(void)
 * @description:    喂狗
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void WDOG_DRV_Trigger(void)
{
	IWDT_Feed_The_Dog();
}

