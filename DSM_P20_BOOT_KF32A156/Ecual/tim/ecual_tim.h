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
#ifndef _ECUAL_TIM_H_
#define _ECUAL_TIM_H_

#include "tim_driver.h"

extern void ecual_Tim_init(Tim_user_config_t* UserCfg,Tim_IRQ_callback_t pCallback_event);
extern void ecual_Tim_Enable(Time_type_t Type, Time_number_t TimIndex);
extern void ecual_Tim_Disable(Time_type_t Type, Time_number_t TimIndex);
extern void ecual_Tim_IRQHandler(Time_type_t Type, Time_number_t TimIndex);

#endif /* _ */
