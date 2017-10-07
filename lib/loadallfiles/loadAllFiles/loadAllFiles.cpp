#include "loadAllFiles.h"

bool loadAllFiles(vector<gameObject *> objects, SDL_Renderer * renderer){

  gameObject ** p = objects.data();

  int numObjects = objects.size();

  for(int i = 0; i < numObjects; i++){

		if ((*p)->load_files(renderer) == false){

      //there was an issue in loading the file//
			return false;

		}

		p++;

	}
  //no issues in loading files//
  return true;
}
