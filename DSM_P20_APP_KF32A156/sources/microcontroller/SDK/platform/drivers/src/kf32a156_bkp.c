/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : kf32a156_bkp.c
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Lib Version      : V2.4.0.250417_release
 *  @Description      : This file provides the backup domain (BKP)
 *                      peripherals function, including:                      
 *                      + Backup filed (BKP) reset and read-write allow       
 *                        functions                                              
 *                      + Backup domain (BKP) functional configuration           
 *                        function                                            
 *                          + Backup domain (BKP) interrupt management function      
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
#include "kf32a156_bkp.h"
static volatile uint32_t BkpEnterCounter = 0u;

static uint32_t Intr_Enter_Critical(void);
static void Intr_Exit_Critical(uint32_t v);

/**
  *   ##### ������(BKP)��λ����д������ #####
  */
/**
  * ����  ��λ������(BKP)���裬�ú�������λ������Ĵ����飬������λRTCģ�顣
  * ����  �ޡ�
  * ����  �ޡ�
  */
void BKP_Reset (void)
{
    /* ������Ĵ����������λ */
    SFR_SET_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    SFR_CLR_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
}

/**
  * ����  ������(BKP)�Ĵ������дʱ����Ҫ�����¼Ĵ���λ�������ã�
  *         1.  OSCCTL0�Ĵ�����PMWRENλ��1����������������Ķ�д������
  *         2.  PM_CTL0�Ĵ�����BKPREGCLRλ��1���Ĵ������˳���λ��
  *         3.  PM_CTL0�Ĵ�����BKPWRλ��1�������������ݼĴ������RTCģ���ڵļĴ�����д������
  *       ��д�Ĵ�����ǰ���øú�����������д������ٴε��øú�������ȱ�ٻ��ε�������޷��ָ�ԭʼ���á�
  * ����  NewState: ������Ĵ������д����ʹ�ܣ�ȡֵ��ΧΪ��
  *                   TRUE: ������Ĵ������дǰ������
  *                   FALSE: ������Ĵ������д������ûָ�
  * ����  �ޡ�
  */
void BKP_Write_And_Read_Enable (FunctionalState NewState)
{
    uint32_t r = 0u;
    /* ����У�� */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));
    if (NewState != FALSE)
    {
        r = Intr_Enter_Critical();
        if (0u == BkpEnterCounter)
        {
            /* ��������������Ķ�д���� */
            SFR_SET_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
            /* �Ĵ������˳���λ */
            SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPREGCLR_POS);
            /* �����������ݼĴ������RTCģ���ڵļĴ�����д���� */
            SFR_SET_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
        }
        else
        { /*Empty*/
        }
        BkpEnterCounter++;
        Intr_Exit_Critical(r);
    }
    else
    {
        r = Intr_Enter_Critical();
        if (BkpEnterCounter != 0)
        {
          BkpEnterCounter--;
        }
        else
        {
          /* code */
        }
        
        if (0u == BkpEnterCounter)
        {
            /* �ָ�BKPWRλ */
            SFR_CLR_BIT_ASM(PM_CTL0, PM_CTL0_BKPWR_POS);
            /* ������д���������� */
            SFR_CLR_BIT_ASM(OSC_CTL0, OSC_CTL0_PMWREN_POS);
        }
        else
        { /*Empty*/
        }
        Intr_Exit_Critical(r);
    }
}
/**
 * @brief �����ٽ��������ص�ǰ�ж�״̬
 *
 * @param ��
 * @retval uint32_t �ж�״̬
 */
static uint32_t Intr_Enter_Critical(void)
{
    uint32_t r = INT_CTL0 & INT_CTL0_AIE;
    __asm volatile("DSI");
    __asm volatile("NOP");
    return r;
}

/**
 * @brief �����ж�״̬�Ƿ�ʹ���ж�
 *
 * @param[in] v �ж�״ֵ̬
 * @retval none
 */
static void Intr_Exit_Critical(uint32_t v)
{
    if (v > 0U)
    {
        __asm volatile("ENI");
        __asm volatile("NOP");
    }
    else
    {/*Empty*/
    }
}
/**
  *   ##### ������(BKP)��λ����д������������� #####
  */


/**
  *   ##### ������(BKP)�������ú��� #####
  */
/**
  * ����  ���ñ�����Ĵ����������λʹ�ܡ�
  * ����  NewState: ������Ĵ����������λ��ȡֵ��ΧΪ��TRUE �� FALSE��
  * ����  ��
  */
void BKP_Reset_Enable (FunctionalState NewState)
{
    /* ����У�� */
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- ����BKP_CTL�Ĵ���BKDRSTλ ----------------*/
    if (NewState != FALSE)
    {
        /* ������Ĵ����鸴λ */
        SFR_SET_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    }
    else
    {
        /* ������ */
        SFR_CLR_BIT_ASM(BKP_CTL, BKP_CTL_BKDRST_POS);
    }
}

/**
  * ����  �������������ŵ���Ч��ƽ��
  * ����  PinSel: ����������ѡ��ȡֵΪ��
  *                 BKP_PIN_RTC_TAMP1: ����������RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: ����������RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: ����������RTC_TAMP3
  *       Effective: ��Ч��ƽ��ȡֵΪ:
  *                    BKP_HIGH_LEVEL_EFFECTIVE: �ߵ�ƽ��������е����ݱ��ݼĴ���
  *                    BKP_LOW_LEVEL_EFFECTIVE: �͵�ƽ��������е����ݱ��ݼĴ���
  * ����  �ޡ�
  */
void BKP_Pin_Effective_Level_Config (uint32_t PinSel, uint32_t Effective)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_BKP_EFFECTIVE_LEVEL(Effective));

    /*------------- ����BKP_CTL�Ĵ���TAMPxLVLλ -------------*/
    tmpreg = BKP_CTL_TAMP1LVL << PinSel;
    if (BKP_HIGH_LEVEL_EFFECTIVE != Effective)
    {
        /* �����������ϵĵ͵�ƽ��������е����ݱ��ݼĴ��� */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* �����������ϵĸߵ�ƽ��������е����ݱ��ݼĴ��� */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * ����  ��������������RTC_TAMP1ʹ�ܡ�
  * ����  PinSel: ����������ѡ��ȡֵΪ��
  *                 BKP_PIN_RTC_TAMP1: ����������RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: ����������RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: ����������RTC_TAMP3
  *       NewState: ����������RTC_TAMP1ʹ��״̬��ȡֵ��ΧΪ��TRUE �� FALSE��
  * ����  �ޡ�
  */
void BKP_Pin_Enable (uint32_t PinSel, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*------------- ����BKP_CTL�Ĵ���TAMPxLVLλ -------------*/
    tmpreg = BKP_CTL_TAMP1EN << PinSel;
    if (NewState != FALSE)
    {
        /* ʹ����������1���� */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* ��ֹ��������1���� */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * ����  ����������ͬ�����ܡ�
  * ����  Mode: ȡֵΪ��
  *                 BKP_TAMP_ASYNC: �������첽
  *                 BKP_TAMP_SYNC: ������ͬ��
  * ����  �ޡ�
  */
void BKP_TAMP_SYNC_Mode_Select(uint32_t Mode)
{
	/* ����У�� */
	CHECK_RESTRICTION(CHECK_BKP_TAMP_MODE(Mode));

	BKP_CTL	= SFR_Config(BKP_CTL, ~BKP_CTL_SYNC, Mode << BKP_CTL_SYNC_POS);
}

/**
  * ����  �������������ʱ�ӡ�
  * ����  CLK: ȡֵΪ��
  *                 BKP_TAMP_SCK_SCLK: ѡ�� SCLK ��Ϊ����ʱ��
  *                 BKP_TAMP_SCK_INTLF: ѡ�� INTLF ��Ϊ����ʱ��
  * ����  �ޡ�
  */
void BKP_TAMP_SCK_Select(uint32_t CLK)
{
	/* ����У�� */
	CHECK_RESTRICTION(CHECK_BKP_TAMP_SCK(CLK));

	BKP_CTL	= SFR_Config(BKP_CTL, ~BKP_CTL_SAMCLKS, CLK << BKP_CTL_SAMCLKS_POS);
}

/**
  * ����  �����ⲿʱ����·����ʹ�ܡ�
  * ����  Source: ʱ��ѡ��ȡֵΪ��
  *                 BKP_EXTHF: �ⲿ��Ƶʱ��
  *                 BKP_EXTLF: �ⲿ��Ƶʱ��
  *       NewState: �ⲿʱ����·����ʹ��״̬��ȡֵ��ΧΪ��TRUE �� FALSE��
  * ����  �ޡ�
  */
void BKP_External_Clock_Bypass_Enable (uint32_t Source, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_CLOCK_SOURCE(Source));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*------------- ����BKP_CTL�Ĵ���TAMPxLVLλ -------------*/
    tmpreg = BKP_CTL_EXTHFBYP << Source;
    if (FALSE != NewState)
    {
        /* �ⲿʱ�ӱ���· */
        BKP_CTL |= tmpreg;
    }
    else
    {
        /* �ⲿʱ��δ��· */
        BKP_CTL &= ~tmpreg;
    }
}

/**
  * ����  д�����򱸷����ݼĴ�����
  * ����  OrderNumber: �������ݼĴ�����ţ�ȡֵ��ΧΪ0~7��
  *       WriteData: д������ݣ�ȡֵ��ΧΪ32λ���ݡ�
  * ����  �ޡ�
  */
void BKP_Data_Config (uint32_t OrderNumber, uint32_t WriteData)
{
    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_DATA_NUMBER(OrderNumber));

    /*------------- ����BKP_DATA�Ĵ���BKPDATAλ -------------*/
    BKP_SFR->DATA[OrderNumber] = WriteData;
}

/**
  * ����  �������򱸷����ݼĴ�����
  * ����  OrderNumber: �������ݼĴ�����ţ�ȡֵ��ΧΪ0~7��
  * ����  �������ݼĴ�����ֵ��ȡֵ��ΧΪ32λ���ݡ�
  */
uint32_t BKP_Get_Data (uint32_t OrderNumber)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_DATA_NUMBER(OrderNumber));

    /*------------- ��ȡBKP_DATA�Ĵ���BKPDATAλ -------------*/
    tmpreg = BKP_SFR->DATA[OrderNumber];

    return tmpreg;
}
/**
  *   ##### ������(BKP)�������ú���������� #####
  */


/**
  *   ##### ������(BKP)�жϹ����� #####
  */
/**
  * ����  �������������ж�ʹ�ܡ�
  * ����  PinSel: ����������ѡ��ȡֵΪ��
  *                 BKP_PIN_RTC_TAMP1: ����������RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: ����������RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: ����������RTC_TAMP3
  *       NewState: ���������ж�ʹ��״̬��ȡֵΪTRUE �� FALSE��
  * ����  �ޡ�
  */
void BKP_Pin_TAMP_INT_Enable (uint32_t PinSel, FunctionalState NewState)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));
    CHECK_RESTRICTION(CHECK_FUNCTIONAL_STATE(NewState));

    /*---------------- ����BKP_INT�Ĵ���TAMPxIEλ ----------------*/
    tmpreg = BKP_INT_TAMP1IE << PinSel;
    if (NewState != FALSE)
    {
        /* ʹ���������ж� */
        BKP_INT |= tmpreg;
    }
    else
    {
        /* ��ֹ�������ж� */
        BKP_INT &= ~tmpreg;
    }
}

/**
  * ����  ��ȡ�����жϱ�־��
  * ����  PinSel: ����������ѡ��ȡֵΪ��
  *                 BKP_PIN_RTC_TAMP1: ����������RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: ����������RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: ����������RTC_TAMP3
  * ����  1:���������¼���0:�������¼�������
  */
FlagStatus BKP_Get_Pin_TAMP_INT_Flag (uint32_t PinSel)
{
    uint32_t tmpreg;

    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));

    /*---------------- ��ȡBKP_INT�Ĵ���TAMPxIFλ ----------------*/
    tmpreg = BKP_INT_TAMP1IF << PinSel;
    if (BKP_INT & tmpreg)
    {
        /* ���������¼� */
        return SET;
    }
    else
    {
        /* �������¼����� */
        return RESET;
    }
}

/**
  * ����  ����������жϱ�־��
  * ����  PinSel: ����������ѡ��ȡֵΪ��
  *                 BKP_PIN_RTC_TAMP1: ����������RTC_TAMP1
  *                 BKP_PIN_RTC_TAMP2: ����������RTC_TAMP2
  *                 BKP_PIN_RTC_TAMP3: ����������RTC_TAMP3
  * ����  ������������жϱ�־״̬��
  */
RetStatus BKP_Clear_Pin_TAMP_INT_Flag (uint32_t PinSel)
{
    uint32_t tmpreg;
    uint32_t tmpreg1;
	volatile uint32_t wait_flag=0x0000;
    /* ����У�� */
    CHECK_RESTRICTION(CHECK_BKP_PIN_RTC_TAMP(PinSel));

    /*---------------- ����BKP_INT�Ĵ���TAMPxICλ ----------------*/
    tmpreg = BKP_INT_TAMP1IC << PinSel;
    tmpreg1 = BKP_INT_TAMP1IF << PinSel;
    BKP_INT |= tmpreg;
    while(((BKP_INT & tmpreg1)>>(BKP_INT_TAMP1IF_POS+PinSel))&& (wait_flag != FLAG_TIMEOUT))
	{
		wait_flag++;
	}
    BKP_INT &= ~tmpreg;
	if(wait_flag==FLAG_TIMEOUT)
	{
		return FAILURE;
	}
	return SUCCESS;
}
/**
  *   ##### ������(BKP)�жϹ����� #####
  */

