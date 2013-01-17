/*
 * states.c
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"
#include "gamestates.h"
#include "splash.h"
#include "game.h"
#include "res/lose.h"
#include "menus.h"
#include "res/win.h"
#include "Libraries/text.h"

void runWin(){
	if(BUTTON_HELD(BUTTON_START)){
		setupSplash();
		stateFunction = runSplash;
	}
}
void runPause(){
	if(BUTTON_HELD(BUTTON_START)){
		setupGame();
		stateFunction = runGame;
	}
}
void runLose(){
	if(BUTTON_HELD(BUTTON_START)){
		setupSplash();
		stateFunction = runSplash;
	}
}

void setupStates(){
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	drawRect3(0,0,160,240,BLACK);
}

void setupStatesWin(){
	setupStates();
	drawImage3(winBitmap,0,0,160,240);

}
void setupStatesLose(){
	setupStates();
	drawImage3(loseBitmap,0,0,160,240);
}
void setupStatesPause(){
	setupStates();
	drawString3(90,20,"Lame pause screen...", WHITE);
	drawString3(120,20,"To continue press START.....", WHITE);
}
