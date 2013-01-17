/*
 * splash.c
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */
#include "splash.h"
#include "gamestates.h"
#include "Libraries/myLib.h"
#include "Libraries/soundLib.h"
#include "res/audio_resources.h"
#include "game.h"
#include "instructions.h"
#include "res/bg1.h"
#include "res/tiles.h"
#include "menus.h"

enum {PLAY,INSTRUCTIONS};
int selected;
#define MAP_ROW 60

void setupSplash(){
	waitForVblank();
	level = 1;

	REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
	REG_BG0CNT = BG_SIZE0 | CBB(0) | SBB(31) | COLOR256 | 0;

	DMANow(3, (unsigned short*) tilesPal, PALETTE, 256 );

	DMANow(3, (void*) bgTiles, (void*) CHARBLOCKBASE[0].tileimg,bgTilesLen / 2);
	DMANow(3, (void*) bgMap, (void*) SCREENBLOCKBASE[31].tilemap, bgMapLen/2);


	DMANow(3, (unsigned int*) menusTiles, &CHARBLOCKBASE[4],menusTilesLen / 2);
	DMANow(3, (unsigned int*) menusPal, SPRITE_PALETTE, menusPalLen / 2);
	int i;
	for (i = 0; i < 128; i++) {
		shadowOAM[i].attr0 = 0;
		shadowOAM[i].attr1 = 0;
		shadowOAM[i].attr2 = 0;
		shadowOAM[i].attr0 = ATTR0_HIDE;
	}

	//RIGHT
	shadowOAM[2].attr0 = 128 ;
	shadowOAM[2].attr1 = ATTR1_SIZE32 | 208;
	shadowOAM[2].attr2 = S_O_64(3*64,0);

	//LEFT
	shadowOAM[3].attr0 = 128 | ATTR0_HIDE;
	shadowOAM[3].attr1 = ATTR1_SIZE32 | ATTR1_HFLIP;
	shadowOAM[3].attr2 = S_O_64(3*64,0);

	//UP
	shadowOAM[4].attr0 = 8;
	shadowOAM[4].attr1 = ATTR1_SIZE32 | (197 -32);
	shadowOAM[4].attr2 = S_O_64(3*64,4);

	//DOWN
	shadowOAM[5].attr0 = 8;
	shadowOAM[5].attr1 = ATTR1_SIZE32 | 45;
	shadowOAM[5].attr2 = S_O_64(3*64,8);

	//INFO
	shadowOAM[6].attr0 = 0;
	shadowOAM[6].attr1 = ATTR1_SIZE64 | 197;
	shadowOAM[6].attr2 = S_O_64(2*64,16);

	//PLAY
	shadowOAM[7].attr0 = 0;
	shadowOAM[7].attr1 = ATTR1_SIZE64 | 0;
	shadowOAM[7].attr2 = S_O_64(0*64,16);






	shadowLevel();
	selected = 0;
	vBlanks = 0;
	REG_BG0VOFS = 32;
	REG_BG0HOFS = 64;
	animate= 0;
	start = 0;
	nextAnimateLevel = 0;
	dir =0;
}
void shadowLevel(){
	shadowOAM[0].attr0 = MAP_ROW;
	shadowOAM[0].attr1 = ATTR1_SIZE64| 50;
	shadowOAM[0].attr2 = S_O_64((level -1) *64,0);

	shadowOAM[1].attr0 = MAP_ROW;
	shadowOAM[1].attr1 = ATTR1_SIZE64| (50 + 64);
	shadowOAM[1].attr2 = S_O_64((level -1) *64,8);
}

void runSplash(){
	if(level >= 3){
		shadowOAM[2].attr0 = 128 | ATTR0_HIDE;
		shadowOAM[3].attr0 = 128;
	}else if(level <= 1){
		shadowOAM[2].attr0 = 128;
		shadowOAM[3].attr0 = 128 | ATTR0_HIDE;
	}else{
		shadowOAM[2].attr0 = 128;
		shadowOAM[3].attr0 = 128;
	}
	buttons_s = BUTTONS;
	if(animate){
		int col = COLMASK & shadowOAM[0].attr1;
		col += dir;
		shadowOAM[0].attr1 = ATTR1_SIZE64| col;
		shadowOAM[1].attr1 = ATTR1_SIZE64| (col + 64);
		animate --;
		if(animate <= 0){
			shadowLevel();
		}
	}else if(BUTTON_PRESSED_S(BUTTON_RIGHT)){
		level ++;
		if(level > 3){
			level = 3;
		}else{
			playSound(A, (unsigned char*)click_11025Hz, CLICK_11025HZ_SIZE, 11025, 0);

			if(level < 3){
				shadowOAM[2].attr0 = 128 | ATTR0_HIDE;
				waitForVblank();
				DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
				waitVB(10);
				shadowOAM[2].attr0 = 128;
				waitForVblank();
				DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
			}


			start = COLMASK & shadowOAM[0].attr1;
			animate = 32 + 64 + 64;
			dir = -2;
		}
	}else if(BUTTON_PRESSED_S(BUTTON_LEFT)){
		level --;
		if(level < 1){
			level = 1;
		}else{
			playSound(A, (unsigned char*)click_11025Hz, CLICK_11025HZ_SIZE, 11025, 0);

			if(level > 1){
				shadowOAM[3].attr0 = 128 | ATTR0_HIDE;
				waitForVblank();
				DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
				waitVB(10);
				shadowOAM[3].attr0 = 128;
				waitForVblank();
				DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
			}

			animate = 32 + 64 + 64;
			dir = 2;
		}

	}else if(BUTTON_HELD(BUTTON_UP)){
		setupGame();
		//initGame();
		stateFunction = runGame;
		selected = PLAY;
	}else if(BUTTON_HELD(BUTTON_DOWN)){
		setupInstructions();
		stateFunction = runInstructions;
		selected = INSTRUCTIONS;
	}
	waitForVblank();
	DMANow(3, shadowOAM, OAM, sizeof(shadowOAM) / 2);
	oldButtons_s = buttons_s;
}

