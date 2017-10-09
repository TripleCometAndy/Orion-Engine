#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_mixer.h"

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#endif


#include <iostream>
#include <fstream>
#include <sstream>

#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

using namespace std;

bool init(int width, int height, SDL_Window ** gWindow, SDL_Renderer ** gRenderer, bool fullScreen, SDL_Joystick** gGameController, bool * hasController);
void close(vector<gameObject *> gameObjects, SDL_Renderer * gRenderer, SDL_Window * gWindow);
bool checkOptions(int * FPS, bool * fullscreen, bool * debugMode, bool * logKeys, bool * debugSingleStep, bool * decouple);
void GetDesktopResolution(int& horizontal, int& vertical);
