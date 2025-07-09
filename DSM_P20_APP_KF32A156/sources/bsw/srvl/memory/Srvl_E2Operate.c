#include <stdint.h>
#include "lpi2c_driver.h"
#include "ecual_i2c.h"
#include "Srvl_E2Operate.h"
#include "Srvl_E2memory.h"
#include "Srvl_E2cfg.h"
#include "ecual_wdog.h"
#include "Srvl_Eeprom.h"

#define EEPROM_I2C  	LPI2C_INSTANCE_0

typedef struct
{
    uint32_t EERAMBase;
    uint32_t EEESize;
} E2_config_t_AT24C16_;

static const E2_config_t_AT24C16_ e2Config = {
    .EERAMBase = EEPROM_ADDRESS,   /* E2PROM��ʼ��ַ о��΢ʹ���ⲿE2 �ͺţ� */
    .EEESize = EEPROM_SIZE,	/* AT24C16 ���� 2KB  */
};

EEPROMInfoStructType E2PROMOpInfo;
static INT8U gu8EepromWriteBuffer[EEPROMBUFFMAXNUM];
static INT8U gu8EepromReadBuffer[EEPROMBUFFMAXNUM];
static void Srvl_SetDataBlockWriteReq(INT16U DataBlockID);

/***********************************************************************************************
 * @function name:  Srvl_E2OptInit
 * @description:    EEPROM����״̬��ʼ��
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2OptInit(void)
{
	ecual_I2C_init(EEPROM_I2C, 500000);

	E2PROMOpInfo.OperateState = EEPROM_IDLE;
	E2PROMOpInfo.OpIndex = 0;
	E2PROMOpInfo.OpType = EEOpNULL;
}
/***********************************************************************************************
 * @function name:  Srvl_E2DataCompare
 * @description:    �Ƚ� EEPROM ��ָ����ַ��������������ݻ������������Ƿ���ͬ
 * @input parameters:
 *     INT32U lu32Dest      // Ŀ���ַ�����Ե�ַ��
 *     INT32U lu32Size      // �Ƚϵ����ݳ��ȣ���λ���ֽڣ�
 *     const INT8U* lpu8DataBuf   // ���Ƚϵ����ݻ�����ָ��
 * @output parameters:     void
 * @return:         ���رȽϽ����D_Ok ��ʾ����ƥ�䣬D_ParaErr ��ʾ��ַ��������D_DataErr ��ʾ���ݲ�ƥ��
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static INT8U Srvl_E2DataCompare(INT32U lu32Dest, INT32U lu32Size, const INT8U* lpu8DataBuf)
{
	INT8U Databuf[lu32Size];
	INT32U i = 0;
    if ((lu32Dest + lu32Size - e2Config.EERAMBase) > e2Config.EEESize)
    {
        return D_ParaErr;
    }

	if (lu32Size == 0)
	{
		return D_Ok;
	}

	Srvl_Eeprom_Read(lu32Dest - e2Config.EERAMBase, lu32Size, (INT32U *)Databuf);

	while (i < lu32Size)
	{
		/* ��һ���ֽ� */
		if (lpu8DataBuf[i] != Databuf[i])
		{
			return D_DataErr;
		}
		i ++;
	}
	return D_Ok;
}

/***********************************************************************************************
 * @function name:  Srvl_E2Read
 * @description:    �� EEPROM �ж�ȡָ����ַ�ͳ��ȵ����ݵ�������
 * @input parameters:
 *     INT32U lu32Dest      // Ŀ���ȡ��ַ�����Ե�ַ��
 *     INT32U lu32Size      // ��ȡ�����ݳ��ȣ���λ���ֽڣ�
 *     INT8U *lpu8ReadBuf   // ���ݶ�ȡ���������ָ��
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2Read(INT32U lu32Dest, INT32U lu32Size, INT8U *lpu8ReadBuf)
{
	/* �����ȡ�����ݳ���Ϊ0���߳�������Flash��ַ�ռ䣬��ֱ�ӷ��� */
	if((lu32Size == 0) || ((lu32Dest + lu32Size - e2Config.EERAMBase) > e2Config.EEESize))
	{
		return;
	}
	//ecual_I2C_read(EEPROM_I2C,lu32Dest - e2Config.EERAMBase,lpu8ReadBuf,lu32Size);
	Srvl_Eeprom_Read(lu32Dest - e2Config.EERAMBase, lu32Size, (INT32U *)lpu8ReadBuf);
}

/***********************************************************************************************
 * @function name:  Srvl_E2Write
 * @description:    �� EEPROM ��ָ����ַд�����ݣ�������д��������У�飬��У�鲻ͨ���������д 3 ��
 * @input parameters:
 *     INT32U lu32Dest      // Ŀ���ַ�����Ե�ַ��
 *     INT32U lu32Size      // д������ݳ��ȣ���λ���ֽڣ�
 *     const INT8U* lpu8DataBuf   // ��д������ݻ�����ָ��
 * @output parameters:     void
 * @return:         ����д������D_Success ��ʾ�ɹ���D_ParaErr ��ʾ��������D_E2_WriteWait ��ʾ�ȴ����ԣ�D_Failure ��ʾд��ʧ��
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
INT8U Srvl_E2Write(INT32U lu32Dest, INT32U lu32Size, const INT8U * lpu8DataBuf)
{
	static INT8U lu8Cnt = 0;
	FEE_StatusType len_Ret = FEE_STATUS_ADDR_ERR;

	if ((lu32Dest + lu32Size - e2Config.EERAMBase) > e2Config.EEESize)
	{
		return D_ParaErr;
	}

	if (lu32Size == 0)
	{
		return D_Success;
	}

	/* д��֮�����У�飬�������ȷ����д�����3�� */
	if (e2Config.EEESize != 0u)
	{
		len_Ret = Srvl_Eeprom_Write(lu32Dest - e2Config.EERAMBase, lu32Size, (const INT32U *)lpu8DataBuf);
	}
	else
	{
		return D_Failure;
	}

	if(len_Ret == FEE_STATUS_OK)
	{
		if (Srvl_E2DataCompare(lu32Dest, lu32Size, lpu8DataBuf) == D_Ok)
		{
			lu8Cnt = 0;
			return D_Success;
		}
		else
		{
			//��д
			if(lu8Cnt < 3)
			{
				lu8Cnt ++;
				return D_E2_WriteWait;
			}
			else
			{
				lu8Cnt = 0;
				return D_Failure;
			}
		}
	}

	return D_Failure;
}
/***********************************************************************************************
 * @function name:  Srvl_E2ReadTask
 * @description:    ��ȡ EEPROM �е����ݣ�������У�顣��У��ͨ���������ݴ洢��ָ����������
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           �ú�������ݲ���״̬��ȡ���ݲ�����У�飬��У��ͨ���������ݱ��浽ָ��λ�ã���������Ϊ��ȡ����״̬��
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2ReadTask(void)
{
	INT16U  Index;
	INT8U  CheckSum;
    INT8U ResultSts = 0;

	if((E2PROMOpInfo.DataNum) < EEPROMBUFFMAXNUM)
	{
		//Srvl_E2Read(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, gu8EepromReadBuffer); /*��ȡ����+У���*/
        ResultSts = Srvl_Eeprom_Read(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, (INT32U *)gu8EepromReadBuffer);
        if(ResultSts != STATUS_SUCCESS)
        {
            memset(gu8EepromReadBuffer,0xFF,E2PROMOpInfo.DataNum); // ��ʧ���建�档
            E2PROMOpInfo.OperateState = EEPROM_READ_ERROR;
            return;
        }

		for(Index = 0x00, CheckSum = 0x00; Index < E2PROMOpInfo.DataNum - 1; Index++)
		{
			CheckSum += gu8EepromReadBuffer[Index];
		}

		if(CheckSum == gu8EepromReadBuffer[E2PROMOpInfo.DataNum - 1]) /*�����ۼӺͺ�,��ֵ����*/
		{
			for(Index = 0x00, CheckSum = 0x00; Index < E2PROMOpInfo.DataNum; Index++)
			{
				*((INT8U *)(E2PROMOpInfo.pData + Index))  = gu8EepromReadBuffer[Index];
				E2PROMOpInfo.OperateState = EEPROM_READ_SUCCESS;
			}
		}
		else
		{
			E2PROMOpInfo.OperateState = EEPROM_READ_ERROR;
		}
	}
	else
	{
		E2PROMOpInfo.OperateState = EEPROM_READ_ERROR;
	}
}

/***********************************************************************************************
 * @function name:  Srvl_E2WriteTask
 * @description:    д�����ݵ� EEPROM��������У��ͽ�����֤����д��ɹ������²���״̬����ʧ�ܣ�����Ϊд�����״̬��
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           �ú����Ὣ���ݺ�У���д�� EEPROM��������д�������²���״̬��
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2WriteTask(void)
{
	INT16U	  Index;
	status_t len_Ret = STATUS_ERROR;

	if((E2PROMOpInfo.DataNum) < EEPROMBUFFMAXNUM)
	{
		/*ȡֵ,�����ۼӺ�*/
		E2PROMOpInfo.WriteCheckSum = 0;
		for(Index = 0; Index < E2PROMOpInfo.DataNum - 1; Index ++)
		{
			gu8EepromWriteBuffer[Index] = *((INT8U *)(E2PROMOpInfo.pData + Index));
			E2PROMOpInfo.WriteCheckSum += gu8EepromWriteBuffer[Index];
		}
		gu8EepromWriteBuffer[E2PROMOpInfo.DataNum - 1] = E2PROMOpInfo.WriteCheckSum;

		len_Ret = Srvl_E2Write(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, gu8EepromWriteBuffer); /*����+У���*/
		if(len_Ret == D_Success)
		{
			E2PROMOpInfo.OperateState = EEPROM_VERIFY_SUCCESS;
		}
		else if(len_Ret == D_Failure)
		{
			E2PROMOpInfo.OperateState = EEPROM_WRITE_ERROR;
		}
		else
		{
			E2PROMOpInfo.OperateState = EEPROM_WRITE_START;
		}
	}
	else
	{
		E2PROMOpInfo.OperateState = EEPROM_WRITE_ERROR;
	}
}

/***********************************************************************************************
 * @function name:  Srvl_RestoreDataFromBackUpID
 * @description:    �ӱ���ID�ָ����ݣ������������ݿ�����Ŀ�����ݿ��С�
 * @input parameters:     INT16U DataBlockId - ���ݿ�ID
 * @output parameters:     void
 * @return:         void
 * @note:           �ú�����������ݿ�ID��鱸��ID�������ڱ������ݣ��򽫱������ݻָ���Ŀ�����ݿ顣
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_RestoreDataFromBackUpID(INT16U DataBlockId)
{
	INT8U *Sdata = NULL;
	INT8U *Tdata = NULL;
	INT8U len = 0;

	if(Srvl_GetE2DataBlockBackUpID(DataBlockId) != D_NOBACKUP)
	{
		Sdata = Srvl_GetE2DataBlockBufferPtr(Srvl_GetE2DataBlockBackUpID(DataBlockId));
		Tdata = Srvl_GetE2DataBlockBufferPtr(DataBlockId);
		len = Srvl_GetE2DataBlockLength(DataBlockId);
		memcpy(Tdata, Sdata, len);
	}
}

/***********************************************************************************************
 * @function name:  Srvl_WriteDataToBackUpID
 * @description:    �����ݿ�ID�е�����д�뵽����ID��Ӧ�����ݿ��С�
 * @input parameters:     INT16U DataBlockId - ���ݿ�ID
 * @output parameters:     void
 * @return:         void
 * @note:           �ú�����������ݿ�ID��ȡ����ID��������ڱ���ID����Ŀ�����ݿ��е�����д�뵽�������ݿ顣
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_WriteDataToBackUpID(INT16U DataBlockId)
{
	INT8U *Sdata = NULL;
	INT8U *Tdata = NULL;
	INT8U len = 0;

	if(Srvl_GetE2DataBlockBackUpID(DataBlockId) != D_NOBACKUP)
	{
		Sdata = Srvl_GetE2DataBlockBufferPtr(DataBlockId);
		Tdata = Srvl_GetE2DataBlockBufferPtr(Srvl_GetE2DataBlockBackUpID(DataBlockId));
		len = Srvl_GetE2DataBlockLength(DataBlockId);
		memcpy(Tdata, Sdata, len);
	}
}
/***********************************************************************************************
 * @function name:  Srvl_SetE2DataBlockToFF
 * @description:    �������ݿ�ID������Ӧ�����ݿ�RAM�������Ϊ0xFF
 * @input parameters:     INT16U DataBlockID��E2���ݿ�ID
 * @output parameters:     void
 * @return:         void
 * @note:           ͨ��ID��ȡ���ݿ�RAM��ַ�ͳ��ȣ������Ϊ0xFF
 * @author:         ssj 2025-05-20
 ***********************************************************************************************/
static void Srvl_SetE2DataBlockToFF(INT16U DataBlockID)
{
	INT8U *pData = NULL;
	INT8U len = 0;

	pData = Srvl_GetE2DataBlockBufferPtr(DataBlockID);
	len = Srvl_GetE2DataBlockLength(DataBlockID);

	if ((pData != NULL) && (len > 0))
	{
		memset(pData, 0xFF, len);
	}
}

/***********************************************************************************************
 * @function name:  Srvl_E2OPEndCallBack
 * @description:    ���� EEPROM ������ɺ�Ļص���ִ�и��ݲ������ͣ���/д����ͬ�ĺ�������
 * @input parameters:     eE2promOpType EEOpType - EEPROM �������ͣ���/д��
 *                       E2PROMOperateResult EEOpRes - EEPROM ����������ɹ�/ʧ�ܣ�
 * @output parameters:     void
 * @return:         void
 * @note:           ���ݲ������ͣ��������ɹ����������Ӧ�Ĵ������磬д�뱸�ݣ��ָ����ݵȣ���
 *                  �������ʧ�ܣ�������Ҫ���д�����
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2OPEndCallBack(eE2promOpType EEOpType, E2PROMOperateResult EEOpRes)
{
	INT16U CurUpID = 0;//��ǰ����ID
	INT16U BackUpID = D_NOBACKUP;//��ǰID�ı���ID
	static INT16U OriginalIndex = 0;

	CurUpID = E2PROMOpInfo.OpIndex;
	BackUpID = Srvl_GetE2DataBlockBackUpID(E2PROMOpInfo.OpIndex);
	E2PROMOpInfo.OpType = EEOpNULL;
	Srvl_SetE2DataBlockOptReq(CurUpID, EN_EEPROM_STA_IDLE);
	if(EEOpType == EEOpWR)
	{
		if(EEOpRes == E2PROM_OPOK)
		{
			//WR RIGHT
			Srvl_SetE2DataBlockOptResult(CurUpID, E2promOpOK);
			if(D_NOBACKUP != BackUpID)
			{
				//����б��ݾ�д����
				Srvl_WriteDataToBackUpID(CurUpID);
				Srvl_SetDataBlockWriteReq(BackUpID);
			}
		}
		else
		{
			//WR WRONG
			Srvl_SetE2DataBlockOptResult(CurUpID, E2promOpFail);
			E2PROMOpInfo.OpType = EEOpNULL;
		}
	}
	else if(EEOpType == EEOpRD)
	{
		if(EEOpRes == E2PROM_OPOK)
		{
			//READ RIGHT
			if(OriginalIndex != D_NOBACKUP)
			{
				Srvl_RestoreDataFromBackUpID(OriginalIndex);
				Srvl_SetE2DataBlockOptResult(OriginalIndex, E2promOpOK);
				OriginalIndex = D_NOBACKUP;
			}
			Srvl_SetE2DataBlockOptResult(CurUpID, E2promOpOK);
		}
		else if(D_NOBACKUP != BackUpID)
		{
			//����б��ݾ�ȥ������
			OriginalIndex = E2PROMOpInfo.OpIndex;
			Srvl_E2SetOpt(BackUpID, EEPROM_READ_START);
		}
		else
        {
			//��ȡ����� ��RAM������Ϊ0xFF
			if(OriginalIndex != D_NOBACKUP)
			{
				Srvl_SetE2DataBlockOptResult(OriginalIndex, E2promOpFail);
				Srvl_SetE2DataBlockToFF(OriginalIndex);
				OriginalIndex = D_NOBACKUP;
			}
            Srvl_SetE2DataBlockOptResult(CurUpID, E2promOpFail);
            Srvl_SetE2DataBlockToFF(CurUpID);
        }
	}
}


/***********************************************************************************************
 * @function name:  Srvl_E2SetOpt
 * @description:    ���� EEPROM ��������ز����������ݲ�������������/д������
 * @input parameters:     INT8U DataBlockId - Ҫ���������ݿ� ID
 *                       EEPROMOperateState eOpStep - �������裨���磬��������ʼ��д������ʼ�����еȣ�
 * @output parameters:     void
 * @return:         void
 * @note:           ���ݴ���Ĳ����������� EEPROM �����������Ϣ������������費�ǿ��У�����������
 *                  �ú��������ʼ��������Ϣ����������ִ�ж���������д������
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2SetOpt(INT8U DataBlockId, EEPROMOperateState eOpStep)//��/дE2PROM��Ӧ��Ŀ
{
	//��ȡ��/д��Ŀ���ڴ����ݵ�ַ
	E2PROMOpInfo.pData = Srvl_GetE2DataBlockBufferPtr(DataBlockId);
	if(NULL == E2PROMOpInfo.pData)
	{
		//��Ŀ���ڴ����ݵ�ַΪNULL�����в���
		Srvl_SetE2DataBlockOptReq(DataBlockId, EN_EEPROM_STA_IDLE);
		return;
	}

	//��ֵ���ײ��E2PROM�����������Ϣ
	E2PROMOpInfo.WritedDataNum = 0;
	E2PROMOpInfo.DataNum = Srvl_GetE2DataBlockLength(DataBlockId);
	E2PROMOpInfo.E2pDataAddress = Srvl_GetE2DataBlockStartAddr(DataBlockId);
	E2PROMOpInfo.OpIndex = DataBlockId;
	E2PROMOpInfo.OperateState = eOpStep;

	if(EEPROM_IDLE != eOpStep)
	{
		Srvl_SetE2DataBlockOptResult(DataBlockId, E2promOping);
	}

	if(EEPROM_READ_START != eOpStep)
	{
		E2PROMOpInfo.OpType = EEOpWR;//д����
	}
	else
	{
		E2PROMOpInfo.OpType = EEOpRD;//������
	}
}

/***********************************************************************************************
 * @function name:  Srvl_SetDataBlockWriteReq
 * @description:    �������ݿ�д�����󣬲��������ݿ�Ĳ���״̬�ͽ����
 * @input parameters:     INT16U DataBlockID - Ҫ����д����������ݿ� ID
 * @output parameters:     void
 * @return:         void
 * @note:           �ú������� `Srvl_SetE2DataBlockOptReq` �������ݿ��д�������󣬲����� `Srvl_SetE2DataBlockOptResult` ����д�����Ľ��״̬Ϊ�ȴ��С�
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_SetDataBlockWriteReq(INT16U DataBlockID)
{
	Srvl_SetE2DataBlockOptReq(DataBlockID, EN_EEPROM_STA_WRITE);
	Srvl_SetE2DataBlockOptResult(DataBlockID, E2promWaitIDL);
}
/***********************************************************************************************
 * @function name: Srvl_WriteMemIndexData
 * @description: ��ָ���ڴ�������Ӧ������д�� EEPROM ������������д������
 * @input parameters: MemIndex - ����������ptru8data - Դ����ָ�룻len - ���ݳ���
 * @output parameters: ��
 * @return: ��
 * @note: ֻ�е�������ԭֵ��һ��ʱ�Żᴥ��д�룬д�뷶Χ����Ϸ�
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
BOOL Srvl_WriteMemIndexData(enSrvMemIndex MemIndex, INT8U * ptru8data, INT8U len)
{
	BOOL Ret = FALSE;
	INT8U i = 0;
	INT8U DataLen = 0;
	INT8U StartOffset = 0;
	INT8U DataBlockID = 0;
	INT8U DataBlockLen = 0;
	INT8U *EepromParaPtr = NULL;
    enE2promOptResult OpResult = E2promNullOp;

	if(MemIndex < EN_MemIndex_Max)
	{
		DataBlockID = Srvl_GetE2DefineDataBlockID(MemIndex);
		StartOffset = Srvl_GetE2DefineStartOffset(MemIndex);
		DataLen = Srvl_GetE2DefineLen(MemIndex);
        OpResult = Srvl_GetE2DataBlockOptResult(DataBlockID); /*��ȡ�������eeprom ����״̬ */
		if(DataBlockID < Srvl_GetE2DataBlockCfgTableLength())
		{
			/*��ȡ�������ݿ�� bufferָ���볤��*/
			EepromParaPtr = Srvl_GetE2DataBlockBufferPtr(DataBlockID);
			DataBlockLen = Srvl_GetE2DataBlockLength(DataBlockID) - 1;//ʵ��ʹ�ó��ȿ��Ǽ�ȥУ���
		}
		if((EepromParaPtr == NULL) || (ptru8data == NULL)) /*Ŀ�����ݵ�ַ,Դ���ݵ�ַ�ǿ�*/
		{
		    return Ret;
		}
			/*���ݶ����ĳ��ȼ���ʼ��� �Ϸ����ж� && д�����ݳ�����ȷ */
		if(((StartOffset + DataLen) <= DataBlockLen)
		&& (DataLen == len))
		{
			/*�ж���д����������ȡeeprom�е����ݲ�һ�º��д��*/
			if(FALSE == Com_MemCmp(&EepromParaPtr[StartOffset], ptru8data, len))
			{
				for(i = 0; i < len; i++)
				{
					EepromParaPtr[StartOffset + i] = ptru8data[i];
				}
			    /* ����д�������õȴ�������д��-����д����������º�ֹ��
			       ���±����������������ʽ����û���� */
                if(OpResult == E2promOping) 
                {
                    Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,TRUE);//Ԥ�洢
                }
                else
                {
                    /*����д���������ݿ�*/
                    Srvl_SetDataBlockWriteReq(DataBlockID);
                    Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,FALSE);
                }
                Ret = TRUE;
			}
			else
			{
				//������ͬ��������
			}
		}
	}
	return Ret;
}

/***********************************************************************************************
 * @function name: Srvl_PreSaveMemDataFunc
 * @description: �ȴ�д��e2p���ݴ���
 * @input parameters: 
 * @output parameters: ��
 * @return: ��
 * @note: 
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_PreSaveMemDataFunc(void)
{
    enE2promOptResult OpResult = E2promNullOp;
    static INT8U DataBlockID = 0xFF;
    INT8U DataBlockIDMax = Srvl_GetE2DataBlockCfgTableLength();
    INT8U PreWriteFlg = FALSE;
    
    DataBlockID = (DataBlockID < DataBlockIDMax)?(DataBlockID += 1):(0);
    
    PreWriteFlg = Srvl_GetE2DataBlockPreWriteFlg(DataBlockID);
    
    if(PreWriteFlg == FALSE)//��Ԥ�洢
    {
        return;
    }
    OpResult = Srvl_GetE2DataBlockOptResult(DataBlockID); /*��ȡ�������eeprom ����״̬ */
    
    if(OpResult != E2promOping)
    {
        Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,FALSE);//Ԥ�洢
        Srvl_SetDataBlockWriteReq(DataBlockID);
    }
}

/***********************************************************************************************
 * @function name: Srvl_ReadMemIndexData
 * @description: �� EEPROM ��������ȡָ���ڴ�����������
 * @input parameters: MemIndex - ����������ptru8data - Ŀ������ָ�룻len - Ҫ��ȡ�����ݳ���
 * @output parameters: ��
 * @return: ��
 * @note: ��ȡ����ǰ��ȷ�����������ݳ����뻺������Ч
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_ReadMemIndexData(enSrvMemIndex MemIndex, INT8U* ptru8data, INT8U len)
{
	INT8U i = 0;
	INT8U DataLen = 0;
	INT8U StartOffset = 0;
	INT8U DataBlockID = 0;
	INT8U DataBlockLen = 0;
	INT8U *EepromParaPtr = NULL;

	if(MemIndex < EN_MemIndex_Max)
	{
		DataBlockID = Srvl_GetE2DefineDataBlockID(MemIndex);
		StartOffset = Srvl_GetE2DefineStartOffset(MemIndex);
		DataLen = Srvl_GetE2DefineLen(MemIndex);
		if(DataBlockID < Srvl_GetE2DataBlockCfgTableLength())
		{
			/*��ȡ�������ݿ�� bufferָ���볤��*/
			EepromParaPtr = Srvl_GetE2DataBlockBufferPtr(DataBlockID);
			DataBlockLen = Srvl_GetE2DataBlockLength(DataBlockID) - 1;//ʵ��ʹ�ó��ȿ��Ǽ�ȥУ���
		}
		if((EepromParaPtr != NULL) && (ptru8data != NULL)) /*Ŀ�����ݵ�ַ,Դ���ݵ�ַ�ǿ�*/
		{
			/*���ݶ����ĳ��ȼ���ʼ��� �Ϸ����ж� && д�����ݳ�����ȷ */
			if(((StartOffset + DataLen) <= DataBlockLen)
			&& (DataLen == len))
			{
				for(i = 0; i < len; i++)
				{
					ptru8data[i] = EepromParaPtr[StartOffset + i];
				}
			}
		}
	}
}

/***********************************************************************************************
 * @function name: Srvl_SetMemIndexDataU8
 * @description: ����ָ���ڴ������� 1 �ֽ����ݵ� EEPROM ������
 * @input parameters: MemIndex - ����������u8SourceData - Դ���ݣ�1 �ֽڣ�
 * @output parameters: ��
 * @return: ��
 * @note: ʵ�ʵ��� Srvl_WriteMemIndexData ����д��
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_SetMemIndexDataU8(enSrvMemIndex MemIndex, INT8U u8SourceData)
{
	Srvl_WriteMemIndexData(MemIndex, (INT8U* )&u8SourceData, 1);
}

/***********************************************************************************************
 * @function name: Srvl_GetMemIndexDataU8
 * @description: ��ȡָ���ڴ������� 1 �ֽ�����
 * @input parameters: MemIndex - ��������
 * @output parameters: ��
 * @return: INT8U - ���ض�ȡ���� 1 �ֽ�����
 * @note: ʵ�ʵ��� Srvl_ReadMemIndexData �� EEPROM ��������ȡ����
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
INT8U Srvl_GetMemIndexDataU8(enSrvMemIndex MemIndex)
{
	INT8U u8SourceData;

	Srvl_ReadMemIndexData(MemIndex, (INT8U* )&u8SourceData, 1);

	return u8SourceData;
}

/***********************************************************************************************
 * @function name: Srvl_SetMemIndexDataU16
 * @description: ����ָ���ڴ������� 2 �ֽ����ݵ� EEPROM ������
 * @input parameters: MemIndex - ����������u16SourceData - Դ���ݣ�2 �ֽڣ�
 * @output parameters: ��
 * @return: ��
 * @note: ʵ�ʵ��� Srvl_WriteMemIndexData ����д��
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_SetMemIndexDataU16(enSrvMemIndex MemIndex, INT16U u16SourceData)
{
	Srvl_WriteMemIndexData(MemIndex, (INT8U* )&u16SourceData, 2);
}
/***********************************************************************************************
 * @function name: Srvl_GetMemIndexDataU16
 * @description: ��ȡָ���ڴ������� 2 �ֽ�����
 * @input parameters: MemIndex - ��������
 * @output parameters: ��
 * @return: INT16U - ���ض�ȡ���� 2 �ֽ�����
 * @note: ʵ�ʵ��� Srvl_ReadMemIndexData �� EEPROM ��������ȡ����
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
INT16U Srvl_GetMemIndexDataU16(enSrvMemIndex MemIndex)
{
	INT16U u16SourceData;

	Srvl_ReadMemIndexData(MemIndex, (INT8U* )&u16SourceData, 2);

	return u16SourceData;
}
/***********************************************************************************************
 * @function name:  Srvl_E2OptTask
 * @description:    ִ�� E2PROM �������񣬸��ݵ�ǰ����״̬ѡ��ͬ�Ĳ������̣�������д�����Ŀ�ʼ���ɹ���ʧ�ܵ�״̬����
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           ���ݵ�ǰ�� `E2PROMOpInfo.OperateState` ״̬������ִ�ж�ȡ����д����������״̬���¡�����ͬ�Ĵ����ɹ�״̬��������ɺ���ûص����� `Srvl_E2OPEndCallBack`��
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2OptTask(void)
{
	switch(E2PROMOpInfo.OperateState)
	{
		case  EEPROM_IDLE :
			E2PROMOpInfo.E2promOpErrorTime	= 0x00;
			break;
		case  EEPROM_READ_START :
			Srvl_E2ReadTask();
			break;
		case  EEPROM_READ_ERROR :
			E2PROMOpInfo.E2promOpErrorTime++;
			if(E2PROMOpInfo.E2promOpErrorTime < EEPROMOPERATEERRORMAXTIME)
			{
				E2PROMOpInfo.OperateState = EEPROM_READ_START;
			}
			else
			{
				E2PROMOpInfo.OperateState = EEPROM_IDLE;
				E2PROMOpInfo.OperateResult = E2PROM_READNG;
				Srvl_E2OPEndCallBack(E2PROMOpInfo.OpType, E2PROMOpInfo.OperateResult);
			}
			break;
		case  EEPROM_READ_SUCCESS :
			E2PROMOpInfo.OperateState = EEPROM_IDLE;
			E2PROMOpInfo.OperateResult = E2PROM_OPOK;
			Srvl_SetE2DataBlockOptResult(E2PROMOpInfo.OpIndex, E2promOpOK);
			break;
		case  EEPROM_VERIFY_SUCCESS :
			E2PROMOpInfo.OperateState = EEPROM_IDLE;
			E2PROMOpInfo.OperateResult = E2PROM_OPOK;
			Srvl_E2OPEndCallBack(E2PROMOpInfo.OpType, E2PROMOpInfo.OperateResult);
			break;
		case  EEPROM_WRITE_ERROR :
			E2PROMOpInfo.OperateState = EEPROM_IDLE;
			E2PROMOpInfo.OperateResult = E2PROM_WRITENG;
			Srvl_E2OPEndCallBack(E2PROMOpInfo.OpType, E2PROMOpInfo.OperateResult);
			break;
		case  EEPROM_WRITE_START :
			Srvl_E2WriteTask();
			break;

		case EEPROM_WRITE_WAIT_FOR_10MS:
			break;

		default :
			break;
	}
}
