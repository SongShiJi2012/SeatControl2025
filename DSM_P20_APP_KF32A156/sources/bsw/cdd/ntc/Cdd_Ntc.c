/*
 * Cdd_Ntc.c
 *
 *  Created on: 2025-3-20
 *      Author: Administrator
 */
#include "Cdd_Ntc.h"
#include "Srvl_E2memory.h"
#include "MidRelay.h"
#include "Ecual_Adc.h"


ST_ScanTempVal ScanTempVal;
/*----------------------------------/NTC温度系数表/----------------------------------------*/
//NTC温度系数表		//5K
//请务必确定表格为顺序表格(升序或降序)
//请务必确定表格起始温度为 -40℃ 开始

//标定测试，发现C40DB加热垫规格同C52X,标定数据采用C52X，与实际温箱标定值存在一定差异
//保险起见，沿用C40DB
const INT16U TempSeatAdTable[] =
{
	3705,3701,3696,3691,3687,3682,3677,3672,3668,3663,			//-40~-31
	3659,3653,3648,3642,3637,3631,3624,3617,3611,3604,			//-30~-21
	3597,3589,3581,3573,3565,3557,3546,3536,3525,3514,			//-20~-11
	3504,3490,3475,3461,3447,3433,3417,3401,3385,3369,3353,		//-10~0
	3339,3325,3311,3297,3283,3263,3243,3223,3204,3184,			//1~10
	3164,3145,3125,3105,3086,3063,3041,3018,2996,2974,			//11~20
	2948,2923,2897,2872,2847,2821,2795,2770,2744,2719,			//21~30
	2703,2688,2673,2657,2642,2638,2635,2631,2628,2624,			//31~40
	2578,2531,2485,2439,2393,2356,2319,2283,2246,2210,			//41~50
	2179,2149,2118,2088,2058,2030,2003,1976,1948,1921,			//51~60
	1879,1837,1794,1752,1710,1684,1658,1632,1606,1581,			//61~70
	1554,1528,1501,1475,1448,1421,1395,1368,1341,1314,			//71~80
	1290,1267,1243,1220,1196,1177,1157,1138,1119,1100,			//81~90
	1078,1057,1035,1014,992,975,958,941,924,907					//91~100
};
//新硬件-主驾AD表
const INT16U TempSeatAdTable_New_Dr0[] =
{
    3472,3456,3441,3425,3410,3394,3372,3350,3329,3307,       //-40~-31
    3285,3259,3234,3208,3183,3157,3129,3100,3072,3043,       //-30~-21
    3015,2981,2947,2913,2879,2845,2807,2769,2732,2694,       //-20~-11
    2656,2614,2572,2531,2489,2447,2406,2365,2323,2282,       //-10~-1
    2241,2195,2149,2104,2058,2012,1970,1927,1885,1842,       //0~9
    1800,1761,1722,1682,1643,1604,1564,1523,1483,1442,       //10~19
    1402,1365,1327,1290,1252,1215,1180,1145,1110,1075,       //20~29
    1040,1011,982,953,924,895,870,844,819,793,               //30~39
    768,745,722,700,677,654,635,616,597,578,                 //40~49
    559,542,526,509,493,476,462,447,433,418,                 //50~59
    404,392,380,369,357,345,334,324,313,303,                 //60~69
    292,286,280,274,269,263,257,251,245,239,                 //70~79
    233,227,222,216,210,204,198,192,186,181,                 //80~89
    175,169,163,157,151,145,139,134,128,122,116,             //90~100
};

//旧硬件-主驾AD表
const INT16U TempSeatAdTable_Old_Dr[] =
{
    3694,3690,3686,3682,3678,3674,3669,3664,3658,3653,        //-40~-31
    3648,3644,3640,3635,3631,3627,3617,3607,3598,3588,        //-30~-21
    3578,3569,3560,3552,3543,3534,3524,3513,3503,3492,        //-20~-11
    3482,3472,3461,3451,3440,3430,3416,3401,3387,3372,        //-10~0
    3358,3340,3322,3303,3285,3267,3248,3229,3211,3192,        //1~10
    3173,3150,3127,3104,3081,3058,3033,3008,2983,2958,        //11~20
    2933,2906,2878,2851,2823,2796,2767,2739,2710,2682,        //21~30
    2653,2622,2591,2559,2528,2497,2466,2434,2403,2371,        //31~40
    2340,2306,2272,2238,2204,2170,2137,2103,2070,2036,        //41~50
    2003,1970,1937,1905,1872,1839,1807,1774,1742,1709,        //51~60
    1677,1646,1614,1583,1551,1520,1490,1460,1431,1401,        //61~70
    1371,1341,1311,1280,1250,1220,1195,1170,1146,1121,        //71~80
    1096,1074,1051,1029,1006,984,964,943,923,902,             //81~90
    882,863,844,826,807,788,770,752,734,716,698,              //91~100
};
//旧硬件-副驾AD表
const INT16U TempSeatAdTable_Old_Pa[] =
{
    3695,3691,3687,3682,3678,3674,3669,3664,3659,3654,         //-40~-31
    3649,3643,3637,3630,3624,3618,3610,3602,3595,3587,         //-30~-21
    3579,3570,3561,3553,3544,3535,3524,3514,3503,3493,         //-20~-11
    3482,3472,3461,3451,3440,3430,3415,3400,3386,3371,         //-10~0
    3356,3339,3322,3304,3287,3270,3251,3232,3212,3193,         //1~10
    3174,3151,3128,3104,3081,3058,3033,3008,2983,2958,         //11~20
    2933,2905,2877,2850,2822,2794,2765,2736,2706,2677,         //21~30
    2648,2617,2586,2554,2523,2492,2462,2432,2402,2372,         //31~40
    2342,2307,2273,2238,2204,2169,2135,2102,2068,2035,         //41~50
    2001,1968,1935,1901,1868,1835,1803,1771,1739,1707,         //51~60
    1675,1643,1611,1579,1547,1515,1486,1457,1427,1398,         //61~70
    1369,1339,1309,1279,1249,1219,1194,1170,1145,1121,         //71~80
    1096,1073,1050,1028,1005,982,962,942,922,902,882,          //81~90
    862,843,823,804,784,766,749,731,714,696,                   //91~100
};

//新硬件-副驾AD表
const INT16U TempSeatAdTable_New_Pa0[] =
{
    3474,3458,3443,3427,3412,3396,3374,3353,3331,3310,      //-40~-31
    3288,3262,3236,3209,3183,3157,3129,3101,3074,3046,      //-30~-21
    3018,2985,2952,2918,2885,2852,2812,2772,2733,2693,      //-20~-11
    2653,2611,2570,2528,2487,2445,2405,2364,2324,2283,      //-10~-1
    2243,2196,2150,2103,2057,2010,1968,1926,1884,1842,      //0~9
    1800,1761,1722,1682,1643,1604,1564,1524,1484,1444,      //10~19
    1404,1366,1328,1291,1253,1215,1180,1144,1109,1073,      //20~29
    1038,1009,980,952,923,894,868,843,817,792,              //30~39
    766,743,720,698,675,652,633,614,596,577,                //40~49
    558,541,524,508,491,474,460,446,432,418,                //50~59
    404,392,380,368,356,344,334,323,313,302,                //60~69
    292,286,280,274,269,263,257,251,245,239,                //70~79
    233,227,222,216,210,204,198,192,186,181,                //80~89
    175,169,163,157,151,145,139,134,128,122,116,            //90~100s
};



/*******************************************************************************
* 函数名称：INT16U Cdd_Ntc_AdToTemp(INT16U TempData)
* 功能描述：温度查表
* 入口参数：温度AD值
* 出口参数：
* 返 回 值：	温度值
* 备    注: 偏移-40度，放大10倍
*******************************************************************************/
INT16U Cdd_Ntc_AdToTemp(INT16U TempData)
{
	INT16U High = (TEMP_STABLE_SIZE - 1);
	INT16U Low = 0;
	INT16U uc16Temp = 0;
	INT16U uc16DecPoint = 0;
	INT16U Mid = (INT16U)(High + Low) / 2;
	INT16U Sequence = SEQ_RISING;
	//INT16U TempData = TempDat-160;

	//判断表格升降序
	if( TempSeatAdTable[0] < TempSeatAdTable[TEMP_STABLE_SIZE - 1] )
	{
		Sequence = SEQ_RISING;
		//超出量程
		if( TempData < TempSeatAdTable[0] || TempData > TempSeatAdTable[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}
	else
	{
		Sequence = SEQ_LOWER;
		//超出量程
		if( TempData > TempSeatAdTable[0] || TempData < TempSeatAdTable[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}

	//二分查找
	for(;;)
	{
		if( TempData < TempSeatAdTable[Mid] )
        {
            (Sequence==SEQ_RISING)?(High = Mid):(Low = Mid);
        }

        if( TempData > TempSeatAdTable[Mid] )
        {
            (Sequence==SEQ_RISING)?(Low = Mid):(High = Mid);
        }

        Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
        if( (TempData==TempSeatAdTable[Mid]) || (High==Mid) || (Low==Mid) )
        {
        	 //uc16Temp = (INT16U)Mid;
        	 break;
        }
	}
	//放大100倍，偏移-4000
	if(TempData > TempSeatAdTable[Mid])
	{
		uc16DecPoint = (TempData -TempSeatAdTable[Mid-1])*100/(TempSeatAdTable[Mid-1] - TempSeatAdTable[Mid]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	}
	else
	{
		uc16DecPoint = (TempSeatAdTable[Mid] - TempData)*100/(TempSeatAdTable[Mid] - TempSeatAdTable[Mid+1]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	}

    return  (uc16Temp/10);
}
/*******************************************************************************
* 函数名称：INT16U Cdd_Ntc_AdToTemp_New_Dr(INT16U TempData)
* 功能描述：温度查表
* 入口参数：温度AD值
* 出口参数：
* 返 回 值：	温度值
* 备    注: 偏移-40度，放大10倍
*******************************************************************************/
INT16U Cdd_Ntc_AdToTemp_New_Dr(INT16U TempData)
{
	INT16U High = (TEMP_STABLE_SIZE - 1);
	INT16U Low = 0;
	INT16U uc16Temp = 0;
	INT16U uc16DecPoint = 0;
	INT16U Mid = (INT16U)(High + Low) / 2;
	INT16U Sequence = SEQ_RISING;
	//INT16U TempData = TempDat-160;
	const INT16U* TempSeatAdTable_New_Dr = NULL;

	TempSeatAdTable_New_Dr = TempSeatAdTable_New_Dr0;

	//判断表格升降序
	if( TempSeatAdTable_New_Dr[0] < TempSeatAdTable_New_Dr[TEMP_STABLE_SIZE - 1] )
	{
		Sequence = SEQ_RISING;
		//超出量程
		if( TempData < TempSeatAdTable_New_Dr[0] || TempData > TempSeatAdTable_New_Dr[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}
	else
	{
		Sequence = SEQ_LOWER;
		//超出量程
		if( TempData > TempSeatAdTable_New_Dr[0] || TempData < TempSeatAdTable_New_Dr[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}

	//二分查找
	for(;;)
	{
		if( TempData < TempSeatAdTable_New_Dr[Mid] )
        {
            (Sequence==SEQ_RISING)?(High = Mid):(Low = Mid);
        }

        if( TempData > TempSeatAdTable_New_Dr[Mid] )
        {
            (Sequence==SEQ_RISING)?(Low = Mid):(High = Mid);
        }

        Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
        if( (TempData==TempSeatAdTable_New_Dr[Mid]) || (High==Mid) || (Low==Mid) )
        {
        	 //uc16Temp = (INT16U)Mid;
        	 break;
        }
	}
	//放大100倍，偏移-4000
	if(TempData > TempSeatAdTable_New_Dr[Mid])
	{
		uc16DecPoint = (TempData -TempSeatAdTable_New_Dr[Mid-1])*100/(TempSeatAdTable_New_Dr[Mid-1] - TempSeatAdTable_New_Dr[Mid]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	}
	else
	{
		uc16DecPoint = (TempSeatAdTable_New_Dr[Mid] - TempData)*100/(TempSeatAdTable_New_Dr[Mid] - TempSeatAdTable_New_Dr[Mid+1]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	}

    return  (uc16Temp/10);
}
/*******************************************************************************
* 函数名称：INT16U Cdd_Ntc_AdToTemp_New_Pa(INT16U TempData)
* 功能描述：温度查表
* 入口参数：温度AD值
* 出口参数：
* 返 回 值：	温度值
* 备    注: 偏移-40度，放大10倍
*******************************************************************************/
INT16U Cdd_Ntc_AdToTemp_New_Pa(INT16U TempData)
{
	INT16U High = (TEMP_STABLE_SIZE - 1);
	INT16U Low = 0;
	INT16U uc16Temp = 0;
	INT16U uc16DecPoint = 0;
	INT16U Mid = (INT16U)(High + Low) / 2;
	INT16U Sequence = SEQ_RISING;
	//INT16U TempData = TempDat-160;

	const INT16U* TempSeatAdTable_New_Pa = NULL;
	TempSeatAdTable_New_Pa = TempSeatAdTable_New_Pa0;

	//判断表格升降序
	if( TempSeatAdTable_New_Pa[0] < TempSeatAdTable_New_Pa[TEMP_STABLE_SIZE - 1] )
	{
		Sequence = SEQ_RISING;
		//超出量程
		if( TempData < TempSeatAdTable_New_Pa[0] || TempData > TempSeatAdTable_New_Pa[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}
	else
	{
		Sequence = SEQ_LOWER;
		//超出量程
		if( TempData > TempSeatAdTable_New_Pa[0] || TempData < TempSeatAdTable_New_Pa[TEMP_STABLE_SIZE-1] )
		{
			return 0;
		}
	}

	//二分查找
	for(;;)
	{
		if( TempData < TempSeatAdTable_New_Pa[Mid] )
        {
            (Sequence==SEQ_RISING)?(High = Mid):(Low = Mid);
        }

        if( TempData > TempSeatAdTable_New_Pa[Mid] )
        {
            (Sequence==SEQ_RISING)?(Low = Mid):(High = Mid);
        }

        Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
        if( (TempData==TempSeatAdTable_New_Pa[Mid]) || (High==Mid) || (Low==Mid) )
        {
        	 //uc16Temp = (INT16U)Mid;
        	 break;
        }
	}
	//放大100倍，偏移-4000
	if(TempData > TempSeatAdTable_New_Pa[Mid])
	{
		uc16DecPoint = (TempData -TempSeatAdTable_New_Pa[Mid-1])*100/(TempSeatAdTable_New_Pa[Mid-1] - TempSeatAdTable_New_Pa[Mid]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	}
	else
	{
		uc16DecPoint = (TempSeatAdTable_New_Pa[Mid] - TempData)*100/(TempSeatAdTable_New_Pa[Mid] - TempSeatAdTable_New_Pa[Mid+1]);
		if(uc16DecPoint > 100)
		{
			uc16DecPoint = 100;
		}
		uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	}

    return  (uc16Temp/10);
}
/***********************************************************************************************
 * @function name:  Cdd_Ntc_GetSeatAd
 * @description:	获取ad值
 * @input parameters: AdType ad标定标类型 ; index:ad索引
 * @output parameters:
 * @return:         void
 * @note:           void
 * @author:         zxj 2023-12-11
 ***********************************************************************************************/
INT16U Cdd_Ntc_GetSeatAd(EN_SeatADType AdType, INT8U index)
{
	INT16U AD_Value = 0;
	const INT16U* TempSeatAdTable = NULL;
	INT8U tableSize = 0;
	switch(AdType)
	{
		case EN_AD_DrOld :
			TempSeatAdTable = TempSeatAdTable_Old_Dr;
			tableSize = sizeof(TempSeatAdTable_Old_Dr) / sizeof(TempSeatAdTable_Old_Dr[0]);
			break;

		case EN_AD_DrNew :
			TempSeatAdTable = TempSeatAdTable_New_Dr0;
			tableSize = sizeof(TempSeatAdTable_New_Dr0) / sizeof(TempSeatAdTable_New_Dr0[0]);
			break;

		case EN_AD_PaOld :
			TempSeatAdTable = TempSeatAdTable_Old_Pa;
			tableSize = sizeof(TempSeatAdTable_Old_Pa) / sizeof(TempSeatAdTable_Old_Pa[0]);
			break;

		case EN_AD_PaNew :
			TempSeatAdTable = TempSeatAdTable_New_Pa0;
			tableSize = sizeof(TempSeatAdTable_New_Pa0) / sizeof(TempSeatAdTable_New_Pa0[0]);
			break;
		default:
			return 0;
			break;
	}


	if(index < tableSize)
	{
		AD_Value = TempSeatAdTable[index];
	}
	else
	{
		AD_Value = 0;
	}
	return AD_Value;
}
/*-------------------------------------------------------------------------
* Function Name : Cdd_Ntc_Task
* Description   :检测温度任务
* Date          : 2019/May/22
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
void Cdd_Ntc_Task(void)
{
//	static INT8U IsNewHard = FALSE;
//    static INT8U s_IsNewHardTime = 20;
//    const INT8U HardCheckMaxTime = 20;
//	Input_SEAT_HEAT_DR_NTCSensor_Proc();
//	Input_SEAT_HEAT_PA_NTCSensor_Proc();
//
//	//判断新旧版本硬件-旧版本记忆按键5V 新版本0V
//	if(EN_MOTOR_DEF == SEAT_HEIGHT_CMD_Get()
//	 && EN_MOTOR_DEF == SEAT_LENGTH_CMD_Get()
//     && EN_MOTOR_DEF == SEAT_BACKREST_CMD_Get())
//	{
//	    /* 纵向堵转时候，Y9电压会上升到1200AD值，故需增加判断 */
//	    if(s_IsNewHardTime >= HardCheckMaxTime)
//	    {
//	        if(Ecual_GetAD_MesVal(eADCCH_EX4067_OUT2_SW_Chl9) <= AD_NEW_HARD)
//	        {
//	            IsNewHard = TRUE;
//	        }
//	        else
//	        {
//	            IsNewHard = FALSE;
//	        }
//	    }
//	    else
//	    {
//	        s_IsNewHardTime += 1;
//	    }
//	}
//	else
//	{
//	    s_IsNewHardTime = 0;
//	}
//
//	if(TRUE == Ecual_GetMesFinishFlg(eADCCH_EX4067_OUT2_SW_Chl10))
//	{
//		if(IsNewHard == FALSE)
//		{
//			//旧版本硬件-使用旧的ad表
//			ScanTempVal.SeatHeatDRNtc = Cdd_Ntc_AdToTemp(Ecual_GetAD_MesVal(eADCCH_EX4067_OUT2_SW_Chl10));
//		}
//		else
//		{
//			//新版本硬件-使用新的ad表-主驾
//			ScanTempVal.SeatHeatDRNtc = Cdd_Ntc_AdToTemp_New_Dr(Ecual_GetAD_MesVal(eADCCH_EX4067_OUT2_SW_Chl10));
//		}
//		if(ScanTempVal.SeatHeatDRNtc > 1650)
//		{
//			ScanTempVal.SeatHeatDRNtc = 1650;
//		}
//	}
//	if(TRUE == Ecual_GetMesFinishFlg(eADCCH_EX4067_OUT2_SW_Chl11))
//	{
//		/*AD检测完成*/
//		if(IsNewHard == FALSE)
//		{
//			//旧版本硬件-使用旧的ad表
//			ScanTempVal.SeatHeatPANtc = Cdd_Ntc_AdToTemp(Ecual_GetAD_MesVal(eADCCH_EX4067_OUT2_SW_Chl11));
//		}
//		else
//		{
//			//新版本硬件-使用新的ad表-主驾
//			ScanTempVal.SeatHeatPANtc = Cdd_Ntc_AdToTemp_New_Pa(Ecual_GetAD_MesVal(eADCCH_EX4067_OUT2_SW_Chl11));
//		}
//		if(ScanTempVal.SeatHeatPANtc > 1650)
//		{
//			ScanTempVal.SeatHeatPANtc = 1650;
//		}
//	}
}

/*-------------------------------------------------------------------------
* Function Name : Cdd_Ntc_Task
* Description   :检测温度任务
* Date          : 2019/May/22
* Parameter     :
* Return Code   :
* Author        :
-------------------------------------------------------------------------*/
ST_ScanTempVal Cdd_Ntc_GetTemp(void)
{
	return ScanTempVal;
}
