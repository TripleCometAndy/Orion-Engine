#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

#ifndef _UGRID
#define _UGRID
#include "../uGrid/uGrid.h"
#endif

void enactAllStateChanges(vector<gameObject *> gameObjects, SDL_Renderer * renderer, uGrid * uniformGrid);
