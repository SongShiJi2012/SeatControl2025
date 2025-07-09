/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kflog.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2023-07-12
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.0.1.230712_release
 *  @Description      : This document describes the C language document template.
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

/******************************************************************************
 **                        MISRA-C Rules Violations
 ******************************************************************************/
/**
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section
 */

/******************************************************************************
 **                        QAC Warnings
 ******************************************************************************/
/**
 * @page QAC Warnings
 */
/*PRQA S 0380 EOF #Number of macro definitions exceeds 4095 - program does not
 * conform strictly to ISO:C99. */
/*PRQA S 0306 EOF #Cast between a pointer to object and an integral type */
/*PRQA S 1006 EOF #This in-line assembler construct is a language extension. The
 * code has been ignored. */
/*PRQA S 3205 EOF #The identifier '%1s' is not used and could be removed. */
/*PRQA S 3218 EOF #File scope static, '%1s', is only accessed in one function.
 */
/*PRQA S 3625 EOF #Type 'char' has been used in the declaration of an object or
 * a function. */
/*PRQA S 1337 EOF #Function defined with a variable number of parameters. */
/*PRQA S 3416 EOF #Logical operation performed on expression with persistent
 * side effects. */
/*PRQA S 3200 EOF #'%1s' returns a value which is not being used. */
/*PRQA S 3209 EOF #'%1s()' returns a value which is always ignored. */

#include "kflog.h"
#ifdef KF_INTERNAL_PRINT
/******************************************************************************
 **                        Include Files
 ******************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "system_init.h"

/******************************************************************************
 **                        File Version Check
 ******************************************************************************/

/******************************************************************************
 **                        user config
 ******************************************************************************/

/**
 * @brief:
 */
enum
{
    UART0_INDEX,
    UART1_INDEX,
    UART2_INDEX,
    UART3_INDEX,
    UART4_INDEX,
    UART5_INDEX,
    UART6_INDEX,
    UART7_INDEX,
    UART8_INDEX,
    UART9_INDEX,
    UART10_INDEX,
    UART11_INDEX,
    UART12_INDEX,
    UART13_INDEX,
    UART14_INDEX,
    UART15_INDEX
};

/**
 * @brief:debugging Log Configuration
 * the default configuration is UART0, baud rate is 921600U
 * the maximum configuration is 921600,the minimum baud rate 1200
 */
#define KFLOG_UART           UART2_INDEX
#define KFLOG_UART_FREQUENCY ((uint32_t)115200U)

/******************************************************************************
 **                        Macro  Definitions
 ******************************************************************************/
/* wait maxtime */
#define UART_TRANSMIT_TIMEOUT ((uint32_t)0xFFFFU)
/* uart select clock */
#define KFLOG_UART_CLOCK ((uint32_t)120000000U)

#define KFLOG_UART_MAX_DATA_LEN (256U)
#define KFLOG_UART_MAX_LINE_NUM (12U)

/******************************************************************************
 **                        Typedef  Definitions
 ******************************************************************************/

/******************************************************************************
**                     Variable Declarations
******************************************************************************/
static uint8_t kvUart_InitStatus = 0u;
/**
 * @brief:log output buffer
 */
static char kvLog_SendData[KFLOG_UART_MAX_DATA_LEN];
static char kvLog_LineNum[KFLOG_UART_MAX_LINE_NUM];

static USART_SFRmap *const kvUart_UnitPtr[16] = {
  USART0_SFR,
  USART1_SFR,
  USART2_SFR,
};
/******************************************************************************
 **                      Private Function Declarations
 ******************************************************************************/

/******************************************************************************
 **                        Export Variables
 ******************************************************************************/

/******************************************************************************
 **                        Export Functions
 ******************************************************************************/
/**
 * @brief:Log information output
 * @param in:plog_module-Information about the registered module
 * LogLevel-Print level
 * pfun-function name
 * line-line num
 * pfile-The file path
 * format,...-varargs
 * @param out:None
 * @retval:None
 */
void kfLog_Printf(const Log_PrintfType *const plog_module, const char *const pfun, const int line,
                  const char *const pfile, const char *format, ...)
{
    /* PRQA S 0751,0488,0702,0432,0771 ++ */
    va_list  args;
    uint32_t TmpLen = 0u;

    memset(kvLog_SendData, 0, (uint32_t)sizeof(kvLog_SendData));
    memset(kvLog_LineNum, 0, (uint32_t)sizeof(kvLog_LineNum));

    if (kvUart_InitStatus == 0u)
    {
        return;
    }
    else
    {
        /* Empty */
    }

    do
    {
        /* module name */
        if (NULL != plog_module)
        {
            if ((strlen(plog_module->name) + strlen("[]")) > ((uint32_t)sizeof(kvLog_SendData) - 1u))
            {
                break;
            }
            else
            {
                /* Empty */
            }
            sprintf(kvLog_SendData, "[%s]", plog_module->name);
            TmpLen = strlen(kvLog_SendData);

            if (0u != (plog_module->opt & KF_LOG_OPT_FUNC))
            {
                if ((TmpLen + strlen(pfun) + strlen("[]")) > ((uint32_t)sizeof(kvLog_SendData) - 1u))
                {
                    break;
                }
                else
                {
                    /* Empty */
                }
                sprintf(&kvLog_SendData[strlen(kvLog_SendData)], "[%s]", pfun);
                TmpLen = strlen(kvLog_SendData);
            }
            else
            {
                /* Empty */
            }

            if (0u != (plog_module->opt & KF_LOG_OPT_LINE))
            {
                sprintf(kvLog_LineNum, "%d", line);
                if ((TmpLen + strlen(kvLog_LineNum) + strlen("[]")) > ((uint32_t)sizeof(kvLog_SendData) - 1u))
                {
                    break;
                }
                else
                {
                    /* Empty */
                }
                sprintf(&kvLog_SendData[strlen(kvLog_SendData)], "[%d]", line);
                TmpLen = strlen(kvLog_SendData);
            }
            else
            {
                /* Empty */
            }

            if (0u != (plog_module->opt & KF_LOG_OPT_FILE))
            {
                if ((TmpLen + strlen(pfile) + strlen("[]")) > ((uint32_t)sizeof(kvLog_SendData) - 1u))
                {
                    break;
                }
                else
                {
                    /* Empty */
                }
                sprintf(&kvLog_SendData[strlen(kvLog_SendData)], "[%s]", pfile);
                TmpLen = strlen(kvLog_SendData);
            }
            else
            {
                /* Empty */
            }
        }
        else
        {
            /* Empty */
        }

        va_start((args), (format));
        if ((TmpLen + strlen(format) + strlen(args)) > ((uint32_t)sizeof(kvLog_SendData) - 1u))
        {
            va_end((args));
            break;
        }
        else
        {
            /* Empty */
        }

        vsprintf(&kvLog_SendData[strlen(kvLog_SendData)], format, args);
        va_end((args));
    } while (0);

    /* send data */

    kfLog_UartSend((uint8_t *)kvLog_SendData, (uint16_t)strlen(kvLog_SendData));
    /* PRQA S 0751,0488,0702,0432,0771 -- */
}

/**
 * @brief:Send a byte of data
 * @param in:Uartx-pointer to the USART memory structure
 * Data-send byte
 * @param out:None
 * @retval:None
 */
static uint8_t kfLog_UartSendData(USART_SFRmap *const Uartx, const uint8_t Data)
{
#if 0
    uint32_t LoopCounter;

#if 0
    LoopCounter = UART_TRANSMIT_TIMEOUT;
    while ((Usart_LL_GetTransmitBufEmptyFlag(Uartx) == 0u) && (LoopCounter != 0u))
    {
        LoopCounter--;
    }

    if (LoopCounter == 0u)
    {
        /* error */
        return 0u;
    }
#endif
    LoopCounter = UART_TRANSMIT_TIMEOUT;
    while ((Usart_LL_GetTransmitterEmptyFlag(Uartx) == 0u) && (LoopCounter != 0u))
    {
        LoopCounter--;
    }

    if (LoopCounter == 0u)
    {
        /* error */
        return 0u;
    }

    Usart_LL_SetTxBufferData(Uartx, Data);
     return 1u;
#else
    uint32_t LoopCounter;

    /*---------------- Set USART_TBUFR register ----------------*/
    LoopCounter = UART_TRANSMIT_TIMEOUT;
    while (LoopCounter != 0u)
    {
        LoopCounter--;
        if (0u != (Uartx->STR & USART_STR_TXEIF))
        {
            break;
        }
        else
        {
            /* Empty */
        }
    }

    if (LoopCounter == 0u)
    {
        /* error */
        return 0u;
    }
    else
    {
        /* Empty */
    }

    Uartx->TBUFR = Data;
    return 1u;
#endif
}

/**
 * @brief:send data and waits for completion
 * @param in:pSendData-send data point
 * SendLen-send data length
 * @param out:None
 * @retval:None
 */
void kfLog_UartSend(const uint8_t *const pSendData, const uint16_t SendLen)
{
    uint16_t Loop;

    if (((uint8_t *)0u == pSendData) || (0u == SendLen))
    {
        return;
    }
    else
    {
        /* Empty */
    }

    for (Loop = 0u; Loop < SendLen; Loop++)
    {
        kfLog_UartSendData(kvUart_UnitPtr[KFLOG_UART], pSendData[Loop]);
    }
}

/**
 * @brief:Reset and initialize the clock
 * @param in:None
 * @param out:None
 * @retval:None
 */
static void kfLog_ResetAndEnableClock(void)
{
    ;
}

/**
 * @brief:Pin configuration of uart. PA3 and PE7 are used by default. If other
 * pins are used, you can copy this function in the file used, without using a
 * weak definition
 * @param in:None
 * @param out:None
 * @retval:None
 */

void USART_Gpio_Config(GPIO_SFRmap *GPIOx, uint16_t GPIO_Pin, uint32_t Rmp)
{
    volatile uint16_t GpioPinTemp = GPIO_Pin, GPIO_PinNum = 0;
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.m_Mode      = GPIO_MODE_RMP;
    GPIO_InitStructure.m_OpenDrain = GPIO_POD_PP;
    GPIO_InitStructure.m_PullDown  = GPIO_NOPULL;
    GPIO_InitStructure.m_PullUp    = GPIO_NOPULL;
    GPIO_InitStructure.m_Speed     = GPIO_LOW_SPEED;
    GPIO_InitStructure.m_Pin       = GPIO_Pin;
    GPIO_Configuration(GPIOx, &GPIO_InitStructure);
    while ((GpioPinTemp & (0x1)) != 1)
    {
        GPIO_PinNum++;
        GpioPinTemp >>= 1;
    }
    GPIO_Pin_RMP_Config(GPIOx, GPIO_PinNum, Rmp);
}

void __attribute__((weak)) kfLog_UartPinInit(void) /* PRQA S 3408 */
{
#if 1
#define PE7_USART0_RX_AF3 GPIOE_SFR, GPIO_PIN_MASK_7, GPIO_RMP_AF3
#define PA3_USART0_TX_AF3 GPIOE_SFR, GPIO_PIN_MASK_8, GPIO_RMP_AF3
    USART_Gpio_Config(PA3_USART0_TX_AF3);
//    USART_Gpio_Config(PE7_USART0_RX_AF3);
#else
    GPIO_Write_Mode_Bits(GPIOA_SFR, GPIO_PIN_MASK_0, GPIO_MODE_RMP);
    GPIO_Write_Mode_Bits(GPIOA_SFR, GPIO_PIN_MASK_1, GPIO_MODE_RMP);

    /* Configuring Low Power Register */
    BKP_Write_And_Read_Enable(TRUE);

    SFR_SET_BIT_ASM(PM_CTL2, PM_CTL2_USART0LPEN_POS);
    SFR_SET_BIT_ASM(PM_CTL2, PM_CTL2_USART0CLKLPEN_POS);
    SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_PHERIIOSEL_POS);
    SFR_SET_BIT_ASM(PM_CTL0, PM_CTL2_GPIOALPEN_POS);

    BKP_Write_And_Read_Enable(FALSE);
#endif
}

/**
 * @brief:Log output initialization
 * 1.The default value is UART0. If you need to change the value, change the
 * KFLOG_UART
 * 2.The default baud rate is 230400
 * 3.8bits Data , 1 stop bit, no flow control, Odd parity
 * @param in:None
 * @param out:None
 * @retval:None
 */
void kfLog_Init(void)
{
    uint16_t RateInteger     = 0u;
    uint16_t RateMolecular   = 1u;
    uint16_t RateDenominator = 0u;

    uint32_t          SystemClockTmp  = 0u;
    uint32_t          UartBaudRateTmp = 0u;
    uint32_t          Coefficient     = 0u;
    USART_SFRmap     *pUartx          = NULL;
    USART_InitTypeDef USART_InitStructure;

    /* PRQA S 2742 ++ */
    if (KFLOG_UART > UART15_INDEX)
    {
        return;
    }
    else
    {
        /* Empty */
    }

    if ((KFLOG_UART_FREQUENCY > 921600u) || (KFLOG_UART_FREQUENCY < 1200u))
    {
        return;
    }
    else
    {
        /* Empty */
    }
    /* PRQA S 2742 -- */

    pUartx = kvUart_UnitPtr[KFLOG_UART];

    /* reset uart and enable clock */
    kfLog_ResetAndEnableClock();

    /* Set Usart To Async Mode */
    USART_Struct_Init(&USART_InitStructure);
    USART_InitStructure.m_Mode          = USART_MODE_FULLDUPLEXASY;
    USART_InitStructure.m_TransferDir   = USART_DIRECTION_FULL_DUPLEX;
    USART_InitStructure.m_WordLength    = USART_WORDLENGTH_8B;
    USART_InitStructure.m_StopBits      = USART_STOPBITS_1;
    USART_InitStructure.m_BaudRateBRCKS = (uint16_t)USART_CLK_SCLK;
    /** Use 16M clock as an example to list the following baud rates
     * 	4800    z:208    x:0    y:0
     * 	9600    z:104    x:0    y:0
     * 	19200   z:52     x:0    y:0
     * 	115200  z:8      x:1    y:13
     */
    /* Baud rate conversion */
    SystemClockTmp  = KFLOG_UART_CLOCK / 100u;
    UartBaudRateTmp = KFLOG_UART_FREQUENCY / 100u;

    RateInteger = (uint16_t)(SystemClockTmp / (16u * UartBaudRateTmp));
    Coefficient = ((SystemClockTmp * 1000u) / (16u * UartBaudRateTmp)) / (RateInteger);

    if (Coefficient <= 1000u)
    {
        /* When the bit is 0, the decimal baud rate generator does not affect
         * the baud rate */
        RateMolecular   = 0u;
        RateDenominator = 0u;
    }
    else
    {
        RateDenominator = (RateMolecular * 1000u) / ((uint16_t)(Coefficient - 1000u));
        /* Numerator and denominator register, maximum 4bits, otherwise set to 0
         */
        if (RateDenominator > 15u)
        {
            /* When the bit is 0, the decimal baud rate generator does not
             * affect the baud rate */
            RateMolecular   = 0u;
            RateDenominator = 0u;
        }
        else
        {
            /* Empty */
        }
    }

    /* Integer part z, get value range is 0 ~ 0xFFFF */
    USART_InitStructure.m_BaudRateInteger = RateInteger;
    /* Numerator part x, get value range is 0 ~ 0x0f */
    USART_InitStructure.m_BaudRateNumerator = RateMolecular;
    /* Denominator part y, get value range is 0 ~ 0x0f */
    USART_InitStructure.m_BaudRateDenominator = RateDenominator;
    /* Reset and enable USARTx */
    USART_Reset(pUartx);
    USART_Configuration(pUartx, &USART_InitStructure);
    USART_Passageway_Select_Config(pUartx, USART_U7816R_PASSAGEWAY_TX0);
    /* Enable UART moudle */
    USART_RESHD_Enable(pUartx, TRUE);
    USART_Transmit_Data_Enable(pUartx, TRUE);
    USART_Cmd(pUartx, TRUE);

    /* uart pin init */
    kfLog_UartPinInit();

    kvUart_InitStatus = 1u;
}
#endif
