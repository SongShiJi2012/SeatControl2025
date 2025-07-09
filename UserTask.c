
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
 * @description:    所有模型初始化接口，统一调用各子模块初始化函数
 * @input parameters:  void
 * @output parameters: void
 * @return:         void
 * @author:         ssj 2025-05-28
 ***********************************************************************************************/
void APPL_AllModel_initialize(void)
{
    /* 驾驶座相关模型初始化 */
    APPL_DriverFaultDetection_initialize();
    Appl_DrMotorAdjust_CtrlModel_initialize();
    Appl_DrComfort_CtrlModel_initialize();
    Appl_DrMemory_CtrlModel_initialize();
    Appl_DrRestMode_CtrlModel_initialize();
    Appl_MassageMode_CtrlModel_initialize();
    Appl_VentAdj_CtrlModel_initialize();
    Appl_DrLearn_CtrlModel_initialize();

    /* 副驾驶座相关模型初始化 */
    APPL_PaFaultDetection_initialize();
    Appl_PaAdjustModel_initialize();
    Appl_PaComfort_CtrlModel_initialize();
    Appl_PaMemory_CtrlModel_initialize();
    Appl_PaLearn_CtrlModel_initialize();

    /* 公共模块相关模型初始化 */
    Appl_PowerMangeModel_initialize();
    Appl_HeatAdj_CtrlModel_initialize();
    Appl_HeatFault_CtrlModel_initialize();
}
/***********************************************************************************************
 * @function name: App_AllModels_Step
 * @description: 按照P20参考顺序，依次调用座椅各模型的处理函数
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
void App_AllModels_Step(void)
{
    /* 驾驶座相关模型 */
    APPL_DriverFaultDetection_step();
    Appl_DrMotorAdjust_CtrlModel_step();
     DescIOCtrl_DrSeatMoveTask(); // 诊断IO控制任务
    Appl_DrComfort_CtrlModel_step();
    Appl_DrMemory_CtrlModel_step();
    Appl_DrRestMode_CtrlModel_step();
    Appl_MassageMode_CtrlModel_step();
    Appl_VentAdj_CtrlModel_step();
    Appl_DrLearn_CtrlModel_step();

    /* 副驾驶座相关模型 */
    APPL_PaFaultDetection_step();
    Appl_PaAdjustModel_step();
    DescIOCtrl_PaSeatMoveTask(); // 诊断IO控制任务
    Appl_PaComfort_CtrlModel_step();
    Appl_PaMemory_CtrlModel_step();
    Appl_PaLearn_CtrlModel_step();
    /* 公共模块相关 */
    // Diag_TaskServices(); // 4ms周期任务-20241203
    Appl_PowerMangeModel_step();
    Appl_HeatAdj_CtrlModel_step();
    Appl_HeatFault_CtrlModel_step();
    // Appl_HeatVentCanOutTask(); // 热通风CAN输出任务
    Appl_VentAdj_CtrlModel_step();
}
/***********************************************************************************************
 * @function name: AppAppRam_Init
 * @description: 系统初始化函数，执行各硬件和驱动的初始化工作，包括ADC、GPIO、CAN、系统定时器等
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
void AllTask_Init()
{
	Ecual_ADC_Init();
	Cpu_SysTimer_Enable();
	/*首次上电*/
	ComCtrlInit();		//Feliks:需要放置在上电的时候才能初始化，唤醒不能执行该函数，因为会导致网络报文发送
	Ecual_CanRxStateInit();  //只有重新上电才初始化
	Ecual_FNOSInit();

	//上电获取上一次的电机位置,只需进入赋值一次
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
 * @description: 1ms周期任务处理函数
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp1msTask(void)
{
	Ecual_CanCheckSendTask();
}
/***********************************************************************************************
 * @function name: AppApp5msTask
 * @description: 5ms周期任务处理函数，执行输出控制、CAN通信、诊断任务、电源管理及EEPROM轮询
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp5msTask(void)
{

	Ecual_CanTask();
	Ecual_CanRxStateMonitor();
	AppDescPinAttackProcess();//安全访问时间限制
	//供电电压数值检测
	Srvl_Set_SupplyVoltage();
	Ecual_GpioScan();//输入轮询
}

/***********************************************************************************************
 * @function name: AppApp10msTask
 * @description: 10ms周期任务处理函数，执行故障管理、电源状态设置、 ADC轮询及模型处理
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp10msTask(void)
{
	Ecual_ADC_SoftwareStartConv();//手动触发ADC转换
	Diag_MonitorEnableCriteriaCheck();
//	Diag_LoadDiagHandle();
	Diag_DtcRecordHandle();
	Cdd_Ntc_Task();
	Ecual_AdcMotorPollingTask();
	App_AllModels_Step();
	MidRelay_MotorCtrlProc();
    Srvl_Tle9210x_MainCycleFunction();

    Ecual_AdcScanAll();//周期扫描
    Srvl_E2WritePollingIfReady();//放10ms任务 保证DMA已 搬运完成
}

/***********************************************************************************************
 * @function name: AppApp20msTask
 * @description: 20ms周期任务处理函数，执行睡眠条件检查、电源管理和继电器延时上电
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp20msTask(void)
{
	Srvl_E2CheckWriteResultAndResp();
    OsekNmSleep_SleepDescFunction();
	//延时上电，避免上电继电器、灯有效
//	PWR_12V_ON();
}

/***********************************************************************************************
 * @function name: AppApp50msTask
 * @description: 50ms周期任务处理函数，执行EEPROM标志更新和睡眠管理任务
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
static void AppApp50msTask(void)
{
	Srvl_E2FlagUpdateTask();
//	SleepManageTask();
}
/***********************************************************************************************
 * @function name: AppAppCycEvent
 * @description: 周期性事件处理函数，根据弹出事件执行对应周期任务
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
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
