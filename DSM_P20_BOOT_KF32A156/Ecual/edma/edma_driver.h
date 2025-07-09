/*******************************************************************************
 *  $File Name$       : edma_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef EDMA_DRIVER_H
#define EDMA_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_dma.h"
#include "status.h"
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IRQn_Type InterruptIndex

#define DMA_Type DMA_SFRmap

 /** Number of instances of the DMA module. */
#define DMA_INSTANCE_COUNT                       (2u)//KF32A156 : DMA0 DMA1
/* @brief Number of DMA interrupt lines. */
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (7U)
/* ADC - Peripheral instance base addresses */
/** Peripheral DMA0 base pointer */
#define DMA0                                     (DMA0_SFR)
/** Peripheral DMA1 base pointer */
#define DMA1                                     (DMA1_SFR)
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0, DMA1}
/* @brief Number of DMA virtual interrupt lines. */
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES (DMA_INSTANCE_COUNT*FEATURE_DMA_CHANNELS_INTERRUPT_LINES)
/* @brief Number of DMA virtual channels. */
#define FEATURE_DMA_VIRTUAL_CHANNELS FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { INT_DMA0, INT_DMA1}

/* @brief Number of DMA channels. */
#define FEATURE_DMA_CHANNELS (7U)

/* @brief DMA channel to instance */
#define FEATURE_DMA_VCH_TO_INSTANCE(x) 	((x) / ((uint32_t)FEATURE_DMA_CHANNELS))
/* @brief DMA virtual channel to channel */
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) % ((uint32_t)FEATURE_DMA_CHANNELS))

/*! @brief eDMA channel priority setting
 * Implements : edma_channel_priority_t_Class
 */
typedef enum {
    EDMA_CHN_PRIORITY_0 = 0U,
    EDMA_CHN_PRIORITY_1 = 1U,
    EDMA_CHN_PRIORITY_2 = 2U,
    EDMA_CHN_PRIORITY_3 = 3U,
    EDMA_CHN_PRIORITY_4 = 4U,
    EDMA_CHN_PRIORITY_5 = 5U,
    EDMA_CHN_PRIORITY_6 = 6U,
    EDMA_CHN_PRIORITY_7 = 7U,
    EDMA_CHN_PRIORITY_8 = 8U,
    EDMA_CHN_PRIORITY_9 = 9U,
    EDMA_CHN_PRIORITY_10 = 10U,
    EDMA_CHN_PRIORITY_11 = 11U,
    EDMA_CHN_PRIORITY_12 = 12U,
    EDMA_CHN_PRIORITY_13 = 13U,
    EDMA_CHN_PRIORITY_14 = 14U,
    EDMA_CHN_PRIORITY_15 = 15U,

    EDMA_CHN_DEFAULT_PRIORITY = 255U
} edma_channel_priority_t;

/*!
 * @brief Channel status for eDMA channel.
 *
 * A structure describing the eDMA channel status. The user can get the status by callback parameter
 * or by calling EDMA_DRV_getStatus() function.
 * Implements : edma_chn_status_t_Class
 */
typedef enum {
    EDMA_CHN_NORMAL = 0U,           /*!< eDMA channel normal state. */
    EDMA_CHN_ERROR                  /*!< An error occurred in the eDMA channel. */
} edma_chn_status_t;

/*!
 * @brief Definition for the eDMA channel callback function.
 *
 * Prototype for the callback function registered in the eDMA driver.
 * Implements : edma_callback_t_Class
 */
typedef void (*edma_callback_t)(void *parameter, edma_chn_status_t status);

/*! @brief Data structure for the eDMA channel state.
 * Implements : edma_chn_state_t_Class
 */
typedef struct {
    uint8_t virtChn;                     /*!< Virtual channel number. */
    edma_callback_t callback;            /*!< Callback function pointer for the eDMA channel. It will
                                              be called at the eDMA channel complete and eDMA channel
                                              error. */
    void *parameter;                     /*!< Parameter for the callback function pointer. */
    volatile edma_chn_status_t status;   /*!< eDMA channel status. */
} edma_chn_state_t;

/*!
 * @brief The user configuration structure for the an eDMA driver channel.
 *
 * Use an instance of this structure with the EDMA_DRV_ChannelInit() function. This allows the user to configure
 * settings of the EDMA channel with a single function call.
 * Implements : edma_channel_config_t_Class
 */
typedef struct {
    edma_channel_priority_t channelPriority; /*!< eDMA channel priority - only used when channel
                                                  arbitration mode is 'Fixed priority'. */
    //uint8_t virtInstance;					/*!< eDMA virtual channel number */
    uint8_t virtChnConfig;                   /*!< eDMA virtual channel number */
    uint32_t periphAddr;            		//外设起始地址
    uint32_t memoryAddr;            		//内存起始地址
    uint8_t transferDirection;
    uint8_t oneShotEn;						//软件出发使能
    edma_callback_t callback;                /*!< Callback that will be registered for this channel */
    void * callbackParam;                    /*!< Parameter passed to the channel callback */
    bool enableTrigger;                      /*!< Enables the periodic trigger capability for the DMA channel. */			
} edma_channel_config_t;


/*!
 * @brief Runtime state structure for the eDMA driver.
 *
 * This structure holds data that is used by the eDMA peripheral driver to manage
 * multi eDMA channels.
 * The user passes the memory for this run-time state structure and the eDMA
 * driver populates the members.
 * Implements : edma_state_t_Class
 */
typedef struct {
    edma_chn_state_t * volatile virtChnState[(uint32_t)FEATURE_DMA_VIRTUAL_CHANNELS];   /*!< Pointer array storing channel state. */
} edma_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Initializes the eDMA module.
 *
 * This function initializes the run-time state structure to provide the eDMA channel allocation
 * release, protect, and track the state for channels. This function also resets the eDMA modules,
 * initializes the module to user-defined settings and default settings.
 * @param edmaState The pointer to the eDMA peripheral driver state structure. The user passes
 * the memory for this run-time state structure and the eDMA peripheral driver populates the
 * members. This run-time state structure keeps track of the eDMA channels status. The memory must
 * be kept valid before calling the EDMA_DRV_DeInit.
 * @param userConfig User configuration structure for eDMA peripheral drivers. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 * @param chnStateArray Array of pointers to run-time state structures for eDMA channels;
 * will populate the state structures inside the eDMA driver state structure.
 * @param chnConfigArray Array of pointers to channel initialization structures.
 * @param chnCount The number of eDMA channels to be initialized.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_Init(edma_state_t * edmaState,
                       edma_chn_state_t * const chnStateArray[],
                       const edma_channel_config_t * const chnConfigArray[],
                       uint32_t chnCount);

void EDMA_DRV_Transmit(uint8_t virtualChannel, uint32_t srcAddr, uint16_t Number);

/*!
 * @brief De-initializes the eDMA module.
 *
 * This function resets the eDMA module to reset state and disables the interrupt to the core.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_Deinit(void);

/*!
 * @brief Initializes an eDMA channel.
 *
 * This function initializes the run-time state structure for a eDMA channel, based on user
 * configuration. It will request the channel, set up the channel priority and install the
 * callback.
 *
 * @param edmaChannelState Pointer to the eDMA channel state structure. The user passes
 * the memory for this run-time state structure and the eDMA peripheral driver populates the
 * members. This run-time state structure keeps track of the eDMA channel status. The memory must
 * be kept valid before calling the EDMA_DRV_ReleaseChannel.
 * @param edmaChannelConfig User configuration structure for eDMA channel. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_ChannelInit(edma_chn_state_t *edmaChannelState,
                              const edma_channel_config_t *edmaChannelConfig);

/*!
 * @brief Releases an eDMA channel.
 *
 * This function stops the eDMA channel and disables the interrupt of this channel. The channel state
 * structure can be released after this function is called.
 *
 * @param virtualChannel eDMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_ReleaseChannel(uint8_t virtualChannel);

/*!
  * @name eDMA Peripheral driver channel operation functions
  * @{
  */
/*!
 * @brief Starts an eDMA channel.
 *
 * This function enables the eDMA channel DMA request.
 *
 * @param virtualChannel eDMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_StartChannel(uint8_t virtualChannel);

/*!
 * @brief Stops the eDMA channel.
 *
 * This function disables the eDMA channel DMA request.
 *
 * @param virtualChannel eDMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_StopChannel(uint8_t virtualChannel);

/*!
 * @brief Registers the callback function and the parameter for eDMA channel.
 *
 * This function registers the callback function and the parameter into the eDMA channel state structure.
 * The callback function is called when the channel is complete or a channel error occurs. The eDMA
 * driver passes the channel status to this callback function to indicate whether it is caused by the
 * channel complete event or the channel error event.
 *
 * To un-register the callback function, set the callback function to "NULL" and call this
 * function.
 *
 * @param virtualChannel eDMA virtual channel number.
 * @param callback The pointer to the callback function.
 * @param parameter The pointer to the callback function's parameter.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t EDMA_DRV_InstallCallback(uint8_t virtualChannel,
                                  edma_callback_t callback,
                                  void *parameter);

/*!
 * @brief Gets the eDMA channel status.
 *
 * @param virtualChannel eDMA virtual channel number.
 *
 * @return Channel status.
 */
edma_chn_status_t EDMA_DRV_GetChannelStatus(uint8_t virtualChannel);

void EDMA_DRV_ClearIntStatus(uint8_t virtualChannel);

void EDMA_DRV_IRQHandler(uint8_t virtualChannel);

#endif /* EDMA_DRIVER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
