#define  SecurityAccess_GLOBALS

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/

#include "uds_pub.h"

#define D_SecurityDiagMask1 	(0x51BD363EUL)
#define D_SecurityFBLMask2 		(0x21763702UL)

/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT16U Srvl_GetRand16(void)
* @par ����
       ����һ��16bit�����������������ͬ���㷨
* @param[in] void
* @param[out] void
* @returns INT16U�������
* @pre ��
* @note ��
* @author Lews Hammond(������)
* @date 2019-10-24
************************************************************************************************************************
*/
INT16U Srvl_GetRand16(void)
{
	static INT16U Rand = 107;
	INT16U tSeed = (INT16U)D_HAL_GET_CUR_MS_TS();

	Rand = (INT16U)( (((INT32U)tSeed * Rand) * 16807UL) % (0xFFF3U) );

	if ( 0x0000 == Rand )
	{
		Rand = 0x1573;
	}
	return Rand;
}
/*!
************************************************************************************************************************
* @par �ӿ�ԭ��
       INT32U SeedToKey(INT8U *seed, INT32U len, INT8U *key, INT32U *retLen)
* @par ����
       JMC V348��ȫ��֤�㷨
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond(������)
* @date 2019-9-24
************************************************************************************************************************
*/
INT32U SeedToKey(INT8U *seed, INT32U Len, INT8U *key, INT32U *retLen)
{
	INT32U i = 0;
	union
	{
		INT8U byte[SecurityAccess_MLVKEYNUM];
		INT32U wort;
	} seedlokal;

	const INT32U mask = D_SecurityDiagMask1;
	/* The array for SEED starts with [1], the array for KEY starts with [0] */
	/* seed contains the SEED from the ECU */
	/* length contains the number of bytes of seed */
	/* key contains the KEY to send to ECU */
	/* retLen contains the number of bytes to send to ECU as key */
	if ((seed[0] == 0) && (seed[1] == 0))
	{
		*retLen = 0;
	}
	else
	{
		seedlokal.wort = ((INT32U)seed[0] << 24U) + ((INT32U)seed[1] << 16U) + ((INT32U)seed[2] << 8U) + ((INT32U)seed[3]);

		for (i = 0; i < 35; i++)
		{
			if (seedlokal.wort & 0x80000000U)
			{
				seedlokal.wort = seedlokal.wort << 1U;
				seedlokal.wort = seedlokal.wort ^ mask;
			}
			else
			{
				seedlokal.wort = seedlokal.wort << 1U;
			}
		}

		for (i = 0; i < 4; i++)
		{
			key[3-i] = seedlokal.byte[i];
		}
		*retLen = Len - 1U;
	}

	return TRUE;
}



/*************************************************************
* �������ƣ�SecurityAccess_vogSeedGenerate
* ������������ȫ�����������Seed
* ��ڲ�����
* ���ڲ�����
* �� �� ֵ��
* ��    ע: 
*************************************************************/
void SecurityAccess_vogSeedGenerate(void)
{
	INT8U i, SeedChgFlg = 1;

	*((INT16U*)SecurityAccess_stgOutInfo.u1SecLvSeed) = Srvl_GetRand16();
	SecurityAccess_stgOutInfo.u1SecLvSeed[2] = ((SecurityAccess_stgOutInfo.u1SecLvSeed[0] << 2) & 0x1C) | \
			((SecurityAccess_stgOutInfo.u1SecLvSeed[1] << 5) & 0xE0) | \
			((SecurityAccess_stgOutInfo.u1SecLvSeed[1] >> 6) & 0x03);
	SecurityAccess_stgOutInfo.u1SecLvSeed[3] = 	((SecurityAccess_stgOutInfo.u1SecLvSeed[1] << 2) & 0x1C) | \
			((SecurityAccess_stgOutInfo.u1SecLvSeed[2] << 5) & 0xE0) | \
			((SecurityAccess_stgOutInfo.u1SecLvSeed[2] >> 6) & 0x03);

	for(i = 0; i < SecurityAccess_MSEEDNUM; i++)
	{
		if(0 != SecurityAccess_stgOutInfo.u1SecLvSeed[i])
		{
			SeedChgFlg = 0;
		}
	}
	if(SeedChgFlg)
	{
		for(i = 0; i < SecurityAccess_MSEEDNUM; i++)
		{
			SecurityAccess_stgOutInfo.u1SecLvSeed[i] = i + 0xAA;
		}
	}
}

/******************************************************************************
**                                  END OF FILE
*******************************************************************************/



