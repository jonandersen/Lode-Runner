/*
 * game.h
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"

#ifndef GAME_H_
#define GAME_H_

#define PLAYER_SPEED 1

unsigned short levelA[1024];
unsigned short levelB[1024];

unsigned short cheat;

Sprite player;
int playerSprite;
int player_walk_animation;
int player_fall_animation;

OBJ_ATTR shadowOAM[128];

int hOff, vOff;
int hOff_count, vOff_count;

#define WEST -1
#define EAST 1
#define NORTH -1
#define SOUTH 1
#define NONE 0

#define H_SCROLL_MAX 272
#define V_SCROLL_MAX 96

#define H_SPRITE_MAX 224
#define H_SPRITE_MIN 0

#define V_SPRITE_MAX 144
#define V_SPRITE_MIN 0

#define H_CENTER 112
#define V_CENTER 80

void scrollMap(int horizontal, int vertical);

void setupGame();
void runGame();
void setupSprites();
int checkCollisionMap(int absRow, int absCol);
int shouldFall(int absRow, int absCol);
int canWalkLadder(int absRow, int absCol);
int getTile(int row, int col, int width, int height);
void changeTile(int row, int col, int width, int height, int tile);
int haveWon();
void initGame();
int canMoveHorizontal(int absRow, int absCol, int cd);

typedef struct TilesRemoved{
	int tile;
	int vBlank;
	int absRow;
	int absCol;
	int widht;
	int height;
	struct TilesRemoved *next;
} TilesRemoved;

TilesRemoved *queue;

Sprite shoot;

#define reGrowTime 360

void addToRemove(int tile, int vBlank, int absRow, int absCol, int width, int height);
void reGrow(int vBlank);
void freeReGrow();



unsigned int lost;

unsigned int buttons_game;
unsigned int oldButtons_game;

#define BUTTON_PRESSED_GAME(key) (!(~(oldButtons_game)&(key)) && (~buttons_game & (key)))

int level;

unsigned int frame;


#endif /* GAME_H_ */
