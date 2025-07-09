/**
 *	@file TLE9210x.h
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

#ifndef TLE9210x_H
#define TLE9210x_H

/************************************************************************
**                             Includes                                **
************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/************************************************************************
**                      Local Macro Definitions                        **
************************************************************************/

/************************************************************************
**                      Local Type Definitions                         **
************************************************************************/
typedef enum
{
    EN_TLE9210X_NUM_1,
    EN_TLE9210X_NUM_2,
    EN_TLE9210X_NUM_MAX,
}en_TLE9210x_NumMaxType;
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

/**
 * @brief TLE9210x (Module)
 */

typedef struct { /*!< TLE9210x_ Structure */

	union {
		volatile uint16_t reg; /*!< Register Control_GENCTRL1*/

		struct {
			volatile uint16_t WDTRIG: 1; /*!< [0..0] Watchdog trigger bit */
			volatile uint16_t WDPER: 1; /*!< [1..1] Watchdog period */
			volatile uint16_t OCEN: 1; /*!< [2..2] Overcurrent shutdown Enable */
			volatile uint16_t IPCHGADT: 1; /*!< [3..3] Adaptation of the pre-charge and pre-discharge current */
			uint16_t : 1; /*!< [4..4] Reserved */
			volatile uint16_t FMODE: 1; /*!< [5..5] Frequency modulation */
			uint16_t : 1; /*!< [6..6] Reserved */
			volatile uint16_t UNLOCK: 1; /*!< [7..7] Unlock bit to disable the watchdog */
			volatile uint16_t VSOVTH: 1; /*!< [8..8] VS Overvoltage threshold */
			volatile uint16_t REG_BANK: 1; /*!< [9..9] Register banking */
			volatile uint16_t CSAG1: 2; /*!< [11..10] Gain of current sense amplifier 1 */
			volatile uint16_t CSD1: 1; /*!< [12..12] Direction of current sense amplifier 1 */
			volatile uint16_t CSAG2: 2; /*!< [14..13] Gain of current sense amplifier 2 */
			volatile uint16_t CSD2: 1; /*!< [15..15] Direction of current sense amplifier 2 */
		} bit;
	} Control_GENCTRL1;

	union {
		volatile uint16_t reg; /*!< Register Control_GENCTRL2*/

		struct {
			volatile uint16_t OCTH1: 2; /*!< [1..0] Configuration Select 1 (see also ) */
			volatile uint16_t OCTH2: 2; /*!< [3..2] Overcurrent detection threshold of CSO2 with CSD2 = 0 */
			volatile uint16_t TFVDS: 2; /*!< [5..4] Filter time of drain-souce voltage monitoring */
			volatile uint16_t CPSTGA: 1; /*!< [6..6] Automatic switch-over between dual and single charge pump stage */
			volatile uint16_t CPUVTH: 1; /*!< [7..7] Charge pump undervoltage detection threshold */
			volatile uint16_t MSKTDREG: 1; /*!< [8..8] Masking of the turn-on/off delay error in the Global Error Flag */
			volatile uint16_t WDDIS: 1; /*!< [9..9] Watchdog disable bit */
			volatile uint16_t IHOLD: 1; /*!< [10..10] Gate driver hold current IHOLD */
			volatile uint16_t AGC: 2; /*!< [12..11] Adaptive gate control */
			volatile uint16_t AGCFILT: 1; /*!< [13..13] Filter for adaptive gate control */
			volatile uint16_t BD_PASS: 1; /*!< [14..14] Bridge driver passive mode */
			volatile uint16_t POCHGDIS: 1; /*!< [15..15] Postcharge disable bit */
		} bit;
	} Control_GENCTRL2;

	union {
		volatile uint8_t byte; /*!< (@ 0x00000000) Global Status Byte */

		struct {
			volatile uint8_t SPIE : 1;  /*!< [0..0] SPI protocol error */
			volatile uint8_t OC : 1;    /*!< [1..1] Overcurrent */
			volatile uint8_t VDSE : 1;  /*!< [2..2] Drain source voltage monitoring */
			volatile uint8_t SUPE : 1;  /*!< [3..3] Supply error */
			volatile uint8_t NPOR : 1;  /*!< [4..4] Power ON reset */
			volatile uint8_t TE : 1;    /*!< [5..5] Thermal error */
			volatile uint8_t FS : 1;    /*!< [6..6] Fail safe */
            uint8_t : 1;                /*!< [7..7] Reserved */
		} bit;
	} GSB;

	union {
		volatile uint16_t reg; /*!< Register Control_VDS1*/

		struct {
			volatile uint16_t HB1VDSTH: 3; /*!< [2..0] HB1 drain-source overvoltage threshold */
			volatile uint16_t HB2VDSTH: 3; /*!< [5..3] HB2 drain-source overvoltage threshold */
			volatile uint16_t HB3VDSTH: 3; /*!< [8..6] HB3 drain-source overvoltage threshold */
			volatile uint16_t HB4VDSTH: 3; /*!< [11..9] HB4 drain-source overvoltage threshold */
			volatile uint16_t HB1D: 1; /*!< [12..12] HS1 Drain-source monitoring */
			volatile uint16_t HB2D: 1; /*!< [13..13] HS2 Drain-source monitoring */
			volatile uint16_t HB3D: 1; /*!< [14..14] HS3 Drain-source monitoring */
			volatile uint16_t HB4D: 1; /*!< [15..15] HS4 Drain-source monitoring */
		} bit;
	} Control_VDS1;

	#if TLE9210x_Variant == TLE92108
	union {
		volatile uint16_t reg; /*!< Register Control_VDS2*/

		struct {
			volatile uint16_t HB5VDSTH: 3; /*!< [2..0] HB5 drain-source overvoltage threshold */
			volatile uint16_t HB6VDSTH: 3; /*!< [5..3] HB6 drain-source overvoltage threshold */
			volatile uint16_t HB7VDSTH: 3; /*!< [8..6] HB7 drain-source overvoltage threshold */
			volatile uint16_t HB8VDSTH: 3; /*!< [11..9] HB8 drain-source overvoltage threshold */
			volatile uint16_t HB5D: 1; /*!< [12..12] HS5 Drain-source monitoring */
			volatile uint16_t HB6D: 1; /*!< [13..13] HS6 Drain-source monitoring */
			volatile uint16_t HB7D: 1; /*!< [14..14] HS7 Drain-source monitoring */
			volatile uint16_t HB8D: 1; /*!< [15..15] HS8 Drain-source monitoring */
		} bit;
	} Control_VDS2;
	#endif

	union {
		volatile uint16_t reg; /*!< Register Control_CCP_BLK1*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t HB1CCPBLK: 2; /*!< [1..0] Cross-current protection and blank times applied to HB1 */
			volatile uint16_t HB2CCPBLK: 2; /*!< [3..2] Cross-current protection and blank times applied to HB2 */
			volatile uint16_t HB3CCPBLK: 2; /*!< [5..4] Cross-current protection and blank times applied to HB3 */
			volatile uint16_t HB4CCPBLK: 2; /*!< [7..6] Cross-current protection and blank times applied to HB4 */
			volatile uint16_t HB5CCPBLK: 2; /*!< [9..8] Cross-current protection and blank times applied to HB5 */
			volatile uint16_t HB6CCPBLK: 2; /*!< [11..10] Cross-current protection and blank times applied to HB6 */
			volatile uint16_t HB7CCPBLK: 2; /*!< [13..12] Cross-current protection and blank times applied to HB7 */
			volatile uint16_t HB8CCPBLK: 2; /*!< [15..14] Cross-current protection and blank times applied to HB8 */
			#else
			volatile uint16_t HB1CCPBLK: 2; /*!< [1..0] Cross-current protection and blank times applied to HB1 */
			volatile uint16_t HB2CCPBLK: 2; /*!< [3..2] Cross-current protection and blank times applied to HB2 */
			volatile uint16_t HB3CCPBLK: 2; /*!< [5..4] Cross-current protection and blank times applied to HB3 */
			volatile uint16_t HB4CCPBLK: 2; /*!< [7..6] Cross-current protection and blank times applied to HB4 */
			uint16_t : 2; /*!< [9..8] Reserved */
			uint16_t : 2; /*!< [11..10] Reserved */
			uint16_t : 2; /*!< [13..12] Reserved */
			uint16_t : 2; /*!< [15..14] Reserved */
			#endif
		} bit;
	} Control_CCP_BLK1;

	union {
		volatile uint16_t reg; /*!< Register Control_CCP_BLK2_ACT*/

		struct {
			volatile uint16_t TCCP1_ACT: 3; /*!< [2..0] Cross-current protection - tCCP1 Active */
			volatile uint16_t TBLANK1_ACT: 3; /*!< [5..3] Blank time - tBLANK1 Active */
			volatile uint16_t TCCP2_ACT: 3; /*!< [8..6] Cross-current protection - tCCP2 Active */
			volatile uint16_t TBLANK2_ACT: 3; /*!< [11..9] Blank time - tBLANK2 Active */
			volatile uint16_t TCCP3_ACT: 3; /*!< [14..12] Cross-current protection - tCCP3 Active */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_CCP_BLK2_ACT;

	union {
		volatile uint16_t reg; /*!< Register Control_CCP_BLK2_FW*/

		struct {
			volatile uint16_t TCCP1_FW: 3; /*!< [2..0] Cross-current protection - tCCP1 Freewheeling */
			volatile uint16_t TBLANK1_FW: 3; /*!< [5..3] Blank time - tBLANK1 Freewheeling */
			volatile uint16_t TCCP2_FW: 3; /*!< [8..6] Cross-current protection - tCCP2 Freewheeling */
			volatile uint16_t TBLANK2_FW: 3; /*!< [11..9] Blank time - tBLANK2 Freewheeling */
			volatile uint16_t TCCP3_FW: 3; /*!< [14..12] Cross-current protection - tCCP3 Freewheeling */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_CCP_BLK2_FW;

	union {
		volatile uint16_t reg; /*!< Register Control_HBMODE*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t HB1MODE: 2; /*!< [1..0] Half-bridge output 1 mode selection */
			volatile uint16_t HB2MODE: 2; /*!< [3..2] Half-bridge output 2 mode selection */
			volatile uint16_t HB3MODE: 2; /*!< [5..4] Half-bridge output 3 mode selection */
			volatile uint16_t HB4MODE: 2; /*!< [7..6] Half-bridge output 4 mode selection */
			volatile uint16_t HB5MODE: 2; /*!< [9..8] Half-bridge output 5 mode selection */
			volatile uint16_t HB6MODE: 2; /*!< [11..10] Half-bridge output 6 mode selection */
			volatile uint16_t HB7MODE: 2; /*!< [13..12] Half-bridge output 7 mode selection */
			volatile uint16_t HB8MODE: 2; /*!< [15..14] Half-bridge output 8 mode selection */
			#else
			volatile uint16_t HB1MODE: 2; /*!< [1..0] Half-bridge output 1 mode selection */
			volatile uint16_t HB2MODE: 2; /*!< [3..2] Half-bridge output 2 mode selection */
			volatile uint16_t HB3MODE: 2; /*!< [5..4] Half-bridge output 3 mode selection */
			volatile uint16_t HB4MODE: 2; /*!< [7..6] Half-bridge output 4 mode selection */
			uint16_t : 2; /*!< [9..8] Reserved */
			uint16_t : 2; /*!< [11..10] Reserved */
			uint16_t : 2; /*!< [13..12] Reserved */
			uint16_t : 2; /*!< [15..14] Reserved */
			#endif
		} bit;
	} Control_HBMODE;

	union {
		volatile uint16_t reg; /*!< Register Control_PWMSET*/

		struct {
			volatile uint16_t PWM1_EN: 1; /*!< [0..0] PWM channel 1 enable */
			volatile uint16_t PWM1_HB: 3; /*!< [3..1] Allocation of the PWM channel 1 */
			volatile uint16_t PWM2_EN: 1; /*!< [4..4] PWM channel 2 enable */
			volatile uint16_t PWM2_HB: 3; /*!< [7..5] Allocation of the PWM channel 2 */
			volatile uint16_t PMW3_EN: 1; /*!< [8..8] PWM channel 3 enable */
			volatile uint16_t PWM3_HB: 3; /*!< [11..9] Allowcation of the PWM channel 3 */
			volatile uint16_t PASS_MOD: 2; /*!< [13..12] Settings for bridge driver passive mode */
			volatile uint16_t PASS_VDS: 1; /*!< [14..14] Drain-Source monitoring in bridge passive mode */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWMSET;

	union {
		volatile uint16_t reg; /*!< Register Control_TPRECHG*/

		struct {
			volatile uint16_t TPCHG1: 2; /*!< [1..0] Pre-charge time of PWM channel 1 */
			volatile uint16_t TPDCHG1: 2; /*!< [3..2] Pre-discharge time of PWM channel 1 */
			volatile uint16_t TPCHG2: 2; /*!< [5..4] Pre-charge time of PWM channel 2 */
			volatile uint16_t TPDCHG2: 2; /*!< [7..6] Pre-discharge time of PWM channel 2 */
			volatile uint16_t TPCHG3: 2; /*!< [9..8] Pre-charge time of PWM channel 3 */
			volatile uint16_t TPDCHG3: 2; /*!< [11..10] Pre-discharge time of PWM channel 3 */
			volatile uint16_t EN_GEN_CHECK: 1; /*!< [12..12] Enable generator check */
			uint16_t : 1; /*!< [13..13] Reserved */
			volatile uint16_t EN_DEEP_AD: 1; /*!< [14..14] Deep adaptation enabled */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_TPRECHG;

	union {
		volatile uint16_t reg; /*!< Register Control_HBIDIAG*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t HB1IDIAG: 1; /*!< [0..0] Control of HB1 off-state current source and current sink */
			volatile uint16_t HB2IDIAG: 1; /*!< [1..1] Control of HB2 off-state current source and current sink */
			volatile uint16_t HB3IDIAG: 1; /*!< [2..2] Control of HB3 off-state current source and current sink */
			volatile uint16_t HB4IDIAG: 1; /*!< [3..3] Control of HB4 off-state current source and current sink */
			volatile uint16_t HB5IDIAG: 1; /*!< [4..4] Control of HB5 off-state current source and current sink */
			volatile uint16_t HB6IDIAG: 1; /*!< [5..5] Control of HB6 off-state current source and current sink */
			volatile uint16_t HB7IDIAG: 1; /*!< [6..6] Control of HB7 off-state current source and current sink */
			volatile uint16_t HB8IDIAG: 1; /*!< [7..7] Control of HB8 off-state current source and current sink */
			volatile uint16_t CSA1_OFF: 1; /*!< [8..8] Disable of CSA1 */
			volatile uint16_t CSA2_OFF: 1; /*!< [9..9] Disable of CSA2 */
			volatile uint16_t OC1FILT: 2; /*!< [11..10] Overcurrent filter time for CSO1 */
			volatile uint16_t OC2FILT: 2; /*!< [13..12] Overcurrent filter time for CSO2 */
			volatile uint16_t CSA1L: 1; /*!< [14..14] Level of CSA1 */
			volatile uint16_t CSA2L: 1; /*!< [15..15] Level of CSA2 */
			#else
			volatile uint16_t HB1IDIAG: 1; /*!< [0..0] Control of HB1 off-state current source and current sink */
			volatile uint16_t HB2IDIAG: 1; /*!< [1..1] Control of HB2 off-state current source and current sink */
			volatile uint16_t HB3IDIAG: 1; /*!< [2..2] Control of HB3 off-state current source and current sink */
			volatile uint16_t HB4IDIAG: 1; /*!< [3..3] Control of HB4 off-state current source and current sink */
			uint16_t : 1; /*!< [4..4] Reserved */
			uint16_t : 1; /*!< [5..5] Reserved */
			uint16_t : 1; /*!< [6..6] Reserved */
			uint16_t : 1; /*!< [7..7] Reserved */
			volatile uint16_t CSA1_OFF: 1; /*!< [8..8] Disable of CSA1 */
			volatile uint16_t CSA2_OFF: 1; /*!< [9..9] Disable of CSA2 */
			volatile uint16_t OC1FILT: 2; /*!< [11..10] Overcurrent filter time for CSO1 */
			volatile uint16_t OC2FILT: 2; /*!< [13..12] Overcurrent filter time for CSO2 */
			volatile uint16_t CSA1L: 1; /*!< [14..14] Level of CSA1 */
			volatile uint16_t CSA2L: 1; /*!< [15..15] Level of CSA2 */
			#endif
		} bit;
	} Control_HBIDIAG;

	union {
		volatile uint16_t reg; /*!< Register Control_ST_ICHG*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t ICHGST1: 4; /*!< [3..0] Static gate driver charge and discharge currents 1 */
			volatile uint16_t ICHGST2: 4; /*!< [7..4] Static gate driver charge and discharge currents 2 */
			volatile uint16_t HB1ICHGST: 1; /*!< [8..8] HB1 Selction of charge and discharge currents */
			volatile uint16_t HB2ICHGST: 1; /*!< [9..9] HB2 Selection of charge and discharge currents */
			volatile uint16_t HB3ICHGST: 1; /*!< [10..10] HB3 Selection of charge and discharge currents */
			volatile uint16_t HB4ICHGST: 1; /*!< [11..11] HB4 Selection of charge and discharge currents */
			volatile uint16_t HB5ICHGST: 1; /*!< [12..12] HB5 Selection of charge and discharge currents */
			volatile uint16_t HB6ICHGST: 1; /*!< [13..13] HB6 Selection of charge and discharge currents */
			volatile uint16_t HB7ICHGST: 1; /*!< [14..14] HB7 Selection of charge and discharge currents */
			volatile uint16_t HB8ICHGST: 1; /*!< [15..15] HB8 Selection of charge and discharge currents */
			#else
			volatile uint16_t ICHGST1: 4; /*!< [3..0] Static gate driver charge and discharge currents 1 */
			volatile uint16_t ICHGST2: 4; /*!< [7..4] Static gate driver charge and discharge currents 2 */
			volatile uint16_t HB1ICHGST: 1; /*!< [8..8] HB1 Selction of charge and discharge currents */
			volatile uint16_t HB2ICHGST: 1; /*!< [9..9] HB2 Selection of charge and discharge currents */
			volatile uint16_t HB3ICHGST: 1; /*!< [10..10] HB3 Selection of charge and discharge currents */
			volatile uint16_t HB4ICHGST: 1; /*!< [11..11] HB4 Selection of charge and discharge currents */
			uint16_t : 1; /*!< [12..12] Reserved */
			uint16_t : 1; /*!< [13..13] Reserved */
			uint16_t : 1; /*!< [14..14] Reserved */
			uint16_t : 1; /*!< [15..15] Reserved */
			#endif
		} bit;
	} Control_ST_ICHG;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_PCHG_INIT*/

		struct {
			volatile uint16_t PCHGINIT1: 5; /*!< [4..0] Initial precharge current of PWM channel 1 */
			volatile uint16_t PCHGINIT2: 5; /*!< [9..5] Initial precharge current of PWM channel 2 */
			volatile uint16_t PCHGINIT3: 5; /*!< [14..10] Initial precharge current of PWM Channel 3 */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWM_PCHG_INIT;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_ICHG_ACT*/

		struct {
			volatile uint16_t ICHG1: 5; /*!< [4..0] Gate driver charge current of PWM Channel 1 (ACTIVE MOSFET) */
			volatile uint16_t ICHG2: 5; /*!< [9..5] Gate driver charge current of PWM Channel 2 (ACTIVE MOSFET) */
			volatile uint16_t ICHG3: 5; /*!< [14..10] Gate driver charge current of PWM Channel 3 (ACTIVE MOSFET) */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWM_ICHG_ACT;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_ICHG_FW*/

		struct {
			volatile uint16_t ICHG1_FW: 5; /*!< [4..0] Gate driver charge and discharge currents of PWM Channel 1 (FW MOSFET) */
			volatile uint16_t ICHG2_FW: 5; /*!< [9..5] Gate driver charge and discharge currents of PWM Channel 2 (FW MOSFET) */
			volatile uint16_t ICHG3_FW: 5; /*!< [14..10] Gate driver charge and discharge currents of PWM Channel 3 (FW MOSFET) */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWM_ICHG_FW;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_IDCHG_ACT*/

		struct {
			volatile uint16_t IDCHG1: 5; /*!< [4..0] Discharge current for PWM Channel 1 (Active MOSFET) */
			volatile uint16_t IDCHG2: 5; /*!< [9..5] Discharge current for PWM Channel 2 (Active MOSFET) */
			volatile uint16_t IDCHG3: 5; /*!< [14..10] Discharge current for PWM Channel 3 (Active MOSFET) */
			volatile uint16_t CCSO: 1; /*!< [15..15] Capacitor connected to the current sense amplifier outputs */
		} bit;
	} Control_PWM_IDCHG_ACT;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_PDCHG_INIT*/

		struct {
			volatile uint16_t PDCHGINIT1: 5; /*!< [4..0] Initial predischarge current of PWM Channel 1 */
			volatile uint16_t PDCHGINIT2: 5; /*!< [9..5] Initial predischarge current of PWM Channel 2 */
			volatile uint16_t PDCHGINIT3: 5; /*!< [14..10] Initial predischarge current of PWM Channel 3 */
			volatile uint16_t CCSO: 1; /*!< [15..15] Capacitor connected to the current sense amplifier outputs */
		} bit;
	} Control_PWM_PDCHG_INIT;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_ICHGMAX_CCP_BLK3_ACT*/

		struct {
			volatile uint16_t ICHGMAX1: 2; /*!< [1..0] Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases */
			volatile uint16_t ICHGMAX2: 2; /*!< [3..2] Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases */
			volatile uint16_t ICHGMAX3: 2; /*!< [5..4] Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases */
			volatile uint16_t TBLANK3_ACT: 3; /*!< [8..6] Blank time - tBLANK3 Active */
			volatile uint16_t TCCP4_ACT: 3; /*!< [11..9] Cross-current protection - tCCP4 Active */
			volatile uint16_t TBLANK4_ACT: 3; /*!< [14..12] Blank timme - tBLANK4 Active */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWM_ICHGMAX_CCP_BLK3_ACT;

	union {
		volatile uint16_t reg; /*!< Register Control_PWM_ICHGMAX_CCP_BLK3_FW*/

		struct {
			volatile uint16_t ICHGMAX1: 2; /*!< [1..0] Maximum drive current of half-bridge mapped to PWM channel 1 during the pre-charge and pre-discharge phases */
			volatile uint16_t ICHGMAX2: 2; /*!< [3..2] Maximum drive current of half-bridge mapped to PWM channel 2 during the pre-charge phase and pre-discharge phases */
			volatile uint16_t ICHGMAX3: 2; /*!< [5..4] Maximum drive current of half-bridge mapped to PWM channel 3 during the pre-charge phase and pre-discharge phases */
			volatile uint16_t TBLANK3_FW: 3; /*!< [8..6] Blank time -tBLANK3 Freewheeling */
			volatile uint16_t TCCP4_FW: 3; /*!< [11..9] Cross-current protection - tCCP4 Freewheeling */
			volatile uint16_t TBLANK4_FW: 3; /*!< [14..12] Blank time -tBLANK4 Freewheeling */
			uint16_t : 1; /*!< [15..15] Reserved */
		} bit;
	} Control_PWM_ICHGMAX_CCP_BLK3_FW;

	union {
		volatile uint16_t reg; /*!< Register Control_TDON_OFF1*/

		struct {
			volatile uint16_t TDON1: 8; /*!< [7..0] Turn-on delay time of PWM Channel 1 = 62.5 x TDON1[7:0] ns */
			volatile uint16_t TDOFF1: 8; /*!< [15..8] Turn-off delay time of PWM Channel 1 = 62.5 x TDOFF1[7:0] ns */
		} bit;
	} Control_TDON_OFF1;

	union {
		volatile uint16_t reg; /*!< Register Control_TDON_OFF2*/

		struct {
			volatile uint16_t TDON2: 8; /*!< [7..0] Turn-on delay time of PWM Channel 2 = 62.5 x TDON2[7:0] ns */
			volatile uint16_t TDOFF2: 8; /*!< [15..8] Turn-off delay time of PWM Channel 2 = 62.5 x TDOFF2[7:0] ns */
		} bit;
	} Control_TDON_OFF2;

	union {
		volatile uint16_t reg; /*!< Register Control_TDON_OFF3*/

		struct {
			volatile uint16_t TDON3: 8; /*!< [7..0] Turn-on delay time of PWM Channel 3 = 62.5 x TDON3[7:0] ns */
			volatile uint16_t TDOFF3: 8; /*!< [15..8] Turn-off delay time of PWM Channel 3 = 62.5 x TDOFF3[7:0] ns */
		} bit;
	} Control_TDON_OFF3;

    union {
		volatile uint16_t reg; /*!< Register Control_DRV_LPWR_EN*/

		struct {
			volatile uint16_t DRV_LPWR_EN:  1; /*!< [0..0]  */
			volatile uint16_t EN_DEEP_DIAG: 1; /*!< [1..1] */
			volatile uint16_t            :  6; /*!< [7..2]  */
            volatile uint16_t TRISE_FALL:   4; /*!< [11..8]  */
            volatile uint16_t STC_EN:       1; /*!< [12..12] */
            volatile uint16_t PDR_DIS:      1; /*!< [13..13]  */
            volatile uint16_t OSC_SSC_DIS:  1; /*!< [14..14] */
            volatile uint16_t GDF_EN:       1; /*!< [15..15] */
		} bit;
	}Control_DRV_LPWR_EN;
	union {
		volatile uint16_t reg; /*!< Register Control_CSA_OC_SH*/

		struct {
			volatile uint16_t CSA1_SEL: 3;      /*!< [2..0]  */
			volatile uint16_t CSA2_SEL: 3;      /*!< [5..3]  */
            volatile uint16_t OC_SEP_EN: 1;     /*!< [6..6]  */
            volatile uint16_t CSA1_SH_EN: 1;    /*!< [7..7]  */
            volatile uint16_t CSA2_SH_EN: 1;    /*!< [8..8]  */
            volatile uint16_t CSA_BLK_SEL: 1;   /*!< [9..9]  */
            volatile uint16_t HB6_PWM4_EN: 1;   /*!< [10..10] */
            uint16_t : 5; /*!< [15..11] Reserved */
		} bit;
	} Control_CSA_OC_SH;

	union {
		volatile uint16_t reg; /*!< Register Status_GENSTAT*/

		struct {
			volatile uint16_t CPUV: 1; /*!< [0..0] Charge Pump Undervoltage */
			volatile uint16_t VSUV: 1; /*!< [1..1] VS Undervoltage */
			volatile uint16_t VSOV: 1; /*!< [2..2] VS Overvoltage */
			volatile uint16_t OC1: 1; /*!< [3..3] Overcurrent detection of CSO1 */
			volatile uint16_t OC2: 1; /*!< [4..4] Overcurrent detection of CSO2 */
			volatile uint16_t TW: 1; /*!< [5..5] Thermal Warning */
			volatile uint16_t TSD: 1; /*!< [6..6] Thermal shutdown */
			volatile uint16_t TDREG1: 1; /*!< [7..7] PWM channel 1 - Regulation of turn-on and turn-off delays */
			volatile uint16_t TDREG2: 1; /*!< [8..8] PWM channel 2 - Regulation of turn-on and turn-off delays */
			volatile uint16_t TDREG3: 1; /*!< [9..9] PWM channel 3 - Regulation of turn-on and turn-off delays */
			volatile uint16_t PWM1STAT: 1; /*!< [10..10] Status of PWM1 input */
			volatile uint16_t PWM2STAT: 1; /*!< [11..11] Status of PWM2 input */
			volatile uint16_t PWM3STAT: 1; /*!< [12..12] Status of PWM3 input */
			volatile uint16_t WDMON: 2; /*!< [14..13] Watchdog Monitoring */
			volatile uint16_t PASS_VDSOV: 1; /*!< [15..15] DS overvoltage while the bridge driver is in passive mode */
		} bit;
	} Status_GENSTAT;

	union {
		volatile uint16_t reg; /*!< Register Status_DSOV*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t HS1DSOV: 1; /*!< [0..0] Drain-Source overvoltage on high-side 1 */
			volatile uint16_t LS1DSOV: 1; /*!< [1..1] Drain-Source overvoltage on low-side 1 */
			volatile uint16_t HS2DSOV: 1; /*!< [2..2] Drain-Source overvoltage on high-side 2 */
			volatile uint16_t LS2DSOV: 1; /*!< [3..3] Drain-Source overvoltage on low-side 2 */
			volatile uint16_t HS3DSOV: 1; /*!< [4..4] Drain-Source overvoltage on high-side 3 */
			volatile uint16_t LS3DSOV: 1; /*!< [5..5] Drain-Source overvoltage on low-side 3 */
			volatile uint16_t HS4DSOV: 1; /*!< [6..6] Drain-Source overvoltage on high-side 4 */
			volatile uint16_t LS4DSOV: 1; /*!< [7..7] Drain-Source overvoltage on low-side 4 */
			volatile uint16_t HS5DSOV: 1; /*!< [8..8] Drain-Source overvoltage on high-side 5 */
			volatile uint16_t LS5DSOV: 1; /*!< [9..9] Drain-Source overvoltage on low-side 5 */
			volatile uint16_t HS6DSOV: 1; /*!< [10..10] Drain-Source overvoltage on high-side 6 */
			volatile uint16_t LS6DSOV: 1; /*!< [11..11] Drain-Source overvoltage on low-side 6 */
			volatile uint16_t HS7DSOV: 1; /*!< [12..12] Drain-Source overvoltage on high-side 7 */
			volatile uint16_t LS7DSOV: 1; /*!< [13..13] Drain-Source overvoltage on low-side 7 */
			volatile uint16_t HS8DSOV: 1; /*!< [14..14] Drain-Source overvoltage on high-side 8 */
			volatile uint16_t LS8DSOV: 1; /*!< [15..15] Drain-Source overvoltage on low-side 8 */
			#else
			volatile uint16_t HS1DSOV: 1; /*!< [0..0] Drain-Source overvoltage on high-side 1 */
			volatile uint16_t LS1DSOV: 1; /*!< [1..1] Drain-Source overvoltage on low-side 1 */
			volatile uint16_t HS2DSOV: 1; /*!< [2..2] Drain-Source overvoltage on high-side 2 */
			volatile uint16_t LS2DSOV: 1; /*!< [3..3] Drain-Source overvoltage on low-side 2 */
			volatile uint16_t HS3DSOV: 1; /*!< [4..4] Drain-Source overvoltage on high-side 3 */
			volatile uint16_t LS3DSOV: 1; /*!< [5..5] Drain-Source overvoltage on low-side 3 */
			volatile uint16_t HS4DSOV: 1; /*!< [6..6] Drain-Source overvoltage on high-side 4 */
			volatile uint16_t LS4DSOV: 1; /*!< [7..7] Drain-Source overvoltage on low-side 4 */
			uint16_t : 1; /*!< [8..8] Reserved */
			uint16_t : 1; /*!< [9..9] Reserved */
			uint16_t : 1; /*!< [10..10] Reserved */
			uint16_t : 1; /*!< [11..11] Reserved */
			uint16_t : 1; /*!< [12..12] Reserved */
			uint16_t : 1; /*!< [13..13] Reserved */
			uint16_t : 1; /*!< [14..14] Reserved */
			uint16_t : 1; /*!< [15..15] Reserved */
			#endif
		} bit;
	} Status_DSOV;

	union {
		volatile uint16_t reg; /*!< Register Status_HBVOUT_PWMERR*/

		struct {
			#if TLE9210x_Variant == TLE92108
			volatile uint16_t HB1VOUT: 1; /*!< [0..0] Voltage level at SH1 when HB1MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB2VOUT: 1; /*!< [1..1] Voltage level at SH2 when HB2MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB3VOUT: 1; /*!< [2..2] Voltage level at SH8 when HB3MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB4VOUT: 1; /*!< [3..3] Voltage level at SH4 when HB4MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB5VOUT: 1; /*!< [4..4] Voltage level at SH5 when HB5MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB6VOUT: 1; /*!< [5..5] Voltage level at SH6 when HB6MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB7VOUT: 1; /*!< [6..6] Voltage level at SH7 when HB7MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB8VOUT: 1; /*!< [7..7] Voltage level at SH8 when HB8MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB1PWME: 1; /*!< [8..8] PWM Error on HB1 */
			volatile uint16_t HB2PWME: 1; /*!< [9..9] PWM Error on HB2 */
			volatile uint16_t HB3PWME: 1; /*!< [10..10] PWM Error on HB3 */
			volatile uint16_t HB4PWME: 1; /*!< [11..11] PWM Error on HB4 */
			volatile uint16_t HB5PWME: 1; /*!< [12..12] PWM Error on HB5 */
			volatile uint16_t HB6PWME: 1; /*!< [13..13] PWM Error on HB6 */
			volatile uint16_t HB7PWME: 1; /*!< [14..14] PWM Error on HB7 */
			volatile uint16_t HB8PWME: 1; /*!< [15..15] PWM Error on HB8 */
			#else
			volatile uint16_t HB1VOUT: 1; /*!< [0..0] Voltage level at SH1 when HB1MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB2VOUT: 1; /*!< [1..1] Voltage level at SH2 when HB2MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB3VOUT: 1; /*!< [2..2] Voltage level at SH8 when HB3MODE[1:0] = (0,0) or (1,1) */
			volatile uint16_t HB4VOUT: 1; /*!< [3..3] Voltage level at SH4 when HB4MODE[1:0] = (0,0) or (1,1) */
			uint16_t : 1; /*!< [4..4] Reserved */
			uint16_t : 1; /*!< [5..5] Reserved */
			uint16_t : 1; /*!< [6..6] Reserved */
			uint16_t : 1; /*!< [7..7] Reserved */
			volatile uint16_t HB1PWME: 1; /*!< [8..8] PWM Error on HB1 */
			volatile uint16_t HB2PWME: 1; /*!< [9..9] PWM Error on HB2 */
			volatile uint16_t HB3PWME: 1; /*!< [10..10] PWM Error on HB3 */
			volatile uint16_t HB4PWME: 1; /*!< [11..11] PWM Error on HB4 */
			uint16_t : 1; /*!< [12..12] Reserved */
			uint16_t : 1; /*!< [13..13] Reserved */
			uint16_t : 1; /*!< [14..14] Reserved */
			uint16_t : 1; /*!< [15..15] Reserved */
			#endif
		} bit;
	} Status_HBVOUT_PWMERR;

	union {
		volatile uint16_t reg; /*!< Register Status_EFF_TDON_OFF1*/

		struct {
			volatile uint16_t TDON1EFF: 8; /*!< [7..0] Effective MOSFET turn-on delay of PWM Channel 1 = 62.5 x TDON1EFF[7:0] ns */
			volatile uint16_t TDOFF1EFF: 8; /*!< [15..8] Effective MOSFET turn-off delay of PWM Channel 1 = 62.5 x TDOFF1EFF[7:0] ns */
		} bit;
	} Status_EFF_TDON_OFF1;

	union {
		volatile uint16_t reg; /*!< Register Status_EFF_TDON_OFF2*/

		struct {
			volatile uint16_t TDON2EFF: 8; /*!< [7..0] Effective MOSFET turn-on delay of PWM Channel 2 = 62.5 x TDON2EFF[7:0] ns */
			volatile uint16_t TDOFF2EFF: 8; /*!< [15..8] Effective MOSFET turn-off delay of PWM Channel 2 = 62.5 x TDOFF2EFF[7:0] ns */
		} bit;
	} Status_EFF_TDON_OFF2;

	union {
		volatile uint16_t reg; /*!< Register Status_EFF_TDON_OFF3*/

		struct {
			volatile uint16_t TDON3EFF: 8; /*!< [7..0] Effective MOSFET turn-on delay of PWM Channel 3 = 62.5 x TDON3EFF[7:0] ns */
			volatile uint16_t TDOFF3EFF: 8; /*!< [15..8] Effective MOSFET turn-off delay of PWM Channel 3 = 62.5 x TDOFF3EFF[7:0] ns */
		} bit;
	} Status_EFF_TDON_OFF3;

	union {
		volatile uint16_t reg; /*!< Register Status_TRISE_FALL1*/

		struct {
			volatile uint16_t TRISE1: 8; /*!< [7..0] MOSFET rise time of PWM Channel 1 = 62.5 x TRISE1[7:0] ns */
			volatile uint16_t TFALL1: 8; /*!< [15..8] MOSFET fall time of PWM Channel 1 = 62.5 x TFALL1[7:0] ns */
		} bit;
	} Status_TRISE_FALL1;

	union {
		volatile uint16_t reg; /*!< Register Status_TRISE_FALL2*/

		struct {
			volatile uint16_t TRISE2: 8; /*!< [7..0] MOSFET rise time of PWM Channel 2 = 62.5 x TRISE2[7:0] ns */
			volatile uint16_t TFALL2: 8; /*!< [15..8] MOSFET fall time of PWM Channel 2 = 62.5 x TFALL2[7:0] ns */
		} bit;
	} Status_TRISE_FALL2;

	union {
		volatile uint16_t reg; /*!< Register Status_TRISE_FALL3*/

		struct {
			volatile uint16_t TRISE3: 8; /*!< [7..0] MOSFET rise time of PWM Channel 3 = 62.5 x TRISE3[7:0] ns */
			volatile uint16_t TFALL3: 8; /*!< [15..8] MOSFET fall time of PWM Channel 3 = 62.5 x TFALL3[7:0] ns */
		} bit;
	} Status_TRISE_FALL3;
	union {
		volatile uint16_t reg; /*!< Register Status_GDF */

		struct {
			volatile uint16_t L1GDF: 1; /*!< [0..0] HB low-side dead time Status */
			volatile uint16_t H1GDF: 1; /*!< [1..1] HB high-side dead time Status */
			volatile uint16_t L2GDF: 1; /*!< [2..2] HB low-side dead time Status */
			volatile uint16_t H2GDF: 1; /*!< [3..3] HB high-side dead time Status */
			volatile uint16_t L3GDF: 1; /*!< [4..4] HB low-side dead time Status */
			volatile uint16_t H3GDF: 1; /*!< [5..5] HB high-side dead time Status */
			volatile uint16_t L4GDF: 1; /*!< [6..6] HB low-side dead time Status */
			volatile uint16_t H4GDF: 1; /*!< [7..7] HB high-side dead time Status */
			volatile uint16_t L5GDF: 1; /*!< [8..8] HB low-side dead time Status */
			volatile uint16_t H5GDF: 1; /*!< [9..9] HB high-side dead time Status */
			volatile uint16_t L6GDF: 1; /*!< [10..10] HB low-side dead time Status */
			volatile uint16_t H6GDF: 1; /*!< [11..11] HB high-side dead time Status */
			volatile uint16_t L7GDF: 1; /*!< [12..12] HB low-side dead time Status */
			volatile uint16_t H7GDF: 1; /*!< [13..13] HB high-side dead time Status */
			volatile uint16_t L8GDF: 1; /*!< [14..14] HB low-side dead time Status */
			volatile uint16_t H8GDF: 1; /*!< [15..15] HB high-side dead time Status */
		} bit;
	} Status_GDF;

	union {
		volatile uint16_t reg; /*!< Register Status_DEVID*/

		struct {
			volatile uint16_t DEV_ID: 3; /*!< [2..0] Device derivative identifier */
			uint16_t : 13; /*!< [3..15] Reserved */
		} bit;
	} Status_DEVID;
} TLE9210x_Type;

extern TLE9210x_Type* TLE9210x;

extern void TLE9210x_SetByte0GSB(en_TLE9210x_NumMaxType Num,uint8_t u8_data);
extern uint8_t TLE9210x_GetByte0GSB(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_FS(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_NPOR(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_TE(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_SUPE(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_VDSE(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_OC(en_TLE9210x_NumMaxType Num);
extern uint8_t TLE9210x_GetByte0GSB_SPIE(en_TLE9210x_NumMaxType Num);
extern void TLE9210_SetRamCopyNum(en_TLE9210x_NumMaxType Num);
extern void TLE9210x_Update_Status_GENSTAT(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_DSOV(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_HBVOUT_PWMERR(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_EFF_TDON_OFF1(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_EFF_TDON_OFF2(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_EFF_TDON_OFF3(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_TRISE_FALL1(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_TRISE_FALL2(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_TRISE_FALL3(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_GDF(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern void TLE9210x_Update_Status_DEVID(en_TLE9210x_NumMaxType Num,uint16_t u16_data);
extern uint16_t TLE9210x_Get_Reg_Status_GENSTAT(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_DSOV(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_HBVOUT_PWMERR(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF1(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF2(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_EFF_TDON_OFF3(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL1(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL2(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_TRISE_FALL3(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_GDF(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Status_DEVID(en_TLE9210x_NumMaxType Num);
extern uint16_t TLE9210x_Get_Reg_Control_HBMODE(en_TLE9210x_NumMaxType Num);

/** @}*/ /* End of group TLE9210x */

#endif /* TLE9210x_H */
