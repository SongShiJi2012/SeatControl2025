/***********************************************************************************************
 * @file:            ecual_pins.c
 * @description:     ʵ��������ŵ� GPIO ���ƽӿڣ�������ƽ���ú����ȡ�
 *                   ͨ�� OutputId_t ö��������Ӧ���ţ�����Ӳ�����״̬��
 * @author:          ssj 2025-05-28
 * @version:         V1.0
 ***********************************************************************************************/

#include "ecual_pins.h"

extern const pin_settings_config_t g_pin_mux_InitConfigArr[SELECT_PLATFORM_PINS];
extern const pin_settings_config_t g_pin_mux_OffModeConfigArr[SELECT_PLATFORM_PINS];
/*! @brief �˿ڼ����Ч���б� ,��Ҫ�����ź�ö��ֵ����,����Hal_GetIoVaild��ȡ��״̬���λ*/
static IoCheckCfg_t Io_CheckVaildTbl[EN_GPIO_IN_ALL_NUM] =
{
//	{EN_MemorySetButton,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  EN_MCU_PIN26_MEMORY_SET_IN}, /*��������Ԥ��*/
	{EN_DRVenFeedback,    		EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin6}, /*����ͨ��*/
	{EN_PaVenFeedback,     		EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin7}, /*����ͨ��*/

	{EN_DRHeightBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin49}, /*���ݸ߶ȿ��ؼ��-���*/
	{EN_DRHeightForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin51}, /*���ݸ߶ȿ��ؼ��-��ǰ*/
	{EN_DRLengthBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin52}, /*�������򿪹ؼ��-���*/
	{EN_DRLengthForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin67}, /*�������򿪹ؼ��-��ǰ*/
	{EN_DRBackBackwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin79}, /*���ݿ������ؼ��-���*/
	{EN_DRBackForwardSW,        EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin80}, /*���ݿ������ؼ��-��ǰ*/
	{EN_DRFrontBackwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin81}, /*����ǰ���Ƕȿ��ؼ��-���*/
	{EN_DRFrontForwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin42}, /*����ǰ���Ƕȿ��ؼ��-��ǰ*/
	{EN_PALengthBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin77}, /*�������򿪹ؼ��-���*/
	{EN_PALengthForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin78}, /*�������򿪹ؼ��-��ǰ*/
	{EN_PABackBackwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin48}, /*���ݿ������ؼ��-���*/
	{EN_PABackForwardSW,        EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin50}, /*���ݿ������ؼ��-��ǰ*/

	{EN_KL15Level,              EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin88}, /* KL15 ���ŵ�ƽ */
};

static OutputPinCfg_t Io_OutPutTbl[EN_OutputNum] =
{
	{ EN_PreDrv1Pwm4Out,      enPin4  },   // Ԥ��1 PWM4���-��EN����
	{ EN_PreDrv2SpiSs2Out,    enPin20 },   // Ԥ��2 SPI SS2ʹ��
	{ EN_Discrete12VOut,      enPin23 },   // ����12Vʹ�ܿ���
	{ EN_LinEnOut,            enPin26 },   // LINʹ��
	{ EN_CanErrOut,           enPin32 },   // CAN����ָʾ���
	{ EN_CanEnOut,            enPin34 },   // CANʹ��
	{ EN_Reserve0Out,         enPin35 },   // Ԥ��
	{ EN_Reserve1Out,         enPin36 },   // Ԥ��
	{ EN_PreDrv2Pwm4Out,      enPin40 },   // Ԥ��2 PWM4���-��EN����
	{ EN_Reserve2Out,         enPin41 },   // Ԥ��
	{ EN_Reserve3Out,         enPin59 },   // Ԥ��
	{ EN_DrHeatOut,           enPin62 },   // ���ݼ��ȿ���
	{ EN_PaHeatOut,           enPin63 },   // ���ݼ��ȿ���
	{ EN_Heat3Out,            enPin69 },   // ����3����
	{ EN_Heat3_4CurrSelOut,   enPin71 },   // ����3&4��������л�
	{ EN_Heat4Out,            enPin72 },   // ����4����
	{ EN_WheelHeatCtrlOut,    enPin74 },   // �����̼��ȿ���
	{ EN_HallPwrOut,          enPin99 },   // ����������ƣ�Ԥ����
	{ EN_CanStbOut,           enPin100 },   // CAN STB����
	{ EN_WdogOut,             enPin33 }   // ι��
    

};
/*************************************************************************************************
 * @function name:      ecual_pins_init
 *
 * @description:        �弯����pin�ų�ʼ��
 *
 * @parameters:         none
 *
 * @return:             0 is successful
 *************************************************************************************************/
status_t ecual_pins_init( ePinsConfigMode Mode )
{
    status_t rt = STATUS_ERROR;

    if( Mode < PINS_MODE_MAX )
    {   
        switch ( Mode )
        {
        case PINS_MODE_INIT:
            {
                rt = PINS_DRV_Init( SELECT_PLATFORM_PINS, g_pin_mux_InitConfigArr );
            }
            break;
        case PINS_MODE_OFFMODE:
            {
                rt = PINS_DRV_Init( SELECT_PLATFORM_PINS, g_pin_mux_OffModeConfigArr );
            }
            break;

        default:
            break;
        }
    }

    return rt;
}
/***********************************************************************************************
 * @function name:  Control_OutputPin
 * @description:    �������ñ�������Ϊ����� IO ���ŵ�ƽ
 * @input parameters:     pin_id: ��������ö�ٱ�� enPinXX ��level: ��ƽֵ��0/1��
 * @output parameters:    ��
 * @return:         BOOL ���ͣ�TRUE �ɹ���FALSE ������ڻ�Ƿ����
 * @author:         ssj 2025-05-28
 ***********************************************************************************************/
BOOL Ecual_GpioWriteOutPutPin(pin_config_id_t pinIndex, GpioLevel_t level)
{
    if(pinIndex >= PINS_NUM_MAX)
    {
        return FALSE;
    }

    const pin_settings_config_t *pConfig = &g_pin_mux_InitConfigArr[pinIndex];

    if(pConfig->m_Mode == GPIO_MODE_OUT)
    {
        PINS_DRV_WritePin(pConfig->base, pConfig->m_PinNum, level);
        return TRUE;
    }

    return FALSE;
}

/***********************************************************************************************
 * @function name:  Control_OutputPin
 * @description:    �������ñ�������Ϊ����� IO ���ŵ�ƽ
 * @input parameters:     pin_id: ��������ö�ٱ�� enPinXX ��level: ��ƽֵ��0/1��
 * @output parameters:    ��
 * @return:         BOOL ���ͣ�TRUE �ɹ���FALSE ������ڻ�Ƿ����
 * @author:         ssj 2025-05-28
 ***********************************************************************************************/
BOOL Ecual_GpioToggleOutPutPin(pin_config_id_t pinIndex)
{
    if(pinIndex >= PINS_NUM_MAX)
    {
        return FALSE;
    }

    const pin_settings_config_t *pConfig = &g_pin_mux_InitConfigArr[pinIndex];

    if(pConfig->m_Mode == GPIO_MODE_OUT)
    {
        PINS_DRV_TogglePin(pConfig->base, pConfig->m_PinNum);
        return TRUE;
    }

    return FALSE;
}


/***********************************************************************************************
 * @function name:  Ecual_GpioWriteCh
 * @description:    �������ͨ���������ö�Ӧ���ŵĵ�ƽ
 * @input parameters: OutputId_t pinIndex - ���ͨ��������GpioLevel_t level - ��ƽֵ
 * @output parameters: ��
 * @return:         ��
 * @author:         ssj 2025-05-28 17:45
 ***********************************************************************************************/
void Ecual_GpioWriteCh(OutputId_t pinIndex, GpioLevel_t level)
{
	if(pinIndex < EN_OutputNum)
	{
		const OutputPinCfg_t *OutputPin = &Io_OutPutTbl[pinIndex];

		Ecual_GpioWriteOutPutPin(OutputPin->pinId, level);
	}
}

/***********************************************************************************************
 * @function name:  Ecual_GpioWriteCh
 * @description:    �������ͨ���������ö�Ӧ���ŵĵ�ƽ
 * @input parameters: OutputId_t pinIndex - ���ͨ��������GpioLevel_t level - ��ƽֵ
 * @output parameters: ��
 * @return:         ��
 * @author:         ssj 2025-05-28 17:45
 ***********************************************************************************************/
void Ecual_GpioToggleCh(OutputId_t pinIndex)
{
	if(pinIndex < EN_OutputNum)
	{
		const OutputPinCfg_t *OutputPin = &Io_OutPutTbl[pinIndex];

		Ecual_GpioToggleOutPutPin(OutputPin->pinId);
	}
}

/***********************************************************************************************
 * @function name:  Ecual_GpioGetChlState
 * @description:    ��ȡָ�����ŵ�ƽ������ GPIO ����ģʽ����Ч
 * @input parameters: pin_config_id_t pinIndex - ��������
 * @output parameters: ��
 * @return:         GpioLevel_t - �������ŵ�ƽֵ����/�ͣ����� EN_GPIO_LEV_NONE ��ʾ��Ч
 * @author:         ssj 2025-05-28 17:42
 ***********************************************************************************************/
GpioLevel_t Ecual_GpioGetChlState(pin_config_id_t pinIndex)
{
    if(pinIndex >= PINS_NUM_MAX)
    {
        return EN_GPIO_LEV_NONE;
    }

    const pin_settings_config_t *pConfig = &g_pin_mux_InitConfigArr[pinIndex];

    if(pConfig->m_Mode == GPIO_MODE_IN)
    {
        uint32_t value = PINS_DRV_ReadPins(pConfig->base);

        if((value & (1 << pConfig->m_PinNum)) != 0U)
        {
            return EN_GPIO_LEV_HIGH;
        }
        else
        {
            return EN_GPIO_LEV_LOW;
        }
    }

    return EN_GPIO_LEV_NONE;
}
/***********************************************************************
 * @function name: Ecual_GetDigitalSwStatus
 * @description: ��ȡ���ּ��˿��Ƿ��⵽��Ч
 * @input parameters: GpioSignalInName_t SignalName���˿�����
 * @output parameters: void
 * @return: BOOL���˿���Ч��
 * @note:
 * @author: Michael Xin
 * @date: 2022-11-03 14:50
 ***********************************************************************/
BOOL Ecual_GetDigitalSwStatus(DigitalSignalInName_t SignalName)
{
	BOOL tVaild = FALSE;

	if (SignalName < EN_GPIO_IN_ALL_NUM) /*�ź�����С�ڶ����ö�����ֵ*/
	{
		tVaild = Io_CheckVaildTbl[SignalName].IsVaild;;
	}

	return tVaild;
}
/***********************************************************************
 * @function name: Ecual_GpioScan
 *
 * @description: ɨ������IO�˿�
 *
 * @input parameters: void
 *
 * @output parameters: void
 *
 * @return: void
 *
 * @note:
 *
 * @author: Michael Xin
 *
 * @date: 2022-11-03 14:46
 ***********************************************************************/
void Ecual_GpioScan(void)
{
	IoCheckCfg_t *pIoCfg = Io_CheckVaildTbl;
	GpioLevel_t GpioLevel = EN_GPIO_LEV_NONE;
	INT8U i = 0;

	for (i = 0; i < (INT8U)EN_GPIO_IN_ALL_NUM; i++)
	{
		GpioLevel = Ecual_GpioGetChlState(pIoCfg[i].pinIndex);

		if (GpioLevel == pIoCfg[i].IoChkVaild) //�Ա����õ���Чֵ�Ƿ�һ��
		{
			if (pIoCfg[i].ScanCnt < D_SCAN_COUNTER_MAX)//��ֹɨ��������
			{
				pIoCfg[i].ScanCnt += D_GPIO_SCAN_PERIOD;
			}

			if (pIoCfg[i].ScanCnt >= pIoCfg[i].ShakeCnt)//ɨ����Ч�������������������˿���Ϊ��Ч
			{
				pIoCfg[i].IsVaild = TRUE;
			}
		}
		else
		{
			pIoCfg[i].ScanCnt = 0;
			pIoCfg[i].IsVaild = FALSE;
		}
	}
}
