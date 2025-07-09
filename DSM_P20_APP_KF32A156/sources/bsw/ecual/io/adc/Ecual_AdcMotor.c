/*
 * Ecual_AdcMotor.c
 *
 *  Created on: 2025-3-26
 *      Author: Administrator
 */
#include "Ecual_AdcMotor.h"
#include "Srvl_PowerMode.h"
#include "ecual_pins.h"
#include "MidRelay.h"
#include "Rte_VfbInterface.h"
#include "Ecual_Adc.h"

static INT16U SeatAdjSw_UP_MIN = 0;
static INT16U SeatAdjSw_UP_MAX = 0;
static INT16U SeatAdjSw_DN_MIN = 0;
static INT16U SeatAdjSw_DN_MAX = 0;
static INT16U SeatAdjSw_CLOSE = 0;

static INT16U MotorCurrMax_Len = 750;        //纵向堵转阈值电流
static INT16U MotorCurrMax_Front = 750;        //腿托堵转阈值电流
static INT16U MotorCurrMax_HeiBack = 500; 	 //高度、椅背堵转阈值电流公用
ST_ScanMotorState ScanMotorStateFlag = {0};
typedef INT8U (*MotorCmdGetter)(void);   // 定义一个函数指针类型，返回EN_MOTOR_MOVE

static void Ecual_SetDrHeightSwitchCmd(void);
static void Ecual_SetDrLengthSwitchCmd(void);
static void Ecual_SetDrBackSwitchCmd(void);
static void Ecual_SetDrFrontSwitchCmd(void);
static void Ecual_SetPaLengthSwitchCmd(void);
static void Ecual_SetPaBackSwitchCmd(void);


static void Ecual_CheckSeatCurrAdMinMax(void);

static void Ecual_SetMotorOverCurrentFlag(eADCCH ADC_ChannelID, INT16U OverCurrentThreshold, BOOL* pOverCurrentFlag);
static void Ecual_CheckMotorOverCurrents(void);
static void Ecual_UpdateAllRelayFlags(void);
static void Ecual_SetRelayFlag(MotorCmdGetter getMotorCmd, UN_RelayIOState *pRelayDriveSts);
/***********************************************************************************************
 * @function name: Ecual_SetDrHeightSwitchCmd
 * @description:  设置主驾高度调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrHeightSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRHeightForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRHeightBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrHeightSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrLengthSwitchCmd
 * @description:  设置主驾纵向调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrLengthSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRLengthForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRLengthBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrLengthSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrBackSwitchCmd
 * @description:  设置主驾靠背调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrBackSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRBackForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRBackBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrBackSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetDrFrontSwitchCmd
 * @description:  设置主驾腿托调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetDrFrontSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_DRFrontForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_DRFrontBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.DrFrontSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetPaLengthSwitchCmd
 * @description:  设置副驾纵向调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetPaLengthSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_PALengthForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_PALengthBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.PaLengthSwitch = EN_SW_DEF;
	}
}
/***********************************************************************************************
 * @function name: Ecual_SetPaBackSwitchCmd
 * @description:  设置副驾靠背调节开关状态，优先判断向前和向后是否同时有效，向前有效则设置向前，否则判断向后，均无效则设置默认
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-28
 ***********************************************************************************************/
static void Ecual_SetPaBackSwitchCmd(void)
{
	BOOL forwardStatus = Ecual_GetDigitalSwStatus(EN_PABackForwardSW);
	BOOL backwardStatus = Ecual_GetDigitalSwStatus(EN_PABackBackwardSW);

	if((forwardStatus == TRUE) && (backwardStatus == TRUE))
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DEF;
	}
	else if(forwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_UP_FW_LF;
	}
	else if(backwardStatus == TRUE)
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DN_BW_RT;
	}
	else
	{
		ScanMotorStateFlag.PaBackSwitch = EN_SW_DEF;
	}
}

/***********************************************************************************************
 * @function name:  Ecual_CheckSeatCurrAdMinMax
 * @description:	堵转电流阈值设定
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
static void Ecual_CheckSeatCurrAdMinMax(void)
{
	//待标定
}
/***********************************************************************************************
 * @function name:  Ecual_SetMotorOverCurrentFlag
 * @description:    检测电机电流是否超过堵转阈值，并更新状态标志位
 * @input parameters: eADCCH ADC_ChannelID - ADC通道枚举ID
 *                    INT16U OverCurrentThreshold - 堵转电流阈值
 *                    BOOL* pOverCurrentFlag - 结果存储的标志位地址
 * @output parameters: void
 * @return:         void
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_SetMotorOverCurrentFlag(eADCCH ADC_ChannelID, INT16U OverCurrentThreshold, BOOL* pOverCurrentFlag)
{
    if(TRUE == Ecual_GetMesFinishFlg(ADC_ChannelID))
    {
        if(Ecual_GetAD_MesVal(ADC_ChannelID) >= OverCurrentThreshold)
        {
            *pOverCurrentFlag = TRUE;
        }
        else
        {
            *pOverCurrentFlag = FALSE;
        }
    }
}

/***********************************************************************************************
 * @function name:  Ecual_CheckMotorOverCurrents
 * @description:    统一检测6个电机的堵转电流状态，更新对应标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         void
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_CheckMotorOverCurrents(void)
{
    Ecual_SetMotorOverCurrentFlag(enADC_DrHeightMotorIS, MOTOR_CURR_MAX_DR_HEIGHT, &ScanMotorStateFlag.DrHeightOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrLengthMotorIS, MOTOR_CURR_MAX_DR_LENGTH, &ScanMotorStateFlag.DrLengthOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrBackMotorIS, MOTOR_CURR_MAX_DR_BACK, &ScanMotorStateFlag.DrBackOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_DrFrontMotorIS, MOTOR_CURR_MAX_DR_FRONT, &ScanMotorStateFlag.DrFrontOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_PaLengthMotorIS, MOTOR_CURR_MAX_PA_LENGTH, &ScanMotorStateFlag.PaLengthOverCurrentFlag);
    Ecual_SetMotorOverCurrentFlag(enADC_PaBackMotorIS, MOTOR_CURR_MAX_PA_BACK, &ScanMotorStateFlag.PaBackOverCurrentFlag);
}

/***********************************************************************************************
 * @function name:  Ecual_SetRelayFlag
 * @description:    通用继电器状态更新接口 -
 * 根据传入的电机命令接口和继电器状态指针更新状态位
 * 由于P20没有继电器 不修改模型 只用电机命令适配模型接口
 * @input parameters:     MotorCmdGetter getMotorCmd - 获取电机命令的函数指针
 *                      UN_RelayIOState *pRelayDriveSts - 继电器状态变量指针
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_SetRelayFlag(MotorCmdGetter getMotorCmd, UN_RelayIOState *pRelayDriveSts)
{
    if((getMotorCmd == NULL) || (pRelayDriveSts == NULL))
    {
        return;
    }

    EN_MOTOR_MOVE enMotorCmd = getMotorCmd();

    if(enMotorCmd == EN_MOTOR_UP_FW_LF)
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = TRUE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = FALSE;
    }
    else if(enMotorCmd == EN_MOTOR_DN_BW_RT)
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = FALSE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = TRUE;
    }
    else
    {
        pRelayDriveSts->Bits.MOTOR_CURR_UP_NOLMAL = FALSE;
        pRelayDriveSts->Bits.MOTOR_CURR_DN_NOLMAL = FALSE;
    }
}
/***********************************************************************************************
 * @function name:  Ecual_UpdateAllRelayFlags
 * @description:    统一调用更新主驾和副驾所有电机继电器状态
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
static void Ecual_UpdateAllRelayFlags(void)
{
    Ecual_SetRelayFlag(Rte_GetVfb_DrHeightMotorCmd,   &ScanMotorStateFlag.DrHeightRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrLengthMotorCmd,   &ScanMotorStateFlag.DrLengthRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrBackMotorCmd,     &ScanMotorStateFlag.DrBackRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_DrFrontMotorCmd,    &ScanMotorStateFlag.DrFrontRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_PaLengthMotorCmd,   &ScanMotorStateFlag.PaLengthRelayDriveSts);
    Ecual_SetRelayFlag(Rte_GetVfb_PaBackMotorCmd,     &ScanMotorStateFlag.PaBackRelayDriveSts);
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagHeightUp
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagHeightUp()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagHeightDN
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagHeightDN()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagLenghtForward
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagLenghtForward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrLengthRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagLenghtBackward
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagLenghtBackward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrLengthRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagBackForward
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagBackForward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrBackRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagBackBackward
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagBackBackward()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrBackRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagFrontUp
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagFrontUp()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrFrontRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrRelayFlagFrontDown
 * @description:	获取继电器驱动状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Ecual_GetDrRelayFlagFrontDown()
{
	BOOL temp;

	if(TRUE == ScanMotorStateFlag.DrFrontRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
	{
		temp = TRUE;
	}
	else
	{
		temp = FALSE;
	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagLenghtForward
 * @description:    获取副驾纵向电机继电器前进（向前）驱动状态
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE表示继电器处于前进状态，FALSE表示非前进状态
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagLenghtForward(void)
{
    if(TRUE == ScanMotorStateFlag.PaLengthRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagLenghtBackward
 * @description:    获取副驾纵向电机继电器后退（向后）驱动状态
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE表示继电器处于后退状态，FALSE表示非后退状态
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagLenghtBackward(void)
{
    if(TRUE == ScanMotorStateFlag.PaLengthRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagBackForward
 * @description:    获取副驾靠背电机继电器前进（向前）驱动状态
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE表示继电器处于前进状态，FALSE表示非前进状态
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagBackForward(void)
{
    if(TRUE == ScanMotorStateFlag.PaBackRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***********************************************************************************************
 * @function name:  Ecual_GetPaRelayFlagBackBackward
 * @description:    获取副驾靠背电机继电器后退（向后）驱动状态
 * @input parameters:     void
 * @output parameters:    void
 * @return:         BOOL - TRUE表示继电器处于后退状态，FALSE表示非后退状态
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPaRelayFlagBackBackward(void)
{
    if(TRUE == ScanMotorStateFlag.PaBackRelayDriveSts.Bits.MOTOR_CURR_DN_NOLMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL Ecual_GetPaRelayFlagHeightUp()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagHeightDN()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagFrontUp()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
BOOL Ecual_GetPaRelayFlagFrontDown()
{
	BOOL temp;

//	if(TRUE == ScanMotorStateFlag.DrHeightRelayDriveSts.Bits.MOTOR_CURR_UP_NOLMAL)
//	{
//		temp = TRUE;
//	}
//	else
//	{
//		temp = FALSE;
//	}
	return temp;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrHeightSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrHeightSwitchCmd()
{
	return ScanMotorStateFlag.DrHeightSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrLengthSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrLengthSwitchCmd()
{
	return ScanMotorStateFlag.DrLengthSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrBackSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrBackSwitchCmd()
{
	return ScanMotorStateFlag.DrBackSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrFrontSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetDrFrontSwitchCmd()
{
	return ScanMotorStateFlag.DrFrontSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaLengthSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetPaLengthSwitchCmd()
{
	return ScanMotorStateFlag.PaLengthSwitch;
}
/***********************************************************************************************
 * @function name:  Ecual_GetPaBackSwitchCmd
 * @description:	获取硬线调节开关状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
EN_SW_TYPE Ecual_GetPaBackSwitchCmd()
{
	return ScanMotorStateFlag.PaBackSwitch;
}

EN_SW_TYPE Ecual_GetPaHeightSwitchCmd()
{
	return EN_SW_DEF;
}
EN_SW_TYPE Ecual_GetPaFrontSwitchCmd()
{
	return EN_SW_DEF;
}
/***********************************************************************************************
 * @function name:  Ecual_GetDrHeightOverCurrentFlag
 * @description:    获取主驾高度电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrHeightOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrHeightOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrLengthOverCurrentFlag
 * @description:    获取主驾纵向电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrLengthOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrLengthOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrBackOverCurrentFlag
 * @description:    获取主驾靠背电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrBackOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrBackOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetDrFrontOverCurrentFlag
 * @description:    获取主驾腿托电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetDrFrontOverCurrentFlag(void)
{
    return ScanMotorStateFlag.DrFrontOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetPrLengthOverCurrentFlag
 * @description:    获取副驾纵向电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPrLengthOverCurrentFlag(void)
{
    return ScanMotorStateFlag.PaLengthOverCurrentFlag;
}

/***********************************************************************************************
 * @function name:  Ecual_GetPrBackOverCurrentFlag
 * @description:    获取副驾靠背电机堵转电流标志位
 * @input parameters: void
 * @output parameters: void
 * @return:         BOOL - 堵转标志位状态
 * @note:
 * @author:         ssj 2025-05-30
 ***********************************************************************************************/
BOOL Ecual_GetPrBackOverCurrentFlag(void)
{
    return ScanMotorStateFlag.PaBackOverCurrentFlag;
}

BOOL Ecual_GetPrFrontOverCurrentFlag()
{
	return EN_SW_DEF;
}
BOOL Ecual_GetPrHeightOverCurrentFlag()
{
	return EN_SW_DEF;
}
/***********************************************************************************************
 * @function name:  Ecual_AdcMotorTask
 * @description:	检测任务
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
void Ecual_AdcMotorPollingTask()
{
	Ecual_SetDrHeightSwitchCmd();
	Ecual_SetDrLengthSwitchCmd();
	Ecual_SetDrBackSwitchCmd();
	Ecual_SetDrFrontSwitchCmd();
	Ecual_SetPaLengthSwitchCmd();
	Ecual_SetPaBackSwitchCmd();

	Ecual_CheckSeatCurrAdMinMax();

	Ecual_UpdateAllRelayFlags();
	Ecual_CheckMotorOverCurrents();
}
