/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_i2c.h
*
*  Description:  board IIC abstraction interface header file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-16
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/

#ifndef _ECUAL_I2C_H_
#define _ECUAL_I2C_H_

/*************************************************************************************************
 * Include files
 *************************************************************************************************/
#include "lpi2c_driver.h"
#include "types.h"
//#include "interrupt_manager.h"
//#include "osif_lock.h"
#include "ecual_common.h"
#include "stdlib.h"
//#include "osif_common.h"

#define I2C_ADDR_8BIT   1
#define I2C_ADDR_16BIT  2

#define I2C_PageSize 0x10
#define I2C_PageWriteTimeout 5//ms

typedef enum {
    LPI2C_0 = 0,
    LPI2C_1,
    
    MAX_I2CPORT
} E_IIC_PORT;

/**/
#define I2C_INTERFACE    LPI2C_0


/*****
 *   I2C娑擃厽鏌囧┃锟� */
typedef enum {
    /*  LPI2C  */
    INT_SOURCE_I2C_RXTX         = 0,
    INT_SOURCE_I2C_FIFO_ERROR,

    INT_SOURCE_I2C_MAX
} E_I2C_INT_SOURCE_INDEX;

typedef enum _e_i2c_status {
    eIICStatus_None             = 0,

    eIICStatus_Initialing,
    eIICStatus_Inited,
    eIICStatus_Deinitialing,

    eIICStatus_MAX
} E_I2C_STATUS;

typedef enum
{
	E_I2C_WRITE_STA_IDLE,
	E_I2C_WRITE_STA_START,
	E_I2C_WRITE_STA_WAIT,
	E_I2C_WRITE_STA_ERR
} E_I2C_WRITE_STATUS;

/*************************************************************************************************
 * Function define
 *************************************************************************************************/

/*************************************************************************************************
 * @function name:        ecual_I2C_init
 *
 * @description:          I2C濡�娼￠崚婵嗩瀶閸栵拷
 *
 * @parameters:           none
 *
 * @return:               true is successful
 *************************************************************************************************/
bool_t ecual_I2C_init( const uint8_t port, const uint32_t baudrate );

/*************************************************************************************************
 * @function name:        ecual_I2C_deinit
 *
 * @description:          I2C閸欏秴鍨垫慨瀣
 *
 * @parameters:           none
 *
 * @return:               true is successful
 *************************************************************************************************/
bool_t ecual_I2C_deinit( const uint8_t port );

/*************************************************************************************************
 * @function name:        ecual_I2C_getStatus
 *
 * @description:          閼惧嘲褰囪ぐ鎾冲I2C閸掓繂顬婇崠鏍Ц閹拷[娴犲懎鐤勯悳鐧縜ster]
 *
 * @parameters:           none
 *
 * @return:               true is successful
 *************************************************************************************************/
bool_t ecual_I2C_getStatus( void );

/*****************************************************************************
** Function:    ecual_I2C_installcallback
** Description: 鐠佸墽鐤咺2C閸ョ偠鐨熼崙鑺ユ殶
** Parameter:   
** Return:      void
******************************************************************************/
void ecual_I2C_installcallback( const uint8_t port, i2c_master_callback_t masterCallback, void *callbackParam);

/*****************************************************************************
** Function:    i2c_write
** Description: i2c閸愶拷
** Parameter:   int port,uint8_t dev_address,uint16_t reg_address,uint8_t ra_size,const uint8_t * buffer,uint16_t size
** Return:      void
******************************************************************************/
uint16_t ecual_I2C_write( const uint8_t port,
                          uint16_t reg_address,
                          const uint8_t* buffer,
                          uint16_t size
                          );

/*****************************************************************************
** Function:    i2c_read
** Description: i2c鐠囷拷
** Parameter:   int port,uint8_t dev_address,uint8_t ra_size,uint8_t * buffer,uint16_t size
** Return:      int
******************************************************************************/
uint16_t ecual_I2C_read( const uint8_t port,
                         uint16_t reg_address,
                         uint8_t* buffer,
                         uint16_t size
                         );

/*************************************************************************************************
 * @function Name:        ecual_I2C_setIntSource
 *
 * @description:          鐠佸墽鐤咺2C閻╃鍙ф稉顓熸焽濠ф劘銆冪粈鍝勶拷
 *
 * @note:
 *
 * @parameters:           none
 *
 * @return:               none
 *************************************************************************************************/
bool_t ecual_I2C_setIntSource( const E_I2C_INT_SOURCE_INDEX index );

/*************************************************************************************************
 * @function name:      ecual_I2C_clrIntSource
 *
 * @description:        濞撳懘娅嶪2C娑擃厽鏌囧┃鎰�缁�搫锟�
 *
 * @note:
 *
 * @parameters:         none
 *
 * @return:             none
 *************************************************************************************************/
bool_t ecual_I2C_clrIntSource( const E_I2C_INT_SOURCE_INDEX index );

/*************************************************************************************************
 * @function name:      ecual_I2C_IntControl
 *
 * @description:        I2C閻╃鍙ф稉顓熸焽閹貉冨煑
 *
 * @note:
 *
 * @parameters:         none
 *
 * @return:             none
 *************************************************************************************************/
bool_t ecual_I2C_IntControl( const E_I2C_INT_SOURCE_INDEX index, const bool_t enable );

#endif /* _ECUAL_I2C_H_ */
