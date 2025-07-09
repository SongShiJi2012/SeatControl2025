/*!
************************************************************************************************************************
* @file uds_srv2a_readdatabyperiodicid.c
* @brief 
* @par 模块输入参数
       
* @par 模块输出参数
       
* @details 
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       void UdsApp_2AReadPeriodDid(void)
* @par 描述
       UDS读取周期did
* @param[in] TpRxInfoStruct：全局变量引用，uds接收数据缓存
* @param[in] UdsDid_PeriodData：全局变量引用，周期DID配置列表
* @param[out] TpTxInfoStruct：全局变量修改，uds发送数据缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-10-18
************************************************************************************************************************
*/

void UdsApp_2AReadPeriodDid(void)
{
    INT8U i = 0;
    INT8U id = 0;
    INT8U tFindIdNum = 0; // 搜索到的id数量
    INT8U periodId[D_UDS_SUPPORT_PERIOD_DID_NUMBER] = {0};
    INT8U periodIdNum = 0;
    BOOL tFindInd = FALSE;
    BOOL tSetFailInd = FALSE;
    INT8U transMode = TpRxInfoStruct.cDataBuf[1];
    
    //请求地址检测
	if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
	{
        TpRxState.engine = kRxState_Idle;
		DescNrc = DescNrcNoRsp;
		return;
	}
	//长度检测
    if ((TpRxInfoStruct.wDataLength < 3U)
     || ((2U + D_UDS_PERIOD_DID_MAX_TRANS_NUMBER) < TpRxInfoStruct.wDataLength)) 
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}

    //会话层检测
    if (SESN_EXTDS != cDescSession)
    {
        DescNrc = kDescNrcConditionsNotCorrect;
		return;
    }
    
    //安全认证检测
//    if(DescSessionSA_CfgChk(eSID_READ_PERIODIC_ID_INDEX)) // JMC 规范未定义
//	{
//		return; 
//	}

    //判断传输模式
    if ((transMode < D_UDS_DID_PERIOD_SLOW_RATE_MODE) || (transMode > D_UDS_DID_PERIOD_STOP_TRANS_MODE))
    {
        DescNrc = (kDescNrcRequestOutOfRange);
		return;
    }
    
    //获取周期did的数量
    periodIdNum = TpRxInfoStruct.wDataLength - 2U;
    // 解析查找周期DID
    for (i = 0; i < periodIdNum; i++)
    {
        periodId[i] = TpRxInfoStruct.cDataBuf[2 + i];
        // 遍历每一个支持的DID
        for (id = 0; id < D_UDS_SUPPORT_PERIOD_DID_NUMBER; id++)
        {
            if (UdsDid_PeriodData[id].Uds_SupportPeriodDid == periodId[i]) // 匹配id一致
            {
                tFindIdNum++;
                if (TRUE != Uds2A_TransModeSetting(transMode, id))
                { // set id excption
                    tSetFailInd = TRUE;
                }
                break; // 找到匹配项，退出
            }
        }
    }

    if (tFindIdNum == periodIdNum) // 搜索到的数量与接收到的数量一致，则认为全部查找成功
    {
        tFindInd = TRUE;
    }
    else
    {
        tFindInd = FALSE;
    }

	if (tFindInd == FALSE) //not find
	{
	    if (UdsDid_PeriodOpt.Uds_DidTransMode == D_UDS_DID_PERIOD_STOP_TRANS_MODE) // 当前是停止模式，did未找齐需要清除
	    {
            UdsApp_2APeriodTransReset();
	    }
	    
	    DescNrc = (kDescNrcRequestOutOfRange);
		return;
	}
	else
	{
	    if (tSetFailInd == TRUE) // 找齐DID，但有设置失败的
		{
            DescNrc = (kDescNrcConditionsNotCorrect);
			return;
		}
		
        if (transMode != D_UDS_DID_PERIOD_STOP_TRANS_MODE)//停止模式不更新模式
        {
            UdsDid_PeriodOpt.Uds_DidTransMode = transMode;
        }
	}

	TpTxInfoStruct.wDataLength = 1;
	DescNrc = DescNrcOK;
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void Uds2A_RemoveArrayData(INT8U pDat[], INT8U tInx, INT8U len)
* @par 描述
       移除周期did中第几个id
* @param[in] INT8U tInx：移除第几个数据
* @param[in] INT8U len：数据的总长度
* @param[out] INT8U pDat[]：需要操作的数据
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       static BOOL Uds2A_RemovePeriodId(INT8U tInx)
* @par 描述
       移除一个周期发送的DID
* @param[in] UdsDid_PeriodOpt：全局变量引用，周期DID传输缓存
* @param[out] UdsDid_PeriodOpt：全局变量修改，周期DID传输缓存
* @returns BOOL：是否移除成功
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-10-18
************************************************************************************************************************
*/

static BOOL Uds2A_RemovePeriodId(INT8U tInx)
{
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;
    INT8U i = 0;
    BOOL removeInd = FALSE;
    //遍历所有发送周期DID
    for (i = 0; i < pOptDat->Uds_PeriodTxDidNum; i++)
    {
        if (pOptDat->Uds_PeriodTxDidInx[i] == tInx) // 查找匹配DID
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
* @par 接口原型
       static BOOL Uds2A_SearchPeriodTxBuf(INT8U tInx)
* @par 描述
       搜索周期发送缓存中是否有重复
* @param[in] INT8U tInx：发送id索引
* @param[out] void
* @param[in,out] void
* @returns BOOL：是否已在发送缓存中
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
        if (pOptDat->Uds_PeriodTxDidInx[i] == tInx) // 查找匹配DID
        {
            findInd = TRUE;
            break;
        }
    }

    return findInd;
}

/*!
************************************************************************************************************************
* @par 接口原型
       static BOOL Uds2A_TransModeSetting(INT8U mode, INT8U tInx)
* @par 描述
       周期DID设置
* @param[in] INT8U mode：数据传输模式
* @param[in] INT8U tInx：周期DID配置索引
* @param[out] UdsDid_PeriodOpt：全局变量修改，周期DID操作缓存
* @returns BOOL：是否设置成功
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
            if (pOptDat->Uds_DidTransMode == D_UDS_DID_PERIOD_STOP_TRANS_MODE) // 仅能在停止时更新，若当前在其他传输模式则不更新
            {
                pOptDat->Uds_DidPeriodCnt = D_UDS_PERIOD_DID_START_DELAY;
                if (pOptDat->Uds_PeriodTxDidNum < D_UDS_SUPPORT_PERIOD_DID_NUMBER)
                {
                    if (Uds2A_SearchPeriodTxBuf(tInx) == FALSE) // 防止重复添加
                    {
                        pOptDat->Uds_PeriodTxDidInx[pOptDat->Uds_PeriodTxDidNum] = tInx;
                        pOptDat->Uds_PeriodTxDidNum++;
                    }
                    setRes = TRUE;
                }
            }
            
            break;
        case D_UDS_DID_PERIOD_STOP_TRANS_MODE:
            if (Uds2A_RemovePeriodId(tInx) == TRUE) // 移除一个周期DID
            {
                setRes = TRUE;
            }
            
            if (pOptDat->Uds_PeriodTxDidNum == 0U) // 当周期DID发送数量为0，则进入停止模式
            {
                UdsApp_2APeriodTransReset();
            }
            
            break;
        
        default: //其他参数不支持
            break;
    }

    return setRes;
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void Uds2A_PeriodTransCtrl(INT32U rate)
* @par 描述
       周期DID发送控制
* @param[in] INT32U rate：周期传输速率
* @param[out] UdsDid_PeriodOpt：全局变量修改，周期DID操作缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2019-10-18
************************************************************************************************************************
*/

static void Uds2A_PeriodTransCtrl(INT32U rate)
{   
    UdsPeriodDidOpt_t *pOptDat = &UdsDid_PeriodOpt;
    static INT8U curTxNum = 0; // 当前循环周期DID发送数量
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
        // 判断当前周期DID是否全部发完
        if (curTxNum >= pOptDat->Uds_PeriodTxDidNum)
        {
            pOptDat->Uds_DidPeriodCnt = rate - trgTxCnt; //间隔时间是由第一个did开始计
            trgTxCnt = 0;
            curTxNum = 0;
        }
        else
        {
            trgTxCnt += D_UDS_PERIOD_DID_MULT_GAP_TIME; // 没有发完，计算当前周期已占用的时间
        }
        
    }
}

/*!
************************************************************************************************************************
* @par 接口原型
       void UdsApp_2APeriodSchedule(void)
* @par 描述
       周期调度发送周期did
* @param[in] UdsDid_PeriodOpt：全局变量引用，周期DID操作缓存
* @param[out] void
* @returns void
* @pre 无
* @note 需要5ms调度
* @author Lews Hammond(刘发星)
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
            
        default: //其他模式不支持
            break;
    }
}

/*!
************************************************************************************************************************
* @par 接口原型
       void UdsApp_2APeriodTransReset(void)
* @par 描述
       复位周期DID传输
* @param[in] void
* @param[out] UdsDid_PeriodOpt：全局变量修改，周期DID操作缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       void UdsApp_ReadCurAntScheTbl(INT8U pDat[], INT8U *pLen)
* @par 描述
       读取天线调度表
* @param[in] void
* @param[out] INT8U pDat[]：调度表
* @param[out] INT8U *pLen：表长度
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       void UdsApp_ReadKey1Strength(INT8U pDat[], INT8U *pLen)
* @par 描述
       读取第一把钥匙场强
* @param[in] void
* @param[out] INT8U pDat[]：读取数据缓存
* @param[out] INT8U *pLen：读取长度
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       void UdsApp_ReadKey2Strength(INT8U pDat[], INT8U *pLen)
* @par 描述
       读取第二把钥匙场强
* @param[in] void
* @param[out] INT8U pDat[]：读取数据缓存
* @param[out] INT8U *pLen：读取长度
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       void UdsApp_ReadCurKeyPos(INT8U pDat[], INT8U *pLen)
* @par 描述
       读取钥匙位置
* @param[in] void
* @param[out] INT8U pDat[]：读取数据缓存
* @param[out] INT8U *pLen：读取长度
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
    //钥匙位置
	pDat[inx] = key1Pos;
	inx++;
	pDat[inx] = key2Pos;
	inx++;
	//PKE工作状态
	pDat[inx] = uirSta;
	inx++;
	pDat[inx] = walSta;
	inx++;

	*pLen = inx;
}

/*!
************************************************************************************************************************
* @par 接口原型
       void UdsApp_ReadRfTestData(INT8U pDat[], INT8U *pLen)
* @par 描述
       读取高频测试数据
* @param[in] void
* @param[out] INT8U pDat[]：读取数据缓存
* @param[out] INT8U *pLen：读取长度
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
    
    //高频数据指示判断
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
* @par 接口原型
       static void Uds2A_PeriodReadCurAntSchedTbl(void)
* @par 描述
       周期发送当前天线工作序列
* @param[in] void
* @param[out] TpTxInfoStruct：全局变量修改，uds发送数据缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       static void Uds2A_PeriodReadCurKey0Streng(void)
* @par 描述
       周期发送当前第一把钥匙场强
* @param[in] void
* @param[out] TpTxInfoStruct：全局变量修改，uds发送数据缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       static void Uds2A_PeriodReadCurKey1Streng(void)
* @par 描述
       周期发送当前第二把钥匙场强
* @param[in] void
* @param[out] TpTxInfoStruct：全局变量修改，uds发送数据缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       static void Uds2A_PeriodReadCurKeyPos(void)
* @par 描述
       周期发送当前钥匙位置
* @param[in] void
* @param[out] TpTxInfoStruct：全局变量修改，uds发送数据缓存
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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
* @par 接口原型
       static void Uds2A_RfTestDataHandle(void)
* @par 描述
       高频测试数据
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
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

