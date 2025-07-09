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
INT8U   Boot_Event5msTime = 1; // ��ʼ����ͬ��ֵ, Ϊ�˴�5ms��10ms����ͬʱ����
INT8U   Boot_Event10msTime = 3;

BOOL	BootEnterAppFlag = FALSE;
BOOL    AppCodeValidFlg = FALSE;
BOOL    g_E2promAppCodeValidFlg = FALSE;
INT16U  EnterAppDelayTimeCnt = D_EnterAppDelayTime_100ms;

uint32_t AppStackPtr; /*Ӧ�ó�����ʼ��ַ*/
uint32_t AppEntryPtr; /*Ӧ�ó�������ַ*/

typedef  void (*pFunction)(void); //����void����ָ�����ͣ�
pFunction Jump_To_Application; //�����Խ����κ����ͺ����ĸ�ֵ
uint32_t JumpAddress;
#define  ApplicationAddress  D_AppCodeStart_Addr
void __set_MSP(uint32_t value){
asm(" MOV SP,%0 \n": :"r"(value): "sp");
}


/*******************************************************************************
* �������ƣ�Boot_System_Init
* ����������ϵͳ������ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: 
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
* �������ƣ�Boot_1msInterrupt
* ����������1ms�жϺ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: 
*******************************************************************************/
void    Boot_1msInterrupt(void)
{
	Boot_1msFlag = TRUE;
}

/*******************************************************************************
* �������ƣ�Boot_5msTask
* ����������5ms������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: 
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
* �������ƣ�BootUp_Application
* ����������Boot��ת��App
* ��ڲ�����
* ���ڲ�������
* �� �� ֵ����
* ��    ע: 
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

	/*����APP����ִ��*/
	if(*(volatile uint32_t*)ApplicationAddress == 0x10010000 ) //�ж�APP�ռ���׸��������Ƿ�Ϊջ����ַ0x10010000����ȷ��˵��APP�����Ѿ�д��
	{

		//Boot_ALLDeInit();  ������������
		Output_FeedWatchDog();
		ecual_pins_init(PINS_MODE_OFFMODE);
		ecual_CAN_Deinit(0);
		ecual_WDOG_dinit();
		INT_All_Enable(FALSE);

		SYS_VECTOFF = ApplicationAddress ; //����������ƫ��ֵ������ӳ������������жϷ�������ȷִ��������Ҫ

		JumpAddress = *(volatile uint32_t*) (ApplicationAddress + 4); //��ȡAPP��startup()��ڵ�ַ
		Jump_To_Application = (pFunction) JumpAddress; //��startup()��ڵ�ַ��ֵ������ָ��
		__set_MSP(*(uint32_t*) ApplicationAddress);
		Jump_To_Application(); //ʹ���µĺ���ָ�룬ת��ִ��APP��startup()�������⽫����APP��������
	}
}

/*******************************************************************************
* �������ƣ�Boot_10msTask
* ����������10ms������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: 
*******************************************************************************/
void    Boot_10msTask(void)
{
    Output_FeedWatchDog();
    //AD1_Task();
    //SystemPowerModeCheckTask();
//    AppE2promReadTask();

	EraseAllAppCodeFlashBlockTask(); // �ղ�ʹ��  �˺�����һ���԰�AppCode��Flash����

    // ����Ƿ�������ת��App����
    if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg) && (TRUE == BootEnterAppFlag)) //
    {
        if(EnterAppDelayTimeCnt)
        {
            EnterAppDelayTimeCnt --;
        }
    }

	if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg) && (TRUE == BootEnterAppFlag) && (0 == EnterAppDelayTimeCnt)) // ������ת��App����
	{
		Output_FeedWatchDog();
		AppStackPtr=*(uint32_t*)D_AppCodeStart_Addr;
		AppEntryPtr=*(uint32_t*)(D_AppCodeStart_Addr+4u);
		BootUp_Application(AppEntryPtr,AppStackPtr);
	}

}

