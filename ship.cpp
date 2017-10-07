#include "Orion.h"


//testtesttest//

ship::ship(int xCoor, int yCoor, int gWidth, int gHeight, string n, string file, string t, SDL_Renderer * renderer, uGrid * uniformGrid, double TIME){

	x = xCoor;
	y = yCoor;
	width = gWidth;
	height = gHeight;


	//velocity in meters//
	xVel = 0;
	yVel = 0;
	velocity = 18.75;


	deltaX = 0;
	deltaY = 0;

	futureY = y;
	currentClip = 0;

	timeFactor = TIME;

	leftPress = false;
	rightPress = false;
  upPress = false;
  downPress = false;

  image = NULL;

	name = n;
	fileName = file;
	type = t;

	hitboxes.push_back(hitbox());
	hitboxes[0].left = x;
	hitboxes[0].right = x + width;
	hitboxes[0].top = y;
	hitboxes[0].bottom = y + height;
	hitboxes[0].name = "ship_hitbox1";
	hitboxes[0].parentName = name;
	hitboxes[0].parentType = type;
	hitboxes[0].pastLeft = x;
	hitboxes[0].pastRight = x + width;
	hitboxes[0].pastTop = y;
	hitboxes[0].pastBottom = y + height;



	frames[0].x = 0;
	frames[0].y = 0;
	frames[0].w = width;
	frames[0].h = height;

	clip = &frames[currentClip];
	hitbox c = hitboxes[0];
	uniformGrid->addReferenceNoIgnore(c);
	//uniformGrid->update(hitboxes);



}
bool ship::exploding(uGrid * uniformGrid){

	vector<hitbox> collidingCrushers;
	hitbox c = hitboxes[0];
	uniformGrid->getName(c,"crushZoneLeft",&collidingCrushers);
	uniformGrid->getName(c,"crushZoneRight",&collidingCrushers);
	//cout << collidingCrushers.size() << endl;

	int numCrushersLeft = 0;
	int numCrushersRight = 0;
	hitbox * g = collidingCrushers.data();
	int count = collidingCrushers.size();
	for(int i = 0; i < count; i++){

		if(!(g->parentType.compare("blockLeft"))){

			numCrushersLeft++;


		}
		if(!(g->parentType.compare("blockRight"))){

			numCrushersRight++;


		}
		g++;

	}
	if(numCrushersLeft >= 1 && numCrushersRight >= 1){

		return true;

	}
	else{

		return false;
	}


}

void ship::handleInput(SDL_Event &e){

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{



		if (e.key.keysym.sym == SDLK_LEFT){

			addInput("LEFT_PRESS");


		}

		if (e.key.keysym.sym == SDLK_RIGHT){

			addInput("RIGHT_PRESS");


		}

    if (e.key.keysym.sym == SDLK_UP){

			addInput("UP_PRESS");


		}

		if (e.key.keysym.sym == SDLK_DOWN){

			addInput("DOWN_PRESS");


		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0){

		if (e.key.keysym.sym == SDLK_LEFT){

			addInput("LEFT_RELEASE");


		}
		else if (e.key.keysym.sym == SDLK_RIGHT){

			addInput("RIGHT_RELEASE");


		}
    else if (e.key.keysym.sym == SDLK_UP){

			addInput("UP_RELEASE");


		}
    else if (e.key.keysym.sym == SDLK_DOWN){

			addInput("DOWN_RELEASE");


		}
		else{


		}

	}



}

void ship::handleInputDebug(char c){

	if (c == 'L'){

		addInput("LEFT_PRESS");


	}
	else if(c == 'l'){

		addInput("LEFT_RELEASE");

	}
	else if(c == 'R'){

		addInput("RIGHT_PRESS");

	}
	else if(c == 'r'){

		addInput("RIGHT_RELEASE");

	}
	else if(c == 'U'){

		addInput("UP_PRESS");

	}
	else if(c == 'u'){

		addInput("UP_RELEASE");

	}
	else if(c == 'D'){

		addInput("DOWN_PRESS");

	}
	else if(c == 'd'){

		addInput("DOWN_RELEASE");

	}

}

void ship::handleStateChanges(vector<gameObject *> * objects, uGrid * uniformGrid){



	string * p = inputs.data();
	int numInputs = inputs.size();


	for (int i = 0 ; i < numInputs; i++){


		if ((*p).compare("LEFT_PRESS") == 0){

			leftPress = true;


		}

		if ((*p).compare("RIGHT_PRESS") == 0){

			rightPress = true;


		}

    if ((*p).compare("UP_PRESS") == 0){

			upPress = true;


		}

		if ((*p).compare("DOWN_PRESS") == 0){

			downPress = true;


		}



		if ((*p).compare("LEFT_RELEASE") == 0){

			leftPress = false;


		}

		if ((*p).compare("RIGHT_RELEASE") == 0){

			rightPress = false;


		}

    if ((*p).compare("UP_RELEASE") == 0){

			upPress = false;


		}

		if ((*p).compare("DOWN_RELEASE") == 0){

			downPress = false;


		}



		p++;

	}
	int leftCrusher = 0;
	int rightCrusher = 0;
	//int leftTop = 0;
	//int leftBottom = 0;
	//int rightTop = 0;
	//int rightBottom = 0;
	//int wall = 0;
	int leftMiddle = 0;
	//int rightMiddle = 0;
	/*
	vector<hitbox> * leftCrushers = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * rightCrushers = uniformGrid->getName(hitboxes[0], "crushZoneRight");
	vector<hitbox> * leftTops = uniformGrid->getName(hitboxes[0], "");
	vector<hitbox> * rightTops = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * leftBottoms = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * rightBottoms = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * walls = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * leftMiddles = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	vector<hitbox> * rightMiddles = uniformGrid->getName(hitboxes[0], "crushZoneLeft");
	*/
	//cout << collidingCrushers.size() << endl;


	if(leftCrusher >= 1 && rightCrusher >= 1){

		cout << "Explodes" << endl;
		exit(1);

	}
	if(leftMiddle >= 1){



	}
	else{


	}




	int xMoveInt = 0;
  int yMoveInt = 0;
  double yMove = 0;
	double xMove = 0;


	if((leftPress || rightPress) && !(upPress || downPress)){


		xMove = velocity * timeFactor;

		xMove = xMove * METERS_TO_PIXELS;

		xMove = xMove + deltaX;
		xMoveInt = (int)floor(xMove);


		deltaX = xMove - xMoveInt;




	}
  else if(!(leftPress || rightPress) && (upPress || downPress)){




    yMove = (velocity * timeFactor);


		yMove = yMove * METERS_TO_PIXELS;
		yMove = yMove + deltaY;
		yMoveInt = (int)floor(yMove);
		deltaY = yMove - yMoveInt;


	}
  else if((leftPress || rightPress) && (upPress || downPress)){



    xMove = (velocity * timeFactor)/2;
    yMove = (velocity * timeFactor)/2;

    xMove = xMove * METERS_TO_PIXELS;
		xMove = xMove + deltaX;
		xMoveInt = (int)floor(xMove);
		deltaX = xMove - xMoveInt;

		yMove = yMove * METERS_TO_PIXELS;
		yMove = yMove + deltaY;
		yMoveInt = (int)floor(yMove);
		deltaY = yMove - yMoveInt;


	}


	if (leftPress){

		futureX = (x - xMoveInt);

	}
	else if (rightPress){

		futureX = x + xMoveInt;

	}
	else{

		futureX = x;

	}

  if (upPress){

		futureY = (y - yMoveInt);

	}
	else if (downPress){

		futureY = y + yMoveInt;

	}
	else{

		futureY = y;

	}

	hitbox future;
	future.top = futureY;
	future.bottom = futureY + height;
	future.left = futureX;
	future.right = futureX + width;
	future.name = "future";
	future.parentName = name;

	if (uniformGrid->findName(future, "wall")){

		futureX = x;


	}
  if (uniformGrid->findName(future, "background_topWall") || uniformGrid->findName(future, "background_bottomWall")){

		futureY = y;
		//cout << "Top or bottom wall" << endl;
	}

}

void ship::enactStateChanges(vector<gameObject *> * objects, SDL_Renderer * renderer, uGrid * uniformGrid){



	move(futureX - x, futureY - y);

	uniformGrid->update(hitboxes);


}
