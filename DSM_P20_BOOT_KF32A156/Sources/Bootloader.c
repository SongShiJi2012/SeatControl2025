#include   "Bootloader.h"
#include "kf32a156_int.h"
#include   "BootDesc.h"
#include "Output.h"
#include   "BootCan.h"
#include "BootFlash.h"
//#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "CpuPeripheralInit.h"
#include "ecual_pins.h"
#include "ecual_can.h"
#include "ecual_wdog.h"

BOOL    Boot_1msFlag = FALSE;
INT8U   Boot_Event5msTime = 1; // 初始化不同的值, 为了错开5ms和10ms任务同时出现
INT8U   Boot_Event10msTime = 3;

BOOL	BootEnterAppFlag = FALSE;
BOOL    AppCodeValidFlg = FALSE;
BOOL    g_E2promAppCodeValidFlg = FALSE;
INT16U  EnterAppDelayTimeCnt = D_EnterAppDelayTime_100ms;

uint32_t AppStackPtr; /*应用程序起始地址*/
uint32_t AppEntryPtr; /*应用程序进入地址*/

typedef  void (*pFunction)(void); //定义void函数指针类型，
pFunction Jump_To_Application; //它可以接受任何类型函数的赋值
uint32_t JumpAddress;
#define  ApplicationAddress  D_AppCodeStart_Addr
void __set_MSP(uint32_t value){
asm(" MOV SP,%0 \n": :"r"(value): "sp");
}


/*******************************************************************************
* 函数名称：Boot_System_Init
* 功能描述：系统变量初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void    Boot_System_Init(void)
{
	Boot_1msFlag = FALSE;
	Boot_Event5msTime= 0x00;
	Boot_Event10msTime = 0x00;
	//BootCANInitOKFlag = FALSE;
	//BootMsgNeedTxIndFlag = 0x00;
}

/*******************************************************************************
* 函数名称：Boot_1msInterrupt
* 功能描述：1ms中断函数
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void    Boot_1msInterrupt(void)
{
	Boot_1msFlag = TRUE;
}

/*******************************************************************************
* 函数名称：Boot_5msTask
* 功能描述：5ms任务处理
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void    Boot_5msTask(void)
{
	Boot_SecurityAccess_u2gRand ++;
	//BootCANInit();
	Srvl_E2WritePolling();
	BootCANTask();
	AppAppE2promCheckReadAndWiteResultAndResp();
}

/*******************************************************************************
* 函数名称：BootUp_Application
* 功能描述：Boot跳转入App
* 入口参数：
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void BootUp_Application(uint32_t appEntry, uint32_t appStack)
{
//    static void (*jump_to_application)(void);
//    static uint32_t stack_pointer;
//
//    jump_to_application = (void (*)(void))appEntry;
//    stack_pointer = appStack;
//
//    Output_FeedWatchDog();
//    S32_SCB->VTOR = D_AppCodeStart_Addr;
//    //__set_MSP(stack_pointer);
//    __asm volatile ("MSR msp, %0\n" : : "r" (stack_pointer) : "sp");
//    //__set_PSP(stack_pointer);
//    __asm volatile ("MSR psp, %0\n" : : "r" (stack_pointer) : "sp");
//
//    Output_FeedWatchDog();
//    jump_to_application();

	/*引导APP程序执行*/
	if(*(volatile uint32_t*)ApplicationAddress == 0x10010000 ) //判断APP空间的首个字内容是否为栈顶地址0x10010000，正确则说明APP程序已经写入
	{

		//Boot_ALLDeInit();  屏蔽所有外设
		Output_FeedWatchDog();
		ecual_pins_init(PINS_MODE_OFFMODE);
		ecual_CAN_Deinit(0);
		ecual_WDOG_dinit();
		INT_All_Enable(FALSE);

		SYS_VECTOFF = ApplicationAddress ; //设置向量表偏移值，即重映射向量表，这对中断服务函数正确执行至关重要

		JumpAddress = *(volatile uint32_t*) (ApplicationAddress + 4); //获取APP的startup()入口地址
		Jump_To_Application = (pFunction) JumpAddress; //将startup()入口地址赋值给函数指针
		__set_MSP(*(uint32_t*) ApplicationAddress);
		Jump_To_Application(); //使用新的函数指针，转向执行APP的startup()函数，这将导致APP程序启动
	}
}

/*******************************************************************************
* 函数名称：Boot_10msTask
* 功能描述：10ms任务处理
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void    Boot_10msTask(void)
{
    Output_FeedWatchDog();
    //AD1_Task();
    //SystemPowerModeCheckTask();
//    AppE2promReadTask();

	EraseAllAppCodeFlashBlockTask(); // 日产使用  此函数会一次性把AppCode的Flash擦完

    // 检测是否满足跳转到App条件
    if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg) && (TRUE == BootEnterAppFlag)) //
    {
        if(EnterAppDelayTimeCnt)
        {
            EnterAppDelayTimeCnt --;
        }
    }

	if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg) && (TRUE == BootEnterAppFlag) && (0 == EnterAppDelayTimeCnt)) // 满足跳转到App条件
	{
		Output_FeedWatchDog();
		AppStackPtr=*(uint32_t*)D_AppCodeStart_Addr;
		AppEntryPtr=*(uint32_t*)(D_AppCodeStart_Addr+4u);
		BootUp_Application(AppEntryPtr,AppStackPtr);
	}

}

