/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               MidRelay.h
** Last modified Date:      2019.3.14
** Last Version:            V1.0.0
** Description:             MidRelay header file
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2019.3.12
** Version:                 V1.0.0
** Descriptions:            MidRelay header file
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#ifndef MIDRELAY_H
#define MIDRELAY_H


/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "Common.h"
#include "Ecual_AdcMotor.h"



#define	D_MIDRELAY_CYCLE				(5)
#define	D_TMS(Tm)						(Tm/D_MIDRELAY_CYCLE)
/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/
/*������Ʒ���*/
typedef enum
{
	EN_MOTOR_DEF = 0,	/*��ʼ״̬*/
	EN_MOTOR_UP_FW_LF,	/*���ϣ���ǰ������*/
	EN_MOTOR_DN_BW_RT,	/*���£��������*/
}EN_MOTOR_MOVE;

/*���Ӿ�����״̬*/
typedef enum
{
	EN_ERVM_DEF = 0,	/*Ĭ��*/
	EN_ERVM_UP,			/*��*/
	EN_ERVM_DN,			/*��*/
	EN_ERVM_LF,			/*��*/
	EN_ERVM_RT,			/*��*/
	EN_ERVM_ERR,		/*����*/
}EN_ERVM_MOVE;

/*
0x0:Inactive
0x1:OFF
0x2:Level 1
0x3:Level 2
0x4:Level 3
0x5:reserved
0x6:reserved
0x7:reserved
*/
typedef enum
{
	EN_LVL_OFF = 0,
	EN_LVL_1,
	EN_LVL_2,
	EN_LVL_3,
	EN_LVL_Max,
}EN_LVL;



/*�������*/
typedef struct
{
	EN_LVL SEAT_HEAT_DR_CMD;	/*�������μ���*/
	EN_LVL SEAT_VEN_DR_CMD;	/*��������ͨ��*/
	EN_LVL SEAT_HEAT_PA_CMD;	/*�������μ���*/
	EN_LVL SEAT_VEN_PA_CMD;	/*��������ͨ��*/
	INT8U WHEEL_HEAT_CMD;	/*�����̼���*/
	INT8U HSD1_CMD;			/*Ԥ���߱߿���1*/
	INT8U HSD2_CMD;			/*Ԥ���߱߿���2*/
	INT8U HSD3_CMD;			/*Ԥ���߱߿���3*/

	EN_MOTOR_MOVE SEAT_HEIGHT_CMD;		/*���θ߶ȵ���*/
	EN_MOTOR_MOVE SEAT_LENGTH_CMD;		/*�����������*/
	EN_MOTOR_MOVE SEAT_BACKREST_CMD;	/*���ο����Ƕȵ���*/
	INT8U SEAT_HEAT_COM_GND_CMD;		/*���μ��ȵؿ���*/
	
	EN_MOTOR_MOVE SEAT_FRONT_HEIGHT_CMD;		/*����ǰ���Ƕȵ���*/
	EN_MOTOR_MOVE SEAT_HEADREST_HEIGHT_CMD;		/*����ͷ��߶ȵ���*/
	EN_MOTOR_MOVE SEAT_CUSHION_LENGTH_CMD;		/*�����Ȳ�֧�ŵ���*/

	EN_MOTOR_MOVE WHEEL_HEIGHT_CMD;				/*���������µ���*/
	EN_MOTOR_MOVE WHEEL_LENGTH_CMD;				/*������ǰ�����*/
	INT8U WHEEL_HEAT_COM_GND_CMD;				/*�����̼��ȵؿ���*/
	
	BOOL LSD1_CMD;			/*Ԥ���ͱ߿���1*/
	BOOL LSD2_CMD;			/*Ԥ���ͱ߿���2*/

	EN_ERVM_MOVE RT_ERVM_CMD;			/*�ұߺ��Ӿ�����*/
	EN_ERVM_MOVE LF_ERVM_CMD;			/*��ߺ��Ӿ�����*/
	
	BOOL SEAT_HEAT_DR_KEEP;   	/*�������μ��ȱ���״̬*/
	BOOL SEAT_HEAT_PA_KEEP; 	/*�������μ��ȱ���״̬*/
	BOOL WHEEL_HEAT_KEEP;		/*�����̼��ȱ���״̬*/

	INT8U RT_UPDN_ERVM_SW;			/*�ұߺ��Ӿ��������±��ؿ���*/
	INT8U LF_UPDN_ERVM_SW;			/*��ߺ��Ӿ��������±��ؿ���*/
	INT8U RT_LFRT_ERVM_SW;			/*�ұߺ��Ӿ��������ұ��ؿ���*/
	INT8U LF_LFRT_ERVM_SW;			/*��ߺ��Ӿ��������ұ��ؿ���*/

}ST_MIDRELAY_STATUS;


typedef enum
{
	EN_SEAT_HEAT = 0,
	EN_SEAT_HEAT_COM,
	EN_SEAT_VEN_DR,
	EN_SEAT_VEN_PA,
	EN_WHL_HEAT,

	EN_SEAT_HEIGHT_MOTOR,
	EN_SEAT_LENGTH_MOTOR,
	EN_SEAT_BACKREST_MOTOR,
	EN_SEAT_FRONT_MOTOR,
	EN_SEAT_PA_HEIGHT_MOTOR,

	EN_SEAT_PA_LENGTH_MOTOR,
	EN_SEAT_PA_BACKREST_MOTOR,
	EN_SEAT_PA_FRONT_MOTOR,

	EN_MOTOR_MAX,
}EN_MOTOR_NUM;

typedef struct
{
	EN_MOTOR_MOVE	SeatHeightPosi;			/*���θ߶�*/
	EN_MOTOR_MOVE	SeatLengthPosi;
	EN_MOTOR_MOVE	SeatBackrestPosi;
	EN_MOTOR_MOVE	SeatFrontHeightPosi;
	EN_MOTOR_MOVE	SeatHeadrestPosi;
	EN_MOTOR_MOVE	SeatCushionLengthPosi;

	EN_MOTOR_MOVE	WheelHeightPosi;
	EN_MOTOR_MOVE	WheelLengthPosi;

	EN_ERVM_MOVE	ERVM_L_MIRROR_L_R__Posi;
	EN_ERVM_MOVE	ERVM_L_MIRROR_U_D__Posi;
	EN_ERVM_MOVE	ERVM_R_MIRROR_L_R__Posi;
	EN_ERVM_MOVE	ERVM_R_MIRROR_U_D__Posi;
}ST_MemorySet;

typedef struct
{
	BOOL	IsCtrl;			//�Ƿ���Ҫ����
	void	(*pFuncMotorCtrl)(void);
}ST_MOTOR_INFO;

typedef struct
{
	ST_MOTOR_INFO	stMotorInfo[EN_MOTOR_MAX];
}ST_OUTPUT_MOTOR_CTRL;

typedef struct{
    	float SetPoint; // �趨Ŀ�� Desired Value
    	float Proportion; // �������� Proportional Const
    	float Integral; // ���ֳ��� Integral Const
    	float Derivative; // ΢�ֳ��� Derivative Const
    	float LastError; // Error[-1]
    	float PrevError; // Error[-2]
    	float SumError; // Sums of Errors
}ST_PID;

typedef struct
{
	INT16U DR_HEAT_PWM;
	INT16U PA_HEAT_PWM;
}ST_HEATPWM;


/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/
extern ST_MIDRELAY_STATUS 	stgMidRelayStatusCmd;
extern EN_MOTOR_MOVE swMotorMove[12];
extern ST_HEATPWM HeatPWM;

/*
**********************************************************************************************************
					FUNCTIONS
**********************************************************************************************************
*/
extern void MidRelay_MotorCtrlProc(void);

#if 0
extern void Memory_Seat_Height_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Length_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Backrest_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_FrontHeight_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Headrest_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_CushionLength_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_WheelHeight_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_WheelLength_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_LeftMirrorMotorLF_RT_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_LeftMirrorMotorUP_DN_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_RightMirrorMotorLF_RT_Judge_Task(INT16U RealData,INT16U SetData);
extern void Memory_RightMirrorMotorUP_DN_Judge_Task(INT16U RealData,INT16U SetData);

extern void Memory_Seat_Height_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Length_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Backrest_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_FrontHeight_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_Headrest_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_Seat_CushionLength_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_WheelHeight_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_WheelLength_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_LeftMirrorMotorLF_RT_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_LeftMirrorMotorUP_DN_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_RightMirrorMotorLF_RT_Set_Task(INT16U RealData,INT16U SetData);
extern void Memory_RightMirrorMotorUP_DN_Set_Task(INT16U RealData,INT16U SetData);
#endif

extern void MidVenDrCmdCtrlProc(void);
extern void MidVenPaCmdCtrlProc(void);

extern EN_SW_TYPE MidRelay_RT_UP_DN_ERVM_Cmd_Get(void);
extern EN_SW_TYPE MidRelay_RT_LF_RT_ERVM_Cmd_Get(void);
extern EN_SW_TYPE MidRelay_LF_UP_DN_ERVM_Cmd_Get(void);
extern EN_SW_TYPE MidRelay_LF_LF_RT_ERVM_Cmd_Get(void);

/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/
#define		SEAT_HEAT_DR_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_HEAT_DR_CMD = Cmd
#define		SEAT_HEAT_DR_CMD_Get()				stgMidRelayStatusCmd.SEAT_HEAT_DR_CMD

#define		SEAT_HEAT_DR_KEEP_Set(Cmd)			stgMidRelayStatusCmd.SEAT_HEAT_DR_KEEP = Cmd
#define		SEAT_HEAT_DR_KEEP_Get()				stgMidRelayStatusCmd.SEAT_HEAT_DR_KEEP

#define		SEAT_HEAT_PA_KEEP_Set(Cmd)			stgMidRelayStatusCmd.SEAT_HEAT_PA_KEEP = Cmd
#define		SEAT_HEAT_PA_KEEP_Get()				stgMidRelayStatusCmd.SEAT_HEAT_PA_KEEP

#define		WHEEL_HEAT_KEEP_Set(Cmd)			stgMidRelayStatusCmd.WHEEL_HEAT_KEEP= Cmd
#define		WHEEL_HEAT_KEEP_Get()				stgMidRelayStatusCmd.WHEEL_HEAT_KEEP
		
#define		SEAT_VEN_DR_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_VEN_DR_CMD = Cmd
#define		SEAT_VEN_DR_CMD_Get()				stgMidRelayStatusCmd.SEAT_VEN_DR_CMD

#define		SEAT_HEAT_PA_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_HEAT_PA_CMD = Cmd
#define		SEAT_HEAT_PA_CMD_Get()				stgMidRelayStatusCmd.SEAT_HEAT_PA_CMD
		
#define		SEAT_VEN_PA_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_VEN_PA_CMD = Cmd
#define		SEAT_VEN_PA_CMD_Get()				stgMidRelayStatusCmd.SEAT_VEN_PA_CMD

#define		WHEEL_HEAT_CMD_Set(Cmd)				stgMidRelayStatusCmd.WHEEL_HEAT_CMD = Cmd
#define		WHEEL_HEAT_CMD_Get()				stgMidRelayStatusCmd.WHEEL_HEAT_CMD

#define		RSVD_HSD1_CMD_Set(Cmd)				stgMidRelayStatusCmd.HSD1_CMD = Cmd
#define		RSVD_HSD1_CMD_Get()					stgMidRelayStatusCmd.HSD1_CMD

#define		RSVD_HSD2_CMD_Set(Cmd)				stgMidRelayStatusCmd.HSD2_CMD = Cmd
#define		RSVD_HSD2_CMD_Get()					stgMidRelayStatusCmd.HSD2_CMD

#define		RSVD_HSD3_CMD_Set(Cmd)				stgMidRelayStatusCmd.HSD3_CMD = Cmd
#define		RSVD_HSD3_CMD_Get()					stgMidRelayStatusCmd.HSD3_CMD

#define		SEAT_HEIGHT_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_HEIGHT_CMD = Cmd
#define		SEAT_HEIGHT_CMD_Get()				stgMidRelayStatusCmd.SEAT_HEIGHT_CMD

#define		SEAT_LENGTH_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_LENGTH_CMD = Cmd
#define		SEAT_LENGTH_CMD_Get()				stgMidRelayStatusCmd.SEAT_LENGTH_CMD

#define		SEAT_BACKREST_CMD_Set(Cmd)			stgMidRelayStatusCmd.SEAT_BACKREST_CMD = Cmd
#define		SEAT_BACKREST_CMD_Get()				stgMidRelayStatusCmd.SEAT_BACKREST_CMD

#define		SEAT_HEAT_COM_GND_CMD_Set(Cmd)		stgMidRelayStatusCmd.SEAT_HEAT_COM_GND_CMD = Cmd
#define		SEAT_HEAT_COM_GND_CMD_Get()			stgMidRelayStatusCmd.SEAT_HEAT_COM_GND_CMD

#define		SEAT_FRONT_HEIGHT_CMD_Set(Cmd)		stgMidRelayStatusCmd.SEAT_FRONT_HEIGHT_CMD = Cmd
#define		SEAT_FRONT_HEIGHT_CMD_Get()			stgMidRelayStatusCmd.SEAT_FRONT_HEIGHT_CMD

#define		SEAT_HEADREST_HEIGHT_CMD_Set(Cmd)		stgMidRelayStatusCmd.SEAT_HEADREST_HEIGHT_CMD = Cmd
#define		SEAT_HEADREST_HEIGHT_CMD_Get()			stgMidRelayStatusCmd.SEAT_HEADREST_HEIGHT_CMD

#define		SEAT_CUSHION_LENGTH_CMD_Set(Cmd)		stgMidRelayStatusCmd.SEAT_CUSHION_LENGTH_CMD = Cmd
#define		SEAT_CUSHION_LENGTH_CMD_Get()			stgMidRelayStatusCmd.SEAT_CUSHION_LENGTH_CMD

#define		WHEEL_HEIGHT_CMD_Set(Cmd)				stgMidRelayStatusCmd.WHEEL_HEIGHT_CMD = Cmd
#define		WHEEL_HEIGHT_CMD_Get()					stgMidRelayStatusCmd.WHEEL_HEIGHT_CMD

#define		WHEEL_LENGTH_CMD_Set(Cmd)				stgMidRelayStatusCmd.WHEEL_LENGTH_CMD = Cmd
#define		WHEEL_LENGTH_CMD_Get()					stgMidRelayStatusCmd.WHEEL_LENGTH_CMD

#define		WHEEL_HEAT_COM_GND_CMD_Set(Cmd)			stgMidRelayStatusCmd.WHEEL_HEAT_COM_GND_CMD = Cmd
#define		WHEEL_HEAT_COM_GND_CMD_Get()			stgMidRelayStatusCmd.WHEEL_HEAT_COM_GND_CMD

#define		RSVD_LSD1_CMD_Set(Cmd)				stgMidRelayStatusCmd.LSD1_CMD = Cmd
#define		RSVD_LSD1_CMD_Get()					stgMidRelayStatusCmd.LSD1_CMD

#define		RSVD_LSD2_CMD_Set(Cmd)				stgMidRelayStatusCmd.LSD2_CMD = Cmd
#define		RSVD_LSD2_CMD_Get()					stgMidRelayStatusCmd.LSD2_CMD


#define		RT_ERVM_CMD_Set(Cmd)			stgMidRelayStatusCmd.RT_ERVM_CMD = Cmd
#define		RT_ERVM_CMD_Get()				stgMidRelayStatusCmd.RT_ERVM_CMD

#define		LF_ERVM_CMD_Set(Cmd)			stgMidRelayStatusCmd.LF_ERVM_CMD = Cmd
#define		LF_ERVM_CMD_Get()				stgMidRelayStatusCmd.LF_ERVM_CMD

#define		RT_UPDN_ERVM_SW_Set(Cmd)			stgMidRelayStatusCmd.RT_UPDN_ERVM_SW= Cmd
#define		RT_UPDN_ERVM_SW_Get()				stgMidRelayStatusCmd.RT_UPDN_ERVM_SW

#define		LF_UPDN_ERVM_SW_Set(Cmd)			stgMidRelayStatusCmd.LF_UPDN_ERVM_SW = Cmd
#define		LF_UPDN_ERVM_SW_Get()				stgMidRelayStatusCmd.LF_UPDN_ERVM_SW

#define		RT_LFRT_ERVM_SW_Set(Cmd)			stgMidRelayStatusCmd.RT_LFRT_ERVM_SW= Cmd
#define		RT_LFRT_ERVM_SW_Get()				stgMidRelayStatusCmd.RT_LFRT_ERVM_SW

#define		LF_LFRT_ERVM_SW_Set(Cmd)			stgMidRelayStatusCmd.LF_LFRT_ERVM_SW = Cmd
#define		LF_LFRT_ERVM_SW_Get()				stgMidRelayStatusCmd.LF_LFRT_ERVM_SW


#endif /* __MIDRELAY_H__ */



