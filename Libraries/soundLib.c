/*
 * sound.c
 *
 *  Created on: Oct 30, 2011
 *      Author: jonandersen
 */
#include "soundLib.h"
#include "myLib.h"

void setupInterrupts() {
	REG_IME = 0;
	REG_INTERRUPT = (unsigned int) interruptHandler;
	// accept interrupts
	REG_IE |= INT_VBLANK;
	// turn on interrupt sending
	REG_DISPSTAT |= INT_VBLANK_ENABLE;

	REG_IME = 1;
}

void interruptHandler() {
	REG_IME = 0;


	if (REG_IF & INT_VBLANK) {
		vBlanks ++;
		// MODIFY THIS FUNCTION !!!
		// Add code to stop/repeat sounds herez
		SoundChannel channel;
		for (channel = A; channel <= B; channel++) {
			vbCounts[channel]++;
			if (vbCounts[channel] > sounds[channel].duration) {
				timers[channel].cnt = 0;
				dma[1 + channel].cnt = 0;
				if (sounds[channel].loops) {
					playSound(channel, sounds[channel].data,
							sounds[channel].length, sounds[channel].frequency,
							sounds[channel].loops);
				} else {
					sounds[channel].isPlaying = 0;
				}
			}
		}

		REG_IF = INT_VBLANK;
	}

	REG_IME = 1;
}

void setupSounds() {
    // COMPLETE THIS FUNCTION !!!
    // This function will enable sounds

    // uncomment and complete the following lines
    REG_SOUNDCNT_X = SND_ENABLED; // Master sound control, determines whether you want sound or not. You have to enable that.

    // SOUND_OUTPUT_RATIO_100 = sound is going to be loud
    // DSA = DIRECT SOUND A
    REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 |
            DSA_OUTPUT_RATIO_100 |
            DSA_OUTPUT_TO_BOTH |
            DSA_TIMER0 |
            DSA_FIFO_RESET |
            DSB_OUTPUT_RATIO_100 |
            DSB_OUTPUT_TO_BOTH |
            DSB_TIMER1 |
            DSB_FIFO_RESET; // For all the settings that we will be using for our sounds.

    REG_SOUNDCNT_L = 0; // Is for legacy sounds. We're not going to be using them. We turn them off.
}

void playSound(SoundChannel channel, const unsigned char* sound, int length, int frequency, int isLooping) {

    // COMPLETE THIS FUNCTION !!!
    // Resets the dma and vbcount!
    dma[1 + channel].cnt = 0;
    vbCounts[channel] = 0;
    // This function will play a sound out of sound channel A

    // fist compute the timer interval for the sound.  The number of cycles divided by the frequency of the sound
    int interval = 16777216/frequency;

    // then setup the DMA channel for this sound

    DMANow(1 + channel, (void*)sound, (void*)REG_FIFO_A + channel * 4, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

    // then setup the timer for this sound
    timers[channel].cnt = 0;
    timers[channel].data = -interval;
    timers[channel].cnt = TIMER_ON;

    // you may have to create additional global variables for these functions to work (to stop the sounds later)
    sounds[channel].data = (void*)sound;
    sounds[channel].length = length;
    sounds[channel].frequency = frequency;
    sounds[channel].isPlaying = 1;
    sounds[channel].loops = isLooping;
    // Number of Vertical blanks.
    sounds[channel].duration = ((60 * length) / frequency) - ((length/frequency) * 3) - 1;
}

