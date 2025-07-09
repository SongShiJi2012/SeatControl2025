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
static INT16U E2WritePollingIndex;//写轮询序号
/********************************************************************
* 函数名称：Srvl_E2Init
* 功能描述：EEPROM应用层数据初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Srvl_E2Init(void)
{
	Srvl_E2OptInit();
}
/***********************************************************************************************
 * @function name:  Srvl_E2ReadAllTask
 * @description:	全部读取 - 阻塞
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
	for(i = 0; i < D_USEID_NUMBER_NO_BACKUP; i++)//这里只需要读取BOOT所需要的ID
	{
		DataBlockId = Srvl_GetUseDataBlockIDNoBackUp(i);
		Srvl_E2SetOpt(DataBlockId, EEPROM_READ_START);
		while(IsE2promBusy())//IsE2promBusy 目前有E2PROM的操作
		{
			Srvl_E2OptTask();
		}
	}
}
/***********************************************************************************************
 * @function name:  Srvl_E2WriteAllTask
 * @description:	全部写完 - 阻塞
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
* 函数名称：AppAppE2promSetCheckWriteResultFlg
* 功能描述：设置检测E2prom写数据结果标识
* 入口参数：CheckE2Idx: 需要检测的E2prom项
* 出口参数：无
* 返 回 值：无
* 备    注: 无
*******************************************************************************/
void AppAppE2promSetCheckWriteResultFlg(INT8U  E2promIndex)
{
    if(E2promIndex < D_READ_NUMBER)
    {
        DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex] = TRUE;
    }
}
/*******************************************************************************
* 函数名称：AppAppE2promSetCheckReadResultFlg
* 功能描述：设置检测E2prom读取数据结果标识
* 入口参数：CheckE2Idx: 需要检测的E2prom项
* 出口参数：无
* 返 回 值：无
* 备    注: 无
*******************************************************************************/
void AppAppE2promSetCheckReadResultFlg(INT8U  E2promIndex)
{
    if(E2promIndex < D_READ_NUMBER)
    {
        DescCheckE2promResult.CheckReadE2promFlg[E2promIndex] = TRUE;
    }
}

/*******************************************************************************
* 函数名称：AppAppE2promCheckWiteAndReadResultAndResp
* 功能描述：检测E2prom读写结果,并响应诊断
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: Period is 5ms
*******************************************************************************/
void AppAppE2promCheckReadAndWiteResultAndResp(void)
{
	INT8U  E2promIndex = 0;

    // 读E2prom Check
    for(E2promIndex = 0; E2promIndex < D_READ_NUMBER; E2promIndex ++)
    {
    	ecual_FeedDog();
        if(TRUE == DescCheckE2promResult.CheckReadE2promFlg[E2promIndex]) // 检查E2prom写标识
        {
            if(DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex]) // 读E2prom 还没超时
            {
                DescCheckE2promResult.ReadE2promTimeoutCnt[E2promIndex] --;
                if(IsAppE2promReadEnd(E2promIndex)) // 读E2prom结束
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


    // 写E2prom Check
    for(E2promIndex = 0; E2promIndex < D_READ_NUMBER; E2promIndex ++)
    {
    	ecual_FeedDog();
        if(TRUE == DescCheckE2promResult.CheckWriteE2promFlg[E2promIndex]) // 检查E2prom写标识
        {
            if(DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex]) // 写E2prom 还没超时
            {
                DescCheckE2promResult.WriteE2promTimeoutCnt[E2promIndex] --;
                if(IsAppE2promWriteEnd(E2promIndex)) // 写E2prom结束
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
* 函数名称：AppE2promInit
* 功能描述：EEPROM应用层数据初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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
			//第一次上电 写入BOOT初始化和app有效标志
			Srvl_WriteMemIndexData(EN_MemIndex_BOOT_INIT_Data, (INT8U * )E2promInitBootBufDefine, D_APP_INIT_Data_Len_4);
			Srvl_WriteMemIndexData(EN_MemIndex_APP_ValidFlg, (INT8U * )E2promAppCodeValidFlgDefine, D_APP_ValidFlg_Len_8);
			Srvl_WriteMemIndexData(EN_MemIndex_CustomerBootVersion, (INT8U * )BootloaderSoftwareVersionNumber, D_CustomerBootVersion_Len_15);
			Srvl_WriteMemIndexData(EN_MemIndex_DareBootVersion, (INT8U * )DareBootSoftwareVersionNumber, D_DareBootVersion_Len_8);
			AppAppE2promSetCheckWriteResultFlg(EN_MemIndex_APP_ValidFlg);

			RamSet(tempBuf, 0x00, D_FingerPrint_ProgramDate_F199_Len_4);
			Srvl_WriteMemIndexData(EN_MemIndex_FingerPrint_ProgramDate_F199, tempBuf, D_FingerPrint_ProgramDate_F199_Len_4);
		    /*清除从APP跳转到BOOT的标识*/
			Srvl_SetMemIndexDataU8(EN_MemIndex_AppJumpToBootFlg, FALSE);
			break;
		}
	}
	BootVersionWrite();

	Srvl_E2WriteAllTask();
}
/*********************************************************************
* 函数名称：Srvl_E2SetE2WritePollingIndex
* 功能描述：设置要操作EE2PROM的项目
* 入口参数：eE2promIndex:要操作EE2PROM的项目
* 出口参数：无
* 返 回 值：无
* 备    注: 无Srvl_E2SetOpIndex(MEMORY_INDEX)
*********************************************************************/
void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex)
{
	INT8U i;

	/*此函数的意义是加快Srvl_E2WritePolling()中对要写条目的索引  */
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
* 函数名称：Srvl_E2WritePolling
* 功能描述： EEPROM写任务轮询 5ms
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Srvl_E2WritePolling(void)
{
	INT8U i;
	INT16U DataBlockId = 0;

	if(IsE2promIDLE())
	{
		for(i = 0; i < D_USEID_NUMBER; i++)
		{
			/* 轮询使用的是否有写请求 Req 设置 */
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
* 函数名称：Srvl_E2ReadPolling
* 功能描述：EEPROM读任务 - 上电已经全部读出 后续无需调用20250321ssj
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
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


