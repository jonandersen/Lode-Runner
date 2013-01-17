/*
 * splash.h
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */
#ifndef SPLASH_H_
#define SPLASH_H_

#define ITEM1_ROW 75
#define ITEM1_COL 150
#define SPACE 12

int selected;

void setupSplash();
void runSplash();
#define BUTTON_PRESSED_S(key) (!(~(oldButtons_s)&(key)) && (~buttons_s & (key)))
void shadowLevel();
unsigned int buttons_s;
unsigned int oldButtons_s;

unsigned int animate;
unsigned short nextAnimateLevel;
int start;
short dir;

#endif /* SPLASH_H_ */
