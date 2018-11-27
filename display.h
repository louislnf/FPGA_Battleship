/*
 * display.h
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "game.h"

typedef enum Color {
	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
} Color;

char convertToMemoryAddress(char row, char col, char gridNumber);

void displayColorInGrid(char row, char col, Color color, char gridNumber);

void drawBoat(Boat boat, Color color, char gridNumber);

void drawPlayerBoats(Player *player, char gridNumber);

#endif /* DISPLAY_H_ */
