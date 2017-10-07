#include "inputHandler.h"
//The inputHandler class handles writing inputs to a file when in "keylogger" mode and reading inputs from a file
//when in "debug" mode.

inputHandler::inputHandler(string fileName, bool writeMode){


  if(writeMode){

    fs.open(fileName.c_str(), std::fstream::app);

  }
  else{

    fs.open(fileName.c_str(), std::fstream::in);

  }

  actionFrame = 0;
  currentFrame = 0;


}
void inputHandler::addInputToFile(string s){

  if(s.compare("QUIT") == 0){

    fs.put('Q');

  }
  else if(s.compare("ESCAPE") == 0){

    fs.put('E');

  }
  else if(s.compare("LEFT_PRESS") == 0){

    fs.put('L');

  }
  else if(s.compare("LEFT_RELEASE") == 0){

    fs.put('l');

  }
  else if(s.compare("RIGHT_PRESS") == 0){

    fs.put('R');

  }
  else if(s.compare("RIGHT_RELEASE") == 0){

    fs.put('r');

  }
  else if(s.compare("UP_PRESS") == 0){

    fs.put('U');

  }
  else if(s.compare("UP_RELEASE") == 0){

    fs.put('u');

  }
  else if(s.compare("DOWN_PRESS") == 0){

    fs.put('D');

  }
  else if(s.compare("DOWN_RELEASE") == 0){

    fs.put('d');

  }
  else if(s.compare("PAUSE") == 0){

    fs.put('P');

  }
  else if(s.compare("RIGHT_BUMPER_PRESS") == 0){


    fs.put('B');

  }
  else if(s.compare("A_BUTTON_PRESS") == 0){


    fs.put('A');

  }
  else if(s.compare("LEFT_BUMPER_PRESS") == 0){


    fs.put('O');

  }
  else if(s.compare("RIGHT_STICK_CLICK") == 0){


    fs.put('S');

  }
  else if(s.compare("LEFT_BUMPER_RELEASE") == 0){


    fs.put('o');

  }
  else if(s.find("JOYSTICK_LEFT") != -1){

    fs.put('C');
    fs.put('(');
    int size = s.size();
    size_t found = s.find("JOYSTICK_LEFT");
    for(int i = 13; i < size; i++){

      fs.put(s[i]);


    }
    fs.put(')');

  }
  else if(s.find("JOYSTICK_RIGHT") != -1){

    fs.put('F');
    fs.put('(');
    int size = s.size();
    size_t found = s.find("JOYSTICK_RIGHT");
    for(int i = 14; i < size; i++){

      fs.put(s[i]);


    }
    fs.put(')');

  }
  else if(s.compare("JOYSTICK_RELEASE") == 0){


    fs.put('G');

  }
  else if(s.find("JOYSTICK2_HELD") != -1){

    fs.put('H');
    fs.put('(');
    int size = s.size();
    size_t found = s.find("JOYSTICK2_HELD");
    for(int i = 14; i < size; i++){

      fs.put(s[i]);


    }
    fs.put(')');

  }
  else if(s.compare("JOYSTICK2_RELEASE") == 0){


    fs.put('h');

  }
  else if(s.compare("LEFT_TRIGGER_PRESS") == 0){


    fs.put('I');

  }
  else if(s.compare("RIGHT_TRIGGER_PRESS") == 0){


    fs.put('J');

  }
  else if(s.compare("LEFT_TRIGGER_RELEASE") == 0){


    fs.put('i');

  }
  else if(s.compare("RIGHT_TRIGGER_RELEASE") == 0){


    fs.put('j');

  }


}

void inputHandler::addNewLine(){

  fs.put('\n');


}

void inputHandler::addFrameCount(){

  fs << currentFrame;
  fs.put(':');

}
void inputHandler::updateCurrentFrame(int updatedFrame){

  currentFrame = updatedFrame;


}

void inputHandler::readActionFrame(){


  char c;
  string line;

  while(fs.get(c)){


      if(c == ':'){

        actionFrame = atoi(line.c_str());

        return;

      }
      else{


        line += c;

      }

  }






}

bool inputHandler::isActionFrame(){

  bool b = (actionFrame == currentFrame);

  if(b){

    return true;
  }
  else{

    return false;
  }


}

char inputHandler::nextChar(){

  char c;
  fs.get(c);
  return c;


}
