/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_flash.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file provides the Flash function
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

/******************************************************************************
**                      		Include Files                                **
******************************************************************************/
#include "kf32a156_flash.h"

/**
  *   ##### FLASH����洢��(FLASH)�������ú��� #####
  */

void __attribute__((section(".indata"))) CHECK_RESTRICTION_RAM(int expr)
{
	while(!expr)
		;
}

/* д���⹦�ܼĴ���RAM */
static inline uint32_t   __attribute__((section(".indata"))) SFR_Config_RAM (uint32_t SfrMem, uint32_t SfrMask, uint32_t WriteVal)
{
    return ((SfrMem & SfrMask) | (WriteVal));
}

/**
  * ����  ����FLASH����ʧ�Դ洢��ECCʹ�ܡ�
  * ����  NewState: FLASH����ʧ�Դ洢��ECCʹ��״̬��ȡֵΪTRUE �� FALSE��
  * ����  �ޡ�
  */
void __attribute__((section(".indata"))) FLASH_NonVolatile_Memory_ECC_Enable_RAM (FunctionalState NewState)
{
    /* ����У�� */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- ����FLASH_CFG�Ĵ���ECCREADENλ ----------------*/
    if (NewState != FALSE)
    {
        /* ʹ��ECCУ�� */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_ECCREADEN_POS));
    }
    else
    {
        /* ��ʹ��ECCУ�� */
        __asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_ECCREADEN_POS));
    }
}

/**
  * ����  ����FLASH����Ԥȡʹ�ܡ�
  * ����  NewState: FLASH����Ԥȡʹ��״̬��ȡֵΪTRUE �� FALSE��
  * ����  �ޡ�
  */
void __attribute__((section(".indata"))) FLASH_Linear_Prefetch_Enable_RAM (FunctionalState NewState)
{
    /* ����У�� */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- ����FLASH_CFG�Ĵ���PREFETCHENλ ----------------*/
    if (NewState != FALSE)
    {
        /* ʹ������Ԥȡ */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_PREFETCHEN_POS));
    }
    else
    {
        /* ��ʹ������Ԥȡ */
    	__asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CFG)),"i"(FLASH_CFG_PREFETCHEN_POS));
    }
}

/**
  * ����  ����FLASH�������ڡ�
  * ����  PeriodNum: FLASH����ϵͳ���ڸ�����ȡֵΪ1~16��
  * ����  �ޡ�
  */
void __attribute__((section(".indata"))) FLASH_Period_Number_Config_RAM (uint32_t PeriodNum)
{
	uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION_RAM(CHECK_FLASH_PERIOD(PeriodNum));

    /*---------------- ����FLASH_CFG�Ĵ���TCFGλ ----------------*/
    tmpreg = (PeriodNum - 1) << FLASH_CFG_TCFG0_POS;
    FLASH_CFG = SFR_Config_RAM (FLASH_CFG,
                        ~FLASH_CFG_TCFG,
                        tmpreg);
}

/**
  * ����  ��FLASH�������״̬��
  * ����  �ޡ�
  * ����  ���״̬��1��������ɣ�0��δ������߼����С�
  */
FlagStatus __attribute__((section(".indata"))) FLASH_Get_Compute_Complete_Status_RAM (void)
{
    if (FLASH_STATE & FLASH_STATE_SIGDONE)
    {
        /* ������� */
        return SET;
    }
    else
    {
        /* δ������߼����� */
        return RESET;
    }
}

/**
  * ����  ����FLASH�������״̬��
  * ����  �ޡ�
  * ����  �ޡ�
  */
void __attribute__((section(".indata"))) FLASH_Clear_Compute_Complete_Status_RAM (void)
{
    /* д 1 ���� */
    while((FLASH_STATE & FLASH_STATE_SIGDONE)>>FLASH_STATE_SIGDONE_POS)
    {
    	__asm volatile("SET [%0], #%1"::"r"(&(FLASH_STATE)),"i"(FLASH_STATE_SIGDONE_POS));
    }
}


/**
  * ����  ����FLASH CheckSum��β��ַ��
  * ����  StartAddr: FLASH CheckSum���׵�ַ����ַ����Ϊ0x0~0xFFFFF��Ӳ�����Ե�4λ��
  *       StopAddr: FLASH CheckSum��β��ַ����ַ����Ϊ0x0~0xFFFFF��Ӳ�����Ե�4λ��
  * ����  �ޡ�
  */
void  __attribute__((section(".indata"))) FLASH_CheckSum_Addr_Config_RAM(uint32_t StartAddr, uint32_t StopAddr)
{
    /* ����У�� */
    CHECK_RESTRICTION_RAM(CHECK_FLASH_ADDR_20BITS(StartAddr));
    CHECK_RESTRICTION_RAM(CHECK_FLASH_ADDR_20BITS(StopAddr));

    FLASH_CSSTART = StartAddr;
    FLASH_CSSTOP = StopAddr;
}

/**
  * ����  ����FLASH����SIG����ʹ�ܡ�
  * ����  NewState: FLASH����SIG����ʹ��״̬��ȡֵΪTRUE �� FALSE��
  * ����  �ޡ�
  */
void  __attribute__((section(".indata"))) FLASH_Start_SIG_Compute_Enable_RAM (FunctionalState NewState)
{
    /* ����У�� */
    CHECK_RESTRICTION_RAM(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- ����FLASH_CSSTOP�Ĵ���SIGGOλ ----------------*/
    if (NewState != FALSE)
    {
        /* ����SIG���� */
        __asm volatile("SET [%0], #%1"::"r"(&(FLASH_CSSTOP)),"i"(FLASH_CSSTOP_SIGGO_POS));
    }
    else
    {
        /* ������SIG���� */
        __asm volatile("CLR [%0], #%1"::"r"(&(FLASH_CSSTOP)),"i"(FLASH_CSSTOP_SIGGO_POS));
    }
}

/**
  * ����  ��ȡFLASH CheckSum�Ľ����
  * ����  CheckSumStruct: FLASH CheckSum��Ϣ�ṹ��ָ�룬
  *                       ָ�����ָ���д�ĵ�ַ�ռ䡣
  * ����  �ޡ�
  */
void __attribute__((section(".indata"))) FLASH_Get_CheckSum_Result_RAM (FLASH_CheckSumResult* CheckSumStruct)
{
	uint32_t tmpreg;

    /*---------------- ����FLASH_CSRESx�Ĵ���CKSPRESλ ----------------*/
    tmpreg = FLASH_CSRES0;
    CheckSumStruct->m_ResultWord[0] = tmpreg;

    tmpreg = FLASH_CSRES1;
    CheckSumStruct->m_ResultWord[1] = tmpreg;

    tmpreg = FLASH_CSRES2;
    CheckSumStruct->m_ResultWord[2] = tmpreg;

    tmpreg = FLASH_CSRES3;
    CheckSumStruct->m_ResultWord[3] = tmpreg;
}

/**
  * ����: ��ȡFLASH��ECC�����־
  * ���룺 �ޡ�
  * ���أ� 	0��FLASH��ECC�����ȷ
  * 	  	1��FLASH��ECC�������
  **/
FlagStatus CACHE_Get_FLASH_ECC_Error_Flag(void)
{
	return ((CACHE_CTLR & PCLK_CTL3_FECCERRFLAG) >> PCLK_CTL3_FECCERRFLAG_POS);
}
/**
  * ����: RAM��ECCУ������ж�ʹ��
  * ���룺 	NewState : 	TRUE : RAM��ECCУ������ж�ʹ��
  * 					FALSE : RAM��ECCУ������жϽ�ֹ��
  * ���أ� �ޡ�
  **/
void CACHE_RAM_Check_ECC_Error_INT_Enable(FunctionalState NewState)
{
	uint32_t tmpreg;

	/* ����У�� */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	tmpreg = NewState << PCLK_CTL3_RECCERRIE_POS;
	CACHE_CTLR = SFR_Config(CACHE_CTLR, ~PCLK_CTL3_RECCERRIE, tmpreg);
}

/**
  * ����: FLASH��ECCУ������ж�ʹ��
  * ���룺 	NewState : 	TRUE : FLASH��ECCУ������ж�ʹ��
  * 					FALSE : FLASH��ECCУ������жϽ�ֹ��
  * ���أ� �ޡ�
  **/
void CACHE_FLASH_Check_ECC_Error_INT_Enable(FunctionalState NewState)
{
	uint32_t tmpreg;

	/* ����У�� */
	CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

	tmpreg = NewState << PCLK_CTL3_FECCERRIE_POS;
	CACHE_CTLR = SFR_Config(CACHE_CTLR, ~PCLK_CTL3_FECCERRIE, tmpreg);
}

