/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_uart.h
*
*  Description:  board UART abstraction interface header file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-15
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/

#ifndef _ECUAL_UART_H_
#define _ECUAL_UART_H_

//#include "osif_lock.h"
#include "ecual_common.h"
#include "callbacks.h"
#include "types.h"

/*************************************************************************************************
 * Macro define
 *************************************************************************************************/
enum {
	HW_UART_0 = 0,
	HW_UART_1,
	HW_UART_2,
	
	MAX_UART_NUM
};

//#define BLE_INTERFACE        HW_UART_2
#define LIN_INTERFACE        HW_UART_0


#define UartLockWait( port )          LockWait( UartBits(port) )
#define UartLockSet( port )           LockSet( UartBits(port) )
#define UartISRLockSet( port )        ISRLockSet( UartBits(port) )

/*************************************************************************************************
 * Function define
 *************************************************************************************************/
bool_t ecual_UART_init( const uint8_t port,
                        uart_callback_t pfnTxCB,
                        uart_callback_t pfnRxCB
                        );

bool_t ecual_UART_deinit( const uint8_t port );
int8_t ecual_UART_getc( const uint8_t port);
bool_t ecual_UART_puts( const uint8_t port, const uint8_pt buffer, const uint32_t size );
#endif /* _ECUAL_UART_H_ */
