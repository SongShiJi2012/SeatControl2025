/*******************************************************************************
 *  $File Name$       : edma_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef FLEXCAN_DRIVER_H
#define FLEXCAN_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_canfd.h"
#include <stdbool.h>
#include "status.h"
//#include "osif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define D_CANFD_MAILBOX_RX_NUM              (2u)
#define D_CANFD_MAILBOX_TX_NUM				(1u)

#define D_CANFD_MAILBOX_TX_START            (Mailbox_0)
#define D_CANFD_MAILBOX_TX_END				(D_CANFD_MAILBOX_TX_START+D_CANFD_MAILBOX_TX_NUM)
#define D_CANFD_MAILBOX_RX_START			(D_CANFD_MAILBOX_TX_END+1)
#define D_CANFD_MAILBOX_RX_END				(D_CANFD_MAILBOX_RX_START + D_CANFD_MAILBOX_RX_NUM)


/* @brief Has Flexible Data Rate */
#define FEATURE_CAN_HAS_FD                  (1)

#define IRQn_Type InterruptIndex

#define CAN_Type uint8_t

 /** Number of instances of the CAN module. */
#define CAN_INSTANCE_COUNT                       (2u)//

/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { CANfd6, CANfd7 }

/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM              (51U)

/* @brief Maximum number of Message Buffers supported for payload size 8 for CANFD6 */
#define FEATURE_CANFD6_MAX_MB_NUM				(51U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CANFD7 */
#define FEATURE_CANFD7_MAX_MB_NUM				(51U)

/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CANFD6_MAX_MB_NUM, FEATURE_CANFD7_MAX_MB_NUM}

/*! @brief The type of the event which occurred when the callback was invoked.
 * Implements : flexcan_event_type_t_Class
 */
typedef enum {
    FLEXCAN_EVENT_RX_COMPLETE,     /*!< A frame was received in the configured Rx MB. */
    FLEXCAN_EVENT_RXFIFO_COMPLETE, /*!< A frame was received in the Rx FIFO. */
    FLEXCAN_EVENT_RXFIFO_WARNING,  /*!< Rx FIFO is almost full (5 frames). */
    FLEXCAN_EVENT_RXFIFO_OVERFLOW, /*!< Rx FIFO is full (incoming message was lost). */
    FLEXCAN_EVENT_TX_COMPLETE,     /*!< A frame was sent from the configured Tx MB. */
    FLEXCAN_EVENT_ERROR
} flexcan_event_type_t;

/*! @brief The state of a given MB (idle/Rx busy/Tx busy).
 * Implements : flexcan_mb_state_t_Class
 */
typedef enum {
    FLEXCAN_MB_IDLE,      /*!< The MB is not used by any transfer. */
    FLEXCAN_MB_RX_BUSY,   /*!< The MB is used for a reception. */
    FLEXCAN_MB_TX_BUSY,   /*!< The MB is used for a transmission. */
} flexcan_mb_state_t;

/*! @brief FlexCAN Message Buffer ID type
 * Implements : flexcan_msgbuff_id_type_t_Class
 */
typedef enum {
    FLEXCAN_MSG_ID_STD,         /*!< Standard ID*/
    FLEXCAN_MSG_ID_EXT          /*!< Extended ID*/
} flexcan_msgbuff_id_type_t;


/*! @brief FlexCAN message buffer structure
 * Implements : flexcan_msgbuff_t_Class
 */
typedef struct {
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msgId;                     /*!< Message Buffer ID*/
    uint8_t data[64];                   /*!< Data bytes of the FlexCAN message*/
    uint8_t dataLen;                    /*!< Length of data in bytes */
} flexcan_msgbuff_t;

/*! @brief Information needed for internal handling of a given MB.
 * Implements : flexcan_mb_handle_t_Class
 */
typedef struct {
	Canfd_MailboxHeaderType *mb_message;//flexcan_msgbuff_t *mb_message;       /*!< The FlexCAN MB structure */
   // semaphore_t mbSema;                  /*!< Semaphore used for signaling completion of a blocking transfer */
    volatile flexcan_mb_state_t state;   /*!< The state of the current MB (idle/Rx busy/Tx busy) */
   // bool isBlocking;                     /*!< True if the transfer is blocking */
    //bool isRemote;                       /*!< True if the frame is a remote frame */
} flexcan_mb_handle_t;

/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should not be
 *      modified by users. Also, contents of the structure are subject to change in
 *      future releases.
 * Implements : flexcan_state_t_Class
 */
typedef struct FlexCANState {
    flexcan_mb_handle_t mbs[FEATURE_CAN_MAX_MB_NUM];           /*!< Array containing information
                                                                    related to each MB */
    void (*callback)(uint8_t instance,
                     flexcan_event_type_t eventType,
                     uint32_t buffIdx,
                     struct FlexCANState *driverState);        /*!< IRQ handler callback function. */
    void *callbackParam;                                       /*!< Parameter used to pass user data
                                                                    when invoking the callback
                                                                    function. */
    void (*error_callback)(uint8_t instance,
                           flexcan_event_type_t eventType,
                           struct FlexCANState *driverState);  /*!< Error IRQ handler callback
                                                                    function. */
    void *errorCallbackParam;                                  /*!< Parameter used to pass user data
                                                                    when invoking the error callback
                                                                    function. */
} flexcan_state_t;

/*! @brief FlexCAN data info from user
 * Implements : Canfd_MailboxHeaderType_Class
 */
typedef struct {
    flexcan_msgbuff_id_type_t msg_id_type;  /*!< Type of message ID (standard or extended)*/
    uint32_t data_length;                   /*!< Length of Data in Bytes*/
#if FEATURE_CAN_HAS_FD
    bool fd_enable;                         /*!< Enable or disable FD*/
    uint8_t fd_padding;                     /*!< Set a value for padding. It will be used when the data length code (DLC)
                                                 specifies a bigger payload size than data_length to fill the MB */
    bool enable_brs;                        /*!< Enable bit rate switch inside a CAN FD format frame*/
#endif
    bool is_remote;                         /*!< Specifies if the frame is standard or remote */
} flexcan_data_info_t;

/*! @brief FlexCAN Rx FIFO filters number
 * Implements : flexcan_rx_fifo_id_filter_num_t_Class
 */
typedef enum {
    FLEXCAN_RX_FIFO_ID_FILTERS_8   = 0x0,         /*!<   8 Rx FIFO Filters. @internal gui name="8 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_16  = 0x1,         /*!<  16 Rx FIFO Filters. @internal gui name="16 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_24  = 0x2,         /*!<  24 Rx FIFO Filters. @internal gui name="24 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_32  = 0x3,         /*!<  32 Rx FIFO Filters. @internal gui name="32 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_40  = 0x4,         /*!<  40 Rx FIFO Filters. @internal gui name="40 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_48  = 0x5,         /*!<  48 Rx FIFO Filters. @internal gui name="48 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_56  = 0x6,         /*!<  56 Rx FIFO Filters. @internal gui name="56 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_64  = 0x7,         /*!<  64 Rx FIFO Filters. @internal gui name="64 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_72  = 0x8,         /*!<  72 Rx FIFO Filters. @internal gui name="72 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_80  = 0x9,         /*!<  80 Rx FIFO Filters. @internal gui name="80 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_88  = 0xA,         /*!<  88 Rx FIFO Filters. @internal gui name="88 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_96  = 0xB,         /*!<  96 Rx FIFO Filters. @internal gui name="96 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_104 = 0xC,         /*!< 104 Rx FIFO Filters. @internal gui name="104 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_112 = 0xD,         /*!< 112 Rx FIFO Filters. @internal gui name="112 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_120 = 0xE,         /*!< 120 Rx FIFO Filters. @internal gui name="120 Rx FIFO Filters" */
    FLEXCAN_RX_FIFO_ID_FILTERS_128 = 0xF          /*!< 128 Rx FIFO Filters. @internal gui name="128 Rx FIFO Filters" */
} flexcan_rx_fifo_id_filter_num_t;

/*! @brief FlexCAN Rx FIFO ID filter table structure
 * Implements : flexcan_id_table_t_Class
 */
typedef struct {
    bool isRemoteFrame;      /*!< Remote frame*/
    bool isExtendedFrame;    /*!< Extended frame*/
    uint32_t id;             /*!< Rx FIFO ID filter element*/
} flexcan_id_table_t;

/*! @brief FlexCAN operation modes
 * Implements : flexcan_operation_modes_t_Class
 */
typedef enum {
    FLEXCAN_NORMAL_MODE,        /*!< Normal mode or user mode @internal gui name="Normal" */
    FLEXCAN_LISTEN_ONLY_MODE,   /*!< Listen-only mode @internal gui name="Listen-only" */
    FLEXCAN_LOOPBACK_MODE,      /*!< Loop-back mode @internal gui name="Loop back" */
    FLEXCAN_FREEZE_MODE,        /*!< Freeze mode @internal gui name="Freeze" */
    FLEXCAN_DISABLE_MODE        /*!< Module disable mode @internal gui name="Disabled" */
} flexcan_operation_modes_t;

#if FEATURE_CAN_HAS_FD
/*! @brief FlexCAN payload sizes
 * Implements : flexcan_fd_payload_size_t_Class
 */
typedef enum {
    FLEXCAN_PAYLOAD_SIZE_8 = 0,  /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_16 ,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_32 ,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_64      /*!< FlexCAN message buffer payload size in bytes*/
} flexcan_fd_payload_size_t;
#endif

/*! @brief FlexCAN bitrate related structures
 * Implements : flexcan_time_segment_t_Class
 */
typedef struct {
    uint32_t propSeg;         /*!< Propagation segment*/
    uint32_t phaseSeg1;       /*!< Phase segment 1*/
    uint32_t phaseSeg2;       /*!< Phase segment 2*/
    uint32_t preDivider;      /*!< Clock prescaler division factor*/
    uint32_t rJumpwidth;      /*!< Resync jump width*/
} flexcan_time_segment_t;

/*! @brief FlexCAN configuration
 * @internal gui name="Common configuration" id="flexcanCfg"
 * Implements : flexcan_user_config_t_Class
 */
typedef struct {
    flexcan_rx_fifo_id_filter_num_t num_id_filters; /*!< The number of RX FIFO ID filters needed
                                                         @internal gui name="Number of RX FIFO ID filters" id="num_id_filters" */
    bool is_rx_fifo_needed;                         /*!< 1 if needed; 0 if not. This controls whether the Rx FIFO feature is enabled or not.
                                                         @internal gui name="Use rx fifo" id="is_rx_fifo_needed" */
    flexcan_operation_modes_t flexcanMode;          /*!< User configurable FlexCAN operation modes.
                                                         @internal gui name="Flexcan Operation Mode" id="flexcanMode"*/
#if FEATURE_CAN_HAS_FD
    flexcan_fd_payload_size_t payload;              /*!< The payload size of the mailboxes specified in bytes. */
    bool fd_enable;                                 /*!< Enable/Disable the Flexible Data Rate feature. */
#endif
    flexcan_time_segment_t bitrate;                 /*!< The bitrate used for standard frames or for the arbitration phase of FD frames. */
#if FEATURE_CAN_HAS_FD
    flexcan_time_segment_t bitrate_cbt;             /*!< The bitrate used for the data phase of FD frames. */
#endif
} flexcan_user_config_t;

/*! @brief FlexCAN Driver callback function type
 * Implements : flexcan_callback_t_Class
 */
typedef void (*flexcan_callback_t)(uint8_t instance, flexcan_event_type_t eventType,
                                   uint32_t buffIdx, flexcan_state_t *flexcanState);

/*! @brief FlexCAN Driver error callback function type
 * Implements : flexcan_error_callback_t_Class
 */
typedef void (*flexcan_error_callback_t)(uint8_t instance, flexcan_event_type_t eventType,
                                         flexcan_state_t *flexcanState);

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes the FlexCAN peripheral.
 *
 * This function initializes
 * @param   instance                   A FlexCAN instance number
 * @param   state                      Pointer to the FlexCAN driver state structure.
 * @param   data                       The FlexCAN platform data
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_ERROR if other error occurred
 */
status_t FLEXCAN_DRV_Init(
       uint8_t instance,
       flexcan_state_t *state,
       const Can_ControllerConfigType *data);

/*!
 * @brief Shuts down a FlexCAN instance.
 *
 * @param   instance    A FlexCAN instance number
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_ERROR if failed
 */
status_t FLEXCAN_DRV_Deinit(uint8_t instance);

/*@}*/

/*!
 * @name Send configuration
 * @{
 */

/*!
 * @brief FlexCAN transmit message buffer field configuration.
 *
 * @param   instance                   A FlexCAN instance number
 * @param   mb_idx                     Index of the message buffer
 * @param   tx_info                    Data info
 * @param   msg_id                     ID of the message to transmit
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of the message buffer is invalid
 */
status_t FLEXCAN_DRV_ConfigTxMb(
    uint8_t instance,
    const uint8_t mb_idx,
    Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id);

/*!
 * @brief Sends a CAN frame using the specified message buffer, in a blocking manner.
 *
 * This function sends a CAN frame using a configured message buffer. The function
 * blocks until either the frame was sent, or the specified timeout expired.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   tx_info    Data info
 * @param   msg_id     ID of the message to transmit
 * @param   mb_data    Bytes of the FlexCAN message
 * @param   timeout_ms A timeout for the transfer in milliseconds.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy;
 *          STATUS_TIMEOUT if the timeout is reached
 */
status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    const Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data,
    uint32_t timeout_ms);

/*!
 * @brief Sends a CAN frame using the specified message buffer.
 *
 * This function sends a CAN frame using a configured message buffer. The function
 * returns immediately. If a callback is installed, it will be invoked after
 * the frame was sent.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   tx_info    Data info
 * @param   msg_id     ID of the message to transmit
 * @param   mb_data    Bytes of the FlexCAN message.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy
 */
status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint8_t mb_idx,
    const Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data);

/*@}*/

/*!
 * @name Receive configuration
 * @{
 */

/*!
 * @brief FlexCAN receive message buffer field configuration
 *
 * @param   instance                   A FlexCAN instance number
 * @param   mb_idx                     Index of the message buffer
 * @param   rx_info                    Data info
 * @param   msg_id                     ID of the message to transmit
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 */
status_t FLEXCAN_DRV_ConfigRxMb(
    const uint8_t instance,
    const uint8_t mb_idx,
    Canfd_MailboxHeaderType *rx_info);

/*!
 * @brief Receives a CAN frame using the specified message buffer, in a blocking manner.
 *
 * This function receives a CAN frame using a configured message buffer. The function
 * blocks until either a frame was received, or the specified timeout expired.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @param   timeout_ms A timeout for the transfer in milliseconds.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy;
 *          STATUS_TIMEOUT if the timeout is reached
 */
status_t FLEXCAN_DRV_ReceiveBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    Canfd_MailboxHeaderType *data,
    uint32_t timeout_ms);

/*!
 * @brief Receives a CAN frame using the specified message buffer.
 *
 * This function receives a CAN frame using a configured message buffer. The function
 * returns immediately. If a callback is installed, it will be invoked after
 * the frame was received and read into the specified buffer.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy
 */
status_t FLEXCAN_DRV_Receive(
    uint8_t instance,
    uint8_t mb_idx,
    Canfd_MailboxHeaderType *data);


/*@}*/

/*!
 * @name IRQ handler callback
 * @{
 */

/*!
 * @brief Installs a callback function for the IRQ handler.
 *
 * @param instance The FlexCAN instance number.
 * @param callback The callback function.
 * @param callbackParam User parameter passed to the callback function through the state parameter.
 */
void FLEXCAN_DRV_InstallEventCallback(uint8_t instance,
                                      flexcan_callback_t callback,
                                      void *callbackParam);

/*!
 * @brief Installs an error callback function for the IRQ handler and enables error interrupts.
 *
 * @param instance The FlexCAN instance number.
 * @param callback The error callback function.
 * @param callbackParam User parameter passed to the error callback function through the state
 *                      parameter.
 */
void FLEXCAN_DRV_InstallErrorCallback(uint8_t instance,
                                      flexcan_error_callback_t callback,
                                      void *callbackParam);

/*!
 * @brief Interrupt handler for a FlexCAN instance.
 *
 * @param   instance    The FlexCAN instance number.
 */
void FLEXCAN_IRQHandler(uint8_t instance);

/*!
 * @brief Error interrupt handler for a FlexCAN instance.
 *
 * @param   instance    The FlexCAN instance number.
 */
void FLEXCAN_Error_IRQHandler(uint8_t instance);

#endif /* FLEXCAN_DRIVER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
