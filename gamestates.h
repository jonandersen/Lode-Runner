/*
 * GameStates.h
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */

#ifndef GAMESTATES_H_
#define GAMESTATES_H_


typedef void (*stateFunctionPointer)();

stateFunctionPointer stateFunction;

void run();
void setup();

#endif /* GAMESTATES_H_ */
