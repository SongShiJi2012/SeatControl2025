/*************************************************************************************************
 * Includes
 *************************************************************************************************/
#include "ecual_can.h"
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static CAN_RemoteWakeup_Callback_t wakeup_callback[CAN_INSTANCE_COUNT] = { NULL };

static flexcan_state_t canCom_State[CAN_INSTANCE_COUNT];

#if (HARDWARE_FILTER == STD_ON)
Can_HwFilterType Can_HwFilter[CAN_INSTANCE_COUNT] = {
	/*CANFD6配置*/
	{
	    {0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	    0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	    0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	    0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	    0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	    0x00000000U},  /*Mask*/
	    {CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
	    CAN_FILTER_STANDARD},  /*Type*/
	},
	/*CANFD7配置*/
	{
		{0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
		0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
		0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
		0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
		0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
		0x00000000U},  /*Mask*/
		{CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,CAN_FILTER_STANDARD,
		CAN_FILTER_STANDARD},  /*Type*/
	},
};
#endif

const Can_Controller_InterruptConfigType Can_Controller_InterruptDefaultConfig[CAN_INSTANCE_COUNT] = {
	//CANFD6中断配置
	{
		/* Rx interrupt enable */
		CAN_INTERRUPT_ENABLE,

		/* Tx interrupt enable set */
		CAN_INTERRUPT_ENABLE,

		/* Busoff interrupt enable set */
#if  (CAN_BUSOFF_RECOVERY_INTERRUPT == STD_ON)
		CAN_INTERRUPT_ENABLE,
#else
		CAN_INTERRUPT_DISABLE
#endif
		 /* Wakeup interrupt enable set */
		CAN_INTERRUPT_DISABLE,

		/* Error alarm interrupt set */
		CAN_INTERRUPT_DISABLE,

		/* Rx data Overflow interrupt set */
		CAN_INTERRUPT_DISABLE,

		/* Negative error interupt set */
		CAN_INTERRUPT_ENABLE,

		/* Arbitrate lose interupt set */
		CAN_INTERRUPT_ENABLE,

		/* Bus error interupt set */
		CAN_INTERRUPT_ENABLE,

	    /* CAN DMA Transmit Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* CAN DMA Receive Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* CAN MailBox Receive Triger Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* Preemption Priority */
		3,

		/* Sub priority */
		0,
	},

	//CANFD7 中断配置
	{
		/* Rx interrupt enable */
		CAN_INTERRUPT_ENABLE,

		/* Tx interrupt enable set */
		CAN_INTERRUPT_ENABLE,

		/* Busoff interrupt enable set */
#if  (CAN_BUSOFF_RECOVERY_INTERRUPT == STD_ON)
		CAN_INTERRUPT_ENABLE,
#else
		CAN_INTERRUPT_DISABLE
#endif
		 /* Wakeup interrupt enable set */
		CAN_INTERRUPT_DISABLE,

		/* Error alarm interrupt set */
		CAN_INTERRUPT_ENABLE,

		/* Rx data Overflow interrupt set */
		CAN_INTERRUPT_DISABLE,

		/* Negative error interupt set */
		CAN_INTERRUPT_ENABLE,

		/* Arbitrate lose interupt set */
		CAN_INTERRUPT_ENABLE,

		/* Bus error interupt set */
		CAN_INTERRUPT_ENABLE,

	    /* CAN DMA Transmit Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* CAN DMA Receive Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* CAN MailBox Receive Triger Interrupt Set */
		CAN_INTERRUPT_DISABLE,

		/* Preemption Priority */
		3,

		/* Sub priority */
		0,
	},
};

/*波特率计算公式：bandrate = HFCL/((PreScale+1)*(1+TSeg1+1+TSeg2+1)
 * 采样率计算公式（1+TSeg1+1）/（1+TSeg1+1+TSeg2+1）
 * 配置参数参考客户资料《02_BAIC_BCPF_HSCAN500k_BCAN&ICAN_ERS_2.1》 P20*/
const Can_BDRConfigType Canfd_Controller_AllClockAndBDRDefaultConfig[CAN_INSTANCE_COUNT] = {
	//CANFD6
	/* Default 500k hz  81.25% */
	/* Clock and bandrate config 0 : Index 0 */
	{
#if (WORKSOURCE_HFCLK == STD_ON)
			.PreScale = 1U,
			.Sjw = 1U,
			.TSeg1 = 11U,
			.TSeg2 = 2U,
#else
			.PreScale = 15U,			/* Prescale */   /*48M:5 1 11 2  120M 15 1 10 2*/
			.Sjw = 1U,				/* Swj */
			.TSeg1 = 10U,			/* Tseg1 */  //11+2/16
		    .TSeg2 = 2U,				/* Tseg2 */
#endif
		CAN_SAMPLE_ONCE /* Sample time */
	},
	//CANFD7
	/* Default 500k hz  75% */
	/* Clock and bandrate config 0 : Index 0 */
	{
#if (WORKSOURCE_HFCLK == STD_ON)
			.PreScale = 1U,
			.Sjw = 1U,
			.TSeg1 = 11U,
			.TSeg2 = 2U,
#else
			.PreScale = 11U,			/* Prescale */
			.Sjw = 1U,				/* Swj */
			.TSeg1 = 14U,			/* Tseg1 */
			.TSeg2 = 3U,				/* Tseg2 */
#endif
		CAN_SAMPLE_ONCE /* Sample time */
	}
};

const Can_FdBDRConfigType Canfd_Controller_ALLFdBDRDefaultConfig[CAN_INSTANCE_COUNT] = {
	//CANFD6 配置
	/* Default 500K hz */
	/* High Speed Clock and bandrate config 0 : Index 0 */
	{
#if (WORKSOURCE_HFCLK == STD_ON)
		.BrsPrescale = 1U,
		.HtSeg1 = 11U,
		.HtSeg2 = 2U,
#else
		.BrsPrescale = 2U,
		.HtSeg1 = 14U,
		.HtSeg2 = 3U,
#endif
	},
	//CANFD7 作为普通CAN配置
	/* Default 500K hz */
	/* High Speed Clock and bandrate config 0 : Index 0 */
	{
#if (WORKSOURCE_HFCLK == STD_ON)
		.BrsPrescale = 0U,
		.HtSeg1 = 5U,
		.HtSeg2 = 0U,
#else
		.BrsPrescale = 2U,
		.HtSeg1 = 14U,
		.HtSeg2 = 3U,
#endif
	},
};

Can_ControllerConfigType canCom_InitConfig[CAN_INSTANCE_COUNT] = {
	//CANFD6
	{
		/* Can controller Mode set */
		CANFD_NORMAL_MODE,
		/* Can FD Mode set */
		DISABLE,
		/* Can controller clock source set */
#if (WORKSOURCE_HFCLK == STD_ON)
		CAN_CLOCKSOURCE_HFCLK,
#else
		CAN_CLOCKSOURCE_SCLK,
#endif
		/* Can controller Arbitrate clock source set */
		CAN_CLOCKSOURCE_SCLK,
		/* Mailbox block size config */
		CAN_8_BYTE_DATALENGTH,
		/* Iso mode or non-iso mode config */
		CAN_FD_ISOMODE,
		/* Global Mask Set */
#if (HARDWARE_FILTER == STD_ON)
		0x00000000,
#else
		0xFFFFFFFF,
#endif
		/* Enable/disable mailbox full receive config */
		CAN_MBFULLRECEIVE_DISABLE,
		/* Interrupt config  */
		&Can_Controller_InterruptDefaultConfig[0],
#if (HARDWARE_FILTER == STD_ON)
		/* Hardware Filter config  */
		&Can_HwFilter[0],
#endif
		/* Arbitrate Segment Baudrate Config */
		&Canfd_Controller_AllClockAndBDRDefaultConfig[0],/*普通CAN波特率配置这个*/
		/* Data Segment Baudrate Config */
		&Canfd_Controller_ALLFdBDRDefaultConfig[0],
	},
	//CANFD7  目前作为普通CAN来用的,因为CAN4没有邮箱
	{
		/* Can controller Mode set */
		CANFD_NORMAL_MODE,
		/* Can FD Mode set */
		DISABLE,
		/* Can controller clock source set */
#if (WORKSOURCE_HFCLK == STD_ON)
		CAN_CLOCKSOURCE_HFCLK,
#else
		CAN_CLOCKSOURCE_SCLK,
#endif
		/* Can controller Arbitrate clock source set */
		CAN_CLOCKSOURCE_SCLK,
		/* Mailbox block size config */
		CAN_8_BYTE_DATALENGTH,
		/* Iso mode or non-iso mode config */
		CAN_FD_NON_ISOMODE,
		/* Global Mask Set */
#if (HARDWARE_FILTER == STD_ON)
		0x00000000,
#else
		0xFFFFFFFF,
#endif
		/* Enable/disable mailbox full receive config */
		CAN_MBFULLRECEIVE_DISABLE,
		/* Interrupt config  */
		&Can_Controller_InterruptDefaultConfig[1],
#if (HARDWARE_FILTER == STD_ON)
		/* Hardware Filter config  */
		&Can_HwFilter[1],
#endif
		/* Arbitrate Segment Baudrate Config */
		&Canfd_Controller_AllClockAndBDRDefaultConfig[1],
		/* Data Segment Baudrate Config */
		&Canfd_Controller_ALLFdBDRDefaultConfig[1],
	},
};

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/***********************************************************************************************
 * @function name:  void ecual_CAN_SetHwFilter(uint8_t instance,uint16_t Mask,uint8_t Type)
 * @description:    滤波    设置
 * @input parameters:      instance
 *						   MailboxCfg
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
#if 0
void ecual_CAN_SetHwFilter(const uint32_t instance,uint8_t Len,strCanMainMailboxRxbuffCfg* MainMailboxCfg)
{
	#if (HARDWARE_FILTER == STD_ON)
			uint8_t i;
			uint8_t MailIndex;
			uint16_t MailboxCfgLen = sizeof(strCanMainMailboxRxbuffCfg);
			strCanMainMailboxRxbuffCfg* MailboxCfg;
			 uint32_t value = (uint32_t)MainMailboxCfg;

	        memset(&Can_HwFilter[instance],0,51);

	        for(i=0;i<Len;i++)
	        {
	        	MailboxCfg = (strCanMainMailboxRxbuffCfg* )value;
	        	MailIndex = MailboxCfg->MailBoxIndex;
	        	Can_HwFilter[instance].MaskCode[MailIndex] = MailboxCfg->IndividualMask;
	        	Can_HwFilter[instance].Can_IdFilterFrame[MailIndex] = MailboxCfg->eMsgIDType;
	        	value += MailboxCfgLen;
	       }
	#endif
}
#endif
void ecual_CAN_SetHwFilter(uint8_t instance,strCanMainMailboxRxbuffCfg* MailboxCfg)
{
	#if (HARDWARE_FILTER == STD_ON)
		uint8_t MailIndex = MailboxCfg->MailBoxIndex;

		Can_HwFilter[instance].MaskCode[MailIndex] = MailboxCfg->IndividualMask;
		Can_HwFilter[instance].Can_IdFilterFrame[MailIndex] = MailboxCfg->eMsgIDType;
	#endif
}

/***********************************************************************************************
 * @function name:  bool_t ecual_CAN_init( const uint32_t instance,
                       flexcan_callback_t pCallback_event,
                       flexcan_error_callback_t pCallback_error,
                       CAN_RemoteWakeup_Callback_t pCallback_wakeup
                       )
 * @description:
 * @input parameters:      instance
 *						   pCallback_event
 *						   pCallback_error
 *						   pCallback_wakeup
 * @output parameters:     void
 * @return:         bool_t
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
bool_t ecual_CAN_init( const uint32_t instance, 
                       flexcan_callback_t pCallback_event,
                       flexcan_error_callback_t pCallback_error,
                       CAN_RemoteWakeup_Callback_t pCallback_wakeup
                       )
{
    bool_t rt = FALSE;
    status_t rc = STATUS_ERROR;

    if ( instance < MAX_CAN_PORT )
    {
        rc = FLEXCAN_DRV_Init( instance, &canCom_State[instance], &canCom_InitConfig[instance] );
        if ( STATUS_SUCCESS == rc )
        {
            FLEXCAN_DRV_InstallEventCallback( instance, pCallback_event, NULL );
            FLEXCAN_DRV_InstallErrorCallback( instance, pCallback_error, NULL );
            rt = TRUE;
        }
    }
    
    return rt;
}

/***********************************************************************************************
 * @function name:  bool_t ecual_CAN_ConfigTxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg)
 * @description:
 * @input parameters:      instance
 *						   mb_idx
 *						   pConfigMsg
 * @output parameters:     void
 * @return:         bool_t
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/

bool_t ecual_CAN_ConfigTxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg)
{
    bool_t rt = FALSE;
    status_t rc = STATUS_ERROR;

    //DEV_ASSERT(instance < CAN_INSTANCE_COUNT);
    //DEV_ASSERT(pConfigMsg->MBIdx < CAN_MAILBOX_NUM_MAX);
    /*20220924 以下数据需要重新配置*/

    rc = FLEXCAN_DRV_ConfigTxMb( instance,mb_idx, pConfigMsg, pConfigMsg->Id);

    rt = ( STATUS_SUCCESS == rc ) ? TRUE : FALSE;

    return rc;
}

/***********************************************************************************************
 * @function name:  bool_t ecual_CAN_ConfigRxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg
 * @description:
 * @input parameters:      instance
 *						   mb_idx
 *						   pConfigMsg
 * @output parameters:     void
 * @return:         bool_t
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
bool_t ecual_CAN_ConfigRxMb( const uint32_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *pConfigMsg )
{
    bool_t rt = FALSE;
    status_t rc = STATUS_ERROR;

    rc = FLEXCAN_DRV_ConfigRxMb(instance, mb_idx, pConfigMsg);

    rt = ( STATUS_SUCCESS == rc ) ? TRUE : FALSE;

    return rt;
}

/***********************************************************************************************
 * @function name:  bool_t ecual_CAN_receive( const uint8_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *message )
 * @description:
 * @input parameters:      instance
 *						   mb_idx
 *						   message
 * @output parameters:     void
 * @return:         bool_t
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
bool_t ecual_CAN_receive( const uint8_t instance, const uint8_t mb_idx, Canfd_MailboxHeaderType *message )
{
    bool_t rt = FALSE;
    status_t rc = STATUS_ERROR;

    rc = FLEXCAN_DRV_Receive( instance, mb_idx, message );

    rt = ( STATUS_SUCCESS == rc ) ? TRUE : FALSE;

    return rt;
}

/***********************************************************************************************
 * @function name: bool_t ecual_CAN_sendOnce( const uint8_t instance,
                           const bool_t isCANFD,
                           strCanMainMailboxTxbuffCfg *pConfigMsg,
                           Canfd_MailboxHeaderType* tx_info
                           )
 * @description:
 * @input parameters:      instance
 *						   isCANFD
 *						   pConfigMsg
 *						   tx_info
 * @output parameters:     void
 * @return:         bool_t
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
bool_t ecual_CAN_sendOnce( const uint8_t instance,
                           const bool_t isCANFD,
                           strCanMainMailboxTxbuffCfg *pConfigMsg,
                           Canfd_MailboxHeaderType* tx_info
                           )
{
    bool_t rt = FALSE;
    status_t rc = STATUS_ERROR;

    //DEV_ASSERT( pConfigMsg->MBIdx < FEATURE_CAN_MAX_MB_NUM);
    /*20220924 以下数据需要重新配置*/


    rc = FLEXCAN_DRV_Send( instance,
    					   pConfigMsg->MailBoxIndex,
                           tx_info,
						   pConfigMsg->CanTxId,
						   tx_info->FrameData.U8Data
                           );

    rt = ( STATUS_SUCCESS == rc ) ? TRUE : FALSE;

    return rt;
}

/***********************************************************************************************
 * @function name: void ecual_CAN_Deinit( const uint8_t instance )
 * @description:
 * @input parameters:      instance
 * @output parameters:     void
 * @return:         void
 * @note:
 * @author:         2022-11-25 czb
 ***********************************************************************************************/
void ecual_CAN_Deinit( const uint8_t instance )
{
   FLEXCAN_DRV_Deinit( instance );
}
