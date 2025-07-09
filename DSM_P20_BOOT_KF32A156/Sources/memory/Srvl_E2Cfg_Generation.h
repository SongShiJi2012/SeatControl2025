/************************************************************************************************
File created time : 2025-06-04 16:32:11
File Name:          Srvl_E2Cfg_Generation.h
Author:             python Script Generation
Description:        E2���ݿ����ö���� - ʹ��excel����й��������ֶ��޸�
************************************************************************************************/



#ifndef _PYTHONE_E2CFG_H_
#define _PYTHONE_E2CFG_H_

#include "Common.h"



/**���ݿ��д����ö��**/
typedef enum _EEPROM_OPT_STA_T
{
    EN_EEPROM_STA_IDLE = 0, /*����*/
    EN_EEPROM_STA_WRITE,    /*д����״̬*/
    EN_EEPROM_STA_READ,     /*������״̬*/
} EepromOptReq;

/**���ݿ��д���ö�ٶ���**/
typedef enum
{
    E2promNullOp  = 0,   /*��ʼ��*/
    E2promWaitIDL,       /*�ȴ�����*/
    E2promOping,         /*������*/
    E2promOpOK,          /*�����ɹ�*/
    E2promOpFail,        /*����ʧ��*/
} enE2promOptResult;

/**���ݿ��������ݽṹ**/
typedef struct EEPROMPARATABLE
{
    INT16U             DataBlockID;         /*ID��ʶ*/
    INT32U             StartAddr;           /*��ʼ��ַ*/
    INT8U              DataLength;          /*���ݳ���*/
    INT16U             BackUpID;            /*�������ݱ�ʶ*/
    INT8U              *pParaBuffer;        /*ָ�������*/
    EepromOptReq       OptReq;              /*��д����״̬*/
    enE2promOptResult  OptResult;           /*��д�������*/
} strEepromDataBlockCfgTable;

/**�Զ���洢�����ݽṹ**/
typedef struct EE_SRV_DATA_TABLE_CFG
{
    INT16U             SrvMemIndex;     /* �Զ���ö�� */
    INT8U              StartOffset;     /* ����洢�����ݿ��ж�ӦRAM��������ʼƫ���� */
    INT8U              len;             /* ����洢���� */
    INT16U             DataBlockID;     /* ���ݿ�ID */
} strEepromDataDefineTable;


#define    D_USEID_NUMBER          6     /* ʹ��ID������ */
#define    D_USEID_NUMBER_NO_BACKUP      3  /* ʹ��ID������ ����������*/
#define    D_NOBACKUP              0     /* �ޱ���*/


#define     D_APP_INIT_Data_Len_4                     4
#define     D_BOOT_INIT_Data_Len_4                    4
#define     D_DareBootVersion_Len_8                   8
#define     D_CustomerBootVersion_Len_15              15

#define     D_APP_ValidFlg_Len_8                      8
#define     D_FingerPrint_ProgramDate_F199_Len_4      4
#define     D_FingerPrint_RepairShopCodeF198_Len_8    8
#define     D_BOOTUdsSecurityAccessTimes_Len_1        1
#define     D_AppUdsSecurityAccessTimes_Len_1         1
#define     D_Reserved0_Len_1                         1

#define     D_AppJumpToBootFlg_Len_1                  1
#define     D_WakeUpSource_Len_1                      1
#define     D_Reserved1_Len_1                         1



typedef enum
{
/********���ݿ�ID_0 ���忪ʼ********/
    #if 0
    D:APP��һ�����б�־ 
    #endif
    EN_MemIndex_APP_INIT_Data = 0, /* D_APP_INIT_Data_Len_4 */
    #if 0
	BOOT��һ�����б�־
    #endif
    EN_MemIndex_BOOT_INIT_Data, /* D_BOOT_INIT_Data_Len_4 */
    #if 0
	�¶�BOOT�汾
    #endif
    EN_MemIndex_DareBootVersion, /* D_DareBootVersion_Len_8 */
    #if 0
	�ͻ�BOOT�汾
    #endif
    EN_MemIndex_CustomerBootVersion, /* D_CustomerBootVersion_Len_15 */
/********���ݿ�ID_0 �������********/

/********���ݿ�ID_1 ���忪ʼ********/
    #if 0
	APP��Ч��־
    #endif
    EN_MemIndex_APP_ValidFlg, /* D_APP_ValidFlg_Len_8 */
    #if 0
	ˢдά������
    #endif
    EN_MemIndex_FingerPrint_ProgramDate_F199, /* D_FingerPrint_ProgramDate_F199_Len_4 */
    #if 0
	�ۺ�ά�޵����
    #endif
    EN_MemIndex_FingerPrint_RepairShopCodeF198, /* D_FingerPrint_RepairShopCodeF198_Len_8 */
    #if 0
	BOOT��ȫ���ʴ���
    #endif
    EN_MemIndex_BOOTUdsSecurityAccessTimes, /* D_BOOTUdsSecurityAccessTimes_Len_1 */
    #if 0
	App��ȫ���ʴ���
    #endif
    EN_MemIndex_AppUdsSecurityAccessTimes, /* D_AppUdsSecurityAccessTimes_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved0, /* D_Reserved0_Len_1 */
/********���ݿ�ID_1 �������********/

/********���ݿ�ID_2 ���忪ʼ********/
    #if 0
	������ת��־
    #endif
    EN_MemIndex_AppJumpToBootFlg, /* D_AppJumpToBootFlg_Len_1 */
    #if 0
	����Դ
    #endif
    EN_MemIndex_WakeUpSource, /* D_WakeUpSource_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved1, /* D_Reserved1_Len_1 */
/********���ݿ�ID_2 �������********/
    EN_MemIndex_Max
} enSrvMemIndex;



/***д�볣�ú�������***/
extern strEepromDataBlockCfgTable * Eel_GetE2DataBlockCfgTablePtr(void);
extern INT16U Srvl_GetE2DataBlockCfgTableLength(void);
extern strEepromDataDefineTable * Eel_GetE2DataDefineTablePtr(void);
extern INT16U Srvl_GetE2DataDefineTableLength(void);
extern void Srvl_SetE2DataBlockOptResult(INT16U DataId, enE2promOptResult Result);
extern enE2promOptResult Srvl_GetE2DataBlockOptResult(INT16U DataId);
extern void Srvl_SetE2DataBlockOptReq(INT16U DataId, EepromOptReq Req);
extern EepromOptReq Srvl_GetE2DataBlockEepOptReq(INT16U DataId);
extern INT8U * Srvl_GetE2DataBlockBufferPtr(INT16U DataId);
extern INT8U Srvl_GetE2DataBlockLength(INT16U DataId);
extern INT32U Srvl_GetE2DataBlockStartAddr(INT16U DataId);
extern INT16U Srvl_GetE2DataBlockBackUpID(INT16U DataId);
extern INT16U Srvl_GetE2DefineDataBlockID(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineLen(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineStartOffset(enSrvMemIndex MemIndex);
extern INT16U Srvl_GetUseDataBlockID(INT16U Index);
extern INT16U Srvl_GetUseDataBlockIDNoBackUp(INT16U Index);

#endif
