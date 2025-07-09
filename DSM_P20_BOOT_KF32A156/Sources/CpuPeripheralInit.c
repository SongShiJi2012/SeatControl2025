#include "CpuPeripheralInit.h"
#include "kf32a156.h"
#include "kf32a156_osc.h"
#include "system_init.h"
#include "ecual_pins.h"
#include "Output.h"
#include "Bootloader.h"
#include "BootCan.h"
#include "UJA1078.h"
#include "watchdog.h"
#include "ecual_can.h"
#include "tim_driver.h"
#include "ecual_tim.h"
#include "stdio.h"
#include "Srvl_E2memory.h"
#include "kflog.h"
#include "BootFlash.h"

volatile BOOL SysTimer1msFlag;
volatile INT8U SysTimer1msCnt;
volatile INT32U SysTimerCount = 0;

/*************************************************************
* 函数名称：Cpu_Delay10Us
* 功能描述：10us延时函数
* 入口参数：延时多少个10us
* 出口参数：无
* 返 回 值：无
* 备    注：无
************************************************************/
void Cpu_Delay10Us(INT16U usec) 
{
	INT8U i=0;

	while(usec>0u)
	{
		for(i=0;i<33u;i++)
		{
		}
		usec-=1u;
	}
}

static void Cpu_Clock_Init(void)
{	
	SystemInit(120);    /*PLL 120M*/
	systick_delay_init(120);
}

/***********************************************************************
Function :  Cpu_Port_Init()
***********************************************************************/
static void Cpu_Port_Init(void)
{
	ecual_pins_init(PINS_MODE_INIT);
}

/********************************************************************
* 函数名称：Cpu_12V_SW_Enable
* 功能描述：使能输出24V-输入上拉电源,SSB供电电源
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Cpu_12V_SW_Enable(void)
{

}

/********************************************************************
* 函数名称：Cpu_12V_SW_Disable
* 功能描述：停止输出24V-输入上拉电源,SSB供电电源
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Cpu_12V_SW_Disable(void)
{

}

/********************************************************************
* 函数名称：SysTimer1msISR
* 功能描述：LPIT0定时器1ms中断服务函数
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void SysTimer1msISR(void)
{
	SysTimer1msFlag = TRUE;
	SysTimerCount++;
	if(++SysTimer1msCnt >= 5)
	{
		SysTimer1msCnt = 0;
	}
	Boot_1msInterrupt();
}

/********************************************************************
* 函数名称：Cpu_SysTimer_Enable
* 功能描述：使能1ms定时,禁止30ms定时
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Cpu_SysTimer_Enable(void)
{
	ecual_Tim_Enable(TIM_TYPE_GENER,TIM_NUM2);
}

/********************************************************************
* 函数名称：Cpu_SysTimer_Disable
* 功能描述：禁止1ms定时,使能30ms定时
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Cpu_SysTimer_Disable(void)
{
	ecual_Tim_Disable(TIM_TYPE_GENER,TIM_NUM2);
}

/***********************************************************************************************
 * @function name: void Cpu_SysTimer_Init(void)
 * @description:     定时器初始化
 * 			 T =  prescaler*timeoutValue/clkSource
 *   			 WDOG_INTERNAL_CLOCK 32K
 * @input parameters:      void
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void Cpu_SysTimer_Init(void)
{
	Tim_user_config_t UserGTimeCfg;

	UserGTimeCfg.TimType = TIM_TYPE_GENER;
	UserGTimeCfg.TimIndex = TIM_NUM2;
	UserGTimeCfg.clkSource = TIM_EXTHF_CLOCK;
	UserGTimeCfg.Prescaler = 15;
	UserGTimeCfg.TimeCnt = 1000;

	ecual_Tim_init(&UserGTimeCfg,SysTimer1msISR);
}
void USART_Async_config(USART_SFRmap *USARTx)
{
	USART_InitTypeDef USART_InitStructure;

	/* configure USARTx to LIN mode */
	USART_Struct_Init(&USART_InitStructure);
	USART_InitStructure.m_Mode = USART_MODE_FULLDUPLEXASY;
	USART_InitStructure.m_TransferDir = USART_DIRECTION_FULL_DUPLEX;
	USART_InitStructure.m_WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.m_StopBits = USART_STOPBITS_1;
	USART_InitStructure.m_BaudRateBRCKS = USART_CLK_HFCLK;
	/** Use 16M clock as an example to list the following baud rates
	 * 	4800    z:208    x:0    y:0
	 * 	9600    z:104    x:0    y:0
	 * 	19200   z:52     x:0    y:0
	 * 	115200  z:8      x:1    y:13
	*/
	/* Integer part z, get value range is 0 ~ 0xFFFF */
	USART_InitStructure.m_BaudRateInteger = 8;
	/* Numerator part x, get value range is 0 ~ 0x0f */
	USART_InitStructure.m_BaudRateNumerator = 1;
	/* Denominator part y, get value range is 0 ~ 0x0f */
	USART_InitStructure.m_BaudRateDenominator = 13;
	/* Reset and enable USARTx */
	USART_Reset(USARTx);
	USART_Configuration(USARTx,&USART_InitStructure);
	/* Enable UART moudle */
	USART_RESHD_Enable (USARTx, TRUE);
	USART_Cmd(USARTx,TRUE);
}
void DebugInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*
   *  Configure PA3 remap mode
   *  as TX pin
   */
	GPIO_InitStructure.m_Mode = GPIO_MODE_RMP;
	GPIO_InitStructure.m_OpenDrain = GPIO_POD_PP;
	GPIO_InitStructure.m_PullDown = GPIO_NOPULL;
	GPIO_InitStructure.m_PullUp = GPIO_NOPULL;
	GPIO_InitStructure.m_Speed = GPIO_LOW_SPEED;
	GPIO_InitStructure.m_Pin = GPIO_PIN_MASK_6;
	GPIO_Configuration(GPIOH_SFR, &GPIO_InitStructure);

	GPIO_Pin_RMP_Config(GPIOH_SFR, GPIO_Pin_Num_6, GPIO_RMP_AF3);
	USART_Async_config(USART1_SFR);
}
/********************************************************************
* 函数名称：CPU_System_Init
* 功能描述：MCU初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void CPU_System_Init(void)
{
	SBC_WDOFF();
	INT_All_Enable (FALSE);
	Cpu_Clock_Init();
	Cpu_Port_Init();
	Cpu_SysTimer_Init();
	Srvl_E2Init();
    BootFlash_Init();
    Srvl_E2OptInit();
	SBC_WDOFF();
//	WDOG_Init(2000); /*2s*/
	BootCANInit();
	Output_FeedWatchDog();
	INT_All_Enable(TRUE);
#if CANTXDEBUG
	DebugInit();
	USART_SendData(USART1_SFR, 0XAA);
#endif
//    kfLog_Init();
//	kf_printf("Boot Init");
}

void CpuClosePeriphal(void)
{
	Boot_DisableInterrupts;
	ecual_CAN_Deinit(0);
}


/***********************************************************************************************
 * @function name:  CPU_GetTimeCount
 * @description:
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
INT32U CPU_GetTimeCount(void)
{
	return SysTimerCount;
}

/***********************************************************************************************
 * @function name:  CPU_TimerDiffTs
 * @description:
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2022-07-26
 ***********************************************************************************************/
INT32U CPU_TimerDiffTs(INT32U lastTs)
{
    INT32U Ts = CPU_GetTimeCount();

    if (lastTs > Ts)
    {
        /* overflow */
        Ts = (0xFFFFFFFFUL - lastTs) + Ts + 1U;
    }
    else
    {
        Ts = Ts - lastTs;
    }

    return Ts;
}
