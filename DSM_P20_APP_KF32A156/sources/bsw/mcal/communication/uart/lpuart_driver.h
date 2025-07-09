/*******************************************************************************
 *  $File Name$       : lpuart_driver.h
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

#ifndef LPUART_DRIVER_H
#define LPUART_DRIVER_H

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "kf32a156_usart.h"
//#include "osif.h"
#include "edma_driver.h"
#include "callbacks.h"
#include <stdbool.h>
#include "status.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** Number of instances of the USART module. */
#define LPUART_INSTANCE_COUNT                      (3u)//KF32A156 : USART0[ToBLE] USART1  USART2[Debug]
/* ADC - Peripheral instance base addresses */
/** Peripheral USART0 base pointer */
#define USART0                                     (USART0_SFR)
/** Peripheral USART1 base pointer */
#define USART1                                     (USART1_SFR)
/** Peripheral USART1 base pointer */
#define USART2                                     (USART2_SFR)
/** Array initializer of USART peripheral base pointers */
#define LPUART_BASE_PTRS                            { USART0, USART1, USART1}
/** Interrupt vectors for the USART peripheral type */
#define LPUART_RX_TX_IRQS                        	{ INT_USART0, INT_USART1, INT_USART2}

/** USART - 外设寄存器内存结构 重定义 */
#define LPUART_Type									USART_SFRmap

/*! @brief Type of LPUART transfer (based on interrupts or DMA).
 *
 * Implements : lpuart_transfer_type_t_Class
 */
typedef enum
{
    LPUART_USING_DMA         = 0,    /*!< The driver will use DMA to perform UART transfer */
    LPUART_USING_INTERRUPTS,          /*!< The driver will use interrupts to perform UART transfer */
    LPUART_USING_POLLING
} lpuart_transfer_type_t;

/*! @brief LPUART number of bits in a character
 *
 * Implements : lpuart_bit_count_per_char_t_Class
 */
typedef enum
{
    LPUART_8_BITS_PER_CHAR  = 0x0U, /*!< 8-bit data characters */
    LPUART_9_BITS_PER_CHAR  = 0x1U, /*!< 9-bit data characters */
    LPUART_10_BITS_PER_CHAR = 0x2U  /*!< 10-bit data characters */
} lpuart_bit_count_per_char_t;

/*! @brief LPUART parity mode
 *
 * Implements : lpuart_parity_mode_t_Class
 */
typedef enum
{
    LPUART_PARITY_DISABLED = 0x0U, /*!< parity disabled */
    LPUART_PARITY_EVEN     = 0x2U, /*!< parity enabled, type even, bit setting: PE|PT = 10 */
    LPUART_PARITY_ODD      = 0x3U  /*!< parity enabled, type odd,  bit setting: PE|PT = 11 */
} lpuart_parity_mode_t;

/*! @brief LPUART number of stop bits
 *
 * Implements : lpuart_stop_bit_count_t_Class
 */
typedef enum
{
    LPUART_ONE_STOP_BIT = 0x0U, /*!< one stop bit */
    LPUART_TWO_STOP_BIT = 0x1U  /*!< two stop bits */
} lpuart_stop_bit_count_t;

/*!
 * @brief Runtime state of the LPUART driver.
 *
 * Note that the caller provides memory for the driver state structures during
 * initialization because the driver does not statically allocate memory.
 *
 * Implements : lpuart_state_t_Class
 */
typedef struct
{
    const uint8_t * txBuff;              /*!< The buffer of data being sent.*/
    uint8_t * rxBuff;                    /*!< The buffer of received data.*/
    volatile uint32_t txSize;            /*!< The remaining number of bytes to be transmitted. */
    volatile uint32_t rxSize;            /*!< The remaining number of bytes to be received. */
    volatile bool isTxBusy;              /*!< True if there is an active transmit.*/
    volatile bool isRxBusy;              /*!< True if there is an active receive.*/
    volatile bool isTxBlocking;          /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;          /*!< True if receive is blocking transaction. */
    lpuart_bit_count_per_char_t bitCountPerChar; /*!< number of bits in a char (8/9/10) */
    uart_callback_t rxCallback;          /*!< Callback to invoke for data receive
                                              Note: when the transmission is interrupt based, the callback
                                              is being called upon receiving a byte; when DMA transmission
                                              is used, the bytes are copied to the rx buffer by the DMA engine
                                              and the callback is called when all the bytes have been transferred. */
    void * rxCallbackParam;              /*!< Receive callback parameter pointer.*/
    uart_callback_t txCallback;          /*!< Callback to invoke for data send
                                              Note: when the transmission is interrupt based, the callback
                                              is being called upon sending a byte; when DMA transmission
                                              is used, the bytes are copied to the tx buffer by the DMA engine
                                              and the callback is called when all the bytes have been transferred. */
    void * txCallbackParam;              /*!< Transmit callback parameter pointer.*/
    lpuart_transfer_type_t transferType; /*!< Type of LPUART transfer (interrupt/dma based) */
    uint8_t rxDMAChannel;                /*!< DMA channel number for DMA-based rx. */
    uint8_t txDMAChannel;                /*!< DMA channel number for DMA-based tx. */
   // semaphore_t rxComplete;              /*!< Synchronization object for blocking Rx timeout condition */
   // semaphore_t txComplete;              /*!< Synchronization object for blocking Tx timeout condition */
    volatile status_t transmitStatus;    /*!< Status of last driver transmit operation */
    volatile status_t receiveStatus;     /*!< Status of last driver receive operation */
} lpuart_state_t;

/*! @brief LPUART configuration structure
 *
 * Implements : lpuart_user_config_t_Class
 */
typedef struct
{
    uint32_t baudRate;                           /*!< LPUART baud rate */
    lpuart_parity_mode_t parityMode;             /*!< parity mode, disabled (default), even, odd */
    lpuart_stop_bit_count_t stopBitCount;        /*!< number of stop bits, 1 stop bit (default) or 2 stop bits */
    lpuart_bit_count_per_char_t bitCountPerChar; /*!< number of bits in a character (8-default, 9 or 10);
                                                      for 9/10 bits chars, users must provide appropriate buffers
                                                      to the send/receive functions (bits 8/9 in subsequent bytes);
                                                      for DMA transmission only 8-bit char is supported. */
    lpuart_transfer_type_t transferType;         /*!< Type of LPUART transfer (interrupt/dma based) */
    uint8_t rxDMAChannel;                        /*!< Channel number for DMA rx channel.
                                                      If DMA mode isn't used this field will be ignored. */
    uint8_t txDMAChannel;                        /*!< Channel number for DMA tx channel.
                                                      If DMA mode isn't used this field will be ignored. */
} lpuart_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes an LPUART operation instance.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LPUART clock source in the application to initialize the LPUART.
 *
 * @param instance  LPUART instance number
 * @param lpuartUserConfig user configuration structure of type #lpuart_user_config_t
 * @param lpuartStatePtr pointer to the LPUART driver state structure
 * @return STATUS_SUCCESS if successful;
 *         STATUS_ERROR if an error occurred
 */
status_t LPUART_DRV_Init(uint32_t instance, lpuart_state_t * lpuartStatePtr,
                         const lpuart_user_config_t * lpuartUserConfig);

/*!
 * @brief Shuts down the LPUART by disabling interrupts and transmitter/receiver.
 *
 * @param instance  LPUART instance number
 * @return STATUS_SUCCESS if successful;
 *         STATUS_ERROR if an error occurred
 */
status_t LPUART_DRV_Deinit(uint32_t instance);

/*!
 * @brief Installs callback function for the LPUART receive.
 *
 * @note After a callback is installed, it bypasses part of the LPUART IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * @param instance The LPUART instance number.
 * @param function The LPUART receive callback function.
 * @param rxBuff The receive buffer used inside IRQHandler. This buffer must be kept as long as the callback is alive.
 * @param callbackParam The LPUART receive callback parameter pointer.
 * @return Former LPUART receive callback function pointer.
 */
uart_callback_t LPUART_DRV_InstallRxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam);

/*!
 * @brief Installs callback function for the LPUART transmit.
 *
 * @note After a callback is installed, it bypasses part of the LPUART IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * @param instance The LPUART instance number.
 * @param function The LPUART transmit callback function.
 * @param txBuff The transmit buffer used inside IRQHandler. This buffer must be kept as long as the callback is alive.
 * @param callbackParam The LPUART transmit callback parameter pointer.
 * @return Former LPUART transmit callback function pointer.
 */
uart_callback_t LPUART_DRV_InstallTxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam);

/*!
 * @brief Sends data out through the LPUART module using a blocking method.
 *
 *  Blocking means that the function does not return until the transmission is complete.
 *
 * @param instance  LPUART instance number
 * @param txBuff  source buffer containing 8-bit data chars to send
 * @param txSize the number of bytes to send
 * @param timeout timeout value in milliseconds
 * @return STATUS_SUCCESS if successful;
 *         STATUS_TIMEOUT if the timeout was reached;
 *         STATUS_BUSY if the resource is busy;
 *         STATUS_ERROR if an error occurred
 */
status_t LPUART_DRV_SendDataBlocking(uint32_t instance,
                                     const uint8_t * txBuff,
                                     uint32_t txSize,
                                     uint32_t timeout);

/*!
 * @brief Sends data out through the LPUART module using a non-blocking method.
 *  This enables an a-sync method for transmitting data. When used with
 *  a non-blocking receive, the LPUART can perform a full duplex operation.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the transmit status to know when the transmit is complete.
 *
 * @param instance  LPUART instance number
 * @param txBuff  source buffer containing 8-bit data chars to send
 * @param txSize  the number of bytes to send
 * @return STATUS_SUCCESS if successful;
 *         STATUS_BUSY if the resource is busy;
 */
status_t LPUART_DRV_SendData(uint32_t instance,
                             const uint8_t * txBuff,
                             uint32_t txSize);

/*!
 * @brief Gets data from the LPUART module by using a blocking method.
 *  Blocking means that the function does not return until the
 *  receive is complete.
 *
 * @param instance  LPUART instance number
 * @param rxBuff  buffer containing 8-bit read data chars received
 * @param rxSize the number of bytes to receive
 * @param timeout timeout value in milliseconds
 * @return STATUS_SUCCESS if successful;
 *         STATUS_TIMEOUT if the timeout was reached;
 *         STATUS_BUSY if the resource is busy;
 *         STATUS_UART_FRAMING_ERROR if a framing error occurred;
 *         STATUS_UART_NOISE_ERROR if a noise error occurred;
 *         STATUS_UART_PARITY_ERROR if a parity error occurred;
 *         STATUS_UART_RX_OVERRUN if an overrun error occurred;
 *         STATUS_ERROR if a DMA error occurred;
 */
status_t LPUART_DRV_ReceiveDataBlocking(uint32_t instance,
                                        uint8_t * rxBuff,
                                        uint32_t rxSize,
                                        uint32_t timeout);

/*!
 * @brief Receive multiple bytes of data using polling method.
 *
 *
 * @param   instance  LPUART instance number.
 * @param   rxBuff The buffer pointer which saves the data to be received.
 * @param   rxSize Size of data need to be received in unit of byte.
 * @return  STATUS_SUCCESS if the transaction is successful;
 *          STATUS_BUSY if the resource is busy;
 *          STATUS_UART_RX_OVERRUN if an overrun error occurred.
 */
status_t LPUART_DRV_ReceiveDataPolling(uint32_t instance, uint8_t *rxBuff, uint32_t rxSize);

status_t LPUART_DRV_ReceiveOneData(uint32_t instance,
                                       uint8_t *rxBuff);

/*!
 * @brief Gets data from the LPUART module by using a non-blocking method.
 *  This enables an a-sync method for receiving data. When used with
 *  a non-blocking transmission, the LPUART can perform a full duplex operation.
 *  Non-blocking means that the function returns immediately.
 *  The application has to get the receive status to know when the receive is complete.
 *
 * @param instance  LPUART instance number
 * @param rxBuff  buffer containing 8-bit read data chars received
 * @param rxSize  the number of bytes to receive
 * @return STATUS_SUCCESS if successful;
 *         STATUS_BUSY if the resource is busy
 */
status_t LPUART_DRV_ReceiveData(uint32_t instance,
                                uint8_t * rxBuff,
                                uint32_t rxSize);

#endif /* LPUART_DRIVER_H */

/******************************************************************************/
/* EOF */
/******************************************************************************/
