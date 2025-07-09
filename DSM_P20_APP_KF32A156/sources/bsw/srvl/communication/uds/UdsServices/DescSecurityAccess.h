/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescSecurityAccess.h
** Last modified Date:      2013.10.23
** Last Version:            V1.0
** Description:             安全访问
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven 莫松文
** Created date:            2013.10.23
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

#ifndef _DESCSECURITYACCESS_H_
#define _DESCSECURITYACCESS_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		DESCSA_GLOBALS 
#define		SECACES_EXT 
#else
#define		SECACES_EXT        extern
#endif


SECACES_EXT void DescSecurityAccess(void);
SECACES_EXT void AppDescSecurityAccessRequestSeed(INT8U u1tNotRepeatReqFlg);
SECACES_EXT void AppDescSecurityAccessServerAlreadyUnlock(void);
SECACES_EXT void AppDescSecurityAccessSendKey(void); 
 
#ifdef __cplusplus
}
#endif
 
#endif  /*_DESCSECURITYACCESS_H_*/

