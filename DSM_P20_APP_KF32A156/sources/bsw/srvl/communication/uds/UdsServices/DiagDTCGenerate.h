/************************************************************************************************
File created time : 2024-06-19 11:14:26
Tool Name : N822_UdsDTC_Generate.py
************************************************************************************************/

#ifndef D_N822BCM_DiagDTCGenerate_H
#define D_N822BCM_DiagDTCGenerate_H

#include "Common.h"
/*DTC ID ö������*/
typedef enum _DIAG_DTC_NAME_T
{
	/* 0~4 */
	En_Dtc_CanBusOff, /* CAN����BUS OFF */ 
	En_Dtc_SupplyVoltageTooLow, /* �����ѹ���� */ 
	En_Dtc_SupplyVoltageTooHigh, /* �����ѹ���� */ 
	En_Dtc_DsmNodeLimphome, /* ���νڵ����Limphome״̬ */ 
	En_Dtc_LostCommunicationWithBcm, /* DSM��BCMͨѶ��ʧ */ 
	/* 5~9 */
	En_Dtc_LostCommunicationWithGw, /* DSM��GWͨѶ��ʧ */ 
	En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, /* ���ݼ�������Եض�· */ 
	En_Dtc_DriverSeatHeatingOutputDisconnected, /* ���ݼ��������· */ 
	En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, /* ���ݼ���NTC+�Եض�· */ 
	En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, /* ���ݼ���NTC+�Ե�Դ��·���· */ 
	/* 10~14 */
	En_Dtc_DriverSeatHeatingNtcInputIsInvalid, /* ���ݼ���NTC+������Ч */ 
	En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, /* ���ݼ�������Եض�· */ 
	En_Dtc_PassengerSeatHeatingOutputDisconnected, /* ���ݼ��������· */ 
	En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, /* ���ݼ���NTC+�Եض�· */ 
	En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, /* ���ݼ���NTC+�Ե�Դ��·���· */ 
	/* 15~19 */
	En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, /* ���ݼ���NTC+������Ч */ 
	En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, /* ����ͨ�������źţ�PWM���Եض�· */ 
	En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, /* ����ͨ�������źţ�PWM���Ե�Դ��·���· */ 
	En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, /* ����ͨ�������źţ�PWM���Եض�· */ 
	En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, /* ����ͨ�������źţ�PWM���Ե�Դ��·���· */ 
	/* 20~24 */
	En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, /* ����������ǰ���ڿ���ճ�� */ 
	En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, /* �������������ڿ���ճ�� */ 
	En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, /* ���ݿ�����ǰ���ڿ���ճ�� */ 
	En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, /* ���ݿ��������ڿ���ճ�� */ 
	En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, /* ���ݸ߶����ϵ��ڿ���ճ�� */ 
	/* 25~29 */
	En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, /* ���ݸ߶����µ��ڿ���ճ�� */ 
	En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, /* ��������ǰ���Ƕ���ǰ���ڿ���ճ�� */ 
	En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, /* ��������ǰ���Ƕ������ڿ���ճ�� */ 
	En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, /* ����������ǰ���ڿ���ճ�� */ 
	En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, /* �������������ڿ���ճ�� */ 
	/* 30~34 */
	En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, /* ���ݿ��������ǰ���ڿ���ճ�� */ 
	En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, /* ���ݿ�����������ڿ���ճ�� */ 
	En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, /* ���ݸ߶ȵ��ڼ̵���ճ�� */ 
	En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, /* ����������ڼ̵���ճ�� */ 
	En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, /* ���ݿ������ڼ̵���ճ�� */ 
	/* 35~39 */
	En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, /* ��������ǰ���Ƕȵ��ڼ̵���ճ�� */ 
	En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, /* ��������������ڼ̵���ճ�� */ 
	En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, /* ���ݿ������ڼ̵���ճ�� */ 
	En_Dtc_DriverSeatHeightRegulatingMotorHallFault, /* ���ݸ߶ȵ��ڵ���������� */ 
	En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, /* ����������ڵ���������� */ 
	/* 40~44 */
	En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, /* ���ݿ������ڵ���������� */ 
	En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, /* ��������ǰ���Ƕȵ��ڵ���������� */ 
	En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, /* ����������ڵ���������� */ 
	En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, /* ���ݿ������ڵ���������� */ 
	En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, /* �����̼�������Եض�· */ 
	/* 45~49 */
	En_Dtc_SteeringWheelHeatingOutputDisconnected, /* �����̼��������· */ 
	En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, /* �����̼���NTC+�Եض�· */ 
	En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, /* �����̼���NTC+�Ե�Դ��·���· */ 
	En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, /* �����̼���NTC+������Ч */ 
	En_Dtc_MassageModuleVoltageTooLow, /* ��Ħģ��Ƿѹ */ 
	/* 50~54 */
	En_Dtc_MassageModuleVoltageTooHigh, /* ��Ħģ���ѹ */ 
	En_Dtc_MassageMotorOvercurrent, /* ��Ħ������� */ 
	En_Dtc_LINError, /* LIN���ݳ��� */ 
	En_DtcType_MaxNum, 
	/* The total DTC number is: 54 */

}DiagDtcNameType_t;



typedef struct DIAG_DTC_CONFIG_LIST_T
{
	DiagDtcNameType_t Diag_DtcName;                             /*!< DTC���� */
	INT32U Diag_DtcCode;       /*!< DTC */
	INT16U Diag_SampleTime;                         /*!< ������ϲ���ʱ�䣬��λms */
	INT16U Diag_FailValidCnt;                       /*!< DTC���ù��ϴ��� */
	INT16U Diag_AgingTimes;                         /*!< DTC�ϻ����� */
	BOOL Diag_DtcEnable;                            /*!< DTCʹ�� */
}DiagDtcCfgList_t;


DiagDtcCfgList_t * Diag_GetDtcConfigListPtr(void); 

pt2Func * Diag_GetDtcHandleFuncPtr(void); 
INT16U Diag_GetGetDtcHandleFuncTblLength(void); 
void Diag_WriteDtcTestFailFlag(DiagDtcNameType_t enDtcIndex, BOOL bSta); 
BOOL Diag_ReadDtcTestFailFlag(DiagDtcNameType_t enDtcIndex); 



#endif 
