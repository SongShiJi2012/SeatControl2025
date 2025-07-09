/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               ecual_ftm.c
** Created By:              chenzibo
** Created date:            2022.12.27
** Version:                 V1.0
** Descriptions:
**
**------------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
**************************************************************************************************/
#include "ecual_ftm.h"
#include "devassert.h"
#include <string.h>
#include "kf32a156_gtim.h"

static FTM_CCP_user_config_t s_User_CCPCfg[D_GCCP_INSTANCE_COUNT];
static FTM_CCP_user_config_t s_User_ECCPCfg[D_ECCP_INSTANCE_COUNT];

const stFtmCcpStsType s_FtmCcpSts[EN_CPP_MAX] = {
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_3,FTM_CHANNL_4},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_3,FTM_CHANNL_3},
    
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_1,FTM_CHANNL_3},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_1,FTM_CHANNL_4},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_0,FTM_CHANNL_1},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_1,FTM_CHANNL_1},
    
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_5,FTM_CHANNL_1},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_5,FTM_CHANNL_2},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_5,FTM_CHANNL_3},
    {D_Ventilate_FREQUENCY,FTM_INSTANCE_5,FTM_CHANNL_4},
    
};

/***********************************************************************************************
 * @function name:  Ecual_FTM_CCP_PWM_9210X_Init
 * @description:    PWM 初始化
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
 static void Ecual_FTM_CCP_PWM_9210X_1_Init(void)
{
    FTM_CCP_user_config_t User_PWMCfg;

    User_PWMCfg.clkSource = FTM_CLOCK_SOURCE_HFCLK;
    User_PWMCfg.Prescaler = 150;
    User_PWMCfg.TimeCnt = D_Ventilate_FREQUENCY;

    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_1_3].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_1_3].Channel;
    User_PWMCfg.Duty = 100; //默认均拉高-刹车模式下，可均拉低边mos
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_1_3].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_1_1].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_1_1].Channel;
    User_PWMCfg.Duty = 100; 
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_1_1].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_1_2].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_1_2].Channel;
    User_PWMCfg.Duty = 100; 
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_1_2].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_1_4].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_1_4].Channel;
    User_PWMCfg.Duty = 100; //起始为EN脚，需要拉高
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_1_4].Index);
}

/***********************************************************************************************
 * @function name:  Ecual_FTM_CCP_PWM_9210X_Init
 * @description:    PWM 初始化
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
static void Ecual_FTM_CCP_PWM_9210X_2_Init(void)
{
    FTM_CCP_user_config_t User_PWMCfg;

    User_PWMCfg.clkSource = FTM_CLOCK_SOURCE_HFCLK;
    User_PWMCfg.Prescaler = 150;
    User_PWMCfg.TimeCnt = D_Ventilate_FREQUENCY;
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_2_1].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_2_1].Channel;
    User_PWMCfg.Duty = 100; 
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_2_1].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_2_2].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_2_2].Channel;
    User_PWMCfg.Duty = 100; 
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_2_2].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_2_3].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_2_3].Channel;
    User_PWMCfg.Duty = 100; 
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_2_3].Index);
    
    User_PWMCfg.CCPIndex = s_FtmCcpSts[EN_CCP_9210X_2_4].Index;
    User_PWMCfg.ChannlIndex = s_FtmCcpSts[EN_CCP_9210X_2_4].Channel;
    User_PWMCfg.Duty = 100; //起始为EN脚，需要拉高
    FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
    Ecual_FTM_CCP_PWM_Enable(s_FtmCcpSts[EN_CCP_9210X_2_4].Index);
}

/***********************************************************************************************
 * @function name:  Ecual_FTM_CCP_PWM_Init
 * @description:    PWM 初始化函数，配置通风电机 PWM 输出参数并使能
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Ecual_FTM_CCP_PWM_Init(void)
{
	FTM_CCP_user_config_t User_PWMCfg;

	// 通风电机的控制信号以低边PWM输出，通风频率为100Hz，误差范围为±10%
	User_PWMCfg.clkSource = FTM_CLOCK_SOURCE_HFCLK;
	User_PWMCfg.Prescaler = 15;
	User_PWMCfg.TimeCnt = D_Ventilate_FREQUENCY;
	// 主驾通风初始化/*主驾用的是CCP3，通道4*/
	User_PWMCfg.CCPIndex = D_Dr_Ventilate_CCP;
	User_PWMCfg.ChannlIndex = D_Dr_Ventilate_CH;
	User_PWMCfg.Duty = 0; /*低有效，配置100%，输出全为高*/
	FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
	Ecual_FTM_CCP_PWM_Enable(D_Dr_Ventilate_CCP);
	// 副驾通风初始化/*副驾用的是CCP3，通道3*/
	User_PWMCfg.CCPIndex = D_Pa_Ventilate_CCP;
	User_PWMCfg.ChannlIndex = D_Pa_Ventilate_CH;
	User_PWMCfg.Duty = 0; /*低有效，配置100%，输出全为高*/
	FTM_DRV_CCP_PWM_Init(&User_PWMCfg);
	Ecual_FTM_CCP_PWM_Enable(D_Pa_Ventilate_CCP);

    Ecual_FTM_CCP_PWM_9210X_1_Init();
    Ecual_FTM_CCP_PWM_9210X_2_Init();
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
 * @function name:  Ecual_UpDateDrVentDuty
 * @description:    更新主驾通风 PWM 占空比
 * @input parameters:     uint8_t Duty
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Ecual_UpDateDrVentDuty(uint8_t Duty)
{
	FTM_CCP_user_config_t pSerSetCCPCfg;

	pSerSetCCPCfg.Duty = Duty;
	pSerSetCCPCfg.TimeCnt = D_Ventilate_FREQUENCY;
	pSerSetCCPCfg.CCPIndex = D_Dr_Ventilate_CCP;
	pSerSetCCPCfg.ChannlIndex = D_Dr_Ventilate_CH;
	FTM_DRV_UpdateCCPPWMDuty(&pSerSetCCPCfg);
}

/***********************************************************************************************
 * @function name:  Ecual_UpDatePwmDuty
 * @description:     PWM 占空比
 * @input parameters:     uint8_t Duty
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Ecual_UpDatePwmDuty(en_FtmCcpChannelType Ch,uint8_t Duty)
{
    FTM_CCP_user_config_t pSerSetCCPCfg;

    if(Ch >= EN_CPP_MAX)
    {
        return;
    }

    pSerSetCCPCfg.Duty = Duty;
    pSerSetCCPCfg.TimeCnt = D_Ventilate_FREQUENCY;
    pSerSetCCPCfg.CCPIndex = s_FtmCcpSts[Ch].Index;
    pSerSetCCPCfg.ChannlIndex = s_FtmCcpSts[Ch].Channel;

    if(Duty >= 100)
    {
        FTM_DRV_CCP_PWM_OutControl(&pSerSetCCPCfg,CCP_CHANNEL_OUTPUT_ACTIVE);
    }
    else
    {
        FTM_DRV_CCP_PWM_OutControl(&pSerSetCCPCfg, CCP_CHANNEL_OUTPUT_PWM_ACTIVE);
        /* PWM duty cycle */
        FTM_DRV_UpdateCCPPWMDuty(&pSerSetCCPCfg);
    }
}

/***********************************************************************************************
 * @function name:  Ecual_UpDatePaVentDuty
 * @description:    更新副驾通风 PWM 占空比
 * @input parameters:     uint8_t Duty
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Ecual_UpDatePaVentDuty(uint8_t Duty)
{
	FTM_CCP_user_config_t pSerSetCCPCfg;

	pSerSetCCPCfg.Duty = Duty;
	pSerSetCCPCfg.TimeCnt = D_Ventilate_FREQUENCY;
	pSerSetCCPCfg.CCPIndex = D_Pa_Ventilate_CCP;
	pSerSetCCPCfg.ChannlIndex = D_Pa_Ventilate_CH;
	FTM_DRV_UpdateCCPPWMDuty(&pSerSetCCPCfg);
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
