#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

void renderAll(vector<gameObject *> gameObjects, SDL_Renderer * renderer, double xRenderCoordFactor, double yRenderCoordFactor);
