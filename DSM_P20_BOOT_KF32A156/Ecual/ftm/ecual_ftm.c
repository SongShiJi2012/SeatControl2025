/*
 * ecual_ftm.c
 *
 *  Created on: 2022-12-19
 *      Author: Administrator
 */
#include "ecual_ftm.h"
#include "devassert.h"
#include <string.h>

FTM_CCP_user_config_t s_User_CCPCfg[GCCP_INSTANCE_COUNT];
FTM_CCP_user_config_t s_User_ECCPCfg[ECCP_INSTANCE_COUNT];
/***********************************************************************************************
 * @function name: Ecual_FTM_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:    初始化PWM
 * PWM频率 f=clkSource/((Prescaler+1)*TimeCnt)
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
{
	 uint8_t Index = User_CCPCfg->CCPIndex;
	 FTM_CCP_user_config_t* pSerSetCCPCfg = &s_User_CCPCfg[Index];

	 memcpy(pSerSetCCPCfg,User_CCPCfg,sizeof(FTM_CCP_user_config_t));

	 //DEV_ASSERT(pSerSetCCPCfg != NULL);

	 FTM_DRV_CCP_PWM_Init(pSerSetCCPCfg);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_CCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty)
 * @description:   修改PWM占空比
 * @input parameters:      Index
 * 						Duty
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_CCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty)
{
	FTM_CCP_user_config_t* pSerSetCCPCfg = &s_User_CCPCfg[Index];

	pSerSetCCPCfg->Duty = Duty;
	FTM_DRV_UpdateCCPPWMDuty(pSerSetCCPCfg);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_CCP_PWM_Disable(FTM_Index Count)
 * @description:    关闭PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_CCP_PWM_Disable(FTM_Index Count)
{
	FTM_DRV_CCP_PWM_Disable(Count);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_CCP_PWM_Enable(FTM_Index Count)
 * @description:    开启PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_CCP_PWM_Enable(FTM_Index Count)
{
	FTM_DRV_CCP_PWM_Enable(Count);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
 * @description:    初始化增强型PWM
 * PWM频率 f=clkSource/((Prescaler+1)*TimeCnt)
 * @input parameters:      User_CCPCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg)
{
	uint8_t ChannlIndex = User_CCPCfg->ChannlIndex;
	uint8_t Index = User_CCPCfg->CCPIndex;
	FTM_CCP_user_config_t* pSerSetECCPCfg;

	if((ChannlIndex < FTM_CHANNL_4) && (Index == FTM_INSTANCE_0))
	{
		pSerSetECCPCfg = &s_User_ECCPCfg[0];
	}
	else if((FTM_CHANNL_4 == ChannlIndex)  && (Index == FTM_INSTANCE_0))
	{
		pSerSetECCPCfg = &s_User_ECCPCfg[1];
	}
	else
	{
		return;
	}

	memcpy(pSerSetECCPCfg,User_CCPCfg,sizeof(FTM_CCP_user_config_t));

	//DEV_ASSERT(pSerSetECCPCfg != NULL);
	FTM_DRV_ECCP_PWM_Init(pSerSetECCPCfg);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_ECCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty)
 * @description:   修改增强PWM占空比
 * @input parameters:      Index
 * 						Duty
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_ECCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty)
{
	FTM_CCP_user_config_t* pSerSetECCPCfg = &s_User_ECCPCfg[Index];

	pSerSetECCPCfg->Duty = Duty;
	FTM_DRV_UpdateECCPPWMDuty(pSerSetECCPCfg);
}


/***********************************************************************************************
 * @function name: void Ecual_FTM_ECCP_PWM_Disable(FTM_Index Count)
 * @description:    关闭增强PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_ECCP_PWM_Disable(FTM_Index Count)
{
	FTM_CCP_user_config_t* pSerSetECCPCfg = &s_User_ECCPCfg[Count];

	FTM_DRV_ECCP_PWM_Disable(pSerSetECCPCfg->ChannlIndex);
}

/***********************************************************************************************
 * @function name: void Ecual_FTM_ECCP_PWM_Enable(FTM_Index Count)
 * @description:    开启增强PWM
 * @input parameters:      Count
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-19 czb
 ***********************************************************************************************/
void Ecual_FTM_ECCP_PWM_Enable(FTM_Index Count)
{
	FTM_CCP_user_config_t* pSerSetECCPCfg = &s_User_ECCPCfg[Count];

	FTM_DRV_ECCP_PWM_Enable(pSerSetECCPCfg->ChannlIndex);
}
