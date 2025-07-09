/**
 *	@file TLE9210x_defines.h
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

/** \addtogroup TLE9210x_DEFINES
 *  @{
 */

#ifndef TLE9210x_DEFINES_H
#define TLE9210x_DEFINES_H

/************************************************************************
**                             Includes                                **
************************************************************************/

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
#define TLE92104 4 /*!< Variant selection for TLE92104 */
#define TLE92108 8 /*!< Variant selection for TLE92108 */
/**
 * \brief Variant selection for the device driver
 *
 * The variant must be specified for which the device driver shall be built
 */
#define TLE9210x_Variant TLE92108


/*
###############
Control_GENCTRL1
###############
*/
#define TLE9210x_Control_GENCTRL1_INIT 0x0026 /*!< Init value for register Control_GENCTRL1*/
#define TLE9210x_Control_GENCTRL1_CSD2_Pos 15u /*!< CSD2 Bit Position*/
#define TLE9210x_Control_GENCTRL1_CSD2_Mask 0x8000u /*!< CSD2 Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_CSAG2_Pos 13u /*!< CSAG2 Bit Position*/
#define TLE9210x_Control_GENCTRL1_CSAG2_Mask 0x6000u /*!< CSAG2 Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_CSD1_Pos 12u /*!< CSD1 Bit Position*/
#define TLE9210x_Control_GENCTRL1_CSD1_Mask 0x1000u /*!< CSD1 Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_CSAG1_Pos 10u /*!< CSAG1 Bit Position*/
#define TLE9210x_Control_GENCTRL1_CSAG1_Mask 0xc00u /*!< CSAG1 Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_REG_BANK_Pos 9u /*!< REG_BANK Bit Position*/
#define TLE9210x_Control_GENCTRL1_REG_BANK_Mask 0x200u /*!< REG_BANK Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_VSOVTH_Pos 8u /*!< VSOVTH Bit Position*/
#define TLE9210x_Control_GENCTRL1_VSOVTH_Mask 0x100u /*!< VSOVTH Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_UNLOCK_Pos 7u /*!< UNLOCK Bit Position*/
#define TLE9210x_Control_GENCTRL1_UNLOCK_Mask 0x80u /*!< UNLOCK Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_FMODE_Pos 5u /*!< FMODE Bit Position*/
#define TLE9210x_Control_GENCTRL1_FMODE_Mask 0x20u /*!< FMODE Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_IPCHGADT_Pos 3u /*!< IPCHGADT Bit Position*/
#define TLE9210x_Control_GENCTRL1_IPCHGADT_Mask 0x8u /*!< IPCHGADT Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_OCEN_Pos 2u /*!< OCEN Bit Position*/
#define TLE9210x_Control_GENCTRL1_OCEN_Mask 0x4u /*!< OCEN Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_WDPER_Pos 1u /*!< WDPER Bit Position*/
#define TLE9210x_Control_GENCTRL1_WDPER_Mask 0x2u /*!< WDPER Bitfield-Mask */
#define TLE9210x_Control_GENCTRL1_WDTRIG_Pos 0u /*!< WDTRIG Bit Position*/
#define TLE9210x_Control_GENCTRL1_WDTRIG_Mask 0x1u /*!< WDTRIG Bitfield-Mask */

/*
###############
Control_GENCTRL2
###############
*/
#define TLE9210x_Control_GENCTRL2_INIT 0x4180 /*!< Init value for register Control_GENCTRL2*/
#define TLE9210x_Control_GENCTRL2_POCHGDIS_Pos 15u /*!< POCHGDIS Bit Position*/
#define TLE9210x_Control_GENCTRL2_POCHGDIS_Mask 0x8000u /*!< POCHGDIS Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_BD_PASS_Pos 14u /*!< BD_PASS Bit Position*/
#define TLE9210x_Control_GENCTRL2_BD_PASS_Mask 0x4000u /*!< BD_PASS Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_AGCFILT_Pos 13u /*!< AGCFILT Bit Position*/
#define TLE9210x_Control_GENCTRL2_AGCFILT_Mask 0x2000u /*!< AGCFILT Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_AGC_Pos 11u /*!< AGC Bit Position*/
#define TLE9210x_Control_GENCTRL2_AGC_Mask 0x1800u /*!< AGC Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_IHOLD_Pos 10u /*!< IHOLD Bit Position*/
#define TLE9210x_Control_GENCTRL2_IHOLD_Mask 0x400u /*!< IHOLD Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_WDDIS_Pos 9u /*!< WDDIS Bit Position*/
#define TLE9210x_Control_GENCTRL2_WDDIS_Mask 0x200u /*!< WDDIS Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_MSKTDREG_Pos 8u /*!< MSKTDREG Bit Position*/
#define TLE9210x_Control_GENCTRL2_MSKTDREG_Mask 0x100u /*!< MSKTDREG Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_CPUVTH_Pos 7u /*!< CPUVTH Bit Position*/
#define TLE9210x_Control_GENCTRL2_CPUVTH_Mask 0x80u /*!< CPUVTH Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_CPSTGA_Pos 6u /*!< CPSTGA Bit Position*/
#define TLE9210x_Control_GENCTRL2_CPSTGA_Mask 0x40u /*!< CPSTGA Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_TFVDS_Pos 4u /*!< TFVDS Bit Position*/
#define TLE9210x_Control_GENCTRL2_TFVDS_Mask 0x30u /*!< TFVDS Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_OCTH2_Pos 2u /*!< OCTH2 Bit Position*/
#define TLE9210x_Control_GENCTRL2_OCTH2_Mask 0xcu /*!< OCTH2 Bitfield-Mask */
#define TLE9210x_Control_GENCTRL2_OCTH1_Pos 0u /*!< OCTH1 Bit Position*/
#define TLE9210x_Control_GENCTRL2_OCTH1_Mask 0x3u /*!< OCTH1 Bitfield-Mask */

/*
###############
Control_VDS1
###############
*/
#define TLE9210x_Control_VDS1_INIT 0x0B6D /*!< Init value for register Control_VDS1*/
#define TLE9210x_Control_VDS1_HB4D_Pos 15u /*!< HB4D Bit Position*/
#define TLE9210x_Control_VDS1_HB4D_Mask 0x8000u /*!< HB4D Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB3D_Pos 14u /*!< HB3D Bit Position*/
#define TLE9210x_Control_VDS1_HB3D_Mask 0x4000u /*!< HB3D Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB2D_Pos 13u /*!< HB2D Bit Position*/
#define TLE9210x_Control_VDS1_HB2D_Mask 0x2000u /*!< HB2D Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB1D_Pos 12u /*!< HB1D Bit Position*/
#define TLE9210x_Control_VDS1_HB1D_Mask 0x1000u /*!< HB1D Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB4VDSTH_Pos 9u /*!< HB4VDSTH Bit Position*/
#define TLE9210x_Control_VDS1_HB4VDSTH_Mask 0xe00u /*!< HB4VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB3VDSTH_Pos 6u /*!< HB3VDSTH Bit Position*/
#define TLE9210x_Control_VDS1_HB3VDSTH_Mask 0x1c0u /*!< HB3VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB2VDSTH_Pos 3u /*!< HB2VDSTH Bit Position*/
#define TLE9210x_Control_VDS1_HB2VDSTH_Mask 0x38u /*!< HB2VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS1_HB1VDSTH_Pos 0u /*!< HB1VDSTH Bit Position*/
#define TLE9210x_Control_VDS1_HB1VDSTH_Mask 0x7u /*!< HB1VDSTH Bitfield-Mask */

/*
###############
Control_VDS2
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_VDS2_INIT 0x0B6D /*!< Init value for register Control_VDS2*/
#define TLE9210x_Control_VDS2_HB8D_Pos 15u /*!< HB8D Bit Position*/
#define TLE9210x_Control_VDS2_HB8D_Mask 0x8000u /*!< HB8D Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB7D_Pos 14u /*!< HB7D Bit Position*/
#define TLE9210x_Control_VDS2_HB7D_Mask 0x4000u /*!< HB7D Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB6D_Pos 13u /*!< HB6D Bit Position*/
#define TLE9210x_Control_VDS2_HB6D_Mask 0x2000u /*!< HB6D Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB5D_Pos 12u /*!< HB5D Bit Position*/
#define TLE9210x_Control_VDS2_HB5D_Mask 0x1000u /*!< HB5D Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB8VDSTH_Pos 9u /*!< HB8VDSTH Bit Position*/
#define TLE9210x_Control_VDS2_HB8VDSTH_Mask 0xe00u /*!< HB8VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB7VDSTH_Pos 6u /*!< HB7VDSTH Bit Position*/
#define TLE9210x_Control_VDS2_HB7VDSTH_Mask 0x1c0u /*!< HB7VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB6VDSTH_Pos 3u /*!< HB6VDSTH Bit Position*/
#define TLE9210x_Control_VDS2_HB6VDSTH_Mask 0x38u /*!< HB6VDSTH Bitfield-Mask */
#define TLE9210x_Control_VDS2_HB5VDSTH_Pos 0u /*!< HB5VDSTH Bit Position*/
#define TLE9210x_Control_VDS2_HB5VDSTH_Mask 0x7u /*!< HB5VDSTH Bitfield-Mask */
#endif

/*
###############
Control_CCP_BLK1
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_CCP_BLK1_HB8CCPBLK_Pos 14u /*!< HB8CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB8CCPBLK_Mask 0xc000u /*!< HB8CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB7CCPBLK_Pos 12u /*!< HB7CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB7CCPBLK_Mask 0x3000u /*!< HB7CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB6CCPBLK_Pos 10u /*!< HB6CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB6CCPBLK_Mask 0xc00u /*!< HB6CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB5CCPBLK_Pos 8u /*!< HB5CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB5CCPBLK_Mask 0x300u /*!< HB5CCPBLK Bitfield-Mask */
#endif
#define TLE9210x_Control_CCP_BLK1_INIT 0x0000 /*!< Init value for register Control_CCP_BLK1*/
#define TLE9210x_Control_CCP_BLK1_HB4CCPBLK_Pos 6u /*!< HB4CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB4CCPBLK_Mask 0xc0u /*!< HB4CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB3CCPBLK_Pos 4u /*!< HB3CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB3CCPBLK_Mask 0x30u /*!< HB3CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB2CCPBLK_Pos 2u /*!< HB2CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB2CCPBLK_Mask 0xcu /*!< HB2CCPBLK Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK1_HB1CCPBLK_Pos 0u /*!< HB1CCPBLK Bit Position*/
#define TLE9210x_Control_CCP_BLK1_HB1CCPBLK_Mask 0x3u /*!< HB1CCPBLK Bitfield-Mask */

/*
###############
Control_CCP_BLK2_ACT
###############
*/
#define TLE9210x_Control_CCP_BLK2_ACT_INIT 0x4924 /*!< Init value for register Control_CCP_BLK2_ACT*/
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP3_ACT_Pos 12u /*!< TCCP3_ACT Bit Position*/
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP3_ACT_Mask 0x7000u /*!< TCCP3_ACT Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_ACT_TBLANK2_ACT_Pos 9u /*!< TBLANK2_ACT Bit Position*/
#define TLE9210x_Control_CCP_BLK2_ACT_TBLANK2_ACT_Mask 0xe00u /*!< TBLANK2_ACT Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP2_ACT_Pos 6u /*!< TCCP2_ACT Bit Position*/
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP2_ACT_Mask 0x1c0u /*!< TCCP2_ACT Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_ACT_TBLANK1_ACT_Pos 3u /*!< TBLANK1_ACT Bit Position*/
#define TLE9210x_Control_CCP_BLK2_ACT_TBLANK1_ACT_Mask 0x38u /*!< TBLANK1_ACT Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP1_ACT_Pos 0u /*!< TCCP1_ACT Bit Position*/
#define TLE9210x_Control_CCP_BLK2_ACT_TCCP1_ACT_Mask 0x7u /*!< TCCP1_ACT Bitfield-Mask */

/*
###############
Control_CCP_BLK2_FW
###############
*/
#define TLE9210x_Control_CCP_BLK2_FW_INIT 0x4924 /*!< Init value for register Control_CCP_BLK2_FW*/
#define TLE9210x_Control_CCP_BLK2_FW_TCCP3_FW_Pos 12u /*!< TCCP3_FW Bit Position*/
#define TLE9210x_Control_CCP_BLK2_FW_TCCP3_FW_Mask 0x7000u /*!< TCCP3_FW Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_FW_TBLANK2_FW_Pos 9u /*!< TBLANK2_FW Bit Position*/
#define TLE9210x_Control_CCP_BLK2_FW_TBLANK2_FW_Mask 0xe00u /*!< TBLANK2_FW Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_FW_TCCP2_FW_Pos 6u /*!< TCCP2_FW Bit Position*/
#define TLE9210x_Control_CCP_BLK2_FW_TCCP2_FW_Mask 0x1c0u /*!< TCCP2_FW Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_FW_TBLANK1_FW_Pos 3u /*!< TBLANK1_FW Bit Position*/
#define TLE9210x_Control_CCP_BLK2_FW_TBLANK1_FW_Mask 0x38u /*!< TBLANK1_FW Bitfield-Mask */
#define TLE9210x_Control_CCP_BLK2_FW_TCCP1_FW_Pos 0u /*!< TCCP1_FW Bit Position*/
#define TLE9210x_Control_CCP_BLK2_FW_TCCP1_FW_Mask 0x7u /*!< TCCP1_FW Bitfield-Mask */

/*
###############
Control_HBMODE
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_HBMODE_HB8MODE_Pos 14u /*!< HB8MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB8MODE_Mask 0xc000u /*!< HB8MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB7MODE_Pos 12u /*!< HB7MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB7MODE_Mask 0x3000u /*!< HB7MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB6MODE_Pos 10u /*!< HB6MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB6MODE_Mask 0xc00u /*!< HB6MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB5MODE_Pos 8u /*!< HB5MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB5MODE_Mask 0x300u /*!< HB5MODE Bitfield-Mask */
#endif
#define TLE9210x_Control_HBMODE_INIT 0x0000 /*!< Init value for register Control_HBMODE*/
#define TLE9210x_Control_HBMODE_HB4MODE_Pos 6u /*!< HB4MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB4MODE_Mask 0xc0u /*!< HB4MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB3MODE_Pos 4u /*!< HB3MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB3MODE_Mask 0x30u /*!< HB3MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB2MODE_Pos 2u /*!< HB2MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB2MODE_Mask 0xcu /*!< HB2MODE Bitfield-Mask */
#define TLE9210x_Control_HBMODE_HB1MODE_Pos 0u /*!< HB1MODE Bit Position*/
#define TLE9210x_Control_HBMODE_HB1MODE_Mask 0x3u /*!< HB1MODE Bitfield-Mask */

/*
###############
Control_PWMSET
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_PWMSET_INIT 0x6C60 /*!< Init value for register Control_PWMSET*/
#else
#define TLE9210x_Control_PWMSET_INIT 0x6420 /*!< Init value for register Control_PWMSET*/
#endif
#define TLE9210x_Control_PWMSET_PASS_VDS_Pos 14u /*!< PASS_VDS Bit Position*/
#define TLE9210x_Control_PWMSET_PASS_VDS_Mask 0x4000u /*!< PASS_VDS Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PASS_MOD_Pos 12u /*!< PASS_MOD Bit Position*/
#define TLE9210x_Control_PWMSET_PASS_MOD_Mask 0x3000u /*!< PASS_MOD Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PWM3_HB_Pos 9u /*!< PWM3_HB Bit Position*/
#define TLE9210x_Control_PWMSET_PWM3_HB_Mask 0xe00u /*!< PWM3_HB Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PMW3_EN_Pos 8u /*!< PMW3_EN Bit Position*/
#define TLE9210x_Control_PWMSET_PMW3_EN_Mask 0x100u /*!< PMW3_EN Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PWM2_HB_Pos 5u /*!< PWM2_HB Bit Position*/
#define TLE9210x_Control_PWMSET_PWM2_HB_Mask 0xe0u /*!< PWM2_HB Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PWM2_EN_Pos 4u /*!< PWM2_EN Bit Position*/
#define TLE9210x_Control_PWMSET_PWM2_EN_Mask 0x10u /*!< PWM2_EN Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PWM1_HB_Pos 1u /*!< PWM1_HB Bit Position*/
#define TLE9210x_Control_PWMSET_PWM1_HB_Mask 0xeu /*!< PWM1_HB Bitfield-Mask */
#define TLE9210x_Control_PWMSET_PWM1_EN_Pos 0u /*!< PWM1_EN Bit Position*/
#define TLE9210x_Control_PWMSET_PWM1_EN_Mask 0x1u /*!< PWM1_EN Bitfield-Mask */

/*
###############
Control_TPRECHG
###############
*/
#define TLE9210x_Control_TPRECHG_INIT 0x0000 /*!< Init value for register Control_TPRECHG*/
#define TLE9210x_Control_TPRECHG_EN_DEEP_AD_Pos 14u /*!< EN_DEEP_AD Bit Position*/
#define TLE9210x_Control_TPRECHG_EN_DEEP_AD_Mask 0x4000u /*!< EN_DEEP_AD Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_EN_GEN_CHECK_Pos 12u /*!< EN_GEN_CHECK Bit Position*/
#define TLE9210x_Control_TPRECHG_EN_GEN_CHECK_Mask 0x1000u /*!< EN_GEN_CHECK Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPDCHG3_Pos 10u /*!< TPDCHG3 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPDCHG3_Mask 0xc00u /*!< TPDCHG3 Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPCHG3_Pos 8u /*!< TPCHG3 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPCHG3_Mask 0x300u /*!< TPCHG3 Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPDCHG2_Pos 6u /*!< TPDCHG2 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPDCHG2_Mask 0xc0u /*!< TPDCHG2 Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPCHG2_Pos 4u /*!< TPCHG2 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPCHG2_Mask 0x30u /*!< TPCHG2 Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPDCHG1_Pos 2u /*!< TPDCHG1 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPDCHG1_Mask 0xcu /*!< TPDCHG1 Bitfield-Mask */
#define TLE9210x_Control_TPRECHG_TPCHG1_Pos 0u /*!< TPCHG1 Bit Position*/
#define TLE9210x_Control_TPRECHG_TPCHG1_Mask 0x3u /*!< TPCHG1 Bitfield-Mask */

/*
###############
Control_HBIDIAG
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_HBIDIAG_HB8IDIAG_Pos 7u /*!< HB8IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB8IDIAG_Mask 0x80u /*!< HB8IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB7IDIAG_Pos 6u /*!< HB7IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB7IDIAG_Mask 0x40u /*!< HB7IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB6IDIAG_Pos 5u /*!< HB6IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB6IDIAG_Mask 0x20u /*!< HB6IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB5IDIAG_Pos 4u /*!< HB5IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB5IDIAG_Mask 0x10u /*!< HB5IDIAG Bitfield-Mask */
#endif
#define TLE9210x_Control_HBIDIAG_INIT 0xC000 /*!< Init value for register Control_HBIDIAG*/
#define TLE9210x_Control_HBIDIAG_CSA2L_Pos 15u /*!< CSA2L Bit Position*/
#define TLE9210x_Control_HBIDIAG_CSA2L_Mask 0x8000u /*!< CSA2L Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_CSA1L_Pos 14u /*!< CSA1L Bit Position*/
#define TLE9210x_Control_HBIDIAG_CSA1L_Mask 0x4000u /*!< CSA1L Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_OC2FILT_Pos 12u /*!< OC2FILT Bit Position*/
#define TLE9210x_Control_HBIDIAG_OC2FILT_Mask 0x3000u /*!< OC2FILT Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_OC1FILT_Pos 10u /*!< OC1FILT Bit Position*/
#define TLE9210x_Control_HBIDIAG_OC1FILT_Mask 0xc00u /*!< OC1FILT Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_CSA2_OFF_Pos 9u /*!< CSA2_OFF Bit Position*/
#define TLE9210x_Control_HBIDIAG_CSA2_OFF_Mask 0x200u /*!< CSA2_OFF Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_CSA1_OFF_Pos 8u /*!< CSA1_OFF Bit Position*/
#define TLE9210x_Control_HBIDIAG_CSA1_OFF_Mask 0x100u /*!< CSA1_OFF Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB4IDIAG_Pos 3u /*!< HB4IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB4IDIAG_Mask 0x8u /*!< HB4IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB3IDIAG_Pos 2u /*!< HB3IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB3IDIAG_Mask 0x4u /*!< HB3IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB2IDIAG_Pos 1u /*!< HB2IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB2IDIAG_Mask 0x2u /*!< HB2IDIAG Bitfield-Mask */
#define TLE9210x_Control_HBIDIAG_HB1IDIAG_Pos 0u /*!< HB1IDIAG Bit Position*/
#define TLE9210x_Control_HBIDIAG_HB1IDIAG_Mask 0x1u /*!< HB1IDIAG Bitfield-Mask */

/*
###############
Control_ST_ICHG
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Control_ST_ICHG_HB8ICHGST_Pos 15u /*!< HB8ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB8ICHGST_Mask 0x8000u /*!< HB8ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB7ICHGST_Pos 14u /*!< HB7ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB7ICHGST_Mask 0x4000u /*!< HB7ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB6ICHGST_Pos 13u /*!< HB6ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB6ICHGST_Mask 0x2000u /*!< HB6ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB5ICHGST_Pos 12u /*!< HB5ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB5ICHGST_Mask 0x1000u /*!< HB5ICHGST Bitfield-Mask */
#endif
#define TLE9210x_Control_ST_ICHG_INIT 0x0044 /*!< Init value for register Control_ST_ICHG*/
#define TLE9210x_Control_ST_ICHG_HB4ICHGST_Pos 11u /*!< HB4ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB4ICHGST_Mask 0x800u /*!< HB4ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB3ICHGST_Pos 10u /*!< HB3ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB3ICHGST_Mask 0x400u /*!< HB3ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB2ICHGST_Pos 9u /*!< HB2ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB2ICHGST_Mask 0x200u /*!< HB2ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_HB1ICHGST_Pos 8u /*!< HB1ICHGST Bit Position*/
#define TLE9210x_Control_ST_ICHG_HB1ICHGST_Mask 0x100u /*!< HB1ICHGST Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_ICHGST2_Pos 4u /*!< ICHGST2 Bit Position*/
#define TLE9210x_Control_ST_ICHG_ICHGST2_Mask 0xf0u /*!< ICHGST2 Bitfield-Mask */
#define TLE9210x_Control_ST_ICHG_ICHGST1_Pos 0u /*!< ICHGST1 Bit Position*/
#define TLE9210x_Control_ST_ICHG_ICHGST1_Mask 0xfu /*!< ICHGST1 Bitfield-Mask */

/*
###############
Control_PWM_PCHG_INIT
###############
*/
#define TLE9210x_Control_PWM_PCHG_INIT_INIT 0x18C6 /*!< Init value for register Control_PWM_PCHG_INIT*/
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT3_Pos 10u /*!< PCHGINIT3 Bit Position*/
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT3_Mask 0x7c00u /*!< PCHGINIT3 Bitfield-Mask */
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT2_Pos 5u /*!< PCHGINIT2 Bit Position*/
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT2_Mask 0x3e0u /*!< PCHGINIT2 Bitfield-Mask */
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT1_Pos 0u /*!< PCHGINIT1 Bit Position*/
#define TLE9210x_Control_PWM_PCHG_INIT_PCHGINIT1_Mask 0x1fu /*!< PCHGINIT1 Bitfield-Mask */

/*
###############
Control_PWM_ICHG_ACT
###############
*/
#define TLE9210x_Control_PWM_ICHG_ACT_INIT 0x18C6 /*!< Init value for register Control_PWM_ICHG_ACT*/
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG3_Pos 10u /*!< ICHG3 Bit Position*/
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG3_Mask 0x7c00u /*!< ICHG3 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG2_Pos 5u /*!< ICHG2 Bit Position*/
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG2_Mask 0x3e0u /*!< ICHG2 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG1_Pos 0u /*!< ICHG1 Bit Position*/
#define TLE9210x_Control_PWM_ICHG_ACT_ICHG1_Mask 0x1fu /*!< ICHG1 Bitfield-Mask */

/*
###############
Control_PWM_ICHG_FW
###############
*/
#define TLE9210x_Control_PWM_ICHG_FW_INIT 0x18C6 /*!< Init value for register Control_PWM_ICHG_FW*/
#define TLE9210x_Control_PWM_ICHG_FW_ICHG3_FW_Pos 10u /*!< ICHG3_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHG_FW_ICHG3_FW_Mask 0x7c00u /*!< ICHG3_FW Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHG_FW_ICHG2_FW_Pos 5u /*!< ICHG2_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHG_FW_ICHG2_FW_Mask 0x3e0u /*!< ICHG2_FW Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHG_FW_ICHG1_FW_Pos 0u /*!< ICHG1_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHG_FW_ICHG1_FW_Mask 0x1fu /*!< ICHG1_FW Bitfield-Mask */

/*
###############
Control_PWM_IDCHG_ACT
###############
*/
#define TLE9210x_Control_PWM_IDCHG_ACT_INIT 0x1CE7 /*!< Init value for register Control_PWM_IDCHG_ACT*/
#define TLE9210x_Control_PWM_IDCHG_ACT_CCSO_Pos 15u /*!< CCSO Bit Position*/
#define TLE9210x_Control_PWM_IDCHG_ACT_CCSO_Mask 0x8000u /*!< CCSO Bitfield-Mask */
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG3_Pos 10u /*!< IDCHG3 Bit Position*/
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG3_Mask 0x7c00u /*!< IDCHG3 Bitfield-Mask */
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG2_Pos 5u /*!< IDCHG2 Bit Position*/
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG2_Mask 0x3e0u /*!< IDCHG2 Bitfield-Mask */
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG1_Pos 0u /*!< IDCHG1 Bit Position*/
#define TLE9210x_Control_PWM_IDCHG_ACT_IDCHG1_Mask 0x1fu /*!< IDCHG1 Bitfield-Mask */

/*
###############
Control_PWM_PDCHG_INIT
###############
*/
#define TLE9210x_Control_PWM_PDCHG_INIT_INIT 0x318C /*!< Init value for register Control_PWM_PDCHG_INIT*/
#define TLE9210x_Control_PWM_PDCHG_INIT_CCSO_Pos 15u /*!< CCSO Bit Position*/
#define TLE9210x_Control_PWM_PDCHG_INIT_CCSO_Mask 0x8000u /*!< CCSO Bitfield-Mask */
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT3_Pos 10u /*!< PDCHGINIT3 Bit Position*/
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT3_Mask 0x7c00u /*!< PDCHGINIT3 Bitfield-Mask */
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT2_Pos 5u /*!< PDCHGINIT2 Bit Position*/
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT2_Mask 0x3e0u /*!< PDCHGINIT2 Bitfield-Mask */
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT1_Pos 0u /*!< PDCHGINIT1 Bit Position*/
#define TLE9210x_Control_PWM_PDCHG_INIT_PDCHGINIT1_Mask 0x1fu /*!< PDCHGINIT1 Bitfield-Mask */

/*
###############
Control_PWM_ICHGMAX_CCP_BLK3_ACT
###############
*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_INIT 0x4900 /*!< Init value for register Control_PWM_ICHGMAX_CCP_BLK3_ACT*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT_Pos 12u /*!< TBLANK4_ACT Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK4_ACT_Mask 0x7000u /*!< TBLANK4_ACT Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT_Pos 9u /*!< TCCP4_ACT Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TCCP4_ACT_Mask 0xe00u /*!< TCCP4_ACT Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT_Pos 6u /*!< TBLANK3_ACT Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_TBLANK3_ACT_Mask 0x1c0u /*!< TBLANK3_ACT Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3_Pos 4u /*!< ICHGMAX3 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX3_Mask 0x30u /*!< ICHGMAX3 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2_Pos 2u /*!< ICHGMAX2 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX2_Mask 0xcu /*!< ICHGMAX2 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1_Pos 0u /*!< ICHGMAX1 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_ACT_ICHGMAX1_Mask 0x3u /*!< ICHGMAX1 Bitfield-Mask */

/*
###############
Control_PWM_ICHGMAX_CCP_BLK3_FW
###############
*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_INIT 0x4900 /*!< Init value for register Control_PWM_ICHGMAX_CCP_BLK3_FW*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW_Pos 12u /*!< TBLANK4_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK4_FW_Mask 0x7000u /*!< TBLANK4_FW Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW_Pos 9u /*!< TCCP4_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TCCP4_FW_Mask 0xe00u /*!< TCCP4_FW Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW_Pos 6u /*!< TBLANK3_FW Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_TBLANK3_FW_Mask 0x1c0u /*!< TBLANK3_FW Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3_Pos 4u /*!< ICHGMAX3 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX3_Mask 0x30u /*!< ICHGMAX3 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2_Pos 2u /*!< ICHGMAX2 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX2_Mask 0xcu /*!< ICHGMAX2 Bitfield-Mask */
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1_Pos 0u /*!< ICHGMAX1 Bit Position*/
#define TLE9210x_Control_PWM_ICHGMAX_CCP_BLK3_FW_ICHGMAX1_Mask 0x3u /*!< ICHGMAX1 Bitfield-Mask */

/*
###############
Control_TDON_OFF1
###############
*/
#define TLE9210x_Control_TDON_OFF1_INIT 0x0A0A /*!< Init value for register Control_TDON_OFF1*/
#define TLE9210x_Control_TDON_OFF1_TDOFF1_Pos 8u /*!< TDOFF1 Bit Position*/
#define TLE9210x_Control_TDON_OFF1_TDOFF1_Mask 0xff00u /*!< TDOFF1 Bitfield-Mask */
#define TLE9210x_Control_TDON_OFF1_TDON1_Pos 0u /*!< TDON1 Bit Position*/
#define TLE9210x_Control_TDON_OFF1_TDON1_Mask 0xffu /*!< TDON1 Bitfield-Mask */

/*
###############
Control_TDON_OFF2
###############
*/
#define TLE9210x_Control_TDON_OFF2_INIT 0x0A0A /*!< Init value for register Control_TDON_OFF2*/
#define TLE9210x_Control_TDON_OFF2_TDOFF2_Pos 8u /*!< TDOFF2 Bit Position*/
#define TLE9210x_Control_TDON_OFF2_TDOFF2_Mask 0xff00u /*!< TDOFF2 Bitfield-Mask */
#define TLE9210x_Control_TDON_OFF2_TDON2_Pos 0u /*!< TDON2 Bit Position*/
#define TLE9210x_Control_TDON_OFF2_TDON2_Mask 0xffu /*!< TDON2 Bitfield-Mask */

/*
###############
Control_TDON_OFF3
###############
*/
#define TLE9210x_Control_TDON_OFF3_INIT 0x0A0A /*!< Init value for register Control_TDON_OFF3*/
#define TLE9210x_Control_TDON_OFF3_TDOFF3_Pos 8u /*!< TDOFF3 Bit Position*/
#define TLE9210x_Control_TDON_OFF3_TDOFF3_Mask 0xff00u /*!< TDOFF3 Bitfield-Mask */
#define TLE9210x_Control_TDON_OFF3_TDON3_Pos 0u /*!< TDON3 Bit Position*/
#define TLE9210x_Control_TDON_OFF3_TDON3_Mask 0xffu /*!< TDON3 Bitfield-Mask */

/*
###############
Control_CSA_OC_SH
###############
*/
#define TLE9210x_Control_CSA_OC_SH_INIT 0x0000 /*!< Init value for register Control_CSA_OC_SH*/
#define TLE9210x_Control_CSA_OC_SH_TDOFF3_HB6_PWM4_EN_Pos 10u /*!< HB6_PWM4_EN Bit Position*/
#define TLE9210x_Control_CSA_OC_SH_TDOFF3_HB6_PWM4_EN_Mask 0x400u /*!< HB6_PWM4_EN Bitfield-Mask */

/*
###############
Status_GENSTAT
###############
*/
#define TLE9210x_Status_GENSTAT_INIT 0x0 /*!< Init value for register Status_GENSTAT*/
#define TLE9210x_Status_GENSTAT_PASS_VDSOV_Pos 15u /*!< PASS_VDSOV Bit Position*/
#define TLE9210x_Status_GENSTAT_PASS_VDSOV_Mask 0x8000u /*!< PASS_VDSOV Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_WDMON_Pos 13u /*!< WDMON Bit Position*/
#define TLE9210x_Status_GENSTAT_WDMON_Mask 0x6000u /*!< WDMON Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_PWM3STAT_Pos 12u /*!< PWM3STAT Bit Position*/
#define TLE9210x_Status_GENSTAT_PWM3STAT_Mask 0x1000u /*!< PWM3STAT Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_PWM2STAT_Pos 11u /*!< PWM2STAT Bit Position*/
#define TLE9210x_Status_GENSTAT_PWM2STAT_Mask 0x800u /*!< PWM2STAT Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_PWM1STAT_Pos 10u /*!< PWM1STAT Bit Position*/
#define TLE9210x_Status_GENSTAT_PWM1STAT_Mask 0x400u /*!< PWM1STAT Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_TDREG3_Pos 9u /*!< TDREG3 Bit Position*/
#define TLE9210x_Status_GENSTAT_TDREG3_Mask 0x200u /*!< TDREG3 Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_TDREG2_Pos 8u /*!< TDREG2 Bit Position*/
#define TLE9210x_Status_GENSTAT_TDREG2_Mask 0x100u /*!< TDREG2 Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_TDREG1_Pos 7u /*!< TDREG1 Bit Position*/
#define TLE9210x_Status_GENSTAT_TDREG1_Mask 0x80u /*!< TDREG1 Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_TSD_Pos 6u /*!< TSD Bit Position*/
#define TLE9210x_Status_GENSTAT_TSD_Mask 0x40u /*!< TSD Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_TW_Pos 5u /*!< TW Bit Position*/
#define TLE9210x_Status_GENSTAT_TW_Mask 0x20u /*!< TW Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_OC2_Pos 4u /*!< OC2 Bit Position*/
#define TLE9210x_Status_GENSTAT_OC2_Mask 0x10u /*!< OC2 Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_OC1_Pos 3u /*!< OC1 Bit Position*/
#define TLE9210x_Status_GENSTAT_OC1_Mask 0x8u /*!< OC1 Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_VSOV_Pos 2u /*!< VSOV Bit Position*/
#define TLE9210x_Status_GENSTAT_VSOV_Mask 0x4u /*!< VSOV Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_VSUV_Pos 1u /*!< VSUV Bit Position*/
#define TLE9210x_Status_GENSTAT_VSUV_Mask 0x2u /*!< VSUV Bitfield-Mask */
#define TLE9210x_Status_GENSTAT_CPUV_Pos 0u /*!< CPUV Bit Position*/
#define TLE9210x_Status_GENSTAT_CPUV_Mask 0x1u /*!< CPUV Bitfield-Mask */

/*
###############
Status_DSOV
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Status_DSOV_LS8DSOV_Pos 15u /*!< LS8DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS8DSOV_Mask 0x8000u /*!< LS8DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS8DSOV_Pos 14u /*!< HS8DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS8DSOV_Mask 0x4000u /*!< HS8DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS7DSOV_Pos 13u /*!< LS7DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS7DSOV_Mask 0x2000u /*!< LS7DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS7DSOV_Pos 12u /*!< HS7DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS7DSOV_Mask 0x1000u /*!< HS7DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS6DSOV_Pos 11u /*!< LS6DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS6DSOV_Mask 0x800u /*!< LS6DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS6DSOV_Pos 10u /*!< HS6DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS6DSOV_Mask 0x400u /*!< HS6DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS5DSOV_Pos 9u /*!< LS5DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS5DSOV_Mask 0x200u /*!< LS5DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS5DSOV_Pos 8u /*!< HS5DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS5DSOV_Mask 0x100u /*!< HS5DSOV Bitfield-Mask */
#endif
#define TLE9210x_Status_DSOV_INIT 0x0 /*!< Init value for register Status_DSOV*/
#define TLE9210x_Status_DSOV_LS4DSOV_Pos 7u /*!< LS4DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS4DSOV_Mask 0x80u /*!< LS4DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS4DSOV_Pos 6u /*!< HS4DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS4DSOV_Mask 0x40u /*!< HS4DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS3DSOV_Pos 5u /*!< LS3DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS3DSOV_Mask 0x20u /*!< LS3DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS3DSOV_Pos 4u /*!< HS3DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS3DSOV_Mask 0x10u /*!< HS3DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS2DSOV_Pos 3u /*!< LS2DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS2DSOV_Mask 0x8u /*!< LS2DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS2DSOV_Pos 2u /*!< HS2DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS2DSOV_Mask 0x4u /*!< HS2DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_LS1DSOV_Pos 1u /*!< LS1DSOV Bit Position*/
#define TLE9210x_Status_DSOV_LS1DSOV_Mask 0x2u /*!< LS1DSOV Bitfield-Mask */
#define TLE9210x_Status_DSOV_HS1DSOV_Pos 0u /*!< HS1DSOV Bit Position*/
#define TLE9210x_Status_DSOV_HS1DSOV_Mask 0x1u /*!< HS1DSOV Bitfield-Mask */

/*
###############
Status_HBVOUT_PWMERR
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Status_HBVOUT_PWMERR_HB8PWME_Pos 15u /*!< HB8PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB8PWME_Mask 0x8000u /*!< HB8PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB7PWME_Pos 14u /*!< HB7PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB7PWME_Mask 0x4000u /*!< HB7PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB6PWME_Pos 13u /*!< HB6PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB6PWME_Mask 0x2000u /*!< HB6PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB5PWME_Pos 12u /*!< HB5PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB5PWME_Mask 0x1000u /*!< HB5PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB8VOUT_Pos 7u /*!< HB8VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB8VOUT_Mask 0x80u /*!< HB8VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB7VOUT_Pos 6u /*!< HB7VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB7VOUT_Mask 0x40u /*!< HB7VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB6VOUT_Pos 5u /*!< HB6VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB6VOUT_Mask 0x20u /*!< HB6VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB5VOUT_Pos 4u /*!< HB5VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB5VOUT_Mask 0x10u /*!< HB5VOUT Bitfield-Mask */
#endif
#define TLE9210x_Status_HBVOUT_PWMERR_INIT 0x0 /*!< Init value for register Status_HBVOUT_PWMERR*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB4PWME_Pos 11u /*!< HB4PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB4PWME_Mask 0x800u /*!< HB4PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB3PWME_Pos 10u /*!< HB3PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB3PWME_Mask 0x400u /*!< HB3PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB2PWME_Pos 9u /*!< HB2PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB2PWME_Mask 0x200u /*!< HB2PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB1PWME_Pos 8u /*!< HB1PWME Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB1PWME_Mask 0x100u /*!< HB1PWME Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB4VOUT_Pos 3u /*!< HB4VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB4VOUT_Mask 0x8u /*!< HB4VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB3VOUT_Pos 2u /*!< HB3VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB3VOUT_Mask 0x4u /*!< HB3VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB2VOUT_Pos 1u /*!< HB2VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB2VOUT_Mask 0x2u /*!< HB2VOUT Bitfield-Mask */
#define TLE9210x_Status_HBVOUT_PWMERR_HB1VOUT_Pos 0u /*!< HB1VOUT Bit Position*/
#define TLE9210x_Status_HBVOUT_PWMERR_HB1VOUT_Mask 0x1u /*!< HB1VOUT Bitfield-Mask */

/*
###############
Status_EFF_TDON_OFF1
###############
*/
#define TLE9210x_Status_EFF_TDON_OFF1_INIT 0x0 /*!< Init value for register Status_EFF_TDON_OFF1*/
#define TLE9210x_Status_EFF_TDON_OFF1_TDOFF1EFF_Pos 8u /*!< TDOFF1EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF1_TDOFF1EFF_Mask 0xff00u /*!< TDOFF1EFF Bitfield-Mask */
#define TLE9210x_Status_EFF_TDON_OFF1_TDON1EFF_Pos 0u /*!< TDON1EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF1_TDON1EFF_Mask 0xffu /*!< TDON1EFF Bitfield-Mask */

/*
###############
Status_EFF_TDON_OFF2
###############
*/
#define TLE9210x_Status_EFF_TDON_OFF2_INIT 0x0 /*!< Init value for register Status_EFF_TDON_OFF2*/
#define TLE9210x_Status_EFF_TDON_OFF2_TDOFF2EFF_Pos 8u /*!< TDOFF2EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF2_TDOFF2EFF_Mask 0xff00u /*!< TDOFF2EFF Bitfield-Mask */
#define TLE9210x_Status_EFF_TDON_OFF2_TDON2EFF_Pos 0u /*!< TDON2EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF2_TDON2EFF_Mask 0xffu /*!< TDON2EFF Bitfield-Mask */

/*
###############
Status_EFF_TDON_OFF3
###############
*/
#define TLE9210x_Status_EFF_TDON_OFF3_INIT 0x0 /*!< Init value for register Status_EFF_TDON_OFF3*/
#define TLE9210x_Status_EFF_TDON_OFF3_TDOFF3EFF_Pos 8u /*!< TDOFF3EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF3_TDOFF3EFF_Mask 0xff00u /*!< TDOFF3EFF Bitfield-Mask */
#define TLE9210x_Status_EFF_TDON_OFF3_TDON3EFF_Pos 0u /*!< TDON3EFF Bit Position*/
#define TLE9210x_Status_EFF_TDON_OFF3_TDON3EFF_Mask 0xffu /*!< TDON3EFF Bitfield-Mask */

/*
###############
Status_TRISE_FALL1
###############
*/
#define TLE9210x_Status_TRISE_FALL1_INIT 0x0 /*!< Init value for register Status_TRISE_FALL1*/
#define TLE9210x_Status_TRISE_FALL1_TFALL1_Pos 8u /*!< TFALL1 Bit Position*/
#define TLE9210x_Status_TRISE_FALL1_TFALL1_Mask 0xff00u /*!< TFALL1 Bitfield-Mask */
#define TLE9210x_Status_TRISE_FALL1_TRISE1_Pos 0u /*!< TRISE1 Bit Position*/
#define TLE9210x_Status_TRISE_FALL1_TRISE1_Mask 0xffu /*!< TRISE1 Bitfield-Mask */

/*
###############
Status_TRISE_FALL2
###############
*/
#define TLE9210x_Status_TRISE_FALL2_INIT 0x0 /*!< Init value for register Status_TRISE_FALL2*/
#define TLE9210x_Status_TRISE_FALL2_TFALL2_Pos 8u /*!< TFALL2 Bit Position*/
#define TLE9210x_Status_TRISE_FALL2_TFALL2_Mask 0xff00u /*!< TFALL2 Bitfield-Mask */
#define TLE9210x_Status_TRISE_FALL2_TRISE2_Pos 0u /*!< TRISE2 Bit Position*/
#define TLE9210x_Status_TRISE_FALL2_TRISE2_Mask 0xffu /*!< TRISE2 Bitfield-Mask */

/*
###############
Status_TRISE_FALL3
###############
*/
#define TLE9210x_Status_TRISE_FALL3_INIT 0x0 /*!< Init value for register Status_TRISE_FALL3*/
#define TLE9210x_Status_TRISE_FALL3_TFALL3_Pos 8u /*!< TFALL3 Bit Position*/
#define TLE9210x_Status_TRISE_FALL3_TFALL3_Mask 0xff00u /*!< TFALL3 Bitfield-Mask */
#define TLE9210x_Status_TRISE_FALL3_TRISE3_Pos 0u /*!< TRISE3 Bit Position*/
#define TLE9210x_Status_TRISE_FALL3_TRISE3_Mask 0xffu /*!< TRISE3 Bitfield-Mask */

/*
###############
Status_DEVID
###############
*/
#if TLE9210x_Variant == TLE92108
#define TLE9210x_Status_DEVID_INIT 0x01 /*!< Init value for register Status_DEVID*/
#else
#define TLE9210x_Status_DEVID_INIT 0x81 /*!< Init value for register Status_DEVID*/
#endif
#define TLE9210x_Status_DEVID_DEV_ID_Pos 0u /*!< DEV_ID Bit Position*/
#define TLE9210x_Status_DEVID_DEV_ID_Mask 0x7u /*!< DEV_ID Bitfield-Mask */

/** @}*/ /* End of group TLE9210x_DEFINES */

#endif /* TLE9210x_DEFINES_H */
