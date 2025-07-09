/************************************************************************************************
File created time : 2025-06-26 15:02:03
File Name:          Srvl_E2Cfg_Generation.h
Author:             python Script Generation
Description:        E2数据块配置定义表 - 使用excel表进行管理，不可手动修改
/************************************************************************************************/



#ifndef _PYTHONE_E2CFG_H_
#define _PYTHONE_E2CFG_H_

#include "Common.h"



/**数据块读写请求枚举**/
typedef enum _EEPROM_OPT_STA_T
{
    EN_EEPROM_STA_IDLE = 0, /*空闲*/
    EN_EEPROM_STA_WRITE,    /*写请求状态*/
    EN_EEPROM_STA_READ,     /*读请求状态*/
} EepromOptReq;

/**数据块读写结果枚举定义**/
typedef enum
{
    E2promNullOp  = 0,   /*初始化*/
    E2promWaitIDL,       /*等待操作*/
    E2promOping,         /*操作中*/
    E2promOpOK,          /*操作成功*/
    E2promOpFail,        /*操作失败*/
} enE2promOptResult;

/**数据块配置数据结构**/
typedef struct EEPROMPARATABLE
{
    INT16U             DataBlockID;         /*ID标识*/
    INT32U             StartAddr;           /*起始地址*/
    INT8U              DataLength;          /*数据长度*/
    INT16U             BackUpID;            /*备份数据标识*/
    INT8U              *pParaBuffer;        /*指向的数据*/
    EepromOptReq       OptReq;              /*读写请求状态*/
    enE2promOptResult  OptResult;           /*读写操作结果*/
    INT8U              PreWriteFlg;         /*预写入标志*/
} strEepromDataBlockCfgTable;

/**自定义存储项数据结构**/
typedef struct EE_SRV_DATA_TABLE_CFG
{
    INT16U             SrvMemIndex;     /* 自定义枚举 */
    INT8U              StartOffset;     /* 定义存储在数据块中对应RAM变量的起始偏移量 */
    INT8U              len;             /* 定义存储长度 */
    INT16U             DataBlockID;     /* 数据块ID */
} strEepromDataDefineTable;


#define    D_USEID_NUMBER                68          /* 使用ID的数量 */
#define    D_USEID_NUMBER_NO_BACKUP      34  /* 使用ID的数量 不包含备份*/
#define    D_NOBACKUP              0xFFFF      /* 无备份 */


typedef enum
{
/********数据块ID_0 定义开始********/
    #if 0
    D:APP第一次运行标志 
    #endif
    EN_MemIndex_APP_INIT_Data = 0, /* D_APP_INIT_Data_Len_4 */
    #if 0
	BOOT第一次运行标志
    #endif
    EN_MemIndex_BOOT_INIT_Data, /* D_BOOT_INIT_Data_Len_4 */
    #if 0
	德尔BOOT版本
    #endif
    EN_MemIndex_DareBootVersion, /* D_DareBootVersion_Len_8 */
    #if 0
	客户BOOT版本
    #endif
    EN_MemIndex_CustomerBootVersion, /* D_CustomerBootVersion_Len_15 */
/********数据块ID_0 定义结束********/

/********数据块ID_1 定义开始********/
    #if 0
	APP有效标志
    #endif
    EN_MemIndex_APP_ValidFlg, /* D_APP_ValidFlg_Len_8 */
    #if 0
	刷写维修日期
    #endif
    EN_MemIndex_FingerPrint_ProgramDate_F199, /* D_FingerPrint_ProgramDate_F199_Len_4 */
    #if 0
	售后维修点代码
    #endif
    EN_MemIndex_FingerPrint_RepairShopCodeF198, /* D_FingerPrint_RepairShopCodeF198_Len_8 */
    #if 0
	BOOT安全访问次数
    #endif
    EN_MemIndex_BOOTUdsSecurityAccessTimes, /* D_BOOTUdsSecurityAccessTimes_Len_1 */
    #if 0
	App安全访问次数
    #endif
    EN_MemIndex_AppUdsSecurityAccessTimes, /* D_AppUdsSecurityAccessTimes_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved0, /* D_Reserved0_Len_1 */
/********数据块ID_1 定义结束********/

/********数据块ID_2 定义开始********/
    #if 0
	升级跳转标志
    #endif
    EN_MemIndex_AppJumpToBootFlg, /* D_AppJumpToBootFlg_Len_1 */
    #if 0
	唤醒源
    #endif
    EN_MemIndex_WakeUpSource, /* D_WakeUpSource_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved1, /* D_Reserved1_Len_1 */
/********数据块ID_2 定义结束********/

/********数据块ID_28 定义开始********/
    #if 0
	主驾高度当前霍尔数
    #endif
    EN_MemIndex_DrCurHallCnt_Height, /* D_DrCurHallCnt_Height_Len_2 */
    #if 0
	主驾纵向当前霍尔数
    #endif
    EN_MemIndex_DrCurHallCnt_Length, /* D_DrCurHallCnt_Length_Len_2 */
    #if 0
	主驾靠背当前霍尔数
    #endif
    EN_MemIndex_DrCurHallCnt_Back, /* D_DrCurHallCnt_Back_Len_2 */
    #if 0
	主驾腿托当前霍尔数
    #endif
    EN_MemIndex_DrCurHallCnt_Front, /* D_DrCurHallCnt_Front_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved2, /* D_Reserved2_Len_3 */
/********数据块ID_28 定义结束********/

/********数据块ID_29 定义开始********/
    #if 0
	主驾高度硬止点坐标
    #endif
    EN_MemIndex_DrHardStopPos_Height, /* D_DrHardStopPos_Height_Len_2 */
    #if 0
	主驾纵向硬止点坐标
    #endif
    EN_MemIndex_DrHardStopPos_Length, /* D_DrHardStopPos_Length_Len_2 */
    #if 0
	主驾靠背硬止点坐标
    #endif
    EN_MemIndex_DrHardStopPos_Back, /* D_DrHardStopPos_Back_Len_2 */
    #if 0
	主驾腿托硬止点坐标
    #endif
    EN_MemIndex_DrHardStopPos_Front, /* D_DrHardStopPos_Front_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved3, /* D_Reserved3_Len_3 */
/********数据块ID_29 定义结束********/

/********数据块ID_30 定义开始********/
    #if 0
	主驾高度记忆位置1
    #endif
    EN_MemIndex_DrMem1_Height, /* D_DrMem1_Height_Len_2 */
    #if 0
	主驾纵向记忆位置1
    #endif
    EN_MemIndex_DrMem1_Length, /* D_DrMem1_Length_Len_2 */
    #if 0
	主驾靠背记忆位置1
    #endif
    EN_MemIndex_DrMem1_Back, /* D_DrMem1_Back_Len_2 */
    #if 0
	主驾腿托记忆位置1
    #endif
    EN_MemIndex_DrMem1_Front, /* D_DrMem1_Front_Len_2 */
    #if 0
	主驾记忆1有效标志
    #endif
    EN_MemIndex_DrMem1_ValidFlag, /* D_DrMem1_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved4, /* D_Reserved4_Len_2 */
/********数据块ID_30 定义结束********/

/********数据块ID_31 定义开始********/
    #if 0
	主驾高度记忆位置2
    #endif
    EN_MemIndex_DrMem2_Height, /* D_DrMem2_Height_Len_2 */
    #if 0
	主驾纵向记忆位置2
    #endif
    EN_MemIndex_DrMem2_Length, /* D_DrMem2_Length_Len_2 */
    #if 0
	主驾靠背记忆位置2
    #endif
    EN_MemIndex_DrMem2_Back, /* D_DrMem2_Back_Len_2 */
    #if 0
	主驾腿托记忆位置2
    #endif
    EN_MemIndex_DrMem2_Front, /* D_DrMem2_Front_Len_2 */
    #if 0
	主驾记忆2有效标志
    #endif
    EN_MemIndex_DrMem2_ValidFlag, /* D_DrMem2_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved5, /* D_Reserved5_Len_2 */
/********数据块ID_31 定义结束********/

/********数据块ID_32 定义开始********/
    #if 0
	主驾高度记忆位置3
    #endif
    EN_MemIndex_DrMem3_Height, /* D_DrMem3_Height_Len_2 */
    #if 0
	主驾纵向记忆位置3
    #endif
    EN_MemIndex_DrMem3_Length, /* D_DrMem3_Length_Len_2 */
    #if 0
	主驾靠背记忆位置3
    #endif
    EN_MemIndex_DrMem3_Back, /* D_DrMem3_Back_Len_2 */
    #if 0
	主驾腿托记忆位置3
    #endif
    EN_MemIndex_DrMem3_Front, /* D_DrMem3_Front_Len_2 */
    #if 0
	主驾记忆3有效标志
    #endif
    EN_MemIndex_DrMem3_ValidFlag, /* D_DrMem3_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved6, /* D_Reserved6_Len_2 */
/********数据块ID_32 定义结束********/

/********数据块ID_33 定义开始********/
    #if 0
	主驾高度主驾小憩回位位置
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Height, /* D_DrRes_ReCallPosi_Height_Len_2 */
    #if 0
	主驾纵向主驾小憩回位位置
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Length, /* D_DrRes_ReCallPosi_Length_Len_2 */
    #if 0
	主驾靠背主驾小憩回位位置
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Back, /* D_DrRes_ReCallPosi_Back_Len_2 */
    #if 0
	主驾腿托主驾小憩回位位置
    #endif
    EN_MemIndex_DrRes_ReCallPosi_Front, /* D_DrRes_ReCallPosi_Front_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved7, /* D_Reserved7_Len_3 */
/********数据块ID_33 定义结束********/

/********数据块ID_34 定义开始********/
    #if 0
	副驾高度当前霍尔数
    #endif
    EN_MemIndex_PaCurHallCnt_Height, /* D_PaCurHallCnt_Height_Len_2 */
    #if 0
	副驾纵向当前霍尔数
    #endif
    EN_MemIndex_PaCurHallCnt_Length, /* D_PaCurHallCnt_Length_Len_2 */
    #if 0
	副驾靠背当前霍尔数
    #endif
    EN_MemIndex_PaCurHallCnt_Back, /* D_PaCurHallCnt_Back_Len_2 */
    #if 0
	副驾腿托当前霍尔数
    #endif
    EN_MemIndex_PaCurHallCnt_Front, /* D_PaCurHallCnt_Front_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved8, /* D_Reserved8_Len_3 */
/********数据块ID_34 定义结束********/

/********数据块ID_35 定义开始********/
    #if 0
	副驾高度硬止点坐标
    #endif
    EN_MemIndex_PaHardStopPos_Height, /* D_PaHardStopPos_Height_Len_2 */
    #if 0
	副驾纵向硬止点坐标
    #endif
    EN_MemIndex_PaHardStopPos_Length, /* D_PaHardStopPos_Length_Len_2 */
    #if 0
	副驾靠背硬止点坐标
    #endif
    EN_MemIndex_PaHardStopPos_Back, /* D_PaHardStopPos_Back_Len_2 */
    #if 0
	副驾腿托硬止点坐标
    #endif
    EN_MemIndex_PaHardStopPos_Front, /* D_PaHardStopPos_Front_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved9, /* D_Reserved9_Len_3 */
/********数据块ID_35 定义结束********/

/********数据块ID_36 定义开始********/
    #if 0
	副驾高度记忆位置1
    #endif
    EN_MemIndex_PaMem1_Height, /* D_PaMem1_Height_Len_2 */
    #if 0
	副驾纵向记忆位置1
    #endif
    EN_MemIndex_PaMem1_Length, /* D_PaMem1_Length_Len_2 */
    #if 0
	副驾靠背记忆位置1
    #endif
    EN_MemIndex_PaMem1_Back, /* D_PaMem1_Back_Len_2 */
    #if 0
	副驾腿托记忆位置1
    #endif
    EN_MemIndex_PaMem1_Front, /* D_PaMem1_Front_Len_2 */
    #if 0
	副驾记忆1有效标志
    #endif
    EN_MemIndex_PaMem1_ValidFlag, /* D_PaMem1_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved10, /* D_Reserved10_Len_2 */
/********数据块ID_36 定义结束********/

/********数据块ID_37 定义开始********/
    #if 0
	副驾高度记忆位置2
    #endif
    EN_MemIndex_PaMem2_Height, /* D_PaMem2_Height_Len_2 */
    #if 0
	副驾纵向记忆位置2
    #endif
    EN_MemIndex_PaMem2_Length, /* D_PaMem2_Length_Len_2 */
    #if 0
	副驾靠背记忆位置2
    #endif
    EN_MemIndex_PaMem2_Back, /* D_PaMem2_Back_Len_2 */
    #if 0
	副驾腿托记忆位置2
    #endif
    EN_MemIndex_PaMem2_Front, /* D_PaMem2_Front_Len_2 */
    #if 0
	副驾记忆2有效标志
    #endif
    EN_MemIndex_PaMem2_ValidFlag, /* D_PaMem2_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved11, /* D_Reserved11_Len_2 */
/********数据块ID_37 定义结束********/

/********数据块ID_38 定义开始********/
    #if 0
	副驾高度记忆位置3
    #endif
    EN_MemIndex_PaMem3_Height, /* D_PaMem3_Height_Len_2 */
    #if 0
	副驾纵向记忆位置3
    #endif
    EN_MemIndex_PaMem3_Length, /* D_PaMem3_Length_Len_2 */
    #if 0
	副驾靠背记忆位置3
    #endif
    EN_MemIndex_PaMem3_Back, /* D_PaMem3_Back_Len_2 */
    #if 0
	副驾腿托记忆位置3
    #endif
    EN_MemIndex_PaMem3_Front, /* D_PaMem3_Front_Len_2 */
    #if 0
	副驾记忆3有效标志
    #endif
    EN_MemIndex_PaMem3_ValidFlag, /* D_PaMem3_ValidFlag_Len_1 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved12, /* D_Reserved12_Len_2 */
/********数据块ID_38 定义结束********/

/********数据块ID_39 定义开始********/
    #if 0
	主驾迎宾纵向后移目标位置
    #endif
    EN_MemIndex_DrWelcome_LenTar_BackWard, /* D_DrWelcome_LenTar_BackWard_Len_2 */
    #if 0
	主驾迎宾纵向前移目标位置
    #endif
    EN_MemIndex_DrWelcome_LenTar_ForWard, /* D_DrWelcome_LenTar_ForWard_Len_2 */
    #if 0
	副驾迎宾纵向后移目标位置
    #endif
    EN_MemIndex_PaWelcome_LenTar_BackWard, /* D_PaWelcome_LenTar_BackWard_Len_2 */
    #if 0
	副驾迎宾纵向前移目标位置
    #endif
    EN_MemIndex_PaWelcome_LenTar_ForWard, /* D_PaWelcome_LenTar_ForWard_Len_2 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved13, /* D_Reserved13_Len_3 */
/********数据块ID_39 定义结束********/

/********数据块ID_42 定义开始********/
    #if 0
	主驾座椅调节配置
	0x00:手动调节
	0x01:六向电机
	0x02:十二向电机
    #endif
    EN_MemIndex_DrAdjustConfig, /* D_DrAdjustConfig_Len_1 */
    #if 0
	副驾座椅调节配置
	0x00:手动调节
	0x01:四向电机
    #endif
    EN_MemIndex_PaAdjustConfig, /* D_PaAdjustConfig_Len_1 */
    #if 0
	主驾通风加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_DrVentAndHeatConfig, /* D_DrVentAndHeatConfig_Len_1 */
    #if 0
	主驾记忆迎宾配置
	0:不存在
	2：存在
    #endif
    EN_MemIndex_DrMemoryConfig, /* D_DrMemoryConfig_Len_1 */
    #if 0
	副驾通风加热配置
	0:不存在
	2：存在
    #endif
    EN_MemIndex_PaVentAndHeatConfig, /* D_PaVentAndHeatConfig_Len_1 */
    #if 0
	副驾记忆迎宾配置
	0:不存在
	3：存在
    #endif
    EN_MemIndex_PaMemoryConfig, /* D_PaMemoryConfig_Len_1 */
    #if 0
	按摩功能配置
	0:不存在
	4：存在
    #endif
    EN_MemIndex_MassageConfig, /* D_MassageConfig_Len_1 */
    #if 0
	车辆功能配置预留byte0
    #endif
    EN_MemIndex_VehicleConfigReserveByte0, /* D_VehicleConfigReserveByte0_Len_1 */
    #if 0
	车辆功能配置预留byte1
    #endif
    EN_MemIndex_VehicleConfigReserveByte1, /* D_VehicleConfigReserveByte1_Len_1 */
    #if 0
	车辆功能配置预留byte2
    #endif
    EN_MemIndex_VehicleConfigReserveByte2, /* D_VehicleConfigReserveByte2_Len_1 */
    #if 0
	车型：C62X、C52X…
	0：P20车型
	1：BM400车型
    #endif
    EN_MemIndex_Heat_CarType, /* D_Heat_CarType_Len_1 */
    #if 0
	加热远程使能配置
	0：无远程使能
	1：有远程使能
    #endif
    EN_MemIndex_Heat_RemoteEnableConfig, /* D_Heat_RemoteEnableConfig_Len_1 */
    #if 0
	加热发动机使能配置
	0：无发动机使能
	1：有发动机使能
    #endif
    EN_MemIndex_Heat_PlatformEngineEnableConfig, /* D_Heat_PlatformEngineEnableConfig_Len_1 */
    #if 0
	加热P20PHEV发动机使能配置
	0：无加热P20PHEV发动机
	1：有加热P20PHEV发动机
    #endif
    EN_MemIndex_Heat_P20_PHEV_EngineCfg, /* D_Heat_P20_PHEV_EngineCfg_Len_1 */
    #if 0
	加热超时使能配置
	0：禁能
	1：使能
    #endif
    EN_MemIndex_Heat_TimeOutPrm, /* D_Heat_TimeOutPrm_Len_1 */
/********数据块ID_42 定义结束********/

/********数据块ID_43 定义开始********/
    #if 0
	加热超时时间配置
	0：无超时
	1：10min
	2：20min
    #endif
    EN_MemIndex_Heat_RunMaxTime, /* D_Heat_RunMaxTime_Len_1 */
    #if 0
	成测报文发送标志
	0：成测报文发送禁能
	1：成测报文发送使能
    #endif
    EN_MemIndex_SendTestMsgFlg, /* D_SendTestMsgFlg_Len_1 */
    #if 0
	通风超时使能配置
	0：禁能
	1：使能
    #endif
    EN_MemIndex_Vent_TimeOutPrm, /* D_Vent_TimeOutPrm_Len_1 */
    #if 0
	通风超时时间配置
	0：无超时
	1：10min
	2：20min
    #endif
    EN_MemIndex_Vent_RunMaxTime, /* D_Vent_RunMaxTime_Len_1 */
    #if 0
	软止点最大调节次数
    #endif
    EN_MemIndex_MotorSoftStopCntMax, /* D_MotorSoftStopCntMax_Len_1 */
    #if 0
	主驾高度到达软止点次数
    #endif
    EN_MemIndex_DrHeightSoftStopCnt, /* D_DrHeightSoftStopCnt_Len_1 */
    #if 0
	主驾纵向到达软止点次数
    #endif
    EN_MemIndex_DrLengthSoftStopCnt, /* D_DrLengthSoftStopCnt_Len_1 */
    #if 0
	主驾靠背到达软止点次数
    #endif
    EN_MemIndex_DrBackSoftStopCnt, /* D_DrBackSoftStopCnt_Len_1 */
    #if 0
	主驾腿托到达软止点次数
    #endif
    EN_MemIndex_DrFrontSoftStopCnt, /* D_DrFrontSoftStopCnt_Len_1 */
    #if 0
	允许写硬件版本号标志
    #endif
    EN_MemIndex_Write_HardwareVersion_Flg, /* D_Write_HardwareVersion_Flg_Len_1 */
    #if 0
	迎宾状态
	0：无效；
	1：后移；
	2：前移。
    #endif
    EN_MemIndex_WelcomeStatus, /* D_WelcomeStatus_Len_1 */
    #if 0
	主驾迎宾位置更新标志:
	0：不更新
	1：更新
    #endif
    EN_MemIndex_WelcomeDrUpate, /* D_WelcomeDrUpate_Len_1 */
    #if 0
	加热整车运行使能配置
	 0：无整车运行状态判断使能
	 1：有整车运行状态判断使能
    #endif
    EN_MemIndex_Heat_PlatFormVehicleEnableConfig, /* D_Heat_PlatFormVehicleEnableConfig_Len_1 */
    #if 0
	车辆功能配置预留byte3
    #endif
    EN_MemIndex_VehicleConfigReserveByte3, /* D_VehicleConfigReserveByte3_Len_1 */
    #if 0
	车辆功能配置预留byte4
    #endif
    EN_MemIndex_VehicleConfigReserveByte4, /* D_VehicleConfigReserveByte4_Len_1 */
/********数据块ID_43 定义结束********/

/********数据块ID_44 定义开始********/
    #if 0
	主驾迎宾开关状态:
	0：关闭
	1：开启
    #endif
    EN_MemIndex_WelcomeSwitch, /* D_WelcomeSwitch_Len_1 */
    #if 0
	按摩模式反馈：
	0x0: 全身放松
	0x1: 全身激活
	0x2：肩部激活
	0x3: 肩部放松
	0x4：腰部激活
	0x5：腰部放松
	0x6：背部激活
	0x7：背部放松
	0x8：Error模块故障
    #endif
    EN_MemIndex_MassageMode, /* D_MassageMode_Len_1 */
    #if 0
	记忆提示反馈报文
	0：无变化
	1：有变化
    #endif
    EN_MemIndex_FLSeatPosMsg, /* D_FLSeatPosMsg_Len_1 */
    #if 0
	副驾迎宾开关
	0：关闭
	1：开启
    #endif
    EN_MemIndex_PaWelcomeSwitch, /* D_PaWelcomeSwitch_Len_1 */
    #if 0
	副驾迎宾状态
	0：无效；
	1：后移；
	2：前移。
    #endif
    EN_MemIndex_PaWelcomeStatus, /* D_PaWelcomeStatus_Len_1 */
    #if 0
	主驾加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_DrHeatConfig, /* D_DrHeatConfig_Len_1 */
    #if 0
	2排加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_SecondHeatConfig, /* D_SecondHeatConfig_Len_1 */
    #if 0
	三排加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_ThirdHeatConfig, /* D_ThirdHeatConfig_Len_1 */
    #if 0
	主驾通风配置
	0:不存在
	2：存在
    #endif
    EN_MemIndex_DrvVentConfig, /* D_DrvVentConfig_Len_1 */
    #if 0
	二排通风配置
	0:不存在
	2：存在
    #endif
    EN_MemIndex_SecondVentConfig, /* D_SecondVentConfig_Len_1 */
    #if 0
	三排通风配置
	0:不存在
	3：存在
    #endif
    EN_MemIndex_ThirdVentConfig, /* D_ThirdVentConfig_Len_1 */
    #if 0
	三排按摩功能配置
	0:不存在
	4：存在
    #endif
    EN_MemIndex_ThirdMassageConfig, /* D_ThirdMassageConfig_Len_1 */
    #if 0
	记忆提示反馈报文
	0：无变化
	1：有变化
    #endif
    EN_MemIndex_FRSeatPosMsg, /* D_FRSeatPosMsg_Len_1 */
    #if 0
	副驾迎宾位置更新标志:
	0：不更新
	1：更新
    #endif
    EN_MemIndex_WelcomePaUpdate, /* D_WelcomePaUpdate_Len_1 */
    #if 0
	副驾高度到达软止点次数
    #endif
    EN_MemIndex_PaHeightSoftStopCnt, /* D_PaHeightSoftStopCnt_Len_1 */
/********数据块ID_44 定义结束********/

/********数据块ID_45 定义开始********/
    #if 0
	副驾纵向到达软止点次数
    #endif
    EN_MemIndex_PaLengthSoftStopCnt, /* D_PaLengthSoftStopCnt_Len_1 */
    #if 0
	副驾靠背到达软止点次数
    #endif
    EN_MemIndex_PaBackSoftStopCnt, /* D_PaBackSoftStopCnt_Len_1 */
    #if 0
	副驾腿托到达软止点次数
    #endif
    EN_MemIndex_PaFrontSoftStopCnt, /* D_PaFrontSoftStopCnt_Len_1 */
    #if 0
	主驾加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_DrHeatFlg, /* D_DrHeatFlg_Len_1 */
    #if 0
	主驾通风配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_DrVentFlg, /* D_DrVentFlg_Len_1 */
    #if 0
	副驾加热配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_PaHeatFlg, /* D_PaHeatFlg_Len_1 */
    #if 0
	副驾通风配置
	0:不存在
	1：存在
    #endif
    EN_MemIndex_PaVentFlg, /* D_PaVentFlg_Len_1 */
    #if 0
	测试模式
	0:不存在
	1：存在
    #endif
    EN_MemIndex_TestMode, /* D_TestMode_Len_1 */
    #if 0
	主驾门状态
	0：关
	1：开
    #endif
    EN_MemIndex_DrDoorSts, /* D_DrDoorSts_Len_1 */
    #if 0
	副驾门状态
	0：关
	1：开
    #endif
    EN_MemIndex_PaDoorSts, /* D_PaDoorSts_Len_1 */
    #if 0
	测试报文发送配置
	0：发送禁能
	1：发送使能
	bit0:0x500
	bit1:0x501
	bit2:0x502
    #endif
    EN_MemIndex_TestMessageSendCfg, /* D_TestMessageSendCfg_Len_1 */
/********数据块ID_45 定义结束********/

/********数据块ID_76 定义开始********/
    #if 0
	系统功能配置F1FA配置
    #endif
    EN_MemIndex_SystemFunctionConfiguration_F1FA, /* D_SystemFunctionConfiguration_F1FA_Len_6 */
    #if 0
	VIN码
    #endif
    EN_MemIndex_UdsDidVinCode, /* D_UdsDidVinCode_Len_17 */
    #if 0
	产品生产日期
    #endif
    EN_MemIndex_ECUManufactureData, /* D_ECUManufactureData_Len_4 */
/********数据块ID_76 定义结束********/

/********数据块ID_77 定义开始********/
    #if 0
	客户硬件版本号
    #endif
    EN_MemIndex_ECUHardwareVersion, /* D_ECUHardwareVersion_Len_16 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved15, /* D_Reserved15_Len_3 */
/********数据块ID_77 定义结束********/

/********数据块ID_78 定义开始********/
    #if 0
	PCBA 存储
    #endif
    EN_MemIndex_PCBASerialNumber, /* D_PCBASerialNumber_Len_21 */
    #if 0
	预留
    #endif
    EN_MemIndex_Reserved16, /* D_Reserved16_Len_2 */
/********数据块ID_78 定义结束********/

/********数据块ID_56 定义开始********/
    #if 0
	控制器上电类型及次数
    #endif
    EN_MemIndex_BoardPowerOnTypeAndCnt, /* D_BoardPowerOnTypeAndCnt_Len_15 */
/********数据块ID_56 定义结束********/

/********数据块ID_57 定义开始********/
    #if 0
	CAN总线BUS OFF
    #endif
    EN_MemIndex_Dtc_Index0, /* D_Dtc_Index0_Len_3 */
    #if 0
	供电电压过低
    #endif
    EN_MemIndex_Dtc_Index1, /* D_Dtc_Index1_Len_3 */
    #if 0
	供电电压过高
    #endif
    EN_MemIndex_Dtc_Index2, /* D_Dtc_Index2_Len_3 */
    #if 0
	座椅节点进入Limphome状态
    #endif
    EN_MemIndex_Dtc_Index3, /* D_Dtc_Index3_Len_3 */
    #if 0
	DSM与BCM通讯丢失
    #endif
    EN_MemIndex_Dtc_Index4, /* D_Dtc_Index4_Len_3 */
/********数据块ID_57 定义结束********/

/********数据块ID_58 定义开始********/
    #if 0
	DSM与GW通讯丢失
    #endif
    EN_MemIndex_Dtc_Index5, /* D_Dtc_Index5_Len_3 */
    #if 0
	主驾加热输出对地短路
    #endif
    EN_MemIndex_Dtc_Index6, /* D_Dtc_Index6_Len_3 */
    #if 0
	主驾加热输出断路
    #endif
    EN_MemIndex_Dtc_Index7, /* D_Dtc_Index7_Len_3 */
    #if 0
	主驾加热NTC+对地短路
    #endif
    EN_MemIndex_Dtc_Index8, /* D_Dtc_Index8_Len_3 */
    #if 0
	主驾加热NTC+对电源短路或断路
    #endif
    EN_MemIndex_Dtc_Index9, /* D_Dtc_Index9_Len_3 */
/********数据块ID_58 定义结束********/

/********数据块ID_59 定义开始********/
    #if 0
	主驾加热NTC+输入无效
    #endif
    EN_MemIndex_Dtc_Index10, /* D_Dtc_Index10_Len_3 */
    #if 0
	副驾加热输出对地短路
    #endif
    EN_MemIndex_Dtc_Index11, /* D_Dtc_Index11_Len_3 */
    #if 0
	副驾加热输出断路
    #endif
    EN_MemIndex_Dtc_Index12, /* D_Dtc_Index12_Len_3 */
    #if 0
	副驾加热NTC+对地短路
    #endif
    EN_MemIndex_Dtc_Index13, /* D_Dtc_Index13_Len_3 */
    #if 0
	副驾加热NTC+对电源短路或断路
    #endif
    EN_MemIndex_Dtc_Index14, /* D_Dtc_Index14_Len_3 */
/********数据块ID_59 定义结束********/

/********数据块ID_60 定义开始********/
    #if 0
	副驾加热NTC+输入无效
    #endif
    EN_MemIndex_Dtc_Index15, /* D_Dtc_Index15_Len_3 */
    #if 0
	主驾通风驱动信号（PWM）对地短路
    #endif
    EN_MemIndex_Dtc_Index16, /* D_Dtc_Index16_Len_3 */
    #if 0
	主驾通风驱动信号（PWM）对电源短路或断路
    #endif
    EN_MemIndex_Dtc_Index17, /* D_Dtc_Index17_Len_3 */
    #if 0
	副驾通风驱动信号（PWM）对地短路
    #endif
    EN_MemIndex_Dtc_Index18, /* D_Dtc_Index18_Len_3 */
    #if 0
	副驾通风驱动信号（PWM）对电源短路或断路
    #endif
    EN_MemIndex_Dtc_Index19, /* D_Dtc_Index19_Len_3 */
/********数据块ID_60 定义结束********/

/********数据块ID_61 定义开始********/
    #if 0
	主驾纵向向前调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index20, /* D_Dtc_Index20_Len_3 */
    #if 0
	主驾纵向向后调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index21, /* D_Dtc_Index21_Len_3 */
    #if 0
	主驾靠背向前调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index22, /* D_Dtc_Index22_Len_3 */
    #if 0
	主驾靠背向后调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index23, /* D_Dtc_Index23_Len_3 */
    #if 0
	主驾高度向上调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index24, /* D_Dtc_Index24_Len_3 */
/********数据块ID_61 定义结束********/

/********数据块ID_62 定义开始********/
    #if 0
	主驾高度向下调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index25, /* D_Dtc_Index25_Len_3 */
    #if 0
	主驾坐垫前部角度向前调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index26, /* D_Dtc_Index26_Len_3 */
    #if 0
	主驾坐垫前部角度向后调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index27, /* D_Dtc_Index27_Len_3 */
    #if 0
	副驾纵向向前调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index28, /* D_Dtc_Index28_Len_3 */
    #if 0
	副驾纵向向后调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index29, /* D_Dtc_Index29_Len_3 */
/********数据块ID_62 定义结束********/

/********数据块ID_63 定义开始********/
    #if 0
	副驾靠背电机向前调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index30, /* D_Dtc_Index30_Len_3 */
    #if 0
	副驾靠背电机向后调节开关粘连
    #endif
    EN_MemIndex_Dtc_Index31, /* D_Dtc_Index31_Len_3 */
    #if 0
	主驾高度调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index32, /* D_Dtc_Index32_Len_3 */
    #if 0
	主驾纵向调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index33, /* D_Dtc_Index33_Len_3 */
    #if 0
	主驾靠背调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index34, /* D_Dtc_Index34_Len_3 */
/********数据块ID_63 定义结束********/

/********数据块ID_64 定义开始********/
    #if 0
	主驾坐垫前部角度调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index35, /* D_Dtc_Index35_Len_3 */
    #if 0
	副驾座椅纵向调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index36, /* D_Dtc_Index36_Len_3 */
    #if 0
	副驾靠背调节继电器粘连
    #endif
    EN_MemIndex_Dtc_Index37, /* D_Dtc_Index37_Len_3 */
    #if 0
	主驾高度调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index38, /* D_Dtc_Index38_Len_3 */
    #if 0
	主驾纵向调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index39, /* D_Dtc_Index39_Len_3 */
/********数据块ID_64 定义结束********/

/********数据块ID_65 定义开始********/
    #if 0
	主驾靠背调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index40, /* D_Dtc_Index40_Len_3 */
    #if 0
	主驾坐垫前部角度调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index41, /* D_Dtc_Index41_Len_3 */
    #if 0
	副驾纵向调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index42, /* D_Dtc_Index42_Len_3 */
    #if 0
	副驾靠背调节电机霍尔故障
    #endif
    EN_MemIndex_Dtc_Index43, /* D_Dtc_Index43_Len_3 */
    #if 0
	方向盘加热输出对地短路
    #endif
    EN_MemIndex_Dtc_Index44, /* D_Dtc_Index44_Len_3 */
/********数据块ID_65 定义结束********/

/********数据块ID_66 定义开始********/
    #if 0
	方向盘加热输出断路
    #endif
    EN_MemIndex_Dtc_Index45, /* D_Dtc_Index45_Len_3 */
    #if 0
	方向盘加热NTC+对地短路
    #endif
    EN_MemIndex_Dtc_Index46, /* D_Dtc_Index46_Len_3 */
    #if 0
	方向盘加热NTC+对电源短路或断路
    #endif
    EN_MemIndex_Dtc_Index47, /* D_Dtc_Index47_Len_3 */
    #if 0
	方向盘加热NTC+输入无效
    #endif
    EN_MemIndex_Dtc_Index48, /* D_Dtc_Index48_Len_3 */
    #if 0
	按摩模块欠压
    #endif
    EN_MemIndex_Dtc_Index49, /* D_Dtc_Index49_Len_3 */
/********数据块ID_66 定义结束********/

/********数据块ID_67 定义开始********/
    #if 0
	按摩模块过压
    #endif
    EN_MemIndex_Dtc_Index50, /* D_Dtc_Index50_Len_3 */
    #if 0
	按摩电机过流
    #endif
    EN_MemIndex_Dtc_Index51, /* D_Dtc_Index51_Len_3 */
    #if 0
	LIN数据出错
    #endif
    EN_MemIndex_Dtc_Index52, /* D_Dtc_Index52_Len_3 */
    #if 0
	DTC预留0
    #endif
    EN_MemIndex_Dtc_Index53, /* D_Dtc_Index53_Len_3 */
    #if 0
	DTC最大值 - 需要这里定义表的顺序连续
    #endif
    EN_MemIndex_Dtc_IndexMax, /* D_Dtc_IndexMax_Len_3 */
/********数据块ID_67 定义结束********/
    EN_MemIndex_Max
} enSrvMemIndex;
#define     D_APP_INIT_Data_Len_4                       4
#define     D_BOOT_INIT_Data_Len_4                      4
#define     D_DareBootVersion_Len_8                     8
#define     D_CustomerBootVersion_Len_15                15

#define     D_APP_ValidFlg_Len_8                        8
#define     D_FingerPrint_ProgramDate_F199_Len_4        4
#define     D_FingerPrint_RepairShopCodeF198_Len_8      8
#define     D_BOOTUdsSecurityAccessTimes_Len_1          1
#define     D_AppUdsSecurityAccessTimes_Len_1           1
#define     D_Reserved0_Len_1                           1

#define     D_AppJumpToBootFlg_Len_1                    1
#define     D_WakeUpSource_Len_1                        1
#define     D_Reserved1_Len_1                           1

#define     D_DrCurHallCnt_Height_Len_2                 2
#define     D_DrCurHallCnt_Length_Len_2                 2
#define     D_DrCurHallCnt_Back_Len_2                   2
#define     D_DrCurHallCnt_Front_Len_2                  2
#define     D_Reserved2_Len_3                           3

#define     D_DrHardStopPos_Height_Len_2                2
#define     D_DrHardStopPos_Length_Len_2                2
#define     D_DrHardStopPos_Back_Len_2                  2
#define     D_DrHardStopPos_Front_Len_2                 2
#define     D_Reserved3_Len_3                           3

#define     D_DrMem1_Height_Len_2                       2
#define     D_DrMem1_Length_Len_2                       2
#define     D_DrMem1_Back_Len_2                         2
#define     D_DrMem1_Front_Len_2                        2
#define     D_DrMem1_ValidFlag_Len_1                    1
#define     D_Reserved4_Len_2                           2

#define     D_DrMem2_Height_Len_2                       2
#define     D_DrMem2_Length_Len_2                       2
#define     D_DrMem2_Back_Len_2                         2
#define     D_DrMem2_Front_Len_2                        2
#define     D_DrMem2_ValidFlag_Len_1                    1
#define     D_Reserved5_Len_2                           2

#define     D_DrMem3_Height_Len_2                       2
#define     D_DrMem3_Length_Len_2                       2
#define     D_DrMem3_Back_Len_2                         2
#define     D_DrMem3_Front_Len_2                        2
#define     D_DrMem3_ValidFlag_Len_1                    1
#define     D_Reserved6_Len_2                           2

#define     D_DrRes_ReCallPosi_Height_Len_2             2
#define     D_DrRes_ReCallPosi_Length_Len_2             2
#define     D_DrRes_ReCallPosi_Back_Len_2               2
#define     D_DrRes_ReCallPosi_Front_Len_2              2
#define     D_Reserved7_Len_3                           3

#define     D_PaCurHallCnt_Height_Len_2                 2
#define     D_PaCurHallCnt_Length_Len_2                 2
#define     D_PaCurHallCnt_Back_Len_2                   2
#define     D_PaCurHallCnt_Front_Len_2                  2
#define     D_Reserved8_Len_3                           3

#define     D_PaHardStopPos_Height_Len_2                2
#define     D_PaHardStopPos_Length_Len_2                2
#define     D_PaHardStopPos_Back_Len_2                  2
#define     D_PaHardStopPos_Front_Len_2                 2
#define     D_Reserved9_Len_3                           3

#define     D_PaMem1_Height_Len_2                       2
#define     D_PaMem1_Length_Len_2                       2
#define     D_PaMem1_Back_Len_2                         2
#define     D_PaMem1_Front_Len_2                        2
#define     D_PaMem1_ValidFlag_Len_1                    1
#define     D_Reserved10_Len_2                          2

#define     D_PaMem2_Height_Len_2                       2
#define     D_PaMem2_Length_Len_2                       2
#define     D_PaMem2_Back_Len_2                         2
#define     D_PaMem2_Front_Len_2                        2
#define     D_PaMem2_ValidFlag_Len_1                    1
#define     D_Reserved11_Len_2                          2

#define     D_PaMem3_Height_Len_2                       2
#define     D_PaMem3_Length_Len_2                       2
#define     D_PaMem3_Back_Len_2                         2
#define     D_PaMem3_Front_Len_2                        2
#define     D_PaMem3_ValidFlag_Len_1                    1
#define     D_Reserved12_Len_2                          2

#define     D_DrWelcome_LenTar_BackWard_Len_2           2
#define     D_DrWelcome_LenTar_ForWard_Len_2            2
#define     D_PaWelcome_LenTar_BackWard_Len_2           2
#define     D_PaWelcome_LenTar_ForWard_Len_2            2
#define     D_Reserved13_Len_3                          3

#define     D_DrAdjustConfig_Len_1                      1
#define     D_PaAdjustConfig_Len_1                      1
#define     D_DrVentAndHeatConfig_Len_1                 1
#define     D_DrMemoryConfig_Len_1                      1
#define     D_PaVentAndHeatConfig_Len_1                 1
#define     D_PaMemoryConfig_Len_1                      1
#define     D_MassageConfig_Len_1                       1
#define     D_VehicleConfigReserveByte0_Len_1           1
#define     D_VehicleConfigReserveByte1_Len_1           1
#define     D_VehicleConfigReserveByte2_Len_1           1
#define     D_Heat_CarType_Len_1                        1
#define     D_Heat_RemoteEnableConfig_Len_1             1
#define     D_Heat_PlatformEngineEnableConfig_Len_1     1
#define     D_Heat_P20_PHEV_EngineCfg_Len_1             1
#define     D_Heat_TimeOutPrm_Len_1                     1

#define     D_Heat_RunMaxTime_Len_1                     1
#define     D_SendTestMsgFlg_Len_1                      1
#define     D_Vent_TimeOutPrm_Len_1                     1
#define     D_Vent_RunMaxTime_Len_1                     1
#define     D_MotorSoftStopCntMax_Len_1                 1
#define     D_DrHeightSoftStopCnt_Len_1                 1
#define     D_DrLengthSoftStopCnt_Len_1                 1
#define     D_DrBackSoftStopCnt_Len_1                   1
#define     D_DrFrontSoftStopCnt_Len_1                  1
#define     D_Write_HardwareVersion_Flg_Len_1           1
#define     D_WelcomeStatus_Len_1                       1
#define     D_WelcomeDrUpate_Len_1                      1
#define     D_Heat_PlatFormVehicleEnableConfig_Len_1    1
#define     D_VehicleConfigReserveByte3_Len_1           1
#define     D_VehicleConfigReserveByte4_Len_1           1

#define     D_WelcomeSwitch_Len_1                       1
#define     D_MassageMode_Len_1                         1
#define     D_FLSeatPosMsg_Len_1                        1
#define     D_PaWelcomeSwitch_Len_1                     1
#define     D_PaWelcomeStatus_Len_1                     1
#define     D_DrHeatConfig_Len_1                        1
#define     D_SecondHeatConfig_Len_1                    1
#define     D_ThirdHeatConfig_Len_1                     1
#define     D_DrvVentConfig_Len_1                       1
#define     D_SecondVentConfig_Len_1                    1
#define     D_ThirdVentConfig_Len_1                     1
#define     D_ThirdMassageConfig_Len_1                  1
#define     D_FRSeatPosMsg_Len_1                        1
#define     D_WelcomePaUpdate_Len_1                     1
#define     D_PaHeightSoftStopCnt_Len_1                 1

#define     D_PaLengthSoftStopCnt_Len_1                 1
#define     D_PaBackSoftStopCnt_Len_1                   1
#define     D_PaFrontSoftStopCnt_Len_1                  1
#define     D_DrHeatFlg_Len_1                           1
#define     D_DrVentFlg_Len_1                           1
#define     D_PaHeatFlg_Len_1                           1
#define     D_PaVentFlg_Len_1                           1
#define     D_TestMode_Len_1                            1
#define     D_DrDoorSts_Len_1                           1
#define     D_PaDoorSts_Len_1                           1
#define     D_TestMessageSendCfg_Len_1                  1

#define     D_SystemFunctionConfiguration_F1FA_Len_6    6
#define     D_UdsDidVinCode_Len_17                      17
#define     D_ECUManufactureData_Len_4                  4

#define     D_ECUHardwareVersion_Len_16                 16
#define     D_Reserved15_Len_3                          3

#define     D_PCBASerialNumber_Len_21                   21
#define     D_Reserved16_Len_2                          2

#define     D_BoardPowerOnTypeAndCnt_Len_15             15

#define     D_Dtc_Index0_Len_3                          3
#define     D_Dtc_Index1_Len_3                          3
#define     D_Dtc_Index2_Len_3                          3
#define     D_Dtc_Index3_Len_3                          3
#define     D_Dtc_Index4_Len_3                          3

#define     D_Dtc_Index5_Len_3                          3
#define     D_Dtc_Index6_Len_3                          3
#define     D_Dtc_Index7_Len_3                          3
#define     D_Dtc_Index8_Len_3                          3
#define     D_Dtc_Index9_Len_3                          3

#define     D_Dtc_Index10_Len_3                         3
#define     D_Dtc_Index11_Len_3                         3
#define     D_Dtc_Index12_Len_3                         3
#define     D_Dtc_Index13_Len_3                         3
#define     D_Dtc_Index14_Len_3                         3

#define     D_Dtc_Index15_Len_3                         3
#define     D_Dtc_Index16_Len_3                         3
#define     D_Dtc_Index17_Len_3                         3
#define     D_Dtc_Index18_Len_3                         3
#define     D_Dtc_Index19_Len_3                         3

#define     D_Dtc_Index20_Len_3                         3
#define     D_Dtc_Index21_Len_3                         3
#define     D_Dtc_Index22_Len_3                         3
#define     D_Dtc_Index23_Len_3                         3
#define     D_Dtc_Index24_Len_3                         3

#define     D_Dtc_Index25_Len_3                         3
#define     D_Dtc_Index26_Len_3                         3
#define     D_Dtc_Index27_Len_3                         3
#define     D_Dtc_Index28_Len_3                         3
#define     D_Dtc_Index29_Len_3                         3

#define     D_Dtc_Index30_Len_3                         3
#define     D_Dtc_Index31_Len_3                         3
#define     D_Dtc_Index32_Len_3                         3
#define     D_Dtc_Index33_Len_3                         3
#define     D_Dtc_Index34_Len_3                         3

#define     D_Dtc_Index35_Len_3                         3
#define     D_Dtc_Index36_Len_3                         3
#define     D_Dtc_Index37_Len_3                         3
#define     D_Dtc_Index38_Len_3                         3
#define     D_Dtc_Index39_Len_3                         3

#define     D_Dtc_Index40_Len_3                         3
#define     D_Dtc_Index41_Len_3                         3
#define     D_Dtc_Index42_Len_3                         3
#define     D_Dtc_Index43_Len_3                         3
#define     D_Dtc_Index44_Len_3                         3

#define     D_Dtc_Index45_Len_3                         3
#define     D_Dtc_Index46_Len_3                         3
#define     D_Dtc_Index47_Len_3                         3
#define     D_Dtc_Index48_Len_3                         3
#define     D_Dtc_Index49_Len_3                         3

#define     D_Dtc_Index50_Len_3                         3
#define     D_Dtc_Index51_Len_3                         3
#define     D_Dtc_Index52_Len_3                         3
#define     D_Dtc_Index53_Len_3                         3
#define     D_Dtc_IndexMax_Len_3                        3






/************************写入常用函数声明************************/

/************************E2数据块配置参数表相关接口************************/
extern strEepromDataBlockCfgTable * Eel_GetE2DataBlockCfgTablePtr(void);
extern INT16U Srvl_GetE2DataBlockCfgTableLength(void);
extern void Srvl_SetE2DataBlockOptResult(INT16U DataId, enE2promOptResult Result);
extern enE2promOptResult Srvl_GetE2DataBlockOptResult(INT16U DataId);
extern void Srvl_SetE2DataBlockOptReq(INT16U DataId, EepromOptReq Req);
extern EepromOptReq Srvl_GetE2DataBlockEepOptReq(INT16U DataId);
extern INT8U * Srvl_GetE2DataBlockBufferPtr(INT16U DataId);
extern INT8U Srvl_GetE2DataBlockLength(INT16U DataId);
extern INT32U Srvl_GetE2DataBlockStartAddr(INT16U DataId);
extern INT16U Srvl_GetE2DataBlockBackUpID(INT16U DataId);
extern void Srvl_SetE2DataBlockPreWriteFlg(INT16U DataId, INT8U PreWriteFlg);
extern INT8U Srvl_GetE2DataBlockPreWriteFlg(INT16U DataId);
/************************E2自定义枚举参数表相关接口************************/
extern strEepromDataDefineTable * Eel_GetE2DataDefineTablePtr(void);
extern INT16U Srvl_GetE2DataDefineTableLength(void);
extern INT16U Srvl_GetE2DefineDataBlockID(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineLen(enSrvMemIndex MemIndex);
extern INT8U Srvl_GetE2DefineStartOffset(enSrvMemIndex MemIndex);
extern INT16U Srvl_GetUseDataBlockID(INT16U Index);
extern INT16U Srvl_GetUseDataBlockIDNoBackUp(INT16U Index);

#endif
