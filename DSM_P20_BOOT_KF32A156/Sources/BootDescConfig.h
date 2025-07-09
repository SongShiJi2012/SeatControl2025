/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD.
**
**                           http://www.fzb.com.cn
**--------------File Info-------------------------------------------------------------------
** File Name:               BootDescConfig.h
** Last modified Date:      2014.1.26
** Last Version:            V1.0
** Description:             Boot诊断配置文件
**
**------------------------------------------------------------------------------------------
** Created By:              Michael
** Created date:            2014.1.26
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

#ifndef _BOOTDESCCFG_H_
#define _BOOTDESCCFG_H_
#ifdef __cplusplus
extern "C" {
#endif


typedef void (* BootDescFuncType)(void);



typedef 		unsigned  char						  BOOT_BOOL;
typedef 		unsigned  char						  BOOT_U8;
typedef 		unsigned  short 					  BOOT_U16;
typedef 		unsigned  long						  BOOT_U32;
typedef 		signed  char						  BOOT_S8;
typedef 		signed  short 					  	  BOOT_S16;
typedef 		signed  long						  BOOT_S32;



/* CAN ID */
#define         BOOTDESC_REQID_PHY                          (0x636)
#define         BOOTDESC_REQID_FUC                          (0x600)
#define         BOOTDESC_RSPID                              (0x637)



#define         BOOTDESC_ENABLE                                         1U
#define         BOOTDESC_DISABLE                                        0U

#define         BOOTSID14_CLRDESCINFO_EN                                BOOTDESC_DISABLE
#define         BOOTSID19_RDDTCINFO_EN                                  BOOTDESC_DISABLE
#define         BOOTSID22_READDID_EN                                    BOOTDESC_ENABLE
#define         BOOTSID27_SECURITYACCESS_EN                             BOOTDESC_ENABLE
#define         BOOTSID28_COMCTL_EN                                     BOOTDESC_ENABLE
#define         BOOTSID2E_WRITEDID_EN                                   BOOTDESC_ENABLE
#define         BOOTSID2F_IOCTRL_EN                                     BOOTDESC_DISABLE
#define         BOOTSID31_ROUTINECTRL_EN                                BOOTDESC_ENABLE
#define         BOOTSID34_REQDWNLOAD_EN                                 BOOTDESC_ENABLE
#define         BOOTSID36_TRANFDATA_EN                                  BOOTDESC_ENABLE
#define         BOOTSID37_TRANFEXIT_EN                                  BOOTDESC_ENABLE
#define         BOOTSID85_CTRLDTCSET_EN                                 BOOTDESC_ENABLE









#ifdef __cplusplus
}
#endif

#endif  /*_BOOTDESCCFG_H_*/

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/

