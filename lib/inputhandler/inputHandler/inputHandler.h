#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class inputHandler {

private:

	fstream fs;
	int currentFrame;
	int actionFrame;

public:

	inputHandler(string fileName, bool writeMode);
	void addInputToFile(string s);
	void addNewLine();
	void addFrameCount();
	void updateCurrentFrame(int updatedFrame);
	void readActionFrame();
	bool isActionFrame();
	char nextChar();



};

