#ifndef _FTM_DRIVER_H_
#define _FTM_DRIVER_H_

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

/*����/�Ƚ�/PWM*/
#define D_GCCP_INSTANCE_COUNT                     (8u)
#define D_GCCP0                                     (CCP0_SFR)
#define D_GCCP1                                     (CCP1_SFR)
#define D_GCCP2                                     (CCP2_SFR)
#define D_GCCP3                                     (CCP3_SFR)
#define D_GCCP4                                     (CCP4_SFR)
#define D_GCCP5                                     (CCP18_SFR)
#define D_GCCP6                                     (CCP19_SFR)
#define D_GCCP7                                     (CCP21_SFR)

#define D_FTM_GCCP_BASE_PTRS    {D_GCCP0,D_GCCP1,D_GCCP2,D_GCCP3,D_GCCP4,D_GCCP5,D_GCCP6,D_GCCP7}

#define D_FTM_GCCP_CHANNEL_PTRS    {CCP_CHANNEL_1,CCP_CHANNEL_2,CCP_CHANNEL_3,CCP_CHANNEL_4}

/*��ǿ�Ͳ���/�Ƚ�/PWM */
/*ͨ��1/2/3�ö�ʱ��5��ͨ��4�õ��Ƕ�ʱ��6��ʹ��ʱ ��Ҫ��ʱ����ͨ������Ҫ��Ӧ*/
#define D_ECCP_INSTANCE_COUNT                     (2u)
#define D_ECCP0                                   (ECCP5_SFR)
#define D_ECCP1                                   (ECCP6_SFR)

#define D_FTM_ECCP_BASE_PTRS    {D_ECCP0,D_ECCP1}

#define D_FTM_ECCP_CHANNEL_PTRS    {ECCP_CHANNEL_1,ECCP_CHANNEL_2,ECCP_CHANNEL_3,ECCP_CHANNEL_4}


/*Ŀǰֻ֧��ϵͳʱ�Ӻ��ⲿ����ʱ��*/
typedef enum
{
    FTM_CLOCK_SOURCE_SYSCLK,
    FTM_CLOCK_SOURCE_HFCLK,
    FTM_CLOCK_SOURCE_LFCLK,
    FTM_CLOCK_SOURCE_INTLFT0,
    FTM_CLOCK_SOURCE_COUNT
} ftm_clock_source_t;

/*PWMƵ�� T= clkSource/((Prescaler+1)*TimeCnt)*/
typedef struct
{
	FTM_Index          CCPIndex;    /*CCP����*/
	FTM_ChannlIndex    ChannlIndex;   /*ͨ����*/
	ftm_clock_source_t    clkSource;  /*ʱ��Դ*/
    uint16_t             Prescaler;  /*��Ƶϵ��*/
    uint32_t             TimeCnt;  /*����*/
    uint8_t             Duty;  /*ռ�ձ� 0-100%*/
} FTM_CCP_user_config_t;


extern void FTM_DRV_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern  void FTM_DRV_CCP_PWM_OutControl(FTM_CCP_user_config_t* User_CCPCfg,uint32_t ChannelOutputCtl);
extern void FTM_DRV_UpdateCCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_CCP_PWM_Disable(FTM_Index Count);
extern void FTM_DRV_CCP_PWM_Enable(FTM_Index Count);

extern void FTM_DRV_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_UpdateECCPPWMDuty(FTM_CCP_user_config_t* User_CCPCfg);
extern void FTM_DRV_ECCP_PWM_Disable(FTM_ChannlIndex Count);
extern void FTM_DRV_ECCP_PWM_Enable(FTM_ChannlIndex Count);

#endif
