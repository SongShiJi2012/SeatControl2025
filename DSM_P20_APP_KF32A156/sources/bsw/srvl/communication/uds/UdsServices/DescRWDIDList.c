/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescRWDIDList.c
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             读写DID列表源文件
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven 莫松文
** Created date:            2013.10.19
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

#define         RWDID_GLOBALS

#include "Desc.h"
#include "Ecual_Adc.h"
#include "Appl_PowerMangeModel.h"
#include "Srvl_E2Operate.h"

#define     __DIDNOTSUPPORTWRITE           0,Desc_enmSecExtLvl,NULL
#define		__DIDNOTSUPPORTREAD			   0,FALSE,NULL

INT8U gPINCodeMatchFlg;	//PIN验证状态标志
INT8U g_u8PINCodeAuthFailCnt;	//PIN验证失败次数记录

const INT8U cFZB_SW_Version_Number[16];


#if (SID22_READDID_EN == DESC_ENABLE) ||(SID2E_WRITEDID_EN == DESC_ENABLE)

static volatile INT16U gRWDIDIndex;
extern const tDESC_DID_INFO pRWDIDInfoTbl[];
static INT8U s_ConfigChangeFlag[2] = {FALSE};/*配置变化标志位*/
static INT32U s_DiagSwHeatTimer = 0x0U;


const INT8U  cFZBHardwareNumber[16] =
{
	"PCB-18013-00-03 "
};

const INT8U cPartNumber[21] = {'2','8','5','P','5','2','H','H','0','B'};/*F187 PartNumberAlphaCode/零部件号*/
const INT8U  cSystemSupplierIdentifier[7] = {'X','D','0','2','1',' ',' '};/*F18A 供应商代码A755E02145*/

INT8U  cSystemSupplierECUHardwareVersion[15] = {' ',' ',' ',' ',' ','H','0','0','3'};/*F191客户硬件版本号-- 此处不适用 需存EEPROM */
const INT8U  cVMFSystemSupplierECUSoftwareVersion[16] =
{'S','0','4','.','0','1','.','0','4','.','2','5','0','6','0','6'}; /*F189 日产客户软件版本号*/


const INT8U u8DareECUHWnumber[8] = {'E','H','0','0','0','0','0','1'};//3160 内部硬件版本号
const INT8U u8DareECUSWnumber[8] = {'E','S','0','0','0','0','0','1'};//3161
const INT8U u8DareECUpartnumber[16] = {'D','S','B','-','2','3','0','3','1','5','-','0','1','-','0','1'};//3162 ECU 序列号


static void CalculateDiagCofigChangeFlagFunction(INT8U Type,INT8U Data);

/*!
************************************************************************************************************************
* Function DIDReadRamDataComm,DIDWriteRamDataComm
* @brief 诊断数据读取,写入接口
* @param void
* @param void
* @returns
* @note
* @author zt
* @date 2021-01-28
************************************************************************************************************************
*/
void DIDReadRamDataComm(const INT8U* pDat, INT8U DatLen)
{
	INT8U i;
	INT8U TxDatLen = 3;

	for(i = 0; i < DatLen; i++)
	{
		TpTxInfoStruct.cDataBuf[TxDatLen++] =  pDat[i];
	}
	TpTxInfoStruct.wDataLength = TxDatLen;
	DescNrc = DescNrcOK;
}

void DIDWriteEepromDataComm(enSrvMemIndex MemIndex, INT8U* ptru8data, INT8U len)
{

	if( (ptru8data != NULL) && (len != 0U) && \
			((len + 3U) == TpRxInfoStruct.wDataLength) )
	{
		Appdesc_engCurrEEPOpDataID = MemIndex;
		Desc_OpTimeLongerThanP2Flag = TRUE;
		Srvl_WriteMemIndexData(MemIndex, ptru8data, len);
		DescNrc = kDescNrcResponsePending;
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
}

void DIDWriteRamDataComm(INT8U* ptru8data, INT8U len)
{
	INT8U i = 0;

	if( (ptru8data != NULL) && (len != 0U) && \
			((len + 3U) == TpRxInfoStruct.wDataLength) )
	{
		for(i = 0; i < len; i++)
		{
			ptru8data[i] = TpRxInfoStruct.cDataBuf[3U + i];
		}

		TpTxInfoStruct.wDataLength = 3;
		DescNrc = DescNrcOK;
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
}

/*!
************************************************************************************************************************
* Function Desc_ReadDID_F198_FingerPrintInformation
* @brief DID-F198 的读取 售后维修点代码
* @param void
* @param void
* @returns
* @note
* @author zt
* @date 2023-10-12
************************************************************************************************************************
*/
static void Desc_ReadDID_F198_FingerPrintInformation(void)
{
#if 1   /*20230919  */
	INT8U cDataBuf[D_FingerPrint_RepairShopCodeF198_Len_8] = {0};

	Srvl_ReadMemIndexData(EN_MemIndex_FingerPrint_RepairShopCodeF198, cDataBuf, D_FingerPrint_RepairShopCodeF198_Len_8);

	DIDReadRamDataComm(cDataBuf, D_FingerPrint_RepairShopCodeF198_Len_8);
#endif     
}
/*!
************************************************************************************************************************
* Function Desc_ReadDID_F199_FingerPrintInformation
* @brief DID-F199 的读取 刷写日期
* @param void
* @param void
* @returns
* @note
* @author zt
* @date 2023-10-12
************************************************************************************************************************
*/
static void Desc_ReadDID_F199_FingerPrintInformation(void)
{
#if 1   /*20230919  */
	INT8U cDataBuf[D_FingerPrint_ProgramDate_F199_Len_4] = {0};

	Srvl_ReadMemIndexData(EN_MemIndex_FingerPrint_ProgramDate_F199, cDataBuf, D_FingerPrint_ProgramDate_F199_Len_4);

	DIDReadRamDataComm(cDataBuf, D_FingerPrint_ProgramDate_F199_Len_4);
#endif     
}

/*!
************************************************************************************************************************
* Function Desc_ReadDID_F197_SystemName
* @brief DID-F197 的读取
* @param void
* @param void
* @returns
* @note
* @author zt
* @date 2021-01-29
************************************************************************************************************************
*/
static void Desc_ReadDID_F197_SystemName(void)
{
	INT8U cDataBuf[8] = {'D', 'S', 'M','_','B','4','1','V'};

	DIDReadRamDataComm(cDataBuf, 8);
}

/***********************************************************************
 * @function name: Desc_ReadDID_F180_BootVersion
 * 
 * @description: 读取boot版本号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 11:14
 ***********************************************************************/
void Desc_ReadDID_F180_BootVersion(void)
{
	INT8U i=0;
	INT8U u8TempBuff[D_CustomerBootVersion_Len_15] = {0};
	Srvl_ReadMemIndexData(EN_MemIndex_CustomerBootVersion, u8TempBuff, D_CustomerBootVersion_Len_15);
	for(i = 0; i < D_CustomerBootVersion_Len_15; i++)
	{
		TpTxInfoStruct.cDataBuf[3U + i] = u8TempBuff[i];
	}

	TpTxInfoStruct.wDataLength = D_CustomerBootVersion_Len_15 + 3U;
	DescNrc = DescNrcOK;
  
}

/*******************************************************************************
* Desc_ReadDID_F184_FingerPrint,Boot_DescWrtie_DIDF184
* 功能描述：DID-F184
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 
*******************************************************************************/
void Desc_ReadDID_F184_FingerPrint(void)
{
    #if 0   /*20230919  */
	INT8U i=0;
	INT8U u8TempBuff[D_DIAG_DIDF184_FDL_LEN] = {0};

	Ecual_FDL_GetBlockBuffData(D_FDL_BLOCK_INDEX_509, D_DIAG_FingerPrint_DIDF184_InBlockAddr, u8TempBuff, D_DIAG_DIDF184_FDL_LEN);
	for(i=0; i<D_DIAG_DIDF184_FDL_LEN; i++)
	{
		TpTxInfoStruct.cDataBuf[3U + i] = u8TempBuff[i];
	}

	TpTxInfoStruct.wDataLength = D_DIAG_DIDF184_FDL_LEN + 3U;
	DescNrc = DescNrcOK;
#endif    
}

/***********************************************************************
 * @function name: Desc_ReadDID_F189_SoftwareVersionNumber
 * 
 * @description: 读取 日产定义的ECU软件版本编号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 13:14
 ***********************************************************************/
void Desc_ReadDID_F189_SoftwareVersionNumber()
{
	DIDReadRamDataComm(GetDatBufAndLen(cVMFSystemSupplierECUSoftwareVersion));
}

/***********************************************************************
 * @function name: Desc_ReadDID_F187_PartNumber
 * 
 * @description: 读取 零部件号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 11:14
 ***********************************************************************/
void Desc_ReadDID_F187_PartNumber()
{
	DIDReadRamDataComm(GetDatBufAndLen(cPartNumber));
}

/***********************************************************************
 * @function name: DescDID_Read_F18A_SystemSupplierIdentifier
 * 
 * @description: 读取 供应商代码
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-06 11:14
 ***********************************************************************/
void DescDID_Read_F18A_SystemSupplierIdentifier(void)
{
	DIDReadRamDataComm(GetDatBufAndLen(cSystemSupplierIdentifier));
}

/***********************************************************************
 * @function name: DescDID_Read_F18B_ECUManufactureDate
 * 
 * @description: 读取产品生产日期
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 14:14
 ***********************************************************************/
void DescDID_Read_F18B_ECUManufactureDate(void)
{
	INT8U cDataBuf[D_ECUManufactureData_Len_4] ={0};
	
	Srvl_ReadMemIndexData(EN_MemIndex_ECUManufactureData, cDataBuf, D_ECUManufactureData_Len_4);
	
	DIDReadRamDataComm(cDataBuf, D_ECUManufactureData_Len_4);
}

/***********************************************************************
 * @function name: DescDID_Write_F18B_ECUManufactureDate
 * 
 * @description: 写入产品生产日期
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 14:14
 ***********************************************************************/
void DescDID_Write_F18B_ECUManufactureDate(void)
{
	DIDWriteEepromDataComm(EN_MemIndex_ECUManufactureData, (INT8U*)&TpRxInfoStruct.cDataBuf[3], D_ECUManufactureData_Len_4);
}

/***********************************************************************
 * @function name: Desc_ReadDID_F190_VIN
 * 
 * @description: 读取VIN码
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-24 11:14
 ***********************************************************************/
void Desc_ReadDID_F190_VIN()
{
	INT8U cDataBuf[D_UdsDidVinCode_Len_17] ={0};
	
	Srvl_ReadMemIndexData(EN_MemIndex_UdsDidVinCode, cDataBuf, D_UdsDidVinCode_Len_17);
	
	DIDReadRamDataComm(cDataBuf, D_UdsDidVinCode_Len_17);
}

/***********************************************************************
 * @function name: Desc_WriteDID_F190_VIN
 * 
 * @description: 写入VIN码
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-24 11:14
 ***********************************************************************/
void Desc_WriteDID_F190_VIN()
{
	DIDWriteEepromDataComm(EN_MemIndex_UdsDidVinCode, (INT8U*)&TpRxInfoStruct.cDataBuf[3], D_UdsDidVinCode_Len_17);
}

/***********************************************************************
 * @function name: DescDID_Read_F191_SystemSupplierECUHardwareVersion
 * 
 * @description: 读取ECU硬件版本号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-06 11:14
 ***********************************************************************/
void DescDID_Read_F191_SystemSupplierECUHardwareVersion(void)
{ 
	INT8U cDataBuf[D_ECUHardwareVersion_Len_16] ={0};
	
	Srvl_ReadMemIndexData(EN_MemIndex_ECUHardwareVersion, cDataBuf, D_ECUHardwareVersion_Len_16);
		
	DIDReadRamDataComm(cDataBuf, D_ECUHardwareVersion_Len_16);
}

/***********************************************************************
 * @function name: DescDID_Write_F191_SystemSupplierECUHardwareVersion
 * 
 * @description: 写ECU硬件版本号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 11:14
 ***********************************************************************/
void DescDID_Write_F191_SystemSupplierECUHardwareVersion(void)
{
	if(Srvl_GetMemIndexDataU8(EN_MemIndex_Write_HardwareVersion_Flg) == TRUE)
	{
		DIDWriteEepromDataComm(EN_MemIndex_ECUHardwareVersion, (INT8U*)&TpRxInfoStruct.cDataBuf[3], D_ECUHardwareVersion_Len_16);
		//写客户硬件版本号成功 ，设置不能再写
		if(DescNrc == kDescNrcResponsePending)
		{
			Srvl_SetMemIndexDataU8(EN_MemIndex_Write_HardwareVersion_Flg,FALSE);
		}
	}
	else
	{
		DescNrc = kDescNrcConditionsNotCorrect;
	}
}



/***********************************************************************
 * @function name: DescDID_Read_F193_SystemSupplierECUSoftwareVersion
 * 
 * @description: 读取内部ECU硬件版本号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 19:14
 ***********************************************************************/
 void DescDID_Read_F193_SystemSupplierECUHardwareVersion(void)
{
	DIDReadRamDataComm(GetDatBufAndLen(cFZBHardwareNumber));
}

/***********************************************************************
 * @function name: DescDID_Read_F195_SystemSupplierECUSoftwareVersion
 * 
 * @description: 读取内部ECU软件版本号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 19:14
 ***********************************************************************/
 void DescDID_Read_F195_SystemSupplierECUSoftwareVersion(void)
{
	DIDReadRamDataComm(GetDatBufAndLen(cFZBSWVersionNumber));
}

/***********************************************************************
 * @function name: DescDID_Read_F101_VechileFunctionConfiguration
 * 
 * @description: 读取车辆配置
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 11:14
 ***********************************************************************/
void DescDID_Read_F101_VechileFunctionConfiguration(void)
{
	AppRAM_unDSMHumanInterface_Obj cDataBuf = {0};
		
	
	cDataBuf.Bits.DrAdjust = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	cDataBuf.Bits.PaAdjust = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	cDataBuf.Bits.DrHeatVent = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig);
	cDataBuf.Bits.DrMemory = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	cDataBuf.Bits.PaHeatVent = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig);
	cDataBuf.Bits.PaMemory = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	cDataBuf.Bits.seatMassage = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageConfig);
	
    cDataBuf.Bits.DrHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeatFlg);
    cDataBuf.Bits.PaHeatFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaHeatFlg);
    cDataBuf.Bits.DrVentFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentFlg);
    cDataBuf.Bits.PaVentFlg = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentFlg);
    
	cDataBuf.Bits.Resvd1 = Srvl_GetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte0); //预留项2bit
	cDataBuf.Bits.Resvd2 = Srvl_GetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte1); //预留项8bit
	cDataBuf.Bits.Resvd3 = Srvl_GetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte2); //预留项8bit
	cDataBuf.Bits.Resvd4 = Srvl_GetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte3); //预留项8bit
	cDataBuf.Bits.Resvd5 = Srvl_GetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte4); //预留项8bit
	
	DIDReadRamDataComm(cDataBuf.Byte, D_VEHICLE_CFG_LEN);   

}

/***********************************************************************
 * @function name: DescDID_Write_F101_VechileFunctionConfiguration
 * 
 * @description: 写车辆配置
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-10-25 11:14
 ***********************************************************************/
void DescDID_Write_F101_VechileFunctionConfiguration(void)
{
	AppRAM_unDSMHumanInterface_Obj cDataBuf = {0};

	BOOL res = TRUE;

	INT8U i = 0;
	
	if((D_VEHICLE_CFG_LEN   + 3U) == TpRxInfoStruct.wDataLength)
	{
		memcpy(cDataBuf.Byte, (INT8U*)&TpRxInfoStruct.cDataBuf[3], D_VEHICLE_CFG_LEN);

		Srvl_SetMemIndexDataU8(EN_MemIndex_DrAdjustConfig, cDataBuf.Bits.DrAdjust);

		Srvl_SetMemIndexDataU8(EN_MemIndex_PaAdjustConfig, cDataBuf.Bits.PaAdjust);

		Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig, cDataBuf.Bits.DrHeatVent);

		Srvl_SetMemIndexDataU8(EN_MemIndex_DrMemoryConfig, cDataBuf.Bits.DrMemory);

		Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig, cDataBuf.Bits.PaHeatVent);

		Srvl_SetMemIndexDataU8(EN_MemIndex_PaMemoryConfig, cDataBuf.Bits.PaMemory);

		Srvl_SetMemIndexDataU8(EN_MemIndex_MassageConfig, cDataBuf.Bits.seatMassage);

		Srvl_SetMemIndexDataU8(EN_MemIndex_DrHeatFlg, cDataBuf.Bits.DrHeatFlg);

		Srvl_SetMemIndexDataU8(EN_MemIndex_PaHeatFlg, cDataBuf.Bits.PaHeatFlg);

		Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentFlg, cDataBuf.Bits.DrVentFlg);

		Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentFlg, cDataBuf.Bits.PaVentFlg);

		Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte0, cDataBuf.Bits.Resvd1);
		Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte1, cDataBuf.Bits.Resvd2);
		Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte2, cDataBuf.Bits.Resvd3);
		Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte3, cDataBuf.Bits.Resvd4);
		Srvl_SetMemIndexDataU8(EN_MemIndex_VehicleConfigReserveByte4, cDataBuf.Bits.Resvd5);

		/*确认主副驾记忆迎宾功能配置是否改变*/
		CalculateDiagCofigChangeFlagFunction(D_DriverSeat,cDataBuf.Bits.DrMemory);
		CalculateDiagCofigChangeFlagFunction(D_PassengerSeat,cDataBuf.Bits.PaMemory);
		TpTxInfoStruct.wDataLength = 3;
		DescNrc = DescNrcOK;
		if(cDataBuf.Bits.DrMemory == FALSE)
		{
			for(i = EN_MemIndex_DrHardStopPos_Height; i <= EN_MemIndex_DrHardStopPos_Front; i++)
			{
//				Ecual_AdcSetReadStopPosi(0);
				Srvl_SetMemIndexDataU16(i,0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_DrHardStopPos_Height + EN_MemIndex_DrMem1_Height, 0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_DrHardStopPos_Height + EN_MemIndex_DrMem2_Height, 0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_DrHardStopPos_Height + EN_MemIndex_DrMem3_Height, 0xFFFF);
			}
            Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem1_ValidFlag, 0);
            Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem2_ValidFlag, 0);
            Srvl_SetMemIndexDataU16(EN_MemIndex_DrMem3_ValidFlag, 0);
		}
		if(cDataBuf.Bits.PaMemory == FALSE)
		{
			for(i = EN_MemIndex_PaHardStopPos_Height; i <= EN_MemIndex_PaHardStopPos_Front; i++)
			{
//				Ecual_AdcSetReadStopPosi(1);
				Srvl_SetMemIndexDataU16(i,0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_PaHardStopPos_Height + EN_MemIndex_PaMem1_Height, 0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_PaHardStopPos_Height + EN_MemIndex_PaMem2_Height, 0xFFFF);
                Srvl_SetMemIndexDataU16(i - EN_MemIndex_PaHardStopPos_Height + EN_MemIndex_PaMem3_Height, 0xFFFF);
            }
            Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem1_ValidFlag, 0);
            Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem2_ValidFlag, 0);
            Srvl_SetMemIndexDataU16(EN_MemIndex_PaMem3_ValidFlag, 0);
		}
	}   
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
  

}

/***********************************************************************
 * @function name: DescDID_Write_F1FA_SystemFunctionConfiguration
 * 
 * @description: 写系统功能配置
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2024-04-11 14:43
 ***********************************************************************/
void DescDID_Write_F1FA_SystemFunctionConfiguration(void)
{
	INT8U u8TempBuff[1] = {0};
	
	DIDWriteEepromDataComm(EN_MemIndex_SystemFunctionConfiguration_F1FA, (INT8U*)&TpRxInfoStruct.cDataBuf[3], D_SystemFunctionConfiguration_F1FA_Len_6);
	u8TempBuff[0] = TpRxInfoStruct.cDataBuf[8] & 0x0C;/*取DID : 0xF1FA第5字节bit2~bit3 PHEV配置*/
	u8TempBuff[0] = u8TempBuff[0] >> 2U;
	if(0x0U != u8TempBuff[0])
	{
		Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg, 1); 		//加热P20PHEV发动机使能配置使能
	}
	else
	{
		Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg, 0); 		//加热P20PHEV发动机使能配置禁能
	}
}

/***********************************************************************
 * @function name: DescDID_Read_F1FA_SystemFunctionConfiguration
 * 
 * @description: 读系统功能配置
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2024-04-11 14:43
 ***********************************************************************/
void DescDID_Read_F1FA_SystemFunctionConfiguration()
{
	INT8U cDataBuf[D_SystemFunctionConfiguration_F1FA_Len_6] ={0};
	
	Srvl_ReadMemIndexData(EN_MemIndex_SystemFunctionConfiguration_F1FA, cDataBuf, D_SystemFunctionConfiguration_F1FA_Len_6);
	
	DIDReadRamDataComm(cDataBuf, D_SystemFunctionConfiguration_F1FA_Len_6);
}



/***********************************************************************
 * @function name: CalculateDiagCofigChangeFlagFunction
 * 
 * @description: 计算F101配置是否改变
 * 
 * @input parameters: Type : 0x0:Driver 0x01:Passenger; Data:Diagnose Request config Data
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-05-30 11:43
 ***********************************************************************/
static void CalculateDiagCofigChangeFlagFunction(INT8U Type,INT8U Data)
{
	INT8U MemoryStatus[2] = {0x0U};
	
	MemoryStatus[D_DriverSeat] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	MemoryStatus[D_PassengerSeat] = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);

	if(D_DriverSeat == Type)
	{
		/*主驾记忆迎宾功能改变*/
		if(MemoryStatus[D_DriverSeat] != Data)
		{
			s_ConfigChangeFlag[D_DriverSeat] = TRUE;
		}
	}
	else
	{
		/*副驾记忆迎宾功能改变*/
		if(MemoryStatus[D_PassengerSeat] != Data)
		{
			s_ConfigChangeFlag[D_PassengerSeat] = TRUE;
		}
	}
}

/***********************************************************************************************
 * @function name:  ClearDiagConfigChangeFlagFunction
 *
 * @description:    将F101改变标志位延时50ms清零
 *
 * @input parameters:    void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           需要在10ms任务调度周期内执行
 *
 * @author:         Prima Niu
 *
 * @date:           2023.6.19 19:33
 ***********************************************************************************************/
void ClearDiagConfigChangeFlagFunction(void)
{
	static INT8U u8F1A1Timer50ms = 0x0u;

	if((TRUE == s_ConfigChangeFlag[D_DriverSeat]) || (TRUE == s_ConfigChangeFlag[D_PassengerSeat]))
	{
		(u8F1A1Timer50ms < D_50msTime)?(u8F1A1Timer50ms ++):(u8F1A1Timer50ms = D_50msTime);
	}
	/*50ms后清零F1A1改变标志位*/
	if(D_50msTime <= u8F1A1Timer50ms)
	{
		u8F1A1Timer50ms = 0x0u;
		s_ConfigChangeFlag[D_DriverSeat] = FALSE;
		s_ConfigChangeFlag[D_PassengerSeat] = FALSE;
	}
}

/***********************************************************************
 * @function name: GetDiagConfigChangeFlagFunc
 * 
 * @description:获取配置改变标志位
 * 
 * @input parameters: 主副驾类型Type : 0x0:Driver 0x01:Passenger;
 * 
 * @output parameters: 配置改变标志位
 * 
 * @return: 无
 * 
 * @note: 配置改变标志位:TRUE-改变;FALSE-不改变
 * 
 * @author: Prima Niu
 * 
 * @date: 2023-06-19 16:33
 ***********************************************************************/
INT8U GetDiagConfigChangeFlagFunc(INT8U Type)
{
	return s_ConfigChangeFlag[Type];
}

/***********************************************************************
 * @function name: DescDID_Read_3160_DareECUHWnumber
 * 
 * @description: 读取 内部硬件版本
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-06 11:14
 ***********************************************************************/
void DescDID_Read_3160_DareECUHWnumber(void)
{
	DIDReadRamDataComm(u8DareECUHWnumber,8);
}

/***********************************************************************
 * @function name: DescDID_Read_3161_DareECUSWnumber
 * 
 * @description: 读取 内部软件版本
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-06 11:14
 ***********************************************************************/
void DescDID_Read_3161_DareECUSWnumber(void)
{
	DIDReadRamDataComm(u8DareECUSWnumber,8);
}

/***********************************************************************
 * @function name: DescDID_Read_3162_DareECUpartnumber
 * 
 * @description: 读取 ECU序列号
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-07 11:14
 ***********************************************************************/
void DescDID_Read_3162_DareECUpartnumber(void)
{
	DIDReadRamDataComm(u8DareECUpartnumber,16);
}

/***********************************************************************
 * @function name: DescDID_Read_3163_Voltagestate
 * 
 * @description: 读取 座椅供电电压
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-07 11:14
 ***********************************************************************/
void DescDID_Read_3163_Voltagestate(void)
{
    #if 0   /*20230919  */
	INT8U cDataBuf[4] = {0x00};
	INT16U vot = 0x00;
		
	vot = Ecual_AdcGetChlStatus(EN_Chl_PowerADetect) / 100;	
	cDataBuf[0] = (INT8U)((vot >> 8) & 0xFF);
	cDataBuf[1] = (INT8U)(vot & 0xFF);
	vot = Ecual_AdcGetChlStatus(EN_Chl_PowerBDetect) / 100;	
	cDataBuf[2] = (INT8U)((vot >> 8) & 0xFF);
	cDataBuf[3] = (INT8U)(vot & 0xFF);
	
	DIDReadRamDataComm(cDataBuf, UBOUND(cDataBuf));
#endif     
	
}

/***********************************************************************
 * @function name: DescDID_Read_3164_InputState
 * 
 * @description: 读取 输入状态
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-07 11:14
 ***********************************************************************/
void DescDID_Read_3164_InputState(void)
{
    #if 0   /*20230919  */
	INT8U cDataBuf[21] = {0x00};
	INT16U temp = 0;
	INT8U  temp_1 = 0;
	cDataBuf[0] = (INT8U) Ecual_AdcGetChlStatus(EN_Chl_KL15_IG1_STS);
	cDataBuf[0] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_DrHeightSw) << 1) & 0xFF);
	cDataBuf[0] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_DrLengthSw) << 3) & 0xFF);
	cDataBuf[0] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_DrFrontSw) << 5) & 0xFF);
	
	cDataBuf[1] = (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_DrBackSw) << 0) & 0xFF);
	cDataBuf[1] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_PaHeightSw) << 2) & 0xFF);
	cDataBuf[1] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_PaLengthSw) << 4) & 0xFF);
	cDataBuf[1] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_PaFrontSw) << 6) & 0xFF);

	cDataBuf[2] = (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_PaBackSw) << 0) & 0xFF);
	//cDataBuf[2] |= (INT8U)((Ecual_GetDigitalSwStatus(EN_MemorySetButton) << 2) & 0xFF);
	//cDataBuf[2] |= (INT8U)((Ecual_AdcGetChlStatus(EN_Chl_MemorySw) << 3) & 0xFF);
	temp_1 = CanRx_0x570_CAPE1_St_PowerMode();
	if(temp_1 == 0)
	{
		temp_1 = 0;
	}
	else if(temp_1 == 2)
	{
		temp_1 = 2;
	}
	else if(temp_1 == 4)
	{
		temp_1 = 3;
	}
	else
	{
		temp_1 = 1;
	}
	cDataBuf[2] |= (INT8U)((temp_1 << 5) & 0xFF);
	cDataBuf[2] |= (INT8U)((CanRx_0x570_CAPE1_F_PowerMode() << 7) & 0xFF);

	
	//主驾温度
	temp = Ecual_AdcGetDrNTCTempValue();
	cDataBuf[3] = (INT8U)((temp / 5) & 0xFF);
	
	//副驾温度
	temp = Ecual_AdcGetPaNTCTempValue();
	cDataBuf[4] = (INT8U)((temp / 5) & 0xFF);

	temp = Ecual_PosiPercent_Signals(EN_DriverHeight);
	cDataBuf[5] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[6] = (INT8U)((temp << 4) & 0xF0);
	
	temp = Ecual_PosiPercent_Signals(EN_DriverLength);
	cDataBuf[7] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[8] = (INT8U)((temp << 4) & 0xF0);
	
	temp = Ecual_PosiPercent_Signals(EN_DriverFront);
	cDataBuf[9] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[10] = (INT8U)((temp << 4) & 0xF0);
	
	temp = Ecual_PosiPercent_Signals(EN_DriverBack);
	cDataBuf[11] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[12] = (INT8U)((temp << 4) & 0xF0);

	temp = Ecual_PosiPercent_Signals(EN_PassengerHeight);
	cDataBuf[13] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[14] = (INT8U)((temp << 4) & 0xF0);

	temp = Ecual_PosiPercent_Signals(EN_PassengerLength);
	cDataBuf[15] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[16] = (INT8U)((temp << 4) & 0xF0);
	
	temp = Ecual_PosiPercent_Signals(EN_PassengerFront);
	cDataBuf[17] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[18] = (INT8U)((temp << 4) & 0xF0);
	
	temp = Ecual_PosiPercent_Signals(EN_PassengerBack);
	cDataBuf[19] = (INT8U)((temp >> 4) & 0xFF);
	cDataBuf[20] = (INT8U)((temp << 4) & 0xF0);

	DIDReadRamDataComm(cDataBuf,UBOUND(cDataBuf));
#endif   
} 

/***********************************************************************
 * @function name: DescDID_Read_3165_OutputState
 * 
 * @description: 读取 座椅输出状态
 * 
 * @input parameters: 无
 * 
 * @output parameters: 无
 * 
 * @return: 无
 * 
 * @note: 无
 * 
 * @author: zjx
 * 
 * @date: 2023-03-07 11:14
 ***********************************************************************/
void DescDID_Read_3165_OutputState(void)
{
   #if 0   /*20230919  */ 
	INT8U cDataBuf[5] = {0x00};
	
	cDataBuf[0]  = Rte_GetVfb_DrHeight();
	cDataBuf[0] |= Rte_GetVfb_DrLength() << 2;
	cDataBuf[0] |= Rte_GetVfb_DrFront() << 4;
	cDataBuf[0] |= Rte_GetVfb_DrBack() << 6;
	
	cDataBuf[1]  = Rte_GetVfb_PaHeight();
	cDataBuf[1] |= Rte_GetVfb_PaLength() << 2;
	cDataBuf[1] |= Rte_GetVfb_PaFront() << 4;
	cDataBuf[1] |= Rte_GetVfb_PaBack() << 6;
	
	cDataBuf[2]  = Rte_GetVfb_DrHeat();
	cDataBuf[2] |= Rte_GetVfb_PaHeat() << 2;
	cDataBuf[2] |= Rte_GetVfb_DrVentilate() << 4;
	cDataBuf[2] |= Rte_GetVfb_PaVentilate() << 6;
	
	cDataBuf[3]  = Rte_GetVfb_DrHeatPwmCnt();
	cDataBuf[4]  = Rte_GetVfb_PaHeatPwmCnt();
	
	DIDReadRamDataComm(cDataBuf,UBOUND(cDataBuf));
#endif    
}

/*******************************************************************************
**  注册读写DID
**
********************************************************************************/
const tDESC_DID_INFO pRWDIDInfoTbl[] =
{
	/* DID,    SessionAllow,           ReqDatLen, ServiceProcess */
	/******************DID - Logistics****************************************/
	{
		0xF101, {SESN_DES,	FALSE,	DescDID_Read_F101_VechileFunctionConfiguration},
					{SESN_DES,	Desc_enmSecExtLvl,	DescDID_Write_F101_VechileFunctionConfiguration}	
	},
	
	{
		0xF1FA, {SESN_DES,	FALSE,	DescDID_Read_F1FA_SystemFunctionConfiguration},
					{SESN_DES,	Desc_enmSecExtLvl,	DescDID_Write_F1FA_SystemFunctionConfiguration}	
	},
	
	{
		0xF198, {SESN_DES, 	FALSE,	Desc_ReadDID_F198_FingerPrintInformation},
		{__DIDNOTSUPPORTWRITE}
	},

	{
		0xF199, {SESN_DES, 	FALSE,	Desc_ReadDID_F199_FingerPrintInformation},
		{__DIDNOTSUPPORTWRITE}
	},
	
	{
		0xF197, {SESN_DES, 	FALSE,	Desc_ReadDID_F197_SystemName},
		{__DIDNOTSUPPORTWRITE}
	},

	


	{
		0xF180, {SESN_DES, 	FALSE,	Desc_ReadDID_F180_BootVersion},
		{__DIDNOTSUPPORTWRITE}
	},


	{
		0xF184, {SESN_DES, 	FALSE,	Desc_ReadDID_F184_FingerPrint},
		{__DIDNOTSUPPORTWRITE}
	},
	
	{
		0xF187, {SESN_DES, 	FALSE,	Desc_ReadDID_F187_PartNumber},
		{__DIDNOTSUPPORTWRITE}
	},
	
	{
		0xF189, {SESN_DES, 	FALSE,	Desc_ReadDID_F189_SoftwareVersionNumber},
		{__DIDNOTSUPPORTWRITE}
	},
	
	{
		0xF18A, {SESN_DES, 	FALSE,	DescDID_Read_F18A_SystemSupplierIdentifier},
		{__DIDNOTSUPPORTWRITE},
	},
	
	{
		0xF18B, {SESN_DES, 	FALSE,	DescDID_Read_F18B_ECUManufactureDate},
		{SESN_EXTDS, Desc_enmSecExtLvl,DescDID_Write_F18B_ECUManufactureDate},
	},
	
//	{
//		0xF190, {SESN_DES, 	FALSE,	Desc_ReadDID_F190_VIN},
//		{SESN_EXTDS, Desc_enmSecExtLvl, Desc_WriteDID_F190_VIN},
//	},
	
	{
		0xF191, {SESN_DES, 	FALSE,	DescDID_Read_F191_SystemSupplierECUHardwareVersion},
		{SESN_EXTDS, Desc_enmSecExtLvl, DescDID_Write_F191_SystemSupplierECUHardwareVersion},
	},
	
	{
		0xF195, {SESN_DES, 	FALSE,	DescDID_Read_F195_SystemSupplierECUSoftwareVersion},
		{__DIDNOTSUPPORTWRITE}
	},
	
	{
		0xF193, {SESN_DES, 	FALSE,	DescDID_Read_F193_SystemSupplierECUHardwareVersion},
		{__DIDNOTSUPPORTWRITE}
	},

	
		
	{
		0x3160, {SESN_DES, FALSE,	  DescDID_Read_3160_DareECUHWnumber},
		{__LIDNOTSUPPORTWRITE}
	},
	
	{
		0x3161, {SESN_DES, FALSE,	  DescDID_Read_3161_DareECUSWnumber},	
		{__LIDNOTSUPPORTWRITE}
	},
	
	{
		0x3162, {SESN_DES, FALSE,	  DescDID_Read_3162_DareECUpartnumber}, 
		{__LIDNOTSUPPORTWRITE}
	},
	
	{
		0x3163, {SESN_DES, FALSE,	  DescDID_Read_3163_Voltagestate},		
		{__LIDNOTSUPPORTWRITE}
	},
	
	{
		0x3164, {SESN_DES, FALSE,	  DescDID_Read_3164_InputState},		
		{__LIDNOTSUPPORTWRITE}
	},
	
	{
		0x3165, {SESN_DES, FALSE,	  DescDID_Read_3165_OutputState},		
		{__LIDNOTSUPPORTWRITE}
	},
    {
		0xFE06, {SESN_DE,       FALSE,   Test_ReadDID_FE06},
        {SESN_ES,                   }
    },
    {
		0xFF06, {SESN_DE,       FALSE,   Test_ReadDID_FF06},
        {SESN_ES,                   }
    },
	/******************DID - Configuration****************************************/


	/******************EBS - UDS - Configuration****************************************/

	/***********************DID - Bitmapped**************************************/
	/***********************DID - Non Bitmapped**************************************/

	/************************FZB-自己增加的DID*******************/
	/*LID Relation*/
	RWLIDLIST,
	/*LID (FZB) Relation*/
	RWLIDFZBLIST,
	/*Calibration Relation*/
	//RWCALIBDID
	D_UDS_PERIOD_DID_LIST,
	D_TEST_C4_DID_LIST,
};


/**************************************************************************
* 函数名称：DescWrRdDIDOp
* 功能描述：诊断读写DID操作
* 入口参数：RWSlc:R/W选择
* 出口参数：无
* 返 回 值：无
* 备    注: 不可更改
***************************************************************************/
void DescWrRdDIDOp(INT8U RWSlc)
{	
	static INT32U t_resetTime = 0;
	INT16U wDID;
	INT8U cSubServiceFound = FALSE;
	tR_DID_INFO tWRDIDInfo;
    INT8U ReadNrcFlg = FALSE;

	/*唤醒后读写服务延时3s才可使用，等待E2prom数据加载*/
//	if(CPU_TimerDiffTs(t_resetTime) < D_RWE2PROMTIME)
//	{
//		DescNrc = kDescNrcBusyRepeatRequest;
//		return;
//	}
	
	wDID = TpRxInfoStruct.cDataBuf[1];
	wDID <<= 8U;
	wDID |= TpRxInfoStruct.cDataBuf[2];
	if(eDID_R == RWSlc)
	{
        if(3U != TpRxInfoStruct.wDataLength) //Only one DataIdentifier.
        {
            ReadNrcFlg = TRUE;//某测试报文需要读长度非3
            DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
            if(wDID < 0xC400 || wDID > 0xC4FF)
            {
                return;
            }
        }
	}
	else if((TpRxInfoStruct.wDataLength < 4U) && (TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq))
	{
		DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
		return;
	}
	for(gRWDIDIndex = 0; gRWDIDIndex < UBOUND(pRWDIDInfoTbl); gRWDIDIndex++)
	{
		if(pRWDIDInfoTbl[gRWDIDIndex].sDID == wDID)
		{
			if(eDID_W == RWSlc)
			{
				TpTxInfoStruct.wDataLength = 3;
				if(TST_PhysicalReq != TpRxInfoStruct.cCANIDIndex)
				{
					TpRxState.engine = kRxState_Idle;
					DescNrc = DescNrcNoRsp;
					return;
				}
				if(DescSessionSA_CfgChk(eSID_WRITE_DATA_BY_IDENTIFIER_INDEX))
				{
					return;
				}
				if(SA_NULL != pDescSessSAConfigTbl[eSID_WRITE_DATA_BY_IDENTIFIER_INDEX].PhySessionSACfg.SA_Allow)
				{
					/*判断安全认证级别是否达到*/
					if(Desc_stsSecLvl.CurrLvl < pRWDIDInfoTbl[gRWDIDIndex].WriteIDInfo.MinRequiredLvl)
					{
						DescNrc = kDescNrcAccessDenied;
						return;
					}
				}
                        #if 1   /*20230919  */   
				if((Rte_GetVfb_VoltMode() != enFinalPowerMode_EN_NORMAL_VOLT) || \
					(DescCheckVehSpd() == FALSE) || DescGetSeatMoveStatusFlg() == TRUE) //车速大于3km/h
				{
					//run档和速度大于4不给使用
					DescNrc = kDescNrcConditionsNotCorrect;
					return;
				}
#endif
				tWRDIDInfo.SessionAllow = pRWDIDInfoTbl[gRWDIDIndex].WriteIDInfo.SessionAllow;
				tWRDIDInfo.ServiceProcess = pRWDIDInfoTbl[gRWDIDIndex].WriteIDInfo.ServiceProcess;
				tWRDIDInfo.SecuAcesReq = TRUE;
			}
			else
			{
				if(DescSessionSA_CfgChk(eSID_READ_DATA_BY_IDENTIFIER_INDEX))
				{
					return;
				}
				tWRDIDInfo.SessionAllow = pRWDIDInfoTbl[gRWDIDIndex].ReadDIDInfo.SessionAllow;
				tWRDIDInfo.ServiceProcess = pRWDIDInfoTbl[gRWDIDIndex].ReadDIDInfo.ServiceProcess;
				tWRDIDInfo.SecuAcesReq = pRWDIDInfoTbl[gRWDIDIndex].ReadDIDInfo.SecuAcesReq;
			}
			if(NULL != tWRDIDInfo.ServiceProcess)
			{
				cSubServiceFound = TRUE;
				tWRDIDInfo.ServiceProcess();
			}
			else
			{
				DescNrc = kDescNrcRequestOutOfRange;
			}
			break;
		}
	}
	if(FALSE == cSubServiceFound)
	{
		// Sub service not support
		if(TpRxInfoStruct.cCANIDIndex == TST_PhysicalReq)
		{
			DescNrc = (kDescNrcRequestOutOfRange);
		}
		else
		{
			if(eDID_R == RWSlc)
			{
				DescNrc = (kDescNrcRequestOutOfRange);
			}
		}
	}
    if(ReadNrcFlg == TRUE)
    {
        DescNrc = kDescNrcIncorrectMessageLengthOrInvalidFormat;
    }
}

/********************************************************************
* 函数名称：DescReadDataByIdentifier
* 功能描述：读DID
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescReadDataByIdentifier(void)
{
	DescWrRdDIDOp(eDID_R);
}

/********************************************************************
* 函数名称：DescWriteDataByIdentifier
* 功能描述：写DID
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
void DescWriteDataByIdentifier(void)
{
	DescWrRdDIDOp(eDID_W);
}

/***********************************************************************
 * @function name: DiagGetSwHeatTimer
 * 
 * @description: 获取方向盘加热时长
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 单位:10ms
 * 
 * @author: Prima Niu
 * 
 * @date: 2021-08-15 18:11
 ***********************************************************************/
INT32U DiagGetSwHeatTimer(void)
{
	return s_DiagSwHeatTimer;
}


/***********************************************************************
 * @function name: DiagSetSwHeatTimer
 * 
 * @description: 传递方向盘加热时长接口
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: Prima Niu
 * 
 * @date: 2021-08-15 18:11
 ***********************************************************************/
void DiagSetSwHeatTimer(INT32U Timer)
{
	s_DiagSwHeatTimer = Timer;
}

#endif
/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

