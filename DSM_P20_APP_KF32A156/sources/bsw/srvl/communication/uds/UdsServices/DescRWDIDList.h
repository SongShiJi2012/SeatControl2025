/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescRWDIDList.h
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


#ifndef _RWDIDLIST_H_
#define _RWDIDLIST_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "Common.h"
#include "Srvl_E2Cfg_Generation.h"
#include "Srvl_E2cfg.h"
#ifndef     RWDID_GLOBALS
#define     RWDID_EXT   
#else
#define     RWDID_EXT   extern
#endif


typedef enum
{
    eDID_W,
    eDID_R,
}eDIDOP_TYPE;

/* DID Memory Manage */
#define D_FINGERPRINT_NUM                   7U
#define D_FINGERPRINT_LEN                   9U
#define D_VIN_SIZE                          17U

#define D_VEHICLE_CFG_LEN					6U  //车辆配置数据长度

#define D_DriverSeat                        (0U)
#define D_PassengerSeat                     (1U)
/************************PID Relational Definition********************************/



/************************LID Relational Definition********************************/
#define		GetDatBufAndLen(pt)					(pt),	UBOUND(pt)

typedef struct
{
    INT8U             SessionAllow;
    INT8U             SecuAcesReq;
    void                (*ServiceProcess)(void);
}tR_DID_INFO;

typedef struct
{
    INT8U             	SessionAllow;
    //Desc_enSecLvl		MinRequiredLvl; /*需要通过的安全级别*/
    INT8U 				MinRequiredLvl; /*需要通过的安全级别*/ 
    void                (*ServiceProcess)(void);
}tW_DID_INFO;

typedef struct
{
    INT16U            sDID;
    tR_DID_INFO         ReadDIDInfo;
    tW_DID_INFO         WriteIDInfo;
}tDESC_DID_INFO;

typedef struct UDS_DID_DATA_TABLE_T
{
    INT16U       DidIndex;
    INT8U*              pDidBuf;
    INT16U              DidDatLen;
}UdsDidDataTbl_t;

typedef struct
{
    INT8U   DrAdjust                    : 2; //主驾座椅调节
    INT8U   PaAdjust         			: 1; //副驾座椅调节
    INT8U   DrHeatVent           		: 1; //主驾座椅通风加热
    INT8U	DrMemory					: 1; //主驾记忆迎宾功能
    INT8U   PaHeatVent         			: 1; //副驾座椅通风加热
    INT8U	PaMemory					: 1; //副驾记忆迎宾功能
    INT8U   seatMassage         		: 1; //座椅按摩
	
    INT8U   DrHeatFlg           		: 1; //主驾座椅加热
    INT8U   DrVentFlg           		: 1; //主驾座椅通风
    INT8U   PaHeatFlg         			: 1; //副驾座椅加热
    INT8U   PaVentFlg         			: 1; //副驾座椅通风
    INT8U   Resvd1                      : 4;
    
    INT8U   Resvd2                      :8;
    INT8U   Resvd3                      :8;
    INT8U   Resvd4                      :8;
    INT8U   Resvd5                      :8;

}DSMHumanInterface_stObj;  //人机交互

typedef union
{
    INT8U Byte[D_VEHICLE_CFG_LEN];
    DSMHumanInterface_stObj Bits;
}AppRAM_unDSMHumanInterface_Obj;  //人机交互;

typedef enum
{
	DSM_enmDEF,
	DSM_enmPowerON,
	DSM_enmDiagRead,
	DSM_enmDiagWrite,
	DSM_enmSleepWrite,
}DSM_enHumanInterRAMOP;


#define   tRWDID_INFO  struct stRWDID

#define D_PIN_AUTH_FAIL_LIMIT_TIME		(3U)
#define	PINCodeMatchFlgSet(Flg)		(gPINCodeMatchFlg = Flg)
#define	PINCodeMatchFlgGet()		(gPINCodeMatchFlg)

extern INT8U gPINCodeMatchFlg;	//PIN验证状态标志
extern INT8U g_u8PINCodeAuthFailCnt;	//PIN验证失败次数记录

extern const INT8U cFZBSWVersionNumber[16];


RWDID_EXT void   DIDReadRamDataComm(const INT8U* pDat, INT8U DatLen);
RWDID_EXT void   DIDWriteEepromDataComm(enSrvMemIndex MemIndex, INT8U* pDat,	INT8U DatLen);
RWDID_EXT void DIDWriteRamDataComm(INT8U* ptru8data, INT8U len);



#if (SID22_READDID_EN == DESC_ENABLE) ||(SID2E_WRITEDID_EN == DESC_ENABLE)
RWDID_EXT void DescReadDataByIdentifier(void);
RWDID_EXT void DescWriteDataByIdentifier(void);
#endif
/***********************************************************************************************
 * @function name:  ClearDiagConfigChangeFlagFunction
 *
 * @description:    将F101改变标志位延时50ms清零
 *
 * @input parameters:    void
 *
 * @output parameters:     void
 *
 * @return:         void
 *
 * @note:           需要在10ms任务调度周期内执行
 *
 * @author:         Prima Niu
 *
 * @date:           2023.6.19 19:33
 ***********************************************************************************************/
void ClearDiagConfigChangeFlagFunction(void);

/***********************************************************************
 * @function name: GetDiagConfigChangeFlagFunc
 * 
 * @description:获取配置改变标志位
 * 
 * @input parameters:  主副驾类型Type : 0x0:Driver 0x01:Passenger;
 * 
 * @output parameters: 配置改变标志位
 * 
 * @return: 无
 * 
 * @note: 配置改变标志位:TRUE-改变;FALSE-不改变
 * 
 * @author: Prima Niu
 * 
 * @date: 2023-06-19 16:33
 ***********************************************************************/
INT8U GetDiagConfigChangeFlagFunc(INT8U Type);
extern void DiagSetSwHeatTimer(INT32U Timer);
extern INT32U DiagGetSwHeatTimer(void);

#ifdef __cplusplus
}
#endif
 
#endif  /*_RWDIDLIST_H_*/

