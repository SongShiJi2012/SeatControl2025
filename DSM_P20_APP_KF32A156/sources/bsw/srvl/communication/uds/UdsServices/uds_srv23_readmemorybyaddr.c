/*!
************************************************************************************************************************
* @file uds_srv23_readmemorybyaddr.c
* @brief 23读取内存服务
* @par 模块输入参数
       
* @par 模块输出参数
       
* @details 
* @author Lews Hammond(刘发星)
* @date 2020-5-20
************************************************************************************************************************
*/

#include "uds_pub.h"

#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)
/*! @brief 23服务读取内存地址范围限制表 */
static const INT32U Uds_ReadMemAddrLmt[D_UDS_READ_MEMORY_START_ADDR][2] = {
    {0xFEE00000u, 0xFEE07FFFu}, /* Retention RAM (32 KB) */
	{0xFEDE0000u, 0xFEDFFFFFu},	 /* Primary Local RAM (128 KB) */
	{0xFEDD8000u, 0xFEDDFFFFu},  /* Secondary Local RAM (32 KB) */
	
	{0xFF200000u, 0xFF207FFFu},  /* Data Flash (32 KB) */
	
	{0x01000000u, 0x01007FFFu},  /* Code Flash (32 KB) */
	{0x00000000u, 0x001FFFFFu},  /* Code Flash (2 MB) */
	
};

static void UdsApp_23ReadMemoryHandle(INT32U startAddr, INT16U dataLen);

/*!
************************************************************************************************************************
* @par 接口原型
       void UdsApp_23ReadMemoryByAddr(void)
* @par 描述
       23服务处理
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2020-5-20
************************************************************************************************************************
*/

void UdsApp_23ReadMemoryByAddr(void)
{
    const INT8U tAddrAndLenFormat = (INT8U)((D_UDS_READ_MEMORY_LEN_FORMAT << 4u) | (D_UDS_READ_MEMORY_ADDR_FORMAT));
    INT8U i = 0;
    INT32U tStartAddr = 0;
    INT32U tEndAddr = 0;
    INT16U tReadMemLen = 0;
    BOOL tMemReadInd = FALSE;
    
    //请求地址检测
    if((INT8U)TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
    {
        TpRxState.engine = kRxState_Idle;
        DescNrc = DescNrcNoRsp;
        return;
    }
    //长度检测
    if (TpRxInfoStruct.wDataLength != (2u + D_UDS_READ_MEMORY_ADDR_FORMAT + D_UDS_READ_MEMORY_LEN_FORMAT))
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
    if (unlockStatus == FALSE)//安全访问没有通过
    {
        //DescNrc = kDescNrcAccessDenied;
        //return;
    }
    // 运行条件检测
    if (UdsApp_GetSysOnlineTestModeInd() == FALSE)
    {
        //DescNrc = kDescNrcConditionsNotCorrect;
        //return;
    }
    //格式检测
    if (tAddrAndLenFormat != TpRxInfoStruct.cDataBuf[1])
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
    // 获取服务请求地址和长度
    tStartAddr = ((INT32U)TpRxInfoStruct.cDataBuf[2] & 0x000000FFu);
    tStartAddr <<= 8u;
    tStartAddr |= ((INT32U)TpRxInfoStruct.cDataBuf[3] & 0x000000FFu);
    tStartAddr <<= 8u;
    tStartAddr |= ((INT32U)TpRxInfoStruct.cDataBuf[4] & 0x000000FFu);
    tStartAddr <<= 8u;
    tStartAddr |= ((INT32U)TpRxInfoStruct.cDataBuf[5] & 0x000000FFu);

    tReadMemLen = ((INT16U)TpRxInfoStruct.cDataBuf[6] & 0x00FFu);
    tReadMemLen <<= 8u;
    tReadMemLen |= ((INT16U)TpRxInfoStruct.cDataBuf[7] & 0x00FFu);

    tEndAddr = tStartAddr + (INT32U)tReadMemLen - 1u; // 包含起始地址本身
    // 读取长度检测
    if ((tReadMemLen > D_UDS_READ_MEMORY_LENGTH_LIMIT)
     || (tReadMemLen == 0U))
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
    
    for (i = 0; i < D_UDS_READ_MEMORY_START_ADDR; i++)
    {
        // 判断起始和结束地址都要在范围内
        if ((tStartAddr >= Uds_ReadMemAddrLmt[i][0]) && (tStartAddr <= Uds_ReadMemAddrLmt[i][1]) 
         && (tEndAddr >= Uds_ReadMemAddrLmt[i][0]) && (tEndAddr <= Uds_ReadMemAddrLmt[i][1]))
        {
            tMemReadInd = TRUE;
            break;
        }
    }

    if (tMemReadInd == TRUE)
    {
        UdsApp_23ReadMemoryHandle(tStartAddr, tReadMemLen);
    }
    else
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
    
}

/*!
************************************************************************************************************************
* @par 接口原型
       static void UdsApp_23ReadMemoryHandle(INT32U startAddr, INT16U dataLen)
* @par 描述
       读取内存数据处理
* @param[in] INT32U startAddr：起始地址
* @param[in] INT16U dataLen：数据长度
* @param[out] void
* @param[in,out] void
* @returns void
* @pre 无
* @note 无
* @author Lews Hammond(刘发星)
* @date 2020-5-20
************************************************************************************************************************
*/

static void UdsApp_23ReadMemoryHandle(INT32U startAddr, INT16U dataLen)
{
    INT16U i = 0;
    INT16U udsBufIndex = 1;

    for (i = 0; i < dataLen; i++)
    {
        TpTxInfoStruct.cDataBuf[udsBufIndex] = (INT8U)(*((INT8U *)startAddr));
        udsBufIndex++;
        startAddr++;
    }

    TpTxInfoStruct.wDataLength = udsBufIndex;
    DescNrc = DescNrcOK;
}


#endif

