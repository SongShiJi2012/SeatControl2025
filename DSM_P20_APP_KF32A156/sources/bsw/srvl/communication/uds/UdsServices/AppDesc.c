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
* @par 接口原型
       void AppDescInit(void)
* @par 描述 初始化诊断管理信息
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
* @par 接口原型
       void AppDescPinAttackProcess(void)
* @par 描述 安全访问防攻击处理
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
			ret = TRUE;//pending后需要隔60s才能再次访问
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
		u1gSecurityAccessIsDelayEndFlg = FALSE;//pending后需要隔60s才能再次访问
	}

}

/*!
************************************************************************************************************************
* @par 接口原型
       BOOL Uds_AccessTimesLmt(void)
* @par 描述 安全访错误尝试次数,需上电记忆之前错误次数
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
* @par 接口原型
       void Uds_AccessTimeRst(void)
* @par 描述 清安全访错误尝试次数
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
* @par 接口原型
       void AppLinDescTask(void)
* @par 描述 诊断LIN响应，目前 只作用于EBS的ID写入
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
	static INT16U tempDID = 0; //用来记录DID;
	static INT8U tRWdlc = 0;//用来判断是读还是写;
	INT8U tRWLINDIDINDEX = 0;//记录是哪个DID下标;
	static INT8U indexPre = 0;
	INT8U i = 0;

	if(linRecv == TRUE)
	{
		//ret = Ecual_LinRecvDiagFrame(msgBuf, &length, sizeof(msgBuf));  /*20230921 LIN功能后续添加*/
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
* @par 接口原型
       void AppDescTask(void)
* @par 描述 诊断回复需延迟类的回复,如2E/14等服务,需操作完毕eeprom后才可以回复正响应
* @param[in]
* @param[out]
* @returns
* @pre
* @note 该函数只作用于EEPROM (2E/14服务)相关的操作
* @author
* @date
************************************************************************************************************************
*/
void AppDescTask(void)
{
  #if 1   /*20230919 未添加该功能*/
	static INT32U EepromNotBusyTimer = 0;
	static INT32U EepromNotBusyTimer2 = 0;
	INT8U DescNrcEprom = DescNrcNoRsp;
	enSrvMemIndex enMemIndex = 0;
	if(Appdesc_engCurrEEPOpDataID < EN_MemIndex_Max)
	{
		if(Appdesc_u1gClrDTCNeedRspFlg == TRUE)
		{
			if((IsE2promBusy() == FALSE)
			&& (IsAppE2promOptReqIDLE(Appdesc_engCurrEEPOpDataID))) /* 写EEPROM结束 */
			{
				TpTxInfoStruct.cDataBuf[0] = Desc_stgLngTmRspInfo.u1RspSID;
				TpTxInfoStruct.cDataBuf[1] = Desc_stgLngTmRspInfo.u1DID0;
				TpTxInfoStruct.cDataBuf[2] = Desc_stgLngTmRspInfo.u1DID1;
				enMemIndex = Srvl_getClearDTCIndex();
				if(IsE2promOptResultOK(enMemIndex)) //清除DTC写的最后一个数据OK
				{
				
					//TpTxInfoStruct.wDataLength = 1;/*统一返回1个字节正响应:14服务此处回复54*/
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
						DescNrcEprom = kDescNrcGeneralProgrammingFailure; //只有物理寻址才会响应
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
			&& (IsAppE2promOptReqIDLE(Appdesc_engCurrEEPOpDataID))) /* 写EEPROM结束 */
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
#if 1   /*20230919 未添加*/                  
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

	/*恢复出厂设置响应*/
	if(DescRoutineCtrl_GetRecoverDefaultFlag() == TRUE)
	{
#if 1   /*20230919 未添加该功能*/          
		/*Eeprom空闲30ms后发送响应报文.实测收到恢复出厂设置命令20ms左右才开始写EEprom*/
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
* @par 接口原型
       void AppDescSessionChanged(INT8U cPreSession, INT8U cNewSession)
* @par 描述 会话层变化后需处理的信息
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

