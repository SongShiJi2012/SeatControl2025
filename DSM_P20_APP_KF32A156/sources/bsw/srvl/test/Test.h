/***********************************************************************************************
 * @file name:      Test.h
 * @description:    本头文件声明了测试模块中用于验证ECU功能的软件接口，主要用于调试与验证。
 *                  包含内容：
 *                    - AD值、霍尔、电机状态等测试功能的外部接口声明
 *                    - EEPROM读写测试接口
 *                    - TLE9210X芯片状态数据收集接口
 *                    - 时间测试函数（基于T21定时器）
 *                    - 可用于调试CAN通信、IO翻转等辅助接口
 *
 * @note:           本文件仅限于测试用途，**严禁在量产代码或非测试模块中调用本文件任何接口函数**
 * @author:         ssj 2025-06-26
 ***********************************************************************************************/



#ifndef TEST_H_
#define TEST_H_

#include "Common.h"
#include "KF32A156.h"




#define		D_TEST_SW			1

#define		D_TEST_TIMER_SW		0 //T21计时器，需要测试程序运行时间时启用。默认关闭

typedef enum
{
    /*0~7*/
    TEST_AD_LOOP = 0,	//AD数据
    TEST_AD_SINGLE,		//AD数据
    TEST_VAR_DATA,		//电机数据
    TEST_9210X_DATA,	//预驱信息
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


/*********************************预留待实现接口*******************************/
extern INT8U Vfb_Reserved_0();
extern INT8U Vfb_Reserved_1();
extern void Ecual_CanSetThirdHeatLvl(INT8U test);
/*********************************预留待实现接口*******************************/







#endif /* TEST_H_ */
