/********************Copyright (c) Fuxin Dare Automotive Parts Co.LTD.*********************
** File Name:              	Common.h
** Author:           		Feliks.Peng
** Date:            		2017.5.11
** Version:                	V1.0
** Descriptions:            	
** Note:					

** History Modify 		
** Modified By:            	 
** Modified date:                       
** Modification:
***********************************************************************************/
#ifndef _COMMON_H
#define _COMMON_H

//#include "S32K144.h" /* include peripheral declarations S32K144 */
//#include "interrupt_manager.h"
#include <string.h>

/*20220924  KF32A156оƬ��һЩ����*/
#include "kf32a156_int.h"
#define  INT_SYS_DisableIRQGlobal()  	INT_All_Enable(FALSE)
#define  INT_SYS_EnableIRQGlobal()     INT_All_Enable(TRUE)
#define  SystemSoftwareReset()  asm("RESET")
/*********************************/


/********************************   Typedef Definitions  ********************************/
typedef unsigned char   BOOL;
typedef	signed char		INT8S;
typedef	unsigned char	INT8U;
typedef	signed short	INT16S;
typedef	unsigned short	INT16U;
typedef	signed int		INT32S;
typedef	unsigned int	INT32U;
typedef double			DOUBLE;

typedef void(*pt2Func)(void);		  /* Pointer to Functions, void argument */
typedef void(*pt2FuncU8)(INT8U);	  /* Pointer to Functions, INT8U argument */
typedef INT8U(*U8pt2FuncU8)(INT8U);	  /* Pointer to Functions, INT8U argument */

#define DSM_ALL_SW  	(0u)    //1����DSMȫƽ̨����	,0����DSM_C62X��Ŀ
/* �������� */
#define DSM_C52X_PROJECT											1
#define DSM_B60V_PROJECT											2
#define DSM_B30X_PROJECT											6
#define DSM_PD014_PROJECT											7
#define DSM_CURRECT_PROJECT											DSM_PD014_PROJECT


#define TASKMAX         (20)
#define PrioHighRdy     (0)
#define PrioLowest      (TASKMAX - 1)


/*��ѹ�������*/
/*13.5v*/
#define V135_UP			(160u) /*16V*/
#define V135_DOWN		(90u) /*9V*/
#define V135_LAG		(5u) /*������*/
/*24.0v*/
#define V240_UP			(320u) /*32V*/
#define V240_DOWN		(180u) /*18V*/
#define V240_LAG		(10u) /*������*/

#define NM_VOLT_NORMAL		(1200u) /*����ͨ��������ѹ12V*/
#define NM_VOLT_LOW			(600u) /*����ͨ�ŵ͵�ѹ6V,DAM�ɼ�����-6.95*/
#define NM_VOLT_HIGH		(1850u) /*����ͨ�ŵ͵�ѹ18.5V��DAM�ɼ�����-17.85*/
#define NM_VOLT_LAG			(50u) /*�жϳ��͵�ѹ0.5V*/

/*���ߺ���Դ*/
#define DESC_WAKEUPSIG_NULL			(0u)
#define DESC_WAKEUPSIG_SW			(1u) /*��Ƶ����*/
#define DESC_WAKEUPSIG_CAN			(2u) /*CAN����*/
#define DESC_WAKEUPSIG_PUSHBUTTON	(3u) /*�������ػ���*/	
#define DESC_WAKEUPSIG_BRAKE		(4u) /*ɲ������*/
#define DESC_WAKEUPSIG_CLUTCH		(5u) /*��ϻ���*/

typedef	union
{
	INT8U Byte;
	struct
	{
		INT8U 	Bit0:1;
		INT8U 	Bit1:1;
		INT8U 	Bit2:1;
		INT8U 	Bit3:1;
		INT8U 	Bit4:1;
		INT8U 	Bit5:1;
		INT8U 	Bit6:1;
		INT8U 	Bit7:1;
	}Bits;
}BYTE8;

#define ToolMake32Bit(hiHiByte,hiLoByte,loHiByte,loLoByte)           ((INT32U)((((INT32U)(hiHiByte))<<24)| \
                                                                     (((INT32U)(hiLoByte))<<16)| \
                                                                     (((INT32U)(loHiByte))<<8) | \
                                                                     ((INT32U)(loLoByte))))
#define ToolGetHiByte(data)                                          ((INT8U)(((unsigned short)(data))>>8))
#define ToolGetLoByte(data)                                          ((INT8U)(data))
#define ToolGetHiHiByte(data)                                        ((INT8U)(((INT32U)(data))>>24))
#define ToolGetHiLoByte(data)                                        ((INT8U)(((INT32U)(data))>>16))
#define ToolGetLoHiByte(data)                                        ((INT8U)(((INT32U)(data))>>8))
#define ToolGetLoLoByte(data)                                        ((INT8U)(data))


typedef	enum
{	
	ev5ms = 0,
	ev10ms,
	ev20ms,
	ev50ms,
	ev1ms,

	evNULL,
	
}TaskId;

typedef union
{
	INT8U byte;
	struct 
	{
		INT8U send0x500Cfg	: 1;
		INT8U send0x501Cfg	: 1;
		INT8U send0x502Cfg	: 1;
		INT8U red			: 5;
	}bit;
}un_TestMessageSendCfg;


/********************************   Definitions  ********************************/
#ifndef	TRUE
#define TRUE           	(1)
#endif

#ifndef FALSE
#define FALSE         	(0)
#endif


/* ���ؽ�����������º꣬���Գ�����չ���� */
#define	D_Ok		(0)			/* No Error						*/
#define D_Init		(1)			/* init data */
#define	D_DataErr		(3)		/* data error		 				*/
#define	D_WaitTimeOut	(4)		/* wait time out	 				*/
#define	D_SystemErr		(5)			/* System error: Unknown cause		*/
#define	D_PointNull	(6)			/* param point is null				*/
#define	D_MsgBufFull	(7)			/* msg of buffer is full				*/
#define	D_NoData	(8)			/* no data						*/
#define	D_NoMessage	(9)			/* no message					*/
#define	D_NoMemory	(10)		/* Insufficient Memory 				*/
#define	D_BufOverflow	(11)	/* buffer data overflow 				*/
#define	D_NoCmdAck	(12)	/* no cmd ack	 data 				*/
#define	D_AckErr	(13)	/* ack data error 					*/
#define	D_AckTimeOut	(14)	/* ack time out	 				*/
#define	D_WaitStatus			(15)	/* wait status		 				*/
#define	D_KeepWait		(16)	/* keep wait 		 				*/
#define	D_ParaErr		(17)		/* Parameter error					*/
/* end ���ؽ�����������º꣬���Գ�����չ���� */

/* ���õĺ궨��,���Գ�����չ���� */
#define     D_True              (1u)
#define     D_False         (0u)

#define     D_Enable                (1u)
#define     D_Disable           (0u)

#define     D_Open                (1u)
#define     D_Close           (0u)

#define     D_Yes           (1u)
#define     D_No            (0u)

#define     D_Failure       (0u)
#define     D_Success       (1u)
#define     D_E2_WriteWait  (2u)

#define		D_ON			(1u)
#define		D_OFF			(0u)

#define		D_ACTIVE		(1u)
#define		D_INACTIVE		(0u)

#define		D_HIGH			(1u)
#define		D_LOW			(0u)

#define		D_Normal		(0u)
#define		D_AbNormal		(1u)

#ifndef D_ENABLE
#define     D_ENABLE        (1u)
#endif
#ifndef D_DISABLE
#define     D_DISABLE       (0u)
#endif
#ifndef D_BUSOFF_COUNT
#define     D_BUSOFF_COUNT   (3u)
#endif
#define DESC_APP_BOOT_NULL				(0u) /*app δ��ת�� boot*/
#define DESC_APP_BOOT_NO_NEED_RESP		(1u) /*app ��ת�� boot��,boot����ظ�*/
#define DESC_APP_BOOT_NEED_RESP			(2u) /*app ��ת�� boot��,boot��ظ�*/

#define ENTER_CRITICAL()         	INT_SYS_DisableIRQGlobal()
#define EXIT_CRITICAL()       		INT_SYS_EnableIRQGlobal()

#define ENABLE_STOP()             	
#define DISABLE_STOP()             	

/* ��������� */
#define UBOUND(__ARRAY) (sizeof(__ARRAY)/sizeof(__ARRAY[0])) 

/*LIN*/
#define SYNCH_DATA              		(0x55)

#define D_SYS_MS_TIME_BASE                  1UL

/********************************ģ��ʹ�õ��ĺ궨��********************************/
#define D_Relay_DownBackFault          2U                        /* �̵����º�ճ������ */
#define D_Relay_UpFrontFault           1U                        /* �̵�����ǰճ������ */
#define D_ToleranceDistance            5U                        /* �����Զ������������Χ */
#define D_DRMEM_SPEED_5            	   5U                        /* ����5KM/H*/
#define D_DrSoftStopDef_B              10U                       /* ��ֹ��������-���� */
#define D_DrSoftStopDef_H              5U                        /* ��ֹ��������-�߶� */
#define D_DrSoftStopDef_L              6U                        /* ��ֹ��������-���� */
#define D_DrSoftStopDef_F              5U                        /* ��ֹ��������-���� */
#define D_StallCurrent                 2000U                     /* �����ת������ֵ */
#define D_InitDelayTime                10U                       /* ��ʼ���ȴ�ʱ�� */
#define D_CLOSE                        0U                        /* �ر� */
#define D_OPEN                         1U                        /* �� */
#define D_SoftDistanceDrLegnth         8U                        /* ����������ֹ����� */
#define D_WelcomeDistance              180U                      /* ӭ������ */
#define D_ClickNapHeightPosi           50U                       /* С�궨λ��-�߶� */
#define D_ClickNapLengthPosi           33U                       /* С���������ƶ����� */
#define D_ClickNapBackPosi             19U                       /* С�궨λ��-���� */
#define D_ClickNapFrontPosi            50U                       /* С�궨λ��-���� */
#define D_ActMax                       5U                        /* ��Ħ����ʱ��D_ActMax -5�� */
#define D_T1                           6000U                     /* ��Ħ����ʱ��T1-1min */
#define D_T2                           30000U                    /* ��Ħ����ʱ��T2-5min */
#define D_T3                           90000U                    /* ��Ħ����ʱ��T3-15min */
#define D_T4                           450000U                   /* ��Ħ����ʱ��T4-75min */

#define D_POWER_ADJUST_15800MV         15800U                    /* ������ߵ�ѹ����ֵ��15.8V�� */
#define D_POWER_ADJUST_7800MV          7800U                     /* ������͵�ѹ����ֵ��7.8V�� */
#define D_POWER_HIGH_DN                16000U                    /* �ߵ�ѹģʽ��͵�ѹ��16V�� */
#define D_POWER_HIGH_UP                18500U                    /* �ߵ�ѹģʽ��ߵ�ѹ(18.5V) */
#define D_POWER_Invalid                3U                        /* ��Ч״̬ */
#define D_POWER_LOW_DN                 6000U                     /* �͵�ѹģʽ��͵�ѹ(6V) */
#define D_POWER_LOW_UP                 9000U                     /* �͵�ѹģʽ��ߵ�ѹ��9V�� */
#define D_POWER_NORMAL_DN              8500U                     /* ����ģʽ��͵�ѹ��8.5V�� */
#define D_POWER_NORMAL_UP              16500U                    /* ����ģʽ��ߵ�ѹ��16.5V�� */
#define D_POWER_OVER_DN                18000U                    /* ��ѹģʽ��͵�ѹ(18V) */
#define D_POWER_OVER_UP                26500U                    /* ��ѹģʽ��ߵ�ѹ(26.5V) */
#define D_POWER_STOP_UP                6500U                     /* ֹͣģʽ��ߵ�ѹ��6.5V�� */
#define D_POWER_STOP_DN                0U                     	 /* ֹͣģʽ��͵�ѹ��0V�� */

#define D_HEATFALUT_CmdOpenLoad        350U                      /* ���������·(0.01A) */
#define D_HEATFALUT_CmdOpenLoad_W      10U                       /* �����̼��������·(0.01A) */
#define D_HEATFALUT_CmdShortToGnd      8640U                     /* ��������Եض�·(��Ӳ���⺣��ȷ�Ϻ�ʹ�ô�ֵ7.2A+20%)���ȵ渺�ع�������������ϱ�ע 7.2A��10%*/
#define D_HEATFALUT_NtcMax             3513U                     /* NTC��Ч���ֵ */
#define D_HEATFALUT_NtcMin             239U                      /* NTC��Ч��Сֵ */
#define D_HEATFALUT_NtcOpenLoad        3690U                     /* NTC��· */
#define D_HEATFALUT_NtcShortToGnd      50U                       /* NTC�Եض�· */

#define D_1stLevel_36                  680U                      /* 1��λ�����¶� */
#define D_2ndLevel_39                  730U                      /* 2��λ�����¶� */
#define D_3rdLevel_45                  770U                      /* 3��λ�����¶� */
#define D_3rdLevel_48                  810U                      /* 3��λ�����¶� */
#define D_DRVHEAT_PID_D                0U                        /* ΢�� */
#define D_DRVHEAT_PID_I                0U                        /* ���� */
#define D_DRVHEAT_PID_P                18U                       /* ���� */
#define D_HEAT_HEAT_DEF                30U                       /* ���Ȳ�ֵ */
#define D_SwsLevel_Temp                855U                      /* �����̼����¶� */
#define OFF                            0U                        /* ��0 */
#define ON                             1U                        /* ��1 */

#define D_VENT_LVL_1_PRECENT           64U                       /* ͨ�絵λ1 */
#define D_VENT_LVL_2_PRECENT           80U                       /* ͨ�絵λ2 */
#define D_VENT_LVL_3_PRECENT           100U                        /* ͨ�絵λ3 */

#define D_SoftDistancePaLegnth         (8u)
#ifndef D_SoftDistancePaHeight
#define     D_SoftDistancePaHeight        (100u)
#endif

#ifndef D_SoftDistancePaLegnth
#define     D_SoftDistancePaLegnth        (8u)
#endif

#ifndef D_SoftDistancePaBack
#define     D_SoftDistancePaBack        (16u)
#endif

#ifndef D_SoftDistancePaFront
#define     D_SoftDistancePaFront        (187u)
#endif


/* ѧϰ */
#define D_FirstMove                    1U                        /* ѧϰ���ܵ�һ��������� */
#define D_FourthlyMove                 4U                        /* ѧϰ���ܵ��ĸ�������� */
#define D_Invalid                      0U                        /* ��������� */
#define D_RelayVolMaxValue             16000U                    /* �̵�����������ѹ/mv */
#define D_RelayVolMinValue             9000U                     /* �̵���������С��ѹ/mv */
#define D_SecondMove                   2U                        /* ѧϰ���ܵڶ���������� */
#define D_ThirdlyMove                  3U                        /* ѧϰ���ܵ������������ */




/********************************���ú���********************************/
extern void Com_RamSet(INT8U * buff, INT8U data, INT16U len);
extern BOOL Com_MemCmp(INT8U * TrgBuff, INT8U * SrcBuff, INT8U Len);

/********************************ģ��ʹ�õ��ĳ���********************************/
extern const volatile INT16U CAL_LockErrNoTime_30ms;/* ��ת����������30ms */
extern const volatile INT32U CAL_ManualSwError_2min ;/* ����ճ��ʱ����120s */
extern const volatile INT32U CAL_ManualSwValid_90s;/* ������Чʱ����90s */
extern const volatile INT8U CAL_MotorHallInvalid_2s;/* �����źŲ��仯ʱ����2s */
extern const volatile INT16U CAL_MotorMaxRunTime_60s;/* ����������ʱ�䣺60s */
extern const volatile INT16U CAL_MotorRelayErr_2s;/* �̵���ճ��ʱ��2s */
extern const volatile INT8U CAL_MotorStall_750ms;/* �����ޱ仯��ת���ʱ����750ms */

#endif

