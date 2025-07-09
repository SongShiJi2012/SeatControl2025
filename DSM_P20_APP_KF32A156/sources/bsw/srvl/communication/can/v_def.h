
#ifndef  V_DEF_H
#define  V_DEF_H

#include "stddef.h"
#include  "Common.h"

#ifndef V_MEMRAM0
# define V_MEMRAM0                  /* addition qualifier data access in RAM  */
#endif

#ifndef V_MEMRAM1_NEAR
# define V_MEMRAM1_NEAR             /* fast data access in RAM */
#endif

#ifndef V_MEMRAM1
# define V_MEMRAM1                 /* fast data access in RAM */
#endif

#ifndef V_MEMRAM1_FAR
# define V_MEMRAM1_FAR             /* slow addressing mode in RAM */
#endif

#ifndef MEMORY_NEAR
# ifndef V_MEMRAM2_NEAR
#  define V_MEMRAM2_NEAR           /* fast data access in RAM */
# endif
  /* compatibility for modules which use old definition of memory qualifer */
# define MEMORY_NEAR   V_MEMRAM2_NEAR
#else
# define V_MEMRAM2_NEAR    MEMORY_NEAR
#endif

#ifndef MEMORY_NORMAL
# ifndef V_MEMRAM2
#  define V_MEMRAM2                 /* fast data access in RAM */
# endif
  /* compatibility for modules which use old definition of memory qualifer */
# define MEMORY_NORMAL   V_MEMRAM2       
#else
# define V_MEMRAM2           MEMORY_NORMAL
#endif

#ifndef MEMORY_FAR
# ifndef V_MEMRAM2_FAR
#  define V_MEMRAM2_FAR            /* slow addressing mode in RAM */
# endif
  /* compatibility for modules which use old definition of memory qualifer */
# define MEMORY_FAR    V_MEMRAM2_FAR
#else
# define V_MEMRAM2_FAR     MEMORY_FAR
#endif

# if !defined( V_MEMROM0 )
/* Remove the old defines */
#  undef MEMORY_ROM
#  undef MEMORY_NEAR
#  undef MEMORY_FAR
    
/* Fix the old defines */
#  define MEMORY_ROM                                                 const
#  define MEMORY_NEAR
#  define MEMORY_FAR
#  define V_MEMROM0  
# endif

#ifndef V_MEMROM1
# define V_MEMROM1                 /* fast data access in ROM */
#endif

# ifndef V_MEMROM2
#  define V_MEMROM2            		/* fast data access in ROM */
# endif

#if !defined(V_NULL)
# define V_NULL ((void*)0)
#endif


#ifndef NULL
# define NULL V_NULL
#endif

typedef unsigned char  vuint8;
typedef signed char    vsint8;
# define canuint8 vuint8
# define cansint8 vsint8

/* 16-Bit qualifier */
typedef unsigned short vuint16;
typedef signed short   vsint16;
#define canuint16 vuint16
#define cansint16 vsint16
#  ifndef vuintx
#   define vuintx vuint16
#  endif

/* 32-Bit qualifier */
typedef unsigned long  vuint32;
typedef signed long    vsint32;
#define canuint32 vuint32
#define cansint32 vsint32


typedef unsigned char *TxDataPtr;              /* ptr to transmission data buffer */
typedef unsigned char *RxDataPtr;              /* ptr to receiving data buffer    */

typedef unsigned short    CanTransmitHandle;
typedef unsigned short    CanReceiveHandle;

#if defined( C_ENABLE_EXTENDED_ID )
typedef unsigned long    tCanTxId;
#else
typedef unsigned short    tCanTxId;
#endif


#if defined C_ENABLE_EXTENDED_ID
typedef unsigned long     tCanRxId;
#else
typedef unsigned short    tCanRxId;
#endif

typedef unsigned int     vbittype;
#define canbittype       vbittype

typedef vuint16 tIlTxCounter;
typedef vuint16 tIlRxTimeoutCounter;

#define CanInterruptDisable()                      D_SYS_ENTER_CRITICAL()
#define CanInterruptRestore()                      D_SYS_EXIT_CRITICAL()

typedef vuint16 tIlTxUpdateCounter;
typedef CanReceiveHandle	IlReceiveHandle;
typedef CanTransmitHandle	IlTransmitHandle;

typedef canuint8 CanChannelHandle;
typedef  unsigned char  *  CanChipDataPtr;

typedef struct 
{
  CanChannelHandle  Channel;
  CanChipDataPtr    pChipData;
  CanReceiveHandle  Handle;
  canuint8          EcuNumber;
/* CPU-specific part */
  /* KB begin CanLL_tCanRxInfoStruct */
  /* KB end CanLL_tCanRxInfoStruct */
} tCanRxInfoStruct;

typedef tCanRxInfoStruct		  *CanRxInfoStructPtr;
typedef  canuint8 ( *ApplPrecopyFct)      (CanRxInfoStructPtr rxStruct);

typedef void  (*IlTimeoutIndicationFct)( void );

/* return values for precopy-routines */
#define kCanNoCopyData     ((canuint8)0x00)
#define kCanCopyData       ((canuint8)0x01)

/* CanTransmit return values -----------------------------------------------*/
#define kCanTxFailed               ((canuint8)0x00)  /* Tx path switched off or no sending possible */
#define kCanTxOk                   ((canuint8)0x01)  /* msg transmitted or in queue                 */
#define kCanTxPartOffline          ((canuint8)0x02)  /* Tx path switched part off or           */
#define kCanCommunicationDisabled  ((canuint8)0x03)  /* if application has disabled com after memory check */

#define kCanTxNotify               ((canuint8)0x05)  /* internal returncode only - not used for the API */


#endif

