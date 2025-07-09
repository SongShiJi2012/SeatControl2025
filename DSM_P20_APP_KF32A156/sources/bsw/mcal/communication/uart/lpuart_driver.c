/*******************************************************************************
 *  $File Name$       : lpuart_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "lpuart_driver.h"
#include "lpuart_irq.h"
#include "kf32a156_int.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to lpuart runtime state structure */
static lpuart_state_t * s_lpuartStatePtr[LPUART_INSTANCE_COUNT] = {NULL};

/* Table of base addresses for lpuart instances. */
static LPUART_Type * const s_lpuartBase[LPUART_INSTANCE_COUNT] = LPUART_BASE_PTRS;

/* Table to save LPUART enum numbers defined in CMSIS files. */
static const IRQn_Type s_lpuartRxTxIrqId[LPUART_INSTANCE_COUNT] = LPUART_RX_TX_IRQS;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static status_t LPUART_DRV_StartSendDataUsingInt(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize);
static status_t LPUART_DRV_StartSendDataUsingPolling(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize);
static void LPUART_DRV_CompleteSendDataUsingInt(uint32_t instance);
static status_t LPUART_DRV_StartReceiveDataUsingInt(uint32_t instance,
                                                    uint8_t * rxBuff,
                                                    uint32_t rxSize);
static void LPUART_DRV_CompleteReceiveDataUsingInt(uint32_t instance);
static void LPUART_DRV_StopTxDma(uint32_t instance);
static void LPUART_DRV_StopRxDma(uint32_t instance);
static status_t LPUART_DRV_StartSendDataUsingDma(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize);
static void LPUART_DRV_TxDmaCallback(void * parameter, edma_chn_status_t status);
static status_t LPUART_DRV_StartReceiveDataUsingDma(uint32_t instance,
                                                    uint8_t * rxBuff,
                                                    uint32_t rxSize);
static void LPUART_DRV_RxDmaCallback(void * parameter, edma_chn_status_t status);
static void LPUART_DRV_PutData(uint32_t instance);
static void LPUART_DRV_GetData(uint32_t instance);
static void LPUART_DRV_RxIrqHandler(uint32_t instance);
static void LPUART_DRV_TxEmptyIrqHandler(uint32_t instance);
static void LPUART_DRV_TxCompleteIrqHandler(uint32_t instance);
static void LPUART_DRV_ErrIrqHandler(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Init
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * LPUART module transmitter and receiver.
 * The following is an example of how to set up the lpuart_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_Init function
 * by passing in these parameters:
 *    lpuart_user_config_t lpuartConfig;
 *    lpuartConfig.baudRate = 9600;
 *    lpuartConfig.bitCountPerChar = LPUART_8_BITS_PER_CHAR;
 *    lpuartConfig.parityMode = LPUART_PARITY_DISABLED;
 *    lpuartConfig.stopBitCount = LPUART_ONE_STOP_BIT;
 *    lpuartConfig.transferType = LPUART_USING_INTERRUPTS;
 *    lpuart_state_t lpuartState;
 *    LPUART_DRV_Init(instance, &lpuartState, &lpuartConfig);
 *
 * Implements    : LPUART_DRV_Init_Activity
 *END**************************************************************************/
status_t LPUART_DRV_Init(uint32_t instance, lpuart_state_t * lpuartStatePtr,
                         const lpuart_user_config_t * lpuartUserConfig)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(lpuartStatePtr != NULL);
    //DEV_ASSERT(lpuartUserConfig != NULL);

    status_t osStatusRxSem;
    status_t osStatusTxSem;
    LPUART_Type * base = s_lpuartBase[instance];
    uint32_t idx;
    uint32_t lpuartSourceClock;


    USART_InitTypeDef USART_InitStructure;
    USART_Struct_Init(&USART_InitStructure);
    /* Set Usart To Async Mode */
    USART_InitStructure.m_Mode = USART_MODE_FULLDUPLEXASY;
    USART_InitStructure.m_TransferDir = USART_DIRECTION_FULL_DUPLEX;
    USART_InitStructure.m_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.m_StopBits = USART_STOPBITS_1;

    /*  Set baudrate */
    USART_InitStructure.m_BaudRateBRCKS = USART_CLK_HFCLK;

    if(115200U == lpuartUserConfig->baudRate)//波特率要自己手动算,官方没推荐的参数.计算方法:时钟源/(16*m_BaudRateInteger*(1+m_BaudRateNumerator/m_BaudRateDenominator))
    {
        USART_InitStructure.m_BaudRateInteger = 8;
        USART_InitStructure.m_BaudRateNumerator = 1;
        USART_InitStructure.m_BaudRateDenominator = 13;
    }
    else if(38400U == lpuartUserConfig->baudRate)
    {
		USART_InitStructure.m_BaudRateInteger = 26;
		USART_InitStructure.m_BaudRateNumerator = 0;
		USART_InitStructure.m_BaudRateDenominator = 13;
    }
    else//暂不需要支持其他本波特率的设置,如需要支持，需手动计算且在此添加,并没有直接的计算方法生成
    {
    	return STATUS_UNSUPPORTED;
    }

    USART_Reset(base);
    USART_Configuration(base, &USART_InitStructure);
    USART_Passageway_Select_Config(base, USART_U7816R_PASSAGEWAY_TX1);
    USART_RESHD_Enable(base, TRUE);
    USART_Transmit_Data_Enable(base, TRUE);
    USART_Cmd(base, TRUE);

    /* Clear the state struct for this instance. */
    uint8_t *clearStructPtr = (uint8_t *)lpuartStatePtr;
    for (idx = 0; idx < sizeof(lpuart_state_t); idx++)
    {
        clearStructPtr[idx] = 0;
    }

    /* Save runtime structure pointer.*/
    s_lpuartStatePtr[instance] = lpuartStatePtr;

    /* Save the transfer information for runtime retrieval */
    lpuartStatePtr->transferType = lpuartUserConfig->transferType;
    lpuartStatePtr->bitCountPerChar = lpuartUserConfig->bitCountPerChar;
	lpuartStatePtr->rxDMAChannel = lpuartUserConfig->rxDMAChannel;
	lpuartStatePtr->txDMAChannel = lpuartUserConfig->txDMAChannel;

    /* initialize last driver operation status */
    lpuartStatePtr->transmitStatus = STATUS_SUCCESS;
    lpuartStatePtr->receiveStatus = STATUS_SUCCESS;

    /* Create the synchronization objects */
    //osStatusRxSem = OSIF_SemaCreate(&lpuartStatePtr->rxComplete, 0);
    //osStatusTxSem = OSIF_SemaCreate(&lpuartStatePtr->txComplete, 0);
    if ((osStatusRxSem == STATUS_ERROR) || (osStatusTxSem == STATUS_ERROR))
    {
        return STATUS_ERROR;
    }

    if(LPUART_USING_DMA == lpuartStatePtr->transferType)
    {
    	 USART_DMA_Write_Transmit_Enable(base,TRUE);
    	 INT_Interrupt_Enable(s_lpuartRxTxIrqId[instance], TRUE);//串口外设中断使能,DMA须和外设中断一起使用,否则DMA使用就不合理
    	 INT_Interrupt_Priority_Config(s_lpuartRxTxIrqId[instance], 7, 0);
    	 //使能外设对应的中断,比如接收中断,错误中断等等
    }
	if(LPUART_USING_INTERRUPTS == lpuartStatePtr->transferType)
	{
		INT_Interrupt_Enable(s_lpuartRxTxIrqId[instance], TRUE);//串口外设中断使能
		INT_Interrupt_Priority_Config(s_lpuartRxTxIrqId[instance], 7, 0);
		//使能外设对应的中断,比如接收中断,错误中断等等
	}

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Deinit
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 transmitter/receiver.
 *
 * Implements    : LPUART_DRV_Deinit_Activity
 *END**************************************************************************/
status_t LPUART_DRV_Deinit(uint32_t instance)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    const LPUART_Type * base = s_lpuartBase[instance];
    const lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    //1.等待发送缓冲为空
    while(!(base->STR & USART_STR_TFEIF));
    while(!(base->STR & USART_STR_TXEIF));

    //2.注销创建的同步信号
   // (void)OSIF_SemaDestroy(&lpuartState->rxComplete);
   // (void)OSIF_SemaDestroy(&lpuartState->txComplete);

	//3.关闭对应的中断
    INT_Interrupt_Enable(s_lpuartRxTxIrqId[instance], FALSE);

    //4.清空状态机
    s_lpuartStatePtr[instance] = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_InstallRxCallback
 * Description   : Install receive data callback function.
 *
 * Implements    : LPUART_DRV_InstallRxCallback_Activity
 *END**************************************************************************/
uart_callback_t LPUART_DRV_InstallRxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    uart_callback_t currentCallback = lpuartState->rxCallback;
    lpuartState->rxCallback = function;
    lpuartState->rxCallbackParam = callbackParam;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_InstallTxCallback
 * Description   : Install transmit data callback function, pass in NULL pointer
 * as callback will uninstall.
 *
 * Implements    : LPUART_DRV_InstallTxCallback_Activity
 *END**************************************************************************/
uart_callback_t LPUART_DRV_InstallTxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    uart_callback_t currentCallback = lpuartState->txCallback;
    lpuartState->txCallback = function;
    lpuartState->txCallbackParam = callbackParam;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_SendDataBlocking
 * Description   : This function sends data out through the LPUART module using
 * blocking method. The function does not return until the transmit is complete.
 *
 * Implements    : LPUART_DRV_SendDataBlocking_Activity
 *END**************************************************************************/
status_t LPUART_DRV_SendDataBlocking(uint32_t instance,
                                     const uint8_t * txBuff,
                                     uint32_t txSize,
                                     uint32_t timeout)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(txBuff != NULL);

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    status_t retVal = STATUS_SUCCESS;
    status_t syncStatus;

    /* Indicates this is a blocking transaction. */
    lpuartState->isTxBlocking = true;

   // DEV_ASSERT((lpuartState->transferType == LPUART_USING_INTERRUPTS) ||
    //           (lpuartState->transferType == LPUART_USING_DMA));

    if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = LPUART_DRV_StartSendDataUsingInt(instance, txBuff, txSize);
    }
    else if (lpuartState->transferType == LPUART_USING_DMA)
    {
        /* Start the transmission process using DMA */
        retVal = LPUART_DRV_StartSendDataUsingDma(instance, txBuff, txSize);
    }

    if (retVal == STATUS_SUCCESS)
    {
        /* Wait until the transmit is complete. */
      //  syncStatus = OSIF_SemaWait(&lpuartState->txComplete, timeout);

        /* Finish the transmission if timeout expired */
        if (syncStatus == STATUS_TIMEOUT)
        {
            lpuartState->isTxBlocking = false;
            lpuartState->transmitStatus = STATUS_TIMEOUT;

            if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
            {
                LPUART_DRV_CompleteSendDataUsingInt(instance);
            }
            else if (lpuartState->transferType == LPUART_USING_DMA)
            {
                LPUART_DRV_StopTxDma(instance);
            }
        }
    }

    return lpuartState->transmitStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_SendData
 * Description   : This function sends data out through the LPUART module using
 * non-blocking method. The function will return immediately after calling this
 * function.
 *
 * Implements    : LPUART_DRV_SendData_Activity
 *END**************************************************************************/
status_t LPUART_DRV_SendData(uint32_t instance,
                             const uint8_t * txBuff,
                             uint32_t txSize)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(txBuff != NULL);

    status_t retVal = STATUS_SUCCESS;
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    lpuartState->isTxBlocking = false;

    //DEV_ASSERT((lpuartState->transferType == LPUART_USING_INTERRUPTS) ||
    //           (lpuartState->transferType == LPUART_USING_DMA));

    if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
    {
        //中断方式开始发送
        retVal = LPUART_DRV_StartSendDataUsingInt(instance, txBuff, txSize);
    }
    else if (lpuartState->transferType == LPUART_USING_DMA)
    {
        //DMA方式开始发送
        retVal = LPUART_DRV_StartSendDataUsingDma(instance, txBuff, txSize);
    }
    else
    {
    	//查询方式开始发送
    	retVal = LPUART_DRV_StartSendDataUsingPolling(instance, txBuff, txSize);
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveDataBlocking
 * Description   : This function receives data from LPUART module using blocking
 * method, the function does not return until the receive is complete.
 *
 * Implements    : LPUART_DRV_ReceiveDataBlocking_Activity
 *END**************************************************************************/
status_t LPUART_DRV_ReceiveDataBlocking(uint32_t instance,
                                        uint8_t * rxBuff,
                                        uint32_t rxSize,
                                        uint32_t timeout)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(rxBuff != NULL);

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    status_t retVal = STATUS_SUCCESS;
    status_t syncStatus;

    /* Indicates this is a blocking transaction. */
    lpuartState->isRxBlocking = true;

    //DEV_ASSERT((lpuartState->transferType == LPUART_USING_INTERRUPTS) ||
    //           (lpuartState->transferType == LPUART_USING_DMA));

    if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
    {
         /* Start the reception process using interrupts */
         retVal = LPUART_DRV_StartReceiveDataUsingInt(instance, rxBuff, rxSize);
    }
    else if (lpuartState->transferType == LPUART_USING_DMA)
    {
        /* Start the reception process using DMA */
        retVal = LPUART_DRV_StartReceiveDataUsingDma(instance, rxBuff, rxSize);
    }

    if (retVal == STATUS_SUCCESS)
    {
        /* Wait until the receive is complete. */
      //  syncStatus = OSIF_SemaWait(&lpuartState->rxComplete, timeout);

        /* Finish the reception if timeout expired */
        if (syncStatus == STATUS_TIMEOUT)
        {
            lpuartState->isRxBlocking = false;
            lpuartState->receiveStatus = STATUS_TIMEOUT;

            if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
            {
                LPUART_DRV_CompleteReceiveDataUsingInt(instance);
            }
            else if (lpuartState->transferType == LPUART_USING_DMA)
            {
                LPUART_DRV_StopRxDma(instance);
            }
        }
    }

    return lpuartState->receiveStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveDataPolling
 * Description   : Receive multiple bytes of data using polling method.
 *
 * Implements    : LPUART_DRV_ReceiveDataPolling_Activity
 *END**************************************************************************/
status_t LPUART_DRV_ReceiveDataPolling(uint32_t instance,
                                       uint8_t *rxBuff,
                                       uint32_t rxSize)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveOneData
 * Description   : Receive multiple bytes of data using polling method.
 *
 * Implements    : LPUART_DRV_ReceiveDataPolling_Activity
 *END**************************************************************************/
status_t LPUART_DRV_ReceiveOneData(uint32_t instance,
                                       uint8_t *rxBuff)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
	//DEV_ASSERT(rxBuff != NULL);

    LPUART_Type * base = s_lpuartBase[instance];

	*rxBuff = USART_ReceiveData(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveData
 * Description   : This function receives data from LPUART module using
 * non-blocking method.  This function returns immediately after initiating the
 * receive function. The application has to get the receive status to see when
 * the receive is complete. In other words, after calling non-blocking get
 * function, the application must get the receive status to check if receive
 * is completed or not.
 *
 * Implements    : LPUART_DRV_ReceiveData_Activity
 *END**************************************************************************/
status_t LPUART_DRV_ReceiveData(uint32_t instance,
                                uint8_t * rxBuff,
                                uint32_t rxSize)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(rxBuff != NULL);

    status_t retVal = STATUS_SUCCESS;
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    lpuartState->isRxBlocking = false;

    //DEV_ASSERT((lpuartState->transferType == LPUART_USING_INTERRUPTS) ||
      //         (lpuartState->transferType == LPUART_USING_DMA));

    if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
    {
        /* Start the reception process using interrupts */
        retVal = LPUART_DRV_StartReceiveDataUsingInt(instance, rxBuff, rxSize);
    }
    else if (lpuartState->transferType == LPUART_USING_DMA)
    {
        /* Start the reception process using DMA */
        retVal = LPUART_DRV_StartReceiveDataUsingDma(instance, rxBuff, rxSize);
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_IRQHandler
 * Description   : Interrupt handler for LPUART.
 * This handler uses the buffers stored in the lpuart_state_t structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LPUART_DRV_IRQHandler(uint32_t instance)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = s_lpuartBase[instance];

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    //未有实际数据要发送时不做处理
    if (!lpuartState->isTxBusy)
    {
        //if (!lpuartState->isRxBusy)//未有实际数据要接收时不做处理的这种情况后续完善
        {
            return;
        }
    }

    if (USART_Get_Transmitter_Empty_Flag(base))
    {
    	/* Clear idle interrupt flag */
        //USART_Clear_Transmit_BUFR_INT_Flag(base);
        /* Check if there are any more bytes to send */
        if (lpuartState->txSize > 0U)
        {
        	LPUART_DRV_TxEmptyIrqHandler(instance);
        }

        if (lpuartState->txSize == 0U)
		{
        	LPUART_DRV_TxCompleteIrqHandler(instance);
		}
    }

	if(USART_Get_Receive_BUFR_Ready_Flag(base))
	{
		//ReceiveData = USART_ReceiveData(USART0_SFR);
		//BPMDrv_RecvProcess(ReceiveData);
		LPUART_DRV_RxIrqHandler(instance);
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_RxIrqHandler
 * Description   : Rx Interrupt handler for LPUART.
 * This function treats the rx full interrupt.
 *
 *END**************************************************************************/
static void LPUART_DRV_RxIrqHandler(uint32_t instance)
{
	lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

	/* Get data and put in receive buffer  */
	LPUART_DRV_GetData(instance);

	/* Invoke callback if there is one */
	if (lpuartState->rxCallback != NULL)
	{
		lpuartState->rxCallback(lpuartState, UART_EVENT_END_TRANSFER, lpuartState->rxCallbackParam);
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_TxEmptyIrqHandler
 * Description   : Tx Empty Interrupt handler for LPUART.
 * This function treats the tx empty interrupt.
 *
 *END**************************************************************************/
static void LPUART_DRV_TxEmptyIrqHandler(uint32_t instance)
{
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];

    /* Check if there are any more bytes to send */
    if (lpuartState->txSize > 0U)
    {
        /* Transmit the data */
        LPUART_DRV_PutData(instance);

        /* Update the internal state */
        if (lpuartState->bitCountPerChar == LPUART_8_BITS_PER_CHAR)
        {
            ++lpuartState->txBuff;
            --lpuartState->txSize;
        }
        else
        {
        	;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_TxCompleteIrqHandler
 * Description   : Tx Complete Interrupt handler for LPUART.
 * This function treats the tx complete interrupt.
 *
 *END**************************************************************************/
static void LPUART_DRV_TxCompleteIrqHandler(uint32_t instance)
{
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    if (lpuartState->txSize == 0U)//调用这个接口之前已经判断过,这里可以不用再判断,目前先保留
    {
        if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
        {
            /* Complete the interrupt based transfer */
            LPUART_DRV_CompleteSendDataUsingInt(instance);
        }
        else if (lpuartState->transferType == LPUART_USING_DMA)
        {
            /* Complete the DMA based transfer */
            LPUART_DRV_StopTxDma(instance);
        }
        /* Invoke callback if there is one */
        if (lpuartState->txCallback != NULL)
        {
            lpuartState->txCallback(lpuartState, UART_EVENT_END_TRANSFER, lpuartState->txCallbackParam);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ErrIrqHandler
 * Description   : Error Interrupt handler for LPUART.
 * This function treats the error interrupts.
 *
 *END**************************************************************************/
static void LPUART_DRV_ErrIrqHandler(uint32_t instance)
{
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];
#if 0
    /* Handle receive overrun interrupt */
    if (LPUART_GetStatusFlag(base, LPUART_RX_OVERRUN))
    {
        /* Update the internal status */
        lpuartState->receiveStatus = STATUS_UART_RX_OVERRUN;
        if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
        {
            /* Complete the transfer (disable rx logic) */
            LPUART_DRV_CompleteReceiveDataUsingInt(instance);
        }
#if FEATURE_LPUART_HAS_DMA_ENABLE
        else
        {
            /* Complete the transfer (stop DMA channel) */
            LPUART_DRV_StopRxDma(instance);
        }
#endif
        /* Invoke callback if there is one */
        if (lpuartState->rxCallback != NULL)
        {
            /***
             * [2019-07-17]ancle:
             *  浼樺寲 >> 澧炲姞骞惰皟鏁翠负鎸囧畾閿欒浜嬩欢瀹氫箟;
             */
            lpuartState->rxCallback(lpuartState, UART_EVENT_RX_OVERRUN, lpuartState->rxCallbackParam);
//            lpuartState->rxCallback(lpuartState, UART_EVENT_ERROR, lpuartState->rxCallbackParam);
        }

        /* Clear the flags */
        LPUART_DRV_ClearErrorFlags(base);
    }
    /* Handle framing error interrupt */
    else if (LPUART_GetStatusFlag(base, LPUART_FRAME_ERR))
    {
        /* Update the internal status */
        lpuartState->receiveStatus = STATUS_UART_FRAMING_ERROR;
        if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
        {
            /* Complete the transfer (disable rx logic) */
            LPUART_DRV_CompleteReceiveDataUsingInt(instance);
        }
#if FEATURE_LPUART_HAS_DMA_ENABLE
        else
        {
            /* Complete the transfer (stop DMA channel) */
            LPUART_DRV_StopRxDma(instance);
        }
#endif
        /* Invoke callback if there is one */
        if (lpuartState->rxCallback != NULL)
        {
            /***
             * [2019-07-17]ancle:
             *  浼樺寲 >> 澧炲姞骞惰皟鏁翠负鎸囧畾閿欒浜嬩欢瀹氫箟;
             */
            lpuartState->rxCallback(lpuartState, UART_EVENT_FRAME_ERR, lpuartState->rxCallbackParam);
//            lpuartState->rxCallback(lpuartState, UART_EVENT_ERROR, lpuartState->rxCallbackParam);
        }

        /* Clear the flags */
        LPUART_DRV_ClearErrorFlags(base);
    }
    /* Handle parity error interrupt */
    else if (LPUART_GetStatusFlag(base, LPUART_PARITY_ERR))
    {
        /* Update the internal status */
        lpuartState->receiveStatus = STATUS_UART_PARITY_ERROR;
        if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
        {
            /* Complete the transfer (disable rx logic) */
            LPUART_DRV_CompleteReceiveDataUsingInt(instance);
        }
#if FEATURE_LPUART_HAS_DMA_ENABLE
        else
        {
            /* Complete the transfer (stop DMA channel) */
            LPUART_DRV_StopRxDma(instance);
        }
#endif
        /* Invoke callback if there is one */
        if (lpuartState->rxCallback != NULL)
        {
            /***
             * [2019-07-17]ancle:
             *  浼樺寲 >> 澧炲姞骞惰皟鏁翠负鎸囧畾閿欒浜嬩欢瀹氫箟;
             */
            lpuartState->rxCallback(lpuartState, UART_EVENT_PARITY_ERR, lpuartState->rxCallbackParam);
//            lpuartState->rxCallback(lpuartState, UART_EVENT_ERROR, lpuartState->rxCallbackParam);
        }

        /* Clear the flags */
        LPUART_DRV_ClearErrorFlags(base);
    }
    /* Handle noise error interrupt */
    else if (LPUART_GetStatusFlag(base, LPUART_NOISE_DETECT))
    {
        /* Update the internal status */
        lpuartState->receiveStatus = STATUS_UART_NOISE_ERROR;
        if (lpuartState->transferType == LPUART_USING_INTERRUPTS)
        {
            /* Complete transfer (disable rx logic) */
            LPUART_DRV_CompleteReceiveDataUsingInt(instance);
        }
#if FEATURE_LPUART_HAS_DMA_ENABLE
        else
        {
            /* Complete the transfer (stop DMA channel) */
            LPUART_DRV_StopRxDma(instance);
        }
#endif
        /* Invoke callback if there is one */
        if (lpuartState->rxCallback != NULL)
        {
            /***
             * [2019-07-17]ancle:
             *  浼樺寲 >> 澧炲姞骞惰皟鏁翠负鎸囧畾閿欒浜嬩欢瀹氫箟;
             */
            lpuartState->rxCallback(lpuartState, UART_EVENT_NOISE_DETECT, lpuartState->rxCallbackParam);
//            lpuartState->rxCallback(lpuartState, UART_EVENT_ERROR, lpuartState->rxCallbackParam);
        }

        /* Clear the flags */
        LPUART_DRV_ClearErrorFlags(base);
    }
    else
    {
        /* Clear all the error/interrupt flags */
        //base->STAT = FEATURE_LPUART_STAT_REG_FLAGS_MASK;
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartSendDataUsingInt
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LPUART_DRV_StartSendDataUsingInt(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
   // DEV_ASSERT(txBuff != NULL);

    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (lpuartState->isTxBusy)
    {
        return STATUS_BUSY;
    }

    /* initialize the module driver state structure */
    lpuartState->txBuff = txBuff;
    lpuartState->txSize = txSize;
    lpuartState->isTxBusy = true;
    lpuartState->transmitStatus = STATUS_BUSY;

    /* Enable tx empty interrupt */
    USART_TXE_INT_Enable(base, TRUE);

    return STATUS_SUCCESS;
}

static status_t LPUART_DRV_StartSendDataUsingPolling(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize)
{
	//DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
	//DEV_ASSERT(txBuff != NULL);

	LPUART_Type * base = s_lpuartBase[instance];
	lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

	//发送之前确认状态机状态,此状态理论上是发送和发送完成一一对应.
	if (lpuartState->isTxBusy)
	{
		return STATUS_BUSY;
	}

	lpuartState->transmitStatus = STATUS_BUSY;

	//查询发送数据,直到数据发送完成
	while (txSize > 0U)
	{
		while (!USART_Get_Transmitter_Empty_Flag(base));

		lpuartState->txBuff = txBuff;
		LPUART_DRV_PutData(instance);

		if (lpuartState->bitCountPerChar == LPUART_8_BITS_PER_CHAR)
		{
			++txBuff;
			--txSize;
		}
		else
		{
			;//从实际项目看,目前驱动只需要支持8个数据位的传输即可.暂时不需要实现完整的UART的驱动.
		}
	}
	//在数据发送结束后,改变状态机的状态
	lpuartState->isTxBusy = false;
	lpuartState->transmitStatus = STATUS_SUCCESS;

	//在数据发送完后,回调通知APP处理发送完成
	if (lpuartState->txCallback != NULL)
	{
		lpuartState->txCallback(lpuartState, UART_EVENT_END_TRANSFER, lpuartState->txCallbackParam);
	}

	return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartSendDataUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LPUART_DRV_StartSendDataUsingDma(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(txBuff != NULL);

    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (lpuartState->isTxBusy)
    {
        return STATUS_BUSY;
    }

    /* Update state structure */
    lpuartState->txBuff = txBuff;
    lpuartState->txSize = 0U;
    lpuartState->isTxBusy = true;
    lpuartState->transmitStatus = STATUS_BUSY;

    /* Configure the transfer control descriptor for the previously allocated channel */
    EDMA_DRV_Transmit(lpuartState->txDMAChannel, (uint32_t)lpuartState->txBuff, txSize);

    /* Call driver function to end the transmission when the DMA transfer is done */
    (void)EDMA_DRV_InstallCallback(lpuartState->txDMAChannel,
                                   (edma_callback_t)(LPUART_DRV_TxDmaCallback),
                                   (void*)(instance));

    /* Start the DMA channel */
    (void)EDMA_DRV_StartChannel(lpuartState->txDMAChannel);

    /* Enable the LPUART transmitter */
    USART_Transmit_Data_Enable(base,TRUE);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_CompleteSendDataUsingInt
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_CompleteSendDataUsingInt(uint32_t instance)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    if (lpuartState->transmitStatus == STATUS_BUSY)
    {
        /* If the transfer is completed, update the transmit status */
        lpuartState->transmitStatus = STATUS_SUCCESS;
    }

    //关闭发送中断
    USART_TXE_INT_Enable(base, FALSE);

    /* Update the internal busy flag */
    lpuartState->isTxBusy = false;

    /* Signal the synchronous completion object. */
    if (lpuartState->isTxBlocking)
    {
      //  (void)OSIF_SemaPost(&lpuartState->txComplete);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_TxDmaCallback
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_TxDmaCallback(void * parameter, edma_chn_status_t status)
{
    uint32_t instance = ((uint32_t)parameter);
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];

    /* Check if the DMA transfer completed with errors */
    if (status == EDMA_CHN_ERROR)
    {
        //更新状态机
        lpuartState->transmitStatus = STATUS_ERROR;

        //回调通知APP错误处理
        if (lpuartState->txCallback != NULL)
        {
            lpuartState->txCallback(lpuartState, UART_EVENT_ERROR, lpuartState->txCallbackParam);
        }
    }
    else
    {
    	//数据通过DMA方式已经缓存到UART的BUFF
    	lpuartState->txSize = 0;

    	//使能UART的发送机为空中断,等待数据发送完成
        USART_TXE_INT_Enable(base, TRUE);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartReceiveDataUsingInt
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LPUART_DRV_StartReceiveDataUsingInt(uint32_t instance,
                                                    uint8_t * rxBuff,
                                                    uint32_t rxSize)
{
   // DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    //DEV_ASSERT(rxBuff != NULL);

    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];

    /* Check it's not busy receiving data from a previous function call */
    if (lpuartState->isRxBusy)
    {
        return STATUS_BUSY;
    }

    /* Check the validity of the parameters */
   // DEV_ASSERT(rxSize > 0U);
   // DEV_ASSERT((lpuartState->bitCountPerChar == LPUART_8_BITS_PER_CHAR) ||
    //           ((rxSize & 1U) == 0U));

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    lpuartState->isRxBusy = true;
    lpuartState->rxBuff = rxBuff;
    lpuartState->rxSize = rxSize;
    lpuartState->receiveStatus = STATUS_BUSY;

    /* Enable the receiver */
    //LPUART_SetReceiverCmd(base, true);

    /* Enable error interrupts */
    //LPUART_SetErrorInterrupts(base, true);

    /* Enable receive data full interrupt */
    //LPUART_SetIntMode(base, LPUART_INT_RX_DATA_REG_FULL, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartReceiveDataUsingDma
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LPUART_DRV_StartReceiveDataUsingDma(uint32_t instance,
                                                    uint8_t * rxBuff,
                                                    uint32_t rxSize)
{
#if 0
    DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);
    DEV_ASSERT(rxBuff != NULL);

    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (lpuartState->isRxBusy)
    {
        return STATUS_BUSY;
    }

    DEV_ASSERT(rxSize > 0U);

    /* Configure the transfer control descriptor for the previously allocated channel */
    (void)EDMA_DRV_ConfigMultiBlockTransfer(lpuartState->rxDMAChannel, EDMA_TRANSFER_PERIPH2MEM,
                                            (uint32_t)(&(base->DATA)), (uint32_t)rxBuff, EDMA_TRANSFER_SIZE_1B,
                                            1U, rxSize, true);

    /* Call driver function to end the reception when the DMA transfer is done */
    (void)EDMA_DRV_InstallCallback(lpuartState->rxDMAChannel,
                                   (edma_callback_t)(LPUART_DRV_RxDmaCallback),
                                   (void*)(instance));

    /* Start the DMA channel */
    (void)EDMA_DRV_StartChannel(lpuartState->rxDMAChannel);

    /* Update the state structure */
    lpuartState->rxBuff = rxBuff;
    lpuartState->rxSize = 0U;
    lpuartState->isRxBusy = true;
    lpuartState->receiveStatus = STATUS_BUSY;

    /* Enable the receiver */
    LPUART_SetReceiverCmd(base, true);

    /* Enable error interrupts */
    LPUART_SetErrorInterrupts(base, true);

    /* Enable rx DMA requests for the current instance */
    LPUART_SetRxDmaCmd(base, true);
#endif
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_CompleteReceiveDataUsingInt
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_CompleteReceiveDataUsingInt(uint32_t instance)
{
    //DEV_ASSERT(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Read dummy to clear RDRF flag */
    USART_ReceiveData(base);

    /* Signal the synchronous completion object. */
    if (lpuartState->isRxBlocking)
    {
      //  (void)OSIF_SemaPost(&lpuartState->rxComplete);
        lpuartState->isRxBlocking = false;
    }

    /* Update the information of the module driver state */
    lpuartState->isRxBusy = false;
    if (lpuartState->receiveStatus == STATUS_BUSY)
    {
        lpuartState->receiveStatus = STATUS_SUCCESS;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_RxDmaCallback
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_RxDmaCallback(void * parameter, edma_chn_status_t status)
{
    uint32_t instance = ((uint32_t)parameter);
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];

    if (status == EDMA_CHN_ERROR)
    {
        /* Update the status */
        lpuartState->receiveStatus = STATUS_ERROR;

        /* Notify the application that an error occurred */
        if (lpuartState->rxCallback != NULL)
        {
            lpuartState->rxCallback(lpuartState, UART_EVENT_ERROR, lpuartState->rxCallbackParam);
        }
    }

    /* Return if an error occurred; error cases are treated by the interrupt handler */
    if (lpuartState->receiveStatus != STATUS_BUSY)
    {
        return;
    }

    /* Invoke callback if there is one */
    if (lpuartState->rxCallback != NULL)
    {
        /* Allow the user to provide a new buffer inside the callback, to continue the reception */
        lpuartState->rxCallback(lpuartState, UART_EVENT_RX_FULL, lpuartState->rxCallbackParam);
    }

    /* If the callback has updated the rx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if (lpuartState->rxSize > 0U)
    {
        /* Now that this rx is set up, clear remaining bytes count */
        lpuartState->rxSize = 0U;

        /* Re-start the channel */
        (void)EDMA_DRV_StartChannel(lpuartState->rxDMAChannel);
    }
    else
    {
        /* Invoke the callback to notify the end of the transfer */
        if (lpuartState->rxCallback != NULL)
        {
            lpuartState->rxCallback(lpuartState, UART_EVENT_END_TRANSFER, lpuartState->rxCallbackParam);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_PutData
 * Description   : Write data to the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_PutData(uint32_t instance)
{
    const lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];
    uint16_t data;
    const uint8_t *txBuff = lpuartState->txBuff;

    if (lpuartState->bitCountPerChar == LPUART_8_BITS_PER_CHAR)
    {
        /* Transmit the data */
        USART_SendData(base, *txBuff);
    }
    else
    {
    	;//暂时不考虑其他数据位的发送
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_GetData
 * Description   : Read data from the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_GetData(uint32_t instance)
{
    const lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];
    LPUART_Type * base = s_lpuartBase[instance];

    uint8_t *rxBuff = lpuartState->rxBuff;

    if (lpuartState->bitCountPerChar == LPUART_8_BITS_PER_CHAR)
    {
        /* Receive the data */
    	*rxBuff = USART_ReceiveData(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StopTxDma
 * Description   : Finish up a DMA transmission by disabling the DMA requests,
 * transmission complete interrupt and tx logic. This function also resets the
 * internal driver state (busy flag/tx semaphore).
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_StopTxDma(uint32_t instance)
{
    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    //关闭发送中断
    USART_TXE_INT_Enable(base, FALSE);

    /* Signal the synchronous completion object. */
    if (lpuartState->isTxBlocking)
    {
      //  (void)OSIF_SemaPost(&lpuartState->txComplete);
    }

    if (lpuartState->transmitStatus == STATUS_BUSY)
    {
        /* If the transfer is completed, update the transmit status */
        lpuartState->transmitStatus = STATUS_SUCCESS;
    }

    /* Update the internal busy flag */
    lpuartState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StopRxDma
 * Description   : Finish up a DMA reception by disabling the DMA requests,
 * error interrupts and rx logic. This function also resets the internal driver
 * state (busy flag/rx semaphore).
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_StopRxDma(uint32_t instance)
{
    LPUART_Type * base = s_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)s_lpuartStatePtr[instance];

    /* Read dummy to clear RDRF flag */
    USART_ReceiveData(base);

    /* Signal the synchronous completion object. */
    if (lpuartState->isRxBlocking)
    {
      //  (void)OSIF_SemaPost(&lpuartState->rxComplete);
        lpuartState->isRxBlocking = false;
    }

    /* Update the internal driver status */
    if (lpuartState->receiveStatus == STATUS_BUSY)
    {
        lpuartState->receiveStatus = STATUS_SUCCESS;
    }

    /* Update the information of the module driver state */
    lpuartState->isRxBusy = false;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
