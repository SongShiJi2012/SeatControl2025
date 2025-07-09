/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               Drv_lpspi.c
** Last modified Date:      2018.04.09
** Last Version:            V1.1.0
** Description:
**
**------------------------------------------------------------------------------------------
** Created By:              HaiBin Cai 蔡海斌
** Created date:            2017.12.15
** Version:                 V1.0.0
** Descriptions:
**
**------------------------------------------------------------------------------------------
** Modified By:             HaiBin Cai 蔡海斌
** Modified date:           2018.04.09
** Version:                 V1.1.0
** Description:
**
********************************************************************************************/

/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "Drv_lpspi.h"
#include "kf32a156.h"
#include "system_init.h"
/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/


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

#if 0
static void LpSPI_Dly(INT8U cnt)
{
	INT8U   Index;

	for(Index = 0x00; Index < cnt; Index++)
	{
		
	}
}
#else
#define  LpSPI_Dly(x)  systick_delay_us(x)
#endif

//函数名 变量名尽量不用缩写
/*
**********************************************************************************************************
* Function Name : LpSpiInit
* Description   : 初始化LpSpiInit
* Date          : 2017/12/22
* Parameter     : EN_LpSpiChannel eSpiChannel
*				：
* Return Code   : Error ID
* Author        : Michael Xin
**********************************************************************************************************
*/
INT8U LpSpiInit(EN_LpSpiChannel eSpiChannel)
{
	/* Initialize LPSPI*/
//	UJA1078_CS_INACTIVE();
//	L99MD02_CS_INACTIVE();
	return D_Ok;
}


/*-------------------------------------------------------------------------
* Function Name : LpSpiSendData
* Description   : 模拟SPI
* Date          : 2019/March/25
* Parameter     :
* Return Code   :
* Author        : 模拟spi模式0
-------------------------------------------------------------------------*/
#if 1
BOOL LpSpiSendData(EN_LpSpiChannel eSpiChl, INT8U *WrData, INT8U *RdData, INT8U Len)
{
	INT8U		i, j;
	INT8U		TempLen = Len;
	INT8U		Mask = 0x80;
	INT32U		TempIOData = 0;

	if(eSpiChl >= en_LpSpiChannelMax)
	{
		return FALSE;
	}
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_ACTIVE();
	}
	else
	{
		L99MD02_CS_ACTIVE();
	}
	SPI_SDO_HIGH();
	LpSPI_Dly(5);
	for(i = 0x00; i < TempLen; i++)
	{
		for(j = 0;j<8;j++)
		{
			SPI_CLK_LOW();
			LpSPI_Dly(1);
			if((WrData[i] & Mask) != 0u)
			{
				SPI_SDO_HIGH();
			}
			else
			{
				SPI_SDO_LOW();
			}
			
			SPI_CLK_HIGH();
			LpSPI_Dly(1);
			

			TempIOData = PINS_DRV_ReadPins(D_PIN_SPI_SDI_GPIO);
			if((TempIOData & (1ul << D_PIN_SPI_SDI_NUM)) != 0u)
			{
				RdData[i] |= Mask;
			}
			else
			{
				RdData[i] &= (~Mask);
			}
			Mask >>= 1;
			if(Mask == 0x00)
			{
				Mask = 0x80;
			}
		}
	}
	SPI_CLK_LOW();
	SPI_SDO_LOW();
	LpSPI_Dly(2);
	SPI_SDO_HIGH();
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_INACTIVE();
	}
	else
	{
		L99MD02_CS_INACTIVE();
	}
	return TRUE;
}
#endif
#if 0
//模拟spi模式1，SBC OK 后视镜不行
BOOL LpSpiSendData(EN_LpSpiChannel eSpiChl, INT8U *WrData, INT8U *RdData, INT8U Len)
{
	INT8U		i, j;
	INT8U		TempLen = Len;
	INT8U		Mask = 0x80;
	INT32U		TempIOData = 0;

	if(eSpiChl >= en_LpSpiChannelMax)
	{
		return FALSE;
	}
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_ACTIVE();
	}
	else
	{
		L99MD02_CS_ACTIVE();
	}
	SPI_SDO_HIGH();
	LpSPI_Dly(5);
	for(i = 0x00; i < TempLen; i++)
	{
		for(j = 0;j<8;j++)
		{
			SPI_CLK_HIGH();
			LpSPI_Dly(1);
			if((WrData[i] & Mask) != 0u)
			{
				SPI_SDO_HIGH();
			}
			else
			{
				SPI_SDO_LOW();
			}

			SPI_CLK_LOW();
			LpSPI_Dly(1);

			TempIOData = PINS_DRV_ReadPins(D_PIN_SPI_SDI_GPIO);
			if((TempIOData & (1ul << D_PIN_SPI_SDI_NUM)) != 0u)
			{
				RdData[i] |= Mask;
			}
			else
			{
				RdData[i] &= (~Mask);
			}
			Mask >>= 1;
			if(Mask == 0x00)
			{
				Mask = 0x80;
			}
		}
	}
	SPI_CLK_LOW();
	SPI_SDO_LOW();
	LpSPI_Dly(2);
	SPI_SDO_HIGH();
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_INACTIVE();
	}
	else
	{
		L99MD02_CS_INACTIVE();
	}
	return TRUE;
}
#endif
#if 0
//SBC模拟spi模式1，后视镜模拟spi模式0
BOOL LpSpiSendData(EN_LpSpiChannel eSpiChl, INT8U *WrData, INT8U *RdData, INT8U Len)
{
	INT8U		i, j;
	INT8U		TempLen = Len;
	INT8U		Mask = 0x80;
	INT32U		TempIOData = 0;

	if(eSpiChl >= en_LpSpiChannelMax)
	{
		return FALSE;
	}
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_ACTIVE();
	}
	else
	{
		L99MD02_CS_ACTIVE();
	}
	SPI_SDO_HIGH();
	LpSPI_Dly(5);
	if(eSpiChl == en_LpSpi_UJA1078)
	{
		for(i = 0x00; i < TempLen; i++)
		{
			for(j = 0;j<8;j++)
			{
				SPI_CLK_HIGH();
				LpSPI_Dly(1);
				if((WrData[i] & Mask) != 0u)
				{
					SPI_SDO_HIGH();
				}
				else
				{
					SPI_SDO_LOW();
				}

				SPI_CLK_LOW();
				LpSPI_Dly(1);

				TempIOData = PINS_DRV_ReadPins(D_PIN_SPI_SDI_GPIO);
				if((TempIOData & (1ul << D_PIN_SPI_SDI_NUM)) != 0u)
				{
					RdData[i] |= Mask;
				}
				else
				{
					RdData[i] &= (~Mask);
				}
				Mask >>= 1;
				if(Mask == 0x00)
				{
					Mask = 0x80;
				}
			}
		}
	}
	else
	{
		SPI_SDO_HIGH();
		LpSPI_Dly(5);
		for(i = 0x00; i < TempLen; i++)
		{
			for(j = 0;j<8;j++)
			{
				SPI_CLK_LOW();
				LpSPI_Dly(1);
				if((WrData[i] & Mask) != 0u)
				{
					SPI_SDO_HIGH();
				}
				else
				{
					SPI_SDO_LOW();
				}

				SPI_CLK_HIGH();
				LpSPI_Dly(1);


				TempIOData = PINS_DRV_ReadPins(D_PIN_SPI_SDI_GPIO);
				if((TempIOData & (1ul << D_PIN_SPI_SDI_NUM)) != 0u)
				{
					RdData[i] |= Mask;
				}
				else
				{
					RdData[i] &= (~Mask);
				}
				Mask >>= 1;
				if(Mask == 0x00)
				{
					Mask = 0x80;
				}
			}
		}
	}
	SPI_CLK_LOW();
	SPI_SDO_LOW();
	LpSPI_Dly(2);
	SPI_SDO_HIGH();

	if(eSpiChl == en_LpSpi_UJA1078)
	{
		UJA1078_CS_INACTIVE();
	}
	else
	{
		L99MD02_CS_INACTIVE();
	}
	return TRUE;
}
#endif


/**********************************************************************************************************
* Function Name : LpSpiSendReadData
* Description   : 发送U8类型SPI
* Date          : 2017/12/22
* Parameter     : EN_LpSpiChannel eSpiChl :通道, INT32U Data
* Return Code   : BOOL
* Author        : Michael Xin
**********************************************************************************************************/
BOOL LpSpiSendReadData(EN_LpSpiChannel eSpiChl,INT32U WriteData,INT32U *ReadData)
{
	INT32U	TempData = WriteData;
#if 0
    
	/* Waiting for the sending buffer to be empty */
	while (SPI_Get_Transmit_Buf_Flag(SPI2_SFR));
	/* Polling to send string  */
	SPI_I2S_SendData32(SPI2_SFR, TempData);
	/* Waiting to accept that the buffer is not empty */
	while (!SPI_Get_Receive_Buf_Flag(SPI2_SFR));
	/* Read the received data */
	*ReadData = SPI_I2S_ReceiveData(SPI2_SFR);
#else
	/* Waiting for the sending buffer to be empty */
	while (SPI_Get_Transmit_Buf_Flag(SPI0_SFR));
	/* Polling to send string  */
	SPI_I2S_SendData32(SPI0_SFR, TempData);
	/* Waiting to accept that the buffer is not empty */
	while (!SPI_Get_Receive_Buf_Flag(SPI0_SFR));
	/* Read the received data */
	*ReadData = SPI_I2S_ReceiveData(SPI0_SFR);
#endif
	return TRUE;
}

/*
**********************************************************************************************************
* Function Name : LpSpiSendData_U16
* Description   : 发送U16类型SPI
* Date          : 2017/12/22
* Parameter     : EN_LpSpiChannel eSpiChl :通道, INT32U Data
* Return Code   : BOOL
* Author        : Michael Xin
**********************************************************************************************************
*/
BOOL LpSpiSendData_U16(EN_LpSpiChannel eSpiChl, INT16U	 *Data)
{
#if 1
        return TRUE;
#elif 0
	INT32U	TempData = *Data;
	UJA1078_CS_ACTIVE();
	/* Waiting for the sending buffer to be empty */
	while (SPI_Get_Transmit_Buf_Flag(SPI0_SFR));
	/* Polling to send string  */
	SPI_I2S_SendData32(SPI0_SFR, TempData);
	/* Waiting to accept that the buffer is not empty */
	while (!SPI_Get_Receive_Buf_Flag(SPI0_SFR));
	/* Read the received data */
	*Data = SPI_I2S_ReceiveData(SPI0_SFR);
	UJA1078_CS_INACTIVE();
	return TRUE;
#else
	BOOL	ret = FALSE;
	INT8U 	i = 0;
	INT8U 	RdData[8] = {0};
	INT8U 	WrData[8] = {0};
	INT16U	TempData = *Data;

	WrData[0] = (INT8U)(TempData >> 8);
	WrData[1] = (INT8U)(TempData);

	if(TRUE == LpSpiSendData(eSpiChl, &WrData[0], &RdData[0], 2))
	{
		ret = TRUE;
		*Data = 0;
		for(i = 0; i < 2; i++)
		{
			*Data <<= 8;
			*Data |= RdData[i];
		}
	}

	return ret;
#endif
}


/*-------------------------------------------------------------------------
* Function Name : LpSpiSendData_Array
* Description   : 发送数组SPI
* Date          : 2019/March/25
* Parameter     : EN_LpSpiChannel eSpiChl:通道号, INT8U *pData:数组, INT8U Len:长度
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
BOOL LpSpiSendData_Array(EN_LpSpiChannel eSpiChl, INT8U *pData, INT8U Len)
{
	BOOL	ret = FALSE;
	INT8U 	RdData[8] = {0};
	if((NULL == pData) || (0 == Len) || (8 < Len))
	{
		return ret;
	}
	if(TRUE == LpSpiSendData(eSpiChl, &pData[0], &RdData[0], Len))
	{
		ret = TRUE;
	}

	return ret;
}


