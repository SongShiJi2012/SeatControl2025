/**
 *	@file TLE9210x.c
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

/** \addtogroup TLE9210x
 *  @{
 */

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x.h"

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

static TLE9210x_Type TLE9210x_ram_copy[EN_TLE9210X_NUM_MAX]; /*!< Instantiation of the Register Shadow */
TLE9210x_Type* TLE9210x = &TLE9210x_ram_copy[EN_TLE9210X_NUM_1]; /*!< Pointer to the Register Shadow */

/************************************************************************
**                    Global Function Definitions                      **
************************************************************************/

/***********************************************************************
 * @function name: TLE9210_SetRamCopyNum
 *
 * @description: ÉèÖÃ»Ø¶Á»º´æµØÖ·
 *
 * @input parameters: void
 *
 * @output parameters: void
 *
 * @return: void
 *
 * @note:
 *
 * @author: czy
 *
 * @date: 2025-04-14
 ***********************************************************************/
 void TLE9210_SetRamCopyNum(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return;
    }
    TLE9210x = &TLE9210x_ram_copy[Num];
}

/**
 * \brief Set the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
void TLE9210x_SetByte0GSB(en_TLE9210x_NumMaxType Num,uint8_t u8_data)
{
  TLE9210x_ram_copy[Num].GSB.byte = u8_data;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.byte;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_FS(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.FS;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_NPOR(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.NPOR;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_TE(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.TE;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_SUPE(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.SUPE;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_VDSE(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.VDSE;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_OC(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.OC;
}

/**
 * \brief Returns the GSB (Global Status Byte) of the TLE9210x device.
 *
 * \return The GSB of the device as a 16-bit unsigned integer.
 */
uint8_t TLE9210x_GetByte0GSB_SPIE(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].GSB.bit.SPIE;
}


/** \brief Update Register Shadow of Status_GENSTAT
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_GENSTAT(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_GENSTAT.reg = u16_data;
}

/** \brief Update Register Shadow of Status_DSOV
*
*   \param u16_data : value to be written
*
*   \return void
*/

/** \brief Update Register Shadow of Status_DSOV
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_DSOV(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_DSOV.reg = u16_data;
}

/** \brief Update Register Shadow of Status_HBVOUT_PWMERR
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_HBVOUT_PWMERR(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_HBVOUT_PWMERR.reg = u16_data;
}

/** \brief Update Register Shadow of Status_EFF_TDON_OFF1
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_EFF_TDON_OFF1(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF1.reg = u16_data;
}

/** \brief Update Register Shadow of Status_EFF_TDON_OFF2
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_EFF_TDON_OFF2(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF2.reg = u16_data;
}

/** \brief Update Register Shadow of Status_EFF_TDON_OFF3
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_EFF_TDON_OFF3(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF3.reg = u16_data;
}

/** \brief Update Register Shadow of Status_TRISE_FALL1
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_TRISE_FALL1(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_TRISE_FALL1.reg = u16_data;
}

/** \brief Update Register Shadow of Status_TRISE_FALL2
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_TRISE_FALL2(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_TRISE_FALL2.reg = u16_data;
}

/** \brief Update Register Shadow of Status_TRISE_FALL3
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_TRISE_FALL3(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_TRISE_FALL3.reg = u16_data;
}

/** \brief Update Register Shadow of Status_GDF
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_GDF(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_GDF.reg = u16_data;
}

/** \brief Update Register Shadow of Status_DEVID
*
*   \param u16_data : value to be written
*
*   \return void
*/
void TLE9210x_Update_Status_DEVID(en_TLE9210x_NumMaxType Num,uint16_t u16_data)
{
  TLE9210x_ram_copy[Num].Status_DEVID.reg = u16_data;
}


/** \brief Return Register Shadow of Status_GENSTAT
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_GENSTAT(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_GENSTAT.reg;
}

/** \brief Return Register Shadow of Status_DSOV
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_DSOV(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_DSOV.reg;
}

/** \brief Return Register Shadow of Status_HBVOUT_PWMERR
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_HBVOUT_PWMERR(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_HBVOUT_PWMERR.reg;
}

/** \brief Return Register Shadow of Status_EFF_TDON_OFF1
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF1(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF1.reg;
}

/** \brief Return Register Shadow of Status_EFF_TDON_OFF2
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF2(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF2.reg;
}

/** \brief Return Register Shadow of Status_EFF_TDON_OFF3
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF3(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_EFF_TDON_OFF3.reg;
}

/** \brief Return Register Shadow of Status_TRISE_FALL1
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL1(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_TRISE_FALL1.reg;
}

/** \brief Return Register Shadow of Status_TRISE_FALL2
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL2(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_TRISE_FALL2.reg;
}

/** \brief Return Register Shadow of Status_TRISE_FALL3
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL3(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_TRISE_FALL3.reg;
}

/** \brief Return Register Shadow of Status_GDF
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_GDF(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_GDF.reg;
}

/** \brief Return Register Shadow of Status_DEVID
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Status_DEVID(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Status_DEVID.reg;
}

/** \brief Return Register Shadow of Status_GENSTAT
*
*   \param en_TLE9210x_NumMaxType:Chip channel
*
*   \return uint16_t
*/
uint16_t TLE9210x_Get_Reg_Control_HBMODE(en_TLE9210x_NumMaxType Num)
{
  return TLE9210x_ram_copy[Num].Control_HBMODE.reg;
}



/** @}*/ /* End of group TLE9210x */
