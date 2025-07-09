/*
 * Ecual_AdcMotor.h
 *
 *  Created on: 2025-3-26
 *      Author: Administrator
 */
#ifndef ECUAL_ADCMOTOR_H_
#define ECUAL_ADCMOTOR_H_

#include "Common.h"
#define     D_SEAT_SW_LIMIT_VOLTAGE               	(142UL)    /*电压限制*/
#define     D_SEAT_SW_LIMIT_MAX                     (4080UL)   /*有效电压限制*/

#define MOTOR_CURR_MAX_DR_HEIGHT   3300   /* 主驾高度电机堵转电流阈值 */
#define MOTOR_CURR_MAX_DR_LENGTH   3670   /* 主驾纵向电机堵转电流阈值 */
#define MOTOR_CURR_MAX_DR_BACK     2244   /* 主驾靠背电机堵转电流阈值 */
#define MOTOR_CURR_MAX_DR_FRONT    3230   /* 主驾腿托电机堵转电流阈值 */
#define MOTOR_CURR_MAX_PA_LENGTH   3445   /* 副驾纵向电机堵转电流阈值 */
#define MOTOR_CURR_MAX_PA_BACK     3364   /* 副驾靠背电机堵转电流阈值 */


typedef enum
{
	EN_SW_DEF = 0,		/*默认状态*/
	EN_SW_UP_FW_LF,		/*上，前，左*/
	EN_SW_DN_BW_RT,		/*下，后，右*/
	EN_SW_ERR,			/*故障*/
}EN_SW_TYPE;

typedef enum
{
	EN_CURR_DEF = 0,		/*默认状态*/
	EN_CURR_NOLMAL,			/*正常在线状态*/
	EN_CURR_ERR,			/*堵转状态*/
}EN_CURR_TYPE;
typedef struct
{
    INT8U MOTOR_CURR_UP_NOLMAL   :1;		/*正常向上在线状态*/
	INT8U MOTOR_CURR_DN_NOLMAL   :1;		/*正常向下在线状态*/
}ST_RelayBits;

typedef union
{
    INT8U Byte;
    ST_RelayBits Bits;
}UN_RelayIOState;
/*输入口扫描*/
typedef struct
{

	EN_SW_TYPE DrHeightSwitch;        /* 主驾高度调节开关输入口  */
	EN_SW_TYPE DrLengthSwitch;        /* 主驾纵向调节开关输入口  */
	EN_SW_TYPE DrBackSwitch;          /* 主驾靠背调节开关输入口  */
	EN_SW_TYPE DrFrontSwitch;         /* 主驾腿托调节开关输入口  */
	EN_SW_TYPE PaLengthSwitch;        /* 副驾纵向调节开关输入口  */
	EN_SW_TYPE PaBackSwitch;          /* 副驾靠背调节开关输入口  */

	BOOL DrHeightOverCurrentFlag;        /* 主驾高度电机电流超过堵转阈值标志位  */
	BOOL DrLengthOverCurrentFlag;        /* 主驾纵向电机电流超过堵转阈值标志位  */
	BOOL DrBackOverCurrentFlag;          /* 主驾靠背电机电流超过堵转阈值标志位  */
	BOOL DrFrontOverCurrentFlag;         /* 主驾腿托电机电流超过堵转阈值标志位  */
	BOOL PaLengthOverCurrentFlag;        /* 副驾纵向电机电流超过堵转阈值标志位  */
	BOOL PaBackOverCurrentFlag;          /* 副驾靠背电机电流超过堵转阈值标志位  */

	BOOL SEAT_HEIGHT_MOTOR_CURR; 				/* 座椅高度电机电流超过堵转阈值标志位 */
	BOOL SEAT_LENGTH_MOTOR_CURR; 				/* 座椅纵向电机电流超过堵转阈值标志位*/
	BOOL SEAT_BACKREST_RECLINE_MOTOR_CURR; 		/* 座椅靠背角度电机电流超过堵转阈值标志位*/
	BOOL SEAT_FRONT_HEIGHT_MOTOR_CURR; 			/* 座椅前部角度电机电流超过堵转阈值标志位*/
	EN_CURR_TYPE SEAT_HEADREST_HEIGHT_MOTOR_CURR; 		/* 座椅头枕高度电机电流超过堵转阈值标志位*/
	EN_CURR_TYPE SEAT_CUSHION_LENGTH_MOTOR_CURR; 		/* 座椅腿部支撑电机电流超过堵转阈值标志位*/

	UN_RelayIOState DrHeightRelayDriveSts; 				/* 主驾高度电机继电器驱动状态*/
	UN_RelayIOState DrLengthRelayDriveSts; 				/* 主驾纵向电机继电器驱动状态*/
	UN_RelayIOState DrBackRelayDriveSts; 				/* 主驾靠背电机继电器驱动状态*/
	UN_RelayIOState DrFrontRelayDriveSts; 				/* 主驾腿托电机继电器驱动状态*/
	UN_RelayIOState PaLengthRelayDriveSts; 				/* 副驾纵向电机继电器驱动状态*/
	UN_RelayIOState PaBackRelayDriveSts; 				/* 副驾靠背电机继电器驱动状态*/
} ST_ScanMotorState;

extern BOOL Ecual_GetDrRelayFlagHeightUp();
extern BOOL Ecual_GetDrRelayFlagHeightDN();

extern BOOL Ecual_GetDrRelayFlagLenghtForward();
extern BOOL Ecual_GetDrRelayFlagLenghtBackward();

extern BOOL Ecual_GetDrRelayFlagBackForward();
extern BOOL Ecual_GetDrRelayFlagBackBackward();

extern BOOL Ecual_GetDrRelayFlagFrontUp();
extern BOOL Ecual_GetDrRelayFlagFrontDown();

extern BOOL Ecual_GetPaRelayFlagHeightUp();
extern BOOL Ecual_GetPaRelayFlagHeightDN();

extern BOOL Ecual_GetPaRelayFlagLenghtForward();
extern BOOL Ecual_GetPaRelayFlagLenghtBackward();

extern BOOL Ecual_GetPaRelayFlagBackForward();
extern BOOL Ecual_GetPaRelayFlagBackBackward();

extern BOOL Ecual_GetPaRelayFlagFrontUp();
extern BOOL Ecual_GetPaRelayFlagFrontDown();

extern EN_SW_TYPE Ecual_GetDrHeightSwitchCmd();
extern EN_SW_TYPE Ecual_GetDrLengthSwitchCmd();
extern EN_SW_TYPE Ecual_GetDrBackSwitchCmd();
extern EN_SW_TYPE Ecual_GetDrFrontSwitchCmd();
extern EN_SW_TYPE Ecual_GetPaHeightSwitchCmd();
extern EN_SW_TYPE Ecual_GetPaLengthSwitchCmd();
extern EN_SW_TYPE Ecual_GetPaBackSwitchCmd();
extern EN_SW_TYPE Ecual_GetPaFrontSwitchCmd();


extern BOOL Ecual_GetDrHeightOverCurrentFlag(void);
extern BOOL Ecual_GetDrLengthOverCurrentFlag(void);
extern BOOL Ecual_GetDrBackOverCurrentFlag(void);
extern BOOL Ecual_GetDrFrontOverCurrentFlag(void);
extern BOOL Ecual_GetPrLengthOverCurrentFlag(void);
extern BOOL Ecual_GetPrBackOverCurrentFlag(void);

extern BOOL Ecual_GetPrHeightOverCurrentFlag();
extern BOOL Ecual_GetPrFrontOverCurrentFlag();


extern void Ecual_AdcMotorPollingTask();
#endif /* ECUAL_ADCMOTOR_H_ */
