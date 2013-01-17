/*
 * instructions.c
 *
 *  Created on: Nov 1, 2011
 *      Author: jonandersen
 */


#include "instructions.h"
#include "Libraries/myLib.h"
#include "splash.h"
#include "gamestates.h"
#include "ins/ins1.h"
#include "ins/ins2.h"
#include "ins/ins3.h"
#include "ins/ins4.h"
#include "ins/ins5.h"
#include "Libraries/text.h"

void setupInstructions(){
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	nbr = 0;
	drawImage3(ins1Bitmap,0,0,160,240);
	drawString3(140,20,"To return press SELECT", WHITE);
	drawString3(150,20,"To continue press START", WHITE);
}
void runInstructions(){
	buttonsIns = BUTTONS;
	if(BUTTON_PRESSED_INS(BUTTON_SELECT)){
		setupSplash();
		stateFunction = runSplash;
	}else if(BUTTON_PRESSED_INS(BUTTON_START)){
		waitForVblank();
		nbr = (nbr +1) %6;
		switch(nbr){
		case 0: drawImage3(ins1Bitmap,0,0,160,240);
		drawString3(140,20,"To return press SELECT", WHITE);
		drawString3(150,20,"To continue press START", WHITE);
		break;
		case 1: drawImage3(ins2Bitmap,0,0,160,240); break;
		case 2: drawImage3(ins3Bitmap,0,0,160,240); break;
		case 3: drawImage3(ins4Bitmap,0,0,160,240); break;
		case 4: drawImage3(ins5Bitmap,0,0,160,240); break;
		case 5: drawRect3(0,0,160,240, BLACK); drawString3(40,20,"To PAUSE at any time press SELECT",WHITE);
		drawString3(50,20,"To return from PAUSE press START",WHITE);
		drawString3(60,20,"To turn cheat ON/OFF press R",WHITE);
		break;
		}
	}
	oldButtonsIns = buttonsIns;
}
