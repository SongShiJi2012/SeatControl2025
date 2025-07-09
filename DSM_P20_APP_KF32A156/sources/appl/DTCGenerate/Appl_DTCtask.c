/*!
************************************************************************************************************************
* @file Appl_DTCtask.c
* @brief 
* @par ģ���������
* @par ģ���������
* @details 
* @author Lews Hammond(������)
* @date 2019-9-4
************************************************************************************************************************
*/

#include "Appl_DTCtask.h"
#include "Srvl_E2memory.h"


//static ST_Task_SleepWork_Status Diag_SleepWorkStatus = {0};
static TaskStatusInfo_t Diag_TaskSta = EN_TASK_INIT;



static BOOL Diag_TaskIsPermitSleepOrNot(void);
static BOOL Diag_TaskIsReadySleepOrNot(void);
static BOOL Diag_TaskIsWorkingOrNot(void);
static void Diag_TaskMandatoryExit(void);

/*! @brief ������� */
//const ST_TaskInfo Diag_TaskInfo =
//{
//	EN_TASK_ID_SRV_DIAG,
//	Diag_Init,
//	Diag_TaskServices,
//	Diag_TaskIsPermitSleepOrNot,
//	Diag_TaskIsReadySleepOrNot,
//	Diag_TaskIsWorkingOrNot,
//	Diag_TaskMandatoryExit
//};

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

void Diag_Init(void)
{
    Diag_TaskSta = EN_TASK_INIT;

}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

void Diag_TaskServices(void)
{
//    switch (Diag_TaskSta)
//    {
//        case EN_TASK_INIT:
//            if (Ecual_GetEepromInitStatus() == EN_MEMORY_READY)
//            {
//                Diag_TaskSta = EN_TASK_RUNNING;
//            }
//            break;
//
//        case EN_TASK_RUNNING:
//		    Diag_MonitorEnableCriteriaCheck();
//			Diag_LoadDiagHandle();
//            Diag_DtcRecordHandle();
//            break;
//
//        case EN_TASK_SLEEP:
//		{
//			;
//		}
//		break;
//        case EN_TASK_EXIT:
//        default: /* task exit */
//            break;
//    }
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

static BOOL Diag_TaskIsPermitSleepOrNot(void)
{
//    return Diag_SleepWorkStatus.Is_Permit_Sleep_Status;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

static BOOL Diag_TaskIsReadySleepOrNot(void)
{
//    return Diag_SleepWorkStatus.Is_Ready_Sleep_Status;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

static BOOL Diag_TaskIsWorkingOrNot(void)
{
//    return Diag_SleepWorkStatus.Is_Working_Status;
}

/*!
************************************************************************************************************************
* �ӿ�ԭ�� 
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-6
************************************************************************************************************************
*/

static void Diag_TaskMandatoryExit(void)
{
    
}

