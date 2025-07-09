/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               Drv_lpspi.h
** Last modified Date:      2017.12.15
** Last Version:            V1.0.0
** Description:             Driver lpspi header file
**
**------------------------------------------------------------------------------------------
** Created By:              Michael Xin
** Created date:            2017.12.15
** Version:                 V1.0.0
** Descriptions:            Driver lpspi header file
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#ifndef __DRV_LPSPI_H__
#define __DRV_LPSPI_H__


/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "pins_driver.h"
#include "Common.h"


/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/
#define		D_SPITIMEOUT					(10U)


/*UJA1078和L99MD02 软件模拟SPI管脚定义*/
#if 0
#define		D_PIN_UJA1078_CS_GPIO			(PTB)
#define		D_PIN_UJA1078_CS_NUM			(5U)

#define		D_PIN_L99MD02_CS_GPIO			(PTC)
#define		D_PIN_L99MD02_CS_NUM			(3U)

#define		D_PIN_SPI_CLK_GPIO				(PTD)
#define		D_PIN_SPI_CLK_NUM				(15U)

#define		D_PIN_SPI_SDO_GPIO				(PTD)
#define		D_PIN_SPI_SDO_NUM				(16U)

#define		D_PIN_SPI_SDI_GPIO				(PTB)
#define		D_PIN_SPI_SDI_NUM				(4U)
#endif

#define		D_PIN_UJA1078_CS_GPIO			(GPIOA_SFR)
#define		D_PIN_UJA1078_CS_NUM			(1U)

#define		D_PIN_L99MD02_CS_GPIO			(GPIOD_SFR)
#define		D_PIN_L99MD02_CS_NUM			(15U)

#define		D_PIN_SPI_CLK_GPIO				(GPIOD_SFR)
#define		D_PIN_SPI_CLK_NUM				(14U)

#define		D_PIN_SPI_SDO_GPIO				(GPIOA_SFR)
#define		D_PIN_SPI_SDO_NUM				(2U)

#define		D_PIN_SPI_SDI_GPIO				(GPIOH_SFR)
#define		D_PIN_SPI_SDI_NUM				(1U)




#define	UJA1078_CS_ACTIVE()				PINS_DRV_WritePin(D_PIN_UJA1078_CS_GPIO, D_PIN_UJA1078_CS_NUM, D_LOW)
#define	UJA1078_CS_INACTIVE()			PINS_DRV_WritePin(D_PIN_UJA1078_CS_GPIO, D_PIN_UJA1078_CS_NUM, D_HIGH)

#define	L99MD02_CS_ACTIVE()				PINS_DRV_WritePin(D_PIN_L99MD02_CS_GPIO, D_PIN_L99MD02_CS_NUM, D_LOW)
#define	L99MD02_CS_INACTIVE()			PINS_DRV_WritePin(D_PIN_L99MD02_CS_GPIO, D_PIN_L99MD02_CS_NUM, D_HIGH)

#define	SPI_CLK_HIGH()					PINS_DRV_WritePin(D_PIN_SPI_CLK_GPIO, D_PIN_SPI_CLK_NUM, D_HIGH)
#define	SPI_CLK_LOW()					PINS_DRV_WritePin(D_PIN_SPI_CLK_GPIO, D_PIN_SPI_CLK_NUM, D_LOW)

#define	SPI_SDO_HIGH()					PINS_DRV_WritePin(D_PIN_SPI_SDO_GPIO, D_PIN_SPI_SDO_NUM, D_HIGH)
#define	SPI_SDO_LOW()					PINS_DRV_WritePin(D_PIN_SPI_SDO_GPIO, D_PIN_SPI_SDO_NUM, D_LOW)


/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/
typedef enum
{
    en_LpSpi_UJA1078 = 0U,
    en_LpSpi_L99MD02,

	
    en_LpSpiChannelMax
} EN_LpSpiChannel;



/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/

/*
**********************************************************************************************************
					FUNCTIONS
**********************************************************************************************************
*/
extern INT8U LpSpiInit(EN_LpSpiChannel eSpiChannel);
extern BOOL LpSpiSendData(EN_LpSpiChannel eSpiChl, INT8U *WrData, INT8U *RdData, INT8U Len);
extern BOOL LpSpiSendData_U16(EN_LpSpiChannel eSpiChl, INT16U	 *Data);
extern BOOL LpSpiSendData_Array(EN_LpSpiChannel eSpiChl, INT8U *pData, INT8U Len);



#endif /* __DRV_LPSPI_H__ */

