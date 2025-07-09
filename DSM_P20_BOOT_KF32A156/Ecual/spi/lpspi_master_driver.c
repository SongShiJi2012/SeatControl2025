/*******************************************************************************
 *  $File Name$       : lpspi_master_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "lpspi_master_driver.h"
#include "edma_driver.h"
#include "kf32a156_int.h"
#include "system_init.h"
#include <math.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Table of base pointers for SPI instances. */
LPSPI_Type * g_lpspiBase[LPSPI_INSTANCE_COUNT] =  SPI_BASE_PTRS;

/*! @brief Table to save LPSPI IRQ enumeration numbers defined in the CMSIS header file. */
IRQn_Type g_lpspiIrqId[LPSPI_INSTANCE_COUNT] =  LPSPI_IRQS;

/* Pointer to runtime state structure.*/
lpspi_state_t * g_lpspiStatePtr[LPSPI_INSTANCE_COUNT] = FEATURE_LPSPI_STATE_STRUCTURES_NULL;
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
/* This function initialize a new SPI transfer */
static status_t LPSPI_DRV_MasterStartTransfer(uint32_t instance,
                                                    const uint8_t * sendBuffer,
                                                    uint8_t * receiveBuffer,
                                                    uint16_t transferByteCount);

/* This function cleans up state structure and hardware after a transfer is complete .*/
static void LPSPI_DRV_MasterCompleteTransfer(uint32_t instance);

/* Bus configuration */
static status_t LPSPI_DRV_MasterConfigureBus(uint32_t instance,
                                            const lpspi_master_config_t * spiConfig,
                                            uint32_t * calculatedBaudRate);


/* Callback for DMA transfer done.*/
static void LPSPI_DRV_MasterCompleteDMATransfer(void* parameter, edma_chn_status_t status);

/* Callback for RX DMA channel*/
static void LPSPI_DRV_MasterCompleteRX(void* parameter, edma_chn_status_t status);
/*******************************************************************************
 * Code
 ******************************************************************************/
 
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterInit
 * Description   : Initializes a LPSPI instance for interrupt driven master mode operation.
 *
 * This function uses an interrupt-driven method for transferring data.
 * In this function, the term "spiConfig" is used to indicate the SPI device for which the LPSPI
 * master is communicating.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, un-gates the clock to the LPSPI module, resets the LPSPI module,
 * configures the IRQ state structure, enables the module-level interrupt to the core, and
 * enables the LPSPI module.
 * Implements : LPSPI_DRV_MasterInit_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterInit(uint32_t instance, lpspi_state_t * lpspiState,
                                    const lpspi_master_config_t * spiConfig)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(lpspiState != NULL);
    //DEV_ASSERT(spiConfig != NULL);

    LPSPI_Type *base = g_lpspiBase[instance];
    status_t errorCode = STATUS_SUCCESS;

    /* Save runtime structure pointers so irq handler can point to the correct state structure */
    g_lpspiStatePtr[instance] = lpspiState;

    /* Configure bus for this device. If NULL is passed, we assume the caller has
     * preconfigured the bus and doesn't wish to re-configure it again for this transfer.
     * Do nothing for calculatedBaudRate. If the user wants to know the calculatedBaudRate
     * then they can call this function separately.
     */
    errorCode = LPSPI_DRV_MasterConfigureBus(instance, spiConfig, NULL);
    if (errorCode != STATUS_SUCCESS)
    {
        return errorCode;
    }
    /* When TX is null the value sent on the bus will be 0 */
    lpspiState->dummy = 0;
    /* Initialize the semaphore */
    //errorCode = OSIF_SemaCreate(&(lpspiState->lpspiSemaphore), 0);
    //DEV_ASSERT(errorCode == STATUS_SUCCESS);

	if(LPSPI_USING_DMA == spiConfig->transferType)
	{
	    /* Receive DMA */
	    SPI_Receive_DMA_INT_Enable(base, TRUE);
	    /* Send DMA */
	    SPI_Transmit_DMA_INT_Enable(base, TRUE);
	}

	if(LPSPI_USING_INTERRUPTS == spiConfig->transferType)
	{
		INT_Interrupt_Enable(g_lpspiIrqId[instance], TRUE);
	}

    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterDeinit
 * Description   : Shuts down a LPSPI instance.
 *
 * This function resets the LPSPI peripheral, gates its clock, and disables the interrupt to
 * the core.  It first checks to see if a transfer is in progress and if so returns an error
 * status.
 * Implements : LPSPI_DRV_MasterDeinit_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterDeinit(uint32_t instance)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);
    /* Instantiate local variable of type lpspi_state_t and point to global state */
    const lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    status_t errorCode = STATUS_SUCCESS;

    /* Check if a transfer is still in progress */
    //DEV_ASSERT(lpspiState->isTransferInProgress == false);

    /* Reset the LPSPI registers to their default state, inlcuding disabling the LPSPI */
    //LPSPI_Init(base);
    /* Clear the state pointer. */
    g_lpspiStatePtr[instance] = NULL;

    /* Destroy the semaphore */
    //errorCode = OSIF_SemaDestroy(&(lpspiState->lpspiSemaphore));
    //DEV_ASSERT(errorCode == STATUS_SUCCESS);
    return errorCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterConfigureBus
 * Description   : Configures the LPSPI port physical parameters to access a device on the bus when
 *                 the LSPI instance is configured for interrupt operation.
 *
 * In this function, the term "spiConfig" is used to indicate the SPI device for which the LPSPI
 * master is communicating. This is an optional function as the spiConfig parameters are
 * normally configured in the initialization function or the transfer functions, where these various
 * functions would call the configure bus function.
 * The user can pass in a different spiConfig structure to the transfer function which contains
 * the parameters for the SPI bus to allow for communication to a different SPI device
 * (the transfer function then calls this function). However, the user also has the option to call
 * this function directly especially to get the calculated baud rate, at which point they may pass
 * in NULL for the spiConfig structure in the transfer function (assuming they have called this
 * configure bus function first).
 * Implements : LPSPI_DRV_MasterConfigureBus_Activity
 *
 *END**************************************************************************/
static status_t LPSPI_DRV_MasterConfigureBus(uint32_t instance,
                                            const lpspi_master_config_t * spiConfig,
                                            uint32_t * calculatedBaudRate)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(spiConfig != NULL);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);

    /* Instantiate local variable of type lpspi_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    uint32_t baudRate;

    SPI_InitTypeDef Spi_ConfigPtr;

    /* SPI mode */
    Spi_ConfigPtr.m_Mode = SPI_MODE_MASTER_CLKDIV4;
    /* SPI clock */
    Spi_ConfigPtr.m_Clock = spiConfig->lpspiSrcClk;
    /* Data transfer start control */
    Spi_ConfigPtr.m_FirstBit = spiConfig->bitFirst;
    /* Spi idle state */
    Spi_ConfigPtr.m_CKP = spiConfig->clkPolarity;//SPI_CKP_LOW;
    /* Spi clock phase(Data shift edge) */
    Spi_ConfigPtr.m_CKE = spiConfig->clkPhase;//SPI_CKE_1EDGE;
    /* Data width */
    Spi_ConfigPtr.m_DataSize = spiConfig->bitcount;
    /* Baud rate :Fck_spi=Fck/2(m_BaudRate+1)*/
    Spi_ConfigPtr.m_BaudRate = (SYSCLK_FREQ_120MHz/(pow(4, (Spi_ConfigPtr.m_Mode+1))))/((spiConfig->bitsPerSec)*2) - 1;

    /* Check the bitcount to make sure it falls within the boundary conditions */
    if ((spiConfig->bitcount < SPI_DATASIZE_8BITS) || (spiConfig->bitcount > SPI_DATASIZE_32BITS))
    {
        return STATUS_ERROR;
    }

    /* Configure internal state structure for LPSPI */
    lpspiState->bitsPerFrame = spiConfig->bitcount;
    lpspiState->lpspiSrcClk = spiConfig->lpspiSrcClk;
    lpspiState->lsb = spiConfig->bitFirst;
    /* Save transfer type DMA/Interrupt */
    lpspiState->transferType = spiConfig->transferType;
    /* Update transfer status */
    lpspiState->isTransferInProgress = false;
    lpspiState->isBlocking = false;
    /* Store DMA channel number used in transfer */
    lpspiState->rxDMAChannel = spiConfig->rxDMAChannel;
    lpspiState->txDMAChannel = spiConfig->txDMAChannel;
    /* Store callback */
    lpspiState->callback = spiConfig->callback;
    lpspiState->callbackParam = spiConfig->callbackParam;

    /* Spi reset */
    SPI_Reset(base);
    /* Configure SPI module */
    SPI_Configuration(base, &Spi_ConfigPtr);
    SPI_Cmd(base, TRUE);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterTransferBlocking
 * Description   : Performs an interrupt driven blocking SPI master mode transfer.
 *
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function does not return until the transfer is complete.
 * This function allows the user to optionally pass in a SPI configuration structure which
 * allows the user to change the SPI bus attributes in conjunction with initiating a SPI transfer.
 * The difference between passing in the SPI configuration structure here as opposed to the
 * configure bus function is that the configure bus function returns the calculated baud rate where
 * this function does not. The user can also call the configure bus function prior to the transfer
 * in which case the user would simply pass in a NULL to the transfer function's device structure
 * parameter.
 * Implements : LPSPI_DRV_MasterTransferBlocking_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterTransferBlocking(uint32_t instance,
                                                const uint8_t * sendBuffer,
                                                uint8_t * receiveBuffer,
                                                uint16_t transferByteCount,
                                                uint32_t timeout)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);
    /* Instantiate local variable of type lpspi_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    status_t error = STATUS_SUCCESS;
    status_t osifError;
    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == (uint16_t)0)
    {
        return error;
    }
    
    /* Check if another transfer is in progress */
    if (SPI_Get_BUSY_Flag(base) == SET)
    {
        return STATUS_BUSY;
    }
    
    /* Dummy wait to ensure the semaphore is 0, no need to check result */
    if ((lpspiState->transferType == LPSPI_USING_DMA) || (lpspiState->transferType == LPSPI_USING_INTERRUPTS))
    {
    	//(void)OSIF_SemaWait(&(lpspiState->lpspiSemaphore), 0);
    }
    lpspiState->isBlocking = true;
    
    error = LPSPI_DRV_MasterStartTransfer(instance, sendBuffer, receiveBuffer,
                                          transferByteCount);
    /* Start the transfer process, if it returns an error code, return this back to user */
    if (error != STATUS_SUCCESS)
    {
        lpspiState->isBlocking = false;
        return error;
    }
    
    if ((lpspiState->transferType == LPSPI_USING_DMA) || (lpspiState->transferType == LPSPI_USING_INTERRUPTS))
    {
		/* As this is a synchronous transfer, wait until the transfer is complete.*/
		//osifError = OSIF_SemaWait(&(lpspiState->lpspiSemaphore), timeout);

		/* If a timeout occurs, stop the transfer by setting the isTransferInProgress to false and
		 * disabling interrupts, then return the timeout error status.
		 */
		if (osifError == STATUS_TIMEOUT)
		{
			/* Set isBlocking variable to false to avoid dummy semaphore post. */
			lpspiState->isBlocking = false;
			/* Complete transfer. */
			//LPSPI_DRV_MasterCompleteTransfer(instance);
			return(STATUS_TIMEOUT);
		}
    }

    return error;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterTransfer
 * Description   : Performs an interrupt driven non-blocking SPI master mode transfer.
 *
 * This function simultaneously sends and receives data on the SPI bus, as SPI is naturally
 * a full-duplex bus. The function returns immediately after initiating the transfer. The user
 * needs to check whether the transfer is complete using the LPSPI_DRV_MasterGetTransferStatus
 * function.
 * This function allows the user to optionally pass in a SPI configuration structure which
 * allows the user to change the SPI bus attributes in conjunction with initiating a SPI transfer.
 * The difference between passing in the SPI configuration structure here as opposed to the
 * configure bus function is that the configure bus function returns the calculated baud rate where
 * this function does not. The user can also call the configure bus function prior to the transfer
 * in which case the user would simply pass in a NULL to the transfer function's device structure
 * parameter.
 * Implements : LPSPI_DRV_MasterTransfer_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterTransfer(uint32_t instance,
                                        const uint8_t * sendBuffer,
                                        uint8_t * receiveBuffer,
                                        uint16_t transferByteCount)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);

    status_t error = STATUS_SUCCESS;
    /* If the transfer count is zero, then return immediately.*/
    if (transferByteCount == (uint16_t)0)
    {
        return STATUS_SUCCESS;
    }

    /* Start the transfer process, if it returns an error code, return this back to user */
    error = LPSPI_DRV_MasterStartTransfer(instance, sendBuffer, receiveBuffer,
                                          transferByteCount);
    if (error != STATUS_SUCCESS)
    {
        return error;
    }

    /* Else, return immediately as this is an async transfer */
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterAbortTransfer
 * Description   : Terminates an interrupt driven asynchronous transfer early.
 *
 * During an a-sync (non-blocking) transfer, the user has the option to terminate the transfer early
 * if the transfer is still in progress.
 * Implements : LPSPI_DRV_MasterAbortTransfer_Activity
 *END**************************************************************************/
status_t LPSPI_DRV_MasterAbortTransfer(uint32_t instance)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);
    LPSPI_Type *base = g_lpspiBase[instance];
    /* Stop the running transfer. */
    LPSPI_DRV_MasterCompleteTransfer(instance);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterStartTransfer
 * Description   : Configure a non-blocking transfer.
 *
 * The number of transferByteCount must be divided by number of bytes/frame.
 * The sendBuffer must be not NULL, but receiveBuffer can be NULL.
 *
 *END**************************************************************************/
static status_t LPSPI_DRV_MasterStartTransfer(uint32_t instance,
                                                    const uint8_t * sendBuffer,
                                                    uint8_t * receiveBuffer,
                                                    uint16_t transferByteCount)
{
    //DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    //DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);
    /* Instantiate local variable of type dspi_master_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    //edma_transfer_size_t dmaTransferSize = EDMA_TRANSFER_SIZE_1B;

    /* Check that we're not busy. */
    if (SPI_Get_BUSY_Flag(base) == SET)
    {
        return STATUS_BUSY;
    }

    lpspiState->status = LPSPI_TRANSFER_OK;

    /* Configure rxCount depending on transfer type.*/
    if (receiveBuffer == NULL)
    {
        lpspiState->rxCount = 0;
    }
    else
    {
        lpspiState->rxCount = transferByteCount;
    }
        
    if (lpspiState->transferType == LPSPI_USING_INTERRUPTS)
    {

        /* Fill out the other members of the run-time state structure. */
        lpspiState->txBuff = (const uint8_t *)sendBuffer;
        lpspiState->rxBuff = (uint8_t *)receiveBuffer;
        lpspiState->txCount = transferByteCount;

        /* Update transfer status */
        lpspiState->isTransferInProgress = true;

        /* Enable the TDF interrupt. */
        SPI_TNEIE_INT_Enable(base, TRUE);
    }
    else if(lpspiState->transferType == LPSPI_USING_POLLING)
    {
        /* Fill out the other members of the run-time state structure. */
        lpspiState->txBuff = (const uint8_t *)sendBuffer;
        lpspiState->rxBuff = (uint8_t *)receiveBuffer;
        lpspiState->txCount = transferByteCount;

        /* Update transfer status */
        lpspiState->isTransferInProgress = true;
        /* Transmit data */
        LPSPI_DRV_FillupSendTxBuffer(instance);
    }
    else
    {
        /* Configure RX DMA channel if is used in current transfer. */
        if(receiveBuffer != NULL)
        {
            /* Fill out the other members of the run-time state structure. */
            lpspiState->txBuff = (const uint8_t *)sendBuffer;
            lpspiState->rxBuff = (uint8_t *)receiveBuffer;
            lpspiState->txCount = transferByteCount;

            /* Update transfer status */
            lpspiState->isTransferInProgress = true;
            EDMA_DRV_Transmit(lpspiState->rxDMAChannel, (uint32_t)lpspiState->rxBuff, lpspiState->rxCount);
            //(void)EDMA_DRV_ConfigMultiBlockTransfer(lpspiState->rxDMAChannel, EDMA_TRANSFER_PERIPH2MEM,
             //                   (uint32_t)(&(base->RDR)),(uint32_t)receiveBuffer, dmaTransferSize, (uint32_t)1U<<(uint8_t)(dmaTransferSize),
             //                   (uint32_t)transferByteCount/(uint32_t)((uint32_t)1U <<(uint8_t)(dmaTransferSize)), true);
            (void)EDMA_DRV_InstallCallback(lpspiState->rxDMAChannel, (LPSPI_DRV_MasterCompleteRX),(void*)(instance));
        }
        /* Configure TX DMA channel */
        if (sendBuffer != NULL)
        {
            /* Fill out the other members of the run-time state structure. */
            lpspiState->txBuff = (const uint8_t *)sendBuffer;
            lpspiState->rxBuff = (uint8_t *)receiveBuffer;
            lpspiState->txCount = transferByteCount;

            /* Update transfer status */
            lpspiState->isTransferInProgress = true;
            //(void)EDMA_DRV_ConfigMultiBlockTransfer(lpspiState->txDMAChannel, EDMA_TRANSFER_MEM2PERIPH,
             //   (uint32_t)sendBuffer, (uint32_t)(&(base->TDR)), dmaTransferSize, (uint32_t)1U<<(uint8_t)(dmaTransferSize),
             //   (uint32_t)transferByteCount/(uint32_t)((uint32_t)1U <<(uint8_t)(dmaTransferSize)), true);

        	EDMA_DRV_Transmit(lpspiState->txDMAChannel, (uint32_t)lpspiState->txBuff, lpspiState->txCount);
        }
        else
        {
            /* Fill out the other members of the run-time state structure. */
            lpspiState->txBuff = (const uint8_t *)sendBuffer;
            lpspiState->rxBuff = (uint8_t *)receiveBuffer;
            lpspiState->txCount = transferByteCount;

            /* Update transfer status */
            lpspiState->isTransferInProgress = true;

            //(void)EDMA_DRV_ConfigMultiBlockTransfer(lpspiState->txDMAChannel, EDMA_TRANSFER_PERIPH2PERIPH,
                //(uint32_t)(&(lpspiState->dummy)), (uint32_t)(&(base->TDR)), dmaTransferSize, (uint32_t)1U<<(uint8_t)(dmaTransferSize),
                //(uint32_t)transferByteCount/(uint32_t)((uint32_t)1U <<(uint8_t)(dmaTransferSize)), true);
        	EDMA_DRV_Transmit(lpspiState->txDMAChannel, (uint32_t)(&(lpspiState->dummy)), 1);
        }

        /* If RX buffer is null the transfer is done when all bytes were sent. */
        (void)EDMA_DRV_InstallCallback(lpspiState->txDMAChannel, (LPSPI_DRV_MasterCompleteDMATransfer),(void*)(instance));

        /* Update transfer status */
        lpspiState->isTransferInProgress = true;
        /* Enable LPSPI DMA request */
        if (receiveBuffer!=NULL)
        {
        	SPI_Receive_DMA_INT_Enable(base, TRUE);
        }
        SPI_Transmit_DMA_INT_Enable(base, TRUE);

        //DMA_Oneshot_Enable(base, lpspiState->txDMAChannel, TRUE);
    }
    return STATUS_SUCCESS;
}

/*!
 * @brief Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the LPSPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 */
static void LPSPI_DRV_MasterCompleteTransfer(uint32_t instance)
{
    /* instantiate local variable of type dspi_master_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    /* The transfer is complete.*/
    lpspiState->isTransferInProgress = false;
    if(lpspiState->transferType == LPSPI_USING_DMA)
    {
        /* Disable LPSPI DMA request */
    	//SPI_Transmit_DMA_INT_Enable(base, FALSE);
    	//SPI_Receive_DMA_INT_Enable(base, FALSE);
    }
    else
    {
    	LPSPI_DRV_DisableTEIEInterrupts(instance);
    }

    if (lpspiState->isBlocking == true)
    {
        //(void)OSIF_SemaPost(&(lpspiState->lpspiSemaphore));
        lpspiState->isBlocking = false;
    }
    if (lpspiState->callback != NULL)
    {
        lpspiState->callback(lpspiState, SPI_EVENT_END_TRANSFER, lpspiState->callbackParam);
    }
}

/*!
 * @brief Finish up a transfer DMA.
 * The main purpose of this function is to create a function compatible with DMA callback type
 */
static void LPSPI_DRV_MasterCompleteDMATransfer(void* parameter, edma_chn_status_t status)
{
    uint32_t instance = (uint32_t)parameter;
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];

    if (status == EDMA_CHN_ERROR)
    {
        (void)LPSPI_DRV_MasterAbortTransfer(instance);
        lpspiState->status = LPSPI_TRANSMIT_FAIL;
    }
    else
    {
        /* Enable transfer complete flag interrupt to catch the end of the transfer. */
        lpspiState->txCount = 0;
        lpspiState->rxCount = 0;
		/* Waiting for spi to send no data */
		while(SPI_Get_BUSY_Flag(base)==SET);
		//LPSPI_DRV_MasterCompleteTransfer(instance);
    }
}

/*!
 * @brief Check if errors are detected on RX channel
 * The main purpose of this function is to check DMA errors on rx channel
 */
static void LPSPI_DRV_MasterCompleteRX(void* parameter, edma_chn_status_t status)
{
    uint32_t instance = (uint32_t)parameter;
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];

    if (status == EDMA_CHN_ERROR)
    {
        (void)LPSPI_DRV_MasterAbortTransfer(instance);
        lpspiState->status = LPSPI_TRANSMIT_FAIL;
    }
    else
    {
    	LPSPI_DRV_MasterCompleteTransfer(instance);
    }
}

/*!
 * @brief Interrupt handler for LPSPI master mode.
 * This handler uses the buffers stored in the lpspi_state_t structs to transfer data.
 * This is not a public API as it is called whenever an interrupt occurs.
 */
void LPSPI_DRV_MasterIRQHandler(uint32_t instance)
{
    /* Instantiate local variable of type dspi_master_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];

    /* Transmit data */
	if(SPI_Get_Transmit_Buf_Flag(base)==RESET)
    {
        if ((lpspiState->txCount != (uint16_t)0))
        {
            LPSPI_DRV_FillupTxBuffer(instance);
        }
    }
    if (lpspiState->txCount == (uint16_t)0)
    {
        /* Check if we're done with this transfer.*/
        if (lpspiState->rxCount == (uint16_t)0)
        {
			/* Waiting for spi to send no data */
			while(SPI_Get_BUSY_Flag(base)==SET);

            LPSPI_DRV_MasterCompleteTransfer(instance);
        }
    }
}

/*!
 * @brief Fill up the TX FIFO with data.
 * This function fills up the TX FIFO with data based on the bytes/frame.
 * This is not a public API as it is called from other driver functions.
 */
void LPSPI_DRV_FillupTxBuffer(uint32_t instance)
{
    /* Instantiate local variable of type dspi_master_state_t and point to global state. */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    uint32_t wordToSend = 0;
    uint16_t numOfBytes;
    /* Fill the TX buffer. */

	/* Get the number of bytes which can be written in a single 32 bits word. */
	numOfBytes = 1;//(uint16_t)(lpspiState->bytesPerFrame - lpspiState->txFrameCnt);

	wordToSend = 0;

	if (lpspiState->txBuff != NULL)
	{
		wordToSend = *((const uint8_t *)(lpspiState->txBuff));
		lpspiState->txBuff += sizeof(uint8_t);

		//lpspiState->txFrameCnt = (uint16_t)((lpspiState->txFrameCnt + numOfBytes) % lpspiState->bytesPerFrame);
	}
	/* Send data */
	SPI_I2S_SendData8(base,wordToSend);
	while(SPI_Get_BUSY_Flag(base)==SET);
    if (lpspiState->rxCount != (uint16_t)0)
    {
        LPSPI_DRV_ReadRXBuffer(instance);
    }
	//Loglevel_printf(LOG_LEVEL_DEBUG, "s: %x. \r\n", wordToSend);
	/* Update internal variable used in transmission. */
	lpspiState->txCount = (uint16_t)(lpspiState->txCount - sizeof(uint8_t));
}

void LPSPI_DRV_FillupSendTxBuffer(uint32_t instance)
{
    /* Instantiate local variable of type dspi_master_state_t and point to global state. */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    uint32_t wordToSend = 0;
    uint16_t numOfBytes;
    /* Fill the TX buffer. */
    while ((lpspiState->rxCount != 0)||((lpspiState->txCount != 0)))
    {
		/* Get the number of bytes which can be written in a single 32 bits word. */
		numOfBytes = 1;//(uint16_t)(lpspiState->bytesPerFrame - lpspiState->txFrameCnt);

		wordToSend = 0;
		/* Waiting for the sending buffer to be empty */
		while (SPI_Get_Transmit_Buf_Flag(SPI1_SFR))
			;
		if (lpspiState->txBuff != NULL)
		{
			wordToSend = *((const uint8_t *)(lpspiState->txBuff));
			lpspiState->txBuff += sizeof(uint8_t);

			//lpspiState->txFrameCnt = (uint16_t)((lpspiState->txFrameCnt + numOfBytes) % lpspiState->bytesPerFrame);
		}
		/* Send data */
		SPI_I2S_SendData8(base,wordToSend);
		/* Waiting to accept that the buffer is not empty */
		while (!SPI_Get_Receive_Buf_Flag(SPI1_SFR))
			;

		if (lpspiState->rxCount != (uint16_t)0)
		{
			LPSPI_DRV_ReadRXBuffer(instance);
		}
		else
		{
			SPI_I2S_ReceiveData(base);
		}
		//Loglevel_printf(LOG_LEVEL_DEBUG, "s: %x. \r\n", wordToSend);
		/* Update internal variable used in transmission. */
		lpspiState->txCount = (uint16_t)(lpspiState->txCount - sizeof(uint8_t));
    }
}
/*!
 * @brief Read all data from RX FIFO
 * This function will read all data from RX FIFO and will transfer this infromation in
 * RX software bufeer.
 * This is not a public API as it is called from other driver functions.
 */
void LPSPI_DRV_ReadRXBuffer(uint32_t instance)
{
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    uint32_t receivedWord;
    uint16_t numOfBytes;

	receivedWord = SPI_I2S_ReceiveData(base);
	/* Get the number of bytes which can be read from this 32 bites */
	//numOfBytes = (uint16_t)(lpspiState->bytesPerFrame - lpspiState->rxFrameCnt);

	/* Generate the word which will be write in buffer. */
	*(lpspiState->rxBuff) = (uint8_t)(receivedWord);
	lpspiState->rxBuff++;

	//lpspiState->rxFrameCnt = (uint16_t)((lpspiState->rxFrameCnt + numOfBytes) % lpspiState->bytesPerFrame);

	/* Update internal variable used in transmission. */
	lpspiState->rxCount = (uint16_t)(lpspiState->rxCount - 1);
}

/*!
 * @brief Disable the TEIE interrupts at the end of a transfer.
 * Disable the interrupts and clear the status for transmit/receive errors.
 */
void LPSPI_DRV_DisableTEIEInterrupts(uint32_t instance)
{
    LPSPI_Type *base = g_lpspiBase[instance];

    /* Disable RNEIE interrupt requests */
	SPI_RNEIE_INT_Enable(base, FALSE);
	/* Disable the TNEIE interrupt. */
	SPI_TNEIE_INT_Enable(base, FALSE);

}

void LPSPI_DRV_DeInit(uint32_t instance)
{
	 LPSPI_Type *base = g_lpspiBase[instance];
	 SPI_InitTypeDef Spi_ConfigPtr;

	 memset(&Spi_ConfigPtr,0,sizeof(SPI_InitTypeDef));

	 SPI_Cmd(base, FALSE);

	 base->BRGR = 0x00000000;
	 base->CTLR = 0x00000000;
	 base->BUFR = 0x00000000;
	 base->STR = 0x00000000;
	 SPI_Configuration(base,&Spi_ConfigPtr);
	 //SPI_Reset(base);
}
