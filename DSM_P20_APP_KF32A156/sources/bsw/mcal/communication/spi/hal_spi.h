

/**************************************************************
 * Author:			 JeanYuan
 * Copyright (c) 2013-2019 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved. 
 *	generated :2020-09-17
 **************************************************************/

#ifndef HAL_SPI_H
#define HAL_SPI_H

//#include "lpspi_master_driver.h"
#include "ecual_common.h"
#include "types.h"


typedef enum
{
	COMM_SPI_0 = 0x00,
	COMM_SPI_1,
	COMM_SPI_2,
	COMM_SPI_MAX
}SpiCommChannel_t;


typedef enum
{
    SPI_USING_DMA         = 0,    /*!< The driver will use DMA to perform SPI transfer */
    SPI_USING_INTERRUPTS,         /*!< The driver will use interrupts to perform SPI transfer */
    SPI_USING_POLLING,
    SPI_USING_SIMULATE,			  /*Ä£ÄâSPI*/
    SPI_USING_MAX
}SpiTransferyType_t;

typedef struct
{
	UINT32 BaudRate;
	SpiTransferyType_t	TransferType;
}SpiParamConf_t;

OptState_t Hal_SpiInit(SpiCommChannel_t uChannel,SpiParamConf_t *uParam);
OptState_t Hal_SpiDeInit(SpiCommChannel_t uChannel);
UINT32 Hal_SpiWrite(SpiCommChannel_t uChannel,UINT8 *uBuffer,UINT16 uLength);
UINT32 Hal_SpiRead(SpiCommChannel_t uChannel,UINT8 *uBuffer,UINT16 uLength);
UINT32 Hal_SpiTransfer(SpiCommChannel_t uChannel,UINT8 *uSendBuffer,UINT8 *uReadBuffer,UINT16 uLength);
void Hal_SpiInitEx(void);






#endif

