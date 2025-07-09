#ifndef _OSEKNMSLEEP_H
#define _OSEKNMSLEEP_H

#include "Common.h"
extern BOOL SleepConditionCheck();

extern void resetS_delayTimer(void);
extern void setLocalSleepFlag(INT8U flg);
extern void OsekNmSleep_SleepPre(void);
extern void OsekNmSleep_SleepDescFunction(void);
extern void OsekNmSleep_SetDescSleepFlg(INT8U Flg);



//#define  	D_STAY_AWAKE

#endif
