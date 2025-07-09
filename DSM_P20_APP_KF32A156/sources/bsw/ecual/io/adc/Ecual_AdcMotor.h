/*
 * Ecual_AdcMotor.h
 *
 *  Created on: 2025-3-26
 *      Author: Administrator
 */
#ifndef ECUAL_ADCMOTOR_H_
#define ECUAL_ADCMOTOR_H_

#include "Common.h"
#define     D_SEAT_SW_LIMIT_VOLTAGE               	(142UL)    /*��ѹ����*/
#define     D_SEAT_SW_LIMIT_MAX                     (4080UL)   /*��Ч��ѹ����*/

#define MOTOR_CURR_MAX_DR_HEIGHT   3300   /* ���ݸ߶ȵ����ת������ֵ */
#define MOTOR_CURR_MAX_DR_LENGTH   3670   /* ������������ת������ֵ */
#define MOTOR_CURR_MAX_DR_BACK     2244   /* ���ݿ��������ת������ֵ */
#define MOTOR_CURR_MAX_DR_FRONT    3230   /* �������е����ת������ֵ */
#define MOTOR_CURR_MAX_PA_LENGTH   3445   /* ������������ת������ֵ */
#define MOTOR_CURR_MAX_PA_BACK     3364   /* ���ݿ��������ת������ֵ */


typedef enum
{
	EN_SW_DEF = 0,		/*Ĭ��״̬*/
	EN_SW_UP_FW_LF,		/*�ϣ�ǰ����*/
	EN_SW_DN_BW_RT,		/*�£�����*/
	EN_SW_ERR,			/*����*/
}EN_SW_TYPE;

typedef enum
{
	EN_CURR_DEF = 0,		/*Ĭ��״̬*/
	EN_CURR_NOLMAL,			/*��������״̬*/
	EN_CURR_ERR,			/*��ת״̬*/
}EN_CURR_TYPE;
typedef struct
{
    INT8U MOTOR_CURR_UP_NOLMAL   :1;		/*������������״̬*/
	INT8U MOTOR_CURR_DN_NOLMAL   :1;		/*������������״̬*/
}ST_RelayBits;

typedef union
{
    INT8U Byte;
    ST_RelayBits Bits;
}UN_RelayIOState;
/*�����ɨ��*/
typedef struct
{

	EN_SW_TYPE DrHeightSwitch;        /* ���ݸ߶ȵ��ڿ��������  */
	EN_SW_TYPE DrLengthSwitch;        /* ����������ڿ��������  */
	EN_SW_TYPE DrBackSwitch;          /* ���ݿ������ڿ��������  */
	EN_SW_TYPE DrFrontSwitch;         /* �������е��ڿ��������  */
	EN_SW_TYPE PaLengthSwitch;        /* ����������ڿ��������  */
	EN_SW_TYPE PaBackSwitch;          /* ���ݿ������ڿ��������  */

	BOOL DrHeightOverCurrentFlag;        /* ���ݸ߶ȵ������������ת��ֵ��־λ  */
	BOOL DrLengthOverCurrentFlag;        /* ��������������������ת��ֵ��־λ  */
	BOOL DrBackOverCurrentFlag;          /* ���ݿ����������������ת��ֵ��־λ  */
	BOOL DrFrontOverCurrentFlag;         /* �������е������������ת��ֵ��־λ  */
	BOOL PaLengthOverCurrentFlag;        /* ��������������������ת��ֵ��־λ  */
	BOOL PaBackOverCurrentFlag;          /* ���ݿ����������������ת��ֵ��־λ  */

	BOOL SEAT_HEIGHT_MOTOR_CURR; 				/* ���θ߶ȵ������������ת��ֵ��־λ */
	BOOL SEAT_LENGTH_MOTOR_CURR; 				/* ��������������������ת��ֵ��־λ*/
	BOOL SEAT_BACKREST_RECLINE_MOTOR_CURR; 		/* ���ο����Ƕȵ������������ת��ֵ��־λ*/
	BOOL SEAT_FRONT_HEIGHT_MOTOR_CURR; 			/* ����ǰ���Ƕȵ������������ת��ֵ��־λ*/
	EN_CURR_TYPE SEAT_HEADREST_HEIGHT_MOTOR_CURR; 		/* ����ͷ��߶ȵ������������ת��ֵ��־λ*/
	EN_CURR_TYPE SEAT_CUSHION_LENGTH_MOTOR_CURR; 		/* �����Ȳ�֧�ŵ������������ת��ֵ��־λ*/

	UN_RelayIOState DrHeightRelayDriveSts; 				/* ���ݸ߶ȵ���̵�������״̬*/
	UN_RelayIOState DrLengthRelayDriveSts; 				/* �����������̵�������״̬*/
	UN_RelayIOState DrBackRelayDriveSts; 				/* ���ݿ�������̵�������״̬*/
	UN_RelayIOState DrFrontRelayDriveSts; 				/* �������е���̵�������״̬*/
	UN_RelayIOState PaLengthRelayDriveSts; 				/* �����������̵�������״̬*/
	UN_RelayIOState PaBackRelayDriveSts; 				/* ���ݿ�������̵�������״̬*/
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
