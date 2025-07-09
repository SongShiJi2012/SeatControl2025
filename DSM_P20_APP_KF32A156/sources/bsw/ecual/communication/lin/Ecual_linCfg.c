/**************************************************************************************************
 * @file        Lin_Cfg.c
 * @brief       LIN总线调度与消息矩阵配置源文件
 * @details     定义LIN调度表、消息矩阵、LIN设备及任务管理等全局变量。
 *              用于LIN主节点通讯管理，支持LIN帧定时调度与收发。
 * @author      ssj
 * @date        2025-06-18
 * @version     V1.0
 * @copyright   Copyright (c) 2025 深圳南方德尔汽车电子有限公司。保留所有权利。
 *
 * ----------------------------------------------------------------------------
 * 修改历史:
 * 日期        作者        版本      描述
 * ----------  ----------  -------  -------------------------------------------
 * 2025-06-18  ssj         V1.0     文件创建，初始版本
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
    //诊断调度写在最后,周期调度添加在此之前
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
    0,                                   // 当前执行的调度表索引
	LIN_DOOR_SCHE_MANAGE_LEN,            // 调度列表总项数
    (LinScheduleList_t *)&ebsLinScheManage[0], // 调度列表首地址
    0,                                   // 间隔时间戳
    LIN_DEV1,                            // LIN设备ID
    FALSE,                               // 任务挂起标志
	LIN_DOOR_MSG_MARRIX_LEN,             // 消息矩阵项数
    (LinMsgMaxrix_t *)&ebsLinMsgMaxrix[0], // 调度列表首地址
};
