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

#define HALL_KEEP_TIME_MS   100  // ���ֹͣ������ɼ�ʱ�� ��Ҫ��������ڹ���


typedef enum _AD_SEAT_SWITCH
{
	EN_DriverHeight = 0,	/*���ݸ߶�*/
	EN_DriverLength,	/*��������*/
	EN_DriverBack,		/*���ݿ���*/
	EN_DriverFront,		/*��������*/

	EN_PassengerLength,	/*��������*/
	EN_PassengerBack,	/*���ݿ���*/
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
	INT16U HallPwmCnt[EN_SeatSwitchMax];  //��ǰ��¼��PWM����λ�����
	INT16U StopPosCnt[EN_SeatSwitchMax];  //������쳤��PWM��
	INT16U HardStopPos[EN_SeatSwitchMax]; //�����Ӳֹ��λ�ã��¡��󡢿���
	INT16U PreHardStopPos[EN_SeatSwitchMax]; //��һ�ε����Ӳֹ��λ�ã��¡��󡢿���
}strADCHALLDATA;

typedef struct HALLERR
{
	INT8U HallErrCnt[EN_SeatSwitchMax];  //��HALL��ʱ
	BOOL HallErrFlg[EN_SeatSwitchMax];  //��HALL��־
	INT8U HallNorCnt[EN_SeatSwitchMax];  //HALL����������ʱ
	BOOL HallNorFlg[EN_SeatSwitchMax];  //HALL����������־
}strHALLERR;
/*--------------ADC����������ֵ����------------------*/

extern strHALLERR HallErr;
extern strADCHALLDATA HallDataHandle;

extern strADCHALLDATA Cdd_HallDataGet(void);
extern INT16U Cdd_GetSeatPosi(enSWITCH chl,INT16U Precent);

//ģ��ʹ��
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
