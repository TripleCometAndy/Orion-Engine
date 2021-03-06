#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../lib/gameobject/gameObject/gameObject.h"
#endif

using namespace std;

bool init(int width, int height, SDL_Window ** gWindow, SDL_Renderer ** gRenderer, bool fullScreen, SDL_Joystick* gGameController, bool * hasController);
void close(vector<gameObject *> gameObjects, SDL_Renderer * gRenderer, SDL_Window * gWindow);
bool checkOptions(int * FPS, bool * fullscreen);
void GetDesktopResolution(int& horizontal, int& vertical);
