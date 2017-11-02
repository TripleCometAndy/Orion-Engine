#include "handleAllStateChanges.h"

//

void handleAllStateChanges(vector<gameObject *> gameObjects, uGrid * uniformGrid, thread_pool * pool) {

	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();

	for (int i = 0 ; i < numObjects; i++) {

		(*p)->handleStateChanges(&gameObjects, uniformGrid, pool);

		p++;
	}

}

void handleAllStateChangesSingleThreaded(vector<gameObject *> gameObjects, uGrid * uniformGrid) {

	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();

	for (int i = 0 ; i < numObjects; i++) {

		(*p)->handleStateChangesSingleThreaded(&gameObjects, uniformGrid);

		p++;
	}

}

