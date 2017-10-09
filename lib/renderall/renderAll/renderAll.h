#ifdef _WIN32

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#endif



#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

void renderAll(vector<gameObject *> gameObjects, SDL_Renderer * renderer, double xRenderCoordFactor, double yRenderCoordFactor);
