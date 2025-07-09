/**************************************************************************************************
 * @file        Lin_Cfg.c
 * @brief       LIN���ߵ�������Ϣ��������Դ�ļ�
 * @details     ����LIN���ȱ���Ϣ����LIN�豸����������ȫ�ֱ�����
 *              ����LIN���ڵ�ͨѶ����֧��LIN֡��ʱ�������շ���
 * @author      ssj
 * @date        2025-06-18
 * @version     V1.0
 * @copyright   Copyright (c) 2025 �����Ϸ��¶������������޹�˾����������Ȩ����
 *
 * ----------------------------------------------------------------------------
 * �޸���ʷ:
 * ����        ����        �汾      ����
 * ----------  ----------  -------  -------------------------------------------
 * 2025-06-18  ssj         V1.0     �ļ���������ʼ�汾
 * ----------------------------------------------------------------------------
 **************************************************************************************************/

#include <LdfFile_DSM_TwoInOne_V10.h>
#include <Ecual_linCfg.h>
#include <Mcal_Lin.h>


/*************************************************************************************************
 * Global Variable declaration
 *************************************************************************************************/
unMaster_Request_t LinMsg_SCM_DiagRequest;
unSlave_Response_t LinMsg_SM_DiagResponse;

LinScheduleList_t  ebsLinScheManage[LIN_DOOR_SCHE_MANAGE_LEN] =
{
	/*Msg Id   Schedule Time*/
	{0x1A, D_SCHEDULE_TIME},
	{0x1B, D_SCHEDULE_TIME},
	{0x3C, D_SCHEDULE_TIME},
	{0x3D, D_SCHEDULE_TIME},
};

LinMsgMaxrix_t  ebsLinMsgMaxrix[LIN_DOOR_MSG_MARRIX_LEN] =
{
	/*Id   Pid   Len  Dir   		 Check Mode     Data          State RecvErrTimes MsgType TxAndRxFlag */
	{0x1A, 0x1A, 8,	  EN_LIN_DIR_TX, eLIN_Enhanced, LinMsg_DSM_1_1.buff,  {0,}, 0, 1, 1},
	{0x1B, 0x5B, 8,	  EN_LIN_DIR_RX, eLIN_Enhanced, LinMsg_Massage_1.buff, {0,}, 0, 1, 1},
    //��ϵ���д�����,���ڵ�������ڴ�֮ǰ
    {0x3C, 0x3C, 8,	EN_LIN_DIR_TX, eLIN_Classic, LinMsg_SCM_DiagRequest.buff,  {0,}, 0, 0, 0},
    {0x3D, 0x3D, 8, EN_LIN_DIR_RX, eLIN_Classic, LinMsg_SM_DiagResponse.buff, {0,}, 0, 0, 0},
};

LinDeviceComm_t LinDevCommManage[D_LIN_DEV_ID_LIN1_EN] = {

#if (D_LIN_DEV_ID_LIN1_EN != 0U)
	{
		LIN_DEV1,\
		eLinBaudRate_19200bps
	},
#endif
};

LinTaskManage_t LinTaskManage = {
    0,                                   // ��ǰִ�еĵ��ȱ�����
	LIN_DOOR_SCHE_MANAGE_LEN,            // �����б�������
    (LinScheduleList_t *)&ebsLinScheManage[0], // �����б��׵�ַ
    0,                                   // ���ʱ���
    LIN_DEV1,                            // LIN�豸ID
    FALSE,                               // ��������־
	LIN_DOOR_MSG_MARRIX_LEN,             // ��Ϣ��������
    (LinMsgMaxrix_t *)&ebsLinMsgMaxrix[0], // �����б��׵�ַ
};
