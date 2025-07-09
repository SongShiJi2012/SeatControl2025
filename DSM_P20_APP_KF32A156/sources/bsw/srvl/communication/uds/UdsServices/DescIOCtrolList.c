/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescIOCtrolList.c
** Last modified Date:      2013.10.21
** Last Version:            V1.0
** Description:             IOCtrolList
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven Ī����
** Created date:            2013.10.21
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#include "DescConfig.h"
#include "DescIOCtrolList.h"
#include "AppDesc.h"
#include "Ecual_Adc.h"
#include "MidRelay.h"
#include "Srvl_PowerMode.h"
#if (SID2F_IOCTRL_EN == DESC_ENABLE)

strDescIOCtrlOutputInfo DescIOCtrlOutputInfo[D_DescIOCtrlItemNum]={0};
static void  DescIOCtrl_Task(void);
static void  DescIOCtrl50A8_Task(void);

/* ���ο������� */
#define   D_SeatMoveReason	(0x66)

#define D_DiagIOCtrlVotMin	(9000UL)	/*���IO�������ε�����С��ѹ��mv��*/
#define D_DiagIOCtrlVotMax	(16000UL)	/*���IO�������ε�������ѹ��mv��*/
/***********************************************************************************************
 * @function name:  DescIOCtrl_6001_Output
 *
 * @description:   �������θ߶ȵ��ڿ��� 
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6001_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRHEIGHT].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRHEIGHT].OutputCtrl = TpRxInfoStruct.cDataBuf[4];
			DescIOCtrlOutputInfo[EN_DRHEIGHT].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		TpTxInfoStruct.wDataLength = 5U;
	}
}
/***********************************************************************************************
 * @function name:  DescIOCtrl_6002_Output
 *
 * @description:   ��������������ڿ��� 
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6002_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRLENGTH].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRLENGTH].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_DRLENGTH].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_6003_Output
 *
 * @description:   �������ο����Ƕȵ��ڿ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6003_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRBACKREST].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRBACKREST].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_DRBACKREST].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_6004_Output
 *
 * @description:   ��������ǰ���Ƕȵ��ڿ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6004_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRCUSHION].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRCUSHION].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_DRCUSHION].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_6005_Output
 *
 * @description:   ��������������ڿ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6005_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_PALENGTH].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_PALENGTH].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_PALENGTH].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U;
	}
}
/***********************************************************************************************
 * @function name:  DescIOCtrl_6006_Output
 *
 * @description:   �������ο����Ƕȵ��ڿ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6006_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_PABACKREST].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_PABACKREST].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_PABACKREST].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_6007_Output
 *
 * @description:   ���ݼ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6007_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRHEAT].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}	
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRHEAT].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_DRHEAT].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_6008_Output
 *
 * @description:   ���ݼ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6008_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_PAHEAT].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}	
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_PAHEAT].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_PAHEAT].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}


/***********************************************************************************************
 * @function name:  DescIOCtrl_6009_Output
 *
 * @description:   ����ͨ��
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_6009_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_DRVENTILATE].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}	
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_DRVENTILATE].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_DRVENTILATE].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}

/***********************************************************************************************
 * @function name:  DescIOCtrl_600A_Output
 *
 * @description:   ���ݼ���
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2023-10-12
 ***********************************************************************************************/
static void DescIOCtrl_600A_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_PAVENTILATE].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}	
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_PAVENTILATE].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_PAVENTILATE].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}


/***********************************************************************
 * @function name: DescIOCtrl_600B_Output
 * 
 * @description: �����̼���IO����
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
 * @date: 2022-03-25 20:51
 ***********************************************************************/
static void DescIOCtrl_600B_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	INT8U IOParameter = 0;
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[EN_WHEEL].DescFlag = eIOCTL_INACTIVE;
			//Ecual_GpioExitIoCtrlMode();
			//Ecual_PwmExitIoCtrlMode();
		}
		break;

		case eIOCTL_RST2DEF:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}	
		break;

		case eIOCTL_FRZCURSTA:
		{
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		}
		break;
		
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[EN_WHEEL].OutputCtrl = TpRxInfoStruct.cDataBuf[4U];
			DescIOCtrlOutputInfo[EN_WHEEL].DescFlag = eIOCTL_ACTIVE;
		}
		break;
		
		default:
			DescNrc = kDescNrcRequestOutOfRange;
			return;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		
		TpTxInfoStruct.cDataBuf[4U] = TpRxInfoStruct.cDataBuf[4U];
		
		TpTxInfoStruct.wDataLength = 5U ;
	}
}
/*!
************************************************************************************************************************
* Function static void DescIOCtrl_D503_Output(eIOCTL_TYPE eIOCtlType)
* @brief DID-D503 gpio����
* @param void
* @param void
* @returns void
* @note ��ֲBCM
* @author  
* @date 2024-4-18
************************************************************************************************************************
*/
static void DescIOCtrl_D500_Output(eIOCTL_TYPE eIOCtlType)
{
	INT8U i=0;
	if(TRUE !=  DescRoutineCtrl_GetDareTestFlag()) 
	{
		DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].DescFlag = (INT8U)eIOCTL_INACTIVE;
		DescNrc = kDescNrcConditionsNotCorrect;
	   return;
	}
	switch(eIOCtlType)
	{
		case eIOCTL_RETURNCTL2ECU:
		{
			DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].DescFlag = (INT8U)eIOCTL_INACTIVE;
			for(i=0; i<D_DescIOCtrlAllItemNum; i++)
			{
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[i] = 0x00;
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputCtrlMask[i] = 0x00;
			}
		}
		break;
		case eIOCTL_RST2DEF:
		{
			DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].DescFlag = (INT8U)eIOCTL_ACTIVE;
			for(i=0; i<D_DescIOCtrlAllItemNum; i++)
			{
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[i] = 0x00;
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputCtrlMask[i] = 0x00;
			}
		}
		break;
		case eIOCTL_FRZCURSTA:
		break;
		case eIOCTL_SHOTTERMADJ:
		{
			DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].DescFlag = (INT8U)eIOCTL_ACTIVE;
			for(i=0; i<D_DescIOCtrlAllItemNum; i++)
			{
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[i] = \
				TpRxInfoStruct.cDataBuf[4U + i];
				DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputCtrlMask[i] =\
				TpRxInfoStruct.cDataBuf[4U+D_DescIOCtrlAllItemNum+i];
			}
		}
		break;
		default:
			DescNrc = kDescNrcServiceNotSupported;
		break;
	}	

	TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
	TpTxInfoStruct.wDataLength = 4;
	DescNrc = DescNrcOK;
	if(eIOCtlType == eIOCTL_SHOTTERMADJ)
	{	
		TpTxInfoStruct.cDataBuf[3] = TpRxInfoStruct.cDataBuf[3];
		for(i=0; i<D_DescIOCtrlAllItemNum; i++)
		{
			TpTxInfoStruct.cDataBuf[4U+i] = TpRxInfoStruct.cDataBuf[4U+i];
			//TpTxInfoStruct.cDataBuf[4U+D_DescIOCtrlItemNum+i] = TpRxInfoStruct.cDataBuf[4U+D_DescIOCtrlItemNum+i];
		}
		TpTxInfoStruct.wDataLength = 4U + D_DescIOCtrlAllItemNum;
	}
}

static void  DescIOCtrl_Task(void)
{
	if(DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
	#if(D_DescIOCtrlAllItemNum > 0U)
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<0U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_ForRot); //����������ǰ
		}
		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<1U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_RevRot); //�����������
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_LENGTH,TLE9210x_OFF); 
		}

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<2U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_ForRot); //���ݿ�����ǰ
		}
 		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<3U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_RevRot); //���ݿ������
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_BACK,TLE9210x_OFF); 
		}
		
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<4U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_ForRot); //���ݸ߶�����
		}
		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<5U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_RevRot); //���ݸ߶�����
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_HEIGHT,TLE9210x_OFF); 
		}		

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<6U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_ForRot); //����ǰ���Ƕ���ǰ
		}
		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[0] & (1U<<7U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_RevRot); //����ǰ���Ƕ����
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_DRV_FRONT,TLE9210x_OFF); 
		}
	#endif

	#if(D_DescIOCtrlAllItemNum > 1U)
		/*DATA[1]*/
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[1] & (1U<<0U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_ForRot);//��������������ǰ
		}
		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[1] & (1U<<1U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_RevRot);//���������������
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_LENGTH,TLE9210x_OFF); 
		}

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[1] & (1U<<2U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_ForRot);//�������ο�����ǰ
		}
		else if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[1] & (1U<<3U)) != 0U)
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_RevRot);//�������ο������
		}
		else
		{
			Srvl_Tle9210x_SetSeatMotor(EN_SEAT_PAS_BACK,TLE9210x_OFF); 
		}
	#endif

	#if(D_DescIOCtrlAllItemNum > 2U)
		/*DATA[2]*/
		/*if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<0U)) != 0U)
		{
			Ecual_GpioWriteCh(EN_MCU_PIN32_FL_HEAT_IN,EN_GPIO_LEV_HIGH); //���ݼ���
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN32_FL_HEAT_IN,EN_GPIO_LEV_LOW);
		}
		
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<1U)) != 0U)
		{ 
			Ecual_GpioWriteCh(EN_MCU_PIN55_FR_HEAT_IN,EN_GPIO_LEV_HIGH);//���ݼ���
		}
	 
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN55_FR_HEAT_IN,EN_GPIO_LEV_LOW);
		}

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<2)) != 0U)
		{
			Ecual_GpioWriteCh(EN_MCU_PIN88_7010_IN0,EN_GPIO_LEV_HIGH);// ����Ԥ��3
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN88_7010_IN0,EN_GPIO_LEV_LOW);
		}

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<3)) != 0U)
		{
			Ecual_GpioWriteCh(EN_MCU_PIN91_7010_IN1,EN_GPIO_LEV_HIGH);// ����Ԥ��4
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN91_7010_IN1,EN_GPIO_LEV_LOW);
		}
		
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<4)) != 0U)
		{
			Ecual_GpioWriteCh(EN_MCU_PIN74_STEER_HEAT_EN,EN_GPIO_LEV_HIGH); //�����̼���
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN74_STEER_HEAT_EN,EN_GPIO_LEV_LOW);
		}	
		*/
		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<5U)) != 0U)
		{
			
		}
		else
		{
			
		}		

		if((DescIOCtrlOutputInfo[D_DescIOCtrlOutputInfo_D500].OutputItemCtrl[2] & (1U<<6U)) != 0U)
		{
			
		}
		else
		{
			
		}
	#endif

	}
}

const tDESC_IOCTL_INFO  pIOCtrlTbl[] =
{
	{0x6001, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6001_Output},
	{0x6002, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6002_Output},
	{0x6003, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6003_Output},
	{0x6004, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6004_Output},
	{0x6005, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6005_Output},
	{0x6006, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6006_Output},
	{0x6007, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6007_Output},
	{0x6008, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6008_Output},
	{0x6009, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_6009_Output},
	{0x600A, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_600A_Output},
	{0x600B, SESN_SSS | SESN_EXTDS, 4U+D_DescShortTermAdjustment, DescIOCtrl_600B_Output},
	{0xD500, SESN_SSS | SESN_EXTDS, 4U+D_DescIOCtrlAllItemNum, DescIOCtrl_D500_Output}
	
};

/***********************************************************************************************
 * @function name:  DescIOCtrl_CheckParam
 *
 * @description:   ���IO���Ʋ���
 *
 * @input parameters:   INT8U tByte 
 *
 * @output parameters:  
 *
 * @return:    BOOL
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2024-01-09
 ***********************************************************************************************/
BOOL DescIOCtrl_CheckParam(INT8U tByte, INT8U param )
{
	BOOL result = TRUE;
	INT8U type = param;
	INT8U temp = tByte;
	switch(type)
	{	
		case EN_DRHEIGHT:
		case EN_DRLENGTH:
		case EN_DRBACKREST:
		case EN_DRCUSHION:
		case EN_PALENGTH:
		case EN_PABACKREST:
			if(temp > 0x02)
			{
				result = FALSE;
			}
			break;
		case EN_DRHEAT:
		case EN_PAHEAT:
		case EN_DRVENTILATE:
		case EN_PAVENTILATE:
			if(temp > 0x03)
			{
				result = FALSE;
			}
			break;
		case EN_WHEEL:
			if(temp > 1)
			{
				result = FALSE;
			}
			break;
		default:
			break;
	}

	return result;
}

/********************************************************************
* �������ƣ�DescInputOutputControlByIdentifier
* �������������IO����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescInputOutputControlByIdentifier(void)
{
	INT16U  wIndex, wCPID;
	INT8U cCPIDFound = FALSE;
	INT8U cSubIDIndex = 0;
	INT8U cCtrlTypeFound = FALSE;
	INT8U u8TempDescValue = 0;
	INT16U Voltage = 0x0U;
	
	Voltage = Rte_GetVfb_VoltSatisfy();
	const eIOCTL_TYPE cDescIOControlTypeID[] = {eIOCTL_RETURNCTL2ECU,
			//eIOCTL_RST2DEF,
			//eIOCTL_FRZCURSTA,
			eIOCTL_SHOTTERMADJ
	};
	
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
		TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
	if(TpRxInfoStruct.wDataLength < 4)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	if(DescSessionSA_CfgChk(eSID_IOCONTROL_BY_IDENTIFIER_INDEX))
	{
		return; 
	}

	
	/*if(unlockStatus == FALSE)
	{
		DescNrc = kDescNrcAccessDenied;
		return;
	}*/
#if 1    /*20230919  δ���*/    
	if(DescCheckVehSpd() == FALSE)//���ٴ���3km/h
	{
		//�ٶȴ���3����ʹ��
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}
#endif    
	//���ε�IOֻ��00 �� 03
	u8TempDescValue = (TpRxInfoStruct.cDataBuf[3] & 0xFF);
	if((0x00u != u8TempDescValue) && (0x03u != u8TempDescValue))
	{
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}
	/* Check the Request Format */
	wCPID = TpRxInfoStruct.cDataBuf[1];
	wCPID <<= 8;
	wCPID |= TpRxInfoStruct.cDataBuf[2];
	for(wIndex = 0; wIndex < UBOUND(pIOCtrlTbl); wIndex ++)
	{
		if(pIOCtrlTbl[wIndex].sCID == wCPID)
		{
			cCPIDFound = TRUE;

			for(cSubIDIndex = 0; cSubIDIndex < UBOUND(cDescIOControlTypeID); cSubIDIndex ++)
			{
				if(cDescIOControlTypeID[cSubIDIndex] == (TpRxInfoStruct.cDataBuf[3] & 0x7F))
				{
					if((cDescIOControlTypeID[cSubIDIndex] == eIOCTL_SHOTTERMADJ) && (TpRxInfoStruct.wDataLength != pIOCtrlTbl[wIndex].sShortTeamDJLen))
					{
						DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
						return;
					}
					if(((cDescIOControlTypeID[cSubIDIndex] == eIOCTL_RETURNCTL2ECU) || (cDescIOControlTypeID[cSubIDIndex] == eIOCTL_FRZCURSTA) ||\
						(cDescIOControlTypeID[cSubIDIndex] == eIOCTL_RST2DEF))&& (TpRxInfoStruct.wDataLength != 4))
					{
						//����= 00 01 02������ֻ��Ϊ4
						DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
						return;
					}
					//���ε��ڵ�ѹ��9-16V
					if( EN_PABACKREST >= wIndex )
					{
						if (0x0U == Voltage)
						{
							DescNrc = kDescNrcConditionsNotCorrect;
							return;
						}
					}
					else
					{	
						//ͨ����ȷ�������ѹ
						if (Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT)
						{
							DescNrc = kDescNrcConditionsNotCorrect;
							return;
						}
					}
						
						//03��������Ʋ���
					if((cDescIOControlTypeID[cSubIDIndex] == eIOCTL_SHOTTERMADJ) \
						 && (TpRxInfoStruct.wDataLength == 5)\
						 && (DescIOCtrl_CheckParam(TpRxInfoStruct.cDataBuf[4],wIndex) == FALSE))
					{
						DescNrc = kDescNrcRequestOutOfRange;
						return;
					}
					cCtrlTypeFound = TRUE;
					pIOCtrlTbl[wIndex].ServiceProcess(cDescIOControlTypeID[cSubIDIndex]);
					break;
				}
			}
			if((FALSE == cCtrlTypeFound)&&(TpRxInfoStruct.wDataLength != 3))
			{
				DescNrc = kDescNrcRequestOutOfRange;
			}
			if((FALSE == cCtrlTypeFound)&&(TpRxInfoStruct.wDataLength == 3))
			{
				DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
			}
			break;
		}
	}
	if(FALSE == cCPIDFound)
	{
		if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
		{
			DescNrc = (kDescNrcRequestOutOfRange);
		}
	}

	if(wCPID == 0xD500)
	{
		DescIOCtrl_Task();
	} 
}


/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT8U Desc_DiagOutCtrlIsValid(INT8U u8index)
* @par ����
       �ж��Ƿ�����Ͽ���
* @param[in] void
* @param[out] void
* @returns void
* @pre ��
* @note 
* @author 
* @date 2021-04-09
************************************************************************************************************************
*/
INT8U Desc_DiagOutCtrlIsValid(INT8U u8index)
{
	INT8U u8DiagCtrlValid = FALSE;
	
	if(u8index < D_DescIOCtrlItemNum)
	{
		if(DescIOCtrlOutputInfo[u8index].DescFlag == (INT8U)eIOCTL_ACTIVE)
		{
			u8DiagCtrlValid = TRUE;
		}
	}

	return u8DiagCtrlValid;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT8U Desc_DiagSetOutCtrlIsValid(INT8U u8index, eIOCTL_ACTVIE_TYPE flg)
* @par ����
       ������Ͽ��Ʊ�־
* @param[in] u8index ���Ƶ������  flg ��Ͽ��Ʊ�־λ
* @param[out] void
* @returns void
* @pre ��
* @note 
* @author 
* @date 2023-05-31
************************************************************************************************************************
*/
void Desc_DiagSetOutCtrlIsValid(INT8U u8index, eIOCTL_ACTVIE_TYPE flg)
{
	if(u8index < D_DescIOCtrlItemNum)
	{
		DescIOCtrlOutputInfo[u8index].DescFlag = (INT8U)flg;
	}
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT8U Desc_DiagOutCtrlPram(INT8U u8index)
* @par ����
       ��ȡ��Ͽ�������
* @param[in] u8index ���ƶ����±�
* @param[out] void
* @returns u8DiagCtrlValid ���Ʋ���
* @pre ��
* @note 
* @author zjx
* @date 2023-03-22
************************************************************************************************************************
*/
INT8U Desc_DiagOutCtrlPram(INT8U u8index)
{
	INT8U u8DiagCtrlValid = 0;
	
	if(u8index < D_DescIOCtrlItemNum)
	{
		if(DescIOCtrlOutputInfo[u8index].DescFlag == (INT8U)eIOCTL_ACTIVE)
		{
			//OutputCtrlΪ8ʱ��ʾ���Ʋ���Ϊ0
			u8DiagCtrlValid = DescIOCtrlOutputInfo[u8index].OutputCtrl + 1; 
		}
	}

	return u8DiagCtrlValid;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT8U Desc_SetDiagOutCtrlPram(INT8U u8index)
* @par ����
      ������Ͽ�������
* @param[in] u8index ���ƶ����±�, pram ���Ʋ���
* @param[out] void
* @returns void 
* @pre ��
* @note 
* @author zjx
* @date 2023-05-25
************************************************************************************************************************
*/
void Desc_DiagSetOutCtrlPram(INT8U u8index,INT8U pram)
{
	if(u8index < D_DescIOCtrlItemNum)
	{
		if(DescIOCtrlOutputInfo[u8index].DescFlag == (INT8U)eIOCTL_ACTIVE)
		{
			DescIOCtrlOutputInfo[u8index].OutputCtrl = pram;
		}
	}
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsRoutineCtrl_SessionChangedToDefault(void)
* @par ����
       �Ự����ֵĬ�ϲ��ֹͣ���IO����
* @param[in] void
* @param[out] void
* @returns void
* @pre ��
* @note 
* @author 
* @date 2021-06-03
************************************************************************************************************************
*/
void UdsIOCtrl_SessionChangedToDefault(void)
{
	INT8U i=0;
	
	for(i=0; i<D_DescIOCtrlItemNum; i++)
	{
		DescIOCtrlOutputInfo[i].DescFlag = (INT8U)eIOCTL_INACTIVE;
		DescIOCtrlOutputInfo[i].OutputCtrl = 0x00;

	}

}

/***********************************************************************************************
 * @function name:  DescIOCtrl_DrSeatMoveTask
 *
 * @description:   �������IO��������
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ͨ������MidRelay_MotorCtrlProc���Ƶ�ƽ������������ſ���By Prima Niu 20250603
 *
 * @author:    zjx
 *
 * @note:    2024-05-31
 ***********************************************************************************************/
void DescIOCtrl_DrSeatMoveTask(void)
{
	//���ݸ߶�	
	if(DescIOCtrlOutputInfo[EN_DRHEIGHT].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_DrMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_DrHeightMotorReason(D_SeatMoveReason);
  		Rte_SetVfb_DrHeightMotorCmd(DescIOCtrlOutputInfo[EN_DRHEIGHT].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_DRHEIGHT].OutputCtrl & 0x01) != 0U)//�������θ߶ȵ��ڣ����ϣ�
		{
			Ecual_GpioWriteCh(EN_MCU_PIN2_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN2_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_DRHEIGHT].OutputCtrl & 0x02) != 0U)//�������θ߶ȵ��ڣ����£�
		{
			Ecual_GpioWriteCh(EN_MCU_PIN1_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN1_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}

	//��������	
	if(DescIOCtrlOutputInfo[EN_DRLENGTH].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_DrMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_DrLengthMotorReason(D_SeatMoveReason);
	  	Rte_SetVfb_DrLengthMotorCmd(DescIOCtrlOutputInfo[EN_DRLENGTH].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_DRLENGTH].OutputCtrl & 0x01) != 0U)//��������������ڣ���ǰ��
		{
			Ecual_GpioWriteCh(EN_MCU_PIN8_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN8_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_DRLENGTH].OutputCtrl & 0x02) != 0U)//��������������ڣ����
		{
			Ecual_GpioWriteCh(EN_MCU_PIN3_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN3_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}
	
	//���ݿ���
	if(DescIOCtrlOutputInfo[EN_DRBACKREST].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_DrMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_DrBackMotorReason(D_SeatMoveReason);
	  	Rte_SetVfb_DrBackMotorCmd(DescIOCtrlOutputInfo[EN_DRBACKREST].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_DRBACKREST].OutputCtrl & 0x01) != 0U)//�������ο������ڣ���ǰ��
		{
			Ecual_GpioWriteCh(EN_MCU_PIN6_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN6_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_DRBACKREST].OutputCtrl & 0x02) != 0U)//�������ο������ڣ����
		{
			Ecual_GpioWriteCh(EN_MCU_PIN7_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN7_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}

	//����ǰ���߶�	
	if(DescIOCtrlOutputInfo[EN_DRCUSHION].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_DrMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_DrFrontMotorReason(D_SeatMoveReason);
	  	Rte_SetVfb_DrFrontMotorCmd(DescIOCtrlOutputInfo[EN_DRCUSHION].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_DRCUSHION].OutputCtrl & 0x01) != 0U)//��������ǰ���߶ȵ��ڣ����ϣ�
		{
			Ecual_GpioWriteCh(EN_MCU_PIN9_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN9_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_DRCUSHION].OutputCtrl & 0x02) != 0U)//��������ǰ���߶ȵ��ڣ����£�
		{
			Ecual_GpioWriteCh(EN_MCU_PIN4_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN4_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}

}

/***********************************************************************************************
 * @function name:  DescIOCtrl_PaSeatMoveTask
 *
 * @description:   �������IO��������
 *
 * @input parameters:   ��
 *
 * @output parameters:   ��
 *
 * @return:    ��
 *
 * @note:     ��
 *
 * @author:    zjx
 *
 * @note:    2024-05-31
 ***********************************************************************************************/
void DescIOCtrl_PaSeatMoveTask(void)
{
	//��������	
	if(DescIOCtrlOutputInfo[EN_PALENGTH].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_PaMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_PaLengthMotorReason(D_SeatMoveReason);
  		Rte_SetVfb_PaLengthMotorCmd(DescIOCtrlOutputInfo[EN_PALENGTH].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_PALENGTH].OutputCtrl & 0x01) != 0U)//��������������ڣ���ǰ��
		{
			Ecual_GpioWriteCh(EN_MCU_PIN18_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN18_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_PALENGTH].OutputCtrl & 0x02) != 0U)//��������������ڣ����
		{
			Ecual_GpioWriteCh(EN_MCU_PIN17_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN17_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}
	
	//���ݿ���
	if(DescIOCtrlOutputInfo[EN_PABACKREST].DescFlag == (INT8U)eIOCTL_ACTIVE)
	{
		Rte_SetVfb_PaMoveType(enSeatMotorRunType_EN_DiagIOEnable);
		Rte_SetVfb_PaBackMotorReason(D_SeatMoveReason);
  		Rte_SetVfb_PaBackMotorCmd(DescIOCtrlOutputInfo[EN_PABACKREST].OutputCtrl);
		/*if( (DescIOCtrlOutputInfo[EN_PABACKREST].OutputCtrl & 0x01) != 0U)//�������ο������ڣ���ǰ��
		{
			Ecual_GpioWriteCh(EN_MCU_PIN20_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN20_RELAY_DRV,EN_GPIO_LEV_LOW);
		}
		if( (DescIOCtrlOutputInfo[EN_PABACKREST].OutputCtrl & 0x02) != 0U)//�������ο������ڣ����
		{
			Ecual_GpioWriteCh(EN_MCU_PIN19_RELAY_DRV,EN_GPIO_LEV_HIGH);
		}
		else
		{
			Ecual_GpioWriteCh(EN_MCU_PIN19_RELAY_DRV,EN_GPIO_LEV_LOW);
		}*/
	}

}

#endif

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/



