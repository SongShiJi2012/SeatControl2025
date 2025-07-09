/************************************************************************************************
File created time : 2024-06-19 11:14:26
Tool Name : N822_UdsDTC_Generate.py
************************************************************************************************/



#include "DiagDTCGenerate.h"
#include "Appl_DtcSetConditionCheck.h"



/************************************************************************************************
�ڲ�ȫ�ֱ�������
************************************************************************************************/

static BOOL bDiagDtcTestFailFlag[En_DtcType_MaxNum] = {0}; 


static DiagDtcCfgList_t Diag_DtcConfigList[] = 
{

	/* 0~4 */
	/* CAN����BUS OFF */
	{
		En_Dtc_CanBusOff, 
		0xC01988, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����ѹ���� */
	{
		En_Dtc_SupplyVoltageTooLow, 
		0xD10116, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����ѹ���� */
	{
		En_Dtc_SupplyVoltageTooHigh, 
		0xD10017, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���νڵ����Limphome״̬ */
	{
		En_Dtc_DsmNodeLimphome, 
		0xD00087, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* DSM��BCMͨѶ��ʧ */
	{
		En_Dtc_LostCommunicationWithBcm, 
		0xC14087, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 5~9 */
	/* DSM��GWͨѶ��ʧ */
	{
		En_Dtc_LostCommunicationWithGw, 
		0xC14787, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ�������Եض�· */
	{
		En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, 
		0xA10014, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ��������· */
	{
		En_Dtc_DriverSeatHeatingOutputDisconnected, 
		0xA10114, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ���NTC+�Եض�· */
	{
		En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, 
		0xA10214, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ���NTC+�Ե�Դ��·���· */
	{
		En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 
		0xA10315, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 10~14 */
	/* ���ݼ���NTC+������Ч */
	{
		En_Dtc_DriverSeatHeatingNtcInputIsInvalid, 
		0xA10429, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ�������Եض�· */
	{
		En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, 
		0xA10514, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ��������· */
	{
		En_Dtc_PassengerSeatHeatingOutputDisconnected, 
		0xA10614, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ���NTC+�Եض�· */
	{
		En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, 
		0xA10714, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݼ���NTC+�Ե�Դ��·���· */
	{
		En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, 
		0xA10815, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 15~19 */
	/* ���ݼ���NTC+������Ч */
	{
		En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, 
		0xA10929, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����ͨ�������źţ�PWM���Եض�· */
	{
		En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, 
		0xA10A14, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����ͨ�������źţ�PWM���Ե�Դ��·���· */
	{
		En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 
		0xA10B15, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����ͨ�������źţ�PWM���Եض�· */
	{
		En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, 
		0xA10C14, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����ͨ�������źţ�PWM���Ե�Դ��·���· */
	{
		En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, 
		0xA10D15, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 20~24 */
	/* ����������ǰ���ڿ���ճ�� */
	{
		En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
		0xA10E96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �������������ڿ���ճ�� */
	{
		En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 
		0xA10F96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ�����ǰ���ڿ���ճ�� */
	{
		En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, 
		0xA11096, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ��������ڿ���ճ�� */
	{
		En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, 
		0xA11196, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݸ߶����ϵ��ڿ���ճ�� */
	{
		En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, 
		0xA11296, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 25~29 */
	/* ���ݸ߶����µ��ڿ���ճ�� */
	{
		En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, 
		0xA11396, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��������ǰ���Ƕ���ǰ���ڿ���ճ�� */
	{
		En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, 
		0xA11496, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��������ǰ���Ƕ������ڿ���ճ�� */
	{
		En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, 
		0xA11596, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����������ǰ���ڿ���ճ�� */
	{
		En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, 
		0xA11696, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �������������ڿ���ճ�� */
	{
		En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, 
		0xA11796, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 30~34 */
	/* ���ݿ��������ǰ���ڿ���ճ�� */
	{
		En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, 
		0xA11896, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ�����������ڿ���ճ�� */
	{
		En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, 
		0xA11996, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݸ߶ȵ��ڼ̵���ճ�� */
	{
		En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, 
		0xA11A96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����������ڼ̵���ճ�� */
	{
		En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, 
		0xA11B96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ������ڼ̵���ճ�� */
	{
		En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, 
		0xA11C96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 35~39 */
	/* ��������ǰ���Ƕȵ��ڼ̵���ճ�� */
	{
		En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, 
		0xA11D96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��������������ڼ̵���ճ�� */
	{
		En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, 
		0xA11E96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ������ڼ̵���ճ�� */
	{
		En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, 
		0xA11F96, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݸ߶ȵ��ڵ���������� */
	{
		En_Dtc_DriverSeatHeightRegulatingMotorHallFault, 
		0xA12096, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����������ڵ���������� */
	{
		En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, 
		0xA12196, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 40~44 */
	/* ���ݿ������ڵ���������� */
	{
		En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, 
		0xA12296, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��������ǰ���Ƕȵ��ڵ���������� */
	{
		En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, 
		0xA12396, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ����������ڵ���������� */
	{
		En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, 
		0xA12496, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ���ݿ������ڵ���������� */
	{
		En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, 
		0xA12596, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����̼�������Եض�· */
	{
		En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, 
		0xA12611, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 45~49 */
	/* �����̼��������· */
	{
		En_Dtc_SteeringWheelHeatingOutputDisconnected, 
		0xA12713, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����̼���NTC+�Եض�· */
	{
		En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, 
		0xA12811, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����̼���NTC+�Ե�Դ��·���· */
	{
		En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, 
		0xA12913, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* �����̼���NTC+������Ч */
	{
		En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, 
		0xA12A29, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��Ħģ��Ƿѹ */
	{
		En_Dtc_MassageModuleVoltageTooLow, 
		0xA12B16, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 

	/* 50~54 */
	/* ��Ħģ���ѹ */
	{
		En_Dtc_MassageModuleVoltageTooHigh, 
		0xA12C17, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* ��Ħ������� */
	{
		En_Dtc_MassageMotorOvercurrent, 
		0xA12D19, 
		10U, 
		1U, 
		40U, 
		D_ENABLE, 
	}, 
	/* LIN���ݳ��� */
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
DTC�ṹ���ӿ�
*************************************************************************/
DiagDtcCfgList_t * Diag_GetDtcConfigListPtr(void)
{
	return &Diag_DtcConfigList[0]; 
}

/*************************************************************************
DTC����: CAN����BUS OFF 
DTC Code: 0xC01988 
DTC��������: Bus-off ��Ϊ���������� 3 �Σ������ڴ��ڼ�û�б��ı��ɹ����� 
*************************************************************************/
static void CanBusOff(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_CanBusOff ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_CanBusOff, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����ѹ���� 
DTC Code: 0xD10116 
DTC��������: �����ѹС��9V(��0.5V���ͻص�ѹ)����2s 
*************************************************************************/
static void SupplyVoltageTooLow(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SupplyVoltageTooLow ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SupplyVoltageTooLow, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����ѹ���� 
DTC Code: 0xD10017 
DTC��������: �����ѹ����16V(��0.5V���ͻص�ѹ)����2s 
*************************************************************************/
static void SupplyVoltageTooHigh(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SupplyVoltageTooHigh ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SupplyVoltageTooHigh, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���νڵ����Limphome״̬ 
DTC Code: 0xD00087 
DTC��������: ����������Limphome״̬ 
*************************************************************************/
static void DsmNodeLimphome(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DsmNodeLimphome ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DsmNodeLimphome, bTestFailFlag ); 

}

/*************************************************************************
DTC����: DSM��BCMͨѶ��ʧ 
DTC Code: 0xC14087 
DTC��������: û�н��յ�0x283���ĳ���10*���� 
*************************************************************************/
static void LostCommunicationWithBcm(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LostCommunicationWithBcm ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LostCommunicationWithBcm, bTestFailFlag ); 

}

/*************************************************************************
DTC����: DSM��GWͨѶ��ʧ 
DTC Code: 0xC14787 
DTC��������: û�н��յ�0x2A7���ĳ���10*���� 
*************************************************************************/
static void LostCommunicationWithGw(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LostCommunicationWithGw ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LostCommunicationWithGw, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ�������Եض�· 
DTC Code: 0xA10014 
DTC��������: �������μ���ʱ����⵽���ݼ�������Եض�·����40ms 
*************************************************************************/
static void DriverSeatHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ��������· 
DTC Code: 0xA10114 
DTC��������: �������μ���ʱ����⵽���ݼ��������·����һ���أ�����200ms 
*************************************************************************/
static void DriverSeatHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+�Եض�· 
DTC Code: 0xA10214 
DTC��������: ��⵽���ݼ���NTC+�Եض�·����1s 
*************************************************************************/
static void DriverSeatHeatingNtcGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+�Ե�Դ��·���· 
DTC Code: 0xA10315 
DTC��������: ��⵽���ݼ���NTC+�Ե�Դ��·���·����1s 
*************************************************************************/
static void DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+������Ч 
DTC Code: 0xA10429 
DTC��������: ���ݼ���NTC+���벻���ţ��¶ȴ���������NTC��ⷶΧ��ʱ�����1s 
*************************************************************************/
static void DriverSeatHeatingNtcInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeatingNtcInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeatingNtcInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ�������Եض�· 
DTC Code: 0xA10514 
DTC��������: �������μ���ʱ����⵽���ݼ�������Եض�·����40ms 
*************************************************************************/
static void PassengerSeatHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ��������· 
DTC Code: 0xA10614 
DTC��������: �������μ���ʱ����⵽���ݼ��������·����200ms 
*************************************************************************/
static void PassengerSeatHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+�Եض�· 
DTC Code: 0xA10714 
DTC��������: ��⵽���ݼ���NTC+�Եض�·����1s 
*************************************************************************/
static void PassengerSeatHeatingNtcGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+�Ե�Դ��·���· 
DTC Code: 0xA10815 
DTC��������: ��⵽���ݼ���NTC+�Ե�Դ��·���·����1s 
*************************************************************************/
static void PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݼ���NTC+������Ч 
DTC Code: 0xA10929 
DTC��������: ���ݼ���NTC+���벻���ţ��¶ȴ���������NTC��ⷶΧ��ʱ�����1s 
*************************************************************************/
static void PassengerSeatHeatingNtcInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatHeatingNtcInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatHeatingNtcInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����ͨ�������źţ�PWM���Եض�· 
DTC Code: 0xA10A14 
DTC��������: ��������ͨ��ʱ����⵽ͨ�������źţ�PWM���Եض�·����1s 
*************************************************************************/
static void DriverSeatVentilationDriveSignalPwmToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatVentilationDriveSignalPwmToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����ͨ�������źţ�PWM���Ե�Դ��·���· 
DTC Code: 0xA10B15 
DTC��������: ��������ͨ��ʱ����⵽ͨ�������źţ�PWM���Ե�Դ��·���·����1s 
*************************************************************************/
static void DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����ͨ�������źţ�PWM���Եض�· 
DTC Code: 0xA10C14 
DTC��������: ��������ͨ��ʱ����⵽ͨ�������źţ�PWM���Եض�·����1s 
*************************************************************************/
static void PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatVentilationDriveSignalPwmToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����ͨ�������źţ�PWM���Ե�Դ��·���· 
DTC Code: 0xA10D15 
DTC��������: ��������ͨ��ʱ����⵽ͨ�������źţ�PWM���Ե�Դ��·���·����1s 
*************************************************************************/
static void PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatVentilationDriveSignalPwmShortsOrBreaksThePowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����������ǰ���ڿ���ճ�� 
DTC Code: 0xA10E96 
DTC��������: ��������������ǰ���ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �������������ڿ���ճ�� 
DTC Code: 0xA10F96 
DTC��������: �����������������ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ�����ǰ���ڿ���ճ�� 
DTC Code: 0xA11096 
DTC��������: ���ݿ��������ǰ���ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatBackrestForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ��������ڿ���ճ�� 
DTC Code: 0xA11196 
DTC��������: ���ݿ�����������ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatBackrestBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݸ߶����ϵ��ڿ���ճ�� 
DTC Code: 0xA11296 
DTC��������: �������θ߶����ϵ��ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatHeightUpwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݸ߶����µ��ڿ���ճ�� 
DTC Code: 0xA11396 
DTC��������: �������θ߶����µ��ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatHeightDownwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��������ǰ���Ƕ���ǰ���ڿ���ճ�� 
DTC Code: 0xA11496 
DTC��������: ��������ǰ���Ƕ���ǰ���ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��������ǰ���Ƕ������ڿ���ճ�� 
DTC Code: 0xA11596 
DTC��������: ��������ǰ���Ƕ������ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����������ǰ���ڿ���ճ�� 
DTC Code: 0xA11696 
DTC��������: ��������������ǰ���ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �������������ڿ���ճ�� 
DTC Code: 0xA11796 
DTC��������: �����������������ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ��������ǰ���ڿ���ճ�� 
DTC Code: 0xA11896 
DTC��������: ���ݿ��������ǰ���ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void PassengerSeatBackrestForwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ�����������ڿ���ճ�� 
DTC Code: 0xA11996 
DTC��������: ���ݿ�����������ڿ��أ�Ӳ�߲ɼ��źţ�������Чʱ�䳬�� 2min 
*************************************************************************/
static void PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݸ߶ȵ��ڼ̵���ճ�� 
DTC Code: 0xA11A96 
DTC��������: �������θ߶�û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void DriverSeatHeightRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����������ڼ̵���ճ�� 
DTC Code: 0xA11B96 
DTC��������: ������������û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void DriverSeatLongitudinalControlRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalControlRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalControlRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ������ڼ̵���ճ�� 
DTC Code: 0xA11C96 
DTC��������: �������ο���û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void DriverSeatBackrestRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��������ǰ���Ƕȵ��ڼ̵���ճ�� 
DTC Code: 0xA11D96 
DTC��������: ��������ǰ���Ƕ�û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void DriverSeatFrontAngleAdjustmentRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��������������ڼ̵���ճ�� 
DTC Code: 0xA11E96 
DTC��������: ������������û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void PassengerSeatLongitudinalControlRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ������ڼ̵���ճ�� 
DTC Code: 0xA11F96 
DTC��������: �������ο���û�м̵������Ϸ���Ŀ������ȴ�е�ѹ�������2s 
*************************************************************************/
static void PassengerSeatBackrestRegulatingRelayIsGlued(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݸ߶ȵ��ڵ���������� 
DTC Code: 0xA12096 
DTC��������: �������θ߶ȵ��������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void DriverSeatHeightRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatHeightRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatHeightRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����������ڵ���������� 
DTC Code: 0xA12196 
DTC��������: ��������������������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void DriverSeatLongitudinalRegulationMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatLongitudinalRegulationMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ������ڵ���������� 
DTC Code: 0xA12296 
DTC��������: �������ο������������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void DriverSeatBackrestRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatBackrestRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatBackrestRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��������ǰ���Ƕȵ��ڵ���������� 
DTC Code: 0xA12396 
DTC��������: ��������ǰ���Ƕȵ��������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void DriverSeatFrontAngleAdjustmentMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_DriverSeatFrontAngleAdjustmentMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ����������ڵ���������� 
DTC Code: 0xA12496 
DTC��������: ��������������������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void PassengerSeatLongitudinalRegulationMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatLongitudinalRegulationMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ���ݿ������ڵ���������� 
DTC Code: 0xA12596 
DTC��������: �������ο������������2s��û�н��յ��������θ߶�λ�ô��������� 
*************************************************************************/
static void PassengerSeatBackrestRegulatingMotorHallFault(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_PassengerSeatBackrestRegulatingMotorHallFault, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����̼�������Եض�· 
DTC Code: 0xA12611 
DTC��������: �����̼���ʱ����⵽���ݼ�������Եض�·����40ms 
*************************************************************************/
static void SteeringWheelHeatingOutputToGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingOutputToGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����̼��������· 
DTC Code: 0xA12713 
DTC��������: �����̼���ʱ����⵽���ݼ��������·����һ���أ�����200ms 
*************************************************************************/
static void SteeringWheelHeatingOutputDisconnected(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingOutputDisconnected ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingOutputDisconnected, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����̼���NTC+�Եض�· 
DTC Code: 0xA12811 
DTC��������: ��⵽�����̼���NTC+�Եض�·����1s 
*************************************************************************/
static void SteeringWheelHeatingNTCGroundShortCircuit(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCGroundShortCircuit, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����̼���NTC+�Ե�Դ��·���· 
DTC Code: 0xA12913 
DTC��������: ��⵽�����̼���NTC+�Ե�Դ��·���·����1s 
*************************************************************************/
static void SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCToShortCircuitOrOpenPowerSupply, bTestFailFlag ); 

}

/*************************************************************************
DTC����: �����̼���NTC+������Ч 
DTC Code: 0xA12A29 
DTC��������: �����̼���NTC+���벻���ţ��¶ȴ���������NTC��ⷶΧ��ʱ�����5s 
*************************************************************************/
static void SteeringWheelHeatingNTCInputIsInvalid(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_SteeringWheelHeatingNTCInputIsInvalid ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_SteeringWheelHeatingNTCInputIsInvalid, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��Ħģ��Ƿѹ 
DTC Code: 0xA12B16 
DTC��������: ��Ħģ��ͨ��LIN�ߣ�0x1B Massage_Error_FB��������DSM����״̬Ϊ����Ħģ��Ƿѹ 
*************************************************************************/
static void MassageModuleVoltageTooLow(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageModuleVoltageTooLow ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageModuleVoltageTooLow, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��Ħģ���ѹ 
DTC Code: 0xA12C17 
DTC��������: ��Ħģ��ͨ��LIN��(0x1B��Massage_Error_FB��������DSM����״̬Ϊ����Ħģ���ѹ 
*************************************************************************/
static void MassageModuleVoltageTooHigh(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageModuleVoltageTooHigh ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageModuleVoltageTooHigh, bTestFailFlag ); 

}

/*************************************************************************
DTC����: ��Ħ������� 
DTC Code: 0xA12D19 
DTC��������: ��Ħģ��ͨ��LIN�ߣ�0x1B��Motor_TimeOutError_FB��������DSM����״̬Ϊ����Ħ������� 
*************************************************************************/
static void MassageMotorOvercurrent(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_MassageMotorOvercurrent ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_MassageMotorOvercurrent, bTestFailFlag ); 

}

/*************************************************************************
DTC����: LIN���ݳ��� 
DTC Code: 0xA12E83 
DTC��������: DSM�������ݳ�ʱ���͵�LIN����checksum������յ���LIN����checksum��LINЭ�飺ZNA_EEA_PU_LIN_Communication_Specification_R1.1_20170512������ 
*************************************************************************/
static void LINError(void) 
{
	BOOL bTestFailFlag = FALSE;

	bTestFailFlag = Diag_ReadDtcTestFailFlag( En_Dtc_LINError ); 
	(void)Diag_DtcMaskSetClrOpt( En_Dtc_LINError, bTestFailFlag ); 

}

/*************************************************************************
��������
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

