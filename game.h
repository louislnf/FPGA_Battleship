/*
 * game.h
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#ifndef GAME_H_
#define GAME_H_

#define NUMBER_OF_BOATS 4
#define GRID_SIZE 10

typedef enum GameMode {
    PLACING,
    SHOOTING,
    OVER
} GameMode;

typedef enum BoatDirection {
    NORTH,
    SOUTH,
    EAST,
    WEST
} BoatDirection;

typedef enum ShotState {
    NOT_SHOT,
    SHOT_IN_WATER,
    SHOT_IN_BOAT
} ShotState;

typedef struct Point {
    char x;
    char y;
} Point;

typedef struct Boat {
    char size;
    Point origin;
    BoatDirection direction;
    char numberOfHits;
} Boat;

typedef struct Player {
    Boat* boats;
    char gridSize;
    char numberOfBoats;
    char numberOfBoatsPlaced;
    ShotState** shotsMap;
} Player;

Point getBoatEndPoint(Boat boat);
char pointInGrid(Point p, char gridSize);
char boatFitsInGrid(Boat boat, char gridSize);
char isPartOfBoat(Point p, Boat boat);
Point* getBoatPoints(Boat boat);
char boatsCollide(Boat b1, Boat b2);
Player* initializePlayer();
void initializeBoats(Player* player);
char canPlaceBoatForPlayer(Player *player, Boat boat);
void moveBoat(Boat *boat, BoatDirection direction);


/* TODO */

/*
 * returns 1 if the shooter hasnt yet shot here
 * else returns 0
 */
char canShootAt(Player *shooter, Point shotLocation);

/*
 * updates the different players data following the shot
 * we assume the shooter CAN SHOOT
 */ 
void shoot(Player *shooter, Player *target, Point shotLocation);

/*
 * returns a Point where the ia should shoot based on the result of the former shots
 * try to shoot next to a former successful shot 
 */
Point ia_whereToShoot(Player* ia)



#endif /* GAME_H_ */
