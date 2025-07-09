/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescRoutineCtlList.h
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             RoutineControl�б�
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven Ī����
** Created date:            2013.10.19
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
** 
**------------------------------------------------------------------------------------------ 
** Modified By:             
** Modified date:           
** Version:                 
** Description:             
** 
********************************************************************************************/

#ifndef _ROUTINECTLLIST_H_
#define _ROUTINECTLLIST_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		ROUTLIST_GLOBALS 
#define		ROUTLIST_EXT 
#else
#define		ROUTLIST_EXT        extern
#endif


/* define Routine Control Type */
#define DESC_ROUTINE_CONTROL_NULL                                   0
#define DESC_ROUTINE_CONTROL_START_ROUTINE                          1
#define DESC_ROUTINE_CONTROL_STOP_ROUTINE                           2
#define DESC_ROUTINE_CONTROL_REQUEST_ROUTINE_RESULT                 3
#define DESC_ROUTINE_CONTROL_ROUTINE_COMPLETE                       4


#define DESC_LEARNED_NOT			0
#define DESC_LEARNED_IN_PROGRESS	1
#define DESC_LEARNED_COMPLETED		2
#define DESC_LEARNED_FAILURE 		3
#define DESC_LEARNED_TIMEOUT		4

// 0x00=ALL not learned δѧϰ
// 0x01=learnning ѧϰ��
// 0x02= ALL learned successful  ѧϰ�ɹ�
// 0x03= learned faultѧϰʧ��
#define DESC_ALL_not_learned			0
#define DESC_learnning					1
#define DESC_ALL_learned_successful		2
#define DESC_learned_fault				3




#define D_50msTime                          (0x5u)

//Added by Alen 2017/9/14

typedef struct
{
    INT8U             ReqDatLen;
    void                (*ServiceProcess)(void);
}tROUTINTE_INFO;

typedef struct 
{
    INT16U            sDID;
    INT8U             SessionAllow;
    INT8U             SecurityAllow; /*��Ҫ�İ�ȫ����*/
    tROUTINTE_INFO      RoutineInfo[3];
}tDESC_ROUTINT_INFO;      


typedef    enum{
    Routinenotactivated = 0x00u,
    RoutineStartSuccess = 0x00u,
    RoutinecompletedwithOK = 0x02u,
    Routineinprogress = 0x03u,
    RoutinestopOK = 0x00u,
    RoutinecompletedNOK = 0x01u,
    
}RoutineResultType;

typedef enum UDS_ROUTINE_EOL_RESULT_T
{
    EN_UDS_ROUTINE_EOL_SUCCESS = 0x00u,
    EN_UDS_ROUTINE_EOL_BATTERY_VOLTAGE_OUT_OF_RANGE = 0x01u,
    EN_UDS_ROUTINE_EOL_RESERVED = 0x02u,
    EN_UDS_ROUTINE_EOL_TERMINAL_STATE_WRONG = 0x03u,
    EN_UDS_ROUTINE_EOL_ESK_VALUE_EXCEPTION = 0x11u,
    EN_UDS_ROUTINE_EOL_ALL_RESULT
}UdsRoutineEolResult_t;

typedef enum
{
	EN_DRHEAT_Rountine = 0,
	EN_PAHEAT_Rountine,
	EN_DRVENT_Rountine,
	EN_PAVENT_Rountine,
	EN_ROUTINECTRLTYPEMAX,
}enRoutineCtrlType;

//����ѧϰ���� - ˳������˳�򱣳�һ��
typedef enum
{

	enStepDrHeightPosiUP = 0,	/*�������θ߶�*/
	enStepDrLengthPosiFW,		/*������������*/
	enStepDrBackrestPosiFW,		/*�������ο���*/
	enStepDrFrontPosiBW,		/*������������*/

	enStepPaHeightPosiUP,		/*�������θ߶�*/
	enStepPaLengthPosiFW,		/*������������*/
	enStepPaBackrestPosiFW, 	/*�������ο���*/
	enStepPaFrontPosiBW,		/*������������*/

	enStepNULL,
}enLeanStep;

ROUTLIST_EXT void  DescRoutineCtrlSequenceSet(INT8U SetDat);
ROUTLIST_EXT void  DescRoutineControl(void);
ROUTLIST_EXT BOOL  DescRoutine_getRoutineCtrFlg(enRoutineCtrlType index);
ROUTLIST_EXT void  DescRoutine_setRoutineCtrFlg(enRoutineCtrlType index, BOOL flg);

INT8U *DescRoutineCtrl_GetRecvPIN(void);

BOOL Desc_IsDiagPassThroughMode(void);
void Desc_StopDiagPassThroughMode(void);

 
BOOL UdsApp_GetSysEolModeInd(void);
BOOL UdsApp_GetSysOnlineTestModeInd(void);
INT8U UdsRoutineCtrl_GetAdChlData(void);
void UdsRoutineCtrl_SessionChangedToDefault(void);
BOOL UdsRoutineCtrl_ForceIntoSleepModeInd(void);
BOOL UdsApp_GetNoFeedWatchDogIntoLimphomeStaInd(void);

extern void setRoutine0203Sts(INT8U Sts);	
extern INT8U getRoutine0203Sts();

void DescRoutine_setDrLearnMotorStep(enLeanStep step);
enLeanStep DescRoutine_getDrLearnMotorStep(void);
void DescRoutine_setDrMotorLearnSts(enLeanStep step);
void DescRoutine_setDrLearnMotorFlg(BOOL flg);
BOOL DescRoutine_getDrLearnMotorFlg(void);
		
void DescRoutine_setPaLearnMotorStep(enLeanStep step);
enLeanStep DescRoutine_getPaLearnMotorStep(void);
void DescRoutine_setPaMotorLearnSts(enLeanStep step);
void DescRoutine_setPaLearnMotorFlg(BOOL flg);
BOOL DescRoutine_getPaLearnMotorFlg(void);
INT8U DescRoutineCtrl_GetRecoverDefaultFlag(void);

/***********************************************************************************************
 * @function name:  GetRecoverDefaultFlag
 *
 * @description:   ��ģ�͵��ã���������10ms
 *
 * @input parameters:    void
 *
 * @output parameters:     INT8U
 *
 * @return:         �Ƿ�ָ�����
 *
 * @note:           ��ģ�͵��ã���������10ms
 *
 * @author:         Prima Niu
 *
 * @date:           2022.10.22
 ***********************************************************************************************/
INT8U GetRecoverDefaultFlag(void);

/***********************************************************************************************
 * @function name:  RecoverDefaultFlagFunction
 *
 * @description:    ���ָ�������־λ��ʱ50ms����
 *
 * @input parameters:    void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           ��Ҫ��10ms�������������ִ��
 *
 * @author:         Prima Niu
 *
 * @date:           2022.10.22
 ***********************************************************************************************/
void RecoverDefaultFlagFunction(void);

INT8U DescRoutineCtrl_GetDareTestFlag(void);
extern void DescRoutineCtrl_SetRecoverDefaultFlag(INT8U flg);
extern void DescRoutineCtrl_SetRecoverDefaultFlag(INT8U flg);
#ifdef __cplusplus
}
#endif
 
#endif  /*_ROUTINECTLLIST_H_*/



