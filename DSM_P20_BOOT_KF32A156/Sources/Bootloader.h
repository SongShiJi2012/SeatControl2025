#ifndef       _BOOTLOADER_H
#define       _BOOTLOADER_H
#include  "Common.h"
#include "kf32a156_int.h"

#define     D_EnterAppDelayTime_100ms             (100 / 10) // 100ms
#define     D_EnterAppDelayTime_1000ms            (1000 / 10) // 1000ms

#define     INT_SYS_EnableIRQGlobal()          INT_All_Enable (TRUE)
#define      INT_SYS_DisableIRQGlobal()         INT_All_Enable (FALSE)

#define     Boot_EnableInterrupts           INT_SYS_EnableIRQGlobal()
#define     Boot_DisableInterrupts          INT_SYS_DisableIRQGlobal()



extern BOOL    Boot_1msFlag;
extern INT8U   Boot_Event5msTime; // 初始化不同的值, 为了错开5ms和10ms任务同时出现
extern INT8U   Boot_Event10msTime;
extern BOOL	    BootEnterAppFlag;
extern BOOL        AppCodeValidFlg;
extern BOOL        g_E2promAppCodeValidFlg;
extern INT16U      EnterAppDelayTimeCnt;

void            Boot_1msInterrupt(void);
void    Boot_5msTask(void);
void    Boot_10msTask(void);
void    Boot_System_Init(void);
void BootUp_Application(uint32_t appEntry, uint32_t appStack);

#endif

