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

/*20220924  KF32A156芯片的一些定义*/
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

#define DSM_ALL_SW  	(0u)    //1定义DSM全平台功能	,0定义DSM_C62X项目
/* 工程配置 */
#define DSM_C52X_PROJECT											1
#define DSM_B60V_PROJECT											2
#define DSM_B30X_PROJECT											6
#define DSM_PD014_PROJECT											7
#define DSM_CURRECT_PROJECT											DSM_PD014_PROJECT


#define TASKMAX         (20)
#define PrioHighRdy     (0)
#define PrioLowest      (TASKMAX - 1)


/*电压检测配置*/
/*13.5v*/
#define V135_UP			(160u) /*16V*/
#define V135_DOWN		(90u) /*9V*/
#define V135_LAG		(5u) /*检测迟滞*/
/*24.0v*/
#define V240_UP			(320u) /*32V*/
#define V240_DOWN		(180u) /*18V*/
#define V240_LAG		(10u) /*检测迟滞*/

#define NM_VOLT_NORMAL		(1200u) /*网络通信正常电压12V*/
#define NM_VOLT_LOW			(600u) /*网络通信低电压6V,DAM采集精度-6.95*/
#define NM_VOLT_HIGH		(1850u) /*网络通信低电压18.5V，DAM采集精度-17.85*/
#define NM_VOLT_LAG			(50u) /*判断迟滞电压0.5V*/

/*休眠后唤醒源*/
#define DESC_WAKEUPSIG_NULL			(0u)
#define DESC_WAKEUPSIG_SW			(1u) /*高频唤醒*/
#define DESC_WAKEUPSIG_CAN			(2u) /*CAN唤醒*/
#define DESC_WAKEUPSIG_PUSHBUTTON	(3u) /*启动开关唤醒*/	
#define DESC_WAKEUPSIG_BRAKE		(4u) /*刹车唤醒*/
#define DESC_WAKEUPSIG_CLUTCH		(5u) /*离合唤醒*/

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


/* 返回结果可以用以下宏，可以持续扩展增加 */
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
/* end 返回结果可以用以下宏，可以持续扩展增加 */

/* 常用的宏定义,可以持续扩展增加 */
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
#define DESC_APP_BOOT_NULL				(0u) /*app 未跳转到 boot*/
#define DESC_APP_BOOT_NO_NEED_RESP		(1u) /*app 跳转到 boot后,boot无需回复*/
#define DESC_APP_BOOT_NEED_RESP			(2u) /*app 跳转到 boot后,boot需回复*/

#define ENTER_CRITICAL()         	INT_SYS_DisableIRQGlobal()
#define EXIT_CRITICAL()       		INT_SYS_EnableIRQGlobal()

#define ENABLE_STOP()             	
#define DISABLE_STOP()             	

/* 求数组个数 */
#define UBOUND(__ARRAY) (sizeof(__ARRAY)/sizeof(__ARRAY[0])) 

/*LIN*/
#define SYNCH_DATA              		(0x55)

#define D_SYS_MS_TIME_BASE                  1UL

/********************************模型使用到的宏定义********************************/
#define D_Relay_DownBackFault          2U                        /* 继电器下后粘连故障 */
#define D_Relay_UpFrontFault           1U                        /* 继电器上前粘连故障 */
#define D_ToleranceDistance            5U                        /* 主驾自动调节误差允许范围 */
#define D_DRMEM_SPEED_5            	   5U                        /* 车速5KM/H*/
#define D_DrSoftStopDef_B              10U                       /* 软止点误差距离-靠背 */
#define D_DrSoftStopDef_H              5U                        /* 软止点误差距离-高度 */
#define D_DrSoftStopDef_L              6U                        /* 软止点误差距离-纵向 */
#define D_DrSoftStopDef_F              5U                        /* 软止点误差距离-腿托 */
#define D_StallCurrent                 2000U                     /* 电机堵转电流阈值 */
#define D_InitDelayTime                10U                       /* 初始化等待时间 */
#define D_CLOSE                        0U                        /* 关闭 */
#define D_OPEN                         1U                        /* 打开 */
#define D_SoftDistanceDrLegnth         8U                        /* 主驾纵向软止点距离 */
#define D_WelcomeDistance              180U                      /* 迎宾距离 */
#define D_ClickNapHeightPosi           50U                       /* 小憩标定位置-高度 */
#define D_ClickNapLengthPosi           33U                       /* 小憩纵向向后移动距离 */
#define D_ClickNapBackPosi             19U                       /* 小憩标定位置-靠背 */
#define D_ClickNapFrontPosi            50U                       /* 小憩标定位置-腿托 */
#define D_ActMax                       5U                        /* 按摩工作时长D_ActMax -5次 */
#define D_T1                           6000U                     /* 按摩工作时长T1-1min */
#define D_T2                           30000U                    /* 按摩工作时长T2-5min */
#define D_T3                           90000U                    /* 按摩工作时长T3-15min */
#define D_T4                           450000U                   /* 按摩工作时长T4-75min */

#define D_POWER_ADJUST_15800MV         15800U                    /* 调节最高电压回滞值（15.8V） */
#define D_POWER_ADJUST_7800MV          7800U                     /* 调节最低电压回滞值（7.8V） */
#define D_POWER_HIGH_DN                16000U                    /* 高电压模式最低电压（16V） */
#define D_POWER_HIGH_UP                18500U                    /* 高电压模式最高电压(18.5V) */
#define D_POWER_Invalid                3U                        /* 无效状态 */
#define D_POWER_LOW_DN                 6000U                     /* 低电压模式最低电压(6V) */
#define D_POWER_LOW_UP                 9000U                     /* 低电压模式最高电压（9V） */
#define D_POWER_NORMAL_DN              8500U                     /* 正常模式最低电压（8.5V） */
#define D_POWER_NORMAL_UP              16500U                    /* 正常模式最高电压（16.5V） */
#define D_POWER_OVER_DN                18000U                    /* 过压模式最低电压(18V) */
#define D_POWER_OVER_UP                26500U                    /* 过压模式最高电压(26.5V) */
#define D_POWER_STOP_UP                6500U                     /* 停止模式最高电压（6.5V） */
#define D_POWER_STOP_DN                0U                     	 /* 停止模式最低电压（0V） */

#define D_HEATFALUT_CmdOpenLoad        350U                      /* 加热输出开路(0.01A) */
#define D_HEATFALUT_CmdOpenLoad_W      10U                       /* 方向盘加热输出开路(0.01A) */
#define D_HEATFALUT_CmdShortToGnd      8640U                     /* 加热输出对地短路(与硬件吴海都确认后使用此值7.2A+20%)加热垫负载工作电流规格书上标注 7.2A±10%*/
#define D_HEATFALUT_NtcMax             3513U                     /* NTC有效最大值 */
#define D_HEATFALUT_NtcMin             239U                      /* NTC有效最小值 */
#define D_HEATFALUT_NtcOpenLoad        3690U                     /* NTC开路 */
#define D_HEATFALUT_NtcShortToGnd      50U                       /* NTC对地短路 */

#define D_1stLevel_36                  680U                      /* 1档位加热温度 */
#define D_2ndLevel_39                  730U                      /* 2档位加热温度 */
#define D_3rdLevel_45                  770U                      /* 3档位加热温度 */
#define D_3rdLevel_48                  810U                      /* 3档位加热温度 */
#define D_DRVHEAT_PID_D                0U                        /* 微分 */
#define D_DRVHEAT_PID_I                0U                        /* 积分 */
#define D_DRVHEAT_PID_P                18U                       /* 比例 */
#define D_HEAT_HEAT_DEF                30U                       /* 加热差值 */
#define D_SwsLevel_Temp                855U                      /* 方向盘加热温度 */
#define OFF                            0U                        /* 置0 */
#define ON                             1U                        /* 置1 */

#define D_VENT_LVL_1_PRECENT           64U                       /* 通风档位1 */
#define D_VENT_LVL_2_PRECENT           80U                       /* 通风档位2 */
#define D_VENT_LVL_3_PRECENT           100U                        /* 通风档位3 */

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


/* 学习 */
#define D_FirstMove                    1U                        /* 学习功能第一个动作电机 */
#define D_FourthlyMove                 4U                        /* 学习功能第四个动作电机 */
#define D_Invalid                      0U                        /* 电机无配置 */
#define D_RelayVolMaxValue             16000U                    /* 继电器工作最大电压/mv */
#define D_RelayVolMinValue             9000U                     /* 继电器工作最小电压/mv */
#define D_SecondMove                   2U                        /* 学习功能第二个动作电机 */
#define D_ThirdlyMove                  3U                        /* 学习功能第三个动作电机 */




/********************************常用函数********************************/
extern void Com_RamSet(INT8U * buff, INT8U data, INT16U len);
extern BOOL Com_MemCmp(INT8U * TrgBuff, INT8U * SrcBuff, INT8U Len);

/********************************模型使用到的常量********************************/
extern const volatile INT16U CAL_LockErrNoTime_30ms;/* 堵转故障消除：30ms */
extern const volatile INT32U CAL_ManualSwError_2min ;/* 开关粘连时长：120s */
extern const volatile INT32U CAL_ManualSwValid_90s;/* 开关有效时长：90s */
extern const volatile INT8U CAL_MotorHallInvalid_2s;/* 霍尔信号不变化时长：2s */
extern const volatile INT16U CAL_MotorMaxRunTime_60s;/* 电机最大运行时间：60s */
extern const volatile INT16U CAL_MotorRelayErr_2s;/* 继电器粘连时间2s */
extern const volatile INT8U CAL_MotorStall_750ms;/* 霍尔无变化堵转检测时长：750ms */

#endif

