/********************Copyright (c) Fuxin Dare Automotive Parts Co.LTD.*********************
** File Name:               Output.h
** Author:           	  Feliks.Peng
** Date:            		  2017.07.24
** Version:                  V1.0
** Descriptions:           Low-side and High-side switches
** Note:			  	  

** History Modify 	  
** Modified By:      	     
** Modified date:                      
** Modification:		  
**********************************************************************************/
#ifndef _OUTPUT_H
#define _OUTPUT_H
#include  "Common.h"
#include "pins_driver.h"

#define OUTPUT_LOW			(0u)
#define OUTPUT_HIGH			(1u)

/*WatchDog GPIO-PIN*/
/*PTA9 feed watchdog*/
#define FeedWatchDog_GPIO			(GPIOE_SFR)
#define FeedWatchDog_PINNUM			(10u)

/*座椅霍尔传感器/HSD3(预留) U19*/
#define		D_PIN_PWR_12V_GPIO				(GPIOE_SFR)
#define		D_PIN_PWR_12V_NUM				(2U)

/*内部+12V控制 */
#define	PWR_12V_ON()			PINS_DRV_WritePin(D_PIN_PWR_12V_GPIO, D_PIN_PWR_12V_NUM, D_ON)
#define	PWR_12V_OFF()			PINS_DRV_WritePin(D_PIN_PWR_12V_GPIO, D_PIN_PWR_12V_NUM, D_OFF)


#define		D_PIN_PWR_LDO1_5V_GPIO			(GPIOA_SFR)
#define		D_PIN_PWR_LDO1_5V_NUM			(6U)

/*LDO1 +5V供电控制*/
#define	PWR_LDO1_5V_ON()			PINS_DRV_WritePin(D_PIN_PWR_LDO1_5V_GPIO, D_PIN_PWR_LDO1_5V_NUM, D_ON)
#define	PWR_LDO1_5V_OFF()			PINS_DRV_WritePin(D_PIN_PWR_LDO1_5V_GPIO, D_PIN_PWR_LDO1_5V_NUM, D_OFF)

void Output_FeedWatchDog(void);

#endif

