#ifndef _ECUAL_LIN_H_
#define _ECUAL_LIN_H_

#include <Mcal_Lin.h>
#include <Ecual_linCfg.h>

extern void Ecual_LINSchTick(void);
extern void Ecual_LinInit(void);
extern BOOL Ecual_LinIsMsgRecvValid(LinChlIdx_t DevId,INT8U idMessage);
extern BOOL Ecual_LinGetLostPid();
extern void Ecaul_LinTxSleepMsg();
#endif
