#include "Orion.h"


int main(int argc, char **argv){


	clock_t begin = clock();
	//Options//
	int FPS = 60;
	bool fullScreen = false;
	bool debugMode = false;
	bool keylogger = false;
	bool debugSingleStep = false;
	bool debugDecouple = false;
	bool singleThread = false;


	int screenWidth = 1360;
	int screenHeight = 768;


	if (checkOptions(&FPS, &fullScreen, &debugMode, &keylogger, &debugSingleStep, &debugDecouple, &singleThread)){

		if (fullScreen){

			//Windows//

			Display* disp = XOpenDisplay(NULL);
			Screen*  scrn = DefaultScreenOfDisplay(disp);
			screenHeight = scrn->height;
			screenWidth  = scrn->width;

			//setScreenDimension(&screenWidth, &screenHeight);

			//screenWidth = 1360;
			//screenHeight = 768;

		}
		else{



		}

	}
	else{

		FPS = 60;

	}

	if(debugMode == false && keylogger == false && debugSingleStep == false && debugDecouple == false){

		loop(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if(debugMode == false && keylogger == true){

		loopWrite(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if(debugMode == true && keylogger == false && singleThread == false){


		loopDebug(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if(debugSingleStep == true && keylogger == false){

		loopDebugSingleStep(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if(debugDecouple == true && keylogger == false){

		loopDebug_SDLDecoupled(FPS, screenWidth, screenHeight, fullScreen);

	}
	else if(debugMode == true && keylogger == false && singleThread == true){

		loopDebugSingleThreaded(FPS, screenWidth, screenHeight, fullScreen);


	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed Secs: " << elapsed_secs << endl;

	return 0;
}
