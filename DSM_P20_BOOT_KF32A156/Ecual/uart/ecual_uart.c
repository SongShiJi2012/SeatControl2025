/*************************************************************************************************
 * Includes
 *************************************************************************************************/
#include "lpuart_driver.h"
#include "ecual_uart.h"
/*************************************************************************************************
 * Variable declaration
 *************************************************************************************************/
//默认串口外设配置表
static lpuart_user_config_t s_lpuart_InitConfig[ MAX_UART_NUM ] = {
  {
	  .transferType = LPUART_USING_INTERRUPTS,//LPUART_USING_DMA,//LPUART_USING_INTERRUPTS,//LPUART_USING_POLLING,
	  .baudRate = 38400U,
	  .parityMode = LPUART_PARITY_DISABLED,
	  .stopBitCount = LPUART_ONE_STOP_BIT,
	  .bitCountPerChar = LPUART_8_BITS_PER_CHAR,
	  .rxDMAChannel = 0U,
	  .txDMAChannel = 0U,
  },
  {
	  .transferType = LPUART_USING_DMA,//LPUART_USING_DMA,//LPUART_USING_INTERRUPTS,//LPUART_USING_POLLING,
	  .baudRate = 115200U,
	  .parityMode = LPUART_PARITY_DISABLED,
	  .stopBitCount = LPUART_ONE_STOP_BIT,
	  .bitCountPerChar = LPUART_8_BITS_PER_CHAR,
	  .rxDMAChannel = 6U,
	  .txDMAChannel = 2U,
  },
  {
	  .transferType = LPUART_USING_DMA,//LPUART_USING_DMA,//LPUART_USING_INTERRUPTS,//LPUART_USING_POLLING,
	  .baudRate = 115200U,
	  .parityMode = LPUART_PARITY_DISABLED,
	  .stopBitCount = LPUART_ONE_STOP_BIT,
	  .bitCountPerChar = LPUART_8_BITS_PER_CHAR,
	  .rxDMAChannel = 6U,
	  .txDMAChannel = 2U,
  }
};

//串口外设状态机
static lpuart_state_t s_lpuart_State[ MAX_UART_NUM ];
//串口外设初始化标志
static bool_t s_lpuartInited[ MAX_UART_NUM ] = { FALSE };

/*************************************************************************************************
 * Function Define
 *************************************************************************************************/

/*************************************************************************************************
 * @function name:  ecual_UART_init
 *
 * @description:    Initial the serial(uart) interface port
 *
 * @parameters:     none
 *
 * @return:         ture is successful
 ************************************************************************************************/
bool_t ecual_UART_init( const uint8_t port,
                        uart_callback_t pfnTxCB,
                        uart_callback_t pfnRxCB
                        )
{
    bool_t rt = FALSE;
    status_t retVal = STATUS_SUCCESS;

    if ( port < MAX_UART_NUM )
    {
        if ( s_lpuartInited[port] )
        {
            /* have inited */
            rt = TRUE;
        }
        else
        {
			retVal = LPUART_DRV_Init( port, &s_lpuart_State[port], &s_lpuart_InitConfig[port] );
			if ( STATUS_SUCCESS == retVal)
			{
				;//
			}
			rt = ( STATUS_SUCCESS == retVal ) ? TRUE : FALSE;
        }
    }

    if ( rt )//注册回调函数
    {
        if ( NULL != pfnTxCB )
        {
            LPUART_DRV_InstallTxCallback( port, pfnTxCB, NULL );
        }
        if ( NULL != pfnRxCB )
        {
            LPUART_DRV_InstallRxCallback( port, pfnRxCB, NULL );
        }

		//UartLockSet(port);//?初始化事件时时不是有set么

        s_lpuartInited[port] = TRUE;
    }

    return rt;
}

/*************************************************************************************************
 * @function name:  ecual_UART_deinit
 *
 * @description:    de-initial the serial(uart) interface port
 *
 * @parameters:     none
 *
 * @return:         ture is successful
 ************************************************************************************************/
bool_t ecual_UART_deinit( const uint8_t port )
{
    bool_t rt = FALSE;
    status_t retVal = STATUS_SUCCESS;

    if ( s_lpuartInited[port] )
    {
        retVal = LPUART_DRV_Deinit( port );
        rt = ( STATUS_SUCCESS == retVal ) ? TRUE : FALSE;
        if ( rt )
        {
        	s_lpuartInited[port] = FALSE;
        }
    }

	//UartLockSet(port);

    return rt;
}

int8_t ecual_UART_getc( const uint8_t port)
{
    int8_t rv = -1;
    uint8_t value = 0;
    status_t retVal = STATUS_SUCCESS;

    if ( s_lpuartInited[port] )
    {
    	retVal = LPUART_DRV_ReceiveOneData( port, &value );
    	if(STATUS_SUCCESS == retVal )
    	{
    		rv = value;
    	}
    }

    return rv;
}

bool_t ecual_UART_puts( const uint8_t port, const uint8_pt buffer, const uint32_t size )
{
    bool_t rt = FALSE;
    status_t retVal = STATUS_SUCCESS;

    if ( s_lpuartInited[port] )
    {
        retVal = LPUART_DRV_SendData( port, buffer, size );

        rt = ( STATUS_SUCCESS == retVal ) ? TRUE : FALSE;
    }

    return rt;
}
