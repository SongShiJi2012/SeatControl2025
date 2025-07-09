/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
** Description:				
**
**************************************************************************************************/

#include "Srvl_PowerMode.h"
#include "Ecual_Adc.h"

static INT16U System_SupplyVoltage;              //KL30 ��ѹֵ ��λMV

/***********************************************************************************************
 * @function name:  Srvl_Get_SupplyVoltage
 * @description:    ��ȡ��ǰϵͳ�����ѹֵ����λ��������
 * @input parameters:     void
 * @output parameters:     void
 * @return:         INT16U ��ǰϵͳ�����ѹֵ��mV��
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
INT16U Srvl_Get_SupplyVoltage(void)
{
	return System_SupplyVoltage;
}
/***********************************************************************************************
 * @function name:  Srvl_Set_SupplyVoltage
 * @description:    ��ȡADCͨ����ѹֵ������ϵͳ�����ѹ����λΪ����(mV)
 * ��ѹ=200K/(200K+1M)=1/6��12λAD����׼��ѹ5V=5000mv��Vkl30=(6*((ADC_Value*5000)/4096))*1000
 * @input parameters:     void
 * @output parameters:     void
 * @return:         INT16U ��ǰ�����ϵͳ�����ѹֵ��mV��
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
void Srvl_Set_SupplyVoltage(void)
{
	INT16U ADC_Value = 0;
	/*��ȡ��Դ��ѹ���ADֵ*/
	ADC_Value = Ecual_AdcGetChlStatus(enADC_KL30Detect);
	/*����ADֵ����ѹ�����Դ��ѹ,��λmv*/
	System_SupplyVoltage = (INT16U)(6*((float)((ADC_Value *5000)>>12)));
}
