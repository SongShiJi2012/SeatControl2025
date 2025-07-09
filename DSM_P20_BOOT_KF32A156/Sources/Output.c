/********************Copyright (c) Fuxin Dare Automotive Parts Co.LTD.*********************
** File Name:               Output.c
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
#include "Output.h"
//#include "pin_mux.h"
#include "watchdog.h"
#include "pins_driver.h"

/****************************************************************
* �������ƣ�void Output_FeedWatchDog(void)
* ����������ι��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע��
****************************************************************/
void Output_FeedWatchDog(void)
{
	WDOG_Feed();
	PINS_DRV_TogglePin(FeedWatchDog_GPIO,FeedWatchDog_PINNUM);
}


