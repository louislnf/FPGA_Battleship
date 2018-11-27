/*
 * cursor.c
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#include "cursor.h"
#include "system.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"
#include "game.h"

unsigned char getCursorX(unsigned char *cursor) {
	return *cursor / 16;
}
void setCursorX(unsigned char *cursor, unsigned char newX) {
	*cursor = newX*16 + getCursorY(cursor);
}
unsigned char getCursorY(unsigned char *cursor) {
	return *cursor % 16;
}
void setCursorY(unsigned char *cursor, unsigned char newY) {
	*cursor = getCursorX(cursor)*16 + newY;
}

void moveCursorLeft(cursor_t *cursor) {
	unsigned char cursorX = getCursorX(cursor);
	if (cursorX > 0) {
		setCursorX(cursor, cursorX-1);
	}
}
void moveCursorRight(cursor_t *cursor) {
	unsigned char cursorX = getCursorX(cursor);
	if (cursorX < 9) {
		setCursorX(cursor, cursorX+1);
	}
}
void moveCursorUp(cursor_t *cursor) {
	unsigned char cursorY = getCursorY(cursor);
	if (cursorY > 0) {
		setCursorY(cursor, cursorY-1);
	}
}
void moveCursorDown(cursor_t *cursor) {
	unsigned char cursorY = getCursorY(cursor);
	if (cursorY < 9) {
		setCursorY(cursor, cursorY+1);
	}
}

void moveCursorToBoatOrigin(Boat boat, cursor_t *cursor) {
	setCursorY(cursor, (unsigned char)boat.origin.x);
	setCursorX(cursor, (unsigned char)boat.origin.y);
}

void writeCursorPosition(cursor_t *cursor) {
	IOWR_ALTERA_AVALON_PIO_DATA(CURSOR_BASE, *cursor);
}
