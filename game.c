/*
 * game.c
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */

#include "game.h"
#include "Libraries/myLib.h"
#include "res/levels.h"
#include "res/tiles.h"
#include "res/sprites.h"
#include "states.h"
#include "gamestates.h"
#include "characters.h"
#include <stdlib.h>
#include "coin.h"
#include "enemies.h"
#include "res/audio_resources.h"
#include "Libraries/soundLib.h"
#include "res/bg1.h"

void setupGame() {
	int i;
	unsigned short * lvlA = levels_A(level);
	unsigned short * lvlB = levels_B(level);
	for (i = 0; i < 1024; i++) {
		levelA[i] = lvlA[i];
		levelB[i] = lvlB[i];
	}

	REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE| SPRITE_ENABLE;
	REG_BG0CNT = BG_SIZE1 | CBB(0) | SBB(30) | COLOR256 | 0;
	REG_BG1CNT = BG_SIZE0 | CBB(1) | SBB(29) | COLOR256 | 1;

	DMANow(3, (unsigned short*) tilesPal, PALETTE, 256 );

	DMANow(3, (void*) tilesTiles, (void*) CHARBLOCKBASE[0].tileimg,
			tilesTilesLen / 2);
	DMANow(3, (void*) bgTiles, (void*) CHARBLOCKBASE[1].tileimg,
			bgTilesLen / 2);
	DMANow(3, (void*) bgMap, (void*) SCREENBLOCKBASE[29].tilemap, bgMapLen/2);

	DMANow(3, (void*) levelA, (void*) SCREENBLOCKBASE[30].tilemap, 1024);
	DMANow(3, (void*) levelB, (void*) SCREENBLOCKBASE[31].tilemap, 1024);

	initGame();

	setupSprites();

	setupCoins(shadowOAM, hOff, vOff);
	setupEnemies(shadowOAM, hOff, vOff);



}

void initGame() {

	vOff = vOffL(level);
	hOff = hOffL(level);
	hOff_count = 0;
	vOff_count = 0;

	lost = 0;

	player.cCount = 0;
	player.rCount = 0;

	player.speed = 1;

	player.row = PR(level);
	player.col = PC(level);
	player.arow = player.row;
	player.acol = player.arow ;
	playerSprite = 0;
	cheat = 0;
	frame = 0;

}

void setupSprites() {
	DMANow(3, (unsigned int*) spriteTiles, &CHARBLOCKBASE[4],
			spriteTilesLen / 2);
	DMANow(3, (unsigned int*) spritePal, SPRITE_PALETTE, spritePalLen / 2);
	int i;
	for (i = 0; i < 128; i++) {
		shadowOAM[i].attr0 = 0;
		shadowOAM[i].attr1 = 0;
		shadowOAM[i].attr2 = 0;
		shadowOAM[i].attr0 = ATTR0_HIDE;
	}

	player.spriteAttr0 = &(shadowOAM[playerSprite].attr0);
	player.spriteAttr1 = &(shadowOAM[playerSprite].attr1);
	player.spriteAttr2 = &(shadowOAM[playerSprite].attr2);

	*player.spriteAttr0 = player.row;
	*player.spriteAttr1 = ATTR1_SIZE16 | player.col;
	*player.spriteAttr2 = PLAYER_NORMAL;

	player_walk_animation = 0;
	player_fall_animation = 0;
}

void runGame() {
	buttons_game = BUTTONS;

	frame++;

	int absRow = player.row + vOff;
	int absCol = player.col + hOff;

	if (BUTTON_HELD(BUTTON_SELECT)) {
			while(!BUTTON_HELD(BUTTON_START)){

			}
	}else if (haveWon()) {
		waitVB(20);
		freeCoins();
		freeEnemies();
		freeReGrow();
		if(level <= NUMBER_OF_LEVELS){
			level ++;
			setupGame();
			return;
		}else{
			stateFunction = runWin;
			setupStatesWin();
			return;
		}
	}else if (lost) {
		waitVB(180);
		freeReGrow();
		freeCoins();
		freeEnemies();
		stateFunction = runLose;
		setupStatesLose();
		return;
	}else if (shouldFall(absRow, absCol)) {
		playerFall(&player, vOff);
	}else if (BUTTON_HELD(BUTTON_UP)) {
		movePlayer(UP, &player, vOff, hOff);
	} else if (BUTTON_HELD(BUTTON_DOWN)) {
		movePlayer(DOWN, &player, vOff, hOff);
	} else if (BUTTON_HELD(BUTTON_LEFT)) {
		movePlayer(LEFT, &player, vOff, hOff);
	} else if (BUTTON_HELD(BUTTON_RIGHT)) {
		movePlayer(RIGHT, &player, vOff, hOff);
	} else if (BUTTON_PRESSED_GAME(BUTTON_A)) {
		*(player.spriteAttr1) |= ATTR1_HFLIP;
		//Add boundry checks!
		int tile = getTile(absRow, absCol - 1, 0, 17);
		int tile2 = getTile(absRow, absCol - 9, 0, 17);
		if (isDestroyable(tile)) {
			changeTile(absRow, absCol - 1, 0, 17, FREE);
			addToRemove(tile, vBlanks, absRow, absCol - 1, 0, 17);
			//shotSetup(absRow + 5, absCol -15, absRow,absCol);

			playSound(A, (unsigned char*)gun_plasmafire_11025Hz, GUN_PLASMAFIRE_11025HZ_SIZE, 11025, 0);
			waitVB(2);
		}
		if (isDestroyable(tile2)) {
			changeTile(absRow, absCol - 9, 0, 17, FREE);
			addToRemove(tile2, vBlanks, absRow, absCol - 9, 0, 17);
		}

		waitForVblank();

		DMANow(3, (void*) levelA, (void*) SCREENBLOCKBASE[30].tilemap, 1024);
		DMANow(3, (void*) levelB, (void*) SCREENBLOCKBASE[31].tilemap, 1024);
	} else if (BUTTON_PRESSED_GAME(BUTTON_B)) {
		*(player.spriteAttr1) &= ~ATTR1_HFLIP;
		//Add boundry checks!
		int tile = getTile(absRow, absCol + 17, 0, 17);
		int tile2 = getTile(absRow, absCol + 17 + 8, 0, 17);
		if (isDestroyable(tile)) {
			changeTile(absRow, absCol + 17, 0, 17, FREE);
			addToRemove(tile, vBlanks, absRow, absCol + 17, 0, 17);
			playSound(A, (unsigned char*)gun_plasmafire_11025Hz, GUN_PLASMAFIRE_11025HZ_SIZE, 11025, 0);
			waitVB(2);
		}
		if (isDestroyable(tile2)) {
			changeTile(absRow, absCol + 17 + 8, 0, 17, FREE);
			addToRemove(tile2, vBlanks, absRow, absCol + 17 + 8, 0, 17);
		}

		waitForVblank();

		DMANow(3, (void*) levelA, (void*) SCREENBLOCKBASE[30].tilemap, 1024);
		DMANow(3, (void*) levelB, (void*) SCREENBLOCKBASE[31].tilemap, 1024);
	}else if(BUTTON_PRESSED_GAME(BUTTON_R)){
		cheat = !cheat;
	}else {
		player_fall_animation = 0;
		movePlayer(-1, &player, vOff, hOff);
	}
	if (vBlanks % 20 == 0) {
		reGrow(vBlanks);
	}
	updateCoins(hOff, vOff);
	updateEnemies(hOff, vOff);

	drawSprite(&player);
	drawCoins();
	drawEnemies();

	waitForVblank();
	DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
	oldButtons_game = buttons_game;

	REG_BG0VOFS = vOff;
	REG_BG0HOFS = hOff;
	REG_BG1VOFS = vOff/3 + 32;
	REG_BG1HOFS = hOff/3;
}

void addToRemove(int tile, int vBlank, int absRow, int absCol, int width,
		int height) {
	TilesRemoved *new = malloc(sizeof(TilesRemoved));
	if (new == NULL) {
		//exit(0);
	}
	new->tile = tile;
	new->vBlank = vBlank;
	new->absRow = absRow;
	new->absCol = absCol;
	new->widht = width;
	new->height = height;
	new->next = NULL;
	TilesRemoved *currentSegment = queue;
	if (currentSegment == NULL) {
		queue = new;
		return;
	}
	while (currentSegment != NULL) {
		if (currentSegment->next == NULL) {
			currentSegment->next = new;
			return;
		}
		currentSegment = currentSegment->next;
	}
}
void reGrow(int vBlank) {
	TilesRemoved *currentSegment = queue;
	while (currentSegment != NULL) {
		if (currentSegment->vBlank + reGrowTime < vBlank) {
			queue = currentSegment->next;
			changeTile(currentSegment->absRow, currentSegment->absCol,
					currentSegment->widht, currentSegment->height,
					currentSegment->tile);
			free(currentSegment);
			DMANow(3, (void*) levelA, (void*) SCREENBLOCKBASE[30].tilemap,
					1024);
			DMANow(3, (void*) levelB, (void*) SCREENBLOCKBASE[31].tilemap,
					1024);
			return;
		}
		currentSegment = currentSegment->next;
	}
}

void freeReGrow(){
	TilesRemoved *currentSegment = queue;
	while (currentSegment != NULL) {
		TilesRemoved *temp =  currentSegment->next;
		free(currentSegment);
		currentSegment = temp;
	}
	queue = NULL;
}

void scrollMap(int horizontal, int vertical) {
	hOff_count += horizontal;
	if (hOff_count % PLAYER_SPEED == 0) {
		hOff += horizontal;
		if (hOff < 0) {
			hOff = max(hOff, 0);
		} else {
			hOff = min(hOff,H_SCROLL_MAX);
		}
	}
	vOff_count += vertical;
	if (vOff_count % PLAYER_SPEED == 0) {
		vOff += vertical;
		if (vOff < 0) {
			vOff = max(vOff, 0);
		} else {
			vOff = min(vOff,V_SCROLL_MAX);
		}
	}
}

int checkCollisionMap(int absRow, int absCol) {
	return getTile(absRow, absCol, 0, 15) != FREE
			|| getTile(absRow, absCol, 8, 15) != FREE;
}

int shouldFall(int absRow, int absCol) {
	return !(checkCollisionMap(absRow + 1, absCol));
			//&& checkCollisionMap(absRow + 1, absCol + 4));
}

int canWalkLadder(int absRow, int absCol) {
	return (isLadder(getTile(absRow, absCol, 4, 15)))
			&& (isLadder(getTile(absRow, absCol, 12, 15)));
}

int getTile(int row, int col, int width, int height) {
	if (col < 256) {
		int r = (row + height) / 8;
		int c = (col + width) / 8;
		return levelA[OFFSET(r,c,LEVEL_WIDTH)];
	} else {
		//-1, no idea why this is needed. Should be looked into
		int r = (row + height) / 8 - 1;
		int c = (col + width) / 8;
		return levelB[OFFSET(r,c,LEVEL_WIDTH)];
	}
}

void changeTile(int row, int col, int width, int height, int tile) {
	if (col < 256) {
		int r = (row + height) / 8;
		int c = (col + width) / 8;
		levelA[OFFSET(r,c,LEVEL_WIDTH)] = tile;
	} else {
		//-1, no idea why this is needed. Should be looked into
		int r = (row + height) / 8 - 1;
		int c = (col + width) / 8;
		levelB[OFFSET(r,c,LEVEL_WIDTH)] = tile;
	}
}

int haveWon() {
	return coins_left == 0;
}

int canMoveHorizontal(int absRow, int absCol, int cd) {
	if (cd < 0) {
		return (getTile(absRow, absCol + cd, 0, 15) == FREE)
				|| isLadder(getTile(absRow, absCol + cd, 0, 15));
	} else {
		return getTile(absRow, absCol + cd + 15, 0, 15) == FREE
				|| isLadder(getTile(absRow, absCol + cd + 15, 0, 15));
	}
}

