/*
 * instructions.h
 *
 *  Created on: Nov 1, 2011
 *      Author: jonandersen
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

void setupInstructions();
void runInstructions();

unsigned short nbr;

#define BUTTON_PRESSED_INS(key) (!(~(oldButtonsIns)&(key)) && (~buttons & (key)))
unsigned int oldButtonsIns;
unsigned int buttonsIns;

#endif /* INSTRUCTIONS_H_ */
