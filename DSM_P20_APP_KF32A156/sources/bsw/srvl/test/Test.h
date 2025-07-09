/***********************************************************************************************
 * @file name:      Test.h
 * @description:    ��ͷ�ļ������˲���ģ����������֤ECU���ܵ�����ӿڣ���Ҫ���ڵ�������֤��
 *                  �������ݣ�
 *                    - ADֵ�����������״̬�Ȳ��Թ��ܵ��ⲿ�ӿ�����
 *                    - EEPROM��д���Խӿ�
 *                    - TLE9210XоƬ״̬�����ռ��ӿ�
 *                    - ʱ����Ժ���������T21��ʱ����
 *                    - �����ڵ���CANͨ�š�IO��ת�ȸ����ӿ�
 *
 * @note:           ���ļ������ڲ�����;��**�Ͻ������������ǲ���ģ���е��ñ��ļ��κνӿں���**
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/



#ifndef TEST_H_
#define TEST_H_

#include "Common.h"
#include "KF32A156.h"




#define		D_TEST_SW			1

#define		D_TEST_TIMER_SW		0 //T21��ʱ������Ҫ���Գ�������ʱ��ʱ���á�Ĭ�Ϲر�

typedef enum
{
    /*0~7*/
    TEST_AD_LOOP = 0,	//AD����
    TEST_AD_SINGLE,		//AD����
    TEST_VAR_DATA,		//�������
    TEST_9210X_DATA,	//Ԥ����Ϣ
    TEST_MAX
} ETEST;

extern void Test_Main(void);
extern void Test_ReadDID_FE06(void);
extern void Test_ReadDID_FF06(void);
#if D_TEST_TIMER_SW
extern void SetTimerStartValue();
extern void SetTimerEndValue();
extern INT32U GetDiffTime0();
extern INT32U GetDiffTime_us();
extern void Test_SendProgramPeriod(void);
extern void Test_SendTimeus(void);
#endif


extern void SetCanTestCommand(INT8U val);
extern void SetCanTestAccelerateFlag(INT8U val);
extern void SetCanTestParameter(INT8U val);
extern void Test_TogglePin59(void);
extern void Test_Hall(void);


/*********************************Ԥ����ʵ�ֽӿ�*******************************/
extern INT8U Vfb_Reserved_0();
extern INT8U Vfb_Reserved_1();
extern void Ecual_CanSetThirdHeatLvl(INT8U test);
/*********************************Ԥ����ʵ�ֽӿ�*******************************/







#endif /* TEST_H_ */
