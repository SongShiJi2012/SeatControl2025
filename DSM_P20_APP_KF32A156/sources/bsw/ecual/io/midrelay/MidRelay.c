/****************************Copyright (c)**************************************************
**                    Shenzhen Southern Dare Automotive Electronics Co.,LTD.
**
**                           http://www.fzb.com.cn
**-------------------------------------File Info--------------------------------------------
** File Name:               MidRelay.c
** Last modified Date:      2019.3.14
** Last Version:            V1.1.0
** Description:				�̵���������ص��м��
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2019.3.12
** Version:                 V1.0.0
** Descriptions:
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/

/*
**********************************************************************************************************
					INCLUDES
**********************************************************************************************************
*/
#include "MidRelay.h"
#include "ecual_ftm.h"
#include "DescConfig.h"
#include "CpuPeripheralInit.h"
#include "Cdd_Ntc.h"
#include "Srvl_PowerMode.h"
#include "Rte_VfbInterface.h"
#include "Srvl_Tle9210x.h"
#include "ecual_pins.h"

/*
**********************************************************************************************************
					MACROS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					TYPEDEFS
**********************************************************************************************************
*/


/*
**********************************************************************************************************
					CONSTANTS
**********************************************************************************************************
*/



/*
**********************************************************************************************************
					GLOBAL VARIABLES
**********************************************************************************************************
*/
ST_MIDRELAY_STATUS	stgMidRelayStatusCmd;

EN_MOTOR_MOVE swMotorMove[12]={0};
ST_MemorySet	MemorySet;

ST_PID SeatDRHeatPID; // DR PID Control Structure
ST_PID SeatPAHeatPID; // PA PID Control Structure

ST_HEATPWM HeatPWM;  //�����ݼ��ȵ�ʵʱռ�ձ�

INT16U SeatTempVal[3]={700,780,930}; //��Ӧ�¶ȵ�λ��30�� �� 38�棬 53��

#define D_MIDRELAY_VENT_LVL1   (40U)
#define D_MIDRELAY_VENT_LVL2   (50U)
#define D_MIDRELAY_VENT_LVL3   (70U)

/*-------------------------------------------------------------------------
* Function Name : PIDCalc
* Description   : PID����
* Date          : 2019/10/05
* Parameter     :ST_PID *pp, INT16U PreTemp
* Return Code   :PWM
* Author        :Kin Chen
-------------------------------------------------------------------------*/
INT16U PIDCalc(ST_PID *pid, INT16U PreTemp)
{
	INT32U dError,Error;
    Error = pid->SetPoint - PreTemp;         // ƫ��
    pid->SumError += Error;                  // ����
    dError = Error - pid->LastError;    	 // ��ǰ΢��
    pid->LastError = Error;
    return (pid->Proportion * Error          // ������
	    + pid->Integral * pid->SumError      // ������
	    + pid->Derivative * dError);         // ΢����
}
/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatHeatDRCmdCtrlProc
* Description   : �������μ��ȿ���
* Date          : 2019/10/05
* Parameter     :void
* Return Code   :void
* Author        :Kin Chen
-------------------------------------------------------------------------*/
static void MidRelay_SeatHeatDRCmdCtrlProc(void)
{
	static INT8U Tmr_Dr = 0;
	static INT8U DrPwmCnt = 0;

	ST_ScanTempVal SEAT_TEMP = Cdd_Ntc_GetTemp();

	SeatDRHeatPID.Proportion = 18.0; 	// Set PID Coefficients  �������� Proportional Const
	SeatDRHeatPID.Integral = 0;    //���ֳ��� Integral Const
	SeatDRHeatPID.Derivative = 0;   //΢�ֳ��� Derivative Const

    if(EN_LVL_OFF == SEAT_HEAT_DR_CMD_Get())
	{
		Tmr_Dr = 0;
		DrPwmCnt = 0;
		HeatPWM.DR_HEAT_PWM = 0;
//    	PWR_SEAT_HEAT_DR_OFF();
	}
    else
    {

    	SeatDRHeatPID.SetPoint = SeatTempVal[SEAT_HEAT_DR_CMD_Get()-1u];

    	if(SeatDRHeatPID.SetPoint > SEAT_TEMP.SeatHeatDRNtc)
		{
			//���3�����ϣ�ȫ����100����
			if((SeatDRHeatPID.SetPoint - SEAT_TEMP.SeatHeatDRNtc) >= 30u)
			{
				HeatPWM.DR_HEAT_PWM = 100;
			}
			else
			{
				//����500MS����һ��PWM��ֵ
				if(++Tmr_Dr >= 100u)
				{
					Tmr_Dr = 0;
					DrPwmCnt = 0;
					HeatPWM.DR_HEAT_PWM = PIDCalc(&SeatDRHeatPID , SEAT_TEMP.SeatHeatDRNtc);

					//����-Ϊ0
					if(HeatPWM.DR_HEAT_PWM & 0x8000u)
					{
						HeatPWM.DR_HEAT_PWM = 0;
					}
					else
					{
						if(HeatPWM.DR_HEAT_PWM > 100u)
						{
							HeatPWM.DR_HEAT_PWM=100;
						}
					}

				}
			}
		}
		else
		{
			HeatPWM.DR_HEAT_PWM = 0;
		}

		DrPwmCnt++;
		if(DrPwmCnt <= HeatPWM.DR_HEAT_PWM)
		{
//			PWR_SEAT_HEAT_DR_ON();
		}
		else if(DrPwmCnt <= 100u)
		{
//			PWR_SEAT_HEAT_DR_OFF();
		}
		else
		{
			DrPwmCnt = 0;
		}
    }

}
/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatHeatPACmdCtrlProc
* Description   : �������μ��ȿ���
* Date          : 2019/10/05
* Parameter     : void
* Return Code   : void
* Author        : Kin Chen
-------------------------------------------------------------------------*/
static void MidRelay_SeatHeatPACmdCtrlProc(void)
{
	static INT8U Tmr_Pa = 0;
	static INT8U PaPwmCnt = 0;

	ST_ScanTempVal SEAT_TEMP = Cdd_Ntc_GetTemp();

	SeatPAHeatPID.Proportion = 18.0; 	// Set PID Coefficients  �������� Proportional Const
	SeatPAHeatPID.Integral = 0;    //���ֳ��� Integral Const
	SeatPAHeatPID.Derivative = 0;   //΢�ֳ��� Derivative Const

	if(EN_LVL_OFF == SEAT_HEAT_PA_CMD_Get())
	{
    	Tmr_Pa = 0;
    	PaPwmCnt = 0;
    	HeatPWM.PA_HEAT_PWM = 0;
//		PWR_SEAT_HEAT_PA_OFF();
	}
    else
    {
    	SeatPAHeatPID.SetPoint = SeatTempVal[SEAT_HEAT_PA_CMD_Get()-1];

    	if(SeatPAHeatPID.SetPoint > SEAT_TEMP.SeatHeatPANtc)
    	{
    		//���3�����ϣ�ȫ����100����
    		if((SeatPAHeatPID.SetPoint - SEAT_TEMP.SeatHeatPANtc) >= 30)
    		{
    			HeatPWM.PA_HEAT_PWM = 100;
    		}
    		else
    		{
    			//����500MS����һ��PWM��ֵ
    			if(++Tmr_Pa >= 100)
    			{
    				Tmr_Pa = 0;
    				PaPwmCnt = 0;
    				HeatPWM.PA_HEAT_PWM = PIDCalc(&SeatPAHeatPID , SEAT_TEMP.SeatHeatPANtc);

    				//����-Ϊ0
    				if(HeatPWM.PA_HEAT_PWM & 0x8000u)
    				{
    					HeatPWM.PA_HEAT_PWM = 0;
    				}
    				else
    				{
    					if(HeatPWM.PA_HEAT_PWM > 100u)
    					{
    						HeatPWM.PA_HEAT_PWM=100;
    					}
    				}

    			}
    		}
    	}
    	else
    	{
    		HeatPWM.PA_HEAT_PWM = 0;
    	}

    	PaPwmCnt++;
    	if(PaPwmCnt <= HeatPWM.PA_HEAT_PWM)
    	{
//    		PWR_SEAT_HEAT_PA_ON();
    	}
    	else if(PaPwmCnt <= 100)
    	{
//    		PWR_SEAT_HEAT_PA_OFF();
    	}
    	else
    	{
    		PaPwmCnt = 0;
    	}
    }

}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatHeatCmdCtrlProc
* Description   : �����μ��ȿ���
* Date          : 2019/March/22
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
static void MidRelay_SeatHeatCmdCtrlProc(void)
{
/*���ݼ���*/
	if(FALSE != Rte_GetVfb_DrHeatIo())
	{
		Ecual_GpioWriteCh(EN_DrHeatOut,EN_GPIO_LEV_HIGH);
	}
	else
	{
		Ecual_GpioWriteCh(EN_DrHeatOut,EN_GPIO_LEV_LOW);
	}
/*���ݼ���*/	
	if(FALSE != Rte_GetVfb_PaHeatIo())
	{
		Ecual_GpioWriteCh(EN_PaHeatOut,EN_GPIO_LEV_HIGH);
	}
	else
	{
		Ecual_GpioWriteCh(EN_PaHeatOut,EN_GPIO_LEV_LOW);
	}
}

/***********************************************************************************************
 * @function name:  MidRelay_SeatVenDrCmdCtrlProc
 * @description:    ��������ͨ����ƴ�����������״̬���� PWM ռ�ձ�
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
static void MidRelay_SeatVenDrCmdCtrlProc(void)
{
	static BOOL DiffStFlg = FALSE;
	static EN_LVL PreState = EN_LVL_Max;
	EN_LVL CurState = Rte_GetVfb_DrVent();

	/* ���״̬�Ƿ��б仯 */
	if(PreState != CurState)
	{
		DiffStFlg = TRUE;
	}

	if(TRUE == DiffStFlg)
	{
		DiffStFlg = FALSE;
		switch(CurState)
		{
			case EN_LVL_OFF:
				Ecual_UpDateDrVentDuty(0);
				break;
			case EN_LVL_1:
				Ecual_UpDateDrVentDuty(D_VENT_LVL_1_PRECENT);
				break;
			case EN_LVL_2:
				Ecual_UpDateDrVentDuty(D_VENT_LVL_2_PRECENT);
				break;
			case EN_LVL_3:
				Ecual_UpDateDrVentDuty(D_VENT_LVL_3_PRECENT);
				break;
			default:
				Ecual_UpDateDrVentDuty(0);
				break;
		}
	}

	PreState = CurState;
}
/***********************************************************************************************
 * @function name:  MidRelay_SeatVenPaCmdCtrlProc
 * @description:    ��������ͨ����ƴ�����������״̬���� PWM ռ�ձ�
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-10
 ***********************************************************************************************/
static void MidRelay_SeatVenPaCmdCtrlProc(void)
{
	static BOOL DiffStFlg = FALSE;
	static EN_LVL PreState = EN_LVL_Max;
	EN_LVL CurState = Rte_GetVfb_PaVent();

	/* ���״̬�Ƿ��б仯 */
	if(PreState != CurState)
	{
		DiffStFlg = TRUE;
	}

	if(TRUE == DiffStFlg)
	{
		DiffStFlg = FALSE;
		switch(CurState)
		{
			case EN_LVL_OFF:
				Ecual_UpDatePaVentDuty(0);
				break;
			case EN_LVL_1:
				Ecual_UpDatePaVentDuty(D_VENT_LVL_1_PRECENT);
				break;
			case EN_LVL_2:
				Ecual_UpDatePaVentDuty(D_VENT_LVL_2_PRECENT);
				break;
			case EN_LVL_3:
				Ecual_UpDatePaVentDuty(D_VENT_LVL_3_PRECENT);
				break;
			default:
				Ecual_UpDatePaVentDuty(0);
				break;
		}
	}

	PreState = CurState;
}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_WheelHeatCmdCtrlProc
* Description   : �����̼��ȿ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_WheelHeatCmdCtrlProc(void)
{

	if(FALSE != Rte_GetVfb_ThirdHeatIo())
	{
		Ecual_GpioWriteCh(EN_WheelHeatCtrlOut,EN_GPIO_LEV_HIGH);
	}
	else
	{
		Ecual_GpioWriteCh(EN_WheelHeatCtrlOut,EN_GPIO_LEV_LOW);
	}

}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatHeightCmdCtrlProc
* Description   : ���θ߶ȵ��ڿ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatHeightCmdCtrlProc(void)
{
	//��������
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_DrHeightMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_DrHeightMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_RevRot);
	}
	else
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_OFF);
	}
}
/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatLengthCmdCtrlProc
* Description   : ����������ڿ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatLengthCmdCtrlProc(void)
{
	//��������
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_DrLengthMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_DrLengthMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_RevRot);
    }
    else
    {
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_OFF);
	}
}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatBackRestCmdCtrlProc
* Description   : ���ο����Ƕȵ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatBackRestCmdCtrlProc(void)
{
	//��������
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_DrBackMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_DrBackMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_RevRot);
    }
    else
    {
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_OFF);
	}
}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatFrontHeightCmdCtrlProc
* Description   : ����ǰ���Ƕȵ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatFrontHeightCmdCtrlProc(void)
{
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_DrFrontMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_DrFrontMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_RevRot);
    }
    else
    {
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_OFF);
	}

}
/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatHeatComGNDCmdCtrlProc
* Description   : ���μ��ȵؿ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
static void MidRelay_SeatHeatComGNDCmdCtrlProc(void)
{
//	if(TRUE == SEAT_HEAT_COM_GND_CMD_Get())
//	{
//		OUTPUT_SEAT_HEAT_COM_DRI_ON();
//	}
//	else
//	{
//		OUTPUT_SEAT_HEAT_COM_DRI_OFF();
//	}
}


/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatPaHeightCmdCtrlProc
* Description   : ���ݸ߶ȵ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatPaHeightCmdCtrlProc(void)
{

}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatPaLengthCmdCtrlProc
* Description   : ���θ����������
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatPaLengthCmdCtrlProc(void)
{
	//��Ͽ���
//	if(DescIOCtl_SeatHeadrest_Active == eIOCTL_ACTIVE)
//	{
//		SEAT_HEADREST_HEIGHT_CMD_Set((DescIOCtl_AllSeatHeadrest_Cmd&0x03));
//	}

	//��������
	swMotorMove[4] = SEAT_HEADREST_HEIGHT_CMD_Get();
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_PaLengthMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_PaLengthMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_RevRot);
    }
    else
    {
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_OFF);
	}
}

/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatPaBackrestCmdCtrlProc
* Description   : ���θ��ݿ�������
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatPaBackrestCmdCtrlProc(void)
{
	//��Ͽ���
//	if(DescIOCtl_SeatcushionLength_Active == eIOCTL_ACTIVE)
//	{
//		SEAT_CUSHION_LENGTH_CMD_Set((DescIOCtl_AllSeatcushionLength_Cmd&0x03));
//	}

	//��������
	swMotorMove[5] = SEAT_CUSHION_LENGTH_CMD_Get();
	if(EN_MOTOR_UP_FW_LF == Rte_GetVfb_PaBackMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_ForRot);
	}
	else if(EN_MOTOR_DN_BW_RT == Rte_GetVfb_PaBackMotorCmd())
	{
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_RevRot);
    }
    else
    {
        Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_OFF);
	}


}


/*-------------------------------------------------------------------------
* Function Name : MidRelay_SeatPaFrontCmdCtrlProc
* Description   : ����ǰ���߶ȵ���
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_SeatPaFrontCmdCtrlProc(void)
{

}


/*-------------------------------------------------------------------------
* Function Name : MidRelay_WheelLengthCmdCtrlProc
* Description   : ������ǰ�����
* Date          : 2019/March/23
* Parameter     :
* Return Code   :
* Author        : 
-------------------------------------------------------------------------*/
static void MidRelay_WheelLengthCmdCtrlProc(void)
{
	//��Ͽ���
//	if(DescIOCtl_AllSteeringWheelFdBk_Cmd == eIOCTL_ACTIVE)
//	{
//		WHEEL_LENGTH_CMD_Set((DescIOCtl_AllSteeringWheelFdBk_Cmd&0x03));
//	}

	//��������
//	swMotorMove[7] = WHEEL_HEIGHT_CMD_Get();
//	if(EN_MOTOR_UP_FW_LF == WHEEL_LENGTH_CMD_Get())
//	{
//		OUTPUT_STEERING_WHEEL_FW_DRI_ON();
//		OUTPUT_STEERING_WHEEL_BK_DRI_OFF();
//	}
//	else if(EN_MOTOR_DN_BW_RT == WHEEL_LENGTH_CMD_Get())
//	{
//		OUTPUT_STEERING_WHEEL_FW_DRI_OFF();
//		OUTPUT_STEERING_WHEEL_BK_DRI_ON();
//	}
//	else
//	{
//		OUTPUT_STEERING_WHEEL_FW_DRI_OFF();
//		OUTPUT_STEERING_WHEEL_BK_DRI_OFF();
//	}

}




/*������Ʊ�*/
ST_OUTPUT_MOTOR_CTRL stgOutputMotorCtrlTbl =
{
	{
		{TRUE,			MidRelay_SeatHeatCmdCtrlProc},
		{DSM_ALL_SW,	MidRelay_SeatHeatComGNDCmdCtrlProc},
		{TRUE,			MidRelay_SeatVenDrCmdCtrlProc},
		{TRUE,			MidRelay_SeatVenPaCmdCtrlProc},
		{TRUE,	        MidRelay_WheelHeatCmdCtrlProc},
				
		{TRUE,			MidRelay_SeatHeightCmdCtrlProc},
		{TRUE,			MidRelay_SeatLengthCmdCtrlProc},
		{TRUE,			MidRelay_SeatBackRestCmdCtrlProc},
		{TRUE,			MidRelay_SeatFrontHeightCmdCtrlProc},
		{DSM_ALL_SW,	MidRelay_SeatPaHeightCmdCtrlProc},
		{TRUE,	        MidRelay_SeatPaLengthCmdCtrlProc},
		{TRUE,	        MidRelay_SeatPaBackrestCmdCtrlProc},
		{DSM_ALL_SW,	MidRelay_SeatPaFrontCmdCtrlProc},
	}
};




/*-------------------------------------------------------------------------
* Function Name : MidRelay_MotorCtrlProc
* Description   : ����м�����
* Date          : 2019/March/22
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void MidRelay_MotorCtrlProc(void)
{
	INT8U i = 0;
	for(i = 0; i < EN_MOTOR_MAX; i++)
	{
		if(TRUE == stgOutputMotorCtrlTbl.stMotorInfo[i].IsCtrl)
		{
			/*��MOTOR���Կ���*/
			stgOutputMotorCtrlTbl.stMotorInfo[i].pFuncMotorCtrl();
		}
	}
}


