/********************Copyright (c) Fuxin Dare Automotive Parts Co.LTD.*********************
** File Name:              	Common.h
** Author:           		Feliks.Peng
** Date:            			2017.5.11
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
#include "kf32a156.h"
#include <string.h>
#include   "BootDescConfig.h"

/* 工程配置 */
#define DSM_C52X_PROJECT											1
#define DSM_B60V_PROJECT											2
#define DSM_B30X_PROJECT											6
#define DSM_PD014_PROJECT											7
#define DSM_CURRECT_PROJECT											DSM_PD014_PROJECT


#define ZNA_SA
#define APP_DEBUG 		(0u) /*置位后,停留在boot不会跳转到app去*/
#define E2_DEBUG 		(0u) /*由于e2为外挂，调试需要擦除时，需要手动打开擦除app有效标志，再关闭*/

#define TASKMAX         (20)
#define PrioHighRdy     (0)
#define PrioLowest      (TASKMAX - 1)

#define HANDDANG		(0x00u) /*手动挡配置*/
#define AUTOHAND		(0x02u) /*自动挡配置*/
#define HANDAUTOMASK	(0x03u) /*配置状态掩码*/

/*电压检测配置*/
/*13.5v*/
#define V135_UP			(160u) /*16V*/
#define V135_DOWN		(90u) /*9V*/
#define V135_LAG		(5u) /*检测迟滞*/
/*24.0v*/
#define V240_UP			(280u) /*28V*/
#define V240_DOWN		(200u) /*20V*/
#define V240_LAG		(5u) /*检测迟滞*/

#define DESC_APP_BOOT_NULL				(0u) /*app 未跳转到 boot*/
#define DESC_APP_BOOT_NEED_RESP			(1u) /*app 跳转到 boot后,boot需回复*/
#define DESC_APP_BOOT_NO_NEED_RESP		(2u) /*app 跳转到 boot后,boot无需回复*/
#define D_DIAG_NeedUpdateSort_Init				(0xFFU)


#define  SystemSoftwareReset()  asm("RESET")

/********************************   Typedef Definitions  ********************************/
typedef unsigned char   BOOL;
typedef	signed char		INT8S;
typedef	unsigned char	INT8U;
typedef	signed short	INT16S;
typedef	unsigned short	INT16U;
typedef	signed int		INT32S;
typedef	unsigned int	INT32U;

#define ToolMake16Bit(hiByte,loByte)                                 ((INT16U)((((INT16U)(hiByte))<<8)| \
                                                                     ((INT16U)(loByte))))
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


typedef	enum
{	
	ev5ms = 0,
	ev3ms,
	ev10ms,	
	evNext5ms,
	ev20ms,
	ev50ms,

	evTrunk,
	evLeftPE,
	evRightPE,
	evLeftLock,
	evKeyIn,
	evPush,
	evIGN1,
	evLeftReq,
	evRightReq,
	evESCL_FB1,
	evESCL_FB2,
	evStart_FB,
	evClutch1,
	evClutch2,
	evIGN2,
	evPPosition,
	evNPosition,
	evFootPlate2,
	evFootPlate1,
	evACC,
	evPDang,
	evNDang,
	evHandPark,
	evST,
	evCrashUnlock,
}TaskId;



/********************************   Definitions  ********************************/
#ifndef	TRUE
//#define TRUE           	(1)
#endif

#ifndef FALSE
//#define FALSE         	(0)
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

#define     D_Success       (1u)
#define     D_Failure       (0u)
#define     D_E2_WriteWait  (2u)

#define		D_HIGH			(1u)
#define		D_LOW			(0u)

#define ENTER_CRITICAL()         	INT_SYS_DisableIRQGlobal()
#define EXIT_CRITICAL()       		INT_SYS_EnableIRQGlobal()

#define ENABLE_STOP()             	
#define DISABLE_STOP()             	

#define IsE2promPwrVoltNormal()		(1u)

/* 求数组个数 */
#define UBOUND(__ARRAY) (sizeof(__ARRAY)/sizeof(__ARRAY[0])) 

/*LIN*/
#define SYNCH_DATA              		(0x55)

/********************************常用函数********************************/
extern void Com_RamSet(INT8U * buff, INT8U data, INT16U len);
extern BOOL Com_MemCmp(INT8U * TrgBuff, INT8U * SrcBuff, INT8U Len);

#endif

