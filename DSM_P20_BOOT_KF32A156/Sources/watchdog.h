/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : watchdog.h
**     Project     : DSM_C52X_APP
**     Processor   : S32K144_100
**     Component   : wdog
**     Version     : Component SDK_S32K14x_08, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K14x_08
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-05-14, 10:30, # CodeGen: 0
**     Contents    :
**         WDOG_DRV_Init             - status_t WDOG_DRV_Init(uint32_t instance, const wdog_user_config_t *...
**         WDOG_DRV_Deinit           - void WDOG_DRV_Deinit(uint32_t instance);
**         WDOG_DRV_GetConfig        - void WDOG_DRV_GetConfig(uint32_t instance, wdog_user_config_t * const config);
**         WDOG_DRV_GetDefaultConfig - void WDOG_DRV_GetDefaultConfig(wdog_user_config_t * const config);
**         WDOG_DRV_SetInt           - status_t WDOG_DRV_SetInt(uint32_t instance,bool enable);
**         WDOG_DRV_Trigger          - void WDOG_DRV_Trigger(uint32_t instance);
**         WDOG_DRV_GetCounter       - uint16_t WDOG_DRV_GetCounter(uint32_t instance);
**         WDOG_DRV_SetWindow        - void WDOG_DRV_SetWindow(uint32_t instance, bool enable, uint16_t windowvalue);
**         WDOG_DRV_SetMode          - void WDOG_DRV_SetMode(uint32_t instance, bool enable, wdog_set_mode_t Setmode);
**         WDOG_DRV_SetTimeout       - void WDOG_DRV_SetTimeout(uint32_t instance, uint16_t timeout);
**         WDOG_DRV_SetTestMode      - void WDOG_DRV_SetTestMode(uint32_t instance, wdog_test_mode_t testMode);
**         WDOG_DRV_GetTestMode      - wdog_test_mode_t WDOG_DRV_GetTestMode(uint32_t instance);
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file watchdog.h
** @version 01.00
*/
/*!
**  @addtogroup watchdog_module watchdog module documentation
**  @{
*/
#ifndef watchdog_H
#define watchdog_H
#include "wdog_driver.h"

extern void WDOG_Init(uint16_t TimeOut);
extern void WDOG_Feed(void);

#endif

