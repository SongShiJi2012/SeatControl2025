/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescClearAllDTCInformation.h
** Last modified Date:      2013.10.24
** Last Version:            V1.0
** Description:             ��������Ϣ
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven Ī����
** Created date:            2013.10.24
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
** 
**------------------------------------------------------------------------------------------ 
** Modified By:             
** Modified date:           
** Version:                 
** Description:             
** 
********************************************************************************************/

#ifndef _DESCCLRDESCINFO_H_
#define _DESCCLRDESCINFO_H_
#ifdef __cplusplus
 extern "C" {
#endif
 
#ifdef		CLRDESCINFO_GLOBALS 
#define		CLRDESCINFO_EXT 
#else
#define		CLRDESCINFO_EXT        extern
#endif


CLRDESCINFO_EXT void DescClearAllDTCInformation(void);
 
CLRDESCINFO_EXT void DescClearDiagnosticInformation(void);
 
#ifdef __cplusplus
}
#endif
 
#endif  /*_DESCCLRDESCINFO_H_*/

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/


