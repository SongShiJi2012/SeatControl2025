/*
 * Srvl_E2cfg.h
 * 配置E2长度与地址以及对应RAM相关结构体
 *  Created on: 2025-3-20
 *      Author: Administrator
 */

#ifndef SRVL_E2CFG_H_
#define SRVL_E2CFG_H_

#include  "Common.h"

/*
Eeprom起始地址: 0x0u
Eeprom长度: 2*1024 bytes = 2048 bytes
Eeprom结束地址: 0x7FFu


存储数据起始地址: 0x0u
存储数据空间: 0x0u~0x3FF 		0x400bytes = 1024bytes
存储数据结束地址: 0x3FF

APP相关固定地址：0x0~0x2FF
BOOT相关固定地址：0x300~0x3FF

备份E2PROM起始地址: 0x400
备份存储数据空间: 0x400~0x7FF 	0x400bytes = 1024bytes
备份存储数据结束地址: 0x7FF

备份APP相关固定地址：0x400~0x6FF
备份BOOT相关固定地址：0x300~0x7FF
*/

/*--------------------------DSM Data Address cfg 通用 ------------------------------------*/
#define	EEPROM_ADDRESS											(0x0u) 	 	/*总EEPROM起始地址*/
#define	EEPROM_APP_ADDRESS										(0x0u) 		/*APP使用 EEPROM起始地址*/
#define	EEPROM_BOOT_ADDRESS										(0x300u)   	/*BOOT使用 EEPROM起始地址*/
#define	BACKUP_ADDRESS_OFFSIZE									(0x0400u)	/*备份E2PROM的偏移*/
#define	NEED_PAGE_NUM(len)										((len)+1u+4u) /*数据实际长度+校验和(1byte)+冗余(4bytes)*/

/*--------------------------APP Data Address ------------------------------------*/
#define    E2PROM_INIT_APP_ADDRESS				(EEPROM_APP_ADDRESS + 0)/*app是否为第一次上电运行的标识的地址 在app判断 boot不处理*/
#define    ECUSERIAL_ADDRESS					(E2PROM_INIT_APP_ADDRESS + E2PROM_INIT_APP_LEN)//14000040
#define    TESTID_ADDRESS						(ECUSERIAL_ADDRESS + NEED_PAGE_NUM(ECUSERIAL_LEN))//14000053
#define	   PIN_ANTI_ATTACK_ADDRESS				(TESTID_ADDRESS + NEED_PAGE_NUM(TESTID_LEN))//14000059
#define    PARTNUMBER_ADDRESS					(PIN_ANTI_ATTACK_ADDRESS + NEED_PAGE_NUM(PIN_ANTI_ATTACK_LEN))//1400005F
#define    VMF_SWNUMBER_ADDRESS 				(PARTNUMBER_ADDRESS + NEED_PAGE_NUM(PARTNUMBER_LEN))//14000078
#define    VMF_SWVERNUMBER_ADDRESS 				(VMF_SWNUMBER_ADDRESS + NEED_PAGE_NUM(VMF_SWNUMBER_LEN))//14000085
#define	   REPAIRSHOPCODE_ADDRESS				(VMF_SWVERNUMBER_ADDRESS + NEED_PAGE_NUM(VMF_SWVERNUMBER_LEN))//1400008C
#define	   PROGRAMMINGDATE_ADDRESS			    (REPAIRSHOPCODE_ADDRESS + NEED_PAGE_NUM(REPAIRSHOPCODE_LEN))//14000099
#define	   ECUINSTALLDATE_ADDRESS				(PROGRAMMINGDATE_ADDRESS + NEED_PAGE_NUM(PROGRAMMINGDATE_LEN))//140000A2
#define	   BOOTSWNUMBER_ADDRESS					(ECUINSTALLDATE_ADDRESS + NEED_PAGE_NUM(ECUINSTALLDATE_LEN))//140000AB
#define	   BOOTSWVER_ADDRESS					(BOOTSWNUMBER_ADDRESS + NEED_PAGE_NUM(BOOTSWNUMBER_LEN))//1400000Be
#define	   PRODUCTNO_ADDRESS					(BOOTSWVER_ADDRESS + NEED_PAGE_NUM(BOOTSWVER_LEN))//140000C8
#define    PIN_ADDRESS                          (PRODUCTNO_ADDRESS  + NEED_PAGE_NUM(PRODUCTNO_LEN))//140000D7
#define    MEMORY_ADDRESS                       (PIN_ADDRESS  + NEED_PAGE_NUM(PIN_LEN))//140000E0
#define    MEMSET_ADDRESS                       (MEMORY_ADDRESS  + NEED_PAGE_NUM(MEMORY_LEN))//1400010F
#define    LOCKED_ADDRESS                       (MEMSET_ADDRESS  + NEED_PAGE_NUM(MEMSET_LEN))//14000115
#define    EEPROMCHANGEGLG_ADDRESS              (LOCKED_ADDRESS  + NEED_PAGE_NUM(LOCKED_LEN))//1400011B
#define    MOTERRUNMAXTIME_ADDRESS             (EEPROMCHANGEGLG_ADDRESS  + NEED_PAGE_NUM(EEPROMCHANGEGLG_LEN))//14000121
#define    ERVMSEEGROUDPOSI_ADDRESS            (MOTERRUNMAXTIME_ADDRESS  + NEED_PAGE_NUM(MOTERRUNMAXTIME_LEN))//14000133
#define    SoftStopCnt_ADDRESS             (ERVMSEEGROUDPOSI_ADDRESS  + NEED_PAGE_NUM(ERVMSEEGROUDPOSI_LEN))//14000140
#define    VIN_ADDRESS							(SoftStopCnt_ADDRESS + NEED_PAGE_NUM(SoftStopCnt_LEN))//1400014E
#define    VehicleFuncConfig_ADDRESS            (VIN_ADDRESS + NEED_PAGE_NUM(VIN_LEN))//14000164
#define    VehicleNetworkConfig_ADDRESS		(VehicleFuncConfig_ADDRESS + NEED_PAGE_NUM(VehicleFuncConfig_LEN))//14000173
#define    CFGIDSeatPositionMemory_ADDRESS	(VehicleNetworkConfig_ADDRESS + NEED_PAGE_NUM(VehicleNetworkConfig_LEN))
#define    RSVD_ADDRESS                         (CFGIDSeatPositionMemory_ADDRESS  + NEED_PAGE_NUM(CFGIDSeatPositionMemory_LEN))
#define    DTC_ADDRESS							(RSVD_ADDRESS + NEED_PAGE_NUM(RSVD_LEN))//140001B2
#define    ECUSERIAL1_ADDRESS					(DTC_ADDRESS + NEED_PAGE_NUM(DTC_LEN))//14000214
#define    PARTNUMBER1_ADDRESS					(ECUSERIAL1_ADDRESS + NEED_PAGE_NUM(ECUSERIAL1_LEN))//14000229
#define    PROGRAMMINGDATE1_ADDRESS				(PARTNUMBER1_ADDRESS + NEED_PAGE_NUM(PARTNUMBER1_LEN))//14000237
#define    SWADHESION_ADDRESS				(PROGRAMMINGDATE1_ADDRESS + NEED_PAGE_NUM(PROGRAMMINGDATE1_LEN))//14000242
#define    BLEIDMEMORY_ADDRESS                (SWADHESION_ADDRESS  + NEED_PAGE_NUM(SWADHESION_LEN))//14000248
#define    BLEIDMEMSET_ADDRESS                (BLEIDMEMORY_ADDRESS  + NEED_PAGE_NUM(BLEIDMEMORY_LEN))//14000277
#define    SOFA_LEARN_ADDRESS                	(BLEIDMEMSET_ADDRESS  + NEED_PAGE_NUM(BLEIDMEMSET_LEN))
#define    ONECLICKMEMORY_ADDRESS                	(SOFA_LEARN_ADDRESS  + NEED_PAGE_NUM(SOFA_LEARN_LEN))
#define    ONECLICKMEMSET_ADDRESS                	(ONECLICKMEMORY_ADDRESS  + NEED_PAGE_NUM(ONECLICKMEMORY_LEN))
#define    CampingExit_ADDRESS                	(ONECLICKMEMSET_ADDRESS  + NEED_PAGE_NUM(ONECLICKMEMSET_LEN))
#define    D_BTS70X0_MEM_ADDRESS          (CampingExit_ADDRESS + NEED_PAGE_NUM(CampingExit_LEN))

#define	   D_PCBASN_ADDRESS										(D_BTS70X0_MEM_ADDRESS + NEED_PAGE_NUM(D_BTS70X0_MEM_LEN))
#define    D_HARDWARE_CFG_ADDRESS				(D_PCBASN_ADDRESS + NEED_PAGE_NUM(D_PCBASN_LEN))
#define    DOORSTATE_ADDRESS                    (D_HARDWARE_CFG_ADDRESS + NEED_PAGE_NUM(D_HARDWARE_CFG_LEN))

#define	   E2PROM_DATA_END_ADDRESS				(DOORSTATE_ADDRESS + NEED_PAGE_NUM(DOORSTATE_LEN))//1400027D

/* BackUp Address */
#define    BACKUP_MEMORY_ADDRESS                                (BACKUP_ADDRESS_OFFSIZE  + 0)
#define    BACKUP_HARDWARE_CFG_ADDRESS                          (BACKUP_MEMORY_ADDRESS  + MEMORY_LEN)

/*--------------------------BOOT Data Address 以下配置app与boot需相同  直接复制------------------------------------*/
#define    D_E2PROM_INIT_BOOT_ADDRESS				(EEPROM_BOOT_ADDRESS + 0) /*boot是否为第一次上电运行的标识的地址 在boot判断 app不处理*/
#define    D_FromAppJumpToBootFlg_Addr              (D_E2PROM_INIT_BOOT_ADDRESS + NEED_PAGE_NUM(D_E2PROM_INIT_BOOT_Len))/*APP跳boot标志*/
#define    D_E2promAppCodeValidFlg_Addr             (D_FromAppJumpToBootFlg_Addr + NEED_PAGE_NUM(D_FromAppJumpToBootFlg_Len))/*APP是否有效标志*/
#define    D_DARE_APP_VER_ADDR              		(D_E2promAppCodeValidFlg_Addr + NEED_PAGE_NUM(D_E2promAppCodeValidFlg_Len))
#define    D_DARE_BOOT_VER_ADDR              		(D_DARE_APP_VER_ADDR + NEED_PAGE_NUM(D_DARE_APP_VER_LEN))
#define    D_BootPINAntiAttack_Addr			        (D_DARE_BOOT_VER_ADDR + NEED_PAGE_NUM(D_DARE_BOOT_VER_LEN))
#define    D_FingerPrint_Addr                       (D_BootPINAntiAttack_Addr + NEED_PAGE_NUM(D_BootPINAntiAttack_Len))
#define    D_WAKE_UP_ADDR                   		(D_FingerPrint_Addr + NEED_PAGE_NUM(D_FingerPrint_Len))
#define    D_OTA_MODE_ADDR                   		(D_WAKE_UP_ADDR + NEED_PAGE_NUM(D_WAKE_UP_LEN))
#define    D_CUST_APP_VER_ADDR              		(D_OTA_MODE_ADDR + NEED_PAGE_NUM(D_OTA_MODE_LEN))
#define    D_CUST_BOOT_VER_ADDR              		(D_CUST_APP_VER_ADDR + NEED_PAGE_NUM(D_CUST_APP_VER_LEN))

#define    D_BOOT_DATA_END_ADDR              		(D_CUST_BOOT_VER_ADDR + NEED_PAGE_NUM(D_CUST_BOOT_VER_LEN))

/*长度定义*/
#define				E2PROM_INIT_APP_LEN								4
#define             ECUSERIAL_LEN                                   14
#define             PARTNUMBER_LEN                                  (20u)
#define				PIN_ANTI_ATTACK_LEN								1
#define				VMF_SWNUMBER_LEN								8
#define				VMF_SWVERNUMBER_LEN								2
#define				SYSTEM_SUPPLIER_ECUHWNUMBER_LEN					14
#define				SYSTEM_SUPPLIER_ECUHWVERSION_LEN				2
#define				SYSTEM_SUPPLIER_ECUSWNUMBER_LEN					14
#define				SYSTEM_SUPPLIER_ECUSWVERSION_LEN				2
#define				SYSTEMNAME_LEN									4
#define				REPAIRSHOPCODE_LEN								8
#define				PROGRAMMINGDATE_LEN								4
#define				ECUINSTALLDATE_LEN								4
#define				BOOTSWNUMBER_LEN								14
#define				BOOTSWVER_LEN									5
#define				PRODUCTNO_LEN									10
#define             TESTID_LEN                                     	1
#define             PIN_LEN                                     	4
#define             RSVD_LEN                                     	2
#define				MEMORY_LEN										((MemSaveItem) * (EN_MEM_POSI_MAX))
#define				MEMSET_LEN										1
#define				LOCKED_LEN										1
#define     		EEPROMCHANGEGLG_LEN           					1
#define     		MOTERRUNMAXTIME_LEN           					13
#define     		ERVMSEEGROUDPOSI_LEN           					8
#define     		SoftStopCnt_LEN           					9
#define             VIN_LEN                                     	17
#define             VehicleFuncConfig_LEN                         	2
#define             VehicleNetworkConfig_LEN					   	4
#define				BLEIDMEMORY_LEN							    	((MemSaveItem) * (EN_MEM_IDPOSI_MAX))
#define				BLEIDMEMSET_LEN									1
#define             CFGIDSeatPositionMemory_LEN                     1

#define				SOFA_LEARN_LEN									1
#define				ONECLICKMEMORY_LEN							((MemSaveItem) * (EN_MEM_POSI_NUM))
#define				ONECLICKMEMSET_LEN							1
#define				CampingExit_LEN								1
#define             D_BTS70X0_MEM_LEN                               (4)
#define             D_PCBASN_LEN                                 	(21)
#define 			D_HARDWARE_CFG_LEN								(2)
#define             DOORSTATE_LEN                                   (1u)

#define				DTC_NUM											(eDTC_MAX)
#ifdef DSMDiag_mgSNAPSHOT_RECORD
#define             DTC_LEN											(DTC_NUM*(3u+9u)) /**/
#else
#define             DTC_LEN											(DTC_NUM*(3u)) /**/
#endif
#define             ECUSERIAL1_LEN                                   16
#define             PARTNUMBER1_LEN                                 (9u)
#define				PROGRAMMINGDATE1_LEN 						     6
#define             SWADHESION_LEN									 1

//以下配置app与boot需相同  直接复制
#define     		E2PROM_INIT_BOOT_LEN      			(4u)
#define     		D_E2PROM_INIT_BOOT_Len      		(4u)
#define     		D_FromAppJumpToBootFlg_Len      	(1u)
#define     		D_E2promAppCodeValidFlg_Len     	(8u)
#define     		D_DARE_APP_VER_LEN      			(10u)
#define     		D_DARE_BOOT_VER_LEN      			(10u)
#define     		D_BootPINAntiAttack_Len         	(1)
#define     		D_FingerPrint_Len               	(9)
#define     		D_WAKE_UP_LEN      					(1u)
#define     		D_OTA_MODE_LEN      		    	(1u)
#define     		D_CUST_APP_VER_LEN      			(4u)
#define     		D_CUST_BOOT_VER_LEN      			(10u)

typedef struct
{
    INT8U Reserved0                                  :2;
    INT8U PinRecogOnPendingEnable                    :1;			//保护标示
    INT8U PinAntiAttackEnable                        :1;			//是否需要10s保护时间
    INT8U PinAttackCnt                               :4;			//记录尝试次数
}AppEE_stPinAntiAttackstBits;
typedef union
{
    INT8U Byte;
    AppEE_stPinAntiAttackstBits Bits;
}AppEE_unPinAntiAttackst;


typedef struct
{
    INT8U  	SeatHeightLocked            	  :1;	//硬止点堵转标志
    INT8U   SeatLengthLocked                  :1;
    INT8U   SeatBackrestLocked                :1;
    INT8U   SeatFrontHeightLocked             :1;
    INT8U   SeatHeadrestLocked                :1;
    INT8U   SeatCushionLengthLocked           :1;
    INT8U   WheelHeightLocked                 :1;
    INT8U   WheelLengthLocked                 :1;
}AppEE_stLockedRotorBits;

typedef union
{
    INT8U Byte;
    AppEE_stLockedRotorBits Bits;
}AppEE_unLockedRotorBits;

typedef struct
{
    INT8U  	SWHeightAdhesion            	 :1;	//开关粘连标志
    INT8U   SWLengthAdhesion                 :1;
    INT8U   SWBackreAdhesion                 :1;
    INT8U   SWRightLfRtAdhesion              :1;
    INT8U   SWRightUpDnAdhesion              :1;
    INT8U   SWLeftLfRtAdhesion               :1;
    INT8U   SWLeftUpDnAdhesion               :1;
    INT8U   reserved                 		 :1;
}AppEE_SWadhesionErrBits;

typedef union
{
    INT8U Byte;
    AppEE_SWadhesionErrBits Bits;
}AppEE_unSWadhesionErr;

typedef struct
{
    INT8U  	MemSet1fg            	:1;	//记忆档位已设置完成标志
    INT8U   MemSet2fg               :1;
    INT8U   MemSet3fg               :1;
    INT8U   MemSet4fg             	:1;
    INT8U   MemSet5fg               :1;
    INT8U   MemSet6fg           	:1;
    INT8U   SeatComfortBWtfg      	:1;//座椅舒适后移功能开始标志
    INT8U   ERVMSeeGroudfg          :1;//后视镜自动下翻开启标志
}AppEE_stMemSetBits;

typedef union
{
    INT8U Byte;
    AppEE_stMemSetBits Bits;
}AppEE_unMemSetBits;

typedef struct
{
    INT8U  	MemBLEIDSet1fg            	:1;	//记忆档位已设置完成标志
    INT8U   MemBLEIDSet2fg              :1;
    INT8U   MemBLEIDSet3fg              :1;
    INT8U   MemBLEIDSet4fg             	:1;
    INT8U   MemBLEIDSet5fg              :1;
    INT8U   MemBLEIDSet6fg           	:1;
	INT8U   Reserved                	:2;
}AppEE_stBLEIDMemSetBits;

typedef union
{
    INT8U Byte;
    AppEE_stBLEIDMemSetBits Bits;
}AppEE_unBLEIDMemSetBits;

typedef struct
{
    INT8U  	MemCampSet4fg            	:1;	//记忆档位已设置完成标志
    INT8U   MemCampSet5fg              :1;
    INT8U   MemCampSet6fg              :1;
    INT8U   MemCampSetTemp              :1;
	INT8U   Reserved                	:4;
}AppEE_stCampMemSetBits;

typedef union
{
    INT8U Byte;
    AppEE_stCampMemSetBits Bits;
}AppEE_unCampMemSetBits;

typedef enum
{
    EN_APPEE_CAMPSTS_NONE,
    EN_APPEE_CAMPSTS_CAMPING,    /* 进入一键露营 */
    EN_APPEE_CAMPSTS_MODE_NAP,   /* 已在打盹模式 */
    EN_APPEE_CAMPSTS_MODE_RESET, /* 已在小憩模式 */
    EN_APPEE_CAMPSTS_MODE_CINEMA, /* 已在娱乐包房模式 */
    EN_APPEE_CAMPSTS_MODE_GAME, /* 已在游戏模式*/
    EN_APPEE_CAMPSTS_MAX
}AppEE_unCampSts;

typedef struct
{
	INT16U	SeatHeightPosi;			/*座椅高度*/
	INT16U	SeatLengthPosi;
	INT16U	SeatBackrestPosi;
}AppEE_ST_MemoryInfo;

#define MemSaveItem    		(sizeof(AppEE_ST_MemoryInfo) / sizeof(INT8U))/*it need adjust when the above struct member change*/
#define MotorNumber    		(3u)/*it need adjust when the above struct member change*/
#define MotorBLEIDNumber  	(6u)/*it need adjust when the above struct member change*/


typedef enum
{
    EN_HW_NTC, /* NTC 硬件配置 */
    EN_HW_RES, /* 预留配置 */
    EN_HW_MAX,
}en_HardWareType;

typedef enum
{
    EN_NTC_OLD, /* NTC旧配置 */
    EN_NTC_NEW, /* NTC新配置 */
    EN_NTC_MAX,
}en_NtcHardWareType;

typedef enum
{
	EN_MEM_POSI1 = 0,
	EN_MEM_POSI2,
	EN_MEM_POSI3,
	EN_MEM_POSI4,
	EN_COMFORT_POSI,
	EN_REAL_TIME_POSI,
	EN_STOP_POSI,

	EN_MEM_POSI_MAX,
}EN_MEM_STORAGE_POSI;

typedef enum
{
	EN_MEM_ONECLICKPOSI4 = 0,
	EN_MEM_ONECLICKPOSI5,
	EN_MEM_ONECLICKPOSI6,
	EN_MEM_ONECLICKPOSITemp,

	EN_MEM_POSI_NUM,
}EN_MEM_ONECLICK_POSI;


typedef enum
{
    EN_MEM_POSI_ID0 = 0,//当前位置
	EN_MEM_POSI_ID1,
	EN_MEM_POSI_ID2,
	EN_MEM_POSI_ID3,
	EN_MEM_POSI_ID4,
	EN_MEM_POSI_ID5,
	EN_MEM_POSI_ID6,

	EN_MEM_IDPOSI_MAX,
}EN_MEM_STORAGE_IDPOSI;
typedef   enum
{
	enSeatHeight = 0,
	enSeatLength,
	enSeatBackrest,
	enSeatFrontHeight,
	enSeatHeadrest,
	enSeatCushionLength,

	enWheelHeight,
	enWheelLength,

	enERVM_Mirror,
	enSeatDRHeat,
	enSeatPAHeat,
	enSeatDRVen,
	enSeatPAVen,

	enTimeMax,
}EN_MAX_TIME;

typedef enum
{
	enERVM_L_MIRROR_LR_Posi_H = 0,
	enERVM_L_MIRROR_LR_Posi_L,
	enERVM_L_MIRROR_UD_Posi_H,
	enERVM_L_MIRROR_UD_Posi_L,
	enERVM_R_MIRROR_LR_Posi_H,
	enERVM_R_MIRROR_LR_Posi_L,
	enERVM_R_MIRROR_UD_Posi_H,
	enERVM_R_MIRROR_UD_Posi_L,

	enERVMPosiMax,
}EN_ERVM_SEE_GROUD_POSI;

typedef enum
{
	enSoftStopCntHeight = 0,    //高度电机到达软停止点的次数
	enSoftStopCntLength,       	//纵向电机到达软停止点的次数
	enSoftStopCntBack,       	//椅背电机到达软停止点的次数
	enSoftStopCntFront,       	//腿托电机到达软停止点的次数
	enSoftStopCntMaxTimes, 		//电机软停止点重置次数
	enMotor_ButtonErr_Time, 	//按键连续按下的时间

	enSoftStopCntMax,
}EN_SOFTSTOPCNT;



typedef struct
{
    INT8U  	ComfortEnablefg         :1;
    INT8U   CFG_ID_Seat_Position_Memory:1;
    INT8U   HeatEnableFlg                :1;//加热使能配置
    INT8U   VentEnableFlg                :1;//通风使能配置
    INT8U   Reserved1             	:4;
}AppEE_STVehicleFuncConfigBits;

typedef union
{
	INT8U Byte;
	AppEE_STVehicleFuncConfigBits Bits;
}AppEE_UNVehicleFuncByte0;

typedef struct
{
	AppEE_UNVehicleFuncByte0 AppEE_unVehicleFuncByte0;
    INT8U ResvdByte1;

}AppEE_STVehicleFuncConfig;



typedef struct
{
	 INT8U ResvdByte0;
	 INT8U ResvdByte1;
	 INT8U ResvdByte2;
	 INT8U ResvdByte3;
}AppEE_STVehicleNetworkConfig;


#endif /* SRVL_E2CFG_H_ */
