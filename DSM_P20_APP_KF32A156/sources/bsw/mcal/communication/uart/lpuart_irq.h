#ifndef LPUART_IRQ_H__
#define LPUART_IRQ_H__

#include <stdint.h>
#include "lpuart_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void LPUART_DRV_IRQHandler(uint32_t instance);

/*******************************************************************************
 *  Default interrupt handlers signatures
 ******************************************************************************/

#if (LPUART_INSTANCE_COUNT > 0U)
/*! @brief LPUART0 interrupt handler. */
void LPUART0_IrqHandler(void);
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
/*! @brief LPUART1 interrupt handler. */
void LPUART1_IrqHandler(void);
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
/*! @brief LPUART2 interrupt handler. */
void LPUART2_IrqHandler(void);
#endif


#endif /* LPUART_IRQ_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
