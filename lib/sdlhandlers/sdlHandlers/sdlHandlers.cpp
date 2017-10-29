#include "sdlHandlers.h"

bool init(int width, int height, SDL_Window ** gWindow, SDL_Renderer ** gRenderer, bool fullScreen, SDL_Joystick ** gGameController, bool * hasController)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		
		if (SDL_NumJoysticks() < 1)
		{
			(*hasController) = false;

			cout << "No Controller" << endl;
			//exit(1);

		}
		else
		{


			//Load joystick
			*gGameController = SDL_JoystickOpen(0);

			if (*gGameController == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}

			(*hasController) = true;


		}


		//
		if (fullScreen){

			(*gWindow) = SDL_CreateWindow("Orion Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_ShowCursor(0);
		}
		else{

			(*gWindow) = SDL_CreateWindow("Orion Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		}
		
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			(*gRenderer) = SDL_CreateRenderer((*gWindow), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor((*gRenderer), 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close(vector<gameObject *> gameObjects, SDL_Renderer * gRenderer, SDL_Window * gWindow)
{
	unsigned int pPos = 0;
	gameObject ** p = gameObjects.data();

	while (pPos < gameObjects.size()){

		(*p)->destruct();
		p++;
		pPos++;

	}

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	SDL_QuitSubSystem(SDL_INIT_HAPTIC);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	IMG_Quit();
	SDL_Quit();
}


bool checkOptions(int * FPS, bool * fullscreen, bool * debugMode, bool * logKeys, bool * debugSingleStep, bool * decouple){

	string line;
	ifstream options("Options.txt");
	stringstream s;
	int buffer;

	if (options.is_open()){

		char c;

		while(options.get(c)){

			if(c == '\n'){

				line.clear();
			}
			else{

				line += c;

			}

			if(line.compare("true") == 0){


				(*fullscreen) = true;



			}
			else if (line.compare("false") == 0){


				(*fullscreen) = false;


			}

			if(line.compare("FPS") == 0){

				line.clear();
				options.get(c);
				while(c != '\n'){

					line += c;
					options.get(c);

				}
				*FPS = atoi(line.c_str());

				line.clear();

			}

			if(line.compare("debug") == 0){


				(*debugMode) = true;



			}
			if(line.compare("keylogger") == 0){


				(*logKeys) = true;



			}
			if(line.compare("dSingleStep") == 0){


				(*debugSingleStep) = true;

			}
			if(line.compare("decouple") == 0){

				(*decouple) = true;

			}


		}
		return true;
		//cout << line << endl;

	}
	else{

		return false;

	}

	return false;

}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	/*
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
	*/
}
