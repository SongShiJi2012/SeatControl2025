/*
 * tim_driver.h
 *
 *  Created on: 2022-6-27
 *      Author: Administrator
 */

#ifndef TIM_DRIVER_H_
#define TIM_DRIVER_H_

#include "kf32a156.h"
#include <stdint.h>

#define GTIM_Type  GPTIM_SFRmap
#define BTIM_Type  BTIM_SFRmap
#define ATIM_Type  ATIM_SFRmap
#define TIM_IRQ_Type InterruptIndex

/*通用定时器*/
#define GTIM_INSTANCE_COUNT                     (8u)
#define GTIM0                                     (T0_SFR)
#define GTIM1                                     (T1_SFR)
#define GTIM2                                     (T2_SFR)
#define GTIM3                                     (T3_SFR)
#define GTIM4                                     (T4_SFR)
#define GTIM5                                     (T18_SFR)
#define GTIM6                                     (T19_SFR)
#define GTIM7                                     (T21_SFR)
#define GTIM_BASE_PTRS                            {GTIM0, GTIM1, GTIM2, GTIM3, GTIM4, GTIM5, GTIM6, GTIM7}
#define GTIM_IRQS                               {INT_T0, INT_T1, INT_T2, INT_T3, INT_T4, INT_T18, INT_T19, INT_T21}

/*基本定时器*/
#define BTIM_INSTANCE_COUNT                     (1u)
#define BTIM0                                     (T14_SFR)
#define BTIM_BASE_PTRS                            {BTIM0}
#define BTIM_IRQS 								  {INT_T14}

/*高级定时器  */
#define ATIM_INSTANCE_COUNT                     (2u)
#define ATIM0                                     (T5_SFR)
#define ATIM1                                     (T6_SFR)
#define ATIM_BASE_PTRS                            {ATIM0,ATIM1}
#define ATIM_IRQS 								  {INT_T5,INT_T6}


/*定时器序号*/
typedef enum
{
    TIM_NUM0 = 0x00U,   /*0*/
    TIM_NUM1,			 /*1*/
    TIM_NUM2,        /*2*/
    TIM_NUM3,
    TIM_NUM4,
    TIM_NUM5,
    TIM_NUM6,
    TIM_NUM7
} Time_number_t;


/*定时器类型  不建议使用高级定时器*/
typedef enum
{
    TIM_TYPE_GENER = 0x00U,   /*通用*/
    TIM_TYPE_BASE,			 /*基本*/
    TIM_TYPE_ADVANCED,        /*高级*/
    TIM_TYPE_COUNT
} Time_type_t;


/*目前只支持系统时钟和外部高速时钟*/
typedef enum
{
    TIM_SYSTEM_CLOCK = 0x00U,   /*系统时钟*/
    TIM_EXTHF_CLOCK, 		   /*外部高速系统*/
    TIM_LFCLK_CLOCK,
    TIM_T0INTLF_CLOCK,
    TIM_TCLOCK_COUNT
} Time_clk_source_t;


/*定时器周期 T= ((Prescaler+1)*TimeCnt)/clkSource*/
typedef struct
{
	Time_type_t          TimType;    /*定时器类型*/
	Time_number_t        TimIndex;   /*定时器序号*/
	Time_clk_source_t    clkSource;//时钟源
    uint16_t             Prescaler;//分频系数
    uint32_t             TimeCnt;//次数
    void (*callback)(void);    /*!< IRQ handler callback function. */
} Tim_user_config_t;


typedef void (*Tim_IRQ_callback_t)(void);


extern void TIM_GENER_DRV_Init(Tim_user_config_t* userConfigPtr);
extern void TIM_BASIC_DRV_Init(Tim_user_config_t* userConfigPtr);
extern void TIM_ADVANCED_DRV_Init(Tim_user_config_t* userConfigPtr);
extern void TIM_GENER_DRV_Disable(Time_number_t Count);
extern void TIM_GENER_DRV_Enable(Time_number_t Count);
extern void TIM_BASIC_DRV_Disable(Time_number_t Count);
extern void TIM_BASIC_DRV_Enable(Time_number_t Count);
extern void TIM_ADVANCED_DRV_Disable(Time_number_t Count);
extern void TIM_ADVANCED_DRV_Enable(Time_number_t Count);
extern void TIM_GENER_IRQClear(Time_number_t Count);
extern void TIM_BASIC_IRQClear(Time_number_t Count);
extern void TIM_ADVANCED_IRQClear(Time_number_t Count);

#endif /* TIM_DRIVER_H_ */
