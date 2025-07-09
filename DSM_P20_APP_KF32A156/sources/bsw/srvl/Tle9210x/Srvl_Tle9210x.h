#ifndef _SRVL_TLE9210x_H_            
#define _SRVL_TLE9210x_H_

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "TLE9210x_FuncLayer.h"
#include "TLE9210x_HAL.h"
#include "pins_driver.h"
#include "Common.h"


/*************************************************************************************************
 * Macro definition
 *************************************************************************************************/

/* ��ʼ��ֵ */
//#define D_RVL_TLE9210x_1_C_GENCTRL1_0_INIT                 (0x0123)//���� 10V/V
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT                 (0x0322)
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT                 (0x2523)//���� 20V/V
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT                 (0x2722)
#define D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT                 (0x4923)//���� 40V/V
#define D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT                 (0x4B22)
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT                 (0x6D23)//���� 80V/V
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT                 (0x6F22)
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_0_INIT                 (0x6D23)//���� 80V/V -OC���ж�
//#define D_SRVL_TLE9210x_1_C_GENCTRL1_1_INIT                 (0x6F22)

#define D_SRVL_TLE9210x_1_C_GENCTRL2_INIT                   (0x033f)//tFVDS:�˲�ʱ�� fae�Ƽ�3us
#define D_SRVL_TLE9210x_1_C_VDS1_INIT                       (0x0B6D)
#define D_SRVL_TLE9210x_1_C_VDS2_INIT                       (0x0B6D)
#define D_SRVL_TLE9210x_1_C_CCP_BLK1_INIT                   (0x0000)
#define D_SRVL_TLE9210x_1_C_HBMODE_INIT                     (0x0000)
#define D_SRVL_TLE9210x_1_C_CCP_BLK2_ACT_INIT               (0x4B28)//����ʱ��375ns�����հ�3us-DR7808����Ӧ��Ӣ������Ҫȷ������ʱ�䡣
#define D_SRVL_TLE9210x_1_C_CCP_BLK2_FW_INIT                (0x4B28)
#define D_SRVL_TLE9210x_1_C_PWMSET_INIT                     (0x6C60)
#define D_SRVL_TLE9210x_1_C_TPRECHG_INIT                    (0x0000)
#define D_SRVL_TLE9210x_1_C_HBIDIAG_INIT                    (0xFC00)
#define D_SRVL_TLE9210x_1_C_ST_ICHG_INIT                    (0x00AA)//�ߵͲ��л��ĳ�ŵ����
#define D_SRVL_TLE9210x_1_C_PWM_PCHG_INIT_INIT              (0x18C6)
#define D_SRVL_TLE9210x_1_C_PWM_ICHG_ACT_INIT               (0x39CE)
#define D_SRVL_TLE9210x_1_C_PWM_ICHG_FW_INIT                (0x39CE)
#define D_SRVL_TLE9210x_1_C_PWM_IDCHG_ACT_INIT              (0x39CE)
#define D_SRVL_TLE9210x_1_C_PWM_PDCHG_INIT_INIT             (0x318C)
#define D_SRVL_TLE9210x_1_C_PWM_ICHGMAX_CCP_BLK3_ACT_INIT   (0x5940)//pwm��ŵ��С�ᵼ�²��ηǾ���
#define D_SRVL_TLE9210x_1_C_PWM_ICHGMAX_CCP_BLK3_FW_INIT    (0x5940)
#define D_SRVL_TLE9210x_1_C_PWM_TDON_OFF1_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_1_C_PWM_TDON_OFF2_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_1_C_PWM_TDON_OFF3_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_1_C_DRV_LPWR_EN_INIT                (0x8200)


#define D_SRVL_TLE9210x_2_C_GENCTRL1_0_INIT                 (0x4923)//���� 40V/V
#define D_SRVL_TLE9210x_2_C_GENCTRL1_1_INIT                 (0x4B22)
#define D_SRVL_TLE9210x_2_C_GENCTRL2_INIT                   (0x033f)
#define D_SRVL_TLE9210x_2_C_VDS1_INIT                       (0x0B6D)
#define D_SRVL_TLE9210x_2_C_VDS2_INIT                       (0x0B6D) //92104�����ô�
#define D_SRVL_TLE9210x_2_C_CCP_BLK1_INIT                   (0x0000)
#define D_SRVL_TLE9210x_2_C_HBMODE_INIT                     (0x0000)
#define D_SRVL_TLE9210x_2_C_CCP_BLK2_ACT_INIT               (0x4B28)
#define D_SRVL_TLE9210x_2_C_CCP_BLK2_FW_INIT                (0x4B28)
#define D_SRVL_TLE9210x_2_C_PWMSET_INIT                     (0x6C60)
#define D_SRVL_TLE9210x_2_C_TPRECHG_INIT                    (0x0000)
#define D_SRVL_TLE9210x_2_C_HBIDIAG_INIT                    (0xFC00)
#define D_SRVL_TLE9210x_2_C_ST_ICHG_INIT                    (0x00AA)
#define D_SRVL_TLE9210x_2_C_PWM_PCHG_INIT_INIT              (0x18C6)
#define D_SRVL_TLE9210x_2_C_PWM_ICHG_ACT_INIT               (0x39CE)
#define D_SRVL_TLE9210x_2_C_PWM_ICHG_FW_INIT                (0x39CE)
#define D_SRVL_TLE9210x_2_C_PWM_IDCHG_ACT_INIT              (0x39CE)
#define D_SRVL_TLE9210x_2_C_PWM_PDCHG_INIT_INIT             (0x318C)
#define D_SRVL_TLE9210x_2_C_PWM_ICHGMAX_CCP_BLK3_ACT_INIT   (0x5940)
#define D_SRVL_TLE9210x_2_C_PWM_ICHGMAX_CCP_BLK3_FW_INIT    (0x5940)
#define D_SRVL_TLE9210x_2_C_PWM_TDON_OFF1_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_2_C_PWM_TDON_OFF2_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_2_C_PWM_TDON_OFF3_INIT              (0x0A0A)
#define D_SRVL_TLE9210x_2_C_DRV_LPWR_EN_INIT                (0x8200)

/*PWM Channel*/
typedef enum
{
	TLE9210x_PWM1 = 0,
	TLE9210x_PWM2,
	TLE9210x_PWM3,
	TLE9210x_PWM4,
	TLE9210x_PWMChMAX
}enTLE9210x_PWMCh;
/*HB Channel*/
typedef enum
{
	TLE9210x_HB1 = 0,
	TLE9210x_HB2,
	TLE9210x_HB3,
	TLE9210x_HB4,
	TLE9210x_HB5,
	TLE9210x_HB6,
	TLE9210x_HB7,
	TLE9210x_HB8,
	TLE9210x_HBChMAX
}enTLE9210x_HBCh;

typedef enum
{
	TLE9210x_OFF = 0,
	TLE9210x_ForRot,
	TLE9210x_RevRot,
	TLE9210x_Brake,
	TLE9210x_ModeMAX
}enTLE9210x_ControlMode;

typedef enum
{
	EN_MotorDrive_0 = 0,
	EN_MotorDrive_1,
	EN_MotorDrive_2,
	EN_MotorDrive_3,
	EN_MotorDrive_MAX,
}enTLE9210x_MotorDriveIndex;

typedef enum
{
    EN_SEAT_DRV_HEIGHT,
    EN_SEAT_DRV_LENGTH,
    EN_SEAT_DRV_BACK,
    EN_SEAT_DRV_FRONT,
    EN_SEAT_PAS_LENGTH,
    EN_SEAT_PAS_BACK,
    EN_SEAT_DRV_MAX,
    EN_SEAT_PAS_HEIGHT,
    EN_SEAT_PAS_FRONT,
}enTLE9210x_SeatDrvtype;

typedef enum
{
	EN_CHIP_TLE92104 = 0,
	EN_CHIP_TLE92108,
	EN_CHIP_MAX
}enTLE9210x_ChipNO;

typedef enum
{
    EN_STSREG_GENSTAT,
    EN_STSREG_DSOV,
    EN_STSREG_HBVOUT_PWMERR,
    EN_STSREG_EFF_TDON_OFF1,
    EN_STSREG_EFF_TDON_OFF2,
    EN_STSREG_EFF_TDON_OFF3,
    EN_STSREG_TRISE_FALL3,
    EN_STSREG_TRISE_FALL1,
    EN_STSREG_TRISE_FALL2,
    EN_STSREG_GDF,
    //EN_STSREG_DEVID,/*��ȡоƬ���� */
    EN_STSREG_MAX,
}enTLE9210x_StsRegType;
    
typedef enum
{
    EN_OFF_STATE_STEP_NONE,        //��ʼ
    EN_OFF_STATE_STEP_OPEN_LOAD,   //���и��ؿ�·���
    EN_OFF_STATE_STEP_TO_BATTERY,  //���жԵ�Դ��·���
    EN_OFF_STATE_STEP_TO_GROUND,   //���жԵض�·���
    EN_OFF_STATE_STEP_WAIT,        //�ȴ��´μ��
    EN_OFF_STATE_STEP_MAX,
}enTLE9210x_OffStateStepType;
    
typedef enum
{
    EN_OFF_STATE_ERR_NONE,        //��ʼ
    EN_OFF_STATE_ERR_TO_GROUND,   //���жԵض�·
    EN_OFF_STATE_ERR_TO_BATTERY,  //���жԵ�Դ��·
    EN_OFF_STATE_ERR_OPEN_LOAD,   //���и��ؿ�·
    EN_OFF_STATE_ERR_MAX,
}enTLE9210x_OffStateErrType;
    
typedef enum
{
    EN_TLE9210X_TEMP_STS_NONE,      //�޹���
    EN_TLE9210X_TEMP_STS_WARRING,   //���¾���
    EN_TLE9210X_TEMP_STS_ERR,       //���¹ض�
    EN_TLE9210X_TEMP_STS_MAX,
}enTLE9210x_TempStsType;
    
typedef enum
{
    EN_TLE9210X_DSOV_STS_NONE,      //�޹���
    EN_TLE9210X_DSOV_STS_OVER_L,    //�ͱ߹�ѹ
    EN_TLE9210X_DSOV_STS_OVER_H,    //�߱߹�ѹ
    EN_TLE9210X_DSOV_STS_OVER_HL,   //�ߵͱ߾���ѹ
    EN_TLE9210X_DSOV_STS_MAX,
}enTLE9210x_DrainSErrType;
    
typedef enum
{
    EN_TLE9210X_VM_STS_NONE,      //�޹���
    EN_TLE9210X_VM_STS_UN,        //Ƿѹ
    EN_TLE9210X_VM_STS_OVER,      //��ѹ
    EN_TLE9210X_VM_STS_UAO,       //��ѹǷѹ
    EN_TLE9210X_VM_STS_MAX,
}enTLE9210x_VMStsType;

typedef enum
{
    EN_TLE9210X_ERR_NONE,
    EN_TLE9210X_ERR_INIT,/* оƬ��ʼ�� */
    EN_TLE9210X_ERR_SAFE,/* ��ȫ���� */
    EN_TLE9210X_ERR_VM,  /* VM�쳣*/
    EN_TLE9210X_ERR_TEMP,/* �¶��쳣 */
    EN_TLE9210X_ERR_PUMP,/* �����쳣 */
    EN_TLE9210X_ERR_DS,  /* ©Դ���� */
    EN_TLE9210X_ERR_OFF, /* ��̬���� */
    EN_TLE9210X_ERR_MAX,
}enTLE9210x_MotorErrStsType;


typedef enum
{
    EN_TLE9210X_INIT_NONE,
    EN_TLE9210X_INIT_CHIP,
    EN_TLE9210X_INIT_GENCTRL1,
    EN_TLE9210X_INIT_WD1,
    EN_TLE9210X_INIT_GENCTRL2,
    EN_TLE9210X_INIT_WD2,
    EN_TLE9210X_INIT_REG,
    EN_TLE9210X_INIT_CLE,
    EN_TLE9210X_INIT_PWM,
    EN_TLE9210X_INIT_MAX,
}enTLE9210x_InitStsType;

/*************************************************************************************************
 * Typedefs 
**************************************************************************************************/
typedef struct
{
	enTLE9210x_MotorDriveIndex Name;
	enTLE9210x_HBCh BHChx0;
	enTLE9210x_HBCh BHChx1;
	enTLE9210x_PWMCh SrcPWMCh;
}stTLE9210x_MotorDriveInfoType;

typedef struct
{
	en_TLE9210x_NumMaxType Num;
	enTLE9210x_ChipNO ChipNO;
    INT8U ChxMax;
    GPIO_Type *Enbase;
    pins_channel_type_t Enpin;
    GPIO_Type *Csbase;
    pins_channel_type_t Cspin;
    INT8U PwmSet;
}stTLE9210x_ChipInfoType;

typedef enum
{
	EN_TLE9210x_Sleep = 0,
	EN_TLE9210x_Normal,
	EN_TLE9210x_FailSafe,
	EN_TLE9210x_MAX
}enTLE9210x_OpMode;
/*************************************************************************************************
 * Global Variable declaration
 *************************************************************************************************/
/** \brief function pointer TLE9210x_fpDEVICE_setDeviceReg
*/
typedef void (*Srvl_TLE9210x_fpDEVICE_setDeviceReg)(uint16_t);

/** \brief function pointer TLE9210x_fpDEVICE_getDeviceReg
*/
typedef void (*Srvl_Tle9210x_fpDEVICE_getDeviceReg)(void);

/** \brief function pointer TLE9210x_fpDEVICE_updateRamReg
*/
typedef void (*Srvl_Tle9210x_fpDEVICE_updateRamReg)(en_TLE9210x_NumMaxType,uint16_t);

typedef uint16_t (*Srvl_Tle9210x_fpDEVICE_GetRamReg)(en_TLE9210x_NumMaxType);

/** \struct TLE9210x_sDEVICE_deviceDriver
 *  \brief Struct for Device Driver cyclic task
 */
typedef struct 
{
  uint8_t u8_deviceDriverStatus;                              /*!<  device driver status */
  uint8_t u8_deviceDriverErrorLog;                            /*!<  device driver error log */
  uint8_t u8_statusSPI;                                       /*!<  status of the SPI interface */
  uint8_t u8_SpiRx[3];                                        /*!<  content of last received SPI message */
  uint8_t u8_CrcResult;                                       /*!<  expected result for crc of last received SPI message */
  Srvl_TLE9210x_fpDEVICE_setDeviceReg fp_setReg;                   /*!<  function pointer to next set register function */
  Srvl_Tle9210x_fpDEVICE_getDeviceReg fp_getReg;                   /*!<  function pointer to next get register function */
  Srvl_Tle9210x_fpDEVICE_updateRamReg fp_updateRamReg;             /*!<  function pointer to next update RAM register function */
  uint16_t u16_setBitValue;                                   /*!<  value to be used in next set register function */
} Srvl_TLE9210x_sDEVICE_deviceDriver;

typedef struct
{
    INT8U FsErrCheckCnt;    /* FS����ȷ�ϼ��� */
    INT8U NporErrCheckCnt;  /* NPOR����ȷ�ϼ��� */
    INT8U ErrSts;       /* ����״̬ */
    INT8U ResetChipCnt; /* ���ϳ��Դ��� */
}Srvl_TLE9210x_ResetChipType;/* ��λоƬ */

extern Srvl_TLE9210x_sDEVICE_deviceDriver TLE9210x_s_deviceDriver;


/*************************************************************************************************
 * Functions define
 *************************************************************************************************/

/* SPIͨѶ */
extern void Srvl_Tle9210x_SpiMasterInit(void);
extern INT32U Srvl_Tle9210x_SpiMasterReadData(void);
extern void Srvl_Tle9210x_SpiMasterSendData(INT32U SendBuff);

/* ���ʹ�� */
extern INT16U Srvl_Tle9210x_GetDiagStatusChipRegData(en_TLE9210x_NumMaxType ChipCnt,INT8U Reg);
extern INT16U Srvl_Tle9210x_GetDiagStatusRamRegData(en_TLE9210x_NumMaxType ChipCnt,INT8U Reg);
extern enTLE9210x_OffStateErrType Srvl_Tle9210x_GetOffStateDiag(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbCh);/* ��ǰ���� */
extern enTLE9210x_OffStateErrType Srvl_Tle9210x_GetWaitOffStateDiag(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbCh);/*�����ɹ��� */

/* ״̬�ӿ� */
extern INT8U Srvl_Tle9210x_GetFailSafeSts(en_TLE9210x_NumMaxType Num);
extern INT8U Srvl_Tle9210x_GetChipInitErrSts(en_TLE9210x_NumMaxType Num);
extern enTLE9210x_VMStsType Srvl_Tle9210x_GetVMStsErr(en_TLE9210x_NumMaxType Num);
extern enTLE9210x_TempStsType Srvl_Tle9210x_GetTempSts(en_TLE9210x_NumMaxType Num);
extern INT8U Srvl_Tle9210x_GetChargePumpUnderVStsErr(en_TLE9210x_NumMaxType Num);
extern enTLE9210x_DrainSErrType Srvl_Tle9210x_GetDrainSourceErr(en_TLE9210x_NumMaxType Num,enTLE9210x_HBCh HbxCh);
extern INT8U Srvl_Tle9210x_GetDataReadErr(en_TLE9210x_NumMaxType Num);
extern INT8U Srvl_Tle9210x_GetWdFlag(en_TLE9210x_NumMaxType Num);
extern enTLE9210x_MotorErrStsType Srvl_Tle9210x_GetMotorErr(enTLE9210x_SeatDrvtype SetMotor);

/* ���ؽӿ� */
extern void Srvl_Tle9210x_Test(void);
extern void Srvl_Tle9210x_MainCycleFunction(void);
extern void Srvl_Tle9210x_Init(en_TLE9210x_NumMaxType Num);

/* ���ƽӿ� */
extern void Srvl_Tle9210x_SetSeatMotor(enTLE9210x_SeatDrvtype SeatDrv,enTLE9210x_ControlMode Control);
extern void Srvl_Tle9210x_PwmSet(en_TLE9210x_NumMaxType Num,enTLE9210x_PWMCh PwmCh,INT8U PwmEn,enTLE9210x_HBCh HBCh);
extern void Srvl_Tle9210x_SetSeatMotorPwm(enTLE9210x_SeatDrvtype SeatDrv,enTLE9210x_ControlMode Control,INT8U PwmCnt);

 /*************************************************************************************************
 * End Of File
 *************************************************************************************************/ 
#endif  /*_SRVL_TLE9210x_H_*/

