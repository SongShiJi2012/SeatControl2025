/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
** Description:				
**
**************************************************************************************************/

#include "Srvl_PowerMode.h"
#include "Ecual_Adc.h"

static INT16U System_SupplyVoltage;              //KL30 电压值 单位MV

/***********************************************************************************************
 * @function name:  Srvl_Get_SupplyVoltage
 * @description:    获取当前系统供电电压值（单位：毫伏）
 * @input parameters:     void
 * @output parameters:     void
 * @return:         INT16U 当前系统供电电压值（mV）
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
INT16U Srvl_Get_SupplyVoltage(void)
{
	return System_SupplyVoltage;
}
/***********************************************************************************************
 * @function name:  Srvl_Set_SupplyVoltage
 * @description:    读取ADC通道电压值并计算系统供电电压，单位为毫伏(mV)
 * 分压=200K/(200K+1M)=1/6，12位AD，基准电压5V=5000mv，Vkl30=(6*((ADC_Value*5000)/4096))*1000
 * @input parameters:     void
 * @output parameters:     void
 * @return:         INT16U 当前计算的系统供电电压值（mV）
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Srvl_Set_SupplyVoltage(void)
{
	INT16U ADC_Value = 0;
	/*获取电源电压检测AD值*/
	ADC_Value = Ecual_AdcGetChlStatus(enADC_KL30Detect);
	/*根据AD值及分压换算电源电压,单位mv*/
	System_SupplyVoltage = (INT16U)(6*((float)((ADC_Value *5000)>>12)));
}
