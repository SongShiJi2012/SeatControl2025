/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "CpuPeripheralInit.h"
#include "Bootloader.h"
#include "Prog.h"
#include "Output.h"
#include "BootDesc.h"
#include "BootTp.h"
#include "kf32a156_bkp.h"
#include "kf32a156_usart.h"
#include "kf32a156_canfd.h"
#include   "BootCan.h"
#include "SPI.h"
#include "Srvl_E2memory.h"
#include "kflog.h"

  volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/

 extern BOOT_U16 	TimerBoot;
int main(void)
{
    /* Write your local variable definition here */

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
#ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
#endif
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */
    /* For example: for(;;) { } */

	INT8U u8Temp=0;

    CPU_System_Init();
    Cpu_SysTimer_Enable();
    Srvl_E2PowerOnInit();
    
    Output_FeedWatchDog();
    //
	BootCANaFCANinit();

    AppCodeValidFlg = FALSE;
    g_E2promAppCodeValidFlg = FALSE;
    BootEnterAppFlag = FALSE;
    EnterAppDelayTimeCnt = 0;
    AppCodeValidFlg = CheckAppCoeValidFlg();

#if (APP_DEBUG!=1u)
  g_E2promAppCodeValidFlg = CheckE2promAppCoeValidFlg();
#endif

    if((TRUE == AppCodeValidFlg) && (TRUE == g_E2promAppCodeValidFlg))
    {
      BootEnterAppFlag = TRUE;
      EnterAppDelayTimeCnt = 0;
    }
    
    //V2打开之后才能接受来自CAN_H和CAN_L的数据
    Output_FeedWatchDog();

    /*APP跳到BOOT的有效标识*/
	u8Temp = Srvl_GetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg);
    if(u8Temp != DESC_APP_BOOT_NULL && u8Temp != D_DIAG_NeedUpdateSort_Init)
    {
      /*APP跳转到BOOT后,将诊断会话设置为编程会话,复位超时时间*/
      BootDescTesterPresentTimer = BOOT_DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
      BootDescSessionChangedFlag = TRUE;
      BootDescPrevSession = BOOT_SESN_EXTDS;
      BootDescSession = BOOT_SESN_PRGS;
      BootDescTimer100ms = BOOT_DESC_TIMER_100MS;

      EnterAppDelayTimeCnt = D_EnterAppDelayTime_100ms;

      /*boot需回复正响应*/
      if(Srvl_GetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg) == DESC_APP_BOOT_NEED_RESP)
      {
          BootTpTxInfoStruct.cDataBuf[0] = 0x50;
          BootTpTxInfoStruct.cDataBuf[1] = 0x02;
          BootTpTxInfoStruct.cDataBuf[2] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME) >> 8); // 单位 1ms
          BootTpTxInfoStruct.cDataBuf[3] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2_CAN_SERVER_MAX * BOOT_DESC_CYCTIME);
          BootTpTxInfoStruct.cDataBuf[4] = (BOOT_U8)(((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10) >> 8); // 单位 10ms
          BootTpTxInfoStruct.cDataBuf[5] = (BOOT_U8)((BOOT_U16)BOOT_DESC_P2EX_CAN_SERVER_MAX * BOOT_DESC_CYCTIME / 10);
          BootTpTxInfoStruct.wDataLength = 6;
          BootDescNrc = BootDescNrcOK;

          Output_FeedWatchDog();
          BootTpTxStart();
          BootTpTxInfoStruct.wDataLength = 0;
          BootDescNrc = BootDescNrcNoRsp;
      }
      /*清除从APP跳转到BOOT的标识*/
      Srvl_SetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg, DESC_APP_BOOT_NULL) ;
    }

  for(;;)
  {
	  if(Boot_1msFlag == TRUE)
	  {
		  BootCANTRX(FALSE);
		  BootCAN_CheckARBSTART();
		  Boot_1msFlag = FALSE;
		  
		  Boot_Event5msTime ++;
		  Boot_Event10msTime ++;
		  
		  if(Boot_Event5msTime >= 5) // 5ms到
		  {
			  Boot_Event5msTime = 0;
			  Boot_5msTask();
		  }
		  
		  if(Boot_Event10msTime >= 10) // 10ms到
		  {
			  Boot_Event10msTime = 0;
			  Boot_10msTask();
		  }
	  }
  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
