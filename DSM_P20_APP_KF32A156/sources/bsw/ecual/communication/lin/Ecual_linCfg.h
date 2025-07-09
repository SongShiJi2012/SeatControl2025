#ifndef SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_
#define SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_
/*
 * Ecual_linCfg.h
 *
 *  Created on: 2025��6��18��
 *      Author: Administrator
 */


#include <Mcal_Lin.h>
#include  "Common.h"

#define D_LIN_POLL_EN                 (1U)
#define D_SCHEDULE_TIME               (10U)
#define ECUAL_LIN_TIMEOUT_MAX         (100U)     /* ��ʱʱ�� */

#define D_LIN_DEV_ID_LIN1_EN          (1U)

#define LIN_DOOR_SCHE_MANAGE_LEN      (4)   /* LIN���ȱ����鳤�� */
#define LIN_DOOR_MSG_MARRIX_LEN       (4)   /* LIN��Ϣ�������鳤�� */



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
	INT8U LinMsg_Ovf : 1;			/*!< lin���͹��ر�־ */
	INT8U LinMsg_TimOut : 1;		/*!< lin��ʱ */
	INT8U LinMsg_NewFlg : 1;		/*!< lin���յ����ݱ�־����δУ�� */
	INT8U LinMsg_RxVaildFlg : 1;	/*!< lin���յ�����ͨ��У�� */
	INT8U LinMsg_WaitRev : 1;		/*!< lin��ʼ�ȴ��ӻ���Ӧ��־ */
	INT8U LinMsg_TxErrFlg : 1;		/*!< lin���͹����д����־ */
	INT8U LinMsg_ChkErrFlg : 1; 	/*!< linУ������־ */
	INT8U LinMsg_Resv : 1;
}LinMsgStaBit_t;

/**
 * @brief LIN��Ϣ������Ϣ���Ա�
 *
 * ���ṹ���������ڶ���LINЭ������֧�ֵ���Ϣ��֡������ϸ���ԡ�
 * ÿһ���������ϢID������������PID�����ȡ�У�顢���ݻ��塢״̬�ȡ�
 *
 * ���Ŀ�ģ�
 *   - ���д��ÿ��LIN��Ϣ���շ���ʽ�����ݡ���ز�����
 *   - ����ͨ����ϢID���ٲ��ҡ������Ӧ��Ϣ��
 *   - ֧�ֶ���������Ϣ������֡���¼�֡�����֡�ȣ���������á�
 *
 * ʹ��˵����
 *   - ���ȱ��ֵ�ĳ��ϢIDʱ������idMessage�ڱ����в��Ҷ�Ӧ�
 *     ������MsgDir/MsgType�Ȳ�����ִ��ʵ�ʵ�LIN��/����Э�鴦��
 *   - ����һ�㰴����Э��֧�ֵ���ϢID�������У�˳�������ȱ�ͬ��
 *
 * ���ͳ�Ա˵����
 *   - idMessage  ����ϢID���͵��ȱ����idMessage��Ӧ
 *   - PidMessage ��PID��Э�鴫��ʵ��ʹ��
 *   - MsgDir     ������TX/���ͻ�RX/����
 *   - Buffer     ����Ϣ������ָ��
 *   - MsgType    ����Ϣ���ͣ�0�¼�֡��1����֡��
 *   - TxAndRxFlag������Ϣ��ǰ�Ƿ�ʹ��
 */
typedef struct _LIN_MSG_MAXRIX
{
    INT8U idMessage;              // ��ϢID
    INT8U PidMessage;             // Э��PID
    INT8U MsgDlc;                 // ���ݳ���
    LinDataDir_t MsgDir;          // ���䷽��
    LinCheckSumType_t MsgChkSum;  // У�������
    INT8U *Buffer;                // ���ݻ�����ָ��
    LinMsgStaBit_t MsgSt;         // ��Ϣ����״̬
    INT32U RecvErrTimes;          // ���մ������
    INT8U MsgType;                // ��Ϣ���ͣ�0�¼�֡��1����֡��
    INT8U TxAndRxFlag;            // ���ͻ����ʹ�ܱ�־
} LinMsgMaxrix_t;

/**
 * @brief LIN���ȱ�
 *
 * ���ṹ���������ڶ���LINЭ��ġ����ȱ���Schedule Table����
 * ���ȱ��ÿһ��ֻ��������ϢID���͡��������ڡ�����������
 *   - ��ʲô˳��ʲôʱ������ѯ/����ÿһ��LIN��Ϣ��֡����
 *
 * ���Ŀ�ģ�
 *   - ���ȱ�ֻ��ע����ʱ�������ĸ���Ϣ������������Ϣ����ϸ�ڣ�
 *   - ����������Ϣ��ѯ˳������ڣ�����������Ϣ��������ԣ�
 *   - ������֧�ָ��ӵ��ȣ������֡��Ӧ��֡��ϡ���ͬ���ȼ��ȣ���
 *
 * ʹ��˵����
 *   - ��ѯ����ʱ����������ȡ��idMessage����ȥ��Ϣ�����в�����ϸ���ԡ�
 *   - ֻҪ���ı���˳������ڲ���������������LIN������Ϊ������Ķ���Ϣ��
 */
typedef struct _DOOR_LIN_SCHEDULE_LIST_T
{
    INT8U idMessage;      // Ҫ���ȵ�LIN��ϢID
    INT16U DelayTime;     // �������ڣ���λms
} LinScheduleList_t;
/**
 * @brief
 * Ϊʲô���ȱ����Ϣ����Ҫ�ֿ���ƣ�
 *
 * 1. ְ����룺
 *    - ���ȱ�ֻ����������˳������ڡ�����������Ϣϸ�ڣ�����������ͨѶ���ࡣ
 *    - ��Ϣ������ϸ����ÿ����Ϣ�����Ժ��շ���ʽ�����ڼ��й����ά����
 *
 * 2. �����������
 *    - ���ȱ���Ը���Ӧ������������ɾ������˳���޸ĵ������ڣ������޸���Ϣ�����ݡ�
 *    - ��Ϣ��Ҳ������ʱ��չ���޸���Ϣ���ԣ���Ӱ������߼���
 *
 * 3. ����Э��������ά����
 *    - �������֡������֡��ֻ���ڵ��ȱ����Ϣ��ֱ�Ǽǣ�����Ӱ�죬ά����㡣
 *
 * 4. ����ʵ�ָ�Ч��
 *    - ��ѭ��ֻ�谴���ȱ���ѯ����idMessageȥ��Ϣ�������ϸ���ݼ��ɣ��ṹ������Ч�ʸߡ�
 *
 * ���ۣ����ȱ����Ϣ������Զ������ǹ�ҵ��������LINЭ��ջ��Ʒ�ʽ���ɿ�������ά����
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
	INT8U 				Index;			/*��ǰִ���б���*/
	INT8U				SumCnt;			/*ÿһ·�б��ܵĸ���*/
	LinScheduleList_t	*LinScheList;	/*�����б�ָ��*/
	INT32U				TimeTick;		/*ÿ��ִ�еļ��ʱ��*/
	LinChlIdx_t			DeviceId;		/*�豸ID ��Ӧ��LIN����*/
	BOOL				IsHandUp;		/*�����Ƿ����*/
	INT8U				MsgCnt;			/*ÿһ����Ϣ������������������*/
	LinMsgMaxrix_t		*LinMaxrixList;	/*��Ϣ����ָ��*/
}LinTaskManage_t;

typedef struct _LIN_COMM_MSG_T_
{
	LinChlIdx_t 	DevId;
	INT8U 			idMessage;
	INT8U 			*buffer;
	INT16U 			len;
}LinCommMsg_t;


#endif /* SOURCES_BSW_ECUAL_COMMUNICATION_LIN_ECUAL_LINCFG_H_ */
