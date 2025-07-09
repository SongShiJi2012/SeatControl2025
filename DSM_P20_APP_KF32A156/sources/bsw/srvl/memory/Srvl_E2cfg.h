#ifndef SRVL_E2CFG_H_
#define SRVL_E2CFG_H_
#include  "Common.h"

/*--------------------------DSM Data Address cfg 通用 ------------------------------------*/
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

typedef  enum
{
	E2promNull_Index           = 0,	/* 0 */
	PIN_ANTI_ATTACK_INDEX,			/* 3 */
	DTC_INDEX,						/* 25 */
	FromAppJumpToBootFlg_Index,
	//客户需求相关
	WakeUpSource_Index,

	E2promItem_Number,				/* 42 */
} enE2promIndex;
//PIN Anti-Attack
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

typedef    struct
{
	AppEE_unPinAntiAttackst				PINAnti_Attack;
	INT8U                               PartNumber[PARTNUMBER_LEN];
	INT8U								RepairShopCode[REPAIRSHOPCODE_LEN];				//维修点代码
	INT8U                              *DTCE2promBuff;
	INT8U                               PartNumber1[PARTNUMBER1_LEN];
	// 与boot共用区域
	INT8U       FromAppJumpToBootFlg;
	INT8U       DareBootVersion[D_DARE_BOOT_VER_LEN];
	AppEE_unPinAntiAttackst BootPINAnti_Attack;
	INT8U       WakeUpSource;
	INT8U       CustomerBootVersion[D_CUST_BOOT_VER_LEN];
} stCarE2promInfo;
#endif /* SRVL_E2CFG_H_ */
