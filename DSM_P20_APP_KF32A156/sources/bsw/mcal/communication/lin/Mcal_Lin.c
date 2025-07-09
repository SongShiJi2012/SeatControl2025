/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:              Drv_Lin.c
** Created By:              chenzibo
** Created date:            2022.12.27
** Version:                 V1.0
** Descriptions:           lin的初始化，发送接收
**
**------------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
**************************************************************************************************/

#include <Mcal_Lin.h>
#include "lpuart_driver.h"

typedef struct
{
	uint8_t	Len;						/* DataLen*/
	uint8_t	Data[MAX_LIN_DATA_LEN+3];	/* Data Buffer*/
	uint8_t	Depth;
}LinDataQueue_t;

static LPUART_Type * const s_LinUartBase[LPUART_INSTANCE_COUNT] = LPUART_BASE_PTRS;
static const IRQn_Type s_LinRxTxIrqId[LPUART_INSTANCE_COUNT] = LPUART_RX_TX_IRQS;

static Lincallback_t s_Lincallback[LPUART_INSTANCE_COUNT] = {NULL};

static LinInfo_t s_LinInfoRxData[LPUART_INSTANCE_COUNT];
static LinInfo_t s_LinInfoTxData[LPUART_INSTANCE_COUNT];
static LinDataQueue_t s_LinTxDataQueue[LPUART_INSTANCE_COUNT];
static LinDataQueue_t s_LinRxDataQueue[LPUART_INSTANCE_COUNT];
/**
 *  @brief :Use LIN2.0 standard check, calculate protection section data
 *  @param in :u32id Input ID data to be processed
 *  @param out :None
 *  @retval :None
 *
 */

/***********************************************************************************************
 * @function name:  uint8_t Drv_LinGetParityValue(uint32_t u32id)
 * @description:     保护ID计算公式   LIN2.0
    * u32id Input ID data to be processed
 * @input parameters:      u32id
 * @output parameters:     void
 * @return:         uint8_t
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/

uint8_t Drv_LinGetParityValue(uint32_t u32id)
{
	uint32_t u32Res = 0;
	uint32_t ID[6];
	uint32_t p_Bit[2];
	uint32_t mask = 0;

	/* Store ID in ID[0:5] */
	for (mask = 0; mask < 6; mask++)
	{
		ID[mask] = (u32id & (1 << mask)) >> mask;
	}
	/* ID6 (p_Bit[0]) is the odd parity of ID0, ID1, ID2, and ID4
		ID7(p_Bit[1]) is the even parity of ID1, ID3, ID4, ID5 */
	p_Bit[0] = (ID[0] + ID[1] + ID[2] + ID[4]) % 2;
	p_Bit[1] = (!((ID[1] + ID[3] + ID[4] + ID[5]) % 2));
	/* Get the ID domain value u32Res
	(the first 6 bits are ID, and the upper two bits are parity bits) */
	u32Res = u32id + (p_Bit[0] << 6) + (p_Bit[1] << 7);
	/* Return ID filed value */
	return u32Res;
}

/***********************************************************************************************
 * @function name: static uint8_t Drv_LinGetCheckSumValue(uint8_t PctID,const uint8_t *Databuf, uint32_t length, LinCheckSumType_t Type)
 * @description:    校验
    * Use LIN2.0 standard check, calculate the test value of LIN data
 * @input parameters:      PctID 	Data of protection segment ID
 *			   Databuf	Pointer of the data to be sent
 *			   Length	The length of the data to be sent
 *			   Type
 * @output parameters:     void
 * @return:         uint8_t
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/
static uint8_t Drv_LinGetCheckSumValue(uint8_t PctID,const uint8_t *Databuf, uint32_t length, LinCheckSumType_t Type)
{
	uint16_t check_sum = 0;
	uint8_t i = 0;

	if(eLIN_Enhanced == Type)
	{
		check_sum = PctID;
	}

	for (i = 0; i < length; i++)
	{
		check_sum += Databuf[i];
		if (check_sum > 0xFF)
		{
			check_sum -= 255;
		}
	}

	return (0xFF - check_sum);
}
void Mcal_LinDeInit(LinDeviceComm_t* LinCfg)
{
	uint8_t Index = LinCfg->LinUartIndex;
	USART_SFRmap *USARTx = s_LinUartBase[Index];
	USART_Deinit(USARTx);
}
/***********************************************************************************************
 * @function name: void Mcal_LinInit(LinDeviceComm_t* LinCfg,Lincallback_t LincallbackFunc)
 * @description:     初始化LIN
    * Use 16M clock as an example to list the following baud rates
	 * 	4800    z:208    x:0    y:0
	 * 	9600    z:104    x:0    y:0
	 * 	19200   z:52     x:0    y:0
	 * 	115200  z:8      x:1    y:13
 * @input parameters:      LinCfg
 * 						   LincallbackFunc
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/
void Mcal_LinInit(LinDeviceComm_t* LinCfg,Lincallback_t LincallbackFunc)
{
	uint8_t Index = LinCfg->LinUartIndex;
	USART_InitTypeDef USART_InitStructure;
	USART_SFRmap *USARTx = s_LinUartBase[Index];
	uint16_t Integer = 0;
	uint8_t Numerator = 0;
	uint8_t Denominator = 0;

	if(eLinBaudRate_9600bps == LinCfg->LinBaudRate)
	{
		 Integer = 104;
		 Numerator = 0;
		 Denominator = 0;
	}
	else if(eLinBaudRate_19200bps == LinCfg->LinBaudRate)
	{
		 Integer = 52;
		 Numerator = 0;
		 Denominator = 0;
	}
	else if(eLinBaudRate_10417bps == LinCfg->LinBaudRate)
	{
		 Integer = 95;
		 Numerator = 9;
		 Denominator = 10;
	}
	else /*115200*/
	{
		Integer = 8;
		Numerator = 1;
		Denominator = 13;

	}

	/* Reset and enable USARTx */
	USART_Reset(USARTx);
	/* configure USARTx to LIN mode */
	USART_Struct_Init(&USART_InitStructure);
	USART_InitStructure.m_Mode=USART_MODE_FULLDUPLEXASY;
	USART_InitStructure.m_TransferDir=USART_DIRECTION_FULL_DUPLEX;
	USART_InitStructure.m_WordLength=USART_WORDLENGTH_8B;
	USART_InitStructure.m_StopBits=USART_STOPBITS_1;
	USART_InitStructure.m_BaudRateBRCKS=USART_CLK_HFCLK;
	USART_InitStructure.m_BRAutoDetect=USART_ABRDEN_OFF;

	/* Integer part z, get value range is 0 ~ 0xFFFF */
	USART_InitStructure.m_BaudRateInteger=Integer;
	/* Numerator part x, get value range is 0 ~ 0x0f */
	USART_InitStructure.m_BaudRateNumerator=Numerator;
	/* Denominator part y, get value range is 0 ~ 0x0f */
	USART_InitStructure.m_BaudRateDenominator=Denominator;
	USART_Configuration(USARTx,&USART_InitStructure);
	/* Enable receive interrupt */
	//USART_RDR_INT_Enable(USARTx,TRUE);
	/* Enable LIN moudle */
	USART_RESHD_Enable (USARTx, TRUE);
	USART_Cmd(USARTx,TRUE);

	INT_Interrupt_Enable(s_LinRxTxIrqId[Index], TRUE);//串口外设中断使能
//	INT_Interrupt_Priority_Config(s_LinRxTxIrqId[Index], 7, 0);
	INT_Interrupt_Priority_Config(s_LinRxTxIrqId[Index], 1, 0);

	s_Lincallback[Index] = LincallbackFunc;
	memset(s_LinInfoRxData,0,sizeof(s_LinInfoRxData));
	memset(s_LinInfoTxData,0,sizeof(s_LinInfoTxData));
}

/***********************************************************************************************
 * @function name:static void Drv_LinSend(LinChlIdx_t Index, uint8_t PID,const uint8_t* Databuf, uint32_t Length,uint8_t CheckSum)
 * @description:    发送数据
    * Use LIN2.0 standard check, calculate the test value of LIN data
 * @input parameters:
 * 			   Index
 * 			   PID 	Data of protection segment ID
 *			   Databuf	Pointer of the data to be sent
 *			   Length	The length of the data to be sent
 *			   CheckSum  check value
 * @output parameters:     void
 * @return:         uint8_t
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/
static void Drv_LinSend(LinChlIdx_t Index, LinFrame_t* LinTxFrameBuff)
{
	//uint8_t ProtectID = GetParityValue(SlaveID);
	uint8_t CheckVaule = 0;
	uint8_t PID = LinTxFrameBuff->u8PID;
	uint8_t Length = LinTxFrameBuff->u8DataLen;
	uint8_t* Databuf = LinTxFrameBuff->au8Data;
	USART_SFRmap* USARTx = s_LinUartBase[Index];
	LinDataQueue_t* pTxDataQueue = &s_LinTxDataQueue[Index];

	CheckVaule = Drv_LinGetCheckSumValue(PID, Databuf, Length, LinTxFrameBuff->eCheckSumType);

	pTxDataQueue->Data[0] = 0x55;/*同步符*/
	pTxDataQueue->Data[1] = PID;
	pTxDataQueue->Depth = 0;
	if(Length > 0 && LinTxFrameBuff->eTransmitType == eLIN_DataSend)
	{
		pTxDataQueue->Len = Length + 3;
		memcpy(&pTxDataQueue->Data[2],Databuf,Length);
		pTxDataQueue->Data[Length+2] = CheckVaule;
	}
	else
	{
		pTxDataQueue->Len = 2;
	}

	 memset(&s_LinInfoRxData[Index],0,sizeof(LinInfo_t));
	 memset(&s_LinRxDataQueue[Index],0,sizeof(LinDataQueue_t));

	USART_Transmit_Data_Enable(USARTx, FALSE);
	USART_Send_Blank_Enable(USARTx, TRUE); /*间隔场*/
	USART_Transmit_Data_Enable(USARTx, TRUE);

	USART_RDR_INT_Enable(USARTx,FALSE);
	USART_TXE_INT_Enable(USARTx, TRUE);
}

/***********************************************************************************************
 * @function name: int Drv_LinMasterSend(LinChlIdx_t eLinChan, const LinFrame_t *pLinDataFrame)
 * @description:    主机发送数据
 * @input parameters:
 * 			   eLinChan
 * 			   pLinDataFrame
 * @output parameters:     void
 * @return:         int
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/
int Drv_LinMasterSend(LinChlIdx_t eLinChan, const LinFrame_t *pLinDataFrame)
{

	int ret = 0;
	LinInfo_t* pLinInfoTxBuff =  &s_LinInfoTxData[eLinChan];

	if(eLinChan >= eLIN_CH_MAX)
	{
		return -1;
	}

	if(pLinInfoTxBuff->eStatus != eLIN_IDLE)
	{
		return -1;
	}

	pLinInfoTxBuff->eStatus= eLIN_TRANSBUSY;

    memcpy(&pLinInfoTxBuff->stFrame,pLinDataFrame,sizeof(LinFrame_t));

	Drv_LinSend(eLinChan, &pLinInfoTxBuff->stFrame);

	return ret;
}

/***********************************************************************************************
 * @function name: void Drv_LinIRQHandler(LinChlIdx_t eLinChan)
 * @description:    中断服务函数
 * @input parameters:
 * 			   eLinChan
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-12-16 czb
 ***********************************************************************************************/
void Drv_LinIRQHandler(LinChlIdx_t eLinChan)
{
	volatile uint8_t Rev_Temp;

	USART_SFRmap* USARTx = s_LinUartBase[eLinChan];
	LinFrame_t* pLinFrameBuff = &s_LinInfoRxData[eLinChan].stFrame;
    //Lincallback_t* RXcallback = &Lincallback[eLinChan];
	LinDataQueue_t* pTxDataQueue = &s_LinTxDataQueue[eLinChan];
	LinInfo_t* pLinInfoTxBuff =  &s_LinInfoTxData[eLinChan];
	LinDataQueue_t* pLinInfoRxBuff =  &s_LinRxDataQueue[eLinChan];

	if (USART_Get_Receive_BUFR_Ready_Flag(USARTx))
	{
		/* Read data buffer, and clear the receive flag */
		Rev_Temp = USART_ReceiveData(USARTx);

		/*第0个是隔离符，第1个是同步，第2个PID，之后才是数据*/
		if(pLinInfoRxBuff->Len < (MAX_LIN_DATA_LEN+3))
		{
			pLinInfoRxBuff->Data[pLinInfoRxBuff->Len] = Rev_Temp;
			pLinInfoRxBuff->Len++;
		}
		else
		{
			//pLinFrameBuff->eCheckSumType = Rev_Temp;
			s_LinInfoRxData[eLinChan].eStatus = eLIN_RECVSUCCESS;
			pLinFrameBuff->u8PID = pLinInfoRxBuff->Data[2];
			pLinFrameBuff->u8DataLen = pLinInfoRxBuff->Len - 3;  /*理论上长度与PID的bit4和bit5有关系(00/10:2 01:4,11:8)，实际长度都是8*/
			memcpy(pLinFrameBuff->au8Data,&pLinInfoRxBuff->Data[3],pLinFrameBuff->u8DataLen);
			if(s_Lincallback[eLinChan] != NULL)
			{
				s_Lincallback[eLinChan](eLinChan,&s_LinInfoRxData[eLinChan]);
			}
		}


		/* Process some things after receiving the data.
			It will receive the data sent by the current node */
	}
	else if(USART_Get_Transmitter_Empty_Flag(USARTx))
	{
		if(pTxDataQueue->Len > 0)
		{
			USARTx->TBUFR = pTxDataQueue->Data[pTxDataQueue->Depth];
			pTxDataQueue->Len--;
			pTxDataQueue->Depth++;
		}
		else
		{

			 USART_TXE_INT_Enable(USARTx, FALSE);
			 USART_RDR_INT_Enable(USARTx,TRUE);
			 pLinInfoTxBuff->eStatus = eLIN_IDLE;
		}

	}
}
