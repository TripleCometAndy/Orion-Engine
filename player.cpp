#include "Orion.h"

player::player(int xCoor, int yCoor, int gWidth, int gHeight, string n, string file, string t, SDL_Renderer * renderer, uGrid * uniformGrid, double TIME) {

	x = xCoor;
	y = yCoor;
	width = gWidth;
	height = gHeight;

	rJoystick = false;
	lBumper = false;

	stateTimer = 0;
	attackTimer = 0;

	deltaX = 0;
	deltaY = 0;

	futureX = x;
	futureY = y;
	currentClip = 0;

	attackID = 0;

	timeFactor = TIME;

	jumping = false;
	futureJumping = false;
	jumpTimer = 0;

	xPress = false;

	image = NULL;
	shieldSheet = NULL;
	swordSheet = NULL;

	walking = false;
	futureWalking = false;

	shielding = false;
	futureShielding = false;

	radiusLeft = 0;
	angleLeft = 0;
	radiusRight = 90;
	angleRight = 90;
	angleShield = 90;

	attackPercent = 0.75;

	moveShieldPastVertical = 0;
	moveShieldFutureVertical = 0;
	moveShieldPastHorizontal = 0;
	moveShieldFutureHorizontal = 0;

	moveAttackPastVertical = 0;
	moveAttackFutureVertical = 0;
	moveAttackPastHorizontal = 0;
	moveAttackFutureHorizontal = 0;

	attackClip = 0;
	name = n;
	fileName = file;
	type = t;

	striking = false;
	futureStriking = false;

	direction = true;
	futureDirection = true;

	renderingWidth = 350;
	renderingHeight = 700;

	hitboxes.push_back(hitbox());
	hitboxes[0].left = x;
	hitboxes[0].right = x + width;
	hitboxes[0].top = y;
	hitboxes[0].bottom = y + height;
	hitboxes[0].name = "player_hitbox1";
	hitboxes[0].parentName = name;
	hitboxes[0].parentType = type;
	hitboxes[0].pastLeft = x;
	hitboxes[0].pastRight = x + width;
	hitboxes[0].pastTop = y;
	hitboxes[0].pastBottom = y + height;
	hitboxes[0].ID = PLAYER_HITBOX;

	//doop.push_back(OrionRect());
	//doop[0].X = 0;
	//doop[0].Y = 0;
	//doop[0].W = 0;
	//doop[0].H = 0;

	attackOne = -1;
	futureAttackOne = -1;
	attackTwo = -1;
	futureAttackTwo = -1;
	attackThree = -1;
	futureAttackThree = -1;

	airAttackTimer = -1;
	futureAirAttackTimer = -1;
	airAttack = false;
	futureAirAttack = false;

	attackClip = 0;

	shieldBashing = false;
	futureBashing = false;
	bashNum = 0;
	bashTimer = 0;

	downShielding = false;
	futureDownShielding = false;

	leftTriggerHandler = 0;
	rightTriggerHandler = 0;

	attackInfoFlipper = false;

	if (shieldSheet != NULL) {


		SDL_DestroyTexture(shieldSheet);
		shieldSheet = NULL;
		width = 0;
		height = 0;

	}


	SDL_Texture * newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load("images/spriteSheetShieldSmaller.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShield.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShield.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	shieldSheet = newTexture;

	if (swordSheet != NULL) {

		SDL_DestroyTexture(swordSheet);
		swordSheet = NULL;
		width = 0;
		height = 0;


	}

	newTexture = NULL;

	loadedSurface = IMG_Load("images/spriteSheetPlayer.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetPlayer.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetPlayer.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	swordSheet = newTexture;


	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetAttackWithValues.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldBash3.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldBash3.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	attackSheet = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash3.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetAttack.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetAttack.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	bashSheet1 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash1.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetBash1.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetBash1.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	bashSheet2 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash2.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldBash2.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldBash2.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	bashSheet3 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldDown.png");

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldDown.png", IMG_GetError());

	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldDown.png", SDL_GetError());
			exit(1);
		}
		else {
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	airShieldSheet = newTexture;


	extractClipsFromXML("images/neutral.xml", 0);

///////////////////////////////



	extractClipsFromXML("images/shield.xml", 56);

///////////////////////////////////////////

	extractClipsFromXML("images/attack.xml", 98);

//////////////////////////////////

	extractClipsFromXML("images/shieldDown.xml", 224);

	//cout << framesVec.size() << endl;
	clip = &frames[currentClip];
	hitbox c = hitboxes[0];
	uniformGrid->addReferenceNoIgnore(c);
	//uniformGrid->update(hitboxes);



}

void player::handleInput(SDL_Event &e, SDL_Joystick* gGameController) {

	if (e.type == SDL_JOYBUTTONDOWN) {



		if (e.jbutton.button == 5) {

			addInput("RIGHT_BUMPER_PRESS");

		}

		if (e.jbutton.button == 0) {

			addInput("A_BUTTON_PRESS");

		}

		if (e.jbutton.button == 4) {


			addInput("LEFT_BUMPER_PRESS");

		}

		if (e.jbutton.button == 10) {


			addInput("RIGHT_STICK_CLICK");


		}
	}

	if (e.type == SDL_JOYBUTTONUP) {

		if (e.jbutton.button == 4) {

			addInput("LEFT_BUMPER_RELEASE");

		}


	}

	if (e.type == SDL_JOYAXISMOTION) {

		int xDirLeft = 3;
		int yDirLeft = 3;
		int xDirRight = 3;
		int yDirRight = 3;

		if ((int)e.jaxis.axis == 0) {

			cout << "Axis" << endl;

		}


		xDirLeft = SDL_JoystickGetAxis(gGameController, 0);

		yDirLeft = SDL_JoystickGetAxis(gGameController, 1);

		int leftTrigger = SDL_JoystickGetAxis(gGameController, 2);
		int rightTrigger = SDL_JoystickGetAxis(gGameController, 5);


		xDirRight = SDL_JoystickGetAxis(gGameController, 3);
		yDirRight = SDL_JoystickGetAxis(gGameController, 4);


		getJoystickInfo(&radiusLeft, &angleLeft, xDirLeft, yDirLeft);
		getJoystickInfo(&radiusRight, &angleRight, xDirRight, yDirRight);


		if (radiusLeft > 5000 && ((angleLeft >= 0 && angleLeft <= 90) || (angleLeft >= 270 && angleLeft <= 360))) {

			addInput("JOYSTICK_LEFT");

		}
		else if (radiusLeft > 5000) {

			addInput("JOYSTICK_RIGHT");

		}
		else if (radiusLeft < 5000) {

			addInput("JOYSTICK_RELEASE");


		}

		if (radiusRight > 5000) {

			addInput("JOYSTICK2_HELD");

		}
		else if (radiusRight < 5000) {

			addInput("JOYSTICK2_RELEASE");


		}

		if (leftTrigger >= 32667) {

			addInput("LEFT_TRIGGER_PRESS");


		}

		if (rightTrigger >= 32667) {

			addInput("RIGHT_TRIGGER_PRESS");

		}

		if (leftTrigger <= 5000) {

			addInput("LEFT_TRIGGER_RELEASE");


		}

		if (rightTrigger <= 5000) {

			addInput("RIGHT_TRIGGER_RELEASE");


		}

	}


}

void player::handleInputDebug(char c) {



	if (c == 'B') {

		addInput("RIGHT_BUMPER_PRESS");

	}

	if (c == 'A') {


		addInput("A_BUTTON_PRESS");

	}

	if (c == 'O') {

		addInput("LEFT_BUMPER_PRESS");

	}

	if (c == 'S') {

		addInput("RIGHT_STICK_CLICK");

	}

	if (c == 'o') {

		addInput("LEFT_BUMPER_RELEASE");
	}

	if (c == 'C') {

		addInput("JOYSTICK_LEFT");

	}

	if (c == 'F') {

		addInput("JOYSTICK_RIGHT");

	}

	if (c == 'G') {

		addInput("JOYSTICK_RELEASE");

	}

	if (c == 'H') {

		addInput("JOYSTICK2_HELD");

	}

	if (c == 'h') {

		addInput("JOYSTICK2_RELEASE");
	}

	if (c == 'I') {

		addInput("LEFT_TRIGGER_PRESS");

	}

	if (c == 'J') {

		addInput("RIGHT_TRIGGER_PRESS");
	}

	if (c == 'i') {

		addInput("LEFT_TRIGGER_RELEASE");
	}

	if (c == 'j') {

		addInput("RIGHT_TRIGGER_RELEASE");
	}

}

void player::handleStateChanges(vector<gameObject *> * objects, uGrid * uniformGrid, thread_pool * pool) {

	xMove = 0;

	processInputs();



	if (attackOne == -1 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 1) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackOneInfo();
		futureAttackOne = 0;
		futureShielding = false;

	}
	else if (attackOne >= 20 && attackOne < 50 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 3) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackTwoInfo();
		futureAttackTwo = 0;
		futureShielding = false;

	}
	else if (attackTwo >= 0 && attackTwo < 20 && attackThree == -1 && (rightTriggerHandler == 5) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackThreeInfo();
		futureAttackThree = 0;
		futureShielding = false;

	}
	else if (jumping && rightTriggerHandler == 1) {

		getAttackTwoInfo();
		futureAirAttack = true;
		futureAirAttackTimer = 0;


	}

	if (rJoystick && lBumper) {

		futureShielding = true;

	}
	else {

		futureShielding = false;

	}

	if (jumping) {

		handleJump();

	}

	if (shielding) {

		if (jumping && futureJumping) {

			handleShieldAir();

		}
		else if (futureBashing || shieldBashing) {

			handleShield();

			switch (bashTimer) {

				case 0:
					bashNum = 1;
					break;

				case 4:
					bashNum = 2;
					break;

				case 5:
					bashNum = 3;
					break;

				case 10:
					bashNum = 2;
					break;

				case 11:
					bashNum = 1;
					break;

				case 15:
					bashNum = 0;
					futureBashing = false;
					break;
			}

			bashTimer++;

		}
		else {

			handleShield();

		}




	}

	if (direction == true) {
		if (walking) {
			if (shielding) {
				xMove = -8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else {

				xMove = -13*(1/timeFactor)/(METERS_TO_PIXELS);

			}
		}
		else if (attackOne != -1) {

			groundAttackOneLeft();

		}
		else if (attackTwo != -1) {

			groundAttackTwoLeft();

		}
		else if (attackThree != -1) {

			groundAttackThreeLeft();

		}
		else if (airAttackTimer != -1) {

			airAttackLeft();


		}

	}
	else {

		if (walking) {

			if (shielding) {
				xMove = 8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else {

				xMove = 13*(1/timeFactor)/(METERS_TO_PIXELS);

			}

		}
		else if (attackOne != -1) {

			groundAttackOneRight();

		}
		else if (attackTwo != -1) {

			groundAttackTwoRight();

		}
		else if (attackThree != -1) {

			groundAttackThreeRight();
		}
		else if (airAttackTimer != -1) {

			airAttackRight();
		}
	}

	int xMoveInt = 0;

	xMove = xMove * timeFactor;
	xMove = xMove * METERS_TO_PIXELS;
	xMove = xMove * attackPercent;
	xMove = xMove * 0.5;
	xMove = xMove + deltaX;
	xMoveInt = (int)floor(xMove);
	deltaX = xMove - xMoveInt;

	futureX += xMoveInt;

	hitbox future;
	future.top = futureY;
	future.bottom = futureY + height;
	future.left = futureX;
	future.right = futureX + width;
	future.name = "future";
	future.parentName = name;


	if (uniformGrid->findName(future, LEFT_WALL, pool) || uniformGrid->findName(future, RIGHT_WALL, pool)) {

		futureX = x;

	}

}

void player::handleStateChangesSingleThreaded(vector<gameObject *> * objects, uGrid * uniformGrid) {

	xMove = 0;

	processInputs();



	if (attackOne == -1 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 1) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackOneInfo();
		futureAttackOne = 0;
		futureShielding = false;

	}
	else if (attackOne >= 20 && attackOne < 50 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 3) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackTwoInfo();
		futureAttackTwo = 0;
		futureShielding = false;

	}
	else if (attackTwo >= 0 && attackTwo < 20 && attackThree == -1 && (rightTriggerHandler == 5) && jumping == false) {

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackThreeInfo();
		futureAttackThree = 0;
		futureShielding = false;

	}
	else if (jumping && rightTriggerHandler == 1) {

		getAttackTwoInfo();
		futureAirAttack = true;
		futureAirAttackTimer = 0;


	}

	if (rJoystick && lBumper) {

		futureShielding = true;

	}
	else {

		futureShielding = false;

	}

	if (jumping) {

		handleJump();

	}

	if (shielding) {

		if (jumping && futureJumping) {

			handleShieldAir();

		}
		else if (futureBashing || shieldBashing) {

			handleShield();

			switch (bashTimer) {

				case 0:
					bashNum = 1;
					break;

				case 4:
					bashNum = 2;
					break;

				case 5:
					bashNum = 3;
					break;

				case 10:
					bashNum = 2;
					break;

				case 11:
					bashNum = 1;
					break;

				case 15:
					bashNum = 0;
					futureBashing = false;
					break;
			}

			bashTimer++;

		}
		else {

			handleShield();

		}




	}

	if (direction == true) {
		if (walking) {
			if (shielding) {
				xMove = -8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else {

				xMove = -13*(1/timeFactor)/(METERS_TO_PIXELS);

			}
		}
		else if (attackOne != -1) {

			groundAttackOneLeft();

		}
		else if (attackTwo != -1) {

			groundAttackTwoLeft();

		}
		else if (attackThree != -1) {

			groundAttackThreeLeft();

		}
		else if (airAttackTimer != -1) {

			airAttackLeft();


		}

	}
	else {

		if (walking) {

			if (shielding) {
				xMove = 8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else {

				xMove = 13*(1/timeFactor)/(METERS_TO_PIXELS);

			}

		}
		else if (attackOne != -1) {

			groundAttackOneRight();

		}
		else if (attackTwo != -1) {

			groundAttackTwoRight();

		}
		else if (attackThree != -1) {

			groundAttackThreeRight();
		}
		else if (airAttackTimer != -1) {

			airAttackRight();
		}
	}

	int xMoveInt = 0;

	xMove = xMove * timeFactor;
	xMove = xMove * METERS_TO_PIXELS;
	xMove = xMove * attackPercent;
	xMove = xMove * 0.5;
	xMove = xMove + deltaX;
	xMoveInt = (int)floor(xMove);
	deltaX = xMove - xMoveInt;

	futureX += xMoveInt;

	hitbox future;
	future.top = futureY;
	future.bottom = futureY + height;
	future.left = futureX;
	future.right = futureX + width;
	future.name = "future";
	future.parentName = name;


	if (uniformGrid->findNameSingleThread(future, LEFT_WALL) || uniformGrid->findNameSingleThread(future, RIGHT_WALL)) {

		futureX = x;

	}

}

void player::enactStateChanges(vector<gameObject *> * objects, SDL_Renderer * renderer, uGrid * uniformGrid) {

	attackOne = futureAttackOne;
	attackTwo = futureAttackTwo;
	attackThree = futureAttackThree;

	walking = futureWalking;
	futureWalking = walking;

	if (shielding && !futureShielding) {

		image = swordSheet;
		currentClip = 0;
		clip = &frames[currentClip];

	}

	airAttackTimer = futureAirAttackTimer;

	futureAirAttackTimer = airAttackTimer;

	airAttack = futureAirAttack;
	futureAirAttack = airAttack;

	shielding = futureShielding;
	futureShielding = shielding;

	shieldBashing = futureBashing;
	futureBashing = shieldBashing;



	downShielding = futureDownShielding;
	futureDownShielding = downShielding;

	jumping = futureJumping;
	futureJumping = jumping;



	striking = futureStriking;
	futureStriking = striking;

	if (shielding) {


		if (shieldBashing) {

			switch (bashNum) {

				case 1:
					image = bashSheet1;
					break;

				case 2:
					image = bashSheet2;
					break;

				case 3:
					image = bashSheet3;
					break;
			}

		}
		else if (downShielding) {

			image = airShieldSheet;


		}
		else {

			image = shieldSheet;
			bashTimer = 0;
			downShielding = false;
			futureDownShielding = false;



		}


		angleShield = angleRight;

		futureY -= moveShieldPastVertical;
		futureY += moveShieldFutureVertical;
		futureX -= moveShieldPastHorizontal;
		futureX += moveShieldFutureHorizontal;
		moveShieldPastVertical = moveShieldFutureVertical;
		moveShieldPastHorizontal = moveShieldFutureHorizontal;

	}

	if (attackOne == -1 && attackTwo == -1 && attackThree == -1 && airAttackTimer == -1) {



	}
	else {

		angleAttack = angleRight;

		if (striking) {
			if (attackID == 1) {

				if (attackInfoFlipper == false) {

					getAttackOneInfo();
					attackInfoFlipper = true;
				}
				else {

				}
			}
			else if (attackID == 2) {

				if (attackInfoFlipper == true) {

					getAttackTwoInfo();
					attackInfoFlipper = false;
				}
				else {



				}

			}
			else if (attackID == 3) {

				if (attackInfoFlipper == false) {

					getAttackThreeInfo();
					attackInfoFlipper = true;
				}
				else {



				}

			}

			currentClip = attackClip;

			image = attackSheet;

			clip = &frames[currentClip];

			futureY -= moveAttackPastVertical;
			futureY += moveAttackFutureVertical;
			futureX -= moveAttackPastHorizontal;
			futureX += moveAttackFutureHorizontal;
			moveAttackPastVertical = moveAttackFutureVertical;
			moveAttackPastHorizontal = moveAttackFutureHorizontal;
		}
		else {

			image = swordSheet;
			futureY -= moveAttackPastVertical;
			moveAttackPastVertical = 0;
			futureX -= moveAttackPastHorizontal;
			moveAttackPastHorizontal = 0;
		}

		if (((angleAttack >= 0 && angleAttack <= 90) || (angleAttack >= 270 && angleAttack <= 360))) {

			direction = false;
			futureDirection = false;

		}
		else {

			direction = true;
			futureDirection = true;

		}


		futureY -= moveShieldPastVertical;

		moveShieldPastVertical = 0;
		futureX -= moveShieldPastHorizontal;
		moveShieldPastHorizontal = 0;




		walking = false;
		futureWalking = false;




	}

	direction = futureDirection;

	move(futureX - x, futureY - y);

	uniformGrid->update(hitboxes);


}

//wormhole//
void player::getAttackOneInfo() {



	if (3 <= angleAttack && angleAttack < 357) {

		if (angleAttack < 237) {

			if (angleAttack < 177) {

				if (angleAttack < 90) {


					if (angleAttack < 21) {

						if (angleAttack < 15) {

							if (angleAttack < 9) {

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 120;
								moveAttackFutureVertical = 12;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 117;
								moveAttackFutureVertical = 12;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 119;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 27) {

							//21 <= angle < 27


							attackPercent = 1;
							attackClip = 118;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;



						}
						else {

							//27 <= angle < 90


							attackPercent = 1;
							attackClip = 116;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else {

					if (angleAttack < 165) {


						if (angleAttack < 159) {

							if (angleAttack < 153) {

								//90 <= angle 153



								attackPercent = 0.6;
								//attackClip = 101;
								attackClip = 106;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;
								//moveAttackFutureHorizontal = -35;
							}
							else {

								//153 <= angle < 159


								attackPercent = 0.63;
								attackClip = 99;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 98;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 171) {

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 102;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//171 <= angle < 177


							attackPercent = 0.69;
							attackClip = 103;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else {


				if (angleAttack < 207) {

					if (angleAttack < 195) {

						if (angleAttack < 189) {

							if (angleAttack < 183) {

								//177 <= angle < 183


								attackPercent = 0.7;
								attackClip = 100;

								moveAttackFutureHorizontal = 0;

							}
							else {

								//183 <= angle < 189


								attackPercent = 0.71;
								attackClip = 164;
								moveAttackFutureVertical = 18;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//189 <= angle < 195


							attackPercent = 0.7;
							attackClip = 165;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 201) {

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 166;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 167;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else {

					if (angleAttack < 225) {

						if (angleAttack < 219) {

							if (angleAttack < 213) {

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 206;
								moveAttackFutureVertical = 8;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//213 <= angle < 219


								attackPercent = 0.7;
								attackClip = 212;
								moveAttackFutureVertical = -2;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 218;
							moveAttackFutureVertical = -10;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 231) {

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 134;
							moveAttackFutureVertical = -15;
							moveAttackFutureHorizontal = 0;
						}
						else {

							//231 <= angle < 237


							attackPercent = 0.67;
							attackClip = 135;
							moveAttackFutureVertical = -22;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else {

			if (angleAttack < 297) {

				if (angleAttack < 267) {

					if (angleAttack < 255) {

						if (angleAttack < 249) {

							if (angleAttack < 243) {

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 137;
								moveAttackFutureVertical = -33;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 136;
								moveAttackFutureVertical = -33;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 138;
							moveAttackFutureVertical = -33;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 261) {

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 189;
							moveAttackFutureVertical = -45;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 190;
							moveAttackFutureVertical = -45;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else {

					if (angleAttack < 285) {

						if (angleAttack < 279) {

							if (angleAttack < 273) {

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 188;
								moveAttackFutureVertical = -50;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 197;
								moveAttackFutureVertical = -44;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 198;
							moveAttackFutureVertical = -44;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 291) {

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 149;
							moveAttackFutureVertical = -38;
							moveAttackFutureHorizontal = 0;



						}
						else {

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 150;
							moveAttackFutureVertical = -38;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else {

				if (angleAttack < 327) {

					if (angleAttack < 315) {

						if (angleAttack < 309) {

							if (angleAttack < 303) {


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 152;
								moveAttackFutureVertical = -28;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 153;
								moveAttackFutureVertical = -23;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 151;
							moveAttackFutureVertical = -18;
							moveAttackFutureHorizontal = 0;
						}

					}
					else {

						if (angleAttack < 321) {

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 221;
							moveAttackFutureVertical = -10;
							moveAttackFutureHorizontal = 0;


						}
						else {

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 215;
							moveAttackFutureVertical = -3;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else {

					if (angleAttack < 345) {

						if (angleAttack < 339) {

							if (angleAttack < 333) {

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 209;
								moveAttackFutureVertical = 13;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 176;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 178;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 351) {

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 177;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//351 <= angle < 357


							attackPercent = 1;
							attackClip = 179;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else {


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)

		attackPercent = 1;
		attackClip = 121;
		moveAttackFutureVertical = 12;
		moveAttackFutureHorizontal = 0;


	}


}

//wormhole
void player::getAttackTwoInfo() {

	if (3 <= angleAttack && angleAttack < 357) {

		if (angleAttack < 237) {

			if (angleAttack < 177) {

				if (angleAttack < 90) {


					if (angleAttack < 21) {

						if (angleAttack < 15) {

							if (angleAttack < 9) {

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 126;
								moveAttackFutureVertical = 17;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 123;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 124;
							moveAttackFutureVertical = 17;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 27) {

							//21 <= angle < 27

							attackPercent = 1;
							attackClip = 125;
							moveAttackFutureVertical = 17;
							moveAttackFutureHorizontal = 0;



						}
						else {

							//27 <= angle < 90



							attackPercent = 1;
							attackClip = 122;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else {

					if (angleAttack < 165) {


						if (angleAttack < 159) {

							if (angleAttack < 153) {

								//90 <= angle 153


								attackPercent = 0.6;
								attackClip = 104;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;
							}
							else {

								//153 <= angle < 159

								attackPercent = 0.63;
								attackClip = 106;
								moveAttackFutureVertical = 15;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 107;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 171) {

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 105;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//171 <= angle < 177


							attackPercent = 0.69;
							attackClip = 108;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else {


				if (angleAttack < 207) {

					if (angleAttack < 195) {

						if (angleAttack < 189) {

							if (angleAttack < 183) {

								//177 <= angle < 183

								attackPercent = 0.7;
								attackClip = 109;
								moveAttackFutureVertical = 15;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//183 <= angle < 189


								attackPercent = 0.7;
								attackClip = 171;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//189 <= angle < 195


							attackPercent = 0.7;
							attackClip = 168;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 201) {

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 169;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 170;
							moveAttackFutureVertical = 0;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else {

					if (angleAttack < 225) {

						if (angleAttack < 219) {

							if (angleAttack < 213) {

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 207;
								moveAttackFutureVertical = -20;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//213 <= angle < 219


								attackPercent = 0.7;
								attackClip = 213;
								moveAttackFutureVertical = -30;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 219;
							moveAttackFutureVertical = -37;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 231) {

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 139;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}
						else {

							//231 <= angle < 237



							attackPercent = 0.67;
							attackClip = 140;
							moveAttackFutureVertical = -63;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else {

			if (angleAttack < 297) {

				if (angleAttack < 267) {

					if (angleAttack < 255) {

						if (angleAttack < 249) {

							if (angleAttack < 243) {

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 142;
								moveAttackFutureVertical = -70;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 143;
								moveAttackFutureVertical = -79;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 141;
							moveAttackFutureVertical = -86;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 261) {

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 191;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 193;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else {

					if (angleAttack < 285) {

						if (angleAttack < 279) {

							if (angleAttack < 273) {

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 192;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 200;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 201;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 291) {

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 154;
							moveAttackFutureVertical = -78;
							moveAttackFutureHorizontal = 0;


						}
						else {

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 155;
							moveAttackFutureVertical = -78;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else {

				if (angleAttack < 327) {

					if (angleAttack < 315) {

						if (angleAttack < 309) {

							if (angleAttack < 303) {


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 156;
								moveAttackFutureVertical = -68;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 157;
								moveAttackFutureVertical = -57;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 158;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}

					}
					else {

						if (angleAttack < 321) {

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 222;
							moveAttackFutureVertical = -40;
							moveAttackFutureHorizontal = 0;


						}
						else {

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 216;
							moveAttackFutureVertical = -30;
							moveAttackFutureHorizontal = 0;


						}



					}

				}
				else {

					if (angleAttack < 345) {

						if (angleAttack < 339) {

							if (angleAttack < 333) {

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 210;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 180;
								moveAttackFutureVertical = 0;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 182;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 351) {

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 181;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//351 <= angle < 357


							attackPercent = 1;
							attackClip = 183;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else {


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		attackPercent = 1;
		attackClip = 127;
		moveAttackFutureVertical = 17;
		moveAttackFutureHorizontal = 0;


	}


}

//wormhole
void player::getAttackThreeInfo() {

	if (3 <= angleAttack && angleAttack < 357) {

		if (angleAttack < 237) {

			if (angleAttack < 177) {

				if (angleAttack < 90) {


					if (angleAttack < 21) {

						if (angleAttack < 15) {

							if (angleAttack < 9) {

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 132;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 129;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 131;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 27) {

							//21 <= angle < 27

							attackPercent = 1;
							attackClip = 130;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;



						}
						else {

							//27 <= angle < 90



							attackPercent = 1;
							attackClip = 128;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else {

					if (angleAttack < 165) {


						if (angleAttack < 159) {

							if (angleAttack < 153) {

								//90 <= angle 153



								attackPercent = 0.6;
								attackClip = 110;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;
							}
							else {

								//153 <= angle < 159


								attackPercent = 0.63;
								attackClip = 111;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 113;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 171) {

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 112;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//171 <= angle < 177

							attackPercent = 0.69;
							attackClip = 114;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else {


				if (angleAttack < 207) {

					if (angleAttack < 195) {

						if (angleAttack < 189) {

							if (angleAttack < 183) {

								//177 <= angle < 183


								attackPercent = 0.7;
								attackClip = 115;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//183 <= angle < 189


								attackPercent = 0.7;
								attackClip = 175;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//189 <= angle < 195

							attackPercent = 0.7;
							attackClip = 172;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 201) {

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 174;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 173;
							moveAttackFutureVertical = 0;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else {

					if (angleAttack < 225) {

						if (angleAttack < 219) {

							if (angleAttack < 213) {

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 208;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//213 <= angle < 219

								attackPercent = 0.7;
								attackClip = 214;
								moveAttackFutureVertical = -26;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 220;
							moveAttackFutureVertical = -37;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 231) {

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 145;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}
						else {

							//231 <= angle < 237



							attackPercent = 0.67;
							attackClip = 147;
							moveAttackFutureVertical = -63;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else {

			if (angleAttack < 297) {

				if (angleAttack < 267) {

					if (angleAttack < 255) {

						if (angleAttack < 249) {

							if (angleAttack < 243) {

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 146;
								moveAttackFutureVertical = -68;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 148;
								moveAttackFutureVertical = -78;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 144;
							moveAttackFutureVertical = -82;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 261) {

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 196;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 195;
							moveAttackFutureVertical = -90;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else {

					if (angleAttack < 285) {

						if (angleAttack < 279) {

							if (angleAttack < 273) {

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 194;
								moveAttackFutureVertical = -90;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 203;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 205;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}


					}
					else {

						if (angleAttack < 291) {

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 159;
							moveAttackFutureVertical = -82;
							moveAttackFutureHorizontal = 0;


						}
						else {

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 160;
							moveAttackFutureVertical = -75;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else {

				if (angleAttack < 327) {

					if (angleAttack < 315) {

						if (angleAttack < 309) {

							if (angleAttack < 303) {


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 161;
								moveAttackFutureVertical = -70;
								moveAttackFutureHorizontal = 0;


							}
							else {

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 163;
								moveAttackFutureVertical = -60;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 162;
							moveAttackFutureVertical = -50;
							moveAttackFutureHorizontal = 0;
						}

					}
					else {

						if (angleAttack < 321) {

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 223;
							moveAttackFutureVertical = -40;
							moveAttackFutureHorizontal = 0;


						}
						else {

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 217;
							moveAttackFutureVertical = -30;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else {

					if (angleAttack < 345) {

						if (angleAttack < 339) {

							if (angleAttack < 333) {

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 211;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;

							}
							else {

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 184;
								moveAttackFutureVertical = 0;
								moveAttackFutureHorizontal = 0;

							}

						}
						else {

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 186;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else {

						if (angleAttack < 351) {

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 185;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}
						else {

							//351 <= angle < 357

							attackPercent = 1;
							attackClip = 187;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else {


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		attackPercent = 1;
		attackClip = 133;
		moveAttackFutureVertical = 20;
		moveAttackFutureHorizontal = 0;


	}

}

void player::processInputs() {

	string * p = inputs.data();
	int numInputs = inputs.size();

	for (int i = 0 ; i < numInputs; i++) {

		if ((*p).compare("LEFT_TRIGGER_PRESS") == 0) {

			if (leftTriggerHandler % 2 == 0) {

				leftTriggerHandler++;

			}


		}

		if ((*p).compare("LEFT_TRIGGER_RELEASE") == 0) {

			if (leftTriggerHandler % 2 != 0) {

				leftTriggerHandler++;


			}

		}


		if ((*p).compare("RIGHT_TRIGGER_PRESS") == 0) {

			if (rightTriggerHandler % 2 == 0) {

				rightTriggerHandler++;

			}


		}

		if ((*p).compare("RIGHT_TRIGGER_RELEASE") == 0) {

			if (rightTriggerHandler % 2 != 0) {


				rightTriggerHandler++;


			}

		}

		if ((*p).compare("RIGHT_BUMPER_PRESS") == 0) {

			if (attackOne == -1 && attackTwo == -1 && attackThree == -1) {

				if (!jumping) {
					futureJumping = true;
					jumpTimer = 0;
				}
			}

		}

		if ((*p).compare("JOYSTICK_RIGHT") == 0) {

			if (attackOne == -1 && attackTwo == -1 && attackThree == -1) {

				futureDirection = true;

				futureWalking = true;

			}

		}
		else if ((*p).compare("JOYSTICK_LEFT") == 0) {

			if (attackOne == -1 && attackTwo == -1 && attackThree == -1) {
				futureDirection = false;
				futureWalking = true;
			}
		}
		else if ((*p).compare("JOYSTICK_RELEASE") == 0) {

			if (walking) {

				futureWalking = false;

			}

		}
		else if ((*p).compare("JOYSTICK2_HELD") == 0) {

			if (attackOne == -1 && attackTwo == -1 && attackThree == -1) {

				rJoystick = true;

			}
			else {

				rJoystick = false;

			}

		}
		else if ((*p).compare("LEFT_BUMPER_PRESS") == 0) {

			if (attackOne == -1 && attackTwo == -1 && attackThree == -1) {

				lBumper = true;

			}
			else {

				lBumper = false;

			}
		}
		else if ((*p).compare("LEFT_BUMPER_RELEASE") == 0) {

			lBumper = false;

		}
		else if ((*p).compare("JOYSTICK2_RELEASE") == 0) {

			rJoystick = false;

		}
		else if ((*p).compare("RIGHT_STICK_CLICK") == 0) {

			futureBashing = true;

		}

		p++;

	}

}

void player::handleShield() {

	if (3 <= angleShield && angleShield < 357) {


		if (angleShield < 237) {

			if (angleShield < 177) {

				if (angleShield < 90) {


					if (angleShield < 21) {

						if (angleShield < 15) {

							if (angleShield < 9) {

								//3 <= angle < 9


								moveShieldFutureVertical = -12;
								moveShieldFutureHorizontal = -10;
								currentClip = 81;

								clip = &frames[currentClip];

							}
							else {

								//9 <= angle < 15


								moveShieldFutureVertical = -8;
								moveShieldFutureHorizontal = -10;
								currentClip = 82;

								clip = &frames[currentClip];

							}

						}
						else {

							//15 <= angle < 21


							moveShieldFutureVertical = 0;
							moveShieldFutureHorizontal = -10;
							currentClip = 77;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 27) {

							//21 <= angle < 27


							moveShieldFutureVertical = 5;
							moveShieldFutureHorizontal = -10;
							currentClip = 78;

							clip = &frames[currentClip];



						}
						else {

							//27 <= angle < 90



							moveShieldFutureVertical = 11;
							moveShieldFutureHorizontal = -10;

							currentClip = 79;

							clip = &frames[currentClip];

						}

					}


				}
				else {

					if (angleShield < 165) {


						if (angleShield < 159) {

							if (angleShield < 153) {

								//90 <= angle 153



								moveShieldFutureVertical = 16;
								moveShieldFutureHorizontal = -32;
								currentClip = 56;

								clip = &frames[currentClip];

							}
							else {

								//153 <= angle < 159


								moveShieldFutureVertical = 8;
								moveShieldFutureHorizontal = -32;
								currentClip = 57;

								clip = &frames[currentClip];

							}

						}
						else {

							//159 <= angle < 165


							moveShieldFutureVertical = 3;
							moveShieldFutureHorizontal = -34;
							currentClip = 58;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 171) {

							//165 <= angle < 171


							moveShieldFutureVertical = -3;
							moveShieldFutureHorizontal = -35;
							currentClip = 59;

							clip = &frames[currentClip];

						}
						else {

							//171 <= angle < 177


							moveShieldFutureVertical = -7;
							moveShieldFutureHorizontal = -37;
							currentClip = 60;

							clip = &frames[currentClip];

						}

					}


				}

			}
			else {


				if (angleShield < 207) {

					if (angleShield < 195) {

						if (angleShield < 189) {

							if (angleShield < 183) {

								//177 <= angle < 183


								moveShieldFutureVertical = -10;
								moveShieldFutureHorizontal = -40;
								currentClip = 61;

								clip = &frames[currentClip];

							}
							else {

								//183 <= angle < 189


								moveShieldFutureVertical = -17;
								moveShieldFutureHorizontal = -38;
								currentClip = 62;

								clip = &frames[currentClip];

							}

						}
						else {

							//189 <= angle < 195


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -36;
							currentClip = 63;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 201) {

							//195 <= angle < 201


							moveShieldFutureVertical = -21;
							moveShieldFutureHorizontal = -35;
							currentClip = 64;

							clip = &frames[currentClip];

						}
						else {

							//201 <= angle < 207


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -35;
							currentClip = 65;

							clip = &frames[currentClip];

						}



					}

				}
				else {

					if (angleShield < 225) {

						if (angleShield < 219) {

							if (angleShield < 213) {

								//207 <= angle < 213


								moveShieldFutureVertical = -22;
								moveShieldFutureHorizontal = -32;
								currentClip = 66;

								clip = &frames[currentClip];


							}
							else {

								//213 <= angle < 219


								moveShieldFutureVertical = -27;
								moveShieldFutureHorizontal = -32;
								currentClip = 67;

								clip = &frames[currentClip];

							}

						}
						else {

							//219 <= angle < 225


							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -29;
							currentClip = 68;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 231) {

							//225 <= angle < 231



							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -27;
							currentClip = 69;

							clip = &frames[currentClip];

						}
						else {

							//231 <= angle < 237



							moveShieldFutureHorizontal = -24;
							currentClip = 70;

							clip = &frames[currentClip];

						}

					}



				}



			}


		}
		else {

			if (angleShield < 297) {

				if (angleShield < 267) {

					if (angleShield < 255) {

						if (angleShield < 249) {

							if (angleShield < 243) {

								//237 <= angle < 243


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -24;
								currentClip = 71;

								clip = &frames[currentClip];

							}
							else {

								//243 <= angle < 249


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -20;
								currentClip = 72;

								clip = &frames[currentClip];

							}

						}
						else {

							//249 <= angle < 255


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -17;
							currentClip = 73;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 261) {

							//255 <= angle < 261


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -12;
							currentClip = 74;

							clip = &frames[currentClip];

						}
						else {

							//261 <= angle < 267


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -8;
							currentClip = 75;

							clip = &frames[currentClip];

						}

					}


				}
				else {

					if (angleShield < 285) {

						if (angleShield < 279) {

							if (angleShield < 273) {

								//267 <= angle < 273


								moveShieldFutureVertical = -28;
								currentClip = 76;

								clip = &frames[currentClip];


							}
							else {

								//273 <= angle < 279


								moveShieldFutureVertical = -28;
								currentClip = 96;

								clip = &frames[currentClip];

							}

						}
						else {

							//279 <= angle < 285


							moveShieldFutureVertical = -28;
							currentClip = 97;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 291) {

							//285 <= angle < 291


							moveShieldFutureVertical = -28;
							currentClip = 92;

							clip = &frames[currentClip];


						}
						else {

							//291 <= angle < 297


							moveShieldFutureVertical = -28;
							currentClip = 93;

							clip = &frames[currentClip];

						}

					}

				}


			}
			else {

				if (angleShield < 327) {

					if (angleShield < 315) {

						if (angleShield < 309) {

							if (angleShield < 303) {


								//297 <= angle < 303


								moveShieldFutureVertical = -28;
								currentClip = 94;

								clip = &frames[currentClip];


							}
							else {

								//303 <= angle < 309


								moveShieldFutureVertical = -25;
								currentClip = 89;

								clip = &frames[currentClip];

							}

						}
						else {

							//309 <= angle < 315


							moveShieldFutureVertical = -30;
							currentClip = 90;

							clip = &frames[currentClip];
						}

					}
					else {

						if (angleShield < 321) {

							//315 <= angle < 321


							moveShieldFutureVertical = -30;
							currentClip = 91;

							clip = &frames[currentClip];


						}
						else {

							//321 <= angle < 327


							moveShieldFutureVertical = -30;
							currentClip = 86;

							clip = &frames[currentClip];

						}



					}

				}
				else {

					if (angleShield < 345) {

						if (angleShield < 339) {

							if (angleShield < 333) {

								//327 <= angle < 333


								moveShieldFutureVertical = -28;
								currentClip = 87;

								clip = &frames[currentClip];

							}
							else {

								//333 <= angle < 339


								moveShieldFutureVertical = -25;
								currentClip = 88;

								clip = &frames[currentClip];

							}

						}
						else {

							//339 <= angle < 345


							moveShieldFutureVertical = -25;
							currentClip = 83;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 351) {

							//345 <= angle < 351


							moveShieldFutureVertical = -28;
							currentClip = 84;

							clip = &frames[currentClip];

						}
						else {

							//351 <= angle < 357


							moveShieldFutureVertical = -22;
							currentClip = 85;

							clip = &frames[currentClip];


						}
					}
				}

			}

		}

	}
	else {


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		moveShieldFutureVertical = -18;
		moveShieldFutureHorizontal = -10;
		currentClip = 80;

		clip = &frames[currentClip];


	}



}

void player::handleJump() {
	/*
	switch(jumpTimer){
		case 0:
			futureY = y - 14;
			break;
		case 2:
			futureY = y - 28;
			break;
		case 4:
			futureY = y - 24;
			break;
		case 6:
			futureY = y - 22;
			break;
		case 8:
			futureY = y - 16;
			break;
		case 10:
			futureY = y - 16;
			break;
		case 12:
			futureY = y - 12;
			break;
		case 14:
			futureY = y - 8;
			break;
		case 16:
			futureY = y - 6;
			break;
		case 18:
			futureY = y - 4;
			break;
		case 20:
			futureY = y;
			break;
		case 22:
			futureY = y;
			break;
		case 24:
			futureY = y + 4;
			break;
		case 26:
			futureY = y + 6;
			break;
		case 28:
			futureY = y + 14;
			break;
		case 30:
			futureY = y + 12;
			break;
		case 32:
			futureY = y + 18;
			break;
		case 34:
			futureY = y + 18;
			break;
		case 36:
			futureY = y + 22;
			break;
		case 38:
			futureY = y + 24;
			break;
		case 40:
			futureY = y + 32;
			futureJumping = false;
			futureDownShielding = false;
			rightTriggerHandler = 0;
			break;
	}


	*/
	switch (jumpTimer) {

		case 0:
			futureY = y - 11;
			break;

		case 1:
			futureY = y - 11;
			break;

		case 2:
			futureY = y - 16;
			break;

		case 3:
			futureY = y - 16;
			break;

		case 4:
			futureY = y - 15;
			break;

		case 5:
			futureY = y - 15;
			break;

		case 6:
			futureY = y - 14;
			break;

		case 7:
			futureY = y - 14;
			break;

		case 8:
			futureY = y - 12;
			break;

		case 9:
			futureY = y - 12;
			break;

		case 10:
			futureY = y - 12;
			break;

		case 11:
			futureY = y - 12;
			break;

		case 12:
			futureY = y - 11;
			break;

		case 13:
			futureY = y - 11;
			break;

		case 14:
			futureY = y - 9;
			break;

		case 15:
			futureY = y - 9;
			break;

		case 16:
			futureY = y - 9;
			break;

		case 17:
			futureY = y - 9;
			break;

		case 18:
			futureY = y - 8;
			break;

		case 19:
			futureY = y - 8;
			break;

		case 20:
			futureY = y;
			break;

		case 21:
			futureY = y;
			break;

		case 23:
			futureY = y + 8;
			break;

		case 24:
			futureY = y + 8;
			break;

		case 25:
			futureY = y + 9;
			break;

		case 26:
			futureY = y + 9;
			break;

		case 27:
			futureY = y + 11;
			break;

		case 28:
			futureY = y + 11;
			break;

		case 29:
			futureY = y + 11;
			break;

		case 30:
			futureY = y + 11;
			break;

		case 31:
			futureY = y + 13;
			break;

		case 32:
			futureY = y + 13;
			break;

		case 33:
			futureY = y + 13;
			break;

		case 34:
			futureY = y + 13;
			break;

		case 35:
			futureY = y + 14;
			break;

		case 36:
			futureY = y + 14;
			break;

		case 37:
			futureY = y + 15;
			break;

		case 38:
			futureY = y + 15;
			break;

		case 39:
			futureY = y + 46;
			futureJumping = false;
			futureDownShielding = false;
			rightTriggerHandler = 0;
			break;
	}

	jumpTimer++;


}

void player::groundAttackOneLeft() {

	attackID = 1;

	switch (attackOne) {

		case 0:
			currentClip = 0;
			clip = &frames[currentClip];
			break;

		case 5:
			currentClip = 1;
			clip = &frames[currentClip];
			break;

		case 10:
			currentClip = 2;
			clip = &frames[currentClip];
			break;

		case 15:
			currentClip = 7;
			clip = &frames[currentClip];
			break;

		case 20:
			currentClip = 8;
			clip = &frames[currentClip];
			break;

		case 25:
			currentClip = 9;
			clip = &frames[currentClip];
			break;

		case 30:
			currentClip = 10;
			clip = &frames[currentClip];
			break;

		case 35:

			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -200*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 40:
			futureStriking = false;
			currentClip = 12;
			clip = &frames[currentClip];
			break;

		case 45:
			currentClip = 12;
			clip = &frames[currentClip];
			break;
	}

	if (attackOne == 50) {

		if (attackTwo != 0) {

			currentClip = 0;
			xMove = 200*(1/timeFactor)/(METERS_TO_PIXELS);
			clip = &frames[currentClip];
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}

		futureAttackOne = -1;

	}
	else {

		futureAttackOne = attackOne + 1;

	}

}

void player::groundAttackTwoLeft() {

	attackID = 2;

	switch (attackTwo) {

		case 0:
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = -5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			currentClip = 14;
			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 10:

			//currentClip = 15;
			clip = &frames[currentClip];
			xMove = -270*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 15:

			futureStriking = false;
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = 286*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
	}

	if (attackTwo == 20) {

		if (attackThree != 0) {
			currentClip = 0;
			clip = &frames[currentClip];
			xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}

		futureAttackTwo = -1;
	}
	else {

		futureAttackTwo = attackTwo + 1;

	}

}

void player::groundAttackThreeLeft() {

	attackID = 3;

	switch (attackThree) {

		case 0:
			currentClip = 17;
			clip = &frames[currentClip];
			xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			currentClip = 18;
			clip = &frames[currentClip];
			break;

		case 10:
			currentClip = 19;
			clip = &frames[currentClip];
			break;

		case 15:
			currentClip = 20;
			clip = &frames[currentClip];
			xMove = -90*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 20:
			futureStriking = true;
			currentClip = 21;
			clip = &frames[currentClip];
			xMove = -290*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 30:
			futureStriking = false;
			clip = &frames[currentClip];
			xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 35:
			currentClip = 23;
			clip = &frames[currentClip];
			xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 40:

			currentClip = 24;
			clip = &frames[currentClip];
			xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 45:

			//currentClip = 25;
			clip = &frames[currentClip];
			xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 50:

			currentClip = 27;
			clip = &frames[currentClip];
			xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 55:
			currentClip = 27;
			clip = &frames[currentClip];
			xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
	}

	if (attackThree == 60) {

		currentClip = 0;
		clip = &frames[currentClip];
		futureAttackThree = -1;
		rightTriggerHandler = 0;
		attackInfoFlipper = false;

	}
	else {

		futureAttackThree = attackThree + 1;

	}

}

void player::groundAttackOneRight() {

	attackID = 1;

	switch (attackOne) {

		case 0:
			currentClip = 32;
			clip = &frames[currentClip];
			break;

		case 5:
			currentClip = 31;
			clip = &frames[currentClip];
			break;

		case 10:
			currentClip = 30;
			clip = &frames[currentClip];
			break;

		case 15:
			currentClip = 35;
			clip = &frames[currentClip];
			break;

		case 20:
			currentClip = 34;
			clip = &frames[currentClip];
			break;

		case 25:
			currentClip = 33;
			clip = &frames[currentClip];
			break;

		case 30:
			currentClip = 40;
			clip = &frames[currentClip];
			break;

		case 35:
			futureStriking = true;
			currentClip = 39;
			clip = &frames[currentClip];
			xMove = 50*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 45:
			futureStriking = false;
			currentClip = 38;
			clip = &frames[currentClip];
			break;

	}

	if (attackOne == 50) {

		if (attackTwo != 0) {

			currentClip = 32;
			xMove = -50*(1/timeFactor)/(METERS_TO_PIXELS);
			clip = &frames[currentClip];
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}

		futureAttackOne = -1;

	}
	else {

		futureAttackOne = attackOne + 1;

	}



}

void player::groundAttackTwoRight() {
	attackID = 2;

	switch (attackTwo) {

		case 0:
			currentClip = 43;
			clip = &frames[currentClip];
			xMove = 5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			futureStriking = true;
			currentClip = 42;
			clip = &frames[currentClip];
			xMove = 17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 10:
			currentClip = 41;
			clip = &frames[currentClip];
			xMove = 67*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 15:
			futureStriking = false;
			currentClip = 46;
			clip = &frames[currentClip];
			xMove = -71*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
	}

	if (attackTwo == 20) {

		if (attackThree != 0) {
			currentClip = 32;
			clip = &frames[currentClip];
			xMove = -68*(1/timeFactor)/(METERS_TO_PIXELS);
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}

		futureAttackTwo = -1;
	}
	else {

		futureAttackTwo = attackTwo + 1;


	}

}

void player::groundAttackThreeRight() {
	attackID = 3;

	switch (attackThree) {

		case 0:
			currentClip = 45;
			clip = &frames[currentClip];
			xMove = -62*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			currentClip = 44;
			clip = &frames[currentClip];
			break;

		case 10:
			currentClip = 49;
			clip = &frames[currentClip];
			break;

		case 15:
			currentClip = 48;
			clip = &frames[currentClip];
			xMove = 22*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 20:
			futureStriking = true;
			currentClip = 47;
			clip = &frames[currentClip];
			xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 30:
			futureStriking = false;
			currentClip = 52;
			clip = &frames[currentClip];
			xMove = -18*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 35:
			currentClip = 51;
			clip = &frames[currentClip];
			xMove = -18*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 40:
			currentClip = 50;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 45:
			currentClip = 55;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 50:
			currentClip = 54;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 55:
			currentClip = 53;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;


	}

	if (attackThree == 60) {

		currentClip = 32;
		clip = &frames[currentClip];
		futureAttackThree = -1;
		rightTriggerHandler = 0;
		attackInfoFlipper = false;

	}
	else {

		futureAttackThree = attackThree + 1;

	}


}

void player::handleShieldAir() {



	if (51 <= angleShield && angleShield < 57) {

		futureDownShielding = true;


		currentClip = 234;

		clip = &frames[currentClip];

	}
	else if (123 <= angleShield && angleShield < 129) {

		futureDownShielding = true;

		currentClip = 224;

		clip = &frames[currentClip];

	}
	else if (57 <= angleShield && angleShield < 123) {

		futureDownShielding = true;

		if (angleShield < 93) {

			if (angleShield < 75) {

				if (angleShield < 69) {

					if (angleShield < 63) {

						//57 <= x < 63
						//60
						currentClip = 235;

						clip = &frames[currentClip];

					}
					else {

						// 63 <= x < 69
						//66
						currentClip = 236;

						clip = &frames[currentClip];


					}

				}
				else {

					// 69 <= x < 75
					//72

					currentClip = 231;

					clip = &frames[currentClip];

				}

			}
			else {

				if (angleShield < 87) {

					if (angleShield < 81) {

						// 75 <= x < 81
						//78

						currentClip = 232;

						clip = &frames[currentClip];

					}
					else {

						// 81 <= x < 87
						//84

						currentClip = 233;

						clip = &frames[currentClip];


					}


				}
				else {

					//87 <= x < 93
					//90
					currentClip = 230;

					clip = &frames[currentClip];

				}

			}

		}
		else {

			if (angleShield < 111) {

				if (angleShield < 105) {

					if (angleShield < 99) {

						// 93 <= x < 99
						//96

						currentClip = 229;

						clip = &frames[currentClip];

					}
					else {

						// 99 <= x < 105
						//102

						currentClip = 228;

						clip = &frames[currentClip];

					}


				}
				else {

					// 105 <= x < 111
					//108

					currentClip = 227;

					clip = &frames[currentClip];

				}


			}
			else {

				if (angleShield < 117) {

					//111 <= x < 117
					//114


					currentClip = 226;

					clip = &frames[currentClip];



				}
				else {

					//117 <= x < 123
					//120

					currentClip = 225;

					clip = &frames[currentClip];

				}

			}

		}


	}
	else if (3 <= angleShield && angleShield < 357) {

		futureDownShielding = false;

		if (angleShield < 237) {

			if (angleShield < 177) {

				if (angleShield < 90) {


					if (angleShield < 21) {

						if (angleShield < 15) {

							if (angleShield < 9) {

								//3 <= angle < 9


								moveShieldFutureVertical = -12;
								moveShieldFutureHorizontal = -10;
								currentClip = 81;

								clip = &frames[currentClip];

							}
							else {

								//9 <= angle < 15


								moveShieldFutureVertical = -8;
								moveShieldFutureHorizontal = -10;
								currentClip = 82;

								clip = &frames[currentClip];

							}

						}
						else {

							//15 <= angle < 21


							moveShieldFutureVertical = 0;
							moveShieldFutureHorizontal = -10;
							currentClip = 77;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 27) {

							//21 <= angle < 27


							moveShieldFutureVertical = 5;
							moveShieldFutureHorizontal = -10;
							currentClip = 78;

							clip = &frames[currentClip];



						}
						else {

							//27 <= angle < 90



							moveShieldFutureVertical = 11;
							moveShieldFutureHorizontal = -10;

							currentClip = 79;

							clip = &frames[currentClip];

						}

					}


				}
				else {

					if (angleShield < 165) {


						if (angleShield < 159) {

							if (angleShield < 153) {

								//90 <= angle 153



								moveShieldFutureVertical = 16;
								moveShieldFutureHorizontal = -32;
								currentClip = 56;

								clip = &frames[currentClip];

							}
							else {

								//153 <= angle < 159


								moveShieldFutureVertical = 8;
								moveShieldFutureHorizontal = -32;
								currentClip = 57;

								clip = &frames[currentClip];

							}

						}
						else {

							//159 <= angle < 165


							moveShieldFutureVertical = 3;
							moveShieldFutureHorizontal = -34;
							currentClip = 58;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 171) {

							//165 <= angle < 171


							moveShieldFutureVertical = -3;
							moveShieldFutureHorizontal = -35;
							currentClip = 59;

							clip = &frames[currentClip];

						}
						else {

							//171 <= angle < 177


							moveShieldFutureVertical = -7;
							moveShieldFutureHorizontal = -37;
							currentClip = 60;

							clip = &frames[currentClip];

						}

					}


				}

			}
			else {


				if (angleShield < 207) {

					if (angleShield < 195) {

						if (angleShield < 189) {

							if (angleShield < 183) {

								//177 <= angle < 183


								moveShieldFutureVertical = -10;
								moveShieldFutureHorizontal = -40;
								currentClip = 61;

								clip = &frames[currentClip];

							}
							else {

								//183 <= angle < 189


								moveShieldFutureVertical = -17;
								moveShieldFutureHorizontal = -38;
								currentClip = 62;

								clip = &frames[currentClip];

							}

						}
						else {

							//189 <= angle < 195


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -36;
							currentClip = 63;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 201) {

							//195 <= angle < 201


							moveShieldFutureVertical = -21;
							moveShieldFutureHorizontal = -35;
							currentClip = 64;

							clip = &frames[currentClip];

						}
						else {

							//201 <= angle < 207


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -35;
							currentClip = 65;

							clip = &frames[currentClip];

						}



					}

				}
				else {

					if (angleShield < 225) {

						if (angleShield < 219) {

							if (angleShield < 213) {

								//207 <= angle < 213


								moveShieldFutureVertical = -22;
								moveShieldFutureHorizontal = -32;
								currentClip = 66;

								clip = &frames[currentClip];


							}
							else {

								//213 <= angle < 219


								moveShieldFutureVertical = -27;
								moveShieldFutureHorizontal = -32;
								currentClip = 67;

								clip = &frames[currentClip];

							}

						}
						else {

							//219 <= angle < 225


							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -29;
							currentClip = 68;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 231) {

							//225 <= angle < 231



							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -27;
							currentClip = 69;

							clip = &frames[currentClip];

						}
						else {

							//231 <= angle < 237



							moveShieldFutureHorizontal = -24;
							currentClip = 70;

							clip = &frames[currentClip];

						}

					}



				}



			}


		}
		else {

			if (angleShield < 297) {

				if (angleShield < 267) {

					if (angleShield < 255) {

						if (angleShield < 249) {

							if (angleShield < 243) {

								//237 <= angle < 243


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -24;
								currentClip = 71;

								clip = &frames[currentClip];

							}
							else {

								//243 <= angle < 249


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -20;
								currentClip = 72;

								clip = &frames[currentClip];

							}

						}
						else {

							//249 <= angle < 255


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -17;
							currentClip = 73;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 261) {

							//255 <= angle < 261


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -12;
							currentClip = 74;

							clip = &frames[currentClip];

						}
						else {

							//261 <= angle < 267


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -8;
							currentClip = 75;

							clip = &frames[currentClip];

						}

					}


				}
				else {

					if (angleShield < 285) {

						if (angleShield < 279) {

							if (angleShield < 273) {

								//267 <= angle < 273


								moveShieldFutureVertical = -28;
								currentClip = 76;

								clip = &frames[currentClip];


							}
							else {

								//273 <= angle < 279


								moveShieldFutureVertical = -28;
								currentClip = 96;

								clip = &frames[currentClip];

							}

						}
						else {

							//279 <= angle < 285


							moveShieldFutureVertical = -28;
							currentClip = 97;

							clip = &frames[currentClip];

						}


					}
					else {

						if (angleShield < 291) {

							//285 <= angle < 291


							moveShieldFutureVertical = -28;
							currentClip = 92;

							clip = &frames[currentClip];


						}
						else {

							//291 <= angle < 297


							moveShieldFutureVertical = -28;
							currentClip = 93;

							clip = &frames[currentClip];

						}

					}

				}


			}
			else {

				if (angleShield < 327) {

					if (angleShield < 315) {

						if (angleShield < 309) {

							if (angleShield < 303) {


								//297 <= angle < 303


								moveShieldFutureVertical = -28;
								currentClip = 94;

								clip = &frames[currentClip];


							}
							else {

								//303 <= angle < 309


								moveShieldFutureVertical = -25;
								currentClip = 89;

								clip = &frames[currentClip];

							}

						}
						else {

							//309 <= angle < 315


							moveShieldFutureVertical = -30;
							currentClip = 90;

							clip = &frames[currentClip];
						}

					}
					else {

						if (angleShield < 321) {

							//315 <= angle < 321


							moveShieldFutureVertical = -30;
							currentClip = 91;

							clip = &frames[currentClip];


						}
						else {

							//321 <= angle < 327


							moveShieldFutureVertical = -30;
							currentClip = 86;

							clip = &frames[currentClip];

						}



					}

				}
				else {

					if (angleShield < 345) {

						if (angleShield < 339) {

							if (angleShield < 333) {

								//327 <= angle < 333


								moveShieldFutureVertical = -28;
								currentClip = 87;

								clip = &frames[currentClip];

							}
							else {

								//333 <= angle < 339


								moveShieldFutureVertical = -25;
								currentClip = 88;

								clip = &frames[currentClip];

							}

						}
						else {

							//339 <= angle < 345


							moveShieldFutureVertical = -25;
							currentClip = 83;

							clip = &frames[currentClip];

						}

					}
					else {

						if (angleShield < 351) {

							//345 <= angle < 351


							moveShieldFutureVertical = -28;
							currentClip = 84;

							clip = &frames[currentClip];

						}
						else {

							//351 <= angle < 357


							moveShieldFutureVertical = -22;
							currentClip = 85;

							clip = &frames[currentClip];


						}
					}
				}

			}

		}

	}
	else {


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		moveShieldFutureVertical = -18;
		moveShieldFutureHorizontal = -10;
		currentClip = 80;

		clip = &frames[currentClip];


	}



}

void player::airAttackLeft() {

	switch (airAttackTimer) {

		case 0:
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = -5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			currentClip = 14;
			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 10:

			//currentClip = 15;
			clip = &frames[currentClip];
			xMove = -270*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 15:

			futureStriking = false;
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = 286*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
	}

	if (airAttackTimer == 20) {


		currentClip = 0;
		clip = &frames[currentClip];
		xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
		rightTriggerHandler = 0;
		attackInfoFlipper = false;



		futureAirAttackTimer = -1;
	}
	else {

		futureAirAttackTimer = airAttackTimer + 1;

	}


}

void player::airAttackRight() {

	switch (airAttackTimer) {

		case 0:
			currentClip = 43;
			clip = &frames[currentClip];
			xMove = 5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 5:
			futureStriking = true;
			currentClip = 42;
			clip = &frames[currentClip];
			xMove = 17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 10:
			currentClip = 41;
			clip = &frames[currentClip];
			xMove = 67*(1/timeFactor)/(METERS_TO_PIXELS);
			break;

		case 15:
			futureStriking = false;
			currentClip = 46;
			clip = &frames[currentClip];
			xMove = -71*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
	}

	if (airAttackTimer == 20) {


		currentClip = 32;
		clip = &frames[currentClip];
		xMove = -68*(1/timeFactor)/(METERS_TO_PIXELS);
		rightTriggerHandler = 0;
		attackInfoFlipper = false;


		futureAirAttackTimer = -1;
	}
	else {

		futureAirAttackTimer = airAttackTimer + 1;


	}

}

void getJoystickInfo(float * radiusLeft, float * angleLeft, int xDir, int yDir) {

	*radiusLeft = (float)sqrt(abs((long)(xDir*xDir) + (long)(yDir*yDir)));



	if (xDir == 0) {

		if (yDir > 0) {

			*angleLeft = 90;

		}
		else if (yDir < 0) {

			*angleLeft = 270;

		}
		else if (yDir == 0) {

			*angleLeft = 0;

		}

	}
	else if (yDir == 0) {

		if (xDir > 0) {

			*angleLeft = 0;

		}
		else if (xDir < 0) {

			*angleLeft = 180;

		}

	}
	else {

		if (xDir * -1 < 0 && yDir * -1 < 0) {

			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			//cout << "Angle: " << *angle << endl;

		}
		else if (xDir * -1 > 0 && yDir * -1 < 0) {


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft = 180 - abs(*angleLeft);

		}
		else if (xDir * -1 > 0 && yDir * -1 > 0) {


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft += 180;

		}
		else if (xDir * -1 < 0 && yDir * -1 > 0) {


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft += 360;

		}


	}


}

void player::printDebugInformation() {

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "DEBUG INFO" << endl;
	cout << "attacking: " << attacking << endl;
	cout << "attackOne: " << attackOne << endl;
	cout << "futureAttackOne: " << futureAttackOne << endl;
	cout << "attackTwo: " << attackTwo << endl;
	cout << "futureAttackTwo: " << futureAttackTwo << endl;
	cout << "attackThree: " << attackThree << endl;
	cout << "futureAttackThree: " << futureAttackThree << endl;
	cout << "direction: " << direction << endl;
	cout << "futureDirection: " << futureDirection << endl;
	cout << "jumping: " << jumping << endl;
	cout << "futureJumping: " << futureJumping << endl;
	cout << "jumpTimer: " << jumpTimer << endl;
	cout << "radiusLeft: " << radiusLeft << endl;
	cout << "radiusRight: " << radiusRight << endl;
	cout << "angleShield: " << angleShield << endl;
	cout << "angleAttack: " << angleAttack << endl;
	cout << "striking: " << striking << endl;
	cout << "futureStriking: " << futureStriking << endl;
	cout << "walking: " << walking << endl;
	cout << "futureWalking: " << futureWalking << endl;
	cout << "shielding: " << shielding << endl;
	cout << "futureShielding: " << futureShielding << endl;
	cout << "moveShieldPastVertical: " << moveShieldPastVertical << endl;
	cout << "moveShieldFutureVertical: " << moveShieldFutureVertical << endl;
	cout << "moveShieldPastHorizontal: " << moveShieldPastHorizontal << endl;
	cout << "moveShieldFutureHorizontal: " << moveShieldFutureHorizontal << endl;
	cout << "moveAttackPastVertical: " << moveAttackPastVertical << endl;
	cout << "moveAttackFutureVertical: " << moveAttackFutureVertical << endl;
	cout << "moveAttackPastHorizontal: " << moveAttackPastHorizontal << endl;
	cout << "moveAttackFutureHorizontal: " << moveAttackFutureHorizontal << endl;
	cout << "attackClip: " << attackClip << endl;
	cout << "rJoystick: " << rJoystick << endl;
	cout << "lBumper: " << lBumper << endl;
	cout << "attackPercent: " << attackPercent << endl;
	cout << "xMove" << xMove << endl;
	cout << "attackID: " << attackID << endl;
	cout << "deltaX: " << deltaX << endl;
	cout << "deltaY: " << deltaY << endl;
	cout << "timeFactor: " << timeFactor << endl;
	cout << "xPress: " << xPress << endl;
	cout << "shieldBashing: " << shieldBashing << endl;
	cout << "futureBashing: " << futureBashing << endl;
	cout << "bashNum: " << bashNum << endl;
	cout << "bashTimer: " << bashTimer << endl;
	cout << "downShielding: " << downShielding << endl;
	cout << "futureDownShielding: " << futureDownShielding << endl;
	cout << "leftTriggerHandler: " << leftTriggerHandler << endl;
	cout << "rightTriggerHandler: " << rightTriggerHandler << endl;
	cout << "airAttack: " << airAttack << endl;
	cout << "futureAirAttack: " << futureAirAttack << endl;
	cout << "airAttackTimer: " << airAttackTimer << endl;
	cout << "futureAirAttackTimer" << futureAirAttackTimer << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;


}

void player::extractClipsFromXML(string xmlFileName, int prevIndex) {

	string line;
	ifstream options(xmlFileName);
	int index = prevIndex;
	char c;
	int tempX = 0;
	int tempY = 0;
	int tempWidth = 0;
	int tempHeight = 0;

	while (options.get(c)) {


		if (c == '<') {

			while (c != '>') {

				line += c;
				options.get(c);

			}

		}

		if (line.compare("<X") == 0) {


			line.clear();
			options.get(c);

			while (c != '\n') {

				line += c;
				options.get(c);

			}

			tempX = atoi(line.c_str());



		}
		else if (line.compare("<Y") == 0) {

			line.clear();
			options.get(c);

			while (c != '\n') {

				line += c;
				options.get(c);

			}

			tempY = atoi(line.c_str());



		}
		else if (line.compare("<Width") == 0) {

			line.clear();
			options.get(c);

			while (c != '\n') {

				line += c;
				options.get(c);

			}

			tempWidth = atoi(line.c_str());



		}
		else if (line.compare("<Height") == 0) {

			line.clear();
			options.get(c);

			while (c != '\n') {

				line += c;
				options.get(c);

			}

			tempHeight = atoi(line.c_str());

			frames[index].x = tempX;
			frames[index].y = tempY;
			frames[index].w = tempWidth;
			frames[index].h = tempHeight;

			index++;

		}
		else {


			line.clear();
		}

	}




}

