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
    .EERAMBase = EEPROM_ADDRESS,   /* E2PROM起始地址 芯旺微使用外部E2 型号： */
    .EEESize = EEPROM_SIZE,	/* AT24C16 容量 2KB  */
};

EEPROMInfoStructType E2PROMOpInfo;
static INT8U gu8EepromWriteBuffer[EEPROMBUFFMAXNUM];
static INT8U gu8EepromReadBuffer[EEPROMBUFFMAXNUM];
static void Srvl_SetDataBlockWriteReq(INT16U DataBlockID);

/***********************************************************************************************
 * @function name:  Srvl_E2OptInit
 * @description:    EEPROM操作状态初始化
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
 * @description:    比较 EEPROM 中指定地址的数据与给定数据缓冲区的数据是否相同
 * @input parameters:
 *     INT32U lu32Dest      // 目标地址（绝对地址）
 *     INT32U lu32Size      // 比较的数据长度（单位：字节）
 *     const INT8U* lpu8DataBuf   // 待比较的数据缓冲区指针
 * @output parameters:     void
 * @return:         返回比较结果：D_Ok 表示数据匹配，D_ParaErr 表示地址参数错误，D_DataErr 表示数据不匹配
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
		/* 读一个字节 */
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
 * @description:    从 EEPROM 中读取指定地址和长度的数据到缓冲区
 * @input parameters:
 *     INT32U lu32Dest      // 目标读取地址（绝对地址）
 *     INT32U lu32Size      // 读取的数据长度（单位：字节）
 *     INT8U *lpu8ReadBuf   // 数据读取输出缓冲区指针
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2Read(INT32U lu32Dest, INT32U lu32Size, INT8U *lpu8ReadBuf)
{
	/* 如果读取的数据长度为0或者超出串行Flash地址空间，则直接返回 */
	if((lu32Size == 0) || ((lu32Dest + lu32Size - e2Config.EERAMBase) > e2Config.EEESize))
	{
		return;
	}
	//ecual_I2C_read(EEPROM_I2C,lu32Dest - e2Config.EERAMBase,lpu8ReadBuf,lu32Size);
	Srvl_Eeprom_Read(lu32Dest - e2Config.EERAMBase, lu32Size, (INT32U *)lpu8ReadBuf);
}

/***********************************************************************************************
 * @function name:  Srvl_E2Write
 * @description:    向 EEPROM 中指定地址写入数据，并进行写入后的数据校验，若校验不通过，最多重写 3 次
 * @input parameters:
 *     INT32U lu32Dest      // 目标地址（绝对地址）
 *     INT32U lu32Size      // 写入的数据长度（单位：字节）
 *     const INT8U* lpu8DataBuf   // 待写入的数据缓冲区指针
 * @output parameters:     void
 * @return:         返回写入结果：D_Success 表示成功，D_ParaErr 表示参数错误，D_E2_WriteWait 表示等待重试，D_Failure 表示写入失败
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

	/* 写完之后进行校验，如果不正确则重写，最多3次 */
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
			//重写
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
 * @description:    读取 EEPROM 中的数据，并进行校验。若校验通过，将数据存储到指定缓冲区。
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           该函数会根据操作状态读取数据并进行校验，若校验通过，则将数据保存到指定位置，否则设置为读取错误状态。
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2ReadTask(void)
{
	INT16U  Index;
	INT8U  CheckSum;
    INT8U ResultSts = 0;

	if((E2PROMOpInfo.DataNum) < EEPROMBUFFMAXNUM)
	{
		//Srvl_E2Read(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, gu8EepromReadBuffer); /*获取数据+校验和*/
        ResultSts = Srvl_Eeprom_Read(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, (INT32U *)gu8EepromReadBuffer);
        if(ResultSts != STATUS_SUCCESS)
        {
            memset(gu8EepromReadBuffer,0xFF,E2PROMOpInfo.DataNum); // 读失败清缓存。
            E2PROMOpInfo.OperateState = EEPROM_READ_ERROR;
            return;
        }

		for(Index = 0x00, CheckSum = 0x00; Index < E2PROMOpInfo.DataNum - 1; Index++)
		{
			CheckSum += gu8EepromReadBuffer[Index];
		}

		if(CheckSum == gu8EepromReadBuffer[E2PROMOpInfo.DataNum - 1]) /*满足累加和后,赋值数据*/
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
 * @description:    写入数据到 EEPROM，并计算校验和进行验证。若写入成功，更新操作状态；若失败，设置为写入错误状态。
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           该函数会将数据和校验和写入 EEPROM，并根据写入结果更新操作状态。
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2WriteTask(void)
{
	INT16U	  Index;
	status_t len_Ret = STATUS_ERROR;

	if((E2PROMOpInfo.DataNum) < EEPROMBUFFMAXNUM)
	{
		/*取值,计算累加和*/
		E2PROMOpInfo.WriteCheckSum = 0;
		for(Index = 0; Index < E2PROMOpInfo.DataNum - 1; Index ++)
		{
			gu8EepromWriteBuffer[Index] = *((INT8U *)(E2PROMOpInfo.pData + Index));
			E2PROMOpInfo.WriteCheckSum += gu8EepromWriteBuffer[Index];
		}
		gu8EepromWriteBuffer[E2PROMOpInfo.DataNum - 1] = E2PROMOpInfo.WriteCheckSum;

		len_Ret = Srvl_E2Write(E2PROMOpInfo.E2pDataAddress, E2PROMOpInfo.DataNum, gu8EepromWriteBuffer); /*数据+校验和*/
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
 * @description:    从备份ID恢复数据，并将备份数据拷贝到目标数据块中。
 * @input parameters:     INT16U DataBlockId - 数据块ID
 * @output parameters:     void
 * @return:         void
 * @note:           该函数会根据数据块ID检查备份ID，若存在备份数据，则将备份数据恢复到目标数据块。
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
 * @description:    将数据块ID中的数据写入到备份ID对应的数据块中。
 * @input parameters:     INT16U DataBlockId - 数据块ID
 * @output parameters:     void
 * @return:         void
 * @note:           该函数会根据数据块ID获取备份ID，如果存在备份ID，则将目标数据块中的数据写入到备份数据块。
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
 * @description:    根据数据块ID，将对应的数据块RAM区域填充为0xFF
 * @input parameters:     INT16U DataBlockID：E2数据块ID
 * @output parameters:     void
 * @return:         void
 * @note:           通过ID获取数据块RAM地址和长度，并填充为0xFF
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
 * @description:    处理 EEPROM 操作完成后的回调，执行根据操作类型（读/写）不同的后续处理。
 * @input parameters:     eE2promOpType EEOpType - EEPROM 操作类型（读/写）
 *                       E2PROMOperateResult EEOpRes - EEPROM 操作结果（成功/失败）
 * @output parameters:     void
 * @return:         void
 * @note:           根据操作类型，若操作成功，则进行相应的处理（例如，写入备份，恢复数据等）。
 *                  如果操作失败，根据需要进行错误处理。
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_E2OPEndCallBack(eE2promOpType EEOpType, E2PROMOperateResult EEOpRes)
{
	INT16U CurUpID = 0;//当前操作ID
	INT16U BackUpID = D_NOBACKUP;//当前ID的备份ID
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
				//如果有备份就写备份
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
			//如果有备份就去读备份
			OriginalIndex = E2PROMOpInfo.OpIndex;
			Srvl_E2SetOpt(BackUpID, EEPROM_READ_START);
		}
		else
        {
			//读取错误后 把RAM变量设为0xFF
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
 * @description:    设置 EEPROM 操作的相关参数，并根据操作类型启动读/写操作。
 * @input parameters:     INT8U DataBlockId - 要操作的数据块 ID
 *                       EEPROMOperateState eOpStep - 操作步骤（例如，读操作开始、写操作开始、空闲等）
 * @output parameters:     void
 * @return:         void
 * @note:           根据传入的操作步骤设置 EEPROM 操作的相关信息。如果操作步骤不是空闲，启动操作。
 *                  该函数负责初始化操作信息，并决定是执行读操作还是写操作。
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
void Srvl_E2SetOpt(INT8U DataBlockId, EEPROMOperateState eOpStep)//读/写E2PROM对应项目
{
	//获取读/写项目的内存数据地址
	E2PROMOpInfo.pData = Srvl_GetE2DataBlockBufferPtr(DataBlockId);
	if(NULL == E2PROMOpInfo.pData)
	{
		//项目的内存数据地址为NULL不进行操作
		Srvl_SetE2DataBlockOptReq(DataBlockId, EN_EEPROM_STA_IDLE);
		return;
	}

	//赋值给底层的E2PROM变量的相关信息
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
		E2PROMOpInfo.OpType = EEOpWR;//写操作
	}
	else
	{
		E2PROMOpInfo.OpType = EEOpRD;//读操作
	}
}

/***********************************************************************************************
 * @function name:  Srvl_SetDataBlockWriteReq
 * @description:    设置数据块写入请求，并更新数据块的操作状态和结果。
 * @input parameters:     INT16U DataBlockID - 要进行写入操作的数据块 ID
 * @output parameters:     void
 * @return:         void
 * @note:           该函数调用 `Srvl_SetE2DataBlockOptReq` 设置数据块的写操作请求，并调用 `Srvl_SetE2DataBlockOptResult` 更新写操作的结果状态为等待中。
 * @author:         ssj 2025-05-13
 ***********************************************************************************************/
static void Srvl_SetDataBlockWriteReq(INT16U DataBlockID)
{
	Srvl_SetE2DataBlockOptReq(DataBlockID, EN_EEPROM_STA_WRITE);
	Srvl_SetE2DataBlockOptResult(DataBlockID, E2promWaitIDL);
}
/***********************************************************************************************
 * @function name: Srvl_WriteMemIndexData
 * @description: 将指定内存索引对应的数据写入 EEPROM 缓冲区并触发写入请求
 * @input parameters: MemIndex - 数据索引；ptru8data - 源数据指针；len - 数据长度
 * @output parameters: 无
 * @return: 无
 * @note: 只有当数据与原值不一致时才会触发写入，写入范围必须合法
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
        OpResult = Srvl_GetE2DataBlockOptResult(DataBlockID); /*获取数据项的eeprom 操作状态 */
		if(DataBlockID < Srvl_GetE2DataBlockCfgTableLength())
		{
			/*获取所在数据块的 buffer指针与长度*/
			EepromParaPtr = Srvl_GetE2DataBlockBufferPtr(DataBlockID);
			DataBlockLen = Srvl_GetE2DataBlockLength(DataBlockID) - 1;//实际使用长度考虑减去校验和
		}
		if((EepromParaPtr == NULL) || (ptru8data == NULL)) /*目标数据地址,源数据地址非空*/
		{
		    return Ret;
		}
			/*数据定义表的长度及起始标号 合法性判断 && 写入数据长度正确 */
		if(((StartOffset + DataLen) <= DataBlockLen)
		&& (DataLen == len))
		{
			/*判断需写入的数据与读取eeprom中的数据不一致后才写入*/
			if(FALSE == Com_MemCmp(&EepromParaPtr[StartOffset], ptru8data, len))
			{
				for(i = 0; i < len; i++)
				{
					EepromParaPtr[StartOffset + i] = ptru8data[i];
				}
			    /* 正在写入则设置等待空闲在写入-避免写入过程中重新何止，
			       导致备份区域更新区域。正式区域没更新 */
                if(OpResult == E2promOping) 
                {
                    Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,TRUE);//预存储
                }
                else
                {
                    /*触发写入整个数据块*/
                    Srvl_SetDataBlockWriteReq(DataBlockID);
                    Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,FALSE);
                }
                Ret = TRUE;
			}
			else
			{
				//数据相同不做处理
			}
		}
	}
	return Ret;
}

/***********************************************************************************************
 * @function name: Srvl_PreSaveMemDataFunc
 * @description: 等待写入e2p数据处理
 * @input parameters: 
 * @output parameters: 无
 * @return: 无
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
    
    if(PreWriteFlg == FALSE)//无预存储
    {
        return;
    }
    OpResult = Srvl_GetE2DataBlockOptResult(DataBlockID); /*获取数据项的eeprom 操作状态 */
    
    if(OpResult != E2promOping)
    {
        Srvl_SetE2DataBlockPreWriteFlg(DataBlockID,FALSE);//预存储
        Srvl_SetDataBlockWriteReq(DataBlockID);
    }
}

/***********************************************************************************************
 * @function name: Srvl_ReadMemIndexData
 * @description: 从 EEPROM 缓冲区读取指定内存索引的数据
 * @input parameters: MemIndex - 数据索引；ptru8data - 目标数据指针；len - 要读取的数据长度
 * @output parameters: 无
 * @return: 无
 * @note: 读取数据前需确保索引、数据长度与缓冲区有效
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
			/*获取所在数据块的 buffer指针与长度*/
			EepromParaPtr = Srvl_GetE2DataBlockBufferPtr(DataBlockID);
			DataBlockLen = Srvl_GetE2DataBlockLength(DataBlockID) - 1;//实际使用长度考虑减去校验和
		}
		if((EepromParaPtr != NULL) && (ptru8data != NULL)) /*目标数据地址,源数据地址非空*/
		{
			/*数据定义表的长度及起始标号 合法性判断 && 写入数据长度正确 */
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
 * @description: 设置指定内存索引的 1 字节数据到 EEPROM 缓冲区
 * @input parameters: MemIndex - 数据索引；u8SourceData - 源数据（1 字节）
 * @output parameters: 无
 * @return: 无
 * @note: 实际调用 Srvl_WriteMemIndexData 进行写入
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_SetMemIndexDataU8(enSrvMemIndex MemIndex, INT8U u8SourceData)
{
	Srvl_WriteMemIndexData(MemIndex, (INT8U* )&u8SourceData, 1);
}

/***********************************************************************************************
 * @function name: Srvl_GetMemIndexDataU8
 * @description: 获取指定内存索引的 1 字节数据
 * @input parameters: MemIndex - 数据索引
 * @output parameters: 无
 * @return: INT8U - 返回读取到的 1 字节数据
 * @note: 实际调用 Srvl_ReadMemIndexData 从 EEPROM 缓冲区读取数据
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
 * @description: 设置指定内存索引的 2 字节数据到 EEPROM 缓冲区
 * @input parameters: MemIndex - 数据索引；u16SourceData - 源数据（2 字节）
 * @output parameters: 无
 * @return: 无
 * @note: 实际调用 Srvl_WriteMemIndexData 进行写入
 * @author: ssj 2025-04-23
 ***********************************************************************************************/
void Srvl_SetMemIndexDataU16(enSrvMemIndex MemIndex, INT16U u16SourceData)
{
	Srvl_WriteMemIndexData(MemIndex, (INT8U* )&u16SourceData, 2);
}
/***********************************************************************************************
 * @function name: Srvl_GetMemIndexDataU16
 * @description: 获取指定内存索引的 2 字节数据
 * @input parameters: MemIndex - 数据索引
 * @output parameters: 无
 * @return: INT16U - 返回读取到的 2 字节数据
 * @note: 实际调用 Srvl_ReadMemIndexData 从 EEPROM 缓冲区读取数据
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
 * @description:    执行 E2PROM 操作任务，根据当前操作状态选择不同的操作流程，包括读写操作的开始、成功、失败等状态处理。
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @note:           根据当前的 `E2PROMOpInfo.OperateState` 状态，决定执行读取任务、写入任务或操作状态更新。处理不同的错误或成功状态，并在完成后调用回调函数 `Srvl_E2OPEndCallBack`。
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
