/****************************************************************************************
 *
 * File Name: kf_it.c
 * Project Name: C52X_APP
 * Version: v1.0
 * Date: 2022-08-30- 15:41:53
 * Author: Administrator
 * 
 ****************************************************************************************/
//#include<KF32A156MQV.h>

//asm(".include		\"KF32A156MQV.inc\"	");	 
#include <Mcal_Lin.h>
#include "CpuPeripheralInit.h"
#include "kf32a156_gtim.h"
#include "kf32a156_atim.h"
#include "flexcan_driver.h"
#include "tim_driver.h"
#include "ecual_tim.h"
#include "kf32a156_dma.h"
#include "Ecual_Adc.h"
#include "Test.h"
#include "Cdd_Hall.h"
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
#if D_TEST_TIMER_SW
void __attribute__((interrupt))_T21_exception (void)
{
	ecual_Tim_IRQHandler(TIM_TYPE_GENER,TIM_NUM7);
}
#endif
/*****************************************************************************************
                              FlexCAN7_exception Course
*****************************************************************************************/
void __attribute__((interrupt)) _CANFD6_exception (void)
{
	FLEXCAN_IRQHandler(0);
}

//*****************************************************************************************
//                              T5 Interrupt Course
//*****************************************************************************************
void __attribute__((interrupt)) _T5_exception(void)
{
    if (0 != ATIM_X_Get_Overflow_INT_Flag(ECCP5_SFR))
    {
        /* Clear interrupt flag  */
        ATIM_X_Clear_Overflow_INT_Flag(ECCP5_SFR);
    }
    else
    {
    }
}
void __attribute__((interrupt)) _USART1_exception (void)
{
	Drv_LinIRQHandler(1);
}


/***********************************************************************************************
 * @function name:  _DMA0_exception
 * @description:    DMA0�жϷ����������DMA0ͨ��5���ݰ�������жϣ�����жϱ�־��
 *                  ����ADC0���ݸ��±�־
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void __attribute__((interrupt)) _DMA0_exception(void)
{
	 /* ����ADC�������ݾ���DMA������� ************************************/
	if(DMA_Get_Finish_Transfer_INT_Flag(DMA0_SFR, DMA_CHANNEL_5))
	{
		DMA_Clear_INT_Flag(DMA0_SFR, DMA_CHANNEL_5, DMA_INT_FINISH_TRANSFER);
		Ecual_SetDma0_Adc0_UpdateFlag(TRUE);
	}
}

/***********************************************************************************************
 * @function name:  _DMA1_exception
 * @description:    DMA1�жϷ����������DMA1ͨ��5��ͨ��7���ݰ�������жϣ�����жϱ�־��
 *                  �ֱ�����ADC1��ADC2���ݸ��±�־�����������ѯ��
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void __attribute__((interrupt)) _DMA1_exception(void)
{
	 /* ����ADC�������ݾ���DMA������� ************************************/
    if(DMA_Get_Finish_Transfer_INT_Flag(DMA1_SFR, DMA_CHANNEL_5))
    {
        DMA_Clear_INT_Flag(DMA1_SFR, DMA_CHANNEL_5, DMA_INT_FINISH_TRANSFER);
    	Ecual_SetDma1_Adc1_UpdateFlag(TRUE);
    }
    if(DMA_Get_Finish_Transfer_INT_Flag(DMA1_SFR, DMA_CHANNEL_7))
    {
        DMA_Clear_INT_Flag(DMA1_SFR, DMA_CHANNEL_7, DMA_INT_FINISH_TRANSFER);
    	Ecual_SetDma1_Adc2_UpdateFlag(TRUE);
    }

}
