/************************************************************************************************
File created time : 2025-06-26 15:02:03
File Name:          Srvl_E2Cfg_Generation.h
Author:             python Script Generation
Description:        E2���ݿ����ö���� - ʹ��excel����й��������ֶ��޸�
/************************************************************************************************/



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
    INT8U              PreWriteFlg;         /*Ԥд���־*/
} strEepromDataBlockCfgTable;

/**�Զ���洢�����ݽṹ**/
typedef struct EE_SRV_DATA_TABLE_CFG
{
    INT16U             SrvMemIndex;     /* �Զ���ö�� */
    INT8U              StartOffset;     /* ����洢�����ݿ��ж�ӦRAM��������ʼƫ���� */
    INT8U              len;             /* ����洢���� */
    INT16U             DataBlockID;     /* ���ݿ�ID */
} strEepromDataDefineTable;


#define    D_USEID_NUMBER                68          /* ʹ��ID������ */
#define    D_USEID_NUMBER_NO_BACKUP      34  /* ʹ��ID������ ����������*/
#define    D_NOBACKUP              0xFFFF      /* �ޱ��� */


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

/********���ݿ�ID_28 ���忪ʼ********/
    #if 0
	���ݸ߶ȵ�ǰ������
    #endif
    EN_MemIndex_DrCurHallCnt_Height, /* D_DrCurHallCnt_Height_Len_2 */
    #if 0
	��������ǰ������
    #endif
    EN_MemIndex_DrCurHallCnt_Length, /* D_DrCurHallCnt_Length_Len_2 */
    #if 0
	���ݿ�����ǰ������
    #endif
    EN_MemIndex_DrCurHallCnt_Back, /* D_DrCurHallCnt_Back_Len_2 */
    #if 0
	�������е�ǰ������
    #endif
    EN_MemIndex_DrCurHallCnt_Front, /* D_DrCurHallCnt_Front_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved2, /* D_Reserved2_Len_3 */
/********���ݿ�ID_28 �������********/

/********���ݿ�ID_29 ���忪ʼ********/
    #if 0
	���ݸ߶�Ӳֹ������
    #endif
    EN_MemIndex_DrHardStopPos_Height, /* D_DrHardStopPos_Height_Len_2 */
    #if 0
	��������Ӳֹ������
    #endif
    EN_MemIndex_DrHardStopPos_Length, /* D_DrHardStopPos_Length_Len_2 */
    #if 0
	���ݿ���Ӳֹ������
    #endif
    EN_MemIndex_DrHardStopPos_Back, /* D_DrHardStopPos_Back_Len_2 */
    #if 0
	��������Ӳֹ������
    #endif
    EN_MemIndex_DrHardStopPos_Front, /* D_DrHardStopPos_Front_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved3, /* D_Reserved3_Len_3 */
/********���ݿ�ID_29 �������********/

/********���ݿ�ID_30 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��1
    #endif
    EN_MemIndex_DrMem1_Height, /* D_DrMem1_Height_Len_2 */
    #if 0
	�����������λ��1
    #endif
    EN_MemIndex_DrMem1_Length, /* D_DrMem1_Length_Len_2 */
    #if 0
	���ݿ�������λ��1
    #endif
    EN_MemIndex_DrMem1_Back, /* D_DrMem1_Back_Len_2 */
    #if 0
	�������м���λ��1
    #endif
    EN_MemIndex_DrMem1_Front, /* D_DrMem1_Front_Len_2 */
    #if 0
	���ݼ���1��Ч��־
    #endif
    EN_MemIndex_DrMem1_ValidFlag, /* D_DrMem1_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved4, /* D_Reserved4_Len_2 */
/********���ݿ�ID_30 �������********/

/********���ݿ�ID_31 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��2
    #endif
    EN_MemIndex_DrMem2_Height, /* D_DrMem2_Height_Len_2 */
    #if 0
	�����������λ��2
    #endif
    EN_MemIndex_DrMem2_Length, /* D_DrMem2_Length_Len_2 */
    #if 0
	���ݿ�������λ��2
    #endif
    EN_MemIndex_DrMem2_Back, /* D_DrMem2_Back_Len_2 */
    #if 0
	�������м���λ��2
    #endif
    EN_MemIndex_DrMem2_Front, /* D_DrMem2_Front_Len_2 */
    #if 0
	���ݼ���2��Ч��־
    #endif
    EN_MemIndex_DrMem2_ValidFlag, /* D_DrMem2_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved5, /* D_Reserved5_Len_2 */
/********���ݿ�ID_31 �������********/

/********���ݿ�ID_32 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��3
    #endif
    EN_MemIndex_DrMem3_Height, /* D_DrMem3_Height_Len_2 */
    #if 0
	�����������λ��3
    #endif
    EN_MemIndex_DrMem3_Length, /* D_DrMem3_Length_Len_2 */
    #if 0
	���ݿ�������λ��3
    #endif
    EN_MemIndex_DrMem3_Back, /* D_DrMem3_Back_Len_2 */
    #if 0
	�������м���λ��3
    #endif
    EN_MemIndex_DrMem3_Front, /* D_DrMem3_Front_Len_2 */
    #if 0
	���ݼ���3��Ч��־
    #endif
    EN_MemIndex_DrMem3_ValidFlag, /* D_DrMem3_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved6, /* D_Reserved6_Len_2 */
/********���ݿ�ID_32 �������********/

/********���ݿ�ID_33 ���忪ʼ********/
    #if 0
	���ݸ߶�����С��λλ��
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Height, /* D_DrRes_ReCallPosi_Height_Len_2 */
    #if 0
	������������С��λλ��
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Length, /* D_DrRes_ReCallPosi_Length_Len_2 */
    #if 0
	���ݿ�������С��λλ��
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Back, /* D_DrRes_ReCallPosi_Back_Len_2 */
    #if 0
	������������С��λλ��
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Front, /* D_DrRes_ReCallPosi_Front_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved7, /* D_Reserved7_Len_3 */
/********���ݿ�ID_33 �������********/

/********���ݿ�ID_34 ���忪ʼ********/
    #if 0
	���ݸ߶ȵ�ǰ������
    #endif
    EN_MemIndex_PaCurHallCnt_Height, /* D_PaCurHallCnt_Height_Len_2 */
    #if 0
	��������ǰ������
    #endif
    EN_MemIndex_PaCurHallCnt_Length, /* D_PaCurHallCnt_Length_Len_2 */
    #if 0
	���ݿ�����ǰ������
    #endif
    EN_MemIndex_PaCurHallCnt_Back, /* D_PaCurHallCnt_Back_Len_2 */
    #if 0
	�������е�ǰ������
    #endif
    EN_MemIndex_PaCurHallCnt_Front, /* D_PaCurHallCnt_Front_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved8, /* D_Reserved8_Len_3 */
/********���ݿ�ID_34 �������********/

/********���ݿ�ID_35 ���忪ʼ********/
    #if 0
	���ݸ߶�Ӳֹ������
    #endif
    EN_MemIndex_PaHardStopPos_Height, /* D_PaHardStopPos_Height_Len_2 */
    #if 0
	��������Ӳֹ������
    #endif
    EN_MemIndex_PaHardStopPos_Length, /* D_PaHardStopPos_Length_Len_2 */
    #if 0
	���ݿ���Ӳֹ������
    #endif
    EN_MemIndex_PaHardStopPos_Back, /* D_PaHardStopPos_Back_Len_2 */
    #if 0
	��������Ӳֹ������
    #endif
    EN_MemIndex_PaHardStopPos_Front, /* D_PaHardStopPos_Front_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved9, /* D_Reserved9_Len_3 */
/********���ݿ�ID_35 �������********/

/********���ݿ�ID_36 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��1
    #endif
    EN_MemIndex_PaMem1_Height, /* D_PaMem1_Height_Len_2 */
    #if 0
	�����������λ��1
    #endif
    EN_MemIndex_PaMem1_Length, /* D_PaMem1_Length_Len_2 */
    #if 0
	���ݿ�������λ��1
    #endif
    EN_MemIndex_PaMem1_Back, /* D_PaMem1_Back_Len_2 */
    #if 0
	�������м���λ��1
    #endif
    EN_MemIndex_PaMem1_Front, /* D_PaMem1_Front_Len_2 */
    #if 0
	���ݼ���1��Ч��־
    #endif
    EN_MemIndex_PaMem1_ValidFlag, /* D_PaMem1_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved10, /* D_Reserved10_Len_2 */
/********���ݿ�ID_36 �������********/

/********���ݿ�ID_37 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��2
    #endif
    EN_MemIndex_PaMem2_Height, /* D_PaMem2_Height_Len_2 */
    #if 0
	�����������λ��2
    #endif
    EN_MemIndex_PaMem2_Length, /* D_PaMem2_Length_Len_2 */
    #if 0
	���ݿ�������λ��2
    #endif
    EN_MemIndex_PaMem2_Back, /* D_PaMem2_Back_Len_2 */
    #if 0
	�������м���λ��2
    #endif
    EN_MemIndex_PaMem2_Front, /* D_PaMem2_Front_Len_2 */
    #if 0
	���ݼ���2��Ч��־
    #endif
    EN_MemIndex_PaMem2_ValidFlag, /* D_PaMem2_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved11, /* D_Reserved11_Len_2 */
/********���ݿ�ID_37 �������********/

/********���ݿ�ID_38 ���忪ʼ********/
    #if 0
	���ݸ߶ȼ���λ��3
    #endif
    EN_MemIndex_PaMem3_Height, /* D_PaMem3_Height_Len_2 */
    #if 0
	�����������λ��3
    #endif
    EN_MemIndex_PaMem3_Length, /* D_PaMem3_Length_Len_2 */
    #if 0
	���ݿ�������λ��3
    #endif
    EN_MemIndex_PaMem3_Back, /* D_PaMem3_Back_Len_2 */
    #if 0
	�������м���λ��3
    #endif
    EN_MemIndex_PaMem3_Front, /* D_PaMem3_Front_Len_2 */
    #if 0
	���ݼ���3��Ч��־
    #endif
    EN_MemIndex_PaMem3_ValidFlag, /* D_PaMem3_ValidFlag_Len_1 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved12, /* D_Reserved12_Len_2 */
/********���ݿ�ID_38 �������********/

/********���ݿ�ID_39 ���忪ʼ********/
    #if 0
	����ӭ���������Ŀ��λ��
    #endif
    EN_MemIndex_DrWelcome_LenTar_BackWard, /* D_DrWelcome_LenTar_BackWard_Len_2 */
    #if 0
	����ӭ������ǰ��Ŀ��λ��
    #endif
    EN_MemIndex_DrWelcome_LenTar_ForWard, /* D_DrWelcome_LenTar_ForWard_Len_2 */
    #if 0
	����ӭ���������Ŀ��λ��
    #endif
    EN_MemIndex_PaWelcome_LenTar_BackWard, /* D_PaWelcome_LenTar_BackWard_Len_2 */
    #if 0
	����ӭ������ǰ��Ŀ��λ��
    #endif
    EN_MemIndex_PaWelcome_LenTar_ForWard, /* D_PaWelcome_LenTar_ForWard_Len_2 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved13, /* D_Reserved13_Len_3 */
/********���ݿ�ID_39 �������********/

/********���ݿ�ID_42 ���忪ʼ********/
    #if 0
	�������ε�������
	0x00:�ֶ�����
	0x01:������
	0x02:ʮ������
    #endif
    EN_MemIndex_DrAdjustConfig, /* D_DrAdjustConfig_Len_1 */
    #if 0
	�������ε�������
	0x00:�ֶ�����
	0x01:������
    #endif
    EN_MemIndex_PaAdjustConfig, /* D_PaAdjustConfig_Len_1 */
    #if 0
	����ͨ���������
	0:������
	1������
    #endif
    EN_MemIndex_DrVentAndHeatConfig, /* D_DrVentAndHeatConfig_Len_1 */
    #if 0
	���ݼ���ӭ������
	0:������
	2������
    #endif
    EN_MemIndex_DrMemoryConfig, /* D_DrMemoryConfig_Len_1 */
    #if 0
	����ͨ���������
	0:������
	2������
    #endif
    EN_MemIndex_PaVentAndHeatConfig, /* D_PaVentAndHeatConfig_Len_1 */
    #if 0
	���ݼ���ӭ������
	0:������
	3������
    #endif
    EN_MemIndex_PaMemoryConfig, /* D_PaMemoryConfig_Len_1 */
    #if 0
	��Ħ��������
	0:������
	4������
    #endif
    EN_MemIndex_MassageConfig, /* D_MassageConfig_Len_1 */
    #if 0
	������������Ԥ��byte0
    #endif
    EN_MemIndex_VehicleConfigReserveByte0, /* D_VehicleConfigReserveByte0_Len_1 */
    #if 0
	������������Ԥ��byte1
    #endif
    EN_MemIndex_VehicleConfigReserveByte1, /* D_VehicleConfigReserveByte1_Len_1 */
    #if 0
	������������Ԥ��byte2
    #endif
    EN_MemIndex_VehicleConfigReserveByte2, /* D_VehicleConfigReserveByte2_Len_1 */
    #if 0
	���ͣ�C62X��C52X��
	0��P20����
	1��BM400����
    #endif
    EN_MemIndex_Heat_CarType, /* D_Heat_CarType_Len_1 */
    #if 0
	����Զ��ʹ������
	0����Զ��ʹ��
	1����Զ��ʹ��
    #endif
    EN_MemIndex_Heat_RemoteEnableConfig, /* D_Heat_RemoteEnableConfig_Len_1 */
    #if 0
	���ȷ�����ʹ������
	0���޷�����ʹ��
	1���з�����ʹ��
    #endif
    EN_MemIndex_Heat_PlatformEngineEnableConfig, /* D_Heat_PlatformEngineEnableConfig_Len_1 */
    #if 0
	����P20PHEV������ʹ������
	0���޼���P20PHEV������
	1���м���P20PHEV������
    #endif
    EN_MemIndex_Heat_P20_PHEV_EngineCfg, /* D_Heat_P20_PHEV_EngineCfg_Len_1 */
    #if 0
	���ȳ�ʱʹ������
	0������
	1��ʹ��
    #endif
    EN_MemIndex_Heat_TimeOutPrm, /* D_Heat_TimeOutPrm_Len_1 */
/********���ݿ�ID_42 �������********/

/********���ݿ�ID_43 ���忪ʼ********/
    #if 0
	���ȳ�ʱʱ������
	0���޳�ʱ
	1��10min
	2��20min
    #endif
    EN_MemIndex_Heat_RunMaxTime, /* D_Heat_RunMaxTime_Len_1 */
    #if 0
	�ɲⱨ�ķ��ͱ�־
	0���ɲⱨ�ķ��ͽ���
	1���ɲⱨ�ķ���ʹ��
    #endif
    EN_MemIndex_SendTestMsgFlg, /* D_SendTestMsgFlg_Len_1 */
    #if 0
	ͨ�糬ʱʹ������
	0������
	1��ʹ��
    #endif
    EN_MemIndex_Vent_TimeOutPrm, /* D_Vent_TimeOutPrm_Len_1 */
    #if 0
	ͨ�糬ʱʱ������
	0���޳�ʱ
	1��10min
	2��20min
    #endif
    EN_MemIndex_Vent_RunMaxTime, /* D_Vent_RunMaxTime_Len_1 */
    #if 0
	��ֹ�������ڴ���
    #endif
    EN_MemIndex_MotorSoftStopCntMax, /* D_MotorSoftStopCntMax_Len_1 */
    #if 0
	���ݸ߶ȵ�����ֹ�����
    #endif
    EN_MemIndex_DrHeightSoftStopCnt, /* D_DrHeightSoftStopCnt_Len_1 */
    #if 0
	�������򵽴���ֹ�����
    #endif
    EN_MemIndex_DrLengthSoftStopCnt, /* D_DrLengthSoftStopCnt_Len_1 */
    #if 0
	���ݿ���������ֹ�����
    #endif
    EN_MemIndex_DrBackSoftStopCnt, /* D_DrBackSoftStopCnt_Len_1 */
    #if 0
	�������е�����ֹ�����
    #endif
    EN_MemIndex_DrFrontSoftStopCnt, /* D_DrFrontSoftStopCnt_Len_1 */
    #if 0
	����дӲ���汾�ű�־
    #endif
    EN_MemIndex_Write_HardwareVersion_Flg, /* D_Write_HardwareVersion_Flg_Len_1 */
    #if 0
	ӭ��״̬
	0����Ч��
	1�����ƣ�
	2��ǰ�ơ�
    #endif
    EN_MemIndex_WelcomeStatus, /* D_WelcomeStatus_Len_1 */
    #if 0
	����ӭ��λ�ø��±�־:
	0��������
	1������
    #endif
    EN_MemIndex_WelcomeDrUpate, /* D_WelcomeDrUpate_Len_1 */
    #if 0
	������������ʹ������
	 0������������״̬�ж�ʹ��
	 1������������״̬�ж�ʹ��
    #endif
    EN_MemIndex_Heat_PlatFormVehicleEnableConfig, /* D_Heat_PlatFormVehicleEnableConfig_Len_1 */
    #if 0
	������������Ԥ��byte3
    #endif
    EN_MemIndex_VehicleConfigReserveByte3, /* D_VehicleConfigReserveByte3_Len_1 */
    #if 0
	������������Ԥ��byte4
    #endif
    EN_MemIndex_VehicleConfigReserveByte4, /* D_VehicleConfigReserveByte4_Len_1 */
/********���ݿ�ID_43 �������********/

/********���ݿ�ID_44 ���忪ʼ********/
    #if 0
	����ӭ������״̬:
	0���ر�
	1������
    #endif
    EN_MemIndex_WelcomeSwitch, /* D_WelcomeSwitch_Len_1 */
    #if 0
	��Ħģʽ������
	0x0: ȫ�����
	0x1: ȫ����
	0x2���粿����
	0x3: �粿����
	0x4����������
	0x5����������
	0x6����������
	0x7����������
	0x8��Errorģ�����
    #endif
    EN_MemIndex_MassageMode, /* D_MassageMode_Len_1 */
    #if 0
	������ʾ��������
	0���ޱ仯
	1���б仯
    #endif
    EN_MemIndex_FLSeatPosMsg, /* D_FLSeatPosMsg_Len_1 */
    #if 0
	����ӭ������
	0���ر�
	1������
    #endif
    EN_MemIndex_PaWelcomeSwitch, /* D_PaWelcomeSwitch_Len_1 */
    #if 0
	����ӭ��״̬
	0����Ч��
	1�����ƣ�
	2��ǰ�ơ�
    #endif
    EN_MemIndex_PaWelcomeStatus, /* D_PaWelcomeStatus_Len_1 */
    #if 0
	���ݼ�������
	0:������
	1������
    #endif
    EN_MemIndex_DrHeatConfig, /* D_DrHeatConfig_Len_1 */
    #if 0
	2�ż�������
	0:������
	1������
    #endif
    EN_MemIndex_SecondHeatConfig, /* D_SecondHeatConfig_Len_1 */
    #if 0
	���ż�������
	0:������
	1������
    #endif
    EN_MemIndex_ThirdHeatConfig, /* D_ThirdHeatConfig_Len_1 */
    #if 0
	����ͨ������
	0:������
	2������
    #endif
    EN_MemIndex_DrvVentConfig, /* D_DrvVentConfig_Len_1 */
    #if 0
	����ͨ������
	0:������
	2������
    #endif
    EN_MemIndex_SecondVentConfig, /* D_SecondVentConfig_Len_1 */
    #if 0
	����ͨ������
	0:������
	3������
    #endif
    EN_MemIndex_ThirdVentConfig, /* D_ThirdVentConfig_Len_1 */
    #if 0
	���Ű�Ħ��������
	0:������
	4������
    #endif
    EN_MemIndex_ThirdMassageConfig, /* D_ThirdMassageConfig_Len_1 */
    #if 0
	������ʾ��������
	0���ޱ仯
	1���б仯
    #endif
    EN_MemIndex_FRSeatPosMsg, /* D_FRSeatPosMsg_Len_1 */
    #if 0
	����ӭ��λ�ø��±�־:
	0��������
	1������
    #endif
    EN_MemIndex_WelcomePaUpdate, /* D_WelcomePaUpdate_Len_1 */
    #if 0
	���ݸ߶ȵ�����ֹ�����
    #endif
    EN_MemIndex_PaHeightSoftStopCnt, /* D_PaHeightSoftStopCnt_Len_1 */
/********���ݿ�ID_44 �������********/

/********���ݿ�ID_45 ���忪ʼ********/
    #if 0
	�������򵽴���ֹ�����
    #endif
    EN_MemIndex_PaLengthSoftStopCnt, /* D_PaLengthSoftStopCnt_Len_1 */
    #if 0
	���ݿ���������ֹ�����
    #endif
    EN_MemIndex_PaBackSoftStopCnt, /* D_PaBackSoftStopCnt_Len_1 */
    #if 0
	�������е�����ֹ�����
    #endif
    EN_MemIndex_PaFrontSoftStopCnt, /* D_PaFrontSoftStopCnt_Len_1 */
    #if 0
	���ݼ�������
	0:������
	1������
    #endif
    EN_MemIndex_DrHeatFlg, /* D_DrHeatFlg_Len_1 */
    #if 0
	����ͨ������
	0:������
	1������
    #endif
    EN_MemIndex_DrVentFlg, /* D_DrVentFlg_Len_1 */
    #if 0
	���ݼ�������
	0:������
	1������
    #endif
    EN_MemIndex_PaHeatFlg, /* D_PaHeatFlg_Len_1 */
    #if 0
	����ͨ������
	0:������
	1������
    #endif
    EN_MemIndex_PaVentFlg, /* D_PaVentFlg_Len_1 */
    #if 0
	����ģʽ
	0:������
	1������
    #endif
    EN_MemIndex_TestMode, /* D_TestMode_Len_1 */
    #if 0
	������״̬
	0����
	1����
    #endif
    EN_MemIndex_DrDoorSts, /* D_DrDoorSts_Len_1 */
    #if 0
	������״̬
	0����
	1����
    #endif
    EN_MemIndex_PaDoorSts, /* D_PaDoorSts_Len_1 */
    #if 0
	���Ա��ķ�������
	0�����ͽ���
	1������ʹ��
	bit0:0x500
	bit1:0x501
	bit2:0x502
    #endif
    EN_MemIndex_TestMessageSendCfg, /* D_TestMessageSendCfg_Len_1 */
/********���ݿ�ID_45 �������********/

/********���ݿ�ID_76 ���忪ʼ********/
    #if 0
	ϵͳ��������F1FA����
    #endif
    EN_MemIndex_SystemFunctionConfiguration_F1FA, /* D_SystemFunctionConfiguration_F1FA_Len_6 */
    #if 0
	VIN��
    #endif
    EN_MemIndex_UdsDidVinCode, /* D_UdsDidVinCode_Len_17 */
    #if 0
	��Ʒ��������
    #endif
    EN_MemIndex_ECUManufactureData, /* D_ECUManufactureData_Len_4 */
/********���ݿ�ID_76 �������********/

/********���ݿ�ID_77 ���忪ʼ********/
    #if 0
	�ͻ�Ӳ���汾��
    #endif
    EN_MemIndex_ECUHardwareVersion, /* D_ECUHardwareVersion_Len_16 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved15, /* D_Reserved15_Len_3 */
/********���ݿ�ID_77 �������********/

/********���ݿ�ID_78 ���忪ʼ********/
    #if 0
	PCBA �洢
    #endif
    EN_MemIndex_PCBASerialNumber, /* D_PCBASerialNumber_Len_21 */
    #if 0
	Ԥ��
    #endif
    EN_MemIndex_Reserved16, /* D_Reserved16_Len_2 */
/********���ݿ�ID_78 �������********/

/********���ݿ�ID_56 ���忪ʼ********/
    #if 0
	�������ϵ����ͼ�����
    #endif
    EN_MemIndex_BoardPowerOnTypeAndCnt, /* D_BoardPowerOnTypeAndCnt_Len_15 */
/********���ݿ�ID_56 �������********/

/********���ݿ�ID_57 ���忪ʼ********/
    #if 0
	CAN����BUS OFF
    #endif
    EN_MemIndex_Dtc_Index0, /* D_Dtc_Index0_Len_3 */
    #if 0
	�����ѹ����
    #endif
    EN_MemIndex_Dtc_Index1, /* D_Dtc_Index1_Len_3 */
    #if 0
	�����ѹ����
    #endif
    EN_MemIndex_Dtc_Index2, /* D_Dtc_Index2_Len_3 */
    #if 0
	���νڵ����Limphome״̬
    #endif
    EN_MemIndex_Dtc_Index3, /* D_Dtc_Index3_Len_3 */
    #if 0
	DSM��BCMͨѶ��ʧ
    #endif
    EN_MemIndex_Dtc_Index4, /* D_Dtc_Index4_Len_3 */
/********���ݿ�ID_57 �������********/

/********���ݿ�ID_58 ���忪ʼ********/
    #if 0
	DSM��GWͨѶ��ʧ
    #endif
    EN_MemIndex_Dtc_Index5, /* D_Dtc_Index5_Len_3 */
    #if 0
	���ݼ�������Եض�·
    #endif
    EN_MemIndex_Dtc_Index6, /* D_Dtc_Index6_Len_3 */
    #if 0
	���ݼ��������·
    #endif
    EN_MemIndex_Dtc_Index7, /* D_Dtc_Index7_Len_3 */
    #if 0
	���ݼ���NTC+�Եض�·
    #endif
    EN_MemIndex_Dtc_Index8, /* D_Dtc_Index8_Len_3 */
    #if 0
	���ݼ���NTC+�Ե�Դ��·���·
    #endif
    EN_MemIndex_Dtc_Index9, /* D_Dtc_Index9_Len_3 */
/********���ݿ�ID_58 �������********/

/********���ݿ�ID_59 ���忪ʼ********/
    #if 0
	���ݼ���NTC+������Ч
    #endif
    EN_MemIndex_Dtc_Index10, /* D_Dtc_Index10_Len_3 */
    #if 0
	���ݼ�������Եض�·
    #endif
    EN_MemIndex_Dtc_Index11, /* D_Dtc_Index11_Len_3 */
    #if 0
	���ݼ��������·
    #endif
    EN_MemIndex_Dtc_Index12, /* D_Dtc_Index12_Len_3 */
    #if 0
	���ݼ���NTC+�Եض�·
    #endif
    EN_MemIndex_Dtc_Index13, /* D_Dtc_Index13_Len_3 */
    #if 0
	���ݼ���NTC+�Ե�Դ��·���·
    #endif
    EN_MemIndex_Dtc_Index14, /* D_Dtc_Index14_Len_3 */
/********���ݿ�ID_59 �������********/

/********���ݿ�ID_60 ���忪ʼ********/
    #if 0
	���ݼ���NTC+������Ч
    #endif
    EN_MemIndex_Dtc_Index15, /* D_Dtc_Index15_Len_3 */
    #if 0
	����ͨ�������źţ�PWM���Եض�·
    #endif
    EN_MemIndex_Dtc_Index16, /* D_Dtc_Index16_Len_3 */
    #if 0
	����ͨ�������źţ�PWM���Ե�Դ��·���·
    #endif
    EN_MemIndex_Dtc_Index17, /* D_Dtc_Index17_Len_3 */
    #if 0
	����ͨ�������źţ�PWM���Եض�·
    #endif
    EN_MemIndex_Dtc_Index18, /* D_Dtc_Index18_Len_3 */
    #if 0
	����ͨ�������źţ�PWM���Ե�Դ��·���·
    #endif
    EN_MemIndex_Dtc_Index19, /* D_Dtc_Index19_Len_3 */
/********���ݿ�ID_60 �������********/

/********���ݿ�ID_61 ���忪ʼ********/
    #if 0
	����������ǰ���ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index20, /* D_Dtc_Index20_Len_3 */
    #if 0
	�������������ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index21, /* D_Dtc_Index21_Len_3 */
    #if 0
	���ݿ�����ǰ���ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index22, /* D_Dtc_Index22_Len_3 */
    #if 0
	���ݿ��������ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index23, /* D_Dtc_Index23_Len_3 */
    #if 0
	���ݸ߶����ϵ��ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index24, /* D_Dtc_Index24_Len_3 */
/********���ݿ�ID_61 �������********/

/********���ݿ�ID_62 ���忪ʼ********/
    #if 0
	���ݸ߶����µ��ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index25, /* D_Dtc_Index25_Len_3 */
    #if 0
	��������ǰ���Ƕ���ǰ���ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index26, /* D_Dtc_Index26_Len_3 */
    #if 0
	��������ǰ���Ƕ������ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index27, /* D_Dtc_Index27_Len_3 */
    #if 0
	����������ǰ���ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index28, /* D_Dtc_Index28_Len_3 */
    #if 0
	�������������ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index29, /* D_Dtc_Index29_Len_3 */
/********���ݿ�ID_62 �������********/

/********���ݿ�ID_63 ���忪ʼ********/
    #if 0
	���ݿ��������ǰ���ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index30, /* D_Dtc_Index30_Len_3 */
    #if 0
	���ݿ�����������ڿ���ճ��
    #endif
    EN_MemIndex_Dtc_Index31, /* D_Dtc_Index31_Len_3 */
    #if 0
	���ݸ߶ȵ��ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index32, /* D_Dtc_Index32_Len_3 */
    #if 0
	����������ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index33, /* D_Dtc_Index33_Len_3 */
    #if 0
	���ݿ������ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index34, /* D_Dtc_Index34_Len_3 */
/********���ݿ�ID_63 �������********/

/********���ݿ�ID_64 ���忪ʼ********/
    #if 0
	��������ǰ���Ƕȵ��ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index35, /* D_Dtc_Index35_Len_3 */
    #if 0
	��������������ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index36, /* D_Dtc_Index36_Len_3 */
    #if 0
	���ݿ������ڼ̵���ճ��
    #endif
    EN_MemIndex_Dtc_Index37, /* D_Dtc_Index37_Len_3 */
    #if 0
	���ݸ߶ȵ��ڵ����������
    #endif
    EN_MemIndex_Dtc_Index38, /* D_Dtc_Index38_Len_3 */
    #if 0
	����������ڵ����������
    #endif
    EN_MemIndex_Dtc_Index39, /* D_Dtc_Index39_Len_3 */
/********���ݿ�ID_64 �������********/

/********���ݿ�ID_65 ���忪ʼ********/
    #if 0
	���ݿ������ڵ����������
    #endif
    EN_MemIndex_Dtc_Index40, /* D_Dtc_Index40_Len_3 */
    #if 0
	��������ǰ���Ƕȵ��ڵ����������
    #endif
    EN_MemIndex_Dtc_Index41, /* D_Dtc_Index41_Len_3 */
    #if 0
	����������ڵ����������
    #endif
    EN_MemIndex_Dtc_Index42, /* D_Dtc_Index42_Len_3 */
    #if 0
	���ݿ������ڵ����������
    #endif
    EN_MemIndex_Dtc_Index43, /* D_Dtc_Index43_Len_3 */
    #if 0
	�����̼�������Եض�·
    #endif
    EN_MemIndex_Dtc_Index44, /* D_Dtc_Index44_Len_3 */
/********���ݿ�ID_65 �������********/

/********���ݿ�ID_66 ���忪ʼ********/
    #if 0
	�����̼��������·
    #endif
    EN_MemIndex_Dtc_Index45, /* D_Dtc_Index45_Len_3 */
    #if 0
	�����̼���NTC+�Եض�·
    #endif
    EN_MemIndex_Dtc_Index46, /* D_Dtc_Index46_Len_3 */
    #if 0
	�����̼���NTC+�Ե�Դ��·���·
    #endif
    EN_MemIndex_Dtc_Index47, /* D_Dtc_Index47_Len_3 */
    #if 0
	�����̼���NTC+������Ч
    #endif
    EN_MemIndex_Dtc_Index48, /* D_Dtc_Index48_Len_3 */
    #if 0
	��Ħģ��Ƿѹ
    #endif
    EN_MemIndex_Dtc_Index49, /* D_Dtc_Index49_Len_3 */
/********���ݿ�ID_66 �������********/

/********���ݿ�ID_67 ���忪ʼ********/
    #if 0
	��Ħģ���ѹ
    #endif
    EN_MemIndex_Dtc_Index50, /* D_Dtc_Index50_Len_3 */
    #if 0
	��Ħ�������
    #endif
    EN_MemIndex_Dtc_Index51, /* D_Dtc_Index51_Len_3 */
    #if 0
	LIN���ݳ���
    #endif
    EN_MemIndex_Dtc_Index52, /* D_Dtc_Index52_Len_3 */
    #if 0
	DTCԤ��0
    #endif
    EN_MemIndex_Dtc_Index53, /* D_Dtc_Index53_Len_3 */
    #if 0
	DTC���ֵ - ��Ҫ���ﶨ����˳������
    #endif
    EN_MemIndex_Dtc_IndexMax, /* D_Dtc_IndexMax_Len_3 */
/********���ݿ�ID_67 �������********/
    EN_MemIndex_Max
} enSrvMemIndex;
#define     D_APP_INIT_Data_Len_4                       4
#define     D_BOOT_INIT_Data_Len_4                      4
#define     D_DareBootVersion_Len_8                     8
#define     D_CustomerBootVersion_Len_15                15

#define     D_APP_ValidFlg_Len_8                        8
#define     D_FingerPrint_ProgramDate_F199_Len_4        4
#define     D_FingerPrint_RepairShopCodeF198_Len_8      8
#define     D_BOOTUdsSecurityAccessTimes_Len_1          1
#define     D_AppUdsSecurityAccessTimes_Len_1           1
#define     D_Reserved0_Len_1                           1

#define     D_AppJumpToBootFlg_Len_1                    1
#define     D_WakeUpSource_Len_1                        1
#define     D_Reserved1_Len_1                           1

#define     D_DrCurHallCnt_Height_Len_2                 2
#define     D_DrCurHallCnt_Length_Len_2                 2
#define     D_DrCurHallCnt_Back_Len_2                   2
#define     D_DrCurHallCnt_Front_Len_2                  2
#define     D_Reserved2_Len_3                           3

#define     D_DrHardStopPos_Height_Len_2                2
#define     D_DrHardStopPos_Length_Len_2                2
#define     D_DrHardStopPos_Back_Len_2                  2
#define     D_DrHardStopPos_Front_Len_2                 2
#define     D_Reserved3_Len_3                           3

#define     D_DrMem1_Height_Len_2                       2
#define     D_DrMem1_Length_Len_2                       2
#define     D_DrMem1_Back_Len_2                         2
#define     D_DrMem1_Front_Len_2                        2
#define     D_DrMem1_ValidFlag_Len_1                    1
#define     D_Reserved4_Len_2                           2

#define     D_DrMem2_Height_Len_2                       2
#define     D_DrMem2_Length_Len_2                       2
#define     D_DrMem2_Back_Len_2                         2
#define     D_DrMem2_Front_Len_2                        2
#define     D_DrMem2_ValidFlag_Len_1                    1
#define     D_Reserved5_Len_2                           2

#define     D_DrMem3_Height_Len_2                       2
#define     D_DrMem3_Length_Len_2                       2
#define     D_DrMem3_Back_Len_2                         2
#define     D_DrMem3_Front_Len_2                        2
#define     D_DrMem3_ValidFlag_Len_1                    1
#define     D_Reserved6_Len_2                           2

#define     D_DrRes_ReCallPosi_Height_Len_2             2
#define     D_DrRes_ReCallPosi_Length_Len_2             2
#define     D_DrRes_ReCallPosi_Back_Len_2               2
#define     D_DrRes_ReCallPosi_Front_Len_2              2
#define     D_Reserved7_Len_3                           3

#define     D_PaCurHallCnt_Height_Len_2                 2
#define     D_PaCurHallCnt_Length_Len_2                 2
#define     D_PaCurHallCnt_Back_Len_2                   2
#define     D_PaCurHallCnt_Front_Len_2                  2
#define     D_Reserved8_Len_3                           3

#define     D_PaHardStopPos_Height_Len_2                2
#define     D_PaHardStopPos_Length_Len_2                2
#define     D_PaHardStopPos_Back_Len_2                  2
#define     D_PaHardStopPos_Front_Len_2                 2
#define     D_Reserved9_Len_3                           3

#define     D_PaMem1_Height_Len_2                       2
#define     D_PaMem1_Length_Len_2                       2
#define     D_PaMem1_Back_Len_2                         2
#define     D_PaMem1_Front_Len_2                        2
#define     D_PaMem1_ValidFlag_Len_1                    1
#define     D_Reserved10_Len_2                          2

#define     D_PaMem2_Height_Len_2                       2
#define     D_PaMem2_Length_Len_2                       2
#define     D_PaMem2_Back_Len_2                         2
#define     D_PaMem2_Front_Len_2                        2
#define     D_PaMem2_ValidFlag_Len_1                    1
#define     D_Reserved11_Len_2                          2

#define     D_PaMem3_Height_Len_2                       2
#define     D_PaMem3_Length_Len_2                       2
#define     D_PaMem3_Back_Len_2                         2
#define     D_PaMem3_Front_Len_2                        2
#define     D_PaMem3_ValidFlag_Len_1                    1
#define     D_Reserved12_Len_2                          2

#define     D_DrWelcome_LenTar_BackWard_Len_2           2
#define     D_DrWelcome_LenTar_ForWard_Len_2            2
#define     D_PaWelcome_LenTar_BackWard_Len_2           2
#define     D_PaWelcome_LenTar_ForWard_Len_2            2
#define     D_Reserved13_Len_3                          3

#define     D_DrAdjustConfig_Len_1                      1
#define     D_PaAdjustConfig_Len_1                      1
#define     D_DrVentAndHeatConfig_Len_1                 1
#define     D_DrMemoryConfig_Len_1                      1
#define     D_PaVentAndHeatConfig_Len_1                 1
#define     D_PaMemoryConfig_Len_1                      1
#define     D_MassageConfig_Len_1                       1
#define     D_VehicleConfigReserveByte0_Len_1           1
#define     D_VehicleConfigReserveByte1_Len_1           1
#define     D_VehicleConfigReserveByte2_Len_1           1
#define     D_Heat_CarType_Len_1                        1
#define     D_Heat_RemoteEnableConfig_Len_1             1
#define     D_Heat_PlatformEngineEnableConfig_Len_1     1
#define     D_Heat_P20_PHEV_EngineCfg_Len_1             1
#define     D_Heat_TimeOutPrm_Len_1                     1

#define     D_Heat_RunMaxTime_Len_1                     1
#define     D_SendTestMsgFlg_Len_1                      1
#define     D_Vent_TimeOutPrm_Len_1                     1
#define     D_Vent_RunMaxTime_Len_1                     1
#define     D_MotorSoftStopCntMax_Len_1                 1
#define     D_DrHeightSoftStopCnt_Len_1                 1
#define     D_DrLengthSoftStopCnt_Len_1                 1
#define     D_DrBackSoftStopCnt_Len_1                   1
#define     D_DrFrontSoftStopCnt_Len_1                  1
#define     D_Write_HardwareVersion_Flg_Len_1           1
#define     D_WelcomeStatus_Len_1                       1
#define     D_WelcomeDrUpate_Len_1                      1
#define     D_Heat_PlatFormVehicleEnableConfig_Len_1    1
#define     D_VehicleConfigReserveByte3_Len_1           1
#define     D_VehicleConfigReserveByte4_Len_1           1

#define     D_WelcomeSwitch_Len_1                       1
#define     D_MassageMode_Len_1                         1
#define     D_FLSeatPosMsg_Len_1                        1
#define     D_PaWelcomeSwitch_Len_1                     1
#define     D_PaWelcomeStatus_Len_1                     1
#define     D_DrHeatConfig_Len_1                        1
#define     D_SecondHeatConfig_Len_1                    1
#define     D_ThirdHeatConfig_Len_1                     1
#define     D_DrvVentConfig_Len_1                       1
#define     D_SecondVentConfig_Len_1                    1
#define     D_ThirdVentConfig_Len_1                     1
#define     D_ThirdMassageConfig_Len_1                  1
#define     D_FRSeatPosMsg_Len_1                        1
#define     D_WelcomePaUpdate_Len_1                     1
#define     D_PaHeightSoftStopCnt_Len_1                 1

#define     D_PaLengthSoftStopCnt_Len_1                 1
#define     D_PaBackSoftStopCnt_Len_1                   1
#define     D_PaFrontSoftStopCnt_Len_1                  1
#define     D_DrHeatFlg_Len_1                           1
#define     D_DrVentFlg_Len_1                           1
#define     D_PaHeatFlg_Len_1                           1
#define     D_PaVentFlg_Len_1                           1
#define     D_TestMode_Len_1                            1
#define     D_DrDoorSts_Len_1                           1
#define     D_PaDoorSts_Len_1                           1
#define     D_TestMessageSendCfg_Len_1                  1

#define     D_SystemFunctionConfiguration_F1FA_Len_6    6
#define     D_UdsDidVinCode_Len_17                      17
#define     D_ECUManufactureData_Len_4                  4

#define     D_ECUHardwareVersion_Len_16                 16
#define     D_Reserved15_Len_3                          3

#define     D_PCBASerialNumber_Len_21                   21
#define     D_Reserved16_Len_2                          2

#define     D_BoardPowerOnTypeAndCnt_Len_15             15

#define     D_Dtc_Index0_Len_3                          3
#define     D_Dtc_Index1_Len_3                          3
#define     D_Dtc_Index2_Len_3                          3
#define     D_Dtc_Index3_Len_3                          3
#define     D_Dtc_Index4_Len_3                          3

#define     D_Dtc_Index5_Len_3                          3
#define     D_Dtc_Index6_Len_3                          3
#define     D_Dtc_Index7_Len_3                          3
#define     D_Dtc_Index8_Len_3                          3
#define     D_Dtc_Index9_Len_3                          3

#define     D_Dtc_Index10_Len_3                         3
#define     D_Dtc_Index11_Len_3                         3
#define     D_Dtc_Index12_Len_3                         3
#define     D_Dtc_Index13_Len_3                         3
#define     D_Dtc_Index14_Len_3                         3

#define     D_Dtc_Index15_Len_3                         3
#define     D_Dtc_Index16_Len_3                         3
#define     D_Dtc_Index17_Len_3                         3
#define     D_Dtc_Index18_Len_3                         3
#define     D_Dtc_Index19_Len_3                         3

#define     D_Dtc_Index20_Len_3                         3
#define     D_Dtc_Index21_Len_3                         3
#define     D_Dtc_Index22_Len_3                         3
#define     D_Dtc_Index23_Len_3                         3
#define     D_Dtc_Index24_Len_3                         3

#define     D_Dtc_Index25_Len_3                         3
#define     D_Dtc_Index26_Len_3                         3
#define     D_Dtc_Index27_Len_3                         3
#define     D_Dtc_Index28_Len_3                         3
#define     D_Dtc_Index29_Len_3                         3

#define     D_Dtc_Index30_Len_3                         3
#define     D_Dtc_Index31_Len_3                         3
#define     D_Dtc_Index32_Len_3                         3
#define     D_Dtc_Index33_Len_3                         3
#define     D_Dtc_Index34_Len_3                         3

#define     D_Dtc_Index35_Len_3                         3
#define     D_Dtc_Index36_Len_3                         3
#define     D_Dtc_Index37_Len_3                         3
#define     D_Dtc_Index38_Len_3                         3
#define     D_Dtc_Index39_Len_3                         3

#define     D_Dtc_Index40_Len_3                         3
#define     D_Dtc_Index41_Len_3                         3
#define     D_Dtc_Index42_Len_3                         3
#define     D_Dtc_Index43_Len_3                         3
#define     D_Dtc_Index44_Len_3                         3

#define     D_Dtc_Index45_Len_3                         3
#define     D_Dtc_Index46_Len_3                         3
#define     D_Dtc_Index47_Len_3                         3
#define     D_Dtc_Index48_Len_3                         3
#define     D_Dtc_Index49_Len_3                         3

#define     D_Dtc_Index50_Len_3                         3
#define     D_Dtc_Index51_Len_3                         3
#define     D_Dtc_Index52_Len_3                         3
#define     D_Dtc_Index53_Len_3                         3
#define     D_Dtc_IndexMax_Len_3                        3






/************************д�볣�ú�������************************/

/************************E2���ݿ����ò�������ؽӿ�************************/
extern strEepromDataBlockCfgTable * Eel_GetE2DataBlockCfgTablePtr(void);
extern INT16U Srvl_GetE2DataBlockCfgTableLength(void);
extern void Srvl_SetE2DataBlockOptResult(INT16U DataId, enE2promOptResult Result);
extern enE2promOptResult Srvl_GetE2DataBlockOptResult(INT16U DataId);
extern void Srvl_SetE2DataBlockOptReq(INT16U DataId, EepromOptReq Req);
extern EepromOptReq Srvl_GetE2DataBlockEepOptReq(INT16U DataId);
extern INT8U * Srvl_GetE2DataBlockBufferPtr(INT16U DataId);
extern INT8U Srvl_GetE2DataBlockLength(INT16U DataId);
extern INT32U Srvl_GetE2DataBlockStartAddr(INT16U DataId);
extern INT16U Srvl_GetE2DataBlockBackUpID(INT16U DataId);
extern void Srvl_SetE2DataBlockPreWriteFlg(INT16U DataId, INT8U PreWriteFlg);
extern INT8U Srvl_GetE2DataBlockPreWriteFlg(INT16U DataId);
/************************E2�Զ���ö�ٲ�������ؽӿ�************************/
extern strEepromDataDefineTable * Eel_GetE2DataDefineTablePtr(void);
extern INT16U Srvl_GetE2DataDefineTableLength(void);
extern INT16U Srvl_GetE2DefineDataBlockID(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineLen(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineStartOffset(enSrvMemIndex MemIndex);
extern INT16U Srvl_GetUseDataBlockID(INT16U Index);
extern INT16U Srvl_GetUseDataBlockIDNoBackUp(INT16U Index);

#endif
