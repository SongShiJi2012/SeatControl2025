#ifndef SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_
#define SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_
/*
 * Ecual_linCfg.h
 *
 *  Created on: 2025年6月18日
 *      Author: Administrator
 */


#include <Mcal_Lin.h>
#include  "Common.h"

#define D_LIN_POLL_EN                 (1U)
#define D_SCHEDULE_TIME               (10U)
#define ECUAL_LIN_TIMEOUT_MAX         (100U)     /* 超时时间 */

#define D_LIN_DEV_ID_LIN1_EN          (1U)

#define LIN_DOOR_SCHE_MANAGE_LEN      (4)   /* LIN调度表数组长度 */
#define LIN_DOOR_MSG_MARRIX_LEN       (4)   /* LIN消息矩阵数组长度 */



typedef enum _LIN_CHECK_SUM_TYPE_T
{
    EN_LIN_CLASS_CHK_SUM = 0,
    EN_LIN_ENHENCE_CHK_SUM
}LinChkSumType_t;

typedef enum _LIN_DATA_DIR_T
{
    EN_LIN_DIR_TX = 0,
    EN_LIN_DIR_RX
}LinDataDir_t;

typedef struct _LIN_MSG_ST_T
{
	INT8U LinMsg_Ovf : 1;			/*!< lin发送过载标志 */
	INT8U LinMsg_TimOut : 1;		/*!< lin超时 */
	INT8U LinMsg_NewFlg : 1;		/*!< lin接收到数据标志，但未校验 */
	INT8U LinMsg_RxVaildFlg : 1;	/*!< lin接收到数据通过校验 */
	INT8U LinMsg_WaitRev : 1;		/*!< lin开始等待从机响应标志 */
	INT8U LinMsg_TxErrFlg : 1;		/*!< lin发送过程中错误标志 */
	INT8U LinMsg_ChkErrFlg : 1; 	/*!< lin校验错误标志 */
	INT8U LinMsg_Resv : 1;
}LinMsgStaBit_t;

/**
 * @brief LIN消息矩阵（消息属性表）
 *
 * 本结构体数组用于定义LIN协议所有支持的消息（帧）的详细属性。
 * 每一项不仅包括消息ID，还包含方向、PID、长度、校验、数据缓冲、状态等。
 *
 * 设计目的：
 *   - 集中存放每个LIN消息的收发方式、内容、相关参数；
 *   - 方便通过消息ID快速查找、处理对应消息；
 *   - 支持多种类型消息（周期帧、事件帧、诊断帧等）的灵活配置。
 *
 * 使用说明：
 *   - 调度表轮到某消息ID时，根据idMessage在本表中查找对应项，
 *     再依据MsgDir/MsgType等参数，执行实际的LIN收/发和协议处理。
 *   - 本表一般按所有协议支持的消息ID完整罗列，顺序可与调度表不同。
 *
 * 典型成员说明：
 *   - idMessage  ：消息ID，和调度表里的idMessage对应
 *   - PidMessage ：PID，协议传输实际使用
 *   - MsgDir     ：方向，TX/发送或RX/接收
 *   - Buffer     ：消息缓冲区指针
 *   - MsgType    ：消息类型（0事件帧，1周期帧）
 *   - TxAndRxFlag：该消息当前是否使能
 */
typedef struct _LIN_MSG_MAXRIX
{
    INT8U idMessage;              // 消息ID
    INT8U PidMessage;             // 协议PID
    INT8U MsgDlc;                 // 数据长度
    LinDataDir_t MsgDir;          // 传输方向
    LinCheckSumType_t MsgChkSum;  // 校验和类型
    INT8U *Buffer;                // 数据缓冲区指针
    LinMsgStaBit_t MsgSt;         // 消息传输状态
    INT32U RecvErrTimes;          // 接收错误计数
    INT8U MsgType;                // 消息类型（0事件帧，1周期帧）
    INT8U TxAndRxFlag;            // 发送或接收使能标志
} LinMsgMaxrix_t;

/**
 * @brief LIN调度表
 *
 * 本结构体数组用于定义LIN协议的“调度表”（Schedule Table）。
 * 调度表的每一项只包含“消息ID”和“调度周期”，即描述：
 *   - 按什么顺序、什么时间间隔轮询/调度每一条LIN消息（帧）。
 *
 * 设计目的：
 *   - 调度表只关注“何时、调度哪个消息”，不包含消息内容细节；
 *   - 可以灵活安排消息轮询顺序和周期，不依赖于消息本身的属性；
 *   - 有利于支持复杂调度（如诊断帧、应用帧混合、不同优先级等）。
 *
 * 使用说明：
 *   - 轮询调度时，遍历本表，取出idMessage，再去消息矩阵中查找详细属性。
 *   - 只要更改本表顺序或周期参数，即可灵活调整LIN调度行为，无需改动消息表。
 */
typedef struct _DOOR_LIN_SCHEDULE_LIST_T
{
    INT8U idMessage;      // 要调度的LIN消息ID
    INT16U DelayTime;     // 调度周期，单位ms
} LinScheduleList_t;
/**
 * @brief
 * 为什么调度表和消息矩阵要分开设计？
 *
 * 1. 职责分离：
 *    - 调度表只描述“调度顺序和周期”，不关心消息细节，便于灵活控制通讯节奏。
 *    - 消息矩阵详细描述每个消息的属性和收发方式，便于集中管理和维护。
 *
 * 2. 灵活性提升：
 *    - 调度表可以根据应用需求任意增删、调整顺序、修改调度周期，无需修改消息表内容。
 *    - 消息表也可以随时扩展或修改消息属性，不影响调度逻辑。
 *
 * 3. 便于协议升级和维护：
 *    - 增加诊断帧或特殊帧，只需在调度表和消息表分别登记，互不影响，维护简便。
 *
 * 4. 代码实现高效：
 *    - 主循环只需按调度表轮询，按idMessage去消息矩阵查详细内容即可，结构清晰，效率高。
 *
 * 结论：调度表和消息矩阵各自独立，是工业界主流的LIN协议栈设计方式，可靠、灵活、易维护。
 */


typedef struct
{
	uint8_t MasterReqB0			: 8;
	uint8_t MasterReqB1			: 8;
	uint8_t MasterReqB2			: 8;
	uint8_t MasterReqB3			: 8;
	uint8_t MasterReqB4			: 8;
	uint8_t MasterReqB5			: 8;
	uint8_t MasterReqB6			: 8;
	uint8_t MasterReqB7			: 8;
}Master_Request;
typedef union
{
	uint8_t buff[8];
	Master_Request Bit;
}unMaster_Request_t;
typedef struct
{
	uint8_t SlaveRespB0			: 8;
	uint8_t SlaveRespB1			: 8;
	uint8_t SlaveRespB2			: 8;
	uint8_t SlaveRespB3			: 8;
	uint8_t SlaveRespB4			: 8;
	uint8_t SlaveRespB5			: 8;
	uint8_t SlaveRespB6			: 8;
	uint8_t SlaveRespB7			: 8;
}Slave_Response;
typedef union
{
	uint8_t buff[8];
	Slave_Response Bit;
}unSlave_Response_t;

typedef struct LIN_TASKS_MANAGE_T
{
	INT8U 				Index;			/*当前执行列表项*/
	INT8U				SumCnt;			/*每一路列表总的个数*/
	LinScheduleList_t	*LinScheList;	/*调度列表指针*/
	INT32U				TimeTick;		/*每项执行的间隔时间*/
	LinChlIdx_t			DeviceId;		/*设备ID 对应的LIN索引*/
	BOOL				IsHandUp;		/*任务是否挂起*/
	INT8U				MsgCnt;			/*每一个消息矩阵包含的数据项个数*/
	LinMsgMaxrix_t		*LinMaxrixList;	/*消息矩阵指针*/
}LinTaskManage_t;

typedef struct _LIN_COMM_MSG_T_
{
	LinChlIdx_t 	DevId;
	INT8U 			idMessage;
	INT8U 			*buffer;
	INT16U 			len;
}LinCommMsg_t;


#endif /* SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_ */
