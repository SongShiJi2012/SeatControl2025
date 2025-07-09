/*
 * flash_driver.h
 *
 *  Created on: 2022-6-15
 *      Author: Administrator
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include "status.h"
#include <stdint.h>

/******************************************************************************
*                      Functional defineition                                 *
******************************************************************************/

#define FEATURE_FLS_PF_BLOCK_SECTOR_SIZE (1024u)
#define FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE (8u)

/* Word size 2 bytes */
#define FTFx_WORD_SIZE     0x0002U
/* Long word size 4 bytes */
#define FTFx_LONGWORD_SIZE 0x0004U
/* Phrase size 8 bytes */
#define FTFx_PHRASE_SIZE   0x0008U
/* Double-phrase size 16 bytes */
#define FTFx_DPHRASE_SIZE  0x0010U


typedef void (* flash_callback_t)(void);

/*******************************************************************************
* Null Callback function definition
*******************************************************************************/
/*!
 * @name Null Callback function definition
 * @{
 */
/*! @brief  Null callback */
#define NULL_CALLBACK      ((flash_callback_t)0xFFFFFFFFU)

/*******************************************************************************
* Flash SSD Configuration Structure
*******************************************************************************/
/*!
 * @brief Flash User Configuration Structure
 *
 * Implements : flash_user_config_t_Class
 */
typedef struct
{
    uint32_t PFlashBase;            /*!< The base address of P-Flash memory */
    uint32_t PFlashSize;            /*!< The size in byte of P-Flash memory */
    uint32_t DFlashBase;            /*!< For FlexNVM device, this is the base address of D-Flash memory
                                     *    (FlexNVM memory); For non-FlexNVM device, this field is unused */
    uint32_t DFlashSize;             /*!< The base address of FlexRAM (for FlexNVM device)
                                     *    or acceleration RAM memory (for non-FlexNVM device) */
    flash_callback_t CallBack;      /*!< Call back function to service the time critical events. Any code reachable from this function
                                     *   must not be placed in a Flash block targeted for a program/erase operation */
} flash_user_config_t;

/*!
 * @brief Flash SSD Configuration Structure
 *
 * The structure includes the static parameters for C90TFS/FTFx which are
 * device-dependent. The fields including
 * PFlashBlockBase, PFlashBlockSize, DFlashBlockBase, EERAMBlockBase,
 * and CallBack are passed via flash_user_config_t.
 * The rest of parameters such as DFlashBlockSize, and EEEBlockSize will be
 * initialized in FLASH_DRV_Init() automatically.
 *
 * Implements : flash_ssd_config_t_Class
 */
typedef struct
{
	volatile uint32_t PFlashBase;          /*!< The base address of P-Flash memory */
	volatile uint32_t PFlashSize;          /*!< The size in byte of P-Flash memory */
	volatile uint32_t DFlashBase;          /*!< For FlexNVM device, this is the base address of D-Flash memory (FlexNVM memory);
                                   *    For non-FlexNVM device, this field is unused */
	volatile uint32_t DFlashSize;          /*!< For FlexNVM device, this is the size in byte of area
                                   *    which is used as D-Flash from FlexNVM memory;
                                   *    For non-FlexNVM device, this field is unused */
	volatile uint32_t EERAMBase;           /*!< The base address of FlexRAM (for FlexNVM device)
                                   *    or acceleration RAM memory (for non-FlexNVM device) */
	volatile uint32_t EEESize;             /*!< For FlexNVM device, this is the size in byte of EEPROM area which was partitioned
                                   *    from FlexRAM; For non-FlexNVM device, this field is unused */
    flash_callback_t CallBack;    /*!< Call back function to service the time critical events. Any code reachable from this function
                                   *   must not be placed in a Flash block targeted for a program/erase operation */
} flash_ssd_config_t;

/*!
 * @brief EEPROM status structure
 *
 * Implements : flash_eeprom_status_t_Class
 */
typedef struct
{
    uint8_t brownOutCode;               /*!< Brown-out detection code */
    uint16_t numOfRecordReqMaintain;    /*!< Number of EEPROM quick write records requiring maintenance */
    uint16_t sectorEraseCount;          /*!< EEPROM sector erase count */
} flash_eeprom_status_t;
status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf,flash_ssd_config_t * const pSSDConfig);
status_t FLASH_DRV_EraseSector(const flash_ssd_config_t * pSSDConfig,uint32_t dest,uint32_t size);
void FLASH_DRV_TaskRunFlag(void);
status_t FLASH_DRV_Program(const flash_ssd_config_t * pSSDConfig,uint32_t dest,uint32_t size,const uint8_t * pData);

#endif /* FLASH_DRIVER_H_ */
