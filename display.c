/*
 * display.c
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#include "display.h"
#include "game.h"

char convertToMemoryAddress(char row, char col, char gridNumber) {
	char adr = 10*row+col;
	switch (gridNumber) {
	case 1:
		return adr;
		break;
	case 2:
		return 100+adr;
		break;
	default:
		return 201;
		break;
	}
}

void displayColorInGrid(char row, char col, Color color, char gridNumber) {
	char adr = convertToMemoryAddress(row, col, gridNumber);
	writeMemory(adr, color);
}

void drawBoat(Boat boat, Color color, char gridNumber) {
	Point* points = getBoatPoints(boat);
	int i;
	for (i=0; i<boat.size; i++) {
		if (points[i].x >= 0 && points[i].x < GRID_SIZE && points[i].y >= 0 && points[i].y < GRID_SIZE) {
			displayColorInGrid(points[i].x, points[i].y, color, gridNumber);
		}
	}
	free(points);
}

void drawPlayerBoats(Player *player, char gridNumber) {
	int i;
	for (i=0; i<player->numberOfBoatsPlaced; i++) {
		drawBoat(player->boats[i], Blue, gridNumber);
	}
	// if the player hasnt finished placing his boats we draw the one he is currently placing in a different color
	if (player->numberOfBoats != player->numberOfBoatsPlaced) {
		drawBoat(player->boats[player->numberOfBoatsPlaced], Cyan, gridNumber);
	}
}