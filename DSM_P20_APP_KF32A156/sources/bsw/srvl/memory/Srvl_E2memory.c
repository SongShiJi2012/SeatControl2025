/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               AppE2prom.c
** Last modified Date:      2014.03.04
** Last Version:            V1.0
** Description:             EEPROM应用层
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven 莫松文
** Created date:            2014.03.04
** Version:                 V1.0
** Descriptions:            The original version 初始版本
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/
#include "Srvl_E2memory.h"
#include "Srvl_E2cfg.h"
#include "DescRWDIDList.h"
#include "Cdd_Hall.h"
#include "ecual_wdog.h"
#include "Srvl_E2Cfg_Generation.h"
#include "Appl_DtcSetConditionCheck.h"
#include "Srvl_Eeprom.h"
#include "Ecual_Adc.h"

stDescCheckE2promResult DescCheckE2promResult;
stAPPEEOP_INFO AppE2promOpInfo;
stCarE2promInfo AppCarE2promInfo;
static INT8U RstToFactModeFlg = 0;

INT8U E2promInitAppBufDefine[D_APP_INIT_Data_Len_4] = {0x5A, 0xA5, 0xAA, DSM_CURRECT_PROJECT};
static INT16U E2WritePollingIndex;//写轮询序号-使用ID数组的下标
static enSrvMemIndex s_enMemIndex = EN_MemIndex_Max;

const enSrvMemIndex E2WriteVerifyIndexList[enCheckE2Idx_Number] =
{
	EN_MemIndex_AppJumpToBootFlg, /* 升级跳转标志 */
};
/***********************************************************************************************
 * @function name: AppSysOpInfo_GetRstToFactModeFlg
 * @description: 获取恢复出厂模式标志状态
 * @input parameters: 无
 * @output parameters: 无
 * @return: 恢复出厂模式标志值（0或1）
 * @author: ssj 20250509
 ***********************************************************************************************/
INT8U Srvl_GetRstToFactModeFlg(void)
{
    return RstToFactModeFlg;
}
/***********************************************************************************************
 * @function name: AppSysOpInfo_SetRstToFactModeFlg
 * @description: 设置恢复出厂模式标志状态
 * @input parameters: flag：需要设置的标志值（0或1）
 * @output parameters: 无
 * @return: 无
 * @author: ssj 20250509
 ***********************************************************************************************/
void Srvl_SetRstToFactModeFlg(INT8U flag)
{
    RstToFactModeFlg = flag;
}


/********************************************************************
* 函数名称：Srvl_E2IsIndexDTCWriting
* 功能描述：判断DTC是否在被写的过程中
* 入口参数：
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
BOOL Srvl_E2IsIndexDTCWriting(void)
{
	BOOL ret=FALSE;
	stAPPEEOP_INFO *pAPPEEOP = &AppE2promOpInfo;

	if(pAPPEEOP->OpIndex == DTC_INDEX)
	{
		ret = TRUE;
	}

	return ret;
}


/***********************************************************************************************
 * @function name:  Srvl_E2SeatMemoryPosiInit
 * @description:       记忆位置初始化
 * @input parameters:  void
 * @output parameters: void
 * @return:            void
 * @note:
 * @author:
 * @note:              2023-10-31
 ***********************************************************************************************/
void Srvl_E2SeatMemoryPosiInit(void)
{

}

/********************************************************************
* 函数名称：Srvl_E2AllDataInit
* 功能描述：EEPROM数据初始化
* 入口参数：eFactMode ：EEPROM要初始化的模式
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Srvl_E2AllDataInit(void)
{
	INT8U temp[32] = /*0000000000000000*/
	{
		'0','0','0','0','0','0','0','0','0','0',
		'0','0','0','0','0','0','0','0','0','0',
		'0','0','0','0','0','0','0','0','0','0',
		'0','0'
	};
	INT8U i = 0x0U;
	
	const INT8U E2promAppCodeValidFlgDefine[D_E2promAppCodeValidFlg_Len] = {0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A, 0xA5, 0x5A}; // CS = FC

	Srvl_WriteMemIndexData(EN_MemIndex_APP_ValidFlg, (INT8U * )E2promAppCodeValidFlgDefine, D_APP_ValidFlg_Len_8);

	Srvl_WriteMemIndexData(EN_MemIndex_UdsDidVinCode, temp, D_UdsDidVinCode_Len_17);
	Srvl_SetMemIndexDataU8(EN_MemIndex_AppUdsSecurityAccessTimes, 0x00);

	//控制器功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrAdjustConfig, 2); 	//主驾座椅调节配置,默认：0x02:Twelve way motor
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaAdjustConfig, TRUE); //副驾座椅调节配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig, TRUE);		//主驾通风加热配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrMemoryConfig, FALSE);	//主驾记忆迎宾配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig, TRUE); //副驾通风加热配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaMemoryConfig, FALSE);		//副驾记忆迎宾配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_MassageConfig, TRUE);	//按摩功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrHeatFlg, TRUE);	//主驾加热功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaHeatFlg, TRUE);	//副驾加热功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentFlg, TRUE);	//主驾通风功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentFlg, TRUE);	//副驾通风功能配置
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte0, 0);	//功能配置预留0
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte1, 0);	//功能配置预留1
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte2, 0);	//功能配置预留2
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte3, 0);	//功能配置预留3
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte4, 0);	//功能配置预留4

	//系统功能配置
	INT8U u8SystemConfigPram[D_SystemFunctionConfiguration_F1FA_Len_6] = {0xF4, 0xFB, 0xF8, 0x7F, 0x38, 0x01};
	Srvl_WriteMemIndexData(EN_MemIndex_SystemFunctionConfiguration_F1FA, u8SystemConfigPram, D_SystemFunctionConfiguration_F1FA_Len_6);
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg, 0); 		//加热P20PHEV发动机使能配置禁能by Prima Niu 20250606

	Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Height,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Length,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Back,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Front,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Height,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Length,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Back,30000);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Front,30000);

	Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Length,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Height,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Length,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Back,0);
	Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Front,0);
	/*P20&BM400通用加热/通风配置默认为存在by Prima Niu 20250605*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RemoteEnableConfig,TRUE);/*默认有远程*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatFormVehicleEnableConfig,TRUE);/*默认有整车运行*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig,TRUE);/*默认有整车运行*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_TimeOutPrm,0);/*默认无超时配置*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RunMaxTime,20);/*默认超时时长20min*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_TimeOutPrm,0);/*默认无超时配置*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_RunMaxTime,20);/*默认超时时长20min*/
	for(i = EN_MemIndex_DrHeatConfig; i < EN_MemIndex_ThirdVentConfig; i ++)
	{
		Srvl_SetMemIndexDataU8(i,TRUE);
	}
	Srvl_SetMemIndexDataU8(EN_MemIndex_ThirdVentConfig,FALSE);/*P20默认无三排通风*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_CarType,0);/*车型信息，默认P20*/
	/*清零位置存储信息by Prima Niu 20250604*/
	for(i = EN_MemIndex_DrMem1_Height; i < EN_MemIndex_PaCurHallCnt_Height; i ++)
	{
		if((i == EN_MemIndex_DrMem1_ValidFlag) || (i == EN_MemIndex_DrMem2_ValidFlag) || (i == EN_MemIndex_DrMem3_ValidFlag))
		{
			Srvl_SetMemIndexDataU8(i,0);
		}
		else
		{
			Srvl_SetMemIndexDataU16(i,0);
		}
	}
	for(i = EN_MemIndex_PaMem1_Height; i < EN_MemIndex_DrAdjustConfig; i ++)
	{
		if((i == EN_MemIndex_PaMem1_ValidFlag) || (i == EN_MemIndex_PaMem2_ValidFlag) || (i == EN_MemIndex_PaMem3_ValidFlag))
		{
			Srvl_SetMemIndexDataU8(i,0);
		}
		else
		{
			Srvl_SetMemIndexDataU16(i,0);
		}
	}
	//默认不发送测试报文
	Srvl_SetMemIndexDataU8(EN_MemIndex_TestMessageSendCfg, 0);
	//全部写入
	Srvl_E2WriteAllTask();
	Srvl_SetRstToFactModeFlg(FALSE);
}

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
//	Srvl_E2OptInit();
    Srvl_Eeprom_init();
}
/********************************************************************
* 函数名称：Srvl_E2PowerOnInit
* 功能描述：EEPROM应用层数据初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Srvl_E2PowerOnInit(void)
{
	INT8U i;
	INT8U ReadBuf[D_APP_INIT_Data_Len_4];

	for (i = 0; i < enCheckE2Idx_Number; i++)
	{
		DescCheckE2promResult.CheckReadE2promFlg[i] = FALSE;
	    DescCheckE2promResult.CheckWriteE2promFlg[i] = FALSE;
	    DescCheckE2promResult.ReadE2promTimeoutCnt[i] = D_ReadE2promTimeout_Time;
	    DescCheckE2promResult.WriteE2promTimeoutCnt[i] = D_WriteE2promTimeout_Time;
	    DescCheckE2promResult.ReadE2promRespProcess[i] = NULL;
	    DescCheckE2promResult.WriteE2promRespProcess[i] = NULL;
	}

	Srvl_E2ReadAllTask();

	Srvl_ReadMemIndexData(EN_MemIndex_APP_INIT_Data, ReadBuf, D_APP_INIT_Data_Len_4);
	for(i = 0; i < D_APP_INIT_Data_Len_4; i++)
	{
		if(ReadBuf[i] != E2promInitAppBufDefine[i])
		{
			Srvl_WriteMemIndexData(EN_MemIndex_APP_INIT_Data, E2promInitAppBufDefine, D_APP_INIT_Data_Len_4);
			Diag_ClearAllDtc();
			Srvl_E2AllDataInit();
			break;
		}
	}

}
/*********************************************************************
* 函数名称：Srvl_E2SetWriteFlg
* 功能描述：设置要写EE2PROM的项目
* 入口参数：eE2promIndex:要写EE2PROM的项目
* 出口参数：无
* 返 回 值：无
* 备    注: 无
*********************************************************************/
void Srvl_E2SetWriteFlg(enE2promIndex  eE2promIndex)
{
}


/********************************************************************
* 函数名称：Srvl_E2FlagUpdateTask
* 功能描述：EEPROM标志位更新任务
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void Srvl_E2FlagUpdateTask(void)
{
}

/*******************************************************************************
* 函数名称：Srvl_E2SetCheckWriteResultFlg
* 功能描述：设置检测E2prom写数据结果标识
* 入口参数：CheckE2Idx: 需要检测的E2prom项
* 出口参数：无
* 返 回 值：无
* 备    注: 无
*******************************************************************************/
void    Srvl_E2SetCheckWriteResultFlg(enCheckE2Idx  CheckE2Idx)
{
    if(CheckE2Idx < enCheckE2Idx_Number)
    {
        DescCheckE2promResult.CheckWriteE2promFlg[CheckE2Idx] = TRUE;
    }
}
/***********************************************************************************************
 * @function name: static void Srvl_ResetE2CheckStatus
 * @description: 重置 EEPROM 写入检查标志与超时计数器
 * @input parameters: enCheckE2Idx idx —— 检查的 EEPROM 索引
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
static void Srvl_ResetE2CheckStatus(enCheckE2Idx idx)
{
    DescCheckE2promResult.CheckWriteE2promFlg[idx] = FALSE;
    DescCheckE2promResult.WriteE2promTimeoutCnt[idx] = D_WriteE2promTimeout_Time;
}
/***********************************************************************************************
 * @function name: Srvl_E2CheckWriteResultAndResp
 * @description: 检测E2prom写入结果并响应诊断（周期：20ms）
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2CheckWriteResultAndResp(void)
{
    enCheckE2Idx CheckE2Idx = enCheckFromAppJumpToBootFlg_Idx; // 校验索引
    BOOL IsCheck = FALSE;                                      // 是否需要校验
    INT16U TimeoutCnt = 0;                                     // 超时计数
    pDescRespProcess RespFunc = NULL;                          // 响应函数指针
    INT16U BlockId = 0;                                        // EEPROM 数据块 ID
    enE2promOptResult WriteResult;                             // 写入结果

    for(CheckE2Idx = enCheckFromAppJumpToBootFlg_Idx; CheckE2Idx < enCheckE2Idx_Number; CheckE2Idx++)
    {
        IsCheck = (TRUE == DescCheckE2promResult.CheckWriteE2promFlg[CheckE2Idx]);
        TimeoutCnt = DescCheckE2promResult.WriteE2promTimeoutCnt[CheckE2Idx];
        RespFunc = DescCheckE2promResult.WriteE2promRespProcess[CheckE2Idx];
        BlockId = Srvl_GetE2DefineDataBlockID(E2WriteVerifyIndexList[CheckE2Idx]);

        if (TRUE != IsCheck)
        {
            DescCheckE2promResult.WriteE2promTimeoutCnt[CheckE2Idx] = D_WriteE2promTimeout_Time;
            continue;
        }

        if (TimeoutCnt > 0)
        {
            DescCheckE2promResult.WriteE2promTimeoutCnt[CheckE2Idx]--;
            WriteResult = Srvl_GetE2DataBlockOptResult(BlockId);

            if ((WriteResult == E2promOpOK) || (WriteResult == E2promOpFail))
            {
            	Srvl_ResetE2CheckStatus(CheckE2Idx);
                if (NULL != RespFunc)
                {
                    RespFunc(WriteResult);
                }
            }
        }
        else
        {
        	Srvl_ResetE2CheckStatus(CheckE2Idx);
            if (NULL != RespFunc)
            {
                RespFunc(E2promOpFail);
            }
        }
    }
}


/***********************************************************************
 * @function name: Srvl_getSystemConfigPram
 *
 * @description: 获取系统功能配置任一bit数据
 *
 * @input parameters: index ：配置字在数据中的bit位
 *
 * @output parameters: 无
 *
 * @return: res ：index 对应bit的值-0/1
 *
 * @note: 无
 *
 * @author: zjx
 *
 * @date: 2024-04-11 14:43
 ***********************************************************************/
INT8U Srvl_getSystemConfigPram(en_System_Config_Index index)
{
	INT8U res = 0;
	INT8U cDataBuf[D_SystemFunctionConfiguration_F1FA_Len_6] ={0};

	Srvl_ReadMemIndexData(EN_MemIndex_SystemFunctionConfiguration_F1FA, cDataBuf, D_SystemFunctionConfiguration_F1FA_Len_6);

	res = (cDataBuf[index / 8] & (1 << (index % 8) )) >> (index % 8);

	return res;
}
/*!
************************************************************************************************************************
* 接口原型 INT8U * Srv_GetMemDiagDTCIndex(INT16U u16Index)
* @brief
* @param[in]
* @param[out]
* @returns
* @pre
* @note 获取 存储的DTC状态信息
* @author
* @date
************************************************************************************************************************
*/
BOOL Srvl_IsMemDiagDTCIndex(enSrvMemIndex MemIndex)
{
	BOOL ret = FALSE;

	if((MemIndex < EN_MemIndex_Dtc_IndexMax) && (MemIndex >= EN_MemIndex_Dtc_Index0))
	{
		ret = TRUE;
	}

	return ret;
}
/***********************************************************************************************
 * @function name: Srvl_SetDTCStatusMask
 * @description: 设置指定 DTC 项的状态掩码数据（写入 EEPROM）基本信息:状态位,检测次数,老化次数
 * @input parameters: INT8U u8DtcIndex DTC 索引号；INT8U *u8Buff 指向3字节状态掩码缓冲区
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
BOOL Srvl_SetDTCStatusMask(DiagDtcNameType_t u8DtcIndex, INT8U *u8Buff)
{
	enSrvMemIndex t_enMemIndex = u8DtcIndex + EN_MemIndex_Dtc_Index0;

	if(t_enMemIndex <= EN_MemIndex_Dtc_IndexMax)
	{
		if(TRUE == Srvl_WriteMemIndexData(t_enMemIndex, u8Buff, 3))
		{
			s_enMemIndex = t_enMemIndex;
			return TRUE;
		}
	}
	return FALSE;
}
/***********************************************************************************************
 * @function name:  Srvl_getClearDTCIndex(void)
 * @description:	获取最后一个写的DTC的索引
 * @input parameters:     void
 * @output parameters:     void
 * @return:         无
 * @note:           无
 * @author:          zjx
 * @note:           2023-06-14
 ***********************************************************************************************/
enSrvMemIndex Srvl_getClearDTCIndex(void)
{
	return s_enMemIndex;
}
/***********************************************************************************************
 * @function name: Srvl_GetDTCStatusMask
 * @description: 获取指定 DTC 项的状态掩码数据（从 EEPROM 中读取）基本信息:状态位,检测次数,老化次数
 * @input parameters: INT8U u8DtcIndex DTC 索引号；INT8U *u8Buff 用于存放读取到的3字节数据
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
BOOL Srvl_GetDTCStatusMask(DiagDtcNameType_t u8DtcIndex, INT8U *u8Buff)
{
	enSrvMemIndex t_enMemIndex = u8DtcIndex + EN_MemIndex_Dtc_Index0;

	if(t_enMemIndex <= EN_MemIndex_Dtc_IndexMax)
	{
		Srvl_ReadMemIndexData(t_enMemIndex, u8Buff, 3);
		return TRUE;
	}
	return FALSE;
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

	for(i = 0; i < D_USEID_NUMBER_NO_BACKUP; i++)
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
/***********************************************************************************************
 * @function name: Srvl_E2SetE2WritePollingIndex
 * @description: 设置E2写轮询索引，加快Srvl_E2WritePolling中对目标数据块的定位
 * @input parameters: enSrvMemIndex eE2promIndex
 * @output parameters: None
 * @return: void
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex)
{
    INT8U i;

    /* 此函数的意义是加快Srvl_E2WritePolling()中对要写条目的索引 */
    for(i = 0; i < D_USEID_NUMBER; i++)
    {
        if(Srvl_GetUseDataBlockID(i) == Srvl_GetUseDataBlockID(eE2promIndex))
        {
            E2WritePollingIndex = i;
            break;
        }
    }
}
/***********************************************************************************************
 * @function name: Srvl_E2WritePolling
 * @description: EEPROM写入轮询任务，检测写请求并启动写操作 5ms
 * @input parameters: None
 * @output parameters: None
 * @return: void
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2WritePolling(void)
{
	INT8U i;                          // 轮询计数变量
	INT8U index;                      // 当前计算得到的轮询索引
	INT16U DataBlockId = 0;           // 当前数据块ID
	BOOL IsWriteReq = 0;             // 是否有写请求标志

	if(TRUE == IsE2promIDLE())
	{
		for(i = 0; i < D_USEID_NUMBER; i++)
		{
			index = (E2WritePollingIndex + i) % D_USEID_NUMBER;
			DataBlockId = Srvl_GetUseDataBlockID(index);
			IsWriteReq = (EN_EEPROM_STA_WRITE == Srvl_GetE2DataBlockEepOptReq(DataBlockId));

			if(TRUE == IsWriteReq)
			{
				Srvl_E2SetOpt(DataBlockId, EEPROM_WRITE_START);
				E2WritePollingIndex = (index + 1) % D_USEID_NUMBER;
				break;
			}
		}
	}

	Srvl_E2OptTask();
    Srvl_PreSaveMemDataFunc();
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
/***********************************************************************************************
 * @function name:  Srvl_E2WritePollingIfReady
 * @description:    E2写入轮询接口，仅在所有霍尔停止采集和所有ADC DMA更新完成后执行
 *                  通过内部定时器累计达到条件后调用 Srvl_E2WritePolling()
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Srvl_E2WritePollingIfReady(void)
{
    static INT8U e2WritePollingTimer  = 0;

    e2WritePollingTimer ++;

    if((e2WritePollingTimer  >= 2)//调度周期 20ms
    && (Cdd_IsHallAllStop() == TRUE)
    && (Ecual_AreAllAdcDmaUpdated() == TRUE))
    {
        Srvl_E2WritePolling();
        e2WritePollingTimer  = 0;
    }
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


