/*******************************************************************************
 *  $File Name$       : flexcan_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "flexcan_driver.h"
#include "devassert.h"
#include "status.h"
#include "kf32a156_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Table of base addresses for CAN instances. */
CAN_Type  const g_flexcanBase[CAN_INSTANCE_COUNT] = CAN_BASE_PTRS;

/* Pointer to runtime state structure.*/
static flexcan_state_t * g_flexcanStatePtr[CAN_INSTANCE_COUNT] = { NULL };

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static status_t FLEXCAN_StartSendData(
                    uint8_t instance,
                    uint8_t mb_idx,
                    const Canfd_MailboxHeaderType *tx_info,
                    uint32_t msg_id,
                    const uint8_t *mb_data,
                    bool isBlocking
                    );
static status_t FLEXCAN_StartRxMessageBufferData(
                    uint8_t instance,
                    uint8_t mb_idx,
                    Canfd_MailboxHeaderType *data,
                    bool isBlocking
                    );
static void FLEXCAN_CompleteTransfer(uint8_t instance, uint32_t mb_idx);

static void FLEXCAN_IRQHandlerRxMB(uint8_t instance, uint32_t mb_idx);
static void FLEXCAN_EnableIRQs(uint8_t instance);
static uint32_t FLEXCAN_DRV_GetMaxMbNum(const CAN_Type base);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_EnableIRQs
 * Description   : This function enable FLEXCAN instance Interrupts
 *
 *END**************************************************************************/
static void FLEXCAN_EnableIRQs(uint8_t instance)
{
	//
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Init
 * Description   : Initialize FlexCAN driver.
 * This function will select a source clock, reset FlexCAN module, set maximum
 * number of message buffers, initialize all message buffers as inactive, enable
 * RX FIFO if needed, mask all mask bits, disable all MB interrupts, enable
 * FlexCAN normal mode, and enable all the error interrupts if needed.
 *
 * Implements    : FLEXCAN_DRV_Init_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_Init(
   uint8_t instance,
   flexcan_state_t *state,
   const Can_ControllerConfigType *data)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(state != NULL);
    DEV_ASSERT(g_flexcanStatePtr[instance] == NULL);

    const CAN_Type base = g_flexcanBase[instance];

    /* DeInitialize FLEXCAN device */
    Can_m_FdControllerDeInit(base);

    /* Initialize FLEXCAN device */
    Can_m_FdControllerInit(base, data, Initindex_0);

    /* Enable FlexCAN interrupts.*/
    FLEXCAN_EnableIRQs(instance);

    for (uint32_t i = 0; i < FEATURE_CAN_MAX_MB_NUM; i++)
    {
#if 0//如需block传输，且有freertos时才需要创建信号，暂时不需要
        osifStat = OSIF_SemaCreate(&state->mbs[i].mbSema, 0U);
        if (osifStat != STATUS_SUCCESS)
        {
            for (uint32_t j = 0; j < i; j++)
            {
                (void)OSIF_SemaDestroy(&state->mbs[j].mbSema);
            }
            return STATUS_ERROR;
        }
#endif
       // state->mbs[i].isBlocking = false;
        state->mbs[i].mb_message = NULL;
        state->mbs[i].state = FLEXCAN_MB_IDLE;
    }

    /* Clear Callbacks in case of autovariables garbage */
    state->callback = NULL;
    state->callbackParam = NULL;
    state->error_callback = NULL;
    state->errorCallbackParam = NULL;

    /* Save runtime structure pointers so irq handler can point to the correct state structure */
    g_flexcanStatePtr[instance] = state;

    return (STATUS_SUCCESS);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ConfigTxMb
 * Description   : Configure a Tx message buffer.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will set up the message buffer fields,
 * configure the message buffer code for Tx buffer as INACTIVE, and enable the
 * Message Buffer interrupt.
 *
 * Implements    : FLEXCAN_DRV_ConfigTxMb_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_ConfigTxMb(

    uint8_t instance,
    const uint8_t mb_idx,
    Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(tx_info != NULL);

	status_t state = STATUS_ERROR;

    const CAN_Type base = g_flexcanBase[instance];

#if 0//已经配置了发送邮箱，因此不需要在这里查询空闲邮箱发送
	for(uint8_t transmitbox = mb_idx; transmitbox< 51; transmitbox++)
	{
		if(Can_m_FdMailBox_Write(base, transmitbox, tx_info) != CAN_BUSY_TRANSMIT_MAILBOX)
		{
			state = STATUS_SUCCESS;
			break;
		}
	}
#else
	state = Can_m_FdMailBox_Write(base, mb_idx, tx_info);   
//	if(Can_m_FdMailBox_Write(base, mb_idx, tx_info) != CAN_BUSY_TRANSMIT_MAILBOX)
//	{
//			state = STATUS_SUCCESS;
//	}
//	else
//	{
//		state = STATUS_ERROR;
//	}
#endif

	return state;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SendBlocking
 * Description   : This function sends a CAN frame using a configured message
 * buffer. The function blocks until either the frame was sent, or the specified
 * timeout expired.
 *
 * Implements    : FLEXCAN_DRV_SendBlocking_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    const Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data,
    uint32_t timeout_ms)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(tx_info != NULL);

    status_t status = STATUS_SUCCESS;
    status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type base  = g_flexcanBase[instance];

    result = FLEXCAN_StartSendData(instance, mb_idx, tx_info, msg_id, mb_data, true);

    if (result == STATUS_SUCCESS)
    {
       // status = OSIF_SemaWait(&state->mbs[mb_idx].mbSema, timeout_ms);

        if (status == STATUS_TIMEOUT)
        {
        	if (state->mbs[mb_idx].state != FLEXCAN_MB_IDLE)
        	{
				state->mbs[mb_idx].state = FLEXCAN_MB_IDLE;
			}
        }
    }
    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Send
 * Description   : This function sends a CAN frame using a configured message
 * buffer. The function returns immediately. If a callback is installed, it will
 * be invoked after the frame was sent.
 *
 * Implements    : FLEXCAN_DRV_Send_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint8_t mb_idx,
    const Canfd_MailboxHeaderType *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data)
{
	uint32_t CAN_delay_count = 0;
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(tx_info != NULL);

    status_t result;
    CAN_Type base = g_flexcanBase[instance];

    result = FLEXCAN_StartSendData(instance, mb_idx, tx_info, msg_id, mb_data, false);
    if(result != STATUS_SUCCESS)
    {
    	result= STATUS_SUCCESS;
    }


    Can_m_FdTransmit(base);//单次发送,使能发送中断后中断里确认发送完成
//    ret=Can_m_FdMailBox_Write(CANfd6, Mailbox_0, &Canfd_Sdu.Can_MailboxHeader[0]);

#if 0
       CAN_delay_count =0x4ff;
       while( ( ( CANFD6_SFR->CTLR0&CANFD_CTLR0_TXSTA)== 0)&& (CAN_delay_count--));
       CAN_delay_count =0xfffff;
       while( ( (CANFD6_SFR->CTLR0 &CANFD_CTLR0_TCSTA)== 0)&& (CAN_delay_count--))
       {
          Can_m_FdTransmit(CANfd6);
       }

       if(CAN_delay_count <= 0)
       {
    	   CAN_delay_count = 0;
       }
#else
//		CAN_delay_count = 0x0f;
//		while(CAN_delay_count--)
//		{
//			Can_m_FdTransmit(base);
//		}
#endif

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ConfigMb
 * Description   : Configure a Rx message buffer.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will set up the message buffer fields,
 * configure the message buffer code for Rx message buffer as NOT_USED, enable
 * the Message Buffer interrupt, configure the message buffer code for Rx
 * message buffer as INACTIVE, copy user's buffer into the message buffer data
 * area, and configure the message buffer code for Rx message buffer as EMPTY.
 *
 * Implements    : FLEXCAN_DRV_ConfigRxMb_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_ConfigRxMb(
    const uint8_t instance,
    const uint8_t mb_idx,
    Canfd_MailboxHeaderType *rx_info)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(rx_info != NULL);

    CAN_Type base = g_flexcanBase[instance];

	Can_m_FdMailBox_Write(base, mb_idx, rx_info);

    return (STATUS_SUCCESS);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ReceiveBlocking
 * Description   : This function receives a CAN frame into a configured message
 * buffer. The function blocks until either a frame was received, or the
 * specified timeout expired.
 *
 * Implements    : FLEXCAN_DRV_ReceiveBlocking_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_ReceiveBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    Canfd_MailboxHeaderType *data,
    uint32_t timeout_ms)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    status_t status = STATUS_SUCCESS;
    status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type base = g_flexcanBase[instance];

    result = FLEXCAN_StartRxMessageBufferData(instance, mb_idx, data, true);

    if(result == STATUS_SUCCESS)
    {
      //  status = OSIF_SemaWait(&state->mbs[mb_idx].mbSema, timeout_ms);

        if (status == STATUS_TIMEOUT)
        {
			result = STATUS_TIMEOUT;
        }
        /* Consider the MB state has been changed by interrupt as frame received */ 
        if (state->mbs[mb_idx].state == FLEXCAN_MB_IDLE)
        {
        	return STATUS_SUCCESS;
        }

        state->mbs[mb_idx].state = FLEXCAN_MB_IDLE;
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Receive
 * Description   : This function receives a CAN frame into a configured message
 * buffer. The function returns immediately. If a callback is installed, it will
 * be invoked after the frame was received and read into the specified buffer.
 *
 * Implements    : FLEXCAN_DRV_Receive_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_Receive(
    uint8_t instance,
    uint8_t mb_idx,
    Canfd_MailboxHeaderType *data)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    status_t result;

    result = FLEXCAN_StartRxMessageBufferData(instance, mb_idx, data, false);

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Deinit
 * Description   : Shutdown a FlexCAN module.
 * This function will disable all FlexCAN interrupts, and disable the FlexCAN.
 *
 * Implements    : FLEXCAN_DRV_Deinit_Activity
 *END**************************************************************************/
status_t FLEXCAN_DRV_Deinit(uint8_t instance)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    CAN_Type base = g_flexcanBase[instance];
    const flexcan_state_t * state = g_flexcanStatePtr[instance];
    status_t result = STATUS_SUCCESS;
    status_t osifStat;

    Can_m_FdControllerDeInit(instance);

    /* Disable FlexCAN interrupts.*/
#if 0//1

#endif


#if 0//2
    if (state != NULL)
    {
		for (uint32_t i = 0; i < FEATURE_CAN_MAX_MB_NUM; i++)
		{
			//如需block传输，且有freertos时
			osifStat = OSIF_SemaDestroy(&state->mbs[i].mbSema);
			if (osifStat != STATUS_SUCCESS)
			{
				result = STATUS_ERROR;
			}
		}
    }
#endif


#if 0//3
	/* Clear state pointer that is checked by FLEXCAN_DRV_Init */
	g_flexcanStatePtr[instance] = NULL;
#endif

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IRQHandlerRxMB
 * Description   : Process IRQHandler in case of Rx MessageBuffer selection
 * for CAN interface.
 *
 * This is not a public API as it is called whenever an interrupt and receive
 * individual MB occurs
 *END**************************************************************************/
static void FLEXCAN_IRQHandlerRxMB(uint8_t instance, uint32_t mb_idx)
{
	 CAN_Type base = g_flexcanBase[instance];
	 flexcan_state_t * state = g_flexcanStatePtr[instance];
	 status_t result = STATUS_SUCCESS;

	 /* Get RX MB field values, receive message and save it*/
	 Can_m_FdMailBox_Read(base, mb_idx, state->mbs[mb_idx].mb_message, MAIL_RECEIVE);

	 /* Complete receive data */
	 //FLEXCAN_CompleteTransfer(instance, mb_idx);
	  state->mbs[mb_idx].state = FLEXCAN_MB_IDLE;

	 /* Invoke callback */
	 if (state->callback != NULL)
	 {
		 state->callback(instance, FLEXCAN_EVENT_RX_COMPLETE, mb_idx, state);
	 }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IRQHandler
 * Description   : Interrupt handler for FLEXCAN.
 * This handler read data from MB or FIFO, and then clear the interrupt flags.
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXCAN_IRQHandler(uint8_t instance)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    CAN_Type base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Get the interrupts that are enabled and ready */
    uint32_t mb_idx = 0;
	uint8_t Rmc_count = 0;
	Can_Controller_InterruptFlagType Can_Controller_InterruptFlag;

	volatile Kf32a_Canfd_Reg *ControllerRegPtr = (Kf32a_Canfd_Reg *)Can_m_ControllersInfo[instance].BaseAddress;
	 /* Get the interrupts that are enabled and ready */
	Can_m_FdGetIntFlag(base, &Can_Controller_InterruptFlag, &Rmc_count);
	/* Clear all error interrupts */
	Can_m_FdClearIntFlag(base, &Can_Controller_InterruptFlag,Rmc_count);

	if (Can_Controller_InterruptFlag.RxIntFlag == 0x01)
	{


		for(mb_idx = D_CANFD_MAILBOX_RX_START; mb_idx <= D_CANFD_MAILBOX_RX_END; mb_idx++)//从接收邮箱配置表里查询相应的范围
		{
			if((Can_m_FdGetMailBoxState(base, mb_idx) == MAIL_RECEIVE_SUCCESS)||(Can_m_FdGetMailBoxState(base, mb_idx) == 6))
			{
				/* Check mailbox completed reception */
				FLEXCAN_IRQHandlerRxMB(instance, mb_idx);
			}
		}
	}

	if (Can_Controller_InterruptFlag.TxIntFlag == 0x01)
	{
		if(instance == 0)
		{
			for(mb_idx = D_CANFD_MAILBOX_TX_START; mb_idx <= D_CANFD_MAILBOX_TX_END; mb_idx++)//从发送邮箱配置表里查询相应的范围
			{
				//if(Can_m_FdGetMailBoxState(base, mb_idx) == MAIL_TRANSMIT_SUCCESS)
//				if(ControllerRegPtr->CANFD_CTLR0.B.TCSTA==1)
				 if (((ControllerRegPtr->CANFD_CTLR0.B.TCSTA == 0x01)) && \
				                    (ControllerRegPtr->CANFD_CTLR0.B.TXSTA == 0x00) && \
				                    ((Can_m_FdGetMailBoxState(base, mb_idx) == MAIL_UNDEFINED) || (Can_m_FdGetMailBoxState(base, mb_idx) == MAIL_TRANSMIT_SUCCESS)))
				{
					/* Complete transmit data */
					FLEXCAN_CompleteTransfer(instance, mb_idx);
				}
				else
				{
					//Can_Controller_InterruptFlag.TxIntFlag = 0x01;
				}
			}
		}
		else
		{
			for(mb_idx = D_CANFD_MAILBOX_TX_START; mb_idx <= D_CANFD_MAILBOX_TX_END; mb_idx++)//从发送邮箱配置表里查询相应的范围
			{
				if(Can_m_FdGetMailBoxState(base, mb_idx) == MAIL_TRANSMIT_SUCCESS)
				{
					/* Complete transmit data */
					FLEXCAN_CompleteTransfer(instance, mb_idx);
				}
			}
		}
	}

//	if(Can_Controller_InterruptFlag.ErrorAlarmFlag == 0x01 || Can_Controller_InterruptFlag.OverFlowFlag == 0x01
//		|| Can_Controller_InterruptFlag.BusErrorFlag || Can_Controller_InterruptFlag.ErrorNegativeFlag
//		|| Can_Controller_InterruptFlag.ArbitrateLoseFlag == 0x01)
//	{
//		//Can_Controller_InterruptFlag.ErrorAlarmFlag = 0x00;
//	}

	if(Can_Controller_InterruptFlag.BusOffFlag == 0x01)
	{
		ControllerRegPtr->CANFD_CTLR0.B.RSMOD = 0x00;
		/* Check if any error occurred */
		FLEXCAN_Error_IRQHandler(instance);
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_Error_IRQHandler
 * Description   : Error interrupt handler for FLEXCAN.
 * This handler read data from MB or FIFO, and then clear the interrupt flags.
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXCAN_Error_IRQHandler(uint8_t instance)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    CAN_Type base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Invoke callback */
    if (state->error_callback != NULL)
    {
        state->error_callback(instance, FLEXCAN_EVENT_ERROR, state);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_StartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t FLEXCAN_StartSendData(
                    uint8_t instance,
                    uint8_t mb_idx,
                    const Canfd_MailboxHeaderType *tx_info,
                    uint32_t msg_id,
                    const uint8_t *mb_data,
                    bool isBlocking
                    )
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    DEV_ASSERT(tx_info != NULL);

    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type base = g_flexcanBase[instance];

    if(mb_idx >= FLEXCAN_DRV_GetMaxMbNum(base))
    {
    	return STATUS_ERROR;      //STATUS_CAN_BUFF_OUT_OF_RANGE;
    }

    if (state->mbs[mb_idx].state != FLEXCAN_MB_IDLE)
    {
        return STATUS_BUSY;
    }

    state->mbs[mb_idx].state = FLEXCAN_MB_TX_BUSY;
   // state->mbs[mb_idx].isBlocking = isBlocking;

    return (STATUS_SUCCESS);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_StartRxMessageBufferData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t FLEXCAN_StartRxMessageBufferData(
                    uint8_t instance,
                    uint8_t mb_idx,
                    Canfd_MailboxHeaderType *data,
                    bool isBlocking
                    )
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    CAN_Type base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Check if the MB index is in range */
    if(mb_idx >= FLEXCAN_DRV_GetMaxMbNum(base))
    {
    	return STATUS_ERROR;      //STATUS_CAN_BUFF_OUT_OF_RANGE;
    }

    /* Start receiving mailbox */
    if(state->mbs[mb_idx].state != FLEXCAN_MB_IDLE)
    {
        return STATUS_BUSY;
    }
    state->mbs[mb_idx].state = FLEXCAN_MB_RX_BUSY;

    state->mbs[mb_idx].mb_message = data;
  //  state->mbs[mb_idx].isBlocking = isBlocking;

    return (STATUS_SUCCESS);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_CompleteTransfer
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXCAN_CompleteTransfer(uint8_t instance, uint32_t mb_idx)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    CAN_Type base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Update the information of the module driver state */
//    if (state->mbs[mb_idx].isBlocking)
    {
        //(void)OSIF_SemaPost(&state->mbs[mb_idx].mbSema);
    }
    state->mbs[mb_idx].state = FLEXCAN_MB_IDLE;

    /* Invoke callback */
    if (state->callback != NULL)
    {
        state->callback(instance, FLEXCAN_EVENT_TX_COMPLETE, mb_idx, state);
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_InstallEventCallback
 * Description   : Installs a callback function for the IRQ handler.
 *
 * Implements    : FLEXCAN_DRV_InstallEventCallback_Activity
 *END**************************************************************************/
void FLEXCAN_DRV_InstallEventCallback(uint8_t instance,
                                      flexcan_callback_t callback,
                                      void *callbackParam)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    flexcan_state_t * state = g_flexcanStatePtr[instance];

    state->callback = callback;
    state->callbackParam = callbackParam;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_InstallErrorCallback
 * Description   : Installs an error callback function for the IRQ handler and enables/disables
 *                 error interrupts.
 *
 * Implements    : FLEXCAN_DRV_InstallErrorCallback_Activity
 *END**************************************************************************/
void FLEXCAN_DRV_InstallErrorCallback(uint8_t instance,
                                      flexcan_error_callback_t callback,
                                      void *callbackParam)
{
    DEV_ASSERT(instance < CAN_INSTANCE_COUNT);

    flexcan_state_t * state = g_flexcanStatePtr[instance];

	state->error_callback = callback;
	state->errorCallbackParam = callbackParam;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_GetMaxMbNum
 * Description   : Computes the maximum RAM size occupied by MBs.
 *
 *END**************************************************************************/
static uint32_t FLEXCAN_DRV_GetMaxMbNum(const CAN_Type base)
{
    uint32_t ret = 0;
    static CAN_Type const flexcanBase[] = CAN_BASE_PTRS;

    static const uint32_t maxMbNum[] = FEATURE_CAN_MAX_MB_NUM_ARRAY;

    for (uint32_t i = 0; i < CAN_INSTANCE_COUNT; i++)
    {
        if (base == flexcanBase[i])
        {
            ret = maxMbNum[i];
        }
    }

    return ret;
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
