/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               AppE2prom.c
** Last modified Date:      2014.03.04
** Last Version:            V1.0
** Description:             EEPROMӦ�ò�
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven Ī����
** Created date:            2014.03.04
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
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
static INT16U E2WritePollingIndex;//д��ѯ���-ʹ��ID������±�
static enSrvMemIndex s_enMemIndex = EN_MemIndex_Max;

const enSrvMemIndex E2WriteVerifyIndexList[enCheckE2Idx_Number] =
{
	EN_MemIndex_AppJumpToBootFlg, /* ������ת��־ */
};
/***********************************************************************************************
 * @function name: AppSysOpInfo_GetRstToFactModeFlg
 * @description: ��ȡ�ָ�����ģʽ��־״̬
 * @input parameters: ��
 * @output parameters: ��
 * @return: �ָ�����ģʽ��־ֵ��0��1��
 * @author: ssj 20250509
 ***********************************************************************************************/
INT8U Srvl_GetRstToFactModeFlg(void)
{
    return RstToFactModeFlg;
}
/***********************************************************************************************
 * @function name: AppSysOpInfo_SetRstToFactModeFlg
 * @description: ���ûָ�����ģʽ��־״̬
 * @input parameters: flag����Ҫ���õı�־ֵ��0��1��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 20250509
 ***********************************************************************************************/
void Srvl_SetRstToFactModeFlg(INT8U flag)
{
    RstToFactModeFlg = flag;
}


/********************************************************************
* �������ƣ�Srvl_E2IsIndexDTCWriting
* �����������ж�DTC�Ƿ��ڱ�д�Ĺ�����
* ��ڲ�����
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
 * @description:       ����λ�ó�ʼ��
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
* �������ƣ�Srvl_E2AllDataInit
* ����������EEPROM���ݳ�ʼ��
* ��ڲ�����eFactMode ��EEPROMҪ��ʼ����ģʽ
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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

	//��������������
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrAdjustConfig, 2); 	//�������ε�������,Ĭ�ϣ�0x02:Twelve way motor
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaAdjustConfig, TRUE); //�������ε�������
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig, TRUE);		//����ͨ���������
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrMemoryConfig, FALSE);	//���ݼ���ӭ������
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig, TRUE); //����ͨ���������
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaMemoryConfig, FALSE);		//���ݼ���ӭ������
	Srvl_SetMemIndexDataU8(EN_MemIndex_MassageConfig, TRUE);	//��Ħ��������
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrHeatFlg, TRUE);	//���ݼ��ȹ�������
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaHeatFlg, TRUE);	//���ݼ��ȹ�������
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentFlg, TRUE);	//����ͨ�繦������
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentFlg, TRUE);	//����ͨ�繦������
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte0, 0);	//��������Ԥ��0
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte1, 0);	//��������Ԥ��1
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte2, 0);	//��������Ԥ��2
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte3, 0);	//��������Ԥ��3
	Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte4, 0);	//��������Ԥ��4

	//ϵͳ��������
	INT8U u8SystemConfigPram[D_SystemFunctionConfiguration_F1FA_Len_6] = {0xF4, 0xFB, 0xF8, 0x7F, 0x38, 0x01};
	Srvl_WriteMemIndexData(EN_MemIndex_SystemFunctionConfiguration_F1FA, u8SystemConfigPram, D_SystemFunctionConfiguration_F1FA_Len_6);
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg, 0); 		//����P20PHEV������ʹ�����ý���by Prima Niu 20250606

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
	/*P20&BM400ͨ�ü���/ͨ������Ĭ��Ϊ����by Prima Niu 20250605*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RemoteEnableConfig,TRUE);/*Ĭ����Զ��*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatFormVehicleEnableConfig,TRUE);/*Ĭ������������*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig,TRUE);/*Ĭ������������*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_TimeOutPrm,0);/*Ĭ���޳�ʱ����*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RunMaxTime,20);/*Ĭ�ϳ�ʱʱ��20min*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_TimeOutPrm,0);/*Ĭ���޳�ʱ����*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_RunMaxTime,20);/*Ĭ�ϳ�ʱʱ��20min*/
	for(i = EN_MemIndex_DrHeatConfig; i < EN_MemIndex_ThirdVentConfig; i ++)
	{
		Srvl_SetMemIndexDataU8(i,TRUE);
	}
	Srvl_SetMemIndexDataU8(EN_MemIndex_ThirdVentConfig,FALSE);/*P20Ĭ��������ͨ��*/
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_CarType,0);/*������Ϣ��Ĭ��P20*/
	/*����λ�ô洢��Ϣby Prima Niu 20250604*/
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
	//Ĭ�ϲ����Ͳ��Ա���
	Srvl_SetMemIndexDataU8(EN_MemIndex_TestMessageSendCfg, 0);
	//ȫ��д��
	Srvl_E2WriteAllTask();
	Srvl_SetRstToFactModeFlg(FALSE);
}

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
//	Srvl_E2OptInit();
    Srvl_Eeprom_init();
}
/********************************************************************
* �������ƣ�Srvl_E2PowerOnInit
* ����������EEPROMӦ�ò����ݳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
* �������ƣ�Srvl_E2SetWriteFlg
* ��������������ҪдEE2PROM����Ŀ
* ��ڲ�����eE2promIndex:ҪдEE2PROM����Ŀ
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
*********************************************************************/
void Srvl_E2SetWriteFlg(enE2promIndex  eE2promIndex)
{
}


/********************************************************************
* �������ƣ�Srvl_E2FlagUpdateTask
* ����������EEPROM��־λ��������
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Srvl_E2FlagUpdateTask(void)
{
}

/*******************************************************************************
* �������ƣ�Srvl_E2SetCheckWriteResultFlg
* �������������ü��E2promд���ݽ����ʶ
* ��ڲ�����CheckE2Idx: ��Ҫ����E2prom��
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
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
 * @description: ���� EEPROM д�����־�볬ʱ������
 * @input parameters: enCheckE2Idx idx ���� ���� EEPROM ����
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
static void Srvl_ResetE2CheckStatus(enCheckE2Idx idx)
{
    DescCheckE2promResult.CheckWriteE2promFlg[idx] = FALSE;
    DescCheckE2promResult.WriteE2promTimeoutCnt[idx] = D_WriteE2promTimeout_Time;
}
/***********************************************************************************************
 * @function name: Srvl_E2CheckWriteResultAndResp
 * @description: ���E2promд��������Ӧ��ϣ����ڣ�20ms��
 * @input parameters: ��
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2CheckWriteResultAndResp(void)
{
    enCheckE2Idx CheckE2Idx = enCheckFromAppJumpToBootFlg_Idx; // У������
    BOOL IsCheck = FALSE;                                      // �Ƿ���ҪУ��
    INT16U TimeoutCnt = 0;                                     // ��ʱ����
    pDescRespProcess RespFunc = NULL;                          // ��Ӧ����ָ��
    INT16U BlockId = 0;                                        // EEPROM ���ݿ� ID
    enE2promOptResult WriteResult;                             // д����

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
 * @description: ��ȡϵͳ����������һbit����
 *
 * @input parameters: index ���������������е�bitλ
 *
 * @output parameters: ��
 *
 * @return: res ��index ��Ӧbit��ֵ-0/1
 *
 * @note: ��
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
* �ӿ�ԭ�� INT8U * Srv_GetMemDiagDTCIndex(INT16U u16Index)
* @brief
* @param[in]
* @param[out]
* @returns
* @pre
* @note ��ȡ �洢��DTC״̬��Ϣ
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
 * @description: ����ָ�� DTC ���״̬�������ݣ�д�� EEPROM��������Ϣ:״̬λ,������,�ϻ�����
 * @input parameters: INT8U u8DtcIndex DTC �����ţ�INT8U *u8Buff ָ��3�ֽ�״̬���뻺����
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
 * @description:	��ȡ���һ��д��DTC������
 * @input parameters:     void
 * @output parameters:     void
 * @return:         ��
 * @note:           ��
 * @author:          zjx
 * @note:           2023-06-14
 ***********************************************************************************************/
enSrvMemIndex Srvl_getClearDTCIndex(void)
{
	return s_enMemIndex;
}
/***********************************************************************************************
 * @function name: Srvl_GetDTCStatusMask
 * @description: ��ȡָ�� DTC ���״̬�������ݣ��� EEPROM �ж�ȡ��������Ϣ:״̬λ,������,�ϻ�����
 * @input parameters: INT8U u8DtcIndex DTC �����ţ�INT8U *u8Buff ���ڴ�Ŷ�ȡ����3�ֽ�����
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

	for(i = 0; i < D_USEID_NUMBER_NO_BACKUP; i++)
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
/***********************************************************************************************
 * @function name: Srvl_E2SetE2WritePollingIndex
 * @description: ����E2д��ѯ�������ӿ�Srvl_E2WritePolling�ж�Ŀ�����ݿ�Ķ�λ
 * @input parameters: enSrvMemIndex eE2promIndex
 * @output parameters: None
 * @return: void
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2SetE2WritePollingIndex(enSrvMemIndex eE2promIndex)
{
    INT8U i;

    /* �˺����������Ǽӿ�Srvl_E2WritePolling()�ж�Ҫд��Ŀ������ */
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
 * @description: EEPROMд����ѯ���񣬼��д��������д���� 5ms
 * @input parameters: None
 * @output parameters: None
 * @return: void
 * @author: ssj 2025-05-14
 ***********************************************************************************************/
void Srvl_E2WritePolling(void)
{
	INT8U i;                          // ��ѯ��������
	INT8U index;                      // ��ǰ����õ�����ѯ����
	INT16U DataBlockId = 0;           // ��ǰ���ݿ�ID
	BOOL IsWriteReq = 0;             // �Ƿ���д�����־

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
/***********************************************************************************************
 * @function name:  Srvl_E2WritePollingIfReady
 * @description:    E2д����ѯ�ӿڣ��������л���ֹͣ�ɼ�������ADC DMA������ɺ�ִ��
 *                  ͨ���ڲ���ʱ���ۼƴﵽ��������� Srvl_E2WritePolling()
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/
void Srvl_E2WritePollingIfReady(void)
{
    static INT8U e2WritePollingTimer  = 0;

    e2WritePollingTimer ++;

    if((e2WritePollingTimer  >= 2)//�������� 20ms
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


