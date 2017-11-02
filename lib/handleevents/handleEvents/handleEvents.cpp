#include "handleEvents.h"
#define PI 3.14159265
//

void handleEvents(bool * quit, bool * paused, vector<gameObject *> gameObjects, SDL_Joystick* gGameController) {

	SDL_Event e;

	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();



	//Handle events on queue

	while (SDL_PollEvent(&e) != 0) {

		p = gameObjects.data();


		//User requests quit

		if (e.type == SDL_QUIT) {
			*quit = true;
		}

		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_ESCAPE) {

				*quit = true;


			}

			if (e.key.keysym.sym == SDLK_p) {

				if (*paused == true) {

					*paused = false;


				}
				else {

					*paused = true;

				}


			}


		}

		if (e.type == SDL_JOYBUTTONDOWN) {


		}



		for (int i = 0; i < numObjects; i++) {

			(*p)->handleInput(e, gGameController);
			p++;

		}


	}

}

void handleEventsWrite(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount, SDL_Joystick* gGameController) {

	SDL_Event e;

	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();

	bool first = true;

	bool leftJoystick = false;
	bool rightJoystick = false;
	bool leftJoystickRelease = false;
	bool joystick2Held = false;
	bool joystick2Release = false;
	bool leftTriggerPress = false;
	bool leftTriggerRelease = false;
	bool rightTriggerPress = false;
	bool rightTriggerRelease = false;

	//Handle events on queue

	while (SDL_PollEvent(&e) != 0) {

		p = gameObjects.data();


		//User requests quit

		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_p) {

				if (*paused == true) {

					*paused = false;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("PAUSE");

				}
				else {

					*paused = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("PAUSE");

				}




			}


		}



		if (*paused == false) {

			if (e.type == SDL_QUIT) {
				*quit = true;

				if (first) {
					iH->addNewLine();
					iH->addFrameCount();
					first = false;
				}

				iH->addInputToFile("QUIT");
			}

			if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_ESCAPE) {

					*quit = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("ESCAPE");



				}

				if (e.key.keysym.sym == SDLK_LEFT) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("LEFT_PRESS");


				}

				if (e.key.keysym.sym == SDLK_RIGHT) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_PRESS");


				}

				if (e.key.keysym.sym == SDLK_UP) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("UP_PRESS");


				}

				if (e.key.keysym.sym == SDLK_DOWN) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("DOWN_PRESS");


				}

			}

			if (e.type == SDL_KEYUP) {

				if (e.key.keysym.sym == SDLK_LEFT) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("LEFT_RELEASE");


				}

				if (e.key.keysym.sym == SDLK_RIGHT) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_RELEASE");


				}

				if (e.key.keysym.sym == SDLK_UP) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("UP_RELEASE");


				}

				if (e.key.keysym.sym == SDLK_DOWN) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("DOWN_RELEASE");


				}



			}

			if (e.type == SDL_JOYBUTTONDOWN) {



				if (e.jbutton.button == 5) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_BUMPER_PRESS");

				}

				if (e.jbutton.button == 0) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("A_BUTTON_PRESS");

				}

				if (e.jbutton.button == 4) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("LEFT_BUMPER_PRESS");

				}

				if (e.jbutton.button == 10) {

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_STICK_CLICK");

				}
			}

			if (e.type == SDL_JOYBUTTONUP) {

				if (first) {
					iH->addNewLine();
					iH->addFrameCount();
					first = false;
				}

				if (e.jbutton.button == 4) {

					iH->addInputToFile("LEFT_BUMPER_RELEASE");

				}


			}

			if (e.type == SDL_JOYAXISMOTION) {

				int xDirLeft = 3;
				int yDirLeft = 3;
				int xDirRight = 3;
				int yDirRight = 3;
				float radiusLeft = 0;
				float radiusRight = 0;
				float angleLeft = 0;
				float angleRight = 0;

				xDirLeft = SDL_JoystickGetAxis(gGameController, 0);
				yDirLeft = SDL_JoystickGetAxis(gGameController, 1);

				int leftTrigger = SDL_JoystickGetAxis(gGameController, 2);
				int rightTrigger = SDL_JoystickGetAxis(gGameController, 5);
				//cout << rightTrigger << endl;

				xDirRight = SDL_JoystickGetAxis(gGameController, 3);
				yDirRight = SDL_JoystickGetAxis(gGameController, 4);


				getJoystickInfo2(&radiusLeft, &angleLeft, xDirLeft, yDirLeft);
				getJoystickInfo2(&radiusRight, &angleRight, xDirRight, yDirRight);


				if (radiusLeft > 5000 && ((angleLeft >= 0 && angleLeft <= 90) || (angleLeft >= 270 && angleLeft <= 360)) && !leftJoystick) {

					leftJoystick = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					string temp;

					string a;
					ostringstream strs;
					strs << angleLeft;
					a = strs.str();
					temp += "JOYSTICK_LEFT";
					temp += a;

					iH->addInputToFile(temp);

				}
				else if (radiusLeft > 5000 && !leftJoystick) {

					leftJoystick = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					string temp;

					string a;
					ostringstream strs;
					strs << angleLeft;
					a = strs.str();
					temp += "JOYSTICK_RIGHT";
					temp += a;
					iH->addInputToFile(temp);

				}
				else if (radiusLeft < 5000 && !leftJoystickRelease) {

					leftJoystickRelease = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("JOYSTICK_RELEASE");


				}

				if (radiusRight > 5000 && !rightJoystick) {

					rightJoystick = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					string temp;

					string a;
					ostringstream strs;
					strs << angleRight;
					a = strs.str();
					temp += "JOYSTICK2_HELD";
					temp += a;

					iH->addInputToFile(temp);

				}
				else if (radiusRight < 5000 && !joystick2Release) {
					joystick2Release = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("JOYSTICK2_RELEASE");


				}

				if (leftTrigger >= 32667 && !leftTriggerPress) {

					leftTriggerPress = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}


					iH->addInputToFile("LEFT_TRIGGER_PRESS");


				}

				if (rightTrigger >= 32667 && !rightTriggerPress) {

					rightTriggerPress = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_TRIGGER_PRESS");

				}

				if (leftTrigger <= 5000 && !leftTriggerRelease) {

					leftTriggerRelease = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("LEFT_TRIGGER_RELEASE");


				}

				if (rightTrigger <= 5000 && !rightTriggerRelease) {
					rightTriggerRelease = true;

					if (first) {
						iH->addNewLine();
						iH->addFrameCount();
						first = false;
					}

					iH->addInputToFile("RIGHT_TRIGGER_RELEASE");


				}

			}


		}

		if (e.type == SDL_JOYAXISMOTION) {


		}



		for (int i = 0; i < numObjects; i++) {

			(*p)->handleInput(e, gGameController);
			p++;

		}


	}


}

void handleEventsRead(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount) {


	gameObject ** p = gameObjects.data();

	int numObjects = gameObjects.size();
	char c;
	string line;
	float angleLeft = 0;
	float angleRight = 0;
	c = iH->nextChar();
	//cout << c << endl;

	while (c != 0) {

		if (c == '\n') {

			iH->readActionFrame();
			return;

		}
		else {

			if (c == 'Q') {

				*quit = true;
				exit(1);
			}

			if (c == 'E') {

				*quit = true;
				exit(1);


			}

			if (c == 'P') {

				if (*paused == true) {

					*paused = false;


				}
				else {

					*paused = true;

				}

			}

			if (c == 'C') {

				//read in (
				c = iH->nextChar();
				c = iH->nextChar();
				string temp;

				while (c != ')') {

					temp += c;
					c = iH->nextChar();

				}

				angleLeft = stof(temp);

				c = 'C';

			}

			if (c == 'F') {

				//read in (
				c = iH->nextChar();
				c = iH->nextChar();
				string temp;

				while (c != ')') {

					temp += c;
					c = iH->nextChar();

				}

				angleLeft = stof(temp);

				c = 'F';

			}

			if (c == 'H') {

				//read in (
				c = iH->nextChar();
				c = iH->nextChar();
				string temp;

				while (c != ')') {

					temp += c;
					c = iH->nextChar();

				}

				angleRight = stof(temp);

				c = 'H';

			}

			for (int i = 0; i < numObjects; i++) {
				(*p)->setAngleLeft(angleLeft);
				(*p)->setAngleRight(angleRight);
				(*p)->handleInputDebug(c);
				p++;

			}

			p = gameObjects.data();

		}

		c = iH->nextChar();
	}

}

void handleEventsRead_SingleStepActionFrame(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount, bool * iterateFrame) {


	gameObject ** p = gameObjects.data();

	SDL_Event e;

	//Handle events on queue

	while (SDL_PollEvent(&e) != 0) {

		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_SPACE) {

				*iterateFrame = true;

			}

			if (e.key.keysym.sym == SDLK_ESCAPE) {

				*quit = true;


			}
		}


	}


	if (*(iterateFrame) == true) {
		int numObjects = gameObjects.size();
		char c;
		string line;
		float angleLeft = 0;
		float angleRight = 0;
		c = iH->nextChar();
		//cout << c << endl;

		while (c != 0) {

			if (c == '\n') {

				iH->readActionFrame();
				return;

			}
			else {

				if (c == 'Q') {

					*quit = true;

				}

				if (c == 'E') {

					*quit = true;
					exit(1);

				}

				if (c == 'P') {

					if (*paused == true) {

						*paused = false;


					}
					else {

						*paused = true;

					}

				}

				if (c == 'C') {

					//read in (
					c = iH->nextChar();
					c = iH->nextChar();
					string temp;

					while (c != ')') {

						temp += c;
						c = iH->nextChar();

					}

					angleLeft = stof(temp);

					c = 'C';

				}

				if (c == 'F') {

					//read in (
					c = iH->nextChar();
					c = iH->nextChar();
					string temp;

					while (c != ')') {

						temp += c;
						c = iH->nextChar();

					}

					angleLeft = stof(temp);

					c = 'F';

				}

				if (c == 'H') {

					//read in (
					c = iH->nextChar();
					c = iH->nextChar();
					string temp;

					while (c != ')') {

						temp += c;
						c = iH->nextChar();

					}

					angleRight = stof(temp);

					c = 'H';

				}

				for (int i = 0; i < numObjects; i++) {
					(*p)->setAngleLeft(angleLeft);
					(*p)->setAngleRight(angleRight);
					(*p)->handleInputDebug(c);
					p++;

				}

				p = gameObjects.data();

			}

			c = iH->nextChar();
		}

	}

}

void handleEventsRead_SingleStep(bool * iterateFrame, bool * quit) {

	SDL_Event e;

	//Handle events on queue

	while (SDL_PollEvent(&e) != 0) {

		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_SPACE) {

				*iterateFrame = true;

			}

			if (e.key.keysym.sym == SDLK_ESCAPE) {

				*quit = true;


			}
		}

	}


}

void getJoystickInfo2(float * radiusLeft, float * angleLeft, int xDir, int yDir) {

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




/*
#include "handleEvents.h"

//

void handleEvents(bool * quit, bool * paused, vector<gameObject *> gameObjects, bool keylogger, bool debugMode){

  SDL_Event e;

  gameObject ** p = gameObjects.data();

  int numObjects = gameObjects.size();

  //Handle events on queue
  if(!keylogger){

    while (SDL_PollEvent(&e) != 0)
    {

      p = gameObjects.data();


      //User requests quit
      if (e.type == SDL_QUIT)
      {
        *quit = true;
      }

      if (e.type == SDL_KEYDOWN){

        if (e.key.keysym.sym == SDLK_ESCAPE){

          *quit = true;


        }
        if (e.key.keysym.sym == SDLK_p){

          if (*paused == true){

            *paused = false;


          }
          else{

            *paused = true;

          }


        }


      }

      if(e.type == SDL_JOYAXISMOTION){


      }

    }
  }
  else{

    ofstream logInputs;
    logInputs.open("Inputs.txt", std::ofstream::app);
    logInputs.put('\n');

    while (SDL_PollEvent(&e) != 0){

      p = gameObjects.data();

      //User requests quit
      if (e.type == SDL_QUIT)
      {
        *quit = true;
        logInputs.put('Q');
      }

      if (e.type == SDL_KEYDOWN){

        if (e.key.keysym.sym == SDLK_ESCAPE){

          *quit = true;
          logInputs.put('E');

        }
        if (e.key.keysym.sym == SDLK_p){

          if (*paused == true){

            *paused = false;


          }
          else{

            *paused = true;

          }
          logInputs.put('P');


        }

      }


      if(e.type == SDL_JOYAXISMOTION){


      }

    }
    logInputs.put('\n');
    logInputs.close();

  }

  if(!debugMode){

    for (int i = 0; i < numObjects; i++){

      (*p)->handleInput(e);
      p++;

    }

  }
  else{

    //read inputs from file//

  }


}
*/

