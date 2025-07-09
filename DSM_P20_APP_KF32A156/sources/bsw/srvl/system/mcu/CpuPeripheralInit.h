#ifndef _CPU_H
#define _CPU_H

#include  "Common.h"


#ifdef		CPUPERINITGLOBALS
#define		CPUPERINIT_EXT
#else
#define		CPUPERINIT_EXT                                                extern
#endif

#define D_HAL_GET_CUR_MS_TS()       CPU_GetTimeCount()


#define LPIT_1MS_CHL			(0u) /*1ms对应LPTI0的通道0*/
#define LPIT_25MS_CHL			(1u) /*25ms对应LPTI0的通道1*/

/*主控上拉电源开关控制*/
#define POWER12VSWGPIO			(PTE)
#define POWER12VSWPIN			(1ul << 1u)
/*SSB电源输出开关控制*/
#define POWERSSBSWGPIO			(PTA)
#define POWERSSBSWPIN			(1ul << 11u)
/*主控外部上拉电源开关控制*/
#define POWER12VOUTSWGPIO		(PTC)
#define POWER12VOUTSWPIN		(1ul << 16u)


/* Definition of power modes indexes, as configured in Power Manager Component
 *  Refer to the Reference Manual for details about the power modes.
 */
#define POWER_MODES (2u)
#define RUNMODE   	(0u) /* Run                 */
#define STOPMODE  	(1u) /* Stop mode           */




CPUPERINIT_EXT volatile INT32U SysTimerCount;

/*************************************************************
* 函数名称：Cpu_Delay10Us
* 功能描述：微秒延时函数
* 入口参数：延时多少微秒
* 出口参数：无
* 返 回 值：无
* 备    注：无
************************************************************/
CPUPERINIT_EXT void Cpu_Delay10Us(INT16U usec);

CPUPERINIT_EXT void CPU_System_Init(void);
CPUPERINIT_EXT void Cpu_Interrupt(void);
CPUPERINIT_EXT void Cpu_SysTimer_Enable(void);
CPUPERINIT_EXT void Cpu_SysTimer_Disable(void);

CPUPERINIT_EXT INT32U CPU_GetTimeCount(void);
CPUPERINIT_EXT INT32U CPU_TimerDiffTs(INT32U lastTs);
extern void CPU_ECUSoftwareReset(void);
extern INT32U CPU_GetFlashStartAddr(void);

#endif

