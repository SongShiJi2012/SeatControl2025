/*******************************************************************************
 *  $File Name$       : lpspi_master_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef LPSPI_MASTER_DRIVER_H
#define LPSPI_MASTER_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_spi.h"
//#include "osif.h"
#include "status.h"
#include <stdbool.h>
#include "callbacks.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IRQn_Type InterruptIndex

#define LPSPI_Type SPI_SFRmap
 /** Number of instances of the SPI module. */
#define LPSPI_INSTANCE_COUNT                     (3u)//KF32A156 : SPI0 SPI1 SPI2
/* ADC - Peripheral instance base addresses */
/** Peripheral SPI0 base pointer */
#define SPI0                                     (SPI0_SFR)
/** Peripheral SPI1 base pointer */
#define SPI1                                     (SPI1_SFR)
/** Peripheral SPI1 base pointer */
#define SPI2                                     (SPI2_SFR)
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1 ,SPI2 }

/** Interrupt vectors for the LPSPI peripheral type */
#define LPSPI_IRQS                               { INT_SPI0, INT_SPI1, INT_SPI2 }

/* Pointer to runtime state structure.*/
#define FEATURE_LPSPI_STATE_STRUCTURES_NULL {NULL, NULL, NULL}

/*! @brief LPSPI Peripheral Chip Select (PCS) configuration (which PCS to configure).
 * Implements : lpspi_which_pcs_t_Class
 */
typedef enum
{
    LPSPI_PCS0 = 0U, /*!< PCS[0] */
    LPSPI_PCS1 = 1U, /*!< PCS[1] */
    LPSPI_PCS2 = 2U, /*!< PCS[2] */
    LPSPI_PCS3 = 3U  /*!< PCS[3] */
} lpspi_which_pcs_t;

/*! @brief LPSPI Signal (PCS and Host Request) Polarity configuration.
 * Implements : lpspi_signal_polarity_t_Class
 */
typedef enum
{
    LPSPI_ACTIVE_HIGH = 1U, /*!< Signal is Active High (idles low). */
    LPSPI_ACTIVE_LOW  = 0U  /*!< Signal is Active Low (idles high). */
} lpspi_signal_polarity_t;

/*! @brief LPSPI clock phase configuration.
 * Implements : lpspi_clock_phase_t_Class
 */
typedef enum
{
    LPSPI_CLOCK_PHASE_1ST_EDGE = 0U, /*!< Data captured on SCK 1st edge, changed on 2nd. */
    LPSPI_CLOCK_PHASE_2ND_EDGE = 1U  /*!< Data changed on SCK 1st edge, captured on 2nd. */
} lpspi_clock_phase_t;

/*! @brief LPSPI Clock Signal (SCK) Polarity configuration.
 * Implements : lpspi_sck_polarity_t_Class
 */
typedef enum
{
    LPSPI_SCK_ACTIVE_HIGH = 0U, /*!< Signal is Active High (idles low). */
    LPSPI_SCK_ACTIVE_LOW  = 1U  /*!< Signal is Active Low (idles high). */
} lpspi_sck_polarity_t;

 /*! @brief Type of error reported by LPSPI
  */
typedef enum
{
    LPSPI_TRANSFER_OK = 0U,    /*!< Transfer OK */
    LPSPI_TRANSMIT_FAIL,       /*!< Error during transmission */
    LPSPI_RECEIVE_FAIL         /*!< Error during reception */
} transfer_status_t;

 /*! @brief Type of LPSPI transfer (based on interrupts or DMA).
  * Implements : lpspi_transfer_type_Class
  */
typedef enum
{
    LPSPI_USING_DMA         = 0,    /*!< The driver will use DMA to perform SPI transfer */
    LPSPI_USING_INTERRUPTS,         /*!< The driver will use interrupts to perform SPI transfer */
    LPSPI_USING_POLLING,         /*!< The driver will use polling to perform SPI transfer */
} lpspi_transfer_type;

/*!
 * @brief Runtime state structure for the LPSPI master driver.
 *
 * This structure holds data that is used by the LPSPI peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 * The user must pass  the memory for this run-time state structure. The
 * LPSPI master driver populates the members.
 * Implements : lpspi_state_t_Class
 */
typedef struct
{
    uint16_t bitsPerFrame;               /*!< Number of bits per frame: 8- to 4096-bits; needed for
                                              TCR programming */
    //uint16_t bytesPerFrame;              /*!< Number of bytes per frame: 1- to 512-bytes */
    //bool isPcsContinuous;                /*!< Option to keep chip select asserted until transfer
                                             // complete; needed for TCR programming */
    bool isBlocking;                     /*!< Save the transfer type */
    uint32_t lpspiSrcClk;                /*!< Module source clock */
    volatile bool isTransferInProgress;  /*!< True if there is an active transfer */
    const uint8_t * txBuff;                      /*!< The buffer from which transmitted bytes are taken */
    uint8_t * rxBuff;                    /*!< The buffer into which received bytes are placed */
    volatile uint16_t txCount;           /*!< Number of bytes remaining to send  */
    volatile uint16_t rxCount;           /*!< Number of bytes remaining to receive */
    //volatile uint16_t txFrameCnt;        /*!< Number of bytes from current frame which were already sent */
    //volatile uint16_t rxFrameCnt;        /*!< Number of bytes from current frame which were already received */
    volatile uint8_t lsb;                   /*!< True if first bit is LSB and false if first bit is MSB */
    //uint8_t fifoSize;                    /*!< RX/TX fifo size */
    uint8_t rxDMAChannel;                /*!< Channel number for DMA rx channel */
    uint8_t txDMAChannel;                /*!< Channel number for DMA tx channel */
    lpspi_transfer_type transferType;    /*!< Type of LPSPI transfer */
   // semaphore_t lpspiSemaphore;          /*!< The semaphore used for blocking transfers */
    transfer_status_t status;            /*!< The status of the current */
    spi_callback_t callback;             /*!< Select the callback to transfer complete */
    void *callbackParam;                 /*!< Select additional callback parameters if it's necessary */
    uint32_t dummy;                      /*!< This field is used for the cases when TX is NULL and LPSPI is in DMA mode */
} lpspi_state_t;

/*!
 * @brief Data structure containing information about a device on the SPI bus.
 *
 * The user must populate these members to set up the LPSPI master and
 * properly communicate with the SPI device.
 * Implements : lpspi_master_config_t_Class
 */
typedef struct
{
    uint32_t bitsPerSec;                 /*!< Baud rate in bits per second*/
    lpspi_which_pcs_t whichPcs;          /*!< Selects which PCS to use */
    lpspi_signal_polarity_t pcsPolarity; /*!< PCS polarity */
    //bool isPcsContinuous;                /*!< Keeps PCS asserted until transfer complete */
    uint16_t bitcount;                   /*!< Number of bits/frame, minimum is 8-bits */
    uint32_t lpspiSrcClk;                /*!< Module source clock */
    lpspi_clock_phase_t clkPhase;        /*!< Selects which phase of clock to capture data */
    lpspi_sck_polarity_t clkPolarity;    /*!< Selects clock polarity */
    uint8_t bitFirst;                       /*!< Option to transmit LSB first */
    lpspi_transfer_type transferType;    /*!< Type of LPSPI transfer */
    //uint8_t rxDMAInstance;
    uint8_t rxDMAChannel;                /*!< Channel number for DMA rx channel. If DMA mode isn't used this field will be ignored. */
    //uint8_t txDMAInstance;                /*!< Channel number for DMA tx channel. If DMA mode isn't used this field will be ignored. */
    uint8_t txDMAChannel;
    spi_callback_t callback;             /*!< Select the callback to transfer complete */
    void *callbackParam;                 /*!< Select additional callback parameters if it's necessary */
} lpspi_master_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and shutdown
 * @{
 */
 
/*!
 * @brief Initializes a LPSPI instance for interrupt driven master mode operation.
 *
 * This function uses an interrupt-driven method for transferring data.
 * In this function, the term "spiConfig" is used to indicate the SPI device for which the LPSPI
 * master is communicating.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, un-gates the clock to the LPSPI module, resets the LPSPI module,
 * configures the IRQ state structure, enables the module-level interrupt to the core, and
 * enables the LPSPI module.
 * This is an example to set up the lpspi_master_state_t and call the
 * LPSPI_DRV_MasterInit function by passing in these parameters:
   @code
    lpspi_master_state_t lpspiMasterState;  <- the user  allocates memory for this structure
    lpspi_master_config_t spiConfig;  Can declare more configs for use in transfer functions
    spiConfig.bitsPerSec = 500000;
    spiConfig.whichPcs = LPSPI_PCS0;
    spiConfig.pcsPolarity = LPSPI_ACTIVE_LOW;
    spiConfig.isPcsContinuous = false;
    spiConfig.bitCount = 16;
    spiConfig.clkPhase = LPSPI_CLOCK_PHASE_1ST_EDGE;
    spiConfig.clkPolarity = LPSPI_ACTIVE_HIGH;
    spiConfig.lsbFirst= false;
    spiConfig.transferType = LPSPI_USING_INTERRUPTS;
    LPSPI_DRV_MasterInit(masterInstance, &lpspiMasterState, &spiConfig);
   @endcode
 *
 * @param instance The instance number of the LPSPI peripheral.
 * @param lpspiState The pointer to the LPSPI master driver state structure. The user
 *  passes the memory for this run-time state structure. The LPSPI master driver
 *  populates the members. This run-time state structure keeps track of the
 *  transfer in progress.
 * @param spiConfig The data structure containing information about a device on the SPI bus
 * @return An error code or STATUS_SUCCESS.
 */
status_t LPSPI_DRV_MasterInit(uint32_t instance, lpspi_state_t * lpspiState,
                                    const lpspi_master_config_t * spiConfig);

/*!
 * @brief Shuts down a LPSPI instance.
 *
 * This function resets the LPSPI peripheral, gates its clock, and disables the interrupt to
 * the core.  It first checks to see if a transfer is in progress and if so returns an error
 * status.
 *
 * @param instance The instance number of the LPSPI peripheral.
 * @return STATUS_SUCCESS The transfer has completed successfully, or
 *         STATUS_BUSY The transfer is still in progress.
 *         STATUS_ERROR if driver is error and needs to clean error.
 */
status_t LPSPI_DRV_MasterDeinit(uint32_t instance);

/*@}*/

/*!
 * @name Blocking transfers
 * @{
 */

/*!
 * @brief Performs an interrupt driven blocking SPI master mode transfer.
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
 * Depending on frame size sendBuffer and receiveBuffer must be aligned like this:
 * -1 byte if frame size <= 8 bits 
 * -2 bytes if 8 bits < frame size <= 16 bits 
 * -4 bytes if 16 bits < frame size   
 *
 * @param instance The instance number of the LPSPI peripheral.
 * @param sendBuffer The pointer to the data buffer of the data to send. You may pass NULL for this
 *  parameter and  bytes with a value of 0 (zero) is sent.
 * @param receiveBuffer Pointer to the buffer where the received bytes are stored. If you pass NULL
 *  for this parameter, the received bytes are ignored.
 * @param transferByteCount The number of bytes to send and receive which is equal to size of send or receive buffers
 * @param timeout A timeout for the transfer in milliseconds. If the transfer takes longer than
 *  this amount of time, the transfer is aborted and a STATUS_TIMEOUT error
 *  returned.
 * @return STATUS_SUCCESS The transfer was successful, or
 *         STATUS_BUSY Cannot perform transfer because a transfer is already in progress, or
 *         STATUS_TIMEOUT The transfer timed out and was aborted.
 */
status_t LPSPI_DRV_MasterTransferBlocking(uint32_t instance,
                                                const uint8_t * sendBuffer,
                                                uint8_t * receiveBuffer,
                                                uint16_t transferByteCount,
                                                uint32_t timeout);

/*@}*/

/*!
 * @name Non-blocking transfers
 * @{
 */

/*!
 * @brief Performs an interrupt driven non-blocking SPI master mode transfer.
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
 * Depending on frame size sendBuffer and receiveBuffer must be aligned like this:
 * -1 byte if frame size <= 8 bits 
 * -2 bytes if 8 bits < frame size <= 16 bits 
 * -4 bytes if 16 bits < frame size
 *
 * @param instance The instance number of the LPSPI peripheral.
 * @param spiConfig Pointer to the SPI configuration structure. This structure contains the settings
 *  for the SPI bus configuration in this transfer. You may pass NULL for this
 *  parameter, in which case the current bus configuration is used unmodified. The device can be
 *  configured separately by calling the LPSPI_DRV_MasterConfigureBus function.
 * @param sendBuffer The pointer to the data buffer of the data to send. You may pass NULL for this
 *  parameter and  bytes with a value of 0 (zero) is sent.
 * @param receiveBuffer Pointer to the buffer where the received bytes are stored. If you pass NULL
 *  for this parameter, the received bytes are ignored.
 * @param transferByteCount The number of bytes to send and receive which is equal to size of send or receive buffers
 * @return STATUS_SUCCESS The transfer was successful, or
 *         STATUS_BUSY Cannot perform transfer because a transfer is already in progress
 */
status_t LPSPI_DRV_MasterTransfer(uint32_t instance,
                                        const uint8_t * sendBuffer,
                                        uint8_t * receiveBuffer,
                                        uint16_t transferByteCount);
/*!
 * @brief Terminates an interrupt driven asynchronous transfer early.
 *
 * During an a-sync (non-blocking) transfer, the user has the option to terminate the transfer early
 * if the transfer is still in progress.
 *
 * @param instance The instance number of the LPSPI peripheral.
 * @return STATUS_SUCCESS The transfer was successful, or
 *         LPSPI_STATUS_NO_TRANSFER_IN_PROGRESS No transfer is currently in progress.
 */
status_t LPSPI_DRV_MasterAbortTransfer(uint32_t instance);

/*!
 * @brief Interrupt handler for LPSPI master mode.
 * This handler uses the buffers stored in the lpspi_master_state_t structs to transfer data.
 *
 * @param instance The instance number of the LPSPI peripheral.
 */
void LPSPI_DRV_MasterIRQHandler(uint32_t instance);

/*!
 * @brief The function LPSPI_DRV_IRQHandler passes IRQ control to either the master or
 * slave driver.
 *
 * The address of the IRQ handlers are checked to make sure they are non-zero before
 * they are called. If the IRQ handler's address is zero, it means that driver was
 * not present in the link (because the IRQ handlers are marked as weak). This would
 * actually be a program error, because it means the master/slave config for the IRQ
 * was set incorrectly.
 */
void LPSPI_DRV_IRQHandler(uint32_t instance);

/*!
 * @brief The function LPSPI_DRV_FillupTxBuffer writes data in TX hardware buffer
 * depending on driver state and number of bytes remained to send.
 */
void LPSPI_DRV_FillupTxBuffer(uint32_t instance);

void LPSPI_DRV_FillupSendTxBuffer(uint32_t instance);
/*!
 * @brief The function LPSPI_DRV_ReadRXBuffer reads data from RX hardware buffer and
 * writes this data in RX software buffer.
 */
void LPSPI_DRV_ReadRXBuffer(uint32_t instance);

/*!
 * @brief Disable the TEIE interrupts at the end of a transfer.
 * Disable the interrupts and clear the status for transmit/receive errors.
 */
void LPSPI_DRV_DisableTEIEInterrupts(uint32_t instance);/*!
 * @brief The function LPSPI_DRV_IRQHandler passes IRQ control to either the master or
 * slave driver.
 *
 * The address of the IRQ handlers are checked to make sure they are non-zero before
 * they are called. If the IRQ handler's address is zero, it means that driver was
 * not present in the link (because the IRQ handlers are marked as weak). This would
 * actually be a program error, because it means the master/slave config for the IRQ
 * was set incorrectly.
 */
void LPSPI_DRV_IRQHandler(uint32_t instance);

/*!
 * @brief The function LPSPI_DRV_FillupTxBuffer writes data in TX hardware buffer
 * depending on driver state and number of bytes remained to send.
 */
void LPSPI_DRV_FillupTxBuffer(uint32_t instance);

void LPSPI_DRV_FillupSendTxBuffer(uint32_t instance);
/*!
 * @brief The function LPSPI_DRV_ReadRXBuffer reads data from RX hardware buffer and
 * writes this data in RX software buffer.
 */
void LPSPI_DRV_ReadRXBuffer(uint32_t instance);

/*!
 * @brief Disable the TEIE interrupts at the end of a transfer.
 * Disable the interrupts and clear the status for transmit/receive errors.
 */
void LPSPI_DRV_DisableTEIEInterrupts(uint32_t instance);

void LPSPI_DRV_DeInit(uint32_t instance);

#endif /* __LPSPI_MASTER_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
