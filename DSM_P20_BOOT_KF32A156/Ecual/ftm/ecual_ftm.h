/*
 * ecual_ftm.h
 *
 *  Created on: 2022-12-19
 *      Author: Administrator
 */

#ifndef ECUAL_FTM_H_
#define ECUAL_FTM_H_

#include "ftm_driver.h"

extern void Ecual_FTM_CCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void Ecual_FTM_CCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty);
extern void Ecual_FTM_CCP_PWM_Disable(FTM_Index Count);
extern void Ecual_FTM_CCP_PWM_Enable(FTM_Index Count);

extern void Ecual_FTM_ECCP_PWM_Init(FTM_CCP_user_config_t* User_CCPCfg);
extern void Ecual_FTM_ECCP_PWM_UpDateDuty(FTM_Index Index, uint8_t Duty);
extern void Ecual_FTM_ECCP_PWM_Disable(FTM_Index Count);
extern void Ecual_FTM_ECCP_PWM_Enable(FTM_Index Count);

#endif /* ECUAL_FTM_H_ */
