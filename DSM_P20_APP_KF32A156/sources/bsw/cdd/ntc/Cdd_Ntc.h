/*
 * Cdd_Ntc.h
 *
 *  Created on: 2025-3-20
 *      Author: Administrator
 */

#ifndef Cdd_NTC_H_
#define Cdd_NTC_H_

#include  "Common.h"




#define TEMP_STABLE_SIZE    (sizeof(TempSeatAdTable)/sizeof(INT16U))
#define TEMP_WTABLE_SIZE    (sizeof(TempWheelAdTable)/sizeof(INT16U))

#define SEQ_RISING        (0UL)        //����
#define SEQ_LOWER         (1UL)        //����
#define AD_NEW_HARD    	(500UL)/*�¾ɰ汾Ӳ������  ���䰴�����ɰ汾����Ƭ AD 3000 +   �°汾����Ƭ AD 50+*/
typedef enum
{
	EN_AD_DrOld = 0,	//���ݾ�Ӳ��
	EN_AD_DrNew,		//������Ӳ��
	EN_AD_PaOld,		//���ݾ�Ӳ��
	EN_AD_PaNew,		//���ݾ�Ӳ��
}EN_SeatADType;

typedef     struct
{
	INT16U	SeatHeatDRNtc;							/*�����μ��ȷ����¶�*/
	INT16U 	SeatHeatPANtc;						    /*�����μ��ȷ����¶�*/
	INT16U	WheelHeatNtc;						    /*�����̼��ȷ����¶�*/
}ST_ScanTempVal;


extern INT16U Cdd_Ntc_GetSeatAd(EN_SeatADType AdType, INT8U index);
extern void Cdd_Ntc_Task(void);
extern ST_ScanTempVal Cdd_Ntc_GetTemp(void);



#endif /* Cdd_NTC_H_ */
