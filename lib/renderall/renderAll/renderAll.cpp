#include "renderAll.h"

//

void renderAll(vector<gameObject *> gameObjects, SDL_Renderer * renderer, double xRenderCoordFactor, double yRenderCoordFactor) {

	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();

	SDL_SetRenderDrawColor(renderer, 0xAF, 0xBF, 0xCF, 0xFF);
	SDL_RenderClear(renderer);

	for (int i = 0 ; i < numObjects; i++) {


		(*p)->show(100, 100, renderer, xRenderCoordFactor, yRenderCoordFactor);

		p++;

	}

	SDL_RenderPresent(renderer);


}

