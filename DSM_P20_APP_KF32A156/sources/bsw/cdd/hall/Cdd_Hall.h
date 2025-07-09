/*
 * Cdd_Hall.h
 *
 *  Created on: 2025-3-18
 *      Author: Administrator
 */

#ifndef Cdd_HALL_H_
#define Cdd_HALL_H_

#include "Common.h"

typedef INT8U(*MotorFun)(void);	  /* Pointer to Functions, INT8U argument */

#define HALL_KEEP_TIME_MS   100  // 电机停止后继续采集时间 需要与调度周期关联


typedef enum _AD_SEAT_SWITCH
{
	EN_DriverHeight = 0,	/*主驾高度*/
	EN_DriverLength,	/*主驾纵向*/
	EN_DriverBack,		/*主驾靠背*/
	EN_DriverFront,		/*主驾腿托*/

	EN_PassengerLength,	/*副驾纵向*/
	EN_PassengerBack,	/*副驾靠背*/
	EN_SeatSwitchMax,
	EN_PaResever_1,
	EN_PaResever_2,

}enSWITCH;

#define 	D_HALLTIME                (10UL)
#define		D_POSI		 			  (100u)

#define 	MotorHallMax  (65535UL)
#define 	MotorHallMin  (0UL)
#define 	D_ADC_HALL_DEF  (30000UL)

#define     HALLERRTIME                (34UL)
#define 	HALLNORTIME                (10UL)

typedef struct ADCHALLDATA
{
	INT16U HallPwmCnt[EN_SeatSwitchMax];  //当前记录的PWM数、位置相关
	INT16U StopPosCnt[EN_SeatSwitchMax];  //电机导轨长度PWM数
	INT16U HardStopPos[EN_SeatSwitchMax]; //电机的硬止点位置（下、后、靠后）
	INT16U PreHardStopPos[EN_SeatSwitchMax]; //上一次电机的硬止点位置（下、后、靠后）
}strADCHALLDATA;

typedef struct HALLERR
{
	INT8U HallErrCnt[EN_SeatSwitchMax];  //无HALL计时
	BOOL HallErrFlg[EN_SeatSwitchMax];  //无HALL标志
	INT8U HallNorCnt[EN_SeatSwitchMax];  //HALL正常工作计时
	BOOL HallNorFlg[EN_SeatSwitchMax];  //HALL正常工作标志
}strHALLERR;
/*--------------ADC霍尔采样数值处理------------------*/

extern strHALLERR HallErr;
extern strADCHALLDATA HallDataHandle;

extern strADCHALLDATA Cdd_HallDataGet(void);
extern INT16U Cdd_GetSeatPosi(enSWITCH chl,INT16U Precent);

//模型使用
extern INT16U Cdd_GetCurrentHallCnt(enSWITCH Posi);
extern INT16U Cdd_GetMotorSize(enSWITCH Posi);
extern INT16U Cdd_GetMotorHardStop(enSWITCH Posi);
extern BOOL Cdd_GetMotorLearnFlag(enSWITCH Posi);
extern void Cdd_ReadAllHallFromE2(void);
extern void Cdd_ClearPassengerHardStopData(void);
extern void Cdd_ClearDriverHardStopData(void);
extern void Cdd_HallDmaHandler(void);
extern void Ecual_HandleHallAndTriggerAdc(void);
extern BOOL Cdd_IsHallAllStop(void);


#endif /* Cdd_HALL_H_ */
