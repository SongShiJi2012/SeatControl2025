/*
 * Cdd_Hall.c
 *
 *  Created on: 2025-3-18
 *      Author: Administrator
 */
#include "Cdd_Hall.h"
#include "CpuPeripheralInit.h"
#include "Srvl_E2memory.h"
#include "Ecual_Adc.h"
#include "stdlib.h"
#include "Test.h"
#include "DescRoutineCtlList.h"
#include "Srvl_PowerMode.h"
#include "Rte_VfbInterface.h"
#include "MidRelay.h"
#include "adc_driver.h"

extern INT32U Dma0_Adc0_Buf[D_ADC0_CONTINUOUS_CHANNEL_NUM];//霍尔数据不复制到原接口 直接在中断处理

typedef struct
{
	EN_MOTOR_MOVE LastCmd;
	INT32U DelayedCollectionTimer;
} HALL_CMD_STATE_T;
static INT16U s_HallDiffValue = 400;   		 /*Hall信号差值*/
INT8U HallState[EN_SeatSwitchMax] = {0};			 //霍尔波形状态 1-上升沿中   2-下降沿中
strHALLERR HallErr;
static BOOL s_HallAllStopFlag = TRUE;  // 所有霍尔通道是否全部停止采集标志，TRUE 表示已全部停止

/*霍尔通道记录的上一次数据*/
strADCHALLDATA HallDataHandle =
{
	{30000,30000,30000,30000,30000,30000}, //当前记录的PWM数、位置相关
	{1044,1047,3672,448,1045,3354},  //电机导轨长度PWM数
	{30000,30000,30000,30000,30000,30000},  //电机的硬止点位置（下、后、靠后）
	{30000,30000,30000,30000,30000,30000},  //上一次电机的硬止点位置（下、后、靠后）
};
static void Cdd_HallAcquire(INT8U i, INT16U HallCurVal, EN_MOTOR_MOVE MotorCmd, BOOL StallErrFlag);
static void Cdd_HallStoreAll(void);
static void Cdd_HallCounterUpdata(INT8U i);
/*获取座椅调节状态*/
static const MotorFun s_MotorCmdFunc[EN_SeatSwitchMax] =
{
	Rte_GetVfb_DrHeightMotorCmd,
	Rte_GetVfb_DrLengthMotorCmd,
	Rte_GetVfb_DrBackMotorCmd,
	Rte_GetVfb_DrFrontMotorCmd,
//	Rte_GetVfb_PaHeightMotorCmd,
	Rte_GetVfb_PaLengthMotorCmd,
	Rte_GetVfb_PaBackMotorCmd,
//	Rte_GetVfb_PaFrontMotorCmd,
};
static const MotorFun s_StallErrFunc[EN_SeatSwitchMax] =
{
	Rte_GetVfb_DrHeightStallErr,
	Rte_GetVfb_DrLengthStallErr,
	Rte_GetVfb_DrBackStallErr,
	Rte_GetVfb_DrFrontStallErr,
//	Rte_GetVfb_PaHeightStallErr,
	Rte_GetVfb_PaLengthStallErr,
	Rte_GetVfb_PaBackStallErr,
//	Rte_GetVfb_PaFrontStallErr,
};
/***********************************************************************
 * @function name: Cdd_HallCounterUpdata
 *
 * @description:堵转标定时，霍尔计数以及记忆数值更新
 *
 * @input parameters: 通道
 *
 * @output parameters:
 *
 * @return:
 *
 * @note:
 *
 * @author: Prima Niu
 *
 * @date: 2023-05-15
 ***********************************************************************/
static void Cdd_HallCounterUpdata(INT8U i)
{
	INT8U j = 0;
	INT16U Adjust_offset = 0;
	INT16U MemPosi_Adjust = 0;
    INT8U MemChangeFlg = 0;
    INT8U CurHallCntEnIndex = 0;//当前坐标
    INT8U MemHallCntEnIndex = 0;//记忆调用坐标
    INT8U ResHallCntEnIndex = 0;//小憩调用坐标
    INT8U SoftStopCntEnIndex = 0;//软堵转次数
    INT8U HardStopCntEnIndex = 0;//硬止点坐标

    if(i <= EN_DriverFront)
    {
    	//主驾
        MemHallCntEnIndex = EN_MemIndex_DrMem1_Height + i;
        CurHallCntEnIndex = EN_MemIndex_DrCurHallCnt_Height + i;
        SoftStopCntEnIndex = EN_MemIndex_DrHeightSoftStopCnt + i;
        HardStopCntEnIndex = EN_MemIndex_DrHardStopPos_Height + i;
        ResHallCntEnIndex = EN_MemIndex_DrRes_ReCallPosi_Height + i;
    }
    else
    {
    	//副驾
        MemHallCntEnIndex = EN_MemIndex_PaMem1_Length + i - EN_PassengerLength;//从副驾纵向开始 减去主驾4向
        CurHallCntEnIndex = EN_MemIndex_PaCurHallCnt_Length + i - EN_PassengerLength;
        SoftStopCntEnIndex = EN_MemIndex_PaLengthSoftStopCnt + i - EN_PassengerLength;
        HardStopCntEnIndex = EN_MemIndex_PaHardStopPos_Length + i - EN_PassengerLength;
    }

	//后止点小于-100%（在-100%~0处进行了前堵转，或者在小于-100%处进行了后堵转），则后止点更新到-100%，当前位置计数以及记忆位置全部增加偏移量
	if(HallDataHandle.HardStopPos[i] < (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]))
	{
		Adjust_offset = (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]) - HallDataHandle.HardStopPos[i];
		HallDataHandle.HallPwmCnt[i] = HallDataHandle.HallPwmCnt[i] + Adjust_offset;
		HallDataHandle.HardStopPos[i] = (D_ADC_HALL_DEF - HallDataHandle.StopPosCnt[i]);
	}
	//后止点大于0%（在0~100%处进行了后堵转，或者大于100%处进行了前堵转），则后止点更新到0%，当前位置计数以及记忆位置全部减少偏移量
	if(HallDataHandle.HardStopPos[i] > D_ADC_HALL_DEF)
	{
		Adjust_offset = HallDataHandle.HardStopPos[i] - D_ADC_HALL_DEF;
		HallDataHandle.HallPwmCnt[i] = HallDataHandle.HallPwmCnt[i] - Adjust_offset;
		HallDataHandle.HardStopPos[i] = D_ADC_HALL_DEF;
    }
	//需要调整当前的方向
	Srvl_SetMemIndexDataU16(CurHallCntEnIndex, HallDataHandle.HallPwmCnt[i]);

    if(MemChangeFlg == FALSE && HallDataHandle.PreHardStopPos[i] != 0xFFFF && HallDataHandle.PreHardStopPos[i] != 0)
    {
        /* 前硬止点 大于 现硬止点 */
        if(HallDataHandle.PreHardStopPos[i] > HallDataHandle.HardStopPos[i])
        {
            Adjust_offset = HallDataHandle.PreHardStopPos[i] - HallDataHandle.HardStopPos[i];
            MemChangeFlg = 1;
        }
        else if(HallDataHandle.PreHardStopPos[i] < HallDataHandle.HardStopPos[i])
        {
            Adjust_offset = HallDataHandle.HardStopPos[i] - HallDataHandle.PreHardStopPos[i];
            MemChangeFlg = 2;
        }
        else
        {

        }

        if(MemChangeFlg > FALSE)
        {
            for(j = 0;j < 3;j ++)
            {
                //更新对应方向的记忆位置参数
            	MemHallCntEnIndex = MemHallCntEnIndex + j * 5;
                MemPosi_Adjust = Srvl_GetMemIndexDataU16(MemHallCntEnIndex);
                //超过100%的同步回移，其他不改变
                if((MemPosi_Adjust != 0x0000) && (MemPosi_Adjust != 0xFFFF))
                {
                    if(MemChangeFlg == 1)
                    {
                        if(MemPosi_Adjust >= HallDataHandle.HardStopPos[i] + Adjust_offset)
                        {
                            MemPosi_Adjust = MemPosi_Adjust - Adjust_offset;
                        }
                        else
                        {
                            MemPosi_Adjust = HallDataHandle.HardStopPos[i];
                        }
                        Srvl_SetMemIndexDataU16(MemHallCntEnIndex, MemPosi_Adjust);
                    }
                    else if(MemChangeFlg == 2)
                    {
                        if(MemPosi_Adjust <= HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i] + Adjust_offset)
                        {
                            MemPosi_Adjust = MemPosi_Adjust + Adjust_offset;
                        }
                        else
                        {
                            MemPosi_Adjust = HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i];
                        }
                        Srvl_SetMemIndexDataU16(MemHallCntEnIndex, MemPosi_Adjust);
                    }
                    else
                    {

                    }
                }
            }
             //更新小憩位置
             if(i <= EN_DriverFront)
             {
                 MemPosi_Adjust = Srvl_GetMemIndexDataU16(ResHallCntEnIndex);
                 if((MemPosi_Adjust != 0x0000) && (MemPosi_Adjust != 0xFFFF))
                 {
                     if(MemChangeFlg == 1)
                     {
                         if(MemPosi_Adjust >= HallDataHandle.HardStopPos[i] + Adjust_offset)
                         {
                             MemPosi_Adjust = MemPosi_Adjust - Adjust_offset;
                         }
                         else
                         {
                             MemPosi_Adjust = HallDataHandle.HardStopPos[i];
                         }
                         Srvl_SetMemIndexDataU16(ResHallCntEnIndex, MemPosi_Adjust);
                     }
                     else if(MemChangeFlg == 2)
                     {
                         if(MemPosi_Adjust <= HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i] + Adjust_offset)
                         {
                             MemPosi_Adjust = MemPosi_Adjust + Adjust_offset;
                         }
                         else
                         {
                             MemPosi_Adjust = HallDataHandle.HardStopPos[i] + HallDataHandle.StopPosCnt[i];
                         }
                         Srvl_SetMemIndexDataU16(ResHallCntEnIndex, MemPosi_Adjust);
                     }
                     else
                     {

                     }
                 }
             }
         }
     }

    /* 重新开始处理到达软止点 */
    Srvl_SetMemIndexDataU8(SoftStopCntEnIndex, 0);
    Srvl_SetMemIndexDataU16(HardStopCntEnIndex, HallDataHandle.HardStopPos[i]);
    HallDataHandle.PreHardStopPos[i] = HallDataHandle.HardStopPos[i];
}
/***********************************************************************
 * @function name: Cdd_HallValUpdata
 *
 * @description: 寻找最小值策略
 *
 * @input parameters: SeekFlag:找最小值标志位
 * Count:电机索引号；ChlValue:电机实时采集Hall信号AD数据
 * @output parameters:
 *
 * @return:
 *
 * @note:
 *
 * @author: Prima Niu
 *
 * @date: 2023-03-21 13:30
 ***********************************************************************/
static INT16U Cdd_HallValUpdata(INT8U HallState, INT16U HallPreVal, INT16U HallCurVal)
{
	if((HallPreVal > HallCurVal) && (2 == HallState))
	{
		//更新数据最小数
		HallPreVal = HallCurVal;
	}

	if((HallPreVal < HallCurVal) && (1 == HallState))
	{
		//更新数据最大数
		HallPreVal = HallCurVal;
	}

	return HallPreVal;
}


/***********************************************************************************************
 * @function name:  Cdd_GetSeatPosi
 * @description:       反馈座椅位置
 * @input parameters:  chl，Precent
 * @output parameters: Posi
 * @return:            Posi
 * @note:
 * @author:            czy
 * @note:              2022-09-8
 ***********************************************************************************************/
INT16U Cdd_GetSeatPosi(enSWITCH chl,INT16U Precent)
{
    INT16U Posi = 0;

    strADCHALLDATA HallData = Cdd_HallDataGet();  //获取当前霍尔反馈的PWM值

    Posi = HallData.HardStopPos[chl] + (INT16U)((INT32U)Precent * HallData.StopPosCnt[chl]/D_POSI);

    return Posi;

}
/********************************************************************
* 函数名称：Cdd_HallDataGet
* 功能描述：获取霍尔反馈数据
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 备    注: 无
********************************************************************/
strADCHALLDATA Cdd_HallDataGet(void)
{
	return HallDataHandle;
}
/***********************************************************************************************
 * @function name:  BOOL Cdd_IsHallAllStop(void)
 * @description:    判断所有霍尔通道是否都已停止采集
 * @input parameters:     无
 * @output parameters:    无
 * @return:         TRUE：全部停止；FALSE：有采集中
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
BOOL Cdd_IsHallAllStop(void)
{
    return s_HallAllStopFlag;
}

/***********************************************************************************************
 * @function name:  Cdd_HallDmaHandler
 * @description:    处理DMA霍尔采样数据，用于霍尔计数和异常处理-调用周期1ms
 * @input parameters:     无
 * @output parameters:    无
 * @return:         无
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
void Cdd_HallDmaHandler(void)
{
	static HALL_CMD_STATE_T HallCmdState[EN_SeatSwitchMax];
	static BOOL g_HallStoreFlag = FALSE;
	INT8U i = 0;
	INT16U AD_Value = 0;
	EN_MOTOR_MOVE MotorCmd = EN_MOTOR_DEF;
	BOOL StallErrFlag = FALSE;

	s_HallAllStopFlag  = TRUE;

	//这里ADCChlManage的霍尔通道要与EN_SeatSwitchMax枚举通道保持一致
	for(i = enADC_DrHeightHallFB; i <= enADC_PaBackHallFB; i++)
	{
		MotorCmd = s_MotorCmdFunc[i]();
		StallErrFlag = s_StallErrFunc[i]();
		// 更新状态：只要有运动命令，就更新
		if(MotorCmd != EN_MOTOR_DEF)
		{
			HallCmdState[i].LastCmd = MotorCmd;
			HallCmdState[i].DelayedCollectionTimer = HALL_KEEP_TIME_MS;
		}

		// 当前电机运行 或者 在延迟采集时间内
		if((MotorCmd != EN_MOTOR_DEF)
		|| (HallCmdState[i].DelayedCollectionTimer != 0))
		{
			s_HallAllStopFlag  = FALSE;

			AD_Value = Dma0_Adc0_Buf[i];/* 直接获取DMA搬运后的数据 */
//			if(ERR_OK == Ecual_AD_MeasureChan(i, &AD_Value))/*原平台接口 获取单次转换AD值*/
			{
				Cdd_HallAcquire(i, AD_Value, HallCmdState[i].LastCmd, StallErrFlag);//霍尔计数
			}
		}
		//暂时按调度周期自减 可以考虑在1ms任务定时自减
		if(HallCmdState[i].DelayedCollectionTimer > 0)
		{
			HallCmdState[i].DelayedCollectionTimer --;
		}
	}

	// 判断是否所有通道都已完全停止，执行一次存储
	if((s_HallAllStopFlag  == TRUE) && (g_HallStoreFlag == TRUE))
	{
		Cdd_HallStoreAll();
		g_HallStoreFlag = FALSE;
	}
	else if(s_HallAllStopFlag  != TRUE)
	{
		g_HallStoreFlag = TRUE;
	}
	else
	{

	}
}

/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description: 获取当前位置霍尔计数
 * @input parameters: 座椅调节方向
 * @output parameters:
 * @return: 当前方向霍尔计数
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetCurrentHallCnt(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.HallPwmCnt[Posi];
	}

	return HallCnt;
}
/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description:获取导轨长度
 * @input parameters: 座椅调节方向
 * @output parameters:
 * @return:
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetMotorSize(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.StopPosCnt[Posi];
	}

	return HallCnt;
}
/***********************************************************************
 * @function name: Ecual_AdcGetCurrentHallCnt
 * @description: 获取硬止点位置
 * @input parameters: 座椅调节方向
 * @output parameters:
 * @return:
 * @note:
 * @author: Prima Niu
 * @date: 2023-04-18 18:28
 ***********************************************************************/
INT16U Cdd_GetMotorHardStop(enSWITCH Posi)
{
	INT16U HallCnt = 0;

	if(Posi < EN_SeatSwitchMax)
	{
		HallCnt = HallDataHandle.HardStopPos[Posi];
	}

	return HallCnt;
}
/***********************************************************************************************
 * @function name:  Cdd_GetMotorLearnFlag
 * @description:	获取电机学习状态
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
BOOL Cdd_GetMotorLearnFlag(enSWITCH Posi)
{
	BOOL temp = 0;
	if(Posi < EN_SeatSwitchMax)
	{
		if(HallDataHandle.HardStopPos[Posi] != 0
		&& HallDataHandle.HardStopPos[Posi] != 0xFFFF)
		{
			temp = 1;
		}
	}

	return temp;
}
/***********************************************************************************************
 * @function name:  Cdd_HallStoreAll
 * @description:	霍尔当前数据存储任务函数
 * @input parameters:
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         ssj 2025-03-26
 ***********************************************************************************************/
static void Cdd_HallStoreAll(void)
{
	for(INT8U i = 0; i < EN_SeatSwitchMax; i++)
	{
		INT16U hallValue = HallDataHandle.HallPwmCnt[i];
		enSrvMemIndex memIndex;

		switch(i)
		{
			case EN_DriverHeight : memIndex = EN_MemIndex_DrCurHallCnt_Height; break;
			case EN_DriverLength : memIndex = EN_MemIndex_DrCurHallCnt_Length; break;
			case EN_DriverBack   : memIndex = EN_MemIndex_DrCurHallCnt_Back; break;
			case EN_DriverFront  : memIndex = EN_MemIndex_DrCurHallCnt_Front; break;

			default:
				continue;  // 未知通道，跳过
		}

		Srvl_SetMemIndexDataU16(memIndex, hallValue);
	}
}
/***********************************************************************************************
 * @function name:  Rte_LoadHallDataToRam
 * @description:    从EEPROM中读取当前霍尔值及硬止点数据，写入到HallDataHandle结构体中
 * @input parameters:     无
 * @output parameters:     无
 * @return:         BOOL：操作成功返回TRUE
 * @note:
 * @author:         ssj + 2025-04-24 11:10
 ***********************************************************************************************/
void Cdd_ReadAllHallFromE2(void)
{
    HallDataHandle.HallPwmCnt[EN_DriverHeight]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Height);
    HallDataHandle.HallPwmCnt[EN_DriverLength]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Length);
    HallDataHandle.HallPwmCnt[EN_DriverBack]    = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Back);
    HallDataHandle.HallPwmCnt[EN_DriverFront]   = Srvl_GetMemIndexDataU16(EN_MemIndex_DrCurHallCnt_Front);

    HallDataHandle.HardStopPos[EN_DriverHeight] = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height);
    HallDataHandle.HardStopPos[EN_DriverLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Length);
    HallDataHandle.HardStopPos[EN_DriverBack]   = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back);
    HallDataHandle.HardStopPos[EN_DriverFront]  = Srvl_GetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Front);

    HallDataHandle.HallPwmCnt[EN_PassengerLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Length);
    HallDataHandle.HallPwmCnt[EN_PassengerBack] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaCurHallCnt_Back);

    HallDataHandle.HardStopPos[EN_PassengerLength] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Length);
    HallDataHandle.HardStopPos[EN_PassengerBack] = Srvl_GetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Back);

    memcpy(&HallDataHandle.PreHardStopPos[0], &HallDataHandle.HardStopPos[0], sizeof(HallDataHandle.PreHardStopPos));
}

/***********************************************************************************************
 * @function name: Cdd_ClearDriverHardStopData
 * @description: 清除主驾的硬止点数据，包括 RAM 中的 HardStopPos 和 EEPROM 中的相关信息
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
void Cdd_ClearDriverHardStopData(void)
{
    /* 清除 RAM 中主驾硬止点数据 */
    HallDataHandle.HardStopPos[EN_DriverHeight] = 0;
    HallDataHandle.HardStopPos[EN_DriverLength] = 0;
    HallDataHandle.HardStopPos[EN_DriverBack] = 0;
    HallDataHandle.HardStopPos[EN_DriverFront] = 0;

    HallDataHandle.PreHardStopPos[EN_DriverHeight] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverLength] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverBack] = 0;
    HallDataHandle.PreHardStopPos[EN_DriverFront] = 0;

    /* 清除 EEPROM 中主驾硬止点相关信息 */
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Height, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Length, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Back, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_DrHardStopPos_Front, 0xFFFF);
}
/***********************************************************************************************
 * @function name: Cdd_ClearPassengerHardStopData
 * @description: 清除副驾的硬止点数据，包括 RAM 中的 HardStopPos 和 EEPROM 中的相关信息
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @author: ssj + 2025-05-15
 ***********************************************************************************************/
void Cdd_ClearPassengerHardStopData(void)
{
    /* 清除 RAM 中副驾硬止点数据 */
    HallDataHandle.HardStopPos[EN_PaResever_1] = 0;
    HallDataHandle.HardStopPos[EN_PassengerLength] = 0;
    HallDataHandle.HardStopPos[EN_PassengerBack] = 0;
    HallDataHandle.HardStopPos[EN_PaResever_2] = 0;

    HallDataHandle.PreHardStopPos[EN_PaResever_1] = 0;
    HallDataHandle.PreHardStopPos[EN_PassengerLength] = 0;
    HallDataHandle.PreHardStopPos[EN_PassengerBack] = 0;
    HallDataHandle.PreHardStopPos[EN_PaResever_2] = 0;

    /* 清除 EEPROM 中副驾硬止点相关信息 */
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Height, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Length, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Back, 0xFFFF);
    Srvl_SetMemIndexDataU16(EN_MemIndex_PaHardStopPos_Front, 0xFFFF);
}
/***********************************************************************************************
 * @function name:  Cdd_HallAcquire
 * @description:    对指定通道霍尔信号进行采样处理，实现变沿检测、霍尔计数与堵转标定
 * @input parameters:     i：霍尔通道索引 HallCurVal：当前AD采样值 MotorCmd：当前运动命令 StallErrFlag：堵转标志
 * @output parameters:    无
 * @return:         无
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
static void Cdd_HallAcquire(INT8U i, INT16U HallCurVal, EN_MOTOR_MOVE MotorCmd, BOOL StallErrFlag)
{
	static INT16U HallPreVal[EN_SeatSwitchMax] = {0};  //上一次的采集值

	if(EN_MOTOR_UP_FW_LF == MotorCmd)
	{
		//本地开关调节发生堵转，标定导轨，写入标定标志，其他调节方式不进行标定
		if(TRUE == StallErrFlag)
		{
			HallDataHandle.HardStopPos[i] = HallDataHandle.HallPwmCnt[i] - HallDataHandle.StopPosCnt[i];
			Cdd_HallCounterUpdata(i);
		}
		//前一个AD数值与当前的做对比，高低电平相差400（8V供电时，差值AD约540）
		if(abs(HallPreVal[i] - HallCurVal) > s_HallDiffValue)
		{
			//变沿检测
			if(HallState[i] == 1)//上升沿中 ：检测到当前AD比上一次AD小则认为是下降沿 否则不更新霍尔数
			{
				if(HallCurVal < HallPreVal[i])
				{
					HallState[i] = 2;//下
					HallDataHandle.HallPwmCnt[i]++;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//更新最大值
				}
			}
			else if(HallState[i] == 2)//下升沿中 ：检测到当前AD比上一次AD大则认为是上升沿 否则不更新霍尔数
			{
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//上
					HallDataHandle.HallPwmCnt[i]++;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//更新最小值
				}

			}
			else
			{
				//第一次上电 直接更新
				HallDataHandle.HallPwmCnt[i]++;
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//上升沿
				}
				else
				{
					HallState[i] = 2;//下降沿
				}
			}

			//有HALL，则HALL正常(次数10，避免抖动)
			if(++HallErr.HallNorCnt[i] >= HALLNORTIME)
			{
				HallErr.HallNorCnt[i] = HALLNORTIME;
				HallErr.HallNorFlg[i] = TRUE;

				HallErr.HallErrCnt[i] = 0;
				HallErr.HallErrFlg[i] = FALSE;
			}
			//更新数据
			HallPreVal[i] = HallCurVal;
		}
		else
		{
			//有控制命令但无HALL，时间需要与电机PWM频率相关（时间需大于PWM周期）
			if(++HallErr.HallErrCnt[i] >= D_HALLTIME)
			{
				HallErr.HallErrCnt[i] = D_HALLTIME;
				HallErr.HallErrFlg[i] = TRUE;
			}
			/* 更新上一次的最小值/最大值 */
			HallPreVal[i] = Cdd_HallValUpdata(HallState[i], HallPreVal[i], HallCurVal);
		}
	}
	else if(EN_MOTOR_DN_BW_RT == MotorCmd)
	{
		//本地开关调节发生堵转，标定导轨，写入标定标志，其他调节方式不进行标定
//		if((EN_CURR_DN_ERR == ScanIOStateFlag.MOTOR_CURR[i]) && (EN_SW_DN_BW_RT == SEAT_ADJUST_SW[i]))
		if(TRUE == StallErrFlag)
		{
			HallDataHandle.HardStopPos[i] = HallDataHandle.HallPwmCnt[i];
			Cdd_HallCounterUpdata(i);
		}
		//前一个AD数值与当前的做对比，高低电平相差400（8V供电时，差值AD约540）
		if(abs(HallPreVal[i] - HallCurVal) > s_HallDiffValue)
		{
			//变沿检测
			if(HallState[i] == 1)//上升沿中 ：检测到当前AD比上一次AD小则认为是下降沿 否则不更新霍尔数
			{
				if(HallCurVal < HallPreVal[i])
				{
					HallState[i] = 2;//下
					HallDataHandle.HallPwmCnt[i]--;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//更新最大值
				}
			}
			else if(HallState[i] == 2)//下升沿中 ：检测到当前AD比上一次AD大则认为是上升沿 否则不更新霍尔数
			{
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//上
					HallDataHandle.HallPwmCnt[i]--;
				}
				else
				{
					HallPreVal[i] = HallCurVal;//更新最小值
				}

			}
			else
			{
				//第一次上电 直接更新
				HallDataHandle.HallPwmCnt[i]--;
				if(HallCurVal > HallPreVal[i])
				{
					HallState[i] = 1;//上升沿
				}
				else
				{
					HallState[i] = 2;//下降沿
				}
			}
			//有HALL，则HALL正常(次数10，避免抖动)
			if(++HallErr.HallNorCnt[i] >= HALLNORTIME)
			{
				HallErr.HallNorCnt[i] = HALLNORTIME;
				HallErr.HallNorFlg[i] = TRUE;

				HallErr.HallErrCnt[i] = 0;
				HallErr.HallErrFlg[i] = FALSE;
			}
			//更新数据
			HallPreVal[i] = HallCurVal;
		}
		else
		{
			//有控制命令但无HALL，时间需要与电机PWM频率相关（时间需大于PWM周期）
			if(++HallErr.HallErrCnt[i] >= D_HALLTIME)
			{
				HallErr.HallErrCnt[i] = D_HALLTIME;
				HallErr.HallErrFlg[i] = TRUE;
			}
			/* 更新上一次的最小值/最大值  */
			HallPreVal[i] = Cdd_HallValUpdata(HallState[i], HallPreVal[i], HallCurVal);
		}
	}
	else
	{
		//无操作CMD动作时，才清正常HALL计数，清HALL正常工作标识
		HallErr.HallNorCnt[i] = 0;
		HallErr.HallNorFlg[i] = FALSE;
		//更新数据
		HallPreVal[i] = HallCurVal;
	}
}
/***********************************************************************************************
 * @function name:  Ecual_HandleHallAndTriggerAdc
 * @description:    处理霍尔DMA数据，触发ADC0转换，并清除DMA0更新标志位
 * 					由于DMA工作时会与模拟E2操作flash接口冲突，不能在定时中断中调用此任务
 * @input parameters:     无
 * @output parameters:    无
 * @return:         无
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
void Ecual_HandleHallAndTriggerAdc(void)
{
	static INT32U u32HallAdcTrigTimer = 0;
    if(CPU_TimerDiffTs(u32HallAdcTrigTimer) >= 1)
    {
    	u32HallAdcTrigTimer = D_HAL_GET_CUR_MS_TS();
		Cdd_HallDmaHandler();
		//必须先清除 避免清除时 DMA已提前完成中断
		Ecual_SetDma0_Adc0_UpdateFlag(FALSE);
		ADC_DRV_SoftwareStartConv(ADCx_0);
    }
}

