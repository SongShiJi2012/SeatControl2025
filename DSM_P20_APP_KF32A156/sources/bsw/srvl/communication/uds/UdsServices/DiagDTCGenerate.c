/************************************************************************************************
File created time : 2024-06-19 11:14:26
Tool Name : N822_UdsDTC_Generate.py
************************************************************************************************/



#include "DiagDTCGenerate.h"
#include "Appl_DtcSetConditionCheck.h"



/************************************************************************************************
内部全局变量声明
************************************************************************************************/

static BOOL bDiagDtcTestFailFlag[En_DtcType_MaxNum] = {0}; 


static DiagDtcCfgList_t Diag_DtcConfigList[] = 
{

	/* 0~4 */
	/* CAN总线BUS OFF */
	{
		En_Dtc_CanBusOff, 
		0xC01988, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 供电电压过低 */
	{
		En_Dtc_SupplyVoltageTooLow, 
		0xD10116, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 供电电压过高 */
	{
		En_Dtc_SupplyVoltageTooHigh, 
		0xD10017, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 座椅节点进入Limphome状态 */
	{
		En_Dtc_DsmNodeLimphome, 
		0xD00087, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* DSM与BCM通讯丢失 */
	{
		En_Dtc_LostCommunicationWithBcm, 
		0xC14087, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 5~9 */
	/* DSM与GW通讯丢失 */
	{
		En_Dtc_LostCommunicationWithGw, 
		0xC14787, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾加热输出对地短路 */
	{
		En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, 
		0xA10014, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾加热输出断路 */
	{
		En_Dtc_DriverSeatHeatingOutputDisconnected, 
		0xA10114, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾加热NTC+对地短路 */
	{
		En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, 
		0xA10214, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾加热NTC+对电源短路或断路 */
	{
		En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 
		0xA10315, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 10~14 */
	/* 主驾加热NTC+输入无效 */
	{
		En_Dtc_DriverSeatHeatingNtcInputIsInvalid, 
		0xA10429, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾加热输出对地短路 */
	{
		En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, 
		0xA10514, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾加热输出断路 */
	{
		En_Dtc_PassengerSeatHeatingOutputDisconnected, 
		0xA10614, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾加热NTC+对地短路 */
	{
		En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, 
		0xA10714, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾加热NTC+对电源短路或断路 */
	{
		En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 
		0xA10815, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 15~19 */
	/* 副驾加热NTC+输入无效 */
	{
		En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, 
		0xA10929, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾通风驱动信号（PWM）对地短路 */
	{
		En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, 
		0xA10A14, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾通风驱动信号（PWM）对电源短路或断路 */
	{
		En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 
		0xA10B15, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾通风驱动信号（PWM）对地短路 */
	{
		En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, 
		0xA10C14, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾通风驱动信号（PWM）对电源短路或断路 */
	{
		En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 
		0xA10D15, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 20~24 */
	/* 主驾纵向向前调节开关粘连 */
	{
		En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
		0xA10E96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾纵向向后调节开关粘连 */
	{
		En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 
		0xA10F96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾靠背向前调节开关粘连 */
	{
		En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, 
		0xA11096, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾靠背向后调节开关粘连 */
	{
		En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, 
		0xA11196, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾高度向上调节开关粘连 */
	{
		En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, 
		0xA11296, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 25~29 */
	/* 主驾高度向下调节开关粘连 */
	{
		En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, 
		0xA11396, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾坐垫前部角度向前调节开关粘连 */
	{
		En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, 
		0xA11496, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾坐垫前部角度向后调节开关粘连 */
	{
		En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, 
		0xA11596, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾纵向向前调节开关粘连 */
	{
		En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
		0xA11696, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾纵向向后调节开关粘连 */
	{
		En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 
		0xA11796, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 30~34 */
	/* 副驾靠背电机向前调节开关粘连 */
	{
		En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, 
		0xA11896, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾靠背电机向后调节开关粘连 */
	{
		En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, 
		0xA11996, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾高度调节继电器粘连 */
	{
		En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, 
		0xA11A96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾纵向调节继电器粘连 */
	{
		En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, 
		0xA11B96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾靠背调节继电器粘连 */
	{
		En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, 
		0xA11C96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 35~39 */
	/* 主驾坐垫前部角度调节继电器粘连 */
	{
		En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, 
		0xA11D96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾座椅纵向调节继电器粘连 */
	{
		En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, 
		0xA11E96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾靠背调节继电器粘连 */
	{
		En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, 
		0xA11F96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾高度调节电机霍尔故障 */
	{
		En_Dtc_DriverSeatHeightRegulatingMotorHallFault, 
		0xA12096, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾纵向调节电机霍尔故障 */
	{
		En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, 
		0xA12196, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 40~44 */
	/* 主驾靠背调节电机霍尔故障 */
	{
		En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, 
		0xA12296, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 主驾坐垫前部角度调节电机霍尔故障 */
	{
		En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, 
		0xA12396, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾纵向调节电机霍尔故障 */
	{
		En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, 
		0xA12496, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 副驾靠背调节电机霍尔故障 */
	{
		En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, 
		0xA12596, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 方向盘加热输出对地短路 */
	{
		En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, 
		0xA12611, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 45~49 */
	/* 方向盘加热输出断路 */
	{
		En_Dtc_SteeringWheelHeatingOutputDisconnected, 
		0xA12713, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 方向盘加热NTC+对地短路 */
	{
		En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, 
		0xA12811, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 方向盘加热NTC+对电源短路或断路 */
	{
		En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, 
		0xA12913, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 方向盘加热NTC+输入无效 */
	{
		En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, 
		0xA12A29, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 按摩模块欠压 */
	{
		En_Dtc_MassageModuleVoltageTooLow, 
		0xA12B16, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 50~54 */
	/* 按摩模块过压 */
	{
		En_Dtc_MassageModuleVoltageTooHigh, 
		0xA12C17, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* 按摩电机过流 */
	{
		En_Dtc_MassageMotorOvercurrent, 
		0xA12D19, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* LIN数据出错 */
	{
		En_Dtc_LINError, 
		0xA12E83, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
};



/*************************************************************************
DTC结构体表接口
*************************************************************************/
DiagDtcCfgList_t * Diag_GetDtcConfigListPtr(void)
{
	return &Diag_DtcConfigList[0]; 
}

/*************************************************************************
DTC含义: CAN总线BUS OFF 
DTC Code: 0xC01988 
DTC设置条件: Bus-off 行为连续发生了 3 次，并且在此期间没有报文被成功发送 
*************************************************************************/
static void CanBusOff(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_CanBusOff ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_CanBusOff, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 供电电压过低 
DTC Code: 0xD10116 
DTC设置条件: 供电电压小于9V(有0.5V的滞回电压)持续2s 
*************************************************************************/
static void SupplyVoltageTooLow(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SupplyVoltageTooLow ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SupplyVoltageTooLow, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 供电电压过高 
DTC Code: 0xD10017 
DTC设置条件: 供电电压大于16V(有0.5V的滞回电压)持续2s 
*************************************************************************/
static void SupplyVoltageTooHigh(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SupplyVoltageTooHigh ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SupplyVoltageTooHigh, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 座椅节点进入Limphome状态 
DTC Code: 0xD00087 
DTC设置条件: 网络管理进入Limphome状态 
*************************************************************************/
static void DsmNodeLimphome(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DsmNodeLimphome ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DsmNodeLimphome, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: DSM与BCM通讯丢失 
DTC Code: 0xC14087 
DTC设置条件: 没有接收到0x283报文超过10*周期 
*************************************************************************/
static void LostCommunicationWithBcm(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LostCommunicationWithBcm ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LostCommunicationWithBcm, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: DSM与GW通讯丢失 
DTC Code: 0xC14787 
DTC设置条件: 没有接收到0x2A7报文超过10*周期 
*************************************************************************/
static void LostCommunicationWithGw(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LostCommunicationWithGw ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LostCommunicationWithGw, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾加热输出对地短路 
DTC Code: 0xA10014 
DTC设置条件: 主驾座椅加热时，检测到主驾加热输出对地短路大于40ms 
*************************************************************************/
static void DriverSeatHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾加热输出断路 
DTC Code: 0xA10114 
DTC设置条件: 主驾座椅加热时，检测到主驾加热输出断路（任一负载）大于200ms 
*************************************************************************/
static void DriverSeatHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾加热NTC+对地短路 
DTC Code: 0xA10214 
DTC设置条件: 检测到主驾加热NTC+对地短路大于1s 
*************************************************************************/
static void DriverSeatHeatingNtcGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾加热NTC+对电源短路或断路 
DTC Code: 0xA10315 
DTC设置条件: 检测到主驾加热NTC+对电源短路或断路大于1s 
*************************************************************************/
static void DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾加热NTC+输入无效 
DTC Code: 0xA10429 
DTC设置条件: 主驾加热NTC+输入不可信（温度传感器超出NTC检测范围）时间大于1s 
*************************************************************************/
static void DriverSeatHeatingNtcInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾加热输出对地短路 
DTC Code: 0xA10514 
DTC设置条件: 副驾座椅加热时，检测到副驾加热输出对地短路大于40ms 
*************************************************************************/
static void PassengerSeatHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾加热输出断路 
DTC Code: 0xA10614 
DTC设置条件: 副驾座椅加热时，检测到副驾加热输出断路大于200ms 
*************************************************************************/
static void PassengerSeatHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾加热NTC+对地短路 
DTC Code: 0xA10714 
DTC设置条件: 检测到副驾加热NTC+对地短路大于1s 
*************************************************************************/
static void PassengerSeatHeatingNtcGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾加热NTC+对电源短路或断路 
DTC Code: 0xA10815 
DTC设置条件: 检测到副驾加热NTC+对电源短路或断路大于1s 
*************************************************************************/
static void PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾加热NTC+输入无效 
DTC Code: 0xA10929 
DTC设置条件: 副驾加热NTC+输入不可信（温度传感器超出NTC检测范围）时间大于1s 
*************************************************************************/
static void PassengerSeatHeatingNtcInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾通风驱动信号（PWM）对地短路 
DTC Code: 0xA10A14 
DTC设置条件: 主驾座椅通风时，检测到通风驱动信号（PWM）对地短路大于1s 
*************************************************************************/
static void DriverSeatVentilationDriveSignalPwmToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾通风驱动信号（PWM）对电源短路或断路 
DTC Code: 0xA10B15 
DTC设置条件: 主驾座椅通风时，检测到通风驱动信号（PWM）对电源短路或断路大于1s 
*************************************************************************/
static void DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾通风驱动信号（PWM）对地短路 
DTC Code: 0xA10C14 
DTC设置条件: 副驾座椅通风时，检测到通风驱动信号（PWM）对地短路大于1s 
*************************************************************************/
static void PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾通风驱动信号（PWM）对电源短路或断路 
DTC Code: 0xA10D15 
DTC设置条件: 副驾座椅通风时，检测到通风驱动信号（PWM）对电源短路或断路大于1s 
*************************************************************************/
static void PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾纵向向前调节开关粘连 
DTC Code: 0xA10E96 
DTC设置条件: 主驾座椅纵向向前调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾纵向向后调节开关粘连 
DTC Code: 0xA10F96 
DTC设置条件: 主驾座椅纵向向后调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾靠背向前调节开关粘连 
DTC Code: 0xA11096 
DTC设置条件: 主驾靠背电机向前调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatBackrestForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾靠背向后调节开关粘连 
DTC Code: 0xA11196 
DTC设置条件: 主驾靠背电机向后调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatBackrestBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾高度向上调节开关粘连 
DTC Code: 0xA11296 
DTC设置条件: 主驾座椅高度向上调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatHeightUpwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾高度向下调节开关粘连 
DTC Code: 0xA11396 
DTC设置条件: 主驾座椅高度向下调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatHeightDownwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾坐垫前部角度向前调节开关粘连 
DTC Code: 0xA11496 
DTC设置条件: 主驾坐垫前部角度向前调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾坐垫前部角度向后调节开关粘连 
DTC Code: 0xA11596 
DTC设置条件: 主驾坐垫前部角度向后调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾纵向向前调节开关粘连 
DTC Code: 0xA11696 
DTC设置条件: 副驾座椅纵向向前调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾纵向向后调节开关粘连 
DTC Code: 0xA11796 
DTC设置条件: 副驾座椅纵向向后调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾靠背电机向前调节开关粘连 
DTC Code: 0xA11896 
DTC设置条件: 副驾靠背电机向前调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void PassengerSeatBackrestForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾靠背电机向后调节开关粘连 
DTC Code: 0xA11996 
DTC设置条件: 副驾靠背电机向后调节开关（硬线采集信号）持续有效时间超过 2min 
*************************************************************************/
static void PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾高度调节继电器粘连 
DTC Code: 0xA11A96 
DTC设置条件: 主驾座椅高度没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void DriverSeatHeightRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾纵向调节继电器粘连 
DTC Code: 0xA11B96 
DTC设置条件: 主驾座椅纵向没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void DriverSeatLongitudinalControlRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalControlRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾靠背调节继电器粘连 
DTC Code: 0xA11C96 
DTC设置条件: 主驾座椅靠背没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void DriverSeatBackrestRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾坐垫前部角度调节继电器粘连 
DTC Code: 0xA11D96 
DTC设置条件: 主驾座椅前部角度没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void DriverSeatFrontAngleAdjustmentRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾座椅纵向调节继电器粘连 
DTC Code: 0xA11E96 
DTC设置条件: 副驾座椅纵向没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void PassengerSeatLongitudinalControlRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾靠背调节继电器粘连 
DTC Code: 0xA11F96 
DTC设置条件: 副驾座椅靠背没有继电器吸合方向的开启命令，却有电压输出持续2s 
*************************************************************************/
static void PassengerSeatBackrestRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾高度调节电机霍尔故障 
DTC Code: 0xA12096 
DTC设置条件: 主驾座椅高度电机启动后，2s内没有接收到主驾座椅高度位置传感器脉冲 
*************************************************************************/
static void DriverSeatHeightRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾纵向调节电机霍尔故障 
DTC Code: 0xA12196 
DTC设置条件: 主驾座椅纵向电机启动后，2s内没有接收到主驾座椅高度位置传感器脉冲 
*************************************************************************/
static void DriverSeatLongitudinalRegulationMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾靠背调节电机霍尔故障 
DTC Code: 0xA12296 
DTC设置条件: 主驾座椅靠背电机启动后，2s内没有接收到主驾座椅高度位置传感器脉冲 
*************************************************************************/
static void DriverSeatBackrestRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 主驾坐垫前部角度调节电机霍尔故障 
DTC Code: 0xA12396 
DTC设置条件: 主驾座椅前部角度电机启动后，2s内没有接收到主驾座椅高度位置传感器脉冲 
*************************************************************************/
static void DriverSeatFrontAngleAdjustmentMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾纵向调节电机霍尔故障 
DTC Code: 0xA12496 
DTC设置条件: 副驾座椅纵向电机启动后，2s内没有接收到副驾座椅高度位置传感器脉冲 
*************************************************************************/
static void PassengerSeatLongitudinalRegulationMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 副驾靠背调节电机霍尔故障 
DTC Code: 0xA12596 
DTC设置条件: 副驾座椅靠背电机启动后，2s内没有接收到副驾座椅高度位置传感器脉冲 
*************************************************************************/
static void PassengerSeatBackrestRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 方向盘加热输出对地短路 
DTC Code: 0xA12611 
DTC设置条件: 方向盘加热时，检测到主驾加热输出对地短路大于40ms 
*************************************************************************/
static void SteeringWheelHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 方向盘加热输出断路 
DTC Code: 0xA12713 
DTC设置条件: 方向盘加热时，检测到主驾加热输出断路（任一负载）大于200ms 
*************************************************************************/
static void SteeringWheelHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 方向盘加热NTC+对地短路 
DTC Code: 0xA12811 
DTC设置条件: 检测到方向盘加热NTC+对地短路大于1s 
*************************************************************************/
static void SteeringWheelHeatingNTCGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 方向盘加热NTC+对电源短路或断路 
DTC Code: 0xA12913 
DTC设置条件: 检测到方向盘加热NTC+对电源短路或断路大于1s 
*************************************************************************/
static void SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 方向盘加热NTC+输入无效 
DTC Code: 0xA12A29 
DTC设置条件: 方向盘加热NTC+输入不可信（温度传感器超出NTC检测范围）时间大于5s 
*************************************************************************/
static void SteeringWheelHeatingNTCInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 按摩模块欠压 
DTC Code: 0xA12B16 
DTC设置条件: 按摩模块通过LIN线（0x1B Massage_Error_FB）反馈至DSM故障状态为：按摩模块欠压 
*************************************************************************/
static void MassageModuleVoltageTooLow(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageModuleVoltageTooLow ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageModuleVoltageTooLow, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 按摩模块过压 
DTC Code: 0xA12C17 
DTC设置条件: 按摩模块通过LIN线(0x1B：Massage_Error_FB）反馈至DSM故障状态为：按摩模块过压 
*************************************************************************/
static void MassageModuleVoltageTooHigh(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageModuleVoltageTooHigh ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageModuleVoltageTooHigh, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: 按摩电机过流 
DTC Code: 0xA12D19 
DTC设置条件: 按摩模块通过LIN线（0x1B：Motor_TimeOutError_FB）反馈至DSM故障状态为：按摩电机过流 
*************************************************************************/
static void MassageMotorOvercurrent(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageMotorOvercurrent ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageMotorOvercurrent, bTestFailFlag ); 

}

/*************************************************************************
DTC含义: LIN数据出错 
DTC Code: 0xA12E83 
DTC设置条件: DSM接收数据超时或发送的LIN数据checksum错误或收到的LIN数据checksum（LIN协议：ZNA_EEA_PU_LIN_Communication_Specification_R1.1_20170512）错误 
*************************************************************************/
static void LINError(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LINError ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LINError, bTestFailFlag ); 

}

/*************************************************************************
处理函数表
*************************************************************************/
static  pt2Func Diag_DtcHandleFunc[] = 
{

	/* 0~4 */
	&CanBusOff, 
	&SupplyVoltageTooLow, 
	&SupplyVoltageTooHigh, 
	&DsmNodeLimphome, 
	&LostCommunicationWithBcm, 

	/* 5~9 */
	&LostCommunicationWithGw, 
	&DriverSeatHeatingOutputToGroundShortCircuit, 
	&DriverSeatHeatingOutputDisconnected, 
	&DriverSeatHeatingNtcGroundShortCircuit, 
	&DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 

	/* 10~14 */
	&DriverSeatHeatingNtcInputIsInvalid, 
	&PassengerSeatHeatingOutputToGroundShortCircuit, 
	&PassengerSeatHeatingOutputDisconnected, 
	&PassengerSeatHeatingNtcGroundShortCircuit, 
	&PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 

	/* 15~19 */
	&PassengerSeatHeatingNtcInputIsInvalid, 
	&DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, 
	&DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 
	&PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, 
	&PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 

	/* 20~24 */
	&DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
	&DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 
	&DriverSeatBackrestForwardAdjustmentSwitchAdhesion, 
	&DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, 
	&DriverSeatHeightUpwardAdjustmentSwitchAdhesion, 

	/* 25~29 */
	&DriverSeatHeightDownwardAdjustmentSwitchAdhesion, 
	&DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, 
	&DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, 
	&PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
	&PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 

	/* 30~34 */
	&PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, 
	&PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, 
	&DriverSeatHeightRegulatingRelayIsGlued, 
	&DriverSeatLongitudinalControlRelayIsGlued, 
	&DriverSeatBackrestRegulatingRelayIsGlued, 

	/* 35~39 */
	&DriverSeatFrontAngleAdjustmentRelayIsGlued, 
	&PassengerSeatLongitudinalControlRelayIsGlued, 
	&PassengerSeatBackrestRegulatingRelayIsGlued, 
	&DriverSeatHeightRegulatingMotorHallFault, 
	&DriverSeatLongitudinalRegulationMotorHallFault, 

	/* 40~44 */
	&DriverSeatBackrestRegulatingMotorHallFault, 
	&DriverSeatFrontAngleAdjustmentMotorHallFault, 
	&PassengerSeatLongitudinalRegulationMotorHallFault, 
	&PassengerSeatBackrestRegulatingMotorHallFault, 
	&SteeringWheelHeatingOutputToGroundShortCircuit, 

	/* 45~49 */
	&SteeringWheelHeatingOutputDisconnected, 
	&SteeringWheelHeatingNTCGroundShortCircuit, 
	&SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, 
	&SteeringWheelHeatingNTCInputIsInvalid, 
	&MassageModuleVoltageTooLow, 

	/* 50~54 */
	&MassageModuleVoltageTooHigh, 
	&MassageMotorOvercurrent, 
	&LINError, 
};

#define D_DtcHandleFunc_Len	 (sizeof(Diag_DtcHandleFunc)/sizeof(Diag_DtcHandleFunc[0]))

pt2Func * Diag_GetDtcHandleFuncPtr(void)
{
	return &Diag_DtcHandleFunc[0];
}

INT16U Diag_GetGetDtcHandleFuncTblLength(void)
{
	return (sizeof(Diag_DtcHandleFunc)/sizeof(Diag_DtcHandleFunc[0]));
}

void Diag_WriteDtcTestFailFlag(DiagDtcNameType_t enDtcIndex, BOOL bSta)
{
	bDiagDtcTestFailFlag[enDtcIndex] = bSta; 
}

BOOL Diag_ReadDtcTestFailFlag(DiagDtcNameType_t enDtcInde)
{
	return bDiagDtcTestFailFlag[enDtcInde]; 
}

