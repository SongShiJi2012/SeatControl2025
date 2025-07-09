/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               UJA1078.c
** Last modified Date:      2019.3.12
** Last Version:            V1.1.0
** Description:
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2019.3.12
** Version:                 V1.0.0
** Descriptions:
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/

/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "UJA1078.h"
#include "kf32a156.h"
#include "system_Init.h"


/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/



/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/
/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/
ST_SBC_UJA1078Info stgSBC_UJA1078Info;

/// Global software mark which indicates if the software is running properly.
/**
*   - 0 Software will reset when WatchdogTrigger() is called
*   - 1 Software is ok no reset required
*/
volatile INT8U WatchdogCheckMark1;

/// Global software mark which indicates if the software is running properly.
/**
*   - 0 Software will reset when WatchdogTrigger() is called
*   - 1 Software is ok no reset required
*/
volatile INT8U WatchdogCheckMark2;

/// This variable indicates if the watchdog is running
/** 该变量示意看门狗是否运行
*   - 0 Watchdog disabled by hardware
*   - 1 Watchdog enabled by hardware
*/
volatile INT8U WatchdogEnabled;

/// This variable indicates if a interrupt is pending
/**
*   - 0 Watchdog disabled by hardware
*   - 1 Watchdog enabled by hardware
*/
volatile INT8U PendingInterrupts;

/// This variable indicates if a V2 undervoltage is present
/**
*   - 0 V2 is OK no undervoltage
*   - 1 V2 is currently below 4.5V
*/
volatile INT8U V2undervoltage;

/// This variable indicates if a abort of goto sleep or stop take place
/**
*   - 0 everything fine
*   - 1 Abort of goto sleep or stop requested
*/
volatile INT8U AbortLowPowerMode;

/// This variable indicates if the applications performs cyclic wake ups
/**
*   - 0 No cyclic wake ups
*   - 1 Cyclic wake up take place triggered by the Cyclic Interrupt
*/
volatile INT8U CyclicWake;

/// This variable indicates if the applications was in stop mode
/**
*   - 0 No stop mode
*   - 1 microcontroller was in stop mode
*/
volatile INT8U Stop;
/*
**********************************************************************************************************
					FUNCTIONS
**********************************************************************************************************
*/

/*-------------------------------------------------------------------------
* Function Name : UJA1078_Init
* Description   : UJA1078初始化
* Date          : 2019/March/16
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
INT8U UJA1078_Init(void)
{
	INT8U status = 0;
	INT16U UJA107x_MCR, UJA107x_ICR;

	/*
	**	初始化 MCR 寄存器
	*/
	UJA107x_MCR = SBC_UJA107x_MCR_INIT;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	UJA107x_MCR |=	MCR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	if(SBC_UJA107x_MCR_INIT != (UJA107x_MCR & MCR_WRITE_MASK))
	{
		status = 0;
	}
	else
	{
		status = 1;
	}
	/*
	**	初始化 ICR 寄存器
	*/
	UJA107x_ICR = SBC_UJA107x_ICR_LOWPOWER;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	UJA107x_ICR |=	ICR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	if(SBC_UJA107x_ICR_LOWPOWER != (UJA107x_ICR & ICR_WRITE_MASK))
	{
		status = 0;
	}
	else
	{
		status = 1;
	}

	return status;
}


/*-------------------------------------------------------------------------
* Function Name : UJA1078_V1UI_InterruptService
* Description   : 该功能执行在V1欠压情况下需要的相关动作。它检查内存和全局变量，因为它们不再可靠，并执行更新
此外，当设备处于循环休眠或停止模式时，它请求转换到正常模式。
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_V1UI_InterruptService(void)
{
	INT16U UJA107x_ISR;
	//(void) CheckMemoryAndApplication();

	if(CyclicWake == TRUE || Stop == TRUE)
	{
		// Normal
		CyclicWake = TRUE;
	}
	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_V1;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);

}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_V2UI_InterruptService
* Description   : 该功能执行V2欠压情况下所需的相关动作
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_V2UI_InterruptService(void)
{
	INT16U UJA107x_ISR;

	//V2polling();

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_V2;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_LWI1_InterruptService
* Description   : 此功能执行在LWI1情况下需要的相关动作。LIN1唤醒中断
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_LWI1_InterruptService(void)
{
	INT16U UJA107x_ISR;

	if(CyclicWake == TRUE || Stop == TRUE)
	{
		// Normal
		CyclicWake = FALSE;
	}
	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_LWI1;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_LWI2_InterruptService
* Description   : LIN2唤醒中断
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_LWI2_InterruptService(void)
{
	INT16U UJA107x_ISR;

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_LWI2;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_CI_InterruptService
* Description   :
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_CI_InterruptService(void)
{
	INT16U UJA107x_ISR;

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_CI;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_WI1_InterruptService
* Description   : 唤醒1中断
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_WI1_InterruptService(void)
{
	INT16U UJA107x_WDSR, UJA107x_ISR;

	UJA107x_WDSR = WDSR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);

	if((UJA107x_WDSR & WDSR_WLS1_MASK) == WDSR_WLS1_MASK)
	{
		// rising edge
	}
	else
	{
		// falling edge
	}

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_WT1;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_WI2_InterruptService
* Description   : 唤醒2
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_WI2_InterruptService(void)
{
	INT16U UJA107x_WDSR, UJA107x_ISR;

	UJA107x_WDSR = WDSR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);

	if((UJA107x_WDSR & WDSR_WLS2_MASK) == WDSR_WLS2_MASK)
	{
		// rising edge
	}
	else
	{
		// falling edge
	}

	if(CyclicWake == TRUE || Stop == TRUE)
	{
		// Normal
		CyclicWake = FALSE;
	}

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_WT2;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_CWI_InterruptService
* Description   : CAN唤醒
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_CWI_InterruptService(void)
{
	INT16U UJA107x_ISR;

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_CWI;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_POSI_InterruptService
* Description   : 上电唤醒
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_POSI_InterruptService(void)
{
	INT16U UJA107x_ISR;

	// Clear Interrupt
	UJA107x_ISR = SBC_UJA107x_ISR_INT_CLR_POSI;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_TransceiverControl
* Description   : CAN使能
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_TransceiverControl(void)
{
	INT16U UJA107x_WDSR, UJA107x_ICR;
	UJA107x_ICR = SBC_UJA107x_ICR_NORMAL;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);

	UJA107x_WDSR = WDSR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);
	if((UJA107x_WDSR & WDSR_V2S_MASK) == WDSR_V2S_MASK)
	{
		// V2 still low
		//printf("V2 undervoltage\n");
		V2undervoltage = 1;
	}
	else
	{
		// V2 is OK again
		V2undervoltage = 0;
		//ResumeCAN_TX();
	}
}



/*-------------------------------------------------------------------------
* Function Name : GetDeviceID
* Description   :
* Date          : 2019/March/23
* Parameter     :
* Return Code   : 返回DeviceID
* Author        :
-------------------------------------------------------------------------*/
EN_SBC_UJA107x_TYPE UJA1078_GetDeviceID(void)
{
	INT16U UJA107x_ICR;
	EN_SBC_UJA107x_TYPE Device = NXP_MAX;
	// Write Device ID pattern
	UJA107x_ICR = DeviceIdPattern;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);


	// Read back Device ID pattern and restore previous ICR content
	UJA107x_ICR = ICR_ADDRESS_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);

	if(UJA107x_ICR == UJA1078_DeviceIdPattern)
	{
		Device = NXP_UJA1078;
	}
	else if(UJA107x_ICR == UJA1075_DeviceIdPattern)
	{
		Device = NXP_UJA1075;
	}
	else if(UJA107x_ICR == UJA1076_DeviceIdPattern)
	{
		Device = NXP_UJA1076;
	}
	else if(UJA107x_ICR == UJA1079_DeviceIdPattern)
	{
		Device = NXP_UJA1079;
	}

	return Device;
}


/*-------------------------------------------------------------------------
* Function Name : UJA1078_SoftwareReset
* Description   : SBC软件复位
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_SoftwareReset(void)
{
	INT16U UJA107x_WDSR;
	UJA107x_WDSR = SBC_UJA107x_WDSR_SWREST;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);
}
/*-------------------------------------------------------------------------
* Function Name : UJA1078_AbortLowPowerHandler
* Description   : 在向低功耗模式转换期间触发中断时调用此功能。它确保实例应用程序再次进入正常模式，
*				  并执行UJA107x寄存器映射的相关正常模式配置。
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_AbortLowPowerHandler(void)
{
	INT16U UJA107x_MCR, UJA107x_ICR;

	// Disable Wake-up config, enable TRX
	UJA107x_ICR = ICR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);


	if((UJA107x_ICR & ICR_WRITE_MASK) != SBC_UJA107x_ICR_NORMAL)
	{
		UJA107x_ICR = SBC_UJA107x_ICR_NORMAL;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);

	}
	// Enter Normal mode again
	UJA107x_MCR = MCR_READ_MASK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);

	if((UJA107x_MCR & MCR_WRITE_MASK) != SBC_UJA107x_MCR_NORMAL)
	{
		// Device not in Normal mode or WBC = 1;
		UJA107x_MCR = SBC_UJA107x_MCR_NORMAL;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	}
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_InterruptHandler
* Description   :
*	-  V1UI_InterruptService() related to \link #ISR_V1UI_MASK V1 Undervoltage Interrupt (V1UI) \endlink
*	-  V2UI_InterruptService() related to \link #ISR_V2UI_MASK V2 Undervoltage Interrupt (V2UI) \endlink
*	-  LWI1_InterruptService() related to \link #ISR_LWI1_MASK LIN1 Wake Interrupt (LWI1) \endlink
*	-  LWI2_InterruptService() related to \link #ISR_LWI1_MASK LIN2 Wake Interrupt (LWI2) \endlink
*	-  WI1_InterruptService() related to \link #ISR_WI1_MASK WAKE1 Interrupt (WI1) \endlink
*	-  WI2_InterruptService() related to \link #ISR_WI2_MASK WAKE1 Interrupt (WI2) \endlink
*	-  CI_InterruptService() related to \link #ISR_CI_MASK Cyclic Interrupt (CI) \endlink
*	-  CWI_InterruptService() related to \link #ISR_CWI_MASK CAN Wake Interrupt (CWI) \endlink
*
*	On the other hand this function also does the clean up after are failed transition to low power mode
*	by calling AbortLowPowerHandler().
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_InterruptHandler(void)
{
	INT16U UJA107x_ISR;
	if(AbortLowPowerMode == 1 || PendingInterrupts == 1)
	{
		if(AbortLowPowerMode == 1)
		{
			AbortLowPowerMode = 0;
			UJA1078_AbortLowPowerHandler();
		}
		UJA107x_ISR = SBC_UJA107x_ISR_CHECK;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);

		if((UJA107x_ISR & ISR_V1UI_MASK) == ISR_V1UI_MASK)
		{
			UJA1078_V1UI_InterruptService();
		}
		if((UJA107x_ISR & ISR_V2UI_MASK) == ISR_V2UI_MASK)
		{
			UJA1078_V2UI_InterruptService();
		}
		if((UJA107x_ISR & ISR_LWI1_MASK) == ISR_LWI1_MASK)
		{
			UJA1078_LWI1_InterruptService();
		}
		if((UJA107x_ISR & ISR_LWI2_MASK) == ISR_LWI2_MASK)
		{
			UJA1078_LWI2_InterruptService();
		}
		if((UJA107x_ISR & ISR_CI_MASK) == ISR_CI_MASK)
		{
			UJA1078_CI_InterruptService();
		}
		if((UJA107x_ISR & ISR_WI1_MASK) == ISR_WI1_MASK)
		{
			UJA1078_WI1_InterruptService();
		}
		if((UJA107x_ISR & ISR_WI2_MASK) == ISR_WI2_MASK)
		{
			UJA1078_WI2_InterruptService();
		}
		if((UJA107x_ISR & ISR_CWI_MASK) == ISR_CWI_MASK)
		{
			UJA1078_CWI_InterruptService();
		}

		UJA107x_ISR = SBC_UJA107x_ISR_CHECK;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);

		if(UJA107x_ISR == NoInterruptPending)
		{
			PendingInterrupts = 0;
		}
		else
		{
			// Schedule Interrupt handling
			PendingInterrupts = 1;
		}
	}
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_SleepMode
* Description   : SBC Sleep 模式配置
* Date          : 2019/March/16
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_SleepMode(void)
{
	INT16U UJA107x_ICR,	UJA107x_ISR, UJA107x_MCR;
	UJA107x_ICR = SBC_UJA107x_ICR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	// Check if wake-up sources (CAN and WAKE1/2) are enabled
	if(UJA107x_ICR != SBC_UJA107x_ICR_LOWPOWER)
	{
		//配置唤醒源
		UJA107x_ICR = SBC_UJA107x_ICR_LOWPOWER;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);

	}

	// Check if interrupts pending
	UJA107x_ISR = SBC_UJA107x_ISR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
	if(UJA107x_ISR != NoInterruptPending)
	{
		// Abort Goto Sleep
		AbortLowPowerMode = TRUE;
	}
	else
	{
		// Enter sleep mode
		UJA107x_MCR =  SBC_UJA107x_MCR_SLEEP;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	}
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_StopMode
* Description   : SBC Stop 模式配置
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_StopMode(void)
{
	INT16U UJA107x_ICR, UJA107x_ISR, UJA107x_WDSR, UJA107x_MCR;
	// Change to Standby Mode
	UJA107x_MCR = SBC_UJA107x_MCR_STANDBY;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);

	UJA107x_ICR = SBC_UJA107x_ICR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	// Check if wake-up sources (CAN and WAKE1/2) are enabled
	if(UJA107x_ICR != SBC_UJA107x_ICR_LOWPOWER)
	{
		UJA107x_ICR = SBC_UJA107x_ICR_LOWPOWER;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);

	}

	// Check if interrupts pending
	UJA107x_ISR = SBC_UJA107x_ISR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
	if(UJA107x_ISR != NoInterruptPending)
	{
		// Abort Goto stop
		AbortLowPowerMode = TRUE;
	}
	else
	{
		UJA107x_WDSR = WDSR_WMC_MASK; // Disable WD
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);
		Stop = TRUE;
	}
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_CyclicWakeUpSBC
* Description   :
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_CyclicWakeUpSBC(void)
{
	INT16U UJA107x_ICR, UJA107x_ISR, UJA107x_WDSR, UJA107x_MCR;
	// Change to Standby Mode
	UJA107x_MCR = SBC_UJA107x_MCR_STANDBY;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);

	UJA107x_ICR = SBC_UJA107x_ICR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	// Check if wake-up sources (CAN and WAKE1/2) are enabled
	if(UJA107x_ICR != SBC_UJA107x_ICR_LOWPOWER)
	{
		UJA107x_ICR = SBC_UJA107x_ICR_LOWPOWER;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ICR);
	}

	// Check if interrupts pending
	UJA107x_ISR =  SBC_UJA107x_ISR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_ISR);
	if(UJA107x_ISR != NoInterruptPending)
	{
		// Abort Goto Sleep
		AbortLowPowerMode = TRUE;
	}
	else
	{
		UJA107x_WDSR = WDSR_NWP_MASK; // Enable WD, 4s period
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);
		if((UJA107x_WDSR & WDSR_WOS_MASK) == 0)
		{
			// Watchdog enabled by hardware
			CyclicWake = TRUE;
		}
		else
		{
			// Watchdog disabled -> dead lock
			AbortLowPowerMode = TRUE;
		}
	}
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_EnterNormalOperation
* Description   : 进入正常模式
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_EnterNormalOperation(void)
{
	INT16U UJA107x_MCR, UJA107x_WDSR;
	// Change to normal mode
	/*配置说明：
	  1.在正常模式下即使不打开V2，CAN物理层处于活动模式。（打开V2即可接收报文）
	  2.无升级请求关闭V2原因：如果在BOOT打开V2，此时有CAN报文在boot中接收，由于唤醒检测在APP中，这样导致CAN报文无法触发唤醒MCU*/
	UJA107x_MCR = SBC_UJA107x_MCR_NORMAL_DisableV2;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);


	//read back to check whether  enter normal mode
	UJA107x_WDSR = SBC_UJA107x_WDSR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);

	// Enable Transceiver
	UJA1078_TransceiverControl();
}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_EnterNormalOperation
* Description   : 打开V2
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_OpenV2(void)
{
    INT16U UJA107x_MCR;
    UJA107x_MCR = SBC_UJA107x_MCR_NORMAL_EnableV2;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
}



/*-------------------------------------------------------------------------
* Function Name : UJA1078_LimpHomeHandling
* Description   : Limphome操作
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_LimpHomeHandling(void)
{
	INT16U UJA107x_MCR;
	UJA107x_MCR = SBC_UJA107x_MCR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	// clear LHC or LHWC if set
	if(((UJA107x_MCR & MCR_LHWC_MASK) == MCR_LHWC_MASK ) || ((UJA107x_MCR & MCR_LHC_MASK) == MCR_LHC_MASK))
	{
		UJA107x_MCR = SBC_UJA107x_MCR_INIT;
		LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_MCR);
	}
}


/*-------------------------------------------------------------------------
* Function Name : UJA1078_ResetAndWakeUpDetection
* Description   : 复位和唤醒源检测
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_ResetAndWakeUpDetection(void)
{
	static INT16U InitTimes = 0;
	EN_SBC_UJA107x_TYPE CurrentDeviceStart;
	EN_SBC_UJA107x_TYPE CurrentDeviceEnd;
	INT8U InitStatus = 0;
	systick_delay_ms(2);//延时等待SBC正常
	do
	{
		// Power On detected
		InitTimes ++;
		CurrentDeviceStart = UJA1078_GetDeviceID();
		InitStatus = UJA1078_Init();
		CurrentDeviceEnd = UJA1078_GetDeviceID();
	}
	while(((CurrentDeviceStart != NXP_UJA1078) || (CurrentDeviceEnd != NXP_UJA1078)) && (InitTimes < 50));

}

/*-------------------------------------------------------------------------
* Function Name : UJA1078_StartupOprTask
* Description   :
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void UJA1078_StartupOprTask(void)
{
	// Reset and Wake-up source detection
//	PINS_DRV_WritePin(PTD, 6U, D_ON);
	UJA1078_ResetAndWakeUpDetection();

#if 0
	// Limp Home Handling
	UJA1078_LimpHomeHandling();


	//Check if watchdog enabled and synchronize timers
	UJA107x_WDSR = SBC_UJA107x_WDSR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA107x_WDSR);

	if((UJA107x_WDSR & WDSR_WOS_MASK) == 0)
	{
		WatchdogEnabled = TRUE;
	}
#endif
}
/*-------------------------------------------------------------------------
* Function Name : UJA1078_StartupOprTask
* Description   :
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
INT16U UJA1078MCR = 0;
INT16U UJA1078ICR = 0;
INT16U UJA1078ISR = 0;
void UJA1078_CheckTask(void)
{
	UJA1078_CWI_InterruptService();

	// Change to normal mode
	UJA1078MCR = SBC_UJA107x_MCR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA1078MCR);

	//读取中断控制寄存器
	UJA1078ICR = SBC_UJA107x_ICR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA1078ICR);

	//读取中断状态寄存器
	UJA1078ISR = SBC_UJA107x_ISR_CHECK;
	LpSpiSendData_U16(SBC_UJA107x_SpiCnl, &UJA1078ISR);

	//UJA1078_TransceiverControl();
}

