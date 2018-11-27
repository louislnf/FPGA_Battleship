
#include "game.h"

Point getBoatEndPoint(Boat boat) {
    Point endPoint;
    endPoint.x = boat.origin.x;
    endPoint.y = boat.origin.y;
    switch (boat.direction) {
        case NORTH:
            endPoint.y = endPoint.y - boat.size + 1;
            break;
        case SOUTH:
            endPoint.y = endPoint.y + boat.size - 1;
            break; 
        case WEST:
            endPoint.x = endPoint.x - boat.size + 1;
            break;
        case EAST:
            endPoint.x = endPoint.x + boat.size - 1;
            break;
        default:
            break;
    }
    return endPoint;
}

char pointInGrid(Point p, char gridSize) {
    return p.x >= 0 && p.x < gridSize && p.y >= 0 && p.y < gridSize;
}

char boatFitsInGrid(Boat boat, char gridSize) {
    return pointInGrid(boat.origin, gridSize) && pointInGrid(getBoatEndPoint(boat), gridSize);
}

char isPartOfBoat(Point p, Boat boat) {
    switch (boat.direction) {
        case NORTH:
            if (p.x == boat.origin.x && p.y <= boat.origin.y && p.y > boat.origin.y-boat.size) {
                return 1;
            }
            break;
        case SOUTH:
            if (p.x == boat.origin.x && p.y >= boat.origin.y && p.y < boat.origin.y+boat.size) {
                return 1;
            }
            break; 
        case WEST:
            if (p.y == boat.origin.y && p.x <= boat.origin.x && p.x > boat.origin.x-boat.size) {
                return 1;
            }
            break;
        case EAST:
            if (p.y == boat.origin.y && p.x >= boat.origin.x && p.x < boat.origin.x+boat.size) {
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

Point* getBoatPoints(Boat boat) {
    Point* points = (Point*)malloc(boat.size*sizeof(Point));
    int i;
    for (i=0; i<boat.size; i++) {
        points[i] = boat.origin;
        switch (boat.direction) {
        case NORTH:
            points[i].y = boat.origin.y-i;
            break;
        case SOUTH:
            points[i].y = boat.origin.y+i;
            break;
        case EAST:
            points[i].x = boat.origin.x+i;
            break;
        case WEST:
            points[i].x = boat.origin.x-i;
            break;
        }
    }
    return points;
}

char boatsCollide(Boat b1, Boat b2) {
    Point *p1, *p2;
    p1 = getBoatPoints(b1);
    p2 = getBoatPoints(b2);
    char numberOfCollisions = 0;
    int i;
    for (i=0; i<b1.size; i++) {
        int j;
        for (j=0; j<b2.size; j++) {
            if (p1[i].x == p2[j].x && p1[i].y == p2[j].y) {
                numberOfCollisions++;
            }
        }
    }
    free(p1);
    free(p2);
    return numberOfCollisions;
}

Player* initializePlayer() {
    Player* player = (Player*)malloc(sizeof(Player));
    player->gridSize = GRID_SIZE;
    player->numberOfBoats = NUMBER_OF_BOATS;
    player->numberOfBoatsPlaced = 0;
    player->shotsMap = (ShotState**)malloc(GRID_SIZE*sizeof(ShotState*));
    int i;
    for (i=0; i<GRID_SIZE; i++) {
    	player->shotsMap = (ShotState*) malloc(GRID_SIZE*sizeof(ShotState));
    	int j;
    	for (j=0; j<GRID_SIZE; j++) {
    		player->shotsMap[i][j] = NOT_SHOT;
    	}
    }
    return player;
}

void initializeBoats(Player* player) {
    Boat* boats = (Boat*) malloc(NUMBER_OF_BOATS*sizeof(Boat));
    int i;
    for (i=0; i<NUMBER_OF_BOATS; i++) {
        boats[i].origin.x = player->gridSize/2;
        boats[i].origin.y = player->gridSize/2;
        boats[i].direction = WEST;
        boats[i].numberOfHits = 0;
    }
    boats[0].size = 5;
    boats[1].size = 4;
    boats[2].size = 3;
    boats[3].size = 2;
    player->boats = boats;
}

char canPlaceBoatForPlayer(Player *player, Boat boat) {
    // checking if player hasnt already placed all his boats and if the boat fits in the grid
    if (player->numberOfBoatsPlaced == player->numberOfBoats || !boatFitsInGrid(boat, GRID_SIZE)) {
        return 0;
    }
    // checking if the new boat does not collide with the other boats of the player
    int i;
    for (i=0; i<player->numberOfBoatsPlaced; i++) {
        if (boatsCollide(boat, player->boats[i])) {
            return 0;
        }
    }
    return 1;
}

void moveBoat(Boat *boat, BoatDirection direction) {
    switch (direction) {
    case NORTH:
        boat->origin.y -= 1;
        break;
    case SOUTH:
        boat->origin.y += 1;
        break;
    case WEST:
        boat->origin.x -= 1;
        break;
    case EAST:
        boat->origin.x += 1;
        break;
    default:
        break;
    }
}
