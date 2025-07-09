/*************************************************************************************************
 *  Copyright (c) 2019, ancle.co.
 *  All rights reserved.
 *
 *  FileName:     ecual_common.h
 *
 *  Description:  ecu layer common define
 *
 *  FileVersion:  V1.00
 *
 *  Date:         2019-03-15
 *
 *  Author:       ancle
 *
 *  Note:         1. New Create;
 *************************************************************************************************/

#ifndef _ECUAL_COMMON_H_
#define _ECUAL_COMMON_H_

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
//#include "osif_common.h"

/*************************************************************************************************
 * Macro define
 *************************************************************************************************/

#define INT_PRIORITY_CAN_ERR        ( 5u )
#define INT_PRIORITY_CAN_ORED       ( 5u )
#define INT_PRIORITY_CAN_MB015      ( 6u )
#define INT_PRIORITY_CAN_MB1631     ( 6u )

#define INT_PRIORITY_FLEXIOUART     ( 9u )
#define INT_PRIORITY_PORTIO         ( 9u )

#define INT_PRIORITY_FTM_IC         ( 9u )

#define INT_PRIORITY_I2C            ( 9u )
#define INT_PRIORITY_SPI_MPU        ( 7u )  /* Slave DMA Interrupt*/

#define INT_PRIORITY_UART_MPU       ( 9u )
#define INT_PRIORITY_UART_BLE       ( 8u )
#define INT_PRIORITY_UART_ATE       ( 10u )


typedef enum
{
	OPT_STATE_SUCCESS     = 0x0,
	OPT_STATE_FAILED      = 0x1,
	OPT_STATE_UNSUPPORTED = 0x2,
	OPT_STATE_TX_BUFFER_FULL = 0x03,
	OPT_STATE_PARAM_INVALID = 0x04,
	OPT_STATE_MAX
}OptState_t;

/***
 *  0:娴ｈ法鏁ゆ稉顓熸焽閺傜懓绱� 1:娴ｈ法鏁MA閺傜懓绱�
 */
#define SPI_USE_DMA     ( 1u )



#endif /* _ECUAL_COMMON_H_ */

/*************************************************************************************************
 * End of Line
 *************************************************************************************************/
