/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @file ftm_pwm_driver.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

#ifndef FTM_DRIVER_H
#define FTM_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "status.h"
#include "stdbool.h"
#include "kf32a156.h"
#include "kf32a156_atim.h"
#include "kf32a156_gtim.h"


typedef CCP_SFRmap FTM_CCP_Type;
typedef ECCP_SFRmap FTM_ECCP_Type;

typedef enum
{
	FTM_INSTANCE_0 = 0,
	FTM_INSTANCE_1,
	FTM_INSTANCE_2,
	FTM_INSTANCE_3,
	FTM_INSTANCE_4,
	FTM_INSTANCE_5,
	FTM_INSTANCE_6,
	FTM_INSTANCE_7,
	FTM_INSTANCE_COUNT,
}FTM_Index;

typedef enum
{
	FTM_CHANNL_1 = 0,
	FTM_CHANNL_2,
	FTM_CHANNL_3,
	FTM_CHANNL_4,
	FTM_CHANNL_COUNT,
}FTM_ChannlIndex;

/*捕获/比较/PWM*/
#define GCCP_INSTANCE_COUNT                     (8u)
#define GCCP0                                     (CCP0_SFR)
#define GCCP1                                     (CCP1_SFR)
#define GCCP2                                     (CCP2_SFR)
#define GCCP3                                     (CCP3_SFR)
#define GCCP4                                     (CCP4_SFR)
#define GCCP5                                     (CCP18_SFR)
#define GCCP6                                     (CCP19_SFR)
#define GCCP7                                     (CCP21_SFR)

#define FTM_GCCP_BASE_PTRS    {GCCP0,GCCP1,GCCP2,GCCP3,GCCP4,GCCP5,GCCP6,GCCP7}

#define FTM_GCCP_CHANNEL_PTRS    {CCP_CHANNEL_1,CCP_CHANNEL_2,CCP_CHANNEL_3,CCP_CHANNEL_4}

/*增强型捕获/比较/PWM */
/*通道1/2/3用定时器5，通道4用的是定时器6；使用时 需要定时器和通道号需要对应*/
#define ECCP_INSTANCE_COUNT                     (2u)
#define ECCP0                                   (ECCP5_SFR)
#define ECCP1                                   (ECCP6_SFR)

#define FTM_ECCP_BASE_PTRS    {ECCP0,ECCP1}

#define FTM_ECCP_CHANNEL_PTRS    {ECCP_CHANNEL_1,ECCP_CHANNEL_2,ECCP_CHANNEL_3,ECCP_CHANNEL_4}


/*目前只支持系统时钟和外部高速时钟*/
typedef enum
{
    FTM_CLOCK_SOURCE_SYSCLK,
    FTM_CLOCK_SOURCE_HFCLK,
    FTM_CLOCK_SOURCE_LFCLK,
    FTM_CLOCK_SOURCE_INTLFT0,
    FTM_CLOCK_SOURCE_COUNT
} ftm_clock_source_t;

/*PWM频率 T= clkSource/((Prescaler+1)*TimeCnt)*/
typedef struct
{
	FTM_Index          CCPIndex;    /*CCP索引*/
	FTM_ChannlIndex    ChannlIndex;   /*通道号*/
	ftm_clock_source_t    clkSource;  /*时钟源*/
    uint16_t             Prescaler;  /*分频系数*/
    uint32_t             TimeCnt;  /*次数*/
    uint8_t             Duty;  /*占空比 0-100%*/
} FTM_CCP_user_config_t;


extern void FTM_DRV_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_UpdateCCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_CCP_PWM_Disable(FTM_Index Count);
extern void FTM_DRV_CCP_PWM_Enable(FTM_Index Count);

extern void FTM_DRV_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_UpdateECCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_ECCP_PWM_Disable(FTM_ChannlIndex Count);
extern void FTM_DRV_ECCP_PWM_Enable(FTM_ChannlIndex Count);

#endif
