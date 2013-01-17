/*
 * characters.c
 *
 *  Created on: Nov 17, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"
#include "characters.h"
#include "game.h"
#include "res/sprites.h"
#include "coin.h"

void playerFall(Sprite *player, int vOff) {
	if (player->row < V_CENTER || vOff >= V_SCROLL_MAX) {
		moveSprite(SOUTH, NONE, player);
	} else {
		scrollMap(NONE, SOUTH);
	}

	*(player->spriteAttr2) = S_O(2,0);
	player->arow = player->row;
	player->acol = player->col;

	checkForCoin(player);
}

void animateShoot(int vBlanks, Sprite *shot) {
	if (vBlanks < shot->cCount + 90) {
		if (vBlanks % 3 == 0) {
			//int row = (shot->arow) + ((float) vBlanks / (float) shot->cCount)* ((shot->row) - (shot->arow));
			*shot->spriteAttr0 = (shot->arow) ;
			//int col = (shot->acol)+ ((float) vBlanks / (float) shot->cCount)* ((shot->col) - (shot->acol));
			*shot->spriteAttr1 = ATTR1_SIZE16 | (shot->acol);
			*shot->spriteAttr2 = S_O(8,(vBlanks % 16)/2);
		}
	} else {
		isShooting = 0;
		*shot->spriteAttr0 = ATTR0_HIDE;
	}

}

void movePlayer(int direction, Sprite *player, int vOff, int hOff) {
	int absRow = player->row + vOff;
	int absCol = player->col + hOff;
	if(frame % ANIMATION_SPEED_PLAYER == 0){
		player_walk_animation = (player_walk_animation + 4) % (4*PLAYER_WALK_STEPS);
	}

	if (direction == UP && canWalkLadder(absRow, absCol)) {
		if (player->row > V_CENTER || vOff <= 0) {
			moveSprite(NORTH, NONE, player);
		} else {
			scrollMap(NONE, NORTH);
		}
		*(player->spriteAttr2) = PLAYER_NORMAL;
	} else if (direction == DOWN && canWalkLadder(absRow + 1, absCol)) {
		if (player->row < V_CENTER || vOff >= V_SCROLL_MAX) {
			moveSprite(SOUTH, NONE, player);
		} else {
			scrollMap(NONE, SOUTH);
		}
		*(player->spriteAttr2) = PLAYER_NORMAL;
	} else if (direction == LEFT && canMoveHorizontal(absRow, absCol, WEST)) {
		if (player->col > H_CENTER || hOff <= 0) {
			moveSprite(NONE, WEST, player);
		} else {
			scrollMap(WEST, NONE);
		}
		//*(player->spriteAttr2) = playerwalk[player_walk_animation% PLAYERWALKLENGHT];
		*(player->spriteAttr2) = PLAYER_WALK + (player_walk_animation);
		*(player->spriteAttr1) |= ATTR1_HFLIP;
	} else if (direction == RIGHT && canMoveHorizontal(absRow, absCol, EAST)) {
		if (player->col < H_CENTER || hOff >= H_SCROLL_MAX) {
			moveSprite(NONE, EAST, player);
		} else {
			scrollMap(EAST, NONE);
		}

		//*(player->spriteAttr2) = playerwalk[player_walk_animation% PLAYERWALKLENGHT];
		*(player->spriteAttr2) = PLAYER_WALK + (player_walk_animation);
		*(player->spriteAttr1) &= ~ATTR1_HFLIP;

	} else {
		*(player->spriteAttr2) = PLAYER_NORMAL;
		player_walk_animation = 0;
	}
	player->arow = player->row;
	player->acol = player->col;

	checkForCoin(player);
	if (!canMoveHorizontal(absRow, absCol, 1)
			&& !canMoveHorizontal(absRow, absCol, -1) && !canWalkLadder(absRow, absCol)) {
		lost = vBlanks;
	}
}

void moveSprite(int rd, int cd, Sprite *sprite) {
	sprite->cCount += cd;
	if (sprite->cCount % sprite->speed == 0) {
		sprite->col += cd;
		sprite->col = max(sprite->col,H_SPRITE_MIN);
		sprite->col = min(sprite->col,H_SPRITE_MAX);
	}
	sprite->rCount += rd;
	if (sprite->rCount % sprite->speed == 0) {
		sprite->row += rd;
		sprite->row = min(sprite->row,V_SPRITE_MAX);
		sprite->row = max(sprite->row,V_SPRITE_MIN);
	}
}

