/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               DescRWLIDList.h
** Last modified Date:      2013.10.19
** Last Version:            V1.0
** Description:             DID列表
**
**------------------------------------------------------------------------------------------
** Created By:              Kenven 莫松文
** Created date:            2013.10.19
** Version:                 V1.0
** Descriptions:            The original version 初始版本
**
**------------------------------------------------------------------------------------------
** Modified By:
** Modified date:
** Version:
** Description:
**
********************************************************************************************/


#ifndef _RWLIDLIST_H_
#define _RWLIDLIST_H_

#include "Common.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifndef     RWLID_GLOBALS
#define     RWLID_EXT
#else
#define     RWLID_EXT   extern
#endif

#define     __LIDNOTSUPPORTWRITE           0,Desc_enmSecExtLvl,NULL
#define		__LIDNOTSUPPORTREAD			   0,FALSE,NULL

extern INT8U GetMassageDiagTime(INT8U Index);

extern void DescDID_Read_DriverSeatState(void);
extern void DescDID_Read_PassengerSeatState(void);
extern void DescDID_Read_BoardModuleGetInitRlt(void);
extern void DescDID_Read_BoardPowerOnCnt(void);
extern void DescDID_Read_OSAllTaskRunCnt(void);
extern void DescDID_Read_CycleMaxRunTime(void);
extern void DescDID_Read_McuWakeupSource(void);



extern void DescDID_Read_FZBECUSoftwareNumber(void);
extern void DescDID_Read_FZBSWVersionNumber(void);
extern void DescDID_Read_FZBHardwareNumber(void);
extern void DescDID_Read_FZBHardwareVersion(void);
extern void DescDID_Read_FZBBootVersion(void);


extern void DescDID_Read_AdcUpMidLowRangeChl0(void);
extern void DescDID_Read_AdcUpMidLowRangeChl1(void);
extern void DescDID_Read_AdcUpMidLowRangeChl2(void);
extern void DescDID_Read_AdcUpMidLowRangeChl3(void);
extern void DescDID_Read_AdcUpMidLowRangeChl4(void);

extern void DescDID_Read_AdcUpMidLowRangeChl5(void);
extern void DescDID_Read_AdcUpMidLowRangeChl6(void);
extern void DescDID_Read_AdcUpMidLowRangeChl7(void);
extern void DescDID_Read_AdcUpMidLowRangeChl8(void);
extern void DescDID_Read_AdcUpMidLowRangeChl9(void);

extern void DescDID_Read_AdcUpMidLowRangeChl10(void);
extern void DescDID_Read_AdcUpMidLowRangeChl11(void);
extern void DescDID_Read_AdcUpMidLowRangeChl12(void);
extern void DescDID_Read_AdcUpMidLowRangeChl13(void);
extern void DescDID_Read_AdcUpMidLowRangeChl14(void);

extern void DescDID_Read_AdcUpMidLowRangeChl15(void);
extern void DescDID_Read_AdcUpMidLowRangeChl16(void);
extern void DescDID_Read_AdcUpMidLowRangeChl17(void);
extern void DescDID_Read_AdcUpMidLowRangeChl18(void);
extern void DescDID_Read_AdcUpMidLowRangeChl19(void);

extern void DescDID_Read_AdcUpMidLowRangeChl20(void);
extern void DescDID_Read_AdcUpMidLowRangeChl21(void);
extern void DescDID_Read_AdcUpMidLowRangeChl22(void);
extern void DescDID_Read_AdcUpMidLowRangeChl23(void);
extern void DescDID_Read_AdcUpMidLowRangeChl24(void);

extern void DescDID_Read_BtsHighDriverChipIsInfo(void);
extern void DescDID_Read_F222_DISwitchStatus(void);
extern void DescDID_Read_F223_AdSwitchStatus(void);
extern void DescDID_Read_3134_HallStatus(void);


void DescDID_Read_DescSleepNormalModeTimeout(void);
void DescDID_Write_DescSleepNormalModeTimeout(void);

void DescDID_Read_DescForceSleepNormalModeTimeout(void);
void DescDID_Write_DescForceSleepNormalModeTimeout(void);
extern INT8U DescDID_GetDescCfgTimeParaTemporary(INT8U u8Index);

#define D_DescSleepNormalModeTimeoutIndex				(0U) /* 进入休眠模式的时间*/
#define D_DescForceSleepNormalModeTimeoutIndex			(1U) /* 进入强制休眠模式的时间*/

#define D_AnalogThreshold								(1638U) /* 模拟量阈值 - 2V (暂定)*/

#define D_DescCfgTimeParaTemporaryArrayNum		(D_DescForceSleepNormalModeTimeoutIndex + 1U)

extern void DescDID_Read_EepromInBusyTs(void);
extern void DescDID_Read_EepromIndexOptRlt(void);
extern void DescDID_Read_HalEepromPara_ID10(void);
extern void DescDID_Read_HalEepromPara_ID11(void);
extern void DescDID_Read_HalEepromPara_ID12(void);
extern void DescDID_Read_HalEepromPara_ID13(void);
extern void DescDID_Read_HalEepromPara_ID14(void);
extern void DescDID_Read_HalEepromPara_ID15(void);
extern void DescDID_Read_HalEepromPara_ID16(void);
extern void DescDID_Read_HalEepromPara_ID17(void);
extern void DescDID_Read_HalEepromPara_ID18(void);
extern void DescDID_Read_HalEepromPara_ID19(void);
extern void DescDID_Read_HalEepromPara_ID20(void);
extern void DescDID_Read_HalEepromPara_ID21(void);
extern void DescDID_Read_HalEepromPara_ID22(void);
extern void DescDID_Read_HalEepromPara_ID23(void);
extern void DescDID_Read_HalEepromPara_ID24(void);
extern void DescDID_Read_HalEepromPara_ID25(void);
extern void DescDID_Read_HalEepromPara_ID26(void);
extern void DescDID_Read_HalEepromPara_ID27(void);
extern void DescDID_Read_HalEepromPara_ID28(void);
extern void DescDID_Read_HalEepromPara_ID29(void);
extern void DescDID_Read_HalEepromPara_ID30(void);
extern void DescDID_Read_HalEepromPara_ID31(void);
extern void DescDID_Read_HalEepromPara_ID32(void);
extern void DescDID_Read_HalEepromPara_ID33(void);
extern void DescDID_Read_HalEepromPara_ID34(void);
extern void DescDID_Read_HalEepromPara_ID35(void);
extern void DescDID_Read_HalEepromPara_ID36(void);
extern void DescDID_Read_HalEepromPara_ID37(void);
extern void DescDID_Read_HalEepromPara_ID38(void);
extern void DescDID_Read_HalEepromPara_ID39(void);

extern void DescDID_Read_HalEepromPara_ID10BackUp(void);
extern void DescDID_Read_HalEepromPara_ID11BackUp(void);
extern void DescDID_Read_HalEepromPara_ID12BackUp(void);
extern void DescDID_Read_HalEepromPara_ID13BackUp(void);
extern void DescDID_Read_HalEepromPara_ID14BackUp(void);
extern void DescDID_Read_HalEepromPara_ID15BackUp(void);
extern void DescDID_Read_HalEepromPara_ID16BackUp(void);
extern void DescDID_Read_HalEepromPara_ID17BackUp(void);
extern void DescDID_Read_HalEepromPara_ID18BackUp(void);
extern void DescDID_Read_HalEepromPara_ID19BackUp(void);
extern void DescDID_Read_HalEepromPara_ID20BackUp(void);
extern void DescDID_Read_HalEepromPara_ID21BackUp(void);
extern void DescDID_Read_HalEepromPara_ID22BackUp(void);
extern void DescDID_Read_HalEepromPara_ID23BackUp(void);
extern void DescDID_Read_HalEepromPara_ID24BackUp(void);
extern void DescDID_Read_HalEepromPara_ID25BackUp(void);
extern void DescDID_Read_HalEepromPara_ID26BackUp(void);
extern void DescDID_Read_HalEepromPara_ID27BackUp(void);
extern void DescDID_Read_HalEepromPara_ID28BackUp(void);
extern void DescDID_Read_HalEepromPara_ID29BackUp(void);
extern void DescDID_Read_HalEepromPara_ID30BackUp(void);
extern void DescDID_Read_HalEepromPara_ID31BackUp(void);
extern void DescDID_Read_HalEepromPara_ID32BackUp(void);
extern void DescDID_Read_HalEepromPara_ID33BackUp(void);
extern void DescDID_Read_HalEepromPara_ID34BackUp(void);
extern void DescDID_Read_HalEepromPara_ID35BackUp(void);
extern void DescDID_Read_HalEepromPara_ID36BackUp(void);
extern void DescDID_Read_HalEepromPara_ID37BackUp(void);
extern void DescDID_Read_HalEepromPara_ID38BackUp(void);
extern void DescDID_Read_HalEepromPara_ID39BackUp(void);

extern void DescDID_Read_HalEepromPara_ID100(void);
extern void DescDID_Read_HalEepromPara_ID101(void);
extern void DescDID_Read_HalEepromPara_ID102(void);
extern void DescDID_Read_HalEepromPara_ID103(void);
extern void DescDID_Read_HalEepromPara_ID104(void);
extern void DescDID_Read_HalEepromPara_ID105(void);
extern void DescDID_Read_HalEepromPara_ID106(void);
extern void DescDID_Read_HalEepromPara_ID107(void);
extern void DescDID_Read_HalEepromPara_ID108(void);
extern void DescDID_Read_HalEepromPara_ID109(void);
extern void DescDID_Read_HalEepromPara_ID110(void);
extern void DescDID_Read_HalEepromPara_ID111(void);
extern void DescDID_Read_HalEepromPara_ID112(void);
extern void DescDID_Read_HalEepromPara_ID113(void);
extern void DescDID_Read_HalEepromPara_ID114(void);
extern void DescDID_Read_HalEepromPara_ID115(void);
extern void DescDID_Read_HalEepromPara_ID116(void);
extern void DescDID_Read_HalEepromPara_ID117(void);
extern void DescDID_Read_HalEepromPara_ID118(void);
extern void DescDID_Read_HalEepromPara_ID119(void);

extern void DescDID_Read_Variable(void);
extern void DescDID_Set_Variable(void);
extern INT8U GetChecksumDisable(void);
extern void DescDID_FDB4_Read_CANchecksum(void);
extern void DescDID_FDB4_Write_CANchecksum(void);

extern void DescDID_Read_FE01_ConfigParameter(void);
extern void DescDID_Write_FE01_ConfigParameter(void);
extern void DescDID_Read_FE02_HeatTemp(void);
extern void DescDID_Read_FE03_VatAndMode(void);
extern void	DescDID_Read_FE04_OTASts(void);
extern void	DescDID_Read_FE05_HALLErr(void);
extern void DescDID_Read_FE06_Position(void);
extern void DescDID_Read_FE0E_MirrorPosition(void);
extern void DescDID_Read_FE08_WakeReason(void);
extern void DescDID_Read_FE09_PaPosition(void);
	
extern void DescDID_Read_FE0A_SendTestMsgFlg(void);
extern void DescDID_Write_FE0A_SendTestMsgFlg(void);

extern void DescDID_Read_FE0B_MotorMoveReason(void);

extern void DescDID_Read_FE0C_MotorMoveType(void);

extern void DescDID_Read_FE0D_MotorLearnInfo(void);

extern void DescDID_Write_FE07_BTS7040Tsk(void);
extern void DescDID_Read_FE07_BTS7040Tsk(void);

extern void DescDID_Read_FE0F_HardwareVersionTsk(void);
extern void DescDID_Write_FE0F_HardwareVersionTsk(void);
extern void DescDID_Read_FE10_TestMode(void);

extern void DescDID_Read_D000_FZBBootVersion(void);

extern void DescDID_Read_D001_ReadWriteHardwareFlg(void);
extern void DescDID_Write_D001_ReadWriteHardwareFlg(void);

extern void DescDID_Read_D003_ReadWritePCBASN(void);
extern void DescDID_Write_D003_ReadWritePCBASN(void);

extern void DescDID_Read_D004_TestMessageSendCfg(void);
extern void DescDID_Write_D004_TestMessageSendCfg(void);

extern void DescDID_Write_D005_HeatGearTemp(void);
extern void DescDID_Read_D005_HeatGearTemp(void);

extern void DescDID_Read_D006_DrMotorPositionInfo(void);
extern void DescDID_Write_D006_DrMotorPositionInfo(void);

extern void DescDID_Read_D007_PaMotorPositionInfo(void);

extern void DescDID_Read_D008_MassageTimeInfo(void);
extern void DescDID_Write_D008_MassageTimeInfo(void);

extern void DescDID_Read_D009_MassageACTInfo(void);

extern void DescDID_Read_D00A_VoltageInfo(void);

extern void DescDID_Read_D00B_VentGearPrecent(void);
extern void DescDID_Write_D00B_VentGearPrecent(void);

extern void DescDID_Read_D00C_SteerHeatTemp(void);
extern void DescDID_Write_D00C_SteerHeatTemp(void);

extern void DescDID_Read_D00D_DrMotorReason(void);
extern void DescDID_Read_D00E_PaMotorReason(void);
extern void DescDID_Read_D00F_VentHeatReason(void);
extern void DescDID_Read_D010_SoftStopFlg(void);
extern void DescDID_Read_D011_MotorPaStopInfo(void);
extern void DescDID_Read_D013_SwHeatTimeInfo(void);
extern void DescDID_Write_D013_SwHeatTimeInfo(void);
extern void DescDID_Read_D014_SwHeatMaxTimeInfo(void);
extern void DescDID_Write_D014_SwHeatMaxTimeInfo(void);
extern void DescDID_Read_D015_BoardTemp(void);
extern void DescDID_Read_D016_WelcomePosi(void);

extern void DescDID_C400_TEST_AD_LOOP(void);
extern void DescDID_C401_TEST_AD_SINGLE(void);
extern void DescDID_C402_TEST_VAR_DATA(void);
extern void DescDID_C403_TEST_9210X(void);
extern void DescDID_TEST_C4FF(void);

#define	RWLIDLIST		\
	{0xFD00, {SESN_SSS, FALSE,    DescDID_Read_DriverSeatState},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD01, {SESN_SSS, FALSE,	  DescDID_Read_PassengerSeatState},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD02, {SESN_SSS, FALSE,	  DescDID_Read_BoardModuleGetInitRlt},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD03, {SESN_SSS, FALSE,	  DescDID_Read_BoardPowerOnCnt},	  {__LIDNOTSUPPORTWRITE}},\
	{0xFD04, {SESN_SSS, FALSE,	  DescDID_Read_OSAllTaskRunCnt},	  {__LIDNOTSUPPORTWRITE}},\
	{0xFD08, {SESN_SSS, FALSE,	  DescDID_Read_CycleMaxRunTime},   {__LIDNOTSUPPORTWRITE}},\
	{0xFD09, {SESN_SSS, FALSE,	  DescDID_Read_McuWakeupSource},   {__LIDNOTSUPPORTWRITE}},\
	{0xFD0A, {SESN_SSS, FALSE,	  DescDID_Read_FZBECUSoftwareNumber},   {__LIDNOTSUPPORTWRITE}},\
	{0xFD0B, {SESN_SSS, FALSE,	  DescDID_Read_FZBSWVersionNumber},   {__LIDNOTSUPPORTWRITE}},\
	{0xFD0C, {SESN_SSS, FALSE,	  DescDID_Read_FZBHardwareNumber},   {__LIDNOTSUPPORTWRITE}},\
	{0xFD0D, {SESN_SSS, FALSE,	  DescDID_Read_FZBHardwareVersion},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD0E, {SESN_SSS, FALSE,	  DescDID_Read_FZBBootVersion},  {__LIDNOTSUPPORTWRITE}},\
	{0xFD10, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl0},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD11, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl1},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD12, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl2},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD13, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl3},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD14, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl4},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD15, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl5},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD16, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl6},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD17, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl7},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD18, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl8},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD19, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl9},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1A, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl10},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1B, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl11},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1C, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl12},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1D, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl13},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1E, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl14},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD1F, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl15},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD20, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl16},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD21, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl17},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD22, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl18},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD23, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl19},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD24, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl20},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD25, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl21},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD26, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl22},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD27, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl23},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD28, {SESN_SSS, FALSE,	  DescDID_Read_AdcUpMidLowRangeChl24},	 {__LIDNOTSUPPORTWRITE}},\
	{0xFD50, {SESN_SSS, FALSE,	  DescDID_Read_DescSleepNormalModeTimeout}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_DescSleepNormalModeTimeout}},\
	{0xFD51, {SESN_SSS, FALSE,	  DescDID_Read_DescForceSleepNormalModeTimeout}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_DescForceSleepNormalModeTimeout}},\
	{0xFD62, {SESN_SSS, FALSE,	  DescDID_Read_EepromInBusyTs},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD63, {SESN_SSS, FALSE,	  DescDID_Read_EepromIndexOptRlt},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD64, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID10},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD65, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID11},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD66, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID12},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD67, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID13},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD68, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID14},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD69, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID15},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6A, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID16},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6B, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID17},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6C, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID18},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6D, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID19},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6E, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID20},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD6F, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID21},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD70, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID22},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD71, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID23},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD72, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID24},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD73, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID25},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD74, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID26},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD75, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID27},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD76, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID28},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD77, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID29},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD78, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID30},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD79, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID31},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7A, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID32},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7B, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID33},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7C, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID34},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7D, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID35},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7E, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID36},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD7F, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID37},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD80, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID38},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD81, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID39},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD82, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID10BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD83, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID11BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD84, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID12BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD85, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID13BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD86, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID14BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD87, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID15BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD88, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID16BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD89, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID17BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8A, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID18BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8B, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID19BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8C, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID20BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8D, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID21BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8E, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID22BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD8F, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID23BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD90, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID24BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD91, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID25BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD92, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID26BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD93, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID27BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD94, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID28BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD95, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID29BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD96, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID30BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD97, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID31BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD98, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID32BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD99, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID33BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9A, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID34BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9B, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID35BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9C, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID36BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9D, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID37BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9E, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID38BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFD9F, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID39BackUp},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA0, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID100},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA1, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID101},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA2, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID102},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA3, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID103},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA4, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID104},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA5, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID105},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA6, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID106},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA7, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID107},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA8, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID108},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDA9, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID109},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAA, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID110},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAB, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID111},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAC, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID112},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAD, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID113},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAE, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID114},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDAF, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID115},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDB0, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID116},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDB1, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID117},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDB2, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID118},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDB3, {SESN_SSS, FALSE,	  DescDID_Read_HalEepromPara_ID119},    {__LIDNOTSUPPORTWRITE}},\
	{0xFDB4, {SESN_SSS, FALSE,	  DescDID_FDB4_Read_CANchecksum}, {SESN_ES, Desc_enmSecNonLvl, DescDID_FDB4_Write_CANchecksum}},\
	{0xFDFF, {__LIDNOTSUPPORTREAD},	{__LIDNOTSUPPORTWRITE}}
	

#define	RWLIDFZBLIST	\
	{0xD000, {SESN_SSS, FALSE,	  DescDID_Read_D000_FZBBootVersion}, {__LIDNOTSUPPORTWRITE}},\
	{0xD001, {SESN_DES, FALSE,	  DescDID_Read_D001_ReadWriteHardwareFlg}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D001_ReadWriteHardwareFlg}},\
	{0xD002, {SESN_SSS, FALSE,	  DescDID_Read_FZBECUSoftwareNumber}, {__LIDNOTSUPPORTWRITE}},\
	{0xD003, {SESN_DES, FALSE,	  DescDID_Read_D003_ReadWritePCBASN}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D003_ReadWritePCBASN}},\
	{0xD004, {SESN_DES, FALSE,	  DescDID_Read_D004_TestMessageSendCfg}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D004_TestMessageSendCfg}},\
	{0xD005, {SESN_DES, FALSE,	  DescDID_Read_D005_HeatGearTemp}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D005_HeatGearTemp}},\
	{0xD006, {SESN_DES, FALSE,	  DescDID_Read_D006_DrMotorPositionInfo}, {SESN_DES, Desc_enmSecNonLvl, DescDID_Write_D006_DrMotorPositionInfo}},\
	{0xD007, {SESN_DES, FALSE,	  DescDID_Read_D007_PaMotorPositionInfo}, {__LIDNOTSUPPORTWRITE}},\
	{0xD008, {SESN_DES, FALSE,	  DescDID_Read_D008_MassageTimeInfo}, {SESN_DES, Desc_enmSecNonLvl,DescDID_Write_D008_MassageTimeInfo}},\
	{0xD009, {SESN_DES, FALSE,	  DescDID_Read_D009_MassageACTInfo}, {__LIDNOTSUPPORTWRITE}},\
	{0xD00A, {SESN_DES, FALSE,	  DescDID_Read_D00A_VoltageInfo}, {__LIDNOTSUPPORTWRITE}},\
	{0xD00B, {SESN_DES, FALSE,	  DescDID_Read_D00B_VentGearPrecent}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D00B_VentGearPrecent}},\
	{0xD00C, {SESN_DES, FALSE,	  DescDID_Read_D00C_SteerHeatTemp}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D00C_SteerHeatTemp}},\
	{0xD00D, {SESN_DES, FALSE,	  DescDID_Read_D00D_DrMotorReason}, {__LIDNOTSUPPORTWRITE}},\
	{0xD00E, {SESN_DES, FALSE,	  DescDID_Read_D00E_PaMotorReason}, {__LIDNOTSUPPORTWRITE}},\
	{0xD00F, {SESN_DES, FALSE,	  DescDID_Read_D00F_VentHeatReason}, {__LIDNOTSUPPORTWRITE}},\
	{0xD010, {SESN_DES, FALSE,	  DescDID_Read_D010_SoftStopFlg}, {__LIDNOTSUPPORTWRITE}},\
	{0xD011, {SESN_DES, FALSE,	  DescDID_Read_D011_MotorPaStopInfo}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D00B_VentGearPrecent}},\
	{0xD013, {SESN_DES, FALSE,	  DescDID_Read_D013_SwHeatTimeInfo}, {__LIDNOTSUPPORTWRITE}},\
	{0xD014, {SESN_DES, FALSE,	  DescDID_Read_D014_SwHeatMaxTimeInfo}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_D014_SwHeatMaxTimeInfo}},\
	{0xD015, {SESN_DES, FALSE,	  DescDID_Read_D015_BoardTemp}, {__LIDNOTSUPPORTWRITE}},\
	{0xD016, {SESN_DES, FALSE,	  DescDID_Read_D016_WelcomePosi}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE00, {SESN_SSS, FALSE,	  DescDID_Read_Variable}, {SESN_ES, Desc_enmSecNonLvl, DescDID_Set_Variable}},\
	{0xFE01, {SESN_SSS, FALSE,	  DescDID_Read_FE01_ConfigParameter}, {SESN_ES, Desc_enmSecNonLvl, DescDID_Write_FE01_ConfigParameter}},\
	{0xFE02, {SESN_DES, FALSE,	  DescDID_Read_FE02_HeatTemp}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE03, {SESN_DES, FALSE,	  DescDID_Read_FE03_VatAndMode}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE04, {SESN_DES, FALSE,	  DescDID_Read_FE04_OTASts}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE05, {SESN_DES, FALSE,	  DescDID_Read_FE05_HALLErr}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE06, {SESN_DES, FALSE,	  DescDID_Read_FE06_Position}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE07, {SESN_SSS, FALSE,	  DescDID_Read_FE07_BTS7040Tsk},	{SESN_ES, Desc_enmSecNonLvl,DescDID_Write_FE07_BTS7040Tsk}},\
	{0xFE08, {SESN_DES, FALSE,	  DescDID_Read_FE08_WakeReason}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE09, {SESN_DES, FALSE,	  DescDID_Read_FE09_PaPosition}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE0A, {SESN_SSS, FALSE,	  DescDID_Read_FE0A_SendTestMsgFlg}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_FE0A_SendTestMsgFlg}},\
	{0xFE0B, {SESN_SSS, FALSE,	  DescDID_Read_FE0B_MotorMoveReason}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE0C, {SESN_SSS, FALSE,	  DescDID_Read_FE0C_MotorMoveType}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE0D, {SESN_SSS, FALSE,	  DescDID_Read_FE0D_MotorLearnInfo}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE0E, {SESN_DES, FALSE,	  DescDID_Read_FE0E_MirrorPosition}, {__LIDNOTSUPPORTWRITE}},\
	{0xFE0F, {SESN_DES, FALSE,	  DescDID_Read_FE0F_HardwareVersionTsk}, {SESN_ES, Desc_enmSecExtLvl, DescDID_Write_FE0F_HardwareVersionTsk}},\
    {0xFE10, {SESN_DES, FALSE,    DescDID_Read_FE10_TestMode}, {__LIDNOTSUPPORTWRITE}}

#define	D_UDS_PERIOD_DID_LIST	\
{0xF221, {SESN_SSS, FALSE,DescDID_Read_BtsHighDriverChipIsInfo}, {__LIDNOTSUPPORTWRITE}},\
{0xF222, {SESN_SSS, FALSE,DescDID_Read_F222_DISwitchStatus}, {__LIDNOTSUPPORTWRITE}},\
{0xF223, {SESN_SSS, FALSE,DescDID_Read_F223_AdSwitchStatus}, {__LIDNOTSUPPORTWRITE}},\
{0x3134, {SESN_SSS, FALSE,DescDID_Read_3134_HallStatus}, {__LIDNOTSUPPORTWRITE}}

//测试报文专用 - C4xx
#define	D_TEST_C4_DID_LIST	\
	{0xC400, {SESN_SSS, FALSE,DescDID_C400_TEST_AD_LOOP}, {__LIDNOTSUPPORTWRITE}},\
	{0xC401, {SESN_SSS, FALSE,DescDID_C401_TEST_AD_SINGLE}, {__LIDNOTSUPPORTWRITE}},\
	{0xC402, {SESN_SSS, FALSE,DescDID_C402_TEST_VAR_DATA}, {__LIDNOTSUPPORTWRITE}},\
	{0xC403, {SESN_SSS, FALSE,DescDID_C403_TEST_9210X}, {__LIDNOTSUPPORTWRITE}},\
	{0xC4FF, {SESN_SSS, FALSE,DescDID_TEST_C4FF}, {__LIDNOTSUPPORTWRITE}}
#ifdef __cplusplus
}
#endif

#endif  /*_RWLIDLIST_H_*/

