/*
 * characters.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jonandersen
 */

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

void playerFall(Sprite *player,int vOff);
void movePlayer(int direction, Sprite *player, int vOff, int hOff) ;

void moveSprite(int rd, int cd, Sprite *sprite);

#define ROWMASK 0xFF
#define COLMASK 0x1FF

int isShooting;
void animateShoot(int vBlanks, Sprite *shot);

#define ANIMATION_SPEED_PLAYER 10


#endif /* CHARACTERS_H_ */
