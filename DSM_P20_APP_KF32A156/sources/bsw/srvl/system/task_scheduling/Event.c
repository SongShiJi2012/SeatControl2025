#include "Event.h"
//#include "interrupt_manager.h"

typedef	struct
{
	INT8U	event;
	INT8U	eventPrio;
} StEvent;



static	StEvent		EventBuff[TASKMAX];
static	INT8U		WriteEventCont;//,ReadEventCont;

void InitEvent()
{
	INT8U	Index;

	for(Index = 0; Index < TASKMAX; Index++)
	{
		EventBuff[Index].event = 0xff;
		EventBuff[Index].eventPrio = PrioLowest;
	}
	WriteEventCont = 0x00;
}

void PushEvent(INT8U event, INT8U eventPrio)
{	
	INT8U Index,Index1;

	ENTER_CRITICAL();
	if(WriteEventCont >= TASKMAX)
	{
		EXIT_CRITICAL();
		return;
	}
	for(Index = 0; Index < WriteEventCont; Index++)
	{
		if(EventBuff[Index].eventPrio > eventPrio)
		{
			for(Index1 = WriteEventCont; Index1 > Index ; Index1--)
			{
				EventBuff[Index1] = EventBuff[Index1- 1];
			}
			break;
		}
	}
	EventBuff[Index].event = event;
	EventBuff[Index].eventPrio = eventPrio;
	WriteEventCont++;	
	EXIT_CRITICAL();
}

INT8U PopEvent()
{	
	INT8U Index;
	INT8U event;

	ENTER_CRITICAL();
	if(WriteEventCont > 0x00)
	{
		event = EventBuff[0].event;
		WriteEventCont--;
		for(Index = 0; Index < TASKMAX - 1; Index++)
		{
			EventBuff[Index] = EventBuff[Index+1];
		}
		EventBuff[TASKMAX - 1].event = 0xFF;
		EventBuff[TASKMAX - 1].eventPrio = PrioLowest;
	}else
	{
		event = 0xFF;
	}
	EXIT_CRITICAL();
	return (event);
}


