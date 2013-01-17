/*
 * coin.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"

#ifndef COIN_H_
#define COIN_H_

Sprite *coins[15];
int coins_left;
int nbrCoins;

void checkForCoin(Sprite *player);
void collectCoin(Sprite *coin);
void setupCoins(OBJ_ATTR shadowOAM[], int hOff, int vOff);
void updateCoins(int hOff, int vOff);
void freeCoins();
void drawCoins();

#endif /* COIN_H_ */
