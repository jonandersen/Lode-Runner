/*
 * enemy.c
 *
 *  Created on: Nov 18, 2011
 *      Author: jonandersen
 */
#include "enemies.h"
#include "res/levels.h"
#include "Libraries/myLib.h"
#include "res/sprites.h"
#include "game.h"
#include "characters.h"
#include <stdlib.h>
#include "Libraries/soundLib.h"
#include "res/audio_resources.h"

void setupEnemies(OBJ_ATTR shadowOAM[], int hOff, int vOff) {
	nbrEnemies = levelEnemies(level);
	unsigned short *enemiesRow = enemyRow(level);
	unsigned short *enemiesCol = enemyCol(level);
	int i;
	for (i = 0; i < nbrEnemies; i++) {
		enemies[i] = malloc(sizeof(Sprite));
		if(enemies[i] == NULL){
			exit(0);
		}
		Sprite *enemey = enemies[i];
		enemy_walk_animation[i] = 0;
		enemey->cCount = 0;
		enemey->rCount = 0;

		enemey->speed = 2;

		enemey->row = enemiesRow[i];
		enemey->col = enemiesCol[i];
		enemey->arow = enemey->row + vOff;
		enemey->acol = enemey->col  + hOff;

		enemey->spriteAttr0 = &(shadowOAM[levelCoins(level) + 1 + i].attr0);
		enemey->spriteAttr1 = &(shadowOAM[levelCoins(level)  + 1 + i].attr1);
		enemey->spriteAttr2 = &(shadowOAM[levelCoins(level)  + 1 + i].attr2);

		*enemey->spriteAttr0 = enemey->arow;
		*enemey->spriteAttr1 = ATTR1_SIZE16 | enemey->acol;
		*enemey->spriteAttr2 = ENEMY_NORMAL;

	}

}
int rMovment(Sprite *enemey) {
	if (player.arow < enemey->arow && canWalkLadder(enemey->row, enemey->col)) {
		return -1;
	} else if (player.arow > enemey->arow
			&& canWalkLadder(enemey->row + 1, enemey->col)) {
		return 1;
	}
	return 0;
}

int cMovment(Sprite *enemey) {
	if (player.col < enemey->acol) {
		return -1;
	} else if (player.col > enemey->acol) {
		return 1;
	}
	return 0;
}

void updateEnemies(int hOff, int vOff) {
	int i;
	for (i = 0; i < nbrEnemies; i++) {
		if(frame % ANIMATION_SPEED_PLAYER == 0){
			enemy_walk_animation[i] = (enemy_walk_animation[i] + 4) % (4*ENEMY_WALK_STEPS);
		}

		Sprite *enemey = enemies[i];
		if (shouldFall(enemey->row, enemey->col)) {
			moveEnemies(SOUTH, NONE, enemey);
			*enemey->spriteAttr2 = ENEMY_FALL;
		} else {
			int rd = rMovment(enemey);
			int cd = cMovment(enemey);
			if (rd) {
				enemey->rCount++;
				moveEnemies(rd, 0, enemey);
			} else if(cd){
				if (cd) {
					enemey->cCount++;
					moveEnemies(0, cd, enemey);
					if(cd < 0){
						*(enemey->spriteAttr2) = enemy_walk_animation[i] + ENEMY_NORMAL;
						*(enemey->spriteAttr1) &= ~ATTR1_HFLIP;
					}else{
						*(enemey->spriteAttr2) = enemy_walk_animation[i] + ENEMY_NORMAL;
						*(enemey->spriteAttr1) |= ATTR1_HFLIP;
					}
				}else{
					enemy_walk_animation[i] = 0;
				}
			}else{
				*enemey->spriteAttr2 = ENEMY_NORMAL;
			}
		}
		enemey->arow = enemey->row - vOff;
		enemey->acol = enemey->col - hOff;

		if (checkCollision(&player, enemey) && !cheat) {
			playSound(A, (unsigned char*)creature_roar1_11025Hz, CREATURE_ROAR1_11025HZ_SIZE, 11025, 0);
			lost = vBlanks;
			waitVB(2);
		}
	}

}

void moveEnemies(int rd, int cd, Sprite *enemey) {
	if (rd && enemey->rCount % enemey->speed) {
		enemey->row += rd;

	}else if (cd && (enemey->cCount) % enemey->speed
			&& canMoveHorizontal(enemey->row, enemey->col, cd)) {
		enemey->col += cd;
	}
}

void drawEnemies() {
	int i;
	for (i = 0; i < nbrEnemies; i++) {
		drawSprite(enemies[i]);
	}
}

void freeEnemies() {
	int i;
	for (i = 0; i < nbrEnemies; i++) {
		free(enemies[i]);
	}
}
