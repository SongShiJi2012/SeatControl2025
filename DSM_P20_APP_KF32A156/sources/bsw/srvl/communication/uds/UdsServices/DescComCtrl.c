/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescComCtrl.c
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             ͨ�ſ���
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven Ī����
** Created date:            2013.10.23
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
#define	COMCTL_GLOBALS

#include "uds_pub.h"
#include "OsekNm_Cfg.h"
#include "Ecual_CAN.h"

//#include "Srvl_nm_osek.h"
//#include "Srvl_SimulinkInterface.h"
//#include "Srvl_CanSignals.h"


static INT8U APPCommDescDisable = FALSE;



#if SID28_COMCTL_EN == DESC_ENABLE

void  ComCtrlInit(void)
{
  #if 1  /*20230919  δʹ��*/
	//�ָ�ͨ��
	ECUAL_CAN_ENABLE_APP_RX_ENABLE();
	ECUAL_CAN_ENABLE_APP_TX_ENABLE();
//	Nm_ClrUdsAppCommCtrl();
//	ApplAppMessageControl(OSEK_ENABLE);
	ECUAL_CAN_ENABLE_NM_RX_ENABLE();
	ECUAL_CAN_ENABLE_NM_TX_ENABLE();
	OsekNm_Start();
#endif
}

static void ComCtrlComm(INT8U ComMsgType, INT8U ComCtrlVal)
{
#if 1  /*20230919  δʹ��*/
  if((0 == (ComMsgType & MSG_TYPE_ALL)) || (MSG_TYPE_ALL < ComMsgType))    //ComMsgType: 01b application   10b networkManagement   11b both
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
	
//	Nm_SetUdsAppCommCtrl();
	if(ComMsgType & MSG_TYPE_NORMAL)
	{
	#if 0
//		ApplAppMessageControl(OSEK_DISABLE); // need notify osek nm
		if(ComCtrlVal == eRXDISABLE_TXDISABLE)
		{
			ECUAL_CAN_DISABLE_APP_RX_ENABLE();
			ECUAL_CAN_DISABLE_APP_TX_ENABLE();
		}
		else if(ComCtrlVal == eRXDISABLE_TXENABLE)
		{
			ECUAL_CAN_DISABLE_APP_RX_ENABLE();
			ECUAL_CAN_ABLE_APP_TX_ENABLE();
//			ApplAppMessageControl(OSEK_ENABLE); // need notify osek nm
		}
		else if(ComCtrlVal == eRXENABLE_TXDISABLE)
		{
			ECUAL_CAN_ABLE_APP_RX_ENABLE();
			ECUAL_CAN_DISABLE_APP_TX_ENABLE();
		}
		else
		{
			ECUAL_CAN_ABLE_APP_RX_ENABLE();
			ECUAL_CAN_ABLE_APP_TX_ENABLE();
//			Nm_ClrUdsAppCommCtrl();
//			ApplAppMessageControl(OSEK_ENABLE); // need notify osek nm
		}
	#endif
//		ApplAppMessageControl(OSEK_DISABLE); // need notify osek nm
		if(ComCtrlVal == eRXDISABLE_TXDISABLE)
		{
			ECUAL_CAN_DISABLE_APP_RX_ENABLE();
			ECUAL_CAN_DISABLE_APP_TX_ENABLE();
			APPCommDescDisable = TRUE;
		}
		else if(ComCtrlVal == eRXDISABLE_TXENABLE)
		{
			ECUAL_CAN_DISABLE_APP_RX_ENABLE();
			ECUAL_CAN_ENABLE_APP_TX_ENABLE();
//			ApplAppMessageControl(OSEK_ENABLE); // need notify osek nm
		}
		else if(ComCtrlVal == eRXENABLE_TXDISABLE)
		{
			ECUAL_CAN_ENABLE_APP_RX_ENABLE();
			ECUAL_CAN_DISABLE_APP_TX_ENABLE();
		}
		else
		{
			ECUAL_CAN_ENABLE_APP_RX_ENABLE();
			ECUAL_CAN_ENABLE_APP_TX_ENABLE();
			APPCommDescDisable = FALSE;
//			Nm_ClrUdsAppCommCtrl();
//			ApplAppMessageControl(OSEK_ENABLE); // need notify osek nm
		}
	}
	if(ComMsgType & MSG_TYPE_NETWORK)
	{
		if(ComCtrlVal == eRXDISABLE_TXDISABLE)
		{
			OsekNm_Stop();
		}
		else if(ComCtrlVal == eRXDISABLE_TXENABLE)
		{
			
		}
		else if(ComCtrlVal == eRXENABLE_TXDISABLE)
		{
			
		}
		else
		{
			OsekNm_Start();
		}
	}
	if(!DescSuppressPosRspBit)
	{
    	TpTxInfoStruct.wDataLength = 2;
    	DescNrc = DescNrcOK;
	}
#endif        
}

static void ComCtrlRxAndTxEnable(INT8U ComMsgType)
{
	ComCtrlComm(ComMsgType, eRXENABLE_TXENABLE);
}

static void ComCtrlRxEnableTxDisable(INT8U ComMsgType)
{
    ComCtrlComm(ComMsgType, eRXENABLE_TXDISABLE);
}

static void ComCtrlRxDisableAndTxEnable(INT8U ComMsgType)
{
    ComCtrlComm(ComMsgType, eRXDISABLE_TXENABLE);
}

static void ComCtrlRxAndTxDisable(INT8U ComMsgType)
{
	ComCtrlComm(ComMsgType, eRXDISABLE_TXDISABLE);
}


const tDESC_COM_INFO pComCtrlTbl[] =
{
	{eRXENABLE_TXENABLE,   /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxAndTxEnable}},
    //{eRXENABLE_TXDISABLE,  /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxEnableTxDisable}},
    //{eRXDISABLE_TXENABLE,  /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxDisableAndTxEnable}},
 	{eRXDISABLE_TXDISABLE, /*SESN_EXTDS | SESN_DS, */{3, ComCtrlRxAndTxDisable}}
};


/********************************************************************
* �������ƣ�DescCommunicationControl
* �������������ͨ�ſ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescCommunicationControl(void)
{
	INT8U cCtrlSubFuncIDIndex, cCtrlSubFuncID;
	INT8U cCtrlSubFuncIDFound = FALSE;
	INT16U u16Speed = 0;
	cCtrlSubFuncID = (TpRxInfoStruct.cDataBuf[1] & 0x7F);

	

	if(3 != TpRxInfoStruct.wDataLength)
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	
	    /*�Ự�����28h ִ���������*/
    if(SESN_EXTDS != cDescSession)
    {	
    	if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
    	{
			DescNrc = kDescNrcServiceNotSupportedInActiveSession;
    	}
		else
		{	
			DescNrc = DescNrcNoRsp;	
		}
        return;
    }
	if(DescCheckVehSpd() == FALSE)//���ٴ���3km/h
	{
		//�ٶȴ���4����ʹ��
		DescNrc = kDescNrcConditionsNotCorrect;
		return;
	}

	for(cCtrlSubFuncIDIndex = 0; cCtrlSubFuncIDIndex < UBOUND(pComCtrlTbl); cCtrlSubFuncIDIndex ++)
	{
		if(pComCtrlTbl[cCtrlSubFuncIDIndex].eComCtrlType == (eCOM_CTL_TYPE)cCtrlSubFuncID)
		{
			cCtrlSubFuncIDFound = TRUE;
			if(DescSessionSA_CfgChk(eSID_COMMUNICATION_CONTROL_INDEX))
			{
				return;
			}
			DescSuppressRosRspBitSet();
			pComCtrlTbl[cCtrlSubFuncIDIndex].ComCtrlInfo.ServiceProcess(TpRxInfoStruct.cDataBuf[2]);
			return;
		}
	}
	if(cCtrlSubFuncIDFound == FALSE)
	{
	    if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
	    {
            DescNrc = kDescNrcSubfunctionNotSupported;
	    }
	}
}

#endif
/***********************************************************************************************
 * @function name:  GetAPPCommDisable(void)
 *
 * @description:	��ȡ�Ƿ�����Ϲرձ��ı�־
 *
 * @input parameters:     
 *
 * @output parameters: APPCommDescDisable    
 *
 * @return:         ��
 *
 * @note:           ��
 *
 * @author:          LC
 *
 * @note:           2024-04-25
 ***********************************************************************************************/

INT8U GetAPPCommDisable(void)
{
	return APPCommDescDisable;
}
/***********************************************************************************************
 * @function name:  SetAPPCommDisable(void)
 *
 * @description:	������Ϲرձ��ı�־
 *
 * @input parameters:     APPCommDescCtrl
 *
 * @output parameters:     
 *
 * @return:         ��
 *
 * @note:           ��
 *
 * @author:          LC
 *
 * @note:           2024-04-25
 ***********************************************************************************************/

INT8U SetAPPCommDisable(INT8U APPCommDescCtrl)
{
	 APPCommDescDisable = APPCommDescCtrl;
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/



