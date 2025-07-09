#ifndef _CPU_H
#define _CPU_H

#include  "Common.h"

#define LPIT_1MS_CHL			(0u) /*1ms对应LPTI0的通道0*/
#define LPIT_30MS_CHL			(1u) /*30ms对应LPTI0的通道1*/

/*主控上拉电源开关控制*/
#define POWER12VSWGPIO			(PTE)
#define POWER12VSWPIN			(1ul << 1u)
/*SSB电源输出开关控制*/
#define POWERSSBSWGPIO			(PTA)
#define POWERSSBSWPIN			(1ul << 11u)
/*主控外部上拉电源开关控制*/
#define POWER12VOUTSWGPIO		(PTC)
#define POWER12VOUTSWPIN		(1ul << 16u)

#define		D_PIN_WATCHDOG_GPIO			(GPIOE_SFR)
#define		D_PIN_WATCHDOG_NUM			(9U)

#define		D_PIN_WATCHDOG_MASK			(GPIO_PIN_MASK_9)

#define		D_ON			(1u)
#define		D_OFF			(0u)
/*SBC看门狗控制*/
#define	SBC_WDOFF()			do{GPIO_Write_Mode_Bits(D_PIN_WATCHDOG_GPIO, D_PIN_WATCHDOG_MASK, GPIO_MODE_OUT );PINS_DRV_WritePin(D_PIN_WATCHDOG_GPIO, D_PIN_WATCHDOG_NUM, D_ON);}while(0)
#define	SBC_WDON()			PINS_DRV_WritePin(D_PIN_WATCHDOG_GPIO, D_PIN_WATCHDOG_NUM, D_OFF)


/* Definition of power modes indexes, as configured in Power Manager Component
 *  Refer to the Reference Manual for details about the power modes.
 */
#define POWER_MODES (2u)
#define RUNMODE   	(0u) /* Run                 */
#define STOPMODE  	(1u) /* Stop mode           */




extern volatile BOOL SysTimer1msFlag;
extern volatile INT8U SysTimer1msCnt;
extern volatile INT32U SysTimerCount;


/*************************************************************
* 函数名称：Cpu_Delay10Us
* 功能描述：微秒延时函数
* 入口参数：延时多少微秒
* 出口参数：无
* 返 回 值：无
* 备    注：无
************************************************************/
extern void Cpu_Delay10Us(INT16U usec);
extern void CPU_System_Init(void);
extern void Cpu_12V_SW_Enable(void);
extern void Cpu_12V_SW_Disable(void);
void Cpu_SysTimer_Enable(void);
void Cpu_SysTimer_Disable(void);
void CpuClosePeriphal(void);
void SysTimer1msISR(void);
INT32U CPU_GetTimeCount(void);
INT32U CPU_TimerDiffTs(INT32U lastTs);

#endif

