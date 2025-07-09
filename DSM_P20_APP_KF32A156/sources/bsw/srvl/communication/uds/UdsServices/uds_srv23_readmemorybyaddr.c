/*!
************************************************************************************************************************
* @file uds_srv23_readmemorybyaddr.c
* @brief 23��ȡ�ڴ����
* @par ģ���������
       
* @par ģ���������
       
* @details 
* @author Lews Hammond(������)
* @date 2020-5-20
************************************************************************************************************************
*/

#include "uds_pub.h"

#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)
/*! @brief 23�����ȡ�ڴ��ַ��Χ���Ʊ� */
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
* @par �ӿ�ԭ��
       void UdsApp_23ReadMemoryByAddr(void)
* @par ����
       23������
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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
    
    //�����ַ���
    if((INT8U)TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
    {
        TpRxState.engine = kRxState_Idle;
        DescNrc = DescNrcNoRsp;
        return;
    }
    //���ȼ��
    if (TpRxInfoStruct.wDataLength != (2u + D_UDS_READ_MEMORY_ADDR_FORMAT + D_UDS_READ_MEMORY_LEN_FORMAT))
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
    if (unlockStatus == FALSE)//��ȫ����û��ͨ��
    {
        //DescNrc = kDescNrcAccessDenied;
        //return;
    }
    // �����������
    if (UdsApp_GetSysOnlineTestModeInd() == FALSE)
    {
        //DescNrc = kDescNrcConditionsNotCorrect;
        //return;
    }
    //��ʽ���
    if (tAddrAndLenFormat != TpRxInfoStruct.cDataBuf[1])
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
    // ��ȡ���������ַ�ͳ���
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

    tEndAddr = tStartAddr + (INT32U)tReadMemLen - 1u; // ������ʼ��ַ����
    // ��ȡ���ȼ��
    if ((tReadMemLen > D_UDS_READ_MEMORY_LENGTH_LIMIT)
     || (tReadMemLen == 0U))
    {
        DescNrc = kDescNrcRequestOutOfRange;
        return;
    }
    
    for (i = 0; i < D_UDS_READ_MEMORY_START_ADDR; i++)
    {
        // �ж���ʼ�ͽ�����ַ��Ҫ�ڷ�Χ��
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
* @par �ӿ�ԭ��
       static void UdsApp_23ReadMemoryHandle(INT32U startAddr, INT16U dataLen)
* @par ����
       ��ȡ�ڴ����ݴ���
* @param[in] INT32U startAddr����ʼ��ַ
* @param[in] INT16U dataLen�����ݳ���
* @param[out] void
* @param[in,out] void
* @returns void
* @pre ��
* @note ��
* @author Lews Hammond(������)
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

