/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescControlDTCSetting.h
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             DTC控制设置
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven 莫松文
** Created date:            2013.10.24
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
#ifndef _DESCDTCCTLSET_H_
#define _DESCDTCCTLSET_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		DTCCTLSET_GLOBALS 
#define		DTCCTLSET_EXT 
#else
#define		DTCCTLSET_EXT        extern
#endif



#if (SID85_CTRLDTCSET_EN == DESC_ENABLE)
DTCCTLSET_EXT void DescControlDTCSetting(void);
#endif 
 
#ifdef __cplusplus
}
#endif
 
#endif  /*_DESCDTCCTLSET_H_*/

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/
  


