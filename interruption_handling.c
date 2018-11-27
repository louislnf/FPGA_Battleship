/*
 * interruption_handling.c
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#include "system.h"
#include "event.h"
#include "alt_types.h"
#include "interruption_handling.h"
#include "sys/alt_irq.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"
#include <stdio.h>
#include <stdlib.h>

void registerSwitchesInterruptions(void *context) {
	// enabling interrupts for the switches
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCHES_BASE, 0xFF);
	// clearing the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0xFF);
	// registering the irq for switches
	alt_irq_register(SWITCHES_IRQ, context, switchesInterruptHandler);
}
void registerButtonsInterruptions(void *context) {
	// enabling interrupts for the 4 buttons
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, 0xFF);
	// clearing the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0xFF);
	// registering the irq for buttons
	alt_irq_register(BUTTONS_IRQ, context, buttonsInterruptHandler);
}

void switchesInterruptHandler(void* context) {
	// reading the value from the switch
	alt_u8 sw = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);

	// adding the event to the event queue
	QueuedEvent** queuedEvent_pp = (QueuedEvent**)context;
	Event event;
	event.type = SWITCH_MOVEDUP;
	event.value = sw;
	queueEvent(queuedEvent_pp, event);

	// clearing the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0xFF);
}

void buttonsInterruptHandler(void* context) {
	alt_u8 but = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);

	// adding the event to the event queue
	QueuedEvent** queuedEvent_pp = (QueuedEvent**)context;
	Event event;
	event.type = BUTTON_PRESSED;
	event.value = but;
	queueEvent(queuedEvent_pp, event);

	// clearing the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0xFF);
}
