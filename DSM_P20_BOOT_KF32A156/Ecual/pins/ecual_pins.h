/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_pins.h
*
*  Description:  board bins abstraction header file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-15
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/

#ifndef ECUAL_PINS_H_
#define ECUAL_PINS_H_

#include "status.h"
#include "types.h"
#include "pins_driver.h"
//#include "pins_init_cfg.h"
//#include "pins_off_cfg.h"

// 定义引脚的索引
enum
{
    /* KF32A156MQV144-LQFP     Pin Name    */
	P1_PTE16 =	0u,  //	0u
	P2_PTE15	,    //	1u
	P3_PTD1		,    //	2u
	P4_PTD0		,    //	3u
	P5_PTE11	,    //	4u
	P6_PTE10	,    //	5u
	P7_PTE13	,    //	6u
	P8_PTE5		,    //	7u
	P9_PTE4		,    //	8u
	P15_PTB7	,    //	9u
	P16_PTB6	,    //	10u
	P17_PTE14	,    //	11u
	P18_PTE3	,    //	12u
	P19_PTE12	,    //	13u
	P20_PTD17	,    //	14u
	P21_PTD16	,    //	15u
	P22_PTD15	,    //	16u
	P23_PTE9	,    //	17u
	P24_PTD14	,    //	18u
	P25_PTD13	,    //	19u
	P26_PTE8	,    //	20u
	P27_PTB5	,    //	21u
	P28_PTB4	,    //	22u
	P29_PTC3	,    //	23u
	P30_PTC2	,    //	24u
	P31_PTD7	,    //	25u
	P32_PTD6	,    //	26u
	P33_PTD5	,    //	27u
	P34_PTD12	,    //	28u
	P35_PTD11	,    //	29u
	P36_PTD10	,    //	30u
	P39_PTC1	,    //	31u
	P40_PTC0	,    //	32u
	P41_PTD9	,    //	33u
	P42_PTD8	,    //	34u
	P43_PTC17	,    //	35u
	P44_PTC16	,    //	36u
	P45_PTC15	,    //	37u
	P46_PTC14	,    //	38u
	P47_PTB3	,    //	39u
	P48_PTB2	,    //	40u
	P49_PTC13	,    //	41u
	P50_PTC12	,    //	42u
	P51_PTC11	,    //	43u
	P52_PTC10	,    //	44u
	P53_PTB1	,    //	45u
	P54_PTB0	,    //	46u
	P55_PTC9	,    //	47u
	P56_PTC8	,    //	48u
	P57_PTA7	,    //	49u
	P58_PTA6	,    //	50u
	P59_PTE7	,    //	51u
	P62_PTA17	,    //	52u
	P63_PTB17	,    //	53u
	P64_PTB16	,    //	54u
	P65_PTB15	,    //	55u
	P66_PTB14	,    //	56u
	P67_PTB13	,    //	57u
	P68_PTB12	,    //	58u
	P69_PTD4	,    //	59u
	P70_PTD3	,    //	60u
	P71_PTD2	,    //	61u
	P72_PTA3	,    //	62u
	P73_PTA2	,    //	63u
	P74_PTB11	,    //	64u
	P75_PTB10	,    //	65u
	P76_PTB9	,    //	66u
	P77_PTB8	,    //	67u
	P78_PTA1	,    //	68u
	P79_PTA0	,    //	69u
	P80_PTC7	,    //	70u
	P81_PTC6	,    //	71u
	P82_PTA16	,    //	72u
	P83_PTA15	,    //	73u
	P84_PTE6	,    //	74u
	P85_PTE2	,    //	75u
	P88_PTA14	,    //	76u
	P89_PTA13	,    //	77u
	P90_PTA12	,    //	78u
	P91_PTA11	,    //	79u
	P92_PTA10	,    //	80u
	P93_PTE1	,    //	81u
	P94_PTE0	,    //	82u
	P95_PTC5	,    //	83u
	P96_PTC4	,    //	84u
	P97_PTA5	,    //	85u
	P98_PTA4	,    //	86u
	P99_PTA9	,    //	87u
	P100_PTA8	,    //	88u

    PINS_NUM_MAX
};


//========================== 板级引脚用户定义===================//
typedef enum
{
    MCU_PIN5_DI_L_TRUNKLID_SW       = P5_PTE11,           /* 后开备箱关输入检测 */
    MCU_PIN6_DI_L_DRV_UNLOCK        = P6_PTE10,           /* 左前门把手BT解锁 输入*/
    MCU_PIN7_DI_L_AST_UNLOCK        = P7_PTE13,           /* 右前门把手BT解锁 输入*/
    MCU_PIN8_DI_L_DRV_LOCK          = P8_PTE5,            /* 左前门把手BT闭锁 输入*/
    MCU_PIN9_DI_L_AST_LOCK          = P9_PTE4,            /* 右前门把手BT闭锁 输入*/
    MCU_PIN50_DO_H_12V_PU_CYR       = P50_PTC12,          /* 高低检供电12V开关控制*/

	MCU_PIN51_DI_L_BT_WAKEUP      	= P51_PTC11, 		  /* BT40唤醒MCU*/
	MCU_PIN52_DI_L_RESET_BT40       = P52_PTC10, 		  /* MCU复位BT40*/

	MCU_PIN91_DO_HL_BCAN_STB        = P91_PTA11,		  /* BCAN_STB*/
	MCU_PIN92_DI_L_BCAN_ERR			= P92_PTA10,  		  /* BCAN_ERR*/
	MCU_PIN94_DO_HL_BCAN_EN        	= P94_PTE0,		  	  /* BCAN_EN*/
    MCU_PIN93_DO_H_T97_CRTL         = P93_PTE1,           /* T97电源控制*/
    MCU_PIN27_SPI0_CS_CRTL			= P27_PTB5,			  /* SPI0使能控制器*/
   	MCU_PIN70_SPI1_CS_CRTL			= P70_PTD3,			  /* SPI1使能控制器*/
   	MCU_PIN99_SPI2_CS_CRTL			= P99_PTA9,			  /* SPI2使能控制器*/
	MCU_PIM59_WK_TO_BT_CRTL 		= P59_PTE7,			  /* MCU_PIM59_WK_TO_BT*/
	MCU_PIN62_BLESTATE_CRTL			= P62_PTA17,		  /* 蓝牙连接状态*/

	MCU_PIN49_12V_TP_CTR			= P49_PTC13,		  /* STB-DV12V*/
	MCU_PIN80_DO_FL_DRIVE			= P80_PTC7,			  /* FL_DRIVE*/
	MCU_PIN81_DO_FR_DRIVE			= P81_PTC6,			  /* FR_DRIVE*/
	MCU_PIN76_BUMP_DRIVE_CTR 		= P76_PTB9,			  /* 保险杠*/
	MCU_PIN77_TRUNK_DRIVE_CTR		= P77_PTB8,		  	  /* 后备箱*/


} user_pin_defines;

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

/*************************************************************************************************
 * @function name:      ecual_pins_init
 *
 * @description:        板集所有pin脚初始化
 *
 * @parameters:         none
 *
 * @return:             0 is successful
 *************************************************************************************************/
status_t ecual_pins_init( ePinsConfigMode InitMode );

/*************************************************************************************************
 * Function Name:        ecual_PIN_output
 *
 * Description:          PIN脚输出电平
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *                       uint8_t value:               输出值  ( high or low )
 *
 * Output:               none
 *
 * Return:               none
 *
 *************************************************************************************************/
void ecual_PIN_output( user_pin_defines pinIndex, uint8_t value );

/*************************************************************************************************
 * Function Name:        ecual_PIN_get
 *
 * Description:          获取PIN脚输入电平
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *
 * Output:               none
 *
 * Return:               1 is high, 0 is low
 *
 *************************************************************************************************/
uint8_t ecual_PIN_get( user_pin_defines pinIndex );

/*************************************************************************************************
 * Function Name:        ecual_PIN_getpinsoutput
 *
 * Description:          获取输出引脚的电平状态
 *
 * Input:                user_pin_defines pinIndex:   PIN脚位
 *
 * Output:               none
 *
 * Return:               1 is high, 0 is low
 *
 *************************************************************************************************/
uint8_t ecual_PIN_getpinsoutput( user_pin_defines pinIndex );

/*************************************************************************************************
 * Function Name:        ecual_PIN_SetEnableFlag
 *
 * Description:          设置引脚使能标志
 *
 * Input:                [in] type : 配置的引脚模式结构体类型
 *					     [in] pin_index : 引脚索引号
 *						 [in] enable : 使能标志
 *
 * Output:               none
 *
 * Return:               true is success
 *
 *************************************************************************************************/
bool_t ecual_PIN_SetEnableFlag( ePinsConfigMode type, uint8_t pin_index, bool_t enable);

#endif /* ECUAL_PINS_H_ */
