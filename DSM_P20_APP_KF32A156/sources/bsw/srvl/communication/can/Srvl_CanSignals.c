/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               Srvl_CanSignals.c
** Created By:              Prima Niu
** Created date:            2024/6/18 星期二 11:26:47
** Version:                 V1.0
** Descriptions:            Implementation of signals
**
**------------------------------------------------------------------------------------------------
** Created By:              
** Created date:            
** Version:                 
** Descriptions:            
**
**************************************************************************************************/

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "Srvl_CanSignals.h"

/*************************************************************/
/* Signals of receive messages                               */
/*************************************************************/
/*************************************************************
变量描述：小憩模式键按下设定
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive
0x1:打开小憩模式
0x2:关闭小憩模式
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x367_IVI_NapMode_SwtichSet(void)
{
     return b_IVI4_IVI_NapMode_SwtichSet_b();
}

/*************************************************************
变量描述：主驾座椅记忆设置1
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 1 请求记忆位置1；
0x2:Memorize  current position 1 记忆现在的位置为1；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet1(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet1_b();
}

/*************************************************************
变量描述：主驾座椅记忆设置2
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 2 请求记忆位置2；
0x2:Memorize  current position 2 记忆现在的位置为2；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet2(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet2_b();
}

/*************************************************************
变量描述：主驾座椅记忆设置3
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 3 请求记忆位置3；
0x2:Memorize  current position 3 记忆现在的位置为3；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet3(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet3_b();
}

/*************************************************************
变量描述：主驾迎宾使能
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:Open
0x2:Close
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_St_FLSeatmeet(void)
{
     return b_IVI8_DSM_IVI_St_FLSeatmeet_b();
}

/*************************************************************
变量描述：副驾座椅记忆设置1
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 1 请求记忆位置1；
0x2:Memorize  current position 1 记忆现在的位置为1；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet1(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet1_b();
}

/*************************************************************
变量描述：副驾座椅记忆设置2
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 2 请求记忆位置2；
0x2:Memorize  current position 2 记忆现在的位置为2；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet2(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet2_b();
}

/*************************************************************
变量描述：副驾座椅记忆设置3
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:call Memory position 3 请求记忆位置3；
0x2:Memorize  current position 3 记忆现在的位置为3；
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet3(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet3_b();
}

/*************************************************************
变量描述：副驾迎宾使能
变量区间: 0x0--0x3
变量说明: 
0x0:Inactive；
0x1:Open
0x2:Close
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_St_FRSeatmeet(void)
{
     return b_IVI8_DSM_IVI_St_FRSeatmeet_b();
}

/*************************************************************
变量描述：主驾座椅加热设置
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive；
0x1:Level 1；1档
0x2:Level 2；2档
0x3:Level 3；3档
0x4:OFF:
0x5:OPEN;
0x6:Reserved；
0x7:Invaild；
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatHeatSet(void)
{
     return b_IVI8_DSM_IVI_FLSeatHeatSet_b();
}

/*************************************************************
变量描述：副驾座椅加热设置
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive；
0x1:Level 1；1档
0x2:Level 2；2档
0x3:Level 3；3档
0x4:OFF:
0x5:OPEN;
0x6:Reserved；
0x7:Invaild；
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatHeatSet(void)
{
     return b_IVI8_DSM_IVI_FRSeatHeatSet_b();
}

/*************************************************************
变量描述：主驾座椅通风设置
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive；
0x1:Level 1；1档
0x2:Level 2；2档
0x3:Level 3；3档
0x4:OFF:
0x5:OPEN;
0x6:Reserved；
0x7:Invaild；
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatVentnSet(void)
{
     return b_IVI8_DSM_IVI_FLSeatVentnSet_b();
}

/*************************************************************
变量描述：副驾座椅通风设置
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive；
0x1:Level 1；1档
0x2:Level 2；2档
0x3:Level 3；3档
0x4:OFF:
0x5:OPEN;
0x6:Reserved；
0x7:Invaild；
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatVentnSet(void)
{
     return b_IVI8_DSM_IVI_FRSeatVentnSet_b();
}

/*************************************************************
变量描述：方向盘加热开关使能
变量区间: 0x0--0x1
变量说明: 
0x0:Not Pressed
0x1:Pressed
*************************************************************/
canuint8 CanRx_0x351_IVI_SwsHeatSw(void)
{
     return b_IVI8_DSM_IVI_SwsHeatSw_b();
}

/*************************************************************
变量描述：按摩档位请求
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive；
0x1:Level 1；1档
0x2:Level 2；2档
0x3:Level 3；3档
0x4:OFF:
0x5~0x6:Reserved；
0x7:Invaild；
*************************************************************/
canuint8 CanRx_0x351_IVI_MassageLevel_Req(void)
{
     return b_IVI8_DSM_IVI_MassageLevel_Req_b();
}

/*************************************************************
变量描述：按摩模式请求
变量区间: 0x0--0xF
变量说明: 
0x0：Inactive
0x1: 全身放松
0x2: 全身激活
0x3：肩部激活
0x4: 肩部放松
0x5：腰部激活
0x6：腰部放松
0x7：背部激活
0x8：背部放松
0x9-0x14：Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_MassageMode_Req(void)
{
     return b_IVI8_DSM_IVI_MassageMode_Req_b();
}

/*************************************************************
变量描述：左前门状态
变量区间: 0x0--0x1
变量说明: 
0x0:Close
0x1:Open
*************************************************************/
canuint8 CanRx_0x28E_BDC_FLDoorSts(void)
{
     return b_BDC3_BDC_FLDoorSts_b();
}

/*************************************************************
变量描述：右前门状态
变量区间: 0x0--0x1
变量说明: 
0x0:Close
0x1:Open
*************************************************************/
canuint8 CanRx_0x28E_BDC_FRDoorSts(void)
{
     return b_BDC3_BDC_FRDoorSts_b();
}

/*************************************************************
变量描述：BDC转发远程主驾驶座椅加热请求
变量区间: 0x0--0x7
变量说明: 
0x0:No Request
0x1:Heat_1
0x2:Heat_2
0x3:Heat_3
0x4:Close
0x5:Reserved
0x6:Reserved
0x7:Invalid
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_DrSeatHeating(void)
{
     return b_BDC5_BDC_TBOX_Req_DrSeatHeating_b();
}

/*************************************************************
变量描述：BDC转发远程副驾驶座椅加热请求
变量区间: 0x0--0x7
变量说明: 
0x0:No Request
0x1:Heat_1
0x2:Heat_2
0x3:Heat_3
0x4:Close
0x5:Reserved
0x6:Reserved
0x7:Invalid
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_PaSeatHeating(void)
{
     return b_BDC5_BDC_TBOX_Req_PaSeatHeating_b();
}

/*************************************************************
变量描述：BDC转发远程主驾驶座椅通风请求
变量区间: 0x0--0x7
变量说明: 
0x0:No Request
0x1:Ventilate_1
0x2:Ventilate_2
0x3:Ventilate_3
0x4:Close
0x5:Reserved
0x6:Reserved
0x7:Invalid
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_DrSeatVentilating(void)
{
     return b_BDC5_BDC_TBOX_Req_DrSeatVentilating_b();
}

/*************************************************************
变量描述：BDC转发远程副驾驶座椅通风请求
变量区间: 0x0--0x7
变量说明: 
0x0:No Request
0x1:Ventilate_1
0x2:Ventilate_2
0x3:Ventilate_3
0x4:Close
0x5:Reserved
0x6:Reserved
0x7:Invalid
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_PaSeatVentilating(void)
{
     return b_BDC5_BDC_TBOX_Req_PaSeatVentilating_b();
}

/*************************************************************
变量描述：TBOX远程方向盘加热命令请求
变量区间: 0x0--0x3
变量说明: 
0x0:无动作
0x1:开始
0x2:关闭
0x3:无效值
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_Steeringwheel_heating(void)
{
     return b_BDC5_BDC_TBOX_Req_Steeringwheel_heating_b();
}

/*************************************************************
变量描述：整车低压电源状态
变量区间: 0x0--0x7
变量说明: 
0x0:Off 
0x1:Acc 
0x2:On 
0x3:Crank
0x4~0x7:Reserved
*************************************************************/
canuint8 CanRx_0x283_BDC_PDU(void)
{
     return b_BDC6_PEPS1_BDC_PDU_b();
}

/*************************************************************
变量描述：BDC remote control status
BDC Tbox远程发动机状态
变量区间: 0x0--0x1
变量说明: 
0x0:Not Remote control mode
0x1:Remote control mode
*************************************************************/
canuint8 CanRx_0x283_BDC_TboxRemoteControlSt(void)
{
     return b_BDC6_PEPS1_BDC_TboxRemoteControlSt_b();
}

/*************************************************************
变量描述：Gear selector position
档位状态
变量区间: 0x0--0xF
变量说明: 
0x0:P
0x1:Reserved
0x2:Reserved
0x3:Reserved
0x4:Reserved
0x5:D
0x6:N
0x7:R
0xF:Fault Value
*************************************************************/
canuint8 CanRx_0x238_TCU_GearSelDisp(void)
{
     return b_TCU1_TCU_GearSelDisp_b();
}

/*************************************************************
变量描述：车速信号有效性
变量区间: 0x0--0x1
变量说明: 
0x0:valid
0x1:invalid
*************************************************************/
canuint8 CanRx_0x284_ABS_VehicleSpeedValid(void)
{
     return b_ABS1_ABS_VehicleSpeedValid_b();
}

/*************************************************************
变量描述：ABS Vehicle Speed
车速信号
变量区间: 0x0--0x8CA0
变量说明: 
0x0000:0~
0x8CA0:360
0x8CA1:Reserved
0xFFFE:Reserved
0xFFFF:Invalid
*************************************************************/
canuint16 CanRx_0x284_ABS_VehicleSpeed(void)
{
     return b_ABS1_ABS_VehicleSpeed_b();
}

/*************************************************************
变量描述：ENG_STA
发动机状态信息
变量区间: 0x0--0x3
变量说明: 
0x0:engine stopped
0x1:Reserved
0x2:engine running
0x3:engine cranking
*************************************************************/
canuint8 CanRx_0x2A7_ECMD_EngineStatus(void)
{
     return b_GWB1_ECMD_EngineStatus_b();
}

/*************************************************************
变量描述：Vehicle Running Status
整车运行状态
变量区间: 0x0--0x3
变量说明: 
0x0:HV OFF
0x1:HV ON
0x2:Ready
0x3:Invalid
*************************************************************/
canuint8 CanRx_0x2AE_VCU_VehRunSta(void)
{
     return b_VCU1_VCU_VehRunSta_b();
}

/*************************************************************
变量描述：Gear Selector Position
档位状态
变量区间: 0x0--0xF
变量说明: 
0x0:P
0x1:Reserved
0x2:Reserved
0x3:Reserved
0x4:Reserved
0x5:D
0x6:N
0x7:R
0xF:Fault Value
*************************************************************/
canuint8 CanRx_0x26E_VCU_GearSelDisp(void)
{
     return b_GWB2_VCU_GearSelDisp_b();
}

/*************************************************************/
/* Signals of send messages                               */
/*************************************************************/
/*************************************************************
变量描述：主驾座椅记忆反馈信息
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive无作动
0x1:Seat position 1 memory succed位置1记忆成功
0x2:Seat position 2 memory succed位置2记忆成功
0x3:Seat position 3 memory succed位置3记忆成功
0x4:Seat position memory fail位置记忆失败
0x5-0x7:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_FLSeatMemStsAndMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FLSeatMemStsAndMsg(sigData);
}

/*************************************************************
变量描述：主驾迎宾状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Open
0x1:Close
0x2:Fault
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_FLSeatmeet(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_FLSeatmeet(sigData);
}

/*************************************************************
变量描述：主驾座椅记忆1调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆1调用成功
0x2:Call Memory Position Faild记忆1调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆1清除成功
0x5:Clean Up Memory Position Faild记忆1清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM1_FLSeatMem1Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM1_FLSeatMem1Sts(sigData);
}

/*************************************************************
变量描述：主驾座椅记忆2调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆2调用成功
0x2:Call Memory Position Faild记忆2调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆2清除成功
0x5:Clean Up Memory Position Faild记忆2清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM2_FLSeatMem2Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FLSeatMem2Sts(sigData);
}

/*************************************************************
变量描述：主驾座椅记忆3调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆3调用成功
0x2:Call Memory Position Faild记忆3调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆3清除成功
0x5:Clean Up Memory Position Faild记忆3清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM3_FLSeatMem3Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM3_FLSeatMem3Sts(sigData);
}

/*************************************************************
变量描述：副驾座椅记忆反馈信息
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive无作动
0x1:Seat position 1 memory succed位置1记忆成功
0x2:Seat position 2 memory succed位置2记忆成功
0x3:Seat position 3 memory succed位置3记忆成功
0x4:Seat position memory fail位置记忆失败
0x5-0x7:reserved

*************************************************************/
void  CanTx_0x3B2_DSM_FRSeatMemStsAndMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FRSeatMemStsAndMsg(sigData);
}

/*************************************************************
变量描述：副驾座椅记忆1调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆1调用成功
0x2:Call Memory Position Faild记忆1调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆1清除成功
0x5:Clean Up Memory Position Faild记忆1清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM1_FRSeatMem1Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM1_FRSeatMem1Sts(sigData);
}

/*************************************************************
变量描述：副驾座椅记忆2调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆2调用成功
0x2:Call Memory Position Faild记忆2调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆2清除成功
0x5:Clean Up Memory Position Faild记忆2清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM2_FRSeatMem2Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FRSeatMem2Sts(sigData);
}

/*************************************************************
变量描述：副驾座椅记忆3调用反馈
变量区间: 0x0--0x7
变量说明: 
0x0:Inactive不作动
0x1:Call Memory Position Succeed记忆3调用成功
0x2:Call Memory Position Faild记忆3调用失败
0x3:Waiting正在调用
0x4:Clean Up Memory Position Succeed记忆3清除成功
0x5:Clean Up Memory Position Faild记忆3清除失败
0x6:Reserved
0x7:Invalid无效
*************************************************************/
void  CanTx_0x3B2_DSM2_FRSeatMem3Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FRSeatMem3Sts(sigData);
}

/*************************************************************
变量描述：副驾迎宾状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Open
0x1:Close
0x2:Fault
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_FRSeatmeet(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_FRSeatmeet(sigData);
}

/*************************************************************
变量描述：主驾座椅加热状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Close
0x1:Open
0x2:error
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatHeatSW(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatHeatSW(sigData);
}

/*************************************************************
变量描述：主驾座椅加热档位反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Level 1  1档
0x1:Level 2   2档
0x2:Level 3   3档
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatHeatGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatHeatGear(sigData);
}

/*************************************************************
变量描述：副驾座椅加热状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Close
0x1:Open
0x2:error
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatHeatSW(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatHeatSW(sigData);
}

/*************************************************************
变量描述：副驾座椅加热档位反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Level 1  1档
0x1:Level 2   2档
0x2:Level 3   3档
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatHeatGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatHeatGear(sigData);
}

/*************************************************************
变量描述：主驾座椅通风状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Close
0x1:Open
0x2:error
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatVentilationSW(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatVentilationSW(sigData);
}

/*************************************************************
变量描述：主驾座椅通风档位反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Level 1  1档
0x1:Level 2   2档
0x2:Level 3   3档
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatVentilationGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatVentilationGear(sigData);
}

/*************************************************************
变量描述：副驾座椅通风状态反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Close
0x1:Open
0x2:error
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatVentilationSW(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatVentilationSW(sigData);
}

/*************************************************************
变量描述：副驾座椅通风档位反馈
变量区间: 0x0--0x3
变量说明: 
0x0:Level 1  1档
0x1:Level 2   2档
0x2:Level 3   3档
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatVentilationGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatVentilationGear(sigData);
}

/*************************************************************
变量描述：主驾记忆提示
变量区间: 0x0--0x1
变量说明: 
0x0：No Change
0x1:Change
*************************************************************/
void  CanTx_0x3B2_DSM_FLSeatPosMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FLSeatPosMsg(sigData);
}

/*************************************************************
变量描述：副驾记忆提示
变量区间: 0x0--0x1
变量说明: 
0x0：No Change
0x1:Change
*************************************************************/
void  CanTx_0x3B2_DSM_FRSeatPosMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FRSeatPosMsg(sigData);
}

/*************************************************************
变量描述：方向盘加热工作状态
变量区间: 0x0--0x3
变量说明: 
0x0:No work
0x1:work
0x2:ERROR
0x3:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_SwsHeatSts(canuint8 sigData)
{
     ILPutTxDSM_DSM_SwsHeatSts(sigData);
}

/*************************************************************
变量描述：按摩档位反馈
变量区间: 0x0--0x7
变量说明: 

0X0:OFF
0x1: Level 1
0x2: Level 2
0x3: Level 3
0x4: AUTO  OFF自动关闭
0x5-7：reserved
*************************************************************/
void  CanTx_0x3B2_DSM_MassageLevel_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_MassageLevel_FB(sigData);
}

/*************************************************************
变量描述：按摩模式反馈
变量区间: 0x0--0xF
变量说明: 
0x0: 全身放松
0x1: 全身激活
0x2：肩部激活
0x3: 肩部放松
0x4：腰部激活
0x5：腰部放松
0x6：背部激活
0x7：背部放松
0x8：Error模块故障
0x9-0x14：Reserved
*************************************************************/
void  CanTx_0x3B2_DSM_MassageMode_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_MassageMode_FB(sigData);
}

/*************************************************************
变量描述：小憩模式请求反馈
变量区间: 0--0x3
变量说明: 
0x0:Inactive
0x1:关闭小憩模式
0x2:打开小憩模式
0x3:ERROR
*************************************************************/
void  CanTx_0x3B2_DSM_NapMode_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_NapMode_FB(sigData);
}


