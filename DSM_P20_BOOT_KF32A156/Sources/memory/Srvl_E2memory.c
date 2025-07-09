/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
********************************************************************************************/

#include "Srvl_E2memory.h"
#include "Srvl_E2cfg.h"
#include "ecual_wdog.h"
#include "Srvl_E2Cfg_Generation.h"
#include "Prog.h"
#include   "Clib.h"

stDescCheckE2promResult DescCheckE2promResult;
INT8U E2promInitAppBufDefine[E2PROM_INIT_APP_LEN] = {0x5A, 0xA5, 0xAA, DSM_CURRECT_PROJECT};
static INT16U E2WritePollingIndex;//д��ѯ���
/********************************************************************
* �������ƣ�Srvl_E2Init
* ����������EEPROMӦ�ò����ݳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Srvl_E2Init(void)
{
	Srvl_E2OptInit();
}
/***********************************************************************************************
 * @function name:  Srvl_E2ReadAllTask
 * @description:	ȫ����ȡ - ����
 * @input parameters:
 * @output parameters:
 * @return:
 * @note:
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
void Srvl_E2ReadAllTask(void)
{
	INT8U i;
	INT16U DataBlockId = 0;

//	for(i = 0; i < D_USEID_NUMBER; i++)
	for(i = 0; i < D_USEID_NUMBER_NO_BACKUP; i++)//����ֻ��Ҫ��ȡBOOT����Ҫ��ID
	{
		DataBlockId = Srvl_GetUseDataBlockIDNoBackUp(i);
		Srvl_E2SetOpt(DataBlockId, EEPROM_READ_START);
		while(IsE2promBusy())//IsE2promBusy Ŀǰ��E2PROM�Ĳ���
		{
			Srvl_E2OptTask();
		}
	}
}
/***********************************************************************************************
 * @function name:  Srvl_E2WriteAllTask
 * @description:	ȫ��д�� - ����
 * @input parameters:
 * @output parameters:
 * @return:
 * @note:
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
void Srvl_E2WriteAllTask(void)
{
	INT8U i;
	INT16U DataBlockId = 0;

	for(i = 0; i < D_USEID_NUMBER; i++)
	{
		DataBlockId = Srvl_GetUseDataBlockID(i);
		if(Srvl_GetE2DataBlockEepOptReq(DataBlockId) == EN_EEPROM_STA_WRITE)
		{
			Srvl_E2SetOpt(DataBlockId, EEPROM_WRITE_START);
			while(IsE2promBusy())
			{
				Srvl_E2OptTask();
			}
			ecual_FeedDog();
		}
	}
}
void BootVersionWrite(void)
{
	INT8U i;
}

/*******************************************************************************
* �������ƣ�AppAppE2promSetCheckWriteResultFlg
* �������������ü��E2promд���ݽ����ʶ
* ��ڲ�����CheckE2Idx: ��Ҫ����E2prom��
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
void AppAppE2promSetCheckWriteResultFlg(INT8U  E2promIndex)
{
    if(E2promIndex < D_READ_NUMBER)
    {
        DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex] = TRUE;
    }
}
/*******************************************************************************
* �������ƣ�AppAppE2promSetCheckReadResultFlg
* �������������ü��E2prom��ȡ���ݽ����ʶ
* ��ڲ�����CheckE2Idx: ��Ҫ����E2prom��
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
void AppAppE2promSetCheckReadResultFlg(INT8U  E2promIndex)
{
    if(E2promIndex < D_READ_NUMBER)
    {
        DescCheckE2promResult.CheckReadE2promFlg[E2promIndex] = TRUE;
    }
}

/*******************************************************************************
* �������ƣ�AppAppE2promCheckWiteAndReadResultAndResp
* �������������E2prom��д���,����Ӧ���
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: Period is 5ms
*******************************************************************************/
void AppAppE2promCheckReadAndWiteResultAndResp(void)
{
	INT8U  E2promIndex = 0;

    // ��E2prom Check
    for(E2promIndex = 0; E2promIndex < D_READ_NUMBER; E2promIndex ++)
    {
    	ecual_FeedDog();
        if(TRUE == DescCheckE2promResult.CheckReadE2promFlg[E2promIndex]) // ���E2promд��ʶ
        {
            if(DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex]) // ��E2prom ��û��ʱ
            {
                DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex] --;
                if(IsAppE2promReadEnd(E2promIndex)) // ��E2prom����
                {
                    DescCheckE2promResult.CheckReadE2promFlg[E2promIndex] = FALSE;
                    DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex] = D_ReadE2promTimeout_Time;

                    if(NULL != DescCheckE2promResult.ReadE2promRespProcess[E2promIndex])
                    {
                        DescCheckE2promResult.ReadE2promRespProcess[E2promIndex]();
                    }
                }
            }
            else
            {
                DescCheckE2promResult.CheckReadE2promFlg[E2promIndex] = FALSE;
                DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex] = D_ReadE2promTimeout_Time;

				if(NULL != DescCheckE2promResult.ReadE2promRespProcess[E2promIndex])
				{
					DescCheckE2promResult.ReadE2promRespProcess[E2promIndex]();
				}
            }
        }
        else
        {
            DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex] = D_ReadE2promTimeout_Time;
        }
    }


    // дE2prom Check
    for(E2promIndex = 0; E2promIndex < D_READ_NUMBER; E2promIndex ++)
    {
    	ecual_FeedDog();
        if(TRUE == DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex]) // ���E2promд��ʶ
        {
            if(DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex]) // дE2prom ��û��ʱ
            {
                DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex] --;
                if(IsAppE2promWriteEnd(E2promIndex)) // дE2prom����
                {
                    DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex] = FALSE;
                    DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex] = D_WriteE2promTimeout_Time;

                    if(NULL != DescCheckE2promResult.WriteE2promRespProcess[E2promIndex])
                    {
                        DescCheckE2promResult.WriteE2promRespProcess[E2promIndex]();
                    }
                }
            }
            else
            {
                DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex] = FALSE;
                DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex] = D_WriteE2promTimeout_Time;

                if(NULL != DescCheckE2promResult.WriteE2promRespProcess[E2promIndex])
                {
                    DescCheckE2promResult.WriteE2promRespProcess[E2promIndex]();
                }
            }
        }
        else
        {
            DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex] = D_WriteE2promTimeout_Time;
        }
    }

}

/********************************************************************
* �������ƣ�AppE2promInit
* ����������EEPROMӦ�ò����ݳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Srvl_E2PowerOnInit(void)
{
	INT8U i;
	INT8U tempBuf[32];

	for( i = 0; i < D_READ_NUMBER; i++)
	{
		DescCheckE2promResult.CheckReadE2promFlg[i] = FALSE;
	    DescCheckE2promResult.CheckWriteE2promFlg[i] = FALSE;
	    DescCheckE2promResult.ReadE2promTimeoutCnt[i] = D_ReadE2promTimeout_Time;
	    DescCheckE2promResult.WriteE2promTimeoutCnt[i] = D_WriteE2promTimeout_Time;
	    DescCheckE2promResult.ReadE2promRespProcess[i] = NULL;
	    DescCheckE2promResult.WriteE2promRespProcess[i] = NULL;
	}

	Srvl_E2ReadAllTask();

	Srvl_ReadMemIndexData(EN_MemIndex_BOOT_INIT_Data, tempBuf, D_APP_INIT_Data_Len_4);
	for(i = 0; i < D_APP_INIT_Data_Len_4; i++)
	{
		if(tempBuf[i] != E2promInitBootBufDefine[i])
		{
			//��һ���ϵ� д��BOOT��ʼ����app��Ч��־
			Srvl_WriteMemIndexData(EN_MemIndex_BOOT_INIT_Data, (INT8U * )E2promInitBootBufDefine, D_APP_INIT_Data_Len_4);
			Srvl_WriteMemIndexData(EN_MemIndex_APP_ValidFlg, (INT8U * )E2promAppCodeValidFlgDefine, D_APP_ValidFlg_Len_8);
			Srvl_WriteMemIndexData(EN_MemIndex_CustomerBootVersion, (INT8U * )BootloaderSoftwareVersionNumber, D_CustomerBootVersion_Len_15);
			Srvl_WriteMemIndexData(EN_MemIndex_DareBootVersion, (INT8U * )DareBootSoftwareVersionNumber, D_DareBootVersion_Len_8);
			AppAppE2promSetCheckWriteResultFlg(EN_MemIndex_APP_ValidFlg);

			RamSet(tempBuf, 0x00, D_FingerPrint_ProgramDate_F199_Len_4);
			Srvl_WriteMemIndexData(EN_MemIndex_FingerPrint_ProgramDate_F199, tempBuf, D_FingerPrint_ProgramDate_F199_Len_4);
		    /*�����APP��ת��BOOT�ı�ʶ*/
			Srvl_SetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg, FALSE);
			break;
		}
	}
	BootVersionWrite();

	Srvl_E2WriteAllTask();
}
/*********************************************************************
* �������ƣ�Srvl_E2SetE2WritePollingIndex
* ��������������Ҫ����EE2PROM����Ŀ
* ��ڲ�����eE2promIndex:Ҫ����EE2PROM����Ŀ
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��Srvl_E2SetOpIndex(MEMORY_INDEX)
*********************************************************************/
void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex)
{
	INT8U i;

	/*�˺����������Ǽӿ�Srvl_E2WritePolling()�ж�Ҫд��Ŀ������  */
	for(i = 0; i < D_USEID_NUMBER; i++)
	{
		if(Srvl_GetUseDataBlockID(i) == Srvl_GetUseDataBlockID(eE2promIndex))
		{
			E2WritePollingIndex = eE2promIndex;
			break;
		}
	}
}
/********************************************************************
* �������ƣ�Srvl_E2WritePolling
* ���������� EEPROMд������ѯ 5ms
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Srvl_E2WritePolling(void)
{
	INT8U i;
	INT16U DataBlockId = 0;

	if(IsE2promIDLE())
	{
		for(i = 0; i < D_USEID_NUMBER; i++)
		{
			/* ��ѯʹ�õ��Ƿ���д���� Req ���� */
			if(E2WritePollingIndex >= D_USEID_NUMBER)
			{
				E2WritePollingIndex = 0;
			}
			DataBlockId = Srvl_GetUseDataBlockID(E2WritePollingIndex);
			if(Srvl_GetE2DataBlockEepOptReq(DataBlockId) == EN_EEPROM_STA_WRITE)
			{
				Srvl_E2SetOpt(DataBlockId, EEPROM_WRITE_START);
				E2WritePollingIndex ++;
				break;
			}
			E2WritePollingIndex ++;
		}
	}

	Srvl_E2OptTask();
}
/********************************************************************
* �������ƣ�Srvl_E2ReadPolling
* ����������EEPROM������ - �ϵ��Ѿ�ȫ������ �����������20250321ssj
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Srvl_E2ReadPolling(void)
{
	INT8U i;
	INT16U DataBlockId = 0;

	if(IsE2promBusy())
	{
		return;
	}
	for(i = 0; i < D_USEID_NUMBER; i++)
	{
		DataBlockId = Srvl_GetUseDataBlockID(i);
		if(Srvl_GetE2DataBlockEepOptReq(DataBlockId) == EN_EEPROM_STA_READ)
		{
			Srvl_E2SetOpt(DataBlockId, EEPROM_READ_START);
			break;
		}
	}
}



/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


