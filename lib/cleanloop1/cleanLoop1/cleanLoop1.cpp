#include "cleanLoop.h"
//

void cleanLoop(vector<gameObject *> gameObjects){

  gameObject ** p = gameObjects.data();

  int numObjects = gameObjects.size();

  for (int i = 0 ; i < numObjects; i++){

    (*p)->clearInputRecord();
    (*p)->clearStateChangeRecord();


    p++;

  }

}
