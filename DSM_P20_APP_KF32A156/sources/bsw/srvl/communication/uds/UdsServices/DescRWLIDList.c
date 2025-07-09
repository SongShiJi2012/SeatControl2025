/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescRWLIDList.c
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             读写LID列表源文件
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
#include "Ecual_Can.h"
#include "Desc.h"
#include "Ecual_Adc.h"
#include "Test.h"
#include "Srvl_E2memory.h"
#include "Rte_VfbInterface.h"
#include "Debug_VfbInterface.h"
#include "Cdd_Hall.h"
#include "Srvl_PowerMode.h"

INT8U RamTest1 = 0;    
INT8U RamTest2 = 0;



#define	RWLID_GLOBALS

//内部软件品号
const INT8U cFZBECUSoftwareArticleNumber[16] =
{
	"PSB-18013-01-00A"/*发布修改*/
};

const INT8U cFZBSWVersionNumber[16] =
{
    "T250613100"/*V版本需要同步修改客户软件版本号cVMFSystemSupplierECUSoftwareVersion，发布修改*/
};

#if (D_GPIO_CONFIG_TABLE_VER == D_GPIO_CONFIG_TABLE_VER_20230114)
//const INT8U  cFZBHardwareNumber[16] =
//{
//	"PCB-18012-01-00"
//};


const INT8U  cFZBHardwareVersion[16] =
{
	"2024-06-25-T1.3"
};

#elif (D_GPIO_CONFIG_TABLE_VER == D_GPIO_CONFIG_TABLE_VER_20230301)

//const INT8U  cFZBHardwareNumber[16] =
//{
//	"PCB-18012-01-01"
//};

const INT8U  cFZBHardwareVersion[16] =
{
	"2023-03-01-T1.1"
};

#elif (D_GPIO_CONFIG_TABLE_VER == D_GPIO_CONFIG_TABLE_VER_20230406)

//const INT8U  cFZBHardwareNumber[16] =
//{
//	"PCB-18012-01-03"
//};

const INT8U  cFZBHardwareVersion[16] =
{
	"2023-04-06-T1.3"
};

#else

//const INT8U  cFZBHardwareNumber[16] =
//{
//	"PCB-18012-01-04"
//};

const INT8U  cFZBHardwareVersion[16] =
{
	"2024-06-25-T1.3"
};

#endif


static INT8U u8DescCfgTimeParaTemporaryArray[D_DescCfgTimeParaTemporaryArrayNum] = {0};
static INT8U u8CheckSumDisable[1] = {0x0u};
static INT8U s_u8MassageTime[4] = {0x0u,0x0u,0x0u,0x0u};



void DescDID_Read_FZBECUSoftwareNumber(void)
{

	DIDReadRamDataComm(cFZBECUSoftwareArticleNumber, 16);

}

void DescDID_Read_FZBSWVersionNumber(void)
{
	DIDReadRamDataComm(cFZBSWVersionNumber, 16);
}

void DescDID_Read_FZBHardwareNumber(void)
{
	
}

void DescDID_Read_FZBHardwareVersion(void)
{
	DIDReadRamDataComm(cFZBHardwareVersion, 16);
}

void DescDID_Read_FZBBootVersion(void)
{
#if 0 /*20230619*/
	INT8U cDataBuf[D_BootVersion_FDL_LEN] ={0};
	
	(void)Ecual_FDL_ReadBootVersion(cDataBuf, D_BootVersion_FDL_LEN);
	
	DIDReadRamDataComm(cDataBuf, D_BootVersion_FDL_LEN);
#endif
}



/***********************************************************************
 * @function name: DescDID_Read_DriverSeatState
 *
 * @description: 诊断读取主驾座椅状态
 *
 * @input parameters: 
 *
 * @output parameters: void
 *
 * @return: 
 *
 * @note:
 *
 * @author: zjx
 *
 * @date: 2024/4/15
 ***********************************************************************/
void DescDID_Read_DriverSeatState(void)
{
	INT16U stopPoint = 0;
	INT8U cDataBuf[10] ={0};
	INT8U SeatMemoryValidCnt = 0;
#if 0		/* 后续调试打开 */
	cDataBuf[0] = Ecual_GetDigitalSwStatus(EN_DRHeightForwardSW);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRHeightBackwardSW) << 1);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRLengthForwardSW) << 2);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRLengthBackwardSW) << 3);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRBackForwardSW) << 4);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRBackBackwardSW) << 5);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRFrontForwardSW) << 6);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_DRFrontBackwardSW) << 7);  

	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_DRSeatHeightStop);
	cDataBuf[1] = ( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1;  
	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_DRSeatLengthStop);
	cDataBuf[1] |= ((( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1) << 1);  
	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_DRSeatBackrestStop);
	cDataBuf[1] |= ((( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1) << 2);  
	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_DRSeatFrontStop);
	cDataBuf[1] |= ((( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1) << 3);  
	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_DRSeatMemory1Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_DRSeatMemory2Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_DRSeatMemory3Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	cDataBuf[1] |= (SeatMemoryValidCnt << 4);

	cDataBuf[2] = Rte_GetVfb_DrHeightCmd();
	cDataBuf[2] |= (Rte_GetVfb_DrLengthCmd() << 2);
	cDataBuf[2] |= (Rte_GetVfb_DrBackCmd() << 4);
	cDataBuf[2] |= (Rte_GetVfb_DrFrontCmd() << 6);

	cDataBuf[3] = Rte_GetVfb_DrHeat();
	cDataBuf[3] |= (Rte_GetVfb_DrVent() << 2);

	cDataBuf[4] = (Cdd_GetCurrentHallCnt(EN_DriverLength) - Cdd_GetMotorHardStop(EN_DriverLength)) * 200 \
					/ Cdd_GetMotorSize(EN_DriverLength);

	cDataBuf[5] = (Cdd_GetCurrentHallCnt(EN_DriverHeight) - Cdd_GetMotorHardStop(EN_DriverHeight)) * 200 \
					/ Cdd_GetMotorSize(EN_DriverHeight);
	
	cDataBuf[6] = (Cdd_GetCurrentHallCnt(EN_DriverBack) - Cdd_GetMotorHardStop(EN_DriverBack)) * 200 \
					/ Cdd_GetMotorSize(EN_DriverBack);
	
	cDataBuf[7] = (Cdd_GetCurrentHallCnt(EN_DriverFront) - Cdd_GetMotorHardStop(EN_DriverFront)) * 200 \
					/ Cdd_GetMotorSize(EN_DriverFront);

	cDataBuf[8] = (Ecual_AdcGetDrNTCTempValue() / 10);

	cDataBuf[9] =  (100 - Ecual_PWM_ChannelGetDuty(EN_MCU_PIN62_FL_VENT_EN)) * 2;
#endif
	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));
}


/***********************************************************************
 * @function name: DescDID_Read_PassengerSeatState
 *
 * @description: 诊断读取副驾座椅状态
 *
 * @input parameters: 
 *
 * @output parameters: void
 *
 * @return: 
 *
 * @note:
 *
 * @author: zjx
 *
 * @date: 2024/4/15
 ***********************************************************************/
void DescDID_Read_PassengerSeatState(void)
{
	INT16U stopPoint = 0;
	INT8U cDataBuf[9] ={0};
	INT8U SeatMemoryValidCnt = 0;
#if 0		/* 后续调试打开 */
	cDataBuf[0] = (Ecual_GetDigitalSwStatus(EN_PALengthForwardSW) << 0);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_PALengthBackwardSW) << 1);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_PABackForwardSW) << 2);  
	cDataBuf[0] |= (Ecual_GetDigitalSwStatus(EN_PABackBackwardSW) << 3);  
	
	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_PASeatLengthStop);
	cDataBuf[0] |= ((( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1) << 4);  
	stopPoint = Srvl_GetMemIndexUserDSMStopPointData(EN_SRV_MemIndex_PASeatBackrestStop);
	cDataBuf[0] |= ((( stopPoint == 0 | stopPoint == 0xFFFF ) ? 0 : 1) << 5);  

	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_PASeatMemory1Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_PASeatMemory2Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	if(Srvl_GetMemIndexDataU16(EN_SRV_MemIndex_PASeatMemory3Valid) == 1)
	{
		SeatMemoryValidCnt += 1;
	}
	cDataBuf[0] |= (SeatMemoryValidCnt << 6);

	cDataBuf[1] = (Rte_GetVfb_PaLengthCmd() << 0);
	cDataBuf[1] |= (Rte_GetVfb_PaBackCmd() << 2);

	cDataBuf[2] = Rte_GetVfb_PaHeat();
	cDataBuf[2] |= (Rte_GetVfb_PaVent() << 2);

	cDataBuf[3] = (Cdd_GetCurrentHallCnt(EN_PassengerLength) - Cdd_GetMotorHardStop(EN_PassengerLength)) * 200 \
					/ Cdd_GetMotorSize(EN_PassengerLength);

	cDataBuf[4] = (Cdd_GetCurrentHallCnt(EN_PassengerBack) - Cdd_GetMotorHardStop(EN_PassengerBack)) * 200 \
					/ Cdd_GetMotorSize(EN_PassengerBack);
	
	cDataBuf[5] = (Ecual_AdcGetPaNTCTempValue() / 10);

	cDataBuf[6] =  (100 - Ecual_PWM_ChannelGetDuty(EN_MCU_PIN63_FR_VENT_EN)) * 2;
	
	cDataBuf[7] =  (Ecual_AdcGetCenterNTCTempValue() / 10);
	
	cDataBuf[8] =  Rte_GetVfb_ThirdHeatIo();
#endif
	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));
}

void DescDID_Read_BoardModuleGetInitRlt(void)
{
	INT8U cDataBuf[10] ={0};
	//INT8U i=0;

	cDataBuf[0]=0;
	cDataBuf[1]=0;
	cDataBuf[2]=0;
	
	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));
}

void DescDID_Read_BoardPowerOnCnt(void)
{
  #if 0 /*20230619*/
	INT8U cDataBuf[D_EE_BoardPowerOnTypeAndCnt_BuffIdxLen] ={0};
	
	(void)Srvl_ReadMemIndexData(EN_SRV_MemIndex_BoardPowerOnTypeAndCnt, cDataBuf, D_EE_BoardPowerOnTypeAndCnt_BuffIdxLen);
	DIDReadRamDataComm(cDataBuf, D_EE_BoardPowerOnTypeAndCnt_BuffIdxLen);
#endif      
}

void DescDID_Read_OSAllTaskRunCnt(void)
{
#if 0 
	INT8U cDataBuf[4U*D_AppTaskRunCnt_TaskNum] ={0};

	OS_GetAllTaskRunCnt(cDataBuf);
	DIDReadRamDataComm(cDataBuf, 4U*D_AppTaskRunCnt_TaskNum);
#endif        
}




void DescDID_Read_CycleMaxRunTime(void)
{
	INT8U cDataBuf[4U + 1U] ={0};
	INT32U u32Temp=0;


#if (D_MEAS_TASK_MAX_RUN_TIME == D_ENABLE)
	u32Temp = Os_GetCycleMaxRunTime();
#endif
	cDataBuf[0] = (u32Temp >> 24U) & 0xFFU;
	cDataBuf[1] = (u32Temp >> 16U) & 0xFFU;
	cDataBuf[2] = (u32Temp >> 8U) & 0xFFU;
	cDataBuf[3] = (u32Temp >> 0U) & 0xFFU;

#if (D_OS_LIMIT_MAIN_CYCLE_TIME == D_ENABLE)
	cDataBuf[4] = Os_GetMaxRunTimeTaskId();
#endif

	DIDReadRamDataComm(cDataBuf, 5U);
}

void DescDID_Read_McuWakeupSource(void)
{
	INT8U cData =0;

//	cData = Srvl_Pwr_GetMcuWakeupSource(); /*20230619*/
	DIDReadRamDataComm(&cData, 1U);
}

#define D_ChlUpMidLowRange_Len		(6U)
void DescDID_Read_AdcUpMidLowRangeChl0(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(0); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl1(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(1); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl2(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(2); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl3(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(3); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl4(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(4); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl5(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(5); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl6(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(6); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl7(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(7); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl8(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(1); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl9(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(9); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl10(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(10); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl11(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(11); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl12(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(12); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl13(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(13); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl14(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(14); /*20230919  未添加*/
	if(pRange != NULL)
	{
		Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl15(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(15); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl16(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(16); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl17(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(17); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl18(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(18); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl19(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(19); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl20(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(20); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl21(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(21); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);    /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl22(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(22); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl23(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(23); /*20230919  未添加*/
	if(pRange != NULL)
	{
		//Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_AdcUpMidLowRangeChl24(void)
{
	INT8U cDataBuf[D_ChlUpMidLowRange_Len] ={0};
	INT8U *pRange = NULL;

	//pRange = Ecual_AdcGetChlUpMidLowRange(24); /*20230919  未添加*/
	if(pRange != NULL)
	{
	//	Com_MemCmp(cDataBuf, pRange, D_ChlUpMidLowRange_Len);   /*20230919  未添加*/
		DIDReadRamDataComm(cDataBuf, D_ChlUpMidLowRange_Len);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

/***********************************************************************
 * @function name: DescDID_Read_BtsHighDriverChipIsInfo
 *
 * @description: 诊断读取高驱电流
 *
 * @input parameters: 
 *
 * @output parameters: void
 *
 * @return: 
 *
 * @note:
 *
 * @author: LC
 *
 * @date: 2023/7/5
 ***********************************************************************/

void DescDID_Read_BtsHighDriverChipIsInfo(void)
{

	INT8U cDataBuf[22] = {0x0U}; 
	INT8U Index = 0;
#if 0
//	
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DriverHeatLp,0) >> 8) & 0xFF);		/* 主驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DriverHeatLp,0) & 0xFF); 					/* 主驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DriverHeatLp,1) >> 8) & 0xFF);		/* 主驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_DriverHeatLp,1) & 0xFF); 				/* 主驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,0) >> 8) & 0xFF);		/* 副驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,0) & 0xFF); 					/* 副驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,1) >> 8) & 0xFF);		/* 副驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,1) & 0xFF); 				/* 副驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,0) >> 8) & 0xFF);		/* 副驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,0) & 0xFF); 					/* 副驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,1) >> 8) & 0xFF);		/* 副驾加热电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_PassengerHeatLp,1) & 0xFF); 				/* 副驾加热电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_VentilatePWRLp,0) >> 8) & 0xFF);		/* 主副通风PWR电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_VentilatePWRLp,0) & 0xFF); 					/* 主副通风PWR电流检测 */
//
//	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_VentilatePWRLp,1) >> 8) & 0xFF);		/* 主副通风PWR电流检测 */
//	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_VentilatePWRLp,1) & 0xFF); 				/* 主副通风PWR电流检测 */

	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_BoardPowerLp,0) >> 8) & 0xFF);		/* 板上供电电流检测 */
	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_BoardPowerLp,0) & 0xFF); 					/* 板上供电电流检测 */

	cDataBuf[Index++] = (INT8U)((Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_BoardPowerLp,1) >> 8) & 0xFF);		/* 板上供电电流检测 */
	cDataBuf[Index++] =	(INT8U)(Ecual_AdcGetBoardBtsHighDriverIS(D_BtsHighDriverChip_BoardPowerLp,1) & 0xFF); 				/* 板上供电电流检测 */
#endif
	DIDReadRamDataComm(cDataBuf, Index);

}

void DescDID_Read_F222_DISwitchStatus(void)
{
	INT8U cDataBuf[12] ={0};
	INT8U i=0;
#if 0
	cDataBuf[0] = Ecual_GetDigitalSwStatus(EN_DRLengthBackwardSW);
	cDataBuf[1] = Ecual_GetDigitalSwStatus(EN_DRLengthForwardSW);
	cDataBuf[2] = Ecual_GetDigitalSwStatus(EN_DRHeightBackwardSW);
	cDataBuf[3] = Ecual_GetDigitalSwStatus(EN_DRHeightForwardSW);
	cDataBuf[4] = Ecual_GetDigitalSwStatus(EN_DRBackBackwardSW);
	cDataBuf[5] = Ecual_GetDigitalSwStatus(EN_DRBackForwardSW);
	cDataBuf[6] = Ecual_GetDigitalSwStatus(EN_DRFrontBackwardSW);
	cDataBuf[7] = Ecual_GetDigitalSwStatus(EN_DRFrontForwardSW);
	cDataBuf[8] = Ecual_GetDigitalSwStatus(EN_PABackBackwardSW);
	cDataBuf[9] = Ecual_GetDigitalSwStatus(EN_PABackForwardSW);
	cDataBuf[10] = Ecual_GetDigitalSwStatus(EN_PALengthBackwardSW);
	cDataBuf[11] = Ecual_GetDigitalSwStatus(EN_PALengthForwardSW);
#endif
	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));
}
void DescDID_Read_F223_AdSwitchStatus(void)
{
	INT8U cDataBuf[46] ={0};
	INT8U i=0;
	INT16U val = 0;
	INT16U va2 = 0;
	INT16U va3 = 0;
	INT16U va4 = 0;
	INT16U va5 = 0;
	INT16U va6 = 0;
#if 0
	val = Ecual_AdcGetChlStatus(D_Chl_DriverHeatNTC);
	cDataBuf[0]  =   (INT8U)val;
	cDataBuf[1]  =   (INT8U)(val >> 8);
	va2 = Ecual_AdcGetChlStatus(D_Chl_PassengerHeatNTC);
	cDataBuf[2]  =   (INT8U)va2;
	cDataBuf[3]  =   (INT8U)(va2 >> 8);

	va3 = Ecual_AdcGetHighDriverIs(EN_HighDriverChip_DrvHeat);
	cDataBuf[4] = (INT8U)va3;
	cDataBuf[5] = (INT8U)(va3 >> 8);

	va4 = Ecual_AdcGetHighDriverIs(EN_HighDriverChip_PaHeat);
	cDataBuf[6] = (INT8U)va4;
	cDataBuf[7] = (INT8U)(va4 >> 8);

	cDataBuf[8] = Ecual_GetDigitalSwStatus(EN_DRVenFeedback);
	cDataBuf[9] = Ecual_GetDigitalSwStatus(EN_PaVenFeedback);


	cDataBuf[10] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_11);  //DrLengthBRVotFlg
	cDataBuf[11] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_10); //DrLengthFWVotFlg
	cDataBuf[12] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_9); //PaLengthBRVotFlg
	cDataBuf[13] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_6); //PaLengthFWVotFlg
	cDataBuf[14] = Ecual_SeatRelayValidCheck(EN_ADC0_RSEQ_12); //DrFrontDNVotFlg
	cDataBuf[15] = Ecual_SeatRelayValidCheck(EN_ADC0_RSEQ_13); // DrFrontUPVotFlg
	cDataBuf[16] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_13); // DrBackBRVotFlg
	cDataBuf[17] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_12); // DrBackFWVotFlg
	
    cDataBuf[18] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_8); // PaBackBRVotFlg
	cDataBuf[19] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_7); // PaBackFWVotFlg
	cDataBuf[20] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_14); // DrHeightUPVotFlg
	cDataBuf[21] = Ecual_SeatRelayValidCheck(EN_ADC1_RSEQ_15); // DrHeightDNVotFlg

	va5 = Ecual_AdcGetChlStatus(D_Chl_SteerHeatNTC);
	cDataBuf[22]  =   (INT8U)va5;
	cDataBuf[23]  =   (INT8U)(va5 >> 8);

	va6 = Ecual_AdcGetHighDriverIs(En_HighDriverChip_ThirdBHeat);
	cDataBuf[24]  =   (INT8U)va6;
	cDataBuf[25]  =   (INT8U)(va6 >> 8);//补充方向的NTC和加热电流
	
	cDataBuf[26] = Ecual_GpioGetChlState(EN_MCU_PIN21_VENTILATION_FB);
	cDataBuf[27] = Ecual_GpioGetChlState(EN_MCU_PIN22_VENTILATION_FB);
	cDataBuf[28] = Ecual_GpioGetChlState(EN_MCU_PIN27_VENTILATION_FB);
	cDataBuf[29] = Ecual_GpioGetChlState(EN_MCU_PIN28_VENTILATION_FB);

	//霍尔信号反馈 - 给工装检测高低电平 - 低有效
	val = Mcal_AdcGetCurrentValue(D_Chl_DriverHeightHall);
	cDataBuf[30] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[31] = (INT8U)((val >> 0) & 0xFF);


	val = Mcal_AdcGetCurrentValue(D_Chl_DriverLengthHall);
	cDataBuf[32] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[33] = (INT8U)((val >> 0) & 0xFF);

	val = Mcal_AdcGetCurrentValue(D_Chl_DriverBackHall);
	cDataBuf[34] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[35] = (INT8U)((val >> 0) & 0xFF);

	val = Mcal_AdcGetCurrentValue(D_Chl_DriverFrontHeightHall);
	cDataBuf[36] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[37] = (INT8U)((val >> 0) & 0xFF);

//	val = Mcal_AdcGetCurrentValue();//预留
//	cDataBuf[38] = (INT8U)((val >> 8) & 0xFF);
//	cDataBuf[39] = (INT8U)((val >> 0) & 0xFF);

	val = Mcal_AdcGetCurrentValue(D_Chl_PassengerLengthHall);
	cDataBuf[40] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[41] = (INT8U)((val >> 0) & 0xFF);

	val = Mcal_AdcGetCurrentValue(D_Chl_PassengerBackHall);
	cDataBuf[42] = (INT8U)((val >> 8) & 0xFF);
	cDataBuf[43] = (INT8U)((val >> 0) & 0xFF);

//	val = Mcal_AdcGetCurrentValue();//预留
//	cDataBuf[44] = (INT8U)((val >> 8) & 0xFF);
//	cDataBuf[45] = (INT8U)((val >> 0) & 0xFF);


#endif

	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));
}
/***********************************************************************
 * @function name: DescDID_Read_3134_HallStatus
 * @description: 读取当前霍尔坐标值
 * @input parameters: 无
 * @output parameters: 无
 * @return: 无
 * @note: 无
 * @author: zjx
 * @date: 2023-11-21 09:14
 ***********************************************************************/
void DescDID_Read_3134_HallStatus(void)
{
	INT8U cDataBuf[16] = {0};
	INT16U temp = 0;

	temp = Cdd_GetCurrentHallCnt(EN_DriverHeight);
	cDataBuf[0] = (INT8U)(temp >> 8);
	cDataBuf[1] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_DriverLength);
	cDataBuf[2] = (INT8U)(temp >> 8);
	cDataBuf[3] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_DriverBack);
	cDataBuf[4] = (INT8U)(temp >> 8);
	cDataBuf[5] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_DriverFront);
	cDataBuf[6] = (INT8U)(temp >> 8);
	cDataBuf[7] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_PaResever_1);
	cDataBuf[8] = (INT8U)(temp >> 8);
	cDataBuf[9] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_PassengerLength);
	cDataBuf[10] = (INT8U)(temp >> 8);
	cDataBuf[11] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_PassengerBack);
	cDataBuf[12] = (INT8U)(temp >> 8);
	cDataBuf[13] = (INT8U)(temp >> 0);

	temp = Cdd_GetCurrentHallCnt(EN_PaResever_2);
	cDataBuf[14] = (INT8U)(temp >> 8);
	cDataBuf[15] = (INT8U)(temp >> 0);

	DIDReadRamDataComm(GetDatBufAndLen(cDataBuf));

}
void DescDID_Read_DescSleepNormalModeTimeout(void)
{
	INT8U cDataBuf[1] ={0};

	cDataBuf[0] = u8DescCfgTimeParaTemporaryArray[D_DescSleepNormalModeTimeoutIndex];
	DIDReadRamDataComm(cDataBuf, 1);
}

void DescDID_Write_DescSleepNormalModeTimeout(void)
{
	INT8U cDataBuf[1] ={0};

//    if (UdsApp_GetSysOnlineTestModeInd() == FALSE)
//    {
//        DescNrc = kDescNrcConditionsNotCorrect;
//        return;
//    }

	cDataBuf[0] = TpRxInfoStruct.cDataBuf[3];
	if(cDataBuf[0] <= 60U)
	{
		DIDWriteRamDataComm(&u8DescCfgTimeParaTemporaryArray[D_DescSleepNormalModeTimeoutIndex], 1);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}

void DescDID_Read_DescForceSleepNormalModeTimeout(void)
{
	INT8U cDataBuf[1] ={0};

	cDataBuf[0] = u8DescCfgTimeParaTemporaryArray[D_DescForceSleepNormalModeTimeoutIndex];
	DIDReadRamDataComm(cDataBuf, 1);
}

void DescDID_Write_DescForceSleepNormalModeTimeout(void)
{
	INT8U cDataBuf[1] ={0};

//    if (UdsApp_GetSysOnlineTestModeInd() == FALSE)
//    {
//        DescNrc = kDescNrcConditionsNotCorrect;
//        return;
//    }

	cDataBuf[0] = TpRxInfoStruct.cDataBuf[3];
	if(cDataBuf[0] <= 30U)
	{
		DIDWriteRamDataComm(&u8DescCfgTimeParaTemporaryArray[D_DescForceSleepNormalModeTimeoutIndex], 1);
	}
	else
	{
		DescNrc = kDescNrcRequestOutOfRange;
	}
}




INT8U DescDID_GetDescCfgTimeParaTemporary(INT8U u8Index)
{
	INT8U u8Data=0;

	if(u8Index < D_DescCfgTimeParaTemporaryArrayNum)
	{
		u8Data = u8DescCfgTimeParaTemporaryArray[u8Index];
	}
	
	return u8Data;
}




void DescDID_Read_EepromInBusyTs(void)
{
	INT8U cDataBuf[4] ={0};

	DIDReadRamDataComm(cDataBuf, 4);
}

void DescDID_Read_EepromIndexOptRlt(void)
{
  #if 0 /*20231909*/
	INT8U cDataBuf[(INT16U)EN_MemIndex_Max] ={0};
	INT16U i=0;

	for(i=0; i<(INT16U)EN_MemIndex_Max ; i++)
	{
		cDataBuf[i] = IsE2promOptResultOK((enSrvMemIndex) i);
	}
	
	DIDReadRamDataComm(cDataBuf, (INT16U)EN_MemIndex_Max);
#endif      
}

void DescDID_Read_HalEepromPara_ID10(void)
{ 
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_10), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID11(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_11), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID12(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_12), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID13(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_13), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID14(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_14), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID15(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_15), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID16(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_16), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID17(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_17), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID18(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_18), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID19(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_19), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID20(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_20), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID21(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_21), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID22(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_22), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID23(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_23), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID24(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_24), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID25(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_25), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID26(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_26), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID27(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_27), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID28(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_28), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID29(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_29), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID30(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_30), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID31(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_31), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID32(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_32), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID33(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_33), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID34(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_34), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID35(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_35), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID36(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_36), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID37(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_37), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID38(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_38), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID39(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_39), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID10BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_10_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID11BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_11_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID12BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_12_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID13BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_13_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID14BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_14_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID15BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_15_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID16BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_16_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID17BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_17_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID18BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_18_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID19BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_19_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID20BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_20_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID21BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_21_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID22BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_22_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID23BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_23_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID24BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_24_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID25BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_25_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID26BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_26_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID27BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_27_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID28BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_28_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID29BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_29_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID30BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_30_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID31BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_31_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID32BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_32_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID33BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_33_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID34BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_34_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID35BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_35_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID36BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_36_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID37BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_37_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID38BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_38), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID39BackUp(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_39_BackUp), D_EEPROM_15BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID100(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_100), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID101(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_101), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID102(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_102), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID103(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_103), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID104(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_104), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID105(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_105), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID106(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_106), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID107(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_107), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID108(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_108), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID109(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_109), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID110(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_110), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID111(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_111), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID112(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_112), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID113(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_113), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID114(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_114), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID115(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_115), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID116(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_116), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID117(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_117), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID118(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_118), D_EEPROM_31BYTES_LEN);
}

void DescDID_Read_HalEepromPara_ID119(void)
{
	//DIDReadRamDataComm(Ecual_GetEepromParaPtr(EN_MEM_APP_DATA_ID_119), D_EEPROM_31BYTES_LEN);
}

void DescDID_FDB4_Read_CANchecksum(void)
{
	//DIDReadRamDataComm(u8CheckSumDisable, 1);
}

void DescDID_FDB4_Write_CANchecksum(void)
{
	if(0x01 < TpRxInfoStruct.cDataBuf[3])
	{
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}
	DIDWriteRamDataComm(GetDatBufAndLen(u8CheckSumDisable));
}

INT8U GetChecksumDisable(void)
{
	return u8CheckSumDisable[0];
}

/***********************************************************************
 * @function name: DescDID_Read_FE01_ConfigParameter
 * 
 * @description: 读取配置字状态
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
 * @date: 2022-03-25 21:01
 ***********************************************************************/
void DescDID_Read_FE01_ConfigParameter(void)
{
	INT8U cDataBuf[40] ={0};
	INT8U index = 0;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_CarType);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_SendTestMsgFlg);
	index ++;

	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrAdjustConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_PaAdjustConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrMemoryConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_PaMemoryConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_MassageConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_RemoteEnableConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_TimeOutPrm);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Heat_RunMaxTime);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Vent_TimeOutPrm);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_Vent_RunMaxTime);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_MotorSoftStopCntMax);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrHeightSoftStopCnt);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrLengthSoftStopCnt);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrBackSoftStopCnt);
	index ++;
	
	cDataBuf[index] = Srvl_GetMemIndexDataU8(EN_MemIndex_DrFrontSoftStopCnt);

	DIDReadRamDataComm(cDataBuf, index);

}

/***********************************************************************
 * @function name: DescDID_Write_FE01_ConfigParameter
 * 
 * @description: 写入配置字
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
 * @date: 2022-03-25 21:11
 ***********************************************************************/
void DescDID_Write_FE01_ConfigParameter(void)
{
	INT8U cDataBuf[40] ={0};
	INT8U index = 0;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_CarType, cDataBuf[index]);
	index ++;
	Srvl_SetMemIndexDataU8(EN_MemIndex_SendTestMsgFlg,cDataBuf[index]);
	index ++;

	Srvl_SetMemIndexDataU8(EN_MemIndex_DrAdjustConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaAdjustConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrVentAndHeatConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrMemoryConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaVentAndHeatConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_PaMemoryConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_MassageConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RemoteEnableConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_PlatformEngineEnableConfig,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_P20_PHEV_EngineCfg,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_TimeOutPrm,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Heat_RunMaxTime,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_TimeOutPrm,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_Vent_RunMaxTime,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_MotorSoftStopCntMax,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrHeightSoftStopCnt,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrLengthSoftStopCnt,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrBackSoftStopCnt,cDataBuf[index]);
	index ++;
	
	Srvl_SetMemIndexDataU8(EN_MemIndex_DrFrontSoftStopCnt,cDataBuf[index]);
}



/***********************************************************************************************
 * @function name:  DescDID_Read_HeatTemp_FE02(void)
 *
 * @description:	读取坐垫温度
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE02_HeatTemp(void)
{
//	INT8U cDataBuf[4] ={0};
//	INT16U temp = 0;
//	//主驾温度
//	temp = Ecual_AdcGetDrNTCTempValue();
//	cDataBuf[0] = (INT8U)(temp >> 8);
//	cDataBuf[1] = (INT8U)(temp >> 0);
//	//副驾温度
//	temp = Ecual_AdcGetPaNTCTempValue();
//	cDataBuf[2] = (INT8U)(temp >> 8);
//	cDataBuf[3] = (INT8U)(temp >> 0);
//	DIDReadRamDataComm(cDataBuf, 4);

}

/***********************************************************************************************
 * @function name:  DescDID_Read_0304_VatAndMode(void)
 *
 * @description:	读取电压及电压模式
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE03_VatAndMode(void)
{
 #if 0 /*20231909*/
	//ECU 电压 RAM
	INT8U  PwrVoltAndModeBuff[3] = {0};
	INT16U Power_Voltage = Ecual_AdcGetChlStatus(EN_Chl_PowerADetect);
	
	enSystemVoltage VccState = Appl_PowerManager_GetPowerSystemVoltSts();
	
	if(Power_Voltage <= 3000UL)  /*如果电源A的电压小于等于3v，则采集电源B的电压*/
	{
		Power_Voltage = Ecual_AdcGetChlStatus(EN_Chl_PowerBDetect);
	}
	PwrVoltAndModeBuff[0] = (Power_Voltage >> 8u) & 0xFFu;
	PwrVoltAndModeBuff[1] = (Power_Voltage ) & 0xFFu;
	PwrVoltAndModeBuff[2] = (INT8U) (VccState & 0xFF);
	DIDReadRamDataComm(PwrVoltAndModeBuff,3);
#endif      
}

/***********************************************************************************************
 * @function name:  DescDID_Read_FE04_OTASts(void)
 *
 * @description:	读取OTA状态
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE04_OTASts(void)
{
    #if 0 /*20231909*/
	//OTA状态
	INT8U  OTASts[1] = {0};
	
	OTASts[0] = Rte_GetVfb_OTABanFlag();
	DIDReadRamDataComm(OTASts,1);
#endif
}

/***********************************************************************************************
 * @function name:  DescDID_Read_FE05_HALLErr(void)
 *
 * @description:	读取霍尔故障、堵转故障
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE05_HALLErr(void)
{
	INT8U  HallStallError[2] = {0};
#if 0	
	//HALL丢失
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_DR_Seat_Height_MotorHALLError) << 7;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_DR_Seat_Length_MotorHALLError) << 6;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_DR_Seat_Backrest_Recline_MotorHALLError) << 5;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_DR_Seat_Cushion_Front_Height_Angle_MotorHALLError) << 4;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_PA_Seat_Height_MotorHALLError) << 3;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_PA_Seat_Length_MotorHALLError) << 2;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_PA_Seat_Backrest_Recline_MotorHALLError) << 1;
	HallStallError[0] |= Diag_ReadDtcTestFailFlag(En_Dtc_PA_Seat_Cushion_Front_Height_Angle_MotorHALLError) << 0;

	/*堵转错误*/
	HallStallError[1] |= Rte_GetVfb_DrHeightLockErr() << 7;
	HallStallError[1] |= Rte_GetVfb_DrLengthLockErr() << 6;
	HallStallError[1] |= Rte_GetVfb_DrBackLockErr() << 5;
	HallStallError[1] |= Rte_GetVfb_DrFrontLockErr() << 4;
	HallStallError[1] |= Rte_GetVfb_PaHeightLockErr() << 3;
	HallStallError[1] |= Rte_GetVfb_PaLengthLockErr() << 2;
	HallStallError[1] |= Rte_GetVfb_PaBackLockErr() << 1;
	HallStallError[1] |= Rte_GetVfb_PaFrontLockErr() << 0;
#endif	
	DIDReadRamDataComm(HallStallError,2);
}
/***********************************************************************************************
 * @function name:  DescDID_Read_FE06_Position(void)
 *
 * @description:	读座椅、后视镜、管柱的3个记忆位置+当前位置
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE06_Position(void)
{
#if 0
  //座椅、后视镜、管柱的3个记忆位置+当前位置
	INT8U  position[112] = {0};
	int i = 0;
	//主驾记忆位置1
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatHeightMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatLengthMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatBackrestMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatFrontMemory1, &position[i], 2);i+=2;

	//主驾记忆位置2
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatHeightMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatLengthMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatBackrestMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatFrontMemory2, &position[i], 2);i+=2;

	//主驾记忆位置3
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatHeightMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatLengthMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatBackrestMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatFrontMemory3, &position[i], 2);i+=2;

	//主驾当前位置
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatHeightPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatLengthPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatBackrestPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatFrontPresent, &position[i], 2);i+=2;

	//主驾小憩回位目标位置
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReCallPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReCallPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReCallPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReCallPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReCallPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReCallPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReCallPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReCallPosi() >> 0);
	//主驾小憩开启目标位置
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReqPosi() >> 0);

	//副驾记忆位置1
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory1, &position[i], 2);i+=2;
	
	//副驾记忆位置2
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory2, &position[i], 2);i+=2;
	
	//副驾记忆位置3
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory3, &position[i], 2);i+=2;
	
	//副驾当前位置
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestPresent, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontPresent, &position[i], 2);i+=2;


#if 0
	//后视镜位置记忆1
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTHORI1STPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTVERT1STPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTHORI1STPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTVERT1STPOSI);i+=1;
	
	//后视镜位置记忆2
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTHORI2NDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTVERT2NDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTHORI2NDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTVERT2NDPOSI);i+=1;
	
	//后视镜位置记忆3
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTHORI3RDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_LEFTVERT3RDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTHORI3RDPOSI);i+=1;
	position[i] = Srvl_GetMemIndexDataU8(D_RIGHTVERT3RDPOSI);i+=1;

	//左后视镜当前位置
	position[i++] = CanRx_0x564_DLF1_N_LmirrorHorizontalPosition();
	position[i++] = CanRx_0x564_DLF1_N_LmirrorVerticalPosition();
	//右后视镜当前位置
	position[i++] = CanRx_0x566_DRF1_N_RmirrorHorizontalPosition();
	position[i++] = CanRx_0x566_DRF1_N_RmirrorVerticalPosition();
	

	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCHeightPosMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCAnglePossMemory1, &position[i], 2);i+=2;
	
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCHeightPosMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCAnglePossMemory2, &position[i], 2);i+=2;
	
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCHeightPosMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_ENSCAnglePossMemory3, &position[i], 2);i+=2;
	
	position[i++] = (INT8U)(b_PCCU_SWH_1_EASC_HeightPos_b() >> 8);
	position[i++] = (INT8U)(b_PCCU_SWH_1_EASC_HeightPos_b() & 0x00FF);
	position[i++] = (INT8U)(b_PCCU_SWH_1_EASC_AnglePos_b() >> 8);
	position[i++] = (INT8U)(b_PCCU_SWH_1_EASC_AnglePos_b() & 0x00FF);
#endif
	DIDReadRamDataComm(position,i);
#endif		
}

/***********************************************************************************************
 * @function name:  DescDID_Read_FE0E_MirrorPosition(void)
 *
 * @description:	读后视镜下翻设定，下翻激活，下翻恢复的位置
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_FE0E_MirrorPosition(void)
{
  #if 0 /*20231909*/
  //
	INT8U i = 0;
	INT8U  pos[24] = {0};
	//右后视镜下翻目标位置
	pos[i++] = Srvl_GetMemIndexDataU8(D_RIGHTDOWNHORI);
	pos[i++] = Srvl_GetMemIndexDataU8(D_RIGHTDOWNVERT);

	//右后视镜下翻恢复位置
	pos[i++] = Srvl_GetMemIndexDataU8(D_RIGHTPREDOWNHORI);
	pos[i++] = Srvl_GetMemIndexDataU8(D_RIGHTPREDOWNVERT);

	//后视镜下翻激活
	pos[i++] = Srvl_GetMemIndexDataU8(D_ACTIVATEDFLAG);
	DIDReadRamDataComm(pos,i);
 #endif       
}


/***********************************************************************************************
 * @function name:  DescDID_Read_FE08_WakeReason(void)
 *
 * @description:	读取唤醒源
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-21
 ***********************************************************************************************/
void DescDID_Read_FE08_WakeReason(void)
{
    #if 0 /*20231909*/
	//唤醒源
	INT8U  tWakeReason[1] = {0};
	
	tWakeReason[0] = Srvl_Pwr_GetWakeReason();
	
	DIDReadRamDataComm(tWakeReason,1);
#endif     
}

/***********************************************************************************************
 * @function name:  DescDID_Read_FE09_PaPosition(void)
 *
 * @description:	读副驾小憩记忆位置+小憩开启后的复位位置+当前位置
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-23
 ***********************************************************************************************/
void DescDID_Read_FE09_PaPosition(void)
{
   #if 0 /*20230919*/ 
	//
	INT8U  pos[24] = {0};
	INT8U i = 0;
	
	
	//副驾小憩记忆位置
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory1,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthMemory1,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestMemory1,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory1,&pos[i],2); i += 2;
	//副驾小憩恢复位置
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory2,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthMemory2,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestMemory2,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory2,&pos[i],2); i += 2;
	//副驾当前位置
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightPresent,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthPresent,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestPresent,&pos[i],2); i += 2;
	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontPresent,&pos[i],2); i += 2;
	
	DIDReadRamDataComm(pos,i);
#endif   
}

/***********************************************************************************************
 * @function name:  DescDID_Read_FE0A_SendTestMsgFlg(void)
 *
 * @description:	读取发送成测报文标志位
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-23
 ***********************************************************************************************/
void DescDID_Read_FE0A_SendTestMsgFlg(void)
{
    #if 1
	INT8U cBuff[1];
	cBuff[0] = Srvl_GetMemIndexDataU8(EN_MemIndex_SendTestMsgFlg);
	DIDReadRamDataComm(cBuff,1);
#endif
}

/***********************************************************************************************
 * @function name:  DescDID_Write_FE0A_SendTestMsgFlg(void)
 *
 * @description:	写入发送成测报文标志位
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-23
 ***********************************************************************************************/
void DescDID_Write_FE0A_SendTestMsgFlg(void)
{
//	INT8U cData[3] = 0;
//	if((3 + 3U) == TpRxInfoStruct.wDataLength)
//	{
//		cData[0] = TpRxInfoStruct.cDataBuf[3];
//		cData[1] = TpRxInfoStruct.cDataBuf[4];//类型
//		cData[2] = TpRxInfoStruct.cDataBuf[5];//时间
//		Srvl_SetMemIndexDataU8(EN_MemIndex_SendTestMsgFlg, cData[0]);    /*20230919*/
//        Srvl_SetTestSendCan(cData[1],cData[2]);
//		TpTxInfoStruct.wDataLength = 3;
//		DescNrc = DescNrcOK;
//	}
//	else
//	{
//		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
//	}
}

/***********************************************************************
 * @function name: DescDID_Read_FE0B_MotorMoveReason
 * 
 * @description: 获取电机动作/停止原因
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
 * @date: 2023-06-25 14:08
 ***********************************************************************/
void DescDID_Read_FE0B_MotorMoveReason(void)
{
    #if 0 /*20230919*/
	INT8U Reason[EN_SeatSwitchMax] = {0};
	INT8U Index = 0;
	
	Reason[EN_DriverHeight] = Rte_GetVfb_DrHeightReason();
	
	Reason[EN_DriverLength] = Rte_GetVfb_DrLengthReason();
	
	Reason[EN_DriverBack] = Rte_GetVfb_DrBackReason();
	
	Reason[EN_DriverFront] = Rte_GetVfb_DrFrontReason();
	
	Reason[EN_PassengerHeight] = Rte_GetVfb_PaHeightReason();
	
	Reason[EN_PassengerLength] = Rte_GetVfb_PaLengthReason();
	
	Reason[EN_PassengerBack] = Rte_GetVfb_PaBackReason();
	
	Reason[EN_PassengerFront] = Rte_GetVfb_PaFrontReason();
	
	DIDReadRamDataComm(Reason,EN_SeatSwitchMax);
#endif     
}

/***********************************************************************
 * @function name: DescDID_Read_FE0C_MotorMoveType
 * 
 * @description: 获取电机动作类型
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
 * @date: 2023-06-25 14:39
 ***********************************************************************/
void DescDID_Read_FE0C_MotorMoveType(void)
{
   #if 0 /*20230919*/ 
	INT8U Type[7] = {0};
	INT8U Index = 0;

	Type[Index] = Rte_GetVfb_MotorType();/*主驾电机*/
	Index ++;
	Type[Index] = Rte_GetVfb_PaMotorType();/*副驾电机*/
	Index ++;
	Type[Index] = Rte_GetVfb_MirrorRunType();/*后视镜*/
	Index ++;
	Type[Index] = Rte_GetVfb_DrVenRunType();/*主驾通风*/
	Index ++;
	Type[Index] = Rte_GetVfb_PaVenRunType();/*副驾通风*/
	Index ++;
	Type[Index] = Rte_GetVfb_DrHeatRunType();/*主驾加热*/
	Index ++;
	Type[Index] = Rte_GetVfb_PaHeatRunType();/*副驾加热*/
	
	DIDReadRamDataComm(Type,Index);
#endif      
}

/***********************************************************************
 * @function name: DescDID_Read_FE0D_MotorLearnInfo
 * 
 * @description: 获取主副驾学习信息
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
 * @date: 2023-06-25 14:53
 ***********************************************************************/
void DescDID_Read_FE0D_MotorLearnInfo(void)
{
  #if 0 /*20230919*/
	INT8U LearnInfo[4] = {0};
	INT8U Index = 0;

	LearnInfo[Index] = Rte_GetVfb_DrLearnEnable();/*主驾学习使能状态*/
	Index ++;
	LearnInfo[Index] = Rte_GetVfb_PaLearnEnable();/*副驾学习使能状态*/
	Index ++;
	LearnInfo[Index] = Rte_GetVfb_DrLearnSts();/*主驾学习步骤及状态*/
	Index ++;
	LearnInfo[Index] = Rte_GetVfb_PaLearnSts();/*副驾学习步骤及状态*/
	
	DIDReadRamDataComm(LearnInfo,Index);
#endif      
}

#if 1
void DescDID_Read_Variable(void)
{
	INT8U cDataBuf[5] = {0x0U}; 
	
	cDataBuf[0] = RamTest1;
	cDataBuf[1] = RamTest2;
	cDataBuf[2] = 0x00;
	cDataBuf[3] = 0x00;
	cDataBuf[4] = 0x00;
	
	DIDReadRamDataComm(cDataBuf, 5);
}

void DescDID_Set_Variable(void)
{
	RamTest1 = TpRxInfoStruct.cDataBuf[3];
	RamTest2 = TpRxInfoStruct.cDataBuf[4];

	TpTxInfoStruct.wDataLength = 3;
	DescNrc = DescNrcOK;
}
#endif



/***********************************************************************
 * @function name: DescDID_Write_FE07_BTS7040Tsk
 * 
 * @description: 写BTS7040配置信息byte0=0：BTS7040     byte0 = 1：BTS7030
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
 * @date: 2023-03-08 14:48
 ***********************************************************************/
void DescDID_Write_FE07_BTS7040Tsk(void)
{
    #if 0 /*20230919*/
	/*超过范围负响应*/
	if((0x0u != TpRxInfoStruct.cDataBuf[3]) && (0x1u != TpRxInfoStruct.cDataBuf[3]))
	{
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}
	if((0x0u != TpRxInfoStruct.cDataBuf[4]) && (0x1u != TpRxInfoStruct.cDataBuf[4]))
	{
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}

	//DIDWriteEepromDataComm(EN_SRV_MemIndex_BTS70X0Config, &TpRxInfoStruct.cDataBuf[3], D_EE_BTS70X0Config_BuffIdxLen);
	
	Srvl_WriteMemIndexData(EN_SRV_MemIndex_BTS70X0Config, &TpRxInfoStruct.cDataBuf[3], D_EE_BTS70X0Config_BuffIdxLen);
	Ecual_AdcSetBTSReadOnceFlag(0);/*adc需要重新读取配置信息*/
	
	TpTxInfoStruct.wDataLength = 3;
	DescNrc = DescNrcOK;
#endif    
}


/***********************************************************************
 * @function name: DescDID_Read_FE07_BTS7040Tsk
 * 
 * @description:读取 BTS7040配置信息
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: byte0=0：BTS7040     byte0 = 1：BTS7030
 * 
 * @author: Prima Niu
 * 
 * @date: 2023-03-08 14:51
 ***********************************************************************/
void DescDID_Read_FE07_BTS7040Tsk(void)
{
#if 0 /*20230919*/
	INT8U u8TempBuff[D_EE_BTS70X0Config_BuffIdxLen]={0};	

	Srvl_ReadMemIndexData(EN_SRV_MemIndex_BTS70X0Config, u8TempBuff, D_EE_BTS70X0Config_BuffIdxLen);

	DIDReadRamDataComm(u8TempBuff, D_EE_BTS70X0Config_BuffIdxLen);
#endif  
}


/***********************************************************************
 * @function name: DescDID_Read_FE0F_HardwareVersionTsk
 * 
 * @description:读取 硬件版本信息
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0 = 未替代Q6版本; 1:替代Q6版本;
 * 
 * @author: Prima Niu
 * 
 * @date: 2023-06-30 14:20
 ***********************************************************************/
void DescDID_Read_FE0F_HardwareVersionTsk(void)
{
  #if 0 /*20230919*/
	INT8U u8TempBuff[1]={0};	

	u8TempBuff[0] = Srvl_GetMemIndexDataU8(D_HARDWAREVERSION);

	DIDReadRamDataComm(u8TempBuff, 1);
#endif   
}


/***********************************************************************
 * @function name: DescDID_Write_FE0F_HardwareVersionTsk
 * 
 * @description:写 硬件版本信息
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0 = 未替代Q6版本; 1:替代Q6版本;
 * 
 * @author: Prima Niu
 * 
 * @date: 2023-07-5 11:33
 ***********************************************************************/
void DescDID_Write_FE0F_HardwareVersionTsk(void)
{
    #if 0 /*20230919*/	/*超过范围负响应*/
	if((0x0u != TpRxInfoStruct.cDataBuf[3]) && (0x1u != TpRxInfoStruct.cDataBuf[3]))
	{
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}

	Srvl_SetMemIndexDataU8(D_HARDWAREVERSION,TpRxInfoStruct.cDataBuf[3]);
	Ecual_AdcSetKL15ReadOnceFlag(0);/*adc需要重新读取配置信息*/

	TpTxInfoStruct.wDataLength = 3;
	DescNrc = DescNrcOK;
#endif    

}

/***********************************************************************
 * @function name: DescDID_Read_FE10_TestMode
 * 
 * @description:读测试模式
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0 = 无测试模式; 1:测试模式;
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-11-13 11:33
 ***********************************************************************/
void DescDID_Read_FE10_TestMode(void)
{
//    INT8U TestMode = 0xFF;
//    INT8U u8TempBuff[1]={0};
//    r_eel_ds_cfg_t *idlTab = Eel_GetEepromIDLTab();
//
//    /* 获取simulink 33块 第7字节数据 ID-52 测试模式 */
//    Ecual_EepRead(idlTab[D_EE_SimulinkUseBuffer0_DataID-6].Addr_u32+7,&TestMode,1);
//
//    u8TempBuff[0] = TestMode;
//
//    DIDReadRamDataComm(u8TempBuff, 1);

}

/***********************************************************************
 * @function name: DescDID_Write_FE0F_HardwareVersionTsk
 * 
 * @description:读 内部boot软件版本信息
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2023-11-02 10:33
 ***********************************************************************/
void DescDID_Read_D000_FZBBootVersion(void)
{
	INT8U i=0;
	INT8U u8TempBuff[D_DareBootVersion_Len_8] = {0};
	Srvl_ReadMemIndexData(EN_MemIndex_DareBootVersion, u8TempBuff, D_DareBootVersion_Len_8);
	for(i = 0; i < D_DareBootVersion_Len_8; i++)
	{
		TpTxInfoStruct.cDataBuf[3U + i] = u8TempBuff[i];
	}

	TpTxInfoStruct.wDataLength = D_DareBootVersion_Len_8 + 3U;
	DescNrc = DescNrcOK;
}

/***********************************************************************
 * @function name: DescDID_Read_FE10_ReadWriteHardwareFlg
 * 
 * @description:读取 允许写硬件版本号标志位
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0 = 不允许写; 1:允许写;
 * 
 * @author: zjx
 * 
 * @date: 2023-11-02 14:20
 ***********************************************************************/
void DescDID_Read_D001_ReadWriteHardwareFlg(void)
{
	INT8U u8TempBuff[1]={0};	

	u8TempBuff[0] = Srvl_GetMemIndexDataU8(EN_MemIndex_Write_HardwareVersion_Flg);

	DIDReadRamDataComm(u8TempBuff, 1);

}

/***********************************************************************
 * @function name: DescDID_Write_FE10_ReadWriteHardwareFlg
 * 
 * @description:写 允许写硬件版本号标志位
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0 = 不允许写; 1:允许写;
 * 
 * @author: zjx
 * 
 * @date: 2023-11-02 14:20
 ***********************************************************************/
void DescDID_Write_D001_ReadWriteHardwareFlg(void)
{

	INT8U cData = 0;
	if((1 + 3U) == TpRxInfoStruct.wDataLength)
	{	
		cData = TpRxInfoStruct.cDataBuf[3];
		Srvl_SetMemIndexDataU8(EN_MemIndex_Write_HardwareVersion_Flg, cData);
		TpTxInfoStruct.wDataLength = 3;
		DescNrc = DescNrcOK;
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
	}

	

}

/***********************************************************************
 * @function name: DescDID_Read_D003_ReadWritePCBASN
 * 
 * @description: 读PCBASN
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note:  
 * 
 * @author: zjx
 * 
 * @date: 2023-11-29 11:20
 ***********************************************************************/
void DescDID_Read_D003_ReadWritePCBASN(void)
{
	INT8U cDataBuf[D_PCBASerialNumber_Len_21] ={0};
	
	Srvl_ReadMemIndexData(EN_MemIndex_PCBASerialNumber, cDataBuf, D_PCBASerialNumber_Len_21);
	
	DIDReadRamDataComm(cDataBuf, D_PCBASerialNumber_Len_21);

}

/***********************************************************************
 * @function name: DescDID_Write_FE10_ReadWriteHardwareFlg
 * 
 * @description: 写PCBASN
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2023-11-29 11:20
 ***********************************************************************/
void DescDID_Write_D003_ReadWritePCBASN(void)
{
	INT8U* PcData = (INT8U*)&TpRxInfoStruct.cDataBuf[3];                                               
	if((3 + D_PCBASerialNumber_Len_21) == TpRxInfoStruct.wDataLength)
	{	
		DIDWriteEepromDataComm(EN_MemIndex_PCBASerialNumber, PcData, D_PCBASerialNumber_Len_21);
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
	}
}


/***********************************************************************
 * @function name: DescDID_Read_D003_ReadTestMessageSendCfg
 * 
 * @description: 读测试报文发送配置
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note:  
 * 
 * @author: zjx
 * 
 * @date: 2024-04-15 14:39
 ***********************************************************************/
void DescDID_Read_D004_TestMessageSendCfg(void)
{
	INT8U cDataBuf[1] ={0};

	Srvl_ReadMemIndexData(EN_MemIndex_TestMessageSendCfg, cDataBuf, D_TestMessageSendCfg_Len_1);

	DIDReadRamDataComm(cDataBuf, D_TestMessageSendCfg_Len_1);

}

/***********************************************************************
 * @function name: DescDID_Write_FE10_ReadWriteHardwareFlg
 * 
 * @description: 写测试报文发送配置
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-15 14:39
 ***********************************************************************/
void DescDID_Write_D004_TestMessageSendCfg(void)
{
	INT8U* PcData = (INT8U*)&TpRxInfoStruct.cDataBuf[3];
	if((3 + D_TestMessageSendCfg_Len_1) == TpRxInfoStruct.wDataLength)
	{
		DIDWriteEepromDataComm(EN_MemIndex_TestMessageSendCfg, PcData, D_TestMessageSendCfg_Len_1);
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
	}
}

/***********************************************************************
 * @function name: DescDID_Write_D005_HeatGearTemp
 * 
 * @description: 设置加热档位温度
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Write_D005_HeatGearTemp(void)
{
//	INT8U* PcData = (INT8U*)&TpRxInfoStruct.cDataBuf[3];
//	INT16U t_temp = 0;
//	INT8U i = 0;
//#if(D_CalibrateHeat == ENABLE)
//
//	if((3 + (2 * EN_HeatGear_MAX)) == TpRxInfoStruct.wDataLength)
//	{
//		for(i = 0; i < EN_HeatGear_MAX; i++)
//		{
//			t_temp = ((INT16U)PcData[ 2 * i ]) << 8;
//			t_temp += (INT16U)PcData[ 2 * i + 1 ];
//			if(FALSE == Ecual_setSeatHeatGearTemp((en_SeatHeatGear)i, t_temp))
//			{
//				DescNrc = kDescNrcRequestOutOfRange;
//				return;
//			}
//		}
//		DescNrc = DescNrcOK;
//	}
//	else
//	{
//		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
//	}
//#else
//	DescNrc = kDescNrcRequestOutOfRange;
//#endif
}


/***********************************************************************
 * @function name: DescDID_Write_D005_HeatGearTemp
 * 
 * @description: 读取加热档位温度
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D005_HeatGearTemp(void)
{
//	INT8U cDataBuf[EN_HeatGear_MAX] ={0};
//	INT16U t_temp = 0;
//	INT8U i = 0;
//
//#if(D_CalibrateHeat == ENABLE)
//	for(i = 0; i < EN_HeatGear_MAX; i++)
//	{
//		t_temp = Ecual_getSeatHeatGearTemp((en_SeatHeatGear)i );
//
//		cDataBuf[2 * i] =(INT8U)(t_temp >> 8);
//		cDataBuf[2 * i + 1] =(INT8U)(t_temp >> 0);
//
//	}
//
//	DIDReadRamDataComm(cDataBuf, (2 * EN_HeatGear_MAX) );
//
//#else
//		DescNrc = kDescNrcRequestOutOfRange;
//#endif

}

/***********************************************************************
 * @function name: DescDID_Read_D006_DrMotorPositionInfo
 * 
 * @description: 主驾相关的电机坐标
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
 * @date: 2023-06-25 14:53
 ***********************************************************************/
void DescDID_Read_D006_DrMotorPositionInfo(void)
{
	INT8U  position[100] = {0};
	int i = 0;

	//主驾记忆位置1 		  EN_MemIndex_DrMem1_Height
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem1_Height, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem1_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem1_Back, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem1_Front, &position[i], 2);i+=2;

	//主驾记忆位置2
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem2_Height, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem2_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem2_Back, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem2_Front, &position[i], 2);i+=2;

	//主驾记忆位置3
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem3_Height, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem3_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem3_Back, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrMem3_Front, &position[i], 2);i+=2;

	//主驾当前位置
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatHeightPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatLengthPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatBackrestPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_DRSeatFrontPresent, &position[i], 2);i+=2;
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverHeight) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverHeight);
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverLength) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverLength);
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverBack) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverBack);
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverFront) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_DriverFront);

	//主驾小憩回位目标位置	  EN_MemIndex_DrRes_ReCallPosi_Height
	Srvl_ReadMemIndexData(EN_MemIndex_DrRes_ReCallPosi_Height, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrRes_ReCallPosi_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrRes_ReCallPosi_Back, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_DrRes_ReCallPosi_Front, &position[i], 2);i+=2;
	//主驾小憩开启目标位置
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResHeightReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResLengthReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResBackReqPosi() >> 0);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReqPosi() >> 8);
	position[i++] = (INT8U)(Rte_GetVfb_DrResFrontReqPosi() >> 0);

	//主驾硬止点信息
	position[i++] = Cdd_GetMotorHardStop(EN_DriverHeight) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_DriverHeight);
	position[i++] = Cdd_GetMotorHardStop(EN_DriverLength) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_DriverLength);
	position[i++] = Cdd_GetMotorHardStop(EN_DriverBack) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_DriverBack);
	position[i++] = Cdd_GetMotorHardStop(EN_DriverFront) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_DriverFront);

	//主驾导轨长度信息
	position[i++] = Cdd_GetMotorSize(EN_DriverHeight) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_DriverHeight);
	position[i++] = Cdd_GetMotorSize(EN_DriverLength) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_DriverLength);
	position[i++] = Cdd_GetMotorSize(EN_DriverBack) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_DriverBack);
	position[i++] = Cdd_GetMotorSize(EN_DriverFront) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_DriverFront);

	DIDReadRamDataComm(position,i);
}
/***********************************************************************************************
 * @function name:  DescDID_Write_D006_DrMotorPositionInfo(void)
 *
 * @description:	写入主驾硬止点信息
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-05-23
 ***********************************************************************************************/
void DescDID_Write_D006_DrMotorPositionInfo(void)
{
    INT8U i;
    INT16U GetData;
    if((8 + 3U) == TpRxInfoStruct.wDataLength)
    {
        for(i = 0;i < 4;i++)
        {
            GetData = TpRxInfoStruct.cDataBuf[3+i*2];
            GetData <<= 8;
            GetData += TpRxInfoStruct.cDataBuf[3+i*2 + 1];

//			Ecual_AdcSetReadStopPosi(0);
            Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height + i,GetData);
        }

        TpTxInfoStruct.wDataLength = 3;
        DescNrc = DescNrcOK;
    }
    else
    {
        DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
    }
}

/***********************************************************************************************
 * @function name:  DescDID_Read_D007_PaMotorPositionInfo(void)
 *
 * @description:	副驾电机相关坐标
 *
 * @input parameters:     void
 *
 * @output parameters:     void
 *
 * @return:         无
 *
 * @note:           无
 *
 * @author:          zjx
 *
 * @note:           2023-04-20
 ***********************************************************************************************/
void DescDID_Read_D007_PaMotorPositionInfo(void)
{
	INT8U  position[50] = {0};
	int i = 0;
	//副驾记忆位置1
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory1, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem1_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem1_Back, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory1, &position[i], 2);i+=2;

	//副驾记忆位置2
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory2, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem2_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem2_Back, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory2, &position[i], 2);i+=2;

	//副驾记忆位置3
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightMemory3, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem3_Length, &position[i], 2);i+=2;
	Srvl_ReadMemIndexData(EN_MemIndex_PaMem3_Back, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontMemory3, &position[i], 2);i+=2;

	//副驾当前位置
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatHeightPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatLengthPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatBackrestPresent, &position[i], 2);i+=2;
//	Srvl_ReadMemIndexData(EN_SRV_MemIndex_PASeatFrontPresent, &position[i], 2);i+=2;
	position[i++] = Cdd_GetCurrentHallCnt(EN_PassengerLength) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_PassengerLength);
	position[i++] = Cdd_GetCurrentHallCnt(EN_PassengerBack) >> 8;
	position[i++] = Cdd_GetCurrentHallCnt(EN_PassengerBack);

	//主驾硬止点信息
//	position[i++] = Cdd_GetMotorHardStop(EN_PaResever_1) >> 8;
//	position[i++] = Cdd_GetMotorHardStop(EN_PaResever_1);
	position[i++] = Cdd_GetMotorHardStop(EN_PassengerLength) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_PassengerLength);
	position[i++] = Cdd_GetMotorHardStop(EN_PassengerBack) >> 8;
	position[i++] = Cdd_GetMotorHardStop(EN_PassengerBack);
//	position[i++] = Cdd_GetMotorHardStop(EN_PaResever_2) >> 8;
//	position[i++] = Cdd_GetMotorHardStop(EN_PaResever_2);

	//主驾导轨长度信息
//	position[i++] = Cdd_GetMotorSize(EN_PaResever_1) >> 8;
//	position[i++] = Cdd_GetMotorSize(EN_PaResever_1);
	position[i++] = Cdd_GetMotorSize(EN_PassengerLength) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_PassengerLength);
	position[i++] = Cdd_GetMotorSize(EN_PassengerBack) >> 8;
	position[i++] = Cdd_GetMotorSize(EN_PassengerBack);
//	position[i++] = Cdd_GetMotorSize(EN_PaResever_2) >> 8;
//	position[i++] = Cdd_GetMotorSize(EN_PaResever_2);
	DIDReadRamDataComm(position,i);
}
/***********************************************************************
 * @function name: DescDID_Read_D008_MassageTimeInfo
 * 
 * @description: 按摩时间、次数参数
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
 * @date: 2024-05-23 20:11
 ***********************************************************************/
void DescDID_Read_D008_MassageTimeInfo(void)
{
	INT16U u16TempBuff;
	INT8U u8TempBuff[17]={0};

	u16TempBuff = Rte_GetVfb_Debug_Mas_T1_Threshold();
	u8TempBuff[0] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[1] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T2_Threshold();
	u8TempBuff[2] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[3] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T3_Threshold();
	u8TempBuff[4] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[5] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T4_Threshold();
	u8TempBuff[6] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[7] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T1timer();
	u8TempBuff[8] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[9] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T2timer();
	u8TempBuff[10] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[11] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T3timer();
	u8TempBuff[12] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[13] = (INT8U)(u16TempBuff >> 0 & 0xFF);

	u16TempBuff = Rte_GetVfb_Debug_Mas_T4timer();
	u8TempBuff[14] = (INT8U)(u16TempBuff >> 8 & 0xFF);
	u8TempBuff[15] = (INT8U)(u16TempBuff >> 0 & 0xFF);
	
	u8TempBuff[16] = Rte_GetVfb_Debug_Mas_ActCount();

	DIDReadRamDataComm(u8TempBuff, 17);
}


/***********************************************************************
 * @function name: DescDID_Write_D008_MassageTimeInfo
 * 
 * @description: 配置按摩定时器时长，单位:s
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 0xFF默认配置T1=2sbT2=10sbT3=30sbT4=150s
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-05-28 17:10
 ***********************************************************************/
void DescDID_Write_D008_MassageTimeInfo(void)
{
	if((0x0u == TpRxInfoStruct.cDataBuf[3]) 
		|| (0x0u == TpRxInfoStruct.cDataBuf[4]) 
		|| (0x0u == TpRxInfoStruct.cDataBuf[5]) 
		|| (0x0u == TpRxInfoStruct.cDataBuf[6]))
	{
		/*0:无效*/
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}
	
	if((0xFFu == TpRxInfoStruct.cDataBuf[3]) 
		&& (0xFFu == TpRxInfoStruct.cDataBuf[4]) 
		&& (0xFFu == TpRxInfoStruct.cDataBuf[5]) 
		&& (0xFFu == TpRxInfoStruct.cDataBuf[6]))
	{
		/*0xFF默认配置*/
		Rte_SetVfb_Debug_Mas_T1_Threshold(2);
		Rte_SetVfb_Debug_Mas_T2_Threshold(10);
		Rte_SetVfb_Debug_Mas_T3_Threshold(30);
		Rte_SetVfb_Debug_Mas_T4_Threshold(150);
	}
	else
	{
		s_u8MassageTime[0] = TpRxInfoStruct.cDataBuf[3];
		s_u8MassageTime[1] = TpRxInfoStruct.cDataBuf[4];
		s_u8MassageTime[2] = TpRxInfoStruct.cDataBuf[5];
		s_u8MassageTime[3] = TpRxInfoStruct.cDataBuf[6];
		
		Rte_SetVfb_Debug_Mas_T1_Threshold(s_u8MassageTime[0]);
		Rte_SetVfb_Debug_Mas_T2_Threshold(s_u8MassageTime[1]);
		Rte_SetVfb_Debug_Mas_T3_Threshold(s_u8MassageTime[2]);
		Rte_SetVfb_Debug_Mas_T4_Threshold(s_u8MassageTime[3]);
	}
	DIDWriteRamDataComm(GetDatBufAndLen(s_u8MassageTime));

}

/***********************************************************************
 * @function name: GetMassageDiagTime
 * 
 * @description: 获取诊断配置的按摩时间，单位：s
 * 
 * @input parameters: index=0:T1; 1:T2; 2:T3; 3:T4; 4:ACT
 * 
 * @output parameters: 按摩时间
 * 
 * @return: 按摩T1~T4定时器时间
 * 
 * @note: 仅供按摩模型使用
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-05-28 17:24
 ***********************************************************************/
void DescDID_Write_D00B_VentGearPrecent(void)
{
	INT8U* PcData = (INT8U*)&TpRxInfoStruct.cDataBuf[3];
	INT8U t_temp = 0;
	INT8U i = 0;

//#if(D_Calibrate == D_ENABLE)
//	if((3 + 3) == TpRxInfoStruct.wDataLength)
//	{
//		for(i = 0; i < 3; i++)
//		{
//			t_temp = PcData[i];
//			if(FALSE == Ecual_setSeatVentGearPrecent(i, t_temp))
//			{
//				DescNrc = kDescNrcRequestOutOfRange;
//				return;
//			}
//		}
//		DescNrc = DescNrcOK;
//	}
//	else
//	{
//		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
//	}
//#else
//	DescNrc = kDescNrcRequestOutOfRange;
//#endif
}


INT8U GetMassageDiagTime(INT8U Index)
{
	return s_u8MassageTime[Index];
}

/***********************************************************************
 * @function name: DescDID_Read_D009_MassageACTInfo
 * 
 * @description: 获取按摩ACT次数
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 待更新
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-05-28 18:12
 ***********************************************************************/
void DescDID_Read_D009_MassageACTInfo(void)
{
	INT8U TempInfo[1] = {0};
	INT8U Index = 0;
	INT8U ACTInfo = 0x0U;
	
	ACTInfo = Rte_GetVfb_Debug_Mas_ActCount();

	TempInfo[Index] = ACTInfo;
	Index ++;

	DIDReadRamDataComm(TempInfo,Index);
}

/***********************************************************************
 * @function name: DescDID_Read_D00A_VoltageInfo
 * 
 * @description: 获取电压及电压模式
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
电压:单位mV,
电压模式
0 : StopVolt
1 : LowVolt
2 : NormalVolt
3 : HighVolt
4 : OverVolt
 * 
 * @author: Prima Niu
 * 
 * @date: 2024-05-23 20:02
 ***********************************************************************/
void DescDID_Read_D00A_VoltageInfo(void)
{
	INT8U VoltaeInfo[3] = {0};
	INT8U Index = 0;
	INT16U Voltage = 0x0U;
	
	Voltage = Srvl_Get_SupplyVoltage();

	VoltaeInfo[Index] = (INT8U)(Voltage >> 8);
	Index ++;
	VoltaeInfo[Index] = (INT8U)Voltage;
	Index ++;
	VoltaeInfo[Index] = Rte_GetVfb_VoltMode();
	Index ++;

	DIDReadRamDataComm(VoltaeInfo,Index);
}

/***********************************************************************
 * @function name: DescDID_Write_D00A_VentGearPrecent
 * 
 * @description: 设置通风档位占空比
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-05-20 13:34
 ***********************************************************************/
/***********************************************************************
 * @function name: DescDID_Read_D00A_VentGearPrecent
 * 
 * @description: 读取通风档位占空比
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-05-20 13:37
 ***********************************************************************/
void DescDID_Read_D00B_VentGearPrecent(void)
{
	INT8U cDataBuf[3] ={0}; 
	INT16U t_temp = 0;
	INT8U i = 0;
	
#if(D_Calibrate == D_ENABLE)
	for(i = 0; i < 3; i++)
	{
//		t_temp = Ecual_getSeatVentGearPrecent(i);
		
		cDataBuf[i] = t_temp;
		
	}
		
	DIDReadRamDataComm(cDataBuf, 3);
	
#else
	DescNrc = kDescNrcRequestOutOfRange;
#endif
}

/***********************************************************************
 * @function name: DescDID_Write_D00C_SteerHeatTemp
 * 
 * @description: 设置方向盘加热温度
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Write_D00C_SteerHeatTemp(void)
{
	INT8U* PcData = (INT8U*)&TpRxInfoStruct.cDataBuf[3];   
	INT16U t_temp = 0;
	INT8U i = 0;
	
#if(D_Calibrate == D_ENABLE)
	if((3 + 2) == TpRxInfoStruct.wDataLength)
	{	
		t_temp = ((INT16U)PcData[0]) << 8;
		t_temp += (INT16U)PcData[1];
//		if(FALSE == Ecual_setSteerHeatTemp(t_temp))
//		{
//			DescNrc = kDescNrcRequestOutOfRange;
//			return;
//
//		}
		DescNrc = DescNrcOK;
	}
	else
	{
		DescNrc =  kDescNrcIncorrectMessageLengthOrInvalidFormat;
	}
#else
	DescNrc = kDescNrcRequestOutOfRange;
#endif
}


/***********************************************************************
 * @function name: DescDID_Read_D00C_SteerHeatTemp
 * 
 * @description: 读取方向盘加热温度
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D00C_SteerHeatTemp(void)
{
	INT8U cDataBuf[2] ={0}; 
	INT16U t_temp = 0;
	INT8U i = 0;
	
#if(D_Calibrate == D_ENABLE)
//	t_temp = Ecual_getSteerHeatTemp();
	
	cDataBuf[0] =(INT8U)(t_temp >> 8);
	cDataBuf[1] =(INT8U)(t_temp >> 0);

		
	DIDReadRamDataComm(cDataBuf, 2);
	
#else
	DescNrc = kDescNrcRequestOutOfRange;
#endif
}
/***********************************************************************
 * @function name: DescDID_Read_D00D_DrMotorReason
 * 
 * @description: 读取主驾运动类型
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D00D_DrMotorReason(void)
{
    INT8U cDataBuf[11] ={0}; 

    cDataBuf[0] = Rte_GetVfb_DrHeightMotorReason();
    cDataBuf[1] = Rte_GetVfb_DrLengthMotorReason();
    cDataBuf[2] = Rte_GetVfb_DrBackMotorReason();
    cDataBuf[3] = Rte_GetVfb_DrFrontMotorReason();
//    cDataBuf[4] = Rte_GetVfb_CurrMotorCtrlType();
    cDataBuf[5] = Rte_GetVfb_DrMoveType();
    cDataBuf[6] = Rte_GetVfb_DrWelcomeRunSts();
    cDataBuf[7] = Rte_GetVfb_DrWelcomeStopReason();
    cDataBuf[8] = Rte_GetVfb_MemSetStopReason();
    cDataBuf[9] = Rte_GetVfb_MemCallStopReason();
    cDataBuf[10] = Rte_GetVfb_PreMemRemindStop();

		
	DIDReadRamDataComm(cDataBuf, 11);
}

/***********************************************************************
 * @function name: DescDID_Read_D00E_PaMotorReason
 * 
 * @description: 读取副驾运动类型
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D00E_PaMotorReason(void)
{
    INT8U cDataBuf[14] ={0}; 

    cDataBuf[0] = Rte_GetVfb_PaHeightMotorReason();
    cDataBuf[1] = Rte_GetVfb_PaLengthMotorReason();
    cDataBuf[2] = Rte_GetVfb_PaBackMotorReason();
    cDataBuf[3] = Rte_GetVfb_PaFrontMotorReason();
//    cDataBuf[4] = Rte_GetVfb_PaCurrMotorCtrlType();
    cDataBuf[5] = Rte_GetVfb_PaMoveType();
    cDataBuf[6] = Rte_GetVfb_PaWelcomeRunSts();
    cDataBuf[7] = Rte_GetVfb_PaWelcomeStopReason();
    cDataBuf[8] = Rte_GetVfb_PaMemSetStopReason();
    cDataBuf[9] = Rte_GetVfb_PaMemCallStopReason();
    cDataBuf[10] = Rte_GetVfb_PaPreMemRemindStop();
//    cDataBuf[11] = Rte_GetVfb_PaLengthStopMoveCause();
//    cDataBuf[12] = Rte_GetVfb_PaBackStopMoveCause();
//    cDataBuf[13] = Rte_GetVfb_PaFrontStopMoveCause();

	DIDReadRamDataComm(cDataBuf, 14);
}

/***********************************************************************
 * @function name: DescDID_Read_D00F_VentHeatReason
 * 
 * @description: 读取通风加热类型
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D00F_VentHeatReason(void)
{
    INT8U cDataBuf[9] ={0}; 

    cDataBuf[0] = Rte_GetVfb_DrVentStopReason();
    cDataBuf[1] = Rte_GetVfb_PaVentStopReason();
    cDataBuf[2] = Rte_GetVfb_ThirdVentStopReason();
    cDataBuf[3] = Rte_GetVfb_CANDrHeatStopReason();
    cDataBuf[4] = Rte_GetVfb_CANPaHeatStopReason();
    cDataBuf[5] = Rte_GetVfb_CANThirdHeatStopReason();
    cDataBuf[6] = Rte_GetVfb_CANDrVentStopReason();
    cDataBuf[7] = Rte_GetVfb_CANPaVentStopReason();
    cDataBuf[8] = Rte_GetVfb_CANThirdVentStopReason();

	DIDReadRamDataComm(cDataBuf, 9);
}

/***********************************************************************
 * @function name: DescDID_Read_D010_SoftStopFlg
 * 
 * @description: 读取主副驾软止点故障
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 
 * 
 * @author: zjx
 * 
 * @date: 2024-04-16 9:39
 ***********************************************************************/
void DescDID_Read_D010_SoftStopFlg(void)
{
    INT8U cDataBuf[8] ={0}; 

    cDataBuf[0] = Rte_GetVfb_PaHeightSoftStopErr();
    cDataBuf[1] = Rte_GetVfb_PaLengthSoftStopErr();
    cDataBuf[2] = Rte_GetVfb_PaBackSoftStopErr();
    cDataBuf[3] = Rte_GetVfb_PaFrontSoftStopErr();
    cDataBuf[4] = Rte_GetVfb_DrHeightSoftStopErr();
    cDataBuf[5] = Rte_GetVfb_DrLengthSoftStopErr();
    cDataBuf[6] = Rte_GetVfb_DrBackSoftStopErr();
    cDataBuf[7] = Rte_GetVfb_DrFrontSoftStopErr();

	DIDReadRamDataComm(cDataBuf, 8);
}

/***********************************************************************
 * @function name: DescDID_Read_D011_MotorPaStopInfo
 * 
 * @description: 获取副驾硬止点信息
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
 * @date: 2023-06-25 14:53
 ***********************************************************************/
void DescDID_Read_D011_MotorPaStopInfo(void)
{
  #if 1
	INT8U LearnInfo[8] = {0};
	INT8U Index = 0;

	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PaResever_1) >> 8;
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PaResever_1);
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PassengerLength) >> 8;
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PassengerLength);
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PassengerBack) >> 8;
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PassengerBack);
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PaResever_2) >> 8;
	Index ++;
	LearnInfo[Index] = Cdd_GetMotorHardStop(EN_PaResever_2);
	Index ++;

	DIDReadRamDataComm(LearnInfo,Index);
#endif      
}

/***********************************************************************
 * @function name: DescDID_Read_D014_SwHeatMaxTimeInfo
 * 
 * @description: 获取方向盘加热时长阈值
 * 
 * @input parameters: 无
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 单位s，0xFF:默认时长20min
 * 
 * @author: Prima Niu
 * 
 * @date: 2021-08-15 18:08
 ***********************************************************************/
void DescDID_Read_D014_SwHeatMaxTimeInfo(void)
{
	INT8U Maxtime = 0x0U;
    INT8U cDataBuf[1] = {0}; 


	Maxtime = Rte_GetVfb_SwHeatMaxTime();
	if(0x0U == Maxtime)
	{
		cDataBuf[0] = 0xFF;/*默认2min*/
	}
	else
	{
		cDataBuf[0] = Maxtime;/*单位:s*/
	}
	
	DIDReadRamDataComm(cDataBuf, 1);
}

/***********************************************************************
 * @function name: DescDID_Write_D014_SwHeatMaxTimeInfo
 * 
 * @description: 设置方向盘加热时长
 * 
 * @input parameters: 
 * 
 * @output parameters: 
 * 
 * @return: 
 * 
 * @note: 单位:s,0无效
 * 
 * @author: Prima Niu
 * 
 * @date: 2021-08-15 18:10
 ***********************************************************************/
void DescDID_Write_D014_SwHeatMaxTimeInfo(void)
{
	if(0x0u == TpRxInfoStruct.cDataBuf[3])
	{
		/*0:无效*/
		DescNrc = kDescNrcRequestOutOfRange;
		return;
	}
	else
	{
		Rte_SetVfb_SwHeatMaxTime(TpRxInfoStruct.cDataBuf[3]);
		DescNrc = DescNrcOK;
	}

}



/***********************************************************************
 * @function name: DescDID_Read_D015_BoardTemp
 * 
 * @description: 获取板上温度
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
 * @date: 2024-09-05 14:38
 ***********************************************************************/
void DescDID_Read_D015_BoardTemp(void)
{
	INT8U u8TempBuff[2] = {0};
	INT16U u16Temp = 0x0U;

	u16Temp = Ecual_ADC_GetCurrentBoardTemp();
	u8TempBuff[0] = (INT8U)(u16Temp >> 8U);
	u8TempBuff[1] = (INT8U)(u16Temp);
	
	DIDReadRamDataComm(u8TempBuff,2);
}


/***********************************************************************
 * @function name: DescDID_Read_D016_WelcomePosi
 * 
 * @description: 迎宾观测相关
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
 * @date: 2024-09-05 14:58
 ***********************************************************************/
void DescDID_Read_D016_WelcomePosi(void)
{
	INT8U u8TempBuff[16] = {0};
	INT16U u16TempPosi = 0x0U;
	/*主驾*/
	u16TempPosi = Srvl_GetMemIndexDataU16(EN_MemIndex_DrWelcome_LenTar_ForWard);
	u8TempBuff[0] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[1] = (INT8U)(u16TempPosi);
	
	u16TempPosi = Srvl_GetMemIndexDataU16(EN_MemIndex_DrWelcome_LenTar_BackWard);
	u8TempBuff[2] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[3] = (INT8U)(u16TempPosi);

	u16TempPosi = Rte_GetVfb_DrWelLengthReqPosi();
	u8TempBuff[4] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[5] = (INT8U)(u16TempPosi);

	u8TempBuff[6] = Rte_GetVfb_DrWelcomeRunSts();
    u8TempBuff[7] = Rte_GetVfb_DrWelcomeStopReason();
	/*副驾*/	
	u16TempPosi = Srvl_GetMemIndexDataU16(EN_MemIndex_PaWelcome_LenTar_ForWard);
	u8TempBuff[8] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[9] = (INT8U)(u16TempPosi);
	
	u16TempPosi = Srvl_GetMemIndexDataU16(EN_MemIndex_PaWelcome_LenTar_BackWard);
	u8TempBuff[10] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[11] = (INT8U)(u16TempPosi);

	u16TempPosi = Rte_GetVfb_PaWelLengthReqPosi();
	u8TempBuff[12] = (INT8U)(u16TempPosi >> 8U);
	u8TempBuff[13] = (INT8U)(u16TempPosi);

	u8TempBuff[14] = Rte_GetVfb_PaWelcomeRunSts();
    u8TempBuff[15] = Rte_GetVfb_PaWelcomeStopReason();
	
	DIDReadRamDataComm(u8TempBuff,16);
}

/***********************************************************************
 * @function name: DescDID_Read_D013_SwHeatTimeInfo
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
 * @date: 2021-08-15 18:12
 ***********************************************************************/
void DescDID_Read_D013_SwHeatTimeInfo(void)
{
    INT8U cDataBuf[8] = {0}; 
	INT32U Timer = 0x0U;

	Timer = DiagGetSwHeatTimer();
    cDataBuf[0] = (INT8U)(Timer >> 24U); 
    cDataBuf[1] = (INT8U)(Timer >> 16U);
    cDataBuf[2] = (INT8U)(Timer >> 8U);
    cDataBuf[3] = (INT8U)(Timer >> 0U);
    
//	Timer = D_HAL_GET_CUR_MS_TS();
    cDataBuf[4] = (INT8U)(Timer >> 24U); 
    cDataBuf[5] = (INT8U)(Timer >> 16U);
    cDataBuf[6] = (INT8U)(Timer >> 8U);
    cDataBuf[7] = (INT8U)(Timer >> 0U);
	DIDReadRamDataComm(cDataBuf, 8);
}
/***********************************************************************
 * @function name: DescDID_TEST_SetC4
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_TEST_SetC4(INT8U Command)
{
	SetCanTestCommand(Command);
//	TpTxInfoStruct.wDataLength = 3;
//	DescNrc = DescNrcOK;
}
/***********************************************************************
 * @function name: DescDID_C400_TEST_AD_LOOP
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_C400_TEST_AD_LOOP(void)
{
	DescDID_TEST_SetC4(TEST_AD_LOOP);
	SetCanTestParameter(0);
}
/***********************************************************************
 * @function name: DescDID_C401_TEST_AD_SINGLE
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_C401_TEST_AD_SINGLE(void)
{
	DescDID_TEST_SetC4(TEST_AD_SINGLE);
	SetCanTestParameter(TpRxInfoStruct.cDataBuf[3]);
}
/***********************************************************************
 * @function name: DescDID_C402_TEST_VAR_DATA
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_C402_TEST_VAR_DATA(void)
{
	DescDID_TEST_SetC4(TEST_VAR_DATA);
}
/***********************************************************************
 * @function name: DescDID_C403_TEST_9210X
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_C403_TEST_9210X(void)
{
	DescDID_TEST_SetC4(TEST_9210X_DATA);
	SetCanTestParameter(TpRxInfoStruct.cDataBuf[3]);
}
/***********************************************************************
 * @function name: DescDID_TEST_C4FF
 * @description: 测试命令
 * @author: 2024/8/27 SSJ
 * @date:
 ***********************************************************************/
void DescDID_TEST_C4FF(void)
{
	DescDID_TEST_SetC4(0xFF);
}
/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

