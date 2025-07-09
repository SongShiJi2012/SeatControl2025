/*******************************************************************************
 *  $File Name$       : lpspi_irq.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef LPSPI_IRQ_H
#define LPSPI_IRQ_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "lpspi_master_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#if (LPSPI_INSTANCE_COUNT > 0U)
/*! @brief LPSPI0 interrupt handler. */
void LPSPI0_DRV_IRQHandler(void);
#endif
#if (LPSPI_INSTANCE_COUNT > 1U)
/*! @brief LPSPI1 interrupt handler. */
void LPSPI1_DRV_IRQHandler(void);
#endif

#if (LPSPI_INSTANCE_COUNT > 2U)
/*! @brief LPSPI2 interrupt handler. */
void LPSPI2_DRV_IRQHandler(void);
#endif

#endif /* LPSPI_IRQ_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
