#include "lpspi_master_driver.h"
#include "hal_spi.h"
#include "ecual_edma.h"
//#include "interrupt_manager.h"

lpspi_state_t LpSpiState[LPSPI_INSTANCE_COUNT];

lpspi_master_config_t LpSpiConfig[LPSPI_INSTANCE_COUNT] = {
	{
	  .bitsPerSec = 1000000U,
	  .whichPcs = LPSPI_PCS0,
	  .pcsPolarity = LPSPI_ACTIVE_HIGH,
	  .bitcount = SPI_DATASIZE_8BITS,
	  .lpspiSrcClk = SPI_CLK_SCLK,
	  .clkPhase = SPI_CKE_1EDGE,
	  .clkPolarity = SPI_CKP_LOW,
	  .bitFirst = SPI_FIRSTBIT_MSB,
	  .transferType = LPSPI_USING_INTERRUPTS,
	  .rxDMAChannel = 0,
	  .txDMAChannel = 1,
	  .callback = NULL,
	  .callbackParam = NULL,
	},
	{
	  .bitsPerSec = 1000000U,
	  .whichPcs = LPSPI_PCS1,
	  .pcsPolarity = LPSPI_ACTIVE_HIGH,
	  .bitcount = SPI_DATASIZE_8BITS,
	  .lpspiSrcClk = SPI_CLK_SCLK,
	  .clkPhase = SPI_CKE_1EDGE,
	  .clkPolarity = SPI_CKP_HIGH,
	  .bitFirst = SPI_FIRSTBIT_MSB,
	  .transferType = LPSPI_USING_INTERRUPTS,
	  .rxDMAChannel = 6+6,//DMA1 通道6
	  .txDMAChannel = 5+6,//DMA1 通道5
	  .callback = NULL,
	  .callbackParam = NULL,
	},
	{
	  .bitsPerSec = 1000000U,
	  .whichPcs = LPSPI_PCS2,
	  .pcsPolarity = LPSPI_ACTIVE_HIGH,
	  .bitcount = SPI_DATASIZE_8BITS,
	  .lpspiSrcClk = SPI_CLK_SCLK,
	  .clkPhase = SPI_CKE_1EDGE,
	  .clkPolarity = SPI_CKP_LOW,
	  .bitFirst = SPI_FIRSTBIT_MSB,
	  .transferType = LPSPI_USING_INTERRUPTS,
	  .rxDMAChannel = 4,
	  .txDMAChannel = 5,
	  .callback = NULL,
	  .callbackParam = NULL,
	},
};


/*SPI 初始化*/
OptState_t Hal_SpiInit(SpiCommChannel_t uChannel,SpiParamConf_t *uParam)
{
	lpspi_master_config_t *Confp;
	lpspi_state_t *SpiStatep;
	
	if(uChannel>=COMM_SPI_MAX)
	{
		return OPT_STATE_FAILED;
	}

	if(uParam == NULL)
	{
		return OPT_STATE_PARAM_INVALID;
	}

	Confp = (lpspi_master_config_t *)&LpSpiConfig[uChannel];
	SpiStatep = (lpspi_state_t *)&LpSpiState[uChannel];

	if(uParam->TransferType == SPI_USING_SIMULATE)
	{
		return OPT_STATE_UNSUPPORTED;
	}
	Confp->bitsPerSec = uParam->BaudRate;
	Confp->transferType = uParam->TransferType;
	if(LPSPI_DRV_MasterInit(uChannel, SpiStatep, Confp) == STATUS_SUCCESS)
	{
		//INT_SYS_SetPriority((IRQn_Type)(LPSPI0_IRQn + uChannel), INT_PRIORITY_SPI_MPU );
		return OPT_STATE_SUCCESS;
	}

	return OPT_STATE_FAILED;
}

/*SPI 反初始化*/
OptState_t Hal_SpiDeInit(SpiCommChannel_t uChannel)
{
#if 0
	if(uChannel>=COMM_SPI_MAX)
	{
		return OPT_STATE_FAILED;
	}
	if(LPSPI_DRV_MasterDeinit(uChannel) == STATUS_SUCCESS)
	{
		return OPT_STATE_SUCCESS;
	}
	return OPT_STATE_FAILED;
#endif
	 LPSPI_DRV_DeInit(uChannel);
}

/*SPI 写数据*/
UINT32 Hal_SpiWrite(SpiCommChannel_t uChannel,UINT8 *uBuffer,UINT16 uLength)
{
	if(uChannel>=COMM_SPI_MAX)
	{
		return 0;
	}
	if((uBuffer == NULL)||(uLength == 0))
	{
		return 0;
	}

	if(LPSPI_DRV_MasterTransferBlocking(uChannel,uBuffer,NULL,uLength,1000) == STATUS_SUCCESS)
	{
		return uLength;
	}
	return 0;
}

/*SPI 读数据*/
UINT32 Hal_SpiRead(SpiCommChannel_t uChannel,UINT8 *uBuffer,UINT16 uLength)
{
	if(uChannel>=COMM_SPI_MAX)
	{
		return 0;
	}
	if((uBuffer == NULL)||(uLength == 0))
	{
		return 0;
	}

	if(LPSPI_DRV_MasterTransferBlocking(uChannel,NULL,uBuffer,uLength,100) == STATUS_SUCCESS)
	{
		return uLength;
	}
	return 0;
}


/*SPI 传输交换数据,读写数据*/
UINT32 Hal_SpiTransfer(SpiCommChannel_t uChannel,UINT8 *uSendBuffer,UINT8 *uReadBuffer,UINT16 uLength)
{
	if(uChannel>=COMM_SPI_MAX)
	{
		return 0;
	}
	if((uSendBuffer == NULL)||(uLength == 0)||(uReadBuffer == NULL))
	{
		return 0;
	}

	if(LPSPI_DRV_MasterTransferBlocking(uChannel,uSendBuffer,uReadBuffer,uLength,100) == STATUS_SUCCESS)
	{
		return uLength;
	}
	return 0;
}

/*SPI公共初始化函数*/
void Hal_SpiInitEx(void)
{
	SpiParamConf_t param;

	param.BaudRate = 1000000u;
	param.TransferType = SPI_USING_DMA;

	Hal_SpiInit(COMM_SPI_0,&param);
	Hal_SpiInit(COMM_SPI_1,&param);
	Hal_SpiInit(COMM_SPI_2,&param);

	if(param.TransferType == SPI_USING_DMA)
	{
		ECUAL_EdmaInit();
	}
}
