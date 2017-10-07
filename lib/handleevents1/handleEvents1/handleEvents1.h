#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "../../gameobject/gameObject/gameObject.h"
#endif

#ifndef _INPUTHANDLER
#define _INPUTHANDLER
#include "../../inputhandler/inputHandler/inputHandler.h"
#endif

#include <fstream>
#include <sstream>


void handleEvents(bool * quit, bool * paused, vector<gameObject *> gameObjects, SDL_Joystick* gGameController);
void handleEventsWrite(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount, SDL_Joystick* gGameController);
void handleEventsRead(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount);
void handleEventsRead_SingleStepActionFrame(bool * quit, bool * paused, vector<gameObject *> gameObjects, inputHandler * iH, int frameCount, bool * iterateFrame);
void handleEventsRead_SingleStep(bool * iterateFrame, bool * quit);
void getJoystickInfo2(float * radiusLeft, float * angleLeft, int xDir, int yDir);
