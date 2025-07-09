/*******************************************************************************
 *  $File Name$       : edma_driver.c
 *  $Author$          : sth
 *  $Data$            : 2022-05
 *  $Version$         : V1.0.0
 *  $Hard Version     : KF32A156MQV
 *  $Description$     :
 ******************************************************************************/

/*******************************************************************************
* Include Files
 ******************************************************************************/
#include "edma_driver.h"
#include "kf32a156_int.h"
#include "devassert.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//��ʼ��ʹ��,ʵ�ʽ��շ������ݳ��Ȼ���������
#define edmaDefaultReceiveDataLen (16U)

/*******************************************************************************
 * Variables
 ******************************************************************************/
//��ʼ��ʹ��,ʵ�ʽ��շ������ݵ�ַ����������
static uint8_t s_edmaDefaultReceiveData[edmaDefaultReceiveDataLen];

/*! @brief Array of base addresses for DMA instances. */
static DMA_Type * const s_edmaBase[DMA_INSTANCE_COUNT] = DMA_BASE_PTRS;
/*! @brief Array of default DMA channel interrupt handlers. */
static const IRQn_Type s_edmaIrqId[FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES] = DMA_CHN_IRQS;
/*! @brief EDMA global structure to maintain eDMA state */
static edma_state_t * s_virtEdmaState;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void EDMA_DRV_ClearStructure(uint8_t *sructPtr, size_t size);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_Init
 * Description   : Initializes the eDMA module.
 *
 * Implements    : EDMA_DRV_Init_Activity
 *END**************************************************************************/
status_t EDMA_DRV_Init(edma_state_t *edmaState,
                       edma_chn_state_t * const chnStateArray[],
                       const edma_channel_config_t * const chnConfigArray[],
                       uint32_t chnCount)
{
    uint32_t index = 0U;
    DMA_Type *edmaRegBase = NULL;
    IRQn_Type irqNumber = 0;//NotAvail_IRQn;
    status_t edmaStatus = STATUS_SUCCESS;
    status_t chnInitStatus = STATUS_SUCCESS;

    /* Check the state and configuration structure pointers are valid */
    DEV_ASSERT((edmaState != NULL) && (userConfig != NULL));

    /* Check the module has not already been initialized */
    //DEV_ASSERT(s_virtEdmaState == NULL);

    /* Save the runtime state structure for the driver */
    s_virtEdmaState = edmaState;

    /* Clear the state structure. */
    EDMA_DRV_ClearStructure((uint8_t *)s_virtEdmaState, sizeof(edma_state_t));

    /* Init all DMA instances */
    for(index = 0U; index < (uint32_t)DMA_INSTANCE_COUNT; index++)
    {
        edmaRegBase = s_edmaBase[index];

    	/* Reset the DMA0 peripheral to enable the peripheral clock */
    	DMA_Reset(edmaRegBase);
    }

    /* Register all edma channel interrupt handlers into vector table. */
    for (index = 0U; index < (uint32_t)DMA_INSTANCE_COUNT; index++)
    {
        /* Enable channel interrupt ID. */
        irqNumber = s_edmaIrqId[index];
    	/*Preempt priority: Subpriority: */
    	INT_Interrupt_Priority_Config(irqNumber, 4, 0);
        INT_Interrupt_Enable(irqNumber, TRUE);
    }
    
    /* Initialize the channels based on configuration list */
    if ((chnStateArray != NULL) && (chnConfigArray != NULL))
    {
        for (index = 0U; index < chnCount; index++)
        {
            chnInitStatus = EDMA_DRV_ChannelInit(chnStateArray[index], chnConfigArray[index]);
            if (chnInitStatus != STATUS_SUCCESS)
            {
                edmaStatus = chnInitStatus;
            }
        }
    }

    return edmaStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_Deinit
 * Description   : Deinitialize EDMA.
 *
 * Implements    : EDMA_DRV_Deinit_Activity
 *END**************************************************************************/
status_t EDMA_DRV_Deinit(void)
{
    uint32_t index = 0U;
    IRQn_Type irqNumber = 0;//NotAvail_IRQn;
    const edma_chn_state_t *chnState = NULL;

    if (s_virtEdmaState != NULL)
    {
        /* Release all edma channel. */
        for (index = 0U; index < (uint32_t)FEATURE_DMA_VIRTUAL_CHANNELS; index++)
        {
            /* Release all channels. */
            chnState = s_virtEdmaState->virtChnState[index];
            if (chnState != NULL)
            {
                (void) EDMA_DRV_ReleaseChannel(chnState->virtChn);
            }
        }
        for (index = 0U; index < (uint32_t)FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES; index++)
        {
            /* Disable channel interrupts. */
            irqNumber = s_edmaIrqId[index];
            INT_Interrupt_Enable(irqNumber, FALSE);
        }
    }

    s_virtEdmaState = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_Transmit
 * Description   :
 *
 * Implements    :
 *END**************************************************************************/
void EDMA_DRV_Transmit(uint8_t virtualChannel, uint32_t srcAddr, uint16_t Number)
{
    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel */
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Load corresponding DMA instance pointer */
    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];

	DMA_Memory_Start_Address_Config(edmaRegBase, dmaChannel, (uint32_t)srcAddr);
	DMA_Transfer_Number_Config(edmaRegBase, dmaChannel, Number);
	DMA_Channel_Enable (edmaRegBase, dmaChannel, TRUE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ChannelInit
 * Description   : Initialize EDMA channel.
 *
 * Implements    : EDMA_DRV_ChannelInit_Activity
 *END**************************************************************************/
status_t EDMA_DRV_ChannelInit(edma_chn_state_t *edmaChannelState,
                              const edma_channel_config_t *edmaChannelConfig)
{
	DMA_InitTypeDef Dma_ConfigPtr;
    /* Get status */
    status_t retStatus = STATUS_SUCCESS;

    //s 20220428 о��΢���DMA1�޷����жϵķ���
	#define DMA1_REMAP_ADDR ((uint32_t)(0x40001700+0x0C8))
	#define D_DMA1_REMAP	((uint32_t *)DMA1_REMAP_ADDR)
	uint32_t temp;
	temp = *D_DMA1_REMAP;
	temp = temp | 0x80;
	*D_DMA1_REMAP = temp;
	//e 20220428 о��΢���DMA1�޷����жϵķ���

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(edmaChannelConfig->virtChnConfig);

    /* Get DMA channel from virtual channel */
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(edmaChannelConfig->virtChnConfig);

    /* Load corresponding DMA instance pointer */
    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];
    /* Get virtual channel value */
    uint8_t virtualChannel = edmaChannelConfig->virtChnConfig;

	/* Transmit data size */
	Dma_ConfigPtr.m_Number = edmaDefaultReceiveDataLen;
	/* DMA transmit direction */
	Dma_ConfigPtr.m_Direction = edmaChannelConfig->transferDirection;
	/* DMA channel priority */
	Dma_ConfigPtr.m_Priority = DMA_CHANNEL_TOP;
	/* Peripheral data width */
	Dma_ConfigPtr.m_PeripheralDataSize = DMA_DATA_WIDTH_8_BITS;
	/* Memory data width */
	Dma_ConfigPtr.m_MemoryDataSize = DMA_DATA_WIDTH_8_BITS;
	/* Peripheral address incremental mode enable */
	Dma_ConfigPtr.m_PeripheralInc = FALSE;
	/* Memory address incremental mode enable */
	Dma_ConfigPtr.m_MemoryInc = TRUE;
	/* DMA channel select */
	Dma_ConfigPtr.m_Channel = dmaChannel;
	/* DMA data block transfer mode */
	Dma_ConfigPtr.m_BlockMode = DMA_TRANSFER_BYTE;
	/* Cycle mode enable */
	Dma_ConfigPtr.m_LoopMode = FALSE;
	/* Peripheral start address */
	Dma_ConfigPtr.m_PeriphAddr = edmaChannelConfig->periphAddr;
	/* Memory start address */
	Dma_ConfigPtr.m_MemoryAddr = (uint32_t)&s_edmaDefaultReceiveData;

	/* Configure DMA */
	DMA_Configuration(edmaRegBase, &Dma_ConfigPtr);

    /* DMA finsh interrupt enable */
    DMA_Finish_Transfer_INT_Enable(edmaRegBase, Dma_ConfigPtr.m_Channel, TRUE);

    /* Set virtual channel state */
    s_virtEdmaState->virtChnState[virtualChannel] = edmaChannelState;
    /* Set virtual channel value */
    s_virtEdmaState->virtChnState[virtualChannel]->virtChn = virtualChannel;
    /* Set virtual channel status to normal */
    s_virtEdmaState->virtChnState[virtualChannel]->status = EDMA_CHN_NORMAL;
	/* Install the user callback */
	retStatus = EDMA_DRV_InstallCallback(edmaChannelConfig->virtChnConfig, edmaChannelConfig->callback, edmaChannelConfig->callbackParam);

	//�������ʹ��
	if(edmaChannelConfig->oneShotEn)
	{
		DMA_Oneshot_Enable(edmaRegBase, Dma_ConfigPtr.m_Channel, TRUE);
	}

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_InstallCallback
 * Description   : Register callback function and parameter.
 *
 * Implements    : EDMA_DRV_InstallCallback_Activity
 *END**************************************************************************/
status_t EDMA_DRV_InstallCallback(uint8_t virtualChannel,
                                  edma_callback_t callback,
                                  void *parameter)
{
    /* Check the channel number is valid */
    //DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check the channel is allocated */
    //DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    s_virtEdmaState->virtChnState[virtualChannel]->callback = callback;
    s_virtEdmaState->virtChnState[virtualChannel]->parameter = parameter;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ReleaseChannel
 * Description   : Free eDMA channel's hardware and software resource.
 *
 * Implements    : EDMA_DRV_ReleaseChannel_Activity
 *END**************************************************************************/
status_t EDMA_DRV_ReleaseChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    //DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check the DMA module is initialized */
    //DEV_ASSERT(s_virtEdmaState != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Get pointer to channel state */
    edma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];

    /* Check that virtual channel is initialized */
    //DEV_ASSERT(chnState != NULL);

    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];

    /* Stop edma channel. */
   //EDMA_SetDmaRequestCmd(edmaRegBase, dmaChannel, false);

    /* Reset the channel state structure to default value. */
    EDMA_DRV_ClearStructure((uint8_t *)chnState, sizeof(edma_chn_state_t));

    s_virtEdmaState->virtChnState[virtualChannel] = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ClearIntStatus
 * Description   : Clear done and interrupt retStatus.
 *
 *END**************************************************************************/
void EDMA_DRV_ClearIntStatus(uint8_t virtualChannel)
{
    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];
    //EDMA_ClearDoneStatusFlag(edmaRegBase, dmaChannel);
    //EDMA_ClearIntStatusFlag(edmaRegBase, dmaChannel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ClearSoftwareTCD
 * Description   : Clear the software tcd structure.
 *
 *END**************************************************************************/
//static void EDMA_DRV_ClearSoftwareTCD(edma_software_tcd_t *stcd)
//{
    //EDMA_DRV_ClearStructure((uint8_t *)stcd, sizeof(edma_software_tcd_t));
//}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_IRQHandler
 * Description   : EDMA IRQ handler.
 *END**************************************************************************/
void EDMA_DRV_IRQHandler(uint8_t virtualChannel)
{
    const edma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];

    EDMA_DRV_ClearIntStatus(virtualChannel);

    if (chnState != NULL)
    {
        if (chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ErrorIRQHandler
 * Description   : EDMA error IRQ handler
 *END**************************************************************************/
void EDMA_DRV_ErrorIRQHandler(uint8_t virtualChannel)
{
    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];
    //EDMA_SetDmaRequestCmd(edmaRegBase, dmaChannel, false);
    edma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];
    if (chnState != NULL)
    {
        //EDMA_DRV_ClearIntStatus(virtualChannel);
        //EDMA_ClearErrorIntStatusFlag(edmaRegBase, dmaChannel);
        chnState->status = EDMA_CHN_ERROR;
        if (chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_StartChannel
 * Description   : Starts an eDMA channel.
 *
 * Implements    : EDMA_DRV_StartChannel_Activity
 *END**************************************************************************/
status_t EDMA_DRV_StartChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    //DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that eDMA module is initialized */
    //DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    //DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Enable requests for current channel */
    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];
    //EDMA_SetDmaRequestCmd(edmaRegBase, dmaChannel, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_StopChannel
 * Description   : Stops an eDMA channel.
 *
 * Implements    : EDMA_DRV_StopChannel_Activity
 *END**************************************************************************/
status_t EDMA_DRV_StopChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    //DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that eDMA module is initialized */
    //DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    //DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t)FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t)FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Disable requests for current channel */
    DMA_Type *edmaRegBase = s_edmaBase[dmaInstance];
    //EDMA_SetDmaRequestCmd(edmaRegBase, dmaChannel, false);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_GetChannelStatus
 * Description   : Returns the eDMA channel retStatus.
 *
 * Implements    : EDMA_DRV_GetChannelStatus_Activity
 *END**************************************************************************/
edma_chn_status_t EDMA_DRV_GetChannelStatus(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    //DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that eDMA module is initialized */
    //DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    //DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    return s_virtEdmaState->virtChnState[virtualChannel]->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_GetDmaRegBaseAddr
 * Description   : Returns the DMA register base address.
 *
 * Implements    : EDMA_DRV_GetDmaRegBaseAddr
 *END**************************************************************************/
DMA_Type * EDMA_DRV_GetDmaRegBaseAddr(uint32_t instance)
{
    /* Check that instance is valid */
    //DEV_ASSERT(instance < DMA_INSTANCE_COUNT);
    
    return s_edmaBase[instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ClearStructure
 * Description   : Clears all bytes at the passed structure pointer.
 *
 *END**************************************************************************/
static void EDMA_DRV_ClearStructure(uint8_t *sructPtr, size_t size)
{
    while (size > 0U)
    {
        *sructPtr = 0;
        sructPtr ++;
        size --;
    }
}
/***********************************************************************************************
 * @function name: ADC_DMA_NormalChl_Init
 * @description: ��ʼ��ָ�� ADC �� DMA ͨ����������ͨͨ�����ݴ��䣬����DMA������ʹ�ܡ�
 * @input parameters:
 *      ADC_SFRmap *ADCx        - ADC�Ĵ�����ַ���� ADC0_SFR��
 *      DMA_SFRmap *DMAx        - DMA�Ĵ�����ַ���� DMA0_SFR��
 *      uint32_t dmaChannel     - DMAͨ���ţ��� DMA_CHANNEL_5��
 *      void *ptr_Memory        - DMA�����Ŀ���ڴ��ַ������ָ��
 *      uint16_t numTransfer    - һ��DMA�����������������λΪ32λ���ݸ�����
 *      uint8_t bResetDMA          - �Ƿ�λDMAģ�飨���ڶ��ADC����һ��DMAģ��������
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-06-27
 ***********************************************************************************************/
void ADC_DMA_NormalChl_Init(ADC_SFRmap *ADCx, DMA_SFRmap *DMAx, uint32_t dmaChannel, void *ptr_Memory, uint16_t numTransfer, uint8_t bResetDMA)
{
    DMA_InitTypeDef dmaNewStruct;

    /* ��ѡ����λ DMA ģ�飬���״̬�����ã�ȷ����ʼ��һ���� */
    if(bResetDMA == TRUE)
    {
        DMA_Reset(DMAx);
    }

    /* ���� DMA �����������������λΪ32λ���ݣ� */
    dmaNewStruct.m_Number = numTransfer;
    /* ���� DMA Ϊ���赽�ڴ淽�� */
    dmaNewStruct.m_Direction = DMA_PERIPHERAL_TO_MEMORY;
    /* ���� DMA ͨ�����ȼ�Ϊ�� */
    dmaNewStruct.m_Priority = DMA_CHANNEL_HIGHER;
    /* �����������ݿ��Ϊ 32 λ��ADC �� DATA �Ĵ���Ϊ 32 λ�� */
    dmaNewStruct.m_PeripheralDataSize = DMA_DATA_WIDTH_32_BITS;
    /* �����ڴ����ݿ��Ϊ 32 λ */
    dmaNewStruct.m_MemoryDataSize = DMA_DATA_WIDTH_32_BITS;
    /* �����ַ�̶�����������ֻ�� ADC �� DATA �Ĵ����� */
    dmaNewStruct.m_PeripheralInc = FALSE;
    /* �ڴ��ַ���������ڴ洢������ ADC ����ֵ */
    dmaNewStruct.m_MemoryInc = TRUE;
    /* ѡ��Ŀ�� DMA ͨ�� */
    dmaNewStruct.m_Channel = dmaChannel;
    /* ���� DMA ���䴥��Ϊһ�δ���һ���ֽڣ��� ADC ת����������� */
    dmaNewStruct.m_BlockMode = DMA_TRANSFER_BYTE;
    /* ���� DMA ѭ��ģʽ��ʵ���������� */
    dmaNewStruct.m_LoopMode = TRUE;
    /* ���������ַΪ ADC �� DATA �Ĵ��� */
    dmaNewStruct.m_PeriphAddr = (uint32_t)(&ADCx->DATA);
    /* ���� DMA Ŀ���ڴ��ַ */
    dmaNewStruct.m_MemoryAddr = (uint32_t)ptr_Memory;

    /* Ӧ�� DMA ���ýṹ�� */
    DMA_Configuration(DMAx, &dmaNewStruct);
    /* ������ѡ DMA ͨ�� */
    DMA_Channel_Enable(DMAx, dmaChannel, TRUE);
}

/***********************************************************************************************
 * @function name: ADC_DMA_Int_Config
 * @description: ����ָ�� ADC �� DMA ͨ���жϣ���Ҫʹ��ȫ��������жϣ������ж����ȼ���������жϱ�־��
 * @input parameters:
 *      DMA_SFRmap *DMAx       - DMA�Ĵ�����ַ���� DMA0_SFR��DMA1_SFR��
 *      uint32_t dmaChannel    - DMAͨ���ţ��� DMA_CHANNEL_5��DMA_CHANNEL_7��
 *      InterruptIndex INT_Index - �ж��������� INT_DMA0��INT_DMA1��
 *      uint32_t Preemption    - �ж���ռ���ȼ�
 *      uint32_t SubPriority   - �ж������ȼ�
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-06-27
 ***********************************************************************************************/
void ADC_DMA_Int_Config(DMA_SFRmap *DMAx, uint32_t dmaChannel, InterruptIndex INT_Index, uint32_t Preemption, uint32_t SubPriority)
{
    /* ʹ��DMA�봫���жϣ���������ã� */
//    DMA_Set_INT_Enable(DMAx, dmaChannel, DMA_INT_HALF_TRANSFER, TRUE);
//    /* ���DMA�봫���жϱ�־ */
//    DMA_Clear_INT_Flag(DMAx, dmaChannel, DMA_INT_HALF_TRANSFER);

    /* ʹ��DMAȫ�����ж� */
    DMA_Set_INT_Enable(DMAx, dmaChannel, DMA_INT_FINISH_TRANSFER, TRUE);
    /* ���DMAȫ�����жϱ�־ */
    DMA_Clear_INT_Flag(DMAx, dmaChannel, DMA_INT_FINISH_TRANSFER);
    /* �����ж����ȼ� */
    INT_Interrupt_Priority_Config(INT_Index, Preemption, SubPriority);

    /* ʹ���ж� */
    INT_Interrupt_Enable(INT_Index, TRUE);
    /* ����жϱ�־ */
    INT_Clear_Interrupt_Flag(INT_Index);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

