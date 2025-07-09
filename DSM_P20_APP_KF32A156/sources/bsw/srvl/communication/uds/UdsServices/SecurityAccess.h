#ifndef __H_SECURITYACCESS
#define __H_SECURITYACCESS

#ifdef		SecurityAccess_GLOBALS
#define  	SecurityAccess_EXT
#else
#define	  SecurityAccess_EXT        extern
#endif

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include  "string.h"
#include  "Desc.h"


#define ZNA_SA

//Macro define-----------------------------------------------------
#define SecurityAccess_MCONSTANTNUM				   		4
#define SecurityAccess_MSEEDNUM				   		    4
#define SecurityAccess_MLVKEYNUM				   	    4


typedef struct
{
	INT8U u1SecLvSeed[SecurityAccess_MSEEDNUM];
	INT8U u1SecLvKey[SecurityAccess_MLVKEYNUM];
	INT8U u1SecLvConst[SecurityAccess_MCONSTANTNUM];
}SecurityAccess_stOutInfo;

//variables define----------------------------------------------
SecurityAccess_EXT SecurityAccess_stOutInfo  SecurityAccess_stgOutInfo;


SecurityAccess_EXT void SecurityAccess_vogSeedGenerate(void);

#ifdef ZNA_SA
SecurityAccess_EXT void SecurityAccess_vogKeyGenerate(void);
#else
SecurityAccess_EXT void SecurityAccess_vogKeyGenerate(INT8U* pInputPIN);

#endif

INT32U SeedToKey(INT8U *seed, INT32U len, INT8U *key, INT32U *retLen);

#endif  //__H_SECURITYACCESS
