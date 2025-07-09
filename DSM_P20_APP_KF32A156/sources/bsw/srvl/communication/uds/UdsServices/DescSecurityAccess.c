/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescSecurityAccess.c
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             ��ȫ����
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

#include "uds_pub.h"
#include "aes_crypto.h"
#include "sha2.h"

const INT8U cDesSecurityAccessSubID[] =
{
	DESC_SECURITY_ACCESS_REQUEST_EXTSEED,\
	DESC_SECURITY_ACCESS_SEND_EXTKEY,\
	DESC_SECURITY_ACCESS_REQUEST_REPROGRA,\
	DESC_SECURITY_ACCESS_SEND_REPROGRA
};

void Desc_vosSecAccessReqSeed(void)
{
	if(Desc_stsSecLvl.PreLvl != Desc_stsSecLvl.CurrLvl)
	{
		Desc_stsSecLvl.PreLvl = Desc_stsSecLvl.CurrLvl;
		bSeedReceive = FALSE;
		unlockStatus = FALSE;
	}
	
	if(bSeedReceive == TRUE)
	{
		if(unlockStatus == FALSE)
		{
			if(Uds_AccessTimesLmt() == TRUE)//Attempt three times repeatedly
			{
				bSeedReceive = FALSE;
				DescNrc = (kDescNrcExceedNumOfAttempts);
			}
			else
			{
			//����ΪTRUEÿ�������Seed�����£�����ΪFALSEֻҪ������Կ��һֱ�������ӣ��������µ�seed
				AppDescSecurityAccessRequestSeed(FALSE);
			}
		}
		else
		{
			AppDescSecurityAccessServerAlreadyUnlock();//��ȫ������ͨ�����ص�seedΪ0
		}
	}
	else
	{
		if(unlockStatus)
		{
			AppDescSecurityAccessServerAlreadyUnlock();//��ȫ������ͨ�����ص�seedΪ0
		}
		else
		{
			AppDescSecurityAccessRequestSeed(TRUE);//��������󷵻�Seed
		}
	}
}


/*3==========================================================================================================================*/
/*  The subService of SecurityAccess 0x27 */
void AppDescSecurityAccessRequestSeed(INT8U u1tNotRepeatReqFlg)//��������󷵻�Seed
{
	INT8U cIndex;

	cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
	bSeedReceive = TRUE;
	if(u1tNotRepeatReqFlg)
	{
		SecurityAccess_vogSeedGenerate();//����seed
	}
	TpTxInfoStruct.wDataLength = 2;
	for(cIndex = 0; cIndex < SecurityAccess_MSEEDNUM; cIndex ++)
	{
		TpTxInfoStruct.cDataBuf[cIndex + 2] = SecurityAccess_stgOutInfo.u1SecLvSeed[cIndex];
		TpTxInfoStruct.wDataLength++;
	}
	DescNrc = DescNrcOK;
}

/*************************************************************
* �������ƣ�AppDescSecurityAccessServerAlreadyUnlock
* ������������ȫ������ͨ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: �ظ�ȫ0X00
*************************************************************/
void AppDescSecurityAccessServerAlreadyUnlock(void)
{
	INT8U cIndex;

	bSeedReceive = TRUE;
	if( (TpRxInfoStruct.cDataBuf[1] == DESC_SECURITY_ACCESS_REQUEST_EXTSEED) || \
	(TpRxInfoStruct.cDataBuf[1] == DESC_SECURITY_ACCESS_REQUEST_REPROGRA) )
	{
		TpTxInfoStruct.wDataLength = 2;
		for(cIndex = 0; cIndex < SecurityAccess_MSEEDNUM; cIndex ++)
		{
			TpTxInfoStruct.cDataBuf[cIndex + 2] = 0;
			TpTxInfoStruct.wDataLength++;
			DescNrc = DescNrcOK;
		}

	}
}
const INT8U ALGORITHM_FACTORS[16] = {
	0x77, 0x20, 0xE9, 0xC3, 0x94, 0xE2, 0x07, 0x6F, 
	0x70, 0x23, 0xD2, 0xEF, 0x41, 0xEA, 0xB8, 0x80
};

/*******************************************************************************
* �������ƣ�BootSecurityAccess_vogKeyGenerate
* ������������ȫ���ʲ���Key�㷨
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*******************************************************************************/
void  SecurityAccess_vogKeyGenerate(void)
{
	INT8U md[32 + 16];
	INT8U thash[32];
	INT8U key[16];
	INT32U len = 16;
	/* ����SHA256 */
	SHA256(SecurityAccess_stgOutInfo.u1SecLvSeed, sizeof(SecurityAccess_stgOutInfo.u1SecLvSeed), md);
	/* ƴ������ */
	memcpy(&md[32], ALGORITHM_FACTORS, 16);
	/* ����SHA256 */
	SHA256(md, sizeof(md), thash);
	/* ȡǰ16���ֽ���KEY */
	memcpy(key, thash, 16);
	aes_encrypt_ecb(key, 16, SecurityAccess_stgOutInfo.u1SecLvSeed, sizeof(SecurityAccess_stgOutInfo.u1SecLvSeed), 
		SecurityAccess_stgOutInfo.u1SecLvKey, &len);

}

/*************************************************************
* �������ƣ�AppDescSecurityAccessSendKey
* ������������ȫ������֤Key
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
*************************************************************/
void AppDescSecurityAccessSendKey(void)
{
	INT8U  Index;
	INT8U bKeyMatch = TRUE;
    INT32U calcLen = 0;

	
	cDescTesterPresentTimer = DESC_TESTER_PRESENT_TIME_OUT_DELAY_TIME;
	if(bSeedReceive == TRUE)
	{
		bSeedReceive = FALSE;

		/*����Ҫ�� unlocked ״̬���յ�Key���24*/
		if(unlockStatus == TRUE)
		{
			DescNrc = (kDescNrcRequestSequenceError);
			return;
		}
        (void)SeedToKey(SecurityAccess_stgOutInfo.u1SecLvSeed, 4, SecurityAccess_stgOutInfo.u1SecLvKey, &calcLen);

		
		/*TODO: ���������ʵ���㷨*/
//		SecurityAccess_vogKeyGenerate();
		for(Index = 0; Index < SecurityAccess_MLVKEYNUM; Index++)
		{
			if(TpRxInfoStruct.cDataBuf[2 + Index] != SecurityAccess_stgOutInfo.u1SecLvKey[Index])
			{
				bKeyMatch = FALSE;
				break;
			}
		}
		//bKeyMatch = TRUE;
		if(bKeyMatch)
		{
			Uds_AccessTimeRst();
			u1gSecurityAccessIsDelayEndFlg = TRUE;
			Com_RamSet(SecurityAccess_stgOutInfo.u1SecLvSeed, 0, SecurityAccess_MSEEDNUM);
			TpTxInfoStruct.wDataLength = 2;
			unlockStatus = TRUE;
			DescNrc = DescNrcOK;
		}
		else
		{
			/* Invalid Key, Denied */
			if(Uds_AccessTimesLmt() == FALSE)
			{
				DescNrc = (kDescNrcInvalidKey);
			}
			else//Attempt three times repeatedly
			{
				bSeedReceive = FALSE;
				DescNrc = (kDescNrcExceedNumOfAttempts);
			}
		}
		
	}
	else
	{
		DescNrc = (kDescNrcRequestSequenceError);
	}
}

/********************************************************************
* �������ƣ�DescSecurityAccess
* ������������ϰ�ȫ����
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void DescSecurityAccess(void)
{
	static INT32U t_resetTime = 0;
	INT8U  wIndex;
	INT8U u1tSubFun, u1tInfoLen;
	INT8U  cSecurityAccessSubFound = FALSE;
	BOOL  Err = FALSE;
	
	u1tInfoLen = (INT8U)TpRxInfoStruct.wDataLength;
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
		TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}

	/*���Ѻ�E2prom����������ʱ3s�ſ�ʹ�ã��ȴ�E2prom���ݼ���*/
	if(CPU_TimerDiffTs(t_resetTime) < D_RWE2PROMTIME)
	{
		DescNrc = kDescNrcBusyRepeatRequest;
		return;
	}
	
	if(!(u1tInfoLen == 2 || u1tInfoLen == 2 + SecurityAccess_MLVKEYNUM))
	{
		DescNrc = (kDescNrcIncorrectMessageLengthOrInvalidFormat);
		return;
	}
	
	if(cDescSession == SESN_DS)
	{
		DescNrc = kDescNrcServiceNotSupportedInActiveSession;
		return;
	}
	
	/*27����֧�ֽ�ֹ�϶���Ӧλ*/
	if(0x80U == (TpRxInfoStruct.cDataBuf[1] & 0x80U))
	{
		DescNrc = (kDescNrcSubfunctionNotSupported);
		return;
	}

	u1tSubFun = (INT8U)(TpRxInfoStruct.cDataBuf[1] & 0x7F);
	for(wIndex = 0; wIndex < UBOUND(cDesSecurityAccessSubID); wIndex++)
	{
		if(cDesSecurityAccessSubID[wIndex] == u1tSubFun)
		{
			/*  SubID Found */
			cSecurityAccessSubFound = TRUE;
		}
	}
	
	if(cSecurityAccessSubFound)
	{
		if(u1gSecurityAccessIsDelayEndFlg == TRUE)
		{
			
			if( ((u1tSubFun == DESC_SECURITY_ACCESS_REQUEST_EXTSEED) || \
			(u1tSubFun == DESC_SECURITY_ACCESS_SEND_EXTKEY) ) && (cDescSession != SESN_EXTDS) )
			{
				Err = TRUE;
			}
			else if(((u1tSubFun == DESC_SECURITY_ACCESS_REQUEST_REPROGRA) || \
			(u1tSubFun == DESC_SECURITY_ACCESS_SEND_REPROGRA)) && \
			(cDescSession != SESN_PRGS))
			{
				Err = TRUE;
			}
			if(FALSE == Err)
			{
				if( (u1tSubFun == DESC_SECURITY_ACCESS_REQUEST_EXTSEED) || \
				(u1tSubFun == DESC_SECURITY_ACCESS_REQUEST_REPROGRA) )
				{
					Desc_stsSecLvl.CurrLvl = (Desc_enSecLvl)((u1tSubFun + 1) / 2);
					Desc_vosSecAccessReqSeed();//��Ӧ����������seed 
				}
				else if( (u1tSubFun == DESC_SECURITY_ACCESS_SEND_EXTKEY) || \
				(u1tSubFun == DESC_SECURITY_ACCESS_SEND_REPROGRA) )
				{
					if(bSeedReceive == TRUE)
					{
						AppDescSecurityAccessSendKey();//��������Ƿ��͵�key
					}
					else
					{
						DescNrc = (kDescNrcRequestSequenceError);
					}
				}
				else
				{
					if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
					{
						DescNrc = (kDescNrcSubfunctionNotSupported);
					}
				}
			}
			else
			{
				DescNrc = kDescNrcSubfunctionNotSupportedInActiveSession;
				//DescNrc = kDescNrcServiceNotSupportedInActiveSession;//�ղ��淶û�иø���Ӧ��(kDescNrcSubfunctionNotSupportedInActiveSession);
			}
		}
		else
		{
			DescNrc = (kDescNrcTimeDelayNotExpired);
		}
	}
	else
	{
		if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
		{
			DescNrc = (kDescNrcSubfunctionNotSupported);
		}
	}
}


