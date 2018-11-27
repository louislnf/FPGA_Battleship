/*
 * event.c
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#include "event.h"
#include <stdlib.h>
#include <stdio.h>

void queueEvent(QueuedEvent** queuedEvent_pp, Event event) {
	if (queuedEvent_pp != NULL) {
		QueuedEvent* formerFirstQueuedEvent = *queuedEvent_pp;
		*queuedEvent_pp = (QueuedEvent*) malloc(sizeof(QueuedEvent));
		(*queuedEvent_pp)->event = event;
		(*queuedEvent_pp)->next = formerFirstQueuedEvent;
	}
}

Event dequeueEvent(QueuedEvent** queuedEvent_pp) {
	QueuedEvent *previous = *queuedEvent_pp;
	QueuedEvent *next = previous->next;
	Event event;
	if (next != NULL) {
		while (next->next != NULL) {
			previous = next;
			next = next->next;
		}
		event = next->event;
		previous->next = NULL;
		free(next);
	} else {
		event = previous->event;
		free(*queuedEvent_pp);
		*queuedEvent_pp = NULL;
	}
	return event;
}

void printEvent(Event event) {
	switch(event.type) {
	case BUTTON_PRESSED:
		printf("button : %d\n", event.value);
		break;
	case SWITCH_MOVEDUP:
		printf("switch : %d\n", event.value);
		break;
	default:
		break;
	}
}
