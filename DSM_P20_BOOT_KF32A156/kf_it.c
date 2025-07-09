/****************************************************************************************
 *
 * File Name: kf_it.c
 * Project Name: C52X_BOOT
 * Version: v1.0
 * Date: 2022-09-30- 11:26:36
 * Author: Administrator
 * 
 ****************************************************************************************/
//#include<KF32A156MQV.h>
#include "CpuPeripheralInit.h"
#include "kf32a156_gtim.h"
#include "kf32a156_atim.h"
#include "flexcan_driver.h"
#include "tim_driver.h"
#include "ecual_tim.h"
//asm(".include		\"KF32A156MQV.inc\"	");	 

//Note:
//*****************************************************************************************
//                                 NMI Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _NMI_exception (void);
void __attribute__((interrupt)) _NMI_exception (void)
{	

}

//*****************************************************************************************
//                               HardFault Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _HardFault_exception (void);
void __attribute__((interrupt)) _HardFault_exception (void)
{

}

//*****************************************************************************************
//                               StackFault Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _StackFault_exception (void);
void __attribute__((interrupt)) _StackFault_exception (void)
{

}

//*****************************************************************************************
//                               AriFault Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _AriFault_exception (void);
void __attribute__((interrupt)) _AriFault_exception (void)
{

}

//*****************************************************************************************
//                               SVC Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _SVC_exception (void);
void __attribute__((interrupt)) _SVC_exception (void)
{

}

//*****************************************************************************************
//                              SoftSV Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _SoftSV_exception (void);
void __attribute__((interrupt)) _SoftSV_exception (void)
{

}

//*****************************************************************************************
//                              SysTick Interrupt Course
//*****************************************************************************************	
void __attribute__((interrupt)) _SysTick_exception (void);
void __attribute__((interrupt)) _SysTick_exception (void)
{
	
}

//*****************************************************************************************
//                              T18 Interrupt Course
//*****************************************************************************************
void __attribute__((interrupt))_T2_exception (void)
{
	ecual_Tim_IRQHandler(TIM_TYPE_GENER,TIM_NUM2);
}

/*****************************************************************************************
                              FlexCAN7_exception Course
*****************************************************************************************/
void __attribute__((interrupt)) _CANFD6_exception (void)
{
	FLEXCAN_IRQHandler(0);
}

