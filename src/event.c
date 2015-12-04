#include "common.h"
#include "keys.h"

static event eventsQueued[MAX_EVENTS_QUEUED];
static int head = 0;
static int tail = 0;

void Event_Queue(int event_type, int value1, int value2)
{
	if (tail >= MAX_EVENTS_QUEUED)
	{
		Print("Error while queuing event.");
		return;
	}
	event ev = eventsQueued[tail];
	ev.event_type = (eventType)event_type;
	ev.value1 = value1;
	ev.value2 = value2;

	eventsQueued[tail++] = ev;
}

event Event_Get()
{
	event ev;

	if (head < tail)
	{
		return eventsQueued[head++];
	}

	memset(&ev, 0, sizeof(ev));
	ev.event_type = EVENT_NULL;
	return ev;
}

void Event_Loop()
{
	event e;
	head = 0;
	while (1)
	{
		e = Event_Get();

		if (e.event_type == EVENT_NULL)
		{
			tail = 0;
			return;
		}

		switch (e.event_type)
		{
		case EVENT_KEY:
			Client_KeyEvent(e.value1, (bool)e.value2);
			break;
		}
	}
}