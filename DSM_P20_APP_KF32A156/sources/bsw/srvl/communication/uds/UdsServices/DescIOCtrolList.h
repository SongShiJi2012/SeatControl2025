/****************************Copyright (c)**************************************************
**                      Fuxin Dare Automotive Parts Co.,LTD. 
** 
**                           http://www.fzb.com.cn 
**--------------File Info------------------------------------------------------------------- 
** File Name:               DescIOCtrolList.h
** Last modified Date:      2013.10.21
** Last Version:            V1.0
** Description:             IOCtrol�б� 
** 
**------------------------------------------------------------------------------------------ 
** Created By:              Kenven Ī����
** Created date:            2013.10.21
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
#ifndef DESCIOCTLLIST_H
#define DESCIOCTLLIST_H

#include  "Common.h"
#include "Srvl_Tle9210x.h"
#include "Appl_PowerMangeModel.h"
#include "Appl_DrMemory_CtrlModel.h"




#ifdef		IOCTLLIST_GLOBALS 
#define		IOCTLLIST_EXT 
#else
#define		IOCTLLIST_EXT        extern
#endif



/* IO�������� */
typedef enum
{
    eIOCTL_RETURNCTL2ECU        = 0x00,
    eIOCTL_RST2DEF              = 0x01,
    eIOCTL_FRZCURSTA            = 0x02,
    eIOCTL_SHOTTERMADJ          = 0x03,
}eIOCTL_TYPE;

typedef struct 
{
    INT16U            sCID;
    INT8U             SessionAllow;
    INT8U			  sShortTeamDJLen;
    void                (*ServiceProcess)(eIOCTL_TYPE eIOCtlType); 
}tDESC_IOCTL_INFO;   



//Use for IO Control--------------------------------------------
typedef enum
{
	eIOCTL_INACTIVE,
	eIOCTL_ACTIVE,
}eIOCTL_ACTVIE_TYPE;


typedef enum
{
	DescIOCtl_enOutput_OFF,
	DescIOCtl_enOutput_ON,
}DescIOCtl_enCtrlOutputSts;




typedef struct
{
 
   //2019.6.14 hfj
	INT8U SeatHeightUpDn				:1;
	INT8U SeatLengthFdBk				:1;
	INT8U SeatBackrestFdBk				:1;
	INT8U SeatHeadrestUpDn				:1;
	INT8U SeatFrontHeightUpDn			:1;
	INT8U SeatcushionLengthFdBk		    :1;
	INT8U SteeringWheelUpDn				:1;
	INT8U SteeringWheelFdBk				:1;
	
	INT8U ERVMRMirrorLFRT				:1;
	INT8U ERVMRMirrorUPDN				:1;
	INT8U ERVMLMirrorLFRT				:1;
	INT8U ERVMLMirrorUPDN				:1;
	INT8U reserved				        :4;
	
}DescIOCtl_stIOCtrlStInfoBits;

typedef union
{
	INT8U HlfWord[2];
	DescIOCtl_stIOCtrlStInfoBits Bits;
}DescIOCtl_unIOCtrlStInfo;

typedef enum
{
	DescIOCtl_enCtrlOutputStOFF,
	DescIOCtl_enCtrlOutputStON,
}DescIOCtl_enCtrlOutputSt;
	


typedef enum
{
	EN_DRHEIGHT = 0,	//���ݸ߶�
	EN_DRLENGTH,	//��������
	EN_DRBACKREST,	//���ݿ���
	EN_DRCUSHION,	//��������
//	EN_PAHEIGHT,	//���ݸ߶�
	EN_PALENGTH,	//��������
	EN_PABACKREST,	//���ݿ���
//	EN_PACUSHION,	//��������
	EN_DRHEAT,		//���ݼ���
	EN_PAHEAT,		//���ݼ���
	EN_DRVENTILATE,		//����ͨ��
	EN_PAVENTILATE,		//����ͨ��
	EN_WHEEL,		//�����̼���
	EN_MAX,
}enIOCtrlPram;

#define D_DescIOCtrlItemNum			(EN_MAX)
#define D_DescShortTermAdjustment	(1U)
#define D_DescIOCtrlAllItemNum	(3U)
typedef struct
{
	INT8U DescFlag;
	INT8U OutputCtrl;
	INT8U OutputItemCtrl[D_DescIOCtrlItemNum];
	INT8U OutputCtrlMask[D_DescIOCtrlItemNum];
}strDescIOCtrlOutputInfo;

#define D_DescIOCtrlOutputInfo_Num		(EN_MAX)
#define D_DescIOCtrlOutputInfo_50A8     (1U)
#define D_DescIOCtrlOutputInfo_D500		(0)




IOCTLLIST_EXT void DescInputOutputControlByIdentifier(void);


/**************************  IO Control Define  ***********************/

INT8U Desc_DiagOutCtrlIsValid(INT8U u8index);
void Desc_DiagSetOutCtrlIsValid(INT8U u8index, eIOCTL_ACTVIE_TYPE flg);
INT8U Desc_DiagOutCtrlPram(INT8U u8index);
void Desc_DiagSetOutCtrlPram(INT8U u8index,INT8U pram);
void UdsIOCtrl_SessionChangedToDefault(void);

void DescIOCtrl_DrSeatMoveTask(void);
void DescIOCtrl_PaSeatMoveTask(void);



/**************************  IO Control Define  ***********************/






 
#endif  /*_DESCIOCTLLIST_H_*/

