#ifndef _DRV_LIN_H_
#define _DRV_LIN_H_

#include  "Common.h"
#include "ecual_uart.h"

typedef enum
{
	LIN_DEV0=HW_UART_0,
	LIN_DEV1,
	LIN_DEV2,
    eLIN_CH_MAX
}LinChlIdx_t;


#define MAX_LIN_DATA_LEN      		(0x08)      // Max bytes lin frame data

typedef enum
{
    eLIN_DataReq = 0,		//master transmit header
    eLIN_DataSend   		//master transmit header + data
}LinTransmitType_t;

typedef enum
{
    eLIN_Enhanced = 0,
    eLIN_Classic
}LinCheckSumType_t;

typedef struct
{
	INT8U				u8PID;						/* Protected ID*/
	LinTransmitType_t 	eTransmitType;				/* TransmitType */
	LinCheckSumType_t 	eCheckSumType;				/* check sum Type*/
	INT8U				u8DataLen;					/* Frame lenth */
	INT8U				au8Data[MAX_LIN_DATA_LEN];	/* Data Buffer*/
}LinFrame_t;


typedef	enum
{
	eLIN_IDLE = 0,        			 			/* Idel status                      */
	eLIN_TRANSBUSY,								/* During the transmission */
	eLIN_RECVSUCCESS,      	 				    /* Reception data Success */
	eLIN_ERROR									/* error status */
}LinBusStatus_t;

typedef	struct
{
	LinFrame_t stFrame;
	LinBusStatus_t eStatus;
	INT8U u8LINBusBusyTimeOutCnt;
}LinInfo_t;


typedef enum
{
	eLinBaudRate_9600bps = 0,
	eLinBaudRate_19200bps,
	eLinBaudRate_10417bps,
    eLinBaudRate_Max
}LinBaudRate_t;


typedef struct _HAL_LIN_DEV_COMM_T
{
	LinChlIdx_t LinUartIndex;
	LinBaudRate_t LinBaudRate;
}LinDeviceComm_t;


typedef void (*Lincallback_t)(LinChlIdx_t eLinChan,LinInfo_t * LinInfo);

extern uint8_t Drv_LinGetParityValue(uint32_t u32id);
extern void Mcal_LinInit(LinDeviceComm_t* LinCfg,Lincallback_t LincallbackFunc);
extern void Mcal_LinDeInit(LinDeviceComm_t* LinCfg);
extern int Drv_LinMasterSend(LinChlIdx_t eLinChan, const LinFrame_t *stCommunicationFrame);
extern void Drv_LinIRQHandler(LinChlIdx_t eLinChan);

#endif 

