/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               UJA1078.h
** Last modified Date:      2019.3.12
** Last Version:            V1.0.0
** Description:             UJA1078 header file
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2019.3.12
** Version:                 V1.0.0
** Descriptions:            UJA1078 header file
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#ifndef __UJA1078_H__
#define __UJA1078_H__


/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "Common.h"
#include "NXP_SBC_UJA107x.h"
#include "Drv_lpspi.h"

/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/

#define	 SBC_UJA107x_SpiCnl 		(en_LpSpi_UJA1078)

#define	 SBC_UJA107x_MCR_CHECK		(MCR_ADDRESS_MASK | MCR_READ_MASK)
#define	 SBC_UJA107x_MCR_INIT		(MCR_ADDRESS_MASK | MCR_ENC_MASK)
#define SBC_UJA107x_MCR_NORMAL      (MCR_ADDRESS_MASK | MCR_MC_MASK | MCR_ENC_MASK | MCR_WBC_MASK)
#define	 SBC_UJA107x_MCR_NORMAL_DisableV2 (MCR_ADDRESS_MASK | MCR_MC2_MASK | MCR_ENC_MASK | MCR_WBC_MASK)//禁止v2
#define	 SBC_UJA107x_MCR_NORMAL_EnableV2  (MCR_ADDRESS_MASK | MCR_MC_MASK)//使能v2

#define	 SBC_UJA107x_MCR_SLEEP		(MCR_ADDRESS_MASK | MCR_MC1_MASK | MCR_ENC_MASK | MCR_WBC_MASK)
#define	 SBC_UJA107x_MCR_STANDBY	(MCR_ADDRESS_MASK | MCR_ENC_MASK | MCR_WBC_MASK)

#define	 SBC_UJA107x_ICR_CHECK		(ICR_ADDRESS_MASK | ICR_READ_MASK)
#define	 SBC_UJA107x_ICR_NORMAL		(ICR_ADDRESS_MASK | ICR_V1UIE_MASK | ICR_V2UIE_MASK | ICR_RTHC_MASK)
#define	 SBC_UJA107x_ICR_INIT		(ICR_ADDRESS_MASK | ICR_V1UIE_MASK | ICR_RTHC_MASK)
//#define	 SBC_UJA107x_ICR_INIT		(ICR_ADDRESS_MASK | ICR_V1UIE_MASK |ISR_WI1_MASK| ICR_RTHC_MASK | ICR_WSE1_MASK)
//#define	 SBC_UJA107x_ICR_INIT		(ICR_ADDRESS_MASK | ICR_RTHC_MASK)
#define	 SBC_UJA107x_ICR_LOWPOWER	(ICR_ADDRESS_MASK | ICR_V1UIE_MASK | ICR_WIC1_MASK | ICR_WIC2_MASK |  \
									ICR_STBCC_MASK | ICR_RTHC_MASK | ICR_WSE1_MASK | ICR_WSE2_MASK)

#define	 SBC_UJA107x_ISR_CHECK			(ISR_ADDRESS_MASK | ISR_READ_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_V1		(ISR_ADDRESS_MASK | ISR_V1UI_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_V2		(ISR_ADDRESS_MASK | ISR_V2UI_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_LWI1		(ISR_ADDRESS_MASK | ISR_LWI1_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_LWI2		(ISR_ADDRESS_MASK | ISR_LWI2_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_CI			(ISR_ADDRESS_MASK | ISR_CI_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_WT1		(ISR_ADDRESS_MASK | ISR_WI1_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_WT2		(ISR_ADDRESS_MASK | ISR_WI2_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_CWI		(ISR_ADDRESS_MASK | ISR_CWI_MASK)
#define	 SBC_UJA107x_ISR_INT_CLR_POSI		(ISR_ADDRESS_MASK | ISR_POSI_MASK)
#define	 SBC_UJA107x_ISR_CLEAN			(ISR_ADDRESS_MASK | ISR_WRITE_CLEAN_MASK)

#define	 SBC_UJA107x_WDSR_CHECK				(WDSR_ADDRESS_MASK | WDSR_READ_MASK)
#define	 SBC_UJA107x_WDSR_SWREST			(WDSR_ADDRESS_MASK | WDSR_SWR_MASK)

/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/
//运行模式
typedef enum
{
	EN_SBC_MODE_INIT = 0,	/*INIT*/
	EN_SBC_MODE_STANDBY,	/*STANDBY*/
	EN_SBC_MODE_NORMAL,		
	EN_SBC_MODE_SLEEP,
	EN_SBC_MODE_OVERTEMP,
}EN_SBC_UJA1078Mode;

typedef struct
{
	BOOL InitState;	//初始化状态；
	EN_SBC_UJA1078Mode Mode;//运行模式；
}ST_SBC_UJA1078Info;


/// enumeration type for the UJA107x family members
typedef enum 
{
  NXP_UJA1078,
  NXP_UJA1075,
  NXP_UJA1076,
  NXP_UJA1079,
  NXP_MAX,
}EN_SBC_UJA107x_TYPE;




/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/



/*
**********************************************************************************************************
					FUNCTIONS
**********************************************************************************************************
*/
extern INT8U UJA1078_Init(void);
extern void UJA1078_SleepMode(void);
extern void UJA1078_StopMode(void);
extern void UJA1078_CyclicWakeUpSBC(void);
extern void UJA1078_EnterNormalOperation(void);
extern void UJA1078_LimpHomeHandling(void);
extern void UJA1078_ResetAndWakeUpDetection(void);

extern void UJA1078_StartupOprTask(void);
extern void UJA1078_CheckTask(void);
extern void UJA1078_OpenV2(void);



#endif /* __UJA1078_H__ */

