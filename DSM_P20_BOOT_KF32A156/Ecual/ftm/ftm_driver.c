/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*!
 * @file ftm_pwm_driver.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * The function is defined for use by application code.
 */

#include "ftm_driver.h"
#include "kf32a156_atim.h"
#include "kf32a156_int.h"
#include "kf32a156_btim.h"
#include "devassert.h"

uint32_t s_CCPCLK[FTM_CLOCK_SOURCE_COUNT] = {GPTIM_SCLK,GPTIM_HFCLK,GPTIM_LFCLK,GPTIM_T0_INTLF};
FTM_CCP_Type * const s_FtmCCPBase[GCCP_INSTANCE_COUNT] = FTM_GCCP_BASE_PTRS;
uint16_t s_FtmCCPChannl[FTM_CHANNL_COUNT] = FTM_GCCP_CHANNEL_PTRS;

uint32_t s_ECCPCLK[FTM_CLOCK_SOURCE_COUNT] = {ATIM_SCLK,ATIM_HFCLK,ATIM_LFCLK};
FTM_ECCP_Type * const s_FtmECCPBase[ECCP_INSTANCE_COUNT] = FTM_ECCP_BASE_PTRS;
uint16_t s_FtmECCPChannl[FTM_CHANNL_COUNT] = FTM_ECCP_CHANNEL_PTRS;

/***********************************************************************************************
 * @function name: uint32_t FTM_DRV_PWMDutyCal(uint32_t TimeCnt, uint32_t Duty)
 * @description:   PWM占空比数据计算
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
static uint32_t FTM_DRV_PWMDutyCal(uint32_t TimeCnt, uint32_t Duty)
{
	uint32_t DutyValue = Duty;

	 if(DutyValue >= 100)
	 {
		 DutyValue = 100;
	 }

	 DutyValue *= TimeCnt;
	 DutyValue /= 100;

	return DutyValue;
}

/***********************************************************************************************
 * @function name: void FTM_DRV_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:    初始化PWM
 * PWM频率 f= clkSource/((Prescaler+1)*TimeCnt)
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
{
	FTM_CCP_Type *CCPx = s_FtmCCPBase[User_CCPCfg->CCPIndex];
	 uint16_t Channl = s_FtmCCPChannl[User_CCPCfg->ChannlIndex];
	 uint32_t Clock_Source = s_CCPCLK[User_CCPCfg->clkSource];
	 uint32_t TimeCnt = User_CCPCfg->TimeCnt;
	 uint16_t Prescaler = User_CCPCfg->Prescaler;
	 uint32_t Duty = 0;

	 DEV_ASSERT(User_CCPCfg->CCPIndex < FTM_INSTANCE_COUNT);
	 DEV_ASSERT(User_CCPCfg->ChannlIndex < FTM_CHANNL_COUNT);

	 Duty =  FTM_DRV_PWMDutyCal(TimeCnt,User_CCPCfg->Duty);

	/* Timer peripheral reset, enable peripheral clock */
	TIM_Reset(CCPx);
	/* PWM function channel mode */
	CCP_PWM_Mode_Config(CCPx, Channl, CCP_PWM_MODE);
	/* Configure CCP channel output to control PWM output, high effective */
	CCP_Channel_Output_Control(CCPx, Channl, CCP_CHANNEL_OUTPUT_PWM_ACTIVE);
	/* PWM duty cycle */
	CCP_Set_Compare_Result(CCPx, Channl, Duty);

	/* Update control now */
	GPTIM_Updata_Immediately_Config(CCPx, TRUE);
	/* Configuration update enable */
	GPTIM_Updata_Enable(CCPx, TRUE);
	/* Timing mode selection */
	GPTIM_Work_Mode_Config(CCPx, GPTIM_TIMER_MODE);
	/* Timer count value */
	GPTIM_Set_Counter(CCPx, 0);
	/* Timer period value */
	GPTIM_Set_Period(CCPx, TimeCnt);
	/* Timer prescaler value */
	GPTIM_Set_Prescaler(CCPx, Prescaler);

	#if CCP_PWM_WORK == PWM_Edge_Out
	/* Up-counting mode, that is, edge-aligned PWM signal */
	GPTIM_Counter_Mode_Config(CCPx, GPTIM_COUNT_UP_OF);
	#else
	/* Up and down counting mode, that is, center-aligned PWM signal */
	GPTIM_Counter_Mode_Config(CCPx, GPTIM_COUNT_UP_DOWN_OF);
	#endif
	/* Configure working clock */
	GPTIM_Clock_Config(CCPx, Clock_Source);
	/* Enable timer */
	GPTIM_Cmd(CCPx, FALSE);
}

/***********************************************************************************************
 * @function name: void FTM_DRV_UpdatePWMDuty(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:   修改PWM占空比
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_UpdateCCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg)
{
	FTM_CCP_Type *CCPx = s_FtmCCPBase[User_CCPCfg->CCPIndex];
	uint16_t Channl = s_FtmCCPChannl[User_CCPCfg->ChannlIndex];
	uint32_t Duty = 0;

	Duty =  FTM_DRV_PWMDutyCal(User_CCPCfg->TimeCnt,User_CCPCfg->Duty);

	GPTIM_Cmd(CCPx, TRUE);
	CCP_Set_Compare_Result(CCPx,Channl,Duty);
}

/***********************************************************************************************
 * @function name: void FTM_DRV_PWM_Disable(FTM_Index Count)
 * @description:    关闭PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_CCP_PWM_Disable(FTM_Index Count)
{
	FTM_CCP_Type *CCPx = s_FtmCCPBase[Count];

	GPTIM_Cmd(CCPx,FALSE);
}

/***********************************************************************************************
 * @function name: void FTM_DRV_PWM_Enable(FTM_Index Count)
 * @description:    开启PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_CCP_PWM_Enable(FTM_Index Count)
{
	FTM_CCP_Type *CCPx = s_FtmCCPBase[Count];

	GPTIM_Cmd(CCPx,TRUE);
}

/***********************************************************************************************
 * @function name: void FTM_DRV_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:    初始化增强型PWM
 * PWM频率 f= clkSource/((Prescaler+1)*TimeCnt)
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
{
	FTM_ECCP_Type* ECCPx = s_FtmECCPBase[User_CCPCfg->CCPIndex];
	uint32_t  Clock_Source = s_ECCPCLK[User_CCPCfg->clkSource];
	uint16_t Channl = s_FtmECCPChannl[User_CCPCfg->ChannlIndex];
	uint32_t TimeCnt = User_CCPCfg->TimeCnt;
	uint16_t Prescaler = User_CCPCfg->Prescaler;
	uint32_t Duty = 0;

	DEV_ASSERT(User_CCPCfg->ChannlIndex < FTM_CHANNL_COUNT);

	Duty =  FTM_DRV_PWMDutyCal(TimeCnt,User_CCPCfg->Duty);

	if(User_CCPCfg->ChannlIndex < FTM_CHANNL_4)
	{
		ECCPx = s_FtmECCPBase[0];
	}
	else if(FTM_CHANNL_4 == User_CCPCfg->ChannlIndex)
	{
		ECCPx = s_FtmECCPBase[1];
	}
	else
	{
		return;
	}

	TIM_Reset(ECCPx);
    /* PWM free mode */
    ECCP_PWM_Mode_Config(ECCPx, ECCP_PWM_FREE);
    /* Independent output mode  */
    ECCP_Channel_Output_Mode(ECCPx, Channl, ECCP_OUTPUT_INDEPENDENT);

    /* Prohibit automatic shutdown  */
    ECCP_Channel_Shutdown_Signal(ECCPx, Channl, ECCP_CHANNEL_SHUTDOWN_FORBID);

    /* Enable automatic restart  */
    ECCP_PWM_Restart_Enable(ECCPx, TRUE);

    /* Enable phase shift  */
    ECCP_PWM_Move_Phase_Enable(ECCPx, TRUE);

    /* PWM output, high effective  */
    ECCP_Channel_Output_Control(ECCPx, Channl, ECCP_PORT_HIGH, ECCP_CHANNEL_OUTPUT_PWM_ACTIVE);

    /* PWM duty cycle  */
    ECCP_Set_Compare_Result(ECCPx, Channl, Duty);

	if(User_CCPCfg->ChannlIndex < FTM_CHANNL_4)
	{
		/* Timing mode */
		ATIM_X_Work_Mode_Config(ECCPx, ATIM_TIMER_MODE);
		/* Count value is cleared to 0  */
		ATIM_X_Set_Counter(ECCPx, 0);
		/* Period value */
		ATIM_X_Set_Period(ECCPx, TimeCnt);
		/* Prescaler 1:1  */
		ATIM_X_Set_Prescaler(ECCPx, Prescaler);
		/* The post-divider ratio is 1:1  */
		ATIM_X_Postscaler_Config(ECCPx, ATIM_POSTSCALER_DIV_1);
		/* Center-aligned PWM signal, counts up, and generates an interrupt flag when it overflows */
		ATIM_X_Counter_Mode_Config(ECCPx, ATIM_COUNT_UP_OF);
		/* Choose HFCLK clock as Tx working clock  */
		ATIM_X_Clock_Config(ECCPx, Clock_Source);
		/* Enable immediate update  */
		ATIM_X_Updata_Immediately_Config(ECCPx, TRUE);

		/* Immediately update the output control register with Tx as the time base  */
		ATIM_X_Updata_Output_Ctl(ECCPx, TRUE);
		/* Allow to change related configuration information with Tx as the time base  */
		ATIM_X_Updata_Enable(ECCPx, TRUE);
		/* Tx start control enable  */
		ATIM_X_Cmd(ECCPx, FALSE);
	}
	else
	{
		/* Timing mode */
		ATIM_Z_Work_Mode_Config(ECCPx, ATIM_TIMER_MODE);
		/* Count value is cleared to 0  */
		ATIM_Z_Set_Counter(ECCPx, 0);
		/* Period value */
		ATIM_Z_Set_Period(ECCPx, TimeCnt);
		/* Prescaler 1:1  */
		ATIM_Z_Set_Prescaler(ECCPx, Prescaler);
		/* The post-divider ratio is 1:1  */
		ATIM_Z_Postscaler_Config(ECCPx, ATIM_POSTSCALER_DIV_1);
		/* Center-aligned PWM signal, counts up, and generates an interrupt flag when it overflows */
		ATIM_Z_Counter_Mode_Config(ECCPx, ATIM_COUNT_UP_OF);
		/* Choose HFCLK clock as Tx working clock  */
		ATIM_Z_Clock_Config(ECCPx, Clock_Source);
		/* Enable immediate update  */
		ATIM_Z_Updata_Immediately_Config(ECCPx, TRUE);

		/* Immediately update the output control register with Tx as the time base  */
		ATIM_Z_Updata_Output_Ctl(ECCPx, TRUE);
		/* Allow to change related configuration information with Tx as the time base  */
		ATIM_Z_Updata_Enable(ECCPx, TRUE);
		/* Tx start control enable  */
		ATIM_Z_Cmd(ECCPx, FALSE);
	}

}

/***********************************************************************************************
 * @function name: void FTM_DRV_UpdatePWMDuty(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:   修改增强型PWM占空比
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_UpdateECCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg)
{
	FTM_ECCP_Type *ECCPx = s_FtmECCPBase[User_CCPCfg->CCPIndex];
	uint16_t Channl = s_FtmECCPChannl[User_CCPCfg->ChannlIndex];
	uint32_t Duty = 0;

	Duty =  FTM_DRV_PWMDutyCal(User_CCPCfg->TimeCnt,User_CCPCfg->Duty);

	/* PWM duty cycle  */
	ATIM_X_Cmd(ECCPx, FALSE);
	ATIM_X_Updata_Immediately_Config(ECCPx,FALSE);
	ATIM_X_Updata_Immediately_Config(ECCPx,TRUE);
	ECCP_Set_Compare_Result(ECCPx, Channl, Duty);
	ATIM_X_Cmd(ECCPx, TRUE);
}

/***********************************************************************************************
 * @function name: void FTM_DRV_ECCP_PWM_Disable(FTM_ChannlIndex Count)
 * @description:    关闭PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_ECCP_PWM_Disable(FTM_ChannlIndex Count)
{
	FTM_ECCP_Type *ECCPx ;

	if(Count < FTM_CHANNL_4)
	{
		ECCPx = s_FtmECCPBase[0];
		ATIM_X_Cmd(ECCPx,FALSE);
	}
	else if(FTM_CHANNL_4 == Count)
	{
		ECCPx = s_FtmECCPBase[1];
		ATIM_Z_Cmd(ECCPx,FALSE);
	}
	else
	{
		return;
	}
}

/***********************************************************************************************
 * @function name: void FTM_DRV_ECCP_PWM_Enable(FTM_ChannlIndex Count)
 * @description:    开启PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void FTM_DRV_ECCP_PWM_Enable(FTM_ChannlIndex Count)
{
	FTM_ECCP_Type *ECCPx ;

	if(Count < FTM_CHANNL_4)
	{
		ECCPx = s_FtmECCPBase[0];
		ATIM_X_Cmd(ECCPx,TRUE);
	}
	else if(FTM_CHANNL_4 == Count)
	{
		ECCPx = s_FtmECCPBase[1];
		ATIM_Z_Cmd(ECCPx,TRUE);
	}
	else
	{
		return;
	}
}

