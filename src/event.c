#include "common.h"

typedef struct _event event;

struct _event
{
	eventType type;
	int value1;
	int value2;
	event *next;
};

static event events[MAX_EVENTS];
static int eventHead = 0;
static int eventTail = 0;

void Event_Queue(eventType type, int value1, int value2)
{
	/*Print("Queue event");
	event *evt;

	if (0 >= MAX_EVENTS)
	{
		Print("Event overflow, ignoring new event");
		free(evt);
		return;
	}

	evt->type = type;
	evt->value1 = value1;
	evt->value2 = value2;
	evt->next = events;
	events = evt;*/
}

event* Event_GetEvent()
{
	/*Print("Get event");
	event* evt;
	if (eventCount > 0)
	{
		evt = events;
		events = evt->next;
		if (&evt == &events)
		{
			Print("Equal");
		}
		eventCount++;
		return events;
	}
	else
	{
		return NULL;
	}*/
}

void Event_Loop()
{
	event* evt;
	while (evt = Event_GetEvent())
	{

	}
}