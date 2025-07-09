/*
 * tim_driver.c
 *
 *  Created on: 2022-6-27
 *      Author: Administrator
 */
#include "tim_driver.h"
#include "kf32a156_btim.h"
#include "kf32a156_gtim.h"
#include "kf32a156_atim.h"
#include "kf32a156_int.h"

uint32_t s_GTIMSource[TIM_TCLOCK_COUNT] = {GPTIM_SCLK,GPTIM_HFCLK,GPTIM_LFCLK,GPTIM_T0_INTLF};

GTIM_Type * s_GTimBase[GTIM_INSTANCE_COUNT] =  GTIM_BASE_PTRS;
TIM_IRQ_Type s_GTIMIrq[GTIM_INSTANCE_COUNT] =  GTIM_IRQS;

uint32_t s_BTIMSource[TIM_TCLOCK_COUNT] = {BTIM_SCLK,BTIM_HFCLK,BTIM_LFCLK,BTIM_SCLK};

BTIM_Type * s_BTimBase[BTIM_INSTANCE_COUNT] =  BTIM_BASE_PTRS;
TIM_IRQ_Type s_BTIMIrq[BTIM_INSTANCE_COUNT] =  BTIM_IRQS;

uint32_t s_ATIMSource[TIM_TCLOCK_COUNT] = {ATIM_SCLK,ATIM_HFCLK,ATIM_LFCLK};

ATIM_Type * s_ATimBase[ATIM_INSTANCE_COUNT] =  ATIM_BASE_PTRS;
TIM_IRQ_Type s_ATIMIrq[ATIM_INSTANCE_COUNT] =  ATIM_IRQS;

/***********************************************************************************************
 * @function name: void WDOG_DRV_Init(wdog_user_config_t * userConfigPtr)
 * @description:    初始化通用定时器
 * 定时器周期  T = CNT*(Prescaler+1)/CLK 单位是ms
 * @input parameters:      userConfigPtr
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void TIM_GENER_DRV_Init(Tim_user_config_t* userConfigPtr)
{
	GTIM_Type* GPTIMx = s_GTimBase[userConfigPtr->TimIndex];
	TIM_IRQ_Type PeripheralIndex = s_GTIMIrq[userConfigPtr->TimIndex];
	uint32_t CNT_T = userConfigPtr->TimeCnt;
	uint32_t Prescaler = userConfigPtr->Prescaler;
	uint32_t CLKSource = s_GTIMSource[userConfigPtr->clkSource];

	/*reset peripherals of Timer 18 and enable peripherals clock source.*******/
	TIM_Reset(GPTIMx);
	/*Configure the T18 immediate update control bit to update immediately*****/
	GPTIM_Updata_Immediately_Config(GPTIMx,TRUE);
	/*Enable T18 update controller*********************************************/
	GPTIM_Updata_Enable(GPTIMx,TRUE);
	/*Set to timing mode as working mode of timer***************************/
	GPTIM_Work_Mode_Config(GPTIMx,GPTIM_TIMER_MODE);
	/*Updata counter***********************************************************/
	GPTIM_Set_Counter(GPTIMx,0);
	/*Set the counting period**************************************************/
	GPTIM_Set_Period(GPTIMx,CNT_T);
	/*Set prescaler************************************************************/
	GPTIM_Set_Prescaler(GPTIMx,Prescaler);
	/*Set up and down count****************************************************/
//	GPTIM_Counter_Mode_Config(GPTIMx,GPTIM_COUNT_UP_DOWN_OUF);
	GPTIM_Counter_Mode_Config(GPTIMx,GPTIM_COUNT_UP_OF);//修改计数方式为向上,原计数相邻间差2个计数时间 - 2025.03.10 ssj
	/*Select CLK  as clock source of timer *********************************/
	GPTIM_Clock_Config(GPTIMx,CLKSource);
	/*Set interrupt priority***************************************************/
	INT_Interrupt_Priority_Config(PeripheralIndex,4,0);
	/*Enable timer 18 overflow interrupt***************************************/
	GPTIM_Overflow_INT_Enable(GPTIMx,TRUE);
	/*Enable INT_T18 interrupt*************************************************/
	INT_Interrupt_Enable(PeripheralIndex,TRUE);
	/*Clear INT_T18 interrupt flag*********************************************/
	INT_Clear_Interrupt_Flag(PeripheralIndex);
	/*Enable timer 18**********************************************************/
	GPTIM_Cmd(GPTIMx,FALSE);
}

/***********************************************************************************************
 * @function name: void TIM_GENER_DRV_Disable(uint8_t Count)
 * @description:    关闭通用定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void TIM_GENER_DRV_Disable(Time_number_t Count)
{
	GTIM_Type* GPTIMx = s_GTimBase[Count];

	GPTIM_Cmd(GPTIMx,FALSE);
}

/***********************************************************************************************
 * @function name: void TIM_GENER_DRV_Enable(uint8_t Count)
 * @description:    开启通用定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-30 czb
 ***********************************************************************************************/
void TIM_GENER_DRV_Enable(Time_number_t Count)
{
	GTIM_Type* GPTIMx = s_GTimBase[Count];
	TIM_IRQ_Type PeripheralIndex = s_GTIMIrq[Count];

	INT_Clear_Interrupt_Flag(PeripheralIndex);
	GPTIM_Cmd(GPTIMx,TRUE);
}

/***********************************************************************************************
 * @function name: void TIM_BASIC_DRV_Init(wdog_user_config_t * userConfigPtr)
 * @description:    初始化基本定时器
 * 定时器周期  T = CNT*(Prescaler+1)/CLK 单位是ms
 * @input parameters:      userConfigPtr
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_BASIC_DRV_Init(Tim_user_config_t* userConfigPtr)
{
	BTIM_Type* BTIMx = s_BTimBase[userConfigPtr->TimIndex];
	TIM_IRQ_Type PeripheralIndex = s_BTIMIrq[userConfigPtr->TimIndex];
	uint32_t CNT_T = userConfigPtr->TimeCnt;
	uint32_t Prescaler = userConfigPtr->Prescaler;
	uint32_t CLKSource = s_BTIMSource[userConfigPtr->clkSource];

	TIM_Reset(BTIMx);
	BTIM_Updata_Immediately_Config(BTIMx,TRUE);
	BTIM_Updata_Enable(BTIMx,TRUE);
	BTIM_Work_Mode_Config(BTIMx,BTIM_TIMER_MODE);
	BTIM_Set_Counter(BTIMx,0);
	BTIM_Set_Period(BTIMx,CNT_T);
	BTIM_Set_Prescaler(BTIMx,Prescaler);
	BTIM_Counter_Mode_Config(BTIMx,BTIM_COUNT_UP_OF);
	/*Select internal high frequency as clock source*/
	BTIM_Clock_Config(BTIMx,CLKSource);
	INT_Interrupt_Priority_Config(PeripheralIndex,4,0);
	BTIM_Overflow_INT_Enable(BTIMx,TRUE);
	INT_Interrupt_Enable(PeripheralIndex,TRUE);
	INT_Clear_Interrupt_Flag(PeripheralIndex);
	BTIM_Cmd(BTIMx,FALSE);
	INT_Stack_Align_Config(INT_STACK_SINGLE_ALIGN);
}

/***********************************************************************************************
 * @function name: void TIM_BASIC_DRV_Disable(uint8_t Count)
 * @description:    关闭基本定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_BASIC_DRV_Disable(Time_number_t Count)
{
	BTIM_Type* BTIMx = s_BTimBase[Count];

	BTIM_Cmd(BTIMx,FALSE);
}

/***********************************************************************************************
 * @function name: void TIM_BASIC_DRV_Enable(uint8_t Count)
 * @description:    开启基本定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_BASIC_DRV_Enable(Time_number_t Count)
{
	BTIM_Type* BTIMx = s_BTimBase[Count];
	TIM_IRQ_Type PeripheralIndex = s_BTIMIrq[Count];

	INT_Clear_Interrupt_Flag(PeripheralIndex);
	BTIM_Cmd(BTIMx,TRUE);
}

/***********************************************************************************************
 * @function name: void TIM_ADVANCED_DRV_Init(wdog_user_config_t * userConfigPtr)
 * @description:    初始化高级定时器
 * 定时器周期  T = CNT*(Prescaler+1)/CLK 单位是ms
 * @input parameters:      userConfigPtr
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_ADVANCED_DRV_Init(Tim_user_config_t* userConfigPtr)
{
	/*20221205 高级定时器还需要优化 czb*/

	ATIM_Type* ATIMx = s_ATimBase[userConfigPtr->TimIndex];
	TIM_IRQ_Type PeripheralIndex = s_ATIMIrq[userConfigPtr->TimIndex];
	uint32_t CNT_T = userConfigPtr->TimeCnt;
	uint32_t Prescaler = userConfigPtr->Prescaler;
	uint32_t CLKSource = s_ATIMSource[userConfigPtr->clkSource];


	if(T5_SFR == ATIMx)
	{
		/*reset peripherals of Timer 18 and enable peripherals clock source.*******/
		TIM_Reset(ATIMx);
		/*Configure the T6 immediate update control bit to update immediately******/
		ATIM_X_Updata_Immediately_Config(ATIMx,TRUE);
		/*Enable T6 update controller**********************************************/
		ATIM_X_Updata_Enable(ATIMx,TRUE);
		/*Set to timing mode as working mode of timer 6****************************/
		ATIM_X_Work_Mode_Config(ATIMx,ATIM_TIMER_MODE);
		/*Updata counter***********************************************************/
		ATIM_X_Set_Counter(ATIMx,0);
		/*Set the counting period**************************************************/
		ATIM_X_Set_Period(ATIMx,CNT_T);
		/*Set prescaler************************************************************/
		ATIM_X_Set_Prescaler(ATIMx,Prescaler);
		ATIM_X_Postscaler_Config(ATIMx,ATIM_POSTSCALER_DIV_1);
		/*Set to count up mode*****************************************************/
		ATIM_X_Counter_Mode_Config(ATIMx,ATIM_COUNT_UP_OF);
		/*Select HFCLK as clock source of timer 6**********************************/
		ATIM_X_Clock_Config(ATIMx,CLKSource);
		/*Enable timer 6 overflow interrupt****************************************/
		ATIM_X_Overflow_INT_Enable(ATIMx,TRUE);
		/*Enable timer 6 **********************************************************/
		ATIM_X_Cmd(ATIMx,FALSE);
	}
	else if(T6_SFR == ATIMx)
	{
		/*reset peripherals of Timer 18 and enable peripherals clock source.*******/
		TIM_Reset(ATIMx);
		/*Configure the T6 immediate update control bit to update immediately******/
		ATIM_Z_Updata_Immediately_Config(ATIMx,TRUE);
		/*Enable T6 update controller**********************************************/
		ATIM_Z_Updata_Enable(ATIMx,TRUE);
		/*Set to timing mode as working mode of timer 6****************************/
		ATIM_Z_Work_Mode_Config(ATIMx,ATIM_TIMER_MODE);
		/*Updata counter***********************************************************/
		ATIM_Z_Set_Counter(ATIMx,0);
		/*Set the counting period**************************************************/
		ATIM_Z_Set_Period(ATIMx,CNT_T);
		/*Set prescaler************************************************************/
		ATIM_Z_Set_Prescaler(ATIMx,Prescaler);
		ATIM_Z_Postscaler_Config(ATIMx,ATIM_POSTSCALER_DIV_1);
		/*Set to count up mode*****************************************************/
		ATIM_Z_Counter_Mode_Config(ATIMx,ATIM_COUNT_UP_OF);
		/*Select HFCLK as clock source of timer 6**********************************/
		ATIM_Z_Clock_Config(ATIMx,CLKSource);
		/*Enable timer 6 overflow interrupt****************************************/
		ATIM_Z_Overflow_INT_Enable(ATIMx,TRUE);
		/*Enable timer 6 **********************************************************/
		ATIM_Z_Cmd(ATIMx,FALSE);
	}
	else
	{
		return;
	}
	/*Set interrupt priority***************************************************/
	INT_Interrupt_Priority_Config(PeripheralIndex,4,0);
	/*Enable INT_T6 interrupt**************************************************/
	INT_Interrupt_Enable(PeripheralIndex,TRUE);
	/*Clear INT_T6 interrupt flag**********************************************/
	INT_Clear_Interrupt_Flag(PeripheralIndex);
	INT_Stack_Align_Config(INT_STACK_SINGLE_ALIGN);
}

/***********************************************************************************************
 * @function name: void TIM_ADVANCED_DRV_Disable(uint8_t Count)
 * @description:    关闭高级定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_ADVANCED_DRV_Disable(Time_number_t Count)
{
	ATIM_Type* ATIMx = s_ATimBase[Count];

	if(T5_SFR == ATIMx)
	{
		ATIM_X_Cmd(ATIMx,FALSE);
	}
	else if(T6_SFR == ATIMx)
	{
		ATIM_Z_Cmd(ATIMx,FALSE);
	}
	else
	{
		return;
	}
}

/***********************************************************************************************
 * @function name: void TIM_ADVANCED_DRV_Enable(uint8_t Count)
 * @description:    开启高级定时器
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_ADVANCED_DRV_Enable(Time_number_t Count)
{
	ATIM_Type* ATIMx = s_ATimBase[Count];
	TIM_IRQ_Type PeripheralIndex = s_ATIMIrq[Count];

	INT_Clear_Interrupt_Flag(PeripheralIndex);
	if(T5_SFR == ATIMx)
	{
		ATIM_X_Cmd(ATIMx,TRUE);
	}
	else if(T6_SFR == ATIMx)
	{
		ATIM_Z_Cmd(ATIMx,TRUE);
	}
	else
	{
		return;
	}
}

/***********************************************************************************************
 * @function name: void TIM_GENER_IRQClear(Time_number_t Count)
 * @description:    通用定时器中断标志清除
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_GENER_IRQClear(Time_number_t Count)
{
	GTIM_Type* GPTIMx = s_GTimBase[Count];

	GPTIM_Clear_Updata_INT_Flag(GPTIMx);
	GPTIM_Clear_Overflow_INT_Flag(GPTIMx);
}

/***********************************************************************************************
 * @function name: void TIM_BASIC_IRQClear(Time_number_t Count)
 * @description:    基本时器中断标志清除
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_BASIC_IRQClear(Time_number_t Count)
{
	BTIM_Type* BTIMx = s_BTimBase[Count];

	BTIM_Clear_Updata_INT_Flag(BTIMx);
	BTIM_Clear_Overflow_INT_Flag (BTIMx);
}

/***********************************************************************************************
 * @function name: void TIM_ADVANCED_IRQClear(Time_number_t Count)
 * @description:    高级定时器中断标志清除
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-2 jkx
 ***********************************************************************************************/
void TIM_ADVANCED_IRQClear(Time_number_t Count)
{
	ATIM_Type* ATIMx = s_ATimBase[Count];

	if (0 != ATIM_X_Get_Overflow_INT_Flag(T5_SFR))
	{
		ATIM_X_Clear_Overflow_INT_Flag(T5_SFR);
	}

	if(0 != ATIM_Z_Get_Overflow_INT_Flag(T6_SFR))
	{
		ATIM_Z_Clear_Overflow_INT_Flag(T6_SFR);
	}
}
