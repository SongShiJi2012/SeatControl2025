#define  AppDesc_GLOBALS

#include "AppDesc.h"
#include "uds_pub.h"
#include "Srvl_E2memory.h"
#include "CpuPeripheralInit.h"
#include "Test.h"

void Sys_WriteUdsSecurityAccessTime(INT8U accessTime)
{
	Srvl_SetMemIndexDataU8(EN_MemIndex_AppUdsSecurityAccessTimes, accessTime);
}

INT8U Sys_ReadUdsSecurityAccessTime(void)
{
	INT8U u8Temp = 0;

	u8Temp = Srvl_GetMemIndexDataU8(EN_MemIndex_AppUdsSecurityAccessTimes);

	return u8Temp;
}

static volatile INT32U PinAttackTime = 0UL;
BOOL linRecv = FALSE;
enSrvMemIndex Appdesc_engCurrEEPOpDataID = EN_MemIndex_Max;
volatile INT8U Appdesc_u1gClrDTCNeedRspFlg = 0;
INT16U recvDID = 0;
const INT8U  DTCSetBit[8] =
{
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
};
const tLIN_DID_INFO pLINDIDInfoTbl[] =
{
	{0x00B2, 0x01, 0},
	{0xC101, 0x03, 0},
	{0xC102, 0x03, 0},
	{0xC103, 0x03, 0},
	{0xC104, 0x03, 0},
	{0xC106, 0x03, 0},
	{0xC107, 0x03, 0},
	{0x0694, 0x07, 0},
	{0x0724, 0x14, 0},
};
/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void AppDescInit(void)
* @par ���� ��ʼ����Ϲ�����Ϣ
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date
************************************************************************************************************************
*/
void AppDescInit(void)
{
	Appdesc_u1gClrDTCNeedRspFlg = FALSE;
	if (Sys_ReadUdsSecurityAccessTime() != 0U)
	{
		u1gSecurityAccessIsDelayEndFlg = FALSE;
	}
	else
	{
		u1gSecurityAccessIsDelayEndFlg = TRUE;
	}
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void AppDescPinAttackProcess(void)
* @par ���� ��ȫ���ʷ���������
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author Michael
* @date 2016-8-24
************************************************************************************************************************
*/
void AppDescPinAttackProcess(void)
{
	INT8U ret = FALSE;

	if (u1gSecurityAccessIsDelayEndFlg == FALSE)
	{
		if(++PinAttackTime >= APPDESC_60S)
		{
			PinAttackTime = 0;
			ret = TRUE;//pending����Ҫ��60s�����ٴη���
		}
	}
	else
	{
		ret = TRUE;
	}

	if(ret)
	{
		u1gSecurityAccessIsDelayEndFlg = TRUE;
	}
	else
	{
		u1gSecurityAccessIsDelayEndFlg = FALSE;//pending����Ҫ��60s�����ٴη���
	}

}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       BOOL Uds_AccessTimesLmt(void)
* @par ���� ��ȫ�ô����Դ���,���ϵ����֮ǰ�������
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date
************************************************************************************************************************
*/
BOOL bCleanFlag = FALSE;

void Uds_AccessTimesClean(void)
{
	static INT16U u16WaitTimer = 0x0u;

	if((TRUE == bCleanFlag) || (FALSE == u1gSecurityAccessIsDelayEndFlg))
	{
		if(0xFFFFu > u16WaitTimer)
		{
			u16WaitTimer ++;
			if(DESC_MAX_Security_60s_TIME <= u16WaitTimer)
			{
				Sys_WriteUdsSecurityAccessTime(0);
				bCleanFlag = FALSE;
				u16WaitTimer = 0x0u;
			}
		}
		else
		{
			u16WaitTimer = 0x0u;
		}
	}
}

BOOL Uds_AccessTimesLmt(void)
{
	BOOL lmtRes = FALSE;
	INT8U accessTimes = Sys_ReadUdsSecurityAccessTime();

	if(accessTimes >= D_UDS_ACCESS_MAX_TIMES)
	{
		u1gSecurityAccessIsDelayEndFlg = FALSE;
		lmtRes = TRUE;
		bCleanFlag = TRUE;
	}
	else
	{
		accessTimes++;
		Sys_WriteUdsSecurityAccessTime(accessTimes);
	}

	return lmtRes;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void Uds_AccessTimeRst(void)
* @par ���� �尲ȫ�ô����Դ���
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date
************************************************************************************************************************
*/
void Uds_AccessTimeRst(void)
{
	Sys_WriteUdsSecurityAccessTime(0);
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void AppLinDescTask(void)
* @par ���� ���LIN��Ӧ��Ŀǰ ֻ������EBS��IDд��
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date
************************************************************************************************************************
*/
void AppLinDescTask(void)
{
	static INT8U msgBuf[32] = {0x00};
	static INT16U length = 0;
	BOOL ret = FALSE;
	static INT32U TimeOut = 0;
	static INT16U tempDID = 0; //������¼DID;
	static INT8U tRWdlc = 0;//�����ж��Ƕ�����д;
	INT8U tRWLINDIDINDEX = 0;//��¼���ĸ�DID�±�;
	static INT8U indexPre = 0;
	INT8U i = 0;

	if(linRecv == TRUE)
	{
		//ret = Ecual_LinRecvDiagFrame(msgBuf, &length, sizeof(msgBuf));  /*20230921 LIN���ܺ������*/
		if(ret)
		{
			if((msgBuf[0] == 0x6E) || (msgBuf[0] == 0x62))
			{
				TpTxInfoStruct.wDataLength = 3;
				TpTxInfoStruct.cDataBuf[0] = msgBuf[0];
				TpTxInfoStruct.cDataBuf[1] = (INT8U)((tempDID >> 8UL) & 0xFF);
				TpTxInfoStruct.cDataBuf[2] = (INT8U)(tempDID & 0xFF);
				if(msgBuf[0] == 0x62)
				{
					TpTxInfoStruct.wDataLength += (pLINDIDInfoTbl[indexPre].ReadDIDLength);
					for(i = 0; i < pLINDIDInfoTbl[indexPre].ReadDIDLength; i++)
					{
						if (i < length - 3)
						{
							TpTxInfoStruct.cDataBuf[3 + i] = msgBuf[3 + i];
						}
						else
						{
							TpTxInfoStruct.cDataBuf[3 + i] = 0xFF;
						}
					}
				}
			}
			else
			{
				TpTxInfoStruct.cDataBuf[0] = DESC_NEGATIVE_RESPONSE_SERVICE_ID;
				TpTxInfoStruct.cDataBuf[1] = msgBuf[1];
				TpTxInfoStruct.cDataBuf[2] = msgBuf[2];
				TpTxInfoStruct.wDataLength = 3;
			}
			TpTxStart();
			tempDID = 0;
			tRWdlc = 0;
			linRecv = FALSE;
			return;
		}


		if(CPU_TimerDiffTs(TimeOut) > 1000UL)
		{
			TpTxInfoStruct.cDataBuf[0] = DESC_NEGATIVE_RESPONSE_SERVICE_ID;
			TpTxInfoStruct.cDataBuf[1] = tRWdlc - 0x40;
			TpTxInfoStruct.cDataBuf[2] = kDescNrcnoResponseFromSubnetComponent;
			TpTxInfoStruct.wDataLength = 3;
			TpTxStart();
			linRecv = FALSE;
		}
		return;
	}
	if(FALSE == linRecv)
	{
		tempDID = Desc_stgLngTmRspInfo.u1DID0;
		tempDID = (tempDID << 8) | Desc_stgLngTmRspInfo.u1DID1;
		tRWdlc = Desc_stgLngTmRspInfo.u1RspSID;

		for(tRWLINDIDINDEX = 0; tRWLINDIDINDEX < UBOUND(pLINDIDInfoTbl); tRWLINDIDINDEX++)
		{
			if(tempDID == pLINDIDInfoTbl[tRWLINDIDINDEX].sDID)
			{
				Desc_stgLngTmRspInfo.u1RspSID = 0;
				Desc_stgLngTmRspInfo.u1DID0 = 0;
				Desc_stgLngTmRspInfo.u1DID1 = 0;
				linRecv = TRUE;
				TimeOut = D_HAL_GET_CUR_MS_TS();
				indexPre = tRWLINDIDINDEX;
			}
		}
	}
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void AppDescTask(void)
* @par ���� ��ϻظ����ӳ���Ļظ�,��2E/14�ȷ���,��������eeprom��ſ��Իظ�����Ӧ
* @param[in]
* @param[out]
* @returns
* @pre
* @note �ú���ֻ������EEPROM (2E/14����)��صĲ���
* @author
* @date
************************************************************************************************************************
*/
void AppDescTask(void)
{
  #if 1   /*20230919 δ��Ӹù���*/
	static INT32U EepromNotBusyTimer = 0;
	static INT32U EepromNotBusyTimer2 = 0;
	INT8U DescNrcEprom = DescNrcNoRsp;
	enSrvMemIndex enMemIndex = 0;
	if(Appdesc_engCurrEEPOpDataID < EN_MemIndex_Max)
	{
		if(Appdesc_u1gClrDTCNeedRspFlg == TRUE)
		{
			if((IsE2promBusy() == FALSE)
			&& (IsAppE2promOptReqIDLE(Appdesc_engCurrEEPOpDataID))) /* дEEPROM���� */
			{
				TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
				TpTxInfoStruct.cDataBuf[1] = Desc_stgLngTmRspInfo.u1DID0;
				TpTxInfoStruct.cDataBuf[2] = Desc_stgLngTmRspInfo.u1DID1;
				enMemIndex = Srvl_getClearDTCIndex();
				if(IsE2promOptResultOK(enMemIndex)) //���DTCд�����һ������OK
				{
				
					//TpTxInfoStruct.wDataLength = 1;/*ͳһ����1���ֽ�����Ӧ:14����˴��ظ�54*/
					TpTxInfoStruct.wDataLength = 1;
					DescNrcEprom = DescNrcOK;

					Appdesc_engCurrEEPOpDataID = EN_MemIndex_Max;
					Desc_OpTimeLongerThanP2Flag = FALSE;
					u1gP2ExCntr = Desc_mgClrDTC_P2ExTIMES;
					Appdesc_u1gClrDTCNeedRspFlg = FALSE;

				}
				/*else
				{
					if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
					{
						DescNrcEprom = kDescNrcGeneralProgrammingFailure; //ֻ������Ѱַ�Ż���Ӧ
					}
				}*/

			}
			else
			{
				if(CPU_TimerDiffTs(DescRepeatRes) > D_DESCNRCEPROMRSP_4000MS)
				{
					DescNrcEprom = kDescNrcResponsePending;
					DescRepeatRes = D_HAL_GET_CUR_MS_TS();
				}
			}
		}
		else
		{

			if((IsE2promBusy() == FALSE)
			&& (IsAppE2promOptReqIDLE(Appdesc_engCurrEEPOpDataID))) /* дEEPROM���� */
			{
				if(TRUE == IsE2promOptResultOK(Appdesc_engCurrEEPOpDataID))
				{
					TpTxInfoStruct.wDataLength = 3;
					TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
					TpTxInfoStruct.cDataBuf[1] = Desc_stgLngTmRspInfo.u1DID0;
					TpTxInfoStruct.cDataBuf[2] = Desc_stgLngTmRspInfo.u1DID1;
					DescNrcEprom = DescNrcOK;
				}
				else
				{
					TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
					if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
					{
						DescNrcEprom = kDescNrcGeneralProgrammingFailure;
					}
				}
				Appdesc_engCurrEEPOpDataID = EN_MemIndex_Max;
				Desc_OpTimeLongerThanP2Flag = FALSE;
			}
                      
		}
		
		if(DiagResetWaitFlag == TRUE)
		{
#if 1   /*20230919 δ���*/                  
			if((IsE2promBusy() == FALSE))
			{
				TpTxInfoStruct.wDataLength = 2;
				TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
				TpTxInfoStruct.cDataBuf[1] = Desc_stgLngTmRspInfo.u1DID0;
				DescNrcEprom = DescNrcOK;
				DescECUResetReq.cDescECUHardRestAnswerfg = TRUE;
				DescECUResetReq.cDescECUHardRestReq = TRUE;
			}
			else
#endif                            
			{
				if(CPU_TimerDiffTs(DescRepeatRes) > D_DESCNRCEPROMRSP_4000MS)
				{
					DescNrcEprom = kDescNrcResponsePending;
					DescRepeatRes = DescRepeatRes = D_HAL_GET_CUR_MS_TS();
				}
			}
		}

		if(DescNrcOK < DescNrcEprom)
		{
			DescSendNegResp(DescNrcEprom);
		}
		if(DescNrcNoRsp != DescNrcEprom)
		{
			TpTxStart();
		}
	}

	/*�ָ�����������Ӧ*/
	if(DescRoutineCtrl_GetRecoverDefaultFlag() == TRUE)
	{
#if 1   /*20230919 δ��Ӹù���*/          
		/*Eeprom����30ms������Ӧ����.ʵ���յ��ָ�������������20ms���Ҳſ�ʼдEEprom*/
		if((IsE2promBusy() == FALSE))
		{
			if (CPU_TimerDiffTs(EepromNotBusyTimer) > D_EEPROMNOTBUSYTIMER)
			{
				TpTxInfoStruct.wDataLength = 5;
				TpTxInfoStruct.cDataBuf[0] = 0x31 + 0x40;
				TpTxInfoStruct.cDataBuf[1] = 0x01;
				TpTxInfoStruct.cDataBuf[2] = 0x60;
				TpTxInfoStruct.cDataBuf[3] = 0x10;
				TpTxInfoStruct.cDataBuf[4] = 0x00;
				DescNrcEprom = DescNrcOK;
				DescRoutineCtrl_SetRecoverDefaultFlag(FALSE);
			}
		}
		else
		{
#endif                  
			EepromNotBusyTimer = D_HAL_GET_CUR_MS_TS();
		}
		
		if(DescNrcOK < DescNrcEprom)
		{
			DescSendNegResp(DescNrcEprom);
		}
		if(DescNrcNoRsp != DescNrcEprom)
		{
			TpTxStart();
		}
	}
	else
	{
		EepromNotBusyTimer = D_HAL_GET_CUR_MS_TS();
	}
 #endif         
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void AppDescSessionChanged(INT8U cPreSession, INT8U cNewSession)
* @par ���� �Ự��仯���账�����Ϣ
* @param[in]
* @param[out]
* @returns
* @pre
* @note
* @author
* @date
************************************************************************************************************************
*/
void AppDescSessionChanged(INT8U cPreSession, INT8U cNewSession)
{
	INT8U cIndex, *pu1tTmp;

	if((cPreSession & 0x7F) == SESN_DS)
	{
		return;
	}
	else
	{
		if((cNewSession & 0x7F) == SESN_DS)
		{
			cDescControlDTCSetting = DESC_CONTROL_DTC_SETTING_ON;
			ComCtrlInit();
			DescRoutineCtrlSequenceSet(0);
			UdsRoutineCtrl_SessionChangedToDefault();
			PINCodeMatchFlgSet(FALSE);
			UdsApp_2APeriodTransReset();
			UdsIOCtrl_SessionChangedToDefault();
			g_u8PINCodeAuthFailCnt = 0;

		}
		else if((cNewSession & 0x7F) == SESN_PRGS)
		{
		}
		bSeedReceive = FALSE;
		unlockStatus = FALSE;
	}
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

