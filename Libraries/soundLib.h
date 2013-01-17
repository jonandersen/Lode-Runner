/*
 * sound.h
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "myLib.h"

#define REG_SOUNDCNT_X *(volatile u16 *)0x04000084

// register definitions
#define REG_SOUNDCNT_L        *(u16*)0x04000080
#define REG_SOUNDCNT_H        *(volatile u16*)0x04000082

// flags
#define SND_ENABLED           (1<<7)
#define SND_OUTPUT_RATIO_25   0
#define SND_OUTPUT_RATIO_50   (1<<0)
#define SND_OUTPUT_RATIO_100  (1<<1)
#define DSA_OUTPUT_RATIO_50   0
#define DSA_OUTPUT_RATIO_100  (1<<2)
#define DSA_OUTPUT_TO_RIGHT   (1<<8)
#define DSA_OUTPUT_TO_LEFT    (1<<9)
#define DSA_OUTPUT_TO_BOTH    (3<<8)
#define DSA_TIMER0            0
#define DSA_TIMER1            (1<<10)
#define DSA_FIFO_RESET        (1<<11)
#define DSB_OUTPUT_RATIO_50   0
#define DSB_OUTPUT_RATIO_100  (1<<3)
#define DSB_OUTPUT_TO_RIGHT   (1<<12)
#define DSB_OUTPUT_TO_LEFT    (1<<13)
#define DSB_OUTPUT_TO_BOTH    (3<<12)
#define DSB_TIMER0            0
#define DSB_TIMER1            (1<<14)
#define DSB_FIFO_RESET        (1<<15)

// FIFO address defines
#define REG_FIFO_A          0x040000A0
#define REG_FIFO_B          0x040000A4


typedef enum {A, B} SoundChannel;

typedef struct {
    u8* data;
    int length;
    int frequency;
    int loops;
    int isPlaying;
    int duration;
} Sound;

Sound sounds[2];
int vbCounts[2];

void setupSounds();
void playSound(SoundChannel channel, const unsigned char* sound, int length, int frequency, int isLooping) ;
void setupInterrupts();
void interruptHandler();

#endif /* SOUND_H_ */
