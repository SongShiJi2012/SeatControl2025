
#include <Ecual_lin.h>
#include "UserTask.h"
#include "CpuPeripheralInit.h"
#include "Srvl_E2memory.h"
#include "Ecual_Adc.h"
#include "Srvl_CanSignals.h"
#include "CANDrv.h"
#include "Srvl_NM.h"
#include "AppDesc.h"
#include "DescComCtrl.h"
#include "Desc.h"
#include "DSM.h"
#include "Event.h"
#include "MidRelay.h"
#include "stdlib.h"
#include "string.h"
#include "DescRoutineCtlList.h"
#include "Test.h"
#include "Cdd_Hall.h"
#include "Cdd_Ntc.h"
#include "Srvl_PowerMode.h"
#include "Ecual_AdcMotor.h"
#include "App_ModelHeader.h"
#include "Appl_DtcSetConditionCheck.h"
#include "Srvl_Tle9210x.h"
#include "kflog.h"
#include "Srvl_Eeprom.h"
#include "OsekNmSleep.h"

static void AppApp1msTask(void);
static void AppApp5msTask(void);
static void AppApp10msTask(void);
static void AppApp20msTask(void);
static void AppApp50msTask(void);
/***********************************************************************************************
 * @function name:  APPL_AllModel_initialize
 * @description:    ����ģ�ͳ�ʼ���ӿڣ�ͳһ���ø���ģ���ʼ������
 * @input parameters:  void
 * @output parameters: void
 * @return:         void
 * @author:         ssj 2025-05-28
 ***********************************************************************************************/
void APPL_AllModel_initialize(void)
{
    /* ��ʻ�����ģ�ͳ�ʼ�� */
    APPL_DriverFaultDetection_initialize();
    Appl_DrMotorAdjust_CtrlModel_initialize();
    Appl_DrComfort_CtrlModel_initialize();
    Appl_DrMemory_CtrlModel_initialize();
    Appl_DrRestMode_CtrlModel_initialize();
    Appl_MassageMode_CtrlModel_initialize();
    Appl_VentAdj_CtrlModel_initialize();
    Appl_DrLearn_CtrlModel_initialize();

    /* ����ʻ�����ģ�ͳ�ʼ�� */
    APPL_PaFaultDetection_initialize();
    Appl_PaAdjustModel_initialize();
    Appl_PaComfort_CtrlModel_initialize();
    Appl_PaMemory_CtrlModel_initialize();
    Appl_PaLearn_CtrlModel_initialize();

    /* ����ģ�����ģ�ͳ�ʼ�� */
    Appl_PowerMangeModel_initialize();
    Appl_HeatAdj_CtrlModel_initialize();
    Appl_HeatFault_CtrlModel_initialize();
}
/***********************************************************************************************
 * @function name: App_AllModels_Step
 * @description: ����P20�ο�˳�����ε������θ�ģ�͵Ĵ�����
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
void App_AllModels_Step(void)
{
    /* ��ʻ�����ģ�� */
    APPL_DriverFaultDetection_step();
    Appl_DrMotorAdjust_CtrlModel_step();
     DescIOCtrl_DrSeatMoveTask(); // ���IO��������
    Appl_DrComfort_CtrlModel_step();
    Appl_DrMemory_CtrlModel_step();
    Appl_DrRestMode_CtrlModel_step();
    Appl_MassageMode_CtrlModel_step();
    Appl_VentAdj_CtrlModel_step();
    Appl_DrLearn_CtrlModel_step();

    /* ����ʻ�����ģ�� */
    APPL_PaFaultDetection_step();
    Appl_PaAdjustModel_step();
    DescIOCtrl_PaSeatMoveTask(); // ���IO��������
    Appl_PaComfort_CtrlModel_step();
    Appl_PaMemory_CtrlModel_step();
    Appl_PaLearn_CtrlModel_step();
    /* ����ģ����� */
    // Diag_TaskServices(); // 4ms��������-20241203
    Appl_PowerMangeModel_step();
    Appl_HeatAdj_CtrlModel_step();
    Appl_HeatFault_CtrlModel_step();
    // Appl_HeatVentCanOutTask(); // ��ͨ��CAN�������
    Appl_VentAdj_CtrlModel_step();
}
/***********************************************************************************************
 * @function name: AppAppRam_Init
 * @description: ϵͳ��ʼ��������ִ�и�Ӳ���������ĳ�ʼ������������ADC��GPIO��CAN��ϵͳ��ʱ����
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
void AllTask_Init()
{
	Ecual_ADC_Init();
	Cpu_SysTimer_Enable();
	/*�״��ϵ�*/
	ComCtrlInit();		//Feliks:��Ҫ�������ϵ��ʱ����ܳ�ʼ�������Ѳ���ִ�иú�������Ϊ�ᵼ�����籨�ķ���
	Ecual_CanRxStateInit();  //ֻ�������ϵ�ų�ʼ��
	Ecual_FNOSInit();

	//�ϵ��ȡ��һ�εĵ��λ��,ֻ����븳ֵһ��
	DescInit();
	TPInit();
	CANDrvInit();
	Nm_InitStart();
    CANDrvNMTxProcess();
    CANDrvMSCAN_vogFillTxEmptyBuffers(FALSE);

	Srvl_E2PowerOnInit();
	Cdd_ReadAllHallFromE2();

	APPL_AllModel_initialize();
    
    kfLog_Init();
	kf_printf("usart Init\r\n");
    Srvl_Tle9210x_SpiMasterInit();
    Srvl_Tle9210x_Init(EN_TLE9210X_NUM_1);
    Srvl_Tle9210x_Init(EN_TLE9210X_NUM_2);
}
/***********************************************************************************************
 * @function name: AppApp1msTask
 * @description: 1ms������������
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp1msTask(void)
{
	Ecual_CanCheckSendTask();
}
/***********************************************************************************************
 * @function name: AppApp5msTask
 * @description: 5ms��������������ִ��������ơ�CANͨ�š�������񡢵�Դ����EEPROM��ѯ
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp5msTask(void)
{

	Ecual_CanTask();
	Ecual_CanRxStateMonitor();
	AppDescPinAttackProcess();//��ȫ����ʱ������
	//�����ѹ��ֵ���
	Srvl_Set_SupplyVoltage();
	Ecual_GpioScan();//������ѯ
}

/***********************************************************************************************
 * @function name: AppApp10msTask
 * @description: 10ms��������������ִ�й��Ϲ�����Դ״̬���á� ADC��ѯ��ģ�ʹ���
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp10msTask(void)
{
	Ecual_ADC_SoftwareStartConv();//�ֶ�����ADCת��
	Diag_MonitorEnableCriteriaCheck();
//	Diag_LoadDiagHandle();
	Diag_DtcRecordHandle();
	Cdd_Ntc_Task();
	Ecual_AdcMotorPollingTask();
	App_AllModels_Step();
	MidRelay_MotorCtrlProc();
    Srvl_Tle9210x_MainCycleFunction();

    Ecual_AdcScanAll();//����ɨ��
    Srvl_E2WritePollingIfReady();//��10ms���� ��֤DMA�� �������
}

/***********************************************************************************************
 * @function name: AppApp20msTask
 * @description: 20ms��������������ִ��˯��������顢��Դ����ͼ̵�����ʱ�ϵ�
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp20msTask(void)
{
	Srvl_E2CheckWriteResultAndResp();
    OsekNmSleep_SleepDescFunction();
	//��ʱ�ϵ磬�����ϵ�̵���������Ч
//	PWR_12V_ON();
}

/***********************************************************************************************
 * @function name: AppApp50msTask
 * @description: 50ms��������������ִ��EEPROM��־���º�˯�߹�������
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp50msTask(void)
{
	Srvl_E2FlagUpdateTask();
//	SleepManageTask();
}
/***********************************************************************************************
 * @function name: AppAppCycEvent
 * @description: �������¼������������ݵ����¼�ִ�ж�Ӧ��������
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
void AppAppCycEvent(void)
{
	Ecual_LINSchTick();
	Ecual_HandleHallAndTriggerAdc();
	switch(PopEvent())
	{
		case ev1ms :
			AppApp1msTask();
			#if D_TEST_SW
				Test_Main();
			#endif
			break;
		case  ev5ms :
			AppApp5msTask();
			break;
		case  ev10ms :
			AppApp10msTask();
			break;
		case  ev20ms :
			AppApp20msTask();
			break;
		case  ev50ms :
			AppApp50msTask();
			break;
		default :
			break;
	}
}
