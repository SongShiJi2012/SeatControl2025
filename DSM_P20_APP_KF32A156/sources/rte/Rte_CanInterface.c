/************************************************************************************************
File created time : 2021-04-23 16:21:51
Tool Name :         NA
Filename:           Rte_CANInterface.c
Author:             ssj
Description:        CAN信号接口处理
************************************************************************************************/
/************************************************************************************************
                                   C O P Y R I G H T
-------------------------------------------------------------------------------
Copyright (c) 2013-2025 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved.
************************************************************************************************/

/********************************************************************************
**  Include files
********************************************************************************/

#include "Srvl_CanSignals.h"
#include "Cdd_Hall.h"
#include "Srvl_E2memory.h"
#include "Rte_CanInterface.h"
#include "CANDrv.h"
#include "Rte_VfbInterface.h"

/*
*******************************************************************************
**  variables define
*******************************************************************************
*/

/*************************************************************
* 函数名称：INT8U Rte_GetCAN_PosiPercent(INT8U i)
* 功能描述：位置百分比
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
INT8U Rte_GetCAN_PosiPercent(INT8U i)
{
	strADCHALLDATA  Seat_Posi = Cdd_HallDataGet();
	INT8U u8Pos = 0;
	INT16U RealPwm = 0;

	if(Seat_Posi.HallPwmCnt[i] >= D_ADC_HALL_DEF)
	{
		RealPwm = Seat_Posi.HallPwmCnt[i] - D_ADC_HALL_DEF;
		if(RealPwm > Seat_Posi.StopPosCnt[i])
		{
			RealPwm = Seat_Posi.StopPosCnt[i];
		}
		u8Pos = 100 + (100 * RealPwm) / (Seat_Posi.StopPosCnt[i]);
	}
	else
	{
		RealPwm = D_ADC_HALL_DEF - Seat_Posi.HallPwmCnt[i];
		if(RealPwm > Seat_Posi.StopPosCnt[i])
		{
			RealPwm = Seat_Posi.StopPosCnt[i];
		}
		u8Pos = 100 - (100 * RealPwm) / (Seat_Posi.StopPosCnt[i]);
	}

	return u8Pos;
}
/***********************************************************************************************
* @function name: Rte_GetCAN_Gear_PN_Flag
* @description: 获取当前是否处于 P/N 挡状态，依据车型和当前挡位判断。
* @input parameters: 无
* @output parameters: 无
* @return: BOOL - TRUE 表示为 P/N 挡，FALSE 表示非 P/N 挡或数据无效
* @note: 挡位来源依赖车型配置与 CAN 报文是否丢失
* @author: ssj 2025-04-23
***********************************************************************************************/
BOOL Rte_GetCAN_Gear_PN_Flag(void)
{
	INT8U Gear = 0;
	BOOL LostFlag = FALSE;
	static BOOL PN_Flag = FALSE;
	INT8U EngineCfg = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg);

	if(FALSE == EngineCfg)
	{
		/*油车*/
		Gear = CanRx_0x238_TCU_GearSelDisp();
		LostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x238);
	}
	else
	{
		/*电车*/
		Gear = CanRx_0x26E_VCU_GearSelDisp();
		LostFlag = Ecual_GetCanMsgLostFlag(eRXINDEX_0x26E);
	}

	if((TRUE == LostFlag)
	|| (0 == Gear)
	|| (6 == Gear))
	{
		PN_Flag = TRUE;
	}
	else if((5 == Gear)
	|| (6 == Gear)
	|| (0xf == Gear))
	{
		PN_Flag = FALSE;
	}
	else
	{

	}

	return PN_Flag;
}
/***********************************************************************************************
* @function name:  Rte_SetCanEvent_0x3B2
* @description:    设置ID为0x3B2的PE消息的事件发送参数
* @input parameters:     无
* @output parameters:     无
* @return:         void
* @note:
* @author:         ssj + 2025-04-24 10:08
***********************************************************************************************/
void Rte_SetCanEvent_0x3B2(INT16U temp)
{
	Ecual_SetPEMsgEventTrigger(eDSMG_0x3B2);
}
/***********************************************************************************************
* @function name:  Rte_GetCanEventSendTimes_0x3B2
* @description:    获取ID为0x3B2消息的事件发送是否完成
* @input parameters:     void
* @output parameters:     无
* @return:         INT8U
* @note:
* @author:         ssj + 2025-04-24 10:10
***********************************************************************************************/
BOOL Rte_GetCanEventSendTimes_0x3B2(void)
{
	BOOL Flag = FALSE;

	if(CANDrvPEMsgOpt.pMsgInfoTbl[eDSMG_0x3B2].SndTimes == 0)
	{
		Flag = TRUE;
	}
	return Flag;
}
/***********************************************************************
* @function name: Ecual_CanGetDrvHeatLvl
*
* @description: 主驾加热档位获取
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-5-24 10:11:34
***********************************************************************/
INT8U Ecual_CanGetDrvHeatLvl(void)
{
	return DSM.dsm.DSM_St_DriSeatHeatGear;
}
/***********************************************************************
* @function name: Ecual_CanGetPasHeatLvl
*
* @description: 副驾加热档位获取
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-5-24 10:10:35
***********************************************************************/
INT8U Ecual_CanGetPasHeatLvl(void)
{
	return DSM.dsm.DSM_St_PasSeatHeatGear;
}
/***********************************************************************
* @function name: Ecual_CanGetThirdHeatLvl
*
* @description: 三排加热档位获取
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:10:35
***********************************************************************/
INT8U Ecual_CanGetThirdHeatLvl(void)
{
    return 0;
}
/***********************************************************************
* @function name: Ecual_CanGetHeatMsgLostFlag
*
* @description: 加热信号丢失
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetHeatMsgLostFlag(void)
{
    return FALSE;
}
/***********************************************************************
* @function name: Ecual_CanSetDrvHeatSts
*
* @description:  主驾加热工作状态
*
* @input parameters:
*
* @output parameters:
*
* @return:
*
* @note:
*
* @author: Prima Niu
*
* @date: 2022-03-25 20:15
***********************************************************************/
void Ecual_CanSetDrvHeatSts(INT8U Sts)
{
	INT8U TxSts = 0x0U;

	if(TRUE == Rte_GetVfb_DrHeatEnable())
	{
		TxSts = Sts;
	}
	CanTx_0x3B2_DSM_St_DriSeatHeatSW(TxSts);
}
/***********************************************************************
 * @function name: Ecual_CanSetPasHeatSts
 *
 * @description: 副驾加热状态
 *
 * @input parameters:
 *
 * @output parameters:
 *
 * @return:
 *
 * @note:
 *
 * @author: Prima Niu
 *
 * @date: 2022-03-25 20:19
 ***********************************************************************/
void Ecual_CanSetPasHeatSts(INT8U Sts)
{
	INT8U TxSts = 0x0U;

	if(TRUE == Rte_GetVfb_SecondHeatEnable())
	{
		TxSts = Sts;
	}
	CanTx_0x3B2_DSM_St_PasSeatHeatSW(TxSts);
}
/***********************************************************************
* @function name: Ecual_CanSetThirdHeatSts
*
* @description: 第三加热状态
*
* @input parameters:
*
* @output parameters:
*
* @return:
*
* @note:
*
* @author: Prima Niu
*
* @date: 2022-03-25 20:19
***********************************************************************/
void Ecual_CanSetThirdHeatSts(INT8U Sts)
{
	INT8U TxSts = 0x0U;

	if(TRUE == Rte_GetVfb_ThirdHeatEnable())
	{
		TxSts = Sts;
	}
	CanTx_0x3B2_DSM_SwsHeatSts(TxSts);
}
/***********************************************************************
* @function name: Ecual_CanGetDriver_HMI_VentilateMsg
*
* @description: 主驾大屏通风信号
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetDriver_HMI_VentilateMsg(void)
{
	return CanRx_0x351_IVI_FLSeatVentnSet();
}

/***********************************************************************
* @function name: Ecual_CanGetDriver_Tbox_VentilateMsg
*
* @description: 主驾远程通风信号状态
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetDriver_Tbox_VentilateMsg(void)
{
	return CanRx_0x281_BDC_TBOX_Req_DrSeatVentilating();
}

/***********************************************************************
* @function name: Ecual_CanGetPassenger_HMI_VentilateMsg
*
* @description: 副驾大屏通风信号
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetPassenger_HMI_VentilateMsg(void)
{
	return CanRx_0x351_IVI_FRSeatVentnSet();
}

/***********************************************************************
* @function name: Ecual_CanGetPassenger_Tbox_VentilateMsg
*
* @description: 副驾远程通风信号
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetPassenger_Tbox_VentilateMsg(void)
{
	return CanRx_0x281_BDC_TBOX_Req_PaSeatVentilating();
}

/***********************************************************************
* @function name: Ecual_CanGetThird_HMI_VentilateMsg
*
* @description: 三排大屏通风信号
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetThird_HMI_VentilateMsg(void)
{
	return FALSE;
}

/***********************************************************************
* @function name: Ecual_CanGetThird_Tbox_VentilateMsg
*
* @description: 三排通风远程信号
*
* @input parameters:
*
* @output parameters: INT8U
*
* @return: INT8U
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
INT8U Ecual_CanGetThird_Tbox_VentilateMsg(void)
{
	return FALSE;
}
/***********************************************************************
* @function name: Ecual_CanGetDrvVentLvl
*
* @description: 主驾通风档位获取
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-5-24 10:11:34
***********************************************************************/
INT8U Ecual_CanGetDrvVentLvl(void)
{
	return DSM.dsm.DSM_St_DriSeatVentilationGear;
}
/***********************************************************************
* @function name: Ecual_CanGetPasVentLvl
*
* @description: 副驾通风档位获取
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:10:35
***********************************************************************/
INT8U Ecual_CanGetPasVentLvl(void)
{
	return DSM.dsm.DSM_St_PasSeatVentilationGear;
}
/***********************************************************************
* @function name: Ecual_CanGetThirdVentLvl
*
* @description: 三排通风档位设置
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-5-24 10:10:35
***********************************************************************/
INT8U Ecual_CanGetThirdVentLvl(void)
{
	return 0;
}
/***********************************************************************
* @function name: Ecual_CanSetDrvVentLvl
*
* @description: 主驾通风档位设置
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:11:34
***********************************************************************/
void Ecual_CanSetDrvVentLvl(INT8U Lvl)
{
    Lvl = (Lvl == 0)?(1):(Lvl);
	CanTx_0x3B2_DSM_St_DriSeatVentilationGear(Lvl-1);
}
/***********************************************************************
* @function name: Ecual_CanSetDrvVentSts
*
* @description: 主驾通风状态
*
* @input parameters:
*
* @output parameters:
*
* @return:
*
* @note:
*
* @author: Prima Niu
*
* @date: 2022-03-25 20:30
***********************************************************************/
void Ecual_CanSetDrvVentSts(INT8U Sts)
{
	INT8U TxSts = 0x0U;

	if(TRUE == Rte_GetVfb_DrVentEnable())
	{
		TxSts = Sts;
	}
	CanTx_0x3B2_DSM_St_DriSeatVentilationSW(TxSts);
}
/***********************************************************************
* @function name: Ecual_CanSetThirdVentLvl
*
* @description: 三排通风档位设置
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:10:35
***********************************************************************/
void Ecual_CanSetThirdVentLvl(INT8U Lvl)
{

}
/***********************************************************************
* @function name: Ecual_CanSetPasVentLvl
*
* @description: 副驾通风档位设置
*
* @input parameters: INT8U
*
* @output parameters: void
*
* @return: void
*
* @note:
*
* @author: czy
*
* @date: 2024-1-8 10:10:35
***********************************************************************/
void Ecual_CanSetPasVentLvl(INT8U Lvl)
{
    Lvl = (Lvl == 0)?(1):(Lvl);
	CanTx_0x3B2_DSM_St_PasSeatVentilationGear(Lvl-1);
}
/***********************************************************************
* @function name: Ecual_CanSetPasVentSts
*
* @description: 副驾通风状态
*
* @input parameters:
*
* @output parameters:
*
* @return:
*
* @note:
*
* @author: Prima Niu
*
* @date: 2022-03-25 20:30
***********************************************************************/
void Ecual_CanSetPasVentSts(INT8U Sts)
{
	INT8U TxSts = 0x0U;

	if(TRUE == Rte_GetVfb_SecondVentEnable())
	{
		TxSts = Sts;
	}
	CanTx_0x3B2_DSM_St_PasSeatVentilationSW(TxSts);
}
