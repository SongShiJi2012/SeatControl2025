/***********************************************************************************************
 * @file:            ecual_pins.c
 * @description:     实现输出引脚的 GPIO 控制接口，包括电平设置函数等。
 *                   通过 OutputId_t 枚举索引对应引脚，控制硬件输出状态。
 * @author:          ssj 2025-05-28
 * @version:         V1.0
 ***********************************************************************************************/

#include "ecual_pins.h"

extern const pin_settings_config_t g_pin_mux_InitConfigArr[SELECT_PLATFORM_PINS];
extern const pin_settings_config_t g_pin_mux_OffModeConfigArr[SELECT_PLATFORM_PINS];
/*! @brief 端口检测有效性列表 ,需要按照信号枚举值排列,否则Hal_GetIoVaild获取的状态会错位*/
static IoCheckCfg_t Io_CheckVaildTbl[EN_GPIO_IN_ALL_NUM] =
{
//	{EN_MemorySetButton,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  EN_MCU_PIN26_MEMORY_SET_IN}, /*记忆设置预留*/
	{EN_DRVenFeedback,    		EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin6}, /*主驾通风*/
	{EN_PaVenFeedback,     		EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin7}, /*副驾通风*/

	{EN_DRHeightBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin49}, /*主驾高度开关检测-向后*/
	{EN_DRHeightForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin51}, /*主驾高度开关检测-向前*/
	{EN_DRLengthBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin52}, /*主驾纵向开关检测-向后*/
	{EN_DRLengthForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin67}, /*主驾纵向开关检测-向前*/
	{EN_DRBackBackwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin79}, /*主驾靠背开关检测-向后*/
	{EN_DRBackForwardSW,        EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin80}, /*主驾靠背开关检测-向前*/
	{EN_DRFrontBackwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin81}, /*主驾前部角度开关检测-向后*/
	{EN_DRFrontForwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin42}, /*主驾前部角度开关检测-向前*/
	{EN_PALengthBackwardSW,     EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin77}, /*副驾纵向开关检测-向后*/
	{EN_PALengthForwardSW,      EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin78}, /*副驾纵向开关检测-向前*/
	{EN_PABackBackwardSW,       EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin48}, /*副驾靠背开关检测-向后*/
	{EN_PABackForwardSW,        EN_GPIO_LEV_LOW, 20, 0, FALSE,  enPin50}, /*副驾靠背开关检测-向前*/

	{EN_KL15Level,              EN_GPIO_LEV_HIGH, 20, 0, FALSE,  enPin88}, /* KL15 引脚电平 */
};

static OutputPinCfg_t Io_OutPutTbl[EN_OutputNum] =
{
	{ EN_PreDrv1Pwm4Out,      enPin4  },   // 预驱1 PWM4输出-先EN功能
	{ EN_PreDrv2SpiSs2Out,    enPin20 },   // 预驱2 SPI SS2使能
	{ EN_Discrete12VOut,      enPin23 },   // 分立12V使能控制
	{ EN_LinEnOut,            enPin26 },   // LIN使能
	{ EN_CanErrOut,           enPin32 },   // CAN错误指示输出
	{ EN_CanEnOut,            enPin34 },   // CAN使能
	{ EN_Reserve0Out,         enPin35 },   // 预留
	{ EN_Reserve1Out,         enPin36 },   // 预留
	{ EN_PreDrv2Pwm4Out,      enPin40 },   // 预驱2 PWM4输出-先EN功能
	{ EN_Reserve2Out,         enPin41 },   // 预留
	{ EN_Reserve3Out,         enPin59 },   // 预留
	{ EN_DrHeatOut,           enPin62 },   // 主驾加热控制
	{ EN_PaHeatOut,           enPin63 },   // 副驾加热控制
	{ EN_Heat3Out,            enPin69 },   // 加热3控制
	{ EN_Heat3_4CurrSelOut,   enPin71 },   // 加热3&4电流检测切换
	{ EN_Heat4Out,            enPin72 },   // 加热4控制
	{ EN_WheelHeatCtrlOut,    enPin74 },   // 方向盘加热控制
	{ EN_HallPwrOut,          enPin99 },   // 霍尔供电控制（预留）
	{ EN_CanStbOut,           enPin100 },   // CAN STB控制
	{ EN_WdogOut,             enPin33 }   // 喂狗
    

};
/*************************************************************************************************
 * @function name:      ecual_pins_init
 *
 * @description:        板集所有pin脚初始化
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
 * @description:    控制配置表中配置为输出的 IO 引脚电平
 * @input parameters:     pin_id: 配置引脚枚举编号 enPinXX ；level: 电平值（0/1）
 * @output parameters:    无
 * @return:         BOOL 类型，TRUE 成功，FALSE 非输出口或非法编号
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
 * @description:    控制配置表中配置为输出的 IO 引脚电平
 * @input parameters:     pin_id: 配置引脚枚举编号 enPinXX ；level: 电平值（0/1）
 * @output parameters:    无
 * @return:         BOOL 类型，TRUE 成功，FALSE 非输出口或非法编号
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
 * @description:    根据输出通道索引设置对应引脚的电平
 * @input parameters: OutputId_t pinIndex - 输出通道索引；GpioLevel_t level - 电平值
 * @output parameters: 无
 * @return:         无
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
 * @description:    根据输出通道索引设置对应引脚的电平
 * @input parameters: OutputId_t pinIndex - 输出通道索引；GpioLevel_t level - 电平值
 * @output parameters: 无
 * @return:         无
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
 * @description:    读取指定引脚电平，仅在 GPIO 输入模式下有效
 * @input parameters: pin_config_id_t pinIndex - 引脚索引
 * @output parameters: 无
 * @return:         GpioLevel_t - 返回引脚电平值（高/低），或 EN_GPIO_LEV_NONE 表示无效
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
 * @description: 获取数字检测端口是否检测到有效
 * @input parameters: GpioSignalInName_t SignalName：端口名称
 * @output parameters: void
 * @return: BOOL：端口有效性
 * @note:
 * @author: Michael Xin
 * @date: 2022-11-03 14:50
 ***********************************************************************/
BOOL Ecual_GetDigitalSwStatus(DigitalSignalInName_t SignalName)
{
	BOOL tVaild = FALSE;

	if (SignalName < EN_GPIO_IN_ALL_NUM) /*信号名称小于定义的枚举最大值*/
	{
		tVaild = Io_CheckVaildTbl[SignalName].IsVaild;;
	}

	return tVaild;
}
/***********************************************************************
 * @function name: Ecual_GpioScan
 *
 * @description: 扫描所有IO端口
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

		if (GpioLevel == pIoCfg[i].IoChkVaild) //对比配置的有效值是否一致
		{
			if (pIoCfg[i].ScanCnt < D_SCAN_COUNTER_MAX)//防止扫描计数溢出
			{
				pIoCfg[i].ScanCnt += D_GPIO_SCAN_PERIOD;
			}

			if (pIoCfg[i].ScanCnt >= pIoCfg[i].ShakeCnt)//扫描有效次数满足消抖次数将端口置为有效
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
