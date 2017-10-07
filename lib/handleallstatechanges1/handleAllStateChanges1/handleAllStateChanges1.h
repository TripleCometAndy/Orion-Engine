#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

#ifndef _UGRID
#define _UGRID
#include "../uGrid/uGrid.h"
#endif

void handleAllStateChanges(vector<gameObject *> gameObjects, uGrid * uniformGrid, thread_pool * pool);
