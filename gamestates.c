#include "gamestates.h"
#include "splash.h"
#include "Libraries/myLib.h"
#include "Libraries/soundLib.h"
#include "res/mainsound.h"
#include "res/levels.h"

unsigned int buttons;
unsigned int oldButtons;



void run() {
	while (1) {
		buttons = BUTTONS;
		stateFunction();
		buttons = BUTTONS;
		oldButtons = buttons;
	}
}

void setup() {
	setupLevels();
	stateFunction = runSplash;
	setupSplash();
	setupInterrupts();
	setupSounds();
	playSound(B, (unsigned char*)main_11025Hz, MAIN_11025HZ_SIZE, 11025, 1);
}

