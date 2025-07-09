
#define     CPUPERINITGLOBALS

#include "CpuPeripheralInit.h"
#include "system_init.h"
#include "Event.h"
#include "Cdd_Hall.h"
#include "DSM.h"
#include "ecual_pins.h"
#include "kf32a156_gtim.h"
#include "kf32a156_btim.h"
#include "kf32a156_int.h"
#include "ecual_ftm.h"
#include "tim_driver.h"
#include "ecual_tim.h"
#include "SPI.h"
#include "test.h"
#include "ecual_wdog.h"
#include "Srvl_E2memory.h"
#include <Ecual_lin.h>

volatile INT32U SysTimerCount = 1;//P20�������ʼ����ȡ���ʱ����з�0�ж� ������Ҫ��ʼ��Ϊ��0
extern const INT32U _g_flash_origin; // �����ⲿ����- ��ȫ�ֱ�����ַΪld�е�flash��ʼ��ַ��

#define          SYSTIMETASK                              5
const		INT8U           ConstAppTime[SYSTIMETASK] =
{
	256 - 5,
	256 - 10,
	256 - 20,
	256 - 50,
	256 - 1,
};

static              INT8U         SystemAppTime[SYSTIMETASK] =
{
	256 - 2,
	256 - 4,
	256 - 5,
	256 - 6,
	256 - 7,
};


/*************************************************************
* �������ƣ�Cpu_Delay10Us
* ����������10us��ʱ����
* ��ڲ�������ʱ���ٸ�10us
* ���ڲ�������
* �� �� ֵ����
* ��    ע����
************************************************************/
void Cpu_Delay10Us(INT16U usec)
{
	INT8U i = 0;

	while(usec > 0u)
	{
		for(i = 0; i < 33u; i++)
		{
		}
		usec -= 1u;
	}
}

static void Cpu_Clock_Init(void)
{
	SystemInit(120);
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
* �������ƣ�Cpu_SystemTimer_IRQ
* ����������1Ms��ʱ���жϵ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Cpu_SystemTimer_IRQ(void)
{
	INT8U         Index;

	SysTimerCount++;
	for(Index = 0x00; Index < SYSTIMETASK; Index++)
	{
		SystemAppTime[Index]++;
		if(SystemAppTime[Index] == 0x00)
		{
			SystemAppTime[Index] = ConstAppTime[Index];
			PushEvent(Index, Index);
		}
	}
}

/********************************************************************
* �������ƣ�Cpu_SysTimer_Enable
* ����������ʹ��1ms��ʱ
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Cpu_SysTimer_Enable(void)
{
	 ecual_Tim_Enable(TIM_TYPE_GENER,TIM_NUM2);
}

/********************************************************************
* �������ƣ�Cpu_SysTimer_Disable
* ������������ֹ1ms��ʱ,ʹ��100ms��ʱ
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Cpu_SysTimer_Disable(void)
{
	ecual_Tim_Disable(TIM_TYPE_GENER,TIM_NUM2);
}

/***********************************************************************************************
 * @function name: void Cpu_SysTimer_Init(void)
 * @description:     ��ʱ����ʼ��
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

	ecual_Tim_init(&UserGTimeCfg,Cpu_SystemTimer_IRQ);
}
/***********************************************************************************************
 * @function name: void Cpu_T21Timer_Init(void)
 * @description:    ���ڼ����������ʱ��� ����1us ���1us  (0��Ƶ ,Ƶ��16M,��Ҫʹ���жϣ���������ע���жϻص�)
 * 					t = CNT * 1/16M
 * @author:         2025-03-10 ssj
 ***********************************************************************************************/
void Cpu_T21Timer_Init(void)
{
	Tim_user_config_t UserGTimeCfg;

	UserGTimeCfg.TimType = TIM_TYPE_GENER;
	UserGTimeCfg.TimIndex = TIM_NUM7;
	UserGTimeCfg.clkSource = TIM_EXTHF_CLOCK;
	UserGTimeCfg.Prescaler = 0;
	UserGTimeCfg.TimeCnt = 0xFFFFFFFF;

	ecual_Tim_init(&UserGTimeCfg,NULL);

	ecual_Tim_Enable(TIM_TYPE_GENER,TIM_NUM7);
}

/********************************************************************
* �������ƣ�CPU_System_Init
* ����������MCU��ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void CPU_System_Init(void)
{
	Cpu_Clock_Init();
	Srvl_E2Init();
	Cpu_Port_Init();
	Cpu_SysTimer_Init();
#if D_TEST_TIMER_SW
	Cpu_T21Timer_Init();
#endif
	Ecual_FTM_CCP_PWM_Init();//ͨ��PWM��ʼ��
	Ecual_LinInit();
//	ecual_WDOG_init(2000); /*2000ms*/
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
 * @function name:  CPU_GetFlashStartAddr
 * @description: ��ȡ������ʼ��ַ
 * @input parameters: ��
 * @output parameters: INT32U-��ʼ��ֵַ
 * @return: ��
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
INT32U CPU_GetFlashStartAddr(void)
{
    const INT32U AppFlashStartAddr = (INT32U)&_g_flash_origin;

    return AppFlashStartAddr;
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
/***********************************************************************************************
 * @function name: void CPU_ECUSoftwareReset
 * @description: ִ�������ʽ�� ECU ��λ��ͨ������ RESET ���ָ��ʵ��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void CPU_ECUSoftwareReset(void)
{
	asm("RESET");
	while(1);
}
