/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               Srvl_CanSignals.c
** Created By:              Prima Niu
** Created date:            2024/6/18 ���ڶ� 11:26:47
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
����������С�ģʽ�������趨
��������: 0x0--0x3
����˵��: 
0x0:Inactive
0x1:��С�ģʽ
0x2:�ر�С�ģʽ
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x367_IVI_NapMode_SwtichSet(void)
{
     return b_IVI4_IVI_NapMode_SwtichSet_b();
}

/*************************************************************
�����������������μ�������1
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 1 �������λ��1��
0x2:Memorize  current position 1 �������ڵ�λ��Ϊ1��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet1(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet1_b();
}

/*************************************************************
�����������������μ�������2
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 2 �������λ��2��
0x2:Memorize  current position 2 �������ڵ�λ��Ϊ2��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet2(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet2_b();
}

/*************************************************************
�����������������μ�������3
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 3 �������λ��3��
0x2:Memorize  current position 3 �������ڵ�λ��Ϊ3��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatMemSet3(void)
{
     return b_IVI8_DSM_IVI_FLSeatMemSet3_b();
}

/*************************************************************
��������������ӭ��ʹ��
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:Open
0x2:Close
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_St_FLSeatmeet(void)
{
     return b_IVI8_DSM_IVI_St_FLSeatmeet_b();
}

/*************************************************************
�����������������μ�������1
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 1 �������λ��1��
0x2:Memorize  current position 1 �������ڵ�λ��Ϊ1��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet1(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet1_b();
}

/*************************************************************
�����������������μ�������2
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 2 �������λ��2��
0x2:Memorize  current position 2 �������ڵ�λ��Ϊ2��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet2(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet2_b();
}

/*************************************************************
�����������������μ�������3
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:call Memory position 3 �������λ��3��
0x2:Memorize  current position 3 �������ڵ�λ��Ϊ3��
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatMemSet3(void)
{
     return b_IVI8_DSM_IVI_FRSeatMemSet3_b();
}

/*************************************************************
��������������ӭ��ʹ��
��������: 0x0--0x3
����˵��: 
0x0:Inactive��
0x1:Open
0x2:Close
0x3:Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_St_FRSeatmeet(void)
{
     return b_IVI8_DSM_IVI_St_FRSeatmeet_b();
}

/*************************************************************
�����������������μ�������
��������: 0x0--0x7
����˵��: 
0x0:Inactive��
0x1:Level 1��1��
0x2:Level 2��2��
0x3:Level 3��3��
0x4:OFF:
0x5:OPEN;
0x6:Reserved��
0x7:Invaild��
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatHeatSet(void)
{
     return b_IVI8_DSM_IVI_FLSeatHeatSet_b();
}

/*************************************************************
�����������������μ�������
��������: 0x0--0x7
����˵��: 
0x0:Inactive��
0x1:Level 1��1��
0x2:Level 2��2��
0x3:Level 3��3��
0x4:OFF:
0x5:OPEN;
0x6:Reserved��
0x7:Invaild��
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatHeatSet(void)
{
     return b_IVI8_DSM_IVI_FRSeatHeatSet_b();
}

/*************************************************************
������������������ͨ������
��������: 0x0--0x7
����˵��: 
0x0:Inactive��
0x1:Level 1��1��
0x2:Level 2��2��
0x3:Level 3��3��
0x4:OFF:
0x5:OPEN;
0x6:Reserved��
0x7:Invaild��
*************************************************************/
canuint8 CanRx_0x351_IVI_FLSeatVentnSet(void)
{
     return b_IVI8_DSM_IVI_FLSeatVentnSet_b();
}

/*************************************************************
������������������ͨ������
��������: 0x0--0x7
����˵��: 
0x0:Inactive��
0x1:Level 1��1��
0x2:Level 2��2��
0x3:Level 3��3��
0x4:OFF:
0x5:OPEN;
0x6:Reserved��
0x7:Invaild��
*************************************************************/
canuint8 CanRx_0x351_IVI_FRSeatVentnSet(void)
{
     return b_IVI8_DSM_IVI_FRSeatVentnSet_b();
}

/*************************************************************
���������������̼��ȿ���ʹ��
��������: 0x0--0x1
����˵��: 
0x0:Not Pressed
0x1:Pressed
*************************************************************/
canuint8 CanRx_0x351_IVI_SwsHeatSw(void)
{
     return b_IVI8_DSM_IVI_SwsHeatSw_b();
}

/*************************************************************
������������Ħ��λ����
��������: 0x0--0x7
����˵��: 
0x0:Inactive��
0x1:Level 1��1��
0x2:Level 2��2��
0x3:Level 3��3��
0x4:OFF:
0x5~0x6:Reserved��
0x7:Invaild��
*************************************************************/
canuint8 CanRx_0x351_IVI_MassageLevel_Req(void)
{
     return b_IVI8_DSM_IVI_MassageLevel_Req_b();
}

/*************************************************************
������������Ħģʽ����
��������: 0x0--0xF
����˵��: 
0x0��Inactive
0x1: ȫ�����
0x2: ȫ����
0x3���粿����
0x4: �粿����
0x5����������
0x6����������
0x7����������
0x8����������
0x9-0x14��Reserved
*************************************************************/
canuint8 CanRx_0x351_IVI_MassageMode_Req(void)
{
     return b_IVI8_DSM_IVI_MassageMode_Req_b();
}

/*************************************************************
������������ǰ��״̬
��������: 0x0--0x1
����˵��: 
0x0:Close
0x1:Open
*************************************************************/
canuint8 CanRx_0x28E_BDC_FLDoorSts(void)
{
     return b_BDC3_BDC_FLDoorSts_b();
}

/*************************************************************
������������ǰ��״̬
��������: 0x0--0x1
����˵��: 
0x0:Close
0x1:Open
*************************************************************/
canuint8 CanRx_0x28E_BDC_FRDoorSts(void)
{
     return b_BDC3_BDC_FRDoorSts_b();
}

/*************************************************************
����������BDCת��Զ������ʻ���μ�������
��������: 0x0--0x7
����˵��: 
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
����������BDCת��Զ�̸���ʻ���μ�������
��������: 0x0--0x7
����˵��: 
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
����������BDCת��Զ������ʻ����ͨ������
��������: 0x0--0x7
����˵��: 
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
����������BDCת��Զ�̸���ʻ����ͨ������
��������: 0x0--0x7
����˵��: 
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
����������TBOXԶ�̷����̼�����������
��������: 0x0--0x3
����˵��: 
0x0:�޶���
0x1:��ʼ
0x2:�ر�
0x3:��Чֵ
*************************************************************/
canuint8 CanRx_0x281_BDC_TBOX_Req_Steeringwheel_heating(void)
{
     return b_BDC5_BDC_TBOX_Req_Steeringwheel_heating_b();
}

/*************************************************************
����������������ѹ��Դ״̬
��������: 0x0--0x7
����˵��: 
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
����������BDC remote control status
BDC TboxԶ�̷�����״̬
��������: 0x0--0x1
����˵��: 
0x0:Not Remote control mode
0x1:Remote control mode
*************************************************************/
canuint8 CanRx_0x283_BDC_TboxRemoteControlSt(void)
{
     return b_BDC6_PEPS1_BDC_TboxRemoteControlSt_b();
}

/*************************************************************
����������Gear selector position
��λ״̬
��������: 0x0--0xF
����˵��: 
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
���������������ź���Ч��
��������: 0x0--0x1
����˵��: 
0x0:valid
0x1:invalid
*************************************************************/
canuint8 CanRx_0x284_ABS_VehicleSpeedValid(void)
{
     return b_ABS1_ABS_VehicleSpeedValid_b();
}

/*************************************************************
����������ABS Vehicle Speed
�����ź�
��������: 0x0--0x8CA0
����˵��: 
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
����������ENG_STA
������״̬��Ϣ
��������: 0x0--0x3
����˵��: 
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
����������Vehicle Running Status
��������״̬
��������: 0x0--0x3
����˵��: 
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
����������Gear Selector Position
��λ״̬
��������: 0x0--0xF
����˵��: 
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
�����������������μ��䷴����Ϣ
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Seat position 1 memory succedλ��1����ɹ�
0x2:Seat position 2 memory succedλ��2����ɹ�
0x3:Seat position 3 memory succedλ��3����ɹ�
0x4:Seat position memory failλ�ü���ʧ��
0x5-0x7:reserved
*************************************************************/
void  CanTx_0x3B2_DSM_FLSeatMemStsAndMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FLSeatMemStsAndMsg(sigData);
}

/*************************************************************
��������������ӭ��״̬����
��������: 0x0--0x3
����˵��: 
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
�����������������μ���1���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����1���óɹ�
0x2:Call Memory Position Faild����1����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����1����ɹ�
0x5:Clean Up Memory Position Faild����1���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM1_FLSeatMem1Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM1_FLSeatMem1Sts(sigData);
}

/*************************************************************
�����������������μ���2���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����2���óɹ�
0x2:Call Memory Position Faild����2����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����2����ɹ�
0x5:Clean Up Memory Position Faild����2���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM2_FLSeatMem2Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FLSeatMem2Sts(sigData);
}

/*************************************************************
�����������������μ���3���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����3���óɹ�
0x2:Call Memory Position Faild����3����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����3����ɹ�
0x5:Clean Up Memory Position Faild����3���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM3_FLSeatMem3Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM3_FLSeatMem3Sts(sigData);
}

/*************************************************************
�����������������μ��䷴����Ϣ
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Seat position 1 memory succedλ��1����ɹ�
0x2:Seat position 2 memory succedλ��2����ɹ�
0x3:Seat position 3 memory succedλ��3����ɹ�
0x4:Seat position memory failλ�ü���ʧ��
0x5-0x7:reserved

*************************************************************/
void  CanTx_0x3B2_DSM_FRSeatMemStsAndMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FRSeatMemStsAndMsg(sigData);
}

/*************************************************************
�����������������μ���1���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����1���óɹ�
0x2:Call Memory Position Faild����1����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����1����ɹ�
0x5:Clean Up Memory Position Faild����1���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM1_FRSeatMem1Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM1_FRSeatMem1Sts(sigData);
}

/*************************************************************
�����������������μ���2���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����2���óɹ�
0x2:Call Memory Position Faild����2����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����2����ɹ�
0x5:Clean Up Memory Position Faild����2���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM2_FRSeatMem2Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FRSeatMem2Sts(sigData);
}

/*************************************************************
�����������������μ���3���÷���
��������: 0x0--0x7
����˵��: 
0x0:Inactive������
0x1:Call Memory Position Succeed����3���óɹ�
0x2:Call Memory Position Faild����3����ʧ��
0x3:Waiting���ڵ���
0x4:Clean Up Memory Position Succeed����3����ɹ�
0x5:Clean Up Memory Position Faild����3���ʧ��
0x6:Reserved
0x7:Invalid��Ч
*************************************************************/
void  CanTx_0x3B2_DSM2_FRSeatMem3Sts(canuint8 sigData)
{
     ILPutTxDSM_DSM2_FRSeatMem3Sts(sigData);
}

/*************************************************************
��������������ӭ��״̬����
��������: 0x0--0x3
����˵��: 
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
�����������������μ���״̬����
��������: 0x0--0x3
����˵��: 
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
�����������������μ��ȵ�λ����
��������: 0x0--0x3
����˵��: 
0x0:Level 1  1��
0x1:Level 2   2��
0x2:Level 3   3��
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatHeatGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatHeatGear(sigData);
}

/*************************************************************
�����������������μ���״̬����
��������: 0x0--0x3
����˵��: 
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
�����������������μ��ȵ�λ����
��������: 0x0--0x3
����˵��: 
0x0:Level 1  1��
0x1:Level 2   2��
0x2:Level 3   3��
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatHeatGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatHeatGear(sigData);
}

/*************************************************************
������������������ͨ��״̬����
��������: 0x0--0x3
����˵��: 
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
������������������ͨ�絵λ����
��������: 0x0--0x3
����˵��: 
0x0:Level 1  1��
0x1:Level 2   2��
0x2:Level 3   3��
*************************************************************/
void  CanTx_0x3B2_DSM_St_DriSeatVentilationGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_DriSeatVentilationGear(sigData);
}

/*************************************************************
������������������ͨ��״̬����
��������: 0x0--0x3
����˵��: 
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
������������������ͨ�絵λ����
��������: 0x0--0x3
����˵��: 
0x0:Level 1  1��
0x1:Level 2   2��
0x2:Level 3   3��
*************************************************************/
void  CanTx_0x3B2_DSM_St_PasSeatVentilationGear(canuint8 sigData)
{
     ILPutTxDSM_DSM_St_PasSeatVentilationGear(sigData);
}

/*************************************************************
�������������ݼ�����ʾ
��������: 0x0--0x1
����˵��: 
0x0��No Change
0x1:Change
*************************************************************/
void  CanTx_0x3B2_DSM_FLSeatPosMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FLSeatPosMsg(sigData);
}

/*************************************************************
�������������ݼ�����ʾ
��������: 0x0--0x1
����˵��: 
0x0��No Change
0x1:Change
*************************************************************/
void  CanTx_0x3B2_DSM_FRSeatPosMsg(canuint8 sigData)
{
     ILPutTxDSM_DSM_FRSeatPosMsg(sigData);
}

/*************************************************************
���������������̼��ȹ���״̬
��������: 0x0--0x3
����˵��: 
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
������������Ħ��λ����
��������: 0x0--0x7
����˵��: 

0X0:OFF
0x1: Level 1
0x2: Level 2
0x3: Level 3
0x4: AUTO  OFF�Զ��ر�
0x5-7��reserved
*************************************************************/
void  CanTx_0x3B2_DSM_MassageLevel_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_MassageLevel_FB(sigData);
}

/*************************************************************
������������Ħģʽ����
��������: 0x0--0xF
����˵��: 
0x0: ȫ�����
0x1: ȫ����
0x2���粿����
0x3: �粿����
0x4����������
0x5����������
0x6����������
0x7����������
0x8��Errorģ�����
0x9-0x14��Reserved
*************************************************************/
void  CanTx_0x3B2_DSM_MassageMode_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_MassageMode_FB(sigData);
}

/*************************************************************
����������С�ģʽ������
��������: 0--0x3
����˵��: 
0x0:Inactive
0x1:�ر�С�ģʽ
0x2:��С�ģʽ
0x3:ERROR
*************************************************************/
void  CanTx_0x3B2_DSM_NapMode_FB(canuint8 sigData)
{
     ILPutTxDSM_DSM_NapMode_FB(sigData);
}


