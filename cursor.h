/*
 * cursor.h
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "game.h"

typedef unsigned char cursor_t;

unsigned char getCursorX(cursor_t *cursor);
void setCursorX(cursor_t *cursor, unsigned char newX);
unsigned char getCursorY(cursor_t *cursor);
void setCursorY(cursor_t *cursor, unsigned char newY);

void moveCursorUp(cursor_t *cursor);
void moveCursorDown(cursor_t *cursor);
void moveCursorLeft(cursor_t *cursor);
void moveCursorRight(cursor_t *cursor);

void moveCursorToBoatOrigin(Boat boat, cursor_t *cursor);

void writeCursorPosition(cursor_t *cursor);

#endif /* CURSOR_H_ */
