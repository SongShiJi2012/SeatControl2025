/***********************************************************************************************
 * @file:            ecual_pins.h
 * @description:     ���� GPIO ���������صĽṹ�塢ö�١��ӿں���ԭ�͡�
 *                   �ṩ�ϲ�ģ����� GPIO ���ͨ����ͳһ�ӿڡ�
 * @author:          ssj 2025-05-28
 * @version:         V1.0
 ***********************************************************************************************/


#ifndef ECUAL_PINS_H_
#define ECUAL_PINS_H_

#include "types.h"
#include "pins_driver.h"

#define D_GPIO_SCAN_PERIOD              (5U)//ms

#define D_SCAN_COUNTER_MAX              (0xFFU - D_GPIO_SCAN_PERIOD)

// �������ŵ�����
typedef enum
{
    /* KF32A156MQV144-LQFP     Pin Name    */
	enPin1,// Ԥ��1 PWM1���	0u
	enPin2,// Ԥ��1 PWM2���	1u
	enPin3,// Ԥ��1 PWM3���	2u
	enPin4,// Ԥ��1 PWM4���-��EN����	3u
	enPin5,// ������ڿ��أ�Ԥ������AD�죩	4u
	enPin6,// ����ͨ�練��-�ߵͼ�	5u
	enPin7,// ����ͨ�練��	6u
	enPin8,// ͨ��3����	7u
	enPin9,// ͨ��4����	8u
	enPin15,// ����Ƶ��Ϊ16MHz	9u
	enPin16,// ����Ƶ��Ϊ16MHz	10u
	enPin17,// Ԥ��2 PWM1���	11u
	enPin18,// Ԥ��2 PWM2���	12u
	enPin19,// Ԥ��2 PWM3���	13u
	enPin20,// Ԥ��2 SPI SS2ʹ��	14u
	enPin21,// Ԥ��1 SPI MISO	15u
	enPin22,// Ԥ��1 SPI SCLK	16u
	enPin23,// ����12Vʹ�ܿ���	17u
	enPin24,// LIN	18u
	enPin25,// LIN	19u
	enPin26,// LINʹ��	20u
	enPin27,// Ԥ��1 SPI SS1ʹ��	21u
	enPin28,// Ԥ��1 SPI MOSI	22u
	enPin29,// CAN6	23u
	enPin30,// CAN6	24u
	enPin31,// ���ڴ�ӡ	25u
	enPin32,// CAN����ָʾ���	26u
	enPin33,// ι���ź�	27u
	enPin34,// CANʹ��	28u
	enPin35,// Ԥ��	29u
	enPin36,// Ԥ��	30u
	enPin39,// ���ݼ���NTC�ɼ���AD�죩��NTC1��	31u
	enPin40,// Ԥ��2 PWM4���-��EN����	32u
	enPin41,// Ԥ��	33u
	enPin42,// ��������ǰ���Ƕ���ǰ���ڿ��ؼ�⣨�ͼ죩	34u
	enPin43,// ���ݿ������ڵ��������⣨AD�죩���ͱ߲ɼ���	35u
	enPin44,// ���ݸ߶ȵ��ڵ��������⣨AD�죩���ͱ߲ɼ���	36u
	enPin45,// ����������ڵ��������⣨AD�죩Ԥ��1 CS01���߲߱ɼ���	37u
	enPin46,// ���ݿ������ڵ��������⣨AD�죩Ԥ��1 CS02���߲߱ɼ���	38u
	enPin47,// ����������ڵ��������⣨AD�죩Ԥ��2 CS01���߲߱ɼ���	39u
	enPin48,// ���ݿ��������ڿ��ؼ�⣨�ͼ죩	40u
	enPin49,// ���ݸ߶����µ��ڿ��ؼ�⣨�ͼ죩	41u
	enPin50,// ���ݿ�����ǰ���ڿ��ؼ�⣨�ͼ죩	42u
	enPin51,// ���ݸ߶����ϵ��ڿ��ؼ�⣨�ͼ죩	43u
	enPin52,// �������������ڿ��ؼ�⣨�ͼ죩	44u
	enPin53,// ����ǰ���Ƕȵ��ڵ��������⣨AD�죩Ԥ��2 CS02���߲߱ɼ���	45u
	enPin54,// ���ݼ���NCT�ɼ���AD�죩��NTC2��	46u
	enPin55,// NTC3�ɼ���AD�죩	47u
	enPin56,// NTC4�ɼ���AD�죩	48u
	enPin57,// �����̼���NTC�ɼ���AD�죩��NTC5��	49u
	enPin58,// ���NTC�ɼ���AD�죩	50u
	enPin59,// Ԥ��	51u
	enPin62,// ���ݼ��ȿ���	52u
	enPin63,// ���ݼ��ȿ���	53u
	enPin64,// ���ݼ��ȵ���������AD�죩	54u
	enPin65,// ���ݼ��ȵ���������AD�죩	55u
	enPin66,// �������練����Ԥ������AD�죩	56u
	enPin67,// ����������ǰ���ڿ��ؼ�⣨�ͼ죩	57u
	enPin68,// KL30���	58u
	enPin69,// ����3����	59u
	enPin70,// ����3&4������⣨AD�죩	60u
	enPin71,// ����3&4��������л�	61u
	enPin72,// ����4����	62u
	enPin73,// �����̼��ȵ���������AD�죩	63u
	enPin74,// �����̼��ȿ���	64u
	enPin75,// EEPROM��I2C��	65u
	enPin76,// EEPROM��I2C��	66u
	enPin77,// �������������ڿ��ؼ�⣨�ͼ죩	67u
	enPin78,// ����������ǰ���ڿ��ؼ�⣨�ͼ죩	68u
	enPin79,// ���ݿ����Ƕ������ڿ��ؼ�⣨�ͼ죩	69u
	enPin80,// ���ݿ����Ƕ���ǰ���ڿ��ؼ�⣨�ͼ죩	70u
	enPin81,// ��������ǰ���Ƕ������ڿ��ؼ�⣨�ͼ죩	71u
	enPin82,// ����ͨ��PWM���	72u
	enPin83,// ����ͨ��PWM���	73u
	enPin84,// ͨ��3 PWM���	74u
	enPin85,// ͨ��4 PWM���	75u
	enPin88,// KL15��⣨�ߵͼ죩	76u
	enPin89,// ���俪�ؼ�⣨Ԥ�������ͼ죩	77u
	enPin90,// �����������������AD�죩	78u
	enPin91,// ���ݸ߶Ȼ���������AD�죩	79u
	enPin92,// ���ݿ�������������AD�죩	80u
	enPin93,// ��������ǰ���ǶȻ���������AD�죩	81u
	enPin94,// �����������������AD�죩	82u
	enPin95,// ���ݿ�������������AD�죩	83u
	enPin96,// ��¼��	84u
	enPin97,// ��λ	85u
	enPin98,// ��¼��	86u
	enPin99,// ����������ƣ�Ԥ����	87u
	enPin100,// CAN STB����	88u

    PINS_NUM_MAX
}pin_config_id_t;

typedef enum _DI_SIGNAL_IN_NAME_T
{
//	EN_MemorySetButton,/*PIN105���俪�����ã�Ԥ����*/
	EN_DRVenFeedback,/*����ͨ�練��*/
	EN_PaVenFeedback,/*����ͨ�練��*/

	EN_DRHeightBackwardSW,/*���ݸ߶ȿ��ؼ��-�������*/
	EN_DRHeightForwardSW,/*���ݸ߶ȿ��ؼ��-������ǰ*/
	EN_DRLengthBackwardSW,/*�������򿪹ؼ��-�������*/
	EN_DRLengthForwardSW,/*�������򿪹ؼ��-������ǰ*/
	EN_DRBackBackwardSW,/*���ݿ������ؼ��-�������*/
	EN_DRBackForwardSW,/*���ݿ������ؼ��-������ǰ*/
	EN_DRFrontBackwardSW,/*����ǰ���Ƕȿ��ؼ��-�������*/
	EN_DRFrontForwardSW,/*����ǰ���Ƕȿ��ؼ��-������ǰ*/

	EN_PALengthBackwardSW,/*�������򿪹ؼ��-�������*/
	EN_PALengthForwardSW,/*�������򿪹ؼ��-������ǰ*/
	EN_PABackBackwardSW,/*���ݿ������ؼ��-�������*/
	EN_PABackForwardSW,/*���ݿ������ؼ��-������ǰ*/

	EN_KL15Level,  /* kl15 ���� */

    /* ...... */
    EN_GPIO_IN_ALL_NUM
}DigitalSignalInName_t; //����ö�ٱ�
typedef enum
{
    EN_PreDrv1Pwm4Out,        /* Ԥ��1 PWM4���-��EN���� */
    EN_PreDrv2SpiSs2Out,      /* Ԥ��2 SPI SS2ʹ�� */
    EN_Discrete12VOut,        /* ����12Vʹ�ܿ��� */
    EN_LinEnOut,              /* LINʹ�� */
    EN_CanErrOut,             /* CAN����ָʾ��� */
    EN_CanEnOut,              /* CANʹ�� */
    EN_Reserve0Out,           /* Ԥ�� */
    EN_Reserve1Out,           /* Ԥ�� */
    EN_PreDrv2Pwm4Out,        /* Ԥ��2 PWM4���-��EN���� */
    EN_Reserve2Out,           /* Ԥ�� */
    EN_Reserve3Out,           /* Ԥ�� */
    EN_DrHeatOut,             /* ���ݼ��ȿ��� */
    EN_PaHeatOut,             /* ���ݼ��ȿ��� */
    EN_Heat3Out,              /* ����3���� */
    EN_Heat3_4CurrSelOut,     /* ����3&4��������л� */
    EN_Heat4Out,              /* ����4���� */
	EN_WheelHeatCtrlOut,      /* �����̼��ȿ��� */
    EN_HallPwrOut,            /* ����������ƣ�Ԥ���� */
    EN_CanStbOut,             /* CAN STB���� */
    EN_WdogOut,               /* ι�� */
    EN_OutputNum
} OutputId_t;//���ö�ٱ�

typedef enum _GPIO_INITIAL_LEVEL_T
{
    EN_GPIO_LEV_LOW = 0U,
    EN_GPIO_LEV_HIGH = 1U,
    EN_GPIO_LEV_NONE
}GpioLevel_t;

/*************************************************************************************************
 * Macro definition
 *************************************************************************************************/

#define LV_low     ( 0 ) // �͵�ƽ
#define LV_high    ( 1 ) // �ߵ�ƽ

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
    const DigitalSignalInName_t IoChkSgn;      /*!< ɨ���ź����� */
    const GpioLevel_t IoChkVaild;      /*!< �˿ڸ���Ч������Ч */
    const uint8_t ShakeCnt;                   /*!< �˿�����ֵ */
    uint8_t ScanCnt;                          /*!< �˿��������� */
    BOOL IsVaild;                           /*!< �˿��Ƿ���Ч */
    pin_config_id_t pinIndex;
}IoCheckCfg_t;
typedef struct
{
	OutputId_t outputId;       // ���ͨ�����壨ö��ֵ��
    pin_config_id_t pinId;  // ����ö�٣��� enPin52��
} OutputPinCfg_t;


extern status_t ecual_pins_init( ePinsConfigMode InitMode );
extern GpioLevel_t Ecual_GpioGetChlState(pin_config_id_t pinIndex);
extern void Ecual_GpioWriteCh(OutputId_t pinIndex, GpioLevel_t level);
extern void Ecual_GpioScan(void);
extern BOOL Ecual_GetDigitalSwStatus(DigitalSignalInName_t SignalName);
extern void Ecual_GpioToggleCh(OutputId_t pinIndex);
extern BOOL Ecual_GpioToggleOutPutPin(pin_config_id_t pinIndex);

#endif /* ECUAL_PINS_H_ */
