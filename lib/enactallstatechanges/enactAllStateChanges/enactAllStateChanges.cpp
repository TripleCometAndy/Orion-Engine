#include "enactAllStateChanges.h"
//
void enactAllStateChanges(vector<gameObject *> gameObjects, SDL_Renderer * renderer, uGrid * uniformGrid, thread_pool * pool){

  gameObject ** p = gameObjects.data();

  int numObjects = gameObjects.size();

  for (int i = 0 ; i < numObjects; i++){



    (*p)->enactStateChanges(&gameObjects, renderer, uniformGrid, pool);

    p++;
  }

}
