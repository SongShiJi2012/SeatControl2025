/***********************************************************************************************
 * @file:            ecual_pins.h
 * @description:     声明 GPIO 输出控制相关的结构体、枚举、接口函数原型。
 *                   提供上层模块调用 GPIO 输出通道的统一接口。
 * @author:          ssj 2025-05-28
 * @version:         V1.0
 ***********************************************************************************************/


#ifndef ECUAL_PINS_H_
#define ECUAL_PINS_H_

#include "types.h"
#include "pins_driver.h"

#define D_GPIO_SCAN_PERIOD              (5U)//ms

#define D_SCAN_COUNTER_MAX              (0xFFU - D_GPIO_SCAN_PERIOD)

// 定义引脚的索引
typedef enum
{
    /* KF32A156MQV144-LQFP     Pin Name    */
	enPin1,// 预驱1 PWM1输出	0u
	enPin2,// 预驱1 PWM2输出	1u
	enPin3,// 预驱1 PWM3输出	2u
	enPin4,// 预驱1 PWM4输出-先EN功能	3u
	enPin5,// 记忆调节开关（预留）（AD检）	4u
	enPin6,// 主驾通风反馈-高低检	5u
	enPin7,// 副驾通风反馈	6u
	enPin8,// 通风3反馈	7u
	enPin9,// 通风4反馈	8u
	enPin15,// 晶振频率为16MHz	9u
	enPin16,// 晶振频率为16MHz	10u
	enPin17,// 预驱2 PWM1输出	11u
	enPin18,// 预驱2 PWM2输出	12u
	enPin19,// 预驱2 PWM3输出	13u
	enPin20,// 预驱2 SPI SS2使能	14u
	enPin21,// 预驱1 SPI MISO	15u
	enPin22,// 预驱1 SPI SCLK	16u
	enPin23,// 分立12V使能控制	17u
	enPin24,// LIN	18u
	enPin25,// LIN	19u
	enPin26,// LIN使能	20u
	enPin27,// 预驱1 SPI SS1使能	21u
	enPin28,// 预驱1 SPI MOSI	22u
	enPin29,// CAN6	23u
	enPin30,// CAN6	24u
	enPin31,// 串口打印	25u
	enPin32,// CAN错误指示输出	26u
	enPin33,// 喂狗信号	27u
	enPin34,// CAN使能	28u
	enPin35,// 预留	29u
	enPin36,// 预留	30u
	enPin39,// 主驾加热NTC采集（AD检）【NTC1】	31u
	enPin40,// 预驱2 PWM4输出-先EN功能	32u
	enPin41,// 预留	33u
	enPin42,// 主驾坐垫前部角度向前调节开关检测（低检）	34u
	enPin43,// 主驾靠背调节电机电流检测（AD检）【低边采集】	35u
	enPin44,// 主驾高度调节电机电流检测（AD检）【低边采集】	36u
	enPin45,// 副驾纵向调节电机电流检测（AD检）预驱1 CS01【高边采集】	37u
	enPin46,// 副驾靠背调节电机电流检测（AD检）预驱1 CS02【高边采集】	38u
	enPin47,// 主驾纵向调节电机电流检测（AD检）预驱2 CS01【高边采集】	39u
	enPin48,// 副驾靠背向后调节开关检测（低检）	40u
	enPin49,// 主驾高度向下调节开关检测（低检）	41u
	enPin50,// 副驾靠背向前调节开关检测（低检）	42u
	enPin51,// 主驾高度向上调节开关检测（低检）	43u
	enPin52,// 主驾纵向向后调节开关检测（低检）	44u
	enPin53,// 主驾前部角度调节电机电流检测（AD检）预驱2 CS02【高边采集】	45u
	enPin54,// 副驾加热NCT采集（AD检）【NTC2】	46u
	enPin55,// NTC3采集（AD检）	47u
	enPin56,// NTC4采集（AD检）	48u
	enPin57,// 方向盘加热NTC采集（AD检）【NTC5】	49u
	enPin58,// 板端NTC采集（AD检）	50u
	enPin59,// 预留	51u
	enPin62,// 主驾加热控制	52u
	enPin63,// 副驾加热控制	53u
	enPin64,// 主驾加热电流反馈（AD检）	54u
	enPin65,// 副驾加热电流反馈（AD检）	55u
	enPin66,// 霍尔供电反馈（预留）（AD检）	56u
	enPin67,// 主驾纵向向前调节开关检测（低检）	57u
	enPin68,// KL30检测	58u
	enPin69,// 加热3控制	59u
	enPin70,// 加热3&4电流检测（AD检）	60u
	enPin71,// 加热3&4电流检测切换	61u
	enPin72,// 加热4控制	62u
	enPin73,// 方向盘加热电流反馈（AD检）	63u
	enPin74,// 方向盘加热控制	64u
	enPin75,// EEPROM（I2C）	65u
	enPin76,// EEPROM（I2C）	66u
	enPin77,// 副驾纵向向后调节开关检测（低检）	67u
	enPin78,// 副驾纵向向前调节开关检测（低检）	68u
	enPin79,// 主驾靠背角度向后调节开关检测（低检）	69u
	enPin80,// 主驾靠背角度向前调节开关检测（低检）	70u
	enPin81,// 主驾坐垫前部角度向后调节开关检测（低检）	71u
	enPin82,// 主驾通风PWM输出	72u
	enPin83,// 副驾通风PWM输出	73u
	enPin84,// 通风3 PWM输出	74u
	enPin85,// 通风4 PWM输出	75u
	enPin88,// KL15检测（高低检）	76u
	enPin89,// 记忆开关检测（预留）（低检）	77u
	enPin90,// 主驾纵向霍尔反馈（AD检）	78u
	enPin91,// 主驾高度霍尔反馈（AD检）	79u
	enPin92,// 主驾靠背霍尔反馈（AD检）	80u
	enPin93,// 主驾坐垫前部角度霍尔反馈（AD检）	81u
	enPin94,// 副驾纵向霍尔反馈（AD检）	82u
	enPin95,// 副驾靠背霍尔反馈（AD检）	83u
	enPin96,// 烧录口	84u
	enPin97,// 复位	85u
	enPin98,// 烧录口	86u
	enPin99,// 霍尔供电控制（预留）	87u
	enPin100,// CAN STB控制	88u

    PINS_NUM_MAX
}pin_config_id_t;

typedef enum _DI_SIGNAL_IN_NAME_T
{
//	EN_MemorySetButton,/*PIN105记忆开关设置（预留）*/
	EN_DRVenFeedback,/*主驾通风反馈*/
	EN_PaVenFeedback,/*副驾通风反馈*/

	EN_DRHeightBackwardSW,/*主驾高度开关检测-靠背向后*/
	EN_DRHeightForwardSW,/*主驾高度开关检测-靠背向前*/
	EN_DRLengthBackwardSW,/*主驾纵向开关检测-靠背向后*/
	EN_DRLengthForwardSW,/*主驾纵向开关检测-靠背向前*/
	EN_DRBackBackwardSW,/*主驾靠背开关检测-靠背向后*/
	EN_DRBackForwardSW,/*主驾靠背开关检测-靠背向前*/
	EN_DRFrontBackwardSW,/*主驾前部角度开关检测-靠背向后*/
	EN_DRFrontForwardSW,/*主驾前部角度开关检测-靠背向前*/

	EN_PALengthBackwardSW,/*副驾纵向开关检测-靠背向后*/
	EN_PALengthForwardSW,/*副驾纵向开关检测-靠背向前*/
	EN_PABackBackwardSW,/*副驾靠背开关检测-靠背向后*/
	EN_PABackForwardSW,/*副驾靠背开关检测-靠背向前*/

	EN_KL15Level,  /* kl15 引脚 */

    /* ...... */
    EN_GPIO_IN_ALL_NUM
}DigitalSignalInName_t; //输入枚举表
typedef enum
{
    EN_PreDrv1Pwm4Out,        /* 预驱1 PWM4输出-先EN功能 */
    EN_PreDrv2SpiSs2Out,      /* 预驱2 SPI SS2使能 */
    EN_Discrete12VOut,        /* 分立12V使能控制 */
    EN_LinEnOut,              /* LIN使能 */
    EN_CanErrOut,             /* CAN错误指示输出 */
    EN_CanEnOut,              /* CAN使能 */
    EN_Reserve0Out,           /* 预留 */
    EN_Reserve1Out,           /* 预留 */
    EN_PreDrv2Pwm4Out,        /* 预驱2 PWM4输出-先EN功能 */
    EN_Reserve2Out,           /* 预留 */
    EN_Reserve3Out,           /* 预留 */
    EN_DrHeatOut,             /* 主驾加热控制 */
    EN_PaHeatOut,             /* 副驾加热控制 */
    EN_Heat3Out,              /* 加热3控制 */
    EN_Heat3_4CurrSelOut,     /* 加热3&4电流检测切换 */
    EN_Heat4Out,              /* 加热4控制 */
	EN_WheelHeatCtrlOut,      /* 方向盘加热控制 */
    EN_HallPwrOut,            /* 霍尔供电控制（预留） */
    EN_CanStbOut,             /* CAN STB控制 */
    EN_WdogOut,               /* 喂狗 */
    EN_OutputNum
} OutputId_t;//输出枚举表

typedef enum _GPIO_INITIAL_LEVEL_T
{
    EN_GPIO_LEV_LOW = 0U,
    EN_GPIO_LEV_HIGH = 1U,
    EN_GPIO_LEV_NONE
}GpioLevel_t;

/*************************************************************************************************
 * Macro definition
 *************************************************************************************************/

#define LV_low     ( 0 ) // 低电平
#define LV_high    ( 1 ) // 高电平

#define PIN_OUT( pin, level )          ecual_PIN_output( pin, level )
#define PIN_GET( pin )                 ecual_PIN_get( pin )

typedef enum
{
    PINS_MODE_INIT = 0,
	PINS_MODE_NORAML,
	PINS_MODE_SUSPEND,
	PINS_MODE_OFFMODE,
    
    PINS_MODE_MAX
} ePinsConfigMode;

typedef struct _IO_CHECK_CFG_T
{
    const DigitalSignalInName_t IoChkSgn;      /*!< 扫描信号名称 */
    const GpioLevel_t IoChkVaild;      /*!< 端口高有效、低有效 */
    const uint8_t ShakeCnt;                   /*!< 端口消抖值 */
    uint8_t ScanCnt;                          /*!< 端口消抖计数 */
    BOOL IsVaild;                           /*!< 端口是否有效 */
    pin_config_id_t pinIndex;
}IoCheckCfg_t;
typedef struct
{
	OutputId_t outputId;       // 输出通道定义（枚举值）
    pin_config_id_t pinId;  // 引脚枚举（如 enPin52）
} OutputPinCfg_t;


extern status_t ecual_pins_init( ePinsConfigMode InitMode );
extern GpioLevel_t Ecual_GpioGetChlState(pin_config_id_t pinIndex);
extern void Ecual_GpioWriteCh(OutputId_t pinIndex, GpioLevel_t level);
extern void Ecual_GpioScan(void);
extern BOOL Ecual_GetDigitalSwStatus(DigitalSignalInName_t SignalName);
extern void Ecual_GpioToggleCh(OutputId_t pinIndex);
extern BOOL Ecual_GpioToggleOutPutPin(pin_config_id_t pinIndex);

#endif /* ECUAL_PINS_H_ */
