#ifndef _CLIB_H
#define _CLIB_H
#include  "Common.h"


extern void RamSet(INT8U * buff, INT8U data, INT8U len);
extern INT8U CalcCheckSum(INT8U * Buff, INT8U len);
extern void MemCopy(INT8U * TrgBuff, INT8U * SrcBuff, INT8U Len);
extern void MemCopyINT32U(INT32U *TrgBuff, INT32U *SrcBuff, INT8U Len);
extern BOOL MemCmp(INT8U * TrgBuff, INT8U * SrcBuff, INT8U Len);
extern void INT8UToINT32U(INT32U *OutBuff, INT8U *InBuff, INT8U Len);
extern void INT32UToINT8U(INT8U *OutBuff, INT32U *InBuff, INT8U Len);
extern BOOL IsSameAsData(INT8U *Buff, INT8U Data, INT8U Len);

#endif

