#ifndef _ECUAL_FTM_H_
#define _ECUAL_FTM_H_

#include "ftm_driver.h"
#include "Common.h"



/*通风频率为100Hz Prescaler  = 15*/
#define  D_Ventilate_FREQUENCY    	100
/*主驾用的是CCP3，通道4*/
#define  D_Dr_Ventilate_CCP   		FTM_INSTANCE_3
#define  D_Dr_Ventilate_CH   		FTM_CHANNL_4
/*副驾用的是CCP3，通道3*/
#define  D_Pa_Ventilate_CCP   		FTM_INSTANCE_3
#define  D_Pa_Ventilate_CH   		FTM_CHANNL_3

/*预驱1 PWM1 - PIN1 CCP18 CH1*/
#define  D_9210X_1_PWM1_CCP   		FTM_INSTANCE_5
#define  D_9210X_1_PWM1_CH   		FTM_CHANNL_1
/*预驱1 PWM2 - PIN2 CCP18 CH2*/
#define  D_9210X_1_PWM2_CCP   		FTM_INSTANCE_5
#define  D_9210X_1_PWM2_CH   		FTM_CHANNL_2
/*预驱1 PWM3 - PIN3 CCP18 CH3*/
#define  D_9210X_1_PWM3_CCP   		FTM_INSTANCE_5
#define  D_9210X_1_PWM3_CH   		FTM_CHANNL_3
/*预驱1 PWM4 - PIN4 CCP18 CH4*/
#define  D_9210X_1_PWM4_CCP   		FTM_INSTANCE_5
#define  D_9210X_1_PWM4_CH   		FTM_CHANNL_4

/*预驱2 PWM1 - PIN17 CCP1 CH3*/
#define  D_9210X_2_PWM1_CCP   		FTM_INSTANCE_1
#define  D_9210X_2_PWM1_CH   		FTM_CHANNL_3
/*预驱2 PWM2 - PIN18 CCP1 CH4*/
#define  D_9210X_2_PWM2_CCP   		FTM_INSTANCE_1
#define  D_9210X_2_PWM2_CH   		FTM_CHANNL_4
/*预驱2 PWM3 - PIN19 CCP0 CH1*/
#define  D_9210X_2_PWM3_CCP   		FTM_INSTANCE_0
#define  D_9210X_2_PWM3_CH   		FTM_CHANNL_1
/*预驱2 PWM4 - PIN40 CCP1 CH1*/
#define  D_9210X_2_PWM4_CCP   		FTM_INSTANCE_1
#define  D_9210X_2_PWM4_CH   		FTM_CHANNL_1

typedef struct
{
    INT32U TimeCnt;
    FTM_Index Index;
    FTM_ChannlIndex Channel;
}stFtmCcpStsType;

typedef enum
{
    EN_CCP_DR_VENT,
    EN_CCP_PA_VENT,
    EN_CCP_9210X_1_1,
    EN_CCP_9210X_1_2,
    EN_CCP_9210X_1_3,
    EN_CCP_9210X_1_4,
    EN_CCP_9210X_2_1,
    EN_CCP_9210X_2_2,
    EN_CCP_9210X_2_3,
    EN_CCP_9210X_2_4,
    EN_CPP_MAX,
}en_FtmCcpChannelType;

extern void Ecual_FTM_CCP_PWM_Init(void);
extern void Ecual_FTM_CCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty);
extern void Ecual_FTM_CCP_PWM_Disable(FTM_Index Count);
extern void Ecual_FTM_CCP_PWM_Enable(FTM_Index Count);

extern void Ecual_FTM_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void Ecual_FTM_ECCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty);
extern void Ecual_FTM_ECCP_PWM_Disable(FTM_Index Count);
extern void Ecual_FTM_ECCP_PWM_Enable(FTM_Index Count);

extern void Ecual_UpDateDrVentDuty(uint8_t Duty);
extern void Ecual_UpDatePaVentDuty(uint8_t Duty);
extern void Ecual_UpDatePwmDuty(en_FtmCcpChannelType Ch,uint8_t Duty);
#endif /* ECUAL_FTM_H_ */
