/*
 * event.h
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef enum EventType {
	BUTTON_PRESSED,
	SWITCH_MOVEDUP
} EventType;

typedef struct Event {
	EventType type;
	char value;
} Event;

typedef struct QueuedEvent {
	Event event;
	struct QueuedEvent *next;
} QueuedEvent;

void queueEvent(QueuedEvent** queuedEvent_pp, Event event);
Event dequeueEvent(QueuedEvent** queuedEvent_pp);



#endif /* EVENT_H_ */
