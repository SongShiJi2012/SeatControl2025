/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescConfig.h
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             ’Ô∂œ≈‰÷√Œƒº˛
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven ƒ™À…Œƒ
** Created date:            2013.10.23
** Version:                 V1.0
** Descriptions:            The original version ≥ı º∞Ê±æ
** 
**------------------------------------------------------------------------------------------ 
** Modified By:             
** Modified date:           
** Version:                 
** Description:             
** 
********************************************************************************************/

#ifndef _DESCCFG_H_
#define _DESCCFG_H_
#ifdef __cplusplus
 extern "C" {
#endif
#include  "Common.h"
#include "TP.h"
#include "Desc.h"
#include "AppDesc.h"
#include "CANDrv.h"
#include "CANDrvMSCAN.h"
#include  "DSM.h"

typedef enum
{
    TST_PhysicalReq,
    TST_FunctionalReq,
    eRX_NM,
}eRX_DESC_TYPE;

/* CAN ID */
#define         DESC_REQID_PHY                     				(kPhysReqSID)
#define         DESC_RSPID                       				(kPhysResSID)
#define         DESC_REQID_FUC                     				(kFuncReqSID)
                                                                                                                                                        
#define         DESC_ENABLE                                         1U
#define         DESC_DISABLE                                        0U

#define         SID14_CLRDESCINFO_EN                                DESC_ENABLE
#define         SID19_RDDTCINFO_EN                                  DESC_ENABLE
#define         SID22_READDID_EN                                    DESC_ENABLE
#define         SID27_SECURITYACCESS_EN                             DESC_ENABLE
#define         SID28_COMCTL_EN                                     DESC_ENABLE
#define         SID2E_WRITEDID_EN                                   DESC_ENABLE
#define         SID2F_IOCTRL_EN                                     DESC_ENABLE
#define         SID31_ROUTINECTRL_EN                                DESC_ENABLE
#define         SID34_REQDWNLOAD_EN                                 DESC_ENABLE
#define         SID36_TRANFDATA_EN                                  DESC_ENABLE
#define         SID37_TRANFEXIT_EN                                  DESC_ENABLE
#define         SID85_CTRLDTCSET_EN                                 DESC_ENABLE
#define         SID2A_PERIOD_DID_SERVICES                           DESC_ENABLE
#define         SID23_READ_MEMORY_BY_ADDR                           DESC_ENABLE





    
#if (SID14_CLRDESCINFO_EN == DESC_ENABLE)
#include "DescClearDiagnosticInformation.h"
#endif

#if (SID19_RDDTCINFO_EN == DESC_ENABLE)
#include "DescReadDTCInfo.h"
#endif

#if (SID22_READDID_EN == DESC_ENABLE)||(SID2E_WRITEDID_EN == DESC_ENABLE)
#include "DescRWDIDList.h"
#include "DescRWLIDList.h"
#endif

#if (SID27_SECURITYACCESS_EN == DESC_ENABLE)
#include "DescSecurityAccess.h"
#endif

#if (SID28_COMCTL_EN == DESC_ENABLE)
#include "DescComCtrl.h"
#endif

#if (SID2F_IOCTRL_EN == DESC_ENABLE)
#include "DescIOCtrolList.h"
#endif

#if (SID31_ROUTINECTRL_EN == DESC_ENABLE)
#include "DescRoutineCtlList.h"
#endif

#if (SID34_REQDWNLOAD_EN == DESC_ENABLE)
#include "DescReqDownload.h"
#endif

#if (SID36_TRANFDATA_EN == DESC_ENABLE)
#include "DescTransferData.h"
#endif

#if (SID37_TRANFEXIT_EN == DESC_ENABLE)
#include "DescReqTransfeExit.h"
#endif

#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
#include "DescControlDTCSetting.h"
#endif



 
 
#ifdef __cplusplus
}
#endif
 
#endif  /*_DESCCFG_H_*/

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

