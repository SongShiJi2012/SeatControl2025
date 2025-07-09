#include   "Clib.h"


/*************************************************************
* �������ƣ�RamSet
* �����������������ú���
* ��ڲ�����buff:�����׵�ַ data:������ֵ len:���鳤��
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�CalcCheckSum
* ��������������CheckSum����
* ��ڲ�����Buff:�����׵�ַ len:���鳤��
* ���ڲ�����
* �� �� ֵ��CheckSumֵ
* ��    ע:
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
* �������ƣ�MemCopy
* �������������鿽��
* ��ڲ�����TrgBuff:Ŀ�������׵�ַ SrcBuff:Դ�����׵�ַ len:���鳤��
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�MemCopyINT32U
* ����������32λ���鿽��
* ��ڲ�����TrgBuff:Ŀ�������׵�ַ SrcBuff:Դ�����׵�ַ len:���鳤��
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�MemCmp
* ��������������Ƚ�
* ��ڲ�����TrgBuff:Ŀ�������׵�ַ SrcBuff:Դ�����׵�ַ len:���鳤��
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�INT8UToINT32U
* ����������8λת32λ����
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�INT32UToINT8U
* ����������32λת8λ����
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע:
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
* �������ƣ�IsSameAsData
* �����������ж������е�ֵ�Ƿ���Ԥ��ֵһ��
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 
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

