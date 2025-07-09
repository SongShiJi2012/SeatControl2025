/****************************Copyright (c)**************************************************
** File Name:               Rte_CanInterface.h
** Last modified Date:      2025.4.23
** Last Version:            V1.0
** Description:             CAN½Ó¿Ú²ã
********************************************************************************************/
#ifndef _RTE_CANINTERFACE_H_
#define _RTE_CANINTERFACE_H_

#include "Common.h"



/********************************************************************************
*variables define
********************************************************************************/


/*
*******************************************************************************
*Function define
*******************************************************************************
*/
extern INT8U Rte_GetCAN_PosiPercent(INT8U i);
extern BOOL Rte_GetCAN_Gear_PN_Flag(void);
extern void Rte_SetCanEvent_0x3B2(INT16U temp);
extern BOOL Rte_GetCanEventSendTimes_0x3B2(void);
extern INT8U Ecual_CanGetDrvHeatLvl(void);
extern INT8U Ecual_CanGetPasHeatLvl(void);
extern INT8U Ecual_CanGetThirdHeatLvl(void);
extern void Ecual_CanSetDrvHeatSts(INT8U Sts);
extern void Ecual_CanSetPasHeatSts(INT8U Sts);
extern void Ecual_CanSetThirdHeatSts(INT8U Sts);
extern INT8U Ecual_CanGetHeatMsgLostFlag(void);
extern INT8U Ecual_CanGetDriver_HMI_VentilateMsg(void);
extern INT8U Ecual_CanGetDriver_Tbox_VentilateMsg(void);
extern INT8U Ecual_CanGetPassenger_HMI_VentilateMsg(void);
extern INT8U Ecual_CanGetPassenger_Tbox_VentilateMsg(void);
extern INT8U Ecual_CanGetThird_HMI_VentilateMsg(void);
extern INT8U Ecual_CanGetThird_Tbox_VentilateMsg(void);
extern INT8U Ecual_CanGetDrvVentLvl(void);
extern INT8U Ecual_CanGetPasVentLvl(void);
extern INT8U Ecual_CanGetThirdVentLvl(void);

extern void Ecual_CanSetDrvVentSts(INT8U Sts);
extern void Ecual_CanSetDrvVentLvl(INT8U Sts);
extern void Ecual_CanSetThirdVentLvl(INT8U Sts);
extern void Ecual_CanSetPasVentLvl(INT8U Sts);
extern void Ecual_CanSetPasVentSts(INT8U Sts);
#endif

