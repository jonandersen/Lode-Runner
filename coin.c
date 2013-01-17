/*
 * coin.c
 *
 *  Created on: Nov 18, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"
#include "coin.h"
#include <stdlib.h>
#include "res/levels.h"
#include "game.h"
#include "Libraries/soundLib.h"
#include "res/audio_resources.h"

void checkForCoin(Sprite *player) {
	int i;
	for (i = 0; i < nbrCoins; i++) {
		if (!(*(coins[i]->spriteAttr0) & ATTR0_HIDE)) {
			if (checkCollision(player, coins[i])) {
				collectCoin(coins[i]);
				break;
			}
		}
	}

}

void collectCoin(Sprite *coin) {
	playSound(A, (unsigned char*)p_up_11025Hz, P_UP_11025HZ_SIZE, 11025, 0);
	*(coin->spriteAttr0) = 0;
	*(coin->spriteAttr1) = 0;
	*(coin->spriteAttr0) = ATTR0_HIDE;
	coins_left--;
	waitVB(2);
}

void setupCoins(OBJ_ATTR shadowOAM[], int hOff, int vOff) {
	nbrCoins = levelCoins(level);
	unsigned short *coinRowLocation = coinRow(level);
	unsigned short *coinColLocation = coinCol(level);
	int i;
	for (i = 0; i < nbrCoins; i++) {
		coins[i] = malloc(sizeof(Sprite));
		if (coins[i] == NULL) {
			exit(0);
		} else {
			coins[i]->spriteAttr0 = &(shadowOAM[i + 1].attr0);
			coins[i]->spriteAttr1 = &(shadowOAM[i + 1].attr1);
			coins[i]->spriteAttr2 = &(shadowOAM[i + 1].attr2);

			coins[i]->row = coinRowLocation[i];
			coins[i]->arow = coins[i]->row - hOff;
			coins[i]->col = coinColLocation[i];
			coins[i]->acol = coins[i]->col - vOff;

			*(coins[i]->spriteAttr0) = coins[i]->arow;
			*(coins[i]->spriteAttr1) = ATTR1_SIZE16 | coins[i]->acol;
			*(coins[i]->spriteAttr2) = S_O(4,0);
		}
	}
	coins_left = nbrCoins;
}

void updateCoins(int hOff, int vOff) {
	int i;
	for (i = 0; i < nbrCoins; i++) {
		coins[i]->arow = coins[i]->row - vOff;
		coins[i]->acol = coins[i]->col - hOff;
	}

}

void freeCoins() {
	int i;
	for (i = 0; i < nbrCoins; i++) {
		free(coins[i]);
	}
}

void drawCoins() {
	int i;
	for (i = 0; i < nbrCoins; i++) {
		drawSprite(coins[i]);
	}
}
