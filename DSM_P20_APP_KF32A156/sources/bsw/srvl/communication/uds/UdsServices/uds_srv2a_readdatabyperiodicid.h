/*!
************************************************************************************************************************
* @file uds_srv2a_readdatabyperiodicid.h
* @brief 
* @par 模块输入参数
       
* @par 模块输出参数
       
* @details 
* @author Lews Hammond(刘发星)
* @date 2019-10-18
************************************************************************************************************************
*/
#include  "Common.h"
#ifndef UDS_SRV2A_READ_DATA_BY_PERIODIC_ID_H
#define UDS_SRV2A_READ_DATA_BY_PERIODIC_ID_H


#if (SID2A_PERIOD_DID_SERVICES == DESC_ENABLE)

#define D_UDS_SUPPORT_PERIOD_DID_NUMBER     5U
/* JMC 诊断规范要求每个DID回复积极响应6A */
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
    INT8U Uds_PeriodTxDidInx[D_UDS_SUPPORT_PERIOD_DID_NUMBER];      /*!< 当前周期传输的DID索引 */
    INT8U Uds_PeriodTxDidNum;                                       /*!< 当前周期传输DID数量 */
    INT8U Uds_DidTransMode;                                         /*!< 传输模式 */
    INT32U Uds_DidPeriodCnt;                                        /*!< 传输模式计数 */
}UdsPeriodDidOpt_t;


typedef struct UDS_PERIOD_DID_CONFIG_T
{
    INT8U Uds_SupportPeriodDid;             /*!< 支持的周期DID */
    void (*pUds_PeriodDidTxFunc)(void);     /*!< 周期DID发送函数 */
    /* 可添加其他读取权限等 */
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


