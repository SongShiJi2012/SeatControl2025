#include "Ecual_Adc.h"
#include "adc_driver.h"
#include "MidRelay.h"
#include  "DSM.h"
#include "edma_driver.h"
#include "kf32a156_dma.h"
#include "kf32a156_adc.h"

static void Ecual_ADCChlxClrBuff(INT8U chl);
static void Ecual_SetAD_MesVal(eADCCH Chl, INT16U Val);
static  INT8U Ecual_ADChlAverage(INT8U chl);

static INT16U BoardAdcChlSta[enADC_MAx] = {0}; /*����ADͨ����״̬���ѹֵ*/

static void Ecual_AdcSwitchChlDoNothing(void)
{
    /*�պ���*/
}

/* �¶ȱ� */
const static INT16U s_TempValueTable[]=
{
	/* BM400 ����˿�����궨���� ��P20�����һ��*/
	3404,3393,3372,3350,3328,3305,3283,3258,3234,3209,/* -40 - -31 */
	3182,3157,3155,3099,3071,3047,3014,2985,2946,2916, /* -30 - -21 */
	2863,2850,2816,2783,2747,2712,2675,2639,2601,2566, /* -20 - -11 */
	2527,2488,2451,2412,2373,2333,2294,2255,2215,2174, /* -10 - -1  */
	2136,2095,2056,2016,1977,1940,1898,1862,1819,1781, /*   0 -  9  */
	1746,1704,1667,1633,1593,1556,1518,1486,1446,1419, /*  10 -  19 */
	1383,1346,1316,1287,1255,1223,1193,1163,1133,1104, /*  20 -  29 */
	1076,1050,1021,996,969,943,920,895,872,849,     /*  30 -  39 */
	826,804,782,762,741,721,702,695,664,645, /*  40 -  49 */
	628,619,595,578,562,548,534,519,506,492,	/*  50 -  59 */
	478,465,453,440,429,417,406,396,385,375,	 /*  60 -  69 */
	365,355,346,336,328,319,311,303,295,287,	/*  70 -  79 */
	280,273,266,259,253,246,239,234,228,223,	/*  80 -  89*/
	217,211,206,201,196,191,187,183,178,174,170,	/*  90 -  99*/
};

/* �������¶ȱ� */
const static INT16U s_TempValueTable4Steer[]=
{
	/* P20������ ����˿�����궨���� */
	3411,3393,3372,3350,3328,3306,3283,3259,3234,3209,/* -40 - -31 */
	3184,3157,3130,3099,3070,3040,3010,2978,2947,2915,/* -30 - -21 */
	2882,2849,2815,2781,2746,2710,2674,2638,2601,2563,/* -20 - -11 */
	2526,2488,2449,2411,2372,2334,2295,2256,2216,2177,/* -10 - -1  */
	2139,2098,2059,2018,1979,1939,1901,1862,1823,1785,/*   0 -  9  */
	1747,1709,1672,1635,1599,1562,1527,1491,1456,1423,/*  10 -  19 */
	1389,1356,1323,1291,1260,1228,1198,1168,1138,1110,/*  20 -  29 */
	1082,1055,1027,1001,975,950,925,901,878,855,    /*  30 -  39 */
	832,811,789,768,748,728,709,690,670,653,/*  40 -  49 */
	636,619,602,586,571,555,541,526,511,499,/*  50 -  59 */
	486,473,461,448,436,425,414,403,393,383,/*  60 -  69 */
	373,363,353,345,335,327,319,310,303,295,/*  70 -  79 */
	287,280,273,266,259,253,247,240,235,229,/*  80 -  89*/
	223,218,213,207,203,198,193,189,184,179,175 /*  90 -  99*/
	 
};
/* ����NTC�¶ȱ� */
const static INT16U s_BoardTempValueTable[]=
{
	3949,3941,3933,3925,3917,3907,3898,3889,3880,3871,	/* -40 - -31 */
	3864,3856,3848,3839,3826,3813,3800,3787,3776,3761,	/* -30 - -21 */
	3746,3731,3716,3701,3684,3667,3650,3633,3615,3594,	/* -20 - -11 */
	3573,3552,3531,3512,3489,3466,3443,3420,3399,3376,	/* -10 - -1  */
	3353,3330,3307,3284,3258,3232,3206,3180,3154,3128,	/*	 0 -  9  */
	3100,3072,3044,3016,2988,2959,2932,2905,2878,2851,	/*	10 -  19 */
	2826,2797,2768,2739,2710,2679,2494,2309,2124,1939,	/*	20 -  29 */
	2529,2474,2419,2364,2309,2255,2236,2217,2198,2179,	/*	30 -  39 */
	2159,2138,2117,2096,2075,2054,2030,2006,1982,1958,	/*	40 -  49 */
	1935,1899,1863,1827,1791,1755,1710,1665,1620,1575,	/*	50 -  59 */
	1531,1478,1425,1372,1319,1268,1268,1268,1268,1268,	/*	60 -  69 */
	1266,1232,1198,1164,1130,1097,1084,1071,1058,1045,	/*	70 -  79 */
	1032,1010,988,966,944,922,898,874,850,826,		    /*	80 -  89*/
	801,790,779,768,757,746,735,724,713,702,			/*	90 -  99*/
	/*693,682,671,660,649,638,627,616,605,594,580,*/
};

static INT16U s_EcualAdcDrNtcTemp = 0;
static INT16U s_EcualAdcPaNtcTemp = 0;
static INT16U s_EcualAdcSecondNtcTemp = 0;
static INT16U s_EcualAdcCenterNtcTemp = 0;	//�����̼����¶�
static INT16U s_EcualAdcBoardNtcTemp = 0;
#define D_TEMP_STABLE_SIZE  (sizeof(s_TempValueTable)/sizeof(INT16U))
#define D_TEMP_STABLE_SIZE_STEER  (sizeof(s_TempValueTable4Steer)/sizeof(INT16U))
#define D_BOARDTEMP_STABLE_SIZE  (sizeof(s_BoardTempValueTable)/sizeof(INT16U))
#define D_SEQ_RISING        (0UL)        //����
#define D_SEQ_LOWER         (1UL)        //����
#define D_HD7008_KILIS		(5400UL) /*HD7008-1 ����ת��ϵ�� ratio kILIS = IL / IIS*/
#define D_HD7008_Ris		(2000UL) /*���������Ĳ���������ֵ*/
#if 0
strADCChlManage ADCChlManage[enADC_MAx]=
{
    {ADCx_0,    Chl_41,     enADC_DrHeightHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_40,     enADC_DrLengthHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_42,     enADC_DrBackHallFB,        ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_43,     enADC_DrFrontHallFB,       ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_0,      enADC_PaLengthHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_92,     enADC_PaBackHallFB,        ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

    {ADCx_0,    Chl_70,     enADC_DrHeightMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_58,     enADC_DrLengthMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_69,     enADC_DrBackMotorIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_55,     enADC_DrFrontMotorIS,      ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_56,     enADC_PaLengthMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_72,     enADC_PaBackMotorIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

    {ADCx_0,    Chl_20,     enADC_DrHeaterIS,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_78,     enADC_PaHeaterIS,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_22,     enADC_Heater3IS,           ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_22,     enADC_Heater4IS,           ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_86,     enADC_SteerHeaterIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

    {ADCx_0,    Chl_45,     enADC_DrHeaterNTC,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_74,     enADC_PaHeaterNTC,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_14,     enADC_NTC3,                ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_15,     enADC_NTC4,                ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_75,     enADC_SteerHeaterNTC,      ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_76,     enADC_BoardNTC,            ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

    {ADCx_0,    Chl_79,     enADC_HallPowerFB,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_95,     enADC_MemoryAdjSw,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_81,     enADC_KL30Detect,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
};
#endif

INT32U Dma0_Adc0_Buf[D_ADC0_CONTINUOUS_CHANNEL_NUM] = {0};//DAM���˵�ַ
INT32U Dma1_Adc1_Buf[D_ADC1_CONTINUOUS_CHANNEL_NUM] = {0};
INT32U Dma1_Adc2_Buf[D_ADC2_CONTINUOUS_CHANNEL_NUM] = {0};
INT32U Dma_Adc_AllBuf[enADC_MAx] = {0};
static BOOL Dma0_Adc0_UpdateFlag = 0;//�жϱ�־λ
static BOOL Dma1_Adc1_UpdateFlag = 0;
static BOOL Dma1_Adc2_UpdateFlag = 0;
#if 1

// ע�⣺DMA�����ɼ�ģʽ�£�ADC0��ADC1��ADC2�����γ�ʼ������������˳����ܴ��ҡ�
// ÿ��ADC�����ɼ����֧��16��ͨ����о��΢KF32A156����
strADCChlManage ADCChlManage[enADC_MAx]=
{
    {ADCx_0,    Chl_41,     enADC_DrHeightHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_40,     enADC_DrLengthHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_42,     enADC_DrBackHallFB,        ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_43,     enADC_DrFrontHallFB,       ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_0,      enADC_PaLengthHallFB,      ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_0,    Chl_92,     enADC_PaBackHallFB,        ChlSw_ON,       ChlFullSta_NO,  1,0,    HALL_BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

	{ADCx_1,    Chl_70,     enADC_DrHeightMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_58,     enADC_DrLengthMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_69,     enADC_DrBackMotorIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_55,     enADC_DrFrontMotorIS,      ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_56,     enADC_PaLengthMotorIS,     ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_72,     enADC_PaBackMotorIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_20,     enADC_DrHeaterIS,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_78,     enADC_PaHeaterIS,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_22,     enADC_Heater3IS,           ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_22,     enADC_Heater4IS,           ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
	{ADCx_1,    Chl_86,     enADC_SteerHeaterIS,       ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_45,     enADC_DrHeaterNTC,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_74,     enADC_PaHeaterNTC,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_14,     enADC_NTC3,                ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_15,     enADC_NTC4,                ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_1,    Chl_75,     enADC_SteerHeaterNTC,      ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},

    {ADCx_2,    Chl_76,     enADC_BoardNTC,            ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_2,    Chl_79,     enADC_HallPowerFB,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_2,    Chl_95,     enADC_MemoryAdjSw,         ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
    {ADCx_2,    Chl_81,     enADC_KL30Detect,          ChlSw_ON,       ChlFullSta_NO,  1,0,    BUFF_SIZE,0,       ChlErr_OK,  {0}, Ecual_AdcSwitchChlDoNothing, FALSE, 0U},
};
#endif
/***********************************************************************************************
 * @function name:  Ecual_ADC_ConfigChannelSequence
 * @description:    �������� ADC0 �� ADC1 �� ADC2 �ĳ���ͨ������
 * @input parameters:  ��
 * @output parameters: ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void Ecual_ADC_ConfigChannelSequence(void)
{
    INT8U i = 0u;
    INT8U Ch = 0u;

    for (i = 0u; i < D_ADC0_CONTINUOUS_CHANNEL_NUM; i++)
    {
        Ch = i;
        ADC_DRV_RegularChannelConfig(ADCChlManage[Ch].ADCx, ADCChlManage[Ch].ADCxChl, i);
    }

    for (i = 0u; i < D_ADC1_CONTINUOUS_CHANNEL_NUM; i++)
    {
        Ch = i + D_ADC0_CONTINUOUS_CHANNEL_NUM;
        ADC_DRV_RegularChannelConfig(ADCChlManage[Ch].ADCx, ADCChlManage[Ch].ADCxChl, i);
    }

    for(i = 0u; i < D_ADC2_CONTINUOUS_CHANNEL_NUM; i++)
    {
        Ch = i + D_ADC0_CONTINUOUS_CHANNEL_NUM + D_ADC1_CONTINUOUS_CHANNEL_NUM;
        ADC_DRV_RegularChannelConfig(ADCChlManage[Ch].ADCx, ADCChlManage[Ch].ADCxChl, i);
    }
}

/********************************************************************
* �������ƣ�Ecual_AD_BuffInit
* ����������ADBuff��ʼ��
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Ecual_AD_BuffInit(void)
{
    INT8U chl = 0;

    for(chl = 0; chl < enADC_MAx; chl++)
    {
        Ecual_ADCChlxClrBuff(chl);
    }
    //�������������
    memset(Dma0_Adc0_Buf, 0, sizeof(Dma0_Adc0_Buf));
    memset(Dma1_Adc1_Buf, 0, sizeof(Dma1_Adc1_Buf));
    memset(Dma1_Adc2_Buf, 0, sizeof(Dma1_Adc2_Buf));
}
/***********************************************************************************************
 * @function name:  Ecual_ADC_SoftwareStartConv
 * @description:    ������� ADC0 �� ADC1 ����ת��
 * @input parameters:  ��
 * @output parameters: ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void Ecual_ADC_SoftwareStartConv(void)
{
    /* ��ǰ��� DMA ���ݸ��±�־λ  �������ʱ DMA����ǰ����ж� */
	Ecual_SetDma1_Adc1_UpdateFlag(FALSE);
	Ecual_SetDma1_Adc2_UpdateFlag(FALSE);
    ADC_DRV_SoftwareStartConv(ADCx_1);
    ADC_DRV_SoftwareStartConv(ADCx_2);
}
/***********************************************************************************************
 * @function name:  Ecual_ADC_Init
 * @description:    ADCģ���ʼ��������DMAͨ����ʼ����ͨ��ɨ��ģʽ���á��������á�DMA���ʺ��ж�����
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void Ecual_ADC_Init(void)
{
	ADC_DMA_NormalChl_Init(ADC0_SFR, DMA0_SFR, DMA_CHANNEL_5, Dma0_Adc0_Buf, D_ADC0_CONTINUOUS_CHANNEL_NUM, TRUE);
	ADC_DMA_NormalChl_Init(ADC1_SFR, DMA1_SFR, DMA_CHANNEL_5, Dma1_Adc1_Buf, D_ADC1_CONTINUOUS_CHANNEL_NUM, TRUE);
	ADC_DMA_NormalChl_Init(ADC2_SFR, DMA1_SFR, DMA_CHANNEL_7, Dma1_Adc2_Buf, D_ADC2_CONTINUOUS_CHANNEL_NUM, FALSE);

	// ����ADC0��ɨ��D_ADC0_CONTINUOUS_CHANNEL_NUM��ͨ��
	ADC_DRV_InitScanMode(ADC0_SFR, D_ADC0_CONTINUOUS_CHANNEL_NUM);
	// ����ADC1��ɨ��D_ADC1_CONTINUOUS_CHANNEL_NUM��ͨ��
	ADC_DRV_InitScanMode(ADC1_SFR, D_ADC1_CONTINUOUS_CHANNEL_NUM);
	// ����ADC2��ɨ��D_ADC2_CONTINUOUS_CHANNEL_NUM��ͨ��
	ADC_DRV_InitScanMode(ADC2_SFR, D_ADC2_CONTINUOUS_CHANNEL_NUM);

	Ecual_ADC_ConfigChannelSequence();

	/* ������ͨͨ�� DMA �ڴ����ģʽ */
	ADC_Regular_Channel_DMA_Cmd(ADC0_SFR, TRUE);
	ADC_Regular_Channel_DMA_Cmd(ADC1_SFR, TRUE);
	ADC_Regular_Channel_DMA_Cmd(ADC2_SFR, TRUE);

	/* ���� DMA �����ж�ģʽ  - �ж���ռ���ȼ�4���ж������ȼ� 0*/
	ADC_DMA_Int_Config(DMA0_SFR, DMA_CHANNEL_5, INT_DMA0, 4u, 0u); // ��Ӧ ADC0
	ADC_DMA_Int_Config(DMA1_SFR, DMA_CHANNEL_5, INT_DMA1, 5u, 0u); // ��Ӧ ADC1
	ADC_DMA_Int_Config(DMA1_SFR, DMA_CHANNEL_7, INT_DMA1, 5u, 0u); // ��Ӧ ADC2

	/* ���������ж� */
	INT_All_Enable(TRUE);

	/* ȡ����ʼ������ ����DMA��ģ��E2��ʼ���ĳ�ͻ */
//	Ecual_ADC_SoftwareStartConv();
	Ecual_AD_BuffInit();
}

/*******************************************************************************
* �������ƣ�Ecual_AD_MeasureChan
* ����������AD�ɼ�
* ��ڲ����� Channel: �ɼ���ͨ��
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
INT8U Ecual_AD_MeasureChan(INT8U Channel, INT16U *pADValue)
{
	if(ChlSw_ON == ADCChlManage[Channel].ChlSw)/* ͨ���򿪲Ų��� */
	{
		enADCx ADCx = ADCChlManage[Channel].ADCx;
		enumADCxChl ADCxChl = ADCChlManage[Channel].ADCxChl;
		if(ADCx < ADCx_Max)
		{
//			ADC_DRV_RegularChannelConfig(ADCx, ADCxChl);
			ADC_DRV_SoftwareStartConv(ADCx);

			for(;;)//���￼���Ƿ����ӳ�ʱ���ƣ�
			{
				while(!ADC_DRV_GetConvCompleteFlag(ADCx));
				*pADValue = ADC_DRV_GetConversionValue(ADCx);
				return ERR_OK;
			}
		}

	}
	
	return ERR_NOTAVAIL;
}

/*******************************************************************************
* �������ƣ�void Ecual_ADCChlxClrBuff(INT8U chl)
* ����������ͨ�������������
* ��ڲ�����chl-��Ҫ�˲���ͨ��
* ���ڲ�����
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
static void Ecual_ADCChlxClrBuff(INT8U chl)
{
	INT8U i = 0;
	
	if(chl < enADC_MAx)
	{
		ADCChlManage[chl].ChlFullSta = ChlFullSta_NO;
		ADCChlManage[chl].MesFinishFlg = FALSE;
		Ecual_SetAD_MesVal(chl, 0);
		for(i = 0;i < ADCChlManage[chl].SampleNum;i++)
		{
			ADCChlManage[chl].SampleBuffer[i] = 0;
			ADCChlManage[i].SampleIndex = 0;
			ADCChlManage[i].SampleCycCnt = 0;
		}
	}
}

/*******************************************************************************
* �������ƣ�INT8U Ecual_ADChlAverage(INT8U chl)
* ����������ͨ���˲���ƽ��
* ��ڲ�����chl-��Ҫ�˲���ͨ��
* ���ڲ�����FALSE-�˲��������,TRUE-�˲����������
* �� �� ֵ����
* ��    ע: ��
*******************************************************************************/
static INT8U Ecual_ADChlAverage(INT8U chl)
{
	INT8U ret = FALSE;
	INT8U i = 0;
	INT16U TempValue = 0;
	INT16U ADValMax = 0x00;
	INT16U ADValMin = 0xFFFF;
	
	/*����ͨ���޴���,ͨ����������*/
	if((ChlErr_OK == ADCChlManage[chl].ErrorFlag) && (ChlFullSta_OK == ADCChlManage[chl].ChlFullSta))
	{
		/* AD ��ֵ����˲�*/
		for (i = 0; i < ADCChlManage[chl].SampleNum; i++)
		{
			TempValue += ADCChlManage[chl].SampleBuffer[i];
			/*��ȡ���ֵ����Сֵ*/
			if (ADValMax < ADCChlManage[chl].SampleBuffer[i])
	        {
	            ADValMax = ADCChlManage[chl].SampleBuffer[i];
	        }
	        if (ADValMin > ADCChlManage[chl].SampleBuffer[i])
	        {
	            ADValMin = ADCChlManage[chl].SampleBuffer[i];
	        }
		}
		/*��ȡƽ��ֵ*/
		i = ADCChlManage[chl].SampleNum;
		if(ADCChlManage[chl].SampleNum > 2u)
		{
			i = ADCChlManage[chl].SampleNum - 2u; /*������ƽ���ĸ���*/
			TempValue = TempValue - ADValMax - ADValMin; /*ȥ�����ֵ��Сֵ*/
		}
		if(i != 0u)
		{
			Ecual_SetAD_MesVal(chl, TempValue/i);/*��ƽ��*/
		}
		else
		{
			Ecual_SetAD_MesVal(chl, 0u);
		}
		
		ret = TRUE;
	}
	return ret;
}

#if 1
/***********************************************************************************************
 * @function name:  Ecual_AD_Step_Task
 * @description:    ��ʱ������ִ��AD�������񣬸���ͨ�����ý���ADת�����������ݣ��������ƽ��ֵ��������ɱ�־
 * @input parameters:     void
 * @output parameters:     void
 * @return:         void
 * @author:         ssj 2025-05-27
 ***********************************************************************************************/
void Ecual_AD_Step_Task(void)
{
	INT8U i = 0;
	INT16U AD_Value = 0;
	strADCChlManage *pChl = NULL;

	for(i = enADC_DrHeightMotorIS; i < enADC_MAx; i++)
	{
		pChl = &ADCChlManage[i];
		if(ERR_OK == Ecual_AD_MeasureChan(i, &AD_Value)) /* �����ɹ� */
		{
			pChl->ErrorFlag = ChlErr_OK;
			pChl->SampleBuffer[pChl->SampleIndex] = AD_Value;

			pChl->SampleIndex += 1u;
			if(pChl->SampleIndex >= pChl->SampleNum) /* �������� */
			{
				pChl->SampleIndex = 0;
				pChl->ChlFullSta = ChlFullSta_OK;

				if(TRUE == Ecual_ADChlAverage(i)) /* ����ƽ��ֵ�ɹ� */
				{
					Ecual_SetMesFinishFlg(i, TRUE); /* ����ͨ���ɼ���ɱ�־ */
				}
			}
		}
		else
		{
			pChl->ErrorFlag = ChlErr_ERR; /* ����ʧ�� */
			pChl->ChlFullSta = ChlFullSta_NO; /* ͨ��δ������״̬��� */
		}
	}
}
/***********************************************************************************************
 * @function name:  Ecual_UpdateAdcChlSampleBuffer
 * @description:    �������� ADC ͨ���Ĳ��������������ж��Ƿ�ɼ����
 * 					ע��������AD���жϴ���
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
static void Ecual_UpdateAdcChlSampleBuffer(void)
{
	INT8U i = 0;
	INT16U AD_Value = 0;
	strADCChlManage *pChl = NULL;

	for(i = enADC_DrHeightMotorIS; i < enADC_MAx; i++)
	{
		pChl = &ADCChlManage[i];

		//��ȡAD����
		AD_Value = Dma_Adc_AllBuf[i];

		pChl->ErrorFlag = ChlErr_OK;
		pChl->SampleBuffer[pChl->SampleIndex] = AD_Value;

		pChl->SampleIndex += 1u;
		if(pChl->SampleIndex >= pChl->SampleNum) /* �������� */
		{
			pChl->SampleIndex = 0;
			pChl->ChlFullSta = ChlFullSta_OK;

			if(TRUE == Ecual_ADChlAverage(i)) /* ����ƽ��ֵ�ɹ� */
			{
				Ecual_SetMesFinishFlg(i, TRUE); /* ����ͨ���ɼ���ɱ�־ */
			}
		}
	}
}

#endif
/********************************************************************
* �������ƣ�Ecual_GetMesFinishFlg
* ������������ȡAD�ɼ���ɱ�־
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
BOOL Ecual_GetMesFinishFlg(eADCCH Chl)
{
	BOOL temp = FALSE;

	if(Chl < enADC_MAx)
	{
		if(TRUE == ADCChlManage[Chl].MesFinishFlg)
		{
			temp = TRUE;
			ADCChlManage[Chl].MesFinishFlg = FALSE;
		}
	}

    return temp;
}

/********************************************************************
* �������ƣ�Ecual_SetMesFinishFlg
* ��������������AD�ɼ���ɱ�־
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
void Ecual_SetMesFinishFlg(eADCCH Chl, BOOL Flg)
{
	if(Chl < enADC_MAx)
	{
		ADCChlManage[Chl].MesFinishFlg = Flg;
	}
}
/********************************************************************
* �������ƣ�Ecual_GetAD_MesVal
* ������������ȡADֵ
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
INT16U Ecual_GetAD_MesVal(eADCCH Chl)
{
	INT16U  MesVal;
	if(Chl < enADC_MAx)
	{
		MesVal =  ADCChlManage[Chl].MesVal;
	}
	return MesVal;
}

/********************************************************************
* �������ƣ�Ecual_SetAD_MesVal
* ��������������ADֵ
* ��ڲ�������
* ���ڲ�������
* �� �� ֵ����
* ��    ע: ��
********************************************************************/
static void Ecual_SetAD_MesVal(eADCCH Chl, INT16U Val)
{
	if(Chl < enADC_MAx)
	{
		ADCChlManage[Chl].MesVal = Val;
	}
}
/*************************************************************************************************
 * Functions define
 *************************************************************************************************/
/***********************************************************************
 * @function name: Ecual_GetAllAdcValue
 *
 * @description: ��ȡ��������ADͨ����ԭʼֵ
 *
 * @input parameters: void
 *
 * @output parameters: BoardAdcChlSta
 *
 * @return: void
 *
 * @note:
 *
 * @author: hqj
 *
 * @date: 2023-10-20 13:17
 ***********************************************************************/
static void Ecual_GetAllAdcValue(void)
{
	eADCCH ADChlIndx;
	INT16U ADC_Value = 0x0U;	
	INT32U u32Temp = 0;

	for(ADChlIndx = enADC_DrHeightMotorIS; ADChlIndx < enADC_MAx; ADChlIndx ++)
	{
		if((ADChlIndx == enADC_DrHeaterIS) || (ADChlIndx == enADC_PaHeaterIS) || (ADChlIndx == enADC_SteerHeaterIS))
		{
			ADC_Value = Ecual_GetAD_MesVal(ADChlIndx);
			/*����ֵ =     (������ѹ*����ϵ��) /��������*/
			u32Temp = (INT16U)((float)((ADC_Value *5000)>>12));
			u32Temp = u32Temp * D_HD7008_KILIS;
			u32Temp = u32Temp / D_HD7008_Ris;
			BoardAdcChlSta[ADChlIndx] = (INT16U)u32Temp;
		}
		else
		{
			BoardAdcChlSta[ADChlIndx] = Ecual_GetAD_MesVal(ADChlIndx);
		}
	}
}
/***********************************************************************
 * @function name: Ecual_AdcGetChlStatus
 *
 * @description: ��ȡģ�������˿�״̬
 *
 * @input parameters: eADCCH ADChl : ADͨ����
 *
 * @output parameters: void
 *
 * @return: ADͨ��״̬
 *
 * @note:
 *
 * @author: Michael Xin
 *
 * @date: 2022-11-02 11:22
 ***********************************************************************/
INT16U Ecual_AdcGetChlStatus(eADCCH ADChl)
{
	INT16U ChlStatus = 0;

	if(ADChl < enADC_MAx)
	{
		ChlStatus = BoardAdcChlSta[ADChl];
	}

	return ChlStatus;
}
 
 /***********************************************************************
  * @function name: Ecual_AdcGetNtcAdcToTemp
  *
  * @description: �¶Ȳ��
  *
  * @input parameters: INT16U
  *
  * @output parameters: INT16U
  *
  * @return: INT16U
  *
  * @note: ƫ��-40�ȣ��Ŵ�10��
  *
  * @author: Michael Xin
  *
  * @date: 2023-4-25 09:50
  ***********************************************************************/
  INT16U Ecual_AdcGetNtcAdcToTemp(INT16U TempData)
 {
	 INT16U High = (D_TEMP_STABLE_SIZE - 1);
	 INT16U Low = 0;
	 INT16U uc16Temp = 0;
	 INT16U uc16DecPoint = 0;
	 INT16U Mid = (INT16U)(High + Low) / 2;
	 INT16U Sequence = D_SEQ_RISING;
	 //INT16U TempData = TempDat-160;
 
	 //�жϱ��������
	 if( s_TempValueTable[0] < s_TempValueTable[D_TEMP_STABLE_SIZE - 1] )
	 {
		 Sequence = D_SEQ_RISING;
		 //��������
		 if( TempData < s_TempValueTable[0] || TempData > s_TempValueTable[D_TEMP_STABLE_SIZE-1] )
		 {
			 return 0;
		 }
	 }
	 else
	 {
		 Sequence = D_SEQ_LOWER;
		 //��������
		 if( TempData > s_TempValueTable[0] || TempData < s_TempValueTable[D_TEMP_STABLE_SIZE-1] )
		 {
			 return 0;
		 }
	 }
 
	 //���ֲ���
	 for(;;)
	 {
		 if( TempData < s_TempValueTable[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(High = Mid):(Low = Mid);
		 }
 
		 if( TempData > s_TempValueTable[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(Low = Mid):(High = Mid);
		 }
 
		 Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
		 if( (TempData==s_TempValueTable[Mid]) || (High==Mid) || (Low==Mid) )
		 {
			 //uc16Temp = (INT16U)Mid;
			 break;
		 }
	 }
	 //�Ŵ�100����ƫ��-4000
	 if(TempData > s_TempValueTable[Mid])
	 {
		 uc16DecPoint = (TempData -s_TempValueTable[Mid-1])*100/(s_TempValueTable[Mid-1] - s_TempValueTable[Mid]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	 }
	 else
	 {
		 uc16DecPoint = (s_TempValueTable[Mid] - TempData)*100/(s_TempValueTable[Mid] - s_TempValueTable[Mid+1]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	 }
 
	 return  (uc16Temp/10);
 }
 
 
 /***********************************************************************
  * @function name: Ecual_AdcGetNtcAdcToTemp
  *
  * @description: �¶Ȳ�� - ������
  *
  * @input parameters: INT16U
  *
  * @output parameters: INT16U
  *
  * @return: INT16U
  *
  * @note: ƫ��-40�ȣ��Ŵ�10��
  *
  * @author: Michael Xin
  *
  * @date: 2023-4-25 09:50
  ***********************************************************************/
  INT16U Ecual_AdcGetNtcAdcToTemp4Steer(INT16U TempData)
 {
	 INT16U High = (D_TEMP_STABLE_SIZE_STEER - 1);
	 INT16U Low = 0;
	 INT16U uc16Temp = 0;
	 INT16U uc16DecPoint = 0;
	 INT16U Mid = (INT16U)(High + Low) / 2;
	 INT16U Sequence = D_SEQ_RISING;
	 //INT16U TempData = TempDat-160;
 
	 //�жϱ��������
	 if( s_TempValueTable4Steer[0] < s_TempValueTable4Steer[D_TEMP_STABLE_SIZE_STEER - 1] )
	 {
		 Sequence = D_SEQ_RISING;
		 //��������
		 if( TempData < s_TempValueTable4Steer[0] || TempData > s_TempValueTable4Steer[D_TEMP_STABLE_SIZE_STEER-1] )
		 {
			 return 0;
		 }
	 }
	 else
	 {
		 Sequence = D_SEQ_LOWER;
		 //��������
		 if( TempData > s_TempValueTable4Steer[0] || TempData < s_TempValueTable4Steer[D_TEMP_STABLE_SIZE_STEER-1] )
		 {
			 return 0;
		 }
	 }
 
	 //���ֲ���
	 for(;;)
	 {
		 if( TempData < s_TempValueTable4Steer[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(High = Mid):(Low = Mid);
		 }
 
		 if( TempData > s_TempValueTable4Steer[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(Low = Mid):(High = Mid);
		 }
 
		 Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
		 if( (TempData==s_TempValueTable4Steer[Mid]) || (High==Mid) || (Low==Mid) )
		 {
			 //uc16Temp = (INT16U)Mid;
			 break;
		 }
	 }
	 //�Ŵ�100����ƫ��-4000
	 if(TempData > s_TempValueTable4Steer[Mid])
	 {
		 uc16DecPoint = (TempData -s_TempValueTable4Steer[Mid-1])*100/(s_TempValueTable4Steer[Mid-1] - s_TempValueTable4Steer[Mid]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	 }
	 else
	 {
		 uc16DecPoint = (s_TempValueTable4Steer[Mid] - TempData)*100/(s_TempValueTable4Steer[Mid] - s_TempValueTable4Steer[Mid+1]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	 }
 
	 return  (uc16Temp/10);
 }
 
 /***********************************************************************
  * @function name: Ecual_AdcGetBoardNtcAdcToTemp
  * 
  * @description: �����¶�NTCת��
  * 
  * @input parameters: 
  * 
  * @output parameters: 
  * 
  * @return: 
  * 
  * @note: 
  * 
  * @author: Prima Niu
  * 
  * @date: 2024-09-05 11:44
  ***********************************************************************/
  INT16U Ecual_AdcGetBoardNtcAdcToTemp(INT16U TempData)
 {
	 INT16U High = (D_BOARDTEMP_STABLE_SIZE - 1);
	 INT16U Low = 0;
	 INT16U uc16Temp = 0;
	 INT16U uc16DecPoint = 0;
	 INT16U Mid = (INT16U)(High + Low) / 2;
	 INT16U Sequence = D_SEQ_RISING;
	 //INT16U TempData = TempDat-160;
 
	 //�жϱ��������
	 if( s_BoardTempValueTable[0] < s_BoardTempValueTable[D_BOARDTEMP_STABLE_SIZE - 1] )
	 {
		 Sequence = D_SEQ_RISING;
		 //��������
		 if( TempData < s_BoardTempValueTable[0] || TempData > s_BoardTempValueTable[D_BOARDTEMP_STABLE_SIZE-1] )
		 {
			 return 0;
		 }
	 }
	 else
	 {
		 Sequence = D_SEQ_LOWER;
		 //��������
		 if( TempData > s_BoardTempValueTable[0] || TempData < s_BoardTempValueTable[D_BOARDTEMP_STABLE_SIZE-1] )
		 {
			 return 0;
		 }
	 }
 
	 //���ֲ���
	 for(;;)
	 {
		 if( TempData < s_BoardTempValueTable[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(High = Mid):(Low = Mid);
		 }
 
		 if( TempData > s_BoardTempValueTable[Mid] )
		 {
			 (Sequence==D_SEQ_RISING)?(Low = Mid):(High = Mid);
		 }
 
		 Mid = (INT16U)(((INT16U)High + (INT16U)Low) / 2);
		 if( (TempData==s_BoardTempValueTable[Mid]) || (High==Mid) || (Low==Mid) )
		 {
			 //uc16Temp = (INT16U)Mid;
			 break;
		 }
	 }
	 //�Ŵ�100����ƫ��-4000
	 if(TempData > s_BoardTempValueTable[Mid])
	 {
		 uc16DecPoint = (TempData -s_BoardTempValueTable[Mid-1])*100/(s_BoardTempValueTable[Mid-1] - s_BoardTempValueTable[Mid]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)((Mid-1)*100 + uc16DecPoint);
	 }
	 else
	 {
		 uc16DecPoint = (s_BoardTempValueTable[Mid] - TempData)*100/(s_BoardTempValueTable[Mid] - s_BoardTempValueTable[Mid+1]);
		 if(uc16DecPoint > 100)
		 {
			 uc16DecPoint = 100;
		 }
		 uc16Temp = (INT16U)(Mid*100 + uc16DecPoint);
	 }
 
	 return  (uc16Temp/10);
 }
 
 
 /***********************************************************************
  * @function name: Ecual_AdcNtcTempValue
  *
  * @description: ntc�¶�
  *
  * @input parameters: void
  *
  * @output parameters: void
  *
  * @return: void
  *
  * @note: 
  *
  * @author: Michael Xin
  *
  * @date: 2023-4-25 09:50
  ***********************************************************************/
 static void Ecual_AdcNtcTempValue(void)
 {
 
	 static INT16U DrNtcVol = 0;
	 static INT16U PaNtcVol = 0;
	 static INT16U SteerNtcVol = 0;
	 static INT16U SecondNtcVol = 0;
	 static INT16U CenterNtcVol = 0;

 
	 DrNtcVol = Ecual_AdcGetChlStatus(enADC_DrHeaterNTC);
	 PaNtcVol = Ecual_AdcGetChlStatus(enADC_PaHeaterNTC);
	 CenterNtcVol = Ecual_AdcGetChlStatus(enADC_SteerHeaterNTC);
 
	 s_EcualAdcDrNtcTemp = Ecual_AdcGetNtcAdcToTemp(DrNtcVol);
	 s_EcualAdcPaNtcTemp = Ecual_AdcGetNtcAdcToTemp(PaNtcVol);
	 s_EcualAdcCenterNtcTemp = Ecual_AdcGetNtcAdcToTemp4Steer(CenterNtcVol);

 
	 ILPutTxDSM_2_DSM_DrNtcValue(s_EcualAdcDrNtcTemp);
	 
	  ILPutTxDSM_2_DSM_PaNtcValue(s_EcualAdcPaNtcTemp );
 
	  ILPutTxDSM_2_DSM_SteerNtcValue( s_EcualAdcCenterNtcTemp);
 
 
 }
 
 /***********************************************************************
  * @function name: Ecual_GetBoardTemp
  * 
  * @description: ��ȡ�����¶�
  * 
  * @input parameters: 
  * 
  * @output parameters: 
  * 
  * @return: 
  * 
  * @note: 
  * 
  * @author: Prima Niu
  * 
  * @date: 2024-09-03 10:58
  ***********************************************************************/
 static void Ecual_GetBoardTemp(void)
 {
	 INT16U u16BoardNTC = 0x0U;
	 //INT16U u16TestNTC,u16TestNTCVolt;
	 
	 /*u16TestNTC = Mcal_AdcGetCurrentValue(EN_ADC1_RSEQ_1);
	 u16TestNTCVolt = (u16TestNTC*HAL_ADC_VREF)>>12;*/
	 u16BoardNTC = Ecual_AdcGetChlStatus(enADC_BoardNTC);
	 s_EcualAdcBoardNtcTemp = Ecual_AdcGetBoardNtcAdcToTemp(u16BoardNTC);	 
 }
 /***********************************************************************
  * @function name: Ecual_SeatHeatNTCAcquire
  * 
  * @description: �����ݼ���NTC�ɼ�
  * 
  * @input parameters: 
  * 
  * @output parameters: 
  * 
  * @return: 
  * 
  * @note: ����NTC���
  * 
  * @author: Prima Niu
  * 
  * @date: 2023-03-20 14:15
  ***********************************************************************/
 static void Ecual_SeatHeatNTCAcquire(void)
 {
	 /*����NTC���*/
	 Ecual_AdcNtcTempValue();
	 Ecual_GetBoardTemp();/*����NTC���2024.9.3by Prima Niu*/
 }
 
 
 /***********************************************************************
  * @function name: Ecual_AdcGetDrNTCTempValue
  * 
  * @description: ��ȡ����ʻ�¶�
  * 
  * @input parameters: INT16U
  * 
  * @output parameters: void
  * 
  * @return: void
  * 
  * @note: 
  * 
  * @author: Zom
  * 
  * @date: 2023-4-21 
  ***********************************************************************/
  INT16U Ecual_AdcGetDrNTCTempValue(void)
  {
	 return s_EcualAdcDrNtcTemp;
 
  }
  
 /***********************************************************************
  * @function name: Ecual_AdcGetPaNTCTempValue
  * 
  * @description: ��ȡ����ʻ�¶�
  * 
  * @input parameters: INT16U
  * 
  * @output parameters: void
  * 
  * @return: void
  * 
  * @note: 
  * 
  * @author: Zom
  * 
  * @date: 2023-4-21 
  ***********************************************************************/
  INT16U Ecual_AdcGetPaNTCTempValue(void)
  {
	 return s_EcualAdcPaNtcTemp;
  }
 /*��ʱ����*/
  INT16U Ecual_AdcGetSecondNTCTempValue(void)
  {
	 return s_EcualAdcSecondNtcTemp;
 
  }
 
  
  /***********************************************************************
   * @function name: Ecual_AdcGetCenterNTCTempValue
   * 
   * @description: ���������¶Ȼ�ȡ
   * 
   * @input parameters: 
   * 
   * @output parameters: 
   * 
   * @return: 
   * 
   * @note: 
   * 
   * @author: Prima Niu
   * 
   * @date: 2022-03-26 18:39
   ***********************************************************************/
  INT16U Ecual_AdcGetCenterNTCTempValue(void)
  {
	 return s_EcualAdcCenterNtcTemp;
 
  } 
 
 /***********************************************************************
  * @function name: Ecual_ADC_GetCurrentBoardTemp
  * 
  * @description: ��ȡ��ǰ�����¶Ƚӿ�
  * 
  * @input parameters: 
  * 
  * @output parameters: 
  * 
  * @return: 
  * 
  * @note: 
  * 
  * @author: Prima Niu
  * 
  * @date: 2024-09-05 13:53
  ***********************************************************************/
 INT16U Ecual_ADC_GetCurrentBoardTemp(void)
 {
	 return s_EcualAdcBoardNtcTemp;  
 }

/***********************************************************************************************
* @function name: Ecual_SetDma0_Adc0_UpdateFlag
* @description: ���� DMA0 ADC0 ���ݸ��±�־
* @input parameters: flag: TRUE �� FALSE
* @output parameters: ��
* @return: ��
* @author: ssj 2025-06-12
***********************************************************************************************/
void Ecual_SetDma0_Adc0_UpdateFlag(BOOL flag)
{
	Dma0_Adc0_UpdateFlag = flag;
}
/***********************************************************************************************
 * @function name: Ecual_SetDma1Adc2UpdateFlag
 * @description: ���� ADC2 DMA1 ���±�־״̬
 * @input parameters: BOOL flag - �����õĸ��±�־״̬
 * @output parameters: ��
 * @return: ��
 * @author: ssj 2025-06-27
 ***********************************************************************************************/
void Ecual_SetDma1_Adc2_UpdateFlag(BOOL flag)
{
    Dma1_Adc2_UpdateFlag = flag;
}

/***********************************************************************************************
 * @function name: Ecual_GetDma1Adc2UpdateFlag
 * @description: ��ȡ ADC2 DMA1 ���±�־״̬
 * @input parameters: ��
 * @output parameters: ��
 * @return: BOOL - ��ǰ���±�־״̬
 * @author: ssj 2025-06-27
 ***********************************************************************************************/
BOOL Ecual_GetDma1_Adc2_UpdateFlag(void)
{
    return Dma1_Adc2_UpdateFlag;
}

/***********************************************************************************************
* @function name: Ecual_GetDma0_Adc0_UpdateFlag
* @description: ��ȡ DMA0 ADC0 ���ݸ��±�־
* @input parameters: ��
* @output parameters: ��
* @return: ��־λֵ TRUE / FALSE
* @author: ssj 2025-06-12
***********************************************************************************************/
BOOL Ecual_GetDma0_Adc0_UpdateFlag(void)
{
	return Dma0_Adc0_UpdateFlag;
}

/***********************************************************************************************
* @function name: Ecual_SetDma1_Adc1_UpdateFlag
* @description: ���� DMA1 ADC1 ���ݸ��±�־
* @input parameters: flag: TRUE �� FALSE
* @output parameters: ��
* @return: ��
* @author: ssj 2025-06-12
***********************************************************************************************/
void Ecual_SetDma1_Adc1_UpdateFlag(BOOL flag)
{
	Dma1_Adc1_UpdateFlag = flag;
}

/***********************************************************************************************
* @function name: Ecual_GetDma1_Adc1_UpdateFlag
* @description: ��ȡ DMA1 ADC1 ���ݸ��±�־
* @input parameters: ��
* @output parameters: ��
* @return: ��־λֵ TRUE / FALSE
* @author: ssj 2025-06-12
***********************************************************************************************/
BOOL Ecual_GetDma1_Adc1_UpdateFlag(void)
{
	return Dma1_Adc1_UpdateFlag;
}
/***********************************************************************************************
 * @function name:  Ecual_AreAllAdcDmaUpdated
 * @description:    �ж�3��ADC DMA���±�־�Ƿ�Ϊ1��ȫ��Ϊ1����1�����򷵻�0
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         INT8U��1��ȫ��Ϊ1��0��������һ����Ϊ1��
 * @author:         ssj 2025-07-02
 ***********************************************************************************************/
INT8U Ecual_AreAllAdcDmaUpdated(void)
{
    if((Ecual_GetDma0_Adc0_UpdateFlag() == TRUE)
    && (Ecual_GetDma1_Adc1_UpdateFlag() == TRUE)
    && (Ecual_GetDma1_Adc2_UpdateFlag() == TRUE))
    {
        return TRUE;
    }

    return FALSE;
}

/***********************************************************************************************
 * @function name:  Ecual_ClrAllAdcDmaUpdateFlag
 * @description:    ͨ�����ø��Խӿڲ��������0������DMA0/ADC0��DMA1/ADC1��DMA1/ADC2�ĸ��±�־
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-28
 ***********************************************************************************************/
void Ecual_ClrAllAdcDmaUpdateFlag(void)
{
    Ecual_SetDma0_Adc0_UpdateFlag(0);
    Ecual_SetDma1_Adc1_UpdateFlag(0);
    Ecual_SetDma1_Adc2_UpdateFlag(0);
}
/***********************************************************************************************
 * @function name:  Ecual_SetAllAdcDmaUpdateFlag
 * @description:    ͨ�����ø��Խӿڲ��������1����λDMA0/ADC0��DMA1/ADC1��DMA1/ADC2�ĸ��±�־
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-28
 ***********************************************************************************************/
void Ecual_SetAllAdcDmaUpdateFlag(void)
{
    Ecual_SetDma0_Adc0_UpdateFlag(1);
    Ecual_SetDma1_Adc1_UpdateFlag(1);
    Ecual_SetDma1_Adc2_UpdateFlag(1);
}

/***********************************************************************************************
 * @function name:  Ecual_Copy_Dma0_Adc0_DataToAllBuf
 * @description:    ʹ�� memcpy �� DMA0 ADC0 ���ݸ��Ƶ��ܻ��������������ж��е��ã�
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void Ecual_Copy_Dma0_Adc0_DataToAllBuf(void)
{
    memcpy(&Dma_Adc_AllBuf[0], &Dma0_Adc0_Buf[0], sizeof(INT32U) * D_ADC0_CONTINUOUS_CHANNEL_NUM);
}

/***********************************************************************************************
 * @function name:  Ecual_Copy_Dma1_Adc1_DataToAllBuf
 * @description:    ʹ�� memcpy �� DMA1 ADC1 ���ݸ��Ƶ��ܻ��������������ж��е��ã�
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void Ecual_Copy_Dma1_Adc1_DataToAllBuf(void)
{
    memcpy(&Dma_Adc_AllBuf[D_ADC0_CONTINUOUS_CHANNEL_NUM],
           &Dma1_Adc1_Buf[0],
           sizeof(INT32U) * D_ADC1_CONTINUOUS_CHANNEL_NUM);
}
/***********************************************************************************************
 * @function name:  Ecual_Copy_Dma1_Adc2_DataToAllBuf
 * @description:    ʹ�� memcpy �� DMA1 ADC2 ���ݸ��Ƶ��ܻ��������������ж��е��ã�
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-27
 ***********************************************************************************************/
void Ecual_Copy_Dma1_Adc2_DataToAllBuf(void)
{
    memcpy(&Dma_Adc_AllBuf[D_ADC0_CONTINUOUS_CHANNEL_NUM + D_ADC1_CONTINUOUS_CHANNEL_NUM],
           &Dma1_Adc2_Buf[0],
           sizeof(INT32U) * D_ADC2_CONTINUOUS_CHANNEL_NUM);
}

/***********************************************************************************************
 * @function name:  Ecual_ADC_Task
 * @description:    ADC �������������жϴ�����ִ�����ݰ��˺ʹ����߼���
 *                  ������ DMA ͨ�������ݸ��±�־��Ϊ TRUE ʱ��ִ�����²�����
 *                  1. ��� DMA ���ݱ�־λ��
 *                  2. �� DMA ͨ�����������ݸ��Ƶ��ܻ�������
 *                  3. ����ÿ�� ADC ͨ���Ĳ������������������ݡ�
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:         ��
 * @author:         ssj 2025-06-12
 ***********************************************************************************************/
void Ecual_ADC_Task(void)
{
	/* ���� DMA ���������ݵ�ͳһ���ܻ����� */
	Ecual_Copy_Dma1_Adc1_DataToAllBuf();
	Ecual_Copy_Dma1_Adc2_DataToAllBuf();

	/* ����ͨ����������������������߼� */
	Ecual_UpdateAdcChlSampleBuffer();
}
/***********************************************************************************************
 * @function name:  Ecual_Disable_AllAdcDma
 * @description:    ����ADC0/1/2����ӦDMAͨ������ֹFlash��д�ڼ�DMA�쳣
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void Ecual_Disable_AllAdcDma(void)
{
    DMA_Channel_Enable(DMA0_SFR, DMA_CHANNEL_5, FALSE);
    DMA_Channel_Enable(DMA1_SFR, DMA_CHANNEL_5, FALSE);
    DMA_Channel_Enable(DMA1_SFR, DMA_CHANNEL_7, FALSE);

    ADC_Cmd(ADC0_SFR, FALSE);
    ADC_Cmd(ADC1_SFR, FALSE);
    ADC_Cmd(ADC2_SFR, FALSE);
}
/***********************************************************************************************
 * @function name:  Ecual_Enable_AllAdcDma
 * @description:    ʹ��ADC0/1/2����ӦDMAͨ��������Flash������ָ�ADC-DMA��������
 * @input parameters:     ��
 * @output parameters:    ��
 * @return:               ��
 * @author:               ssj 2025-06-27
 ***********************************************************************************************/
void Ecual_Enable_AllAdcDma(void)
{
    ADC_Cmd(ADC0_SFR, TRUE);
    ADC_Cmd(ADC1_SFR, TRUE);
    ADC_Cmd(ADC2_SFR, TRUE);

    DMA_Channel_Enable(DMA0_SFR, DMA_CHANNEL_5, TRUE);
    DMA_Channel_Enable(DMA1_SFR, DMA_CHANNEL_5, TRUE);
    DMA_Channel_Enable(DMA1_SFR, DMA_CHANNEL_7, TRUE);
}

 /***********************************************************************
  * @function name: Ecual_AdcScanAll
  *
  * @description: ADɨ�裬ɨ������ͨ��
  *
  * @input parameters: void
  *
  * @output parameters: void
  *
  * @return: void
  *
  * @note: ������Ҫ������ͨ���Ƚ϶࣬��ѯռ��̫����ʱ�䣬������Ե�ʱ��ֳ�����ʱ�����ڲ���������ͨ��
  *
  * @author: Michael Xin
  *
  * @date: 2022-11-02 09:50
  ***********************************************************************/
 void Ecual_AdcScanAll(void)
 {
	Ecual_ADC_Task();
	Ecual_GetAllAdcValue();
	Ecual_SeatHeatNTCAcquire();
 }
