/**
 *	@file TLE9210x_FuncLayer.h
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

#ifndef TLE9210x_FUNCLAYER_H
#define TLE9210x_FUNCLAYER_H

/************************************************************************
**                             Includes                                **
************************************************************************/
#include "TLE9210x.h"
#include "TLE9210x_RegLayer.h"
#include "TLE9210x_ServLayer.h"
#include "TLE9210x_defines.h"
#include "Srvl_Tle9210x.h"

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

uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSD2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSD2(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSAG2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSAG2(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSD1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSD1(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_CSAG1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_CSAG1(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_REG_BANK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_REG_BANK(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_VSOVTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_VSOVTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_UNLOCK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_UNLOCK(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_FMODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_FMODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_IPCHGADT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_IPCHGADT(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_OCEN(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_OCEN(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_WDPER(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_WDPER(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL1_WDTRIG(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL1(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_POCHGDIS(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_POCHGDIS(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_BD_PASS(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_BD_PASS(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_AGCFILT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_AGCFILT(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_AGC(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_AGC(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_IHOLD(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_IHOLD(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_WDDIS(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_WDDIS(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_MSKTDREG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_MSKTDREG(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_CPUVTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_CPUVTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_CPSTGA(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_CPSTGA(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_TFVDS(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_TFVDS(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_OCTH2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_OCTH2(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2_OCTH1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_GENCTRL2_OCTH1(void);
uint8_t TLE9210x_FuncLayer_set_Control_GENCTRL2(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB4D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB4D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB3D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB3D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB2D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB2D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB1D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB1D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB4VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB4VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB3VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB3VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB2VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB2VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1_HB1VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1_HB1VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS1(void);
void TLE9210x_FuncLayer_Trigger_Watchdog(void);
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB8D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB8D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB7D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB7D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB6D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB6D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB5D(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB5D(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB8VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB8VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB7VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB7VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB6VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB6VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2_HB5VDSTH(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2_HB5VDSTH(void);
uint8_t TLE9210x_FuncLayer_set_Control_VDS2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_VDS2(void);
#endif
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB8CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB8CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB7CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB7CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB6CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB6CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB5CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB5CCPBLK(void);
#endif
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB4CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB4CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB3CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB3CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB2CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB2CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1_HB1CCPBLK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK1_HB1CCPBLK(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK1(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP3_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP3_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TBLANK2_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TBLANK2_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP2_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP2_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TBLANK1_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TBLANK1_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT_TCCP1_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_ACT_TCCP1_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP3_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP3_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TBLANK2_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TBLANK2_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP2_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP2_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TBLANK1_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TBLANK1_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW_TCCP1_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CCP_BLK2_FW_TCCP1_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW(uint16_t u16_data);
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB8MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB8MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB7MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB7MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB6MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB6MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB5MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB5MODE(void);
#endif
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB4MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB4MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB3MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB3MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB2MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB2MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE_HB1MODE(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBMODE_HB1MODE(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBMODE(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PASS_VDS(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PASS_VDS(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PASS_MOD(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PASS_MOD(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_HB(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM3_HB(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_EN(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM3_EN(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_HB(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM2_HB(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_EN(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM2_EN(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_HB(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM1_HB(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_EN(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWMSET_PWM1_EN(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWMSET(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_EN_DEEP_AD(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_EN_DEEP_AD(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_EN_GEN_CHECK(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_EN_GEN_CHECK(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG3(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG3(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG2(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG2(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPDCHG1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPDCHG1(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG_TPCHG1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TPRECHG_TPCHG1(void);
uint8_t TLE9210x_FuncLayer_set_Control_TPRECHG(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA2L(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA2L(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA1L(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA1L(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_OC2FILT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_OC2FILT(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_OC1FILT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_OC1FILT(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA2_OFF(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA2_OFF(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_CSA1_OFF(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_CSA1_OFF(void);
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB8IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB8IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB7IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB7IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB6IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB6IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB5IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB5IDIAG(void);
#endif
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB4IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB4IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB3IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB3IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB2IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB2IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG_HB1IDIAG(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_HBIDIAG_HB1IDIAG(void);
uint8_t TLE9210x_FuncLayer_set_Control_HBIDIAG(uint16_t u16_data);
#if TLE9210x_Variant == TLE92108
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB8ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB8ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB7ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB7ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB6ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB6ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB5ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB5ICHGST(void);
#endif
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB4ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB4ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB3ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB3ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB2ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB2ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_HB1ICHGST(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_HB1ICHGST(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_ICHGST2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_ICHGST2(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG_ICHGST1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_ST_ICHG_ICHGST1(void);
uint8_t TLE9210x_FuncLayer_set_Control_ST_ICHG(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT_PCHGINIT1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PCHG_INIT_PCHGINIT1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT_ICHG1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_ACT_ICHG1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG3_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG3_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG2_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG2_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW_ICHG1_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHG_FW_ICHG1_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_CCSO(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_CCSO(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT_IDCHG1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_IDCHG_ACT_IDCHG1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_CCSO(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_CCSO(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT_PDCHGINIT1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_PDCHG_INIT_PDCHGINIT1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1(void);
uint8_t TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1_TDOFF1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF1_TDOFF1(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1_TDON1(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF1_TDON1(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF1(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2_TDOFF2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF2_TDOFF2(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2_TDON2(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF2_TDON2(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF2(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3_TDOFF3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF3_TDOFF3(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3_TDON3(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_TDON_OFF3_TDON3(void);
uint8_t TLE9210x_FuncLayer_set_Control_TDON_OFF3(uint16_t u16_data);
uint8_t TLE9210x_FuncLayer_set_Control_CSA_OC_SH_HB6_PWM4_EN(uint16_t u16_data);
uint16_t TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PASS_VDSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_WDMON(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM3STAT(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM2STAT(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_PWM1STAT(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG3(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG2(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TDREG1(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TSD(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_TW(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_OC2(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_OC1(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_VSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_VSUV(void);
uint16_t TLE9210x_FuncLayer_get_Status_GENSTAT_CPUV(void);
#if TLE9210x_Variant == TLE92108
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS8DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS8DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS7DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS7DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS6DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS6DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS5DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS5DSOV(void);
#endif
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS4DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS4DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS3DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS3DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS2DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS2DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_LS1DSOV(void);
uint16_t TLE9210x_FuncLayer_get_Status_DSOV_HS1DSOV(void);
#if TLE9210x_Variant == TLE92108
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB8PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB7PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB6PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB5PWME(void);
#endif
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB4PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB3PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB2PWME(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB1PWME(void);
#if TLE9210x_Variant == TLE92108
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB8VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB7VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB6VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB5VOUT(void);
#endif
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB4VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB3VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB2VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_HBVOUT_PWMERR_HB1VOUT(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF1_TDOFF1EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF1_TDON1EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF2_TDOFF2EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF2_TDON2EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF3_TDOFF3EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_EFF_TDON_OFF3_TDON3EFF(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL1_TFALL1(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL1_TRISE1(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL2_TFALL2(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL2_TRISE2(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL3_TFALL3(void);
uint16_t TLE9210x_FuncLayer_get_Status_TRISE_FALL3_TRISE3(void);
uint16_t TLE9210x_FuncLayer_get_Status_DEVID_DEV_ID(void);

/** @}*/ /* End of group TLE9210x_FUNCTION_LAYER */

#endif /* TLE9210x_FUNCLAYER_H */
