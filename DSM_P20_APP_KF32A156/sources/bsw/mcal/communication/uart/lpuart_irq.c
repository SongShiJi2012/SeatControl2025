/*******************************************************************************
 *  $File Name$       : lpuart_irq.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/

#include "lpuart_irq.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (LPUART_INSTANCE_COUNT > 0U)
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART0_IrqHandler
 * Description   : LPUART0 interrupt handler
 *
 *END**************************************************************************/
void LPUART0_IrqHandler(void)
{
    LPUART_DRV_IRQHandler(0);
}
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_IrqHandler
 * Description   : LPUART1 interrupt handler
 *
 *END**************************************************************************/
void LPUART1_IrqHandler(void)
{
    LPUART_DRV_IRQHandler(1);
}
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART2_IrqHandler
 * Description   : LPUART2 interrupt handler
 *
 *END**************************************************************************/
void LPUART2_IrqHandler(void)
{
    LPUART_DRV_IRQHandler(2);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
