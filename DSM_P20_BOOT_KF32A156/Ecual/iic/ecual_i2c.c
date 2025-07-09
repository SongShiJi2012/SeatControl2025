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


/*************************************************************************************************
 * Include files
 *************************************************************************************************/
#include "ecual_i2c.h"
#include "lpi2c_driver.h"
#include "kf32a156_int.h"
#include "pins_driver.h"
#include "callbacks.h"
#include <string.h>
#include "system_init.h"
#include "CpuPeripheralInit.h"
/*************************************************************************************************
 * Variable define
 *************************************************************************************************/

static lpi2c_master_state_t s_lpi2c1MasterState;

static E_I2C_WRITE_STATUS s_writeStates = E_I2C_WRITE_STA_IDLE;

/*************************************************************************************************
 * @function Name:        ecual_I2C_init
 *
 * @description:          I2C婵犵數濮烽。钘壩ｉ崨鏉戝瀭妞ゅ繐鐗婇弲鎼佹煢濡警妾抽柣鎺嶇矙閺屻劑鎮㈤崫鍕戙垻绱掗敓鑺ヮ棯缂佺粯绻堝Λ鍐ㄢ槈濞嗘瑧绀婇梻浣筋嚙妤犳悂鎮ユ總绋胯摕婵炴垯鍨归崘锟芥煕椤垵浜滄い蹇ユ嫹
 *
 * @parameters:           none
 *
 * @return:               true is successful
 *
 * @describe:             濞夈垻澹掗悳鍥╃搼娴滐拷 baudrate = SCLK / (BaudRateH + BaudRateL) 閻╊喖澧犳禒鍛暜閹革拷50K 500k 1M
 *************************************************************************************************/
bool_t ecual_I2C_init( const uint8_t port, const uint32_t baudrate )
{
	   lpi2c_master_user_config_t lpi2c1_MasterConfig0 = {
		   .slaveAddress = 1U,
		   .is10bitAddr = true,
		   .operatingMode = LPI2C_STANDARD_MODE,
		   .baudRate = baudrate,
		   .transferType = LPI2C_USING_INTERRUPTS,
		   .dmaChannel = 0U,
		   .masterCallback = NULL,
		   .callbackParam = NULL,
	   };

    LPI2C_DRV_MasterInit(port,&lpi2c1_MasterConfig0,&s_lpi2c1MasterState);

    return TRUE;
}

/*************************************************************************************************
 * @function Name:        ecual_I2C_deinit
 *
 * @description:          I2C闂傚倸鍊风粈渚�箟閿熺姵鍋￠柕澹懐鐓嬮梺鍦檸閸犳牠宕归崒鐐寸厱妞ゎ厽鍨垫禍婵嬫煕濞嗗繒绠婚柟顔筋殹閺佹劖鎯斿┑鍫㈡晨婵＄偑鍊栧ú鈺呭箯閿燂拷*
 * @parameters:           none
 *
 * @return:               true is successful
 *************************************************************************************************/
bool_t ecual_I2C_deinit( const uint8_t port )
{
    LPI2C_DRV_MasterDeinit(port);

    return TRUE;
}

/*****************************************************************************
** Function:    i2c_read
** Description: i2c闂傚倷娴囧畷鍨叏閺夋嚚褰掑礋椤栨氨顔嗛梺璺ㄥ櫐閹凤拷* Parameter:   int port,uint8_t dev_address,uint8_t ra_size,uint8_t * buffer,uint16_t size
** Return:      int
******************************************************************************/
uint16_t ecual_I2C_read(uint8_t port,uint16_t reg_address, uint8_t* buffer,uint16_t size)
{
	INT_All_Enable(FALSE);
	LPI2C_DRV_MasterSetSlaveAddr(port,reg_address,TRUE);
	LPI2C_DRV_MasterReceiveData(port,buffer,size,TRUE);
	INT_All_Enable(TRUE);
  	return TRUE;
}

/*****************************************************************************
** Function:    i2c_read
** Description: i2c闂傚倷娴囧畷鍨叏閺夋嚚褰掑礋椤栨氨顔嗛梺璺ㄥ櫐閹凤拷* Parameter:   int port,uint8_t dev_address,uint8_t ra_size,uint8_t * buffer,uint16_t size
** Return:      int
******************************************************************************/
FunctionalState ecual_I2C_compare(uint8_t port,uint16_t reg_address,const uint8_t* buffer,uint16_t size)
{
	uint8_t ReadData[size];
	uint16_t i;

	LPI2C_DRV_MasterSetSlaveAddr(port,reg_address,TRUE);
	LPI2C_DRV_MasterReceiveData(port,ReadData,size,TRUE);

	for(i=0; i<size; i++)
	{
		if(ReadData[i] != buffer[i])
		{
			return FALSE;
		}
	}
  	return TRUE;
}

/*****************************************************************************
** Function:    i2c_write
** Description: i2c闂傚倸鍊风粈渚�箟閿熺姴绀夌憸鏃堢嵁韫囨稒鏅搁柨鐕傛嫹* Parameter:   int port,uint8_t dev_address,uint16_t reg_address,uint8_t ra_size,const uint8_t * buffer,uint16_t size
** Return:      void
******************************************************************************/
#if 0
uint16_t ecual_I2C_write(uint8_t port,uint16_t reg_address,const uint8_t* buffer,uint16_t size)
{
	uint16_t  I2C_PageSize = 0x10;

	if((reg_address+size) > 0x800)
	{
		return STATUS_ERROR;
	}

	uint16_t _nStart = reg_address;
	uint16_t _nSize ;
	uint16_t _nPageCur;
	uint16_t _nPageNext;
	uint16_t _nLen  = size ;

	INT_All_Enable(FALSE);
	while(_nLen)
	{

		_nPageCur  = _nStart / I2C_PageSize ;
		_nPageNext = (_nStart + _nLen) / I2C_PageSize ;
		if(_nPageCur == _nPageNext)
		{
			_nSize = _nLen ;
		}
		else
		{
			_nSize = (_nPageCur + 1) * I2C_PageSize - _nStart ;
		}
		LPI2C_DRV_MasterSetSlaveAddr(port,_nStart,TRUE);
		LPI2C_DRV_MasterSendData(port,buffer,_nSize,TRUE);

		_nLen   -= _nSize ;
		_nStart += _nSize ;
		buffer  += _nSize ;

		INT_All_Enable(TRUE);
		systick_delay_ms(5);
		INT_All_Enable(FALSE);
	}
	INT_All_Enable(TRUE);

	return STATUS_SUCCESS;
}
#else
/*****************************************************************************
** Function:    ecual_I2C_write
** Description: i2c polling write
** Return:      status(default success)
******************************************************************************/
uint16_t ecual_I2C_write(uint8_t port,uint16_t reg_address,const uint8_t* buffer,uint16_t size)
{
	uint16_t writeSta = STATUS_ERROR;
	static uint16_t _nStart;
	static uint16_t _nSize ;
	static uint16_t p_nSize ;
	static uint16_t _nPageCur;
	static uint16_t _nPageNext;
	static uint16_t _nLen;
	static INT32U WriteTimeout = 0;
	static INT32U addrTest = 0;

	switch(s_writeStates)
	{
		case E_I2C_WRITE_STA_IDLE:
			_nStart = reg_address;
			_nLen  = size ;
			p_nSize = 0;
		case E_I2C_WRITE_STA_START:
			if(_nLen)
			{
				_nPageCur  = _nStart / I2C_PageSize ;
				_nPageNext = (_nStart + _nLen) / I2C_PageSize ;
				if(_nPageCur == _nPageNext)
				{
					_nSize = _nLen ;
				}
				else
				{
					_nSize = (_nPageCur + 1) * I2C_PageSize - _nStart ;
				}

				buffer  += p_nSize ;
				INT_All_Enable(FALSE);
				LPI2C_DRV_MasterSetSlaveAddr(port,_nStart,TRUE);
				LPI2C_DRV_MasterSendData(port,buffer,_nSize,TRUE);
				INT_All_Enable(TRUE);
				_nLen   -= _nSize ;
				_nStart += _nSize ;
				p_nSize += _nSize ;

				writeSta = STATUS_BUSY;

				WriteTimeout = CPU_GetTimeCount();

				s_writeStates = E_I2C_WRITE_STA_WAIT;
			}
			else
			{
				s_writeStates = E_I2C_WRITE_STA_IDLE;
				writeSta = STATUS_ERROR;
			}
			break;

		case E_I2C_WRITE_STA_WAIT:
			if(CPU_TimerDiffTs(WriteTimeout) < I2C_PageWriteTimeout)
			{
				s_writeStates = E_I2C_WRITE_STA_WAIT;
				writeSta = STATUS_BUSY;
			}
			else
			{
				if(_nLen)
				{
					s_writeStates = E_I2C_WRITE_STA_START;
					writeSta = STATUS_BUSY;
				}
				else
				{
					s_writeStates = E_I2C_WRITE_STA_IDLE;
					writeSta = STATUS_SUCCESS;
				}
			}
			break;

		default :
			s_writeStates = E_I2C_WRITE_STA_IDLE;
			writeSta = STATUS_ERROR;
			break;
	}

	return writeSta;
}
#endif
/*************************************************************************************************
 * End of Line
 *************************************************************************************************/
