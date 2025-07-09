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

#define SEQ_RISING        (0UL)        //升序
#define SEQ_LOWER         (1UL)        //降序
#define AD_NEW_HARD    	(500UL)/*新旧版本硬件区分  记忆按键：旧版本有贴片 AD 3000 +   新版本无贴片 AD 50+*/
typedef enum
{
	EN_AD_DrOld = 0,	//主驾旧硬件
	EN_AD_DrNew,		//主驾新硬件
	EN_AD_PaOld,		//副驾旧硬件
	EN_AD_PaNew,		//副驾旧硬件
}EN_SeatADType;

typedef     struct
{
	INT16U	SeatHeatDRNtc;							/*主座椅加热反馈温度*/
	INT16U 	SeatHeatPANtc;						    /*主座椅加热反馈温度*/
	INT16U	WheelHeatNtc;						    /*方向盘加热反馈温度*/
}ST_ScanTempVal;


extern INT16U Cdd_Ntc_GetSeatAd(EN_SeatADType AdType, INT8U index);
extern void Cdd_Ntc_Task(void);
extern ST_ScanTempVal Cdd_Ntc_GetTemp(void);



#endif /* Cdd_NTC_H_ */
