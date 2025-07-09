/**
 *	@file TLE9210x_RegLayer.c
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

/** \addtogroup TLE9210x_REGISTER_LAYER
 *  @{
 */

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x_RegLayer.h"
#include "TLE9210x_ServLayer.h"

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

/** \brief Set Control_GENCTRL1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_GENCTRL1(uint16_t u16_data)
{
	TLE9210x->Control_GENCTRL1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlGENCTRL1_ADDR, u16_data); // without converting the watchdog-bit
}

/** \brief Get Control_GENCTRL1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_GENCTRL1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlGENCTRL1_ADDR);
}

/** \brief Set Control_GENCTRL2 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_GENCTRL2(uint16_t u16_data)
{
	TLE9210x->Control_GENCTRL2.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlGENCTRL2_ADDR, u16_data);
}

/** \brief Get Control_GENCTRL2 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_GENCTRL2(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlGENCTRL2_ADDR);
}

/** \brief Set Control_VDS1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_VDS1(uint16_t u16_data)
{
	TLE9210x->Control_VDS1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlVDS1_ADDR, u16_data);
}

/** \brief Get Control_VDS1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_VDS1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlVDS1_ADDR);
}

/** \brief Set Control_VDS2 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_VDS2(uint16_t u16_data)
{
	TLE9210x->Control_VDS2.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlVDS2_ADDR, u16_data);
}

/** \brief Get Control_VDS2 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_VDS2(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlVDS2_ADDR);
}

/** \brief Set Control_CCP_BLK1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_CCP_BLK1(uint16_t u16_data)
{
	TLE9210x->Control_CCP_BLK1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlCCPBLK1_ADDR, u16_data);
}

/** \brief Get Control_CCP_BLK1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_CCP_BLK1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlCCPBLK1_ADDR);
}

/** \brief Set Control_CCP_BLK2_ACT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT(uint16_t u16_data)
{
	TLE9210x->Control_CCP_BLK2_ACT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlCCPBLK2ACT_ADDR, u16_data);
}

/** \brief Get Control_CCP_BLK2_ACT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_CCP_BLK2_ACT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlCCPBLK2ACT_ADDR);
}

/** \brief Set Control_CCP_BLK2_FW Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_CCP_BLK2_FW(uint16_t u16_data)
{
	TLE9210x->Control_CCP_BLK2_FW.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlCCPBLK2FW_ADDR, u16_data);
}

/** \brief Get Control_CCP_BLK2_FW Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_CCP_BLK2_FW(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlCCPBLK2FW_ADDR);
}

/** \brief Set Control_HBMODE Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_HBMODE(uint16_t u16_data)
{
	TLE9210x->Control_HBMODE.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlHBMODE_ADDR, u16_data);
}

/** \brief Get Control_HBMODE Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_HBMODE(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlHBMODE_ADDR);
}

/** \brief Set Control_PWMSET Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWMSET(uint16_t u16_data)
{
	TLE9210x->Control_PWMSET.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMSET_ADDR, u16_data);
}

/** \brief Get Control_PWMSET Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWMSET(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMSET_ADDR);
}

/** \brief Set Control_TPRECHG Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_TPRECHG(uint16_t u16_data)
{
	TLE9210x->Control_TPRECHG.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlTPRECHG_ADDR, u16_data);
}

/** \brief Get Control_TPRECHG Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_TPRECHG(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlTPRECHG_ADDR);
}

/** \brief Set Control_HBIDIAG Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_HBIDIAG(uint16_t u16_data)
{
	TLE9210x->Control_HBIDIAG.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlHBIDIAG_ADDR, u16_data);
}

/** \brief Get Control_HBIDIAG Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_HBIDIAG(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlHBIDIAG_ADDR);
}

/** \brief Set Control_ST_ICHG Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_ST_ICHG(uint16_t u16_data)
{
	TLE9210x->Control_ST_ICHG.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlSTICHG_ADDR, u16_data);
}

/** \brief Get Control_ST_ICHG Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_ST_ICHG(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlSTICHG_ADDR);
}

/** \brief Set Control_PWM_PCHG_INIT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT(uint16_t u16_data)
{
	TLE9210x->Control_PWM_PCHG_INIT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMPCHGINIT_ADDR, u16_data);
}

/** \brief Get Control_PWM_PCHG_INIT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_PCHG_INIT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMPCHGINIT_ADDR);
}

/** \brief Set Control_PWM_ICHG_ACT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT(uint16_t u16_data)
{
	TLE9210x->Control_PWM_ICHG_ACT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMICHGACT_ADDR, u16_data);
}

/** \brief Get Control_PWM_ICHG_ACT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_ICHG_ACT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMICHGACT_ADDR);
}

/** \brief Set Control_PWM_ICHG_FW Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_ICHG_FW(uint16_t u16_data)
{
	TLE9210x->Control_PWM_ICHG_FW.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMICHGFW_ADDR, u16_data);
}

/** \brief Get Control_PWM_ICHG_FW Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_ICHG_FW(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMICHGFW_ADDR);
}

/** \brief Set Control_PWM_IDCHG_ACT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT(uint16_t u16_data)
{
	TLE9210x->Control_PWM_IDCHG_ACT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMIDCHGACT_ADDR, u16_data);
}

/** \brief Get Control_PWM_IDCHG_ACT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_IDCHG_ACT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMIDCHGACT_ADDR);
}

/** \brief Set Control_PWM_PDCHG_INIT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT(uint16_t u16_data)
{
	TLE9210x->Control_PWM_PDCHG_INIT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMPDCHGINIT_ADDR, u16_data);
}

/** \brief Get Control_PWM_PDCHG_INIT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_PDCHG_INIT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMPDCHGINIT_ADDR);
}

/** \brief Set Control_PWM_ICHGMAX_CCP_BLK3_ACT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT(uint16_t u16_data)
{
	TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_ACT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMICHGMAXCCPBLK3ACT_ADDR, u16_data);
}

/** \brief Get Control_PWM_ICHGMAX_CCP_BLK3_ACT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMICHGMAXCCPBLK3ACT_ADDR);
}

/** \brief Set Control_PWM_ICHGMAX_CCP_BLK3_FW Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW(uint16_t u16_data)
{
	TLE9210x->Control_PWM_ICHGMAX_CCP_BLK3_FW.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlPWMICHGMAXCCPBLK3FW_ADDR, u16_data);
}

/** \brief Get Control_PWM_ICHGMAX_CCP_BLK3_FW Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlPWMICHGMAXCCPBLK3FW_ADDR);
}

/** \brief Set Control_TDON_OFF1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_TDON_OFF1(uint16_t u16_data)
{
	TLE9210x->Control_TDON_OFF1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlTDONOFF1_ADDR, u16_data);
}

/** \brief Get Control_TDON_OFF1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_TDON_OFF1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlTDONOFF1_ADDR);
}

/** \brief Set Control_TDON_OFF2 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_TDON_OFF2(uint16_t u16_data)
{
	TLE9210x->Control_TDON_OFF2.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlTDONOFF2_ADDR, u16_data);
}

/** \brief Get Control_TDON_OFF2 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_TDON_OFF2(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlTDONOFF2_ADDR);
}

/** \brief Set Control_TDON_OFF3 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_TDON_OFF3(uint16_t u16_data)
{
	TLE9210x->Control_TDON_OFF3.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlTDONOFF3_ADDR, u16_data);
}

/** \brief Get Control_TDON_OFF3 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_TDON_OFF3(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlTDONOFF3_ADDR);
}

/** \brief Set Control_DRV_LPWR_EN Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_DRV_LPWR_EN(uint16_t u16_data)
{
	TLE9210x->Control_DRV_LPWR_EN.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlDRV_LPWR_EN_ADDR, u16_data);
}

/** \brief Get Control_DRV_LPWR_EN Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_DRV_LPWR_EN(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlDRV_LPWR_EN_ADDR);
}

/** \brief Set Control_CSA_OC_SH Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Control_CSA_OC_SH(uint16_t u16_data)
{
	TLE9210x->Control_CSA_OC_SH.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_ControlCSA_OC_SH_ADDR, u16_data);
}

/** \brief Get Control_CSA_OC_SH Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Control_CSA_OC_SH(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_ControlCSA_OC_SH_ADDR);
}

/** \brief Set Status_GENSTAT Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_GENSTAT(uint16_t u16_data)
{
	TLE9210x->Status_GENSTAT.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusGENSTAT_ADDR, u16_data);
}

/** \brief Get Status_GENSTAT Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_GENSTAT(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusGENSTAT_ADDR);
}

void TLE9210x_RegLayer_getclr_Status_GENSTAT(void)
{
	TLE9210x_ServLayer_getRegClr(TLE9210x_StatusGENSTAT_ADDR);
}

/** \brief Set Status_DSOV Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_DSOV(uint16_t u16_data)
{
	TLE9210x->Status_DSOV.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusDSOV_ADDR, u16_data);
}

/** \brief Get Status_DSOV Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_DSOV(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusDSOV_ADDR);
}

/** \brief Set Status_HBVOUT_PWMERR Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_HBVOUT_PWMERR(uint16_t u16_data)
{
	TLE9210x->Status_HBVOUT_PWMERR.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusHBVOUTPWMERR_ADDR, u16_data);
}

/** \brief Get Status_HBVOUT_PWMERR Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_HBVOUT_PWMERR(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusHBVOUTPWMERR_ADDR);
}

/** \brief Set Status_EFF_TDON_OFF1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF1(uint16_t u16_data)
{
	TLE9210x->Status_EFF_TDON_OFF1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusEFFTDONOFF1_ADDR, u16_data);
}

/** \brief Get Status_EFF_TDON_OFF1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusEFFTDONOFF1_ADDR);
}

/** \brief Set Status_EFF_TDON_OFF2 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF2(uint16_t u16_data)
{
	TLE9210x->Status_EFF_TDON_OFF2.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusEFFTDONOFF2_ADDR, u16_data);
}

/** \brief Get Status_EFF_TDON_OFF2 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF2(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusEFFTDONOFF2_ADDR);
}

/** \brief Set Status_EFF_TDON_OFF3 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF3(uint16_t u16_data)
{
	TLE9210x->Status_EFF_TDON_OFF3.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusEFFTDONOFF3_ADDR, u16_data);
}

/** \brief Get Status_EFF_TDON_OFF3 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF3(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusEFFTDONOFF3_ADDR);
}

/** \brief Set Status_TRISE_FALL1 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_TRISE_FALL1(uint16_t u16_data)
{
	TLE9210x->Status_TRISE_FALL1.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusTRISEFALL1_ADDR, u16_data);
}

/** \brief Get Status_TRISE_FALL1 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_TRISE_FALL1(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusTRISEFALL1_ADDR);
}

/** \brief Set Status_TRISE_FALL2 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_TRISE_FALL2(uint16_t u16_data)
{
	TLE9210x->Status_TRISE_FALL2.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusTRISEFALL2_ADDR, u16_data);
}

/** \brief Get Status_TRISE_FALL2 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_TRISE_FALL2(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusTRISEFALL2_ADDR);
}

/** \brief Set Status_TRISE_FALL3 Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_TRISE_FALL3(uint16_t u16_data)
{
	TLE9210x->Status_TRISE_FALL3.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusTRISEFALL3_ADDR, u16_data);
}

/** \brief Get Status_TRISE_FALL3 Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_TRISE_FALL3(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusTRISEFALL3_ADDR);
}

/** \brief Set Status_GDF Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_GDF(uint16_t u16_data)
{
	TLE9210x->Status_GDF.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusGDF_ADDR, u16_data);
}

/** \brief Get Status_GDF Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_GDF(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusGDF_ADDR);
}

/** \brief Set Status_DEVID Register
*
*   \param u16_data : value to be written
*   \return void
*/
void TLE9210x_RegLayer_set_Status_DEVID(uint16_t u16_data)
{
	TLE9210x->Status_DEVID.reg = u16_data;
	TLE9210x_ServLayer_setReg(TLE9210x_StatusDEVID_ADDR, u16_data);
}

/** \brief Get Status_DEVID Register
*
*   \return void
*/
void TLE9210x_RegLayer_get_Status_DEVID(void)
{
	TLE9210x_ServLayer_getReg(TLE9210x_StatusDEVID_ADDR);
}

/** @}*/ /* End of group TLE9210x_REGISTER_LAYER */
