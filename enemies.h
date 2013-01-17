/*
 * enemey.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jonandersen
 */
#include "Libraries/myLib.h"

#ifndef ENEMEY_H_
#define ENEMEY_H_

Sprite *enemies[15];
int nbrEnemies;

void setupEnemies(OBJ_ATTR shadowOAM[], int hOff, int vOff);
void updateEnemies(int hOff, int vOff);
void moveEnemies(int rd, int cd, Sprite *enemey) ;
void drawEnemies();
void freeEnemies();

int enemy_walk_animation[15];

#endif /* ENEMEY_H_ */
