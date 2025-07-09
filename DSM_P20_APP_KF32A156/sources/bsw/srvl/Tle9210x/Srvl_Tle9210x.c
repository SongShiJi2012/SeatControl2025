/****************************Copyright (c)********************************************************
**                      Southern Dare Co.,Ltd.
**
**--------------File Info-------------------------------------------------------------------------
** File Name:               文件名(Srvl_Tle9210x.c)
** Created By:              hqj
** Created date:            2023-12-14
** Version:                 V1.0
** Descriptions:            与TLE9210x相关的具体功能
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
/*! SPI发送和接收数组*/
static INT32U s_SpiTxBuff = 0;
static INT32U s_SpiRxBuff = 0;

const stTLE9210x_MotorDriveInfoType MotorDriveInfo[EN_MotorDrive_MAX] = /* TLE2910x资源分配信息 */
{
	{EN_MotorDrive_0,TLE9210x_HB1,TLE9210x_HB2,TLE9210x_PWM1},
	{EN_MotorDrive_1,TLE9210x_HB3,TLE9210x_HB4,TLE9210x_PWM2},
	{EN_MotorDrive_2,TLE9210x_HB5,TLE9210x_HB6,TLE9210x_PWM3},
	{EN_MotorDrive_3,TLE9210x_HB7,TLE9210x_HB8,TLE9210x_PWM1},
};

const stTLE9210x_ChipInfoType s_SrvlTle9210xChipInfo[EN_TLE9210X_NUM_MAX] =/* 预驱芯片相关信息 */
{
    /* 芯片序号             芯片型号             通道数           EN         CS       */ 
    {EN_TLE9210X_NUM_1,EN_CHIP_TLE92108,   8,  GPIOA_SFR, 5U, GPIOD_SFR,13U,FALSE},
    {EN_TLE9210X_NUM_2,EN_CHIP_TLE92104,   4,  GPIOD_SFR, 5U, GPIOA_SFR,1U, FALSE},
};

static INT8U s_SrvlTle9210xWdFlg[EN_TLE9210X_NUM_MAX] = {0};//在初始化中配置 

static en_TLE9210x_NumMaxType s_Tle9210X_CurrentChipNum = EN_TLE9210X_NUM_1;/* 当前通讯预驱芯片 */


/* 关闭状态故障检测 */
static enTLE9210x_OffStateStepType s_SrvlTle9210x_OffStateStep[EN_TLE9210X_NUM_MAX] = {EN_OFF_STATE_STEP_NONE};
static enTLE9210x_OffStateErrType s_SrvlTle9210x_OffStateErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_OFF_STATE_ERR_NONE};
static enTLE9210x_OffStateErrType s_SrvlTle9210x_OffWaitStateErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_OFF_STATE_ERR_NONE};

/* 复位检测 */
static Srvl_TLE9210x_ResetChipType s_SrvlTle9210x_ResetChip[EN_TLE9210X_NUM_MAX];

/* 温度检测 */
static enTLE9210x_TempStsType s_SrvlTle9210x_TempStsErr[EN_TLE9210X_NUM_MAX] = {EN_TLE9210X_TEMP_STS_NONE};

/* VM检测 */
static enTLE9210x_VMStsType s_SrvlTle9210x_VMStsErr[EN_TLE9210X_NUM_MAX] = {EN_TLE9210X_VM_STS_NONE};

/* 充电泵欠压检测 */
static INT8U s_SrvlTle9210x_ChargePumpUnderVStsErr[EN_TLE9210X_NUM_MAX] = {FALSE};


/* 漏源故障检测 */
static enTLE9210x_DrainSErrType s_SrvlTle9210x_DrainSourceErr[EN_TLE9210X_NUM_MAX][TLE9210x_HBChMAX] = {EN_TLE9210X_DSOV_STS_NONE};

/* 获取数据异常-可做调试使用 */
INT8U s_SrvlTle9210x_DataReadErr[EN_TLE9210X_NUM_MAX] = {0};

/* 初始化状态 */
static INT8U s_SrvlTle9210x_ChipInitErrSts[EN_TLE9210X_NUM_MAX] = {FALSE};
/*************************************************************************************************
 * Global Variable declaration
 *************************************************************************************************/
static void Srvl_Tle9210x_ReadStatus_GDF(void);

/*轮询获取 状态寄存器数组 */
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

/* 故障状态获取 */
/* GENSTAT 0xE2*/
/* 热故障:TSD 热警告:TW OC2过流:OC2 OC1过流:OC1 VM过压:VSOV VM欠压:VSUV 充电泵欠压:CPUV */

/* DSOV 0xE4*/
/* 通道漏源过压 */

/* HBVOUT_PWMERR 0xE6*/
/* PWM 通道配置错误:HBxPWME，无开HB确过压:HBxVOUT */

/* EFF_TDON_OFFx-0xE8 0xEA 0xEC*/
/* PWM 开关时间 */

/* TRISE_FALL 0xF2 0xEE 0xF0*/
/* PWM  上升下降故障时间*/

/* GDF -需要写A55A到1F才能访问 0xF4*/
/* 栅极死区时间过短 */
/*轮询更新 状态寄存器缓存RAM数组 */
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
* @description: 初始化
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
* @description: spi发数据
* @input parameters: DataBuff:spi输入参数
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
    
    TLE9210x_ServLayer_getSpiData();//读数据放到各缓存区
}

/***********************************************************************
* @function name: Srvl_Tle9210x_SpiMasterReadData
* @description: spi获取数据
* @input parameters: INT32U:spi值
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

    TLE9210x_SetByte0GSB(s_Tle9210X_CurrentChipNum,RxBuff);/*设置总状态 */

    /* 每次发送数据-确认接收的故障状态-防止误判断 */
    Srvl_Tle9210x_SetResetChipErrCnt(s_Tle9210X_CurrentChipNum);
	return s_SpiRxBuff;
}

/***********************************************************************
* @function name: Srvl_Tle9210x_GetSpiRegData
* @description: spi获取数据
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
* @description: 设置通讯芯片
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
* @description: 设置通讯芯片EN引脚
* @input parameters: INT32U
* @output parameters: void
* @return: void
* @note:
* @author: czy
* @date: 2025.04.16
***********************************************************************/
static void Srvl_Tle9210x_SetChipEn(en_TLE9210x_NumMaxType Num,INT8U EnSts)
{
    /* 超范围 */
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
* @description: 设置故障复位计数
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
* @description: 控制寄存器发送数据
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
* @description: 状态寄存器发送数据
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
 * @description: 进入访问寄存器设置
 * @input parameters: en_TLE9210x_NumMaxType INT8U
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_WriteDEVID(void)
{
    const INT16U WriteReadSeg = 0xA55A; /* 访问寄存器1A 1C 1D 1E 需要先往DEVID写入0xA55A */

    TLE9210x_RegLayer_set_Status_DEVID(WriteReadSeg);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_ReadStatus_GDF
 * @description: 获取状态寄存器 GDF
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.23
 ***********************************************************************/
static void Srvl_Tle9210x_ReadStatus_GDF(void)
{
    Srvl_Tle9210x_WriteDEVID();//写此寄存器 会报SPIE 属于正常现象-非故障
    TLE9210x_RegLayer_get_Status_GDF();
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_WriteControl_DRV_LPWR_EN
 * @description: 设置 DRV_LPWR_EN寄存器
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
 * @description: 初始化
 * @input parameters: en_TLE9210x_NumMaxType 
 * @output parameters: void
 * @return: INT8U
 * @note:
 * @author: czy
 * @date: 2025.04.16
 ***********************************************************************/
static void Srvl_Tle9210x_PwmInit(en_TLE9210x_NumMaxType Num)
{
    /* 超范围 */
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
 * @description: 初始化-若打开看门狗，调试需打断点的 先失能
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

    /*2M spi 初始化单芯片寄存器使用时间 1.2ms */
     fpDEVICE_initDeviceReg fp_initRegAll[] = {&TLE9210x_FuncLayer_set_Control_GENCTRL1,
                                               &TLE9210x_FuncLayer_set_Control_GENCTRL2,
                                               &TLE9210x_FuncLayer_set_Control_VDS2,                      //8通道 特有 
                                               &TLE9210x_FuncLayer_set_Control_VDS1,
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK1,                  /* 交叉电流保护 空白时间设定 */
                                               &TLE9210x_FuncLayer_set_Control_HBMODE,                     /* 通道设置 */

                                               /*REG_BANK=0才能设置 */
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK2_ACT,              /* active mos 时间设定 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_ACT,  /* pwm 最大驱动电流 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHG_ACT,              /* active pwm充电电流 */
                                               &TLE9210x_FuncLayer_set_Control_ST_ICHG,                   /* 静态充放电通道与电流设置*/
                                               &TLE9210x_FuncLayer_set_Control_PWM_IDCHG_ACT,             /* pwm 放电电流 */

                                               /*REG_BANK=1才能设置-每次设置GENCTRL1都需要反转 WDTRIG */
                                               &TLE9210x_FuncLayer_set_Control_GENCTRL1,
                                               &TLE9210x_FuncLayer_set_Control_CCP_BLK2_FW,               /* FreeWheeling mos 时间设定 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHGMAX_CCP_BLK3_FW,   /* pwm 最大驱动电流 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_ICHG_FW,               /* freewheeling pwm充放电电流*/
                                               &TLE9210x_FuncLayer_set_Control_PWM_PDCHG_INIT,            /* pwm预放电电流 */
                                               &TLE9210x_FuncLayer_set_Control_PWM_PCHG_INIT,             /* pwm预充电流 */

                                               &TLE9210x_FuncLayer_set_Control_PWMSET,                    /* PWM 设置*/
                                               &TLE9210x_FuncLayer_set_Control_TPRECHG,                   /* 预充电时间设定 */
                                               &TLE9210x_FuncLayer_set_Control_HBIDIAG,                   /* 半桥诊断时间控制 */
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF1,                 /* pwm on off 延时时间 */
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF2,
                                               &TLE9210x_FuncLayer_set_Control_TDON_OFF3};
     INT16U u16_initRegValueAll[EN_TLE9210X_NUM_MAX][23] = {
                                             /*预驱动1-7808 */
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
                                              /*预驱动2-7804*/
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
                                             
    /* 超范围 */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return EN_TLE9210X_INIT_CHIP;
    }
    
    Srvl_Tle9210x_SetChip(Num);//设置芯片-寄存器存储RAM
    //初始化GENCTRL1-反转看门狗(设置GENCTRL1 均需反转WDTRIG)
    (void)TLE9210x_RegLayer_set_Control_GENCTRL1(u16_initRegValueAll[Num][0]); /* polyspace MISRA2012:8.7 [Justified: Low] "Given due architecture" */

    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL1;}//SPI异常
    /* Disable/Enable watchdog depending on parameter */
    if (s_SrvlTle9210xWdFlg[Num] == FALSE) 
    {
        //设置UNLOCK 等待失能看门狗
        TLE9210x_RegLayer_set_Control_GENCTRL1((u16_initRegValueAll[Num][0] | TLE9210x_Control_GENCTRL1_UNLOCK_Mask) 
        & ~TLE9210x_Control_GENCTRL1_WDTRIG_Mask);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_WD1;}//SPI异常
        //初始化GENCTRL2-失能看门狗
        TLE9210x_RegLayer_set_Control_GENCTRL2(u16_initRegValueAll[Num][1] | TLE9210x_Control_GENCTRL2_WDDIS_Mask);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL2;}//SPI异常
        TLE9210x_RegLayer_set_Control_GENCTRL1(u16_initRegValueAll[Num][0]);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_WD2;}//SPI异常
    }
    else
    {
        TLE9210x_RegLayer_set_Control_GENCTRL2(u16_initRegValueAll[Num][1]);
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_GENCTRL2;}//SPI异常
    }
    
    /* 初始化控制寄存器 */
    u8_initRegisterNum = (INT8U)((sizeof(u16_initRegValueAll)/sizeof(u16_initRegValueAll[0][0]))/EN_TLE9210X_NUM_MAX);
    VdsEnum = (s_SrvlTle9210xChipInfo[Num].ChxMax == 4)?(2):(3);//4通道的不需要设置VDS2
    for(u8_initRegisterCounter = VdsEnum; u8_initRegisterCounter < u8_initRegisterNum; u8_initRegisterCounter++)
    {
        fp_initRegTemp = fp_initRegAll[u8_initRegisterCounter];
        u16_initRegValueTemp = u16_initRegValueAll[Num][u8_initRegisterCounter];
        fp_initRegTemp(u16_initRegValueTemp);
        Srvl_Tle9210x_SendSetReg();
        if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_REG;}//SPI异常
    }
    /* 初始化后清除一次 GENSTAT寄存器 促使NPOR置1 */
    TLE9210x_RegLayer_set_Status_GENSTAT(0);
    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_CLE;}//SPI异常

    /* 初始化 PWM控制 */
    Srvl_Tle9210x_PwmInit(Num);
    if(TLE9210x_GetByte0GSB_SPIE(Num) == TRUE){return EN_TLE9210X_INIT_PWM;}//SPI异常

    return EN_TLE9210X_INIT_NONE;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_Init
 * @description: 初始化-若打开看门狗，调试需打断点的 先失能
 * @input parameters: Num:芯片号 
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

    /* 超范围 */
    if(Num >= EN_TLE9210X_NUM_MAX)
    {
        return;
    }
    
    if(AppFlashStartAddr == 0)
    {
        s_SrvlTle9210xWdFlg[Num] = FALSE; //调试起始地址为0 进这里失能看门狗
    }
    else
    {
        s_SrvlTle9210xWdFlg[Num] = TRUE; //使能看门狗-调试打断点时会复位预驱
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
        /* 初始化失败 */
        s_SrvlTle9210x_ChipInitErrSts[Num] = InitResult;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_FeedWdg
 * @description: 喂狗
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

    /* 轮询喂狗 */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
    /* 不喂狗则不执行 */
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
 * @description: 诊断控制获取芯片RAM中寄存器值
 * @input parameters: ChipCnt:芯片号  Reg寄存器号
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
 * @description: 诊断控制获取实际芯片当前寄存器值
 * @input parameters: ChipCnt:芯片号  Reg寄存器号
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
        /* spi获取寄存器信息 */
        s_SrvlTle9210x_GetRegStsFunc[Reg](); 
        /* 将获取数据存储到备份RAM中 */
        TempRegData = Srvl_Tle9210x_GetSpiRegData();
        s_SrvlTle9210x_UpdataRegStsFunc[Reg](s_Tle9210X_CurrentChipNum,TempRegData);
        return TempRegData;
    }
    return FALSE;
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_StatusReg_UpdateCycle
 * @description: 读取状态寄存器
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

    for(ChipCnt = 0;ChipCnt < 1;ChipCnt++)//轮询查各芯片状态寄存器
    {
        //设置芯片-寄存器存储RAM
        Result = Srvl_Tle9210x_SetChip(ChipCnt);
        
        if(s_SrvlTle9210x_GetRegStsFunc[UpdateCnt] != NULL 
        && s_SrvlTle9210x_UpdataRegStsFunc[UpdateCnt] != NULL
        && Result == TRUE)
        {
            /* spi获取寄存器信息 */
            s_SrvlTle9210x_GetRegStsFunc[UpdateCnt](); 
            /* 将获取数据存储到备份RAM中 */
            TempRegData = Srvl_Tle9210x_GetSpiRegData();
            s_SrvlTle9210x_UpdataRegStsFunc[UpdateCnt](s_Tle9210X_CurrentChipNum,TempRegData);
        }
    }
    if(UpdateCnt < UpdateCntMax)/* 周期轮询查状态寄存器 */
    {
        UpdateCnt = UpdateCnt + 1;
    }
    else
    {
        UpdateCnt = 0;
        //ChipCnt = (ChipCnt < (EN_TLE9210X_NUM_MAX - 1))?(ChipCnt + 1):(EN_TLE9210X_NUM_1);/* 轮询查芯片 */
    }
}
/***********************************************************************
 * @function name: Srvl_Tle9210x_TempVoltageErrStsFunc
 * @description: 温度-电压故障数据
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
    /* 轮询检查 */
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

    /* 清除GENSTAT并获取状态 */
    Srvl_Tle9210x_SetChip(ChipNum);
    TLE9210x_RegLayer_set_Status_GENSTAT(0);
    TLE9210x_Update_Status_GENSTAT(ChipNum,Srvl_Tle9210x_GetSpiRegData());

    GENSTATRegValue = TLE9210x_Get_Reg_Status_GENSTAT(ChipNum);
    VMSts = (GENSTATRegValue >> 1) & 0X03;

    //VM 状态
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
    //充电泵状态
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

    //温度状态
    if(TempErrSts == FALSE)
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_NONE;
    }
    else if(TLE9210x_FuncLayer_get_Status_GENSTAT_TSD() != FALSE) /* 过温关断 */
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_ERR;
    }
    else if(TLE9210x_FuncLayer_get_Status_GENSTAT_TW() != FALSE) /* 过温警告 */
    {
        s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_WARRING;
    }
    else
    {   /* 故障消失 - 使用TempErrSts检测 */
        //s_SrvlTle9210x_TempStsErr[ChipNum] = EN_TLE9210X_TEMP_STS_NONE;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_PWM4EnCheckReset
 * @description: 开启PWM4之后检测是否反复复位-做周期检测spi通讯情况
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
    const INT16U DevidRegValueInit = 0x0001; //DR7808 7804 文档中数据均为此
    const INT8U ErrCntMax = 5;

    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
    
    Srvl_Tle9210x_SetChip(ChipNum);
    if(TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN() == FALSE) /* 没有开启PWM4 */
    {
        ErrCnt[ChipNum] = 0;
        return;
    }
    TLE9210x_RegLayer_get_Status_DEVID();
    TLE9210x_Update_Status_DEVID(ChipNum,Srvl_Tle9210x_GetSpiRegData());
    DevidRegValue = TLE9210x_Get_Reg_Status_DEVID(ChipNum);
    
    if(DevidRegValue != DevidRegValueInit) //数据不相同
    {
        ErrCnt[ChipNum] += 1;
        s_SrvlTle9210x_DataReadErr[ChipNum] = TRUE;
    }
    else
    {
        ErrCnt[ChipNum] = 0;
        s_SrvlTle9210x_DataReadErr[ChipNum] = FALSE;
    }
    //超次数 使能EN 等待检测NPOR故障在Srvl_Tle9210x_ResetChipControlFunc初始化芯片
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
 * @description: 漏源电压故障数据
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
    /* 轮询检查 */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);

    DSErrSts = TLE9210x_GetByte0GSB_VDSE(ChipNum);
    
    if(DSErrSts == FALSE)
    {
        memset(&s_SrvlTle9210x_DrainSourceErr[ChipNum][0],EN_TLE9210X_DSOV_STS_NONE,TLE9210x_HBChMAX);
        return;
    }
    /* 清除DSOV并获取状态 */
    Srvl_Tle9210x_SetChip(ChipNum);
    TLE9210x_RegLayer_set_Status_DSOV(0);
    TLE9210x_Update_Status_DSOV(ChipNum,Srvl_Tle9210x_GetSpiRegData());

    DsovRegValue = TLE9210x_Get_Reg_Status_DSOV(ChipNum);
    
    for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax*2; HbCnt+=2) /* 获取故障状态 -可能性：mos短路，负载异常 阈值不匹配 */
    {
       s_SrvlTle9210x_DrainSourceErr[ChipNum][HbCnt] = (DsovRegValue >> HbCnt) & 0x03;
    }
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_ResetChipControlFunc
 * @description: 故障复位芯片操作
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
    const INT8U ResetCntMax = 10; /* 复位芯片尝试次数 */
    const INT8U ErrCntMax = 2;    /* 故障确认次数 */
    INT8U FallStateErr = FALSE;   /* FS 故障状态 */
    INT8U PowerOnReset = FALSE;   /* NPNOR 故障状态 */

    /* 轮询检查所需重新初始化状态 */
    ChipNum = (ChipNum >= (EN_TLE9210X_NUM_MAX-1))?(EN_TLE9210X_NUM_1):(ChipNum + 1);
   // ChipNum = 0;

    ResetChip = &s_SrvlTle9210x_ResetChip[ChipNum];
    
    FallStateErr = (ResetChip->FsErrCheckCnt >= ErrCntMax)?(TRUE):(FALSE);   /* FS 故障状态 */
    PowerOnReset = (ResetChip->NporErrCheckCnt >= ErrCntMax)?(TRUE):(FALSE); /* NPOR 故障状态 */
    
    if(ResetChip->ResetChipCnt > ResetCntMax) /* 初始化超次数 */
    {
        ResetChip->ErrSts = TRUE;
        return;
    }
    
    ResetChip->ErrSts = FALSE;
    if(FallStateErr == FALSE && PowerOnReset == FALSE) /* 无FS故障 或 上电复位 */
    {
        ResetChip->ResetChipCnt = 0;
        return;
    }

    ResetChip->ResetChipCnt += 1; //若判断存在故障次数，原调节动作无效。-若需开启需要重新打开。
    
    Srvl_Tle9210x_SetChip(ChipNum);
    
    if(TLE9210x_FuncLayer_get_Control_CSA_OC_SH_HB6_PWM4_EN() == TRUE)//有开PWM4的故障-要先设置EN
    {
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,0);
        TLE9210x_WaitFor_us_HAL(150);
        Ecual_UpDatePwmDuty(EN_CCP_9210X_1_4 + ChipNum*4,100);
    }
    
    if(FallStateErr == TRUE)    /* 故障保护模式 需退回正常模式 */
    {
        TLE9210x_RegLayer_set_Status_GENSTAT(0);
        TLE9210x_Update_Status_GENSTAT(ChipNum,Srvl_Tle9210x_GetSpiRegData());
        /* 写WDTRIG_GENCTRL1 为1 */
        TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(TRUE);
        Srvl_Tle9210x_SendSetReg();
        /* 写WDTRIG_GENCTRL1 为0 */
        TLE9210x_FuncLayer_set_Control_GENCTRL1_WDTRIG(FALSE);
        Srvl_Tle9210x_SendSetReg();
    }
    
    /* 初始化控制寄存器 */
    Srvl_Tle9210x_Init(ChipNum);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_OffStateDiagnostic
 * @description: 关状态诊断
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note: 10ms周期 WaitTimeCntMax400ms 等待4s
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
static void Srvl_Tle9210x_OffStateDiagnostic(void)
{
    /*1.将源漏极过压设置到2V 
      2.检测负载断开故障- HBxIDIAG = 0 && HByIDIAG = 0 -> HBxVOUT = 1  HByVOUT = 0 
      3.检测短电源故障 - HBIDIAG = 0 -> HBxVOUT = 1
      4.检测短地故障 - HBIDIAG = 0 -> HBxVOUT = 0
      5.将漏源极过压设置到mV 
      目前需要4个周期完成检测 - 检测过程需要 禁开 HBxMODE */
                                                        /*全部上拉，Hbx上拉Hby下拉 全部下拉， */
    const INT16U RegHbidiagValue[EN_OFF_STATE_STEP_MAX] = {0x0000,0x00AA,0x00FF,0x0000,0x0000};
    const INT16U RegVds1Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS1_INIT,D_SRVL_TLE9210x_2_C_VDS1_INIT};
    const INT16U RegVds2Init[EN_TLE9210X_NUM_MAX] = {D_SRVL_TLE9210x_1_C_VDS2_INIT,D_SRVL_TLE9210x_2_C_VDS2_INIT};
    const INT16U WaitTimeCntMax = 400;/* 假设10ms 周期 */
    static INT16U s_WaitTimeCnt[EN_TLE9210X_NUM_MAX] = {0};
    INT16U RegContHBMODE = 0;
    INT16U TempRegData = 0;
    INT8U HbCnt = 0;
    INT8U HbxyValue = 0;
    en_TLE9210x_NumMaxType ChipNum = EN_TLE9210X_NUM_1;
    
    for(ChipNum = EN_TLE9210X_NUM_1;ChipNum < EN_TLE9210X_NUM_MAX;ChipNum++)
    {
        /* 需要先设置芯片 再控制输出 */
        Srvl_Tle9210x_SetChip(ChipNum);
        RegContHBMODE = TLE9210x_Get_Reg_Control_HBMODE(ChipNum);

        if((RegContHBMODE != 0 && RegContHBMODE != 0xFFFF) || s_SrvlTle9210x_OffStateStep[ChipNum] >= EN_OFF_STATE_STEP_MAX)
        {
            /* 存在电机运行不检测 */
            s_WaitTimeCnt[ChipNum] = 0;
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_WAIT;/* 运行结束之后等时间再检测 */
            continue;
        }

        /* 等待下轮 - 检测一次 */
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_WAIT)
        {   
            s_WaitTimeCnt[ChipNum] += 1;
            if(s_WaitTimeCnt[ChipNum] > WaitTimeCntMax)
            {
                s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_NONE;
            }
            else
            {
                /*检测完成再 赋值到缓存-避免检测过程中读取状态 出错 */
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
            TLE9210x_FuncLayer_set_Control_VDS1(0x0FFF); /* 设置2V */
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS2(0x0FFF); /* 设置2V */
            Srvl_Tle9210x_SendSetReg();
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_OPEN_LOAD;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_OPEN_LOAD]);
            Srvl_Tle9210x_SendSetReg();
            continue;
        }

        /* 更新HBVOUT_PWMERR状态 */
        TLE9210x_RegLayer_get_Status_HBVOUT_PWMERR();
        TempRegData = Srvl_Tle9210x_GetSpiRegData();
        TLE9210x_Update_Status_HBVOUT_PWMERR(ChipNum,TempRegData);
        TempRegData = TempRegData & 0x00FF;/* 获取 HBxVOUT状态 */
        
        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_OPEN_LOAD)
        {
            /*若HBxVOUT= 0 HByVOUT= 0则正常 */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt+=2)
            {
                HbxyValue = (TempRegData >> HbCnt) & 0x03;
               if(HbxyValue == 0x00) // 10 电机导通 电压接近0 -正常情况下为 00
               {
                    /* 正常 */
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_NONE;
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt+1] = EN_OFF_STATE_ERR_NONE;
               }
               else
               {
                    /* 异常 */
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
            /*若HBxVOUT= 0 则正常 */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt++)
            {
               if(TempRegData & (1 << HbCnt)) // 为1 
               {
                    /* 对电源短路 */
                    s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_TO_BATTERY;
               }
               else
               {
                    /* 正常 */
               }
            }
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_TO_GROUND;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_TO_GROUND]);
            Srvl_Tle9210x_SendSetReg();
            continue;
        }

        if(s_SrvlTle9210x_OffStateStep[ChipNum] == EN_OFF_STATE_STEP_TO_GROUND)
        {
            /*若HBxVOUT= 1 则正常 */
            for(HbCnt = 0; HbCnt < s_SrvlTle9210xChipInfo[ChipNum].ChxMax; HbCnt++)
            {
               if(TempRegData & (1 << HbCnt)) // 为1 
               {
                    /* 正常 */
               }
               else
               {
                  /* 对地短路 */
                   s_SrvlTle9210x_OffStateErr[ChipNum][HbCnt] = EN_OFF_STATE_ERR_TO_GROUND;
               }
            }
            s_SrvlTle9210x_OffStateStep[ChipNum] = EN_OFF_STATE_STEP_WAIT;
            TLE9210x_FuncLayer_set_Control_HBIDIAG(RegHbidiagValue[EN_OFF_STATE_STEP_WAIT]);
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS1(RegVds1Init[ChipNum]); /* 设置初始化 */
            Srvl_Tle9210x_SendSetReg();
            TLE9210x_FuncLayer_set_Control_VDS2(RegVds2Init[ChipNum]); /* 设置初始化 */
            Srvl_Tle9210x_SendSetReg();
        }
    }
}
 
/***********************************************************************
 * @function name: Srvl_Tle9210x_Driver
 * @description: 驱动设置
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
    /* 超范围 */
    if(Drv >= EN_MotorDrive_MAX || Num >= EN_TLE9210X_NUM_MAX || Cont >= TLE9210x_ModeMAX)
    {
        return;
    }
    
    /* 需要先设置芯片号 再控制输出 */
    Srvl_Tle9210x_SetChip(Num);

    if(Cont != TLE9210x_OFF)
    {
        /* 判断VDS1 2 若被静态检测修改过，则需要重新设置漏源阈值 */
        if(TLE9210x_FuncLayer_get_Control_VDS1() != RegVds1Init[Num])
        {
            TLE9210x_FuncLayer_set_Control_VDS1(RegVds1Init[Num]); /* 设置初始化 */
            Srvl_Tle9210x_SendSetReg();
        }
        
        if(TLE9210x_FuncLayer_get_Control_VDS2() != RegVds2Init[Num]
        && s_SrvlTle9210xChipInfo[Num].ChipNO == EN_CHIP_TLE92108)
        {
            TLE9210x_FuncLayer_set_Control_VDS2(RegVds2Init[Num]); /* 设置初始化 */
            Srvl_Tle9210x_SendSetReg();
        }
    }
//    TLE9210x_FuncLayer_set_Control_GENCTRL2_BD_PASS(0u);/* 上电默认设置0 此处可不设置 */
//    Srvl_Tle9210x_SendSetReg();
    
    /* 获取实际状态值*/
    HbModeRegBuf = TLE9210x_Get_Reg_Control_HBMODE(Num);

    /* 控制对应Hbx-y 开关*/
    HbModeRegBuf = (HbModeRegBuf & HbModeMask[Drv]) | (DrvMask[Cont] << (Drv * EN_MotorDrive_MAX));
    /* 设置发送值 */
    TLE9210x_FuncLayer_set_Control_HBMODE(HbModeRegBuf);
    Srvl_Tle9210x_SendSetReg();

}

/***********************************************************************
 * @function name: Srvl_Tle9210x_SetSeatMotorPwm
 * @description: 座椅pwm接口
 * @input parameters: SeatDrv:电机通道 Control:控制方向 - (使用TLE9210x_Brake)若打开映射pwm 则需要将pwm设置百分百 后再关闭
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

    /* 超范围 */
    if(SeatDrv >= EN_SEAT_DRV_MAX || Control >= TLE9210x_ModeMAX || PwmCnt > PwmMax)
    {
        return;
    }
    
    if(Control == TLE9210x_OFF) //关闭电机 pwm 设置100 - 供刹车功能使用
    {
        PwmCnt = PwmMax;
    }
    
    if(PwmCntOld[SeatDrv] != PwmCnt)//不重复设置
    {
        PwmCntOld[SeatDrv] = PwmCnt;
        Ecual_UpDatePwmDuty(PwmSetChannel[SeatDrv],PwmCnt);
    }
    
    Srvl_Tle9210x_SetSeatMotor(SeatDrv,Control);
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_SetSeatMotor
 * @description: 座椅调节接口
 * @input parameters: SeatDrv:电机通道 Control:控制方向 - (使用TLE9210x_Brake)若打开映射pwm 则需要将pwm设置百分百 后再关闭
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

    
    /* 超范围 */
    if(SeatDrv >= EN_SEAT_DRV_MAX || Control >= TLE9210x_ModeMAX)
    {
        return;
    }

    /* 超过次数 */
    if(ContorModeOld[SeatDrv] == Control && SeatMotorCnt[SeatDrv] > SeatMotorCntMax)
    {
        return;
    }
    
    /* 相同调节电机 不同调节方向 */
    if(ContorModeOld[SeatDrv] != Control)
    {
        ContorModeOld[SeatDrv] = Control;
        SeatMotorCnt[SeatDrv] = 0;
    }

    if(Control == TLE9210x_OFF && SeatMotorCnt[SeatDrv] < 2) // 先拉低再关闭 - 刹车
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
    PWM设置-设置通道后，设置HBMODE对应 HSxorLSx 对应接口 Srvl_Tle9210x_IoSet
    若PWM通道不变化，放Srvl_Tle9210x_StaticInit时 调用。
 * @input parameters: Num:芯片号 PwmCh:pwm通道 PwmEn:pwm使能 HBCh:半桥通道
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
    /* 超范围 */
    if(HBCh >= TLE9210x_HBChMAX || Num >= EN_TLE9210X_NUM_MAX || PwmCh >= TLE9210x_PWMChMAX)
    {
        return;
    }
    
    /* 需要先设置芯片 再控制 */
    /* 关闭PWM4 需要先设置EN为高电平，再关闭。*/
    Srvl_Tle9210x_SetChip(Num);
    if(PwmCh == TLE9210x_PWM4) /* pwm4-只能映射到HB6 */
    {
        Srvl_Tle9210x_WriteDEVID();
        /* 设置pwm4 EN使能 */
        TLE9210x_FuncLayer_set_Control_CSA_OC_SH_HB6_PWM4_EN(PwmEn);
        /* spi发送数据 */
        Srvl_Tle9210x_SendSetReg();
    }
    else
    {
        /* 设置pwm HB使能 */
        SetPwmxHbFunc[PwmCh](HBCh);
        /* spi发送数据 */
        Srvl_Tle9210x_SendSetReg();
        /* 设置pwm EN使能 */
        SetPwmxEnFunc[PwmCh](PwmEn);
        /* spi发送数据 */
        Srvl_Tle9210x_SendSetReg();
    }
}


/***********************************************************************
 * @function name: Srvl_Tle9210x_GetOffStateDiag
 * @description: 当前故障状态
 * @input parameters: Num:芯片号 HbCh半桥通道号
 * @output parameters: enTLE9210x_OffStateErrType
 * @return: enTLE9210x_OffStateErrType:关故障实时状态
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
    的时候才能读故障 -若非wait过程 为正在检测故障过程 会跳变 
    使用 Srvl_Tle9210x_GetWaitOffStateDiag 则不能会存在此问题 */
    return s_SrvlTle9210x_OffStateErr[Num][HbCh];
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetWaitOffStateDiag
 * @description: 诊断完成后的故障状态
 * @input parameters: Num:芯片号 HbCh半桥通道号
 * @output parameters: enTLE9210x_OffStateErrType
 * @return: enTLE9210x_OffStateErrType:关故障确认状态
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
 * @description: 芯片主处理函数
 * @input parameters: void
 * @output parameters: void
 * @return: void
 * @note:
 * @author: czy
 * @date: 2025.04.28
 ***********************************************************************/
void Srvl_Tle9210x_MainCycleFunction(void)
{
    Srvl_Tle9210x_FeedWdg();                    /* 喂狗 */
    Srvl_Tle9210x_OffStateDiagnostic();         /* 关闭状态诊断 */
    Srvl_Tle9210x_ResetChipControlFunc();       /* 芯片复位检测 */
    Srvl_Tle9210x_TempVoltageErrStsFunc();      /* 过温 过压 过流 */
    Srvl_Tle9210x_DrainSourceVolErrStsFunc();   /* 漏源过压 */
//    Srvl_Tle9210x_StatusReg_UpdateCycle();      /* 获取状态寄存器 - 后续删除 */
    Srvl_Tle9210x_PWM4EnCheckReset();           /* 若打开PWM4 则检测是否中途复位 */
    Srvl_Tle9210x_Test();
}

/***********************************************************************
 * @function name: Srvl_Tle9210x_GetTempSts
 * @description: 获取芯片温度状态 - TjW阈值=140度  Tjsd阈值=180度
 * @input parameters: Num:芯片号
 * @output parameters: enTLE9210x_TempStsType
 * @return: enTLE9210x_TempStsType:温度故障状态
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
 * @description: 获取芯片安全故障-多次尝试恢复失败 
 * @input parameters: Num:芯片号
 * @output parameters: INT8U
 * @return: INT8U:芯片初始化故障状态
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
 * @description: 获取调节过程中出现漏源故障 
 * @input parameters: Num:芯片号 HbxCh:半桥通道
 * @output parameters: enTLE9210x_DrainSErrType
 * @return: enTLE9210x_DrainSErrType:漏源故障状态
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
 * @description: 获取初始化状态 
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
 * @description: 获取VM状态
 * @input parameters: Num:芯片号 
 * @output parameters: enTLE9210x_VMStsType
 * @return: s_SrvlTle9210x_VMStsErr:vm故障状态
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
 * @description: 获取充电泵状态 
 * @input parameters: Num:芯片号  
 * @output parameters: INT8U
 * @return: s_SrvlTle9210x_ChargePumpUnderVStsErr:充电泵状态
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
 * @description: PWM4开启 获取读芯片数据故障状态 
 * @input parameters: Num:芯片号 
 * @output parameters: INT8U
 * @return: s_SrvlTle9210x_DataReadErr:pwm4数据异常
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
 * @description: 喂狗状态 
 * @input parameters: Num:芯片号 
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
 * @description: 故障停止 
 * @input parameters: enTLE9210x_SeatDrvtype 座椅驱动
 * @output parameters: enTLE9210x_MotorErrStsType 停止原因
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

    if(SetMotor >= EN_SEAT_DRV_MAX)//超值
    {
        return EN_TLE9210X_ERR_NONE;
    }

    if(Num[SetMotor] >= EN_TLE9210X_NUM_MAX)//超值
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
 * @description: 测试
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
        /* 根据手册DR7808Q - 6.8.3示例 */
        /* 设置HBxMODE=00b -> 设置PWMx_HB到对应通道,使能PWM_EN -> 设置通道输出方向 */
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

