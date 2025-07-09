/*!
************************************************************************************************************************
* @file uds_srv2a_readdatabyperiodicid.c
* @brief 
* @par ģ���������
       
* @par ģ���������
       
* @details 
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

#include "uds_pub.h"
#include "uds_srv2a_readdatabyperiodicid.h"

#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)

static void Uds2A_PeriodReadCurAntSchedTbl(void);
static void Uds2A_PeriodReadCurKey0Streng(void);
static void Uds2A_PeriodReadCurKey1Streng(void);
static void Uds2A_PeriodReadCurKeyPos(void);
static void Uds2A_RfTestDataHandle(void);

static const UdsPeriodDidCfg_t UdsDid_PeriodData[D_UDS_SUPPORT_PERIOD_DID_NUMBER] = {
    {D_UDS_PERIOD_DID_CUR_ANT_SCHED_LIST, Uds2A_PeriodReadCurAntSchedTbl},
    {D_UDS_PERIOD_DID_CUR_KEY0_STRENG, Uds2A_PeriodReadCurKey0Streng},
    {D_UDS_PERIOD_DID_CUR_KEY1_STRENG, Uds2A_PeriodReadCurKey1Streng},
    {D_UDS_PERIOD_DID_CUR_KEY_LOCAT, Uds2A_PeriodReadCurKeyPos},
    {D_UDS_PERIOD_DID_RF_TEST_DATA, Uds2A_RfTestDataHandle}
};

static UdsPeriodDidOpt_t UdsDid_PeriodOpt = {
    {0}, 0, D_UDS_DID_PERIOD_STOP_TRANS_MODE, 0
};


static BOOL Uds2A_TransModeSetting(INT8U mode, INT8U tInx);
static void Uds2A_PeriodTransCtrl(INT32U rate);
static BOOL Uds2A_RemovePeriodId(INT8U tInx);
static void Uds2A_RemoveArrayData(INT8U pDat[], INT8U tInx, INT8U len);
static BOOL Uds2A_SearchPeriodTxBuf(INT8U tInx);

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_2AReadPeriodDid(void)
* @par ����
       UDS��ȡ����did
* @param[in] TpRxInfoStruct��ȫ�ֱ������ã�uds�������ݻ���
* @param[in] UdsDid_PeriodData��ȫ�ֱ������ã�����DID�����б�
* @param[out] TpTxInfoStruct��ȫ�ֱ����޸ģ�uds�������ݻ���
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

void UdsApp_2AReadPeriodDid(void)
{
    INT8U i = 0;
    INT8U id = 0;
    INT8U tFindIdNum = 0; // ��������id����
    INT8U periodId[D_UDS_SUPPORT_PERIOD_DID_NUMBER] = {0};
    INT8U periodIdNum = 0;
    BOOL tFindInd = FALSE;
    BOOL tSetFailInd = FALSE;
    INT8U transMode = TpRxInfoStruct.cDataBuf[1];
    
    //�����ַ���
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
        TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
	//���ȼ��
    if ((TpRxInfoStruct.wDataLength < 3U)
     || ((2U + D_UDS_PERIOD_DID_MAX_TRANS_NUMBER) < TpRxInfoStruct.wDataLength)) 
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

    //�Ự����
    if (SESN_EXTDS != cDescSession)
    {
        DescNrc = kDescNrcConditionsNotCorrect;
		return;
    }
    
    //��ȫ��֤���
//    if(DescSessionSA_CfgChk(eSID_READ_PERIODIC_ID_INDEX)) // JMC �淶δ����
//	{
//		return; 
//	}

    //�жϴ���ģʽ
    if ((transMode < D_UDS_DID_PERIOD_SLOW_RATE_MODE) || (transMode > D_UDS_DID_PERIOD_STOP_TRANS_MODE))
    {
        DescNrc = (kDescNrcRequestOutOfRange);
		return;
    }
    
    //��ȡ����did������
    periodIdNum = TpRxInfoStruct.wDataLength - 2U;
    // ������������DID
    for (i = 0; i < periodIdNum; i++)
    {
        periodId[i] = TpRxInfoStruct.cDataBuf[2 + i];
        // ����ÿһ��֧�ֵ�DID
        for (id = 0; id < D_UDS_SUPPORT_PERIOD_DID_NUMBER; id++)
        {
            if (UdsDid_PeriodData[id].Uds_SupportPeriodDid == periodId[i]) // ƥ��idһ��
            {
                tFindIdNum++;
                if (TRUE != Uds2A_TransModeSetting(transMode, id))
                { // set id excption
                    tSetFailInd = TRUE;
                }
                break; // �ҵ�ƥ����˳�
            }
        }
    }

    if (tFindIdNum == periodIdNum) // ����������������յ�������һ�£�����Ϊȫ�����ҳɹ�
    {
        tFindInd = TRUE;
    }
    else
    {
        tFindInd = FALSE;
    }

	if (tFindInd == FALSE) //not find
	{
	    if (UdsDid_PeriodOpt.Uds_DidTransMode == D_UDS_DID_PERIOD_STOP_TRANS_MODE) // ��ǰ��ֹͣģʽ��didδ������Ҫ���
	    {
            UdsApp_2APeriodTransReset();
	    }
	    
	    DescNrc = (kDescNrcRequestOutOfRange);
		return;
	}
	else
	{
	    if (tSetFailInd == TRUE) // ����DID����������ʧ�ܵ�
		{
            DescNrc = (kDescNrcConditionsNotCorrect);
			return;
		}
		
        if (transMode != D_UDS_DID_PERIOD_STOP_TRANS_MODE)//ֹͣģʽ������ģʽ
        {
            UdsDid_PeriodOpt.Uds_DidTransMode = transMode;
        }
	}

	TpTxInfoStruct.wDataLength = 1;
	DescNrc = DescNrcOK;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_RemoveArrayData(INT8U pDat[], INT8U tInx, INT8U len)
* @par ����
       �Ƴ�����did�еڼ���id
* @param[in] INT8U tInx���Ƴ��ڼ�������
* @param[in] INT8U len�����ݵ��ܳ���
* @param[out] INT8U pDat[]����Ҫ����������
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_RemoveArrayData(INT8U pDat[], INT8U tInx, INT8U len)
{
    INT8U i = 0;

    if ((pDat == NULL) || (len == 0) || (len < tInx))
    {
        return;
    }

    for (i = tInx; i < (len - 1); i++)
    {
        pDat[i] = pDat[i + 1];
    }
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static BOOL Uds2A_RemovePeriodId(INT8U tInx)
* @par ����
       �Ƴ�һ�����ڷ��͵�DID
* @param[in] UdsDid_PeriodOpt��ȫ�ֱ������ã�����DID���仺��
* @param[out] UdsDid_PeriodOpt��ȫ�ֱ����޸ģ�����DID���仺��
* @returns BOOL���Ƿ��Ƴ��ɹ�
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static BOOL Uds2A_RemovePeriodId(INT8U tInx)
{
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;
    INT8U i = 0;
    BOOL removeInd = FALSE;
    //�������з�������DID
    for (i = 0; i < pOptDat->Uds_PeriodTxDidNum; i++)
    {
        if (pOptDat->Uds_PeriodTxDidInx[i] == tInx) // ����ƥ��DID
        {
            removeInd = TRUE;
            //remove periodic id
            Uds2A_RemoveArrayData(pOptDat->Uds_PeriodTxDidInx, i, pOptDat->Uds_PeriodTxDidNum);
			if (pOptDat->Uds_PeriodTxDidNum > 0)
            {
                pOptDat->Uds_PeriodTxDidNum--;
            }
            break;
        }
    }

    return removeInd;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static BOOL Uds2A_SearchPeriodTxBuf(INT8U tInx)
* @par ����
       �������ڷ��ͻ������Ƿ����ظ�
* @param[in] INT8U tInx������id����
* @param[out] void
* @param[in,out] void
* @returns BOOL���Ƿ����ڷ��ͻ�����
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-27
************************************************************************************************************************
*/

static BOOL Uds2A_SearchPeriodTxBuf(INT8U tInx)
{
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;
    INT8U i = 0;
    BOOL findInd = FALSE;

    for (i = 0; i < pOptDat->Uds_PeriodTxDidNum; i++)
    {
        if (pOptDat->Uds_PeriodTxDidInx[i] == tInx) // ����ƥ��DID
        {
            findInd = TRUE;
            break;
        }
    }

    return findInd;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static BOOL Uds2A_TransModeSetting(INT8U mode, INT8U tInx)
* @par ����
       ����DID����
* @param[in] INT8U mode�����ݴ���ģʽ
* @param[in] INT8U tInx������DID��������
* @param[out] UdsDid_PeriodOpt��ȫ�ֱ����޸ģ�����DID��������
* @returns BOOL���Ƿ����óɹ�
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static BOOL Uds2A_TransModeSetting(INT8U mode, INT8U tInx)
{
    BOOL setRes = FALSE;
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;

    if (tInx >= D_UDS_SUPPORT_PERIOD_DID_NUMBER)
    {
        return setRes;
    }

    switch (mode)
    {
        case D_UDS_DID_PERIOD_SLOW_RATE_MODE:
        case D_UDS_DID_PERIOD_MID_RATE_MODE:
        case D_UDS_DID_PERIOD_FAST_RATE_MODE:
            if (pOptDat->Uds_DidTransMode == D_UDS_DID_PERIOD_STOP_TRANS_MODE) // ������ֹͣʱ���£�����ǰ����������ģʽ�򲻸���
            {
                pOptDat->Uds_DidPeriodCnt = D_UDS_PERIOD_DID_START_DELAY;
                if (pOptDat->Uds_PeriodTxDidNum < D_UDS_SUPPORT_PERIOD_DID_NUMBER)
                {
                    if (Uds2A_SearchPeriodTxBuf(tInx) == FALSE) // ��ֹ�ظ����
                    {
                        pOptDat->Uds_PeriodTxDidInx[pOptDat->Uds_PeriodTxDidNum] = tInx;
                        pOptDat->Uds_PeriodTxDidNum++;
                    }
                    setRes = TRUE;
                }
            }
            
            break;
        case D_UDS_DID_PERIOD_STOP_TRANS_MODE:
            if (Uds2A_RemovePeriodId(tInx) == TRUE) // �Ƴ�һ������DID
            {
                setRes = TRUE;
            }
            
            if (pOptDat->Uds_PeriodTxDidNum == 0U) // ������DID��������Ϊ0�������ֹͣģʽ
            {
                UdsApp_2APeriodTransReset();
            }
            
            break;
        
        default: //����������֧��
            break;
    }

    return setRes;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_PeriodTransCtrl(INT32U rate)
* @par ����
       ����DID���Ϳ���
* @param[in] INT32U rate�����ڴ�������
* @param[out] UdsDid_PeriodOpt��ȫ�ֱ����޸ģ�����DID��������
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodTransCtrl(INT32U rate)
{   
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;
    static INT8U curTxNum = 0; // ��ǰѭ������DID��������
    static INT32U trgTxCnt = 0;
    
    if (pOptDat->Uds_DidPeriodCnt > 0)
    {
        pOptDat->Uds_DidPeriodCnt--;
    }
    if (pOptDat->Uds_DidPeriodCnt == 0)
    {
        pOptDat->Uds_DidPeriodCnt = D_UDS_PERIOD_DID_MULT_GAP_TIME;
        
        if (UdsDid_PeriodData[pOptDat->Uds_PeriodTxDidInx[curTxNum]].pUds_PeriodDidTxFunc != NULL)
        {
            UdsDid_PeriodData[pOptDat->Uds_PeriodTxDidInx[curTxNum]].pUds_PeriodDidTxFunc();
        }

        curTxNum++;
        // �жϵ�ǰ����DID�Ƿ�ȫ������
        if (curTxNum >= pOptDat->Uds_PeriodTxDidNum)
        {
            pOptDat->Uds_DidPeriodCnt = rate - trgTxCnt; //���ʱ�����ɵ�һ��did��ʼ��
            trgTxCnt = 0;
            curTxNum = 0;
        }
        else
        {
            trgTxCnt += D_UDS_PERIOD_DID_MULT_GAP_TIME; // û�з��꣬���㵱ǰ������ռ�õ�ʱ��
        }
        
    }
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_2APeriodSchedule(void)
* @par ����
       ���ڵ��ȷ�������did
* @param[in] UdsDid_PeriodOpt��ȫ�ֱ������ã�����DID��������
* @param[out] void
* @returns void
* @pre ��
* @note ��Ҫ5ms����
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

void UdsApp_2APeriodSchedule(void)
{
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;

    switch (pOptDat->Uds_DidTransMode)
    {
        case D_UDS_DID_PERIOD_SLOW_RATE_MODE:
            Uds2A_PeriodTransCtrl(D_UDS_DID_PERIOD_TX_SLOW);
            break;
            
        case D_UDS_DID_PERIOD_MID_RATE_MODE:
            Uds2A_PeriodTransCtrl(D_UDS_DID_PERIOD_TX_MID);
            break;
            
        case D_UDS_DID_PERIOD_FAST_RATE_MODE:
            Uds2A_PeriodTransCtrl(D_UDS_DID_PERIOD_TX_FAST);
            break;
            
        case D_UDS_DID_PERIOD_STOP_TRANS_MODE:
            pOptDat->Uds_DidPeriodCnt = 0xFFFFFFFFUL;
            break;
            
        default: //����ģʽ��֧��
            break;
    }
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_2APeriodTransReset(void)
* @par ����
       ��λ����DID����
* @param[in] void
* @param[out] UdsDid_PeriodOpt��ȫ�ֱ����޸ģ�����DID��������
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

void UdsApp_2APeriodTransReset(void)
{
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;

    pOptDat->Uds_DidTransMode = D_UDS_DID_PERIOD_STOP_TRANS_MODE;
    pOptDat->Uds_PeriodTxDidNum = 0;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_ReadCurAntScheTbl(INT8U pDat[], INT8U *pLen)
* @par ����
       ��ȡ���ߵ��ȱ�
* @param[in] void
* @param[out] INT8U pDat[]�����ȱ�
* @param[out] INT8U *pLen������
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-30
************************************************************************************************************************
*/

void UdsApp_ReadCurAntScheTbl(INT8U pDat[], INT8U *pLen)
{
    INT8U inx = 0;
    INT8U antSchedTblBuff[3] = {0};
    INT8U *antSchedTbl = antSchedTblBuff;

    Com_MemCmp(pDat, antSchedTbl, 3U);
    *pLen = 3U;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_ReadKey1Strength(INT8U pDat[], INT8U *pLen)
* @par ����
       ��ȡ��һ��Կ�׳�ǿ
* @param[in] void
* @param[out] INT8U pDat[]����ȡ���ݻ���
* @param[out] INT8U *pLen����ȡ����
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-30
************************************************************************************************************************
*/

void UdsApp_ReadKey1Strength(INT8U pDat[], INT8U *pLen)
{
    INT8U inx = 0U;
    INT16U AntStrengthBuff[3] = {0};
	INT16U *key1Streng = AntStrengthBuff;

    pDat[inx] = (INT8U)(key1Streng[0] >> 8U);
	inx++;
	pDat[inx] = (INT8U)(key1Streng[0]);
	inx++;
	pDat[inx] = (INT8U)(key1Streng[1] >> 8U);
	inx++;
	pDat[inx] = (INT8U)(key1Streng[1]);
	inx++;
	pDat[inx] = (INT8U)(key1Streng[2] >> 8U);
	inx++;

	*pLen = inx;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_ReadKey2Strength(INT8U pDat[], INT8U *pLen)
* @par ����
       ��ȡ�ڶ���Կ�׳�ǿ
* @param[in] void
* @param[out] INT8U pDat[]����ȡ���ݻ���
* @param[out] INT8U *pLen����ȡ����
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-30
************************************************************************************************************************
*/

void UdsApp_ReadKey2Strength(INT8U pDat[], INT8U *pLen)
{
    INT8U inx = 0U;
    INT16U AntStrengthBuff[3] = {0};
	INT16U *key2Streng = AntStrengthBuff;

    pDat[inx] = (INT8U)(key2Streng[0] >> 8U);
	inx++;
	pDat[inx] = (INT8U)(key2Streng[0]);
	inx++;
	pDat[inx] = (INT8U)(key2Streng[1] >> 8U);
	inx++;
	pDat[inx] = (INT8U)(key2Streng[1]);
	inx++;
	pDat[inx] = (INT8U)(key2Streng[2] >> 8U);
	inx++;

	*pLen = inx;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_ReadCurKeyPos(INT8U pDat[], INT8U *pLen)
* @par ����
       ��ȡԿ��λ��
* @param[in] void
* @param[out] INT8U pDat[]����ȡ���ݻ���
* @param[out] INT8U *pLen����ȡ����
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-30
************************************************************************************************************************
*/

void UdsApp_ReadCurKeyPos(INT8U pDat[], INT8U *pLen)
{
    INT8U inx = 0U;
    INT8U key1Pos = (INT8U)0;
    INT8U key2Pos = (INT8U)0;    
    INT8U uirSta = 0;
    INT8U walSta = 0;
    //Կ��λ��
	pDat[inx] = key1Pos;
	inx++;
	pDat[inx] = key2Pos;
	inx++;
	//PKE����״̬
	pDat[inx] = uirSta;
	inx++;
	pDat[inx] = walSta;
	inx++;

	*pLen = inx;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       void UdsApp_ReadRfTestData(INT8U pDat[], INT8U *pLen)
* @par ����
       ��ȡ��Ƶ��������
* @param[in] void
* @param[out] INT8U pDat[]����ȡ���ݻ���
* @param[out] INT8U *pLen����ȡ����
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-30
************************************************************************************************************************
*/

void UdsApp_ReadRfTestData(INT8U pDat[], INT8U *pLen)
{
    INT8U inx = 0U;
    const INT16U dataCrcSeed = 0xF5FAU;
    INT8U *pRfDat = NULL;
    INT16U crc = 0;
    BOOL rfDataInd = 0;
    
    //��Ƶ����ָʾ�ж�
    if (rfDataInd == TRUE)
    {
        pDat[inx] = rfDataInd;
        inx++;
        pDat[inx] = (INT8U)(crc >> 8U);
        inx++;
        pDat[inx] = (INT8U)crc;
        inx++;
    }
    else
    {
        pDat[inx] = 0x00;
        inx++;
        pDat[inx] = 0x00;
        inx++;
        pDat[inx] = 0x00;
        inx++;
    }

    *pLen = inx;
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_PeriodReadCurAntSchedTbl(void)
* @par ����
       ���ڷ��͵�ǰ���߹�������
* @param[in] void
* @param[out] TpTxInfoStruct��ȫ�ֱ����޸ģ�uds�������ݻ���
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodReadCurAntSchedTbl(void)
{
    INT8U inx = 0U;
    INT8U tLen = 0;
    
    //period did
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_ACTIVE_RESP;
	inx++;
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_CUR_ANT_SCHED_LIST;
	inx++;

    UdsApp_ReadCurAntScheTbl((INT8U *)&TpTxInfoStruct.cDataBuf[inx], &tLen);
    inx += tLen;

	TpTxInfoStruct.wDataLength = inx;
    TpTxStart();
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_PeriodReadCurKey0Streng(void)
* @par ����
       ���ڷ��͵�ǰ��һ��Կ�׳�ǿ
* @param[in] void
* @param[out] TpTxInfoStruct��ȫ�ֱ����޸ģ�uds�������ݻ���
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodReadCurKey0Streng(void)
{
    INT8U inx = 0U;
    INT8U tLen = 0;

	//period did
	TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_ACTIVE_RESP;
	inx++;	
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_CUR_KEY0_STRENG;
	inx++;

	UdsApp_ReadKey1Strength((INT8U *)&TpTxInfoStruct.cDataBuf[inx], &tLen);
	inx += tLen;

	TpTxInfoStruct.wDataLength = inx;
    TpTxStart();
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_PeriodReadCurKey1Streng(void)
* @par ����
       ���ڷ��͵�ǰ�ڶ���Կ�׳�ǿ
* @param[in] void
* @param[out] TpTxInfoStruct��ȫ�ֱ����޸ģ�uds�������ݻ���
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodReadCurKey1Streng(void)
{
    INT8U inx = 0U;
    INT8U tLen = 0;

	//period did
	TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_ACTIVE_RESP;
	inx++;
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_CUR_KEY1_STRENG;
	inx++;

	UdsApp_ReadKey2Strength((INT8U *)&TpTxInfoStruct.cDataBuf[inx], &tLen);
	inx += tLen;
	
	TpTxInfoStruct.wDataLength = inx;
    TpTxStart();
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_PeriodReadCurKeyPos(void)
* @par ����
       ���ڷ��͵�ǰԿ��λ��
* @param[in] void
* @param[out] TpTxInfoStruct��ȫ�ֱ����޸ģ�uds�������ݻ���
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodReadCurKeyPos(void)
{
    INT8U inx = 0U;
    INT8U tLen = 0;
    
    //period did
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_ACTIVE_RESP;
	inx++;
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_CUR_KEY_LOCAT;
	inx++;

	UdsApp_ReadCurKeyPos((INT8U *)&TpTxInfoStruct.cDataBuf[inx], &tLen);
	inx += tLen;

	TpTxInfoStruct.wDataLength = inx;

    TpTxStart();
}

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       static void Uds2A_RfTestDataHandle(void)
* @par ����
       ��Ƶ��������
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-12-18
************************************************************************************************************************
*/

static void Uds2A_RfTestDataHandle(void)
{
    INT8U inx = 0U;
    INT8U tLen = 0;

    //period did
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_ACTIVE_RESP;
	inx++;
    TpTxInfoStruct.cDataBuf[inx] = D_UDS_PERIOD_DID_RF_TEST_DATA;
	inx++;

	UdsApp_ReadRfTestData((INT8U *)&TpTxInfoStruct.cDataBuf[inx], &tLen);
	inx += tLen;

	TpTxInfoStruct.wDataLength = inx;

    TpTxStart();
}


#endif

