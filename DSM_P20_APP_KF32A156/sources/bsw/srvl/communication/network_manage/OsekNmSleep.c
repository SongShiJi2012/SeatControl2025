
#include "OsekNmSleep.h"
//#include "uds_can.h"
#include "Rte_VfbInterface.h"
#include "DiagDTCGenerate.h"
//#include "Ecual_Gpio.h"
#include "Appl_DrMemory_CtrlModel.h"
#include "Appl_PaMemory_CtrlModel.h"
#include "CpuPeripheralInit.h"
#include "ecual_pins.h"
#include "ecual_wdog.h"

#define D_DelayTime		(5000UL)	//����������������ʱʱ��

INT8U LocalSleepFlag = 0;		//�����������߱�־λ
static INT32U s_delayTimer = 0;  //����������������ʱʱ���ʱ��
static INT8U s_SrvlDescSleepFlg = FALSE;

static void LocalSleepCheck(void);

void setLocalSleepFlag(INT8U flg)
{
	LocalSleepFlag = flg;
}

void resetS_delayTimer(void)
{
	s_delayTimer = D_HAL_GET_CUR_MS_TS();
}

/***********************************************************************************************
 * @function name:  SleepConditionCheck
 *
 * @description:   �����������
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    res  TRUE: ������������;	      	FALSE��δ������������
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2024-04-08
 ***********************************************************************************************/
BOOL SleepConditionCheck()
{	
    BOOL res = FALSE;

#ifdef D_STAY_AWAKE
    return FALSE;//DEBUG ����������
#endif

    LocalSleepCheck();//��ʱ����
    if((Ecual_CanGetUdsMsgRecFlg() == FALSE) 
    && TRUE == LocalSleepFlag)
    {
        res = TRUE;
    }
    return res;
}

/*��ʱ���ԣ������ĵ����߹�������
1��ϵͳ��ԴΪOFF
2�����ε���Ӳ������Ч���⵽����ճ������
3��δʹ�����ε��ڼ̵����ҵ��ڼ̵��������й���
4��δʹ�����μ���
5��δʹ������ͨ��
6��δ���յ���ϱ��� 
8��δ���յ����������(Sleep.Ind=0x0��Inactive) 
ע��������������������ʱ5s
*/
static void LocalSleepCheck(void)
{
	INT8U SWSt = FALSE;
	INT8U SWDTC = 0x00;
	INT8U MotorMove[8] = {0x0U};
	INT8U VenHeatOut[5] ={0x0u};
	INT8U PowMode = 0x0u ;
	INT8U MoveFlag = 0x0u ;
	INT8U HeatVenFlag = 0x0u ;
	INT8U DTCFault = 0;
	INT8U i,j = 0x0u;
	BOOL MemorySetValidFlag = FALSE;
    
    if(TRUE == Ecual_GetDigitalSwStatus(EN_DRLengthBackwardSW) \
    && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalBackwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRLengthForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalForwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRHeightBackwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightDownwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRHeightForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightUpwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRBackBackwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestBackwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRBackForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestForwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRFrontBackwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleBackwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_DRFrontForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleForwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_PABackBackwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestBackwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_PABackForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestForwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_PALengthBackwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalBackwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else if(TRUE == Ecual_GetDigitalSwStatus(EN_PALengthForwardSW) \
         && FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalForwardAdjustmentSwitchAdhesion))
    {
        SWSt = TRUE;
    }
    else
    {

    }
    
	MotorMove[0] = Rte_GetVfb_DrHeightMotorCmd();
	MotorMove[1] = Rte_GetVfb_DrLengthMotorCmd();
	MotorMove[2] = Rte_GetVfb_DrBackMotorCmd();
	MotorMove[3] = Rte_GetVfb_DrFrontMotorCmd();
	MotorMove[4] = Rte_GetVfb_PaHeightMotorCmd();
	MotorMove[5] = Rte_GetVfb_PaLengthMotorCmd();
	MotorMove[6] = Rte_GetVfb_PaBackMotorCmd();
	MotorMove[7] = Rte_GetVfb_PaFrontMotorCmd();
	if(MotorMove[0] == 0x00 && MotorMove[1] == 0x00 && MotorMove[2] == 0x00 && MotorMove[3] == 0x00 && \
		MotorMove[4] == 0x00 && MotorMove[5] == 0x00 && MotorMove[6] == 0x00 && MotorMove[7] == 0x00)
	{
		MoveFlag = 0x01;
	}
	else
	{
		MoveFlag = 0x00;
	}
	VenHeatOut[0]  = Rte_GetVfb_DrHeat();
	VenHeatOut[1]  = Rte_GetVfb_PaHeat();
	VenHeatOut[2] = Rte_GetVfb_DrVent();
	VenHeatOut[3] = Rte_GetVfb_PaVent();
	VenHeatOut[4] = Rte_GetVfb_ThirdHeat();
	if(VenHeatOut[0] == 0x00 && VenHeatOut[1] == 0x00 && VenHeatOut[2] == 0x00 && VenHeatOut[3] == 0x00 && \
		VenHeatOut[4] == 0x00 )
	{
	   HeatVenFlag = 0x01;
	}
	else
	{
		HeatVenFlag = 0x00;
	}

	if(	 (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatHeightRegulatingRelayIsGlued))
		&& (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatLongitudinalControlRelayIsGlued))
		&& (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatBackrestRegulatingRelayIsGlued))
		&& (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_DriverSeatFrontAngleAdjustmentRelayIsGlued))
		&& (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatLongitudinalControlRelayIsGlued))
		&& (FALSE == Diag_ReadDtcTestFailFlag(En_Dtc_PassengerSeatBackrestRegulatingRelayIsGlued)))
	{
		DTCFault = 0;
	}
	else
	{
		DTCFault = 1;
	}

	/*�յ������ݼ������ñ��ĸ�������ʱ��2024.6.19 By Prima Niu */
	/* �������� 0���� 1������λ��  2�����䵱ǰλ��0x3:Reserved��Դ��CanRx_0x351_IVI_FLSeatMemSet1ϵ��*/
	if((0x2 == DrMem_IVI_FLSeatMemSet1) || (0x2 == DrMem_IVI_FLSeatMemSet2) || (0x2 == DrMem_IVI_FLSeatMemSet3) \
		||(0x2 == PaMem_IVI_FRSeatMemSet1) || (0x2 == PaMem_IVI_FRSeatMemSet2) || (0x2 == PaMem_IVI_FRSeatMemSet3))
	{
		MemorySetValidFlag = TRUE;
	}
	else
	{
		MemorySetValidFlag = FALSE;
	}
	
	PowMode = Rte_GetVfb_PowerMode();
 	if((MoveFlag == 1) && (HeatVenFlag == 1) && (PowMode == 0 ) 
    && (DTCFault == 0 ) && (MemorySetValidFlag == FALSE)
    && (SWSt == FALSE))
 	{
 		if(CPU_TimerDiffTs(s_delayTimer) > D_DelayTime)
		{
			LocalSleepFlag = 1;
		}
	}
	else
	{
		LocalSleepFlag = 0;
		s_delayTimer = D_HAL_GET_CUR_MS_TS();
	}
	
}
/***********************************************************************
 * @function name: Srvl_SetDescSleepFlg
 * @description: ������Ͻ�������
 * @input parameters: INT8U
 * @output parameters: void
 * @return: NULL
 * @note: 
 * @author: Michael Xin
 * @date: 2024-11-12 11:31
 ***********************************************************************/
void OsekNmSleep_SetDescSleepFlg(INT8U Flg)
{
    s_SrvlDescSleepFlg = Flg;
}
/***********************************************************************************************
 * @function name:  Srvl_SleepDescFunction
 * @description:   �������
 * @input parameters:   ��
 * @output parameters:   ��
 * @return:    ��
 * @note:     ��
 * @author:    zjx
 * @note:    2024-04-08
 ***********************************************************************************************/
void OsekNmSleep_SleepDescFunction(void)
{
    static INT8U s_TimeCnt = 0;
    const INT8U TimeMax = 5;//100ms

    if(s_SrvlDescSleepFlg == FALSE)
    {
        s_TimeCnt = 0;
        return;
    }
    
    if(s_TimeCnt >= TimeMax)
    {
        OsekNmSleep_SleepPre();
    }
}

/***********************************************************************************************
 * @function name:  OsekNmSleep_SleepPre
 * @description:   ���߽���
 * @input parameters:   ��
 * @output parameters:   ��
 * @return:    ��
 * @note:     ��
 * @author:    zjx
 * @note:    2024-04-08
 ***********************************************************************************************/
void OsekNmSleep_SleepPre(void)
{
    INT_All_Enable(FALSE);
    Ecual_GpioWriteCh(EN_CanStbOut, EN_GPIO_LEV_LOW);
    Ecual_GpioWriteCh(EN_CanEnOut, EN_GPIO_LEV_HIGH);/*EN���ŵ͸�ƽ����ģʽ*/
    ecual_WDOG_init(200);
    while(1);
}

