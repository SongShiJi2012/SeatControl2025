/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               �ļ���(Srvl_Tle9210x.c)
** Created By:              hqj
** Created date:            2023-12-14
** Version:                 V1.0
** Descriptions:            ��TLE9210x��صľ��幦��
**
**------------------------------------------------------------------------------------------------
** Modified By:				
** Modified date:			
** Version:					
** Description:				
**
**************************************************************************************************/

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "Srvl_Tle9210x.h"
#include "Drv_lpspi.h"
#include "SPI.h"
#include "ecual_ftm.h"
#include "CpuPeripheralInit.h"
#include "kflog.h"

/*************************************************************************************************
 * Static Variable declaration
 *************************************************************************************************/
/*! SPI���ͺͽ�������*/
static INT32U s_SpiTxBuff = 0;
static INT32U s_SpiRxBuff = 0;

const stTLE9210x_MotorDriveInfoType MotorDriveInfo[EN_MotorDrive_MAX] = /* TLE2910x��Դ������Ϣ */
{
	{EN_MotorDrive_0,TLE9210x_HB1,TLE9210x_HB2,TLE9210x_PWM1},
	{EN_MotorDrive_1,TLE9210x_HB3,TLE9210x_HB4,TLE9210x_PWM2},
	{EN_MotorDrive_2,TLE9210x_HB5,TLE9210x_HB6,TLE9210x_PWM3},
	{EN_MotorDrive_3,TLE9210x_HB7,TLE9210x_HB8,TLE9210x_PWM1},
};

const stTLE9210x_ChipInfoType s_SrvlTle9210xChipInfo[EN_TLE9210X_NUM_MAX] =/* Ԥ��оƬ�����Ϣ */
{
    /* оƬ���             оƬ�ͺ�             ͨ����           EN         CS       */ 
    {EN_TLE9210X_NUM_1,EN_CHIP_TLE92108,   8,  GPIOA_SFR, 5U, GPIOD_SFR,13U,FALSE},
    {EN_TLE9210X_NUM_2,EN_CHIP_TLE92104,   4,  GPIOD_SFR, 5U, GPIOA_SFR,1U, FALSE},
};

static INT8U s_SrvlTle9210xWdFlg[EN_TLE9210X_NUM_MAX] = {0};//�ڳ�ʼ�������� 

static en_TLE9210x_NumMaxType s_Tle9210X_CurrentChipNum = EN_TLE9210X_NUM_1;/* ��ǰͨѶԤ��оƬ */


/* �ر�״̬���ϼ�� */
static enTLE9210x_OffStateStepType s_SrvlTle9210x_OffStateStep[EN_TLE9210X_NUM_MAX] = {EN_OFF_STATE_STEP_NONE};
static enTLE9210x_OffStateErrType s_SrvlTle9210x_OffStateErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_OFF_STATE_ERR_NONE};
static enTLE9210x_OffStateErrType s_SrvlTle9210x_OffWaitStateErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_OFF_STATE_ERR_NONE};

/* ��λ��� */
static Srvl_TLE9210x_ResetChipType s_SrvlTle9210x_ResetChip[EN_TLE9210X_NUM_MAX];

/* �¶ȼ�� */
static enTLE9210x_TempStsType s_SrvlTle9210x_TempStsErr[EN_TLE9210X_NUM_MAX] = {EN_TLE9210X_TEMP_STS_NONE};

/* VM��� */
static enTLE9210x_VMStsType s_SrvlTle9210x_VMStsErr[EN_TLE9210X_NUM_MAX] = {EN_TLE9210X_VM_STS_NONE};

/* ����Ƿѹ��� */
static INT8U s_SrvlTle9210x_ChargePumpUnderVStsErr[EN_TLE9210X_NUM_MAX] = {FALSE};


/* ©Դ���ϼ�� */
static enTLE9210x_DrainSErrType s_SrvlTle9210x_DrainSourceErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_TLE9210X_DSOV_STS_NONE};

/* ��ȡ�����쳣-��������ʹ�� */
INT8U s_SrvlTle9210x_DataReadErr[EN_TLE9210X_NUM_MAX] = {0};

/* ��ʼ��״̬ */
static INT8U s_SrvlTle9210x_ChipInitErrSts[EN_TLE9210X_NUM_MAX] = {FALSE};
/*************************************************************************************************
 * Global Variable declaration
 *************************************************************************************************/
static void Srvl_Tle9210x_ReadStatus_GDF(void);

/*��ѯ��ȡ ״̬�Ĵ������� */
static Srvl_Tle9210x_fpDEVICE_getDeviceReg s_SrvlTle9210x_GetRegStsFunc[EN_STSREG_MAX] = {&TLE9210x_RegLayer_get_Status_GENSTAT,
                                                                                          &TLE9210x_RegLayer_get_Status_DSOV,
                                                                                          &TLE9210x_RegLayer_get_Status_HBVOUT_PWMERR,
                                                                                          &TLE9210x_RegLayer_get_Status_EFF_TDON_OFF1,
                                                                                          &TLE9210x_RegLayer_get_Status_EFF_TDON_OFF2,
                                                                                          &TLE9210x_RegLayer_get_Status_EFF_TDON_OFF3,
                                                                                          &TLE9210x_RegLayer_get_Status_TRISE_FALL3,
                                                                                          &TLE9210x_RegLayer_get_Status_TRISE_FALL1,
                                                                                          &TLE9210x_RegLayer_get_Status_TRISE_FALL2,
                                                                                          &Srvl_Tle9210x_ReadStatus_GDF,
                                                                                          /*&TLE9210x_RegLayer_get_Status_DEVID*/};

/* ����״̬��ȡ */
/* GENSTAT 0xE2*/
/* �ȹ���:TSD �Ⱦ���:TW OC2����:OC2 OC1����:OC1 VM��ѹ:VSOV VMǷѹ:VSUV ����Ƿѹ:CPUV */

/* DSOV 0xE4*/
/* ͨ��©Դ��ѹ */

/* HBVOUT_PWMERR 0xE6*/
/* PWM ͨ�����ô���:HBxPWME���޿�HBȷ��ѹ:HBxVOUT */

/* EFF_TDON_OFFx-0xE8 0xEA 0xEC*/
/* PWM ����ʱ�� */

/* TRISE_FALL 0xF2 0xEE 0xF0*/
/* PWM  �����½�����ʱ��*/

/* GDF -��ҪдA55A��1F���ܷ��� 0xF4*/
/* դ������ʱ����� */
/*��ѯ���� ״̬�Ĵ�������RAM���� */
static Srvl_Tle9210x_fpDEVICE_updateRamReg s_SrvlTle9210x_UpdataRegStsFunc[EN_STSREG_MAX] = {&TLE9210x_Update_Status_GENSTAT,
                                                                                             &TLE9210x_Update_Status_DSOV,
                                                                                             &TLE9210x_Update_Status_HBVOUT_PWMERR,
                                                                                             &TLE9210x_Update_Status_EFF_TDON_OFF1,
                                                                                             &TLE9210x_Update_Status_EFF_TDON_OFF2,
                                                                                             &TLE9210x_Update_Status_EFF_TDON_OFF3,
                                                                                             &TLE9210x_Update_Status_TRISE_FALL3,
                                                                                             &TLE9210x_Update_Status_TRISE_FALL1,
                                                                                             &TLE9210x_Update_Status_TRISE_FALL2,
                                                                                             &TLE9210x_Update_Status_GDF,
                                                                                             /*&TLE9210x_Update_Status_DEVID*/};

static Srvl_Tle9210x_fpDEVICE_GetRamReg s_SrvlTle9210x_RamRegStsFunc[EN_STSREG_MAX] = {&TLE9210x_Get_Reg_Status_GENSTAT,
                                                                                       &TLE9210x_Get_Reg_Status_DSOV,
                                                                                       &TLE9210x_Get_Reg_Status_HBVOUT_PWMERR,
                                                                                       &TLE9210x_Get_Reg_Status_EFF_TDON_OFF1,
                                                                                       &TLE9210x_Get_Reg_Status_EFF_TDON_OFF2,
                                                                                       &TLE9210x_Get_Reg_Status_EFF_TDON_OFF3,
                                                                                       &TLE9210x_Get_Reg_Status_TRISE_FALL3,
                                                                                       &TLE9210x_Get_Reg_Status_TRISE_FALL1,
                                                                                       &TLE9210x_Get_Reg_Status_TRISE_FALL2,
                                                                                       &TLE9210x_Get_Reg_Status_GDF,
                                                                                       /*&TLE9210x_Update_Status_DEVID*/};

Srvl_TLE9210x_sDEVICE_deviceDriver TLE9210x_s_deviceDriver = {FALSE,FALSE, 0u,{0, 0, 0},0u,NULL,NULL,NULL,0u};


/*************************************************************************************************
 * Functions define
 *************************************************************************************************/
typedef uint8_t (*fpDEVICE_initDeviceReg)(uint16_t initValue); 
static void Srvl_Tle9210x_SetResetChipErrCnt(en_TLE9210x_NumMaxType ChipNum);

/***********************************************************************
* @function name: Srvl_Tle9210x_SpiMasterInit
* @description: ��ʼ��
* @input parameters: void
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
void Srvl_Tle9210x_SpiMasterInit(void)
{    
    Spi_Init(SPI0_SFR);
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SpiMasterSendData
* @description: spi������
* @input parameters: DataBuff:spi�������
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
void Srvl_Tle9210x_SpiMasterSendData(INT32U DataBuff)
{
    static INT32U s_TxData[3] = {0};
    static INT32U s_RxData[3] = {0};
    INT8U Cnt = 0;
    const INT8U CntMax = 3;
	s_SpiTxBuff = DataBuff;

    s_TxData[0] = (s_SpiTxBuff >> 24) & 0xFF;
    s_TxData[1] = (s_SpiTxBuff >> 16) & 0xFF;
    s_TxData[2] = (s_SpiTxBuff >> 8) & 0xFF;
    
    PINS_DRV_WritePin(s_SrvlTle9210xChipInfo[s_Tle9210X_CurrentChipNum].Csbase,
    s_SrvlTle9210xChipInfo[s_Tle9210X_CurrentChipNum].Cspin,D_LOW);
    #if 1
    for(Cnt = 0;Cnt < CntMax;Cnt++)
    {
        LpSpiSendReadData(0,s_TxData[Cnt],&s_RxData[Cnt]);//5M 8bit 16us
    }
    #else
        LpSpiSendReadData(0,s_SpiTxBuff,s_SpiRxBuff);//5M 32bit 11us
    #endif
    PINS_DRV_WritePin(s_SrvlTle9210xChipInfo[s_Tle9210X_CurrentChipNum].Csbase,
    s_SrvlTle9210xChipInfo[s_Tle9210X_CurrentChipNum].Cspin,D_HIGH);
    
    s_SpiRxBuff = s_RxData[0] & 0xFF;
    s_SpiRxBuff <<= 8;
    s_SpiRxBuff += s_RxData[1] & 0xFF;
    s_SpiRxBuff <<= 8;
    s_SpiRxBuff += s_RxData[2] & 0xFF;
    
    TLE9210x_ServLayer_getSpiData();//�����ݷŵ���������
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SpiMasterReadData
* @description: spi��ȡ����
* @input parameters: INT32U:spiֵ
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
INT32U Srvl_Tle9210x_SpiMasterReadData(void)
{
	INT8U RxBuff = 0;
	RxBuff = s_SpiRxBuff >> 16;

    TLE9210x_SetByte0GSB(s_Tle9210X_CurrentChipNum,RxBuff);/*������״̬ */

    /* ÿ�η�������-ȷ�Ͻ��յĹ���״̬-��ֹ���ж� */
    Srvl_Tle9210x_SetResetChipErrCnt(s_Tle9210X_CurrentChipNum);
	return s_SpiRxBuff;
}

/***********************************************************************
* @function name: Srvl_Tle9210x_GetSpiRegData
* @description: spi��ȡ����
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.28
***********************************************************************/
static INT16U Srvl_Tle9210x_GetSpiRegData(void)
{
    INT16U DataBuf = 0;
    
    DataBuf = TLE9210x_s_deviceDriver.u8_SpiRx[1];
    DataBuf <<= 8;
    DataBuf += TLE9210x_s_deviceDriver.u8_SpiRx[2];
    return DataBuf;
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SetChip
* @description: ����ͨѶоƬ
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
static INT8U Srvl_Tle9210x_SetChip(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    s_Tle9210X_CurrentChipNum = Num;
    TLE9210_SetRamCopyNum(Num);
    return TRUE;
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SetChipEn
* @description: ����ͨѶоƬEN����
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
static void Srvl_Tle9210x_SetChipEn(en_TLE9210x_NumMaxType Num,INT8U EnSts)
{
    /* ����Χ */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return;
    }
    
    if(EnSts > TRUE)
    {
        EnSts = TRUE;
    }
    
    PINS_DRV_WritePin(s_SrvlTle9210xChipInfo[Num].Enbase,s_SrvlTle9210xChipInfo[Num].Enpin,EnSts);
}

/***********************************************************************
* @function name: Srvl_9210x_SetResetChipErrCnt
* @description: ���ù��ϸ�λ����
* @input parameters: en_TLE9210x_NumMaxType
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.28
***********************************************************************/
static void Srvl_Tle9210x_SetResetChipErrCnt(en_TLE9210x_NumMaxType ChipNum)
{
    if(TLE9210x_GetByte0GSB_FS(ChipNum) == TRUE)
    {
        s_SrvlTle9210x_ResetChip[ChipNum].FsErrCheckCnt += 1;
    }
    else
    {
        s_SrvlTle9210x_ResetChip[ChipNum].FsErrCheckCnt = 0;
    }
    if(TLE9210x_GetByte0GSB_NPOR(ChipNum) == FALSE)
    {
        s_SrvlTle9210x_ResetChip[ChipNum].NporErrCheckCnt += 1;
    }
    else
    {
        s_SrvlTle9210x_ResetChip[ChipNum].NporErrCheckCnt = 0;
    }
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SendSetReg
* @description: ���ƼĴ�����������
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
static void Srvl_Tle9210x_SendSetReg(void)
{
    if(TLE9210x_s_deviceDriver.fp_setReg != NULL)
    {
        TLE9210x_s_deviceDriver.fp_setReg(TLE9210x_s_deviceDriver.u16_setBitValue);
        TLE9210x_s_deviceDriver.fp_setReg = NULL;
    }
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SendGetReg
* @description: ״̬�Ĵ�����������
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
static void Srvl_Tle9210x_SendGetReg(void)
{
    if(TLE9210x_s_deviceDriver.fp_getReg != NULL)
    {
        TLE9210x_s_deviceDriver.fp_getReg();
        TLE9210x_s_deviceDriver.fp_getReg = NULL;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_WriteDEVID
 * @description: ������ʼĴ�������
 * @input parameters: en_TLE9210x_NumMaxType INT8U
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_WriteDEVID(void)
{
    const INT16U WriteReadSeg = 0xA55A; /* ���ʼĴ���1A 1C 1D 1E ��Ҫ����DEVIDд��0xA55A */

    TLE9210x_RegLayer_set_Status_DEVID(WriteReadSeg);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_ReadStatus_GDF
 * @description: ��ȡ״̬�Ĵ��� GDF
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.23
 ***********************************************************************/
static void Srvl_Tle9210x_ReadStatus_GDF(void)
{
    Srvl_Tle9210x_WriteDEVID();//д�˼Ĵ��� �ᱨSPIE ������������-�ǹ���
    TLE9210x_RegLayer_get_Status_GDF();
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_WriteControl_DRV_LPWR_EN
 * @description: ���� DRV_LPWR_EN�Ĵ���
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.23
 ***********************************************************************/
static void Srvl_Tle9210x_WriteControl_DRV_LPWR_EN(INT16U RegData)
{
    Srvl_Tle9210x_WriteDEVID();
    TLE9210x_RegLayer_set_Control_DRV_LPWR_EN(RegData);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_PwmInit
 * @description: ��ʼ��
 * @input parameters: en_TLE9210x_NumMaxType 
 * @output parameters: void
 * @return: INT8U
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_PwmInit(en_TLE9210x_NumMaxType Num)
{
    /* ����Χ */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return ;
    }

    if(s_SrvlTle9210xChipInfo[Num].PwmSet == FALSE)
    {
        return;
    }

    Srvl_Tle9210x_PwmSet(Num,TLE9210x_PWM1,TRUE,TLE9210x_HB2);
    Srvl_Tle9210x_PwmSet(Num,TLE9210x_PWM2,TRUE,TLE9210x_HB4);
    if(s_SrvlTle9210xChipInfo[Num].ChxMax == 8)
    {
        Srvl_Tle9210x_PwmSet(Num,TLE9210x_PWM3,TRUE,TLE9210x_HB8);
        Srvl_Tle9210x_PwmSet(Num,TLE9210x_PWM4,TRUE,TLE9210x_HB6);
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_Init
 * @description: ��ʼ��-���򿪿��Ź����������ϵ�� ��ʧ��
 * @input parameters: en_TLE9210x_NumMaxType 
 * @output parameters: void
 * @return: INT8U
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static INT8U Srvl_Tle9210x_StaticInit(en_TLE9210x_NumMaxType Num)
{
    fpDEVICE_initDeviceReg fp_initRegTemp;
    INT8U u8_initRegisterCounter;
    INT8U u8_initRegisterNum;
    INT16U u16_initRegValueTemp;
    INT8U VdsEnum = 2;

    /*2M spi ��ʼ����оƬ�Ĵ���ʹ��ʱ�� 1.2ms */
     fpDEVICE_initDeviceReg fp_initRegAll[] = {&TLE9210x_FuncLayer_set_Control_GENCTRL1,
                                               &TLE9210x_FuncLayer_set_Control_GENCTRL2,
                                               &TLE9210x_FuncLayer_set_Control_VDS2,                      //8ͨ�� ���� 
                                               &TLE9210x_FuncLayer_set_Control_VDS1,
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK1,                  /* ����������� �հ�ʱ���趨 */
                                               &TLE9210x_FuncLayer_set_Control_HBMODE,                     /* ͨ������ */

                                               /*REG_BANK=0�������� */
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT,              /* active mos ʱ���趨 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT,  /* pwm ����������� */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT,              /* active pwm������ */
                                               &TLE9210x_FuncLayer_set_Control_ST_ICHG,                   /* ��̬��ŵ�ͨ�����������*/
                                               &TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT,             /* pwm �ŵ���� */

                                               /*REG_BANK=1��������-ÿ������GENCTRL1����Ҫ��ת WDTRIG */
                                               &TLE9210x_FuncLayer_set_Control_GENCTRL1,
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW,               /* FreeWheeling mos ʱ���趨 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW,   /* pwm ����������� */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW,               /* freewheeling pwm��ŵ����*/
                                               &TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT,            /* pwmԤ�ŵ���� */
                                               &TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT,             /* pwmԤ����� */

                                               &TLE9210x_FuncLayer_set_Control_PWMSET,                    /* PWM ����*/
                                               &TLE9210x_FuncLayer_set_Control_TPRECHG,                   /* Ԥ���ʱ���趨 */
                                               &TLE9210x_FuncLayer_set_Control_HBIDIAG,                   /* �������ʱ����� */
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF1,                 /* pwm on off ��ʱʱ�� */
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF2,
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF3};
     INT16U u16_initRegValueAll[EN_TLE9210X_NUM_MAX][23] = {
                                             /*Ԥ����1-7808 */
                                             {D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT,
                                              D_SRVL_TLE9210x_1_C_GENCTRL2_INIT,
                                              D_SRVL_TLE9210x_1_C_VDS2_INIT,                    
                                              D_SRVL_TLE9210x_1_C_VDS1_INIT,                    
                                              D_SRVL_TLE9210x_1_C_CCP_BLK1_INIT,                
                                              D_SRVL_TLE9210x_1_C_HBMODE_INIT,
                                              /*REG_BANK=0*/
                                              D_SRVL_TLE9210x_1_C_CCP_BLK2_ACT_INIT,            
                                              D_SRVL_TLE9210x_1_C_PWM_ICHGMAX_CCP_BLK3_ACT_INIT,
                                              D_SRVL_TLE9210x_1_C_PWM_ICHG_ACT_INIT,            
                                              D_SRVL_TLE9210x_1_C_ST_ICHG_INIT,                 
                                              D_SRVL_TLE9210x_1_C_PWM_IDCHG_ACT_INIT,           
                                              /*REG_BANK=1*/
                                              D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT,
                                              D_SRVL_TLE9210x_1_C_CCP_BLK2_FW_INIT,             
                                              D_SRVL_TLE9210x_1_C_PWM_ICHGMAX_CCP_BLK3_FW_INIT, 
                                              D_SRVL_TLE9210x_1_C_PWM_ICHG_FW_INIT,             
                                              D_SRVL_TLE9210x_1_C_PWM_PDCHG_INIT_INIT,          
                                              D_SRVL_TLE9210x_1_C_PWM_PCHG_INIT_INIT,           
                                              
                                              D_SRVL_TLE9210x_1_C_PWMSET_INIT,                 
                                              D_SRVL_TLE9210x_1_C_TPRECHG_INIT,                 
                                              D_SRVL_TLE9210x_1_C_HBIDIAG_INIT,                 
                                              D_SRVL_TLE9210x_1_C_PWM_TDON_OFF1_INIT,           
                                              D_SRVL_TLE9210x_1_C_PWM_TDON_OFF2_INIT,           
                                              D_SRVL_TLE9210x_1_C_PWM_TDON_OFF3_INIT},
                                              /*Ԥ����2-7804*/
                                              { D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT,
                                                D_SRVL_TLE9210x_1_C_GENCTRL2_INIT,
                                                D_SRVL_TLE9210x_2_C_VDS2_INIT,
                                                D_SRVL_TLE9210x_2_C_VDS1_INIT,
                                                D_SRVL_TLE9210x_2_C_CCP_BLK1_INIT,
                                                D_SRVL_TLE9210x_1_C_HBMODE_INIT,
                                                /*REG_BANK=0*/
                                                D_SRVL_TLE9210x_2_C_CCP_BLK2_ACT_INIT,            
                                                D_SRVL_TLE9210x_2_C_PWM_ICHGMAX_CCP_BLK3_ACT_INIT,
                                                D_SRVL_TLE9210x_2_C_PWM_ICHG_ACT_INIT,            
                                                D_SRVL_TLE9210x_2_C_ST_ICHG_INIT,                 
                                                D_SRVL_TLE9210x_2_C_PWM_IDCHG_ACT_INIT,           
                                                /*REG_BANK=1*/
                                                D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT,
                                                D_SRVL_TLE9210x_2_C_CCP_BLK2_FW_INIT,             
                                                D_SRVL_TLE9210x_2_C_PWM_ICHGMAX_CCP_BLK3_FW_INIT, 
                                                D_SRVL_TLE9210x_2_C_PWM_ICHG_FW_INIT,             
                                                D_SRVL_TLE9210x_2_C_PWM_PDCHG_INIT_INIT,          
                                                D_SRVL_TLE9210x_2_C_PWM_PCHG_INIT_INIT,           
                                                
                                                D_SRVL_TLE9210x_2_C_PWMSET_INIT,                 
                                                D_SRVL_TLE9210x_2_C_TPRECHG_INIT,                 
                                                D_SRVL_TLE9210x_2_C_HBIDIAG_INIT,                 
                                                D_SRVL_TLE9210x_2_C_PWM_TDON_OFF1_INIT,           
                                                D_SRVL_TLE9210x_2_C_PWM_TDON_OFF2_INIT,           
                                                D_SRVL_TLE9210x_2_C_PWM_TDON_OFF3_INIT}};
                                             
    /* ����Χ */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return EN_TLE9210X_INIT_CHIP;
    }
    
    Srvl_Tle9210x_SetChip(Num);//����оƬ-�Ĵ����洢RAM
    //��ʼ��GENCTRL1-��ת���Ź�(����GENCTRL1 ���跴תWDTRIG)
    (void)TLE9210x_RegLayer_set_Control_GENCTRL1(u16_initRegValueAll[Num][0]); /* polyspace MISRA2012:8.7 [Justified: Low] "Given due architecture" */

    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL1;}//SPI�쳣
    /* Disable/Enable watchdog depending on parameter */
    if (s_SrvlTle9210xWdFlg[Num] == FALSE) 
    {
        //����UNLOCK �ȴ�ʧ�ܿ��Ź�
        TLE9210x_RegLayer_set_Control_GENCTRL1((u16_initRegValueAll[Num][0] | TLE9210x_Control_GENCTRL1_UNLOCK_Mask) 
        & ~TLE9210x_Control_GENCTRL1_WDTRIG_Mask);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_WD1;}//SPI�쳣
        //��ʼ��GENCTRL2-ʧ�ܿ��Ź�
        TLE9210x_RegLayer_set_Control_GENCTRL2(u16_initRegValueAll[Num][1] | TLE9210x_Control_GENCTRL2_WDDIS_Mask);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL2;}//SPI�쳣
        TLE9210x_RegLayer_set_Control_GENCTRL1(u16_initRegValueAll[Num][0]);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_WD2;}//SPI�쳣
    }
    else
    {
        TLE9210x_RegLayer_set_Control_GENCTRL2(u16_initRegValueAll[Num][1]);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL2;}//SPI�쳣
    }
    
    /* ��ʼ�����ƼĴ��� */
    u8_initRegisterNum = (INT8U)((sizeof(u16_initRegValueAll)/sizeof(u16_initRegValueAll[0][0]))/EN_TLE9210X_NUM_MAX);
    VdsEnum = (s_SrvlTle9210xChipInfo[Num].ChxMax == 4)?(2):(3);//4ͨ���Ĳ���Ҫ����VDS2
    for(u8_initRegisterCounter = VdsEnum; u8_initRegisterCounter < u8_initRegisterNum; u8_initRegisterCounter++)
    {
        fp_initRegTemp = fp_initRegAll[u8_initRegisterCounter];
        u16_initRegValueTemp = u16_initRegValueAll[Num][u8_initRegisterCounter];
        fp_initRegTemp(u16_initRegValueTemp);
        Srvl_Tle9210x_SendSetReg();
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_REG;}//SPI�쳣
    }
    /* ��ʼ�������һ�� GENSTAT�Ĵ��� ��ʹNPOR��1 */
    TLE9210x_RegLayer_set_Status_GENSTAT(0);
    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_CLE;}//SPI�쳣

    /* ��ʼ�� PWM���� */
    Srvl_Tle9210x_PwmInit(Num);
    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_PWM;}//SPI�쳣

    return EN_TLE9210X_INIT_NONE;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_Init
 * @description: ��ʼ��-���򿪿��Ź����������ϵ�� ��ʧ��
 * @input parameters: Num:оƬ�� 
 * @output parameters: void
 * @return: INT8U
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
void Srvl_Tle9210x_Init(en_TLE9210x_NumMaxType Num)
{
    INT8U RetryInitCnt = 0;
    const INT8U RetryInitMax = 4;
    INT8U InitResult = TRUE;
    INT32U AppFlashStartAddr = CPU_GetFlashStartAddr();

    /* ����Χ */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return;
    }
    
    if(AppFlashStartAddr == 0)
    {
        s_SrvlTle9210xWdFlg[Num] = FALSE; //������ʼ��ַΪ0 ������ʧ�ܿ��Ź�
    }
    else
    {
        s_SrvlTle9210xWdFlg[Num] = TRUE; //ʹ�ܿ��Ź�-���Դ�ϵ�ʱ�ḴλԤ��
    }
    //kf_printf("Num:%d,FA: 0x%08X ",Num, AppFlashStartAddr);
    //kf_printf("Wd: %d\r\n",s_SrvlTle9210xWdFlg[Num]);

    s_SrvlTle9210x_ChipInitErrSts[Num] = EN_TLE9210X_INIT_NONE;
    do{
        InitResult = Srvl_Tle9210x_StaticInit(Num);
        if(InitResult == EN_TLE9210X_INIT_NONE){break;}
        RetryInitCnt += 1;
       }while(RetryInitCnt < RetryInitMax);

    if(RetryInitCnt >= RetryInitMax && InitResult != EN_TLE9210X_INIT_NONE)
    {
        /* ��ʼ��ʧ�� */
        s_SrvlTle9210x_ChipInitErrSts[Num] = InitResult;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_FeedWdg
 * @description: ι��
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_FeedWdg(void)
{
    static en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_MAX;

    /* ��ѯι�� */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
    /* ��ι����ִ�� */
    if(s_SrvlTle9210xWdFlg[ChipNum] == FALSE)
    {
        return;
    }

    Srvl_Tle9210x_SetChip(ChipNum);
    TLE9210x_FuncLayer_Trigger_Watchdog();
    Srvl_Tle9210x_SendSetReg();    
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetDiagStatusRamRegData
 * @description: ��Ͽ��ƻ�ȡоƬRAM�мĴ���ֵ
 * @input parameters: ChipCnt:оƬ��  Reg�Ĵ�����
 * @output parameters: INT16U
 * @return: INT16U
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
 INT16U Srvl_Tle9210x_GetDiagStatusRamRegData(en_TLE9210x_NumMaxType ChipCnt,INT8U Reg)
{
    INT16U TempRegData = 0;
    
    if(ChipCnt >= EN_TLE9210X_NUM_MAX || Reg >= EN_STSREG_MAX)
    {
        return FALSE;
    }
    if(s_SrvlTle9210x_RamRegStsFunc[Reg] != NULL)
    {
       TempRegData = s_SrvlTle9210x_RamRegStsFunc[Reg](ChipCnt);
       return TempRegData;
    }
    return FALSE;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetDiagStatusChipRegData
 * @description: ��Ͽ��ƻ�ȡʵ��оƬ��ǰ�Ĵ���ֵ
 * @input parameters: ChipCnt:оƬ��  Reg�Ĵ�����
 * @output parameters: INT16U
 * @return: INT16U
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
INT16U Srvl_Tle9210x_GetDiagStatusChipRegData(en_TLE9210x_NumMaxType ChipCnt,INT8U Reg)
{
    INT16U TempRegData = 0;
    INT8U Result = FALSE;
    if(ChipCnt >= EN_TLE9210X_NUM_MAX || Reg >= EN_STSREG_MAX)
    {
        return FALSE;
    }
    Result = Srvl_Tle9210x_SetChip(ChipCnt);
    if(s_SrvlTle9210x_GetRegStsFunc[Reg] != NULL && s_SrvlTle9210x_UpdataRegStsFunc[Reg] != NULL && Result == TRUE)
    {
        /* spi��ȡ�Ĵ�����Ϣ */
        s_SrvlTle9210x_GetRegStsFunc[Reg](); 
        /* ����ȡ���ݴ洢������RAM�� */
        TempRegData = Srvl_Tle9210x_GetSpiRegData();
        s_SrvlTle9210x_UpdataRegStsFunc[Reg](s_Tle9210X_CurrentChipNum,TempRegData);
        return TempRegData;
    }
    return FALSE;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_StatusReg_UpdateCycle
 * @description: ��ȡ״̬�Ĵ���
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_StatusReg_UpdateCycle(void)
{
    static en_TLE9210x_NumMaxType ChipCnt = EN_TLE9210X_NUM_1;
    static INT16U UpdateCnt = 0;
    const INT16U UpdateCntMax = EN_STSREG_MAX-1;
    INT16U TempRegData = 0;
    INT8U Result = FALSE;

    for(ChipCnt = 0;ChipCnt < 1;ChipCnt++)//��ѯ���оƬ״̬�Ĵ���
    {
        //����оƬ-�Ĵ����洢RAM
        Result = Srvl_Tle9210x_SetChip(ChipCnt);
        
        if(s_SrvlTle9210x_GetRegStsFunc[UpdateCnt] != NULL 
        && s_SrvlTle9210x_UpdataRegStsFunc[UpdateCnt] != NULL
        && Result == TRUE)
        {
            /* spi��ȡ�Ĵ�����Ϣ */
            s_SrvlTle9210x_GetRegStsFunc[UpdateCnt](); 
            /* ����ȡ���ݴ洢������RAM�� */
            TempRegData = Srvl_Tle9210x_GetSpiRegData();
            s_SrvlTle9210x_UpdataRegStsFunc[UpdateCnt](s_Tle9210X_CurrentChipNum,TempRegData);
        }
    }
    if(UpdateCnt < UpdateCntMax)/* ������ѯ��״̬�Ĵ��� */
    {
        UpdateCnt = UpdateCnt + 1;
    }
    else
    {
        UpdateCnt = 0;
        //ChipCnt = (ChipCnt < (EN_TLE9210X_NUM_MAX - 1))?(ChipCnt + 1):(EN_TLE9210X_NUM_1);/* ��ѯ��оƬ */
    }
}
/***********************************************************************
 * @function name: Srvl_Tle9210x_TempVoltageErrStsFunc
 * @description: �¶�-��ѹ��������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
static void Srvl_Tle9210x_TempVoltageErrStsFunc(void)
{
    static en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_MAX;
    INT8U TempErrSts = FALSE;
    INT8U SupplyErrSts = FALSE;
    INT8U SupplyOcErrSts = FALSE;
    INT16U GENSTATRegValue = 0;
    INT8U VMSts = 0;
    /* ��ѯ��� */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);

    TempErrSts = TLE9210x_GetByte0GSB_TE(ChipNum);
    SupplyErrSts = TLE9210x_GetByte0GSB_SUPE(ChipNum);
    SupplyOcErrSts = TLE9210x_GetByte0GSB_OC(ChipNum);
        
    if(TempErrSts == FALSE && SupplyErrSts == FALSE && SupplyOcErrSts == FALSE)
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_NONE;
        s_SrvlTle9210x_VMStsErr[ChipNum] = EN_TLE9210X_VM_STS_NONE;
        s_SrvlTle9210x_ChargePumpUnderVStsErr[ChipNum] = FALSE;
        return;
    }

    /* ���GENSTAT����ȡ״̬ */
    Srvl_Tle9210x_SetChip(ChipNum);
    TLE9210x_RegLayer_set_Status_GENSTAT(0);
    TLE9210x_Update_Status_GENSTAT(ChipNum,Srvl_Tle9210x_GetSpiRegData());

    GENSTATRegValue = TLE9210x_Get_Reg_Status_GENSTAT(ChipNum);
    VMSts = (GENSTATRegValue >> 1) & 0X03;

    //VM ״̬
    if(SupplyErrSts == FALSE)
    {
        s_SrvlTle9210x_VMStsErr[ChipNum] = EN_TLE9210X_VM_STS_NONE;
    }
    else if(VMSts != 0)
    {
        s_SrvlTle9210x_VMStsErr[ChipNum] = VMSts;
    }
    else
    {}
    //����״̬
    if(SupplyErrSts == FALSE)
    {
        s_SrvlTle9210x_ChargePumpUnderVStsErr[ChipNum] = FALSE;
    }
    else if(TLE9210x_FuncLayer_get_Status_GENSTAT_CPUV() != 0)
    {
        s_SrvlTle9210x_ChargePumpUnderVStsErr[ChipNum] = TRUE;
    }
    else
    {}

    //�¶�״̬
    if(TempErrSts == FALSE)
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_NONE;
    }
    else if(TLE9210x_FuncLayer_get_Status_GENSTAT_TSD() != FALSE) /* ���¹ض� */
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_ERR;
    }
    else if(TLE9210x_FuncLayer_get_Status_GENSTAT_TW() != FALSE) /* ���¾��� */
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_WARRING;
    }
    else
    {   /* ������ʧ - ʹ��TempErrSts��� */
        //s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_NONE;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_PWM4EnCheckReset
 * @description: ����PWM4֮�����Ƿ񷴸���λ-�����ڼ��spiͨѶ���
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.05.22
 ***********************************************************************/
static void Srvl_Tle9210x_PWM4EnCheckReset(void)
{
    static en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_MAX;
    static INT8U ErrCnt[EN_TLE9210X_NUM_MAX] = {0};
    INT16U DevidRegValue = 0;
    const INT16U DevidRegValueInit = 0x0001; //DR7808 7804 �ĵ������ݾ�Ϊ��
    const INT8U ErrCntMax = 5;

    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
    
    Srvl_Tle9210x_SetChip(ChipNum);
    if(TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN() == FALSE) /* û�п���PWM4 */
    {
        ErrCnt[ChipNum] = 0;
        return;
    }
    TLE9210x_RegLayer_get_Status_DEVID();
    TLE9210x_Update_Status_DEVID(ChipNum,Srvl_Tle9210x_GetSpiRegData());
    DevidRegValue = TLE9210x_Get_Reg_Status_DEVID(ChipNum);
    
    if(DevidRegValue != DevidRegValueInit) //���ݲ���ͬ
    {
        ErrCnt[ChipNum] += 1;
        s_SrvlTle9210x_DataReadErr[ChipNum] = TRUE;
    }
    else
    {
        ErrCnt[ChipNum] = 0;
        s_SrvlTle9210x_DataReadErr[ChipNum] = FALSE;
    }
    //������ ʹ��EN �ȴ����NPOR������Srvl_Tle9210x_ResetChipControlFunc��ʼ��оƬ
    if(ErrCnt[ChipNum] > (ErrCntMax + 1))
    {
        ErrCnt[ChipNum] = 0;
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,100);
        return;
    }
    if(ErrCnt[ChipNum] > ErrCntMax) 
    {
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,0);
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_DrainSourceVolErrStsFunc
 * @description: ©Դ��ѹ��������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
static void Srvl_Tle9210x_DrainSourceVolErrStsFunc(void)
{
    static en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_MAX;
    INT8U DSErrSts = FALSE;
    INT8U HbCnt = 0;
    INT16U DsovRegValue = 0;
    /* ��ѯ��� */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);

    DSErrSts = TLE9210x_GetByte0GSB_VDSE(ChipNum);
    
    if(DSErrSts == FALSE)
    {
        memset(&s_SrvlTle9210x_DrainSourceErr[ChipNum][0],EN_TLE9210X_DSOV_STS_NONE,TLE9210x_HBChMAX);
        return;
    }
    /* ���DSOV����ȡ״̬ */
    Srvl_Tle9210x_SetChip(ChipNum);
    TLE9210x_RegLayer_set_Status_DSOV(0);
    TLE9210x_Update_Status_DSOV(ChipNum,Srvl_Tle9210x_GetSpiRegData());

    DsovRegValue = TLE9210x_Get_Reg_Status_DSOV(ChipNum);
    
    for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax*2; HbCnt+=2) /* ��ȡ����״̬ -�����ԣ�mos��·�������쳣 ��ֵ��ƥ�� */
    {
       s_SrvlTle9210x_DrainSourceErr[ChipNum][HbCnt] = (DsovRegValue >> HbCnt) & 0x03;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_ResetChipControlFunc
 * @description: ���ϸ�λоƬ����
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
static void Srvl_Tle9210x_ResetChipControlFunc(void)
{
    Srvl_TLE9210x_ResetChipType *ResetChip = NULL;
    static en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_MAX;
    const INT8U ResetCntMax = 10; /* ��λоƬ���Դ��� */
    const INT8U ErrCntMax = 2;    /* ����ȷ�ϴ��� */
    INT8U FallStateErr = FALSE;   /* FS ����״̬ */
    INT8U PowerOnReset = FALSE;   /* NPNOR ����״̬ */

    /* ��ѯ����������³�ʼ��״̬ */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
   // ChipNum = 0;

    ResetChip = &s_SrvlTle9210x_ResetChip[ChipNum];
    
    FallStateErr = (ResetChip->FsErrCheckCnt >= ErrCntMax)?(TRUE):(FALSE);   /* FS ����״̬ */
    PowerOnReset = (ResetChip->NporErrCheckCnt >= ErrCntMax)?(TRUE):(FALSE); /* NPOR ����״̬ */
    
    if(ResetChip->ResetChipCnt > ResetCntMax) /* ��ʼ�������� */
    {
        ResetChip->ErrSts = TRUE;
        return;
    }
    
    ResetChip->ErrSts = FALSE;
    if(FallStateErr == FALSE && PowerOnReset == FALSE) /* ��FS���� �� �ϵ縴λ */
    {
        ResetChip->ResetChipCnt = 0;
        return;
    }

    ResetChip->ResetChipCnt += 1; //���жϴ��ڹ��ϴ�����ԭ���ڶ�����Ч��-���迪����Ҫ���´򿪡�
    
    Srvl_Tle9210x_SetChip(ChipNum);
    
    if(TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN() == TRUE)//�п�PWM4�Ĺ���-Ҫ������EN
    {
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,0);
        TLE9210x_WaitFor_us_HAL(150);
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,100);
    }
    
    if(FallStateErr == TRUE)    /* ���ϱ���ģʽ ���˻�����ģʽ */
    {
        TLE9210x_RegLayer_set_Status_GENSTAT(0);
        TLE9210x_Update_Status_GENSTAT(ChipNum,Srvl_Tle9210x_GetSpiRegData());
        /* дWDTRIG_GENCTRL1 Ϊ1 */
        TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(TRUE);
        Srvl_Tle9210x_SendSetReg();
        /* дWDTRIG_GENCTRL1 Ϊ0 */
        TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(FALSE);
        Srvl_Tle9210x_SendSetReg();
    }
    
    /* ��ʼ�����ƼĴ��� */
    Srvl_Tle9210x_Init(ChipNum);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_OffStateDiagnostic
 * @description: ��״̬���
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note: 10ms���� WaitTimeCntMax400ms �ȴ�4s
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
static void Srvl_Tle9210x_OffStateDiagnostic(void)
{
    /*1.��Դ©����ѹ���õ�2V 
      2.��⸺�ضϿ�����- HBxIDIAG = 0 && HByIDIAG = 0 -> HBxVOUT = 1  HByVOUT = 0 
      3.���̵�Դ���� - HBIDIAG = 0 -> HBxVOUT = 1
      4.���̵ع��� - HBIDIAG = 0 -> HBxVOUT = 0
      5.��©Դ����ѹ���õ�mV 
      Ŀǰ��Ҫ4��������ɼ�� - ��������Ҫ ���� HBxMODE */
                                                        /*ȫ��������Hbx����Hby���� ȫ�������� */
    const INT16U RegHbidiagValue[EN_OFF_STATE_STEP_MAX] = {0x0000,0x00AA,0x00FF,0x0000,0x0000};
    const INT16U RegVds1Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS1_INIT,D_SRVL_TLE9210x_2_C_VDS1_INIT};
    const INT16U RegVds2Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS2_INIT,D_SRVL_TLE9210x_2_C_VDS2_INIT};
    const INT16U WaitTimeCntMax = 400;/* ����10ms ���� */
    static INT16U s_WaitTimeCnt[EN_TLE9210X_NUM_MAX] = {0};
    INT16U RegContHBMODE = 0;
    INT16U TempRegData = 0;
    INT8U HbCnt = 0;
    INT8U HbxyValue = 0;
    en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_1;
    
    for(ChipNum = EN_TLE9210X_NUM_1;ChipNum < EN_TLE9210X_NUM_MAX;ChipNum++)
    {
        /* ��Ҫ������оƬ �ٿ������ */
        Srvl_Tle9210x_SetChip(ChipNum);
        RegContHBMODE = TLE9210x_Get_Reg_Control_HBMODE(ChipNum);

        if((RegContHBMODE != 0 && RegContHBMODE != 0xFFFF) || s_SrvlTle9210x_OffStateStep[ChipNum] >= EN_OFF_STATE_STEP_MAX)
        {
            /* ���ڵ�����в���� */
            s_WaitTimeCnt[ChipNum] = 0;
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_WAIT;/* ���н���֮���ʱ���ټ�� */
            continue;
        }

        /* �ȴ����� - ���һ�� */
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_WAIT)
        {   
            s_WaitTimeCnt[ChipNum] += 1;
            if(s_WaitTimeCnt[ChipNum] > WaitTimeCntMax)
            {
                s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_NONE;
            }
            else
            {
                /*�������� ��ֵ������-����������ж�ȡ״̬ ���� */
                memcpy(&s_SrvlTle9210x_OffWaitStateErr[ChipNum],&s_SrvlTle9210x_OffStateErr[ChipNum],
                    sizeof(s_SrvlTle9210x_OffWaitStateErr)/EN_TLE9210X_NUM_MAX);
                continue;
            }
        }
        
        s_WaitTimeCnt[ChipNum] = 0;
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_NONE)
        {
            TLE9210x_FuncLayer_set_Control_GENCTRL2_BD_PASS(0u);
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS1(0x0FFF); /* ����2V */
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS2(0x0FFF); /* ����2V */
            Srvl_Tle9210x_SendSetReg();
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_OPEN_LOAD;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_OPEN_LOAD]);
            Srvl_Tle9210x_SendSetReg();
            continue;
        }

        /* ����HBVOUT_PWMERR״̬ */
        TLE9210x_RegLayer_get_Status_HBVOUT_PWMERR();
        TempRegData = Srvl_Tle9210x_GetSpiRegData();
        TLE9210x_Update_Status_HBVOUT_PWMERR(ChipNum,TempRegData);
        TempRegData = TempRegData & 0x00FF;/* ��ȡ HBxVOUT״̬ */
        
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_OPEN_LOAD)
        {
            /*��HBxVOUT= 0 HByVOUT= 0������ */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt+=2)
            {
                HbxyValue = (TempRegData >> HbCnt) & 0x03;
               if(HbxyValue == 0x00) // 10 �����ͨ ��ѹ�ӽ�0 -���������Ϊ 00
               {
                    /* ���� */
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_NONE;
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt+1] = EN_OFF_STATE_ERR_NONE;
               }
               else
               {
                    /* �쳣 */
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_OPEN_LOAD;
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt+1] = EN_OFF_STATE_ERR_OPEN_LOAD;
               }
            }
            
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_TO_BATTERY;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_TO_BATTERY]);
            Srvl_Tle9210x_SendSetReg();
            continue;
        }

        
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_TO_BATTERY)
        {
            /*��HBxVOUT= 0 ������ */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt++)
            {
               if(TempRegData & (1 << HbCnt)) // Ϊ1 
               {
                    /* �Ե�Դ��· */
                    s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_TO_BATTERY;
               }
               else
               {
                    /* ���� */
               }
            }
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_TO_GROUND;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_TO_GROUND]);
            Srvl_Tle9210x_SendSetReg();
            continue;
        }

        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_TO_GROUND)
        {
            /*��HBxVOUT= 1 ������ */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt++)
            {
               if(TempRegData & (1 << HbCnt)) // Ϊ1 
               {
                    /* ���� */
               }
               else
               {
                  /* �Եض�· */
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_TO_GROUND;
               }
            }
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_WAIT;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_WAIT]);
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS1(RegVds1Init[ChipNum]); /* ���ó�ʼ�� */
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS2(RegVds2Init[ChipNum]); /* ���ó�ʼ�� */
            Srvl_Tle9210x_SendSetReg();
        }
    }
}
 
/***********************************************************************
 * @function name: Srvl_Tle9210x_Driver
 * @description: ��������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_IoSet(en_TLE9210x_NumMaxType Num,enTLE9210x_MotorDriveIndex Drv,enTLE9210x_ControlMode Cont)
{
    INT16U HbModeRegBuf = 0;
    const INT16U HbModeMask[EN_MotorDrive_MAX] = {0xFFF0,0xFF0F,0xF0FF,0x0FFF};
    const INT8U DrvMask[TLE9210x_ModeMAX] = {0x00,0x06,0x09,0x05};

    const INT16U RegVds1Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS1_INIT,D_SRVL_TLE9210x_2_C_VDS1_INIT};
    const INT16U RegVds2Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS2_INIT,D_SRVL_TLE9210x_2_C_VDS2_INIT};
    /* ����Χ */
    if(Drv >= EN_MotorDrive_MAX || Num >= EN_TLE9210X_NUM_MAX || Cont >= TLE9210x_ModeMAX)
    {
        return;
    }
    
    /* ��Ҫ������оƬ�� �ٿ������ */
    Srvl_Tle9210x_SetChip(Num);

    if(Cont != TLE9210x_OFF)
    {
        /* �ж�VDS1 2 ������̬����޸Ĺ�������Ҫ��������©Դ��ֵ */
        if(TLE9210x_FuncLayer_get_Control_VDS1() != RegVds1Init[Num])
        {
            TLE9210x_FuncLayer_set_Control_VDS1(RegVds1Init[Num]); /* ���ó�ʼ�� */
            Srvl_Tle9210x_SendSetReg();
        }
        
        if(TLE9210x_FuncLayer_get_Control_VDS2() != RegVds2Init[Num]
        && s_SrvlTle9210xChipInfo[Num].ChipNO == EN_CHIP_TLE92108)
        {
            TLE9210x_FuncLayer_set_Control_VDS2(RegVds2Init[Num]); /* ���ó�ʼ�� */
            Srvl_Tle9210x_SendSetReg();
        }
    }
//    TLE9210x_FuncLayer_set_Control_GENCTRL2_BD_PASS(0u);/* �ϵ�Ĭ������0 �˴��ɲ����� */
//    Srvl_Tle9210x_SendSetReg();
    
    /* ��ȡʵ��״ֵ̬*/
    HbModeRegBuf = TLE9210x_Get_Reg_Control_HBMODE(Num);

    /* ���ƶ�ӦHbx-y ����*/
    HbModeRegBuf = (HbModeRegBuf & HbModeMask[Drv]) | (DrvMask[Cont] << (Drv * EN_MotorDrive_MAX));
    /* ���÷���ֵ */
    TLE9210x_FuncLayer_set_Control_HBMODE(HbModeRegBuf);
    Srvl_Tle9210x_SendSetReg();

}

/***********************************************************************
 * @function name: Srvl_Tle9210x_SetSeatMotorPwm
 * @description: ����pwm�ӿ�
 * @input parameters: SeatDrv:���ͨ�� Control:���Ʒ��� - (ʹ��TLE9210x_Brake)����ӳ��pwm ����Ҫ��pwm���ðٷְ� ���ٹر�
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.05.20
 ***********************************************************************/
void Srvl_Tle9210x_SetSeatMotorPwm(enTLE9210x_SeatDrvtype SeatDrv,enTLE9210x_ControlMode Control,INT8U PwmCnt)
{
    const en_FtmCcpChannelType PwmSetChannel[EN_SEAT_DRV_MAX] = 
        {EN_CCP_9210X_1_3,EN_CCP_9210X_1_2,EN_CCP_9210X_1_4,EN_CCP_9210X_1_1,
        EN_CCP_9210X_2_1,EN_CCP_9210X_2_2};
    const INT8U PwmMax = 100;
    static INT8U PwmCntOld[EN_SEAT_DRV_MAX] = {0};

    /* ����Χ */
    if(SeatDrv >= EN_SEAT_DRV_MAX || Control >= TLE9210x_ModeMAX || PwmCnt > PwmMax)
    {
        return;
    }
    
    if(Control == TLE9210x_OFF) //�رյ�� pwm ����100 - ��ɲ������ʹ��
    {
        PwmCnt = PwmMax;
    }
    
    if(PwmCntOld[SeatDrv] != PwmCnt)//���ظ�����
    {
        PwmCntOld[SeatDrv] = PwmCnt;
        Ecual_UpDatePwmDuty(PwmSetChannel[SeatDrv],PwmCnt);
    }
    
    Srvl_Tle9210x_SetSeatMotor(SeatDrv,Control);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_SetSeatMotor
 * @description: ���ε��ڽӿ�
 * @input parameters: SeatDrv:���ͨ�� Control:���Ʒ��� - (ʹ��TLE9210x_Brake)����ӳ��pwm ����Ҫ��pwm���ðٷְ� ���ٹر�
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.05.20
 ***********************************************************************/
void Srvl_Tle9210x_SetSeatMotor(enTLE9210x_SeatDrvtype SeatDrv,enTLE9210x_ControlMode Control)
{
    const INT8U SeatMotorCntMax = 5;
    static INT8U SeatMotorCnt[EN_SEAT_DRV_MAX] = {0};
    static enTLE9210x_ControlMode ContorModeOld[EN_SEAT_DRV_MAX] = {0};

    
    /* ����Χ */
    if(SeatDrv >= EN_SEAT_DRV_MAX || Control >= TLE9210x_ModeMAX)
    {
        return;
    }

    /* �������� */
    if(ContorModeOld[SeatDrv] == Control && SeatMotorCnt[SeatDrv] > SeatMotorCntMax)
    {
        return;
    }
    
    /* ��ͬ���ڵ�� ��ͬ���ڷ��� */
    if(ContorModeOld[SeatDrv] != Control)
    {
        ContorModeOld[SeatDrv] = Control;
        SeatMotorCnt[SeatDrv] = 0;
    }

    if(Control == TLE9210x_OFF && SeatMotorCnt[SeatDrv] < 2) // �������ٹر� - ɲ��
    {
        Control = TLE9210x_Brake;
    }
    else
    {
        
    }

    
//	kf_printf("HSw:%d -- Mot:%d\r\n",Rte_GetVfb_PaBackSwitchCmd(),Rte_GetVfb_PaBackMotorCmd());
//	kf_printf("SeatDrv:%d -- Control:%d\r\n",SeatDrv,Control);
    SeatMotorCnt[SeatDrv] += 1;
    
    switch(SeatDrv)
    {
        case EN_SEAT_DRV_HEIGHT:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,EN_MotorDrive_3,Control);
        break;
        case EN_SEAT_DRV_LENGTH:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,EN_MotorDrive_1,Control);
        break;
        case EN_SEAT_DRV_BACK:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,EN_MotorDrive_2,Control);
        break;
        case EN_SEAT_DRV_FRONT:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,EN_MotorDrive_0,Control);
        break;
        case EN_SEAT_PAS_LENGTH:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_2,EN_MotorDrive_0,Control);
        break;
        case EN_SEAT_PAS_BACK:
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_2,EN_MotorDrive_1,Control);
        break;
        default:
        break;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_PwmSet
 * @description: 
    PWM����-����ͨ��������HBMODE��Ӧ HSxorLSx ��Ӧ�ӿ� Srvl_Tle9210x_IoSet
    ��PWMͨ�����仯����Srvl_Tle9210x_StaticInitʱ ���á�
 * @input parameters: Num:оƬ�� PwmCh:pwmͨ�� PwmEn:pwmʹ�� HBCh:����ͨ��
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
void Srvl_Tle9210x_PwmSet(en_TLE9210x_NumMaxType Num,enTLE9210x_PWMCh PwmCh,INT8U PwmEn,enTLE9210x_HBCh HBCh)
{
    fpDEVICE_initDeviceReg SetPwmxHbFunc[TLE9210x_PWM4] = {&TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_HB,
                                              &TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_HB,
                                              &TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_HB};
    fpDEVICE_initDeviceReg SetPwmxEnFunc[TLE9210x_PWM4] = {&TLE9210x_FuncLayer_set_Control_PWMSET_PWM1_EN,
                                              &TLE9210x_FuncLayer_set_Control_PWMSET_PWM2_EN,
                                              &TLE9210x_FuncLayer_set_Control_PWMSET_PWM3_EN};
    /* ����Χ */
    if(HBCh >= TLE9210x_HBChMAX || Num >= EN_TLE9210X_NUM_MAX || PwmCh >= TLE9210x_PWMChMAX)
    {
        return;
    }
    
    /* ��Ҫ������оƬ �ٿ��� */
    /* �ر�PWM4 ��Ҫ������ENΪ�ߵ�ƽ���ٹرա�*/
    Srvl_Tle9210x_SetChip(Num);
    if(PwmCh == TLE9210x_PWM4) /* pwm4-ֻ��ӳ�䵽HB6 */
    {
        Srvl_Tle9210x_WriteDEVID();
        /* ����pwm4 ENʹ�� */
        TLE9210x_FuncLayer_set_Control_CSA_OC_SH_HB6_PWM4_EN(PwmEn);
        /* spi�������� */
        Srvl_Tle9210x_SendSetReg();
    }
    else
    {
        /* ����pwm HBʹ�� */
        SetPwmxHbFunc[PwmCh](HBCh);
        /* spi�������� */
        Srvl_Tle9210x_SendSetReg();
        /* ����pwm ENʹ�� */
        SetPwmxEnFunc[PwmCh](PwmEn);
        /* spi�������� */
        Srvl_Tle9210x_SendSetReg();
    }
}


/***********************************************************************
 * @function name: Srvl_Tle9210x_GetOffStateDiag
 * @description: ��ǰ����״̬
 * @input parameters: Num:оƬ�� HbCh����ͨ����
 * @output parameters: enTLE9210x_OffStateErrType
 * @return: enTLE9210x_OffStateErrType:�ع���ʵʱ״̬
 * @note:
 * @author: czy
 * @date: 2025.04.27
 ***********************************************************************/
enTLE9210x_OffStateErrType Srvl_Tle9210x_GetOffStateDiag(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbCh)
{
    if(Num >= EN_TLE9210X_NUM_MAX || HbCh >= TLE9210x_HBChMAX)
    {
        return EN_OFF_STATE_ERR_NONE;
    }
    /*s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_WAIT 
    ��ʱ����ܶ����� -����wait���� Ϊ���ڼ����Ϲ��� ������ 
    ʹ�� Srvl_Tle9210x_GetWaitOffStateDiag ���ܻ���ڴ����� */
    return s_SrvlTle9210x_OffStateErr[Num][HbCh];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetWaitOffStateDiag
 * @description: �����ɺ�Ĺ���״̬
 * @input parameters: Num:оƬ�� HbCh����ͨ����
 * @output parameters: enTLE9210x_OffStateErrType
 * @return: enTLE9210x_OffStateErrType:�ع���ȷ��״̬
 * @note:
 * @author: czy
 * @date: 2025.05.12
 ***********************************************************************/
enTLE9210x_OffStateErrType Srvl_Tle9210x_GetWaitOffStateDiag(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbCh)
{
    if(Num >= EN_TLE9210X_NUM_MAX || HbCh >= TLE9210x_HBChMAX)
    {
        return EN_OFF_STATE_ERR_NONE;
    }
    return s_SrvlTle9210x_OffWaitStateErr[Num][HbCh];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_MainCycleFunction
 * @description: оƬ��������
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
void Srvl_Tle9210x_MainCycleFunction(void)
{
    Srvl_Tle9210x_FeedWdg();                    /* ι�� */
    Srvl_Tle9210x_OffStateDiagnostic();         /* �ر�״̬��� */
    Srvl_Tle9210x_ResetChipControlFunc();       /* оƬ��λ��� */
    Srvl_Tle9210x_TempVoltageErrStsFunc();      /* ���� ��ѹ ���� */
    Srvl_Tle9210x_DrainSourceVolErrStsFunc();   /* ©Դ��ѹ */
//    Srvl_Tle9210x_StatusReg_UpdateCycle();      /* ��ȡ״̬�Ĵ��� - ����ɾ�� */
    Srvl_Tle9210x_PWM4EnCheckReset();           /* ����PWM4 �����Ƿ���;��λ */
    Srvl_Tle9210x_Test();
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetTempSts
 * @description: ��ȡоƬ�¶�״̬ - TjW��ֵ=140��  Tjsd��ֵ=180��
 * @input parameters: Num:оƬ��
 * @output parameters: enTLE9210x_TempStsType
 * @return: enTLE9210x_TempStsType:�¶ȹ���״̬
 * @note:
 * @author: czy
 * @date: 2025.04.27
 ***********************************************************************/
enTLE9210x_TempStsType Srvl_Tle9210x_GetTempSts(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return EN_TLE9210X_TEMP_STS_NONE;
    }
    return s_SrvlTle9210x_TempStsErr[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetFailSafeSts
 * @description: ��ȡоƬ��ȫ����-��γ��Իָ�ʧ�� 
 * @input parameters: Num:оƬ��
 * @output parameters: INT8U
 * @return: INT8U:оƬ��ʼ������״̬
 * @note:
 * @author: czy
 * @date: 2025.04.27
 ***********************************************************************/
INT8U Srvl_Tle9210x_GetFailSafeSts(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return EN_TLE9210X_TEMP_STS_NONE;
    }
    return s_SrvlTle9210x_ResetChip[Num].ErrSts;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetDrainSourceErr
 * @description: ��ȡ���ڹ����г���©Դ���� 
 * @input parameters: Num:оƬ�� HbxCh:����ͨ��
 * @output parameters: enTLE9210x_DrainSErrType
 * @return: enTLE9210x_DrainSErrType:©Դ����״̬
 * @note:
 * @author: czy
 * @date: 2025.05.06
 ***********************************************************************/
enTLE9210x_DrainSErrType Srvl_Tle9210x_GetDrainSourceErr(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbxCh)
{
    if(Num >= EN_TLE9210X_NUM_MAX || HbxCh >= TLE9210x_HBChMAX)
    {
        return EN_TLE9210X_DSOV_STS_NONE;
    }
    return s_SrvlTle9210x_DrainSourceErr[Num][HbxCh];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetChipInitErrSts
 * @description: ��ȡ��ʼ��״̬ 
 * @input parameters: en_TLE9210x_NumMaxType 
 * @output parameters: INT8U
 * @return: s_SrvlTle9210x_ChipInitErrSts
 * @note:
 * @author: czy
 * @date: 2025.05.19
 ***********************************************************************/
INT8U Srvl_Tle9210x_GetChipInitErrSts(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    return s_SrvlTle9210x_ChipInitErrSts[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetVMStsErr
 * @description: ��ȡVM״̬
 * @input parameters: Num:оƬ�� 
 * @output parameters: enTLE9210x_VMStsType
 * @return: s_SrvlTle9210x_VMStsErr:vm����״̬
 * @note:
 * @author: czy
 * @date: 2025.05.19
 ***********************************************************************/
enTLE9210x_VMStsType Srvl_Tle9210x_GetVMStsErr(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    return s_SrvlTle9210x_VMStsErr[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetChargePumpUnderVStsErr
 * @description: ��ȡ����״̬ 
 * @input parameters: Num:оƬ��  
 * @output parameters: INT8U
 * @return: s_SrvlTle9210x_ChargePumpUnderVStsErr:����״̬
 * @note:
 * @author: czy
 * @date: 2025.05.19
 ***********************************************************************/
INT8U Srvl_Tle9210x_GetChargePumpUnderVStsErr(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    return s_SrvlTle9210x_ChargePumpUnderVStsErr[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetDataReadErr
 * @description: PWM4���� ��ȡ��оƬ���ݹ���״̬ 
 * @input parameters: Num:оƬ�� 
 * @output parameters: INT8U
 * @return: s_SrvlTle9210x_DataReadErr:pwm4�����쳣
 * @note:
 * @author: czy
 * @date: 2025.05.23
 ***********************************************************************/
INT8U Srvl_Tle9210x_GetDataReadErr(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    return s_SrvlTle9210x_DataReadErr[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetWdFlag
 * @description: ι��״̬ 
 * @input parameters: Num:оƬ�� 
 * @output parameters: INT8U
 * @return: 
 * @note:
 * @author: czy
 * @date: 2025.06.17
 ***********************************************************************/
INT8U Srvl_Tle9210x_GetWdFlag(en_TLE9210x_NumMaxType Num)
{
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return FALSE;
    }
    return s_SrvlTle9210xWdFlg[Num];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetMotorErr
 * @description: ����ֹͣ 
 * @input parameters: enTLE9210x_SeatDrvtype ��������
 * @output parameters: enTLE9210x_MotorErrStsType ֹͣԭ��
 * @return: 
 * @note:
 * @author: czy
 * @date: 2025.06.18
 ***********************************************************************/
enTLE9210x_MotorErrStsType Srvl_Tle9210x_GetMotorErr(enTLE9210x_SeatDrvtype SetMotor)
{
    const en_TLE9210x_NumMaxType Num[EN_SEAT_DRV_MAX] = {
        EN_TLE9210X_NUM_1,EN_TLE9210X_NUM_1,EN_TLE9210X_NUM_1,EN_TLE9210X_NUM_1,
        EN_TLE9210X_NUM_2,EN_TLE9210X_NUM_2};
    const enTLE9210x_HBCh HBCh[EN_SEAT_DRV_MAX][2] = {
        {TLE9210x_HB7,TLE9210x_HB8},
        {TLE9210x_HB3,TLE9210x_HB4},
        {TLE9210x_HB5,TLE9210x_HB6},
        {TLE9210x_HB1,TLE9210x_HB2},
        {TLE9210x_HB1,TLE9210x_HB2},
        {TLE9210x_HB3,TLE9210x_HB4}};
    
    enTLE9210x_MotorErrStsType MotorStpSts = EN_TLE9210X_ERR_NONE;

    if(SetMotor >= EN_SEAT_DRV_MAX)//��ֵ
    {
        return EN_TLE9210X_ERR_NONE;
    }

    if(Num[SetMotor] >= EN_TLE9210X_NUM_MAX)//��ֵ
    {
        return EN_TLE9210X_ERR_NONE;
    }

    if(Srvl_Tle9210x_GetChipInitErrSts(Num[SetMotor]) != FALSE)
    {
        MotorStpSts = EN_TLE9210X_ERR_INIT;
    }
    else if(Srvl_Tle9210x_GetFailSafeSts(Num[SetMotor]) != FALSE)
    {
        MotorStpSts = EN_TLE9210X_ERR_SAFE;
    }
    else if(Srvl_Tle9210x_GetVMStsErr(Num[SetMotor]) != EN_TLE9210X_VM_STS_NONE)
    {
        MotorStpSts = EN_TLE9210X_ERR_VM;
    }
    else if(Srvl_Tle9210x_GetTempSts(Num[SetMotor]) == EN_TLE9210X_TEMP_STS_ERR)
    {
        MotorStpSts = EN_TLE9210X_ERR_TEMP;
    }
    else if(Srvl_Tle9210x_GetChargePumpUnderVStsErr(Num[SetMotor]) != FALSE)
    {
        MotorStpSts = EN_TLE9210X_ERR_PUMP;
    }
    else if(Srvl_Tle9210x_GetDrainSourceErr(Num[SetMotor],HBCh[SetMotor][0]) != EN_TLE9210X_DSOV_STS_NONE
    || Srvl_Tle9210x_GetDrainSourceErr(Num[SetMotor],HBCh[SetMotor][1]) != EN_TLE9210X_DSOV_STS_NONE)
    {
        MotorStpSts = EN_TLE9210X_ERR_DS;
    }
    else if(Srvl_Tle9210x_GetWaitOffStateDiag(Num[SetMotor],HBCh[SetMotor][0]) != EN_OFF_STATE_ERR_NONE
    || Srvl_Tle9210x_GetWaitOffStateDiag(Num[SetMotor],HBCh[SetMotor][1]) != EN_OFF_STATE_ERR_NONE)
    {
        MotorStpSts = EN_TLE9210X_ERR_OFF;
    }
    else{}
    
    return MotorStpSts;
}

#if 1
INT8U OffStateDiag = 0;
INT8U EnFlg = 0;
INT8U IoSetFlg = 0;
INT8U ClearFs = 0;
enTLE9210x_MotorDriveIndex MotorDriver = 1;
enTLE9210x_SeatDrvtype MotorDrivertype = 6;

INT8U PwmIndex = 3;
INT8U PwmCycle = 50;
INT8U PwmEnable = 0;
INT8U PwmSetFg = 0;
enTLE9210x_HBCh PwmHBCh = TLE9210x_HB3;
enTLE9210x_PWMCh PwmWMCh = TLE9210x_PWM1;
INT8U PwmTo9210Enable = 1;
INT8U PwmHbFor = TLE9210x_ForRot;
enTLE9210x_ControlMode ControrlMode = 0;


INT8U ChipCnt = 0;
INT8U SetEnFlg = 0;
/***********************************************************************
 * @function name: Srvl_Tle9210x_Test
 * @description: ����
 * @input parameters: void 
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.05.23
 ***********************************************************************/
void Srvl_Tle9210x_Test(void)
{
//    INT32U Cnt = 0;
	static INT32U Cnt = 0;
    if(EnFlg == 0)
    {
    //    Srvl_Tle9210x_SetChipEn(0,1);
    }
    else if(EnFlg == 1)
    {
        EnFlg = 0;
        Srvl_Tle9210x_SetChipEn(ChipCnt,SetEnFlg);
        if(SetEnFlg != 0)
        {
            Srvl_Tle9210x_Init(ChipCnt);
        }
    }

    if(OffStateDiag == 1)
    {
        Srvl_Tle9210x_OffStateDiagnostic();
    }

    if(PwmEnable == 1)
    {
        PwmEnable = 0;
        Ecual_UpDatePwmDuty(PwmIndex,PwmCycle);
    }

    if(PwmSetFg == 1)
    {
        /* �����ֲ�DR7808Q - 6.8.3ʾ�� */
        /* ����HBxMODE=00b -> ����PWMx_HB����Ӧͨ��,ʹ��PWM_EN -> ����ͨ��������� */
        PwmSetFg = 0;
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,MotorDriver,TLE9210x_OFF);
        Srvl_Tle9210x_PwmSet(EN_TLE9210X_NUM_1,PwmWMCh,PwmTo9210Enable,PwmHBCh);
        Srvl_Tle9210x_IoSet(EN_TLE9210X_NUM_1,MotorDriver,PwmHbFor);
    }
    /*
    Srvl_Tle9210x_TempVoltageErrStsFunc();
    Srvl_Tle9210x_StatusReg_UpdateCycle();
    Srvl_Tle9210x_DrainSourceVolErrStsFunc();
*/
    if(ClearFs == 1)
    {
        ClearFs = 0;
        Srvl_Tle9210x_ResetChipControlFunc();
    }
//    Srvl_Tle9210x_FeedWdg();
    if(IoSetFlg == 1)
    {
        Cnt++;
        Srvl_Tle9210x_SetSeatMotor(MotorDrivertype,ControrlMode);
    }
    else if(IoSetFlg == 2)
    {
        Srvl_Tle9210x_SetSeatMotorPwm(MotorDrivertype,ControrlMode,PwmCycle);
    }
}
#endif

 /*************************************************************************************************
 * End Of File
 *************************************************************************************************/

