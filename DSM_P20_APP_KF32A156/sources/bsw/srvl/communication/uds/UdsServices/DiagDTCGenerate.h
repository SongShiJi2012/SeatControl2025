/************************************************************************************************
File created time : 2024-06-19 11:14:26
Tool Name : N822_UdsDTC_Generate.py
************************************************************************************************/

#ifndef D_N822BCM_DiagDTCGenerate_H
#define D_N822BCM_DiagDTCGenerate_H

#include "Common.h"
/*DTC ID 枚举类型*/
typedef enum _DIAG_DTC_NAME_T
{
	/* 0~4 */
	En_Dtc_CanBusOff, /* CAN总线BUS OFF */ 
	En_Dtc_SupplyVoltageTooLow, /* 供电电压过低 */ 
	En_Dtc_SupplyVoltageTooHigh, /* 供电电压过高 */ 
	En_Dtc_DsmNodeLimphome, /* 座椅节点进入Limphome状态 */ 
	En_Dtc_LostCommunicationWithBcm, /* DSM与BCM通讯丢失 */ 
	/* 5~9 */
	En_Dtc_LostCommunicationWithGw, /* DSM与GW通讯丢失 */ 
	En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, /* 主驾加热输出对地短路 */ 
	En_Dtc_DriverSeatHeatingOutputDisconnected, /* 主驾加热输出断路 */ 
	En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, /* 主驾加热NTC+对地短路 */ 
	En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, /* 主驾加热NTC+对电源短路或断路 */ 
	/* 10~14 */
	En_Dtc_DriverSeatHeatingNtcInputIsInvalid, /* 主驾加热NTC+输入无效 */ 
	En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, /* 副驾加热输出对地短路 */ 
	En_Dtc_PassengerSeatHeatingOutputDisconnected, /* 副驾加热输出断路 */ 
	En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, /* 副驾加热NTC+对地短路 */ 
	En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, /* 副驾加热NTC+对电源短路或断路 */ 
	/* 15~19 */
	En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, /* 副驾加热NTC+输入无效 */ 
	En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, /* 主驾通风驱动信号（PWM）对地短路 */ 
	En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, /* 主驾通风驱动信号（PWM）对电源短路或断路 */ 
	En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, /* 副驾通风驱动信号（PWM）对地短路 */ 
	En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, /* 副驾通风驱动信号（PWM）对电源短路或断路 */ 
	/* 20~24 */
	En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, /* 主驾纵向向前调节开关粘连 */ 
	En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, /* 主驾纵向向后调节开关粘连 */ 
	En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, /* 主驾靠背向前调节开关粘连 */ 
	En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, /* 主驾靠背向后调节开关粘连 */ 
	En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, /* 主驾高度向上调节开关粘连 */ 
	/* 25~29 */
	En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, /* 主驾高度向下调节开关粘连 */ 
	En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, /* 主驾坐垫前部角度向前调节开关粘连 */ 
	En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, /* 主驾坐垫前部角度向后调节开关粘连 */ 
	En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, /* 副驾纵向向前调节开关粘连 */ 
	En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, /* 副驾纵向向后调节开关粘连 */ 
	/* 30~34 */
	En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, /* 副驾靠背电机向前调节开关粘连 */ 
	En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, /* 副驾靠背电机向后调节开关粘连 */ 
	En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, /* 主驾高度调节继电器粘连 */ 
	En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, /* 主驾纵向调节继电器粘连 */ 
	En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, /* 主驾靠背调节继电器粘连 */ 
	/* 35~39 */
	En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, /* 主驾坐垫前部角度调节继电器粘连 */ 
	En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, /* 副驾座椅纵向调节继电器粘连 */ 
	En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, /* 副驾靠背调节继电器粘连 */ 
	En_Dtc_DriverSeatHeightRegulatingMotorHallFault, /* 主驾高度调节电机霍尔故障 */ 
	En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, /* 主驾纵向调节电机霍尔故障 */ 
	/* 40~44 */
	En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, /* 主驾靠背调节电机霍尔故障 */ 
	En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, /* 主驾坐垫前部角度调节电机霍尔故障 */ 
	En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, /* 副驾纵向调节电机霍尔故障 */ 
	En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, /* 副驾靠背调节电机霍尔故障 */ 
	En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, /* 方向盘加热输出对地短路 */ 
	/* 45~49 */
	En_Dtc_SteeringWheelHeatingOutputDisconnected, /* 方向盘加热输出断路 */ 
	En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, /* 方向盘加热NTC+对地短路 */ 
	En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, /* 方向盘加热NTC+对电源短路或断路 */ 
	En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, /* 方向盘加热NTC+输入无效 */ 
	En_Dtc_MassageModuleVoltageTooLow, /* 按摩模块欠压 */ 
	/* 50~54 */
	En_Dtc_MassageModuleVoltageTooHigh, /* 按摩模块过压 */ 
	En_Dtc_MassageMotorOvercurrent, /* 按摩电机过流 */ 
	En_Dtc_LINError, /* LIN数据出错 */ 
	En_DtcType_MaxNum, 
	/* The total DTC number is: 54 */

}DiagDtcNameType_t;



typedef struct DIAG_DTC_CONFIG_LIST_T
{
	DiagDtcNameType_t Diag_DtcName;                             /*!< DTC名称 */
	INT32U Diag_DtcCode;       /*!< DTC */
	INT16U Diag_SampleTime;                         /*!< 故障诊断采样时间，单位ms */
	INT16U Diag_FailValidCnt;                       /*!< DTC设置故障次数 */
	INT16U Diag_AgingTimes;                         /*!< DTC老化次数 */
	BOOL Diag_DtcEnable;                            /*!< DTC使能 */
}DiagDtcCfgList_t;


DiagDtcCfgList_t * Diag_GetDtcConfigListPtr(void); 

pt2Func * Diag_GetDtcHandleFuncPtr(void); 
INT16U Diag_GetGetDtcHandleFuncTblLength(void); 
void Diag_WriteDtcTestFailFlag(DiagDtcNameType_t enDtcIndex, BOOL bSta); 
BOOL Diag_ReadDtcTestFailFlag(DiagDtcNameType_t enDtcIndex); 



#endif 
