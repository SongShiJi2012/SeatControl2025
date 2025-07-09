/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @lpi2c_driver.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 1.3, Taking address of near auto variable.
 * The code is not dynamically linked. An absolute stack address is obtained
 * when taking the address of the near auto variable. A source of error in writing
 * dynamic code is that the stack segment may be different from the data segment.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, Identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, Identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, Identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, Identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, A compatible declaration shall be
 * visible when an object or function with external linkage is defined.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.9, Could define variable at block scope
 * The variables are defined in the common source file and this rule can't be
 * applied.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, Expression assigned to a narrower or different essential type.
 * The cast is required to perform a conversion between an unsigned integer and an enum type with many values.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, Impermissible cast; cannot cast from 'essentially Boolean'
 * to 'essentially unsigned'. This is required by the conversion of a bool into a bit.
 * Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum<i>'.
 * This is required by the conversion of a bitfield of a register into a enum.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, Conversion between a pointer and integer type.
 * The cast is required to initialize a pointer with an unsigned long define, representing an address.
 * This conversion is required because the converted values are the addresses used in DMA transfer.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, Cast from pointer to unsigned long, cast from unsigned long to pointer
 * and cast from unsigned int to pointer. The cast is required to perform a conversion between a pointer
 * and an unsigned long define, representing an address or vice versa. The cast is required to initialize a DMA
 * transfer. The converted value is the address of a buffer.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.8, Attempt to cast away const/volatile from a pointer or reference.
 * The cast is required to initialize a DMA transfer. The converted value is the address of a register.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 15.5, Return statement before end of function.
 * The return statement before end of function is used for simpler code
 * structure and better readability.
 */
#include "kf32a156_int.h"
#include "lpi2c_driver.h"
#include "devassert.h"
#include "system_init.h"

#define D_WAITIMER    (0x0787)    /*系统时钟120M   0x0787 1ms 最长不超过1ms*/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Table of base addresses for LPI2C instances. */
static LPI2C_Type * const g_lpi2cBase[LPI2C_INSTANCE_COUNT] = LPI2C_BASE_PTRS;

/* Pointer to runtime state structure.*/
static lpi2c_master_state_t* g_lpi2cMasterStatePtr[LPI2C_INSTANCE_COUNT] = {NULL};
static lpi2c_slave_state_t* g_lpi2cSlaveStatePtr[LPI2C_INSTANCE_COUNT] = {NULL}; /*暂时不做从机模式*/

/* Table for lpi2c IRQ numbers */
static const IRQn_Type g_lpi2cMasterIrqId[LPI2C_INSTANCE_COUNT] = LPI2C_MASTER_IRQS; /*中断后面研究*/
//static const IRQn_Type g_lpi2cSlaveIrqId[LPI2C_INSTANCE_COUNT] = LPI2C_SLAVE_IRQS;

/* PCC clock sources, for getting the input clock frequency */
//static const clock_names_t g_lpi2cClock[LPI2C_INSTANCE_COUNT] = LPI2C_PCC_CLOCKS;

/* Callback for master DMA transfer done.*/
static void LPI2C_DRV_MasterCompleteDMATransfer(void* parameter, edma_chn_status_t status);

/*! @brief Direction of a LPI2C transfer - transmit or receive. */
typedef enum
{
   LPI2C_TX_REQ = 0,    /*!< The driver will perform an I2C transmit transfer */
   LPI2C_RX_REQ = 1,    /*!< The driver will perform an I2C receive transfer */
} lpi2c_transfer_direction_t;

/*!
 * @brief DMA internal parameters structure
 *
 * This structure is used in DMA transfers. It contains different
 * variables required for setting and maintaining a DMA transfer.
 */
typedef struct
{
    /*! @cond DRIVER_INTERNAL_USE_ONLY */
    uint8_t dmaChannel;                             /* Channel number for the DMA channel */
  //  edma_transfer_type_t dmaTransferType;           /* Type for the DMA transfer */
    uint32_t i2cDataRegAddr;                        /* An i2c data register address */
    uint8_t *bufferTransfer;                        /* Buffer used for transfer */
    uint32_t transferSize;                          /* Size of the data to be transfered */
    lpi2c_transfer_direction_t transferDirection;   /* Tells if the driver will make a receive or transmit DMA transfer */
    /*! @endcond */
} lpi2c_dma_transfer_params_t;


/*******************************************************************************
 * Private Functions
 ******************************************************************************/
FunctionalState LPI2C_DRV_Generate_Start(I2C_SFRmap *I2C_Choose)
{
	uint16_t WaitTimer = D_WAITIMER;
	FunctionalState Res = FALSE;

    /* Clear interrupt flag ISIF */
    if(FAILURE == I2C_Clear_INTERRUPT_Flag(I2C_Choose))
    {
    	  return FALSE;
    }
    /* Enable I2C HW module*/
    I2C_Cmd(I2C_Choose, TRUE);
    /* Start bit */
    I2C_Generate_START(I2C_Choose, TRUE);
    /* Wait for the start signal to stabilize */
    //while (!I2C_Get_INTERRUPT_Flag(I2C_Choose));
    while ((!I2C_Get_INTERRUPT_Flag(I2C_Choose)) &&(--WaitTimer));

    if(0 != WaitTimer)
    {
    	Res = TRUE;
    }

    return Res;
}

FunctionalState LPI2C_DRV_Generate_Send(I2C_SFRmap *I2C_Choose,uint8_t Data)
{
	uint16_t WaitTimer = D_WAITIMER;

	I2C_SendData8(I2C_Choose, Data);
	/* Clear the ISIF bit of the I2C interrupt flag */
   if(FAILURE == I2C_Clear_INTERRUPT_Flag(I2C_Choose))
	{
		  return FALSE;
	}

	/* Wait for sending to complete */
	while ((!I2C_Get_INTERRUPT_Flag(I2C_Choose)) &&(--WaitTimer));
	if(0 == WaitTimer)
	{
		 return FALSE;
	}

	WaitTimer = D_WAITIMER;
	//while(I2C_Get_Ack_Fail_Flag(I2C_Choose));
	while(I2C_Get_Ack_Fail_Flag(I2C_Choose)&&(--WaitTimer)); /*如果没ACK，从机忙*/
	if(0 == WaitTimer)
	{
		 return FALSE;
	}

	return TRUE;
}

uint16_t LPI2C_DRV_Generate_Receive(I2C_SFRmap *I2C_Choose,FunctionalState Ack)
{
	uint16_t ReadData = 0;
	uint16_t WaitTimer = D_WAITIMER;

	if(TRUE == Ack)
	{
		I2C_Ack_DATA_Config(I2C_Choose, I2C_ACKDATA_ACK);
	}
	else
	{
		I2C_Ack_DATA_Config(I2C_Choose, I2C_ACKDATA_NO_ACK);
	}
	I2C_Clear_INTERRUPT_Flag(I2C_Choose);
	while ((!I2C_Get_INTERRUPT_Flag(I2C_Choose)) &&(--WaitTimer)); /*数据接收中断*/
	WaitTimer = D_WAITIMER;
	while((I2C_Get_Receive_Buff_Flag(I2C_Choose) == RESET) && (--WaitTimer));
	ReadData = I2C_ReceiveData(I2C_Choose);

	return ReadData;
}

void LPI2C_DRV_Generate_Stop(I2C_SFRmap *I2C_Choose)
{
	uint16_t WaitTimer = D_WAITIMER;

	/* Stop bit */
	I2C_Generate_STOP(I2C_Choose, TRUE);
	/* Clear the ISIF bit of the I2C interrupt flag */
	 if(FAILURE == I2C_Clear_INTERRUPT_Flag(I2C_Choose))
	{
		  return ;
	}
	/* Wait for the stop to complete */
	while ((!I2C_Get_INTERRUPT_Flag(I2C_Choose)) &&(--WaitTimer));

	/* Clear the ISIF bit of the I2C interrupt flag */
	 if(FAILURE == I2C_Clear_INTERRUPT_Flag(I2C_Choose))
	{
		  return ;
	}
	/* Clear the I2C stop flag PIF bit */
	I2C_Clear_Stop_Flag(I2C_Choose);
	/* Stop I2C module */
	I2C_Cmd(I2C_Choose, FALSE);
}




/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterCmdQueueEmpty
 * Description   : checks if there are any commands in the master software queue
 *
 *END**************************************************************************/
static inline bool LPI2C_DRV_MasterCmdQueueEmpty(const lpi2c_master_state_t * master)
{
    DEV_ASSERT(master != NULL);

    return (master->cmdQueue.writeIdx == master->cmdQueue.readIdx);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterResetQueue
 * Description   : resets the master software queue
 *
 *END**************************************************************************/
static inline void LPI2C_DRV_MasterResetQueue(lpi2c_master_state_t * master)
{
    DEV_ASSERT(master != NULL);

    master->cmdQueue.readIdx = 0U;
    master->cmdQueue.writeIdx = 0U;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterQueueCmd
 * Description   : queues a command in the hardware FIFO or in the master software queue
 *
 *END**************************************************************************/
static inline void LPI2C_DRV_MasterQueueCmd(LPI2C_Type *baseAddr,
                                            lpi2c_master_state_t * master,
                                            lpi2c_master_command_t cmd,
                                            uint8_t data)
{
	 DEV_ASSERT(master != NULL);
	 DEV_ASSERT(baseAddr != NULL);

	 uint8_t Cnt = 0;
	 FunctionalState  Res = FALSE;

#if 0
   // uint16_t txFIFOCount = LPI2C_Get_MasterTxFIFOCount(baseAddr);
   // uint16_t txFIFOSize = LPI2C_Get_MasterTxFIFOSize(baseAddr);

    /* Check if there is room in the hardware FIFO */
    if (txFIFOCount < txFIFOSize)
    {
        LPI2C_Cmd_MasterTransmit(baseAddr, cmd, data);
    }
    else
    {
        /* Hardware FIFO full, use software FIFO */
        DEV_ASSERT(master->cmdQueue.writeIdx < LPI2C_MASTER_CMD_QUEUE_SIZE);

        master->cmdQueue.cmd[master->cmdQueue.writeIdx] = cmd;
        master->cmdQueue.data[master->cmdQueue.writeIdx] = data;
        master->cmdQueue.writeIdx++;
    }
#endif

    switch(cmd)
    {
    	case  LPI2C_MASTER_COMMAND_START:
     		LPI2C_DRV_Generate_Start(baseAddr);
    		Res = LPI2C_DRV_Generate_Send(baseAddr,data);
    	break;

    	case  LPI2C_MASTER_COMMAND_TRANSMIT:
    		while (master->txSize > 0U)
			{
    			LPI2C_DRV_Generate_Send(baseAddr,master->txBuff[0U]);
				master->txBuff++;
				master->txSize--;
			}
    	break;

    	case  LPI2C_MASTER_COMMAND_RECEIVE:
    		while ((master->rxSize > 0U) )
    		{
    			if(master->rxSize != 1)
    			{
    				master->rxBuff[0U] = LPI2C_DRV_Generate_Receive(baseAddr,master->sendStop);
    			}
    			else
    			{
    				master->rxBuff[0U] = LPI2C_DRV_Generate_Receive(baseAddr,FALSE);
    			}
    			master->rxBuff++;
    			master->rxSize--;
    		}
        break;

    	case  LPI2C_MASTER_COMMAND_STOP:
    		LPI2C_DRV_Generate_Stop(baseAddr);
        break;

    	case  LPI2C_MASTER_COMMAND_START_NACK:    /*20220923 发送地址，需要重新改*/
        	LPI2C_DRV_Generate_Send(baseAddr,data);
        break;

    	default:
    	break;
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSendQueuedCmd
 * Description   : transfers commands from the master software queue to the hardware FIFO
 *
 *END**************************************************************************/
#if 0
static inline void LPI2C_DRV_MasterSendQueuedCmd(LPI2C_Type *baseAddr, lpi2c_master_state_t * master)
{
    DEV_ASSERT(master != NULL);
    DEV_ASSERT(baseAddr != NULL);

    uint16_t txFIFOCount = LPI2C_Get_MasterTxFIFOCount(baseAddr);
    uint16_t txFifoSize = LPI2C_Get_MasterTxFIFOSize(baseAddr);

    while ((!LPI2C_DRV_MasterCmdQueueEmpty(master)) && (txFIFOCount < txFifoSize))
    {
        LPI2C_Cmd_MasterTransmit(baseAddr,
                                    master->cmdQueue.cmd[master->cmdQueue.readIdx],
                                    master->cmdQueue.data[master->cmdQueue.readIdx]);
        master->cmdQueue.readIdx++;

        txFIFOCount = LPI2C_Get_MasterTxFIFOCount(baseAddr);
    }

    if (LPI2C_DRV_MasterCmdQueueEmpty(master))
    {
        /* Reset queue */
        LPI2C_DRV_MasterResetQueue(master);
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSendAddress
 * Description   : send start event and slave address
 *                 parameter receive specifies the direction of the transfer
 *
 *END**************************************************************************/
static void LPI2C_DRV_MasterSendAddress(LPI2C_Type *baseAddr,
                                        lpi2c_master_state_t * master,
                                        bool receive)
{
    uint8_t addrByte;
    lpi2c_master_command_t startCommand;

    DEV_ASSERT(master != NULL);
    DEV_ASSERT(baseAddr != NULL);

#if(LPI2C_HAS_HIGH_SPEED_MODE)
    if ((master->operatingMode == LPI2C_HIGHSPEED_MODE) && (master->highSpeedInProgress == false))
    {
        /* Initiating High-speed mode - send master code first */
        LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_START_NACK, master->masterCode);
        master->highSpeedInProgress = true;
    }

    if (master->highSpeedInProgress == true)
    {
        /* Use high-speed settings after start event in High Speed mode */
        startCommand = LPI2C_MASTER_COMMAND_START_HS;
    }
    else
#endif
    {
        /* Normal START command */
        startCommand = LPI2C_MASTER_COMMAND_START;
    }

    if (master->is10bitAddr)
    {
        /* 10-bit addressing */
        /* First address byte: 1111 0XXD, where XX are bits 10 and 9 of address, and D = 0(transmit) */
        addrByte = (uint8_t)(0xA0U + ((master->slaveAddress >> 7U) & 0x0EU) + (uint8_t)0U);
        LPI2C_DRV_MasterQueueCmd(baseAddr, master, startCommand, addrByte);
        /* Second address byte: Remaining 8 bits of address */
        addrByte = (uint8_t)(master->slaveAddress & 0xFFU);
        LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_START_NACK, addrByte);
        if (receive == true)
        {
            /* Receiving from 10-bit slave - must send repeated start and resend first address byte */
            /* First address byte: 1111 0XXD, where XX are bits 10 and 9 of address, and D = 1 (receive) */
            addrByte = (uint8_t)(0xA0U + ((master->slaveAddress >> 7U) & 0x0EU) + (uint8_t)1U);
            LPI2C_DRV_MasterQueueCmd(baseAddr, master, startCommand, addrByte);
        }
    }
    else
    {
        /* 7-bit addressing */
        /* Address byte: slave 7-bit address + D = 0(transmit) or 1 (receive) */
        addrByte = (uint8_t)((master->slaveAddress << 1U) + (uint8_t)receive);
        LPI2C_DRV_MasterQueueCmd(baseAddr, master, startCommand, addrByte);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterQueueData
 * Description   : queues transmit data in the LPI2C tx fifo until it is full
 *
 *END**************************************************************************/
static void LPI2C_DRV_MasterQueueData(LPI2C_Type *baseAddr,
                                      lpi2c_master_state_t * master)
{
    /* Don't queue any data if there are commands in the software queue */
    if (LPI2C_DRV_MasterCmdQueueEmpty(master))
    {
    	 LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_TRANSMIT,master->txBuff[0U]);

    }
    LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_STOP,master->txBuff[0U]);
    master->status = STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterReinit
 * Description   : re-initialize the I2C master
 *
 *END**************************************************************************/
static status_t LPI2C_DRV_MasterReinit(uint32_t instance, lpi2c_master_state_t * master)
{
    LPI2C_Type *baseAddr;
    lpi2c_baud_rate_params_t baudRate;

    baseAddr = g_lpi2cBase[instance];
    g_lpi2cMasterStatePtr[instance] = master;

    /* Re-initialize driver status structure */
    master->txBuff = NULL;
    master->txSize = 0;
    master->rxBuff = NULL;
    master->rxSize = 0;
    master->i2cIdle = true;

	LPI2C_DRV_MasterResetQueue(master);

	/* Initialize module */
//	LPI2C_Init(baseAddr);

	/* Set baud rate */
	baudRate.baudRate = master->baudrate;
	#if(LPI2C_HAS_HIGH_SPEED_MODE)
	    baudRate.baudRateHS = master->baudRateHS;
	#endif
	(void)LPI2C_DRV_MasterSetBaudRate(instance, master->operatingMode, baudRate);

	 /* Set slave address */
	 LPI2C_DRV_MasterSetSlaveAddr(instance, master->slaveAddress, master->is10bitAddr);

	 /* Enable LPI2C master */
	// LPI2C_Set_MasterEnable(baseAddr, true);

	 return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterHandleTransmitDataRequest
 * Description   : handle a transmit request for master
 *
 *END**************************************************************************/
static void LPI2C_DRV_MasterHandleTransmitDataRequest(LPI2C_Type *baseAddr, lpi2c_master_state_t *master)
{
#if 0
    /* More data needed for transmission */
    if (!LPI2C_DRV_MasterCmdQueueEmpty(master))
    {
        /* If there are queued commands, send them */
        LPI2C_DRV_MasterSendQueuedCmd(baseAddr, master);
    }
    else if (master->txBuff != NULL)
    {
        /* A transmission is in progress */
        if (master->txSize == 0U)
        {
            /* There is no more data in buffer, the transmission is over */
            LPI2C_DRV_MasterEndTransfer(baseAddr, master, master->sendStop, false);

            /* Signal transfer end for blocking transfers */
            if (master->blocking == true)
            {
                (void)OSIF_SemaPost(&(master->idleSemaphore));
            }

            master->status = STATUS_SUCCESS;

            if (master->masterCallback != NULL)
            {
                master->masterCallback(I2C_MASTER_EVENT_END_TRANSFER, master->callbackParam);
            }
        }
        else
        {
            /* Queue data bytes to fill tx fifo */
            LPI2C_DRV_MasterQueueData(baseAddr, master);
        }
    }
    else
    {
        /* No more commands and no transmission in progress - disable tx event */
        LPI2C_Set_MasterInt(baseAddr, LPI2C_MASTER_TRANSMIT_DATA_INT, false);
    }
#endif
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterHandleReceiveDataRequest
 * Description   : handle a receive request for master
 *
 *END**************************************************************************/
#if 0
static void LPI2C_DRV_MasterHandleReceiveDataReadyEvent(LPI2C_Type *baseAddr, lpi2c_master_state_t *master)
{
    /* Received data ready */
    DEV_ASSERT(master->rxBuff != NULL);

    /* Transfer received data to user buffer */
    while ((LPI2C_Get_MasterRxFIFOCount(baseAddr) > 0U) && (master->rxSize > 0U))
    {
        master->rxBuff[0U] = LPI2C_Get_MasterRxData(baseAddr);
        master->rxBuff++;
        master->rxSize--;
    }
    if (master->rxSize == 0U)
    {
        /* Done receiving */
        LPI2C_DRV_MasterEndTransfer(baseAddr, master, master->sendStop, false);

        /* Signal transfer end for blocking transfers */
        if (master->blocking == true)
        {
          //  (void)OSIF_SemaPost(&(master->idleSemaphore));
        }

        master->status = STATUS_SUCCESS;

        if (master->masterCallback != NULL)
        {
            master->masterCallback(I2C_MASTER_EVENT_END_TRANSFER, master->callbackParam);
        }
    }
    else if (master->rxSize <= LPI2C_Get_MasterRxFIFOWatermark(baseAddr))
    {
        /* Reduce rx watermark to receive the last few bytes */
     //   LPI2C_Set_MasterRxFIFOWatermark(baseAddr, (uint16_t)(master->rxSize - 1U));
    }
    else
    {
        /* Continue reception */
    }
}
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void LPI2C_DRV_HWInit(uint8_t instance,uint32_t baudrate,uint8_t is10bitAddr)
{
    I2C_SFRmap* I2cx  = g_lpi2cBase[instance];
    I2C_InitTypeDef I2cConfigPtr;

	 /* I2c mode */
	 I2cConfigPtr.m_Mode = I2C_MODE_I2C;
	 /* I2c clock */
	 I2cConfigPtr.m_ClockSource = I2C_CLK_HFCLK;  /*16M*/

	 if(0 == is10bitAddr)
	 {
		 I2cConfigPtr.m_BADR10 = I2C_BUFRADDRESS_7BIT;
	 }
	 else
	 {
		 I2cConfigPtr.m_BADR10 =  I2C_BUFRADDRESS_10BIT;
	 }

	 /* SMBus type */
	 I2cConfigPtr.m_MasterSlave = I2C_MODE_SMBUSHOST;

	 if(250000 == baudrate)
	 {
		 /* I2c baud rate low level time */
		 I2cConfigPtr.m_BaudRateL = 32;
		 /* I2c baud rate high level time */
		 I2cConfigPtr.m_BaudRateH = 32;
	 }
	 else if(500000 == baudrate)
	 {
		/* I2c baud rate low level time */
		I2cConfigPtr.m_BaudRateL = 16;
		/* I2c baud rate high level time */
		I2cConfigPtr.m_BaudRateH = 16;
	 }
	 else if(1000000 == baudrate)
	 {
		/* I2c baud rate low level time */
		I2cConfigPtr.m_BaudRateL = 8;
		/* I2c baud rate high level time */
		I2cConfigPtr.m_BaudRateH = 8;
	 }
	 else
	 {
		/* I2c baud rate low level time */
		I2cConfigPtr.m_BaudRateL = 32;
		/* I2c baud rate high level time */
		I2cConfigPtr.m_BaudRateH = 32;
	 }
	 /* Enable ACK */
	 I2cConfigPtr.m_AckEn = TRUE;
	 /* Select the response signal as ACK */
	 I2cConfigPtr.m_AckData = I2C_ACKDATA_ACK;

    I2C_Reset(I2cx);
    /* Configue I2C */
    I2C_Configuration(I2cx, &I2cConfigPtr);
    /* Enable I2C HW module */
    I2C_Cmd(I2cx, TRUE);
    /* Clear Interrupt flag */
    I2C_Clear_INTERRUPT_Flag(I2cx);
    /* Enable I2C address match */
    I2C_MATCH_ADDRESS_Config(I2cx, TRUE);
    /* Enable I2C HW module */
    I2C_Cmd(I2cx, TRUE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterInit
 * Description   : initialize the I2C master mode driver
 *
 * Implements : LPI2C_DRV_MasterInit_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterInit(uint32_t instance,
                                    const lpi2c_master_user_config_t * userConfigPtr,
                                    lpi2c_master_state_t * master)
{
    LPI2C_Type *baseAddr;

    lpi2c_baud_rate_params_t baudRate;

    DEV_ASSERT(master != NULL);
    DEV_ASSERT(userConfigPtr != NULL);
    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    /* Check to see if the LPI2C master instance is already initialized */
    DEV_ASSERT(g_lpi2cMasterStatePtr[instance] == NULL);

    baseAddr = g_lpi2cBase[instance];
    g_lpi2cMasterStatePtr[instance] = master;

    /* Initialize driver status structure */
    master->rxBuff = NULL;
    master->rxSize = 0U;
    master->txBuff = NULL;
    master->txSize = 0U;
    master->status = STATUS_SUCCESS;
    master->i2cIdle = true;
    master->slaveAddress = userConfigPtr->slaveAddress;
    master->is10bitAddr = userConfigPtr->is10bitAddr;
    master->transferType = userConfigPtr->transferType;
    /* Store DMA channel number used in transfer */
    master->dmaChannel = userConfigPtr->dmaChannel;
    master->masterCallback = userConfigPtr->masterCallback;
    master->callbackParam = userConfigPtr->callbackParam;
#if(LPI2C_HAS_HIGH_SPEED_MODE)
    master->masterCode = userConfigPtr->masterCode;
    master->highSpeedInProgress = false;
#endif
    master->blocking = false;
    master->baudrate = userConfigPtr->baudRate;
    master->abortedTransfer = false;

    LPI2C_DRV_MasterResetQueue(master);

    /* Enable lpi2c interrupt */
   // INT_SYS_EnableIRQ(g_lpi2cMasterIrqId[instance]);

    /* Set baud rate */
    baudRate.baudRate = userConfigPtr->baudRate;
    /* Set slave address */
    LPI2C_DRV_MasterSetSlaveAddr(instance, userConfigPtr->slaveAddress, userConfigPtr->is10bitAddr);

    LPI2C_DRV_HWInit((uint8_t)instance, baudRate.baudRate,userConfigPtr->is10bitAddr);

    return STATUS_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterDeinit
 * Description   : deinitialize the I2C master mode driver
 *
 * Implements : LPI2C_DRV_MasterDeinit_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterDeinit(uint32_t instance)
{
    LPI2C_Type *baseAddr;
    const lpi2c_master_state_t *master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Destroy the semaphore */
 //   (void)OSIF_SemaDestroy(&(master->idleSemaphore));

    g_lpi2cMasterStatePtr[instance] = NULL;

    /* Disable master */
   // LPI2C_Set_MasterEnable(baseAddr, false);

    /* Disable i2c interrupt */
   // INT_SYS_DisableIRQ(g_lpi2cMasterIrqId[instance]);

    I2C_Cmd(g_lpi2cBase[instance], FALSE);
    INT_Interrupt_Enable(g_lpi2cMasterIrqId[instance], false);
    I2C_ISIE_INT_Enable(g_lpi2cBase[instance], false);

    return STATUS_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterGetBaudRate
 * Description   : returns the currently configured baud rate
 *
 * Implements : LPI2C_DRV_MasterGetBaudRate_Activity
 *END**************************************************************************/
#if 0
void LPI2C_DRV_MasterGetBaudRate(uint32_t instance, lpi2c_baud_rate_params_t *baudRate)
{
    const LPI2C_Type *baseAddr;
    const lpi2c_master_state_t *master;
    status_t retVal;
    uint32_t prescaler;
    uint32_t clkLo;
    uint32_t clkHi;
    uint32_t inputClock;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Get the protocol clock frequency */
    retVal = CLOCK_SYS_GetFreq(g_lpi2cClock[instance], &inputClock);
    DEV_ASSERT(retVal == STATUS_SUCCESS);
    DEV_ASSERT(inputClock > 0U);

    /* Ignoring the glitch filter, the baud rate formula is:
            SCL_freq = Input_freq / (2^PRESCALER * (CLKLO + CLKHI + 2))
    */
    prescaler = LPI2C_Get_MasterPrescaler(baseAddr);
    clkHi =LPI2C_Get_MasterClockHighPeriod(baseAddr);
    clkLo = LPI2C_Get_MasterClockLowPeriod(baseAddr);

    baudRate->baudRate = inputClock / (((uint32_t)1U << prescaler) * (clkLo + clkHi + (uint32_t)2U));

#if(LPI2C_HAS_HIGH_SPEED_MODE)
    if (master->operatingMode == LPI2C_HIGHSPEED_MODE)
    {
        clkHi = LPI2C_Get_MasterClockHighPeriodHS(baseAddr);
        clkLo = LPI2C_Get_MasterClockLowPeriodHS(baseAddr);

        baudRate->baudRateHS = inputClock / (((uint32_t)1U << prescaler) * (clkLo + clkHi + (uint32_t)2U));
    }
#endif

    (void)retVal;
    (void)master;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSetBaudRate
 * Description   : set the baud rate for any subsequent I2C communication
 *
 * Implements : LPI2C_DRV_MasterSetBaudRate_Activity
 *END**************************************************************************/
#if 0
status_t LPI2C_DRV_MasterSetBaudRate(uint32_t instance,
                                const lpi2c_mode_t operatingMode,
                                const lpi2c_baud_rate_params_t baudRate)
{
    LPI2C_Type *baseAddr;
    const lpi2c_master_state_t * master;
    status_t retVal;
    uint32_t inputClock;
    uint32_t minPrescaler = 0U;
    uint32_t prescaler;
    uint32_t clkTotal;
    uint32_t clkLo;
    uint32_t clkHi;
    uint32_t setHold;
    uint32_t dataVd;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check if driver is busy */
    if(!master->i2cIdle)
    {
        return STATUS_BUSY;
    }

    /* Get the protocol clock frequency */
    retVal = CLOCK_SYS_GetFreq(g_lpi2cClock[instance], &inputClock);
    DEV_ASSERT(retVal == STATUS_SUCCESS);
    DEV_ASSERT(inputClock > 0U);

    /* Disable master */
    LPI2C_Set_MasterEnable(baseAddr, false);

    /* Ignoring the glitch filter, the baud rate formula is:
            SCL_freq = Input_freq / (2^PRESCALER * (CLKLO + CLKHI + 2))
            Assume CLKLO = 2*CLKHI, SETHOLD = CLKHI, DATAVD = CLKHI/2
    */

    if (baudRate.baudRate != 0U)
    {
        /* Compute minimum prescaler for which CLKLO and CLKHI values are in valid range. Always round up. */
        minPrescaler = ((inputClock - 1U) / ((baudRate.baudRate) * (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U))) + (uint32_t)1U;
        for (prescaler = 0U; prescaler < 7U; prescaler++)
        {
            if (((uint32_t)1U << prescaler) >= minPrescaler)
            {
                break;
            }
        }

        /* Compute CLKLO and CLKHI values for this prescaler. Round to nearest integer. */
        clkTotal = (inputClock + ((baudRate.baudRate << prescaler) >> 1U)) / (baudRate.baudRate << prescaler);
    }
    else
    {
        prescaler = 7U;
        clkTotal = (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U);
    }

    if (clkTotal > (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U))
    {
        clkTotal = (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U);
    }

    /*
     * If we try to compute clk high and low values using clkTotal equal with 0
     * (this is the case when the baudrate is 0), we will get negative values for
     * them, so we set them to 0 for this case.
     */
    if (clkTotal <= 1U)
    {
        clkHi = 0U;
        clkLo = 0U;
    }
    else
    {
        clkHi = (clkTotal - 2U) / 3U;
        clkLo = clkTotal - 2U - clkHi;
    }

    if (clkHi < CLKHI_MIN_VALUE)
    {
        clkHi = CLKHI_MIN_VALUE;
    }
    if (clkLo < CLKLO_MIN_VALUE)
    {
        clkLo = CLKLO_MIN_VALUE;
    }

    /* Compute DATAVD and SETHOLD */
    setHold = clkHi;
    dataVd = clkHi >> 1U;
    if (setHold < SETHOLD_MIN_VALUE)
    {
        setHold = SETHOLD_MIN_VALUE;
    }
    if (dataVd < DATAVD_MIN_VALUE)
    {
        dataVd = DATAVD_MIN_VALUE;
    }

    /* Apply settings */
    LPI2C_Set_MasterPrescaler(baseAddr, (lpi2c_master_prescaler_t)prescaler);
    LPI2C_Set_MasterDataValidDelay(baseAddr, (uint8_t)dataVd);
    LPI2C_Set_MasterSetupHoldDelay(baseAddr, (uint8_t)setHold);
    LPI2C_Set_MasterClockHighPeriod(baseAddr, (uint8_t)clkHi);
    LPI2C_Set_MasterClockLowPeriod(baseAddr, (uint8_t)clkLo);

#if(LPI2C_HAS_HIGH_SPEED_MODE)
    if (operatingMode == LPI2C_HIGHSPEED_MODE)
    {
        /* Compute settings for High-speed baud rate */
        /* Compute High-speed CLKLO and CLKHI values for the same prescaler. Round to nearest integer. */
        clkTotal = (inputClock + ((baudRate.baudRateHS << prescaler) >> 1U)) / (baudRate.baudRateHS << prescaler);
        if (clkTotal > (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U))
        {
            clkTotal = (CLKHI_MAX_VALUE + CLKLO_MAX_VALUE + 2U);
        }

        clkHi = (clkTotal - 2U) / 3U;
        clkLo = clkTotal - 2U - clkHi;
        if (clkHi < CLKHI_MIN_VALUE)
        {
            clkHi = CLKHI_MIN_VALUE;
        }
        if (clkLo < CLKLO_MIN_VALUE)
        {
            clkLo = CLKLO_MIN_VALUE;
        }

        /* Compute High-speed DATAVD and SETHOLD */
        setHold = clkHi;
        dataVd = clkHi >> 1U;
        if (setHold < SETHOLD_MIN_VALUE)
        {
            setHold = SETHOLD_MIN_VALUE;
        }
        if (dataVd < DATAVD_MIN_VALUE)
        {
            dataVd = DATAVD_MIN_VALUE;
        }

        /* Apply High-speed settings */
        LPI2C_Set_MasterDataValidDelayHS(baseAddr, (uint8_t)dataVd);
        LPI2C_Set_MasterSetupHoldDelayHS(baseAddr, (uint8_t)setHold);
        LPI2C_Set_MasterClockHighPeriodHS(baseAddr, (uint8_t)clkHi);
        LPI2C_Set_MasterClockLowPeriodHS(baseAddr, (uint8_t)clkLo);
    }
#endif

    /* Perform other settings related to the chosen operating mode */
    LPI2C_DRV_MasterSetOperatingMode(instance, operatingMode);

    /* Re-enable master */
    LPI2C_Set_MasterEnable(baseAddr, true);
    
    (void) minPrescaler;
    (void)master;
    (void)retVal;

    return STATUS_SUCCESS;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSetSlaveAddr
 * Description   : set the slave address for any subsequent I2C communication
 *
 * Implements : LPI2C_DRV_MasterSetSlaveAddr_Activity
 *END**************************************************************************/
void LPI2C_DRV_MasterSetSlaveAddr(uint32_t instance, const uint16_t address, const bool is10bitAddr)
{
    lpi2c_master_state_t * master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    master->slaveAddress = address;
    master->is10bitAddr = is10bitAddr;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSendData
 * Description   : perform a non-blocking send transaction on the I2C bus
 *
 * Implements : LPI2C_DRV_MasterSendData_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterSendData(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            bool sendStop)
{
    LPI2C_Type *baseAddr;
    lpi2c_master_state_t *master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(txSize > 0U);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check if driver is busy */
    if(!master->i2cIdle)
    {
    	return STATUS_BUSY;
    }

    /* Copy parameters to driver state structure */
    master->txBuff = txBuff;
    master->txSize = txSize;
    master->sendStop = sendStop;
    master->i2cIdle = false;
    master->status = STATUS_BUSY;

	/* Initiate communication */
	LPI2C_DRV_MasterSendAddress(baseAddr, master, false);

	/* Queue data bytes to fill tx fifo */
	LPI2C_DRV_MasterQueueData(baseAddr, master);

	/* Set tx FIFO watermark */
   // LPI2C_Set_MasterTxFIFOWatermark(baseAddr, 0U);

    master->i2cIdle = true;
    return STATUS_SUCCESS;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterWaitTransferEnd
 * Description   : waits for the end of a blocking transfer
 *
 *END**************************************************************************/
static status_t LPI2C_DRV_MasterWaitTransferEnd(uint32_t instance, uint32_t timeout)
{
#if 0
    LPI2C_Type *baseAddr;
    status_t osifError = STATUS_SUCCESS;
    lpi2c_master_state_t *master;
    uint16_t rxFifoFill = 0;

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];

    /* Wait for transfer to be completed by the IRQ */
    osifError = OSIF_SemaWait(&(master->idleSemaphore), timeout);

    if (osifError == STATUS_TIMEOUT)
    {
    	/* If master is sending data transfer is aborted now in case timeout occurred */
        if(master->txSize != 0U)
        {
	    	LPI2C_DRV_MasterEndTransfer(baseAddr, master, false, true);

	    	master->status = STATUS_TIMEOUT;
        }
        else
        {
        	if(master->transferType == LPI2C_USING_DMA)
        	{
        		/* Stop DMA channel and activate interrupts */
        		(void)EDMA_DRV_StopChannel(master->dmaChannel);
        	}

        	/* Disable interrupts to check number of bytes in rx fifo */
        	LPI2C_Set_MasterInt(baseAddr, LPI2C_MASTER_RECEIVE_DATA_INT, false);

        	/* Check number of bytes in rx fifo */
        	rxFifoFill = LPI2C_Get_MasterRxFIFOCount(baseAddr);

        	/* In case both rx size and number of bytes in rx fifo is 0, then the transfer ended successfully */
        	if((rxFifoFill == master->rxSize) && (master->rxSize ==  0U))
        	{
        		master->status = STATUS_SUCCESS;

        	    /* Blocking transfer is over */
        	    master->blocking = false;

        		return master->status;
        	}

        	/* Set watermark to rxFifoFill in case the rx size is grater than the number of bytes in the rx  fifo */
        	if(rxFifoFill < master->rxSize)
        	{
        		master->abortedTransfer = true;
        		LPI2C_Set_MasterRxFIFOWatermark(baseAddr, rxFifoFill);

            	master->status = STATUS_TIMEOUT;
        	}

        	LPI2C_Set_MasterInt(baseAddr, LPI2C_MASTER_RECEIVE_DATA_INT, true);

        	osifError = OSIF_SemaWait(&(master->idleSemaphore), timeout);
            if(osifError == STATUS_TIMEOUT)
            {
            	(void)LPI2C_DRV_MasterReinit(instance, master);
                master->status = STATUS_TIMEOUT;
            }

            master->abortedTransfer = false;
        }
    }

    /* Blocking transfer is over */
    master->blocking = false;
    return master->status;
#endif
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterSendDataBlocking
 * Description   : perform a blocking send transaction on the I2C bus
 *
 * Implements : LPI2C_DRV_MasterSendDataBlocking_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterSendDataBlocking(uint32_t instance,
                                    const uint8_t * txBuff,
                                    uint32_t txSize,
                                    bool sendStop,
                                    uint32_t timeout)
{

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(txSize > 0U);

    lpi2c_master_state_t *master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check if driver is busy */
    if(!master->i2cIdle)
    {
    	return STATUS_BUSY;
    }

    /* mark transfer as blocking */
    master->blocking = true;

    /* Dummy wait to ensure the semaphore is 0, no need to check result */
  //  (void)OSIF_SemaWait(&(master->idleSemaphore), 0);

    (void)LPI2C_DRV_MasterSendData(instance, txBuff, txSize, sendStop);

    /* Wait for transfer to end */
    return LPI2C_DRV_MasterWaitTransferEnd(instance, timeout);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterAbortTransferData
 * Description   : abort a non-blocking I2C Master transmission or reception
 *
 * Implements : LPI2C_DRV_MasterAbortTransferData_Activity
 *END**************************************************************************/
#if 0
status_t LPI2C_DRV_MasterAbortTransferData(uint32_t instance)
{
    LPI2C_Type *baseAddr;
    lpi2c_master_state_t * master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    if (master->rxBuff != NULL)
    {
        /* Aborting a reception not supported because hardware will continue the
           current command even if the FIFO is reset and this could last indefinitely */
        return STATUS_UNSUPPORTED;
    }

    /* End transfer: force stop generation, reset FIFOs */
    master->status = STATUS_I2C_ABORTED;
    LPI2C_DRV_MasterEndTransfer(baseAddr, master, true, true);

    return STATUS_SUCCESS;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterReceiveData
 * Description   : perform a non-blocking receive transaction on the I2C bus
 *
 * Implements : LPI2C_DRV_MasterReceiveData_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterReceiveData(uint32_t  instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize,
                                       bool sendStop)
{
    LPI2C_Type *baseAddr;
    lpi2c_master_state_t * master;
    uint16_t rxBytes;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(rxSize > 0U);

    DEV_ASSERT(rxSize <= 256U);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check if driver is busy */
    if(!master->i2cIdle)
    {
    	return STATUS_BUSY;
    }

#if(LPI2C_HAS_ULTRA_FAST_MODE)
    if (master->operatingMode == LPI2C_ULTRAFAST_MODE)
    {
        /* No reception possible in ultra-fast mode */
        return STATUS_ERROR;
    }
#endif

    /* Copy parameters to driver state structure */
    master->rxSize = rxSize;
    master->i2cIdle = false;
    master->sendStop = sendStop;
    master->rxBuff = rxBuff;
    master->status = STATUS_BUSY;


	/* Initiate communication */
	LPI2C_DRV_MasterSendAddress(baseAddr, master, true);
	/* Queue receive command for rxSize bytes */
	LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_RECEIVE, (uint8_t)(rxSize - 1U));

	LPI2C_DRV_MasterQueueCmd(baseAddr, master, LPI2C_MASTER_COMMAND_STOP,0);

    master->i2cIdle = true;
    return STATUS_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterReceiveDataBlocking
 * Description   : perform a blocking receive transaction on the I2C bus
 *
 * Implements : LPI2C_DRV_MasterReceiveDataBlocking_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterReceiveDataBlocking(uint32_t instance,
                                           uint8_t * rxBuff,
                                           uint32_t rxSize,
                                           bool sendStop,
                                           uint32_t timeout)
{
	status_t retVal = STATUS_SUCCESS;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(rxSize > 0U);

    lpi2c_master_state_t *master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check if driver is busy */
    if(!master->i2cIdle)
    {
    	return STATUS_BUSY;
    }

    /* mark transfer as blocking */
    master->blocking = true;

    /* Dummy wait to ensure the semaphore is 0, no need to check result */
  //  (void)OSIF_SemaWait(&(master->idleSemaphore), 0);

    retVal = LPI2C_DRV_MasterReceiveData(instance, rxBuff, rxSize, sendStop);

#if(LPI2C_HAS_ULTRA_FAST_MODE)
    if (retVal != STATUS_SUCCESS)
    {
        master->blocking = false;
        return retVal;
    }
#endif

    (void) retVal;

    /* Wait for transfer to end */
    return LPI2C_DRV_MasterWaitTransferEnd(instance, timeout);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterGetTransferStatus
 * Description   : return the current status of the I2C master transfer
 *
 * When performing an a-sync (non-blocking) transfer, the user can call this function
 * to ascertain the state of the current transfer. In addition, if the transfer is still
 * in progress, the user can get the number of words that should be receive.
 *
 * Implements : LPI2C_DRV_MasterGetTransferStatus_Activity
 *END**************************************************************************/
status_t LPI2C_DRV_MasterGetTransferStatus(uint32_t instance,
                                                uint32_t *bytesRemaining)
{
    const LPI2C_Type *baseAddr;
    const lpi2c_master_state_t * master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    if ((bytesRemaining != NULL) && (master->transferType == LPI2C_USING_INTERRUPTS))
    {
        if (master->txSize > 0U)
        {
            /* Send data */
            /* Remaining bytes = bytes in buffer + bytes in tx FIFO */
        //    *bytesRemaining = master->txSize + LPI2C_Get_MasterTxFIFOCount(baseAddr);
        }
        else if (master->rxSize > 0U)
        {
            /* Receive data */
            /* Remaining bytes = free space in buffer - bytes in rx FIFO */
         //   *bytesRemaining = master->rxSize - LPI2C_Get_MasterRxFIFOCount(baseAddr);
        }
        else
        {
            *bytesRemaining = 0U;
        }
    }

    return master->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : void LPI2C_DRV_MasterIRQInit(lpi2c_Index instance,FunctionalState Status)
 * Description   : Gets the default configuration structure for master
 *
 * Implements : LPI2C_DRV_MasterGetDefaultConfig_Activity
 *END**************************************************************************/
void LPI2C_DRV_MasterIRQInit(lpi2c_Index instance,FunctionalState Status)
{
	I2C_SFRmap* I2cx  = g_lpi2cBase[instance];
	InterruptIndex Index[LPI2C_INSTANCE_COUNT] = {INT_I2C0,INT_I2C1,INT_I2C2,INT_I2C3};

	DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    INT_Interrupt_Enable(Index[instance], Status);
    I2C_ISIE_INT_Enable(I2cx, Status);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPI2C_DRV_MasterIRQHandler
 * Description   : handle non-blocking master operation when I2C interrupt occurs
 *
 *END**************************************************************************/
#if 0



void LPI2C_DRV_MasterIRQHandler(uint32_t instance)
{
    LPI2C_Type *baseAddr;
    lpi2c_master_state_t * master;

    DEV_ASSERT(instance < LPI2C_INSTANCE_COUNT);

    baseAddr = g_lpi2cBase[instance];
    master = g_lpi2cMasterStatePtr[instance];
    DEV_ASSERT(master != NULL);

    /* Check which event caused the interrupt */
    if (LPI2C_Get_MasterTransmitDataRequestEvent(baseAddr))
    {
        LPI2C_DRV_MasterHandleTransmitDataRequest(baseAddr, master);
    }

    if ((LPI2C_Get_MasterReceiveDataReadyEvent(baseAddr)))
    {
    	if(master->abortedTransfer)
    	{
    		 /* Signal transfer end for blocking transfers */
    		 if (master->blocking == true)
    		 {
    		     (void)OSIF_SemaPost(&(master->idleSemaphore));
    		 }

    		 master->status = STATUS_TIMEOUT;

            (void)LPI2C_DRV_MasterReinit(instance, master);
    	}
    	else
    	{
    	     LPI2C_DRV_MasterHandleReceiveDataReadyEvent(baseAddr, master);
    	}
    }

    if (LPI2C_Get_MasterFIFOErrorEvent(baseAddr))
    {
        /* FIFO error */
        LPI2C_Clear_MasterFIFOErrorEvent(baseAddr);

#if(LPI2C_HAS_HIGH_SPEED_MODE)
        /* High-speed transfers end at STOP condition */
        master->highSpeedInProgress = false;
#endif
        master->status = STATUS_ERROR;

        /* End transfer: no stop generation (the module will handle that by itself
           if needed), reset FIFOs */
        LPI2C_DRV_MasterEndTransfer(baseAddr, master, false, true);

        /* Signal transfer end for blocking transfers */
        if (master->blocking == true)
        {
            (void)OSIF_SemaPost(&(master->idleSemaphore));
        }

        if (master->masterCallback != NULL)
        {
            /***
             * [2019.07.17] ancle:
             *  Add event: event changed, I2C_MASTER_EVENT_END_TRANSFER change to I2C_MASTER_EVENT_FIFO_ERROR;
             **/
            master->masterCallback( I2C_MASTER_EVENT_FIFO_ERROR, master->callbackParam );
        }
    }

    if (LPI2C_Get_MasterArbitrationLostEvent(baseAddr))
    {
        /* Arbitration lost */
        LPI2C_Clear_MasterArbitrationLostEvent(baseAddr);

        /* End transfer: no stop generation (the module will handle that by itself
           if needed), reset FIFOs */
        LPI2C_DRV_MasterEndTransfer(baseAddr, master, false, true);

        /* Signal transfer end for blocking transfers */
        if (master->blocking == true)
        {
            (void)OSIF_SemaPost(&(master->idleSemaphore));
        }

        master->status = STATUS_I2C_ARBITRATION_LOST;

        if (master->masterCallback != NULL)
        {
            master->masterCallback(I2C_MASTER_EVENT_END_TRANSFER, master->callbackParam);
        }
    }

    if (LPI2C_Get_MasterNACKDetectEvent(baseAddr))
    {
        /* Received NACK */

#if(LPI2C_HAS_ULTRA_FAST_MODE)
        /* Ignore NACK in Ultra Fast mode */
        if (master->operatingMode != LPI2C_ULTRAFAST_MODE)
        {
#endif
            /* Signal transfer end for blocking transfers */
            if (master->blocking == true)
            {
                (void)OSIF_SemaPost(&(master->idleSemaphore));
            }

#if(LPI2C_HAS_HIGH_SPEED_MODE)
            /* High-speed transfers end at STOP condition */
            master->highSpeedInProgress = false;
#endif
            master->status = STATUS_I2C_RECEIVED_NACK;

            /* End transfer: no stop generation (the module will handle that by itself
               if needed), reset FIFOs */
            LPI2C_DRV_MasterEndTransfer(baseAddr, master, false, true);

            if (master->masterCallback != NULL)
            {
                master->masterCallback(I2C_MASTER_EVENT_END_TRANSFER, master->callbackParam);
            }
			
		    /* Clear NACK flag */
            LPI2C_Clear_MasterNACKDetectEvent(baseAddr);
#if(LPI2C_HAS_ULTRA_FAST_MODE)
        }
#endif
    }
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
