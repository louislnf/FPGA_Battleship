/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

/*
 * CUSTOM HEADERS
 */

#include "interruption_handling.h"
#include "cursor.h"
#include "memory.h"
#include "event.h"
#include "display.h"
#include "unistd.h"
#include "game.h"

int main()
{
	/*
	 * SETUP HARDWARE RELATED
	 */

	// cleaning memory
	cleanMemory();

	// initializing the cursor
	cursor_t *cursor = (cursor_t*)malloc(sizeof(cursor_t));
	setCursorX(cursor, 0);
	setCursorY(cursor, 0);
	writeCursorPosition(cursor);

	// initializing the event queue
	QueuedEvent** queuedEvent_pp = (QueuedEvent**)malloc(sizeof(QueuedEvent*));
	*queuedEvent_pp = NULL;

	// registering the interruptions handler
	registerButtonsInterruptions(queuedEvent_pp);
	registerSwitchesInterruptions(queuedEvent_pp);


	/*
	 * SETUP GAME RELATED
	 */


	GameMode gameMode = PLACING;
	Player* player = initializePlayer(GRID_SIZE, NUMBER_OF_BOATS);
	Player* ia = initializePlayer(GRID_SIZE, NUMBER_OF_BOATS);

	initializeBoats(player);
	// drawing boats to init view
	drawPlayerBoats(player, 1);
	// placing cursor
	moveCursorToBoatOrigin(player->boats[player->numberOfBoatsPlaced], cursor);

	char choosingDirection = 0;


	/*
	 * MAIN LOOP
	 */

	Event event;

	while (1) {
		if (*queuedEvent_pp != NULL) {
			event = dequeueEvent(queuedEvent_pp);
			// checking for reset switch 
			if (event.type == SWITCH_MOVEDUP && event.value == 4 ) {
				//goto startTag;
			}
			switch (gameMode) {
			case PLACING:
				// checking wether the player has placed all his boats yet or not, if so we move to the shooting part
				if (player->numberOfBoatsPlaced == player->numberOfBoats) {
					gameMode = SHOOTING;
					cleanMemory();
					drawPlayerBoats(player, 2);
					break;
				}
				switch(event.type) {
				case BUTTON_PRESSED:
					printf("Button pressed %d\n", event.value);
					if (choosingDirection) {
						switch (event.value) {
						case 1:
							player->boats[player->numberOfBoatsPlaced].direction = NORTH;
							break;
						case 2:
							player->boats[player->numberOfBoatsPlaced].direction = SOUTH;
							break;
						case 4:
							player->boats[player->numberOfBoatsPlaced].direction = WEST;
							break;
						case 8:
							player->boats[player->numberOfBoatsPlaced].direction = EAST;
							break;
						default:
							break;
						}
					} else {
						switch (event.value) {
						case 1:
							moveBoat(&(player->boats[player->numberOfBoatsPlaced]), NORTH);
							break;
						case 2:
							moveBoat(&(player->boats[player->numberOfBoatsPlaced]), SOUTH);
							break;
						case 4:
							moveBoat(&(player->boats[player->numberOfBoatsPlaced]), WEST);;
							break;
						case 8:
							moveBoat(&(player->boats[player->numberOfBoatsPlaced]), EAST);
							break;
						default:
							break;
						}
						moveCursorToBoatOrigin(player->boats[player->numberOfBoatsPlaced], cursor);
					}
					break;
				case SWITCH_MOVEDUP:
					printf("Switch moved up %d\n", event.value);
					switch(event.value) {
						case 1: // OK SWITCH
							if (choosingDirection) {
								// checking if the boat can be placed
								if (canPlaceBoatForPlayer(player, player->boats[player->numberOfBoatsPlaced])) {
									// then we update the number of boats placed
									player->numberOfBoatsPlaced += 1;
									moveCursorToBoatOrigin(player->boats[player->numberOfBoatsPlaced], cursor);
									choosingDirection = 0;
								} else {
									// debug print
									printf("Cannot place boat here !\n");
								}
							} else {
								choosingDirection = 1;
							}
							break;
						case 2: // CANCEL SWITCH
							// does nothing if not already choosing direction
							choosingDirection = 0;
							break;
						default:
							break;
					}
					break;
				default:
					break;
				}
				// here we draw the player1's boats in the first grid
				cleanMemory();
				drawPlayerBoats(player, 1);
				break;
			case SHOOTING:
				break;
			case OVER:
				break;
			default:
				break;
			}
		}
		writeCursorPosition(cursor);
	}

	return 0;
}
