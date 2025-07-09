/**
 *	@file TLE9210x_FuncLayer.c
 *	@author Infineon Technologies AG
 *	@date 11.09.2023
 *	@brief TLE9210x specific device driver implementation from Infineon Technologies AG.
 *
 ************************************************************************
 *
 * Copyright (c) 2023, Infineon Technologies AG
 * All rights reserved.
 *
 ************************************************************************
 */

/** \addtogroup TLE9210x_FUNCTION_LAYER
 *  @{
 */

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x_FuncLayer.h"

/************************************************************************
**                      Local Macro Definitions                        **
************************************************************************/

/************************************************************************
**                      Local Type Definitions                         **
************************************************************************/

/************************************************************************
**                    Local Variable Definitions                       **
************************************************************************/

/************************************************************************
**                    Local Function Definitions                       **
************************************************************************/

/************************************************************************
**                    Global Variable Definitions                      **
************************************************************************/

/************************************************************************
**                    Global Function Definitions                      **
************************************************************************/

/** \brief Set Direction of current sense amplifier 2
*
*   \note  Value: 0b0b - The current sense is unidirectional
*   \note  Value: 0b1b - The current sense is bidirectional
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSD2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_CSD2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_CSD2_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_CSD2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Direction of current sense amplifier 2
*
*   \note  Value: 0b0b - The current sense is unidirectional
*   \note  Value: 0b1b - The current sense is bidirectional
*
*   \return CSD2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSD2(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.CSD2;
}

/** \brief Set Gain of current sense amplifier 2
*
*   \note  Value: 0b00b - 10 V/V (default)
*   \note  Value: 0b01b - 20 V/V
*   \note  Value: 0b10b - 40 V/V
*   \note  Value: 0b11b - 80 V/V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSAG2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_CSAG2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_CSAG2_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_CSAG2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Gain of current sense amplifier 2
*
*   \note  Value: 0b00b - 10 V/V (default)
*   \note  Value: 0b01b - 20 V/V
*   \note  Value: 0b10b - 40 V/V
*   \note  Value: 0b11b - 80 V/V
*
*   \return CSAG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSAG2(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.CSAG2;
}

/** \brief Set Direction of current sense amplifier 1
*
*   \note  Value: 0b0b - The current sense is unidirectional (default)
*   \note  Value: 0b1b - The current sense is bidirectional
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSD1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_CSD1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_CSD1_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_CSD1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Direction of current sense amplifier 1
*
*   \note  Value: 0b0b - The current sense is unidirectional (default)
*   \note  Value: 0b1b - The current sense is bidirectional
*
*   \return CSD1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSD1(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.CSD1;
}

/** \brief Set Gain of current sense amplifier 1
*
*   \note  Value: 0b00b - 10 V/V (default)
*   \note  Value: 0b01b - 20 V/V
*   \note  Value: 0b10b - 40 V/V
*   \note  Value: 0b11b - 80 V/V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSAG1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_CSAG1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_CSAG1_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_CSAG1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Gain of current sense amplifier 1
*
*   \note  Value: 0b00b - 10 V/V (default)
*   \note  Value: 0b01b - 20 V/V
*   \note  Value: 0b10b - 40 V/V
*   \note  Value: 0b11b - 80 V/V
*
*   \return CSAG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSAG1(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.CSAG1;
}

/** \brief Set Register banking
*
*   \note  Value: 0b0b - (Default)
*   \note  Value: 0b1b - REG_BANK = 1
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_REG_BANK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_REG_BANK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_REG_BANK_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_REG_BANK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Register banking
*
*   \note  Value: 0b0b - (Default)
*   \note  Value: 0b1b - REG_BANK = 1
*
*   \return REG_BANK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_REG_BANK(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.REG_BANK;
}

/** \brief Set VS Overvoltage threshold
*
*   \note  Value: 0b0b - V_SOVOFF = V_SOVOFF1 (min. 19V, default)
*   \note  Value: 0b1b - V_SOVOFF = V_SOVOFF2 (min. 29V)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_VSOVTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_VSOVTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_VSOVTH_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_VSOVTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get VS Overvoltage threshold
*
*   \note  Value: 0b0b - V_SOVOFF = V_SOVOFF1 (min. 19V, default)
*   \note  Value: 0b1b - V_SOVOFF = V_SOVOFF2 (min. 29V)
*
*   \return VSOVTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_VSOVTH(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.VSOVTH;
}

/** \brief Set Unlock bit to disable the watchdog
*
*   \note  Value: 0b0b - WDDIS cannot be reset (default)
*   \note  Value: 0b1b - WDDIS (GENCTRL2) can be reset in the following SPI frame
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_UNLOCK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_UNLOCK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_UNLOCK_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_UNLOCK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Unlock bit to disable the watchdog
*
*   \note  Value: 0b0b - WDDIS cannot be reset (default)
*   \note  Value: 0b1b - WDDIS (GENCTRL2) can be reset in the following SPI frame
*
*   \return UNLOCK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_UNLOCK(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.UNLOCK;
}

/** \brief Set Frequency modulation
*
*   \note  Value: 0b0b - No modulation
*   \note  Value: 0b1b - Modulation frequency 15.6 kHz (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_FMODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_FMODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_FMODE_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_FMODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Frequency modulation
*
*   \note  Value: 0b0b - No modulation
*   \note  Value: 0b1b - Modulation frequency 15.6 kHz (default)
*
*   \return FMODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_FMODE(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.FMODE;
}

/** \brief Set Adaptation of the pre-charge and pre-discharge current
*
*   \note  Value: 0b0b - 1 current step (default)
*   \note  Value: 0b1b - 2 current steps
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_IPCHGADT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_IPCHGADT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_IPCHGADT_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_IPCHGADT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Adaptation of the pre-charge and pre-discharge current
*
*   \note  Value: 0b0b - 1 current step (default)
*   \note  Value: 0b1b - 2 current steps
*
*   \return IPCHGADT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_IPCHGADT(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.IPCHGADT;
}

/** \brief Set Overcurrent shutdown Enable
*
*   \note  Value: 0b0b - Disabled
*   \note  Value: 0b1b - Enabled (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_OCEN(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_OCEN_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_OCEN_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_OCEN_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Overcurrent shutdown Enable
*
*   \note  Value: 0b0b - Disabled
*   \note  Value: 0b1b - Enabled (default)
*
*   \return OCEN value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_OCEN(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.OCEN;
}

/** \brief Set Watchdog period
*
*   \note  Value: 0b0b - 50 ms
*   \note  Value: 0b1b - 200 ms (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_WDPER(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_WDPER_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_WDPER_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_WDPER_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Watchdog period
*
*   \note  Value: 0b0b - 50 ms
*   \note  Value: 0b1b - 200 ms (default)
*
*   \return WDPER value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_WDPER(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.WDPER;
}

/** \brief Set Watchdog trigger bit
*
*   \note  Value: 0b0b - After power on reset, the default value is 0
*   \note  Value: 0b1b - This bit is inverted within a watchdog period
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL1_WDTRIG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL1_WDTRIG_Pos) & (uint16_t)TLE9210x_Control_GENCTRL1_WDTRIG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Watchdog trigger bit
*
*   \note  Value: 0b0b - After power on reset, the default value is 0
*   \note  Value: 0b1b - This bit is inverted within a watchdog period
*
*   \return WDTRIG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_WDTRIG(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL1.bit.WDTRIG;
}

/** \brief Set General Control Register 1 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Postcharge disable bit
*
*   \note  Value: 0b0b - The postcharge is enabled during PWM (defaultO
*   \note  Value: 0b1b - The postcharge is disabled during PWM
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_POCHGDIS(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_POCHGDIS_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_POCHGDIS_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_POCHGDIS_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Postcharge disable bit
*
*   \note  Value: 0b0b - The postcharge is enabled during PWM (defaultO
*   \note  Value: 0b1b - The postcharge is disabled during PWM
*
*   \return POCHGDIS value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_POCHGDIS(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.POCHGDIS;
}

/** \brief Set Bridge driver passive mode
*
*   \note  Value: 0b0b - Bridge driver is in active mode
*   \note  Value: 0b1b - Bridge driver is in passive mode (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_BD_PASS(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_BD_PASS_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_BD_PASS_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_BD_PASS_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Bridge driver passive mode
*
*   \note  Value: 0b0b - Bridge driver is in active mode
*   \note  Value: 0b1b - Bridge driver is in passive mode (default)
*
*   \return BD_PASS value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_BD_PASS(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.BD_PASS;
}

/** \brief Set Filter for adaptive gate control
*
*   \note  Value: 0b0b - No filter applied (default)
*   \note  Value: 0b1b - Filter applied
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_AGCFILT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_AGCFILT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_AGCFILT_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_AGCFILT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Filter for adaptive gate control
*
*   \note  Value: 0b0b - No filter applied (default)
*   \note  Value: 0b1b - Filter applied
*
*   \return AGCFILT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_AGCFILT(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.AGCFILT;
}

/** \brief Set Adaptive gate control
*
*   \note  Value: 0b00b - (default) Adaptive gate control disabled, pre-charge and predischarge disabled
*   \note  Value: 0b01b - Adaptive gate control disabled, precharge is disabled, predischarge is enabled with IPREDCHG = IPDCHGINIT
*   \note  Value: 0b10b - Adaptive gate control enabled, IPRECHG and IPREDCHG are self adapted
*   \note  Value: 0b11b - Reserved. Adaptive gate control enabled, IPRECHG and IPREDCHG are self adapted
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_AGC(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_AGC_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_AGC_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_AGC_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Adaptive gate control
*
*   \note  Value: 0b00b - (default) Adaptive gate control disabled, pre-charge and predischarge disabled
*   \note  Value: 0b01b - Adaptive gate control disabled, precharge is disabled, predischarge is enabled with IPREDCHG = IPDCHGINIT
*   \note  Value: 0b10b - Adaptive gate control enabled, IPRECHG and IPREDCHG are self adapted
*   \note  Value: 0b11b - Reserved. Adaptive gate control enabled, IPRECHG and IPREDCHG are self adapted
*
*   \return AGC value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_AGC(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.AGC;
}

/** \brief Set Gate driver hold current IHOLD
*
*   \note  Value: 0b0b - (default) Charge: I_CHG8 (12.5 mA typ.), discharge I_DCHG8 (14.2 mA typ.)
*   \note  Value: 0b1b - Charge: I_CHG12 (23.9 mA typ.), discharge: I_DCHG12 (26.0 mA typ.)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_IHOLD(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_IHOLD_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_IHOLD_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_IHOLD_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Gate driver hold current IHOLD
*
*   \note  Value: 0b0b - (default) Charge: I_CHG8 (12.5 mA typ.), discharge I_DCHG8 (14.2 mA typ.)
*   \note  Value: 0b1b - Charge: I_CHG12 (23.9 mA typ.), discharge: I_DCHG12 (26.0 mA typ.)
*
*   \return IHOLD value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_IHOLD(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.IHOLD;
}

/** \brief Set Watchdog disable bit
*
*   \note  Value: 0b0b - The watchdog is enabled (default)
*   \note  Value: 0b1b - The watchdog is disabled if the previous SPI frame has set UNLOCK bit (GENCTRL1)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_WDDIS(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_WDDIS_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_WDDIS_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_WDDIS_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Watchdog disable bit
*
*   \note  Value: 0b0b - The watchdog is enabled (default)
*   \note  Value: 0b1b - The watchdog is disabled if the previous SPI frame has set UNLOCK bit (GENCTRL1)
*
*   \return WDDIS value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_WDDIS(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.WDDIS;
}

/** \brief Set Masking of the turn-on/off delay error in the Global Error Flag
*
*   \note  Value: 0b0b - Turn-on/off delay error is reported in the GEF
*   \note  Value: 0b1b - Turn-on/off delay error is masked in the GEF (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_MSKTDREG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_MSKTDREG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_MSKTDREG_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_MSKTDREG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Masking of the turn-on/off delay error in the Global Error Flag
*
*   \note  Value: 0b0b - Turn-on/off delay error is reported in the GEF
*   \note  Value: 0b1b - Turn-on/off delay error is masked in the GEF (default)
*
*   \return MSKTDREG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_MSKTDREG(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.MSKTDREG;
}

/** \brief Set Charge pump undervoltage detection threshold
*
*   \note  Value: 0b0b - V_CPUV (referred to VS) = 6.0 V typ.
*   \note  Value: 0b1b - V_CPUV (referred to VS) = 7.5 V typ. (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_CPUVTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_CPUVTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_CPUVTH_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_CPUVTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Charge pump undervoltage detection threshold
*
*   \note  Value: 0b0b - V_CPUV (referred to VS) = 6.0 V typ.
*   \note  Value: 0b1b - V_CPUV (referred to VS) = 7.5 V typ. (default)
*
*   \return CPUVTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_CPUVTH(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.CPUVTH;
}

/** \brief Set Automatic switch-over between dual and single charge pump stage
*
*   \note  Value: 0b0b - Automatic switch over deactivated (default)
*   \note  Value: 0b1b - Automatic switch over activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_CPSTGA(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_CPSTGA_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_CPSTGA_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_CPSTGA_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Automatic switch-over between dual and single charge pump stage
*
*   \note  Value: 0b0b - Automatic switch over deactivated (default)
*   \note  Value: 0b1b - Automatic switch over activated
*
*   \return CPSTGA value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_CPSTGA(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.CPSTGA;
}

/** \brief Set Filter time of drain-souce voltage monitoring
*
*   \note  Value: 0b00b - 0.5 µs (default)
*   \note  Value: 0b01b - 1 µs
*   \note  Value: 0b10b - 2 µs
*   \note  Value: 0b11b - 3 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_TFVDS(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_TFVDS_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_TFVDS_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_TFVDS_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Filter time of drain-souce voltage monitoring
*
*   \note  Value: 0b00b - 0.5 µs (default)
*   \note  Value: 0b01b - 1 µs
*   \note  Value: 0b10b - 2 µs
*   \note  Value: 0b11b - 3 µs
*
*   \return TFVDS value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_TFVDS(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.TFVDS;
}

/** \brief Set Overcurrent detection threshold of CSO2 with CSD2 = 0/1
*
*   \note  Value: 0b00b - If the CSD2-Value is 0, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD2-Value is 0, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD2-Value is 0, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD2-Value is 0, the appropriate option 4 is used - For more Information see the datasheet
*   \note  Value: 0b00b - If the CSD2-Value is 1, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD2-Value is 1, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD2-Value is 1, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD2-Value is 1, the appropriate option 4 is used - For more Information see the datasheet
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_OCTH2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_OCTH2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_OCTH2_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_OCTH2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Overcurrent detection threshold of CSO2 with CSD2 = 0/1
*
*   \note  Value: 0b00b - If the CSD2-Value is 0, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD2-Value is 0, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD2-Value is 0, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD2-Value is 0, the appropriate option 4 is used - For more Information see the datasheet
*   \note  Value: 0b00b - If the CSD2-Value is 1, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD2-Value is 1, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD2-Value is 1, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD2-Value is 1, the appropriate option 4 is used - For more Information see the datasheet
*
*   \return OCTH2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_OCTH2(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.OCTH2;
}

/** \brief Set Overcurrent detection threshold of CSO1 with CSD1 = 0/1
*
*   \note  Value: 0b00b - If the CSD1-Value is 0, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD1-Value is 0, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD1-Value is 0, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD1-Value is 0, the appropriate option 4 is used - For more Information see the datasheet
*   \note  Value: 0b00b - If the CSD1-Value is 1, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD1-Value is 1, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD1-Value is 1, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD1-Value is 1, the appropriate option 4 is used - For more Information see the datasheet
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_OCTH1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_GENCTRL2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_GENCTRL2_OCTH1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_GENCTRL2_OCTH1_Pos) & (uint16_t)TLE9210x_Control_GENCTRL2_OCTH1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Overcurrent detection threshold of CSO1 with CSD1 = 0/1
*
*   \note  Value: 0b00b - If the CSD1-Value is 0, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD1-Value is 0, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD1-Value is 0, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD1-Value is 0, the appropriate option 4 is used - For more Information see the datasheet
*   \note  Value: 0b00b - If the CSD1-Value is 1, the appropriate option 1 is used - For more Information see the datasheet (default)
*   \note  Value: 0b01b - If the CSD1-Value is 1, the appropriate option 2 is used - For more Information see the datasheet
*   \note  Value: 0b10b - If the CSD1-Value is 1, the appropriate option 3 is used - For more Information see the datasheet
*   \note  Value: 0b11b - If the CSD1-Value is 1, the appropriate option 4 is used - For more Information see the datasheet
*
*   \return OCTH1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_OCTH1(void)
{
	return (uint16_t)TLE9210x->Control_GENCTRL2.bit.OCTH1;
}

/** \brief Set General Control Register 2 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_GENCTRL2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set HS4 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH4 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH4
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB4D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB4D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB4D_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB4D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HS4 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH4 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH4
*
*   \return HB4D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB4D(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB4D;
}

/** \brief Set HS3 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH3 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH3
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB3D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB3D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB3D_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB3D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HS3 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH3 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH3
*
*   \return HB3D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB3D(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB3D;
}

/** \brief Set HS2 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH2 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN-VSH2
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB2D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB2D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB2D_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB2D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HS2 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH2 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN-VSH2
*
*   \return HB2D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB2D(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB2D;
}

/** \brief Set HS1 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH1 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH1
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB1D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB1D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB1D_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB1D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HS1 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH1 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH1
*
*   \return HB1D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB1D(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB1D;
}

/** \brief Set HB4 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB4VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB4VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB4VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB4VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HB4 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB4VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB4VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB4VDSTH;
}

/** \brief Set HB3 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB3VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB3VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB3VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB3VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HB3 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB3VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB3VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB3VDSTH;
}

/** \brief Set HB2 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB2VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB2VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB2VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB2VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HB2 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB2VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB2VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB2VDSTH;
}

/** \brief Set HB1 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB1VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS1_HB1VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS1_HB1VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS1_HB1VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get HB1 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB1VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB1VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.bit.HB1VDSTH;
}

/** \brief Set Drain-source monitoring HB1-4 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS1;
		u8_success = 1;
	}
	return u8_success;
}
/** \brief Set Drain-source monitoring HB1-4 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS1(void)
{
	return (uint16_t)TLE9210x->Control_VDS1.reg;
}

#if TLE9210x_Variant == TLE92108
/** \brief Set HS8 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH8 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH8
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB8D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB8D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB8D_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB8D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HS8 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH8 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH8
*
*   \return HB8D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB8D(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB8D;
}
#endif

/** \brief Set HS7 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH7 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH7
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB7D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB7D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB7D_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB7D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HS7 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH7 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH7
*
*   \return HB7D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB7D(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB7D;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HS6 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH6 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN-VSH6
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB6D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB6D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB6D_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB6D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HS6 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH6 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN-VSH6
*
*   \return HB6D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB6D(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB6D;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HS5 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH5 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH5
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB5D(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB5D_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB5D_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB5D_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HS5 Drain-source monitoring
*
*   \note  Value: 0b0b - Drain-source monitoring: DH-VSH5 (default)
*   \note  Value: 0b1b - Drain-source monitoring: CSIN1-VSH5
*
*   \return HB5D value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB5D(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB5D;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB8 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB8VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB8VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB8VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB8VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB8 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB8VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB8VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB8VDSTH;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB7 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB7VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB7VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB7VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB7VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB7 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB7VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB7VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB7VDSTH;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB6 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB6VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB6VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB6VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB6VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB6 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB6VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB6VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB6VDSTH;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB5 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB5VDSTH(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_VDS2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_VDS2_HB5VDSTH_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_VDS2_HB5VDSTH_Pos) & (uint16_t)TLE9210x_Control_VDS2_HB5VDSTH_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB5 drain-source overvoltage threshold
*
*   \note  Value: 0b000b - 0.15 V
*   \note  Value: 0b001b - 0.20 V (default)
*   \note  Value: 0b010b - 0.25 V
*   \note  Value: 0b011b - 0.30 V
*   \note  Value: 0b100b - 0.40 V
*   \note  Value: 0b101b - 0.50 V
*   \note  Value: 0b110b - 0.60 V
*   \note  Value: 0b111b - 2.0 V
*
*   \return HB5VDSTH value
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB5VDSTH(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.bit.HB5VDSTH;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Drain-source monitoring threshold HB5-8 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_VDS2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_VDS2;
		u8_success = 1;
	}
	return u8_success;
}
/** \brief Set Drain-source monitoring threshold HB5-8 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint16_t TLE9210x_FuncLayer_get_Control_VDS2(void)
{
	return (uint16_t)TLE9210x->Control_VDS2.reg;
}

#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Cross-current protection and blank times applied to HB8
*
*   \note  Value: 0b00b - (tHB8CCP, tHB8BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB8CCP, tHB8BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB8CCP, tHB8BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB8CCP, tHB8BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB8CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB8CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB8CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB8CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Cross-current protection and blank times applied to HB8
*
*   \note  Value: 0b00b - (tHB8CCP, tHB8BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB8CCP, tHB8BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB8CCP, tHB8BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB8CCP, tHB8BLANK) = (tCCP4, tBLANK4)
*
*   \return HB8CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB8CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB8CCPBLK;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Cross-current protection and blank times applied to HB7
*
*   \note  Value: 0b00b - (tHB7CCP, tHB7BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB7CCP, tHB7BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB7CCP, tHB7BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB7CCP, tHB7BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB7CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB7CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB7CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB7CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Cross-current protection and blank times applied to HB7
*
*   \note  Value: 0b00b - (tHB7CCP, tHB7BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB7CCP, tHB7BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB7CCP, tHB7BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB7CCP, tHB7BLANK) = (tCCP4, tBLANK4)
*
*   \return HB7CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB7CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB7CCPBLK;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Cross-current protection and blank times applied to HB6
*
*   \note  Value: 0b00b - (tHB6CCP, tHB6BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB6CCP, tHB6BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB6CCP, tHB6BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB6CCP, tHB6BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB6CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB6CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB6CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB6CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Cross-current protection and blank times applied to HB6
*
*   \note  Value: 0b00b - (tHB6CCP, tHB6BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB6CCP, tHB6BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB6CCP, tHB6BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB6CCP, tHB6BLANK) = (tCCP4, tBLANK4)
*
*   \return HB6CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB6CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB6CCPBLK;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Cross-current protection and blank times applied to HB5
*
*   \note  Value: 0b00b - (tHB5CCP, tHB5BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB5CCP, tHB5BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB5CCP, tHB5BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB5CCP, tHB5BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB5CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB5CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB5CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB5CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Cross-current protection and blank times applied to HB5
*
*   \note  Value: 0b00b - (tHB5CCP, tHB5BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB5CCP, tHB5BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB5CCP, tHB5BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB5CCP, tHB5BLANK) = (tCCP4, tBLANK4)
*
*   \return HB5CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB5CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB5CCPBLK;
}
#endif

/** \brief Set Cross-current protection and blank times applied to HB4
*
*   \note  Value: 0b00b - (tHB4CCP, tHB4BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB4CCP, tHB4BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB4CCP, tHB4BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB4CCP, tHB4BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB4CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB4CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB4CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB4CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Cross-current protection and blank times applied to HB4
*
*   \note  Value: 0b00b - (tHB4CCP, tHB4BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB4CCP, tHB4BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB4CCP, tHB4BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB4CCP, tHB4BLANK) = (tCCP4, tBLANK4)
*
*   \return HB4CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB4CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB4CCPBLK;
}

/** \brief Set Cross-current protection and blank times applied to HB3
*
*   \note  Value: 0b00b - (tHB3CCP, tHB3BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB3CCP, tHB3BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB3CCP, tHB3BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB3CCP, tHB3BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB3CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB3CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB3CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB3CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Cross-current protection and blank times applied to HB3
*
*   \note  Value: 0b00b - (tHB3CCP, tHB3BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB3CCP, tHB3BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB3CCP, tHB3BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB3CCP, tHB3BLANK) = (tCCP4, tBLANK4)
*
*   \return HB3CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB3CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB3CCPBLK;
}

/** \brief Set Cross-current protection and blank times applied to HB2
*
*   \note  Value: 0b00b - (tHB2CCP, tHB2BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB2CCP, tHB2BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB2CCP, tHB2BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB2CCP, tHB2BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB2CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB2CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB2CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB2CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Cross-current protection and blank times applied to HB2
*
*   \note  Value: 0b00b - (tHB2CCP, tHB2BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB2CCP, tHB2BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB2CCP, tHB2BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB2CCP, tHB2BLANK) = (tCCP4, tBLANK4)
*
*   \return HB2CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB2CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB2CCPBLK;
}

/** \brief Set Cross-current protection and blank times applied to HB1
*
*   \note  Value: 0b00b - (tHB1CCP, tHB1BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB1CCP, tHB1BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB1CCP, tHB1BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB1CCP, tHB1BLANK) = (tCCP4, tBLANK4)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB1CCPBLK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK1_HB1CCPBLK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK1_HB1CCPBLK_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK1_HB1CCPBLK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Cross-current protection and blank times applied to HB1
*
*   \note  Value: 0b00b - (tHB1CCP, tHB1BLANK) = (tCCP1, tBLANK1) (default)
*   \note  Value: 0b01b - (tHB1CCP, tHB1BLANK) = (tCCP2, tBLANK2)
*   \note  Value: 0b10b - (tHB1CCP, tHB1BLANK) = (tCCP3, tBLANK3)
*   \note  Value: 0b11b - (tHB1CCP, tHB1BLANK) = (tCCP4, tBLANK4)
*
*   \return HB1CCPBLK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB1CCPBLK(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK1.bit.HB1CCPBLK;
}

/** \brief Set Cross current protection and blank times setting 1 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Cross-current protection - tCCP3 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP3_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_ACT_TCCP3_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP3_ACT_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP3_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP3 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP3_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP3_ACT(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.bit.TCCP3_ACT;
}

/** \brief Set Blank time - tBLANK2 Active
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TBLANK2_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_ACT_TBLANK2_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TBLANK2_ACT_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TBLANK2_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time - tBLANK2 Active
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TBLANK2_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TBLANK2_ACT(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.bit.TBLANK2_ACT;
}

/** \brief Set Cross-current protection - tCCP2 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP2_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_ACT_TCCP2_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP2_ACT_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP2_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP2 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP2_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP2_ACT(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.bit.TCCP2_ACT;
}

/** \brief Set Blank time - tBLANK1 Active
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TBLANK1_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_ACT_TBLANK1_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TBLANK1_ACT_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TBLANK1_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time - tBLANK1 Active
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TBLANK1_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TBLANK1_ACT(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.bit.TBLANK1_ACT;
}

/** \brief Set Cross-current protection - tCCP1 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP1_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_ACT_TCCP1_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP1_ACT_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_ACT_TCCP1_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP1 Active
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP1_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP1_ACT(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_ACT.bit.TCCP1_ACT;
}

/** \brief Set Cross current protection and blank times setting for active MOSFETs Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Cross-current protection - tCCP3 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP3_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_FW_TCCP3_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP3_FW_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP3_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP3 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP3_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP3_FW(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_FW.bit.TCCP3_FW;
}

/** \brief Set Blank time - tBLANK2 Freewheeling
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TBLANK2_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_FW_TBLANK2_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TBLANK2_FW_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TBLANK2_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time - tBLANK2 Freewheeling
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TBLANK2_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TBLANK2_FW(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_FW.bit.TBLANK2_FW;
}

/** \brief Set Cross-current protection - tCCP2 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP2_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_FW_TCCP2_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP2_FW_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP2_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP2 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP2_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP2_FW(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_FW.bit.TCCP2_FW;
}

/** \brief Set Blank time - tBLANK1 Freewheeling
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TBLANK1_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_FW_TBLANK1_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TBLANK1_FW_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TBLANK1_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time - tBLANK1 Freewheeling
*
*   \note  Value: 0b000b - 625 ns
*   \note  Value: 0b001b - 1000 ns
*   \note  Value: 0b010b - 1250 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TBLANK1_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TBLANK1_FW(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_FW.bit.TBLANK1_FW;
}

/** \brief Set Cross-current protection - tCCP1 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP1_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CCP_BLK2_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CCP_BLK2_FW_TCCP1_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP1_FW_Pos) & (uint16_t)TLE9210x_Control_CCP_BLK2_FW_TCCP1_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP1 Freewheeling
*
*   \note  Value: 0b000b - 375 ns
*   \note  Value: 0b001b - 625 ns
*   \note  Value: 0b010b - 1000 ns
*   \note  Value: 0b011b - 1500 ns
*   \note  Value: 0b100b - 2000 ns (default)
*   \note  Value: 0b101b - 3000 ns
*   \note  Value: 0b110b - 4000 ns
*   \note  Value: 0b111b - 16000 ns
*
*   \return TCCP1_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP1_FW(void)
{
	return (uint16_t)TLE9210x->Control_CCP_BLK2_FW.bit.TCCP1_FW;
}

/** \brief Set Cross current protection and blank times setting for FW MOSFETs Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CCP_BLK2_FW;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

#if TLE9210x_Variant == TLE92108
/** \brief Set Half-bridge output 8 mode selection
*
*   \note  Value: 0b00b - HB8 is in high impedance (default)
*   \note  Value: 0b01b - LS8 is ON
*   \note  Value: 0b10b - HS8 is ON
*   \note  Value: 0b11b - Reserved - HB8 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB8MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB8MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB8MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB8MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Half-bridge output 8 mode selection
*
*   \note  Value: 0b00b - HB8 is in high impedance (default)
*   \note  Value: 0b01b - LS8 is ON
*   \note  Value: 0b10b - HS8 is ON
*   \note  Value: 0b11b - Reserved - HB8 is in high impedance
*
*   \return HB8MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB8MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB8MODE;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Half-bridge output 7 mode selection
*
*   \note  Value: 0b00b - HB7 is in high impedance (default)
*   \note  Value: 0b01b - LS7 is ON
*   \note  Value: 0b10b - HS7 is ON
*   \note  Value: 0b11b - Reserved - HB7 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB7MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB7MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB7MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB7MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Half-bridge output 7 mode selection
*
*   \note  Value: 0b00b - HB7 is in high impedance (default)
*   \note  Value: 0b01b - LS7 is ON
*   \note  Value: 0b10b - HS7 is ON
*   \note  Value: 0b11b - Reserved - HB7 is in high impedance
*
*   \return HB7MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB7MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB7MODE;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Half-bridge output 6 mode selection
*
*   \note  Value: 0b00b - HB6 is in high impedance (default)
*   \note  Value: 0b01b - LS6 is ON
*   \note  Value: 0b10b - HS6 is ON
*   \note  Value: 0b11b - Reserved - HB6 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB6MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB6MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB6MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB6MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Half-bridge output 6 mode selection
*
*   \note  Value: 0b00b - HB6 is in high impedance (default)
*   \note  Value: 0b01b - LS6 is ON
*   \note  Value: 0b10b - HS6 is ON
*   \note  Value: 0b11b - Reserved - HB6 is in high impedance
*
*   \return HB6MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB6MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB6MODE;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Half-bridge output 5 mode selection
*
*   \note  Value: 0b00b - HB5 is in high impedance (default)
*   \note  Value: 0b01b - LS5 is ON
*   \note  Value: 0b10b - HS5 is ON
*   \note  Value: 0b11b - Reserved - HB5 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB5MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB5MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB5MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB5MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Half-bridge output 5 mode selection
*
*   \note  Value: 0b00b - HB5 is in high impedance (default)
*   \note  Value: 0b01b - LS5 is ON
*   \note  Value: 0b10b - HS5 is ON
*   \note  Value: 0b11b - Reserved - HB5 is in high impedance
*
*   \return HB5MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB5MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB5MODE;
}
#endif

/** \brief Set Half-bridge output 4 mode selection
*
*   \note  Value: 0b00b - HB4 is in high impedance (default)
*   \note  Value: 0b01b - LS4 is ON
*   \note  Value: 0b10b - HS4 is ON
*   \note  Value: 0b11b - Reserved - HB4 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB4MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB4MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB4MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB4MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Half-bridge output 4 mode selection
*
*   \note  Value: 0b00b - HB4 is in high impedance (default)
*   \note  Value: 0b01b - LS4 is ON
*   \note  Value: 0b10b - HS4 is ON
*   \note  Value: 0b11b - Reserved - HB4 is in high impedance
*
*   \return HB4MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB4MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB4MODE;
}

/** \brief Set Half-bridge output 3 mode selection
*
*   \note  Value: 0b00b - HB3 is in high impedance (default)
*   \note  Value: 0b01b - LS3 is ON
*   \note  Value: 0b10b - HS3 is ON
*   \note  Value: 0b11b - Reserved - HB3 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB3MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB3MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB3MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB3MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Half-bridge output 3 mode selection
*
*   \note  Value: 0b00b - HB3 is in high impedance (default)
*   \note  Value: 0b01b - LS3 is ON
*   \note  Value: 0b10b - HS3 is ON
*   \note  Value: 0b11b - Reserved - HB3 is in high impedance
*
*   \return HB3MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB3MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB3MODE;
}

/** \brief Set Half-bridge output 2 mode selection
*
*   \note  Value: 0b00b - HB2 is in high impedance (default)
*   \note  Value: 0b01b - LS2 is ON
*   \note  Value: 0b10b - HS2 is ON
*   \note  Value: 0b11b - Reserved - HB2 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB2MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB2MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB2MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB2MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Half-bridge output 2 mode selection
*
*   \note  Value: 0b00b - HB2 is in high impedance (default)
*   \note  Value: 0b01b - LS2 is ON
*   \note  Value: 0b10b - HS2 is ON
*   \note  Value: 0b11b - Reserved - HB2 is in high impedance
*
*   \return HB2MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB2MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB2MODE;
}

/** \brief Set Half-bridge output 1 mode selection
*
*   \note  Value: 0b00b - HB1 is in high impedance (default)
*   \note  Value: 0b01b - LS1 is ON
*   \note  Value: 0b10b - HS1 is ON
*   \note  Value: 0b11b - Reserved - HB1 is in high impedance
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB1MODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBMODE.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBMODE_HB1MODE_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBMODE_HB1MODE_Pos) & (uint16_t)TLE9210x_Control_HBMODE_HB1MODE_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Half-bridge output 1 mode selection
*
*   \note  Value: 0b00b - HB1 is in high impedance (default)
*   \note  Value: 0b01b - LS1 is ON
*   \note  Value: 0b10b - HS1 is ON
*   \note  Value: 0b11b - Reserved - HB1 is in high impedance
*
*   \return HB1MODE value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB1MODE(void)
{
	return (uint16_t)TLE9210x->Control_HBMODE.bit.HB1MODE;
}

/** \brief Set Half-bridge mode Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBMODE;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Drain-Source monitoring in bridge passive mode
*
*   \note  Value: 0b0b - DS monitoring in bridge passive mode disabled
*   \note  Value: 0b1b - DS monitoring in bridge passive mode enabled (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PASS_VDS(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PASS_VDS_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PASS_VDS_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PASS_VDS_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get Drain-Source monitoring in bridge passive mode
*
*   \note  Value: 0b0b - DS monitoring in bridge passive mode disabled
*   \note  Value: 0b1b - DS monitoring in bridge passive mode enabled (default)
*
*   \return PASS_VDS value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PASS_VDS(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PASS_VDS;
}

/** \brief Set Settings for bridge driver passive mode
*
*   \note  Value: 0b00b - LS1-4 are always off
*   \note  Value: 0b01b - LS1-4 are always on (static brake)
*   \note  Value: 0b10b - LS1-4 are activated if passive VS OV is detected (overvoltage break) (default)
*   \note  Value: 0b11b - LS1-4 are activated if passive VS OV is detected and PWM1 = High (overvoltage brake conditioned by PWM1)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PASS_MOD(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PASS_MOD_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PASS_MOD_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PASS_MOD_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get Settings for bridge driver passive mode
*
*   \note  Value: 0b00b - LS1-4 are always off
*   \note  Value: 0b01b - LS1-4 are always on (static brake)
*   \note  Value: 0b10b - LS1-4 are activated if passive VS OV is detected (overvoltage break) (default)
*   \note  Value: 0b11b - LS1-4 are activated if passive VS OV is detected and PWM1 = High (overvoltage brake conditioned by PWM1)
*
*   \return PASS_MOD value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PASS_MOD(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PASS_MOD;
}

/** \brief Set Allowcation of the PWM channel 3
*
*   \note  Value: 0b000b - Allocated to HB1
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7 (default)
*   \note  Value: 0b111b - Allocated to HB8
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_HB(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PWM3_HB_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PWM3_HB_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PWM3_HB_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get Allowcation of the PWM channel 3
*
*   \note  Value: 0b000b - Allocated to HB1
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7 (default)
*   \note  Value: 0b111b - Allocated to HB8
*
*   \return PWM3_HB value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM3_HB(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PWM3_HB;
}

/** \brief Set PWM channel 3 enable
*
*   \note  Value: 0b0b - PWM3 is disabled (default)
*   \note  Value: 0b1b - PWM3 is enabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_EN(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PMW3_EN_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PMW3_EN_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PMW3_EN_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get PWM channel 3 enable
*
*   \note  Value: 0b0b - PWM3 is disabled (default)
*   \note  Value: 0b1b - PWM3 is enabled
*
*   \return PMW3_EN value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM3_EN(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PMW3_EN;
}

/** \brief Set Allocation of the PWM channel 2
*
*   \note  Value: 0b000b - Allocated to HB1
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4 (default)
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7
*   \note  Value: 0b111b - Allocated to HB8
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_HB(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PWM2_HB_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PWM2_HB_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PWM2_HB_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get Allocation of the PWM channel 2
*
*   \note  Value: 0b000b - Allocated to HB1
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4 (default)
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7
*   \note  Value: 0b111b - Allocated to HB8
*
*   \return PWM2_HB value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM2_HB(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PWM2_HB;
}

/** \brief Set PWM channel 2 enable
*
*   \note  Value: 0b0b - PWM2 is disabled (default)
*   \note  Value: 0b1b - PWM2 is enabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_EN(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PWM2_EN_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PWM2_EN_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PWM2_EN_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get PWM channel 2 enable
*
*   \note  Value: 0b0b - PWM2 is disabled (default)
*   \note  Value: 0b1b - PWM2 is enabled
*
*   \return PWM2_EN value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM2_EN(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PWM2_EN;
}

/** \brief Set Allocation of the PWM channel 1
*
*   \note  Value: 0b000b - Allocated to HB1 (default)
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7
*   \note  Value: 0b111b - Allocated to HB8
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_HB(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PWM1_HB_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PWM1_HB_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PWM1_HB_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get Allocation of the PWM channel 1
*
*   \note  Value: 0b000b - Allocated to HB1 (default)
*   \note  Value: 0b001b - Allocated to HB2
*   \note  Value: 0b010b - Allocated to HB3
*   \note  Value: 0b011b - Allocated to HB4
*   \note  Value: 0b100b - Allocated to HB5
*   \note  Value: 0b101b - Allocated to HB6
*   \note  Value: 0b110b - Allocated to HB7
*   \note  Value: 0b111b - Allocated to HB8
*
*   \return PWM1_HB value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM1_HB(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PWM1_HB;
}

/** \brief Set PWM channel 1 enable
*
*   \note  Value: 0b0b - PWM1 is disabled (default)
*   \note  Value: 0b1b - PWM1 is enabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_EN(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWMSET.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWMSET_PWM1_EN_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWMSET_PWM1_EN_Pos) & (uint16_t)TLE9210x_Control_PWMSET_PWM1_EN_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
	#if TLE9210x_Variant == TLE92104
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Get PWM channel 1 enable
*
*   \note  Value: 0b0b - PWM1 is disabled (default)
*   \note  Value: 0b1b - PWM1 is enabled
*
*   \return PWM1_EN value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM1_EN(void)
{
	return (uint16_t)TLE9210x->Control_PWMSET.bit.PWM1_EN;
}

/** \brief Set Setting of PWM channels Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWMSET;
		u8_success = 1;
	}
 	#if TLE9210x_Variant == TLE92104
  	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	#endif
	return u8_success;
}

/** \brief Set Deep adaptation enabled
*
*   \note  Value: 0b0b - Deep adaptation disabled (default)
*   \note  Value: 0b1b - Deep adaptation enabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_EN_DEEP_AD(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_EN_DEEP_AD_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_EN_DEEP_AD_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_EN_DEEP_AD_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Deep adaptation enabled
*
*   \note  Value: 0b0b - Deep adaptation disabled (default)
*   \note  Value: 0b1b - Deep adaptation enabled
*
*   \return EN_DEEP_AD value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_EN_DEEP_AD(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.EN_DEEP_AD;
}

/** \brief Set Enable generator check
*
*   \note  Value: 0b0b - Detection of generator mode disabled (default)
*   \note  Value: 0b1b - Detection of generator mode enabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_EN_GEN_CHECK(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_EN_GEN_CHECK_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_EN_GEN_CHECK_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_EN_GEN_CHECK_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Enable generator check
*
*   \note  Value: 0b0b - Detection of generator mode disabled (default)
*   \note  Value: 0b1b - Detection of generator mode enabled
*
*   \return EN_GEN_CHECK value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_EN_GEN_CHECK(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.EN_GEN_CHECK;
}

/** \brief Set Pre-discharge time of PWM channel 3
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPDCHG3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG3_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-discharge time of PWM channel 3
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPDCHG3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG3(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPDCHG3;
}

/** \brief Set Pre-charge time of PWM channel 3
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPCHG3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPCHG3_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPCHG3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-charge time of PWM channel 3
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPCHG3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG3(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPCHG3;
}

/** \brief Set Pre-discharge time of PWM channel 2
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPDCHG2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG2_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-discharge time of PWM channel 2
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPDCHG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG2(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPDCHG2;
}

/** \brief Set Pre-charge time of PWM channel 2
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPCHG2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPCHG2_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPCHG2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-charge time of PWM channel 2
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPCHG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG2(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPCHG2;
}

/** \brief Set Pre-discharge time of PWM channel 1
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPDCHG1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG1_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPDCHG1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-discharge time of PWM channel 1
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPDCHG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG1(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPDCHG1;
}

/** \brief Set Pre-charge time of PWM channel 1
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TPRECHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TPRECHG_TPCHG1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TPRECHG_TPCHG1_Pos) & (uint16_t)TLE9210x_Control_TPRECHG_TPCHG1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Pre-charge time of PWM channel 1
*
*   \note  Value: 0b00b - 125 ns (default)
*   \note  Value: 0b01b - 250 ns
*   \note  Value: 0b10b - 500 ns
*   \note  Value: 0b11b - 1000 ns
*
*   \return TPCHG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG1(void)
{
	return (uint16_t)TLE9210x->Control_TPRECHG.bit.TPCHG1;
}

/** \brief Set PWM pre-charge and pre-discharge time Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TPRECHG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Level of CSA2
*
*   \note  Value: 0b0b - CSA2 is configured as low-side
*   \note  Value: 0b1b - CSA2 is configured as high-side (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA2L(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_CSA2L_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_CSA2L_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_CSA2L_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Level of CSA2
*
*   \note  Value: 0b0b - CSA2 is configured as low-side
*   \note  Value: 0b1b - CSA2 is configured as high-side (default)
*
*   \return CSA2L value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA2L(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.CSA2L;
}

/** \brief Set Level of CSA1
*
*   \note  Value: 0b0b - CSA1 is configured as low-side
*   \note  Value: 0b1b - CSA1 is configured as high-side (default)
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA1L(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_CSA1L_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_CSA1L_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_CSA1L_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Level of CSA1
*
*   \note  Value: 0b0b - CSA1 is configured as low-side
*   \note  Value: 0b1b - CSA1 is configured as high-side (default)
*
*   \return CSA1L value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA1L(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.CSA1L;
}

/** \brief Set Overcurrent filter time for CSO2
*
*   \note  Value: 0b00b - 6 µs (default)
*   \note  Value: 0b01b - 10 µs
*   \note  Value: 0b10b - 50 µs
*   \note  Value: 0b11b - 100 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_OC2FILT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_OC2FILT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_OC2FILT_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_OC2FILT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Overcurrent filter time for CSO2
*
*   \note  Value: 0b00b - 6 µs (default)
*   \note  Value: 0b01b - 10 µs
*   \note  Value: 0b10b - 50 µs
*   \note  Value: 0b11b - 100 µs
*
*   \return OC2FILT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_OC2FILT(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.OC2FILT;
}

/** \brief Set Overcurrent filter time for CSO1
*
*   \note  Value: 0b00b - 6 µs (default)
*   \note  Value: 0b01b - 10 µs
*   \note  Value: 0b10b - 50 µs
*   \note  Value: 0b11b - 100 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_OC1FILT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_OC1FILT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_OC1FILT_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_OC1FILT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Overcurrent filter time for CSO1
*
*   \note  Value: 0b00b - 6 µs (default)
*   \note  Value: 0b01b - 10 µs
*   \note  Value: 0b10b - 50 µs
*   \note  Value: 0b11b - 100 µs
*
*   \return OC1FILT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_OC1FILT(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.OC1FILT;
}

/** \brief Set Disable of CSA2
*
*   \note  Value: 0b0b - CSA2 enabled (default)
*   \note  Value: 0b1b - CSA1 disabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA2_OFF(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_CSA2_OFF_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_CSA2_OFF_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_CSA2_OFF_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Disable of CSA2
*
*   \note  Value: 0b0b - CSA2 enabled (default)
*   \note  Value: 0b1b - CSA1 disabled
*
*   \return CSA2_OFF value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA2_OFF(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.CSA2_OFF;
}

/** \brief Set Disable of CSA1
*
*   \note  Value: 0b0b - CSA1 enabled (default)
*   \note  Value: 0b1b - CSA1 disabled
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA1_OFF(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_CSA1_OFF_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_CSA1_OFF_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_CSA1_OFF_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Disable of CSA1
*
*   \note  Value: 0b0b - CSA1 enabled (default)
*   \note  Value: 0b1b - CSA1 disabled
*
*   \return CSA1_OFF value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA1_OFF(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.CSA1_OFF;
}

#if TLE9210x_Variant == TLE92108
/** \brief Set Control of HB8 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB8IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB8IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB8IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB8IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Control of HB8 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB8IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB8IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB8IDIAG;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Control of HB7 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB7IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB7IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB7IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB7IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Control of HB7 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB7IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB7IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB7IDIAG;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Control of HB6 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB6IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB6IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB6IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB6IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Control of HB6 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB6IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB6IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB6IDIAG;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set Control of HB5 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB5IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB5IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB5IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB5IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Control of HB5 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB5IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB5IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB5IDIAG;
}
#endif

/** \brief Set Control of HB4 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB4IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB4IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB4IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB4IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Control of HB4 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB4IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB4IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB4IDIAG;
}

/** \brief Set Control of HB3 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB3IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB3IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB3IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB3IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Control of HB3 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB3IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB3IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB3IDIAG;
}

/** \brief Set Control of HB2 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB2IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB2IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB2IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB2IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Control of HB2 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB2IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB2IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB2IDIAG;
}

/** \brief Set Control of HB1 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB1IDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_HBIDIAG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_HBIDIAG_HB1IDIAG_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_HBIDIAG_HB1IDIAG_Pos) & (uint16_t)TLE9210x_Control_HBIDIAG_HB1IDIAG_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Control of HB1 off-state current source and current sink
*
*   \note  Value: 0b0b - Pull-down deactivated (default)
*   \note  Value: 0b1b - Pull-down activated
*
*   \return HB1IDIAG value
*/
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB1IDIAG(void)
{
	return (uint16_t)TLE9210x->Control_HBIDIAG.bit.HB1IDIAG;
}

/** \brief Set Half-bridge diagnostic current control Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_HBIDIAG;
		u8_success = 1;
	}
	return u8_success;
}

#if TLE9210x_Variant == TLE92108
/** \brief Set HB8 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 8
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 8
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB8ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB8ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB8ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB8ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB8 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 8
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 8
*
*   \return HB8ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB8ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB8ICHGST;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB7 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 7
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 7
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB7ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB7ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB7ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB7ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB7 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 7
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 7
*
*   \return HB7ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB7ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB7ICHGST;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB6 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is appied to the half-bridge 6
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 6
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB6ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB6ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB6ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB6ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB6 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is appied to the half-bridge 6
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 6
*
*   \return HB6ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB6ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB6ICHGST;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Set HB5 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half=bridge 5
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 5
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB5ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB5ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB5ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB5ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get HB5 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half=bridge 5
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 5
*
*   \return HB5ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB5ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB5ICHGST;
}
#endif

/** \brief Set HB4 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 4
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 4
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB4ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB4ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB4ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB4ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get HB4 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 4
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 4
*
*   \return HB4ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB4ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB4ICHGST;
}

/** \brief Set HB3 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 3
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 3
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB3ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB3ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB3ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB3ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get HB3 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 3
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 3
*
*   \return HB3ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB3ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB3ICHGST;
}

/** \brief Set HB2 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 2
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 2
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB2ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB2ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB2ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB2ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get HB2 Selection of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 2
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 2
*
*   \return HB2ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB2ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB2ICHGST;
}

/** \brief Set HB1 Selction of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 1
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 1
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB1ICHGST(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_HB1ICHGST_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_HB1ICHGST_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_HB1ICHGST_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get HB1 Selction of charge and discharge currents
*
*   \note  Value: 0b0b - The static charge/discharge current 1 is applied to the half-bridge 1
*   \note  Value: 0b1b - The static charge/discharge current 2 is applied to the half-bridge 1
*
*   \return HB1ICHGST value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB1ICHGST(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.HB1ICHGST;
}

/** \brief Set Static gate driver charge and discharge currents 2
*
*   \note  Value: 0b0000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b0001b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b0010b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0011b - Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b0100b - (DEFAULT) Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b0101b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b0110b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0111b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b1000b - Charge current: 37.1 mA | Discharge current: 39.5 mA
*   \note  Value: 0b1001b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b1010b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b1011b - Charge current: 60.2 mA | Discharge current: 62.5 mA
*   \note  Value: 0b1100b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b1101b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b1110b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b1111b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_ICHGST2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_ICHGST2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_ICHGST2_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_ICHGST2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Static gate driver charge and discharge currents 2
*
*   \note  Value: 0b0000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b0001b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b0010b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0011b - Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b0100b - (DEFAULT) Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b0101b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b0110b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0111b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b1000b - Charge current: 37.1 mA | Discharge current: 39.5 mA
*   \note  Value: 0b1001b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b1010b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b1011b - Charge current: 60.2 mA | Discharge current: 62.5 mA
*   \note  Value: 0b1100b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b1101b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b1110b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b1111b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*
*   \return ICHGST2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_ICHGST2(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.ICHGST2;
}

/** \brief Set Static gate driver charge and discharge currents 1
*
*   \note  Value: 0b0000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b0001b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b0010b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0011b - Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b0100b - (DEFAULT) Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b0101b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b0110b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0111b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b1000b - Charge current: 37.1 mA | Discharge current: 39.5 mA
*   \note  Value: 0b1001b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b1010b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b1011b - Charge current: 60.2 mA | Discharge current: 62.5 mA
*   \note  Value: 0b1100b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b1101b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b1110b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b1111b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_ICHGST1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_ST_ICHG.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_ST_ICHG_ICHGST1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_ST_ICHG_ICHGST1_Pos) & (uint16_t)TLE9210x_Control_ST_ICHG_ICHGST1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Static gate driver charge and discharge currents 1
*
*   \note  Value: 0b0000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b0001b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b0010b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0011b - Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b0100b - (DEFAULT) Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b0101b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b0110b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b0111b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b1000b - Charge current: 37.1 mA | Discharge current: 39.5 mA
*   \note  Value: 0b1001b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b1010b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b1011b - Charge current: 60.2 mA | Discharge current: 62.5 mA
*   \note  Value: 0b1100b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b1101b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b1110b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b1111b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*
*   \return ICHGST1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_ICHGST1(void)
{
	return (uint16_t)TLE9210x->Control_ST_ICHG.bit.ICHGST1;
}

/** \brief Set Charge current for static half-bridges Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_ST_ICHG;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Initial precharge current of PWM Channel 3
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT3_Pos) & (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial precharge current of PWM Channel 3
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return PCHGINIT3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.bit.PCHGINIT3;
}

/** \brief Set Initial precharge current of PWM channel 2
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT2_Pos) & (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial precharge current of PWM channel 2
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return PCHGINIT2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.bit.PCHGINIT2;
}

/** \brief Set Initial precharge current of PWM channel 1
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT1_Pos) & (uint16_t)TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial precharge current of PWM channel 1
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return PCHGINIT1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PCHG_INIT.bit.PCHGINIT1;
}

/** \brief Set Precharge current initialization Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Gate driver charge current of PWM Channel 3 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_ACT_ICHG3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG3_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge current of PWM Channel 3 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return ICHG3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.bit.ICHG3;
}

/** \brief Set Gate driver charge current of PWM Channel 2 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_ACT_ICHG2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG2_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge current of PWM Channel 2 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return ICHG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.bit.ICHG2;
}

/** \brief Set Gate driver charge current of PWM Channel 1 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_ACT_ICHG1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG1_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_ACT_ICHG1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge current of PWM Channel 1 (ACTIVE MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA
*   \note  Value: 0b10001b - Charge current: 40.7 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA
*
*   \return ICHG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_ACT.bit.ICHG1;
}

/** \brief Set Charge current for half-bridges in PWM (active MOSFETs) Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Gate driver charge and discharge currents of PWM Channel 3 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG3_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_FW_ICHG3_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG3_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG3_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge and discharge currents of PWM Channel 3 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \return ICHG3_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG3_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_FW.bit.ICHG3_FW;
}

/** \brief Set Gate driver charge and discharge currents of PWM Channel 2 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG2_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_FW_ICHG2_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG2_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG2_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge and discharge currents of PWM Channel 2 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \return ICHG2_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG2_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_FW.bit.ICHG2_FW;
}

/** \brief Set Gate driver charge and discharge currents of PWM Channel 1 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG1_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHG_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHG_FW_ICHG1_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG1_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHG_FW_ICHG1_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Gate driver charge and discharge currents of PWM Channel 1 (FW MOSFET)
*
*   \note  Value: 0b00000b - Charge current: 1.0 mA | Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Charge current: 1.5 mA | Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Charge current: 2.0 mA | Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Charge current: 3.2 mA | Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Charge current: 4.5 mA | Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Charge current: 6.3 mA | Discharge current: 7.5 mA
*   \note  Value: 0b00110b - (DEFAULT) Charge current: 8.0 mA | Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Charge current: 10.3 mA | Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Charge current: 12.5 mA | Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Charge current: 15.1 mA | Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Charge current: 17.8 mA | Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Charge current: 20.8 mA | Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Charge current: 23.9 mA | Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Charge current: 27.0 mA | Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Charge current: 30.0 mA | Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Charge current: 33.5 mA | Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Charge current: 37.1 mA | Discharge current: 39.5
*   \note  Value: 0b10001b - Charge current: 40.7 mA | Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Charge current: 44.3 mA | Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Charge current: 48.3 mA | Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Charge current: 52.3 mA | Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Charge current: 56.2 mA | Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Charge current: 60.1 mA | Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Charge current: 64.2 mA | Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Charge current: 68.3 mA | Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Charge current: 72.5 mA | Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Charge current: 76.8 mA | Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Charge current: 81.4 mA | Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Charge current: 86.0 mA | Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Charge current: 91.0 mA | Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Charge current: 96.0 mA | Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Charge current: 100 mA | Discharge current: 100 mA
*
*   \return ICHG1_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG1_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHG_FW.bit.ICHG1_FW;
}

/** \brief Set Charge current for half-bridges in PWM (FW MOSFETs) Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHG_FW;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Capacitor connected to the current sense amplifier outputs
*
*   \note  Value: 0b0b - Capacitor connected to CSO less than 100 pF (default)
*   \note  Value: 0b1b - Capacitor connected to CSO less than 400 pF
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_CCSO(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_IDCHG_ACT_CCSO_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_CCSO_Pos) & (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_CCSO_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Capacitor connected to the current sense amplifier outputs
*
*   \note  Value: 0b0b - Capacitor connected to CSO less than 100 pF (default)
*   \note  Value: 0b1b - Capacitor connected to CSO less than 400 pF
*
*   \return CCSO value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_CCSO(void)
{
	return (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.bit.CCSO;
}

/** \brief Set Discharge current for PWM Channel 3 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_IDCHG_ACT_IDCHG3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG3_Pos) & (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Discharge current for PWM Channel 3 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return IDCHG3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.bit.IDCHG3;
}

/** \brief Set Discharge current for PWM Channel 2 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_IDCHG_ACT_IDCHG2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG2_Pos) & (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Discharge current for PWM Channel 2 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return IDCHG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.bit.IDCHG2;
}

/** \brief Set Discharge current for PWM Channel 1 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_IDCHG_ACT_IDCHG1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG1_Pos) & (uint16_t)TLE9210x_Control_PWM_IDCHG_ACT_IDCHG1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Discharge current for PWM Channel 1 (Active MOSFET)
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - (DEFAULT) Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return IDCHG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_IDCHG_ACT.bit.IDCHG1;
}

/** \brief Set Discharge current of active MOSFETs in PWM operation Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Capacitor connected to the current sense amplifier outputs
*
*   \note  Value: 0b0b - Capacitor connected to CSO less than 100 pF (default)
*   \note  Value: 0b1b - Capacitor connected to CSO less than 400 pF
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_CCSO(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PDCHG_INIT_CCSO_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_CCSO_Pos) & (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_CCSO_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Capacitor connected to the current sense amplifier outputs
*
*   \note  Value: 0b0b - Capacitor connected to CSO less than 100 pF (default)
*   \note  Value: 0b1b - Capacitor connected to CSO less than 400 pF
*
*   \return CCSO value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_CCSO(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.bit.CCSO;
}

/** \brief Set Initial predischarge current of PWM Channel 3
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT3_Pos) & (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial predischarge current of PWM Channel 3
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return PDCHGINIT3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.bit.PDCHGINIT3;
}

/** \brief Set Initial predischarge current of PWM Channel 2
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT2_Pos) & (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial predischarge current of PWM Channel 2
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return PDCHGINIT2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.bit.PDCHGINIT2;
}

/** \brief Set Initial predischarge current of PWM Channel 1
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT1_Pos) & (uint16_t)TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Initial predischarge current of PWM Channel 1
*
*   \note  Value: 0b00000b - Discharge current: 1.0 mA
*   \note  Value: 0b00001b - Discharge current: 1.9 mA
*   \note  Value: 0b00010b - Discharge current: 2.8 mA
*   \note  Value: 0b00011b - Discharge current: 4.3 mA
*   \note  Value: 0b00100b - Discharge current: 5.7 mA
*   \note  Value: 0b00101b - Discharge current: 7.5 mA
*   \note  Value: 0b00110b - Discharge current: 9.4 mA
*   \note  Value: 0b00111b - Discharge current: 11.8 mA
*   \note  Value: 0b01000b - Discharge current: 14.2 mA
*   \note  Value: 0b01001b - Discharge current: 17.0 mA
*   \note  Value: 0b01010b - Discharge current: 19.7 mA
*   \note  Value: 0b01011b - Discharge current: 22.9 mA
*   \note  Value: 0b01100b - (DEFAULT) Discharge current: 26.0 mA
*   \note  Value: 0b01101b - Discharge current: 29.0 mA
*   \note  Value: 0b01110b - Discharge current: 32.0 mA
*   \note  Value: 0b01111b - Discharge current: 35.8 mA
*   \note  Value: 0b10000b - Discharge current: 39.5 mA
*   \note  Value: 0b10001b - Discharge current: 43.1 mA
*   \note  Value: 0b10010b - Discharge current: 46.8 mA
*   \note  Value: 0b10011b - Discharge current: 50.8 mA
*   \note  Value: 0b10100b - Discharge current: 54.7 mA
*   \note  Value: 0b10101b - Discharge current: 58.6 mA
*   \note  Value: 0b10110b - Discharge current: 62.5 mA
*   \note  Value: 0b10111b - Discharge current: 66.6 mA
*   \note  Value: 0b11000b - Discharge current: 70.6 mA
*   \note  Value: 0b11001b - Discharge current: 74.6 mA
*   \note  Value: 0b11010b - Discharge current: 78.5 mA
*   \note  Value: 0b11011b - Discharge current: 82.8 mA
*   \note  Value: 0b11100b - Discharge current: 87.0 mA
*   \note  Value: 0b11101b - Discharge current: 91.0 mA
*   \note  Value: 0b11110b - Discharge current: 95.0 mA
*   \note  Value: 0b11111b - Discharge current: 100 mA
*
*   \return PDCHGINIT1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_PDCHG_INIT.bit.PDCHGINIT1;
}

/** \brief Set Predischarge current initialization Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT(uint16_t u16_data)
{
	uint8_t u8_success = 0;

    if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1u)
    {
        u8_success = 2;
    }
    else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Blank timme - tBLANK4 Active
*
*   \note  Value: 0b000b - Active drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - Active drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - Active drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - Active drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - Active drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - Active drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - Active drain-Source overvoltage blank time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank timme - tBLANK4 Active
*
*   \note  Value: 0b000b - Active drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - Active drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - Active drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - Active drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - Active drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - Active drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - Active drain-Source overvoltage blank time: 16 µs
*
*   \return TBLANK4_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.TBLANK4_ACT;
}

/** \brief Set Cross-current protection - tCCP4 Active
*
*   \note  Value: 0b000b - Active cross-current protection time: 375 ns
*   \note  Value: 0b001b - Active cross-current protection time: 625 ns
*   \note  Value: 0b010b - Active cross-current protection time: 1 µs
*   \note  Value: 0b011b - Active cross-current protection time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active cross-current protection time: 2 µs
*   \note  Value: 0b101b - Active cross-current protection time: 3 µs
*   \note  Value: 0b110b - Active cross-current protection time: 4 µs
*   \note  Value: 0b111b - Active cross-current protection time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP4 Active
*
*   \note  Value: 0b000b - Active cross-current protection time: 375 ns
*   \note  Value: 0b001b - Active cross-current protection time: 625 ns
*   \note  Value: 0b010b - Active cross-current protection time: 1 µs
*   \note  Value: 0b011b - Active cross-current protection time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active cross-current protection time: 2 µs
*   \note  Value: 0b101b - Active cross-current protection time: 3 µs
*   \note  Value: 0b110b - Active cross-current protection time: 4 µs
*   \note  Value: 0b111b - Active cross-current protection time: 16 µs
*
*   \return TCCP4_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.TCCP4_ACT;
}

/** \brief Set Blank time - tBLANK3 Active
*
*   \note  Value: 0b000b - Active drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - Active drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - Active drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - Active drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - Active drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - Active drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - Active drain-Source overvoltage blank time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time - tBLANK3 Active
*
*   \note  Value: 0b000b - Active drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - Active drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - Active drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - Active drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) Active drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - Active drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - Active drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - Active drain-Source overvoltage blank time: 16 µs
*
*   \return TBLANK3_ACT value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.TBLANK3_ACT;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.ICHGMAX3;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.ICHGMAX2;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 0u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 18.8 mA | Discharge: 19.7 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.bit.ICHGMAX1;
}

/** \brief Set Max. pre-charge / pre-discharge currents for half-bridges in PWM tCCP and tBLANK setting for active MOSFETs Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 0)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Blank time -tBLANK4 Freewheeling
*
*   \note  Value: 0b000b - FW Drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - FW Drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - FW Drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - FW Drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW Drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - FW Drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - FW Drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - FW Drain-Source overvoltage blank time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time -tBLANK4 Freewheeling
*
*   \note  Value: 0b000b - FW Drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - FW Drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - FW Drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - FW Drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW Drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - FW Drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - FW Drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - FW Drain-Source overvoltage blank time: 16 µs
*
*   \return TBLANK4_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.TBLANK4_FW;
}

/** \brief Set Cross-current protection - tCCP4 Freewheeling
*
*   \note  Value: 0b000b - FW cross-current protection time: 375 ns
*   \note  Value: 0b001b - FW cross-current protection time: 625 ns
*   \note  Value: 0b010b - FW cross-current protection time: 1 µs
*   \note  Value: 0b011b - FW cross-current protection time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW cross-current protection time: 2 µs
*   \note  Value: 0b101b - FW cross-current protection time: 3 µs
*   \note  Value: 0b110b - FW cross-current protection time: 4 µs
*   \note  Value: 0b111b - FW cross-current protection time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Cross-current protection - tCCP4 Freewheeling
*
*   \note  Value: 0b000b - FW cross-current protection time: 375 ns
*   \note  Value: 0b001b - FW cross-current protection time: 625 ns
*   \note  Value: 0b010b - FW cross-current protection time: 1 µs
*   \note  Value: 0b011b - FW cross-current protection time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW cross-current protection time: 2 µs
*   \note  Value: 0b101b - FW cross-current protection time: 3 µs
*   \note  Value: 0b110b - FW cross-current protection time: 4 µs
*   \note  Value: 0b111b - FW cross-current protection time: 16 µs
*
*   \return TCCP4_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.TCCP4_FW;
}

/** \brief Set Blank time -tBLANK3 Freewheeling
*
*   \note  Value: 0b000b - FW Drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - FW Drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - FW Drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - FW Drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW Drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - FW Drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - FW Drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - FW Drain-Source overvoltage blank time: 16 µs
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Blank time -tBLANK3 Freewheeling
*
*   \note  Value: 0b000b - FW Drain-Source overvoltage blank time: 625 ns
*   \note  Value: 0b001b - FW Drain-Source overvoltage blank time: 1 µs
*   \note  Value: 0b010b - FW Drain-Source overvoltage blank time: 1.25 µs
*   \note  Value: 0b011b - FW Drain-Source overvoltage blank time: 1.5 µs
*   \note  Value: 0b100b - (DEFAULT) FW Drain-Source overvoltage blank time: 2 µs
*   \note  Value: 0b101b - FW Drain-Source overvoltage blank time: 3 µs
*   \note  Value: 0b110b - FW Drain-Source overvoltage blank time: 4 µs
*   \note  Value: 0b111b - FW Drain-Source overvoltage blank time: 16 µs
*
*   \return TBLANK3_FW value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.TBLANK3_FW;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.ICHGMAX3;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.ICHGMAX2;
}

/** \brief Set Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if((TLE9210x_s_deviceDriver.fp_setReg == NULL) && (TLE9210x->Control_GENCTRL1.bit.REG_BANK == 1u))
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1_Pos) & (uint16_t)TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Get Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases
*
*   \note  Value: 0b00b - (DEFAULT) Charge: 19 mA | Discharge: 19 mA
*   \note  Value: 0b01b - Charge: 41 mA | Discharge: 43 mA
*   \note  Value: 0b10b - Charge: 77 mA | Discharge: 79 mA
*   \note  Value: 0b11b - Charge: 100 mA | Discharge: 100 mA
*
*   \return ICHGMAX1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1(void)
{
	return (uint16_t)TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.bit.ICHGMAX1;
}

/** \brief Set Max. pre-charge / pre-discharge currents for half-bridges in PWM tCCP and tBLANK setting for FW MOSFETs Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful, 2: request successful but register bank has not the right value)
*/
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x->Control_GENCTRL1.bit.REG_BANK != 1)
	{
		u8_success = 2;
	}
	else if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW;
		u8_success = 1;
	}
	else
	{
		// MISRA
	}
	return u8_success;
}

/** \brief Set Turn-off delay time of PWM Channel 1 = 62.5 x TDOFF1[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1_TDOFF1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF1_TDOFF1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF1_TDOFF1_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF1_TDOFF1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-off delay time of PWM Channel 1 = 62.5 x TDOFF1[7:0] ns
*
*
*   \return TDOFF1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF1_TDOFF1(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF1.bit.TDOFF1;
}

/** \brief Set Turn-on delay time of PWM Channel 1 = 62.5 x TDON1[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1_TDON1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF1.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF1_TDON1_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF1_TDON1_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF1_TDON1_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-on delay time of PWM Channel 1 = 62.5 x TDON1[7:0] ns
*
*
*   \return TDON1 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF1_TDON1(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF1.bit.TDON1;
}

/** \brief Set Turn-on and turn-off delays for PWM channel 1 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF1;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Turn-off delay time of PWM Channel 2 = 62.5 x TDOFF2[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2_TDOFF2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF2_TDOFF2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF2_TDOFF2_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF2_TDOFF2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-off delay time of PWM Channel 2 = 62.5 x TDOFF2[7:0] ns
*
*
*   \return TDOFF2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF2_TDOFF2(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF2.bit.TDOFF2;
}

/** \brief Set Turn-on delay time of PWM Channel 2 = 62.5 x TDON2[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2_TDON2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF2.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF2_TDON2_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF2_TDON2_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF2_TDON2_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-on delay time of PWM Channel 2 = 62.5 x TDON2[7:0] ns
*
*
*   \return TDON2 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF2_TDON2(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF2.bit.TDON2;
}

/** \brief Set Turn-on and turn-off delays for PWM channel 2 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF2;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set Turn-off delay time of PWM Channel 3 = 62.5 x TDOFF3[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3_TDOFF3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF3.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF3_TDOFF3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF3_TDOFF3_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF3_TDOFF3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF3;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-off delay time of PWM Channel 3 = 62.5 x TDOFF3[7:0] ns
*
*
*   \return TDOFF3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF3_TDOFF3(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF3.bit.TDOFF3;
}

/** \brief Set Turn-on delay time of PWM Channel 3 = 62.5 x TDON3[7:0] ns
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3_TDON3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_TDON_OFF3.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_TDON_OFF3_TDON3_Mask)) | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_TDON_OFF3_TDON3_Pos) & (uint16_t)TLE9210x_Control_TDON_OFF3_TDON3_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF3;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get Turn-on delay time of PWM Channel 3 = 62.5 x TDON3[7:0] ns
*
*
*   \return TDON3 value
*/
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF3_TDON3(void)
{
	return (uint16_t)TLE9210x->Control_TDON_OFF3.bit.TDON3;
}

/** \brief Set Turn-on and turn-off delays for PWM channel 3 Register
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_data;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_TDON_OFF3;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Set CSA_OC_SH_HB6_PWM4_EN
*
*
*   \param u16_data : value to be written
*   \return u8_success : (0: request not successful, 1: request successful)
*/
uint8_t TLE9210x_FuncLayer_set_Control_CSA_OC_SH_HB6_PWM4_EN(uint16_t u16_data)
{
	uint8_t u8_success = 0;
	uint16_t u16_reg_temp = 0;
	if(TLE9210x_s_deviceDriver.fp_setReg == NULL)
	{
		u16_reg_temp = (uint16_t)TLE9210x->Control_CSA_OC_SH.reg;
		u16_reg_temp = (uint16_t)((u16_reg_temp & (uint16_t)(~TLE9210x_Control_CSA_OC_SH_TDOFF3_HB6_PWM4_EN_Mask)) 
            | ((uint16_t)(u16_data << (uint16_t)TLE9210x_Control_CSA_OC_SH_TDOFF3_HB6_PWM4_EN_Pos) 
            & (uint16_t)TLE9210x_Control_CSA_OC_SH_TDOFF3_HB6_PWM4_EN_Mask));
		TLE9210x_s_deviceDriver.u16_setBitValue = u16_reg_temp;
		TLE9210x_s_deviceDriver.fp_setReg = &TLE9210x_RegLayer_set_Control_CSA_OC_SH;
		u8_success = 1;
	}
	return u8_success;
}

/** \brief Get CSA_OC_SH_HB6_PWM4_EN
*
*
*   \return CSA_OC_SH_HB6_PWM4_EN value
*/
uint16_t TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN(void)
{
	return (uint16_t)TLE9210x->Control_CSA_OC_SH.bit.HB6_PWM4_EN;
}

/** \brief Get DS overvoltage while the bridge driver is in passive mode
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of any low-sides
*   \note  Value: 0b1b - Overvoltage on drain-source of one of the low-side is detected
*
*   \return PASS_VDSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PASS_VDSOV(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.PASS_VDSOV;
}

/** \brief Get Watchdog Monitoring
*
*   \note  Value: 0b00b - (DEFAULT) WD Timer is between [0-25%] of the WD period
*   \note  Value: 0b01b - WD Timer is between [25-50%] of the WD period
*   \note  Value: 0b10b - WD Timer is between [50-75%] of the WD period
*   \note  Value: 0b11b - WD Timer is between [75-100%] of the WD period
*
*   \return WDMON value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_WDMON(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.WDMON;
}

/** \brief Serve Watchdog function. 
 * 	\note Call this function to serve the Watchdog
*/
void TLE9210x_FuncLayer_Trigger_Watchdog(void)
{
    //Invert the Watchdog-Trigger-Bit
	if (TLE9210x_FuncLayer_get_Control_GENCTRL1_WDTRIG() == 0x01)
	{
		(void)TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(0x0u);
	}
	else
	{
		(void)TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(0x01);
	}
}

/** \brief Get Status of PWM3 input
*
*   \note  Value: 0b0b - (DEFAULT) PWM3 is low
*   \note  Value: 0b1b - PWM3 is high
*
*   \return PWM3STAT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM3STAT(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.PWM3STAT;
}

/** \brief Get Status of PWM2 input
*
*   \note  Value: 0b0b - (DEFAULT) PWM2 is low
*   \note  Value: 0b1b - PWM2 is high
*
*   \return PWM2STAT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM2STAT(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.PWM2STAT;
}

/** \brief Get Status of PWM1 input
*
*   \note  Value: 0b0b - (DEFAULT) PWM1 is low
*   \note  Value: 0b1b - PWM1 is high
*
*   \return PWM1STAT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM1STAT(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.PWM1STAT;
}

/** \brief Get PWM channel 3 - Regulation of turn-on and turn-off delays
*
*   \note  Value: 0b0b - (DEFAULT) The turn-on delay or the turn-off delay are not in regulation
*   \note  Value: 0b1b - The turn-on and turn-off delays are in regulation
*
*   \return TDREG3 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG3(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.TDREG3;
}

/** \brief Get PWM channel 2 - Regulation of turn-on and turn-off delays
*
*   \note  Value: 0b0b - (DEFAULT) The turn-on delay or the turn-off delay are not in regulation
*   \note  Value: 0b1b - The turn-on and turn-off delays are in regulation
*
*   \return TDREG2 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG2(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.TDREG2;
}

/** \brief Get PWM channel 1 - Regulation of turn-on and turn-off delays
*
*   \note  Value: 0b0b - (DEFAULT) The turn-on delay or the turn-off delay are not in regulation
*   \note  Value: 0b1b - The turn-on and turn-off delays are in regulation
*
*   \return TDREG1 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG1(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.TDREG1;
}

/** \brief Get Thermal shutdown
*
*   \note  Value: 0b0b - (DFEAULT) No thermal shutdown is detected
*   \note  Value: 0b1b - A thermal shutdown is detected
*
*   \return TSD value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TSD(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.TSD;
}

/** \brief Get Thermal Warning
*
*   \note  Value: 0b0b - (DEFAULT) No therrmal warning is detected
*   \note  Value: 0b1b - A thermal warning is detected
*
*   \return TW value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TW(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.TW;
}

/** \brief Get Overcurrent detection of CSO2
*
*   \note  Value: 0b0b - (DEFAULT) No overcurrent detection on CSO2
*   \note  Value: 0b1b - Overcurrent detected on CSO2
*
*   \return OC2 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_OC2(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.OC2;
}

/** \brief Get Overcurrent detection of CSO1
*
*   \note  Value: 0b0b - No overcurrent detection on CSO1
*   \note  Value: 0b1b - Overcurrent detected on CSO1
*
*   \return OC1 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_OC1(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.OC1;
}

/** \brief Get VS Overvoltage
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on VS detected
*   \note  Value: 0b1b - Overvoltage on VS detected
*
*   \return VSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_VSOV(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.VSOV;
}

/** \brief Get VS Undervoltage
*
*   \note  Value: 0b0b - (DEFAULT) No undervoltage on VS detected
*   \note  Value: 0b1b - Undervoltage on VS detected
*
*   \return VSUV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_VSUV(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.VSUV;
}

/** \brief Get Charge Pump Undervoltage
*
*   \note  Value: 0b0b - (DEFAULT) No charge pump undervoltage
*   \note  Value: 0b1b - A charge pump undervoltage is detected
*
*   \return CPUV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_CPUV(void)
{
	return (uint16_t)TLE9210x->Status_GENSTAT.bit.CPUV;
}

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on low-side 8
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 8
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 8 detected
*
*   \return LS8DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS8DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS8DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on high-side 8
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 8
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 8 detected
*
*   \return HS8DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS8DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS8DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on low-side 7
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 7
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 7 detected
*
*   \return LS7DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS7DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS7DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on high-side 7
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 7
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 7 detected
*
*   \return HS7DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS7DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS7DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on low-side 6
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 6
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 6 detected
*
*   \return LS6DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS6DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS6DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on high-side 6
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 6
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 6 detected
*
*   \return HS6DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS6DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS6DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on low-side 5
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 5
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 5 detected
*
*   \return LS5DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS5DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS5DSOV;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Drain-Source overvoltage on high-side 5
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 5
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 5 detected
*
*   \return HS5DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS5DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS5DSOV;
}
#endif

/** \brief Get Drain-Source overvoltage on low-side 4
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 4
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 4 detected
*
*   \return LS4DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS4DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS4DSOV;
}

/** \brief Get Drain-Source overvoltage on high-side 4
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 4
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 4 detected
*
*   \return HS4DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS4DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS4DSOV;
}

/** \brief Get Drain-Source overvoltage on low-side 3
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 3
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 3 detected
*
*   \return LS3DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS3DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS3DSOV;
}

/** \brief Get Drain-Source overvoltage on high-side 3
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 3
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 3 detected
*
*   \return HS3DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS3DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS3DSOV;
}

/** \brief Get Drain-Source overvoltage on low-side 2
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 2
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 2 detected
*
*   \return LS2DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS2DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS2DSOV;
}

/** \brief Get Drain-Source overvoltage on high-side 2
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 2
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 2 detected
*
*   \return HS2DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS2DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS2DSOV;
}

/** \brief Get Drain-Source overvoltage on low-side 1
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of low-side 1
*   \note  Value: 0b1b - Overvoltage on drain-source of low-side 1 detected
*
*   \return LS1DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS1DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.LS1DSOV;
}

/** \brief Get Drain-Source overvoltage on high-side 1
*
*   \note  Value: 0b0b - (DEFAULT) No overvoltage on drain-source of high-side 1
*   \note  Value: 0b1b - Overvoltage on drain-source of high-side 1 detected
*
*   \return HS1DSOV value
*/
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS1DSOV(void)
{
	return (uint16_t)TLE9210x->Status_DSOV.bit.HS1DSOV;
}

#if TLE9210x_Variant == TLE92108
/** \brief Get PWM Error on HB8
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB8
*
*   \return HB8PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB8PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB8PWME;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get PWM Error on HB7
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB7
*
*   \return HB7PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB7PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB7PWME;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get PWM Error on HB6
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB6
*
*   \return HB6PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB6PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB6PWME;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get PWM Error on HB5
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB5
*
*   \return HB5PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB5PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB5PWME;
}
#endif

/** \brief Get PWM Error on HB4
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB4
*
*   \return HB4PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB4PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB4PWME;
}

/** \brief Get PWM Error on HB3
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB3
*
*   \return HB3PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB3PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB3PWME;
}

/** \brief Get PWM Error on HB2
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB2
*
*   \return HB2PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB2PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB2PWME;
}

/** \brief Get PWM Error on HB1
*
*   \note  Value: 0b0b - (DEFAULT) No PWM error
*   \note  Value: 0b1b - More than one activated PWM channels is mapped to HB1
*
*   \return HB1PWME value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB1PWME(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB1PWME;
}

#if TLE9210x_Variant == TLE92108
/** \brief Get Voltage level at SH8 when HB8MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH8|>V_VDSMONTHx if HB8D = 0 | |VCSIN1-VSH8|>V_VDSMONTHx if HB8D = 1
*   \note  Value: 0b1b - High: |VDH-VSH8| [less than] V_VDSMONTHx if HB8D = 0 | |VCSIN1-VSH8| [less than] V_VDSMONTHx if HB8D = 1
*
*   \return HB8VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB8VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB8VOUT;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Voltage level at SH7 when HB7MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH7|>V_VDSMONTHx if HB7D = 0 | |VCSIN1-VSH7|>V_VDSMONTHx if HB7D = 1
*   \note  Value: 0b1b - High: |VDH-VSH7| [less than] V_VDSMONTHx if HB7D = 0 | |VCSIN1-VSH7| [less than] V_VDSMONTHx if HB7D = 1
*
*   \return HB7VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB7VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB7VOUT;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Voltage level at SH6 when HB6MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH6|>V_VDSMONTHx if HB6D = 0 | |VCSIN1-VSH6|>V_VDSMONTHx if HB6D = 1
*   \note  Value: 0b1b - High: |VDH-VSH6| [less than] V_VDSMONTHx if HB6D = 0 | |VCSIN1-VSH6| [less than] V_VDSMONTHx if HB6D = 1
*
*   \return HB6VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB6VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB6VOUT;
}
#endif

#if TLE9210x_Variant == TLE92108
/** \brief Get Voltage level at SH5 when HB5MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH5|>V_VDSMONTHx if HB5D = 0 | |VCSIN1-VSH5|>V_VDSMONTHx if HB5D = 1
*   \note  Value: 0b1b - High: |VDH-VSH5| [less than] V_VDSMONTHx if HB5D = 0 | |VCSIN1-VSH5| [less than] V_VDSMONTHx if HB5D = 1
*
*   \return HB5VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB5VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB5VOUT;
}
#endif

/** \brief Get Voltage level at SH4 when HB4MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH4|>V_VDSMONTHx if HB4D = 0 | |VCSIN1-VSH4|>V_VDSMONTHx if HB4D = 1
*   \note  Value: 0b1b - High: |VDH-VSH4| [less than] V_VDSMONTHx if HB4D = 0 | |VCSIN1-VSH4| [less than] V_VDSMONTHx if HB4D = 1
*
*   \return HB4VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB4VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB4VOUT;
}

/** \brief Get Voltage level at SH8 when HB3MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH3|>V_VDSMONTHx if HB3D = 0 | |VCSIN1-VSH3|>V_VDSMONTHx if HB3D = 1
*   \note  Value: 0b1b - High: |VDH-VSH3| [less than] V_VDSMONTHx if HB3D = 0 | |VCSIN1-VSH3| [less than] V_VDSMONTHx if HB3D = 1
*
*   \return HB3VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB3VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB3VOUT;
}

/** \brief Get Voltage level at SH2 when HB2MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH2|>V_VDSMONTHx if HB2D = 0 | |VCSIN1-VSH2|>V_VDSMONTHx if HB2D = 1
*   \note  Value: 0b1b - High: |VDH-VSH2| [less than] V_VDSMONTHx if HB2D = 0 | |VCSIN1-VSH2| [less than] V_VDSMONTHx if HB2D = 1
*
*   \return HB2VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB2VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB2VOUT;
}

/** \brief Get Voltage level at SH1 when HB1MODE[1:0] = (0,0) or (1,1)
*
*   \note  Value: 0b0b - Low: |VDH-VSH1|>V_VDSMONTHx if HB1D = 0 | |VCSIN1-VSH1|>V_VDSMONTHx if HB1D = 1
*   \note  Value: 0b1b - High: |VDH-VSH1| [less than] V_VDSMONTHx if HB1D = 0 | |VCSIN1-VSH1| [less than] V_VDSMONTHx if HB1D = 1
*
*   \return HB1VOUT value
*/
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB1VOUT(void)
{
	return (uint16_t)TLE9210x->Status_HBVOUT_PWMERR.bit.HB1VOUT;
}

/** \brief Get Effective MOSFET turn-off delay of PWM Channel 1 = 62.5 x TDOFF1EFF[7:0] ns
*
*
*   \return TDOFF1EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF1_TDOFF1EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF1.bit.TDOFF1EFF;
}

/** \brief Get Effective MOSFET turn-on delay of PWM Channel 1 = 62.5 x TDON1EFF[7:0] ns
*
*
*   \return TDON1EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF1_TDON1EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF1.bit.TDON1EFF;
}

/** \brief Get Effective MOSFET turn-off delay of PWM Channel 2 = 62.5 x TDOFF2EFF[7:0] ns
*
*
*   \return TDOFF2EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF2_TDOFF2EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF2.bit.TDOFF2EFF;
}

/** \brief Get Effective MOSFET turn-on delay of PWM Channel 2 = 62.5 x TDON2EFF[7:0] ns
*
*
*   \return TDON2EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF2_TDON2EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF2.bit.TDON2EFF;
}

/** \brief Get Effective MOSFET turn-off delay of PWM Channel 3 = 62.5 x TDOFF3EFF[7:0] ns
*
*
*   \return TDOFF3EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF3_TDOFF3EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF3.bit.TDOFF3EFF;
}

/** \brief Get Effective MOSFET turn-on delay of PWM Channel 3 = 62.5 x TDON3EFF[7:0] ns
*
*
*   \return TDON3EFF value
*/
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF3_TDON3EFF(void)
{
	return (uint16_t)TLE9210x->Status_EFF_TDON_OFF3.bit.TDON3EFF;
}

/** \brief Get MOSFET fall time of PWM Channel 1 = 62.5 x TFALL1[7:0] ns
*
*
*   \return TFALL1 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL1_TFALL1(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL1.bit.TFALL1;
}

/** \brief Get MOSFET rise time of PWM Channel 1 = 62.5 x TRISE1[7:0] ns
*
*
*   \return TRISE1 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL1_TRISE1(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL1.bit.TRISE1;
}

/** \brief Get MOSFET fall time of PWM Channel 2 = 62.5 x TFALL2[7:0] ns
*
*
*   \return TFALL2 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL2_TFALL2(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL2.bit.TFALL2;
}

/** \brief Get MOSFET rise time of PWM Channel 2 = 62.5 x TRISE2[7:0] ns
*
*
*   \return TRISE2 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL2_TRISE2(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL2.bit.TRISE2;
}

/** \brief Get MOSFET fall time of PWM Channel 3 = 62.5 x TFALL3[7:0] ns
*
*
*   \return TFALL3 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL3_TFALL3(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL3.bit.TFALL3;
}

/** \brief Get MOSFET rise time of PWM Channel 3 = 62.5 x TRISE3[7:0] ns
*
*
*   \return TRISE3 value
*/
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL3_TRISE3(void)
{
	return (uint16_t)TLE9210x->Status_TRISE_FALL3.bit.TRISE3;
}

#if TLE9210x_Variant == TLE92108
/** \brief Get Device derivative identifier
*
*   \note  Value: 0b000b - Reserved
*   \note  Value: 0b001b - Device: TLE92108-232
*   \note  Value: 0b010b - Reserved
*   \note  Value: 0b011b - Device: TLE92108-231
*   \note  Value: 0b100b - Reserved
*   \note  Value: 0b101b - Reserved
*   \note  Value: 0b110b - Reserved
*   \note  Value: 0b111b - Reserved
*
*   \return DEV_ID value
*/
#else
/** \brief Get Device derivative identifier
*
*   \note  Value: 0b000b - Reserved
*   \note  Value: 0b001b - Device: TLE92104-232
*   \note  Value: 0b010b - Reserved
*   \note  Value: 0b011b - Reserved
*   \note  Value: 0b100b - Reserved
*   \note  Value: 0b101b - Reserved
*   \note  Value: 0b110b - Reserved
*   \note  Value: 0b111b - Device: TLE92104-131
*
*   \return DEV_ID value
*/
#endif
uint16_t TLE9210x_FuncLayer_get_Status_DEVID_DEV_ID(void)
{
	return (uint16_t)TLE9210x->Status_DEVID.bit.DEV_ID;
}

/** @}*/ /* End of group TLE9210x_FUNCTION_LAYER */
