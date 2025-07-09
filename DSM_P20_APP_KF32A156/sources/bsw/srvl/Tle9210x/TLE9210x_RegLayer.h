/**
 *	@file TLE9210x_RegLayer.h
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

#ifndef TLE9210x_REGLAYER_H
#define TLE9210x_REGLAYER_H

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x.h"

/************************************************************************
**                      Local Macro Definitions                        **
************************************************************************/

#define TLE9210x_ControlGENCTRL1_ADDR               (0x00)
#define TLE9210x_ControlGENCTRL2_ADDR               (0x01)
#define TLE9210x_ControlVDS1_ADDR                   (0x02)
#if TLE9210x_Variant == TLE92108
#define TLE9210x_ControlVDS2_ADDR                   (0x03)
#endif
#define TLE9210x_ControlCCPBLK1_ADDR                (0x04)
#define TLE9210x_ControlCCPBLK2ACT_ADDR             (0x05)
#define TLE9210x_ControlCCPBLK2FW_ADDR              (0x05)
#define TLE9210x_ControlHBMODE_ADDR                 (0x06)
#define TLE9210x_ControlPWMSET_ADDR                 (0x07)
#define TLE9210x_ControlTPRECHG_ADDR                (0x08)
#define TLE9210x_ControlHBIDIAG_ADDR                (0x09)
#define TLE9210x_ControlSTICHG_ADDR                 (0x0A)
#define TLE9210x_ControlPWMPCHGINIT_ADDR            (0x0A)
#define TLE9210x_ControlPWMICHGACT_ADDR             (0x0B)
#define TLE9210x_ControlPWMICHGFW_ADDR              (0x0B)
#define TLE9210x_ControlPWMIDCHGACT_ADDR            (0x0C)
#define TLE9210x_ControlPWMPDCHGINIT_ADDR           (0x0C)
#define TLE9210x_ControlPWMICHGMAXCCPBLK3ACT_ADDR   (0x0D)
#define TLE9210x_ControlPWMICHGMAXCCPBLK3FW_ADDR    (0x0D)
#define TLE9210x_ControlTDONOFF1_ADDR               (0x0E)
#define TLE9210x_ControlTDONOFF2_ADDR               (0x0F)
#define TLE9210x_ControlTDONOFF3_ADDR               (0x10)
#define TLE9210x_StatusGENSTAT_ADDR                 (0x11)
#define TLE9210x_StatusDSOV_ADDR                    (0x12)
#define TLE9210x_StatusHBVOUTPWMERR_ADDR            (0x13)
#define TLE9210x_StatusEFFTDONOFF1_ADDR             (0x14)
#define TLE9210x_StatusEFFTDONOFF2_ADDR             (0x15)
#define TLE9210x_StatusEFFTDONOFF3_ADDR             (0x16)
#define TLE9210x_StatusTRISEFALL1_ADDR              (0x17)
#define TLE9210x_StatusTRISEFALL2_ADDR              (0x18)
#define TLE9210x_StatusTRISEFALL3_ADDR              (0x19)
#define TLE9210x_StatusGDF_ADDR                     (0x1A)
#define TLE9210x_ControlDRV_LPWR_EN_ADDR            (0x1C)
#define TLE9210x_ControlCSA_OC_SH_ADDR              (0x1D)
#define TLE9210x_ControlMISC_ADDR                   (0x1E)
#define TLE9210x_StatusDEVID_ADDR                   (0x1F)

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

void TLE9210x_RegLayer_set_Control_GENCTRL1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_GENCTRL1(void);
void TLE9210x_RegLayer_set_Control_GENCTRL2(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_GENCTRL2(void);
void TLE9210x_RegLayer_set_Control_VDS1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_VDS1(void);
void TLE9210x_RegLayer_set_Control_VDS2(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_VDS2(void);
void TLE9210x_RegLayer_set_Control_CCP_BLK1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_CCP_BLK1(void);
void TLE9210x_RegLayer_set_Control_CCP_BLK2_ACT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_CCP_BLK2_ACT(void);
void TLE9210x_RegLayer_set_Control_CCP_BLK2_FW(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_CCP_BLK2_FW(void);
void TLE9210x_RegLayer_set_Control_HBMODE(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_HBMODE(void);
void TLE9210x_RegLayer_set_Control_PWMSET(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWMSET(void);
void TLE9210x_RegLayer_set_Control_TPRECHG(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_TPRECHG(void);
void TLE9210x_RegLayer_set_Control_HBIDIAG(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_HBIDIAG(void);
void TLE9210x_RegLayer_set_Control_ST_ICHG(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_ST_ICHG(void);
void TLE9210x_RegLayer_set_Control_PWM_PCHG_INIT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_PCHG_INIT(void);
void TLE9210x_RegLayer_set_Control_PWM_ICHG_ACT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_ICHG_ACT(void);
void TLE9210x_RegLayer_set_Control_PWM_ICHG_FW(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_ICHG_FW(void);
void TLE9210x_RegLayer_set_Control_PWM_IDCHG_ACT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_IDCHG_ACT(void);
void TLE9210x_RegLayer_set_Control_PWM_PDCHG_INIT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_PDCHG_INIT(void);
void TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT(void);
void TLE9210x_RegLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW(void);
void TLE9210x_RegLayer_set_Control_TDON_OFF1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_TDON_OFF1(void);
void TLE9210x_RegLayer_set_Control_TDON_OFF2(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_TDON_OFF2(void);
void TLE9210x_RegLayer_set_Control_TDON_OFF3(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_TDON_OFF3(void);
void TLE9210x_RegLayer_set_Control_CSA_OC_SH(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_CSA_OC_SH(void);
void TLE9210x_RegLayer_set_Control_DRV_LPWR_EN(uint16_t u16_data);
void TLE9210x_RegLayer_get_Control_DRV_LPWR_EN(void);
void TLE9210x_RegLayer_set_Status_GENSTAT(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_GENSTAT(void);
void TLE9210x_RegLayer_set_Status_DSOV(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_DSOV(void);
void TLE9210x_RegLayer_set_Status_HBVOUT_PWMERR(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_HBVOUT_PWMERR(void);
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF1(void);
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF2(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF2(void);
void TLE9210x_RegLayer_set_Status_EFF_TDON_OFF3(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_EFF_TDON_OFF3(void);
void TLE9210x_RegLayer_set_Status_TRISE_FALL1(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_TRISE_FALL1(void);
void TLE9210x_RegLayer_set_Status_TRISE_FALL2(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_TRISE_FALL2(void);
void TLE9210x_RegLayer_set_Status_TRISE_FALL3(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_TRISE_FALL3(void);
void TLE9210x_RegLayer_set_Status_GDF(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_GDF(void);
void TLE9210x_RegLayer_set_Status_DEVID(uint16_t u16_data);
void TLE9210x_RegLayer_get_Status_DEVID(void);


void TLE9210x_RegLayer_getclr_Status_GENSTAT(void);

/** @}*/ /* End of group TLE9210x_REGISTER_LAYER */

#endif /* TLE9210x_REGLAYER_H */
