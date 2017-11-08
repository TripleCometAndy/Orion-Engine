#include "Orion.h"


int main(int argc, char **argv) {



	//Options//
	int FPS = 60;
	bool fullScreen = false; //true if game will run in fullscreen//
	bool debugMode = false; //true if debugMode//
	bool keylogger = false; //true if the keylogger will be run//
	bool debugSingleStep = false; //true if debug mode will happen manually, one frame at a time//
	bool debugDecouple = false; //debug mode with no SDL interaction//
	bool singleThread = false; //game runs with a single thread. No thread pool//

	//screen dimensions if not fullscreen//
	int screenWidth = 0;
	int screenHeight = 0;

	//Read Options from Options.txt. Returns true if Options.txt exists//
  if (checkOptions(&FPS, &fullScreen, &debugMode, &keylogger, &debugSingleStep, &debugDecouple, &singleThread)) {
		//set screen resolution for fullscreen//
		if (fullScreen) {

			//TODO. ADD This Into "LinuxFunctions.h"//
			Display* disp = XOpenDisplay(NULL);
			Screen*  scrn = DefaultScreenOfDisplay(disp);
			screenHeight = scrn->height;
			screenWidth  = scrn->width;

			//Windows//



			//setScreenDimension(&screenWidth, &screenHeight);



		}
		else {

			screenWidth = 1360;
			screenHeight = 768;

		}

	}
	else { //Options.txt doesn't exist. Use default values//

		FPS = 60;
		screenWidth = 1360;
		screenHeight = 768;
	}

	//The Orion Engine uses different modes for loops based on initial settings (debug, keylog, etc).//
	//Intended loop is entered here//

	if (debugMode == false &&
	keylogger == false &&
	debugSingleStep == false &&
	debugDecouple == false) {

		loop(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if (debugMode == false && keylogger == true) {

		loopWrite(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if (debugMode == true &&
	keylogger == false &&
	singleThread == false) {


		loopDebug(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if (debugSingleStep == true && keylogger == false) {

		loopDebugSingleStep(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if (debugDecouple == true && keylogger == false) {

		loopDebug_SDLDecoupled(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if (debugMode == true && keylogger == false &&
	singleThread == true) {

		loopDebugSingleThreaded(FPS, screenWidth, screenHeight, fullScreen);


	}



	return 0;
}
