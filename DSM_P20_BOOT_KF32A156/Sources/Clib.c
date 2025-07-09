#include   "Clib.h"


/*************************************************************
* 函数名称：RamSet
* 功能描述：数组重置函数
* 入口参数：buff:数组首地址 data:重置数值 len:数组长度
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void    RamSet(INT8U *buff, INT8U data, INT8U len)
{
	INT8U Index;

	for(Index = 0x00; Index < len; Index++, buff++)
	{
		*buff = data;
	}
}

/*************************************************************
* 函数名称：CalcCheckSum
* 功能描述：计算CheckSum函数
* 入口参数：Buff:数组首地址 len:数组长度
* 出口参数：
* 返 回 值：CheckSum值
* 备    注:
*************************************************************/
INT8U     CalcCheckSum(INT8U *Buff, INT8U len)
{
	INT8U Index, temp = 0;

	for(Index = 0x00; Index < len; Index++, Buff++)
	{
		temp += *Buff;
	}
	return (temp);
}

/*************************************************************
* 函数名称：MemCopy
* 功能描述：数组拷贝
* 入口参数：TrgBuff:目标数组首地址 SrcBuff:源数组首地址 len:数组长度
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void    MemCopy(INT8U *TrgBuff, INT8U *SrcBuff, INT8U Len)
{
	INT8U  Index;
	for(Index = 0x00; Index < Len; Index++)
	{
		*TrgBuff = *SrcBuff;
		TrgBuff++;
		SrcBuff++;
	}
}

/*************************************************************
* 函数名称：MemCopyINT32U
* 功能描述：32位数组拷贝
* 入口参数：TrgBuff:目标数组首地址 SrcBuff:源数组首地址 len:数组长度
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void    MemCopyINT32U(INT32U *TrgBuff, INT32U *SrcBuff, INT8U Len)
{
	INT8U  Index;
	for(Index = 0x00; Index < Len; Index++)
	{
		*TrgBuff = *SrcBuff;
		TrgBuff++;
		SrcBuff++;
	}
}


/*************************************************************
* 函数名称：MemCmp
* 功能描述：数组比较
* 入口参数：TrgBuff:目标数组首地址 SrcBuff:源数组首地址 len:数组长度
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
BOOL   MemCmp(INT8U *TrgBuff, INT8U *SrcBuff, INT8U Len)
{
	INT8U     Index;
	BOOL   ret = TRUE;

	for(Index = 0x00; Index < Len; Index++)
	{
		if(TrgBuff[Index] != SrcBuff[Index])
		{
			ret = FALSE;
			break;
		}
	}
	return ret;
}

/*************************************************************
* 函数名称：INT8UToINT32U
* 功能描述：8位转32位函数
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void    INT8UToINT32U(INT32U *OutBuff, INT8U *InBuff, INT8U Len)
{
	INT8U Index;
	for(Index = 0x00; Index < Len; Index += 4)
	{
		OutBuff[Index >> 2] = (INT32U)InBuff[Index] << 24;
		OutBuff[Index >> 2] += (INT32U)InBuff[Index + 1] << 16;
		OutBuff[Index >> 2] += (INT32U)InBuff[Index + 2] << 8;
		OutBuff[Index >> 2] += (INT32U)InBuff[Index + 3] << 0;
	}
}


/*************************************************************
* 函数名称：INT32UToINT8U
* 功能描述：32位转8位函数
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注:
*************************************************************/
void    INT32UToINT8U(INT8U *OutBuff, INT32U *InBuff, INT8U Len)
{
	INT8U Index, Index0 = 0;
	for(Index = 0x00; Index < Len; Index++)
	{
		OutBuff[Index0++] = (INT8U)(InBuff[Index] >> 24);
		OutBuff[Index0++] = (INT8U)(InBuff[Index] >> 16);
		OutBuff[Index0++] = (INT8U)(InBuff[Index] >> 8);
		OutBuff[Index0++] = (INT8U)(InBuff[Index] >> 0);
	}
}

/*************************************************************
* 函数名称：IsSameAsData
* 功能描述：判断数组中的值是否与预定值一致
* 入口参数：
* 出口参数：
* 返 回 值：
* 备    注: 
*************************************************************/
BOOL IsSameAsData(INT8U *Buff, INT8U Data, INT8U Len)
{
    INT8U     Index;
    BOOL ret = TRUE;
    for(Index = 0x00; Index < Len; Index++)
    {
        if(Buff[Index] != Data)
        {
            ret = FALSE;
            break;
        }
    }
    return ret;
}

