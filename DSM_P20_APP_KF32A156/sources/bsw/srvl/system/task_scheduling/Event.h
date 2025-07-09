#ifndef	_EVENT_H
#define	_EVENT_H


#include  "Common.h"

extern void	InitEvent(void);
extern void	PushEvent(INT8U event, INT8U eventPrio);
extern INT8U PopEvent(void);

#endif


