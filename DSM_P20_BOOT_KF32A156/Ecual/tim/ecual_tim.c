/*************************************************************************************************
*  Copyright (c) 2022,
*  All rights reserved.
*
*  FileName:     ecual_tim.h
*
*  Description:
*
*  FileVersion:  V1.00
*
*  Date:         2022-12-5
*
*  Author:
*
*  Note:         1. New Create;
*************************************************************************************************/
#include "ecual_tim.h"
#include "devassert.h"

Tim_user_config_t  s_GUserConfigPtr[GTIM_INSTANCE_COUNT];
Tim_user_config_t  s_BUserConfigPtr[BTIM_INSTANCE_COUNT];
Tim_user_config_t  s_AUserConfigPtr[ATIM_INSTANCE_COUNT];

/***********************************************************************************************
 * @function name: void ecual_Tim_init(Tim_user_config_t* UserCfg)
 * @description:     初始化定时器
 * 			 T =  (prescaler+1)*timeoutValue/clkSource
 * @input parameters:     UserCfg
 * 						pCallback_event
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_Tim_init(Tim_user_config_t* UserCfg,Tim_IRQ_callback_t pCallback_event)
{
	uint8_t Ch = UserCfg->TimIndex ;
	Time_type_t TimerType = UserCfg->TimType ;
	Tim_user_config_t * state;

	DEV_ASSERT(TimerType < TIM_TYPE_COUNT);

	switch (TimerType)
	{
		case TIM_TYPE_GENER:
			DEV_ASSERT(Ch <= GTIM_INSTANCE_COUNT);

			state = &s_GUserConfigPtr[Ch];
			state->TimType = UserCfg->TimType;
			state->TimIndex = UserCfg->TimIndex;
			state->clkSource = UserCfg->clkSource;
			state->Prescaler = UserCfg->Prescaler;
			state->TimeCnt = UserCfg->TimeCnt;
			state->callback = pCallback_event;
			TIM_GENER_DRV_Init(state);
		break;

		case TIM_TYPE_BASE:
			DEV_ASSERT(Ch <= BTIM_INSTANCE_COUNT);

			state = &s_BUserConfigPtr[Ch];
			state->TimType = UserCfg->TimType;
			state->TimIndex = UserCfg->TimIndex;
			state->clkSource = UserCfg->clkSource;
			state->Prescaler = UserCfg->Prescaler;
			state->TimeCnt = UserCfg->TimeCnt;
			state->callback = pCallback_event;
			TIM_BASIC_DRV_Init(state);
		break;

		case TIM_TYPE_ADVANCED:
			DEV_ASSERT(Ch <= ATIM_INSTANCE_COUNT);

			state = &s_AUserConfigPtr[Ch];
			state->TimType = UserCfg->TimType;
			state->TimIndex = UserCfg->TimIndex;
			state->clkSource = UserCfg->clkSource;
			state->Prescaler = UserCfg->Prescaler;
			state->TimeCnt = UserCfg->TimeCnt;
			state->callback = pCallback_event;
			TIM_ADVANCED_DRV_Init(state);
		break;

		default:
		break;
	}
}

/***********************************************************************************************
 * @function name: void ecual_Tim_Enable(Time_type_t Type, Time_number_t TimIndex)
 * @description:     定时器使能
 * @input parameters:      Type  TimIndex
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_Tim_Enable(Time_type_t Type, Time_number_t TimIndex)
{
	switch (Type)
	{
		case TIM_TYPE_GENER:
			TIM_GENER_DRV_Enable(TimIndex);
		break;

		case TIM_TYPE_BASE:
			TIM_BASIC_DRV_Enable(TimIndex);
		break;

		case TIM_TYPE_ADVANCED:
			TIM_ADVANCED_DRV_Enable(TimIndex);
		break;

		default:
		break;
	}
}

/***********************************************************************************************
 * @function name: void ecual_Tim_Disable(Time_type_t Type, Time_number_t TimIndex)
 * @description:     定时器失能
 * @input parameters:      Type  TimIndex
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_Tim_Disable(Time_type_t Type, Time_number_t TimIndex)
{
	switch (Type)
	{
		case TIM_TYPE_GENER:
			TIM_GENER_DRV_Disable(TimIndex);
		break;

		case TIM_TYPE_BASE:
			TIM_BASIC_DRV_Disable(TimIndex);
		break;

		case TIM_TYPE_ADVANCED:
			TIM_ADVANCED_DRV_Disable(TimIndex);
		break;

		default:
		break;
	}
}

/***********************************************************************************************
 * @function name: void ecual_Tim_IRQHandler(Time_type_t Type, Time_number_t TimIndex)
 * @description:     定时器中断
 * @input parameters:      Type  TimIndex
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_Tim_IRQHandler(Time_type_t Type, Time_number_t TimIndex)
{
	Tim_user_config_t * state;

	switch (Type)
	{
		case TIM_TYPE_GENER:
			state = &s_GUserConfigPtr[TimIndex];
			TIM_GENER_IRQClear(TimIndex);
			if (state->callback != NULL)
			{
				state->callback();
			}
		break;

		case TIM_TYPE_BASE:
			state = &s_BUserConfigPtr[TimIndex];
			TIM_BASIC_IRQClear(TimIndex);
			if (state->callback != NULL)
			{
				state->callback();
			}
		break;

		case TIM_TYPE_ADVANCED:
			state = &s_AUserConfigPtr[TimIndex];
			TIM_ADVANCED_IRQClear(TimIndex);
			if (state->callback != NULL)
			{
				state->callback();
			}
		break;

		default:
		break;
	}
}

