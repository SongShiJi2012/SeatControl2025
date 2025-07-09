/*!
************************************************************************************************************************
* @file uds_srv2a_readdatabyperiodicid.h
* @brief 
* @par ģ���������
       
* @par ģ���������
       
* @details 
* @author Lews Hammond(������)
* @date 2019-10-18
************************************************************************************************************************
*/
#include  "Common.h"
#ifndef UDS_SRV2A_READ_DATA_BY_PERIODIC_ID_H
#define UDS_SRV2A_READ_DATA_BY_PERIODIC_ID_H


#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)

#define D_UDS_SUPPORT_PERIOD_DID_NUMBER     5U
/* JMC ��Ϲ淶Ҫ��ÿ��DID�ظ�������Ӧ6A */
#define D_UDS_PERIOD_DID_ACTIVE_RESP        0x6AU

/* period did range: 0xF200-0xF2FF */
#define D_UDS_PERIOD_DID_CUR_ANT_SCHED_LIST         0x21U
#define D_UDS_PERIOD_DID_CUR_KEY0_STRENG            0x22U
#define D_UDS_PERIOD_DID_CUR_KEY1_STRENG            0x23U
#define D_UDS_PERIOD_DID_CUR_KEY_LOCAT              0x24U
#define D_UDS_PERIOD_DID_RF_TEST_DATA               0x25U

#define D_UDS_DID_PERIOD_SLOW_RATE_MODE      0x01U
#define D_UDS_DID_PERIOD_MID_RATE_MODE       0x02U
#define D_UDS_DID_PERIOD_FAST_RATE_MODE      0x03U
#define D_UDS_DID_PERIOD_STOP_TRANS_MODE     0x04U

#define D_UDS_PERIOD_DID_SCHEDULE_TIME      5U // unit ms

#define D_UDS_PERIOD_DID_MULT_GAP_TIME      (25UL / D_UDS_PERIOD_DID_SCHEDULE_TIME)
#define D_UDS_PERIOD_DID_START_DELAY        (10UL / D_UDS_PERIOD_DID_SCHEDULE_TIME)

#define D_UDS_DID_PERIOD_TX_SLOW            (500UL / D_UDS_PERIOD_DID_SCHEDULE_TIME)
#define D_UDS_DID_PERIOD_TX_MID             (300UL / D_UDS_PERIOD_DID_SCHEDULE_TIME)
#define D_UDS_DID_PERIOD_TX_FAST            (100UL / D_UDS_PERIOD_DID_SCHEDULE_TIME)

#define D_UDS_PERIOD_DID_MAX_TRANS_NUMBER   (D_UDS_DID_PERIOD_TX_FAST / D_UDS_PERIOD_DID_MULT_GAP_TIME)

typedef struct UDS_PERIOD_DID_OPT_T
{
    INT8U Uds_PeriodTxDidInx[D_UDS_SUPPORT_PERIOD_DID_NUMBER];      /*!< ��ǰ���ڴ����DID���� */
    INT8U Uds_PeriodTxDidNum;                                       /*!< ��ǰ���ڴ���DID���� */
    INT8U Uds_DidTransMode;                                         /*!< ����ģʽ */
    INT32U Uds_DidPeriodCnt;                                        /*!< ����ģʽ���� */
}UdsPeriodDidOpt_t;


typedef struct UDS_PERIOD_DID_CONFIG_T
{
    INT8U Uds_SupportPeriodDid;             /*!< ֧�ֵ�����DID */
    void (*pUds_PeriodDidTxFunc)(void);     /*!< ����DID���ͺ��� */
    /* �����������ȡȨ�޵� */
}UdsPeriodDidCfg_t;


void UdsApp_2AReadPeriodDid(void);

void UdsApp_2APeriodSchedule(void);

extern void UdsApp_2APeriodTransReset(void);

void UdsApp_ReadCurAntScheTbl(INT8U pDat[], INT8U *pLen);

void UdsApp_ReadKey1Strength(INT8U pDat[], INT8U *pLen);

void UdsApp_ReadKey2Strength(INT8U pDat[], INT8U *pLen);

void UdsApp_ReadCurKeyPos(INT8U pDat[], INT8U *pLen);

void UdsApp_ReadRfTestData(INT8U pDat[], INT8U *pLen);




#endif

#endif


