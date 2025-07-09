/*
 * flash_driver.c
 *
 *  Created on: 2022-6-15
 *      Author: Administrator
 */

#include "system_init.h"
#include "Flash_Driver.h"
#include "kf32a156.h"
#include "kf32a156_int.h"
#include "ChipMessageApi.h"
#include "devassert.h"

#define FEATURE_FLS_HAS_FLEX_NVM (1u)
#define FEATURE_FLS_DF_BLOCK_SIZE (65536u)
#define FEATURE_FLS_FLEX_RAM_SIZE (4096u)
#define FEATURE_FLS_DF_BLOCK_SECTOR_SIZE (2048u)

/***********************************************************************************************
 * @function name:  uint32_t FlashEraseNPage(unsigned int Address, unsigned int Length)
 * @description:
 * @input parameters:      Address :address aligned by 1K
 *							Length :length like 1024 2048 3072 4096...
 * @output parameters:     void
 * @return:         uint32_t
 * @note:       CMD_SUCCESS									0x00
 *				BUSY 										0x0B
 *				SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION 	0x09
 *				INVALID_SECTOR 								0x07
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
uint8_t FlashEraseNPage(unsigned int Address, unsigned int Length)
{
	uint8_t FlashRetVal;
	uint32_t IntState;

	IntState = (INT_CTL0 & INT_CTL0_AIE);
	SFR_CLR_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);

	FlashRetVal = __FLASH_Erase__(Function_Parameter_Validate, Address, Length);
	if (IntState != 0)
	{
		SFR_SET_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);
	}

	return FlashRetVal;
}

/***********************************************************************************************
 * @function name:  status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf)
 * @description:
 * @input parameters:      pUserConf
 *							pSSDConfig
 * @output parameters:     void
 * @return:         status_t
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf,
                        flash_ssd_config_t * const pSSDConfig)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t FlashDrvTaskStart = 0;
#if 1
    DEV_ASSERT(pUserConf != NULL);
    DEV_ASSERT(pSSDConfig != NULL);
#if FEATURE_FLS_HAS_FLEX_NVM
    uint8_t DEPartitionCode;    /* store D/E-Flash Partition Code */
#endif

    pSSDConfig->PFlashBase = pUserConf->PFlashBase;
    pSSDConfig->PFlashSize = pUserConf->PFlashSize;
    pSSDConfig->DFlashBase = pUserConf->DFlashBase;
    pSSDConfig->DFlashSize = pUserConf->DFlashSize;
    pSSDConfig->CallBack = pUserConf->CallBack;

#if FEATURE_FLS_HAS_FLEX_NVM
    if (pSSDConfig->DFlashSize < FEATURE_FLS_DF_BLOCK_SIZE)
    {
        pSSDConfig->EEESize = FEATURE_FLS_FLEX_RAM_SIZE;
    }
    else
    {
        pSSDConfig->EEESize = 0U;
    }
#else /* FEATURE_FLS_HAS_FLEX_NVM == 0 */
    /* If size of D/E-Flash = 0 */
    pSSDConfig->DFlashSize = 0U;
    pSSDConfig->EEESize = 0U;
#endif /* End of FEATURE_FLS_HAS_FLEX_NVM */
#endif
    return ret;
}

/***********************************************************************************************
 * @function name:  status_t FLASH_DRV_EraseSector(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint32_t size)
 * @description:
 * @input parameters:      pSSDConfig
 *							dest
 *							size
 * @output parameters:     void
 * @return:         status_t
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
status_t FLASH_DRV_EraseSector(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint32_t size)
{
    DEV_ASSERT(pSSDConfig != NULL);
    status_t ret = STATUS_SUCCESS;       /* Return code variable */
    uint32_t sectorSize;                 /* Size of one sector   */
    uint32_t temp;                       /* Temporary variable   */
    uint32_t tempSize = size;            /* Temporary of size variation */

#if FEATURE_FLS_HAS_FLEX_NVM
    temp = pSSDConfig->DFlashBase;
    if ((dest >= temp) && (dest < (temp + pSSDConfig->DFlashSize)))
    {
       // DEV_ASSERT((dest % FEATURE_FLS_DF_SECTOR_CMD_ADDRESS_ALIGMENT) == 0U);
        dest += 0x800000U - temp;
        sectorSize = (uint32_t)FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;

    }
    else
#endif
    {
        temp = pSSDConfig->PFlashBase;
        if ((dest >= temp) && (dest < (temp + pSSDConfig->PFlashSize)))
        {
           // DEV_ASSERT((dest % FEATURE_FLS_PF_SECTOR_CMD_ADDRESS_ALIGMENT) == 0U);
            dest -= temp;
            sectorSize = (uint32_t)FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
        }
        else
        {
            ret = STATUS_ERROR;
            tempSize = 0U;
            sectorSize = 0U;
        }
    }

    /* Check if the size is sector alignment or not */
    if ((tempSize & (sectorSize - 1U)) != 0U)
    {
        /* Return an error code */
        ret = STATUS_ERROR;
    }

    while ((tempSize > 0U) && (STATUS_SUCCESS == ret))
    {
		if(CMD_SUCCESS == FlashEraseNPage(dest,sectorSize))
		{
			ret = STATUS_SUCCESS;
		}
		else
		{
			 ret = STATUS_ERROR;
		}

		/* Update size and destination address */
		tempSize -= sectorSize;
		dest += sectorSize;

    }
    return ret;
}

/***********************************************************************************************
 * @function name:  static uint32_t FlashWriteNBytes(unsigned int Address, unsigned int Length,
 * 							const unsigned char *Buffers)
 * @description:
 * @input parameters:       Address :address aligned by 1K
 * 				Length :The length must be no more than 1K
 * 				Buffers:input data
 * @output parameters:     void
 * @return:         uint32_t
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
static uint32_t FlashWriteNBytes(unsigned int Address, unsigned int Length, const unsigned char *Buffers)
{
	uint32_t IntState;

	unsigned int ReadTempBuffer[Length];

	IntState = (INT_CTL0 & INT_CTL0_AIE);
	SFR_CLR_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);

	memcpy(ReadTempBuffer,Buffers,Length);

	__FLASH_Program_NBytes__(Function_Parameter_Validate, Address, Length, ReadTempBuffer);
	if (IntState != 0)
	{
		SFR_SET_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);
	}

	return CMD_SUCCESS;
}

/***********************************************************************************************
 * @function name:  status_t FLASH_DRV_Program(const flash_ssd_config_t * pSSDConfig,
                           uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData)
 * @description:
 * @input parameters:      pSSDConfig
 * 							dest
 * 							size
 * 							pData
 * @output parameters:     void
 * @return:         status_t
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
status_t FLASH_DRV_Program(const flash_ssd_config_t * pSSDConfig,
                           uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData)
{
    DEV_ASSERT(pSSDConfig != NULL);
    DEV_ASSERT(pData != NULL);
    DEV_ASSERT((dest % FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE) == 0U);
    status_t ret = STATUS_SUCCESS;    /* Return code variable */
    uint32_t temp;
    uint8_t i;

    if ((size & (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE - 1U)) != 0U)
    {
        ret = STATUS_ERROR;
    }
    else
    {
    #if FEATURE_FLS_HAS_FLEX_NVM
        temp = pSSDConfig->DFlashBase;
        if ((dest >= temp) && (dest < (temp + pSSDConfig->DFlashSize)))
        {
            dest += 0x800000U - temp;
        }
        else
    #endif
        {
            temp = pSSDConfig->PFlashBase;
            if ((dest >= temp) && (dest < (temp + pSSDConfig->PFlashSize)))
            {
                dest -= temp;
            }
            else
            {
                ret = STATUS_ERROR;
            }
        }

        while ((size > 0U) && (STATUS_SUCCESS == ret))
        {
			FlashWriteNBytes(dest,FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE,pData);

			/* Update destination address for next iteration */
			dest += FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
			/* Update size for next iteration */
			size -= FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
			/* Increment the source address by 1 */
			pData += FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
        }
    }
    return ret;
}

/***********************************************************************************************
 * @function name:  void FlashReadNByte(unsigned int Address, unsigned int Length, unsigned char *Buffers)
 * @description:
 * @input parameters:       Address :Starting  address
 * 							Length :Read length
 * 							size
 * 							pData
 * @output parameters:    Buffers :Read data to Buffers
 * @return:         void
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
void FlashReadNByte(unsigned int Address, unsigned int Length, unsigned char *Buffers)
{
	for (int i = 0; i < Length; i++)
	{
		Buffers[i] = *(unsigned char *)Address++;
	}
}

/***********************************************************************************************
 * @function name:  uint32_t FlashCheckNBytes(unsigned int Address, unsigned int Length, unsigned char *Buffers)
 * @description:
 * @input parameters:       Address:address aligned by 1K
 * 							Length :must is 1024
 * 							Buffers:input data
 * @output parameters:    void
 * @return:     CMD_SUCCESS									0x00
 *				COUNT_ERROR(not bytes 1K 2K 3K 4K)			0x06
 * 				COMPARE_ERROR								0x0A
 *				ADDR_ERROR									0x0D
 *				ADDR_NOT_MAPPED								0x0E
 * @note:
 * @author:         2022-11-07 czb
 ***********************************************************************************************/
uint32_t FlashCheckNBytes(unsigned int Address, unsigned int Length, unsigned char *Buffers)
{
	uint32_t FlashRetVal, IntState;
	IntState = (INT_CTL0 & INT_CTL0_AIE);
	SFR_CLR_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);
	FlashRetVal = __FLASH_Check__(Address, Length, Buffers);
	if (IntState != 0)
	{
		SFR_SET_BIT_ASM(INT_CTL0, INT_CTL0_AIE_POS);
	}
	return FlashRetVal;
}


