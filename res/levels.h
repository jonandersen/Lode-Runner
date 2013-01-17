/*
 * levels.h
 *
 *  Created on: Nov 3, 2011
 *      Author: jonandersen
 */
#ifndef LEVELS_H_
#define LEVELS_H_

//GENERAL
#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 32
void setupLevels();
#define FREE 197
#define isLadder(number)  (number == 192) || (number == 193) || (number == 174) || (number == 175)
#define isCoin(number) (number == 10) || (number == 11) || (number == 26) || (number == 28)
#define isDestroyable(number) (number == 23) || (number == 24) || (number == 25) || (number == 26) || (number == 27) || (number == 28) || (number == 4)

#define NUMBER_OF_LEVELS 3

//LEVEL 1
extern unsigned short level1_A[1024];
extern unsigned short level1_B[1024];
#define P1R 0
#define P1C 0
#define vOff1 0
#define hOff1 0
#define LEVEL1_COINS 8
extern unsigned short coinRowLocation1[LEVEL1_COINS];
extern unsigned short coinColLocation1[LEVEL1_COINS];
#define LEVEL1_ENEMIES 0
extern unsigned short enemyRowLocation1[LEVEL1_ENEMIES];
extern unsigned short enemyColLocation1[LEVEL1_ENEMIES];

//LEVEL 2
extern unsigned short level2_A[1024];
extern unsigned short level2_B[1024];
#define P2R 0
#define P2C 0
#define vOff2 0
#define hOff2 0
#define LEVEL2_COINS 5
extern unsigned short coinRowLocation2[LEVEL2_COINS];
extern unsigned short coinColLocation2[LEVEL2_COINS];
#define LEVEL2_ENEMIES 1
extern unsigned short enemyRowLocation2[LEVEL2_ENEMIES];
extern unsigned short enemyColLocation2[LEVEL2_ENEMIES];

//LEVEL 3
extern unsigned short level3_A[1024];
extern unsigned short level3_B[1024];
#define P3R 104
#define P3C 64
#define vOff3 0
#define hOff3 0
#define LEVEL3_COINS 13
extern unsigned short coinRowLocation3[LEVEL3_COINS];
extern unsigned short coinColLocation3[LEVEL3_COINS];
#define LEVEL3_ENEMIES 2
extern unsigned short enemyRowLocation3[LEVEL3_ENEMIES];
extern unsigned short enemyColLocation3[LEVEL3_ENEMIES];



unsigned short *levels_A(int level);
unsigned short *levels_B(int level);

unsigned short PR(int level);
unsigned short PC(int level);

unsigned short levelCoins(int level);

unsigned short *coinRow(int level);
unsigned short *coinCol(int level);

unsigned short levelEnemies(int level);

unsigned short *enemyRow(int level);
unsigned short *enemyCol(int level);

int hOffL(int level);
int vOffL(int level);


#endif /* LEVELS_H_ */
