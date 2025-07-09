#include "ecual_edma.h"
#include "edma_driver.h"
#include "ecual_common.h"

/*! @brief Physical channel number for channel configuration #0 */
#define EDMA_CHN0_NUMBER   (0U)

/*! @brief Physical channel number for channel configuration #1 */
#define EDMA_CHN1_NUMBER   (1U)

/*! @brief Physical channel number for channel configuration #2 */
#define EDMA_CHN2_NUMBER   (2U)

/*! @brief Physical channel number for channel configuration #3 */
#define EDMA_CHN3_NUMBER   (3U)

/*! @brief Physical channel number for channel configuration #4 */
#define EDMA_CHN4_NUMBER   (4U)

/*! @brief Physical channel number for channel configuration #5 */
#define EDMA_CHN5_NUMBER   (5U)

/*! @brief Physical channel number for channel configuration #6 */
#define EDMA_CHN6_NUMBER   (6U)

/*! @brief Physical channel number for channel configuration #7 */
#define EDMA_CHN7_NUMBER   (7U)

#define EDMA_INSTANCE0_NUMBER   (0U)
#define EDMA_INSTANCE1_NUMBER   (1U)

/*! @brief The total number of configured channels */
#define EDMA_CONFIGURED_CHANNELS_COUNT   (3U)




edma_state_t dmaController1_State;

edma_chn_state_t dmaController1Chn0_State;

edma_chn_state_t dmaController1Chn1_State;

edma_chn_state_t dmaController1Chn2_State;

edma_chn_state_t dmaController1Chn3_State;

edma_chn_state_t dmaController1Chn4_State;

edma_chn_state_t dmaController1Chn5_State;

edma_chn_state_t dmaController1Chn6_State;

edma_chn_state_t dmaController1Chn7_State;


edma_chn_state_t * const edmaChnStateArray[] = {
    &dmaController1Chn0_State,
    &dmaController1Chn1_State,
    &dmaController1Chn2_State,
    &dmaController1Chn3_State,
    &dmaController1Chn4_State,
    &dmaController1Chn5_State,
    &dmaController1Chn6_State,
    &dmaController1Chn7_State
};


edma_channel_config_t dmaController1Chn0_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_6,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN0_NUMBER,
    //.source = EDMA_REQ_LPSPI0_RX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
edma_channel_config_t dmaController1Chn1_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN1_NUMBER,
    //.source = EDMA_REQ_LPSPI0_TX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};

//spi 1
edma_channel_config_t dmaController1Chn2_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN5_NUMBER+7,//一个DMA模块对应的通道只有7个,在接口里通过虚拟通道再转化为实际对应的DMA模块以及对应的物理通道
    .periphAddr = (uint32_t) & (SPI1_SFR->BUFR),
    .transferDirection = DMA_PERIPHERAL_TO_MEMORY,
    .oneShotEn = 0,
    //.source = EDMA_REQ_LPSPI1_RX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
edma_channel_config_t dmaController1Chn3_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_6,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN4_NUMBER+7,
    .periphAddr = (uint32_t) & (SPI1_SFR->BUFR),
    .transferDirection = DMA_MEMORY_TO_PERIPHERAL,
    .oneShotEn = 1,
    //.source = EDMA_REQ_LPSPI1_TX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
//

edma_channel_config_t dmaController1Chn4_Config = {
	.channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN4_NUMBER,
    //.source = EDMA_REQ_LPSPI2_RX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
edma_channel_config_t dmaController1Chn5_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN5_NUMBER,
    .periphAddr = (uint32_t) & (SPI2_SFR->BUFR),
    .transferDirection = DMA_PERIPHERAL_TO_MEMORY,
    //.source = EDMA_REQ_LPSPI2_TX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
edma_channel_config_t dmaController1Chn6_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN3_NUMBER,
    .periphAddr = (uint32_t) & (USART1_SFR->RBUFR),
    .transferDirection = DMA_PERIPHERAL_TO_MEMORY,
    //.source = EDMA_REQ_LPUART1_RX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};
edma_channel_config_t dmaController1Chn7_Config = {
    .channelPriority = EDMA_CHN_PRIORITY_5,//EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN2_NUMBER,
    .periphAddr = (uint32_t) & (USART1_SFR->TBUFR),
    .transferDirection = DMA_MEMORY_TO_PERIPHERAL,
    .oneShotEn = 1,
    //.source = EDMA_REQ_LPUART1_TX,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false
};

const edma_channel_config_t * const edmaChnConfigArray[] = {
    //&dmaController1Chn0_Config,
    //&dmaController1Chn1_Config,
	&dmaController1Chn2_Config,
	&dmaController1Chn3_Config,
    //&dmaController1Chn4_Config,
    //&dmaController1Chn5_Config,
	//&dmaController1Chn6_Config,
	&dmaController1Chn7_Config
};

void ECUAL_EdmaInit(void)
{
	EDMA_DRV_Init(&dmaController1_State, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);

	for(uint8_t i=0; i<EDMA_CONFIGURED_CHANNELS_COUNT; i++ )
	{
		//INT_SYS_SetPriority((IRQn_Type)(DMA0_IRQn+i), INT_PRIORITY_SPI_MPU );//中断以后再研究
	}
}

void ECUAL_EdmaUnInit(void)
{
	EDMA_DRV_Deinit();
}
