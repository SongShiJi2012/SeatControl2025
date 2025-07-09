/*!
************************************************************************************************************************
* @file Appl_DTCtask.h
* @brief 
* @par 模块输入参数
* @par 模块输出参数
* @details 
* @author Lews Hammond(刘发星)
* @date 2019-9-4
************************************************************************************************************************
*/
#ifndef SYS_FAULT_DIAGNOSTIC_H
#define SYS_FAULT_DIAGNOSTIC_H
#include "Common.h"
//#include "Srvl_CfgTask.h"

typedef enum _TASK_STATUS_INFO_T
{
    EN_TASK_INIT = 0,
    EN_TASK_RUNNING,
    EN_TASK_SLEEP,
    EN_TASK_EXIT,
    EN_TASK_ALL_STA
}TaskStatusInfo_t;


//extern const ST_TaskInfo Diag_TaskInfo;
extern void Diag_Init(void);
extern void Diag_TaskServices(void);

#endif


