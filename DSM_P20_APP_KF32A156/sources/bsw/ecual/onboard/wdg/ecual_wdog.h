/*************************************************************************************************
*  Copyright (c) 2019, ancle.co.
*  All rights reserved.
*
*  FileName:     ecual_wdog.h
*
*  Description:  board WDG abstraction interface header file
*
*  FileVersion:  V1.00
*
*  Date:         2019-03-15
*
*  Author:       ancle
*
*  Note:         1. New Create;
*************************************************************************************************/

#ifndef _ECUAL_WDOG_H_
#define _ECUAL_WDOG_H_

#include "pins_driver.h"
#include "types.h"

extern void ecual_WDOG_init(uint16_t TimerValue);
extern void ecual_WDOG_dinit(void);
extern void ecual_FeedDog(void);
extern void Ecual_FeedOutsideDog(void);

#endif /* ECUAL_WDOG_H_ */
